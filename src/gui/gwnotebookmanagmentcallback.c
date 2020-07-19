/*  GWhere.
 *  Copyright (C) 2000  Sébastien LECACHEUR
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#include "../gwsupport.h"
#include "gwnotebookmanagmentcallback.h"

#include <string.h> /* strcmp strlen */
#include <sys/types.h>

#include "data/gwdata.h"
#include "tools/gwtools.h"
#include "res/gwres.h"

#include "gwcomboboxcategories.h"
#include "gwnotebookmanagment.h"
#include "gwcapturebox.h"
#include "gwprogressbarbox.h"
#include "gwmsgbox.h"

#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"
#include "../gwdevicemanager.h"
#include "../gwsupermount.h"
#include "../gwhelper.h"
#include "../gwcatalogmanager.h"


gint gw_notebook_managment_load_device_list ( GtkWindow *w) {
	GList *devices = NULL, *tmp = NULL;
	GtkCombo *cmb = NULL;
	gint result = -1;
	gchar *selected_device = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		devices = gw_get_drives_list ( devices);

		if ( devices != NULL ) {
			cmb = gw_notebook_managment_get_combo_box_device ( w);

			if ( cmb != NULL ) {
				gtk_combo_set_popdown_strings ( cmb, devices);

				/* Selects default device : mnt/cdrom */
				if ( (selected_device = gw_am_get_settings ( GW_VALUE_APP_DISK_SELECTED)) == NULL ) {
					selected_device = GW_VALUE_APP_DISK_SELECTED_DEFAULT;
				}

				if ( (tmp = g_list_find_custom ( devices, selected_device, (GCompareFunc)strcmp)) == NULL) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : select default device = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, selected_device);
#endif

					tmp = g_list_first ( devices);
				} else {}

				//FIXME Is it necessary to encode to UTF-8 ?
				g_strdup_to_gtk_text ( tmp->data, text_utf8);
				gtk_entry_set_text ( GTK_ENTRY ( cmb->entry), text_utf8);
				g_free ( text_utf8);

				if ( devices != NULL ) {
					g_list_foreach ( devices, (GFunc)g_free, NULL);
					g_list_free ( devices);
				}

				result = 0;
			}
		}
	}

	return result;
}


gboolean gw_notebook_managment_scan_click ( GtkWidget *bt, GtkWindow *window) {
	GtkWindow *msg = NULL;
	gint num_archive = 0, form_num;
	gchar *name = NULL, *disk_name = NULL, *dir = NULL, *num = NULL, *tmp = NULL, *index = NULL, *str_num = NULL, *str_form_num = NULL, *str_form_num_value = NULL;
	struct vfs_stats *vfs = NULL;
	GWDBCategory *category = NULL;
	gboolean has_been_mounted = FALSE;
	gboolean has_been_ejected = FALSE;
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	struct scan_disk_info *scan_disk = NULL;
	GtkWindow *progress_bar = NULL;
	gboolean result = FALSE;
	gfloat disk_size = 0.0;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( window != NULL ) {
		if ( gw_pm_get_current_catalog_plugin ( ) == NULL) {
			gw_msg_box_create ( window, _( "New catalog"), _( "There is no available catalog plugin"));
		} else {
			tree = gw_gui_manager_main_interface_get_tree ( );
			root = gw_gui_manager_main_interface_get_tree_root ( );

			dir = gw_notebook_managment_get_device_dir ( window);
			name = gw_notebook_managment_get_device_name ( window);
			num = gw_notebook_managment_get_device_number ( window);

			vfs = vfs_stats_new ( );

			if ( vfs != NULL ) {
				gw_dm_device_load_to_vfs_stats ( vfs, dir);

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
				vfs_stats_display ( vfs);

				g_print ( "*** GW - %s (%d) :: %s() : checking if device can be mounted\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

				/* Checks if the device can be mounted */
#if defined ( HAVE_MOUNT_SYSTEM)
				if ( (gw_dm_disk_is_mounted_from_vfs_stats ( vfs) == FALSE) && (gw_notebook_managment_get_option_automount ( window) == FALSE) ) {
#else
				if ( (gw_dm_disk_is_mounted_from_vfs_stats ( vfs) == FALSE) ) {
#endif

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : device is not mounted\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

					msg = gw_msg_box_create ( window, _( "Add disk"), _( "The disk hasn't been added : there are not mounted media"));

					result = FALSE;
				} else if ( gw_dm_disk_can_mounted_from_vfs_stats ( vfs) == FALSE ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : cannot mount device\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

					msg = gw_msg_box_create ( window, _( "Add disk"), _( "The disk hasn't been added : cannot mount media"));

					result = FALSE;
				} else {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
					g_print ( "*** GW - %s (%d) :: %s() : device is mounted or can be mounted\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

					/* Gets archive number */
					num_archive = gw_helper_db_disk_get_num_archive ( context, num);

					/* If the "use label disk" is activated AND the filled disk name is empty,
					   must try to get the disk label in order to replace the disk name. */
					if ( ((name == NULL) || ((strlen ( name) == 0) && (strcmp ( name, "") == 0))) && (gw_notebook_managment_get_option_use_disk_label ( window) == TRUE) ) {
						if ( vfs_stats_get_label ( vfs) != NULL ) {
							if ( name != NULL ) {
								g_free ( name);
								name = NULL;
							}

							name = g_strdup ( vfs_stats_get_label ( vfs));
						}
					}

					/* If it must generates the disk name. */
					if ( gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_USE_PATTERN) == 1) {
						/* Saves the new advanced pattern. */
						gw_am_set_settings ( GW_VALUE_APP_DISK_SCAN_PATTERN, gw_notebook_managment_get_device_name ( window));

						/* Generate disk name from advanced pattern :
						   - %% : %
						   - %n : number archive (can use prefix to prefixed by 0 : %.4n give 0001, 0002, 0003, ..., 0091, ...
						   - %l : disk volume label
						   - %t : disk type
						   - %s : serial number
						 */
						index = name;
						while ( (index = strchr ( index, '%')) != NULL ) {
							if ( sscanf ( index, "%%.%dn", &form_num) == 1 ) {
								str_form_num = g_strdup_printf ( "%%0.%dd", form_num);
								str_form_num_value = g_strdup_printf ( str_form_num, num_archive);
								g_free ( str_form_num);
								str_form_num = g_strdup_printf ( "%%.%dn", form_num);
								if ( (tmp = gw_str_replace_str ( name, str_form_num, str_form_num_value)) != NULL ) {
									g_free ( name);
									index = name = tmp;
								} else {
									index = name;
								}

								g_free ( str_form_num);
								g_free ( str_form_num_value);
							} else {
								index++;
							}
						}

						str_num = g_strdup_printf ( "%d", num_archive);
						if  ( (tmp = gw_str_replace_str ( name, "%n", str_num)) != NULL ) {
							g_free ( name);
							name = tmp;
						}

						g_free ( str_num);

						if ( (tmp = gw_str_replace_str ( name, "%l", vfs_stats_get_label ( vfs))) != NULL ) {
							g_free ( name);
							name = tmp;
						}

						if ( (tmp = gw_str_replace_str ( name, "%t", vfs_stats_get_type ( vfs))) != NULL ) {
							g_free ( name);
							name = tmp;
						}

						if ( (tmp = gw_str_replace_str ( name, "%s", vfs_stats_get_serial_number ( vfs))) != NULL ) {
							g_free ( name);
							name = tmp;
						}

						if ( (tmp = gw_str_replace_str ( name, "%%", "%")) != NULL ) {
							g_free ( name);
							name = tmp;
						}
					}

					/* Puts a mapping on the disk name */
					disk_name = gw_helper_db_disk_get_name ( context, name);

					/* Checkes if the catalog is opened */
					if ( root == NULL || context == NULL ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
						g_print ( "*** GW - %s (%d) :: %s() : no catalog is opened\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

						/* If no catalog is opened */
						gw_capture_box_create ( window, _("Add new disk"), _("Enter catalog name"), _("New catalog"), GTK_SIGNAL_FUNC ( gw_capture_box_catalog_name_ok));

						result = FALSE;
					} else {
						/* If a catalog is opened */
						if ( gw_notebook_managment_get_option_category_recursive ( window) == TRUE ) {
							category = gw_combo_box_categories_get_selected_category ( gw_notebook_managment_get_combo_box_categories ( window));
						} else {
							plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
							category = plugin->gw_db_catalog_get_db_category_by_name ( context, _( "none"));
//							category = gw_db_catalog_get_category ( gw_combo_box_categories_get_catalog_info ( gw_notebook_managment_get_combo_box_categories ( window)), _( "none"));
						}

						if ( (disk_name == NULL) || (strlen ( disk_name) == 0) ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
							g_print ( "*** GW - %s (%d) :: %s() : disk name isn't filled\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

							/* If no disk name is filled */
							gw_capture_box_create ( window, _("Add disk"), _("Enter disk name"), (tmp = gw_helper_db_disk_get_name ( context, _("New disk"))), GTK_SIGNAL_FUNC ( gw_capture_box_disk_name_ok));
							g_free ( tmp);

							result = FALSE;
						} else {
							/* Adds the disk with the disk name filled */
							if ( gw_dm_disk_is_mounted_from_vfs_stats ( vfs) || ((has_been_mounted = gw_dm_disk_mount_from_vfs_stats ( vfs)) == TRUE)) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
								g_print ( "*** GW - %s (%d) :: %s() : the disk is going to be added\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

								/* If device is allready mounted or if has been mounted */
								scan_disk = scan_disk_info_new ( );
								scan_disk_info_set_vfs ( scan_disk, vfs);
								scan_disk_info_set_disk_name ( scan_disk, g_strdup ( disk_name));
								scan_disk_info_set_disk_num_archive ( scan_disk, num_archive);
								scan_disk_info_set_disk_category_ref ( scan_disk, gw_db_category_get_ref ( category));
								scan_disk_info_set_explore_tree_structure ( scan_disk, gw_notebook_managment_get_option_explore_tree_structure ( window));
								scan_disk_info_set_explore_archive ( scan_disk, gw_notebook_managment_get_option_explore_archive ( window));
								scan_disk_info_set_make_description ( scan_disk, gw_notebook_managment_get_option_make_description ( window));
								scan_disk_info_set_scan_disk_set_current_statment ( scan_disk, &gw_notebook_managment_set_current_statment);

								disk_size = vfs_stats_get_total_used_space ( vfs);
								progress_bar = gw_progress_bar_box_create ( window, _( "Scanning"), _( "Adding disk is working"), _( "Please wait"), disk_size, gw_notebook_managment_stop_scan_disk, scan_disk);
								gw_gui_manager_main_interface_refresh ( );

								scan_disk_info_set_statment_controler ( scan_disk, progress_bar);

								if ( gw_cm_add_disk ( scan_disk) != -1 ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
									g_print ( "*** GW - %s (%d) :: %s() : the disk has been correctly added\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

									gw_progress_bar_box_set_text ( progress_bar, _( "The disk has been added"));
									gw_progress_bar_box_set_ok_state ( progress_bar);

									result = TRUE;
								} else {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
									g_print ( "*** GW - %s (%d) :: %s() : the disk hasn't been correctly added\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

									gw_progress_bar_box_set_text ( progress_bar, scan_disk_info_get_error_msg ( scan_disk));
									gw_progress_bar_box_set_ok_state ( progress_bar);

									result = FALSE;
								}

								gw_db_category_free ( category);

#if defined ( HAVE_MOUNT_SYSTEM)
								if ( has_been_mounted == TRUE ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
									g_print ( "*** GW - %s (%d) :: %s() : try to umount device\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

									/* Umounts only if device didn't mounted before */
									gw_dm_disk_umount_from_vfs_stats ( vfs);
#endif

									/* Eject CD-Rom if option checked */
									if ( gw_notebook_managment_get_option_eject ( window) == TRUE ) {
										has_been_ejected = gw_drive_eject ( dir);

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
										g_print ( "*** GW - %s (%d) :: %s() : the device has%s been ejected\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, (has_been_ejected?"":"n't"));
#endif
									}
#if defined ( HAVE_MOUNT_SYSTEM)
								}
#endif
								/* Don't free scan_disk because progress_bar_box need it, scan_disk must be freed
								   when progress_bar_box destroyed. */
							} else {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
								g_print ( "*** GW - %s (%d) :: %s() : device cannot be mounted, adding canceled\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

								/* The device cannot be mounted */
								gw_msg_box_create ( window, _( "Add disk"), _( "Mount failed\n"));

								result = FALSE;
							}

							/* Clears all field zone here, because the action "Scan" didn't meet using error as :
							   - no opened catalog
							   - no media selected
							   - no disk name selected or unabble to generate it
							 */
							if ( gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_USE_PATTERN) == 1) {
								gw_notebook_managment_set_device_name ( window, gw_am_get_settings ( GW_VALUE_APP_DISK_SCAN_PATTERN));
							} else {
								gw_notebook_managment_set_device_name ( window, "");
							}

							gw_notebook_managment_set_device_number ( window, "");
						}

						/* Don't clear field zones here because, the user may be didn't fill disk name. */
					}

					/* Don't clear field zones here because, the user may be didn't open catalog. */
					g_free ( disk_name);
				}
			}

			g_free ( dir);
			g_free ( name);
			g_free ( num);

			vfs_stats_free ( vfs);
		}
	}

	return result;
}


gint gw_notebook_managment_select_device ( GtkWidget *entry, GtkWindow *w) {
	GtkLabel *l;
	gchar *text, *msg;
#ifdef HAVE_MOUNT_SYSTEM
	gboolean mounted = FALSE;
#endif
	gboolean disk_in_drive = FALSE;
	struct vfs_stats *vfs = NULL;
	gint result = -1;
	gchar *selected_device = NULL;
	gchar *text_utf8 = NULL;
	GtkCombo *cmb = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (entry != NULL) && (w != NULL) ) {
		cmb = gw_notebook_managment_get_combo_box_device ( w);

		if ( !gw_notebook_managment_get_option_display_info ( w) || !GTK_WIDGET_HAS_FOCUS ( entry)) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : no display device informations\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			l = gw_notebook_managment_get_label_device_info ( w);
			g_strdup_to_gtk_text ( _( "Info : "), text_utf8);
			gtk_label_set_text ( l, text_utf8);
			g_free ( text_utf8);

			l = gw_notebook_managment_get_label_device_type ( w);
			g_strdup_to_gtk_text ( _( "Type : "), text_utf8);
			gtk_label_set_text ( l, text_utf8);
			g_free ( text_utf8);

#ifdef HAVE_MOUNT_SYSTEM
			l = gw_notebook_managment_get_label_device_mounted ( w);
			g_strdup_to_gtk_text ( _( "Mounted : "), text_utf8);
			gtk_label_set_text ( l, text_utf8);
			g_free ( text_utf8);
#endif

			l = gw_notebook_managment_get_label_device_volume ( w);
			g_strdup_to_gtk_text ( _( "Volume : "), text_utf8);
			gtk_label_set_text ( l, text_utf8);
			g_free ( text_utf8);

			l = gw_notebook_managment_get_label_device_serial_number ( w);
			g_strdup_to_gtk_text ( _( "Serial number : "), text_utf8);
			gtk_label_set_text ( l, text_utf8);
			g_free ( text_utf8);

			l = gw_notebook_managment_get_label_device_capacity ( w);
			g_strdup_to_gtk_text ( _( "Capacity : "), text_utf8);
			gtk_label_set_text ( l, text_utf8);
			g_free ( text_utf8);

			l = gw_notebook_managment_get_label_device_free_space ( w);
			g_strdup_to_gtk_text ( _( "Free space : "), text_utf8);
			gtk_label_set_text ( l, text_utf8);
			g_free ( text_utf8);

			result = 0;
		} else {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : device informations are going to be displayed\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			vfs = vfs_stats_new ( );

			if ( vfs != NULL ) {
				g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), selected_device);

#if defined ( HAVE_MOUNT_SYSTEM)
				gw_dm_device_load_to_vfs_stats ( vfs, selected_device);

				/* Checks if device is mounted */
				mounted = gw_dm_disk_is_mounted_from_vfs_stats ( vfs);
				disk_in_drive = gw_dm_disk_can_mounted_from_vfs_stats ( vfs);
#else
				if ( (disk_in_drive = gw_dm_is_disk_in_drive ( selected_device)) == TRUE ) {
					gw_dm_device_load_to_vfs_stats ( vfs, selected_device);
				}
#endif

				text = g_strconcat ( _( "Info : "), disk_in_drive?vfs_stats_get_name ( vfs):_( "no drive"), NULL);
				l = gw_notebook_managment_get_label_device_info ( w);

				g_strdup_to_gtk_text ( text, text_utf8);
				g_free ( text);
				gtk_label_set_text ( l, text_utf8);
				g_free ( text_utf8);

				if ( disk_in_drive ) {
					msg = g_strdup ( vfs_stats_get_type ( vfs));

					if ( msg == NULL ) {
						msg = g_strdup ( _( "unknown"));
					}
				} else {
					msg = g_strdup ( _( "no drive"));
				}

				text = g_strconcat ( _( "Type : "), msg, NULL);
				g_free ( msg);
				l = gw_notebook_managment_get_label_device_type ( w);
				g_strdup_to_gtk_text ( text, text_utf8);
				g_free ( text);
				gtk_label_set_text ( l, text_utf8);
				g_free ( text_utf8);

#ifdef HAVE_MOUNT_SYSTEM
				l = gw_notebook_managment_get_label_device_mounted ( w);
				text = g_strconcat ( _( "Mounted : "), mounted?_( "Yes"):_( "No"), NULL);
				g_strdup_to_gtk_text ( text, text_utf8);
				g_free ( text);
				gtk_label_set_text ( l, text_utf8);
				g_free ( text_utf8);
#endif

				if ( disk_in_drive ) {
					if ( ( msg = g_strdup ( vfs_stats_get_label ( vfs)) ) == NULL ) {
						msg = g_strdup ( _( "No label"));
					}
				} else {
					msg = g_strdup ( _( "no drive"));
				}

				l = gw_notebook_managment_get_label_device_volume ( w);
				text = g_strconcat ( _( "Volume name : "), disk_in_drive?msg:_("no drive"), NULL);
				g_free ( msg);
				g_strdup_to_gtk_text ( text, text_utf8);
				g_free ( text);
				gtk_label_set_text ( l, text_utf8);
				g_free ( text_utf8);

				l = gw_notebook_managment_get_label_device_serial_number ( w);
				text = g_strconcat ( _( "Serial number : "), disk_in_drive?vfs_stats_get_serial_number ( vfs):_( "no drive"), NULL);
				g_strdup_to_gtk_text ( text, text_utf8);
				g_free ( text);
				gtk_label_set_text ( l, text_utf8);
				g_free ( text_utf8);

				l = gw_notebook_managment_get_label_device_capacity ( w);
				text_utf8 = NULL;
				text = g_strconcat ( _( "Capacity : "), disk_in_drive?(text_utf8 = gw_ui64_byte_to_str_format ( vfs_stats_get_total_capacity ( vfs))):_( "no drive"), NULL);
				if ( text_utf8 != NULL ) {
					g_free ( text_utf8);
				}
				g_strdup_to_gtk_text ( text, text_utf8);
				g_free ( text);
				gtk_label_set_text ( l, text_utf8);
				g_free ( text_utf8);

				l = gw_notebook_managment_get_label_device_free_space ( w);
				text_utf8 = NULL;
				text = g_strconcat ( _( "Free space : "), disk_in_drive?(text_utf8 = gw_ui64_byte_to_str_format ( vfs_stats_get_total_free_space ( vfs))):_( "no drive"), NULL);
				if ( text_utf8 != NULL ) {
					g_free ( text_utf8);
				}
				g_strdup_to_gtk_text ( text, text_utf8);
				g_free ( text);
				gtk_label_set_text ( l, text_utf8);
				g_free ( text_utf8);

				result = 0;

				g_free ( selected_device);
			}

			vfs_stats_free ( vfs);
		}
	}

	return result;
}


gint gw_notebook_managment_refresh_info ( GtkWidget *chk, GtkWindow *w) {
	GtkCombo *cmb = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL ) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_DISPLAY_INFO, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
	}

	if ( w != NULL ) {
		if ( (cmb = gw_notebook_managment_get_combo_box_device ( w)) != NULL) {
			result = gw_notebook_managment_select_device ( GTK_WIDGET ( GTK_OBJECT ( GTK_ENTRY ( GTK_COMBO ( cmb)->entry))), w);
		}
	}

	return result;
}


gint gw_notebook_managment_refresh_categories ( GtkWindow *w) {
	GtkHBox *cmb;
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		tree = gw_gui_manager_main_interface_get_tree ( );
		root = gw_gui_manager_main_interface_get_tree_root ( );

		cmb = gw_notebook_managment_get_combo_box_categories ( w);
		gw_combo_box_categories_load ( cmb);

		result = 0;
	}

	return result;
}


gboolean gw_notebook_managment_stop_scan_disk ( GtkObject *obj, gpointer data) {
	struct scan_disk_info *scan_disk = NULL;
	GtkWindow *progress_bar_box = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( data != NULL ) {
		scan_disk = (struct scan_disk_info*)data;
		progress_bar_box = GTK_WINDOW ( scan_disk_info_get_statment_controler ( scan_disk));

		if ( gw_progress_bar_box_get_isok_state ( progress_bar_box)) {
			gtk_widget_destroy ( GTK_WIDGET ( progress_bar_box));

			/* The scan_disk data is freed here and not in the gw_notebook_managment_scan_clik(). */
			scan_disk_info_free ( scan_disk);

			result = TRUE;
		} else if ( gw_progress_bar_box_get_iscancel_state ( progress_bar_box) ) {
			scan_disk_info_set_stop ( scan_disk, TRUE);
			gw_progress_bar_box_set_text ( progress_bar_box, _( "the disk adding is canceled"));
			gw_progress_bar_box_set_ok_state ( progress_bar_box);

			result = TRUE;
		} else {
			result = FALSE;
		}
	}

	return result;
}


gint gw_notebook_managment_set_current_statment ( gpointer w, gfloat current) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		gw_progress_bar_box_add_value ( (GtkWindow*)w, current);
		gw_gui_manager_main_interface_refresh ( );

		result = 0;
	}

	return result;
}



gint gw_capture_box_catalog_name_ok ( GtkWidget *w, gpointer data) {
	gchar *name = NULL;
	GtkWindow *window = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( data != NULL ) {
		name = gw_capture_box_get_text ( data);

		if ( name != NULL && ( strlen ( name) > 0) ) {
			/* If catalog name is filled : update catalog informations */
			window = gw_gui_manager_main_interface_get_main_window ( );
			tree = gw_gui_manager_main_interface_get_tree ( );
			root = gw_gui_manager_main_interface_get_tree_root ( );

			if ( window != NULL ) {
				gw_am_new_catalog ( name);

				/* Destroys the capture box and relaunches the scan */
				gtk_widget_destroy ( data);
				gw_notebook_managment_scan_click ( NULL,  window);

				result = 0;
			}
		} else {
			gw_msg_box_create ( window, _( "Add disk"), _( "Please select a catalog name\n"));

			result = -1;
		}

		if ( name != NULL ) {
			g_free ( name);
		}
	}

	return result;
}


gint gw_capture_box_disk_name_ok ( GtkWidget *w, gpointer data) {
	gchar *disk_name;
	GtkWindow *window = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( data != NULL ) {
		window = gw_gui_manager_main_interface_get_main_window ( );

		if ( window != NULL ) {
			disk_name = gw_capture_box_get_text ( data);
			gw_notebook_managment_set_device_name ( window, disk_name);
			g_free ( disk_name);

			/* Destroys the capture box and relaunches the scan */
			gtk_widget_destroy ( data);
			gw_notebook_managment_scan_click ( NULL, window);

			result = 0;
		}
	}

	return result;
}


gint gw_notebook_managment_option_explore_tree_structure_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_SCAN_EXPLORE_TREE_STRUCTURE, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_managment_option_explore_archive_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_SCAN_EXPLORE_ARCHIVE, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_managment_option_category_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_SCAN_CATEGORY, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_managment_option_description_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_SCAN_DESCRIPTION, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_managment_option_use_disk_label_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_SCAN_LABEL, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_managment_option_use_pattern_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_SCAN_USE_PATTERN, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));

		if ( gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_USE_PATTERN) == 1) {
			gw_notebook_managment_set_device_name ( w, gw_am_get_settings ( GW_VALUE_APP_DISK_SCAN_PATTERN));
		} else {
			gw_notebook_managment_set_device_name ( w, "");
		}

		result = 0;
	}

	return result;
}


gint gw_notebook_managment_option_automount_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_AUTOMOUNT, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_managment_option_eject_click ( GtkToggleButton *chk, GtkWindow *w) {
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL) {
		gw_am_set_settings ( GW_VALUE_APP_DISK_EJECT, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}

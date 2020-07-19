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


#include <string.h> /* strlen */
#include "gwsupport.h"
#include "gwguimanager.h"

#include <gtk/gtk.h>

#include "gui/gwgui.h"
#include "gui/gwreferences.h"

#include "gwapplicationmanager.h"


GtkWindow *window;
GtkCTreeNode *root;


GtkWindow * gw_gui_manager_main_interface_create ( ) {
	GtkWidget *main_window = NULL;
	GtkWidget *vbox = NULL;
	GtkWidget *menu_bar = NULL;
	GtkWidget *tool_bar = NULL;
	GtkWidget *notebook = NULL;
	GtkWidget *status_bar = NULL;
	GtkAccelGroup *accel_group = NULL;
	gint x = -1;
	gint y = -1;
	gint height = -1;
	gint width = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	accel_group = gtk_accel_group_new ( );

	/* Main window */
	main_window = gtk_window_new ( GTK_WINDOW_TOPLEVEL);
	window = GTK_WINDOW ( main_window);
	gtk_window_set_policy ( window, TRUE, TRUE, FALSE);

	/* Checks if have last size and cheks if the window can be displayed in the current screen. */
	if ( (height = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_HEIGHT)) < 0 ) {
		height = GW_VALUE_APP_WIN_HEIGHT_DEFAULT;
	}
	height = MIN ( height, gdk_screen_height ( ));

	if ( (width = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_WIDTH)) < 0 ) {
		width = GW_VALUE_APP_WIN_WIDTH_DEFAULT;
	}
	width = MIN ( width, gdk_screen_width ( ));

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "window size is %dx%d", width, height);
#endif

	/* It is better to use gtk_widget_set_usize() or gtk_window_set_default_size()? */
	gtk_window_set_default_size ( GTK_WINDOW ( main_window), width, height);

	/* Checks if have lasty position and checks if the window can be displayed in the current screen. */
	if ( ((x = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_X)) >= 0) && ((y = gw_am_get_settings_tol ( GW_VALUE_APP_WIN_Y)) >= 0) ) {
		 gtk_widget_set_uposition ( main_window, x, y);
	} else {
		gtk_window_set_position ( GTK_WINDOW ( main_window), GTK_WIN_POS_CENTER);
	}

	/* Checking on position and size doesn't support shifted positions of the windows compared to the screen. */

	gtk_window_set_title ( GTK_WINDOW ( main_window), PROJECT_NAME);
  	gtk_signal_connect ( GTK_OBJECT ( main_window), "delete_event", GTK_SIGNAL_FUNC ( gw_menu_file_exit_click), NULL);
  	gtk_signal_connect ( GTK_OBJECT ( main_window), "destroy", GTK_SIGNAL_FUNC ( gw_menu_file_exit_click), NULL);
	gtk_widget_realize ( main_window);

	/* Vertical box */
	vbox = gtk_vbox_new ( FALSE, 0);
	gtk_widget_ref ( vbox);
	gtk_object_set_data_full ( GTK_OBJECT ( main_window), "VbMainWindow", vbox, (GtkDestroyNotify) gtk_widget_unref);
	gtk_container_add ( GTK_CONTAINER ( main_window), vbox);

	/* Menu bar */
	menu_bar = gw_menu_create ( window, accel_group, vbox);
	gtk_box_pack_start ( GTK_BOX ( vbox), menu_bar, FALSE, FALSE, 0);

	/* Tool bar */
	tool_bar = gw_tool_bar_create_and_add ( window, vbox);

	/* Notebook */
	notebook = gw_notebook_create ( window, vbox);
	gtk_box_pack_start ( GTK_BOX ( vbox), notebook, TRUE, TRUE, 0);

	/* Status bar */
	status_bar = gw_status_bar_create_and_add ( window, vbox);

	gtk_window_add_accel_group ( window, accel_group);

	return window;
}


gint gw_gui_manager_main_interface_set_tree_root ( GtkCTreeNode *node) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	root = node;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	if ( root == NULL ) {
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "root node is NULL");
	}
#endif

	return 0;
}



GtkWindow * gw_gui_manager_main_interface_get_main_window ( void) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	if ( window == NULL ) {
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "main window is NULL");
	}
#endif

	return window;
}


GtkWindow * gw_gui_manager_main_interface_get_progress_bar_box ( void) {
	GtkWindow *progress_bar_box = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	progress_bar_box = gtk_object_get_data ( GTK_OBJECT ( window), GW_REF_PROGRESS_BAR_BOX);

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	if ( progress_bar_box == NULL ) {
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "progress bar box is NULL");
	}
#endif

	return progress_bar_box;
}


GtkCTree * gw_gui_manager_main_interface_get_tree ( void) {
	GtkCTree *tree = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	tree = GTK_CTREE ( gtk_object_get_data ( GTK_OBJECT ( window), GW_REF_TREE));

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	if ( tree == NULL ) {
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "tree is NULL");
	}
#endif

	return tree;
}


GtkCTreeNode * gw_gui_manager_main_interface_get_tree_root ( void) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( root == NULL ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "root node is NULL");
#endif
	}

	return root;
}


void gw_gui_manager_main_interface_refresh ( void) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	while ( gtk_events_pending ( ) ) {
		gtk_main_iteration ( );
	}
}


void gw_gui_manager_main_interface_update_all ( void) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "refreshing categories...");
#endif

	gw_notebook_managment_refresh_categories ( window);

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "updating menus...");
#endif

	gw_gui_manager_main_interface_update_menus ( );

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "updating devices informations....");
#endif

	gw_gui_manager_main_interface_update_notebook_catalog ( );

	gw_gui_manager_main_interface_update_notebook_search ( );

	gw_gui_manager_main_interface_update_notebook_managment ( );

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "all updates and refresh are done!!");
#endif
}


void gw_gui_manager_main_interface_update_menus ( void) {
	gchar *files = NULL;
	gchar **files_list = NULL;
	gint i = 0, size = 0;
	gint max_nb_files = GW_VALUE_APP_RECENT_SIZE_DEFAULT;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (files = gw_am_get_settings ( GW_VALUE_APP_RECENTS_FILES)) != NULL) {
		if ( (max_nb_files = gw_am_get_settings_tol ( GW_VALUE_APP_RECENT_SIZE)) == -1 ) {
			max_nb_files = GW_VALUE_APP_RECENT_SIZE_DEFAULT;
		}

		files_list = g_strsplit ( files, G_SEARCHPATH_SEPARATOR_S, -1);


		/* Gets the number of recents opened files. */
		for ( i = 0; files_list[i] != NULL; i++) { }

		size = i;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Current history size is %d", size);
#endif

		if ( size > 0 ) {
			/* Removes all unwanted items (all over the max size). */
			if ( size > max_nb_files ) {
				for ( i = max_nb_files; files_list[i] != NULL; i++) {
					g_free ( files_list[i]);
					files_list[i] = NULL;
				}
			}

			/* Removes the last item if is empty (for the case where the list is ended by ";"). */
			if ( files_list[size - 1] != NULL ) {
				if ( strlen ( files_list[size - 1]) == 0 ) {
					g_free ( files_list[size - 1]);
					files_list[size - 1] = NULL;
				}
			}
		}

		gw_menu_file_set_recents_files ( window, files_list);
		g_strfreev ( files_list);
	}
}


void gw_gui_manager_main_interface_update_notebook_catalog ( void) {
	GtkCTree *tree = NULL;
	GtkCTreeNode *selection = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (tree = gw_gui_manager_main_interface_get_tree ( )) != NULL ) {
		if ( (GTK_CLIST ( tree)->selection != NULL) && ((selection = GTK_CTREE_NODE ( GTK_CLIST ( tree)->selection->data)) != NULL) ) {
			gtk_ctree_select ( GTK_CTREE ( tree), selection);
		} else {
			gw_notebook_catalog_clist_explorer_set_column_title_disk ( );
		}
	} else {
		gw_notebook_catalog_clist_explorer_set_column_title_disk ( );
	}

	return;
}

void gw_gui_manager_main_interface_update_notebook_search ( void) {
	gint value = 0;
	gchar *str = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	str = gw_am_get_settings ( GW_VALUE_APP_SEARCH_STRING);

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "search string => %s", str);
#endif

	gw_notebook_search_set_search_text ( gw_gui_manager_main_interface_get_main_window ( ), str);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_CASE_SENSITIVE)) == -1 ) {
		value = GW_VALUE_APP_SEARCH_CASE_SENSITIVE_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "use case sensitive => %d", value);
#endif

	gw_notebook_search_set_option_case_sensitive ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_TYPE)) == -1 ) {
		value = GW_VALUE_APP_SEARCH_TYPE_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "search type => %d", value);
#endif

	gw_notebook_search_set_option_search_type ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_FILE_NAME)) == -1 ) {
		value = GW_VALUE_APP_SEARCH_FILE_NAME_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "match with files name => %d", value);
#endif

	gw_notebook_search_set_option_match_file ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_FOLDER_NAME)) == -1 ) {
		value = GW_VALUE_APP_SEARCH_FOLDER_NAME_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "match with folders name => %d", value);
#endif

	gw_notebook_search_set_option_match_folder ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_DISK_NAME)) == -1 ) {
		value = GW_VALUE_APP_SEARCH_DISK_NAME_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "match with disks name => %d", value);
#endif

	gw_notebook_search_set_option_match_disk ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_CATEGORY_NAME)) == -1 ) {
		value = GW_VALUE_APP_SEARCH_CATEGORY_NAME_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "math woth categories name => %d", value);
#endif

	gw_notebook_search_set_option_match_category ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_DESCRIPTION)) == -1 ) {
		value = GW_VALUE_APP_SEARCH_DESCRIPTION_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "use case sensitive => %d", value);
#endif

	gw_notebook_search_set_option_match_description ( gw_gui_manager_main_interface_get_main_window ( ), value);


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "updating the search column properties");
#endif

	gw_notebook_search_clist_search_set_column_title ( );
}


void gw_gui_manager_main_interface_update_notebook_managment ( void) {
	gint value = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_DISPLAY_INFO)) == -1 ) {
		value = GW_VALUE_APP_DISK_DISPLAY_INFO_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "display info => %d", value);
#endif

	gw_notebook_managment_set_option_display_info ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_EXPLORE_TREE_STRUCTURE)) == -1 ) {
		value = GW_VALUE_APP_DISK_SCAN_EXPLORE_TREE_STRUCTURE_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "explore tree structure => %d", value);
#endif

	gw_notebook_managment_set_option_explore_tree_structure ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_EXPLORE_ARCHIVE)) == -1 ) {
		value = GW_VALUE_APP_DISK_SCAN_EXPLORE_ARCHIVE_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "explore archive => %d", value);
#endif

	gw_notebook_managment_set_option_explore_archive ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_CATEGORY)) ==  -1) {
		value = GW_VALUE_APP_DISK_SCAN_CATEGORY_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "category recursive => %d", value);
#endif

	gw_notebook_managment_set_option_category_recursive ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_DESCRIPTION)) == -1 ) {
		value = GW_VALUE_APP_DISK_SCAN_DESCRIPTION_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "make description => %d", value);
#endif

	gw_notebook_managment_set_option_make_description ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_USE_PATTERN)) == -1 ) {
		value = GW_VALUE_APP_DISK_SCAN_USE_PATTERN_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "use pattern => %d", value);
#endif

	gw_notebook_managment_set_option_use_pattern ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_SCAN_LABEL)) == -1 ) {
		value = GW_VALUE_APP_DISK_SCAN_LABEL_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "use volume name => %d", value);
#endif

	gw_notebook_managment_set_option_use_disk_label ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_AUTOMOUNT)) == -1 ) {
		value = GW_VALUE_APP_DISK_AUTOMOUNT_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "automount => %d", value);
#endif

	gw_notebook_managment_set_option_automount ( gw_gui_manager_main_interface_get_main_window ( ), value);

	if ( (value = gw_am_get_settings_tol ( GW_VALUE_APP_DISK_EJECT)) == -1 ) {
		value = GW_VALUE_APP_DISK_EJECT_DEFAULT;
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "eject => %d", value);
#endif

	gw_notebook_managment_set_option_eject ( gw_gui_manager_main_interface_get_main_window ( ), value);
}


void gw_gui_manager_exit ( void) {
	GtkWindow *window = NULL;
	gchar *selected_device = NULL;
	gint x, y, width, height;
	gint position = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	window = gw_gui_manager_main_interface_get_main_window ( );

	if ( window != NULL ) {
		/* Saves the horizontal pane position which is in the catalog tabbed pane. */
		if ( (position = gw_notebook_catalog_get_hpan_position ( window)) != -1 ) {
			gw_am_set_settings ( GW_VALUE_APP_EXPLORER_HPAN_POSITION, g_strdup_printf ( "%d", position));
		}

		/* Saves the last selected device. */
		selected_device = gw_notebook_managment_get_device_dir ( window);

		if ( selected_device != NULL ) {
			gw_am_set_settings ( GW_VALUE_APP_DISK_SELECTED, selected_device);
		}

		/* Saves the main window size and position. */
		if ( gw_am_get_settings_tol ( GW_VALUE_APP_GUI_AUTOSAVE) == 1 ) {
			gdk_window_get_position ( GTK_WIDGET ( window)->window, &x, &y);
			gdk_window_get_size ( GTK_WIDGET ( window)->window, &width, &height);
			gw_am_set_settings ( GW_VALUE_APP_WIN_X, g_strdup_printf ( "%d", x));
			gw_am_set_settings ( GW_VALUE_APP_WIN_Y, g_strdup_printf ( "%d", y));
			gw_am_set_settings ( GW_VALUE_APP_WIN_WIDTH, g_strdup_printf ( "%d", width));
			gw_am_set_settings ( GW_VALUE_APP_WIN_HEIGHT, g_strdup_printf ( "%d", height));
		}

		/* Destroyes the main window. */
		gtk_widget_destroy ( GTK_WIDGET ( window));
	}
}

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
#include "gwmenufilecallback.h"

#include <string.h> /* strcmp strlen */

#include "data/gwdata.h"
#include "res/gwres.h"

#include "gwpropertiesbox.h"
#include "gwstatusbar.h"
#include "gwcapturebox.h"
#include "gwwindowboxmail.h"
#include "gwmsgbox.h"
#include "gwdialogbox.h"
#include "gwmsgbox.h"
#include "gwfileselectionbox.h"
#include "gwnotebookmanagmentcallback.h"
#include "gwnotebookcatalog.h"

#include "../gwhelper.h"
#include "../gwcatalogmanager.h"
#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"


gboolean gw_menu_file_new_click ( GtkMenuItem *mi, GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gchar *msg = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "creating new catalog ==> memory status : ");
	g_mem_profile ( );
#endif

	if ( gw_pm_get_current_catalog_plugin ( ) == NULL) {
		gw_msg_box_create ( w, _( "New catalog"), _( "There is no available catalog plugin"));
	} else if ( w != NULL ) {
		/* Checks if a catalog has been modified */
		if ( gw_helper_db_catalog_is_open_and_modified ( ) ) {
			/* If has been modified, ask to save it before create new catalog */
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);
			msg = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_helper_db_catalog_get_full_name ( catalog), "\n", NULL);
			gw_dialog_box_create ( w, _( "New file"), msg, GTK_SIGNAL_FUNC ( gw_menu_file_new_save_file_ok), GTK_SIGNAL_FUNC ( gw_menu_file_new_save_file_no), NULL, NULL);
			g_free ( msg);
			gw_db_catalog_free ( catalog);
		} else {
			/* Else ask the new catalog name */
			gw_capture_box_create ( w, _( "New catalog"), _( "Enter catalog name"), "", GTK_SIGNAL_FUNC ( gw_menu_file_new_file_ok));
		}
	}

	return TRUE;
}


gboolean gw_menu_file_open_click ( GtkMenuItem *mi, GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gchar *msg = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( gw_pm_get_current_catalog_plugin ( ) == NULL) {
		gw_msg_box_create ( w, _( "Open catalog"), _( "There is no available catalog plugin"));
	} else if ( w != NULL ) {
		/* Checks if a catalog has been modified */
		if ( gw_helper_db_catalog_is_open_and_modified ( ) ) {
			/* If has been modified, ask to save it before open an existing catalog */
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);
			msg = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_helper_db_catalog_get_full_name ( catalog), "\n", NULL);
			gw_dialog_box_create ( w, _( "Open file"), msg, GTK_SIGNAL_FUNC ( gw_menu_file_open_save_file_ok), GTK_SIGNAL_FUNC ( gw_menu_file_open_save_file_no), NULL, NULL);
			g_free ( msg);
			gw_db_catalog_free ( catalog);
		} else {
			/* Else opens file selection box */
			gw_file_selection_box_create ( _( "Open catalog"), NULL, (GtkSignalFunc)gw_menu_file_open_file_ok, (GtkSignalFunc)gw_menu_file_open_file_cancel);
		}
	}

	return TRUE;
}


gboolean gw_menu_file_close_click ( GtkMenuItem *mi, GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gchar *msg = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "closing new catalog ==> memory status : ");
	g_mem_profile ( );
#endif

	/* Checks if a catalog has been modified */
	if ( gw_helper_db_catalog_is_open_and_modified ( ) ) {
		/* If has been modified, ask to save it before close the current catalog */
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);
		msg = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_helper_db_catalog_get_full_name ( catalog), "\n", NULL);
		gw_dialog_box_create ( w, _( "Close file"), msg, GTK_SIGNAL_FUNC ( gw_menu_file_close_save_file_ok), GTK_SIGNAL_FUNC ( gw_menu_file_close_save_file_no), NULL, NULL);
		g_free ( msg);
		gw_db_catalog_free ( catalog);
	} else if ( gw_helper_db_catalog_is_open ( ) ) {
		/* Else closes it */
		gw_am_close_catalog ( FALSE);

		result = TRUE;
	} else {
		gw_msg_box_create ( w, _( "Close file"), _( "No catalog is opened"));
	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "new catalog closed ==> memory status : ");
	g_mem_profile ( );
#endif

	return result;
}


gboolean gw_menu_file_send_mail_click ( GtkMenuItem *mi, GtkWindow *w) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;
	gchar *msg = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		/* Check if the mail options if configured. */
		if ( gw_am_can_send_mail ( ) ) {
			/* Checks if a catalog has been modified */
			if ( gw_helper_db_catalog_is_open_and_modified ( ) ) {
				/* If has been modified, ask to save it before send the current catalog by mail */
				plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
				catalog = plugin->gw_db_catalog_get_db_catalog ( context);
				msg = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_helper_db_catalog_get_full_name ( catalog), "\n", NULL);
				gw_dialog_box_create ( w, _( "Send file by mail"), msg, GTK_SIGNAL_FUNC ( gw_menu_file_send_mail_save_file_ok), GTK_SIGNAL_FUNC ( gw_menu_file_send_mail_save_file_no), NULL, NULL);
				g_free ( msg);
				gw_db_catalog_free ( catalog);
			} else if ( gw_helper_db_catalog_is_open ( ) ) {
				/* Else send it by mail */
				plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
				catalog = plugin->gw_db_catalog_get_db_catalog ( context);
				gw_mail_window_box_create ( w, gw_helper_db_catalog_get_full_name ( catalog));
				gw_db_catalog_free ( catalog);
			} else {
				gw_msg_box_create ( w, _( "Send file by mail"), _( "No catalog is opened"));
			}

			result = TRUE;
		} else {
			gw_msg_box_create ( w, _( "Send file by mail"), _( "Please configure mail options in the settings in order to send mails."));
		}
	}

	return result;
}


gboolean gw_menu_file_send_mail_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL) {
		/* Destroys the dialog box. */
		gtk_widget_destroy ( GTK_WIDGET ( dg));

		/* Checks if a catalog context is open */
		if ( context != NULL) {
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);

			/* Checks if it's a new catalog (in this case his full name is "./[catalog_full_name]"). */
			if ( gw_helper_db_catalog_is_new ( catalog)) {
				/* If it's a new catalog, asks a file name. */
				gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_send_mail_saveas_file_selection_ok, NULL);
			} else {
				/* Else save it directly and send it by mail. */
				gw_menu_file_save_click ( NULL, NULL);

				/* Shows the mail window box. */
				gw_mail_window_box_create ( window, gw_helper_db_catalog_get_full_name ( catalog));
			}

			gw_db_catalog_free ( catalog);

			result = TRUE;
		} else {
		}
	}

	return result;
}


gboolean gw_menu_file_send_mail_save_file_no ( GtkWidget *bt, GtkWindow *dg) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL ) {
		/* Destroys the dialog box. */
		gtk_widget_destroy ( GTK_WIDGET ( dg));

		/* Checks if a catalog context is open */
		if ( context != NULL) {
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);

			if ( gw_helper_db_catalog_is_new ( catalog)) {
				gw_msg_box_create ( window, _( "Send file by mail"), _( "The current catalog is never be saved, cannot send it"));
			} else {
				/* Shows the mail window box. */
				gw_mail_window_box_create ( window, gw_db_catalog_get_db_name ( catalog));
			}

			gw_db_catalog_free ( catalog);

			result = TRUE;
		} else {
		}
	}

	return result;
}


gboolean gw_menu_file_send_mail_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL ) {
		g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8);

		if ( (strlen ( text_utf8) > 0 ) && (strcmp ( text_utf8, "") != 0) ) {
//			/* Updates informations of opened catalog. */
//			catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));

			/* Updates informations of opened catalog. */
			switch ( gw_am_save_catalog ( gtk_file_selection_get_filename ( fs))) {
				case 0:
							break;

				case GWECATNOMODIFIED:
							break;

				case GWECATNOFILENAME:
							break;

				case GWECATCANNOTSAVE:
							break;

				default:
							break;
			}

			/* Closes the file selection box. */
			gtk_widget_destroy ( GTK_WIDGET ( fs));

			/* Shows the mail window box. */
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);
			gw_mail_window_box_create ( window, gw_db_catalog_get_db_name ( catalog));
			gw_db_catalog_free ( catalog);
		}

		g_free ( text_utf8);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_properties_click ( GtkMenuItem *mi, GtkWindow *w) {
	GtkCTree *tree = gw_gui_manager_main_interface_get_tree ( );
	GtkCTreeNode *root = gw_gui_manager_main_interface_get_tree_root ( );
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		tree = gw_gui_manager_main_interface_get_tree ( );
		root = gw_gui_manager_main_interface_get_tree_root ( );

		/* Checks if a catalog is opened */
		//TODO use helper functions
		if ( gw_am_get_current_catalog_context ( ) != NULL) {
			gw_properties_box_create_catalog ( mi, w, tree, root);

			return TRUE;
		} else {
			gw_msg_box_create ( w, _( "Catalog properties"), _( "No catalog is opened"));
		}
	}

	return result;
}


gboolean gw_menu_file_save_click ( GtkMenuItem *mi, GtkWindow *w) {
	gboolean result = FALSE;
	GWDBCatalog *catalog = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

//TODO use helper functions
	if ( gw_am_get_current_catalog_context ( ) != NULL) {
		switch ( gw_am_save_catalog ( NULL)) {
			case 0:			result = TRUE;

						break;

			case GWECATNOMODIFIED:
						break;

			case GWECATNOFILENAME:	//TODO should we set the catalog title as catalog file name by default in the file selection box??
						catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));
						gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_saveas_file_selection_ok, NULL);
						gw_db_catalog_free ( catalog);

						break;

			case GWECATCANNOTSAVE:
						break;

			default:
						break;
		}
	} else {
			gw_msg_box_create ( w, _( "Save catalog"), _( "No catalog is opened"));
	}

	return result;
}


gboolean gw_menu_file_saveas_click ( GtkMenuItem *mi, GtkWindow *w) {
	GWDBCatalog *catalog = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Checks if a catalog is opened */
//TODO use helper functions
	if ( gw_am_get_current_catalog_context ( ) != NULL) {
		catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));
		gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_saveas_file_selection_ok, NULL);
		gw_db_catalog_free ( catalog);
	} else {
		gw_msg_box_create ( w, _( "Save as catalog"), _( "No catalog is opened"));
	}

	return TRUE;
}


gboolean gw_menu_file_exit_click ( GtkMenuItem *mi, GtkWindow *w) {
	GWDBCatalog *catalog = NULL;
//	GtkCTree *tree = NULL;
//	GtkCTreeNode *root = NULL;
	GtkWindow *window = NULL;
	gchar *msg[2];


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL ) {
		window = gw_gui_manager_main_interface_get_main_window ( );

		/* Checks if a catalog has been modified */
		if ( gw_am_get_current_catalog_context ( ) != NULL ) {
			catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));
			if ( catalog!=NULL && gw_db_catalog_is_modified ( catalog) ) {
				/* If has been modified, ask to save it before exit program */
				msg[0] = g_strconcat ( _( "Quit "), PROJECT_NAME, NULL);
	//			if ( gw_db_catalog_get_db_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_db_name ( catalog))>0 ) {
	//				msg[1] = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_db_catalog_get_db_name ( catalog), "\n", NULL);
	//			} else {
	//				msg[1] = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_db_catalog_get_name ( catalog), "\n", NULL);
	//			}
					msg[1] = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_helper_db_catalog_get_full_name ( catalog), "\n", NULL);
	
				gw_dialog_box_create ( window, msg[0], msg[1], GTK_SIGNAL_FUNC ( gw_menu_file_exit_save_file_ok), GTK_SIGNAL_FUNC ( gw_menu_file_exit_save_file_no), NULL, NULL);
				g_free ( msg[0]);
				g_free ( msg[1]);
			} else {
				/* Else exit program */
				gw_menu_file_exit ( );
			}
		} else {
			/* Else exit program */
			gw_menu_file_exit ( );
		}
	}

	return TRUE;
}


gboolean gw_menu_file_open_file_ok ( GtkObject *ob, GtkFileSelection *fs) {
	GWDBContext *context = gw_am_get_current_catalog_context ( );
//	GWDBCatalog *catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL ) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : beginning...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8);

		/* Checkes if a catalog has been selected */
		if ( (strlen ( text_utf8) > 0) && (strcmp ( text_utf8, "") != 0) ) {
			gtk_widget_hide ( GTK_WIDGET ( fs));

//TODO use helper functions
			if ( context != NULL ) {
				/* If a catalog is opened, don't save it. Destroys the tree and remove the window title. */
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : a catalog is already opened\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

//				gw_notebook_catalog_ctree_destroy_all ( );
				gw_am_close_catalog ( FALSE);
			}

			/* Loads the catalog. */
			gw_am_load_catalog ( gtk_file_selection_get_filename ( fs));

			gtk_widget_destroy ( GTK_WIDGET ( fs));
		}

		g_free ( text_utf8);
	}

	return FALSE;
}


gboolean gw_menu_file_open_file_cancel ( GtkObject *ob, GtkFileSelection *fs) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL) {
		gtk_widget_destroy ( GTK_WIDGET ( fs));

		return TRUE;
	}

	return FALSE;
}


gboolean gw_menu_file_new_file_ok ( GtkWidget *bt, GtkWindow *w) {
	gchar *name = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	name = gw_capture_box_get_text ( w);

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : catalog name = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, name);
#endif

	if ( name != NULL && (strlen ( name) > 0) ) {
		/* Checks if a catalog is allready opened */
		if ( gw_am_get_current_catalog_context ( ) != NULL ) {
			/* If is opened, closes it */
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : a catalog is already opened\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			gw_am_close_catalog ( FALSE);
		} else {
		}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : initializes the catalog data structure\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gw_am_new_catalog ( name);

		gtk_widget_destroy ( GTK_WIDGET ( w));
	}

	if ( name != NULL) {
		g_free ( name);
	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "new catalog created ==> memory status : ");
	g_mem_profile ( );
#endif

	return TRUE;
}


gboolean gw_menu_file_new_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWDBCatalog *catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	gtk_widget_destroy ( GTK_WIDGET ( dg));

	/* Checks if is a new catalog (in this case his full name is "./[catalog_full_name]"). */
	if ( gw_helper_db_catalog_is_new ( catalog)) {
//	if ( gw_db_catalog_get_db_name ( catalog)==NULL || strlen ( gw_db_catalog_get_db_name ( catalog))==0 ) {
		/* If it's a new catalog, asks a file name. */
//		gw_file_selection_box_create ( _( "Save as catalog"), gw_db_catalog_get_name ( catalog), (GtkSignalFunc)gw_menu_file_new_saveas_file_selection_ok, NULL);
		gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_new_saveas_file_selection_ok, NULL);
	} else {
		/* Else save it directly and displays a fill box of new catalog */
		gw_menu_file_save_click ( NULL, NULL);
		gw_capture_box_create ( window, _( "New catalog"), _( "Enter catalog name"), "", GTK_SIGNAL_FUNC ( gw_menu_file_new_file_ok));
	}

	return TRUE;
}


gboolean gw_menu_file_new_save_file_no ( GtkWidget *bt, GtkWindow *dg) {
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL ) {
		gtk_widget_destroy ( GTK_WIDGET ( dg));
		gw_capture_box_create ( window, _("New catalog"), _("Enter catalog name"), "", GTK_SIGNAL_FUNC ( gw_menu_file_new_file_ok));

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_new_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	GtkWindow *window = NULL;
	gchar *text_utf8[2];
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8[0]);

	if ( (strlen ( text_utf8[0]) > 0) && (strcmp ( text_utf8[0], "") != 0) ) {
		/* Saves the catalog. */
		g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), text_utf8[1]);
		switch ( gw_am_save_catalog ( text_utf8[1])) {
			case 0:
						break;

			case GWECATNOMODIFIED:
						break;

			case GWECATNOFILENAME:
						break;

			case GWECATCANNOTSAVE:
						break;

			default:
						break;
		}

		g_free ( text_utf8[1]);

		/* Close the file selection box and displays a new fill box of new catalog. */
		gtk_widget_destroy ( GTK_WIDGET ( fs));
		window = gw_gui_manager_main_interface_get_main_window ( );
		gw_capture_box_create ( window, _("New catalog"), _("Enter catalog name"), "", GTK_SIGNAL_FUNC ( gw_menu_file_new_file_ok));

		result = TRUE;
	}

	g_free ( text_utf8[0]);

	return result;
}


gboolean gw_menu_file_open_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWDBCatalog *catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	gtk_widget_destroy ( GTK_WIDGET ( dg));

	/* Checks if it's a new catalog (in this case his full name is ".[/catalog_full_name]"). */
	if ( gw_helper_db_catalog_is_new ( catalog)) {
//	if ( gw_db_catalog_get_db_name ( catalog)==NULL || strlen ( gw_db_catalog_get_db_name ( catalog))==0 ) {
		/* If it's a new catalog, asks file name. */
//		gw_file_selection_box_create ( _( "Save as catalog"), gw_db_catalog_get_name ( catalog), (GtkSignalFunc)gw_menu_file_open_saveas_file_selection_ok, NULL);
		gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_open_saveas_file_selection_ok, NULL);
	} else {
		/* Else save it directly and displays a file selection box to select the catalog to open. */
		gw_menu_file_save_click ( NULL, NULL);

		gw_file_selection_box_create ( _("Open catalog"), NULL, (GtkSignalFunc)gw_menu_file_open_file_ok, (GtkSignalFunc)gw_menu_file_open_file_cancel);
	}

	return TRUE;
}


gboolean gw_menu_file_open_save_file_no ( GtkWidget *bt, GtkWindow *dg) {
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL ) {
		gtk_widget_destroy ( GTK_WIDGET ( dg));
		gw_file_selection_box_create ( _("Open catalog"), NULL, (GtkSignalFunc)gw_menu_file_open_file_ok, (GtkSignalFunc)gw_menu_file_open_file_cancel);

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_open_recents_files_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gpointer file_index = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	file_index = gw_dialog_box_get_user_data ( dg);
	gtk_widget_destroy ( GTK_WIDGET ( dg));

	if ( context != NULL ) {
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);

		/* Checks if it's a new catalog (in this case his full name is ".[/catalog_full_name]"). */
		if ( gw_helper_db_catalog_is_new ( catalog)) {
			gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_open_recents_files_saveas_file_selection_ok, file_index);
		} else {
			/* Else save it directly and displays a file selection box to select the catalog to open. */
			gw_menu_file_save_click ( NULL, NULL);

			/* Warning use a gint value instead of a gpointer value!! */
			result = gw_am_load_catalog_from_recents_files ( GPOINTER_TO_UINT ( file_index));
		}

		gw_db_catalog_free ( catalog);
	} else {
		/* Warning use a gint value instead of a gpointer value!! */
		result = gw_am_load_catalog_from_recents_files ( GPOINTER_TO_UINT ( file_index));
	}

	return result;
}


gboolean gw_menu_file_open_recents_files_save_file_no ( GtkWidget *bt, GtkWindow *dg) {
	gboolean result = FALSE;
	gpointer file_index = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL ) {
		file_index = gw_dialog_box_get_user_data ( dg);
		gtk_widget_destroy ( GTK_WIDGET ( dg));
		gw_am_close_catalog ( FALSE);

		/* Warning use a gint value instead of a gpointer value!! */
		result = gw_am_load_catalog_from_recents_files ( GPOINTER_TO_UINT ( file_index));

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_open_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	gboolean result = FALSE;
	gchar *text_utf8[2];


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL ) {
		g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8[0]);

		if ( (strlen ( text_utf8[0]) > 0) && (strcmp ( text_utf8[0], "") != 0) ) {
			/* Save the catalog. */
			g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), text_utf8[1]);
			switch ( gw_am_save_catalog ( text_utf8[1])) {
				case 0:		result = TRUE;

							break;

				case GWECATNOMODIFIED:
							break;

				case GWECATNOFILENAME:
							break;

				case GWECATCANNOTSAVE:
							break;

				default:
							break;
			}

			g_free ( text_utf8[1]);

			/* Closes the file selection box and displays a new fill box of new catalog. */
			gtk_widget_destroy ( GTK_WIDGET ( fs));
			gw_file_selection_box_create ( _( "Open catalog"), NULL, (GtkSignalFunc)gw_menu_file_open_file_ok, (GtkSignalFunc)gw_menu_file_open_file_cancel);
		}

		g_free ( text_utf8[0]);
	}

	return result;
}


gboolean gw_menu_file_open_recents_files_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	gboolean result = FALSE;
	gchar *text_utf8[2];
	gpointer file_index = NULL;
	gchar *catalog_path_name = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL ) {
		g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8[0]);

		/* Gets the real file name in the recents opened catalogs list, because after saving the current
		   opened catalog, the wanted catalog in the recents list (may) will not have the same index. */
		file_index = gw_file_selection_box_get_user_data ( GTK_WINDOW ( fs));

		/* Warning use a gint value instead of a gpointer value!! */
		catalog_path_name = gw_am_get_catalog_path_name_from_recents_files ( GPOINTER_TO_UINT ( file_index));

		if ( (strlen ( text_utf8[0]) > 0) && (strcmp ( text_utf8[0], "") != 0) ) {
			/* Save the catalog. */
			g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), text_utf8[1]);
			switch ( gw_am_save_catalog ( text_utf8[1])) {
				case 0:		result = TRUE;

							break;

				case GWECATNOMODIFIED:
							break;

				case GWECATNOFILENAME:
							break;

				case GWECATCANNOTSAVE:
							break;

				default:
							break;
			}

			g_free ( text_utf8[1]);

			/* Closes the file selection box and displays a new fill box of new catalog. */
			gtk_widget_destroy ( GTK_WIDGET ( fs));

			result = gw_am_load_catalog ( catalog_path_name);
		}

		g_free ( text_utf8[0]);

		if ( catalog_path_name != NULL ) {
			g_free ( catalog_path_name);
		}
	}

	return result;
}


gboolean gw_menu_file_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
//	GtkCTree *tree = NULL;
//	GtkCTreeNode *root = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	gtk_widget_destroy ( GTK_WIDGET ( dg));

	/* Checks if it's a new catalog (in this case his full name is "./[catalog_full_name]"). */
	if ( context != NULL ) {
		catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_catalog_get_db_catalog ( context);
	if ( gw_helper_db_catalog_is_new ( catalog)) {
//	if ( gw_db_catalog_get_db_name ( catalog)==NULL || strlen ( gw_db_catalog_get_db_name ( catalog))==0 ) {
		/* If it's a new catalog, asks un file name. */
//		gw_file_selection_box_create ( _( "Save as catalog"), gw_db_catalog_get_name ( catalog), (GtkSignalFunc)gw_menu_file_saveas_file_selection_ok, NULL);
		gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_saveas_file_selection_ok, NULL);
	} else {
		/* Else save it directly. */
		gw_menu_file_save_click ( NULL, NULL);
	}
	} else {
	}

	result = TRUE;

	return result;
}


gboolean gw_menu_file_save_file_no ( GtkWidget *bt, GtkWindow *dg) {
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL ) {
		gtk_widget_destroy ( GTK_WIDGET ( dg));

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	gboolean result = FALSE;
	gchar *text_utf8[2];


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8[0]);
g_print("save as %s\n",text_utf8[0]);

	if ( (strlen ( text_utf8[0]) > 0) && (strcmp ( text_utf8[0], "") != 0) ) {
		/* Save the opened catalog. */
		g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), text_utf8[1]);
		switch ( gw_am_save_catalog ( text_utf8[1])) {
			case 0:		result = TRUE;

						break;

			case GWECATNOMODIFIED:
						break;

			case GWECATNOFILENAME:
						gw_file_selection_box_create ( _( "Save as catalog"), gw_db_catalog_get_name ( ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ))), (GtkSignalFunc)gw_menu_file_saveas_file_selection_ok, NULL);

						break;

			case GWECATCANNOTSAVE:
						break;

			default:
						break;
		}

		g_free ( text_utf8[1]);

		/* Closes the file selection box. */
		gtk_widget_destroy ( GTK_WIDGET ( fs));
	}

	g_free ( text_utf8[0]);

	return result;
}


gboolean gw_menu_file_close_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	gtk_widget_destroy ( GTK_WIDGET ( dg));

	if ( context != NULL ) {
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);

		/* Checks if it's a new catalog (in this case his full name is "./[catalog_full_name]"). */
		if ( gw_helper_db_catalog_is_new ( catalog)) {
			/* If it's a new catalog, asks a file name. */
			gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_close_saveas_file_selection_ok, NULL);
		} else {
			/* Else save it directly and close it. */
			gw_menu_file_save_click ( NULL, NULL);

			gw_am_close_catalog ( FALSE);
		}

		gw_db_catalog_free ( catalog);

		result = TRUE;
	} else {
	}

	return result;
}


gboolean gw_menu_file_close_save_file_no ( GtkWidget *bt, GtkWindow *dg) {
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL ) {
		gw_am_close_catalog ( FALSE);
		gtk_widget_destroy ( GTK_WIDGET ( dg));

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_close_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	GWDBCatalog *catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));
	gboolean result = FALSE;
	gchar *text_utf8[2];


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8[0]);

	if ( (strlen ( text_utf8[0]) > 0) && (strcmp ( text_utf8[0], "") != 0) ) {
		/* Updates informations of opened catalog. */
//TODO use helper functions
		if ( catalog != NULL ) {
			g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), text_utf8[1]);
			switch ( gw_am_save_catalog ( text_utf8[1]) ) {
				case 0:			result = TRUE;

							break;

				case GWECATNOMODIFIED:
							break;

				case GWECATNOFILENAME:
							break;

				case GWECATCANNOTSAVE:
							break;

				default:
							break;
			}

			g_free ( text_utf8[1]);
		} else {}

		/* Closes the file selection box and closes the catalog. */
		gtk_widget_destroy ( GTK_WIDGET ( fs));
		gw_am_close_catalog ( FALSE);
	}

	g_free ( text_utf8[0]);

	return result;
}


gboolean gw_menu_file_exit_save_file_ok ( GtkWidget *bt, GtkWindow *dg) {
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	gtk_widget_destroy ( GTK_WIDGET ( dg));

	/* Checks if it's a new catalog (in this case his full name is "./[catalog_full_name]"). */
	if ( gw_helper_db_catalog_is_new ( catalog)) {
//	if ( gw_db_catalog_get_db_name ( catalog)==NULL || strlen ( gw_db_catalog_get_db_name ( catalog))==0 ) {
		/* If it's a new catalog, asks a file name. */
//		gw_file_selection_box_create ( _( "Save as catalog"), gw_db_catalog_get_name ( catalog), (GtkSignalFunc)gw_menu_file_exit_saveas_file_selection_ok, NULL);
		gw_file_selection_box_create ( _( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_exit_saveas_file_selection_ok, NULL);
	} else {
		/* Else save the catalog directly and exit program. */
		gw_menu_file_save_click ( NULL, NULL);
		gw_menu_file_exit ( );
	}

	result = TRUE;

	return result;
}


gboolean gw_menu_file_exit_save_file_no ( GtkWidget *bt, GtkWindow *dg) {
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( dg != NULL ) {
		gtk_widget_destroy ( GTK_WIDGET ( dg));
		gw_menu_file_exit ( );

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_exit_saveas_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	gboolean result = FALSE;
	gchar *text_utf8[2];


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL ) {
		g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), text_utf8[0]);

		if ( (strlen ( text_utf8[0]) > 0) && (strcmp ( text_utf8[0], "") != 0) ) {
			/* Saves the catalog. */
			g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), text_utf8[1]);
			switch ( gw_am_save_catalog ( text_utf8[1]) ) {
				case 0:		result = TRUE;
							break;

				case GWECATNOMODIFIED:
							break;

				case GWECATNOFILENAME:
							break;

				case GWECATCANNOTSAVE:
							break;

				default:
							break;
			}

			g_free ( text_utf8[1]);

			/* Exits the program. */
			gtk_widget_destroy ( GTK_WIDGET ( fs));
			gw_menu_file_exit ( );

			result = TRUE;
		}

		g_free ( text_utf8[0]);
	}

	return result;
}


void gw_menu_file_exit ( void) {
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Exit main program */
	gw_am_close_catalog ( FALSE);
	gw_am_exit ( );
	gtk_main_quit ( );
}


gboolean gw_menu_file_import_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gboolean result = FALSE;
	gchar *short_db_name = NULL, *db_name = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), short_db_name);

	if ( short_db_name != NULL && strlen ( short_db_name) > 0 ) {
		/* Import the opened catalog */
		g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), db_name);

		if ( gw_am_import_catalog_from ( gw_pm_get_current_catalog_plugin ( ), gw_pm_get_selected_import_catalog_plugin ( ), db_name, short_db_name) != -1) {
			gw_msg_box_create ( window, _( "Import catalog from"), _( "Catalog imported"));
		} else {
			gw_msg_box_create ( window, _( "Import catalog from"), _( "Catalog is not imported"));
		}

		if ( db_name != NULL) g_free ( db_name);

		/* Closes the file selection box. */
		gtk_widget_destroy ( GTK_WIDGET ( fs));

		/* Clears the selected catalog plugin to import */
		gw_pm_set_selected_import_catalog_plugin ( NULL);

		result = TRUE;
	} else {}

	if ( short_db_name != NULL) g_free ( short_db_name);

	return result;
}


gboolean gw_menu_file_import_item_click ( GtkMenuItem *m, gpointer data) {
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gchar *plugin_name = data;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	gboolean result = FALSE;


	if ( context == NULL) {
		gw_pm_set_selected_import_catalog_plugin ( gw_pm_get_catalog_plugin ( plugin_name));

		gw_file_selection_box_create ( _( "Import catalog from"), NULL, (GtkSignalFunc)gw_menu_file_import_file_selection_ok, NULL);

		result = TRUE;
	} else {
		gw_msg_box_create ( window, _( "Import catalog from"), _( "A catalog is already opened"));
	}

	return result;
}


gboolean gw_menu_file_export_file_selection_ok ( GtkWidget *bt, GtkFileSelection *fs) {
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gboolean result = FALSE;
	gchar *short_db_name = NULL, *db_name = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( GTK_FILE_SELECTION ( fs)->selection_entry)), short_db_name);

	if ( short_db_name != NULL && strlen ( short_db_name) > 0 ) {
		/* Export the opened catalog */
		g_strdup_from_gtk_text ( gtk_file_selection_get_filename ( fs), db_name);

		if ( gw_am_export_catalog_to ( gw_am_get_current_catalog_context ( ), gw_pm_get_selected_export_catalog_plugin ( ), db_name, short_db_name) != -1) {
			gw_msg_box_create ( window, _( "Export catalog to"), _( "Catalog exported"));
		} else {
			gw_msg_box_create ( window, _( "Export catalog to"), _( "Catalog is not exported"));
		}

		if ( db_name != NULL) g_free ( db_name);

		/* Closes the file selection box. */
		gtk_widget_destroy ( GTK_WIDGET ( fs));

		/* Clears the selected catalog plugin to export */
		gw_pm_set_selected_export_catalog_plugin ( NULL);

		result = TRUE;
	} else {}

	if ( short_db_name != NULL) g_free ( short_db_name);

	return result;
}


gboolean gw_menu_file_export_item_click ( GtkMenuItem *m, gpointer data) {
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gchar *plugin_name = data;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);

			/* Sets the catalog plugin to export */
			gw_pm_set_selected_export_catalog_plugin ( gw_pm_get_catalog_plugin ( plugin_name));

			gw_file_selection_box_create ( _( "Export catalog to"), gw_helper_db_catalog_get_usefull_name ( catalog), (GtkSignalFunc)gw_menu_file_export_file_selection_ok, NULL);

			gw_db_catalog_free ( catalog);

			result = TRUE;
		} else {}
	} else {
		gw_msg_box_create ( window, _( "Export catalog to"), _( "No catalog is opened"));
	}

	return result;
}


gboolean gw_menu_file_recents_files_item_click ( GtkMenuItem *m, gpointer data) {
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;
	gchar *msg = NULL;
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( gw_pm_get_current_catalog_plugin ( ) == NULL) {
		gw_msg_box_create ( window, _( "Open file"), _( "There is no available catalog plugin"));
	} else {
		/* Checks if a catalog context is open */
		if ( context != NULL) {
			plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
			catalog = plugin->gw_db_catalog_get_db_catalog ( context);

			/* Checks if a catalog has been modified */
			if ( gw_db_catalog_is_modified ( catalog)) {
				/* If has been modified, ask to save it before open another catalog */
				msg = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_helper_db_catalog_get_full_name ( catalog), "\n", NULL);

				gw_dialog_box_create ( window, _( "Open file"), msg, GTK_SIGNAL_FUNC ( gw_menu_file_open_recents_files_save_file_ok), GTK_SIGNAL_FUNC ( gw_menu_file_open_recents_files_save_file_no), NULL, data);
				g_free ( msg);
			} else {
				gw_am_close_catalog ( FALSE);

				/* Warning use a gint value instead of a gpointer value!! */
				result = gw_am_load_catalog_from_recents_files ( GPOINTER_TO_UINT ( data));
			}

			gw_db_catalog_free ( catalog);
		} else {
			/* Warning use a gint value instead of a gpointer value!! */
			result = gw_am_load_catalog_from_recents_files ( GPOINTER_TO_UINT ( data));
		}
	}

	return result;
}

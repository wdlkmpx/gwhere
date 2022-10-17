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
#include "gwmisc.h"
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
			gw_oknocancel_box (w, _( "New file"), msg,
			                   gw_menu_file_new_save_file_ok,
			                   gw_menu_file_new_save_file_no,
			                   NULL, NULL);
			g_free ( msg);
			gw_db_catalog_free ( catalog);
		} else {
			/* Else ask the new catalog name */
			gw_input_box (w, _( "New catalog"), _( "Enter catalog name"), "",
			              gw_menu_file_new_file_ok);
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
			gw_oknocancel_box (w, _( "Open file"), msg,
			                   gw_menu_file_open_save_file_ok,
			                   gw_menu_file_open_save_file_no,
			                      NULL, NULL);
			g_free ( msg);
			gw_db_catalog_free ( catalog);
		} else {
			/* Else opens file selection box */
			gw_file_chooser_box (_( "Open catalog"), NULL, NULL,
			                            gw_menu_file_open_file_ok,
			                            NULL);
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
		gw_oknocancel_box (w, _( "Close file"), msg,
		                   gw_menu_file_close_save_file_ok,
		                   gw_menu_file_close_save_file_no,
		                   NULL, NULL);
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
						gw_file_chooser_box (_( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
						                            gw_menu_file_saveas_file_selection_ok, NULL);
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
		gw_file_chooser_box (_( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
		                            gw_menu_file_saveas_file_selection_ok, NULL);
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
				msg[1] = g_strconcat ( _( "Would you want save catalog :\n\n"), gw_helper_db_catalog_get_full_name ( catalog), "\n", NULL);

				gw_oknocancel_box (window, msg[0], msg[1],
				                   gw_menu_file_exit_save_file_ok,
				                   gw_menu_file_exit_save_file_no,
				                   NULL, NULL);
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


gboolean gw_menu_file_open_file_ok (GtkWidget *w, char * filename)
{
	GWDBContext *context = gw_am_get_current_catalog_context ( );

	//TODO use helper functions
	if ( context != NULL ) {
		/* If a catalog is opened, don't save it. Destroys the tree and remove the window title. */
		gw_am_close_catalog ( FALSE);
	}

	/* Loads the catalog. */
	gw_am_load_catalog (filename);

	return FALSE;
}


gboolean gw_menu_file_new_file_ok ( GtkWidget *bt, gpointer data)
{
	char * name = (char *) data;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : catalog name = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, name);
#endif

	/* Checks if a catalog is allready opened */
	if ( gw_am_get_current_catalog_context ( ) != NULL ) {
		/* If is opened, closes it */
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : a catalog is already opened\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		gw_am_close_catalog ( FALSE);
	}

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : initializes the catalog data structure\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	gw_am_new_catalog ( name);

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "new catalog created ==> memory status : ");
	g_mem_profile ( );
#endif

	return TRUE;
}


gboolean gw_menu_file_new_save_file_ok (GtkWidget *w, gpointer data)
{
	GWDBCatalog *catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );

	/* Checks if is a new catalog (in this case his full name is "./[catalog_full_name]"). */
	if ( gw_helper_db_catalog_is_new ( catalog)) {
		gw_file_chooser_box (_( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
		                            gw_menu_file_new_saveas_file_selection_ok, NULL);
	} else {
		/* Else save it directly and displays a fill box of new catalog */
		gw_menu_file_save_click ( NULL, NULL);
		gw_input_box (window, _( "New catalog"), _( "Enter catalog name"), "",
		              gw_menu_file_new_file_ok);
	}

	return TRUE;
}


gboolean gw_menu_file_new_save_file_no (GtkWidget *bt, gpointer data)
{
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	gw_input_box (window, _("New catalog"), _("Enter catalog name"), "",
	              gw_menu_file_new_file_ok);
	return TRUE;
}


gboolean gw_menu_file_new_saveas_file_selection_ok (GtkWidget *w, char * filename)
{
	GtkWindow *window = NULL;
	/* Saves the catalog. */
	switch (gw_am_save_catalog (filename)) {
		case 0: break;
		case GWECATNOMODIFIED: break;
		case GWECATNOFILENAME: break;
		case GWECATCANNOTSAVE: break;
		default: break;
	}

	window = gw_gui_manager_main_interface_get_main_window ( );
	gw_input_box (window, _("New catalog"), _("Enter catalog name"), "",
	              gw_menu_file_new_file_ok);
	return TRUE;
}


gboolean gw_menu_file_open_save_file_ok (GtkWidget *w, gpointer data)
{
	GWDBCatalog *catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Checks if it's a new catalog (in this case his full name is ".[/catalog_full_name]"). */
	if ( gw_helper_db_catalog_is_new ( catalog)) {
		gw_file_chooser_box (_( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
		                            gw_menu_file_open_saveas_file_selection_ok, NULL);
	} else {
		/* Else save it directly and displays a file selection box to select the catalog to open. */
		gw_menu_file_save_click ( NULL, NULL);

		gw_file_chooser_box (_("Open catalog"), NULL, NULL,
		                            gw_menu_file_open_file_ok, NULL);
	}

	return TRUE;
}


gboolean gw_menu_file_open_save_file_no (GtkWidget *w, gpointer data)
{
	//xxx to be verified
	gw_file_chooser_box ( _("Open catalog"), NULL, NULL,
	                            gw_menu_file_open_file_ok, NULL);
	return TRUE;
}


gboolean gw_menu_file_open_recents_files_save_file_ok (GtkWidget *w, gpointer data)
{
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gpointer file_index = data;
	gboolean result = FALSE;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( context != NULL ) {
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);

		/* Checks if it's a new catalog (in this case his full name is ".[/catalog_full_name]"). */
		if ( gw_helper_db_catalog_is_new ( catalog)) {
			gw_file_chooser_box (_( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
			                            gw_menu_file_open_recents_files_saveas_file_selection_ok,
			                            file_index);
		} else {
			/* Else save it directly and displays a file selection box to select the catalog to open. */
			gw_menu_file_save_click ( NULL, NULL);

			/* Warning use a gint value instead of a gpointer value!! */
			result = gw_am_load_catalog_from_recent_files ( GPOINTER_TO_UINT ( file_index));
		}

		gw_db_catalog_free ( catalog);
	} else {
		/* Warning use a gint value instead of a gpointer value!! */
		result = gw_am_load_catalog_from_recent_files ( GPOINTER_TO_UINT ( file_index));
	}

	return result;
}


gboolean gw_menu_file_open_recents_files_save_file_no (GtkWidget *w, gpointer data)
{
	gboolean result = FALSE;
	gpointer file_index = data;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	if (file_index) {
		gw_am_close_catalog ( FALSE);

		/* Warning use a gint value instead of a gpointer value!! */
		result = gw_am_load_catalog_from_recent_files ( GPOINTER_TO_UINT ( file_index));

		result = TRUE;
	}

	return result;
}


gboolean gw_menu_file_open_saveas_file_selection_ok (GtkWidget *w, char * filename)
{
	/* Save the catalog. */
	switch (gw_am_save_catalog (filename)) {
		case 0: break;
		case GWECATNOMODIFIED: break;
		case GWECATNOFILENAME: break;
		case GWECATCANNOTSAVE: break;
		default: break;
	}

	gw_file_chooser_box (_( "Open catalog"), NULL, NULL,
	                            gw_menu_file_open_file_ok, NULL);
	return TRUE;
}


gboolean gw_menu_file_open_recents_files_saveas_file_selection_ok (GtkWidget *w, char * filename)
{
	gpointer file_index = 0; // needs fixing
	gchar *catalog_path_name = NULL;

	/* Warning use a gint value instead of a gpointer value!! */
	catalog_path_name = gw_am_get_catalog_path_name_from_recent_files ( GPOINTER_TO_UINT ( file_index));

	/* Save the catalog. */
	switch (gw_am_save_catalog (filename)) {
		case 0: break;
		case GWECATNOMODIFIED: break;
		case GWECATNOFILENAME: break;
		case GWECATCANNOTSAVE: break;
		default: break;
	}

	gw_am_load_catalog (catalog_path_name);
	if (catalog_path_name) {
		g_free (catalog_path_name);
	}

	return TRUE;
}


gboolean gw_menu_file_saveas_file_selection_ok (GtkWidget *w, char * filename)
{
	/* Save the opened catalog. */
	switch (gw_am_save_catalog (filename))
	{
		case 0:	  break;
		case GWECATNOMODIFIED: break;
		case GWECATNOFILENAME:
			gw_file_chooser_box (_( "Save as catalog"), gw_db_catalog_get_name ( ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ))), NULL,
			                            gw_menu_file_saveas_file_selection_ok, NULL);
			break;
		case GWECATCANNOTSAVE: break;
		default: break;
	}
	return TRUE;
}


gboolean gw_menu_file_close_save_file_ok (GtkWidget *w, gpointer data)
{
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	gboolean result = FALSE;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( context != NULL ) {
		plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context);
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);

		/* Checks if it's a new catalog (in this case his full name is "./[catalog_full_name]"). */
		if ( gw_helper_db_catalog_is_new ( catalog)) {
			/* If it's a new catalog, asks a file name. */
			gw_file_chooser_box (_( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
			                            gw_menu_file_close_saveas_file_selection_ok, NULL);
		} else {
			/* Else save it directly and close it. */
			gw_menu_file_save_click ( NULL, NULL);

			gw_am_close_catalog ( FALSE);
		}

		gw_db_catalog_free ( catalog);

		result = TRUE;
	} 

	return result;
}


gboolean gw_menu_file_close_save_file_no (GtkWidget *w, gpointer data)
{
	gw_am_close_catalog ( FALSE);
	return TRUE;
}


gboolean gw_menu_file_close_saveas_file_selection_ok (GtkWidget *w, char * filename)
{
	GWDBCatalog *catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( gw_am_get_current_catalog_context ( )))->gw_db_catalog_get_db_catalog ( gw_am_get_current_catalog_context ( ));

	/* Updates informations of opened catalog. */
	//TODO use helper functions
	if ( catalog != NULL ) {
		switch (gw_am_save_catalog (filename)) {
			case 0: break;
			case GWECATNOMODIFIED: break;
			case GWECATNOFILENAME: break;
			case GWECATCANNOTSAVE: break;
			default: break;
		}
	}
	gw_am_close_catalog (FALSE);

	return TRUE;
}


gboolean gw_menu_file_exit_save_file_ok (GtkWidget *w, gpointer data)
{
	GWDBContext   * context = gw_am_get_current_catalog_context ();
	GWCatalogPlugin *plugin = (GWCatalogPlugin*) gw_db_context_get_plugin (context);
	GWDBCatalog   * catalog = plugin->gw_db_catalog_get_db_catalog (context);

	/* Checks if it's a new catalog (in this case his full name is "./[catalog_full_name]"). */
	if (gw_helper_db_catalog_is_new (catalog)) {
		gw_file_chooser_box (_( "Save as catalog"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
		                            gw_menu_file_exit_saveas_file_selection_ok, NULL);
	} else {
		/* Else save the catalog directly and exit program. */
		gw_menu_file_save_click ( NULL, NULL);
		gw_menu_file_exit ( );
	}

	return TRUE;
}


gboolean gw_menu_file_exit_save_file_no (GtkWidget *w, gpointer data)
{
	gw_menu_file_exit ();
	return TRUE;
}


gboolean gw_menu_file_exit_saveas_file_selection_ok (GtkWidget *w, char * filename)
{
	/* Saves the catalog. */
	switch (gw_am_save_catalog (filename)) {
		case 0: break;
		case GWECATNOMODIFIED: break;
		case GWECATNOFILENAME: break;
		case GWECATCANNOTSAVE: break;
		default: break;
	}
	gw_menu_file_exit ();

	return TRUE;
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


gboolean gw_menu_file_import_file_selection_ok (GtkWidget *w, char * filename)
{
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );

	if ( gw_am_import_catalog_from (gw_pm_get_current_catalog_plugin ( ), gw_pm_get_selected_import_catalog_plugin ( ), filename, filename) != -1) {
		gw_msg_box_create ( window, _( "Import catalog from"), _( "Catalog imported"));
	} else {
		gw_msg_box_create ( window, _( "Import catalog from"), _( "Catalog is not imported"));
	}

	/* Clears the selected catalog plugin to import */
	gw_pm_set_selected_import_catalog_plugin ( NULL);

	return TRUE;
}


gboolean gw_menu_file_import_item_click ( GtkMenuItem *m, gpointer data) {
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gchar *plugin_name = data;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	gboolean result = FALSE;


	if ( context == NULL) {
		gw_pm_set_selected_import_catalog_plugin ( gw_pm_get_catalog_plugin ( plugin_name));

		gw_file_chooser_box (_( "Import catalog from"), NULL, NULL,
		                            gw_menu_file_import_file_selection_ok, NULL);

		result = TRUE;
	} else {
		gw_msg_box_create ( window, _( "Import catalog from"), _( "A catalog is already opened"));
	}

	return result;
}


gboolean gw_menu_file_export_file_selection_ok (GtkWidget *w, char * filename)
{
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );

	if ( gw_am_export_catalog_to ( gw_am_get_current_catalog_context ( ), gw_pm_get_selected_export_catalog_plugin ( ), filename, filename) != -1) {
		gw_msg_box_create ( window, _( "Export catalog to"), _( "Catalog exported"));
	} else {
		gw_msg_box_create ( window, _( "Export catalog to"), _( "Catalog is not exported"));
	}
	gw_pm_set_selected_export_catalog_plugin ( NULL);

	return TRUE;
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

			gw_file_chooser_box (_( "Export catalog to"), gw_helper_db_catalog_get_usefull_name ( catalog), NULL,
			                            gw_menu_file_export_file_selection_ok, NULL);

			gw_db_catalog_free ( catalog);

			result = TRUE;
		} else {}
	} else {
		gw_msg_box_create ( window, _( "Export catalog to"), _( "No catalog is opened"));
	}

	return result;
}


gboolean gw_menu_file_recent_files_item_click ( GtkMenuItem *m, gpointer data) {
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

				gw_oknocancel_box (window, _( "Open file"), msg,
				                   gw_menu_file_open_recents_files_save_file_ok,
				                   gw_menu_file_open_recents_files_save_file_no,
				                   NULL, data);
				g_free ( msg);
			} else {
				gw_am_close_catalog ( FALSE);

				/* Warning use a gint value instead of a gpointer value!! */
				result = gw_am_load_catalog_from_recent_files ( GPOINTER_TO_UINT ( data));
			}

			gw_db_catalog_free ( catalog);
		} else {
			/* Warning use a gint value instead of a gpointer value!! */
			result = gw_am_load_catalog_from_recent_files ( GPOINTER_TO_UINT ( data));
		}
	}

	return result;
}

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


#include "gwsupport.h"
#include "gwapplicationmanager.h"

#include <glib.h>
#include <stdlib.h> /* atoi -> strtol */
#include <errno.h> /* ERANGE */
#include <string.h> /* strstr strchr strrchr */
#include <stdarg.h> /* va_list va_start va_arg va_end */

#include "data/gwdata.h"
#include "tools/gwtools.h"
#include "res/gwres.h"
#include "gui/gwgui.h"

#include "gwguimanager.h"
#include "gwcatalogmanager.h"


#define GW_APPLICATION_HOME_OLD ".GWhere"
#define GW_APPLICATION_HOME ".gwhere"
#define GW_APPLICATION_SETTINGS_FILE_OLD "GWhere.cfg"
#define GW_APPLICATION_SETTINGS_FILE "gwhere.cfg"
#define GW_APPLICATION_SETTINGS_FILE_SAVE_EXTENSION "bak"


GWApplicationSettings my_application_settings;


gint gw_am_init ( gint argc, gchar *argv[]) {
	gint result = -1;
	GWSettings *settings = NULL;
	GtkWindow *window = NULL;
	gchar *catalog_file_path = NULL;
#ifdef GW_DEBUG_MODE
	gchar *os_version = NULL;
#endif
	gchar **plugins_name = NULL;


	memset ( &my_application_settings, '\0', sizeof ( GWApplicationSettings));
#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "%s %s is running in debug mode", PROJECT_NAME, VERSION);

	gw_os_get_version_str ( &os_version);
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, _( "Is running on %s"), os_version);
	if ( os_version != NULL ) {
		g_free ( os_version);
	}
#endif

	if ( g_get_user_name ( ) != NULL) {
		my_application_settings.user_name = g_strdup ( g_get_user_name ( ));
	}

	if ( g_get_home_dir ( ) != NULL) {
		my_application_settings.user_gwhere_home = g_strconcat ( g_get_home_dir ( ), G_DIR_SEPARATOR_S, GW_APPLICATION_HOME, NULL);
	} else {
		my_application_settings.user_gwhere_home = g_strconcat ( GW_HOME_DIR, G_DIR_SEPARATOR_S, GW_APPLICATION_HOME, NULL);
	}

	if ( my_application_settings.user_gwhere_home != NULL) {
		my_application_settings.user_gwhere_settings_file = g_strconcat ( my_application_settings.user_gwhere_home, G_DIR_SEPARATOR_S, GW_APPLICATION_SETTINGS_FILE, NULL);
	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Configuration file : %s", my_application_settings.user_gwhere_settings_file);
#endif

	if ( gw_properties_file_load_all_settings ( my_application_settings.user_gwhere_settings_file, &settings) == -1) {
		/* If the properties file doesn't exist, allocates a new GWSettings. */
		settings = gw_settings_new ( );
	}

	my_application_settings.settings = settings;
	gw_am_load_default_settings ( );

#ifdef GW_DEBUG_MODE
	gw_settings_display ( my_application_settings.settings);
#endif

	/* Loads all the plugins. */
	gw_pm_init ( );

	/* Loads the GWhere's theme from a rc file. */
	gtk_rc_parse ( gw_am_get_settings ( GW_VALUE_APP_GUI_RC_FILE));

	/* Creates the GUI. */
	window = gw_gui_manager_main_interface_create ( );
	gtk_widget_show_all ( GTK_WIDGET ( window));
	icons_load_catalog ( window);
	gw_gui_manager_main_interface_update_all ( );

	/* Command lines parameters overloads the settings.
	   That's why loads before the optional file else the autoloaded file. */
	if ( argc >= 2 ) {
		gw_am_load_catalog ( argv[1]);
	} else if ( gw_am_get_settings_tob ( GW_VALUE_APP_CATALOG_AUTOLOAD) == TRUE ) {
		if ( gw_am_get_settings_tob ( GW_VALUE_APP_CATALOG_AUTOLOAD_LAST) == TRUE ) {
			gw_am_load_catalog ( gw_am_get_settings ( GW_VALUE_APP_CATALOG_LAST));
		} else {
			if ( gw_am_get_settings_tob ( GW_VALUE_APP_CATALOG_AUTOLOAD_SELECTED) == TRUE ) {
				if ( (catalog_file_path = gw_am_get_settings ( GW_VALUE_APP_CATALOG_AUTOLOAD_FILEPATH)) != NULL ) {
					gw_am_load_catalog ( catalog_file_path);
				} else {}
			} else {}
		}
	} else {}

	if ( gw_pm_get_current_catalog_plugin ( ) == NULL) {
		gw_status_bar_put_messages ( window, _( "There is no available catalog plugin"), "");
	}

	/* Loads the import plugins. */
	plugins_name = gw_pm_get_all_catalog_import_plugin_name ( );
	gw_menu_file_set_import ( window, plugins_name);
	g_free ( plugins_name);
	plugins_name = gw_pm_get_all_catalog_export_plugin_name ( );
	gw_menu_file_set_export ( window, plugins_name);
	g_free ( plugins_name);

	return result;
}


gint gw_am_load_default_settings ( ) {
#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( gw_am_get_settings ( GW_VALUE_APP_GUI_RC_FILE) == NULL ) {
		gw_am_set_settings ( GW_VALUE_APP_GUI_RC_FILE, g_strconcat ( my_application_settings.user_gwhere_home, G_DIR_SEPARATOR_S, GW_VALUE_APP_GUI_RC_FILE_DEFAULT, NULL));
	}

	if ( gw_am_get_settings ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER) == NULL ) {
		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER, g_strdup_printf ( "%d", GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER_DEFAULT));
	}

	if ( gw_am_get_settings ( GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE) == NULL ) {
		gw_am_set_settings ( GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE, g_strdup_printf ( "%d", GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE_DEFAULT));
	}

	return 0;
}


gboolean gw_am_can_send_mail ( ) {
	gboolean result = FALSE;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( gw_am_get_settings ( GW_VALUE_APP_MAIL_EMAIL_ADDRESS) != NULL ) {
		if ( gw_am_get_settings ( GW_VALUE_APP_MAIL_SERVER_ADDRESS) != NULL ) {
			if ( gw_am_get_settings ( GW_VALUE_APP_MAIL_SERVER_PORT) != NULL ) {
				result = TRUE;
			}
		}
	}

	return result;
}


gchar * gw_am_get_settings ( const gchar *name) {
	gchar *value = NULL;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( name != NULL ) {
		value = gw_settings_get_value ( my_application_settings.settings, (gchar *)name);
	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "pair is (%s := %s)", name!=NULL?name:"(null)", value!=NULL?value:"(null)");
#endif


	return value;
}


gfloat gw_am_get_settings_tod ( const gchar *name) {
	gint result = -1;
	gchar *str_value = NULL;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (str_value = gw_am_get_settings ( name)) != NULL ) {
		result = strtod ( str_value, NULL);
	}

	return result;
}


gint gw_am_get_settings_tol ( const gchar *name) {
	gint result = -1;
	gchar *str_value = NULL;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (str_value = gw_am_get_settings ( name)) != NULL ) {
		result = strtol ( str_value, NULL, 10);

	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "pair is (%s := %d)", name!=NULL?name:"(null)", result);
#endif

	return result;
}


gint gw_am_get_settings_tolx ( const gchar *name, const gint value) {
	gint result = -1;


	if ( (result = gw_am_get_settings_tol ( name)) == -1) {
		result = value;
	}

	return result;
}


gboolean gw_am_get_settings_tob ( const gchar *name) {
	gboolean result = FALSE;
	gint int_value = -1;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (int_value = gw_am_get_settings_tol ( name)) != -1 ) {
		result = int_value==1?TRUE:FALSE;
	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "pair is (%s := %d)", name!=NULL?name:"(null)", result);
#endif

	return result;
}


gboolean gw_am_get_settings_tobx ( const gchar *name, const gboolean value) {
	gboolean result = FALSE;
	gint int_value = -1;


	if ( (int_value = gw_am_get_settings_tol ( name)) == -1 ) {
		result = value;
	} else {
		result = int_value==1?TRUE:FALSE;
	}

	return result;
}


gint gw_am_set_settings ( const gchar *name, gchar *value) {
	gint result = -1;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "pair is (%s := %s)", name!=NULL?name:"(null)", value!=NULL?value:"(null)");
#endif

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "old pair is (%s := %s)", name!=NULL?name:"(null)", gw_am_get_settings ( name)!=NULL?gw_am_get_settings ( name):"(null)");
#endif

	if ( name != NULL ) {
		gw_settings_add_pair ( my_application_settings.settings, g_strdup ( name), value);

		result = 0;
	}

#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "new pair is (%s := %s)", name!=NULL?name:"(null)", gw_am_get_settings ( name)!=NULL?gw_am_get_settings ( name):"(null)");
#endif

	return result;
}


struct catalog_file_info * gw_am_get_current_catalog ( ) {
	struct catalog_file_info * catalog_info = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	tree = gw_gui_manager_main_interface_get_tree ( );
	root = gw_gui_manager_main_interface_get_tree_root ( );

	if ( (tree != NULL) && (root != NULL) ) {
		/* Gets catalog informations */
		catalog_info = gtk_ctree_node_get_row_data ( tree, root);
	}

	return catalog_info;

}


gint gw_am_exit ( ) {
	gint result = -1;
	gchar *save_file = NULL;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	gw_gui_manager_exit ( );
	gw_pm_exit ( );

	if ( gw_file_mkdirs ( my_application_settings.user_gwhere_home) == 0 ) {
#ifdef GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Configuration file : is %s exists?", my_application_settings.user_gwhere_settings_file);
#endif
		if ( gw_file_exists ( my_application_settings.user_gwhere_settings_file) == 0 ) {
			save_file = g_strconcat ( my_application_settings.user_gwhere_settings_file, "." , GW_APPLICATION_SETTINGS_FILE_SAVE_EXTENSION, NULL);
			gw_file_copy ( my_application_settings.user_gwhere_settings_file, save_file);
			g_free ( save_file);
		}

#ifdef GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Configuration file : %s", my_application_settings.user_gwhere_settings_file);
		gw_settings_display ( my_application_settings.settings);
#endif

		if ( gw_properties_file_save_all_settings ( my_application_settings.user_gwhere_settings_file, &(my_application_settings.settings), NULL) != -1) {
#ifdef GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "properties file saved");
#endif

			result = 0;
		} else {
#ifdef GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "warning unabble to save the properties file!!");
#endif
		}
	}

	if ( my_application_settings.settings != NULL) {
		gw_settings_free ( my_application_settings.settings);
		my_application_settings.settings = NULL;
	}

	if ( my_application_settings.user_gwhere_home != NULL ) {
		g_free ( my_application_settings.user_gwhere_home);
		my_application_settings.user_gwhere_home = NULL;
	}

	if ( my_application_settings.user_gwhere_settings_file != NULL ) {
		g_free ( my_application_settings.user_gwhere_settings_file);
		my_application_settings.user_gwhere_settings_file = NULL;
	}

	return result;
}


gint gw_am_send_mail ( GWMail *mail) {
	gint result = -1;
	gboolean good = TRUE;
	gint server_port = 0;


#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( mail != NULL ) {
		/* Checks if can send a mail. */
		if ( gw_am_can_send_mail ( ) ) {
			/* To do more and more checking tests. */
			good = good && gw_mail_check_email_list ( gw_am_get_settings ( GW_VALUE_APP_MAIL_EMAIL_ADDRESS));
			good = good && gw_mail_check_email_list ( mail->to);
			good = good && gw_mail_check_email_list ( mail->cc);
			good = good && gw_mail_check_email_list ( mail->bcc);

			if ( good ) {
				server_port = gw_am_get_settings_tol ( GW_VALUE_APP_MAIL_SERVER_PORT);

				if ( (server_port == INT_MIN) || ( server_port == INT_MAX) ) {
					switch ( errno) {
						case ERANGE :	perror ( "strtol");
								break;

						default :	perror ( "strtol");
								break;
					}
				}

				result = gw_mail_send_mail ( gw_am_get_settings ( GW_VALUE_APP_MAIL_SERVER_ADDRESS),
						server_port,
						gw_am_get_settings ( GW_VALUE_APP_MAIL_EMAIL_ADDRESS),
						mail->to,
						mail->cc,
						mail->bcc,
						mail->subject,
						mail->message,
						mail->file_path);
			}
		}
	}

	return result;
}


gint gw_am_load_catalog ( const char *filepath) {
	/* Bug to fix : should check if a catalog is already opened. */
	gint result = -1;
	GtkWindow *window = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	GWCatalogPlugin *plugin = gw_pm_get_default_catalog_plugin ( );
	GWDBContext *context = NULL;
	gint compression_level = -1;
	gchar *mode = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	/* If a catalog is open, need to close it */
	//TODO use helper functions
	if ( gw_am_get_current_catalog_context ( ) != NULL ) {
		gw_menu_file_close_click ( NULL, NULL);
	}

	if ( filepath != NULL ) {
		/* Gets the file compression level. */
		compression_level = gw_am_get_settings_tolx ( GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL, GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT);

		/* Builds the open file mode. */
		mode = g_strdup_printf ( "wb%d", compression_level);

		context = plugin->gw_db_catalog_open ( plugin, filepath, mode);
		g_free ( mode);
		if ( context != NULL) {
			gw_db_context_set_plugin ( context, plugin);
			gw_cm_load ( context);

#if GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Adding the current catalogs in the recents files list...");
#endif

			gw_am_add_recent_file ( filepath);
			gw_am_set_settings ( GW_VALUE_APP_CATALOG_LAST, g_strdup ( filepath));

			gw_status_bar_put_messages ( window, _( "Catalog loaded"), "");
			gw_gui_manager_main_interface_update_all ( );
			gw_gui_manager_main_interface_refresh ( );
		} else {
			window = gw_gui_manager_main_interface_get_main_window ( );
			gw_status_bar_put_messages ( window, _( "Loading catalog failed"), "");
			gw_msg_box_create ( window, _( "Loading catalog"), _( "The catalog is invalid or doesn't exists. Check your catalog path please."));
		}

		window = gw_gui_manager_main_interface_get_main_window ( );
		tree = gw_gui_manager_main_interface_get_tree ( );
		root = gw_gui_manager_main_interface_get_tree_root ( );

#if GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "%s extension is %s", filepath, &filepath[strlen ( filepath) - 3]);
#endif
	}

	return result;
}


gint gw_am_save_catalog ( const gchar *path) {
	gint result = -1;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWDBCatalog *catalog = NULL;
	GtkCTree *tree = NULL;
	GtkCTreeNode *root = NULL;
	GtkWindow *window = NULL;
	gchar *text[1];
	gchar *fullfilename = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	catalog = ((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_catalog_get_db_catalog ( context);

	//FIXME if the catalog file already exists it will be erased.
	if ( (gw_db_catalog_get_db_name ( catalog)!=NULL) && (gw_file_exists ( path) == 0) && (strcmp ( path, gw_db_catalog_get_db_name ( catalog)) != 0) ) {
#if GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Warning the catalog file already exists and it will be erased without confirmation");
#endif
	}

	if ( catalog != NULL ) {
		tree = gw_gui_manager_main_interface_get_tree ( );
		root = gw_gui_manager_main_interface_get_tree_root ( );
		window = gw_gui_manager_main_interface_get_main_window ( );

		if ( path != NULL ) {
			/* Adds the extension if it isn't present. */
			if ( (strlen ( path) < 4) || (strcmp ( &path[strlen ( path) - 4], ".ctg") != 0) ) {
				fullfilename = g_strconcat ( path, ".ctg", NULL);
			} else {
				fullfilename = g_strdup ( path);
			}

			/* Checks if the catalog must be saved in a new file. */
			if ( (gw_db_catalog_get_db_name ( catalog) == NULL) || (strcmp ( fullfilename, gw_db_catalog_get_db_name ( catalog)) != 0) ) {
				gw_db_catalog_set_ismodified ( catalog, TRUE);
				gw_db_catalog_set_short_db_name ( catalog, gw_file_get_name ( fullfilename));
				gw_db_catalog_set_db_name ( catalog, fullfilename);
			} else {
				g_free ( fullfilename);
				fullfilename = NULL;
			}
		} else {}

		gw_db_catalog_set_program_builder ( catalog, g_strconcat ( PROJECT_NAME, VERSION, NULL));

		/* Writes the new window title. */
		if ( gw_db_catalog_get_db_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_db_name ( catalog))>0 ) {
			gtk_window_set_title ( window, (text[0] = g_strconcat ( PROJECT_NAME, " - ", gw_db_catalog_get_db_name ( catalog), NULL)));
			g_free ( text[0]);
			text[0] = NULL;
		} else {
			/* Don't modify the main window title */
		}

		/* Sets the new catalog name in the tree. */
		if ( gw_db_catalog_get_name ( catalog)!=NULL && strlen ( gw_db_catalog_get_name ( catalog))>0) {
			g_strdup_to_gtk_text ( gw_db_catalog_get_name ( catalog), text[0]);
		} else {
			g_strdup_to_gtk_text ( gw_db_catalog_get_short_db_name ( catalog), text[0]);
		}

		gtk_ctree_set_node_info ( tree, root, text[0], 5, PixCatalog, MskCatalog, PixCatalog, MskCatalog, FALSE, TRUE);
		g_free(text[0]);

		/* Checks if the catalog has been modified. */
		if ( gw_db_catalog_is_modified ( catalog) ) {
#if GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "the catalog is modified.");
#endif
			/* If has been modified save it */
			/* Checks if it's a new catalog (in this case his full name is "./[catalog_name]") */
			if ( gw_db_catalog_get_db_name ( catalog)==NULL || strlen ( gw_db_catalog_get_db_name ( catalog))==0 ) {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "it's a new catalog, please set a catalog file name.");
#endif

				/* If it's a new catalog, ask a file name */
				result = GWECATNOFILENAME;
			} else {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "the catalog is saving...");
#endif

				gw_status_bar_put_messages ( window, _( "Saving catalog"), _( "Please wait..."));
				gw_gui_manager_main_interface_refresh ( );
				((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_catalog_update ( context, catalog);

				/* Else save it directly */
				if ( ((GWCatalogPlugin*)gw_db_context_get_plugin ( context))->gw_db_catalog_save ( context) == 0) {
					gw_db_catalog_set_ismodified ( catalog, FALSE);
					result = 0;

					gw_am_add_recent_file ( gw_db_catalog_get_db_name ( catalog));
					gw_am_set_settings ( GW_VALUE_APP_CATALOG_LAST, g_strdup ( gw_db_catalog_get_db_name ( catalog)));

					gw_status_bar_put_messages ( window, _( "Catalog saved"), "");
					gw_gui_manager_main_interface_update_all ( );
					gw_gui_manager_main_interface_refresh ( );
				} else {
					result = GWECATCANNOTSAVE;

					gw_status_bar_put_messages ( window, _( "Saving catalog failed"), "");
					gw_gui_manager_main_interface_refresh ( );
				}
			}
		} else {
#if GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "the catalog isn't modified.");
#endif

			result = GWECATNOMODIFIED;
		}
	} else {
#if GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "no opened catalog!!");
#endif
	}

	return result;
}


gint gw_am_close_catalog ( gboolean save) {
	gint result = -1;
	GWDBContext * context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = NULL;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL) {
			plugin->gw_db_catalog_close ( context);
			result = 0;
		} else {
			//Impossible : le context's plugin cannot be NULL!!
		}
	}

	gw_am_set_current_catalog_context ( NULL);
	gw_notebook_catalog_ctree_destroy_all ( );

	return result;
}


gint gw_am_add_recent_file ( const gchar *filepath) {
	gint result = -1;
	gchar *recents_files = NULL;
	gint max_nb_files = -1;
	gchar **recents_files_list = NULL;
	gint i = 0;
	gboolean already_exist = FALSE;
	gchar *recents_files_tmp = NULL;
	gchar *recents_file = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( filepath != NULL ) {
		/* Stores in the recents opened files list. */
		recents_files = gw_am_get_settings ( GW_VALUE_APP_RECENTS_FILES);
		max_nb_files = gw_am_get_settings_tol ( GW_VALUE_APP_RECENT_SIZE);

		if ( recents_files != NULL ) {
			recents_files_list = g_strsplit ( recents_files, G_SEARCHPATH_SEPARATOR_S, -1);

			/* Gets the number of recents opened files and checks if the file doesn't already exists. */
			for ( i = 0; (recents_files_list[i] != NULL); i++) {
				/* Checks if the file doesn't already exist in the files that will be kept. */
				if ( (strcmp ( filepath, recents_files_list[i]) == 0) && (i < max_nb_files) ) {
#if GW_DEBUG_MODE
					gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "the file %s is already in the recents opened catalog file at position %d.", filepath, i+1);
#endif

					already_exist = TRUE;
				}
			}

			/* Removes all over stored recents opened files. */
			while ( ((i >= (max_nb_files - 1)) && ( i >= 0) && (already_exist == FALSE)) || ((i >= (max_nb_files)) && ( i >= 0) && (already_exist == TRUE))) {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "remove %s at %d.", recents_files_list[i]!=NULL?recents_files_list[i]:"(null)", i+1);
#endif
				g_free ( recents_files_list[i]);
				recents_files_list[i] = NULL;
				i--;
			}

			/* Make a place for the new entry. */
			if ( (i >= (max_nb_files - 1)) && (already_exist == FALSE) && (i >= 0) ) {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "must remove one entry for the new entry", NULL);
#endif

				g_free ( recents_files_list[i]);
				recents_files_list[i] = NULL;
				i--;
			}

			/* Builds the new recents opened files string. */
			if ( recents_files_list != NULL ) {
				recents_files_tmp = g_strjoinv ( G_SEARCHPATH_SEPARATOR_S, recents_files_list);
			}

			if ( (already_exist == FALSE) ) {
				if ( recents_files_tmp != NULL ) {
					recents_file = g_strconcat ( filepath, G_SEARCHPATH_SEPARATOR_S, recents_files_tmp, NULL);
				} else {
					recents_file = g_strdup ( filepath);
				}
			} else {
				if ( recents_files_tmp != NULL ) {
					recents_file = g_strdup ( recents_files_tmp);
				} else {
					recents_file = NULL;
				}
			}

			if ( recents_files_tmp != NULL ) {
				g_free ( recents_files_tmp);
			}

			gw_am_set_settings ( GW_VALUE_APP_RECENTS_FILES, recents_file);

			g_strfreev ( recents_files_list);
		} else {
			gw_am_set_settings ( GW_VALUE_APP_RECENTS_FILES, g_strdup ( filepath));
		}
	}

	return result;
}


gint gw_am_load_catalog_from_recents_files ( const guint index) {
	gint result = -1;
	gchar *files = NULL;
	gchar **files_list = NULL;
	gint i = 0;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "opening recent file number %d.", index);
#endif

	if ( (files = gw_am_get_settings ( GW_VALUE_APP_RECENTS_FILES)) != NULL) {
		files_list = g_strsplit ( files, G_SEARCHPATH_SEPARATOR_S, -1);

		i = 0;
		while ( (files_list[i] != NULL) && (i < index) ) {
			i++;
		}

		if ( i == index ) {
#if GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "preparing to load %s.", files_list[i]);
#endif

			gw_am_load_catalog ( files_list[i]);

			result = 0;
		}

		g_strfreev ( files_list);
	}

	return result;
}


gchar * gw_am_get_catalog_path_name_from_recents_files ( const guint index) {
	gchar *files = NULL;
	gchar **files_list = NULL;
	gchar *result = NULL;
	gint i = 0;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "getting catalog path name in recents files list at %d.", index);
#endif

	if ( (files = gw_am_get_settings ( GW_VALUE_APP_RECENTS_FILES)) != NULL) {
		files_list = g_strsplit ( files, G_SEARCHPATH_SEPARATOR_S, -1);

		i = 0;
		while ( (files_list[i] != NULL) && (i < index) ) {
			i++;
		}

		if ( i == index ) {
#if GW_DEBUG_MODE
			gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "preparing to load %s.", files_list[i]);
#endif

			result = g_strdup ( files_list[i]);
		}

		g_strfreev ( files_list);
	}

	return result;
}


void gw_am_log_msg ( const gint level, const gchar *file, const gint line, const gchar *function, const gchar *msg, ...) {
	/* There is may be a bug with the special sequence "%c". */
#if GW_DEBUG_MODE
	gint nb = 0;
	gchar *str_index = NULL;
	gchar *segm = NULL;
	gchar *tmp = NULL;
	gint len = 0;
	gint i;


	g_print ( "*** GW - %s (%d) :: %s()", file, line, function);

	if ( msg != NULL ) {
		g_print ( " : ");

		str_index = (gchar*)msg;

		while ( (str_index = strchr ( str_index, '%')) != NULL) {
			nb++;
			str_index++;
		}

		str_index = (gchar*)msg;

		if ( nb > 0 ) {
			va_list ( ap);
			va_start ( ap, msg);

			for ( i = 1; i <= nb; i++) {
				segm = str_index;
				str_index = strchr ( segm, '%') + 2;
				len = str_index - segm;
				tmp = (gchar*)g_malloc0 ( sizeof ( gchar) * (len+1));
				memcpy ( tmp, segm, len);
				tmp[len] = '\0';

				switch ( tmp[len-1]) {
					case 'd':	g_print ( tmp, va_arg ( ap, int));break;
					case 'c':	g_print ( tmp, va_arg ( ap, char));break;
					case 's':	g_print ( tmp, va_arg ( ap, char*));break;
					case 'p':	g_print ( tmp, va_arg ( ap, void*));break;
					default:	g_print ( tmp);break;
				}

				g_free ( tmp);
			}

			va_end ( ap);
		}

		g_print ( "%s", str_index);
	}

	g_print ( "\n");
#endif
}


void gw_am_beep ( ) {
#ifdef GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( gw_am_get_settings_tob ( GW_VALUE_APP_GUI_BEEP) == TRUE) {
		gdk_beep ( );
	}

	return;
}


GWSettingsExplorerField ** gw_plugin_settings_explorer_disk_get_all_fields ( void) {
	GWSettingsExplorerField **p;
	gint i = 0;
	gint index = -1;
	gint show = -1;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	p = (GWSettingsExplorerField**)g_malloc ( sizeof ( GWSettingsExplorerField*) * 13);

	for ( i = 0; i < 13; i++ ) {
		p[i] = NULL;
	}

	i = -1;

	/* Disk name */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_TITLE), p[i]->name);
	p[i]->position = gw_am_get_settings_tolx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION_DEFAULT);
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_POSITION);
	p[i]->visible = gw_am_get_settings_tobx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SHOW, TRUE);
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NAME_SHOW);

	/* Disk file system name */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_TITLE), p[i]->name);
	p[i]->position = gw_am_get_settings_tolx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION, GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION_DEFAULT);
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_POSITION);
	p[i]->visible = gw_am_get_settings_tobx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SHOW, TRUE);
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FSNAME_SHOW);

	/* Disk access path */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_TITLE), p[i]->name);
	p[i]->position = gw_am_get_settings_tolx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION, GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION_DEFAULT);
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_POSITION);
	p[i]->visible = gw_am_get_settings_tobx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SHOW, TRUE);
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_PATH_SHOW);

	/* Disk number archive */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_TITLE), p[i]->name);
	p[i]->position = gw_am_get_settings_tolx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION, GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION_DEFAULT);
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_POSITION);
	p[i]->visible = gw_am_get_settings_tobx ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SHOW, TRUE);;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_NBARCHIVE_SHOW);

	/* Disk type */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_TYPE_SHOW);

	/* Disk volume name */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_VOLUME_SHOW);

	/* Disk capacity */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CAPACITY_SHOW);

	/* Disk free space */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_FREE_SHOW);

	/* Disk adding date */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DATE_SHOW);

	/* Disk serial number */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_SERIAL_SHOW);

	/* Disk category */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_CATEGORY_SHOW);

	/* Disk description */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_DISK_COLUMN_DESCRIPTION_SHOW);

	return p;
}


GWSettingsExplorerField ** gw_plugin_settings_explorer_file_get_all_fields ( void) {
	GWSettingsExplorerField **p;
	gint i = 0;
	gint index = -1;
	gint show = -1;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	p = (GWSettingsExplorerField**)g_malloc ( sizeof ( GWSettingsExplorerField*) * 12);

	for ( i = 0; i < 12; i++ ) {
		p[i] = NULL;
	}

	i = -1;

	/* File name */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_NAME_SHOW);

	/* File rights */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_RIGHTS_SHOW);

	/* File owner */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_OWNER_SHOW);

	/* File group */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_GROUP_SHOW);

	/* File size */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_SIZE_SHOW);

	/* File inode */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_INODE_SHOW);

	/* File acces date */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_ADATE_SHOW);

	/* File modification date */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_MDATE_SHOW);

	/* File creation date */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CDATE_SHOW);

	/* File category */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_CATEGORY_SHOW);

	/* File description */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION)) == -1) {
		index = GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_EXPLORER_FILE_COLUMN_DESCRIPTION_SHOW);

	return p;
}


GWSettingsExplorerField ** gw_plugin_settings_search_get_all_fields ( void) {
	GWSettingsExplorerField **p;
	gint i = 0;
	gint index = -1;
	gint show = -1;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	p = (GWSettingsExplorerField**)g_malloc ( sizeof ( GWSettingsExplorerField*) * 8);

	for ( i = 0; i < 8; i++ ) {
		p[i] = NULL;
	}

	i = -1;

	/* File name */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_SEARCH_COLUMN_NAME_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION)) == -1) {
		index = GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_NAME_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_NAME_SHOW);

	/* Disk name */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_SEARCH_COLUMN_DISK_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION)) == -1) {
		index = GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DISK_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_DISK_SHOW);

	/* File path */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_SEARCH_COLUMN_PATH_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION)) == -1) {
		index = GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_PATH_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_PATH_SHOW);

	/* File size */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_SEARCH_COLUMN_SIZE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION)) == -1) {
		index = GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_SIZE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_SIZE_SHOW);

	/* File date */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_SEARCH_COLUMN_DATE_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION)) == -1) {
		index = GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DATE_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_DATE_SHOW);

	/* File category */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION)) == -1) {
		index = GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SHOW);

	/* File description */
	index = -1;
	show = -1;
	p[++i] = gw_settings_explorer_field_new ( );

	g_strdup_to_gtk_text ( _( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_TITLE), p[i]->name);

	if ( (index = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION)) == -1) {
		index = GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT;
	}
	p[i]->position = index;
	p[i]->position_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION);

	if ( (show = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SHOW)) == -1) {
		show = 1;
	}
	p[i]->visible = (gboolean)show;
	p[i]->visible_v = g_strdup ( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SHOW);

	return p;
}


void gw_am_set_current_catalog_context ( GWDBContext * context) {
	current_catalog_context = context;
}


GWDBContext * gw_am_get_current_catalog_context ( ) {
	return current_catalog_context;
}


gint gw_am_import_catalog_from ( GWCatalogPlugin *oplugin, GWCatalogPlugin *iplugin, gchar *db_name, gchar *short_db_name) {
	GWCatalogPlugin *op = oplugin, *ip = iplugin;
	GWDBContext *octx = NULL, *ictx = NULL;
	GWDBCatalog *ocat = NULL, *icat = NULL;
	GWDBCategory **categories = NULL;
	GWDBDisk **disks = NULL;
	GWDBDiskPK idiskPK = NULL, odiskPK = NULL;
	GWDBFile **files = NULL;
	GWDBFilePK ifilePK = NULL, ofilePK = NULL;
	gint i = 0, j = 0;
	gchar *compression_level = NULL;
	gchar *mode = NULL;


	/* Gets the file compression level. */
	compression_level = gw_am_get_settings ( GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL);
	if ( compression_level == NULL ) {
		compression_level = g_strdup_printf ( "%d", GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT);
	} else {
		compression_level = g_strdup ( compression_level);
	}

	/* Builds the open file mode. */
	mode = g_strdup_printf ( "wb%s", compression_level);
	g_free ( compression_level);

	/* Creates the import plugin context */
	if ( (ictx = ip->gw_db_catalog_open ( ip, db_name, mode)) == NULL ) {
		g_free ( mode);

		return -1;
	}
	octx = op->gw_db_catalog_create ( op, short_db_name, mode);
	gw_db_context_set_plugin ( octx, op);
	g_free(mode);
	gw_db_context_set_plugin ( ictx, ip);
	icat = ip->gw_db_catalog_get_db_catalog ( ictx);
	ocat = ip->gw_db_catalog_get_db_catalog ( octx);
	if ( gw_db_catalog_get_name ( icat) != NULL) {
		gw_db_catalog_set_name ( ocat, g_strdup ( gw_db_catalog_get_name ( icat)));
	}
	if ( gw_db_catalog_get_description ( icat) != NULL) {
		gw_db_catalog_set_description ( ocat, g_strdup ( gw_db_catalog_get_description ( icat)));
	}
	gw_db_catalog_set_program_builder ( ocat, g_strdup_printf ( "%s (%s)", PROJECT_NAME, "plugin name??"));
	op->gw_db_catalog_update ( octx, ocat);
	gw_db_catalog_free ( ocat);
	gw_db_catalog_free ( icat);

	/* Imports all the categories */
	//Becarefull, at time the category index is managed by the catalog plugin.
	if ( (categories = ip->gw_db_catalog_get_db_categories ( ictx)) != NULL) {
		for ( i = 0; categories[i]!=NULL; i++) {
			if ( gw_db_category_get_index ( categories[i]) != 0) {
				op->gw_db_catalog_add_db_category ( octx, categories[i]);
//TOVALIDATE
//			} else {
//				gw_db_category_free ( categories[i]);
//			}
}
gw_db_category_free ( categories[i]);
		}

		g_free ( categories);
	}

	/* Imports all the disks */
	if ( (disks = ip->gw_db_catalog_get_db_disks ( ictx)) != NULL) {
		for ( i = 0; disks[i]!=NULL; i++) {
			idiskPK = gw_db_disk_get_ref ( disks[i]);
			odiskPK = op->gw_db_catalog_add_db_disk ( octx, disks[i]);
			if ( (files = ip->gw_db_disk_get_db_files ( ictx, idiskPK)) != NULL) {
				for ( j = 0; files[j]!=NULL;j++) {
					ifilePK = gw_db_file_get_ref ( files[j]);
					ofilePK = op->gw_db_disk_add_db_file ( octx, odiskPK, files[j]);

					/* Imports the folder */
					gw_cm_catalog_copy_folder ( ictx, octx, ifilePK, ofilePK);
//TOVALIDATE
gw_db_file_free ( files[j]);
				}

				g_free ( files);
			}
//TOVALIDATE
gw_db_disk_free ( disks[i]);
		}

		g_free ( disks);
	}

	/* Closes the import plugin context */
	ip->gw_db_catalog_close ( ictx);

	/* Loads the imported catalog */
	gw_cm_load ( octx);

	return 0;
}


gint gw_am_export_catalog_to ( GWDBContext *context, GWCatalogPlugin *plugin, gchar *db_name, gchar *short_db_name) {
	GWCatalogPlugin *op = plugin, *ip = NULL;
	GWDBContext *octx = NULL, *ictx = context;
	GWDBCatalog *ocat = NULL, *icat = NULL;
	GWDBCategory **categories = NULL;
	GWDBDisk **disks = NULL;
	GWDBDiskPK idiskPK = NULL, odiskPK = NULL;
	GWDBFile **files = NULL;
	GWDBFilePK ifilePK = NULL, ofilePK = NULL;
	gint i = 0, j = 0;
	gchar *compression_level = NULL;
	gchar *mode = NULL;
	GWPluginInfo *plugin_info = NULL;


	/* Gets the file compression level. */
	compression_level = gw_am_get_settings ( GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL);

	if ( compression_level == NULL ) {
		compression_level = g_strdup_printf ( "%d", GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT);
	} else {
		compression_level = g_strdup ( compression_level);
	}

	/* Builds the open file mode. */
	mode = g_strdup_printf ( "wb%s", compression_level);
	g_free ( compression_level);

	/* Creates the export plugin context */
	ip = gw_db_context_get_plugin ( ictx);
	icat = ip->gw_db_catalog_get_db_catalog ( ictx);
	if ( (octx = op->gw_db_catalog_create ( op, gw_db_catalog_get_name ( icat), mode)) == NULL ) {
		g_free ( mode);
		gw_db_catalog_free ( icat);

		return -1;
	}
	g_free ( mode);
	gw_db_context_set_plugin ( octx, op);

	/* Export catalog information */
	ocat = op->gw_db_catalog_get_db_catalog ( octx);
	gw_db_catalog_set_db_name ( ocat, g_strdup ( db_name));
	gw_db_catalog_set_short_db_name ( ocat, g_strdup ( short_db_name));
	//FIXME add plugin name
	plugin_info = op->gw_plugin_get_info ( );
	gw_db_catalog_set_program_builder ( ocat, g_strdup_printf ( "%s (%s)", PROJECT_NAME, gw_plugin_info_get_name ( plugin_info)));
	gw_plugin_info_free ( plugin_info);
	gw_db_catalog_set_description ( ocat, g_strdup ( gw_db_catalog_get_description ( icat)));
	op->gw_db_catalog_update ( octx, ocat);
	gw_db_catalog_free ( ocat);
	gw_db_catalog_free ( icat);

	/* Exports all the categories */
	//Becarefull, at time the category index is managed by the catalog plugin.
	if ( (categories = ip->gw_db_catalog_get_db_categories ( ictx)) != NULL) {
		for ( i = 0; categories[i]!=NULL; i++) {
			if ( gw_db_category_get_index ( categories[i]) != 0) {
				op->gw_db_catalog_add_db_category ( octx, categories[i]);
//TOVALIDATE
//			} else {
//				gw_db_category_free ( categories[i]);
//			}
}
gw_db_category_free ( categories[i]);
		}

		g_free ( categories);
	}

	/* Exports all the disks */
	if ( (disks = ip->gw_db_catalog_get_db_disks ( ictx)) != NULL) {
		for ( i = 0; disks[i]!=NULL; i++) {
			idiskPK = gw_db_disk_get_ref ( disks[i]);
			odiskPK = op->gw_db_catalog_add_db_disk ( octx, disks[i]);
			if ( (files = ip->gw_db_disk_get_db_files ( ictx, idiskPK)) != NULL) {
				for ( j = 0; files[j]!=NULL;j++) {
					ifilePK = gw_db_file_get_ref ( files[j]);
					ofilePK = op->gw_db_disk_add_db_file ( octx, odiskPK, files[j]);

					/* Exports the folder */
					gw_cm_catalog_copy_folder ( ictx, octx, ifilePK, ofilePK);
//TOVALIDATE
gw_db_file_free ( files[j]);
				}

				g_free ( files);
			}
//TOVALIDATE
gw_db_disk_free ( disks[i]);
		}

		g_free ( disks);
	}

	/* Saves and closes the export plugin context */
	op->gw_db_catalog_save ( octx);
	op->gw_db_catalog_close ( octx);

	return 0;
}


gint gw_am_new_catalog ( const gchar *name) {
	gint result = -1;
	GWCatalogPlugin *plugin = NULL;
	GWDBContext *context = NULL;
	GWDBCatalog *catalog = NULL;
	gchar *compression_level = NULL;
	gchar *mode = NULL;


	if ( name != NULL) {
		/* Gets the file compression level. */
		compression_level = gw_am_get_settings ( GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL);

		if ( compression_level == NULL ) {
			compression_level = g_strdup_printf ( "%d", GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT);
		} else {
			compression_level = g_strdup ( compression_level);
		}

		/* Builds the open file mode. */
		mode = g_strdup_printf ( "wb%s", compression_level);
		g_free ( compression_level);
		plugin = gw_pm_get_current_catalog_plugin ( );
		context = plugin->gw_db_catalog_create ( plugin, name, mode);
		g_free ( mode);
		gw_db_context_set_plugin ( context, plugin);
		catalog = plugin->gw_db_catalog_get_db_catalog ( context);
		gw_db_catalog_set_program_builder ( catalog, g_strdup ( PROJECT_NAME));
		plugin->gw_db_catalog_update ( context, catalog);
		gw_db_catalog_free ( catalog);

		gw_cm_load ( context);

		result = 0;
	}

	return result;
}

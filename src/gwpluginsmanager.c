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
#include "gwpluginsmanager.h"

#include <gmodule.h>
#include <dirent.h> /* opendir readir closedir */
#include <string.h> /* strstr */

#include "gwapplicationmanager.h"
#include "gwhelper.h"


GWPluginsManager my_plugins_manager;


typedef struct gw_plugin_s {
	GModule *module;
	gpointer data;
}GWPlugin;


typedef gboolean (*func_gw_plugin_load_t)(GWPlugin*);
typedef gboolean (*func_gw_plugin_unload_t)(gchar*,GWPlugin*,gpointer);
typedef gchar* (*func_gw_plugin_key_t)(GWPlugin*);


GHashTable * gw_plugin_manager_load_plugins ( const gchar *directory, const gchar *extension, func_gw_plugin_load_t gw_plugin_load, func_gw_plugin_key_t gw_plugin_key) {
	GHashTable *plugins = NULL;
	DIR *plugins_dir = NULL;
	struct dirent *dentry = NULL;
	gchar *file_ext = NULL;
	gchar *module_path = NULL;
	GModule *module = NULL;
	GWPlugin *plugin = NULL;


	if ( directory != NULL ) {
		if ( extension != NULL) {
			if ( gw_plugin_load != NULL) {
				if ( gw_plugin_key != NULL) {
					// Creates the hashtable to store all the plugins
					plugins = g_hash_table_new ( g_str_hash, g_str_equal);

					// Tries to open the plugins directory
					if ( (plugins_dir = opendir ( directory)) != NULL ) {
						// Scans the plugins directory
						while ( (dentry = readdir ( plugins_dir)) != NULL ) {
							// Checks the file name
							if ( dentry->d_name != NULL ) {
								// Search the file extension
								if ( (file_ext = strrchr ( dentry->d_name, '.')) != NULL ) {
									// Checks if the file extension correspond to a plugin file
									if ( strcasecmp ( ++file_ext, extension) == 0 ) {
										// Builds the module (plugin) path
										module_path = g_strconcat ( directory, G_DIR_SEPARATOR_S, dentry->d_name, NULL);

										// Tries to load the found module
										if ( (module = g_module_open ( module_path, 0)) != NULL ) {
											// Checks if the plugin can be loaded and load it
											plugin = (GWPlugin*)g_malloc ( sizeof ( GWPlugin));
											memset ( plugin, '\0', sizeof ( GWPlugin));
											plugin->module = module;
											if ( gw_plugin_load ( plugin) == TRUE ) {
												g_hash_table_insert ( plugins, gw_plugin_key ( plugin), plugin);
											} else {
												g_free ( plugin);
												plugin = NULL;
											}
										} else {}

										g_free ( module_path);
									} else {}
								} else {}

								file_ext = NULL;
							} else {}
						}

						closedir ( plugins_dir);
					} else {}
				} else {}
			} else {}
		} else {}
	} else {}

	return plugins;
}


gboolean gw_plugin_load_catalog_plugin ( GWPlugin *plugin) {
	gboolean result = FALSE;
	GModule *module = NULL;
	GWCatalogPlugin *catalog_plugin = NULL;
	func_gw_plugin_get_info_t func_gw_plugin_get_info = NULL;
	func_gw_db_catalog_create_t func_gw_db_catalog_create = NULL;
	func_gw_db_catalog_open_t func_gw_db_catalog_open = NULL;
	func_gw_db_catalog_save_t func_gw_db_catalog_save = NULL;
	func_gw_db_catalog_close_t func_gw_db_catalog_close = NULL;
	func_gw_db_catalog_get_db_catalog_t func_gw_db_catalog_get_db_catalog = NULL;
	func_gw_db_catalog_get_db_category_t func_gw_db_catalog_get_db_category = NULL;
	func_gw_db_catalog_get_db_disk_t func_gw_db_catalog_get_db_disk = NULL;
	func_gw_db_catalog_get_db_file_t func_gw_db_catalog_get_db_file = NULL;
	func_gw_db_catalog_get_db_categories_t func_gw_db_catalog_get_db_categories = NULL;
	func_gw_db_catalog_get_db_disks_t func_gw_db_catalog_get_db_disks = NULL;
	func_gw_db_disk_get_db_files_t func_gw_db_disk_get_db_files = NULL;
	func_gw_db_file_get_db_files_t func_gw_db_file_get_db_files = NULL;
	func_gw_db_file_get_db_disk_t func_gw_db_file_get_db_disk = NULL;
	func_gw_db_file_get_parent_db_file_t func_gw_db_file_get_parent_db_file = NULL;
	func_gw_db_catalog_add_db_category_t func_gw_db_catalog_add_db_category = NULL;
	func_gw_db_catalog_add_db_disk_t func_gw_db_catalog_add_db_disk = NULL;
	func_gw_db_disk_add_db_file_t func_gw_db_disk_add_db_file = NULL;
	func_gw_db_file_add_db_file_t func_gw_db_file_add_db_file = NULL;
	func_gw_db_catalog_remove_db_category_t func_gw_db_catalog_remove_db_category = NULL;
	func_gw_db_catalog_remove_db_disk_t func_gw_db_catalog_remove_db_disk = NULL;
	func_gw_db_catalog_remove_db_file_t func_gw_db_catalog_remove_db_file = NULL;
	func_gw_db_catalog_update_t func_gw_db_catalog_update = NULL;
	func_gw_db_category_update_t func_gw_db_category_update = NULL;
	func_gw_db_disk_update_t func_gw_db_disk_update = NULL;
	func_gw_db_file_update_t func_gw_db_file_update = NULL;
	func_gw_db_catalog_get_nb_db_files_t func_gw_db_catalog_get_nb_db_files = NULL;
	func_gw_db_catalog_get_nb_db_folders_t func_gw_db_catalog_get_nb_db_folders = NULL;
	func_gw_db_catalog_get_nb_db_disks_t func_gw_db_catalog_get_nb_db_disks = NULL;
	func_gw_db_disk_get_nb_db_files_t func_gw_db_disk_get_nb_db_files = NULL;
	func_gw_db_disk_get_nb_db_folders_t func_gw_db_disk_get_nb_db_folders = NULL;
	func_gw_db_catalog_get_capacity_t func_gw_db_catalog_get_capacity = NULL;
	func_gw_db_catalog_get_full_t func_gw_db_catalog_get_full = NULL;
	func_gw_db_catalog_get_free_t func_gw_db_catalog_get_free = NULL;
	func_gw_db_catalog_get_db_category_by_index_t func_gw_db_catalog_get_db_category_by_index = NULL;
	func_gw_db_catalog_get_db_category_by_name_t func_gw_db_catalog_get_db_category_by_name = NULL;
	func_gw_db_catalog_get_db_disk_by_name_t func_gw_db_catalog_get_db_disk_by_name = NULL;
	func_gw_db_disk_get_db_file_by_name_t func_gw_db_disk_get_db_file_by_name = NULL;
	func_gw_db_file_get_db_file_by_name_t func_gw_db_file_get_db_file_by_name = NULL;
	func_gw_db_file_get_location_t func_gw_db_file_get_location = NULL;


	if ( (module = plugin->module) != NULL ) {
		g_module_symbol ( module, "plugin_get_info", (gpointer *)(&func_gw_plugin_get_info));
		g_module_symbol ( module, "plugin_db_catalog_create", (gpointer *)(&func_gw_db_catalog_create));
		g_module_symbol ( module, "plugin_db_catalog_open", (gpointer *)(&func_gw_db_catalog_open));
		g_module_symbol ( module, "plugin_db_catalog_save", (gpointer *)(&func_gw_db_catalog_save));
		g_module_symbol ( module, "plugin_db_catalog_close", (gpointer *)(&func_gw_db_catalog_close));
		g_module_symbol ( module, "plugin_db_catalog_get_capacity", (gpointer *)(&func_gw_db_catalog_get_capacity));
		g_module_symbol ( module, "plugin_db_catalog_get_full", (gpointer *)(&func_gw_db_catalog_get_full));
		g_module_symbol ( module, "plugin_db_catalog_get_free", (gpointer *)(&func_gw_db_catalog_get_free));
		g_module_symbol ( module, "plugin_db_catalog_get_nb_db_files", (gpointer *)(&func_gw_db_catalog_get_nb_db_files));
		g_module_symbol ( module, "plugin_db_catalog_get_nb_db_folders", (gpointer *)(&func_gw_db_catalog_get_nb_db_folders));
		g_module_symbol ( module, "plugin_db_catalog_get_nb_db_disks", (gpointer *)(&func_gw_db_catalog_get_nb_db_disks));
		g_module_symbol ( module, "plugin_db_catalog_get_db_catalog", (gpointer *)(&func_gw_db_catalog_get_db_catalog));
		g_module_symbol ( module, "plugin_db_catalog_get_db_category", (gpointer *)(&func_gw_db_catalog_get_db_category));
		g_module_symbol ( module, "plugin_db_catalog_get_db_disk", (gpointer *)(&func_gw_db_catalog_get_db_disk));
		g_module_symbol ( module, "plugin_db_catalog_get_db_file", (gpointer *)(&func_gw_db_catalog_get_db_file));
		g_module_symbol ( module, "plugin_db_catalog_get_db_categories", (gpointer *)(&func_gw_db_catalog_get_db_categories));
		g_module_symbol ( module, "plugin_db_catalog_get_db_disks", (gpointer *)(&func_gw_db_catalog_get_db_disks));
		g_module_symbol ( module, "plugin_db_disk_get_nb_db_files", (gpointer *)(&func_gw_db_disk_get_nb_db_files));
		g_module_symbol ( module, "plugin_db_disk_get_nb_db_folders", (gpointer *)(&func_gw_db_disk_get_nb_db_folders));
		g_module_symbol ( module, "plugin_db_disk_get_db_files", (gpointer *)(&func_gw_db_disk_get_db_files));
		g_module_symbol ( module, "plugin_db_file_get_db_files", (gpointer *)(&func_gw_db_file_get_db_files));
		g_module_symbol ( module, "plugin_db_catalog_get_db_category_by_index", (gpointer *)(&func_gw_db_catalog_get_db_category_by_index));
		g_module_symbol ( module, "plugin_db_catalog_get_db_category_by_name", (gpointer *)(&func_gw_db_catalog_get_db_category_by_name));
		g_module_symbol ( module, "plugin_db_catalog_get_db_disk_by_name", (gpointer *)(&func_gw_db_catalog_get_db_disk_by_name));
		g_module_symbol ( module, "plugin_db_disk_get_db_file_by_name", (gpointer *)(&func_gw_db_disk_get_db_file_by_name));
		g_module_symbol ( module, "plugin_db_file_get_db_file_by_name", (gpointer *)(&func_gw_db_file_get_db_file_by_name));
		g_module_symbol ( module, "plugin_db_file_get_db_disk", (gpointer *)(&func_gw_db_file_get_db_disk));
		g_module_symbol ( module, "plugin_db_file_get_parent_db_file", (gpointer *)(&func_gw_db_file_get_parent_db_file));
		g_module_symbol ( module, "plugin_db_file_get_location", (gpointer *)(&func_gw_db_file_get_location));
		g_module_symbol ( module, "plugin_db_catalog_add_db_category", (gpointer *)(&func_gw_db_catalog_add_db_category));
		g_module_symbol ( module, "plugin_db_catalog_add_db_disk", (gpointer *)(&func_gw_db_catalog_add_db_disk));
		g_module_symbol ( module, "plugin_db_disk_add_db_file", (gpointer *)(&func_gw_db_disk_add_db_file));
		g_module_symbol ( module, "plugin_db_file_add_db_file", (gpointer *)(&func_gw_db_file_add_db_file));
		g_module_symbol ( module, "plugin_db_catalog_remove_db_category", (gpointer *)(&func_gw_db_catalog_remove_db_category));
		g_module_symbol ( module, "plugin_db_catalog_remove_db_disk", (gpointer *)(&func_gw_db_catalog_remove_db_disk));
		g_module_symbol ( module, "plugin_db_catalog_remove_db_file", (gpointer *)(&func_gw_db_catalog_remove_db_file));
		g_module_symbol ( module, "plugin_db_catalog_update", (gpointer *)(&func_gw_db_catalog_update));
		g_module_symbol ( module, "plugin_db_category_update", (gpointer *)(&func_gw_db_category_update));
		g_module_symbol ( module, "plugin_db_disk_update", (gpointer *)(&func_gw_db_disk_update));
		g_module_symbol ( module, "plugin_db_file_update", (gpointer *)(&func_gw_db_file_update));

		if ( func_gw_plugin_get_info!=NULL &&
			func_gw_db_catalog_create!=NULL &&
			func_gw_db_catalog_open!=NULL &&
			func_gw_db_catalog_save!=NULL &&
			func_gw_db_catalog_close!=NULL &&
			func_gw_db_catalog_get_nb_db_files!=NULL &&
			func_gw_db_catalog_get_nb_db_folders!=NULL &&
			func_gw_db_catalog_get_nb_db_disks!=NULL &&
			func_gw_db_catalog_get_db_catalog!=NULL &&
			func_gw_db_catalog_get_db_category!=NULL &&
			func_gw_db_catalog_get_db_disk!=NULL &&
			func_gw_db_catalog_get_db_file!=NULL &&
			func_gw_db_catalog_get_db_categories!=NULL &&
			func_gw_db_catalog_get_db_disks!=NULL &&
			func_gw_db_disk_get_nb_db_files!=NULL &&
			func_gw_db_disk_get_nb_db_folders!=NULL &&
			func_gw_db_disk_get_db_files!=NULL &&
			func_gw_db_file_get_db_files!=NULL &&
			func_gw_db_file_get_db_disk!=NULL &&
			func_gw_db_file_get_parent_db_file!=NULL &&
			func_gw_db_catalog_add_db_category!=NULL &&
			func_gw_db_catalog_add_db_disk!=NULL &&
			func_gw_db_disk_add_db_file!=NULL &&
			func_gw_db_file_add_db_file!=NULL &&
			func_gw_db_catalog_remove_db_category!=NULL &&
			func_gw_db_catalog_remove_db_disk!=NULL &&
			func_gw_db_catalog_remove_db_file!=NULL &&
			func_gw_db_catalog_update!=NULL &&
			func_gw_db_category_update!=NULL &&
			func_gw_db_disk_update!=NULL &&
			func_gw_db_file_update!=NULL ) {

			if ( (catalog_plugin = (GWCatalogPlugin*)g_malloc ( sizeof ( GWCatalogPlugin))) != NULL ) {
				memset ( catalog_plugin, '\0', sizeof ( GWCatalogPlugin));
				catalog_plugin->gw_plugin_get_info = func_gw_plugin_get_info;
				catalog_plugin->gw_db_catalog_create = func_gw_db_catalog_create;
				catalog_plugin->gw_db_catalog_open = func_gw_db_catalog_open;
				catalog_plugin->gw_db_catalog_save = func_gw_db_catalog_save;
				catalog_plugin->gw_db_catalog_close = func_gw_db_catalog_close;
				if ( func_gw_db_catalog_get_capacity != NULL) {
					catalog_plugin->gw_db_catalog_get_capacity = func_gw_db_catalog_get_capacity;
				} else {
					catalog_plugin->gw_db_catalog_get_capacity = gw_helper_plugin_db_catalog_get_capacity;
				}
				if ( func_gw_db_catalog_get_full != NULL) {
					catalog_plugin->gw_db_catalog_get_full = func_gw_db_catalog_get_full;
				} else {
					catalog_plugin->gw_db_catalog_get_full = gw_helper_plugin_db_catalog_get_full;
				}
				if ( func_gw_db_catalog_get_free != NULL) {
					catalog_plugin->gw_db_catalog_get_free = func_gw_db_catalog_get_free;
				} else {
					catalog_plugin->gw_db_catalog_get_free = gw_helper_plugin_db_catalog_get_free;
				}
				catalog_plugin->gw_db_catalog_get_nb_db_files = func_gw_db_catalog_get_nb_db_files;
				catalog_plugin->gw_db_catalog_get_nb_db_folders = func_gw_db_catalog_get_nb_db_folders;
				catalog_plugin->gw_db_catalog_get_nb_db_disks = func_gw_db_catalog_get_nb_db_disks;
				catalog_plugin->gw_db_catalog_get_db_catalog = func_gw_db_catalog_get_db_catalog;
				catalog_plugin->gw_db_catalog_get_db_category = func_gw_db_catalog_get_db_category;
				catalog_plugin->gw_db_catalog_get_db_disk = func_gw_db_catalog_get_db_disk;
				catalog_plugin->gw_db_catalog_get_db_file = func_gw_db_catalog_get_db_file;
				catalog_plugin->gw_db_catalog_get_db_categories = func_gw_db_catalog_get_db_categories;
				catalog_plugin->gw_db_catalog_get_db_disks = func_gw_db_catalog_get_db_disks;
				catalog_plugin->gw_db_disk_get_nb_db_files = func_gw_db_disk_get_nb_db_files;
				catalog_plugin->gw_db_disk_get_nb_db_folders = func_gw_db_disk_get_nb_db_folders;
				catalog_plugin->gw_db_disk_get_db_files = func_gw_db_disk_get_db_files;
				catalog_plugin->gw_db_file_get_db_files = func_gw_db_file_get_db_files;
				if ( func_gw_db_catalog_get_db_category_by_index != NULL) {
					catalog_plugin->gw_db_catalog_get_db_category_by_index = func_gw_db_catalog_get_db_category_by_index;
				} else {
					catalog_plugin->gw_db_catalog_get_db_category_by_index = gw_helper_plugin_db_catalog_get_db_category_by_index;
				}
				if ( func_gw_db_catalog_get_db_category_by_name != NULL) {
					catalog_plugin->gw_db_catalog_get_db_category_by_name = func_gw_db_catalog_get_db_category_by_name;
				} else {
					catalog_plugin->gw_db_catalog_get_db_category_by_name = gw_helper_plugin_db_catalog_get_db_category_by_name;
				}
				if ( func_gw_db_catalog_get_db_disk_by_name != NULL) {
					catalog_plugin->gw_db_catalog_get_db_disk_by_name = func_gw_db_catalog_get_db_disk_by_name;
				} else {
					catalog_plugin->gw_db_catalog_get_db_disk_by_name = gw_helper_plugin_db_catalog_get_db_disk_by_name;
				}
				if ( func_gw_db_disk_get_db_file_by_name != NULL) {
					catalog_plugin->gw_db_disk_get_db_file_by_name = func_gw_db_disk_get_db_file_by_name;
				} else {
					catalog_plugin->gw_db_disk_get_db_file_by_name = gw_helper_plugin_db_disk_get_db_file_by_name;
				}
				if ( func_gw_db_file_get_db_file_by_name != NULL) {
					catalog_plugin->gw_db_file_get_db_file_by_name = func_gw_db_file_get_db_file_by_name;
				} else {
					catalog_plugin->gw_db_file_get_db_file_by_name = gw_helper_plugin_db_file_get_db_file_by_name;
				}
				catalog_plugin->gw_db_file_get_db_disk = func_gw_db_file_get_db_disk;
				catalog_plugin->gw_db_file_get_parent_db_file = func_gw_db_file_get_parent_db_file;
				if ( func_gw_db_file_get_location != NULL) {
					catalog_plugin->gw_db_file_get_location = func_gw_db_file_get_location;
				} else {
					catalog_plugin->gw_db_file_get_location = gw_helper_plugin_db_file_get_location;
				}
				catalog_plugin->gw_db_catalog_add_db_category = func_gw_db_catalog_add_db_category;
				catalog_plugin->gw_db_catalog_add_db_disk = func_gw_db_catalog_add_db_disk;
				catalog_plugin->gw_db_disk_add_db_file = func_gw_db_disk_add_db_file;
				catalog_plugin->gw_db_file_add_db_file = func_gw_db_file_add_db_file;
				catalog_plugin->gw_db_catalog_remove_db_category = func_gw_db_catalog_remove_db_category;
				catalog_plugin->gw_db_catalog_remove_db_disk = func_gw_db_catalog_remove_db_disk;
				catalog_plugin->gw_db_catalog_remove_db_file = func_gw_db_catalog_remove_db_file;
				catalog_plugin->gw_db_catalog_update = func_gw_db_catalog_update;
				catalog_plugin->gw_db_category_update = func_gw_db_category_update;
				catalog_plugin->gw_db_disk_update = func_gw_db_disk_update;
				catalog_plugin->gw_db_file_update = func_gw_db_file_update;
				plugin->data = catalog_plugin;

				result = TRUE;
			} else {}
		} else {}
	} else {}

	return result;
}


gboolean gw_plugin_unload_catalog_plugin ( gchar *key, GWPlugin *plugin, gpointer data) {
	gboolean result = TRUE;


	if ( key != NULL ) {
		g_free ( key);
	} else {}

	if ( plugin != NULL ) {
		if ( plugin->module != NULL ) {
			g_module_close ( plugin->module);
		} else {}

		g_free ( plugin);
	}

	return result;
}


gchar * gw_plugin_key_catalog_plugin ( GWPlugin *plugin) {
	gchar *key = NULL;


	GWCatalogPlugin *catalog_plugin = plugin->data;
	key = g_strdup ( gw_plugin_info_get_name ( catalog_plugin->gw_plugin_get_info ( )));

	return key;
}


gint gw_pm_init ( ) {
	gint result = -1;
	GModule *module = NULL;
	gchar *module_path = NULL;
	func_get_author_t func_get_author = NULL;
	func_get_info_t func_get_info = NULL;
	func_get_help_t func_get_help = NULL;
	func_get_allowed_ext_t func_get_allowed_ext = NULL;
	func_get_allowed_name_t func_get_allowed_name = NULL;
	func_get_file_descr_t func_get_file_descr = NULL;
	func_get_files_descr_t func_get_files_descr = NULL;
	func_get_parent_descr_t func_get_parent_descr = NULL;
	DIR *plugins_descr_dir = NULL;
	struct dirent *dentry = NULL;
	char *so = NULL;
	gchar **allowed_ext = NULL;
	gchar **allowed_name = NULL;
	int i = 0;
	gchar *plugins_dir = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( g_module_supported ( ) ) {
		if ( (my_plugins_manager.catalog_plugins = gw_plugin_manager_load_plugins ( gw_package_get_plugins_catalog_dir ( ), G_MODULE_SUFFIX, &gw_plugin_load_catalog_plugin, &gw_plugin_key_catalog_plugin)) != NULL) {
			/* Plugins are loaded. */
		} else {
			/* Plugins loading failed. */
		}

		my_plugins_manager.descr_plugins = g_hash_table_new ( g_str_hash, g_str_equal/*(GCompareFunc)strcasecmp*/);
		my_plugins_manager.file_descr_funcs = g_hash_table_new ( g_str_hash, g_str_equal/*(GCompareFunc)strcasecmp*/);
		my_plugins_manager.files_descr_funcs = g_hash_table_new ( g_str_hash, g_str_equal/*(GCompareFunc)strcasecmp*/);
		my_plugins_manager.parent_descr_funcs = g_hash_table_new ( g_str_hash, g_str_equal/*(GCompareFunc)strcasecmp*/);

#if GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Starting the scan of %s...", PACKAGE_PLUGINS_DESCRIPTION_DIR);
#endif

		if ( (plugins_dir = gw_package_get_plugins_description_dir ( )) != NULL ) {
			if ( (plugins_descr_dir = opendir ( plugins_dir)) != NULL ) {
				while ( (dentry = readdir ( plugins_descr_dir)) != NULL ) {
#if GW_DEBUG_MODE
					gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Current file is %s", dentry->d_name);
#endif

					if ( dentry->d_name != NULL ) {
#if GW_DEBUG_MODE
						gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Checking the file %s", dentry->d_name);
#endif

						if ( (so = strrchr ( dentry->d_name, '.')) != NULL ) {
#if GW_DEBUG_MODE
							gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "File extension is founded : %s", so);
#endif

							if ( strcasecmp ( ++so, G_MODULE_SUFFIX) == 0 ) {
								/* The file extension is a valid extension for module file. */
#if GW_DEBUG_MODE
								gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "The file extension founded is supported : %s.", so);
#endif
								module_path = g_strconcat ( PACKAGE_PLUGINS_DESCRIPTION_DIR, G_DIR_SEPARATOR_S, dentry->d_name, NULL);

#if GW_DEBUG_MODE
								gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Trying to load %s...", module_path);
#endif

								module = g_module_open ( module_path, 0);

								if ( module != NULL ) {
									g_module_symbol ( module, "plugin_get_author", (gpointer *)(&func_get_author));
									g_module_symbol ( module, "plugin_get_info", (gpointer *)(&func_get_info));
									g_module_symbol ( module, "plugin_get_help", (gpointer *)(&func_get_help));
									g_module_symbol ( module, "plugin_get_allowed_ext", (gpointer *)(&func_get_allowed_ext));
									g_module_symbol ( module, "plugin_get_allowed_name", (gpointer *)(&func_get_allowed_name));
									g_module_symbol ( module, "plugin_get_file_descr", (gpointer *)(&func_get_file_descr));
									g_module_symbol ( module, "plugin_get_files_descr", (gpointer *)(&func_get_files_descr));
									g_module_symbol ( module, "plugin_get_parent_descr", (gpointer *)(&func_get_parent_descr));

									if ( (func_get_author != NULL) && (func_get_info != NULL) && (func_get_help != NULL) ) {
#if GW_DEBUG_MODE
										gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Module name is %s", g_module_name ( module));
										gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Module author is %s", func_get_author ( )!=NULL?func_get_author ( ):"");
										gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Module info is %s", func_get_info ( )!=NULL?func_get_info ( ):"");
										gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Module help is %s", func_get_help ( )!=NULL?func_get_help ( ):"");
#endif

										if ( (func_get_allowed_ext != NULL) && (func_get_file_descr != NULL) ) {
#if GW_DEBUG_MODE
											gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Module allowed_ext is %s", func_get_allowed_ext ( ));
#endif

											if ( (func_get_allowed_ext ( ) != NULL) && (strlen ( func_get_allowed_ext ( )) > 0) ) {
												allowed_ext = g_strsplit ( func_get_allowed_ext ( ), "|", -1);

												if ( allowed_ext != NULL ) {
													for ( i = 0; allowed_ext[i] != NULL; i++) {
														g_hash_table_insert ( my_plugins_manager.descr_plugins, g_strdup ( func_get_allowed_ext ( )), module);
#if GW_DEBUG_MODE
														gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "plugin %s added", allowed_ext[i]);
#endif

														g_strdown ( allowed_ext[i]);
														g_hash_table_insert ( my_plugins_manager.file_descr_funcs, g_strdup ( allowed_ext[i]), func_get_file_descr);
													}

													g_strfreev ( allowed_ext);
													allowed_ext = NULL;
												}
											}
										}

										if ( (func_get_allowed_name != NULL) && (func_get_allowed_name ( ) != NULL) && ((func_get_files_descr != NULL) || (func_get_parent_descr != NULL)) ) {
#if GW_DEBUG_MODE
											gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Module allowed_name is %s", func_get_allowed_name ( ));
#endif

											if ( (func_get_allowed_name ( ) != NULL) && (strlen ( func_get_allowed_name ( )) > 0) ) {
												allowed_name = g_strsplit ( func_get_allowed_name ( ), "|", -1);

												if ( allowed_name != NULL ) {
													for ( i = 0; allowed_name[i] != NULL; i++) {
														g_hash_table_insert ( my_plugins_manager.descr_plugins, g_strdup ( func_get_allowed_name ( )), module);

														g_strdown ( allowed_name[i]);

														if ( func_get_files_descr != NULL ) {
															g_hash_table_insert ( my_plugins_manager.files_descr_funcs, g_strdup ( allowed_name[i]), func_get_files_descr);
#if GW_DEBUG_MODE
															gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "plugin %s added", allowed_name[i]);
#endif
														}

														if ( func_get_parent_descr != NULL ) {
															g_hash_table_insert ( my_plugins_manager.parent_descr_funcs, g_strdup ( allowed_name[i]), func_get_parent_descr);

#if GW_DEBUG_MODE
															gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "plugin %s added", allowed_name[i]);
#endif
														}
													}

													g_strfreev ( allowed_name);
													allowed_name = NULL;
												}
											}
										}
									}
								} else {
#if GW_DEBUG_MODE
									gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "unabble to load plugin %s, error :%s", dentry->d_name, g_module_error ( ));
#endif
								}

								g_free ( module_path);
								module_path = NULL;
							} else {
								/* The file extension is not supported as module file extension. */
#if GW_DEBUG_MODE
								gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "The file extension founded is not supported : %s.", so);
#endif
							}
						} else {
							/* Unable to find the file extension. */
#if GW_DEBUG_MODE
							gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "No file extension has been founded.", NULL);
#endif
						}

						so = NULL;
					} else {
						/* Unable to get the file name. */
#if GW_DEBUG_MODE
						gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "File name is null (inode=%d).", dentry->d_ino);
#endif
					}

				}

				closedir ( plugins_descr_dir);
			} else {
#if GW_DEBUG_MODE
				gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "%s not found.", PACKAGE_PLUGINS_DESCRIPTION_DIR);
#endif
			}

			g_free ( plugins_dir);
		}

#if GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Scan of %s is stopped.", PACKAGE_PLUGINS_DESCRIPTION_DIR);
#endif

		gw_pm_set_current_catalog_plugin ( gw_pm_get_default_catalog_plugin ( ));
	} else {
#if GW_DEBUG_MODE
		gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, "Dynamic modules are not supported!!");
#endif
	}

	return result;
}


gboolean gw_pm_module_close ( gchar * key, GModule *value, gpointer data) {
	gboolean result = FALSE;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( key != NULL ) {
		g_free ( key);
	}

	if ( value != NULL ) {
		g_module_close ( value);
	}

	return result;
}


gint gw_pm_get_file_descr_func ( const gchar *ext, func_get_file_descr_t *f) {
	gint result = -1;
	gchar *ext_lower = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (my_plugins_manager.file_descr_funcs != NULL) && (ext != NULL) ) {
		g_strdown ( ext_lower = g_strdup ( ext));
		*f = g_hash_table_lookup ( my_plugins_manager.file_descr_funcs, ext_lower);
		g_free ( ext_lower);
	}

	return result;
}


gint gw_pm_get_files_descr_func ( const gchar *name, func_get_files_descr_t *f) {
	gint result = -1;
	gchar *name_lower = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (my_plugins_manager.files_descr_funcs != NULL) && ( name != NULL) ) {
		g_strdown ( name_lower = g_strdup ( name));
		*f = g_hash_table_lookup ( my_plugins_manager.files_descr_funcs, name_lower);
		g_free ( name_lower);
	}

	return result;
}


gint gw_pm_get_parent_descr_func ( const gchar *name, func_get_parent_descr_t *f) {
	gint result = -1;
	gchar *name_lower = NULL;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( (my_plugins_manager.parent_descr_funcs != NULL) && (name != NULL) ) {
		g_strdown ( name_lower = g_strdup ( name));
		*f = g_hash_table_lookup ( my_plugins_manager.parent_descr_funcs, name_lower);
		g_free ( name_lower);
	}

	return result;
}


gint gw_pm_exit ( ) {
	gint result = -1;


#if GW_DEBUG_MODE
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, NULL);
#endif

	if ( my_plugins_manager.catalog_plugins != NULL ) {
//		g_hash_table_foreach_remove ( my_plugins_manager.catalog_plugins, (GHRFunc)gw_pm_module_close, NULL);
		g_hash_table_foreach_remove ( my_plugins_manager.catalog_plugins, (GHRFunc)gw_plugin_unload_catalog_plugin, NULL);
		g_hash_table_destroy ( my_plugins_manager.catalog_plugins);
		my_plugins_manager.catalog_plugins = NULL;
	}

	if ( my_plugins_manager.file_descr_funcs != NULL ) {
		g_hash_table_destroy ( my_plugins_manager.file_descr_funcs);
		my_plugins_manager.file_descr_funcs = NULL;
	}

	if ( my_plugins_manager.files_descr_funcs != NULL ) {
		g_hash_table_destroy ( my_plugins_manager.files_descr_funcs);
		my_plugins_manager.files_descr_funcs = NULL;
	}

	if ( my_plugins_manager.parent_descr_funcs != NULL ) {
		g_hash_table_destroy ( my_plugins_manager.parent_descr_funcs);
		my_plugins_manager.parent_descr_funcs = NULL;
	}

	if ( my_plugins_manager.descr_plugins != NULL ) {
		g_hash_table_foreach_remove ( my_plugins_manager.descr_plugins, (GHRFunc)gw_pm_module_close, NULL);
		g_hash_table_destroy ( my_plugins_manager.descr_plugins);
		my_plugins_manager.descr_plugins = NULL;
	}

	return result;
}


GWCatalogPlugin * gw_pm_get_catalog_plugin ( gchar* name) {
	GWCatalogPlugin * catalog_plugin = NULL;


	if ( my_plugins_manager.catalog_plugins != NULL) {
		GWPlugin *plugin = g_hash_table_lookup ( my_plugins_manager.catalog_plugins, name);

		if ( plugin != NULL) {
			catalog_plugin = plugin->data;
		} else {}
	} else {}


	return catalog_plugin;
}


GWCatalogPlugin * gw_pm_get_default_catalog_plugin ( ) {
	//TODO read the plugin name in the settings
	return gw_pm_get_catalog_plugin ( "GWhere catalog");
}


void gw_pm_add_plugin_name ( gpointer key, gpointer value, gpointer data) {
	gchar **names = data;
	gchar *name = key;
	GWPlugin *plugin = value;
	gint i = 0;


	if ( data!=NULL && key!=NULL) {
		/* Doesn't add the current catalog plugin */
		if ( plugin->data != gw_pm_get_current_catalog_plugin ( )) {
			for ( i = 0; names[i] != NULL; i++);
			names[i] = name;
		} else {}
	}
}


gchar ** gw_pm_get_all_catalog_import_plugin_name ( ) {
	gchar **names = NULL;
	gint i = 0, nb = 0;


	if ( my_plugins_manager.catalog_plugins != NULL ) {
		if ( (nb = g_hash_table_size ( my_plugins_manager.catalog_plugins)) > 0 ) {
			if ( gw_pm_get_current_catalog_plugin ( ) != NULL ) {
				nb--;
			}

			names = (gchar**)g_malloc0 ( sizeof ( gchar*) * ( nb + 1));
			for ( i = 0; i < (nb + 1); i++) names[i] = NULL;
			g_hash_table_foreach ( my_plugins_manager.catalog_plugins, (GHFunc)gw_pm_add_plugin_name, names);
		} else {}
	} else {}

	return names;
}


gchar ** gw_pm_get_all_catalog_export_plugin_name ( ) {
	gchar **names = NULL;
	gint i = 0, nb = 0;


	if ( my_plugins_manager.catalog_plugins != NULL ) {
		if ( (nb = g_hash_table_size ( my_plugins_manager.catalog_plugins)) > 0 ) {
			if ( gw_pm_get_current_catalog_plugin ( ) != NULL ) {
				nb--;
			}

			names = (gchar**)g_malloc0 ( sizeof ( gchar*) * ( nb + 1));
			for ( i = 0; i < (nb + 1); i++) names[i] = NULL;
			g_hash_table_foreach ( my_plugins_manager.catalog_plugins, (GHFunc)gw_pm_add_plugin_name, names);
		} else {}
	} else {}

	return names;
}


void gw_pm_set_current_catalog_plugin ( GWCatalogPlugin *ctg_plugin) {
	my_plugins_manager.current_ctg_plugin = ctg_plugin;
}


GWCatalogPlugin * gw_pm_get_current_catalog_plugin ( ) {
	return my_plugins_manager.current_ctg_plugin;
}


void gw_pm_set_selected_import_catalog_plugin ( GWCatalogPlugin *ctg_plugin) {
	my_plugins_manager.selected_import_ctg_pugin = ctg_plugin;
}


GWCatalogPlugin * gw_pm_get_selected_import_catalog_plugin ( ) {
	return my_plugins_manager.selected_import_ctg_pugin;
}


void gw_pm_set_selected_export_catalog_plugin ( GWCatalogPlugin *ctg_plugin) {
	my_plugins_manager.selected_export_ctg_pugin = ctg_plugin;
}


GWCatalogPlugin * gw_pm_get_selected_export_catalog_plugin ( ) {
	return my_plugins_manager.selected_export_ctg_pugin;
}

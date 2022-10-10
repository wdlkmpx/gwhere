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


/*!
 * \file gwcatalog.h
 * \brief This is the interface specification of catalog plugins.\n
 * A catalog plugin \e MUST implements the following functions in order to be
 * used by GWhere as plugin.
 *
 * \author Sébastien LECACHEUR <zero@gwhere.org>
 * \version 1.0
 * \date 2000-2005
 */


#ifndef GW_PLUGINS_CATALOG_H
#define GW_PLUGINS_CATALOG_H


#include "db/gwdb.h"
#include "gwplugininfo.h"


/*!
 * \brief A type definition for the catalog plugin functions.\n
 * This type definition is used by all the following functions.
 */
typedef struct gw_catalog_plugin_s GWCatalogPlugin;


/*!
 * \brief Returns all the catalog plugin information.
 * \return The new allocated GWPluginInfo object. It \e MUST be
 * free with the gw_plugin_info_free function.
 */
typedef GWPluginInfo* (*func_gw_plugin_get_info_t)(void);


/*!
 * \brief Creates a new catalog and returns the associated context.
 * \param plugin The plugin to use in order to create the catalog.
 * \param path The catalog path where to create the catalog.
 * \param mode The used mode for creation.
 * \return The new allocated GWDBContext object. It \e MUST be free
 * with the _gw_db_context_free function after calling the
 * func_gw_db_catalog_close_t function. Returns NULL if an error
 * occured.
 */
typedef GWDBContext* (*func_gw_db_catalog_create_t)(GWCatalogPlugin* plugin, const gchar* path, const gchar* mode);


/*!
 * \brief Opens an existing catalog and returns the associated context.
 * \param plugin The plugin to use in order to open the catalog.
 * \param path The catalog path to open.
 * \param mode The used mode for opening.
 * \return The new allocated GWDBContext object. It \e MUST be free
 * with the _gw_db_context_free function after calling the
 * func_gw_db_catalog_close_t function. Returns NULL if an error
 * occured.
 */
typedef GWDBContext* (*func_gw_db_catalog_open_t)(GWCatalogPlugin* plugin, const gchar* path, const gchar* mode);


/*!
 * \brief Saves the corresponding catalog of the given context.
 * \param context The context of the catalog to save.
 * \return 0 if the catalog is saved or if no need to be saved,
 * otherwise returns -1.
 */
typedef gint (*func_gw_db_catalog_save_t)(GWDBContext* context);


/*!
 * \brief Closes the given context.\n
 * It is used in order to free internal and private allocated objects
 * by the plugin.
 * \param context The context to close.
 * \return 0 if the context was correctly closed otherwise returns
 * -1.
 * \warning This function don't free the GWDBContext object.
 */
typedef gint (*func_gw_db_catalog_close_t)(GWDBContext* context);


/*!
 * \brief Returns the catalog information.
 * \param context The context to get catalog information.
 * \return A new allocated GWDBCatalog object otherwise returns NULL.
 * \warning The returned GWDBCatalog \e MUST be freed with the
 * gw_db_catalog_free function.
 */
typedef GWDBCatalog* (*func_gw_db_catalog_get_db_catalog_t)(GWDBContext* context);


/*!
 * \brief Returns the disk information.
 * \param context The context to get disk information.
 * \param ref The disk primary key to get information.
 * \return A new allocated GWDBDisk object otherwise returns NULL.
 * \warning The returned GWDBDisk \e MUST be freed with the
 * gw_db_disk_free function.
 */
typedef GWDBDisk* (*func_gw_db_catalog_get_db_disk_t)(GWDBContext* context, GWDBDiskPK ref);


/*!
 * \brief Returns the file information.
 * \param context The context to get file information.
 * \param ref The file primary key to get information.
 * \return A new allocated GWDBFile object otherwise returns NULL.
 * \warning The returned GWDBFile \e MUST be freed with the
 * gw_db_file_free function.
 */
typedef GWDBFile* (*func_gw_db_catalog_get_db_file_t)(GWDBContext* context, GWDBFilePK ref);


/*!
 * \brief Returns the category information.
 * \param context The context to get category information.
 * \param ref The category primary key to get information.
 * \return A new allocated GWDBCategory object otherwise returns NULL.
 * \warning The returned GWDBCategory \e MUST be free with the
 * gw_db_category_free function.
 */
typedef GWDBCategory* (*func_gw_db_catalog_get_db_category_t)(GWDBContext* context, GWDBCategoryPK ref);


/*!
 * \brief Returns all the categories information.
 * \param context The context to get all categories information.
 * \return New allocated array of GWDBCategory objects otherwise returns NULL.
 * The array ends with NULL pointer.
 * \warning All the returned GWDBCategory objects \e MUST be freed with the
 * gw_db_category_free function and the returned array \e MUST be freed with
 * the g_free function.
 */
typedef GWDBCategory** (*func_gw_db_catalog_get_db_categories_t)(GWDBContext* context);


/*!
 * \brief Returns all the disks information.
 * \param context The context to get all disks information.
 * \return New allocated array of GWDBDisk objects otherwise returns NULL.
 * The array ends with NULL pointer.
 * \warning All the returned GWDBDisk objects \e MUST be freed with the
 * gw_db_disk_free function and the returned array \e MUST be freed with
 * the g_free function.
 */
typedef GWDBDisk** (*func_gw_db_catalog_get_db_disks_t)(GWDBContext* context);


/*!
 * \brief Returns all the root files information of the given disk.
 * \param context The context to get all root files information.
 * \param ref The disk primary key to get all root files information.
 * \return New allocated array of GWDBFile objects otherwise returns NULL.
 * The array ends with NULL pointer.
 * \warning All the returned GWDBFile objects \e MUST be freed with the
 * gw_db_file_free function and the returned array \e MUST be freed with
 * the g_free function.
 */
typedef GWDBFile** (*func_gw_db_disk_get_db_files_t)(GWDBContext* context, GWDBDiskPK ref);


/*!
 * \brief Returns all the children files information of the given file.
 * \param context The context to get all children files information.
 * \param ref The file primary key to get all children files information.
 * \return New allocated array of GWDBFile objects otherwise returns NULL.
 * The array ends with NULL pointer.
 * \warning All the returned GWDBFile objects \e MUST be freed with the
 * gw_db_file_free function and the returned array \e MUST be freed with
 * the g_free function.
 */
typedef GWDBFile** (*func_gw_db_file_get_db_files_t)(GWDBContext* context, GWDBFilePK ref);


/*!
 * \brief Returns the disk information of the given file.
 * \param context The context to get the disk information.
 * \param ref The file primary key to get the disk information.
 * \return A new allocated GWDBDisk object otherwise returns NULL.
 * \warning The returned GWDBDisk object \e MUST be freed with the
 * gw_db_disk_free function.
 */
typedef GWDBDisk* (*func_gw_db_file_get_db_disk_t)(GWDBContext* context, GWDBFilePK ref);


/*!
 * \brief Returns the parent file information of the given file.
 * \param context The context to get the parent file information.
 * \param ref The file primary key to get the parent file information.
 * \return A new allocated GWDBFile object otherwise returns NULL.
 * \warning The returned GWDBFile object \e MUST be freed with the
 * gw_db_file_free function.
 */
typedef GWDBFile* (*func_gw_db_file_get_parent_db_file_t)(GWDBContext* context, GWDBFilePK ref);


/*!
 * \brief Adds the given category to the catalog.
 * \param context The context to add category.
 * \param category The category object to add.
 * \return The category primary key otherwise returns NULL.
 * \warning The given GWDBCategory object \e MUST be freed with the
 * gw_db_category_free function.
 * \warning The new primary key of the given object is setted.
 */
typedef GWDBCategoryPK (*func_gw_db_catalog_add_db_category_t)(GWDBContext* context, GWDBCategory* category);


/*!
 * \brief Adds the given disk to the catalog.
 * \param context The context to add disk.
 * \param disk The disk object to add.
 * \return The disk primary key otherwise returns NULL.
 * \warning The given GWDBDisk object \e MUST be freed with the
 * gw_db_disk_free function.
 * \warning The new primary key of the given object is setted.
 */
typedef GWDBDiskPK (*func_gw_db_catalog_add_db_disk_t)(GWDBContext* context, GWDBDisk* disk);


/*!
 * \brief Adds the given file to the root of given disk.
 * \param context The context to add file.
 * \param ref The disk primary key where to add file.
 * \param file The file object to add.
 * \return The file primary key otherwise returns NULL.
 * \warning The given GWDBFile object \e MUST be freed with the
 * gw_db_file_free function.
 * \warning The new primary key of the given object is setted.
 */
typedef GWDBFilePK (*func_gw_db_disk_add_db_file_t)(GWDBContext* context, GWDBDiskPK ref, GWDBFile* file);


/*!
 * \brief Adds the given file to the given parent file.
 * \param context The context to add file.
 * \param ref The parent file primary key where to add file.
 * \param file The file object to add.
 * \return The file primary key otherwise returns NULL.
 * \warning The given GWDBFile object \e MUST be freed with the
 * gw_db_file_free function.
 * \warning The new primary key of the given object is setted.
 */
typedef GWDBFilePK (*func_gw_db_file_add_db_file_t)(GWDBContext* context, GWDBFilePK ref, GWDBFile* file);


/*!
 * \brief Removes the given category from the catalog.
 * \param context The context to remove category.
 * \param ref The category primary key to remove.
 * \return 0 if the category was removed otherwise returns -1.
 */
typedef gint (*func_gw_db_catalog_remove_db_category_t)(GWDBContext* context, GWDBCategoryPK ref);


/*!
 * \brief Removes the given disk and all his files from the catalog.
 * \param context The context to remove disk.
 * \param ref The disk primary key to remove.
 * \return 0 if the disk and all his files were removed otherwise
 * returns -1.
 */
typedef gint (*func_gw_db_catalog_remove_db_disk_t)(GWDBContext* context, GWDBDiskPK ref);


/*!
 * \brief Removes the given file and all his sub-files from the catalog.
 * \param context The context to remove file.
 * \param ref The file primary key to remove.
 * \return 0 if the file and all his sub-files were removed otherwise
 * returns -1.
 */
typedef gint (*func_gw_db_catalog_remove_db_file_t)(GWDBContext* context, GWDBFilePK ref);


/*!
 * \brief Updates the given catalog.
 * \param context The context to update catalog.
 * \param catalog The catalog object to update.
 * \return O if the catalog was updated otherwise returns -1.
 * \warning The given GWDBCatalog \e MUST be freed with the
 * gw_db_catalog_free function.
 */
typedef gint (*func_gw_db_catalog_update_t)(GWDBContext* context, GWDBCatalog* catalog);


/*!
 * \brief Updates the given category.
 * \param context The context to update category.
 * \param category The category object to update.
 * \return 0 if the category was updated otherwise returns -1.
 * \warning The given GWDBCategory \e MUST be freed with the
 * gw_db_category_free function.
 */
typedef gint (*func_gw_db_category_update_t)(GWDBContext* context, GWDBCategory* category);


/*!
 * \brief Updates the given disk.
 * \param context The context to update disk.
 * \param disk The disk object to update.
 * \return 0 if the disk was updated otherwise returns -1.
 * \warning The given GWDBDisk \e MUST be freed with the
 * gw_db_disk_free function.
 */
typedef gint (*func_gw_db_disk_update_t)(GWDBContext* context, GWDBDisk* disk);


/*!
 * \brief Updates the given file.
 * \param context The context to update file.
 * \param file The file object to update.
 * \return 0 if the file was updated otherwise returns -1.
 * \warning The given GWDBFile \e MUST be freed with the
 * gw_db_file_free funtion.
 */
typedef gint (*func_gw_db_file_update_t)(GWDBContext* context, GWDBFile* file);


/* Can be optionals functions ? */


/*!
 * \brief Returns the number of files in the catalog.
 * \param context The context to get number of files.
 * \return The number of files otherwise returns 0.
 * \warning The number of files does not include folders but includes
 * all the "." and ".." files.
 */
typedef glong (*func_gw_db_catalog_get_nb_db_files_t)(GWDBContext* context);


/*!
 * \brief Returns the number of folders and sub-folders in the catalog.
 * \param context The context to get number of folders.
 * \return The number of folders and sub-folders otherwise returns
 * 0.
 * \todo Rename this function.
 */
typedef glong (*func_gw_db_catalog_get_nb_db_folders_t)(GWDBContext* context);


/*!
 * \brief Returns the number of disks in the catalog.
 * \param context The context to get number of disks.
 * \return The number of disks otherwise returns 0.
 */
typedef gint (*func_gw_db_catalog_get_nb_db_disks_t)(GWDBContext* context);


/*!
 * \brief Returns the number of files in the given disk.
 * \param context The context to get number of files.
 * \param ref The disk primary key to get number of files.
 * \return The number of files otherwise returns
 * 0.
 * \warning The number of files does not include folders but includes
 * all the "." and ".." files.
 */
typedef glong (*func_gw_db_disk_get_nb_db_files_t)(GWDBContext* context, GWDBDiskPK ref);


/*!
 * \brief Returns the number of folders and sub-folders in the given disk.
 * \param context The context to get number of folders.
 * \param ref The disk primary key to get number of folders.
 * \return The number of folders and sub-folders otherwise returns
 * 0.
 * \todo Rename this function.
 */
typedef glong (*func_gw_db_disk_get_nb_db_folders_t)(GWDBContext* context, GWDBDiskPK ref);


/* Optionals functions */
typedef guint64 (*func_gw_db_catalog_get_capacity_t)(GWDBContext*);// sum on all the gw_db_disk_get_capacity()
typedef guint64 (*func_gw_db_catalog_get_full_t)(GWDBContext*);// sum on all the gw_db_disk_get_full()
typedef guint64 (*func_gw_db_catalog_get_free_t)(GWDBContext*);// sum on all the gw_db_disk_get_free()
typedef GWDBCategory* (*func_gw_db_catalog_get_db_category_by_index_t)(GWDBContext*, gint);// gw_db_category_get_index(gw_db_catalog_get_db_categories())
typedef GWDBCategory* (*func_gw_db_catalog_get_db_category_by_name_t)(GWDBContext*, gchar*);// gw_db_category_get_name(gw_db_catalog_get_db_categories())
typedef GWDBDisk* (*func_gw_db_catalog_get_db_disk_by_name_t)(GWDBContext*, gchar*);// gw_db_disk_get_name(gw_db_catalog_get_db_disks())
typedef GWDBFile* (*func_gw_db_disk_get_db_file_by_name_t)(GWDBContext*, GWDBDiskPK, gchar*);// gw_db_file_get_name(gw_db_disk_get_db_files())
typedef GWDBFile* (*func_gw_db_file_get_db_file_by_name_t)(GWDBContext*, GWDBFilePK, gchar*);// gw_db_file_get_name(gw_db_file_get_db_files())
typedef gchar* (*func_gw_db_file_get_location_t)(GWDBContext*, GWDBFilePK);// while(gw_db_file_get_parent_db_file())


struct gw_catalog_plugin_s {
	func_gw_plugin_get_info_t gw_plugin_get_info;

	func_gw_db_catalog_create_t gw_db_catalog_create;
	func_gw_db_catalog_open_t gw_db_catalog_open;
	func_gw_db_catalog_save_t gw_db_catalog_save;
	func_gw_db_catalog_close_t gw_db_catalog_close;

	func_gw_db_catalog_get_db_catalog_t gw_db_catalog_get_db_catalog;
	func_gw_db_catalog_get_db_category_t gw_db_catalog_get_db_category;
	func_gw_db_catalog_get_db_disk_t gw_db_catalog_get_db_disk;
	func_gw_db_catalog_get_db_file_t gw_db_catalog_get_db_file;
	func_gw_db_catalog_get_db_categories_t gw_db_catalog_get_db_categories;
	func_gw_db_catalog_get_db_disks_t gw_db_catalog_get_db_disks;
	func_gw_db_disk_get_db_files_t gw_db_disk_get_db_files;
	func_gw_db_file_get_db_files_t gw_db_file_get_db_files;
	func_gw_db_file_get_db_disk_t gw_db_file_get_db_disk;
	func_gw_db_file_get_parent_db_file_t gw_db_file_get_parent_db_file;

	func_gw_db_catalog_add_db_category_t gw_db_catalog_add_db_category;
	func_gw_db_catalog_add_db_disk_t gw_db_catalog_add_db_disk;
	func_gw_db_disk_add_db_file_t gw_db_disk_add_db_file;
	func_gw_db_file_add_db_file_t gw_db_file_add_db_file;

	func_gw_db_catalog_remove_db_category_t gw_db_catalog_remove_db_category;
	func_gw_db_catalog_remove_db_disk_t gw_db_catalog_remove_db_disk;
	func_gw_db_catalog_remove_db_file_t gw_db_catalog_remove_db_file;

	func_gw_db_catalog_update_t gw_db_catalog_update;
	func_gw_db_category_update_t gw_db_category_update;
	func_gw_db_disk_update_t gw_db_disk_update;
	func_gw_db_file_update_t gw_db_file_update;

	func_gw_db_catalog_get_nb_db_files_t gw_db_catalog_get_nb_db_files;
	func_gw_db_catalog_get_nb_db_folders_t gw_db_catalog_get_nb_db_folders;
	func_gw_db_catalog_get_nb_db_disks_t gw_db_catalog_get_nb_db_disks;
	func_gw_db_disk_get_nb_db_files_t gw_db_disk_get_nb_db_files;
	func_gw_db_disk_get_nb_db_folders_t gw_db_disk_get_nb_db_folders;

	func_gw_db_catalog_get_capacity_t gw_db_catalog_get_capacity;
	func_gw_db_catalog_get_full_t gw_db_catalog_get_full;
	func_gw_db_catalog_get_free_t gw_db_catalog_get_free;
	func_gw_db_catalog_get_db_category_by_index_t gw_db_catalog_get_db_category_by_index;
	func_gw_db_catalog_get_db_category_by_name_t gw_db_catalog_get_db_category_by_name;
	func_gw_db_catalog_get_db_disk_by_name_t gw_db_catalog_get_db_disk_by_name;
	func_gw_db_disk_get_db_file_by_name_t gw_db_disk_get_db_file_by_name;
	func_gw_db_file_get_db_file_by_name_t gw_db_file_get_db_file_by_name;
	func_gw_db_file_get_location_t gw_db_file_get_location;
};


#endif

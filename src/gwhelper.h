/*  GWhere
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
 * @header	gwhelper.h
 * 		GWhere<br>
 * 		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 * 		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 * 		This component was developed for the GWhere project.<br>
 * 		It's a tool to work on the catalog tree.<br>
 * @abstract	This is the catalog tree tool.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwhelper.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_HELPER_H
#define GW_HELPER_H


#include "data/gwdata.h"
#include "db/gwdb.h"
#include "gwpluginsmanager.h"


/*!
 * @function	gw_catalog_get_total_disks
 * @abstract	Gets the number of disks in the catalog.
 * @discussion	This function gets the number of disks in the catalog tree.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @result	the number of disks.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_catalog_get_total_disks ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_catalog_get_total_folders
 * @abstract	Gets the number of folders in the catalog.
 * @discussion	This function gets the number of folders in the catalog tree.
 * 		It's the number of all folders (and subfolders).
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @result	the number of folders.<br>
 *		Returns -1 when an error occured.
 */
gint gw_catalog_get_total_folders ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_catalog_get_total_files
 * @abstract	Gets the number of files in the catalog.
 * @discussion	This function gets the number of files in the catalog tree.
 * 		It's the number of files in all folders (and subfolders).
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @result	the number of files.<br>
 *		Returns <i>-1</i> when an error occured.
 */
//gint gw_catalog_get_total_files ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_catalog_get_total_capacity
 * @abstract	Gets the total capacity of the catalog.
 * @discussion	This function gets the total capacity of the catalog. This
 * 		capacity is based on each capacity disk.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @result	the total capacity of catalog.<br>
 *		Returns <i>-1</i> when an error occured.
 */
//long double gw_catalog_get_total_capacity ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_catalog_get_total_used_space
 * @abstract	Gets the total used space of the catalog.
 * @discussion	This function gets the total used space of the catalog. This
 * 		capacity is based on used space of each disk.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @result	the total used space of catalog.<br>
 *		Returns <i>-1</i> when an error occured.
 */
//long double gw_catalog_get_total_used_space ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_catalog_get_total_free_space
 * @abstract	Gets the total free space of the catalog.
 * @discussion	This function gets the total free space of the catalog. This
 * 		capacity is based on free space of each disk.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @result	the total free space of catalog.<br>
 *		Returns <i>-1</i> when an error occured.
 */
//long double gw_catalog_get_total_free_space ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_catalog_get_num_disk_with_type
 * @abstract	Gets the number of disks of one type.
 * @discussion	This function gets the number of disks of one type.<br>
 *		"Other" is the type for all other unreconized disk type.<br>
 *		<b>Warning</b> : this function is too CRAZY!! To used even if
 * 		you know what you do.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @param	type		the disk type to select
 * @result	the number of disks of this type.<br>
 *		Returns <i>-1</i> when an error occured.
 */
//gint gw_catalog_get_num_disk_with_type ( GtkCTree *ctree, GtkCTreeNode *node, gchar *type);


/*!
 * @function	gw_disk_get_total_folders
 * @abstract	Gets the number of folders in the disk.
 * @discussion	This function gets the number of folders in the disk in the
 * 		catalog tree. It's the number of all folders (and subfolders).
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the disk root
 * @result	the number of folders.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_disk_get_total_folders ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_disk_get_total_files
 * @abstract	Gets the number of files in the disk.
 * @discussion	This function gets the number of files in the disk in the catalog
 * 		tree. It's the number of files in all folders (and subfolders).
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the disk root
 * @result	the number of files.<br>
 *		Returns <i>-1</i> when an error occured. */
//gint gw_disk_get_total_files ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_disk_get_max_num
 * @abstract	Gets the number of files in the disk.
 * @discussion	This function gets the biggest disk number archive.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the catalog root
 * @result	the max number archive disk.<br>
 *		Returns <i>-1</i> when an error occured.
 */
//gint gw_disk_get_max_num ( GtkCTree *ctree, GtkCTreeNode *root);


/*!
 * @function	gw_disk_name_is_exist
 * @abstract	Gets if the disk name exist
 * @discussion	This function gets if the disk name is allready used by another disk.
 *		<b>Warning</b> : in future new parameters => GtkCTree, GtkCTreeNode!!
 * @param	name	the disk name
 * @result	is exist or no.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
//gboolean gw_disk_name_is_exist ( gchar *name);


/*!
 * @function	gw_disk_num_is_exist
 * @abstract	Gets if the disk number archive exist
 * @discussion	This function gets if the disk number archive is allready used by another disk.
 *		<b>Warning</b> : in future new parameters => GtkCTree, GtkCTreeNode!!
 * @param	name	the disk number archive
 * @result	is exist or no.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
//gboolean gw_disk_num_is_exist ( gint num);


/*!
 * @function	gw_folder_get_catalog
 * @abstract	Gets the catalog of the folder
 * @discussion	This function gets the catalog of the folder.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the folder
 * @result	the node in the tree where is the catalog root.
 */
GtkCTreeNode * gw_folder_get_catalog ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_folder_get_disk
 * @abstract	Gets the disk of the folder
 * @discussion	This function gets the disk of the folder.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the folder
 * @result	the node in the tree where is the disk root.<br>
 * 		Returns <i>NULL</i> when an error occured.
 */
GtkCTreeNode * gw_folder_get_disk ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_folder_get_disk_name
 * @abstract	Gets the disk name of the folder
 * @discussion	This function gets the disk name of the folder.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the folder
 * @result	the disk name. Must be freed with g_free().<br>
 * 		Returns <i>NULL</i> when an error occured.
 */
//gchar * gw_folder_get_disk_name ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_folder_get_disk_type
 * @abstract	Gets the disk type of the folder
 * @discussion	This function gets the disk type of the folder.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the folder
 * @result	the disk type. Must be freed with g_free().<br>
 * 		Returns <i>NULL</i> when an error occured.
 */
//gchar * gw_folder_get_disk_type ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_folder_get_location_on_disk
 * @abstract	Gets the folder location on the disk
 * @discussion	This function gets the folder location on the disk.
 * @param	ctree		the tree where is the catalog
 * @param	node		the node in the tree where is the folder
 * @result	the full location of the folder. Must be freed with g_free().<br>
 * 		Returns <i>NULL</i> when an error occured.
 */
//gchar * gw_folder_get_location_on_disk ( GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_disk_get_num_archive
 * @abstract	Checks if the disk number archive is valid
 * @discussion	This function checks if the disk number archive is valid. In order to be valid
 *		the number archive must be unique. If is not valid the function generates a valid
 *		number archive. This new number archive is not an allready used number archive.
 *		It's calculed with : gw_disk_get_max_num + 1.<br>
 *		If the archive number is valid the function returns this number.
 * @param	num		the number archive
 * @result	a valid number archive.<br>
 *		Returns <i>-1</i> when an error occured.
 */
//gint gw_disk_get_num_archive ( gchar *num);


/*!
 * @function	gw_disk_get_name
 * @abstract	Checks if the disk name is valid
 * @discussion	This function checks if the disk name is valid. In order to be valid
 *		the name must be unique. If is not valid the function generates a valid
 *		name. This new name is not an allready used name.
 *		It's calculed with : "name ( i)" (where i is an incremental number).<br>
 *		If the name is valid the function returns this name.
 * @param	num		the name
 * @result	a valid name. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
//gchar * gw_disk_get_name ( gchar *name);


/*!
 * @function	gw_folder_name_is_exist
 * @abstract	Gets if the folder name exist
 * @discussion	This function gets if the folder name is already used by another folder
 * 		or file (in the same parent folder).
 *		<b>Warning</b> : in future new parameters => GtkCTree, GtkCTreeNode!!
 * @param	name	the folder name
 * @result	is exist or no.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
//gboolean gw_folder_name_is_exist ( GtkCTreeNode *folder, gchar *name);


gboolean gw_helper_db_catalog_is_open ( );
gboolean gw_helper_db_catalog_is_open_and_modified ( );


gchar * gw_helper_db_catalog_get_usefull_name ( GWDBCatalog *catalog);
gchar * gw_helper_db_catalog_get_full_name ( GWDBCatalog *catalog);


gboolean gw_helper_db_catalog_is_new ( GWDBCatalog *catalog);


GdkPixmap * gw_helper_db_disk_get_pixmap ( GWDBDisk *disk);
GdkBitmap * gw_helper_db_disk_get_bitmap ( GWDBDisk *disk);


GWDBDiskType gw_helper_db_disk_get_db_type ( GWDBDisk *disk);
gint gw_helper_db_catalog_get_nb_db_disk_of_type ( GWDBContext *context, GWDBDiskType type);


gboolean gw_helper_db_disk_num_is_exist ( GWDBContext *context, gint num);
gint gw_helper_db_disk_get_max_num ( GWDBContext *context);
gint gw_helper_db_disk_get_num_archive ( GWDBContext *context, gchar *num);

gboolean gw_helper_db_disk_name_is_exist ( GWDBContext *context, gchar *name);
gchar * gw_helper_db_disk_get_name ( GWDBContext *context, gchar *name);

gboolean gw_helper_db_file_name_is_exist ( GWDBContext *context, GWDBFilePK file, gchar *name);


guint64 gw_helper_plugin_db_catalog_get_capacity ( GWDBContext *context);
guint64 gw_helper_plugin_db_catalog_get_full ( GWDBContext *context);
guint64 gw_helper_plugin_db_catalog_get_free ( GWDBContext *context);
GWDBCategory * gw_helper_plugin_db_catalog_get_db_category_by_index ( GWDBContext *context, gint index);
GWDBCategory * gw_helper_plugin_db_catalog_get_db_category_by_name ( GWDBContext *context, gchar *name);
GWDBDisk * gw_helper_plugin_db_catalog_get_db_disk_by_name ( GWDBContext *context, gchar *name);
GWDBFile * gw_helper_plugin_db_disk_get_db_file_by_name ( GWDBContext *context, GWDBDiskPK ref, gchar *name);
GWDBFile * gw_helper_plugin_db_file_get_db_file_by_name ( GWDBContext *context, GWDBFilePK ref, gchar *name);
gchar * gw_helper_plugin_db_file_get_location ( GWDBContext *context, GWDBFilePK ref);


gchar * gw_helper_db_file_get_cdate_to_str ( GWDBFile *file);
gchar * gw_helper_db_file_get_adate_to_str ( GWDBFile *file);
gchar * gw_helper_db_file_get_mdate_to_str ( GWDBFile *file);
gchar * gw_helper_db_disk_get_date_to_str ( GWDBDisk *disk);


/*!
 * @function	gw_helper_search_item_info_get_date_to_str
 * @abstract	Gets the formated search item date.
 * @discussion	This function gets the formated search item information date.<br>
 * @param	si	the search item information to get formated date
 * @result	The formated date. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_helper_search_item_info_date_to_str ( struct search_item_info *si);


#endif

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
 * @header	gwcatalogmanager.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br>
 *		It's a tool to load/save from/to a file formated to the GWhere file format.<br>
 *		Goto to specification for file format specifications.<br><br>
 *		Catalogs are compressed this the zlib.<br>
 * @abstract	This is the catalog loader component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		gwdata.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwcatalogmanager.c
 * @author	Author <zero@gwhere.org>
 * @author	Luis PARRAVICINI : zlib patch
 */


#ifndef GW_CATALOG_MANAGER_H
#define GW_CATALOG_MANAGER_H

#include <zlib.h>

#include "data/gwdata.h"
#include "gwpluginsmanager.h"


GWDBContext * current_catalog_context;


gint gw_cm_load ( /*GWCatalogPlugin *plugin,*/ GWDBContext *context);
gint gw_cm_add_disk ( struct scan_disk_info *scan_disk);
gint gw_cm_add_dir ( struct scan_disk_info *scan_disk, gchar *directory, GWDBDisk *disk, GWDBFile *parent, GList **forbidden);


/*!
 * @function	catalog_load_file
 * @abstract	Loads a catalog file.
 * @discussion	This function creates the catalog's tree from a GWhere format file.
 * @param	catalog_info	the catalog's datas
 * @param	ctree			the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_load_file ( struct catalog_file_info *catalog_info, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_load_file_version_1
 * @abstract	Loads a catalog file.
 * @discussion	This function creates the catalog's tree from a GWhere format file from a file formated with file version 1.<br>
 *		Goto to specification for file format specifications.<br>
 * @param	catalog_info	the catalog's datas
 * @param	fic		the file source descriptor
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_load_file_version_1 ( struct catalog_file_info *catalog_info, gzFile fic, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_load_file_version_2
 * @abstract	Loads a catalog file.
 * @discussion	This function creates the catalog's tree from a GWhere format file from a file formated with file version 2.<br>
 *		Goto to specification for file format specifications.<br>
 * @param	catalog_info	the catalog's datas
 * @param	fic		the file source descriptor
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @param	sb		the used string buffer to read catalog file
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_load_file_version_2 ( struct catalog_file_info *catalog_info, gzFile fic, GtkCTree *ctree, GtkCTreeNode *parent, GWStringBuffer *sb);


/*!
 * @function	catalog_load_disk_1
 * @abstract	Loads a disk from catalog file.
 * @discussion	This function loads a disk to the catalog's tree from a GWhere format file from a file formated with file version 1.<br>
 *		Goto to specification for file format specifications.<br>
 * @param	fic		the file source descriptor
 * @param	ctree		the tree where disk will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	returns the number under directories.<br>
 */
//gint catalog_load_disk_1 ( gzFile fic, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_load_disk_2
 * @abstract	Loads a disk from catalog file.
 * @discussion	This function loads a disk to the catalog's tree from a GWhere format file from a file formated with file version 2.<br>
 *		Goto to specification for file format specifications.<br>
 * @param	fic		the file source descriptor
 * @param	ctree		the tree where disk will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @param	sb		the string buffer used to read the catalog file
 * @result	returns the number under directories.<br>
 */
//gint catalog_load_disk_2 ( gzFile fic, GtkCTree *ctree, GtkCTreeNode *parent, GWStringBuffer *sb);


/*!
 * @function	catalog_load_dir_1
 * @abstract	Loads a directory from catalog file.
 * @discussion	This function loads a directory to the catalog's tree from a GWhere format file from a file formated with file version 1.<br>
 *		Goto to specification for file format specifications.<br>
 * @param	fic		the file source descriptor
 * @param	ctree		the tree where directory will be loaded
 * @param	parent		the node in the tree where is the parent directory is
 * @result	returns the number under directories.<br>
 */
 //gint catalog_load_dir_1 ( gzFile fic, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_load_dir_2
 * @abstract	Loads a directory from catalog file.
 * @discussion	This function loads a directory to the catalog's tree from a GWhere format file from a file formated with file version 2.<br>
 *		Goto to specification for file format specifications.<br>
 * @param	fic		the file source descriptor
 * @param	ctree		the tree where directory will be loaded
 * @param	parent		the node in the tree where is the parent directory is
 * @param	sb		the string buffer used to read the catalog file
 * @result	returns the number under directories.<br>
 */
//gint catalog_load_dir_2 ( gzFile fic, GtkCTree *ctree, GtkCTreeNode *parent, GWStringBuffer *sb);


/*!
 * @function	catalog_add_disk
 * @abstract	This function adds a disk to the catalog.
 * @discussion	This function adds a disk to the catalog's tree.<br>
 * @param	scan_disk	the ScanDiskInfo to scan
 * @param	ctree		the tree where the disk will be added
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_add_disk ( struct scan_disk_info *scan_disk, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_add_dir
 * @abstract	This function adds a directory to the catalog.
 * @discussion	This function adds a directory to the catalog's tree.<br>
 * @param	scan_disk	the scan disk
 * @param	directory		the directory name to add
 * @param	dir_info		the directory informations
 * @param	ctree		the tree where the disk will be added
 * @param	parent		the node in the tree where is the catalog root
 * @param	forbidden	the list of forbidden directory to not scan
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_add_dir ( struct scan_disk_info *scan_disk, gchar *directory, struct dir_info *dir_info, GtkCTree *ctree, GtkCTreeNode *parent, GList **forbidden);


/*!
 * @function	catalog_save_file
 * @abstract	Saves a catalog to a file.
 * @discussion	This function saves the catalog's tree to a GWhere format file.
 * @param	file		the file name to save
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_save_file ( gchar *file, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_save_file_version_1
 * @abstract	Saves a catalog to a file.
 * @discussion	This function saves the catalog's tree to a GWhere format file from a file formated with file version 1.<br>
 * @param	file		the file name to save
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_save_file_version_1 ( gchar *file, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_save_file_version_2
 * @abstract	Saves a catalog to a file.
 * @discussion	This function saves the catalog's tree to a GWhere format file from a file formated with file version 2.<br>
 * @param	file		the file name to save
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_save_file_version_2 ( gchar *file, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_save_file_disk_1
 * @abstract	Saves a disk to a file.
 * @discussion	This function saves the disk in the catalog's tree to a GWhere format file from a file formated with file version 1.<br>
 * @param	file		the file name to save
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_save_file_disk_1 ( gint fic, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_save_file_disk_2
 * @abstract	Saves a disk to a file.
 * @discussion	This function saves the disk in the catalog's tree to a GWhere format file from a file formated with file version 2.<br>
 * @param	file		the file name to save
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_save_file_disk_2 ( gint fic, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_save_file_dir_1
 * @abstract	Saves a directory to a file.
 * @discussion	This function saves the directory in the catalog's tree to a GWhere format file from a file formated with file version 1.<br>
 * @param	file		the file name to save
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_save_file_dir_1 ( gint fic, GtkCTree *ctree, GtkCTreeNode *parent);


/*!
 * @function	catalog_save_file_dir_2
 * @abstract	Saves a directory to a file.
 * @discussion	This function saves the directory in the catalog's tree to a GWhere format file from a file formated with file version 2.<br>
 * @param	file		the file name to save
 * @param	ctree		the tree where catalog will be loaded
 * @param	parent		the node in the tree where is the catalog root
 * @param	buf		the used string buffer to encode all string to file format
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
//gint catalog_save_file_dir_2 ( gzFile fic, GtkCTree *ctree, GtkCTreeNode *parent, GWStringBuffer *buf[2]);


/*!
 * @function	catalog_ctree_data_free
 * @abstract	Frees all data's ctree.
 * @discussion	This function frees all datas allocated for the ctree. These datas are attached to each node of the catalog's tree in order to list all files.<br>
 * @param	p		the list of datas
 * @result	an error code.<br>
 *		Returns 0 when it's done.<br>
 *		Returns -1 when an error occured.<br>
 */
gint catalog_ctree_data_free ( GList *p);


/*!
 * @function	catalog_disk_info_new_from_table
 * @abstract	Creates a new disk information from a catalog file.
 * @discussion	This function creates a new disk information from table readed in a catalog file and from a file version. It's an allocation function.
 * @param	attrib		the table of attributes
 * @param	file_version	the number of file version
 * @result	a pointer to the disk information structure.<br>
 */
//struct disk_info * catalog_disk_info_new_from_table ( gchar **attrib, gint file_version);


/*!
 * @function	catalog_disk_info_new_from_str
 * @abstract	Creates a new disk information from a catalog file.
 * @discussion	This function creates a new disk information from string readed in a catalog file and from a file version. It's an allocation function.
 * @param	str		the string of attributes
 * @param	file_version	the number of file version
 * @param	catalog_info	the catalog which contains some needed categories
 * @result	a pointer to the disk information structure.<br>
 */
//struct disk_info * catalog_disk_info_new_from_str ( gchar *str, gint file_version, struct catalog_file_info *catalog_info);


/*!
 * @function	catalog_disk_info_to_file
 * @abstract	Makes a string to save disk informations.
 * @discussion	This function makes a formated string to save disk informations in a file.
 * @param	p		the disk informations to save
 * @param	file_version	the file version to save disk informations
 * @result	the string to save.<br>
 *		Returns <i>null</i> when an error occured.<br>
 */
//gchar * catalog_disk_info_to_file ( struct disk_info *p, gint file_version);


/*!
 * @function	catalog_file_info_new_from_table
 * @abstract	Creates a new file information from a catalog file.
 * @discussion	This function creates a new file information from table readed in a catalog file and from a file version. It's an allocation function.
 * @param	attrib		the table of attributes
 * @param	folder		indicates if this is a folder
 * @param	file_version	the number of file version
 * @param	catalog_info	the catalog which contains some needed categories
 * @result	a pointer to the file information structure.<br>
 */
//struct file_info * catalog_file_info_new_from_table ( gchar **attrib, gboolean folder, gint file_version);


/*!
 * @function	catalog_file_info_new_from_str
 * @abstract	Creates a new file information from a catalog file.
 * @discussion	This function creates a new file information from a string readed in a catalog file and from a file version. It's an allocation function.
 * @param	str		the string of attributes
 * @param	file_version	the number of file version
 * @param	catalog_info	the catalog which contains some needed categories
 * @result	a pointer to the file information structure.<br>
 */
//struct file_info * catalog_file_info_new_from_str ( gchar *str, gint file_version, struct catalog_file_info *catalog_info);


/*!
 * @function	catalog_file_info_to_file
 * @abstract	Makes a string to save file informations.
 * @discussion	This function makes a formated string to save file informations in a file.
 * @param	p			the file informations to save
 * @param	file_version		the file version to save file informations
 * @result	the string to save.<br>
 *		Returns <i>null</i> when an error occured.<br>
 */
//gchar * catalog_file_info_to_file ( struct file_info *p, gint file_version);


void gw_cm_catalog_copy_folder ( GWDBContext *ictx, GWDBContext *octx, GWDBFilePK ifolder, GWDBFilePK ofolder);


#endif

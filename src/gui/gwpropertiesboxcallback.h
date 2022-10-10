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
 * @header	gwpropertiesboxcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for properties box callbacks.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		gwdata.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwpropertiesboxcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_PROPERTIES_BOX_CALLBACK_H
#define GW_GUI_GW_PROPERTIES_BOX_CALLBACK_H


#include "data/gwdata.h"


/*!
 * @function	gw_properties_box_catalog_ok
 * @abstract	Validates the catalog properties box and closes it.
 * @discussion	This function validates the catalog properties box and closes it.
 * @param	b	invoker button
 * @param	w	main window
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_properties_box_catalog_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_properties_box_disk_ok
 * @abstract	Validates the disk properties box and closes it.
 * @discussion	This function validates the disk properties box and closes it.
 * @param	b	invoker button
 * @param	w	main window
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_properties_box_disk_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_properties_box_folder_ok
 * @abstract	Validates the folder properties box and closes it.
 * @discussion	This function validates the folder properties box and closes it.
 * @param	b	invoker button
 * @param	w	main window
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_properties_box_folder_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_properties_box_file_ok
 * @abstract	Validates the file properties box and closes it.
 * @discussion	This function validates the file properties box and closes it.
 * @param	b	invoker button
 * @param	w	main window
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_properties_box_file_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_properties_box_catalog_name_check
 * @abstract	Checks if the catalog name was changed and sets the new value.
 * @discussion	This function check if catalog name was changed and sets the new value.
 * @param	w	properties box
 * @param	node	node in tree of the catalog
 * @param	catalog_info	catalog file info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_catalog_name_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog);


/*!
 * @function	gw_properties_box_catalog_description_check
 * @abstract	Checks if the catalog description was changed and sets the new value.
 * @discussion	This function check if catalog description was changed and sets the new value.
 * @param	w	properties box
 * @param	node	node in tree of the catalog
 * @param	catalog_info	catalog file info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_catalog_description_check ( GtkWidget *w, GWDBCatalog *catalog);


/*!
 * @function	gw_properties_box_disk_name_check
 * @abstract	Checks if the disk name was changed and sets the new value.
 * @discussion	This function check if disk name was changed and sets the new value.
 * @param	w	properties box
 * @param	node	node in tree of the disk
 * @param	catalog_info	catalog file info
 * @param	disk_info	disk info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_disk_name_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk);


/*!
 * @function	gw_properties_box_disk_num_archive_check
 * @abstract	Checks if the disk number archive was changed and sets the new value.
 * @discussion	This function check if disk number archive was changed and sets the new value.
 * @param	w	properties box
 * @param	node	node in tree of the disk
 * @param	catalog_info	catalog file info
 * @param	disk_info	disk info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_disk_num_archive_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk);


/*!
 * @function	gw_properties_box_disk_category_check
 * @abstract	Checks if the disk category was changed and sets the new value.
 * @discussion	This function check if disk category was changed and sets the new value.
 * @param	w	properties box
 * @param	node	node in tree of the disk
 * @param	catalog_info	catalog file info
 * @param	disk_info	disk info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_disk_category_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk);


/*!
 * @function	gw_properties_box_disk_description_check
 * @abstract	Checks if the disk description was changed and sets the new value.
 * @discussion	This function check if disk description was changed and sets the new value.
 * @param	w	properties box
 * @param	node	node in tree of the disk
 * @param	catalog_info	catalog file info
 * @param	disk_info	disk info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_disk_description_check ( GtkWidget *w, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk);


/*!
 * @function	gw_properties_box_folder_category_check
 * @abstract	Checks if the folder category was changed and sets the new value.
 * @discussion	This function check if folder category was changed and sets the new value.
 * @param	w	properties box
 * @param	catalog_info	catalog file info
 * @param	file_info	folder info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_folder_category_check ( GtkWidget *w, GWDBFile *folder);


/*!
 * @function	gw_properties_box_folder_description_check
 * @abstract	Checks if the folder description was changed and sets the new value.
 * @discussion	This function check if folder description was changed and sets the new value.
 * @param	w	properties box
 * @param	catalog_info	catalog file info
 * @param	folder_info	folder info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_folder_description_check ( GtkWidget *w, GWDBFile *folder);


/*!
 * @function	gw_properties_box_file_category_check
 * @abstract	Checks if the file category was changed and sets the new value.
 * @discussion	This function check if file category was changed and sets the new value.
 * @param	w	properties box
 * @param	catalog_info	catalog file info
 * @param	file_info	file info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_file_category_check ( GtkWidget *w, GWDBFile *file);


/*!
 * @function	gw_properties_box_file_description_check
 * @abstract	Checks if the file description was changed and sets the new value.
 * @discussion	This function check if file description was changed and sets the new value.
 * @param	w	properties box
 * @param	catalog_info	catalog file info
 * @param	file_info	file info
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_properties_box_file_description_check ( GtkWidget *w, GWDBFile *file);


#endif

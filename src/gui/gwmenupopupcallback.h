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
 * @header	gwenupopupcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a link component between menu popup and functionalities.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/02/11
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwmenupopupcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_MENU_POPUP_CALLBACK_H
#define GW_GUI_GW_MENU_POPUP_CALLBACK_H


/*!
 * @function	gw_menu_popup_catalog_rename
 * @abstract	Launches the renaming of a catalog.
 * @discussion	This function launches the renaming of a catalog.
 * @param	m	menu item invoker
 * @param	node	node of the catalog in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_catalog_rename ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_catalog_rename_ok
 * @abstract	Validates the renaming of a catalog.
 * @discussion	This function validates the renaming of a catalog.
 * @param	w	button invoker
 * @param	data	the capture box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_catalog_rename_ok ( GtkWidget *w, GtkWidget *data);


/*!
 * @function	gw_menu_popup_catalog_add_new_disk
 * @abstract	Goes to add a new disk in the catalog.
 * @discussion	This function goes to add a new disk in the catalog.<br>
 *		<b>Warning</b> : not yet implemented!!
 * @param	w	button invoker
 * @param	node	node of the catalog in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_catalog_add_new_disk ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_catalog_edit_description
 * @abstract	Launches the description edition of a catalog.
 * @discussion	This function launches the description edition of a catalog.
 * @param	m	menu item invoker
 * @param	node	node of the catalog in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_catalog_edit_description ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_catalog_edit_description_ok
 * @abstract	Validates the description edition of a catalog.
 * @discussion	This function validates the description edition of a catalog.
 * @param	b	button invoker
 * @param	w	the text box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_catalog_edit_description_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_menu_popup_catalog_edit_categories
 * @abstract	Launches the categories edition.
 * @discussion	This function launches the categories edition.
 * @param	m	menu item invoker
 * @param	node	node of the catalog in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_catalog_edit_categories ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_catalog_properties
 * @abstract	Shows the catalog properties.
 * @discussion	This function shows the catalog properties.
 * @param	m	menu item invoker
 * @param	node	node of the catalog in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_catalog_properties ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_disk_move_to
 * @abstract	Goes to the selected disk.
 * @discussion	This function goes to the selected disk.
 * @param	m	menu item invoker
 * @param	node	node of the selected disk in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_move_to ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_disk_rename
 * @abstract	Launches the renaming of a disk.
 * @discussion	This function launches the renaming of a disk.
 * @param	m	menu item invoker
 * @param	node	node of the disk in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_rename ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_disk_rename_ok
 * @abstract	Validates the renaming of a disk.
 * @discussion	This function validates the renaming of a disk.
 * @param	w	button invoker
 * @param	data	the capture box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_rename_ok ( GtkWidget *w, GtkWidget *data);


/*!
 * @function	gw_menu_popup_disk_delete
 * @abstract	Removes the selected disk from the catalog.
 * @discussion	This function removes the selected disk from the catalog.
 * @param	m	menu item invoker
 * @param	node	node of the disk in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_delete ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_disk_change_volume_label
 * @abstract	Launches the volume label disk editing.
 * @discussion	This function launches the volume label disk editing.
 * @param	m	menu item invoker
 * @param	node	node of the disk in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_change_volume_label ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_disk_change_volume_label_ok
 * @abstract	Validates the volume label disk editing.
 * @discussion	This function validates the volume label disk editing.
 * @param	w	button invoker
 * @param	data	the capture box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_change_volume_label_ok ( GtkWidget *w, GtkWidget *data);


/*!
 * @function	gw_menu_popup_disk_edit_description
 * @abstract	Launches the description edition of a disk.
 * @discussion	This function launches the description edition of a disk.
 * @param	m	menu item invoker
 * @param	node	node of the disk in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_edit_description ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_disk_edit_description_ok
 * @abstract	Validates the description edition of a disk.
 * @discussion	This function validates the description edition of a disk.
 * @param	b	button invoker
 * @param	w	the text box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_edit_description_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_menu_popup_disk_properties
 * @abstract	Shows the disk properties.
 * @discussion	This function shows the disk properties.
 * @param	m	menu item invoker
 * @param	node	node of the disk in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_disk_properties ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_folder_move_to
 * @abstract	Goes to the selected folder.
 * @discussion	This function goes to the selected folder.
 * @param	m	menu item invoker
 * @param	node	node of the selected folder in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_folder_move_to ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_folder_rename
 * @abstract	Launches the renaming of a folder.
 * @discussion	This function launches the renaming of a folder.
 * @param	m	menu item invoker
 * @param	node	node of the folder in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_folder_rename ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_folder_rename_ok
 * @abstract	Validates the renaming of a folder.
 * @discussion	This function validates the renaming of a folder.
 * @param	w	button invoker
 * @param	data	the capture box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_folder_rename_ok ( GtkWidget *w, GtkWidget *data);


/*!
 * @function	gw_menu_popup_folder_edit_description
 * @abstract	Launches the description edition of a folder.
 * @discussion	This function launches the description edition of a folder.
 * @param	m	menu item invoker
 * @param	node	node of the folder in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_folder_edit_description ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_folder_edit_description_ok
 * @abstract	Validates the description edition of a folder.
 * @discussion	This function validates the description edition of a folder.
 * @param	b	button invoker
 * @param	w	the text box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_folder_edit_description_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_menu_popup_folder_remove
 * @abstract	Removes the selected folder from the catalog.
 * @discussion	This function removes the selected folder from the catalog.
 * @param	m	menu item invoker
 * @param	node	node of the folder in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_folder_remove ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_folder_properties
 * @abstract	Shows the folder properties.
 * @discussion	This function shows the folder properties.
 * @param	m	menu item invoker
 * @param	node	node of the folder in the tree
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_folder_properties ( GtkMenuItem *m, GtkCTreeNode *node);


/*!
 * @function	gw_menu_popup_file_rename
 * @abstract	Launches the renaming of a file name.
 * @discussion	This function launches the renaming of a file name.
 * @param	m	menu item invoker
 * @param	row	row of the file in the list
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_file_rename ( GtkMenuItem *m, gpointer row);


/*!
 * @function	gw_menu_popup_file_rename_ok
 * @abstract	Validates the renaming of a file name.
 * @discussion	This function validates the renaming of a file name.
 * @param	b	button invoker
 * @param	w	the text box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_file_rename_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_menu_popup_file_edit_description
 * @abstract	Launches the description edition of a file.
 * @discussion	This function launches the description edition of a file.
 * @param	m	menu item invoker
 * @param	row	row of the file in the list
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_file_edit_description ( GtkMenuItem *m, gpointer row);


/*!
 * @function	gw_menu_popup_file_edit_description_ok
 * @abstract	Validates the description edition of a file.
 * @discussion	This function validates the description edition of a file.
 * @param	b	button invoker
 * @param	w	the text box
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_file_edit_description_ok ( GtkWidget *b, GtkWidget *w);


/*!
 * @function	gw_menu_popup_file_remove
 * @abstract	Removes the selected file from the catalog.
 * @discussion	This function removes the selected file from the catalog.
 * @param	m	menu item invoker
 * @param	rowe	row of the file in the list
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_file_remove ( GtkMenuItem *m, gpointer row);


/*!
 * @function	gw_menu_popup_file_properties
 * @abstract	Shows the file properties.
 * @discussion	This function shows the file properties.
 * @param	m	menu item invoker
 * @param	row	row of the file in the list
 * @result	is the event submited correctly.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_menu_popup_file_properties ( GtkMenuItem *m, gpointer row);


#endif

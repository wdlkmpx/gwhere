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
 * @header	gwpropertiesbox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for properties box.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		gwdata.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwpropertiesbox.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_PROPERTIES_BOX_H
#define GW_GUI_GW_PROPERTIES_BOX_H


#include "data/gwdata.h"


/*! @define	GW_PROPERTIES_TYPE_CATALOG	The type "catalog" for properties box */
#define GW_PROPERTIES_TYPE_CATALOG 0
/*! @define	GW_PROPERTIES_TYPE_DISK	The type "disk" for properties box */
#define GW_PROPERTIES_TYPE_DISK 1
/*! @define	GW_PROPERTIES_TYPE_FOLDER	The type "folder" for properties box */
#define GW_PROPERTIES_TYPE_FOLDER 2
/*! @define	GW_PROPERTIES_TYPE_FILE	The type "file" for properties box */
#define GW_PROPERTIES_TYPE_FILE 3


/*!
 * @function	gw_properties_box_create
 * @abstract	Creates a properties box.
 * @discussion	This function creates a properties box. Don't
 *		use this generic function. It more careful to
 *		use the following functions :<br>
 *		<ul>
 *			<li>gw_properties_box_create_catalog</li>
 *			<li>gw_properties_box_create_disk</li>
 *			<li>gw_properties_box_create_folder</li>
 *			<li>gw_properties_box_create_file</li>
 *		</ul>
 * @param	w		main window
 * @param	ctree		catalog tree
 * @param	node		relative tree root node
 * @param	what		kind of properties box
 * @param	files		files list
 * @result	the properties box.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_properties_box_create ( GtkWindow *w, GtkCTree *ctree, GtkCTreeNode *node, gint what, GWDBFile *file);


/*!
 * @function	gw_properties_box_create_catalog
 * @abstract	Creates a catalog properties box.
 * @discussion	This function creates a catalog properties box.
 * @param	m		invoker
 * @param	w		main window
 * @param	ctree		catalog tree
 * @param	node		catalog node in tree
 * @result	the catalog properties box.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_properties_box_create_catalog ( GtkMenuItem *m, GtkWindow *w, GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_properties_box_create_disk
 * @abstract	Creates a disk properties box.
 * @discussion	This function creates a disk properties box.
 * @param	m		invoker
 * @param	w		main window
 * @param	ctree		catalog tree
 * @param	node		disk node in tree
 * @result	the disk properties box.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_properties_box_create_disk ( GtkMenuItem *m, GtkWindow *w, GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_properties_box_create_folder
 * @abstract	Creates a folder properties box.
 * @discussion	This function creates a folder properties box.
 * @param	m		invoker
 * @param	w		main window
 * @param	ctree		catalog tree
 * @param	node		folder node in tree
 * @result	the folder properties box.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_properties_box_create_folder ( GtkMenuItem *m, GtkWindow *w, GtkCTree *ctree, GtkCTreeNode *node);


/*!
 * @function	gw_properties_box_create_file
 * @abstract	Creates a file properties box.
 * @discussion	This function creates a file properties box.
 * @param	m		invoker
 * @param	w		main window
 * @param	ctree		catalog tree
 * @param	node		file node in tree
 * @param	files		files list
 * @result	the file properties box.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_properties_box_create_file ( GtkMenuItem *m, GtkWindow *w, GtkCTree *ctree, GtkCTreeNode *node, GWDBFile *files);


/*!
 * @function	gw_properties_box_create_notebook_panel_catalog_info
 * @abstract	Creates a tabbed pane for catalog properties box.
 * @discussion	This function creates a tabbed pane for catalog properties box.
 * @param	w			main window
 * @param	notebook		notebook
 * @param	ctree			catalog tree
 * @param	node			catalog node in tree
 * @param	catalog_file_info	catalog file info
 * @result	the notebook.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkNotebook * gw_properties_box_create_notebook_panel_catalog_info ( GtkWindow *w, GtkNotebook *notebook, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog);


/*!
 * @function	gw_properties_box_create_notebook_panel_disk_info
 * @abstract	Creates a tabbed pane for disk properties box.
 * @discussion	This function creates a tabbed pane for disk properties box.
 * @param	w			main window
 * @param	notebook		notebook
 * @param	ctree			catalog tree
 * @param	node			disk node in tree
 * @param	catalog_file_info	catalog file info
 * @result	the notebook.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkNotebook * gw_properties_box_create_notebook_panel_disk_info ( GtkWindow *w, GtkNotebook *parent, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBDisk *disk);


/*!
 * @function	gw_properties_box_create_notebook_panel_folder_info
 * @abstract	Creates a tabbed pane for folder properties box.
 * @discussion	This function creates a tabbed pane for catalog properties box.
 * @param	w			main window
 * @param	notebook		notebook
 * @param	ctree			catalog tree
 * @param	node			folder node in tree
 * @param	catalog_file_info	catalog file info
 * @result	the notebook.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
//GtkNotebook * gw_properties_box_create_notebook_panel_folder_info ( GtkWindow *w, GtkNotebook *notebook, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog);
GtkNotebook * gw_properties_box_create_notebook_panel_folder_info ( GtkWindow *w, GtkNotebook *notebook, GWDBCatalog *catalog, GWDBDisk *disk, GWDBFile *folder);


/*!
 * @function	gw_properties_box_create_notebook_panel_file_info
 * @abstract	Creates a tabbed pane for file properties box.
 * @discussion	This function creates a tabbed pane for file properties box.
 * @param	w			main window
 * @param	notebook		notebook
 * @param	ctree			catalog tree
 * @param	node			file node in tree
 * @param	catalog_file_info	catalog file info
 * @param	files			files list
 * @result	the notebook.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkNotebook * gw_properties_box_create_notebook_panel_file_info ( GtkWindow *w, GtkNotebook *notebook, GtkCTree *ctree, GtkCTreeNode *node, GWDBCatalog *catalog, GWDBFile *file);


/*!
 * @function	gw_properties_box_get_catalog_name
 * @abstract	Gets the catalog name.
 * @discussion	This function gets the catalog name.
 * @param	w		properties box
 * @result	the catalog name. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_properties_box_get_catalog_name ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_catalog_category
 * @abstract	Gets the catalog category.
 * @discussion	This function gets the catalog category.
 * @param	w		properties box
 * @result	the catalog category.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
//GWDBCategory * gw_properties_box_get_catalog_category ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_catalog_description
 * @abstract	Gets the catalog description.
 * @discussion	This function gets the catalog description.
 * @param	w		properties box
 * @result	the catalog description. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_properties_box_get_catalog_description ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_disk_name
 * @abstract	Gets the disk name.
 * @discussion	This function gets the disk name.
 * @param	w		properties box
 * @result	the disk name. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_properties_box_get_disk_name ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_disk_num
 * @abstract	Gets the disk archive number.
 * @discussion	This function gets the disk archive number.
 * @param	w		properties box
 * @result	the disk archive number. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_properties_box_get_disk_num ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_disk_category
 * @abstract	Gets the disk category.
 * @discussion	This function gets the disk category.
 * @param	w		properties box
 * @result	the disk category.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GWDBCategoryPK gw_properties_box_get_disk_category_ref ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_disk_description
 * @abstract	Gets the disk description.
 * @discussion	This function gets the disk description.
 * @param	w		properties box
 * @result	the disk description. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_properties_box_get_disk_description ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_folder_category
 * @abstract	Gets the folder category.
 * @discussion	This function gets the folder category.
 * @param	w		properties box
 * @result	the folder category.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GWDBCategoryPK gw_properties_box_get_folder_category_ref ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_folder_description
 * @abstract	Gets the folder description.
 * @discussion	This function gets the folder description.
 * @param	w		properties box
 * @result	the folder description. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_properties_box_get_folder_description ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_file_category
 * @abstract	Gets the file category.
 * @discussion	This function gets the file category.
 * @param	w		properties box
 * @result	the file category.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GWDBCategoryPK gw_properties_box_get_file_category_ref ( GtkWidget *w);


/*!
 * @function	gw_properties_box_get_file_description
 * @abstract	Gets the file description.
 * @discussion	This function gets the file description.
 * @param	w		properties box
 * @result	the file description. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_properties_box_get_file_description ( GtkWidget *w);


#endif

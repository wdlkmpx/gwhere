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
 * @header	gwnotebookcatalog.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for the pane of catalog explorer in the main notebook.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/02/13
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwnotebookcatalog.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_NOTEBOOK_CATALOG_H
#define GW_GUI_GW_NOTEBOOK_CATALOG_H


/*!
 * @function	gw_notebook_catalog_create
 * @abstract	Creates a catalog explorer notebook pane.
 * @discussion	This function creates a catalog explorer notebook pane.
 * @param	w		refence to the main window
 * @result	the catalog explorer notebook pane.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_notebook_catalog_create ( GtkWindow *w);


/*!
 * @function	gw_notebook_catalog_create_and_add
 * @abstract	Creates a catalog explorer notebook pane and adds it to the notebook.
 * @discussion	This function creates a catalog explorer notebook pane and adds it to the notebook.
 * @param	w		refence to the main window
 * @param	parent		reference to the container
 * @result	the catalog explorer notebook pane.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_notebook_catalog_create_and_add ( GtkWindow *w, GtkNotebook * parent);


/*!
 * @function	gw_notebook_catalog_get_clist_explorer
 * @abstract	Gets the list of the catalog explorer.
 * @discussion	This function gets the list of catalog explorer.
 * @param	w		refence to the main window
 * @result	the list of catalog explorer.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkCList * gw_notebook_catalog_get_clist_explorer ( GtkWindow *w);


/*!
 * @function	gw_notebook_catalog_clist_explorer_set_column_title_file
 * @abstract	Sets the catalog clist explorer title column for files.
 * @discussion	This function sets the catalog clist explorer title column for files.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_catalog_clist_explorer_set_column_title_file ( void);


/*!
 * @function	gw_notebook_catalog_clist_explorer_set_column_title_disk
 * @abstract	Sets the catalog clist explorer title column for disks.
 * @discussion	This function sets the catalog clist explorer title column for disks.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_catalog_clist_explorer_set_column_title_disk ( void);


/*!
 * @function	gw_notebook_catalog_ctree_node_get_child
 * @abstract	Gets a special child in the node
 * @discussion	This functions gets the child with a special name in the node.<br>
 * @param	node	the node to get the child
 * @param	name	the child name
 * @result	Returns the node when search match.<br>
 *		Returns <i>NULL</i> when don't find child or when an error occured.
 */
GtkCTreeNode * gw_notebook_catalog_ctree_node_get_child  ( GtkCTreeNode *node, gchar *name);


/*!
 * @function	gw_notebook_catalog_ctree_node_get_num_children
 * @abstract	Gets the number of children in the node
 * @discussion	This functions gets the number of children in the node. Number of children is the number of subfolders in the folde.r<br>
 * @param	node	the node to get the number of children
 * @result	the number of chidren.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_catalog_ctree_node_get_num_children ( GtkCTreeNode *node);


/*!
 * @function	gw_notebook_catalog_ctree_destroy_all
 * @abstract	Destroys the tree
 * @discussion	This function destroys the tree and frees all datas structures used for catalog.<br>
 *		This function is call when the user close a catalog.
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_catalog_ctree_destroy_all ( void);


/*!
 * @function	gw_notebook_catalog_get_hpan_position
 * @abstract	Gets the horizontal pane position
 * @discussion	This function gets the horizontal pane position
 * @result	Returns the horizontal pane position.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_catalog_get_hpan_position ( GtkWindow *w);


#endif

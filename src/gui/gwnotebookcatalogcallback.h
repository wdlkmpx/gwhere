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
 * @header	gwnotebookcatalogcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is the graphical catalog explorer component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwnotebookcatalogcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_NOTEBOOK_CATALOG_CALLBACK_H
#define GW_GUI_GW_NOTEBOOK_CATALOG_CALLBACK_H


/*!
 * @function	gw_notebook_catalog_set_column_sort
 * @abstract	Sets the sort algorithm.
 * @discussion	This function sets the sort algorithm.
 * @param	clist		catalog file list clist
 * @param	column		column to sort
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_catalog_set_column_sort ( GtkCList *clist, gint column);


/*!
 * @function	gw_notebook_catalog_column_sort
 * @abstract	Sorts the column as ascending or descending.
 * @discussion	This function sorts the column as ascending or descending.
 * @param	clist		catalog file list clist
 * @param	column		column to sort
 * @param	data		unused at time
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_catalog_column_sort ( GtkCList *clist, gint column, gpointer data);


/*!
 * @function	gw_notebook_catalog_clist_button_press_event
 * @abstract	Loads the list of files.
 * @discussion	This function loads the list of files whitch are in the
 *		selected folder or disk (or loads the list of disk if is
 *		a catalog that was selected).<br>
 *		This function call when the user click on a item in the
 *		list of file (or disk).<br>
 * @param	w	the source widget event
 * @param	event	the event
 * @result	Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_catalog_clist_button_press_event ( GtkWidget *w, GdkEventButton *event);


/*!
 * @function	gw_notebook_catalog_clist_column_resized
 * @abstract	Saves the column width.
 * @discussion	This function saves the column width.<br>
 *		This function call when the user click on a item in the
 *		list of file (or disk).<br>
 * @param	clist	the column list source invoker
 * @param	column	the column number
 * @param	width	the new column width
 * @param	data	unused data
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_catalog_clist_column_resized ( GtkCList *clist, gint column, gint width, gpointer data);


/*!
 * @function	gw_notebook_catalog_ctree_button_press_event
 * @abstract	Loads the list of files.
 * @discussion	This function loads the list of files whitch are in the
 *		selected folder or disk (or loads the list of disk if is
 *		a catalog that was selected).<br>
 *		This function call when the user click on a item in the
 *		tree.<br>
 * @param	w	the source widget event
 * @param	event	the event
 * @result	Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_catalog_ctree_button_press_event ( GtkWidget *w, GdkEventButton *event);


/*!
 * @function	gw_notebook_catalog_ctree_select_row
 * @abstract	Loads the list of files.
 * @discussion	This function loads the list of files whitch are in the
 *		selected folder or disk (or loads the list of disk if is
 *		a catalog that was selected).<br>
 *		This function call when the user select on a item in the
 *		tree.<br>
 * @param	ctree	the tree
 * @param	noeud	the node selected
 * @param	colonne	the column
 * @param	p	a void pointer (in order to send datas structure).
 * @result	Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_catalog_ctree_select_row ( GtkCTree *ctree, GtkCTreeNode *noeud, gint colonne, gpointer g);


/*!
 * @function	gw_notebook_catalog_ctree_node_get_folder_size
 * @abstract	Gets the size of folder
 * @discussion	This functions gets the size of the selected folder.<br>
 * @param	ctree	the tree where is the folder
 * @param	node	the node
 * @result	the size of folder.<br>
 *		Returns <i>0</i> when an error occured.<br>
 */
//gulong gw_notebook_catalog_ctree_node_get_folder_size ( GtkCTree *ctree, GtkCTreeNode *node);


#endif

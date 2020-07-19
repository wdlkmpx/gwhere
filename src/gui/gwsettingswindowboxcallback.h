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
 * @header	gwsettingswindowboxcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI callback component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwsettingswindowboxcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_SETTINGS_WINDOW_BOX_CALLBACK_H
#define GW_GUI_GW_SETTINGS_WINDOW_BOX_CALLBACK_H


/*!
 * @typedef	func_gw_settings_window_box_notebook_apply_t
 *		This function is called when settings are applied.
 * @abstract	Functions specification
 * @param	settings	the parent window of plugin
 */
typedef gint (*func_gw_settings_window_box_notebook_apply_t)( GtkWindow *settings);


/*!
 * @function	gw_settings_window_box_tree_select_row
 * @abstract	Loads the requested plugin.
 * @discussion	This function loads the requested plugin. This function
 *		is called when user select a plugin in the exploration
 *		tree.
 * @param	ctree	the exploration tree
 * @param	node	the selected node in tree
 * @param	column	the column of the selected node in tree
 * @param	w	the settings window box
 */
void gw_settings_window_box_tree_select_row ( GtkCTree *ctree, GList *node, gint column, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_tree_unselect_row
 * @abstract	Checks with a settings is modified.
 * @discussion	This function checks with a settings is modified. This function
 *		is called when user unselect a plugin in the exploration
 *		tree.
 * @param	ctree	the exploration tree
 * @param	node	the selected node in tree
 * @param	column	the column of the selected node in tree
 * @param	w	the settings window box
 */
void gw_settings_window_box_tree_unselect_row ( GtkCTree *ctree, GList *node, gint column, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_tree_expand
 * @abstract	Does nothing at this time.
 * @discussion	This function does nothing at this time. This function
 *		is called when user expand a node in the exploration
 *		tree.
 * @param	ctree	the exploration tree
 * @param	node	the selected node in tree
 * @param	w	the settings window box
 */
void gw_settings_window_box_tree_expand ( GtkCTree *ctree, GList *node, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_tree_collapse
 * @abstract	Does nothing at this time.
 * @discussion	This function does nothing at this time. This function
 *		is called when user collapse a node in the exploration
 *		tree.
 * @param	ctree	the exploration tree
 * @param	node	the selected node in tree
 * @param	w	the settings window box
 */
void gw_settings_window_box_tree_collapse ( GtkCTree *ctree, GList *node, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_tree_move
 * @abstract	Does nothing at this time.
 * @discussion	This function does nothing at this time. This function
 *		is called when user move a node in the exploration
 *		tree.
 * @param	ctree		the exploration tree
 * @param	node		the selected node in tree
 * @param	new_parent	the new node's parent
 * @param	new_siblng	the new node's sibling
 * @param	w		the settings window box
 */
void gw_settings_window_box_tree_move ( GtkCTree *ctree, GList *node, GList *new_parent, GList *new_sibling, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_tree_change_focus_row_expansion
 * @abstract	Does nothing at this time.
 * @discussion	This function does nothing at this time.
 * @param	ctree		the exploration tree
 * @param	expansion	the tree expansion type
 * @param	w		the settings window box
 */
void gw_settings_window_box_tree_change_focus_row_expansion ( GtkCTree *ctree, GtkCTreeExpansionType expansion, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_noteboox_settings_switch_page
 * @abstract	Does nothing at this time.
 * @discussion	his function does nothing at this time. This function
 *		is called when user select a plugin in the exploration
 *		tree and the plugin switch to another.
 * @param	notebook	the notebook where are plugins
 * @param	page		the page in notebook
 * @param	page_num	the page number
 * @param	w		the settings window box
 */
void gw_settings_window_box_noteboox_settings_switch_page ( GtkNotebook *notebook, GtkNotebookPage *page, gint page_num, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_btn_ok_clicked
 * @abstract	Prevents Ok button is clicked.
 * @discussion	This function prevents Ok button is clicked.
 * @param	button	the invoker button
 * @param	w	the settings window box
 */
void gw_settings_window_box_btn_ok_clicked ( GtkButton *button, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_btn_cancel_clicked
 * @abstract	Prevents Cancel button is clicked.
 * @discussion	This function prevents Cancel button is clicked.
 * @param	button	the invoker button
 * @param	w	the settings window box
 */
void gw_settings_window_box_btn_cancel_clicked ( GtkButton *button, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_btn_apply_clicked
 * @abstract	Prevents Apply button is clicked.
 * @discussion	This function prevents Apply button is clicked.
 * @param	button	the invoker button
 * @param	w	the settings window box
 */
void gw_settings_window_box_btn_apply_clicked ( GtkButton *button, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_apply_ok
 * @abstract	Applies all changes.
 * @discussion	This function applies all changes.
 * @param	button	the invoker button
 * @param	w	the settings window box
 */
void gw_settings_window_box_apply_ok ( GtkButton *button, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_apply_no
 * @abstract	Doesn't apply all changes.
 * @discussion	This function doesn't apply all changes.
 * @param	button	the invoker button
 * @param	w	the settings window box
 */
void gw_settings_window_box_apply_no ( GtkButton *button, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_apply_cancel
 * @abstract	Cancels apply all changes.
 * @discussion	This function cancels apply all changes.
 * @param	button	the invoker button
 * @param	w	the settings window box
 */
void gw_settings_window_box_apply_cancel ( GtkButton *button, GtkWindow *w);


/*!
 * @function	gw_settings_window_box_closed
 * @abstract	Called when the settings window box is closed.
 * @discussion	This function is called when the settings window box is closed.
 * @param	settings_window_box	the invoker button
 * @param	window	the settings window box
 */
void gw_settings_window_box_closed ( GtkWindow *settings_window_box, GtkWindow *window);


#endif

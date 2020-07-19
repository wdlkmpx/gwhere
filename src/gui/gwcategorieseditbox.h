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
 * @header	gwcategorieseditbox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br>
 *		It's a GUI component to manage a list of categories.<br><br>
 * @abstract	This is a GUI component to list categories of a catalog.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/25
 * @see		gwsupport.h
 * @see		gwdata.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwcategories.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_CATEGORIES_EDIT_BOX_H
#define GW_GUI_GW_CATEGORIES_EDIT_BOX_H


#include "data/gwdata.h"


/*!
 * @function	gw_categories_edit_box_create
 * @abstract	Creates the GUI component
 * @discussion	This function creates and displays the categories managment window.<br>
 *		This window is modal.
 * @param	window		the main application window
 * @param	catalog_info	the catalog information data structure
 * @result	a pointer to this window.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GtkWindow * gw_categories_edit_box_create ( GtkWindow *window, GWDBCatalog *catalog);


/*!
 * @function	gw_categories_edit_box_load_categories_list
 * @abstract	Loads the list of catalog categories.
 * @discussion	This function loads the list of catalog categories in the categories managment window.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_load_categories_list ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_update_click
 * @abstract	Allows to edit properties of the selected category.
 * @discussion	This function allows to edit properties of the selected category.<br>
 *		This function call when the user click on update button.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_update_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_remove_click
 * @abstract	Removes the selected category from catalog.
 * @discussion	This function removes the selected category from catalog.<br>
 *		This function call when the user click on remove button.<br>
 * @param	w		the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_remove_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_add_update_click
 * @abstract	Adds or Updates the current edited category.
 * @discussion	This function adds or updates the current edited category.<br>
 *		This function call when the user click on add/update button.<br>
 *		Adds when the button state is add and updates when the button state is update.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_add_update_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_list_select_row
 * @abstract	Updates the editing category properties.
 * @discussion	This function updates the editing category properties. Clears all field in category properties.<br>
 *		This function call when the user select one item in the category list.<br>
 * @param	list	the categories list
 * @param	line	the current line
 * @param	column	the current column
 * @param	event	the event that call the function
 * @param	w	the categories managment window
 * @result	Return <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_categories_edit_box_list_select_row ( GtkCList *list, gint line, gint column, GdkEvent *event, GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_set_category_name
 * @abstract	Sets category name.
 * @discussion	This function sets the category name in the edit category properties.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 * 		Returns <i>0</i> when it's done.<br>
 * 		Returns -1 when an error occured.<br>
 */
gint gw_categories_edit_box_set_category_name ( GtkWindow *w, gchar *category_name);


/*!
 * @function	gw_categories_edit_box_set_category_description
 * @abstract	Sets category description.
 * @discussion	This function sets the category description in the edit category properties.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_set_category_description ( GtkWindow *w, gchar *category_description);


/*!
 * @function	gw_categories_edit_box_set_add_state
 * @abstract	Sets Add/Update button in Add mode.
 * @discussion	This function sets in "Add mode" the add/update button.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_set_add_state ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_set_update_state
 * @abstract	Sets Add/Update button in Update mode.
 * @discussion	This function sets in "Update mode" the add/update button.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_set_update_state ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_add_category
 * @abstract	Adds a category to the categories list.
 * @discussion	This function adds a category to the categories list.<br>
 *		If category is <i>null</i> adds the current edited category.<br>
 * @param	w		the categories managment window
 * @param	category	the category data structure to add
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_add_category ( GtkWindow *w, GWDBCategory *category);


/*!
 * @function	gw_categories_edit_box_update_category
 * @abstract	Updates a category to the catagories list.
 * @discussion	This function updates a category to the categories list.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_update_category ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_remove_category
 * @abstract	Removes from categories list the selected category.
 * @discussion	This function removes the selected category from categories list.<br>
 * @param	w	the categories managment window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_categories_edit_box_remove_category ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_main_window
 * @abstract	Gets the main window
 * @discussion	This function gets the main application window.<br>
 * @param	w	the categories managment window
 * @result	a pointer to the main window.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GtkWindow * gw_categories_edit_box_get_main_window ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_update_category_button
 * @abstract	Gets the update category button
 * @discussion	This function gets the update category button.<br>
 * @param	w	the categories managment window
 * @result	a pointer to the update category button.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkButton * gw_categories_edit_box_get_update_category_button ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_remove_category_button
 * @abstract	Gets the remove category button
 * @discussion	This function gets the remove category button.<br>
 * @param	w	the categories managment window
 * @result	a pointer to the remove category button.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkButton * gw_categories_edit_box_get_remove_category_button ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_add_update_category_button
 * @abstract	Gets the add/update category button
 * @discussion	This function gets the add/update category button.<br>
 * @param	w	the categories managment window
 * @result	a pointer to the add/update category button.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkButton * gw_categories_edit_box_get_add_update_category_button ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_category
 * @abstract	Gets the selected category.
 * @discussion	This function gets the selected category.<br>
 * @param	w	the categories managment window
 * @result	pointer to data structure of the selected category.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GWDBCategory * gw_categories_edit_box_get_category ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_category_name
 * @abstract	Gets current edited category name.
 * @discussion	This function gets the current edited category name.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the categories managment window
 * @result	the current edited name.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_categories_edit_box_get_category_name ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_category_description
 * @abstract	Gets current edited category description.
 * @discussion	This function gets the current edited category description.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the categories managment window
 * @result	the current edited description.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_categories_edit_box_get_category_description ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_isadd_state
 * @abstract	Checks if Add/Update button is in "Add mode".
 * @discussion	This function checks if add/upadte button is in "Add mode".<br>
 * @param	w	the categories managment window
 * @result	Returns <i>TRUE</i> if it is in "Add mode".<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_categories_edit_box_get_isadd_state ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_get_isupdate_state
 * @abstract	Checks if Add/Update button is in "Update mode".
 * @discussion	This function checks if add/upadte button is in "Upadte mode".<br>
 * @param	w	the categories managment window
 * @result	Returns <i>TRUE</i> if it is in "Update mode".<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_categories_edit_box_get_isupdate_state ( GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_category_name_changed
 * @abstract	Updates the add/update button when the category name changed.
 * @discussion	This function updates the add/update button when the category name changed.<br>
 * @param	w	the categories edit box window
 * @result	an error code.<br>
 *		Returns always <i>FALSE</i> at this time.
 */
gboolean gw_categories_edit_box_category_name_changed ( GtkWidget *entry, GtkWindow *w);


/*!
 * @function	gw_categories_edit_box_category_description_changed
 * @abstract	Updates the add/update button when the category description changed.
 * @discussion	This function updates the add/update button when the category description changed.<br>
 * @param	w	the categories edit box window
 * @result	an error code.<br>
 *		Returns always <i>FALSE</i> at this time.
 */
gboolean gw_categories_edit_box_category_description_changed ( GtkWidget *entry, GtkWindow *w);


#endif

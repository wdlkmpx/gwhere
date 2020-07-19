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
 * @header	gwcomboboxcategories.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br>
 *		It's a GUI component to display a list of categories and select one of them.<br><br>
 * @abstract	This is a GUI component to select a categoy.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/10/01
 * @see		gwsupport.h
 * @see		gwdata.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwcomboboxcategories.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_COMBO_BOX_CATEGORIES_H
#define GW_GUI_GW_COMBO_BOX_CATEGORIES_H


#include "data/gwdata.h"


/*!
 * @function	gw_combo_box_categories_create
 * @abstract	Creates the GUI component
 * @discussion	This function creates and displays the categories combo box.<br>
 *		If title is <i>null</i>, no label are displayed.<br>
 * @param	w		the main application window
 * @param	title		the combo box title
 * @param	catalog_info	the catalog information data structure
 * @result	a pointer to this combo box.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GtkHBox * gw_combo_box_categories_create ( GtkWindow *w, gchar *title, GWDBCatalog *catalog);


/*!
 * @function	gw_combo_box_categories_load
 * @abstract	Loads the list of catalog categories.
 * @discussion	This function loads the list of catalog categories in the categories combo box.<br>
 * @param	cbc		the categories combo box
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_combo_box_categories_load ( GtkHBox *cbc);


/*!
 * @function	gw_combo_box_categories_set_selected_category
 * @abstract	Sets the selected category.
 * @discussion	This function sets the selected category in the combo box with the category information data structure.<br>
 * @param	cbc		the categories combo box to set selected category
 * @param	category	the category information data structure
 * @result	an error code.<br>
 * 		Returns <i>0</i> when it's done.<br>
 * 		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_combo_box_categories_set_selected_category ( GtkHBox *cbc, GWDBCategoryPK ref);


/*!
 * @function	gw_combo_box_categories_set_selected_category_name
 * @abstract	Sets the selected category.
 * @discussion	This function sets the selected category in the combo box with the category name.<br>
 * @param	cbc		the categories combo box to set selected category
 * @param	name		the name of the selected category
 * @result	an error code.<br>
 * 		Returns <i>0</i> when it's done.<br>
 * 		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_combo_box_categories_set_selected_category_name ( GtkHBox *cbc, gchar *name);


/*!
 * @function	gw_combo_box_categories_get_selected_category
 * @abstract	Gets the selected category.
 * @discussion	This function gets the selected category in the combo box.<br>
 * @param	cbc		the categories combo box to get selected category
 * @result	pointer to data structure of the selected category.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GWDBCategory * gw_combo_box_categories_get_selected_category ( GtkHBox *cbc);


/*!
 * @function	gw_combo_box_categories_get_selected_category_name
 * @abstract	Gets the selected category name.
 * @discussion	This function gets the selected category name in the combo box.<br>
 *		It's a new allocated string and must free with g_free().<br>
 * @param	cbc		the categories combo box to get selected category
 * @result	the name of the selected category.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_combo_box_categories_get_selected_category_name ( GtkHBox *cbc);


/*!
 * @function	gw_combo_box_categories_get_combo
 * @abstract	Gets the combo.
 * @discussion	This function gets the categories combo of categories combo box.<br>
 * @param	cbc		the categories combo to get categories combo box
 * @result	pointer to the combo.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GtkCombo * gw_combo_box_categories_get_combo ( GtkHBox *cbc);


/*!
 * @function	gw_combo_box_categories_get_categories
 * @abstract	Gets the categories list.
 * @discussion	This function gets the categories list of categories combo box.<br>
 * @param	cbc		the categories combo box to get categories list
 * @result	pointer to categories list.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GList * gw_combo_box_categories_get_categories ( GtkHBox *cbc);


#endif

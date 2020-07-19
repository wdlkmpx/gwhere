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
 * @header	gwnotebooksearchcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component callback for search engine notebook pane.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/02/13
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwnotebooksearchcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_NOTEBOOK_SEARCH_CALLBACK_H
#define GW_GUI_GW_NOTEBOOK_SEARCH_CALLBACK_H


/*!
 * @function	gw_notebook_search_column_sort
 * @abstract	Sorts the column as ascending or descending.
 * @discussion	This function sorts the column as ascending or descending.
 * @param	clist		search result clist
 * @param	column		column to sort
 * @param	data		unused at time
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_column_sort ( GtkCList *clist, gint column, gpointer data);


/*!
 * @function	gw_notebook_search_search_string_activate
 * @abstract	Saves the search string
 * @discussion	This function saves the search string.
 * @param	entry		entry invoker
 * @param	w		main window
 * @result	Returns <i>TRUE</i> is the search string is saved.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_search_string_activate ( GtkWidget *entry, GtkWindow *w);


/*!
 * @function	gw_notebook_search_search_button_click
 * @abstract	Starts the search.
 * @discussion	This function starts the search.
 * @param	bt		button invoker
 * @param	w		main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_search_button_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_notebook_search_clear_button_click
 * @abstract	Clears all search results.
 * @discussion	This function clears all search results.
 * @param	bt		button invoker
 * @param	w		main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_clear_button_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_notebook_search_select_row
 * @abstract	Updates the status bar.
 * @discussion	This function updates the status bar when a result item is selected.
 * @param	clist		search result clist
 * @param	line		selected item line
 * @param	column		selected item column
 * @param	even		event whitch invoke this function
 * @param	w		main window
 * @result	Returns <i>TRUE</i> is the event submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_select_row ( GtkCList *clist, gint line, gint column, GdkEventButton *event, GtkWindow *w);


/*!
 * @function	gw_notebook_search_option_use_case_sensitive_click
 * @abstract	Saves ... option.
 * @discussion	This function saves ... option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_option_use_case_sensitive_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 */
gint gw_notebook_search_option_search_type_click ( GtkToggleButton *chk, gpointer search_type);


/*!
 * @function	gw_notebook_search_option_match_file_click
 * @abstract	Saves ... option.
 * @discussion	This function saves ... option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_option_match_file_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_search_option_match_folder_click
 * @abstract	Saves ... option.
 * @discussion	This function saves ... option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_option_match_folder_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_search_option_match_disk_click
 * @abstract	Saves ... option.
 * @discussion	This function saves ... option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_option_match_disk_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_search_option_match_category_click
 * @abstract	Saves ... option.
 * @discussion	This function saves ... option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_option_match_category_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_search_option_match_description_click
 * @abstract	Saves ... option.
 * @discussion	This function saves ... option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_option_match_description_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_search_clist_column_resized
 * @abstract	Saves the column width.
 * @discussion	This function saves the column width.<br>
 *		This function call when the user click resize any
 *		column in the search.<br>
 * @param	clist	the column list source invoker
 * @param	column	the column number
 * @param	width	the new column width
 * @param	data	unused data
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_clist_column_resized ( GtkCList *clist, gint column, gint width, gpointer data);


/*!
 * @function	gw_notebook_search_set_column_sort
 * @abstract	Sets the sort algorithm.
 * @discussion	This function sets the sort algorithm.
 * @param	clist		catalog file list clist
 * @param	column		column to sort
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_set_column_sort ( GtkCList *clist, gint column);


#endif

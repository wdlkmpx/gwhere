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
 * @header	gwnotebooksearch.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for the pane of search engine.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/02/13
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwnotebooksearch.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_NOTEBOOK_SEARCH_H
#define GW_GUI_GW_NOTEBOOK_SEARCH_H


#include "data/gwdata.h"


/*!
 * @function	gw_notebook_search_create
 * @abstract	Creates a search engine notebook pane.
 * @discussion	This function creates a search engine notebook pane.
 * @param	w		main window
 * @result	the search engine notebook pane.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_notebook_search_create ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_create_and_add
 * @abstract	Creates a search engine notebook pane and adds it to the notebook.
 * @discussion	This function creates a search engine notebook pane and adds it to the notebook.
 * @param	w		main window
 * @param	parent		the container
 * @result	the search engine notebook pane.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_notebook_search_create_and_add ( GtkWindow *w, GtkNotebook * parent);


/*!
 * @function	gw_notebook_search_get_clist_search
 * @abstract	Gets the list of the search engine.
 * @discussion	This function gets the list of search engine.
 * @param	w		refence to the main window
 * @result	the list of search engine.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkCList * gw_notebook_search_get_clist_search ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_search_text
 * @abstract	Gets the search string.
 * @discussion	This function gets the search string. This string may be empty.
 * @param	w		refence to the main window
 * @result	the search string of search engine. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_notebook_search_get_search_text ( GtkWindow *w);


/*!
 */
gboolean gw_notebook_search_set_search_text ( GtkWindow *w, gchar *text);


/*!
 * @function	gw_notebook_search_set_option_case_sensitive
 * @abstract	Sets the search to case sensitive.
 * @discussion	This function sets the search to case sensitive.
 * @param	w		refence to the main window
 * @param	case_sensitive	<i>TRUE</i> to activate case sensitive otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_case_sensitive ( GtkWindow *w, gboolean case_sensitive);


/*!
 * @function	gw_notebook_search_set_option_key_words
 * @abstract	Sets the search to use key words.
 * @discussion	This function sets the search to use key words.
 * @param	w		refence to the main window
 * @param	key_words	<i>TRUE</i> to activate key words search otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_key_words ( GtkWindow *w, gboolean key_words);

/*!
 * @function	gw_notebook_search_set_option_wildcards
 * @abstract	Sets the search to use wildcards.
 * @discussion	This function sets the search to use wilcards.
 * @param	w		refence to the main window
 * @param	wildcards	<i>TRUE</i> to activate wilcards search otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_wildcards ( GtkWindow *w, gboolean wildcards);

/*!
 * @function	gw_notebook_search_set_option_regular_expression
 * @abstract	Sets the search to use regular expression.
 * @discussion	This function sets the search to use regular expression.
 * @param	w		refence to the main window
 * @param	regex	<i>TRUE</i> to activate regural expression search otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_regular_expression ( GtkWindow *w, gboolean regex);


/*!
 * @function	gw_notebook_search_set_option_search_type
 * @abstract	Sets the search type.
 * @discussion	This function sets the search type.
 * @param	w		refence to the main window
 * @param	search_type	<i>SEARCH_TYPE_KEY_WORDS</i>,<i>SEARCH_TYPE_WILDCARDS</i>
 *				or <i>SEARCH_TYPE_REGEX</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_search_type ( GtkWindow *w, gint search_type);


/*!
 * @function	gw_notebook_search_set_option_match_file
 * @abstract	Sets the search to matches with files
 * @discussion	This function sets the search to matches with files name.
 * @param	w		refence to the main window
 * @param	match_file	<i>TRUE</i> to match with files otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_match_file ( GtkWindow *w, gboolean match_file);


/*!
 * @function	gw_notebook_search_set_option_match_folder
 * @abstract	Sets the search to matches with folders
 * @discussion	This function sets the search to matches with folders name.
 * @param	w		refence to the main window
 * @param	match_folder	<i>TRUE</i> to match with folders otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_match_folder ( GtkWindow *w, gboolean match_folder);


/*!
 * @function	gw_notebook_search_set_option_match_disk
 * @abstract	Sets the search to matches with disks
 * @discussion	This function sets the search to matches with disks name.
 * @param	w		refence to the main window
 * @param	match_disk	<i>TRUE</i> to match with disks otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_match_disk ( GtkWindow *w, gboolean match_disk);


/*!
 * @function	gw_notebook_search_set_option_match_category
 * @abstract	Sets the search to matches with categories
 * @discussion	This function sets the search to matches with categories.
 * @param	w		refence to the main window
 * @param	match_category	<i>TRUE</i> to match with categories otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_match_category ( GtkWindow *w, gboolean match_category);


/*!
 * @function	gw_notebook_search_set_option_match_description
 * @abstract	Sets the search to matches with descriptions
 * @discussion	This function sets the search to matches with descriptions.
 * @param	w		refence to the main window
 * @param	match_description	<i>TRUE</i> to match with descriptions otherwise <i>FALSE</i>
 * @result	Returns <i>TRUE</i> when it is done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_set_option_match_description ( GtkWindow *w, gboolean math_description);


/*!
 * @function	gw_notebook_search_clist_search_set_column_title
 * @abstract	Sets the columns properties
 * @discussion	This function sets the columns properties
 * @result	Returns <i>0</i> when it is done.
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_search_clist_search_set_column_title ( void);


/*!
 * @function	gw_notebook_search_get_option_case_sensitive
 * @abstract	Gets if the search is case sensitive.
 * @discussion	This function gets if the search is case sensitive.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search is case sensitive else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_get_option_case_sensitive ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_option_key_words
 * @abstract	Gets if the search use key words.
 * @discussion	This function gets if the search use key words.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search use key words else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_notebook_search_get_option_key_words ( GtkWindow *w);

/*!
 * @function	gw_notebook_search_get_option_wildcards
 * @abstract	Gets if the search use wildcards.
 * @discussion	This function gets if the search use wilcards.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search use wildcards else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_notebook_search_get_option_wildcards ( GtkWindow *w);

/*!
 * @function	gw_notebook_search_get_option_regular_expression
 * @abstract	Gets if the search use regular expression.
 * @discussion	This function gets if the search use regular expression.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search use regular expression else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_notebook_search_get_option_regular_expression ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_option_search_type
 * @abstract	Gets the search type.
 * @discussion	This function gets the search type.
 * @param	w		refence to the main window
 * @result	Returns <i>SEARCH_TYPE_KEY_WORDS</i>,<i>SEARCH_TYPE_WILDCARDS</i> or <i>SEARCH_TYPE_REGEX</i>.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_notebook_search_get_option_search_type ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_option_match_file
 * @abstract	Gets if the search matches with file
 * @discussion	This function gets if the search matches with files name.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search matches with files else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_get_option_match_file ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_option_match_folder
 * @abstract	Gets if the search matches with folder
 * @discussion	This function gets if the search matches with folders name.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search matches with folders else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_get_option_match_folder ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_option_match_disk
 * @abstract	Gets if the search matches with disk
 * @discussion	This function gets if the search matches with disks name.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search matches with disks else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_get_option_match_disk ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_option_match_category
 * @abstract	Gets if the search matches with categories
 * @discussion	This function gets if the search matches with categories.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search matches with categories else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_get_option_match_category ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_option_match_description
 * @abstract	Gets if the search matches with descriptions
 * @discussion	This function gets if the search matches with descriptions.
 * @param	w		refence to the main window
 * @result	Returns <i>TRUE</i> if the search matches with descriptions else returns <i>FALSE</i>.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_search_get_option_match_description ( GtkWindow *w);


/*!
 * @function	gw_notebook_search_get_user_quick_search
 * @abstract	Gets the user quick search informations
 * @discussion	This function gets the user quick search informations.
 *				<b>Warning :</b> this function allocates a new <i>struct user_quick_search<i>
 *				must free this structure after.
 * @param	w		refence to the main window
 * @result	the user quick search structure. Must be freed with user_quick_search_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
struct user_quick_search * gw_notebook_search_get_user_quick_search ( GtkWindow *w);


#endif

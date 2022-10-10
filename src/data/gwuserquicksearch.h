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
 * @header	gwuserquicksearch.h
 * @discussion	GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 *		It uses to link with user settings. It's an inherited object from EngineQuickSearch.
 * @abstract	This is the engine quick search information data structure
 * @version	1.0 2002/03/11
 * @author	Author <zero@gwhere.org>
 * @see		gwenginequicksearch.c
 * @ref		gwuserquicksearch.c
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK Web Site <http://www.gtk.org>
 * @author	S&eacute;bastien LECACHEUR <zero@gwhere.org>
 */


#ifndef GW_DATA_USER_QUICK_SEARCH_H
#define GW_DATA_USER_QUICK_SEARCH_H


#include "gwenginequicksearch.h"


/*! @define	SEARCH_TYPE_NONE	Undefinied search type */
#define SEARCH_TYPE_NONE -1
/*! @define	SEARCH_TYPE_KEY_WORDS	Search type for key words */
#define SEARCH_TYPE_KEY_WORDS 0
/*! @define	SEARCH_TYPE_WILDCARDS	Search type for wildcards */
#define SEARCH_TYPE_WILDCARDS 1
/*! @define	SEARCH_TYPE_REGEX	Search type for regural expression */
#define SEARCH_TYPE_REGEX 2


/*!
 * @struct	user_quick_search
 * @abstract	User Quick Search information data structure
 * @discussion	User Quick Search information is an opaque data structure containing information about a quick search.
 */
struct user_quick_search;


/*!
 * @function	user_quick_search_new
 * @abstract	Creates a new user quick search
 * @discussion	This function creates a new user quick search. It's an allocation function.<br>
 *		All data are agregated.
 * @result	a pointer to the user quick search structure.
 *		Returns <i>NULL</i> when an error occured.
 */
struct user_quick_search *user_quick_search_new ( void);


/*!
 * @function	user_quick_search_set_pattern
 * @abstract	Sets the search pattern string
 * @discussion	This function sets the pattern for quick search. This patern is a regular expression
 * @param	p	the user quick search to set patern
 * @param	pattern	the search pattern string
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_pattern ( struct user_quick_search *p, gchar *pattern);


/*!
 * @function	user_quick_search_set_case_sensitive
 * @abstract	Sets if the quick search is case sensitive
 * @discussion	This function sets if the quick search is case sensitive.
 * @param	p	the user quick search to set case sensitive mode
 * @param	case_sensitive	<i>TRUE</i> if quick search is case sensitive or <i>FALSE</i> if is uncase sensitive
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_case_sensitive ( struct user_quick_search *p, gboolean case_sensitive);


/*!
 * @function	user_quick_search_set_type
 * @abstract	Sets the quick search type
 * @discussion	This function sets the quick search type.
 * @param	p	the user quick search to set if uses regular expression
 * @param	type	<i>SEARCH_TYPE_KEY_WORDS</i>,<i>SEARCH_TYPE_WILDCARDS</i>
 *			or <i>SEARCH_TYPE_REGEX</i>
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_type ( struct user_quick_search *p, gint type);


/*!
 * @function	user_quick_search_set_match_file
 * @abstract	Sets if the quick search matches with files
 * @discussion	This function sets if the quick search matches with files
 * @param	p	the user quick search to set if matches with files
 * @param	match_file	<i>TRUE</i> if quick search matches with files or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_match_file ( struct user_quick_search *p, gboolean match_file);


/*!
 * @function	user_quick_search_set_match_folder
 * @abstract	Sets if the quick search matches with folders
 * @discussion	This function sets if the quick search matches with folders
 * @param	p	the user quick search to set if matches with folders
 * @param	match_folder	<i>TRUE</i> if quick search matches with folders or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_match_folder ( struct user_quick_search *p, gboolean match_folder);


/*!
 * @function	user_quick_search_set_match_disk
 * @abstract	Sets if the quick search matches with disks
 * @discussion	This function sets if the quick search matches with disks
 * @param	p	the user quick search to set if matches with disks
 * @param	match_disk	<i>TRUE</i> if quick search matches with disks or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_match_disk ( struct user_quick_search *p, gboolean match_disk);


/*!
 * @function	user_quick_search_set_match_category
 * @abstract	Sets if the quick search matches with categories
 * @discussion	This function sets if the quick search matches with categories
 * @param	p	the user quick search to set if matches with cateogies
 * @param	match_category	<i>TRUE</i> if quick search matches with categories or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_match_category ( struct user_quick_search *p, gboolean match_category);


/*!
 * @function	user_quick_search_set_match_description
 * @abstract	Sets if the quick search matches with descriptions
 * @discussion	This function sets if the quick search matches with descriptions
 * @param	p	the user quick search to set if matches with descriptions
 * @param	match_description	<i>TRUE</i> if quick search matches with descriptions or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_set_match_description ( struct user_quick_search *p, gboolean match_description);


/*!
 * @function	user_quick_search_get_pattern
 * @abstract	Gets the search pattern string
 * @discussion	This function gets the pattern for quick search.
 * @param	p	the user quick search to get pattern
 * @result	the pattern
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * user_quick_search_get_pattern ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_get_case_sensitive
 * @abstract	Gets if the quick search is case sensitive
 * @discussion	This function gets if the quick search is case sensitive.
 * @param	p	the user quick search to get if is case sensitive
 * @result	<i>TRUE</i> if the quick search is case sensitive or <i>FALSE</i> if is uncase sensitive
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean user_quick_search_get_case_sensitive ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_get_type
 * @abstract	Gets if the quick search uses regural expressions
 * @discussion	This function gets if the quick search uses regular expressions.
 * @param	p	the user quick search to get if uses regular expressions
 * @result	<i>SEARCH_TYPE_KEY_WORDS</i>,<i>SEARCH_TYPE_WILDCARDS</i> or <i>SEARCH_TYPE_REGEX</i>
 *		Returns <i>SEARCH_TYPE_NONE</i> when an error occured.
 */
gint user_quick_search_get_type ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_get_match_file
 * @abstract	Gets if the quick search matches with files
 * @discussion	This function gets if the quick search matches with files.
 * @param	p	the user quick search to get if matches with files
 * @result	<i>TRUE</i> if the quick search matches with files or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean user_quick_search_get_match_file ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_get_match_folder
 * @abstract	Gets if the quick search matches with folders
 * @discussion	This function gets if the quick search matches with folders.
 * @param	p	the user quick search to get if matches with folders
 * @result	<i>TRUE</i> if the quick search matches with folders or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean user_quick_search_get_match_folder ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_get_match_disk
 * @abstract	Gets if the quick search matches with disks
 * @discussion	This function gets if the quick search matches with disks.
 * @param	p	the user quick search to get if matches with disks
 * @result	<i>TRUE</i> if the quick search matches with disks or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean user_quick_search_get_match_disk ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_get_match_category
 * @abstract	Gets if the quick search matches with categories
 * @discussion	This function gets if the quick search matches with categories.
 * @param	p	the user quick search to get if matches with categories
 * @result	<i>TRUE</i> if the quick search matches with categories or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean user_quick_search_get_match_category ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_get_match_description
 * @abstract	Gets if the quick search matches with descriptions
 * @discussion	This function gets if the quick search matches with descriptions.
 * @param	p	the user quick search to get if matches with descriptions
 * @result	<i>TRUE</i> if the quick search matches with descriptions or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean user_quick_search_get_match_description ( struct user_quick_search *p);


/*!
 * @function	user_quick_search_free
 * @abstract	Frees data structure
 * @discussion	This function frees the user quick search data structure.
 * @param	p	the user quick search to free
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint user_quick_search_free ( struct user_quick_search *p);



/*!
 * @function	user_quick_search_to_engine_quick_search
 * @abstract	Transforms a user quick search to engine quick search
 * @discussion	This function tranforms user quick search to engine quick search. It's creates a regular
 *		expression from the search patern.
 * @param	p	the user quick search to transform
 * @result	the engine quick search structure.
 *		Returns <i>NULL</i> when an error occured.
 */
struct engine_quick_search *user_quick_search_to_engine_quick_search ( struct user_quick_search *p);


#endif

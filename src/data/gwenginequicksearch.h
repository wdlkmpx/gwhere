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
 * @header	gwenginequicksearch.h
 * @discussion	GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 *		It uses in the search engine. By defaut the quick search is case sensitive and matches only with files.
 * @abstract	This is the engine quick search information data structure
 * @version	1.0 2002/03/11
 * @author	Author <zero@gwhere.org>
 * @ref		gwenginequicksearch.c
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK Web Site <http://www.gtk.org>
 * @author	S&eacute;bastien LECACHEUR <zero@gwhere.org>
 */


#ifndef GW_DATA_ENGINE_QUICK_SEARCH_H
#define GW_DATA_ENGINE_QUICK_SEARCH_H


/*!
 * @struct	engine_quick_search
 * @abstract	Engine Quick Search information data structure
 * @discussion	Engine Quick Search information is an opaque data structure containing information about a quick search.
 */
//struct engine_quick_search;


/*!
 * @function	engine_quick_search_new
 * @abstract	Creates a new engine quick search
 * @discussion	This function creates a new engine quick search. It's an allocation function.<br>
 *		All data are agregated.
 * @result	a pointer to the engine quick search structure.
 *		Returns <i>NULL</i> when an error occured.
 */
struct engine_quick_search *engine_quick_search_new ( void);


/*!
 * @function	engine_quick_search_set_pattern
 * @abstract	Sets the search pattern string
 * @discussion	This function sets the pattern for quick search. This pattern is a regular expression
 * @param	p	the engine quick search to set pattern
 * @param	pattern	the search pattern string
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_pattern ( struct engine_quick_search *p, gchar *pattern);


/*!
 * @function	engine_quick_search_set_key_words
 * @abstract	Sets the list of key words for the search
 * @discussion	This function sets the list of key words for the search. These key
 *		words are regular expressions
 * @param	p		the engine quick search to set pattern
 * @param	key_words_list	the key words list
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_key_words ( struct engine_quick_search *p, gchar **key_words_list);


/*!
 * @function	engine_quick_search_set_type
 * @abstract	Sets the search type
 * @discussion	This function sets the search type
 * @param	p	the engine quick search to set pattern
 * @param	type	the search type (<i>SEARCH_TYPE_KEY_WORDS</i>, <i>SEARCH_TYPE_WILDCARDS</i>,
 *			<i>SEARCH_TYPE_REGEX</i>)
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_type ( struct engine_quick_search *p, gint type);


/*!
 * @function	engine_quick_search_set_case_sensitive
 * @abstract	Sets if the quick search is case sensitive
 * @discussion	This function sets if the quick search is case sensitive.
 * @param	p	the engine quick search to set case sensitive mode
 * @param	case_sensitive	<i>TRUE</i> if quick search is case sensitive or <i>FALSE</i> if is uncase sensitive
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_case_sensitive ( struct engine_quick_search *p, gboolean case_sensitive);


/*!
 * @function	engine_quick_search_set_match_file
 * @abstract	Sets if the quick search matches with files
 * @discussion	This function sets if the quick search matches with files
 * @param	p	the engine quick search to set if matches with files
 * @param	match_file	<i>TRUE</i> if quick search matches with files or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_match_file ( struct engine_quick_search *p, gboolean match_file);


/*!
 * @function	engine_quick_search_set_match_folder
 * @abstract	Sets if the quick search matches with folders
 * @discussion	This function sets if the quick search matches with folders
 * @param	p	the engine quick search to set if matches with folders
 * @param	match_folder	<i>TRUE</i> if quick search matches with folders or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_match_folder ( struct engine_quick_search *p, gboolean match_folder);


/*!
 * @function	engine_quick_search_set_match_disk
 * @abstract	Sets if the quick search matches with disks
 * @discussion	This function sets if the quick search matches with disks
 * @param	p	the engine quick search to set if matches with disks
 * @param	match_disk	<i>TRUE</i> if quick search matches with disks or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_match_disk ( struct engine_quick_search *p, gboolean match_disk);


/*!
 * @function	engine_quick_search_set_match_category
 * @abstract	Sets if the quick search matches with categories
 * @discussion	This function sets if the quick search matches with categories
 * @param	p	the engine quick search to set if matches with cateogies
 * @param	match_category	<i>TRUE</i> if quick search matches with categories or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_match_category ( struct engine_quick_search *p, gboolean match_category);


/*!
 * @function	engine_quick_search_set_match_description
 * @abstract	Sets if the quick search matches with descriptions
 * @discussion	This function sets if the quick search matches with descriptions
 * @param	p	the engine quick search to set if matches with descriptions
 * @param	match_description	<i>TRUE</i> if quick search matches with descriptions or <i>FALSE</i> if doesn't match
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_match_description ( struct engine_quick_search *p, gboolean match_description);


/*!
 * @function	engine_quick_search_set_match_all_key_words
 * @abstract	Sets if the quick search matches with all key words
 * @discussion	This function sets if the quick search matches with all key words
 * @param	p	the engine quick search to set if matches with all key words
 * @param	match_all_key_words	<i>TRUE</i> if quick search matches with all key words or <i>FALSE</i> if it matches with only one of them
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_set_match_all_key_words ( struct engine_quick_search *p, gboolean match_all_key_words);


/*!
 * @function	engine_quick_search_get_pattern
 * @abstract	Gets the search pattern string
 * @discussion	This function gets the pattern for quick search.
 * @param	p	the engine quick search to get pattern
 * @result	the pattern
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * engine_quick_search_get_pattern ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_key_words
 * @abstract	Gets the list of key words for the search
 * @discussion	This function gets the list of key words for the search. These key
 *		words are regular expressions
 * @param	p		the engine quick search to set pattern
 * @result	The key words list.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar ** engine_quick_search_get_key_words ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_type
 * @abstract	Gets the search type
 * @discussion	This function gets the search type
 * @param	p	the engine quick search to set pattern
 * @param	type	
 * @result	The search type (SEARCH_TYPE_KEY_WORDS, SEARCH_TYPE_WILDCARDS,
 *		SEARCH_TYPE_REGEX).<br>
 *		Returns <i>SEARCH_TYPE_NONE</i> when an error occured.
 */
gint engine_quick_search_get_type ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_case_sensitive
 * @abstract	Gets if the quick search is case sensitive
 * @discussion	This function gets if the quick search is case sensitive.
 * @param	p	the engine quick search to get if is case sensitive
 * @result	<i>TRUE</i> if the quick search is case sensitive or <i>FALSE</i> if is uncase sensitive
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean engine_quick_search_get_case_sensitive ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_match_file
 * @abstract	Gets if the quick search matches with files
 * @discussion	This function gets if the quick search matches with files.
 * @param	p	the engine quick search to get if matches with files
 * @result	<i>TRUE</i> if the quick search matches with files or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean engine_quick_search_get_match_file ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_match_folder
 * @abstract	Gets if the quick search matches with folders
 * @discussion	This function gets if the quick search matches with folders.
 * @param	p	the engine quick search to get if matches with folders
 * @result	<i>TRUE</i> if the quick search matches with folders or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean engine_quick_search_get_match_folder ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_match_disk
 * @abstract	Gets if the quick search matches with disks
 * @discussion	This function gets if the quick search matches with disks.
 * @param	p	the engine quick search to get if matches with disks
 * @result	<i>TRUE</i> if the quick search matches with disks or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean engine_quick_search_get_match_disk ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_match_category
 * @abstract	Gets if the quick search matches with categories
 * @discussion	This function gets if the quick search matches with categories.
 * @param	p	the engine quick search to get if matches with categories
 * @result	<i>TRUE</i> if the quick search matches with categories or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean engine_quick_search_get_match_category ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_match_description
 * @abstract	Gets if the quick search matches with descriptions
 * @discussion	This function gets if the quick search matches with descriptions.
 * @param	p	the engine quick search to get if matches with descriptions
 * @result	<i>TRUE</i> if the quick search matches with descriptions or <i>FALSE</i> if doesn't match
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean engine_quick_search_get_match_description ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_get_match_all_key_words
 * @abstract	Gets if the quick search matches with all key words
 * @discussion	This function gets if the quick search matches with all key words.
 * @param	p	the engine quick search to get if matches with all key words
 * @result	<i>TRUE</i> if the quick search matches with all key words or <i>FALSE</i> if it matches with only one of them
 *		Returns <i>NULL</i> when an error occured.
 */
gboolean engine_quick_search_get_match_all_key_words ( struct engine_quick_search *p);


/*!
 * @function	engine_quick_search_free
 * @abstract	Frees data structure
 * @discussion	This function frees the engine quick search data structure.
 * @param	p	the engine quick search to free
 * @result	an error code.
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint engine_quick_search_free ( struct engine_quick_search *p);


#endif

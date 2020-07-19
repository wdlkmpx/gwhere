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
 * @header	gwstringbuffer.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br>
 *		It's an object for string buffer representation.<br>
 * 		A string buffer is an indexed array of characters where the first character is at
 * 		the position <i>0</i> and the last character at the position <i>length - 1</i>.
 * @abstract	This is the catalog file data structure.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwstringbuffer.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_DATA_STRING_BUFFER_H
#define GW_DATA_STRING_BUFFER_H


/*!
 * @typedef	GWStringBuffer
 *		This structure represents a string buffer. It is used to manipulate
 * 		lot of strings without reallocating at each time memory.
 * @abstract	The string buffer representation.
 * @struct	string_buffer_s
 */
typedef struct string_buffer_s GWStringBuffer;


/*!
 * @function	gw_string_buffer_new
 * @abstract	Creates a new string buffer
 * @discussion	This function constructs a string buffer with no characters in it
 * 		and an initial capacity of <i>0</i> characters.
 * @result	A pointer to the string buffer structure.
 *		Returns <i>NULL</i> when an error occured.
 */
GWStringBuffer * gw_string_buffer_new ( void);


/*!
 * @function	gw_string_buffer_new_from_str
 * @abstract	Creates a new string buffer from a string
 * @discussion	This function constructs a string buffer from the specified string.
 * 		So that it represents the same sequence of characters as the string
 * 		argument; in other words, the initial contents of the string buffer
 * 		is a copy of the argument string. The initial capacity of the string
 * 		buffer is <i>0</i> plus the length of the string argument.
 * @param	str	the initial contents of the string buffer
 * @result	A pointer to the string buffer structure.
 *		Returns <i>NULL</i> when an error occured.
 */
GWStringBuffer * gw_string_buffer_new_from_str ( const gchar *str);


/*!
 * @function	gw_string_buffer_resize
 * @abstract	Resizes the new string buffer capacity
 * @discussion	This function resizes the string buffer capacity. It only can increase
 * 		the string buffer capacity and not decrease it. So the the new size must
 * 		bigger than the actual string buffer capacity.
 * @result	The new string buffer capacity.<br>
 *		Returns <i>0</i> when the new size is smaller than the string capacity
 * 		or when an error occured.
 */
gulong gw_string_buffer_resize ( GWStringBuffer *p, gulong newsize);


/*!
 * @function	gw_string_buffer_delete
 * @abstract	Deletes the characters in a substring of the string buffer
 * @discussion	This function removes the characters in a substring of this string
 * 		buffer. The substring begins at the specified start and extends to the
 * 		character at index end - 1 or to the end of the string buffer if no
 * 		such character exists. If start is equal to end, no changes are made.
 * @param	p	the string buffer to removes somes characters
 * @param	start	the strat of the substring to remove (inclusive)
 * @param	end	the end of the substring to remove (exclusive)
 * @result	The number of deleted characters.<br>
 *		Returns <i>0</i> if the start is negative, greater than the string
 * 		buffer length or greater than end; or when an error occured.
 */
gulong gw_string_buffer_delete ( GWStringBuffer *p, gulong start, gulong end);


/*!
 * @function	gw_string_buffer_delete_all
 * @abstract	Deletes all the characters of the string buffer
 * @discussion	This function removes all the characters of this string buffer.
 * @param	p	the string buffer to removes somes characters
 * @result	The number of deleted characters.<br>
 *		Returns <i>0</i> when an error occured.
 */
gulong gw_string_buffer_delete_all ( GWStringBuffer *p);


/*!
 * @function	gw_string_buffer_set_str
 * @abstract	Sets the given string to the string buffer
 * @discussion	This function set the given string the the string buffer
 * @param	p	the string buffer to sets the given string
 * @param	str	the string to set
 * @param	len	the length of the given string
 */
void gw_string_buffer_set_str ( GWStringBuffer *p, gchar *str, gulong len);


/*!
 * @function	gw_string_buffer_append_str
 * @abstract	Appends the given string to this string buffer.
 * @discussion	This function appends the given string to this string buffer.
 * 		The characters of the string argument are appended, in order,
 * 		to the contents of this string buffer, increasing the length
 * 		of this string buffer by the length of the third argument. If
 * 		str is <i>NULL</i>, no string is appended to the string buffer.
 * @param	p	the string buffer to append the given string
 * @param	str	the string to append
 * @param	len	the length of the given string, this is the number
 * 			of characters to append
 */
void gw_string_buffer_append_str ( GWStringBuffer *p, gchar *str, gulong len);


/*!
 * @function	gw_string_buffer_insert_str
 * @abstract	Inserts the given string into this string buffer at the specified
 * 		index position.
 * @discussion	This function inserts the given string into this string buffer
 * 		at the specified index position.<br>
 * 		The characters of the string argument are inserted, in order,
 * 		into the string buffer at the indicated offset, moving up any
 * 		characters originally above that position and increasing the
 * 		length of this string buffer by the length of the fourth argument.
 * 		If str is <i>NULL</i>, no string is inserted to the string buffer.
 * @param	p	the string buffer to insert the given string
 * @param	str	the string to insert
 * @param	start	the index where the string will be inserted. This argument
 * 			must be greater than or equal to <i>0</i>, and less than or equal
 * 			to the length of this string buffer
 * @param	len	the length of the given string, this is the number
 * 			of characters to insert
 */
void gw_string_buffer_insert_str ( GWStringBuffer *p, gchar *str, gulong start, gulong len);


/*!
 * @function	gw_string_buffer_replace_str
 * @astract	Replaces by the given string the substring of the string buffer.
 * @discussion	This function replaces by the given string the substring of the
 * 		string buffer at the given position with the given length.<br>
 * 		The characters of the string argument are used, in order, into
 * 		the string buffer at the indicated offset, replacing any characters
 * 		originall at this position.<br>
 * 		If the string buffer capacity is less than the sum of the start
 * 		argument and the len argument, the string buffer size is increased.
 * @param	p	the string buffer where a substring must to be replaced.
 * @param	str	the string which must replace the substring.
 * @param	start	the index in the string buffer where the substring starts.
 * 			This argument must be greater than or equal to <i>0</i>,
 * 			and less than or equal to the length of this string buffer.
 * @param	len	the length of the given string, this is the number of
 * 			characters to replace.
 */
void gw_string_buffer_replace_str ( GWStringBuffer *p, gchar *str, gulong start, gulong end);


/*!
 * @function	gw_string_buffer_replace_chr
 * @astract	Replaces a specified character in the string buffer by the given character.
 * @discussion	This function replaces a specified character in the string buffer by the
 * 		given character at the given position.<br>
 * @param	p	the string buffer where a character must to be replaced.
 * @param	chr	the character which must replace the specified character.
 * @param	index	the index in the string buffer where the specified character to
 * 			replace is located. This argument must be greater than or equal
 * 			to <i>0</i>, and less than or equal to the length of this string
 * 			buffer.
 */
void gw_string_buffer_replace_chr ( GWStringBuffer *p, gchar chr, gulong index);


/*!
 * @function	gw_string_buffer_get_str
 * @abstract	Returns the internal string.
 * @discussion	This function returns the internal string. This one is the string representation
 * 		of the given string buffer.
 * @param	p	the string buffer to get the string form.
 * @return	the string form of the string buffer otherwize returns <i>NULL</i> if an error
 * 		was occured or if the string buffer is empty.
 */
gchar * gw_string_buffer_get_str ( GWStringBuffer *p);


/*!
 * @function	gw_string_buffer_get_size
 * @abstract	Returns the string buffer size.
 * @discussion	this function returns the string buffer size. This
 * 		size correspond with the string buffer capacity.
 * @param	p	the string buffer to get the size.
 * @return	the string buffer capacity or <i>0</i> an error
 * 		was occured.
 */
gulong gw_string_buffer_get_size ( GWStringBuffer *p);


/*!
 * @function	gw_string_buffer_free
 * @abstract	Frees the given string buffer.
 * @discussion	This function frees the given string buffer. If this string buffer contains
 * 		an internal buffer, this buffer will be freed too.
 * @param	p	the string buffer to free.
 */
void gw_string_buffer_free ( GWStringBuffer *p);


#endif

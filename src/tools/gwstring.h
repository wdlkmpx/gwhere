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
 * @header	gwstring.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a tool component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		glib.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwstring.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_TOOLS_GWSTRING_H
#define GW_TOOLS_GWSTRING_H


#include <glib.h>
#include "data/gwdata.h"


#define DATE_FORMAT "%d/%m/%Y %H:%M:%S"


#ifndef strsep
/*!
 * @function	strsep
 * @abstract	Parses a string with delimiters.
 * @discussion	This function returns the next token from the
 *		string stringp which is delimited by delim. The token is
 *		terminated with a <i>`\0'</i> character and stringp is updated to
 *		point past the token.<br>
 * @param	stringp	the string to parse
 * @param	delim	the delimiter
 * @result	returns a pointer to the  token, or <i>NULL</i> if delim is not found in stringp.
 */
char * strsep ( char **stringp, const char *delim);
#endif  /* strsep */


#if defined ( OS_WIN32)
	#include <winsock2.h>
#else
	#ifndef ntohl
		/*! @define	ntohl	The ntohl() port. */
		#define ntohl gw_ntohl
	#endif /* ntohl */
#endif


/*!
 * @function	gw_ntohl
 * @abstract	Formats a long number to a string
 * @discussion	This function converts the long integer netlong
 *		from network byte order to host byte order.<br>
 * @param	in	integer netlong to convert
 * @result	returns the integer long.
 */
unsigned long int gw_ntohl ( unsigned long int in);


/*!
 * @function	gw_l_byte_to_str_format
 * @abstract	Formats a long number to a string
 * @discussion	This function creates a string from a long number.<br>
 *		Example :<br>
 *		4096 => "4Kb"<br>
 * @param	n	octet number to format
 * @result	the formated string. Must be freed with g_free().
 */
gchar * gw_l_byte_to_str_format ( long size );


/*!
 * @function	gw_ul_byte_to_str_format
 * @abstract	Formats an unsigned long number to a string
 * @discussion	This function creates a string from an unsigned long number.<br>
 *		Example :<br>
 *		4096 => "4Kb"<br>
 * @param	n	octet number to format
 * @result	the formated string. Must be freed with g_free().
 */
gchar * gw_ul_byte_to_str_format ( unsigned long size );


/*!
 * @function	gw_ui64_byte_to_str_format
 * @abstract	Formats an unsigned int 64 bytes number to a string
 * @discussion	This function creates a string from an unsigned int 64 number.<br>
 *		Example :<br>
 *		4096 => "4Kb"<br>
 * @param	n	octet number to format
 * @result	the formated string. Must be freed with g_free().
 */
gchar * gw_ui64_byte_to_str_format ( guint64 size );


/*!
 * @function	gw_d_byte_to_str_format
 * @abstract	Formats a double number to a string
 * @discussion	This function creates a string from a double number.<br>
 *		Example :<br>
 *		4096 => "4Kb"<br>
 * @param	n	octet number to format
 * @result	the formated string. Must be freed with g_free().
 */
gchar * gw_d_byte_to_str_format ( gdouble size );


/*!
 * @function	gw_ld_byte_to_str_format
 * @abstract	Formats a long double number to a string
 * @discussion	This function creates a string from a long double number.<br>
 *		Example :<br>
 *		4096 => "4Kb"<br>
 * @param	n	octet number to format
 * @result	the formated string. Must be freed with g_free().
 */
gchar * gw_ld_byte_to_str_format ( long double size );


/*!
 * @function	gw_str_format_to_ld
 * @abstract	Calculs logn double number from a string
 * @discussion	This function calculs the long double number of bytes from a string. The string is a formated string.<br>
 *		Example :<br>
 *		"4Kb" => 4096<br>
 * @param	desc	the formated string
 * @result	the octet number
 */
long double gw_str_format_to_ld ( gchar * nb);


/*!
 * @function	gw_tm_to_str_format
 * @abstract	Formats a date from a time number
 * @discussion	This function creates a string from a time number.<br>
 * @param	p	 the time number
 * @result	the formated string. Must be freed with g_free().
 */
gchar * gw_tm_to_str_format ( struct tm* p);


/*!
 * @function	gw_file_to_str
 * @abstract	Formats a string from a specified file format to displayed format
 * @discussion	This function replaces all <i>"\\n"</i> to <i>"\n"</i> and all
                <i>"\\#"</i> to <i>":"</i>.
 * @param	str	the string to format
 * @result	the formated string. Must be freed with g_free().
 */
gchar * gw_file_to_str ( gchar *str);


/*!
 * @function	gw_str_to_file
 * @abstract	Formats a string to a specified file format
 * @discussion	This function replaces all <i>":"</i> to <i>"\\#"</i> and all
                <i>"\n"</i> to <i>"\\n"</i>.
 * @param	str	the string to format
 * @result	the formated string. Must be freed with g_free().
 *		Returns <i>NULL</i> if there is no <i>"\n"</i> or <i>":"</i>.
 */
gchar * gw_str_to_file ( gchar *str);


/*!
 * @function	gw_str_to_file_strb
 * @abstract	Formats a string to a specified file format
 * @discussion	This function replaces all <i>":"</i> to <i>"\\#"</i> and all
                <i>"\n"</i> to <i>"\\n"</i>.
 * @param	str	the string to format
 * @param	buf	the string buffer to store the new string
 * @result	the formated string. Must be freed with g_free().
 *		Returns <i>NULL</i> if there is no <i>"\n"</i> or <i>":"</i>.
 */
gchar * gw_str_to_file_strb ( const gchar *str, GWStringBuffer *buf);


/*!
 * @function	gw_str_replace_str
 * @abstract	Replaces all sub string of one string by another sub string
 * @discussion	This function replaces all sub string of one string by another sub string
 * @param	pattern	the string to replace sub string
 * @param	src	the sub string to replace
 * @param	dst	the sub string to put
 * @result	A new allocated string.<br>
 *		Returns <i>NULL</i> if there no sub string to replace or when an error occured.<br>
 */
gchar * gw_str_replace_str ( gchar *pattern, gchar *src, gchar *dst);


/*!
 * @function	gw_str_replace_strv
 * @abstract	Replaces all sub string of one string by another sub string
 * @discussion	This function replaces all listed sub string of one string by others listed sub string. The arrays must end with <i>NULL</i>.
 * @param	pattern	the string to replace sub string
 * @param	src	the array of sub string to replace
 * @param	dst	the array sub string to put
 * @result	A new allocated string.<br>
 *		Returns <i>NULL</i> if there no sub string to replace or when an error occured.<br>
 */
gchar * gw_str_replace_strv ( gchar *pattern, gchar **src, gchar **dst);


/*!
 * @function	gw_str_blob_to_regex
 * @abstract	Transforms a blob string to regular expression
 * @discussion	This function transforms a blob string to regular expression
 * @param	blob	the blob string to transform
 * @result	the regural expression.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_str_blob_to_regex ( gchar *blob);

/*!
 * @function	gw_str_key_words_to_regex
 * @abstract	Transforms a key words string to regular expression table
 * @discussion	This function transforms a key words string to regular expression table
 * @param	jey_words	the key_words string to transform
 * @result	the regural expression table.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar ** gw_str_key_words_to_regex ( gchar *key_words);


/*!
 * @function	gw_strcmp_strblob
 * @abstract	Compares a string with a blob string
 * @discussion	This function compares a string with a blob string
 * @param	str	the string to compare
 * @param	blob	the blob string to transform
 * @param	case_sensitive	if comparaison is case sensitive
 * @result	Returns <i>0</i> when the two string are equals.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_strcmp_strblob ( gchar *str, gchar *blob, gboolean case_sensitive);


/*!
 * @function	gw_strcmp_strregex
 * @abstract	Compares a string with a regular expression string
 * @discussion	This function compares a string with a regular expression string
 * @param	str	the string to compare
 * @param	regex	the regex string to transform
 * @param	case_sensitive	if comparaison is case sensitive
 * @result	Returns <i>0</i> when the two string are equals.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_strcmp_strregex ( gchar *str, gchar *regex, gboolean case_sensitive);


/*!
 * @function	gw_strdel_chrsry
 * @abstract	Removes all the consecutive series of the
 * 				specified character in the given string.
 * @discussion	This function removes all the consecutive series
 * 				of the specified character. In fact it removes the
 * 				consecutive series of these character by only one
 * 				of this character. The given string will modify.<br>
 * 				For the string <i>"Hello    world!!"</i> with the given
 * 				character <i>' '</i>, this function will modify the given
 * 				string to <i>"Hello world!!"</i>.
 * @param	str	the string to removed all the consecutive series
 * @result	Returns number of deleted characters.<br>
 */
gint gw_strdel_chrsry ( gchar *str, const gchar chr);


/*!
 * @function	gw_str_trim_doubled_char
 * @abstract	Trims all doubled characters in the string.
 * @discussion	This function trims all doubled characters in the string.
 * @param	str	the string to trim
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_trim_doubled_char ( gchar *str);


/*!
 * @function	gw_str_trim
 * @abstract	Removes white space from both begin  and ends of this string.
 * @discussion	This function removes white space from both begins and ends of this string.
 *				If the string is only white spaces, this functions returns the empty
 *				string.
 * @param	str	the string to removes white space
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_trim ( gchar *str);


/*!
 * @function	gw_str_trim2
 * @abstract	Removes white space from both begins and ends of this string.
 * @discussion	This function removes white space from both begins ends of this string.
 *				If the string is only white spaces, this functions returns the empty
 *				string.
 * @param	str	the string to removes white space
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_trim2 ( gchar *str);


/*!
 * @function	gw_str_trim_left
 * @abstract	Removes white space from begins of this string.
 * @discussion	This function removes white space from begins of this string.
 *				If the string is only white spaces, this functions returns the empty
 *				string.
 * @param	str	the string to removes white space
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_trim_left ( gchar *str);


/*!
 * @function	gw_str_trim_right
 * @abstract	Removes white space from ends of this string.
 * @discussion	This function removes white space from ends of this string.
 *				If the string is only white spaces, this functions returns the empty
 *				string.
 * @param	str	the string to removes white space
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_trim_right ( gchar *str);


/*!
 * @function	gw_str_delete_char
 * @abstract	Deletes all specified characters in the string.
 * @discussion	This function deletes all specified character in the string.
 * @param	str	the string to delete character
 * @param	c	character to delete
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_delete_char ( gchar *str, gchar c);


/*!
 * @function	gw_str_replace_char
 * @abstract	Replace all specified characters by another in the string.
 * @discussion	This function replace all specified character by another in the string.
 * @param	str	the string to replace one character by another
 * @param	before	character to replace
 * @param	after	new character
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_replace_char ( gchar *string, gchar before, gchar after);


/*!
 * @function	gw_str_substr
 * @abstract	Gets the substring of a string.
 * @discussion	This function gets the substring of a string. The substring begins
 *		at the specified index begin and extends to the character at index end.
 *		Thus the length of the substring is end+1-begin
 * @param	str	the string to gets substring
 * @param	begin	begin index
 * @param	end	end index
 * @param	dest	destination of the substring (Note that dest must point to a buffer of sufficient size, size must bigger than end+1-begin)
 * @result	Returns the lenght of the substring.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_substr ( const gchar *str, gint begin, gint end, gchar *dest);


/*!
 * @function	gw_str_dupsubstr
 * @abstract	Gets and allocates the substring of a string.
 * @discussion	This function gets and allocates the substring of a string. The substring begins
 *		at the specified index begin and extends to the character at index end.
 *		Thus the length of the substring is end+1-begin
 * @param	str	the string to gets substring
 * @param	begin	begin index
 * @param	end	end index
 * @param	dest	destination of the substring (Note that dest must be freed with g_free)
 * @result	Returns the lenght of the substring.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_dupsubstr ( const gchar *str, gint begin, gint end, gchar **dest);


/*!
 * @function	gw_str_to_lower
 * @abstract	Converts an upper-case string to lower-case.
 * @discussion	This function converts an upper-case string to the corresponding
 *		lower-case string.
 * @param	str	the string to convert
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_to_lower ( gchar *str);


/*!
 * @function	gw_str_to_upper
 * @abstract	Converts an lower-case string to upper-case.
 * @discussion	This function converts an lower-case string to the corresponding
 *		upper-case string.
 * @param	str	the string to convert
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_to_upper ( gchar *str);


/*!
 * @function	gw_str_to_ascii
 * @abstract	Converts an  string to ascii
 * @discussion	This function converts a string to the corresponding.
 *		ascii string. Replace all non-ascii caracters by spaces
 *		caracters.
 * @param	str	the string to convert
 * @param	len	length of caracters to check. If len equals <i>-1</i>
 *			parse all string.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_str_to_ascii ( gchar *str, gint len);


/*!
 * @function	gintlen
 * @abstract	Gets the length of an integer.
 * @discussion	This function gets the length of an integer.<br>
 *		For example :<br>
 *		gintlen ( 100) returns 3.<br>
 *		gintlen ( 99) returns 2.<br>
 *		gintlen ( 1254) returns 4.<br>
 * @param	in	the integer to get lenght
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gintlen ( const gint n);


gchar * gw_time_to_str ( gulong t, const gchar *format) ;
gchar * gw_time_to_str_df ( gulong t);


#endif

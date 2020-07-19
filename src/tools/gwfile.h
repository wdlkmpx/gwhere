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
 * @header	gwfile.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a tool component for files.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/05/19
 * @see		gwsupport.h
 * @see		zlib.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	Zlib Web Site <http://www.zlib.org>
 * @ref		gwfile.c
 * @author	Author <zero@gwhere.org>
 * @author	Luis PARRAVICINI
 */


#ifndef GW_TOOLS_FILE_H
#define GW_TOOLS_FILE_H


#include <stdio.h>

#include <zlib.h>
#include "data/gwdata.h"


/*! @define	MAX_LINE	The max line size (to read lines in files) */
#define MAX_LINE 666


/*!
 * @function	gw_file_copy
 * @abstract	Copies file
 * @discussion	This function copies a file  to another file.<br>
 * @param	source		source file  to copy
 * @param	dest		destination file for copy
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
int gw_file_copy ( const gchar *source, const gchar *dest);


/*!
 * @function	gw_file_read_until_c
 * @abstract	Reads caracters in a file
 * @discussion	This function reads caracters in a file until a specified caractere.<br>
 * @param	fic		the file where extract caracters
 * @param	c		the delimitor caracter
 * @param	len		the line max size
 * @result	the string when it's done.<br>
 *		Returns <i>NULL</i> when an error occured or when the caracter aren't in the file.
 */
gchar * gw_file_read_until_c ( int fic, gchar c, int len);


/*!
 * @function	gw_zfile_read_until_c
 * @abstract	Reads caracters in a file
 * @discussion	This function reads caracters in a file until a specified caractere.<br>
 *		If len is <i>-1</i> readed line has no limits and the
 *		string will be allocated.
 * @param	fic		the compressed file where extract caracters
 * @param	c		the delimitor caracter
 * @param	len		th eline max size
 * @result	the string when it's done.<br>
 *		Returns <i>NULL</i> when an error occured or when the caracter aren't in the file.
 */
gchar * gw_zfile_read_until_c ( gzFile fic, gchar c, int len);


gchar * gw_file_readline_sb ( FILE *fic, GWStringBuffer **sb);


/*!
 * @function	gw_file_readline
 * @abstract	Reads line in a file
 * @discussion	This function reads a line in a file.<br>
 *		If len is <i>-1</i> readed line has no limits and the
 *		string will be allocated.
 * @author	Sébastien LECACHEUR
 * @param	fic	the file where extract line
 * @param	buf	the string to store readed line
 * @param	len	the line max size
 * @result	the string when it's done.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_file_readline ( int fic, gchar *buf, int len);


/*!
 * @function	gw_zfile_readline_sb
 * @abstract	Reads line in a compressed file
 * @discussion	This function reads a line in a compressed file.<br>
 * @param	fic	the compressed file where extract line
 * @param	sb	the string buffer to store readed line
 * @result	the string when it's done.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_zfile_readline_sb ( gzFile fic, GWStringBuffer **sb);


/*!
 * @function	gw_zfile_readline
 * @abstract	Reads line in a compressed file
 * @discussion	This function reads a line in a compressed file.<br>
 *		If len is <i>-1</i> readed line has no limits and the
 *		string will be allocated. Otherwise the buffer must be
 *		allocated before call gw_zfile_readline().
 * @author	Luis PARRAVICINI
 * @param	fic	the compressed file where extract line
 * @param	buf	the string to store readed line
 * @param	len	the line max size
 * @result	the string when it's done.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_zfile_readline ( gzFile fic, gchar **buf, int len);


/*!
 * @function	gw_file_get_size
 * @abstract	Gets the size of a file
 * @discussion	This function gets the size of a file.<br>
 * @author	Grégory BLOQUEL
 * @param	file	the file to get size
 * @result	the file size.<br>
 *		Returns <i>-1</i> when an error occured.
 */
long gw_file_get_size ( FILE * file);


/*!
 * @function	gw_file_exists
 * @abstract	Tests whether the file denoted by this abstract pathname exists.
 * @discussion	This function tests whether the file denoted by this abstract pathname exists.<br>
 * @param	pathname	file name
 * @result	an error code.<br>
 *		Returns <i>0</i> if and only if the file denoted by this abstract pathname exists.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
int gw_file_exists ( const gchar *pathname);


/*!
 * @function	gw_file_get_name
 * @abstract	Tests whether the file denoted by this abstract pathname exists.
 * @discussion	This function returns the name of the file or directory denoted
 *				by this abstract pathname. This is just the last name in the
 *				pathname's name sequence. If the pathname's name sequence is empty,
 *				then the NULL pointer is returned.<br>
 *				Note that the returned string should be freed by g_free().<br>
 * @param	pathname	file name
 * @result	file name.<br>
 *		Returns <i>NULL</i> otherwise or when an error occured.
 */
gchar * gw_file_get_name ( const gchar *pathname);


/*!
 * @function	gw_file_mkdir
 * @abstract	Creates the directory named by this abstract pathname.
 * @discussion	This function creates the directory named by this abstract pathname.<br>
 * @param	pathname	directory pathname
 * @result	an error code.<br>
 *		Returns <i>0</i> if the directory was created or if the directory already exists.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
int gw_file_mkdir ( const gchar *pathname);


/*!
 * @function	gw_file_mkdirs
 * @abstract	Creates the directory named by this abstract pathname
 * @discussion	This function creates the directory named by this abstract pathname,
 *		including any necessary but nonexistent parent directories. Note that
 *		if this operation fails it may have succeeded in creating some of the
 *		necessary parent directories.<br>
 *		Note that the abstract pathname should not end with "/" character.<br>
 * @param	pathname	directory pathname
 * @result	an error code.<br>
 *		Returns <i>0</i> if the directory was created, along with all necessary
 *		parent directories or if the directory already exists.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
int gw_file_mkdirs ( const gchar *pathname);


/*!
 * @function	gw_zfile_uncompress
 * @abstract	Uncompresses source file to destination file.
 * @discussion	This function uncompresses source file to destination file.<br>
 * @param	in_pathname	source file pathname
 * @param	out_pathname	destination file pathname
 * @result	an error code.<br>
 *		Returns <i>0</i> cannot uncompress the source file.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
int gw_zfile_uncompress ( const gchar *in_filepath, const gchar *out_filepath);


#endif

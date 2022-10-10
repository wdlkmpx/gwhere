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
 * @header	gwencode.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a tool component to encode/decode files or strings.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		glib.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwencode.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_TOOLS_ENCODE_H
#define GW_TOOLS_ENCODE_H


#include <glib.h>


/*!
 * @function	gw_encode_file_base64
 * @abstract	Encodes a file to base 64
 * @discussion	This function encodes a file to base 64.
 * @param	file1	source file to encode
 * @param	file2	destination file
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
 gint gw_encode_file_base64 ( gchar *src, gchar *dst);


/*!
 * @function	gw_decode_file_base64
 * @abstract	Decodes a file to base 64
 * @discussion	This function decodes a file to base 64.
 * @param	file1	source file to decode
 * @param	file2	destination file
 * @result	Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_decode_file_base64 ( gchar *src, gchar *dst);


#endif

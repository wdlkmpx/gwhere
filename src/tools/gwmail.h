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
 * @header	gwmail.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a tool component to send mails.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/09/03
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @ref		gwmail.c
 * @author	Author <gregory.bloquel@fnac.net>
 * @author	Grégory BLOQUEL
 * @author	Sébastien LECACHEUR
  */


#ifndef GW_TOOLS_MAIL_H
#define GW_TOOLS_MAIL_H


/*!
 * @function	gw_mail_check_msg
 * @abstract	Checks if the server doesn't return an error.
 * @discussion	This function checks if the server doesn't return an error.<br>
 * @param	msg		server response
 * @param	code		error code to check
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
int gw_mail_check_msg ( char * msg, char * code);


/*!
 * @function	gw_mail_read_msg
 * @abstract	Reads messages on a socket.
 * @discussion	This function reads messages on a socket.<br>
 * @param	sd		socket descriptor
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
int gw_mail_read_msg ( int sd);


/*!
 * @function	gw_mail_send_msg
 * @abstract	Sends messages on a socket.
 * @discussion	This function sends messages on a socket.<br>
 * @param	sd		socket descriptor
 * @param	msg		message to send
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
int gw_mail_send_msg ( int sd, char * msg);


/*!
 * @function	gw_mail_attachment_encode_base64_and_send
 * @abstract	Encodes in base 64 and sends a file on a socket.
 * @discussion	This function encodes in base 64 and sends a file on a socket.<br>
 * @param	sd		socket descriptor
 * @param	file		file name to encode and send
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
int gw_mail_attachment_encode_base64_and_send ( int sd, char * file );


/*!
 * @function	gw_mail_send_mail
 * @abstract	Sends a mail.
 * @discussion	This function sends a mail.<br>
 * @param	hostname	server host name
 * @param	server_port	server port
 * @param	from		mail "from" field
 * @param	to		mail "to" field
 * @param	cc		mail "cc" field
 * @param	bcc		mail "bcc" field
 * @param	object		mail "object" field
 * @param	msg		mail message
 * @param	file		file name to attach
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
int gw_mail_send_mail ( char * hostname, int server_port, char * from, char * to, char * cc, char * bcc, char * object, char * msg, char * file);


/*!
 * @function	gw_mail_check_email_list
 * @abstract	Checks an email list format
 * @discussion	This function checks an email list format.<br>
 *		An email list have good format if each email address are seperated by ";" character and if
 *		each email address have an "@" character.
 * @param	email_list	email list to check
 * @result	returns <i>TRUE</i> if the email list have the good format.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_mail_check_email_list ( const char * email_list);


#endif

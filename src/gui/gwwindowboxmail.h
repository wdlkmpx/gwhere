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
 * @header	gwwindowboxmail.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwwindowboxmail.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_MAIL_WINDOW_BOX_H
#define GW_GUI_GW_MAIL_WINDOW_BOX_H


/*!
 * @function	gw_mail_window_box_create
 * @abstract	Creates a mail window box.
 * @discussion	This function creates a mail window box.
 * @param	w		the parent window
 * @param	file_name	the catalog file name
 * @result	the mail box window.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_mail_window_box_create ( GtkWindow *window, gchar *file_name);


/*!
 * @function	gw_mail_window_box_get_main_window
 * @abstract	Gets the parent window.
 * @discussion	This function gets the parent window of the mail window box.
 * @param	w	the mail window box
 * @result	the parent window of the mail window box
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_mail_window_box_get_main_window ( GtkWindow *w);


/*!
 * @function	gw_mail_window_box_get_to
 * @abstract	Gets the "TO" field.
 * @discussion	This function gets the "TO" field of the mail window box.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the mail window box
 * @result	the field "TO".<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_mail_window_box_get_to ( GtkWindow *w);


/*!
 * @function	gw_mail_window_box_get_cc
 * @abstract	Gets the "CC" field.
 * @discussion	This function gets the "CC" field of the mail window box.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the mail window box
 * @result	the field "CC".<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_mail_window_box_get_cc ( GtkWindow *w);


/*!
 * @function	gw_mail_window_box_get_bcc
 * @abstract	Gets the "BCC" field.
 * @discussion	This function gets the "BCC" field of the mail window box.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the mail window box
 * @result	the field "BCC".<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_mail_window_box_get_bcc ( GtkWindow *w);


/*!
 * @function	gw_mail_window_box_get_subject
 * @abstract	Gets the subject.
 * @discussion	This function gets the subject of the mail window box.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the mail window box
 * @result	the subject.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_mail_window_box_get_subject ( GtkWindow *w);


/*!
 * @function	gw_mail_window_box_get_msg
 * @abstract	Gets the message.
 * @discussion	This function gets the message of the mail window box.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the mail window box
 * @result	the message.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_mail_window_box_get_msg ( GtkWindow *w);


/*!
 * @function	gw_mail_window_box_get_file_path
 * @abstract	Gets the file path.
 * @discussion	This function gets the file path of the mail window box.
 *		It's a new allocated string and must be freed with g_free().<br>
 * @param	w	the mail window box
 * @result	the file path.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_mail_window_box_get_file_path ( GtkWindow *w);


/*!
 * @function	gw_mail_window_box_get_option_attach_file
 * @abstract	Gets if attach file option is checked.
 * @discussion	This function gets if attach file option is checked.
 * @param	w	the mail window box
 * @result	Returns <i>TRUE</i> if option is checked.<br>
 *		Returns <i>NULL</i> otherwise or when an error occured.
 */
gboolean gw_mail_window_box_get_option_attach_file ( GtkWindow *w);


#endif

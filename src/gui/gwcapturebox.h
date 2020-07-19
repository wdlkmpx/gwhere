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
 * @header	gwcapturebox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to text field window box.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwcapturebox.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_CAPTURE_BOX_H
#define GW_GUI_GW_CAPTURE_BOX_H


/*!
 * @function	gw_capture_box_create
 * @abstract	Creates a capture window box.
 * @discussion	This function creates a capture window box. If the validate callback function
 *		is <i>NULL</i>, the window is destroyed when the user clicks validate the capture box.
 * @param	w		the parent window
 * @param	title		the window box title
 * @param	subject		the text which is displayed in the capture box
 * @param	text		the answer which is displayed in the field text
 * @param	ok		the function which will be call when user validate the capture box
 * @result	the capture box window.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GtkWidget * gw_capture_box_create ( GtkWindow *window, gchar *title, gchar *subject, gchar *text, GtkSignalFunc ok);


/*!
 * @function	gw_capture_box_get_text
 * @abstract	Gets the text field.
 * @discussion	This function gets the text field value.
 *		It's a new allocated string and must free with g_free().<br>
 * @param	w	the capture box window
 * @result	the filled text value of the capture box.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_capture_box_get_text ( GtkWindow *w);


/*!
 * @function	gw_capture_box_get_main_window
 * @abstract	Gets the parent window.
 * @discussion	This function gets the parent window of the capture box.
 * @param	w	the capture box window
 * @result	the parent window of the capture box.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GtkWindow * gw_capture_box_get_main_window ( GtkWindow *w);


/*!
 * @function	gw_capture_box_destroy
 * @abstract	Notifies the callback event of destroy.
 * @discussion	This function notifies the callback event of destroy.
 * @param	w	the capture box window
 * @param	seft_window	pointer to the capture box window reference
 * @result	the parent window of the capture box.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gint gw_capture_box_destroy ( GtkWindow *w, GtkWidget **self_window);


#endif

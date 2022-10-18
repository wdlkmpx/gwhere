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
 * @header	gwmisc.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to diplay message box.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		gtk/gtk.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwmisc.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_MISC_H
#define GW_GUI_GW_MISC_H


/*!
 * @function	gw_msg_box_create
 * @abstract	Creates the message box window.
 * @discussion	This function creates the message box window.
 * @param	w	main window
 * @param	title	the window title
 * @param	msg	the message to display
 */
void gw_msg_box_create ( GtkWindow *w, gchar *title, gchar *msg);


/*!
 * @function	gw_file_chooser_box
 * @abstract	Creates and shows a file selection window box.
 * @discussion	This function creates and shows a file selection box.
 * @param	title		the file selection box title
 * @param	filename	the default file name
 * @param	ok		the function which will be call when user clicks on ok button
 * @param	cancel		the function which will be call when user clicks on cancel button
 */
void gw_file_chooser_box (gchar *title,
                          gchar *filename,
                          GtkWindow *parent_window,
                          gpointer ok_func,
                          gpointer cancel_func);

/*!
 * @function	gw_input_box
 * @abstract	Creates a capture window box.
 * @discussion	This function creates an input box. If the validate callback function
 *		is <i>NULL</i>, the window is destroyed when the user clicks validate the capture box.
 * @param	w		the parent window
 * @param	title		the window box title
 * @param	subject		the text which is displayed in the capture box
 * @param	text		the answer which is displayed in the field text
 * @param	ok		the function which will be call when user validate the capture box
 */
void gw_input_box (GtkWindow *window, gchar *title, gchar *subject,
                   gchar *text, gpointer ok_func);


/*!
 * @function	gw_oknocancel_box
 * @abstract	Creates a dialog window box.
 * @discussion	This function creates a dialog window box.
 * @param	window	parent window (if is <i>NULL</i>, the dialog box is not modal
 * @param	title	the window box title
 * @param	text	the message which is displayed in the text area
 * @param	ok	the function which will be call when user validate the dialog box
 * @param	no	the function which will be call when user answer no to the dialog box
 * @param	cancel	the function which will be call when user cancel the dialog box
 * @param	data	user data (usefull for callback function)
 */
void gw_oknocancel_box (GtkWindow *window, gchar *title, gchar *text,
                        gpointer ok_func,
                        gpointer no_func,
                        gpointer cancel_func,
                        gpointer data);

/*!
 * @function	gw_text_box
 * @abstract	Creates a filled text box.
 * @discussion	This function creates a filled text box. If the
 *		ok callback function is <i>NULL</i> the filled
 *		text box is destroy when the user clicks on
 *		ok button.
 * @param	w		refence to the parent window
 * @param	title		window title
 * @param	subject		frame title
 * @param	text		default text value
 * @param	ok		ok callback function
 */
void gw_text_box (GtkWindow *window, gchar *title,
                  gchar *subject, gchar *text,
                  gpointer ok_func);

#endif

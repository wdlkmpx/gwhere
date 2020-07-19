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
 * @header	gwdialogbox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to diplay dialog box.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwdialogbox.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_DIALOG_BOX_H
#define GW_GUI_GW_DIALOG_BOX_H


/*!
 * @function	gw_dialog_box_create
 * @abstract	Creates a dialog window box.
 * @discussion	This function creates a dialog window box.
 * @param	window	parent window (if is <i>NULL</i>, the dialog box is not modal
 * @param	title	the window box title
 * @param	text	the message which is displayed in the text area
 * @param	ok	the function which will be call when user validate the dialog box
 * @param	no	the function which will be call when user answer no to the dialog box
 * @param	cancel	the function which will be call when user cancel the dialog box
 * @param	data	user data (usefull for callback function)
 * @result	the dialog box window.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_dialog_box_create ( GtkWindow *window, gchar *title, gchar *text, GtkSignalFunc ok, GtkSignalFunc no, GtkSignalFunc cancel, gpointer data);


/*!
 * @function	gw_dialog_box_get_user_data
 * @abstract	Gets previously stored user data.
 * @discussion	This function gets previously stored user data.
 * @param	w	dialog box window
 * @result	user data
 */
gpointer gw_dialog_box_get_user_data ( GtkWindow *w);


/*!
 * @function	gw_dialog_box_get_parent_window
 * @abstract	Gets the parent window.
 * @discussion	This function gets the parent window of application.
 * @param	w	dialog box window
 * @result	dialog box' parent window
 */
GtkWindow * gw_dialog_box_get_parent_window ( GtkWindow *w);


#endif

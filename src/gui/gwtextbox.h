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
 * @header	gwtextbox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for filled text box.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwtextbox.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_TEXT_BOX_H
#define GW_GUI_GW_TEXT_BOX_H


/*!
 * @function	gw_text_box_create
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
 * @result	the filled text box.<br>
 * 		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_text_box_create ( GtkWindow *parent, gchar *title, gchar *subject, gchar *text, GtkSignalFunc ok);


/*!
 * @function	gw_text_box_get_text
 * @abstract	Gets the text value
 * @discussion	This function gets the text value.
 * @param	w		the filled text box
 * @result	the text value. Must be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_text_box_get_text ( GtkWidget *w);


/*!
 * @function	gw_text_box_get_parent_window
 * @abstract	Gets the parent window
 * @discussion	This function gets the parent window.
 * @param	w		the filled text box
 * @result	the parent window.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_text_box_get_parent_window ( GtkWidget *w);


#endif

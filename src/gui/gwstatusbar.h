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
 * @header	gwstatusbar.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for the status bar.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwstatusbar.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_STATUS_BAR_H
#define GW_GUI_GW_STATUS_BAR_H


/*!
 * @function	gw_status_bar_create
 * @abstract	Creates a status bar.
 * @discussion	This function creates a status bar.
 * @param	w	refence to the main window
 * @result	the status bar.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_status_bar_create ( GtkWindow *w);


/*!
 * @function	gw_status_bar_create_and_add
 * @abstract	Creates a status bar and adds to the container.
 * @discussion	This function creates a status bar and add to the container.
 * @param	w		refence to the main window
 * @param	parent		parent container
 * @result	the status bar.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_status_bar_create_and_add ( GtkWindow *w, GtkWidget *parent);


/*!
 * @function	gw_status_bar_get_first_status
 * @abstract	Gets the first status.
 * @discussion	This function gets the first status.
 * @param	w		refence to the main window
 * @result	the first status.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkStatusbar * gw_status_bar_get_first_status ( GtkWindow *w);


/*!
 * @function	gw_status_bar_get_second_status
 * @abstract	Gets the second status.
 * @discussion	This function gets the second status.
 * @param	w		refence to the main window
 * @result	the second status.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkStatusbar * gw_status_bar_get_second_status ( GtkWindow *w);


/*!
 * @function	gw_status_bar_put_messages
 * @abstract	Puts messages into status bar.
 * @discussion	This function puts messages into status bar.<br>
 * @param	w		refence to the main window
 * @param	first_msg		the first message
 * @param	second_msg		the second message
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_put_messages ( GtkWindow *w, gchar *first_msg, gchar *second_msg);


#endif

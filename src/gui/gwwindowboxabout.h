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
 * @header	gwwindowboxabout.h
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
 * @ref		gwwindowboxabout.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_WINDOW_BOX_ABOUT_H
#define GW_GUI_WINDOW_BOX_ABOUT_H


/*!
 * @function	gw_window_box_about_create
 * @abstract	Creates the about window.
 * @discussion	This function creates the about window. This window
 *		can be destroyed by clicking on.
 * @param	win	refence to the main window
 * @result	the about window.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_window_box_about_create ( GtkWindow *window);


/*!
 * @function	gw_window_box_about_destroy
 * @abstract	Destroyes the about window.
 * @discussion	This function destroyes the about window. This window
 *		can be destroyed by clicking on.
 * @param	w	refence to the about window
 * @param	self_window	refence to the pointer of about window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_window_box_about_destroy ( GtkWindow *w, GtkWidget **self_window);


#endif

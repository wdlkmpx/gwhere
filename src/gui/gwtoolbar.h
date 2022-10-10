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
 * @header	gwtoolbar.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for handle tool bar.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwtoolbar.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_TOOL_BAR_H
#define GW_GUI_GW_TOOL_BAR_H


/*!
 * @function	gw_tool_bar_create
 * @abstract	Creates a handle tool bar.
 * @discussion	This function creates a handle tool bar.
 * @param	w		refence to the main window
 * @result	the handle tool bar.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_tool_bar_create ( GtkWindow * w);


/*!
 * @function	gw_tool_bar_create_and_add
 * @abstract	Creates a handle tool bar and adds to the container.
 * @discussion	This function creates a handle tool bar and adds to the container.
 * @param	w		refence to the main window
 * @param	parent		reference to the container
 * @result	the handle tool bar.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_tool_bar_create_and_add ( GtkWindow * w, GtkWidget *parent);


#endif

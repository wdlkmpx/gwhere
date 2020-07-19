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
 * @header	gwmenuhelpcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a link component between menu help and functionalities.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/02/11
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwmenuhelpcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_MENU_HELP_CALLBACK_H
#define GW_GUI_GW_MENU_HELP_CALLBACK_H


/*!
 * @function	gw_menu_help_about_click
 * @abstract	Launches from menu help : about.
 * @discussion	This function launches from the menu help the functionality : about
 * @param	m	menu item invoker
 * @param	w	reference to the main window
 * @result	Returns <i>TRUE</i> if the event is submited correctly.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_menu_help_about_click ( GtkMenuItem *m, GtkWindow *w);


#endif

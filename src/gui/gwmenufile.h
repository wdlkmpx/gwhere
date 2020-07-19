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
 * @header	gwmenufile.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for menu file.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwmenufile.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_MENU_FILE_H
#define GW_GUI_GW_MENU_FILE_H


/*!
 * @function	gw_menu_file_create
 * @abstract	Creates a menu file.
 * @discussion	This function creates a menu file.
 * @param	w	refence to the main window
 * @param	ag	accel group
 * @param	parent	reference to the container
 * @result	the menu file.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_menu_file_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent);


/*!
 * @function	gw_menu_file_set_recents_files
 * @abstract	Sets the list of recents opened files.
 * @discussion	This function sets the list of recents opened files.
 * @param	w	refence to the main window
 * @param	files	list of files
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_menu_file_set_recents_files ( GtkWindow *w, gchar **files);


gboolean gw_menu_file_set_import ( GtkWindow *w, gchar **plugins);


gboolean gw_menu_file_set_export ( GtkWindow *w, gchar **plugins);


#endif

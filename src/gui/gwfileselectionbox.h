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
 * @header	gwfileselectionbox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to select a file.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwfileselectionbox.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_FILE_SELECTION_BOX_H
#define GW_GUI_GW_FILE_SELECTION_BOX_H


/*!
 * @function	gw_file_selection_box_create
 * @abstract	Creates and shows a file selection window box.
 * @discussion	This function creates and shows a file selection box.
 * @param	title		the file selection box title
 * @param	filename	the default file name
 * @param	ok		the function which will be call when user clicks on ok button
 * @param	cancel		the function which will be call when user clicks on cancel button
 * @result	the file selection box.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_file_selection_box_create ( gchar *title, gchar *filename, GCallback ok, GCallback cancel);

#endif

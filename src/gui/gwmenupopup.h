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
 * @header	gwmenupopup.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for menu popup.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwmenupopup.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_MENU_POPUP_H
#define GW_GUI_GW_MENU_POPUP_H


/*!
 * @function	gw_menu_popup_create
 * @abstract	Creates the general popup menu.
 * @discussion	This function creates the general popup menu. This
 *		popup menu allows to open, close a catalog, exit program,...
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_create ( GtkWindow *w);


/*!
 * @function	gw_menu_popup_create_and_show
 * @abstract	Creates the general popup menu and shows it.
 * @discussion	This function creates the general popup menu and shows it.
 *		This popup menu allows to open, close a catalog, exit program,...
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_create_and_show ( GtkWindow *w);


/*!
 * @function	gw_menu_popup_catalog_create
 * @abstract	Creates the catalog popup menu.
 * @discussion	This function creates the catalog popup menu. This popup
 *		menu allows to open, close a catalog, exit program,...
 *		and view catalog properties...
 * @param	node	the node in the tree where is the catalog root
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_catalog_create ( GtkCTreeNode *node, GtkWindow *w);


/*!
 * @function	gw_menu_popup_catalog_create_and_show
 * @abstract	Creates the catalog popup menu and shows it.
 * @discussion	This function creates the catalog popup menu and shows it.
 *		This popup menu allows to open, close a catalog, exit
 *		program,... and view catalog properties...
 * @param	node	the node in the tree where is the catalog root
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_catalog_create_and_show ( GtkCTreeNode *node, GtkWindow *w);


/*!
 * @function	gw_menu_popup_disk_create
 * @abstract	Creates the disk popup menu.
 * @discussion	This function creates the disk popup menu. This popup menu
 *		allows to open, close a catalog, exit program,... and view
 *		disk properties...
 * @param	node	the node in the tree where is the disk root
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_disk_create ( GtkCTreeNode *node, GtkWindow *w);


/*!
 * @function	gw_menu_popup_disk_create_and_show
 * @abstract	Creates the disk popup menu and shows it.
 * @discussion	This function creates the disk popup menu and shows it.
 *		This popup menu allows to open, close a catalog, exit
 *		program,... and view disk properties...
 * @param	node	the node in the tree where is the disk root
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_disk_create_and_show ( GtkCTreeNode *node, GtkWindow *w);


/*!
 * @function	gw_menu_popup_dir_create
 * @abstract	Creates the folder popup menu.
 * @discussion	This function creates the folder popup menu. This popup
 *		menu allows to open, close a catalog, exit program,...
 *		and view folder properties...
 * @param	node	the node in the tree where is the folder
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_dir_create ( GtkCTreeNode *node, GtkWindow *w);


/*!
 * @function	gw_menu_popup_dir_create_and_show
 * @abstract	Creates the folder popup menu and shows it.
 * @discussion	This function creates the folder popup menu and shows it.
 *		This popup menu allows to open, close a catalog, exit
 *		program,... and view folder properties...
 * @param	node	the node in the tree where is the folder
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_dir_create_and_show ( GtkCTreeNode *node, GtkWindow *w);


/*!
 * @function	gw_menu_popup_file_create
 * @abstract	Creates the file popup menu.
 * @discussion	This function creates the file popup menu. This popup menu
 *		allows to open, close a catalog, exit program,... and view
 *		file properties...
 * @param	node	the node in the tree where is the dis root
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_file_create ( gpointer row, GtkWindow *w);


/*!
 * @function	gw_menu_popup_file_create_and_show
 * @abstract	Creates the file popup menu and shows it.
 * @discussion	This function creates the file popup menu and shows it.
 *		This popup menu allows to open, close a catalog, exit
 *		program,... and view file properties...
 * @param	node	the node in the tree where is the dis root
 * @param	w	the main window application
 * @result	the popup menu.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkMenu * gw_menu_popup_file_create_and_show ( gpointer row, GtkWindow *w);


#endif

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
 * @header	gwstatusbarcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component for the status bar callback.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwstatusbarcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_STATUS_BAR_CALLBACK_H
#define GW_GUI_GW_STATUS_BAR_CALLBACK_H


/*!
 * @function	gw_status_bar_put_msg_catalog
 * @abstract	Puts messages about catalog into status bar.
 * @discussion	This function puts messages about catalog into
 *		status bar. this function is called when the
 *		user select a catalog.
 * @param	w		refence to the main window
 * @param	ctree		tree catalog
 * @param	root		catalog root tree node
 * @param	num		number of disks
 * @param	size		total size of disks
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_put_msg_catalog ( GtkWindow *w, GtkCTree *ctree, GtkCTreeNode *root, gint num, gdouble size);


/*!
 * @function	gw_status_bar_put_msg_disk
 * @abstract	Puts messages about disk into status bar.
 * @discussion	This function puts messages about disk into
 *		status bar. This function is called when the
 *		user select a disk.<br>
 *		Set num to <i>0</i> when the disk is selected
 *		in the files list. In this case listed items
 *		will be one.
 * @param	w		refence to the main window
 * @param	name		disk name
 * @param	type		disk type
 * @param	size		total size of disk
 * @param	free		total free space of disk
 * @param	num		number of sub elements disks (in only one level)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_put_msg_disk ( GtkWindow *w, gchar *name, gchar *type, guint64 capacity, guint64 free, gdouble size, gint num);


/*!
 * @function	gw_status_bar_put_msg_dir
 * @abstract	Puts messages about dir into status bar.
 * @discussion	This function puts messages about dir into
 *		status bar. This function is called when the
 *		user select a dir.<br>
 *		Set num to <i>0</i> when the dir is selected
 *		in the files list. In this case listed items
 *		will be one.
 * @param	w		refence to the main window
 * @param	name		dir name
 * @param	size		total size of dir
 * @param	nb_files	number of files
 * @param	nb_subfolders	number of subfolders
 * @param	num		number of sub elements dir (in only one level)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_put_msg_dir ( GtkWindow *w, gchar *name, gdouble size, gint nb_files, gint nb_subfolders, gint num);


/*!
 * @function	gw_status_bar_put_msg_file
 * @abstract	Puts messages about file into status bar.
 * @discussion	This function puts messages about file into
 *		status bar. This function is called when the
 *		user select a file.<br>
 * @param	w		refence to the main window
 * @param	name		file name
 * @param	size		file size
 * @param	date		file date
 * @param	num		number of selected files
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_put_msg_file ( GtkWindow *w, gchar *name, gdouble size, gchar *date, gint num);


/*!
 * @function	gw_status_bar_set_catalog_explorer_page
 * @abstract	Updates status for the explorer tabbed pane.
 * @discussion	This function updates status for the explorer
 *		tabbed pane. This function is called when the
 *		user goes to the explorer tabbed pane.<br>
 * @param	w		refence to the main window
 * @param	n		number of selected items
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_set_catalog_explorer_page ( GtkWindow *w, gint n);


/*!
 * @function	gw_status_bar_set_catalog_search_page
 * @abstract	Updates status for the catalog search tabbed pane.
 * @discussion	This function updates status for the catalog
 *		search tabbed pane. This function is called
 *		when the user goes to the catalog search tabbed
 *		pane.<br>
 * @param	w		refence to the main window
 * @param	n		number of selected items
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_set_catalog_search_page ( GtkWindow *w, gint n);


/*!
 * @function	gw_status_bar_set_catalog_managment_page
 * @abstract	Updates status for the catalog managment tabbed pane.
 * @discussion	This function updates status for the catalog
 *		managment tabbed pane. This function is called
 *		when the user goes to the catalog managment
 *		tabbed pane.<br>
 * @param	w		refence to the main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_status_bar_set_catalog_managment_page ( GtkWindow *w);


#endif

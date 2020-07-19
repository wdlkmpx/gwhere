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
 * @header	gwnotebookmanagmentcallback.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI callack component to manage disks.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwnotebookmanagmentcallback.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_NOTEBOOK_MANAGMENT_CALLBACK_H
#define GW_GUI_GW_NOTEBOOK_MANAGMENT_CALLBACK_H


/*!
 * @function	gw_notebook_managment_load_device_list
 * @abstract	Loads the device list.
 * @discussion	This function loads the device list into the combo box.
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_load_device_list ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_scan_click
 * @abstract	Scans the device.
 * @discussion	This function scans the device. This function is called when
 *		the user click on the scan button.
 * @param	bt	button invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_managment_scan_click ( GtkWidget *bt, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_select_device
 * @abstract	Displays informations for selected device.
 * @discussion	This function displays informations for selected device. This
 *		function is called when the user selected a device in the
 *		device list.
 * @param	cmb	combo device list
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_select_device ( GtkWidget *cmb, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_refresh_info
 * @abstract	Refreshes informations for selected device.
 * @discussion	This function refreshes informations for selected device. This
 *		function is called when the user selected the option display
 *		information on device.
 * @param	chk	check button invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_refresh_info ( GtkWidget *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_refresh_categories
 * @abstract	Refreshes the list of categories.
 * @discussion	This function refreshes the list of categories
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_refresh_categories ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_stop_scan_disk
 * @abstract	Stops the scan of device.
 * @discussion	This function stops the scan of device.
 * @param	obj	event invoker
 * @param	data	an object (scan_disk_info)
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_notebook_managment_stop_scan_disk ( GtkObject *obj, gpointer data);


/*!
 * @function	gw_notebook_managment_set_current_statment
 * @abstract	Stops the scan of device.
 * @discussion	This function stops the scan of device.
 * @param	p	progress bar box
 * @param	current	current statment of processing
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_set_current_statment ( gpointer p, gfloat current);


/*!
 * @function	gw_capture_box_catalog_name_ok
 * @abstract	Creates a new catalog and relaunches the disk scanning.
 * @discussion	This function creates a new catalog and relaunches the disk scanning.
 * @param	w	button invoker
 * @param	data	capture box
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_capture_box_catalog_name_ok ( GtkWidget *w, gpointer data);


/*!
 * @function	gw_capture_box_disk_name_ok
 * @abstract	Filled the disk name and relaunches the disk scanning.
 * @discussion	This function filled the disk name and relaunches the disk scanning.
 * @param	w	button invoker
 * @param	data	capture box
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_capture_box_disk_name_ok ( GtkWidget *w, gpointer data);


/*!
 * @function	gw_notebook_managment_option_explore_tree_structure_click
 * @abstract	Saves the tree structure exploration option.
 * @discussion	This function saves the tree structure exploration option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_explore_tree_structure_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_option_explore_archive_click
 * @abstract	Saves the archives exploration option.
 * @discussion	This function saves the archives exploration option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_explore_archive_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_option_category_click
 * @abstract	Saves the recursively category setting option.
 * @discussion	This function saves the recursively category setting option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_category_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_option_description_click
 * @abstract	Saves the auto-extract description from files option.
 * @discussion	This function saves the auto-extract description from files option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_description_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_option_use_disk_label_click
 * @abstract	Saves the using volume name as disk name option.
 * @discussion	This function saves the using volume name as disk name option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_use_disk_label_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_option_use_pattern_click
 * @abstract	Saves the using an advanced pattern to generate disk name option.
 * @discussion	This function saves an advanced pattern to generate disk name option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_use_pattern_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_option_automount_click
 * @abstract	Saves the automount option.
 * @discussion	This function saves the automount option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_automount_click ( GtkToggleButton *chk, GtkWindow *w);


/*!
 * @function	gw_notebook_managment_option_eject_click
 * @abstract	Saves the auto-eject CD-Rom option.
 * @discussion	This function saves the auto-eject CD-Rom option.
 *		This function is called when the user click on option check box.
 * @param	chk	check box invoker
 * @param	w	main window
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_notebook_managment_option_eject_click ( GtkToggleButton *chk, GtkWindow *w);


#endif

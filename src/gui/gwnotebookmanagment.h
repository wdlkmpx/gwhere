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
 * @header	gwnotebookmanagment.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to manage disks.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwnotebookmanagment.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_NOTEBOOK_MANAGMENT_H
#define GW_GUI_GW_NOTEBOOK_MANAGMENT_H


/*!
 * @function	gw_notebook_managment_create
 * @abstract	Creates a tabbed pane for disk managment.
 * @discussion	This function creates a tabbed pane for disk managment.
 * @param	w		main window
 * @result	the tabbed pane<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_notebook_managment_create ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_create_and_add
 * @abstract	Creates a tabbed pane for disk managment and adds to the container.
 * @discussion	This function creates a tabbed pane for disk managment and add to the container.
 * @param	w		main window
 * @param	parent		parent notebook container
 * @result	the tabbed pane<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWidget * gw_notebook_managment_create_and_add ( GtkWindow *w, GtkNotebook *parent);


/*!
 * @function	gw_notebook_managment_set_device_dir
 * @abstract	Sets the device folder path.
 * @discussion	This function sets the device folder path.<br>
 *		<b>Warning</b> : this function do nothing at time!!
 * @param	w		main window
 * @param	device_dir	the device folder path
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_device_dir ( GtkWindow *w, gchar *device_dir);


/*!
 * @function	gw_notebook_managment_set_device_name
 * @abstract	Sets the device name.
 * @discussion	This function sets the device name.
 * @param	w		main window
 * @param	device_name	the device name
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_device_name ( GtkWindow *w, gchar *device_name);


/*!
 * @function	gw_notebook_managment_set_device_number
 * @abstract	Sets the device number archive.
 * @discussion	This function sets the device number archive.
 * @param	w		main window
 * @param	device_number	the device number archive
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_device_number ( GtkWindow *w, gchar *device_number);


/*!
 * @function	gw_notebook_managment_set_device_category
 * @abstract	Sets the device selected category name.
 * @discussion	This function sets the device selected category name.
 * @param	w		main window
 * @param	device_category	the device selected catagory name
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_device_category ( GtkWindow *w, gchar *device_category);


/*!
 * @function	gw_notebook_managment_set_option_automount
 * @abstract	Activates or desactivates the automount option.
 * @discussion	This function activates or desactivates the automount option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_automount ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_display_info
 * @abstract	Activates or desactivates the diplaying informations option.
 * @discussion	This function activates or desactivates the displaying informations option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_display_info ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_eject
 * @abstract	Activates or desactivates the auto-eject CD-Rom option.
 * @discussion	This function activates or desactivates the auto-eject CD-Rom option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_eject ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_category_recursive
 * @abstract	Activates or desactivates the recursively category setting option.
 * @discussion	This function activates or desactivates the recursively category setting option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_category_recursive ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_explore_tree_structure
 * @abstract	Activates or desactivates the tree structure exploration option.
 * @discussion	This function activates or desactivates the tree structure exploration option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_explore_tree_structure ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_explore_archive
 * @abstract	Activates or desactivates the archives exploration option.
 * @discussion	This function activates or desactivates the archives exploration option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_explore_archive ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_make_description
 * @abstract	Activates or desactivates the auto-extracting informations from files option.
 * @discussion	This function activates or desactivates the auto-extracting informations from files option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_make_description ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_use_pattern
 * @abstract	Activates or desactivates the using of an advnaced pattern to generate disk name option.
 * @discussion	This function activates or desactivates the using of an advnaced pattern to generate disk name option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_use_pattern ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_set_option_use_disk_label
 * @abstract	Activates or desactivates the using disk label as disk name option.
 * @discussion	This function activates or desactivates the using disk label as disk name option.
 * @param	w		main window
 * @param	b		<i>TRUE</i> to activate or <i>FALSE</i> to desactivate
 * @result	an error code<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> otherwise or when an error occured.
 */
gint gw_notebook_managment_set_option_use_disk_label ( GtkWindow *w, gboolean b);


/*!
 * @function	gw_notebook_managment_get_device_dir
 * @abstract	Gets the selected device path.
 * @discussion	This function gets the selected device path.
 * @param	w		main window
 * @result	the device path. Should be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_notebook_managment_get_device_dir ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_device_name
 * @abstract	Gets the device name.
 * @discussion	This function gets the device name.
 * @param	w		main window
 * @result	the device name. Should be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_notebook_managment_get_device_name ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_device_number
 * @abstract	Gets the device number archive.
 * @discussion	This function gets the device number archive.
 * @param	w		main window
 * @result	the device number archive. Should be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_notebook_managment_get_device_number ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_device_category
 * @abstract	Gets the selected device category name.
 * @discussion	This function gets the selected device category name.
 * @param	w		main window
 * @result	the device category name. Should be freed with g_free().<br>
 *		Returns <i>NULL</i> when an error occured.
 */
gchar * gw_notebook_managment_get_device_category ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_display_info
 * @abstract	Gets the displaying informations option value.
 * @discussion	This function gets the displaying informations option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_display_info ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_automount
 * @abstract	Gets the automount option value.
 * @discussion	This function gets the automount option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_automount ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_eject
 * @abstract	Gets the auto-eject CD-Rom option value.
 * @discussion	This function gets the auto-eject CD-Rom option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_eject ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_category_recursive
 * @abstract	Gets the recursively category setting option value.
 * @discussion	This function gets the recursively category setting option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_category_recursive ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_explore_tree_structure
 * @abstract	Gets the tree structure exploration option value.
 * @discussion	This function gets the tree structure exploration option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_explore_tree_structure ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_explore_archive
 * @abstract	Gets the archives exploration option value.
 * @discussion	This function gets the archives exploration option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_explore_archive ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_make_description
 * @abstract	Gets the auto-extract informations from files option value.
 * @discussion	This function gets the auto-extract informations from files option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_make_description ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_use_pattern
 * @abstract	Gets the using of an advanced pattern to generate disk name option value.
 * @discussion	This function gets the using of an advanced pattern to generate disk name option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_use_pattern ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_option_use_disk_label
 * @abstract	Gets the using disk label as disk name option value.
 * @discussion	This function gets the using disk label as disk name option value.
 * @param	w		main window
 * @result	Returns <i>TRUE</i> when the option if activated.<br>
 *		Returns <i>FALSE</i> otherwise or when an error occured.
 */
gboolean gw_notebook_managment_get_option_use_disk_label ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_combo_box_categories
 * @abstract	Gets the combo box categories.
 * @discussion	This function gets the combo box categories.
 * @param	w		main window
 * @result	the combo box categories.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkHBox * gw_notebook_managment_get_combo_box_categories ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_combo_box_device
 * @abstract	Gets the combo devices list.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the combo devices list.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkCombo * gw_notebook_managment_get_combo_box_device ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_label_device_info
 * @abstract	Gets the label of device informations.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the label.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkLabel * gw_notebook_managment_get_label_device_info ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_label_device_type
 * @abstract	Gets the label of device type.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the label.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkLabel * gw_notebook_managment_get_label_device_type ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_label_device_mounted
 * @abstract	Gets the label of device mount status.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the label.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkLabel * gw_notebook_managment_get_label_device_mounted ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_label_device_volume
 * @abstract	Gets the label of device volume name.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the label.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkLabel * gw_notebook_managment_get_label_device_volume ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_label_device_serial_number
 * @abstract	Gets the label of device serial number.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the label.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkLabel * gw_notebook_managment_get_label_device_serial_number ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_label_device_capacity
 * @abstract	Gets the label of device full capacity.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the label.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkLabel * gw_notebook_managment_get_label_device_capacity ( GtkWindow *w);


/*!
 * @function	gw_notebook_managment_get_label_device_free_space
 * @abstract	Gets the label of device free space.
 * @discussion	This function gets the combo devices list.
 * @param	w		main window
 * @result	the label.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkLabel * gw_notebook_managment_get_label_device_free_space ( GtkWindow *w);


#endif

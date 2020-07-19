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
 * @header	gwsettingswindowbox.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @see		gwsettingsinterface.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwsettingswindowbox.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_SETTINGS_WINDOW_BOX_H
#define GW_GUI_GW_SETTINGS_WINDOW_BOX_H

#include "gwsettingsinterface.h"


/*! @define	GW_REF_SETTINGS_WINDOW_BOX_NOTEBOOK_FUNCTION	The function of the current notebook */
#define GW_REF_SETTINGS_WINDOW_BOX_NOTEBOOK_FUNCTION "gw_ref_settings_window_box_notebook_function"
/*! @define	GW_REF_SETTINGS_MODULE	The settings module of the current notebook page */
#define GW_REF_SETTINGS_MODULE "gw_ref_settings_module"


/*!
 * @function	gw_settings_window_box_create
 * @abstract	Creates a settings window box.
 * @discussion	This function creates a settings window box.
 * @param	w		the parent window
 * @result	the settings window box.<br>
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_settings_window_box_create ( GtkWindow *window);


/*!
 * @function	gw_settings_window_box_load_sections
 * @abstract	Loads all sections of the settings window box.
 * @discussion	This function loads all sections of the settings window box.
 * @param	settings	settings window box
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.
 *		Returns <i>FALSE</i> when an error occured.
 */
gboolean gw_settings_window_box_load_sections ( GtkWindow *settings);


/*!
 * @function	gw_settings_window_box_set_modified
 * @abstract	Indicates to the settings that some values are modified.
 * @discussion	This function indicates to the settings that some values are modified.
 * @param	w	settings window box
 * @param	state	state is modified or no
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_settings_window_box_set_modified ( GtkWindow *w, gboolean state);


/*!
 * @function	gw_settings_window_box_get_ctree
 * @abstract	Gets the settings ctree.
 * @discussion	This function gets the settings ctree.
 * @param	w	settings window box
 * @result	the ctree of the settings window box
 *		Returns <i>NULL</i> when an error occured.
 */
GtkCTree * gw_settings_window_box_get_ctree ( GtkWindow *w);


/*!
 * @function	gw_settings_window_box_get_notebook
 * @abstract	Gets the settings notebook.
 * @discussion	This function gets the settings notebook.
 * @param	w	the settings window box
 * @result	the notebook of the settings window box
 *		Returns <i>NULL</i> when an error occured.
 */
GtkNotebook * gw_settings_window_box_get_notebook ( GtkWindow *w);

/*!
 * @function	gw_settings_window_box_get_ok_button
 * @abstract	Gets the ok button.
 * @discussion	This function gets the ok button.
 * @param	w	the settings window box
 * @result	the ok button of the settings window box
 *		Returns <i>NULL</i> when an error occured.
 */
GtkButton * gw_settings_window_box_get_ok_button ( GtkWindow *w);

/*!
 * @function	gw_settings_window_box_get_cancel_button
 * @abstract	Gets the cancel button.
 * @discussion	This function gets the cancel button.
 * @param	w	the settings window box
 * @result	the cancel button of the settings window box
 *		Returns <i>NULL</i> when an error occured.
 */
GtkButton * gw_settings_window_box_get_cancel_button ( GtkWindow *w);

/*!
 * @function	gw_settings_window_box_get_apply_button
 * @abstract	Gets the apply button.
 * @discussion	This function gets the apply button.
 * @param	w	the settings window box
 * @result	the apply button of the settings window box
 *		Returns <i>NULL</i> when an error occured.
 */
GtkButton * gw_settings_window_box_get_apply_button ( GtkWindow *w);


/*!
 * @function	gw_settings_window_box_get_main_window
 * @abstract	Gets the parent window.
 * @discussion	This function gets the parent window of the settings window box.
 * @param	w	the settings window box
 * @result	the parent window of the settings window box
 *		Returns <i>NULL</i> when an error occured.
 */
GtkWindow * gw_settings_window_box_get_main_window ( GtkWindow *w);


/*!
 * @function	gw_settings_window_box_apply_button_set_enable
 * @abstract	Sets the enable state of the apply button.
 * @discussion	This function sets the enable state of the apply button.
 * @param	w	the settings window box
 * @param	state	the enable state
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_settings_window_box_apply_button_set_enable ( GtkWindow *w, gboolean state);


/*!
 * @function	gw_settings_window_box_apply_button_get_enable
 * @abstract	Sets the enable state of the apply button.
 * @discussion	This function sets the enable state of the apply button.
 * @param	w	the settings window box
 * @result	enable state.<br>
 *		Returns <i>TRUE</i> if it is enabled.
 *		Returns <i>FALSE</i> if it is not enabled or when an error occured.
 */
gboolean gw_settings_window_box_apply_button_get_enable ( GtkWindow *w);


#endif

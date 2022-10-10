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
 * @header	gwsettinsginterface.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 *		In order to write a setting plugin, you must implement the 
 *		gw_plugin_settings_init_t public function. All others functions 
 *		may be privated but must be implemented too and loaded in the 
 *		gwsettingsmodule.<br>
 * @abstract	This is the interface for settings plugins.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/07/24
 * @ref		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @see		gwsettingsinterface.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_SETTINGS_INTERFACE_H
#define GW_GUI_GW_SETTINGS_INTERFACE_H


/*!
 * @typedef	gw_plugin_settings_pane_create_t
 *		Creates the pane to display in the setting window box.
 * @abstract	Functions specification
 * @param	settings	settings window box
 * @param	parent		container of the pane
 * @param	pane		pane to display
 * @return	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
typedef gint (*gw_plugin_settings_pane_create_t) ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane);


/*!
 * @typedef	gw_plugin_settings_pane_load_t
 *		Loads values of the pane.
 * @abstract	Functions specification
 * @param	pane	pane to load values
 * @return	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
typedef gint (*gw_plugin_settings_pane_load_t) ( GtkWidget *pane);


/*!
 * @typedef	gw_plugin_settings_pane_on_change_t
 *		Called when the pane is modified.
 * @abstract	Functions specification
 * @param	entry	invoker event
 * @param	pane	modified pane
 * @return	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
typedef gint (*gw_plugin_settings_pane_on_change_t) ( GtkEntry *entry, GtkWidget *pane);


/*!
 * @typedef	gw_plugin_settings_pane_apply_t
 *		Applies changes in the pane.
 * @abstract	Functions specification
 * @param	pane	pane to applay changes
 * @return	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
typedef gint (*gw_plugin_settings_pane_apply_t) ( GtkWidget *pane);


/*!
 * @typedef	gw_settings_module_s
 *		Settings module structure.
 * @abstract	This structure centralize all implemented functions of one settings module
 * @field	name		settings module name
 * @field	page		settings module page in notebook
 * @field	pane		settings module pane (to not destroy when free GWSettingsModule)
 * @field	settings_window	settings window box (to not destroy when free GWSettingsModule)
 * @field	child		table of all children ended by NULL
 * @field	create		create pane function
 * @field	load		load pane function
 * @field	on_change	on change event callback pane function
 * @field	apply		apply callback pane function
*/
typedef struct gw_settings_module_s
{
	gchar *name;
	GtkContainer *page;
	GtkWidget *pane;
	GtkWindow *settings_window;
	struct gw_settings_module_s **child;
	gw_plugin_settings_pane_create_t create;
	gw_plugin_settings_pane_load_t load;
	gw_plugin_settings_pane_on_change_t on_change;
	gw_plugin_settings_pane_apply_t apply;
}GWSettingsModule;


/*!
 * @typedef	gw_plugin_settings_init_t
 *		Inits the settings module data structure
 * @abstract	Functions specification
 * @param	module	pointer to the future settings module
 * @return	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
typedef gint (*gw_plugin_settings_init_t) ( GWSettingsModule **module);


/*!
 * @function	gw_settings_module_new
 * @abstract	Allocates a new GWSettingsModule structure.
 * @discussion	This function allocates a new GWSettingsModule structure.
 * @result	a settings module.<br>
 *		Returns <i>NULL</i> when an error occured
 */
GWSettingsModule * gw_settings_module_new ( );


/*!
 * @function	gw_settings_module_check
 * @abstract	Checks if the module have all needed functions.
 * @discussion	This function checks if the module have all needed functions.
 * @param	module		settings module to check
 * @result	Returns <i>TRUE</i> if the settings module is good and implements 
 *		all needed functions.
 *		Returns <i>FALSE</i> if the settings module doesn't implement 
 *		all needed functions or when an error occured
 */
gboolean gw_settings_module_check ( GWSettingsModule *module);


/*!
 * @function	gw_settings_module_free
 * @abstract	Frees the GWSettingsModule structure.
 * @discussion	This function frees the GWSettingsModule structure.
 * @param	module		settings module to free
 * @return	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_module_free ( GWSettingsModule *module);


#endif

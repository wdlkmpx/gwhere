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
 * @header	gwsettingsexplorer.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to configure some settings about the explorer.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2003/02/06
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @ref		gwsettingsexplorer.c
 * @ref		gwsettingsinterface.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_SETTINGS_EXPLORER_H
#define GW_GUI_GW_SETTINGS_EXPLORER_H


#include "gwsettingsinterface.h"


/*!
 * @typedef	gw_settings_explorer_field_s
 *		Settings Explorer Field structure.
 * @abstract	This structure describe all properties of a field in the explorer
 * @field	name		name of the field
 * @field	position	position of the field
 * @field	position_v	variable name to store position of the field
 * @field	visible		is the field must be showed
 * @field	visible_v	variable name to store show mode of the field
 */
typedef struct gw_settings_explorer_field_s {
	gchar *name;
	gint position;
	gchar *position_v;
	gboolean visible;
	gchar *visible_v;
} GWSettingsExplorerField;


/*!
 * @function	gw_plugin_settings_explorer_init
 * @abstract	Initializes the explorer plugin.
 * @discussion	This function initializes the explorer plugin.
 * @param	module		module to store the plugin
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_plugin_settings_explorer_init ( GWSettingsModule **module);


/*!
 * @function	gw_settings_explorer_field_new
 * @abstract	Creates a new GWSettingsExplorerField.
 * @discussion	This function creates a new GWSettingsExplorerField
 * @result	a new settings explorer field.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GWSettingsExplorerField * gw_settings_explorer_field_new ( void);


/*!
 * @function	gw_settings_explorer_field_find_by_name
 * @abstract	Searches in a table of settings explorer field one field.
 * @discussion	This function searches in a table of settings explorer field one field.
 * @param	p	table in which search
 * @param	name	name of field to search
 * @result	the searched settings explorer field.<br>
 *		Returns <i>NULL</i> if it doesn't exist or when an error occured.<br>
 */
GWSettingsExplorerField * gw_settings_explorer_field_find_by_name ( GWSettingsExplorerField **p, const gchar *name);


/*!
 * @function	gw_settings_explorer_field_free
 * @abstract	Frees a settings explorer field.
 * @discussion	This function frees a settings explorer field.
 * @param	p	settings explorer field to free
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_explorer_field_free ( GWSettingsExplorerField *p);


/*!
 * @function	gw_settings_explorer_field_freev
 * @abstract	Frees a table of settings explorer field.
 * @discussion	This function frees a table of settings explorer field.
 * @param	p	table of settings explorer field to free
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_explorer_field_freev ( GWSettingsExplorerField **p);


#endif

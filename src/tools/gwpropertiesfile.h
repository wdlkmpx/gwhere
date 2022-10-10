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
 * @header	gwpropertiesfile.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *
 *		This component was developed for the GWhere project.<br><br>
 *
 *		The properties file contains a list of key/value pair.<br>
 *		Each line must contains only one pair. The key and the value are separated by the
 *		equal character : "=". Note that all beginning and ending whites spaces are always removed.
 *		If the value is replaced by <i>NULL</i> when it equals the empty string : "".<br>
 * @abstract	This is a tool component for properties files.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2002/05/19
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @ref		gwpropertiesfile.c
 * @author	Author <zero@gwhere.org>
 * @author	Luis PARRAVICINI
  */


#ifndef GW_TOOLS_PROPERTIES_FILE_H
#define GW_TOOLS_PROPERTIES_FILE_H


#include "data/gwdata.h"


/*!
 * @function	gw_properties_file_read_variable_value
 * @abstract	Reads the variable value in the properties file.
 * @discussion	This function reads the variable value in the properties file.<br>
 * @param	name		file name
 * @param	var		variable name
 * @param	value		value (note that value must be freed with g_free)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_properties_file_read_variable_value ( const gchar *name, const gchar *var, gchar **value);


/*!
 * @function	gw_properties_file_load_all_settings
 * @abstract	Reads the variable value in the properties file and allocates a new GWSettings.
 * @discussion	This function reads the variable value in the properties file and allocates a new GWSettings.<br>
 * @param	name		file name
 * @param	settings	a pointere (note that settings must be freed with gw_settings_free)
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_properties_file_load_all_settings ( const gchar *name, GWSettings **settings);


/*!
 * @function	gw_properties_file_save_all_settings
 * @abstract	Saves all variable of the GWSettings in the properties file and frees it.
 * @discussion	This function saves all variable of the GWSettings in the properties file and frees it.
 *		<b>Warning</b> : the mode parameter is not yet implemented. This function erase all
 *		existing parameters (and comments).<br>
 *		Not free the GWSettings at time.<br>
 * @param	name		file name
 * @param	settings	a pointer (note will be freed)
 * @param	mode		save mode <i>"u"</i> : update, <i>"e"</i> : ecrase
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_properties_file_save_all_settings ( const gchar *name, GWSettings **settings, const gchar *mode);


#endif

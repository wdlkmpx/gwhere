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
 * @header	gwsettings.h
 * @discussion	GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is the scan disk information data structure
 * @version	1.0 2002/01/17
 * @author	Author <zero@gwhere.org>
 * @see		glib.h
 * @see		gwsupport.h
 * @ref		gwsettings.c
 * @link		GWhere Web Site <http://www.gwhere.org>
 * @link		GTK Web Site <http://www.gtk.org>
 * @author	S&eacute;bastien LECACHEUR <zero@gwhere.org>
 */


#ifndef GW_DATA_SETTINGS_H
#define GW_DATA_SETTINGS_H


/*!
 * @struct	GWSettings
 * @abstract	Settings data structure
 * @discussion	GWSettings is an opaque data structure containing list of settings for the applications.
 */
typedef struct settings GWSettings;


/*!
 * @function	gw_settings_new
 * @abstract	Creates a new settings list.
 * @discussion	This function creates a new settings list. It's an allocation function.
 * @result	a pointer to the settings structure.<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
GWSettings * gw_settings_new ( void);


/*!
 * @function	gw_settings_display
 * @abstract	Displays a settings list.
 * @discussion	This function diplays a settings list.
 * @result	a error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_display ( GWSettings *p);


/*!
 * @function	gw_settings_add_pair
 * @abstract	Adds a key/value pair.
 * @discussion	This function adds a key/value pair.<br>
 * @param	p	settings where add
 * @param	key	the key to add
 * @param	value	the value to add
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_add_pair ( GWSettings *p, gchar *key, gchar *value);

/*!
 * @function	gw_settings_get_value
 * @abstract	Gets the value of a pair.
 * @discussion	This function gets the value of the pair designed by a key.<br>
 * @param	p	settings to get value
 * @param	key	the key
 * @result	the value<br>
 *		Returns <i>NULL</i> when an error occured.<br>
 */
gchar * gw_settings_get_value ( GWSettings *p, gchar *key);


/*!
 * @function	gw_settings_free
 * @abstract	Frees datas structure.
 * @discussion	This function frees the settings data structure.<br>
 *		Frees all variables in the list.
 * @param	p	the settings to free
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_free ( GWSettings *p);


/*!
 * @function	gw_settings_pair_display
 * @abstract	Displays a key/value pair.
 * @discussion	This function diplays a key/value pair.<br>
 * @param	key	the key to display
 * @param	value	the value to display
 * @param	data	user data (not used at time).
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_pair_display ( gchar * key, gchar *value, gpointer data);


/*!
 * @function	gw_settings_pair_free
 * @abstract	Frees a key/value pair.
 * @discussion	This function frees a key/value pair.<br>
 * @param	key	the key to free
 * @param	value	the value to free
 * @param	data	user data (not used at time).
 * @result	an error code.<br>
 *		Returns <i>TRUE</i> when it's done.<br>
 *		Returns <i>FALSE</i> when an error occured.<br>
 */
gboolean gw_settings_pair_free ( gchar * key, gchar *value, gpointer data);


/*!
 * @function	gw_settings_to_line
 * @abstract	Stores in a string the pair key/value.
 * @discussion	This function stores in a string the pair key/value.<br>
 * @param	key	the key to free
 * @param	value	the value to free
 * @param	line	a pointer to store the pair (the format is "key=value\n").
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_to_line ( gchar * key, gchar *value, gchar **line);


/*!
 * @function	gw_settings_to_file
 * @abstract	Stores in a string all pairs key/value.
 * @discussion	This function stores in a string all pairs key/value.<br>
 * @param	key	the key to free
 * @param	value	the value to free
 * @param	file	a pointer to store all pairs (the format is "key1=value1\nkey2=value2\nkey3=value3\n").
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_settings_to_file ( GWSettings *p, gchar **file);


#endif

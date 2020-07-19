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
 * @header	gwsettingsmail.h
 *		GWhere<br>
 *		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 *		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a GUI component to configure some settings about mail component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2003/02/06
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @ref		gwsettingsmail.c
 * @ref		gwsettingsinterface.c
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_GUI_GW_SETTINGS_MAIL_H
#define GW_GUI_GW_SETTINGS_MAIL_H


#include "gwsettingsinterface.h"


/*!
 * @function	gw_plugin_settings_mail_init
 * @abstract	Initializes the mail plugin.
 * @discussion	This function initializes the mail plugin.
 * @param	module		module to store the plugin
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.<br>
 */
gint gw_plugin_settings_mail_init ( GWSettingsModule **module);


#endif

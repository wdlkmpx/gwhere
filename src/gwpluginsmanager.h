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
 * @header	gwpluginsmanager.h
 *		GWhere<br />
 *		Copyright (C) 2000  Sébastien LECACHEUR<br /><br />
 *		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br /><br />
 *		This component was developed for the GWhere project.<br /><br />
 * @abstract	This is a component to manage GWhere application.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @author	Grégory BLOQUEL <gregory.bloquel@fnac.net>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwpluginsmanager.c
 * @ref		plugins/gwdescr.h
 * @ref		plugins/gwcatalog.h
 * @author	Author <zero@gwhere.org>
 */


#ifndef GW_PLUGINS_MANAGER_H
#define GW_PLUGINS_MANAGER_H


#include <glib.h>
#include "plugins/gwdescr.h"
#include "plugins/gwcatalog.h"


/*!
 * @typedef     GWPluginsManager
 * @discussion	Common data structure for the plugin manager
 * @field	catalog_plugins		list of all catalog plugins
 * @field	descr_plugins		list of all description plugins
 */
typedef struct gw_plugins_manager {
	GHashTable *catalog_plugins;
	GHashTable *descr_plugins;
	GHashTable *file_descr_funcs;
	GHashTable *files_descr_funcs;
	GHashTable *parent_descr_funcs;
	GWCatalogPlugin *current_ctg_plugin;
	GWCatalogPlugin *selected_import_ctg_pugin;
	GWCatalogPlugin *selected_export_ctg_pugin;
}GWPluginsManager;


/*!
 * @function	gw_pm_init
 * @abstract	Initializes the plugins settings.
 * @discussion	This function initializes the plugins settings.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_pm_init ( );


/*!
 * @function	gw_pm_get_file_descr_func
 * @abstract	Gets the function to use from one file extension.
 * @discussion	This function gets the function to use from one file extension.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_pm_get_file_descr_func ( const gchar *ext, func_get_file_descr_t *f);


/*!
 * @function	gw_pm_get_files_descr_func
 * @abstract	Gets the function to use from one file extension.
 * @discussion	This function gets the function to use from one file extension.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_pm_get_files_descr_func ( const gchar *ext, func_get_files_descr_t *f);


/*!
 * @function	gw_pm_get_parent_descr_func
 * @abstract	Gets the function to use from one file extension.
 * @discussion	This function gets the function to use from one file extension.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_pm_get_parent_descr_func ( const gchar *ext, func_get_parent_descr_t *f);


/*!
 * @function	gw_pm_exit
 * @abstract	Exits the plugins manager and processes to all savings.
 * @discussion	This function exits the plugins manager and processes to all savings.
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.<br>
 *		Returns <i>-1</i> when an error occured.
 */
gint gw_pm_exit ( );


GWCatalogPlugin * gw_pm_get_default_catalog_plugin ( );


GWCatalogPlugin * gw_pm_get_catalog_plugin ( gchar* name);


gchar ** gw_pm_get_all_catalog_import_plugin_name ( );


gchar ** gw_pm_get_all_catalog_export_plugin_name ( );


void gw_pm_set_current_catalog_plugin ( GWCatalogPlugin *ctg_plugin);


GWCatalogPlugin * gw_pm_get_current_catalog_plugin ( );


void gw_pm_set_selected_import_catalog_plugin ( GWCatalogPlugin *ctg_plugin);


GWCatalogPlugin * gw_pm_get_selected_import_catalog_plugin ( );


void gw_pm_set_selected_export_catalog_plugin ( GWCatalogPlugin *ctg_plugin);


GWCatalogPlugin * gw_pm_get_selected_export_catalog_plugin ( );


#endif

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


#include "gwsupport.h"
#include "gwplugininfo.h"


struct gw_plugin_info_s {
	gchar *name;
	gchar *version;
	gchar *author;
	gchar *description;
	gchar *help;
}_GWPluginInfo;


GWPluginInfo * gw_plugin_info_new ( void) {
	GWPluginInfo *plugin_info = NULL;


	if ( (plugin_info = (GWPluginInfo*)g_malloc0 ( sizeof ( GWPluginInfo))) != NULL ) {
		plugin_info->name = NULL;
		plugin_info->version = NULL;
		plugin_info->author = NULL;
		plugin_info->description = NULL;
		plugin_info->help = NULL;
	}

	return plugin_info;
}


gint gw_plugin_info_set_name ( GWPluginInfo *plugin_info, gchar *name) {
	if ( plugin_info != NULL ) {
		if ( plugin_info->name != NULL ) {
			g_free ( plugin_info->name);
		}

		plugin_info->name = name;

		return 0;
	}

	return -1;
}


gint gw_plugin_info_set_version ( GWPluginInfo *plugin_info, gchar *version) {
	if ( plugin_info != NULL ) {
		if ( plugin_info->version != NULL ) {
			g_free ( plugin_info->version);
		}

		plugin_info->version = version;

		return 0;
	}

	return -1;
}


gint gw_plugin_info_set_author ( GWPluginInfo *plugin_info, gchar *author) {
	if ( plugin_info != NULL ) {
		if ( plugin_info->author != NULL ) {
			g_free ( plugin_info->author);
		}

		plugin_info->author = author;

		return 0;
	}

	return -1;
}


gint gw_plugin_info_set_description ( GWPluginInfo *plugin_info, gchar *description) {
	if ( plugin_info != NULL ) {
		if ( plugin_info->description != NULL ) {
			g_free ( plugin_info->description);
		}

		plugin_info->description = description;

		return 0;
	}

	return -1;
}


gint gw_plugin_info_set_help ( GWPluginInfo *plugin_info, gchar *help) {
	if ( plugin_info != NULL ) {
		if ( plugin_info->help != NULL ) {
			g_free ( plugin_info->help);
		}

		plugin_info->help = help;

		return 0;
	}

	return -1;
}


gchar * gw_plugin_info_get_name ( GWPluginInfo *plugin_info) {
	if ( plugin_info != NULL ) {
		return plugin_info->name;
	}

	return NULL;
}


gchar * gw_plugin_info_get_version ( GWPluginInfo *plugin_info) {
	if ( plugin_info != NULL ) {
		return plugin_info->version;
	}

	return NULL;
}


gchar * gw_plugin_info_get_author ( GWPluginInfo *plugin_info) {
	if ( plugin_info != NULL ) {
		return plugin_info->author;
	}

	return NULL;
}


gchar * gw_plugin_info_get_description ( GWPluginInfo *plugin_info) {
	if ( plugin_info != NULL ) {
		return plugin_info->description;
	}

	return NULL;
}


gchar * gw_plugin_info_get_help ( GWPluginInfo *plugin_info) {
	if ( plugin_info != NULL ) {
		return plugin_info->help;
	}

	return NULL;
}


gint gw_plugin_info_free ( GWPluginInfo *plugin_info) {
	if ( plugin_info != NULL ) {
		gw_plugin_info_set_name ( plugin_info, NULL);
		gw_plugin_info_set_version ( plugin_info, NULL);
		gw_plugin_info_set_author ( plugin_info, NULL);
		gw_plugin_info_set_description ( plugin_info, NULL);
		gw_plugin_info_set_help ( plugin_info, NULL);

		g_free ( plugin_info);

		return 0;
	}

	return -1;
}

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


#include "../gwsupport.h"
#include "gwsettingsinterface.h"


GWSettingsModule * gw_settings_module_new ( )
{
	GWSettingsModule *module = NULL;

	if ( (module = (GWSettingsModule*)g_malloc ( sizeof ( GWSettingsModule))) != NULL )
	{
		module->name = NULL;
		module->page = NULL;
		module->pane = NULL;
		module->settings_window = NULL;
		module->child = NULL;
		module->create = NULL;
		module->load = NULL;
		module->on_change = NULL;
		module->apply = NULL;
	}

	return module;
}


gboolean gw_settings_module_check ( GWSettingsModule *module)
{
	gboolean result = FALSE;


	if ( module != NULL )
	{
		if ( (module->create != NULL) && (module->load != NULL) && (module->on_change != NULL) && (module->apply != NULL))
		{
			result = TRUE;
		}
	}

	return result;
}


gint gw_settings_module_free ( GWSettingsModule *module)
{
	gint result = -1;
	gint i = 0;

	if ( module != NULL )
	{
		if ( module->name != NULL )
		{
			g_free ( module->name);
		}

		if ( module->child != NULL )
		{
			for ( i = 0; module->child[i] != NULL; i++)
			{
				gw_settings_module_free ( module->child[i]);
				module->child[i] = NULL;
			}

			g_free ( module->child);
		}

		g_free ( module);
	}

	return result;
}

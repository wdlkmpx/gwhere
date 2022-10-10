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


#include "../gwsupport.h"
#include "gwsettings.h"

#include <glib.h>


struct settings
{
	GHashTable *list;		/* List of variables					*/
};


GWSettings * gw_settings_new ( void)
{
	GWSettings *p = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( (p = (GWSettings*)g_malloc0 ( sizeof ( GWSettings))) != NULL )
	{
		p->list = g_hash_table_new ( g_str_hash, g_str_equal);
	}

	return p;
}


gint gw_settings_display ( GWSettings *p)
{
	gint result = -1;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->list != NULL )
		{
			g_hash_table_foreach ( p->list, (GHFunc)gw_settings_pair_display, NULL);

			result = 0;
		}
	}

	return result;
}


gint gw_settings_add_pair ( GWSettings *p, gchar *key, gchar *value)
{
	gint result = -1;
	gboolean exist = FALSE;
	gpointer old_key = NULL;
	gpointer old_value = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( key != NULL )
		{
			if ( (exist = g_hash_table_lookup_extended ( p->list, key, &old_key, &old_value)) == TRUE )
			{
				g_hash_table_remove ( p->list, old_key);
				gw_settings_pair_free ( old_key, old_value, NULL);
			}

			g_hash_table_insert ( p->list, key, value);

			result = 0;
		}
	}

	return result;
}


gchar * gw_settings_get_value ( GWSettings *p, gchar *key)
{
	gchar *result = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( key != NULL )
		{
			result = g_hash_table_lookup ( p->list, key);
		}
	}

	return result;
}


gint gw_settings_free ( GWSettings *p)
{
	gint result = -1;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( p != NULL )
	{
		if ( p->list != NULL )
		{
			/* Must free each key/value pairs. */
			g_hash_table_foreach_remove ( p->list, (GHRFunc)gw_settings_pair_free, NULL);

			g_hash_table_destroy ( p->list);
		}

		g_free ( p);

		result = 0;
	}

	return result;
}


gboolean gw_settings_pair_display ( gchar *key, gchar *value, gpointer data)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	g_print ( "*** GW - %s (%d) :: %s() : key/value => (%s := %s)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, key, value);

	return result;
}

gboolean gw_settings_pair_free ( gchar * key, gchar *value, gpointer data)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( key != NULL )
	{
		g_free ( key);

		result = TRUE;
	}

	if ( value != NULL )
	{
		g_free ( value);
	}

	return result;
}


gint gw_settings_to_line ( gchar * key, gchar *value, gchar **line)
{
	gint result = -1;
	gchar *new_line = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (key != NULL) && (value != NULL) )
	{
		new_line = g_strconcat ( *line, key, "=", value, "\n", NULL);
		g_free ( *line);
		*line = new_line;

		result = 0;
	}

	return result;
}


gint gw_settings_to_file ( GWSettings *p, gchar **file)
{
	gint result = -1;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->list != NULL )
		{
			g_hash_table_foreach ( p->list, (GHFunc)gw_settings_to_line, file);

			result = 0;
		}
	}

	return result;
}

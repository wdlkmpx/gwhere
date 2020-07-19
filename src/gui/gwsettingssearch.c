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


#include <string.h> /* strcmp */
#include "../gwsupport.h"
#include "gwsettingssearch.h"

#include "gwsettingswindowbox.h"
#include "gwsettingsquicksearch.h"

#include "../gwapplicationmanager.h"


/*! @define	GW_PLUGIN_SETTINGS_WINDOW	The parent window */
#define GW_PLUGIN_SETTINGS_WINDOW "gw_plugin_settings_window"
/*! @define	GW_PLUGIN_SETTINGS_SEARCH_SORT_CASE_SENSITIVE_CHK	The check box for case sensitive sort */
#define GW_PLUGIN_SETTINGS_SEARCH_SORT_CASE_SENSITIVE_CHK "gw_plugin_settings_search_sort_case_sensitive_chk"
/*! @define	GW_PLUGIN_SETTINGS_SEARCH_SORT_GROUP_BY_TYPE_CHK	The check box for group by type the result sort */
#define GW_PLUGIN_SETTINGS_SEARCH_SORT_GROUP_BY_TYPE_CHK "gw_plugin_settings_search_sort_group_by_type_chk"
/*! @define	GW_PLUGIN_SETTINGS_SEARCH_AUTORESIZE_COLUMN_CHK	The check box for autoresize column */
#define GW_PLUGIN_SETTINGS_SEARCH_AUTORESIZE_COLUMN_CHK "gw_plugin_settings_search_autoresize_column_chk"
/*! @define	GW_PLUGIN_SETTINGS_SEARCH_KEY_WORDS_MODE_CHK	The check box for the key words search mode column */
#define GW_PLUGIN_SETTINGS_SEARCH_KEY_WORDS_MODE_CHK "gw_plugin_settings_search_key_words_mode_chk"


/* I don't like global variable, I don't know to do. */
GtkWidget *pane_settings_search = NULL;


gint gw_plugin_settings_search_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane);
gint gw_plugin_settings_search_pane_load ( GtkWidget *pane);
gint gw_plugin_settings_search_pane_on_change ( GtkEntry *entry, GtkWidget *pane);
gint gw_plugin_settings_search_pane_apply ( GtkWidget *pane);


gint gw_plugin_settings_search_init ( GWSettingsModule **module)
{
	gint result = -1;

	if ( (*module = gw_settings_module_new ( )) != NULL )
	{
		(*module)->name = g_strdup ( _( "Search"));
		(*module)->create = &gw_plugin_settings_search_pane_create;
		(*module)->load = &gw_plugin_settings_search_pane_load;
		(*module)->on_change = &gw_plugin_settings_search_pane_on_change;
		(*module)->apply = &gw_plugin_settings_search_pane_apply;

		(*module)->child = (GWSettingsModule**)g_malloc ( sizeof ( GWSettingsModule*) * 3);

		if ( (*module)->child != NULL)
		{
			(*module)->child[0] = NULL;
			(*module)->child[1] = NULL;
			(*module)->child[2] = NULL;
			gw_plugin_settings_quick_search_init ( &((*module)->child[0]));
			/*gw_plugin_settings_advanced_search_init ( &((*module)->child[1]));*/
		}

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_search_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane)
{
	gint result = -1;
	GtkWidget *table_pane;
	GtkWidget *chk_sort_group_by;
	GtkWidget *chk_sort_case_sensitive;
	GtkWidget *chk_autoresize;
	GtkWidget *chk_key_words_mode;
	GtkTooltips *tooltips;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	tooltips = gtk_tooltips_new ( );

	if ( settings != NULL && parent != NULL )
	{
		table_pane = gtk_table_new ( 5, 2, FALSE);
		gtk_widget_ref ( GTK_WIDGET ( settings));
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_WINDOW, settings, (GtkDestroyNotify) gtk_widget_unref);
		gtk_container_set_border_width ( GTK_CONTAINER ( table_pane), 5);
		gtk_table_set_row_spacings ( GTK_TABLE (table_pane), 5);
		gtk_table_set_col_spacings ( GTK_TABLE (table_pane), 5);

		/* Adds the case sensitive sort option. */
		g_strdup_to_gtk_text ( _( "Case sensitive sort."), text_utf8);
		chk_sort_case_sensitive = gtk_check_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_widget_ref ( chk_sort_case_sensitive);
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_SEARCH_SORT_CASE_SENSITIVE_CHK, chk_sort_case_sensitive, (GtkDestroyNotify) gtk_widget_unref);
		g_strdup_to_gtk_text ( _( "The result sort in search is case sensitive."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, chk_sort_case_sensitive, text_utf8, NULL);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_sort_case_sensitive, 0, 1, 0, 1, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the sort group by type option. */
		g_strdup_to_gtk_text ( _( "Result sort group by type."), text_utf8);
		chk_sort_group_by = gtk_check_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_widget_ref ( chk_sort_group_by);
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_SEARCH_SORT_GROUP_BY_TYPE_CHK, chk_sort_group_by, (GtkDestroyNotify) gtk_widget_unref);
		g_strdup_to_gtk_text ( _( "The result sort in search can be grouped by item type. If this option is checked all item will be grouped by catalogs, disks, folders and files."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, chk_sort_group_by, text_utf8, NULL);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_sort_group_by, 0, 1, 1, 2, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the autoresize column option. */
		g_strdup_to_gtk_text ( _( "Autoresize columns"), text_utf8);
		chk_autoresize = gtk_check_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_widget_ref ( chk_autoresize);
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_SEARCH_AUTORESIZE_COLUMN_CHK, chk_autoresize, (GtkDestroyNotify) gtk_widget_unref);
		g_strdup_to_gtk_text ( _( "Autoresize all explorer column."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, chk_autoresize, text_utf8, NULL);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_autoresize, 0, 1, 2, 3, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the key words mode option. */
		g_strdup_to_gtk_text ( _( "All key words must match"), text_utf8);
		chk_key_words_mode = gtk_check_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_widget_ref ( chk_key_words_mode);
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_SEARCH_KEY_WORDS_MODE_CHK, chk_key_words_mode, (GtkDestroyNotify) gtk_widget_unref);
		g_strdup_to_gtk_text ( _( "Choose if all key words or only one of all key words must match with item in order to be in the search result."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, chk_key_words_mode, text_utf8, NULL);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_key_words_mode, 0, 1, 3, 4, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		*pane = table_pane;
		pane_settings_search = *pane;

		gw_plugin_settings_search_pane_load ( table_pane);

		/* Connects signals after loading. */
		gtk_signal_connect ( GTK_OBJECT ( chk_sort_case_sensitive), "clicked", (GtkSignalFunc)gw_plugin_settings_search_pane_on_change, table_pane);
		gtk_signal_connect ( GTK_OBJECT ( chk_sort_group_by), "clicked", (GtkSignalFunc)gw_plugin_settings_search_pane_on_change, table_pane);
		gtk_signal_connect ( GTK_OBJECT ( chk_autoresize), "clicked", (GtkSignalFunc)gw_plugin_settings_search_pane_on_change, table_pane);
		gtk_signal_connect ( GTK_OBJECT ( chk_key_words_mode), "clicked", (GtkSignalFunc)gw_plugin_settings_search_pane_on_change, table_pane);

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_search_pane_load ( GtkWidget *pane)
{
	gint result = -1;
	GtkToggleButton *chk_bt = NULL;
	gfloat value = -1;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : loading...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		/* Checks case sensitive sort option. */
		if ( (chk_bt = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_SORT_CASE_SENSITIVE_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the case sensitive sort option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE)) == -1 )
			{
				value = GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE_DEFAULT;
			}

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : case sensitive sort option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
#endif

			gtk_toggle_button_set_active ( chk_bt, (gboolean)value);
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		chk_bt = NULL;

		/* Checks sort group by option. */
		if ( (chk_bt = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_SORT_GROUP_BY_TYPE_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the sort group by option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_SEARCH_SORT_BY_TYPE)) == -1 )
			{
				value = GW_VALUE_APP_SEARCH_SORT_BY_TYPE_DEFAULT;
			}

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : sort group by option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
#endif

			gtk_toggle_button_set_active ( chk_bt, (gboolean)value);
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		chk_bt = NULL;

		/* Checks autoresize option. */
		if ( (chk_bt = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_AUTORESIZE_COLUMN_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the autoresize option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE)) == -1 )
			{
				value = GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE_DEFAULT;
			}

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : autoresize option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
#endif

			gtk_toggle_button_set_active ( chk_bt, (gboolean)value);
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		chk_bt = NULL;

		/* Checks key words mode option. */
		if ( (chk_bt = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_KEY_WORDS_MODE_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the key words mode option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE)) == -1 )
			{
				value = GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE_DEFAULT;
			}

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : key words mode option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
#endif

			gtk_toggle_button_set_active ( chk_bt, (gboolean)value);
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		chk_bt = NULL;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_search_pane_on_change ( GtkEntry *entry, GtkWidget *pane)
{
	gint result = -1;
	GtkWindow *settings = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		if ( (settings = GTK_WINDOW ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, TRUE);

			result = 0;
		}
	}

	return result;
}


gint gw_plugin_settings_search_pane_apply ( GtkWidget *pane)
{
	gint result = -1;
	GtkToggleButton *chk = NULL;
	gchar *value = NULL;
	gboolean bool_value = 0;
	GtkWindow *settings = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		if ( (chk = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_SORT_CASE_SENSITIVE_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE, g_strdup_printf ( "%d", (gint)bool_value));
		}

		value = NULL;

		if ( (chk = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_SORT_GROUP_BY_TYPE_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_SEARCH_SORT_BY_TYPE, g_strdup_printf ( "%d", (gint)bool_value));
		}

		value = NULL;

		if ( (chk = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_AUTORESIZE_COLUMN_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_AUTORESIZE, g_strdup_printf ( "%d", (gint)bool_value));
		}

		value = NULL;

		if ( (chk = GTK_TOGGLE_BUTTON ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SEARCH_KEY_WORDS_MODE_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE, g_strdup_printf ( "%d", (gint)bool_value));
		}

		value = NULL;

		if ( (settings = GTK_WINDOW ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, FALSE);
		}

		result = 0;
	}

	return result;
}


GWSettingsSearchField * gw_settings_search_field_new ( void)
{
	GWSettingsSearchField *p = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (p = (GWSettingsSearchField*)g_malloc ( sizeof ( GWSettingsSearchField))) != NULL )
	{
		p->name = NULL;
		p->position = -1;
		p->position_v = NULL;
		p->visible = FALSE;
		p->visible_v = NULL;
	}

	return p;
}


GWSettingsSearchField * gw_settings_search_field_find_by_name ( GWSettingsSearchField **p, const gchar *name)
{
	GWSettingsSearchField *field = NULL;
	gint i = 0;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (p != NULL) && (name != NULL) )
	{
		while ( p[i] != NULL )
		{
			if ( (p[i]->name != NULL) && (strcmp ( name, p[i]->name) == 0) )
			{
				field = p[i];
			}

			i++;
		}
	}

	return field;
}


gint gw_settings_search_field_free ( GWSettingsSearchField * p)
{
	gint result = -1;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->name != NULL )
		{
			g_free ( p->name);
			p->name = NULL;
		}

		if ( p->position_v != NULL )
		{
			g_free ( p->position_v);
			p->position_v = NULL;
		}

		if ( p->visible_v != NULL )
		{
			g_free ( p->visible_v);
			p->visible_v = NULL;
		}

		g_free ( p);

		result = 0;
	}

	return result;
}


gint gw_settings_search_field_freev ( GWSettingsSearchField **p)
{
	gint result = -1;
	gint i = 0;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		for ( i = 0; p[i] != NULL; i++)
		{
			gw_settings_search_field_free ( p[i]);
			p[i] = NULL;
		}

		g_free ( p);
		result = 0;
	}

	return result;
}

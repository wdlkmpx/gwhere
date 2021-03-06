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
#include "gwsettingsexplorer.h"

#include "gwsettingswindowbox.h"
#include "gwsettingsexplorerdisk.h"
#include "gwsettingsexplorerfile.h"

#include "../gwapplicationmanager.h"


/*! @define	GW_PLUGIN_SETTINGS_WINDOW	The parent window */
#define GW_PLUGIN_SETTINGS_WINDOW "gw_plugin_settings_window"
/*! @define	GW_PLUGIN_SETTINGS_EXPLORER_SORT_CASE_SENSITIVE_CHK	The check box for case sensitive sort */
#define GW_PLUGIN_SETTINGS_EXPLORER_SORT_CASE_SENSITIVE_CHK "gw_plugin_settings_explorer_sort_case_sensitive_chk"
/*! @define	GW_PLUGIN_SETTINGS_EXPLORER_SORT_GROUP_BY_FOLDER_CHK	The check box for group by type the result sort */
#define GW_PLUGIN_SETTINGS_EXPLORER_SORT_GROUP_BY_FOLDER_CHK "gw_plugin_settings_explorer_sort_group_by_folder_chk"
/*! @define	GW_PLUGIN_SETTINGS_EXPLORER_AUTORESIZE_COLUMN_CHK	The check box for autoresize column */
#define GW_PLUGIN_SETTINGS_EXPLORER_AUTORESIZE_COLUMN_CHK "gw_plugin_settings_explorer_autoresize_column_chk"


/* I don't like global variable, I don't know to do. */
GtkWidget *pane_settings_explorer = NULL;


gint gw_plugin_settings_explorer_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane);
gint gw_plugin_settings_explorer_pane_load ( GtkWidget *pane);
gint gw_plugin_settings_explorer_pane_on_change ( GtkEntry *entry, GtkWidget *pane);
gint gw_plugin_settings_explorer_pane_apply ( GtkWidget *pane);


gint gw_plugin_settings_explorer_init ( GWSettingsModule **module)
{
	gint result = -1;

	if ( (*module = gw_settings_module_new ( )) != NULL )
	{
		(*module)->name = g_strdup ( _( "Explorer"));
		(*module)->create = &gw_plugin_settings_explorer_pane_create;
		(*module)->load = &gw_plugin_settings_explorer_pane_load;
		(*module)->on_change = &gw_plugin_settings_explorer_pane_on_change;
		(*module)->apply = &gw_plugin_settings_explorer_pane_apply;

		(*module)->child = (GWSettingsModule**)g_malloc ( sizeof ( GWSettingsModule*) * 3);

		if ( (*module)->child != NULL)
		{
			(*module)->child[0] = NULL;
			(*module)->child[1] = NULL;
			(*module)->child[2] = NULL;
			gw_plugin_settings_explorer_disk_init ( &((*module)->child[0]));
			gw_plugin_settings_explorer_file_init ( &((*module)->child[1]));
		}

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_explorer_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane)
{
	gint result = -1;
	GtkWidget *table_pane;
	GtkWidget *chk_sort_group_by;
	GtkWidget *chk_sort_case_sensitive;
	GtkWidget *chk_autoresize;

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif


	if ( settings != NULL && parent != NULL )
	{
		table_pane = gtk_table_new ( 5, 2, FALSE);
		g_object_ref ( GTK_WIDGET ( settings));
		g_object_set_data_full (G_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_WINDOW, settings, (GDestroyNotify) g_object_unref);
		gtk_container_set_border_width ( GTK_CONTAINER ( table_pane), 5);
		gtk_table_set_row_spacings ( GTK_TABLE (table_pane), 5);
		gtk_table_set_col_spacings ( GTK_TABLE (table_pane), 5);

		/* Adds the case sensitive sort option. */
		chk_sort_case_sensitive = gtk_check_button_new_with_label (_( "Case sensitive sort."));
		g_object_ref ( chk_sort_case_sensitive);
		g_object_set_data_full (G_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_EXPLORER_SORT_CASE_SENSITIVE_CHK, chk_sort_case_sensitive, (GDestroyNotify) g_object_unref);
		gtk_widget_set_tooltip_text (chk_sort_case_sensitive,
		                             _( "The result sort in explorer is case sensitive."));
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_sort_case_sensitive, 0, 1, 0, 1, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the sort group by type option. */
		chk_sort_group_by = gtk_check_button_new_with_label (_( "Result sort group by folder/file."));
		g_object_ref ( chk_sort_group_by);
		g_object_set_data_full (G_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_EXPLORER_SORT_GROUP_BY_FOLDER_CHK, chk_sort_group_by, (GDestroyNotify) g_object_unref);
		gtk_widget_set_tooltip_text (chk_sort_group_by,
		                             _( "The result sort in explorer can be grouped by item type. If this option is checked all item will be grouped by folders or files."));
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_sort_group_by, 0, 1, 1, 2, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the autoload catalog option. */
		chk_autoresize = gtk_check_button_new_with_label (_( "Autoresize columns"));
		g_object_ref ( chk_autoresize);
		g_object_set_data_full (G_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_EXPLORER_AUTORESIZE_COLUMN_CHK, chk_autoresize, (GDestroyNotify) g_object_unref);
		gtk_widget_set_tooltip_text (chk_autoresize,
		                             _( "Autoresize all explorer column."));
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_autoresize, 0, 1, 2, 3, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		*pane = table_pane;
		pane_settings_explorer = *pane;

		gw_plugin_settings_explorer_pane_load ( table_pane);

		/* Connects signals after loading. */
		g_signal_connect (G_OBJECT ( chk_sort_case_sensitive), "clicked", (GCallback)gw_plugin_settings_explorer_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( chk_sort_group_by), "clicked", (GCallback)gw_plugin_settings_explorer_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( chk_autoresize), "clicked", (GCallback)gw_plugin_settings_explorer_pane_on_change, table_pane);

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_explorer_pane_load ( GtkWidget *pane)
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
		if ( (chk_bt = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_SORT_CASE_SENSITIVE_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the case sensitive sort option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE)) == -1 )
			{
				value = GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE_DEFAULT;
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
		if ( (chk_bt = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_SORT_GROUP_BY_FOLDER_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the sort group by option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER)) == -1 )
			{
				value = GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER_DEFAULT;
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
		if ( (chk_bt = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_AUTORESIZE_COLUMN_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the autoresize option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE)) == -1 )
			{
				value = GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE_DEFAULT;
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

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_explorer_pane_on_change ( GtkEntry *entry, GtkWidget *pane)
{
	gint result = -1;
	GtkWindow *settings = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		if ( (settings = GTK_WINDOW ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, TRUE);

			result = 0;
		}
	}

	return result;
}


gint gw_plugin_settings_explorer_pane_apply ( GtkWidget *pane)
{
	gint result = -1;
	GtkToggleButton *chk = NULL;
	gboolean bool_value = 0;
	GtkWindow *settings = NULL;

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_SORT_CASE_SENSITIVE_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_EXPLORER_SORT_CASE_SENSITIVE, g_strdup_printf ( "%d", (gint)bool_value));
		}

		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_SORT_GROUP_BY_FOLDER_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_EXPLORER_SORT_BY_FOLDER, g_strdup_printf ( "%d", (gint)bool_value));
		}

		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_AUTORESIZE_COLUMN_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE, g_strdup_printf ( "%d", (gint)bool_value));
		}

		if ( (settings = GTK_WINDOW ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, FALSE);
		}

		result = 0;
	}

	return result;
}


GWSettingsExplorerField * gw_settings_explorer_field_new ( void)
{
	GWSettingsExplorerField *p = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (p = (GWSettingsExplorerField*)g_malloc ( sizeof ( GWSettingsExplorerField))) != NULL )
	{
		p->name = NULL;
		p->position = -1;
		p->position_v = NULL;
		p->visible = FALSE;
		p->visible_v = NULL;
	}

	return p;
}


GWSettingsExplorerField * gw_settings_explorer_field_find_by_name ( GWSettingsExplorerField **p, const gchar *name)
{
	GWSettingsExplorerField *field = NULL;
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


gint gw_settings_explorer_field_free ( GWSettingsExplorerField * p)
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


gint gw_settings_explorer_field_freev ( GWSettingsExplorerField **p)
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
			gw_settings_explorer_field_free ( p[i]);
			p[i] = NULL;
		}

		g_free ( p);
		result = 0;
	}

	return result;
}

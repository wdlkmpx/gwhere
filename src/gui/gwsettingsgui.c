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
#include "gwsettingsgui.h"

#include "gwsettingswindowbox.h"
#include "gwfileselectionbox.h"

#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"


/*! @define	GW_PLUGIN_SETTINGS_WINDOW	The parent window */
#define GW_PLUGIN_SETTINGS_WINDOW "gw_plugin_settings_window"
/*! @define	GW_PLUGIN_SETTINGS_GUI_AUTOSAVE_CHK	The check box for autosave GUI properties */
#define GW_PLUGIN_SETTINGS_GUI_AUTOSAVE_CHK "gw_plugin_settings_gui_save_properties_chk"
/*! @define	GW_PLUGIN_SETTINGS_GUI_BEEP_CHK	The check box for allowing beep */
#define GW_PLUGIN_SETTINGS_GUI_BEEP_CHK "gw_plugin_settings_gui_beep_chk"


/* I don't like global variable, I don't know to do. */
GtkWidget *pane_settings_gui = NULL;


gint gw_plugin_settings_gui_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane);
gint gw_plugin_settings_gui_pane_load ( GtkWidget *pane);
gint gw_plugin_settings_gui_pane_on_change ( GtkEntry *entry, GtkWidget *pane);
gint gw_plugin_settings_gui_pane_apply ( GtkWidget *pane);


gint gw_plugin_settings_gui_init ( GWSettingsModule **module)
{
	gint result = -1;

	if ( (*module = gw_settings_module_new ( )) != NULL )
	{
		(*module)->name = g_strdup ( _( "GUI"));
		(*module)->create = &gw_plugin_settings_gui_pane_create;
		(*module)->load = &gw_plugin_settings_gui_pane_load;
		(*module)->on_change = &gw_plugin_settings_gui_pane_on_change;
		(*module)->apply = &gw_plugin_settings_gui_pane_apply;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_gui_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane)
{
	gint result = -1;
	GtkWidget *table_pane;
	GtkWidget *chk_autosave;
	GtkWidget *chk_beep;
	GtkTooltips *tooltips;

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	tooltips = gtk_tooltips_new ( );

	if ( settings != NULL && parent != NULL )
	{
		table_pane = gtk_table_new ( 5, 2, FALSE);
		g_object_ref ( GTK_WIDGET ( settings));
		g_object_set_data_full (G_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_WINDOW, settings, (GDestroyNotify) g_object_unref);
		gtk_container_set_border_width ( GTK_CONTAINER ( table_pane), 5);
		gtk_table_set_row_spacings ( GTK_TABLE (table_pane), 5);
		gtk_table_set_col_spacings ( GTK_TABLE (table_pane), 5);

		/* Adds the autosave GUI properties option. */
		chk_autosave = gtk_check_button_new_with_label (_( "Save GUI properties on exit"));
		g_object_ref ( chk_autosave);
		g_object_set_data_full (G_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_GUI_AUTOSAVE_CHK, chk_autosave, (GDestroyNotify) g_object_unref);
		gtk_tooltips_set_tip ( tooltips, chk_autosave,
		                      _( "Save GUI properties as window position and size."), NULL);
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_autosave, 0, 1, 0, 1, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the allowing beep option. */
		chk_beep = gtk_check_button_new_with_label (_( "Allow beep"));
		g_object_ref ( chk_beep);
		g_object_set_data_full (G_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_GUI_BEEP_CHK, chk_beep, (GDestroyNotify) g_object_unref);
		gtk_tooltips_set_tip ( tooltips, chk_beep,
		                      _( "Allows to emits a short beep on some event."), NULL);
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_beep, 0, 1, 1, 2, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		*pane = table_pane;
		pane_settings_gui = *pane;

		gw_plugin_settings_gui_pane_load ( table_pane);

		/* Connects signals after loading. */
		g_signal_connect (G_OBJECT ( chk_autosave), "clicked", (GCallback)gw_plugin_settings_gui_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( chk_beep), "clicked", (GCallback)gw_plugin_settings_gui_pane_on_change, table_pane);

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_gui_pane_load ( GtkWidget *pane)
{
	gint result = -1;
	GtkToggleButton *chk = NULL;
	gfloat value = 0;

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : loading...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		/* Checks autosave option. */
		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_GUI_AUTOSAVE_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the autosave GUI option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			value = gw_am_get_settings_tod ( GW_VALUE_APP_GUI_AUTOSAVE);

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : autosave GUI option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
#endif

			gtk_toggle_button_set_active ( chk, (gboolean)value);
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		chk = NULL;
		value = 0;

		/* Checks beep option. */
		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_GUI_BEEP_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the beep option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			if ( (value = gw_am_get_settings_tod ( GW_VALUE_APP_GUI_BEEP)) == -1 )
			{
				value = GW_VALUE_APP_GUI_BEEP_DEFAULT;
			}

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : beep option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
#endif

			gtk_toggle_button_set_active ( chk, (gboolean)value);
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		chk = NULL;
		value = 0;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_gui_pane_on_change ( GtkEntry *entry, GtkWidget *pane)
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


gint gw_plugin_settings_gui_pane_apply ( GtkWidget *pane)
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
		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_GUI_AUTOSAVE_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_GUI_AUTOSAVE, g_strdup_printf ( "%d", (gint)bool_value));
		}

		value = NULL;

		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_GUI_BEEP_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_GUI_BEEP, g_strdup_printf ( "%d", (gint)bool_value));
		}

		value = NULL;

		if ( (settings = GTK_WINDOW ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, FALSE);
		}

		result = 0;
	}

	return result;
}

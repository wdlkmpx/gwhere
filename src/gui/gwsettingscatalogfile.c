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


#include <string.h> /* stcmp */
#include "../gwsupport.h"
#include "gwsettingscatalogfile.h"

#include "gwsettingswindowbox.h"
#include "gwmisc.h"

#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"


/*! @define	GW_PLUGIN_SETTINGS_WINDOW	The parent window */
#define GW_PLUGIN_SETTINGS_WINDOW "gw_plugin_settings_window"
/*! @define	GW_PLUGIN_SETTINGS_CATALOG_COMPRESSION_LEVEL_ENTRY	The entry for compression level */
#define GW_PLUGIN_SETTINGS_CATALOG_COMPRESSION_LEVEL_ENTRY "gw_plugin_settings_catalog_compression_level_entry"
/*! @define	GW_PLUGIN_SETTINGS_CATALOG_HISTORY_SIZE_ENTRY	The entry for history size */
#define GW_PLUGIN_SETTINGS_CATALOG_HISTORY_SIZE_ENTRY "gw_plugin_settings_catalog_history_size_entry"
/*! @define	GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_CHK	The check box for autoload catalog */
#define GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_CHK "gw_plugin_settings_catalog_autoload_chk"
/*! @define	GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_LAST_RADIO	The radio button for autoload last opened catalog */
#define GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_LAST_RADIO "gw_plugin_settings_catalog_autoload_last_radio"
/*! @define	GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECTED_RADIO	The radio button for autoload selected catalog */
#define GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECTED_RADIO "gw_plugin_settings_catalog_autoload_selected_radio"
/*! @define	GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_ENTRY	The entry for selected catalog */
#define GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_ENTRY "gw_plugin_settings_catalog_autoload_entry"
/*! @define	GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECT_BTN	The button for select a catalog to autoload */
#define GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECT_BTN "gw_plugin_settings_catalog_autoload_select_btn"


/* I don't like global variable, I don't know to do. */
static GtkWidget *pane_settings_catalog_file = NULL;


gint gw_plugin_settings_catalog_file_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane);
gint gw_plugin_settings_catalog_file_pane_load ( GtkWidget *pane);
gint gw_plugin_settings_catalog_file_pane_on_change ( GtkEntry *entry, GtkWidget *pane);
gint gw_plugin_settings_catalog_file_pane_apply ( GtkWidget *pane);
gint gw_plugin_settings_catalog_file_btn_clear_history_click ( GtkButton *btn, GtkWidget *pane);
gint gw_plugin_settings_catalog_file_btn_autoload_catalog_click ( GtkButton *btn, GtkWidget *pane);
void gw_plugin_settings_catalog_file_btn_select_catalog_click (GtkButton *btn, GtkWidget *pane);
void gw_plugin_settings_catalog_file_btn_select_catalog_click_ok (GtkWidget *w, char * filename);


gint gw_plugin_settings_catalog_file_init ( GWSettingsModule **module)
{
	gint result = -1;

	if ( (*module = gw_settings_module_new ( )) != NULL )
	{
		(*module)->name = g_strdup ( _( "Catalog file"));
		(*module)->create = &gw_plugin_settings_catalog_file_pane_create;
		(*module)->load = &gw_plugin_settings_catalog_file_pane_load;
		(*module)->on_change = &gw_plugin_settings_catalog_file_pane_on_change;
		(*module)->apply = &gw_plugin_settings_catalog_file_pane_apply;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_catalog_file_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane)
{
	gint result = -1;
	GtkWidget *table_pane;
	GtkWidget *lbl_catalog_level_compression;
	GtkAdjustment *adj_catalog_level_compression;
	GtkWidget *spn_catalog_level_compression;
	GtkWidget *lbl_catalog_history_size;
	GtkAdjustment *adj_catalog_history_size;
	GtkWidget *spn_catalog_history_size;
	GtkWidget *btn_history_clear;
	GtkWidget *chk_autoload;
	GtkWidget *entry_autoload_filepath;
	GtkWidget *btn_autoload;
	gfloat level = GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT;
	gfloat size = GW_VALUE_APP_RECENT_SIZE_DEFAULT;
	GtkWidget *radio_last = NULL;
	GtkWidget *radio_selected = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( settings != NULL && parent != NULL )
	{
		table_pane = gtk_table_new ( 7, 2, TRUE);
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_WINDOW, settings);
		gtk_container_set_border_width ( GTK_CONTAINER ( table_pane), 5);
		gtk_table_set_row_spacings ( GTK_TABLE (table_pane), 5);
		gtk_table_set_col_spacings ( GTK_TABLE (table_pane), 5);

		/* Adds the compression level. */
		lbl_catalog_level_compression = gtk_label_new (_( "Catalog compression level :"));
		gtk_table_attach ( GTK_TABLE ( table_pane), lbl_catalog_level_compression, 0, 1, 0, 1, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lbl_catalog_level_compression), 0, 0.5);

		adj_catalog_level_compression = (GtkAdjustment *) gtk_adjustment_new ( level, GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_MIN, GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_MAX, 1.0, 1.0, 0.0);
		spn_catalog_level_compression = gtk_spin_button_new ( adj_catalog_level_compression, 0, 0);
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_CATALOG_COMPRESSION_LEVEL_ENTRY, spn_catalog_level_compression);
		gtk_spin_button_set_numeric ( GTK_SPIN_BUTTON ( spn_catalog_level_compression), TRUE);
		gtk_spin_button_set_wrap ( GTK_SPIN_BUTTON ( spn_catalog_level_compression), TRUE);
		gtk_widget_set_tooltip_text (spn_catalog_level_compression,
		                             _( "Select the catalog compression level. The default value is 3, it's a good value between high performance and small size."));

		gtk_table_attach ( GTK_TABLE ( table_pane), spn_catalog_level_compression, 1, 2, 0, 1, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);


		/* Adds the history size. */
		lbl_catalog_history_size = gtk_label_new (_( "Recent opened catalogs :"));
		gtk_table_attach ( GTK_TABLE ( table_pane), lbl_catalog_history_size, 0, 1, 1, 2, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lbl_catalog_history_size), 0, 0.5);

		adj_catalog_history_size = (GtkAdjustment *) gtk_adjustment_new ( size, GW_VALUE_APP_RECENT_SIZE_MIN, GW_VALUE_APP_RECENT_SIZE_MAX, 1.0, 1.0, 0.0);
		spn_catalog_history_size = gtk_spin_button_new ( adj_catalog_history_size, 0, 0);
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_CATALOG_HISTORY_SIZE_ENTRY, spn_catalog_history_size);
		gtk_spin_button_set_numeric ( GTK_SPIN_BUTTON ( spn_catalog_history_size), TRUE);
		gtk_spin_button_set_wrap ( GTK_SPIN_BUTTON ( spn_catalog_history_size), TRUE);
		gtk_widget_set_tooltip_text (spn_catalog_history_size,
		                             _( "Select the size of recent opened catalogs history. The default value is 5."));

		gtk_table_attach ( GTK_TABLE ( table_pane), spn_catalog_history_size, 1, 2, 1, 2, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the clear history. */
		btn_history_clear = gtk_button_new_with_label (_( "Clear history"));
		g_signal_connect (G_OBJECT ( btn_history_clear), "clicked", (GCallback)gw_plugin_settings_catalog_file_btn_clear_history_click, table_pane);
		gtk_widget_set_tooltip_text (btn_history_clear,
		                             _( "Click here to clear the recent opened files history."));
		gtk_table_attach ( GTK_TABLE ( table_pane), btn_history_clear, 1, 2, 2, 3, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);

		/* Adds the autload catalog option. */
		chk_autoload = gtk_check_button_new_with_label (_( "Autoload catalog"));
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_CHK, chk_autoload);
		gtk_widget_set_tooltip_text (chk_autoload, _( "Autoloads a default catalog when at starting."));
		gtk_table_attach ( GTK_TABLE ( table_pane), chk_autoload, 0, 1, 3, 4, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		g_signal_connect (G_OBJECT ( chk_autoload), "clicked", (GCallback)gw_plugin_settings_catalog_file_btn_autoload_catalog_click, table_pane);

		/* Create the radio button group for autoload options. */
		radio_last = gtk_radio_button_new_with_label_from_widget ( NULL, _("Load last opened catalog file."));
		gtk_table_attach ( GTK_TABLE ( table_pane), radio_last, 0, 1, 4, 5, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_LAST_RADIO, radio_last);
		gtk_widget_set_sensitive ( GTK_WIDGET ( radio_last), FALSE);
		radio_selected = gtk_radio_button_new_with_label_from_widget ( GTK_RADIO_BUTTON ( radio_last),
		                                                              _("Load selected catalog file."));
		gtk_table_attach ( GTK_TABLE ( table_pane), radio_selected, 0, 1, 5, 6, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECTED_RADIO, radio_selected);
		gtk_widget_set_sensitive ( GTK_WIDGET ( radio_selected), FALSE);

		entry_autoload_filepath = gtk_entry_new ( );
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_ENTRY, entry_autoload_filepath);
		gtk_widget_set_tooltip_text (entry_autoload_filepath,
		                             _( "Enter the full catalog file path to load."));
		gtk_table_attach ( GTK_TABLE ( table_pane), entry_autoload_filepath, 1, 2, 5, 6, (GtkAttachOptions) ( GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_widget_set_sensitive ( GTK_WIDGET ( entry_autoload_filepath), FALSE);

		/* Adds the select catalog file. */
		btn_autoload = gtk_button_new_with_label (_( "Select catalog"));
		g_object_set_data (G_OBJECT(table_pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECT_BTN, btn_autoload);
		g_signal_connect (G_OBJECT ( btn_autoload), "clicked", (GCallback)gw_plugin_settings_catalog_file_btn_select_catalog_click, table_pane);
		gtk_widget_set_tooltip_text (btn_autoload, _( "Click here to browse and select the catalog file."));
		gtk_table_attach ( GTK_TABLE ( table_pane), btn_autoload, 1, 2, 6, 7, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_widget_set_sensitive ( GTK_WIDGET ( btn_autoload), FALSE);

		*pane = table_pane;
		pane_settings_catalog_file = table_pane;

		gw_plugin_settings_catalog_file_pane_load ( table_pane);

		/* Connects signals after loading. */
		g_signal_connect (G_OBJECT ( spn_catalog_level_compression), "changed", (GCallback)gw_plugin_settings_catalog_file_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( spn_catalog_history_size), "changed", (GCallback)gw_plugin_settings_catalog_file_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( chk_autoload), "clicked", (GCallback)gw_plugin_settings_catalog_file_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( radio_last), "clicked", (GCallback)gw_plugin_settings_catalog_file_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( radio_selected), "clicked", (GCallback)gw_plugin_settings_catalog_file_pane_on_change, table_pane);
		g_signal_connect (G_OBJECT ( entry_autoload_filepath), "changed", (GCallback)gw_plugin_settings_catalog_file_pane_on_change, table_pane);

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_catalog_file_pane_load ( GtkWidget *pane)
{
	gint result = -1;
	GtkSpinButton *button = NULL;
	GtkAdjustment *adj_catalog_level_compression = NULL;
	GtkAdjustment *adj_catalog_history_size = NULL;
	GtkToggleButton *chk_autoload = NULL;
	GtkEntry *entry_autoload_filepath = NULL;
	gfloat level = GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL_DEFAULT;
	gfloat size = GW_VALUE_APP_RECENT_SIZE_DEFAULT;
	gfloat autoload = 0;
	gchar *value = NULL;

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : loading...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		if ( (button = GTK_SPIN_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_COMPRESSION_LEVEL_ENTRY))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the compression level...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			level = gw_am_get_settings_tod ( GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL);

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : compression level is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, level);
#endif
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no spin button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		adj_catalog_level_compression = gtk_spin_button_get_adjustment ( button);
		gtk_adjustment_set_value ( adj_catalog_level_compression, level);
		button = NULL;
		value = NULL;


		/* Checks history size. */
		if ( (button = GTK_SPIN_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_HISTORY_SIZE_ENTRY))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the history size...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			size = gw_am_get_settings_tod ( GW_VALUE_APP_RECENT_SIZE);

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : history size is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, size);
#endif
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no spin button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		adj_catalog_history_size = gtk_spin_button_get_adjustment ( button);
		gtk_adjustment_set_value ( adj_catalog_history_size, size);
		button = NULL;
		value = NULL;

		/* Checks autoload option. */
		if ( (chk_autoload = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_CHK))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the autoload option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			autoload = gw_am_get_settings_tod ( GW_VALUE_APP_CATALOG_AUTOLOAD);

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : autoload option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, autoload);
#endif
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		gtk_toggle_button_set_active ( chk_autoload, (gboolean)autoload);
		chk_autoload = NULL;
		value = NULL;

		/* Checks autoload last option. */
		if ( (chk_autoload = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_LAST_RADIO))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the autoload last option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			autoload = gw_am_get_settings_tod ( GW_VALUE_APP_CATALOG_AUTOLOAD_LAST);

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : autoload last option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, autoload);
#endif
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		gtk_toggle_button_set_active ( chk_autoload, (gboolean)autoload);
		chk_autoload = NULL;
		value = NULL;

		/* Checks autoload selected option. */
		if ( (chk_autoload = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECTED_RADIO))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the autoload selected option...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			autoload = gw_am_get_settings_tod ( GW_VALUE_APP_CATALOG_AUTOLOAD_SELECTED);

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : autoload seletec option is %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, autoload);
#endif
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no check button!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		gtk_toggle_button_set_active ( chk_autoload, (gboolean)autoload);
		chk_autoload = NULL;
		value = NULL;

		/* Checks autoload file path. */
		if ( (entry_autoload_filepath = GTK_ENTRY ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_ENTRY))) != NULL)
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : getting the autoload file path...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			value = gw_am_get_settings ( GW_VALUE_APP_CATALOG_AUTOLOAD_FILEPATH);

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			if ( value != NULL ) {
				g_print ( "*** GW - %s (%d) :: %s() : autoload file path is %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
			} else {
				g_print ( "*** GW - %s (%d) :: %s() : autoload file path is NULL\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
			}
#endif
		}
		else
		{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : warning no entry!!\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		if (value) {
			gtk_entry_set_text ( entry_autoload_filepath, value);
		}
		entry_autoload_filepath = NULL;
		value = NULL;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_catalog_file_pane_on_change ( GtkEntry *entry, GtkWidget *pane)
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


gint gw_plugin_settings_catalog_file_pane_apply ( GtkWidget *pane)
{
	gint result = -1;
	GtkEntry *entry = NULL;
	GtkToggleButton *chk = NULL;
	gchar *value = NULL;
	gboolean bool_value = 0;
	GtkWindow *settings = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		if ( (entry = GTK_ENTRY ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_COMPRESSION_LEVEL_ENTRY))) != NULL)
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), value);
			gw_am_set_settings ( GW_VALUE_APP_CATALOG_COMPRESSION_LEVEL, value);
		}

		entry = NULL;
		value = NULL;

		if ( (entry = GTK_ENTRY ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_HISTORY_SIZE_ENTRY))) != NULL)
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), value);
			gw_am_set_settings ( GW_VALUE_APP_RECENT_SIZE, value);
		}

		entry = NULL;
		value = NULL;

		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_CHK))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_CATALOG_AUTOLOAD, g_strdup_printf ( "%d", (gint)bool_value));
		}

		entry = NULL;
		value = NULL;

		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_LAST_RADIO))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_CATALOG_AUTOLOAD_LAST, g_strdup_printf ( "%d", (gint)bool_value));
		}

		entry = NULL;
		value = NULL;

		if ( (chk = GTK_TOGGLE_BUTTON ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECTED_RADIO))) != NULL)
		{
			bool_value = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
			gw_am_set_settings ( GW_VALUE_APP_CATALOG_AUTOLOAD_SELECTED, g_strdup_printf ( "%d", (gint)bool_value));
		}

		entry = NULL;
		value = NULL;

		if ( (entry = GTK_ENTRY ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_ENTRY))) != NULL)
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), value);
			gw_am_set_settings ( GW_VALUE_APP_CATALOG_AUTOLOAD_FILEPATH, value);
		}

		entry = NULL;
		value = NULL;

		if ( (settings = GTK_WINDOW ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, FALSE);
		}

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_catalog_file_btn_clear_history_click ( GtkButton *btn, GtkWidget *pane)
{
	gint result = -1;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_RECENT_FILES, g_strdup ( ""));
		gw_gui_manager_main_interface_update_all ( );
		result = 0;
	}

	return result;
}


gint gw_plugin_settings_catalog_file_btn_autoload_catalog_click ( GtkButton *btn, GtkWidget *pane)
{
	gint result = -1;
	gboolean activation = FALSE;
	GtkWidget *widget = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL && btn != NULL)
	{
		activation = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( btn));

		if ( (widget = GTK_WIDGET ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_LAST_RADIO))) != NULL )
		{
			gtk_widget_set_sensitive ( GTK_WIDGET ( widget), activation);
		}

		if ( (widget = GTK_WIDGET ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECTED_RADIO))) != NULL )
		{
			gtk_widget_set_sensitive ( GTK_WIDGET ( widget), activation);
		}

		if ( (widget = GTK_WIDGET ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_ENTRY))) != NULL )
		{
			gtk_widget_set_sensitive ( GTK_WIDGET ( widget), activation);
		}

		if ( (widget = GTK_WIDGET ( g_object_get_data (G_OBJECT ( pane), GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_SELECT_BTN))) != NULL )
		{
			gtk_widget_set_sensitive ( GTK_WIDGET ( widget), activation);
		}

		result = 0;
	}

	return result;
}


void gw_plugin_settings_catalog_file_btn_select_catalog_click ( GtkButton *btn, GtkWidget *pane)
{
    GtkWindow *mwin = gw_gui_manager_main_interface_get_main_window();
    GtkWindow *settings_dialog;
    settings_dialog = (GtkWindow*) g_object_get_data (G_OBJECT(mwin), "settings_dialog");
    gw_file_chooser_box (_("Select autoloaded catalog"), NULL,
                         settings_dialog,
                         gw_plugin_settings_catalog_file_btn_select_catalog_click_ok,
                         NULL);
}

void gw_plugin_settings_catalog_file_btn_select_catalog_click_ok (GtkWidget *w, char * filename)
{
    GtkEntry *entry_autoload_filepath;
    entry_autoload_filepath = GTK_ENTRY (g_object_get_data (G_OBJECT(pane_settings_catalog_file),
                                                            GW_PLUGIN_SETTINGS_CATALOG_AUTOLOAD_ENTRY));
    gtk_entry_set_text (entry_autoload_filepath, filename);
}

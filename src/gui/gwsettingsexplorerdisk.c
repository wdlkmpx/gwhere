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
#include "gwsettingsexplorerdisk.h"

#include "gwsettingswindowbox.h"
#include "gwsettingsexplorer.h"

#include "../gwapplicationmanager.h"


/*! @define	GW_PLUGIN_SETTINGS_WINDOW	The parent window */
#define GW_PLUGIN_SETTINGS_WINDOW "gw_plugin_settings_window"
/*! @define	GW_PLUGIN_SETTINGS_EXPLORER_DISK_FIELDS_TABLE	The table of fields */
#define GW_PLUGIN_SETTINGS_EXPLORER_DISK_FIELDS_TABLE "gw_plugin_settings_explorer_disk_fields_table"
/*! @define	GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_VISIBLE	The list of visible fields */
#define GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_VISIBLE "gw_plugin_settings_explorer_disk_list_visible"
/*! @define	GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_HIDDEN	The list of hidden fields */
#define GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_HIDDEN "gw_plugin_settings_explorer_disk_list_hidden"


gint gw_plugin_settings_explorer_disk_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane);
gint gw_plugin_settings_explorer_disk_pane_load ( GtkWidget *pane);
gint gw_plugin_settings_explorer_disk_pane_on_change ( GtkEntry *entry, GtkWidget *pane);
gint gw_plugin_settings_explorer_disk_pane_apply ( GtkWidget *pane);
gint gw_plugin_settings_explorer_disk_btn_show_click ( GtkButton *btn, GtkWidget *pane);
gint gw_plugin_settings_explorer_disk_btn_hide_click ( GtkButton *btn, GtkWidget *pane);
gboolean gw_plugin_settings_explorer_disk_destroy ( GtkWidget *pane, gpointer data);


gint gw_plugin_settings_explorer_disk_init ( GWSettingsModule **module)
{
	gint result = -1;

	if ( (*module = gw_settings_module_new ( )) != NULL )
	{
		(*module)->name = g_strdup ( _( "Disks"));
		(*module)->create = &gw_plugin_settings_explorer_disk_pane_create;
		(*module)->load = &gw_plugin_settings_explorer_disk_pane_load;
		(*module)->on_change = &gw_plugin_settings_explorer_disk_pane_on_change;
		(*module)->apply = &gw_plugin_settings_explorer_disk_pane_apply;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_explorer_disk_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane)
{
	gint result = -1;
	GtkWidget *hbox;
	GtkWidget *scr_clist_hidden;
	GtkWidget *clist_hidden;
	GtkWidget *col_title_hidden;
	GtkWidget *vbox_btn;
	GtkWidget *btn_hidden;
	GtkWidget *btn_show;
	GtkWidget *scr_clist_visible;
	GtkWidget *clist_visible;
	GtkWidget *col_title_visible;
	GtkTooltips *tooltips;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( settings != NULL && parent != NULL )
	{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : Creating configuration pane...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		tooltips = gtk_tooltips_new ( );

		hbox = gtk_hbox_new ( FALSE, 0);
		gtk_widget_ref ( GTK_WIDGET ( settings));
		gtk_object_set_data_full ( GTK_OBJECT ( hbox), GW_PLUGIN_SETTINGS_WINDOW, settings, (GtkDestroyNotify) gtk_widget_unref);
		gtk_container_set_border_width ( GTK_CONTAINER ( hbox), 5);
		
		scr_clist_visible = gtk_scrolled_window_new ( NULL, NULL);
		gtk_box_pack_start ( GTK_BOX ( hbox), scr_clist_visible, TRUE, TRUE, 0);

		clist_visible = gtk_clist_new ( 1);
		gtk_widget_ref ( clist_visible);
		gtk_object_set_data_full ( GTK_OBJECT ( hbox), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_VISIBLE, clist_visible, (GtkDestroyNotify) gtk_widget_unref);
		gtk_container_add ( GTK_CONTAINER ( scr_clist_visible), clist_visible);
		gtk_clist_set_column_width ( GTK_CLIST ( clist_visible), 0, 80);
		gtk_clist_optimal_column_width ( GTK_CLIST ( clist_visible), 0);
		gtk_clist_column_titles_show (GTK_CLIST (clist_visible));

		g_strdup_to_gtk_text ( _( "Visible"), text_utf8);
		col_title_visible = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_clist_set_column_widget ( GTK_CLIST ( clist_visible), 0, col_title_visible);

		vbox_btn = gtk_vbox_new ( TRUE, 0);
		gtk_box_pack_start ( GTK_BOX ( hbox), vbox_btn, TRUE, TRUE, 5);

		g_strdup_to_gtk_text ( _( "Hide"), text_utf8);
		btn_hidden = gtk_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_box_pack_start ( GTK_BOX ( vbox_btn), btn_hidden, FALSE, FALSE, 0);

		g_strdup_to_gtk_text ( _( "Show"), text_utf8);
		btn_show = gtk_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_box_pack_start ( GTK_BOX ( vbox_btn), btn_show, FALSE, FALSE, 0);
		
		scr_clist_hidden = gtk_scrolled_window_new ( NULL, NULL);
		gtk_box_pack_start ( GTK_BOX ( hbox), scr_clist_hidden, TRUE, TRUE, 0);

		clist_hidden = gtk_clist_new ( 1);
		gtk_widget_ref ( clist_hidden);
		gtk_object_set_data_full ( GTK_OBJECT ( hbox), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_HIDDEN, clist_hidden, (GtkDestroyNotify) gtk_widget_unref);
		gtk_container_add ( GTK_CONTAINER (scr_clist_hidden), clist_hidden);
		gtk_clist_set_column_width ( GTK_CLIST ( clist_hidden), 0, 80);
		gtk_clist_optimal_column_width ( GTK_CLIST ( clist_hidden), 0);
		gtk_clist_column_titles_show ( GTK_CLIST ( clist_hidden));

		g_strdup_to_gtk_text ( _( "Hidden"), text_utf8);
		col_title_hidden = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_clist_set_column_widget ( GTK_CLIST ( clist_hidden), 0, col_title_hidden);

		*pane = hbox;

		gw_plugin_settings_explorer_disk_pane_load ( hbox);

		/* Connects signals after loading. */
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : connecting all callbacks to signals...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_signal_connect  ( GTK_OBJECT ( hbox), "destroy", (GtkSignalFunc)gw_plugin_settings_explorer_disk_destroy, NULL);
		gtk_signal_connect  ( GTK_OBJECT ( btn_hidden), "clicked", (GtkSignalFunc)gw_plugin_settings_explorer_disk_btn_hide_click, hbox);
		gtk_signal_connect  ( GTK_OBJECT ( btn_show), "clicked", (GtkSignalFunc)gw_plugin_settings_explorer_disk_btn_show_click, hbox);

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_explorer_disk_pane_load ( GtkWidget *pane)
{
	gint result = -1;
	GtkCList *list_visible = NULL;
	GtkCList *list_hidden = NULL;
	GtkCList *list = NULL;
	GWSettingsExplorerField **fields;
	gint i;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		list_visible = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_VISIBLE));
		list_hidden = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_HIDDEN));

		if ( (list_visible != NULL) && (list_hidden != NULL) )
		{
			if ( (fields = gw_plugin_settings_explorer_disk_get_all_fields ( )) != NULL )
			{
			gtk_object_set_data_full ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_FIELDS_TABLE, fields, (GtkDestroyNotify) gw_settings_explorer_field_freev);

			gtk_clist_freeze ( list_visible);
			gtk_clist_freeze ( list_hidden);

			for ( i = 0; fields[i] != NULL; i++)
			{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : adding the field %s to the list visible/hidden\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, fields[i]->name);
#endif

				if ( fields[i]->visible == TRUE )
				{
					list = list_visible;
				}
				else
				{
					list = list_hidden;
				}

				gtk_clist_append ( list, &fields[i]->name);
			}

			gtk_clist_thaw ( list_visible);
			gtk_clist_thaw ( list_hidden);
			}

#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : all fields are loaded.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		}

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_explorer_disk_pane_on_change ( GtkEntry *entry, GtkWidget *pane)
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


gint gw_plugin_settings_explorer_disk_pane_apply ( GtkWidget *pane)
{
	gint result = -1;
	GtkCList *list_visible = NULL;
	GtkCList *list_hidden = NULL;
	GtkWindow *settings = NULL;
	GWSettingsExplorerField **fields = NULL;
	gint i = 0;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		list_visible = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_VISIBLE));
		list_hidden = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_HIDDEN));
		fields = (GWSettingsExplorerField**)gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_FIELDS_TABLE);

		if ( (list_visible != NULL) && (list_hidden != NULL) && (fields != NULL) )
		{
			for ( i = 0; fields[i] != NULL; i++)
			{
				gw_am_set_settings ( fields[i]->visible_v, g_strdup_printf ( "%d", (gint)fields[i]->visible));
				gw_am_set_settings ( fields[i]->position_v, g_strdup_printf ( "%d", (gint)fields[i]->position));
			}
		}

		if ( (settings = GTK_WINDOW ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, FALSE);
		}

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_explorer_disk_btn_show_click ( GtkButton *btn, GtkWidget *pane)
{
	gint result = -1;
	GtkCList *list_visible = NULL;
	GtkCList *list_hidden = NULL;
	gchar *text = NULL;
	GtkWindow *settings = NULL;
	gint row = -1;
	GWSettingsExplorerField **fields = NULL;
	GWSettingsExplorerField *field = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL)
	{
		list_visible = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_VISIBLE));
		list_hidden = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_HIDDEN));
		fields = (GWSettingsExplorerField**)gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_FIELDS_TABLE);

		if ( (list_visible != NULL) && (list_hidden != NULL) )
		{
			if ( list_hidden->selection != NULL )
			{
				row = GPOINTER_TO_INT ( ((GList*)(list_hidden->selection))->data);

				if ( row >= 0 )
				{
					gtk_clist_freeze ( list_visible);
					gtk_clist_freeze ( list_hidden);

					/* Move the column to the hidden list. */
					gtk_clist_get_text ( list_hidden, row, 0, &text);
					gtk_clist_append ( list_visible, &text);
					field = gw_settings_explorer_field_find_by_name ( fields, text);
					if ( field != NULL )
					{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
						g_print ( "*** GW - %s (%d) :: %s() : %s is showed now\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, field->name);
#endif

						field->visible = TRUE;
					}
					gtk_clist_remove ( list_hidden, row);

					gtk_clist_thaw ( list_visible);
					gtk_clist_thaw ( list_hidden);

					if ( (settings = GTK_WINDOW ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
					{
						gw_settings_window_box_set_modified ( settings, TRUE);

						result = 0;
					}
				}
			}
		}
	}

	return result;
}


gint gw_plugin_settings_explorer_disk_btn_hide_click ( GtkButton *btn, GtkWidget *pane)
{
	gint result = -1;
	GtkCList *list_visible = NULL;
	GtkCList *list_hidden = NULL;
	gchar *text = NULL;
	GtkWindow *settings = NULL;
	gint row = -1;
	GWSettingsExplorerField **fields = NULL;
	GWSettingsExplorerField *field = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL)
	{
		list_visible = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_VISIBLE));
		list_hidden = GTK_CLIST ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_LIST_HIDDEN));
		fields = (GWSettingsExplorerField**)gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EXPLORER_DISK_FIELDS_TABLE);

		if ( (list_visible != NULL) && (list_hidden != NULL) )
		{
			if ( list_visible->selection != NULL )
			{
				row = GPOINTER_TO_INT ( ((GList*)(list_visible->selection))->data);

				if ( row >= 0 )
				{
					gtk_clist_freeze ( list_visible);
					gtk_clist_freeze ( list_hidden);

					/* Move the column to the hidden list. */
					gtk_clist_get_text ( list_visible, row, 0, &text);
					gtk_clist_append ( list_hidden, &text);
					field = gw_settings_explorer_field_find_by_name ( fields, text);
					if ( field != NULL )
					{
#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
						g_print ( "*** GW - %s (%d) :: %s() : %s is hidden now\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, field->name);
#endif

						field->visible = FALSE;
					}
					gtk_clist_remove ( list_visible, row);

					gtk_clist_thaw ( list_visible);
					gtk_clist_thaw ( list_hidden);

					if ( (settings = GTK_WINDOW ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
					{
						gw_settings_window_box_set_modified ( settings, TRUE);

						result = 0;
					}
				}
			}
		}
	}

	return result;
}


gboolean gw_plugin_settings_explorer_disk_destroy ( GtkWidget *pane, gpointer data)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return result;
}

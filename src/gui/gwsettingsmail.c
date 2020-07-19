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
#include "gwsettingsmail.h"

#include "gwsettingswindowbox.h"

#include "../gwapplicationmanager.h"


/*! @define	GW_PLUGIN_SETTINGS_WINDOW	The parent window */
#define GW_PLUGIN_SETTINGS_WINDOW "gw_plugin_settings_window"
/*! @define	GW_PLUGIN_SETTINGS_EMAIL_ADDRESS_ENTRY	The entry for email address */
#define GW_PLUGIN_SETTINGS_EMAIL_ADDRESS_ENTRY "gw_plugin_settings_email_address_entry"
/*! @define	GW_PLUGIN_SETTINGS_SERVER_ADDRESS_ENTRY	The entry for server address */
#define GW_PLUGIN_SETTINGS_SERVER_ADDRESS_ENTRY "gw_plugin_settings_server_address_entry"
/*! @define	GW_PLUGIN_SETTINGS_SERVER_PORT_ENTRY	The entry for server port */
#define GW_PLUGIN_SETTINGS_SERVER_PORT_ENTRY "gw_plugin_settings_server_port_entry"


gint gw_plugin_settings_mail_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane);
gint gw_plugin_settings_mail_pane_load ( GtkWidget *pane);
gint gw_plugin_settings_mail_pane_on_change ( GtkEntry *entry, GtkWidget *pane);
gint gw_plugin_settings_mail_pane_apply ( GtkWidget *pane);


/*!
 * @function	gw_settings_window_box_get_mail_notebook_email_address
 * @abstract	Gets the filled email address.
 * @discussion	This function gets the filled email address.
 * @param	w	the settings window box
 * @result	the filled email address
 *		Returns <i>NULL</i> when an error occured.<br>
 */
/*gchar * gw_settings_window_box_get_mail_notebook_email_address ( GtkWindow *w);*/


/*!
 * @function	gw_settings_window_box_get_mail_notebook_server_address
 * @abstract	Gets the filled server address.
 * @discussion	This function gets the filled server address.
 * @param	w	the settings window box
 * @result	the filled server address
 *		Returns <i>NULL</i> when an error occured.<br>
 */
/*gchar * gw_settings_window_box_get_mail_notebook_server_address ( GtkWindow *w);*/


/*!
 * @function	gw_settings_window_box_get_mail_notebook_server_port
 * @abstract	Gets the filled server port.
 * @discussion	This function gets the filled server port.
 * @param	w	the settings window box
 * @result	the filled server port
 *		Returns <i>-1</i> when an error occured.<br>
 */
/*gint gw_settings_window_box_get_mail_notebook_server_port ( GtkWindow *w);*/


gint gw_plugin_settings_mail_init ( GWSettingsModule **module)
{
	gint result = -1;

	if ( (*module = gw_settings_module_new ( )) != NULL )
	{
		(*module)->name = g_strdup ( _( "Mail"));
		(*module)->create = &gw_plugin_settings_mail_pane_create;
		(*module)->load = &gw_plugin_settings_mail_pane_load;
		(*module)->on_change = &gw_plugin_settings_mail_pane_on_change;
		(*module)->apply = &gw_plugin_settings_mail_pane_apply;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_mail_pane_create ( GtkWindow *settings, GtkContainer *parent, GtkWidget **pane)
{
	gint result = -1;
	GtkWidget *table_pane;
	GtkWidget *lbl_email_address;
	GtkWidget *lbl_server_address;
	GtkWidget *lbl_server_port;
	GtkWidget *ent_email_address;
	GtkWidget *ent_server_address;
	GtkWidget *ent_server_port;
	GtkTooltips *tooltips;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	tooltips = gtk_tooltips_new ( );

	if ( settings != NULL && parent != NULL )
	{
		table_pane = gtk_table_new ( 3, 2, FALSE);
		gtk_widget_ref ( GTK_WIDGET ( settings));
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_WINDOW, settings, (GtkDestroyNotify) gtk_widget_unref);
		gtk_container_set_border_width ( GTK_CONTAINER ( table_pane), 5);
		gtk_table_set_row_spacings ( GTK_TABLE (table_pane), 5);
		gtk_table_set_col_spacings ( GTK_TABLE (table_pane), 5);

		/* Email address. */
		g_strdup_to_gtk_text ( _( "Email address :"), text_utf8);
		lbl_email_address = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( table_pane), lbl_email_address, 0, 1, 0, 1, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lbl_email_address), 0, 0.5);

		ent_email_address = gtk_entry_new ( );
		gtk_widget_ref ( ent_email_address);
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_EMAIL_ADDRESS_ENTRY, ent_email_address, (GtkDestroyNotify) gtk_widget_unref);
		gtk_table_attach ( GTK_TABLE ( table_pane), ent_email_address, 1, 2, 0, 1, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		g_strdup_to_gtk_text ( _( "Enter your email address."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, ent_email_address, text_utf8, NULL);
		g_free ( text_utf8);

		/* Server address. */
		g_strdup_to_gtk_text ( _( "Out going mail server :"), text_utf8);
		lbl_server_address = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( table_pane), lbl_server_address, 0, 1, 1, 2, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lbl_server_address), 0, 0.5);

		ent_server_address = gtk_entry_new ( );
		gtk_widget_ref ( ent_server_address);
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_SERVER_ADDRESS_ENTRY, ent_server_address, (GtkDestroyNotify) gtk_widget_unref);
		gtk_table_attach ( GTK_TABLE ( table_pane), ent_server_address, 1, 2, 1, 2, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		g_strdup_to_gtk_text ( _( "Enter your out going mail server. Usualy this address is mail.yourdomain.com"), text_utf8);
		gtk_tooltips_set_tip ( tooltips, ent_server_address, text_utf8, NULL);
		g_free ( text_utf8);

		/* Server port. */
		g_strdup_to_gtk_text ( _( "Server port :"), text_utf8);
		lbl_server_port = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( table_pane), lbl_server_port, 0, 1, 2, 3, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lbl_server_port), 0, 0.5);

		ent_server_port = gtk_entry_new ( );
		gtk_widget_ref ( ent_server_port);
		gtk_object_set_data_full ( GTK_OBJECT ( table_pane), GW_PLUGIN_SETTINGS_SERVER_PORT_ENTRY, ent_server_port, (GtkDestroyNotify) gtk_widget_unref);
		gtk_table_attach ( GTK_TABLE ( table_pane), ent_server_port, 1, 2, 2, 3, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (0), 0, 0);
		g_strdup_to_gtk_text ( _( "Enter the out going mail server port (the most common value is 25)."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, ent_server_port, text_utf8, NULL);
		g_free ( text_utf8);

		*pane = table_pane;

		gw_plugin_settings_mail_pane_load ( table_pane);

		/* Connects signals after loading. */
		gtk_signal_connect  ( GTK_OBJECT ( ent_email_address), "changed", (GtkSignalFunc)gw_plugin_settings_mail_pane_on_change, table_pane);
		gtk_signal_connect  ( GTK_OBJECT ( ent_server_address), "changed", (GtkSignalFunc)gw_plugin_settings_mail_pane_on_change, table_pane);
		gtk_signal_connect  ( GTK_OBJECT ( ent_server_port), "changed", (GtkSignalFunc)gw_plugin_settings_mail_pane_on_change, table_pane);

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_mail_pane_load ( GtkWidget *pane)
{
	gint result = -1;
	GtkEntry *entry = NULL;
	gchar *value = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{

		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EMAIL_ADDRESS_ENTRY))) != NULL)
		{
			value = gw_am_get_settings ( GW_VALUE_APP_MAIL_EMAIL_ADDRESS);

			g_strdup_to_gtk_text ( value, text_utf8);
			gtk_entry_set_text ( GTK_ENTRY ( entry), text_utf8);
			g_free ( text_utf8);
		}

		entry = NULL;
		value = NULL;

		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SERVER_ADDRESS_ENTRY))) != NULL)
		{
			value = gw_am_get_settings ( GW_VALUE_APP_MAIL_SERVER_ADDRESS);

			g_strdup_to_gtk_text ( value, text_utf8);
			gtk_entry_set_text ( GTK_ENTRY ( entry), text_utf8);
			g_free ( text_utf8);
		}

		entry = NULL;
		value = NULL;

		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SERVER_PORT_ENTRY))) != NULL)
		{
			value = gw_am_get_settings ( GW_VALUE_APP_MAIL_SERVER_PORT);

			if ( value == NULL )
			{
				g_strdup_to_gtk_text ( GW_VALUE_APP_MAIL_SERVER_PORT_DEFAULT, text_utf8);
			}
			else
			{
				g_strdup_to_gtk_text ( value, text_utf8);
			}

			gtk_entry_set_text ( GTK_ENTRY ( entry), text_utf8);
			g_free ( text_utf8);
		}

		entry = NULL;
		value = NULL;

		result = 0;
	}

	return result;
}


gint gw_plugin_settings_mail_pane_on_change ( GtkEntry *entry, GtkWidget *pane)
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


gint gw_plugin_settings_mail_pane_apply ( GtkWidget *pane)
{
	gint result = -1;
	GtkEntry *entry = NULL;
	gchar *value = NULL;
	GtkWindow *settings = NULL;


#ifdef GW_DEBUG_PLUGIN_SETTINGS_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( pane != NULL )
	{
		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_EMAIL_ADDRESS_ENTRY))) != NULL)
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), value);
			gw_am_set_settings ( GW_VALUE_APP_MAIL_EMAIL_ADDRESS, value);
		}

		entry = NULL;
		value = NULL;

		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SERVER_ADDRESS_ENTRY))) != NULL)
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), value);
			gw_am_set_settings ( GW_VALUE_APP_MAIL_SERVER_ADDRESS, value);
		}

		entry = NULL;
		value = NULL;

		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_SERVER_PORT_ENTRY))) != NULL)
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), value);
			gw_am_set_settings ( GW_VALUE_APP_MAIL_SERVER_PORT, value);
		}

		entry = NULL;
		value = NULL;

		if ( (settings = GTK_WINDOW ( gtk_object_get_data ( GTK_OBJECT ( pane), GW_PLUGIN_SETTINGS_WINDOW))) != NULL )
		{
			gw_settings_window_box_set_modified ( settings, FALSE);
		}

		result = 0;
	}

	return result;
}

/*
gchar * gw_settings_window_box_get_mail_notebook_email_address ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *email_address = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_MAIL_NOTEBOOK_EMAIL_ENTRY));
		email_address = gtk_entry_get_text ( entry);
	}

	return email_address;
}
*/
/*
gchar * gw_settings_window_box_get_mail_notebook_server_address ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *server_address = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_MAIL_NOTEBOOK_SERVER_ENTRY));
		server_address = gtk_entry_get_text ( entry);
	}

	return server_address;
}
*/
/*
gint gw_settings_window_box_get_mail_notebook_server_port ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gint server_port = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_SETTINGS_WINDOW_BOX_MAIL_NOTEBOOK_SERVER_PORT_ENTRY));
		server_port = strtol ( gtk_entry_get_text ( entry), NULL,0);
	}

	return server_port;
}
*/

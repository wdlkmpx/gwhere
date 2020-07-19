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
#include "gwcapturebox.h"


/*! @define	GW_REF_GW_CAPTURE_BOX_PARENT_WINDOW	The parent window */
#define GW_REF_GW_CAPTURE_BOX_PARENT_WINDOW "gw_ref_gw_capture_box_parent_window"
/*! @define	GW_REF_GW_CAPTURE_BOX_DATA_CAPTURE	The text field */
#define GW_REF_GW_CAPTURE_BOX_DATA_CAPTURE "gw_ref_gw_capture_box_data_capture"
/*! @define	DATA_GW_CAPTURE_MAX_SIZE	The max size of text field */
#define DATA_GW_CAPTURE_MAX_SIZE 255
/*! @define	GW_REF_GW_CAPTURE_BOX_ACCEL_GROUP	The accel group of the capture box */
#define GW_REF_GW_CAPTURE_BOX_ACCEL_GROUP "gw_ref_gw_capture_box_accel_group"


GtkWidget * gw_capture_box_create ( GtkWindow *window, gchar *title, gchar *subject, gchar *text, GtkSignalFunc ok)
{
	/* This window must be single, this property may be changed */
	static GtkWidget *w = NULL;
	GtkWidget *frame = NULL;
	GtkWidget *vbox = NULL;
	GtkWidget *hbox = NULL;
	GtkWidget *entry_data_capture = NULL;
	GtkWidget *button = NULL;
	guint button_key;
	GtkAccelGroup *accel = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !w )
	{
		/* Init an accel group for shortcuts */
		accel = gtk_accel_group_new ( );

		w = gtk_window_new ( GTK_WINDOW_TOPLEVEL);
		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, TRUE);
		g_strdup_to_gtk_text ( title, text_utf8);
		gtk_window_set_title ( GTK_WINDOW ( w), text_utf8);
		g_free ( text_utf8);
		gtk_container_border_width ( GTK_CONTAINER ( w), 10);

		gtk_window_set_modal ( GTK_WINDOW ( w),TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);

		gtk_signal_connect ( GTK_OBJECT ( w), "destroy", GTK_SIGNAL_FUNC ( gw_capture_box_destroy), &w);
		gtk_signal_connect ( GTK_OBJECT ( w), "delete-event", GTK_SIGNAL_FUNC ( gtk_widget_destroy), NULL);

		/* Store parent window reference */
		gtk_widget_ref ( GTK_WIDGET ( window));
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_GW_CAPTURE_BOX_PARENT_WINDOW, window, ( GtkDestroyNotify) gtk_widget_unref);

		frame = gtk_frame_new ( subject);
		gtk_container_add ( GTK_CONTAINER ( w), frame);

		vbox = gtk_vbox_new ( TRUE, 10);
		gtk_container_add ( GTK_CONTAINER ( frame), vbox);
		gtk_container_set_border_width ( GTK_CONTAINER ( vbox), 10);

		entry_data_capture = gtk_entry_new_with_max_length ( DATA_GW_CAPTURE_MAX_SIZE);
		gtk_signal_connect ( GTK_OBJECT ( entry_data_capture), "activate", GTK_SIGNAL_FUNC ( ok), w);

		/* Store data capture reference */
		gtk_widget_ref ( entry_data_capture);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_GW_CAPTURE_BOX_DATA_CAPTURE, entry_data_capture, ( GtkDestroyNotify) gtk_widget_unref);
		g_strdup_to_gtk_text ( text, text_utf8);
		gtk_entry_set_text ( GTK_ENTRY ( entry_data_capture), text_utf8);
		g_free ( text_utf8);
		gtk_box_pack_start ( GTK_BOX ( vbox), entry_data_capture, TRUE, TRUE, 0);
		GTK_WIDGET_SET_FLAGS ( entry_data_capture, GTK_CAN_FOCUS);
		gtk_widget_grab_focus ( entry_data_capture);
		gtk_entry_select_region ( GTK_ENTRY ( entry_data_capture), 0, -1);

		hbox = gtk_hbox_new ( TRUE, 10);
		gtk_container_add ( GTK_CONTAINER ( vbox), hbox);

		button = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_OK"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked", accel, button_key, GDK_MOD1_MASK, 0);
		gtk_object_set_user_data ( GTK_OBJECT ( button), w);
		gtk_box_pack_start ( GTK_BOX ( hbox), button, TRUE, TRUE, 0);

		if ( ok != NULL )
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : connecting the ok callback function...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			gtk_signal_connect ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( ok), w);
		}
		else
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : ok callback function is null\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			gtk_signal_connect_object ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		button = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_Cancel"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked", accel, button_key, GDK_MOD1_MASK, 0);
		gtk_object_set_user_data ( GTK_OBJECT ( button), w);
		gtk_box_pack_start ( GTK_BOX ( hbox), button, TRUE, TRUE, 0);
		gtk_signal_connect_object ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));

		gtk_window_add_accel_group ( GTK_WINDOW ( w), accel);
	}

	if ( !GTK_WIDGET_VISIBLE ( w) )
	{
#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : show the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_show_all ( w);
	}
	else
	{
#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : destroy the window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_destroy ( w);
	}

	return w;
}


gchar * gw_capture_box_get_text ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_GW_CAPTURE_BOX_DATA_CAPTURE))) != NULL)
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), text);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : data capture = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif
		}
	}

	return text;
}


GtkWindow * gw_capture_box_get_main_window ( GtkWindow *w)
{
	GtkWidget *parent = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		parent = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_GW_CAPTURE_BOX_PARENT_WINDOW);
	}

	if ( parent == NULL )
	{
#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : parent window is null\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return GTK_WINDOW ( parent);
}


gint gw_capture_box_destroy ( GtkWindow *w, GtkWidget **self_window)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
                g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && ( self_window != NULL) )
	{
		gtk_widget_destroyed ( GTK_WIDGET ( w), self_window);

		result = 0;
	}

	return result;
}

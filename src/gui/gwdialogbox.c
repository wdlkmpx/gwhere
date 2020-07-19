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
#include "gwdialogbox.h"


/*! @define	GW_REF_DIALOG_BOX_PARENT_WINDOW	The parent window */
#define GW_REF_DIALOG_BOX_PARENT_WINDOW "gw_ref_dialog_box_parent_window"
/*! @define	GW_REF_DIALOG_BOX_USER_DATA	The attached user data */
#define GW_REF_DIALOG_BOX_USER_DATA "gw_ref_dialog_box_user_data"


GtkWidget * gw_dialog_box_create ( GtkWindow *window, gchar *title, gchar *text, GtkSignalFunc ok, GtkSignalFunc no, GtkSignalFunc cancel, gpointer data)
{
	/*static */GtkWidget *w = NULL;
	GtkWidget *label;
	GtkWidget *button;
	guint button_key;
	GtkAccelGroup *accel;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !w )
	{
		accel = gtk_accel_group_new ( );

		w = gtk_dialog_new ( );

		if ( window != NULL )
		{
			gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
			gtk_window_set_transient_for ( GTK_WINDOW ( w), GTK_WINDOW ( window));
			gtk_object_set_data ( GTK_OBJECT ( w), GW_REF_DIALOG_BOX_PARENT_WINDOW, window);
		}

		if ( data != NULL )
		{
			gtk_object_set_data ( GTK_OBJECT ( w), GW_REF_DIALOG_BOX_USER_DATA, data);
		}

		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
		gtk_container_set_border_width ( GTK_CONTAINER ( w), 10);
		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, TRUE);

#ifdef HAVE_GTK12
		gtk_signal_connect ( GTK_OBJECT ( w), "destroy", GTK_SIGNAL_FUNC ( gtk_widget_destroyed), &w);
#endif
		g_strdup_to_gtk_text ( title, text_utf8);
		gtk_window_set_title ( GTK_WINDOW ( w), text_utf8);
		g_free ( text_utf8);

		g_strdup_to_gtk_text ( text, text_utf8);
		label = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_misc_set_padding ( GTK_MISC ( label), 10, 10);
		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->vbox), label, TRUE, TRUE, 0);

		button = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_OK"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked", accel, button_key, GDK_MOD1_MASK, 0);

		if ( ok != NULL )
		{
			gtk_signal_connect ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( ok), w);
		}
		else
		{
			gtk_signal_connect_object ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->action_area), button, TRUE, TRUE, 0);
		gtk_widget_grab_focus ( button);

		button = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _("_No"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked", accel, button_key, GDK_MOD1_MASK, 0);

		if ( no != NULL )
		{
			gtk_signal_connect ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( no), w);
		}
		else
		{
			gtk_signal_connect_object ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->action_area), button, TRUE, TRUE, 0);

		button = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _("_Cancel"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked", accel, button_key, GDK_MOD1_MASK, 0);

		if ( cancel != NULL )
		{
			gtk_signal_connect ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( cancel), w);
		}
		else
		{
			gtk_signal_connect_object ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->action_area), button, TRUE, TRUE, 0);

		gtk_window_add_accel_group ( GTK_WINDOW ( w), accel);
	}

	if ( !GTK_WIDGET_VISIBLE ( w) )
	{
		gtk_widget_show_all ( w);
	}
	else
	{
		gtk_widget_destroy ( w);
	}

	return w;
}


gpointer gw_dialog_box_get_user_data ( GtkWindow *w)
{
	gpointer data = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		data = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_DIALOG_BOX_USER_DATA);
	}

	return data;
}


GtkWindow * gw_dialog_box_get_parent_window ( GtkWindow *w)
{
	GtkWindow *window = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		window = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_DIALOG_BOX_PARENT_WINDOW);
	}

	return window;
}

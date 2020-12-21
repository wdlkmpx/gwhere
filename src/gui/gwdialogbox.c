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


GtkWidget * gw_dialog_box_create ( GtkWindow *window, gchar *title, gchar *text, GCallback ok, GCallback no, GCallback cancel, gpointer data)
{
	/*static */GtkWidget *w = NULL;
	GtkWidget *label;
	GtkWidget *button;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !w )
	{
		w = gtk_dialog_new ( );

		if ( window != NULL )
		{
			gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
			gtk_window_set_transient_for ( GTK_WINDOW ( w), GTK_WINDOW ( window));
			g_object_set_data (G_OBJECT ( w), GW_REF_DIALOG_BOX_PARENT_WINDOW, window);
		}

		if ( data != NULL )
		{
			g_object_set_data (G_OBJECT ( w), GW_REF_DIALOG_BOX_USER_DATA, data);
		}

		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
		gtk_container_set_border_width ( GTK_CONTAINER ( w), 10);
		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, TRUE);

		gtk_window_set_title ( GTK_WINDOW ( w), title);

		label = gtk_label_new (text);
		gtk_misc_set_padding ( GTK_MISC ( label), 10, 10);
		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->vbox), label, TRUE, TRUE, 0);

		button = gtk_button_new_with_mnemonic (_("_OK"));

		if ( ok != NULL )
		{
			g_signal_connect (G_OBJECT ( button), "clicked", G_CALLBACK ( ok), w);
		}
		else
		{
			g_signal_connect_swapped (G_OBJECT ( button), "clicked", G_CALLBACK ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->action_area), button, TRUE, TRUE, 0);
		gtk_widget_grab_focus ( button);

		button = gtk_button_new_with_mnemonic (_("_No"));

		if ( no != NULL )
		{
			g_signal_connect (G_OBJECT ( button), "clicked", G_CALLBACK ( no), w);
		}
		else
		{
			g_signal_connect_swapped (G_OBJECT ( button), "clicked", G_CALLBACK ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->action_area), button, TRUE, TRUE, 0);

		button = gtk_button_new_with_mnemonic (_("_Cancel"));

		if ( cancel != NULL )
		{
			g_signal_connect (G_OBJECT ( button), "clicked", G_CALLBACK ( cancel), w);
		}
		else
		{
			g_signal_connect_swapped (G_OBJECT ( button), "clicked", G_CALLBACK ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		gtk_box_pack_start ( GTK_BOX ( GTK_DIALOG ( w)->action_area), button, TRUE, TRUE, 0);
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
		data = g_object_get_data (G_OBJECT ( w), GW_REF_DIALOG_BOX_USER_DATA);
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
		window = g_object_get_data (G_OBJECT ( w), GW_REF_DIALOG_BOX_PARENT_WINDOW);
	}

	return window;
}

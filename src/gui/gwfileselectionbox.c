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
#include "gwfileselectionbox.h"

#include "../gwguimanager.h"


/*! @define	GW_REF_FILE_SELECTION_BOX_USER_DATA	The attached user data */
#define GW_REF_FILE_SELECTION_BOX_USER_DATA "gw_ref_file_selection_box_user_data"


GtkWidget * gw_file_selection_box_create ( gchar *title, gchar *filename, GCallback ok, GCallback cancel)
{
	static GtkWidget *w = NULL;
	GtkWidget *button;
	GtkWindow *window = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !w )
	{
		window = gw_gui_manager_main_interface_get_main_window ( );

		w = gtk_file_selection_new (title);

		if ( filename != NULL ) {
			gtk_file_selection_set_filename ( GTK_FILE_SELECTION ( w), filename);
		}

		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, TRUE);
		gtk_file_selection_show_fileop_buttons ( GTK_FILE_SELECTION ( w));

		gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), GTK_WINDOW ( window));
		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);

		g_signal_connect (G_OBJECT ( w), "destroy", G_CALLBACK ( gtk_widget_destroyed), &w);
		gtk_button_set_relief ( GTK_BUTTON ( GTK_FILE_SELECTION ( w)->ok_button), GTK_RELIEF_HALF);

		if ( ok != NULL )
		{
			g_signal_connect (G_OBJECT ( GTK_FILE_SELECTION ( w)->ok_button), "clicked", G_CALLBACK ( ok), w);
		}

		if ( cancel != NULL )
		{
			g_signal_connect (G_OBJECT ( GTK_FILE_SELECTION ( w)->cancel_button), "clicked", G_CALLBACK ( cancel), w);
		}
		else
		{
			g_signal_connect_swapped (G_OBJECT ( GTK_FILE_SELECTION ( w)->cancel_button), "clicked", G_CALLBACK ( gtk_widget_destroy), GTK_OBJECT ( w));
		}
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


gpointer gw_file_selection_box_get_user_data ( GtkWindow *w)
{
	gpointer data = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		data = g_object_get_data (G_OBJECT ( w), GW_REF_FILE_SELECTION_BOX_USER_DATA);
	}

	return data;
}

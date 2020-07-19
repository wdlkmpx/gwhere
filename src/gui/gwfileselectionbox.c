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


GtkWidget * gw_file_selection_box_create ( gchar *title, gchar *filename, GtkSignalFunc ok, GtkSignalFunc cancel)
{
	static GtkWidget *w = NULL;
	GtkWidget *button;
	GtkWindow *window = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !w )
	{
		window = gw_gui_manager_main_interface_get_main_window ( );

		g_strdup_to_gtk_text ( title, text_utf8);
		w = gtk_file_selection_new ( text_utf8);
		g_free ( text_utf8);

		if ( filename != NULL ) {
			g_strdup_to_gtk_text ( filename, text_utf8);
			gtk_file_selection_set_filename ( GTK_FILE_SELECTION ( w), text_utf8);
			g_free ( text_utf8);
		}

		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, TRUE);
		gtk_file_selection_hide_fileop_buttons ( GTK_FILE_SELECTION ( w));

		gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), GTK_WINDOW ( window));
		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);

		gtk_signal_connect ( GTK_OBJECT ( w), "destroy", GTK_SIGNAL_FUNC ( gtk_widget_destroyed), &w);
		gtk_button_set_relief ( GTK_BUTTON ( GTK_FILE_SELECTION ( w)->ok_button), GTK_RELIEF_HALF);

		if ( ok != NULL )
		{
			gtk_signal_connect ( GTK_OBJECT ( GTK_FILE_SELECTION ( w)->ok_button), "clicked", GTK_SIGNAL_FUNC ( ok), w);
		}

		if ( cancel != NULL )
		{
			gtk_signal_connect ( GTK_OBJECT ( GTK_FILE_SELECTION ( w)->cancel_button), "clicked", GTK_SIGNAL_FUNC ( cancel), w);
		}
		else
		{
			gtk_signal_connect_object ( GTK_OBJECT ( GTK_FILE_SELECTION ( w)->cancel_button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		g_strdup_to_gtk_text ( _( "Hide file operations"), text_utf8);
		button = gtk_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_signal_connect ( GTK_OBJECT ( button), "clicked", (GtkSignalFunc) gw_file_selection_box_hide_fileops, (gpointer) w);
		gtk_box_pack_start ( GTK_BOX ( GTK_FILE_SELECTION ( w)->action_area), button, FALSE, FALSE, 0);

		g_strdup_to_gtk_text ( _( "Show file operation"), text_utf8);
		button = gtk_button_new_with_label ( text_utf8);
		g_free ( text_utf8);
		gtk_signal_connect_object ( GTK_OBJECT ( button), "clicked", (GtkSignalFunc) gtk_file_selection_show_fileop_buttons, (gpointer) w);
		gtk_box_pack_start ( GTK_BOX ( GTK_FILE_SELECTION ( w)->action_area), button, FALSE, FALSE, 0);
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


GtkWidget * gw_file_selection_box_create_full ( gchar *title, gchar *filename, GtkSignalFunc ok, GtkSignalFunc cancel, gpointer data)
{
	GtkWidget *fs = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	fs = gw_file_selection_box_create ( title, filename, ok, cancel);

	if ( fs != NULL )
	{
		gtk_object_set_data ( GTK_OBJECT ( fs), GW_REF_FILE_SELECTION_BOX_USER_DATA, data);
	}

	return fs;
}


gboolean gw_file_selection_box_hide_fileops ( GtkWidget *widget, GtkFileSelection *fs)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		gtk_file_selection_hide_fileop_buttons ( fs);

		result = TRUE;
	}

	return result;
}


gboolean gw_file_selection_box_show_fileops ( GtkWidget *widget, GtkFileSelection *fs)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( fs != NULL )
	{
		gtk_file_selection_show_fileop_buttons ( fs);

		result = TRUE;
	}

	return result;
}


gpointer gw_file_selection_box_get_user_data ( GtkWindow *w)
{
	gpointer data = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		data = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_FILE_SELECTION_BOX_USER_DATA);
	}

	return data;
}

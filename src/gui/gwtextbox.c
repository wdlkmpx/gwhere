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
#include "gwtextbox.h"

#include "gtktextarea.h"

#include <string.h> /* strlen */


/*! @define	GW_REF_TEXT_BOX_PARENT_WINDOW	The parent window reference */
#define GW_REF_TEXT_BOX_PARENT_WINDOW "gw_ref_gw_text_box_parent_window"
/*! @define	GW_REF_TEXT_DATA_TEXT	The data text reference */
#define GW_REF_TEXT_DATA_TEXT "gw_ref_text_data_text"


GtkWidget * gw_text_box_create ( GtkWindow *window, gchar *title, gchar *subject, gchar *text, GtkSignalFunc ok)
{
	/* This is a single window, this properties may be changed */
	static GtkWidget *w = NULL;
	GtkWidget *frame = NULL;
	GtkWidget *vbox = NULL;
	GtkWidget *hbox = NULL;
	GtkWidget *scroll_zone = NULL;
	GtkWidget *txt_area = NULL;
	GtkWidget *button = NULL;
	guint button_key;
	GtkAccelGroup *accel = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Inits an accel group for keystroke shortcuts */
	accel = gtk_accel_group_new ( );

	if ( !w )
	{
		w = gtk_window_new ( GTK_WINDOW_TOPLEVEL);
		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, TRUE);
		g_strdup_to_gtk_text ( title, text_utf8);
		gtk_window_set_title ( GTK_WINDOW ( w), text_utf8);
		g_free ( text_utf8);
		gtk_window_set_modal ( GTK_WINDOW ( w),TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
		gtk_container_border_width ( GTK_CONTAINER ( w), 5);

		gtk_signal_connect ( GTK_OBJECT ( w), "destroy", GTK_SIGNAL_FUNC ( gtk_widget_destroyed), &w);

		/* Store parent window reference */
		gtk_widget_ref ( GTK_WIDGET ( window));
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_TEXT_BOX_PARENT_WINDOW, window, (GtkDestroyNotify) gtk_widget_unref);

		frame = gtk_frame_new ( subject);
		gtk_container_add ( GTK_CONTAINER ( w), frame);

		vbox = gtk_vbox_new ( FALSE, 0);
		gtk_container_add ( GTK_CONTAINER ( frame), vbox);
		gtk_container_set_border_width ( GTK_CONTAINER ( vbox), 10);

		/* Creates the text srollbar */
		scroll_zone = gtk_scrolled_window_new ( NULL, NULL);
		gtk_box_pack_start ( GTK_BOX ( vbox), scroll_zone, TRUE, TRUE, 0);
		gtk_container_set_border_width ( GTK_CONTAINER ( scroll_zone), 5);
		gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scroll_zone), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		/* Creates text area */
		txt_area = gtk_text_area_new ( );
		gtk_text_area_set_editable ( GTK_TEXT_AREA ( txt_area), TRUE);

		/* Sets default text value */
		if ( text != NULL )
		{
			gtk_text_area_insert ( GTK_TEXT_AREA ( txt_area), text);
		}

		gtk_widget_set_usize ( txt_area, 400, 300);
		gtk_widget_ref ( txt_area);

		/* Store data text reference */
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_TEXT_DATA_TEXT, txt_area, (GtkDestroyNotify) gtk_widget_unref);
		gtk_container_add ( GTK_CONTAINER ( scroll_zone), txt_area);
		gtk_widget_grab_focus ( txt_area);

		hbox = gtk_hbox_new ( TRUE, 10);
		gtk_container_add ( GTK_CONTAINER ( vbox), hbox);
		gtk_container_set_border_width ( GTK_CONTAINER ( hbox), 5);

		button = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_OK"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked", accel, button_key, GDK_MOD1_MASK, 0);
		gtk_object_set_user_data ( GTK_OBJECT ( button), w);
		gtk_box_pack_start ( GTK_BOX ( hbox), button, TRUE, TRUE, 0);

		if ( ok != NULL )
		{
			gtk_signal_connect ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( ok), w);
		}
		else
		{
			gtk_signal_connect_object ( GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		}

		button = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_Cancel"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked", accel, button_key, GDK_MOD1_MASK, 0);
		gtk_object_set_user_data ( GTK_OBJECT ( button), w);
		gtk_box_pack_start ( GTK_BOX ( hbox), button, TRUE, TRUE, 0);
		gtk_signal_connect_object ( GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));

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


gchar * gw_text_box_get_text ( GtkWidget *w)
{
	GtkTextArea *text_area = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (text_area = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_TEXT_DATA_TEXT)) != NULL )
		{
			text = gtk_text_area_get_text ( GTK_TEXT_AREA ( text_area));
		}
	}

	return text;
}


GtkWindow * gw_text_box_get_parent_window ( GtkWidget *w)
{
	GtkWindow *parent = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		parent = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_TEXT_BOX_PARENT_WINDOW);
	}

	return parent;
}

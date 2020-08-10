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
#include "gwmsgbox.h"


GtkWindow * gw_msg_box_create ( GtkWindow *window, gchar *title, gchar *subject)
{
	/*static */GtkWidget *w = NULL;
	GtkWidget *vbox,*label,*button,*hbox;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : title=%s subject=%s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, title, subject);
#endif

	if ( !w )
	{
#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() new dialog window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		w = gtk_window_new ( GTK_WINDOW_DIALOG);

		gtk_window_set_policy ( GTK_WINDOW ( w), FALSE, FALSE, TRUE);
		gtk_window_set_title ( GTK_WINDOW ( w), title);
		gtk_container_border_width ( GTK_CONTAINER ( w), 10);

		gtk_window_set_modal ( GTK_WINDOW ( w),TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
		gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);

		vbox = gtk_vbox_new ( TRUE, 10);
		gtk_container_add ( GTK_CONTAINER ( w), vbox);
		gtk_container_set_border_width ( GTK_CONTAINER ( vbox), 10);

		label = gtk_label_new (subject);
		gtk_box_pack_start ( GTK_BOX ( vbox), label, FALSE, FALSE, 0);

		/* The Ok button area */
		hbox = gtk_hbutton_box_new ( );
		gtk_button_box_set_layout ( GTK_BUTTON_BOX ( hbox), GTK_BUTTONBOX_EDGE);
		gtk_button_box_set_spacing ( GTK_BUTTON_BOX ( hbox), 5);
		gtk_box_pack_end ( GTK_BOX ( vbox), hbox, FALSE, FALSE, 0);

		button = gtk_button_new_with_mnemonic (_("_OK"));
		gtk_object_set_user_data ( GTK_OBJECT ( button), w);
		gtk_box_pack_start ( GTK_BOX ( hbox), button, TRUE, FALSE, 0);
		gtk_signal_connect_object ( GTK_OBJECT ( button), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		GTK_WIDGET_SET_FLAGS ( button, GTK_CAN_FOCUS);
		gtk_widget_grab_focus ( button);
	}

	if ( !GTK_WIDGET_VISIBLE ( w))
	{
		gtk_widget_show_all ( w);
	}
	else
	{
		gtk_widget_destroy ( w);
	}

	return GTK_WINDOW ( w);
}

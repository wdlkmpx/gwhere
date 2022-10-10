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
#include "gwtoolbar.h"

#include "res/gwres.h"

#include "gwmenufilecallback.h"


GtkWidget * gw_tool_bar_create ( GtkWindow *w)
{
	GtkWidget *toolbar, * hbox, * button;
	GtkWidget *pix_ico_new;
	GtkWidget *pix_ico_open;
	GtkWidget *pix_ico_save;
	GtkWidget *pix_ico_close;

	toolbar = gtk_handle_box_new ( );
	gtk_handle_box_set_shadow_type ( GTK_HANDLE_BOX ( toolbar), GTK_SHADOW_OUT);

	hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 4);
	gtk_container_set_border_width (GTK_CONTAINER (hbox), 5);
	gtk_container_add (GTK_CONTAINER (toolbar), hbox);

	pix_ico_new   = gtk_image_new_from_stock (GTK_STOCK_NEW,   GTK_ICON_SIZE_SMALL_TOOLBAR);
	pix_ico_open  = gtk_image_new_from_stock (GTK_STOCK_OPEN,  GTK_ICON_SIZE_SMALL_TOOLBAR);
	pix_ico_save  = gtk_image_new_from_stock (GTK_STOCK_SAVE,  GTK_ICON_SIZE_SMALL_TOOLBAR);
	pix_ico_close = gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_SMALL_TOOLBAR);

	button = gtk_button_new ();
	gtk_button_set_image (GTK_BUTTON (button), pix_ico_new);
	g_signal_connect (button, "clicked", G_CALLBACK (gw_menu_file_new_click), w);
	gtk_widget_set_tooltip_text (button, _("New catalog"));
	gtk_button_set_relief (GTK_BUTTON (button), GTK_RELIEF_NONE);
	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);

	button = gtk_button_new ();
	gtk_button_set_image (GTK_BUTTON (button), pix_ico_open);
	g_signal_connect (button, "clicked", G_CALLBACK (gw_menu_file_open_click), w);
	gtk_widget_set_tooltip_text (button, _( "Open catalog"));
	gtk_button_set_relief (GTK_BUTTON (button), GTK_RELIEF_NONE);
	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);

	button = gtk_button_new ();
	gtk_button_set_image (GTK_BUTTON (button), pix_ico_save);
	g_signal_connect (button, "clicked", G_CALLBACK (gw_menu_file_save_click), w);
	gtk_widget_set_tooltip_text (button, _( "Save catalog"));
	gtk_button_set_relief (GTK_BUTTON (button), GTK_RELIEF_NONE);
	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);

	button = gtk_button_new ();
	gtk_button_set_image (GTK_BUTTON (button), pix_ico_close);
	g_signal_connect (button, "clicked", G_CALLBACK (gw_menu_file_close_click), w);
	gtk_widget_set_tooltip_text (button, _( "Close catalog"));
	gtk_button_set_relief (GTK_BUTTON (button), GTK_RELIEF_NONE);
	gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);

	return toolbar;
}


GtkWidget * gw_tool_bar_create_and_add ( GtkWindow *w, GtkWidget *parent)
{
	GtkWidget *tool_bar = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		tool_bar = gw_tool_bar_create ( w);

		if ( (parent != NULL) && (tool_bar != NULL) )
		{
			gtk_box_pack_start ( GTK_BOX ( parent), tool_bar, FALSE, FALSE, 0);
		}
	}

	return tool_bar;
}

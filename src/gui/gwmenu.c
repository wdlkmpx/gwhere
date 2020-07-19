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
#include "gwmenu.h"

#include "gwmenufile.h"
#include "gwmenuaction.h"
#include "gwmenuoptions.h"
#include "gwmenuhelp.h"

#include "gwreferences.h"


/*! @define	GW_REF_MENU_BAR	The menu bar reference */
#define GW_REF_MENU_BAR "gw_menu_bar"


GtkWidget * gw_menu_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent)
{
	GtkWidget *menu_bar;
	GtkWidget *menu_file = NULL;
	GtkWidget *menu_action = NULL;
	GtkWidget *menu_options = NULL;
	GtkWidget *menu_help = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Menu */
	menu_bar = gtk_menu_bar_new ( );
	gtk_widget_ref ( menu_bar);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MENU_BAR, menu_bar, (GtkDestroyNotify) gtk_widget_unref);

	/* File menu */
	menu_file = gw_menu_file_create ( w, ag, menu_bar);
	gtk_container_add ( GTK_CONTAINER ( menu_bar), menu_file);

	/* Action menu */
	menu_action = gw_menu_action_create ( w, ag, menu_bar);
	gtk_container_add ( GTK_CONTAINER ( menu_bar), menu_action);

	/* Options menu */
	menu_options = gw_menu_options_create ( w, ag, menu_bar);
	gtk_container_add ( GTK_CONTAINER ( menu_bar), menu_options);

	/* Help menu */
	menu_help = gw_menu_help_create ( w, ag, menu_bar);
	gtk_menu_item_right_justify ( GTK_MENU_ITEM ( menu_help));
	gtk_container_add ( GTK_CONTAINER ( menu_bar), menu_help);

	return menu_bar;
}

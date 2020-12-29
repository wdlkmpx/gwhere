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


/*! @define	GW_REF_HANDLE_TOOL_BAR	The handle tool bar reference */
#define GW_REF_HANDLE_TOOL_BAR "gw_handle_tool_bar"
/*! @define	GW_REF_TOOL_BAR	The tool bar reference */
#define GW_REF_TOOL_BAR "gw_tool_bar"


GtkWidget * gw_tool_bar_create ( GtkWindow *w)
{
	GtkWidget *handle_box = NULL;
	GtkWidget *tool_bar;
	GtkWidget *pix_ico_new;
	GtkWidget *pix_ico_open;
	GtkWidget *pix_ico_save;
	GtkWidget *pix_ico_close;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	handle_box = gtk_handle_box_new ( );

	/* Stores the handle box reference */
	g_object_ref ( handle_box);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_HANDLE_TOOL_BAR, handle_box, (GDestroyNotify) g_object_unref);
	gtk_handle_box_set_shadow_type ( GTK_HANDLE_BOX ( handle_box), GTK_SHADOW_OUT);

	/* Should put defined ( OS_WIN32) because gtk_toolbar_new(void) is undefined?! */
	tool_bar = gtk_toolbar_new ( );

	/* Stores the tool bar box reference */
	g_object_ref ( tool_bar);
	g_object_set_data_full (G_OBJECT ( w), GW_REF_TOOL_BAR, tool_bar, (GDestroyNotify) g_object_unref);
	gtk_container_add ( GTK_CONTAINER ( handle_box), tool_bar);

	/* Loads icons for tool bar */
	icons_load_toolbar ( w);

	/* Adds all icons to the tool bar */
	pix_ico_new = gtk_pixmap_new ( PixNew, MskNew);
	gtk_toolbar_append_item ( GTK_TOOLBAR ( tool_bar), NULL,
	                         _( "New catalog"), NULL, pix_ico_new,  G_CALLBACK ( gw_menu_file_new_click), w);
	pix_ico_open = gtk_pixmap_new ( PixOpen, MskOpen);
	gtk_toolbar_append_item ( GTK_TOOLBAR ( tool_bar), NULL,
	                         _( "Open catalog"), NULL, pix_ico_open,  G_CALLBACK ( gw_menu_file_open_click), w);
	pix_ico_save = gtk_pixmap_new ( PixSave, MskSave);
	gtk_toolbar_append_item ( GTK_TOOLBAR ( tool_bar), NULL,
	                         _( "Save catalog"), NULL, pix_ico_save,  G_CALLBACK ( gw_menu_file_save_click), w);
	pix_ico_close = gtk_pixmap_new ( PixClose, MskClose);
	gtk_toolbar_append_item ( GTK_TOOLBAR ( tool_bar), NULL,
	                         _( "Close catalog"), NULL, pix_ico_close,  G_CALLBACK ( gw_menu_file_close_click), w);
	return handle_box;
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

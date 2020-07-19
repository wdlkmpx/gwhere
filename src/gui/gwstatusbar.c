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
#include "gwstatusbar.h"


/*! @define	GW_REF_STATUS_BAR_FIRST_STATUS	The first status reference */
#define GW_REF_STATUS_BAR_FIRST_STATUS "gw_ref_gw_status_bar_first_status"
/*! @define	GW_REF_STATUS_BAR_SECOND_STATUS	The second status reference */
#define GW_REF_STATUS_BAR_SECOND_STATUS "gw_ref_gw_status_bar_second_status"


GtkWidget * gw_status_bar_create ( GtkWindow *w)
{
	GtkWidget *gw_status_bar_box;
	GtkWidget *hbox;
	GtkWidget *status_bar1;
	GtkWidget *status_bar2;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	gw_status_bar_box = gtk_viewport_new ( NULL, NULL);
	gtk_viewport_set_shadow_type ( GTK_VIEWPORT ( gw_status_bar_box), GTK_SHADOW_NONE);

	hbox = gtk_hbox_new ( FALSE, 0);
	gtk_container_add ( GTK_CONTAINER ( gw_status_bar_box), hbox);

	/* First status bar */
	status_bar1 = gtk_statusbar_new ( );
	gtk_widget_ref ( status_bar1);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_STATUS_BAR_FIRST_STATUS, status_bar1, (GtkDestroyNotify) gtk_widget_unref);
	gtk_box_pack_start ( GTK_BOX ( hbox), status_bar1, FALSE, FALSE, 0);
	gtk_widget_set_usize ( status_bar1, 500, -2);

	/* Second status bar */
	status_bar2 = gtk_statusbar_new ( );
	gtk_widget_ref ( status_bar2);
	gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_STATUS_BAR_SECOND_STATUS, status_bar2, (GtkDestroyNotify) gtk_widget_unref);
	gtk_box_pack_start ( GTK_BOX ( hbox), status_bar2, TRUE, TRUE, 0);

	return gw_status_bar_box;
}


GtkWidget * gw_status_bar_create_and_add ( GtkWindow *w, GtkWidget *parent)
{
	GtkWidget *status_bar = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	status_bar = gw_status_bar_create ( w);

	if ( (parent != NULL) && (status_bar != NULL) )
	{
		gtk_box_pack_start ( GTK_BOX ( parent), status_bar, FALSE, FALSE, 0);
	}

	return status_bar;
}


GtkStatusbar * gw_status_bar_get_first_status ( GtkWindow *w)
{
	GtkStatusbar *status = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		status = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_STATUS_BAR_FIRST_STATUS);
	}

	return status;
}


GtkStatusbar * gw_status_bar_get_second_status ( GtkWindow *w)
{
	GtkStatusbar *status = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		status = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_STATUS_BAR_SECOND_STATUS);
	}

	return status;
}


gint gw_status_bar_put_messages ( GtkWindow *w, gchar *first_msg, gchar *second_msg)
{
	GtkStatusbar *status = NULL;
	guint context_id;
	gint result = -1;
	/* They are static in order to remove last messages before put new messages. */
	static guint message_id1 = 0;
	static guint message_id2 = 0;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : (%s;%s)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, first_msg, second_msg);
#endif

	if ( w != NULL )
	{
		if ( first_msg != NULL )
		{
			status = gw_status_bar_get_first_status ( w);
			context_id = gtk_statusbar_get_context_id ( status, "Working");
			if ( message_id1 != 0 )
			{
				gtk_statusbar_remove ( status, context_id, message_id1);
			}
			g_strdup_to_gtk_text ( first_msg, text_utf8);
			message_id1 = gtk_statusbar_push ( status, context_id, text_utf8);
			g_free ( text_utf8);
		}

		if ( second_msg != NULL )
		{
			status = gw_status_bar_get_second_status ( w);
			context_id = gtk_statusbar_get_context_id ( status, "Working");
			if ( message_id2 != 0 )
			{
				gtk_statusbar_remove ( status, context_id, message_id2);
			}
			g_strdup_to_gtk_text ( second_msg, text_utf8);
			message_id2 = gtk_statusbar_push ( status, context_id, text_utf8);
			g_free ( text_utf8);
		}

		result = 0;
	}

	return result;
}

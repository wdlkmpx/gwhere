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
#include "gwwindowboxabout.h"


/*! @define	GW_REF_WINDOW_ABOUT_LOGO_PIX	The logo pixmap */
#define GW_REF_WINDOW_ABOUT_LOGO_PIX "gw_ref_window_about_logo_pix"
/*! @define	GW_REF_WINDOW_ABOUT_LOGO_BIT	The logo bitmap */
#define GW_REF_WINDOW_ABOUT_LOGO_BIT "gw_ref_window_about_logo_bit"
/*! @define	GW_REF_WINDOW_ABOUT_EVENT_BOX	The event box */
#define GW_REF_WINDOW_ABOUT_EVENT_BOX "gw_ref_window_about_event_box"
/*! @define	GW_REF_WINDOW_ABOUT_VBOX	The main vertical box */
#define GW_REF_WINDOW_ABOUT_VBOX "gw_ref_window_about_vbox"
/*! @define	GW_REF_WINDOW_ABOUT_TEXT	The about text */
#define GW_REF_WINDOW_ABOUT_TEXT "gw_ref_window_about_text"


/* XPM : GWhere logo */
static char *GWhere_logo_xpm[] = {
"70 46 3 1",
". c #669999",
"# c #ff9900",
"  c None",
"                                   ...                                ",
"                         ......................                       ",
"                      .............................                   ",
"                  .................   .................               ",
"                ..........                     ..........             ",
"              ........                             ........           ",
"            .......                                   .......         ",
"           .....                                        ......        ",
"         ......                                           ......      ",
"        .....                                               .....     ",
"       ....                                                  .....    ",
"      ....                                                     ....   ",
"     ....                                                       ....  ",
"    ....                                                         .... ",
"   ....                                                           ....",
"   ...                                                             ...",
"  ...                                                                 ",
"  ...                                                                 ",
" ...                                                                  ",
" ...                  ##   ###   ## ##     #  ####### #######  #######",
" ...                  ##   ###   ## ##     # ##       #     ## #      ",
"...                    #   ###   #  ##     # ##       #     ## #      ",
"...                    ##  # #  ##  ##     # ##       #     ## #      ",
"...                    ## ## ## ##  ######## #######  # #####  #######",
"...                    ## ## ## ##  ######## ##       ######   #      ",
"...                     # ## ## #   ##     # ##       # ##     #      ",
" ..                     ####  ###   ##     # ##       #  ##    #      ",
" ...                    ###   ###   ##     # ##       #   ##   ##     ",
" ...                     ##   ###   ##     #  ######  #    ##   ######",
"  ...                                                                 ",
"  ...                   ..............................................",
"   ...                  ..............................................",
"   ....                                                           ....",
"    ....                                                         .... ",
"     ....                                                       ....  ",
"      ....                                                     ....   ",
"       ....                                                  .....    ",
"        .....                                               .....     ",
"         ......                                           ......      ",
"           ......                                       ......        ",
"            .......                                   ......          ",
"              ........                             .......            ",
"                ..........                     .........              ",
"                  .................   .................               ",
"                      .............................                   ",
"                         ......................                       "};


GtkWidget * gw_window_box_about_create ( GtkWindow *window)
{
        /* This window must be single, this property shouldn't be changed */
        static GtkWidget *w = NULL;
        GdkColor transparent = {0};
        GtkWidget *vbox_about = NULL;
        GtkWidget *label = NULL;
        GtkWidget *event_box = NULL;
        GtkWidget *logo = NULL;
	GdkPixmap *pix_gw_logo = NULL;
	GdkBitmap *msk_gw_logo = NULL;
        gchar * text = NULL;
        gchar * text_utf8 = NULL;
        GdkCursor *cursor = NULL;
        gchar * os_version = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
        g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

        if ( !w )
        {
	        /* GWhere logo loading */
	        pix_gw_logo = gdk_pixmap_create_from_xpm_d ( GTK_WIDGET ( window)->window, &msk_gw_logo, &transparent, GWhere_logo_xpm);

                w = gtk_window_new ( GTK_WINDOW_TOPLEVEL);

                gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
                gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
                gtk_window_set_position ( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
                g_strdup_to_gtk_text ( _( "About"), text_utf8);
                gtk_window_set_title ( GTK_WINDOW ( w), text_utf8);
                g_free ( text_utf8);

                gtk_signal_connect ( GTK_OBJECT ( w), "destroy", GTK_SIGNAL_FUNC ( gw_window_box_about_destroy), &w);
                gtk_signal_connect ( GTK_OBJECT ( w), "delete-event", GTK_SIGNAL_FUNC ( gtk_widget_destroy), NULL);

		/* See more bottom the call of gdk_pixmap_unref() and gdk_bitmap_unref().
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_WINDOW_ABOUT_LOGO_PIX, pix_gw_logo, ( GtkDestroyNotify)gdk_pixmap_unref);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_WINDOW_ABOUT_LOGO_BIT, msk_gw_logo, ( GtkDestroyNotify)gdk_bitmap_unref);
		*/

                gtk_container_set_border_width ( GTK_CONTAINER ( w), 5);
                gtk_widget_set_usize ( w, 360, 340);

                event_box = gtk_event_box_new ( );
                gtk_container_add ( GTK_CONTAINER ( w), event_box);

                vbox_about = gtk_vbox_new ( FALSE, 0);
                gtk_container_add ( GTK_CONTAINER ( event_box), vbox_about);

                logo = gtk_pixmap_new ( pix_gw_logo, msk_gw_logo);
		gdk_pixmap_unref ( pix_gw_logo);
		gdk_bitmap_unref ( msk_gw_logo);
                gtk_container_add ( GTK_CONTAINER ( vbox_about), logo);

		/* Doesn't encode to UTF-8 substring because the result string will be encoded. */
		gw_os_get_version_str ( &os_version);
                text = g_strconcat ( PROJECT_NAME,
                                "-",
                                VERSION,
                                _( "\nRemovable media catalog managment\nBy Sebastien LECACHEUR\n\nzero@gwhere.org\nhttp://www.gwhere.org\n"),
                                _( "GWhere allows to manage a database of yours CDs and others removable media (hard disks, floppy drive, Zip drive, CD- ROM, etc...). With GWhere it's easy to browse yours CDs or to make quick search without need to insert yours CDs in the drive at each once."),
                                _( "\n\nRuns under "),
                                os_version,
                                NULL);
                if ( os_version != NULL )
                {
                	g_free ( os_version);
                }

		g_strdup_to_gtk_text ( text, text_utf8);
                g_free ( text);

                label = gtk_label_new ( text_utf8);
                g_free ( text_utf8);
                gtk_label_set_justify ( GTK_LABEL ( label), GTK_JUSTIFY_FILL);
                gtk_label_set_line_wrap ( GTK_LABEL ( label), TRUE);
                gtk_container_add ( GTK_CONTAINER ( vbox_about), label);

		/* Should it be mandatory? Yes, in order to get the good window size
		   to displaying all informations. */
		gtk_widget_set_usize ( label, 330, 280);

		gtk_widget_set_events ( event_box, GDK_BUTTON_PRESS_MASK);
		gtk_signal_connect_object ( GTK_OBJECT ( event_box), "button_press_event", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));

		if ( (cursor = gdk_cursor_new ( GDK_HAND2)) != NULL)
		{
	                /* Fix bug : event_box->window is NULL with GTK-2.0. */
			if ( GTK_WIDGET ( event_box)->window != NULL )
			{
                		gdk_window_set_cursor ( GTK_WIDGET ( event_box)->window, cursor);
#ifdef HAVE_GTK20
                		gdk_cursor_unref ( cursor);
#endif
                	}
                	else
                	{
#ifdef GW_DEBUG_GUI_COMPONENT
                		g_warning ( "gtk_event_box->window is NULL!!");
#endif
                		gdk_cursor_destroy ( cursor);
                	}
                }
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

		g_warning ( "gw_window_box_about is already displayed!! Destroying it...");

                gtk_widget_destroy ( w);
        }

        return w;
}


gint gw_window_box_about_destroy ( GtkWindow *w, GtkWidget **self_window)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
                g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && ( self_window != NULL) )
	{
		gtk_widget_destroyed ( GTK_WIDGET ( w), self_window);

		result = 0;
	}

	return result;
}

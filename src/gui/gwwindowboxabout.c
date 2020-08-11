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

/* XPM : GWhere logo */
static const char * GWhere_logo_xpm[] = {
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
    GtkWidget *w = NULL;

    const gchar * authors[] =
    {
        "Sebastien LECACHEUR <zero@gwhere.org>",
        NULL
    };
    /* TRANSLATORS: Replace this string with your names, one name per line. */
    gchar * translators = _("Translated by");

    GdkPixbuf * logo = gdk_pixbuf_new_from_xpm_data (GWhere_logo_xpm);

    /* Create and initialize the dialog. */
    w = g_object_new (GTK_TYPE_ABOUT_DIALOG,
                      "version",      VERSION,
                      "program-name", PROJECT_NAME,
                      "copyright",    "Copyright (C) 2000-2020",
                      "comments",     _("Removable media catalog management\nGWhere allows to manage a database of yours CDs and other removable media (hard disks, etc...)."),
                      "license",      "This program is free software; you can redistribute it and/or\nmodify it under the terms of the GNU General Public License\nas published by the Free Software Foundation; either version 2\nof the License, or (at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\nGNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program; if not, write to the Free Software\nFoundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.",
                      "website",      "http://www.gwhere.org",
                      "authors",      authors,
                      "translator-credits", translators,
                      "logo",         logo,
                      NULL);
    gtk_container_set_border_width (GTK_CONTAINER (w), 2);
    gtk_window_set_transient_for (GTK_WINDOW (w), window);
    gtk_window_set_modal (GTK_WINDOW (w), TRUE);
    gtk_window_set_position (GTK_WINDOW (w), GTK_WIN_POS_CENTER_ON_PARENT);

    /* Display the dialog, wait for the user to close it, then destroy it. */
    gtk_dialog_run (GTK_DIALOG (w));
    gtk_widget_destroy (w);

    return (w);
}


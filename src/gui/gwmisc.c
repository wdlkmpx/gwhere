/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 */

#include "../gwsupport.h"
#include "gwmisc.h"


void gw_msg_box_create (GtkWindow *window, gchar *title, gchar *subject)
{
   GtkWidget * w;
   w = gtk_message_dialog_new (window,
                               GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                               GTK_MESSAGE_OTHER,
                               GTK_BUTTONS_OK,
                               "%s", subject);
   gtk_window_set_title (GTK_WINDOW (w), title);
   g_signal_connect_swapped (w, "response", G_CALLBACK (gtk_widget_destroy), w);
   gtk_widget_show (w);
}

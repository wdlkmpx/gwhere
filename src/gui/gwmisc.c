/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 */

#include "../gwsupport.h"
#include "gwmisc.h"
#include "../gwguimanager.h"


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



void gw_file_chooser_box_create (gchar *title, gchar *filename,
                                 GCallback ok, GCallback cancel)
{
   GtkWidget * w;
   GtkWindow * parent_window;
   GtkWidget * button_ok, * button_c;
   GtkFileChooserAction action;
   char current_dir[256];
   getcwd (current_dir, sizeof(current_dir));

   parent_window = gw_gui_manager_main_interface_get_main_window ( );

   if (filename) {
      action = GTK_FILE_CHOOSER_ACTION_SAVE;
   } else {
      action = GTK_FILE_CHOOSER_ACTION_OPEN;
   }

   w = gtk_file_chooser_dialog_new (title,
                                    parent_window,
                                    action,
                                    NULL, NULL);
   gtk_window_set_position (GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
   gtk_widget_set_size_request (GTK_WIDGET (w), 640, 480);
   gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (w), TRUE);
   gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (w), current_dir);

   if (filename) {
      gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (w), filename);
   }

   button_ok = gtk_dialog_add_button (GTK_DIALOG (w), "gtk-ok", GTK_RESPONSE_OK);
   button_c  = gtk_dialog_add_button (GTK_DIALOG (w), "gtk-cancel", GTK_RESPONSE_CANCEL);
   if (ok) {
      g_signal_connect (button_ok, "clicked", G_CALLBACK (ok), w);
   }
   if (cancel) {
      g_signal_connect (button_c, "clicked", G_CALLBACK (cancel), w);
   } else {
      g_signal_connect_swapped (button_c, "clicked", G_CALLBACK (gtk_widget_destroy), w);
   }

   gtk_widget_show (w);
}




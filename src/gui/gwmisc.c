/*
 * This is free and unencumbered software released into the public domain.
 *
 * For more information, please refer to <https://unlicense.org>
 */

#include "../gwsupport.h"
#include "gwmisc.h"
#include "../gwguimanager.h"

typedef struct gw_box_data
{
   GtkWidget * dialog;
   GtkWidget * entry;
   void (*ok_func) (void *,void *);
} gw_box_data;

// input_box
static void input_box_response_cb (GtkDialog * dlg, int response, gpointer user_data);
static void input_box_entry_activate_cb (GtkEntry * entry, gpointer user_data);


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


/***********************************************
 *            Input Box
 */

static void input_box_response_cb (GtkDialog * dlg, int response, gpointer user_data)
{
   gw_box_data * ddata = (gw_box_data *) user_data;
   if (response == GTK_RESPONSE_OK)
   {
      char * entry_text = NULL;
      if (ddata->entry) {
         entry_text = g_strdup (gtk_entry_get_text (GTK_ENTRY (ddata->entry)));
      }
      if (!*entry_text) {
         g_signal_stop_emission_by_name (dlg, "response");
         gw_msg_box_create (GTK_WINDOW (dlg), NULL, "Please enter text...");
         g_free (entry_text);
         return;
      }

      // destroy dialog before calling func
      gtk_widget_destroy (GTK_WIDGET (dlg));

      if (ddata->ok_func) {
         ddata->ok_func (dlg, entry_text);
      }
      g_free (entry_text);
   } else {
      gtk_widget_destroy (GTK_WIDGET (dlg));
   }

   g_free (ddata);
}


static void input_box_entry_activate_cb (GtkEntry * entry, gpointer user_data)
{
   gw_box_data * ddata = (gw_box_data *) user_data;
   gtk_dialog_response (GTK_DIALOG (ddata->dialog), GTK_RESPONSE_OK);
}


void gw_input_box (GtkWindow *window, gchar *title, gchar *subject,
                   gchar *text, gpointer ok)
{
   GtkWidget * w = NULL;
   GtkWidget * vbox, * frame, * text_entry;
   gw_box_data * ddata = g_malloc0 (sizeof (gw_box_data));

   w = gtk_dialog_new ();
   gtk_window_set_policy (GTK_WINDOW (w), FALSE, FALSE, TRUE);
   gtk_window_set_title (GTK_WINDOW (w), title);
   gtk_container_set_border_width (GTK_CONTAINER (w), 5);

   gtk_window_set_modal (GTK_WINDOW (w),TRUE);
   gtk_window_set_transient_for (GTK_WINDOW (w), window);
   gtk_window_set_position (GTK_WINDOW (w), GTK_WIN_POS_CENTER);

   vbox = gtk_dialog_get_content_area (GTK_DIALOG (w));
   gtk_box_set_spacing (GTK_BOX (vbox), 6);
   gtk_container_set_border_width (GTK_CONTAINER (vbox), 0);

   if (subject) {
      frame = gtk_frame_new (subject);
      gtk_box_pack_start (GTK_BOX (vbox), frame, TRUE, TRUE, 0);
      vbox = gtk_vbox_new (FALSE, 0);
      gtk_container_add (GTK_CONTAINER (frame), vbox);
      gtk_container_set_border_width (GTK_CONTAINER (vbox), 8);
   }

   text_entry = gtk_entry_new ();
   gtk_entry_set_max_length (GTK_ENTRY (text_entry), 300);
   gtk_entry_set_text (GTK_ENTRY (text_entry), text);
   gtk_box_pack_start (GTK_BOX (vbox), text_entry, TRUE, TRUE, 0);
   gtk_editable_select_region (GTK_EDITABLE (text_entry), 0, -1);

   gtk_dialog_add_button (GTK_DIALOG (w), _("_OK"), GTK_RESPONSE_OK);
   gtk_dialog_add_button (GTK_DIALOG (w), _("_Cancel"), GTK_RESPONSE_CANCEL);

   ddata->dialog  = w;
   ddata->entry   = text_entry;
   ddata->ok_func = ok;

   g_signal_connect (w, "response", G_CALLBACK (input_box_response_cb), ddata);
   g_signal_connect (text_entry, "activate",
                     G_CALLBACK (input_box_entry_activate_cb), ddata);

   gtk_widget_show_all (w);
}

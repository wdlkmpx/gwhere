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
#include "gwwindowboxmail.h"

#include "gtktextarea.h"

#include "gwwindowboxmailcallback.h"


/*! @define	GW_REF_MAIL_WINDOW_BOX_PARENT_WINDOW	The parent window */
#define GW_REF_MAIL_WINDOW_BOX_PARENT_WINDOW "gw_ref_mail_window_box_parent_window"
/*! @define	GW_REF_MAIL_WINDOW_BOX_TO_ENTRY	The send to entry */
#define GW_REF_MAIL_WINDOW_BOX_TO_ENTRY "gw_ref_mail_window_box_to_entry"
/*! @define	GW_REF_MAIL_WINDOW_BOX_CC_ENTRY	The send CC entry */
#define GW_REF_MAIL_WINDOW_BOX_CC_ENTRY "gw_ref_mail_window_box_cc_entry"
/*! @define	GW_REF_MAIL_WINDOW_BOX_BCC_ENTRY	The send BCC entry */
#define GW_REF_MAIL_WINDOW_BOX_BCC_ENTRY "gw_ref_mail_window_box_bcc_entry"
/*! @define	GW_REF_MAIL_WINDOW_BOX_OBJECT_ENTRY	The mail object entry */
#define GW_REF_MAIL_WINDOW_BOX_OBJECT_ENTRY "gw_ref_mail_window_box_object_entry"
/*! @define	GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK	The checkbox to know if attach file */
#define GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK "gw_ref_mail_window_box_attach_file_chk"
/*! @define	GW_REF_MAIL_WINDOW_BOX_MESSAGE_TEXT_AREA	The message text of the mail */
#define GW_REF_MAIL_WINDOW_BOX_MESSAGE_TEXT_AREA "gw_ref_mail_window_box_message_text_area"


GtkWindow * gw_mail_window_box_create ( GtkWindow *window, gchar *file_name)
{
	/* This window must be single, this property may be changed */
	static GtkWidget *w = NULL;
	GtkWidget *vbMailWindowsBox;
	GtkWidget *tblSendOptions;
	GtkWidget *lblTo;
	GtkWidget *lblCC;
	GtkWidget *lblBCC;
	GtkWidget *lblObject;
	GtkWidget *entTo;
	GtkWidget *entCC;
	GtkWidget *entBCC;
	GtkWidget *entObject;
	GtkWidget *lblAttachedFile;
	GtkWidget *chkBtnAttachedFile;
	GtkWidget *scrTextMail;
	GtkWidget *txtMail;
	GtkWidget *hbSendMailControl;
	GtkWidget *btnCancel;
	GtkWidget *btnSend;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( !w )
	{
		w = gtk_window_new ( GTK_WINDOW_TOPLEVEL);
		gtk_widget_set_tooltip_text (GTK_WIDGET ( w),
		                             _( "This window box allows you to send a catalog by mail to one (or more) of yours contacts."));
		gtk_window_set_title ( GTK_WINDOW ( w), _( "Send mail"));

		gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
		gtk_window_set_position (GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
		gtk_widget_set_size_request ( w, 400, 300);
		g_signal_connect (G_OBJECT ( w), "destroy", G_CALLBACK ( gtk_widget_destroyed), &w);

		/* Store parent window reference */
		g_object_ref ( GTK_WIDGET ( window));
		g_object_set_data_full (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_PARENT_WINDOW, window, ( GDestroyNotify) g_object_unref);

		vbMailWindowsBox = gtk_vbox_new ( FALSE, 5);
		gtk_container_add ( GTK_CONTAINER ( w), vbMailWindowsBox);
		gtk_container_set_border_width ( GTK_CONTAINER ( vbMailWindowsBox), 5);

		tblSendOptions = gtk_table_new ( 5, 2, FALSE);
		gtk_box_pack_start ( GTK_BOX ( vbMailWindowsBox), tblSendOptions, FALSE, TRUE, 0);
		gtk_table_set_row_spacings ( GTK_TABLE ( tblSendOptions), 5);
		gtk_table_set_col_spacings ( GTK_TABLE ( tblSendOptions), 5);


		lblTo = gtk_label_new ( _( "To :"));
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblTo, 0, 1, 0, 1, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblTo), 0, 0.5);

		lblCC = gtk_label_new ( _( "CC :"));
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblCC, 0, 1, 1, 2, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblCC), 0, 0.5);

		lblBCC = gtk_label_new ( _( "BCC :"));
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblBCC, 0, 1, 2, 3, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblBCC), 0, 0.5);

		lblObject = gtk_label_new ( _( "Subject :"));
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblObject, 0, 1, 3, 4,(GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblObject), 0, 0.5);

		entTo = gtk_entry_new ( );
		g_object_ref ( entTo);
		g_object_set_data_full (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_TO_ENTRY, entTo,(GDestroyNotify) g_object_unref);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), entTo, 1, 2, 0, 1,(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_widget_set_tooltip_text (entTo,
		                             _( "Enter here the email address of your(s) contact(s)."));

		entCC = gtk_entry_new ( );
		g_object_ref ( entCC);
		g_object_set_data_full (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_CC_ENTRY, entCC,(GDestroyNotify) g_object_unref);
		gtk_table_attach (GTK_TABLE (tblSendOptions), entCC, 1, 2, 1, 2,(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),(GtkAttachOptions) ( 0), 0, 0);
		gtk_widget_set_tooltip_text (entCC,
		                             _( "Enter here the email address of the copied mail contacts."));

		entBCC = gtk_entry_new ( );
		g_object_ref ( entBCC);
		g_object_set_data_full (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_BCC_ENTRY, entBCC, (GDestroyNotify) g_object_unref);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), entBCC, 1, 2, 2, 3, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_widget_set_tooltip_text (entBCC,
		                             _( "Enter here the email address of the hidden copied mail contacts."));

		entObject = gtk_entry_new ( );
		g_object_ref ( entObject);
		g_object_set_data_full (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_OBJECT_ENTRY, entObject, (GDestroyNotify) g_object_unref);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), entObject, 1, 2, 3, 4, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_widget_set_tooltip_text (entObject, _( "Enter here the object of your mail."));

		lblAttachedFile = gtk_label_new ( _( "Attached file :"));
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblAttachedFile, 0, 1, 4, 5, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblAttachedFile), 0, 0.5);

		if ( file_name != NULL )
		{
			chkBtnAttachedFile = gtk_check_button_new_with_label ( file_name);
			g_object_ref ( chkBtnAttachedFile);
			g_object_set_data_full (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK, chkBtnAttachedFile, (GDestroyNotify) g_object_unref);
			gtk_table_attach ( GTK_TABLE ( tblSendOptions), chkBtnAttachedFile, 1, 2, 4, 5, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
			gtk_widget_set_tooltip_text (chkBtnAttachedFile,
			                             _( "Choose to attach or no the catalog file."));
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chkBtnAttachedFile), TRUE);
		}

		scrTextMail = gtk_scrolled_window_new ( NULL, NULL);
		gtk_box_pack_start ( GTK_BOX ( vbMailWindowsBox), scrTextMail, TRUE, TRUE, 0);
		gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrTextMail), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		txtMail = gtk_text_area_new ( );
		g_object_ref ( txtMail);
		g_object_set_data_full (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_MESSAGE_TEXT_AREA, txtMail, (GDestroyNotify) g_object_unref);
		gtk_text_area_set_editable ( GTK_TEXT_AREA ( txtMail), TRUE);
		gtk_container_add ( GTK_CONTAINER ( scrTextMail), txtMail);
		gtk_widget_set_tooltip_text (txtMail,
		                             _( "Type here the text for the mail message."));

		/* The Send/Cancel button area */
		hbSendMailControl = gtk_hbutton_box_new ( );
		gtk_button_box_set_layout ( GTK_BUTTON_BOX ( hbSendMailControl), GTK_BUTTONBOX_END);
		gtk_box_set_spacing (GTK_BOX ( hbSendMailControl), 5);
		gtk_box_pack_end ( GTK_BOX ( vbMailWindowsBox), hbSendMailControl, FALSE, FALSE, 0);

		btnSend = gtk_button_new_with_mnemonic (_("_Send"));
		gtk_box_pack_start ( GTK_BOX ( hbSendMailControl), btnSend, FALSE, TRUE, 0);
		gtk_widget_set_tooltip_text (btnSend,
		                             _( "Click here to send a mail (with an attached catalog)."));
		g_signal_connect (G_OBJECT ( btnSend), "clicked", G_CALLBACK ( gw_mail_window_box_send_click), GTK_WINDOW ( w));

		btnCancel = gtk_button_new_with_label (_("_Cancel"));
		gtk_box_pack_start ( GTK_BOX ( hbSendMailControl), btnCancel, TRUE, TRUE, 0);
		GTK_WIDGET_UNSET_FLAGS ( btnCancel, GTK_CAN_FOCUS);
		gtk_widget_set_tooltip_text (btnCancel,
		                             _( "Click here to cancel the send of a mail."));
		g_signal_connect_swapped (G_OBJECT ( btnCancel), "clicked", G_CALLBACK ( gtk_widget_destroy), GTK_OBJECT ( w));
	}

	if ( !gtk_widget_get_visible ( w) )
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

		gtk_widget_destroy ( w);
	}

	return GTK_WINDOW ( w);
}


GtkWindow * gw_mail_window_box_get_main_window ( GtkWindow *w)
{
	GtkWidget *parent = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		parent = g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_PARENT_WINDOW);
	}

	if ( parent == NULL )
	{
#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : parent window is null\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return GTK_WINDOW ( parent);
}


gchar * gw_mail_window_box_get_to ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (entry = GTK_ENTRY ( g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_TO_ENTRY))) != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), text);
		}

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : to field = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif
	}

	return text;
}


gchar * gw_mail_window_box_get_cc ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (entry = GTK_ENTRY ( g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_CC_ENTRY))) != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), text);
		}

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : cc field = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif
	}

	return text;
}


gchar * gw_mail_window_box_get_bcc ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (entry = GTK_ENTRY ( g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_BCC_ENTRY))) != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), text);
		}

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : bcc field = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif
	}

	return text;
}


gchar * gw_mail_window_box_get_subject ( GtkWindow *w)
{
	GtkEntry *entry = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (entry = GTK_ENTRY ( g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_OBJECT_ENTRY))) != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( entry), text);
		}

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : object field = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif
	}

	return text;
}


gboolean gw_mail_window_box_get_option_attach_file ( GtkWindow *w)
{
	GtkToggleButton *chk = NULL;
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (chk = g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK)) != NULL )
		{
			result = gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk));
		}
	}

	return result;
}


gchar * gw_mail_window_box_get_file_path ( GtkWindow *w)
{
	GtkCheckButton *chk_button = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		chk_button = g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK);

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print ( "*** GW - %s (%d) :: %s() : file path = %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, text);
#endif

		if ( chk_button != NULL )
		{
			gtk_label_get ( GTK_LABEL ( GTK_BIN ( GTK_BUTTON ( chk_button))->child), &text);
			g_strdup_from_gtk_text ( text, text);
		}
	}

	return text;
}


gchar * gw_mail_window_box_get_msg ( GtkWindow *w)
{
	GtkTextArea *text_area = NULL;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (text_area = g_object_get_data (G_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_MESSAGE_TEXT_AREA)) != NULL )
		{
			text = gtk_text_area_get_text ( GTK_TEXT_AREA ( text_area));
		}
	}

	return text;
}

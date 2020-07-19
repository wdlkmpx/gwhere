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
	guint btnCancel_key;
	GtkWidget *btnCancel;
	guint btnSend_key;
	GtkWidget *btnSend;
	GtkAccelGroup *accel_group;
	GtkTooltips *tooltips;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Inits the tooltips group. */
	tooltips = gtk_tooltips_new ( );

	/* Init an accel group for shortcuts */
	accel_group = gtk_accel_group_new ( );

	if ( !w )
	{
		w = gtk_window_new ( GTK_WINDOW_TOPLEVEL);
		g_strdup_to_gtk_text ( _( "This window box allows you to send a catalog by mail to one (or more) of yours contacts."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, GTK_WIDGET ( w), text_utf8, NULL);
		g_free ( text_utf8);
		g_strdup_to_gtk_text ( _( "Send mail"), text_utf8);
		gtk_window_set_title ( GTK_WINDOW ( w), text_utf8);
		g_free ( text_utf8);

		gtk_window_set_modal ( GTK_WINDOW ( w), TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w), window);
		gtk_window_set_position (GTK_WINDOW ( w), GTK_WIN_POS_CENTER);
		gtk_widget_set_usize ( w, 400, 300);
		gtk_signal_connect ( GTK_OBJECT ( w), "destroy", GTK_SIGNAL_FUNC ( gtk_widget_destroyed), &w);

		/* Store parent window reference */
		gtk_widget_ref ( GTK_WIDGET ( window));
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_PARENT_WINDOW, window, ( GtkDestroyNotify) gtk_widget_unref);

		vbMailWindowsBox = gtk_vbox_new ( FALSE, 5);
		gtk_container_add ( GTK_CONTAINER ( w), vbMailWindowsBox);
		gtk_container_set_border_width ( GTK_CONTAINER ( vbMailWindowsBox), 5);

		tblSendOptions = gtk_table_new ( 5, 2, FALSE);
		gtk_box_pack_start ( GTK_BOX ( vbMailWindowsBox), tblSendOptions, FALSE, TRUE, 0);
		gtk_table_set_row_spacings ( GTK_TABLE ( tblSendOptions), 5);
		gtk_table_set_col_spacings ( GTK_TABLE ( tblSendOptions), 5);


		g_strdup_to_gtk_text ( _( "To :"), text_utf8);
		lblTo = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblTo, 0, 1, 0, 1, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblTo), 0, 0.5);

		g_strdup_to_gtk_text ( _( "CC :"), text_utf8);
		lblCC = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblCC, 0, 1, 1, 2, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblCC), 0, 0.5);

		g_strdup_to_gtk_text ( _( "BCC :"), text_utf8);
		lblBCC = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblBCC, 0, 1, 2, 3, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblBCC), 0, 0.5);

		g_strdup_to_gtk_text ( _( "Subject :"), text_utf8);
		lblObject = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblObject, 0, 1, 3, 4,(GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblObject), 0, 0.5);

		entTo = gtk_entry_new ( );
		gtk_widget_ref ( entTo);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_TO_ENTRY, entTo,(GtkDestroyNotify) gtk_widget_unref);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), entTo, 1, 2, 0, 1,(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		g_strdup_to_gtk_text ( _( "Enter here the email address of your(s) contact(s)."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, entTo, text_utf8, NULL);
		g_free ( text_utf8);

		entCC = gtk_entry_new ( );
		gtk_widget_ref ( entCC);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_CC_ENTRY, entCC,(GtkDestroyNotify) gtk_widget_unref);
		gtk_table_attach (GTK_TABLE (tblSendOptions), entCC, 1, 2, 1, 2,(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),(GtkAttachOptions) ( 0), 0, 0);
		g_strdup_to_gtk_text ( _( "Enter here the email address of the copied mail contacts."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, entCC, text_utf8, NULL);
		g_free ( text_utf8);

		entBCC = gtk_entry_new ( );
		gtk_widget_ref ( entBCC);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_BCC_ENTRY, entBCC, (GtkDestroyNotify) gtk_widget_unref);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), entBCC, 1, 2, 2, 3, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		g_strdup_to_gtk_text ( _( "Enter here the email address of the hidden copied mail contacts."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, entBCC, text_utf8, NULL);
		g_free ( text_utf8);

		entObject = gtk_entry_new ( );
		gtk_widget_ref ( entObject);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_OBJECT_ENTRY, entObject, (GtkDestroyNotify) gtk_widget_unref);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), entObject, 1, 2, 3, 4, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		g_strdup_to_gtk_text ( _( "Enter here the object of your mail."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, entObject, text_utf8, NULL);
		g_free ( text_utf8);

		g_strdup_to_gtk_text ( _( "Attached file :"), text_utf8);
		lblAttachedFile = gtk_label_new ( text_utf8);
		g_free ( text_utf8);
		gtk_table_attach ( GTK_TABLE ( tblSendOptions), lblAttachedFile, 0, 1, 4, 5, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
		gtk_misc_set_alignment ( GTK_MISC ( lblAttachedFile), 0, 0.5);

		if ( file_name != NULL )
		{
			g_strdup_to_gtk_text ( file_name, text_utf8);
			chkBtnAttachedFile = gtk_check_button_new_with_label ( text_utf8);
			g_free ( text_utf8);
			gtk_widget_ref ( chkBtnAttachedFile);
			gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK, chkBtnAttachedFile, (GtkDestroyNotify) gtk_widget_unref);
			gtk_table_attach ( GTK_TABLE ( tblSendOptions), chkBtnAttachedFile, 1, 2, 4, 5, (GtkAttachOptions) (GTK_FILL), (GtkAttachOptions) ( 0), 0, 0);
			g_strdup_to_gtk_text ( _( "Choose to attach or no the catalog file."), text_utf8);
			gtk_tooltips_set_tip ( tooltips, chkBtnAttachedFile, text_utf8, NULL);
			g_free ( text_utf8);
			gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( chkBtnAttachedFile), TRUE);
		}

		scrTextMail = gtk_scrolled_window_new ( NULL, NULL);
		gtk_box_pack_start ( GTK_BOX ( vbMailWindowsBox), scrTextMail, TRUE, TRUE, 0);
		gtk_scrolled_window_set_policy ( GTK_SCROLLED_WINDOW ( scrTextMail), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

		txtMail = gtk_text_area_new ( );
		gtk_widget_ref ( txtMail);
		gtk_object_set_data_full ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_MESSAGE_TEXT_AREA, txtMail, (GtkDestroyNotify) gtk_widget_unref);
		gtk_text_area_set_editable ( GTK_TEXT_AREA ( txtMail), TRUE);
		gtk_container_add ( GTK_CONTAINER ( scrTextMail), txtMail);
		g_strdup_to_gtk_text ( _( "Type here the text for the mail message."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, txtMail, text_utf8, NULL);
		g_free ( text_utf8);

		/* The Send/Cancel button area */
		hbSendMailControl = gtk_hbutton_box_new ( );
		gtk_button_box_set_layout ( GTK_BUTTON_BOX ( hbSendMailControl), GTK_BUTTONBOX_END);
		gtk_button_box_set_spacing ( GTK_BUTTON_BOX ( hbSendMailControl), 5);
		gtk_box_pack_end ( GTK_BOX ( vbMailWindowsBox), hbSendMailControl, FALSE, FALSE, 0);

		btnSend = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_Send"), text_utf8);
		btnSend_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( btnSend)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( btnSend, "clicked", accel_group, btnSend_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);
		gtk_box_pack_start ( GTK_BOX ( hbSendMailControl), btnSend, FALSE, TRUE, 0);
		g_strdup_to_gtk_text ( _( "Click here to send a mail (with an attached catalog)."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, btnSend, text_utf8, NULL);
		g_free ( text_utf8);
		gtk_signal_connect ( GTK_OBJECT ( btnSend), "clicked", GTK_SIGNAL_FUNC ( gw_mail_window_box_send_click), GTK_WINDOW ( w));

		btnCancel = gtk_button_new_with_label ( "");
		g_strdup_to_gtk_text ( _( "_Cancel"), text_utf8);
		btnCancel_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( btnCancel)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( btnCancel, "clicked", accel_group, btnCancel_key, GDK_MOD1_MASK, (GtkAccelFlags) 0);
		gtk_box_pack_start ( GTK_BOX ( hbSendMailControl), btnCancel, TRUE, TRUE, 0);
		GTK_WIDGET_UNSET_FLAGS ( btnCancel, GTK_CAN_FOCUS);
		g_strdup_to_gtk_text ( _( "Click here to cancel the send of a mail."), text_utf8);
		gtk_tooltips_set_tip ( tooltips, btnCancel, text_utf8, NULL);
		gtk_signal_connect_object ( GTK_OBJECT ( btnCancel), "clicked", GTK_SIGNAL_FUNC ( gtk_widget_destroy), GTK_OBJECT ( w));
		g_free ( text_utf8);

		gtk_window_add_accel_group ( GTK_WINDOW ( w), accel_group);
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
		parent = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_PARENT_WINDOW);
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
		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_TO_ENTRY))) != NULL )
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
		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_CC_ENTRY))) != NULL )
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
		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_BCC_ENTRY))) != NULL )
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
		if ( (entry = GTK_ENTRY ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_OBJECT_ENTRY))) != NULL )
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
		if ( (chk = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK)) != NULL )
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
		chk_button = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_ATTACH_FILE_CHK);

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
		if ( (text_area = gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_MAIL_WINDOW_BOX_MESSAGE_TEXT_AREA)) != NULL )
		{
			text = gtk_text_area_get_text ( GTK_TEXT_AREA ( text_area));
		}
	}

	return text;
}

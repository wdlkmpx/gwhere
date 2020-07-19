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
#include "gwwindowboxmailcallback.h"

#include "gwwindowboxmail.h"
#include "gwmsgbox.h"
#include "gwprogressbarbox.h"

#include "../gwapplicationmanager.h"
#include "../gwguimanager.h"


gboolean gw_mail_window_box_send_click ( GtkWidget *bt, GtkWindow *w)
{
	gboolean result = FALSE;
	GWMail *mail = NULL;
	GtkWindow *msg_box = NULL;


	if ( w != NULL )
	{
		if ( (mail = (GWMail*)g_malloc ( sizeof ( GWMail))) != NULL)
		{
			mail->to = gw_mail_window_box_get_to ( w);
			mail->cc = gw_mail_window_box_get_cc ( w);
			mail->bcc = gw_mail_window_box_get_bcc ( w);
			mail->subject = gw_mail_window_box_get_subject ( w);
			mail->message = gw_mail_window_box_get_msg ( w);

			if ( gw_mail_window_box_get_option_attach_file ( w) )
			{
				mail->file_path = gw_mail_window_box_get_file_path ( w);
			}
			else
			{
				mail->file_path = NULL;
			}

			msg_box = gw_msg_box_create ( w, _( "Send mail"), _( "Sending mail, please wait..."));
			gw_gui_manager_main_interface_refresh ( );

			if ( gw_am_send_mail ( mail) == -1 )
			{
				gtk_widget_destroy ( GTK_WIDGET ( msg_box));

				gw_msg_box_create ( w, _( "Send mail"), _( "An error occured during the sending of mail. Please check your parameters."));
			}
			else
			{
				gtk_widget_destroy ( GTK_WIDGET ( msg_box));
				gtk_widget_destroy ( GTK_WIDGET ( w));
			}

			g_free ( mail->to);
			g_free ( mail->cc);
			g_free ( mail->bcc);
			g_free ( mail->subject);
			g_free ( mail->message);
			g_free ( mail);
		}
	}

	return result;
}

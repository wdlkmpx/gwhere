/*  GWhere.
 *  Copyright (C) 2000	Sébastien LECACHEUR
 *
 *  This program is free software; you can redistribute	it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the	Free Software Foundation; either version 2 of the License, or
 *  (at	your option) any later version.
 *
 *  This program is distributed	in the hope that it will be useful,
 *  but	WITHOUT	ANY WARRANTY; without even the implied warranty	of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR	PURPOSE.  See the
 *  GNU	General	Public License for more	details.
 *
 *  You	should have received a copy of the GNU General Public License
 *  along with this program; if	not, write to the Free Software
 *  Foundation,	Inc., 59 Temple	Place -	Suite 330, Boston, MA 02111-1307, USA.
 */


#include "../gwsupport.h"
#include "gwprogressbarbox.h"

#include <string.h> /* strcmp */


/*! @define	GW_REF_PROGRESS_BAR_BOX_PARENT_WINDOW	The parent window reference */
#define	GW_REF_PROGRESS_BAR_BOX_PARENT_WINDOW "gw_ref_gw_progress_bar_box_parent_window"
/*! @define	GW_REF_PROGRESS_BAR_BOX_TEXT_INFO_LABEL	The text info label to describe	current	processing */
#define	GW_REF_PROGRESS_BAR_BOX_TEXT_INFO_LABEL	"gw_ref_gw_progress_bar_box_text_info_label"
/*! @define	GW_REF_PROGRESS_BAR_BOX_PROGRESS_BAR	The real progress bar */
#define	GW_REF_PROGRESS_BAR_BOX_PROGRESS_BAR "gw_ref_gw_progress_bar_box_progress_bar"
/*! @define	GW_PROGRESS_BAR_BOX_PROGRESS_BAR_FORMAT_STRING	The progress bar format	string */
#define	GW_PROGRESS_BAR_BOX_PROGRESS_BAR_FORMAT_STRING "%v / %u  (%p %%)"
/*! @define	GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON	The ok/cancel button */
#define	GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON "gw_ref_gw_progress_bar_box_ok_cancel_button"
/*! @define	GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON_STATE	The ok/cancel button state */
#define	GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON_STATE "gw_ref_gw_progress_bar_box_ok_cancel_button_state"


GtkWindow * gw_progress_bar_box_create ( GtkWindow *window, gchar *title, gchar *subject, gchar *text, gfloat max, func_stop_progress_t stop, gpointer p)
{
	GtkWidget *w = NULL;
	GtkWidget *frame;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *file_name;
	GtkWidget *progress_bar	= NULL;
	GtkWidget *button;
	guint button_key;
	GtkAccelGroup *accel = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s() : %f\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, max);
#endif

	/* Inits accel group for keystroke shortcuts */
	accel =	gtk_accel_group_new ( );

	if ( !w	)
	{
		w = gtk_window_new ( GTK_WINDOW_DIALOG);
		gtk_window_set_policy (	GTK_WINDOW ( w), FALSE,	FALSE, FALSE);
		g_strdup_to_gtk_text ( title, text_utf8);
		gtk_window_set_title ( GTK_WINDOW ( w),	text_utf8);
		g_free ( text_utf8);
		gtk_container_border_width ( GTK_CONTAINER ( w), 5);

		gtk_window_set_modal ( GTK_WINDOW ( w),TRUE);
		gtk_window_set_transient_for ( GTK_WINDOW ( w),	window);
		gtk_window_set_position	( GTK_WINDOW ( w), GTK_WIN_POS_CENTER);

		gtk_widget_ref ( GTK_WIDGET ( window));
		gtk_object_set_data_full ( GTK_OBJECT (	w), GW_REF_PROGRESS_BAR_BOX_PARENT_WINDOW, window, (GtkDestroyNotify) gtk_widget_unref);

		if ( stop != NULL )
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : connect signals on delete_event and destroy\n", __FILE__,	__LINE__, __PRETTY_FUNCTION__);
#endif

			/* These signals do nothing. In	this way the window cannot be destroyed. What must be done when	stop is	NULL? */
			gtk_signal_connect ( GTK_OBJECT	( w), "delete_event", GTK_SIGNAL_FUNC (	gw_progress_bar_box_signal_do_nothing), NULL);
			gtk_signal_connect ( GTK_OBJECT	( w), "destroy", GTK_SIGNAL_FUNC ( gw_progress_bar_box_signal_do_nothing),	NULL);
		}

		g_strdup_to_gtk_text ( subject, text_utf8);
		frame =	gtk_frame_new (	text_utf8);
		g_free ( text_utf8);
		gtk_container_add ( GTK_CONTAINER ( w),	frame);

		vbox = gtk_vbox_new ( FALSE, 0);
		gtk_container_add ( GTK_CONTAINER ( frame), vbox);
		gtk_container_set_border_width ( GTK_CONTAINER ( vbox),	10);

		g_strdup_to_gtk_text ( text, text_utf8);
		file_name = gtk_label_new ( text_utf8);
		g_free ( text_utf8);

		/* Store the reference to the text info	label to describe the current processing. */
		gtk_widget_ref ( file_name);
		gtk_object_set_data_full ( GTK_OBJECT (	w), GW_REF_PROGRESS_BAR_BOX_TEXT_INFO_LABEL, file_name,	(GtkDestroyNotify) gtk_widget_unref);
		gtk_label_set_justify (	GTK_LABEL ( file_name),	GTK_JUSTIFY_LEFT);
		gtk_box_pack_start ( GTK_BOX ( vbox), file_name, TRUE, TRUE, 0);

#ifdef GW_DEBUG_GUI_COMPONENT
		g_print	( "*** GW - %s (%d) :: %s() : creates the real progress	bar\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
		progress_bar = gtk_progress_bar_new ( );

		/* Store reference to the real progress	bar */
		gtk_widget_ref ( progress_bar);
		gtk_object_set_data_full ( GTK_OBJECT (	w), GW_REF_PROGRESS_BAR_BOX_PROGRESS_BAR, progress_bar,	(GtkDestroyNotify) gtk_widget_unref);

		/* Doesn't show	the progress bar if max	value is 0 */
		if ( max > 0 )
		{
			gtk_progress_configure ( GTK_PROGRESS (	progress_bar), 0, 0, max);
			gtk_progress_set_show_text ( GTK_PROGRESS ( progress_bar), TRUE);

			/* Set the format string of progess state visualization	*/
			g_strdup_to_gtk_text ( GW_PROGRESS_BAR_BOX_PROGRESS_BAR_FORMAT_STRING, text_utf8);
			gtk_progress_set_format_string ( GTK_PROGRESS (	progress_bar), text_utf8);
			g_free ( text_utf8);
			gtk_box_pack_start ( GTK_BOX ( vbox), progress_bar, TRUE, TRUE,	0);
		}

		hbox = gtk_hbox_new ( TRUE, 10);
		gtk_container_add ( GTK_CONTAINER ( vbox), hbox);
		gtk_container_set_border_width ( GTK_CONTAINER ( hbox),	5);

		button = gtk_button_new_with_label ( "");

		/* Store reference to the ok/cancel button */
		gtk_widget_ref ( button);
		gtk_object_set_data_full ( GTK_OBJECT (	w), GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON, button, (GtkDestroyNotify) gtk_widget_unref);
		gw_progress_bar_box_set_state ( GTK_WINDOW ( w), STATE_CANCEL);
		g_strdup_to_gtk_text ( _( "_Cancel"), text_utf8);
		button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( button)->child), text_utf8);
		g_free ( text_utf8);
		gtk_widget_add_accelerator ( button, "clicked",	accel, button_key, GDK_MOD1_MASK, 0);
		gtk_object_set_user_data ( GTK_OBJECT (	button), w);
		gtk_box_pack_start ( GTK_BOX ( hbox), button, TRUE, TRUE, 0);
		gtk_widget_grab_focus ( button);

		if ( stop != NULL )
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : connect custom callback on ok/cancel button\n", __FILE__,	__LINE__, __PRETTY_FUNCTION__);
#endif

			gtk_signal_connect ( GTK_OBJECT	( button), "clicked", GTK_SIGNAL_FUNC (	stop), p);
		}
		else
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : connect standard callback	on ok/cancel button\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			gtk_signal_connect ( GTK_OBJECT	( button), "clicked", GTK_SIGNAL_FUNC (	gw_progress_bar_box_ok_cancel_click), w);
		}

		gtk_window_add_accel_group ( GTK_WINDOW	( w), accel);
	}

	if ( !GTK_WIDGET_VISIBLE ( w) )
	{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : show window\n", __FILE__,	__LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_show_all ( w);
	}
	else
	{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : destroy window\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

		gtk_widget_destroy ( w);
	}

	return GTK_WINDOW ( w);
}


GtkWindow * gw_progress_bar_box_get_parent_window ( GtkWindow *w)
{
	GtkWindow *parent = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		parent = GTK_WINDOW ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_PROGRESS_BAR_BOX_PARENT_WINDOW));
	}

	return parent;
}


GtkProgress * gw_progress_bar_box_get_progress_bar	( GtkWindow *w)
{
	GtkProgress *progress_bar = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		progress_bar =	GTK_PROGRESS ( gtk_object_get_data ( GTK_OBJECT	( w), GW_REF_PROGRESS_BAR_BOX_PROGRESS_BAR));
	}

	return progress_bar;
}


GtkButton * gw_progress_bar_box_get_ok_cancel_button ( GtkWindow *w)
{
	GtkButton *button = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		button =  GTK_BUTTON ( gtk_object_get_data ( GTK_OBJECT	( w), GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON));
	}

	return button;
}


gboolean gw_progress_bar_box_get_iscancel_state ( GtkWindow *w)
{
	gboolean result	= FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL)
	{
		if ( gw_progress_bar_box_get_state ( w) == STATE_CANCEL )
		{
			result = TRUE;
		}
	}

	return result;
}


gboolean gw_progress_bar_box_get_isok_state ( GtkWindow *w)
{
	gboolean result	= FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL)
	{
		if ( gw_progress_bar_box_get_state ( w) == STATE_OK )
		{
			result = TRUE;
		}
	}

	return result;
}


gchar *	gw_progress_bar_box_get_text ( GtkWindow *w)
{
	GtkLabel *label	= NULL;
	gchar *text = NULL;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (label = GTK_LABEL ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_PROGRESS_BAR_BOX_TEXT_INFO_LABEL))) != NULL )
		{
			gtk_label_get (	label, &text);
			g_strdup_from_gtk_text ( text, text_utf8);
		}
	}

	return text_utf8;
}


gint gw_progress_bar_box_get_state ( GtkWindow *w)
{
	gint state = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		state = GPOINTER_TO_INT ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON_STATE));
	}

	return state;
}


gfloat gw_progress_bar_box_get_value ( GtkWindow *w)
{
	GtkProgress *progress_bar = NULL;
	gfloat value = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (progress_bar = gw_progress_bar_box_get_progress_bar ( w)) != NULL )
		{
			value =	gtk_progress_get_value ( progress_bar);
		}
	}

	return value;
}


gfloat gw_progress_bar_box_get_percentage ( GtkWindow *w)
{
	GtkProgress *progress_bar = NULL;
	gfloat percentage = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (progress_bar = gw_progress_bar_box_get_progress_bar ( w)) != NULL )
		{
			percentage = gtk_progress_get_current_percentage ( progress_bar);
		}
	}

	return percentage;
}


gint gw_progress_bar_box_set_value	( GtkWindow *w,	gfloat value)
{
	GtkProgress *progress_bar = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s() : new value is %g\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, value);
#endif

	if ( w != NULL )
	{
		if ( (progress_bar = gw_progress_bar_box_get_progress_bar ( w)) != NULL )
		{
			gtk_progress_set_value ( progress_bar, value);

			result = 0;
		}
	}

	return result;
}


gint gw_progress_bar_box_add_value	( GtkWindow *w,	gfloat value)
{
	GtkProgress *progress_bar = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (progress_bar = gw_progress_bar_box_get_progress_bar ( w)) != NULL )
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : new value is %e => %e\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, gtk_progress_get_value ( progress_bar) + value, gw_progress_bar_box_get_percentage ( w));
#endif

			gtk_progress_set_value ( progress_bar, gtk_progress_get_value (	progress_bar) +	value);

			result = 0;
		}
	}

	return result;
}


gint gw_progress_bar_box_set_percentage ( GtkWindow *w, gfloat percentage)
{
	GtkProgress *progress_bar = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (progress_bar = gw_progress_bar_box_get_progress_bar ( w)) != NULL )
		{
			gtk_progress_set_percentage ( progress_bar, percentage);

			result = 0;
		}
	}

	return result;
}


gint gw_progress_bar_box_set_text ( GtkWindow *w, gchar *file_name)
{
	GtkLabel *label	= NULL;
	gchar *text_utf8 = NULL;
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (label = GTK_LABEL ( gtk_object_get_data ( GTK_OBJECT ( w), GW_REF_PROGRESS_BAR_BOX_TEXT_INFO_LABEL))) != NULL )
		{
			g_strdup_to_gtk_text ( file_name, text_utf8);
			gtk_label_set_text ( label, text_utf8);
			g_free ( text_utf8);
		}

		result = 0;
	}

	return result;
}


gint gw_progress_bar_box_set_state ( GtkWindow *w, gint state)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		gtk_object_set_data ( GTK_OBJECT ( w), GW_REF_PROGRESS_BAR_BOX_OK_CANCEL_BUTTON_STATE, GINT_TO_POINTER ( state));

		result = 0;
	}

	return result;
}


gint gw_progress_bar_box_set_ok_state ( GtkWindow *w)
{
	GtkButton *bt =	NULL;
	GtkAccelGroup *accel = NULL;
	guint button_key;
	gint result = -1;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		bt = gw_progress_bar_box_get_ok_cancel_button ( w);

		if ( bt	!= NULL	)
		{
			/* Inits new accel group for keystroke shortcuts */
			accel =	gtk_accel_group_new ( );
			g_strdup_to_gtk_text ( _( "_Ok"), text_utf8);
			button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( bt)->child),	text_utf8);
			g_free ( text_utf8);
			gtk_widget_add_accelerator ( GTK_WIDGET	( bt), "clicked", accel, button_key, GDK_MOD1_MASK, 0);
			gtk_window_add_accel_group ( w,	accel);
			gw_progress_bar_box_set_state ( w, STATE_OK);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : button state is updated to ok\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			result = 0;
		}
		else
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : cannot update button state\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			result = -1;
		}
	}

	return result;
}


gint gw_progress_bar_box_set_cancel_state ( GtkWindow *w)
{
	GtkButton *bt =	NULL;
	GtkAccelGroup *accel = NULL;
	guint button_key;
	gint result = -1;
	gchar *text_utf8 = NULL;


#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		bt = gw_progress_bar_box_get_ok_cancel_button ( w);

		if ( bt	!= NULL	)
		{
			/* Inits new accel groups for keystroke	shortcuts */
			accel =	gtk_accel_group_new ( );
			g_strdup_to_gtk_text ( _( "_Cancel"), text_utf8);
			button_key = gtk_label_parse_uline ( GTK_LABEL ( GTK_BIN ( bt)->child),	text_utf8);
			g_free ( text_utf8);
			gtk_widget_add_accelerator ( GTK_WIDGET	( bt), "clicked", accel, button_key, GDK_MOD1_MASK, 0);
			gtk_window_add_accel_group ( w,	accel);
			gw_progress_bar_box_set_state ( w, STATE_CANCEL);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : button state is updated to cancel\n", __FILE__, __LINE__,	__PRETTY_FUNCTION__);
#endif

			result = 0;
		}
		else
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : cannot update button state\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			result = -1;
		}

	}

	return result;
}


gboolean gw_progress_bar_box_ok_cancel_click ( GtkWidget *bt, GtkWindow *w)
{
	gboolean result	= FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( gw_progress_bar_box_get_isok_state ( w) )
		{
			gw_progress_bar_box_ok_click ( bt,	w);

			result = TRUE;
		}
		else { if ( gw_progress_bar_box_get_iscancel_state	( w) )
		{
			gw_progress_bar_box_cancel_click (	bt, w);

			result = TRUE;
		}
		else
		{
#ifdef GW_DEBUG_GUI_COMPONENT
			g_print	( "*** GW - %s (%d) :: %s() : unknown state\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
			/* If they're no state */
			result = FALSE;
		}}
	}

	return result;
}


gboolean gw_progress_bar_box_ok_click ( GtkWidget *bt, GtkWindow *w)
{
	gboolean result	= FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return result;
}


gboolean gw_progress_bar_box_cancel_click ( GtkWidget *bt,	GtkWindow *w)
{
	gboolean result	= FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return result;
}


gboolean gw_progress_bar_box_destroy ( GtkObject *w, gpointer *p)
{
	gboolean result	= FALSE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return result;
}


gboolean gw_progress_bar_box_signal_do_nothing ( GtkObject	*ob, gpointer p)
{
	gboolean result	= TRUE;


#ifdef GW_DEBUG_GUI_COMPONENT
	g_print	( "*** GW - %s (%d) :: %s()\n",	__FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	return result;
}

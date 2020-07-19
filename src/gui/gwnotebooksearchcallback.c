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
#include "gwnotebooksearchcallback.h"

#include <string.h> /* strncmp strcasecmp */

#include "gwnotebooksearch.h"
#include "gwstatusbar.h"
#include "gwstatusbarcallback.h"
#include "gwmsgbox.h"

#include "data/gwdata.h"

#include "../gwapplicationmanager.h"
#include "../gwsearchengine.h"
#include "../gwguimanager.h"


gint gw_catalog_compare_search_gulong ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2)
{
	struct search_item_info *search_item_info1 = NULL, *search_item_info2 = NULL;
	gulong nb1 = 0, nb2 = 0;
	gint type1, type2;
	gchar *str_name1 = NULL, *str_name2 = NULL;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) )
	{
		search_item_info1 = (struct search_item_info*)(((GtkCListRow *)ptr1)->data);
		search_item_info2 = (struct search_item_info*)(((GtkCListRow *)ptr2)->data);

		if ( (search_item_info1!=NULL) && (search_item_info2!=NULL) )
		{
			str_name1 = search_item_info_get_name ( search_item_info1);
			str_name2 = search_item_info_get_name ( search_item_info2);
			type1 = search_item_info_get_type ( search_item_info1);
			type2 = search_item_info_get_type ( search_item_info2);

			switch ( clist->sort_column)
			{
				case GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT:	nb1 = search_item_info_get_date ( search_item_info1);
											nb2 = search_item_info_get_date ( search_item_info2);
											break;
			}

			if ( (str_name1!=NULL) && (str_name2!=NULL) )
			{
				if ( (strlen ( str_name1) == 2) && (strncmp ( str_name1, "..", 2) == 0) )
				{
					result = (clist->sort_type==GTK_SORT_ASCENDING?-2:2);
				}
				else
				{
					if ( (strlen ( str_name2) == 2) && (strncmp ( str_name2, "..", 2) == 0) )
					{
						result = (clist->sort_type==GTK_SORT_ASCENDING?2:-2);
					}
					else
					{
						result = (((gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_SORT_BY_TYPE)==0)||(type1==type2))?(nb1-nb2):(type1-type2));
					}
				}
			}
		}
	}

	return result;
}


gint gw_catalog_compare_search_gui64long ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2)
{
	struct search_item_info *search_item_info1 = NULL, *search_item_info2 = NULL;
	guint64 nb1 = 0, nb2 = 0;
	gint type1, type2;
	gchar *str_name1 = NULL, *str_name2 = NULL;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) )
	{
		search_item_info1 = (struct search_item_info*)(((GtkCListRow *)ptr1)->data);
		search_item_info2 = (struct search_item_info*)(((GtkCListRow *)ptr2)->data);

		if ( (search_item_info1!=NULL) && (search_item_info2!=NULL) )
		{
			str_name1 = search_item_info_get_name ( search_item_info1);
			str_name2 = search_item_info_get_name ( search_item_info2);
			type1 = search_item_info_get_type ( search_item_info1);
			type2 = search_item_info_get_type ( search_item_info2);

			switch ( clist->sort_column)
			{
				case GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT:	nb1 = search_item_info_get_size ( search_item_info1);
											nb2 = search_item_info_get_size ( search_item_info2);
											break;
			}

			if ( (str_name1!=NULL) && (str_name2!=NULL) )
			{
				if ( (strlen ( str_name1) == 2) && (strncmp ( str_name1, "..", 2) == 0) )
				{
					result = (clist->sort_type==GTK_SORT_ASCENDING?-2:2);
				}
				else
				{
					if ( (strlen ( str_name2) == 2) && (strncmp ( str_name2, "..", 2) == 0) )
					{
						result = (clist->sort_type==GTK_SORT_ASCENDING?2:-2);
					}
					else
					{
						result = (((gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_SORT_BY_TYPE)==0)||(type1==type2))?(nb1-nb2):(type1-type2));
					}
				}
			}
		}
	}

	return result;
}


gint gw_catalog_compare_search_str ( GtkCList *clist, const gpointer ptr1, const gpointer ptr2)
{
	struct search_item_info *search_item_info1 = NULL, *search_item_info2 = NULL;
	gchar *str_name1 = NULL, *str_name2 = NULL;
	gchar *str1 = NULL, *str2 = NULL;
	gboolean type1 = FALSE, type2 = FALSE;
	gint result = 0;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (ptr1!=NULL) && (ptr2!=NULL) )
	{
		search_item_info1 = (struct search_item_info*)(((GtkCListRow *)ptr1)->data);
		search_item_info2 = (struct search_item_info*)(((GtkCListRow *)ptr2)->data);

		if ( (search_item_info1!=NULL) && (search_item_info2!=NULL) )
		{
			str_name1 = search_item_info_get_name ( search_item_info1);
			str_name2 = search_item_info_get_name ( search_item_info2);
			type1 = search_item_info_get_type ( search_item_info1);
			type2 = search_item_info_get_type ( search_item_info2);

			switch ( clist->sort_column)
			{
				case GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT:		str1 = str_name1;
												str2 = str_name2;
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT:		str1 = search_item_info_get_disk ( search_item_info1);
												str2 = search_item_info_get_disk ( search_item_info2);
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT:		str1 = search_item_info_get_path ( search_item_info1);
												str2 = search_item_info_get_path ( search_item_info2);
												break;


				case GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT:	str1 = search_item_info_get_category_name ( search_item_info1);
												str2 = search_item_info_get_category_name ( search_item_info2);
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT:	str1 = search_item_info_get_description ( search_item_info1);
												str2 = search_item_info_get_description ( search_item_info2);
												break;
			}

			if ( (str_name1!=NULL) && (str_name2!=NULL) && (str1!=NULL) && (str2!=NULL) )
			{
				if ( (strlen ( str_name1) == 2) && (strncmp ( str_name1, "..", 2) == 0) )
				{
					result = (clist->sort_type==GTK_SORT_ASCENDING?-2:2);
				}
				else
				{
					if ( (strlen ( str_name2) == 2) && (strncmp ( str_name2, "..", 2) == 0) )
					{
						result = (clist->sort_type==GTK_SORT_ASCENDING?2:-2);
					}
					else
					{
						if ( gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_SORT_CASE_SENSITIVE) == 1 )
						{
							result = (((gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_SORT_BY_TYPE)==0)||(type1==type2))?strcmp ( str1, str2):(type1-type2));
						}
						else
						{
							result = (((gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_SORT_BY_TYPE)==0)||(type1==type2))?strcasecmp ( str1, str2):(type1-type2));
						}
					}
				}
			}
		}
	}

	return result;
}


gboolean gw_notebook_search_column_sort ( GtkCList *clist, gint column, gpointer data)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( clist != NULL )
	{
		if ( GPOINTER_TO_INT ( data) != -1 )
		{
		if ( column == clist->sort_column )
		{
			if ( clist->sort_type == GTK_SORT_ASCENDING )
			{
				clist->sort_type = GTK_SORT_DESCENDING;
			}
			else
			{
				clist->sort_type = GTK_SORT_ASCENDING;
			}
		}
		else
		{
			gtk_clist_set_sort_column ( clist, column);
		}
		}

		gw_notebook_search_set_column_sort ( clist, column);

		if ( GPOINTER_TO_INT ( data) != -1 )
		{
			gtk_clist_sort ( clist);
		}

		result = TRUE;
	}

	return result;
}


gboolean gw_notebook_search_search_string_activate ( GtkWidget *entry, GtkWindow *w)
{
	gboolean result = FALSE;
	gchar *text = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( entry != NULL )
		{
			g_strdup_from_gtk_text ( gtk_entry_get_text ( GTK_ENTRY ( entry)), text);
			gw_am_set_settings ( GW_VALUE_APP_SEARCH_STRING, text);
		result = TRUE;
	}
	}

	return result;
}


gboolean gw_notebook_search_search_button_click ( GtkWidget *bt, GtkWindow *w)
{
	gboolean result = FALSE;
	struct user_quick_search *user_qs = NULL;
	gulong founded = 0;
	gchar *msg = NULL;
	GtkWindow *window = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		/* saves the new filled search string */
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_STRING, gw_notebook_search_get_search_text ( w));

		if ( gw_gui_manager_main_interface_get_tree_root ( ) != NULL )
		{
			/* Allocate user_quick_search structure, had to free this structure after */
			user_qs = gw_notebook_search_get_user_quick_search ( w);
			window = gw_gui_manager_main_interface_get_main_window ( );

			gw_status_bar_put_messages ( window, _( "Search in catalog"), _( "Please wait..."));
			gw_gui_manager_main_interface_refresh ( );

			founded = search_engine_search_in_disk ( w, user_qs);
			msg = g_strdup_printf ( _("%lu item(s) founded."), founded);
			gw_status_bar_put_messages ( window, _( "Search result"), msg);
			g_free ( msg);

			/* Free the user_quick_search struture. */
			user_quick_search_free ( user_qs);

			if ( founded == 0 )
			{
				gw_msg_box_create ( w, _( "Search result"), _( "No item matched."));
				/* Doesn't use it at time. It should be configured in the settings. */
				/* gdk_beep ( );*/
				gw_am_beep ( );
			}

			result = TRUE;
		}
		else
		{
			gw_msg_box_create ( w, _( "Searching..."), _( "Cannot start searching : no catalog loaded"));

			result = FALSE;
		}
	}

	return result;
}


gboolean gw_notebook_search_clear_button_click ( GtkWidget *bt, GtkWindow *w)
{
	gboolean result = FALSE;
	GtkCList *clist = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		if ( (clist = gw_notebook_search_get_clist_search ( w)) != NULL )
		{
			gtk_clist_freeze ( clist);
			gtk_clist_clear ( clist);
			gtk_clist_thaw ( clist);

			result = TRUE;
		}
	}

	return result;
}


gboolean gw_notebook_search_select_row ( GtkCList *clist, gint line, gint column, GdkEventButton *event, GtkWindow *w)
{
	gboolean result = FALSE;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( clist != NULL && w != NULL )
	{
		gw_status_bar_set_catalog_search_page ( w, g_list_length ( clist->selection));

		result = TRUE;
	}

	return result;
}


gint gw_notebook_search_option_use_case_sensitive_click ( GtkToggleButton *chk, GtkWindow *w)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_CASE_SENSITIVE, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_search_option_search_type_click ( GtkToggleButton *chk, gpointer search_type)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_TYPE, g_strdup_printf ( "%d", GPOINTER_TO_INT ( search_type)));
		result = 0;
	}

	return result;
}


gint gw_notebook_search_option_match_file_click ( GtkToggleButton *chk, GtkWindow *w)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_FILE_NAME, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_search_option_match_folder_click ( GtkToggleButton *chk, GtkWindow *w)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_FOLDER_NAME, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_search_option_match_disk_click ( GtkToggleButton *chk, GtkWindow *w)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_DISK_NAME, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_search_option_match_category_click ( GtkToggleButton *chk, GtkWindow *w)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_CATEGORY_NAME, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_search_option_match_description_click ( GtkToggleButton *chk, GtkWindow *w)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( chk != NULL)
	{
		gw_am_set_settings ( GW_VALUE_APP_SEARCH_DESCRIPTION, g_strdup_printf ( "%d", gtk_toggle_button_get_active ( GTK_TOGGLE_BUTTON ( chk))));
		result = 0;
	}

	return result;
}


gint gw_notebook_search_clist_column_resized ( GtkCList *clist, gint column, gint width, gpointer user_data)
{
	gint result = -1;
	gint autoresize = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (autoresize = gw_am_get_settings_tol ( GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE)) == -1 )
	{
		autoresize = GW_VALUE_APP_EXPLORER_COLUMN_AUTORESIZE_DEFAULT;
	}

	/* Saves the column width only if the autoresize mode is desactivated. */
	if ( autoresize == FALSE )
	{
		if ( (clist!=NULL) && (column>-1) )
		{
			switch ( column)
			{
				case GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_NAME_SIZE, g_strdup_printf ( "%d", width));
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_DISK_SIZE, g_strdup_printf ( "%d", width));
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_PATH_SIZE, g_strdup_printf ( "%d", width));
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_SIZE_SIZE, g_strdup_printf ( "%d", width));
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT:		gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_DATE_SIZE, g_strdup_printf ( "%d", width));
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_SIZE, g_strdup_printf ( "%d", width));
												break;

				case GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT:	gw_am_set_settings ( GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_SIZE, g_strdup_printf ( "%d", width));
												break;

				default:							break;
			}

			result = 0;
		}
	}

	return result;
}


gint gw_notebook_search_set_column_sort ( GtkCList *clist, gint column)
{
	gint result = -1;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (clist!=NULL) && (column>-1) )
	{
		switch ( column)
		{
			case GW_VALUE_APP_SEARCH_COLUMN_NAME_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_search_str);
											break;

			case GW_VALUE_APP_SEARCH_COLUMN_DISK_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_search_str);
											break;

			case GW_VALUE_APP_SEARCH_COLUMN_PATH_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_search_str);
											break;

			case GW_VALUE_APP_SEARCH_COLUMN_SIZE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_search_gui64long);
											break;

			case GW_VALUE_APP_SEARCH_COLUMN_DATE_POSITION_DEFAULT:		gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_search_gulong);
											break;

			case GW_VALUE_APP_SEARCH_COLUMN_CATEGORY_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_search_str);
											break;

			case GW_VALUE_APP_SEARCH_COLUMN_DESCRIPTION_POSITION_DEFAULT:	gtk_clist_set_compare_func ( clist, (GtkCListCompareFunc)gw_catalog_compare_search_str);
											break;

			default:							gtk_clist_set_compare_func ( clist, NULL);
											break;
		}

		result = 0;
	}

	return result;
}

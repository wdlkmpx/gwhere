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
#include "gwnotebook.h"

#include "gwnotebookcatalog.h"
#include "gwnotebooksearch.h"
#include "gwnotebookmanagment.h"
#include "gwreferences.h"

#include "gwnotebookmanagmentcallback.h"
#include "gwstatusbarcallback.h"
// callbacks
gboolean gw_notebook_page_switch (GtkNotebook *notebook, GtkNotebookPage *page, gint page_num, GtkWindow *w);


GtkWidget * gw_notebook_create ( GtkWindow *w, GtkWidget *parent)
{
	GtkWidget *notebook = NULL;
	GtkWidget *notebook_catalog = NULL;
	GtkWidget *notebook_search = NULL;
	GtkWidget *notebook_managment = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		notebook = gtk_notebook_new ( );
		g_object_ref ( notebook);
		g_object_set_data_full (G_OBJECT ( w), GW_REF_NOTEBOOK, notebook,(GDestroyNotify) g_object_unref);
		gtk_widget_show ( notebook);

		/* Notebook catalog */
		notebook_catalog = gw_notebook_catalog_create_and_add ( w, GTK_NOTEBOOK ( notebook));

		/* Notebook search */
		notebook_search = gw_notebook_search_create_and_add ( w, GTK_NOTEBOOK ( notebook));

		/* Notebook managment */
		notebook_managment = gw_notebook_managment_create_and_add ( w, GTK_NOTEBOOK ( notebook));

		g_signal_connect (G_OBJECT ( notebook), "switch_page", G_CALLBACK ( gw_notebook_page_switch), w);
	}

	return notebook;
}



gboolean gw_notebook_page_switch (GtkNotebook *notebook,
                                  GtkNotebookPage *page,
                                  gint page_num,
                                  GtkWindow *w) /* user_data */
{
	GtkCList *clist = NULL;
	gboolean result = FALSE;
	static gboolean first_load = TRUE;
	GtkComboBoxText *cmb = NULL;

#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		switch ( page_num )
		{
			case 0:
				clist = gw_notebook_catalog_get_clist_explorer ( w);
				gw_status_bar_set_catalog_explorer_page ( w, g_list_length ( clist->selection));
				result = TRUE;
				break;

			case 1:
				clist = gw_notebook_catalog_get_clist_explorer ( w);
				gw_status_bar_set_catalog_search_page ( w, g_list_length ( clist->selection));
				result = TRUE;
				break;

			case 2:
				gw_status_bar_set_catalog_managment_page ( w);
				/* Loads device informations at the first displaying managment tabbed pane. */
				if ( first_load)
				{
					first_load = FALSE;
					if ( (cmb = gw_notebook_managment_get_combo_box_device ( w)) != NULL)
					{
						gw_notebook_managment_select_device (cmb, w);
					}
				}
				result = TRUE;
				break;

			default:
				return FALSE;
				break;
		}
	}

	return result;
}

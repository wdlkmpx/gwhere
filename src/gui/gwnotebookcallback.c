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
#include "gwnotebookcallback.h"

#include "gwnotebookcatalog.h"
#include "gwnotebookmanagment.h"
#include "gwnotebookmanagmentcallback.h"
#include "gwstatusbarcallback.h"


gboolean gw_notebook_page_switch ( GtkNotebook *notebook, GtkNotebookPage *page, gint page_num, GtkWindow *w)
{
	GtkCList *clist = NULL;
	gboolean result = FALSE;
	static gboolean first_load = TRUE;
	GtkCombo *cmb = NULL;


#ifdef GW_DEBUG_GUI_CALLBACK_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( w != NULL )
	{
		switch ( page_num )
		{
			case 0:	clist = gw_notebook_catalog_get_clist_explorer ( w);
				gw_status_bar_set_catalog_explorer_page ( w, g_list_length ( clist->selection));

				result = TRUE;
				break;

			case 1:	clist = gw_notebook_catalog_get_clist_explorer ( w);
				gw_status_bar_set_catalog_search_page ( w, g_list_length ( clist->selection));

				result = TRUE;
				break;

			case 2: gw_status_bar_set_catalog_managment_page ( w);

				/* Loads device informations at the first displaying managment tabbed pane. */
				if ( first_load)
				{
					first_load = FALSE;
					if ( (cmb = gw_notebook_managment_get_combo_box_device ( w)) != NULL)
					{
						gtk_widget_grab_focus ( GTK_WIDGET ( GTK_OBJECT ( GTK_ENTRY ( GTK_COMBO ( cmb)->entry))));
						gw_notebook_managment_select_device ( GTK_WIDGET ( GTK_OBJECT ( GTK_ENTRY ( GTK_COMBO ( cmb)->entry))), w);
					}
				}

				result = TRUE;
				break;

			default:return FALSE;
				break;
		}
	}

	return result;
}

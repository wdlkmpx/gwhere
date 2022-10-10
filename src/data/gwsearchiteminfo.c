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
#include "gwsearchiteminfo.h"


#include <stdlib.h>
#include <string.h> /* strlen strncmp */
#include <time.h>
#include "tools/gwtools.h"


typedef struct search_item_info {
	gint type;			/* Item type						*/
	gchar *name;			/* Item name						*/
	gchar *disk;			/* Item disk						*/
	gchar *path;			/* Item path						*/
	guint64 size;			/* Item size						*/
	gulong date;			/* Item creation date					*/
	GWDBCategory *category;		/* Item category					*/
	gchar *description;		/* Item description (or comment)			*/
} SearchItemInfo;


SearchItemInfo * search_item_info_new ( void) {
	SearchItemInfo *p = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( (p = (SearchItemInfo*)g_malloc0 ( sizeof ( SearchItemInfo))) != NULL ) {
		p->type = SEARCH_ITEM_TYPE_NONE;
		p->name = NULL;
		p->disk = NULL;
		p->path = NULL;
		p->size = 0;
		p->date = 0;
		p->category = NULL;
		p->description = NULL;
	}

	return p;
}


gint search_item_info_set_type ( SearchItemInfo *p, gint type) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		p->type = type;

		return 0;
	}

	return -1;
}


gint search_item_info_set_name ( SearchItemInfo *p, gchar *name) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->name != NULL ) {
			g_free ( p->name);
		}

		p->name = name;

		return 0;
	}

	return -1;
}


gint search_item_info_set_disk ( SearchItemInfo *p, gchar *disk) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->disk != NULL ) {
			g_free ( p->disk);
		}

		p->disk = disk;

		return 0;
	}

	return -1;
}


gint search_item_info_set_path ( SearchItemInfo *p, gchar *path) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->path != NULL ) {
			g_free ( p->path);
		}

		p->path = path;

		return 0;
	}

	return -1;
}


gint search_item_info_set_size ( SearchItemInfo *p, guint64 size) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		p->size = size;

		return 0;
	}

	return -1;
}


gint search_item_info_set_date ( SearchItemInfo *p, gulong date) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		p->date = date;

		return 0;
	}

	return -1;
}


gint search_item_info_set_category ( struct search_item_info *p, GWDBCategory *category) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->category != NULL ) {
			/* Must decrese category count */
		}

		p->category = category;

		return 0;
	}

	return -1;
}


gint search_item_info_set_description ( SearchItemInfo *p, gchar *description) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->description != NULL ) {
			g_free ( p->description);
		}

		p->description = description;

		return 0;
	}

	return -1;
}


gint search_item_info_get_type ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		return p->type;
	}

	return SEARCH_ITEM_TYPE_NONE;
}


gchar * search_item_info_get_name ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->name != NULL ) {
			return p->name;
		} else {
			return "";
		}
	}

	return NULL;
}


gchar * search_item_info_get_disk ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->disk != NULL ) {
			return p->disk;
		} else {
			return "";
		}
	}

	return NULL;
}


gchar * search_item_info_get_path ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->path != NULL ) {
			return p->path;
		} else {
			return "";
		}
	}

	return NULL;
}


guint64 search_item_info_get_size ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		return p->size;
	}

	return -1;
}


gulong search_item_info_get_date ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		return p->date;
	}

	return 0;
}


GWDBCategory * search_item_info_get_category ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->category != NULL ) {
			return p->category;
		}
	}

	return NULL;
}


gchar * search_item_info_get_category_name ( struct search_item_info *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( search_item_info_get_category ( p) == NULL ) {
			return "";
		}

		//FIXME very bad way!!
		return gw_db_category_get_name ( search_item_info_get_category ( p));
	}

	return NULL;
}


gint search_item_info_get_category_index ( struct search_item_info *p) {
	gint index = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( search_item_info_get_category ( p) != NULL ) {
			if  ( (index = gw_db_category_get_index ( search_item_info_get_category ( p))) != -1 ) {
				return index;
			}
		}

	}

	return -1;
}


gchar * search_item_info_get_description ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL ) {
		if ( p->description != NULL ) {
			return p->description;
		} else {
			return "";
		}
	}

	return NULL;
}


gint search_item_info_free ( SearchItemInfo *p) {
#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( p != NULL ) {
		/* Do not free any string to not destroy database. */
		search_item_info_set_name ( p, NULL);

		search_item_info_set_disk ( p, NULL);
		search_item_info_set_path ( p, NULL);

		search_item_info_set_description ( p, NULL);

		if ( p->category != NULL) {
			gw_db_category_free ( p->category);
		}

		g_free ( p);

		return 0;
	}

	return -1;
}

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
#include "gwenginequicksearch.h"


#include "gwuserquicksearch.h"


typedef struct engine_quick_search {
	gchar *pattern;					/* The search string pattern (it's a regular expression)	*/
	gchar **key_words;				/* The key words list in cas of key words search		*/
	gint type;					/* Type of search						*/
	gboolean case_sensitive;				/* If use case sensitive					*/
	gboolean match_file;				/* If search match with files					*/
	gboolean match_folder;				/* If search match with folders				*/
	gboolean match_disk;				/* If search match with disks				*/
	gboolean match_category;				/* If search match with categories				*/
	gboolean match_description;			/* If search match with descriptions				*/
	gboolean match_all_key_words;			/* If search must match all key words			*/
	} EngineQuickSearch;


struct engine_quick_search *engine_quick_search_new ( void)
{
	struct engine_quick_search *p = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( (p = ( struct engine_quick_search*)g_malloc0 ( sizeof ( struct engine_quick_search))) != NULL)
	{
		p->pattern = NULL;
		p->key_words = NULL;
		p->type = SEARCH_TYPE_NONE;
		p->case_sensitive = TRUE;
		p->match_file = TRUE;
		p->match_folder = FALSE;
		p->match_disk = FALSE;
		p->match_category = FALSE;
		p->match_description = FALSE;
		p->match_all_key_words = FALSE;
	}

	return p;
}


gint engine_quick_search_set_pattern ( struct engine_quick_search *p, gchar *pattern)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->pattern != NULL )
		{
			g_free ( p->pattern);
		}

		p->pattern = pattern;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_key_words ( struct engine_quick_search *p, gchar **key_words_list)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->key_words != NULL )
		{
			g_strfreev ( p->key_words);
		}

		p->key_words = key_words_list;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_type ( struct engine_quick_search *p, gint type)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->type = type;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_case_sensitive ( struct engine_quick_search *p, gboolean case_sensitive)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->case_sensitive = case_sensitive;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_match_file ( struct engine_quick_search *p, gboolean match_file)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->match_file = match_file;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_match_folder ( struct engine_quick_search *p, gboolean match_folder)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->match_folder = match_folder;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_match_disk ( struct engine_quick_search *p, gboolean match_disk)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->match_disk = match_disk;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_match_category ( struct engine_quick_search *p, gboolean match_category)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->match_category = match_category;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_match_description ( struct engine_quick_search *p, gboolean match_description)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->match_description = match_description;

		return 0;
	}

	return -1;
}


gint engine_quick_search_set_match_all_key_words ( struct engine_quick_search *p, gboolean match_all_key_words)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->match_all_key_words = match_all_key_words;

		return 0;
	}

	return -1;
}


gchar * engine_quick_search_get_pattern ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->pattern;
	}

	return NULL;
}


gchar ** engine_quick_search_get_key_words ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->key_words;
	}

	return NULL;
}


gint engine_quick_search_get_type ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->type;
	}

	return SEARCH_TYPE_NONE;
}


gboolean engine_quick_search_get_case_sensitive ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->case_sensitive;
	}

	return FALSE;
}


gboolean engine_quick_search_get_match_file ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->match_file;
	}

	return FALSE;
}


gboolean engine_quick_search_get_match_folder ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->match_folder;
	}

	return FALSE;
}


gboolean engine_quick_search_get_match_disk ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->match_disk;
	}

	return FALSE;
}


gboolean engine_quick_search_get_match_category ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->match_category;
	}

	return FALSE;
}


gboolean engine_quick_search_get_match_description ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->match_description;
	}

	return FALSE;
}


gboolean engine_quick_search_get_match_all_key_words ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->match_all_key_words;
	}

	return FALSE;
}


gint engine_quick_search_free ( struct engine_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( p != NULL )
	{
		engine_quick_search_set_pattern ( p, NULL);
		engine_quick_search_set_key_words ( p, NULL);

		g_free ( p);

		return 0;
	}

	return -1;
}

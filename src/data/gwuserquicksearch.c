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
#include "gwuserquicksearch.h"


#include "tools/gwtools.h"


typedef struct user_quick_search {
	struct engine_quick_search *quick_search;		/* The quick search		*/
	gint search_type;					/* The quick search type	*/
	} UserQuickSearch;


struct user_quick_search *user_quick_search_new ( void)
{
	struct user_quick_search *p = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( (p = ( struct user_quick_search*)g_malloc0 ( sizeof ( struct user_quick_search))) != NULL)
	{
		p->quick_search = engine_quick_search_new ( );
		p->search_type = 0;
	}

	return p;
}


gint user_quick_search_set_pattern ( struct user_quick_search *p, gchar *pattern)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_set_pattern ( p->quick_search, pattern);
	}

	return -1;
}


gint user_quick_search_set_case_sensitive ( struct user_quick_search *p, gboolean case_sensitive)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_set_case_sensitive ( p->quick_search, case_sensitive);
	}

	return -1;
}


gint user_quick_search_set_type ( struct user_quick_search *p, gint type)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->search_type = type;

		return 0;
	}

	return -1;
}


gint user_quick_search_set_match_file ( struct user_quick_search *p, gboolean match_file)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_set_match_file ( p->quick_search, match_file);
	}

	return -1;
}


gint user_quick_search_set_match_folder ( struct user_quick_search *p, gboolean match_folder)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_set_match_folder ( p->quick_search, match_folder);
	}

	return -1;
}


gint user_quick_search_set_match_disk ( struct user_quick_search *p, gboolean match_disk)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_set_match_disk ( p->quick_search, match_disk);
	}

	return -1;
}


gint user_quick_search_set_match_category ( struct user_quick_search *p, gboolean match_category)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_set_match_category ( p->quick_search, match_category);
	}

	return -1;
}


gint user_quick_search_set_match_description ( struct user_quick_search *p, gboolean match_description)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_set_match_description ( p->quick_search, match_description);
	}

	return -1;
}


gchar * user_quick_search_get_pattern ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_get_pattern ( p->quick_search);
	}

	return NULL;
}


gboolean user_quick_search_get_case_sensitive ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_get_case_sensitive ( p->quick_search);
	}

	return FALSE;
}


gint user_quick_search_get_type ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->search_type;
	}

	return SEARCH_TYPE_NONE;
}


gboolean user_quick_search_get_match_file ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_get_match_file ( p->quick_search);
	}

	return FALSE;
}


gboolean user_quick_search_get_match_folder ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_get_match_folder ( p->quick_search);
	}

	return FALSE;
}


gboolean user_quick_search_get_match_disk ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_get_match_disk ( p->quick_search);
	}

	return FALSE;
}


gboolean user_quick_search_get_match_category ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_get_match_category ( p->quick_search);
	}

	return FALSE;
}


gboolean user_quick_search_get_match_description ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return engine_quick_search_get_match_description ( p->quick_search);
	}

	return FALSE;
}


gint user_quick_search_free ( struct user_quick_search *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( p != NULL )
	{
		engine_quick_search_free ( p->quick_search);

		g_free ( p);

		return 0;
	}

	return -1;
}


struct engine_quick_search *user_quick_search_to_engine_quick_search ( struct user_quick_search *p)
{
	struct engine_quick_search *result = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		result = engine_quick_search_new ( );

		engine_quick_search_set_case_sensitive ( result, user_quick_search_get_case_sensitive ( p));
		engine_quick_search_set_type ( result, user_quick_search_get_type ( p));
		engine_quick_search_set_match_file ( result, user_quick_search_get_match_file ( p));
		engine_quick_search_set_match_folder ( result, user_quick_search_get_match_folder ( p));
		engine_quick_search_set_match_disk ( result, user_quick_search_get_match_disk ( p));
		engine_quick_search_set_match_category ( result, user_quick_search_get_match_category ( p));
		engine_quick_search_set_match_description ( result, user_quick_search_get_match_description ( p));

		if ( user_quick_search_get_type ( p) == SEARCH_TYPE_KEY_WORDS )
		{
			engine_quick_search_set_key_words ( result, gw_str_key_words_to_regex ( user_quick_search_get_pattern ( p)));
		}
		else if ( user_quick_search_get_type ( p) == SEARCH_TYPE_WILDCARDS )
		{
			engine_quick_search_set_pattern ( result, gw_str_blob_to_regex ( user_quick_search_get_pattern ( p)));
    		}
		else if ( user_quick_search_get_type ( p) == SEARCH_TYPE_REGEX )
		{
			engine_quick_search_set_pattern ( result, user_quick_search_get_pattern ( p));
    		}
	}

	return result;
}

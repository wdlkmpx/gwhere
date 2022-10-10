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
#include "gwscandiskinfo.h"


typedef struct scan_disk_info {
	struct vfs_stats *vfs;				/* Virtual file system to scan					*/
	gchar *disk_name;				/* Disk name for catalog					*/
	gint disk_num_archive;				/* Disk number archive for catalog				*/
	GWDBCategoryPK disk_category;			/* Disk category for catalog					*/
	gboolean explore_tree_structure;		/* If explores tree structure				*/
	gboolean explore_archive;			/* If explores archive files					*/
	gboolean make_description;			/* If makes description file					*/
	gboolean category_recursive;			/* If sets category recursive					*/
	gboolean stop;					/* If must stop the scan					*/
	gchar *error_msg;				/* Error message						*/
	gpointer statment_controler;			/* Statment controler					*/
	func_descr_t scan_disk_get_file_description;	/* Function to get the file description				*/
	func_statment_t scan_disk_set_current_statment;	/* Function to indicate current statment of scan		*/
	} scan_disk_info;



struct scan_disk_info * scan_disk_info_new ( void)
{
	scan_disk_info *p = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( (p = ( struct scan_disk_info*)g_malloc0 ( sizeof ( struct scan_disk_info))) != NULL)
	{
		p->vfs = NULL;
		p->disk_name = NULL;
		p->disk_num_archive = 0;
		p->disk_category = NULL;
		p->explore_tree_structure = FALSE;
		p->explore_archive = FALSE;
		p->make_description = FALSE;
		p->category_recursive = FALSE;
		p->stop = FALSE;
		p->error_msg = NULL;
		p->scan_disk_get_file_description = NULL;
		p->scan_disk_set_current_statment = NULL;
	}

	return p;
}


gint scan_disk_info_set_vfs ( struct scan_disk_info *p, struct vfs_stats *vfs)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->vfs = vfs;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_disk_name ( struct scan_disk_info *p, gchar *name)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->disk_name != NULL )
		{
			g_free ( p->disk_name);
		}

		p->disk_name = name;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_disk_num_archive ( struct scan_disk_info *p, gint num)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->disk_num_archive = num;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_disk_category_ref ( struct scan_disk_info *p, GWDBCategoryPK ref)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->disk_category = ref;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_explore_tree_structure ( struct scan_disk_info *p, gboolean tree_structure)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->explore_tree_structure = tree_structure;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_explore_archive ( struct scan_disk_info *p, gboolean explore_archive)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->explore_archive = explore_archive;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_make_description ( struct scan_disk_info *p, gboolean make_description)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->make_description = make_description;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_category_recursive ( struct scan_disk_info *p, gboolean category_recursive)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->category_recursive = category_recursive;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_stop ( struct scan_disk_info *p, gboolean stop)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->stop = stop;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_error_msg ( struct scan_disk_info *p, gchar *error_msg)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->error_msg != NULL )
		{
			g_free ( p->error_msg);
		}

		p->error_msg = error_msg;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_statment_controler ( struct scan_disk_info *p, gpointer statment_controler)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->statment_controler = statment_controler;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_scan_disk_get_file_description ( struct scan_disk_info *p, func_descr_t f)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->scan_disk_get_file_description = f;

		return 0;
	}

	return -1;
}


gint scan_disk_info_set_scan_disk_set_current_statment ( struct scan_disk_info *p, func_statment_t f)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->scan_disk_set_current_statment = f;

		return 0;
	}

	return -1;
}


struct vfs_stats * scan_disk_info_get_vfs ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->vfs;
	}

	return NULL;
}


gchar * scan_disk_info_get_disk_name ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->disk_name;
	}

	return NULL;
}


gint scan_disk_info_get_disk_num_archive ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->disk_num_archive;
	}

	return -1;
}


GWDBCategoryPK scan_disk_info_get_disk_category_ref ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->disk_category;
	}

	return NULL;
}


gboolean scan_disk_info_get_explore_tree_structure ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->explore_tree_structure;
	}

	return FALSE;
}


gboolean scan_disk_info_get_explore_archive ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->explore_archive;
	}

	return FALSE;
}


gboolean scan_disk_info_get_make_description ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->make_description;
	}

	return FALSE;
}


gboolean scan_disk_info_get_category_recursive ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->category_recursive;
	}

	return FALSE;
}


gboolean scan_disk_info_get_stop ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->stop;
	}

	return FALSE;
}


gchar * scan_disk_info_get_error_msg ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->error_msg;
	}

	return NULL;
}


gpointer scan_disk_info_get_statment_controler ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->statment_controler;
	}

	return NULL;
}


func_descr_t scan_disk_info_get_scan_disk_get_file_description ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->scan_disk_get_file_description;
	}

	return NULL;
}


func_statment_t scan_disk_info_get_scan_disk_set_current_statment ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL)
	{
		return p->scan_disk_set_current_statment;
	}

	return NULL;
}


gint scan_disk_info_free ( struct scan_disk_info *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( p != NULL )
	{
		scan_disk_info_set_disk_name ( p, NULL);
		scan_disk_info_set_error_msg ( p, NULL);

		g_free ( p);

		return 0;
	}

	return -1;
}

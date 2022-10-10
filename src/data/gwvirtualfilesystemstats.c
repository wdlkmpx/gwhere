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
#include "gwvirtualfilesystemstats.h"

#include <string.h> /* strncmp */


typedef struct vfs_stats
{
	gchar *name;			/* File system name				*/
	gchar *dir;			/* File system path				*/
	gchar *label;			/* File system label				*/
	gchar *serial_number;		/* Serial number				*/
	gchar *type;			/* File system type				*/
	gchar **options;		/* File system options				*/
	gboolean mounted;		/* Status : mounted/umounted			*/
	gulong nb_files;		/* Number of files				*/
	glong blocks_size;		/* Block size					*/
	gulong blocks;			/* Total number of blocks			*/
	gulong blocks_free;		/* Number of free blocks			*/
} VFSStats;


VFSStats * vfs_stats_new ( void)
{
	VFSStats *p = NULL;


#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( (p = (VFSStats*)g_malloc0 ( sizeof ( VFSStats))) != NULL )
	{
		p->name = NULL;
		p->dir = NULL;
		p->label = NULL;
		p->serial_number = NULL;
		p->type = NULL;
		p->options = NULL;
		p->mounted = FALSE;
		p->nb_files = 0;
		p->blocks_size = 0;
		p->blocks = 0;
		p->blocks_free = 0;

		return p;
	}

	return NULL;
}


void vfs_stats_display ( VFSStats *p)
{
	/* Displays all values of the data structure */
	gint i = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		g_print ( "\nName : %s\n", p->name);
		g_print ( "Dir : %s\n", p->dir);
		g_print ( "Label : %s\n", p->label);
		g_print ( "Serial number : %s\n", p->serial_number);
		g_print ( "Type : %s\n", p->type);

		if ( p->options != NULL )
		{
			for ( i = 0; p->options[i] != NULL; i++)
			{
				g_print ( "Option %d : %s\n", i, p->options[i]);
			}
		}

		if ( p->mounted )
		{
			g_print ( "Mounted\n");
		}
		else
		{
			g_print ( "No mounted\n");
		}

		g_print ( "Number of files : %ld\n", p->nb_files);
		g_print ( "Blocks size : %lu\n", p->blocks_size);
		g_print ( "Blocks : %ld\n", p->blocks);
		g_print ( "Blocks free : %lu\n", p->blocks_free);

		return;
	}

	g_print ( "\nvfs stats is (null)\n");
}


gint vfs_stats_set_name ( VFSStats *p, gchar *name)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->name != NULL )
		{
			g_free ( p->name);
		}

		p->name = name;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_dir ( VFSStats *p, gchar *dir)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->dir != NULL )
		{
			g_free ( p->dir);
		}

		p->dir = dir;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_label ( VFSStats *p, gchar *label)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->label != NULL )
		{
			g_free ( p->label);
		}

		p->label = label;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_type ( VFSStats *p, gchar *type)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->type != NULL )
		{
			g_free ( p->type);
		}

		p->type = type;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_options ( VFSStats *p, gchar **options)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->options != NULL )
		{
			g_strfreev ( p->options);
		}

		p->options = options;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_ismounted ( VFSStats *p, gboolean mounted)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->mounted = mounted;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_nb_files ( VFSStats *p, gulong nb_files)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->nb_files = nb_files;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_blocks_size ( VFSStats *p, glong blocks_size)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->blocks_size = blocks_size;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_blocks ( VFSStats *p, gulong blocks)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->blocks = blocks;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_blocks_free ( VFSStats *p, gulong blocks_free)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		p->blocks_free = blocks_free;

		return 0;
	}

	return -1;
}


gint vfs_stats_set_serial_number ( struct vfs_stats *p, gchar *serial_number)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->serial_number != NULL )
		{
			g_free ( p->serial_number);
		}

		p->serial_number = serial_number;

		return 0;
	}

	return -1;
}



gchar * vfs_stats_get_name ( VFSStats *p)
{
	gint i = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( (p->type != NULL) && (strncmp ( p->type, "supermount", 10) == 0) )
		{
			if ( p->options != NULL )
			{
				for ( i = 0; p->options[i] != NULL; i++)
				{
					if ( strncmp ( p->options[i], "dev=", 4) == 0 )
					{
						return p->options[i]+4;
					}
				}
			}
		}
		else
		{
			return p->name;
		}
	}

	return NULL;
}


gchar * vfs_stats_get_dir ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->dir;
	}

	return NULL;
}


gchar * vfs_stats_get_label ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->label;
	}

	return NULL;
}


gchar * vfs_stats_get_type ( VFSStats *p)
{
	gint i = 0;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		if ( p->type != NULL )
		{
			if ( strncmp ( p->type, "supermount", 10) == 0 )
			{
				for ( i = 0; p->options[i] != NULL; i++)
				{
					if ( strncmp ( p->options[i], "fs=", 3) == 0 )
					{
						return p->options[i]+3;
					}
				}
			}
			else { if ( strncmp ( p->type, "auto", 4) == 0 )
			{
				return NULL;
			}
			else
			{
				return p->type;
			}}
		}
	}

	return NULL;
}


gchar * vfs_stats_get_serial_number ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->serial_number;
	}

	return NULL;
}


gchar ** vfs_stats_get_options ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->options;
	}

	return NULL;
}


gboolean vfs_stats_get_ismounted ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->mounted;
	}

	return FALSE;
}


gulong vfs_stats_get_nb_files ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->nb_files;
	}

	return 0;
}


glong vfs_stats_get_blocks_size ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p != NULL )
	{
		return p->blocks_size;
	}

	return 0;
}


gulong vfs_stats_get_blocks ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p!= NULL )
	{
		return p->blocks;
	}

	return 0;
}


gulong vfs_stats_get_blocks_free ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p!= NULL )
	{
		return p->blocks_free;
	}

	return 0;
}


guint64 vfs_stats_get_total_capacity ( VFSStats *p)
{
	guint64 b_size, b_num;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p== NULL )
	{
		return -1;
	}

	b_size = vfs_stats_get_blocks_size ( p);
	b_num = vfs_stats_get_blocks ( p);

	return b_size * b_num;
}


guint64 vfs_stats_get_total_free_space ( VFSStats *p)
{
	guint64 b_size, b_free;


#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p == NULL )
	{
		return -1;
	}

	b_size = vfs_stats_get_blocks_size ( p);
	b_free = vfs_stats_get_blocks_free ( p);

	return b_size * b_free;
}


guint64 vfs_stats_get_total_used_space ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( p == NULL )
	{
		return -1;
	}

	return vfs_stats_get_total_capacity ( p) - vfs_stats_get_total_free_space ( p);
}


gboolean vfs_stats_free ( VFSStats *p)
{
#ifdef GW_DEBUG_DATA_COMPONENT
	static gint i = 0;


	i++;

	g_print ( "*** GW - %s (%d) :: %s() : %d calls\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
#endif

	if ( p != NULL )
	{
		vfs_stats_set_name ( p, NULL);
		vfs_stats_set_dir ( p, NULL);
		vfs_stats_set_label ( p, NULL);
		vfs_stats_set_serial_number ( p, NULL);
		vfs_stats_set_type ( p, NULL);
		vfs_stats_set_options ( p, NULL);

		g_free ( p);

		return TRUE;
	}

	return FALSE;
}

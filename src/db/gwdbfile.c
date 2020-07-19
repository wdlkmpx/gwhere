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


#include "gwsupport.h" /* str_equals */
#include "gwdbfile.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> /* strlen strncmp */


#if defined ( OS_WIN32)
	#define S_IFLNK 0120000
	#define S_IFSOCK 0140000
	#define S_ISUID 0004000
	#define S_ISGID 0002000
	#define S_ISVTX 0001000
	#define S_IRGRP 0000040
	#define S_IWGRP 0000020
	#define S_IXGRP 0000010
	#define S_IROTH 0000004
	#define S_IWOTH 0000002
	#define S_IXOTH 0000001
#endif


typedef struct gw_db_file_s {
	gpointer ref;				/* File reference					*/
	gchar *name;				/* File name						*/
	mode_t rights;				/* File rights						*/
	gchar *owner;				/* File owner						*/
	gchar *group;				/* File owner group					*/
	guint64 size;				/* File size						*/
	glong inode;				/* File inode						*/
	gulong cdate;				/* File creation date					*/
	gulong adate;				/* File access date					*/
	gulong mdate;				/* File modification date				*/
	GWDBCategoryPK category;		/* File category pk					*/
	gchar *description;			/* File description (or comment)			*/
}_GWDBFile;


GWDBFile * gw_db_file_new ( void) {
	GWDBFile *file = NULL;


	if ( (file = (GWDBFile*)g_malloc0 ( sizeof ( GWDBFile))) != NULL ) {
		file->ref = NULL;
		file->name = NULL;
		file->rights = 0;
		file->owner = NULL;
		file->group = NULL;
		file->size = 0;
		file->inode = 0;
		file->cdate = 0;
		file->adate = 0;
		file->mdate = 0;
		file->category = NULL;
		file->description = NULL;
	}

	return file;
}


gint gw_db_file_set_ref ( GWDBFile *file, gpointer ref) {
	if ( file != NULL ) {
		file->ref = ref;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_name ( GWDBFile *file, gchar *name) {
	if ( file != NULL ) {
		if ( file->name != NULL ) {
			g_free ( file->name);
		}

		file->name = name;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_rights ( GWDBFile *file, mode_t rights) {
	if ( file != NULL ) {
		file->rights = rights;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_rights_from_gchar ( GWDBFile *file, gchar *rights) {
	mode_t mode = 000000; //TODO replace by hexa code


	if ( (file != NULL) && (rights != NULL) && strlen ( rights)==10 ) {
		switch (rights[0]) {
			case 'b':	mode|=S_IFBLK;
						break;

			case 'l':	mode|=S_IFLNK;
						break;

			case 'd':	mode|=S_IFDIR;
						break;

			case 'c':	mode|=S_IFCHR;
						break;

			case 'p':	mode|=S_IFIFO;
						break;

			case 's':	mode|=S_IFSOCK;
						break;

			default:	break;
		}

		if ( rights[1]=='r') {
			mode|=S_IRUSR;
		}

		if ( rights[2]=='w') {
			mode|=S_IWUSR;
		}

		switch (rights[3]) {
			case 'x':	mode|=S_IXUSR;
						break;

			case 's':	mode|=S_ISUID;
						mode|=S_IXUSR;
						break;

			case 'S':	mode|=S_ISUID;
						break;

			default:	break;
		}

		if ( rights[4]=='r') {
			mode|=S_IRGRP;
		}

		if ( rights[5]=='w') {
			mode|=S_IWGRP;
		}

		switch (rights[6]) {
			case 'x':	mode|=S_IXGRP;
						break;

			case 's':	mode|=S_ISGID;
						mode|=S_IXGRP;
						break;

			case 'S':	mode|=S_ISGID;
						break;

			default:	break;
		}

		if ( rights[7]=='r') {
			mode|=S_IROTH;
		}

		if ( rights[8]=='w') {
			mode|=S_IWOTH;
		}

		switch (rights[9]) {
			case 'x':	mode|=S_IXOTH;
						break;

			case 't':	mode|=S_ISVTX;
						mode|=S_IXOTH;
						break;

			case 'T':	mode|=S_ISVTX;
						break;

			default:	break;
		}

		file->rights = mode;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_owner ( GWDBFile *file, gchar *owner) {
	if ( file != NULL ) {
		if ( file->owner != NULL ) {
			g_free ( file->owner);
		}

		file->owner = owner;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_group ( GWDBFile *file, gchar *group) {
	if ( file != NULL ) {
		if ( file->group != NULL ) {
			g_free ( file->group);
		}

		file->group = group;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_size ( GWDBFile *file, guint64 size) {
	if ( file != NULL ) {
		file->size = size;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_inode ( GWDBFile *file, glong inode) {
	if ( file != NULL ) {
		file->inode = inode;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_cdate ( GWDBFile *file, gulong cdate) {
	if ( file != NULL ) {
		file->cdate = cdate;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_adate ( GWDBFile *file, gulong adate) {
	if ( file != NULL ) {
		file->adate = adate;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_mdate ( GWDBFile *file, gulong mdate) {
	if ( file != NULL ) {
		file->mdate = mdate;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_category ( GWDBFile *file, GWDBCategoryPK category) {
	if ( file != NULL ) {
		file->category = category;

		return 0;
	}

	return -1;
}


gint gw_db_file_set_description ( GWDBFile *file, gchar *description) {
	if ( file != NULL ) {
		if ( file->description != NULL ) {
			g_free ( file->description);
		}

		file->description = description;

		return 0;
	}

	return -1;
}


gpointer gw_db_file_get_ref ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->ref;
	}

	return NULL;
}


gchar * gw_db_file_get_name ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->name;
	}

	return NULL;
}


gboolean gw_db_file_is_directory ( GWDBFile *file) {
	if ( file != NULL ) {
		return ( (S_IFMT & file->rights) == S_IFDIR );
	}

	/* Ugly coder!!*/
	return FALSE;
}


gboolean gw_db_file_is_real_directory ( GWDBFile *file) {
	if ( file != NULL) {
		if ( gw_db_file_is_directory ( file) ) {
			if ( gw_db_file_get_name ( file) != NULL ) {
				switch ( strlen ( gw_db_file_get_name ( file))) {
					case 0:		/* Impossible case!! */
								return FALSE;
								break;

					case 1:		return !(strncmp ( gw_db_file_get_name ( file), ".", 1) == 0);
								break;

					case 2:		return !(strncmp ( gw_db_file_get_name ( file), "..", 2) == 0);
								break;

					default:	return TRUE;
								break;
				}
			}
		}
	}

	/* Ugly coder!!*/
	return FALSE;
}


gboolean gw_db_file_is_real_file ( GWDBFile *file) {
	if ( file != NULL ) {
		return ( (S_IFMT & file->rights) != S_IFDIR && (S_IFMT & file->rights) != S_IFCHR && (S_IFMT & file->rights) != S_IFIFO && (S_IFMT & file->rights) != S_IFSOCK);
	}

	/* Ugly coder!!*/
	return FALSE;
}


mode_t gw_db_file_get_rights ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->rights;
	}

	//TODO find the appropriate value...
	return -1;
}


gchar* gw_db_file_get_rights_to_gchar ( GWDBFile *file) {
	gchar* rigths = NULL;


	if ( file != NULL ) {
		rigths = g_strdup ( "----------");
#if defined ( OS_LINUX) || defined ( OS_CYGWIN)
		if ( S_ISLNK ( file->rights) ) {
			rigths[0] = 'l';
		} else {
#endif
			switch ( S_IFMT & file->rights ) {
				case S_IFBLK:	rigths[0] = 'b';
								break;

				case S_IFLNK:	rigths[0] = 'l';
								break;

				case S_IFDIR:	rigths[0] = 'd';
								break;

				case S_IFCHR:	rigths[0] = 'c';
								break;

				case S_IFIFO:	rigths[0] = 'p';
								break;

				case S_IFSOCK:	rigths[0] = 's';
								break;
			}
#if defined ( OS_LINUX) || defined ( OS_CYGWIN)
		}
#endif

		/* Owner rights */
		if (S_IRUSR & file->rights) rigths[1] = 'r';
		if (S_IWUSR & file->rights) rigths[2] = 'w';
		if (S_ISUID & file->rights){
			if (S_IXUSR & file->rights) {
				rigths[3] = 's';
			} else {
				rigths[3] = 'S';
			}
		} else {
			if (S_IXUSR & file->rights) {
				rigths[3] = 'x';
			}
		}

		/* Group rights */
		if (S_IRGRP & file->rights) rigths[4] = 'r';
		if (S_IWGRP & file->rights) rigths[5] = 'w';
		if (S_ISGID & file->rights) {
			if (S_IXGRP & file->rights) {
				rigths[6] = 's';
			} else {
				rigths[6] = 'S';
			}
		} else {
			if (S_IXGRP & file->rights) {
				rigths[6] = 'x';
			}
		}

		/* Others rights */
		if (S_IROTH & file->rights) rigths[7] = 'r';
		if (S_IWOTH & file->rights) rigths[8] = 'w';
		if (S_ISVTX & file->rights) {
			if (S_IXOTH & file->rights) {
				rigths[9] = 't';
			} else {
				rigths[9] = 'T';
			}
		} else {
			if (S_IXOTH & file->rights) {
				rigths[9] = 'x';
			}
		}
	}

	return rigths;
}


gchar * gw_db_file_get_owner ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->owner;
	}

	return NULL;
}


gchar * gw_db_file_get_group ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->group;
	}

	return NULL;
}


guint64 gw_db_file_get_size ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->size;
	}

	return 0;
}


glong gw_db_file_get_inode ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->inode;
	}

	return -1;
}


gulong gw_db_file_get_cdate ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->cdate;
	}

	return 0;
}


gulong gw_db_file_get_adate ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->adate;
	}

	return 0;
}


gulong gw_db_file_get_mdate ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->mdate;
	}

	return 0;
}


GWDBCategoryPK gw_db_file_get_category ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->category;
	}

	return NULL;
}


gchar * gw_db_file_get_description ( GWDBFile *file) {
	if ( file != NULL ) {
		return file->description;
	}

	return NULL;
}


GWDBFile * gw_db_file_dup ( GWDBFile *file, GWDBFile **dup) {
	GWDBFile *dup_file = NULL;


	if ( file != NULL ) {
		dup_file = *dup;
		if ( dup_file == NULL ) {
			/* Don't check if gw_db_file_new return NULL because all following functions check it too. */
			(*dup) = dup_file = gw_db_file_new ( );
		}

		gw_db_file_set_ref ( dup_file, gw_db_file_get_ref ( file));
		if ( gw_db_file_get_name ( file) != NULL ) {
			gw_db_file_set_name ( dup_file, g_strdup ( gw_db_file_get_name ( file)));
		} else {
			gw_db_file_set_name ( dup_file, NULL);
		}
		gw_db_file_set_rights ( dup_file, gw_db_file_get_rights ( file));
		if ( gw_db_file_get_owner ( file) != NULL ) {
			gw_db_file_set_owner ( dup_file, g_strdup ( gw_db_file_get_owner ( file)));
		} else {
			gw_db_file_set_owner ( dup_file, NULL);
		}
		if ( gw_db_file_get_group ( file ) != NULL ) {
			gw_db_file_set_group ( dup_file, g_strdup ( gw_db_file_get_group ( file)));
		} else {
			gw_db_file_set_group ( dup_file, NULL);
		}
		gw_db_file_set_size ( dup_file, gw_db_file_get_size ( file));
		gw_db_file_set_inode ( dup_file, gw_db_file_get_inode ( file));
		gw_db_file_set_adate ( dup_file, gw_db_file_get_adate ( file));
		gw_db_file_set_cdate ( dup_file, gw_db_file_get_cdate ( file));
		gw_db_file_set_mdate ( dup_file, gw_db_file_get_mdate ( file));
		gw_db_file_set_category ( dup_file, gw_db_file_get_category ( file));
		if ( gw_db_file_get_description ( file) != NULL ) {
			gw_db_file_set_description ( dup_file, g_strdup ( gw_db_file_get_description ( file)));
		} else {
			gw_db_file_set_description ( dup_file, NULL);
		}
	}

	return dup_file;
}


gint gw_db_file_free ( GWDBFile *file) {
	if ( file != NULL ) {
		gw_db_file_set_name ( file, NULL);
		gw_db_file_set_owner ( file, NULL);
		gw_db_file_set_group ( file, NULL);
		gw_db_file_set_description ( file, NULL);

		g_free ( file);

		return 0;
	}

	return -1;
}


gboolean gw_db_file_equals ( GWDBFile *file, GWDBFile *to) {
	gboolean equals = FALSE;


	if ( file != NULL && to != NULL) {
		if ( gw_db_file_get_ref ( file) == gw_db_file_get_ref ( to)
			&& str_equals ( gw_db_file_get_name ( file), gw_db_file_get_name ( to))
			&& gw_db_file_get_rights ( file) == gw_db_file_get_rights ( to)
			&& str_equals ( gw_db_file_get_owner ( file), gw_db_file_get_owner ( to))
			&& str_equals ( gw_db_file_get_group ( file), gw_db_file_get_group ( to))
			&& gw_db_file_get_size ( file) == gw_db_file_get_size ( to)
			&& gw_db_file_get_inode ( file) == gw_db_file_get_inode ( to)
			&& gw_db_file_get_cdate ( file) == gw_db_file_get_cdate ( to)
			&& gw_db_file_get_adate ( file) == gw_db_file_get_adate ( to)
			&& gw_db_file_get_mdate ( file) == gw_db_file_get_mdate ( to)
			&& gw_db_file_get_category ( file) == gw_db_file_get_category ( to)
			&& str_equals ( gw_db_file_get_description ( file), gw_db_file_get_description ( to))
			 ) {
			equals = TRUE;
		}
	}

	return equals;
}

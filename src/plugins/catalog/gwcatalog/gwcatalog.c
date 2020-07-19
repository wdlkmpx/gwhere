#include <glib.h>
#include <zlib.h>
#include <stdlib.h> /* strtol strtoul strtoull */
#include <string.h> /* strrchr */
#include <sys/stat.h> /* stat */
#include "plugins/gwcatalog.h"
#include "data/gwdata.h"
#include "tools/gwtools.h"
#include "gwsupport.h"


#define PROJECT_NAME "GWhere"


#if defined ( OS_WIN32)
	#define FORMAT1_DISK_SHORT "//\n%s:%d:%s:%s:%"##G_GUINT64_FORMAT##":%"##G_GUINT64_FORMAT##":%ld:%s:"
	#define FORMAT1_DISK_LONG "//\n%s:%d:%s:%s:%"##G_GUINT64_FORMAT##":%"##G_GUINT64_FORMAT##":%ld:%s:%s\n"
	#define FORMAT1_FILE_SHORT  "%s:%s:%s:%s:%ld:%"##G_GUINT64_FORMAT##":%ld:%ld:%ld:"
	#define FORMAT1_FILE_LONG "%s:%s:%s:%s:%ld:%"##G_GUINT64_FORMAT##":%ld:%ld:%ld:%s\n"
	#define FORMAT2_DISK_SHORT "//\n%s:%d:%s:%s:%s:%s:%"##G_GUINT64_FORMAT##":%"##G_GUINT64_FORMAT##":%ld:%s:%d:"
	#define FORMAT2_DISK_LONG "//\n%s:%d:%s:%s:%s:%s:%"##G_GUINT64_FORMAT##":%"##G_GUINT64_FORMAT##":%ld:%s:%d:%s\n"
	#define FORMAT2_FILE_SHORT "%s:%s:%s:%s:%ld:%"##G_GUINT64_FORMAT##":%ld:%ld:%ld:%d:"
	#define FORMAT2_FILE_LONG "%s:%s:%s:%s:%ld:%"##G_GUINT64_FORMAT##":%ld:%ld:%ld:%d:%s\n"
#else
	#ifdef __STDC__
		#define CONCAT3(x,y,z) x/**/y/**/z/**/
		#define CONCAT5(v,w,x,y,z) v/**/w/**/x/**/y/**/z/**/
	#else
		#define CONCAT3(x,y,z) x/**/y/**/z/**/
		#define CONCAT5(v,w,x,y,z) v/**/w/**/x/**/y/**/z/**/
	#endif

	#define FORMAT1_DISK_SHORT  CONCAT5("//\n%s:%d:%s:%s:%",G_GUINT64_FORMAT,":%",G_GUINT64_FORMAT,":%ld:%s:")
	#define FORMAT1_DISK_LONG  CONCAT5("//\n%s:%d:%s:%s:%",G_GUINT64_FORMAT,":%",G_GUINT64_FORMAT,":%ld:%s:%s\n")
	#define FORMAT1_FILE_SHORT  CONCAT3("%s:%s:%s:%s:%ld:%",G_GUINT64_FORMAT,":%ld:%ld:%ld:")
	#define FORMAT1_FILE_LONG  CONCAT3("%s:%s:%s:%s:%ld:%",G_GUINT64_FORMAT,":%ld:%ld:%ld:%s\n")
	#define FORMAT2_DISK_SHORT  CONCAT5("//\n%s:%d:%s:%s:%s:%s:%",G_GUINT64_FORMAT,":%",G_GUINT64_FORMAT,":%ld:%s:%d:")
	#define FORMAT2_DISK_LONG  CONCAT5("//\n%s:%d:%s:%s:%s:%s:%",G_GUINT64_FORMAT,":%",G_GUINT64_FORMAT,":%ld:%s:%d:%s\n")
	#define FORMAT2_FILE_SHORT  CONCAT3("%s:%s:%s:%s:%ld:%",G_GUINT64_FORMAT,":%ld:%ld:%ld:%d:")
	#define FORMAT2_FILE_LONG  CONCAT3("%s:%s:%s:%s:%ld:%",G_GUINT64_FORMAT,":%ld:%ld:%ld:%d:%s\n")
#endif


typedef struct {
	GWDBCatalog *catalog;
	GList *categories;
	GNode *tree;
	gzFile zfile;
	GWStringBuffer *sb;
	gchar *mode;
}_data;


gint gw_db_data_category_free ( GWDBCategory *category, gpointer data) {
	if ( category != NULL ) {
		gw_db_category_free ( category);

		return 0;
	}

	return -1;
}


gboolean g_node_file_free ( GNode *file, gpointer data) {
	if ( file != NULL) {
		gw_db_category_remove_file ( gw_db_file_get_category ( file->data));
		gw_db_file_free ( file->data);
	}

	return FALSE;
}


gboolean g_node_files_free ( GNode *file, gpointer data) {
	if ( file != NULL) {
		g_node_traverse ( file, G_LEVEL_ORDER, G_TRAVERSE_ALL, -1, (GNodeTraverseFunc)g_node_file_free, NULL);
	}

	return FALSE;
}


gboolean g_node_disk_free ( GNode *disk, gpointer data) {
	if ( disk != NULL) {
		g_node_children_foreach ( disk, G_TRAVERSE_ALL, (GNodeForeachFunc)g_node_files_free, NULL);
		g_node_unlink ( disk);
		gw_db_category_remove_disk ( gw_db_disk_get_category ( disk->data));
		gw_db_disk_free ( disk->data);
		g_node_destroy ( disk);
	}

	return FALSE;
}


gboolean g_node_count_files ( GNode *file, gpointer data) {
	glong *pcount = data;


	if ( file != NULL) {
		if ( !gw_db_file_is_directory ( file->data)) {
			(*pcount)++;
		}
	}

	return FALSE;
}


gboolean g_node_count_folders ( GNode *file, gpointer data) {
	glong *pcount = data;


	if ( file != NULL) {
		if ( gw_db_file_is_real_directory ( file->data)) {
			(*pcount)++;
		}
	}

	return FALSE;
}


GWDBFile* gw_db_file_from_str ( gchar *str, gint file_version, GWDBContext *context) {
	GWDBFile *file = NULL;
	gint i = 0, j = 0, begin = 0;
	gchar *tmp = NULL;
	GWDBCategory *category = NULL;
	_data *data = gw_db_context_get_data ( context);


	if ( (file = gw_db_file_new ( )) != NULL ) {
		i = 0;
		begin = i;

		/* Read the file name. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			if ( str[j] == '\\') {
				if ( str[j+1] == '#') {
					str[i++] = ':';
					j++;
				} else if ( str[j+1] == 'n') {
					str[i++] = '\n';
					j++;
				} else {
					str[i++] = str[j];
				}
			} else {
				str[i++] = str[j];
			}
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_file_set_name ( file, tmp);
		tmp = NULL;

		i = j + 1;
		begin = i;

		/* Read the file rights. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		if ( tmp != NULL )
		{
			gw_db_file_set_rights_from_gchar ( file, tmp);
			g_free ( tmp);
			tmp = NULL;
		}

		i = j + 1;
		begin = i;

		/* Read the file owner. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_file_set_owner ( file, tmp);

		i = j + 1;
		begin = i;

		/* Read the file group. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_file_set_group ( file, tmp);

		i = j + 1;
		begin = i;

		/* Read the file inode. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_file_set_inode ( file, strtol ( &str[begin], NULL, 10));
		} else {
			tmp = NULL;
		}

		i = j + 1;
		begin = i;

		/* Read the file size. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_file_set_size ( file, strtoui64 ( &str[begin], NULL, 10));
		} else {
		}

		i = j + 1;
		begin = i;

		/* Read the file cdate. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_file_set_cdate ( file, strtoul ( &str[begin], NULL, 10));
		} else {
		}

		i = j + 1;
		begin = i;

		/* Read the file adate. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_file_set_adate ( file, strtoul ( &str[begin], NULL, 10));
		} else {
		}

		i = j + 1;
		begin = i;

		/* Read the file mdate. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_file_set_mdate ( file, strtoul ( &str[begin], NULL, 10));
		} else {
			if ( file_version == 1) {
				if ( str[j] == '\0') {
					gw_db_file_set_mdate ( file, strtoul ( &str[begin], NULL, 10));
				}
			}
		}

		if ( file_version == 2) {
			i = j + 1;
			begin = i;

			/* Read the file category. */
			for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
				i++;
			}

			if ( str[j] == ':') {
				str[j] = '\0';
				if ( context != NULL ) {
					category = g_list_nth ( data->categories, strtol ( &str[begin], NULL, 10))->data;
					gw_db_file_set_category ( file, gw_db_category_get_ref ( category));
					gw_db_category_add_file ( category);
				}
			} else {}
		} else {}

		i = j + 1;
		begin = i;

		/* Read the file description. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			if ( str[j] == '\\') {
				if ( str[j+1] == '#') {
					str[i++] = ':';
					j++;
				} else if ( str[j+1] == 'n') {
					str[i++] = '\n';
					j++;
				} else {
					str[i++] = str[j];
				}
			} else {
				str[i++] = str[j];
			}
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_file_set_description ( file, tmp);
	}

	return file;
}


GWDBDisk* gw_db_disk_from_str ( gchar *str, gint file_version, GWDBContext *context) {
	GWDBDisk *disk = NULL;
	gint i = 0, j = 0, begin = 0;
	gchar *tmp = NULL;
	GWDBCategory *category = NULL;
	_data *data = gw_db_context_get_data ( context);


	if ( (disk = gw_db_disk_new ( )) != NULL ) {
		i = 0;
		begin = i;

		/* Read the disk name. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			if ( str[j] == '\\') {
				if ( str[j+1] == '#') {
					str[i++] = ':';
					j++;
				} else if ( str[j+1] == 'n') {
					str[i++] = '\n';
					j++;
				} else {
					str[i++] = str[j];
				}
			} else {
				str[i++] = str[j];
			}
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_disk_set_name ( disk, tmp);
		tmp = NULL;

		i = j + 1;
		begin = i;

		/* Read the disk archive number. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_disk_set_num ( disk, strtol ( &str[begin], NULL, 10));
		} else {
			tmp = NULL;
		}

		if ( file_version == 1) {
		} else if ( file_version == 2 ) {
			i = j + 1;
			begin = i;

			/* Read the disk file system name. */
			for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
				if ( str[j] == '\\') {
					if ( str[j+1] == '#') {
						str[i++] = ':';
						j++;
					} else if ( str[j+1] == 'n') {
						str[i++] = '\n';
						j++;
					} else {
						str[i++] = str[j];
					}
				} else {
					str[i++] = str[j];
				}
			}

			if ( begin < i) {
				if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
					memcpy(tmp,&str[begin],i-begin);
				} else {
					tmp = NULL;
				}
			} else {
				tmp = NULL;
			}

			gw_db_disk_set_fsname ( disk, tmp);
			tmp = NULL;
		}

		if ( file_version == 1) {
		} else if ( file_version == 2 ) {
			i = j + 1;
			begin = i;

			/* Read the disk access directory. */
			for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
				if ( str[j] == '\\') {
					if ( str[j+1] == '#') {
						str[i++] = ':';
						j++;
					} else if ( str[j+1] == 'n') {
						str[i++] = '\n';
						j++;
					} else {
						str[i++] = str[j];
					}
				} else {
					str[i++] = str[j];
				}
			}

			if ( begin < i) {
				if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
					memcpy(tmp,&str[begin],i-begin);
				} else {
					tmp = NULL;
				}
			} else {
				tmp = NULL;
			}

			gw_db_disk_set_path ( disk, tmp);
			tmp = NULL;
		}

		i = j + 1;
		begin = i;

		/* Read the disk type. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			if ( str[j] == '\\') {
				if ( str[j+1] == '#') {
					str[i++] = ':';
					j++;
				} else if ( str[j+1] == 'n') {
					str[i++] = '\n';
					j++;
				} else {
					str[i++] = str[j];
				}
			} else {
				str[i++] = str[j];
			}
		}

		if ( begin < i) {
			if ( (file_version==1) && (i-begin>=6) && (memcmp(&str[begin],"CD-ROM",6)==0) ) {
				/* CD-ROM [ fstype ] */
				tmp = g_strdup("iso9660");
			} else if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		//TODO to check the following code..
		if ( (i-begin>=6) && (memcmp ( &str[begin], "CD-ROM", 6) == 0) ) {
			/* CD-ROM [ fstype ] */
			gw_db_disk_set_type ( disk, CDROM);
		} else if ( (i-begin==4) && (memcmp ( &str[begin], "cdfs", 4) == 0) ) {
			gw_db_disk_set_type ( disk, CDROM);
		} else if ( (i-begin>2) && (memcmp ( &str[begin], "HD", 2) == 0) ) {
			gw_db_disk_set_type ( disk, HD);
		} else if ( (i-begin==6) && (memcmp ( &str[begin], "Floppy", 6) == 0) ) {
			gw_db_disk_set_type ( disk, FLOPPY);
		} else if ( (i-begin==3) && (memcmp ( &str[begin], "Zip", 3) == 0) ) {
			gw_db_disk_set_type ( disk, ZIP_DRIVE);
		} else if ( (i-begin==3) && (memcmp ( &str[begin], "smb", 3) == 0) ) {
			gw_db_disk_set_type ( disk, NETWORK_DRIVE);
		} else if ( (i-begin==4) && (memcmp ( &str[begin], "ntfs", 4) == 0) ) {
			gw_db_disk_set_type ( disk, HD);
		} else {
			if ( (tmp = gw_db_disk_get_fsname ( disk)) != NULL) {
				if ( strncmp ( "/dev/hd", tmp, 7) == 0 ) {
					gw_db_disk_set_type ( disk, HD);
				} else if ( strncmp ("/dev/fd", tmp, 7) == 0 ) {
					gw_db_disk_set_type ( disk, FLOPPY);
				} else if ( strncmp ( "/dev/zip", tmp, 8) == 0 ) {
					gw_db_disk_set_type ( disk, ZIP_DRIVE);
				} else if ( strncmp ( "\\\\.\\A:\\", tmp, 7) == 0 ) {
					gw_db_disk_set_type ( disk, FLOPPY);
				} else if ( strncmp ( "\\\\.\\B:\\", tmp, 7) == 0 ) {
					gw_db_disk_set_type ( disk, FLOPPY);
				} else {
					gw_db_disk_set_type ( disk, NONE);
				}
			} else {
				gw_db_disk_set_type ( disk, NONE);
			}
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_disk_set_fstype ( disk, tmp);
		tmp = NULL;

		if ( file_version == 1 ) {
			/* We can guess disk_fsname but not disk_path. */
			if ( (i-begin<=6) && (memcmp ( &str[begin], "CD-ROM", 6) == 0) ) {
				gw_db_disk_set_fsname ( disk, g_strdup ( "/dev/cdrom"));
			} else if ( (i-begin>2) && (memcmp ( &str[begin], "HD", 2) == 0) ) {
				gw_db_disk_set_fsname ( disk, g_strdup ( "/dev/hd"));
			} else if ( (i-begin==6) && (memcmp ( &str[begin], "Floppy", 6) == 0) ) {
				gw_db_disk_set_fsname ( disk, g_strdup ( "/dev/fd"));
			} else if ( (i-begin==3) && (memcmp ( &str[begin], "Zip", 3) == 0) ) {
				gw_db_disk_set_fsname ( disk, g_strdup ( "/dev/zip"));
			} else {
			}
		}

		i = j + 1;
		begin = i;

		/* Read the disk volume name. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			if ( str[j] == '\\') {
				if ( str[j+1] == '#') {
					str[i++] = ':';
					j++;
				} else if ( str[j+1] == 'n') {
					str[i++] = '\n';
					j++;
				} else {
					str[i++] = str[j];
				}
			} else {
				str[i++] = str[j];
			}
		}

		if ( begin < i) {
			if ( memcmp ( &str[begin], "(null)", 6) != 0 ) {
				if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
					memcpy(tmp,&str[begin],i-begin);
				} else {
					tmp = NULL;
				}
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_disk_set_volume ( disk, tmp);
		tmp = NULL;

		i = j + 1;
		begin = i;

		/* Read the disk used space. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_disk_set_full ( disk, strtoui64 ( &str[begin], NULL, 10));
		} else {}

		i = j + 1;
		begin = i;

		/* Read the disk free space. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_disk_set_free ( disk, strtoui64 ( &str[begin], NULL, 10));
		} else {}

		i = j + 1;
		begin = i;

		/* Read the disk adding date. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			i++;
		}

		if ( str[j] == ':') {
			str[j] = '\0';
			gw_db_disk_set_date ( disk, strtoul ( &str[begin], NULL, 10));
		} else {}

		i = j + 1;
		begin = i;

		/* Read the disk serial number. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			if ( str[j] == '\\') {
				if ( str[j+1] == '#') {
					str[i++] = ':';
					j++;
				} else if ( str[j+1] == 'n') {
					str[i++] = '\n';
					j++;
				} else {
					str[i++] = str[j];
				}
			} else {
				str[i++] = str[j];
			}
		}

		if ( begin < i) {
			if ( memcmp ( &str[begin], "(null)", 6) != 0 ) {
				if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
					memcpy(tmp,&str[begin],i-begin);
				} else {
					tmp = NULL;
				}
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_disk_set_serial ( disk, tmp);
		tmp = NULL;

		if ( file_version == 2) {
			i = j + 1;
			begin = i;

			/* Read the disk category. */
			for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
				i++;
			}

			if ( str[j] == ':') {
				str[j] = '\0';
				if ( context != NULL ) {
					category = g_list_nth ( data->categories, strtol ( &str[begin], NULL, 10))->data;
					gw_db_disk_set_category ( disk, gw_db_category_get_ref ( category));
					gw_db_category_add_disk ( category);
				}
			} else {}
		} else {}

		i = j + 1;
		begin = i;

		/* Read the disk description. */
		for ( j = i; ((str[j] != ':') && (str[j] != '\0')); j++ ) {
			if ( str[j] == '\\') {
				if ( str[j+1] == '#') {
					str[i++] = ':';
					j++;
				} else if ( str[j+1] == 'n') {
					str[i++] = '\n';
					j++;
				} else {
					str[i++] = str[j];
				}
			} else {
				str[i++] = str[j];
			}
		}

		if ( begin < i) {
			if ( (tmp = (gchar*)g_malloc0(sizeof(gchar)*(i-begin+1))) != NULL ) {
				memcpy(tmp,&str[begin],i-begin);
			} else {
				tmp = NULL;
			}
		} else {
			tmp = NULL;
		}

		gw_db_disk_set_description ( disk, tmp);
		tmp = NULL;
	}

	return disk;
}


gint catalog_load_dir ( GWDBContext *context, GNode *parent, gint version) {
	_data *data = gw_db_context_get_data ( context);
	gzFile fic = data->zfile;
	GWStringBuffer *sb = data->sb;
	guint ret, compt = 0;
	gchar *buf = NULL;
	GWDBFile *file = NULL;
	GNode *folder = NULL, *fileN = NULL;


	while ( strcmp ( (buf = gw_zfile_readline_sb ( fic, &sb)), "\\") != 0 ) {
		if ( strcmp ( buf, "/") == 0 ) {
			/* Case : is a folder */
			compt++;
			buf = gw_zfile_readline_sb ( fic, &sb);

			/* Allocates datas structures */
			file = gw_db_file_from_str ( buf, version, context);

			/* Create folder node */
			folder = g_node_new ( file);
			gw_db_file_set_ref ( file, folder);
			g_node_append ( parent, folder);

			/* Loads folder with a recursive call */
			if ( (ret = catalog_load_dir ( context, folder, version)) == 0) {
				/* Empty directory */
			}
		} else {
			/* Case : is a file */
			/* Allocates datas structure */
			file = gw_db_file_from_str ( buf, version, context);

			/* Adds to files list the file informations */
			fileN = g_node_new ( file);
			gw_db_file_set_ref ( file, fileN);
			g_node_append ( parent, fileN);
		}
	}

	return compt;
}


gint catalog_load_disk ( GWDBContext *context, GNode *parent, gint version) {
	_data *data = gw_db_context_get_data ( context);
	gzFile fic = data->zfile;
	GWStringBuffer *sb = data->sb;
	guint ret, compt = 0;
	gchar *buf = NULL;
	GWDBFile *file = NULL;
	GNode *folder = NULL, *fileN = NULL;


	while ( strcmp ( (buf = gw_zfile_readline_sb ( fic, &sb)), "\\") != 0 )	{
		if ( strcmp ( buf, "/") == 0 ) {
			/* Case : is a folder */
			compt++;
			buf = gw_zfile_readline_sb ( fic, &sb);

			/* Allocates datas structure */
			file = gw_db_file_from_str ( buf, version, context);

			/* Creates folder node */
			folder = g_node_new ( file);
			gw_db_file_set_ref ( file, folder);
			g_node_append ( parent, folder);

			/* Loads folder */
			if ( (ret = catalog_load_dir ( context, folder, version)) == 0) {
				/* Empty directory */
			}
		} else {
			/* Case : is a file */
			/* Allocates datas structure */
			file = gw_db_file_from_str ( buf, version, context);

			/* Adds to files list the file informations */
			fileN = g_node_new ( file);
			gw_db_file_set_ref ( file, fileN);
			g_node_append ( parent, fileN);
		}
	}

	return compt;
}


gint catalog_load ( GWDBContext *context, gint version) {
	_data *data = NULL;
	GNode *tree = NULL;
	GNode *parent = NULL;
	gchar *buf = NULL;
	GWStringBuffer *sb = NULL;
	gchar **tmp = NULL;
	GWDBDisk *disk = NULL;
	gzFile fic;
	gchar *tmp_buf = NULL;
	GWDBCatalog *catalog = NULL;
	GWDBCategory *category = NULL;
	GWCatalogPlugin *plugin = NULL;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		plugin = gw_db_context_get_plugin ( context);
		catalog = data->catalog;

		/* Creates root node. */
		tree = g_node_new ( NULL);
		data->tree = tree;
		sb = data->sb;
		fic = data->zfile;

		/* Loads catalog informations */
		if ( version == 1 ) {
		} else if ( version == 2 ) {
			if ( (buf = gw_zfile_readline_sb ( fic, &sb)) != NULL ) {
				tmp = g_strsplit ( buf, ":", 0);

				if ( tmp != NULL ) {
					/* Reads catalog name */
					if ( tmp[0] != NULL) {
						if ( strcmp ( tmp[0], "" ) != 0 ) {
							/* Case : the catalog gets a name */
							tmp_buf = gw_file_to_str ( tmp[0]);
							gw_db_catalog_set_name ( catalog, tmp_buf);
						} else {
							/* Case : default catalog name is file name */
						}
					}

					/* Reads catalog description */
					if ( tmp[1] != NULL ) {
						if ( strcmp ( tmp[1], "" ) != 0 ) {
							tmp_buf = gw_file_to_str ( tmp[1]);
							gw_db_catalog_set_description ( catalog, tmp_buf);
						}
					}

					g_strfreev ( tmp);
				}
			}
		}

		while ( (buf = gw_zfile_readline_sb ( fic, &sb)) != NULL ) {
			if ( strcmp ( buf, "//") == 0 ) {
				gw_zfile_readline_sb ( fic, &sb);

				/* Creates a disk node */
				disk = gw_db_disk_from_str ( buf, version, context);
				g_node_append ( tree, parent = g_node_new ( disk));
				gw_db_disk_set_ref ( disk, parent);

				/* Loads disk */
				if ( catalog_load_disk ( context, parent, version) == -1 ) {
					return -1;
				}
			} else {
				if ( version == 1) {
					/* Loads descriptions */
				} else if ( version == 2 ) {
					/* Loads categories */
					tmp = g_strsplit ( buf, ":", 2);
					if ( tmp[0] != NULL ) {
						category = gw_db_category_new ( );
						tmp_buf = gw_file_to_str ( tmp[0]);
						gw_db_category_set_name ( category, tmp_buf);

						if ( tmp[1] != NULL ) {
							if ( strcmp ( tmp[1], "" ) != 0 ) {
								tmp_buf = gw_file_to_str ( tmp[1]);
								gw_db_category_set_description ( category, tmp_buf);
							}
						}

						plugin->gw_db_catalog_add_db_category ( context, category);
						gw_db_category_free ( category);
					}

					g_strfreev ( tmp);
				}
			}
		}
	} else {}

	return 0;
}


gint catalog_save_file_dir_2 ( GWDBContext *context, GNode *parent, gzFile fic, GWStringBuffer *buf[2]) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBFile *file = NULL;
	GNode *node = NULL;
	gchar *tmp[3];
	gint i = 0, nb = 0;
	GWDBCategory *category = NULL;


	/* Gets folder files list */
	nb = g_node_n_children ( parent);
	for ( i = 0; i < nb; i++) {
		node = g_node_nth_child ( parent, i);
		file = node->data;

		/* Writes file informations */
		/* Checks if it's a folder different from "." and ".." */
		if ( gw_db_file_is_real_directory ( file) == TRUE ) {
			if ( gzputs ( fic, "/\n") == -1 ) {
					return -1;
			}
		}

		/* Gets file informations */
		tmp[0] = gw_str_to_file_strb ( gw_db_file_get_name ( file), buf[0]);
		tmp[1] = gw_str_to_file_strb ( gw_db_file_get_description ( file), buf[1]);
		tmp[2] = gw_db_file_get_rights_to_gchar ( file);
		category = plugin->gw_db_catalog_get_db_category ( context, gw_db_file_get_category ( file));

		if ( gzprintf ( fic, FORMAT2_FILE_LONG,
					tmp[0],
					tmp[2],
					gw_db_file_get_owner ( file),
					gw_db_file_get_group ( file),
					gw_db_file_get_inode ( file),
					gw_db_file_get_size ( file),
					gw_db_file_get_cdate ( file),
					gw_db_file_get_adate ( file),
					gw_db_file_get_mdate ( file),
					(gw_db_category_get_index ( category)==-1?0:gw_db_category_get_index ( category)),
					tmp[1]) == 0 ) {
			gw_db_category_free ( category);
			return -1;
		}
		gw_db_category_free ( category);

		if ( gw_db_file_is_real_directory ( file) == TRUE ) {
			/* Saves all subfolders */
			catalog_save_file_dir_2 ( context, node, fic, buf);
			if ( gzputs ( fic, "\\\n") == -1 ) {
				return -1;
			}
		}
	}

	return 0;
}


gint catalog_save_file_disk_2 ( GWDBContext *context, GWDBDisk *disk, gint fic, GWStringBuffer **buf) {
	return -1;
}


gint catalog_save_file_version_2 ( GWDBContext *context) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	gzFile fic;
	GWDBCatalog *catalog = NULL;
	GWDBDisk *disk = NULL;
	GList *categories;
	gint size = 0;
	gchar *tmp[7];
	GWStringBuffer *strbuf[2];
	_data *data = gw_db_context_get_data ( context);
	GNode *tree = NULL, *node = NULL;
	gint i = 0, nb = 0;
	gchar *fullfiletmpname = NULL;
	GWDBCategory *category = NULL;


#if GW_DEBUG_TIME
	time_t begin;
	time ( &begin);
#endif

	catalog = data->catalog;

	/* Makes a save in a tempory file to prevent database lost in case of crash. */
	fullfiletmpname = g_strconcat ( gw_db_catalog_get_db_name ( catalog), ".tmp", NULL);

	/* Creates file */
	if ( (fic = gzopen ( fullfiletmpname, data->mode)) == NULL ) {
		return -1;
	}

	/* Writes file version */
	if ( gzprintf ( fic, "%s:%s:2\n", PROJECT_NAME, VERSION) == 0 ) {
		if ( gzclose ( fic) != Z_OK) {
		}

		return -1;
	}

	/* Writes catalog informations */
	tmp[0] = gw_str_to_file ( gw_db_catalog_get_name ( catalog));
	tmp[1] = gw_str_to_file ( gw_db_catalog_get_description ( catalog));
	if ( gzprintf ( fic, "%s:%s\n",
				(tmp[0]==NULL)?(gw_db_catalog_get_name ( catalog)==NULL?"":gw_db_catalog_get_name ( catalog)):tmp[0],
				(tmp[1]==NULL)?(gw_db_catalog_get_description ( catalog)==NULL?"":gw_db_catalog_get_description ( catalog)):tmp[1]) == 0 ) {
		if ( gzclose ( fic) != Z_OK ) {
		}

		if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
		if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}

		return -1;
	}

	if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
	if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}

	/* Writes catelories list */
	if ( (categories = data->categories) != NULL) {
		/* Had to save categories */
		/* Puts one catagory by line */
		categories = g_list_first ( categories);
		size = g_list_length ( categories);

		for ( i = 1; i < size; i++ ) {
			categories = g_list_next ( categories);

			tmp[0] = gw_str_to_file ( gw_db_category_get_name ( categories->data));
			tmp[1] = gw_str_to_file ( gw_db_category_get_description ( categories->data));
			if ( gzprintf ( fic, "%s:%s\n",
						(tmp[0]==NULL)?(gw_db_category_get_name ( categories->data)==NULL?"":gw_db_category_get_name ( categories->data)):tmp[0],
						(tmp[1]==NULL)?(gw_db_category_get_description ( categories->data)==NULL?"":gw_db_category_get_description ( categories->data)):tmp[1]) == 0 ) {
				if ( gzclose ( fic) != Z_OK ) {
				}

				if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
				if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}

				return -1;
			}

			if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
			if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
		}
	} else {
		if ( gzputs ( fic, "\n") == -1 ) {
			if ( gzclose ( fic) != Z_OK ) {
			}

			return -1;
		}
	}

	strbuf[0] = gw_string_buffer_new ( );
	strbuf[1] = gw_string_buffer_new ( );

	/* Saves all disks */
	tree = data->tree;
	nb = g_node_n_children ( tree);
	for ( i = 0; i < nb; i++) {
		node = g_node_nth_child ( tree, i);
		disk = (GWDBDisk*)node->data;
		tmp[0] = gw_str_to_file ( gw_db_disk_get_name ( disk));
		tmp[1] = gw_str_to_file ( gw_db_disk_get_fsname ( disk));
		tmp[2] = gw_str_to_file ( gw_db_disk_get_path ( disk));
		tmp[3] = gw_str_to_file ( gw_db_disk_get_fstype ( disk));
		tmp[4] = gw_str_to_file ( gw_db_disk_get_volume ( disk));
		tmp[5] = gw_str_to_file ( gw_db_disk_get_serial ( disk));
		tmp[6] = gw_str_to_file ( gw_db_disk_get_description ( disk));
		category = plugin->gw_db_catalog_get_db_category ( context, gw_db_disk_get_category ( disk));

		if ( gzprintf ( fic, FORMAT2_DISK_LONG,
					(tmp[0]==NULL)?gw_db_disk_get_name ( disk):tmp[0],
					gw_db_disk_get_num ( disk),
					(tmp[1]==NULL)?(gw_db_disk_get_fsname ( disk)==NULL?"":gw_db_disk_get_fsname ( disk)):tmp[1],
					(tmp[2]==NULL)?(gw_db_disk_get_path ( disk)==NULL?"":gw_db_disk_get_path ( disk)):tmp[2],
					(tmp[3]==NULL)?(gw_db_disk_get_fstype ( disk)==NULL?"":gw_db_disk_get_fstype ( disk)):tmp[3],
					(tmp[4]==NULL)?(gw_db_disk_get_volume ( disk)==NULL?"":gw_db_disk_get_volume ( disk)):tmp[4],
					gw_db_disk_get_full ( disk),
					gw_db_disk_get_free ( disk),
					gw_db_disk_get_date ( disk),
					(tmp[5]==NULL)?(gw_db_disk_get_serial ( disk)==NULL?"":gw_db_disk_get_serial ( disk)):tmp[5],
					(gw_db_category_get_index ( category)==-1)?0:gw_db_category_get_index ( category),
					(tmp[6]==NULL)?(gw_db_disk_get_description ( disk)==NULL?"":gw_db_disk_get_description ( disk)):tmp[6]) == 0 ) {
			if ( gzclose ( fic) != Z_OK ) {
			}
			gw_db_category_free ( category);

			if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
			if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
			if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}
			if ( tmp[3] != NULL ) {g_free ( tmp[3]);tmp[3] = NULL;}
			if ( tmp[4] != NULL ) {g_free ( tmp[4]);tmp[4] = NULL;}
			if ( tmp[5] != NULL ) {g_free ( tmp[5]);tmp[5] = NULL;}
			if ( tmp[6] != NULL ) {g_free ( tmp[6]);tmp[6] = NULL;}

			gw_string_buffer_free ( strbuf[0]);
			gw_string_buffer_free ( strbuf[1]);

			return -1;
		}

		gw_db_category_free ( category);

		if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
		if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
		if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}
		if ( tmp[3] != NULL ) {g_free ( tmp[3]);tmp[3] = NULL;}
		if ( tmp[4] != NULL ) {g_free ( tmp[4]);tmp[4] = NULL;}
		if ( tmp[5] != NULL ) {g_free ( tmp[5]);tmp[5] = NULL;}
		if ( tmp[6] != NULL ) {g_free ( tmp[6]);tmp[6] = NULL;}

		/* Recursive call to catalog_save_file_dir_2 */
		catalog_save_file_dir_2 ( context, node, fic, strbuf);

		if ( gzputs ( fic, "\\\n") == -1 ) {
			if ( gzclose ( fic) != Z_OK ) {
			}

			gw_string_buffer_free ( strbuf[0]);
			gw_string_buffer_free ( strbuf[1]);

			return -1;
		}
	}

	gw_string_buffer_free ( strbuf[0]);
	gw_string_buffer_free ( strbuf[1]);

	/* Closes file */
	if ( gzclose ( fic) == -1 ) {
		return -1;
	}

	/* Deteles the previous version of the catalog file before renames the temporary
	   files with the catalog file name because rename() cannot eraze a file. */
	unlink ( gw_db_catalog_get_db_name ( catalog));
	rename ( fullfiletmpname, gw_db_catalog_get_db_name ( catalog));

	/* Catalog informations were saved */
	gw_db_catalog_set_ismodified ( catalog, FALSE);

#if GW_DEBUG_TIME
	gw_am_log_msg ( 0, __FILE__, __LINE__, __PRETTY_FUNCTION__, _( "Elapsed time to save the catalog : %d secs"), time ( NULL) - begin);
#endif

	return 0;
}


gint catalog_save ( GWDBContext *context, gint version) {
	if ( context != NULL ) {
		return catalog_save_file_version_2 ( context);
	}

	return -1;
}


GWDBContext * plugin_db_catalog_create ( GWCatalogPlugin *plugin, const gchar *name, const gchar *mode) {
	GWDBContext *context = NULL;
	GWDBCatalog *catalog = NULL;
	GWDBCategory *category = NULL;
	_data *data = NULL;
	GNode *tree = NULL;


	/* Creates a new catalog context. */
	context = gw_db_context_new ( );
	gw_db_context_set_plugin ( context, plugin);
	data = (_data*)g_malloc ( sizeof ( _data));
	gw_db_context_set_data ( context, data);
	plugin = gw_db_context_get_plugin ( context);

	/* Creates a new catalog. */
	data->catalog = catalog = gw_db_catalog_new ( );
	data->categories = NULL;
	data->tree = NULL;
	data->zfile = NULL;
	data->sb = NULL;
	data->mode = g_strdup ( mode);
	category = gw_db_category_new ( );
	gw_db_category_set_name ( category, g_strdup ( _( "none")));
	plugin->gw_db_catalog_add_db_category ( context, category);
	gw_db_category_free ( category);
	gw_db_catalog_set_name ( catalog, g_strdup ( name));
	gw_db_catalog_set_short_db_name ( catalog, g_strdup ( name));

	/* Creates root node. */
	tree = g_node_new ( NULL);
	data->tree = tree;

	return context;
}


GWDBContext * plugin_db_catalog_open ( GWCatalogPlugin *plugin, const gchar* file, const gchar* mode) {
	GWDBContext *context = NULL;
	GWDBCatalog *catalog = NULL;
	GWDBCategory *category = NULL;
	gzFile zfile;
	_data *data = NULL;
	GWStringBuffer *sb = NULL;
	gchar **tmp = NULL;
	gchar *buf = NULL;
	struct stat f_info;
	gchar *extension = NULL;


	/* Checks if the given path is valid */
	if ( file==NULL || strlen ( file)==0) {
		return NULL;
	}
	
	/* Checks if the given file extension is really ".ctg" */
	extension = strrchr ( file, '.');
	if ( extension==NULL || strlen ( extension)!=4 || strcmp(".ctg",extension)!=0) {
		return NULL;
	}

	/* Reads the GWhere file and load all the catalog in memory. */
	if ( (zfile = gzopen ( file, "rb")) != NULL ) {
		context = gw_db_context_new ( );
		gw_db_context_set_plugin ( context, plugin);
		data = (_data*)g_malloc ( sizeof ( _data));
		gw_db_context_set_data ( context, data);
		plugin = gw_db_context_get_plugin ( context);
		data->catalog = catalog = gw_db_catalog_new ( );
		data->mode = g_strdup ( mode);

		if ( stat ( file, &f_info) != -1 ) {
			gw_db_catalog_set_size ( catalog, f_info.st_size);
		}

		data->categories = NULL;
		data->tree = NULL;
		data->zfile = zfile;
		data->sb = NULL;
		category = gw_db_category_new ( );
		gw_db_category_set_name ( category, g_strdup ( _( "none")));
		plugin->gw_db_catalog_add_db_category ( context, category);
		gw_db_category_free ( category);

		gw_db_catalog_set_db_name ( catalog, g_strdup ( file));
		if ( strrchr ( file, G_DIR_SEPARATOR) != NULL) {
			gw_db_catalog_set_short_db_name ( catalog, g_strdup ( strrchr ( file, G_DIR_SEPARATOR) + 1));
		} else {
			//TODO impossible??
			gw_db_catalog_set_short_db_name ( catalog, g_strdup ( file));
		}

		if ( (buf = gw_zfile_readline_sb ( zfile, &sb)) != NULL ) {
			data->sb = sb;
			/* Checks the file version */
			tmp = g_strsplit ( buf, ":", 0);

			if ( strcmp ( tmp[0], PROJECT_NAME) == 0 ) {
				gw_db_catalog_set_version ( catalog, g_strdup ( tmp[2]));
				if ( tmp[3] != NULL) {
					gw_db_catalog_set_program_builder ( catalog, g_strdup ( tmp[3]));
				} else {
					gw_db_catalog_set_program_builder ( catalog, g_strconcat ( PROJECT_NAME, " ", tmp[1], NULL));
				}

				switch ( strtol ( tmp[2], NULL, 10)) {
					case 1:	/* Loads the 1st version of GWhere file. */
							catalog_load ( context, 1);
							break;

					case 2:	/* Loads the 2nd version of GWhere file. */
							catalog_load ( context, 2);
							break;

					default:/* This version is unknown. */
							break;
				}

			} else {}

			if ( tmp != NULL ) g_strfreev ( tmp);
		} else {}

		if ( sb != NULL) gw_string_buffer_free ( sb);
			if ( gzclose ( zfile) != Z_OK ) {
		}

		gw_db_catalog_set_ismodified ( data->catalog, FALSE);
	} else {}

	return context;
}


gint plugin_db_catalog_save ( GWDBContext *context) {
	_data *data = NULL;
	gint result = -1;


	if ( context != NULL) {
		data = gw_db_context_get_data ( context);
		if ( gw_db_catalog_is_modified ( data->catalog) ) {
			if ( catalog_save ( context, 2)!=-1 ) {
				result = 0;
			} else {
				/* Catalog is not saved. */
			}
		} else {
			/* Not need to save the catalog. */
			result = 0;
		}
	} else {}

	return result;
}


gint plugin_db_catalog_close ( GWDBContext *context) {
	_data *data = NULL;
	GNode *tree = NULL, *node = NULL;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);

		tree = data->tree;
		nb = g_node_n_children ( tree);
		for ( i = 0; i < nb; i++ ) {
			node = g_node_first_child ( tree);
			if ( node != NULL ) {
				g_node_disk_free ( node, NULL);
			} else {}
		}

		gw_db_catalog_free ( data->catalog);
		if ( data->categories != NULL ) {
			g_list_foreach ( data->categories, (GFunc)gw_db_data_category_free, NULL);
			g_list_free ( data->categories);
		}

		if ( data->mode != NULL ) {
			g_free ( data->mode);
		}

		g_free ( data);

		return 0;
	}

	return 0;
}


/**/guint64 plugin_db_catalog_get_capacity ( GWDBContext *context) {
	GWDBDisk* disk = NULL;
	_data *data = NULL;
	GNode *tree = NULL;
	gint i = 0, nb = 0;
	guint64 capacity = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb = g_node_n_children ( tree);
		for ( i = 0; i < nb; i++ ) {
			disk = g_node_nth_child ( tree, i)->data;
			capacity += gw_db_disk_get_capacity ( disk);
		}
	}

	return capacity;
}/**/


/**/guint64 plugin_db_catalog_get_full ( GWDBContext *context) {
	GWDBDisk* disk = NULL;
	_data *data = NULL;
	GNode *tree = NULL;
	gint i = 0, nb = 0;
	guint64 full = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb = g_node_n_children ( tree);
		for ( i = 0; i < nb; i++ ) {
			disk = g_node_nth_child ( tree, i)->data;
			full += gw_db_disk_get_full ( disk);
		}
	}

	return full;
}/**/


/**/guint64 plugin_db_catalog_get_free ( GWDBContext *context) {
	GWDBDisk* disk = NULL;
	_data *data = NULL;
	GNode *tree = NULL;
	gint i = 0, nb = 0;
	guint64 free = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb = g_node_n_children ( tree);
		for ( i = 0; i < nb; i++ ) {
			disk = g_node_nth_child ( tree, i)->data;
			free += gw_db_disk_get_free ( disk);
		}
	}

	return free;
}/**/


glong plugin_db_catalog_get_nb_db_files ( GWDBContext *context) {
	_data *data = NULL;
	GNode *tree = NULL;
	glong count = 0;
	gint i = 0, j = 0, nb_disk = 0, nb = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb_disk = g_node_n_children ( tree);
		for ( i = 0; i < nb_disk; i++ ) {
			nb = g_node_n_children ( g_node_nth_child ( tree, i));
			for ( j = 0; j < nb; j++ ) {
				g_node_traverse ( g_node_nth_child ( g_node_nth_child ( tree, i), j), G_LEVEL_ORDER, G_TRAVERSE_LEAFS, -1, (GNodeTraverseFunc)g_node_count_files, &count);
			}
		}
	}

	return count;
}


glong plugin_db_catalog_get_nb_db_folders ( GWDBContext *context) {
	_data *data = NULL;
	GNode *tree = NULL;
	glong count = 0;
	gint i = 0, j = 0, nb_disk = 0, nb = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb_disk = g_node_n_children ( tree);
		for ( i = 0; i < nb_disk; i++ ) {
			nb = g_node_n_children ( g_node_nth_child ( tree, i));
			for ( j = 0; j < nb; j++ ) {
				g_node_traverse ( g_node_nth_child ( g_node_nth_child ( tree, i), j), G_LEVEL_ORDER, G_TRAVERSE_ALL, -1, (GNodeTraverseFunc)g_node_count_folders, &count);
			}
		}
	}

	return count;
}


gint plugin_db_catalog_get_nb_db_disks ( GWDBContext *context) {
	_data *data = NULL;
	GNode *tree = NULL;
	gint nb = -1;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb = g_node_n_children ( tree);
	}

	return nb;
}


GWDBDisk** plugin_db_catalog_get_db_disks ( GWDBContext *context) {
	GWDBDisk** disks = NULL;
	GWDBDisk* disk = NULL;
	_data *data = NULL;
	GNode *tree = NULL;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb = g_node_n_children ( tree);
		disks = (GWDBDisk**)g_malloc(sizeof(GWDBDisk*)*(nb+1));
		for ( i = 0; i <= nb; i++ ) disks[i] = NULL;
		for ( i = 0; i < nb; i++ ) {
			disk = g_node_nth_child ( tree, i)->data;
			disks[i] = gw_db_disk_dup ( disk, &disks[i]);
		}
	}

	return disks;
}


glong plugin_db_disk_get_nb_db_files ( GWDBContext *context, GWDBDiskPK ref) {
	GNode *disk = ref;
	glong count = 0;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		nb = g_node_n_children ( disk);
		for ( i = 0; i < nb; i++) {
			g_node_traverse ( g_node_nth_child ( disk, i), G_LEVEL_ORDER, G_TRAVERSE_LEAFS, -1, (GNodeTraverseFunc)g_node_count_files, &count);
		}
	}

	return count;
}


glong plugin_db_disk_get_nb_db_folders ( GWDBContext *context, GWDBDiskPK ref) {
	GNode *disk = ref;
	glong count = 0;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		nb = g_node_n_children ( disk);
		for ( i = 0; i < nb; i++) {
			g_node_traverse ( g_node_nth_child ( disk, i), G_LEVEL_ORDER, G_TRAVERSE_ALL, -1, (GNodeTraverseFunc)g_node_count_folders, &count);
		}
	}

	return count;
}


GWDBFile** plugin_db_disk_get_db_files ( GWDBContext *context, GWDBDiskPK ref) {
	GWDBFile** files = NULL;
	GWDBFile* file = NULL;
	GNode *disk = ref;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		nb = g_node_n_children ( disk);
		files = (GWDBFile**)g_malloc(sizeof(GWDBFile*)*(nb+1));
		for ( i = 0; i <= nb; i++ ) files[i] = NULL;
		for ( i = 0; i < nb; i++ ) {
			file = g_node_nth_child ( disk, i)->data;
			files[i] = gw_db_file_dup ( file, &files[i]);
		}
	}

	return files;
}


GWDBFile** plugin_db_file_get_db_files ( GWDBContext *context, GWDBFilePK ref) {
	GWDBFile** files = NULL;
	GWDBFile* file = NULL;
	GNode *folder = ref;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		nb = g_node_n_children ( folder);
		files = (GWDBFile**)g_malloc(sizeof(GWDBFile*)*(nb+1));
		for ( i = 0; i <= nb; i++ ) files[i] = NULL;
		for ( i = 0; i < nb; i++ ) {
			file = g_node_nth_child ( folder, i)->data;
			files[i] = gw_db_file_dup ( file, &files[i]);
		}
	}

	return files;
}


/**/GWDBFile* plugin_db_disk_get_db_file_by_name ( GWDBContext *context, GWDBDiskPK ref, gchar *name) {
	GWDBFile* file = NULL, *file_match = NULL;
	GNode *disk = ref;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		nb = g_node_n_children ( disk);
		for ( i = 0; i < nb && file_match == NULL; i++ ) {
			file = g_node_nth_child ( disk, i)->data;
			if ( strcmp ( gw_db_file_get_name ( file), name) == 0) {
				file_match = gw_db_file_dup ( file, &file_match);
			}
		}
	}

	return file_match;
}/**/


/**/GWDBFile* plugin_db_file_get_db_file_by_name ( GWDBContext *context, GWDBFilePK ref, gchar *name) {
	GWDBFile* file = NULL, *file_match = NULL;
	GNode *folder = ref;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		nb = g_node_n_children ( folder);
		for ( i = 0; i < nb && file_match == NULL; i++ ) {
			file = g_node_nth_child ( folder, i)->data;
			if ( strcmp ( gw_db_file_get_name ( file), name) == 0) {
				file_match = gw_db_file_dup ( file, &file_match);
			}
		}
	}

	return file_match;
}/**/


GWDBDisk* plugin_db_file_get_db_disk ( GWDBContext *context, GWDBFilePK ref) {
	_data *data = NULL;
	GNode *tree = NULL;
	GWDBDisk *disk = NULL;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb = g_node_n_children ( tree);
		for ( i = 0; i < nb; i++ ) {
			if ( g_node_is_ancestor ( g_node_nth_child ( tree, i), ref) == TRUE) {
				disk = gw_db_disk_dup ( g_node_nth_child ( tree, i)->data, &disk);

				break;
			} else {
				disk = NULL;
			}
		}

	}

	return disk;
}


GWDBFile * plugin_db_file_get_parent_db_file ( GWDBContext *context, GWDBFilePK ref) {
	GNode *node = ref;
	GWDBFile *parent = NULL;


	if ( context != NULL) {
		if ( g_node_depth ( node) > 3 ) {
			parent = gw_db_file_dup ( node->parent->data, &parent);
		} else{}
	}

	return parent;
}


/**/gchar* plugin_db_file_get_location ( GWDBContext *context, GWDBFilePK ref) {
	_data *data = NULL;
	GNode *tree = NULL, *current = ref;
	gchar *location = NULL,*tmp = NULL;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		location = g_strdup ( "/");
		current = current->parent;

		while ( g_node_depth ( current) > 2) {
			tmp = g_strconcat ( "/", gw_db_file_get_name ( current->data), location, NULL);
			g_free ( location);
			location = tmp;
			current = current->parent;
		}
	}

	return location;
}/**/


GWDBDiskPK plugin_db_catalog_add_db_disk ( GWDBContext *context, GWDBDisk *disk) {
	_data *data = NULL;
	GNode *tree = NULL;
	GWDBDiskPK pk = NULL;
	GWDBDisk *disk_dup = NULL;


	if ( context != NULL) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;

		/* It is the minimal test to process!! */
		if ( gw_db_disk_get_name ( disk) != NULL ) {
			disk_dup = gw_db_disk_dup ( disk, &disk_dup);
			pk = g_node_new ( disk_dup);
			gw_db_disk_set_ref ( disk_dup, pk);
			gw_db_disk_set_ref ( disk, pk);
			g_node_append ( tree, pk);
			gw_db_catalog_set_ismodified ( data->catalog, TRUE);
			gw_db_category_add_disk ( gw_db_disk_get_category ( disk_dup));
		}
	}

	return pk;
}


GWDBFilePK plugin_db_disk_add_db_file ( GWDBContext *context, GWDBDiskPK ref, GWDBFile *file) {
	GNode *node = ref;
	GWDBFilePK pk = NULL;
	GWDBFile *file_dup = NULL;


	if ( context != NULL && ref != NULL) {
		/* It is the minimal test to process!! */
		if ( gw_db_file_get_name ( file) != NULL ) {
			if ( g_node_depth ( node) == 2 ) {
				file_dup = gw_db_file_dup ( file, &file_dup);
				pk = g_node_new ( file_dup);
				gw_db_file_set_ref ( file_dup, pk);
				gw_db_file_set_ref ( file, pk);
				g_node_append ( node, pk);
				gw_db_category_add_file ( gw_db_file_get_category ( file_dup));
			}
		}
	}

	return pk;
}


GWDBFilePK plugin_db_file_add_db_file ( GWDBContext *context, GWDBFilePK ref, GWDBFile *file) {
	GNode *node = ref;
	GWDBFilePK pk = NULL;
	GWDBFile *file_dup = NULL;


	if ( context != NULL && ref != NULL) {
		/* It is the minimal test to process!! */
		if ( gw_db_file_get_name ( file) != NULL ) {
			if ( g_node_depth ( node) > 2 ) {
				file_dup = gw_db_file_dup ( file, &file_dup);
				pk = g_node_new ( file_dup);
				gw_db_file_set_ref ( file_dup, pk);
				gw_db_file_set_ref ( file, pk);
				g_node_append ( node, pk);
				gw_db_category_add_file ( gw_db_file_get_category ( file_dup));
			} else if ( g_node_depth ( node) == 2 ) {
				file_dup = gw_db_file_dup ( file, &file_dup);
				pk = g_node_new ( file_dup);
				gw_db_file_set_ref ( file_dup, pk);
				gw_db_file_set_ref ( file, pk);
				g_node_append ( node, pk);
				gw_db_category_add_file ( gw_db_file_get_category ( file_dup));
			}
		}
	}

	return pk;
}


gint plugin_db_catalog_remove_db_disk ( GWDBContext *context, GWDBDiskPK ref) {
	GNode *node = ref;
	_data *data = NULL;


	if ( context != NULL && ref != NULL) {
		/* It is the minimal test to process!! */
		if ( g_node_depth ( node) == 2 ) {
			gw_db_category_remove_disk ( gw_db_disk_get_category ( node->data));
			g_node_disk_free ( node, NULL);
			data = gw_db_context_get_data ( context);
			gw_db_catalog_set_ismodified ( data->catalog, TRUE);

			return 0;
		}
	}

	return -1;
}


gint plugin_db_catalog_remove_db_file ( GWDBContext *context, GWDBFilePK ref) {
	GNode *node = ref;
	_data *data = NULL;


	if ( context != NULL && ref != NULL) {
		/* It is the minimal test to process!! */
		if ( g_node_depth ( node) > 2 ) {
			g_node_unlink ( node);
			g_node_files_free ( node, NULL);
			g_node_destroy ( node);
			data = gw_db_context_get_data ( context);
			gw_db_catalog_set_ismodified ( data->catalog, TRUE);

			return 0;
		}
	}

	return -1;
}


gint plugin_db_disk_update ( GWDBContext *context, GWDBDisk *disk) {
	GNode *node = NULL;
	GWDBDisk *disk_dup = NULL;
	_data *data = NULL;


	if ( context != NULL && disk != NULL ) {
		/* It is the minimal test to process!! */
		//TODO it should be better to test if disk name already exists
		if ( gw_db_disk_get_name ( disk) != NULL ) {
			node = gw_db_disk_get_ref ( disk);
			if ( g_node_depth ( node) == 2 ) {
				disk_dup = node->data;
				if ( !gw_db_disk_equals ( disk_dup, disk) ) {
					if ( gw_db_disk_get_category ( disk) != gw_db_disk_get_category ( disk_dup)) {
						gw_db_category_add_disk ( gw_db_disk_get_category ( disk));
						gw_db_category_remove_disk ( gw_db_disk_get_category ( disk_dup));
					}

					gw_db_disk_dup ( disk, &disk_dup);
					data = gw_db_context_get_data ( context);
					gw_db_catalog_set_ismodified ( data->catalog, TRUE);

					return 0;
				}
			}
		}
	}

	return -1;
}


gint plugin_db_file_update ( GWDBContext *context, GWDBFile *file) {
	GNode *node = NULL;
	GWDBFile *file_dup = NULL;
	_data *data = NULL;


	if ( context != NULL && file != NULL ) {
		/* It is the minimal test to process!! */
		//TODO it should be better to test if disk name already exists
		if ( gw_db_file_get_name ( file) != NULL ) {
			node = gw_db_file_get_ref ( file);
			if ( g_node_depth ( node) > 2 ) {
				file_dup = node->data;
				if ( !gw_db_file_equals ( file_dup, file) ) {
					if ( gw_db_file_get_category ( file) != gw_db_file_get_category ( file_dup)) {
						gw_db_category_add_file ( gw_db_file_get_category ( file));
						gw_db_category_remove_file ( gw_db_file_get_category ( file_dup));
					}

					gw_db_file_dup ( file, &file_dup);
					data = gw_db_context_get_data ( context);
					gw_db_catalog_set_ismodified ( data->catalog, TRUE);

					return 0;
				}
			}
		}
	}

	return -1;
}


/**/GWDBCategory* plugin_db_catalog_get_db_category_by_index ( GWDBContext *context, gint index) {
	GWDBCategory *category = NULL;
	GList *categories = NULL;
	_data *data = NULL;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		categories = data->categories;
		nb = g_list_length ( categories);

		for ( i = 0; i < nb && category == NULL; i++) {
			if ( gw_db_category_get_index ( g_list_nth ( categories, i)->data) == index) {
				category = gw_db_category_dup ( g_list_nth ( categories, i)->data, &category);
			}
		}
	}

	return category;
}/**/


GWDBCatalog* plugin_db_catalog_get_db_catalog ( GWDBContext *context) {
	GWDBCatalog *catalog = NULL;
	_data *data = NULL;


	if ( context != NULL) {
		data = gw_db_context_get_data ( context);
		catalog = gw_db_catalog_dup ( data->catalog, &catalog);
	}

	return catalog;
}


GWDBDisk* plugin_db_catalog_get_db_disk ( GWDBContext *context, GWDBDiskPK ref) {
	GWDBDisk *disk = NULL;
	GNode *node = ref;


	if ( context != NULL && ref != NULL) {
		disk = gw_db_disk_dup ( node->data, &disk);
	}

	return disk;
}


GWDBFile* plugin_db_catalog_get_db_file ( GWDBContext *context, GWDBFilePK ref) {
	GWDBFile *file = NULL;
	GNode *node = ref;
	_data *data = NULL;


	if ( context != NULL && ref != NULL) {
		data = gw_db_context_get_data ( context);
		if ( g_node_is_ancestor ( data->tree, node) && g_node_depth ( node) > 2) {
			file = gw_db_file_dup ( node->data, &file);
		}
	}

	return file;
}


GWDBCategory* plugin_db_catalog_get_db_category ( GWDBContext *context, GWDBCategoryPK ref) {
	GWDBCategory *category = NULL;


	if ( context != NULL && ref != NULL) {
		category = gw_db_category_dup ( ref, &category);
	}

	return category;
}


GWDBCategory** plugin_db_catalog_get_db_categories ( GWDBContext *context) {
	GWDBCategory **categories = NULL;
	_data *data = NULL;
	gint nb = 0, i = 0;


	if ( context != NULL) {
		data = gw_db_context_get_data ( context);
		nb = g_list_length ( g_list_first ( data->categories));
		categories = (GWDBCategory**)g_malloc(sizeof(GWDBCategory*)*(nb+1));
		for ( i = 0; i <= nb; i++ ) categories[i] = NULL;
		for ( i = 0; i < nb; i++ ) {
			categories[i] = gw_db_category_dup ( g_list_nth ( data->categories, i)->data, &categories[i]);
		}
	}

	return categories;
}


GWDBCategoryPK plugin_db_catalog_add_db_category ( GWDBContext *context, GWDBCategory *category) {
	_data *data = NULL;
	GWDBCategoryPK pk = NULL;
	gint index = 0;
	GWDBCategory *category_dup = NULL;


	if ( context != NULL && category != NULL ) {
		data = gw_db_context_get_data ( context);
		category_dup = gw_db_category_dup ( category, &category_dup);
		data->categories = g_list_append ( data->categories, category_dup);
		index = g_list_length ( g_list_first ( data->categories)) - 1;
		if ( index == -1) index = 0;
		gw_db_category_set_index ( category_dup, index);
		gw_db_category_set_index ( category, index);
		gw_db_category_set_ref ( category_dup, category_dup);
		gw_db_category_set_ref ( category, category_dup);
		gw_db_catalog_set_ismodified ( data->catalog, TRUE);

		pk = category_dup;
	}

	return pk;
}


gint plugin_db_catalog_remove_db_category ( GWDBContext *context, GWDBCategoryPK ref) {
	_data *data = NULL;
	GWDBCategory *category = ref;
	GList *categories = NULL;
	gint size = 0, i = 0, index = 0;


	if ( context != NULL && category != NULL) {
		data = gw_db_context_get_data ( context);
		categories = data->categories;
		size = g_list_length ( g_list_first ( categories)) - 1;
		index = gw_db_category_get_index ( category);

		categories = g_list_remove ( categories, gw_db_category_get_ref(category));
		categories = g_list_first ( categories);
		categories = g_list_first ( categories);

		categories = g_list_nth ( categories, index);

		for ( i = index; i < size; i++) {
			gw_db_category_set_index ( categories->data, gw_db_category_get_index ( categories->data) - 1);
			categories = g_list_next ( categories);
		}

		gw_db_catalog_set_ismodified ( data->catalog, TRUE);

		return 0;
	}

	return -1;
}


gint plugin_db_catalog_update ( GWDBContext *context, GWDBCatalog *catalog) {
	GWDBCatalog *catalog_dup = NULL;
	_data *data = NULL;


	if ( context != NULL && catalog != NULL ) {
		data = gw_db_context_get_data ( context);
		//TODO it should be better to test if catalog is correct
		catalog_dup = data->catalog;
		if ( !gw_db_catalog_equals ( catalog_dup, catalog) ) {
			gw_db_catalog_dup ( catalog, &catalog_dup);
			gw_db_catalog_set_ismodified ( catalog_dup, TRUE);

			return 0;
		} else {}
	}

	return -1;
}


gint plugin_db_category_update ( GWDBContext *context, GWDBCategory *category) {
	GWDBCategory *category_dup = NULL;
	_data *data = NULL;
	gint i = 0;


	if ( context != NULL && category != NULL ) {
		data = gw_db_context_get_data ( context);

		for ( i = 0; i < g_list_length ( data->categories); i++) {
			category_dup = g_list_nth ( data->categories, i)->data;
			if ( gw_db_category_get_index ( category) == gw_db_category_get_index ( category_dup)) {
				break;
			} else {
				category_dup = NULL;
			}
		}

		if ( category_dup != NULL ) {
			category_dup = gw_db_category_dup ( category, &category_dup);
			data = gw_db_context_get_data ( context);
			gw_db_catalog_set_ismodified ( data->catalog, TRUE);

			return 0;
		}
	}

	return -1;
}


/**/GWDBCategory* plugin_db_catalog_get_db_category_by_name ( GWDBContext *context, gchar *name) {
	GWDBCategory *category = NULL;
	GList *categories = NULL;
	_data *data = NULL;
	gint i = 0, nb = 0;


	if ( context != NULL && name != NULL ) {
		data = gw_db_context_get_data ( context);
		categories = data->categories;
		nb = g_list_length ( categories);

		for ( i = 0; i < nb && category == NULL; i++) {
			if ( strcmp ( name, gw_db_category_get_name ( g_list_nth ( categories, i)->data)) == 0) {
				category = gw_db_category_dup ( g_list_nth ( categories, i)->data, &category);
			}
		}
	}

	return category;
}/**/


/**/GWDBDisk* plugin_db_catalog_get_db_disk_by_name ( GWDBContext *context, gchar *name) {
	GWDBDisk* disk = NULL;
	GWDBDisk* disk_dup = NULL;
	_data *data = NULL;
	GNode *tree = NULL;
	gint i = 0, nb = 0;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);
		tree = data->tree;
		nb = g_node_n_children ( tree);
		for ( i = 0; i < nb && disk == NULL; i++ ) {
			disk = g_node_nth_child ( tree, i)->data;
			if ( strcmp ( name, gw_db_disk_get_name ( disk)) != 0) {
				disk = NULL;
			} else {
				disk_dup = gw_db_disk_dup ( disk, &disk_dup);
			}
		}
	}

	return disk_dup;
}/**/


GWPluginInfo * plugin_get_info ( ) {
	GWPluginInfo *plugin_info = gw_plugin_info_new ( );


	gw_plugin_info_set_name ( plugin_info, g_strdup ( "GWhere catalog"));
	gw_plugin_info_set_version ( plugin_info, g_strdup ( "1.0.0"));
	gw_plugin_info_set_author ( plugin_info, g_strdup ( "Sébastien LECACHEUR"));
	gw_plugin_info_set_description ( plugin_info, g_strdup ( "Store any catalog in a simple file with the native GWhere file format."));
	gw_plugin_info_set_help ( plugin_info, g_strdup ( "There is no help at time"));

	return plugin_info;
}

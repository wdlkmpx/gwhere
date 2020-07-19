#include <glib.h>
#include <stdlib.h> /* strtol strtoul strtoull */
#include <string.h> /* strrchr */
#include <sys/stat.h> /* stat */
#include <time.h> /* localtime strptime */
#include <ctype.h> /* isdigit */
#include "plugins/gwcatalog.h"
#include "data/gwdata.h"
#include "tools/gwtools.h"
#include "gwsupport.h"


#define CSV_SEPARATOR ';'
#define CSV_SEPARATOR_S ";"
#define CSV_DATE_FORMAT "%Y-%m-%d %H:%M:%S"


#if defined ( OS_WIN32)
	#define CSV_LINE_DISK "%s;%d;%s;%s;%s;%s;%"##G_GUINT64_FORMAT##";%"##G_GUINT64_FORMAT##";%s;%s;%s;%s\n"
	#define CSV_LINE_FILE "%s;%s;%s;%s;%s;%s;%ld;%"##G_GUINT64_FORMAT##";%s;%s;%s;%s;%s\n"
#else
	#ifdef __STDC__
		#define CONCAT3(x,y,z) x/**/y/**/z/**/
		#define CONCAT5(v,w,x,y,z) v/**/w/**/x/**/y/**/z/**/
	#else
		#define CONCAT3(x,y,z) x/**/y/**/z/**/
		#define CONCAT5(v,w,x,y,z) v/**/w/**/x/**/y/**/z/**/
	#endif

	#define CSV_LINE_DISK  CONCAT5("%s;%d;%s;%s;%s;%s;%",G_GUINT64_FORMAT,";%",G_GUINT64_FORMAT,";%s;%s;%s;%s\n")
	#define CSV_LINE_FILE  CONCAT3("%s;%s;%s;%s;%s;%s;%ld;%",G_GUINT64_FORMAT,";%s;%s;%s;%s;%s\n")
#endif


typedef struct {
	GWDBCatalog *catalog;
	GList *categories;
	GNode *tree;
	GWStringBuffer *sb;
	FILE *file;
	gchar *current_disk_name;
}_data;


// __USE_XOPEN or _XOPEN_SOURCE must be defined with GlibC2
#if !defined(HAVE_STRPTIME) || !defined(__USE_XOPEN)
/* get a positive number between n_min and n_max, for a maximum length
   of len_max. Return -1 if error. */
static int date_get_num ( const char **pp, int n_min, int n_max, int len_max) {
	int i, val, c;
	const char *p;


	p = *pp;
	val = 0;
	for ( i = 0; i < len_max; i++) {
		c = *p;
		if (!isdigit(c)) {
			break;
		}

		val = (val * 10) + c - '0';
		p++;
	}

	/* no number read ? */
	if (p == *pp) {
		return -1;
	}

	if (val < n_min || val > n_max) {
		return -1;
	}

	*pp = p;

	return val;
}


/* small strptime for minimum use. */
const char *strptime ( const char *p, const char *fmt, struct tm *dt) {
	int c, val;

	for(;;) {
		c = *fmt++;
		if (c == '\0') {
			return p;
		} else if (c == '%') {
			c = *fmt++;
			switch(c) {
			case 'H':
				val = date_get_num(&p, 0, 23, 2);
				if (val == -1)
				return NULL;
				dt->tm_hour = val;
				/* Disables dayligth saving */
				dt->tm_isdst = -1;
				break;
			case 'M':
				val = date_get_num(&p, 0, 59, 2);
				if (val == -1)
				return NULL;
				dt->tm_min = val;
				break;
			case 'S':
				val = date_get_num(&p, 0, 59, 2);
				if (val == -1)
				return NULL;
				dt->tm_sec = val;
				break;
			case 'Y':
				val = date_get_num(&p, 0, 9999, 4);
				if (val == -1)
				return NULL;
				dt->tm_year = val - 1900;
				break;
			case 'y':
				val = date_get_num(&p, 0, 9999, 2);
				if (val == -1)
				return NULL;
				dt->tm_year = val - 1900;
				break;
			case 'm':
				val = date_get_num(&p, 1, 12, 2);
				if (val == -1)
				return NULL;
				dt->tm_mon = val - 1;
				break;
			case 'd':
				val = date_get_num(&p, 1, 31, 2);
				if (val == -1)
				return NULL;
				dt->tm_mday = val;
				break;
			case '%':
				goto match;
			default:
				return NULL;
			}
		} else {
			match:
			if (c != *p) {
				return NULL;
			}

			p++;
		}
	}

	return p;
}
#endif


gchar * csv_str_to_file ( gchar *str) {
	gchar *txt = NULL, *tmp = NULL;


	if ( str != NULL ) {
		if ( strchr ( str, '\"') != NULL ) {
			tmp = gw_str_replace_str ( str, "\"", "\"\"");
			txt = g_strconcat ( "\"", tmp, "\"", NULL);
			g_free ( tmp);
		} else if ( strchr ( str, CSV_SEPARATOR) != NULL || strchr ( str, '\n') != NULL ) {
			txt = g_strconcat ( "\"", str, "\"", NULL);
		} else {
			txt = g_strdup ( str);
		}
	} else {
		txt = g_strdup ( "");
	}

	return txt;
}


gchar * csv_format_date ( gulong t) {
	struct tm *time = NULL;
	gchar *date = NULL;


	if ( t != 0 ) {
		if ( (time = localtime ( &t)) != NULL ) {
			/* Disables dayligth saving */
			time->tm_isdst = -1;
			if ( (date = (gchar*)g_malloc ( sizeof ( gchar) * 20)) != NULL ) {
				strftime ( date, 20, CSV_DATE_FORMAT, time);

				return date;
			} else {}
		} else {}
	} else {}

	return NULL;
}


gulong csv_read_date ( gchar *date) {
	struct tm time;
	gulong t = 0;


	if ( date != 0 ) {
		memset ( &time, '\0', sizeof ( struct tm));
		strptime ( date, CSV_DATE_FORMAT, &time);
		t = mktime ( &time);
	} else {}

	return t;
}


GWDBContext * csv_context_new ( GWCatalogPlugin *plugin) {
	GWDBContext *context = NULL;
	GWDBCatalog *catalog = NULL;
	GWDBCategory *category = NULL;
	_data *data = NULL;


	/* Create the new catalog context */
	context = gw_db_context_new ( );
	gw_db_context_set_plugin ( context, plugin);
	data = (_data*)g_malloc ( sizeof ( _data));
	gw_db_context_set_data ( context, data);
	data->catalog = catalog = gw_db_catalog_new ( );
	data->categories = NULL;
	data->tree = g_node_new ( NULL);
	data->sb = NULL;
	data->file = NULL;
	data->current_disk_name = NULL;

	/* Creates the default category */
	category = gw_db_category_new ( );
	gw_db_category_set_name ( category, g_strdup ( _( "none")));
	data->categories = g_list_append ( data->categories, category);
	gw_db_category_set_index ( category, 0);

	return context;
}


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


gchar * cvs_file_read_record ( FILE *f, GWStringBuffer **sb, GWStringBuffer *tmp) {
	gchar *buf = NULL, *tmp_buf = NULL;
	gint i = 0, count = 0;


	if ( f!=NULL && tmp!=NULL) {
		if ( (buf = gw_file_readline_sb ( f, sb)) != NULL ) {

			do {
				for ( i = 0, count = 0; buf[i] != '\0'; i++) if ( buf[i] == '"' ) count++;

				if ( count%2==1) {
					gw_string_buffer_set_str ( tmp, buf, strlen ( buf));
					gw_string_buffer_append_str ( tmp, "\n", strlen ( "\n"));
					buf = gw_file_readline_sb ( f, sb);
					tmp_buf = gw_string_buffer_get_str ( tmp);
					gw_string_buffer_insert_str ( *sb, tmp_buf, 0, strlen ( tmp_buf));
					buf = gw_string_buffer_get_str ( *sb);
				}
			} while ( count%2==1);
		}
	}

	return buf;
}


gchar * cvs_file_read_field_str ( gchar *str, gint *pos) {
	//WARN The given str parameter is altered
	//FIXME When go back with "last_real_separator" the readed field may be altered :-/
	gchar used_separator = CSV_SEPARATOR;
	gint i = 0, j = 0, begin = 0, end = 0, count = 0;
	gchar *field = NULL;
	gint last_real_separator = -1;


	if ( str!=NULL && *pos>=0) {
		begin = i = *pos;

		if ( str[i]=='"') {
			used_separator = '"';
			count = 1;
			begin = ++i;
		} else {
			used_separator = CSV_SEPARATOR;
			count = 0;
		}

		for ( j = i; ((str[j] != used_separator || count%2==1) && (str[j] != '\0')); j++ ) {
			if ( str[j] == '"') {
				if ( str[j+1] == CSV_SEPARATOR ) {
					last_real_separator = j + 1;
				}

				if ( str[j+1] == '"') {
					count++;
				}

				if ( str[j+1]!=CSV_SEPARATOR && str[j+1]!='"' && str[j+1]!='\n' && str[j+1]!='\0') {
					/* Impossible */
					break;
				}

				count++;
				str[i++] = str[j++];
			} else {
				str[i++] = str[j];
			}
		}

		if ( last_real_separator != -1 ) {
			str[i] = str[j];
			i = last_real_separator;
			j = i - 1;
		}

		if ( used_separator == '"') {
			end = i - 1;
		} else {
			end = i;
		}

		if ( begin < end) {
			if ( (field = (gchar*)g_malloc0 ( sizeof ( gchar)*(end-begin+1))) != NULL ) {
				memcpy ( field, &str[begin], end-begin);
				field[end-begin] = '\0';
			} else {
				field = NULL;
			}
		} else {
			field = NULL;
		}

		*pos = j + 1;
	}

	return field;
}


glong cvs_file_read_field_l ( gchar *str, gint *pos) {
	gint i = 0, begin = 0;
	glong field = 0;


	if ( str!=NULL && pos>=0) {
		begin = *pos;

		for ( i = begin; ((str[i] != CSV_SEPARATOR) && (str[i] != '\0')); i++ ) {}

		if ( str[i] == CSV_SEPARATOR) {
			str[i] = '\0';
			field = strtol ( &str[begin], NULL, 10);
		}

		*pos = i + 1;
	}

	return field;
}


gulong cvs_file_read_field_date ( gchar *str, gint *pos) {
	gint i = 0, begin = 0;
	gulong field = 0;


	if ( str!=NULL && pos>=0) {
		begin = *pos;

		for ( i = begin; ((str[i] != CSV_SEPARATOR) && (str[i] != '\0')); i++ ) {}

		if ( str[i] == CSV_SEPARATOR) {
			str[i] = '\0';
			field = csv_read_date ( &str[begin]);
		}

		*pos = i + 1;
	}

	return field;
}


guint64 cvs_file_read_field_ui64 ( gchar *str, gint *pos) {
	gint i = 0, begin = 0;
	guint64 field = 0;


	if ( str!=NULL && pos>=0) {
		begin = *pos;

		for ( i = begin; ((str[i] != CSV_SEPARATOR) && (str[i] != '\0')); i++ ) {}

		if ( str[i] == CSV_SEPARATOR) {
			str[i] = '\0';
			field = strtoui64 ( &str[begin], NULL, 10);
		}

		*pos = i + 1;
	}

	return field;
}


GWDBFile * csv_file_from_str ( gchar *str, GWDBContext *context, gchar **disk_name, gchar **location) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBFile *file = NULL;
	gint index = 0;
	gchar *tmp = NULL;
	GWDBCategory *category = NULL;


	if ( (file = gw_db_file_new ( )) != NULL ) {
		/* Read the file name. */
		gw_db_file_set_name ( file, cvs_file_read_field_str ( str, &index));

		tmp = cvs_file_read_field_str ( str, &index);
		if ( tmp != NULL ) {
			*disk_name = tmp;
			tmp = NULL;
		}

		tmp = cvs_file_read_field_str ( str, &index);
		if ( tmp != NULL ) {
			*location = tmp;
			tmp = NULL;
		}

		/* Read the file rights. */
		tmp = cvs_file_read_field_str ( str, &index);
		if ( tmp != NULL ) {
			gw_db_file_set_rights_from_gchar ( file, tmp);
			g_free ( tmp);
			tmp = NULL;
		}

		/* Read the file owner. */
		gw_db_file_set_owner ( file, cvs_file_read_field_str ( str, &index));

		/* Read the file group. */
		gw_db_file_set_group ( file, cvs_file_read_field_str ( str, &index));

		/* Read the file inode. */
		gw_db_file_set_inode ( file, cvs_file_read_field_l ( str, &index));

		/* Read the file size. */
		gw_db_file_set_size ( file, cvs_file_read_field_ui64 ( str, &index));

		/* Read the file cdate. */
		gw_db_file_set_cdate ( file, cvs_file_read_field_date ( str, &index));

		/* Read the file adate. */
		gw_db_file_set_adate ( file, cvs_file_read_field_date ( str, &index));

		/* Read the file mdate. */
		gw_db_file_set_mdate ( file, cvs_file_read_field_date ( str, &index));

		/* Read the file category. */
		tmp = cvs_file_read_field_str ( str, &index);
		if ( context!=NULL && tmp!=NULL) {
			gw_db_file_set_category ( file, gw_db_category_get_ref ( category = plugin->gw_db_catalog_get_db_category_by_name ( context, tmp)));
			gw_db_category_add_file ( gw_db_category_get_ref ( category));
			gw_db_category_free ( category);
		}
		if ( tmp != NULL ) {
			g_free ( tmp);
			tmp = NULL;
		}

		/* Read the file description. */
		gw_db_file_set_description ( file, cvs_file_read_field_str ( str, &index));
	}

	return file;
}


GWDBCategory * csv_category_from_str ( gchar *str, GWDBContext *context) {
	GWDBCategory *category = NULL;
	gint index = 0;


	if ( (category = gw_db_category_new ( )) != NULL ) {
		gw_db_category_set_name ( category, cvs_file_read_field_str ( str, &index));
		gw_db_category_set_description ( category, cvs_file_read_field_str ( str, &index));
	}

	return category;
}


GWDBDisk * csv_disk_from_str ( gchar *str, GWDBContext *context) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	GWDBDisk *disk = NULL;
	gint index = 0;
	gchar *tmp = NULL;
	GWDBCategory *category = NULL;


	if ( (disk = gw_db_disk_new ( )) != NULL ) {
		/* Read the disk name. */
		gw_db_disk_set_name ( disk, cvs_file_read_field_str ( str, &index));

		/* Read the disk archive number. */
		gw_db_disk_set_num ( disk, cvs_file_read_field_l ( str, &index));

		/* Read the disk file system name. */
		gw_db_disk_set_fsname ( disk, cvs_file_read_field_str ( str, &index));

		/* Read the disk access directory. */
		gw_db_disk_set_path ( disk, cvs_file_read_field_str ( str, &index));

		/* Read the disk type. */
		tmp = cvs_file_read_field_str ( str, &index);
		if ( tmp!=NULL && strlen ( tmp)>=6 && memcmp(tmp,"CD-ROM",6)==0 ) {
			g_free ( tmp);
			tmp = g_strdup ( "iso9660");
		}

		//TODO to check the following code..
		if ( tmp!=NULL ) {
			if ( strlen(tmp)>=6 && memcmp(tmp,"CD-ROM",6)==0 ) {
				gw_db_disk_set_type ( disk, CDROM);
			} else if ( strlen(tmp)==4 && memcmp(tmp,"cdfs",4)==0 ) {
				gw_db_disk_set_type ( disk, CDROM);
			} else if ( strlen(tmp)>2 && memcmp(tmp,"HD",2)==0 ) {
				gw_db_disk_set_type ( disk, HD);
			} else if ( strlen(tmp)==6 && memcmp(tmp,"Floppy",6)==0 ) {
				gw_db_disk_set_type ( disk, FLOPPY);
			} else if ( strlen(tmp)==3 && memcmp(tmp,"Zip",3)==0 ) {
				gw_db_disk_set_type ( disk, ZIP_DRIVE);
			} else if ( strlen(tmp)==3 && memcmp(tmp,"smb",3)==0 ) {
				gw_db_disk_set_type ( disk, NETWORK_DRIVE);
			} else if ( strlen(tmp)==4 && memcmp(tmp,"ntfs",4)==0 ) {
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
		}
		gw_db_disk_set_fstype ( disk, tmp);

		/* Read the disk volume name. */
		gw_db_disk_set_volume ( disk, cvs_file_read_field_str ( str, &index));

		/* Read the disk used space. */
		gw_db_disk_set_full ( disk, cvs_file_read_field_ui64 ( str, &index));

		/* Read the disk free space. */
		gw_db_disk_set_free ( disk, cvs_file_read_field_ui64 ( str, &index));

		/* Read the disk adding date. */
		gw_db_disk_set_date ( disk, cvs_file_read_field_date ( str, &index));

		/* Read the disk serial number. */
		gw_db_disk_set_serial ( disk, cvs_file_read_field_str ( str, &index));

		/* Read the disk category. */
		tmp = cvs_file_read_field_str ( str, &index);
		if ( context!=NULL && tmp!=NULL) {
			gw_db_disk_set_category ( disk, gw_db_category_get_ref ( category = plugin->gw_db_catalog_get_db_category_by_name ( context, tmp)));
			gw_db_category_add_disk ( gw_db_category_get_ref ( category));
			gw_db_category_free ( category);
		}
		if ( tmp != NULL ) {
			g_free ( tmp);
			tmp = NULL;
		}

		/* Read the disk description. */
		gw_db_disk_set_description ( disk, cvs_file_read_field_str ( str, &index));
	}

	return disk;
}


gint csv_file_save_folder ( GWDBContext *context, GNode *parent, GWStringBuffer *buf[2]) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	_data *data = gw_db_context_get_data ( context);
	FILE *f = data->file;
	GWDBFile *file = NULL;
	GNode *node = NULL;
	gchar *tmp[10];
	gint i = 0, nb = 0;
	gchar *_tmp = NULL;
	GWDBCategory *category = NULL;


	/* Gets folder files list */
	nb = g_node_n_children ( parent);
	for ( i = 0; i < nb; i++) {
		node = g_node_nth_child ( parent, i);
		file = node->data;

		/* Gets file informations */
		tmp[0] = csv_str_to_file ( gw_db_file_get_name ( file));
		tmp[1] = csv_str_to_file ( gw_db_file_get_description ( file));
		tmp[2] = gw_db_file_get_rights_to_gchar ( file);
		tmp[3] = csv_str_to_file ( _tmp = plugin->gw_db_file_get_location ( context, gw_db_file_get_ref ( file)));
		g_free ( _tmp);
		tmp[4] = csv_format_date ( gw_db_file_get_cdate ( file));
		tmp[5] = csv_format_date ( gw_db_file_get_adate ( file));
		tmp[6] = csv_format_date ( gw_db_file_get_mdate ( file));
		tmp[7] = csv_str_to_file ( gw_db_file_get_owner ( file));
		tmp[8] = csv_str_to_file ( gw_db_file_get_group ( file));
		category = plugin->gw_db_catalog_get_db_category ( context, gw_db_file_get_category ( file));
		if ( gw_db_category_get_index ( category) != 0) {
			tmp[9] = csv_str_to_file ( _tmp = gw_db_category_get_name ( category));
		} else {
			tmp[9] = g_strdup ( "");
		}
		gw_db_category_free ( category);

		_tmp = g_strdup_printf ( CSV_LINE_FILE,
					tmp[0],
					data->current_disk_name,
					tmp[3],
					tmp[2],
					tmp[7],
					tmp[8],
					gw_db_file_get_inode ( file),
					gw_db_file_get_size ( file),
					tmp[4],
					tmp[5],
					tmp[6],
					tmp[9],
					tmp[1]);
		if ( fprintf ( f, _tmp) == 0 ) {
			fclose ( f);

			g_free ( _tmp);
			if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
			if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
			if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}
			if ( tmp[3] != NULL ) {g_free ( tmp[3]);tmp[3] = NULL;}
			if ( tmp[4] != NULL ) {g_free ( tmp[4]);tmp[4] = NULL;}
			if ( tmp[5] != NULL ) {g_free ( tmp[5]);tmp[5] = NULL;}
			if ( tmp[6] != NULL ) {g_free ( tmp[6]);tmp[6] = NULL;}
			if ( tmp[7] != NULL ) {g_free ( tmp[7]);tmp[7] = NULL;}
			if ( tmp[8] != NULL ) {g_free ( tmp[8]);tmp[8] = NULL;}
			if ( tmp[9] != NULL ) {g_free ( tmp[9]);tmp[9] = NULL;}

			return -1;
		}

		g_free ( _tmp);
		if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
		if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
		if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}
		if ( tmp[3] != NULL ) {g_free ( tmp[3]);tmp[3] = NULL;}
		if ( tmp[4] != NULL ) {g_free ( tmp[4]);tmp[4] = NULL;}
		if ( tmp[5] != NULL ) {g_free ( tmp[5]);tmp[5] = NULL;}
		if ( tmp[6] != NULL ) {g_free ( tmp[6]);tmp[6] = NULL;}
		if ( tmp[7] != NULL ) {g_free ( tmp[7]);tmp[7] = NULL;}
		if ( tmp[8] != NULL ) {g_free ( tmp[8]);tmp[8] = NULL;}
		if ( tmp[9] != NULL ) {g_free ( tmp[9]);tmp[9] = NULL;}

		if ( gw_db_file_is_real_directory ( file) == TRUE ) {
			/* Saves all subfolders */
			csv_file_save_folder ( context, node, buf);
		}
	}

	return 0;
}


gint csv_file_save ( GWDBContext *context) {
	GWCatalogPlugin *plugin = gw_db_context_get_plugin ( context);
	FILE *f = NULL;
	GWDBCatalog *catalog = NULL;
	GWDBDisk *disk = NULL;
	GList *categories;
	gint size = 0;
	gchar *mode = "wb+";
	gchar *tmp[9];
	GWStringBuffer *strbuf[2];
	_data *data = gw_db_context_get_data ( context);
	GNode *tree = NULL, *node = NULL;
	gint i = 0, nb = 0;
	gchar *fullfiletmpname = NULL;
	gchar *_tmp = NULL;
	GWDBCategory *category = NULL;

#if GW_DEBUG_TIME
	time_t begin;
	time ( &begin);
#endif

	catalog = data->catalog;

	/* Makes a save in a tempory file to prevent database lost in case of crash. */
	fullfiletmpname = g_strconcat ( gw_db_catalog_get_db_name ( catalog), ".tmp", NULL);

	/* Creates file */
	if ( (data->file = f = fopen ( fullfiletmpname, mode)) == NULL ) {
		return -1;
	}

	/* Writes catalog informations */
	if ( fprintf ( f, "CATALOG_NAME;CATALOG_DESCRIPTION;CATALOG_PROGRAM_BUILDER\n")==0 ) {
		fclose ( f);

		return -1;
	}

	tmp[0] = csv_str_to_file ( gw_db_catalog_get_name ( catalog));
	tmp[1] = csv_str_to_file ( gw_db_catalog_get_description ( catalog));
	tmp[2] = csv_str_to_file ( gw_db_catalog_get_program_builder ( catalog));
	if ( fprintf ( f, "%s;%s;%s\n",
				tmp[0],
				tmp[1],
				tmp[2]) == 0 ) {
		fclose ( f);

		if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
		if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
		if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}

		return -1;
	}

	if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
	if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
	if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}

	if ( fprintf ( f, "\n") == -1 ) {
		fclose ( f);

		return -1;
	}

	/* Writes catelories list */
	if ( fprintf ( f, "CATEGORY_NAME;CATEGORY_DESCRIPTION\n")==0 ) {
		fclose ( f);

		return -1;
	}

	if ( (categories = data->categories) != NULL) {
		categories = g_list_first ( categories);
		size = g_list_length ( categories);

		for ( i = 1; i < size; i++ ) {
			categories = g_list_next ( categories);
			if ( gw_db_category_get_index ( categories->data) != 0) {
				tmp[0] = csv_str_to_file ( gw_db_category_get_name ( categories->data));
				tmp[1] = csv_str_to_file ( gw_db_category_get_description ( categories->data));
				if ( fprintf ( f, "%s;%s\n",
						tmp[0],
						tmp[1]) == 0 ) {
					fclose ( f);

					if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
					if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}

					return -1;
				}

				if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
				if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
			}
		}
	}

	if ( fprintf ( f, "\n") == -1 ) {
		fclose ( f);

		return -1;
	}

	strbuf[0] = gw_string_buffer_new ( );
	strbuf[1] = gw_string_buffer_new ( );

	/* Saves all disks */
	if ( fprintf ( f, "DISK_NAME;DISK_NUM;DISK_FSNAME;DISK_PATH;DISK_FSTYPE;DISK_VOLUME;DISK_FULL;DISK_FREE;DISK_DATE;DISK_SERIAL;DISK_CATEGORY;DISK_DESCRIPTION\n")==0 ) {
		fclose ( f);

		return -1;
	}

	tree = data->tree;
	nb = g_node_n_children ( tree);
	for ( i = 0; i < nb; i++) {
		node = g_node_nth_child ( tree, i);
		disk = (GWDBDisk*)node->data;
		tmp[0] = csv_str_to_file ( gw_db_disk_get_name ( disk));
		tmp[1] = csv_str_to_file ( gw_db_disk_get_fsname ( disk));
		tmp[2] = csv_str_to_file ( gw_db_disk_get_path ( disk));
		tmp[3] = csv_str_to_file ( gw_db_disk_get_fstype ( disk));
		tmp[4] = csv_str_to_file ( gw_db_disk_get_volume ( disk));
		tmp[5] = csv_str_to_file ( gw_db_disk_get_serial ( disk));
		tmp[6] = csv_str_to_file ( gw_db_disk_get_description ( disk));
		category = plugin->gw_db_catalog_get_db_category ( context, gw_db_disk_get_category ( disk));
		if ( gw_db_category_get_index ( category) != 0 ) {
			tmp[7] = csv_str_to_file ( gw_db_category_get_name ( category));
		} else {
			tmp[7] = g_strdup ( "");
		}
		gw_db_category_free ( category);
		tmp[8] = csv_format_date ( gw_db_disk_get_date ( disk));

		_tmp = g_strdup_printf (CSV_LINE_DISK,
					tmp[0],
					gw_db_disk_get_num ( disk),
					tmp[1],
					tmp[2],
					tmp[3],
					tmp[4],
					gw_db_disk_get_full ( disk),
					gw_db_disk_get_free ( disk),
					tmp[8],
					tmp[5],
					tmp[7],
					tmp[6]);
		if ( fprintf ( f, _tmp) == 0 ) {
			fclose ( f);

			g_free ( _tmp);
			if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
			if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
			if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}
			if ( tmp[3] != NULL ) {g_free ( tmp[3]);tmp[3] = NULL;}
			if ( tmp[4] != NULL ) {g_free ( tmp[4]);tmp[4] = NULL;}
			if ( tmp[5] != NULL ) {g_free ( tmp[5]);tmp[5] = NULL;}
			if ( tmp[6] != NULL ) {g_free ( tmp[6]);tmp[6] = NULL;}
			if ( tmp[7] != NULL ) {g_free ( tmp[7]);tmp[7] = NULL;}
			if ( tmp[8] != NULL ) {g_free ( tmp[8]);tmp[8] = NULL;}

			gw_string_buffer_free ( strbuf[0]);
			gw_string_buffer_free ( strbuf[1]);

			return -1;
		}

		g_free ( _tmp);
		if ( tmp[0] != NULL ) {g_free ( tmp[0]);tmp[0] = NULL;}
		if ( tmp[1] != NULL ) {g_free ( tmp[1]);tmp[1] = NULL;}
		if ( tmp[2] != NULL ) {g_free ( tmp[2]);tmp[2] = NULL;}
		if ( tmp[3] != NULL ) {g_free ( tmp[3]);tmp[3] = NULL;}
		if ( tmp[4] != NULL ) {g_free ( tmp[4]);tmp[4] = NULL;}
		if ( tmp[5] != NULL ) {g_free ( tmp[5]);tmp[5] = NULL;}
		if ( tmp[6] != NULL ) {g_free ( tmp[6]);tmp[6] = NULL;}
		if ( tmp[7] != NULL ) {g_free ( tmp[7]);tmp[7] = NULL;}
		if ( tmp[8] != NULL ) {g_free ( tmp[8]);tmp[8] = NULL;}
	}

	if ( fprintf ( f, "\n") == -1 ) {
		fclose ( f);

		return -1;
	}

	/* Saves all files */
	if ( fprintf ( f, "FILE_NAME;FILE_DISK;FILE_LOCATION;FILE_RIGTHS;FILE_OWNER;FILE_GROUP;FILE_INODE;FILE_SIZE;FILE_CREATION_DATE;FILE_ACCESS_DATE;FILE_MODIFICATION_DATE;FILE_CATEGORY;FILE_DESCRIPTION\n")==0 ) {
		fclose ( f);

		return -1;
	}

	for ( i = 0; i < nb; i++) {
		node = g_node_nth_child ( tree, i);
		disk = (GWDBDisk*)node->data;
		data->current_disk_name = gw_db_disk_get_name ( disk);
		csv_file_save_folder ( context, node, strbuf);
		data->current_disk_name = NULL;
	}

	gw_string_buffer_free ( strbuf[0]);
	gw_string_buffer_free ( strbuf[1]);

	/* Closes file */
	if ( fclose ( f) == -1 ) {
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


GWDBContext * plugin_db_catalog_create ( GWCatalogPlugin *plugin, const gchar* name) {
	GWDBContext *context = csv_context_new ( plugin);
	_data *data = gw_db_context_get_data ( context);
	GWDBCatalog *catalog = data->catalog;


	/* Initializes the catalog information */
	gw_db_catalog_set_name ( catalog, g_strdup ( name));
	gw_db_catalog_set_short_db_name ( catalog, g_strdup ( name));

	return context;
}


GWDBContext * plugin_db_catalog_open ( GWCatalogPlugin *plugin, const gchar* path) {
	GWDBContext *context = NULL;
	GWDBCatalog *catalog = NULL;
	GWDBCategory *category = NULL;
	GWDBDisk *disk = NULL;
	FILE *f = NULL;
	_data *data = NULL;
	GWStringBuffer *sb = NULL, *tmp_sb = NULL;
	gchar **tmp = NULL;
	gchar *buf = NULL;
	struct stat f_info;
	GNode *parent = NULL;
	gchar *disk_name = NULL, *location = NULL;
	GWDBFile *file = NULL;
	GWDBFile *folder = NULL, *current = NULL;
	gint i = 0;
	gint index = 0;
	gchar *extension = NULL;


	/* Checks if the given path is valid */
	if ( path==NULL || strlen ( path)==0) {
		return NULL;
	}

	/* Checks if the given file extension is really ".csv" */
	extension = strrchr ( path, '.');
	if ( extension==NULL || strlen ( extension)!=4 || strcmp(".csv",extension)!=0) {
		return NULL;
	}

	/* Reads the CSV file and load all the catalog in memory. */
	if ( (f = fopen ( path, "r")) != NULL ) {
		context = csv_context_new ( plugin);
		data = gw_db_context_get_data ( context);
		catalog = data->catalog;

		if ( stat ( path, &f_info) != -1 ) {
			gw_db_catalog_set_size ( catalog, f_info.st_size);
		}

		gw_db_catalog_set_db_name ( catalog, g_strdup ( path));
		if ( strrchr ( path, G_DIR_SEPARATOR) != NULL) {
			gw_db_catalog_set_short_db_name ( catalog, g_strdup ( strrchr ( path, G_DIR_SEPARATOR) + 1));
		} else {
			//TODO impossible??
			gw_db_catalog_set_short_db_name ( catalog, g_strdup ( path));
		}

		tmp_sb = gw_string_buffer_new ( );

		while ( (buf = cvs_file_read_record ( f, &sb, tmp_sb)) != NULL ) {
			data->sb = sb;

			if ( strcmp ( buf, "CATALOG_NAME;CATALOG_DESCRIPTION;CATALOG_PROGRAM_BUILDER") == 0 ) {
				if ( (buf = cvs_file_read_record ( f, &sb, tmp_sb)) != NULL ) {
					if ( strlen ( buf) == 0 ) {break;}
					gw_db_catalog_set_name ( catalog, cvs_file_read_field_str ( buf, &index));
					gw_db_catalog_set_description ( catalog, cvs_file_read_field_str ( buf, &index));
					gw_db_catalog_set_program_builder ( catalog, cvs_file_read_field_str ( buf, &index));
				}
			} else if ( strcmp ( buf, "CATEGORY_NAME;CATEGORY_DESCRIPTION") == 0 ) {
				while ( (buf = cvs_file_read_record ( f, &sb, tmp_sb)) != NULL ) {
					if ( strlen ( buf) == 0 ) {break;}
					category = csv_category_from_str ( buf, context);

					data->categories = g_list_append ( data->categories, category);
					gw_db_category_set_index ( category, g_list_length ( g_list_first ( data->categories)) - 1);
				}
			} else if ( strcmp ( buf, "DISK_NAME;DISK_NUM;DISK_FSNAME;DISK_PATH;DISK_FSTYPE;DISK_VOLUME;DISK_FULL;DISK_FREE;DISK_DATE;DISK_SERIAL;DISK_CATEGORY;DISK_DESCRIPTION") == 0 ) {
				while ( (buf = cvs_file_read_record ( f, &sb, tmp_sb)) != NULL ) {
					if ( strlen ( buf) == 0 ) {break;}
					disk = csv_disk_from_str ( buf, context);
					g_node_append ( data->tree, parent = g_node_new ( disk));
					gw_db_disk_set_ref ( disk, parent);
				}
				                  
			} else if ( strcmp ( buf, "FILE_NAME;FILE_DISK;FILE_LOCATION;FILE_RIGTHS;FILE_OWNER;FILE_GROUP;FILE_INODE;FILE_SIZE;FILE_CREATION_DATE;FILE_ACCESS_DATE;FILE_MODIFICATION_DATE;FILE_CATEGORY;FILE_DESCRIPTION") == 0 ) {
				while ( (buf = cvs_file_read_record ( f, &sb, tmp_sb)) != NULL ) {
					if ( strlen ( buf) == 0 ) {break;}
					file = csv_file_from_str ( buf, context, &disk_name, &location);
					disk = plugin->gw_db_catalog_get_db_disk_by_name ( context, disk_name);
					tmp = g_strsplit ( location, "/", 0);
					for ( i = 1; (tmp[i] != NULL) && (strlen(tmp[i]) > 0); i++) {
						if ( i == 1 ) {
							folder = plugin->gw_db_disk_get_db_file_by_name ( context, gw_db_disk_get_ref ( disk), tmp[i]);
						} else {
							folder = plugin->gw_db_file_get_db_file_by_name ( context, gw_db_file_get_ref ( current), tmp[i]);
						}

						gw_db_file_free ( current);
						current = folder;
					}

					if ( strcmp ( location, "/") == 0 ) {
						g_node_append ( gw_db_disk_get_ref ( disk), parent = g_node_new ( file));
						gw_db_file_set_ref ( file, parent);
					} else {
						g_node_append ( gw_db_file_get_ref ( current), parent = g_node_new ( file));
						gw_db_file_set_ref ( file, parent);
					}

					g_free ( disk_name);
					g_free ( location);
					g_strfreev ( tmp);
					location = NULL;
				}
			} else {}
		}

		gw_string_buffer_free ( tmp_sb);

		fclose ( f);

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
			result = csv_file_save ( context);
		} else {}
	} else {}

	return result;
}


gint plugin_db_catalog_close ( GWDBContext *context) {
	_data *data = NULL;
	GNode *tree = NULL, *node = NULL;
	gint i = 0, nb = 0;
	gint result = -1;


	if ( context != NULL ) {
		data = gw_db_context_get_data ( context);

		/* Destroys the catalog tree */
		tree = data->tree;
		nb = g_node_n_children ( tree);
		for ( i = 0; i < nb; i++ ) {
			node = g_node_first_child ( tree);
			if ( node != NULL ) {
				g_node_disk_free ( node, NULL);
			} else {}
		}

		/* Frees the catalog information */
		gw_db_catalog_free ( data->catalog);

		/* Frees all the categories */
		if ( data->categories != NULL ) {
			g_list_foreach ( data->categories, (GFunc)gw_db_data_category_free, NULL);
			g_list_free ( data->categories);
		}

		/* Destroys all the data context */
		gw_string_buffer_free ( data->sb);
		g_free ( data);

		result = 0;

	}

	return result;
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

		categories = g_list_remove ( categories, gw_db_category_get_ref ( category));
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
	gchar *short_db_name = NULL, *db_name = NULL;


	if ( context != NULL && catalog != NULL ) {
		data = gw_db_context_get_data ( context);
		//TODO it should be better to test if catalog is correct
		catalog_dup = data->catalog;
		if ( !gw_db_catalog_equals ( catalog_dup, catalog) ) {
			gw_db_catalog_dup ( catalog, &catalog_dup);
			db_name = gw_db_catalog_get_db_name ( catalog_dup);
			if ( strlen ( db_name) < 4 || strcmp ( ".csv", &db_name[strlen ( db_name)-4]) != 0 ) {
				gw_db_catalog_set_db_name ( catalog_dup, g_strconcat ( db_name, ".csv", NULL));
			}
			short_db_name = gw_db_catalog_get_short_db_name ( catalog_dup);
			if ( strlen ( short_db_name) < 4 || strcmp ( ".csv", &short_db_name[strlen ( short_db_name)-4]) != 0 ) {
				gw_db_catalog_set_short_db_name ( catalog_dup, g_strconcat ( short_db_name, ".csv", NULL));
			}

			gw_db_catalog_set_ismodified ( catalog_dup, TRUE);

			return 0;
		}
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


	gw_plugin_info_set_name ( plugin_info, g_strdup ( "CSV catalog"));
	gw_plugin_info_set_version ( plugin_info, g_strdup ( "1.0.0"));
	gw_plugin_info_set_author ( plugin_info, g_strdup ( "Sébastien LECACHEUR"));
	gw_plugin_info_set_description ( plugin_info, g_strdup ( "Store any catalog in a simple CSV file."));
	gw_plugin_info_set_help ( plugin_info, g_strdup ( "There is no help at time"));

	return plugin_info;
}

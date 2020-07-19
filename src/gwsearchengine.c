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


#include "gwsupport.h"
#include "gwsearchengine.h"

#include <gtk/gtk.h>

#include <string.h> /* strcmp */

#include "data/gwdata.h"
#include "tools/gwtools.h"
#include "res/gwres.h"
#include "gui/gwgui.h"

#include "gwapplicationmanager.h"
#include "gwguimanager.h"
#include "gwhelper.h"


gulong search_engine_search_in_disk ( GtkWindow *w, struct user_quick_search *uqs) {
	GtkCList *clist_result = NULL;
	GtkCTreeNode *root = gw_gui_manager_main_interface_get_tree_root ( );
	struct engine_quick_search *engine_qs = NULL;
	gulong result = 0;
	gboolean all_words = FALSE;
	GWRegex regex;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBDisk **disks = NULL;
	GWDBFile **files = NULL;
	gint i = 0, j = 0;
	GWDBCategory *category = NULL;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			engine_qs = user_quick_search_to_engine_quick_search ( uqs);
			if ( (all_words = gw_am_get_settings_tol ( GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE)) == -1 ) {
				all_words = GW_VALUE_APP_SEARCH_TYPE_KEY_WORDS_MODE_DEFAULT;
			}
			engine_quick_search_set_match_all_key_words ( engine_qs, !all_words);
			clist_result = gw_notebook_search_get_clist_search ( w);

			memset ( &regex, '\0', sizeof ( GWRegex));
			if ( engine_quick_search_get_type ( engine_qs) != SEARCH_TYPE_KEY_WORDS ) {
				if ( regcomp ( &(regex.r), engine_quick_search_get_pattern ( engine_qs), (engine_quick_search_get_case_sensitive ( engine_qs)==FALSE?REG_ICASE:0)|REG_NOSUB) != 0) {
					/* Regcomp error!! */
				}
			}

			if ( (root != NULL) && ( ((engine_quick_search_get_type ( engine_qs) == SEARCH_TYPE_KEY_WORDS) && (engine_quick_search_get_key_words ( engine_qs) != NULL)) || (engine_quick_search_get_pattern ( engine_qs) != NULL)) ) {
				/* Clears the old search result */
				gtk_clist_clear ( clist_result);

				/* Browses all disks of catalog */
				if ( (disks = plugin->gw_db_catalog_get_db_disks ( context)) != NULL) {
					for ( i = 0; disks[i] != NULL; i++) {
						category = plugin->gw_db_catalog_get_db_category ( context, gw_db_disk_get_category ( disks[i]));
						if ( search_engine_check_disk_match ( disks[i], category, engine_qs, &regex) == 0 ) {
							search_engine_add_disk ( clist_result, disks[i], category);
							result++;
						} else {
							gw_db_category_free ( category);
						}

						if ( (files = plugin->gw_db_disk_get_db_files ( context, gw_db_disk_get_ref ( disks[i]))) != NULL) {
							for ( j = 0; files[j] != NULL; j++) {
								category = plugin->gw_db_catalog_get_db_category ( context, gw_db_file_get_category ( files[j]));
								if ( search_engine_check_file_match ( files[j], category, engine_qs, &regex) == 0 ) {
									search_engine_add_item ( clist_result, files[j], category);
									result++;
								} else {
									gw_db_category_free ( category);
								}

								if ( gw_db_file_is_real_directory ( files[j])) {
									result += search_engine_search_in_dir ( files[j], engine_qs, &regex);
								} else {}

								gw_db_file_free ( files[j]);
							}

							g_free ( files);
						} else {}

						gw_db_disk_free ( disks[i]);
					}

					g_free ( disks);
				}
			}

			if ( engine_quick_search_get_type ( engine_qs) != SEARCH_TYPE_KEY_WORDS ) {
				regfree ( &(regex.r));
			}
		} else {}
	} else {}

	return result;
}


gulong search_engine_search_in_dir ( GWDBFile *folder, struct engine_quick_search *eqs, GWRegex *regex) {
	GtkCList *clist_result = NULL;
	GtkWindow *window = gw_gui_manager_main_interface_get_main_window ( );
	gulong result = 0;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBFile **files = NULL;
	GWDBCategory *category = NULL;
	gint i = 0;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			clist_result = gw_notebook_search_get_clist_search ( window);

			if ( (files = plugin->gw_db_file_get_db_files ( context, gw_db_file_get_ref ( folder))) != NULL) {
				for ( i = 0; files[i] != NULL; i++) {
					category = plugin->gw_db_catalog_get_db_category ( context, gw_db_file_get_category ( files[i]));
					if ( search_engine_check_file_match ( files[i], category, eqs, regex) == 0 ) {
						search_engine_add_item ( clist_result, files[i], category);
						result++;
					} else {
						gw_db_category_free ( category);
					}

					if ( gw_db_file_is_real_directory ( files[i])) {
						result += search_engine_search_in_dir ( files[i], eqs, regex);
					} else { }

					gw_db_file_free ( files[i]);
				}

				g_free ( files);
			} else { }
		} else {}
	} else {}

	return result;
}


gint search_engine_check_disk_match ( GWDBDisk *disk, GWDBCategory *category, struct engine_quick_search *eqs, GWRegex *regex) {
	gint result = -1;
	gchar *word = NULL;
	gchar **words = NULL;
	gint i = 0;
	gint all_words = -1;
	gboolean case_sensitive;


	if ( ( disk != NULL ) || ( eqs != NULL ) ) {
		if ( engine_quick_search_get_match_disk ( eqs) ) {
			case_sensitive = engine_quick_search_get_case_sensitive ( eqs);

			if ( engine_quick_search_get_type ( eqs) == SEARCH_TYPE_KEY_WORDS ) {
				words = engine_quick_search_get_key_words ( eqs);
				all_words = !engine_quick_search_get_match_all_key_words ( eqs);

				if ( all_words == 0) {
					result = -1;

					for ( i = 0; ((words[i] != NULL) && ( result == -1)); i++) {
						if ( gw_strcmp_strregex ( gw_db_disk_get_name ( disk), words[i], case_sensitive) == 0 ) {
							result = 0;
							break;
						}
					}

					if ( engine_quick_search_get_match_category ( eqs) && category != NULL ) {
						for ( i = 0; ((words[i] != NULL) && ( result == -1)); i++) {
							if ( gw_strcmp_strregex ( gw_db_category_get_name ( category), words[i], case_sensitive) == 0 ) {
								result = 0;
								break;
							}
						}
					}

					if ( engine_quick_search_get_match_description ( eqs) && gw_db_disk_get_description ( disk) != NULL ) {
						for ( i = 0; ((words[i] != NULL) && ( result == -1)); i++) {
							if ( gw_strcmp_strregex ( gw_db_disk_get_description ( disk), words[i], case_sensitive) == 0 ) {
								result = 0;
								break;
							}
						}
					}
				} else {
					result = 0;

					for ( i = 0; ((words[i] != NULL) && ( result == 0)); i++) {
						if ( gw_strcmp_strregex ( gw_db_disk_get_name ( disk), words[i], case_sensitive) != 0 ) {
							result = -1;
							break;
						}
					}

					if ( result != 0) {
						if ( engine_quick_search_get_match_category ( eqs) ) {
							result = 0;

							for ( i = 0; ((words[i] != NULL) && ( result == 0)); i++) {
								if ( gw_strcmp_strregex ( gw_db_category_get_name ( category), words[i], case_sensitive) != 0 ) {
									result = -1;
									break;
								}
							}
						}

						if ( result != 0 ) {
							if ( engine_quick_search_get_match_description ( eqs) ) {
								result = 0;

								for ( i = 0; ((words[i] != NULL) && ( result == 0)); i++) {
									if ( gw_strcmp_strregex ( gw_db_disk_get_description ( disk), words[i], case_sensitive) != 0 ) {
										result = -1;
										break;
									}
								}
							}
						}
					}
				}
			} else {
				word = engine_quick_search_get_pattern ( eqs);

				if ( (regexec ( &(regex->r), gw_db_disk_get_name ( disk), 0, NULL, 0) == 0 ) ||
					(engine_quick_search_get_match_category ( eqs) && gw_db_category_get_name ( category) != NULL && regexec ( &(regex->r), gw_db_category_get_name ( category), 0, NULL, 0) == 0) ||
					(engine_quick_search_get_match_description ( eqs) && gw_db_disk_get_description ( disk) != NULL && regexec ( &(regex->r), gw_db_disk_get_description ( disk), 0, NULL, 0) == 0)) {
					result = 0;
				}
 			}

		}
	}

	return result;
}


gint search_engine_check_file_match ( GWDBFile *file, GWDBCategory *category, struct engine_quick_search *eqs, GWRegex *regex) {
	gint result = -1;
	gchar *word = NULL;
	gchar **words = NULL;
	gint i = 0;
	gint all_words = -1;
	gboolean case_sensitive;


	if ( ( file != NULL ) || ( eqs != NULL ) ) {
		if ( ( engine_quick_search_get_match_file ( eqs) && !gw_db_file_is_real_directory ( file) ) || ( engine_quick_search_get_match_folder ( eqs) && gw_db_file_is_real_directory ( file) ) ) {
			case_sensitive = engine_quick_search_get_case_sensitive ( eqs);
			if ( engine_quick_search_get_type ( eqs) == SEARCH_TYPE_KEY_WORDS ) {
				words = engine_quick_search_get_key_words ( eqs);
				all_words = !engine_quick_search_get_match_all_key_words ( eqs);

				if ( all_words == 0) {
					result = -1;

					for ( i = 0; ((words[i] != NULL) && ( result == -1)); i++) {
						if ( gw_strcmp_strregex ( gw_db_file_get_name ( file), words[i], case_sensitive) == 0 ) {
							result = 0;
							break;
						}
					}

					if ( engine_quick_search_get_match_category ( eqs) && category != NULL ) {
						for ( i = 0; ((words[i] != NULL) && ( result == -1)); i++) {
							if ( gw_strcmp_strregex ( gw_db_category_get_name ( category), words[i], case_sensitive) == 0 ) {
								result = 0;
								break;
							}
						}
					}

					if ( engine_quick_search_get_match_description ( eqs) && gw_db_file_get_description ( file) != NULL ) {
						for ( i = 0; ((words[i] != NULL) && ( result == -1)); i++) {
							if ( gw_strcmp_strregex ( gw_db_file_get_description ( file), words[i], case_sensitive) == 0 ) {
								result = 0;
								break;
							}
						}
					}
				} else {
					result = 0;

					for ( i = 0; ((words[i] != NULL) && ( result == 0)); i++) {
						if ( gw_strcmp_strregex ( gw_db_file_get_name ( file), words[i], case_sensitive) != 0 ) {
							result = -1;
							break;
						}
					}

					if ( result != 0 ) {
						if ( engine_quick_search_get_match_category ( eqs) ) {
							result = 0;

							for ( i = 0; ((words[i] != NULL) && ( result == 0)); i++) {
								if ( gw_strcmp_strregex ( gw_db_category_get_name ( category), words[i], case_sensitive) != 0 ) {
									result = -1;
									break;
								}
							}
						}

						if ( result != 0 ) {
							if ( engine_quick_search_get_match_description ( eqs) && gw_db_file_get_description ( file) != NULL ) {
								result = 0;

								for ( i = 0; ((words[i] != NULL) && ( result == 0)); i++) {
									if ( gw_strcmp_strregex ( gw_db_file_get_description ( file), words[i], case_sensitive) != 0 ) {
										result = -1;
										break;
									}
								}
							}
						}
					}
				}
			} else {
				word = engine_quick_search_get_pattern ( eqs);

				if ( (regexec ( &(regex->r), gw_db_file_get_name ( file), 0, NULL, 0) == 0 ) ||
					(engine_quick_search_get_match_category ( eqs) && gw_db_category_get_name ( category) != NULL && regexec ( &(regex->r), gw_db_category_get_name ( category), 0, NULL, 0) == 0) ||
					(engine_quick_search_get_match_description ( eqs) && gw_db_file_get_description ( file) != NULL && regexec ( &(regex->r), gw_db_file_get_description ( file), 0, NULL, 0) == 0)) {
					result = 0;
				}
			}
		}
	}

	return result;
}


gint search_engine_add_item ( GtkCList *clist, GWDBFile *file, GWDBCategory *category) {
	gint result = -1;
	gchar *info[7];
	gint row, i;
	gchar *text_utf8 = NULL;
	gchar *location = NULL, *tmp = NULL;
	struct search_item_info *search_item = NULL;
	GWDBContext *context = gw_am_get_current_catalog_context ( );
	GWCatalogPlugin *plugin = NULL;
	GWDBDisk *disk = NULL;


	if ( context != NULL) {
		if ( (plugin = (GWCatalogPlugin*)gw_db_context_get_plugin ( context)) != NULL ) {
			if ( file != NULL ) {
				disk = plugin->gw_db_file_get_db_disk ( context, gw_db_file_get_ref ( file));
				g_strdup_to_gtk_text ( gw_db_file_get_name ( file), info[0]);
				g_strdup_to_gtk_text ( gw_db_disk_get_name ( disk), info[1]);
				g_strdup_to_gtk_text ( (location = plugin->gw_db_file_get_location ( context, gw_db_file_get_ref ( file))), info[2]);
				text_utf8 = gw_l_byte_to_str_format ( gw_db_file_get_size ( file));
				g_strdup_to_gtk_text ( text_utf8, info[3]);
				g_free ( text_utf8);
				tmp = gw_helper_db_file_get_cdate_to_str ( file);
				g_strdup_to_gtk_text ( tmp, info[4]);
				g_free ( tmp);
				g_strdup_to_gtk_text ( gw_db_category_get_name ( category), info[5]);
				g_strdup_to_gtk_text ( gw_db_file_get_description ( file), info[6]);
				gw_str_replace_char ( info[6], '\n', ' ');

				row = gtk_clist_append ( clist, info);

				search_item = search_item_info_new ( );
				if ( gw_db_file_is_real_directory ( file)) {
					search_item_info_set_type ( search_item, SEARCH_ITEM_TYPE_FOLDER);
				} else {
					search_item_info_set_type ( search_item, SEARCH_ITEM_TYPE_FILE);
				}
				search_item_info_set_name ( search_item, g_strdup ( gw_db_file_get_name ( file)));
				search_item_info_set_disk ( search_item, g_strdup ( gw_db_disk_get_name ( disk)));
				search_item_info_set_path ( search_item, location);
				search_item_info_set_size ( search_item, gw_db_file_get_size ( file));
				search_item_info_set_date ( search_item, gw_db_file_get_cdate ( file));
				search_item_info_set_category ( search_item, category);
				if ( gw_db_file_get_description ( file) != NULL ) {
					search_item_info_set_description ( search_item, g_strdup ( gw_db_file_get_description ( file)));
				}

				/* Note : doesn't give the free function else data will be destroy from database */
				gtk_clist_set_row_data_full ( clist, row, (struct search_item_info*)search_item, /*(GtkDestroyNotify)search_item_info_free*/NULL);

				if ( gw_db_file_is_real_directory ( file)) {
					gtk_clist_set_pixtext ( clist, row, 0, info[0], 5, PixFolder, MskFolder);
				} else {
					gtk_clist_set_pixtext ( clist, row, 0, info[0], 5, PixFile, MskFile);
				}

				for ( i = 0; i <= 6; i++) {
					g_free ( info[i]);
				}
				gw_db_disk_free ( disk);

				result = 0;
			}
		} else {}
	} else {}

	return result;
}


gint search_engine_add_disk ( GtkCList *clist, GWDBDisk *disk, GWDBCategory *category) {
	gint result = -1;
	gchar *info[7];
	gint row, i;
	gchar *text_utf8 = NULL;
	gchar *tmp = NULL;
	struct search_item_info *search_item = NULL;


	if ( disk != NULL ) {
		g_strdup_to_gtk_text ( gw_db_disk_get_name ( disk), info[0]);
		g_strdup_to_gtk_text ( gw_db_disk_get_name ( disk), info[1]);
		g_strdup_to_gtk_text ( "", info[2]);
		text_utf8 = gw_ui64_byte_to_str_format ( gw_db_disk_get_full ( disk));
		g_strdup_to_gtk_text ( text_utf8, info[3]);
		g_free ( text_utf8);
		tmp = gw_helper_db_disk_get_date_to_str ( disk);
		g_strdup_to_gtk_text ( tmp, info[4]);
		g_free ( tmp);
		g_strdup_to_gtk_text ( gw_db_category_get_name ( category), info[5]);
		g_strdup_to_gtk_text ( gw_db_disk_get_description ( disk), info[6]);
		gw_str_replace_char ( info[6], '\n', ' ');

		row = gtk_clist_append ( clist, info);

		//TODO don't use SearchItem but DiskInfo
		search_item = search_item_info_new ( );
		search_item_info_set_type ( search_item, SEARCH_ITEM_TYPE_DISK);
		search_item_info_set_name ( search_item, g_strdup ( gw_db_disk_get_name ( disk)));
		search_item_info_set_disk ( search_item, g_strdup ( gw_db_disk_get_name ( disk)));
		search_item_info_set_size ( search_item, gw_db_disk_get_full ( disk));
		search_item_info_set_date ( search_item, gw_db_disk_get_date ( disk));
		search_item_info_set_category ( search_item, category);
		search_item_info_set_description ( search_item, g_strdup ( gw_db_disk_get_description ( disk)));

		/* Note : doesn't give the free function else data will be destroy from database */
		gtk_clist_set_row_data_full ( clist, row, (struct search_item_info*)search_item, (GtkDestroyNotify) search_item_info_free);

		gtk_clist_set_pixtext ( clist, row, 0, info[0], 5, gw_helper_db_disk_get_pixmap ( disk), gw_helper_db_disk_get_bitmap ( disk));

		for ( i = 0; i <= 6; i++) {
			g_free ( info[i]);
		}

		result = 0;
	}

	return result;
}

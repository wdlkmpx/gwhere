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
#include "gwmenufile.h"

#include <gdk/gdkkeysyms.h>

#include "gwmenufilecallback.h"
#include "gwreferences.h"


/*! @define	GW_REF_MENU_BAR_FILE_MENU_HEADER	The file menu header reference */
#define GW_REF_MENU_BAR_FILE_MENU_HEADER "gw_menu_bar_file_menu_header"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_NEW	The file menu -> new reference */
#define GW_REF_MENU_BAR_FILE_MENU_NEW "gw_menu_bar_file_menu_new"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_OPEN	The file menu -> open reference */
#define GW_REF_MENU_BAR_FILE_MENU_OPEN "gw_menu_bar_file_menu_open"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_SAVE	The file menu -> save reference */
#define GW_REF_MENU_BAR_FILE_MENU_SAVE "gw_menu_bar_file_menu_save"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_SAVEAS	The file menu -> save as reference */
#define GW_REF_MENU_BAR_FILE_MENU_SAVEAS "gw_menu_bar_file_menu_saveas"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_CLOSE	The file menu -> close reference */
#define GW_REF_MENU_BAR_FILE_MENU_CLOSE "gw_menu_bar_file_menu_close"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_SEPARATOR	The file menu -> separator reference */
#define GW_REF_MENU_BAR_FILE_MENU_SEPARATOR "gw_menu_bar_file_menu_separator"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_IMPORT	The file menu -> import reference */
#define GW_REF_MENU_BAR_FILE_MENU_IMPORT "gw_menu_bar_file_menu_import"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_EXPORT	The file menu -> export reference */
#define GW_REF_MENU_BAR_FILE_MENU_EXPORT "gw_menu_bar_file_menu_export"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_PROPERTIES	The file menu -> properties reference */
#define GW_REF_MENU_BAR_FILE_MENU_PROPERTIES "gw_menu_bar_file_menu_properties"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_RECENT_FILES	The file menu -> recent files reference */
#define GW_REF_MENU_BAR_FILE_MENU_RECENT_FILES "gw_menu_bar_file_menu_recent_files"
/*! @define	GW_REF_MENU_BAR_FILE_MENU_EXIT	The file menu -> exit reference */
#define GW_REF_MENU_BAR_FILE_MENU_EXIT "gw_menu_bar_file_menu_exit"
/*! @define	GW_REF_MENU_BAR_FILE_MENU	The file menu reference */
#define GW_REF_MENU_BAR_FILE_MENU "gw_menu_bar_file_menu"


GtkWidget * gw_menu_file_create ( GtkWindow *w, GtkAccelGroup *ag, GtkWidget *parent) {
	GtkWidget *gw_menu_file_header = NULL;
	GtkWidget *menu_file = NULL;
	GtkWidget *gw_menu_file_new = NULL;
	GtkWidget *gw_menu_file_open = NULL;
	GtkWidget *gw_menu_file_save = NULL;
	GtkWidget *gw_menu_file_saveas = NULL;
	GtkWidget *gw_menu_file_close = NULL;
	GtkWidget *gw_menu_file_separator = NULL;
	GtkWidget *gw_menu_file_import = NULL;
	GtkWidget *gw_menu_file_import_items = NULL;
	GtkWidget *gw_menu_file_export = NULL;
	GtkWidget *gw_menu_file_export_items = NULL;
	GtkWidget *gw_menu_file_properties = NULL;
	GtkWidget *gw_menu_file_recent_files = NULL;
	GtkWidget *gw_menu_file_recent_files_items = NULL;
	GtkWidget *gw_menu_file_exit = NULL;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	/* Menu file header */
	gw_menu_file_header = gtk_menu_item_new_with_mnemonic (_("_File"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_HEADER, gw_menu_file_header);

	menu_file = gtk_menu_new ( );
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU, menu_file);
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_header), menu_file);

	/* Menu file -> new */
	gw_menu_file_new = gtk_menu_item_new_with_mnemonic (_("_New"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_NEW, gw_menu_file_new);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_new);
	gtk_widget_add_accelerator ( gw_menu_file_new, "activate", ag, GDK_KEY(n), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_file_new), "activate", G_CALLBACK ( gw_menu_file_new_click), w);

	/* Menu file -> open */
	gw_menu_file_open = gtk_menu_item_new_with_mnemonic (_( "_Open"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_OPEN, gw_menu_file_open);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_open);
	gtk_widget_add_accelerator ( gw_menu_file_open, "activate", ag, GDK_KEY(o), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_file_open), "activate", G_CALLBACK ( gw_menu_file_open_click), w);

	/* Menu file -> save */
	gw_menu_file_save = gtk_menu_item_new_with_mnemonic (_( "_Save"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SAVE, gw_menu_file_save);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_save);
	gtk_widget_add_accelerator ( gw_menu_file_save, "activate", ag, GDK_KEY(s), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_file_save), "activate", G_CALLBACK ( gw_menu_file_save_click), w);

	/* Menu file -> save as */
	gw_menu_file_saveas = gtk_menu_item_new_with_mnemonic (_( "Sav_e as"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SAVEAS, gw_menu_file_saveas);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_saveas);
	gtk_widget_add_accelerator ( gw_menu_file_saveas, "activate", ag, GDK_KEY(e), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_file_saveas), "activate", G_CALLBACK ( gw_menu_file_saveas_click), w);

	/* Menu file -> close */
	gw_menu_file_close = gtk_menu_item_new_with_mnemonic (_( "C_lose"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_CLOSE, gw_menu_file_close);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_close);
	gtk_widget_add_accelerator ( gw_menu_file_close, "activate", ag, GDK_KEY(f), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_file_close), "activate",G_CALLBACK ( gw_menu_file_close_click), w);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> import catalog */
	gw_menu_file_import = gtk_menu_item_new_with_mnemonic (_( "Import"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_IMPORT, gw_menu_file_import);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_import);

	gw_menu_file_import_items = gtk_menu_new ( );
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_import), gw_menu_file_import_items);

	/* Menu file -> export catalog */
	gw_menu_file_export = gtk_menu_item_new_with_mnemonic (_( "Export"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_EXPORT, gw_menu_file_export);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_export);

	gw_menu_file_export_items = gtk_menu_new ( );
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_export), gw_menu_file_export_items);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> properties */
	gw_menu_file_properties = gtk_menu_item_new_with_mnemonic (_("_Properties"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_PROPERTIES, gw_menu_file_properties);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_properties);
	gtk_widget_add_accelerator ( gw_menu_file_properties, "activate", ag, GDK_KEY(p), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_file_properties), "activate", G_CALLBACK ( gw_menu_file_properties_click), w);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> recent files */
	gw_menu_file_recent_files = gtk_menu_item_new_with_mnemonic (_( "_Recent files"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_RECENT_FILES, gw_menu_file_recent_files);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_recent_files);
	gtk_widget_add_accelerator ( gw_menu_file_recent_files, "activate", ag, GDK_KEY(r), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

	gw_menu_file_recent_files_items = gtk_menu_new ( );
	gtk_menu_item_set_submenu ( GTK_MENU_ITEM ( gw_menu_file_recent_files), gw_menu_file_recent_files_items);

	/* Menu file -> separator */
	gw_menu_file_separator = gtk_menu_item_new ( );
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_SEPARATOR, gw_menu_file_separator);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_separator);
	gtk_widget_set_sensitive ( gw_menu_file_separator, FALSE);

	/* Menu file -> exit */
	gw_menu_file_exit = gtk_menu_item_new_with_mnemonic (_( "E_xit"));
	g_object_set_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_EXIT, gw_menu_file_exit);
	gtk_container_add ( GTK_CONTAINER ( menu_file), gw_menu_file_exit);
	gtk_widget_add_accelerator ( gw_menu_file_exit, "activate", ag, GDK_KEY(x), GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect (G_OBJECT ( gw_menu_file_exit), "activate", G_CALLBACK ( gw_menu_file_exit_click), w);

	return gw_menu_file_header;
}


gboolean gw_menu_file_set_import ( GtkWindow *w, gchar **plugins) {
	gboolean result = FALSE;
	GtkMenuItem *import_menu = NULL;
	GtkWidget *menu_item_import = NULL;
	GtkWidget *import_submenu = NULL;
	guint i = 0;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && (plugins != NULL) ) {
		import_menu = GTK_MENU_ITEM ( g_object_get_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_IMPORT));

		if ( import_menu != NULL ) {
			gtk_menu_item_set_submenu (import_menu, NULL);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			import_submenu = gtk_menu_new ( );
			gtk_menu_item_set_submenu ( import_menu, import_submenu);

			for ( i = 0; plugins[i] != NULL; i++) {
#ifdef GW_DEBUG_GUI_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item at %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item => %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, plugins[i]);
#endif
				menu_item_import = gtk_menu_item_new_with_label (plugins[i]);
				gtk_container_add ( GTK_CONTAINER ( import_submenu), menu_item_import);

				g_signal_connect (G_OBJECT ( menu_item_import), "activate", G_CALLBACK ( gw_menu_file_import_item_click), plugins[i]);
			}

			gtk_widget_show_all ( GTK_WIDGET ( import_menu));

			result = TRUE;
		}

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : import plugins are added.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return result;
}


gboolean gw_menu_file_set_export ( GtkWindow *w, gchar **plugins) {
	gboolean result = FALSE;
	GtkMenuItem *import_menu = NULL;
	GtkWidget *menu_item_import = NULL;
	GtkWidget *import_submenu = NULL;
	guint i = 0;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && (plugins != NULL) ) {
		import_menu = GTK_MENU_ITEM ( g_object_get_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_EXPORT));

		if ( import_menu != NULL ) {
			gtk_menu_item_set_submenu ( import_menu, NULL);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			import_submenu = gtk_menu_new ( );
			gtk_menu_item_set_submenu ( import_menu, import_submenu);

			for ( i = 0; plugins[i] != NULL; i++) {
#ifdef GW_DEBUG_GUI_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item at %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item => %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, plugins[i]);
#endif
				menu_item_import = gtk_menu_item_new_with_label (plugins[i]);
				gtk_container_add ( GTK_CONTAINER ( import_submenu), menu_item_import);

				/* Warning use a gint value instead of a gpointer value!! */
				g_signal_connect (G_OBJECT ( menu_item_import), "activate", G_CALLBACK ( gw_menu_file_export_item_click), /*GUINT_TO_POINTER ( i)*/g_strdup ( plugins[i]));
			}

			gtk_widget_show_all ( GTK_WIDGET ( import_menu));

			result = TRUE;
		}

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : export plugins are added.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return result;
}


gboolean gw_menu_file_set_recent_files ( GtkWindow *w, gchar **files) {
	gboolean result = FALSE;
	GtkMenuItem *recent_files_menu = NULL;
	GtkWidget *menu_item_recent_files = NULL;
	GtkWidget *recent_files_submenu = NULL;
	guint i = 0;

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s()\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

	if ( (w != NULL) && (files != NULL) ) {
		recent_files_menu = GTK_MENU_ITEM ( g_object_get_data (G_OBJECT ( w), GW_REF_MENU_BAR_FILE_MENU_RECENT_FILES));

		if ( recent_files_menu != NULL ) {
			gtk_menu_item_set_submenu ( recent_files_menu, NULL);

#ifdef GW_DEBUG_GUI_COMPONENT
			g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu...\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif

			recent_files_submenu = gtk_menu_new ( );
			gtk_menu_item_set_submenu ( recent_files_menu, recent_files_submenu);

			for ( i = 0; files[i] != NULL; i++) {
#ifdef GW_DEBUG_GUI_COMPONENT
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item at %d\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, i);
				g_print ( "*** GW - %s (%d) :: %s() : Creating a new submenu item => %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, files[i]);
#endif

				menu_item_recent_files = gtk_menu_item_new_with_label (files[i]);
				gtk_container_add ( GTK_CONTAINER ( recent_files_submenu), menu_item_recent_files);

				/* Warning use a gint value instead of a gpointer value!! */
				g_signal_connect (G_OBJECT ( menu_item_recent_files), "activate", G_CALLBACK ( gw_menu_file_recent_files_item_click), GUINT_TO_POINTER ( i));
			}

			gtk_widget_show_all ( GTK_WIDGET ( recent_files_menu));

			result = TRUE;
		}

#ifdef GW_DEBUG_GUI_COMPONENT
	g_print ( "*** GW - %s (%d) :: %s() : recent opened catalog files are added.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
#endif
	}

	return result;
}

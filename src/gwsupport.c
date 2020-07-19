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

/*
#ifdef HAVE_CONFIG_H
    #if defined ( OS_LINUX) || defined ( OS_CYGWIN )
        #include <config.h>
    #elif defined ( OS_WIN32)
        #include "../config_win32.h"
    #endif
#endif
*/
#if defined ( OS_WIN32)
	#include <winreg.h>
#endif

#include <stdlib.h> /* atoi */
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gtk/gtk.h>


/* This is an internally used function to check if a pixmap file exists. */
static gchar* check_file_exists ( const gchar *directory, const gchar *filename);

/* This is an internally used function to create pixmaps. */
static GtkWidget* create_dummy_pixmap ( GtkWidget *widget);

GtkWidget* lookup_widget ( GtkWidget *widget, const gchar *widget_name) {
	GtkWidget *parent, *found_widget;

	for (;;) {
		if (GTK_IS_MENU (widget))
			parent = gtk_menu_get_attach_widget (GTK_MENU (widget));
		else
			parent = widget->parent;
		if (parent == NULL)
			break;
		widget = parent;
		}

	found_widget = (GtkWidget*) gtk_object_get_data (GTK_OBJECT (widget),
                                                   widget_name);
	if (!found_widget)
		g_warning ("Widget not found: %s", widget_name);
	return found_widget;
	}


/* This is a dummy pixmap we use when a pixmap can't be found. */
static char *dummy_pixmap_xpm[] = {	/* columns rows colors chars-per-pixel	*/
					"1 1 1 1",
					"  c None",
					/* pixels				*/
					" "
					};


/* This is an internally used function to create pixmaps. */
static GtkWidget* create_dummy_pixmap ( GtkWidget *widget) {
	GdkColormap *colormap;
	GdkPixmap *gdkpixmap;
	GdkBitmap *mask;
	GtkWidget *pixmap;

	colormap = gtk_widget_get_colormap (widget);
	gdkpixmap = gdk_pixmap_colormap_create_from_xpm_d ( NULL, colormap, &mask, NULL, dummy_pixmap_xpm);
	if (gdkpixmap == NULL)
		g_error ("Couldn't create replacement pixmap.");
	pixmap = gtk_pixmap_new (gdkpixmap, mask);
	gdk_pixmap_unref (gdkpixmap);
	gdk_bitmap_unref (mask);
	return pixmap;
	}


static GList *pixmaps_directories = NULL;

/* Use this function to set the directory containing installed pixmaps. */
void add_pixmap_directory ( const gchar     *directory) {
	pixmaps_directories = g_list_prepend ( pixmaps_directories, g_strdup (directory));
	}


/* This is an internally used function to create pixmaps. */
GtkWidget* create_pixmap ( GtkWidget *widget, const gchar *filename) {
	gchar *found_filename = NULL;
	GdkColormap *colormap;
	GdkPixmap *gdkpixmap;
	GdkBitmap *mask;
	GtkWidget *pixmap;
	GList *elem;

	/* We first try any pixmaps directories set by the application. */
	elem = pixmaps_directories;
	while (elem) {
		found_filename = check_file_exists ((gchar*)elem->data, filename);
		if (found_filename)
			break;
		elem = elem->next;
		}

	/* If we haven't found the pixmap, try the source directory. */
	if (!found_filename) {
		found_filename = check_file_exists ("../pixmaps", filename);
		}

	if (!found_filename) {
		g_warning (_("Couldn't find pixmap file: %s"), filename);
		return create_dummy_pixmap (widget);
		}

	colormap = gtk_widget_get_colormap (widget);
	gdkpixmap = gdk_pixmap_colormap_create_from_xpm ( NULL, colormap, &mask, NULL, found_filename);
	if (gdkpixmap == NULL) {
		g_warning (_("Error loading pixmap file: %s"), found_filename);
		g_free (found_filename);
		return create_dummy_pixmap (widget);
		}
	g_free (found_filename);
	pixmap = gtk_pixmap_new (gdkpixmap, mask);
	gdk_pixmap_unref (gdkpixmap);
	gdk_bitmap_unref (mask);
	return pixmap;
	}


/* This is an internally used function to check if a pixmap file exists. */
gchar* check_file_exists ( const gchar *directory, const gchar *filename) {
	gchar *full_filename;
	struct stat s;
	gint status;


	full_filename = (gchar*) g_malloc ( strlen ( directory) + 1 + strlen ( filename) + 1);
	strcpy ( full_filename, directory);
	strcat ( full_filename, G_DIR_SEPARATOR_S);
	strcat ( full_filename, filename);

	status = stat ( full_filename, &s);
	if ( status == 0 && S_ISREG ( s.st_mode) )
	{
		return full_filename;
	}

	g_free ( full_filename);

	return NULL;
}


#if defined ( OS_WIN32) || defined ( OS_CYGWIN)


int gw_win32_get_version ( int *sys_type, int *version_major, int *version_minor, int *service_pack)
{
	BOOL result;
	OSVERSIONINFO osvi;
	char pack[4]="-1";

	/* First check what version of Windows we're in. */
	osvi.dwOSVersionInfoSize = sizeof ( OSVERSIONINFO);
	result = GetVersionEx ( &osvi);

	if ( !result )
	{
		/* Unable to identify system version. */
		return 606;
	}

	/* The system Type (1=Win3.1, 2=Win95, 3=Win98/ME, 4=Win/ME, 5=Win/NT, 6=Win/2000). */
	if ( osvi.dwPlatformId == VER_PLATFORM_WIN32s )
	{
	        *sys_type = 1;
	}

	if ( osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS )
	{
		*sys_type = 2;
	}

	if ( osvi.dwPlatformId == VER_PLATFORM_WIN32_NT )
	{
	        *sys_type = 5;
	}

	/* Major version number. */
	*version_major = osvi.dwMajorVersion;

	if ( *version_major >= 5 )
	{
		*sys_type = 6;
	}

	/* Minor version number. */
	*version_minor = osvi.dwMinorVersion;

	/* For Win/98, minor version is greater than zero. */
	if ( (*sys_type == 2) && (*version_minor > 0) )
	{
		*sys_type = 3;
	}

	/* For Win/ME, minor version is 90 or greater. */
	if ( (*sys_type == 3) && (*version_minor >= 90) )
	{
		*sys_type = 4;
	}

	/* Service Pack info : For NT/2000, extract the service pack as a number. */
	*service_pack = -1;

	if ( (*sys_type >= 5) && (strcmp ( osvi.szCSDVersion, "Service Pack")) )
	{
		pack[0] = osvi.szCSDVersion[12];
		pack[1] = osvi.szCSDVersion[13];
		pack[2] = osvi.szCSDVersion[14];
		*service_pack = atoi ( pack);
	}

	/* For Win/95, use Build Number to extract OSR info and return in service_pack. */
	if ( *sys_type == 2 )
	{
		*service_pack = 0;

		if ( osvi.dwBuildNumber > 67109814 )
		{
			/* OSR2 (4.00.950B) */
			*service_pack = 1;
		}
	}

	if ( *version_major == 5 )
	{
		if ( *version_minor == 0 )
		{
			*sys_type = 6;
		}

		if ( *version_minor == 1 )
		{
			*sys_type = 7;
		}

		if ( *version_minor == 2 )
		{
			*sys_type = 8;
		}
	}

	return 0;
}


#endif


int gw_os_get_version_str ( gchar **version)
{
	gchar *os_version = NULL;
#if defined ( OS_WIN32)
	int sys_type;
	int version_major;
	int version_minor;
	int service_pack;
#endif


	#if defined ( OS_LINUX)
	os_version = g_strdup ( "GNU/Linux");
	#elif defined ( OS_CYGWIN)
	os_version = g_strdup ( "Cygwin");
	#elif defined ( OS_FREEBSD)
	os_version = g_strdup ( "FreeBSD");
	#elif defined ( OS_OPENBSD)
	os_version = g_strdup ( "OpenBSD");
	#elif defined ( OS_NETBSD)
	os_version = g_strdup ( "NetBSD");
	#elif defined ( OS_WIN32)
	if ( gw_win32_get_version ( &sys_type, &version_major, &version_minor, &service_pack) == 0 )
	{
		switch ( sys_type )
		{
			case 0 : break;
			case 1 :	os_version = g_strdup ( "MS Windows 3.x");
					break;

			case 2 :	if ( service_pack == 0 )
					{
						os_version = g_strdup ( "MS Windows 95 OSR1");
					}
					else
					{
						os_version = g_strdup ( "MS Windows 95 OSR2");
					}
					break;

			case 3 :	os_version = g_strdup ( "MS Windows 98");
					break;

			case 4 :	os_version = g_strdup ( "MS Windows ME");
					break;

			case 5 :	if ( version_minor == 0 )
					{
						os_version = g_strdup_printf ( "MS Windows NT v4.00 SP%d", service_pack);
					}
					else if ( version_minor == 51)
					{
						os_version = g_strdup_printf ( "MS Windows NT v3.51 SP%d", service_pack);
					}
					else
					{
						os_version = g_strdup_printf ( "MS Windows NT SP%d", service_pack);
					}

					break;

			case 6 :	os_version = g_strdup_printf ( "MS Windows 2000 SP%d", service_pack);
					break;

			case 7 :	os_version = g_strdup ( "MS Windows XP");
					break;

			case 8 :	os_version = g_strdup ( "MS Windows server 2003 family");
					break;

			default :	break;
		}
	}
	else
	{
		os_version = g_strdup ( "MS Windows");
	}
	#elif defined ( OS_UNKNOWN)
	os_version = g_strdup ( _("unknown"));
	#endif

	*version = os_version;

	return 0;
}


#if defined ( OS_WIN32)
char * gw_package_get_dir ( char *subdir) {
	char *dir = NULL;
	HKEY hkey = 0;
	char install_dir[2048];
	unsigned long dwLen = sizeof ( install_dir);


	memset(install_dir,'\0',2048);
	if ( RegOpenKey ( HKEY_LOCAL_MACHINE, "SOFTWARE\\GWhere", &hkey) == ERROR_SUCCESS ) {
		if ( RegQueryValueEx ( hkey, "Install_Dir", NULL, NULL, (LPBYTE)&install_dir, &dwLen) == ERROR_SUCCESS ) {
			if ( install_dir!=NULL && strlen ( install_dir)>0 ) {
				dir = g_strconcat ( install_dir, G_DIR_SEPARATOR_S, subdir, NULL);
			}
		}

		RegCloseKey (hkey);
	}

	if ( RegOpenKey ( HKEY_CURRENT_USER, "SOFTWARE\\GWhere", &hkey) == ERROR_SUCCESS ) {
		if ( RegQueryValueEx ( hkey, "Install_Dir", NULL, NULL, (LPBYTE)&install_dir, &dwLen) == ERROR_SUCCESS ) {
			if ( install_dir!=NULL && strlen ( install_dir)>0 ) {
				dir = g_strconcat ( install_dir, G_DIR_SEPARATOR_S, subdir, NULL);
			}
		}

		RegCloseKey (hkey);
	}

	if ( dir == NULL ) {
		dir = g_strdup ( subdir);
	}

	return dir;
}
#endif


char * gw_package_get_locale_dir ( void) {
	char *locale_dir = NULL;


#if defined ( OS_WIN32)
	locale_dir = gw_package_get_dir ( PACKAGE_LOCALE_DIR);
#else
	locale_dir = g_strdup ( PACKAGE_LOCALE_DIR);
#endif

	if ( locale_dir == NULL) {
		locale_dir = g_strdup ( PACKAGE_LOCALE_DIR);
	}

	return locale_dir;
}


char * gw_package_get_plugins_description_dir ( void) {
	char *plugins_dir = NULL;


#if defined ( OS_WIN32)
	plugins_dir = gw_package_get_dir ( PACKAGE_PLUGINS_DESCRIPTION_DIR);
#else
	plugins_dir = g_strdup ( PACKAGE_PLUGINS_DESCRIPTION_DIR);
#endif

	return plugins_dir;
}


char * gw_package_get_plugins_catalog_dir ( void) {
	char *plugins_dir = NULL;


#if defined ( OS_WIN32)
	plugins_dir = gw_package_get_dir ( PACKAGE_PLUGINS_CATALOG_DIR);
#else
	plugins_dir = g_strdup ( PACKAGE_PLUGINS_CATALOG_DIR);
#endif

	return plugins_dir;
}


char * gw_package_get_plugins_dir ( void) {
	char *plugins_dir = NULL;


#if defined ( OS_WIN32)
	plugins_dir = gw_package_get_dir ( PACKAGE_PLUGINS_DIR);
#else
	plugins_dir = g_strdup ( PACKAGE_PLUGINS_DIR);
#endif

	return plugins_dir;
}

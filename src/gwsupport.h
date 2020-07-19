/*  GWhere
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


/*!
 * @header	gwsupport.h
 * 		GWhere<br>
 * 		Copyright (C) 2000  Sébastien LECACHEUR<br><br>
 * 		This Distributed under the terms of the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public Licence</a><br><br>
 * 		This component was developed for the GWhere project.<br><br>
 * @abstract	This is a configure component.
 * @author	Sébastien LECACHEUR <zero@gwhere.org>
 * @version	1.0 2001/08/21
 * @see		gwsupport.h
 * @link	GWhere Web Site <http://www.gwhere.org>
 * @link	GTK+ Web Site <http://www.gtk.org>
 * @ref		gwsupport.c
 * @author	Author <zero@gwhere.org>
 */


#include <gtk/gtk.h>

#ifndef GW_SUPPORT_H
#define GW_SUPPORT_H


#ifdef HAVE_CONFIG_H
	#if defined ( OS_WIN32)
		#include "../win32/config.h"
	#else
		#include <config.h>
	#endif
#endif


#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
	#include <windows.h>
#endif


#if defined ( HAVE_GTK20)
	/*! @define	GTK_WINDOW_DIALOG	Define it for GTK 2.0 compilation */
	#define GTK_WINDOW_DIALOG GTK_WINDOW_TOPLEVEL
#endif


#define str_equals(a,b) ((a==NULL&&b==NULL)||(a!=NULL&&b!=NULL&&strcmp(a,b)==0))


#if defined ( HAVE_GTK12)
	/*! @define	g_strdup_to_gtk_text	With GTK 1.2 just duplicate string */
	#define g_strdup_to_gtk_text(str,text) if(str!=NULL){text=g_strdup(str);}else{text=g_strdup("");}
#elif defined ( HAVE_GTK20)
	/*! @define	g_strdup_to_gtk_text	With GTK 2.0 encode string to UTF-8 */
	#define g_strdup_to_gtk_text(str,text) if(str!=NULL){text=g_locale_to_utf8(str,-1,NULL,NULL,NULL);}else{text=g_strdup("");}
#endif

#if defined ( HAVE_GTK12)
	/*! @define	g_strlen_gtk_text	With GTK 1.2 just duplicate call strlen */
	#define g_strlen_gtk_text(str) strlen(str)
#elif defined ( HAVE_GTK20)
	/*! @define	g_strlen_gtk_text	With GTK 2.0 give the UTF-8 string length */
	#define g_strlen_gtk_text(str) g_utf8_strlen(str,-1)
#endif

#if defined ( HAVE_GTK12)
	/*! @define	g_strdup_from_gtk_text	With GTK 1.2 just duplicate string */
	#define g_strdup_from_gtk_text(str,text) if(str!=NULL){text=g_strdup(str);}else{text=g_strdup("");}
#elif defined ( HAVE_GTK20)
	/*! @define	g_strdup_from_gtk_text	With GTK 2.0 decode string from UTF-8 */
	#define g_strdup_from_gtk_text(str,text) if(str!=NULL){text=g_locale_from_utf8(str,-1,NULL,NULL,NULL);}else{text=g_strdup("");}
#endif

#if defined ( OS_LINUX) || defined ( OS_FREEBSD) || defined ( OS_OPENBSD) || defined ( OS_NETBSD) || defined ( OS_MACOS) || defined ( OS_MACOSX) || defined ( OS_DARWIN)
	/*! @define	HAVE_MOUNT_SYSTEM	Define system with mount system */
	#define HAVE_MOUNT_SYSTEM
#endif


/* Defines extra long number format */
#ifndef G_HAVE_GINT64
	typdef guint64 guint32;
	#define G_MAXUINT64 G_MAXULONG
	#define G_GUINT64_FORMAT "u"
	#define strtoui64(x,y,z) strtoul(x,y,z)
#elif defined ( HAVE_GTK12)
	#define G_GUINT64_FORMAT "llu"
	#define strtoui64(x,y,z) strtoull(x,y,z)
#else
	#define strtoui64(x,y,z) strtoull(x,y,z)
#endif


/* Defines plugin file extension*/
#if defined ( HAVE_GTK12)
	#if defined ( OS_WIN32)
		#define G_MODULE_SUFFIX "dll"
	#else
		#define G_MODULE_SUFFIX "so"
	#endif
#endif


/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
/*
#  define _(String) gettext ( String)
*/
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif



/*
 * Public Functions.
 */

/*
 * This function returns a widget in a component created by Glade.
 * Call it with the toplevel widget in the component (i.e. a window/dialog),
 * or alternatively any widget in the component, and the name of the widget
 * you want returned.
 */
GtkWidget * lookup_widget ( GtkWidget *widget, const gchar *widget_name);


/* get_widget() is deprecated. Use lookup_widget instead. */
#define get_widget lookup_widget


/* Use this function to set the directory containing installed pixmaps. */
void add_pixmap_directory ( const gchar *directory);


/*
 * Private Functions.
 */

/* This is used to create the pixmaps in the interface. */
GtkWidget * create_pixmap ( GtkWidget *widget, const gchar *filename);


/* This is used in of Win9x where they aren't home folder. */
#if defined ( OS_WIN32)
	#define GW_HOME_DIR "C:\\Windows\\LocalSettings"
#else
	#define GW_HOME_DIR "/home"
#endif


#if defined ( OS_WIN32) || defined ( OS_CYGWIN)
/*!
 * @function	gw_win32_get_version
 * @abstract	Gets the system version number and service pack number.
 * @discussion	This function gets the system version number and service pack number.<br>
 *		This works for Win 3.x(Win32s) and Win/95/98/ME and also Win/NT/2000.<br>
 * 		sys_type has the following values :<br>
 * 		<ul>
 * 			<li>0 = Unknown</li>
 * 			<li>1 = Win 3.x</li>
 * 			<li>2 = Win 95</li>
 * 			<li>3 = Win 98</li>
 * 			<li>4 = Win ME</li>
 *			<li>5 = Win NT</li>
 *			<li>6 = Win 2000</li>
 * 			<li>7 = Win XP</li>
 *			<li>8 = Win Server 2003 familly</li>
 * 		</ul>
 * 		version_major is (e.g.) 4 for Win/NT, 5 for Win/2000.<br>
 * 		version_minor is (e.g.) 51 for NT v3.51, 0 for NT v 4.00.<br>
 *		service_pack (service pack #) is meaningful for NT or 2000
 * 		(and also for Win/95, where it is returned as 0 or 1 to
 * 		indicate Win/95 or Win/95B(OSR2) respectively).<br>
 * @param	sys_type	type of system
 * @param	version_major	major version of system
 * @param	version_minor	minor version of system
 * @param	service_pack	service pack number of system
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.
 *		Returns <i>606</i> when it's unable to identify system type.<br>
 *		Returns <i>648</i> when it's unable to load library.<br>
 *		Returns <i>649</i> when disk name may be invalid or Disk not accessible.<br>
 */
int gw_win32_get_version ( int *sys_type, int *version_major, int *version_minor, int *service_pack);


#endif


/*!
 * @function	gw_os_get_version_str
 * @abstract	Gets the operating system version.
 * @discussion	This function gets the formatted operating system version.<br>
 * @param	version		string to store system version must be freed
 *				with g_free().
 * @result	an error code.<br>
 *		Returns <i>0</i> when it's done.
 *		Returns <i>-1</i> when an error occured.
 */
int gw_os_get_version_str ( gchar **version);


char * gw_package_get_locale_dir ( void);


char * gw_package_get_plugins_dir ( void);
char * gw_package_get_plugins_description_dir ( void);
char * gw_package_get_plugins_catalog_dir ( void);


#endif

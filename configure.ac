dnl Process this file with autoconf to produce a configure script.

AC_INIT([gwhere],[0.2.3],[https://github.com/wdlkmpx/gwhere])
AM_INIT_AUTOMAKE([1.11 -Wall foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
m4_ifdef([AM_MAINTAINER_MODE], [AM_MAINTAINER_MODE])

AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_GNU_GETTEXT([external])
AM_PROG_AR
LT_INIT

# Init intltool
IT_PROG_INTLTOOL

dnl ================================================
AC_DEFINE([PROJECT_NAME], "GWhere", [Project name])
AC_SUBST(PACKAGE)
AC_SUBST(VERSION)
AC_SUBST(PROJECT_NAME)

AC_SEARCH_LIBS([strerror],[cposix])
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_STDC

CFLAGS="$CFLAGS -fno-strict-aliasing"

dnl Checks GTK+ version
dnl ===================

gtk_modules="gtk+-2.0 >= 2.14.0
gmodule-2.0 >= 2.14.0"
PKG_CHECK_MODULES(GTK, [$gtk_modules])

dnl Checks for libraries.
dnl =====================
AC_CHECK_LIB([z], [zlibVersion], , AC_MSG_ERROR(Cannot find zlib))

dnl Checks functions
dnl ==============
AC_FUNC_FNMATCH
AC_CHECK_FUNCS(dup2 getmntent getwd hasmntopt memset regcomp strerror mempcpy getfsent strftime strptime)


dnl Checks headers
dnl =============
AC_CHECK_HEADERS(fcntl.h libintl.h mntent.h sys/ioctl.h sys/mount.h sys/vfs.h stddef.h string.h unistd.h)
AC_HEADER_DIRENT
AC_HEADER_SYS_WAIT
AC_HEADER_STDC


dnl Checks for typedefs, structures, and compiler characteristics
dnl =============================================================
AC_C_CONST
AC_STRUCT_TM
AC_TYPE_UID_T


dnl Set PACKAGE_LOCALE_DIR in config.h
dnl ==================================
localedir=
if test "x${prefix}" = "xNONE"; then
  localedir="${ac_default_prefix}/${DATADIRNAME}/locale"
else
  localedir="${prefix}/${DATADIRNAME}/locale"
fi
AC_DEFINE_UNQUOTED([PACKAGE_LOCALE_DIR], "$localedir", [Package locale directory])


dnl Set PACKAGE_DATA_DIR in config.h
dnl ================================
DATADIR=
if test "x${datadir}" = 'x${prefix}/share'; then
  if test "x${prefix}" = "xNONE"; then
    DATADIR="${ac_default_prefix}/share/${PACKAGE}"
  else
    DATADIR="${prefix}/share/${PACKAGE}"
  fi
else
  DATADIR="${datadir}/${PACKAGE}"
fi
AC_DEFINE_UNQUOTED([PACKAGE_DATA_DIR], "$DATADIR", [Package data dir])


dnl Set PACKAGE_PLUGINS_DIR in config.h
dnl ================================
plugins_dir=
if test "x${prefix}" = "xNONE"; then
  plugins_dir="${ac_default_prefix}/lib/${PACKAGE}/plugins"
else
  plugins_dir="${prefix}/lib/${PACKAGE}/plugins"
fi
AC_DEFINE_UNQUOTED([PACKAGE_PLUGINS_DIR], "$plugins_dir", [Plugins directory])


dnl Set PACKAGE_PLUGINS_CATALOG_DIR in config.h
dnl ================================
catalog_dir=
if test "x${prefix}" = "xNONE"; then
  catalog_dir="${ac_default_prefix}/lib/${PACKAGE}/plugins/catalog"
else
  catalog_dir="${prefix}/lib/${PACKAGE}/plugins/catalog"
fi
AC_DEFINE_UNQUOTED([PACKAGE_PLUGINS_CATALOG_DIR], "$catalog_dir", [Package plugins catalog dir])


dnl Set PACKAGE_PLUGINS_DESCRIPTION_DIR in config.h
dnl ================================
plugin_desc_dir=
if test "x${prefix}" = "xNONE"; then
  plugin_desc_dir="${ac_default_prefix}/lib/${PACKAGE}/plugins/descr"
else
  plugin_desc_dir="${prefix}/lib/${PACKAGE}/plugins/descr"
fi
AC_DEFINE_UNQUOTED([PACKAGE_PLUGINS_DESCRIPTION_DIR], "$plugin_desc_dir", [Package plugins description dir])


dnl Set PACKAGE_SOURCE_DIR in config.h
dnl ==================================
packagesrcdir=`cd $srcdir && pwd`
AC_DEFINE_UNQUOTED([PACKAGE_SOURCE_DIR], "$packagesrcdir", [Package source dir])


dnl Use --enable-debug for debug mode
dnl =================================
AC_ARG_ENABLE(debug,
	[  --enable-debug          use GWhere in debugging mode. [default=no]],
	GW_DEBUG_MODE=yes,
	GW_DEBUG_MODE=no)
if test "x$GW_DEBUG_MODE" = "xyes" ; then
	AC_DEFINE([GW_DEBUG_MODE], [1], [GW DEBUG MODE])
	echo checking for debug mode... yes
else
	echo checking for debug mode... no
fi


dnl Use --enable-debug-time for debug time
dnl ======================================
AC_ARG_ENABLE(debug-time,
	[  --enable-debug-time          use GWhere in debugging time. [default=no]],
	GW_DEBUG_TIME=yes,
	GW_DEBUG_TIME=no)
if test "x$GW_DEBUG_TIME" = "xyes" ; then
	if test "x$GW_DEBUG_MODE" = "xyes" ; then
		AC_DEFINE([GW_DEBUG_TIME], [1], [GW DEBUG MODE])
		echo checking for debug time... yes
	else
		echo checking for debug time... no
	fi
fi


dnl Use --enable-debug-data-component for debug data component
dnl ==========================================================
AC_ARG_ENABLE(debug-data-component,
	[  --enable-debug-data-component          use GWhere in debugging data component. [default=no]],
	GW_DEBUG_DATA_COMPONENT=yes,
	GW_DEBUG_DATA_COMPONENT=no)
if test "x$GW_DEBUG_DATA_COMPONENT" = "xyes" ; then
	if test "x$GW_DEBUG_MODE" = "xyes" ; then
		AC_DEFINE([GW_DEBUG_DATA_COMPONENT], [1], [GW DEBUG DATA COMPONENT])
		echo checking for debug data component... yes
	else
		echo checking for debug data component... no
	fi
fi


dnl Use --enable-debug-tools-component for debug data component
dnl ==========================================================
AC_ARG_ENABLE(debug-tools-component,
	[  --enable-debug-tools-component          use GWhere in debugging tools component. [default=no]],
	GW_DEBUG_TOOLS_COMPONENT=yes,
	GW_DEBUG_TOOLS_COMPONENT=no)
if test "x$GW_DEBUG_TOOLS_COMPONENT" = "xyes" ; then
	if test "x$GW_DEBUG_MODE" = "xyes" ; then
		AC_DEFINE([GW_DEBUG_TOOLS_COMPONENT], [1], [GW DEBUG TOOLS COMPONENT])
		echo checking for debug tools component... yes
	else
		echo checking for debug tools component... no
	fi
fi


dnl Use --enable-debug-gui-component for debug GUI component
dnl ========================================================
AC_ARG_ENABLE(debug-gui-component,
	[  --enable-debug-gui-component          use GWhere in debugging GUI component. [default=no]],
	GW_DEBUG_GUI_COMPONENT=yes,
	GW_DEBUG_GUI_COMPONENT=no)
if test "x$GW_DEBUG_GUI_COMPONENT" = "xyes" ; then
	if test "x$GW_DEBUG_MODE" = "xyes" ; then
		AC_DEFINE([GW_DEBUG_GUI_COMPONENT], [1], [GW DEBUG GUI COMPONENT])
		echo checking for debug gui component... yes
	else
		echo checking for debug gui component... no
	fi
fi


dnl Use --enable-debug-gui-callback-component for debug GUI callback component
dnl ==========================================================================
AC_ARG_ENABLE(debug-gui-callback-component,
	[  --enable-debug-gui-callback-component          use GWhere in debugging GUI callback component. [default=no]],
	GW_DEBUG_GUI_CALLBACK_COMPONENT=yes,
	GW_DEBUG_GUI_CALLBACK_COMPONENT=no)
if test "x$GW_DEBUG_GUI_CALLBACK_COMPONENT" = "xyes" ; then
	if test "x$GW_DEBUG_MODE" = "xyes" ; then
		AC_DEFINE([GW_DEBUG_GUI_CALLBACK_COMPONENT], [1], [GW DEBUG GUI CALLBACK COMPONENT])
		echo checking for debug gui callback component... yes
	else
		echo checking for debug gui callback component... no
	fi
fi


dnl Use --enable-debug-all for debug mode
dnl =================================
AC_ARG_ENABLE(debug-all,
	[  --enable-debug-all          use GWhere in debugging mode with debug. [default=no]],
	GW_DEBUG_ALL=yes,
	GW_DEBUG_ALL=no)
if test "x$GW_DEBUG_ALL" = "xyes" ; then
	echo checking for debug all... yes
	AC_DEFINE([GW_DEBUG_MODE], [1], [GW DEBUG MODE])
	AC_DEFINE([GW_DEBUG_TIME], [1], [GW DEBUG TIME])
	AC_DEFINE([GW_DEBUG_DATA_COMPONENT], [1], [GW DEBUG DATA COMPONENT])
	AC_DEFINE([GW_DEBUG_TOOLS_COMPONENT], [1], [GW DEBUG TOOLS COMPONENT])
	AC_DEFINE([GW_DEBUG_GUI_COMPONENT], [1], [GW GUI COMPONENT])
	AC_DEFINE([GW_DEBUG_GUI_CALLBACK_COMPONENT], [1], [GW DEBUG GUI CALLBACK COMPONENT])
	GW_DEBUG_MODE=yes
	GW_DEBUG_TIME=yes
	GW_DEBUG_DATA_COMPONENT=yes
	GW_DEBUG_TOOLS_COMPONENT=yes
	GW_DEBUG_GUI_COMPONENT=yes
	GW_DEBUG_GUI_CALLBACK_COMPONENT=yes
else
	echo checking for debug all... no
fi


dnl Set GW_PROG_PATH_MOUNT (mount program path) in config.h
dnl =======================================================
AC_PATH_PROG([GW_PROG_PATH_MOUNT], [mount])
AC_SUBST(GW_PROG_PATH_MOUNT)
if test "x$GW_PROG_PATH_MOUNT" != "x" ; then
  AC_DEFINE_UNQUOTED([GW_PROG_PATH_MOUNT], "$GW_PROG_PATH_MOUNT", [mount path])
fi


dnl Set GW_PROG_PATH_UMOUNT (umount program path) in config.h
dnl =======================================================
AC_PATH_PROG([GW_PROG_PATH_UMOUNT], [umount])
AC_SUBST(GW_PROG_PATH_UMOUNT)
if test "x$GW_PROG_PATH_UMOUNT" != "x" ; then
  AC_DEFINE_UNQUOTED([GW_PROG_PATH_UMOUNT], "$GW_PROG_PATH_UMOUNT", [umount path])
fi


GETTEXT_PACKAGE=gwhere
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package.])
AM_GLIB_GNU_GETTEXT

AC_CONFIG_FILES([
Makefile
src/db/Makefile
src/data/Makefile
src/tools/Makefile
src/gui/Makefile
src/res/Makefile
src/plugins/Makefile
src/plugins/descr/Makefile
src/plugins/catalog/Makefile
src/plugins/catalog/gwcatalog/Makefile
src/plugins/catalog/csv/Makefile
src/Makefile
doc/Doxyfile
doc/Makefile
doc/license/Makefile
doc/man/Makefile
po/Makefile.in
win32/Makefile
win32/config.h
win32/gwhere.nsi
])
AC_OUTPUT


echo ""
echo ""
echo "***************************************************"
echo "*          Configuring GWhere-$VERSION              *"
echo "***************************************************"
echo "*"
echo "*   GTK+ : $GTK_VERSION"
echo "*"
echo "*   Options :"

if test "x$GW_DEBUG_MODE" = "xyes" ; then
   echo "*        - Debug mode enabled"
fi

if test "x$GW_DEBUG_TIME" = "xyes" ; then
   echo "*        - Debug time enabled"
fi

if test "x$GW_DEBUG_DATA_COMPONENT" = "xyes" ; then
   echo "*        - Debug data components enabled"
fi

if test "x$GW_DEBUG_TOOLS_COMPONENT" = "xyes" ; then
   echo "*        - Debug tools components enabled"
fi

if test "x$GW_DEBUG_GUI_COMPONENT" = "xyes" ; then
   echo "*        - Debug GUI components enabled"
fi

if test "x$GW_DEBUG_GUI_CALLBACK_COMPONENT" = "xyes" ; then
   echo "*        - Debug GUI callback components enabled"
fi

echo "*"
echo "***************************************************"
echo ""
echo configure complete, type \'make\' to compile GWhere
echo ""

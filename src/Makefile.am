## Process this file with automake to produce Makefile.in

SUBDIRS = tools db data res gui plugins

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src/res \
	-I$(top_srcdir)/src/tools \
	-I$(top_srcdir)/src/db \
	-I$(top_srcdir)/src/data \
	-I$(top_srcdir)/src/gui \
	@GTK_CFLAGS@ \
	-D${HOST_OS}

bin_PROGRAMS = gwhere

gwhere_SOURCES = \
	main.c main.h \
	gwsupport.c gwsupport.h \
	gwcatalogmanager.c gwcatalogmanager.h \
	gwhelper.c gwhelper.h \
	gwsearchengine.c gwsearchengine.h \
	gwsupermount.c gwsupermount.h \
	gwapplicationmanager.c gwapplicationmanager.h \
	gwguimanager.c gwguimanager.h \
	gwpluginsmanager.c gwpluginsmanager.h \
	gwdevicemanager.c gwdevicemanager.h

gwhere_LDADD = \
	@top_srcdir@/src/res/libgwres.a \
	@top_srcdir@/src/tools/libgwtools.a \
	@top_srcdir@/src/plugins/libgwplugins.a \
	@top_srcdir@/src/db/libgwdb.a \
	@top_srcdir@/src/data/libgwdata.a \
	@top_srcdir@/src/gui/libgwgui.a \
	@GTK_LIBS@ \
	$(INTLLIBS)

gwhere_LDFLAGS = \

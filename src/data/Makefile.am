## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	$(GTK_CFLAGS)

noinst_LIBRARIES = libgwdata.a

libgwdata_a_SOURCES = \
	gwdata.h \
	gwsearchiteminfo.c gwsearchinfo.h \
	gwscandiskinfo.c gwscandiskinfo.h \
	gwenginequicksearch.c gwenginequicksearch.h \
	gwuserquicksearch.c gwuserquicksearch.h \
	gwsettings.c gwsettings.h \
	gwstringbuffer.c gwstringbuffer.h \
	gwvirtualfilesystemstats.c gwvirtualfilesystemstats.h

EXTRA_DIST = $(SOURCES)

libgwdata_a_LIBADD = \
	$(top_srcdir)/src/tools/libgwtools.a

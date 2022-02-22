## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	$(GTK_CFLAGS)

noinst_LIBRARIES = libgwtools.a

libgwtools_a_SOURCES = \
	gwtools.h \
	gwstring.c gwstring.h \
	gwencode.c gwencode.h \
	gwfile.c gwfile.h \
	gwpropertiesfile.c gwpropertiesfile.h \
	gwfilesystem.c gwfilesystem.h

EXTRA_DIST = $(SOURCES)

## Process this file with automake to produce Makefile.in

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@ \
	-D${HOST_OS}

noinst_LIBRARIES = libgwtools.a

libgwtools_a_SOURCES = \
	gwtools.h \
	gwstring.c gwstring.h \
	gwencode.c gwencode.h \
	gwfile.c gwfile.h \
	gwpropertiesfile.c gwpropertiesfile.h \
	gwfilesystem.c gwfilesystem.h \
	gwmail.c gwmail.h

EXTRA_DIST = $(SOURCES)

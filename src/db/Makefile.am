## Process this file with automake to produce Makefile.in

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@ \
	-D${HOST_OS}

noinst_LIBRARIES = libgwdb.a

libgwdb_a_SOURCES = \
	gwdb.h \
	gwdbcontext.c gwdbcontext.h \
	gwdbcatalog.c gwdbcatalog.h \
	gwdbcategory.c gwdbcategory.h \
	gwdbdisk.c gwdbdisk.h \
	gwdbdisktype.h \
	gwdbfile.c gwdbfile.h

EXTRA_DIST = $(SOURCES)

libgwdb_a_LIBADD = 

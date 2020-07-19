## Process this file with automake to produce Makefile.in

INCLUDES = \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src \
	@GTK_CFLAGS@ \
	-D${HOST_OS}

noinst_LIBRARIES = libgwgui.a

libgwgui_a_SOURCES = \
	gwgui.h gwreferences.h \
	gtktextarea.c gtktextarea.h \
	gwwindowboxabout.c gwwindowboxabout.h \
	gwcapturebox.c gwcapturebox.h \
	gwwindowboxmail.c gwwindowboxmail.h \
	gwwindowboxmailcallback.c gwwindowboxmailcallback.h \
	gwsettingsinterface.c gwsettingsinterface.h \
	gwsettingswindowbox.c gwsettingswindowbox.h \
	gwsettingswindowboxcallback.c gwsettingswindowboxcallback.h \
	gwsettingsgeneral.c gwsettingsgeneral.h \
	gwsettingscatalogfile.c gwsettingscatalogfile.h \
	gwsettingsgui.c gwsettingsgui.h \
	gwsettingsexplorer.c gwsettingsexplorer.h \
	gwsettingsexplorerdisk.c gwsettingsexplorerdisk.h \
	gwsettingsexplorerfile.c gwsettingsexplorerfile.h \
	gwsettingssearch.c gwsettingssearch.h \
	gwsettingsquicksearch.c gwsettingsquicksearch.h \
	gwsettingsmail.c gwsettingsmail.h \
	gwfileselectionbox.c gwfileselectionbox.h \
	gwcategorieseditbox.c gwcategorieseditbox.h \
	gwcomboboxcategories.c gwcomboboxcategories.h \
	gwdialogbox.c gwdialogbox.h \
	gwmenu.c gwmenu.h \
	gwmenufile.c gwmenufile.h \
	gwmenufilecallback.c gwmenufilecallback.h \
	gwmenuaction.c gwmenuaction.h \
	gwmenuactioncallback.c gwmenuactioncallback.h \
	gwmenuoptions.c gwmenuoptions.h \
	gwmenuoptionscallback.c gwmenuoptionscallback.h \
	gwmenuhelp.c gwmenuhelp.h \
	gwmenuhelpcallback.c gwmenuhelpcallback.h \
	gwmenupopup.c gwmenupopup.h \
	gwmenupopupcallback.c gwmenupopupcallback.h \
	gwtoolbar.c toolbar.h \
	gwnotebook.c gwnotebook.h \
	gwnotebookcallback.c gwnotebookcallback.h \
	gwnotebookcatalog.c gwnotebookcatalog.h \
	gwnotebookcatalogcallback.c gwnotebookcatalogcallback.h \
	gwnotebooksearch.c gwnotebooksearch.h \
	gwnotebooksearchcallback.c gwnotebooksearchcallback.h \
	gwnotebookmanagment.c gwnotebookmanagment.h \
	gwnotebookmanagmentcallback.c gwnotebookmanagmentcallback.h \
	gwmsgbox.c gwmsgbox.h \
	gwprogressbarbox.c gwprogressbarbox.h \
	gwpropertiesbox.c gwpropertiesbox.h \
	gwpropertiesboxcallback.c gwpropertiesboxcallback.h \
	gwstatusbar.c gwstatusbar.h \
	gwstatusbarcallback.c gwstatusbarcallback.h \
	gwtextbox.c gwtextbox.h

EXTRA_DIST = $(SOURCES)

libgwgui_a_LIBADD = \
	@top_srcdir@/src/db/libgwdb.a \
	@top_srcdir@/src/data/libgwdata.a \
	@top_srcdir@/src/res/libgwres.a \
	@top_srcdir@/src/tools/libgwtools.a

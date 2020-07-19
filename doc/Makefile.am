SUBDIRS = license man

DOXYGEN = doxygen

noinst_DATA = Doxyfile.in

doxygen-html: Doxyfile
	$(DOXYGEN) $<

EXTRA_DIST = README.Linux \
		README.Cygwin \
		README.Win32 \
		README.FreeBSD \
		README.NetBSD \
		README.OpenBSD \
		$(noinst_DATA)

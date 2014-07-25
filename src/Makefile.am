AM_CFLAGS = -W -g -Wall -Wno-unused-parameter

include_HEADERS = popen-noshell.h
lib_LTLIBRARIES = libpopennoshell.la

libpopennoshell_la_LDFLAGS = -shared
libpopennoshell_la_CFLAGS = $(AM_CFLAGS)
libpopennoshell_la_SOURCES = popen-noshell.c

pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = libpopennoshell.pc

libpopennoshell.pc: libpopennoshell.pc.in
	sed -e 's![@]prefix[@]!$(prefix)!g' \
		-e 's![@]exec_prefix[@]!$(exec_prefix)!g' \
		-e 's![@]includedir[@]!$(includedir)!g' \
		-e 's![@]libdir[@]!$(libdir)!g' \
		-e 's![@]PACKAGE_VERSION[@]!$(PACKAGE_VERSION)!g' \
		libpopennoshell.pc.in > $@

noinst_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = libpopennoshell.la

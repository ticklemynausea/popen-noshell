AM_CFLAGS = -W -g -Wall -Wno-unused-parameter

include_HEADERS = popen-noshell.h
lib_LTLIBRARIES = libpopennoshell.la

libpopennoshell_la_LDFLAGS = -shared
libpopennoshell_la_CFLAGS = $(AM_CFLAGS)
libpopennoshell_la_SOURCES = popen-noshell.c

noinst_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = libpopennoshell.la

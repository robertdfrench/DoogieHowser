## Process this file with automake to produce Makefile.in

TESTS = check_force
check_PROGRAMS = check_force.exe
check_force_exe_SOURCES = check_force.c $(top_builddir)/src/force.h
check_force_exe_CFLAGS = @CHECK_CFLAGS@
check_force_exe_LDADD = $(top_builddir)/src/libforce.la @CHECK_LIBS@

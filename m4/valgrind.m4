# valgrind.m4 serial 1
dnl Copyright (C) 2008 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl From Simon Josefsson

# sj_VALGRIND()
# -------------
# Check if valgrind is available, and set VALGRIND to it if available.
AC_DEFUN([sj_VALGRIND],
[
  # Run self-tests under valgrind?
  if test "$cross_compiling" = no; then
    AC_CHECK_PROGS(VALGRIND, valgrind)
  fi
  if test -n "$VALGRIND" && $VALGRIND true > /dev/null 2>&1; then
    opt_valgrind_tests=yes
  else
    opt_valgrind_tests=no
    VALGRIND=
  fi 
  AC_MSG_CHECKING([whether self tests are run under valgrind])
  AC_ARG_ENABLE(valgrind-tests,
  	AS_HELP_STRING([--enable-valgrind-tests],
                         [run self tests under valgrind]),
    opt_valgrind_tests=$enableval)
  AC_MSG_RESULT($opt_valgrind_tests)
])

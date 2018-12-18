AC_INIT([brainfuck], [1.0.0], [haximilian@gmail.com])
LT_INIT
AC_PREREQ([2.6.8])

AC_CONFIG_SRCDIR([src/brainfuck.c])
AC_CONFIG_SRCDIR([src/loop.c])
AC_CONFIG_SRCDIR([src/node.c])
AC_CONFIG_SRCDIR([src/reader.c])
AC_CONFIG_SRCDIR([include/loop.h])
AC_CONFIG_SRCDIR([include/node.h])
AC_CONFIG_SRCDIR([include/reader.h])
AC_CONFIG_SRCDIR([lib/cbug/Debug.h])

AC_ARG_ENABLE(debug, AS_HELP_STRING([--enable-debug], [enable debugging, default: no]),
  [case "${enableval}" in
    yes) debug=true ;;
    no)  debug=false ;;
    *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
  esac],
  [debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")

AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([1.11 -Wall -Werror])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_PROG_CC
AC_OUTPUT

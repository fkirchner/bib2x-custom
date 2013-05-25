dnl Process this file with autoconf to produce a configure script.
AC_INIT
AC_CONFIG_SRCDIR([include/odb.h])

AC_CANONICAL_TARGET

dnl Every other copy of the package version number gets its value from here
AM_INIT_AUTOMAKE(bib2x, 0.9.0)

AC_SUBST(VERSION)

ISODATE=`date +%Y-%m-%d`
AC_SUBST(ISODATE)

#AC_CANONICAL_TARGET([])

AM_SANITY_CHECK

dnl Checks for programs.
AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL
dnl AC_PROG_LEX
dnl AC_DECL_YYTEXT
dnl AC_PROG_YACC
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_INSTALL

AC_PATH_X
AC_PATH_XTRA

AC_HEADER_STDC
AC_HEADER_TIME
AC_HEADER_SYS_WAIT

AC_C_CONST
AC_PROG_AWK
AC_PROG_LN_S

AC_CHECK_HEADERS([sys/timeb.h arpa/inet.h netdb.h netinet/in.h stdlib.h sys/ioctl.h sys/socket.h sys/time.h unistd.h])


AC_CHECK_FUNCS([gettimeofday])


#AC_CHECK_LIB(stdc++, cout, , AC_MSG_ERROR([WTF?]))
#AC_CHECK_LIB([ssl], [SSL_new])

dnl Checks for header files.
dnl AC_HEADER_STDC
dnl AC_CHECK_HEADERS(unistd.h)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIGNAL
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_CHECK_FUNCS([bzero gethostbyname gettimeofday inet_ntoa select socket])

dnl Only supported with newer autoconf
AC_FUNC_FORK


AC_ARG_ENABLE([debug],[--enable-debug  enable the DEBUG flag], AC_DEFINE(_DEBUG))

AC_HEADER_STDBOOL

AC_CONFIG_FILES([Makefile \
          src/Makefile \
          templates/Makefile \
          include/Makefile]) 
AC_OUTPUT


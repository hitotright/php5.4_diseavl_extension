dnl $Id$
dnl config.m4 for extension diseval

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(diseval, for diseval support,
dnl Make sure that the comment is aligned:
dnl [  --with-diseval             Include diseval support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(diseval, whether to enable diseval support,
dnl Make sure that the comment is aligned:
[  --enable-diseval           Enable diseval support])

if test "$PHP_DISEVAL" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-diseval -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/diseval.h"  # you most likely want to change this
  dnl if test -r $PHP_DISEVAL/$SEARCH_FOR; then # path given as parameter
  dnl   DISEVAL_DIR=$PHP_DISEVAL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for diseval files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DISEVAL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DISEVAL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the diseval distribution])
  dnl fi

  dnl # --with-diseval -> add include path
  dnl PHP_ADD_INCLUDE($DISEVAL_DIR/include)

  dnl # --with-diseval -> check for lib and symbol presence
  dnl LIBNAME=diseval # you may want to change this
  dnl LIBSYMBOL=diseval # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DISEVAL_DIR/lib, DISEVAL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DISEVALLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong diseval lib version or lib not found])
  dnl ],[
  dnl   -L$DISEVAL_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DISEVAL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(diseval, diseval.c, $ext_shared)
fi

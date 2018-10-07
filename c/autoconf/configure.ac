AC_INIT([myconfig], [1.0])
AC_CONFIG_SRCDIR(src/main.c)

AC_MSG_NOTICE([Hello, world.])
echo "Testing for a C compiler"
AC_PROG_CC
AC_LANG(C)
AC_CHECK_HEADERS(sndfile.h)
AC_CHECK_HEADERS(fftw3.h)
AC_CHECK_LIB(sndfile, sf_open) 
AC_CHECK_LIB(fftw3, fftw_malloc) 

AC_OUTPUT(Makefile)

dnl SFLPhone - configure.ac for automake 1.9 and autoconf 2.59
dnl

dnl Process this file with autoconf to produce a configure script.
AC_PREREQ([2.65])
AC_INIT([sflphone],[0.9.14],[sflphoneteam@savoirfairelinux.com],[sflphone])
AC_COPYRIGHT([[Copyright (c) Savoir-Faire Linux 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011]])
AC_REVISION([$Revision$])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Silent build by default. Use make V=1 to increase verbosity
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

dnl Rewrite name of programs to be installed
dnl AC_ARG_PROGRAM

dnl Compute canonical system name
dnl AC_CANONICAL_TARGET

dnl Improve make variable MAKE
AC_PROG_MAKE_SET

dnl Where to find configure files
dnl AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_MACRO_DIR([m4])

dnl What to generate
dnl AC_CONFIG_FILES([stamp-h], [echo timestamp > stamp-h])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([libs/Makefile \
		libs/utilspp/Makefile \
		libs/utilspp/singleton/Makefile \
		libs/iax2/Makefile])

AC_CONFIG_FILES([src/Makefile \
		src/sip/Makefile \
		src/im/Makefile \
		src/iax/Makefile \
		src/audio/Makefile \
		src/audio/audiortp/Makefile \
		src/audio/pulseaudio/Makefile \
		src/audio/alsa/Makefile \
		src/audio/sound/Makefile \
		src/audio/codecs/Makefile \
		src/config/Makefile \
		src/dbus/Makefile \
		src/plug-in/Makefile \
		src/plug-in/test/Makefile \
		src/hooks/Makefile \
		src/history/Makefile])

dnl Unitary test section
AC_CONFIG_FILES([test/Makefile])

AC_CONFIG_FILES([ringtones/Makefile])

AC_CONFIG_FILES([man/Makefile])

AC_CONFIG_FILES([doc/Makefile \
		doc/dbus-api/Makefile \
		doc/doxygen/Makefile])

dnl Check for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

dnl will have to remove this
LT_INIT

dnl Define C++ as default language
AC_LANG(C++)

dnl Check for header files
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h libintl.h limits.h malloc.h \
        memory.h netdb.h netinet/in.h stdlib.h string.h strings.h \
        sys/ioctl.h sys/socket.h sys/time.h unistd.h utime.h ostream])

dnl Check for typedefs, structures, and compiler characteristics
AC_HEADER_STAT
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_C_VOLATILE
AC_CHECK_TYPES([ptrdiff_t])

dnl ********************************
dnl Check for needed functions
dnl ********************************
AC_FUNC_CHOWN
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
	AC_DIAGNOSE([obsolete],[your code may safely assume C89 semantics that RETSIGTYPE is void.
Remove this warning and the `AC_CACHE_CHECK' when you adjust the code.])dnl
AC_CACHE_CHECK([return type of signal handlers],[ac_cv_type_signal],[AC_COMPILE_IFELSE(
[AC_LANG_PROGRAM([#include <sys/types.h>
#include <signal.h>
],
		 [return *(signal (0, 0)) (0) == 1;])],
		   [ac_cv_type_signal=int],
		   [ac_cv_type_signal=void])])
AC_DEFINE_UNQUOTED([RETSIGTYPE],[$ac_cv_type_signal],[Define as the return type of signal handlers
		    (`int' or `void').])

AC_FUNC_STAT
AC_FUNC_UTIME_NULL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([bzero floor gethostbyname gethrtime gettimeofday \
		inet_ntoa memset mkdir pathconf pow regcomp select setlocale socket \
		strchr strdup strerror strrchr strstr strtol utime])

dnl Check for GNU ccRTP
PKG_PROG_PKG_CONFIG

dnl Trying to set PJSIP using pkg-config
dnl PKG_CHECK_MODULES(SIP, libpj-sfl, have_libpj=true, have_libpj=false)
dnl if test "x${have_libpj}" = "xfalse" ; then
dnl    AC_MSG_ERROR([PJSIP not found. http://www.pjsip.org/download.htm])
dnl fi
dnl AC_SUBST(SIP_CFLAGS)

dnl Check for uuid development package - name: uuid-dev
UUID_MIN_VERSION=1.0
PKG_CHECK_MODULES(UUID, uuid >= ${UUID_MIN_VERSION}, HAVE_UUID=true, HAVE_UUID=false);

LIBCRYPTO_MIN_VERSION=1.0
PKG_CHECK_MODULES(LIBCRYPTO, libcrypto >= ${LIBCRYPTO_MIN_VERSION}, HAVE_LIBCRYPTO=true, HAVE_LIBCRYPTO=false);

dnl Check for alsa development package - name: libasound2-dev
ALSA_MIN_VERSION=1.0
PKG_CHECK_MODULES(ALSA, alsa >= ${ALSA_MIN_VERSION},, AC_MSG_ERROR([Missing alsa development package: libasound2-dev or alsa-lib-devel]))

dnl Check for pulseaudio development package - name: libpulse-dev
LIBPULSE_MIN_VERSION=0.9.15
PKG_CHECK_MODULES(PULSEAUDIO, libpulse >= ${LIBPULSE_MIN_VERSION},, AC_MSG_ERROR([Missing pulseaudio development package: libpulse-dev]))

dnl Check for the samplerate development package - name: libsamplerate0-dev
LIBSAMPLERATE_MIN_VERSION=0.1.2
PKG_CHECK_MODULES(SAMPLERATE, samplerate >= ${LIBSAMPLERATE_MIN_VERSION},, AC_MSG_ERROR([Missing libsamplerate development package: libsamplerate0-dev]))

LIBCCGNU2_MIN_VERSION=1.3.1
PKG_CHECK_MODULES(CCGNU2, libccgnu2 >= ${LIBCCGNU2_MIN_VERSION},, AC_MSG_ERROR([Missing common cpp development package: libcommoncpp2-dev]))

LIBCCEXT2_MIN_VERSION=1.3.1
PKG_CHECK_MODULES(CCEXT2, libccext2 >= ${LIBCCEXT2_MIN_VERSION})

LIBCCRT_MIN_VERSION=1.3.0
PKG_CHECK_MODULES(CCRTP, libccrtp1 >= ${LIBCCRT_MIN_VERSION},, AC_MSG_ERROR([Missing ccrtp development package: libccrtp-dev]))

dnl Check for OpenSSL to link against pjsip and provide SIPS TLS support
PKG_CHECK_MODULES([libssl], libssl,, AC_MSG_ERROR([Missing ssl development package: libssl-dev]))

dnl Check for libzrtpcpp, a ccRTP extension providing zrtp key exchange
LIBZRTPCPP_MIN_VERSION=1.3.0
PKG_CHECK_MODULES(ZRTPCPP, libzrtpcpp >= ${LIBZRTPCPP_MIN_VERSION},, AC_MSG_ERROR([Missing zrtp development package: libzrtpcpp-dev]))

dnl DBus-C++ detection
dnl pkg-config doesn't like 0.6.0-pre1 version number, it assumes that it is
dnl more recent than (unreleased) 0.6.0
DBUS_CPP_REQUIRED_VERSION=0.6.0-pre1
PKG_CHECK_MODULES(DBUSCPP, dbus-c++-1,,
	AC_MSG_ERROR([You need the DBus-c++ libraries (version $DBUS_CPP_REQUIRED_VERSION or better)]))

AC_ARG_WITH(debug,
		AS_HELP_STRING(
				[--with-debug],
				[Set to enable debugging information @<:@default=no@:>@]
				),
			[CXXFLAGS="-g -O0"],
			[CXXFLAGS="-O2"]
			)

CXXFLAGS="${CXXFLAGS} -Wno-return-type -Wall -Wextra -Wnon-virtual-dtor"

AC_CHECK_LIB([expat], XML_ParserCreate_MM,
		[AC_CHECK_HEADERS(expat.h, have_expat=true, have_expat=false)],
	have_expat=false)

test "$have_expat" = false && AC_MSG_ERROR([libexpat development files missing])

xml_CFLAGS=
xml_LIBS=-lexpat

AC_SUBST(xml_CFLAGS)
AC_SUBST(xml_LIBS)

AC_CHECK_LIB([yaml], yaml_parser_initialize,
	       [AC_CHECK_HEADERS(yaml.h, have_yaml=true, have_yaml=false)],
	       have_yaml=false)

test "$have_yaml" = "false" && AC_MSG_ERROR([libyaml development files missing])

yaml_CFLAGS=
yaml_LIBS=-lyaml
AC_SUBST(yaml_CFLAGS)
AC_SUBST(yaml_LIBS)

AC_CHECK_LIB([pthread], pthread_create,
		[AC_CHECK_HEADERS(pthread.h, have_pthread=true, have_pthread=false)],
		have_pthread=false)

test "$have_pthread" = "false" && AC_MSG_ERROR([You need the POSIX Thread library (pthreads)])	


AC_CHECK_LIB([pcre], pcre_free,
		[AC_CHECK_HEADERS(pcre.h, have_pcre=true, have_pcre=false)],
		have_pcre=false)

test "$have_pcre" = "false" && AC_MSG_ERROR([You need the Perl-Compatible Regular Expressions library (pcre)])	

PCRE_LIBS=-lpcre
PCRE_CFLAGS=
AC_SUBST(PCRE_LIBS)
AC_SUBST(PCRE_CFLAGS)

dnl Check for libcppunit-dev
CPPUNIT_MIN_VERSION=1.12
PKG_CHECK_MODULES(CPPUNIT, cppunit >= ${CPPUNIT_MIN_VERSION}, AM_CONDITIONAL(BUILD_TEST, test 1 = 1 ), AM_CONDITIONAL(BUILD_TEST, test 0 = 1 ))

# check for libgsm1 (doesn't use pkg-config)
	dnl Check for libgsm
AC_ARG_WITH([gsm],
		[AS_HELP_STRING([--without-gsm],
			[disable support for gsm codec])],
		[],
		[with_gsm=yes])

LIBGSM=
AS_IF([test "x$with_gsm" != xno],
		[AC_CHECK_HEADER([gsm/gsm.h], , AC_MSG_FAILURE([Unable to find the libgsm1 headers (you may need to install the dev package).  You may use --without-gsm to compile without gsm codec support.]))]
		[AC_CHECK_LIB([gsm], [gsm_decode],
			[],
			[AC_MSG_FAILURE(
				[libgsm link test failed.   You may use --without-gsm to compile without gsm codec support.])]
			)
		]
	 )

AC_DEFINE_UNQUOTED([HAVE_GSM], `if test "x$with_gsm" = "xyes"; then echo 1; else echo 0; fi`, [Define if you have libgsm])
AM_CONDITIONAL(BUILD_GSM, test "x$with_gsm" = "xyes" )

dnl Check for libspeex
AC_ARG_WITH([speex],
		[AS_HELP_STRING([--without-speex],
		[disable support for speex codec])],
		[],
		[with_speex=yes])

AS_IF([test "x$with_speex" != xno],
		[AC_CHECK_HEADER([speex/speex.h], , AC_MSG_FAILURE([Unable to find the libspeex headers (you may need to install the dev package).  You may use --without-speex to compile without speex codec support.]))]
		[AC_CHECK_LIB([speex], [speex_decode_int],
		[],
		[AC_MSG_FAILURE([libspeex link test failed.   You may use --without-speex to compile without speex codec support.])])
		])
		
AC_DEFINE_UNQUOTED([HAVE_SPEEX], `if test "x$with_speex" = "xyes"; then echo 1; else echo 0; fi`, [Define if you have libspeex])
AM_CONDITIONAL(BUILD_SPEEX, test "x$with_speex" = "xyes" )

dnl check in case the libspeexdsp is not installed
AC_CHECK_HEADER([speex/speex_preprocess.h], , AC_MSG_FAILURE([Unable to find the libspeexdsp headers (you may need to install the libspeexdsp-dev package) used for Noise Suppression and Automatic Gain Control.]))
AC_CHECK_LIB(speexdsp, speex_preprocess_run, [], [], [])


# check for libcelt
AC_ARG_WITH([celt],
		[AS_HELP_STRING([--without-celt],
		[disable support for celt codec])],
		[],
		[with_celt=yes])

AS_IF([test "x$with_celt" != xno],
	[PKG_CHECK_MODULES(CELT, celt >= 0.9.1,
		[
			with_celt_91=yes; AC_MSG_NOTICE([Using celt 0.9.1])
    	],
    	[
			PKG_CHECK_MODULES(CELT, celt >= 0.7.1,
            [
                with_celt_71=yes; AC_MSG_NOTICE([Using celt 0.7.1])
            ],
            [
                AC_MSG_FAILURE([libcelt link test failed.   You may use --without-celt to compile without celt codec support.])
            ])
    	])]
)

# AC_SUBST(BUILD_CELT)
# AM_CONDITIONAL(BUILD_CELT, test "x$with_celt" = "xyes" )
AM_CONDITIONAL(BUILD_CELT_91, test "x$with_celt_91" = "xyes" )
AM_CONDITIONAL(BUILD_CELT_71, test "x$with_celt_71" = "xyes" )


dnl Check for IAX
AC_ARG_WITH([iax2],
		[AS_HELP_STRING([--without-iax2],
			[disable support for the iax2 protocol])],
		[],
		[with_iax2=yes])

AC_DEFINE_UNQUOTED([HAVE_IAX], `if test "x$with_iax2" = "xyes"; then echo 1; else echo 0;fi`, [Define if you have libiax2])
AM_CONDITIONAL(USE_IAX, test "x$with_iax2" = "xyes" )

	dnl Check for network-manager
AC_ARG_WITH([networkmanager],
		[AS_HELP_STRING([--without-networkmanager],
			[disable support for network-manager events])],
		[],
		[with_networkmanager=yes])

AM_CONDITIONAL(USE_NETWORKMANAGER, test "x$with_networkmanager" = "xyes" )

# check for doxygen, mostly stolen from http://log4cpp.sourceforge.net/
# ----------------------------------------------------------------------------
AC_DEFUN([BB_ENABLE_DOXYGEN],
    [
    AC_ARG_ENABLE(doxygen, [  --enable-doxygen        enable documentation generation with doxygen (disabled by default)])
    AC_ARG_ENABLE(dot, [  --enable-dot            use 'dot' to generate graphs in doxygen (auto)])
    if test "x$enable_doxygen" = xyes; then
        AC_PATH_PROG(DOXYGEN, doxygen, , $PATH)
        test x$DOXYGEN = x && AC_MSG_ERROR([could not find doxygen])
        AC_PATH_PROG(DOT, dot, , $PATH)
        test x$DOT = x -a "x$enable_dot" = xyes && AC_MSG_ERROR([could not find dot])
    fi
	AM_CONDITIONAL(ENABLE_DOXYGEN, test x$DOXYGEN = xyes)
])
# Acutally perform the doxygen check
BB_ENABLE_DOXYGEN

# Go!
AC_OUTPUT

AC_MSG_NOTICE([[Configuration done! Please make sure that pjsip library (libs/pjproject) has already been compiled. Run `make' to build the software.]])

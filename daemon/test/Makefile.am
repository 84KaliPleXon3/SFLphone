include ../globals.mak

TESTS_ENVIRONMENT = CODECS_PATH="$(top_builddir)/src/audio/codecs" \
					FAKE_PLUGIN_DIR="$(top_builddir)/src/plug-in/test/" \
					FAKE_PLUGIN_NAME="$(top_builddir)/src/plug-in/test/libplugintest.so"
check_PROGRAMS = test
TESTS = run_tests.sh

test_CXXFLAGS = $(CPPUNIT_CFLAGS)
test_LDADD = $(LLIBS) @LIBCRYPTO_LIBS@

test_SOURCES = \
	main.cpp \
	validator.cpp \
	validator.h \
	accounttest.h \
	accounttest.cpp \
	audiolayertest.h \
	audiolayertest.cpp \
	configurationtest.h \
	configurationtest.cpp \
	historytest.h \
	historytest.cpp \
	hookmanagertest.h \
	hookmanagertest.cpp \
	numbercleanertest.h \
	numbercleanertest.cpp \
	pluginmanagertest.h \
	pluginmanagertest.cpp \
	rtptest.h \
	rtptest.cpp \
	sdesnegotiatortest.h \
	sdesnegotiatortest.cpp \
	instantmessagingtest.h \
	instantmessagingtest.cpp \
	siptest.h \
	siptest.cpp \
	sdptest.h \
	sdptest.cpp \
	echocanceltest.h \
	echocanceltest.cpp \
	gaincontroltest.h \
	gaincontroltest.cpp

LLIBS=$(CPPUNIT_LIBS) ../src/libsflphone.la

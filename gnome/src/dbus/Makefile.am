include ../../globals.mak

noinst_LTLIBRARIES=libdbus.la

BUILT_SOURCES=                      \
    callmanager-glue.h              \
    configurationmanager-glue.h     \
    instance-glue.h                 \
    marshaller.c                    \
    marshaller.h

# Rule to generate the binding headers
%-glue.h: %-introspec.xml Makefile.am
	dbus-binding-tool --mode=glib-client $<  > $@

# Create the necessary marshallers for the signals implemented by the library
marshaller.c: marshaller.list
	glib-genmarshal --body --g-fatal-warnings $< > $@

marshaller.h: marshaller.list
	glib-genmarshal --header --g-fatal-warnings $< > $@

libdbus_la_SOURCES=     \
    dbus.c              \
    $(BUILT_SOURCES)

libdbus_la_LDFLAGS= $(DBUSGLIB_LDFLAGS) $(LIBNOTIFY_LDFLAGS) \
			$(SFLGTK_LDFLAGS) $(SFLGLIB_LDFLAGS) $(WEBKIT_LDFLAGS) $(LIBGNOMEUI_LDFLAGS) \
			$(GNOMEDOCUTILS_LDFLAGS)

libdbus_la_CFLAGS= $(DBUSGLIB_CFLAGS) $(LIBNOTIFY_CFLAGS) \
			$(SFLGTK_CFLAGS) $(SFLGLIB_CFLAGS) $(WEBKIT_CFLAGS) $(LIBGNOMEUI_CFLAGS) \
			$(GNOMEDOCUTILS_CFLAGS)

EXTRA_DIST= \
    marshaller.list

CLEANFILES= \
    $(BUILT_SOURCES)

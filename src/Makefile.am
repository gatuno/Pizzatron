# Automake file for Pizzatron

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = pizzatron
pizzatron_SOURCES = pizzatron.c cp-button.c cp-button.h gettext.h
EXTRA_DIST = pizzatron.rc

if MINGW32
pizzatron_ico.o: pizzatron.rc ../data/pizzatron.ico
	$(WINDRES) $(srcdir)/pizzatron.rc -O coff -o pizzatron_ico.o

mingw_ldadd = pizzatron_ico.o
else # NOT MINGW
mingw_ldadd =
endif

pizzatron_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" $(AM_CPPFLAGS)
pizzatron_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_ttf_LIBS) $(CPSTAMP_CFLAGS) $(AM_CFLAGS)
pizzatron_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS) $(SDL_ttf_LIBS) $(CPSTAMP_LIBS) $(mingw_ldadd)
LDADD = $(LIBINTL)

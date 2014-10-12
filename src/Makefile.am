# Automake file for Pizzatron

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = pizzatron
pizzatron_SOURCES = pizzatron.c
#EXTRA_DIST =

pizzatron_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" $(AM_CPPFLAGS)
pizzatron_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_ttf_LIBS) $(AM_CFLAGS)
pizzatron_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS) $(SDL_ttf_LIBS)


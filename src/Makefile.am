# Automake file for Pizzatron

gamedatadir = $(pkgdatadir)/data

bin_PROGRAMS = pizzatron
pizzatron_SOURCES = pizzatron.c \
	cp-button.c cp-button.h \
	gettext.h \
	rotar.c rotar.h \
	draw-text.c draw-text.h \
	path.c path.h

if MACOSX
pizzatron_SOURCES += SDLMain.m SDLMain.h
endif

EXTRA_DIST = pizzatron.rc SDLMain.m SDLMain.h

if MINGW32
pizzatron_ico.o: pizzatron.rc ../data/pizzatron.ico
	$(WINDRES) $(srcdir)/pizzatron.rc -O coff -o pizzatron_ico.o

mingw_ldadd = pizzatron_ico.o
else # NOT MINGW
mingw_ldadd =
endif

pizzatron_CPPFLAGS = -DGAMEDATA_DIR=\"$(gamedatadir)/\" -DLOCALEDIR=\"$(localedir)\" $(AM_CPPFLAGS)
pizzatron_CFLAGS = $(SDL_CFLAGS) $(SDL_image_CFLAGS) $(SDL_mixer_CFLAGS) $(SDL_ttf_CFLAGS) $(CPSTAMP_CFLAGS) $(AM_CFLAGS)
if MACOSX
# En MAC OS X, hay que ligar/compilar contra los frameworks
pizzatron_LDFLAGS = -Wl,-rpath,@loader_path/../Frameworks $(AM_LDFLAGS)
else
pizzatron_LDADD = $(SDL_LIBS) $(SDL_image_LIBS) $(SDL_mixer_LIBS) $(SDL_ttf_LIBS) -lm $(CPSTAMP_LIBS) $(mingw_ldadd)
endif
LDADD = $(LIBINTL)

#------------------ Packaging rules for Mac OSX ------------------------

bundle_root = $(top_builddir)/etc/macfiles
bundle_name = $(bundle_root)/Pizzatron.app
# Special target to copy all needed game files to Pizzatron.app/Contents/Resources.
# For Mac OS X bundle.
.PHONY: bundle
bundle:
	-rm -rf $(bundle_root)
	mkdir -p $(bundle_name)/Contents/MacOS
	mkdir -p $(bundle_name)/Contents/Resources/data/
	echo "APPL????" > $(bundle_name)/Contents/PkgInfo
	cp $(top_builddir)/etc/Info.plist $(bundle_name)/Contents/
	cp $(top_builddir)/etc/pizzatron.icns $(bundle_name)/Contents/Resources/
	mkdir -p $(bundle_name)/Contents/Resources/data/images
	cp $(top_builddir)/data/images/*.png $(bundle_name)/Contents/Resources/data/images
	mkdir -p $(bundle_name)/Contents/Resources/data/images/stamps
	cp $(top_builddir)/data/images/stamps/*.png $(bundle_name)/Contents/Resources/data/images/stamps
	mkdir -p $(bundle_name)/Contents/Resources/data/images/es
	cp $(top_builddir)/data/images/es/*.png $(bundle_name)/Contents/Resources/data/images/es
	mkdir -p $(bundle_name)/Contents/Resources/data/images/de
	cp $(top_builddir)/data/images/de/*.png $(bundle_name)/Contents/Resources/data/images/de
	mkdir -p $(bundle_name)/Contents/Resources/data/images/fr
	cp $(top_builddir)/data/images/fr/*.png $(bundle_name)/Contents/Resources/data/images/fr
	mkdir -p $(bundle_name)/Contents/Resources/data/music
	cp $(top_builddir)/data/music/* $(bundle_name)/Contents/Resources/data/music
	mkdir -p $(bundle_name)/Contents/Resources/data/sounds
	cp $(top_builddir)/data/sounds/* $(bundle_name)/Contents/Resources/data/sounds
	cp $(top_builddir)/data/*.ttf $(bundle_name)/Contents/Resources/data
	for cat in $(ALL_LINGUAS); do \
	  dir=$(bundle_name)/Contents/Resources/locale/$$cat/LC_MESSAGES; \
	  mkdir -p $$dir; \
	  echo "installing $$cat as $$dir/pizzatron.mo"; \
	  cp $(top_builddir)/po/$$cat.gmo $$dir/pizzatron.mo; \
	done

# Special target to copy the binary to Pizzatron.app/Contents/MacOS.
.PHONY: bundle-fw
bundle-fw: bundle
	cp pizzatron $(bundle_name)/Contents/MacOS/pizzatron
	mkdir  $(bundle_name)/Contents/Frameworks
	for i in SDL SDL_mixer SDL_image SDL_ttf CPStamp; do \
	  cp -a /Library/Frameworks/$${i}.framework $(bundle_name)/Contents/Frameworks/; \
	done
	strip $(bundle_name)/Contents/MacOS/pizzatron

# Special target to make a disk image of the bundled app
.PHONY: bundle-dmg
bundle-dmg: bundle-fw
	ln -s /Applications $(bundle_root)/Applications
	hdiutil create  -ov -srcfolder $(bundle_root) -volname Pizzatron -imagekey zlib-level=6 $(top_builddir)/etc/pizzatron.dmg


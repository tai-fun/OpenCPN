## Process this file with automake to produce Makefile.in

VERSION=1.3.6
COPYRIGHT_YEAR=2009
WX_LIB_DIR=$(WX_HOME)/lib

INCLUDES = \
	 -I./$(srcdir)/include -I./$(srcdir)/src/nmea0183\
	 -I/usr/X11R6/include\
	 -I./$(srcdir)/src/mygdal\
	 -I./$(srcdir)/src/grib\
	 -I./$(srcdir)/src/grib/bzip2




AM_CFLAGS =\
	 -Wall\
	 -g

AM_CXXFLAGS =\
	 -Wall\
	 -g

opencpn_LDFLAGS =

opencpn_LDADD =  \
	$(WX_LIBS)

wxhome= $(WX_HOME)

#	The variable BUILD_WITH_GTK_OPTIMIZATION comes from configure script AM_CONDITIONAL()
if BUILD_WITH_GTK_OPTIMIZATION
AM_CFLAGS += -DocpnUSE_GTK_OPTIMIZE
AM_CXXFLAGS += -DocpnUSE_GTK_OPTIMIZE
endif


#	The variable BUILD_WITH_S57 comes from configure script AM_CONDITIONAL()
if BUILD_WITH_S57
AM_CFLAGS += -DUSE_S57
AM_CXXFLAGS += -DUSE_S57
endif

#	The variable BUILD_WITH_GLU_TESS comes from configure script AM_CONDITIONAL()
if BUILD_WITH_GLU_TESS
AM_CFLAGS += $(GL_CFLAGS)
AM_CXXFLAGS += $(GL_CFLAGS)
opencpn_LDADD += $(GL_LIBS)
endif



bin_PROGRAMS = opencpn

opencpn_SOURCES = 	src/bbox.cpp \
 			src/ocpn_pixel.cpp \
			src/chart1.cpp \
			src/chartdb.cpp \
			src/chartdbs.cpp \
			src/chartimg.cpp \
			src/chcanv.cpp \
			src/concanv.cpp \
			src/cutil.c \
			src/georef.c \
			src/navutil.cpp \
			src/nmea.cpp \
			src/routeman.cpp \
			src/routeprop.cpp \
			src/statwin.cpp \
			src/tcmgr.cpp \
			src/thumbwin.cpp \
			src/options.cpp \
			src/wvschart.cpp \
			src/about.cpp \
			src/ais.cpp \
			src/cm93.cpp \
			src/nmea0183/latlong.cpp \
			src/nmea0183/long.cpp \
			src/nmea0183/nmea0183.cpp \
			src/nmea0183/nmea0183.hpp \
			src/nmea0183/response.cpp \
			src/nmea0183/rmb.cpp \
			src/nmea0183/sentence.cpp \
			src/nmea0183/talkerid.cpp \
			src/nmea0183/rmc.cpp \
			src/nmea0183/hexvalue.cpp \
			src/nmea0183/lat.cpp \
			src/nmea0183/expid.cpp \
			src/nmea0183/wpl.cpp \
			src/nmea0183/rte.cpp \
			src/nmea0183/hdt.cpp \
			src/nmea0183/hdg.cpp \
			src/nmea0183/hdm.cpp \
			src/nmea0183/gll.cpp \
			src/nmea0183/vtg.cpp \
			src/scrollingdialog.cpp \
			src/grib.cpp \
			src/grib/GribReader.cpp \
			src/grib/GribRecord.cpp  \
			src/grib/zuFile.cpp \
			src/grib/IsoLine.cpp \
			src/grib/bzip2/blocksort.c \
			src/grib/bzip2/bzlib.c \
			src/grib/bzip2/compress.c \
			src/grib/bzip2/crctable.c \
			src/grib/bzip2/decompress.c \
			src/grib/bzip2/huffman.c \
			src/grib/bzip2/randtable.c 

if BUILD_WITH_S57
opencpn_SOURCES +=	src/s52cnsy.cpp \
			src/s52plib.cpp \
			src/s52utils.cpp \
			src/s57chart.cpp \
			src/mygeom.cpp \
			src/tri.c
endif

if BUILD_WITH_S57
opencpn_SOURCES +=	src/myiso8211/ddffielddefn.cpp \
			src/myiso8211/ddfmodule.cpp \
			src/myiso8211/ddfrecord.cpp \
			src/myiso8211/ddfsubfielddefn.cpp \
			src/myiso8211/ddffield.cpp \
			src/myiso8211/ddfutils.cpp \
			src/mygdal/ddfrecordindex.cpp \
			src/mygdal/cpl_conv.cpp \
			src/mygdal/cpl_csv.cpp \
			src/mygdal/cpl_dir.cpp \
			src/mygdal/cpl_error.cpp \
	 		src/mygdal/cpl_findfile.cpp \
			src/mygdal/cpl_minixml.cpp \
			src/mygdal/cpl_path.cpp \
	 		src/mygdal/cpl_string.cpp \
			src/mygdal/cpl_vsisimple.cpp \
			src/mygdal/cplgetsymbol.cpp \
			src/mygdal/ograssemblepolygon.cpp \
			src/mygdal/ogrcurve.cpp \
			src/mygdal/ogrfeature.cpp \
			src/mygdal/ogrfeaturedefn.cpp \
			src/mygdal/ogrfielddefn.cpp \
			src/mygdal/ogrgeometry.cpp \
			src/mygdal/ogrgeometrycollection.cpp \
			src/mygdal/ogrgeometryfactory.cpp \
			src/mygdal/ogrlinearring.cpp \
			src/mygdal/ogrlinestring.cpp \
			src/mygdal/ogrmultilinestring.cpp \
			src/mygdal/ogrmultipoint.cpp \
			src/mygdal/ogrmultipolygon.cpp \
			src/mygdal/ogrpoint.cpp \
			src/mygdal/ogrpolygon.cpp \
			src/mygdal/ogrs57datasource.cpp \
			src/mygdal/ogrlayer.cpp \
			src/mygdal/ogrs57layer.cpp \
			src/mygdal/ogrutils.cpp \
			src/mygdal/s57classregistrar.cpp \
			src/mygdal/s57featuredefns.cpp \
			src/mygdal/s57reader.cpp \
			src/mygdal/gdal_misc.cpp 
 
endif

if BUILD_WITH_WIFI_CLIENT
AM_CXXFLAGS += -DUSE_WIFI_CLIENT
opencpn_SOURCES += src/wificlient.cpp 
endif


noinst_HEADERS = \
 	include/about.h \
 	include/ais.h \
 	include/bbox.h \
 	include/chart1.h \
 	include/chartbase.h \
 	include/chartdb.h \
 	include/chartimg.h \
 	include/chcanv.h \
 	include/concanv.h \
 	include/cutil.h \
 	include/dychart.h \
 	include/georef.h \
  	include/mygeom.h \
 	include/navutil.h \
 	include/nmea.h \
 	include/ocpn_pixel.h \
 	include/options.h \
 	include/routeman.h \
 	include/s52plib.h \
 	include/s52s57.h \
 	include/s52utils.h \
 	include/s57chart.h \
 	include/s57mgr.h \
 	include/sercomm.h \
 	include/statwin.h \
 	include/tcmgr.h \
 	include/thumbwin.h \
 	include/triangulate.h \
 	include/wificlient.h \
 	include/wvschart.h \
 	include/cm93.h \
	include/grib.h \
	src/mygdal/cpl_config.h \
 	src/mygdal/cpl_conv.h \
 	src/mygdal/cpl_csv.h \
 	src/mygdal/cpl_error.h \
 	src/mygdal/cpl_list.h \
 	src/mygdal/cpl_minixml.h \
 	src/mygdal/cpl_multiproc.h \
 	src/mygdal/cpl_odbc.h \
 	src/mygdal/cpl_port.h \
 	src/mygdal/cpl_string.h \
 	src/mygdal/cpl_vsi.h \
 	src/nmea0183/nmea0183.h \
 	src/nmea0183/LatLong.hpp \
 	src/nmea0183/nmea0183.hpp \
 	src/nmea0183/Response.hpp \
 	src/nmea0183/RMB.hpp \
 	src/nmea0183/RMC.HPP \
 	src/nmea0183/Sentence.hpp \
 	src/nmea0183/hdt.hpp \
 	src/nmea0183/hdg.hpp \
 	src/nmea0183/hdm.hpp \
 	src/mygdal/iso8211.h \
 	src/mygdal/ogr_s57.h \
 	src/mygdal/s57.h \
 	src/mygdal/ogr_feature.h \
 	src/mygdal/ogr_geometry.h \
 	src/mygdal/ogr_p.h \
 	src/mygdal/ogr_attrind.h \
 	src/mygdal/ogrsf_frmts.h \
 	src/mygdal/ogr_spatialref.h \
 	src/mygdal/gdal.h \
 	src/mygdal/ogr_api.h \
 	src/mygdal/gdal_priv.h \
 	src/mygdal/gdal_frmts.h 



EXTRA_DIST = \
	data/wvsdata/readmewvs.txt \
	data/wvsdata/wvs1.dat \
	data/wvsdata/wvs43.dat \
	data/s57data/attdecode.csv \
	data/s57data/S52RAZDS.RLE \
	data/s57data/s57attributes.csv \
	data/s57data/s57expectedinput.csv \
	data/s57data/s57objectclasses.csv \
	data/tcdata/HARMONIC \
	data/tcdata/HARMONIC.IDX \
	src/bitmaps/down.xpm \
	src/bitmaps/left.xpm \
	src/bitmaps/pencil.xpm \
	src/bitmaps/right.xpm \
	src/bitmaps/up.xpm \
	src/bitmaps/settings.xpm \
	src/bitmaps/zoomin.xpm \
	src/bitmaps/zoomout.xpm \
	src/bitmaps/scin.xpm \
	src/bitmaps/scout.xpm \
	src/bitmaps/tide.xpm \
	src/bitmaps/text.xpm \
	src/bitmaps/route.xpm \
	src/bitmaps/exitt.xpm \
	src/bitmaps/follow.xpm \
	src/bitmaps/current.xpm \
	src/bitmaps/print.xpm \
	src/bitmaps/help.xpm \
	src/bitmaps/colscheme.xpm \
	makefile.wat


#          The variable BUILD_FOR_DARWIN comes from configure.in
#          Note that we redefine the target all to include invocation of Rez, the resource tool for OSx
if BUILD_FOR_DARWIN
opencpn_SOURCES += src/macsercomm.cpp
opencpn_SOURCES += src/macutils.c
noinst_HEADERS += include/macsercomm.h
noinst_HEADERS += include/macutils.h
APP = OpenCPN
bundle_dir = $(APP).app
contents_dir = $(APP).app/Contents
binary_dir = $(contents_dir)/MacOS
resource_dir = $(contents_dir)/Resources
support_dir = $(contents_dir)/SharedSupport
staging_dir = buildosx/app-bundle
dmg_staging_dir = $(APP)-$(VERSION)
WX_DYLIBS_PATTERN=*wx*$(WX_RELEASE).0.dylib
GL_PATTERN=libGL*.dylib
GL_LIB_LOC=/usr/X11R6/lib
GL_DEP_LIBS = `ls $(GL_LIB_LOC)/$(GL_PATTERN)`

all: opencpn $(binary_dir)/opencpn

$(binary_dir)/opencpn:	opencpn
	mkdir -p $(binary_dir) $(resource_dir) $(support_dir)
	sed "s/__VERSION__/$(VERSION)/;s/__COPYRIGHT_YEAR__/$(COPYRIGHT_YEAR)/" $(staging_dir)/Info.plist > $(contents_dir)/Info.plist
	cp $(staging_dir)/opencpn.icns $(resource_dir)
	cp opencpn $(binary_dir)
	cp -r data/license.txt data/*data $(support_dir)
	cp $(WX_LIB_DIR)/*.dylib $(binary_dir)
	cd $(binary_dir); \
	for i in `ls $(WX_DYLIBS_PATTERN)` ; \
		do echo patching load path for dynamic library $${i}; \
		for j in `ls $(WX_DYLIBS_PATTERN)`; \
			do install_name_tool -change $(WX_LIB_DIR)/$${i} @executable_path/$${i} $${j} ; \
		done ;\
		install_name_tool  -id  @executable_path/$${i} $${i} ;\
		install_name_tool  -change $(WX_LIB_DIR)/$${i} @executable_path/$${i} opencpn ; \
	done

dmg: $(binary_dir)/opencpn
	if [ -d $(dmg_staging_dir) ] ; then rm -rf $(dmg_staging_dir); fi
	mkdir -p $(dmg_staging_dir)
	cp -r $(bundle_dir) $(dmg_staging_dir)
	cp buildosx/README.rtf $(dmg_staging_dir)
	if [ -f OpenCPN.dmg ] ; then rm OpenCPN.dmg; fi
	hdiutil create -megabytes 95 -srcfolder $(dmg_staging_dir) OpenCPN.dmg
endif


## Installation
##  The static data files will go into @prefix@/share/opencpn, default is e.g. /usr/local/share/opencpn

install-data-local:
	mkdir -p $(DESTDIR)$(pkgdatadir)
	mkdir -p $(DESTDIR)$(pkgdatadir)/wvsdata
	cp -p ./$(srcdir)/data/wvsdata/wvs1.dat $(DESTDIR)$(pkgdatadir)/wvsdata
	cp -p ./$(srcdir)/data/wvsdata/wvs43.dat $(DESTDIR)$(pkgdatadir)/wvsdata
	cp -p ./$(srcdir)/data/wvsdata/readmewvs.txt $(DESTDIR)$(pkgdatadir)/wvsdata
	mkdir -p $(DESTDIR)$(pkgdatadir)/s57data
	cp -p ./$(srcdir)/data/s57data/s57attributes.csv $(DESTDIR)$(pkgdatadir)/s57data
	cp -p ./$(srcdir)/data/s57data/s57objectclasses.csv $(DESTDIR)$(pkgdatadir)/s57data
	cp -p ./$(srcdir)/data/s57data/s57expectedinput.csv $(DESTDIR)$(pkgdatadir)/s57data
	cp -p ./$(srcdir)/data/s57data/attdecode.csv $(DESTDIR)$(pkgdatadir)/s57data
	cp -p ./$(srcdir)/data/s57data/S52RAZDS.RLE $(DESTDIR)$(pkgdatadir)/s57data
	mkdir -p $(DESTDIR)$(pkgdatadir)/tcdata
	cp -p ./$(srcdir)/data/tcdata/HARMONIC  $(DESTDIR)$(pkgdatadir)/tcdata
	cp -p ./$(srcdir)/data/tcdata/HARMONIC.IDX  $(DESTDIR)$(pkgdatadir)/tcdata
	cp -p ./$(srcdir)/data/license.txt  $(DESTDIR)$(pkgdatadir)
	mkdir -p $(DESTDIR)$(pkgdatadir)/doc
	cp -p ./$(srcdir)/data/doc/help.html  $(DESTDIR)$(pkgdatadir)/doc
	mkdir -p $(DESTDIR)$(pkgdatadir)/doc/images
	cp -p ./$(srcdir)/data/doc/images/*  $(DESTDIR)$(pkgdatadir)/doc/images
	mkdir -p $(DESTDIR)$(pkgdatadir)/doc/includes
	cp -p ./$(srcdir)/data/doc/includes/*  $(DESTDIR)$(pkgdatadir)/doc/includes
	cp -p ./$(srcdir)/data/opencpn.png  /usr/share/icons
	cp -p ./$(srcdir)/data/opencpn.desktop  /usr/share/applications
	mkdir -p /usr/local/share/locale/de/LC_MESSAGES
	mkdir -p /usr/local/share/locale/da/LC_MESSAGES
	mkdir -p /usr/local/share/locale/it/LC_MESSAGES
	mkdir -p /usr/local/share/locale/pl/LC_MESSAGES
	mkdir -p /usr/local/share/locale/fr/LC_MESSAGES
	mkdir -p /usr/local/share/locale/es/LC_MESSAGES
	mkdir -p /usr/local/share/locale/nl/LC_MESSAGES
	mkdir -p /usr/local/share/locale/sv/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_de_DE.mo /usr/local/share/locale/de/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_da_DK.mo /usr/local/share/locale/da/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_it_IT.mo /usr/local/share/locale/it/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_pl_PL.mo /usr/local/share/locale/pl/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_fr_FR.mo /usr/local/share/locale/fr/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_es_ES.mo /usr/local/share/locale/es/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_nl_NL.mo /usr/local/share/locale/nl/LC_MESSAGES
	cp -p ./$(srcdir)/po/opencpn_sv_SE.mo /usr/local/share/locale/sv/LC_MESSAGES


uninstall-local:
	rm -fr $(DESTDIR)$(pkgdatadir)/wvsdata/*
	rm -fr $(DESTDIR) $(pkgdatadir)/s57data/* 
	rm -fr $(DESTDIR)$(pkgdatadir)/tcdata/* 
	rmdir $(DESTDIR)$(pkgdatadir)/wvsdata
	rmdir $(DESTDIR)$(pkgdatadir)/s57data 
	rmdir $(DESTDIR)$(pkgdatadir)/tcdata 
	rmdir $(DESTDIR)$(pkgdatadir)

$(srcdir)/po/opencpn.pot: opencpn
	mkdir -p ./po
	xgettext --package-name opencpn --package-version 1.3.6  -o ./po/opencpn.pot  ./src/*.cpp --keyword=_ --width=80

messages: $(srcdir)/po/opencpn.pot
	msgmerge ./po/opencpn_de_DE.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_de_DE.mo ./po/opencpn_de_DE.po 
	msgmerge ./po/opencpn_da_DK.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_da_DK.mo ./po/opencpn_da_DK.po 
	msgmerge ./po/opencpn_it_IT.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_it_IT.mo ./po/opencpn_it_IT.po 
	msgmerge ./po/opencpn_pl_PL.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_pl_PL.mo ./po/opencpn_pl_PL.po 
	msgmerge ./po/opencpn_fr_FR.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_fr_FR.mo ./po/opencpn_fr_FR.po 
	msgmerge ./po/opencpn_es_ES.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_es_ES.mo ./po/opencpn_es_ES.po 
	msgmerge ./po/opencpn_nl_NL.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_nl_NL.mo ./po/opencpn_nl_NL.po 
	msgmerge ./po/opencpn_sv_SE.po ./po/opencpn.pot --width=80 --strict -U --backup=none --no-location
	msgfmt --check --output-file ./po/opencpn_sv_SE.mo ./po/opencpn_sv_SE.po 



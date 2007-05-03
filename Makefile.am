## Process this file with automake to produce Makefile.in

VERSION=1.2.0

INCLUDES = \
	$(WX_CXXFLAGS)\
	 -I./$(srcdir)/include -I./$(srcdir)/src/nmea0183\
	-I/usr/include/gtk-2.0 -I/usr/lib/gtk-2.0/include -I/usr/X11R6/include\
        -I/usr/include/atk-1.0 -I/usr/include/pango-1.0 -I/usr/include/freetype2\
        -I/usr/include/freetype2/config -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include

AM_CFLAGS =\
	 -Wall\
	 -g

AM_CXXFLAGS =\
	 -Wall\
	 -g

opencpn_LDFLAGS =

opencpn_LDADD =  \
	$(WX_LIBS)





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
			src/chartimg.cpp \
			src/chcanv.cpp \
			src/concanv.cpp \
			src/cutil.c \
			src/georef.c \
			src/navutil.cpp \
			src/nmea.cpp \
			src/routeman.cpp \
			src/sercomm.cpp \
			src/statwin.cpp \
			src/tcmgr.cpp \
			src/thumbwin.cpp \
			src/options.cpp \
			src/wvschart.cpp \
			src/about.cpp \
			src/ais.cpp \
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
			src/nmea0183/expid.cpp

if BUILD_WITH_S57
opencpn_SOURCES +=	src/s52cnsy.cpp \
			src/s52plib.cpp \
			src/s52utils.cpp \
			src/s57chart.cpp \
			src/mygeom.cpp \
			src/tri.c
endif

if BUILD_WITH_SHARED_GDAL
opencpn_SOURCES +=	src/myiso8211/ddffielddefn.cpp \
			src/myiso8211/ddfmodule.cpp \
			src/myiso8211/ddfrecord.cpp \
			src/myiso8211/ddfsubfielddefn.cpp \
			src/myiso8211/ddfutils.cpp

opencpn_LDADD += $(GDAL_LIBS)
AM_CFLAGS += $(GDAL_CFLAGS)
endif

if BUILD_WITH_INTERNAL_GDAL
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
			src/mygdal/ogr_fromepsg.cpp \
			src/mygdal/ogr_srs_esri.cpp \
			src/mygdal/ogr_srs_proj4.cpp \
			src/mygdal/ogr_srs_xml.cpp \
			src/mygdal/ogr_srsnode.cpp \
			src/mygdal/ograssemblepolygon.cpp \
			src/mygdal/ogrct.cpp \
			src/mygdal/ogrcurve.cpp \
			src/mygdal/ogrdatasource.cpp \
			src/mygdal/ogrfeature.cpp \
			src/mygdal/ogrfeaturedefn.cpp \
			src/mygdal/ogrfeaturequery.cpp \
			src/mygdal/ogrfielddefn.cpp \
			src/mygdal/ogrgeometry.cpp \
			src/mygdal/ogrgeometrycollection.cpp \
			src/mygdal/ogrgeometryfactory.cpp \
			src/mygdal/ogrlayer.cpp \
			src/mygdal/ogrlinearring.cpp \
			src/mygdal/ogrlinestring.cpp \
			src/mygdal/ogrmultilinestring.cpp \
			src/mygdal/ogrmultipoint.cpp \
			src/mygdal/ogrmultipolygon.cpp \
			src/mygdal/ogrpoint.cpp \
			src/mygdal/ogrpolygon.cpp \
			src/mygdal/ogrs57datasource.cpp \
			src/mygdal/ogrs57driver.cpp \
			src/mygdal/ogrs57layer.cpp \
			src/mygdal/ogrsfdriver.cpp \
			src/mygdal/ogrsfdriverregistrar.cpp \
			src/mygdal/ogrspatialreference.cpp \
			src/mygdal/ogrutils.cpp \
			src/mygdal/s57classregistrar.cpp \
			src/mygdal/s57featuredefns.cpp \
			src/mygdal/s57filecollector.cpp\
			src/mygdal/s57reader.cpp \
			src/mygdal/swq.c  \
			src/mygdal/ogr_gensql.cpp \
			src/mygdal/ogr_srs_dict.cpp \
			src/mygdal/ogr_attrind.cpp \
			src/mygdal/ogr_nullattrind.cpp \
			src/mygdal/s57writer.cpp \
			src/mygdal/ogr2gmlgeometry.cpp \
			src/mygdal/gml2ogrgeometry.cpp \
			src/mygdal/gdal_misc.cpp

INCLUDES += -I./$(srcdir)/src/mygdal
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
 	include/iso8211.h \
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
 	src/mygdal/gdal_alg.h \
 	src/mygdal/gdal_frmts.h \
 	src/mygdal/gdal.h \
 	src/mygdal/gdal_priv.h \
 	src/mygdal/gdalwarper.h \
 	src/mygdal/iso8211.h \
 	src/mygdal/ogr_api.h \
 	src/mygdal/ogr_attrind.h \
 	src/mygdal/ogr_core.h \
 	src/mygdal/ogr_feature.h \
 	src/mygdal/ogr_featurestyle.h \
 	src/mygdal/ogr_gensql.h \
 	src/mygdal/ogr_geometry.h \
 	src/mygdal/ogr_p.h \
 	src/mygdal/ogr_s57.h \
 	src/mygdal/ogrsf_frmts.h \
 	src/mygdal/ogr_spatialref.h \
 	src/mygdal/ogr_srs_api.h \
 	src/mygdal/s57.h \
 	src/mygdal/sfclsid.h \
 	src/mygdal/sfiiddef.h \
 	src/mygdal/swq.h \
 	src/nmea0183/nmea0183.h \
 	src/nmea0183/LatLong.hpp \
 	src/nmea0183/nmea0183.hpp \
 	src/nmea0183/Response.hpp \
 	src/nmea0183/RMB.hpp \
 	src/nmea0183/RMC.HPP \
 	src/nmea0183/Sentence.hpp

EXTRA_DIST = \
	data/wvsdata/readmewvs.txt \
	data/wvsdata/wvs1.dat \
	data/wvsdata/wvs43.dat \
	data/s57data/attdecode.csv \
	data/s57data/S52RAZDS.RLE \
	data/s57data/S52RGB.TXT \
	data/s57data/s57attributes.csv \
	data/s57data/s57expectedinput.csv \
	data/s57data/s57objectclasses.csv \
	data/s57data/SP52COL.DAT \
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


## Installation
##  The static data files will go into @prefix@/share/opencpn, default is e.g. /usr/local/share/opencpn

install-data-local:
	mkdir -p $(pkgdatadir)
	cp -r ./$(srcdir)/data/wvsdata $(pkgdatadir)
	cp -r ./$(srcdir)/data/s57data $(pkgdatadir)
	cp -r ./$(srcdir)/data/tcdata  $(pkgdatadir)

uninstall-local:
	rm -fr $(pkgdatadir)/wvsdata/*
	rm -fr $(pkgdatadir)/s57data/* 
	rm -fr $(pkgdatadir)/tcdata/* 
	rmdir $(pkgdatadir)/wvsdata
	rmdir $(pkgdatadir)/s57data 
	rmdir $(pkgdatadir)/tcdata 
	rmdir $(pkgdatadir)




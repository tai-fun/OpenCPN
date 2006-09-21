## Process this file with automake to produce Makefile.in


INCLUDES = \
	$(WX_CXXFLAGS)\
	 -Iinclude -Isrc/nmea0183 -Isrc/dialog

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
AM_CFLAGS += -DUSE_GLU_TESS
AM_CXXFLAGS += -DUSE_GLU_TESS
opencpn_LDADD += -lGL -lGLU
endif

bin_PROGRAMS = opencpn

opencpn_SOURCES = 	src/bbox.cpp \
 			src/bitmapo.cpp \
			src/chart1.cpp \
			src/chartdb.cpp \
			src/chartimg.cpp \
			src/chcanv.cpp \
			src/concanv.cpp \
			src/cutil.c \
			src/dataum.c \
			src/dymemdc.cpp \
			src/georef.c \
			src/navutil.cpp \
			src/nmea.cpp \
			src/routeman.cpp \
			src/sercomm.cpp \
			src/statwin.cpp \
			src/tcmgr.cpp \
			src/thumbwin.cpp \
			src/dialog/options.cpp \
			src/wvschart.cpp \
			src/about.cpp \
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
			src/gpc.c \
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

INCLUDES += -Isrc/mygdal
endif

if BUILD_WITH_WIFI_CLIENT
AM_CXXFLAGS += -DUSE_WIFI_CLIENT
opencpn_SOURCES +=	src/wificlient.cpp 
endif


## Installation

install-data-local:
	cp -r data/wvsdata $(pkgdatadir)
	cp -r data/s57data $(pkgdatadir)
	cp -r data/bitmaps $(pkgdatadir)
	cp -r data/tcdata $(pkgdatadir)






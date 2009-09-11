##---------------------------------------------------------------------------
## Author:      dsr
## Copyright:   
## License:     wxWidgets License
## Update:      
##---------------------------------------------------------------------------
 
# define minimum cmake version
cmake_minimum_required(VERSION 2.6.2)
 
# Our project is called 'opencpn' this is how it will be called in
# visual studio, and in our makefiles. 
project(opencpn)
 
# Location where cmake first looks for cmake modules.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
 
##---------------------------------------------------
## Please set your wxWidgets configuration here
##--------------------------------------------------- 
 
# Here you can define what libraries of wxWidgets you need for your
# application. You can figure out what libraries you need here;
# http://www.wxwidgets.org/manuals/2.8/wx_librarieslist.html
# We need the Find package for wxWidgets to work

#set(wxWidgets_ROOT_DIR c:/wxWidgets-2.8.10)
#set(wxWidgets_LIB_DIR  c:/wxWidgets-2.8.10/vc_lib)      
#set(wxWidgets_CONFIGURATION msw)

find_package(wxWidgets COMPONENTS base core html net media xml adv REQUIRED)
 
##---------------------------------------------------
## Actual config file starts here
##--------------------------------------------------- 
 
# wxWidgets include directory
include_directories(${wxWidgets_INCLUDE_DIRS})
 
# add wxWidgets definitions
add_definitions(${wxWidgets_DEFINITIONS})

# add opencpn definitions
add_definitions(-DUSE_S57 -D__MSVC__ -DUSE_GLU_TESS)

# Add some definitions to satisfy MS
add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_DEPRECATE)
 
# For convenience we define the sources as a variable. You can add 
# header files and cpp/c files and CMake will sort them out

#set(OPENCPN_DIR U:/Projects/opencpn_sf/opencpn)

set(SRCS 
                        ${OPENCPN_DIR}/src/chart1.cpp
                        ${OPENCPN_DIR}/src/bbox.cpp 
 			${OPENCPN_DIR}/src/ocpn_pixel.cpp 
			${OPENCPN_DIR}/src/chart1.cpp 
			${OPENCPN_DIR}/src/chartdb.cpp 
			${OPENCPN_DIR}/src/chartimg.cpp 
			${OPENCPN_DIR}/src/chcanv.cpp 
			${OPENCPN_DIR}/src/concanv.cpp 
			${OPENCPN_DIR}/src/cutil.c 
			${OPENCPN_DIR}/src/georef.c 
			${OPENCPN_DIR}/src/navutil.cpp 
			${OPENCPN_DIR}/src/nmea.cpp 
			${OPENCPN_DIR}/src/routeman.cpp 
			${OPENCPN_DIR}/src/routeprop.cpp 
			${OPENCPN_DIR}/src/sercomm.cpp 
			${OPENCPN_DIR}/src/statwin.cpp 
			${OPENCPN_DIR}/src/tcmgr.cpp 
			${OPENCPN_DIR}/src/thumbwin.cpp 
			${OPENCPN_DIR}/src/options.cpp 
			${OPENCPN_DIR}/src/wvschart.cpp 
			${OPENCPN_DIR}/src/about.cpp 
			${OPENCPN_DIR}/src/ais.cpp 
			${OPENCPN_DIR}/src/cm93.cpp 
			${OPENCPN_DIR}/src/nmea0183/latlong.cpp 
			${OPENCPN_DIR}/src/nmea0183/long.cpp 
			${OPENCPN_DIR}/src/nmea0183/nmea0183.cpp 
			${OPENCPN_DIR}/src/nmea0183/nmea0183.hpp 
			${OPENCPN_DIR}/src/nmea0183/response.cpp 
			${OPENCPN_DIR}/src/nmea0183/rmb.cpp 
			${OPENCPN_DIR}/src/nmea0183/sentence.cpp 
			${OPENCPN_DIR}/src/nmea0183/talkerid.cpp 
			${OPENCPN_DIR}/src/nmea0183/rmc.cpp 
			${OPENCPN_DIR}/src/nmea0183/hexvalue.cpp 
			${OPENCPN_DIR}/src/nmea0183/lat.cpp 
			${OPENCPN_DIR}/src/nmea0183/expid.cpp 
			${OPENCPN_DIR}/src/nmea0183/wpl.cpp 
			${OPENCPN_DIR}/src/nmea0183/rte.cpp
			${OPENCPN_DIR}/src/nmea0183/hdt.cpp
 			${OPENCPN_DIR}/src/nmea0183/hdg.cpp
 			${OPENCPN_DIR}/src/nmea0183/hdm.cpp
                        ${OPENCPN_DIR}/src/s52cnsy.cpp 
			${OPENCPN_DIR}/src/s52plib.cpp 
			${OPENCPN_DIR}/src/s52utils.cpp 
			${OPENCPN_DIR}/src/s57chart.cpp 
			${OPENCPN_DIR}/src/mygeom.cpp 
			${OPENCPN_DIR}/src/tri.c
			${OPENCPN_DIR}/src/scrollingdialog.cpp
                        ${OPENCPN_DIR}/src/myiso8211/ddffielddefn.cpp 
			${OPENCPN_DIR}/src/myiso8211/ddfmodule.cpp 
			${OPENCPN_DIR}/src/myiso8211/ddfrecord.cpp 
			${OPENCPN_DIR}/src/myiso8211/ddfsubfielddefn.cpp 
			${OPENCPN_DIR}/src/myiso8211/ddffield.cpp 
			${OPENCPN_DIR}/src/myiso8211/ddfutils.cpp 
			${OPENCPN_DIR}/src/mygdal/ddfrecordindex.cpp 
			${OPENCPN_DIR}/src/mygdal/cpl_conv.cpp 
			${OPENCPN_DIR}/src/mygdal/cpl_csv.cpp 
			${OPENCPN_DIR}/src/mygdal/cpl_dir.cpp 
			${OPENCPN_DIR}/src/mygdal/cpl_error.cpp 
	 		${OPENCPN_DIR}/src/mygdal/cpl_findfile.cpp 
			${OPENCPN_DIR}/src/mygdal/cpl_minixml.cpp 
			${OPENCPN_DIR}/src/mygdal/cpl_path.cpp 
	 		${OPENCPN_DIR}/src/mygdal/cpl_string.cpp 
			${OPENCPN_DIR}/src/mygdal/cpl_vsisimple.cpp 
			${OPENCPN_DIR}/src/mygdal/cplgetsymbol.cpp 
			${OPENCPN_DIR}/src/mygdal/ograssemblepolygon.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrcurve.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrfeature.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrfeaturedefn.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrfielddefn.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrgeometry.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrgeometrycollection.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrgeometryfactory.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrlinearring.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrlinestring.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrmultilinestring.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrmultipoint.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrmultipolygon.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrpoint.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrpolygon.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrs57datasource.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrlayer.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrs57layer.cpp 
			${OPENCPN_DIR}/src/mygdal/ogrutils.cpp 
			${OPENCPN_DIR}/src/mygdal/s57classregistrar.cpp 
			${OPENCPN_DIR}/src/mygdal/s57featuredefns.cpp 
			${OPENCPN_DIR}/src/mygdal/s57reader.cpp 
			${OPENCPN_DIR}/src/mygdal/gdal_misc.cpp 
    )

# Add the include directories 
INCLUDE_DIRECTORIES(include ${OPENCPN_DIR}/include ${OPENCPN_DIR}/src/mygdal ${OPENCPN_DIR}/src/nmea0183)

# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if(WIN32)
  set(SRCS ${SRCS} ${OPENCPN_DIR}/src/opencpn.rc)
endif(WIN32)
 
# Here we define the executable 
# the above paths and defines will be used in this build
add_executable(opencpn WIN32 ${SRCS})
 
#set_target_properties(opencpn
#                        PROPERTIES COMPILE_FLAGS /Zp4
#                        )


set_target_properties(opencpn
                        PROPERTIES LINK_FLAGS /MANIFEST:NO
                        )


# We add to our target 'opencpn' the wxWidgets libraries. These are
# set for us by the find script. If you need other libraries, you
# can add them here as well. 
target_link_libraries(opencpn ${wxWidgets_LIBRARIES} setupapi.lib gdiplus.lib glu32.lib)


#  Fix up time_t definition
# Checks for 32-bit version. And always use 32-bit time_t for compatibility
IF(CMAKE_GENERATOR MATCHES "Visual Studio" AND CMAKE_SIZEOF_VOID_P MATCHES 4)
  ADD_DEFINITIONS(-D_USE_32BIT_TIME_T)
ENDIF(CMAKE_GENERATOR MATCHES "Visual Studio" AND CMAKE_SIZEOF_VOID_P MATCHES 4)

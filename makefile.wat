################################################################################
# Global build options
################################################################################

################################################################################
# OpenCPN build options
################################################################################

# Specify the application install location, (e.g. wmake -f makefile.wat install)
APPDIR = "c:\Program Files\opencpn"

# Release or Debug? [release,debug]
BUILD = release

# Where are the sources?
SRC_DIR = .

# Use S57 ENC Charts? [0,1]
USE_S57 = 1

# Specify the Tesselator option [0,1]
# If USE_GLU_TESS = 0, then compile with only the internal tesselator module
# If USE_GLU_TESS = 1, compile with additional linkages to GLU tesselator
USE_GLU_TESS = 1

# Specify linkage to glu32.lib, instead of default glu32.dll [0,1]
# One of the following is required if USE_GLU_TESS = 1
#  Also note, if glu32.dll is not available at run-time, the internal
#    tesselator will be used, with logged warning.
# ToDo:  This makefile needs some touchup to use gluxx.lib in MSW
USE_GLU_LIB = 0
USE_GLU_DLL = 1

# Enable the (undocumented) wifi client window [0,1]
USE_WIFI_CLIENT = 0

# Special configuration
CFG =

#################################################################################
# WXWIDGETS Location/Configuration
# Assumes the "standard" wxWidgets static distribution/build
#
# Some modifications will be required to the makefile if shared or monolithic
# wxWidgets libraries are to be used.
WX_BASE = c:\wx283
WX_RELEASE_NODOT = 28
#################################################################################


#################################################################################
#  Probably do not need modifications in following....
#################################################################################

# -------------------------------------------------------------------------
# These are wxWidgets configuration options:
# They MUST BE in sync with the options set to build the wxWidgets libraries
# as found in $(WXBASE)\build\msw\config.wat
# -------------------------------------------------------------------------
SHARED = 0
WXUNIV = 0
UNICODE = 0
MONOLITHIC = 1
USE_GUI = 1
USE_HTML = 1
USE_MEDIA = 1
USE_XRC = 1
USE_AUI = 1
USE_RICHTEXT = 1
USE_OPENGL = 0
USE_ODBC = 0
USE_QA = 0
USE_EXCEPTIONS = 1
USE_RTTI = 1
USE_THREADS = 1
USE_GDIPLUS = 0
RUNTIME_LIBS = static
DEBUG_INFO = default
DEBUG_FLAG = default


CC = wcc386
CXX = wpp386
CFLAGS = 
CXXFLAGS = 
CPPFLAGS = 
LDFLAGS = 
CPP = $(CC) -p


### Conditionally set variables: ###

!ifeq BUILD release
CPPFLAGS = -dNDEBUG
!endif

PORTNAME =
!ifeq USE_GUI 0
PORTNAME = base
!endif
!ifeq USE_GUI 1
PORTNAME = msw
!endif

WXDEBUGFLAG =
!ifeq BUILD debug
!ifeq DEBUG_FLAG default
WXDEBUGFLAG = d
!endif
!endif
!ifeq DEBUG_FLAG 1
WXDEBUGFLAG = d
!endif

WXUNICODEFLAG =
!ifeq UNICODE 1
WXUNICODEFLAG = u
!endif

WXUNIVNAME =
!ifeq WXUNIV 1
WXUNIVNAME = univ
!endif

WXDLLFLAG =
!ifeq SHARED 1
WXDLLFLAG = dll
!endif

LIBTYPE_SUFFIX =
!ifeq SHARED 0
LIBTYPE_SUFFIX = lib
!endif
!ifeq SHARED 1
LIBTYPE_SUFFIX = dll
!endif

EXTRALIBS_FOR_BASE =
!ifeq MONOLITHIC 0
EXTRALIBS_FOR_BASE = 
!endif
!ifeq MONOLITHIC 1
EXTRALIBS_FOR_BASE =  
!endif

__DEBUGINFO_0 =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO_0 = -d2
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO_0 = -d0
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO_0 = -d0
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO_0 = -d2
!endif

__DEBUGINFO_1 =
!ifeq BUILD debug
!ifeq DEBUG_INFO default
__DEBUGINFO_1 = debug all
!endif
!endif
!ifeq BUILD release
!ifeq DEBUG_INFO default
__DEBUGINFO_1 = 
!endif
!endif
!ifeq DEBUG_INFO 0
__DEBUGINFO_1 = 
!endif
!ifeq DEBUG_INFO 1
__DEBUGINFO_1 = debug all
!endif

__OPTIMIZEFLAG_2 =
!ifeq BUILD debug
__OPTIMIZEFLAG_2 = -od
!endif
!ifeq BUILD release
__OPTIMIZEFLAG_2 = -ot -ox
!endif

__THREADSFLAG_5 =
!ifeq USE_THREADS 0
__THREADSFLAG_5 = 
!endif
!ifeq USE_THREADS 1
__THREADSFLAG_5 = -bm
!endif

__RUNTIME_LIBS_6 =
!ifeq RUNTIME_LIBS dynamic
__RUNTIME_LIBS_6 = -br
!endif
!ifeq RUNTIME_LIBS static
__RUNTIME_LIBS_6 = 
!endif

__RTTIFLAG_7 =
!ifeq USE_RTTI 0
__RTTIFLAG_7 = 
!endif
!ifeq USE_RTTI 1
__RTTIFLAG_7 = -xr
!endif

__EXCEPTIONSFLAG_8 =
!ifeq USE_EXCEPTIONS 0
__EXCEPTIONSFLAG_8 = 
!endif
!ifeq USE_EXCEPTIONS 1
__EXCEPTIONSFLAG_8 = -xs
!endif

__WXLIB_CORE_p =
!ifeq MONOLITHIC 0
__WXLIB_CORE_p = &
	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core.lib
!endif

__WXLIB_BASE_p =
!ifeq MONOLITHIC 0
__WXLIB_BASE_p = &
	wxbase$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR).lib
!endif

__WXLIB_MONO_p =
!ifeq MONOLITHIC 1
__WXLIB_MONO_p = &
	wx$(PORTNAME)$(WXUNIVNAME)$(WX_RELEASE_NODOT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR).lib
!endif

__LIB_TIFF_p =
!ifeq USE_GUI 1
__LIB_TIFF_p = wxtiff$(WXDEBUGFLAG).lib
!endif

__LIB_JPEG_p =
!ifeq USE_GUI 1
__LIB_JPEG_p = wxjpeg$(WXDEBUGFLAG).lib
!endif

__LIB_PNG_p =
!ifeq USE_GUI 1
__LIB_PNG_p = wxpng$(WXDEBUGFLAG).lib
!endif

__GDIPLUS_LIB_p =
!ifeq USE_GDIPLUS 1
__GDIPLUS_LIB_p = gdiplus.lib
!endif

__WXUNIV_DEFINE_p =
!ifeq WXUNIV 1
__WXUNIV_DEFINE_p = -d__WXUNIVERSAL__
!endif

__DEBUG_DEFINE_p =
!ifeq BUILD debug
!ifeq DEBUG_FLAG default
__DEBUG_DEFINE_p = -d__WXDEBUG__
!endif
!endif
!ifeq DEBUG_FLAG 1
__DEBUG_DEFINE_p = -d__WXDEBUG__
!endif

__EXCEPTIONS_DEFINE_p =
!ifeq USE_EXCEPTIONS 0
__EXCEPTIONS_DEFINE_p = -dwxNO_EXCEPTIONS
!endif

__RTTI_DEFINE_p =
!ifeq USE_RTTI 0
__RTTI_DEFINE_p = -dwxNO_RTTI
!endif

__THREAD_DEFINE_p =
!ifeq USE_THREADS 0
__THREAD_DEFINE_p = -dwxNO_THREADS
!endif

__UNICODE_DEFINE_p =
!ifeq UNICODE 1
__UNICODE_DEFINE_p = -d_UNICODE
!endif

__GFXCTX_DEFINE_p =
!ifeq USE_GDIPLUS 1
__GFXCTX_DEFINE_p = -dwxUSE_GRAPHICS_CONTEXT=1
!endif

__DLLFLAG_p =
!ifeq SHARED 1
__DLLFLAG_p = -dWXUSINGDLL
!endif





### Variables: ###

OBJS = &
	wat_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WXDLLFLAG)$(CFG)
LIBDIRNAME = $(WX_BASE)\lib\wat_$(LIBTYPE_SUFFIX)$(CFG)
SETUPHDIR = &
	$(LIBDIRNAME)\$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)
	
PROJ_CXXFLAGS = $(__DEBUGINFO_0) $(__OPTIMIZEFLAG_2) $(__THREADSFLAG_5) &
	$(__RUNTIME_LIBS_6) -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) &
	$(__UNICODE_DEFINE_p) $(__GFXCTX_DEFINE_p) -i=$(SETUPHDIR) &
	-i=$(SRC_DIR)\include -wx -wcd=549 -wcd=656 -wcd=657 -wcd=667 -i=. $(__DLLFLAG_p) &
	-wcd=726 -wcd=389 -wcd=716 -wcd=391 &
	-i=$(GDAL_INCLUDE) -i=$(SRC_DIR)\src\nmea0183 $(__DS57) $(__DGLUTESS) $(__DGLUDLL) &
	-i=$(WX_BASE)\include -dNOPCH $(__RTTIFLAG_7) $(__EXCEPTIONSFLAG_8) $(CPPFLAGS) &
	$(CXXFLAGS) -hc -fr=$*.err 

CPP_PROJ = $(PROJ_CXXFLAGS)



####################BEGIN MAKEFILE###############################################
#  OpenCPN Specifics
#  Probably do not need modifications in following....
#################################################################################

# Establish variables

#  S57 ENC support

!ifeq USE_S57 1
__DS57 = -dUSE_S57
!else
__DS57 =
!endif


#  Tesselator
!ifeq USE_GLU_TESS 1
__DGLUTESS = -dUSE_GLU_TESS
__DGLUDLL = -dUSE_GLU_DLL
!else
__DGLUTESS =
#GLU_LIB = 
__DGLUDLL = 
!endif


#  Undocumented WIFI client
!if "$(USE_WIFI_CLIENT)" == "1"
__DWIFI = /DUSE_WIFI_CLIENT
!endif
!if "$(USE_WIFI_CLIENT)" == "0"
__DWIFI =
!endif


#  wxWidgets
#!if "$(WX_BUILD_TOOL)" == "MSVC"  
#WX_LIB = $(WX_BASE)\lib\vc_lib
#!endif
#!if "$(WX_BUILD_TOOL)" == "BCC"  
#WX_LIB = $(WX_BASE)\lib\bcc_lib
#!endif

WX_INCLUDE_GENERIC = "$(WX_BASE)\include"
WX_INCLUDE_MSW = $(WX_LIB)

#  GDAL
GDAL_INCLUDE = $(SRC_DIR)\src\mygdal
GDAL_LIB =






#-----------------------------------
#	Debug or release?
#-----------------------------------

!ifeq BUILD debug
# Debug Options

__DDEBUG = /D_DEBUG
OUTDIR=.\debug_
INTDIR=.\debug_
DEBUG_CHAR = d

!ELSE
#   Release 0ptions
OUTDIR=.\release_
INTDIR=.\release_
__DDEBUG = 
DEBUG_CHAR =

!ENDIF



LINK32_OBJS= &
	$(INTDIR)/sercomm.obj &
	$(INTDIR)/latlong.obj &
	$(INTDIR)/concanv.obj &
	$(INTDIR)/routeman.obj &
	$(INTDIR)/options.obj &
	$(INTDIR)/expid.obj &
	$(INTDIR)/chart1.obj &
	$(INTDIR)/talkerid.obj &
	$(INTDIR)/nmea0183.obj &
	$(INTDIR)/georef.obj &
	$(INTDIR)/nmea.obj &
	$(INTDIR)/response.obj &
	$(INTDIR)/long.obj &
	$(INTDIR)/hexvalue.obj &
	$(INTDIR)/thumbwin.obj &
	$(INTDIR)/about.obj &
	$(INTDIR)/rmc.obj &
	$(INTDIR)/navutil.obj &
	$(INTDIR)/sentence.obj &
	$(INTDIR)/ocpn_pixel.obj &
	$(INTDIR)/tcmgr.obj &
	$(INTDIR)/statwin.obj &
	$(INTDIR)/chartdb.obj &
	$(INTDIR)/bbox.obj &
	$(INTDIR)/wvschart.obj &
	$(INTDIR)/ais.obj &
	$(INTDIR)/lat.obj &
	$(INTDIR)/chcanv.obj &
	$(INTDIR)/chartimg.obj &
	$(INTDIR)/rmb.obj &
 	$(INTDIR)/cutil.obj &
	$(INTDIR)/routeprop.obj

ISO8211_OBJS = &
	$(INTDIR)/ddfrecord.obj &
	$(INTDIR)/ddfsubfielddefn.obj &
	$(INTDIR)/ddffielddefn.obj &
	$(INTDIR)/ddffield.obj &
	$(INTDIR)/ddfmodule.obj &
    $(INTDIR)/ddfutils.obj

GDAL_OBJS = &
	$(INTDIR)/gdal_misc.obj &
	$(INTDIR)/cpl_csv.obj &
	$(INTDIR)/cpl_dir.obj &
	$(INTDIR)/cpl_error.obj &
	$(INTDIR)/cpl_findfile.obj &
	$(INTDIR)/cpl_minixml.obj &
	$(INTDIR)/cpl_path.obj &
	$(INTDIR)/cpl_string.obj &
	$(INTDIR)/cpl_vsisimple.obj &
	$(INTDIR)/cpl_conv.obj &
	$(INTDIR)/cplgetsymbol.obj &
	$(INTDIR)/ograssemblepolygon.obj &
	$(INTDIR)/ogrcurve.obj &
	$(INTDIR)/ogrfeature.obj &
	$(INTDIR)/ogrfeaturedefn.obj &
	$(INTDIR)/ogrfielddefn.obj &
	$(INTDIR)/ogrgeometry.obj &
	$(INTDIR)/ogrgeometrycollection.obj &
	$(INTDIR)/ogrgeometryfactory.obj &
	$(INTDIR)/ogrlayer.obj &
	$(INTDIR)/ogrlinearring.obj &
	$(INTDIR)/ogrlinestring.obj &
	$(INTDIR)/ogrmultilinestring.obj &
	$(INTDIR)/ogrmultipoint.obj &
	$(INTDIR)/ogrmultipolygon.obj &
	$(INTDIR)/ogrpoint.obj &
	$(INTDIR)/ogrpolygon.obj &
	$(INTDIR)/ogrs57datasource.obj &
	$(INTDIR)/ogrs57layer.obj &
	$(INTDIR)/ogrutils.obj &
	$(INTDIR)/s57classregistrar.obj &
	$(INTDIR)/s57featuredefns.obj &
	$(INTDIR)/s57reader.obj &
	$(INTDIR)/ddfrecordindex.obj

!ifeq USE_S57 1
S57_OBJS = &
	$(INTDIR)/s57chart.obj &
	$(INTDIR)/s52utils.obj &
	$(INTDIR)/s52plib.obj &
	$(INTDIR)/s52cnsy.obj &
	$(INTDIR)/tri.obj &
	$(INTDIR)/mygeom.obj
!else
S57_OBJS =
!endif


!ifeq USE_WIFI_CLIENT 1
WIFI_OBJS = $(INTDIR)/wificlient.obj
!ELSE
WIFI_OBJS = 
!ENDIF



#  Targets

ALL : .SYMBOLIC $(OUTDIR)\opencpn.exe


$(OUTDIR) :
     -if not exist $(OUTDIR) mkdir $(OUTDIR)

APP_ICON = opencpn.ico
$(INTDIR)\opencpn.res : $(SRC_DIR)\src\bitmaps\$(APP_ICON) $(SRC_DIR)\src\opencpn.rc
	wrc -q -ad -bt=nt -r -fo=$^@   -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) $(__UNICODE_DEFINE_p)  $(__GFXCTX_DEFINE_p) -i=$(SETUPHDIR) -i=$(SRC_DIR)\src\bitmaps -i=. $(__DLLFLAG_p)  $(SRC_DIR)\src\opencpn.rc



$(OUTDIR)\opencpn.exe : $(OUTDIR) $(LINK32_OBJS) $(ISO8211_OBJS) $(GDAL_OBJS) $(WIFI_OBJS) $(S57_OBJS) $(INTDIR)\opencpn.res
	@%create $(OUTDIR)\ocpn.lbc
	@%append $(OUTDIR)\ocpn.lbc option st=1048576
	@%append $(OUTDIR)\ocpn.lbc option quiet
	@%append $(OUTDIR)\ocpn.lbc name $^@
	@%append $(OUTDIR)\ocpn.lbc option caseexact
	@%append $(OUTDIR)\ocpn.lbc $(LDFLAGS) $(__DEBUGINFO_1)  libpath $(LIBDIRNAME) system nt_win ref '_WinMain@16'
	@for %i in ($(LINK32_OBJS)) do @%append $(OUTDIR)\ocpn.lbc file %i
	@for %i in ($(S57_OBJS)) do @%append $(OUTDIR)\ocpn.lbc file %i
	@for %i in ($(GDAL_OBJS)) do @%append $(OUTDIR)\ocpn.lbc file %i
	@for %i in ($(ISO8211_OBJS)) do @%append $(OUTDIR)\ocpn.lbc file %i
	@for %i in ( $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p)  wxzlib$(WXDEBUGFLAG).lib  wxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib $(EXTRALIBS_FOR_BASE)  $(__GDIPLUS_LIB_p) kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib setupapi.lib) do @%append $(OUTDIR)\ocpn.lbc library %i
	@%append $(OUTDIR)\ocpn.lbc option resource=$(OUTDIR)\opencpn.res
	@for %i in () do @%append $(OUTDIR)\ocpn.lbc option stack=%i
	wlink @$(OUTDIR)\ocpn.lbc

install: $(OUTDIR) $(OUTDIR)\opencpn.exe
  -mkdir $(APPDIR)
	cd $(OUTDIR)
	copy opencpn.exe $(APPDIR)
	cd ..
	xcopy /y /r /d /f /s data\*.* $(APPDIR)

CLEAN : .SYMBOLIC
	-if exist $(INTDIR)\*.obj del $(INTDIR)\*.obj
	-if exist $(INTDIR)\*.res del $(INTDIR)\*.res
	-if exist $(INTDIR)\*.lbc del $(INTDIR)\*.lbc
	-if exist $(INTDIR)\*.ilk del $(INTDIR)\*.ilk
	-if exist $(INTDIR)\*.pch del $(INTDIR)\*.pch
	-if exist $(INTDIR)\opencpn.exe del $(INTDIR)\opencpn.exe

	


#CPP_OBJS="$(INTDIR)/

#.c{$(CPP_OBJS)}.obj:
#   $(CPP) $(CPP_PROJ) $<

#.cpp{$(CPP_OBJS)}.obj:
#   $(CPP) $(CPP_PROJ) $<

#.cxx{$(CPP_OBJS)}.obj:
#   $(CPP) $(CPP_PROJ) $<




################################################################################
# Begin Target

# Name opencpn - Win32 Release
################################################################################
# Begin Source File

#SOURCE=$(SRC_DIR)\src\wvschart.cpp
DEP_CPP_WVSCH=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\wvschart.h


$(OUTDIR)/wvschart.obj : $(SRC_DIR)\src\wvschart.cpp $(DEP_CPP_WVSCH)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\wvschart.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\ais.cpp
DEP_CPP_WVSCH=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\ais.h


$(OUTDIR)/ais.obj : $(SRC_DIR)\src\ais.cpp $(DEP_CPP_WVSCH)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\ais.cpp
   
# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\bbox.cpp
DEP_CPP_BBOX=&
	$(SRC_DIR)\include\bbox.h


$(OUTDIR)/bbox.obj : $(SRC_DIR)\src\bbox.cpp  $(DEP_CPP_BBOX)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\bbox.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\ocpn_pixel.cpp
DEP_CPP_BITMA=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\ocpn_pixel.h


$(OUTDIR)/ocpn_pixel.obj : $(SRC_DIR)\src\ocpn_pixel.cpp $(DEP_CPP_BITMA)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\ocpn_pixel.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\chart1.cpp
DEP_CPP_CHART=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\include\options.h&
	$(SRC_DIR)\src\bitmaps\settings.xpm&
	$(SRC_DIR)\src\bitmaps\zoomin.xpm&
	$(SRC_DIR)\src\bitmaps\zoomout.xpm&
	$(SRC_DIR)\src\bitmaps\scin.xpm&
	$(SRC_DIR)\src\bitmaps\scout.xpm&
	$(SRC_DIR)\src\bitmaps\tide.xpm&
	$(SRC_DIR)\src\bitmaps\text.xpm&
	$(SRC_DIR)\src\bitmaps\route.xpm&
	$(SRC_DIR)\src\bitmaps\exitt.xpm&
	$(SRC_DIR)\src\bitmaps\follow.xpm&
	$(SRC_DIR)\src\bitmaps\current.xpm&
	$(SRC_DIR)\src\bitmaps\print.xpm&
	$(SRC_DIR)\src\bitmaps\help.xpm&
	$(SRC_DIR)\src\bitmaps\colscheme.xpm&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.hpp&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\chcanv.h&
	$(SRC_DIR)\include\chartdb.h&
	$(SRC_DIR)\include\navutil.h&
	$(SRC_DIR)\include\routeman.h&
	$(SRC_DIR)\include\statwin.h&
	$(SRC_DIR)\include\concanv.h&
	$(SRC_DIR)\include\nmea.h&
	$(SRC_DIR)\include\about.h&
	$(SRC_DIR)\include\wificlient.h&
	$(SRC_DIR)\include\s52plib.h&
	$(SRC_DIR)\include\thumbwin.h&
	$(SRC_DIR)\include\s57chart.h


$(OUTDIR)/chart1.obj : $(SRC_DIR)\src\chart1.cpp $(DEP_CPP_CHART)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\chart1.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\chartdb.cpp
DEP_CPP_CHARTD=&
	$(SRC_DIR)\include\chartdb.h&
	$(SRC_DIR)\include\chartimg.h&
	$(SRC_DIR)\include\s57chart.h&
	$(SRC_DIR)\include\chart1.h


$(OUTDIR)/chartdb.obj : $(SRC_DIR)\src\chartdb.cpp $(DEP_CPP_CHARTD)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\chartdb.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\chartimg.cpp
DEP_CPP_CHARTI=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\chartimg.h


$(OUTDIR)/chartimg.obj : $(SRC_DIR)\src\chartimg.cpp $(DEP_CPP_CHARTI)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\chartimg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\chcanv.cpp
DEP_CPP_CHCAN=&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\chcanv.h&
	$(SRC_DIR)\include\routeman.h&
	$(SRC_DIR)\include\navutil.h&
	$(SRC_DIR)\include\concanv.h&
	$(SRC_DIR)\include\thumbwin.h&
	$(SRC_DIR)\include\chartdb.h&
	$(SRC_DIR)\include\wvschart.h&
	$(SRC_DIR)\include\georef.h&
	$(SRC_DIR)\include\chartimg.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\s57chart.h&
	$(SRC_DIR)\include\s52plib.h


$(OUTDIR)/chcanv.obj : $(SRC_DIR)\src\chcanv.cpp $(DEP_CPP_CHCAN)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\chcanv.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\concanv.cpp
DEP_CPP_CONCA=&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\concanv.h&
	$(SRC_DIR)\include\routeman.h&
	$(SRC_DIR)\include\navutil.h


$(OUTDIR)/concanv.obj : $(SRC_DIR)\src\concanv.cpp $(DEP_CPP_CONCA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\concanv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\cutil.c
DEP_CPP_CUTIL=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\cutil.h

$(OUTDIR)/cutil.obj : $(SRC_DIR)\src\cutil.c $(DEP_CPP_CUTIL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\cutil.c


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\georef.c
DEP_CPP_GEORE=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\georef.h


$(OUTDIR)/georef.obj : $(SRC_DIR)\src\georef.c $(DEP_CPP_GEORE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\georef.c 


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygeom.cpp
DEP_CPP_MYGEO=&
	$(SRC_DIR)\include\mygeom.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\triangulate.h


$(OUTDIR)/mygeom.obj : $(SRC_DIR)\src\mygeom.cpp $(DEP_CPP_MYGEO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygeom.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\navutil.cpp
DEP_CPP_NAVUT=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\navutil.h&
	$(SRC_DIR)\include\chcanv.h&
	$(SRC_DIR)\include\nmea.h&
	$(SRC_DIR)\include\s52plib.h&
	$(SRC_DIR)\include\georef.h


$(OUTDIR)/navutil.obj : $(SRC_DIR)\src\navutil.cpp $(DEP_CPP_NAVUT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\navutil.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea.cpp
DEP_CPP_NMEA_=&
	$(GDAL_INCLUDE)\cpl_port.h&

NODEP_CPP_NMEA_=&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\nmea.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\sercomm.h


$(OUTDIR)/nmea.obj : $(SRC_DIR)\src\nmea.cpp $(DEP_CPP_NMEA_)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\routeman.cpp
DEP_CPP_ROUTE=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.hpp&
	$(SRC_DIR)\include\sercomm.h&
	$(SRC_DIR)\include\routeman.h&
	$(SRC_DIR)\include\chcanv.h&
	$(SRC_DIR)\include\concanv.h&
	$(SRC_DIR)\include\nmea.h&
	$(SRC_DIR)\include\navutil.h&
	$(SRC_DIR)\include\chartbase.h


$(OUTDIR)/routeman.obj : $(SRC_DIR)\src\routeman.cpp $(DEP_CPP_ROUTE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\routeman.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\s52cnsy.cpp
DEP_CPP_S52CN=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\s57chart.h&
	$(SRC_DIR)\include\s52plib.h&
	$(SRC_DIR)\include\s52utils.h


$(OUTDIR)/s52cnsy.obj : $(SRC_DIR)\src\s52cnsy.cpp $(DEP_CPP_S52CN)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\s52cnsy.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\s52plib.cpp
DEP_CPP_S52PL=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\georef.h&
	$(SRC_DIR)\include\s52plib.h&
	$(SRC_DIR)\include\s57chart.h&
	$(SRC_DIR)\include\mygeom.h


$(OUTDIR)/s52plib.obj : $(SRC_DIR)\src\s52plib.cpp $(DEP_CPP_S52PL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\s52plib.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\s52utils.cpp
DEP_CPP_S52UT=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\s52utils.h


$(OUTDIR)/s52utils.obj : $(SRC_DIR)\src\s52utils.cpp $(DEP_CPP_S52UT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\s52utils.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\s57chart.cpp
DEP_CPP_S57CH=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\s52s57.h&
	$(SRC_DIR)\include\s52plib.h&
	$(SRC_DIR)\include\s57chart.h&
	$(SRC_DIR)\include\nmea.h&
	$(SRC_DIR)\include\mygeom.h&
	$(SRC_DIR)\include\cutil.h


$(OUTDIR)/s57chart.obj : $(SRC_DIR)\src\s57chart.cpp $(DEP_CPP_S57CH)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\s57chart.cpp


# End Source File

################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\sercomm.cpp
DEP_CPP_SERCO=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\sercomm.h


#$(OUTDIR)\sercomm.obj : $(SRC_DIR)\src\ $(DEP_CPP_SERCO) $(OUTDIR)
#.\debug_\sercomm.obj : $(SRC_DIR)\src\sercomm.cpp
#   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $**
#   $(CPP) $(CPP_PROJ) $(SRC_DIR)\src\
#$(OUTDIR)\sercomm.obj : $(SRC_DIR)\src\sercomm.cpp $(DEP_CPP_SERCO)
$(OUTDIR)\sercomm.obj : $(SRC_DIR)\src\sercomm.cpp $(DEP_CPP_SERCO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\sercomm.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\statwin.cpp
DEP_CPP_STATW=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\statwin.h&
	$(SRC_DIR)\include\chartdb.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\chartbase.h


$(OUTDIR)/statwin.obj : $(SRC_DIR)\src\statwin.cpp $(DEP_CPP_STATW)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\statwin.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\tcmgr.cpp
DEP_CPP_TCMGR=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\tcmgr.h


$(OUTDIR)/tcmgr.obj : $(SRC_DIR)\src\tcmgr.cpp $(DEP_CPP_TCMGR)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\tcmgr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\thumbwin.cpp
DEP_CPP_THUMB=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\thumbwin.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\chartdb.h&
	$(SRC_DIR)\include\chcanv.h


$(OUTDIR)/thumbwin.obj : $(SRC_DIR)\src\thumbwin.cpp $(DEP_CPP_THUMB)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\thumbwin.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\tri.c
DEP_CPP_TRI_C=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\triangulate.h


$(OUTDIR)/tri.obj : $(SRC_DIR)\src\tri.c $(DEP_CPP_TRI_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\tri.c


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\wificlient.cpp
DEP_CPP_WIFIC=&
	$(GDAL_INCLUDE)\cpl_port.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\wificlient.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\statwin.h


$(OUTDIR)/wificlient.obj : $(SRC_DIR)\src\wificlient.cpp $(DEP_CPP_WIFIC)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\wificlient.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\about.cpp
NODEP_CPP_ABOUT=&
	$(SRC_DIR)\include\about.h&
	$(SRC_DIR)\include\chart1.h


$(OUTDIR)/about.obj : $(SRC_DIR)\src\about.cpp
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\about.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\routeprop.cpp
DEP_CPP_RTPRO=&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\chcanv.h&
	$(SRC_DIR)\include\routeman.h&
	$(SRC_DIR)\include\navutil.h&
	$(SRC_DIR)\include\georef.h&
	$(SRC_DIR)\include\chart1.h&
	$(SRC_DIR)\include\routeprop.h


$(OUTDIR)/routeprop.obj : $(SRC_DIR)\src\routeprop.cpp $(DEP_CPP_RTPRO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\routeprop.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\myiso8211\ddfutils.cpp
DEP_CPP_DDFUT=&
	$(SRC_DIR)\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddfutils.obj : $(SRC_DIR)\src\myiso8211\ddfutils.cpp $(DEP_CPP_DDFUT)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\myiso8211\ddfutils.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\myiso8211\ddffielddefn.cpp
DEP_CPP_DDFFI=&
	$(SRC_DIR)\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddffielddefn.obj : $(SRC_DIR)\src\myiso8211\ddffielddefn.cpp $(DEP_CPP_DDFFI)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\myiso8211\ddffielddefn.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\myiso8211\ddfmodule.cpp
DEP_CPP_DDFMO=&
	$(SRC_DIR)\src\mygdal\iso8211.h


$(OUTDIR)/ddfmodule.obj : $(SRC_DIR)\src\myiso8211\ddfmodule.cpp $(DEP_CPP_DDFMO)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\myiso8211\ddfmodule.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\myiso8211\ddfrecord.cpp
DEP_CPP_DDFRE=&
	$(SRC_DIR)\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddfrecord.obj : $(SRC_DIR)\src\myiso8211\ddfrecord.cpp $(DEP_CPP_DDFRE)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\myiso8211\ddfrecord.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\myiso8211\ddfsubfielddefn.cpp
DEP_CPP_DDFSU=&
	$(SRC_DIR)\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddfsubfielddefn.obj : $(SRC_DIR)\src\myiso8211\ddfsubfielddefn.cpp $(DEP_CPP_DDFSU)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\myiso8211\ddfsubfielddefn.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\myiso8211\ddffield.cpp
DEP_CPP_DDFFIE=&
	$(SRC_DIR)\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddffield.obj : $(SRC_DIR)\src\myiso8211\ddffield.cpp $(DEP_CPP_DDFFIE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\myiso8211\ddffield.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Ztg.cpp
DEP_CPP_ZTG_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Ztg.obj : $(SRC_DIR)\src\nmea0183\Ztg.cpp $(DEP_CPP_ZTG_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Ztg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Alm.cpp
DEP_CPP_ALM_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Alm.obj : $(SRC_DIR)\src\nmea0183\Alm.cpp $(DEP_CPP_ALM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Alm.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Apb.cpp
DEP_CPP_APB_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Apb.obj : $(SRC_DIR)\src\nmea0183\Apb.cpp $(DEP_CPP_APB_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Apb.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Asd.cpp
DEP_CPP_ASD_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Asd.obj : $(SRC_DIR)\src\nmea0183\Asd.cpp $(DEP_CPP_ASD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Asd.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Bec.cpp
DEP_CPP_BEC_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Bec.obj : $(SRC_DIR)\src\nmea0183\Bec.cpp $(DEP_CPP_BEC_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Bec.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Bod.cpp
DEP_CPP_BOD_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Bod.obj : $(SRC_DIR)\src\nmea0183\Bod.cpp $(DEP_CPP_BOD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Bod.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Bwc.cpp
DEP_CPP_BWC_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Bwc.obj : $(SRC_DIR)\src\nmea0183\Bwc.cpp $(DEP_CPP_BWC_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Bwc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Bwr.cpp
DEP_CPP_BWR_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Bwr.obj : $(SRC_DIR)\src\nmea0183\Bwr.cpp $(DEP_CPP_BWR_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Bwr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Bww.cpp
DEP_CPP_BWW_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Bww.obj : $(SRC_DIR)\src\nmea0183\Bww.cpp $(DEP_CPP_BWW_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Bww.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Checksum.cpp
DEP_CPP_CHECK=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Checksum.obj : $(SRC_DIR)\src\nmea0183\Checksum.cpp $(DEP_CPP_CHECK)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Checksum.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Dbt.cpp
DEP_CPP_DBT_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Dbt.obj : $(SRC_DIR)\src\nmea0183\Dbt.cpp $(DEP_CPP_DBT_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Dbt.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Dcn.cpp
DEP_CPP_DCN_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Dcn.obj : $(SRC_DIR)\src\nmea0183\Dcn.cpp $(DEP_CPP_DCN_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Dcn.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Deccalop.cpp
DEP_CPP_DECCA=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Deccalop.obj : $(SRC_DIR)\src\nmea0183\Deccalop.cpp $(DEP_CPP_DECCA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Deccalop.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Dpt.cpp
DEP_CPP_DPT_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Dpt.obj : $(SRC_DIR)\src\nmea0183\Dpt.cpp $(DEP_CPP_DPT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Dpt.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\expid.cpp
DEP_CPP_EXPID=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/expid.obj : $(SRC_DIR)\src\nmea0183\expid.cpp $(DEP_CPP_EXPID)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\expid.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Field.cpp
DEP_CPP_FIELD=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Field.obj : $(SRC_DIR)\src\nmea0183\Field.cpp $(DEP_CPP_FIELD)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Field.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Freqmode.cpp
DEP_CPP_FREQM=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Freqmode.obj : $(SRC_DIR)\src\nmea0183\Freqmode.cpp $(DEP_CPP_FREQM)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Freqmode.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Fsi.cpp
DEP_CPP_FSI_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Fsi.obj : $(SRC_DIR)\src\nmea0183\Fsi.cpp $(DEP_CPP_FSI_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Fsi.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Gga.cpp
DEP_CPP_GGA_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Gga.obj : $(SRC_DIR)\src\nmea0183\Gga.cpp $(DEP_CPP_GGA_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Gga.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Glc.cpp
DEP_CPP_GLC_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Glc.obj : $(SRC_DIR)\src\nmea0183\Glc.cpp $(DEP_CPP_GLC_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Glc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Gll.cpp
DEP_CPP_GLL_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Gll.obj : $(SRC_DIR)\src\nmea0183\Gll.cpp $(DEP_CPP_GLL_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Gll.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Gxa.cpp
DEP_CPP_GXA_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Gxa.obj : $(SRC_DIR)\src\nmea0183\Gxa.cpp $(DEP_CPP_GXA_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Gxa.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Hdg.cpp
DEP_CPP_HDG_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Hdg.obj : $(SRC_DIR)\src\nmea0183\Hdg.cpp $(DEP_CPP_HDG_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Hdg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Hdt.cpp
DEP_CPP_HDT_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Hdt.obj : $(SRC_DIR)\src\nmea0183\Hdt.cpp $(DEP_CPP_HDT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Hdt.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Hex.cpp
DEP_CPP_HEX_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Hex.obj : $(SRC_DIR)\src\nmea0183\Hex.cpp $(DEP_CPP_HEX_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Hex.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\hexvalue.cpp
DEP_CPP_HEXVA=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/hexvalue.obj : $(SRC_DIR)\src\nmea0183\hexvalue.cpp $(DEP_CPP_HEXVA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\hexvalue.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Hsc.cpp
DEP_CPP_HSC_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Hsc.obj : $(SRC_DIR)\src\nmea0183\Hsc.cpp $(DEP_CPP_HSC_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Hsc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\lat.cpp
DEP_CPP_LAT_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/lat.obj : $(SRC_DIR)\src\nmea0183\lat.cpp $(DEP_CPP_LAT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\lat.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\latlong.cpp
DEP_CPP_LATLO=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/latlong.obj : $(SRC_DIR)\src\nmea0183\latlong.cpp $(DEP_CPP_LATLO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\latlong.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Lcd.cpp
DEP_CPP_LCD_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Lcd.obj : $(SRC_DIR)\src\nmea0183\Lcd.cpp $(DEP_CPP_LCD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Lcd.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\long.cpp
DEP_CPP_LONG_=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/long.obj : $(SRC_DIR)\src\nmea0183\long.cpp $(DEP_CPP_LONG_)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\long.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Lorantd.cpp
DEP_CPP_LORAN=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Lorantd.obj : $(SRC_DIR)\src\nmea0183\Lorantd.cpp $(DEP_CPP_LORAN)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Lorantd.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Manufact.cpp
DEP_CPP_MANUF=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Manufact.obj : $(SRC_DIR)\src\nmea0183\Manufact.cpp $(DEP_CPP_MANUF)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Manufact.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Mlist.cpp
DEP_CPP_MLIST=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Mlist.obj : $(SRC_DIR)\src\nmea0183\Mlist.cpp $(DEP_CPP_MLIST)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Mlist.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Mtw.cpp
DEP_CPP_MTW_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Mtw.obj : $(SRC_DIR)\src\nmea0183\Mtw.cpp $(DEP_CPP_MTW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Mtw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Mwv.cpp
DEP_CPP_MWV_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Mwv.obj : $(SRC_DIR)\src\nmea0183\Mwv.cpp $(DEP_CPP_MWV_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Mwv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\nmea0183.cpp
DEP_CPP_NMEA0=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/nmea0183.obj : $(SRC_DIR)\src\nmea0183\nmea0183.cpp $(DEP_CPP_NMEA0)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\nmea0183.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Oln.cpp
DEP_CPP_OLN_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Oln.obj : $(SRC_DIR)\src\nmea0183\Oln.cpp $(DEP_CPP_OLN_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Oln.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Omegapar.cpp
DEP_CPP_OMEGA=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Omegapar.obj : $(SRC_DIR)\src\nmea0183\Omegapar.cpp $(DEP_CPP_OMEGA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Omegapar.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Osd.cpp
DEP_CPP_OSD_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Osd.obj : $(SRC_DIR)\src\nmea0183\Osd.cpp $(DEP_CPP_OSD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Osd.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\P.cpp
DEP_CPP_P_CPP=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/P.obj : $(SRC_DIR)\src\nmea0183\P.cpp $(DEP_CPP_P_CPP)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\P.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Radardat.cpp
DEP_CPP_RADAR=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Radardat.obj : $(SRC_DIR)\src\nmea0183\Radardat.cpp $(DEP_CPP_RADAR)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Radardat.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Ratiopls.cpp
DEP_CPP_RATIO=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Ratiopls.obj : $(SRC_DIR)\src\nmea0183\Ratiopls.cpp $(DEP_CPP_RATIO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Ratiopls.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\response.cpp
DEP_CPP_RESPO=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/response.obj : $(SRC_DIR)\src\nmea0183\response.cpp $(DEP_CPP_RESPO)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\response.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Rma.cpp
DEP_CPP_RMA_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Rma.obj : $(SRC_DIR)\src\nmea0183\Rma.cpp $(DEP_CPP_RMA_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Rma.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\rmb.cpp
DEP_CPP_RMB_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/rmb.obj : $(SRC_DIR)\src\nmea0183\rmb.cpp $(DEP_CPP_RMB_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\rmb.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\rmc.cpp
DEP_CPP_RMC_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/rmc.obj : $(SRC_DIR)\src\nmea0183\rmc.cpp $(DEP_CPP_RMC_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\rmc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Rot.cpp
DEP_CPP_ROT_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Rot.obj : $(SRC_DIR)\src\nmea0183\Rot.cpp $(DEP_CPP_ROT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Rot.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Rpm.cpp
DEP_CPP_RPM_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Rpm.obj : $(SRC_DIR)\src\nmea0183\Rpm.cpp $(DEP_CPP_RPM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Rpm.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Rsa.cpp
DEP_CPP_RSA_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Rsa.obj : $(SRC_DIR)\src\nmea0183\Rsa.cpp $(DEP_CPP_RSA_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Rsa.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Rsd.cpp
DEP_CPP_RSD_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Rsd.obj : $(SRC_DIR)\src\nmea0183\Rsd.cpp $(DEP_CPP_RSD_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Rsd.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Rte.cpp
DEP_CPP_RTE_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Rte.obj : $(SRC_DIR)\src\nmea0183\Rte.cpp $(DEP_CPP_RTE_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Rte.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\sentence.cpp
DEP_CPP_SENTE=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/sentence.obj : $(SRC_DIR)\src\nmea0183\sentence.cpp $(DEP_CPP_SENTE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\sentence.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Sfi.cpp
DEP_CPP_SFI_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Sfi.obj : $(SRC_DIR)\src\nmea0183\Sfi.cpp $(DEP_CPP_SFI_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Sfi.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Stn.cpp
DEP_CPP_STN_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Stn.obj : $(SRC_DIR)\src\nmea0183\Stn.cpp $(DEP_CPP_STN_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Stn.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\talkerid.cpp
DEP_CPP_TALKE=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/talkerid.obj : $(SRC_DIR)\src\nmea0183\talkerid.cpp $(DEP_CPP_TALKE)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\talkerid.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Test.cpp
DEP_CPP_TEST_=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Test.obj : $(SRC_DIR)\src\nmea0183\Test.cpp $(DEP_CPP_TEST_)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Test.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Trf.cpp
DEP_CPP_TRF_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Trf.obj : $(SRC_DIR)\src\nmea0183\Trf.cpp $(DEP_CPP_TRF_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Trf.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Ttm.cpp
DEP_CPP_TTM_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Ttm.obj : $(SRC_DIR)\src\nmea0183\Ttm.cpp $(DEP_CPP_TTM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Ttm.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Vbw.cpp
DEP_CPP_VBW_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Vbw.obj : $(SRC_DIR)\src\nmea0183\Vbw.cpp $(DEP_CPP_VBW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Vbw.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Vdr.cpp
DEP_CPP_VDR_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Vdr.obj : $(SRC_DIR)\src\nmea0183\Vdr.cpp $(DEP_CPP_VDR_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Vdr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Vhw.cpp
DEP_CPP_VHW_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Vhw.obj : $(SRC_DIR)\src\nmea0183\Vhw.cpp $(DEP_CPP_VHW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Vhw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Vlw.cpp
DEP_CPP_VLW_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Vlw.obj : $(SRC_DIR)\src\nmea0183\Vlw.cpp $(DEP_CPP_VLW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Vlw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Vpw.cpp
DEP_CPP_VPW_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Vpw.obj : $(SRC_DIR)\src\nmea0183\Vpw.cpp $(DEP_CPP_VPW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Vpw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Vtg.cpp
DEP_CPP_VTG_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Vtg.obj : $(SRC_DIR)\src\nmea0183\Vtg.cpp $(DEP_CPP_VTG_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Vtg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Wcv.cpp
DEP_CPP_WCV_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Wcv.obj : $(SRC_DIR)\src\nmea0183\Wcv.cpp $(DEP_CPP_WCV_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Wcv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Wnc.cpp
DEP_CPP_WNC_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Wnc.obj : $(SRC_DIR)\src\nmea0183\Wnc.cpp $(DEP_CPP_WNC_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Wnc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Wpl.cpp
DEP_CPP_WPL_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Wpl.obj : $(SRC_DIR)\src\nmea0183\Wpl.cpp $(DEP_CPP_WPL_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Wpl.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Xdr.cpp
DEP_CPP_XDR_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Xdr.obj : $(SRC_DIR)\src\nmea0183\Xdr.cpp $(DEP_CPP_XDR_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Xdr.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Xte.cpp
DEP_CPP_XTE_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Xte.obj : $(SRC_DIR)\src\nmea0183\Xte.cpp $(DEP_CPP_XTE_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Xte.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Xtr.cpp
DEP_CPP_XTR_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Xtr.obj : $(SRC_DIR)\src\nmea0183\Xtr.cpp $(DEP_CPP_XTR_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Xtr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Zda.cpp
DEP_CPP_ZDA_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP

$(OUTDIR)/Zda.obj : $(SRC_DIR)\src\nmea0183\Zda.cpp $(DEP_CPP_ZDA_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Zda.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Zfo.cpp
DEP_CPP_ZFO_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Zfo.obj : $(SRC_DIR)\src\nmea0183\Zfo.cpp $(DEP_CPP_ZFO_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Zfo.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\nmea0183\Aam.cpp
DEP_CPP_AAM_C=&
	$(SRC_DIR)\src\nmea0183\nmea0183.h&
	$(SRC_DIR)\src\nmea0183\nmea0183.hpp&
	$(SRC_DIR)\src\nmea0183\Sentence.hpp&
	$(SRC_DIR)\src\nmea0183\Response.hpp&
	$(SRC_DIR)\src\nmea0183\LatLong.hpp&
	$(SRC_DIR)\src\nmea0183\RMB.hpp&
	$(SRC_DIR)\src\nmea0183\RMC.HPP


$(OUTDIR)/Aam.obj : $(SRC_DIR)\src\nmea0183\Aam.cpp $(DEP_CPP_AAM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\nmea0183\Aam.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\options.cpp
DEP_CPP_OPTIO=&
	$(SRC_DIR)\include\options.h&
	$(SRC_DIR)\include\dychart.h&
	$(SRC_DIR)\include\navutil.h&
	$(SRC_DIR)\include\s52plib.h

$(OUTDIR)/options.obj : $(SRC_DIR)\src\options.cpp $(DEP_CPP_OPTIO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\options.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_csv.cpp

DEP_CPP_CPL_C=&
	$(SRC_DIR)\src\mygdal\cpl_csv.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h

$(OUTDIR)/cpl_csv.obj : $(SRC_DIR)\src\mygdal\cpl_csv.cpp $(DEP_CPP_CPL_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_csv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\gdal_misc.cpp

DEP_CPP_CPL_D=&
	$(SRC_DIR)\src\mygdal\gdal.h

$(OUTDIR)/gdal_misc.obj : $(SRC_DIR)\src\mygdal\gdal_misc.cpp $(DEP_CPP_CPL_D)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\gdal_misc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_dir.cpp


DEP_CPP_CPL_D=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h


$(OUTDIR)/cpl_dir.obj : $(SRC_DIR)\src\mygdal\cpl_dir.cpp $(DEP_CPP_CPL_D)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_dir.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_error.cpp


DEP_CPP_CPL_E=&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h




$(OUTDIR)/cpl_error.obj : $(SRC_DIR)\src\mygdal\cpl_error.cpp $(DEP_CPP_CPL_E)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_error.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_findfile.cpp


DEP_CPP_CPL_F=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_findfile.obj : $(SRC_DIR)\src\mygdal\cpl_findfile.cpp $(DEP_CPP_CPL_F)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_findfile.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_minixml.cpp


DEP_CPP_CPL_M=&
	$(SRC_DIR)\src\mygdal\cpl_minixml.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h




$(OUTDIR)/cpl_minixml.obj : $(SRC_DIR)\src\mygdal\cpl_minixml.cpp $(DEP_CPP_CPL_M)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_minixml.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_path.cpp


DEP_CPP_CPL_P=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_path.obj : $(SRC_DIR)\src\mygdal\cpl_path.cpp $(DEP_CPP_CPL_P)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_path.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_string.cpp

DEP_CPP_CPL_S=&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_string.obj : $(SRC_DIR)\src\mygdal\cpl_string.cpp $(DEP_CPP_CPL_S)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_string.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_vsisimple.cpp


DEP_CPP_CPL_V=&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h




$(OUTDIR)/cpl_vsisimple.obj : $(SRC_DIR)\src\mygdal\cpl_vsisimple.cpp $(DEP_CPP_CPL_V)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_vsisimple.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cplgetsymbol.cpp

DEP_CPP_CPLGE=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h





$(OUTDIR)/cplgetsymbol.obj : $(SRC_DIR)\src\mygdal\cplgetsymbol.cpp $(DEP_CPP_CPLGE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cplgetsymbol.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ograssemblepolygon.cpp


DEP_CPP_OGRAS=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ograssemblepolygon.obj : $(SRC_DIR)\src\mygdal\ograssemblepolygon.cpp $(DEP_CPP_OGRAS)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ograssemblepolygon.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrcurve.cpp


DEP_CPP_OGRCU=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrcurve.obj : $(SRC_DIR)\src\mygdal\ogrcurve.cpp $(DEP_CPP_OGRCU)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrcurve.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrfeature.cpp

DEP_CPP_OGRFE=&
	$(SRC_DIR)\src\mygdal\ogr_feature.h&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrfeature.obj : $(SRC_DIR)\src\mygdal\ogrfeature.cpp $(DEP_CPP_OGRFE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrfeature.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrfeaturedefn.cpp


DEP_CPP_OGRFEA=&
	$(SRC_DIR)\src\mygdal\ogr_feature.h&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrfeaturedefn.obj : $(SRC_DIR)\src\mygdal\ogrfeaturedefn.cpp $(DEP_CPP_OGRFEA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrfeaturedefn.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrfielddefn.cpp


DEP_CPP_OGRFI=&
	$(SRC_DIR)\src\mygdal\ogr_feature.h&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrfielddefn.obj : $(SRC_DIR)\src\mygdal\ogrfielddefn.cpp $(DEP_CPP_OGRFI)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrfielddefn.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrgeometry.cpp

DEP_CPP_OGRGE=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrgeometry.obj : $(SRC_DIR)\src\mygdal\ogrgeometry.cpp $(DEP_CPP_OGRGE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrgeometry.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrgeometrycollection.cpp

DEP_CPP_OGRGEO=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrgeometrycollection.obj : $(SRC_DIR)\src\mygdal\ogrgeometrycollection.cpp $(DEP_CPP_OGRGEO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrgeometrycollection.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrgeometryfactory.cpp


DEP_CPP_OGRGEOM=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrgeometryfactory.obj : $(SRC_DIR)\src\mygdal\ogrgeometryfactory.cpp $(DEP_CPP_OGRGEOM)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrgeometryfactory.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrlayer.cpp


DEP_CPP_OGRLA=&
	$(SRC_DIR)\src\mygdal\ogrsf_frmts.h&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_attrind.h&
	$(SRC_DIR)\src\mygdal\ogr_feature.h&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrlayer.obj : $(SRC_DIR)\src\mygdal\ogrlayer.cpp $(DEP_CPP_OGRLA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrlayer.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrlinearring.cpp


DEP_CPP_OGRLI=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrlinearring.obj : $(SRC_DIR)\src\mygdal\ogrlinearring.cpp $(DEP_CPP_OGRLI)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrlinearring.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrlinestring.cpp

DEP_CPP_OGRLIN=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrlinestring.obj : $(SRC_DIR)\src\mygdal\ogrlinestring.cpp $(DEP_CPP_OGRLIN)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrlinestring.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrmultilinestring.cpp

DEP_CPP_OGRMU=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrmultilinestring.obj : $(SRC_DIR)\src\mygdal\ogrmultilinestring.cpp $(DEP_CPP_OGRMU)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrmultilinestring.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrmultipoint.cpp


DEP_CPP_OGRMUL=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrmultipoint.obj : $(SRC_DIR)\src\mygdal\ogrmultipoint.cpp $(DEP_CPP_OGRMUL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrmultipoint.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrmultipolygon.cpp


DEP_CPP_OGRMULT=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrmultipolygon.obj : $(SRC_DIR)\src\mygdal\ogrmultipolygon.cpp $(DEP_CPP_OGRMULT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrmultipolygon.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrpoint.cpp


DEP_CPP_OGRPO=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrpoint.obj : $(SRC_DIR)\src\mygdal\ogrpoint.cpp $(DEP_CPP_OGRPO)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrpoint.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrpolygon.cpp


DEP_CPP_OGRPOL=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrpolygon.obj : $(SRC_DIR)\src\mygdal\ogrpolygon.cpp $(DEP_CPP_OGRPOL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrpolygon.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrs57datasource.cpp


DEP_CPP_OGRS5=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\ogr_s57.h


$(OUTDIR)/ogrs57datasource.obj : $(SRC_DIR)\src\mygdal\ogrs57datasource.cpp $(DEP_CPP_OGRS5)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrs57datasource.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrs57layer.cpp


DEP_CPP_OGRS57L=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\ogr_s57.h


$(OUTDIR)/ogrs57layer.obj : $(SRC_DIR)\src\mygdal\ogrs57layer.cpp $(DEP_CPP_OGRS57L)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrs57layer.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ogrutils.cpp


DEP_CPP_OGRUT=&
	$(SRC_DIR)\src\mygdal\ogr_geometry.h&
	$(SRC_DIR)\src\mygdal\ogr_p.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\ogr_spatialref.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h




$(OUTDIR)/ogrutils.obj : $(SRC_DIR)\src\mygdal\ogrutils.cpp $(DEP_CPP_OGRUT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ogrutils.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\s57classregistrar.cpp

DEP_CPP_S57CL=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\s57.h


$(OUTDIR)/s57classregistrar.obj : $(SRC_DIR)\src\mygdal\s57classregistrar.cpp $(DEP_CPP_S57CL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\s57classregistrar.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\s57featuredefns.cpp


DEP_CPP_S57FE=&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\s57.h


$(OUTDIR)/s57featuredefns.obj : $(SRC_DIR)\src\mygdal\s57featuredefns.cpp $(DEP_CPP_S57FE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\s57featuredefns.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\s57reader.cpp


DEP_CPP_S57RE=&
	$(SRC_DIR)\src\mygdal\ogr_api.h&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\ogr_core.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\s57.h


$(OUTDIR)/s57reader.obj : $(SRC_DIR)\src\mygdal\s57reader.cpp $(DEP_CPP_S57RE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\s57reader.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\cpl_conv.cpp

DEP_CPP_CPL_CO=&
	$(SRC_DIR)\src\mygdal\cpl_conv.h&
	$(SRC_DIR)\src\mygdal\cpl_string.h&
	$(SRC_DIR)\src\mygdal\cpl_port.h&
	$(SRC_DIR)\src\mygdal\cpl_vsi.h&
	$(SRC_DIR)\src\mygdal\cpl_error.h&
	$(SRC_DIR)\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_conv.obj : $(SRC_DIR)\src\mygdal\cpl_conv.cpp $(DEP_CPP_CPL_CO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\cpl_conv.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=$(SRC_DIR)\src\mygdal\ddfrecordindex.cpp
DEP_CPP_DDFR2=&


$(OUTDIR)/ddfrecordindex.obj : $(SRC_DIR)\src\mygdal\ddfrecordindex.cpp $(DEP_CPP_DDFR2)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $(SRC_DIR)\src\mygdal\ddfrecordindex.cpp


# End Source File
# End Target
# End Project
################################################################################






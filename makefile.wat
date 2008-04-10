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

WX_RELEASE_NODOT = 28
OBJS = &
	wat_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WXDLLFLAG)$(CFG)
LIBDIRNAME = $(WX_BASE)\lib\wat_$(LIBTYPE_SUFFIX)$(CFG)
SETUPHDIR = &
	$(LIBDIRNAME)\$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)
	
PROJ_CXXFLAGS = $(__DEBUGINFO_0) $(__OPTIMIZEFLAG_2) $(__THREADSFLAG_5) &
	$(__RUNTIME_LIBS_6) -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) &
	$(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) &
	$(__UNICODE_DEFINE_p) $(__GFXCTX_DEFINE_p) -i=$(SETUPHDIR) &
	-i=.\include -wx -wcd=549 -wcd=656 -wcd=657 -wcd=667 -i=. $(__DLLFLAG_p) &
	-wcd=726 -wcd=389 -wcd=716 -wcd=391 &
	-i=$(GDAL_INCLUDE) $(__DS57) $(__DGLUTESS) $(__DGLUDLL) &
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
GDAL_INCLUDE = .\src\mygdal
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
$(INTDIR)\opencpn.res : .\src\bitmaps\$(APP_ICON) .\src\opencpn.rc
	wrc -q -ad -bt=nt -r -fo=$^@   -d__WXMSW__ $(__WXUNIV_DEFINE_p) $(__DEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) $(__THREAD_DEFINE_p) $(__UNICODE_DEFINE_p)  $(__GFXCTX_DEFINE_p) -i=$(SETUPHDIR) -i=.\src\bitmaps -i=. $(__DLLFLAG_p)  .\src\opencpn.rc



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
	@for %i in ( $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p)  wxzlib$(WXDEBUGFLAG).lib  wxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG).lib wxexpat$(WXDEBUGFLAG).lib $(EXTRALIBS_FOR_BASE)  $(__GDIPLUS_LIB_p) kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append $(OUTDIR)\ocpn.lbc library %i
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

#SOURCE=.\src\wvschart.cpp
DEP_CPP_WVSCH=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\wvschart.h


$(OUTDIR)/wvschart.obj : .\src\wvschart.cpp $(DEP_CPP_WVSCH)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\wvschart.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\ais.cpp
DEP_CPP_WVSCH=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\ais.h


$(OUTDIR)/ais.obj : .\src\ais.cpp $(DEP_CPP_WVSCH)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\ais.cpp
   
# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\bbox.cpp
DEP_CPP_BBOX=&
	.\include\bbox.h


$(OUTDIR)/bbox.obj : .\src\bbox.cpp  $(DEP_CPP_BBOX)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\bbox.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\ocpn_pixel.cpp
DEP_CPP_BITMA=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\ocpn_pixel.h


$(OUTDIR)/ocpn_pixel.obj : .\src\ocpn_pixel.cpp $(DEP_CPP_BITMA)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\ocpn_pixel.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chart1.cpp
DEP_CPP_CHART=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\src\nmea0183\nmea0183.h&
	.\include\options.h&
	.\src\bitmaps\settings.xpm&
	.\src\bitmaps\zoomin.xpm&
	.\src\bitmaps\zoomout.xpm&
	.\src\bitmaps\scin.xpm&
	.\src\bitmaps\scout.xpm&
	.\src\bitmaps\tide.xpm&
	.\src\bitmaps\text.xpm&
	.\src\bitmaps\route.xpm&
	.\src\bitmaps\exitt.xpm&
	.\src\bitmaps\follow.xpm&
	.\src\bitmaps\current.xpm&
	.\src\bitmaps\print.xpm&
	.\src\bitmaps\help.xpm&
	.\src\bitmaps\colscheme.xpm&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.hpp&
	.\include\dychart.h&
	.\include\chart1.h&
	.\include\chcanv.h&
	.\include\chartdb.h&
	.\include\navutil.h&
	.\include\routeman.h&
	.\include\statwin.h&
	.\include\concanv.h&
	.\include\nmea.h&
	.\include\about.h&
	.\include\wificlient.h&
	.\include\s52plib.h&
	.\include\thumbwin.h&
	.\include\s57chart.h


$(OUTDIR)/chart1.obj : .\src\chart1.cpp $(DEP_CPP_CHART)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\chart1.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chartdb.cpp
DEP_CPP_CHARTD=&
	.\include\chartdb.h&
	.\include\chartimg.h&
	.\include\s57chart.h&
	.\include\chart1.h


$(OUTDIR)/chartdb.obj : .\src\chartdb.cpp $(DEP_CPP_CHARTD)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\chartdb.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chartimg.cpp
DEP_CPP_CHARTI=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\chartimg.h


$(OUTDIR)/chartimg.obj : .\src\chartimg.cpp $(DEP_CPP_CHARTI)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\chartimg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chcanv.cpp
DEP_CPP_CHCAN=&
	.\include\dychart.h&
	.\include\chcanv.h&
	.\include\routeman.h&
	.\include\navutil.h&
	.\include\concanv.h&
	.\include\thumbwin.h&
	.\include\chartdb.h&
	.\include\wvschart.h&
	.\include\georef.h&
	.\include\chartimg.h&
	.\include\chart1.h&
	.\include\s57chart.h&
	.\include\s52plib.h


$(OUTDIR)/chcanv.obj : .\src\chcanv.cpp $(DEP_CPP_CHCAN)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\chcanv.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\concanv.cpp
DEP_CPP_CONCA=&
	.\include\dychart.h&
	.\include\chart1.h&
	.\include\concanv.h&
	.\include\routeman.h&
	.\include\navutil.h


$(OUTDIR)/concanv.obj : .\src\concanv.cpp $(DEP_CPP_CONCA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\concanv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\cutil.c
DEP_CPP_CUTIL=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\cutil.h

$(OUTDIR)/cutil.obj : .\src\cutil.c $(DEP_CPP_CUTIL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\cutil.c


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\georef.c
DEP_CPP_GEORE=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\georef.h


$(OUTDIR)/georef.obj : .\src\georef.c $(DEP_CPP_GEORE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\georef.c 


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygeom.cpp
DEP_CPP_MYGEO=&
	.\include\mygeom.h&
	.\include\dychart.h&
	.\include\triangulate.h


$(OUTDIR)/mygeom.obj : .\src\mygeom.cpp $(DEP_CPP_MYGEO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygeom.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\navutil.cpp
DEP_CPP_NAVUT=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\chart1.h&
	.\include\navutil.h&
	.\include\chcanv.h&
	.\include\nmea.h&
	.\include\s52plib.h&
	.\include\georef.h


$(OUTDIR)/navutil.obj : .\src\navutil.cpp $(DEP_CPP_NAVUT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\navutil.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea.cpp
DEP_CPP_NMEA_=&
	$(GDAL_INCLUDE)\cpl_port.h&

NODEP_CPP_NMEA_=&
	.\include\dychart.h&
	.\include\nmea.h&
	.\include\chart1.h&
	.\include\sercomm.h


$(OUTDIR)/nmea.obj : .\src\nmea.cpp $(DEP_CPP_NMEA_)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\routeman.cpp
DEP_CPP_ROUTE=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.hpp&
	.\include\sercomm.h&
	.\include\routeman.h&
	.\include\chcanv.h&
	.\include\concanv.h&
	.\include\nmea.h&
	.\include\navutil.h&
	.\include\chartbase.h


$(OUTDIR)/routeman.obj : .\src\routeman.cpp $(DEP_CPP_ROUTE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\routeman.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s52cnsy.cpp
DEP_CPP_S52CN=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\s57chart.h&
	.\include\s52plib.h&
	.\include\s52utils.h


$(OUTDIR)/s52cnsy.obj : .\src\s52cnsy.cpp $(DEP_CPP_S52CN)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\s52cnsy.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s52plib.cpp
DEP_CPP_S52PL=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\georef.h&
	.\include\s52plib.h&
	.\include\s57chart.h&
	.\include\mygeom.h


$(OUTDIR)/s52plib.obj : .\src\s52plib.cpp $(DEP_CPP_S52PL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\s52plib.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s52utils.cpp
DEP_CPP_S52UT=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\s52utils.h


$(OUTDIR)/s52utils.obj : .\src\s52utils.cpp $(DEP_CPP_S52UT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\s52utils.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s57chart.cpp
DEP_CPP_S57CH=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\s52s57.h&
	.\include\s52plib.h&
	.\include\s57chart.h&
	.\include\nmea.h&
	.\include\mygeom.h&
	.\include\cutil.h


$(OUTDIR)/s57chart.obj : .\src\s57chart.cpp $(DEP_CPP_S57CH)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\s57chart.cpp


# End Source File

################################################################################
# Begin Source File

SOURCE=.\src\sercomm.cpp
DEP_CPP_SERCO=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\sercomm.h


#$(OUTDIR)\sercomm.obj : .\src\ $(DEP_CPP_SERCO) $(OUTDIR)
#.\debug_\sercomm.obj : .\src\sercomm.cpp
#   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) $**
#   $(CPP) $(CPP_PROJ) .\src\
#$(OUTDIR)\sercomm.obj : .\src\sercomm.cpp $(DEP_CPP_SERCO)
$(OUTDIR)\sercomm.obj : .\src\sercomm.cpp $(DEP_CPP_SERCO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\sercomm.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\statwin.cpp
DEP_CPP_STATW=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\statwin.h&
	.\include\chartdb.h&
	.\include\chart1.h&
	.\include\chartbase.h


$(OUTDIR)/statwin.obj : .\src\statwin.cpp $(DEP_CPP_STATW)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\statwin.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\tcmgr.cpp
DEP_CPP_TCMGR=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\tcmgr.h


$(OUTDIR)/tcmgr.obj : .\src\tcmgr.cpp $(DEP_CPP_TCMGR)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\tcmgr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\thumbwin.cpp
DEP_CPP_THUMB=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\thumbwin.h&
	.\include\chart1.h&
	.\include\chartdb.h&
	.\include\chcanv.h


$(OUTDIR)/thumbwin.obj : .\src\thumbwin.cpp $(DEP_CPP_THUMB)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\thumbwin.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\tri.c
DEP_CPP_TRI_C=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\triangulate.h


$(OUTDIR)/tri.obj : .\src\tri.c $(DEP_CPP_TRI_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\tri.c


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\wificlient.cpp
DEP_CPP_WIFIC=&
	$(GDAL_INCLUDE)\cpl_port.h&
	.\include\dychart.h&
	.\include\wificlient.h&
	.\include\chart1.h&
	.\include\statwin.h


$(OUTDIR)/wificlient.obj : .\src\wificlient.cpp $(DEP_CPP_WIFIC)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\wificlient.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\about.cpp
NODEP_CPP_ABOUT=&
	.\include\about.h&
	.\include\chart1.h


$(OUTDIR)/about.obj : .\src\about.cpp
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\about.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\routeprop.cpp
DEP_CPP_RTPRO=&
	.\include\dychart.h&
	.\include\chcanv.h&
	.\include\routeman.h&
	.\include\navutil.h&
	.\include\georef.h&
	.\include\chart1.h&
	.\include\routeprop.h


$(OUTDIR)/routeprop.obj : .\src\routeprop.cpp $(DEP_CPP_RTPRO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\routeprop.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfutils.cpp
DEP_CPP_DDFUT=&
	.\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddfutils.obj : .\src\myiso8211\ddfutils.cpp $(DEP_CPP_DDFUT)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\myiso8211\ddfutils.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddffielddefn.cpp
DEP_CPP_DDFFI=&
	.\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddffielddefn.obj : .\src\myiso8211\ddffielddefn.cpp $(DEP_CPP_DDFFI)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\myiso8211\ddffielddefn.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfmodule.cpp
DEP_CPP_DDFMO=&
	.\src\mygdal\iso8211.h


$(OUTDIR)/ddfmodule.obj : .\src\myiso8211\ddfmodule.cpp $(DEP_CPP_DDFMO)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\myiso8211\ddfmodule.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfrecord.cpp
DEP_CPP_DDFRE=&
	.\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddfrecord.obj : .\src\myiso8211\ddfrecord.cpp $(DEP_CPP_DDFRE)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\myiso8211\ddfrecord.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfsubfielddefn.cpp
DEP_CPP_DDFSU=&
	.\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddfsubfielddefn.obj : .\src\myiso8211\ddfsubfielddefn.cpp $(DEP_CPP_DDFSU)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\myiso8211\ddfsubfielddefn.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddffield.cpp
DEP_CPP_DDFFIE=&
	.\src\mygdal\iso8211.h&
	$(GDAL_INCLUDE)\cpl_port.h


$(OUTDIR)/ddffield.obj : .\src\myiso8211\ddffield.cpp $(DEP_CPP_DDFFIE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\myiso8211\ddffield.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Ztg.cpp
DEP_CPP_ZTG_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Ztg.obj : .\src\nmea0183\Ztg.cpp $(DEP_CPP_ZTG_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Ztg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Alm.cpp
DEP_CPP_ALM_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Alm.obj : .\src\nmea0183\Alm.cpp $(DEP_CPP_ALM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Alm.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Apb.cpp
DEP_CPP_APB_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Apb.obj : .\src\nmea0183\Apb.cpp $(DEP_CPP_APB_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Apb.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Asd.cpp
DEP_CPP_ASD_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Asd.obj : .\src\nmea0183\Asd.cpp $(DEP_CPP_ASD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Asd.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Bec.cpp
DEP_CPP_BEC_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Bec.obj : .\src\nmea0183\Bec.cpp $(DEP_CPP_BEC_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Bec.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Bod.cpp
DEP_CPP_BOD_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Bod.obj : .\src\nmea0183\Bod.cpp $(DEP_CPP_BOD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Bod.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Bwc.cpp
DEP_CPP_BWC_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Bwc.obj : .\src\nmea0183\Bwc.cpp $(DEP_CPP_BWC_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Bwc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Bwr.cpp
DEP_CPP_BWR_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Bwr.obj : .\src\nmea0183\Bwr.cpp $(DEP_CPP_BWR_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Bwr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Bww.cpp
DEP_CPP_BWW_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Bww.obj : .\src\nmea0183\Bww.cpp $(DEP_CPP_BWW_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Bww.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Checksum.cpp
DEP_CPP_CHECK=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Checksum.obj : .\src\nmea0183\Checksum.cpp $(DEP_CPP_CHECK)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Checksum.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Dbt.cpp
DEP_CPP_DBT_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Dbt.obj : .\src\nmea0183\Dbt.cpp $(DEP_CPP_DBT_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Dbt.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Dcn.cpp
DEP_CPP_DCN_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Dcn.obj : .\src\nmea0183\Dcn.cpp $(DEP_CPP_DCN_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Dcn.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Deccalop.cpp
DEP_CPP_DECCA=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Deccalop.obj : .\src\nmea0183\Deccalop.cpp $(DEP_CPP_DECCA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Deccalop.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Dpt.cpp
DEP_CPP_DPT_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Dpt.obj : .\src\nmea0183\Dpt.cpp $(DEP_CPP_DPT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Dpt.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\expid.cpp
DEP_CPP_EXPID=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/expid.obj : .\src\nmea0183\expid.cpp $(DEP_CPP_EXPID)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\expid.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Field.cpp
DEP_CPP_FIELD=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Field.obj : .\src\nmea0183\Field.cpp $(DEP_CPP_FIELD)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Field.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Freqmode.cpp
DEP_CPP_FREQM=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Freqmode.obj : .\src\nmea0183\Freqmode.cpp $(DEP_CPP_FREQM)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Freqmode.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Fsi.cpp
DEP_CPP_FSI_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Fsi.obj : .\src\nmea0183\Fsi.cpp $(DEP_CPP_FSI_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Fsi.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Gga.cpp
DEP_CPP_GGA_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Gga.obj : .\src\nmea0183\Gga.cpp $(DEP_CPP_GGA_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Gga.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Glc.cpp
DEP_CPP_GLC_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Glc.obj : .\src\nmea0183\Glc.cpp $(DEP_CPP_GLC_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Glc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Gll.cpp
DEP_CPP_GLL_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Gll.obj : .\src\nmea0183\Gll.cpp $(DEP_CPP_GLL_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Gll.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Gxa.cpp
DEP_CPP_GXA_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Gxa.obj : .\src\nmea0183\Gxa.cpp $(DEP_CPP_GXA_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Gxa.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Hdg.cpp
DEP_CPP_HDG_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Hdg.obj : .\src\nmea0183\Hdg.cpp $(DEP_CPP_HDG_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Hdg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Hdt.cpp
DEP_CPP_HDT_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Hdt.obj : .\src\nmea0183\Hdt.cpp $(DEP_CPP_HDT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Hdt.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Hex.cpp
DEP_CPP_HEX_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Hex.obj : .\src\nmea0183\Hex.cpp $(DEP_CPP_HEX_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Hex.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\hexvalue.cpp
DEP_CPP_HEXVA=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/hexvalue.obj : .\src\nmea0183\hexvalue.cpp $(DEP_CPP_HEXVA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\hexvalue.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Hsc.cpp
DEP_CPP_HSC_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Hsc.obj : .\src\nmea0183\Hsc.cpp $(DEP_CPP_HSC_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Hsc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\lat.cpp
DEP_CPP_LAT_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/lat.obj : .\src\nmea0183\lat.cpp $(DEP_CPP_LAT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\lat.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\latlong.cpp
DEP_CPP_LATLO=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/latlong.obj : .\src\nmea0183\latlong.cpp $(DEP_CPP_LATLO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\latlong.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Lcd.cpp
DEP_CPP_LCD_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Lcd.obj : .\src\nmea0183\Lcd.cpp $(DEP_CPP_LCD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Lcd.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\long.cpp
DEP_CPP_LONG_=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/long.obj : .\src\nmea0183\long.cpp $(DEP_CPP_LONG_)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\long.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Lorantd.cpp
DEP_CPP_LORAN=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Lorantd.obj : .\src\nmea0183\Lorantd.cpp $(DEP_CPP_LORAN)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Lorantd.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Manufact.cpp
DEP_CPP_MANUF=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Manufact.obj : .\src\nmea0183\Manufact.cpp $(DEP_CPP_MANUF)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Manufact.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Mlist.cpp
DEP_CPP_MLIST=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Mlist.obj : .\src\nmea0183\Mlist.cpp $(DEP_CPP_MLIST)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Mlist.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Mtw.cpp
DEP_CPP_MTW_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Mtw.obj : .\src\nmea0183\Mtw.cpp $(DEP_CPP_MTW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Mtw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Mwv.cpp
DEP_CPP_MWV_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Mwv.obj : .\src\nmea0183\Mwv.cpp $(DEP_CPP_MWV_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Mwv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\nmea0183.cpp
DEP_CPP_NMEA0=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/nmea0183.obj : .\src\nmea0183\nmea0183.cpp $(DEP_CPP_NMEA0)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\nmea0183.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Oln.cpp
DEP_CPP_OLN_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Oln.obj : .\src\nmea0183\Oln.cpp $(DEP_CPP_OLN_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Oln.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Omegapar.cpp
DEP_CPP_OMEGA=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Omegapar.obj : .\src\nmea0183\Omegapar.cpp $(DEP_CPP_OMEGA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Omegapar.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Osd.cpp
DEP_CPP_OSD_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Osd.obj : .\src\nmea0183\Osd.cpp $(DEP_CPP_OSD_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Osd.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\P.cpp
DEP_CPP_P_CPP=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/P.obj : .\src\nmea0183\P.cpp $(DEP_CPP_P_CPP)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\P.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Radardat.cpp
DEP_CPP_RADAR=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Radardat.obj : .\src\nmea0183\Radardat.cpp $(DEP_CPP_RADAR)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Radardat.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Ratiopls.cpp
DEP_CPP_RATIO=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Ratiopls.obj : .\src\nmea0183\Ratiopls.cpp $(DEP_CPP_RATIO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Ratiopls.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\response.cpp
DEP_CPP_RESPO=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/response.obj : .\src\nmea0183\response.cpp $(DEP_CPP_RESPO)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\response.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Rma.cpp
DEP_CPP_RMA_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Rma.obj : .\src\nmea0183\Rma.cpp $(DEP_CPP_RMA_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Rma.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\rmb.cpp
DEP_CPP_RMB_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/rmb.obj : .\src\nmea0183\rmb.cpp $(DEP_CPP_RMB_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\rmb.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\rmc.cpp
DEP_CPP_RMC_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/rmc.obj : .\src\nmea0183\rmc.cpp $(DEP_CPP_RMC_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\rmc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Rot.cpp
DEP_CPP_ROT_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Rot.obj : .\src\nmea0183\Rot.cpp $(DEP_CPP_ROT_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Rot.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Rpm.cpp
DEP_CPP_RPM_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Rpm.obj : .\src\nmea0183\Rpm.cpp $(DEP_CPP_RPM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Rpm.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Rsa.cpp
DEP_CPP_RSA_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Rsa.obj : .\src\nmea0183\Rsa.cpp $(DEP_CPP_RSA_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Rsa.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Rsd.cpp
DEP_CPP_RSD_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Rsd.obj : .\src\nmea0183\Rsd.cpp $(DEP_CPP_RSD_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Rsd.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Rte.cpp
DEP_CPP_RTE_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Rte.obj : .\src\nmea0183\Rte.cpp $(DEP_CPP_RTE_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Rte.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\sentence.cpp
DEP_CPP_SENTE=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/sentence.obj : .\src\nmea0183\sentence.cpp $(DEP_CPP_SENTE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\sentence.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Sfi.cpp
DEP_CPP_SFI_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Sfi.obj : .\src\nmea0183\Sfi.cpp $(DEP_CPP_SFI_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Sfi.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Stn.cpp
DEP_CPP_STN_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Stn.obj : .\src\nmea0183\Stn.cpp $(DEP_CPP_STN_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Stn.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\talkerid.cpp
DEP_CPP_TALKE=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/talkerid.obj : .\src\nmea0183\talkerid.cpp $(DEP_CPP_TALKE)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\talkerid.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Test.cpp
DEP_CPP_TEST_=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Test.obj : .\src\nmea0183\Test.cpp $(DEP_CPP_TEST_)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Test.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Trf.cpp
DEP_CPP_TRF_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Trf.obj : .\src\nmea0183\Trf.cpp $(DEP_CPP_TRF_C)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Trf.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Ttm.cpp
DEP_CPP_TTM_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Ttm.obj : .\src\nmea0183\Ttm.cpp $(DEP_CPP_TTM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Ttm.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Vbw.cpp
DEP_CPP_VBW_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Vbw.obj : .\src\nmea0183\Vbw.cpp $(DEP_CPP_VBW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Vbw.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Vdr.cpp
DEP_CPP_VDR_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Vdr.obj : .\src\nmea0183\Vdr.cpp $(DEP_CPP_VDR_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Vdr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Vhw.cpp
DEP_CPP_VHW_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Vhw.obj : .\src\nmea0183\Vhw.cpp $(DEP_CPP_VHW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Vhw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Vlw.cpp
DEP_CPP_VLW_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Vlw.obj : .\src\nmea0183\Vlw.cpp $(DEP_CPP_VLW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Vlw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Vpw.cpp
DEP_CPP_VPW_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Vpw.obj : .\src\nmea0183\Vpw.cpp $(DEP_CPP_VPW_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Vpw.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Vtg.cpp
DEP_CPP_VTG_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Vtg.obj : .\src\nmea0183\Vtg.cpp $(DEP_CPP_VTG_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Vtg.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Wcv.cpp
DEP_CPP_WCV_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Wcv.obj : .\src\nmea0183\Wcv.cpp $(DEP_CPP_WCV_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Wcv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Wnc.cpp
DEP_CPP_WNC_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Wnc.obj : .\src\nmea0183\Wnc.cpp $(DEP_CPP_WNC_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Wnc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Wpl.cpp
DEP_CPP_WPL_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Wpl.obj : .\src\nmea0183\Wpl.cpp $(DEP_CPP_WPL_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Wpl.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Xdr.cpp
DEP_CPP_XDR_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Xdr.obj : .\src\nmea0183\Xdr.cpp $(DEP_CPP_XDR_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Xdr.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Xte.cpp
DEP_CPP_XTE_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Xte.obj : .\src\nmea0183\Xte.cpp $(DEP_CPP_XTE_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Xte.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Xtr.cpp
DEP_CPP_XTR_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Xtr.obj : .\src\nmea0183\Xtr.cpp $(DEP_CPP_XTR_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Xtr.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Zda.cpp
DEP_CPP_ZDA_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP

$(OUTDIR)/Zda.obj : .\src\nmea0183\Zda.cpp $(DEP_CPP_ZDA_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Zda.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Zfo.cpp
DEP_CPP_ZFO_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Zfo.obj : .\src\nmea0183\Zfo.cpp $(DEP_CPP_ZFO_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Zfo.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Aam.cpp
DEP_CPP_AAM_C=&
	.\src\nmea0183\nmea0183.h&
	.\src\nmea0183\nmea0183.hpp&
	.\src\nmea0183\Sentence.hpp&
	.\src\nmea0183\Response.hpp&
	.\src\nmea0183\LatLong.hpp&
	.\src\nmea0183\RMB.hpp&
	.\src\nmea0183\RMC.HPP


$(OUTDIR)/Aam.obj : .\src\nmea0183\Aam.cpp $(DEP_CPP_AAM_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\nmea0183\Aam.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\options.cpp
DEP_CPP_OPTIO=&
	.\include\options.h&
	.\include\dychart.h&
	.\include\navutil.h&
	.\include\s52plib.h

$(OUTDIR)/options.obj : .\src\options.cpp $(DEP_CPP_OPTIO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\options.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_csv.cpp

DEP_CPP_CPL_C=&
	.\src\mygdal\cpl_csv.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h

$(OUTDIR)/cpl_csv.obj : .\src\mygdal\cpl_csv.cpp $(DEP_CPP_CPL_C)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_csv.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\gdal_misc.cpp

DEP_CPP_CPL_D=&
	.\src\mygdal\gdal.h

$(OUTDIR)/gdal_misc.obj : .\src\mygdal\gdal_misc.cpp $(DEP_CPP_CPL_D)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\gdal_misc.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_dir.cpp


DEP_CPP_CPL_D=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h


$(OUTDIR)/cpl_dir.obj : .\src\mygdal\cpl_dir.cpp $(DEP_CPP_CPL_D)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_dir.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_error.cpp


DEP_CPP_CPL_E=&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h




$(OUTDIR)/cpl_error.obj : .\src\mygdal\cpl_error.cpp $(DEP_CPP_CPL_E)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_error.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_findfile.cpp


DEP_CPP_CPL_F=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_findfile.obj : .\src\mygdal\cpl_findfile.cpp $(DEP_CPP_CPL_F)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_findfile.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_minixml.cpp


DEP_CPP_CPL_M=&
	.\src\mygdal\cpl_minixml.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_vsi.h




$(OUTDIR)/cpl_minixml.obj : .\src\mygdal\cpl_minixml.cpp $(DEP_CPP_CPL_M)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_minixml.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_path.cpp


DEP_CPP_CPL_P=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_path.obj : .\src\mygdal\cpl_path.cpp $(DEP_CPP_CPL_P)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_path.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_string.cpp

DEP_CPP_CPL_S=&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_string.obj : .\src\mygdal\cpl_string.cpp $(DEP_CPP_CPL_S)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_string.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_vsisimple.cpp


DEP_CPP_CPL_V=&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h




$(OUTDIR)/cpl_vsisimple.obj : .\src\mygdal\cpl_vsisimple.cpp $(DEP_CPP_CPL_V)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_vsisimple.cpp


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cplgetsymbol.cpp

DEP_CPP_CPLGE=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h





$(OUTDIR)/cplgetsymbol.obj : .\src\mygdal\cplgetsymbol.cpp $(DEP_CPP_CPLGE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cplgetsymbol.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ograssemblepolygon.cpp


DEP_CPP_OGRAS=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ograssemblepolygon.obj : .\src\mygdal\ograssemblepolygon.cpp $(DEP_CPP_OGRAS)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ograssemblepolygon.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrcurve.cpp


DEP_CPP_OGRCU=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrcurve.obj : .\src\mygdal\ogrcurve.cpp $(DEP_CPP_OGRCU)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrcurve.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrfeature.cpp

DEP_CPP_OGRFE=&
	.\src\mygdal\ogr_feature.h&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrfeature.obj : .\src\mygdal\ogrfeature.cpp $(DEP_CPP_OGRFE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrfeature.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrfeaturedefn.cpp


DEP_CPP_OGRFEA=&
	.\src\mygdal\ogr_feature.h&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrfeaturedefn.obj : .\src\mygdal\ogrfeaturedefn.cpp $(DEP_CPP_OGRFEA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrfeaturedefn.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrfielddefn.cpp


DEP_CPP_OGRFI=&
	.\src\mygdal\ogr_feature.h&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrfielddefn.obj : .\src\mygdal\ogrfielddefn.cpp $(DEP_CPP_OGRFI)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrfielddefn.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrgeometry.cpp

DEP_CPP_OGRGE=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrgeometry.obj : .\src\mygdal\ogrgeometry.cpp $(DEP_CPP_OGRGE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrgeometry.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrgeometrycollection.cpp

DEP_CPP_OGRGEO=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrgeometrycollection.obj : .\src\mygdal\ogrgeometrycollection.cpp $(DEP_CPP_OGRGEO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrgeometrycollection.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrgeometryfactory.cpp


DEP_CPP_OGRGEOM=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrgeometryfactory.obj : .\src\mygdal\ogrgeometryfactory.cpp $(DEP_CPP_OGRGEOM)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrgeometryfactory.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrlayer.cpp


DEP_CPP_OGRLA=&
	.\src\mygdal\ogrsf_frmts.h&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_attrind.h&
	.\src\mygdal\ogr_feature.h&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrlayer.obj : .\src\mygdal\ogrlayer.cpp $(DEP_CPP_OGRLA)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrlayer.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrlinearring.cpp


DEP_CPP_OGRLI=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrlinearring.obj : .\src\mygdal\ogrlinearring.cpp $(DEP_CPP_OGRLI)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrlinearring.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrlinestring.cpp

DEP_CPP_OGRLIN=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrlinestring.obj : .\src\mygdal\ogrlinestring.cpp $(DEP_CPP_OGRLIN)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrlinestring.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrmultilinestring.cpp

DEP_CPP_OGRMU=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrmultilinestring.obj : .\src\mygdal\ogrmultilinestring.cpp $(DEP_CPP_OGRMU)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrmultilinestring.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrmultipoint.cpp


DEP_CPP_OGRMUL=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrmultipoint.obj : .\src\mygdal\ogrmultipoint.cpp $(DEP_CPP_OGRMUL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrmultipoint.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrmultipolygon.cpp


DEP_CPP_OGRMULT=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrmultipolygon.obj : .\src\mygdal\ogrmultipolygon.cpp $(DEP_CPP_OGRMULT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrmultipolygon.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrpoint.cpp


DEP_CPP_OGRPO=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrpoint.obj : .\src\mygdal\ogrpoint.cpp $(DEP_CPP_OGRPO)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrpoint.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrpolygon.cpp


DEP_CPP_OGRPOL=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrpolygon.obj : .\src\mygdal\ogrpolygon.cpp $(DEP_CPP_OGRPOL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrpolygon.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrs57datasource.cpp


DEP_CPP_OGRS5=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\ogr_s57.h


$(OUTDIR)/ogrs57datasource.obj : .\src\mygdal\ogrs57datasource.cpp $(DEP_CPP_OGRS5)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrs57datasource.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrs57layer.cpp


DEP_CPP_OGRS57L=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\ogr_s57.h


$(OUTDIR)/ogrs57layer.obj : .\src\mygdal\ogrs57layer.cpp $(DEP_CPP_OGRS57L)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrs57layer.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrutils.cpp


DEP_CPP_OGRUT=&
	.\src\mygdal\ogr_geometry.h&
	.\src\mygdal\ogr_p.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\ogr_spatialref.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h




$(OUTDIR)/ogrutils.obj : .\src\mygdal\ogrutils.cpp $(DEP_CPP_OGRUT)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ogrutils.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57classregistrar.cpp

DEP_CPP_S57CL=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\s57.h


$(OUTDIR)/s57classregistrar.obj : .\src\mygdal\s57classregistrar.cpp $(DEP_CPP_S57CL)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\s57classregistrar.cpp



# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57featuredefns.cpp


DEP_CPP_S57FE=&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\s57.h


$(OUTDIR)/s57featuredefns.obj : .\src\mygdal\s57featuredefns.cpp $(DEP_CPP_S57FE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\s57featuredefns.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57reader.cpp


DEP_CPP_S57RE=&
	.\src\mygdal\ogr_api.h&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\ogr_core.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_config.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\s57.h


$(OUTDIR)/s57reader.obj : .\src\mygdal\s57reader.cpp $(DEP_CPP_S57RE)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\s57reader.cpp




# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_conv.cpp

DEP_CPP_CPL_CO=&
	.\src\mygdal\cpl_conv.h&
	.\src\mygdal\cpl_string.h&
	.\src\mygdal\cpl_port.h&
	.\src\mygdal\cpl_vsi.h&
	.\src\mygdal\cpl_error.h&
	.\src\mygdal\cpl_config.h





$(OUTDIR)/cpl_conv.obj : .\src\mygdal\cpl_conv.cpp $(DEP_CPP_CPL_CO)
   $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\cpl_conv.cpp

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ddfrecordindex.cpp
DEP_CPP_DDFR2=&


$(OUTDIR)/ddfrecordindex.obj : .\src\mygdal\ddfrecordindex.cpp $(DEP_CPP_DDFR2)
  $(CXX) -bt=nt -zq -fo=$^@ $(CPP_PROJ) .\src\mygdal\ddfrecordindex.cpp


# End Source File
# End Target
# End Project
################################################################################






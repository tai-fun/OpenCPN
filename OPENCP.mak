# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=OPENCP - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to OPENCP - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OPENCP - Win32 Release" && "$(CFG)" != "OPENCP - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "OPENCP.mak" CFG="OPENCP - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OPENCP - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OPENCP - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "OPENCP - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "OPENCP - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\OPENCP.exe"

CLEAN : 
	-@erase ".\Release\OPENCP.exe"
	-@erase ".\Release\s57reader.obj"
	-@erase ".\Release\talkerid.obj"
	-@erase ".\Release\s52cnsy.obj"
	-@erase ".\Release\ogrgeometryfactory.obj"
	-@erase ".\Release\ogrs57driver.obj"
	-@erase ".\Release\cpl_dir.obj"
	-@erase ".\Release\nmea0183.obj"
	-@erase ".\Release\cpl_csv.obj"
	-@erase ".\Release\Rmc.obj"
	-@erase ".\Release\cpl_conv.obj"
	-@erase ".\Release\mygeom.obj"
	-@erase ".\Release\cpl_vsisimple.obj"
	-@erase ".\Release\s57featuredefns.obj"
	-@erase ".\Release\ogrsfdriver.obj"
	-@erase ".\Release\response.obj"
	-@erase ".\Release\ogr_gensql.obj"
	-@erase ".\Release\sercomm.obj"
	-@erase ".\Release\ograssemblepolygon.obj"
	-@erase ".\Release\ogrspatialreference.obj"
	-@erase ".\Release\cpl_path.obj"
	-@erase ".\Release\ogrgeometrycollection.obj"
	-@erase ".\Release\ogr_srs_esri.obj"
	-@erase ".\Release\routeman.obj"
	-@erase ".\Release\ogr_srs_xml.obj"
	-@erase ".\Release\lat.obj"
	-@erase ".\Release\cpl_string.obj"
	-@erase ".\Release\chcanv.obj"
	-@erase ".\Release\concanv.obj"
	-@erase ".\Release\rmb.obj"
	-@erase ".\Release\ogr_attrind.obj"
	-@erase ".\Release\ogrcurve.obj"
	-@erase ".\Release\gml2ogrgeometry.obj"
	-@erase ".\Release\s57chart.obj"
	-@erase ".\Release\ogrfielddefn.obj"
	-@erase ".\Release\ogr_nullattrind.obj"
	-@erase ".\Release\ddfmodule.obj"
	-@erase ".\Release\tcmgr.obj"
	-@erase ".\Release\ddffield.obj"
	-@erase ".\Release\ddfutils.obj"
	-@erase ".\Release\cpl_error.obj"
	-@erase ".\Release\ogr_srs_dict.obj"
	-@erase ".\Release\ddfsubfielddefn.obj"
	-@erase ".\Release\ogrpolygon.obj"
	-@erase ".\Release\ogrlinestring.obj"
	-@erase ".\Release\ogrmultipolygon.obj"
	-@erase ".\Release\gdal_misc.obj"
	-@erase ".\Release\statwin.obj"
	-@erase ".\Release\ogrfeaturedefn.obj"
	-@erase ".\Release\expid.obj"
	-@erase ".\Release\s52plib.obj"
	-@erase ".\Release\nmea.obj"
	-@erase ".\Release\ogrs57datasource.obj"
	-@erase ".\Release\ogrlinearring.obj"
	-@erase ".\Release\ogrpoint.obj"
	-@erase ".\Release\ddfrecordindex.obj"
	-@erase ".\Release\long.obj"
	-@erase ".\Release\dymemdc.obj"
	-@erase ".\Release\ogr2gmlgeometry.obj"
	-@erase ".\Release\cutil.obj"
	-@erase ".\Release\hexvalue.obj"
	-@erase ".\Release\ddffielddefn.obj"
	-@erase ".\Release\ogrfeature.obj"
	-@erase ".\Release\s57classregistrar.obj"
	-@erase ".\Release\thumbwin.obj"
	-@erase ".\Release\s52utils.obj"
	-@erase ".\Release\ogr_srsnode.obj"
	-@erase ".\Release\ogrgeometry.obj"
	-@erase ".\Release\chart1.obj"
	-@erase ".\Release\ogrutils.obj"
	-@erase ".\Release\s57writer.obj"
	-@erase ".\Release\tri.obj"
	-@erase ".\Release\sentence.obj"
	-@erase ".\Release\latlong.obj"
	-@erase ".\Release\georef.obj"
	-@erase ".\Release\ogr_fromepsg.obj"
	-@erase ".\Release\cpl_minixml.obj"
	-@erase ".\Release\cplgetsymbol.obj"
	-@erase ".\Release\ogrs57layer.obj"
	-@erase ".\Release\s57filecollector.obj"
	-@erase ".\Release\cpl_findfile.obj"
	-@erase ".\Release\dataum.obj"
	-@erase ".\Release\ogrdatasource.obj"
	-@erase ".\Release\ogrmultilinestring.obj"
	-@erase ".\Release\ogrlayer.obj"
	-@erase ".\Release\options.obj"
	-@erase ".\Release\navutil.obj"
	-@erase ".\Release\bitmapo.obj"
	-@erase ".\Release\wificlient.obj"
	-@erase ".\Release\ddfrecord.obj"
	-@erase ".\Release\swq.obj"
	-@erase ".\Release\wvschart.obj"
	-@erase ".\Release\bbox.obj"
	-@erase ".\Release\about.obj"
	-@erase ".\Release\ogr_srs_proj4.obj"
	-@erase ".\Release\ogrmultipoint.obj"
	-@erase ".\Release\ogrsfdriverregistrar.obj"
	-@erase ".\Release\chartdb.obj"
	-@erase ".\Release\ogrct.obj"
	-@erase ".\Release\chartimg.obj"
	-@erase ".\Release\ogrfeaturequery.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /GR /GX /Od /I "include" /I "\wx262\include" /I "\wx262\lib\vc_lib\msw" /D "NDEBUG" /D "__WXMSW__" /D "WIN32" /D "_WINDOWS" /D "CPL_DISABLE_DLL" /D "_CTYPE_DISABLE_MACROS" /D "USE_WIFI_CLIENT" /D "USE_S57" /D "USE_GLU_TESS" /D "USE_GLU_DLL" /c
# SUBTRACT CPP /WX /YX /Yc /Yu
CPP_PROJ=/nologo /ML /GR /GX /Od /I "include" /I "\wx262\include" /I\
 "\wx262\lib\vc_lib\msw" /D "NDEBUG" /D "__WXMSW__" /D "WIN32" /D "_WINDOWS" /D\
 "CPL_DISABLE_DLL" /D "_CTYPE_DISABLE_MACROS" /D "USE_WIFI_CLIENT" /D "USE_S57"\
 /D "USE_GLU_TESS" /D "USE_GLU_DLL" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OPENCP.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 wxbase26.lib wxbase26_net.lib wxmsw26_core.lib wxmsw26_adv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc"
# SUBTRACT LINK32 /incremental:yes /nodefaultlib
LINK32_FLAGS=wxbase26.lib wxbase26_net.lib wxmsw26_core.lib wxmsw26_adv.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 comctl32.lib wsock32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/OPENCP.pdb" /machine:I386 /nodefaultlib:"libc"\
 /out:"$(OUTDIR)/OPENCP.exe" 
LINK32_OBJS= \
	"$(INTDIR)/s57reader.obj" \
	"$(INTDIR)/talkerid.obj" \
	"$(INTDIR)/s52cnsy.obj" \
	"$(INTDIR)/ogrgeometryfactory.obj" \
	"$(INTDIR)/ogrs57driver.obj" \
	"$(INTDIR)/cpl_dir.obj" \
	"$(INTDIR)/nmea0183.obj" \
	"$(INTDIR)/cpl_csv.obj" \
	"$(INTDIR)/Rmc.obj" \
	"$(INTDIR)/cpl_conv.obj" \
	"$(INTDIR)/mygeom.obj" \
	"$(INTDIR)/cpl_vsisimple.obj" \
	"$(INTDIR)/s57featuredefns.obj" \
	"$(INTDIR)/ogrsfdriver.obj" \
	"$(INTDIR)/response.obj" \
	"$(INTDIR)/ogr_gensql.obj" \
	"$(INTDIR)/sercomm.obj" \
	"$(INTDIR)/ograssemblepolygon.obj" \
	"$(INTDIR)/ogrspatialreference.obj" \
	"$(INTDIR)/cpl_path.obj" \
	"$(INTDIR)/ogrgeometrycollection.obj" \
	"$(INTDIR)/ogr_srs_esri.obj" \
	"$(INTDIR)/routeman.obj" \
	"$(INTDIR)/ogr_srs_xml.obj" \
	"$(INTDIR)/lat.obj" \
	"$(INTDIR)/cpl_string.obj" \
	"$(INTDIR)/chcanv.obj" \
	"$(INTDIR)/concanv.obj" \
	"$(INTDIR)/rmb.obj" \
	"$(INTDIR)/ogr_attrind.obj" \
	"$(INTDIR)/ogrcurve.obj" \
	"$(INTDIR)/gml2ogrgeometry.obj" \
	"$(INTDIR)/s57chart.obj" \
	"$(INTDIR)/ogrfielddefn.obj" \
	"$(INTDIR)/ogr_nullattrind.obj" \
	"$(INTDIR)/ddfmodule.obj" \
	"$(INTDIR)/tcmgr.obj" \
	"$(INTDIR)/ddffield.obj" \
	"$(INTDIR)/ddfutils.obj" \
	"$(INTDIR)/cpl_error.obj" \
	"$(INTDIR)/ogr_srs_dict.obj" \
	"$(INTDIR)/ddfsubfielddefn.obj" \
	"$(INTDIR)/ogrpolygon.obj" \
	"$(INTDIR)/ogrlinestring.obj" \
	"$(INTDIR)/ogrmultipolygon.obj" \
	"$(INTDIR)/gdal_misc.obj" \
	"$(INTDIR)/statwin.obj" \
	"$(INTDIR)/ogrfeaturedefn.obj" \
	"$(INTDIR)/expid.obj" \
	"$(INTDIR)/s52plib.obj" \
	"$(INTDIR)/nmea.obj" \
	"$(INTDIR)/ogrs57datasource.obj" \
	"$(INTDIR)/ogrlinearring.obj" \
	"$(INTDIR)/ogrpoint.obj" \
	"$(INTDIR)/ddfrecordindex.obj" \
	"$(INTDIR)/long.obj" \
	"$(INTDIR)/dymemdc.obj" \
	"$(INTDIR)/ogr2gmlgeometry.obj" \
	"$(INTDIR)/cutil.obj" \
	"$(INTDIR)/hexvalue.obj" \
	"$(INTDIR)/ddffielddefn.obj" \
	"$(INTDIR)/ogrfeature.obj" \
	"$(INTDIR)/s57classregistrar.obj" \
	"$(INTDIR)/thumbwin.obj" \
	"$(INTDIR)/s52utils.obj" \
	"$(INTDIR)/ogr_srsnode.obj" \
	"$(INTDIR)/ogrgeometry.obj" \
	"$(INTDIR)/chart1.obj" \
	"$(INTDIR)/ogrutils.obj" \
	"$(INTDIR)/s57writer.obj" \
	"$(INTDIR)/tri.obj" \
	"$(INTDIR)/sentence.obj" \
	"$(INTDIR)/latlong.obj" \
	"$(INTDIR)/georef.obj" \
	"$(INTDIR)/ogr_fromepsg.obj" \
	"$(INTDIR)/cpl_minixml.obj" \
	"$(INTDIR)/cplgetsymbol.obj" \
	"$(INTDIR)/ogrs57layer.obj" \
	"$(INTDIR)/s57filecollector.obj" \
	"$(INTDIR)/cpl_findfile.obj" \
	"$(INTDIR)/dataum.obj" \
	"$(INTDIR)/ogrdatasource.obj" \
	"$(INTDIR)/ogrmultilinestring.obj" \
	"$(INTDIR)/ogrlayer.obj" \
	"$(INTDIR)/options.obj" \
	"$(INTDIR)/navutil.obj" \
	"$(INTDIR)/bitmapo.obj" \
	"$(INTDIR)/wificlient.obj" \
	"$(INTDIR)/ddfrecord.obj" \
	"$(INTDIR)/swq.obj" \
	"$(INTDIR)/wvschart.obj" \
	"$(INTDIR)/bbox.obj" \
	"$(INTDIR)/about.obj" \
	"$(INTDIR)/ogr_srs_proj4.obj" \
	"$(INTDIR)/ogrmultipoint.obj" \
	"$(INTDIR)/ogrsfdriverregistrar.obj" \
	"$(INTDIR)/chartdb.obj" \
	"$(INTDIR)/ogrct.obj" \
	"$(INTDIR)/chartimg.obj" \
	"$(INTDIR)/ogrfeaturequery.obj"

"$(OUTDIR)\OPENCP.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\OPENCP.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\OPENCP.exe"
	-@erase ".\Debug\s52utils.obj"
	-@erase ".\Debug\lat.obj"
	-@erase ".\Debug\gdal_misc.obj"
	-@erase ".\Debug\mygeom.obj"
	-@erase ".\Debug\cpl_path.obj"
	-@erase ".\Debug\ogrutils.obj"
	-@erase ".\Debug\routeman.obj"
	-@erase ".\Debug\s57classregistrar.obj"
	-@erase ".\Debug\s57reader.obj"
	-@erase ".\Debug\ogr_srs_xml.obj"
	-@erase ".\Debug\s57featuredefns.obj"
	-@erase ".\Debug\ogrs57driver.obj"
	-@erase ".\Debug\rmb.obj"
	-@erase ".\Debug\latlong.obj"
	-@erase ".\Debug\ogrct.obj"
	-@erase ".\Debug\ogr_attrind.obj"
	-@erase ".\Debug\ogrcurve.obj"
	-@erase ".\Debug\ogrlayer.obj"
	-@erase ".\Debug\tri.obj"
	-@erase ".\Debug\chcanv.obj"
	-@erase ".\Debug\options.obj"
	-@erase ".\Debug\navutil.obj"
	-@erase ".\Debug\bitmapo.obj"
	-@erase ".\Debug\s57chart.obj"
	-@erase ".\Debug\ogr_gensql.obj"
	-@erase ".\Debug\ogrsfdriverregistrar.obj"
	-@erase ".\Debug\ogr_srs_esri.obj"
	-@erase ".\Debug\ogr_srs_proj4.obj"
	-@erase ".\Debug\ogrs57datasource.obj"
	-@erase ".\Debug\ogrmultipoint.obj"
	-@erase ".\Debug\talkerid.obj"
	-@erase ".\Debug\chartdb.obj"
	-@erase ".\Debug\nmea0183.obj"
	-@erase ".\Debug\cpl_string.obj"
	-@erase ".\Debug\s52cnsy.obj"
	-@erase ".\Debug\ogrfeature.obj"
	-@erase ".\Debug\gml2ogrgeometry.obj"
	-@erase ".\Debug\cpl_conv.obj"
	-@erase ".\Debug\nmea.obj"
	-@erase ".\Debug\cpl_dir.obj"
	-@erase ".\Debug\ogr_nullattrind.obj"
	-@erase ".\Debug\cpl_csv.obj"
	-@erase ".\Debug\ogrlinestring.obj"
	-@erase ".\Debug\long.obj"
	-@erase ".\Debug\response.obj"
	-@erase ".\Debug\cpl_vsisimple.obj"
	-@erase ".\Debug\ogrfielddefn.obj"
	-@erase ".\Debug\sercomm.obj"
	-@erase ".\Debug\ddfsubfielddefn.obj"
	-@erase ".\Debug\ogrfeaturedefn.obj"
	-@erase ".\Debug\ddfmodule.obj"
	-@erase ".\Debug\hexvalue.obj"
	-@erase ".\Debug\ogrmultipolygon.obj"
	-@erase ".\Debug\about.obj"
	-@erase ".\Debug\s57filecollector.obj"
	-@erase ".\Debug\thumbwin.obj"
	-@erase ".\Debug\cpl_error.obj"
	-@erase ".\Debug\ogr_srs_dict.obj"
	-@erase ".\Debug\ddfrecordindex.obj"
	-@erase ".\Debug\ogr_srsnode.obj"
	-@erase ".\Debug\ogrgeometry.obj"
	-@erase ".\Debug\concanv.obj"
	-@erase ".\Debug\ogrpolygon.obj"
	-@erase ".\Debug\ogr2gmlgeometry.obj"
	-@erase ".\Debug\tcmgr.obj"
	-@erase ".\Debug\sentence.obj"
	-@erase ".\Debug\cpl_minixml.obj"
	-@erase ".\Debug\ogrmultilinestring.obj"
	-@erase ".\Debug\chart1.obj"
	-@erase ".\Debug\ogrs57layer.obj"
	-@erase ".\Debug\ogrgeometrycollection.obj"
	-@erase ".\Debug\bbox.obj"
	-@erase ".\Debug\swq.obj"
	-@erase ".\Debug\expid.obj"
	-@erase ".\Debug\wvschart.obj"
	-@erase ".\Debug\ogrdatasource.obj"
	-@erase ".\Debug\ddffielddefn.obj"
	-@erase ".\Debug\ddffield.obj"
	-@erase ".\Debug\georef.obj"
	-@erase ".\Debug\ddfutils.obj"
	-@erase ".\Debug\dataum.obj"
	-@erase ".\Debug\cutil.obj"
	-@erase ".\Debug\chartimg.obj"
	-@erase ".\Debug\ogrgeometryfactory.obj"
	-@erase ".\Debug\s57writer.obj"
	-@erase ".\Debug\statwin.obj"
	-@erase ".\Debug\ogr_fromepsg.obj"
	-@erase ".\Debug\cplgetsymbol.obj"
	-@erase ".\Debug\Rmc.obj"
	-@erase ".\Debug\ogrspatialreference.obj"
	-@erase ".\Debug\ogrpoint.obj"
	-@erase ".\Debug\s52plib.obj"
	-@erase ".\Debug\cpl_findfile.obj"
	-@erase ".\Debug\ogrlinearring.obj"
	-@erase ".\Debug\dymemdc.obj"
	-@erase ".\Debug\ddfrecord.obj"
	-@erase ".\Debug\ogrsfdriver.obj"
	-@erase ".\Debug\ograssemblepolygon.obj"
	-@erase ".\Debug\ogrfeaturequery.obj"
	-@erase ".\Debug\wificlient.obj"
	-@erase ".\Debug\OPENCP.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /WX /GR /GX /Zi /Od /I "include" /I "\wx262\include" /I "\wx262\lib\vc_lib\mswd" /D "_DEBUG" /D "__WXMSW__" /D "WIN32" /D "_WINDOWS" /D "CPL_DISABLE_DLL" /D "_CTYPE_DISABLE_MACROS" /D "USE_WIFI_CLIENT" /D "USE_S57" /D "USE_GLU_TESS" /D "USE_GLU_DLL" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /MLd /WX /GR /GX /Zi /Od /I "include" /I "\wx262\include" /I\
 "\wx262\lib\vc_lib\mswd" /D "_DEBUG" /D "__WXMSW__" /D "WIN32" /D "_WINDOWS" /D\
 "CPL_DISABLE_DLL" /D "_CTYPE_DISABLE_MACROS" /D "USE_WIFI_CLIENT" /D "USE_S57"\
 /D "USE_GLU_TESS" /D "USE_GLU_DLL" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/OPENCP.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 wxbase26d.lib wxbase26d_net.lib wxmsw26d_core.lib wxmsw26d_adv.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib wsock32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /nodefaultlib:"libcd"
LINK32_FLAGS=wxbase26d.lib wxbase26d_net.lib wxmsw26d_core.lib wxmsw26d_adv.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 comctl32.lib wsock32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/OPENCP.pdb" /debug /machine:I386 /nodefaultlib:"libcd"\
 /out:"$(OUTDIR)/OPENCP.exe" 
LINK32_OBJS= \
	"$(INTDIR)/s52utils.obj" \
	"$(INTDIR)/lat.obj" \
	"$(INTDIR)/gdal_misc.obj" \
	"$(INTDIR)/mygeom.obj" \
	"$(INTDIR)/cpl_path.obj" \
	"$(INTDIR)/ogrutils.obj" \
	"$(INTDIR)/routeman.obj" \
	"$(INTDIR)/s57classregistrar.obj" \
	"$(INTDIR)/s57reader.obj" \
	"$(INTDIR)/ogr_srs_xml.obj" \
	"$(INTDIR)/s57featuredefns.obj" \
	"$(INTDIR)/ogrs57driver.obj" \
	"$(INTDIR)/rmb.obj" \
	"$(INTDIR)/latlong.obj" \
	"$(INTDIR)/ogrct.obj" \
	"$(INTDIR)/ogr_attrind.obj" \
	"$(INTDIR)/ogrcurve.obj" \
	"$(INTDIR)/ogrlayer.obj" \
	"$(INTDIR)/tri.obj" \
	"$(INTDIR)/chcanv.obj" \
	"$(INTDIR)/options.obj" \
	"$(INTDIR)/navutil.obj" \
	"$(INTDIR)/bitmapo.obj" \
	"$(INTDIR)/s57chart.obj" \
	"$(INTDIR)/ogr_gensql.obj" \
	"$(INTDIR)/ogrsfdriverregistrar.obj" \
	"$(INTDIR)/ogr_srs_esri.obj" \
	"$(INTDIR)/ogr_srs_proj4.obj" \
	"$(INTDIR)/ogrs57datasource.obj" \
	"$(INTDIR)/ogrmultipoint.obj" \
	"$(INTDIR)/talkerid.obj" \
	"$(INTDIR)/chartdb.obj" \
	"$(INTDIR)/nmea0183.obj" \
	"$(INTDIR)/cpl_string.obj" \
	"$(INTDIR)/s52cnsy.obj" \
	"$(INTDIR)/ogrfeature.obj" \
	"$(INTDIR)/gml2ogrgeometry.obj" \
	"$(INTDIR)/cpl_conv.obj" \
	"$(INTDIR)/nmea.obj" \
	"$(INTDIR)/cpl_dir.obj" \
	"$(INTDIR)/ogr_nullattrind.obj" \
	"$(INTDIR)/cpl_csv.obj" \
	"$(INTDIR)/ogrlinestring.obj" \
	"$(INTDIR)/long.obj" \
	"$(INTDIR)/response.obj" \
	"$(INTDIR)/cpl_vsisimple.obj" \
	"$(INTDIR)/ogrfielddefn.obj" \
	"$(INTDIR)/sercomm.obj" \
	"$(INTDIR)/ddfsubfielddefn.obj" \
	"$(INTDIR)/ogrfeaturedefn.obj" \
	"$(INTDIR)/ddfmodule.obj" \
	"$(INTDIR)/hexvalue.obj" \
	"$(INTDIR)/ogrmultipolygon.obj" \
	"$(INTDIR)/about.obj" \
	"$(INTDIR)/s57filecollector.obj" \
	"$(INTDIR)/thumbwin.obj" \
	"$(INTDIR)/cpl_error.obj" \
	"$(INTDIR)/ogr_srs_dict.obj" \
	"$(INTDIR)/ddfrecordindex.obj" \
	"$(INTDIR)/ogr_srsnode.obj" \
	"$(INTDIR)/ogrgeometry.obj" \
	"$(INTDIR)/concanv.obj" \
	"$(INTDIR)/ogrpolygon.obj" \
	"$(INTDIR)/ogr2gmlgeometry.obj" \
	"$(INTDIR)/tcmgr.obj" \
	"$(INTDIR)/sentence.obj" \
	"$(INTDIR)/cpl_minixml.obj" \
	"$(INTDIR)/ogrmultilinestring.obj" \
	"$(INTDIR)/chart1.obj" \
	"$(INTDIR)/ogrs57layer.obj" \
	"$(INTDIR)/ogrgeometrycollection.obj" \
	"$(INTDIR)/bbox.obj" \
	"$(INTDIR)/swq.obj" \
	"$(INTDIR)/expid.obj" \
	"$(INTDIR)/wvschart.obj" \
	"$(INTDIR)/ogrdatasource.obj" \
	"$(INTDIR)/ddffielddefn.obj" \
	"$(INTDIR)/ddffield.obj" \
	"$(INTDIR)/georef.obj" \
	"$(INTDIR)/ddfutils.obj" \
	"$(INTDIR)/dataum.obj" \
	"$(INTDIR)/cutil.obj" \
	"$(INTDIR)/chartimg.obj" \
	"$(INTDIR)/ogrgeometryfactory.obj" \
	"$(INTDIR)/s57writer.obj" \
	"$(INTDIR)/statwin.obj" \
	"$(INTDIR)/ogr_fromepsg.obj" \
	"$(INTDIR)/cplgetsymbol.obj" \
	"$(INTDIR)/Rmc.obj" \
	"$(INTDIR)/ogrspatialreference.obj" \
	"$(INTDIR)/ogrpoint.obj" \
	"$(INTDIR)/s52plib.obj" \
	"$(INTDIR)/cpl_findfile.obj" \
	"$(INTDIR)/ogrlinearring.obj" \
	"$(INTDIR)/dymemdc.obj" \
	"$(INTDIR)/ddfrecord.obj" \
	"$(INTDIR)/ogrsfdriver.obj" \
	"$(INTDIR)/ograssemblepolygon.obj" \
	"$(INTDIR)/ogrfeaturequery.obj" \
	"$(INTDIR)/wificlient.obj"

"$(OUTDIR)\OPENCP.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "OPENCP - Win32 Release"
# Name "OPENCP - Win32 Debug"

!IF  "$(CFG)" == "OPENCP - Win32 Release"

!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\src\thumbwin.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_THUMB=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\thumbwin.h"\
	".\include\chart1.h"\
	".\include\chartdb.h"\
	".\include\chcanv.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\bitmapo.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\gpc.h"\
	".\include\tcmgr.h"\
	
NODEP_CPP_THUMB=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	

"$(INTDIR)\thumbwin.obj" : $(SOURCE) $(DEP_CPP_THUMB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_THUMB=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\thumbwin.h"\
	".\include\chart1.h"\
	".\include\chartdb.h"\
	".\include\chcanv.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\bitmapo.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\gpc.h"\
	".\include\tcmgr.h"\
	
NODEP_CPP_THUMB=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	

"$(INTDIR)\thumbwin.obj" : $(SOURCE) $(DEP_CPP_THUMB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\tcmgr.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_TCMGR=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/textfile.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	
NODEP_CPP_TCMGR=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	

"$(INTDIR)\tcmgr.obj" : $(SOURCE) $(DEP_CPP_TCMGR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_TCMGR=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/textfile.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	
NODEP_CPP_TCMGR=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	

"$(INTDIR)\tcmgr.obj" : $(SOURCE) $(DEP_CPP_TCMGR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\statwin.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_STATW=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\statwin.h"\
	".\include\chartdb.h"\
	".\include\chart1.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	"\wx262\include\wx/datetime.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	".\include\bitmapo.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\tcmgr.h"\
	
NODEP_CPP_STATW=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	

"$(INTDIR)\statwin.obj" : $(SOURCE) $(DEP_CPP_STATW) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_STATW=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\statwin.h"\
	".\include\chartdb.h"\
	".\include\chart1.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	".\include\bitmapo.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\tcmgr.h"\
	
NODEP_CPP_STATW=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\include\wx\x11\private.h"\
	

"$(INTDIR)\statwin.obj" : $(SOURCE) $(DEP_CPP_STATW) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\sercomm.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_SERCO=\
	".\include\dychart.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	
NODEP_CPP_SERCO=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	

"$(INTDIR)\sercomm.obj" : $(SOURCE) $(DEP_CPP_SERCO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_SERCO=\
	".\include\dychart.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	
NODEP_CPP_SERCO=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	

"$(INTDIR)\sercomm.obj" : $(SOURCE) $(DEP_CPP_SERCO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\routeman.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_ROUTE=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	".\include\sercomm.h"\
	".\include\routeman.h"\
	".\include\chcanv.h"\
	".\include\concanv.h"\
	".\include\nmea.h"\
	".\src\nmea0183\nmea0183.h"\
	".\include\navutil.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\tcmgr.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	".\src\nmea0183\nmea0183.hpp"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	".\include\bitmapo.h"\
	".\include\dymemdc.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	
NODEP_CPP_ROUTE=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\routeman.obj" : $(SOURCE) $(DEP_CPP_ROUTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_ROUTE=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	".\include\sercomm.h"\
	".\include\routeman.h"\
	".\include\chcanv.h"\
	".\include\concanv.h"\
	".\include\nmea.h"\
	".\src\nmea0183\nmea0183.h"\
	".\include\navutil.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\tcmgr.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	".\src\nmea0183\nmea0183.hpp"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	".\include\bitmapo.h"\
	".\include\dymemdc.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	
NODEP_CPP_ROUTE=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	

"$(INTDIR)\routeman.obj" : $(SOURCE) $(DEP_CPP_ROUTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_NMEA_=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/tokenzr.h"\
	".\include\dychart.h"\
	".\include\nmea.h"\
	".\include\chart1.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/wxchar.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	
NODEP_CPP_NMEA_=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\nmea.obj" : $(SOURCE) $(DEP_CPP_NMEA_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_NMEA_=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/tokenzr.h"\
	".\include\dychart.h"\
	".\include\nmea.h"\
	".\include\chart1.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	
NODEP_CPP_NMEA_=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	

"$(INTDIR)\nmea.obj" : $(SOURCE) $(DEP_CPP_NMEA_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\navutil.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_NAVUT=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/tokenzr.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	".\include\chart1.h"\
	".\include\navutil.h"\
	".\include\chcanv.h"\
	".\include\georef.h"\
	".\include\nmea.h"\
	".\include\s52plib.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/fontenum.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/fontutil.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/wxchar.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	".\include\tcmgr.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	".\include\s52s57.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	"\wx262\include\wx/unix/fontutil.h"\
	
NODEP_CPP_NAVUT=\
	".\..\..\..\usr\X11R6\include\X11\Xlib.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\fontutil.h"\
	

"$(INTDIR)\navutil.obj" : $(SOURCE) $(DEP_CPP_NAVUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_NAVUT=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/tokenzr.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	".\include\chart1.h"\
	".\include\navutil.h"\
	".\include\chcanv.h"\
	".\include\georef.h"\
	".\include\nmea.h"\
	".\include\s52plib.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/fontenum.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/fontutil.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	".\include\tcmgr.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	".\include\s52s57.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	"\wx262\include\wx/unix/fontutil.h"\
	
NODEP_CPP_NAVUT=\
	".\..\..\..\usr\X11R6\include\X11\Xlib.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\fontutil.h"\
	

"$(INTDIR)\navutil.obj" : $(SOURCE) $(DEP_CPP_NAVUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\georef.c
DEP_CPP_GEORE=\
	".\include\georef.h"\
	

"$(INTDIR)\georef.obj" : $(SOURCE) $(DEP_CPP_GEORE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\dymemdc.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_DYMEM=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/msw/private.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\dychart.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	
NODEP_CPP_DYMEM=\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	

"$(INTDIR)\dymemdc.obj" : $(SOURCE) $(DEP_CPP_DYMEM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_DYMEM=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/msw/private.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\dychart.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/longlong.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	
NODEP_CPP_DYMEM=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\dymemdc.obj" : $(SOURCE) $(DEP_CPP_DYMEM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\dataum.c

"$(INTDIR)\dataum.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\concanv.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_CONCA=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/datetime.h"\
	".\include\chart1.h"\
	".\include\concanv.h"\
	".\include\routeman.h"\
	".\include\navutil.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	
NODEP_CPP_CONCA=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	

"$(INTDIR)\concanv.obj" : $(SOURCE) $(DEP_CPP_CONCA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_CONCA=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/datetime.h"\
	".\include\chart1.h"\
	".\include\concanv.h"\
	".\include\routeman.h"\
	".\include\navutil.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	
NODEP_CPP_CONCA=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	

"$(INTDIR)\concanv.obj" : $(SOURCE) $(DEP_CPP_CONCA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chcanv.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_CHCAN=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/image.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	".\include\chcanv.h"\
	".\include\routeman.h"\
	".\include\navutil.h"\
	".\include\concanv.h"\
	".\include\thumbwin.h"\
	".\include\chartdb.h"\
	".\include\wvschart.h"\
	".\include\georef.h"\
	".\include\chartimg.h"\
	".\include\chart1.h"\
	".\include\s57chart.h"\
	".\include\s52plib.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/wxchar.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/longlong.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\tcmgr.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/encinfo.h"\
	".\include\bitmapo.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	
NODEP_CPP_CHCAN=\
	".\src\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\chcanv.obj" : $(SOURCE) $(DEP_CPP_CHCAN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_CHCAN=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/image.h"\
	".\include\dychart.h"\
	"\wx262\include\wx/listimpl.cpp"\
	".\include\chcanv.h"\
	".\include\routeman.h"\
	".\include\navutil.h"\
	".\include\concanv.h"\
	".\include\thumbwin.h"\
	".\include\chartdb.h"\
	".\include\wvschart.h"\
	".\include\georef.h"\
	".\include\chartimg.h"\
	".\include\chart1.h"\
	".\include\s57chart.h"\
	".\include\s52plib.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\tcmgr.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	".\include\bitmapo.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	
NODEP_CPP_CHCAN=\
	".\src\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	

"$(INTDIR)\chcanv.obj" : $(SOURCE) $(DEP_CPP_CHCAN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chartimg.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_CHART=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\chartimg.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/image.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/defs.h"\
	".\include\chartbase.h"\
	".\include\georef.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\dychart.h"\
	".\include\bitmapo.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/ffile.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	
NODEP_CPP_CHART=\
	".\src\wx\x11\private.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\chartimg.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_CHART=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\chartimg.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/image.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	".\include\chartbase.h"\
	".\include\georef.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\dychart.h"\
	".\include\bitmapo.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/ffile.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	
NODEP_CPP_CHART=\
	".\src\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	

"$(INTDIR)\chartimg.obj" : $(SOURCE) $(DEP_CPP_CHART) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chartdb.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_CHARTD=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\chartdb.h"\
	".\include\chartimg.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\s57chart.h"\
	"\wx262\include\wx/arrimpl.cpp"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/strconv.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/longlong.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/ffile.h"\
	"\wx262\include\wx/datetime.h"\
	".\include\dychart.h"\
	".\include\bitmapo.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\tcmgr.h"\
	".\include\gpc.h"\
	".\include\georef.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	
NODEP_CPP_CHARTD=\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\chartdb.obj" : $(SOURCE) $(DEP_CPP_CHARTD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_CHARTD=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\chartdb.h"\
	".\include\chartimg.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\s57chart.h"\
	"\wx262\include\wx/arrimpl.cpp"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\dychart.h"\
	".\include\bitmapo.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\tcmgr.h"\
	".\include\gpc.h"\
	".\include\georef.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	
NODEP_CPP_CHARTD=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	

"$(INTDIR)\chartdb.obj" : $(SOURCE) $(DEP_CPP_CHARTD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\chart1.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_CHART1=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/print.h"\
	"\wx262\include\wx/printdlg.h"\
	"\wx262\include\wx/artprov.h"\
	".\include\dychart.h"\
	".\include\chart1.h"\
	".\include\chcanv.h"\
	".\include\chartdb.h"\
	".\include\navutil.h"\
	".\include\routeman.h"\
	".\include\statwin.h"\
	".\include\concanv.h"\
	".\include\nmea.h"\
	".\src\nmea0183\nmea0183.h"\
	".\src\dialog\options.h"\
	".\include\about.h"\
	".\include\thumbwin.h"\
	".\include\tcmgr.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/image.h"\
	".\include\s52plib.h"\
	".\include\s57chart.h"\
	".\include\wificlient.h"\
	".\src\bitmaps\settings.xpm"\
	".\src\bitmaps\zoomin.xpm"\
	".\src\bitmaps\zoomout.xpm"\
	".\src\bitmaps\scin.xpm"\
	".\src\bitmaps\scout.xpm"\
	".\src\bitmaps\tide.xpm"\
	".\src\bitmaps\text.xpm"\
	".\src\bitmaps\route.xpm"\
	".\src\bitmaps\exitt.xpm"\
	".\src\bitmaps\follow.xpm"\
	".\src\bitmaps\current.xpm"\
	".\src\bitmaps\print.xpm"\
	".\src\bitmaps\help.xpm"\
	".\src\bitmaps\colscheme.xpm"\
	"\wx262\include\wx/encconv.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\bitmapo.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	".\src\nmea0183\nmea0183.hpp"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	"\wx262\include\wx/notebook.h"\
	"\wx262\include\wx/dirctrl.h"\
	"\wx262\include\wx/bookctrl.h"\
	"\wx262\include\wx/univ/notebook.h"\
	"\wx262\include\wx/msw/notebook.h"\
	"\wx262\include\wx/generic/notebook.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/choicebk.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/generic/dirctrlg.h"\
	"\wx262\include\wx/imaglist.h"\
	"\wx262\include\wx/treectrl.h"\
	"\wx262\include\wx/dirdlg.h"\
	"\wx262\include\wx/choice.h"\
	"\wx262\include\wx/msw/imaglist.h"\
	"\wx262\include\wx/generic/imaglist.h"\
	"\wx262\include\wx/treebase.h"\
	"\wx262\include\wx/generic/treectlg.h"\
	"\wx262\include\wx/palmos/treectrl.h"\
	"\wx262\include\wx/msw/treectrl.h"\
	"\wx262\include\wx/textctrl.h"\
	"\wx262\include\wx/ioswrap.h"\
	"\wx262\include\wx/univ/textctrl.h"\
	"\wx262\include\wx/msw/wince/textctrlce.h"\
	"\wx262\include\wx/msw/textctrl.h"\
	"\wx262\include\wx/generic/dirdlgg.h"\
	"\wx262\include\wx/msw/dirdlg.h"\
	"\wx262\include\wx/ctrlsub.h"\
	"\wx262\include\wx/univ/choice.h"\
	"\wx262\include\wx/msw/wince/choicece.h"\
	"\wx262\include\wx/msw/choice.h"\
	"\wx262\include\wx/combobox.h"\
	"\wx262\include\wx/univ/combobox.h"\
	"\wx262\include\wx/msw/combobox.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	
NODEP_CPP_CHART1=\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\os2\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\imaglist.h"\
	".\..\..\..\wx262\include\wx\wx\x11\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\motif\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\os2\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dirdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\choice.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\choice.h"\
	".\..\..\..\wx262\include\wx\wx\mac\choice.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\choice.h"\
	".\..\..\..\wx262\include\wx\wx\os2\choice.h"\
	".\..\..\..\wx262\include\wx\wx\motif\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\mac\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\os2\combobox.h"\
	

"$(INTDIR)\chart1.obj" : $(SOURCE) $(DEP_CPP_CHART1) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_CHART1=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/print.h"\
	"\wx262\include\wx/printdlg.h"\
	"\wx262\include\wx/artprov.h"\
	".\include\dychart.h"\
	".\include\chart1.h"\
	".\include\chcanv.h"\
	".\include\chartdb.h"\
	".\include\navutil.h"\
	".\include\routeman.h"\
	".\include\statwin.h"\
	".\include\concanv.h"\
	".\include\nmea.h"\
	".\src\nmea0183\nmea0183.h"\
	".\src\dialog\options.h"\
	".\include\about.h"\
	".\include\thumbwin.h"\
	".\include\tcmgr.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/image.h"\
	".\include\s52plib.h"\
	".\include\s57chart.h"\
	".\include\wificlient.h"\
	".\src\bitmaps\settings.xpm"\
	".\src\bitmaps\zoomin.xpm"\
	".\src\bitmaps\zoomout.xpm"\
	".\src\bitmaps\scin.xpm"\
	".\src\bitmaps\scout.xpm"\
	".\src\bitmaps\tide.xpm"\
	".\src\bitmaps\text.xpm"\
	".\src\bitmaps\route.xpm"\
	".\src\bitmaps\exitt.xpm"\
	".\src\bitmaps\follow.xpm"\
	".\src\bitmaps\current.xpm"\
	".\src\bitmaps\print.xpm"\
	".\src\bitmaps\help.xpm"\
	".\src\bitmaps\colscheme.xpm"\
	"\wx262\include\wx/encconv.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	".\include\chartbase.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/ffile.h"\
	".\include\bitmapo.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\gpc.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	".\src\nmea0183\nmea0183.hpp"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	"\wx262\include\wx/notebook.h"\
	"\wx262\include\wx/dirctrl.h"\
	"\wx262\include\wx/bookctrl.h"\
	"\wx262\include\wx/univ/notebook.h"\
	"\wx262\include\wx/msw/notebook.h"\
	"\wx262\include\wx/generic/notebook.h"\
	"\wx262\include\wx/choicebk.h"\
	"\wx262\include\wx/generic/dirctrlg.h"\
	"\wx262\include\wx/imaglist.h"\
	"\wx262\include\wx/treectrl.h"\
	"\wx262\include\wx/dirdlg.h"\
	"\wx262\include\wx/choice.h"\
	"\wx262\include\wx/msw/imaglist.h"\
	"\wx262\include\wx/generic/imaglist.h"\
	"\wx262\include\wx/treebase.h"\
	"\wx262\include\wx/generic/treectlg.h"\
	"\wx262\include\wx/palmos/treectrl.h"\
	"\wx262\include\wx/msw/treectrl.h"\
	"\wx262\include\wx/textctrl.h"\
	"\wx262\include\wx/ioswrap.h"\
	"\wx262\include\wx/univ/textctrl.h"\
	"\wx262\include\wx/msw/wince/textctrlce.h"\
	"\wx262\include\wx/msw/textctrl.h"\
	"\wx262\include\wx/generic/dirdlgg.h"\
	"\wx262\include\wx/msw/dirdlg.h"\
	"\wx262\include\wx/ctrlsub.h"\
	"\wx262\include\wx/univ/choice.h"\
	"\wx262\include\wx/msw/wince/choicece.h"\
	"\wx262\include\wx/msw/choice.h"\
	"\wx262\include\wx/combobox.h"\
	"\wx262\include\wx/univ/combobox.h"\
	"\wx262\include\wx/msw/combobox.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	
NODEP_CPP_CHART1=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\os2\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\imaglist.h"\
	".\..\..\..\wx262\include\wx\wx\x11\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\motif\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\os2\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dirdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\choice.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\choice.h"\
	".\..\..\..\wx262\include\wx\wx\mac\choice.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\choice.h"\
	".\..\..\..\wx262\include\wx\wx\os2\choice.h"\
	".\..\..\..\wx262\include\wx\wx\motif\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\mac\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\os2\combobox.h"\
	

"$(INTDIR)\chart1.obj" : $(SOURCE) $(DEP_CPP_CHART1) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\bitmapo.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_BITMA=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\bitmapo.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/msw/private.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/image.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	
NODEP_CPP_BITMA=\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\bitmapo.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_BITMA=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\bitmapo.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/msw/private.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/image.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/longlong.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	
NODEP_CPP_BITMA=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\bitmapo.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\bbox.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_BBOX_=\
	"\wx262\include\wx/wxprec.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	
NODEP_CPP_BBOX_=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	

"$(INTDIR)\bbox.obj" : $(SOURCE) $(DEP_CPP_BBOX_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_BBOX_=\
	"\wx262\include\wx/wxprec.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	
NODEP_CPP_BBOX_=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	

"$(INTDIR)\bbox.obj" : $(SOURCE) $(DEP_CPP_BBOX_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\dialog\options.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_OPTIO=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\dychart.h"\
	".\src\dialog\options.h"\
	".\include\navutil.h"\
	".\include\s52plib.h"\
	"\wx262\include\wx/artprov.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/generic/panelg.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/notebook.h"\
	"\wx262\include\wx/dirctrl.h"\
	"\wx262\include\wx/bookctrl.h"\
	"\wx262\include\wx/univ/notebook.h"\
	"\wx262\include\wx/msw/notebook.h"\
	"\wx262\include\wx/generic/notebook.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/choicebk.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/generic/dirctrlg.h"\
	"\wx262\include\wx/imaglist.h"\
	"\wx262\include\wx/treectrl.h"\
	"\wx262\include\wx/dirdlg.h"\
	"\wx262\include\wx/choice.h"\
	"\wx262\include\wx/msw/imaglist.h"\
	"\wx262\include\wx/generic/imaglist.h"\
	"\wx262\include\wx/treebase.h"\
	"\wx262\include\wx/generic/treectlg.h"\
	"\wx262\include\wx/palmos/treectrl.h"\
	"\wx262\include\wx/msw/treectrl.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/textctrl.h"\
	"\wx262\include\wx/ioswrap.h"\
	"\wx262\include\wx/univ/textctrl.h"\
	"\wx262\include\wx/msw/wince/textctrlce.h"\
	"\wx262\include\wx/msw/textctrl.h"\
	"\wx262\include\wx/generic/dirdlgg.h"\
	"\wx262\include\wx/msw/dirdlg.h"\
	"\wx262\include\wx/ctrlsub.h"\
	"\wx262\include\wx/univ/choice.h"\
	"\wx262\include\wx/msw/wince/choicece.h"\
	"\wx262\include\wx/msw/choice.h"\
	"\wx262\include\wx/combobox.h"\
	"\wx262\include\wx/univ/combobox.h"\
	"\wx262\include\wx/msw/combobox.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	".\include\s52s57.h"\
	".\include\gpc.h"\
	
NODEP_CPP_OPTIO=\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\os2\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\imaglist.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\motif\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\os2\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dirdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\choice.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\choice.h"\
	".\..\..\..\wx262\include\wx\wx\mac\choice.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\choice.h"\
	".\..\..\..\wx262\include\wx\wx\os2\choice.h"\
	".\..\..\..\wx262\include\wx\wx\motif\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\mac\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\os2\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	

"$(INTDIR)\options.obj" : $(SOURCE) $(DEP_CPP_OPTIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_OPTIO=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\dychart.h"\
	".\src\dialog\options.h"\
	".\include\navutil.h"\
	".\include\s52plib.h"\
	"\wx262\include\wx/artprov.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/notebook.h"\
	"\wx262\include\wx/dirctrl.h"\
	"\wx262\include\wx/bookctrl.h"\
	"\wx262\include\wx/univ/notebook.h"\
	"\wx262\include\wx/msw/notebook.h"\
	"\wx262\include\wx/generic/notebook.h"\
	"\wx262\include\wx/choicebk.h"\
	"\wx262\include\wx/generic/dirctrlg.h"\
	"\wx262\include\wx/imaglist.h"\
	"\wx262\include\wx/treectrl.h"\
	"\wx262\include\wx/dirdlg.h"\
	"\wx262\include\wx/choice.h"\
	"\wx262\include\wx/msw/imaglist.h"\
	"\wx262\include\wx/generic/imaglist.h"\
	"\wx262\include\wx/treebase.h"\
	"\wx262\include\wx/generic/treectlg.h"\
	"\wx262\include\wx/palmos/treectrl.h"\
	"\wx262\include\wx/msw/treectrl.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/textctrl.h"\
	"\wx262\include\wx/ioswrap.h"\
	"\wx262\include\wx/univ/textctrl.h"\
	"\wx262\include\wx/msw/wince/textctrlce.h"\
	"\wx262\include\wx/msw/textctrl.h"\
	"\wx262\include\wx/generic/dirdlgg.h"\
	"\wx262\include\wx/msw/dirdlg.h"\
	"\wx262\include\wx/ctrlsub.h"\
	"\wx262\include\wx/univ/choice.h"\
	"\wx262\include\wx/msw/wince/choicece.h"\
	"\wx262\include\wx/msw/choice.h"\
	"\wx262\include\wx/combobox.h"\
	"\wx262\include\wx/univ/combobox.h"\
	"\wx262\include\wx/msw/combobox.h"\
	"\wx262\include\wx/config.h"\
	"\wx262\include\wx/confbase.h"\
	"\wx262\include\wx/fileconf.h"\
	"\wx262\include\wx/msw/regconf.h"\
	"\wx262\include\wx/msw/iniconf.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/fontdlg.h"\
	"\wx262\include\wx/palmos/prefconf.h"\
	"\wx262\include\wx/textfile.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/msw/registry.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/generic/fontdlgg.h"\
	"\wx262\include\wx/msw/fontdlg.h"\
	".\include\s52s57.h"\
	".\include\gpc.h"\
	
NODEP_CPP_OPTIO=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\os2\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\imaglist.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\x11\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\motif\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\os2\textctrl.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dirdlg.h"\
	".\..\..\..\wx262\include\wx\wx\motif\choice.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\choice.h"\
	".\..\..\..\wx262\include\wx\wx\mac\choice.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\choice.h"\
	".\..\..\..\wx262\include\wx\wx\os2\choice.h"\
	".\..\..\..\wx262\include\wx\wx\motif\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\mac\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\os2\combobox.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\os2\fontdlg.h"\
	".\..\..\..\wx262\include\wx\wx\mac\fontdlg.h"\
	

"$(INTDIR)\options.obj" : $(SOURCE) $(DEP_CPP_OPTIO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\talkerid.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_TALKE=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_TALKE=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\talkerid.obj" : $(SOURCE) $(DEP_CPP_TALKE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_TALKE=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_TALKE=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\talkerid.obj" : $(SOURCE) $(DEP_CPP_TALKE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\sentence.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_SENTE=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_SENTE=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\sentence.obj" : $(SOURCE) $(DEP_CPP_SENTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_SENTE=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_SENTE=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\sentence.obj" : $(SOURCE) $(DEP_CPP_SENTE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\rmb.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_RMB_C=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_RMB_C=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\rmb.obj" : $(SOURCE) $(DEP_CPP_RMB_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_RMB_C=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_RMB_C=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\rmb.obj" : $(SOURCE) $(DEP_CPP_RMB_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\response.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_RESPO=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_RESPO=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\response.obj" : $(SOURCE) $(DEP_CPP_RESPO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_RESPO=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_RESPO=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\response.obj" : $(SOURCE) $(DEP_CPP_RESPO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\nmea0183.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_NMEA0=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/listimpl.cpp"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_NMEA0=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\nmea0183.obj" : $(SOURCE) $(DEP_CPP_NMEA0) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_NMEA0=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/listimpl.cpp"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_NMEA0=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\nmea0183.obj" : $(SOURCE) $(DEP_CPP_NMEA0) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\long.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_LONG_=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_LONG_=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\long.obj" : $(SOURCE) $(DEP_CPP_LONG_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_LONG_=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_LONG_=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\long.obj" : $(SOURCE) $(DEP_CPP_LONG_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\latlong.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_LATLO=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_LATLO=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\latlong.obj" : $(SOURCE) $(DEP_CPP_LATLO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_LATLO=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_LATLO=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\latlong.obj" : $(SOURCE) $(DEP_CPP_LATLO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\lat.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_LAT_C=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_LAT_C=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\lat.obj" : $(SOURCE) $(DEP_CPP_LAT_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_LAT_C=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_LAT_C=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\lat.obj" : $(SOURCE) $(DEP_CPP_LAT_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\hexvalue.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_HEXVA=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_HEXVA=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\hexvalue.obj" : $(SOURCE) $(DEP_CPP_HEXVA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_HEXVA=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_HEXVA=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\hexvalue.obj" : $(SOURCE) $(DEP_CPP_HEXVA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\expid.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_EXPID=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_EXPID=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\expid.obj" : $(SOURCE) $(DEP_CPP_EXPID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_EXPID=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_EXPID=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\expid.obj" : $(SOURCE) $(DEP_CPP_EXPID) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\nmea0183\Rmc.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_RMC_C=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_RMC_C=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\Rmc.obj" : $(SOURCE) $(DEP_CPP_RMC_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_RMC_C=\
	".\src\nmea0183\nmea0183.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/list.h"\
	".\src\nmea0183\nmea0183.hpp"\
	"\wx262\include\wx/defs.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	".\src\nmea0183\Sentence.hpp"\
	".\src\nmea0183\Response.hpp"\
	".\src\nmea0183\LatLong.hpp"\
	".\src\nmea0183\RMB.hpp"\
	".\src\nmea0183\Rmc.hpp"\
	
NODEP_CPP_RMC_C=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	

"$(INTDIR)\Rmc.obj" : $(SOURCE) $(DEP_CPP_RMC_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\wvschart.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_WVSCH=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\wvschart.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\chartbase.h"\
	".\include\bitmapo.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	
NODEP_CPP_WVSCH=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\wvschart.obj" : $(SOURCE) $(DEP_CPP_WVSCH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_WVSCH=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\wvschart.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\chartbase.h"\
	".\include\bitmapo.h"\
	".\include\bbox.h"\
	".\include\dymemdc.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	
NODEP_CPP_WVSCH=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	

"$(INTDIR)\wvschart.obj" : $(SOURCE) $(DEP_CPP_WVSCH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\about.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_ABOUT=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/textfile.h"\
	".\include\about.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/dynarray.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/iosfwrap.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/longlong.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/notebook.h"\
	"\wx262\include\wx/bookctrl.h"\
	"\wx262\include\wx/univ/notebook.h"\
	"\wx262\include\wx/msw/notebook.h"\
	"\wx262\include\wx/generic/notebook.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/choicebk.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	
NODEP_CPP_ABOUT=\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\os2\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\about.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_ABOUT=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/textfile.h"\
	".\include\about.h"\
	".\include\chart1.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/notebook.h"\
	"\wx262\include\wx/bookctrl.h"\
	"\wx262\include\wx/univ/notebook.h"\
	"\wx262\include\wx/msw/notebook.h"\
	"\wx262\include\wx/generic/notebook.h"\
	"\wx262\include\wx/choicebk.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	
NODEP_CPP_ABOUT=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\os2\notebook.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	

"$(INTDIR)\about.obj" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\wificlient.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_WIFIC=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\wificlient.h"\
	".\include\chart1.h"\
	".\include\statwin.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	
NODEP_CPP_WIFIC=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	

"$(INTDIR)\wificlient.obj" : $(SOURCE) $(DEP_CPP_WIFIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_WIFIC=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\wificlient.h"\
	".\include\chart1.h"\
	".\include\statwin.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	
NODEP_CPP_WIFIC=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	

"$(INTDIR)\wificlient.obj" : $(SOURCE) $(DEP_CPP_WIFIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\cutil.c
DEP_CPP_CUTIL=\
	".\include\cutil.h"\
	

"$(INTDIR)\cutil.obj" : $(SOURCE) $(DEP_CPP_CUTIL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\tri.c
DEP_CPP_TRI_C=\
	".\include\triangulate.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\tri.obj" : $(SOURCE) $(DEP_CPP_TRI_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygeom.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_MYGEO=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/mstream.h"\
	".\include\dychart.h"\
	".\include\mygeom.h"\
	".\include\triangulate.h"\
	{$(INCLUDE)}"\Gl\Gl.h"\
	{$(INCLUDE)}"\Gl\Glu.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/wxchar.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/longlong.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	".\include\s52s57.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	
NODEP_CPP_MYGEO=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	

"$(INTDIR)\mygeom.obj" : $(SOURCE) $(DEP_CPP_MYGEO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_MYGEO=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/mstream.h"\
	".\include\dychart.h"\
	".\include\mygeom.h"\
	".\include\triangulate.h"\
	{$(INCLUDE)}"\Gl\Gl.h"\
	{$(INCLUDE)}"\Gl\Glu.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	".\include\s52s57.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	
NODEP_CPP_MYGEO=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	

"$(INTDIR)\mygeom.obj" : $(SOURCE) $(DEP_CPP_MYGEO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s52cnsy.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_S52CN=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\s57chart.h"\
	".\include\s52plib.h"\
	".\include\S52utils.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\bbox.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/wfstream.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	".\include\dymemdc.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	".\include\bitmapo.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/ffile.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\gpc.h"\
	
NODEP_CPP_S52CN=\
	".\src\S52CS.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	

"$(INTDIR)\s52cnsy.obj" : $(SOURCE) $(DEP_CPP_S52CN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_S52CN=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\s57chart.h"\
	".\include\s52plib.h"\
	".\include\S52utils.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\bbox.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	".\include\dymemdc.h"\
	".\include\s52s57.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	".\include\bitmapo.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/ffile.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\gpc.h"\
	
NODEP_CPP_S52CN=\
	".\src\S52CS.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	

"$(INTDIR)\s52cnsy.obj" : $(SOURCE) $(DEP_CPP_S52CN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s52plib.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_S52PL=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\georef.h"\
	".\include\s52plib.h"\
	".\include\s57chart.h"\
	".\include\mygeom.h"\
	"\wx262\include\wx/image.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\s52s57.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/wfstream.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/generic/panelg.h"\
	".\include\bitmapo.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/ffile.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	
NODEP_CPP_S52PL=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	

"$(INTDIR)\s52plib.obj" : $(SOURCE) $(DEP_CPP_S52PL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_S52PL=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	".\include\dychart.h"\
	".\include\georef.h"\
	".\include\s52plib.h"\
	".\include\s57chart.h"\
	".\include\mygeom.h"\
	"\wx262\include\wx/image.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\s52s57.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/file.h"\
	"\wx262\include\wx/wfstream.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	".\include\bitmapo.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/ffile.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	
NODEP_CPP_S52PL=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	

"$(INTDIR)\s52plib.obj" : $(SOURCE) $(DEP_CPP_S52PL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s52utils.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_S52UT=\
	".\include\dychart.h"\
	".\include\S52utils.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	
NODEP_CPP_S52UT=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	

"$(INTDIR)\s52utils.obj" : $(SOURCE) $(DEP_CPP_S52UT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_S52UT=\
	".\include\dychart.h"\
	".\include\S52utils.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/msgout.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	
NODEP_CPP_S52UT=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	

"$(INTDIR)\s52utils.obj" : $(SOURCE) $(DEP_CPP_S52UT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\s57chart.cpp

!IF  "$(CFG)" == "OPENCP - Win32 Release"

DEP_CPP_S57CH=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/image.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/textfile.h"\
	".\include\dychart.h"\
	".\include\s52s57.h"\
	".\include\s52plib.h"\
	".\include\s57chart.h"\
	".\include\nmea.h"\
	".\include\mygeom.h"\
	".\include\cutil.h"\
	{$(INCLUDE)}"\cpl_csv.h"\
	"\wx262\include\wx/arrimpl.cpp"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/wxchar.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\lib\vc_lib\msw\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/longlong.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/wfstream.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/generic/panelg.h"\
	".\include\bitmapo.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/ffile.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/msw/dib.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\cpl_string.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	
NODEP_CPP_S57CH=\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	

"$(INTDIR)\s57chart.obj" : $(SOURCE) $(DEP_CPP_S57CH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "OPENCP - Win32 Debug"

DEP_CPP_S57CH=\
	"\wx262\include\wx/wxprec.h"\
	"\wx262\include\wx/wx.h"\
	"\wx262\include\wx/image.h"\
	"\wx262\include\wx/tokenzr.h"\
	"\wx262\include\wx/textfile.h"\
	".\include\dychart.h"\
	".\include\s52s57.h"\
	".\include\s52plib.h"\
	".\include\s57chart.h"\
	".\include\nmea.h"\
	".\include\mygeom.h"\
	".\include\cutil.h"\
	{$(INCLUDE)}"\cpl_csv.h"\
	"\wx262\include\wx/arrimpl.cpp"\
	"\wx262\include\wx/defs.h"\
	"\wx262\include\wx/wxchar.h"\
	"\wx262\include\wx/msw/wrapwin.h"\
	"\wx262\include\wx/platform.h"\
	"\wx262\include\wx/features.h"\
	"\wx262\include\wx/version.h"\
	"\wx262\include\wx/dlimpexp.h"\
	"\wx262\include\wx/debug.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	"\wx262\lib\vc_lib\mswd\wx/setup.h"\
	"\wx262\include\wx/chkconf.h"\
	"\wx262\include\wx/msw/wince/libraries.h"\
	"\wx262\include\wx/msw/gccpriv.h"\
	"\wx262\include\wx/palmos/chkconf.h"\
	"\wx262\include\wx/msw/wince/chkconf.h"\
	"\wx262\include\wx/msw/chkconf.h"\
	"\wx262\include\wx/msw/winundef.h"\
	"\wx262\include\wx/object.h"\
	"\wx262\include\wx/dynarray.h"\
	"\wx262\include\wx/list.h"\
	"\wx262\include\wx/hash.h"\
	"\wx262\include\wx/string.h"\
	"\wx262\include\wx/intl.h"\
	"\wx262\include\wx/log.h"\
	"\wx262\include\wx/event.h"\
	"\wx262\include\wx/app.h"\
	"\wx262\include\wx/utils.h"\
	"\wx262\include\wx/stream.h"\
	"\wx262\include\wx/window.h"\
	"\wx262\include\wx/panel.h"\
	"\wx262\include\wx/frame.h"\
	"\wx262\include\wx/dc.h"\
	"\wx262\include\wx/dcclient.h"\
	"\wx262\include\wx/dcmemory.h"\
	"\wx262\include\wx/dcprint.h"\
	"\wx262\include\wx/dcscreen.h"\
	"\wx262\include\wx/button.h"\
	"\wx262\include\wx/memory.h"\
	"\wx262\include\wx/xti.h"\
	"\wx262\include\wx/msw/msvcrt.h"\
	"\wx262\include\wx/msgout.h"\
	"\wx262\include\wx/flags.h"\
	"\wx262\include\wx/arrstr.h"\
	"\wx262\include\wx/hashmap.h"\
	"\wx262\include\wx/beforestd.h"\
	"\wx262\include\wx/afterstd.h"\
	{$(INCLUDE)}"\Strings.h"\
	"\wx262\include\wx/buffer.h"\
	"\wx262\include\wx/strconv.h"\
	"\wx262\include\wx/iosfwrap.h"\
	"\wx262\include\wx/fontenc.h"\
	"\wx262\include\wx/generic/logg.h"\
	"\wx262\include\wx/clntdata.h"\
	"\wx262\include\wx/gdicmn.h"\
	"\wx262\include\wx/cursor.h"\
	"\wx262\include\wx/thread.h"\
	"\wx262\include\wx/vector.h"\
	"\wx262\include\wx/palmos/cursor.h"\
	"\wx262\include\wx/msw/cursor.h"\
	"\wx262\include\wx/palmos/gdiimage.h"\
	"\wx262\include\wx/gdiobj.h"\
	"\wx262\include\wx/palmos/gdiobj.h"\
	"\wx262\include\wx/msw/gdiobj.h"\
	"\wx262\include\wx/msw/gdiimage.h"\
	"\wx262\include\wx/vidmode.h"\
	"\wx262\include\wx/build.h"\
	"\wx262\include\wx/init.h"\
	"\wx262\include\wx/palmos/app.h"\
	"\wx262\include\wx/msw/app.h"\
	"\wx262\include\wx/univ/theme.h"\
	"\wx262\include\wx/icon.h"\
	"\wx262\include\wx/iconloc.h"\
	"\wx262\include\wx/palmos/icon.h"\
	"\wx262\include\wx/msw/icon.h"\
	"\wx262\include\wx/filefn.h"\
	"\wx262\include\wx/longlong.h"\
	{$(INCLUDE)}"\Dirent.h"\
	"\wx262\include\wx/msw/wince/time.h"\
	"\wx262\include\wx/msw/private.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	"\wx262\include\wx/msw/microwin.h"\
	"\wx262\include\wx/msw/mslu.h"\
	"\wx262\include\wx/colour.h"\
	"\wx262\include\wx/palmos/colour.h"\
	"\wx262\include\wx/msw/colour.h"\
	"\wx262\include\wx/font.h"\
	"\wx262\include\wx/region.h"\
	"\wx262\include\wx/validate.h"\
	"\wx262\include\wx/palette.h"\
	"\wx262\include\wx/accel.h"\
	"\wx262\include\wx/access.h"\
	"\wx262\include\wx/palmos/window.h"\
	"\wx262\include\wx/msw/window.h"\
	"\wx262\include\wx/univ/window.h"\
	"\wx262\include\wx/palmos/font.h"\
	"\wx262\include\wx/msw/font.h"\
	"\wx262\include\wx/palmos/region.h"\
	"\wx262\include\wx/msw/region.h"\
	"\wx262\include\wx/palmos/palette.h"\
	"\wx262\include\wx/msw/palette.h"\
	"\wx262\include\wx/generic/paletteg.h"\
	"\wx262\include\wx/generic/accel.h"\
	"\wx262\include\wx/msw/accel.h"\
	"\wx262\include\wx/variant.h"\
	"\wx262\include\wx/msw/ole/access.h"\
	"\wx262\include\wx/datetime.h"\
	"\wx262\include\wx/db.h"\
	"\wx262\include\wx/isql.h"\
	"\wx262\include\wx/isqlext.h"\
	"\wx262\include\wx/bitmap.h"\
	"\wx262\include\wx/palmos/bitmap.h"\
	"\wx262\include\wx/msw/bitmap.h"\
	"\wx262\include\wx/generic/panelg.h"\
	"\wx262\include\wx/containr.h"\
	"\wx262\include\wx/toplevel.h"\
	"\wx262\include\wx/univ/frame.h"\
	"\wx262\include\wx/palmos/frame.h"\
	"\wx262\include\wx/msw/frame.h"\
	"\wx262\include\wx/iconbndl.h"\
	"\wx262\include\wx/palmos/toplevel.h"\
	"\wx262\include\wx/msw/toplevel.h"\
	"\wx262\include\wx/univ/toplevel.h"\
	"\wx262\include\wx/univ/inpcons.h"\
	"\wx262\include\wx/univ/inphand.h"\
	"\wx262\include\wx/brush.h"\
	"\wx262\include\wx/pen.h"\
	"\wx262\include\wx/math.h"\
	"\wx262\include\wx/palmos/dc.h"\
	"\wx262\include\wx/msw/dc.h"\
	"\wx262\include\wx/palmos/brush.h"\
	"\wx262\include\wx/msw/brush.h"\
	"\wx262\include\wx/palmos/pen.h"\
	"\wx262\include\wx/msw/pen.h"\
	"\wx262\include\wx/palmos/dcclient.h"\
	"\wx262\include\wx/msw/dcclient.h"\
	"\wx262\include\wx/palmos/dcmemory.h"\
	"\wx262\include\wx/msw/dcmemory.h"\
	"\wx262\include\wx/palmos/dcprint.h"\
	"\wx262\include\wx/msw/dcprint.h"\
	"\wx262\include\wx/cmndata.h"\
	"\wx262\include\wx/encinfo.h"\
	"\wx262\include\wx/palmos/dcscreen.h"\
	"\wx262\include\wx/msw/dcscreen.h"\
	"\wx262\include\wx/control.h"\
	"\wx262\include\wx/univ/button.h"\
	"\wx262\include\wx/msw/button.h"\
	"\wx262\include\wx/univ/control.h"\
	"\wx262\include\wx/palmos/control.h"\
	"\wx262\include\wx/msw/control.h"\
	"\wx262\include\wx/imagbmp.h"\
	"\wx262\include\wx/imagpng.h"\
	"\wx262\include\wx/imaggif.h"\
	"\wx262\include\wx/imagpcx.h"\
	"\wx262\include\wx/imagjpeg.h"\
	"\wx262\include\wx/imagtiff.h"\
	"\wx262\include\wx/imagpnm.h"\
	"\wx262\include\wx/imagxpm.h"\
	"\wx262\include\wx/imagiff.h"\
	"\wx262\include\wx/textbuf.h"\
	"\wx262\include\wx/file.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	".\include\gpc.h"\
	".\include\bbox.h"\
	"\wx262\include\wx/matrix.h"\
	"\wx262\include\wx/geometry.h"\
	"\wx262\include\wx/generic/progdlgg.h"\
	".\include\chartbase.h"\
	"\wx262\include\wx/dir.h"\
	"\wx262\include\wx/filename.h"\
	"\wx262\include\wx/wfstream.h"\
	{$(INCLUDE)}"\ogrsf_frmts.h"\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\gdal.h"\
	".\include\dymemdc.h"\
	"\wx262\include\wx/dialog.h"\
	"\wx262\include\wx/univ/dialog.h"\
	"\wx262\include\wx/palmos/dialog.h"\
	"\wx262\include\wx/msw/dialog.h"\
	".\include\bitmapo.h"\
	".\include\chcanv.h"\
	".\include\chart1.h"\
	".\include\tcmgr.h"\
	"\wx262\include\wx/print.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	"\wx262\include\wx/msw/printwin.h"\
	"\wx262\include\wx/generic/printps.h"\
	"\wx262\include\wx/prntbase.h"\
	"\wx262\include\wx/scrolwin.h"\
	"\wx262\include\wx/generic/scrolwin.h"\
	"\wx262\include\wx/ffile.h"\
	{$(INCLUDE)}"\ogr_feature.h"\
	{$(INCLUDE)}"\ogr_geometry.h"\
	{$(INCLUDE)}"\ogr_core.h"\
	{$(INCLUDE)}"\ogr_spatialref.h"\
	{$(INCLUDE)}"\ogr_srs_api.h"\
	"\wx262\include\wx/msw/dib.h"\
	".\include\sercomm.h"\
	"\wx262\include\wx/socket.h"\
	"\wx262\include\wx/sckaddr.h"\
	"\wx262\include\wx/gsocket.h"\
	"\wx262\include\wx/msw/gsockmsw.h"\
	"\wx262\include\wx/unix/gsockunx.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\cpl_string.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	
NODEP_CPP_S57CH=\
	".\..\..\..\wx262\include\wx\wx\mac\carbon\config_xcode.h"\
	".\..\..\..\wx262\include\wx\wx\mac\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\motif\chkconf.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\log.h"\
	".\..\..\..\wx262\include\wx\wx\motif\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\x11\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\mac\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\os2\cursor.h"\
	".\..\..\..\wx262\include\wx\wx\motif\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\x11\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\os2\gdiobj.h"\
	".\..\..\..\wx262\include\wx\wx\motif\app.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\app.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\app.h"\
	".\..\..\..\wx262\include\wx\wx\x11\app.h"\
	".\..\..\..\wx262\include\wx\wx\mac\app.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\app.h"\
	".\..\..\..\wx262\include\wx\wx\os2\app.h"\
	".\..\..\..\wx262\include\wx\wx\motif\icon.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\icon.h"\
	".\..\..\..\wx262\include\wx\wx\x11\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\icon.h"\
	".\..\..\..\wx262\include\wx\wx\mac\icon.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\icon.h"\
	".\..\..\..\wx262\include\wx\wx\os2\private.h"\
	".\..\..\..\wx262\include\wx\wx\motif\colour.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\colour.h"\
	".\..\..\..\wx262\include\wx\wx\x11\colour.h"\
	".\..\..\..\wx262\include\wx\wx\mac\colour.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\colour.h"\
	".\..\..\..\wx262\include\wx\wx\os2\colour.h"\
	".\..\..\..\wx262\include\wx\wx\motif\window.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\window.h"\
	".\..\..\..\wx262\include\wx\wx\x11\window.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\window.h"\
	".\..\..\..\wx262\include\wx\wx\mac\window.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\window.h"\
	".\..\..\..\wx262\include\wx\wx\os2\window.h"\
	".\..\..\..\wx262\include\wx\wx\motif\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\font.h"\
	".\..\..\..\wx262\include\wx\wx\x11\font.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\font.h"\
	".\..\..\..\wx262\include\wx\wx\mac\font.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\font.h"\
	".\..\..\..\wx262\include\wx\wx\os2\font.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\region.h"\
	".\..\..\..\wx262\include\wx\wx\x11\region.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\region.h"\
	".\..\..\..\wx262\include\wx\wx\mac\region.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\region.h"\
	".\..\..\..\wx262\include\wx\wx\os2\region.h"\
	".\..\..\..\wx262\include\wx\wx\motif\palette.h"\
	".\..\..\..\wx262\include\wx\wx\x11\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\palette.h"\
	".\..\..\..\wx262\include\wx\wx\mac\palette.h"\
	".\..\..\..\wx262\include\wx\wx\os2\palette.h"\
	".\..\..\..\wx262\include\wx\wx\motif\accel.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\accel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\accel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\accel.h"\
	".\..\..\..\wx262\include\wx\wx\generic\access.h"\
	".\..\..\..\wx262\include\wx\wx\x11\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\mac\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\os2\bitmap.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\frame.h"\
	".\..\..\..\wx262\include\wx\wx\motif\frame.h"\
	".\..\..\..\wx262\include\wx\wx\mac\frame.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\frame.h"\
	".\..\..\..\wx262\include\wx\wx\os2\frame.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\x11\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\mac\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\os2\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\toplevel.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dc.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dc.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dc.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dc.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dc.h"\
	".\..\..\..\wx262\include\wx\wx\x11\brush.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\brush.h"\
	".\..\..\..\wx262\include\wx\wx\mac\brush.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\brush.h"\
	".\..\..\..\wx262\include\wx\wx\os2\brush.h"\
	".\..\..\..\wx262\include\wx\wx\x11\pen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\pen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\pen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\pen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\pen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcclient.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcmemory.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcprint.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\x11\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mgl\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dcscreen.h"\
	".\..\..\..\wx262\include\wx\wx\motif\button.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\button.h"\
	".\..\..\..\wx262\include\wx\wx\motif\control.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\control.h"\
	".\..\..\..\wx262\include\wx\wx\mac\control.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\control.h"\
	".\..\..\..\wx262\include\wx\wx\os2\control.h"\
	".\..\..\..\wx262\include\wx\wx\motif\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\mac\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\cocoa\dialog.h"\
	".\..\..\..\wx262\include\wx\wx\os2\dialog.h"\
	".\include\wx\x11\private.h"\
	".\..\..\..\wx262\include\wx\wx\mac\printmac.h"\
	".\..\..\..\wx262\include\wx\wx\os2\printos2.h"\
	".\..\..\..\wx262\include\wx\wx\gtk\scrolwin.h"\
	".\..\..\..\wx262\include\wx\wx\mac\gsockmac.h"\
	

"$(INTDIR)\s57chart.obj" : $(SOURCE) $(DEP_CPP_S57CH) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfutils.cpp
DEP_CPP_DDFUT=\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ddfutils.obj" : $(SOURCE) $(DEP_CPP_DDFUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddffielddefn.cpp
DEP_CPP_DDFFI=\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\cpl_string.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ddffielddefn.obj" : $(SOURCE) $(DEP_CPP_DDFFI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfmodule.cpp
DEP_CPP_DDFMO=\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ddfmodule.obj" : $(SOURCE) $(DEP_CPP_DDFMO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfrecord.cpp
DEP_CPP_DDFRE=\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ddfrecord.obj" : $(SOURCE) $(DEP_CPP_DDFRE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddfsubfielddefn.cpp
DEP_CPP_DDFSU=\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ddfsubfielddefn.obj" : $(SOURCE) $(DEP_CPP_DDFSU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\myiso8211\ddffield.cpp
DEP_CPP_DDFFIE=\
	".\include\iso8211.h"\
	{$(INCLUDE)}"\cpl_conv.h"\
	{$(INCLUDE)}"\cpl_port.h"\
	{$(INCLUDE)}"\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\cpl_vsi.h"\
	{$(INCLUDE)}"\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ddffield.obj" : $(SOURCE) $(DEP_CPP_DDFFIE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\swq.c
DEP_CPP_SWQ_C=\
	".\src\mygdal\swq.h"\
	

"$(INTDIR)\swq.obj" : $(SOURCE) $(DEP_CPP_SWQ_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_csv.cpp
DEP_CPP_CPL_C=\
	".\src\mygdal\cpl_csv.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_csv.obj" : $(SOURCE) $(DEP_CPP_CPL_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_dir.cpp
DEP_CPP_CPL_D=\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	{$(INCLUDE)}"\Dirent.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	

"$(INTDIR)\cpl_dir.obj" : $(SOURCE) $(DEP_CPP_CPL_D) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_error.cpp
DEP_CPP_CPL_E=\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_error.obj" : $(SOURCE) $(DEP_CPP_CPL_E) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_findfile.cpp
DEP_CPP_CPL_F=\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_findfile.obj" : $(SOURCE) $(DEP_CPP_CPL_F) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_minixml.cpp
DEP_CPP_CPL_M=\
	".\src\mygdal\cpl_minixml.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_vsi.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_minixml.obj" : $(SOURCE) $(DEP_CPP_CPL_M) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_path.cpp
DEP_CPP_CPL_P=\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_path.obj" : $(SOURCE) $(DEP_CPP_CPL_P) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_string.cpp
DEP_CPP_CPL_S=\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_string.obj" : $(SOURCE) $(DEP_CPP_CPL_S) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_vsisimple.cpp
DEP_CPP_CPL_V=\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_vsisimple.obj" : $(SOURCE) $(DEP_CPP_CPL_V) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cplgetsymbol.cpp
DEP_CPP_CPLGE=\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cplgetsymbol.obj" : $(SOURCE) $(DEP_CPP_CPLGE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ddfrecordindex.cpp
DEP_CPP_DDFREC=\
	".\src\mygdal\s57.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ddfrecordindex.obj" : $(SOURCE) $(DEP_CPP_DDFREC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\gdal_misc.cpp
DEP_CPP_GDAL_=\
	".\src\mygdal\gdal_priv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\gdal.h"\
	".\src\mygdal\gdal_frmts.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\gdal_misc.obj" : $(SOURCE) $(DEP_CPP_GDAL_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\gml2ogrgeometry.cpp
DEP_CPP_GML2O=\
	".\src\mygdal\cpl_minixml.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_srs_api.h"\
	

"$(INTDIR)\gml2ogrgeometry.obj" : $(SOURCE) $(DEP_CPP_GML2O) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_attrind.cpp
DEP_CPP_OGR_A=\
	".\src\mygdal\ogr_attrind.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr_attrind.obj" : $(SOURCE) $(DEP_CPP_OGR_A) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_fromepsg.cpp
DEP_CPP_OGR_F=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_csv.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr_fromepsg.obj" : $(SOURCE) $(DEP_CPP_OGR_F) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_gensql.cpp
DEP_CPP_OGR_G=\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_gensql.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\swq.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_srs_api.h"\
	

"$(INTDIR)\ogr_gensql.obj" : $(SOURCE) $(DEP_CPP_OGR_G) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_nullattrind.cpp
DEP_CPP_OGR_N=\
	".\src\mygdal\ogr_attrind.h"\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	

"$(INTDIR)\ogr_nullattrind.obj" : $(SOURCE) $(DEP_CPP_OGR_N) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_srs_dict.cpp
DEP_CPP_OGR_S=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr_srs_dict.obj" : $(SOURCE) $(DEP_CPP_OGR_S) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_srs_esri.cpp
DEP_CPP_OGR_SR=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\cpl_csv.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr_srs_esri.obj" : $(SOURCE) $(DEP_CPP_OGR_SR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_srs_proj4.cpp
DEP_CPP_OGR_SRS=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr_srs_proj4.obj" : $(SOURCE) $(DEP_CPP_OGR_SRS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_srs_xml.cpp
DEP_CPP_OGR_SRS_=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\cpl_minixml.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr_srs_xml.obj" : $(SOURCE) $(DEP_CPP_OGR_SRS_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr_srsnode.cpp
DEP_CPP_OGR_SRSN=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr_srsnode.obj" : $(SOURCE) $(DEP_CPP_OGR_SRSN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogr2gmlgeometry.cpp
DEP_CPP_OGR2G=\
	".\src\mygdal\cpl_minixml.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogr2gmlgeometry.obj" : $(SOURCE) $(DEP_CPP_OGR2G) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ograssemblepolygon.cpp
DEP_CPP_OGRAS=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ograssemblepolygon.obj" : $(SOURCE) $(DEP_CPP_OGRAS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrct.cpp
DEP_CPP_OGRCT=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_vsi.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	
NODEP_CPP_OGRCT=\
	".\src\mygdal\proj_api.h"\
	

"$(INTDIR)\ogrct.obj" : $(SOURCE) $(DEP_CPP_OGRCT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrcurve.cpp
DEP_CPP_OGRCU=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrcurve.obj" : $(SOURCE) $(DEP_CPP_OGRCU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrdatasource.cpp
DEP_CPP_OGRDA=\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_gensql.h"\
	".\src\mygdal\ogr_attrind.h"\
	".\src\mygdal\swq.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrdatasource.obj" : $(SOURCE) $(DEP_CPP_OGRDA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrfeature.cpp
DEP_CPP_OGRFE=\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrfeature.obj" : $(SOURCE) $(DEP_CPP_OGRFE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrfeaturedefn.cpp
DEP_CPP_OGRFEA=\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrfeaturedefn.obj" : $(SOURCE) $(DEP_CPP_OGRFEA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrfeaturequery.cpp
DEP_CPP_OGRFEAT=\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_attrind.h"\
	".\src\mygdal\swq.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrfeaturequery.obj" : $(SOURCE) $(DEP_CPP_OGRFEAT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrfielddefn.cpp
DEP_CPP_OGRFI=\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrfielddefn.obj" : $(SOURCE) $(DEP_CPP_OGRFI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrgeometry.cpp
DEP_CPP_OGRGE=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrgeometry.obj" : $(SOURCE) $(DEP_CPP_OGRGE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrgeometrycollection.cpp
DEP_CPP_OGRGEO=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrgeometrycollection.obj" : $(SOURCE) $(DEP_CPP_OGRGEO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrgeometryfactory.cpp
DEP_CPP_OGRGEOM=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrgeometryfactory.obj" : $(SOURCE) $(DEP_CPP_OGRGEOM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrlayer.cpp
DEP_CPP_OGRLA=\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_attrind.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrlayer.obj" : $(SOURCE) $(DEP_CPP_OGRLA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrlinearring.cpp
DEP_CPP_OGRLI=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrlinearring.obj" : $(SOURCE) $(DEP_CPP_OGRLI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrlinestring.cpp
DEP_CPP_OGRLIN=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrlinestring.obj" : $(SOURCE) $(DEP_CPP_OGRLIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrmultilinestring.cpp
DEP_CPP_OGRMU=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrmultilinestring.obj" : $(SOURCE) $(DEP_CPP_OGRMU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrmultipoint.cpp
DEP_CPP_OGRMUL=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrmultipoint.obj" : $(SOURCE) $(DEP_CPP_OGRMUL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrmultipolygon.cpp
DEP_CPP_OGRMULT=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrmultipolygon.obj" : $(SOURCE) $(DEP_CPP_OGRMULT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrpoint.cpp
DEP_CPP_OGRPO=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrpoint.obj" : $(SOURCE) $(DEP_CPP_OGRPO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrpolygon.cpp
DEP_CPP_OGRPOL=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrpolygon.obj" : $(SOURCE) $(DEP_CPP_OGRPOL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrs57datasource.cpp
DEP_CPP_OGRS5=\
	".\src\mygdal\ogr_s57.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\s57.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrs57datasource.obj" : $(SOURCE) $(DEP_CPP_OGRS5) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrs57driver.cpp
DEP_CPP_OGRS57=\
	".\src\mygdal\ogr_s57.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\s57.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrs57driver.obj" : $(SOURCE) $(DEP_CPP_OGRS57) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrs57layer.cpp
DEP_CPP_OGRS57L=\
	".\src\mygdal\ogr_s57.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\s57.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrs57layer.obj" : $(SOURCE) $(DEP_CPP_OGRS57L) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrsfdriver.cpp
DEP_CPP_OGRSF=\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrsfdriver.obj" : $(SOURCE) $(DEP_CPP_OGRSF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrsfdriverregistrar.cpp
DEP_CPP_OGRSFD=\
	".\src\mygdal\ogrsf_frmts.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrsfdriverregistrar.obj" : $(SOURCE) $(DEP_CPP_OGRSFD) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrspatialreference.cpp
DEP_CPP_OGRSP=\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrspatialreference.obj" : $(SOURCE) $(DEP_CPP_OGRSP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\ogrutils.cpp
DEP_CPP_OGRUT=\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_p.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\ogrutils.obj" : $(SOURCE) $(DEP_CPP_OGRUT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57classregistrar.cpp
DEP_CPP_S57CL=\
	".\src\mygdal\s57.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	
NODEP_CPP_S57CL=\
	".\src\mygdal\s57tables.h"\
	

"$(INTDIR)\s57classregistrar.obj" : $(SOURCE) $(DEP_CPP_S57CL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57featuredefns.cpp
DEP_CPP_S57FE=\
	".\src\mygdal\s57.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\s57featuredefns.obj" : $(SOURCE) $(DEP_CPP_S57FE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57filecollector.cpp
DEP_CPP_S57FI=\
	".\src\mygdal\s57.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\s57filecollector.obj" : $(SOURCE) $(DEP_CPP_S57FI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57reader.cpp
DEP_CPP_S57RE=\
	".\src\mygdal\s57.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\s57reader.obj" : $(SOURCE) $(DEP_CPP_S57RE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\s57writer.cpp
DEP_CPP_S57WR=\
	".\src\mygdal\s57.h"\
	".\src\mygdal\ogr_api.h"\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\ogr_feature.h"\
	".\src\mygdal\iso8211.h"\
	".\src\mygdal\ogr_geometry.h"\
	".\src\mygdal\ogr_core.h"\
	".\src\mygdal\ogr_spatialref.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	".\src\mygdal\ogr_srs_api.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\s57writer.obj" : $(SOURCE) $(DEP_CPP_S57WR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\src\mygdal\cpl_conv.cpp
DEP_CPP_CPL_CO=\
	".\src\mygdal\cpl_conv.h"\
	".\src\mygdal\cpl_string.h"\
	".\src\mygdal\cpl_port.h"\
	".\src\mygdal\cpl_vsi.h"\
	".\src\mygdal\cpl_error.h"\
	".\src\mygdal\cpl_config.h"\
	{$(INCLUDE)}"\Strings.h"\
	{$(INCLUDE)}"\Sys\Stat.h"\
	{$(INCLUDE)}"\Sys\Types.h"\
	

"$(INTDIR)\cpl_conv.obj" : $(SOURCE) $(DEP_CPP_CPL_CO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################

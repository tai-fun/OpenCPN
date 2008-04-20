/******************************************************************************
 * $Id: s57chart.h,v 1.13 2008/04/20 21:04:36 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  S57 Chart Object
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) $YEAR$ by $AUTHOR$   *
 *   $EMAIL$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *
<<<<<<< s57chart.h
 * $Log: s57chart.h,v $
 * Revision 1.13  2008/04/20 21:04:36  bdbcat
 * Cleanup
 *
 * Revision 1.12  2008/04/10 01:01:32  bdbcat
 * Cleanup
 *
 * Revision 1.11  2008/03/30 23:24:11  bdbcat
 * Cleanup
 *
=======
 * $Log: s57chart.h,v $
 * Revision 1.13  2008/04/20 21:04:36  bdbcat
 * Cleanup
 *
 * Revision 1.12  2008/04/10 01:01:32  bdbcat
 * Cleanup
 *
 * Revision 1.11  2008/03/30 23:24:11  bdbcat
 * Cleanup
 *
 * Revision 1.10  2008/01/12 06:19:18  bdbcat
 * Update for Mac OSX/Unicode
 *
>>>>>>> 1.10
 * Revision 1.9  2008/01/02 21:06:00  bdbcat
 * Update for Version 1.2.2
 *
 * Revision 1.8  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.7  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.6  2007/03/02 02:07:11  dsr
 * Convert to UTM Projection
 *
 * Revision 1.5  2006/10/08 00:36:25  dsr
 * no message
 *
 * Revision 1.4  2006/10/07 03:50:54  dsr
 * *** empty log message ***
 *
 * Revision 1.3  2006/10/01 03:24:40  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 *
 */



#ifndef __S57CHART_H__
#define __S57CHART_H__

#include <wx/wx.h>
#include "wx/generic/progdlgg.h"
#include "bbox.h"
#include "chartbase.h"
#include "wx/dir.h"
#include "wx/filename.h"
#include "wx/file.h"
#include "wx/stream.h"
#include "wx/wfstream.h"

#include <ogrsf_frmts.h>

#include "iso8211.h"

#include "gdal.h"

#include "s52s57.h"                 //types
#include "ogr_s57.h"

// ----------------------------------------------------------------------------
// Useful Prototypes
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// S57 Utility Prototypes
// ----------------------------------------------------------------------------
extern "C" int  s57_initialize(const wxString& csv_dir, FILE *flog);
extern "C" bool s57_GetChartExtent(const wxString& FullPath, Extent *pext);


//----------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Fwd Defns
//----------------------------------------------------------------------------

class ChartBase;
class ViewPort;
class ocpnBitmap;
class PixelCache;

#include <wx/dynarray.h>

// Define the Array of S57Obj
WX_DECLARE_OBJARRAY(S57Obj, ArrayOfS57Obj);

// And also a list
WX_DECLARE_LIST(S57Obj, ListOfS57Obj);

//----------------------------------------------------------------------------
// s57 Chart object class
//----------------------------------------------------------------------------
class s57chart : public ChartBase
{
public:
      s57chart();
      ~s57chart();

      InitReturn Init( const wxString& name, ChartInitFlag flags, ColorScheme cs );

//    Accessors

      ThumbData *GetThumbData(int tnx, int tny, float lat, float lon);
      ThumbData *GetThumbData() {return pThumbData;}
      bool UpdateThumbData(float lat, float lon);

      float GetNativeScale(){return NativeScale;}
      float GetChartSkew(){return 0.0;}

      void InvalidateCache();

      void RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type);
      void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion);

      // Todo be smarter here, look at pDib, etc....
      virtual bool IsCacheValid(){ return false; }


      void GetPointPix(ObjRazRules *rzRules, float rlat, float rlon, wxPoint *r);
      void GetPixPoint(int pixx, int pixy, double *plat, double *plon, ViewPort *vpt);

      void SetVPParms(ViewPort *pvpt);
      void SetFullExtent(Extent& ext);
      void GetChartExtent(Extent *pext);

      void SetColorScheme(ColorScheme cs, bool bApplyImmediate);
      void UpdateLUPs();

      ListOfS57Obj *GetObjListAtLatLon(float lat, float lon, float select_radius, ViewPort *VPoint);
      bool DoesLatLonSelectObject(float lat, float lon, float select_radius, S57Obj *obj);
      bool IsPointInObjArea(float lat, float lon, float select_radius, S57Obj *obj);
      wxString *CreateObjDescription(const S57Obj *obj);
      wxString *GetAttributeDecode(wxString& att, int ival);

      //    Access to raw ENC DataSet
      bool InitENCMinimal( const wxString& FullPath );
      int GetENCScale();
      OGRFeature *GetChartFirstM_COVR(int &catcov);
      OGRFeature *GetChartNextM_COVR(int &catcov);

      //    DEPCNT VALDCO array access
      bool GetNearestSafeContour(double safe_cnt, double &next_safe_cnt);

      ListOfS57Obj *GetAssociatedObjects(S57Obj *obj);


// Public data
//Todo Accessors here
      //  Object arrays used by S52PLIB TOPMAR rendering logic
      wxArrayPtrVoid *pFloatingATONArray;
      wxArrayPtrVoid *pRigidATONArray;

      double        ref_lat, ref_lon;             // Common reference point, derived from FullExtent

private:
      void DoRenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, RenderTypeEnum option);

      int DCRenderRect(wxMemoryDC& dcinput, ViewPort& vp, wxRect *rect);
      bool DCRenderLPB(wxMemoryDC& dcinput, ViewPort& vp, wxRect* rect);

      int BuildS57File(const wxString& FullPath);
      int BuildRAZFromS57File(const wxString& FullPath);

      void CreateSENCRecord( OGRFeature *pFeature, FILE * fpOut, int mode );

      void GetChartNameFromTXT(const wxString& FullPath, wxString &Name);
      bool BuildThumbnail(const wxString &bmpname);

      void FreeObjectsAndRules();
      const char *getName(OGRFeature *feature);
      int GetUpdateFileArray(const wxString& DirName, wxArrayString *UpFiles);
      int CountUpdates( const wxString& DirName, wxString &LastUpdateDate);

      int _insertRules(S57Obj *obj, LUPrec *LUP);

      int my_fgets( char *buf, int buf_len_max, wxBufferedInputStream& ifs );


 // Private Data
      wxString    *m_pcsv_locn;
      int         nGeoRecords;
      float       NativeScale;

      ViewPort    last_vp;

      char        *hdr_buf;
      char        *mybuf_ptr;
      int         hdr_len;
      wxFileName  *pS57FileName;
      ObjRazRules *razRules[PRIO_NUM][LUPNAME_NUM];

      Extent      FullExtent;

      wxArrayString *tmpup_array;
      PixelCache   *pDIB;

      bool         bGLUWarningSent;
      Col_Scheme_t m_S52_color_index;

//  SM Projection parms
      double     easting_vp_center, northing_vp_center;
      double    x_vp_center, y_vp_center;
      double    view_scale_ppm;
      double    prev_easting_ul, prev_northing_ul;
      double    prev_easting_lr, prev_northing_lr;

//  Raw ENC DataSet members
      OGRS57DataSource  *m_pENCDS;

//  DEPCNT VALDCO array members
      int         m_nvaldco;
      int         m_nvaldco_alloc;
      double       *m_pvaldco_array;


};

#endif

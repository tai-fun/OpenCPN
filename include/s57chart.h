/******************************************************************************
 * $Id: s57chart.h,v 1.17 2008/12/09 03:40:42 bdbcat Exp $
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
 * $Log: s57chart.h,v $
 * Revision 1.17  2008/12/09 03:40:42  bdbcat
 * Add cm93 support
 *
 * Revision 1.16  2008/10/23 23:33:10  bdbcat
 * Cleanup
 *
 * Revision 1.15  2008/08/26 13:49:53  bdbcat
 * Better color scheme support
 *
 * Revision 1.14  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
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

enum
{
      BUILD_SENC_OK,
      BUILD_SENC_NOK_RETRY,
      BUILD_SENC_NOK_PERMANENT
};

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

      virtual InitReturn Init( const wxString& name, ChartInitFlag flags, ColorScheme cs );

//    Accessors

      ThumbData *GetThumbData(int tnx, int tny, float lat, float lon);
      ThumbData *GetThumbData() {return pThumbData;}
      bool UpdateThumbData(float lat, float lon);

      int GetNativeScale(){return m_Chart_Scale;}
      void SetNativeScale(int s){m_Chart_Scale = s;}

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
      bool GetChartExtent(Extent *pext);

      void SetColorScheme(ColorScheme cs, bool bApplyImmediate);
      void UpdateLUPs();

      ListOfS57Obj *GetObjListAtLatLon(float lat, float lon, float select_radius, ViewPort *VPoint);
      bool DoesLatLonSelectObject(float lat, float lon, float select_radius, S57Obj *obj);
      bool IsPointInObjArea(float lat, float lon, float select_radius, S57Obj *obj);
      wxString *CreateObjDescription(const S57Obj *obj);
      wxString *GetAttributeDecode(wxString& att, int ival);

      wxFileName GetSENCFileName(){ return m_SENCFileName; }
      void SetSENCFileName(wxFileName fn){ m_SENCFileName = fn;}

      int BuildRAZFromSENCFile(const wxString& SENCPath);

      //    Initialize from an existing SENC file
      bool InitFromSENCMinimal( const wxString& FullPath );

      //    DEPCNT VALDCO array access
      bool GetNearestSafeContour(double safe_cnt, double &next_safe_cnt);

      ListOfS57Obj *GetAssociatedObjects(S57Obj *obj);


// Public data
//Todo Accessors here
      //  Object arrays used by S52PLIB TOPMAR rendering logic
      wxArrayPtrVoid *pFloatingATONArray;
      wxArrayPtrVoid *pRigidATONArray;

      double        ref_lat, ref_lon;             // Common reference point, derived from FullExtent
      Extent        m_FullExtent;
      bool         m_bExtentSet;

      double      m_s_ref_lat, m_s_ref_lon;

private:
      void DoRenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, RenderTypeEnum option);

      int DCRenderRect(wxMemoryDC& dcinput, ViewPort& vp, wxRect *rect);
      bool DCRenderLPB(wxMemoryDC& dcinput, ViewPort& vp, wxRect* rect);

      InitReturn PostInit( ChartInitFlag flags, ColorScheme cs );
      InitReturn FindOrCreateSenc( const wxString& name );
      int BuildSENCFile(const wxString& FullPath000, const wxString& SENCFileName);

      void CreateSENCRecord( OGRFeature *pFeature, FILE * fpOut, int mode );

      void GetChartNameFromTXT(const wxString& FullPath, wxString &Name);
      bool BuildThumbnail(const wxString &bmpname);
      bool CreateHeaderDataFromENC(void);
      bool CreateHeaderDataFromSENC(void);
      bool GetBaseFileAttr(wxFileName fn);


           //    Access to raw ENC DataSet
      bool InitENCMinimal( const wxString& FullPath );
      int GetENCScale();
      OGRFeature *GetChartFirstM_COVR(int &catcov);
      OGRFeature *GetChartNextM_COVR(int &catcov);

      void FreeObjectsAndRules();
      const char *getName(OGRFeature *feature);
      int GetUpdateFileArray(const wxFileName file000, wxArrayString *UpFiles);
      int ValidateAndCountUpdates( const wxFileName file000, const wxString SENCDir, wxString &LastUpdateDate);

      int _insertRules(S57Obj *obj, LUPrec *LUP);

      int my_fgets( char *buf, int buf_len_max, wxBufferedInputStream& ifs );

 // Private Data
      wxString    *m_pcsv_locn;

      ViewPort    last_vp;

      char        *hdr_buf;
      char        *mybuf_ptr;
      int         hdr_len;
      wxFileName  m_SENCFileName;
      ObjRazRules *razRules[PRIO_NUM][LUPNAME_NUM];


      wxArrayString *m_tmpup_array;
      PixelCache   *pDIB;

      bool         bGLUWarningSent;

      wxBitmap    *m_pDIBThumbDay;
      wxBitmap    *m_pDIBThumbDim;
      wxBitmap    *m_pDIBThumbOrphan;
      bool        m_bneed_new_thumbnail;

      wxDateTime  m_date000;                    // extracted from DSID:ISDT
      wxString    m_edtn000;                    // extracted from DSID:EDTN
      int         m_nGeoRecords;                // extracted from DSSI:NOGR
      int         m_native_scale;               // extracted from DSPM:CSCL

//  SM Projection parms
      double    easting_vp_center, northing_vp_center;
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

/******************************************************************************
 * $Id: s57chart.h,v 1.24 2009/08/22 01:23:49 bdbcat Exp $
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
 * Revision 1.24  2009/08/22 01:23:49  bdbcat
 * More virtual methods
 *
 * Revision 1.23  2009/06/03 03:22:50  bdbcat
 * Set Overzoom limits
 *
 * Revision 1.22  2009/05/05 04:02:49  bdbcat
 * *** empty log message ***
 *
 * Revision 1.21  2009/04/18 03:33:44  bdbcat
 * *** empty log message ***
 *
 * Revision 1.20  2009/03/30 19:21:21  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.19  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.18  2008/12/22 18:41:18  bdbcat
 * Update cm93 support
 *
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
#include "chcanv.h"                // for Viewport


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
class S57ObjectDesc;

#include <wx/dynarray.h>

// Declare the Array of S57Obj
WX_DECLARE_OBJARRAY(S57Obj, ArrayOfS57Obj);
// And also a list
WX_DECLARE_LIST(S57Obj, ListOfS57Obj);


WX_DECLARE_OBJARRAY(VE_Element, ArrayOfVE_Elements);
WX_DECLARE_OBJARRAY(VC_Element, ArrayOfVC_Elements);

WX_DECLARE_HASH_MAP( int, wxString, wxIntegerHash, wxIntegerEqual, MyNatsurHash );

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

      virtual ThumbData *GetThumbData(int tnx, int tny, float lat, float lon);
      virtual ThumbData *GetThumbData() {return pThumbData;}
      bool UpdateThumbData(float lat, float lon);

      virtual int GetNativeScale(){return m_Chart_Scale;}
      virtual double GetNormalScaleMin(double canvas_scale_factor);
      virtual double GetNormalScaleMax(double canvas_scale_factor);

      void SetNativeScale(int s){m_Chart_Scale = s;}

      double GetChartSkew(){return 0.0;}

      virtual void InvalidateCache();

      virtual bool RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type);
      virtual void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion);

      virtual bool IsCacheValid(){ return (pDIB != NULL); }

      virtual void GetPointPix(ObjRazRules *rzRules, float rlat, float rlon, wxPoint *r);
      virtual void GetPointPix(ObjRazRules *rzRules, wxPoint2DDouble *en, wxPoint *r, int nPoints);
      virtual void GetPixPoint(int pixx, int pixy, double *plat, double *plon, ViewPort *vpt);

      virtual void SetVPParms(ViewPort *pvpt);

      virtual bool AdjustVP(ViewPort &vp_last, ViewPort &vp_proposed);
      virtual bool IsRenderDelta(ViewPort &vp_last, ViewPort &vp_proposed);

      void SetFullExtent(Extent& ext);
      bool GetChartExtent(Extent *pext);

      void SetColorScheme(ColorScheme cs, bool bApplyImmediate);
      virtual void UpdateLUPs(s57chart *pOwner);

      int _insertRules(S57Obj *obj, LUPrec *LUP, s57chart *pOwner);

      virtual ListOfS57Obj *GetObjListAtLatLon(float lat, float lon, float select_radius, ViewPort *VPoint);
      bool DoesLatLonSelectObject(float lat, float lon, float select_radius, S57Obj *obj);
      bool IsPointInObjArea(float lat, float lon, float select_radius, S57Obj *obj);
      virtual S57ObjectDesc *CreateObjDescription(const S57Obj *obj);
      wxString GetAttributeDecode(wxString& att, int ival);

      wxFileName GetSENCFileName(){ return m_SENCFileName; }
      void SetSENCFileName(wxFileName fn){ m_SENCFileName = fn;}

      int BuildRAZFromSENCFile(const wxString& SENCPath);

      int my_fgets( char *buf, int buf_len_max, wxInputStream& ifs );

      //    Initialize from an existing SENC file
      bool InitFromSENCMinimal( const wxString& FullPath );

      //    DEPCNT VALDCO array access
      bool GetNearestSafeContour(double safe_cnt, double &next_safe_cnt);

      ListOfS57Obj *GetAssociatedObjects(S57Obj *obj);


      virtual int Get_nve_elements(void){ return m_nve_elements;}
      virtual int Get_nvc_elements(void){ return m_nvc_elements;}

      virtual VE_Element  **Get_pve_array(void){ return m_pve_array;}
      virtual VC_Element  **Get_pvc_array(void){ return m_pvc_array;}

      virtual void ForceEdgePriorityEvaluate(void);

// Public data
//Todo Accessors here
      //  Object arrays used by S52PLIB TOPMAR rendering logic
      wxArrayPtrVoid *pFloatingATONArray;
      wxArrayPtrVoid *pRigidATONArray;

      double        ref_lat, ref_lon;             // Common reference point, derived from FullExtent
      Extent        m_FullExtent;
      bool          m_bExtentSet;
      bool          m_bLinePrioritySet;

      //  SM Projection parms, stored as convenience to expedite pixel conversions
      double    m_easting_vp_center, m_northing_vp_center;
      double    m_pixx_vp_center, m_pixy_vp_center;
      double    m_view_scale_ppm;

      //    Last ViewPort succesfully rendered, stored as an aid to calculating pixel cache address offsets and regions
      ViewPort    m_last_vp;

      //    Geometry tables
      int         m_nve_elements;
      int         m_nvc_elements;

      VE_Element  **m_pve_array;
      VC_Element  **m_pvc_array;

private:
      bool DoRenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, RenderTypeEnum option);

      int DCRenderRect(wxMemoryDC& dcinput, ViewPort& vp, wxRect *rect);
      bool DCRenderLPB(wxMemoryDC& dcinput, ViewPort& vp, wxRect* rect);

      InitReturn PostInit( ChartInitFlag flags, ColorScheme cs );
      InitReturn FindOrCreateSenc( const wxString& name );
      int BuildSENCFile(const wxString& FullPath000, const wxString& SENCFileName);

      void  CreateSENCRecord( OGRFeature *pFeature, FILE * fpOut, int mode, S57Reader *poReader );
      void  CreateSENCVectorEdgeTable(FILE * fpOut, S57Reader *poReader);
      void  CreateSENCConnNodeTable(FILE * fpOut, S57Reader *poReader);


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



 // Private Data
      wxString    *m_pcsv_locn;


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


//  Raw ENC DataSet members
      OGRS57DataSource  *m_pENCDS;

//  DEPCNT VALDCO array members
      int         m_nvaldco;
      int         m_nvaldco_alloc;
      double       *m_pvaldco_array;

      int         *m_pVectorEdgeHelperTable;

      MyNatsurHash m_natsur_hash;               // hash table for cacheing NATSUR string values from int attributes

};

//----------------------------------------------------------------------------
//    This class encapsulates the results (per object) of an S57 object query
//----------------------------------------------------------------------------
//
class S57ObjectDesc
{
public:
      wxString    S57ClassName;
      wxString    S57ClassDesc;
      wxString    Attributes;
};


#endif

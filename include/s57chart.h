/******************************************************************************
 * $Id: s57chart.h,v 1.8 2007/06/10 02:37:18 bdbcat Exp $
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

// ----------------------------------------------------------------------------
// Useful Prototypes
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// S57 Utility Prototypes
// ----------------------------------------------------------------------------
extern "C" int  s57_initialize(const wxString& csv_dir, FILE *flog);
extern "C" int  s57_GetChartScale(char *pFullPath);
extern "C" bool s57_GetChartExtent(char *pFullPath, Extent *pext);
extern "C" bool s57_GetChartFirstM_COVR(char *pFullPath, OGRDataSource **pDS, OGRFeature **pFeature,
                               OGRLayer **pLayer, int &catcov);
extern "C" bool s57_GetChartNextM_COVR(OGRDataSource *pDS, OGRLayer *pLayer, OGRFeature *pLastFeature,
                              OGRFeature **pFeature, int &catcov);
extern "C" bool s57_ddfrecord_test();



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

      ArrayOfS57Obj *GetObjArrayAtLatLon(float lat, float lon, float select_radius, ViewPort *VPoint);
      bool DoesLatLonSelectObject(float lat, float lon, float select_radius, S57Obj *obj);
      bool IsPointInObjArea(float lat, float lon, float select_radius, S57Obj *obj);
      wxString *CreateObjDescription(const S57Obj& obj);
      wxString *GetAttributeDecode(wxString& att, int ival);

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

      int BuildS57File(const char *pFullPath);
      int BuildRAZFromS57File(const char *pFullPath);

      void CreateSENCRecord( OGRFeature *pFeature, FILE * fpOut, int mode );

      void GetChartNameFromTXT(const wxString& FullPath, wxString &Name);

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



};

#endif

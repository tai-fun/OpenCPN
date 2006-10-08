/******************************************************************************
 * $Id: s57chart.h,v 1.5 2006/10/08 00:36:25 dsr Exp $
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
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.8  2006/08/04 11:43:37  dsr
 * no message
 *
 * Revision 1.7  2006/07/28 20:47:51  dsr
 * Cleanup
 *
 * Revision 1.6  2006/06/02 02:08:06  dsr
 * Add Arrays of ATON objects
 *
 * Revision 1.5  2006/05/28 01:47:00  dsr
 * SENC Version 104
 *
 * Revision 1.4  2006/05/28 00:55:04  dsr
 * Implement PolyGeo
 *
 * Revision 1.3  2006/05/19 19:36:19  dsr
 * Cleanup
 *
 * Revision 1.2  2006/04/23 04:06:18  dsr
 * Implement S57 Query
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.12  2006/04/19 00:59:12  dsr
 * Implement ColorScheme
 *
 * Revision 1.11  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.10  2006/03/13 05:10:10  dsr
 * Cleanup
 *
 * Revision 1.9  2006/03/04 21:25:38  dsr
 * Cleanup
 *
 * Revision 1.8  2006/02/24 17:59:56  dsr
 * Add GetNameFromTXT
 *
 * Revision 1.7  2006/02/23 01:25:49  dsr
 * Cleanup
 *
 * Revision 1.6  2006/02/09 14:01:39  dsr
 * Define ThumbData friends
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
#include "dymemdc.h"
#include "s52s57.h"                 //types

// ----------------------------------------------------------------------------
// Random Prototypes
// ----------------------------------------------------------------------------
extern "C" void UTMtoDeg(double long0, short southernHemisphere, double x, double y, double *lat, double *lon);
extern "C" void DegToUTM(float lat, float lon, char *zone, float *x, float *y, float lon0);
extern "C" void toTM(float lat, float lon, float lat0, float lon0, float k0, float *x, float *y);
extern "C" void fromTM(double x, double y, double lat0, double lon0, double k0, double *lat, double *lon);

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
class wxBitmapo;
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


 //Todo whats this??
      void GetPointPix(float rlat, float rlon, wxPoint *r);
      void pix_to_latlong(int pixx, int pixy, double *plat, double *plon);
      void vp_pix_to_latlong(ViewPort& vp, int pixx, int pixy, double *plat, double *plon);
      void latlong_to_pix(double lat, double lon, int &pixx, int &pixy);
      void latlong_to_pix_vp(double lat, double lon, int &pixx, int &pixy, ViewPort& vp);

      void GetPointPixEst(float rlat, float rlon, wxPoint *r);

      void SetVPParms(ViewPort *pvpt);
      void SetFullExtent(Extent& ext);
      void GetChartExtent(Extent *pext);

      void SetColorScheme(ColorScheme cs, bool bApplyImmediate);

      ArrayOfS57Obj *GetObjArrayAtLatLon(float lat, float lon, float select_radius);
      bool DoesLatLonSelectObject(float lat, float lon, float select_radius, S57Obj *obj);
      bool IsPointInObjArea(float lat, float lon, float select_radius, S57Obj *obj);
      wxString *CreateObjDescription(const S57Obj& obj);
      wxString *GetAttributeDecode(wxString& att, int ival);

// Public data
//Todo Accessors here
      //  Object arrays used by S52PLIB TOPMAR rendering logic
      wxArrayPtrVoid *pFloatingATONArray;
      wxArrayPtrVoid *pRigidATONArray;


private:
      void DoRenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint,
            RenderTypeEnum option, wxBitmap **ppDIB, wxImage **pImg);

      int DCRender(wxDC& dcinput, ViewPort& vp, wxRect *rect);

      int BuildS57File(const char *pFullPath);
      int BuildRAZFromS57File(const char *pFullPath);

      void CreateSENCRecord( OGRFeature *pFeature, FILE * fpOut, int mode );

      void GetChartNameFromTXT(const wxString& FullPath, wxString &Name);

      int S57_done();
      int S57_freeObj(S57Obj *obj);
      int _create_attList(S57Obj *obj);
      const char *getName(OGRFeature *feature);
      int GetUpdateFileArray(const wxString& DirName, wxArrayString *UpFiles);
      int CountUpdates( const wxString& DirName, wxString &LastUpdateDate);

      int _linkObj2rules();
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

#ifdef      S57USE_PIXELCACHE
      PixelCache   *pDIB;
#else
#ifdef dyUSE_BITMAPO_S57
      wxBitmapo   *pDIB;
#else
      wxBitmap    *pDIB;
#endif
#endif

//  Linear Projection Parms
      double        pix_per_deg_lat, pix_per_deg_lon, lat_top, lon_left;



};

#endif

/******************************************************************************
 * $Id: chartbase.h,v 1.14 2009/06/28 02:02:35 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  ChartBase Definition
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
 * $Log: chartbase.h,v $
 * Revision 1.14  2009/06/28 02:02:35  bdbcat
 * Implement Datum transforms.
 *
 * Revision 1.13  2009/06/21 03:12:05  bdbcat
 * Update dummy chart zoom limits.
 *
 * Revision 1.12  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.11  2008/12/09 03:33:25  bdbcat
 * Add cm93 support
 *
 * Revision 1.10  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
 *
 * Revision 1.9  2008/03/30 23:26:07  bdbcat
 * Cleanup
 *
 * Revision 1.8  2008/01/02 21:04:29  bdbcat
 * Update for Version 1.2.2
 *
 * Revision 1.7  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.6  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.5  2007/03/02 02:03:38  dsr
 * Remove geo-referencing methods from base class
 *
 * Revision 1.4  2006/10/08 14:15:15  dsr
 * no message
 *
 * Revision 1.3  2006/10/08 00:36:25  dsr
 * no message
 *
 * Revision 1.2  2006/10/07 03:50:54  dsr
 * *** empty log message ***
 *
 */

#ifndef _CHARTBASE_H_
#define _CHARTBASE_H_

#include "dychart.h"

#include "ocpn_pixel.h"
#include "bbox.h"
#include "chcanv.h"         // for enums
#include "chart1.h"



//----------------------------------------------------------------------------
//  Forward Declarations
//----------------------------------------------------------------------------
class ViewPort;

//----------------------------------------------------------------------------
// Constants. etc
//----------------------------------------------------------------------------

//    ChartBase::Init()  init_flags constants
typedef enum ChartInitFlag
{
      FULL_INIT = 0,
      HEADER_ONLY,
      THUMB_ONLY
}_ChartInitFlag;

//    ChartType constants
typedef enum ChartTypeEnum
{
      CHART_TYPE_KAP = 0,
      CHART_TYPE_GEO,
      CHART_TYPE_S57,
      CHART_TYPE_CM93,
      CHART_TYPE_CM93COMP,
      CHART_TYPE_DUMMY
}_ChartTypeEnum;

//    ChartFamily constants
typedef enum ChartFamilyEnum
{
      CHART_FAMILY_UNKNOWN = 0,
      CHART_FAMILY_RASTER,
      CHART_FAMILY_VECTOR
}_ChartFamilyEnum;


typedef enum RenderTypeEnum
{
      DC_RENDER_ONLY = 0,
      DC_RENDER_RETURN_DIB,
      DC_RENDER_RETURN_IMAGE
}_RenderTypeEnum;

typedef enum InitReturn
{
      INIT_OK = 0,
      INIT_FAIL_RETRY,        // Init failed, retry suggested
      INIT_FAIL_REMOVE,       // Init failed, suggest remove from further use
      INIT_FAIL_NOERROR       // Init failed, request no explicit error message
}_InitReturn;


class ThumbData
{
public:
    ThumbData();
    virtual ~ThumbData();

      wxBitmap    *pDIBThumb;
      int         ShipX;
      int         ShipY;
      int         Thumb_Size_X;
      int         Thumb_Size_Y;
};



typedef struct _Extent{
  double SLAT;
  double WLON;
  double NLAT;
  double ELON;
}Extent;

//          Depth unit type enum
typedef enum ChartDepthUnitType
{
    DEPTH_UNIT_UNKNOWN,
    DEPTH_UNIT_FEET,
    DEPTH_UNIT_METERS,
    DEPTH_UNIT_FATHOMS
}_ChartDepthUnitType;


// ----------------------------------------------------------------------------
// ChartBase
// ----------------------------------------------------------------------------

class ChartBase
{

public:
      ChartBase();
      virtual ~ChartBase() = 0;

      virtual InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs) = 0;

//    Accessors
      virtual ThumbData *GetThumbData(int tnx, int tny, float lat, float lon) = 0;
      virtual ThumbData *GetThumbData() = 0;
      virtual bool UpdateThumbData(float lat, float lon) = 0;

      virtual int GetNativeScale() = 0;
      virtual double GetNormalScaleMin(double canvas_scale_factor) = 0;
      virtual double GetNormalScaleMax(double canvas_scale_factor) = 0;

      virtual double GetChartSkew() = 0;
      virtual bool GetChartExtent(Extent *pext) = 0;

      virtual wxString GetPubDate(){ return *pPubYear;}
      virtual wxDateTime GetEditionDate(void){ return m_EdDate;}

      virtual wxString GetFullPath(){ return *m_pFullPath;}
      virtual wxString GetName(){ return *m_pName;}
      virtual ChartDepthUnitType GetDepthUnitType(void) { return m_depth_unit_id;}

      virtual bool IsReadyToRender(){ return bReadyToRender;}

      virtual void InvalidateCache(void) = 0;

      virtual bool RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type) = 0;

      virtual void SetVPParms(ViewPort *vpt) = 0;

      virtual bool AdjustVP(ViewPort &vp_last, ViewPort &vp_proposed) = 0;
      virtual bool IsRenderDelta(ViewPort &vp_last, ViewPort &vp_proposed) = 0;

      virtual void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion) = 0;

      virtual void SetColorScheme(ColorScheme cs, bool bApplyImmediate) = 0;

      virtual bool IsCacheValid(void) = 0;

      virtual int  GetCOVRTablenPoints(int iTable){ return m_pCOVRContourTable[iTable]; }
      virtual float *GetCOVRTableHead(int iTable){ return m_pCOVRTable[iTable]; }

      ChartTypeEnum     m_ChartType;
      ChartFamilyEnum   m_ChartFamily;

      wxString          *m_pFullPath;
      wxString          *m_pName;

      wxString          *pPubYear;
      wxString          *pDepthUnits;

      wxBitmap          *pcached_bitmap;

      ThumbData         *pThumbData;

      ColorScheme       m_global_color_scheme;
      bool              bReadyToRender;

      double            Chart_Error_Factor;

      ChartDepthUnitType m_depth_unit_id;

      //    Chart region coverage information
      //    Charts may have multiple valid regions within the lat/lon box described by the chart extent
      //    The following table structure contains this imbedded information

      //    Typically, BSB charts will contain only one entry, corresponding to the PLY information in the chart header
      //    ENC charts often contain multiple entries

      int         m_nCOVREntries;                       // number of coverage table entries
      int         *m_pCOVRContourTable;                 // int table of number of points in each coverage table entry
      float       **m_pCOVRTable;                       // table of pointers to list of floats describing valid COVR

      //    Todo  Define invalid COVR regions

protected:
      int               m_Chart_Scale;
      wxDateTime        m_EdDate;

      double            m_lon_datum_adjust;             // Add these numbers to WGS84 position to obtain internal chart position
      double            m_lat_datum_adjust;


};


// ----------------------------------------------------------------------------
// ChartDummy
// ----------------------------------------------------------------------------

class ChartDummy : public ChartBase
{

public:
      ChartDummy();
      virtual ~ChartDummy();

      virtual InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );

//    Accessors
      virtual ThumbData *GetThumbData(int tnx, int tny, float lat, float lon);
      virtual ThumbData *GetThumbData() {return pThumbData;}
      virtual bool UpdateThumbData(float lat, float lon);

      virtual int GetNativeScale();
      double GetNormalScaleMin(double canvas_scale_factor){return 1.0;}
      double GetNormalScaleMax(double canvas_scale_factor){ return 1.0e8;}

      virtual wxString GetPubDate();
      virtual double GetChartSkew(){ return 0.0;}
      virtual bool GetChartExtent(Extent *pext);

      virtual void InvalidateCache(void);

      virtual bool RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type);

      virtual void SetVPParms(ViewPort *vpt);

      virtual bool AdjustVP(ViewPort &vp_last, ViewPort &vp_proposed);

      virtual bool IsRenderDelta(ViewPort &vp_last, ViewPort &vp_proposed);

      virtual void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion);

      virtual void SetColorScheme(ColorScheme cs, bool bApplyImmediate);

      virtual bool IsCacheValid(){ return false; }


private:
      wxBitmap    *m_pBM;
};



#endif

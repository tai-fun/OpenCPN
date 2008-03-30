/******************************************************************************
 * $Id: chartbase.h,v 1.9 2008/03/30 23:26:07 bdbcat Exp $
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
      CHART_TYPE_DUMMY
}_ChartTypeEnum;

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
      INIT_FAIL_REMOVE        // Init Failed, suggest remove from further use
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

      virtual float GetNativeScale() = 0;
      virtual float GetChartSkew() = 0;
      virtual void GetChartExtent(Extent *pext) = 0;

      virtual void GetPubDate(wxString &data){ data = *pPubYear;}
      virtual void GetFullPath(wxString &data){ data = *m_pFullPath;}
      virtual void GetName(wxString &data){ data = *pName;}
      virtual ChartDepthUnitType GetDepthUnitType(void) { return m_depth_unit_id;}

      virtual bool IsReadyToRender(){ return bReadyToRender;}

      virtual void InvalidateCache(void) = 0;

      virtual void RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type) = 0;

      virtual void SetVPParms(ViewPort *vpt) = 0;

      virtual void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion) = 0;

      virtual void SetColorScheme(ColorScheme cs, bool bApplyImmediate) = 0;

      virtual bool IsCacheValid(void) = 0;

      ChartTypeEnum     ChartType;
      int               Chart_Scale;
      wxString          *m_pFullPath;
      wxString          *pName;

      wxString          *pPubYear;
      wxString          *pDepthUnits;

      wxBitmap          *pcached_bitmap;

      ThumbData         *pThumbData;

      ColorScheme       m_global_color_scheme;
      bool              bReadyToRender;

      double            Chart_Error_Factor;

      ChartDepthUnitType m_depth_unit_id;
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

      virtual float GetNativeScale();
      virtual void GetPubDate(wxString &data);
      virtual float GetChartSkew(){ return 0.0;}
      virtual void GetChartExtent(Extent *pext);

      virtual void InvalidateCache(void);

      virtual void RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type);

      virtual void SetVPParms(ViewPort *vpt);

      virtual void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion);

      virtual void SetColorScheme(ColorScheme cs, bool bApplyImmediate);

      virtual bool IsCacheValid(){ return false; }


private:
      wxBitmap    *m_pBM;
};



#endif

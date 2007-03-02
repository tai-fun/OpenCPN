/******************************************************************************
 * $Id: chartbase.h,v 1.5 2007/03/02 02:03:38 dsr Exp $
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
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.2  2006/05/19 19:36:18  dsr
 * Cleanup
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.10  2006/04/19 00:54:52  dsr
 * Implement ColorScheme
 *
 * Revision 1.9  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.8  2006/03/04 21:23:25  dsr
 * Move PixelCache definition here
 *
 * Revision 1.7  2006/02/24 17:56:05  dsr
 * Add some new accessors
 *
 * Revision 1.6  2006/02/24 02:59:06  dsr
 * Cleanup
 *
 * Revision 1.5  2006/02/23 01:17:00  dsr
 * Cleanup, moved Viewport definition to chcanv
 *
 * Revision 1.4  2006/02/09 13:55:39  dsr
 * Define ThumbData class, and friends
 *
 * Revision 1.3  2006/02/10 03:19:06  dsr
 * *** empty log message ***
 *
 *
 */

#ifndef _CHARTBASE_H_
#define _CHARTBASE_H_

#include "dychart.h"

#include "bitmapo.h"
#include "bbox.h"
#include "dymemdc.h"
#include "chcanv.h"         // for enums
#include "chart1.h"

#ifdef __WXX11__
#include "wx/x11/private.h"

//    For MIT-SHM Extensions
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#endif


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
};

//    ChartType constants
typedef enum ChartTypeEnum
{
      CHART_TYPE_KAP = 0,
      CHART_TYPE_GEO,
      CHART_TYPE_S57,
      CHART_TYPE_DUMMY
};

typedef enum RenderTypeEnum
{
      DC_RENDER_ONLY = 0,
      DC_RENDER_RETURN_DIB,
      DC_RENDER_RETURN_IMAGE
};

typedef enum InitReturn
{
      INIT_OK = 0,
      INIT_FAIL_RETRY,        // Init failed, retry suggested
      INIT_FAIL_REMOVE        // Init Failed, suggest remove from further use
};



class ThumbData
{
public:
    ThumbData();
    virtual ~ThumbData();

      wxBitmap    *pDIB;
      int         ShipX;
      int         ShipY;
};


 typedef enum RGBO
{
  RGB = 0,
  BGR
};

typedef struct _Extent{
  double SLAT;
  double WLON;
  double NLAT;
  double ELON;
}Extent;



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
      virtual float GetNativeScale() = 0;
      virtual float GetChartSkew() = 0;
      virtual void GetChartExtent(Extent *pext) = 0;

      virtual void GetPubDate(wxString &data){ data = *pPubYear;}
      virtual void GetFullPath(wxString &data){ data = *pFullPath;}
      virtual void GetName(wxString &data){ data = *pName;}
      virtual bool IsReadyToRender(){ return bReadyToRender;}

      virtual void InvalidateCache(void) = 0;

      virtual void RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type) = 0;

      virtual void SetVPParms(ViewPort *vpt) = 0;

      virtual void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion) = 0;

      virtual void SetColorScheme(ColorScheme cs, bool bApplyImmediate) = 0;

      virtual ColorScheme GetColorScheme(void) { return m_color_scheme; }

      virtual bool IsCacheValid(void) = 0;

      ChartTypeEnum     ChartType;
      int               Chart_Scale;
      wxString          *pFullPath;
      wxString          *pName;

      wxString          *pPubYear;

      wxBitmap          *pcached_bitmap;

      ThumbData         *pThumbData;

      ColorScheme       m_color_scheme;
      bool              bReadyToRender;

      double            Chart_Error_Factor;
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

// ============================================================================
// PixelCache Definition
// ============================================================================
class PixelCache
{
  public:

      //    Constructors

    PixelCache(int width, int height, int depth);
    ~PixelCache();

    void SelectIntoDC(wxMemoryDC &dc);
    RGBO GetRGBO(){return m_rgbo;}

      //    Data storage
    int               m_width;
    int               m_height;
    int               m_depth;
    unsigned char     *pData;
    int               line_pitch_bytes;
    int               bytes_per_pixel;
    RGBO               m_rgbo;

#ifdef dyUSE_BITMAPO
      wxBitmapo         *m_pbm;
#else
      wxBitmap          *m_pbm;
#endif

      wxImage           *m_pimage;

#ifdef __PIX_CACHE_DIBSECTION__
      wxDIB             *m_pDS;
#endif

#ifdef __PIX_CACHE_X11IMAGE__
      XImage            *m_pxim;
      Display           *xdisplay;

#endif

#ifdef ocpUSE_MITSHM
      XShmSegmentInfo   *pshminfo;
#endif

};



#endif

/******************************************************************************
 * $Id: chcanv.h,v 1.2 2006/10/05 03:52:54 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Chart Canvas
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
 * $Log: chcanv.h,v $
 * Revision 1.2  2006/10/05 03:52:54  dsr
 * no message
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.5  2006/07/28 20:47:50  dsr
 * Cleanup
 *
 * Revision 1.4  2006/05/28 00:50:01  dsr
 * Floats to Doubles in ViewPort
 *
 * Revision 1.3  2006/05/19 19:36:19  dsr
 * Cleanup
 *
 * Revision 1.2  2006/04/23 04:07:38  dsr
 * Implement S57 Query
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.11  2006/04/19 00:56:41  dsr
 * *** empty log message ***
 *
 * Revision 1.10  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.9  2006/03/13 05:10:09  dsr
 * Cleanup
 *
 * Revision 1.8  2006/03/04 21:24:45  dsr
 * Implement thread-based chart rescale logic
 *
 * Revision 1.7  2006/02/24 03:00:17  dsr
 * Cleanup
 *
 * Revision 1.6  2006/02/23 01:20:05  dsr
 * Cleanup, add ViewPort and some accessors
 *
 * Revision 1.5  2006/02/10 03:19:06  dsr
 * *** empty log message ***
 *
 *
 */




#ifndef __CHCANV_H__
#define __CHCANV_H__

#include "dychart.h"

#include "tcmgr.h"                     // for pIDX

#include "bbox.h"

#ifdef __WXMSW__
#include <wx/datetime.h>
#endif

//----------------------------------------------------------------------------
//    Forward Declarations
//----------------------------------------------------------------------------
      class Route;
      class TCWin;
      class RoutePoint;
      class SelectItem;
      class wxBoundingBox;
      class wxBitmapo;
      class WVSChart;
      class MyFrame;
      class ChartRescaleThread;
      class ChartBaseBSB;
      class PixelCache;
      class ChartBase;

//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------
#define     RESCALE_TIMER     1
#define     PAN_TIMER 2

typedef enum ScaleTypeEnum
{
  SCALE_SUBSAMP = 0,
  SCALE_BILINEAR,
};

enum                                //  specify the render behaviour of SetViewPoint()
{
    CURRENT_RENDER,                 // use the current render type
    FORCE_SUBSAMPLE                 // force sub-sampled render, with re-render timer
};

//          Cursor region enumerator
enum
{
      CENTER,
      MID_RIGHT,
      MID_LEFT,
      MID_TOP,
      MID_BOT,
};

//----------------------------------------------------------------------------
// ViewPort
//----------------------------------------------------------------------------
class ViewPort
{
  public:
//  ctor
    ViewPort()  { bValid = false;}

//  Accessors
    bool IsValid() { return bValid; }

//  Generic
    double   clat;                   // center point
    double   clon;
    double   view_scale;
    double   lat_top;
    double   lat_bot;
    double   lon_left;
    double   lon_right;
    wxBoundingBox vpBBox;
    float    chart_scale;            // conventional chart displayed scale

    int      pix_width;
    int      pix_height;

    bool     bValid;                 // This VP is valid

    double   ppd_lat;
    double   ppd_lon;

};




//----------------------------------------------------------------------------
// ChartCanvas
//----------------------------------------------------------------------------
class ChartCanvas: public wxWindow
{
public:
      ChartCanvas(wxFrame *frame);
      ~ChartCanvas();

      //    Methods
      void OnPaint(wxPaintEvent& event);
      void NowPaint();
      void Scroll(int dx, int dy);
      void CanvasPopupMenu(int x, int y, int seltype);
      void PopupMenuHandler(wxCommandEvent& event);
      void SetMyCursor(wxCursor *c);


      void SetViewPoint(double lat, double lon, double scale, int mod_mode, int sample_mode);

      void SetVPScale(double sc);

      void GetPointPix(float rlat, float rlon, wxPoint *r);
      void GetPixPoint(int x, int y, float &lat, float &lon);
      void WarpPointerDeferred(int x, int y);

      //    Accessors
      int GetCanvas_width(){ return canvas_width;}
      int GetCanvas_height(){ return canvas_height;}
      float GetVPScale(){return VPoint.view_scale;}
      float GetVPChartScale(){return VPoint.chart_scale;}

      void  SetbNewVP(bool f){ bNewVP = f;}

      //Todo build more accessors
      bool        m_bFollow;
      bool        m_bForceReDraw;
      wxCursor    *pCursorPencil;
      bool        bShowCurrent;
      bool        bShowTide;
      float       canvas_scale_factor;    // converter....
                                    // useage....
                                    // conventional_chart_scale   = scale_factor /pix_per_deg_lon
      TCWin       *pCwin;
      ViewPort    VPoint;
      wxBitmap    *pscratch_bm;

private:

      bool        bNewVP;
      int         cursor_region;

      wxRect      bbRect;

      wxPoint     r_rband;
      wxPoint     LastShipPoint;
      wxPoint     LastPredPoint;
      bool        bDrawingRoute;
      bool        m_bRouteEditing;
      RoutePoint  *m_pRoutePointEditTarget;
      SelectItem  *m_pFoundPoint;

      Route       *pMouseRoute;
      double      prev_rlat;
      double      prev_rlon;
      RoutePoint  *prev_pMousePoint;
      Route       *pSelectedRoute;
      Route       *m_pEditRoute;
      RoutePoint  *pFoundRoutePoint;


      wxCursor    *pCursorLeft;
      wxCursor    *pCursorRight;
      wxCursor    *pCursorUp;
      wxCursor    *pCursorDown;

      wxCursor    *pCursorUpLeft;
      wxCursor    *pCursorUpRight;
      wxCursor    *pCursorDownLeft;
      wxCursor    *pCursorDownRight;
      wxCursor    *pCursorArrow;

      wxCursor    *pPriorCursor;

      int         popx, popy;
      bool        m_bAppendingRoute;

      float       long0;

      wxBitmap    *pThumbDIBShow;
      wxBitmap    *pThumbShowing;

      bool        bShowingCurrent;
      bool        bShowingTide;


      //    Methods
      void OnActivate(wxActivateEvent& event);
      void OnSize(wxSizeEvent& event);
      void RescaleTimerEvent(wxTimerEvent& event);
      void MouseEvent(wxMouseEvent& event);
      void ShipDraw(wxDC& dc, wxPoint& ShipPoint, wxPoint& PredPoint);
      void DrawArrow(wxDC& dc, int x, int y, float rot_angle, float scale);
      void OnEvtRescale(wxCommandEvent & event);

      void PanTimerEvent(wxTimerEvent& event);
      void DrawAllRoutesInBBox(wxDC& dc, wxBoundingBox& BltBBox);

      void DrawAllTCInBBox(wxDC& dc, wxBoundingBox& BBox, bool bRebuildSelList,
                       bool bforce_redraw);
      void DrawAllTidesInBBox(wxDC& dc, wxBoundingBox& BBox, bool bRebuildSelList,
                        bool bforce_redraw);
      void DrawAllCurrentsInBBox(wxDC& dc, wxBoundingBox& BBox,
                           bool bRebuildSelList, bool bforce_redraw_currents);
      void DrawTCWindow(int x, int y, void *pIDX);
      void RenderChartOutline(wxDC *pdc, int dbIndex, ViewPort& vp);
      void RenderAllChartOutlines(wxDC *pdc, ViewPort& vp);


      //    Data
      int         canvas_width, canvas_height;

      int         xr_margin;                          // chart scroll margins, control cursor, etc.
      int         xl_margin;
      int         yt_margin;
      int         yb_margin;

      MyFrame     *parent_frame;
      int         m_test;

      wxPoint     last_drag;
      ChartBase   *drag_chart;              // Todo for debug only

      wxMemoryDC  *pmemdc;

      wxRect      latest_bfollow_overlay_rect;

      int         warp_x, warp_y;
      bool        warp_flag;

      ScaleTypeEnum  current_scale_method;
      wxTimer     *pRescaleTimer;

      bool        m_bSubsamp;
      int         m_rescale_timer_msec;

      wxBitmap    *pBM;

      float       current_draw_scaler;


      wxTimer     *pPanTimer;

      WVSChart    *pwvs_chart;

      ChartRescaleThread      *pRescaleThread;
      ChartBaseBSB            *pCBSB;

DECLARE_EVENT_TABLE()
};

//----------------------------------------------------------------------------
//    Constants
//----------------------------------------------------------------------------
enum
{
      ID_TCWIN_NX,
      ID_TCWIN_PR
};

enum
{
      TIDE_PLOT,
      CURRENT_PLOT
};

//----------------------------------------------------------------------------
// TCWin
//----------------------------------------------------------------------------
WX_DECLARE_LIST(wxPoint, SplineList);           // for spline curve points

class TCWin: public wxDialog
{
public:
      TCWin(ChartCanvas *parent, int x, int y, void *pvIDX);
      ~TCWin();

      void OnSize(wxSizeEvent& event);
      void OnPaint(wxPaintEvent& event);
      void MouseEvent(wxMouseEvent& event);
      void OKEvent(wxCommandEvent& event);
      void NXEvent(wxCommandEvent& event);
      void PREvent(wxCommandEvent& event);
      void OnCloseWindow(wxCloseEvent& event);

      void Resize(void);

      void RePosition(void);

      bool        bForceRedraw;

private:

      int         plot_type;

      IDX_entry   *pIDX;
      wxButton    *OK_button;
      wxButton    *NX_button;
      wxButton    *PR_button;

      SplineList  *psList;
      int         im;
      int         ib;
      int         it;

      float       tcv[24];
      bool        btc_valid;
      ChartCanvas *pParent;
      int         corr_mins;
      char        stz[4];
      int         t_graphday_00_at_station;
      wxDateTime  graphday;
      int         plot_y_offset;

DECLARE_EVENT_TABLE()
};


//----------------------------------------------------------------------------------------------------------
//    ocpCursor Specification
//----------------------------------------------------------------------------------------------------------

class wxCursorRefData;

class ocpCursor : public wxCursor
{
      public:

            ocpCursor(const wxString& cursorName, long type, int hotSpotX=0, int hotSpotY=0);
            ocpCursor(char **xpm_data, long type, int hotSpotX=0, int hotSpotY=0);
};

//----------------------------------------------------------------------------------------------------------
//    ChartRescaleThread Specification
//----------------------------------------------------------------------------------------------------------
DECLARE_EVENT_TYPE(EVT_RESCALE_THREAD_DONE, -1)

class ChartBase;

class ChartRescaleThread : public wxThread
{
      public:
        ChartRescaleThread(wxWindow *ParentWindow,
                           ChartBase *pChart, wxRect& s, wxRect& d, ScaleTypeEnum st);

        void *Entry(void);

        wxEvtHandler *m_pChCanvEventHandler;
        ChartBase *pch;
        wxRect source;
        wxRect dest;
        ScaleTypeEnum scale_type;

};


//----------------------------------------------------------------------------------------------------------
//    s57QueryDialog Specification
//----------------------------------------------------------------------------------------------------------
class S57QueryDialog: public wxDialog
{
DECLARE_CLASS( S57QueryDialog )
DECLARE_EVENT_TABLE()
public:

      /// Constructors

      S57QueryDialog( );
      S57QueryDialog( wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxString& caption = wxT("Object Query"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU );

      ~S57QueryDialog( );
      /// Initialise our variables
      void Init();

      /// Creation
      bool Create( wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxString& caption = wxT("Object Query"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU );

      /// Creates the controls and sizers
      void CreateControls();

      void SetText(wxString &text_string);

      wxString    *pQueryResult;
};

#endif

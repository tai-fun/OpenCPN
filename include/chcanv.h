/******************************************************************************
 * $Id: chcanv.h,v 1.9 2007/06/10 02:37:18 bdbcat Exp $
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
 * Revision 1.9  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.7  2007/03/02 02:05:44  dsr
 * Re-define ViewPort Class to better support skewed and UTM Vector charts
 *
 * Revision 1.6  2006/11/01 02:18:45  dsr
 * AIS Support
 *
 *
 */




#ifndef __CHCANV_H__
#define __CHCANV_H__

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
      class ocpnBitmap;
      class WVSChart;
      class MyFrame;
      class ChartBaseBSB;
      class ChartBase;
      class AIS_Target_Data;

//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------
#define     RESCALE_TIMER     1
#define     PAN_TIMER         2
#define     CURTRACK_TIMER    3

typedef enum ScaleTypeEnum
{
  SCALE_SUBSAMP = 0,
  SCALE_BILINEAR,
}_ScaleTypeEnum;

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
    double   view_scale_ppm;
    double   binary_scale_factor;    // Meaningful for Raster Charts only
    double   skew;
    double   c_east, c_north;       // SM co-ordinates of ViewPort center
                                    // relative to (near) chart centroid


    wxBoundingBox vpBBox;           // An un-skewed rectangular lat/lon bounding box
                                    // which contains the entire vieport

    float    chart_scale;            // conventional chart displayed scale

    int      pix_width;
    int      pix_height;

    bool     bValid;                 // This VP is valid


    double   pref_a_lat;            // Viewport reference "corner" points
    double   pref_a_lon;            // Used for hit testing
    double   pref_b_lat;            // n.b. on skewed viewports, points
    double   pref_b_lon;            // describe a skewed rectangle
    double   pref_c_lat;
    double   pref_c_lon;
    double   pref_d_lat;
    double   pref_d_lon;

    //  These for s57 charts only, will have to go.....
    //  s57chart.cpp needs to acknowledge reference points
    double   lat_top;
    double   lat_bot;
    double   lon_left;
    double   lon_right;


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


      void SetViewPoint(double lat, double lon, double scale_ppm, double skew, int mod_mode, int sample_mode);

      void SetVPScale(double sc);

      void GetPointPix(double rlat, double rlon, wxPoint *r);
      void GetPixPoint(int x, int y, double &lat, double &lon);
      void WarpPointerDeferred(int x, int y);
      void UpdateShips();
      void UpdateAIS();
      void FlushBackgroundRender(void);

      //    Accessors
      int GetCanvas_width(){ return canvas_width;}
      int GetCanvas_height(){ return canvas_height;}
      float GetVPScale(){return VPoint.view_scale_ppm;}
      float GetVPChartScale(){return VPoint.chart_scale;}
      double GetVPBinaryScaleFactor(){return VPoint.binary_scale_factor;}

      void  SetbNewVP(bool f){ bNewVP = f;}
      bool  GetbNewVP(){ return bNewVP;}

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
      wxColour    Ship_Color;
      int         Ship_Size;

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

      AIS_Target_Data *pFoundAIS_Target_Data;

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

      wxBitmap    *pThumbDIBShow;
      wxBitmap    *pThumbShowing;

      bool        bShowingCurrent;
      bool        bShowingTide;


      //    Methods
      void OnActivate(wxActivateEvent& event);
      void OnSize(wxSizeEvent& event);
      void MouseEvent(wxMouseEvent& event);
      void ShipDraw(wxDC& dc);
      void DrawArrow(wxDC& dc, int x, int y, float rot_angle, float scale);
      void OnEvtRescale(wxCommandEvent& event);
      void OnIdleEvent(wxIdleEvent& event);

      void RescaleTimerEvent(wxTimerEvent& event);
      void PanTimerEvent(wxTimerEvent& event);
      void OnCursorTrackTimerEvent(wxTimerEvent& event);

      void DrawAllRoutesInBBox(wxDC& dc, wxBoundingBox& BltBBox);

      void DrawAllTidesInBBox(wxDC& dc, wxBoundingBox& BBox, bool bRebuildSelList,
                        bool bdraw_mono = false);
      void DrawAllCurrentsInBBox(wxDC& dc, wxBoundingBox& BBox,
                           bool bRebuildSelList, bool bforce_redraw_currents, bool bdraw_mono = false);
      void DrawTCWindow(int x, int y, void *pIDX);
      void RenderChartOutline(wxDC *pdc, int dbIndex, ViewPort& vp, bool bdraw_mono = false);
      void RenderAllChartOutlines(wxDC *pdc, ViewPort& vp, bool bdraw_mono = false);
      wxBitmap *DrawTCCBitmap(bool bAddNewSelpoints);
      void AISDraw(wxDC& dc);


      //    Data
      int         canvas_width, canvas_height;

      int         xr_margin;                          // chart scroll margins, control cursor, etc.
      int         xl_margin;
      int         yt_margin;
      int         yb_margin;

      MyFrame     *parent_frame;

      wxPoint     last_drag;

      wxMemoryDC  *pmemdc;

      int         warp_x, warp_y;
      bool        warp_flag;

      ScaleTypeEnum  current_scale_method;

      bool        m_bSubsamp;

      wxBitmap    *pBM;

      float       current_draw_scaler;


      wxTimer     *pRescaleTimer;   // This timer used for bi-linear rescale
      wxTimer     *pPanTimer;       // This timer used for auto panning on route creation and edit
      wxTimer     *pCurTrackTimer;  // This timer used to update the status window on mouse idle

      int         m_rescale_timer_msec;
      int         m_curtrack_timer_msec;

      WVSChart    *pwvs_chart;

      ChartBaseBSB *pCBSB;
      wxBitmap    *pss_overlay_bmp;
      wxMask      *pss_overlay_mask;

      wxRect      ship_draw_rect;
      wxRect      ais_draw_rect;

      bool        m_bBackRender;
      bool        m_bbr_paused;
      ChartBaseBSB *br_Ch;

      wxBitmap    *proute_bm;       // a bitmap and dc used to calculate route bounding box
      wxMemoryDC  dc_route;         // seen in mouse->edit->route

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


//----------------------------------------------------------------------------------------------------------
//    AISTargetQueryDialog Specification
//----------------------------------------------------------------------------------------------------------
class AISTargetQueryDialog: public wxDialog
{
DECLARE_CLASS( AISTargetQueryDialog )
DECLARE_EVENT_TABLE()
public:

      /// Constructors

      AISTargetQueryDialog( );
      AISTargetQueryDialog( wxWindow* parent,
            wxWindowID id = wxID_ANY,
            const wxString& caption = wxT("Object Query"),
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU );

      ~AISTargetQueryDialog( );
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

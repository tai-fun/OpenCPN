/******************************************************************************
 * $Id: chcanv.h,v 1.23 2009/06/22 02:44:05 bdbcat Exp $
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
 * Revision 1.23  2009/06/22 02:44:05  bdbcat
 * Implement AIS Target highlight.
 *
 * Revision 1.22  2009/06/17 02:49:09  bdbcat
 * Cleanup.
 *
 * Revision 1.21  2009/06/03 03:21:15  bdbcat
 * Implement canvas panning, wheel zoom, etc.
 *
 * Revision 1.20  2009/04/07 16:54:42  bdbcat
 * New Tide station icon
 *
 * Revision 1.19  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.18  2008/12/09 04:05:53  bdbcat
 * Cleanup Comments
 *
 * Revision 1.17  2008/10/31 01:06:22  bdbcat
 * Fix ViewPort ctor
 *
 * Revision 1.16  2008/10/23 23:34:11  bdbcat
 * Cleanup
 *
 * Revision 1.15  2008/08/26 13:49:53  bdbcat
 * Better color scheme support
 *
 * Revision 1.14  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
 *
 * Revision 1.13  2008/04/10 00:58:53  bdbcat
 * Cleanup
 *
 * Revision 1.12  2008/03/30 23:26:50  bdbcat
 * Cleanup
 *
 * Revision 1.11  2008/01/10 03:39:06  bdbcat
 * Update for Mac OSX
 *
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

#include "bbox.h"

#include <wx/datetime.h>
#include <wx/treectrl.h>

#include "chart1.h"                 // for enum types

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
      class IDX_entry;
      class S57ObjectTree;
      class S57ObjectDesc;

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

typedef enum ownship_state_t
{
      SHIP_NORMAL        = 0,
      SHIP_LOWACCURACY,
      SHIP_INVALID
}_ownship_state_t;

enum {
      ID_S57QUERYTREECTRL =            10000
};

//----------------------------------------------------------------------------
// ViewPort
//----------------------------------------------------------------------------
class ViewPort
{
  public:
//  ctor
    ViewPort()  { bValid = false; skew = 0; view_scale_ppm = 1;}

//  Accessors
    bool IsValid() { return bValid; }

//  Generic
    double   clat;                   // center point
    double   clon;
    double   view_scale_ppm;
    double   skew;


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


      void SetViewPoint(double lat, double lon, double scale_ppm, double skew, int sample_mode);
      void SetVPScale(double sc);

      void GetPointPix(double rlat, double rlon, wxPoint *r);
      void GetPixPoint(int x, int y, double &lat, double &lon);
      void WarpPointerDeferred(int x, int y);
      void UpdateShips();
      void UpdateAIS();
      void FlushBackgroundRender(void);

      void SetColorScheme(ColorScheme cs);

      //    Accessors
      int GetCanvas_width(){ return canvas_width;}
      int GetCanvas_height(){ return canvas_height;}
      float GetVPScale(){return VPoint.view_scale_ppm;}
      float GetVPChartScale(){return VPoint.chart_scale;}
      double GetCanvasScaleFactor(){return m_canvas_scale_factor;}

//      void  SetbNewVP(bool f){ m_bNewVP = f;}
//      bool  GetbNewVP(){ return m_bNewVP;}

      void  SetbTCUpdate(bool f){ m_bTCupdate = f;}
      bool  GetbTCUpdate(){ return m_bTCupdate;}
      void  SetbShowCurrent(bool f){ m_bShowCurrent = f;}
      bool  GetbShowCurrent(){ return m_bShowCurrent;}
      void  SetbShowTide(bool f){ m_bShowTide = f;}
      bool  GetbShowTide(){ return m_bShowTide;}
      double GetPixPerMM(){ return m_pix_per_mm;}

      void SetOwnShipState(ownship_state_t state){ m_ownship_state = state;}

      bool ZoomCanvasIn(void);
      bool ZoomCanvasOut(void);
      bool PanCanvas(int dx, int dy);

      //Todo build more accessors
      bool        m_bFollow;
      wxCursor    *pCursorPencil;
      TCWin       *pCwin;
      ViewPort    VPoint;
      wxBitmap    *pscratch_bm;
      double      m_cursor_lon, m_cursor_lat;


private:
      bool        m_bShowCurrent;
      bool        m_bShowTide;
      int         cursor_region;
      bool        m_bTCupdate;

      wxRect      bbRect;

      wxPoint     r_rband;
      wxPoint     LastShipPoint;
      wxPoint     LastPredPoint;
      bool        m_bDrawingRoute;
      bool        m_bRouteEditing;
      bool        m_bMarkEditing;
      RoutePoint  *m_pRoutePointEditTarget;
      SelectItem  *m_pFoundPoint;
      bool        m_bChartDragging;


      Route       *m_pMouseRoute;
      double      m_prev_rlat;
      double      m_prev_rlon;
      RoutePoint  *m_prev_pMousePoint;
      Route       *m_pSelectedRoute;
//      Route       *m_pEditRoute;
      wxArrayPtrVoid *m_pEditRouteArray;
      RoutePoint  *m_pFoundRoutePoint;
      RoutePoint  *m_pFoundRoutePointSecond;

      AIS_Target_Data *m_pFoundAIS_Target_Data;
      AIS_Target_Data *m_pSnapshotAIS_Target_Data;

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

      double       m_canvas_scale_factor;    // converter....
                                    // useage....
                                    // true_chart_scale_on_display   = m_canvas_scale_factor / pixels_per_meter of displayed chart

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
      bool CheckEdgePan(int x, int y);
      void OnCursorTrackTimerEvent(wxTimerEvent& event);

      void DrawAllRoutesInBBox(wxDC& dc, wxBoundingBox& BltBBox);
      void DrawAllWaypointsInBBox(wxDC& dc, wxBoundingBox& BltBBox, bool bDrawMarksOnly);

      void DrawAllTidesInBBox(wxDC& dc, wxBoundingBox& BBox, bool bRebuildSelList,
                        bool bdraw_mono = false);
      void DrawAllCurrentsInBBox(wxDC& dc, wxBoundingBox& BBox, double skew_angle,
                           bool bRebuildSelList, bool bforce_redraw_currents, bool bdraw_mono = false);
      void DrawTCWindow(int x, int y, void *pIDX);
      void RenderChartOutline(wxDC *pdc, int dbIndex, ViewPort& vp, bool bdraw_mono = false);
      void RenderAllChartOutlines(wxDC *pdc, ViewPort& vp, bool bdraw_mono = false);
      wxBitmap *DrawTCCBitmap(bool bAddNewSelpoints = true);
      void AISDraw(wxDC& dc);
      void ScaleBarDraw( wxDC& dc, int x_origin, int y_origin );

      void EmbossDepthScale(wxMemoryDC *psource_dc, wxMemoryDC *pdest_dc, int emboss_ident);
      int *CreateEmbossMap(wxFont &font, int width, int height, char *str, ColorScheme cs);
      void CreateDepthUnitEmbossMaps(ColorScheme cs);
      wxBitmap CreateDimBitmap(wxBitmap &Bitmap, double factor);

      void JaggyCircle(wxDC &dc, wxPen pen, int x, int y, int radius);


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
      wxMemoryDC  m_dc_route;         // seen in mouse->edit->route

      double   m_ownship_predictor_minutes;      // Minutes shown on ownship position predictor graphic
                                                // defaults to 5

      int         m_emboss_width, m_emboss_height;
      int         *m_pEM_Feet;                // maps for depth unit emboss pattern
      int         *m_pEM_Meters;
      int         *m_pEM_Fathoms;

      double      m_pix_per_mm;     // pixels per millimeter on the screen

      double      m_true_scale_ppm;

      ownship_state_t   m_ownship_state;

      ColorScheme m_cs;

      wxBitmap    m_bmTideDay;
      wxBitmap    m_bmTideDusk;
      wxBitmap    m_bmTideNight;
      wxBitmap    m_bmCurrentDay;
      wxBitmap    m_bmCurrentDusk;
      wxBitmap    m_bmCurrentNight;


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

      bool        m_bForceTCRedraw;

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
      void SetObjectTree(void **pOD, int n_items);

      void SetSelectedItem(wxTreeItemId item_id);                  // a "notification" from Tree control

      wxString format_attributes(wxString &attr, int lcol, int rcol);

      //    Overrides
      void OnPaint ( wxPaintEvent& event );


      //    Data
      wxString          QueryResult;
      wxTextCtrl        *m_pQueryTextCtl;
      S57ObjectTree     *m_pTree;
      wxTreeItemId      m_root_id;

      int               m_n_items;
      void              **m_ppOD;

      wxTreeItemId      *m_id_array;                              // an array of wxTreeItemIDs
      int               m_char_width;

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

      //    Data
      wxString    *pQueryResult;
};


//----------------------------------------------------------------------------------------------------------
//    S57 Object Query Tree Control Specification
//----------------------------------------------------------------------------------------------------------
class S57ObjectTree: public wxTreeCtrl
{
      DECLARE_CLASS( S57ObjectTree )
      DECLARE_EVENT_TABLE()
public:
      /// Constructors
      S57ObjectTree( );
      S57ObjectTree( S57QueryDialog* parent, wxWindowID id = wxID_ANY,
                                        const wxPoint& pos = wxDefaultPosition,
                                        const wxSize& size = wxDefaultSize,
                                        long style = wxTR_HAS_BUTTONS );

      ~S57ObjectTree( );

      /// Initialise our variables
      void Init();

      //  Override events
      void OnItemExpanding( wxTreeEvent& event);
      void OnItemSelectChange( wxTreeEvent& event);

      //    Data
      S57QueryDialog    *m_parent;

};

class MyTreeItemData : public wxTreeItemData
{
public:
      MyTreeItemData(S57ObjectDesc *pOD){ m_pOD = pOD; }

      S57ObjectDesc     *m_pOD;
};

#endif

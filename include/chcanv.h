/******************************************************************************
 * $Id: chcanv.h,v 1.38 2009/12/26 21:10:41 bdbcat Exp $
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
 * Revision 1.38  2009/12/26 21:10:41  bdbcat
 * TCWIN
 *
 * Revision 1.37  2009/12/10 21:21:37  bdbcat
 * Beta 1210
 *
 * Revision 1.36  2009/11/18 01:26:42  bdbcat
 * 1.3.5 Beta 1117
 *
 * Revision 1.35  2009/09/25 15:02:38  bdbcat
 * Implement toplevel CM93 detail slider
 *
 * Revision 1.34  2009/09/18 02:49:38  bdbcat
 * Various, including AIS Info Window update, ship icons
 *
 * Revision 1.33  2009/09/11 20:42:29  bdbcat
 * Implement png graphics, new AIS Query dialog
 *
 * Revision 1.32  2009/09/01 22:17:15  bdbcat
 * New Methods
 *
 * Revision 1.31  2009/08/29 23:24:44  bdbcat
 * Various, including alert suppression logic
 *
 * Revision 1.30  2009/08/25 21:38:25  bdbcat
 * *** empty log message ***
 *
 * Revision 1.29  2009/08/22 01:22:04  bdbcat
 * Tracks
 *
 * Revision 1.28  2009/07/29 01:08:32  bdbcat
 * Implement Measure tool.
 *
 * Revision 1.27  2009/07/17 03:54:16  bdbcat
 * Add config option for Wheel Zoom to cursor.
 *
 * Revision 1.26  2009/07/16 02:41:10  bdbcat
 * Various
 *
 * Revision 1.25  2009/07/03 03:00:32  bdbcat
 * Improve AIS Dialogs.
 *
 * Revision 1.24  2009/06/25 02:37:04  bdbcat
 * Slow down mouse wheel, fix chart outlines near IDL.
 *
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
      class AISroWin;

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
      ID_S57QUERYTREECTRL =            10000,
      ID_AISDIALOGOK
};


//----------------------------------------------------------------------------
// ViewPort
//----------------------------------------------------------------------------
class ViewPort
{
  public:
//  ctor
    ViewPort()  { bValid = false; skew = 0; view_scale_ppm = 1;}

    wxPoint GetMercatorPixFromLL(double lat, double lon);
    void GetMercatorLLFromPix(const wxPoint &p, double *lat, double *lon);

//  Accessors
    bool IsValid() { return bValid; }

//  Generic
    double   clat;                   // center point
    double   clon;
    double   view_scale_ppm;
    double   skew;


    LLBBox   vpBBox;                // An un-skewed rectangular lat/lon bounding box
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


//    This is the callback function prototype used to call back registered overlay providers
typedef bool (*RenderOverlayCallBackFunction)(wxMemoryDC *pmdc, ViewPort *vp);


class OverlaySpec
{
      public:
            int                                 m_sequence;
            RenderOverlayCallBackFunction       m_render_callback;
};


class emboss_data
{
      public:
            emboss_data(){ pmap = NULL; }
            ~emboss_data(){ free(pmap); }

            int         *pmap;
            int         width;
            int         height;
      private:
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
      void OnChar(wxKeyEvent &event);
      void OnPaint(wxPaintEvent& event);
      void NowPaint();
      void Scroll(int dx, int dy);
      void CanvasPopupMenu(int x, int y, int seltype);
      void PopupMenuHandler(wxCommandEvent& event);
      void SetMyCursor(wxCursor *c);
      void LostMouseCapture(wxMouseCaptureLostEvent& event);

      bool Do_Hotkeys(wxKeyEvent &event);

      void SetViewPoint(double lat, double lon, double scale_ppm, double skew, int sample_mode);
      void SetVPScale(double sc);
      void SetViewPoint ( double lat, double lon);
      void ReloadVP ( void );

      void GetCanvasPointPix(double rlat, double rlon, wxPoint *r);
      void GetCanvasPixPoint(int x, int y, double &lat, double &lon);
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

      bool ZoomCanvasIn(double lat = 0., double lon = 0.);
      bool ZoomCanvasOut(double lat = 0., double lon = 0.);
      bool PanCanvas(int dx, int dy);

      bool RegisterOverlayProvider(int sequence, RenderOverlayCallBackFunction pcallback);
      bool UnRegisterOverlayProvider(int sequence, RenderOverlayCallBackFunction pcallback);

      void ShowGribDialog(void);

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
      wxArrayPtrVoid *m_pEditRouteArray;
      RoutePoint  *m_pFoundRoutePoint;
      RoutePoint  *m_pFoundRoutePointSecond;

      int         m_FoundAIS_MMSI;

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

      void DrawAllRoutesInBBox(wxDC& dc, wxBoundingBox& BltBBox, const wxRegion& clipregion);
      void DrawAllWaypointsInBBox(wxDC& dc, wxBoundingBox& BltBBox, const wxRegion& clipregion, bool bDrawMarksOnly);

      void DrawAllTidesInBBox(wxDC& dc, wxBoundingBox& BBox, bool bRebuildSelList,
                        bool bdraw_mono = false);
      void DrawAllCurrentsInBBox(wxDC& dc, wxBoundingBox& BBox, double skew_angle,
                           bool bRebuildSelList, bool bforce_redraw_currents, bool bdraw_mono = false);
      void DrawTCWindow(int x, int y, void *pIDX);
      void RenderChartOutline(wxDC *pdc, int dbIndex, ViewPort& vp, bool bdraw_mono = false);
      void RenderAllChartOutlines(wxDC *pdc, ViewPort& vp, bool bdraw_mono = false);
      wxBitmap *DrawTCCBitmap( wxDC *pbackground_dc, bool bAddNewSelpoints = true);

      void AISDraw(wxDC& dc);
      void ScaleBarDraw( wxDC& dc, int x_origin, int y_origin );

      void EmbossDepthScale(wxMemoryDC *psource_dc, wxMemoryDC *pdest_dc, int emboss_ident);
      emboss_data *CreateEmbossMapData(wxFont &font, int width, int height, const char *str, ColorScheme cs);
      void CreateDepthUnitEmbossMaps(ColorScheme cs);
      wxBitmap CreateDimBitmap(wxBitmap &Bitmap, double factor);

      void CreateOZEmbossMapData(ColorScheme cs);
      void EmbossOverzoomIndicator ( wxMemoryDC *temp_dc, wxMemoryDC *scratch_dc);

      void EmbossCanvas ( wxMemoryDC *psource_dc, wxMemoryDC *pdest_dc, emboss_data *pemboss, int x, int y);

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

      wxTimer     m_MouseWheelTimer;
      int         m_mouse_wheel_oneshot;
      int         m_last_wheel_dir;

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

      wxBitmap    *proute_bm;          // a bitmap and dc used to calculate route bounding box
      wxMemoryDC  m_dc_route;         // seen in mouse->edit->route

      double   m_ownship_predictor_minutes;      // Minutes shown on ownship position predictor graphic
                                                // defaults to 5

      emboss_data *m_pEM_Feet;                // maps for depth unit emboss pattern
      emboss_data *m_pEM_Meters;
      emboss_data *m_pEM_Fathoms;

      emboss_data *m_pEM_OverZoom;


      double      m_pix_per_mm;     // pixels per millimeter on the screen

      double      m_true_scale_ppm;

      ownship_state_t   m_ownship_state;

      ColorScheme m_cs;
      bool        m_bMeasure_Active;
      int         m_nMeasureState;
      Route       *m_pMeasureRoute;

      wxBitmap    m_bmTideDay;
      wxBitmap    m_bmTideDusk;
      wxBitmap    m_bmTideNight;
      wxBitmap    m_bmCurrentDay;
      wxBitmap    m_bmCurrentDusk;
      wxBitmap    m_bmCurrentNight;

      AISroWin    *m_pPopUpWin;

      wxImage     m_os_image_green_day;
      wxImage     m_os_image_green_dusk;
      wxImage     m_os_image_green_night;
      wxImage     m_os_image_red_day;
      wxImage     m_os_image_red_dusk;
      wxImage     m_os_image_red_night;
      wxImage     m_os_image_grey_day;
      wxImage     m_os_image_grey_dusk;
      wxImage     m_os_image_grey_night;

      wxImage     *m_pos_image_green;
      wxImage     *m_pos_image_red;
      wxImage     *m_pos_image_grey;

      wxArrayPtrVoid      m_OverlaySpecArray;

      wxImage     m_ship_pix_image;             //cached ship draw image for high overzoom
      int         m_cur_ship_pix;
      bool        m_cur_ship_pix_isgrey;


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
      int         val_off;


      float       tcv[24];
      bool        btc_valid;
      ChartCanvas *pParent;
      int         corr_mins;
      wxString    m_stz;
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
            ocpCursor(const char **xpm_data, long type, int hotSpotX=0, int hotSpotY=0);
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

      void SetColorScheme(ColorScheme cs);

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


class AISInfoWin;

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

      void OnClose(wxCloseEvent& event);
      void OnIdOKClick( wxCommandEvent& event );
      void OnMove( wxMoveEvent& event );

      void CreateControls();

      void SetText(wxString &text_string);
      void SetColorScheme(ColorScheme cs);

      void UpdateText(void);
      void SetMMSI(int mmsi){ m_MMSI = mmsi; }
      int  GetMMSI(void){ return m_MMSI; }

      //    Data
      int               m_MMSI;
      AISInfoWin        *m_pQueryTextCtl;
      ColorScheme       m_colorscheme;
      wxBoxSizer        *m_pboxSizer;
      int               m_nl;
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



//----------------------------------------------------------------------------
// AIS Rollover Window
//----------------------------------------------------------------------------
class AISroWin: public wxWindow
{
      public:
            AISroWin(wxWindow *parent);
            ~AISroWin();

            void OnPaint(wxPaintEvent& event);

            void SetColorScheme(ColorScheme cs);
            void SetString(wxString &s){ m_string = s; }
            void SetPosition(wxPoint pt){ m_position = pt; }
            void SetBitmap(void);


      private:

            wxString          m_string;
            wxSize            m_size;
            wxPoint           m_position;
            wxBitmap          *m_pbm;

            DECLARE_EVENT_TABLE()
};


//------------------------------------------------------------------------------
//    AISInfoWin Specification
//------------------------------------------------------------------------------

class AISInfoWin : public wxWindow
{
      public:
            AISInfoWin ( wxWindow *parent, wxWindowID id = -1, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                         long style = 0, const wxString& name = _T(""));

            ~AISInfoWin(void);

            void OnPaint(wxPaintEvent& event);
            void AppendText(wxString &text);
            void Clear(void){}
            void SetInsertionPoint(int pt){}
            wxSize GetOptimumSize(int *pn_nl = NULL, int *pn_cmax = NULL);
            void SetHPad(int d){ m_offsetx = d; }
            void SetVPad(int d){ m_offsety = d; }

            wxString    m_text;
            int         m_maxtl;

            int         m_offsetx, m_offsety;

            DECLARE_EVENT_TABLE()
};

//------------------------------------------------------------------------------
//    CM93 Detail Slider Specification
//------------------------------------------------------------------------------

class CM93DSlide : public wxDialog
{
      public:
            CM93DSlide ( wxWindow *parent, wxWindowID id, int value, int minValue, int maxValue,
                         const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& title = _T(""));

            ~CM93DSlide(void);

            void Init(void);
            bool Create( wxWindow *parent, wxWindowID id, int value, int minValue, int maxValue,
                                     const wxPoint& pos, const wxSize& size, long style, const wxString& title);

            void OnCancelClick( wxCommandEvent& event );
            void OnMove( wxMoveEvent& event );
            void OnThumbRelease( wxScrollEvent& event);
            void OnClose(wxCloseEvent& event);


            wxSlider          *m_pCM93DetailSlider;
            wxWindow          *m_pparent;

            DECLARE_EVENT_TABLE()
};


#endif

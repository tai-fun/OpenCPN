/******************************************************************************
 * $Id: navutil.h,v 1.2 2006/09/21 01:38:23 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Navigation Utility Functions
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
 * $Log: navutil.h,v $
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.8  2006/04/19 02:04:55  dsr
 * *** empty log message ***
 *
 * Revision 1.7  2006/04/19 00:57:39  dsr
 * Implement FontMgr and X11FontPicker
 *
 * Revision 1.6  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.5  2006/02/23 01:23:12  dsr
 * Cleanup
 *
 *
 *
 */


#ifndef __NAVUTIL__
#define __NAVUTIL__


#include <wx/config.h>
#include <wx/confbase.h>
#include <wx/fileconf.h>

#ifdef __WXMSW__
#include <wx/msw/regconf.h>
#include <wx/msw/iniconf.h>
#endif

#include "bbox.h"




// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------

class Route;

//    class declarations

typedef struct tagVECTOR2D  {
  double     x;
  double     y;
} VECTOR2D, *PVECTOR2D;


class RoutePoint
{
public:
      Route             *m_pParentRoute;
      float             rlat;
      float             rlon;
      int               nPoint;
      float             m_seg_len;              // length in NMI to this point
                                                // undefined for starting point
      bool              m_bPtIsSelected;

};

WX_DECLARE_LIST(RoutePoint, RoutePointList);// establish class as list member


//----------------------------------------------------------------------------
//    Route
//----------------------------------------------------------------------------
class Route : public wxObject
{
public:
      Route(void);
      ~Route(void);

      RoutePoint *AddPoint(float rlat, float rlon);
      RoutePoint *GetPoint(int nPoint, float *prlat, float *prlon);
      RoutePoint *InsertPoint(int nP, float rlat, float rlon);
      void DrawPointWhich(wxDC& dc, int iPoint, wxPoint *rpn);
      void DrawPointLL(wxDC& dc, float rlat, float rlon, int iPoint, wxPoint *rpn);
      void DrawSegment(wxDC& dc, wxPoint *rp1, wxPoint *rp2);
      void DrawRoute(wxDC& dc);
      RoutePoint *GetLastPoint();
      void DeletePoint(RoutePoint *rp);
      void DeSelectRoute();
      void CalculateBBox();
      void UpdateSegmentDistances();
      void DrawRouteLine(wxDC& dc, int xa, int ya, int xb, int yb);



      int         m_nPoints;
      int         ConfigRouteNum;
      bool        m_bRtIsSelected;
      bool        m_bRtIsActive;
      int         m_nRouteActivePoint;
      bool        m_bIsBeingCreated;
      bool        m_bIsBeingEdited;

      RoutePointList    *pRoutePointList;

      wxBoundingBox     BBox;


};

WX_DECLARE_LIST(Route, RouteList);                    // establish class Route as list member



//----------------------------------------------------------------------------
//    Config
//----------------------------------------------------------------------------
class MyConfig:public wxFileConfig
{
public:

      MyConfig(wxString & appName);
      MyConfig(const wxString &appName, const wxString &vendorName,
                              const wxString &LocalFileName);


      int LoadMyConfig(int iteration);
      virtual bool AddNewRoute(Route *pr, int ConfigRouteNum = -1);
      virtual bool UpdateRoute(Route *pr);
      virtual bool DeleteRoute(Route *pr);
      virtual bool UpdateChartDirs(wxArrayString *pdirlist);
      virtual void UpdateSettings();

      int NextRouteNum;


//    Members describing the current config and runtime environment
      wxPen *pRoutePen;
      wxPen *pSelectedRoutePen;
      wxPen *pActiveRoutePen;
      wxPen *pActiveRoutePointPen;


      float st_lat, st_lon, st_view_scale;            // startup values
      bool  st_bFollow;
      bool  st_bShowS57Text;

//    These members are set/reset in Options dialog
      bool  m_bShowDebugWindows;

      int   m_nDisplayCategory;
      int   m_nSymbolStyle;
      int   m_nBoundaryStyle;
      int   m_nColorScheme;

};


//    Constants for SelectItem.m_seltype
enum
{
      SELTYPE_ROUTEPOINT,
      SELTYPE_ROUTESEGMENT,
      SELTYPE_TIDEPOINT,
      SELTYPE_CURRENTPOINT,
      SELTYPE_ROUTECREATE,
      SELTYPE_UNKNOWN
};

//-----------------------------------------------------------------------------
//          Selectable Item
//-----------------------------------------------------------------------------

class SelectItem
{
public:
      float m_slat;
      float m_slon;
      float m_slat2;
      float m_slon2;
      int   m_seltype;
      bool  m_bIsSelected;
      void  *m_pData1;
      void  *m_pData2;
};



WX_DECLARE_LIST(SelectItem, SelectableItemList);// establish class as list member



class Select
{
public:

      Select();
      ~Select();

      bool AddSelectablePoint(float slat, float slon, RoutePoint *pRoutePointAdd);
      bool AddSelectableRouteSegment(float slat1, float slon1, float slat2, float slon2,
                                                         RoutePoint *pRoutePointAdd1,
                                                         RoutePoint *pRoutePointAdd2);

      SelectItem *FindSelection(float slat, float slon, int fseltype, float SelectRadius);

      bool DeleteAllSelectableRouteSegments(Route *);
      bool DeleteAllSelectableRoutePoints(Route *);
      bool AddAllSelectableRouteSegments(Route *pr);
      bool AddAllSelectableRoutePoints(Route *pr);

//    Tide/Current Point Support
      bool AddSelectableTCPoint(float slat, float slon, void *data, int fseltype);
      bool DeleteAllTCPoints(void);

//    Delete all selectable points in list by type
      bool DeleteAllSelectableTypePoints(int SeltypeToDelete);



private:

      SelectableItemList      *pSelectList;

};

//---------------------------------------------------------------------------------
//          Private Font Manager
//---------------------------------------------------------------------------------
class MyFontDesc
{
public:

      MyFontDesc(const char *DialogString, const char *ConfigString, wxFont *pFont);
      ~MyFontDesc();

      wxString    *m_dialogstring;
      wxString    *m_configstring;
      wxString    *m_nativeInfo;
      wxFont      *m_font;
};


WX_DECLARE_LIST(MyFontDesc, FontList);

class FontMgr
{
public:
      FontMgr();
      ~FontMgr();

      wxFont *GetFont(wxString &TextElement);

      int GetNumFonts(void);
      wxString *GetConfigString(int i);
      wxString *GetDialogString(int i);
      wxString *GetNativeDesc(int i);
      void LoadFontNative(wxString *pConfigString, wxString *pNativeDesc);
      bool SetFont(wxString &TextElement, wxFont *pFont);

private:

      FontList          *m_fontlist;
      wxFont            *pDefFont;

};

/*
#include <wx/fontdlg.h>

class WXDLLEXPORT X11FontPicker : public wxGenericFontDialog
{
public:
      X11FontPicker(wxFrame *parent);
      ~X11FontPicker();

      virtual void CreateWidgets();


};
*/

/*
 * X11FontPicker DIALOG
 */
#include <wx/fontdlg.h>

class WXDLLEXPORT wxChoice;
class WXDLLEXPORT wxText;
class WXDLLEXPORT wxCheckBox;
class WXDLLEXPORT MyFontPreviewer;

/*
enum
{
      wxID_FONT_UNDERLINE = 3000,
      wxID_FONT_STYLE,
      wxID_FONT_WEIGHT,
      wxID_FONT_FAMILY,
      wxID_FONT_COLOUR,
      wxID_FONT_SIZE
};
*/

class WXDLLEXPORT X11FontPicker : public wxFontDialogBase
{
      public:
            X11FontPicker() { Init(); }
            X11FontPicker(wxWindow *parent, const wxFontData& data)  : wxFontDialogBase(parent, data) { Init(); }
            virtual ~X11FontPicker();

            virtual int ShowModal();


    // deprecated, for backwards compatibility only
            X11FontPicker(wxWindow *parent, const wxFontData *data)
      : wxFontDialogBase(parent, data) { Init(); }

    // Internal functions
            void OnCloseWindow(wxCloseEvent& event);

            virtual void CreateWidgets();
            virtual void InitializeFont();

            void OnChangeFont(wxCommandEvent& event);
            void OnChangeFace(wxCommandEvent& event);

      protected:
    // common part of all ctors
            void Init();

            virtual bool DoCreate(wxWindow *parent);
            void InitializeAllAvailableFonts();
            void SetChoiceOptionsFromFacename(wxString &facename);
            void DoFontChange(void);

            wxFont dialogFont;

            wxChoice    *familyChoice;
            wxChoice    *styleChoice;
            wxChoice    *weightChoice;
            wxChoice    *colourChoice;
            wxCheckBox  *underLineCheckBox;
            wxChoice    *pointSizeChoice;

            MyFontPreviewer *m_previewer;
            bool        m_useEvents;

            wxArrayString     *pFaceNameArray;

            wxFont            *pPreviewFont;

    //  static bool fontDialogCancelled;
            DECLARE_EVENT_TABLE()
                        DECLARE_DYNAMIC_CLASS(X11FontPicker)
};






//---------------------------------------------------------------------------------
//      Vector Stuff for Hit Test Algorithm
//---------------------------------------------------------------------------------

extern "C" double vGetLengthOfNormal(PVECTOR2D a, PVECTOR2D b, PVECTOR2D n);
extern "C" double vDotProduct(PVECTOR2D v0, PVECTOR2D v1);
extern "C" PVECTOR2D vAddVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v);
extern "C" PVECTOR2D vSubtractVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v);
extern "C" double vVectorMagnitude(PVECTOR2D v0);
extern "C" double vVectorSquared(PVECTOR2D v0);

#endif

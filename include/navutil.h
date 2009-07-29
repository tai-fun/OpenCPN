/******************************************************************************
 * $Id: navutil.h,v 1.13 2009/07/29 00:50:09 bdbcat Exp $
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
 * Revision 1.13  2009/07/29 00:50:09  bdbcat
 * Update Route Draw logic
 *
 * Revision 1.12  2009/07/16 02:44:00  bdbcat
 * Various, esp Export Route.
 *
 * Revision 1.11  2009/06/28 03:34:39  bdbcat
 * Save GPX_IO directory.
 *
 * Revision 1.10  2009/06/03 03:22:04  bdbcat
 * Correct GPX Route import logic
 *
 * Revision 1.9  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.8  2008/12/19 01:46:39  bdbcat
 * Add selectable depth unit conversion for S57 charts
 *
 * Revision 1.7  2008/08/26 13:49:53  bdbcat
 * Better color scheme support
 *
 * Revision 1.6  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
 *
 * Revision 1.5  2008/03/30 23:29:52  bdbcat
 * Cleanup/optimize
 *
 * Revision 1.4  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.3  2006/11/01 02:18:45  dsr
 * AIS Support
 *
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
#include <wx/xml/xml.h>

#ifdef __WXMSW__
#include <wx/msw/regconf.h>
#include <wx/msw/iniconf.h>
#endif

#include "bbox.h"
#include "s52s57.h"



extern "C" float DistGreatCircle(double slat, double slon, double dlat, double dlon);
extern bool LogMessageOnce(wxString &msg);
extern wxString toSDMM(int NEflag, double a);

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

class Hyperlink { // toh, 2009.02.14
      public:
            wxString DescrText;
            wxString Link;
            wxString Type;
};

WX_DECLARE_LIST(Hyperlink, HyperlinkList);// establish class as list member


class RoutePoint
{
public:
      RoutePoint(double lat, double lon, const wxString& icon_ident, const wxString& name, wxString *pGUID = NULL);
      ~RoutePoint(void);
      void DrawPoint(wxDC& dc, wxPoint *rpn = NULL);
      void DrawTransparentBox(wxDC& dc, int x, int y, int size_x, int size_y,
                                          unsigned char rval, unsigned char gval, unsigned char bval, unsigned char transparency);
      void ReLoadIcon(void);

      void SetPosition(double lat, double lon);
      void CalculateDCRect(wxDC& dc, wxRect *prect);

      bool IsSame(RoutePoint *pOtherRP);        // toh, 2009.02.11

      float             m_lat;
      float             m_lon;
      float             m_seg_len;              // length in NMI to this point
                                                // undefined for starting point
      bool              m_bPtIsSelected;
      bool              m_bIsBeingEdited;
      bool              m_bIsInRoute;
      bool              m_bIsolatedMark;        // This is an isolated mark, created by drop mark, or GPX-In, or config file load

      bool              m_bIsActive;
      int               m_ConfigWPNum;
      wxString          m_MarkName;
      wxString          m_MarkDescription;
      wxString          m_GUID;
      wxString          m_IconName;
      wxBitmap          *m_pbmIcon;
      bool              m_bBlink;
      bool              m_bDynamicName;
      bool              m_bShowName;
      wxRect            CurrentRect_in_DC;
      int               m_NameLocationOffsetX;
      int               m_NameLocationOffsetY;

      HyperlinkList     *m_HyperlinkList; // toh, 2009.02.14

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

      void AddPoint(RoutePoint *pNewPoint, bool b_rename_in_sequence = true);
      void AddTentativePoint(const wxString& GUID);
      RoutePoint *GetPoint(int nPoint);
      int GetIndexOf(RoutePoint *prp);
      RoutePoint *InsertPointBefore(RoutePoint *pRP, float rlat, float rlon, bool bRenamePoints = false);
      void DrawPointWhich(wxDC& dc, int iPoint, wxPoint *rpn);
      void DrawSegment(wxDC& dc, wxPoint *rp1, wxPoint *rp2, double scale_ppm, bool bdraw_arrow);
      void DrawRoute(wxDC& dc, double scale_ppm);
      RoutePoint *GetLastPoint();
      void DeletePoint(RoutePoint *rp, bool bRenamePoints = false);
      void RemovePoint(RoutePoint *rp, bool bRenamePoints = false);
      void DeSelectRoute();
      void CalculateBBox();
      void UpdateSegmentDistances();
      void CalculateDCRect(wxDC& dc_route, wxRect *prect, double scale_ppm);
      int GetnPoints(void){ return m_nPoints; }
      void Reverse(bool bRenamePoints = false);
      void RebuildGUIDList(void);
      void RenameRoutePoints();
      void ReloadRoutePointIcons();
      wxString GetNewMarkSequenced(void);
      void AssembleRoute();
      bool IsEqualTo(Route *ptargetroute);
      void ClearHighlights(void);

      bool SendToGPS(wxString& com_name, bool bsend_waypoints, wxGauge *pProgress);

      int         m_ConfigRouteNum;
      bool        m_bRtIsSelected;
      bool        m_bRtIsActive;
      RoutePoint  *m_pRouteActivePoint;
      bool        m_bIsBeingCreated;
      bool        m_bIsBeingEdited;
      double      m_route_length;
      wxString    m_RouteNameString;
      wxString    m_RouteStartString;
      wxString    m_RouteEndString;

      wxArrayString      RoutePointGUIDList;
      RoutePointList     *pRoutePointList;

      wxBoundingBox     BBox;
      wxRect      active_pt_rect;

private:
      void DrawRouteLine(wxDC& dc, int xa, int ya, int xb, int yb, double scale_ppm, bool bdraw_arrow);
      int         m_nPoints;
      int         m_nm_sequence;


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
      virtual bool DeleteConfigRoute(Route *pr);

      virtual bool AddNewWayPoint(RoutePoint *pWP, int ConfigRouteNum = -1);
      virtual bool UpdateWayPoint(RoutePoint *pWP);
      virtual bool DeleteWayPoint(RoutePoint *pWP);

      virtual bool UpdateChartDirs(wxArrayString *pdirlist);
      virtual void UpdateSettings();

/*
      void CreateXMLNavObj(void);
      void CreateXMLRoutePoints(void);
      wxXmlNode *CreateMarkNode(RoutePoint *pr);
      void WriteXMLNavObj(const wxString& file);

      wxXmlDocument     *m_pXMLNavObj;
      wxXmlNode         *m_XMLrootnode;
*/
      void ExportGPX(wxWindow* parent);   // toh, 2009.02.15
      void ImportGPX(wxWindow* parent);   // toh, 2009.02.15

//    toh, 2009.02.10
      void CreateGPXNavObj(void);
      void CreateGPXRoutePoints(void);
      wxXmlNode *CreateGPXWptNode(RoutePoint *pr);
      wxXmlNode *CreateGPXRptNode(RoutePoint *pr,int nbr);
      void WriteXMLNavObj(const wxString& file);
      bool WptIsInRouteList(RoutePoint *pr);

      // toh, 2009.02.17
      RoutePoint *GPXLoadWaypoint(wxXmlNode* wptnode,bool &WpExists,bool LoadRoute=false);
      void GPXLoadRoute(wxXmlNode* rtenode);

      void CreateGPXRoute(Route *pRoute);
      bool ExportGPXRoute(wxWindow* parent, Route *pRoute);

      wxXmlDocument     *m_pXMLNavObj;
      wxXmlNode         *m_XMLrootnode;
//    toh, end

      int m_NextRouteNum;
      int m_NextWPNum;

      float st_lat, st_lon, st_view_scale;            // startup values
      bool  st_bFollow;

      wxString    m_gpx_path;

//    These members are set/reset in Options dialog
      bool  m_bShowDebugWindows;

};


//    Constants for SelectItem.m_seltype
enum
{
      SELTYPE_ROUTEPOINT,
      SELTYPE_ROUTESEGMENT,
      SELTYPE_TIDEPOINT,
      SELTYPE_CURRENTPOINT,
      SELTYPE_ROUTECREATE,
      SELTYPE_UNKNOWN,
      SELTYPE_AISTARGET,
      SELTYPE_MARKPOINT,

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
      bool UpdateSelectableRouteSegments(RoutePoint *prp);

//    Generic Point Support
//      e.g. Tides/Currents and AIS Targets
      bool AddSelectablePoint(float slat, float slon, void *data, int fseltype);
      bool DeleteAllPoints(void);
      bool DeleteSelectablePoint(void *data, int SeltypeToDelete);
      bool ModifySelectablePoint(float slat, float slon, void *data, int fseltype);

//    Delete all selectable points in list by type
      bool DeleteAllSelectableTypePoints(int SeltypeToDelete);

      //  Accessors

      SelectableItemList *GetSelectList(){return pSelectList;}

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

      wxFont *GetFont(const wxString &TextElement);

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
//            X11FontPicker(wxWindow *parent, const wxFontData *data)
//      : wxFontDialogBase(parent, data) { Init(); }

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

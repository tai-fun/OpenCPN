/******************************************************************************
 * $Id: routeman.h,v 1.7 2009/08/03 03:08:51 bdbcat Exp $
 *
 * Project:  OpenCP
 * Purpose:  Route Manager
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
 * $Log: routeman.h,v $
 * Revision 1.7  2009/08/03 03:08:51  bdbcat
 * Improve Waypoint logic
 *
 * Revision 1.6  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.5  2008/11/12 04:15:44  bdbcat
 * Support Garmin Devices / Cleanup
 *
 * Revision 1.4  2008/08/29 02:24:18  bdbcat
 * Redefine IconImageList
 *
 * Revision 1.3  2008/08/26 13:49:53  bdbcat
 * Better color scheme support
 *
 * Revision 1.2  2008/03/30 23:29:52  bdbcat
 * Cleanup/optimize
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.4  2006/04/19 02:05:18  dsr
 * Compute Normal arrival distance
 *
 * Revision 1.3  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.2  2006/02/23 01:23:57  dsr
 * Cleanup
 *
 *
 */


#ifndef __ROUTEMAN_H__
#define __ROUTEMAN_H__


#include "chart1.h"                 // for ColorScheme definition
#include <wx/imaglist.h>

#include "nmea0183.h"

//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------
#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */
#endif



//    Constants for SendToGps... Dialog
#define ID_STGDIALOG 10005
#define SYMBOL_STG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_STG_TITLE _("Send Route To GPS")
#define SYMBOL_STG_IDNAME ID_STGDIALOG
#define SYMBOL_STG_SIZE wxSize(500, 500)
#define SYMBOL_STG_POSITION wxDefaultPosition

enum {
      ID_STG_CANCEL =            10000,
      ID_STG_OK,
      ID_STG_CHOICE_COMM
};

//----------------------------------------------------------------------------
//    forward class declarations
//----------------------------------------------------------------------------

class Route;
class RoutePoint;
class RoutePointList;

//    List definitions for Waypoint Manager Icons

class markicon_bitmap_list_type;
class markicon_key_list_type;
class markicon_description_list_type;

class MarkIcon
{
      public:
            wxBitmap   *picon_bitmap;
            wxString   icon_name;
            wxString   icon_description;
};


//----------------------------------------------------------------------------
//   Routeman
//----------------------------------------------------------------------------

class Routeman
{
public:
      Routeman();
      ~Routeman();

      void AssembleAllRoutes(void);
      void DeleteRoute(Route *pRoute);
      Route *FindRouteContainingWaypoint(RoutePoint *pWP);
      wxArrayPtrVoid *GetRouteArrayContaining(RoutePoint *pWP);

      bool ActivateRoute(Route *pActivate);
      bool ActivateRoutePoint(Route *pA, RoutePoint *pRP);
      bool ActivateNextPoint(Route *pr);
      bool UpdateProgress();
      bool UpdateAutopilot();
      bool DeactivateRoute();

      void SetColorScheme(ColorScheme cs);

      Route *GetpActiveRoute(){ return pActiveRoute;}
      RoutePoint *GetpActivePoint(){ return pActivePoint;}
      float GetCurrentRngToActivePoint(){ return CurrentRngToActivePoint;}          //TODO all these need to be doubles
      float GetCurrentBrgToActivePoint(){ return CurrentBrgToActivePoint;}
      float GetCurrentRngToActiveNormalArrival(){ return CurrentRangeToActiveNormalCrossing;}
      float GetCurrentXTEToActivePoint(){ return CurrentXTEToActivePoint;}
      float GetCurrentSegmentCourse(){ return CurrentSegmentCourse;}
      int   GetXTEDir(){ return XTEDir;}

      wxPen   * GetRoutePen(void){return m_pRoutePen;}
      wxPen   * GetSelectedRoutePen(void){return m_pSelectedRoutePen;}
      wxPen   * GetActiveRoutePen(void){return m_pActiveRoutePen;}
      wxPen   * GetActiveRoutePointPen(void){return m_pActiveRoutePointPen;}
      wxPen   * GetRoutePointPen(void){return m_pRoutePointPen;}
      wxBrush * GetRouteBrush(void){return m_pRouteBrush;}
      wxBrush * GetSelectedRouteBrush(void){return m_pSelectedRouteBrush;}
      wxBrush * GetActiveRouteBrush(void){return m_pActiveRouteBrush;}
      wxBrush * GetActiveRoutePointBrush(void){return m_pActiveRoutePointBrush;}
      wxBrush * GetRoutePointBrush(void){return m_pRoutePointBrush;}

      bool        m_bDataValid;

private:
      Route       *pActiveRoute;
      RoutePoint  *pActivePoint;
      float       RouteBrgToActivePoint;        //TODO all these need to be doubles
      float       CurrentSegmentBeginLat;
      float       CurrentSegmentBeginLon;
      float       CurrentRngToActivePoint;
      float       CurrentBrgToActivePoint;
      float       CurrentXTEToActivePoint;
      float       CourseToRouteSegment;
      float       CurrentRangeToActiveNormalCrossing;
      RoutePoint  *pActiveRouteSegmentBeginPoint;
      RoutePoint  *pRouteActivatePoint;
      float       CurrentSegmentCourse;
      int         XTEDir;
      bool        m_bArrival;
      wxPen       *m_pRoutePen;
      wxPen       *m_pSelectedRoutePen;
      wxPen       *m_pActiveRoutePen;
      wxPen       *m_pActiveRoutePointPen;
      wxPen       *m_pRoutePointPen;
      wxBrush     *m_pRouteBrush;
      wxBrush     *m_pSelectedRouteBrush;
      wxBrush     *m_pActiveRouteBrush;
      wxBrush     *m_pActiveRoutePointBrush;
      wxBrush     *m_pRoutePointBrush;


      NMEA0183    m_NMEA0183;                         // For autopilot output

};

//----------------------------------------------------------------------------
//   Route "Send to GPS..." Dialog Definition
//----------------------------------------------------------------------------

class SendToGpsDlg : public wxDialog
{
      DECLARE_DYNAMIC_CLASS( SendToGpsDlg )
      DECLARE_EVENT_TABLE()

 public:
       SendToGpsDlg();
       SendToGpsDlg(  wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style );
       ~SendToGpsDlg( );

       bool Create( wxWindow* parent, wxWindowID id = SYMBOL_STG_IDNAME, const wxString& caption = SYMBOL_STG_TITLE,
                    const wxPoint& pos = SYMBOL_STG_POSITION, const wxSize& size = SYMBOL_STG_SIZE,
                    long style = SYMBOL_STG_STYLE);
       void SetRoute(Route *pRoute){m_pRoute = pRoute;}

private:
      void CreateControls();

      void OnCancelClick( wxCommandEvent& event );
      void OnSendClick( wxCommandEvent& event );

      Route       *m_pRoute;
      wxComboBox  *m_itemCommListBox;
      wxGauge     *m_pgauge;
      wxButton    *m_CancelButton;
      wxButton    *m_SendButton;

};



//----------------------------------------------------------------------------
//   WayPointman
//----------------------------------------------------------------------------

class WayPointman
{
public:
      WayPointman();
      ~WayPointman();
      wxBitmap *GetIconBitmap(const wxString& icon_key);
      int GetIconIndex(const wxBitmap *pbm);
      int GetNumIcons(void){ return m_nIcons; }
      wxString CreateGUID(RoutePoint *pRP);
      RoutePoint *GetNearbyWaypoint(double lat, double lon, double radius_meters);
      void SetColorScheme(ColorScheme cs);

      wxBitmap *GetIconBitmap(int index);
      wxString *GetIconDescription(int index);
      wxString *GetIconKey(int index);

      wxImageList *Getpmarkicon_image_list(void);

      RoutePointList    *m_pWayPointList;

private:
      void ProcessIcon(wxImage *pimage, wxString key, wxString description);

      wxBitmap *CreateDimBitmap(wxBitmap *pBitmap, double factor);

      int m_nIcons;

      wxImageList       *pmarkicon_image_list;        // Current wxImageList, updated on colorscheme change

      wxArrayPtrVoid    DayIconArray;
      wxArrayPtrVoid    DuskIconArray;
      wxArrayPtrVoid    NightIconArray;

      wxArrayPtrVoid    *m_pcurrent_icon_array;

};

#endif

/******************************************************************************
 * $Id: routeman.h,v 1.3 2008/08/26 13:49:53 bdbcat Exp $
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


#include "chart1.h"                 // for hash table definition
#include <wx/imaglist.h>
//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------
#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */
#endif

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

      bool ActivateRoute(Route *pActivate);
      bool ActivateRoutePoint(Route *pA, RoutePoint *pRP);
      bool ActivateNextPoint(Route *pr);
      bool UpdateProgress();
      bool UpdateAutopilot();
      bool DeactivateRoute();

      void SetColorScheme(ColorScheme cs);

      Route *GetpActiveRoute(){ return pActiveRoute;}
      RoutePoint *GetpActivePoint(){ return pActivePoint;}
      float GetCurrentRngToActivePoint(){ return CurrentRngToActivePoint;}
      float GetCurrentBrgToActivePoint(){ return CurrentBrgToActivePoint;}
      float GetCurrentRngToActiveNormalArrival(){ return CurrentRangeToActiveNormalCrossing;}
      float GetCurrentXTEToActivePoint(){ return CurrentXTEToActivePoint;}
      float GetCurrentSegmentCourse(){ return CurrentSegmentCourse;}
      int   GetXTEDir(){ return XTEDir;}

      wxPen * GetRoutePen(void){return m_pRoutePen;}
      wxPen * GetSelectedRoutePen(void){return m_pSelectedRoutePen;}
      wxPen * GetActiveRoutePen(void){return m_pActiveRoutePen;}
      wxPen * GetActiveRoutePointPen(void){return m_pActiveRoutePointPen;}
      wxPen * GetRoutePointPen(void){return m_pRoutePointPen;}

      bool        m_bDataValid;

private:
      Route       *pActiveRoute;
      RoutePoint  *pActivePoint;
      float       RouteBrgToActivePoint;
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

      void SetColorScheme(ColorScheme cs);

      wxBitmap *GetIconBitmap(int index);
      wxString *GetIconDescription(int index);
      wxString *GetIconKey(int index);

      wxImageList *Getpmarkicon_image_list(void){return pmarkicon_image_list;}

      RoutePointList    *m_pWayPointList;

private:
      wxBitmap *CreateDimBitmap(wxBitmap *pBitmap, double factor);

      int m_nIcons;

      wxImageList       *pmarkicon_image_list;        // Current wxImageList, updated on colorscheme change

      wxArrayPtrVoid    DayIconArray;
      wxArrayPtrVoid    DuskIconArray;
      wxArrayPtrVoid    NightIconArray;

      wxArrayPtrVoid    *m_pcurrent_icon_array;

};

#endif

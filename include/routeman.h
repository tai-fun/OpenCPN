/******************************************************************************
 * $Id: routeman.h,v 1.2 2008/03/30 23:29:52 bdbcat Exp $
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

      Route *GetpActiveRoute(){ return pActiveRoute;}
      RoutePoint *GetpActivePoint(){ return pActivePoint;}
      float GetCurrentRngToActivePoint(){ return CurrentRngToActivePoint;}
      float GetCurrentBrgToActivePoint(){ return CurrentBrgToActivePoint;}
      float GetCurrentRngToActiveNormalArrival(){ return CurrentRangeToActiveNormalCrossing;}
      float GetCurrentXTEToActivePoint(){ return CurrentXTEToActivePoint;}
      float GetCurrentSegmentCourse(){ return CurrentSegmentCourse;}
      int   GetXTEDir(){ return XTEDir;}

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

      wxBitmap *GetIconBitmap(int index);
      wxString *GetIconDescription(int index);
      wxString *GetIconKey(int index);

      RoutePointList    *m_pWayPointList;

//      string_to_pchar_hash      markicon_xpm_hash;         // hash map of [static] mark icon xpms
//      string_to_pbitmap_hash    markicon_bitmap_hash;      // and to created bitmaps with same index
//      string_to_string_hash     markicon_description_hash; // and to nice readable description of Icon

      markicon_description_list_type      *pmarkicon_description_list;
      markicon_bitmap_list_type           *pmarkicon_bitmap_list;
      markicon_key_list_type              *pmarkicon_key_list;
      wxImageList                         *pmarkicon_image_list;


private:
      int m_nIcons;

};

#endif

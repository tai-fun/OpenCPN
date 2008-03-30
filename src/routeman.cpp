/******************************************************************************
 * $Id: routeman.cpp,v 1.6 2008/03/30 22:11:41 bdbcat Exp $
 *
 * Project:  OpenCPN
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
<<<<<<< routeman.cpp
 * $Log: routeman.cpp,v $
 * Revision 1.6  2008/03/30 22:11:41  bdbcat
 * Add RoutePoint manager
 *
=======
 * $Log: routeman.cpp,v $
 * Revision 1.6  2008/03/30 22:11:41  bdbcat
 * Add RoutePoint manager
 *
 * Revision 1.5  2008/01/12 06:20:56  bdbcat
 * Update for Mac OSX/Unicode
 *
>>>>>>> 1.5
 * Revision 1.4  2007/06/10 02:32:30  bdbcat
 * Improve mercator bearing calculation
 *
 * Revision 1.3  2007/05/03 13:23:56  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.2  2006/09/21 01:37:36  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.3  2006/08/04 11:42:02  dsr
 * no message
 *
 * Revision 1.2  2006/07/28 20:38:19  dsr
 * New AP interface
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.5  2006/04/19 02:01:56  dsr
 * Compute Normal arrival distance
 *
 * Revision 1.4  2006/03/16 03:08:24  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/02/23 01:46:00  dsr
 * Cleanup
 *
 *
 */

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "wx/image.h"

#include "dychart.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <wx/listimpl.cpp>

#ifdef __WXMSW__
#if ocpnUSE_MSW_SERCOMM
        #include "sercomm.h"
#endif
#endif

#include "routeman.h"
#include "chcanv.h"
#include "concanv.h"
#include "nmea.h"
#include "nmea0183/nmea0183.h"
#include "navutil.h"
#include "chartbase.h"
#include "georef.h"


//    Include a (large) set of XPM images for mark/waypoint icons
#include "bitmaps/empty.xpm"
#include "bitmaps/airplane.xpm"
#include "bitmaps/anchorage.xpm"
#include "bitmaps/anchor.xpm"
#include "bitmaps/boarding.xpm"
#include "bitmaps/boundary.xpm"
#include "bitmaps/bouy1.xpm"
#include "bitmaps/bouy2.xpm"
#include "bitmaps/campfire.xpm"
#include "bitmaps/camping.xpm"
#include "bitmaps/circle.xpm"
#include "bitmaps/coral.xpm"
#include "bitmaps/fishhaven.xpm"
#include "bitmaps/fishing.xpm"
#include "bitmaps/fish.xpm"
#include "bitmaps/float.xpm"
#include "bitmaps/food.xpm"
#include "bitmaps/fuel.xpm"
#include "bitmaps/greenlite.xpm"
#include "bitmaps/kelp.xpm"
#include "bitmaps/light1.xpm"
#include "bitmaps/light.xpm"
#include "bitmaps/litevessel.xpm"
#include "bitmaps/mob.xpm"
#include "bitmaps/mooring.xpm"
#include "bitmaps/oilbouy.xpm"
#include "bitmaps/platform.xpm"
#include "bitmaps/redgreenlite.xpm"
#include "bitmaps/redlite.xpm"
#include "bitmaps/rock1.xpm"
#include "bitmaps/rock2.xpm"
#include "bitmaps/sand.xpm"
#include "bitmaps/scuba.xpm"
#include "bitmaps/shoal.xpm"
#include "bitmaps/snag.xpm"
#include "bitmaps/square.xpm"
#include "bitmaps/triangle.xpm"
#include "bitmaps/wreck1.xpm"
#include "bitmaps/wreck2.xpm"
#include "bitmaps/xmblue.xpm"
#include "bitmaps/xmgreen.xpm"
#include "bitmaps/xmred.xpm"
#include "bitmaps/diamond.xpm"

extern "C" float DistGreatCircle(double slat, double slon, double dlat, double dlon);


extern ChartBase        *Current_Ch;
extern ChartCanvas      *cc1;
extern ConsoleCanvas    *console;

extern RouteList        *pRouteList;
extern Select           *pSelect;
extern MyConfig         *pConfig;
extern NMEA0183         *pNMEA0183;
extern AutoPilotWindow  *pAPilot;
extern WayPointman      *pWayPointMan;
extern wxRect           g_blink_rect;

extern float            gLat, gLon, gSog, gCog;
extern bool             bAutoPilotOut;

#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */
#endif


//    List definitions for Waypoint Manager Icons
WX_DECLARE_LIST(wxBitmap, markicon_bitmap_list_type);
WX_DECLARE_LIST(wxString, markicon_key_list_type);
WX_DECLARE_LIST(wxString, markicon_description_list_type);


//    List implementation for Waypoint Manager Icons
#include <wx/listimpl.cpp>
WX_DEFINE_LIST(markicon_bitmap_list_type);
WX_DEFINE_LIST(markicon_key_list_type);
WX_DEFINE_LIST(markicon_description_list_type);


CPL_CVSID("$Id: routeman.cpp,v 1.6 2008/03/30 22:11:41 bdbcat Exp $");

//--------------------------------------------------------------------------------
//      Routeman   "Route Manager"
//--------------------------------------------------------------------------------

Routeman::Routeman()
{
        pActiveRoute = NULL;
        pActivePoint = NULL;
        pRouteActivatePoint = NULL;
}

Routeman::~Routeman()
{
        if( pRouteActivatePoint)
                delete  pRouteActivatePoint;
}

//    Make a 2-D search to find the route containing a given waypoint
Route *Routeman::FindRouteContainingWaypoint(RoutePoint *pWP)
{
      wxRouteListNode *node = pRouteList->GetFirst();
      while(node)
      {
            Route *proute = node->GetData();

            wxRoutePointListNode *pnode = (proute->pRoutePointList)->GetFirst();
            while(pnode)
            {
                  RoutePoint *prp = pnode->GetData();
                  if(prp == pWP)                // success
                        return proute;

                  pnode = pnode->GetNext();
            }

            node = node->GetNext();
      }

      return NULL;                              // not found
}


bool Routeman::ActivateRoute(Route *pActivate)
{
        pActiveRoute = pActivate;

        wxRoutePointListNode *node = (pActiveRoute->pRoutePointList)->GetFirst();

        pActivePoint = node->GetData();               // start at beginning

        ActivateRoutePoint(pActivate, pActivePoint);
        /*
        pActiveRoute->m_pRouteActivePoint = pActivePoint;
        pActivePoint->m_bBlink = true;

//      Calculate initial course to first route point

        pRouteActivatePoint = new RoutePoint(gLat, gLon, wxString(_T("")), wxString(_T("")), NULL);       // Current location
        pRouteActivatePoint->m_bShowName = false;

        pActiveRouteSegmentBeginPoint = pRouteActivatePoint;
        */

        m_bArrival = false;

        pActivate->m_bRtIsActive = true;

        m_bDataValid = false;

        console->ShowWithFreshFonts();
        return true;
}

bool Routeman::ActivateRoutePoint(Route *pA, RoutePoint *pRP_target)
{
        pActiveRoute = pA;
        pActivePoint = pRP_target;
        pActiveRoute->m_pRouteActivePoint = pRP_target;

        wxRoutePointListNode *node = (pActiveRoute->pRoutePointList)->GetFirst();
        while(node)
        {
              RoutePoint *pn = node->GetData();
              pn->m_bBlink = false;                     // turn off all blinking points
              node = node->GetNext();
        }

        node = (pActiveRoute->pRoutePointList)->GetFirst();
        RoutePoint *prp_first = node->GetData();

        //  If activating first point in route, create a "virtual" waypoint at present position
        if(pRP_target == prp_first)
        {
                if(pRouteActivatePoint)
                        delete pRouteActivatePoint;

                pRouteActivatePoint = new RoutePoint(gLat, gLon, wxString(_T("")), wxString(_T("")), NULL); // Current location
                pRouteActivatePoint->m_bShowName = false;

                pActiveRouteSegmentBeginPoint = pRouteActivatePoint;
        }

        else
        {
              prp_first->m_bBlink = false;
              node = node->GetNext();
              RoutePoint *np_prev = prp_first;
              while(node)
              {
                  RoutePoint *pnext = node->GetData();
                  if(pnext == pRP_target)
                  {
                          pActiveRouteSegmentBeginPoint = np_prev;
                          break;
                  }

                  np_prev = pnext;
                  node = node->GetNext();
            }
        }

        pRP_target->m_bBlink = true;                               // blink the active point
        g_blink_rect = pRP_target->CurrentRect_in_DC;               // set up global blinker

        m_bArrival = false;
        return true;
}

bool Routeman::ActivateNextPoint(Route *pr)
{
      if(pActivePoint)
            pActivePoint->m_bBlink = false;

      int n_index_active = pActiveRoute->GetIndexOf(pActivePoint);
      if((n_index_active + 1) <= pActiveRoute->GetnPoints())
      {
          pActiveRouteSegmentBeginPoint = pActivePoint;

          pActiveRoute->m_pRouteActivePoint = pActiveRoute->GetPoint(n_index_active + 1);

          pActivePoint = pActiveRoute->GetPoint(n_index_active + 1);

          pActivePoint->m_bBlink = true;
          g_blink_rect = pActivePoint->CurrentRect_in_DC;               // set up global blinker

          m_bArrival = false;

          return true;
      }

      return false;
}




bool Routeman::UpdateProgress()
{
    bool bret_val = false;

        if(pActiveRoute)
        {
//      Update bearing, range, and crosstrack error
                double north, east;
                toSM(pActivePoint->m_lat, pActivePoint->m_lon, gLat, gLon, &east, &north);
                double a = atan(north / east);
                if(pActivePoint->m_lon > gLon)
                    CurrentBrgToActivePoint = 90. - (a * 180/PI);
                else
                    CurrentBrgToActivePoint = 270. - (a * 180/PI);

//      Calculate Range using SM coordinates

//      Or, Calculate using Great Circle Formula

                float d5 = DistGreatCircle(gLat, gLon, pActivePoint->m_lat, pActivePoint->m_lon );
                CurrentRngToActivePoint = d5;

//      Get the XTE vector, normal to current segment
                VECTOR2D va, vb, vn;

                vb.x = pActivePoint->m_lon - pActiveRouteSegmentBeginPoint->m_lon;
                vb.y = pActivePoint->m_lat - pActiveRouteSegmentBeginPoint->m_lat;
                va.x = pActivePoint->m_lon - gLon;
                va.y = pActivePoint->m_lat - gLat;

                double delta = vGetLengthOfNormal(&va, &vb, &vn);
                CurrentXTEToActivePoint = delta * 60.;

//    Calculate the distance to the arrival line, which is perpendicular to the current route segment
//    Taking advantage of the calculated normal from current position to route segment vn
                VECTOR2D vToArriveNormal;
                vSubtractVectors(&va, &vn, &vToArriveNormal);


//                CurrentRangeToActiveNormalCrossing = vVectorMagnitude(&vToArriveNormal) * 60;

                float d6 = DistGreatCircle(gLat, gLon,
                                           gLat + vToArriveNormal.y, gLon + vToArriveNormal.x );
                CurrentRangeToActiveNormalCrossing = d6;


//      Compute XTE direction

                double e = atan((pActivePoint->m_lat - pActiveRouteSegmentBeginPoint->m_lat) /
                        (pActivePoint->m_lon - pActiveRouteSegmentBeginPoint->m_lon));
                if(pActivePoint->m_lon > pActiveRouteSegmentBeginPoint->m_lon)
                        CurrentSegmentCourse = 90. - (e * 180/PI);
                else
                        CurrentSegmentCourse = 270. - (e * 180/PI);

                double h = atan(vn.y / vn.x);
                if(vn.x > 0)
                        CourseToRouteSegment = 90. - (h * 180/PI);
                else
                        CourseToRouteSegment = 270. - (h * 180/PI);

                h= CurrentBrgToActivePoint - CourseToRouteSegment;
                if(h < 0 )
                        h = h + 360;

                if(h > 180)
                        XTEDir = 1;
                else
                        XTEDir = -1;



//      Determine Arrival
                float ArrivalRadius = .05;

                bool bDidArrival = false;

//                if(CurrentRngToActivePoint <= ArrivalRadius)
                if(CurrentRangeToActiveNormalCrossing <= ArrivalRadius)
                {
                  m_bArrival = true;
                  UpdateAutopilot();

                  bDidArrival = true;

                  if(!ActivateNextPoint(pActiveRoute))            // at the end?
                          DeactivateRoute();

//                  cc1->m_bForceReDraw = true;                     // cause a redraw if any RoutePoint changes
                }

                if(!bDidArrival)                                        // Only once on arrival
                        UpdateAutopilot();

                bret_val = true;                                        // a route is active
        }

        m_bDataValid = true;

        return bret_val;
}

bool Routeman::DeactivateRoute()
{
      if(pActivePoint)
            pActivePoint->m_bBlink = false;

      if(pActiveRoute)
      {
          pActiveRoute->m_bRtIsActive = false;
          pActiveRoute->m_pRouteActivePoint = NULL;
      }
      pActiveRoute = NULL;

      if(pRouteActivatePoint)
          delete  pRouteActivatePoint;
      pRouteActivatePoint = NULL;

      console->pCDI->ClearBackground();

      console->Show(false);

      m_bDataValid = false;

      return true;
}

bool Routeman::UpdateAutopilot()
{
        wxString str_buf;

        if(bAutoPilotOut)
        {
                SENTENCE snt;
                pNMEA0183->Rmb.IsDataValid = NTrue;
                pNMEA0183->Rmb.CrossTrackError = CurrentXTEToActivePoint;

                if(XTEDir < 0)
                        pNMEA0183->Rmb.DirectionToSteer = Left;
                else
                        pNMEA0183->Rmb.DirectionToSteer = Right;


                str_buf.Printf(_T("%03d"), pActiveRoute->GetIndexOf(pActiveRouteSegmentBeginPoint));
                wxString from = str_buf;
                pNMEA0183->Rmb.From = from;

                str_buf.Printf(_T("%03d"), pActiveRoute->GetIndexOf(pActivePoint));
                wxString to = str_buf;
                pNMEA0183->Rmb.To = to;

                pNMEA0183->Rmb.DestinationPosition.Latitude.Latitude = pActivePoint->m_lat;
                pNMEA0183->Rmb.DestinationPosition.Latitude.Northing = North;

                pNMEA0183->Rmb.DestinationPosition.Longitude.Longitude = fabs(pActivePoint->m_lon);
                pNMEA0183->Rmb.DestinationPosition.Longitude.Easting = West;


                pNMEA0183->Rmb.RangeToDestinationNauticalMiles = CurrentRngToActivePoint;
                pNMEA0183->Rmb.BearingToDestinationDegreesTrue = CurrentBrgToActivePoint;
                pNMEA0183->Rmb.DestinationClosingVelocityKnots = gSog;

                if(m_bArrival)
                        pNMEA0183->Rmb.IsArrivalCircleEntered = NTrue;
                else
                        pNMEA0183->Rmb.IsArrivalCircleEntered = NFalse;

                pNMEA0183->Rmb.Write(snt);

        //      stats->pTStat2->TextDraw(( const char *)snt.Sentence);

                pAPilot->AutopilotOut(snt.Sentence);
                }

        return true;
}

void Routeman::DeleteRoute(Route *pRoute)
{
      // walk the route, deleting points used only by this route
      wxRoutePointListNode *pnode = (pRoute->pRoutePointList)->GetFirst();
      while(pnode)
      {
            RoutePoint *prp = pnode->GetData();
            if(prp->m_bDynamicName)                // Mark is a "route only" type
            {
                  pConfig->DeleteWayPoint(prp);
                  pSelect->DeleteSelectablePoint(prp, SELTYPE_ROUTEPOINT);
                  delete prp;
            }
            else
                  prp->m_bIsInRoute = false;          // Take this point out of route

            pnode = pnode->GetNext();
      }

      pSelect->DeleteAllSelectableRouteSegments(pRoute);
      pRouteList->DeleteObject(pRoute);
      delete pRoute;
}

void Routeman::AssembleAllRoutes(void)
{
      //    Iterate on the RouteList
      wxRouteListNode *node = pRouteList->GetFirst();
      while(node)
      {
            Route *proute = node->GetData();

            proute->AssembleRoute();
            pSelect->AddAllSelectableRouteSegments(proute);

 /*
            //    And the RoutePointGUIDs
            for(unsigned int ip = 0 ; ip < proute->RoutePointGUIDList.GetCount() ; ip++)
            {
                  wxString GUID = proute->RoutePointGUIDList[ip];

                  //    And on the RoutePoints themselves
                  double prev_rlat;
                  double prev_rlon;
                  RoutePoint *prev_pRoutePoint;

                  wxRoutePointListNode *prpnode = pWayPointMan->m_pWayPointList->GetFirst();
                  while(prpnode)
                  {
                        RoutePoint *pr = prpnode->GetData();

                        if(pr->m_GUID == GUID)
                        {
                              proute->AddPoint(pr);
                              if(ip)
                                    pSelect->AddSelectableRouteSegment(prev_rlat, prev_rlon, pr->m_lat, pr->m_lon,
                                          prev_pRoutePoint, pr);

                              prev_rlat = pr->m_lat;
                              prev_rlon = pr->m_lon;
                              prev_pRoutePoint = pr;
                              break;
                        }
                        prpnode = prpnode->GetNext(); //RoutePoint
                  }
            }
 */
            node = node->GetNext();                   // Route
      }
}


//--------------------------------------------------------------------------------
//      WayPointman   Implementation
//--------------------------------------------------------------------------------

//    This macro (with apologies) creates the two hashmaps for manipulating mark icons by key name.
//    Allows the assignemnt of static XPM images and desciptive strings to specific wxString keys.

#define MAKEHASH(key, xpm_ptr, description)        markicon_xpm_hash[_T(key)]  =      (char *)  xpm_ptr;\
                                                   markicon_description_hash[_T(key)] = new wxString(_T(description));


//    This macro makes the three lists needed for manipulating icons by name.
//    We use wxLists becuase we like to guarantee the order of items in the list
//    for display purposes, and this is not possible with wxHashmap.

#define MAKEICONLISSTS(key, xpm_ptr, description)     pmarkiconBitmap = new wxBitmap((char **)xpm_ptr);\
                                                   pmarkicon_image_list->Add(*pmarkiconBitmap);\
                                                   pmarkicon_bitmap_list->Append(pmarkiconBitmap);\
                                                   pmarkicon_description_list->Append(new wxString(_T(description)));\
                                                   pmarkicon_key_list->Append(new wxString(_T(key)));



WayPointman::WayPointman()
{
      m_pWayPointList = new RoutePointList;


      //    Get the icon image size
      wxBitmap BitmapTest((char **)airplane);
      int bitmap_sizex = BitmapTest.GetWidth();
      int bitmap_sizey = BitmapTest.GetHeight();
      pmarkicon_image_list = new wxImageList(bitmap_sizex, bitmap_sizey);

      pmarkicon_description_list    = new markicon_description_list_type;
      pmarkicon_bitmap_list         = new markicon_bitmap_list_type;
      pmarkicon_key_list            = new markicon_key_list_type;

      wxBitmap *pmarkiconBitmap;

      MAKEICONLISSTS("empty", empty, "Empty")
      MAKEICONLISSTS("airplane", airplane, "Airplane")
      MAKEICONLISSTS("anchorage", anchorage, "Anchorage")
      MAKEICONLISSTS("anchor", anchor, "Anchor")
      MAKEICONLISSTS("boarding", boarding, "Boarding Location")
      MAKEICONLISSTS("boundary", boundary, "Boundary Mark")
      MAKEICONLISSTS("bouy1", bouy1, "Bouy Type A")
      MAKEICONLISSTS("bouy2", bouy2, "Bouy Type B")
      MAKEICONLISSTS("campfire", campfire, "Campfire")
      MAKEICONLISSTS("camping", camping, "Camping Spot")
      MAKEICONLISSTS("coral", coral, "Coral")
      MAKEICONLISSTS("fishhaven", fishhaven, "Fish Haven")
      MAKEICONLISSTS("fishing", fishing, "Fishing Spot")
      MAKEICONLISSTS("fish", fish, "Fish")
      MAKEICONLISSTS("floating", floating, "Float")
      MAKEICONLISSTS("food", food, "Food")
      MAKEICONLISSTS("fuel", fuel, "Fuel")
      MAKEICONLISSTS("greenlite", greenlite, "Green Light")
      MAKEICONLISSTS("kelp", kelp, "Kelp")
      MAKEICONLISSTS("light1", light1, "Light Type A")
      MAKEICONLISSTS("light", light, "Light Type B")
      MAKEICONLISSTS("litevessel", litevessel, "Light Vessel")
      MAKEICONLISSTS("mob", mob, "MOB")
      MAKEICONLISSTS("mooring", mooring, "Mooring Bouy")
      MAKEICONLISSTS("oilbouy", oilbouy, "Oil Bouy")
      MAKEICONLISSTS("platform", platform, "Platform")
      MAKEICONLISSTS("redgreenlite", redgreenlite, "Red/Green Light")
      MAKEICONLISSTS("redlite", redlite, "Red Light")
      MAKEICONLISSTS("rock1", rock1, "Rock (exposed)")
      MAKEICONLISSTS("rock2", rock2, "Rock, (awash)")
      MAKEICONLISSTS("sand", sand, "Sand")
      MAKEICONLISSTS("scuba", scuba, "Scuba")
      MAKEICONLISSTS("shoal", shoal, "Shoal")
      MAKEICONLISSTS("snag", snag, "Snag")
      MAKEICONLISSTS("square", square, "Square")
      MAKEICONLISSTS("triangle", triangle, "Triangle")
      MAKEICONLISSTS("diamond", diamond, "Diamond")
      MAKEICONLISSTS("circle", circle, "Circle")
      MAKEICONLISSTS("wreck1", wreck1, "Wreck A")
      MAKEICONLISSTS("wreck2", wreck2, "Wreck B")
      MAKEICONLISSTS("xmblue", xmblue, "Blue X")
      MAKEICONLISSTS("xmgreen", xmgreen, "Green X")
      MAKEICONLISSTS("xmred", xmred, "Red X")

      m_nIcons = pmarkicon_key_list->GetCount();

/*
// Load up all the icon xpm data pointers into a hash map
      markicon_xpm_hash.clear();


      MAKEHASH("airplane", airplane, "Airplane")


//      markicon_xpm_hash[_T("airplane")]  =      (char *)  airplane;
      MAKEHASH("anchorage", anchorage, "Anchorage")
      MAKEHASH("anchor", anchor, "")
      MAKEHASH("boarding", boarding, "Boarding Location")
      MAKEHASH("boundary", boundary, "Boundary Mark")
      MAKEHASH("bouy1", bouy1, "Bouy Type A")
      MAKEHASH("bouy2", bouy2, "Bouy Type B")
      MAKEHASH("campfire", campfire, "Campfire")
      MAKEHASH("camping", camping, "Camping Spot")
      MAKEHASH("circle", circle, "Circle")
      MAKEHASH("coral", coral, "Coral")
      MAKEHASH("fishhaven", fishhaven, "Fish Haven")
      MAKEHASH("fishing", fishing, "Fishing Spot")
      MAKEHASH("fish", fish, "Fish")
      MAKEHASH("floating", floating, "Float")
      MAKEHASH("food", food, "Food")
      MAKEHASH("fuel", fuel, "Fuel")
      MAKEHASH("greenlite", greenlite, "Green Light")
      MAKEHASH("kelp", kelp, "Kelp")
      MAKEHASH("light1", light1, "Light Type A")
      MAKEHASH("light", light, "Light Type B")
      MAKEHASH("litevessel", litevessel, "Light Vessel")
      MAKEHASH("mob", mob, "MOB")
      MAKEHASH("mooring", mooring, "Mooring Bouy")
      MAKEHASH("oilbouy", oilbouy, "Oil Bouy")
      MAKEHASH("platform", platform, "Platform")
      MAKEHASH("redgreenlite", redgreenlite, "Red/Green Light")
      MAKEHASH("redlite", redlite, "Red Light")
      MAKEHASH("rock1", rock1, "Rock (exposed)")
      MAKEHASH("rock2", rock2, "Rock, (awash)")
      MAKEHASH("sand", sand, "Sand")
      MAKEHASH("scuba", scuba, "Scuba")
      MAKEHASH("shoal", shoal, "Shoal")
      MAKEHASH("snag", snag, "Snag")
      MAKEHASH("square", square, "")
      MAKEHASH("triangle", triangle, "Triangle")
      MAKEHASH("wreck1", wreck1, "Wreck A")
      MAKEHASH("wreck2", wreck2, "Wreck B")
      MAKEHASH("xmblue", xmblue, "Blue X")
      MAKEHASH("xmgreen", xmgreen, "Green X")
      MAKEHASH("xmred", xmred, "Red X")


      //    Create one default icon bitmap
      //    Deferring creation of others until needed by GetIconBitmap()

      wxString default_icon(_T("square"));
      char **px1 = (char **)markicon_xpm_hash[default_icon];          // default

      wxBitmap *pmarkiconBitmap = new wxBitmap(px1);
      // store it
      markicon_bitmap_hash[default_icon] = pmarkiconBitmap;
*/

}

WayPointman::~WayPointman()
{

      //    Two step here, since the RoutePoint dtor also touches the
      //    RoutePoint list.
      //    Copy the master RoutePoint list to a temporary list,
      //    then clear and delete objects from the temp list

      RoutePointList    temp_list;

      wxRoutePointListNode *node = m_pWayPointList->GetFirst();
      while(node)
      {
            RoutePoint *pr = node->GetData();

            temp_list.Append(pr);
            node = node->GetNext();
      }

      temp_list.DeleteContents(true);
      temp_list.Clear();


      m_pWayPointList->Clear();
      delete m_pWayPointList;

      pmarkicon_description_list->DeleteContents(true);
      pmarkicon_bitmap_list->DeleteContents(true);
      pmarkicon_key_list->DeleteContents(true);

      delete pmarkicon_description_list;
      delete pmarkicon_bitmap_list;
      delete pmarkicon_key_list;
      delete pmarkicon_image_list;

/*
    //      Delete the created mark icon bitmaps
    string_to_pchar_hash::iterator it;
    for( it = markicon_xpm_hash.begin(); it != markicon_xpm_hash.end(); ++it )
    {

        wxString index = it->first;
        delete markicon_bitmap_hash[index];
    }
*/

}


wxBitmap *WayPointman::GetIconBitmap(const wxString& icon_key)
{
      wxBitmap *pret = NULL;
      int index = -1;

//    Get the common list index by brute search
      markicon_key_list_type::Node *node = pmarkicon_key_list->GetFirst();
      while(node)
      {
            wxString *ps = node->GetData();

            if(ps->IsSameAs(icon_key))
            {
                  index = pmarkicon_key_list->IndexOf(ps);
                  break;
            }
            node = node->GetNext();
      }

      if(index == -1)               // key was not found, use empty (transparent)Icon at index 0
            index = 0;

      if(index >= 0)
      {
            markicon_bitmap_list_type::Node *bitmap_node = pmarkicon_bitmap_list->Item(index);
            pret = bitmap_node->GetData();
      }

    /* hashmap
      wxBitmap *pret = markicon_bitmap_hash[icon_key];

      if(NULL == pret)                          // has not been made yet
      {
        char **px1 = (char **)markicon_xpm_hash[icon_key];
        if(NULL != px1)
        {
            wxBitmap *pmarkiconBitmap = new wxBitmap(px1);
            markicon_bitmap_hash[icon_key] = pmarkiconBitmap;
            pret = pmarkiconBitmap;
        }
        else
          pret = markicon_bitmap_hash[_T("square")];  // default
      }

  */

      return pret;
}

wxBitmap *WayPointman::GetIconBitmap(int index)
{
      wxBitmap *pret = NULL;

      if(index >= 0)
      {
            markicon_bitmap_list_type::Node *bnode = pmarkicon_bitmap_list->Item(index);
            pret = bnode->GetData();
      }

      return pret;
}


wxString *WayPointman::GetIconDescription(int index)
{
      wxString *pret = NULL;

      if(index >= 0)
      {
            markicon_description_list_type::Node *dnode = pmarkicon_description_list->Item(index);
            pret = dnode->GetData();
      }

      return pret;
}

wxString *WayPointman::GetIconKey(int index)
{
      wxString *pret = NULL;

      if(index >= 0)
      {
            markicon_key_list_type::Node *knode = pmarkicon_key_list->Item(index);
            pret = knode->GetData();
      }

      return pret;
}

int WayPointman::GetIconIndex(const wxBitmap *pbm)
{
//    Get the common list index by brute search
      int index = -1;
      markicon_bitmap_list_type::Node *node = pmarkicon_bitmap_list->GetFirst();
      while(node)
      {
            wxBitmap *pbmt = node->GetData();

            if(pbmt == pbm)
            {
                  index = pmarkicon_bitmap_list->IndexOf((wxBitmap *)pbm);
                  break;
            }
            node = node->GetNext();
      }

      return index;
}

     //  Create the unique identifier

wxString WayPointman::CreateGUID(RoutePoint *pRP)
{
      wxDateTime now = wxDateTime::Now();
      time_t ticks = now.GetTicks();
      wxString GUID;
      GUID.Printf(_T("%d-%d-%d"), ((int)fabs(pRP->m_lat * 1e4)), ((int)fabs(pRP->m_lon * 1e4)), (int)ticks);
      return GUID;
}

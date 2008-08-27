/******************************************************************************
 * $Id: routeman.cpp,v 1.8 2008/08/27 22:52:16 bdbcat Exp $
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
 * $Log: routeman.cpp,v $
 * Revision 1.8  2008/08/27 22:52:16  bdbcat
 * Fix wxImageList bug for  variable icon size
 *
 * Revision 1.7  2008/08/26 13:46:25  bdbcat
 * Better color scheme support
 *
 * Revision 1.6  2008/03/30 22:11:41  bdbcat
 * Add RoutePoint manager
 *
 * $Log: routeman.cpp,v $
 * Revision 1.8  2008/08/27 22:52:16  bdbcat
 * Fix wxImageList bug for  variable icon size
 *
 * Revision 1.7  2008/08/26 13:46:25  bdbcat
 * Better color scheme support
 *
 * Revision 1.6  2008/03/30 22:11:41  bdbcat
 * Add RoutePoint manager
 *
 * Revision 1.5  2008/01/12 06:20:56  bdbcat
 * Update for Mac OSX/Unicode
 *
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
#include "bitmaps/activepoint.xpm"

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


//    List definitions for Waypoint Manager Icons
WX_DECLARE_LIST(wxBitmap, markicon_bitmap_list_type);
WX_DECLARE_LIST(wxString, markicon_key_list_type);
WX_DECLARE_LIST(wxString, markicon_description_list_type);


//    List implementation for Waypoint Manager Icons
#include <wx/listimpl.cpp>
WX_DEFINE_LIST(markicon_bitmap_list_type);
WX_DEFINE_LIST(markicon_key_list_type);
WX_DEFINE_LIST(markicon_description_list_type);


CPL_CVSID("$Id: routeman.cpp,v 1.8 2008/08/27 22:52:16 bdbcat Exp $");

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
              pn->m_bIsActive = false;

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
        pRP_target->m_bIsActive = true;                            // and active

        g_blink_rect = pRP_target->CurrentRect_in_DC;               // set up global blinker

        m_bArrival = false;
        return true;
}

bool Routeman::ActivateNextPoint(Route *pr)
{
      if(pActivePoint)
      {
            pActivePoint->m_bBlink = false;
            pActivePoint->m_bIsActive = false;
      }

      int n_index_active = pActiveRoute->GetIndexOf(pActivePoint);
      if((n_index_active + 1) <= pActiveRoute->GetnPoints())
      {
          pActiveRouteSegmentBeginPoint = pActivePoint;

          pActiveRoute->m_pRouteActivePoint = pActiveRoute->GetPoint(n_index_active + 1);

          pActivePoint = pActiveRoute->GetPoint(n_index_active + 1);

          pActivePoint->m_bBlink = true;
          pActivePoint->m_bIsActive = true;
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


//      Calculate range using Great Circle Formula

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


//          Compute current segment course
//          Using simple Mercater projection
                double x1, y1, x2, y2;
                toSM(pActiveRouteSegmentBeginPoint->m_lat,  pActiveRouteSegmentBeginPoint->m_lon,
                     pActiveRouteSegmentBeginPoint->m_lat,  pActiveRouteSegmentBeginPoint->m_lon, &x1, &y1);

                toSM(pActivePoint->m_lat,  pActivePoint->m_lon,
                     pActiveRouteSegmentBeginPoint->m_lat,  pActiveRouteSegmentBeginPoint->m_lon, &x2, &y2);

                double e1 = atan2((x2 - x1), (y2-y1));
                CurrentSegmentCourse = e1 * 180/PI;
                if(CurrentSegmentCourse < 0)
                      CurrentSegmentCourse += 360;


 //      Compute XTE direction
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
      {
            pActivePoint->m_bBlink = false;
            pActivePoint->m_bIsActive = false;
      }


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

void Routeman::SetColorScheme(ColorScheme cs)
{
      // Re-Create the pens and colors
      m_pRoutePen =             wxThePenList->FindOrCreatePen(wxColour(0,0,255), 2, wxSOLID);
      m_pSelectedRoutePen =     wxThePenList->FindOrCreatePen(wxColour(255,0,0), 2, wxSOLID);
      m_pActiveRoutePen =       wxThePenList->FindOrCreatePen(wxColour(255,0,255), 2, wxSOLID);
      m_pActiveRoutePointPen =  wxThePenList->FindOrCreatePen(wxColour(0,0,255), 2, wxSOLID);
      m_pRoutePointPen =        wxThePenList->FindOrCreatePen(wxColour(0,0,255), 2, wxSOLID);

//    Or in something like S-52 compliance

      m_pRoutePen =             wxThePenList->FindOrCreatePen(GetGlobalColor(_T("UINFB")), 2, wxSOLID);
      m_pSelectedRoutePen =     wxThePenList->FindOrCreatePen(GetGlobalColor(_T("CHRED")), 2, wxSOLID);
      m_pActiveRoutePen =       wxThePenList->FindOrCreatePen(GetGlobalColor(_T("PLRTE")), 2, wxSOLID);
//      m_pActiveRoutePointPen =  wxThePenList->FindOrCreatePen(GetGlobalColor(_T("PLRTE")), 2, wxSOLID);
//      m_pRoutePointPen =        wxThePenList->FindOrCreatePen(GetGlobalColor(_T("CHBLK")), 2, wxSOLID);


            //    Iterate on the RouteList to reload Icons
/*
      wxRouteListNode *node = pRouteList->GetFirst();
      while(node)
      {
            Route *proute = node->GetData();
            proute->ReloadRoutePointIcons();
            node = node->GetNext();                   // Route
      }
*/
 }

//--------------------------------------------------------------------------------
//      WayPointman   Implementation
//--------------------------------------------------------------------------------





#define MAKEICONARRAYS(key, xpm_ptr, description)      pmarkiconImage = new wxImage((char **)xpm_ptr);\
                                                   pmarkiconBitmap = new wxBitmap(*pmarkiconImage);\
                                                   delete pmarkiconImage;\
                                                   pmi = new MarkIcon;\
                                                   pmi->picon_bitmap = pmarkiconBitmap;\
                                                   pmi->icon_name = _T(key);\
                                                   pmi->icon_description = _T(description);\
                                                   DayIconArray.Add((void *)pmi);\
                                                            pmarkiconImage = new wxImage((char **)xpm_ptr);\
                                                            pmarkiconBitmap = new wxBitmap(*pmarkiconImage);\
                                                            delete pmarkiconImage;\
                                                            pmarkiconBitmapDim = CreateDimBitmap(pmarkiconBitmap, .50);\
                                                            delete pmarkiconBitmap;\
                                                            pmi = new MarkIcon;\
                                                            pmi->picon_bitmap = pmarkiconBitmapDim;\
                                                            pmi->icon_name = _T(key);\
                                                            pmi->icon_description = _T(description);\
                                                            DuskIconArray.Add((void *)pmi);\
                                                                   pmarkiconImage = new wxImage((char **)xpm_ptr);\
                                                                   pmarkiconBitmap = new wxBitmap(*pmarkiconImage);\
                                                                   delete pmarkiconImage;\
                                                                   pmarkiconBitmapDim = CreateDimBitmap(pmarkiconBitmap, .25);\
                                                                   delete pmarkiconBitmap;\
                                                                   pmi = new MarkIcon;\
                                                                   pmi->picon_bitmap = pmarkiconBitmapDim;\
                                                                   pmi->icon_name = _T(key);\
                                                                   pmi->icon_description = _T(description);\
                                                                   NightIconArray.Add((void *)pmi);\


WayPointman::WayPointman()
{
      MarkIcon *pmi;

      m_pWayPointList = new RoutePointList;

      wxImage *pmarkiconImage;
      wxBitmap *pmarkiconBitmap;
      wxBitmap *pmarkiconBitmapDim;

/*
      pmarkiconImage = new wxImage((char **)airplane);
      if(pmarkiconImage->HasMask())
            int ddl = 4;
      pmarkiconBitmap = new wxBitmap(*pmarkiconImage);
      if(!pmarkiconBitmap->Ok())
            int ggl = 4;
      if(pmarkiconBitmap->GetDepth() == 1)
            int ggk = 5;
//      pmarkiconMask = new wxMask(*pmarkiconBitmap);
//      pmarkiconBitmap->SetMask(pmarkiconMask);

 */
















      MAKEICONARRAYS("empty", empty, "Empty")
      MAKEICONARRAYS("airplane", airplane, "Airplane")
      MAKEICONARRAYS("anchorage", anchorage, "Anchorage")
      MAKEICONARRAYS("anchor", anchor, "Anchor")
      MAKEICONARRAYS("boarding", boarding, "Boarding Location")
      MAKEICONARRAYS("boundary", boundary, "Boundary Mark")
      MAKEICONARRAYS("bouy1", bouy1, "Bouy Type A")
      MAKEICONARRAYS("bouy2", bouy2, "Bouy Type B")
      MAKEICONARRAYS("campfire", campfire, "Campfire")
      MAKEICONARRAYS("camping", camping, "Camping Spot")
      MAKEICONARRAYS("coral", coral, "Coral")
      MAKEICONARRAYS("fishhaven", fishhaven, "Fish Haven")
      MAKEICONARRAYS("fishing", fishing, "Fishing Spot")
      MAKEICONARRAYS("fish", fish, "Fish")
      MAKEICONARRAYS("floating", floating, "Float")
      MAKEICONARRAYS("food", food, "Food")
      MAKEICONARRAYS("fuel", fuel, "Fuel")
      MAKEICONARRAYS("greenlite", greenlite, "Green Light")
      MAKEICONARRAYS("kelp", kelp, "Kelp")
      MAKEICONARRAYS("light1", light1, "Light Type A")
      MAKEICONARRAYS("light", light, "Light Type B")
      MAKEICONARRAYS("litevessel", litevessel, "Light Vessel")
      MAKEICONARRAYS("mob", mob, "MOB")
      MAKEICONARRAYS("mooring", mooring, "Mooring Bouy")
      MAKEICONARRAYS("oilbouy", oilbouy, "Oil Bouy")
      MAKEICONARRAYS("platform", platform, "Platform")
      MAKEICONARRAYS("redgreenlite", redgreenlite, "Red/Green Light")
      MAKEICONARRAYS("redlite", redlite, "Red Light")
      MAKEICONARRAYS("rock1", rock1, "Rock (exposed)")
      MAKEICONARRAYS("rock2", rock2, "Rock, (awash)")
      MAKEICONARRAYS("sand", sand, "Sand")
      MAKEICONARRAYS("scuba", scuba, "Scuba")
      MAKEICONARRAYS("shoal", shoal, "Shoal")
      MAKEICONARRAYS("snag", snag, "Snag")
      MAKEICONARRAYS("square", square, "Square")
      MAKEICONARRAYS("triangle", triangle, "Triangle")
      MAKEICONARRAYS("diamond", diamond, "Diamond")
      MAKEICONARRAYS("circle", circle, "Circle")
      MAKEICONARRAYS("wreck1", wreck1, "Wreck A")
      MAKEICONARRAYS("wreck2", wreck2, "Wreck B")
      MAKEICONARRAYS("xmblue", xmblue, "Blue X")
      MAKEICONARRAYS("xmgreen", xmgreen, "Green X")
      MAKEICONARRAYS("xmred", xmred, "Red X")
      MAKEICONARRAYS("activepoint", activepoint, "Active WP")

      m_nIcons = DayIconArray.GetCount();
      m_pcurrent_icon_array = &DayIconArray;

      //    Create a default wxImageList
      // First find the largest bitmap size
      int w=0;
      int h=0;

      for( unsigned int i = 0 ; i< m_pcurrent_icon_array->GetCount() ; i++)
      {
            pmi = (MarkIcon *)m_pcurrent_icon_array->Item(i);
            w = wxMax(w, pmi->picon_bitmap->GetWidth());
            h = wxMax(h, pmi->picon_bitmap->GetHeight());
      }

      //Build an image list large enough
      pmarkicon_image_list = new wxImageList(w, h);

      //  Addd the icons
      for( unsigned int i = 0 ; i< m_pcurrent_icon_array->GetCount() ; i++)
      {
            pmi = (MarkIcon *)m_pcurrent_icon_array->Item(i);
            pmarkicon_image_list->Add(*pmi->picon_bitmap);
      }

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

      for( unsigned int i = 0 ; i< DayIconArray.GetCount() ; i++)
      {
            MarkIcon *pmi = (MarkIcon *)NightIconArray.Item(i);
            delete pmi->picon_bitmap;
            delete pmi;

            pmi = (MarkIcon *)DuskIconArray.Item(i);
            delete pmi->picon_bitmap;
            delete pmi;

            pmi = (MarkIcon *)DayIconArray.Item(i);
            delete pmi->picon_bitmap;
            delete pmi;
      }


      NightIconArray.Empty();
      DuskIconArray.Empty();
      DayIconArray.Empty();

      pmarkicon_image_list->RemoveAll();
      delete pmarkicon_image_list;
}

wxBitmap *WayPointman::CreateDimBitmap(wxBitmap *pBitmap, double factor)
{
      wxImage img = pBitmap->ConvertToImage();
      int sx = img.GetWidth();
      int sy = img.GetHeight();

      wxImage new_img(img);

      for(int i = 0 ; i < sx ; i++)
      {
            for(int j = 0 ; j < sy ; j++)
            {
                  if(!img.IsTransparent(i,j))
                  {
                        new_img.SetRGB(i, j, (unsigned char)(img.GetRed(i, j) * factor),
                                             (unsigned char)(img.GetGreen(i, j) * factor),
                                             (unsigned char)(img.GetBlue(i, j) * factor));
                  }
            }
      }

      wxBitmap *pret = new wxBitmap(new_img);

      return pret;

}

void WayPointman::SetColorScheme(ColorScheme cs)
{
      switch(cs)
      {
            case GLOBAL_COLOR_SCHEME_DAY:
                  m_pcurrent_icon_array = &DayIconArray;
                  break;
            case GLOBAL_COLOR_SCHEME_DUSK:
                  m_pcurrent_icon_array = &DuskIconArray;
                  break;
            case GLOBAL_COLOR_SCHEME_NIGHT:
                  m_pcurrent_icon_array = &NightIconArray;
                  break;
            default:
                  m_pcurrent_icon_array = &DayIconArray;
                  break;
      }

      //    Iterate on the RoutePoint list, requiring each to reload icon

      wxRoutePointListNode *node = m_pWayPointList->GetFirst();
      while(node)
      {
            RoutePoint *pr = node->GetData();
            pr->ReLoadIcon();
            node = node->GetNext();
      }


      //    Remake the wxImageList
      pmarkicon_image_list->RemoveAll();
      for( unsigned int i = 0 ; i< m_pcurrent_icon_array->GetCount() ; i++)
      {
            MarkIcon *pmi = (MarkIcon *)m_pcurrent_icon_array->Item(i);
            pmarkicon_image_list->Add(*pmi->picon_bitmap);
      }

}


wxBitmap *WayPointman::GetIconBitmap(const wxString& icon_key)
{
      wxBitmap *pret = NULL;
      MarkIcon *pmi;
      unsigned int i;

      for( i = 0 ; i< m_pcurrent_icon_array->GetCount() ; i++)
      {
            pmi = (MarkIcon *)m_pcurrent_icon_array->Item(i);
            if(pmi->icon_name.IsSameAs(icon_key))
                  break;
      }

      if(i == m_pcurrent_icon_array->GetCount())              // not found
            pmi = (MarkIcon *)m_pcurrent_icon_array->Item(0);       // use item 0



      pret = pmi->picon_bitmap;


      return pret;
}

wxBitmap *WayPointman::GetIconBitmap(int index)
{
      wxBitmap *pret = NULL;

      if(index >= 0)
      {
            MarkIcon *pmi = (MarkIcon *)m_pcurrent_icon_array->Item(index);
            pret = pmi->picon_bitmap;
      }
      return pret;
}


wxString *WayPointman::GetIconDescription(int index)
{
      wxString *pret = NULL;

      if(index >= 0)
      {
            MarkIcon *pmi = (MarkIcon *)m_pcurrent_icon_array->Item(index);
            pret = &pmi->icon_description;
      }
      return pret;
}

wxString *WayPointman::GetIconKey(int index)
{
      wxString *pret = NULL;

      if(index >= 0)
      {
            MarkIcon *pmi = (MarkIcon *)m_pcurrent_icon_array->Item(index);
            pret = &pmi->icon_name;
      }
      return pret;
}

int WayPointman::GetIconIndex(const wxBitmap *pbm)
{
      unsigned int i;

      for( i = 0 ; i< m_pcurrent_icon_array->GetCount() ; i++)
      {
            MarkIcon *pmi = (MarkIcon *)m_pcurrent_icon_array->Item(i);
            if(pmi->picon_bitmap == pbm)
                  break;
      }

      return i;

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


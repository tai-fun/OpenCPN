/******************************************************************************
 * $Id: routeman.cpp,v 1.5 2008/01/12 06:20:56 bdbcat Exp $
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

static float DistGreatCircle(double slat, double slon, double dlat, double dlon);


extern ChartBase        *Current_Ch;
extern ChartCanvas      *cc1;
extern ConsoleCanvas    *console;

extern RouteList        *pRouteList;
extern Select           *pSelect;
extern MyConfig         *pConfig;
extern NMEA0183         *pNMEA0183;
extern AutoPilotWindow  *pAPilot;

extern float            gLat, gLon, gSog, gCog;
extern bool             bAutoPilotOut;

#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */
#endif

CPL_CVSID("$Id: routeman.cpp,v 1.5 2008/01/12 06:20:56 bdbcat Exp $");

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


bool Routeman::ActivateRoute(Route *pActivate)
{
        pActiveRoute = pActivate;

        wxRoutePointListNode *node = (pActiveRoute->pRoutePointList)->GetFirst();

        pActivePoint = node->GetData();               // start at beginning
        pActiveRoute->m_nRouteActivePoint = 1;

//      Calculate initial course to first route point

        pRouteActivatePoint = new RoutePoint();       // Current location
        pRouteActivatePoint->rlat = gLat;
        pRouteActivatePoint->rlon = gLon;
        pRouteActivatePoint->nPoint = 0;              // virtual point

        pActiveRouteSegmentBeginPoint = pRouteActivatePoint;

        m_bArrival = false;

        pActivate->m_bRtIsActive = true;

        m_bDataValid = false;

        console->ShowWithFreshFonts();
        return true;
}

bool Routeman::ActivateRoutePoint(Route *pA, RoutePoint *pRP)
{
        pActiveRoute = pA;
        pActivePoint = pRP;
        pActiveRoute->m_nRouteActivePoint = pRP->nPoint;

        wxRoutePointListNode *node = (pActiveRoute->pRoutePointList)->GetFirst();

        if(pRP->nPoint == 1)
        {
                if(pRouteActivatePoint)
                        delete pRouteActivatePoint;

                pRouteActivatePoint = new RoutePoint();                         // Current location
                pRouteActivatePoint->rlat = gLat;
                pRouteActivatePoint->rlon = gLon;
                pRouteActivatePoint->nPoint = 0;

                pActiveRouteSegmentBeginPoint = pRouteActivatePoint;
        }

        else
        {
                while(node)
                {
                        RoutePoint *np = node->GetData();
                        if(np->nPoint == pRP->nPoint - 1)
                        {
                                pActiveRouteSegmentBeginPoint = np;
                                break;
                        }

                        node = node->GetNext();
                }
        }
        m_bArrival = false;
        return true;
}

bool Routeman::ActivateNextPoint(Route *pr)
{
        float f,g;

        if((pActiveRoute->m_nRouteActivePoint + 1) <= pActiveRoute->m_nPoints)
        {
                pActiveRouteSegmentBeginPoint = pActivePoint;

                pActiveRoute->m_nRouteActivePoint += 1;

                pActivePoint = pActiveRoute->GetPoint(pActiveRoute->m_nRouteActivePoint,
                                                                                          &f, &g);
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
                toSM(pActivePoint->rlat, pActivePoint->rlon, gLat, gLon, &east, &north);
                double a = atan(north / east);
                if(pActivePoint->rlon > gLon)
                    CurrentBrgToActivePoint = 90. - (a * 180/PI);
                else
                    CurrentBrgToActivePoint = 270. - (a * 180/PI);

//      Calculate Range using SM coordinates

//      Or, Calculate using Great Circle Formula

                float d5 = DistGreatCircle(gLat, gLon, pActivePoint->rlat, pActivePoint->rlon );
                CurrentRngToActivePoint = d5;

//      Get the XTE vector, normal to current segment
                VECTOR2D va, vb, vn;

                vb.x = pActivePoint->rlon - pActiveRouteSegmentBeginPoint->rlon;
                vb.y = pActivePoint->rlat - pActiveRouteSegmentBeginPoint->rlat;
                va.x = pActivePoint->rlon - gLon;
                va.y = pActivePoint->rlat - gLat;

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

                double e = atan((pActivePoint->rlat - pActiveRouteSegmentBeginPoint->rlat) /
                        (pActivePoint->rlon - pActiveRouteSegmentBeginPoint->rlon));
                if(pActivePoint->rlon > pActiveRouteSegmentBeginPoint->rlon)
                        CurrentSegmentCourse = 90. - (e * 180/PI);
                else
                        CurrentSegmentCourse = 270. - (e * 180/PI);

                double h = atan(vn.y / vn.x);
                if(vn.x > 0)
                        CourseToRouteSegment = 90. - (h * 180/PI);
                else
                        CourseToRouteSegment = 270. - (h * 180/PI);

                float f, g;

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

                        if((pActiveRoute->m_nRouteActivePoint + 1) <= pActiveRoute->m_nPoints)
                        {
                                pActiveRouteSegmentBeginPoint = pActivePoint;

                                pActiveRoute->m_nRouteActivePoint += 1;

                                pActivePoint = pActiveRoute->GetPoint(pActiveRoute->m_nRouteActivePoint,
                                                                                                      &f, &g);
                                m_bArrival = false;
                        }
                        else
                                DeactivateRoute();

                        cc1->m_bForceReDraw = true;                     // cause a redraw if any RoutePoint changes

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
        if(pActiveRoute)
        {
                pActiveRoute->m_bRtIsActive = false;
                pActiveRoute->m_nRouteActivePoint = 0;
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


                str_buf.Printf(_T("%03d"), pActiveRouteSegmentBeginPoint->nPoint);
                wxString from = str_buf;
                pNMEA0183->Rmb.From = from;

                str_buf.Printf(_T("%03d"), pActivePoint->nPoint);
                wxString to = str_buf;
                pNMEA0183->Rmb.To = to;

                pNMEA0183->Rmb.DestinationPosition.Latitude.Latitude = pActivePoint->rlat;
                pNMEA0183->Rmb.DestinationPosition.Latitude.Northing = North;

                pNMEA0183->Rmb.DestinationPosition.Longitude.Longitude = fabs(pActivePoint->rlon);
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

static float DistGreatCircle(double slat, double slon, double dlat, double dlon)
{
//    Calculate distance using Great Circle Formula
//  d=2*asin(sqrt((sin((lat1-lat2)/2))^2 +
//                 cos(lat1)*cos(lat2)*(sin((lon1-lon2)/2))^2))
//  distance_nm=((180*60)/pi)*distance_radians

      double lon1 = dlon * PI / 180.;
      double lon2 = slon * PI / 180.;
      double lat1 = dlat * PI / 180.;
      double lat2 = slat * PI / 180.;

      double v = sin((lon1 - lon2)/2.0);
      double w = cos(lat1) * cos(lat2) * v * v;
      double x = sin((lat1 - lat2)/2.0);
      double d4 = 2.0 * asin(sqrt(x*x + w));

      float d5 = (180. * 60. / PI) * d4;
      return d5;
}

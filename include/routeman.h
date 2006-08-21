/******************************************************************************
 * $Id: routeman.h,v 1.1 2006/08/21 05:52:11 dsr Exp $
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
 * Revision 1.1  2006/08/21 05:52:11  dsr
 * Initial revision
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



//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
//    class declarations
//----------------------------------------------------------------------------

class Route;
class RoutePoint;

//----------------------------------------------------------------------------
//   Routeman
//----------------------------------------------------------------------------

class Routeman
{
public:
      Routeman();
      ~Routeman();

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

#endif

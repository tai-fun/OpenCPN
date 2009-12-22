/******************************************************************************
 * $Id:
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
 *
 * $Log: navutil.cpp,v $
 * Revision 1.56  2009/12/22 21:45:17  bdbcat
 * Cleanup
 *
 * Revision 1.55  2009/12/10 21:12:54  bdbcat
 * Beta 1210
 *
 * Revision 1.54  2009/11/23 04:38:51  bdbcat
 * Unicode correction
 *
 * Revision 1.53  2009/11/23 04:18:00  bdbcat
 * Improve GPX Track logic
 *
 * Revision 1.52  2009/11/18 01:24:54  bdbcat
 * 1.3.5 Beta 1117
 *
 * Revision 1.51  2009/09/30 02:32:38  bdbcat
 * Update to GPX 1.1 format
 *
 * Revision 1.50  2009/09/29 18:09:54  bdbcat
 * Add color to managed fonts
 *
 * Revision 1.48  2009/09/25 15:13:27  bdbcat
 * Correct waypoint date/time
 *
 * Revision 1.47  2009/09/18 02:21:16  bdbcat
 * Various, MSVC fonts, dialog locations
 *
 * Revision 1.46  2009/09/11 23:19:01  bdbcat
 * *** empty log message ***
 *
 * Revision 1.45  2009/09/04 01:56:03  bdbcat
 * New config options
 *
 * Revision 1.44  2009/08/30 14:19:40  bdbcat
 * Correct Track last point coordinates
 *
 * Revision 1.43  2009/08/30 03:31:56  bdbcat
 * Optimize wxGraphicsContext calls
 *
 * Revision 1.42  2009/08/29 23:25:59  bdbcat
 * Correct leak in Route::Draw()
 *
 * Revision 1.41  2009/08/25 21:32:13  bdbcat
 * Various, including GDK SIGSEGV workaround
 *
 * Revision 1.40  2009/08/22 01:21:17  bdbcat
 * Tracks
 *
 * Revision 1.39  2009/08/03 03:08:20  bdbcat
 * Improve Waypoint logic
 *
 * Revision 1.38  2009/07/29 00:49:54  bdbcat
 * Update Route Draw logic
 *
 * Revision 1.37  2009/07/17 03:54:54  bdbcat
 * Add config option for Wheel Zoom to cursor.
 *
 * Revision 1.36  2009/07/16 02:43:49  bdbcat
 * Various, esp Export Route.
 *
 * Revision 1.35  2009/07/08 01:51:15  bdbcat
 * Cleanup.
 *
 * Revision 1.34  2009/06/30 03:02:16  bdbcat
 * Add configurable chart cache limit.
 *
 * Revision 1.33  2009/06/28 21:41:09  bdbcat
 * Save GPX_IO directory fix.
 *
 * Revision 1.32  2009/06/28 03:34:52  bdbcat
 * Save GPX_IO directory.
 *
 * Revision 1.31  2009/06/17 02:46:29  bdbcat
 * More Options
 *
 * Revision 1.30  2009/06/14 01:51:16  bdbcat
 * AIS Alert Dialog
 *
 * Revision 1.29  2009/06/03 03:18:27  bdbcat
 * Correct GPX Route import logic
 *
 * Revision 1.28  2009/05/14 02:48:34  bdbcat
 * Correct southern latitude restore on startup.
 *
 * Revision 1.27  2009/05/09 01:30:52  bdbcat
 * Correct wx constants in wxFileDialog.
 *
 * Revision 1.26  2009/05/05 03:59:27  bdbcat
 * New text options
 *
 * Revision 1.25  2009/04/19 02:24:56  bdbcat
 * Implement "Important Text" option
 *
 * Revision 1.24  2009/04/13 02:33:25  bdbcat
 * Add "show ATON labels" option
 *
 * Revision 1.23  2009/03/30 19:06:17  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.22  2009/03/26 22:29:39  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.21  2008/12/22 18:38:56  bdbcat
 * Add NMEA Debug flag
 *
 * Revision 1.20  2008/12/19 01:46:02  bdbcat
 * Add selectable depth unit conversion for S57 charts
 *
 * Revision 1.19  2008/11/12 04:13:11  bdbcat
 * Support Garmin Devices / Mac Fonts / Cleanup
 *
 * Revision 1.18  2008/10/31 01:07:43  bdbcat
 * Fix initial Lat/Lon/scale value logic
 *
 * Revision 1.17  2008/10/23 23:28:47  bdbcat
 * Add OwnShipLatLon to config file for debugging
 *
 * Revision 1.16  2008/08/26 13:48:15  bdbcat
 * Better color scheme support
 *
 * Revision 1.15  2008/08/09 23:58:40  bdbcat
 * Numerous revampings....
 *
 * Revision 1.13  2008/04/11 03:25:08  bdbcat
 * Implement Auto Anchor Mark
 *
 * Revision 1.12  2008/04/10 01:03:51  bdbcat
 * Cleanup
 *
 * Revision 1.11  2008/03/30 22:05:53  bdbcat
 * Support Route/Mark Properties
 *
 * Revision 1.10  2008/01/12 06:20:35  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.9  2008/01/10 03:36:33  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.7  2007/06/10 02:29:34  bdbcat
 * Color scheme support
 *
 * Revision 1.6  2007/05/03 13:23:55  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.5  2007/03/02 02:01:06  dsr
 * Cleanup, improve horizontal route segment selection
 *
 * Revision 1.4  2006/11/01 02:15:58  dsr
 * AIS Support
 *
 * Revision 1.3  2006/10/01 03:22:58  dsr
 * no message
 *
 *
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/tokenzr.h>
#include <wx/sstream.h>
#include <wx/image.h>
#include <wx/filename.h>
#include <wx/graphics.h>

#include "dychart.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <wx/listimpl.cpp>

#include "chart1.h"
#include "navutil.h"
#include "chcanv.h"
#include "georef.h"
#include "nmea.h"
#include "ais.h"
#include "cutil.h"
#include "routeman.h"
#include "s52utils.h"
#include "chartbase.h"
#include "cm93.h"

#ifdef USE_S57
#include "s52plib.h"
#endif

CPL_CVSID ( "$Id: navutil.cpp,v 1.56 2009/12/22 21:45:17 bdbcat Exp $" );

//    Statics

extern ChartBase        *Current_Ch;
extern ChartCanvas      *cc1;
extern MyFrame          *gFrame;
extern NMEAWindow       *g_pnmea;
extern FontMgr          *pFontMgr;

extern RouteList        *pRouteList;
extern Select           *pSelect;
extern MyConfig         *pConfig;
extern ArrayOfCDI       g_ChartDirArray;
extern double           vLat, vLon, gLat, gLon;
extern double           kLat, kLon;
extern double           initial_scale_ppm;
extern ColorScheme      global_color_scheme;

extern wxToolBarBase    *toolBar;
extern wxString         *pNMEADataSource;
extern wxString         *pNMEA_AP_Port;
extern wxString         *pWIFIServerName;
extern wxString         *g_pcsv_locn;
extern wxString         *g_pSENCPrefix;
extern wxString         g_PresLibData;

extern bool             g_bShowPrintIcon;
extern AutoPilotWindow  *pAPilot;
extern wxString         *pAIS_Port;
extern AIS_Decoder      *g_pAIS;
extern wxString         g_SData_Locn;
extern wxString         *pInit_Chart_Dir;
extern WayPointman      *pWayPointMan;
extern Routeman         *pRouteMan;
extern ComPortManager   *g_pCommMan;

extern bool             s_bSetSystemTime;
extern bool             g_bShowDepthUnits;
extern bool             g_bAutoAnchorMark;
extern bool             g_bShowOutlines;
extern bool             g_bGarminPersistance;
extern int              g_nNMEADebug;

extern int              g_nframewin_x;
extern int              g_nframewin_y;
extern bool             g_bframemax;

extern double           g_PlanSpeed;
extern wxRect           g_blink_rect;

extern wxArrayString    *pMessageOnceArray;

//    AIS Global configuration
extern bool             g_bCPAMax;
extern double           g_CPAMax_NM;
extern bool             g_bCPAWarn;
extern double           g_CPAWarn_NM;
extern bool             g_bTCPA_Max;
extern double           g_TCPA_Max;
extern bool             g_bMarkLost;
extern double           g_MarkLost_Mins;
extern bool             g_bRemoveLost;
extern double           g_RemoveLost_Mins;
extern bool             g_bShowCOG;
extern double           g_ShowCOG_Mins;
extern bool             g_bShowTracks;
extern bool             g_bTrackCarryOver;
extern double           g_ShowTracks_Mins;
extern bool             g_bShowMoored;
extern double           g_ShowMoored_Kts;
extern bool             g_bAIS_CPA_Alert;
extern bool             g_bAIS_CPA_Alert_Audio;
extern int              g_ais_alert_dialog_x, g_ais_alert_dialog_y;
extern int              g_ais_alert_dialog_sx, g_ais_alert_dialog_sy;
extern int              g_ais_query_dialog_x, g_ais_query_dialog_y;
extern wxString         g_sAIS_Alert_Sound_File;
extern bool             g_bAIS_CPA_Alert_Suppress_Moored;

extern bool             g_bShowPrintIcon;
extern bool             g_bShowGPXIcons;              // toh, 2009.02.14
extern bool             g_bNavAidShowRadarRings;            // toh, 2009.02.24
extern int              g_iNavAidRadarRingsNumberVisible;   // toh, 2009.02.24
extern float            g_fNavAidRadarRingsStep;            // toh, 2009.02.24
extern int              g_pNavAidRadarRingsStepUnits;       // toh, 2009.02.24
extern bool             g_bWayPointPreventDragging;         // toh, 2009.02.24

extern bool             g_bEnableZoomToCursor;
extern bool             g_bShowTrackIcon;
extern double           g_TrackIntervalSeconds;
extern double           g_TrackDeltaDistance;
extern bool             g_bTrackTime;
extern bool             g_bTrackDistance;
extern int              gsp_watchdog_timeout_ticks;

extern int              g_nCacheLimit;

extern bool             g_bGDAL_Debug;
extern bool             g_bDebugCM93;
extern bool             g_bDebugS57;

#ifdef USE_S57
extern s52plib          *ps52plib;
#endif

extern wxString         g_CM93DictDir;
extern int              g_cm93_zoom_factor;
extern bool             g_bShowCM93DetailSlider;
extern int              g_cm93detail_dialog_x, g_cm93detail_dialog_y;

extern bool             g_bUseGreenShip;

extern wxString         g_grib_dir;
extern bool             g_bShowGRIBIcon;
extern bool             g_bGRIBUseHiDef;
extern int              g_grib_dialog_x, g_grib_dialog_y;
extern int              g_grib_dialog_sx, g_grib_dialog_sy;

extern bool             g_b_overzoom_x;                      // Allow high overzoom
extern bool             g_bshow_overzoom_emboss;
extern int              g_nautosave_interval_seconds;
extern int              g_n_ownship_meters;

extern bool             g_bPreserveScaleOnX;

extern bool             g_bUseRMC;
extern bool             g_bUseGLL;

extern TTYWindow        *g_NMEALogWindow;
extern int              g_NMEALogWindow_x, g_NMEALogWindow_y;
extern int              g_NMEALogWindow_sx, g_NMEALogWindow_sy;

extern wxString         g_locale;

//------------------------------------------------------------------------------
// Some wxWidgets macros for useful classes
//------------------------------------------------------------------------------
WX_DEFINE_LIST ( RouteList );
WX_DEFINE_LIST ( SelectableItemList );
WX_DEFINE_LIST ( RoutePointList );
WX_DEFINE_LIST ( HyperlinkList );         // toh, 2009.02.22

//-----------------------------------------------------------------------------
//          Selectable Item
//-----------------------------------------------------------------------------

SelectItem::SelectItem()
{
}

SelectItem::~SelectItem()
{
}


int  SelectItem::GetUserData ( void )
{
      return m_Data4;
}

void  SelectItem::SetUserData ( int data )
{
      m_Data4 = data;
}




//-----------------------------------------------------------------------------
//          Select
//-----------------------------------------------------------------------------

Select::Select()
{
      pSelectList = new SelectableItemList;
}

Select::~Select()
{
      pSelectList->DeleteContents ( true );
      pSelectList->Clear();
      delete pSelectList;


}

bool Select::AddSelectableRoutePoint ( float slat, float slon, RoutePoint *pRoutePointAdd )
{
      SelectItem *pSelItem = new SelectItem;
      pSelItem->m_slat = slat;
      pSelItem->m_slon = slon;
      pSelItem->m_seltype = SELTYPE_ROUTEPOINT;
      pSelItem->m_bIsSelected = false;
      pSelItem->m_pData1 = pRoutePointAdd;

      pSelectList->Append ( pSelItem );

      return true;
}

bool Select::AddSelectableRouteSegment ( float slat1, float slon1, float slat2, float slon2,
        RoutePoint *pRoutePointAdd1, RoutePoint *pRoutePointAdd2,
        Route *pRoute )
{
      SelectItem *pSelItem = new SelectItem;
      pSelItem->m_slat = slat1;
      pSelItem->m_slon = slon1;
      pSelItem->m_slat2 = slat2;
      pSelItem->m_slon2 = slon2;
      pSelItem->m_seltype = SELTYPE_ROUTESEGMENT;
      pSelItem->m_bIsSelected = false;
      pSelItem->m_pData1 = pRoutePointAdd1;
      pSelItem->m_pData2 = pRoutePointAdd2;
      pSelItem->m_pData3 = pRoute;

      pSelectList->Append ( pSelItem );

      return true;
}

bool Select::DeleteAllSelectableRouteSegments ( Route *pr )
{
      SelectItem *pFindSel;

//    Iterate on the select list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while ( node )
      {
            pFindSel = node->GetData();
            if ( pFindSel->m_seltype == SELTYPE_ROUTESEGMENT )
            {

//                  RoutePoint *ps1 = (RoutePoint *)pFindSel->m_pData1;
//                  RoutePoint *ps2 = (RoutePoint *)pFindSel->m_pData2;

                  if ( ( Route * ) pFindSel->m_pData3  == pr )
                  {
                        delete pFindSel;
                        pSelectList->DeleteNode ( node );   //delete node;

                        node = pSelectList->GetFirst();     // reset the top node

                        goto got_next_outer_node;
                  }
            }

            node = node->GetNext();
      got_next_outer_node:
            continue;
      }


      return true;
}


bool Select::DeleteAllSelectableRoutePoints ( Route *pr )
{
      SelectItem *pFindSel;

//    Iterate on the select list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while ( node )
      {
            pFindSel = node->GetData();
            if ( pFindSel->m_seltype == SELTYPE_ROUTEPOINT )
            {
                  RoutePoint *ps = ( RoutePoint * ) pFindSel->m_pData1;

                  //    inner loop iterates on the route's point list
                  wxRoutePointListNode *pnode = ( pr->pRoutePointList )->GetFirst();
                  while ( pnode )
                  {
                        RoutePoint *prp = pnode->GetData();

                        if ( prp == ps )
                        {
                              delete pFindSel;
                              pSelectList->DeleteNode ( node );   //delete node;
                              node = pSelectList->GetFirst();

                              goto got_next_outer_node;
                        }
                        pnode = pnode->GetNext();
                  }
            }

            node = node->GetNext();
      got_next_outer_node:
            continue;
      }
      return true;
}


bool Select::AddAllSelectableRoutePoints ( Route *pr )
{
      if ( pr->pRoutePointList->GetCount() )
      {
            wxRoutePointListNode *node = ( pr->pRoutePointList )->GetFirst();

            while ( node )
            {
                  RoutePoint *prp = node->GetData();
                  AddSelectableRoutePoint ( prp->m_lat, prp->m_lon, prp );
                  node = node->GetNext();
            }
            return true;
      }
      else
            return false;
}

bool Select::AddAllSelectableRouteSegments ( Route *pr )
{
      wxPoint rpt, rptn;
      float slat1, slon1, slat2, slon2;

      if ( pr->pRoutePointList->GetCount() )
      {
            wxRoutePointListNode *node = ( pr->pRoutePointList )->GetFirst();

            RoutePoint *prp0 = node->GetData();
            slat1 = prp0->m_lat;
            slon1 = prp0->m_lon;

            node = node->GetNext();

            while ( node )
            {
                  RoutePoint *prp = node->GetData();
                  slat2 = prp->m_lat;
                  slon2 = prp->m_lon;

                  AddSelectableRouteSegment ( slat1, slon1, slat2, slon2, prp0, prp, pr );

                  slat1 = slat2;
                  slon1 = slon2;
                  prp0 = prp;

                  node = node->GetNext();
            }
            return true;
      }
      else
            return false;
}

bool Select::UpdateSelectableRouteSegments ( RoutePoint *prp )
{
      SelectItem *pFindSel;
      bool ret = false;

//    Iterate on the select list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while ( node )
      {
            pFindSel = node->GetData();
            if ( pFindSel->m_seltype == SELTYPE_ROUTESEGMENT )
            {
                  if ( pFindSel->m_pData1 == prp )
                  {
                        pFindSel->m_slat = prp->m_lat;
                        pFindSel->m_slon = prp->m_lon;
                        ret = true;;
                  }

                  else if ( pFindSel->m_pData2 == prp )
                  {
                        pFindSel->m_slat2 = prp->m_lat;
                        pFindSel->m_slon2 = prp->m_lon;
                        ret = true;
                  }
            }
            node = node->GetNext();
      }


      return ret;
}





//-----------------------------------------------------------------------------------
//          Selectable Point Object Support
//-----------------------------------------------------------------------------------

SelectItem *Select::AddSelectablePoint ( float slat, float slon, void *pdata, int fseltype )
{
      SelectItem *pSelItem = new SelectItem;
      if ( pSelItem )
      {
            pSelItem->m_slat = slat;
            pSelItem->m_slon = slon;
            pSelItem->m_seltype = fseltype;
            pSelItem->m_bIsSelected = false;
            pSelItem->m_pData1 = pdata;

            pSelectList->Append ( pSelItem );
      }

      return pSelItem;
}

bool Select::DeleteAllPoints ( void )
{
      pSelectList->DeleteContents ( true );
      pSelectList->Clear();
      return true;
}


bool Select::DeleteSelectablePoint ( void *pdata, int SeltypeToDelete )
{
      SelectItem *pFindSel;

      if ( NULL != pdata )
      {
//    Iterate on the list
            wxSelectableItemListNode *node = pSelectList->GetFirst();

            while ( node )
            {
                  pFindSel = node->GetData();
                  if ( pFindSel->m_seltype == SeltypeToDelete )
                  {
                        if ( pdata == pFindSel->m_pData1 )
                        {
                              delete pFindSel;
                              delete node;
                              return true;
                        }
                  }
                  node = node->GetNext();
            }
      }
      return false;
}


bool Select::DeleteAllSelectableTypePoints ( int SeltypeToDelete )
{
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while ( node )
      {
            pFindSel = node->GetData();
            if ( pFindSel->m_seltype == SeltypeToDelete )
            {
                  delete pFindSel;
                  delete node;
                  node = pSelectList->GetFirst();
                  goto got_next_node;
            }

            node = node->GetNext();
      got_next_node:
            continue;
      }
      return true;
}

bool Select::ModifySelectablePoint ( float lat, float lon, void *data, int SeltypeToModify )
{
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while ( node )
      {
            pFindSel = node->GetData();
            if ( pFindSel->m_seltype == SeltypeToModify )
            {
                  if ( data == pFindSel->m_pData1 )
                  {
                        pFindSel->m_slat = lat;
                        pFindSel->m_slon = lon;
                        return true;
                  }
            }

            node = node->GetNext();
      }
      return false;
}



SelectItem *Select::FindSelection ( float slat, float slon, int fseltype, float SelectRadius )
{
      float a,b,c,d;
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while ( node )
      {
            pFindSel = node->GetData();
            if ( pFindSel->m_seltype == fseltype )
            {
                  switch ( fseltype )
                  {
                        case SELTYPE_ROUTEPOINT:
                        case SELTYPE_TIDEPOINT:
                        case SELTYPE_CURRENTPOINT:
                        case SELTYPE_AISTARGET:
                              a = fabs ( slat - pFindSel->m_slat );
                              b = fabs ( slon - pFindSel->m_slon );

                              if ( ( fabs ( slat - pFindSel->m_slat ) < SelectRadius ) &&
                                      ( fabs ( slon - pFindSel->m_slon ) < SelectRadius ) )
                                    goto find_ok;
                              break;
                        case SELTYPE_ROUTESEGMENT:
                        {
                              a = pFindSel->m_slat;
                              b = pFindSel->m_slat2;
                              c = pFindSel->m_slon;
                              d = pFindSel->m_slon2;

                              double adder = 0.;

                              if ( ( c * d ) < 0. )
                              {
                                    //    Arrange for points to be increasing longitude, c to d
                                    double dist, brg;
                                    DistanceBearingMercator ( a, c, b, d, &brg, &dist );
                                    if ( brg < 180. )             // swap points?
                                    {
                                          double tmp;
                                          tmp = c; c=d; d=tmp;
                                          tmp = a; a=b; b=tmp;
                                    }
                                    if ( d < 0. )     // idl?
                                    {
                                          d += 360.;
                                          if ( slon < 0. )
                                                adder = 360.;
                                    }
                              }


//    As a course test, use segment bounding box test
                              if ( ( slat >= ( fmin ( a,b ) - SelectRadius ) ) && ( slat <= ( fmax ( a,b ) + SelectRadius ) ) &&
                                      ( ( slon + adder ) >= ( fmin ( c,d ) - SelectRadius ) ) && ( ( slon + adder ) <= ( fmax ( c,d ) + SelectRadius ) ) )
                              {
//    Use vectors to do hit test....
                                    VECTOR2D va, vb, vn;

                                    va.x = ( slon + adder ) - c;
                                    va.y = slat - a;
                                    vb.x = d - c;
                                    vb.y = b - a;

                                    double delta = vGetLengthOfNormal ( &va, &vb, &vn );
                                    if ( fabs ( delta ) < SelectRadius )
                                          goto find_ok;
                              }

                              break;
                        }
                        default:
                              break;
                  }
            }


            node = node->GetNext();
      }

      return NULL;
find_ok:
      return pFindSel;
}


//-----------------------------------------------------------------------------
//          WayPoint Implementation
//-----------------------------------------------------------------------------
RoutePoint::RoutePoint ( double lat, double lon, const wxString& icon_ident, const wxString& name, wxString *pGUID )
{
      //  Establish points
      m_lat = lat;
      m_lon = lon;

      //      Normalize the longitude, to fix any old poorly formed points
      if ( m_lon < -180. )
            m_lon += 360.;
      else if ( m_lon > 180. )
            m_lon -= 360.;


      //  Nice defaults
      m_seg_len = 0.0;
      m_bDynamicName = false;
      m_bPtIsSelected = false;
      m_bIsBeingEdited = false;
      m_bIsActive = false;
      m_bBlink = false;
      m_bIsInRoute = false;
      m_bIsolatedMark = false;
      m_bShowName = true;
      m_bKeepXRoute = false;
      m_bIsVisible = true;
      m_ConfigWPNum = -1;
      CurrentRect_in_DC = wxRect ( 0,0,0,0 );
      m_NameLocationOffsetX = -10;
      m_NameLocationOffsetY = 8;

      m_prop_string_format = _T ( "A" );              // Set the current Property String format indicator

      m_HyperlinkList = NULL;
      m_HyperlinkList = new HyperlinkList;

      wxString GUID = pWayPointMan->CreateGUID ( this );

      if ( NULL != pGUID )
      {
            if ( pGUID->IsEmpty() )
                  m_GUID = GUID;

            else
                  m_GUID = *pGUID;
      }
      else
            m_GUID = GUID;

      //      Get Icon bitmap
      m_IconName = icon_ident;
      ReLoadIcon();

      m_MarkName = name;

      //  Add the waypoint to the global list maintained by the waypoint manager

      if ( NULL != pWayPointMan )
            pWayPointMan->m_pWayPointList->Append ( this );
}


RoutePoint::~RoutePoint ( void )
{
//  Remove this point from the global waypoint list
      if ( NULL != pWayPointMan )
            pWayPointMan->m_pWayPointList->DeleteObject ( this );

      delete m_HyperlinkList;
}

wxString RoutePoint::CreatePropString ( void )
{
      wxString ret;
      ret.Printf ( _T ( ",%d,%d,%d,%d" ), m_bDynamicName, m_bShowName, m_bKeepXRoute, m_bIsVisible );
      ret.Prepend ( m_prop_string_format );
      return ret;
}

void RoutePoint::SetPropFromString ( const wxString &prop_string )
{
      long tmp_prop;
      wxString str_fmt;

      if ( !prop_string.IsEmpty() )
      {
            wxStringTokenizer tkp ( prop_string, _T ( "," ) );

            //  Look at the first character
            wxString c1 = prop_string.Mid ( 0,1 );
            if ( c1.ToLong ( &tmp_prop ) )
                  str_fmt = _T ( "A" );       // Assume format version is 'A' if first char is numeric
            else
                  str_fmt = tkp.GetNextToken();

            if ( str_fmt == _T ( "A" ) )
            {

                  wxString token = tkp.GetNextToken();
                  token.ToLong ( &tmp_prop );
                  m_bDynamicName = ! ( tmp_prop == 0 );

                  token = tkp.GetNextToken();
                  token.ToLong ( &tmp_prop );
                  m_bShowName = ! ( tmp_prop == 0 );

                  token = tkp.GetNextToken();
                  token.ToLong ( &tmp_prop );
                  m_bKeepXRoute = ! ( tmp_prop == 0 );

                  token = tkp.GetNextToken();               // format A might or might not have 4 fields
                  if ( token.Len() )
                  {
                        token.ToLong ( &tmp_prop );
                        m_bIsVisible = ! ( tmp_prop == 0 );
                  }
                  else
                        m_bIsVisible = true;
            }
      }

}



void RoutePoint::ReLoadIcon ( void )
{
      m_pbmIcon = pWayPointMan->GetIconBitmap ( m_IconName );
}


void RoutePoint::Draw ( wxDC& dc, wxPoint *rpn )
{
      wxPoint r;
      wxRect            hilitebox;
      unsigned char transparency = 200;

      cc1->GetCanvasPointPix ( m_lat, m_lon, &r );
//      printf(" x: %d     y: %d\n", r.x, r.y);

//      r = cc1->VPoint.GetMercatorPixFromLL(m_lat, m_lon);
//      printf("      vpx: %d     vpy: %d\n", r.x, r.y);

      //  return the home point in this dc to allow "connect the dots"
      if ( NULL != rpn )
            *rpn = r;

      if ( !m_bIsVisible )
            return;

      wxPen *pen;
      if ( m_bBlink )
            pen = pRouteMan->GetActiveRoutePointPen();
      else
            pen = pRouteMan->GetRoutePointPen();

      unsigned char ol_red   = pen->GetColour().Red(); //50;
      unsigned char ol_green = pen->GetColour().Green(); //100;
      unsigned char ol_blue  = pen->GetColour().Blue(); //255;


//    Substitue icon?
      wxBitmap *pbm;
      if ( m_bIsActive )
            pbm = pWayPointMan->GetIconBitmap ( _T ( "activepoint" ) );
      else
            pbm =m_pbmIcon;

      int sx2 = pbm->GetWidth() /2;
      int sy2 = pbm->GetHeight() /2;



//    Calculate the mark drawing extents
      wxRect r1 ( r.x-sx2, r.y-sy2, sx2 * 2, sy2 * 2 );
      if ( m_bShowName )
      {
            dc.SetFont ( *pFontMgr->GetFont ( _T ( "Marks" ) ) );
            int stextx, stexty;
            dc.GetTextExtent ( m_MarkName, &stextx, &stexty );
            wxRect r2 ( r.x + m_NameLocationOffsetX, r.y + m_NameLocationOffsetY, stextx, stexty );
            r1.Union ( r2 );
      }
      hilitebox = r1;
      hilitebox.x -= r.x;
      hilitebox.y -= r.y;
      hilitebox.Inflate ( 2 );

      //  Highlite any selected point
      if ( m_bPtIsSelected )
      {
            DrawTransparentBox ( dc, r.x + hilitebox.x, r.y + hilitebox.y, hilitebox.width, hilitebox.height,
                                 ol_red, ol_green, ol_blue, transparency );
      }

      bool bDrawHL = false;

      if ( m_bBlink && ( gFrame->nBlinkerTick & 1 ) )
            bDrawHL = true;

      if ( ( !bDrawHL ) && ( NULL != m_pbmIcon ) )
      {
            dc.DrawBitmap ( *pbm, r.x - sx2, r.y - sy2, true );
            // on MSW, the dc Bounding box is not updated on DrawBitmap() method.
            // Do it explicitely here for all platforms.
            dc.CalcBoundingBox ( r.x - sx2, r.y - sy2 );
            dc.CalcBoundingBox ( r.x + sx2, r.y + sy2 );

      }

      if ( m_bShowName )
      {
            dc.SetFont ( *pFontMgr->GetFont ( _T ( "Marks" ) ) );
            dc.SetTextForeground(pFontMgr->GetFontColor(_T("Marks")));

            dc.DrawText ( m_MarkName, r.x + m_NameLocationOffsetX, r.y + m_NameLocationOffsetY );
      }



      //  Save the current draw rectangle in the current DC
      //    This will be useful for fast icon redraws
      CurrentRect_in_DC.x      = r.x + hilitebox.x;
      CurrentRect_in_DC.y      = r.y + hilitebox.y;
      CurrentRect_in_DC.width  = hilitebox.width;
      CurrentRect_in_DC.height = hilitebox.height;



      if ( m_bBlink )
            g_blink_rect = CurrentRect_in_DC;               // also save for global blinker

}

void RoutePoint::DrawTransparentBox ( wxDC& dc, int x, int y, int size_x, int size_y,
                                      unsigned char rval, unsigned char gval, unsigned char bval, unsigned char transparency )
{

      //    Get wxImage of area of interest
      wxBitmap obm ( size_x, size_y );
      wxMemoryDC mdc1;
      mdc1.SelectObject ( obm );
      mdc1.Blit ( 0, 0, size_x, size_y, &dc, x, y );
      mdc1.SelectObject ( wxNullBitmap );
      wxImage oim = obm.ConvertToImage();

      //    Create an image with selected transparency/color
      int olay_red   = rval * transparency;
      int olay_green = gval * transparency;
      int olay_blue  = bval * transparency;

      //    Create destination image
      wxImage dest ( size_x, size_y, false );
      unsigned char *dest_data = ( unsigned char * ) malloc ( size_x * size_y * 3 * sizeof ( unsigned char ) );
      unsigned char *po = oim.GetData();
      unsigned char *d = dest_data;

      int sb = size_x * size_y;
      for ( int i=0 ; i<sb ; i++ )
      {
            int r = ( ( *po++ ) * 255 ) + olay_red;
            *d++ = ( unsigned char ) ( r / 512 );
            int g = ( ( *po++ ) * 255 ) + olay_green;
            *d++ = ( unsigned char ) ( g / 512 );
            int b = ( ( *po++ ) * 255 ) + olay_blue;
            *d++ = ( unsigned char ) ( b / 512 );
      }

      dest.SetData ( dest_data );

      //    Convert destination to bitmap and draw it
      wxBitmap dbm ( dest );
      dc.DrawBitmap ( dbm, x, y, false );

      // on MSW, the dc Bounding box is not updated on DrawBitmap() method.
      // Do it explicitely here for all platforms.
      dc.CalcBoundingBox ( x, y );
      dc.CalcBoundingBox ( x + size_x, y + size_y );

}

void RoutePoint::SetPosition ( double lat, double lon )
{
      m_lat = lat;
      m_lon = lon;
}


void RoutePoint::CalculateDCRect ( wxDC& dc, wxRect *prect )
{
      dc.ResetBoundingBox();
      dc.DestroyClippingRegion();

      // Draw the mark on the dc
      Draw ( dc, NULL );

      //  Retrieve the drawing extents
      prect->x = dc.MinX() - 1;
      prect->y = dc.MinY() - 1;
      prect->width  = dc.MaxX() - dc.MinX() + 2; // Mouse Poop?
      prect->height = dc.MaxY() - dc.MinY() + 2;

}

// toh, 2009.02.23
bool RoutePoint::IsSame ( RoutePoint *pOtherRP )
{
      bool IsSame = false;

      if ( this->m_MarkName == pOtherRP->m_MarkName )
      {
            if ( fabs ( this->m_lat-pOtherRP->m_lat ) < 1.e-6 && fabs ( this->m_lon-pOtherRP->m_lon ) < 1.e-6 )
                  IsSame = true;
      }
      return IsSame;
}




//-----------------------------------------------------------------------------
//          Route Implementation
//-----------------------------------------------------------------------------

Route::Route ( void )
{
      m_bRtIsSelected = false;
      m_bRtIsActive = false;
      m_pRouteActivePoint = NULL;
      m_bIsBeingEdited = false;
      m_bIsBeingCreated = false;
      m_bIsTrack = false;
      m_nPoints = 0;
      m_nm_sequence = 1;
      m_route_length = 0.0;

      pRoutePointList = new RoutePointList;
      m_pLastAddedPoint = NULL;

      RBBox.Reset();
}


Route::~Route ( void )
{
      pRoutePointList->DeleteContents ( false );            // do not delete Marks
      pRoutePointList->Clear();
      delete pRoutePointList;
}


void Route::AddPoint ( RoutePoint *pNewPoint, bool b_rename_in_sequence )
{
      pNewPoint->m_bIsInRoute = true;
      pNewPoint->m_bIsolatedMark = false;       // definitely no longer isolated

      pRoutePointList->Append ( pNewPoint );

      m_nPoints++;

      RBBox.Expand(pNewPoint->m_lon, pNewPoint->m_lat);


      if(m_pLastAddedPoint)
            pNewPoint->m_seg_len = DistGreatCircle(m_pLastAddedPoint->m_lat, m_pLastAddedPoint->m_lon, pNewPoint->m_lat, pNewPoint->m_lon);

      m_route_length += pNewPoint->m_seg_len;

      m_pLastAddedPoint = pNewPoint;

      if ( b_rename_in_sequence && pNewPoint->m_MarkName.IsEmpty() )
      {
            pNewPoint->m_MarkName.Printf ( _T ( "%03d" ), m_nPoints );
            pNewPoint->m_bDynamicName = true;
      }
      return;
}


void Route::AddTentativePoint ( const wxString& GUID )
{
      RoutePointGUIDList.Add ( GUID );
      return;
}





RoutePoint *Route::GetPoint ( int nWhichPoint )
{
      RoutePoint *prp;
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      int i=1;
      while ( node )
      {
            prp = node->GetData();
            if ( i == nWhichPoint )
                  return prp;

            i++;
            node = node->GetNext();
      }

      return ( NULL );
}

void Route::DrawPointWhich ( wxDC& dc, int iPoint, wxPoint *rpn )
{
      GetPoint ( iPoint )->Draw ( dc, rpn );
}



void Route::DrawSegment ( wxDC& dc, wxPoint *rp1, wxPoint *rp2, ViewPort &VP, bool bdraw_arrow )
{
      if ( m_bRtIsSelected )
            dc.SetPen ( *pRouteMan->GetSelectedRoutePen() );
      else if ( m_bRtIsActive )
            dc.SetPen ( *pRouteMan->GetActiveRoutePen() );
      else
            dc.SetPen ( *pRouteMan->GetRoutePen() );

      RenderSegment ( dc, rp1->x, rp1->y, rp2->x, rp2->y, VP, bdraw_arrow );
}




void Route::Draw ( wxDC& dc, ViewPort &VP )
{
      if ( m_nPoints == 0 )
            return;

      if ( m_bRtIsSelected )
      {
            dc.SetPen ( *pRouteMan->GetRoutePen() );
            dc.SetBrush ( *pRouteMan->GetRouteBrush() );
      }
      else if ( m_bRtIsActive )
      {
            dc.SetPen ( *pRouteMan->GetActiveRoutePen() );
            dc.SetBrush ( *pRouteMan->GetActiveRouteBrush() );
      }
      else
      {
            dc.SetPen ( *pRouteMan->GetRoutePen() );
            dc.SetBrush ( *pRouteMan->GetRouteBrush() );
      }



      wxPoint rpt1, rpt2;
      DrawPointWhich ( dc, 1, &rpt1 );

      wxRoutePointListNode *node = pRoutePointList->GetFirst();
      RoutePoint *prp1 = node->GetData();
      node = node->GetNext();

      while ( node )
      {

            RoutePoint *prp2 = node->GetData();
            prp2->Draw ( dc, &rpt2 );

            //    Handle offscreen points
            bool b_2_on = VP.vpBBox.PointInBox ( prp2->m_lon, prp2->m_lat, 0 );
            bool b_1_on = VP.vpBBox.PointInBox ( prp1->m_lon, prp1->m_lat, 0 );

            //TODO This logic could be simpliifed
            //Simple case
            if ( b_1_on && b_2_on )
                  RenderSegment ( dc, rpt1.x, rpt1.y, rpt2.x, rpt2.y, VP, true );         // with arrows

            //    In the cases where one point is on, and one off
            //    we must decide which way to go in longitude
            //     Arbitrarily, we will go the shortest way

            double pix_full_circle =  WGS84_semimajor_axis_meters * mercator_k0 * 2 * PI * VP.view_scale_ppm;
            double dp = pow ( ( double ) ( rpt1.x - rpt2.x ), 2 ) + pow ( ( double ) ( rpt1.y - rpt2.y ), 2 );
            double dtest;
            int adder;
            if ( b_1_on && !b_2_on )
            {
                  if ( rpt2.x < rpt1.x )
                        adder = ( int ) pix_full_circle;
                  else
                        adder = - ( int ) pix_full_circle;

                  dtest = pow ( ( double ) ( rpt1.x - ( rpt2.x + adder ) ), 2 ) + pow ( ( double ) ( rpt1.y - rpt2.y ), 2 );

                  if ( dp < dtest )
                        adder = 0;

                  RenderSegment ( dc, rpt1.x, rpt1.y, rpt2.x + adder, rpt2.y, VP, true );
            }
            else if ( !b_1_on && b_2_on )
            {
                  if ( rpt1.x < rpt2.x )
                        adder = ( int ) pix_full_circle;
                  else
                        adder = - ( int ) pix_full_circle;

                  dtest = pow ( ( double ) ( rpt2.x - ( rpt1.x + adder ) ), 2 ) + pow ( ( double ) ( rpt1.y - rpt2.y ), 2 );

                  if ( dp < dtest )
                        adder = 0;

                  RenderSegment ( dc, rpt1.x + adder, rpt1.y, rpt2.x, rpt2.y, VP, true );
            }

            //Both off, need to check shortest distance
            else if ( !b_1_on && !b_2_on )
            {
                  if ( rpt1.x < rpt2.x )
                        adder = ( int ) pix_full_circle;
                  else
                        adder = - ( int ) pix_full_circle;

                  dtest = pow ( ( double ) ( rpt2.x - ( rpt1.x + adder ) ), 2 ) + pow ( ( double ) ( rpt1.y - rpt2.y ), 2 );

                  if ( dp < dtest )
                        adder = 0;

                  RenderSegment ( dc, rpt1.x + adder, rpt1.y, rpt2.x, rpt2.y, VP, true );
            }






            rpt1 = rpt2;
            prp1 = prp2;

            node = node->GetNext();
      }
}

static int s_arrow_icon[] =
{
      0, 0,
      5, 2,
      18, 6,
      12, 0,
      18,-6,
      5, -2,
      0, 0
};


void Route::RenderSegment ( wxDC& dc, int xa, int ya, int xb, int yb, ViewPort &VP, bool bdraw_arrow, int hilite_width )
{
      //    Get the dc boundary
      int sx, sy;
      dc.GetSize ( &sx, &sy );

      //    Clip the line segment to the dc boundary
      int x0 = xa;
      int y0 = ya;
      int x1 = xb;
      int y1 = yb;


      //    If hilite is desired, use a Native Graphics context to render alpha colours
      //    That is, if wxGraphicsContext is available.....

#if dwxUSE_GRAPHICS_CONTEXT
      if ( hilite_width )
      {
            wxGraphicsContext *pgc;

            wxMemoryDC *pmdc = wxDynamicCast ( &dc, wxMemoryDC );
            if ( pmdc )
            {
                  pgc = wxGraphicsContext::Create ( *pmdc );
            }
            else
            {
                  wxClientDC *pcdc = wxDynamicCast ( &dc, wxClientDC );
                  if ( pcdc )
                        pgc = wxGraphicsContext::Create ( *pcdc );
            }


            if ( pgc )
            {
                  if ( Visible == cohen_sutherland_line_clip_i ( &x0, &y0, &x1, &y1, 0, sx, 0, sy ) )
                  {
                        wxPen psave = dc.GetPen();

                        wxColour y = GetGlobalColor ( _T ( "YELO1" ) );
                        wxColour hilt ( y.Red(), y.Green(), y.Blue(), 128 );

                        wxPen HiPen ( hilt, hilite_width, wxSOLID );

                        pgc->SetPen ( HiPen );
                        pgc->StrokeLine ( x0, y0, x1, y1 );

                        pgc->SetPen ( psave );
                        pgc->StrokeLine ( x0, y0, x1, y1 );
                  }

                  delete pgc;
            }
      }

      else
#endif
      {
            if ( Visible == cohen_sutherland_line_clip_i ( &x0, &y0, &x1, &y1, 0, sx, 0, sy ) )
                  dc.DrawLine ( x0, y0, x1, y1 );
      }

      if ( bdraw_arrow )
      {
            //    Draw a direction arrow

            double theta = atan2 ( ( double ) ( yb-ya ), ( double ) ( xb-xa ) );
            theta -= PI / 2;


            wxPoint icon[10];
            double icon_scale_factor = 100 * VP.view_scale_ppm;
            icon_scale_factor = fmin ( icon_scale_factor, 1.5 );              // Sets the max size
            icon_scale_factor = fmax ( icon_scale_factor, .10 );

            //    Get the absolute line length
            //    and constrain the arrow to be no more than xx% of the line length
            double nom_arrow_size = 20.;
            double max_arrow_to_leg = .20;
            double lpp = sqrt ( pow ( ( double ) ( xa - xb ), 2 ) + pow ( ( double ) ( ya - yb ), 2 ) );

            double icon_size = icon_scale_factor * nom_arrow_size;
            if ( icon_size > ( lpp * max_arrow_to_leg ) )
                  icon_scale_factor = ( lpp * max_arrow_to_leg ) / nom_arrow_size;


            for ( int i=0; i<7; i++ )
            {
                  int j = i * 2;
                  double pxa = ( double ) ( s_arrow_icon[j] );
                  double pya = ( double ) ( s_arrow_icon[j+1] );

                  pya *=  icon_scale_factor;
                  pxa *=  icon_scale_factor;

                  double px = ( pxa * sin ( theta ) ) + ( pya * cos ( theta ) );
                  double py = ( pya * sin ( theta ) ) - ( pxa * cos ( theta ) );

                  icon[i].x = ( int ) ( px ) + xb;
                  icon[i].y = ( int ) ( py ) + yb;
            }
            dc.DrawPolygon ( 6, &icon[0], 0, 0 );
      }
}





void Route::ClearHighlights ( void )
{
      RoutePoint *prp = NULL;
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      while ( node )
      {
            prp = node->GetData();
            if ( prp )
                  prp->m_bPtIsSelected = false;
            node = node->GetNext();
      }
}


RoutePoint *Route::InsertPointBefore ( RoutePoint *pRP, float rlat, float rlon, bool bRenamePoints )
{
      RoutePoint *newpoint = new RoutePoint ( rlat, rlon, wxString ( _T ( "diamond" ) ), GetNewMarkSequenced(), NULL );
      newpoint->m_bIsInRoute = true;
      newpoint->m_bDynamicName = true;

      int nRP = pRoutePointList->IndexOf ( pRP );
      pRoutePointList->Insert ( nRP, newpoint );

      RoutePointGUIDList.Insert ( pRP->m_GUID, nRP );

      m_nPoints++;

      if ( bRenamePoints )
            RenameRoutePoints();

      CalculateBBox();
      UpdateSegmentDistances();

      return ( newpoint );
}


wxString Route::GetNewMarkSequenced ( void )
{
      wxString ret;
      ret.Printf ( _T ( "NM%03d" ), m_nm_sequence );
      m_nm_sequence++;

      return ret;
}

RoutePoint *Route::GetLastPoint()
{
      RoutePoint *data_m1 = NULL;
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      while ( node )
      {
            data_m1 = node->GetData();
            node = node->GetNext();
      }
      return ( data_m1 );
}

int Route::GetIndexOf ( RoutePoint *prp )
{
      int ret = pRoutePointList->IndexOf ( prp ) + 1;
      if ( ret == wxNOT_FOUND )
            return 0;
      else
            return ret;

}

void Route::DeletePoint ( RoutePoint *rp, bool bRenamePoints )
{
      pRoutePointList->DeleteObject ( rp );

      if ( rp->m_GUID.Len() )
            RoutePointGUIDList.Remove ( rp->m_GUID );

      delete rp;

      m_nPoints -= 1;

      if ( bRenamePoints )
            RenameRoutePoints();

      CalculateBBox();
      UpdateSegmentDistances();
}

void Route::RemovePoint ( RoutePoint *rp, bool bRenamePoints )
{
      pRoutePointList->DeleteObject ( rp );
      RoutePointGUIDList.Remove ( rp->m_GUID );
      m_nPoints -= 1;


      // check all other routes to see if this point appears in any other route
      Route *pcontainer_route = pRouteMan->FindRouteContainingWaypoint ( rp );

      if ( pcontainer_route == NULL )
      {
            rp->m_bIsInRoute = false;          // Take this point out of this (and only) route
            rp->m_bDynamicName = false;
            rp->m_bIsolatedMark = true;        // This has become an isolated mark
      }


      if ( bRenamePoints )
            RenameRoutePoints();

      CalculateBBox();
      UpdateSegmentDistances();
}



void Route::DeSelectRoute()
{
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *rp;
      while ( node )
      {
            rp = node->GetData();
            rp->m_bPtIsSelected = false;

            node = node->GetNext();
      }
}


void Route::ReloadRoutePointIcons()
{
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *rp;
      while ( node )
      {
            rp = node->GetData();
            rp->ReLoadIcon();

            node = node->GetNext();
      }
}



void Route::CalculateBBox()
{

      double bbox_xmin = 180.;                        // set defaults
      double bbox_ymin = 90.;
      double bbox_xmax = -180;
      double bbox_ymax = -90.;


      RBBox.Reset();

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *data;
      while ( node )
      {
            data = node->GetData();

            if ( data->m_lon > bbox_xmax )
                  bbox_xmax = data->m_lon;
            if ( data->m_lon < bbox_xmin )
                  bbox_xmin = data->m_lon;
            if ( data->m_lat > bbox_ymax )
                  bbox_ymax = data->m_lat;
            if ( data->m_lat < bbox_ymin )
                  bbox_ymin = data->m_lat;

            node = node->GetNext();
      }


      RBBox.Expand ( bbox_xmin, bbox_ymin );
      RBBox.Expand ( bbox_xmax, bbox_ymax );


}

void Route::CalculateDCRect ( wxDC& dc_route, wxRect *prect, ViewPort &VP )
{

      dc_route.ResetBoundingBox();
      dc_route.DestroyClippingRegion();

      // Draw the route on the dc
      Draw ( dc_route, VP );

      //  Retrieve the drawing extents
      prect->x = dc_route.MinX() - 1;
      prect->y = dc_route.MinY() - 1;
      prect->width  = dc_route.MaxX() - dc_route.MinX() + 2; // Mouse Poop?
      prect->height = dc_route.MaxY() - dc_route.MinY() + 2;

}


/*
Update the route segment lengths, storing each segment length in <destination> point.
Also, compute total route length by summing segment distances.
*/
void Route::UpdateSegmentDistances()
{
      wxPoint rpt, rptn;
      float slat1, slon1, slat2, slon2;

      double route_len = 0.0;

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      if ( node )
      {
            RoutePoint *prp0 = node->GetData();
            slat1 = prp0->m_lat;
            slon1 = prp0->m_lon;

            node = node->GetNext();

            while ( node )
            {
                  RoutePoint *prp = node->GetData();
                  slat2 = prp->m_lat;
                  slon2 = prp->m_lon;

//    Calculate the absolute distance from 1->2

                  double brg, dd;
                  DistanceBearingMercator(slat1, slon1, slat2, slon2, &brg, &dd);

//    And store in Point 2
                  prp->m_seg_len = dd;

                  route_len += dd;

                  slat1 = slat2;
                  slon1 = slon2;
                  prp0 = prp;

                  node = node->GetNext();
            }
      }

      m_route_length = route_len;
}


void Route::Reverse ( bool bRenamePoints )
{
      RebuildGUIDList();                        // ensure the GUID list is intact and good

      //    Reverse the GUID list
      wxArrayString ArrayTemp;

      int ncount = RoutePointGUIDList.GetCount();
      for ( int i=0 ; i<ncount ; i++ )
            ArrayTemp.Add ( RoutePointGUIDList[ncount - 1 - i] );

      RoutePointGUIDList = ArrayTemp;

      pRoutePointList->DeleteContents ( false );
      pRoutePointList->Clear();
      m_nPoints = 0;

      AssembleRoute();                          // Rebuild the route points from the GUID list

      if ( bRenamePoints )
            RenameRoutePoints();
}

void Route::RebuildGUIDList ( void )
{
      RoutePointGUIDList.Clear();               // empty the GUID list

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *rp;
      while ( node )
      {
            rp = node->GetData();
            RoutePointGUIDList.Add ( rp->m_GUID );

            node = node->GetNext();
      }
}

void Route::AssembleRoute ( void )
{
      //    iterate over the RoutePointGUIDs
      for ( unsigned int ip = 0 ; ip < RoutePointGUIDList.GetCount() ; ip++ )
      {
            wxString GUID = RoutePointGUIDList[ip];

            //    And on the RoutePoints themselves
            wxRoutePointListNode *prpnode = pWayPointMan->m_pWayPointList->GetFirst();
            while ( prpnode )
            {
                  RoutePoint *prp = prpnode->GetData();

                  if ( prp->m_GUID == GUID )
                  {
                        AddPoint ( prp );
                        break;
                  }
                  prpnode = prpnode->GetNext(); //RoutePoint
            }
      }
}

void Route::RenameRoutePoints ( void )
{
      //    iterate on the route points.
      //    If dynamically named, rename according to current list position

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      int i = 1;
      while ( node )
      {
            RoutePoint *prp = node->GetData();
            if ( prp->m_bDynamicName )
                  prp->m_MarkName.Printf ( _T ( "%03d" ), i );

            node = node->GetNext();
            i++;
      }
}


bool Route::SendToGPS ( wxString& com_name, bool bsend_waypoints, wxGauge *pProgress )
{
      SENTENCE    snt;
      NMEA0183    oNMEA0183;
      oNMEA0183.TalkerID = _T ( "EC" );

      int nProg = pRoutePointList->GetCount() + 1;
      if ( pProgress )
            pProgress->SetRange ( 100 );

      int port_fd = g_pCommMan->OpenComPort ( com_name, 4800 );

      //    Send out the waypoints, in order
      if ( bsend_waypoints )
      {
            wxRoutePointListNode *node = pRoutePointList->GetFirst();

            int ip = 1;
            while ( node )
            {
                  RoutePoint *prp = node->GetData();

                  if ( prp->m_lat < 0. )
                        oNMEA0183.Wpl.Position.Latitude.Set ( -prp->m_lat, _T ( "S" ) );
                  else
                        oNMEA0183.Wpl.Position.Latitude.Set ( prp->m_lat, _T ( "N" ) );

                  if ( prp->m_lon < 0. )
                        oNMEA0183.Wpl.Position.Longitude.Set ( -prp->m_lon, _T ( "W" ) );
                  else
                        oNMEA0183.Wpl.Position.Longitude.Set ( prp->m_lon, _T ( "E" ) );


                  oNMEA0183.Wpl.To = prp->m_MarkName.Truncate ( 6 );

                  oNMEA0183.Wpl.Write ( snt );

                  g_pCommMan->WriteComPort ( com_name, snt.Sentence );

                  if ( pProgress )
                  {
                        pProgress->SetValue ( ( ip * 100 ) / nProg );
                        pProgress->Refresh();
                        pProgress->Update();
                  }

                  wxMilliSleep ( 1000 );

                  node = node->GetNext();

                  ip++;
            }
      }

      //    Create the NMEA Rte sentence

      oNMEA0183.Rte.Empty();
      oNMEA0183.Rte.TypeOfRoute = CompleteRoute;

      if ( m_RouteNameString.IsEmpty() )
            oNMEA0183.Rte.RouteName = _T ( "00" );
      else
            oNMEA0183.Rte.RouteName = m_RouteNameString;

      oNMEA0183.Rte.total_number_of_messages     = 1;
      oNMEA0183.Rte.message_number               = 1;

      //    add the waypoints
      wxRoutePointListNode *node = pRoutePointList->GetFirst();
      while ( node )
      {
            RoutePoint *prp = node->GetData();
            oNMEA0183.Rte.AddWaypoint ( prp->m_MarkName.Truncate ( 6 ) );
            node = node->GetNext();
      }


      oNMEA0183.Rte.Write ( snt );

//      printf("%s", snt.Sentence.mb_str());
      g_pCommMan->WriteComPort ( com_name, snt.Sentence );


      wxMilliSleep ( 1000 );

      g_pCommMan->CloseComPort ( port_fd );

      return true;
}

//    Is this route equal to another, meaning,
//    Do all routepoint positions and names match?
bool Route::IsEqualTo ( Route *ptargetroute )
{
      wxRoutePointListNode *pthisnode = ( this->pRoutePointList )->GetFirst();
      wxRoutePointListNode *pthatnode = ( ptargetroute->pRoutePointList )->GetFirst();

      if ( NULL == pthisnode )
            return false;

      while ( pthisnode )
      {
            if ( NULL == pthatnode )
                  return false;

            RoutePoint *pthisrp = pthisnode->GetData();
            RoutePoint *pthatrp = pthatnode->GetData();

            if ( ( fabs ( pthisrp->m_lat - pthatrp->m_lat ) > 1.0e-6 ) || ( fabs ( pthisrp->m_lon - pthatrp->m_lon ) > 1.0e-6 ) )
                  return false;

            if ( !pthisrp->m_MarkName.IsSameAs ( pthatrp->m_MarkName ) )
                  return false;

            pthisnode = pthisnode->GetNext();
            pthatnode = pthatnode->GetNext();
      }

      return true;                              // success, they are the same
}

//---------------------------------------------------------------------------------
//    Track Implementation
//---------------------------------------------------------------------------------
BEGIN_EVENT_TABLE ( Track, wxEvtHandler )
      EVT_TIMER ( TIMER_TRACK1, Track::OnTimerTrack )
END_EVENT_TABLE()

Track::Track ( void )
{
      m_TimerTrack.SetOwner ( this, TIMER_TRACK1 );
      m_TimerTrack.Stop();
      m_bRunning = false;
      m_bIsTrack = true;
      m_TrackTimerSec = -1;
      m_DeltaDistance = 0.0;
      m_bTrackTime = false;
      m_bTrackDistance = false;
      m_prev_time = wxDateTime::Now();
      m_prev_time.ResetTime();            // set to midnight this morning.

      wxDateTime now = wxDateTime::Now();
      m_ConfigRouteNum = now.GetTicks();        // a unique number....

      m_track_run = 0;
}

Track::~Track()
{
      Stop();
}


void Track::Start ( void )
{
      if ( !m_bRunning )
      {
            AddPointNow();                   // Add initial point
            m_TimerTrack.Start ( 1000, wxTIMER_CONTINUOUS );
            m_bRunning = true;
      }
}

void Track::Stop ( void )
{
      if ( m_bRunning )
            AddPointNow();                   // Add last point


      m_TimerTrack.Stop();
      m_bRunning = false;
      m_track_run = 0;
}


void Track::OnTimerTrack ( wxTimerEvent& event )
{
      m_TimerTrack.Stop();
      m_track_run++;

      double delta = DistGreatCircle ( gLat, gLon, m_prev_glat, m_prev_glon );
      bool b_addpoint = false;

      if ( m_bTrackTime && ( m_TrackTimerSec > 0. ) && ( ( double ) m_track_run >= m_TrackTimerSec ) )
      {
            b_addpoint = true;
            m_track_run = 0;
      }
      else if ( m_bTrackDistance && ( m_DeltaDistance > 0.0 ) && ( delta >= m_DeltaDistance ) )
            b_addpoint = true;

      if ( b_addpoint )
            AddPointNow();

      m_TimerTrack.Start ( 1000, wxTIMER_CONTINUOUS );
}

void Track::AddPointNow()
{

      wxDateTime now = wxDateTime::Now();

      if((m_prev_glat == gLat) && (m_prev_glon == gLon))                 // avoid zero length segs
            return;

      if(m_prev_time == now)                                            // avoid zero time segs
            return;

      RoutePoint *pTrackPoint = new RoutePoint ( gLat, gLon, wxString ( _T ( "xmred" ) ), wxString ( _T ( "" ) ), NULL );
      pTrackPoint->m_bShowName = false;
      pTrackPoint->m_bIsVisible  = false;
      pTrackPoint->m_CreateTime = now.ToUTC();

      AddPoint ( pTrackPoint );

      if ( GetnPoints() > 1 )
            pSelect->AddSelectableRouteSegment ( m_prev_glat, m_prev_glon, gLat, gLon,
                                                 m_prev_pTrackPoint, pTrackPoint, this );

      m_prev_glon = gLon;
      m_prev_glat = gLat;

      m_prev_time = now;
}


void Track::Draw ( wxDC& dc, ViewPort &VP )
{
      if ( GetnPoints() == 0 )
            return;

      dc.SetBrush ( wxBrush ( GetGlobalColor ( _T ( "CHMGD" ) ) ) );
      wxPen dPen ( GetGlobalColor ( _T ( "CHMGD" ) ), 3 ) ;
      dc.SetPen ( dPen );

      double radius_meters = Current_Ch->GetNativeScale() * .0015;         // 1.5 mm at original scale
      double radius = radius_meters * VP.view_scale_ppm;


      wxPoint rpt, rptn;
      DrawPointWhich ( dc, 1, &rpt );

      wxRoutePointListNode *node = pRoutePointList->GetFirst();
      node = node->GetNext();

      while ( node )
      {

            RoutePoint *prp = node->GetData();
            prp->Draw ( dc, &rptn );

            RenderSegment ( dc, rpt.x, rpt.y, rptn.x, rptn.y, VP, false, ( int ) radius );      // no arrows, with hilite
            rpt = rptn;

            node = node->GetNext();
      }

      //    Draw last segment, dynamically, maybe.....

      if ( m_bRunning )
      {
            wxPoint r;
            cc1->GetCanvasPointPix ( gLat, gLon, &r );
            RenderSegment ( dc, rpt.x, rpt.y, r.x, r.y, VP, false, ( int ) radius );      // no arrows, with hilite
      }
}






//-----------------------------------------------------------------------------
//          MyConfig Implementation
//-----------------------------------------------------------------------------


MyConfig::MyConfig ( const wxString &appName, const wxString &vendorName, const wxString &LocalFileName )
            :wxFileConfig ( appName, vendorName, LocalFileName, wxString ( _T ( "" ) ) )
{
      //    Create the default NavObjectCollection FileName
      wxFileName config_file ( LocalFileName );
      m_sNavObjSetFile = config_file.GetPath ( wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR );
      m_sNavObjSetFile += _T ( "navobj.xml" );

      m_pNavObjectInputSet = NULL;
//      m_pNavObjectOutputSet = NULL;
}



int MyConfig::LoadMyConfig ( int iteration )
{

      int read_int;

//    Global options and settings
      SetPath ( _T ( "/Settings" ) );

      // Some undocumented values
      Read ( _T ( "nCacheLimit" ), &g_nCacheLimit, CACHE_N_LIMIT_DEFAULT );
      Read ( _T ( "DebugGDAL" ), &g_bGDAL_Debug, 0 );
      Read ( _T ( "DebugNMEA" ), &g_nNMEADebug, 0 );
      Read ( _T ( "GPSDogTimeout" ),  &gsp_watchdog_timeout_ticks, GPS_TIMEOUT_SECONDS );
      Read ( _T ( "DebugCM93" ),  &g_bDebugCM93, 0 );
      Read ( _T ( "DebugS57" ),  &g_bDebugS57, 0 );
      Read ( _T ( "UseGreenShipIcon" ),  &g_bUseGreenShip, 0 );
      Read ( _T ( "AllowExtremeOverzoom" ),  &g_b_overzoom_x, 1 );
      Read ( _T ( "ShowOverzoomEmbossWarning" ),  &g_bshow_overzoom_emboss, 1 );
      Read ( _T ( "AutosaveIntervalSeconds" ),  &g_nautosave_interval_seconds, 300 );
      Read ( _T ( "OwnshipLengthMeters" ),  &g_n_ownship_meters, 12 );
      Read ( _T ( "UseNMEA_RMC" ),  &g_bUseRMC, 1 );
      Read ( _T ( "UseNMEA_GLL" ),  &g_bUseGLL, 1 );

      Read ( _T ( "CM93DetailFactor" ),  &g_cm93_zoom_factor, 0 );
      g_cm93_zoom_factor = wxMin(g_cm93_zoom_factor,CM93_ZOOM_FACTOR_MAX_RANGE);
      g_cm93_zoom_factor = wxMax(g_cm93_zoom_factor,(-CM93_ZOOM_FACTOR_MAX_RANGE));

      g_cm93detail_dialog_x = Read ( _T ( "CM93DetailZoomPosX" ), 200L );
      g_cm93detail_dialog_y = Read ( _T ( "CM93DetailZoomPosY" ), 200L );
      Read ( _T ( "ShowCM93DetailSlider" ),  &g_bShowCM93DetailSlider, 0 );

      Read ( _T ( "SetSystemTime" ), &s_bSetSystemTime, 0 );
      Read ( _T ( "ShowDebugWindows" ), &m_bShowDebugWindows, 1 );
      Read ( _T ( "ShowPrintIcon" ), &g_bShowPrintIcon, 0 );
      Read ( _T ( "ShowDepthUnits" ), &g_bShowDepthUnits, 1 );
      Read ( _T ( "AutoAnchorDrop" ),  &g_bAutoAnchorMark, 0 );
      Read ( _T ( "ShowChartOutlines" ),  &g_bShowOutlines, 0 );
      Read ( _T ( "GarminPersistance" ),  &g_bGarminPersistance, 0 );
      Read ( _T ( "ShowGRIBIcon" ),  &g_bShowGRIBIcon, 0 );
      Read ( _T ( "GRIBUseHiDef" ),  &g_bGRIBUseHiDef, 0 );

      g_grib_dialog_sx = Read ( _T ( "GRIBDialogSizeX" ), 300L );
      g_grib_dialog_sy = Read ( _T ( "GRIBDialogSizeY" ), 540L );
      g_grib_dialog_x =  Read ( _T ( "GRIBDialogPosX" ), 20L );
      g_grib_dialog_y =  Read ( _T ( "GRIBDialogPosY" ), 20L );

      Read ( _T ( "StartWithTrackActive" ),  &g_bTrackCarryOver, 0 );

      wxString stps;
      Read ( _T ( "PlanSpeed" ),  &stps );
      stps.ToDouble ( &g_PlanSpeed );

      Read ( _T ( "PreserveScaleOnX" ),  &g_bPreserveScaleOnX, 0 );

      g_locale = _T("en_US");
      Read ( _T ( "Locale" ), &g_locale );

      SetPath ( _T ( "/Settings/GlobalState" ) );
      Read ( _T ( "bFollow" ), &st_bFollow );

      Read ( _T ( "FrameWinX" ), &g_nframewin_x );
      Read ( _T ( "FrameWinY" ), &g_nframewin_y );
      Read ( _T ( "FrameMax" ),  &g_bframemax );


      //    AIS
      wxString s;
      SetPath ( _T ( "/Settings/AIS" ) );

      Read ( _T ( "bNoCPAMax" ), &g_bCPAMax );

      Read ( _T ( "NoCPAMaxNMi" ),  &s );
      s.ToDouble ( &g_CPAMax_NM );

      Read ( _T ( "bCPAWarn" ), &g_bCPAWarn );

      Read ( _T ( "CPAWarnNMi" ),  &s );
      s.ToDouble ( &g_CPAWarn_NM );

      Read ( _T ( "bTCPAMax" ), &g_bTCPA_Max );

      Read ( _T ( "TCPAMaxMinutes" ),  &s );
      s.ToDouble ( &g_TCPA_Max );

      Read ( _T ( "bMarkLostTargets" ), &g_bMarkLost );

      Read ( _T ( "MarkLost_Minutes" ),  &s );
      s.ToDouble ( &g_MarkLost_Mins );

      Read ( _T ( "bRemoveLostTargets" ), &g_bRemoveLost );

      Read ( _T ( "RemoveLost_Minutes" ),  &s );
      s.ToDouble ( &g_RemoveLost_Mins );

      Read ( _T ( "bShowCOGArrows" ), &g_bShowCOG );

      Read ( _T ( "CogArrowMinutes" ),  &s );
      s.ToDouble ( &g_ShowCOG_Mins );

      Read ( _T ( "bShowTargetTracks" ), &g_bShowTracks );

      Read ( _T ( "TargetTracksMinutes" ),  &s );
      s.ToDouble ( &g_ShowTracks_Mins );

      Read ( _T ( "bShowMooredTargets" ), &g_bShowMoored );

      Read ( _T ( "MooredTargetMaxSpeedKnots" ),  &s );
      s.ToDouble ( &g_ShowMoored_Kts );

      Read ( _T ( "bAISAlertDialog" ), &g_bAIS_CPA_Alert );

      Read ( _T ( "bAISAlertAudio" ), &g_bAIS_CPA_Alert_Audio );
      Read ( _T ( "AISAlertAudioFile" ),  &g_sAIS_Alert_Sound_File );
      Read ( _T ( "bAISAlertSuppressMoored" ), &g_bAIS_CPA_Alert_Suppress_Moored );

      g_ais_alert_dialog_sx = Read ( _T ( "AlertDialogSizeX" ), 200L );
      g_ais_alert_dialog_sy = Read ( _T ( "AlertDialogSizeY" ), 200L );
      g_ais_alert_dialog_x = Read ( _T ( "AlertDialogPosX" ), 200L );
      g_ais_alert_dialog_y = Read ( _T ( "AlertDialogPosY" ), 200L );
      g_ais_query_dialog_x = Read ( _T ( "QueryDialogPosX" ), 200L );
      g_ais_query_dialog_y = Read ( _T ( "QueryDialogPosY" ), 200L );

      g_NMEALogWindow_sx = Read ( _T ( "NMEALogWindowSizeX" ), 400L );
      g_NMEALogWindow_sy = Read ( _T ( "NMEALogWindowSizeY" ), 100L );
      g_NMEALogWindow_x = Read ( _T ( "NMEALogWindowPosX" ), 10L );
      g_NMEALogWindow_y = Read ( _T ( "NMEALogWindowPosY" ), 10L );


#ifdef USE_S57
      if ( NULL != ps52plib )
      {
            SetPath ( _T ( "/Settings/GlobalState" ) );

            Read ( _T ( "bShowS57Text" ), &read_int, 0 );
            ps52plib->SetShowS57Text ( ! ( read_int == 0 ) );

            Read ( _T ( "bShowS57ImportantTextOnly" ), &read_int, 0 );
            ps52plib->SetShowS57ImportantTextOnly ( ! ( read_int == 0 ) );

            Read ( _T ( "bShowLightDescription" ), &read_int, 0 );
            ps52plib->SetShowLdisText ( ! ( read_int == 0 ) );

            Read ( _T ( "nDisplayCategory" ), &read_int, ( enum _DisCat ) OTHER );
            ps52plib->m_nDisplayCategory = ( enum _DisCat ) read_int;

            Read ( _T ( "nSymbolStyle" ), &read_int, ( enum _LUPname ) PAPER_CHART );
            ps52plib->m_nSymbolStyle = ( LUPname ) read_int;

            Read ( _T ( "nBoundaryStyle" ), &read_int, 0 );
            ps52plib->m_nBoundaryStyle = ( LUPname ) read_int;

            Read ( _T ( "bShowSoundg" ), &read_int, 0 );
            ps52plib->m_bShowSoundg = ! ( read_int == 0 );

            Read ( _T ( "bShowMeta" ), &read_int, 0 );
            ps52plib->m_bShowMeta = ! ( read_int == 0 );

            Read ( _T ( "bUseSCAMIN" ), &read_int, 0 );
            ps52plib->m_bUseSCAMIN = ! ( read_int == 0 );

            Read ( _T ( "bShowAtonText" ), &read_int, 0 );
            ps52plib->m_bShowAtonText = ! ( read_int == 0 );

            Read ( _T ( "bDeClutterText" ), &read_int, 0 );
            ps52plib->m_bDeClutterText = ! ( read_int == 0 );

            double dval;
            if ( Read ( _T ( "S52_MAR_SAFETY_CONTOUR" ), &dval, 5.0 ) )
                  S52_setMarinerParam ( S52_MAR_SAFETY_CONTOUR, dval );

            if ( Read ( _T ( "S52_MAR_SHALLOW_CONTOUR" ), &dval, 3.0 ) )
                  S52_setMarinerParam ( S52_MAR_SHALLOW_CONTOUR, dval );

            if ( Read ( _T ( "S52_MAR_DEEP_CONTOUR" ), &dval, 10.0 ) )
                  S52_setMarinerParam ( S52_MAR_DEEP_CONTOUR, dval );

            if ( Read ( _T ( "S52_MAR_TWO_SHADES" ), &dval, 0.0 ) )
                  S52_setMarinerParam ( S52_MAR_TWO_SHADES, dval );

            ps52plib->UpdateMarinerParams();

            SetPath ( _T ( "/Settings/GlobalState" ) );
            Read ( _T ( "S52_DEPTH_UNIT_SHOW" ), &read_int, 1 );   // default is metres
            ps52plib->m_nDepthUnitDisplay = read_int;
      }

      wxString strpres ( _T ( "PresentationLibraryData" ) );
      wxString valpres;
      SetPath ( _T ( "/Directories" ) );
      Read ( strpres, &valpres );              // Get the File name
      if ( iteration == 0 )
            g_PresLibData = valpres;

      wxString strd ( _T ( "S57DataLocation" ) );
      wxString val;
      SetPath ( _T ( "/Directories" ) );
      Read ( strd, &val );              // Get the Directory name


      wxString dirname ( val );
      if ( !dirname.IsEmpty() )
      {
            if ( g_pcsv_locn->IsEmpty() )   // on second pass, don't overwrite
            {
                  g_pcsv_locn->Clear();
                  g_pcsv_locn->Append ( val );
            }
      }

      wxString strs ( _T ( "SENCFileLocation" ) );
      SetPath ( _T ( "/Directories" ) );
      wxString vals;
      Read ( strs, &vals );              // Get the Directory name

      if ( iteration == 0 )
            *g_pSENCPrefix = vals;

#endif

      SetPath ( _T ( "/Directories" ) );
      Read ( _T ( "CM93DictionaryLocation" ), &g_CM93DictDir );

      Read ( _T ( "GRIBDirectory" ), &g_grib_dir );

      SetPath ( _T ( "/Directories" ) );
      wxString vald;
      Read ( _T ( "InitChartDir" ), &vald );           // Get the Directory name

      wxString dirnamed ( vald );
      if ( !dirnamed.IsEmpty() )
      {
            if ( pInit_Chart_Dir->IsEmpty() )   // on second pass, don't overwrite
            {
                  pInit_Chart_Dir->Clear();
                  pInit_Chart_Dir->Append ( vald );
            }
      }

      Read ( _T ( "GPXIODir" ), &m_gpx_path );           // Get the Directory name

      SetPath ( _T ( "/Settings/GlobalState" ) );
      Read ( _T ( "nColorScheme" ), &read_int, 0 );
      global_color_scheme = ( ColorScheme ) read_int;

      SetPath ( _T ( "/Settings/NMEADataSource" ) );
      Read ( _T ( "Source" ), pNMEADataSource, _T ( "NONE" ) );

      SetPath ( _T ( "/Settings/NMEAAutoPilotPort" ) );
      Read ( _T ( "Port" ), pNMEA_AP_Port, _T ( "NONE" ) );

      SetPath ( _T ( "/Settings/WiFiServer" ) );
      Read ( _T ( "Server" ), pWIFIServerName, _T ( "NONE" ) );

      SetPath ( _T ( "/Settings/AISPort" ) );
      Read ( _T ( "Port" ), pAIS_Port, _T ( "NONE" ) );

//    Reasonable starting point
      vLat = START_LAT;                   // display viewpoint
      vLon = START_LON;

      gLat = START_LAT;                   // GPS position, as default
      gLon = START_LON;

      initial_scale_ppm = .00003;        // decent initial value

      SetPath ( _T ( "/Settings/GlobalState" ) );
      wxString st;

      if ( Read ( _T ( "VPLatLon" ), &st ) )
      {
            sscanf ( st.mb_str ( wxConvUTF8 ), "%f,%f", &st_lat, &st_lon );

            //    Sanity check the lat/lon...both have to be reasonable.
            if ( fabs ( st_lon ) < 360. )
            {
                  while ( st_lon < -180. )
                        st_lon += 360.;

                  while ( st_lon > 180. )
                        st_lon -= 360.;

                  vLon = st_lon;
            }

            if ( fabs ( st_lat ) < 90.0 )
                  vLat = st_lat;
      }
      s.Printf ( _T ( "Setting Viewpoint Lat/Lon %g, %g" ), vLat, vLon );
      wxLogMessage ( s );


      if ( Read ( wxString ( _T ( "VPScale" ) ), &st ) )
      {
            sscanf ( st.mb_str ( wxConvUTF8 ), "%f", &st_view_scale );
//    Sanity check the scale
            st_view_scale = fmax ( st_view_scale, .001/32 );
            st_view_scale = fmin ( st_view_scale, 4 );
            initial_scale_ppm = st_view_scale;
      }


      wxString sll;
      float lat, lon;
      if ( Read ( _T ( "OwnShipLatLon" ), &sll ) )
      {
            sscanf ( sll.mb_str ( wxConvUTF8 ), "%f,%f", &lat, &lon );
//            gLat = lat;
//            gLon = lon;

            //    Sanity check the lat/lon...both have to be reasonable.
            if ( fabs ( lon ) < 360. )
            {
                  while ( lon < -180. )
                        lon += 360.;

                  while ( lon > 180. )
                        lon -= 360.;

                  gLon = lon;
            }

            if ( fabs ( lat ) < 90.0 )
                  gLat = st_lat;
      }
      s.Printf ( _T ( "Setting Ownship Lat/Lon %g, %g" ), gLat, gLon );
      wxLogMessage ( s );


#ifdef USE_S57
//    S57 Object Class Visibility

      bool bNeedNew = true;
      OBJLElement *pOLE;

      SetPath ( _T ( "/Settings/ObjectFilter" ) );

      if ( ps52plib )
      {
            int iOBJMax = GetNumberOfEntries();
            if ( iOBJMax )
            {

                  wxString str;
                  long val;
                  long dummy;

                  wxString sObj;

                  bool bCont = pConfig->GetFirstEntry ( str, dummy );
                  while ( bCont )
                  {
                        pConfig->Read ( str, &val );              // Get an Object Viz

                        if ( str.StartsWith ( _T ( "viz" ), &sObj ) )
                        {
                              for ( unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++ )
                              {
                                    pOLE = ( OBJLElement * ) ( ps52plib->pOBJLArray->Item ( iPtr ) );
                                    if ( !strncmp ( pOLE->OBJLName, sObj.mb_str(), 6 ) )
                                    {
                                          pOLE->nViz = val;
                                          bNeedNew = false;
                                          break;
                                    }
                              }

                              if ( bNeedNew )
                              {
                                    pOLE = ( OBJLElement * ) malloc ( sizeof ( OBJLElement ) );
                                    strcpy ( pOLE->OBJLName, sObj.mb_str() );
                                    pOLE->nViz = val;

                                    ps52plib->pOBJLArray->Add ( ( void * ) pOLE );
                              }
                        }
                        bCont = pConfig->GetNextEntry ( str, dummy );
                  }
            }
      }
#endif

//    Chart Directories
      SetPath ( _T ( "/ChartDirectories" ) );
      int iDirMax = GetNumberOfEntries();
      if ( iDirMax )
      {
            g_ChartDirArray.Empty();
            wxString str, val;
            long dummy;
            int nAdjustChartDirs = 0;
            int iDir = 0;
            bool bCont = pConfig->GetFirstEntry ( str, dummy );
            while ( bCont )
            {
                  pConfig->Read ( str, &val );              // Get a Directory name

                  wxString dirname ( val );
                  if ( !dirname.IsEmpty() )
                  {

                        /*     Special case for first time run after Windows install with sample chart data...
                               We desire that the sample configuration file opencpn.ini should not contain any
                               installation dependencies, so...
                               Detect and update the sample [ChartDirectories] entries to point to the Shared Data directory
                               For instance, if the (sample) opencpn.ini file should contain shortcut coded entries like:

                               [ChartDirectories]
                               ChartDir1=SampleCharts\\MaptechRegion7

                               then this entry will be updated to be something like:
                               ChartDir1=c:\Program Files\opencpn\SampleCharts\\MaptechRegion7

                        */
                        if ( dirname.Find ( _T ( "SampleCharts" ) ) == 0 )    // only update entries starting with "SampleCharts"
                        {
                              nAdjustChartDirs++;

                              pConfig->DeleteEntry ( str );
                              wxString new_dir = dirname.Mid ( dirname.Find ( _T ( "SampleCharts" ) ) );
                              new_dir.Prepend ( g_SData_Locn );
                              dirname=new_dir;
                        }


                        ChartDirInfo cdi;
                        cdi.fullpath = dirname.BeforeFirst('^');
                        cdi.magic_number = dirname.AfterFirst('^');

                        g_ChartDirArray.Add ( cdi );
                        iDir++;
                  }

                  bCont = pConfig->GetNextEntry ( str, dummy );
            }

            if ( nAdjustChartDirs )
                  pConfig->UpdateChartDirs ( g_ChartDirArray );
      }



//    Fonts

#ifdef __WXX11__
      SetPath ( _T ( "/Settings/X11Fonts" ) );
#endif

#ifdef __WXGTK__
      SetPath ( _T ( "/Settings/GTKFonts" ) );
#endif

#ifdef __WXMSW__
      SetPath ( _T ( "/Settings/MSWFonts" ) );
#endif

#ifdef __WXMAC__
      SetPath ( _T ( "/Settings/MacFonts" ) );
#endif

      if ( 0 == iteration )
      {
            wxString str;
            long dummy;
            wxString *pval = new wxString;

            bool bCont = GetFirstEntry ( str, dummy );
            while ( bCont )
            {
                  Read ( str, pval );
                  pFontMgr->LoadFontNative ( &str, pval );
                  bCont = GetNextEntry ( str, dummy );
            }
            delete pval;
      }



//    Routes
      if ( 0 == iteration )
      {
            int routenum = 0;
            pRouteList = new RouteList;

            SetPath ( _T ( "/Routes" ) );
            int iRoutes = GetNumberOfGroups();
            if ( iRoutes )
            {
                  int rnt;

                  wxString str, val;
                  long dummy;

                  bool bCont = GetFirstGroup ( str, dummy );
                  while ( bCont )
                  {
                        Route *pConfRoute = new Route();
                        pRouteList->Append ( pConfRoute );

                        int RouteNum;
                        sscanf ( str.mb_str(), "RouteDefn%d", &RouteNum );
                        pConfRoute->m_ConfigRouteNum = RouteNum;

                        SetPath ( str );
                        Read ( _T ( "RoutePoints" ), &val );          // nPoints
                        int nPoints = atoi ( val.mb_str() );

                        Read ( _T ( "RouteName" ), &pConfRoute->m_RouteNameString );
                        Read ( _T ( "RouteStart" ), &pConfRoute->m_RouteStartString );
                        Read ( _T ( "RouteEnd" ), &pConfRoute->m_RouteEndString );

                        //        Get extended properties
                        long tmp_prop;
                        wxString str_prop;
                        Read ( _T ( "Properties" ), &str_prop );                    // Properties

                        if ( !str_prop.IsEmpty() )
                        {
                              wxStringTokenizer tkp ( str_prop, _T ( "," ) );
                              wxString token;

                              token = tkp.GetNextToken();
                              token.ToLong ( &tmp_prop );
                              pConfRoute->m_bIsTrack = ! ( tmp_prop == 0 );
                        }



                        for ( int ip = 0 ; ip < nPoints ; ip++ )
                        {
                              wxString sipc;
                              sipc.Printf ( _T ( "RoutePointID%d" ), ip+1 );
                              wxString str_ID;
                              Read ( sipc, &str_ID );
                              if ( !str_ID.IsEmpty() )
                                    pConfRoute->AddTentativePoint ( str_ID );

                        }

                        SetPath ( _T ( ".." ) );
                        bCont = GetNextGroup ( str, dummy );

                        //    Get next available RouteDefnx number
                        sscanf ( str.mb_str(), "RouteDefn%d", &rnt );
                        if ( rnt > routenum )
                              routenum = rnt;
                  }
            }

            m_NextRouteNum = routenum + 1;
      }

      //    Marks
      if ( 0 == iteration )
      {
            m_NextWPNum = 0;
            int marknum = 0;

            SetPath ( _T ( "/Marks" ) );
            int iMarks = GetNumberOfGroups();
            if ( iMarks )
            {
                  int mnt;

                  wxString str, val;
                  long dummy;
                  double rlat, rlon;

                  bool bCont = GetFirstGroup ( str, dummy );
                  while ( bCont )
                  {
                        int MarkNum;
                        sscanf ( str.mb_str(), "MarkDefn%d", &MarkNum );

                        SetPath ( str );
                        wxString sipb;
                        sipb.Printf ( _T ( "RoutePoint" ) );
                        Read ( sipb, &val );                       // Point lat/lon
                        double lat = 0.;
                        double lon = 0.;
                        wxStringTokenizer tkz ( val, _T ( "," ) );

                        wxString token = tkz.GetNextToken();
                        token.ToDouble ( &lat );
                        rlat = lat;
                        token = tkz.GetNextToken();
                        token.ToDouble ( &lon );
                        rlon = lon;

                        wxString sipbn = sipb;
                        sipbn.Append ( _T ( "Name" ) );
                        wxString mark_name;
                        Read ( sipbn, &mark_name );                       // name

                        wxString sipbi = sipb;
                        sipbi.Append ( _T ( "Icon" ) );
                        wxString icon_name;
                        Read ( sipbi, &icon_name );                       // icon

                        if ( icon_name.IsEmpty() )
                              icon_name = _T ( "triangle" );

                        wxString sipb1 = sipb;
                        sipb1.Append ( _T ( "GUID" ) );
                        wxString str_GUID;
                        Read ( sipb1, &str_GUID );                       // GUID

                        //      Normalize the longitude, to fix any old poorly formed points
                        if ( rlon < -180. )
                              rlon += 360.;
                        else if ( rlon > 180. )
                              rlon -= 360.;

                        RoutePoint *pWP = new RoutePoint ( rlat, rlon, icon_name, mark_name, &str_GUID );

                        pWP->m_bIsolatedMark = true;                      // This is an isolated mark

//        Get extended properties
                        long tmp_prop;
                        wxString str_prop;
                        wxString sipb2 = sipb;
                        sipb2.Append ( _T ( "Prop" ) );
                        Read ( sipb2, &str_prop );                       // Properties

                        pWP->SetPropFromString ( str_prop );

                        sipb2 = sipb;
                        sipb2.Append ( _T ( "NameLocationOffset" ) );
                        Read ( sipb2, &str_prop );

                        if ( !str_prop.IsEmpty() )
                        {
                              wxStringTokenizer tkpp ( str_prop, _T ( "," ) );
                              token = tkpp.GetNextToken();
                              token.ToLong ( &tmp_prop );
                              pWP->m_NameLocationOffsetX = tmp_prop;

                              token = tkpp.GetNextToken();
                              token.ToLong ( &tmp_prop );
                              pWP->m_NameLocationOffsetY = tmp_prop;
                        }


                        // Get hyperlinks; toh, 2009.02.23
                        wxString str_hyperlinks;
                        wxString sipb3 = sipb;
                        sipb3.Append ( _T ( "Link" ) );

                        bool cont = true;
                        int i=1;
                        while ( cont )
                        {
                              wxString sipb4 = sipb3;
                              wxString buf;
                              buf.Printf ( _T ( "%d" ), i );
                              sipb4.Append ( buf );

                              cont = Read ( sipb4, &str_hyperlinks );                       // hyperlinks

                              if ( cont && !str_hyperlinks.IsEmpty() )
                              {
                                    Hyperlink *link;
                                    link = new Hyperlink;

                                    wxStringTokenizer tkp ( str_hyperlinks, _T ( "^" ) );

                                    token = tkp.GetNextToken();
                                    link->Link = token;

                                    token = tkp.GetNextToken();

                                    if ( token.Length() > 0 )
                                          link->DescrText = token;

                                    token = tkp.GetNextToken();

                                    if ( token.Length() > 0 )
                                          link->Type = token;

                                    if(NULL == pWP->m_HyperlinkList)
                                          pWP->m_HyperlinkList = new HyperlinkList;

                                    pWP->m_HyperlinkList->Append ( link );
                              }
                              i++;
                        }


                        pSelect->AddSelectableRoutePoint ( rlat, rlon, pWP );
                        pWP->m_ConfigWPNum = MarkNum;

                        SetPath ( _T ( ".." ) );
                        bCont = GetNextGroup ( str, dummy );

                        //    Get next available MarkDefnx number
                        sscanf ( str.mb_str(), "MarkDefn%d", &mnt );
                        if ( mnt > marknum )
                              marknum = mnt;
                  }
            }
            m_NextWPNum = marknum + 1;


      }

      //    Constitute the routes just loaded
      if ( 0 == iteration )
      {
            pRouteMan->AssembleAllRoutes();
      }

//      next thing to do is read tracks from the NavObject XML file,

      if ( 0 == iteration )
      {
            if ( NULL == m_pNavObjectInputSet )
                  m_pNavObjectInputSet = new NavObjectCollection ( _T ( "gpx" ), _T ( "1.0" ), _T ( "opencpn" ) );

            if ( ::wxFileExists ( m_sNavObjSetFile ) )
            {
                  m_pNavObjectInputSet->Load ( m_sNavObjSetFile );

                  m_pNavObjectInputSet->LoadAllGPXTracks();
            }

            delete m_pNavObjectInputSet;
      }

      //XML

      /*
            SetPath(_T("/Settings/XML"));
            wxString xml_file_string;
            Read(_T("XMLNavObjectFile"), &xml_file_string);
      */

      /*
      if(0 == iteration)
      {
            wxString xml_file_string(_T("test.xml"));

            if(::wxFileExists(xml_file_string))
            {
                  m_pXMLNavObj = new wxXmlDocument;
                  if(m_pXMLNavObj->Load(xml_file_string))
                  {
                        int i=9;
                  }
            }
      }
      */

      SetPath ( _T ( "/Settings/Others" ) );
      g_bShowGPXIcons = false;
      Read ( _T ( "ShowGPXIcons" ), &g_bShowGPXIcons );

      // Radar rings
      g_bNavAidShowRadarRings = false;          // toh, 2009.02.24
      Read ( _T ( "ShowRadarRings" ), &g_bNavAidShowRadarRings );

      g_iNavAidRadarRingsNumberVisible = 1;     // toh, 2009.02.24
      Read ( _T ( "RadarRingsNumberVisible" ), &val );
      if ( val.Length() > 0 )
            g_iNavAidRadarRingsNumberVisible = atoi ( val.mb_str() );

      g_fNavAidRadarRingsStep = 1.0;            // toh, 2009.02.24
      Read ( _T ( "RadarRingsStep" ), &val );
      if ( val.Length() > 0 )
            g_fNavAidRadarRingsStep = atof ( val.mb_str() );

      g_pNavAidRadarRingsStepUnits = 0;         // toh, 2009.02.24
      Read ( _T ( "RadarRingsStepUnits" ), &g_pNavAidRadarRingsStepUnits );

      // Waypoint dragging with mouse
      g_bWayPointPreventDragging = false;       // toh, 2009.02.24
      Read ( _T ( "WaypointPreventDragging" ), &g_bWayPointPreventDragging );

      g_bEnableZoomToCursor = false;
      Read ( _T ( "EnableZoomToCursor" ), &g_bEnableZoomToCursor );

      g_bShowTrackIcon = false;;
      Read ( _T ( "ShowTrackIcon" ), &g_bShowTrackIcon );

      g_TrackIntervalSeconds = 60.0;
      val.Clear();
      Read ( _T ( "TrackIntervalSeconds" ), &val );
      if ( val.Length() > 0 )
            g_TrackIntervalSeconds = atof ( val.mb_str() );

      g_TrackDeltaDistance = 0.10;
      val.Clear();
      Read ( _T ( "TrackDeltaDistance" ), &val );
      if ( val.Length() > 0 )
            g_TrackDeltaDistance = atof ( val.mb_str() );

      Read ( _T ( "EnableTrackByTime" ), &g_bTrackTime, 1 );
      Read ( _T ( "EnableTrackByDistance" ), &g_bTrackDistance, 0 );

      Read ( _T ( "NavObjectFileName" ), m_sNavObjSetFile );

      return ( 0 );
}


bool MyConfig::AddNewRoute ( Route *pr, int crm )
{
      wxString str_buf;
      int acrm;

      if ( crm != -1 )
            acrm = crm;
      else
            acrm = m_NextRouteNum;


//    Build the Group Name
      wxString t ( _T ( "/Routes/RouteDefn" ) );
      str_buf.Printf ( _T ( "%d" ), acrm );
      t.Append ( str_buf );

      SetPath ( t );

      str_buf.Printf ( _T ( "%d" ), pr->GetnPoints() );
      Write ( _T ( "RoutePoints" ), str_buf );

      Write ( _T ( "RouteName" ), pr->m_RouteNameString );
      Write ( _T ( "RouteStart" ), pr->m_RouteStartString );
      Write ( _T ( "RouteEnd" ), pr->m_RouteEndString );

      wxString Props;
      Props.Printf ( _T ( "%d" ), pr->m_bIsTrack );
      Write ( _T ( "Properties" ), Props );

      //    Points
      for ( int ip=1 ; ip < pr->GetnPoints() +1 ; ip++ )
      {
            str_buf.Printf ( _T ( "RoutePointID%d" ), ip );
            RoutePoint *prp = pr->GetPoint ( ip );
            Write ( str_buf, prp->m_GUID );
      }

      for ( int ip1=1 ; ip1 < pr->GetnPoints() +1 ; ip1++ )
      {
            RoutePoint *prp = pr->GetPoint ( ip1 );
            UpdateWayPoint ( prp );
      }

      Flush();

      pr->m_ConfigRouteNum = acrm;

      if ( crm == -1 )
            m_NextRouteNum +=1;             // auto increment for next time

      return true;
}


bool MyConfig::UpdateRoute ( Route *pr )
{
      if ( pr->m_bIsTrack )
            return false;

      wxString str_buf;

//    Build the Group Name
      wxString t ( _T ( "/Routes/RouteDefn" ) );
      str_buf.Printf ( _T ( "%d" ), pr->m_ConfigRouteNum );
      t.Append ( str_buf );

      DeleteGroup ( t );

      AddNewRoute ( pr, pr->m_ConfigRouteNum );

      return true;
}


bool MyConfig::DeleteConfigRoute ( Route *pr )
{
      wxString str_buf;
      assert ( pr->m_ConfigRouteNum );

//    Build the Group Name
      wxString t ( _T ( "/Routes/RouteDefn" ) );
      str_buf.Printf ( _T ( "%d" ), pr->m_ConfigRouteNum );
      t.Append ( str_buf );

      DeleteGroup ( t );

      Flush();

      return true;
}


bool MyConfig::AddNewWayPoint ( RoutePoint *pWP, int crm )
{
      wxString str_buf;
      int acrm;

      if ( crm != -1 )
            acrm = crm;
      else
            acrm = m_NextWPNum;

//    Build the Group Name
      wxString t ( _T ( "/Marks/MarkDefn" ) );
      str_buf.Printf ( _T ( "%d" ), acrm );
      t.Append ( str_buf );

      SetPath ( t );

//          add the GUID here
      str_buf.Printf ( _T ( "RoutePoint" ) );
      wxString str_buf1;
      str_buf1.Printf ( _T ( "%f,%f" ), pWP->m_lat, pWP->m_lon );
      Write ( str_buf, str_buf1 );

      str_buf.Printf ( _T ( "RoutePointName" ) );
      Write ( str_buf, pWP->m_MarkName );

      str_buf.Printf ( _T ( "RoutePointIcon" ) );
      Write ( str_buf, pWP->m_IconName );

      str_buf.Printf ( _T ( "RoutePointGUID" ) );
      Write ( str_buf, pWP->m_GUID );

      str_buf.Printf ( _T ( "RoutePointProp" ) );
      str_buf1 = pWP->CreatePropString();
      Write ( str_buf, str_buf1 );

      str_buf.Printf ( _T ( "RoutePointNameLocationOffset" ) );
      str_buf1.Printf ( _T ( "%d,%d" ), pWP->m_NameLocationOffsetX, pWP->m_NameLocationOffsetY );
      Write ( str_buf, str_buf1 );

      // toh, 2009.02.23
      if( pWP->m_HyperlinkList)
      {
            int NbrLinks = pWP->m_HyperlinkList->GetCount();
            if ( NbrLinks > 0 )
            {
                  wxHyperlinkListNode *linknode = pWP->m_HyperlinkList->GetFirst();

                  int i=1;
                  while ( linknode )
                  {
                        Hyperlink *link = linknode->GetData();
                        wxString Link = link->Link;
                        wxString Descr = link->DescrText;
                        linknode = linknode->GetNext();

                        wxString t ( _T ( "RoutePointLink" ) );
                        str_buf.Printf ( _T ( "%d" ), i );
                        t.Append ( str_buf );

                        str_buf1 = _T ( "" );
                        str_buf1.Append ( link->Link );
                        if ( link->DescrText.Length() > 0 )
                        {
                              str_buf1.Append ( _T ( "^" ) );
                              str_buf1.Append ( link->DescrText );
                        }
                        if ( link->Type.Length() > 0 )
                        {
                              str_buf1.Append ( _T ( "^" ) );
                              str_buf1.Append ( link->Type );
                        }
                        Write ( t, str_buf1 );
                        i++;
                  }
            }
      }

      Flush();

      pWP->m_ConfigWPNum = acrm;

      if ( crm == -1 )
            m_NextWPNum +=1;             // auto increment for next time

      return true;
}


bool MyConfig::UpdateWayPoint ( RoutePoint *pWP )
{
      wxString str_buf;

//    Build the Group Name
      wxString t ( _T ( "/Marks/MarkDefn" ) );
      str_buf.Printf ( _T ( "%d" ), pWP->m_ConfigWPNum );
      t.Append ( str_buf );

      DeleteGroup ( t );

      AddNewWayPoint ( pWP, pWP->m_ConfigWPNum );

      return true;
}


bool MyConfig::DeleteWayPoint ( RoutePoint *pWP )
{
      wxString str_buf;

//      assert(pWP->m_ConfigWPNum);

//    Build the Group Name
      wxString t ( _T ( "/Marks/MarkDefn" ) );
      str_buf.Printf ( _T ( "%d" ), pWP->m_ConfigWPNum );
      t.Append ( str_buf );

      DeleteGroup ( t );

      Flush();

      return true;
}


bool MyConfig::UpdateChartDirs ( ArrayOfCDI& dir_array )
{
      wxString key, dir;
      wxString str_buf;

      SetPath ( _T ( "/ChartDirectories" ) );
      int iDirMax = GetNumberOfEntries();
      if ( iDirMax )
      {

            long dummy;

            for ( int i=0 ; i<iDirMax ; i++ )
            {
                  GetFirstEntry ( key, dummy );
                  DeleteEntry ( key, false );
            }
      }

      iDirMax = dir_array.GetCount();

      for ( int iDir = 0 ; iDir <iDirMax ; iDir++ )
      {
            ChartDirInfo cdi = dir_array.Item ( iDir );

            wxString dirn = cdi.fullpath;
            dirn.Append(_T("^"));
            dirn.Append(cdi.magic_number);

            str_buf.Printf ( _T ( "ChartDir%d" ), iDir+1 );

            Write ( str_buf, dirn );

      }

      Flush();
      return true;
}



void MyConfig::UpdateSettings()
{
//    Global options and settings
      SetPath ( _T ( "/Settings" ) );

      Write ( _T ( "ShowDebugWindows" ), m_bShowDebugWindows );
      Write ( _T ( "ShowPrintIcon" ), g_bShowPrintIcon );
      Write ( _T ( "SetSystemTime" ), s_bSetSystemTime );
      Write ( _T ( "ShowDepthUnits" ), g_bShowDepthUnits );
      Write ( _T ( "AutoAnchorDrop" ),  g_bAutoAnchorMark );
      Write ( _T ( "ShowChartOutlines" ),  g_bShowOutlines );
      Write ( _T ( "GarminPersistance" ),  g_bGarminPersistance );

      Write ( _T ( "CM93DetailFactor" ),  g_cm93_zoom_factor );
      Write ( _T ( "CM93DetailZoomPosX" ),  g_cm93detail_dialog_x );
      Write ( _T ( "CM93DetailZoomPosY" ),  g_cm93detail_dialog_y );
      Write ( _T ( "ShowCM93DetailSlider" ), g_bShowCM93DetailSlider );
      Write ( _T ( "AllowExtremeOverzoom" ), g_b_overzoom_x );

      Write ( _T ( "ShowGRIBIcon" ), g_bShowGRIBIcon );
      Write ( _T ( "GRIBUseHiDef" ), g_bGRIBUseHiDef );

      Write ( _T ( "GRIBDialogSizeX" ),  g_grib_dialog_sx );
      Write ( _T ( "GRIBDialogSizeY" ),  g_grib_dialog_sy );
      Write ( _T ( "GRIBDialogPosX" ),   g_grib_dialog_x );
      Write ( _T ( "GRIBDialogPosY" ),   g_grib_dialog_y );

      Write ( _T ( "NMEALogWindowSizeX" ),  g_NMEALogWindow_sx );
      Write ( _T ( "NMEALogWindowSizeY" ),  g_NMEALogWindow_sy );
      Write ( _T ( "NMEALogWindowPosX" ),   g_NMEALogWindow_x );
      Write ( _T ( "NMEALogWindowPosY" ),   g_NMEALogWindow_y );

      Write ( _T ( "PreserveScaleOnX" ),   g_bPreserveScaleOnX );

      Write ( _T ( "StartWithTrackActive" ),   g_bTrackCarryOver );

      wxString st0;
      st0.Printf ( _T ( "%g" ), g_PlanSpeed );
      Write ( _T ( "PlanSpeed" ), st0 );

      Write ( _T ( "Locale" ), g_locale );


//    S57 Object Filter Settings

      SetPath ( _T ( "/Settings/ObjectFilter" ) );

#ifdef USE_S57
      if ( ps52plib )
      {
            for ( unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++ )
            {
                  OBJLElement *pOLE = ( OBJLElement * ) ( ps52plib->pOBJLArray->Item ( iPtr ) );

                  wxString st1 ( _T ( "viz" ) );
                  st1.Append ( wxString ( pOLE->OBJLName,  wxConvUTF8 ) );
                  Write ( st1, pOLE->nViz );
            }
      }
#endif

//    Global State

      SetPath ( _T ( "/Settings/GlobalState" ) );

      wxString st1;

      if ( cc1 && cc1->VPoint.bValid )
      {
            st1.Printf ( _T ( "%10.4f,%10.4f" ), cc1->VPoint.clat, cc1->VPoint.clon );
            Write ( _T ( "VPLatLon" ), st1 );
            st1.Printf ( _T ( "%g" ), cc1->VPoint.view_scale_ppm );
            Write ( _T ( "VPScale" ), st1 );
      }

      st1.Printf ( _T ( "%10.4f, %10.4f" ), gLat, gLon );
      Write ( _T ( "OwnShipLatLon" ), st1 );

      //    Various Options
      SetPath ( _T ( "/Settings/GlobalState" ) );
      if(cc1)
		  Write ( _T ( "bFollow" ), cc1->m_bFollow );
      Write ( _T ( "nColorScheme" ), ( int ) gFrame->GetColorScheme() );

      Write ( _T ( "FrameWinX" ), g_nframewin_x );
      Write ( _T ( "FrameWinY" ), g_nframewin_y );
      Write ( _T ( "FrameMax" ),  g_bframemax );

      //    AIS
      SetPath ( _T ( "/Settings/AIS" ) );

      Write ( _T ( "bNoCPAMax" ), g_bCPAMax );
      Write ( _T ( "NoCPAMaxNMi" ),  g_CPAMax_NM );
      Write ( _T ( "bCPAWarn" ), g_bCPAWarn );
      Write ( _T ( "CPAWarnNMi" ),  g_CPAWarn_NM );
      Write ( _T ( "bTCPAMax" ), g_bTCPA_Max );
      Write ( _T ( "TCPAMaxMinutes" ),  g_TCPA_Max );
      Write ( _T ( "bMarkLostTargets" ), g_bMarkLost );
      Write ( _T ( "MarkLost_Minutes" ),  g_MarkLost_Mins );
      Write ( _T ( "bRemoveLostTargets" ), g_bRemoveLost );
      Write ( _T ( "RemoveLost_Minutes" ),  g_RemoveLost_Mins );
      Write ( _T ( "bShowCOGArrows" ), g_bShowCOG );
      Write ( _T ( "CogArrowMinutes" ),  g_ShowCOG_Mins );
      Write ( _T ( "bShowTargetTracks" ), g_bShowTracks );
      Write ( _T ( "TargetTracksMinutes" ),  g_ShowTracks_Mins );
      Write ( _T ( "bShowMooredTargets" ), g_bShowMoored );
      Write ( _T ( "MooredTargetMaxSpeedKnots" ),  g_ShowMoored_Kts );
      Write ( _T ( "bAISAlertDialog" ), g_bAIS_CPA_Alert );
      Write ( _T ( "bAISAlertAudio" ), g_bAIS_CPA_Alert_Audio );
      Write ( _T ( "AISAlertAudioFile" ),  g_sAIS_Alert_Sound_File );
      Write ( _T ( "bAISAlertSuppressMoored" ),  g_bAIS_CPA_Alert_Suppress_Moored );

      Write ( _T ( "AlertDialogSizeX" ),  g_ais_alert_dialog_sx );
      Write ( _T ( "AlertDialogSizeY" ),  g_ais_alert_dialog_sy );
      Write ( _T ( "AlertDialogPosX" ),  g_ais_alert_dialog_x );
      Write ( _T ( "AlertDialogPosY" ),  g_ais_alert_dialog_y );
      Write ( _T ( "QueryDialogPosX" ),  g_ais_query_dialog_x );
      Write ( _T ( "QueryDialogPosY" ),  g_ais_query_dialog_y );


#ifdef USE_S57
      SetPath ( _T ( "/Settings/GlobalState" ) );
      Write ( _T ( "bShowS57Text" ), ps52plib->GetShowS57Text() );
      Write ( _T ( "bShowS57ImportantTextOnly" ), ps52plib->GetShowS57ImportantTextOnly() );
      Write ( _T ( "nDisplayCategory" ), ( long ) ps52plib->m_nDisplayCategory );
      Write ( _T ( "nSymbolStyle" ), ( int ) ps52plib->m_nSymbolStyle );
      Write ( _T ( "nBoundaryStyle" ), ( int ) ps52plib->m_nBoundaryStyle );

      Write ( _T ( "bShowSoundg" ), ps52plib->m_bShowSoundg );
      Write ( _T ( "bShowMeta" ), ps52plib->m_bShowMeta );
      Write ( _T ( "bUseSCAMIN" ), ps52plib->m_bUseSCAMIN );
      Write ( _T ( "bShowAtonText" ), ps52plib->m_bShowAtonText );
      Write ( _T ( "bShowLightDescription" ), ps52plib->m_bShowLdisText );
      Write ( _T ( "bDeClutterText" ), ps52plib->m_bDeClutterText );

      Write ( _T ( "S52_MAR_SAFETY_CONTOUR" ), S52_getMarinerParam ( S52_MAR_SAFETY_CONTOUR ) );
      Write ( _T ( "S52_MAR_SHALLOW_CONTOUR" ), S52_getMarinerParam ( S52_MAR_SHALLOW_CONTOUR ) );
      Write ( _T ( "S52_MAR_DEEP_CONTOUR" ), S52_getMarinerParam ( S52_MAR_DEEP_CONTOUR ) );
      Write ( _T ( "S52_MAR_TWO_SHADES" ), S52_getMarinerParam ( S52_MAR_TWO_SHADES ) );
      Write ( _T ( "S52_DEPTH_UNIT_SHOW" ), ps52plib->m_nDepthUnitDisplay );

      SetPath ( _T ( "/Directories" ) );
      Write ( _T ( "S57DataLocation" ), *g_pcsv_locn );
      Write ( _T ( "SENCFileLocation" ), *g_pSENCPrefix );
      Write ( _T ( "PresentationLibraryData" ), g_PresLibData );
      Write ( _T ( "CM93DictionaryLocation" ), g_CM93DictDir );

#endif

      SetPath ( _T ( "/Directories" ) );
      Write ( _T ( "InitChartDir" ), *pInit_Chart_Dir );
      Write ( _T ( "GPXIODir" ), m_gpx_path );
      Write ( _T ( "GRIBDirectory" ), g_grib_dir );


      if ( g_pnmea )
      {
            SetPath ( _T ( "/Settings/NMEADataSource" ) );
            wxString source;
            g_pnmea->GetSource ( source );
            Write ( _T ( "Source" ), source );
      }

      if ( pAPilot )
      {
            SetPath ( _T ( "/Settings/NMEAAutoPilotPort" ) );
            wxString ap_port;
            pAPilot->GetAP_Port ( ap_port );
            Write ( _T ( "Port" ), ap_port );
      }

      SetPath ( _T ( "/Settings/WiFiServer" ) );
      Write ( _T ( "Server" ), *pWIFIServerName );


      if ( g_pAIS )
      {
            SetPath ( _T ( "/Settings/AISPort" ) );
            wxString ais_port;
            g_pAIS->GetSource ( ais_port );
            Write ( _T ( "Port" ), ais_port );
      }


//    Fonts
#ifdef __WXX11__
      SetPath ( _T ( "/Settings/X11Fonts" ) );
#endif

#ifdef __WXGTK__
      SetPath ( _T ( "/Settings/GTKFonts" ) );
#endif

#ifdef __WXMSW__
      SetPath ( _T ( "/Settings/MSWFonts" ) );
#endif

#ifdef __WXMAC__
      SetPath ( _T ( "/Settings/MacFonts" ) );
#endif

      int nFonts = pFontMgr->GetNumFonts();

      for ( int i=0 ; i<nFonts ; i++ )
      {
            wxString cfstring ( *pFontMgr->GetConfigString ( i ) );

/*
            wxString valstring ( *pFontMgr->GetDialogString ( i ) );
            valstring.Append ( _T ( ":" ) );
            valstring.Append ( *pFontMgr->GetNativeDesc ( i ) );
*/
            wxString valstring = pFontMgr->GetFullConfigDesc ( i );
            Write ( cfstring, valstring );
      }


      SetPath ( _T ( "/Settings/Others" ) );
      Write ( _T ( "ShowGPXIcons" ), g_bShowGPXIcons );

      // Radar rings; toh, 2009.02.24
      Write ( _T ( "ShowRadarRings" ), g_bNavAidShowRadarRings );
      Write ( _T ( "RadarRingsNumberVisible" ), g_iNavAidRadarRingsNumberVisible );
      Write ( _T ( "RadarRingsStep" ), g_fNavAidRadarRingsStep );
      Write ( _T ( "RadarRingsStepUnits" ), g_pNavAidRadarRingsStepUnits );

      // Waypoint dragging with mouse; toh, 2009.02.24
      Write ( _T ( "WaypointPreventDragging" ), g_bWayPointPreventDragging );

      Write ( _T ( "EnableZoomToCursor" ), g_bEnableZoomToCursor );

      Write ( _T ( "ShowTrackIcon" ), g_bShowTrackIcon );
      Write ( _T ( "TrackIntervalSeconds" ),g_TrackIntervalSeconds );
      Write ( _T ( "TrackDeltaDistance" ),g_TrackDeltaDistance );
      Write ( _T ( "EnableTrackByTime" ), g_bTrackTime );
      Write ( _T ( "EnableTrackByDistance" ), g_bTrackDistance );

      Flush();


      //    Create the NavObjectCollection, and save to specified file

      NavObjectCollection *pNavObjectSet = new NavObjectCollection( _T ( "gpx" ), _T ( "1.0" ), _T ( "opencpn" ) );

      pNavObjectSet->CreateGPXPoints();
      pNavObjectSet->CreateGPXRoutes();
      pNavObjectSet->CreateGPXTracks();

      pNavObjectSet->Save ( m_sNavObjSetFile, 4 );

      delete pNavObjectSet;

}

bool MyConfig::ExportGPXRoute ( wxWindow* parent, Route *pRoute )
{

      wxFileDialog saveDialog( parent, wxT ( "Export GPX file" ), m_gpx_path, wxT ( "" ),
                  wxT ( "GPX files (*.gpx)|*.gpx" ), wxFD_SAVE );

      int response = saveDialog.ShowModal();

      wxString path = saveDialog.GetPath();
      wxFileName fn ( path );
      m_gpx_path = fn.GetPath();

      if ( response == wxID_OK )
      {
            fn.SetExt ( _T ( "gpx" ) );

            if(wxFileExists(fn.GetFullPath()))
            {
                  int answer = wxMessageBox(_T("Overwrite existing file?"), _T("Confirm"),
                                            wxICON_QUESTION | wxYES_NO | wxCANCEL);
                  if (answer != wxYES)
                        return false;
            }

            CreateExportGPXNavObj();

            // TODO this is awkward
            if ( !pRoute->m_bIsTrack )
                  CreateGPXRoute ( pRoute );
            else
            {
                  wxXmlNode *track_node = CreateGPXTrackStatic ( pRoute );
                  m_XMLrootnode->AddChild ( track_node );
//                  CreateGPXTrack ( pRoute );
            }

            WriteXMLNavObj ( fn.GetFullPath() );
            return true;
      }
      else
            return false;
}




void MyConfig::ExportGPX ( wxWindow* parent )
{

      wxFileDialog saveDialog( parent, wxT ( "Export GPX file" ), m_gpx_path, wxT ( "" ),
                  wxT ( "GPX files (*.gpx)|*.gpx" ), wxFD_SAVE );

      int response = saveDialog.ShowModal();

      wxString path = saveDialog.GetPath();
      wxFileName fn ( path );
      m_gpx_path = fn.GetPath();

      if ( response == wxID_OK )
      {

            fn.SetExt ( _T ( "gpx" ) );

            if(wxFileExists(fn.GetFullPath()))
            {
                  int answer = wxMessageBox(_T("Overwrite existing file?"), _T("Confirm"),
                                            wxICON_QUESTION | wxYES_NO | wxCANCEL);
                  if (answer != wxYES)
                        return;
            }

            CreateExportGPXNavObj();
            CreateGPXWayPoints();
            CreateGPXRoutes();
            CreateGPXTracks();
            WriteXMLNavObj ( fn.GetFullPath() );
      }
}


void MyConfig::ImportGPX ( wxWindow* parent )
{

      wxFileDialog openDialog( parent, wxT ( "Import GPX file" ), m_gpx_path, wxT ( "" ),
                  wxT ( "GPX files (*.gpx)|*.gpx|All files (*.*)|*.*" ), wxFD_OPEN );
      int response = openDialog.ShowModal();

      wxFileName fn ( openDialog.GetPath() );
      m_gpx_path = fn.GetPath();

      if ( response == wxID_OK )
      {
            wxString path = openDialog.GetPath();

            if ( ::wxFileExists ( path ) )
            {
                  wxXmlDocument *pXMLNavObj = new wxXmlDocument;
                  if ( pXMLNavObj->Load ( path ) )
                  {
                        wxXmlNode *root = pXMLNavObj->GetRoot();

                        wxString RootName = root->GetName();
                        if ( RootName == _T ( "gpx" ) )
                        {
                              wxString RootContent = root->GetNodeContent();

                              wxXmlNode *child = root->GetChildren();
                              while ( child )
                              {
                                    wxString ChildName = child->GetName();
                                    if ( ChildName == _T ( "wpt" ) )
                                    {
                                          bool WpExists;
                                          GPXLoadWaypoint ( child,WpExists );
                                    }
                                    if ( ChildName == _T ( "rte" ) )
                                    {
                                          GPXLoadRoute ( child );
                                    }
                                    if ( ChildName == _T ( "trk" ) )
                                    {
                                                ::GPXLoadTrack ( child );
                                    }
                                    child = child->GetNext();
                              }
                        }
                  }
            }
      }
}

// toh, 2009.02.17
RoutePoint *MyConfig::GPXLoadWaypoint ( wxXmlNode* wptnode,bool &WpExists, bool LoadingRoute )
{
      wxString LatString = wptnode->GetPropVal ( _T ( "lat" ),_T ( "0.0" ) );
      wxString LonString = wptnode->GetPropVal ( _T ( "lon" ),_T ( "0.0" ) );

      wxString SymString  = _T ( "circle" );                // default icon
      wxString NameString = _T ( "" );
      wxString DescString = _T ( "" );
      wxString TypeString = _T ( "" );
      wxString ChildName  = _T ( "" );
      wxString PropString = _T ( "" );

      HyperlinkList *linklist = new HyperlinkList;

      wxString HrefString = _T ( "" );
      wxString HrefTextString = _T ( "" );
      wxString HrefTypeString = _T ( "" );

      wxXmlNode *child = wptnode->GetChildren();
      while ( child )
      {
            ChildName = child->GetName();
            if ( ChildName == _T ( "sym" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        SymString = child1->GetContent();
            }
            if ( ChildName == _T ( "name" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        NameString = child1->GetContent();
            }
            if ( ChildName == _T ( "desc" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        DescString = child1->GetContent();
            }
            if ( ChildName == _T ( "type" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        TypeString = child1->GetContent();
            }
            if ( ChildName == _T ( "prop" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        PropString = child1->GetContent();
            }

            // Read hyperlink
            if ( ChildName == _T ( "link" ) )
            {
                  HrefString = child->GetPropVal ( _T ( "href" ),_T ( "" ) );

                  wxXmlNode *child1 = child->GetChildren();
                  while ( child1 )
                  {
                        wxString LinkString = child1->GetName();

                        if ( LinkString == _T ( "text" ) )
                        {
                              wxXmlNode *child1a = child1->GetChildren();
                              HrefTextString = child1a->GetContent();
                        }

                        if ( LinkString == _T ( "type" ) )
                        {
                              wxXmlNode *child1a = child1->GetChildren();
                              HrefTypeString = child1a->GetContent();
                        }
                        child1 = child1->GetNext();
                  }

                  Hyperlink *link = new Hyperlink;
                  link->Link = HrefString;
                  link->DescrText = HrefTextString;
                  link->Type = HrefTypeString;
                  linklist->Append ( link );
            }

            child = child->GetNext();
      }

      // Create waypoint
      double rlat;
      double rlon;
      LatString.ToDouble ( &rlat );
      LonString.ToDouble ( &rlon );

      // If WP already exists it mustn't be added again
      wxRoutePointListNode *node = pWayPointMan->m_pWayPointList->GetFirst();

      RoutePoint *pWP;
      WpExists = false;
      while ( node )
      {
            RoutePoint *pr = node->GetData();

            if ( NameString == pr->m_MarkName )
            {
                  if ( fabs ( rlat-pr->m_lat ) < 1.e-6 && fabs ( rlon-pr->m_lon ) < 1.e-6 )
                  {
                        WpExists = true;
                        pWP = pr;
                        break;
                  }
            }
            node = node->GetNext();
      }

      if ( !WpExists )
      {
            pWP = new RoutePoint ( rlat, rlon, SymString, NameString );

            pWP->SetPropFromString ( PropString );

            pWP->m_NameLocationOffsetX = -10;
            pWP->m_NameLocationOffsetY = 8;

            delete pWP->m_HyperlinkList;
            pWP->m_HyperlinkList = linklist;

            if ( !LoadingRoute )
            {
                  pWP->m_bIsolatedMark = true;                      // This is an isolated mark

                  pConfig->AddNewWayPoint ( pWP,m_NextWPNum );   // use auto next num
                  pSelect->AddSelectableRoutePoint ( rlat, rlon, pWP );
                  pWP->m_ConfigWPNum = m_NextWPNum;
                  m_NextWPNum++;
            }
      }

      return ( pWP );
}

// toh, 2009.02.17
void MyConfig::GPXLoadRoute ( wxXmlNode* rtenode )
{
      int routenum = m_NextRouteNum;

      wxString Name = rtenode->GetName();
      wxString RouteName = rtenode->GetPropVal ( _T ( "name" ),_T ( "N.N." ) );

      if ( Name == _T ( "rte" ) )
      {
            Route *pTentRoute = new Route();

            pTentRoute->m_RouteNameString = RouteName;

            wxXmlNode *child = rtenode->GetChildren();
            int ip = 0;

            while ( child )
            {
                  wxString ChildName = child->GetName();
                  if ( ChildName == _T ( "rtept" ) )
                  {
                        bool WpExists;
                        RoutePoint *pWp = GPXLoadWaypoint ( child, WpExists, true );

                        pTentRoute->AddPoint ( pWp, false );                      // don't auto-rename numerically
                        if ( !WpExists )
                              pWp->m_ConfigWPNum = 1000 + ( routenum * 100 ) + ip;  // dummy mark number
                        ip++;
                  }
                  child = child->GetNext();
            }

            //    Search for an identical route already in place.  If found, discard this one

            bool  routeExists = false;
            wxRouteListNode *route_node = pRouteList->GetFirst();
            while ( route_node )
            {
                  Route *proute = route_node->GetData();

                  if ( proute->IsEqualTo ( pTentRoute ) )
                  {
                        routeExists = true;
                        break;
                  }
                  route_node = route_node->GetNext();                         // next route
            }

//    TODO  All this trouble for a tentative route.......Should make some Route methods????
            if ( !routeExists )
            {
                  pRouteList->Append ( pTentRoute );
                  pConfig->AddNewRoute ( pTentRoute,routenum );   // use auto next num
                  pTentRoute->m_ConfigRouteNum = routenum;
                  m_NextRouteNum = routenum + 1;

                  pConfig->UpdateRoute ( pTentRoute );
                  pTentRoute->RebuildGUIDList();                  // ensure the GUID list is intact

                  //    Add the selectable points and segments

                  int ip = 0;
                  float prev_rlat, prev_rlon;
                  RoutePoint *prev_pConfPoint;

                  wxRoutePointListNode *node = pTentRoute->pRoutePointList->GetFirst();
                  while ( node )
                  {

                        RoutePoint *prp = node->GetData();

                        pSelect->AddSelectableRoutePoint ( prp->m_lat,prp->m_lon, prp );

                        if ( ip )
                              pSelect->AddSelectableRouteSegment ( prev_rlat, prev_rlon, prp->m_lat, prp->m_lon,prev_pConfPoint, prp, pTentRoute );

                        prev_rlat = prp->m_lat;
                        prev_rlon = prp->m_lon;
                        prev_pConfPoint = prp;

                        ip++;

                        node = node->GetNext();
                  }
            }
            else
            {

                  // walk the route, deleting points used only by this route
                  wxRoutePointListNode *pnode = ( pTentRoute->pRoutePointList )->GetFirst();
                  while ( pnode )
                  {
                        RoutePoint *prp = pnode->GetData();

                        // check all other routes to see if this point appears in any other route
                        Route *pcontainer_route = pRouteMan->FindRouteContainingWaypoint ( prp );

                        if ( pcontainer_route == NULL )
                        {
                              prp->m_bIsInRoute = false;          // Take this point out of this (and only) route
                              if ( !prp->m_bKeepXRoute )
                              {
                                    pConfig->DeleteWayPoint ( prp );
                                    delete prp;
                              }
                        }

                        pnode = pnode->GetNext();
                  }

                  delete pTentRoute;
            }
      }
}


#if 0
void MyConfig::GPXLoadTrack ( wxXmlNode* trknode )
{
//      int routenum = m_NextRouteNum;

      //    Tentatively take the Track name from the Property "name"
      //    May be overridden later by child <name>..</name>
      wxString RouteName = trknode->GetPropVal ( _T ( "name" ),_T ( "N.N." ) );

      wxString Name = trknode->GetName();
      if ( Name == _T ( "trk" ) )
      {
            Track *pTentTrack = new Track();

            wxXmlNode *tschild = trknode->GetChildren();

            RoutePoint *pRecentPoint = NULL;
            RoutePoint *pWp = NULL;

            while ( tschild )
            {
                  wxString ChildName = tschild->GetName();
                  if ( ChildName == _T ( "trkseg" ) )
                  {
                        //    Official GPX spec calls for trkseg to have children trkpt
                        wxXmlNode *tpchild = tschild->GetChildren();
                        if(tpchild)
                        {
                              while(tpchild)
                              {
                                    wxString tpChildName = tpchild->GetName();
                                    if(tpChildName == _T("trkpt"))
                                    {
                                          pWp = LoadGPXTrackpoint ( tpchild );


                              //    Don't add this point if it is geographically the same as the previous point
                                          if(pRecentPoint)
                                          {
                                                if((pRecentPoint->m_lat != pWp->m_lat) || (pRecentPoint->m_lon != pWp->m_lon))
                                                      pTentTrack->AddPoint ( pWp, false );                      // don't auto-rename numerically

                                          }
                                          else
                                                pTentTrack->AddPoint ( pWp, false );                      // add first point always

                                          pRecentPoint = pWp;
                                    }

                                    //          This else clause loads opencpn tracks exported prior to v1.3.5 Build 1122
                                    //          and can go away after release of 1.3.6
                                    else
                                    {
                                          pWp = LoadGPXTrackpoint ( tschild );

                              //    Don't add this point if it is geographically the same as the previous point
                                          if(pRecentPoint)
                                          {
                                                if((pRecentPoint->m_lat != pWp->m_lat) || (pRecentPoint->m_lon != pWp->m_lon))
                                                      pTentTrack->AddPoint ( pWp, false );                      // don't auto-rename numerically

                                          }
                                          else
                                                pTentTrack->AddPoint ( pWp, false );                      // add first point always

                                          pRecentPoint = pWp;
                                    }


                                    tpchild = tpchild->GetNext();

                              }
                        }
                  }
                  else if ( ChildName == _T ( "name" ) )
                  {
                        wxXmlNode *child1 = tschild->GetChildren();
                        if( child1 )                                    // name will always be in first child??
                               RouteName = child1->GetContent();
                  }

                  tschild = tschild->GetNext();

            }

            pTentTrack->m_RouteNameString = RouteName;

            //    Search for an identical route/track already in place.  If found, discard this one

            bool  bAddtrack = true;
            wxRouteListNode *route_node = pRouteList->GetFirst();
            while ( route_node )
            {
                  Route *proute = route_node->GetData();

                  if ( proute->IsEqualTo ( pTentTrack ) )
                  {
                        bAddtrack = false;
                        break;
                  }
                  route_node = route_node->GetNext();                         // next route
            }

            //    If the track has only 1 point, don't load it.
            //    This usually occurs if some points were dscarded above as being co-incident.
            if(pTentTrack->GetnPoints() < 2)
                  bAddtrack = false;

//    TODO  All this trouble for a tentative route.......Should make some Route methods????
            if ( bAddtrack )
            {
                  pRouteList->Append ( pTentTrack );

                  //    Add the selectable points and segments

                  int ip = 0;
                  float prev_rlat, prev_rlon;
                  RoutePoint *prev_pConfPoint;

                  wxRoutePointListNode *node = pTentTrack->pRoutePointList->GetFirst();
                  while ( node )
                  {

                        RoutePoint *prp = node->GetData();

                        if ( ip )
                              pSelect->AddSelectableRouteSegment ( prev_rlat, prev_rlon, prp->m_lat, prp->m_lon,prev_pConfPoint, prp, pTentTrack );

                        prev_rlat = prp->m_lat;
                        prev_rlon = prp->m_lon;
                        prev_pConfPoint = prp;

                        ip++;

                        node = node->GetNext();
                  }
            }
            else
            {

                  // walk the route, deleting points used only by this route
                  wxRoutePointListNode *pnode = ( pTentTrack->pRoutePointList )->GetFirst();
                  while ( pnode )
                  {
                        RoutePoint *prp = pnode->GetData();

                        // check all other routes to see if this point appears in any other route
                        Route *pcontainer_route = pRouteMan->FindRouteContainingWaypoint ( prp );

                        if ( pcontainer_route == NULL )
                        {
                              prp->m_bIsInRoute = false;          // Take this point out of this (and only) track/route
                              if ( !prp->m_bKeepXRoute )
                              {
                                    pConfig->DeleteWayPoint ( prp );
                                    delete prp;
                              }
                        }

                        pnode = pnode->GetNext();
                  }

                  delete pTentTrack;
            }
      }
}

#endif


//---------------------------------------------------------------------------------
//    GPX XML Support for Navigation Objects
//---------------------------------------------------------------------------------

void MyConfig::CreateExportGPXNavObj ( void )
{
      m_pXMLNavObj = new wxXmlDocument;
      m_XMLrootnode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "gpx" ) );
      m_pXMLNavObj->SetRoot ( m_XMLrootnode );

      m_XMLrootnode->AddProperty ( _T ( "version" ),_T ( "1.1" ) );
      m_XMLrootnode->AddProperty ( _T ( "creator" ),_T ( "OpenCPN" ) );
      m_XMLrootnode->AddProperty( _T ( "xmlns:xsi" ), _T("http://www.w3.org/2001/XMLSchema-instance") );
      m_XMLrootnode->AddProperty( _T ( "xmlns" ), _T("http://www.topografix.com/GPX/1/1") );
      m_XMLrootnode->AddProperty( _T ( "xsi:schemaLocation" ), _T("http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd") );

}


void MyConfig::CreateGPXWayPoints ( void )
{
      //    Iterate on the RoutePoint list
      // If a waypoint is also in the route, it mustn't be written

      wxRoutePointListNode *node = pWayPointMan->m_pWayPointList->GetFirst();

      RoutePoint *pr;
      wxXmlNode *prev_node;

      bool IsFirst = true;
      while ( node )
      {
            pr = node->GetData();

            if ( !WptIsInRouteList ( pr ) )
            {
                  wxXmlNode *mark_node = CreateGPXWptNode ( pr );

                  if ( IsFirst )
                  {
                        IsFirst = false;
                        m_XMLrootnode->AddChild ( mark_node );
                  }
                  else
                        prev_node->SetNext ( mark_node );

                  prev_node = mark_node;
            }
            node = node->GetNext();
      }
}


void MyConfig::CreateGPXRoutes ( void )
{
      // Routes
      wxRouteListNode *node1 = pRouteList->GetFirst();
      while ( node1 )
      {
            Route *pRoute = node1->GetData();
            if ( !pRoute->m_bIsTrack )
                  CreateGPXRoute ( pRoute );

            node1 = node1->GetNext();
      }
}

void MyConfig::CreateGPXTracks ( void )
{
      // Routes
      wxRouteListNode *node1 = pRouteList->GetFirst();
      while ( node1 )
      {
            Route *pRoute = node1->GetData();
            if ( pRoute->m_bIsTrack )
            {
                  wxXmlNode *track_node = ::CreateGPXTrackStatic ( pRoute );
                  m_XMLrootnode->AddChild ( track_node );
            }
            node1 = node1->GetNext();
      }
}





void MyConfig::CreateGPXRoute ( Route *pRoute )
{
      wxXmlNode *GPXRte_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "rte" ) );
      m_XMLrootnode->AddChild ( GPXRte_node );



/*      GPXRte_node->AddProperty ( _T ( "name" ),pRoute->m_RouteNameString );
      wxString strnum;
      strnum.Printf ( _T ( "%d" ),pRoute->m_ConfigRouteNum );
      GPXRte_node->AddProperty ( _T ( "number" ),strnum );
*/

      //  or
      wxXmlNode *node;
      wxXmlNode *tnode;

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      GPXRte_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pRoute->m_RouteNameString );
      node->AddChild ( tnode );

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "number" ) );
      GPXRte_node->AddChild ( node );
      wxString strnum;
      strnum.Printf ( _T ( "%d" ),pRoute->m_ConfigRouteNum );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), strnum );
      node->AddChild ( tnode );
      //


      RoutePointList *pRoutePointList = pRoute->pRoutePointList;

      wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
      RoutePoint *prp;

      int i=1;
      while ( node2 )
      {
            prp = node2->GetData();

            wxXmlNode *rpt_node = CreateGPXRptNode ( prp,i+1 );
            GPXRte_node->AddChild ( rpt_node );

            node2=node2->GetNext();
            i++;
      }
}

#if 0
void MyConfig::CreateGPXTrack ( Route *pRoute )
{

      wxXmlNode *GPXTrk_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "trk" ) );
      m_XMLrootnode->AddChild ( GPXTrk_node );


      wxXmlNode *node;
      wxXmlNode *tnode;

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      GPXTrk_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pRoute->m_RouteNameString );
      node->AddChild ( tnode );

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "number" ) );
      GPXTrk_node->AddChild ( node );
      wxString strnum;
      strnum.Printf ( _T ( "%d" ),pRoute->m_ConfigRouteNum );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), strnum );
      node->AddChild ( tnode );

      wxXmlNode *trkseg_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "trkseg" ) );
      GPXTrk_node->AddChild ( trkseg_node );


      RoutePointList *pRoutePointList = pRoute->pRoutePointList;
      wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
      RoutePoint *prp;

      int i=1;
      while ( node2 )
      {
            prp = node2->GetData();

            wxXmlNode *rpt_node = ::CreateGPXTptNode ( prp,i+1 );
            trkseg_node->AddChild ( rpt_node );

            node2=node2->GetNext();
            i++;
      }
}
#endif


// toh, 2009.02.24
bool MyConfig::WptIsInRouteList ( RoutePoint *pr )
{
      bool IsInList = false;

      wxRouteListNode *node1 = pRouteList->GetFirst();
      while ( node1 )
      {
            Route *pRoute = node1->GetData();
            RoutePointList *pRoutePointList = pRoute->pRoutePointList;

            wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
            RoutePoint *prp;

            while ( node2 )
            {
                  prp = node2->GetData();

                  if ( pr->IsSame ( prp ) )
                  {
                        IsInList = true;
                        break;
                  }

                  node2=node2->GetNext();
            }
            node1 = node1->GetNext();
      }
      return IsInList;
}

void MyConfig::WriteXMLNavObj ( const wxString& file )
{
      m_pXMLNavObj->Save ( file, 4 );
}


wxXmlNode *MyConfig::CreateGPXWptNode ( RoutePoint *pr )
{
      wxXmlNode *GPXWpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "wpt" ) );

      wxString str_lat;
      str_lat.Printf ( _T ( "%.6f" ), pr->m_lat );
      wxString str_lon;
      str_lon.Printf ( _T ( "%.6f" ), pr->m_lon );
      GPXWpt_node->AddProperty ( _T ( "lat" ),str_lat );
      GPXWpt_node->AddProperty ( _T ( "lon" ),str_lon );

      //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node;


      //  Name
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      GPXWpt_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Description
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "desc" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkDescription );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  Icon
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "sym" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_IconName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Type (waypoint or POI)
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),_T ( "WPT" ) );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  RoutePoint properties/flags
      wxString str = pr->CreatePropString();

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "prop" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), str );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Hyperlinks
      HyperlinkList *linklist = pr->m_HyperlinkList;
      if(linklist)
      {
            wxHyperlinkListNode *linknode = linklist->GetFirst();
            while ( linknode )
            {
                  Hyperlink *link = linknode->GetData();
                  wxString Link = link->Link;
                  wxString Descr = link->DescrText;
                  wxString Type = link->Type;

                  node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "link" ) );
                  current_sib_node->SetNext ( node );

                  wxXmlProperty *prop = new wxXmlProperty ( _T ( "href" ),Link );
                  node->SetProperties ( prop );

                  if ( Descr.Length() > 0 )
                  {
                        wxXmlNode *textnode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "text" ) );
                        node->AddChild ( textnode );
                        wxXmlNode *descrnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Descr );
                        textnode->AddChild ( descrnode );

                  }

                  current_sib_node = node;

                  if ( Type.Length() > 0 )
                  {
                        wxXmlNode *typenode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
                        node->AddChild ( typenode );
                        wxXmlNode *typnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Type );
                        typenode->AddChild ( typnode );
                  }

                  current_sib_node = node;

                  linknode = linknode->GetNext();
            }
      }


      return ( GPXWpt_node );
}

wxXmlNode *MyConfig::CreateGPXRptNode ( RoutePoint *pr,int nbr )
{
      wxXmlNode *GPXWpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "rtept" ) );

      wxString str_lat;
      str_lat.Printf ( _T ( "%.6f" ), pr->m_lat );
      wxString str_lon;
      str_lon.Printf ( _T ( "%.6f" ), pr->m_lon );
      GPXWpt_node->AddProperty ( _T ( "lat" ),str_lat );
      GPXWpt_node->AddProperty ( _T ( "lon" ),str_lon );

      //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node;


      //  Name
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      GPXWpt_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Description
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "desc" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkDescription );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  Icon
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "sym" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_IconName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Type (waypoint or POI)
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),_T ( "WPT" ) /* pr->m_MarkDescription*/ );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  RoutePoint properties/flags
      wxString str = pr->CreatePropString();

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "prop" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), str );
      node->AddChild ( tnode );

      current_sib_node = node;


      // Hyperlinks
      HyperlinkList *linklist = pr->m_HyperlinkList;
      if(linklist)
      {
            wxHyperlinkListNode *linknode = linklist->GetFirst();
            while ( linknode )
            {
                  Hyperlink *link = linknode->GetData();
                  wxString Link = link->Link;
                  wxString Descr = link->DescrText;
                  wxString Type = link->Type;

                  node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "link" ) );
                  current_sib_node->SetNext ( node );

                  wxXmlProperty *prop = new wxXmlProperty ( _T ( "href" ),Link );
                  node->SetProperties ( prop );

                  if ( Descr.Length() > 0 )
                  {
                        wxXmlNode *textnode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "text" ) );
                        node->AddChild ( textnode );
                        wxXmlNode *descrnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Descr );
                        textnode->AddChild ( descrnode );

                  }

                  current_sib_node = node;

                  if ( Type.Length() > 0 )
                  {
                        wxXmlNode *typenode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
                        node->AddChild ( typenode );
                        wxXmlNode *typnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Type );
                        typenode->AddChild ( typnode );
                  }

                  current_sib_node = node;

                  linknode = linknode->GetNext();
            }
      }

      return ( GPXWpt_node );
}


#if 0
wxXmlNode *MyConfig::CreateGPXTptNode ( RoutePoint *pr,int nbr )
{
      wxXmlNode *GPXWpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "trkpt" ) );

      wxString str_lat;
      str_lat.Printf ( _T ( "%.6f" ), pr->m_lat );
      wxString str_lon;
      str_lon.Printf ( _T ( "%.6f" ), pr->m_lon );
      GPXWpt_node->AddProperty ( _T ( "lat" ),str_lat );
      GPXWpt_node->AddProperty ( _T ( "lon" ),str_lon );

      //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node = NULL;

            //  Create Time
      if ( pr->m_CreateTime.IsValid() )
      {
            wxString dt;
            dt = pr->m_CreateTime.FormatISODate();
            dt += _T ( "T" );
            dt += pr->m_CreateTime.FormatISOTime();
            dt += _T ( "Z" );

            node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "time" ) );
            GPXWpt_node->AddChild ( node );
            tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), dt );
            node->AddChild ( tnode );

            current_sib_node = node;
      }

      //  Name
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      if(current_sib_node)
            current_sib_node->SetNext ( node );
      else
            GPXWpt_node->AddChild ( node );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkName );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  Icon
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "sym" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_IconName );
      node->AddChild ( tnode );

      current_sib_node = node;



      return ( GPXWpt_node );
}
#endif


//-------------------------------------------------------------------------
//
//          Static GPX Support Routines
//
//-------------------------------------------------------------------------

wxXmlNode *CreateGPXTrackStatic ( Route *pRoute )
{

      wxXmlNode *GPXTrk_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "trk" ) );

      wxXmlNode *node;
      wxXmlNode *tnode;

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      GPXTrk_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pRoute->m_RouteNameString );
      node->AddChild ( tnode );

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "number" ) );
      GPXTrk_node->AddChild ( node );
      wxString strnum;
      strnum.Printf ( _T ( "%d" ),pRoute->m_ConfigRouteNum );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), strnum );
      node->AddChild ( tnode );

      wxXmlNode *trkseg_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "trkseg" ) );
      GPXTrk_node->AddChild ( trkseg_node );


      RoutePointList *pRoutePointList = pRoute->pRoutePointList;
      wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
      RoutePoint *prp;

      int i=1;
      while ( node2 )
      {
            prp = node2->GetData();

            wxXmlNode *rpt_node = ::CreateGPXTptNode ( prp,i+1 );
            trkseg_node->AddChild ( rpt_node );

            node2=node2->GetNext();
            i++;
      }

      return GPXTrk_node;
}





wxXmlNode *CreateGPXWptNode ( RoutePoint *pr )
{
      wxXmlNode *GPXWpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "wpt" ) );

      wxString str_lat;
      str_lat.Printf ( _T ( "%.6f" ), pr->m_lat );
      wxString str_lon;
      str_lon.Printf ( _T ( "%.6f" ), pr->m_lon );
      GPXWpt_node->AddProperty ( _T ( "lat" ),str_lat );
      GPXWpt_node->AddProperty ( _T ( "lon" ),str_lon );

      //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node;


      //  Name
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      GPXWpt_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Description
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "desc" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkDescription );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  Icon
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "sym" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_IconName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Type (waypoint or POI)
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),_T ( "WPT" )  );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  RoutePoint properties/flags
      wxString str = pr->CreatePropString();

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "prop" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), str );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Hyperlinks
      HyperlinkList *linklist = pr->m_HyperlinkList;
      if(linklist)
      {
            wxHyperlinkListNode *linknode = linklist->GetFirst();
            while ( linknode )
            {
                  Hyperlink *link = linknode->GetData();
                  wxString Link = link->Link;
                  wxString Descr = link->DescrText;
                  wxString Type = link->Type;

                  node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "link" ) );
                  current_sib_node->SetNext ( node );

                  wxXmlProperty *prop = new wxXmlProperty ( _T ( "href" ),Link );
                  node->SetProperties ( prop );

                  if ( Descr.Length() > 0 )
                  {
                        wxXmlNode *textnode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "text" ) );
                        node->AddChild ( textnode );
                        wxXmlNode *descrnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Descr );
                        textnode->AddChild ( descrnode );

                  }

                  current_sib_node = node;

                  if ( Type.Length() > 0 )
                  {
                        wxXmlNode *typenode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
                        node->AddChild ( typenode );
                        wxXmlNode *typnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Type );
                        typenode->AddChild ( typnode );
                  }

                  current_sib_node = node;

                  linknode = linknode->GetNext();
            }
      }

      return ( GPXWpt_node );
}


wxXmlNode *CreateGPXRptNode ( RoutePoint *pr,int nbr )
{
      wxXmlNode *GPXWpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "rtept" ) );

      wxString str_lat;
      str_lat.Printf ( _T ( "%.6f" ), pr->m_lat );
      wxString str_lon;
      str_lon.Printf ( _T ( "%.6f" ), pr->m_lon );
      GPXWpt_node->AddProperty ( _T ( "lat" ),str_lat );
      GPXWpt_node->AddProperty ( _T ( "lon" ),str_lon );

      //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node;


      //  Name
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      GPXWpt_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Description
      if ( pr->m_MarkDescription.Len() )
      {
            node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "desc" ) );
            current_sib_node->SetNext ( node );
            tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkDescription );
            node->AddChild ( tnode );

            current_sib_node = node;
      }

           //  Icon
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "sym" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_IconName );
      node->AddChild ( tnode );

      current_sib_node = node;

           // Type (waypoint or POI)
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),_T ( "WPT" ) /* pr->m_MarkDescription*/ );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  RoutePoint properties/flags
      wxString str = pr->CreatePropString();

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "prop" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), str );
      node->AddChild ( tnode );

      current_sib_node = node;


      // Hyperlinks
      HyperlinkList *linklist = pr->m_HyperlinkList;
      if(linklist)
      {
            wxHyperlinkListNode *linknode = linklist->GetFirst();
            while ( linknode )
            {
                  Hyperlink *link = linknode->GetData();
                  wxString Link = link->Link;
                  wxString Descr = link->DescrText;
                  wxString Type = link->Type;

                  node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "link" ) );
                  current_sib_node->SetNext ( node );

                  wxXmlProperty *prop = new wxXmlProperty ( _T ( "href" ),Link );
                  node->SetProperties ( prop );

                  if ( Descr.Length() > 0 )
                  {
                        wxXmlNode *textnode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "text" ) );
                        node->AddChild ( textnode );
                        wxXmlNode *descrnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Descr );
                        textnode->AddChild ( descrnode );

                  }

                  current_sib_node = node;

                  if ( Type.Length() > 0 )
                  {
                        wxXmlNode *typenode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
                        node->AddChild ( typenode );
                        wxXmlNode *typnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Type );
                        typenode->AddChild ( typnode );
                  }

                  current_sib_node = node;

                  linknode = linknode->GetNext();
            }
      }

      return ( GPXWpt_node );
}


wxXmlNode *CreateGPXTptNode ( RoutePoint *pr,int nbr )
{
      wxXmlNode *GPXTpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "trkpt" ) );

      wxString str_lat;
      str_lat.Printf ( _T ( "%.6f" ), pr->m_lat );
      wxString str_lon;
      str_lon.Printf ( _T ( "%.6f" ), pr->m_lon );
      GPXTpt_node->AddProperty ( _T ( "lat" ),str_lat );
      GPXTpt_node->AddProperty ( _T ( "lon" ),str_lon );

      //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node = NULL;

            //  Create Time
      if ( pr->m_CreateTime.IsValid() )
      {
            wxString dt;
            dt = pr->m_CreateTime.FormatISODate();
            dt += _T ( "T" );
            dt += pr->m_CreateTime.FormatISOTime();
            dt += _T ( "Z" );

            node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "time" ) );
            GPXTpt_node->AddChild ( node );
            tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), dt );
            node->AddChild ( tnode );

            current_sib_node = node;
      }


      //  Name
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "name" ) );
      if(current_sib_node)
            current_sib_node->SetNext ( node );
      else
            GPXTpt_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkName );
      node->AddChild ( tnode );

      current_sib_node = node;

      // Description
      if ( pr->m_MarkDescription.Len() )
      {
            node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "desc" ) );
            current_sib_node->SetNext ( node );
            tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkDescription );
            node->AddChild ( tnode );

            current_sib_node = node;
      }

      //  Icon
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "sym" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_IconName );
      node->AddChild ( tnode );

      current_sib_node = node;


      // Hyperlinks
      HyperlinkList *linklist = pr->m_HyperlinkList;
      if(linklist)
      {
            if ( linklist->GetCount() )
            {
                  wxHyperlinkListNode *linknode = linklist->GetFirst();
                  while ( linknode )
                  {
                        Hyperlink *link = linknode->GetData();
                        wxString Link = link->Link;
                        wxString Descr = link->DescrText;
                        wxString Type = link->Type;

                        node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "link" ) );
                        current_sib_node->SetNext ( node );

                        wxXmlProperty *prop = new wxXmlProperty ( _T ( "href" ),Link );
                        node->SetProperties ( prop );

                        if ( Descr.Length() > 0 )
                        {
                              wxXmlNode *textnode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "text" ) );
                              node->AddChild ( textnode );
                              wxXmlNode *descrnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Descr );
                              textnode->AddChild ( descrnode );

                        }

                        current_sib_node = node;

                        if ( Type.Length() > 0 )
                        {
                              wxXmlNode *typenode = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "type" ) );
                              node->AddChild ( typenode );
                              wxXmlNode *typnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ),Type );
                              typenode->AddChild ( typnode );
                        }

                        current_sib_node = node;

                        linknode = linknode->GetNext();
                  }
            }
      }

      return ( GPXTpt_node );
}




RoutePoint *LoadGPXTrackpoint ( wxXmlNode* wptnode )
{
      wxString LatString = wptnode->GetPropVal ( _T ( "lat" ),_T ( "0.0" ) );
      wxString LonString = wptnode->GetPropVal ( _T ( "lon" ),_T ( "0.0" ) );

      wxString SymString  = _T ( "circle" );                // default icon
      wxString NameString = _T ( "" );
      wxString DescString = _T ( "" );
      wxString TypeString = _T ( "" );
      wxString ChildName  = _T ( "" );
      wxDateTime dt;

      HyperlinkList *linklist = NULL;

      wxString HrefString = _T ( "" );
      wxString HrefTextString = _T ( "" );
      wxString HrefTypeString = _T ( "" );

      wxXmlNode *child = wptnode->GetChildren();
      while ( child )
      {
            ChildName = child->GetName();
            if ( ChildName == _T ( "sym" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        SymString = child1->GetContent();
            }
            if ( ChildName == _T ( "name" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        NameString = child1->GetContent();
            }
            if ( ChildName == _T ( "desc" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        DescString = child1->GetContent();
            }
            if ( ChildName == _T ( "type" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                        TypeString = child1->GetContent();
            }

            if ( ChildName == _T ( "time" ) )
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if ( child1 != NULL )
                  {
                        wxString TimeString = child1->GetContent();
                        if ( TimeString.Len() )
                        {
                              TimeString.Replace(_T("T"), _T(" "));             // make ParseDateTime work
                              dt.ParseDateTime ( TimeString );
                        }
                  }
            }
            // Read hyperlink
            if ( ChildName == _T ( "link" ) )
            {
                  linklist = new HyperlinkList;

                  HrefString = child->GetPropVal ( _T ( "href" ),_T ( "" ) );

                  wxXmlNode *child1 = child->GetChildren();
                  while ( child1 )
                  {
                        wxString LinkString = child1->GetName();

                        if ( LinkString == _T ( "text" ) )
                        {
                              wxXmlNode *child1a = child1->GetChildren();
                              HrefTextString = child1a->GetContent();
                        }

                        if ( LinkString == _T ( "type" ) )
                        {
                              wxXmlNode *child1a = child1->GetChildren();
                              HrefTypeString = child1a->GetContent();
                        }
                        child1 = child1->GetNext();
                  }

                  Hyperlink *link = new Hyperlink;
                  link->Link = HrefString;
                  link->DescrText = HrefTextString;
                  link->Type = HrefTypeString;
                  linklist->Append ( link );
            }

            child = child->GetNext();
      }

      // Create waypoint
      double rlat;
      double rlon;
      LatString.ToDouble ( &rlat );
      LonString.ToDouble ( &rlon );

      RoutePoint *pWP = new RoutePoint ( rlat, rlon, SymString, NameString );
      pWP->m_bShowName = false;
      pWP->m_NameLocationOffsetX = -10;
      pWP->m_NameLocationOffsetY = 8;
      pWP->m_bIsVisible = false;
      if ( dt.IsValid() )
            pWP->m_CreateTime = dt;

      if(linklist)
      {
            delete pWP->m_HyperlinkList;                    // created in RoutePoint ctor
            pWP->m_HyperlinkList = linklist;
      }

      return ( pWP );
}



void GPXLoadTrack ( wxXmlNode* trknode )
{
      //    Tentatively take the Track name from the Property "name"
      //    May be overridden later by child <name>..</name>
      wxString RouteName = trknode->GetPropVal ( _T ( "name" ),_T ( "N.N." ) );

      wxString Name = trknode->GetName();
      if ( Name == _T ( "trk" ) )
      {
            Track *pTentTrack = new Track();

            wxXmlNode *tschild = trknode->GetChildren();

            RoutePoint *pRecentPoint = NULL;
            RoutePoint *pWp = NULL;

            while ( tschild )
            {
                  wxString ChildName = tschild->GetName();
                  if ( ChildName == _T ( "trkseg" ) )
                  {
                        //    Official GPX spec calls for trkseg to have children trkpt
                        wxXmlNode *tpchild = tschild->GetChildren();
                        if(tpchild)
                        {
                              while(tpchild)
                              {
                                    wxString tpChildName = tpchild->GetName();
                                    if(tpChildName == _T("trkpt"))
                                    {
                                          pWp = ::LoadGPXTrackpoint ( tpchild );


                              //    Don't add this point if it is geographically the same as the previous point
                                          if(pRecentPoint)
                                          {
                                                if((pRecentPoint->m_lat != pWp->m_lat) || (pRecentPoint->m_lon != pWp->m_lon))
                                                      pTentTrack->AddPoint ( pWp, false );                      // don't auto-rename numerically

                                          }
                                          else
                                                pTentTrack->AddPoint ( pWp, false );                      // add first point always

                                          pRecentPoint = pWp;
                                    }

                                    //          This else clause loads opencpn tracks exported prior to v1.3.5 Build 1122
                                    //          and can go away after release of 1.3.6
                                    else
                                    {
                                          pWp = ::LoadGPXTrackpoint ( tschild );

                              //    Don't add this point if it is geographically the same as the previous point
                                          if(pRecentPoint)
                                          {
                                                if((pRecentPoint->m_lat != pWp->m_lat) || (pRecentPoint->m_lon != pWp->m_lon))
                                                      pTentTrack->AddPoint ( pWp, false );                      // don't auto-rename numerically

                                          }
                                          else
                                                pTentTrack->AddPoint ( pWp, false );                      // add first point always

                                          pRecentPoint = pWp;
                                    }


                                    tpchild = tpchild->GetNext();

                              }
                        }
                  }
                  else if ( ChildName == _T ( "name" ) )
                  {
                        wxXmlNode *child1 = tschild->GetChildren();
                        if( child1 )                                    // name will always be in first child??
                              RouteName = child1->GetContent();
                  }

                  tschild = tschild->GetNext();

            }

            pTentTrack->m_RouteNameString = RouteName;

            //    Search for an identical route/track already in place.  If found, discard this one

            bool  bAddtrack = true;
            wxRouteListNode *route_node = pRouteList->GetFirst();
            while ( route_node )
            {
                  Route *proute = route_node->GetData();

                  if ( proute->IsEqualTo ( pTentTrack ) )
                  {
                        bAddtrack = false;
                        break;
                  }
                  route_node = route_node->GetNext();                         // next route
            }

            //    If the track has only 1 point, don't load it.
            //    This usually occurs if some points were dscarded above as being co-incident.
            if(pTentTrack->GetnPoints() < 2)
                  bAddtrack = false;

//    TODO  All this trouble for a tentative route.......Should make some Route methods????
            if ( bAddtrack )
            {
                  pRouteList->Append ( pTentTrack );

                  //    Add the selectable points and segments

                  int ip = 0;
                  float prev_rlat, prev_rlon;
                  RoutePoint *prev_pConfPoint;

                  wxRoutePointListNode *node = pTentTrack->pRoutePointList->GetFirst();
                  while ( node )
                  {

                        RoutePoint *prp = node->GetData();

                        if ( ip )
                              pSelect->AddSelectableRouteSegment ( prev_rlat, prev_rlon, prp->m_lat, prp->m_lon,prev_pConfPoint, prp, pTentTrack );

                        prev_rlat = prp->m_lat;
                        prev_rlon = prp->m_lon;
                        prev_pConfPoint = prp;

                        ip++;

                        node = node->GetNext();
                  }
            }
            else
            {

                  // walk the route, deleting points used only by this route
                  wxRoutePointListNode *pnode = ( pTentTrack->pRoutePointList )->GetFirst();
                  while ( pnode )
                  {
                        RoutePoint *prp = pnode->GetData();

                        // check all other routes to see if this point appears in any other route
                        Route *pcontainer_route = pRouteMan->FindRouteContainingWaypoint ( prp );

                        if ( pcontainer_route == NULL )
                        {
                              prp->m_bIsInRoute = false;          // Take this point out of this (and only) track/route
                              if ( !prp->m_bKeepXRoute )
                              {
                                    pConfig->DeleteWayPoint ( prp );
                                    delete prp;
                              }
                        }

                        pnode = pnode->GetNext();
                  }

                  delete pTentTrack;
            }
      }
}



















//---------------------------------------------------------------------------------
//    XML Support for Navigation Objects
//---------------------------------------------------------------------------------

NavObjectCollection::NavObjectCollection ( wxString RootName, wxString Version, wxString Creator )
{
      m_pXMLrootnode = new wxXmlNode ( wxXML_ELEMENT_NODE, RootName );
      m_pXMLrootnode->AddProperty ( _T ( "version" ), Version );
      m_pXMLrootnode->AddProperty ( _T ( "creator" ), Creator );
      SetRoot ( m_pXMLrootnode );
      m_proot_next = NULL;
}

NavObjectCollection::~NavObjectCollection()
{
//     delete m_pXMLrootnode;            // done in base class
}

bool NavObjectCollection::CreateGPXPoints ( void )
{

      //    Iterate over the Routepoint list, creating Nodes for
      //    Routepoints that are not in any Route

      wxRoutePointListNode *node = pWayPointMan->m_pWayPointList->GetFirst();

      RoutePoint *pr;

      while ( node )
      {
            pr = node->GetData();

            if ( !pr->m_bIsInRoute )
            {
                  wxXmlNode *mark_node = CreateGPXWptNode ( pr );

                  if( m_proot_next == NULL )
                        m_pXMLrootnode->AddChild ( mark_node );
                  else
                        m_proot_next->SetNext( mark_node );

                  m_proot_next = mark_node;

            }
            node = node->GetNext();
      }

      return true;
}

bool NavObjectCollection::CreateGPXRoutes ( void )
{
      // Routes
      wxRouteListNode *node1 = pRouteList->GetFirst();
      while ( node1 )
      {
            Route *pRoute = node1->GetData();

            if ( !pRoute->m_bIsTrack )                            // Not tracks
            {
                  RoutePointList *pRoutePointList = pRoute->pRoutePointList;

                  wxXmlNode *GPXWpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "rte" ) );
                  GPXWpt_node->AddProperty ( _T ( "name" ),pRoute->m_RouteNameString );
                  wxString strnum;
                  strnum.Printf ( _T ( "%d" ),pRoute->m_ConfigRouteNum );
                  GPXWpt_node->AddProperty ( _T ( "number" ),strnum );


                  if(m_proot_next == NULL)
                        m_pXMLrootnode->AddChild ( GPXWpt_node );
                  else
                        m_proot_next->SetNext( GPXWpt_node );

                  m_proot_next = GPXWpt_node;

                  wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
                  RoutePoint *prp;

                  int i=1;
                  wxXmlNode *current_sib;

                  while ( node2 )
                  {
                        prp = node2->GetData();

                        wxXmlNode *rpt_node = CreateGPXRptNode ( prp,i+1 );

                        if(i == 1)
                              GPXWpt_node->AddChild ( rpt_node );
                        else
                              current_sib->SetNext(rpt_node);

                        current_sib = rpt_node;

                        node2=node2->GetNext();
                        i++;
                  }
            }
            node1 = node1->GetNext();
      }

      return true;
}

bool NavObjectCollection::CreateGPXTracks ( void )
{
      // Tracks
      wxRouteListNode *node1 = pRouteList->GetFirst();
      while ( node1 )
      {
            Route *pRoute = node1->GetData();
            RoutePointList *pRoutePointList = pRoute->pRoutePointList;

            if ( pRoutePointList->GetCount() )
            {
                  if ( pRoute->m_bIsTrack )                            // Tracks only
                  {

                        wxXmlNode *Track_Node = ::CreateGPXTrackStatic ( pRoute );
                        if(m_proot_next == NULL)
                              m_pXMLrootnode->AddChild ( Track_Node );
                        else
                              m_proot_next->SetNext( Track_Node );

                        m_proot_next = Track_Node;

/*
                        wxXmlNode *GPXWpt_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "trk" ) );
                        GPXWpt_node->AddProperty ( _T ( "name" ),pRoute->m_RouteNameString );
                        wxString strnum;
                        strnum.Printf ( _T ( "%d" ),pRoute->m_ConfigRouteNum );
                        GPXWpt_node->AddProperty ( _T ( "number" ),strnum );

                        if(m_proot_next == NULL)
                              m_pXMLrootnode->AddChild ( GPXWpt_node );
                        else
                              m_proot_next->SetNext( GPXWpt_node );

                        m_proot_next = GPXWpt_node;

                        wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
                        RoutePoint *prp;

                        int i=1;
                        wxXmlNode *current_sib;

                        while ( node2 )
                        {
                              prp = node2->GetData();

                              wxXmlNode *rpt_node = ::CreateGPXTptNode ( prp,i+1 );

                              if(i == 1)
                                    GPXWpt_node->AddChild ( rpt_node );
                              else
                                    current_sib->SetNext(rpt_node);

                              current_sib = rpt_node;

                              node2=node2->GetNext();
                              i++;
                        }
                        */
                  }
            }
            node1 = node1->GetNext();
      }

      return true;
}



bool NavObjectCollection::LoadAllGPXTracks()
{
      wxXmlNode *root = GetRoot();

      wxString RootName = root->GetName();
      if ( RootName == _T ( "gpx" ) )
      {
            wxString RootContent = root->GetNodeContent();

            wxXmlNode *child = root->GetChildren();
            while ( child )
            {
                  wxString ChildName = child->GetName();
                  if ( ChildName == _T ( "trk" ) )
                        ::GPXLoadTrack ( child );

                  child = child->GetNext();
            }
      }

      return true;
}







wxXmlNode *NavObjectCollection::CreateMarkNode ( RoutePoint *pr )
{
      wxXmlNode *mark_node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "Mark" ) );

      //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node;

      //  Icon
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "Icon" ) );
      mark_node->AddChild ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_IconName );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  Position
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "Position" ) );
      current_sib_node->SetNext ( node );
      wxString str_pos;
      str_pos.Printf ( _T ( "%9.6f" ), fabs ( pr->m_lat ) );
      if ( pr->m_lat > 0 )
            str_pos += _T ( " N " );
      else
            str_pos += _T ( " S " );

      wxString str_pos1;
      str_pos1.Printf ( _T ( "%10.6f" ), fabs ( pr->m_lon ) );
      str_pos += str_pos1;
      if ( pr->m_lon > 0 )
            str_pos += _T ( " E" );
      else
            str_pos += _T ( " W" );

      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), str_pos );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  Name
      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "Name" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), pr->m_MarkName );
      node->AddChild ( tnode );

      current_sib_node = node;

      //  RoutePoint properties/flags
      wxString str = pr->CreatePropString();

      node = new wxXmlNode ( wxXML_ELEMENT_NODE, _T ( "prop" ) );
      current_sib_node->SetNext ( node );
      tnode = new wxXmlNode ( wxXML_TEXT_NODE, _T ( "" ), str );
      node->AddChild ( tnode );

      current_sib_node = node;

      return ( mark_node );
}

/*
void NavObjectCollection::LoadGPXTrack ( wxXmlNode* rtenode )
{
      wxString Name = rtenode->GetName();
      wxString RouteName = rtenode->GetPropVal ( _T ( "name" ),_T ( "N.N." ) );

      if ( Name == _T ( "trk" ) )
      {
            Track *pTentTrack = new Track();

            pTentTrack->m_RouteNameString = RouteName;

            wxXmlNode *child = rtenode->GetChildren();

            RoutePoint *pRecentPoint = NULL;

            while ( child )
            {
                  wxString ChildName = child->GetName();
                  if ( ChildName == _T ( "trkseg" ) )
                  {
                        RoutePoint *pWp = LoadGPXTrackpoint ( child );

                        //    Don't add this point if it is geographically the same as the previous point
                        if(pRecentPoint)
                        {
                              if((pRecentPoint->m_lat != pWp->m_lat) || (pRecentPoint->m_lon != pWp->m_lon))
                                    pTentTrack->AddPoint ( pWp, false );                      // don't auto-rename numerically
                        }
                        else
                              pTentTrack->AddPoint ( pWp, false );                      // add first point always

                        pRecentPoint = pWp;
                  }
                  child = child->GetNext();
            }

            //    Search for an identical route already in place.  If found, discard this one

            bool  bAddtrack = true;

            wxRouteListNode *route_node = pRouteList->GetFirst();
            while ( route_node )
            {
                  Route *proute = route_node->GetData();

                  if ( proute->IsEqualTo ( pTentTrack ) )
                  {
                        bAddtrack = false;
                        break;
                  }
                  route_node = route_node->GetNext();                         // next route
            }

            //    If the track has only 1 point, don't load it.
            //    This usually occurs if some points were dscarded above as being co-incident.

            if(pTentTrack->GetnPoints() < 2)
                  bAddtrack = false;

//    TODO  All this trouble for a tentative route.......Should make some Route methods????
            if ( bAddtrack )
            {
                  pRouteList->Append ( pTentTrack );

                  //    Add the selectable points and segments

                  int ip = 0;
                  float prev_rlat, prev_rlon;
                  RoutePoint *prev_pConfPoint;

                  wxRoutePointListNode *node = pTentTrack->pRoutePointList->GetFirst();
                  while ( node )
                  {

                        RoutePoint *prp = node->GetData();

                        if ( ip )
                              pSelect->AddSelectableRouteSegment ( prev_rlat, prev_rlon, prp->m_lat, prp->m_lon,prev_pConfPoint, prp, pTentTrack );

                        prev_rlat = prp->m_lat;
                        prev_rlon = prp->m_lon;
                        prev_pConfPoint = prp;

                        ip++;

                        node = node->GetNext();
                  }
            }
            else
            {

                  // walk the route, deleting points used only by this route
                  wxRoutePointListNode *pnode = ( pTentTrack->pRoutePointList )->GetFirst();
                  while ( pnode )
                  {
                        RoutePoint *prp = pnode->GetData();

                        // check all other routes to see if this point appears in any other route
                        Route *pcontainer_route = pRouteMan->FindRouteContainingWaypoint ( prp );

                        if ( pcontainer_route == NULL )
                        {
                              prp->m_bIsInRoute = false;          // Take this point out of this (and only) track/route
                              if ( !prp->m_bKeepXRoute )
                              {
                                    pConfig->DeleteWayPoint ( prp );
                                    delete prp;
                              }
                        }

                        pnode = pnode->GetNext();
                  }

                  delete pTentTrack;
            }
      }
}

*/



//---------------------------------------------------------------------------------
//          Private Font Manager and Helpers
//---------------------------------------------------------------------------------
#include <wx/fontdlg.h>
#include <wx/fontenum.h>
#include "wx/encinfo.h"
#include "wx/fontutil.h"

MyFontDesc::MyFontDesc ( const char *DialogString, const char *ConfigString, wxFont *pFont, wxColour color )
{
      m_dialogstring = new wxString ( DialogString,  wxConvUTF8 );
      m_configstring = new wxString ( ConfigString,  wxConvUTF8 );

      m_nativeInfo = new wxString ( pFont->GetNativeFontInfoDesc() );

      m_font = pFont;
      m_color = color;
}

MyFontDesc::~MyFontDesc()
{
      delete m_dialogstring;
      delete m_configstring;
      delete m_nativeInfo;
      delete m_font;
}


#include <wx/listimpl.cpp>
WX_DEFINE_LIST ( FontList );

FontMgr::FontMgr()
{

      //    Create the list of fonts
      m_fontlist = new FontList;
      m_fontlist->DeleteContents ( true );

      //    Get a nice generic font as default
      pDefFont = wxTheFontList->FindOrCreateFont ( 12, wxDEFAULT,wxNORMAL, wxBOLD,
                 FALSE, wxString ( _T ( "" ) ), wxFONTENCODING_SYSTEM );


}

FontMgr::~FontMgr()
{
      delete m_fontlist;
}


wxColour FontMgr::GetFontColor ( const wxString &TextElement )
{
       //    Look thru the font list for a match
      MyFontDesc *pmfd;
      wxNode *node = ( wxNode * ) ( m_fontlist->GetFirst() );  while ( node )
      {
            pmfd = ( MyFontDesc * ) node->GetData();
            if ( *pmfd->m_dialogstring == TextElement )
                  return pmfd->m_color;
            node = node->GetNext();
      }

      return wxColour(0,0,0);
}

wxFont *FontMgr::GetFont ( const wxString &TextElement, int default_size )
{
      //    Look thru the font list for a match
      MyFontDesc *pmfd;
      wxNode *node = ( wxNode * ) ( m_fontlist->GetFirst() );  while ( node )
      {
            pmfd = ( MyFontDesc * ) node->GetData();
            if ( *pmfd->m_dialogstring == TextElement )
                  return pmfd->m_font;
            node = node->GetNext();
      }

      //    Found no font, so create a nice one and add to the list
      //    First, create the configstring by contortion of the TextElement
      wxString configstring ( _T ( "Font" ) );
      int i=0;
      while ( TextElement[i] )
      {
            if ( TextElement[i] != ' ' )                    // strip out the spaces
                  configstring += TextElement[i];
            i++;
      }

      //    Now create a benign, always present native string
      wxString nativefont;

      //    Optional user requested default size
      int new_size;
      if ( 0 == default_size )
            new_size = 12;
      else
            new_size = default_size;

//    For those platforms which have no native font description string format
      nativefont.Printf ( _T ( "%d;%d;%d;%d;%d;%d;%s;%d" ),
                          0,                                 // version
                          new_size,
                          wxFONTFAMILY_DEFAULT,
                          ( int ) wxFONTSTYLE_NORMAL,
                          ( int ) wxFONTWEIGHT_NORMAL,
                          false,
                          "",
                          ( int ) wxFONTENCODING_DEFAULT );

//    If we know of a detailed description string format, use it.
#ifdef __WXGTK__
      nativefont.Printf ( _T ( "Fixed %2d" ), new_size );
#endif

#ifdef __WXX11__
      nativefont = _T ( "0;-*-fixed-*-*-*-*-*-120-*-*-*-*-iso8859-1" );
#endif

#ifdef __WXMSW__
//      nativefont = _T ( "0;-11;0;0;0;400;0;0;0;0;0;0;0;0;MS Sans Serif" );

      int h, w, hm, wm;
      ::wxDisplaySize(&w, &h);            // pixels
      ::wxDisplaySizeMM(&wm, &hm);        // MM
      double pix_per_inch_v = (h / hm) *  25.4;
      int lfHeight = -(int)((new_size * (pix_per_inch_v/72.0)) + 0.5);

      nativefont.Printf(_T("%d;%ld;%ld;%ld;%ld;%ld;%d;%d;%d;%d;%d;%d;%d;%d;%s"),
               0,                   // version, in case we want to change the format later
               lfHeight,            //lf.lfHeight
               0,                   //lf.lfWidth,
               0,                   //lf.lfEscapement,
               0,                   //lf.lfOrientation,
               400,                 //lf.lfWeight,
               0,                   //lf.lfItalic,
               0,                   //lf.lfUnderline,
               0,                   //lf.lfStrikeOut,
               0,                   //lf.lfCharSet,
               0,                   //lf.lfOutPrecision,
               0,                   //lf.lfClipPrecision,
               0,                   //lf.lfQuality,
               0,                   //lf.lfPitchAndFamily,
               "MS Sans Serif");      //lf.lfFaceName

#endif


      wxFont *nf0 = new wxFont();
      wxFont *nf = nf0->New ( nativefont );

      wxColor color(*wxBLACK);

      MyFontDesc *pnewfd = new MyFontDesc ( TextElement.mb_str(), configstring.mb_str(), nf, color );
      m_fontlist->Append ( pnewfd );

      return pnewfd->m_font;

}


bool FontMgr::SetFont ( wxString &TextElement, wxFont *pFont, wxColour color )
{
      //    Look thru the font list for a match
      MyFontDesc *pmfd;
      wxNode *node = ( wxNode * ) ( m_fontlist->GetFirst() );  while ( node )
      {
            pmfd = ( MyFontDesc * ) node->GetData();
            if ( *pmfd->m_dialogstring == TextElement )
            {
                  // Todo Think about this
                  //

//      Cannot delete the present font, since it may be in use elsewhere
//      This WILL leak....but only on font changes


//              delete pmfd->m_font;                            // purge any old value
                  delete pmfd->m_nativeInfo;

                  pmfd->m_font = pFont;
                  pmfd->m_nativeInfo = new wxString ( pFont->GetNativeFontInfoDesc() );
                  pmfd->m_color = color;

                  return true;
            }
            node = node->GetNext();
      }

      return false;
}



int FontMgr::GetNumFonts ( void )
{
      return m_fontlist->GetCount();
}

wxString *FontMgr::GetConfigString ( int i )
{
      MyFontDesc *pfd = ( MyFontDesc * ) ( m_fontlist->Item ( i )->GetData() );
      wxString *ret = pfd->m_configstring;
      return ret;
}

wxString *FontMgr::GetDialogString ( int i )
{
      MyFontDesc *pfd = ( MyFontDesc * ) ( m_fontlist->Item ( i )->GetData() );
      wxString *ret = pfd->m_dialogstring;
      return ret;
}

wxString *FontMgr::GetNativeDesc ( int i )
{
      MyFontDesc *pfd = ( MyFontDesc * ) ( m_fontlist->Item ( i )->GetData() );
      wxString *ret = pfd->m_nativeInfo;
      return ret;
}

wxString FontMgr::GetFullConfigDesc ( int i )
{
      MyFontDesc *pfd = ( MyFontDesc * ) ( m_fontlist->Item ( i )->GetData() );
      wxString ret =  *(pfd->m_dialogstring);
      ret.Append ( _T ( ":" ) );
      ret.Append( *(pfd->m_nativeInfo) );
      ret.Append ( _T ( ":" ) );

      wxString cols(_T("rgb(0,0,0)"));
      if(pfd->m_color.IsOk())
            cols =  pfd->m_color.GetAsString(wxC2S_CSS_SYNTAX);

      ret.Append(cols);
      return ret;
}




void FontMgr::LoadFontNative ( wxString *pConfigString, wxString *pNativeDesc )
{
      //    Parse the descriptor string

      wxStringTokenizer tk ( *pNativeDesc, _T ( ":" ) );
      wxString dialogstring = tk.GetNextToken();
      wxString nativefont = tk.GetNextToken();

      wxString c = tk.GetNextToken();
      wxColour color(c);            // from string description



      //    Search for a match in the list
      MyFontDesc *pmfd;
      wxNode *node = ( wxNode * ) ( m_fontlist->GetFirst() );

      while ( node )
      {
            pmfd = ( MyFontDesc * ) node->GetData();
            if ( *pmfd->m_configstring == *pConfigString )
            {
                  pmfd->m_nativeInfo = new wxString ( nativefont );
                  wxFont *nf = pmfd->m_font->New ( *pmfd->m_nativeInfo );
                  pmfd->m_font = nf;
                  break;
            }
            node = node->GetNext();
      }

      //    Create and add the font to the list
      if ( !node )
      {

            wxFont *nf0 = new wxFont();
            wxFont *nf = nf0->New ( nativefont );
            delete nf0;

            MyFontDesc *pnewfd = new MyFontDesc ( dialogstring.mb_str(), pConfigString->mb_str(), nf, color );
            m_fontlist->Append ( pnewfd );

      }


}

#ifdef __WXX11__
#include "/usr/X11R6/include/X11/Xlib.h"

//-----------------------------------------------------------------------------
// helper class - MyFontPreviewer
//-----------------------------------------------------------------------------

class  MyFontPreviewer : public wxWindow
{
      public:
            MyFontPreviewer ( wxWindow *parent, const wxSize& sz = wxDefaultSize ) : wxWindow ( parent, wxID_ANY, wxDefaultPosition, sz )
            {
            }

      private:
            void OnPaint ( wxPaintEvent& event );
            DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE ( MyFontPreviewer, wxWindow )
      EVT_PAINT ( MyFontPreviewer::OnPaint )
END_EVENT_TABLE()

void MyFontPreviewer::OnPaint ( wxPaintEvent& WXUNUSED ( event ) )
{
      wxPaintDC dc ( this );

      wxSize size = GetSize();
      wxFont font = GetFont();

      dc.SetPen ( *wxBLACK_PEN );
      dc.SetBrush ( *wxWHITE_BRUSH );
      dc.DrawRectangle ( 0, 0, size.x, size.y );

      if ( font.Ok() )
      {
            dc.SetFont ( font );
            // Calculate vertical centre
            long w, h;
            dc.GetTextExtent ( wxT ( "X" ), &w, &h );
            dc.SetTextForeground ( GetForegroundColour() );
            dc.SetClippingRegion ( 2, 2, size.x-4, size.y-4 );
            dc.DrawText ( GetName(),
                          10, size.y/2 - h/2 );
            dc.DestroyClippingRegion();
      }
}


//-----------------------------------------------------------------------------
// X11FontPicker
//-----------------------------------------------------------------------------


IMPLEMENT_DYNAMIC_CLASS ( X11FontPicker, wxDialog )

BEGIN_EVENT_TABLE ( X11FontPicker, wxDialog )
      EVT_CHECKBOX ( wxID_FONT_UNDERLINE, X11FontPicker::OnChangeFont )
      EVT_CHOICE ( wxID_FONT_STYLE, X11FontPicker::OnChangeFont )
      EVT_CHOICE ( wxID_FONT_WEIGHT, X11FontPicker::OnChangeFont )
      EVT_CHOICE ( wxID_FONT_FAMILY, X11FontPicker::OnChangeFace )
      EVT_CHOICE ( wxID_FONT_COLOUR, X11FontPicker::OnChangeFont )
      EVT_CHOICE ( wxID_FONT_SIZE, X11FontPicker::OnChangeFont )

      EVT_CLOSE ( X11FontPicker::OnCloseWindow )
END_EVENT_TABLE()


#define SCALEABLE_SIZES 11
static wxString scaleable_pointsize[SCALEABLE_SIZES] =
{
      wxT ( "6" ),
      wxT ( "8" ),
      wxT ( "10" ),
      wxT ( "12" ),
      wxT ( "14" ),
      wxT ( "16" ),
      wxT ( "18" ),
      wxT ( "20" ),
      wxT ( "24" ),
      wxT ( "30" ),
      wxT ( "36" )
};


#define NUM_COLS 48
static wxString wxColourDialogNames[NUM_COLS]={wxT ( "ORANGE" ),
        wxT ( "GOLDENROD" ),
        wxT ( "WHEAT" ),
        wxT ( "SPRING GREEN" ),
        wxT ( "SKY BLUE" ),
        wxT ( "SLATE BLUE" ),
        wxT ( "MEDIUM VIOLET RED" ),
        wxT ( "PURPLE" ),

        wxT ( "RED" ),
        wxT ( "YELLOW" ),
        wxT ( "MEDIUM SPRING GREEN" ),
        wxT ( "PALE GREEN" ),
        wxT ( "CYAN" ),
        wxT ( "LIGHT STEEL BLUE" ),
        wxT ( "ORCHID" ),
        wxT ( "LIGHT MAGENTA" ),

        wxT ( "BROWN" ),
        wxT ( "YELLOW" ),
        wxT ( "GREEN" ),
        wxT ( "CADET BLUE" ),
        wxT ( "MEDIUM BLUE" ),
        wxT ( "MAGENTA" ),
        wxT ( "MAROON" ),
        wxT ( "ORANGE RED" ),

        wxT ( "FIREBRICK" ),
        wxT ( "CORAL" ),
        wxT ( "FOREST GREEN" ),
        wxT ( "AQUARAMINE" ),
        wxT ( "BLUE" ),
        wxT ( "NAVY" ),
        wxT ( "THISTLE" ),
        wxT ( "MEDIUM VIOLET RED" ),

        wxT ( "INDIAN RED" ),
        wxT ( "GOLD" ),
        wxT ( "MEDIUM SEA GREEN" ),
        wxT ( "MEDIUM BLUE" ),
        wxT ( "MIDNIGHT BLUE" ),
        wxT ( "GREY" ),
        wxT ( "PURPLE" ),
        wxT ( "KHAKI" ),

        wxT ( "BLACK" ),
        wxT ( "MEDIUM FOREST GREEN" ),
        wxT ( "KHAKI" ),
        wxT ( "DARK GREY" ),
        wxT ( "SEA GREEN" ),
        wxT ( "LIGHT GREY" ),
        wxT ( "MEDIUM SLATE BLUE" ),
        wxT ( "WHITE" )
                                              };

/*
            * Generic X11FontPicker
 */

void X11FontPicker::Init()
{
      m_useEvents = false;
      m_previewer = NULL;
      Create ( m_parent ) ;
}

X11FontPicker::~X11FontPicker()
{
}

void X11FontPicker::OnCloseWindow ( wxCloseEvent& WXUNUSED ( event ) )
{
      EndModal ( wxID_CANCEL );
}

bool X11FontPicker::DoCreate ( wxWindow *parent )
{
      if ( !wxDialog::Create ( parent , wxID_ANY , _T ( "Choose Font" ) , wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE,
                               _T ( "fontdialog" ) ) )
      {
            wxFAIL_MSG ( wxT ( "wxFontDialog creation failed" ) );
            return false;
      }

      InitializeAllAvailableFonts();
      InitializeFont();
      CreateWidgets();

// sets initial font in preview area
      wxCommandEvent dummy;
      OnChangeFont ( dummy );

      return true;
}

int X11FontPicker::ShowModal()
{
      int ret = wxDialog::ShowModal();

      if ( ret != wxID_CANCEL )
      {
            dialogFont = *pPreviewFont;
            m_fontData.m_chosenFont = dialogFont;
      }

      return ret;
}


void X11FontPicker::InitializeAllAvailableFonts()
{

      // get the Array of all fonts facenames
      wxString pattern;
      pattern.Printf ( wxT ( "-*-*-*-*-*-*-*-*-*-*-*-*-iso8859-1" ) );

      int nFonts;
      char ** list = XListFonts ( ( Display * ) wxGetDisplay(), pattern.mb_str(), 32767, &nFonts );

      pFaceNameArray = new wxArrayString;
      unsigned int jname;
      for ( int i=0 ; i < nFonts ; i++ )
      {
            wxStringTokenizer st ( wxString ( list[i] ), _T ( "-" ) );
            st.GetNextToken();
            st.GetNextToken();
            wxString facename = st.GetNextToken();
            for ( jname=0 ; jname<pFaceNameArray->GetCount() ; jname++ )
            {
                  if ( facename == pFaceNameArray->Item ( jname ) )
                        break;
            }
            if ( jname >= pFaceNameArray->GetCount() )
            {
                  pFaceNameArray->Add ( facename );
            }

      }

}


// This should be application-settable
static bool ShowToolTips() { return false; }

void X11FontPicker::CreateWidgets()
{
      // layout

      bool is_pda = ( wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA );
      int noCols, noRows;
      if ( is_pda )
      {
            noCols = 2; noRows = 3;
      }
      else
      {
            noCols = 3; noRows = 2;
      }

      wxBoxSizer* itemBoxSizer2 = new wxBoxSizer ( wxVERTICAL );
      this->SetSizer ( itemBoxSizer2 );
      this->SetAutoLayout ( TRUE );

      wxBoxSizer* itemBoxSizer3 = new wxBoxSizer ( wxVERTICAL );
      itemBoxSizer2->Add ( itemBoxSizer3, 1, wxEXPAND|wxALL, 5 );

      wxFlexGridSizer* itemGridSizer4 = new wxFlexGridSizer ( noRows, noCols, 0, 0 );
      itemBoxSizer3->Add ( itemGridSizer4, 0, wxEXPAND, 5 );

      wxBoxSizer* itemBoxSizer5 = new wxBoxSizer ( wxVERTICAL );
      itemGridSizer4->Add ( itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
      wxStaticText* itemStaticText6 = new wxStaticText ( this, wxID_STATIC, _ ( "&Font family:" ),
              wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer5->Add ( itemStaticText6, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5 );

      wxChoice* itemChoice7 = new wxChoice ( this, wxID_FONT_FAMILY, wxDefaultPosition,
                                             wxDefaultSize, *pFaceNameArray, 0 );
      itemChoice7->SetHelpText ( _ ( "The font family." ) );
      if ( ShowToolTips() )
            itemChoice7->SetToolTip ( _ ( "The font family." ) );
      itemBoxSizer5->Add ( itemChoice7, 0, wxALIGN_LEFT|wxALL, 5 );

      wxBoxSizer* itemBoxSizer8 = new wxBoxSizer ( wxVERTICAL );
      itemGridSizer4->Add ( itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
      wxStaticText* itemStaticText9 = new wxStaticText ( this, wxID_STATIC, _ ( "&Style:" ), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer8->Add ( itemStaticText9, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5 );

      wxChoice* itemChoice10 = new wxChoice ( this, wxID_FONT_STYLE, wxDefaultPosition, wxDefaultSize );
      itemChoice10->SetHelpText ( _ ( "The font style." ) );
      if ( ShowToolTips() )
            itemChoice10->SetToolTip ( _ ( "The font style." ) );
      itemBoxSizer8->Add ( itemChoice10, 0, wxALIGN_LEFT|wxALL, 5 );

      wxBoxSizer* itemBoxSizer11 = new wxBoxSizer ( wxVERTICAL );
      itemGridSizer4->Add ( itemBoxSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
      wxStaticText* itemStaticText12 = new wxStaticText ( this, wxID_STATIC, _ ( "&Weight:" ), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer11->Add ( itemStaticText12, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5 );

      wxChoice* itemChoice13 = new wxChoice ( this, wxID_FONT_WEIGHT, wxDefaultPosition, wxDefaultSize );
      itemChoice13->SetHelpText ( _ ( "The font weight." ) );
      if ( ShowToolTips() )
            itemChoice13->SetToolTip ( _ ( "The font weight." ) );
      itemBoxSizer11->Add ( itemChoice13, 0, wxALIGN_LEFT|wxALL, 5 );

      wxBoxSizer* itemBoxSizer14 = new wxBoxSizer ( wxVERTICAL );
      itemGridSizer4->Add ( itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
      if ( m_fontData.GetEnableEffects() )
      {
            wxStaticText* itemStaticText15 = new wxStaticText ( this, wxID_STATIC, _ ( "C&olour:" ),
                    wxDefaultPosition, wxDefaultSize, 0 );
            itemBoxSizer14->Add ( itemStaticText15, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5 );

            wxSize colourSize = wxDefaultSize;
            if ( is_pda )
                  colourSize.x = 100;

            wxChoice* itemChoice16 = new wxChoice ( this, wxID_FONT_COLOUR, wxDefaultPosition,
                                                    colourSize, NUM_COLS, wxColourDialogNames, 0 );
            itemChoice16->SetHelpText ( _ ( "The font colour." ) );
            if ( ShowToolTips() )
                  itemChoice16->SetToolTip ( _ ( "The font colour." ) );
            itemBoxSizer14->Add ( itemChoice16, 0, wxALIGN_LEFT|wxALL, 5 );
      }

      wxBoxSizer* itemBoxSizer17 = new wxBoxSizer ( wxVERTICAL );
      itemGridSizer4->Add ( itemBoxSizer17, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
      wxStaticText* itemStaticText18 = new wxStaticText ( this, wxID_STATIC, _ ( "&Point size:" ),
              wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer17->Add ( itemStaticText18, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5 );

      wxChoice *pc = new wxChoice ( this, wxID_FONT_SIZE, wxDefaultPosition, wxDefaultSize );
      pc->SetHelpText ( _ ( "The font point size." ) );
      if ( ShowToolTips() )
            pc->SetToolTip ( _ ( "The font point size." ) );
      itemBoxSizer17->Add ( pc, 0, wxALIGN_LEFT|wxALL, 5 );

      if ( m_fontData.GetEnableEffects() )
      {
            wxBoxSizer* itemBoxSizer20 = new wxBoxSizer ( wxVERTICAL );
            itemGridSizer4->Add ( itemBoxSizer20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5 );
            wxCheckBox* itemCheckBox21 = new wxCheckBox ( this, wxID_FONT_UNDERLINE, _ ( "&Underline" ),
                    wxDefaultPosition, wxDefaultSize, 0 );
            itemCheckBox21->SetValue ( FALSE );
            itemCheckBox21->SetHelpText ( _ ( "Whether the font is underlined." ) );
            if ( ShowToolTips() )
                  itemCheckBox21->SetToolTip ( _ ( "Whether the font is underlined." ) );
            itemBoxSizer20->Add ( itemCheckBox21, 0, wxALIGN_LEFT|wxALL, 5 );
      }

      if ( !is_pda )
            itemBoxSizer3->Add ( 5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

      wxStaticText* itemStaticText23 = new wxStaticText ( this, wxID_STATIC, _ ( "Preview:" ), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer3->Add ( itemStaticText23, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5 );

      MyFontPreviewer* itemWindow24 = new MyFontPreviewer ( this, wxSize ( 400, 80 ) );
      m_previewer = itemWindow24;
      itemWindow24->SetHelpText ( _ ( "Shows the font preview." ) );
      if ( ShowToolTips() )
            itemWindow24->SetToolTip ( _ ( "Shows the font preview." ) );
      itemBoxSizer3->Add ( itemWindow24, 0, wxEXPAND, 5 );

      wxBoxSizer* itemBoxSizer25 = new wxBoxSizer ( wxHORIZONTAL );
      itemBoxSizer3->Add ( itemBoxSizer25, 0, wxEXPAND, 5 );
      itemBoxSizer25->Add ( 5, 5, 1, wxEXPAND|wxALL, 5 );

      wxButton* itemButton28 = new wxButton ( this, wxID_CANCEL, _ ( "&Cancel" ), wxDefaultPosition, wxDefaultSize, 0 );
      if ( ShowToolTips() )
            itemButton28->SetToolTip ( _ ( "Click to cancel the font selection." ) );
      itemBoxSizer25->Add ( itemButton28, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

      wxButton* itemButton27 = new wxButton ( this, wxID_OK, _ ( "&OK" ), wxDefaultPosition, wxDefaultSize, 0 );
      itemButton27->SetDefault();
      itemButton27->SetHelpText ( _ ( "Click to confirm the font selection." ) );
      if ( ShowToolTips() )
            itemButton27->SetToolTip ( _ ( "Click to confirm the font selection." ) );
      itemBoxSizer25->Add ( itemButton27, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

      familyChoice = ( wxChoice* ) FindWindow ( wxID_FONT_FAMILY );
      styleChoice = ( wxChoice* ) FindWindow ( wxID_FONT_STYLE );
      weightChoice = ( wxChoice* ) FindWindow ( wxID_FONT_WEIGHT );
      colourChoice = ( wxChoice* ) FindWindow ( wxID_FONT_COLOUR );
      pointSizeChoice = ( wxChoice* ) FindWindow ( wxID_FONT_SIZE );
      underLineCheckBox = ( wxCheckBox* ) FindWindow ( wxID_FONT_UNDERLINE );

      //    Get readable font items
      wxString gotfontnative = dialogFont.GetNativeFontInfoDesc();
      wxStringTokenizer st ( gotfontnative, _T ( "-" ) );
      st.GetNextToken();
      st.GetNextToken();
      wxString facename = st.GetNextToken();
      wxString weight = st.GetNextToken();
      st.GetNextToken();
      st.GetNextToken();
      st.GetNextToken();
      st.GetNextToken();
      wxString pointsize = st.GetNextToken();

      int ptsz = atoi ( pointsize.mb_str() );
      pointsize.Printf ( _T ( "%d" ), ptsz / 10 );

      SetChoiceOptionsFromFacename ( facename );


      familyChoice->SetStringSelection ( facename );
      weightChoice->SetStringSelection ( weight );
      pointSizeChoice->SetStringSelection ( pointsize );

      m_previewer->SetFont ( dialogFont );
      m_previewer->SetName ( _T( "ABCDEFGabcdefg12345" ) );

//    m_previewer->Refresh();


//    familyChoice->SetStringSelection( wxFontFamilyIntToString(dialogFont.GetFamily()) );
//    styleChoice->SetStringSelection(wxFontStyleIntToString(dialogFont.GetStyle()));
//    weightChoice->SetStringSelection(wxFontWeightIntToString(dialogFont.GetWeight()));

      /*
      if (colourChoice)
      {
            wxString name(wxTheColourDatabase->FindName(m_fontData.GetColour()));
            if (name.length())
                  colourChoice->SetStringSelection(name);
            else
                  colourChoice->SetStringSelection(wxT("BLACK"));
      }

      if (underLineCheckBox)
      {
            underLineCheckBox->SetValue(dialogFont.GetUnderlined());
      }

      //    pointSizeChoice->SetSelection(dialogFont.GetPointSize()-1);
      pointSizeChoice->SetSelection(0);

      #if !defined(__SMARTPHONE__) && !defined(__POCKETPC__)
      GetSizer()->SetItemMinSize(m_previewer, is_pda ? 100 : 430, is_pda ? 40 : 100);
      GetSizer()->SetSizeHints(this);
      GetSizer()->Fit(this);

      Centre(wxBOTH);
      #endif
      */


      // Don't block events any more
      m_useEvents = true;

}


void X11FontPicker::OnChangeFace ( wxCommandEvent& WXUNUSED ( event ) )
{
      if ( !m_useEvents ) return;

      //    Capture the current selections
      wxString facename = familyChoice->GetStringSelection();
      wxString pointsize = pointSizeChoice->GetStringSelection();
      wxString weight = weightChoice->GetStringSelection();


      SetChoiceOptionsFromFacename ( facename );

      //    Reset the choices
      familyChoice->SetStringSelection ( facename );
      weightChoice->SetStringSelection ( weight );
      pointSizeChoice->SetStringSelection ( pointsize );

      //    And make the font change
      DoFontChange();

}


void X11FontPicker::SetChoiceOptionsFromFacename ( wxString &facename )
{
      //    Get a list of matching fonts
      char face[100];
      strncpy ( face, facename.mb_str(), 100 );

      char pattern[100];
      sprintf ( pattern, "-*-%s-*-*-*-*-*-*-*-*-*-*-iso8859-1", face );
//    wxString pattern;
//    pattern.Printf(wxT("-*-%s-*-*-*-*-*-*-*-*-*-*-iso8859-1"), facename.mb_str());

      int nFonts;
      char ** list = XListFonts ( ( Display * ) wxGetDisplay(), pattern, 32767, &nFonts );

      //    First, look thru all the point sizes looking for "0" to indicate scaleable (e.g. TrueType) font
      bool scaleable = false;
      for ( int i=0 ; i < nFonts ; i++ )
      {
            wxStringTokenizer st ( wxString ( list[i] ), _T ( "-" ) );
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            wxString pointsize = st.GetNextToken();

            if ( pointsize.IsSameAs ( _T ( "0" ) ) )
            {
                  scaleable = true;
                  break;
            }
      }


      // make different pointsize selections for scaleable fonts
      wxArrayString PointSizeArray;

      if ( scaleable )
      {
            for ( int j=0 ; j < SCALEABLE_SIZES ; j++ )
                  PointSizeArray.Add ( scaleable_pointsize[j] );
      }

      else
      {
            //Get the Point Sizes Array
            unsigned int jname;
            for ( int i=0 ; i < nFonts ; i++ )
            {
//                  printf("%s\n", list[i]);
                  wxStringTokenizer st ( wxString ( list[i] ), _T ( "-" ) );
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  wxString pointsize = st.GetNextToken();
                  //           printf("%s\n",facename.mb_str());
                  for ( jname=0 ; jname<PointSizeArray.GetCount() ; jname++ )
                  {
                        if ( pointsize == PointSizeArray.Item ( jname ) )
                              break;
                  }
                  if ( jname >= PointSizeArray.GetCount() )
                  {
                        PointSizeArray.Add ( pointsize );
//                        printf("Added %s\n", pointsize.mb_str());
                  }
            }
      }
      pointSizeChoice->Clear();
      pointSizeChoice->Append ( PointSizeArray );
      pointSizeChoice->SetSelection ( 0 );

      //Get the Weight Array
      wxArrayString WeightArray;
      for ( int i=0 ; i < nFonts ; i++ )
      {
//            printf("%s\n", list[i]);
            wxStringTokenizer st ( wxString ( list[i] ), _T ( "-" ) );
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            wxString weight = st.GetNextToken();
            //           printf("%s\n",facename.mb_str());
            unsigned int jname;
            for ( jname=0 ; jname<WeightArray.GetCount() ; jname++ )
            {
                  if ( weight == WeightArray.Item ( jname ) )
                        break;
            }
            if ( jname >= WeightArray.GetCount() )
            {
                  WeightArray.Add ( weight );
//                  printf("Added weight %s\n", weight.mb_str());
            }
      }

      weightChoice->Clear();
      weightChoice->Append ( WeightArray );
      weightChoice->SetSelection ( 0 );

}





void X11FontPicker::InitializeFont()
{
      int fontFamily = wxSWISS;
      int fontWeight = wxNORMAL;
      int fontStyle = wxNORMAL;
      int fontSize = 12;
      bool fontUnderline = false;

      wxString fontnative;
      if ( m_fontData.m_initialFont.Ok() )
      {
            fontnative = m_fontData.m_initialFont.GetNativeFontInfoDesc();
            fontFamily = m_fontData.m_initialFont.GetFamily();
            fontWeight = m_fontData.m_initialFont.GetWeight();
            fontStyle = m_fontData.m_initialFont.GetStyle();
            fontSize = m_fontData.m_initialFont.GetPointSize();
            fontUnderline = m_fontData.m_initialFont.GetUnderlined();
      }

//      printf("Init Fetching    %s\n", fontnative.mb_str());

      wxFont tFont = wxFont ( fontSize, fontFamily, fontStyle,
                              fontWeight, fontUnderline );

      wxFont *pdialogFont = tFont.New ( fontnative );

      //    Confirm
      /*
            wxNativeFontInfo *i = (wxNativeFontInfo *)pdialogFont->GetNativeFontInfo();

            XFontStruct *xfont = (XFontStruct*) pdialogFont->GetFontStruct( 1.0, (Display *)wxGetDisplay() );
            unsigned long ret;
            XGetFontProperty(xfont, 18, &ret);
            char* x = XGetAtomName((Display *)wxGetDisplay(), ret);
            printf(" Init Got %s\n", x);
      */

      dialogFont = *pdialogFont;

}

void X11FontPicker::OnChangeFont ( wxCommandEvent& WXUNUSED ( event ) )
{
      if ( !m_useEvents ) return;

      DoFontChange();
}


void X11FontPicker::DoFontChange ( void )
{
      wxString facename = familyChoice->GetStringSelection();
      wxString pointsize = pointSizeChoice->GetStringSelection();
      wxString weight = weightChoice->GetStringSelection();

      char font_x[200];
      sprintf ( font_x,"-*-%s-%s-r-normal-*-*-%s0-*-*-*-*-iso8859-1", facename.mb_str(), weight.mb_str(), pointsize.mb_str() );
      wxString font_xlfd ( font_x,  wxConvUTF8 );


//                  printf("Fetching    %s\n", font_xlfd.mb_str());

      XFontStruct *test = XLoadQueryFont ( ( Display * ) wxGetDisplay(),font_xlfd.mb_str() );

      //    Confirm
      /*
                        unsigned long ret0;
                        if(test)
      {
                        XGetFontProperty(test, 18, &ret0);
                        char* x = XGetAtomName((Display *)wxGetDisplay(), ret0);
                        printf("FGot %s\n", x);
      }
      */
      if ( test )
      {
            font_xlfd.Prepend ( "0;" );
            wxFont *ptf = new wxFont;
            pPreviewFont = ptf->New ( font_xlfd );

            /*
                  wxNativeFontInfo *i = (wxNativeFontInfo *)pPreviewFont->GetNativeFontInfo();

                  XFontStruct *xfont = (XFontStruct*) pPreviewFont->GetFontStruct( 1.0, (Display *)wxGetDisplay() );
                  unsigned long ret;
                  XGetFontProperty(xfont, 18, &ret);
                  char* x = XGetAtomName((Display *)wxGetDisplay(), ret);
                  printf("Got %s\n", x);
            */
            m_previewer->SetName ( _T( "ABCDEFGabcdefg12345" ) );
            m_previewer->SetFont ( *pPreviewFont );
            m_previewer->Refresh();
      }

      else
      {
            wxString err ( _T ( "No Font:" ) );
            err.Append ( font_xlfd );
            m_previewer->SetName ( err );
            m_previewer->SetFont ( *pPreviewFont );
            m_previewer->Refresh();
      }


      /*
      int fontFamily = wxFontFamilyStringToInt(WXSTRINGCAST familyChoice->GetStringSelection());
      int fontWeight = wxFontWeightStringToInt(WXSTRINGCAST weightChoice->GetStringSelection());
      int fontStyle = wxFontStyleStringToInt(WXSTRINGCAST styleChoice->GetStringSelection());
      int fontSize = wxAtoi(pointSizeChoice->GetStringSelection());
      // Start with previous underline setting, we want to retain it even if we can't edit it
      // dialogFont is always initialized because of the call to InitializeFont
      int fontUnderline = dialogFont.GetUnderlined();

      if (underLineCheckBox)
      {
            fontUnderline = underLineCheckBox->GetValue();
      }

      dialogFont = wxFont(fontSize, fontFamily, fontStyle, fontWeight, (fontUnderline != 0));
      m_previewer->SetFont(dialogFont);

      if ( colourChoice )
      {
            if ( !colourChoice->GetStringSelection().empty() )
      {
                  wxColour col = wxTheColourDatabase->Find(colourChoice->GetStringSelection());
                  if (col.Ok())
      {
                        m_fontData.m_fontColour = col;
      }
      }
      }
      // Update color here so that we can also use the color originally passed in
      // (EnableEffects may be false)
      if (m_fontData.m_fontColour.Ok())
            m_previewer->SetForegroundColour(m_fontData.m_fontColour);

      m_previewer->Refresh();
      */
}

#endif            //__WXX11__


//---------------------------------------------------------------------------------
//          Vector Stuff for Hit Test Algorithm
//---------------------------------------------------------------------------------
double vGetLengthOfNormal ( PVECTOR2D a, PVECTOR2D b, PVECTOR2D n )
{
      VECTOR2D c, vNormal;
      //
      //Obtain projection vector.
      //
      //c = ((a * b)/(|b|^2))*b
      //
      c.x = b->x * ( vDotProduct ( a, b ) /vDotProduct ( b, b ) );
      c.y = b->y * ( vDotProduct ( a, b ) /vDotProduct ( b, b ) );
//
      //Obtain perpendicular projection : e = a - c
      //
      vSubtractVectors ( a, &c, &vNormal );
      //
      //Fill PROJECTION structure with appropriate values.
      //
      *n = vNormal;

      return ( vVectorMagnitude ( &vNormal ) );
}

double vDotProduct ( PVECTOR2D v0, PVECTOR2D v1 )
{
      double dotprod;

      dotprod = ( v0 == NULL || v1 == NULL )
                ? 0.0
                : ( v0->x * v1->x ) + ( v0->y * v1->y );

      return ( dotprod );
}

PVECTOR2D vAddVectors ( PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v )
{
      if ( v0 == NULL || v1 == NULL )
            v = ( PVECTOR2D ) NULL;
      else
      {
            v->x = v0->x + v1->x;
            v->y = v0->y + v1->y;
      }
      return ( v );
}


PVECTOR2D vSubtractVectors ( PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v )
{
      if ( v0 == NULL || v1 == NULL )
            v = ( PVECTOR2D ) NULL;
      else
      {
            v->x = v0->x - v1->x;
            v->y = v0->y - v1->y;
      }
      return ( v );
}

double vVectorSquared ( PVECTOR2D v0 )
{
      double dS;

      if ( v0 == NULL )
            dS = 0.0;
      else
            dS = ( ( v0->x * v0->x ) + ( v0->y * v0->y ) );
      return ( dS );
}

double vVectorMagnitude ( PVECTOR2D v0 )
{
      double dMagnitude;

      if ( v0 == NULL )
            dMagnitude = 0.0;
      else
            dMagnitude = sqrt ( vVectorSquared ( v0 ) );
      return ( dMagnitude );
}


/**************************************************************************/
/*          LogMessageOnce                                                */
/**************************************************************************/

bool LogMessageOnce ( wxString &msg )
{
      //    Search the array for a match

      for ( unsigned int i=0 ; i < pMessageOnceArray->GetCount() ; i++ )
      {
            if ( msg.IsSameAs ( pMessageOnceArray->Item ( i ) ) )
                  return false;
      }

      // Not found, so add to the array
      pMessageOnceArray->Add ( msg );

      //    And print it
      wxLogMessage ( msg );
      return true;
}


/**************************************************************************/
/*          Some assorted utilities                                       */
/**************************************************************************/

wxString toSDMM ( int NEflag, double a )
{
      short neg = 0;
      int d;
      long m;

      if ( a < 0.0 )
      {
            a = -a;
            neg = 1;
      }
      d = ( int ) a;
      m = ( long ) ( ( a - ( double ) d ) * 60000.0 );

      if ( neg )
            d = -d;

      wxString s;

      if ( !NEflag )
            s.Printf ( _T ( "%d %02ld.%03ld'" ), d, m / 1000, m % 1000 );
      else
      {
            if ( NEflag == 1 )
            {
                  char c = 'N';

                  if ( neg )
                  {
                        d = -d;
                        c = 'S';
                  }

                  s.Printf ( _T ( "%03d %02ld.%03ld %c" ), d, m / 1000, ( m % 1000 ), c );
            }
            else if ( NEflag == 2 )
            {
                  char c = 'E';

                  if ( neg )
                  {
                        d = -d;
                        c = 'W';
                  }
                  s.Printf ( _T ( "%03d %02ld.%03ld %c" ), d, m / 1000, ( m % 1000 ), c );
            }
      }
      return s;
}

//    TTYScroll and TTYWindow Implemetation

IMPLEMENT_DYNAMIC_CLASS( TTYWindow, wxDialog )

            BEGIN_EVENT_TABLE( TTYWindow, wxDialog )
            EVT_CLOSE(TTYWindow::OnCloseWindow)
            EVT_MOVE( TTYWindow::OnMove )
            EVT_SIZE( TTYWindow::OnSize )
            END_EVENT_TABLE()


TTYWindow::TTYWindow()
{
}

TTYWindow::~TTYWindow()
{
      delete m_pScroll;
      g_NMEALogWindow = NULL;
}

void TTYWindow::OnCloseWindow(wxCloseEvent& event)
{
      Destroy();
}

void TTYWindow::OnSize(wxSizeEvent& event)
{
      //    Record the dialog size
      wxSize p = event.GetSize();
      g_NMEALogWindow_sx = p.x;
      g_NMEALogWindow_sy = p.y;

      event.Skip();
}

void TTYWindow::OnMove( wxMoveEvent& event )
{
      //    Record the dialog position
      wxPoint p = event.GetPosition();
      g_NMEALogWindow_x = p.x;
      g_NMEALogWindow_y = p.y;

      event.Skip();
}


void TTYScroll::Add(wxString &line)
{
      if(m_plineArray->GetCount() > m_nLines-1)
      {                                         // shuffle the arraystring
            wxArrayString *p_newArray = new wxArrayString;

            for(unsigned int i=1 ; i < m_plineArray->GetCount() ; i++)
            {
                  p_newArray->Add(m_plineArray->Item(i));
            }
            delete m_plineArray;
            m_plineArray = p_newArray;
      }

      m_plineArray->Add(line);
}

void TTYScroll::OnDraw(wxDC& dc)
{
    // update region is always in device coords, translate to logical ones
      wxRect rectUpdate = GetUpdateRegion().GetBox();
      CalcUnscrolledPosition(rectUpdate.x, rectUpdate.y,
                             &rectUpdate.x, &rectUpdate.y);


      size_t lineFrom = rectUpdate.y / m_hLine,
      lineTo = rectUpdate.GetBottom() / m_hLine;

      if ( lineTo > m_nLines - 1)
            lineTo = m_nLines - 1;

      wxCoord y = lineFrom*m_hLine;
      for ( size_t line = lineFrom; line <= lineTo; line++ )
      {
            wxCoord yPhys;
            CalcScrolledPosition(0, y, NULL, &yPhys);

            dc.DrawText(m_plineArray->Item(line), 0, y);
            y += m_hLine;
      }
}


void TTYWindow::Add(wxString &line)
{
      if(m_pScroll)
            m_pScroll->Add(line);
}



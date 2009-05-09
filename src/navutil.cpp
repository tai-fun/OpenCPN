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
 * Revision 1.14  2008/04/20 20:54:40  bdbcat
 * Set defaults
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
 * $Log: navutil.cpp,v $
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

#ifdef USE_S57
#include "s52plib.h"
#endif

CPL_CVSID("$Id: navutil.cpp,v 1.27 2009/05/09 01:30:52 bdbcat Exp $");

//    Statics

extern ChartBase        *Current_Ch;
extern ChartCanvas      *cc1;
extern MyFrame          *gFrame;
extern NMEAWindow       *g_pnmea;
extern FontMgr          *pFontMgr;

extern RouteList        *pRouteList;
extern Select           *pSelect;
extern MyConfig         *pConfig;
extern wxArrayString    *pChartDirArray;
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
extern wxString         *g_pPresLibData;

extern bool             g_bShowPrintIcon;
extern AutoPilotWindow  *pAPilot;
extern wxString         *pAIS_Port;
extern AIS_Decoder      *pAIS;
extern wxString         *pSData_Locn;
extern wxString         *pInit_Chart_Dir;
extern WayPointman      *pWayPointMan;
extern Routeman         *pRouteMan;
extern ComPortManager   *g_pCommMan;

extern bool             s_bSetSystemTime;
extern bool             g_bShowDepthUnits;
extern bool             g_bAutoAnchorMark;
extern bool             g_bShowOutlines;
extern bool             g_bGarminPersistance;
extern bool             g_bNMEADebug;

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
extern double           g_ShowTracks_Mins;
extern bool             g_bShowMoored;
extern double           g_ShowMoored_Kts;

extern bool             g_bShowPrintIcon;
extern bool             g_bShowGPXIcons;              // toh, 2009.02.14
extern bool             g_bNavAidShowRadarRings;            // toh, 2009.02.24
extern int              g_iNavAidRadarRingsNumberVisible;   // toh, 2009.02.24
extern float            g_fNavAidRadarRingsStep;            // toh, 2009.02.24
extern int              g_pNavAidRadarRingsStepUnits;       // toh, 2009.02.24
extern bool             g_bWayPointPreventDragging;         // toh, 2009.02.24


#ifdef USE_S57
extern s52plib          *ps52plib;
#endif

//------------------------------------------------------------------------------
// Some wxWidgets macros for useful classes
//------------------------------------------------------------------------------
WX_DEFINE_LIST(RouteList);
WX_DEFINE_LIST(SelectableItemList);
WX_DEFINE_LIST(RoutePointList);
WX_DEFINE_LIST(HyperlinkList);            // toh, 2009.02.22

//-----------------------------------------------------------------------------
//          Select
//-----------------------------------------------------------------------------

Select::Select()
{
      pSelectList = new SelectableItemList;
}

Select::~Select()
{
      pSelectList->DeleteContents(true);
      pSelectList->Clear();
      delete pSelectList;


}

bool Select::AddSelectablePoint(float slat, float slon, RoutePoint *pRoutePointAdd)
{
      SelectItem *pSelItem = new SelectItem;
      pSelItem->m_slat = slat;
      pSelItem->m_slon = slon;
      pSelItem->m_seltype = SELTYPE_ROUTEPOINT;
      pSelItem->m_bIsSelected = false;
      pSelItem->m_pData1 = pRoutePointAdd;

      pSelectList->Append(pSelItem);

      return true;
}

bool Select::AddSelectableRouteSegment(float slat1, float slon1, float slat2, float slon2,
                                                         RoutePoint *pRoutePointAdd1, RoutePoint *pRoutePointAdd2)
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

      pSelectList->Append(pSelItem);

      return true;
}

bool Select::DeleteAllSelectableRouteSegments(Route *pr)
{
      SelectItem *pFindSel;

//    Iterate on the select list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while(node)
      {
          pFindSel = node->GetData();
            if(pFindSel->m_seltype == SELTYPE_ROUTESEGMENT)
            {
                  //    inner loop iterates on the route's point list
                  wxRoutePointListNode *pnode = (pr->pRoutePointList)->GetFirst();
                  while (pnode)
                  {
                        RoutePoint *prp = pnode->GetData();
                        RoutePoint *ps = (RoutePoint *)pFindSel->m_pData1;
                        if(prp == ps)
                        {
                              delete pFindSel;
                              pSelectList->DeleteNode(node);      //delete node;
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


bool Select::DeleteAllSelectableRoutePoints(Route *pr)
{
      SelectItem *pFindSel;

//    Iterate on the select list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while(node)
      {
          pFindSel = node->GetData();
            if(pFindSel->m_seltype == SELTYPE_ROUTEPOINT)
            {
                  RoutePoint *ps = (RoutePoint *)pFindSel->m_pData1;

                  //    inner loop iterates on the route's point list
                  wxRoutePointListNode *pnode = (pr->pRoutePointList)->GetFirst();
                  while (pnode)
                  {
                        RoutePoint *prp = pnode->GetData();

                        if(prp == ps)
                        {
                              delete pFindSel;
                              pSelectList->DeleteNode(node);      //delete node;
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


bool Select::AddAllSelectableRoutePoints(Route *pr)
{
      if(pr->pRoutePointList->GetCount())
      {
            wxRoutePointListNode *node = (pr->pRoutePointList)->GetFirst();

            while (node)
            {
                  RoutePoint *prp = node->GetData();
                  AddSelectablePoint(prp->m_lat, prp->m_lon, prp);
                  node = node->GetNext();
            }
            return true;
      }
      else
            return false;
}

bool Select::AddAllSelectableRouteSegments(Route *pr)
{
      wxPoint rpt, rptn;
      float slat1, slon1, slat2, slon2;

      if(pr->pRoutePointList->GetCount())
      {
            wxRoutePointListNode *node = (pr->pRoutePointList)->GetFirst();

            RoutePoint *prp0 = node->GetData();
            slat1 = prp0->m_lat;
            slon1 = prp0->m_lon;

            node = node->GetNext();

            while (node)
            {
                  RoutePoint *prp = node->GetData();
                  slat2 = prp->m_lat;
                  slon2 = prp->m_lon;

                  AddSelectableRouteSegment(slat1, slon1, slat2, slon2, prp0, prp);

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

bool Select::UpdateSelectableRouteSegments(RoutePoint *prp)
{
      SelectItem *pFindSel;
      bool ret = false;

//    Iterate on the select list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while(node)
      {
            pFindSel = node->GetData();
            if(pFindSel->m_seltype == SELTYPE_ROUTESEGMENT)
            {
                  if(pFindSel->m_pData1 == prp)
                  {
                        pFindSel->m_slat = prp->m_lat;
                        pFindSel->m_slon = prp->m_lon;
                        ret = true;;
                  }

                  else if(pFindSel->m_pData2 == prp)
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

bool Select::AddSelectablePoint(float slat, float slon, void *data, int fseltype)
{
      SelectItem *pSelItem = new SelectItem;
      pSelItem->m_slat = slat;
      pSelItem->m_slon = slon;
      pSelItem->m_seltype = fseltype;
      pSelItem->m_bIsSelected = false;
      pSelItem->m_pData1 = data;

      pSelectList->Append(pSelItem);

      return true;
}

bool Select::DeleteAllPoints(void)
{
      pSelectList->DeleteContents(true);
      pSelectList->Clear();
      return true;
}


bool Select::DeleteSelectablePoint(void *data, int SeltypeToDelete)
{
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while(node)
      {
            pFindSel = node->GetData();
            if(pFindSel->m_seltype == SeltypeToDelete)
            {
                if(data == pFindSel->m_pData1)
                {
                  delete pFindSel;
                  delete node;
                  return true;
                }
            }

            node = node->GetNext();
       }
      return false;
}


bool Select::DeleteAllSelectableTypePoints(int SeltypeToDelete)
{
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while(node)
      {
            pFindSel = node->GetData();
            if(pFindSel->m_seltype == SeltypeToDelete)
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

bool Select::ModifySelectablePoint(float lat, float lon, void *data, int SeltypeToModify)
{
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

      while(node)
      {
            pFindSel = node->GetData();
            if(pFindSel->m_seltype == SeltypeToModify)
            {
                if(data == pFindSel->m_pData1)
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



SelectItem *Select::FindSelection(float slat, float slon, int fseltype, float SelectRadius)
{
      float a,b,c,d;
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

                  while(node)
                  {
                      pFindSel = node->GetData();
                        if(pFindSel->m_seltype == fseltype)
                        {
                              switch(fseltype)
                              {
                              case SELTYPE_ROUTEPOINT:
                              case SELTYPE_TIDEPOINT:
                              case SELTYPE_CURRENTPOINT:
                              case SELTYPE_AISTARGET:
                                    a = fabs(slat - pFindSel->m_slat);
                                    b = fabs(slon - pFindSel->m_slon);

                                    if((fabs(slat - pFindSel->m_slat) < SelectRadius) &&
                                       (fabs(slon - pFindSel->m_slon) < SelectRadius))
                                          goto find_ok;
                                    break;
                              case SELTYPE_ROUTESEGMENT:
                                    a = pFindSel->m_slat;
                                    b = pFindSel->m_slat2;
                                    c = pFindSel->m_slon;
                                    d = pFindSel->m_slon2;

//    As a course test, use segment bounding box test
                                    if( (slat >= (fmin(a,b) - SelectRadius)) && (slat <= (fmax(a,b) + SelectRadius)) &&
                                         (slon >= (fmin(c,d) - SelectRadius)) && (slon <= (fmax(c,d) + SelectRadius))  )
                                    {
//    Use vectors to do hit test....
                                          VECTOR2D va, vb, vn;

                                          va.x = slon - c;
                                          va.y = slat - a;
                                          vb.x = d - c;
                                          vb.y = b - a;

                                          double delta = vGetLengthOfNormal(&va, &vb, &vn);
                                          if(fabs(delta) < SelectRadius)
                                                goto find_ok;
                                    }

                                    break;
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
RoutePoint::RoutePoint(double lat, double lon, const wxString& icon_ident, const wxString& name, wxString *pGUID)
{
      //  Establish points
      m_lat = lat;
      m_lon = lon;

      //  Nice defaults
      m_seg_len = 0.0;
      m_bDynamicName = false;
      m_bPtIsSelected = false;
      m_bIsBeingEdited = false;
      m_bIsActive = false;
      m_bBlink = false;
      m_bIsInRoute = false;
      m_bShowName = true;
      m_ConfigWPNum = -1;
      CurrentRect_in_DC = wxRect(0,0,0,0);
      m_NameLocationOffsetX = -10;
      m_NameLocationOffsetY = 8;

      // toh, 2009.02.22
      m_HyperlinkList = new HyperlinkList;

      wxString GUID = pWayPointMan->CreateGUID(this);

      if(NULL != pGUID)
      {
          if(pGUID->IsEmpty())
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

      if(NULL != pWayPointMan)
        pWayPointMan->m_pWayPointList->Append(this);
}


RoutePoint::~RoutePoint(void)
{
//  Remove this point from the global waypoint list
    if(NULL != pWayPointMan)
        pWayPointMan->m_pWayPointList->DeleteObject(this);
}

void RoutePoint::ReLoadIcon(void)
{
      m_pbmIcon = pWayPointMan->GetIconBitmap(m_IconName);
}


void RoutePoint::DrawPoint(wxDC& dc, wxPoint *rpn)
{
      wxPoint r;
      wxRect            hilitebox;
      unsigned char transparency = 200;

      wxPen *pen;
      if(m_bBlink)
            pen = pRouteMan->GetActiveRoutePointPen();
      else
            pen = pRouteMan->GetRoutePointPen();

      unsigned char ol_red   = pen->GetColour().Red(); //50;
      unsigned char ol_green = pen->GetColour().Green(); //100;
      unsigned char ol_blue  = pen->GetColour().Blue(); //255;

      cc1->GetPointPix(m_lat, m_lon, &r);

//    Substitue icon?
      wxBitmap *pbm;
      if(m_bIsActive)
            pbm = pWayPointMan->GetIconBitmap(_T("activepoint"));
      else
            pbm =m_pbmIcon;

      int sx2 = pbm->GetWidth()/2;
      int sy2 = pbm->GetHeight()/2;



//    Calculate the mark drawing extents
      wxRect r1(r.x-sx2, r.y-sy2, sx2 * 2, sy2 * 2);
      if(m_bShowName)
      {
            dc.SetFont(*pFontMgr->GetFont(_T("Marks")));
            int stextx, stexty;
            dc.GetTextExtent(m_MarkName, &stextx, &stexty);
            wxRect r2(r.x + m_NameLocationOffsetX, r.y + m_NameLocationOffsetY, stextx, stexty);
            r1.Union(r2);
      }
      hilitebox = r1;
      hilitebox.x -= r.x;
      hilitebox.y -= r.y;
      hilitebox.Inflate(2);

      //  Highlite any selected point
      if(m_bPtIsSelected)
      {
            DrawTransparentBox(dc, r.x + hilitebox.x, r.y + hilitebox.y, hilitebox.width, hilitebox.height,
                               ol_red, ol_green, ol_blue, transparency);
      }

      bool bDrawHL = false;

      if(m_bBlink && (gFrame->nBlinkerTick & 1))
            bDrawHL = true;

      if((!bDrawHL) && (NULL != m_pbmIcon))
      {
                  dc.DrawBitmap(*pbm, r.x - sx2, r.y - sy2, true);
            // on MSW, the dc Bounding box is not updated on DrawBitmap() method.
            // Do it explicitely here for all platforms.
                  dc.CalcBoundingBox(r.x - sx2, r.y - sy2);
                  dc.CalcBoundingBox(r.x + sx2, r.y + sy2);

      }

      if(m_bShowName)
      {
            dc.SetFont(*pFontMgr->GetFont(_T("Marks")));
            dc.DrawText(m_MarkName, r.x + m_NameLocationOffsetX, r.y + m_NameLocationOffsetY);
      }


      //  return the home point in this dc to allow "connect the dots"
      if(NULL != rpn)
            *rpn = r;

      //  Save the current draw rectangle in the current DC
      //    This will be useful for fast icon redraws
      CurrentRect_in_DC.x      = r.x + hilitebox.x;
      CurrentRect_in_DC.y      = r.y + hilitebox.y;
      CurrentRect_in_DC.width  = hilitebox.width;
      CurrentRect_in_DC.height = hilitebox.height;



      if(m_bBlink)
            g_blink_rect = CurrentRect_in_DC;               // also save for global blinker

}

void RoutePoint::DrawTransparentBox(wxDC& dc, int x, int y, int size_x, int size_y,
                                    unsigned char rval, unsigned char gval, unsigned char bval, unsigned char transparency)
{

      //    Get wxImage of area of interest
      wxBitmap obm(size_x, size_y);
      wxMemoryDC mdc1;
      mdc1.SelectObject(obm);
      mdc1.Blit(0, 0, size_x, size_y, &dc, x, y);
      mdc1.SelectObject(wxNullBitmap);
      wxImage oim = obm.ConvertToImage();

      //    Create an image with selected transparency/color
      int olay_red   = rval * transparency;
      int olay_green = gval * transparency;
      int olay_blue  = bval * transparency;

      //    Create destination image
      wxImage dest(size_x, size_y, false);
      unsigned char *dest_data = (unsigned char *)malloc(size_x * size_y * 3 * sizeof(unsigned char));
      unsigned char *po = oim.GetData();
      unsigned char *d = dest_data;

      int sb = size_x * size_y;
      for(int i=0 ; i<sb ; i++)
      {
            int r = ((*po++) * 255) + olay_red;
            *d++ = (unsigned char)(r / 512);
            int g = ((*po++) * 255) + olay_green;
            *d++ = (unsigned char)(g / 512);
            int b = ((*po++) * 255) + olay_blue;
            *d++ = (unsigned char)(b / 512);
      }

      dest.SetData(dest_data);

      //    Convert destination to bitmap and draw it
      wxBitmap dbm(dest);
      dc.DrawBitmap(dbm, x, y, false);

      // on MSW, the dc Bounding box is not updated on DrawBitmap() method.
      // Do it explicitely here for all platforms.
      dc.CalcBoundingBox(x, y);
      dc.CalcBoundingBox(x + size_x, y + size_y);

}

void RoutePoint::SetPosition(double lat, double lon)
{
      m_lat = lat;
      m_lon = lon;
}


void RoutePoint::CalculateDCRect(wxDC& dc, wxRect *prect)
{
      dc.ResetBoundingBox();
      dc.DestroyClippingRegion();

    // Draw the mark on the dc
      DrawPoint(dc, NULL);

    //  Retrieve the drawing extents
      prect->x = dc.MinX() - 1;
      prect->y = dc.MinY() - 1;
      prect->width  = dc.MaxX() - dc.MinX() + 2; // Mouse Poop?
      prect->height = dc.MaxY() - dc.MinY() + 2;

}

// toh, 2009.02.23
bool RoutePoint::IsSame(RoutePoint *pOtherRP)
{
      bool IsSame = false;

      if (this->m_MarkName == pOtherRP->m_MarkName)
      {
            if (fabs(this->m_lat-pOtherRP->m_lat) < 1.e-6 && fabs(this->m_lon-pOtherRP->m_lon) < 1.e-6)
                  IsSame = true;
      }
      return IsSame;
}




//-----------------------------------------------------------------------------
//          Route Implementation
//-----------------------------------------------------------------------------

Route::Route(void)
{
      m_bRtIsSelected = false;
      m_bRtIsActive = false;
      m_pRouteActivePoint = NULL;
      m_bIsBeingEdited = false;
      m_bIsBeingCreated = false;
      m_nPoints = 0;
      m_nm_sequence = 1;

      pRoutePointList = new RoutePointList;

      BBox.Reset();
}


Route::~Route(void)
{
      pRoutePointList->DeleteContents(false);               // do not delete Marks
      pRoutePointList->Clear();
      delete pRoutePointList;
}


void Route::AddPoint(RoutePoint *pNewPoint)
{
      pNewPoint->m_bIsInRoute = true;

      pRoutePointList->Append(pNewPoint);

      m_nPoints++;

      CalculateBBox();
      UpdateSegmentDistances();

      if(pNewPoint->m_MarkName.IsEmpty())
      {
            pNewPoint->m_MarkName.Printf(_T("%03d"), m_nPoints);
            pNewPoint->m_bDynamicName = true;
      }
      return;
}


void Route::AddTentativePoint(const wxString& GUID)
{
      RoutePointGUIDList.Add(GUID);
      return;
}





RoutePoint *Route::GetPoint(int nWhichPoint)
{
      RoutePoint *prp;
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      int i=1;
      while (node)
      {
            prp = node->GetData();
            if(i == nWhichPoint)
                  return prp;

            i++;
            node = node->GetNext();
      }

      return(NULL);
}

void Route::DrawPointWhich(wxDC& dc, int iPoint, wxPoint *rpn)
{
      GetPoint(iPoint)->DrawPoint(dc, rpn);
}



void Route::DrawSegment(wxDC& dc, wxPoint *rp1, wxPoint *rp2, double scale_ppm, bool bdraw_arrow)
{
      if(m_bRtIsSelected)
            dc.SetPen(*pRouteMan->GetSelectedRoutePen());
      else if(m_bRtIsActive)
            dc.SetPen(*pRouteMan->GetActiveRoutePen());
      else
            dc.SetPen(*pRouteMan->GetRoutePen());

      DrawRouteLine(dc, rp1->x, rp1->y, rp2->x, rp2->y, scale_ppm, bdraw_arrow);            // with clipping
}




void Route::DrawRoute(wxDC& dc, double scale_ppm)
{

      if(m_bRtIsSelected)
      {
            dc.SetPen(*pRouteMan->GetRoutePen());
            dc.SetBrush(*pRouteMan->GetRouteBrush());
      }
      else if(m_bRtIsActive)
      {
            dc.SetPen(*pRouteMan->GetActiveRoutePen());
            dc.SetBrush(*pRouteMan->GetActiveRouteBrush());
      }
      else
      {
            dc.SetPen(*pRouteMan->GetRoutePen());
            dc.SetBrush(*pRouteMan->GetRouteBrush());
      }



      wxPoint rpt, rptn;
      DrawPointWhich(dc, 1, &rpt);

      wxRoutePointListNode *node = pRoutePointList->GetFirst();
      node = node->GetNext();

      while (node)
      {

            RoutePoint *prp = node->GetData();
            prp->DrawPoint(dc, &rptn);
            DrawRouteLine(dc, rpt.x, rpt.y, rptn.x, rptn.y, scale_ppm, true);            // with clipping
            rpt = rptn;

            node = node->GetNext();
      }
}

static int s_arrow_icon[] = {
      0, 0,
      5, 2,
      18, 6,
      12, 0,
      18,-6,
      5, -2,
      0, 0
};

void Route::DrawRouteLine(wxDC& dc, int xa, int ya, int xb, int yb, double scale_ppm, bool bdraw_arrow)
{
      //    Get the dc boundary
      int sx, sy;
      dc.GetSize(&sx, &sy);

      //    Clip the line segment to the dc boundary
      int x0 = xa;
      int y0 = ya;
      int x1 = xb;
      int y1 = yb;

      if(Visible == cohen_sutherland_line_clip_i (&x0, &y0, &x1, &y1, 0, sx, 0, sy))
            dc.DrawLine(x0, y0, x1, y1);

      if(bdraw_arrow)
      {
      //    Draw a direction arrow

            double theta = atan2((yb-ya), (xb-xa));
            theta -= PI / 2;


            wxPoint icon[10];
            double icon_scale_factor = 100 * scale_ppm;
            icon_scale_factor = fmin(icon_scale_factor, 1.5);
            icon_scale_factor = fmax(icon_scale_factor, 1.0);

            for ( int i=0; i<7; i++ )
            {
                  int j = i * 2;
                  double pxa = ( double ) (s_arrow_icon[j]  );
                  double pya = ( double ) (s_arrow_icon[j+1]);

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


RoutePoint *Route::InsertPointBefore(RoutePoint *pRP, float rlat, float rlon, bool bRenamePoints)
{
      RoutePoint *newpoint = new RoutePoint(rlat, rlon, wxString(_T("diamond")), GetNewMarkSequenced(), NULL);
      newpoint->m_bIsInRoute = true;
      newpoint->m_bDynamicName = false;  //true;

      int nRP = pRoutePointList->IndexOf(pRP);
      pRoutePointList->Insert(nRP, newpoint);

      RoutePointGUIDList.Insert(pRP->m_GUID, nRP);

      m_nPoints++;

      if(bRenamePoints)
            RenameRoutePoints();

      CalculateBBox();
      UpdateSegmentDistances();

      return(newpoint);
}


wxString Route::GetNewMarkSequenced(void)
{
      wxString ret;
      ret.Printf(_T("NM%03d"), m_nm_sequence);
      m_nm_sequence++;

      return ret;
}

RoutePoint *Route::GetLastPoint()
{
      RoutePoint *data_m1 = NULL;
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      while (node)
      {
            data_m1 = node->GetData();
            node = node->GetNext();
      }
      return(data_m1);
}

int Route::GetIndexOf(RoutePoint *prp)
{
      int ret = pRoutePointList->IndexOf(prp) + 1;
      if(ret == wxNOT_FOUND)
            return 0;
      else
            return ret;

}

void Route::DeletePoint(RoutePoint *rp, bool bRenamePoints)
{
      pRoutePointList->DeleteObject(rp);
      RoutePointGUIDList.Remove(rp->m_GUID);

      delete rp;

      m_nPoints -= 1;

      if(bRenamePoints)
            RenameRoutePoints();

      CalculateBBox();
      UpdateSegmentDistances();
}

void Route::RemovePoint(RoutePoint *rp, bool bRenamePoints)
{
      pRoutePointList->DeleteObject(rp);
      RoutePointGUIDList.Remove(rp->m_GUID);
      m_nPoints -= 1;


      // check all other routes to see if this point appears in any other route
      Route *pcontainer_route = pRouteMan->FindRouteContainingWaypoint(rp);

      if(rp->m_bDynamicName)                // Mark is a "route only" type
      {
            if(pcontainer_route == NULL)
                  rp->m_bDynamicName = false;
      }
      else if (pcontainer_route == NULL)
            rp->m_bIsInRoute = false;          // Take this point out of this (and only) route


      if(bRenamePoints)
            RenameRoutePoints();

      CalculateBBox();
      UpdateSegmentDistances();
}



void Route::DeSelectRoute()
{
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *rp;
      while (node)
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
      while (node)
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


      BBox.Reset();

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *data;
      while (node)
      {
            data = node->GetData();

            if(data->m_lon > bbox_xmax)
                  bbox_xmax = data->m_lon;
            if(data->m_lon < bbox_xmin)
                  bbox_xmin = data->m_lon;
            if(data->m_lat > bbox_ymax)
                  bbox_ymax = data->m_lat;
            if(data->m_lat < bbox_ymin)
                  bbox_ymin = data->m_lat;

            node = node->GetNext();
      }


      BBox.Expand(bbox_xmin, bbox_ymin);
      BBox.Expand(bbox_xmax, bbox_ymax);


}

void Route::CalculateDCRect(wxDC& dc_route, wxRect *prect, double scale_ppm)
{

    dc_route.ResetBoundingBox();
    dc_route.DestroyClippingRegion();

    // Draw the route on the dc
    DrawRoute(dc_route, scale_ppm);

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

      if(node)
      {
            RoutePoint *prp0 = node->GetData();
            slat1 = prp0->m_lat;
            slon1 = prp0->m_lon;

            node = node->GetNext();

            while (node)
            {
                  RoutePoint *prp = node->GetData();
                  slat2 = prp->m_lat;
                  slon2 = prp->m_lon;

//    Calculate the absolute distance from 1->2

                  double lon1 = slon1 * PI / 180.;
                  double lon2 = slon2 * PI / 180.;
                  double lat1 = slat1 * PI / 180.;
                  double lat2 = slat2 * PI / 180.;

                  double v = sin((lon1 - lon2)/2.0);
                  double w = cos(lat1) * cos(lat2) * v * v;
                  double x = sin((lat1 - lat2)/2.0);
                  double d4 = 2.0 * asin(sqrt(x*x + w));

                  float d5 = (180. * 60. / PI) * d4;

//    And store in Point 2
                  prp->m_seg_len = d5;

                  route_len += d5;

                  slat1 = slat2;
                  slon1 = slon2;
                  prp0 = prp;

                  node = node->GetNext();
            }
      }

      m_route_length = route_len;
}


void Route::Reverse(bool bRenamePoints)
{
      RebuildGUIDList();                        // ensure the GUID list is intact and good

      //    Reverse the GUID list
      wxArrayString ArrayTemp;

      int ncount = RoutePointGUIDList.GetCount();
      for(int i=0 ; i<ncount ; i++)
            ArrayTemp.Add(RoutePointGUIDList[ncount - 1 - i]);

      RoutePointGUIDList = ArrayTemp;

      pRoutePointList->DeleteContents(false);
      pRoutePointList->Clear();
      m_nPoints = 0;

      AssembleRoute();                          // Rebuild the route points from the GUID list

      if(bRenamePoints)
            RenameRoutePoints();
}

void Route::RebuildGUIDList(void)
{
      RoutePointGUIDList.Clear();               // empty the GUID list

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *rp;
      while (node)
      {
            rp = node->GetData();
            RoutePointGUIDList.Add(rp->m_GUID);

            node = node->GetNext();
      }
}

void Route::AssembleRoute(void)
{
      //    iterate over the RoutePointGUIDs
      for(unsigned int ip = 0 ; ip < RoutePointGUIDList.GetCount() ; ip++)
      {
            wxString GUID = RoutePointGUIDList[ip];

                  //    And on the RoutePoints themselves
            wxRoutePointListNode *prpnode = pWayPointMan->m_pWayPointList->GetFirst();
            while(prpnode)
            {
                  RoutePoint *prp = prpnode->GetData();

                  if(prp->m_GUID == GUID)
                  {
                        AddPoint(prp);
                        break;
                  }
                  prpnode = prpnode->GetNext(); //RoutePoint
            }
      }
}

void Route::RenameRoutePoints(void)
{
     //    iterate on the route points.
     //    If dynamically named, rename according to current list position

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      int i = 1;
      while (node)
      {
            RoutePoint *prp = node->GetData();
            if(prp->m_bDynamicName)
                  prp->m_MarkName.Printf(_T("%03d"), i);

            node = node->GetNext();
            i++;
      }
}


 bool Route::SendToGPS(wxString& com_name, bool bsend_waypoints, wxGauge *pProgress)
{
      SENTENCE snt;
      NMEA0183    oNMEA0183;
      oNMEA0183.TalkerID = _T("EC");

      int nProg = pRoutePointList->GetCount() + 1;
      if(pProgress)
            pProgress->SetRange(100);

      //    Send out the waypoints, in order
      if(bsend_waypoints)
      {
            wxRoutePointListNode *node = pRoutePointList->GetFirst();

            int ip = 1;
            while (node)
            {
                  RoutePoint *prp = node->GetData();

                  if(prp->m_lat < 0.)
                        oNMEA0183.Wpl.Position.Latitude.Set(-prp->m_lat, _T("S"));
                  else
                        oNMEA0183.Wpl.Position.Latitude.Set(prp->m_lat, _T("N"));

                  if(prp->m_lon < 0.)
                        oNMEA0183.Wpl.Position.Longitude.Set(-prp->m_lon, _T("W"));
                  else
                        oNMEA0183.Wpl.Position.Longitude.Set(prp->m_lon, _T("E"));


                  oNMEA0183.Wpl.To = prp->m_MarkName.Truncate(6);

                  oNMEA0183.Wpl.Write(snt);

//                  printf("%s", snt.Sentence.mb_str());
                  g_pCommMan->WriteComPort(com_name, snt.Sentence);

                  if(pProgress)
                  {
                        pProgress->SetValue((ip * 100) / nProg);
                        pProgress->Refresh();
                  }

                  wxMilliSleep(100);

                  node = node->GetNext();

                  ip++;
            }
      }

      //    Create the NMEA Rte sentence

      oNMEA0183.Rte.Empty();
      oNMEA0183.Rte.TypeOfRoute = CompleteRoute;

      if(m_RouteNameString.IsEmpty())
            oNMEA0183.Rte.RouteName = _T("(NO NAME)");
      else
            oNMEA0183.Rte.RouteName = m_RouteNameString;

      oNMEA0183.Rte.total_number_of_messages     = 1;
      oNMEA0183.Rte.message_number               = 1;

      //    add the waypoints
      wxRoutePointListNode *node = pRoutePointList->GetFirst();
      while (node)
      {
            RoutePoint *prp = node->GetData();
            oNMEA0183.Rte.AddWaypoint(prp->m_MarkName.Truncate(6));
            node = node->GetNext();
      }


      oNMEA0183.Rte.Write(snt);

//      printf("%s", snt.Sentence.mb_str());
      g_pCommMan->WriteComPort(com_name, snt.Sentence);


      wxMilliSleep(100);

      return true;
}



//-----------------------------------------------------------------------------
//          MyConfig Implementation
//-----------------------------------------------------------------------------


MyConfig::MyConfig(const wxString &appName, const wxString &vendorName, const wxString &LocalFileName)
      :wxFileConfig(appName, vendorName, LocalFileName, wxString(_T("")))
{
}



int MyConfig::LoadMyConfig(int iteration)
{

      int read_int;

//    Global options and settings
      SetPath(_T("/Settings"));

      s_bSetSystemTime = false;
      Read(_T("SetSystemTime"), &s_bSetSystemTime);

      m_bShowDebugWindows = true;
      Read(_T("ShowDebugWindows"), &m_bShowDebugWindows);

      g_bShowPrintIcon = false;
      Read(_T("ShowPrintIcon"), &g_bShowPrintIcon);

      g_bShowDepthUnits = true;
      Read(_T("ShowDepthUnits"), &g_bShowDepthUnits);

      g_bAutoAnchorMark = false;
      Read(_T("AutoAnchorDrop"),  &g_bAutoAnchorMark);

      g_bShowOutlines = false;
      Read(_T("ShowChartOutlines"),  &g_bShowOutlines);

      g_bGarminPersistance = false;
      Read(_T("GarminPersistance"),  &g_bGarminPersistance);

      wxString stps;
      Read(_T("PlanSpeed"),  &stps);
      stps.ToDouble(&g_PlanSpeed);

      g_bNMEADebug = false;
      Read(_T("DebugNMEA"),  &g_bNMEADebug);

      SetPath(_T("/Settings/GlobalState"));
      Read(_T("bFollow"), &st_bFollow);

      Read(_T("FrameWinX"), &g_nframewin_x);
      Read(_T("FrameWinY"), &g_nframewin_y);
      Read(_T("FrameMax"),  &g_bframemax);


      //    AIS
      wxString s;
      SetPath(_T("/Settings/AIS"));

      Read(_T("bNoCPAMax"), &g_bCPAMax);

      Read(_T("NoCPAMaxNMi"),  &s);
      s.ToDouble(&g_CPAMax_NM);

      Read(_T("bCPAWarn"), &g_bCPAWarn);

      Read(_T("CPAWarnNMi"),  &s);
      s.ToDouble(&g_CPAWarn_NM);

      Read(_T("bTCPAMax"), &g_bTCPA_Max);

      Read(_T("TCPAMaxMinutes"),  &s);
      s.ToDouble(&g_TCPA_Max);

      Read(_T("bMarkLostTargets"), &g_bMarkLost);

      Read(_T("MarkLost_Minutes"),  &s);
      s.ToDouble(&g_MarkLost_Mins);

      Read(_T("bRemoveLostTargets"), &g_bRemoveLost);

      Read(_T("RemoveLost_Minutes"),  &s);
      s.ToDouble(&g_RemoveLost_Mins);

      Read(_T("bShowCOGArrows"), &g_bShowCOG);

      Read(_T("CogArrowMinutes"),  &s);
      s.ToDouble(&g_ShowCOG_Mins);

      Read(_T("bShowTargetTracks"), &g_bShowTracks);

      Read(_T("TargetTracksMinutes"),  &s);
      s.ToDouble(&g_ShowTracks_Mins);

      Read(_T("bShowMooredTargets"), &g_bShowMoored);

      Read(_T("MooredTargetMaxSpeedKnots"),  &s);
      s.ToDouble(&g_ShowMoored_Kts);

#ifdef USE_S57
    if(NULL != ps52plib)
    {
      SetPath(_T("/Settings/GlobalState"));

      Read(_T("bShowS57Text"), &read_int, 0);
      ps52plib->SetShowS57Text(read_int);

      Read(_T("bShowS57ImportantTextOnly"), &read_int, 0);
      ps52plib->SetShowS57ImportantTextOnly(read_int);

      Read(_T("bShowLightDescription"), &read_int, 0);
      ps52plib->SetShowLdisText(read_int);

      Read(_T("nDisplayCategory"), &read_int, (enum _DisCat)OTHER);
      ps52plib->m_nDisplayCategory = (enum _DisCat)read_int;

      Read(_T("nSymbolStyle"), &read_int, (enum _LUPname)PAPER_CHART);
      ps52plib->m_nSymbolStyle = (LUPname)read_int;

      Read(_T("nBoundaryStyle"), &read_int, 0);
      ps52plib->m_nBoundaryStyle = (LUPname)read_int;

      Read(_T("bShowSoundg"), &read_int, 0);
      ps52plib->m_bShowSoundg = read_int;

      Read(_T("bShowMeta"), &read_int, 0);
      ps52plib->m_bShowMeta = read_int;

      Read(_T("bUseSCAMIN"), &read_int, 0);
      ps52plib->m_bUseSCAMIN = read_int;

      Read(_T("bShowAtonText"), &read_int, 0);
      ps52plib->m_bShowAtonText = read_int;

      Read(_T("bDeClutterText"), &read_int, 0);
      ps52plib->m_bDeClutterText = read_int;

      double dval;
      if(Read(_T("S52_MAR_SAFETY_CONTOUR"), &dval, 5.0))
            S52_setMarinerParam(S52_MAR_SAFETY_CONTOUR, dval);

      if(Read(_T("S52_MAR_SHALLOW_CONTOUR"), &dval, 3.0))
            S52_setMarinerParam(S52_MAR_SHALLOW_CONTOUR, dval);

      if(Read(_T("S52_MAR_DEEP_CONTOUR"), &dval, 10.0))
            S52_setMarinerParam(S52_MAR_DEEP_CONTOUR, dval);

      if(Read(_T("S52_MAR_TWO_SHADES"), &dval, 0.0))
            S52_setMarinerParam(S52_MAR_TWO_SHADES, dval);

      ps52plib->UpdateMarinerParams();

      SetPath(_T("/Settings/GlobalState"));
      Read(_T("S52_DEPTH_UNIT_SHOW"), &read_int, 1);         // default is metres
      ps52plib->m_nDepthUnitDisplay = read_int;
    }

    wxString strpres(_T("PresentationLibraryData"));
    wxString valpres;
    SetPath(_T("/Directories"));
    Read(strpres, &valpres);                 // Get the File name
    if(iteration == 0)
          *g_pPresLibData = valpres;

    wxString strd(_T("S57DataLocation"));
    wxString val;
    SetPath(_T("/Directories"));
    Read(strd, &val);                 // Get the Directory name


    wxString dirname(val);
    if(!dirname.IsEmpty())
    {
        if(g_pcsv_locn->IsEmpty())      // on second pass, don't overwrite
        {
            g_pcsv_locn->Clear();
            g_pcsv_locn->Append(val);
        }
    }

    wxString strs(_T("SENCFileLocation"));
    SetPath(_T("/Directories"));
    wxString vals;
    Read(strs, &vals);                 // Get the Directory name

    if(iteration == 0)
        *g_pSENCPrefix = vals;

#endif

     SetPath(_T("/Directories"));
     wxString vald;

     Read(_T("InitChartDir"), &vald);                 // Get the Directory name

     wxString dirnamed(vald);
     if(!dirnamed.IsEmpty())
     {
         if(pInit_Chart_Dir->IsEmpty())      // on second pass, don't overwrite
         {
             pInit_Chart_Dir->Clear();
             pInit_Chart_Dir->Append(vald);
         }
     }


      SetPath(_T("/Settings/GlobalState"));
      Read(_T("nColorScheme"), &read_int, 0);
      global_color_scheme = (ColorScheme)read_int;

      SetPath(_T("/Settings/NMEADataSource"));
      Read(_T("Source"), pNMEADataSource, _T("NONE"));

      SetPath(_T("/Settings/NMEAAutoPilotPort"));
      Read(_T("Port"), pNMEA_AP_Port, _T("NONE"));

      SetPath(_T("/Settings/WiFiServer"));
      Read(_T("Server"), pWIFIServerName, _T("NONE"));

      SetPath(_T("/Settings/AISPort"));
      Read(_T("Port"), pAIS_Port, _T("NONE"));

//    Reasonable starting point
      vLat = START_LAT;                   // display viewpoint
      vLon = START_LON;

      gLat = START_LAT;                   // GPS position, as default
      gLon = START_LON;

      initial_scale_ppm = .00003;        // decent initial value

      SetPath(_T("/Settings/GlobalState"));
      wxString st;

      if(Read(_T("VPLatLon"), &st))
      {
            sscanf(st.mb_str(wxConvUTF8), "%f,%f", &st_lat, &st_lon);
            //    Sanity check the lat/lon
            if((st_lat > 0.0) && (st_lat < 90.0))
                  vLat = st_lat;

            if((st_lon > -179.9) && (st_lon < 179.9))
                  vLon = st_lon;

            wxString s;
            s.Printf(_T("Setting Viewpoint Lat/Lon %g, %g"), vLat, vLon);
      }

      if(Read(wxString(_T("VPScale")), &st))
      {
            sscanf(st.mb_str(wxConvUTF8), "%f", &st_view_scale);
//    Sanity check the scale
            st_view_scale = fmax(st_view_scale, .001/32);
            st_view_scale = fmin(st_view_scale, 4);
            initial_scale_ppm = st_view_scale;
      }


      wxString sll;
      float lat, lon;
      if(Read(_T("OwnShipLatLon"), &sll))
      {
            sscanf(sll.mb_str(wxConvUTF8), "%f,%f", &lat, &lon);
            gLat = lat;
            gLon = lon;
      }


#ifdef USE_S57
//    S57 Object Class Visibility

      bool bNeedNew = true;
      OBJLElement *pOLE;

      SetPath(_T("/Settings/ObjectFilter"));

      if(ps52plib)
      {
            int iOBJMax = GetNumberOfEntries();
            if(iOBJMax)
            {

                  wxString str;
                  long val;
                  long dummy;

                  wxString sObj;

                  bool bCont = pConfig->GetFirstEntry(str, dummy);
                  while ( bCont )
                  {
                        pConfig->Read(str, &val);                 // Get an Object Viz

                        if(str.StartsWith(_T("viz"), &sObj))
                        {
                                 for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
                                 {
                                       pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));
                                       if(!strncmp(pOLE->OBJLName, sObj.mb_str(), 6))
                                       {
                                             pOLE->nViz = val;
                                             bNeedNew = false;
                                             break;
                                       }
                                 }

                                 if(bNeedNew)
                                 {
                                       pOLE = (OBJLElement *)malloc(sizeof(OBJLElement));
                                       strcpy(pOLE->OBJLName, sObj.mb_str());
                                       pOLE->nViz = val;

                                       ps52plib->pOBJLArray->Add((void *)pOLE);
                                 }
                        }
                        bCont = pConfig->GetNextEntry(str, dummy);
                  }
            }
      }
#endif

//    Chart Directories
      SetPath(_T("/ChartDirectories"));
      int iDirMax = GetNumberOfEntries();
      if(iDirMax)
      {
          pChartDirArray->Empty();
          wxString str, val;
          long dummy;
          int nAdjustChartDirs = 0;
          int iDir = 0;
          bool bCont = pConfig->GetFirstEntry(str, dummy);
          while ( bCont )
          {
                pConfig->Read(str, &val);                 // Get a Directory name

                wxString dirname(val);
                if(!dirname.IsEmpty())
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
                    if(dirname.Find(_T("SampleCharts")) == 0)    // only update entries starting with "SampleCharts"
                    {
                        nAdjustChartDirs++;

                        pConfig->DeleteEntry(str);
                        wxString new_dir = dirname.Mid(dirname.Find(_T("SampleCharts")));
                        new_dir.Prepend(*pSData_Locn);
                        dirname=new_dir;
                    }

                    if(NULL != pChartDirArray)
                    {
                        pChartDirArray->Add(dirname);
                        iDir++;
                    }
                }

                bCont = pConfig->GetNextEntry(str, dummy);
          }

          if(nAdjustChartDirs)
              pConfig->UpdateChartDirs(pChartDirArray);
      }



//    Fonts

#ifdef __WXX11__
      SetPath(_T("/Settings/X11Fonts"));
#endif

#ifdef __WXGTK__
      SetPath(_T("/Settings/GTKFonts"));
#endif

#ifdef __WXMSW__
      SetPath(_T("/Settings/MSWFonts"));
#endif

#ifdef __WXMAC__
      SetPath(_T("/Settings/MacFonts"));
#endif

      if(0 == iteration)
      {
        wxString str;
        long dummy;
        wxString *pval = new wxString;

        bool bCont = GetFirstEntry(str, dummy);
        while ( bCont )
        {
            Read(str, pval);
            pFontMgr->LoadFontNative(&str, pval);
            bCont = GetNextEntry(str, dummy);
        }
        delete pval;
      }



//    Routes
      if(0 == iteration)
      {
        int routenum = 0;
        pRouteList = new RouteList;

        SetPath(_T("/Routes"));
        int iRoutes = GetNumberOfGroups();
        if(iRoutes)
        {
                    int rnt;

                    wxString str, val;
                    long dummy;
                    float rlat, rlon, prev_rlat, prev_rlon;
                    RoutePoint *prev_pConfPoint;

                    bool bCont = GetFirstGroup(str, dummy);
                    while ( bCont )
                    {
                            Route *pConfRoute = new Route();
                            pRouteList->Append(pConfRoute);

                            int RouteNum;
                            sscanf(str.mb_str(), "RouteDefn%d", &RouteNum);
                            pConfRoute->m_ConfigRouteNum = RouteNum;

                            SetPath(str);
                            Read(_T("RoutePoints"), &val);                // nPoints
                            int nPoints = atoi(val.mb_str());

                            Read(_T("RouteName"), &pConfRoute->m_RouteNameString);
                            Read(_T("RouteStart"), &pConfRoute->m_RouteStartString);
                            Read(_T("RouteEnd"), &pConfRoute->m_RouteEndString);



                            for(int ip = 0 ; ip < nPoints ; ip++)
                            {
//      New way
                                  wxString sipc;
                                  sipc.Printf(_T("RoutePointID%d"), ip+1);
                                  wxString str_ID;
                                  Read(sipc, &str_ID);
                                  if(!str_ID.IsEmpty())
                                      pConfRoute->AddTentativePoint(str_ID);

//      Old Way
                                wxString sipb;
                                sipb.Printf(_T("RoutePoint%d"), ip+1);
                                wxString rval;
                                Read(sipb, &rval);                          // Point lat/lon, icon, name
                                if(!rval.IsEmpty())
                                {
                                    double lat = 0.;
                                    double lon = 0.;
                                    wxStringTokenizer tkz(rval, _T(","));

                                    wxString token = tkz.GetNextToken();
                                    token.ToDouble(&lat);
                                    rlat = lat;
                                    token = tkz.GetNextToken();
                                    token.ToDouble(&lon);
                                    rlon = lon;

                                    wxString sipbn = sipb;
                                    sipbn.Append(_T("Name"));
                                    wxString mark_name;
                                    Read(sipbn, &mark_name);                          // name

                                    wxString sipbi = sipb;
                                    sipbi.Append(_T("Icon"));
                                    wxString icon_name;
                                    Read(sipbi, &icon_name);                          // icon

                                    if(icon_name.IsEmpty())
                                          icon_name = _T("square");

                                    wxString sipb1 = sipb;
                                    sipb1.Append(_T("GUID"));
                                    wxString str_GUID;
                                    Read(sipb1, &str_GUID);                          // GUID

                                    RoutePoint *pWP = new RoutePoint(rlat, rlon, icon_name, mark_name, &str_GUID);

                                    //        Get extended properties
                                    wxString sipb2 = sipb;
                                    sipb2.Append(_T("Prop"));
                                    wxString str_prop;
                                    Read(sipb2, &str_prop);                          // Properties

                                    wxStringTokenizer tkp(str_prop, _T(","));

                                    token = tkp.GetNextToken();
                                    long tmp_prop;
                                    token.ToLong(&tmp_prop);
                                    pWP->m_bDynamicName = tmp_prop;

                                    token = tkp.GetNextToken();
                                    token.ToLong(&tmp_prop);
                                    pWP->m_bShowName = tmp_prop;

                                    pConfRoute->AddPoint(pWP);
                                    pSelect->AddSelectablePoint(rlat, rlon, pWP);
                                    if(ip)
                                          pSelect->AddSelectableRouteSegment(prev_rlat, prev_rlon, rlat, rlon,
                                                                                    prev_pConfPoint, pWP);

                                    prev_rlat = rlat;
                                    prev_rlon = rlon;
                                    prev_pConfPoint = pWP;

                                    pWP->m_ConfigWPNum = 1000 + (RouteNum * 100) + ip;          // dummy mark number

                                }
                            }

                            SetPath(_T(".."));
                            bCont = GetNextGroup(str, dummy);

        //    Get next available RouteDefnx number
                            sscanf(str.mb_str(), "RouteDefn%d", &rnt);
                            if(rnt > routenum)
                                routenum = rnt;
                    }
        }

        m_NextRouteNum = routenum + 1;
      }

      //    Marks
      if(0 == iteration)
      {
            m_NextWPNum = 0;
            int marknum = 0;

            SetPath(_T("/Marks"));
            int iMarks = GetNumberOfGroups();
            if(iMarks)
            {
                    int mnt;

                    wxString str, val;
                    long dummy;
                    double rlat, rlon;

                    bool bCont = GetFirstGroup(str, dummy);
                    while ( bCont )
                    {
                            int MarkNum;
                            sscanf(str.mb_str(), "MarkDefn%d", &MarkNum);

                            SetPath(str);
                            wxString sipb;
                            sipb.Printf(_T("RoutePoint"));
                            Read(sipb, &val);                          // Point lat/lon
                            double lat = 0.;
                            double lon = 0.;
                            wxStringTokenizer tkz(val, _T(","));

                            wxString token = tkz.GetNextToken();
                            token.ToDouble(&lat);
                            rlat = lat;
                            token = tkz.GetNextToken();
                            token.ToDouble(&lon);
                            rlon = lon;

                            wxString sipbn = sipb;
                            sipbn.Append(_T("Name"));
                            wxString mark_name;
                            Read(sipbn, &mark_name);                          // name

                            wxString sipbi = sipb;
                            sipbi.Append(_T("Icon"));
                            wxString icon_name;
                            Read(sipbi, &icon_name);                          // icon

                            if(icon_name.IsEmpty())
                                  icon_name = _T("triangle");

                            wxString sipb1 = sipb;
                            sipb1.Append(_T("GUID"));
                            wxString str_GUID;
                            Read(sipb1, &str_GUID);                          // GUID

                            RoutePoint *pWP = new RoutePoint(rlat, rlon, icon_name, mark_name, &str_GUID);

 //        Get extended properties
                            long tmp_prop;
                            wxString str_prop;
                            wxString sipb2 = sipb;
                            sipb2.Append(_T("Prop"));
                            Read(sipb2, &str_prop);                          // Properties

                            if(!str_prop.IsEmpty())
                            {
                              wxStringTokenizer tkp(str_prop, _T(","));

                              token = tkp.GetNextToken();
                              token.ToLong(&tmp_prop);
                              pWP->m_bDynamicName = tmp_prop;

                              token = tkp.GetNextToken();
                              token.ToLong(&tmp_prop);
                              pWP->m_bShowName = tmp_prop;
                            }

                            sipb2 = sipb;
                            sipb2.Append(_T("NameLocationOffset"));
                            Read(sipb2, &str_prop);

                            if(!str_prop.IsEmpty())
                            {
                              wxStringTokenizer tkpp(str_prop, _T(","));
                              token = tkpp.GetNextToken();
                              token.ToLong(&tmp_prop);
                              pWP->m_NameLocationOffsetX = tmp_prop;

                              token = tkpp.GetNextToken();
                              token.ToLong(&tmp_prop);
                              pWP->m_NameLocationOffsetY = tmp_prop;
                            }


                                              // Get hyperlinks; toh, 2009.02.23
                            wxString str_hyperlinks;
                            wxString sipb3 = sipb;
                            sipb3.Append(_T("Link"));

                            bool cont = true;
                            int i=1;
                            while (cont)
                            {
                                  wxString sipb4 = sipb3;
                                  wxString buf;
                                  buf.Printf(_T("%d"), i);
                                  sipb4.Append(buf);

                                  cont = Read(sipb4, &str_hyperlinks);                          // hyperlinks

                                  if(cont && !str_hyperlinks.IsEmpty())
                                  {
                                        Hyperlink *link;
                                        link = new Hyperlink;

                                        wxStringTokenizer tkp(str_hyperlinks, _T("^"));

                                        token = tkp.GetNextToken();
                                        link->Link = token;

                                        token = tkp.GetNextToken();

                                        if (token.Length() > 0)
                                              link->DescrText = token;

                                        token = tkp.GetNextToken();

                                        if (token.Length() > 0)
                                              link->Type = token;

                                        pWP->m_HyperlinkList->Append(link);
                                  }
                                  i++;
                            }


                            pSelect->AddSelectablePoint(rlat, rlon, pWP);
                            pWP->m_ConfigWPNum = MarkNum;

                            SetPath(_T(".."));
                            bCont = GetNextGroup(str, dummy);

        //    Get next available MarkDefnx number
                            sscanf(str.mb_str(), "MarkDefn%d", &mnt);
                            if(mnt > marknum)
                                marknum = mnt;
                    }
            }
            m_NextWPNum = marknum + 1;


      }

      //    Constitute the routes just loaded
      if(0 == iteration)
      {
            pRouteMan->AssembleAllRoutes();
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

            // XML, toh, 2009.02.10
      SetPath(_T("/Settings/Others"));
      g_bShowGPXIcons = false;
      Read(_T("ShowGPXIcons"), &g_bShowGPXIcons);

      // Radar rings
      g_bNavAidShowRadarRings = false;          // toh, 2009.02.24
      Read(_T("ShowRadarRings"), &g_bNavAidShowRadarRings);

      g_iNavAidRadarRingsNumberVisible = 1;     // toh, 2009.02.24
      Read(_T("RadarRingsNumberVisible"), &val);
      if (val.Length() > 0)
            g_iNavAidRadarRingsNumberVisible = atoi(val.mb_str());

      g_fNavAidRadarRingsStep = 1.0;            // toh, 2009.02.24
      Read(_T("RadarRingsStep"), &val);
      if (val.Length() > 0)
            g_fNavAidRadarRingsStep = atof(val.mb_str());

      g_pNavAidRadarRingsStepUnits = 0;         // toh, 2009.02.24
      Read(_T("RadarRingsStepUnits"), &g_pNavAidRadarRingsStepUnits);

      // Waypoint dragging with mouse
      g_bWayPointPreventDragging = false;       // toh, 2009.02.24
      Read(_T("WaypointPreventDragging"), &g_bWayPointPreventDragging);


      return(0);
}


bool MyConfig::AddNewRoute(Route *pr, int crm)
{
      wxString str_buf;
      int acrm;

      if(crm != -1)
            acrm = crm;
      else
            acrm = m_NextRouteNum;


//    Build the Group Name
      wxString t(_T("/Routes/RouteDefn"));
      str_buf.Printf(_T("%d"), acrm);
      t.Append(str_buf);

      SetPath(t);

      str_buf.Printf(_T("%d"), pr->GetnPoints());
      Write(_T("RoutePoints"), str_buf);

      Write(_T("RouteName"), pr->m_RouteNameString);
      Write(_T("RouteStart"), pr->m_RouteStartString);
      Write(_T("RouteEnd"), pr->m_RouteEndString);


      //    New way
      for(int ip=1 ; ip < pr->GetnPoints()+1 ; ip++)
      {
            str_buf.Printf(_T("RoutePointID%d"), ip);
            RoutePoint *prp = pr->GetPoint(ip);
            Write(str_buf, prp->m_GUID);
      }

      for(int ip1=1 ; ip1 < pr->GetnPoints()+1 ; ip1++)
      {
            RoutePoint *prp = pr->GetPoint(ip1);
            UpdateWayPoint(prp);
      }

      //  Old Way
      /*
      for(int ip=1 ; ip < pr->GetnPoints()+1 ; ip++)
      {
            str_buf.Printf(_T("RoutePoint%d"), ip);

            RoutePoint *prp = pr->GetPoint(ip);
            wxString str_buf1;
            str_buf1.Printf(_T("%f,%f"), prp->m_lat, prp->m_lon);

            str_buf1<<_T(",");
            str_buf1<<prp->m_MarkName;
            str_buf1<<_T(",");
            str_buf1<<prp->m_IconName;
            Write(str_buf, str_buf1);

            wxString str_buf0 = str_buf;
            str_buf.Append(_T("GUID"));
            Write(str_buf, prp->m_GUID);

            str_buf = str_buf0;
            str_buf.Append(_T("Prop"));
            str_buf1.Printf(_T("%d,%d"), prp->m_bDynamicName, prp->m_bShowName);
            Write(str_buf, str_buf1);
      }
      */

      Flush();

      pr->m_ConfigRouteNum = acrm;

      if(crm == -1)
            m_NextRouteNum +=1;             // auto increment for next time

      return true;
}


bool MyConfig::UpdateRoute(Route *pr)
{
      wxString str_buf;

      assert(pr->m_ConfigRouteNum);

//    Build the Group Name
      wxString t(_T("/Routes/RouteDefn"));
      str_buf.Printf(_T("%d"), pr->m_ConfigRouteNum);
      t.Append(str_buf);

      DeleteGroup(t);

      AddNewRoute(pr, pr->m_ConfigRouteNum);

      return true;
}


bool MyConfig::DeleteConfigRoute(Route *pr)
{
      wxString str_buf;
      assert(pr->m_ConfigRouteNum);

//    Build the Group Name
      wxString t(_T("/Routes/RouteDefn"));
      str_buf.Printf(_T("%d"), pr->m_ConfigRouteNum);
      t.Append(str_buf);

      DeleteGroup(t);

      Flush();

      return true;
}


bool MyConfig::AddNewWayPoint(RoutePoint *pWP, int crm)
{
      wxString str_buf;
      int acrm;

      if(crm != -1)
            acrm = crm;
      else
            acrm = m_NextWPNum;

//    Build the Group Name
      wxString t(_T("/Marks/MarkDefn"));
      str_buf.Printf(_T("%d"), acrm);
      t.Append(str_buf);

      SetPath(t);

//          add the GUID here
      str_buf.Printf(_T("RoutePoint"));
      wxString str_buf1;
      str_buf1.Printf(_T("%f,%f"), pWP->m_lat, pWP->m_lon);
      Write(str_buf, str_buf1);

      str_buf.Printf(_T("RoutePointName"));
      Write(str_buf, pWP->m_MarkName);

      str_buf.Printf(_T("RoutePointIcon"));
      Write(str_buf, pWP->m_IconName);

      str_buf.Printf(_T("RoutePointGUID"));
      Write(str_buf, pWP->m_GUID);

      str_buf.Printf(_T("RoutePointProp"));
      str_buf1.Printf(_T("%d,%d"), pWP->m_bDynamicName, pWP->m_bShowName);
      Write(str_buf, str_buf1);

      str_buf.Printf(_T("RoutePointNameLocationOffset"));
      str_buf1.Printf(_T("%d,%d"), pWP->m_NameLocationOffsetX, pWP->m_NameLocationOffsetY);
      Write(str_buf, str_buf1);

            // toh, 2009.02.23
      int NbrLinks = pWP->m_HyperlinkList->GetCount();
      if (NbrLinks > 0)
      {
            HyperlinkList *hyperlinklist = pWP->m_HyperlinkList;

            wxHyperlinkListNode *linknode = hyperlinklist->GetFirst();

            int i=1;
            while (linknode)
            {
                  Hyperlink *link = linknode->GetData();
                  wxString Link = link->Link;
                  wxString Descr = link->DescrText;
                  linknode = linknode->GetNext();

                  wxString t(_T("RoutePointLink"));
                  str_buf.Printf(_T("%d"), i);
                  t.Append(str_buf);

                  str_buf1 = _T("");
                  str_buf1.Append(link->Link);
                  if (link->DescrText.Length() > 0)
                  {
                        str_buf1.Append(_T("^"));
                        str_buf1.Append(link->DescrText);
                  }
                  if (link->Type.Length() > 0)
                  {
                        str_buf1.Append(_T("^"));
                        str_buf1.Append(link->Type);
                  }
                  Write(t, str_buf1);
                  i++;
            }
      }


      Flush();

      pWP->m_ConfigWPNum = acrm;

      if(crm == -1)
            m_NextWPNum +=1;             // auto increment for next time

      return true;
}


bool MyConfig::UpdateWayPoint(RoutePoint *pWP)
{
      wxString str_buf;

//    Build the Group Name
      wxString t(_T("/Marks/MarkDefn"));
      str_buf.Printf(_T("%d"), pWP->m_ConfigWPNum);
      t.Append(str_buf);

      DeleteGroup(t);

      AddNewWayPoint(pWP, pWP->m_ConfigWPNum);

      return true;
}


bool MyConfig::DeleteWayPoint(RoutePoint *pWP)
{
      wxString str_buf;

//      assert(pWP->m_ConfigWPNum);

//    Build the Group Name
      wxString t(_T("/Marks/MarkDefn"));
      str_buf.Printf(_T("%d"), pWP->m_ConfigWPNum);
      t.Append(str_buf);

      DeleteGroup(t);

      Flush();

      return true;
}


bool MyConfig::UpdateChartDirs(wxArrayString *pdirlist)
{
      wxString key, dir;
      wxString str_buf;

      SetPath(_T("/ChartDirectories"));
      int iDirMax = GetNumberOfEntries();
      if(iDirMax)
      {

            long dummy;

            for (int i=0 ; i<iDirMax ; i++)
            {
                  GetFirstEntry(key, dummy);
                  DeleteEntry(key, false);
            }
      }

      iDirMax = pdirlist->GetCount();

      for(int iDir = 0 ; iDir <iDirMax ; iDir++)
      {
            wxString dirn = pdirlist->Item(iDir);
            str_buf.Printf(_T("ChartDir%d"), iDir+1);

            Write(str_buf, dirn);

      }

      Flush();
      return true;
}



void MyConfig::UpdateSettings()
{
//    Global options and settings
    SetPath(_T("/Settings"));

    Write(_T("ShowDebugWindows"), m_bShowDebugWindows);
    Write(_T("ShowPrintIcon"), g_bShowPrintIcon);
    Write(_T("SetSystemTime"), s_bSetSystemTime);
    Write(_T("ShowDepthUnits"), g_bShowDepthUnits);
    Write(_T("AutoAnchorDrop"),  g_bAutoAnchorMark);
    Write(_T("ShowChartOutlines"),  g_bShowOutlines);
    Write(_T("GarminPersistance"),  g_bGarminPersistance);

    wxString st0;
    st0.Printf(_T("%g"), g_PlanSpeed);
    Write(_T("PlanSpeed"), st0);


//    S57 Object Filter Settings

    SetPath(_T("/Settings/ObjectFilter"));

#ifdef USE_S57
      if(ps52plib)
      {
            for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
            {
                  OBJLElement *pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));

                  wxString st1(_T("viz"));
                  st1.Append(wxString(pOLE->OBJLName,  wxConvUTF8));
                  Write(st1, pOLE->nViz);
            }
      }
#endif

//    Global State

      SetPath(_T("/Settings/GlobalState"));

      wxString st1;

      if(cc1->VPoint.bValid)
      {
          st1.Printf(_T("%10.4f,%10.4f"), cc1->VPoint.clat, cc1->VPoint.clon);
          Write(_T("VPLatLon"), st1);
          st1.Printf(_T("%g"), cc1->VPoint.view_scale_ppm);
          Write(_T("VPScale"), st1);
      }


      //    Various Options
      SetPath(_T("/Settings/GlobalState"));
      Write(_T("bFollow"), cc1->m_bFollow);
      Write(_T("nColorScheme"), (int)gFrame->GetColorScheme());

      Write(_T("FrameWinX"), g_nframewin_x);
      Write(_T("FrameWinY"), g_nframewin_y);
      Write(_T("FrameMax"),  g_bframemax);

            //    AIS
      SetPath(_T("/Settings/AIS"));

      Write(_T("bNoCPAMax"), g_bCPAMax);
      Write(_T("NoCPAMaxNMi"),  g_CPAMax_NM);
      Write(_T("bCPAWarn"), g_bCPAWarn);
      Write(_T("CPAWarnNMi"),  g_CPAWarn_NM);
      Write(_T("bTCPAMax"), g_bTCPA_Max);
      Write(_T("TCPAMaxMinutes"),  g_TCPA_Max);
      Write(_T("bMarkLostTargets"), g_bMarkLost);
      Write(_T("MarkLost_Minutes"),  g_MarkLost_Mins);
      Write(_T("bRemoveLostTargets"), g_bRemoveLost);
      Write(_T("RemoveLost_Minutes"),  g_RemoveLost_Mins);
      Write(_T("bShowCOGArrows"), g_bShowCOG);
      Write(_T("CogArrowMinutes"),  g_ShowCOG_Mins);
      Write(_T("bShowTargetTracks"), g_bShowTracks);
      Write(_T("TargetTracksMinutes"),  g_ShowTracks_Mins);
      Write(_T("bShowMooredTargets"), g_bShowMoored);
      Write(_T("MooredTargetMaxSpeedKnots"),  g_ShowMoored_Kts);


#ifdef USE_S57
      SetPath(_T("/Settings/GlobalState"));
      Write(_T("bShowS57Text"), ps52plib->GetShowS57Text());
      Write(_T("bShowS57ImportantTextOnly"), ps52plib->GetShowS57ImportantTextOnly());
      Write(_T("nDisplayCategory"), (long)ps52plib->m_nDisplayCategory);
      Write(_T("nSymbolStyle"), (int)ps52plib->m_nSymbolStyle);
      Write(_T("nBoundaryStyle"), (int)ps52plib->m_nBoundaryStyle);

      Write(_T("bShowSoundg"), ps52plib->m_bShowSoundg);
      Write(_T("bShowMeta"), ps52plib->m_bShowMeta);
      Write(_T("bUseSCAMIN"), ps52plib->m_bUseSCAMIN);
      Write(_T("bShowAtonText"), ps52plib->m_bShowAtonText);
      Write(_T("bShowLightDescription"), ps52plib->m_bShowLdisText);
      Write(_T("bDeClutterText"), ps52plib->m_bDeClutterText);

      Write(_T("S52_MAR_SAFETY_CONTOUR"), S52_getMarinerParam(S52_MAR_SAFETY_CONTOUR));
      Write(_T("S52_MAR_SHALLOW_CONTOUR"), S52_getMarinerParam(S52_MAR_SHALLOW_CONTOUR));
      Write(_T("S52_MAR_DEEP_CONTOUR"), S52_getMarinerParam(S52_MAR_DEEP_CONTOUR));
      Write(_T("S52_MAR_TWO_SHADES"), S52_getMarinerParam(S52_MAR_TWO_SHADES));
      Write(_T("S52_DEPTH_UNIT_SHOW"), ps52plib->m_nDepthUnitDisplay);

      SetPath(_T("/Directories"));
      Write(_T("S57DataLocation"), *g_pcsv_locn);
      Write(_T("SENCFileLocation"), *g_pSENCPrefix);
      Write(_T("PresentationLibraryData"), *g_pPresLibData);


#endif

      SetPath(_T("/Directories"));
      Write(_T("InitChartDir"), *pInit_Chart_Dir);

      if(g_pnmea)
      {
          SetPath(_T("/Settings/NMEADataSource"));
          wxString source;
          g_pnmea->GetSource(source);
          Write(_T("Source"), source);
      }

      if(pAPilot)
      {
          SetPath(_T("/Settings/NMEAAutoPilotPort"));
        wxString ap_port;
        pAPilot->GetAP_Port(ap_port);
        Write(_T("Port"), ap_port);
      }

      SetPath(_T("/Settings/WiFiServer"));
      Write(_T("Server"), *pWIFIServerName);


      if(pAIS)
      {
          SetPath(_T("/Settings/AISPort"));
        wxString ais_port;
        pAIS->GetSource(ais_port);
        Write(_T("Port"), ais_port);
      }


//    Fonts
#ifdef __WXX11__
      SetPath(_T("/Settings/X11Fonts"));
#endif

#ifdef __WXGTK__
      SetPath(_T("/Settings/GTKFonts"));
#endif

#ifdef __WXMSW__
      SetPath(_T("/Settings/MSWFonts"));
#endif

#ifdef __WXMAC__
      SetPath(_T("/Settings/MacFonts"));
#endif

      int nFonts = pFontMgr->GetNumFonts();

      for(int i=0 ; i<nFonts ; i++)
      {
            wxString cfstring(*pFontMgr->GetConfigString(i));
            wxString valstring(*pFontMgr->GetDialogString(i));
            valstring.Append(_T(":"));
            valstring.Append(*pFontMgr->GetNativeDesc(i));
            Write(cfstring, valstring);
      }


      SetPath(_T("/Settings/Others"));
      Write(_T("ShowGPXIcons"), g_bShowGPXIcons);

      // Radar rings; toh, 2009.02.24
      Write(_T("ShowRadarRings"), g_bNavAidShowRadarRings);
      Write(_T("RadarRingsNumberVisible"), g_iNavAidRadarRingsNumberVisible);
      Write(_T("RadarRingsStep"), g_fNavAidRadarRingsStep);
      Write(_T("RadarRingsStepUnits"), g_pNavAidRadarRingsStepUnits);

      // Waypoint dragging with mouse; toh, 2009.02.24
      Write(_T("WaypointPreventDragging"), g_bWayPointPreventDragging);


      Flush();

      /*
      CreateXMLNavObj();
      CreateXMLRoutePoints();
      WriteXMLNavObj(_T("test.xml"));
      */
}

// toh, 2009.02.15
void MyConfig::ExportGPX(wxWindow* parent)
{
      wxFileDialog *saveDialog = new wxFileDialog(parent, wxT("Export GPX file"), wxT(""), wxT(""),
                  wxT("GPX files (*.gpx)|*.gpx"), wxFD_SAVE);

   // We have to check for the correct extension! If it can't be found, we have to set it!
   // To do...
      int response = saveDialog->ShowModal();
      if (response == wxID_OK) {
            wxString path = saveDialog->GetPath();

            CreateGPXNavObj();
            CreateGPXRoutePoints();
            WriteXMLNavObj(path);
      }
}

// toh, 2009.02.15
void MyConfig::ImportGPX(wxWindow* parent)
{
      wxFileDialog *openDialog = new wxFileDialog(parent, wxT("Import GPX file"), wxT(""), wxT(""),
                  wxT("GPX files (*.gpx)|*.gpx|All files (*.*)|*.*"), wxFD_OPEN);
      int response = openDialog->ShowModal();
      if (response == wxID_OK) {
            wxString path = openDialog->GetPath();

            if(::wxFileExists(path))
            {
                  wxXmlDocument *pXMLNavObj = new wxXmlDocument;
                  if(pXMLNavObj->Load(path))
                  {
                        wxXmlNode *root = pXMLNavObj->GetRoot();

                        wxString RootName = root->GetName();
                        if (RootName == _T("gpx"))
                        {
                              wxString RootContent = root->GetNodeContent();

                              wxXmlNode *child = root->GetChildren();
                              while (child)
                              {
                                    wxString ChildName = child->GetName();
                                    if (ChildName == _T("wpt"))
                                    {
                                          bool WpExists;
                                          GPXLoadWaypoint(child,WpExists);
                                    }
                                    if (ChildName == _T("rte"))
                                    {
                                          GPXLoadRoute(child);
                                    }
                                    if (ChildName == _T("trk"))        // For the future ;-)
                                    {
                                    }
                                    child = child->GetNext();
                              }
                        }
                  }
            }
      }
}

// toh, 2009.02.17
RoutePoint *MyConfig::GPXLoadWaypoint(wxXmlNode* wptnode,bool &WpExists,bool LoadRoute)
{
      wxString LatString = wptnode->GetPropVal(_T("lat"),_T("0.0"));
      wxString LonString = wptnode->GetPropVal(_T("lon"),_T("0.0"));

      wxString SymString  = _T("");
      wxString NameString = _T("null");
      wxString DescString = _T("");
      wxString TypeString = _T("");
      wxString ChildName  = _T("");

      HyperlinkList *linklist = new HyperlinkList;

      wxString HrefString = _T("");
      wxString HrefTextString = _T("");
      wxString HrefTypeString = _T("");

      wxXmlNode *child = wptnode->GetChildren();
      while (child)
      {
            ChildName = child->GetName();
            if (ChildName == _T("sym"))
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if (child1 != NULL)
                        SymString = child1->GetContent();
            }
            if (ChildName == _T("name"))
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if (child1 != NULL)
                        NameString = child1->GetContent();
            }
            if (ChildName == _T("desc"))
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if (child1 != NULL)
                        DescString = child1->GetContent();
            }
            if (ChildName == _T("type"))
            {
                  wxXmlNode *child1 = child->GetChildren();
                  if (child1 != NULL)
                        TypeString = child1->GetContent();
            }

      // Read hyperlink
            if (ChildName == _T("link"))
            {
                  HrefString = child->GetPropVal(_T("href"),_T(""));

                  wxXmlNode *child1 = child->GetChildren();
                  while (child1)
                  {
                        wxString LinkString = child1->GetName();

                        if (LinkString == _T("text"))
                        {
                              wxXmlNode *child1a = child1->GetChildren();
                              HrefTextString = child1a->GetContent();
                        }

                        if (LinkString == _T("type"))
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
                  linklist->Append(link);
            }

            child = child->GetNext();
      }

   // Create waypoint
      double rlat;
      double rlon;
      LatString.ToDouble(&rlat);
      LonString.ToDouble(&rlon);

   // If WP already exists it mustn't be added again
      wxRoutePointListNode *node = pWayPointMan->m_pWayPointList->GetFirst();

      RoutePoint *pWP;
      WpExists = false;
      while(node)
      {
            RoutePoint *pr = node->GetData();

            if (NameString == pr->m_MarkName)
            {
                  if (fabs(rlat-pr->m_lat) < 1.e-6 && fabs(rlon-pr->m_lon) < 1.e-6)
                  {
                        WpExists = true;
                        pWP = pr;
                        break;
                  }
            }
            node = node->GetNext();
      }

      if (!WpExists)
      {
            pWP = new RoutePoint(rlat, rlon, SymString, NameString);
            pWP->m_bDynamicName = true;
            pWP->m_bShowName = true;
            pWP->m_NameLocationOffsetX = -10;
            pWP->m_NameLocationOffsetY = 8;
            pWP->m_HyperlinkList = linklist;

            if (!LoadRoute)
                  pConfig->AddNewWayPoint ( pWP,m_NextWPNum);    // use auto next num
            pSelect->AddSelectablePoint(rlat, rlon, pWP);
            pWP->m_ConfigWPNum = m_NextWPNum;
            m_NextWPNum++;
      }

      return (pWP);
}

// toh, 2009.02.17
void MyConfig::GPXLoadRoute(wxXmlNode* rtenode)
{
      int routenum = m_NextRouteNum;

      wxString Name = rtenode->GetName();
      wxString RouteName = rtenode->GetPropVal(_T("name"),_T("N.N."));

      if (Name == _T("rte"))
      {
            Route *pConfRoute = new Route();
            pRouteList->Append(pConfRoute);
            pConfig->AddNewRoute ( pConfRoute,routenum);    // use auto next num

            pConfRoute->m_ConfigRouteNum = routenum;

            pConfRoute->m_RouteNameString = RouteName;

            m_NextRouteNum = routenum + 1;

            wxXmlNode *child = rtenode->GetChildren();
            int ip = 0;
            float prev_rlat, prev_rlon;
            RoutePoint *prev_pConfPoint;

            while (child)
            {
                  wxString ChildName = child->GetName();
                  if (ChildName == _T("rtept"))
                  {
                        bool WpExists;
                        RoutePoint *pWp = GPXLoadWaypoint(child,WpExists,true);
                        pConfRoute->AddPoint(pWp);
                        if (WpExists)
                              pSelect->AddSelectablePoint(pWp->m_lat,pWp->m_lon, pWp);

                        float rlat = pWp->m_lat;
                        float rlon = pWp->m_lon;

                        if (ip)
                              pSelect->AddSelectableRouteSegment(prev_rlat, prev_rlon, rlat, rlon,prev_pConfPoint, pWp);

                        prev_rlat = pWp->m_lat;
                        prev_rlon = pWp->m_lon;
                        prev_pConfPoint = pWp;
                        pWp->m_ConfigWPNum = 1000 + (routenum * 100) + ip;          // dummy mark number
                        ip++;
                  }
                  child = child->GetNext();
            }
            pConfig->UpdateRoute ( pConfRoute );
            pConfRoute->RebuildGUIDList();                  // ensure the GUID list is intact and
      }
}







/*
//---------------------------------------------------------------------------------
//    XML Support for Navigation Objects
//---------------------------------------------------------------------------------

void MyConfig::CreateXMLNavObj(void)
{
      m_pXMLNavObj = new wxXmlDocument;
      m_XMLrootnode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("NavObjectCollection"));
      m_pXMLNavObj->SetRoot(m_XMLrootnode);
}


void MyConfig::CreateXMLRoutePoints(void)
{
      //    Iterate on the RoutePoint list
      wxRoutePointListNode *node = pWayPointMan->m_pWayPointList->GetFirst();

      RoutePoint *pr = node->GetData();
      wxXmlNode *mark_node = CreateMarkNode(pr);
      m_XMLrootnode->AddChild(mark_node);

      wxXmlNode *prev_node = mark_node;

      node = node->GetNext();
      while(node)
      {
            pr = node->GetData();

            wxXmlNode *mark_node = CreateMarkNode(pr);
            prev_node->SetNext(mark_node);

            prev_node = mark_node;
            node = node->GetNext();
      }
}


void MyConfig::WriteXMLNavObj(const wxString& file)
{
      m_pXMLNavObj->Save(file, 4);
}


wxXmlNode *MyConfig::CreateMarkNode(RoutePoint *pr)
{
    wxXmlNode *mark_node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Mark"));

    //  Get and create the mark properties, one by one
    wxXmlNode *node;
    wxXmlNode *tnode;
    wxXmlNode *current_sib_node;

            //  Icon
    node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Icon"));
    mark_node->AddChild(node);
    tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_IconName);
    node->AddChild(tnode);

    current_sib_node = node;

            //  Position
    node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Position"));
    current_sib_node->SetNext(node);
    wxString str_pos;
    str_pos.Printf(_T("%9.6f"), fabs(pr->m_lat));
    if(pr->m_lat > 0)
        str_pos += _T(" N ");
    else
        str_pos += _T(" S ");

    wxString str_pos1;
    str_pos1.Printf(_T("%10.6f"), fabs(pr->m_lon));
    str_pos += str_pos1;
    if(pr->m_lon > 0)
        str_pos += _T(" E");
    else
        str_pos += _T(" W");

    tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), str_pos);
    node->AddChild(tnode);

    current_sib_node = node;

            //  Name
    node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("Name"));
    current_sib_node->SetNext(node);
    tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_MarkName);
    node->AddChild(tnode);

    current_sib_node = node;

    return(mark_node);
}

*/


// toh, 2009.02.10
//---------------------------------------------------------------------------------
//    GPX XML Support for Navigation Objects
//---------------------------------------------------------------------------------

void MyConfig::CreateGPXNavObj(void)
{
      m_pXMLNavObj = new wxXmlDocument;
      m_XMLrootnode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("gpx"));
      m_XMLrootnode->AddProperty(_T("version"),_T("1.1"));
      m_XMLrootnode->AddProperty(_T("creator"),_T("OpenCPN"));
      m_pXMLNavObj->SetRoot(m_XMLrootnode);
}


void MyConfig::CreateGPXRoutePoints(void)
{
      //    Iterate on the RoutePoint list
      // If a waypoint is also in the route, it mustn't be written

      wxRoutePointListNode *node = pWayPointMan->m_pWayPointList->GetFirst();

      RoutePoint *pr;
      wxXmlNode *prev_node;

      bool IsFirst = true;
      while(node)
      {
            pr = node->GetData();

            if (!WptIsInRouteList(pr))
            {
                  wxXmlNode *mark_node = CreateGPXWptNode(pr);

                  if (IsFirst)
                  {
                        IsFirst = false;
                        m_XMLrootnode->AddChild(mark_node);
                  }
                  else
                        prev_node->SetNext(mark_node);

                  prev_node = mark_node;
            }
            node = node->GetNext();
      }

            // Route
      wxRouteListNode *node1 = pRouteList->GetFirst();
      while ( node1 )
      {
            Route *pRoute = node1->GetData();
            RoutePointList *pRoutePointList = pRoute->pRoutePointList;

            wxXmlNode *GPXWpt_node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("rte"));
            GPXWpt_node->AddProperty(_T("name"),pRoute->m_RouteNameString);
            wxString strnum;
            strnum.Printf(_T("%d"),pRoute->m_ConfigRouteNum);
            GPXWpt_node->AddProperty(_T("number"),strnum);
            m_XMLrootnode->AddChild(GPXWpt_node);

            wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
            RoutePoint *prp;

            int i=1;
            while(node2)
            {
                  prp = node2->GetData();

                  wxXmlNode *rpt_node = CreateGPXRptNode(prp,i+1);
                  GPXWpt_node->AddChild(rpt_node);

                  node2=node2->GetNext();
                  i++;
            }
            node1 = node1->GetNext();
      }
}

// toh, 2009.02.24
bool MyConfig::WptIsInRouteList(RoutePoint *pr)
{
      bool IsInList = false;

      wxRouteListNode *node1 = pRouteList->GetFirst();
      while ( node1 )
      {
            Route *pRoute = node1->GetData();
            RoutePointList *pRoutePointList = pRoute->pRoutePointList;

            wxRoutePointListNode *node2 = pRoutePointList->GetFirst();
            RoutePoint *prp;

            while(node2)
            {
                  prp = node2->GetData();

                  if (pr->IsSame(prp))
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

void MyConfig::WriteXMLNavObj(const wxString& file)
{
      m_pXMLNavObj->Save(file, 4);
}


wxXmlNode *MyConfig::CreateGPXWptNode(RoutePoint *pr)
{
      wxXmlNode *GPXWpt_node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("wpt"));

      wxString str_lat;
      str_lat.Printf(_T("%.6f"), fabs(pr->m_lat));
      wxString str_lon;
      str_lon.Printf(_T("%.6f"), fabs(pr->m_lon));
      GPXWpt_node->AddProperty(_T("lat"),str_lat);
      GPXWpt_node->AddProperty(_T("lon"),str_lon);

    //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node;

            //  Icon
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("sym"));
      GPXWpt_node->AddChild(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_IconName);
      node->AddChild(tnode);

      current_sib_node = node;

            //  Name
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("name"));
      current_sib_node->SetNext(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_MarkName);
      node->AddChild(tnode);

      current_sib_node = node;

    // Description
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("desc"));
      current_sib_node->SetNext(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_MarkDescription);
      node->AddChild(tnode);

      current_sib_node = node;

    // Hyperlinks
      HyperlinkList *linklist = pr->m_HyperlinkList;
      wxHyperlinkListNode *linknode = linklist->GetFirst();
      while (linknode)
      {
            Hyperlink *link = linknode->GetData();
            wxString Link = link->Link;
            wxString Descr = link->DescrText;
            wxString Type = link->Type;

            node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("link"));
            current_sib_node->SetNext(node);

            wxXmlProperty *prop = new wxXmlProperty(_T("href"),Link);
            node->SetProperties(prop);

            if (Descr.Length() > 0)
            {
                  wxXmlNode *textnode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("text"));
                  node->AddChild(textnode);
                  wxXmlNode *descrnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""),Descr);
                  textnode->AddChild(descrnode);

            }

            current_sib_node = node;

            if (Type.Length() > 0)
            {
                  wxXmlNode *typenode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("type"));
                  node->AddChild(typenode);
                  wxXmlNode *typnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""),Type);
                  typenode->AddChild(typnode);
            }

            current_sib_node = node;

            linknode = linknode->GetNext();
      }

    // Type (waypoint or POI)
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("type"));
      current_sib_node->SetNext(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""),_T("WPT") /* pr->m_MarkDescription*/);
      node->AddChild(tnode);

      current_sib_node = node;

      return(GPXWpt_node);
}

wxXmlNode *MyConfig::CreateGPXRptNode(RoutePoint *pr,int nbr)
{
      wxXmlNode *GPXWpt_node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("rtept"));

      wxString str_lat;
      str_lat.Printf(_T("%.6f"), fabs(pr->m_lat));
      wxString str_lon;
      str_lon.Printf(_T("%.6f"), fabs(pr->m_lon));
      GPXWpt_node->AddProperty(_T("lat"),str_lat);
      GPXWpt_node->AddProperty(_T("lon"),str_lon);

    //  Get and create the mark properties, one by one
      wxXmlNode *node;
      wxXmlNode *tnode;
      wxXmlNode *current_sib_node;

            //  Icon
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("sym"));
      GPXWpt_node->AddChild(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_IconName);
      node->AddChild(tnode);

      current_sib_node = node;

            //  Name
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("name"));
      current_sib_node->SetNext(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_MarkName);
      node->AddChild(tnode);

      current_sib_node = node;

    // Description
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("desc"));
      current_sib_node->SetNext(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""), pr->m_MarkDescription);
      node->AddChild(tnode);

      current_sib_node = node;

    // Hyperlinks
      HyperlinkList *linklist = pr->m_HyperlinkList;
      wxHyperlinkListNode *linknode = linklist->GetFirst();
      while (linknode)
      {
            Hyperlink *link = linknode->GetData();
            wxString Link = link->Link;
            wxString Descr = link->DescrText;
            wxString Type = link->Type;

            node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("link"));
            current_sib_node->SetNext(node);

            wxXmlProperty *prop = new wxXmlProperty(_T("href"),Link);
            node->SetProperties(prop);

            if (Descr.Length() > 0)
            {
                  wxXmlNode *textnode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("text"));
                  node->AddChild(textnode);
                  wxXmlNode *descrnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""),Descr);
                  textnode->AddChild(descrnode);

            }

            current_sib_node = node;

            if (Type.Length() > 0)
            {
                  wxXmlNode *typenode = new wxXmlNode(wxXML_ELEMENT_NODE, _T("type"));
                  node->AddChild(typenode);
                  wxXmlNode *typnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""),Type);
                  typenode->AddChild(typnode);
            }

            current_sib_node = node;

            linknode = linknode->GetNext();
      }

    // Type (waypoint or POI)
      node = new wxXmlNode(wxXML_ELEMENT_NODE, _T("type"));
      current_sib_node->SetNext(node);
      tnode = new wxXmlNode(wxXML_TEXT_NODE, _T(""),_T("WPT") /* pr->m_MarkDescription*/);
      node->AddChild(tnode);

      current_sib_node = node;

      return(GPXWpt_node);
}



//---------------------------------------------------------------------------------
//          Private Font Manager and Helpers
//---------------------------------------------------------------------------------
#include <wx/fontdlg.h>
#include <wx/fontenum.h>
#include "wx/encinfo.h"
#include "wx/fontutil.h"

MyFontDesc::MyFontDesc(const char *DialogString, const char *ConfigString, wxFont *pFont)
{
    m_dialogstring = new wxString(DialogString,  wxConvUTF8);
    m_configstring = new wxString(ConfigString,  wxConvUTF8);

      m_nativeInfo = new wxString(pFont->GetNativeFontInfoDesc());

      m_font = pFont;
}

MyFontDesc::~MyFontDesc()
{
      delete m_dialogstring;
      delete m_configstring;
      delete m_nativeInfo;
      delete m_font;
}


#include <wx/listimpl.cpp>
WX_DEFINE_LIST(FontList);

FontMgr::FontMgr()
{

      //    Create the list of fonts
      m_fontlist = new FontList;
      m_fontlist->DeleteContents(true);

      //    Get a nice generic font as default
      pDefFont = wxTheFontList->FindOrCreateFont(12, wxDEFAULT,wxNORMAL, wxBOLD,
              FALSE, wxString(_T("")), wxFONTENCODING_SYSTEM );


}

FontMgr::~FontMgr()
{
      delete m_fontlist;
}


wxFont *FontMgr::GetFont(const wxString &TextElement)
{
      //    Look thru the font list for a match
      MyFontDesc *pmfd;
      wxNode *node = (wxNode *)(m_fontlist->GetFirst());  while (node)
      {
            pmfd = (MyFontDesc *)node->GetData();
            if(*pmfd->m_dialogstring == TextElement)
                  return pmfd->m_font;
            node = node->GetNext();
      }

      //    Found no font, so create a nice one and add to the list
      //    First, create the configstring by contortion of the TextElement
      wxString configstring(_T("Font"));
      int i=0;
      while(TextElement[i])
      {
            if(TextElement[i] != ' ')                       // strip out the spaces
                  configstring += TextElement[i];
            i++;
      }

      //    Now create a benign, always present native string
      wxString nativefont;

//    For those platforms which have no native font description string format
      nativefont.Printf(_T("%d;%d;%d;%d;%d;%d;%s;%d"),
               0,                                 // version
               12,
               wxFONTFAMILY_DEFAULT,
               (int)wxFONTSTYLE_NORMAL,
               (int)wxFONTWEIGHT_NORMAL,
               false,
               "",
               (int)wxFONTENCODING_DEFAULT);

//    If we know of a detailed description string format, use it.
#ifdef __WXGTK__
      nativefont = _T("Fixed 12");
#endif

#ifdef __WXX11__
      nativefont = _T("0;-*-fixed-*-*-*-*-*-120-*-*-*-*-iso8859-1");
#endif

#ifdef __WXMSW__
      nativefont = _T("0;-11;0;0;0;400;0;0;0;0;0;0;0;0;MS Sans Serif");
#endif


      wxFont *nf0 = new wxFont();
      wxFont *nf = nf0->New(nativefont);

      MyFontDesc *pnewfd = new MyFontDesc(TextElement.mb_str(), configstring.mb_str(), nf);
      m_fontlist->Append(pnewfd);

      return pnewfd->m_font;

}


bool FontMgr::SetFont(wxString &TextElement, wxFont *pFont)
{
      //    Look thru the font list for a match
      MyFontDesc *pmfd;
      wxNode *node = (wxNode *)(m_fontlist->GetFirst());  while (node)
      {
            pmfd = (MyFontDesc *)node->GetData();
            if(*pmfd->m_dialogstring == TextElement)
            {
                // Todo Think about this
                //

//      Cannot delete the present font, since it may be in use elsewhere
//      This WILL leak....but only on font changes


//              delete pmfd->m_font;                            // purge any old value
                delete pmfd->m_nativeInfo;

                pmfd->m_font = pFont;
                pmfd->m_nativeInfo = new wxString(pFont->GetNativeFontInfoDesc());

                return true;
            }
            node = node->GetNext();
      }

      return false;
}



int FontMgr::GetNumFonts(void)
{
      return m_fontlist->GetCount();
}

wxString *FontMgr::GetConfigString(int i)
{
      MyFontDesc *pfd = (MyFontDesc *)(m_fontlist->Item(i)->GetData());
      wxString *ret = pfd->m_configstring;
      return ret;
}

wxString *FontMgr::GetDialogString(int i)
{
      MyFontDesc *pfd = (MyFontDesc *)(m_fontlist->Item(i)->GetData());
      wxString *ret = pfd->m_dialogstring;
      return ret;
}

wxString *FontMgr::GetNativeDesc(int i)
{
      MyFontDesc *pfd = (MyFontDesc *)(m_fontlist->Item(i)->GetData());
      wxString *ret = pfd->m_nativeInfo;
      return ret;
}

void FontMgr::LoadFontNative(wxString *pConfigString, wxString *pNativeDesc)
{
      //    Parse the descriptor string

      wxStringTokenizer tk(*pNativeDesc, _T(":"));
      wxString dialogstring = tk.GetNextToken();
      wxString nativefont = tk.GetNextToken();

      //    Search for a match in the list
      MyFontDesc *pmfd;
      wxNode *node = (wxNode *)(m_fontlist->GetFirst());

      while (node)
      {
            pmfd = (MyFontDesc *)node->GetData();
            if(*pmfd->m_configstring == *pConfigString)
            {
                  pmfd->m_nativeInfo = new wxString(nativefont);
                  wxFont *nf = pmfd->m_font->New(*pmfd->m_nativeInfo);
                  pmfd->m_font = nf;
                  break;
            }
            node = node->GetNext();
      }

      //    Create and add the font to the list
      if(!node)
      {

            wxFont *nf0 = new wxFont();
            wxFont *nf = nf0->New(nativefont);
            delete nf0;

            MyFontDesc *pnewfd = new MyFontDesc(dialogstring.mb_str(), pConfigString->mb_str(), nf);
            m_fontlist->Append(pnewfd);

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
            MyFontPreviewer(wxWindow *parent, const wxSize& sz = wxDefaultSize) : wxWindow(parent, wxID_ANY, wxDefaultPosition, sz)
            {
            }

      private:
            void OnPaint(wxPaintEvent& event);
            DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MyFontPreviewer, wxWindow)
            EVT_PAINT(MyFontPreviewer::OnPaint)
            END_EVENT_TABLE()

void MyFontPreviewer::OnPaint(wxPaintEvent& WXUNUSED(event))
{
      wxPaintDC dc(this);

      wxSize size = GetSize();
      wxFont font = GetFont();

      dc.SetPen(*wxBLACK_PEN);
      dc.SetBrush(*wxWHITE_BRUSH);
      dc.DrawRectangle(0, 0, size.x, size.y);

      if ( font.Ok() )
      {
            dc.SetFont(font);
        // Calculate vertical centre
            long w, h;
            dc.GetTextExtent( wxT("X"), &w, &h);
            dc.SetTextForeground(GetForegroundColour());
            dc.SetClippingRegion(2, 2, size.x-4, size.y-4);
            dc.DrawText(GetName(),
                       10, size.y/2 - h/2);
            dc.DestroyClippingRegion();
      }
}


//-----------------------------------------------------------------------------
// X11FontPicker
//-----------------------------------------------------------------------------


IMPLEMENT_DYNAMIC_CLASS(X11FontPicker, wxDialog)

            BEGIN_EVENT_TABLE(X11FontPicker, wxDialog)
            EVT_CHECKBOX(wxID_FONT_UNDERLINE, X11FontPicker::OnChangeFont)
            EVT_CHOICE(wxID_FONT_STYLE, X11FontPicker::OnChangeFont)
            EVT_CHOICE(wxID_FONT_WEIGHT, X11FontPicker::OnChangeFont)
            EVT_CHOICE(wxID_FONT_FAMILY, X11FontPicker::OnChangeFace)
            EVT_CHOICE(wxID_FONT_COLOUR, X11FontPicker::OnChangeFont)
            EVT_CHOICE(wxID_FONT_SIZE, X11FontPicker::OnChangeFont)

            EVT_CLOSE(X11FontPicker::OnCloseWindow)
            END_EVENT_TABLE()


#define SCALEABLE_SIZES 11
static wxString scaleable_pointsize[SCALEABLE_SIZES] = {
      wxT("6"),
      wxT("8"),
      wxT("10"),
      wxT("12"),
      wxT("14"),
      wxT("16"),
      wxT("18"),
      wxT("20"),
      wxT("24"),
      wxT("30"),
      wxT("36")
};


#define NUM_COLS 48
            static wxString wxColourDialogNames[NUM_COLS]={wxT("ORANGE"),
      wxT("GOLDENROD"),
      wxT("WHEAT"),
      wxT("SPRING GREEN"),
      wxT("SKY BLUE"),
      wxT("SLATE BLUE"),
      wxT("MEDIUM VIOLET RED"),
      wxT("PURPLE"),

      wxT("RED"),
      wxT("YELLOW"),
      wxT("MEDIUM SPRING GREEN"),
      wxT("PALE GREEN"),
      wxT("CYAN"),
      wxT("LIGHT STEEL BLUE"),
      wxT("ORCHID"),
      wxT("LIGHT MAGENTA"),

      wxT("BROWN"),
      wxT("YELLOW"),
      wxT("GREEN"),
      wxT("CADET BLUE"),
      wxT("MEDIUM BLUE"),
      wxT("MAGENTA"),
      wxT("MAROON"),
      wxT("ORANGE RED"),

      wxT("FIREBRICK"),
      wxT("CORAL"),
      wxT("FOREST GREEN"),
      wxT("AQUARAMINE"),
      wxT("BLUE"),
      wxT("NAVY"),
      wxT("THISTLE"),
      wxT("MEDIUM VIOLET RED"),

      wxT("INDIAN RED"),
      wxT("GOLD"),
      wxT("MEDIUM SEA GREEN"),
      wxT("MEDIUM BLUE"),
      wxT("MIDNIGHT BLUE"),
      wxT("GREY"),
      wxT("PURPLE"),
      wxT("KHAKI"),

      wxT("BLACK"),
      wxT("MEDIUM FOREST GREEN"),
      wxT("KHAKI"),
      wxT("DARK GREY"),
      wxT("SEA GREEN"),
      wxT("LIGHT GREY"),
      wxT("MEDIUM SLATE BLUE"),
      wxT("WHITE")
            };

/*
            * Generic X11FontPicker
 */

void X11FontPicker::Init()
{
      m_useEvents = false;
      m_previewer = NULL;
      Create( m_parent ) ;
}

X11FontPicker::~X11FontPicker()
{
}

void X11FontPicker::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
      EndModal(wxID_CANCEL);
}

bool X11FontPicker::DoCreate(wxWindow *parent)
{
      if ( !wxDialog::Create( parent , wxID_ANY , _T("Choose Font") , wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE,
            _T("fontdialog") ) )
      {
            wxFAIL_MSG( wxT("wxFontDialog creation failed") );
            return false;
      }

      InitializeAllAvailableFonts();
      InitializeFont();
      CreateWidgets();

// sets initial font in preview area
      wxCommandEvent dummy;
      OnChangeFont(dummy);

      return true;
}

int X11FontPicker::ShowModal()
{
      int ret = wxDialog::ShowModal();

      if (ret != wxID_CANCEL)
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
      pattern.Printf(wxT("-*-*-*-*-*-*-*-*-*-*-*-*-iso8859-1"));

      int nFonts;
      char ** list = XListFonts((Display *)wxGetDisplay(), pattern.mb_str(), 32767, &nFonts);

      pFaceNameArray = new wxArrayString;
      unsigned int jname;
      for(int i=0 ; i < nFonts ; i++)
      {
            wxStringTokenizer st(wxString(list[i]), _T("-"));
            st.GetNextToken();
            st.GetNextToken();
            wxString facename = st.GetNextToken();
            for(jname=0 ; jname<pFaceNameArray->GetCount() ; jname++)
            {
                  if(facename == pFaceNameArray->Item(jname))
                        break;
            }
            if(jname >= pFaceNameArray->GetCount())
            {
                  pFaceNameArray->Add(facename);
            }

      }

}


// This should be application-settable
static bool ShowToolTips() { return false; }

void X11FontPicker::CreateWidgets()
{
    // layout

      bool is_pda = (wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA);
      int noCols, noRows;
      if (is_pda)
      {
            noCols = 2; noRows = 3;
      }
      else
      {
            noCols = 3; noRows = 2;
      }

      wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
      this->SetSizer(itemBoxSizer2);
      this->SetAutoLayout(TRUE);

      wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
      itemBoxSizer2->Add(itemBoxSizer3, 1, wxEXPAND|wxALL, 5);

      wxFlexGridSizer* itemGridSizer4 = new wxFlexGridSizer(noRows, noCols, 0, 0);
      itemBoxSizer3->Add(itemGridSizer4, 0, wxEXPAND, 5);

      wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5);
      wxStaticText* itemStaticText6 = new wxStaticText( this, wxID_STATIC, _("&Font family:"),
                  wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer5->Add(itemStaticText6, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      wxChoice* itemChoice7 = new wxChoice( this, wxID_FONT_FAMILY, wxDefaultPosition,
                  wxDefaultSize, *pFaceNameArray, 0 );
      itemChoice7->SetHelpText(_("The font family."));
      if (ShowToolTips())
            itemChoice7->SetToolTip(_("The font family."));
      itemBoxSizer5->Add(itemChoice7, 0, wxALIGN_LEFT|wxALL, 5);

      wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5);
      wxStaticText* itemStaticText9 = new wxStaticText( this, wxID_STATIC, _("&Style:"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      wxChoice* itemChoice10 = new wxChoice( this, wxID_FONT_STYLE, wxDefaultPosition, wxDefaultSize);
      itemChoice10->SetHelpText(_("The font style."));
      if (ShowToolTips())
            itemChoice10->SetToolTip(_("The font style."));
      itemBoxSizer8->Add(itemChoice10, 0, wxALIGN_LEFT|wxALL, 5);

      wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5);
      wxStaticText* itemStaticText12 = new wxStaticText( this, wxID_STATIC, _("&Weight:"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer11->Add(itemStaticText12, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      wxChoice* itemChoice13 = new wxChoice( this, wxID_FONT_WEIGHT, wxDefaultPosition, wxDefaultSize);
      itemChoice13->SetHelpText(_("The font weight."));
      if (ShowToolTips())
            itemChoice13->SetToolTip(_("The font weight."));
      itemBoxSizer11->Add(itemChoice13, 0, wxALIGN_LEFT|wxALL, 5);

      wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5);
      if (m_fontData.GetEnableEffects())
      {
            wxStaticText* itemStaticText15 = new wxStaticText( this, wxID_STATIC, _("C&olour:"),
                        wxDefaultPosition, wxDefaultSize, 0 );
            itemBoxSizer14->Add(itemStaticText15, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

            wxSize colourSize = wxDefaultSize;
            if (is_pda)
                  colourSize.x = 100;

            wxChoice* itemChoice16 = new wxChoice( this, wxID_FONT_COLOUR, wxDefaultPosition,
                        colourSize, NUM_COLS, wxColourDialogNames, 0 );
            itemChoice16->SetHelpText(_("The font colour."));
            if (ShowToolTips())
                  itemChoice16->SetToolTip(_("The font colour."));
            itemBoxSizer14->Add(itemChoice16, 0, wxALIGN_LEFT|wxALL, 5);
      }

      wxBoxSizer* itemBoxSizer17 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer17, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5);
      wxStaticText* itemStaticText18 = new wxStaticText( this, wxID_STATIC, _("&Point size:"),
                  wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer17->Add(itemStaticText18, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      wxChoice *pc = new wxChoice( this, wxID_FONT_SIZE, wxDefaultPosition, wxDefaultSize);
      pc->SetHelpText(_("The font point size."));
      if (ShowToolTips())
            pc->SetToolTip(_("The font point size."));
      itemBoxSizer17->Add(pc, 0, wxALIGN_LEFT|wxALL, 5);

      if (m_fontData.GetEnableEffects())
      {
            wxBoxSizer* itemBoxSizer20 = new wxBoxSizer(wxVERTICAL);
            itemGridSizer4->Add(itemBoxSizer20, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
            wxCheckBox* itemCheckBox21 = new wxCheckBox( this, wxID_FONT_UNDERLINE, _("&Underline"),
                        wxDefaultPosition, wxDefaultSize, 0 );
            itemCheckBox21->SetValue(FALSE);
            itemCheckBox21->SetHelpText(_("Whether the font is underlined."));
            if (ShowToolTips())
                  itemCheckBox21->SetToolTip(_("Whether the font is underlined."));
            itemBoxSizer20->Add(itemCheckBox21, 0, wxALIGN_LEFT|wxALL, 5);
      }

      if (!is_pda)
            itemBoxSizer3->Add(5, 5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

      wxStaticText* itemStaticText23 = new wxStaticText( this, wxID_STATIC, _("Preview:"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer3->Add(itemStaticText23, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      MyFontPreviewer* itemWindow24 = new MyFontPreviewer( this, wxSize(400, 80) );
      m_previewer = itemWindow24;
      itemWindow24->SetHelpText(_("Shows the font preview."));
      if (ShowToolTips())
            itemWindow24->SetToolTip(_("Shows the font preview."));
      itemBoxSizer3->Add(itemWindow24, 0, wxEXPAND, 5);

      wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
      itemBoxSizer3->Add(itemBoxSizer25, 0, wxEXPAND, 5);
      itemBoxSizer25->Add(5, 5, 1, wxEXPAND|wxALL, 5);

    wxButton* itemButton28 = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    if (ShowToolTips())
          itemButton28->SetToolTip(_("Click to cancel the font selection."));
    itemBoxSizer25->Add(itemButton28, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton27 = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton27->SetDefault();
    itemButton27->SetHelpText(_("Click to confirm the font selection."));
    if (ShowToolTips())
          itemButton27->SetToolTip(_("Click to confirm the font selection."));
    itemBoxSizer25->Add(itemButton27, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    familyChoice = (wxChoice*) FindWindow(wxID_FONT_FAMILY);
    styleChoice = (wxChoice*) FindWindow(wxID_FONT_STYLE);
    weightChoice = (wxChoice*) FindWindow(wxID_FONT_WEIGHT);
    colourChoice = (wxChoice*) FindWindow(wxID_FONT_COLOUR);
    pointSizeChoice = (wxChoice*) FindWindow(wxID_FONT_SIZE);
    underLineCheckBox = (wxCheckBox*) FindWindow(wxID_FONT_UNDERLINE);

          //    Get readable font items
    wxString gotfontnative = dialogFont.GetNativeFontInfoDesc();
    wxStringTokenizer st(gotfontnative, _T("-"));
    st.GetNextToken();
    st.GetNextToken();
    wxString facename = st.GetNextToken();
    wxString weight = st.GetNextToken();
    st.GetNextToken();
    st.GetNextToken();
    st.GetNextToken();
    st.GetNextToken();
    wxString pointsize = st.GetNextToken();

    int ptsz = atoi(pointsize.mb_str());
    pointsize.Printf(_T("%d"), ptsz / 10);

    SetChoiceOptionsFromFacename(facename);


    familyChoice->SetStringSelection(facename);
    weightChoice->SetStringSelection(weight);
    pointSizeChoice->SetStringSelection(pointsize);

    m_previewer->SetFont(dialogFont);
    m_previewer->SetName(_("ABCDEFGabcdefg12345"));

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


void X11FontPicker::OnChangeFace(wxCommandEvent& WXUNUSED(event))
{
      if (!m_useEvents) return;

      //    Capture the current selections
      wxString facename = familyChoice->GetStringSelection();
      wxString pointsize = pointSizeChoice->GetStringSelection();
      wxString weight = weightChoice->GetStringSelection();


      SetChoiceOptionsFromFacename(facename);

      //    Reset the choices
      familyChoice->SetStringSelection(facename);
      weightChoice->SetStringSelection(weight);
      pointSizeChoice->SetStringSelection(pointsize);

      //    And make the font change
      DoFontChange();

}


void X11FontPicker::SetChoiceOptionsFromFacename(wxString &facename)
{
      //    Get a list of matching fonts
    char face[100];
    strncpy(face, facename.mb_str(), 100);

    char pattern[100];
    sprintf(pattern, "-*-%s-*-*-*-*-*-*-*-*-*-*-iso8859-1", face);
//    wxString pattern;
//    pattern.Printf(wxT("-*-%s-*-*-*-*-*-*-*-*-*-*-iso8859-1"), facename.mb_str());

      int nFonts;
      char ** list = XListFonts((Display *)wxGetDisplay(), pattern, 32767, &nFonts);

      //    First, look thru all the point sizes looking for "0" to indicate scaleable (e.g. TrueType) font
      bool scaleable = false;
      for(int i=0 ; i < nFonts ; i++)
      {
            wxStringTokenizer st(wxString(list[i]), _T("-"));
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            wxString pointsize = st.GetNextToken();

            if(pointsize.IsSameAs(_T("0")))
            {
                  scaleable = true;
                  break;
            }
      }


      // make different pointsize selections for scaleable fonts
      wxArrayString PointSizeArray;

      if(scaleable)
      {
            for(int j=0 ; j < SCALEABLE_SIZES ; j++)
                  PointSizeArray.Add(scaleable_pointsize[j]);
      }

      else
      {
            //Get the Point Sizes Array
            unsigned int jname;
            for(int i=0 ; i < nFonts ; i++)
            {
//                  printf("%s\n", list[i]);
                  wxStringTokenizer st(wxString(list[i]), _T("-"));
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  st.GetNextToken();
                  wxString pointsize = st.GetNextToken();
      //           printf("%s\n",facename.mb_str());
                  for(jname=0 ; jname<PointSizeArray.GetCount() ; jname++)
                  {
                        if(pointsize == PointSizeArray.Item(jname))
                              break;
                  }
                  if(jname >= PointSizeArray.GetCount())
                  {
                        PointSizeArray.Add(pointsize);
//                        printf("Added %s\n", pointsize.mb_str());
                  }
            }
      }
      pointSizeChoice->Clear();
      pointSizeChoice->Append(PointSizeArray);
      pointSizeChoice->SetSelection(0);

      //Get the Weight Array
      wxArrayString WeightArray;
      for(int i=0 ; i < nFonts ; i++)
      {
//            printf("%s\n", list[i]);
            wxStringTokenizer st(wxString(list[i]), _T("-"));
            st.GetNextToken();
            st.GetNextToken();
            st.GetNextToken();
            wxString weight = st.GetNextToken();
      //           printf("%s\n",facename.mb_str());
            unsigned int jname;
            for(jname=0 ; jname<WeightArray.GetCount() ; jname++)
            {
                  if(weight == WeightArray.Item(jname))
                        break;
            }
            if(jname >= WeightArray.GetCount())
            {
                  WeightArray.Add(weight);
//                  printf("Added weight %s\n", weight.mb_str());
            }
      }

      weightChoice->Clear();
      weightChoice->Append(WeightArray);
      weightChoice->SetSelection(0);

}





void X11FontPicker::InitializeFont()
{
      int fontFamily = wxSWISS;
      int fontWeight = wxNORMAL;
      int fontStyle = wxNORMAL;
      int fontSize = 12;
      bool fontUnderline = false;

      wxString fontnative;
      if (m_fontData.m_initialFont.Ok())
      {
            fontnative = m_fontData.m_initialFont.GetNativeFontInfoDesc();
            fontFamily = m_fontData.m_initialFont.GetFamily();
            fontWeight = m_fontData.m_initialFont.GetWeight();
            fontStyle = m_fontData.m_initialFont.GetStyle();
            fontSize = m_fontData.m_initialFont.GetPointSize();
            fontUnderline = m_fontData.m_initialFont.GetUnderlined();
      }

//      printf("Init Fetching    %s\n", fontnative.mb_str());

      wxFont tFont = wxFont(fontSize, fontFamily, fontStyle,
                              fontWeight, fontUnderline);

      wxFont *pdialogFont = tFont.New(fontnative);

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

void X11FontPicker::OnChangeFont(wxCommandEvent& WXUNUSED(event))
{
                  if (!m_useEvents) return;

                  DoFontChange();
}


void X11FontPicker::DoFontChange(void)
{
      wxString facename = familyChoice->GetStringSelection();
      wxString pointsize = pointSizeChoice->GetStringSelection();
      wxString weight = weightChoice->GetStringSelection();

      char font_x[200];
      sprintf(font_x,"-*-%s-%s-r-normal-*-*-%s0-*-*-*-*-iso8859-1", facename.mb_str(), weight.mb_str(), pointsize.mb_str());
      wxString font_xlfd(font_x,  wxConvUTF8);


//                  printf("Fetching    %s\n", font_xlfd.mb_str());

      XFontStruct *test = XLoadQueryFont((Display *)wxGetDisplay(),font_xlfd.mb_str());

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
      if(test)
      {
            font_xlfd.Prepend("0;");
            wxFont *ptf = new wxFont;
            pPreviewFont = ptf->New(font_xlfd);

/*
      wxNativeFontInfo *i = (wxNativeFontInfo *)pPreviewFont->GetNativeFontInfo();

      XFontStruct *xfont = (XFontStruct*) pPreviewFont->GetFontStruct( 1.0, (Display *)wxGetDisplay() );
      unsigned long ret;
      XGetFontProperty(xfont, 18, &ret);
      char* x = XGetAtomName((Display *)wxGetDisplay(), ret);
      printf("Got %s\n", x);
*/
            m_previewer->SetName(_("ABCDEFGabcdefg12345"));
            m_previewer->SetFont(*pPreviewFont);
            m_previewer->Refresh();
      }

      else
      {
            wxString err(_T("No Font:"));
            err.Append(font_xlfd);
            m_previewer->SetName(err);
            m_previewer->SetFont(*pPreviewFont);
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
double vGetLengthOfNormal(PVECTOR2D a, PVECTOR2D b, PVECTOR2D n)
{
  VECTOR2D c, vNormal;
  //
  //Obtain projection vector.
  //
  //c = ((a * b)/(|b|^2))*b
  //
  c.x = b->x * (vDotProduct(a, b)/vDotProduct(b, b));
  c.y = b->y * (vDotProduct(a, b)/vDotProduct(b, b));
//
  //Obtain perpendicular projection : e = a - c
  //
  vSubtractVectors(a, &c, &vNormal);
  //
  //Fill PROJECTION structure with appropriate values.
  //
  *n = vNormal;

  return (vVectorMagnitude(&vNormal));
}

double vDotProduct(PVECTOR2D v0, PVECTOR2D v1)
{
  double dotprod;

  dotprod = (v0 == NULL || v1 == NULL)
            ? 0.0
            : (v0->x * v1->x) + (v0->y * v1->y);

  return(dotprod);
}

PVECTOR2D vAddVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v)
{
      if (v0 == NULL || v1 == NULL)
            v = (PVECTOR2D)NULL;
      else
      {
            v->x = v0->x + v1->x;
            v->y = v0->y + v1->y;
      }
      return(v);
}


PVECTOR2D vSubtractVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v)
{
  if (v0 == NULL || v1 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    v->x = v0->x - v1->x;
    v->y = v0->y - v1->y;
  }
  return(v);
}

double vVectorSquared(PVECTOR2D v0)
{
  double dS;

  if (v0 == NULL)
    dS = 0.0;
  else
    dS = ((v0->x * v0->x) + (v0->y * v0->y));
  return (dS);
}

double vVectorMagnitude(PVECTOR2D v0)
{
  double dMagnitude;

  if (v0 == NULL)
    dMagnitude = 0.0;
  else
    dMagnitude = sqrt(vVectorSquared(v0));
  return (dMagnitude);
}


/**************************************************************************/
/*          LogMessageOnce                                                */
/**************************************************************************/

bool LogMessageOnce(wxString &msg)
{
      //    Search the array for a match

      for(unsigned int i=0 ; i < pMessageOnceArray->GetCount() ; i++)
      {
            if(msg.IsSameAs(pMessageOnceArray->Item(i)))
                  return false;
      }

      // Not found, so add to the array
      pMessageOnceArray->Add(msg);

      //    And print it
      wxLogMessage(msg);
      return true;
}


/**************************************************************************/
/*          Some assorted utilities                                       */
/**************************************************************************/

wxString toSDMM(int NEflag, double a)
{
      short neg = 0;
      int d;
      long m;

      if (a < 0.0)
      {
            a = -a;
            neg = 1;
      }
      d = (int) a;
      m = (long) ((a - (double) d) * 60000.0);

      if (neg)
            d = -d;

      wxString s;

      if (!NEflag)
            s.Printf(_T("%d %02ld.%03ld'"), d, m / 1000, m % 1000);
      else
      {
            if (NEflag == 1)
            {
                  char c = 'N';

                  if (neg)
                  {
                        d = -d;
                        c = 'S';
                  }

                  s.Printf(_T("%02d %02ld.%03ld %c"), d, m / 1000, (m % 1000), c);
            }
            else if (NEflag == 2)
            {
                  char c = 'E';

                  if (neg)
                  {
                        d = -d;
                        c = 'W';
                  }
                  s.Printf(_T("%03d %02ld.%03ld %c"), d, m / 1000, (m % 1000), c);
            }
      }
      return s;
}




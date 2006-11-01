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
 * $Log: navutil.cpp,v $
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

#ifdef USE_S57
#include "s52plib.h"
#endif

CPL_CVSID("$Id: navutil.cpp,v 1.4 2006/11/01 02:15:58 dsr Exp $");

//    Statics

extern ChartBase        *Current_Ch;
extern ChartCanvas      *cc1;
extern MyFrame          *gFrame;
extern NMEAWindow       *nmea;
extern FontMgr          *pFontMgr;

extern RouteList        *pRouteList;
extern Select           *pSelect;
extern MyConfig         *pConfig;
extern wxArrayString    *pChartDirArray;
extern float            vLat, vLon, gLat, gLon;
extern wxToolBarBase    *toolBar;
extern wxString         *pNMEADataSource;
extern wxString         *pNMEA_AP_Port;
extern wxString         *pWIFIServerName;
extern wxString         *pcsv_locn;
extern bool             g_bShowPrintIcon;
extern AutoPilotWindow  *pAPilot;
extern wxString         *pAIS_Port;
extern AIS_Decoder      *pAIS;

#ifdef USE_S57
extern s52plib          *ps52plib;
#endif

//------------------------------------------------------------------------------
// Some wxWidgets macros for useful classes
//------------------------------------------------------------------------------
WX_DEFINE_LIST(RouteList);


WX_DEFINE_LIST(SelectableItemList);
WX_DEFINE_LIST(RoutePointList);

//-----------------------------------------------------------------------------
//          C Linkage to clip.c
//-----------------------------------------------------------------------------

extern "C" {
      typedef enum { Visible, Invisible } ClipResult;
      ClipResult cohen_sutherland_line_clip_i (int *x0, int *y0, int *x1, int *y1,
                                   int xmin_, int xmax_, int ymin_, int ymax_);
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

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

                  while(node)
                  {
                      pFindSel = node->GetData();
                        if(pFindSel->m_seltype == SELTYPE_ROUTESEGMENT)
                        {
                                    Route *tpr = ((RoutePoint *)pFindSel->m_pData1)->m_pParentRoute;
                                    if(tpr == pr)
                                    {
                                          delete pFindSel;
                                          delete node;
                                          node = pSelectList->GetFirst();

                                          goto got_next_node;
                                    }

                        }


                        node = node->GetNext();
got_next_node:
                        continue;
                  }


      return true;
}


bool Select::DeleteAllSelectableRoutePoints(Route *pr)
{
      SelectItem *pFindSel;

//    Iterate on the list
      wxSelectableItemListNode *node = pSelectList->GetFirst();

                  while(node)
                  {
                      pFindSel = node->GetData();
                        if(pFindSel->m_seltype == SELTYPE_ROUTEPOINT)
                        {
                                    RoutePoint *ps = (RoutePoint *)pFindSel->m_pData1;
                                    Route *tpr = ps->m_pParentRoute;
                                    if(tpr == pr)
                                    {
                                          delete pFindSel;
                                          delete node;
                                          node = pSelectList->GetFirst();

                                          goto got_next_node;
                                    }

                        }



                        node = node->GetNext();
got_next_node:
                        continue;
                  }


      return true;
}


bool Select::AddAllSelectableRoutePoints(Route *pr)
{

      wxRoutePointListNode *node = (pr->pRoutePointList)->GetFirst();

      while (node)
      {
            RoutePoint *prp = node->GetData();

            AddSelectablePoint(prp->rlat, prp->rlon, prp);

            node = node->GetNext();

      }


      return true;
}

bool Select::AddAllSelectableRouteSegments(Route *pr)
{
      wxPoint rpt, rptn;
      float slat1, slon1, slat2, slon2;

      wxRoutePointListNode *node = (pr->pRoutePointList)->GetFirst();

      RoutePoint *prp0 = node->GetData();
      slat1 = prp0->rlat;
      slon1 = prp0->rlon;

      node = node->GetNext();

      while (node)
      {
            RoutePoint *prp = node->GetData();
            slat2 = prp->rlat;
            slon2 = prp->rlon;

            AddSelectableRouteSegment(slat1, slon1, slat2, slon2, prp0, prp);

            slat1 = slat2;
            slon1 = slon2;
            prp0 = prp;

            node = node->GetNext();
      }


      return true;
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
                                    if( (slat >= fmin(a,b)) && (slat <= fmax(a,b)) &&
                                        (slon >= fmin(c,d)) && (slon <= fmax(c,d)))
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
//          Route
//-----------------------------------------------------------------------------

Route::Route(void)
{
      m_bRtIsSelected = false;
      m_bRtIsActive = false;
      m_nRouteActivePoint = 0;
      m_bIsBeingEdited = false;
      m_bIsBeingCreated = false;

      pRoutePointList = new RoutePointList;

      BBox.Reset();

}


Route::~Route(void)
{

      pRoutePointList->DeleteContents(true);
      pRoutePointList->Clear();
      delete pRoutePointList;
}


RoutePoint *Route::AddPoint(float rlat, float rlon)
{
      RoutePoint *np = new RoutePoint;
      np->rlat = rlat;
      np->rlon = rlon;
      np->m_bPtIsSelected = false;
      np->m_pParentRoute = this;

      RoutePoint *pLast = GetLastPoint();

//      m_runPoint++;
//      np->nPoint = m_runPoint;

      if(NULL == pLast)
        np->nPoint = 1;
      else
        np->nPoint = pLast->nPoint + 1;

      pRoutePointList->Append(np);

      CalculateBBox();
      UpdateSegmentDistances();

      return(np);

}

RoutePoint *Route::GetPoint(int nWhichPoint, float *prlat, float *prlon)
{
  RoutePoint *prp;
  wxRoutePointListNode *node = pRoutePointList->GetFirst();

  while (node)
  {
    prp = node->GetData();
      if(prp->nPoint == nWhichPoint)
      {
            *prlat = prp->rlat;
            *prlon = prp->rlon;
            return prp;
      }

      node = node->GetNext();

  }


  wxLogError("Error in Route::GetPoint, nWhichPoint=%d", nWhichPoint);

      return(NULL);
}

void Route::DrawPointWhich(wxDC& dc, int iPoint, wxPoint *rpn)
{
      float rlat, rlon;
      GetPoint(iPoint, &rlat, &rlon);

      DrawPointLL(dc, rlat, rlon, iPoint, rpn);
}




void Route::DrawPointLL(wxDC& dc, float rlat, float rlon, int iPoint, wxPoint *rpn)
{
      bool bBlink = false;
      wxPen oldPen = dc.GetPen();

      if(m_bRtIsSelected)
            dc.SetPen(*pConfig->pSelectedRoutePen);
      else if(m_bRtIsActive)
      {
            if(m_nRouteActivePoint == iPoint)
            {
                  dc.SetPen(*pConfig->pActiveRoutePointPen);
                  bBlink = true;
            }
            else
                  dc.SetPen(*pConfig->pActiveRoutePen);

      }
      else if(m_nRouteActivePoint == iPoint)
                  dc.SetPen(*pConfig->pActiveRoutePointPen);
      else
            dc.SetPen(*pConfig->pRoutePen);

      if(bBlink && (gFrame->nBlinkerTick & 1))
            dc.SetPen(*pConfig->pActiveRoutePen);

      //    Get the dc boundary
      int sx, sy;
      dc.GetSize(&sx, &sy);

      wxPoint r;
      cc1->GetPointPix(rlat, rlon, &r);

      if((r.x > 0) && (r.x < sx) && (r.y > 0) && (r.y < sy))
      {
            int d = 8;
            dc.DrawLine(r.x, r.y+d, r.x+d, r.y);
            dc.DrawLine(r.x+d, r.y, r.x, r.y-d);
            dc.DrawLine(r.x, r.y-d, r.x-d, r.y);
            dc.DrawLine(r.x-d, r.y, r.x, r.y+d);

            char buf[8];
            sprintf(buf, "%03d", iPoint);
            dc.DrawText(buf, r.x-10, r.y+8);
      }
//    dc.DrawCircle(rpt, 5);

      *rpn = r;

      dc.SetPen(oldPen);                        // Restore last pen

}

void Route::DrawSegment(wxDC& dc, wxPoint *rp1, wxPoint *rp2)
{
      if(m_bRtIsSelected)
            dc.SetPen(*pConfig->pSelectedRoutePen);
      else if(m_bRtIsActive)
            dc.SetPen(*pConfig->pActiveRoutePen);
      else
            dc.SetPen(*pConfig->pRoutePen);


//      dc.DrawLine(rp1->x, rp1->y, rp2->x, rp2->y);
      DrawRouteLine(dc, rp1->x, rp1->y, rp2->x, rp2->y);            // with clipping
}




void Route::DrawRoute(wxDC& dc)
{

      if(m_bRtIsSelected)
            dc.SetPen(*pConfig->pSelectedRoutePen);
      else if(m_bRtIsActive)
            dc.SetPen(*pConfig->pActiveRoutePen);
      else
            dc.SetPen(*pConfig->pRoutePen);


      wxPoint rpt, rptn;
      DrawPointWhich(dc, 1, &rpt);

      wxRoutePointListNode *node = pRoutePointList->GetFirst();
      node = node->GetNext();

      while (node)
      {

            RoutePoint *prp = node->GetData();
            DrawPointLL(dc, prp->rlat, prp->rlon, prp->nPoint, &rptn);
//    printf("Line %d %d %d %d\n",rpt.x, rpt.y, rptn.x, rptn.y );

//            dc.DrawLine(rpt.x, rpt.y, rptn.x, rptn.y);
            DrawRouteLine(dc, rpt.x, rpt.y, rptn.x, rptn.y);            // with clipping
            rpt = rptn;

            node = node->GetNext();
      }

}

void Route::DrawRouteLine(wxDC& dc, int xa, int ya, int xb, int yb)
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
      {
//            printf("Clipped to %d %d %d %d\n",x0, y0, x1, y1 );
      //    And draw it
            dc.DrawLine(x0, y0, x1, y1);
      }
//      else
//            printf("Invisible\n");

}


RoutePoint *Route::InsertPoint(int nP, float rlat, float rlon)
{
      RoutePoint *np = new RoutePoint;
      np->rlat = rlat;
      np->rlon = rlon;
      np->m_bPtIsSelected = false;
      np->m_pParentRoute = this;
      np->nPoint = nP+1;

      pRoutePointList->Insert(nP, np);

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      int i = 1;
      while (node)
      {
            RoutePoint *prp = node->GetData();
            if(i > nP+1)
                  prp->nPoint += 1;

            node = node->GetNext();
            i++;

      }


      m_nPoints++;

      CalculateBBox();
      UpdateSegmentDistances();

      return(np);
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


void Route::DeletePoint(RoutePoint *rp)
{
      pRoutePointList->DeleteObject(rp);

      delete rp;

      RoutePoint *data_m1;
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

//    Summarily renumber all the points in the route
      int ip = 1;
      while (node)
      {
            data_m1 = node->GetData();
            data_m1->nPoint = ip;
            ip++;

            node = node->GetNext();
      }

      m_nPoints -= 1;

      CalculateBBox();
      UpdateSegmentDistances();

}

void Route::DeSelectRoute()
{
      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      RoutePoint *data;
      while (node)
      {
            data = node->GetData();
            data->m_bPtIsSelected = false;

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

            if(data->rlon > bbox_xmax)
                  bbox_xmax = data->rlon;
            if(data->rlon < bbox_xmin)
                  bbox_xmin = data->rlon;
            if(data->rlat > bbox_ymax)
                  bbox_ymax = data->rlat;
            if(data->rlat < bbox_ymin)
                  bbox_ymin = data->rlat;


            node = node->GetNext();
      }


      BBox.Expand(bbox_xmin, bbox_ymin);
      BBox.Expand(bbox_xmax, bbox_ymax);


}

void Route::UpdateSegmentDistances()
{
      wxPoint rpt, rptn;
      float slat1, slon1, slat2, slon2;

      wxRoutePointListNode *node = pRoutePointList->GetFirst();

      if(node)
      {
            RoutePoint *prp0 = node->GetData();
            slat1 = prp0->rlat;
            slon1 = prp0->rlon;

            node = node->GetNext();

            while (node)
            {
                  RoutePoint *prp = node->GetData();
                  slat2 = prp->rlat;
                  slon2 = prp->rlon;

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

                  slat1 = slat2;
                  slon1 = slon2;
                  prp0 = prp;

                  node = node->GetNext();
            }
      }

}




//-----------------------------------------------------------------------------
//          MyConfig
//-----------------------------------------------------------------------------


MyConfig::MyConfig(const wxString &appName, const wxString &vendorName, const wxString &LocalFileName)
      :wxFileConfig(appName, vendorName, LocalFileName)

{
}



int MyConfig::LoadMyConfig(int iteration)
{
      char buf[200];


//    Global options and settings
      SetPath("/Settings");

      m_bShowDebugWindows = false;
      Read("ShowDebugWindows", &m_bShowDebugWindows);

      g_bShowPrintIcon = false;
      Read("ShowPrintIcon", &g_bShowPrintIcon);

      SetPath("/Settings/GlobalState");
      Read("bFollow", &st_bFollow);


#ifdef USE_S57
    if(NULL != ps52plib)
    {
      SetPath("/Settings/GlobalState");
      Read("bShowS57Text", &st_bShowS57Text, 0);
      ps52plib->SetShowS57Text(st_bShowS57Text);

      SetPath("/Settings/GlobalState");
      Read("nDisplayCategory", &m_nDisplayCategory, (enum _DisCat)OTHER);
      ps52plib->m_nDisplayCategory = (enum _DisCat)m_nDisplayCategory;

      SetPath("/Settings/GlobalState");
      Read("nSymbolStyle", &m_nSymbolStyle, (enum _LUPname)PAPER_CHART);
      ps52plib->m_nSymbolStyle = m_nSymbolStyle;

      SetPath("/Settings/GlobalState");
      Read("nBoundaryStyle", &m_nBoundaryStyle, 0);
      ps52plib->m_nBoundaryStyle = m_nBoundaryStyle;
    }

    wxString strd("S57DataLocation");
    wxString val;
    SetPath("/Directories");
    Read(strd, &val);                 // Get the Directory name

    wxString dirname(val);
    if(!dirname.IsEmpty())
    {
        pcsv_locn->Clear();
        pcsv_locn->Append(val);
    }



#endif

      SetPath("/Settings/GlobalState");
      Read("nColorScheme", &m_nColorScheme, 0);
      gFrame->SetAndApplyColorScheme((ColorScheme)m_nColorScheme);



      SetPath("/Settings/NMEADataSource");
      Read(_T("Source"), pNMEADataSource, _T("NONE"));

      SetPath("/Settings/NMEAAutoPilotPort");
      Read(_T("Port"), pNMEA_AP_Port, _T("NONE"));

      SetPath("/Settings/WiFiServer");
      Read(_T("Server"), pWIFIServerName, _T("NONE"));

      SetPath("/Settings/AISPort");
      Read(_T("Port"), pAIS_Port, _T("NONE"));

//    Reasonable starting point
      vLat = START_LAT;                   // display viewpoint
      vLon = START_LON;

      gLat = START_LAT;                   // GPS position, as default
      gLon = START_LON;

      SetPath("/Settings/GlobalState");
      int nr = 0;
      wxString *st = new wxString;

      if(Read(wxString("VPLatLon"), st))
      {
            nr++;
            sscanf(st->c_str(), "%f,%f", &st_lat, &st_lon);
      }

      if(Read(wxString("VPScale"), st))
      {
            nr++;
            sscanf(st->c_str(), "%f", &st_view_scale);
      }

      delete st;

      if(nr == 2)
      {
//    Sanity check the lat/lon
            if((st_lat > 0.0) && (st_lat < 90.0))
                  vLat = st_lat;

            if((st_lon > -179.9) && (st_lon < 179.9))
                  vLon = st_lon;
      }







#ifdef USE_S57
//    S57 Object Class Visibility

      bool bNeedNew = true;
      OBJLElement *pOLE;

      SetPath("/Settings/ObjectFilter");

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

                        if(str.StartsWith("viz", &sObj))
                        {
                                 for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
                                 {
                                       pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));
                                       if(!strncmp(pOLE->OBJLName, sObj.c_str(), 6))
                                       {
                                             pOLE->nViz = val;
                                             bNeedNew = false;
                                             break;
                                       }
                                 }

                                 if(bNeedNew)
                                 {
                                       pOLE = (OBJLElement *)malloc(sizeof(OBJLElement));
                                       strcpy(pOLE->OBJLName, sObj.c_str());
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
      SetPath("/ChartDirectories");
      int iDirMax = GetNumberOfEntries();
      if(iDirMax)
      {
          pChartDirArray->Empty();
          wxString str, val;
          long dummy;

          int iDir = 0;
          bool bCont = pConfig->GetFirstEntry(str, dummy);
          while ( bCont )
          {
                pConfig->Read(str, &val);                 // Get a Directory name

                wxString dirname(val);
                if(!dirname.IsEmpty())
                    if(NULL != pChartDirArray)
                    pChartDirArray->Add(dirname);
                iDir++;

                bCont = pConfig->GetNextEntry(str, dummy);
          }

      }

//    Pens and Colors
      pRoutePen =             wxThePenList->FindOrCreatePen(wxColour(0,0,255), 2, wxSOLID);
      pSelectedRoutePen = wxThePenList->FindOrCreatePen(wxColour(255,0,0), 2, wxSOLID);
      pActiveRoutePen =   wxThePenList->FindOrCreatePen(wxColour(255,0,255), 2, wxSOLID);
      pActiveRoutePointPen = wxThePenList->FindOrCreatePen(wxColour(0,0,255), 2, wxSOLID);



//    Fonts

#ifdef __WXX11__
      SetPath("/Settings/X11Fonts");
#endif
#ifdef __WXGTK__
      SetPath("/Settings/GTKFonts");
#endif
#ifdef __WXMSW__
      SetPath("/Settings/MSWFonts");
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

        SetPath("/Routes");
        int iRoutes = GetNumberOfGroups();
        if(iRoutes)
        {
                    int rnt;

                    wxString str, val;
                    long dummy;
                    float rlat, rlon, prev_rlat, prev_rlon;
                    RoutePoint *pConfPoint, *prev_pConfPoint;

                    bool bCont = GetFirstGroup(str, dummy);
                    while ( bCont )
                    {
                            Route *pConfRoute = new Route();
                            pRouteList->Append(pConfRoute);

                            int RouteNum;
                            sscanf(str.c_str(), "RouteDefn%d", &RouteNum);
                            pConfRoute->ConfigRouteNum = RouteNum;

                            SetPath(str);
                            Read("RoutePoints", &val);                // nPoints
                            int nPoints = atoi(val);

                            pConfRoute->m_nPoints = nPoints;
                            for(int ip = 0 ; ip < nPoints ; ip++)
                            {
                                char ipb[20];
                                sprintf(ipb, "RoutePoint%d", ip+1);
                                wxString rps(ipb);
                                Read(rps, &val);                          // Point lat/lon
                                strcpy(buf,(char *)val.c_str());
                                sscanf(buf, "%f,%f", &rlat, &rlon);

                                pConfPoint = pConfRoute->AddPoint(rlat, rlon);
                                pSelect->AddSelectablePoint(rlat, rlon, pConfPoint);

                                if(ip)
                                {
                                        pSelect->AddSelectableRouteSegment(prev_rlat, prev_rlon, rlat, rlon,
                                                                                prev_pConfPoint, pConfPoint);
                                }


                                prev_rlat = rlat;
                                prev_rlon = rlon;
                                prev_pConfPoint = pConfPoint;

                            }


                            SetPath("..");
                            bCont = GetNextGroup(str, dummy);

        //    Get next available RouteDefnx number
                            sscanf((char *)str.c_str(), "RouteDefn%d", &rnt);
                            if(rnt > routenum)
                                routenum = rnt;

                    }
        }

        NextRouteNum = routenum + 1;
      }

      return(0);

}


bool MyConfig::AddNewRoute(Route *pr, int crm)
{
      char buf[20];
      char buf1[40];
      float rlat, rlon;
      int acrm;

      if(crm != -1)
            acrm = crm;
      else
            acrm = NextRouteNum;

      assert(abs(acrm < 1000));

//    Build the Group Name
      wxString t("/Routes/RouteDefn");
      sprintf(buf, "%d", acrm);
      t.Append(wxString(buf));

      SetPath(t);

      sprintf(buf, "%d", pr->m_nPoints);
      Write(wxString("RoutePoints"), buf);

      for(int ip=1 ; ip < pr->m_nPoints+1 ; ip++)
      {

            sprintf(buf, "RoutePoint%d", ip);

            pr->GetPoint(ip , &rlat, &rlon);
            sprintf(buf1, "%f,%f", rlat, rlon);

            Write(wxString(buf), wxString(buf1));
      }

      Flush();

      pr->ConfigRouteNum = acrm;

      if(crm == -1)
            NextRouteNum +=1;             // auto increment for next time

      return true;
}


bool MyConfig::UpdateRoute(Route *pr)
{
      char buf[20];

      assert(pr->ConfigRouteNum);

//    Build the Group Name
      wxString t("/Routes/RouteDefn");
      sprintf(buf, "%d", pr->ConfigRouteNum);
      t.Append(wxString(buf));

      DeleteGroup(t);

      AddNewRoute(pr, pr->ConfigRouteNum);

      return true;
}


bool MyConfig::DeleteRoute(Route *pr)
{
      char buf[20];

      assert(pr->ConfigRouteNum);

//    Build the Group Name
      wxString t("/Routes/RouteDefn");
      sprintf(buf, "%d", pr->ConfigRouteNum);
      t.Append(wxString(buf));

      DeleteGroup(t);

      Flush();

      return true;
}


bool MyConfig::UpdateChartDirs(wxArrayString *pdirlist)
{
      wxString key, dir;
      char buf[80];

      SetPath("/ChartDirectories");
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
            sprintf(buf, "ChartDir%d", iDir+1);

            Write(wxString(buf), dirn);

      }

      Flush();
      return true;
}



void MyConfig::UpdateSettings()
{
//    Global options and settings
      SetPath("/Settings");

      Write("ShowDebugWindows", m_bShowDebugWindows);
      Write("ShowPrintIcon", g_bShowPrintIcon);


//    S57 Object Filter Settings

      SetPath("/Settings/ObjectFilter");

#ifdef USE_S57
      if(ps52plib)
      {
            for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
            {
                  OBJLElement *pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));

                  char st1[20];
                  char *pv = st1;
                  strcpy(pv, "viz");

                  strcat(pv, pOLE->OBJLName);
                  Write(pv, pOLE->nViz);
            }
      }
#endif

//    Global State

      SetPath("/Settings/GlobalState");

      char st1[40];
      char *pv = st1;

      if(cc1->VPoint.bValid)
      {
            sprintf(pv, "%10.4f,%10.4f", cc1->VPoint.clat, cc1->VPoint.clon);
            Write("VPLatLon", pv);
            sprintf(pv, "%16.1f", cc1->VPoint.view_scale);
            Write("VPScale", pv);
      }


      //    Various Options
      SetPath("/Settings/GlobalState");
      Write("bFollow", cc1->m_bFollow);
      Write("nColorScheme", (int)gFrame->GetColorScheme());

#ifdef USE_S57
      Write("bShowS57Text", ps52plib->GetShowS57Text());
      Write("nDisplayCategory", (long)ps52plib->m_nDisplayCategory);
      Write("nSymbolStyle", ps52plib->m_nSymbolStyle);
      Write("nBoundaryStyle", ps52plib->m_nBoundaryStyle);

      SetPath("/Directories");
      Write("S57DataLocation", *pcsv_locn);

#endif


      if(nmea)
      {
          SetPath("/Settings/NMEADataSource");
          wxString source;
          nmea->GetSource(source);
          Write(_T("Source"), source);
      }

      if(pAPilot)
      {
        SetPath("/Settings/NMEAAutoPilotPort");
        wxString ap_port;
        pAPilot->GetAP_Port(ap_port);
        Write(_T("Port"), ap_port);
      }

      SetPath("/Settings/WiFiServer");
      Write(_T("Server"), *pWIFIServerName);


      if(pAIS)
      {
        SetPath("/Settings/AISPort");
        wxString ais_port;
        pAIS->GetSource(ais_port);
        Write(_T("Port"), ais_port);
      }


//    Fonts
#ifdef __WXX11__
      SetPath("/Settings/X11Fonts");
#endif
#ifdef __WXGTK__
      SetPath("/Settings/GTKFonts");
#endif
#ifdef __WXMSW__
      SetPath("/Settings/MSWFonts");
#endif

      int nFonts = pFontMgr->GetNumFonts();

      for(int i=0 ; i<nFonts ; i++)
      {
            wxString cfstring(*pFontMgr->GetConfigString(i));
            wxString valstring(*pFontMgr->GetDialogString(i));
            valstring.Append(":");
            valstring.Append(*pFontMgr->GetNativeDesc(i));
            Write(cfstring, valstring);
      }

      Flush();

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
      m_dialogstring = new wxString(DialogString);
      m_configstring = new wxString(ConfigString);

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
                  FALSE, wxString(""), wxFONTENCODING_SYSTEM );


}

FontMgr::~FontMgr()
{
      delete m_fontlist;
}


wxFont *FontMgr::GetFont(wxString &TextElement)
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
#ifdef __WXGTK__
      wxString nativefont(_T("Fixed 12"));
#endif
#ifdef __WXX11__
      wxString nativefont(_T("0;-*-fixed-*-*-*-*-*-120-*-*-*-*-iso8859-1"));
#endif
#ifdef __WXMSW__
      wxString nativefont(_T("0;-11;0;0;0;400;0;0;0;0;0;0;0;0;MS Sans Serif"));
#endif




      wxFont *nf0 = new wxFont();
      wxFont *nf = nf0->New(nativefont);

      MyFontDesc *pnewfd = new MyFontDesc(TextElement.c_str(), configstring.c_str(), nf);
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

            MyFontDesc *pnewfd = new MyFontDesc(dialogstring.c_str(), pConfigString->c_str(), nf);
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
      itemBoxSizer2->Add(itemBoxSizer3, 1, wxGROW|wxALL, 5);

      wxFlexGridSizer* itemGridSizer4 = new wxFlexGridSizer(noRows, noCols, 0, 0);
      itemBoxSizer3->Add(itemGridSizer4, 0, wxGROW, 5);

      wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW, 5);
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
      itemGridSizer4->Add(itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW, 5);
      wxStaticText* itemStaticText9 = new wxStaticText( this, wxID_STATIC, _("&Style:"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      wxChoice* itemChoice10 = new wxChoice( this, wxID_FONT_STYLE, wxDefaultPosition, wxDefaultSize);
      itemChoice10->SetHelpText(_("The font style."));
      if (ShowToolTips())
            itemChoice10->SetToolTip(_("The font style."));
      itemBoxSizer8->Add(itemChoice10, 0, wxALIGN_LEFT|wxALL, 5);

      wxBoxSizer* itemBoxSizer11 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW, 5);
      wxStaticText* itemStaticText12 = new wxStaticText( this, wxID_STATIC, _("&Weight:"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer11->Add(itemStaticText12, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      wxChoice* itemChoice13 = new wxChoice( this, wxID_FONT_WEIGHT, wxDefaultPosition, wxDefaultSize);
      itemChoice13->SetHelpText(_("The font weight."));
      if (ShowToolTips())
            itemChoice13->SetToolTip(_("The font weight."));
      itemBoxSizer11->Add(itemChoice13, 0, wxALIGN_LEFT|wxALL, 5);

      wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxVERTICAL);
      itemGridSizer4->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW, 5);
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
      itemGridSizer4->Add(itemBoxSizer17, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW, 5);
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
      itemBoxSizer3->Add(itemWindow24, 0, wxGROW, 5);

      wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
      itemBoxSizer3->Add(itemBoxSizer25, 0, wxGROW, 5);
      itemBoxSizer25->Add(5, 5, 1, wxGROW|wxALL, 5);

#ifdef __WXMAC__
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
#else
    wxButton* itemButton27 = new wxButton( this, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton27->SetDefault();
    itemButton27->SetHelpText(_("Click to confirm the font selection."));
    if (ShowToolTips())
          itemButton27->SetToolTip(_("Click to confirm the font selection."));
    itemBoxSizer25->Add(itemButton27, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton28 = new wxButton( this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    if (ShowToolTips())
          itemButton28->SetToolTip(_("Click to cancel the font selection."));
    itemBoxSizer25->Add(itemButton28, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
#endif

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

    int ptsz = atoi(pointsize.c_str());
    pointsize.Printf("%d", ptsz / 10);

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
      wxString pattern;
      pattern.Printf(wxT("-*-%s-*-*-*-*-*-*-*-*-*-*-iso8859-1"), facename.c_str());

      int nFonts;
      char ** list = XListFonts((Display *)wxGetDisplay(), pattern.mb_str(), 32767, &nFonts);

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
      //           printf("%s\n",facename.c_str());
                  for(jname=0 ; jname<PointSizeArray.GetCount() ; jname++)
                  {
                        if(pointsize == PointSizeArray.Item(jname))
                              break;
                  }
                  if(jname >= PointSizeArray.GetCount())
                  {
                        PointSizeArray.Add(pointsize);
//                        printf("Added %s\n", pointsize.c_str());
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
      //           printf("%s\n",facename.c_str());
            unsigned int jname;
            for(jname=0 ; jname<WeightArray.GetCount() ; jname++)
            {
                  if(weight == WeightArray.Item(jname))
                        break;
            }
            if(jname >= WeightArray.GetCount())
            {
                  WeightArray.Add(weight);
//                  printf("Added weight %s\n", weight.c_str());
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

//      printf("Init Fetching    %s\n", fontnative.c_str());

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

      wxString font_xlfd;
      font_xlfd.Printf((wxT("-*-%s-%s-r-normal-*-*-%s0-*-*-*-*-iso8859-1")),
                        facename.c_str(), weight.c_str(), pointsize.c_str());

//                  printf("Fetching    %s\n", font_xlfd.c_str());

      XFontStruct *test = XLoadQueryFont((Display *)wxGetDisplay(),font_xlfd.c_str());

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



/////////////

 #ifndef __CLIP_H__
  #define __CLIP_H__

 #ifdef __cplusplus
             extern "C" {
 #endif /* __cplusplus */

//typedef enum { NotClipped, WasClipped } ClipResult;

ClipResult cohen_sutherland_line_clip_d (double *x0, double *y0, double *x1, double *y1,
                              double xmin_, double xmax_, double ymin_, double ymax_);

//ClipResult cohen_sutherland_line_clip_i (int *x0, int *y0, int *x1, int *y1,
//                              int xmin_, int xmax_, int ymin_, int ymax_);

#ifdef __cplusplus
 }
#endif /* __cplusplus */

#endif /* __CLIP_H__ */

extern "C" {
      ClipResult cohen_sutherland_line_clip_i (int *x0, int *y0, int *x1, int *y1,
                                   int xmin_, int xmax_, int ymin_, int ymax_);
}
/*
*
* Copyright (C) 1999,2000,2001,2002,2003 Percy Zahl
*
* Authors: Percy Zahl <zahl@users.sf.net>
* additional features: Andreas Klust <klust@users.sf.net>
* WWW Home: http://gxsm.sf.net
*
*/

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

//#include "clip.h"

#define CTRUE -1
#define CFALSE 0

typedef enum {
      LEFT, RIGHT, BOTTOM, TOP
} edge;
typedef long outcode;


/* Local variables for cohen_sutherland_line_clip: */
struct LOC_cohen_sutherland_line_clip {
      double xmin, xmax, ymin, ymax;
} ;

void CompOutCode (double x, double y, outcode *code, struct LOC_cohen_sutherland_line_clip *LINK)
{
      /*Compute outcode for the point (x,y) */
      *code = 0;
      if (y > LINK->ymax)
                  *code = 1L << ((long)TOP);
      else if (y < LINK->ymin)
                  *code = 1L << ((long)BOTTOM);
      if (x > LINK->xmax)
                  *code |= 1L << ((long)RIGHT);
      else if (x < LINK->xmin)
                  *code |= 1L << ((long)LEFT);
}

ClipResult cohen_sutherland_line_clip_i (int *x0_, int *y0_, int *x1_, int *y1_,
                                         int xmin_, int xmax_, int ymin_, int ymax_)
{
      ClipResult ret;
      double x0,y0,x1,y1;
      x0 = *x0_;
      y0 = *y0_;
      x1 = *x1_;
      y1 = *y1_;
      ret = cohen_sutherland_line_clip_d (&x0, &y0, &x1, &y1,
                                          (double)xmin_, (double)xmax_,
                                          (double)ymin_, (double)ymax_);
      *x0_ = (int)x0;
      *y0_ = (int)y0;
      *x1_ = (int)x1;
      *y1_ = (int)y1;
      return ret;
}

ClipResult cohen_sutherland_line_clip_d (double *x0, double *y0, double *x1, double *y1,
                                         double xmin_, double xmax_, double ymin_, double ymax_)
{
      /* Cohen-Sutherland clipping algorithm for line P0=(x1,y0) to P1=(x1,y1)
            and clip rectangle with diagonal from (xmin,ymin) to (xmax,ymax).*/
      struct LOC_cohen_sutherland_line_clip V;
      int accept = CFALSE, done = CFALSE;
      ClipResult clip = Visible;
      outcode outcode0, outcode1, outcodeOut;
      /*Outcodes for P0,P1, and whichever point lies outside the clip rectangle*/
      double x=0., y=0.;

      V.xmin = xmin_;
      V.xmax = xmax_;
      V.ymin = ymin_;
      V.ymax = ymax_;
      CompOutCode(*x0, *y0, &outcode0, &V);
      CompOutCode(*x1, *y1, &outcode1, &V);
      do {
                  if (outcode0 == 0 && outcode1 == 0) {   /*Trivial accept and exit*/
                        accept = CTRUE;
                        done = CTRUE;
                  } else if ((outcode0 & outcode1) != 0) {
                        clip = Invisible;
                        done = CTRUE;
                  }
                  /*Logical intersection is true, so trivial reject and exit.*/
                  else {
                        clip = Visible;
                        /*Failed both tests, so calculate the line segment to clip;
                        from an outside point to an intersection with clip edge.*/
                        /*At least one endpoint is outside the clip rectangle; pick it.*/
                        if (outcode0 != 0)
                              outcodeOut = outcode0;
                        else
                              outcodeOut = outcode1;
                        /*Now find intersection point;
                        use formulas y=y0+slope*(x-x0),x=x0+(1/slope)*(y-y0).*/

                        if (((1L << ((long)TOP)) & outcodeOut) != 0) {
                              /*Divide line at top of clip rectangle*/
                              x = *x0 + (*x1 - *x0) * (V.ymax - *y0) / (*y1 - *y0);
                              y = V.ymax;
                        } else if (((1L << ((long)BOTTOM)) & outcodeOut) != 0) {
                              /*Divide line at bottom of clip rectangle*/
                              x = *x0 + (*x1 - *x0) * (V.ymin - *y0) / (*y1 - *y0);
                              y = V.ymin;
                        } else if (((1L << ((long)RIGHT)) & outcodeOut) != 0) {
                              /*Divide line at right edge of clip rectangle*/
                              y = *y0 + (*y1 - *y0) * (V.xmax - *x0) / (*x1 - *x0);
                              x = V.xmax;
                        } else if (((1L << ((long)LEFT)) & outcodeOut) != 0) {
                              /*Divide line at left edge of clip rectangle*/
                              y = *y0 + (*y1 - *y0) * (V.xmin - *x0) / (*x1 - *x0);
                              x = V.xmin;
                        }
                        /*Now we move outside point to intersection point to clip,
                        and get ready for next pass.*/
                        if (outcodeOut == outcode0) {
                              *x0 = x;
                              *y0 = y;
                              CompOutCode(*x0, *y0, &outcode0, &V);
                        } else {
                              *x1 = x;
                              *y1 = y;
                              CompOutCode(*x1, *y1, &outcode1, &V);
                        }
                  }
      } while (!done);
      return clip;
}

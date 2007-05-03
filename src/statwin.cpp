/******************************************************************************
 * $Id:
 *
 * Project:  OpenCPN
 * Purpose:  Status Window
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
 * $Log: statwin.cpp,v $
 * Revision 1.7  2007/05/03 13:23:56  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.6  2007/01/19 02:19:52  dsr
 * Improve bar scaling
 *
 * Revision 1.5  2006/12/03 21:17:24  dsr
 * Clear nRegions in ctor
 *
 * Revision 1.4  2006/10/07 03:50:28  dsr
 * *** empty log message ***
 *
 * Revision 1.3  2006/10/01 03:22:59  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:37:37  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.6  2006/08/04 11:42:03  dsr
 * no message
 *
 * Revision 1.5  2006/07/28 20:45:32  dsr
 * WiFi window status show.
 *
 * Revision 1.4  2006/07/06 23:14:59  dsr
 * Add WiFi Server Status Display
 *
 * Revision 1.3  2006/07/05 02:32:47  dsr
 * Add WiFi Client Status Window
 *
 * Revision 1.2  2006/05/19 19:29:33  dsr
 * Cleanup
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 *
 */



#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "dychart.h"

#include "statwin.h"
#include "chartdb.h"
#include "chart1.h"
#include "chartbase.h"

//------------------------------------------------------------------------------
//    External Static Storage
//------------------------------------------------------------------------------
extern ChartDB          *ChartData;
extern ChartStack       *pCurrentStack;
extern int              CurrentStackEntry;

CPL_CVSID("$Id: statwin.cpp,v 1.7 2007/05/03 13:23:56 dsr Exp $");

//------------------------------------------------------------------------------
//    StatWin Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(StatWin, wxWindow)
  EVT_PAINT(StatWin::OnPaint)
  EVT_SIZE(StatWin::OnSize)
  EVT_MOUSE_EVENTS(StatWin::MouseEvent)
END_EVENT_TABLE()

// ctor
StatWin::StatWin(wxFrame *frame):
 wxWindow(frame, wxID_ANY, wxPoint(20,20), wxSize(5,5), wxSIMPLE_BORDER)

{
      int x,y;
      GetClientSize(&x, &y);

      SetBackgroundColour(wxColour(150,150,150));

      m_rows = 1;

 //   Create the Children

      pPiano = new PianoWin((wxFrame *)this);
      pPiano->SetSize(0, 0, x *6/10, y*1/m_rows);

#ifdef USE_WIFI_CLIENT
      pWiFi = new WiFiStatWin((wxFrame *)this);
      pWiFi->SetSize(x * 6/10, 0, x *4/10, y * 1/m_rows);
#endif

 }

StatWin::~StatWin()
{
}



void StatWin::OnPaint(wxPaintEvent& event)
{
      pPiano->Refresh(false);
//      pTStat1->Refresh(false);
//      pTStat2->Refresh(false);

      wxPaintDC dc(this);
}


void StatWin::OnSize(wxSizeEvent& event)
{
      int width,height;
      this->GetClientSize(&width, &height);
      int x,y;
      this->GetPosition(&x, &y);

      if(width) pPiano->SetSize(0,0, width *6/10, height*1/m_rows);
 //     if(width) pTStat1->SetSize(0,height * 1/m_rows, width, height*1/m_rows);
 //     if(width) pTStat2->SetSize(0,height * 2/m_rows, width, height*1/m_rows);

#ifdef USE_WIFI_CLIENT
      if(width) pWiFi->SetSize(width * 6/10, 0, width *4/10, height*1/m_rows);
#endif

}

void StatWin::FormatStat(void)
{

      pPiano->FormatKeys();
}

void StatWin::MouseEvent(wxMouseEvent& event)
{
      int x,y;
      event.GetPosition(&x, &y);

}

int StatWin::GetFontHeight()
{
      wxClientDC dc(this);

      wxCoord w,h;
      GetTextExtent("TEST", &w, &h);

      return(h);
}



//------------------------------------------------------------------------------
//          TextStat Window Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(TStatWin, wxWindow)
  EVT_PAINT(TStatWin::OnPaint)
  EVT_SIZE(TStatWin::OnSize)
END_EVENT_TABLE()

TStatWin::TStatWin(wxFrame *frame):
      wxWindow(frame, wxID_ANY,wxPoint(20,20), wxSize(5,5), wxSIMPLE_BORDER)
{
      SetBackgroundColour(wxColour(150,150,150));
      pText = NULL;
      bTextSet = false;

}

TStatWin::~TStatWin(void)
{
      if(bTextSet && pText)
            free(pText);
}


void TStatWin::OnSize(wxSizeEvent& event)
{
}

void TStatWin::OnPaint(wxPaintEvent& event)
{
      wxPaintDC dc(this);
      dc.DrawText(pText, 0, 0);
}

void TStatWin::TextDraw(const char *text)
{
      if(bTextSet && pText)
            free(pText);

      pText = (char *)malloc(strlen(text) + 1);
      bTextSet = true;

      strcpy(pText, text);
      Refresh(true);
}




//------------------------------------------------------------------------------
//          Piano Window Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(PianoWin, wxWindow)
  EVT_PAINT(PianoWin::OnPaint)
  EVT_SIZE(PianoWin::OnSize)
  EVT_MOUSE_EVENTS(PianoWin::MouseEvent)
END_EVENT_TABLE()

// Define a constructor
PianoWin::PianoWin(wxFrame *frame):
      wxWindow(frame, wxID_ANY, wxPoint(20,20), wxSize(5,5), wxSIMPLE_BORDER)
{
      SetBackgroundColour(wxColour(150,150,150));
      index_last = -1;

 // Create/Get some brush pointers
    pbackBrush = wxTheBrushList->FindOrCreateBrush(wxColour(150,150,150), wxSOLID);    // Solid background
    ptBrush =    wxTheBrushList->FindOrCreateBrush(wxColour( 45, 45,170), wxSOLID);    // Raster Chart
    pslBrush =   wxTheBrushList->FindOrCreateBrush(wxColour(170,170,255), wxSOLID);

    pvBrush =    wxTheBrushList->FindOrCreateBrush(wxColour( 45, 150,45), wxSOLID);    // Vector Chart
    psvBrush =   wxTheBrushList->FindOrCreateBrush(wxColour(120,255,120), wxSOLID);    // and selected
    puvBrush =   wxTheBrushList->FindOrCreateBrush(wxColour( 96, 96, 96), wxSOLID);    // and unavailable

    gparent = (MyFrame *)GetGrandParent();

    nRegions = 0;
 }

PianoWin::~PianoWin()
{
}



void PianoWin::OnSize(wxSizeEvent& event)
{
}

void PianoWin::OnPaint(wxPaintEvent& event)
{
      int width, height;
      GetClientSize(&width, &height );
      wxPaintDC dc(this);

      if(!pCurrentStack)                        // Stack must be valid
            return;

      dc.SetBackground(*pbackBrush);
      dc.Clear();

//    Create the Piano Keys

      int nKeys = pCurrentStack->nEntry;

      assert(nKeys <= KEY_REGIONS_MAX);

      if(nKeys)
      {

            wxPen ppPen(wxColour(0,0,0), 1, wxSOLID);
            dc.SetPen(ppPen);

            dc.SetBrush(*ptBrush);


//      If no S57 support, mark the chart as "unavailable"
            for(int i=0 ; i<nKeys ; i++)
            {
                  if(ChartData->GetCSChartType(pCurrentStack, i) == CHART_TYPE_S57)
#ifndef USE_S57
                        dc.SetBrush(*puvBrush);
#else
                        dc.SetBrush(*pvBrush);
#endif
                  else
                        dc.SetBrush(*ptBrush);

                  dc.DrawRectangle(KeyRegion[i].GetBox());
            }

            if(ChartData->GetCSChartType(pCurrentStack, CurrentStackEntry) == CHART_TYPE_S57)
#ifndef USE_S57
                dc.SetBrush(*puvBrush);
#else
                dc.SetBrush(*psvBrush);
#endif
            else
                  dc.SetBrush(*pslBrush);

            dc.DrawRectangle(KeyRegion[CurrentStackEntry].GetBox());

      }
}

void PianoWin::FormatKeys(void)
{
      int width, height;
      this->GetClientSize(&width, &height );

      if(!pCurrentStack)
            return;

      int nKeys = pCurrentStack->nEntry;

      if(nKeys)
      {
            int kw = width / nKeys;

//    Build the Key Regions

            assert(nKeys <= KEY_REGIONS_MAX);

            for(int i=0 ; i<nKeys ; i++)
            {
                  wxRegion r((i * kw) +3, 2, kw-6, height-4);
                  KeyRegion[i] = r;
            }
      }
      nRegions = nKeys;

}

void PianoWin::MouseEvent(wxMouseEvent& event)
{

      int x,y;
      event.GetPosition(&x, &y);

//    Check the regions

      if(event.LeftDown())
      {
            if(nRegions)
            {
                  for(int i=0 ; i<nRegions ; i++)
                  {
                        if(KeyRegion[i].Contains(x,y)  == wxInRegion)
                        {
                              gparent->SelectChartFromStack(i);
                        }
                  }
            }
      }

      else
      {
            if(nRegions)
            {
                  for(int i=0 ; i<nRegions ; i++)
                  {
                        if(KeyRegion[i].Contains(x,y)  == wxInRegion)
                        {
                              if(i != index_last)
                              {
                                    gparent->SetChartThumbnail(i);
                                    index_last = i;
                              }

                        }
                  }
            }
      }

      if(event.Leaving())
      {
            gparent->SetChartThumbnail(-1);
            index_last = -1;
      }

      /*
      Todo:
      Could do something like this to better encapsulate the pianowin
      Allows us to get rid of global statics...

      wxCommandEvent ev(MyPianoEvent);    // Private event
      ..set up event to specify action...SelectChart, SetChartThumbnail, etc
      ::PostEvent(pEventReceiver, ev);    // event receiver passed to ctor

      */

}

#ifdef USE_WIFI_CLIENT
//------------------------------------------------------------------------------
//          WiFiStat Window Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(WiFiStatWin, wxWindow)
        EVT_PAINT(WiFiStatWin::OnPaint)
        EVT_SIZE(WiFiStatWin::OnSize)
        END_EVENT_TABLE()

WiFiStatWin::WiFiStatWin(wxFrame *frame):
        wxWindow(frame, wxID_ANY,wxPoint(20,20), wxSize(5,5), wxSIMPLE_BORDER)
{
    SetBackgroundColour(wxColour(150,150,150));
    pbackBrush = wxTheBrushList->FindOrCreateBrush(wxColour(150,150,150), wxSOLID);    // Solid background

    pqual_hiBrush =   wxTheBrushList->FindOrCreateBrush(wxColour(240,240,000), wxSOLID);    //Yellow
    psecureBrush =    wxTheBrushList->FindOrCreateBrush(wxColour(255,140, 50), wxSOLID);    //Orange

    pqual_hiNewBrush =   wxTheBrushList->FindOrCreateBrush(wxColour(000,255,000), wxSOLID); //Green
    psecureNewBrush =    wxTheBrushList->FindOrCreateBrush(wxColour(255,000,000), wxSOLID); //Red

    for(int ista = 0 ; ista < NSIGBARS ; ista++)
        m_quality[ista] = 0;

    m_bserverstat = true;

}

WiFiStatWin::~WiFiStatWin(void)
{
}


void WiFiStatWin::OnSize(wxSizeEvent& event)
{
}

void WiFiStatWin::OnPaint(wxPaintEvent& event)
{
    int width, height;
    GetClientSize(&width, &height );
    wxPaintDC dc(this);

    dc.SetBackground(*pbackBrush);
    dc.Clear();

    int bar_total = width / NSIGBARS;

//    Create the Signal Strength Indicators
    dc.SetBrush(*pbackBrush);
    wxPen ppPen(wxColour(0,0,0), 1, wxSOLID);
    dc.SetPen(ppPen);

    if(m_bserverstat)
    {
        for(int ista = 0 ; ista < NSIGBARS ; ista++)
        {
            if(0 != m_quality[ista])
            {
                int x = width - bar_total * (ista + 1);

                dc.SetBrush(*pbackBrush);
                dc.DrawRectangle(x+2, 2, bar_total-4 , height-4);

                // Old stations get soft color bars
                if(m_age[ista])
                {
                    dc.SetBrush(*pqual_hiBrush);
                    if(m_secure[ista])
                        dc.SetBrush(*psecureBrush);
                }
                else
                {
                    dc.SetBrush(*pqual_hiNewBrush);
                    if(m_secure[ista])
                        dc.SetBrush(*psecureNewBrush);
                }

                DrawBars(dc, x+2, 2, bar_total-4 , height-4, m_quality[ista], 100);
            }
        }
    }
    else
    {
        wxPen yellowPen(wxColour(192,192,0), 3, wxSOLID);
        dc.SetPen(yellowPen);

        dc.DrawLine(1, 1, width-1, 1);
        dc.DrawLine(width-1, 1, width-1, height-1);
        dc.DrawLine(width-1, height-1, 1, height-1);
        dc.DrawLine(1, height-1, 1, 1);
    }
}


void WiFiStatWin::DrawBars(wxDC &dc, int x, int y, int box_width, int box_height, int val, int val_max)
{
    int xb;
    //  Scale onto 0..50, so we can draw 5 bars = 50 points
    int aval = (val * 50) / val_max;

    int nBars = ((aval) / 10);

    int bar_w = box_width / 5;

    for(int i=0 ; i<nBars ; i++)
    {
        xb = x + (i * bar_w) + 2;
        dc.DrawRectangle(xb, y+2, bar_w - 2 , box_height-4);
    }

    // partial bar
    xb += bar_w;
    dc.DrawRectangle(xb, y+2, bar_w * (aval % 10) / 10, box_height-4);

}



void WiFiStatWin::TextDraw(const char *text)
{
    Refresh(true);
}

void WiFiStatWin::SetNumberStations(int n)
{
    m_nstations = n;

    Refresh(true);
}

void WiFiStatWin::SetStationQuality(int istation, int quality)
{
    m_quality[istation] = quality;
}
void WiFiStatWin::SetStationSecureFlag(int istation, int flag)
{
    m_secure[istation] = flag;
}
void WiFiStatWin::SetStationAge(int istation, int age)
{
    m_age[istation] = age;
}

#endif



/******************************************************************************
 * $Id: concanv.cpp,v 1.10 2009/03/26 22:29:16 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Console Canvas
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
 * $Log: concanv.cpp,v $
 * Revision 1.10  2009/03/26 22:29:16  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.9  2008/08/26 13:46:25  bdbcat
 * Better color scheme support
 *
 * Revision 1.8  2008/04/10 01:05:49  bdbcat
 * Cleanup
 *
 * Revision 1.7  2008/03/30 22:00:27  bdbcat
 * Cleanup
 *
 * $Log: concanv.cpp,v $
 * Revision 1.10  2009/03/26 22:29:16  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.9  2008/08/26 13:46:25  bdbcat
 * Better color scheme support
 *
 * Revision 1.8  2008/04/10 01:05:49  bdbcat
 * Cleanup
 *
 * Revision 1.7  2008/03/30 22:00:27  bdbcat
 * Cleanup
 *
 * Revision 1.6  2008/01/12 06:23:42  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.5  2008/01/10 03:36:19  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.4  2007/06/10 02:27:30  bdbcat
 * Color scheme support
 *
 * Revision 1.3  2007/05/03 13:23:55  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.2  2006/10/05 03:49:31  dsr
 * cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.2  2006/04/23 03:54:12  dsr
 * Cleanup leaks
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.6  2006/04/19 02:00:39  dsr
 * Show Normal arrival distance
 *
 * Revision 1.5  2006/04/19 00:43:42  dsr
 * FontMgr experimental code
 *
 * Revision 1.4  2006/03/16 03:08:00  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/02/23 01:40:14  dsr
 * Cleanup
 *
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
#include "wx/datetime.h"

#include "chart1.h"
#include "concanv.h"
#include "routeman.h"
#include "navutil.h"

extern Routeman         *pRouteMan;
extern FontMgr          *pFontMgr;

extern                  double gCog;
extern                  double gSog;


CPL_CVSID("$Id: concanv.cpp,v 1.10 2009/03/26 22:29:16 bdbcat Exp $");


//------------------------------------------------------------------------------
//    ConsoleCanvas Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ConsoleCanvas, wxWindow)
      EVT_PAINT(ConsoleCanvas::OnPaint)
      EVT_SIZE(ConsoleCanvas::OnSize)
      EVT_MOUSE_EVENTS(ConsoleCanvas::MouseEvent)
END_EVENT_TABLE()

// Define a constructor for my canvas
ConsoleCanvas::ConsoleCanvas(wxFrame *frame):
            wxWindow(frame, wxID_ANY,   wxPoint(20,20), wxSize(5,5),wxNO_BORDER/*wxSUNKEN_BORDER | wxCLIP_CHILDREN*/ )
{

      pThisLegBox = new wxStaticBox(this, -1, _T("This Leg"), wxPoint(1,1),
                                    wxSize(170,200), 0, _T("staticBox"));

      pSBoxRgn = new wxRegion(pThisLegBox->GetRect() );

      pThisLegFont = wxTheFontList->FindOrCreateFont(12, wxDEFAULT,wxNORMAL, wxBOLD, FALSE,
              wxString(_T("Eurostile Extended")));

      pThisLegBox->SetFont(*pThisLegFont);

      pXTE = new AnnunText(this, -1,wxPoint(10,20), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pXTE->SetALabel(_T("XTE"));

      pBRG = new AnnunText(this, -1,wxPoint(10,75), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pBRG->SetALabel(_T("BRG"));

      pRNG = new AnnunText(this, -1,wxPoint(10,130), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pRNG->SetALabel(_T("RNG"));

      pTTG = new AnnunText(this, -1,wxPoint(10,185), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pTTG->SetALabel(_T("TTG"));


//    Create CDI Display Window

      pCDI = new CDI(this, -1, wxPoint(0,200), wxSize(100, 200), wxSIMPLE_BORDER, _T("CDI"));

      m_bShowRouteTotal = false;

      Hide();
}


 ConsoleCanvas::~ConsoleCanvas()
{
      delete pCDI;
      delete pSBoxRgn;
}


void ConsoleCanvas::OnSize(wxSizeEvent& event)
{
      int canvas_width, canvas_height;
      GetClientSize(&canvas_width, &canvas_height);

      pThisLegBox->SetSize(1,1,canvas_width-2,240);

      int CDIHeight = canvas_width /2;
      pCDI->SetSize(2, canvas_height - CDIHeight - 12, canvas_width-4, CDIHeight);

}

void ConsoleCanvas::SetColorScheme(ColorScheme cs)
{
    pbackBrush = wxTheBrushList->FindOrCreateBrush(GetGlobalColor(_T("DILG1"/*UIBDR*/)), wxSOLID);
    SetBackgroundColour(GetGlobalColor(_T("DILG1"/*"UIBDR"*/)));

    //  Also apply color scheme to all known children

    pThisLegBox->SetBackgroundColour(GetGlobalColor(_T("DILG1"/*"UIBDR"*/)));

    pXTE->SetColorScheme(cs);
    pBRG->SetColorScheme(cs);
    pRNG->SetColorScheme(cs);
    pTTG->SetColorScheme(cs);

    pCDI->SetColorScheme(cs);
}


void ConsoleCanvas::OnPaint(wxPaintEvent& event)
{
      int x,y;
      GetClientSize(&x, &y);
      wxString str_buf;

      wxPaintDC dc(this);

      if(pRouteMan->GetpActiveRoute())
      {
            if(m_bNeedClear)
            {
                  ClearBackground();
                  pThisLegBox->Refresh();
                  m_bNeedClear = false;
            }


            if(pRouteMan->m_bDataValid)
            {

//    Range
                  wxString srng;
                  float rng = pRouteMan->GetCurrentRngToActivePoint();
                  float nrng = pRouteMan->GetCurrentRngToActiveNormalArrival();
                  if(fabs(rng - nrng) > .01)
                  {
                        if(nrng < 10.0)
                            srng.Printf(_T("%5.2f/%5.2f"), rng, nrng );
                        else
                            srng.Printf(_T("%5.1f/%5.1f"), rng, nrng );
                  }
                  else
                  {
                        if(rng < 10.0)
                            srng.Printf(_T("%6.2f"), rng );
                        else
                            srng.Printf(_T("%6.1f"), rng );
                  }


                  if(!m_bShowRouteTotal)
                        pRNG->SetAValue(srng);

//    Brg
                  str_buf.Printf(_T("%6.0f"), pRouteMan->GetCurrentBrgToActivePoint());
                  pBRG->SetAValue(str_buf);

//    XTE
                  str_buf.Printf(_T("%6.2f"), pRouteMan->GetCurrentXTEToActivePoint());
                  pXTE->SetAValue(str_buf);
                  if(pRouteMan->GetXTEDir() < 0)
                      pXTE->SetALabel(wxString(_T("XTE         L")));
                  else
                      pXTE->SetALabel(wxString(_T("XTE         R")));

//    TTG
                  float ttg_sec = (rng / gSog) * 3600.;
                  wxTimeSpan ttg_span(0, 0, long(ttg_sec), 0);
                  wxString ttg_s = ttg_span.Format();
                  if(!m_bShowRouteTotal)
                        pTTG->SetAValue(ttg_s);

      //    Remainder of route
                  float trng = rng;

                  Route *prt = pRouteMan->GetpActiveRoute();
                  wxRoutePointListNode *node = (prt->pRoutePointList)->GetFirst();
                  RoutePoint *prp;

                  int n_addflag = 0;
                  while(node)
                  {
                        prp = node->GetData();
                        if(n_addflag)
                              trng += prp->m_seg_len;

                        if(prp == prt->m_pRouteActivePoint)
                              n_addflag ++;

                        node=node->GetNext();
                  }

//                total rng
                  wxString strng;
                  if(trng < 10.0)
                      strng.Printf(_T("%6.2f"), trng );
                  else
                      strng.Printf(_T("%6.1f"), trng );

                  if(m_bShowRouteTotal)
                        pRNG->SetAValue(strng);

//                total ttg
                  float tttg_sec = (trng / gSog) * 3600.;
                  wxTimeSpan tttg_span(0, 0, long(tttg_sec), 0);
                  wxString tttg_s = tttg_span.Format();
                  if(m_bShowRouteTotal)
                        pTTG->SetAValue(tttg_s);

//                total ETA to be shown on XTE panel
                  wxDateTime dtnow, eta;
                  dtnow.SetToCurrent();
                  eta = dtnow.Add(tttg_span);
                  wxString seta = eta.FormatTime();

                  if(m_bShowRouteTotal)
                  {
                        pXTE->SetAValue(seta);
                        pXTE->SetALabel(wxString(_T("ETA          ")));
                  }
            }
      }
}


void ConsoleCanvas::UpdateRouteData()
{
      if(pRouteMan->GetpActiveRoute())
      {
            m_bRouteDataStale = true;
            Refresh(true);
      }
      else if(!IsShown())
      {
            m_bNeedClear = true;
      }
}


void ConsoleCanvas::MouseEvent(wxMouseEvent& event)
{

      int x,y;
      event.GetPosition(&x, &y);

      ///TODO  Why is this necessary???
#ifndef __WXGTK__
      {
        if(!HasCapture())
            CaptureMouse();

        if(event.Leaving())
            if(HasCapture())
                  ReleaseMouse();
      }
#endif

      if(event.IsButton())
//            wxLogMessage(_T("concanv::MouseEvent Button"));
//    Check the regions

      if(event.LeftDown())
      {
            wxRect br = pSBoxRgn->GetBox();
            if(pSBoxRgn->Contains(x,y)  == wxInRegion)
            {
                  m_bShowRouteTotal = !m_bShowRouteTotal;
                  if(m_bShowRouteTotal)
                        pThisLegBox->SetLabel(_T("Route"));
                  else
                        pThisLegBox->SetLabel(_T("This Leg"));

                  pThisLegBox->Refresh(true);
            }
      }

      else
      {
            wxRegion rr(GetRect());
#ifdef __WXMSW__
            if(rr.Contains(x,y)  != wxInRegion)
            {
//                  wxLogMessage(_T("concanv::MouseEvent releasing mouse"));
                  ReleaseMouse();
            }
#endif
      }

}

void ConsoleCanvas::ShowWithFreshFonts(void)
{
      pBRG->RefreshFonts();
      pXTE->RefreshFonts();
      pTTG->RefreshFonts();
      pRNG->RefreshFonts();

      Show();
}




//------------------------------------------------------------------------------
//    AnnunText Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(AnnunText, wxWindow)
      EVT_PAINT(AnnunText::OnPaint)
END_EVENT_TABLE()


AnnunText::AnnunText(wxWindow *parent, wxWindowID id,
                               const wxPoint& pos, const wxSize& size, const wxString& LegendElement, const wxString& ValueElement):
        wxWindow(parent, id, pos, size, wxSIMPLE_BORDER/*wxSUNKEN_BORDER*/, wxString(_T("")))
{
      label = new wxString(_T("Label"));
      value = new wxString(_T("-----"));

      plabelFont = wxTheFontList->FindOrCreateFont(14, wxFONTFAMILY_SWISS,wxNORMAL, wxBOLD, FALSE,
              wxString(_T("Arial Bold")));
      pvalueFont = wxTheFontList->FindOrCreateFont(24, wxFONTFAMILY_DEFAULT,wxNORMAL, wxBOLD, FALSE,
              wxString(_T("helvetica")), wxFONTENCODING_ISO8859_1);


      pLegendTextElement = new wxString( LegendElement );
      pValueTextElement = new wxString( ValueElement );

      plabelFont = pFontMgr->GetFont(*pLegendTextElement);
      pvalueFont = pFontMgr->GetFont(*pValueTextElement);

/*
      // Calculate font sizes
      int mmx, mmy;
      wxDisplaySizeMM(&mmx, &mmy);
      int sx, sy;
      wxDisplaySize(&sx, &sy);

      float mm_per_pixel = ((float)mmy)/((float)sy);

      int sixe_x, size_y;
      GetSize(&sixe_x, &size_y);

      float font_twips = size_y * 0.6;
      font_twips = font_twips * mm_per_pixel /25.4;         // inches
      font_twips = font_twips * 720;

      int itwips = (int)font_twips;

      wxString xFontName;
      */
#if 0
      if(MyBuildXFontSpec(-1, itwips,  wxFONTFAMILY_DEFAULT, wxNORMAL, wxFONTWEIGHT_BOLD, 0,
         wxString("nimbus sans l"), wxString("iso8859"), wxString("1"), &xFontName))
      {
            wxLogMessage(_T("Found Font, itwips = %d"), itwips);
            xFontName.Prepend("0;");
            wxFont *ptf = new wxFont;
            pvalueFont = ptf->New(xFontName);
// Doesn't work??
//          pvalueFont = ptf->New(wxSize(-1, 44), wxFONTFAMILY_DEFAULT, wxNORMAL, wxFONTWEIGHT_BOLD, false,
//                                  wxString("nimbus sans l"), wxFONTENCODING_ISO8859_1);
      }
#endif


      /*
      wxString pattern;
//      pattern.Printf(wxT("-*-%s-*-*-*-*-*-*-*-*-*-*-*-*"),
//                     "utopia");

//      pattern.Printf(wxT("-*-*-*-*-*-*-*-*-*-*-*-*-*-*"));
      pattern.Printf(wxT("-*-%s-*-r-normal-*-*-*-*-*-*-*-%s-%s"),  ///CANNOT Printf %s
                        "utopia",
                     info.xregistry.mb_str(),
                     info.xencoding.mb_str());

    // get the list of all fonts
      int nFonts;
      char ** list = XListFonts((Display *)wxGetDisplay(), pattern.mb_str(), 32767, &nFonts);

      for(int i=0 ; i < nFonts ; i++)
      {
            char *pname = list[i];
            printf("%s\n", pname);
      }

      MyFontEnumerator fe;
      fe.EnumerateFacenames(wxFONTENCODING_ISO8859_1 );


      wxArrayString Names = fe.GetFacenames();
      int nNames = Names.GetCount();

      for(int i=0 ; i < nNames ; i++)
      {
            wxString name = Names.Item(i);
            printf("%s\n", name.mb_str());
      }

//      wxString fd = pvalueFont->GetNativeFontInfoDesc();
    wxFontDialog dg(this, NULL);
//      dg.ShowModal();
*/
}

AnnunText::~AnnunText()
{
      delete label;
      delete value;
      delete pLegendTextElement;
      delete pValueTextElement;

}
void AnnunText::SetColorScheme(ColorScheme cs)
{
      pbackBrush = wxTheBrushList->FindOrCreateBrush(GetGlobalColor(_T("UBLCK"/*"UIBCK"*/)), wxSOLID);

      m_text_color = GetGlobalColor(_T("GREEN4"/*"UINFD"*/));
}



void AnnunText::RefreshFonts()
{
      plabelFont = pFontMgr->GetFont(*pLegendTextElement);
      pvalueFont = pFontMgr->GetFont(*pValueTextElement);

}

void AnnunText::SetLegendElement(const wxString &element)
{
      delete pLegendTextElement;
      pLegendTextElement = new wxString( element );
}

void AnnunText::SetValueElement(const wxString &element)
{
      delete pValueTextElement;
      pValueTextElement = new wxString( element );
}




void AnnunText::SetALabel(const wxString &l)
{
      *label = l;
}

void AnnunText::SetAValue(const wxString &v)
{
      *value = v;
}

void AnnunText::OnPaint(wxPaintEvent& event)
{
      int sx,sy;
      GetClientSize(&sx, &sy);

      //    Do the drawing on an off-screen memory DC, and blit into place
      //    to avoid objectionable flashing
      wxMemoryDC mdc;

      wxBitmap m_bitmap(sx, sy, -1);
      mdc.SelectObject(m_bitmap);
      mdc.SetBackground(*pbackBrush);
      mdc.Clear();

      mdc.SetTextForeground(m_text_color);

      if(plabelFont)
      {
          wxString nfi = plabelFont->GetNativeFontInfoDesc();
            mdc.SetFont(*plabelFont);
            mdc.DrawText(*label, 5, 2);
      }

      if(pvalueFont)
      {
            mdc.SetFont(*pvalueFont);

            int w, h;
            mdc.GetTextExtent(*value, &w, &h);
            int cw, ch;
            mdc.GetSize(&cw, &ch);

            mdc.DrawText(*value, cw - w - 2, ch - h - 2);
      }

      wxPaintDC dc(this);
      dc.Blit(0, 0, sx, sy, &mdc, 0, 0);

}





//------------------------------------------------------------------------------
//    CDI Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(CDI, wxWindow)
      EVT_PAINT(CDI::OnPaint)
END_EVENT_TABLE()


CDI::CDI(wxWindow *parent, wxWindowID id,
             const wxPoint& pos, const wxSize& size, long style, const wxString& name):
            wxWindow(parent, id, pos, size, style, name)

{
}

void CDI::SetColorScheme(ColorScheme cs)
{
    m_pbackBrush = wxTheBrushList->FindOrCreateBrush(GetGlobalColor(_T("DILG2")), wxSOLID);
    m_proadBrush = wxTheBrushList->FindOrCreateBrush(GetGlobalColor(_T("DILG1")), wxSOLID);
    m_proadPen = wxThePenList->FindOrCreatePen(GetGlobalColor(_T("CHBLK")), 1, wxSOLID);
}


void CDI::OnPaint(wxPaintEvent& event)
{
      int sx,sy;
      GetClientSize(&sx, &sy);

      //    Do the drawing on an off-screen memory DC, and blit into place
      //    to avoid objectionable flashing
      wxMemoryDC mdc;

      wxBitmap m_bitmap(sx, sy, -1);
      mdc.SelectObject(m_bitmap);
      mdc.SetBackground(*m_pbackBrush);
      mdc.Clear();

      int xp = sx/2;
      int yp = sy*9/10;

      int path_length = sy * 3;
      int pix_per_xte = 120;

      if(pRouteMan->GetpActiveRoute())
      {
            double angle = 90 - (pRouteMan->GetCurrentSegmentCourse() - gCog);

            double dy = path_length * sin(angle *PI/180.);
            double dx = path_length * cos(angle *PI/180.);

            int xtedir;
            xtedir = pRouteMan->GetXTEDir();
            double xte = pRouteMan->GetCurrentXTEToActivePoint();

            double ddy = xtedir * pix_per_xte * xte * sin((90 - angle) *PI/180.);
            double ddx = xtedir * pix_per_xte * xte * cos((90 - angle) *PI/180.);

            int ddxi = (int)ddx;
            int ddyi = (int)ddy;

            int xc1 = xp - (int)(dx/2) + ddxi;
            int yc1 = yp + (int)(dy/2) + ddyi;
            int xc2 = xp + (int)(dx/2) + ddxi;
            int yc2 = yp - (int)(dy/2) + ddyi;


            wxPoint road[4];

            int road_top_width = 10;
            int road_bot_width = 40;

            road[0].x = xc1 - (int)(road_bot_width * cos((90 - angle) *PI/180.));
            road[0].y = yc1 - (int)(road_bot_width * sin((90 - angle) *PI/180.));

            road[1].x = xc2 - (int)(road_top_width * cos((90 - angle) *PI/180.));
            road[1].y = yc2 - (int)(road_top_width * sin((90 - angle) *PI/180.));

            road[2].x = xc2 + (int)(road_top_width * cos((90 - angle) *PI/180.));
            road[2].y = yc2 + (int)(road_top_width * sin((90 - angle) *PI/180.));

            road[3].x = xc1 + (int)(road_bot_width * cos((90 - angle) *PI/180.));
            road[3].y = yc1 + (int)(road_bot_width * sin((90 - angle) *PI/180.));

            mdc.SetBrush(*m_proadBrush);
            mdc.SetPen(*m_proadPen);
            mdc.DrawPolygon(4, road,0,0,wxODDEVEN_RULE);

            mdc.DrawLine(xc1, yc1, xc2, yc2);

            mdc.DrawLine(0, yp, sx, yp);
            mdc.DrawCircle(xp,yp,6);
            mdc.DrawLine(xp, yp+5, xp, yp-5);
      }

      wxPaintDC dc(this);
      dc.Blit(0, 0, sx, sy, &mdc, 0, 0);
}




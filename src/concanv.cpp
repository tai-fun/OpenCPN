/******************************************************************************
 * $Id: concanv.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $
 *
 * Project:  OpenCP
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
 * Revision 1.1  2006/08/21 05:52:19  dsr
 * Initial revision
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

#ifdef __WXMSW__
  #include <stdlib.h>
  #include <math.h>
  #include <time.h>
  #include "wx/datetime.h"
#endif

#include "chart1.h"
#include "concanv.h"
#include "routeman.h"
#include "navutil.h"

extern Routeman         *pRouteMan;
extern FontMgr          *pFontMgr;

extern      float gCog;
extern      float gSog;


CPL_CVSID("$Id: concanv.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $");




//------------------------------------------------------------------------------
//    ConsoleCanvas Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ConsoleCanvas, wxWindow)
      EVT_PAINT(ConsoleCanvas::OnPaint)
//  EVT_ACTIVATE(ChartCanvas::OnActivate)
      EVT_SIZE(ConsoleCanvas::OnSize)
      EVT_MOUSE_EVENTS(ConsoleCanvas::MouseEvent)
END_EVENT_TABLE()

// Define a constructor for my canvas
ConsoleCanvas::ConsoleCanvas(wxFrame *frame):
            wxControl(frame, wxID_ANY,   wxPoint(20,20), wxSize(5,5),
                      wxSUNKEN_BORDER | wxCLIP_CHILDREN   )


{
      SetBackgroundColour(wxColour(128,128,128));

      pThisLegBox = new wxStaticBox(this, -1, "This Leg", wxPoint(1,1),
            wxSize(170,200), 0, "staticBox");

      pSBoxRgn = new wxRegion(pThisLegBox->GetRect() );

      pThisLegFont = wxTheFontList->FindOrCreateFont(12, wxDEFAULT,wxNORMAL, wxBOLD, FALSE,
                                                                        wxString("Eurostile Extended"));

      pThisLegBox->SetFont(*pThisLegFont);

      pXTE = new AnnunText(this, -1,wxPoint(10,20), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pXTE->SetALabel("XTE");

      pBRG = new AnnunText(this, -1,wxPoint(10,75), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pBRG->SetALabel("BRG");

      pRNG = new AnnunText(this, -1,wxPoint(10,130), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pRNG->SetALabel("RNG");

      pTTG = new AnnunText(this, -1,wxPoint(10,185), wxSize(140,50), _T("Console Legend"), _T("Console Value"));
      pTTG->SetALabel("TTG");





//    Create CDI Display Window

      pCDI = new CDI(this, -1, wxPoint(0,200), wxSize(100, 200), wxSIMPLE_BORDER, "CDI");
      pCDI->SetBackgroundColour(wxColour(192,192,192));


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
      this->GetClientSize(&canvas_width, &canvas_height);

      pThisLegBox->SetSize(1,1,canvas_width-2,240);

      int CDIHeight = canvas_width /2;
      pCDI->SetSize(2, canvas_height - CDIHeight - 4, canvas_width-4, CDIHeight);


}



void ConsoleCanvas::OnPaint(wxPaintEvent& event)
{
      int x,y;
      this->GetClientSize(&x, &y);
      char buf[40];

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
                              srng.Printf("%5.2f/%5.2f", rng, nrng );
                        else
                              srng.Printf("%5.1f/%5.1f", rng, nrng );
                  }
                  else
                  {
                        if(rng < 10.0)
                              srng.Printf("%6.2f", rng );
                        else
                              srng.Printf("%6.1f", rng );
                  }


                  if(!m_bShowRouteTotal)
                        pRNG->SetAValue(srng.c_str());

//    Brg
                  sprintf(buf, "%6.0f", pRouteMan->GetCurrentBrgToActivePoint());
                  pBRG->SetAValue(buf);

//    XTE
                  sprintf(buf, "%6.2f", pRouteMan->GetCurrentXTEToActivePoint());
                  pXTE->SetAValue(buf);
                  if(pRouteMan->GetXTEDir() < 0)
                        pXTE->SetALabel("XTE         L");
                  else
                        pXTE->SetALabel("XTE         R");

//    TTG
                  float ttg_sec = (rng / gSog) * 3600.;
                  wxTimeSpan ttg_span(0, 0, long(ttg_sec), 0);
                  wxString ttg_s = ttg_span.Format();
                  if(!m_bShowRouteTotal)
                        pTTG->SetAValue(ttg_s.c_str());

      //    Remainder of route
                  float trng = rng;

                  Route *prt = pRouteMan->GetpActiveRoute();
                  wxRoutePointListNode *node = (prt->pRoutePointList)->GetFirst();
                  RoutePoint *prp;


                  while(node)
                  {
                        prp = node->GetData();
                        if(prp->nPoint > prt->m_nRouteActivePoint)
                              trng += prp->m_seg_len;

                        node=node->GetNext();
                  }

//                total rng
                  if(trng < 10.0)
                        sprintf(&buf[0], "%6.2f", trng );
                  else
                        sprintf(&buf[0], "%6.1f", trng );

                  if(m_bShowRouteTotal)
                        pRNG->SetAValue(buf);

//                total ttg
                  float tttg_sec = (trng / gSog) * 3600.;
                  wxTimeSpan tttg_span(0, 0, long(tttg_sec), 0);
                  wxString tttg_s = tttg_span.Format();
                  if(m_bShowRouteTotal)
                        pTTG->SetAValue(tttg_s.c_str());

//                total ETA to be shown on XTE panel
                  wxDateTime dtnow, eta;
                  dtnow.SetToCurrent();
                  eta = dtnow.Add(tttg_span);
                  wxString seta = eta.FormatTime();

                  if(m_bShowRouteTotal)
                  {
                        pXTE->SetAValue(seta.c_str());
                        pXTE->SetALabel("ETA          ");
                  }




                  pBRG->Refresh(true);
                  pXTE->Refresh(true);
                  pTTG->Refresh(true);
                  pRNG->Refresh(true);


//    The CDI Display
                  pCDI->Refresh(true);
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


#ifndef __WXGTK__
      if(!HasCapture())
            CaptureMouse();

      if(event.Leaving())
            if(HasCapture())
                  ReleaseMouse();
#endif

      if(event.IsButton())
            wxLogMessage("concanv::MouseEvent Button");
//    Check the regions

      if(event.LeftDown())
      {
            wxRect br = pSBoxRgn->GetBox();
            if(pSBoxRgn->Contains(x,y)  == wxInRegion)
            {
                  m_bShowRouteTotal = !m_bShowRouteTotal;
                  if(m_bShowRouteTotal)
                        pThisLegBox->SetLabel(wxString("Route"));
                  else
                        pThisLegBox->SetLabel(wxString("This Leg"));

                  pThisLegBox->Refresh(true);
            }
      }

      else
      {
            wxRegion rr(GetRect());
#ifdef __WXMSW__
            if(rr.Contains(x,y)  != wxInRegion)
            {
                  wxLogMessage("concanv::MouseEvent releasing mouse");
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



/*
#include <wx/fontdlg.h>
#include <wx/fontenum.h>
#include "wx/encinfo.h"
#include "wx/fontutil.h"

#include "/usr/X11R6/include/X11/Xlib.h"


// returns TRUE if there are any fonts matching this font spec
static bool MyTestFontSpec(const wxString& fontspec)
{
    // some X servers will fail to load this font because there are too many
    // matches so we must test explicitly for this
      if ( fontspec == _T("-*-*-*-*-*-*-*-*-*-*-*-*-*-*") )
      {
            return TRUE;
      }


      wxNativeFont test = wxLoadFont(fontspec);

      if ( test )
      {
            XFreeFont((Display *)wxGetDisplay(), (XFontStruct *)test);        //            wxFreeFont(test);

            return TRUE;
      }
      else
      {
            return FALSE;
      }
}




static bool MyBuildXFontSpec(int pixelSize, int pointSize,
                                    int family,
                                    int style,
                                    int weight,
                                    bool WXUNUSED(underlined),
                                    const wxString& facename,
                                    const wxString& xregistry,
                                    const wxString& xencoding,
                                    wxString* xFontName)
{
      wxString xfamily;
      switch (family)
      {
            case wxDECORATIVE: xfamily = wxT("lucida"); break;
            case wxROMAN:      xfamily = wxT("times");  break;
            case wxMODERN:     xfamily = wxT("courier"); break;
            case wxSWISS:      xfamily = wxT("helvetica"); break;
            case wxTELETYPE:   xfamily = wxT("lucidatypewriter"); break;
            case wxSCRIPT:     xfamily = wxT("utopia"); break;
            default:           xfamily = wxT("*");
      }
#if wxUSE_NANOX
    int xweight;
    switch (weight)
    {
          case wxBOLD:
          {
                xweight = MWLF_WEIGHT_BOLD;
                break;
          }
          case wxLIGHT:
          {
                xweight = MWLF_WEIGHT_LIGHT;
                break;
          }
          case wxNORMAL:
          {
                xweight = MWLF_WEIGHT_NORMAL;
                break;
          }

          default:
          {
                xweight = MWLF_WEIGHT_DEFAULT;
                break;
          }
    }
    GR_SCREEN_INFO screenInfo;
    GrGetScreenInfo(& screenInfo);

    int yPixelsPerCM = screenInfo.ydpcm;

    // A point is 1/72 of an inch.
    // An inch is 2.541 cm.
    // So pixelHeight = (pointSize / 72) (inches) * 2.541 (for cm) * yPixelsPerCM (for pixels)
    // In fact pointSize is 10 * the normal point size so
    // divide by 10.

    int pixelHeight = (int) ( (((float)pointSize) / 720.0) * 2.541 * (float) yPixelsPerCM) ;

    // An alternative: assume that the screen is 72 dpi.
    //int pixelHeight = (int) (((float)pointSize / 720.0) * 72.0) ;
    //int pixelHeight = (int) ((float)pointSize / 10.0) ;

    GR_LOGFONT logFont;
    logFont.lfHeight = pixelHeight;
    logFont.lfWidth = 0;
    logFont.lfEscapement = 0;
    logFont.lfOrientation = 0;
    logFont.lfWeight = xweight;
    logFont.lfItalic = (style == wxNORMAL ? 0 : 1) ;
    logFont.lfUnderline = 0;
    logFont.lfStrikeOut = 0;
    logFont.lfCharSet = MWLF_CHARSET_DEFAULT; // TODO: select appropriate one
    logFont.lfOutPrecision = MWLF_TYPE_DEFAULT;
    logFont.lfClipPrecision = 0; // Not used
    logFont.lfRoman = (family == wxROMAN ? 1 : 0) ;
    logFont.lfSerif = (family == wxSWISS ? 0 : 1) ;
    logFont.lfSansSerif = !logFont.lfSerif ;
    logFont.lfModern = (family == wxMODERN ? 1 : 0) ;
    logFont.lfProportional = (family == wxTELETYPE ? 0 : 1) ;
    logFont.lfOblique = 0;
    logFont.lfSmallCaps = 0;
    logFont.lfPitch = 0; // 0 = default
    strcpy(logFont.lfFaceName, facename.c_str());

    XFontStruct* fontInfo = (XFontStruct*) malloc(sizeof(XFontStruct));
    fontInfo->fid = GrCreateFont((GR_CHAR*) facename.c_str(), pixelHeight, & logFont);
    GrGetFontInfo(fontInfo->fid, & fontInfo->info);
    return (wxNativeFont) fontInfo;

#else
    wxString fontSpec;
    if (!facename.IsEmpty())
    {
          fontSpec.Printf(wxT("-*-%s-*-*-normal-*-*-*-*-*-*-*-*-*"),
                          facename.c_str());

          if ( MyTestFontSpec(fontSpec) )
          {
                xfamily = facename;
          }
          else
          {
                return false;
          }
    }

    wxString xstyle;
    switch (style)
    {
          case wxSLANT:
                fontSpec.Printf(wxT("-*-%s-*-o-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xstyle = wxT("o");
                      break;
                }
            // fall through - try wxITALIC now

          case wxITALIC:
                fontSpec.Printf(wxT("-*-%s-*-i-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xstyle = wxT("i");
                }
                else if ( style == wxITALIC ) // and not wxSLANT
                {
                // try wxSLANT
                      fontSpec.Printf(wxT("-*-%s-*-o-*-*-*-*-*-*-*-*-*-*"),
                                      xfamily.c_str());
                      if ( MyTestFontSpec(fontSpec) )
                      {
                            xstyle = wxT("o");
                      }
                      else
                      {
                    // no italic, no slant - leave default
                            xstyle = wxT("*");
                      }
                }
                break;

          default:
                wxFAIL_MSG(_T("unknown font style"));
            // fall back to normal

          case wxNORMAL:
                xstyle = wxT("r");
                break;
    }

    wxString xweight;
    switch (weight)
    {
          case wxBOLD:
          {
                fontSpec.Printf(wxT("-*-%s-bold-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("bold");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-heavy-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("heavy");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-extrabold-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("extrabold");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-demibold-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("demibold");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-black-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("black");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-ultrablack-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("ultrablack");
                      break;
                }
          }
          break;
          case wxLIGHT:
          {
                fontSpec.Printf(wxT("-*-%s-light-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("light");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-thin-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("thin");
                      break;
                }
          }
          break;
          case wxNORMAL:
          {
                fontSpec.Printf(wxT("-*-%s-medium-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("medium");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-normal-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("normal");
                      break;
                }
                fontSpec.Printf(wxT("-*-%s-regular-*-*-*-*-*-*-*-*-*-*-*"),
                                xfamily.c_str());
                if ( MyTestFontSpec(fontSpec) )
                {
                      xweight = wxT("regular");
                      break;
                }
                xweight = wxT("*");
          }
          break;
          default:           xweight = wxT("*"); break;
    }

    // if pointSize is -1, don't specify any
    wxString sizeSpec;
    if ( pointSize == -1 )
    {
          sizeSpec = _T('*');
    }
    else
    {
          sizeSpec.Printf(_T("%d"), pointSize);
    }

   // if pixelSize is -1, don't specify any
    wxString pixsizeSpec;
    if ( pixelSize == -1 )
    {
          pixsizeSpec = _T('*');
    }
    else
    {
          pixsizeSpec.Printf(_T("%d"), pixelSize);
    }

    // construct the X font spec from our data
    fontSpec.Printf(wxT("-*-%s-%s-%s-normal-*-%s-%s-*-*-*-*-%s-%s"),
                    xfamily.c_str(), xweight.c_str(), xstyle.c_str(), pixsizeSpec.c_str(),
                    sizeSpec.c_str(), xregistry.c_str(), xencoding.c_str());

    if( xFontName )
          *xFontName = fontSpec;

    if ( MyTestFontSpec(fontSpec) )
          return true;
    else
          return false;
#endif
    // wxUSE_NANOX
}
*/
//------------------------------------------------------------------------------
//    AnnunText Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(AnnunText, wxWindow)
      EVT_PAINT(AnnunText::OnPaint)
END_EVENT_TABLE()


AnnunText::AnnunText(wxWindow *parent, wxWindowID id,
                               const wxPoint& pos, const wxSize& size, const char *LegendElement, const char *ValueElement):
            wxWindow(parent, id, pos, size, wxSUNKEN_BORDER, wxString(""))
{
      SetBackgroundColour(wxColour(0,0,0));

      label = new wxString("Label");
      value = new wxString("-----");

      plabelFont = wxTheFontList->FindOrCreateFont(14, wxFONTFAMILY_SWISS,wxNORMAL, wxBOLD, FALSE,
                                                                        wxString("Arial Bold"));
      pvalueFont = wxTheFontList->FindOrCreateFont(24, wxFONTFAMILY_DEFAULT,wxNORMAL, wxBOLD, FALSE,
                  wxString("helvetica"), wxFONTENCODING_ISO8859_1);


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
            wxLogMessage("Found Font, itwips = %d", itwips);
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
      pattern.Printf(wxT("-*-%s-*-r-normal-*-*-*-*-*-*-*-%s-%s"),
                        "utopia",
                     info.xregistry.c_str(),
                     info.xencoding.c_str());

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
            printf("%s\n", name.c_str());
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
      wxPaintDC dc(this);

      dc.SetTextForeground(wxColour(0,255,0));

      if(plabelFont)
      {
          wxString nfi = plabelFont->GetNativeFontInfoDesc();
            dc.SetFont(*plabelFont);
            dc.DrawText(*label, 5, 2);
      }

      if(pvalueFont)
      {
            dc.SetFont(*pvalueFont);

            int w, h;
            dc.GetTextExtent(*value, &w, &h);
            int cw, ch;
            dc.GetSize(&cw, &ch);

            dc.DrawText(*value, cw - w - 2, ch - h - 2);
      }




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



void CDI::OnPaint(wxPaintEvent& event)
{
      int x,y;
      GetClientSize(&x, &y);

      wxPaintDC dc(this);
      dc.Clear();

      int xp = x/2;
      int yp = y*9/10;


      int path_length = y * 3;
      int pix_per_xte = 120;

      if(pRouteMan->GetpActiveRoute())
      {
            float angle = 90 - (pRouteMan->GetCurrentSegmentCourse() - gCog);

            float PI = 3.14159;

            float dy = path_length * sin(angle *PI/180.);
            float dx = path_length * cos(angle *PI/180.);

            int xtedir;
            xtedir = pRouteMan->GetXTEDir();
            float xte = pRouteMan->GetCurrentXTEToActivePoint();

            float ddy = xtedir * pix_per_xte * xte * sin((90 - angle) *PI/180.);
            float ddx = xtedir * pix_per_xte * xte * cos((90 - angle) *PI/180.);

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

            dc.DrawPolygon(4, road,0,0,wxODDEVEN_RULE);

            dc.DrawLine(xc1, yc1, xc2, yc2);

            dc.DrawLine(0, yp, x, yp);
            dc.DrawCircle(xp,yp,6);
            dc.DrawLine(xp, yp+5, xp, yp-5);

      }

}




/******************************************************************************
 * $Id: about.cpp,v 1.45 2009/12/26 21:12:05 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  About Dialog
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
 * $Log: about.cpp,v $
 * Revision 1.45  2009/12/26 21:12:05  bdbcat
 * 1.3.6 RC1226
 *
 * Revision 1.44  2009/12/22 22:29:38  bdbcat
 * Beta 1220
 *
 * Revision 1.43  2009/12/17 02:45:58  bdbcat
 * Beta 1216
 *
 * Revision 1.42  2009/12/13 03:09:26  bdbcat
 * Beta 1210a
 *
 * Revision 1.41  2009/12/10 21:31:47  bdbcat
 * Beta 1210
 *
 * Revision 1.40  2009/11/23 04:09:21  bdbcat
 * 1122
 *
 * Revision 1.39  2009/11/19 01:56:12  bdbcat
 * Build 1118
 *
 * Revision 1.38  2009/11/18 01:22:16  bdbcat
 * 1.3.5
 *
 * Revision 1.37  2009/09/30 23:14:18  bdbcat
 * Version 1.3.4
 *
 * Revision 1.36  2009/09/30 02:33:13  bdbcat
 * 929
 *
 * Revision 1.35  2009/09/25 15:18:34  bdbcat
 * 925
 *
 * Revision 1.34  2009/09/18 03:51:28  bdbcat
 * 917
 *
 * Revision 1.33  2009/09/11 23:16:38  bdbcat
 * 911
 *
 * Revision 1.32  2009/09/04 01:50:21  bdbcat
 * 903
 *
 * Revision 1.31  2009/09/01 22:17:41  bdbcat
 * Build 901
 *
 * Revision 1.30  2009/08/31 02:48:32  bdbcat
 * Build 830
 *
 * Revision 1.29  2009/08/25 21:25:40  bdbcat
 * 825
 *
 * Revision 1.27  2009/08/22 01:15:58  bdbcat
 * Build 821
 *
 * Revision 1.26  2009/07/29 01:08:07  bdbcat
 * Build 728.
 *
 * Revision 1.25  2009/07/17 03:55:31  bdbcat
 * Build 716.
 *
 * Revision 1.24  2009/07/16 02:36:56  bdbcat
 * 1.3.3
 *
 * Revision 1.23  2009/07/11 00:59:04  bdbcat
 * 1.3.2
 *
 * Revision 1.22  2009/07/08 01:45:45  bdbcat
 * Update Authors.
 *
 * Revision 1.21  2009/06/28 02:03:06  bdbcat
 * Implement "Tips" tab.
 *
 * Revision 1.20  2009/06/17 02:41:43  bdbcat
 * Add Philip
 *
 * Revision 1.19  2009/06/03 03:48:38  bdbcat
 * 2009
 *
 * Revision 1.18  2009/06/03 03:08:22  bdbcat
 * 1.3.1
 *
 * Revision 1.17  2009/05/05 03:54:48  bdbcat
 * Version 1.3.0
 *
 * Revision 1.16  2009/03/26 22:28:44  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.15  2008/12/09 03:51:52  bdbcat
 * Cleanup Comments
 *
 * Revision 1.14  2008/11/12 04:11:28  bdbcat
 * Cleanup
 *
 * Revision 1.13  2008/10/23 23:40:03  bdbcat
 * Add dherring as coauthor
 *
 * Revision 1.12  2008/08/29 02:26:13  bdbcat
 * Version update
 *
 * Revision 1.11  2008/08/09 23:58:40  bdbcat
 * Numerous revampings....
 *
 * Revision 1.10  2008/04/10 01:24:05  bdbcat
 * Update Version to 1.2.4
 *
 * Revision 1.9  2008/03/30 21:34:03  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.8  2008/01/12 06:23:02  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.7  2008/01/10 03:35:19  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.5  2007/06/10 02:21:53  bdbcat
 * Bump to 1.2.1
 *
 * Revision 1.4  2007/05/03 13:23:54  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.3  2006/12/03 21:40:51  dsr
 * Cleanup
 *
 *
 *
 */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
      #include <wx/wx.h>
#endif

#include "wx/textfile.h"
#include <wx/html/htmlwin.h>


#include "about.h"
#include "chart1.h"

CPL_CVSID("$Id: about.cpp,v 1.45 2009/12/26 21:12:05 bdbcat Exp $");


//    Some constants

char OpenCPNVersion[] = {"\n\n           Version 1.3.6 RC1226"};


char AboutText[] =
{
  "\n\n\n\n                       OpenCPN\n\n\
      (c) 2000-2009 The OpenCPN Authors\n"
};

char AuthorText[] =
{
"   David S Register\n\
      bdbcat@yahoo.com\n\
      OpenCPN Lead Developer\n\n\
    Mark A Sikes\n\
      markasikes@gmail.com\n\
      OpenCPN CoDeveloper\n\n\
    Thomas Haller\n\
      thomasmartin.haller@web.de\n\
      GPX Import/Export Implementation\n\n\
    Will Kamp\n\
      will@matrixmariner.com\n\
      Toolbar Icon design\n\n\
    Richard Smith\n\
      smithstrawler@hotmail.com\n\
      OpenCPN CoDeveloper, MacOSX\n\n\
    David Herring\n\
      dherring@dherring.com\n\
      OpenCPN CoDeveloper, MacOSX\n\n\
    Philip Lange\n\
      philip.lange@albemarleweb.com\n\
      OpenCPN Documentation\n\n\
    Ron Kuris\n\
      swcafe@gmail.com\n\
      wxWidgets Support\n\n\
    Julian Smart, Robert Roebling et al\n\
      wxwidgets.org\n\
      wxWidgets Authors\n\n\
    Sylvain Duclos\n\
      sylvain_duclos@yahoo.com\n\
      S52 Presentation Library code\n\n\
    Manish P. Pagey\n\
      pagey@san.rr.com\n\
      Serial Port Library\n\n\
    David Flater\n\
      software@flaterco.com\n\
      XTIDE tide and current code\n\n\
    Frank Warmerdam\n\
      warmerdam@pobox.com\n\
      GDAL Class Library\n\n\
    Mike Higgins\n\
      higgins@monitor.net\n\
      BSB Chart Format Detail\n\n\
    Samuel R. Blackburn\n\
      sammy@sed.csc.com\n\
      NMEA0183 Class Library\n\n\
    Atul Narkhede\n\
      narkhede@cs.unc.edu\n\
      Polygon Graphics utilities\n\n\
    Jan C. Depner\n\
      depnerj@navo.navy.mil\n\
      WVS Chart Library\n\n\
    Stuart Cunningham, et al\n\
      stuart_hc@users.sourceforge.net\n\
      BSB Chart Georeferencing Algorithms\n\n\
    John F. Waers\n\
      jfwaers@csn.net\n\
      UTM Conversion Algorithms\n\n\
    Carsten Tschach\n\
      tschach@zedat.fu-berlin.de\n\
      UTM Conversion Algorithms\n\n\
    Ed Williams\n\
      http://williams.best.vwh.net/avform.htm\n\
      Great Circle Formulary\n\n\
    Philippe Bekaert\n\
                   \n\
      CIE->RGB Color Conversion Matrix\n\n\
    Robert Lipe\n\
      robertlipe@usa.net\n\
      Garmin USB GPS Interface\n"

};



/*
    For Developer Reference, the included source code
    elements are licensed as follows:

      wxWidgets                         LGPL
      s52cnsy&s52plib                   GPL
      seriallib                         GPL
      tcmgr                             GPL
      mygdal                            BSD, compatible with GPL
      nmea0183                          Owner License, compatible with GPL
      triangles                         Public Domain see tri.c, compatible with GPL
      wvschart                          Public Domain see wvschart.cpp, compatible with GPL

*/


IMPLEMENT_DYNAMIC_CLASS( about, wxDialog )


BEGIN_EVENT_TABLE( about, wxDialog )
    EVT_BUTTON( xID_OK, about::OnXidOkClick )
    EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK_HELP, about::OnPageChange)

END_EVENT_TABLE()


about::about( )
{
}

about::about( wxWindow* parent,wxString *pData_Locn, wxWindowID id, const wxString& caption,
                  const wxPoint& pos, const wxSize& size, long style)
{
  m_pDataLocn = pData_Locn;
  Create(parent, id, caption, pos, size, style);
  m_parent = parent;
}


bool about::Create( wxWindow* parent, wxWindowID id, const wxString& caption,
                     const wxPoint& pos, const wxSize& size, long style)
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    m_parent = parent;

    m_btips_loaded = false;

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();

    return TRUE;
}

void about::CreateControls()
{

  about* itemDialog1 = this;

  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
  itemDialog1->SetSizer(itemBoxSizer2);


  wxStaticText *pST1 = new wxStaticText(this, -1, _T("Label"), wxDefaultPosition, wxSize(400, 100));
  pST1->SetLabel(_("OpenCPN...A Nice Little Open Source Chart Plotter/Navigator"));
  itemBoxSizer2->Add(pST1);


  wxNotebook* itemNotebook4 = new wxNotebook( itemDialog1, ID_NOTEBOOK_HELP, wxDefaultPosition, wxSize(-1, -1), wxNB_TOP );
  itemBoxSizer2->Add(itemNotebook4, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, 5);

  //    About Panel
  wxPanel* itemPanelAbout = new wxPanel( itemNotebook4, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelAbout, _("About"));

  wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
  itemPanelAbout->SetSizer(itemBoxSizer6);

  wxTextCtrl *pAboutTextCtl = new wxTextCtrl( itemPanelAbout, -1, _T(""), wxDefaultPosition, wxSize(-1, 400),
                                              wxTE_MULTILINE | wxTE_READONLY );
  itemBoxSizer6->Add(pAboutTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, 5);


  wxString *pAboutString = new wxString(AboutText,  wxConvUTF8);

  pAboutString->Append(wxString(OpenCPNVersion,  wxConvUTF8));

  pAboutTextCtl->WriteText(*pAboutString);
  delete pAboutString;

  //     Authors Panel
  wxPanel* itemPanelAuthors = new wxPanel( itemNotebook4, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelAuthors, _("Authors"));

  wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
  itemPanelAuthors->SetSizer(itemBoxSizer7);

  wxTextCtrl *pAuthorTextCtl = new wxTextCtrl( itemPanelAuthors, -1, _T(""), wxDefaultPosition, wxSize(-1, 400),
                                               wxTE_MULTILINE | wxTE_READONLY );
  itemBoxSizer7->Add(pAuthorTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, 5);

  wxString *pAuthorsString = new wxString(AuthorText,  wxConvUTF8);
  pAuthorTextCtl->WriteText(*pAuthorsString);
  delete pAuthorsString;


  //  License Panel
  wxPanel* itemPanelLicense = new wxPanel( itemNotebook4, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelLicense, _("License"));

  wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
  itemPanelLicense->SetSizer(itemBoxSizer8);


  int tcflags = wxTE_MULTILINE | wxTE_READONLY;

  //    wxX11 TextCtrl is broken in many ways.
  //    Here, the wxTE_DONTWRAP flag creates a horizontal scroll bar
  //    which fails in wxX11 2.8.2....
#ifndef __WXX11__
  tcflags |= wxTE_DONTWRAP;
#endif
  wxTextCtrl *pLicenseTextCtl = new wxTextCtrl( itemPanelLicense, -1, _T(""), wxDefaultPosition, wxSize(-1, 400), tcflags);

  itemBoxSizer8->Add(pLicenseTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, 5);

  wxString license_loc(*m_pDataLocn);
  license_loc.Append(_T("license.txt"));

  wxTextFile license_file(license_loc);

  if(license_file.Open())
  {
      wxString str;
      str = license_file.GetFirstLine();
      pLicenseTextCtl->WriteText(str);

      while (!license_file.Eof())
      {
            str = license_file.GetNextLine();
            str.Append(_T("\n"));
            pLicenseTextCtl->AppendText(str);
      }
      license_file.Close();
  }
  else
  {
      wxString msg(_T("Could not open License file: "));
      msg.Append(license_loc);
      wxLogMessage(msg);
  }
  pLicenseTextCtl->SetInsertionPoint(0);

    //     Tips Panel
  wxPanel* itemPanelTips = new wxPanel( itemNotebook4, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelTips, _("Help"));

  wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxVERTICAL);
  itemPanelTips->SetSizer(itemBoxSizer9);


//  m_ptips_window = new  wxHtmlWindow(itemPanelTips, -1, wxDefaultPosition, wxSize(100,400), wxHW_DEFAULT_STYLE, _T("OpenCPN Help"));
//  itemBoxSizer9->Add(m_ptips_window, 0, wxGROW);


  //    Close Button

  wxBoxSizer* itemBoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer2->Add(itemBoxSizer28, 0, wxALIGN_RIGHT|wxALL, 5);

  wxButton* itemButton29 = new wxButton( itemDialog1, xID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
  itemButton29->SetDefault();
  itemBoxSizer28->Add(itemButton29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
}


void about::OnXidOkClick( wxCommandEvent& event )
{
  Close();
}

void about::OnPageChange(wxNotebookEvent& event)
{
      int i = event.GetSelection();

      if(3 == i)                        // 3 is the index of "Tips" page
      {
            wxString tips_locn = _T("tips.html");
            tips_locn.Prepend(*m_pDataLocn);
            wxLaunchDefaultBrowser(tips_locn);
/*
            if(NULL != m_ptips_window)
            {
                  if(!m_btips_loaded)
                  {
                        wxString tips_locn = _T("tips.html");
                        tips_locn.Prepend(*m_pDataLocn);
                        m_ptips_window->LoadPage(tips_locn);
                        m_btips_loaded = true;
                  }
            }
*/
      }
}



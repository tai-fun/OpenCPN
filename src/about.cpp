/******************************************************************************
 * $Id: about.cpp,v 1.10 2008/04/10 01:24:05 bdbcat Exp $
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
<<<<<<< about.cpp
 * $Log: about.cpp,v $
 * Revision 1.10  2008/04/10 01:24:05  bdbcat
 * Update Version to 1.2.4
 *
 * Revision 1.9  2008/03/30 21:34:03  bdbcat
 * Update for Mac OSX/Unicode
 *
=======
 * $Log: about.cpp,v $
 * Revision 1.10  2008/04/10 01:24:05  bdbcat
 * Update Version to 1.2.4
 *
 * Revision 1.9  2008/03/30 21:34:03  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.8  2008/01/12 06:23:02  bdbcat
 * Update for Mac OSX/Unicode
 *
>>>>>>> 1.8
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


#include "about.h"
#include "chart1.h"

CPL_CVSID("$Id: about.cpp,v 1.10 2008/04/10 01:24:05 bdbcat Exp $");


//    Some constants

char OpenCPNVersion[] = {"\n\n                      Version 1.2.4"};


char AboutText[] =
{
  "\n\n\n\n                       OpenCPN\n\n\
      (c) 2000-2008 The OpenCPN Authors\n"
};

char AuthorText[] =
{
"   David S Register\n\
      bdbcat@yahoo.com\n\
      OpenCPN Lead Developer\n\n\
   Richard Smith\n\
      smithstrawler@hotmail.com\n\
      OpenCPN CoDeveloper, MacOSX\n\n\
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
      Great Circle Formulary"
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

      sercomm ??? Possible rewrite\
*/




IMPLEMENT_DYNAMIC_CLASS( about, wxDialog )


BEGIN_EVENT_TABLE( about, wxDialog )
    EVT_BUTTON( xID_OK, about::OnXidOkClick )
END_EVENT_TABLE()


about::about( )
{
}

about::about( wxWindow* parent,wxString *pLicense_Data_Locn, wxWindowID id, const wxString& caption,
                  const wxPoint& pos, const wxSize& size, long style)
{
  pLicenseLocn = pLicense_Data_Locn;
  Create(parent, id, caption, pos, size, style);
}


bool about::Create( wxWindow* parent, wxWindowID id, const wxString& caption,
                     const wxPoint& pos, const wxSize& size, long style)
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

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
  pST1->SetLabel(_T("OpenCPN...A Nice Little Open Source Chart Plotter/Navigator"));
  itemBoxSizer2->Add(pST1);


  wxNotebook* itemNotebook4 = new wxNotebook( itemDialog1, -1 , wxDefaultPosition, wxSize(-1, -1), wxNB_TOP );
  itemBoxSizer2->Add(itemNotebook4, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxALL, 5);

  //    About Panel
  wxPanel* itemPanelAbout = new wxPanel( itemNotebook4, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelAbout, _T("About"));

  wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
  itemPanelAbout->SetSizer(itemBoxSizer6);

  wxTextCtrl *pAboutTextCtl = new wxTextCtrl( itemPanelAbout, -1, _T(""), wxDefaultPosition, wxSize(-1, 400),
                                              wxTE_MULTILINE | wxTE_READONLY );
  itemBoxSizer6->Add(pAboutTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxALL, 5);


  wxString *pAboutString = new wxString(AboutText,  wxConvUTF8);

  pAboutString->Append(wxString(OpenCPNVersion,  wxConvUTF8));

  pAboutTextCtl->WriteText(*pAboutString);
  delete pAboutString;

  //     Authors Panel
  wxPanel* itemPanelAuthors = new wxPanel( itemNotebook4, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelAuthors, _T("Authors"));

  wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
  itemPanelAuthors->SetSizer(itemBoxSizer7);

  wxTextCtrl *pAuthorTextCtl = new wxTextCtrl( itemPanelAuthors, -1, _T(""), wxDefaultPosition, wxSize(-1, 400),
                                               wxTE_MULTILINE | wxTE_READONLY );
  itemBoxSizer7->Add(pAuthorTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxALL, 5);

  wxString *pAuthorsString = new wxString(AuthorText,  wxConvUTF8);
  pAuthorTextCtl->WriteText(*pAuthorsString);
  delete pAuthorsString;


  //  License Panel
  wxPanel* itemPanelLicense = new wxPanel( itemNotebook4, -1, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelLicense, _T("License"));

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

  itemBoxSizer8->Add(pLicenseTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxGROW|wxALL, 5);

  wxString license_loc(*pLicenseLocn);
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

  //    Close Button

  wxBoxSizer* itemBoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer2->Add(itemBoxSizer28, 0, wxALIGN_RIGHT|wxALL, 5);

  wxButton* itemButton29 = new wxButton( itemDialog1, xID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
  itemButton29->SetDefault();
  itemBoxSizer28->Add(itemButton29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
}


void about::OnXidOkClick( wxCommandEvent& event )
{
  EndModal(1);
}



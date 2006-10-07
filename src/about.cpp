/******************************************************************************
 * $Id: about.cpp,v 1.2 2006/10/07 03:50:27 dsr Exp $
 *
 * Project:  OpenCP
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
 * Revision 1.2  2006/10/07 03:50:27  dsr
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.3  2006/04/23 03:57:10  dsr
 * Fix internal names
 *
 * Revision 1.2  2006/04/19 04:08:26  dsr
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.5  2006/04/19 00:33:30  dsr
 * Add Name field to help screen, giving tag version from CVS
 *
 * Revision 1.4  2006/03/16 03:18:13  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/03/16 03:15:25  dsr
 * Cleanup tabs
 *
 * Revision 1.2  2006/03/13 05:02:40  dsr
 * Cleanup
 *
 * Revision 1.1  2006/02/23 01:57:28  dsr
 * Initial
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

CPL_CVSID("$Id: about.cpp,v 1.2 2006/10/07 03:50:27 dsr Exp $");


//    Some constants

char OpenCPNVersion[] = {"\n\n                      Version 1.0"};


char AboutText[] =
{
  "\n\n\n\n                     OpenCPN\n\n\
      (c) 2000-2006 The OpenCPN Authors\n"
};

char AuthorText[] =
{
"   David S Register\n\
      bdbcat@yahoo.com\n\
      OpenCPN Author\n\n\
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
   Remco Treffkorn, et al\n\
      Georeferencing Utilities\n\n"




};

//Todo Fix this, especially add QPL license to license tab, and make a point of GPC license
char LicenseText[] =
{
  "OpenCPN Convert to GPL\
      wxWidgets LGPL\
      s52cnsy&plib GPL\
      seriallib GPL\
      tcmgr GPL\
      mygdal BSD OK for GPL\
      nmea0183 OK for GPL\
      triangles Public Domain see tri.c OK for GPL\
      wvschart Public Domain see wvschart.cpp OK for GPL\
      \n\n\n\n\n\n\n\
      sercomm ??? Possible rewrite\
      georef QPL(see License.qpl) NEED TO INCLUDE AND REFERENCE LICENSE.QPL"

};



#define ID_CHOICE_NMEA  wxID_HIGHEST + 1



IMPLEMENT_DYNAMIC_CLASS( about, wxDialog )


BEGIN_EVENT_TABLE( about, wxDialog )


////@begin options event table entries
    EVT_BUTTON( xID_OK, about::OnXidOkClick )

////@end options event table entries



END_EVENT_TABLE()

/*!
 * about constructors
 */

about::about( )
{
}

about::about( wxWindow* parent,wxString *pLicense_Data_Locn, wxWindowID id, const wxString& caption,
                  const wxPoint& pos, const wxSize& size, long style)
{

  pParent = (MyFrame *)parent;

  pLicenseLocn = pLicense_Data_Locn;
  Create(parent, id, caption, pos, size, style);
}

/*!
 * options creator
 */

bool about::Create( wxWindow* parent, wxWindowID id, const wxString& caption,
                     const wxPoint& pos, const wxSize& size, long style)
{
////@begin options member initialisation
////@end options member initialisation



////@begin options creation
  SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
  wxDialog::Create( parent, id, caption, pos, size, style );

  CreateControls();
  GetSizer()->Fit(this);
  GetSizer()->SetSizeHints(this);
  Centre();
////@end options creation


  return TRUE;
}

/*!
 * Control creation for options
 */

void about::CreateControls()
{

  about* itemDialog1 = this;

  wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
  itemDialog1->SetSizer(itemBoxSizer2);

  wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
  itemFlexGridSizer3->AddGrowableRow(0);
  itemBoxSizer2->Add(itemFlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);


  wxStaticText *pST1 = new wxStaticText(this, -1, "Label", wxDefaultPosition, wxSize(400, 100));
  pST1->SetLabel("OpenCPN...A Nice Little Open Source Chart Plotter/Navigator");
  itemFlexGridSizer3->Add(pST1);



  wxNotebook* itemNotebook4 = new wxNotebook( itemDialog1, ID_NOTEBOOK, wxDefaultPosition, wxSize(400, 300), wxNB_TOP );
  itemFlexGridSizer3->Add(itemNotebook4);


  wxPanel* itemPanelAbout = new wxPanel( itemNotebook4, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelAbout, "About");

  wxTextCtrl *pAboutTextCtl = new wxTextCtrl( itemPanelAbout, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(350, 200),
                                              wxTE_MULTILINE );
  wxString *pAboutString = new wxString(AboutText);

  pAboutString->Append(OpenCPNVersion);

  pAboutTextCtl->WriteText(*pAboutString);
  delete pAboutString;

  wxPanel* itemPanel5 = new wxPanel( itemNotebook4, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanel5, _("Authors"));

  wxTextCtrl *pAuthorTextCtl = new wxTextCtrl( itemPanel5, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(350, 200), wxTE_MULTILINE );
  wxString *pAuthorsString = new wxString(AuthorText);
  pAuthorTextCtl->WriteText(*pAuthorsString);
  delete pAuthorsString;

  //  License tab
  wxPanel* itemPanelLicense = new wxPanel( itemNotebook4, ID_PANEL2, wxDefaultPosition, wxDefaultSize,
                                           wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
  itemNotebook4->AddPage(itemPanelLicense, _("License"));

  wxTextCtrl *pLicenseTextCtl = new wxTextCtrl( itemPanelLicense, ID_TEXTCTRL, _T(""),
      wxDefaultPosition, wxSize(350, 200), wxTE_MULTILINE | wxTE_DONTWRAP);


  wxString license_loc(*pLicenseLocn);
  license_loc.Append("license.txt");

  wxTextFile license_file(license_loc);

  if(license_file.Open())
  {
      wxString str;
      str = license_file.GetFirstLine();
      pLicenseTextCtl->WriteText(str);

      while (!license_file.Eof())
      {
            str = license_file.GetNextLine();
            str.Append("\n");
            pLicenseTextCtl->AppendText(str);
      }
      license_file.Close();


  }
  else
    wxLogMessage("Could not open License file %s", license_loc.c_str());




  wxBoxSizer* itemBoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
  itemBoxSizer2->Add(itemBoxSizer28, 0, wxALIGN_RIGHT|wxALL, 5);

  wxButton* itemButton29 = new wxButton( itemDialog1, xID_OK, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
  itemButton29->SetDefault();
  itemBoxSizer28->Add(itemButton29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


////@end options content construction



}



void about::SetInitialSettings()
{

}



/*!
 * Should we show tooltips?
 */

bool about::ShowToolTips()
{
  return TRUE;
}



/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for xID_OK
 */

void about::OnXidOkClick( wxCommandEvent& event )
{


  EndModal(1);

}



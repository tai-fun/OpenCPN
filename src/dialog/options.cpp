/******************************************************************************
 * $Id: options.cpp,v 1.5 2006/10/07 03:51:44 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  Options Dialog
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
 * $Log: options.cpp,v $
 * Revision 1.5  2006/10/07 03:51:44  dsr
 * *** empty log message ***
 *
 * Revision 1.4  2006/10/05 03:52:18  dsr
 * gpsd
 *
 * Revision 1.3  2006/10/01 03:24:19  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:37:48  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:20  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.6  2006/08/04 11:48:38  dsr
 * no message
 *
 * Revision 1.5  2006/07/28 20:49:09  dsr
 * New NMEA Logic
 *
 * Revision 1.4  2006/07/05 02:34:55  dsr
 * Save/Restore WiFi Server
 *
 * Revision 1.3  2006/05/19 19:32:29  dsr
 * Cleanup
 *
 * Revision 1.2  2006/04/23 04:02:09  dsr
 * Fix internal names
 *
 * Revision 1.1.1.1  2006/04/19 03:23:29  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.10  2006/04/19 01:00:46  dsr
 * Add Font Chooser panel
 *
 * Revision 1.9  2006/03/16 03:53:06  dsr
 * Cleanup
 *
 * Revision 1.8  2006/03/16 03:28:26  dsr
 * Cleanup tabs
 *
 * Revision 1.7  2006/03/13 04:54:11  dsr
 * Rebuild TCP/IP NMEA Source logic
 *
 * Revision 1.6  2006/02/23 01:55:09  dsr
 * Cleanup
 *
 * Revision 1.5  2006/02/10 03:19:40  dsr
 * *** empty log message ***
 *
 *
 */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/generic/progdlgg.h"


#include "dychart.h"

#include "options.h"

#include "navutil.h"
#ifdef USE_S57
#include "s52plib.h"
#endif

extern bool             g_bShowPrintIcon;
extern wxString         *pNMEADataSource;
extern wxString         *pNMEA_AP_Port;
extern FontMgr          *pFontMgr;

#ifdef USE_WIFI_CLIENT
extern wxString         *pWIFIServerName;
#endif

#ifdef USE_S57
extern s52plib          *ps52plib;
#endif

//    Some constants
#define ID_CHOICE_NMEA  wxID_HIGHEST + 1


/*!
 * options type definition
 */

IMPLEMENT_DYNAMIC_CLASS( options, wxDialog )

/*!
 * options event table definition
 */

BEGIN_EVENT_TABLE( options, wxDialog )


//    BUGBUG DSR Must use wxID_TREECTRL to capture tree events.

    EVT_TREE_SEL_CHANGED( wxID_TREECTRL, options::OnDirctrlSelChanged )
////@begin options event table entries
    EVT_CHECKBOX( ID_DEBUGCHECKBOX1, options::OnDebugcheckbox1Click )

    EVT_TREE_SEL_CHANGED( ID_DIRCTRL, options::OnDirctrlSelChanged )

    EVT_BUTTON( ID_BUTTONADD, options::OnButtonaddClick )

    EVT_BUTTON( ID_BUTTONDELETE, options::OnButtondeleteClick )

    EVT_BUTTON( ID_BUTTONREBUILD, options::OnButtonrebuildClick )

    EVT_RADIOBOX( ID_RADIOBOX, options::OnRadioboxSelected )

    EVT_BUTTON( xID_OK, options::OnXidOkClick )

    EVT_BUTTON( wxID_CANCEL, options::OnCancelClick )
    EVT_BUTTON( ID_BUTTONFONTCHOOSE, options::OnChooseFont )

////@end options event table entries
    EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, options::OnPageChange)  //Processes a wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event.

      EVT_CHOICE( ID_CHOICE_NMEA, options::OnNMEASourceChoice )
      EVT_COMBOBOX( ID_CHOICE_NMEA, options::OnNMEASourceChoice )

    EVT_RADIOBOX(ID_RADIOBOX, options::OnDisplayCategoryRadioButton )
    EVT_BUTTON( ID_CLEARLIST, options::OnButtonClearClick )
    EVT_BUTTON( ID_SELECTLIST, options::OnButtonSelectClick )

END_EVENT_TABLE()

/*!
 * options constructors
 */

options::options( )
{
}

options::options( wxWindow* parent, wxWindowID id, const wxString& caption, const wxString& Initial_Chart_Dir,
              const wxPoint& pos, const wxSize& size, long style)
{
      pDirCtl = NULL;
      m_pCurrentDirList = NULL;
      m_pWorkDirList = NULL;

      pParent = parent;

    Create(parent, id, caption, pos, size, style, Initial_Chart_Dir);
}

/*!
 * options creator
 */

bool options::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style,
                const wxString& Initial_Chart_Dir)
{
////@begin options member initialisation
    pDebugShowStat = NULL;
    pDirCtl = NULL;
    pSelCtl = NULL;
    pTextCtl = NULL;
    ps57Ctl = NULL;
    ps57CtlListBox = NULL;
    pDispCat = NULL;
////@end options member initialisation


//    m_pinit_chart_dir = new wxString(Initial_Chart_Dir);
    m_pinit_chart_dir = (wxString *)&Initial_Chart_Dir;

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

void options::CreateControls()
{
////@begin options content construction

    options* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxFlexGridSizer* itemFlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
    itemFlexGridSizer3->AddGrowableRow(0);
    itemBoxSizer2->Add(itemFlexGridSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxNotebook* itemNotebook4 = new wxNotebook( itemDialog1, ID_NOTEBOOK, wxDefaultPosition, wxSize(400, 500), wxNB_TOP );

    wxPanel* itemPanel5 = new wxPanel( itemNotebook4, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    itemPanel5->SetSizer(itemBoxSizer6);

    wxStaticBox* itemStaticBoxSizerDebugStatic = new wxStaticBox(itemPanel5, wxID_ANY, _("Debug"));
    wxStaticBoxSizer* itemStaticBoxSizerDebug = new wxStaticBoxSizer(itemStaticBoxSizerDebugStatic, wxVERTICAL);
    itemBoxSizer6->Add(itemStaticBoxSizerDebug, 0, wxGROW|wxALL, 5);
    pDebugShowStat = new wxCheckBox( itemPanel5, ID_DEBUGCHECKBOX1, _("Show Status and Debug Windows"), wxDefaultPosition,
                             wxSize(300, -1), 0 );
    pDebugShowStat->SetValue(FALSE);
    itemStaticBoxSizerDebug->Add(pDebugShowStat, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticBox* itemStaticBoxSizerPrintStatic = new wxStaticBox(itemPanel5, wxID_ANY, _("Printing"));
    wxStaticBoxSizer* itemStaticBoxSizerPrint = new wxStaticBoxSizer(itemStaticBoxSizerPrintStatic, wxVERTICAL);
    itemBoxSizer6->Add(itemStaticBoxSizerPrint, 0, wxGROW|wxALL, 5);
    pPrintShowIcon = new wxCheckBox( itemPanel5, ID_DEBUGCHECKBOX1, _("Show Printing Icon"), wxDefaultPosition,
                             wxSize(300, -1), 0 );
    pPrintShowIcon->SetValue(FALSE);
    itemStaticBoxSizerPrint->Add(pPrintShowIcon, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);




    itemNotebook4->AddPage(itemPanel5, _("Settings"));


//    Add NMEA Options Box
    wxStaticBox* itemNMEAStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("NMEA Options"));
    wxStaticBoxSizer* itemNMEAStaticBoxSizer = new wxStaticBoxSizer(itemNMEAStaticBox, wxVERTICAL);
    itemBoxSizer6->Add(itemNMEAStaticBoxSizer, 0, wxGROW|wxALL, 5);


//    Add NMEA data source controls
    wxStaticBox* itemNMEASourceStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("NMEA Data Source"));
    wxStaticBoxSizer* itemNMEASourceStaticBoxSizer = new wxStaticBoxSizer(itemNMEASourceStaticBox, wxVERTICAL);
    itemNMEAStaticBoxSizer->Add(itemNMEASourceStaticBoxSizer, 0, wxGROW|wxALL, 5);

      m_itemNMEAListBox = new wxComboBox(itemPanel5, ID_CHOICE_NMEA);
      m_itemNMEAListBox->Append( _T("None"));
      m_itemNMEAListBox->Append( _T("COM1"));
      m_itemNMEAListBox->Append( _T("COM2"));
      m_itemNMEAListBox->Append( _T("COM3"));
      m_itemNMEAListBox->Append( _T("COM4"));
      m_itemNMEAListBox->Append( _T("/dev/ttyS0"));
      m_itemNMEAListBox->Append( _T("/dev/ttyS1"));
      m_itemNMEAListBox->Append( _T("Network GPSD"));

//    Activate the proper selections
//    n.b. Hard coded indices
      int sidx;
      bool tcp_en = false;
      wxString source;
      source = (*pNMEADataSource);
      if(source.Upper().Contains("SERIAL"))
      {
          wxString sourcex = source.Mid(7);
          sidx = m_itemNMEAListBox->FindString(sourcex);
      }
      else if(source.Upper().Contains("NONE"))
            sidx = 0;
      else if(source.Upper().Contains("GPSD"))
      {
          sidx = m_itemNMEAListBox->FindString(_T("Network GPSD"));
          tcp_en = true;
      }
      else
          sidx = 0;                                 // malformed selection

      if(sidx ==  wxNOT_FOUND)                  // user specified in ComboBox
      {
          wxString nsource = source.AfterFirst(':');
          m_itemNMEAListBox->Append( nsource );
          sidx = m_itemNMEAListBox->FindString(nsource);
      }


      m_itemNMEAListBox->SetSelection(sidx);
      itemNMEASourceStaticBoxSizer->Add(m_itemNMEAListBox, 0, wxGROW|wxALL, 5);

//    Add NMEA TCP/IP Server address
    m_itemNMEA_TCPIP_StaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("GPSD Data Server"));
    m_itemNMEA_TCPIP_StaticBoxSizer = new wxStaticBoxSizer(m_itemNMEA_TCPIP_StaticBox, wxVERTICAL);
    itemNMEAStaticBoxSizer->Add(m_itemNMEA_TCPIP_StaticBoxSizer, 0, wxGROW|wxALL, 5);

      m_itemNMEA_TCPIP_Source = new wxTextCtrl(itemPanel5, wxID_ANY);
      m_itemNMEA_TCPIP_StaticBoxSizer->Add(m_itemNMEA_TCPIP_Source, 0, wxGROW|wxALL, 5);

      m_itemNMEA_TCPIP_StaticBox->Enable(tcp_en);
      m_itemNMEA_TCPIP_Source->Enable(tcp_en);

      if(tcp_en)
      {
            wxString ip;
            ip = source.Mid(5);
            m_itemNMEA_TCPIP_Source->WriteText(ip);
      }




//    Add Autopilot serial output port controls
      wxStaticBox* itemNMEAAutoStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("Autopilot Output Port"));
      wxStaticBoxSizer* itemNMEAAutoStaticBoxSizer = new wxStaticBoxSizer(itemNMEAAutoStaticBox, wxVERTICAL);
      itemNMEAStaticBoxSizer->Add(itemNMEAAutoStaticBoxSizer, 0, wxGROW|wxALL, 5);

      m_itemNMEAAutoListBox = new wxChoice(itemPanel5, ID_CHOICE_NMEA);
      m_itemNMEAAutoListBox->Append( _T("None"));

      int apidx;
      wxString apport;
      apport = *pNMEA_AP_Port;
      wxString comx_ap;

#ifdef __WXMSW__
      m_itemNMEAAutoListBox->Append( _T("COM1"));
      m_itemNMEAAutoListBox->Append( _T("COM2"));
      m_itemNMEAAutoListBox->Append( _T("COM3"));
      m_itemNMEAAutoListBox->Append( _T("COM4"));

      apidx = 0;
      int ic = apport.Find("COM");
      if(-1 != ic)
      {
            comx_ap = apport.Mid(ic + 3, 1);
            apidx = comx_ap[0] - '0';
      }
#else
      m_itemNMEAAutoListBox->Append( _T("/dev/ttyS0"));
      m_itemNMEAAutoListBox->Append( _T("/dev/ttyS1"));

      apidx = 0;
      int ic = apport.Find("/dev/ttyS");
      if(-1 != ic)
      {
            char ccomx_ap = apport.GetChar(ic+9);
            apidx = ccomx_ap - '0' + 1;
      }


#endif



      m_itemNMEAAutoListBox->SetSelection(apidx);

      itemNMEAAutoStaticBoxSizer->Add(m_itemNMEAAutoListBox, 0, wxGROW|wxALL, 5);

#ifdef USE_WIFI_CLIENT
//    Add WiFi Options Box
      wxStaticBox* itemWIFIStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("WiFi Options"));
      wxStaticBoxSizer* itemWIFIStaticBoxSizer = new wxStaticBoxSizer(itemWIFIStaticBox, wxVERTICAL);
      itemBoxSizer6->Add(itemWIFIStaticBoxSizer, 0, wxGROW|wxALL, 5);

//    Add WiFi TCP/IP Server address
      m_itemWIFI_TCPIP_StaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("TCP/IP WiFi Data Server"));
      m_itemWIFI_TCPIP_StaticBoxSizer = new wxStaticBoxSizer(m_itemWIFI_TCPIP_StaticBox, wxVERTICAL);
      itemWIFIStaticBoxSizer->Add(m_itemWIFI_TCPIP_StaticBoxSizer, 0, wxGROW|wxALL, 5);

      m_itemWIFI_TCPIP_Source = new wxTextCtrl(itemPanel5, wxID_ANY);
      m_itemWIFI_TCPIP_StaticBoxSizer->Add(m_itemWIFI_TCPIP_Source, 0, wxGROW|wxALL, 5);

      m_itemWIFI_TCPIP_StaticBox->Enable(1);
      m_itemWIFI_TCPIP_Source->Enable(1);

      wxString ip;
      ip = pWIFIServerName->Mid(7);
      m_itemWIFI_TCPIP_Source->WriteText(ip);
#endif




//    Build "Charts" page

    itemPanel9 = new wxPanel( itemNotebook4, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemBoxSizer10 = new wxBoxSizer(wxVERTICAL);
    itemPanel9->SetSizer(itemBoxSizer10);

    //      Linux wxUNIVERSAL wxGenericDirCtrl is --very-- slow.
    //      Slowness is in ArtProvider, generating the proper icons
    //      So....
    //      Move the dir tree control out of the ctor, and only build it if "CHART" panel is selected.
    //      See this::OnPageChange event handler


    itemNotebook4->AddPage(itemPanel9, _("Charts"));


    //      Build S57 Options page

    ps57Ctl = new wxPanel( itemNotebook4, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer22 = new wxBoxSizer(wxHORIZONTAL);
    ps57Ctl->SetSizer(itemBoxSizer22);

    wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer22->Add(itemBoxSizer23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxString* ps57CtlListBoxStrings = NULL;
    ps57CtlListBox = new wxCheckListBox( ps57Ctl, ID_CHECKLISTBOX, wxDefaultPosition, wxSize(-1, 300), 0,
                                         ps57CtlListBoxStrings, wxLB_SINGLE );
    itemBoxSizer23->Add(ps57CtlListBox, 0, wxALIGN_LEFT|wxALL, 5);

    itemButtonClearList = new wxButton( ps57Ctl, ID_CLEARLIST, _("Clear All"),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemButtonClearList->SetDefault();
    itemBoxSizer23->Add(itemButtonClearList, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemButtonSelectList = new wxButton( ps57Ctl, ID_SELECTLIST, _("Select All"),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemButtonSelectList->SetDefault();
    itemBoxSizer23->Add(itemButtonSelectList, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer22->Add(itemBoxSizer25, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);
    wxStaticBox* itemStaticBoxSizer26Static = new wxStaticBox(ps57Ctl, wxID_ANY, _("Chart Display Options"));
    wxStaticBoxSizer* itemStaticBoxSizer26 = new wxStaticBoxSizer(itemStaticBoxSizer26Static, wxVERTICAL);
    itemBoxSizer25->Add(itemStaticBoxSizer26, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxString pDispCatStrings[] = {
        _("&Base"),
        _("&Standard"),
        _("&Other"),
        _("&MarinersStandard")
    };
    pDispCat = new wxRadioBox( ps57Ctl, ID_RADIOBOX, _("Display Category"), wxDefaultPosition, wxDefaultSize, 4, pDispCatStrings, 1, wxRA_SPECIFY_COLS );
    itemStaticBoxSizer26->Add(pDispCat, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemNotebook4->AddPage(ps57Ctl, _("S57 Object Filter"));


    //      Add Invariant buttons
    itemFlexGridSizer3->Add(itemNotebook4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer28, 0, wxALIGN_RIGHT|wxALL, 5);

    wxButton* itemButton29 = new wxButton( itemDialog1, xID_OK, _("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
    itemButton29->SetDefault();
    itemBoxSizer28->Add(itemButton29, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton30 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer28->Add(itemButton30, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


    //      Build Fonts panel
    wxPanel* itemPanelFont = new wxPanel( itemNotebook4, ID_PANELFONT, wxDefaultPosition, wxDefaultSize,
                                          wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizerFontPanel = new wxBoxSizer(wxVERTICAL);
    itemPanelFont->SetSizer(itemBoxSizerFontPanel);

    wxStaticBox* itemFontStaticBox = new wxStaticBox(itemPanelFont, wxID_ANY, _("Font Options"));
    wxStaticBoxSizer* itemFontStaticBoxSizer = new wxStaticBoxSizer(itemFontStaticBox, wxVERTICAL);
    itemBoxSizerFontPanel->Add(itemFontStaticBoxSizer, 0, wxGROW|wxALL, 5);

    wxStaticBox* itemFontElementStaticBox = new wxStaticBox(itemPanelFont, wxID_ANY, _("Text Element"));
    wxStaticBoxSizer* itemFontElementStaticBoxSizer = new wxStaticBoxSizer(itemFontElementStaticBox, wxVERTICAL);
    itemFontStaticBoxSizer->Add(itemFontElementStaticBoxSizer, 0, wxGROW|wxALL, 5);

    m_itemFontElementListBox = new wxChoice(itemPanelFont, ID_CHOICE_FONTELEMENT);

    int nFonts = pFontMgr->GetNumFonts();
    for( int it = 0 ; it < nFonts ; it++)
    {
          wxString *t = pFontMgr->GetDialogString(it);
          m_itemFontElementListBox->Append( *t );
    }

    if(nFonts)
          m_itemFontElementListBox->SetSelection(0);

    itemFontElementStaticBoxSizer->Add(m_itemFontElementListBox, 0, wxGROW|wxALL, 5);

    wxButton* itemFontChooseButton = new wxButton( itemPanelFont, ID_BUTTONFONTCHOOSE, _("Choose Font..."),
                wxDefaultPosition, wxDefaultSize, 0 );
    itemFontElementStaticBoxSizer->Add(itemFontChooseButton, 0, wxGROW|wxALL, 5);


    itemNotebook4->AddPage(itemPanelFont, _("Fonts"));

////@end options content construction


      pSettingsCB1 = pDebugShowStat;
}



void options::SetInitialSettings()
{
      wxString dirname;

      if(m_pCurrentDirList)
      {
            int nDir = m_pCurrentDirList->GetCount();

            for(int i=0 ; i<nDir ; i++)
            {
                  dirname = m_pCurrentDirList->Item(i);
                  if(!dirname.IsEmpty())
                  {
                      if (pTextCtl)
                      {
                          pTextCtl->AppendText(dirname);
                          pTextCtl->AppendText(_T("\n"));
                      }
                  }
            }
      }

//    Settings too

      pSettingsCB1->SetValue(m_pConfig->m_bShowDebugWindows);
      pPrintShowIcon->SetValue(g_bShowPrintIcon);


#ifdef USE_S57
//    S57 Object Filters
      ps57CtlListBox->Clear();

      for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
      {
            OBJLElement *pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));

            ps57CtlListBox->Append(wxString(pOLE->OBJLName));
            ps57CtlListBox->Check(ps57CtlListBox->GetCount()-1, pOLE->nViz);

    }

//    Diplay Category
      if(ps52plib)
      {
            int nset = 2;                             // default OTHER

            switch(ps52plib->m_nDisplayCategory)
            {
            case (DISPLAYBASE):
                  nset = 0;
                  break;
            case (STANDARD):
                  nset = 1;
                  break;
            case (OTHER):
                  nset = 2;
                  break;
            case (MARINERS_STANDARD):
                  nset = 3;
                  break;
            default:
                    nset = 3;
                    break;
            }

            pDispCat->SetSelection(nset);
      }

      ps57CtlListBox->Enable(MARINERS_STANDARD == ps52plib->m_nDisplayCategory);
      itemButtonClearList->Enable(MARINERS_STANDARD == ps52plib->m_nDisplayCategory);
      itemButtonSelectList->Enable(MARINERS_STANDARD == ps52plib->m_nDisplayCategory);

#endif

}


void options::OnDisplayCategoryRadioButton( wxCommandEvent& event)
{
   int select = pDispCat->GetSelection();

    if(3 == select)
    {
        ps57CtlListBox->Enable();
        itemButtonClearList->Enable();
        itemButtonSelectList->Enable();
    }

    else
    {
        ps57CtlListBox->Disable();
        itemButtonClearList->Disable();
        itemButtonSelectList->Disable();
    }

    event.Skip();

}

void options::OnButtonClearClick( wxCommandEvent& event )
{
    int nOBJL = ps57CtlListBox->GetCount();
    for( int iPtr = 0 ; iPtr < nOBJL ; iPtr++)
        ps57CtlListBox->Check(iPtr, false);

   event.Skip();
}


void options::OnButtonSelectClick( wxCommandEvent& event )
{
    int nOBJL = ps57CtlListBox->GetCount();
    for( int iPtr = 0 ; iPtr < nOBJL ; iPtr++)
        ps57CtlListBox->Check(iPtr, true);

    event.Skip();
}

/*!
 * wxEVT_COMMAND_TREE_SEL_CHANGED event handler for ID_DIRCTRL
 */

void options::OnDirctrlSelChanged( wxTreeEvent& event )
{
    // Before editing this code, remove the block markers.


    if(pDirCtl)
      {
            wxString SelDir;
            SelDir = pDirCtl->GetPath();
            pSelCtl->Clear();
            pSelCtl->AppendText(SelDir);
      }

      event.Skip();
}

/*!
 * Should we show tooltips?
 */

bool options::ShowToolTips()
{
    return TRUE;
}

/*!
 * Get bitmap resources
 */

wxBitmap options::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin options bitmap retrieval
    return wxNullBitmap;
////@end options bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon options::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin options icon retrieval
    return wxNullIcon;
////@end options icon retrieval
}
/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTONADD
 */

void options::OnButtonaddClick( wxCommandEvent& event )
{
    // Before editing this code, remove the block markers.

      wxString SelDir;
      SelDir = pDirCtl->GetPath();


      pTextCtl->AppendText(SelDir);
      pTextCtl->AppendText(_T("\n"));


      event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for xID_OK
 */

void options::OnXidOkClick( wxCommandEvent& event )
{

//    Handle Chart Tab
      wxString dirname;

      if(pTextCtl)
      {
            int n = pTextCtl->GetNumberOfLines();
            if(m_pWorkDirList)
            {
                    m_pWorkDirList->Clear();
                    for(int i=0 ; i<n ; i++)
                    {
                        dirname = pTextCtl->GetLineText(i);
                        if(!dirname.IsEmpty())
                                m_pWorkDirList->Add(dirname);
                    }
            }
      }
      else
      {
          if(m_pCurrentDirList)
          {
              m_pWorkDirList->Clear();
              int nDir = m_pCurrentDirList->GetCount();

              for(int i=0 ; i<nDir ; i++)
              {
                  dirname = m_pCurrentDirList->Item(i);
                  if(!dirname.IsEmpty())
                      m_pWorkDirList->Add(dirname);
              }
          }
      }


//    Handle Settings Tab

      if(m_pConfig)
      {
            m_pConfig->m_bShowDebugWindows = pSettingsCB1->GetValue();
      }

    g_bShowPrintIcon = pPrintShowIcon->GetValue();


//    NMEA Options

// Source
      wxString sel(m_itemNMEAListBox->GetStringSelection());
      if(sel.Contains("COM"))
            sel.Prepend("Serial:");
      else if(sel.Contains("/dev"))
          sel.Prepend("Serial:");
      else if(sel.Contains("GPSD"))
      {
            sel.Empty();
            sel.Append("GPSD:");
            sel.Append(m_itemNMEA_TCPIP_Source->GetLineText(0));
      }
    *pNMEADataSource = sel;

// AP Output
    wxString selp(m_itemNMEAAutoListBox->GetStringSelection());
    *pNMEA_AP_Port = selp;

#ifdef USE_WIFI_CLIENT
// WiFi
    wxString WiFiSource;
    WiFiSource.Empty();
    WiFiSource.Append("TCP/IP:");
    WiFiSource.Append(m_itemWIFI_TCPIP_Source->GetLineText(0));
    *pWIFIServerName = WiFiSource;
#endif

#ifdef USE_S57
    //    Handle s57 Tab
      int nOBJL = ps57CtlListBox->GetCount();

      for( int iPtr = 0 ; iPtr < nOBJL ; iPtr++)
      {
            OBJLElement *pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));

            pOLE->nViz = ps57CtlListBox->IsChecked(iPtr);
    }


      if(ps52plib)
      {
            enum _DisCat nset = OTHER;
            switch(pDispCat->GetSelection())
            {
            case 0:
                  nset = DISPLAYBASE;
                  break;
            case 1:
                  nset = STANDARD;
                  break;
            case 2:
                  nset = OTHER;
                  break;
            case 3:
                  nset = MARINERS_STANDARD;
                  break;
            }
            ps52plib->m_nDisplayCategory = nset;

      }
#endif

      EndModal(1);

}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTONDELETE
 */

void options::OnButtondeleteClick( wxCommandEvent& event )
{

      wxString dirname;

      pTextCtl->Cut();

      int n = pTextCtl->GetNumberOfLines();
      if(m_pWorkDirList)
      {
            m_pWorkDirList->Clear();


            for(int i=0 ; i<n ; i++)
            {
                  dirname = pTextCtl->GetLineText(i);
                  if(!dirname.IsEmpty())
                        m_pWorkDirList->Add(dirname);
            }

            pTextCtl->Clear();

            int nDir = m_pWorkDirList->GetCount();
            for(int id=0 ; id<nDir ; id++)
            {
                  dirname = m_pWorkDirList->Item(id);
                  if(!dirname.IsEmpty())
                  {
                        pTextCtl->AppendText(dirname);
                        pTextCtl->AppendText(_T("\n"));
                  }
            }
      }

      event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTONREBUILD
 */

void options::OnButtonrebuildClick( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTONREBUILD in options.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTONREBUILD in options.
}


/*!
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX
 */

void options::OnDebugcheckbox1Click( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX in options.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CHECKBOX in options.
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_CANCEL
 */

void options::OnCancelClick( wxCommandEvent& event )
{
    // Before editing this code, remove the block markers.
      EndModal(0);

}
/*!
 * wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX
 */

void options::OnRadioboxSelected( wxCommandEvent& event )
{
////@begin wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX in options.
    // Before editing this code, remove the block markers.
    event.Skip();
////@end wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_RADIOBOX in options.
}

void options::OnChooseFont( wxCommandEvent& event )
{

      wxString sel_text_element = m_itemFontElementListBox->GetStringSelection();

      wxFont *psfont;
      wxFontData font_data;

      wxFont *pif = pFontMgr->GetFont(sel_text_element);
      wxFontData init_font_data;
      if(pif)
            init_font_data.SetInitialFont(*pif);

#ifdef __WXX11__
      X11FontPicker dg(pParent, init_font_data);
#else
      wxFontDialog dg(pParent, init_font_data);
#endif
      int retval = dg.ShowModal();
      if(wxID_CANCEL != retval)
      {
            font_data = dg.GetFontData();
            wxFont font = font_data.GetChosenFont();
            psfont = new wxFont(font);
            pFontMgr->SetFont(sel_text_element, psfont);
      }


      event.Skip();
}


void options::OnPageChange(wxNotebookEvent& event)
{

//#ifdef __LINUX__ // __WXX11__

      int i = event.GetSelection();

      //    User selected Chart Page?
      //    If so, build the "Charts" page variants
      //    Also, show a progress dialog, since getting the GenericTreeCtrl may be slow
      //    and the user needs feedback
      if(i == 1)                        // 1 is the index of "Charts" page
      {

          wxSize s = itemPanel9->GetSize();
          int ctl_width = s.GetWidth() - 20;

/*
          wxProgressDialog *pprog_dlg = new wxProgressDialog(_T("OpenCPN Message"), _T("Reading Chart Folders"),
                  100, itemPanel9, wxPD_AUTO_HIDE );
          pprog_dlg->Update( 50);

          wxGenericDirCtrl *pTmpCtl = new wxGenericDirCtrl( itemPanel9, ID_DIRCTRL, *m_pinit_chart_dir, wxDefaultPosition,
                  wxSize(ctl_width, 100), 0, _T("All files (*.*)|*.*"), 0 );

          pprog_dlg->Update( 100);
          delete pTmpCtl;
          delete pprog_dlg;
*/


          wxStaticBox* itemStaticBoxSizer11Static = new wxStaticBox(itemPanel9, wxID_ANY, _("Available Chart Directories"));
          itemStaticBoxSizer11 = new wxStaticBoxSizer(itemStaticBoxSizer11Static, wxVERTICAL);
          itemBoxSizer10->Add(itemStaticBoxSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
          pDirCtl = new wxGenericDirCtrl( itemPanel9, ID_DIRCTRL, *m_pinit_chart_dir, wxDefaultPosition,
                                          wxSize(ctl_width, 100), 0, _T("All files (*.*)|*.*"), 0 );
          itemStaticBoxSizer11->Add(pDirCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);



          pSelCtl = new wxTextCtrl( itemPanel9, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxSize(300, -1), 0 );
          itemStaticBoxSizer11->Add(pSelCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

          wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
          itemStaticBoxSizer11->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
          wxButton* itemButton15 = new wxButton( itemPanel9, ID_BUTTONADD, _("Add Selection"), wxDefaultPosition, wxDefaultSize, 0 );
          itemBoxSizer14->Add(itemButton15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

          itemActiveChartStaticBox = new wxStaticBox(itemPanel9, wxID_ANY, _("Active Chart Directories"));
          wxStaticBoxSizer* itemStaticBoxSizer16 = new wxStaticBoxSizer(itemActiveChartStaticBox, wxVERTICAL);
          itemBoxSizer10->Add(itemStaticBoxSizer16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
          pTextCtl = new wxTextCtrl( itemPanel9, ID_TEXTCTRL, _T(""),
                                     wxDefaultPosition, wxSize(ctl_width, 100), wxTE_MULTILINE ); // size needs 300,100 on gtk
          itemStaticBoxSizer16->Add(pTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

          wxButton* itemButton18 = new wxButton( itemPanel9, ID_BUTTONDELETE, _("Delete Selection"), wxDefaultPosition, wxDefaultSize, 0 );
          itemStaticBoxSizer16->Add(itemButton18, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

          wxStaticBox* itemStaticBoxSizer19Static = new wxStaticBox(itemPanel9, wxID_ANY, _("Chart List"));
          wxStaticBoxSizer* itemStaticBoxSizer19 = new wxStaticBoxSizer(itemStaticBoxSizer19Static, wxVERTICAL);
          itemBoxSizer10->Add(itemStaticBoxSizer19, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
          wxButton* itemButton20 = new wxButton( itemPanel9, ID_BUTTONREBUILD, _("Rebuild..."), wxDefaultPosition, wxDefaultSize, 0 );
          itemStaticBoxSizer19->Add(itemButton20, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

          //        Fill in the control variable data

          //        Currently selected chart dirs
          wxString dirname;
          if(m_pCurrentDirList)
          {
              int nDir = m_pCurrentDirList->GetCount();
              for(int i=0 ; i<nDir ; i++)
              {
                  dirname = m_pCurrentDirList->Item(i);
                  if(!dirname.IsEmpty())
                  {
                      if (pTextCtl)
                      {
                          pTextCtl->AppendText(dirname);
                          pTextCtl->AppendText(_T("\n"));
                      }
                  }
              }
          }

          itemBoxSizer10->Layout();
      }
//#endif
}


void options::OnNMEASourceChoice(wxCommandEvent& event)
{
    int i = event.GetSelection();
    wxString src(m_itemNMEAListBox->GetString(i));
    if(src.Contains("GPSD"))
    {
        m_itemNMEA_TCPIP_StaticBox->Enable();
        m_itemNMEA_TCPIP_Source->Enable();

        m_itemNMEA_TCPIP_Source->Clear();
        m_itemNMEA_TCPIP_Source->WriteText("localhost"); // default

        wxString source;
        source = *pNMEADataSource;
        if(source.Contains("GPSD"))
        {
            wxString ip;
            ip = source.Mid(5);
            if(ip.Len())
            {
                m_itemNMEA_TCPIP_Source->Clear();
                m_itemNMEA_TCPIP_Source->WriteText(ip);
            }
        }
    }
    else
    {
        m_itemNMEA_TCPIP_StaticBox->Disable();
        m_itemNMEA_TCPIP_Source->Disable();
    }

}

//--------------------------------------------------------------------------------------------------------
//    Options Dialog Pre-Setup
//--------------------------------------------------------------------------------------------------------
#include "wx/artprov.h"

//    Ask the ::wxArtProvider to preload the icons required for a wxGenericDirCtrl
//    Thereby accelerating the Options dialog creation.
OptionSetup::OptionSetup()
{

      wxBitmap btmp;

     // folder:
      btmp = wxArtProvider::GetBitmap(wxART_FOLDER,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));
    // folder_open
      btmp = wxArtProvider::GetBitmap(wxART_FOLDER_OPEN,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));
    // drive
      btmp = wxArtProvider::GetBitmap(wxART_HARDDISK,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));
    // cdrom
      btmp = wxArtProvider::GetBitmap(wxART_CDROM,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));
    // floppy
      btmp = wxArtProvider::GetBitmap(wxART_FLOPPY,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));
    // removeable
      btmp = wxArtProvider::GetBitmap(wxART_REMOVABLE,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));
    // file
      btmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));
    // exe file
      btmp = wxArtProvider::GetBitmap(wxART_EXECUTABLE_FILE,
                              wxART_CMN_DIALOG,
                              wxSize(16, 15));

}


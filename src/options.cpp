/******************************************************************************
 * $Id: options.cpp,v 1.34 2009/11/18 01:25:31 bdbcat Exp $
 *
 * Project:  OpenCPN
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
 * Revision 1.34  2009/11/18 01:25:31  bdbcat
 * 1.3.5 Beta 1117
 *
 * Revision 1.33  2009/09/29 18:14:26  bdbcat
 * Add color to managed fonts
 *
 * Revision 1.32  2009/09/25 15:15:38  bdbcat
 * Implement toplevel CM93 detail slider
 *
 * Revision 1.31  2009/09/18 01:29:12  bdbcat
 * Add cm93 zoom factor slider
 *
 * Revision 1.30  2009/09/11 20:31:19  bdbcat
 * Utilize wxScollingDialog
 *
 * Revision 1.29  2009/08/31 02:37:36  bdbcat
 * Improve option legends
 *
 * Revision 1.28  2009/08/29 23:30:46  bdbcat
 * Track options now radio buttons
 *
 * Revision 1.27  2009/08/22 01:21:17  bdbcat
 * Tracks
 *
 * Revision 1.26  2009/08/03 03:16:39  bdbcat
 * Cleanup for MSVC
 *
 * Revision 1.25  2009/07/17 03:54:55  bdbcat
 * Add config option for Wheel Zoom to cursor.
 *
 * Revision 1.24  2009/07/16 02:39:12  bdbcat
 * Allow override of NMEA data source
 *
 * Revision 1.23  2009/07/03 02:56:00  bdbcat
 * Allow fifo data source.
 *
 * Revision 1.22  2009/06/17 02:46:43  bdbcat
 * Add AIS Alerts
 *
 * Revision 1.21  2009/06/14 01:50:08  bdbcat
 * AIS Alert Dialog
 *
 * Revision 1.20  2009/06/03 03:19:22  bdbcat
 * Implement AIS/GPS Port sharing
 *
 * Revision 1.19  2009/05/05 03:59:27  bdbcat
 * New text options
 *
 * Revision 1.18  2009/04/19 02:24:56  bdbcat
 * Implement "Important Text" option
 *
 * Revision 1.17  2009/04/18 03:30:27  bdbcat
 * Add tab "Vector Charts"
 *
 * Revision 1.16  2009/04/13 02:33:25  bdbcat
 * Add "show ATON labels" option
 *
 * Revision 1.15  2009/03/26 22:30:21  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.14  2008/12/19 01:40:52  bdbcat
 * Add selectable depth unit conversion for S57 charts
 *
 * Revision 1.13  2008/12/09 03:30:25  bdbcat
 * Cleanup Comments
 *
 * Revision 1.12  2008/12/09 03:29:03  bdbcat
 * Cleanup
 *
 * Revision 1.11  2008/11/12 04:12:08  bdbcat
 * Support Garmin Devices
 *
 * Revision 1.10  2008/08/26 13:46:25  bdbcat
 * Better color scheme support
 *
 * Revision 1.9  2008/08/09 23:58:40  bdbcat
 * Numerous revampings....
 *
 * Revision 1.8  2008/04/11 03:25:08  bdbcat
 * Implement Auto Anchor Mark
 *
 * Revision 1.7  2008/04/10 01:07:52  bdbcat
 * Cleanup and fix EOL problem on wxTextCtrl
 *
 * Revision 1.6  2008/03/30 22:09:48  bdbcat
 * Cleanup
 *
 * Revision 1.5  2008/01/12 06:20:47  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.4  2008/01/10 03:37:18  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.2  2007/06/10 02:31:21  bdbcat
 * Cleanup
 *
 * Revision 1.8  2006/12/03 21:29:03  dsr
 * Cleanup AIS options.
 *
 * Revision 1.7  2006/11/01 02:19:08  dsr
 * AIS Support
 *
 * Revision 1.6  2006/10/08 00:37:16  dsr
 * no message
 *
 *
 */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/generic/progdlgg.h"
#include "wx/sound.h"


#include "dychart.h"
#include "chart1.h"
#include "options.h"
#include "cm93.h"

#include "navutil.h"
#ifdef USE_S57
#include "s52plib.h"
#include "s52utils.h"
#endif

extern bool             g_bShowPrintIcon;
extern bool             g_bShowOutlines;
extern bool             g_bShowDepthUnits;
extern wxString         *pNMEADataSource;
extern wxString         *pNMEA_AP_Port;
extern FontMgr          *pFontMgr;
extern wxString         *pAIS_Port;
extern wxString         *pInit_Chart_Dir;
extern bool             g_bAutoAnchorMark;
extern ColorScheme      global_color_scheme;
extern bool             g_bGarminPersistance;
extern wxString         g_SData_Locn;


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
extern bool             g_bAIS_CPA_Alert;
extern bool             g_bAIS_CPA_Alert_Audio;
extern wxString         g_sAIS_Alert_Sound_File;
extern bool             g_bAIS_CPA_Alert_Suppress_Moored;

extern bool             g_bShowGPXIcons;                     // toh, 2009.02.14
extern bool             g_bNavAidShowRadarRings;            // toh, 2009.02.24
extern int              g_iNavAidRadarRingsNumberVisible;   // toh, 2009.02.24
extern float            g_fNavAidRadarRingsStep;            // toh, 2009.02.24
extern int              g_pNavAidRadarRingsStepUnits;       // toh, 2009.02.24
extern bool             g_bWayPointPreventDragging;         // toh, 2009.02.24

extern bool             g_bEnableZoomToCursor;
extern bool             g_bShowTrackIcon;
extern double           g_TrackIntervalSeconds;
extern double           g_TrackDeltaDistance;
extern double           g_TrackDeltaDistance;
extern bool             g_bTrackTime;
extern bool             g_bTrackDistance;

extern int              g_cm93_zoom_factor;
extern CM93DSlide       *pCM93DetailSlider;
extern bool             g_bShowCM93DetailSlider;

extern bool             g_bShowGRIBIcon;

#ifdef USE_WIFI_CLIENT
extern wxString         *pWIFIServerName;
#endif

#ifdef USE_S57
extern s52plib          *ps52plib;
#endif

//    Some constants
#define ID_CHOICE_NMEA  wxID_HIGHEST + 1


extern wxArrayString *EnumerateSerialPorts(void);           // in chart1.cpp

IMPLEMENT_DYNAMIC_CLASS( options, wxDialog )

BEGIN_EVENT_TABLE( options, wxDialog )
//    BUGBUG DSR Must use wxID_TREECTRL to capture tree events.

    EVT_TREE_SEL_CHANGED( wxID_TREECTRL, options::OnDirctrlSelChanged )
    EVT_CHECKBOX( ID_DEBUGCHECKBOX1, options::OnDebugcheckbox1Click )
    EVT_TREE_SEL_CHANGED( ID_DIRCTRL, options::OnDirctrlSelChanged )
    EVT_BUTTON( ID_BUTTONADD, options::OnButtonaddClick )
    EVT_BUTTON( ID_BUTTONDELETE, options::OnButtondeleteClick )
    EVT_RADIOBOX( ID_RADIOBOX, options::OnRadioboxSelected )
    EVT_BUTTON( xID_OK, options::OnXidOkClick )
    EVT_BUTTON( wxID_CANCEL, options::OnCancelClick )
    EVT_BUTTON( ID_BUTTONFONTCHOOSE, options::OnChooseFont )
    EVT_NOTEBOOK_PAGE_CHANGED(ID_NOTEBOOK, options::OnPageChange)
    EVT_CHOICE( ID_CHOICE_NMEA, options::OnNMEASourceChoice )
    EVT_COMBOBOX( ID_CHOICE_NMEA, options::OnNMEASourceChoice )
    EVT_RADIOBOX(ID_RADIOBOX, options::OnDisplayCategoryRadioButton )
    EVT_BUTTON( ID_CLEARLIST, options::OnButtonClearClick )
    EVT_BUTTON( ID_SELECTLIST, options::OnButtonSelectClick )
    EVT_BUTTON( ID_AISALERTSELECTSOUND, options::OnButtonSelectSound )
    EVT_BUTTON( ID_AISALERTTESTSOUND, options::OnButtonTestSound )

END_EVENT_TABLE()


options::options( )
{
}

options::options( MyFrame* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
      Init();
      wxScrollingDialog::Init();

      pParent = parent;

      //    As a display optimization....
      //    if current color scheme is other than DAY,
      //    Then create the dialog ..WITHOUT.. borders and title bar.
      //    This way, any window decorations set by external themes, etc
      //    will not detract from night-vision

      long wstyle = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxVSCROLL;
//      if(global_color_scheme != GLOBAL_COLOR_SCHEME_DAY)
//            wstyle |= (wxNO_BORDER);

      SetLayoutAdaptation(true);
      SetLayoutAdaptationLevel(2);

//      Create(parent, id, caption, pos, size, wstyle);

      SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
      wxScrollingDialog::Create( parent, id, caption, pos, size,wstyle );

      CreateControls();
      if (GetSizer())
      {
            GetSizer()->SetSizeHints(this);
      }
      Centre();
}
void options::Init()
{
    pDirCtl = NULL;
    m_pCurrentDirList = NULL;
    m_pWorkDirList = NULL;

    pDebugShowStat = NULL;
    pSelCtl = NULL;
    pTextCtl = NULL;
    ps57Ctl = NULL;
    ps57CtlListBox = NULL;
    pDispCat = NULL;
    m_pSerialArray = NULL;

    itemStaticBoxSizer11 = NULL;
    pDirCtl = NULL;;
    itemActiveChartStaticBox = NULL;

    m_pSerialArray = EnumerateSerialPorts();

}


bool options::Create( MyFrame* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{

    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );


    CreateControls();

    Fit();
    Centre();

    return TRUE;
}


void options::CreateControls()
{
    unsigned int iPortIndex;

    int border_size = 4;
    int check_spacing = 4;
    int group_item_spacing = 1;           // use for items within one group, with Add(...wxALL)

    wxFont *qFont = wxTheFontList->FindOrCreateFont ( 10, wxFONTFAMILY_DEFAULT,
                wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );
    SetFont(*qFont);

    int font_size_y, font_descent, font_lead;
    GetTextExtent(_T("0"), NULL, &font_size_y, &font_descent, &font_lead);
    wxSize small_button_size(-1, (int)(1.5 * (font_size_y + font_descent + font_lead)));


    //      Check the display size.
    //      If "small", adjust some factors to squish out some more white space
    int width, height;
    ::wxDisplaySize(&width, &height);

    if(height < 700)
    {
          border_size = 2;
          check_spacing = 2;
          group_item_spacing = 1;

          wxFont *sFont = wxTheFontList->FindOrCreateFont ( 8, wxFONTFAMILY_DEFAULT,
                      wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );
          SetFont(*sFont);

          int font_size_y, font_descent, font_lead;
          GetTextExtent(_T("0"), NULL, &font_size_y, &font_descent, &font_lead);
          small_button_size = wxSize(-1, (int)(1.5 * (font_size_y + font_descent + font_lead)));
    }

    options* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    itemNotebook4 = new wxNotebook( itemDialog1, ID_NOTEBOOK, wxDefaultPosition,
            wxSize(-1, -1), wxNB_TOP );
    itemBoxSizer2->Add(itemNotebook4, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, border_size);

   //      Add Invariant Notebook buttons
    wxBoxSizer* itemBoxSizer28 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer28, 0, wxALIGN_RIGHT|wxALL, border_size);

    m_OKButton = new wxButton( itemDialog1, xID_OK, _("Ok"), wxDefaultPosition, wxDefaultSize, 0 );
    m_OKButton->SetDefault();
    itemBoxSizer28->Add(m_OKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, border_size);

    m_CancelButton = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer28->Add(m_CancelButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, border_size);


    //  Create "Settings" panel

    itemPanel5 = new wxPanel( itemNotebook4, ID_PANEL2, wxDefaultPosition, wxDefaultSize,
                                       wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    itemPanel5->SetSizer(itemBoxSizer6);

    itemNotebook4->AddPage(itemPanel5, _("Settings"));



    //  Debug checkbox
    wxStaticBox* itemStaticBoxSizerDebugStatic = new wxStaticBox(itemPanel5, wxID_ANY, _("Navigation Data"));
    wxStaticBoxSizer* itemStaticBoxSizerDebug = new wxStaticBoxSizer(itemStaticBoxSizerDebugStatic, wxVERTICAL);
    itemBoxSizer6->Add(itemStaticBoxSizerDebug, 0, wxEXPAND|wxALL, border_size);
    pDebugShowStat = new wxCheckBox( itemPanel5, ID_DEBUGCHECKBOX1, _("Show Status Bar"), wxDefaultPosition,
                             wxSize(-1, -1), 0 );
    pDebugShowStat->SetValue(FALSE);
    itemStaticBoxSizerDebug->Add(pDebugShowStat, 1, wxALIGN_LEFT|wxALL, 2);

    //  Printing checkbox
    wxStaticBox* itemStaticBoxSizerPrintStatic = new wxStaticBox(itemPanel5, wxID_ANY, _("Printing"));
    wxStaticBoxSizer* itemStaticBoxSizerPrint = new wxStaticBoxSizer(itemStaticBoxSizerPrintStatic, wxVERTICAL);
    itemBoxSizer6->Add(itemStaticBoxSizerPrint, 0, wxEXPAND|wxALL, 5);
    pPrintShowIcon = new wxCheckBox( itemPanel5, ID_PRINTCHECKBOX1, _("Show Printing Icon"), wxDefaultPosition,
                             wxSize(-1, -1), 0 );
    pPrintShowIcon->SetValue(FALSE);
    itemStaticBoxSizerPrint->Add(pPrintShowIcon, 1, wxALIGN_LEFT|wxALL, 2);

///
        // Chart Display Options Box
    wxStaticBox* itemStaticBoxSizerCDOStatic = new wxStaticBox(itemPanel5, wxID_ANY, _("Chart Display Options"));
    wxStaticBoxSizer* itemStaticBoxSizerCDO = new wxStaticBoxSizer(itemStaticBoxSizerCDOStatic, wxVERTICAL);
    itemBoxSizer6->Add(itemStaticBoxSizerCDO, 0, wxEXPAND|wxALL, border_size);

    //  Chart Outlines checkbox
    pCDOOutlines = new wxCheckBox( itemPanel5, ID_OUTLINECHECKBOX1, _("Show Chart Outlines"), wxDefaultPosition,
                                   wxSize(-1, -1), 0 );
    pCDOOutlines->SetValue(FALSE);
    itemStaticBoxSizerCDO->Add(pCDOOutlines, 1, wxALIGN_LEFT|wxALL, 2);


    //  Depth Unit checkbox
    pSDepthUnits = new wxCheckBox( itemPanel5, ID_SHOWDEPTHUNITSBOX1, _("Show DepthUnits"), wxDefaultPosition,
                                   wxSize(-1, -1), 0 );
    pSDepthUnits->SetValue(FALSE);
    itemStaticBoxSizerCDO->Add(pSDepthUnits, 1, wxALIGN_LEFT|wxALL, 2);


    //  Auto Anchor Mark
    pAutoAnchorMark = new wxCheckBox( itemPanel5, ID_AUTOANCHORMARKBOX1, _("Automatic Anchor Mark"), wxDefaultPosition,
                                      wxSize(-1, -1), 0 );
    pAutoAnchorMark->SetValue(FALSE);
    itemStaticBoxSizerCDO->Add(pAutoAnchorMark, 1, wxALIGN_LEFT|wxALL, 2);
///

//    Add NMEA Options Box
    wxStaticBox* itemNMEAStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("NMEA Options"));
    wxStaticBoxSizer* itemNMEAStaticBoxSizer = new wxStaticBoxSizer(itemNMEAStaticBox, wxVERTICAL);
    itemBoxSizer6->Add(itemNMEAStaticBoxSizer, 0, wxEXPAND|wxALL, 4);


//    Add NMEA data source controls
    wxStaticBox* itemNMEASourceStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _("NMEA Data Source"));
    wxStaticBoxSizer* itemNMEASourceStaticBoxSizer = new wxStaticBoxSizer(itemNMEASourceStaticBox, wxVERTICAL);
    itemNMEAStaticBoxSizer->Add(itemNMEASourceStaticBoxSizer, 0, wxEXPAND|wxALL, 4);

    m_itemNMEAListBox = new wxComboBox(itemPanel5, ID_CHOICE_NMEA);
    m_itemNMEAListBox->Append( _T("None"));

      //    Fill in the listbox with all detected serial ports
    for (iPortIndex=0 ; iPortIndex < m_pSerialArray->GetCount() ; iPortIndex++)
          m_itemNMEAListBox->Append( m_pSerialArray->Item(iPortIndex) );


//    Search the string array looking for "GARMIN"
      bool bfound_garmin_string = false;
    for (iPortIndex=0 ; iPortIndex < m_pSerialArray->GetCount() ; iPortIndex++)
      {
            if(   m_pSerialArray->Item(iPortIndex).Contains(_T("GARMIN")))
            {
                  bfound_garmin_string = true;
                  break;
            }
      }

        //  Garmin persistence logic:
        //  Make sure "GARMIN" is in the list if the persistence flag is set.
        //  This covers the situation where Garmin is desired, but the
        //  device is not connected yet.
        //  n.b. Hot-plugging is not supported.  Opencpn must be
        //  restarted with device inserted to enable this option.
      if(g_bGarminPersistance && !bfound_garmin_string)
      m_itemNMEAListBox->Append( _T("GARMIN"));


#ifndef OCPN_DISABLE_SOCKETS
      m_itemNMEAListBox->Append( _T("Network GPSD"));
#endif

      m_itemNMEAListBox->Append( _T("AIS Port (Shared)"));


//    Activate the proper selections
//    n.b. Hard coded indices
      int sidx;
      bool tcp_en = false;
      wxString source;
      source = (*pNMEADataSource);
      if(source.Upper().Contains(_T("SERIAL")))
      {
          wxString sourcex = source.Mid(7);
          sidx = m_itemNMEAListBox->FindString(sourcex);
      }
      else if(source.Upper().Contains(_T("NONE")))
          sidx = 0;

      else if(source.Upper().Contains(_("GARMIN")))
          sidx = m_itemNMEAListBox->FindString(_T("GARMIN"));

      else if(source.Upper().Contains(_("AIS")))
            sidx = m_itemNMEAListBox->FindString(_T("AIS Port (Shared)"));

#ifndef OCPN_DISABLE_SOCKETS
      else if(source.Upper().Contains(_T("GPSD")))
      {
          sidx = m_itemNMEAListBox->FindString(_T("Network GPSD"));
          tcp_en = true;
      }
#endif
      else
          sidx = 0;                                 // malformed selection


      if(sidx ==  wxNOT_FOUND)                  // user specified in ComboBox
      {
          wxString nsource = source.AfterFirst(':');
          m_itemNMEAListBox->Append( nsource );
          sidx = m_itemNMEAListBox->FindString(nsource);
      }


      m_itemNMEAListBox->SetSelection(sidx);
      itemNMEASourceStaticBoxSizer->Add(m_itemNMEAListBox, 0, wxEXPAND|wxALL, border_size);

#ifndef OCPN_DISABLE_SOCKETS

//    Add NMEA TCP/IP Server address
      m_itemNMEA_TCPIP_StaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _T("GPSD Data Server"));
      m_itemNMEA_TCPIP_StaticBoxSizer = new wxStaticBoxSizer(m_itemNMEA_TCPIP_StaticBox, wxVERTICAL);
      itemNMEAStaticBoxSizer->Add(m_itemNMEA_TCPIP_StaticBoxSizer, 0, wxEXPAND|wxALL, 4);

      m_itemNMEA_TCPIP_Source = new wxTextCtrl(itemPanel5, wxID_ANY);
      m_itemNMEA_TCPIP_StaticBoxSizer->Add(m_itemNMEA_TCPIP_Source, 0, wxEXPAND|wxALL, border_size);

      m_itemNMEA_TCPIP_StaticBox->Enable(tcp_en);
      m_itemNMEA_TCPIP_Source->Enable(tcp_en);

      if(tcp_en)
      {
            wxString ip;
            ip = source.Mid(5);
            m_itemNMEA_TCPIP_Source->WriteText(ip);
      }
#endif



//    Add Autopilot serial output port controls
      wxStaticBox* itemNMEAAutoStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _T("Autopilot Output Port"));
      wxStaticBoxSizer* itemNMEAAutoStaticBoxSizer = new wxStaticBoxSizer(itemNMEAAutoStaticBox, wxVERTICAL);
      itemNMEAStaticBoxSizer->Add(itemNMEAAutoStaticBoxSizer, 0, wxEXPAND|wxALL, 4);

      m_itemNMEAAutoListBox = new wxComboBox(itemPanel5, ID_CHOICE_AP);
      m_itemNMEAAutoListBox->Append( _T("None"));

      //    Fill in the listbox with all detected serial ports
      for (iPortIndex=0 ; iPortIndex < m_pSerialArray->GetCount() ; iPortIndex++)
            m_itemNMEAAutoListBox->Append( m_pSerialArray->Item(iPortIndex) );

      wxString ap_com;
      if(pNMEA_AP_Port->Contains(_T("Serial")))
          ap_com = pNMEA_AP_Port->Mid(7);
      else
          ap_com = _T("None");

      sidx = m_itemNMEAAutoListBox->FindString(ap_com);
      m_itemNMEAAutoListBox->SetSelection(sidx);

      itemNMEAAutoStaticBoxSizer->Add(m_itemNMEAAutoListBox, 0, wxEXPAND|wxALL, border_size);


#ifdef USE_WIFI_CLIENT
//    Add WiFi Options Box
      wxStaticBox* itemWIFIStaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _T("WiFi Options"));
      wxStaticBoxSizer* itemWIFIStaticBoxSizer = new wxStaticBoxSizer(itemWIFIStaticBox, wxVERTICAL);
      itemBoxSizer6->Add(itemWIFIStaticBoxSizer, 0, wxEXPAND|wxALL, border_size);

//    Add WiFi TCP/IP Server address
      m_itemWIFI_TCPIP_StaticBox = new wxStaticBox(itemPanel5, wxID_ANY, _T("TCP/IP WiFi Data Server"));
      m_itemWIFI_TCPIP_StaticBoxSizer = new wxStaticBoxSizer(m_itemWIFI_TCPIP_StaticBox, wxVERTICAL);
      itemWIFIStaticBoxSizer->Add(m_itemWIFI_TCPIP_StaticBoxSizer, 0, wxEXPAND|wxALL, border_size);

      m_itemWIFI_TCPIP_Source = new wxTextCtrl(itemPanel5, wxID_ANY);
      m_itemWIFI_TCPIP_StaticBoxSizer->Add(m_itemWIFI_TCPIP_Source, 0, wxEXPAND|wxALL, border_size);

      m_itemWIFI_TCPIP_StaticBox->Enable(1);
      m_itemWIFI_TCPIP_Source->Enable(1);

      wxString ip;
      ip = pWIFIServerName->Mid(7);
      m_itemWIFI_TCPIP_Source->WriteText(ip);
#endif




//    Build "Charts" page

    itemPanel9 = new wxPanel( itemNotebook4, ID_PANEL, wxDefaultPosition, wxDefaultSize,
                              wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemBoxSizer10 = new wxBoxSizer(wxVERTICAL);
    itemPanel9->SetSizer(itemBoxSizer10);

    //      Linux wxUNIVERSAL wxGenericDirCtrl is --very-- slow.
    //      Slowness is in ArtProvider, generating the proper icons
    //      So....
    //      Move the dir tree control out of the ctor, and only build it if "CHART" panel is selected.
    //      See this::OnPageChange event handler


    itemNotebook4->AddPage(itemPanel9, _T("Charts"));


    //      Build S57 Options page

    ps57Ctl = new wxPanel( itemNotebook4, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxVERTICAL);
    ps57Ctl->SetSizer(itemBoxSizer25);

//    wxBoxSizer* itemBoxSizer25 = new wxBoxSizer(wxHORIZONTAL);
//    itemBoxSizer22->Add(itemBoxSizer25, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, border_size);

    wxStaticBox* itemStaticBoxSizer26Static = new wxStaticBox(ps57Ctl, wxID_ANY, _T("Chart Display Filters"));
    wxStaticBoxSizer* itemStaticBoxSizer26 = new wxStaticBoxSizer(itemStaticBoxSizer26Static, wxHORIZONTAL);
    itemBoxSizer25->Add(itemStaticBoxSizer26, 0, wxALL|wxEXPAND, 4);

    wxStaticBox* itemStaticBoxSizer57Static = new wxStaticBox(ps57Ctl, wxID_ANY, _T("Mariner's Standard"));
    wxStaticBoxSizer* itemStaticBoxSizer57 = new wxStaticBoxSizer(itemStaticBoxSizer57Static, wxVERTICAL);
    itemStaticBoxSizer26->Add(itemStaticBoxSizer57, 1, wxALL|wxEXPAND, 2);

    wxString* ps57CtlListBoxStrings = NULL;
    ps57CtlListBox = new wxCheckListBox( ps57Ctl, ID_CHECKLISTBOX, wxDefaultPosition, wxSize(-1, 150), 0,
                                         ps57CtlListBoxStrings, wxLB_SINGLE );
    itemStaticBoxSizer57->Add(ps57CtlListBox, 0, wxALIGN_LEFT|wxALL, border_size);

    wxBoxSizer* itemBoxSizer57 = new wxBoxSizer(wxVERTICAL);
    itemStaticBoxSizer57->Add(itemBoxSizer57, 1, wxALL|wxEXPAND, 2);

    itemButtonClearList = new wxButton( ps57Ctl, ID_CLEARLIST, _T("Clear All"),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer57->Add(itemButtonClearList, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);

    itemButtonSelectList = new wxButton( ps57Ctl, ID_SELECTLIST, _T("Select All"),
            wxDefaultPosition, wxDefaultSize, 0 );
    itemButtonSelectList->SetDefault();
    itemBoxSizer57->Add(itemButtonSelectList, 0, wxALIGN_CENTER_VERTICAL|wxALL, 2);



    wxBoxSizer* itemBoxSizer75 = new wxBoxSizer(wxVERTICAL);
    itemStaticBoxSizer26->Add(itemBoxSizer75, 1, wxALL, border_size);

    wxString pDispCatStrings[] = {
        _T("&Base"),
        _T("&Standard"),
        _T("&Other"),
        _T("&MarinersStandard")
    };
    pDispCat = new wxRadioBox( ps57Ctl, ID_RADIOBOX, _T("Display Category"), wxDefaultPosition, wxDefaultSize,
                               4, pDispCatStrings, 1, wxRA_SPECIFY_COLS );
    itemBoxSizer75->Add(pDispCat, 0, wxALL|wxEXPAND, 2);



    pCheck_SOUNDG = new wxCheckBox( ps57Ctl, ID_SOUNDGCHECKBOX, _T("ShowSoundings"), wxDefaultPosition,
                                     wxSize(-1, -1), 0 );
    pCheck_SOUNDG->SetValue(FALSE);
    itemBoxSizer75->Add(pCheck_SOUNDG, 1, wxALIGN_LEFT|wxALL|wxEXPAND, check_spacing);

    pCheck_META = new wxCheckBox( ps57Ctl, ID_METACHECKBOX, _T("META Objects"), wxDefaultPosition,
            wxSize(-1, -1), 0 );
    pCheck_META->SetValue(FALSE);
    itemBoxSizer75->Add(pCheck_META, 1, wxALIGN_LEFT|wxALL|wxEXPAND, check_spacing);

    pCheck_SHOWIMPTEXT = new wxCheckBox( ps57Ctl, ID_IMPTEXTCHECKBOX, _T("Show Important Text Only"), wxDefaultPosition,
                                      wxSize(-1, -1), 0 );
    pCheck_SHOWIMPTEXT->SetValue(FALSE);
    itemBoxSizer75->Add(pCheck_SHOWIMPTEXT, 1, wxALIGN_LEFT|wxALL|wxEXPAND, check_spacing);

    pCheck_SCAMIN = new wxCheckBox( ps57Ctl, ID_SCAMINCHECKBOX, _T("Use SCAMIN"), wxDefaultPosition,
            wxSize(-1, -1), 0 );
    pCheck_SCAMIN->SetValue(FALSE);
    itemBoxSizer75->Add(pCheck_SCAMIN, 1, wxALIGN_LEFT|wxALL|wxEXPAND, check_spacing);

    pCheck_ATONTEXT = new wxCheckBox( ps57Ctl, ID_ATONTEXTCHECKBOX, _T("Show ATON labels"), wxDefaultPosition,
                                    wxSize(-1, -1), 0 );
    pCheck_SCAMIN->SetValue(FALSE);
    itemBoxSizer75->Add(pCheck_ATONTEXT, 1, wxALIGN_LEFT|wxALL|wxEXPAND, check_spacing);

    pCheck_LDISTEXT = new wxCheckBox( ps57Ctl, ID_LDISTEXTCHECKBOX, _T("Show Light Descriptions"), wxDefaultPosition,
                                      wxSize(-1, -1), 0 );
    pCheck_LDISTEXT->SetValue(FALSE);
    itemBoxSizer75->Add(pCheck_LDISTEXT, 1, wxALIGN_LEFT|wxALL|wxEXPAND, check_spacing);

    pCheck_DECLTEXT = new wxCheckBox( ps57Ctl, ID_DECLTEXTCHECKBOX, _T("De-Clutter Text (exp.)"), wxDefaultPosition,
                                      wxSize(-1, -1), 0 );
    pCheck_DECLTEXT->SetValue(FALSE);
    itemBoxSizer75->Add(pCheck_DECLTEXT, 1, wxALIGN_LEFT|wxALL|wxEXPAND, check_spacing);

    wxStaticBox* itemStaticBoxSizer83Static = new wxStaticBox(ps57Ctl, wxID_ANY, _T("Chart Display Style"));
    wxStaticBoxSizer* itemStaticBoxSizer83 = new wxStaticBoxSizer(itemStaticBoxSizer83Static, wxVERTICAL);
    itemStaticBoxSizer26->Add(itemStaticBoxSizer83, 1, wxALL|wxEXPAND, 2);

    wxString pPointStyleStrings[] = {
        _T("&Paper Chart"),
        _T("&Simplified"),
    };
    pPointStyle = new wxRadioBox( ps57Ctl, ID_RADIOBOX, _T("Points"), wxDefaultPosition, wxDefaultSize,
                                  2, pPointStyleStrings, 1, wxRA_SPECIFY_COLS );
    itemStaticBoxSizer83->Add(pPointStyle, 0, wxALL|wxEXPAND, border_size);

    wxString pBoundStyleStrings[] = {
        _T("&Plain"),
        _T("&Symbolized"),
    };
    pBoundStyle = new wxRadioBox( ps57Ctl, ID_RADIOBOX, _T("Boundaries"), wxDefaultPosition, wxDefaultSize,
                                              2, pBoundStyleStrings, 1, wxRA_SPECIFY_COLS );
    itemStaticBoxSizer83->Add(pBoundStyle, 0, wxALL|wxEXPAND, border_size);

    wxString pColorNumStrings[] = {
          _T("&2 Color"),
          _T("&4 Color"),
    };
    p24Color = new wxRadioBox( ps57Ctl, ID_RADIOBOX, _T("Colors"), wxDefaultPosition, wxDefaultSize,
                               2, pColorNumStrings, 1, wxRA_SPECIFY_COLS );
    itemStaticBoxSizer83->Add(p24Color, 0, wxALL|wxEXPAND, border_size);



    wxStaticBox *pslStatBox = new wxStaticBox(ps57Ctl, wxID_ANY, _T("CM93 Zoom Detail"));
    wxStaticBoxSizer* itemStaticBoxSizersl = new wxStaticBoxSizer(pslStatBox, wxVERTICAL);
    itemStaticBoxSizer83->Add(itemStaticBoxSizersl, 0, wxALL|wxEXPAND, border_size);
    m_pSlider_CM93_Zoom = new wxSlider(ps57Ctl, ID_CM93ZOOM , 0, -CM93_ZOOM_FACTOR_MAX_RANGE, CM93_ZOOM_FACTOR_MAX_RANGE,
                                       wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_AUTOTICKS | wxSL_LABELS);
    itemStaticBoxSizersl->Add(m_pSlider_CM93_Zoom, 0, wxALL|wxEXPAND, border_size);


    wxStaticBox*  pdepth_static = new wxStaticBox(ps57Ctl, wxID_ANY, _T("Depth Settings"));
    wxStaticBoxSizer *pdepth_sizer = new wxStaticBoxSizer(pdepth_static, wxHORIZONTAL);
    itemBoxSizer25->Add(pdepth_sizer, 0, wxTOP|wxALL|wxEXPAND, 2);

    wxStaticBox* itemStaticBoxSizer27Static = new wxStaticBox(ps57Ctl, wxID_ANY, _T("Depth Settings(m)"));
    wxStaticBoxSizer* itemStaticBoxSizer27 = new wxStaticBoxSizer(itemStaticBoxSizer27Static, wxVERTICAL);
    pdepth_sizer/*itemBoxSizer25*/->Add(itemStaticBoxSizer27, 0, wxTOP|wxALL|wxEXPAND, 2);

    wxStaticText* itemStaticText4 = new wxStaticText( ps57Ctl, wxID_STATIC, _T("Shallow Depth"));
    itemStaticBoxSizer27->Add(itemStaticText4, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, border_size);

    m_ShallowCtl = new wxTextCtrl( ps57Ctl, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(110, -1), 0 );
    itemStaticBoxSizer27->Add(m_ShallowCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, 2);

    wxStaticText* itemStaticText5 = new wxStaticText( ps57Ctl, wxID_STATIC, _T("Safety Depth"));
    itemStaticBoxSizer27->Add(itemStaticText5, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_SafetyCtl = new wxTextCtrl( ps57Ctl, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(110, -1), 0 );
    itemStaticBoxSizer27->Add(m_SafetyCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, 2);

    wxStaticText* itemStaticText6 = new wxStaticText( ps57Ctl, wxID_STATIC, _T("Deep Depth"));
    itemStaticBoxSizer27->Add(itemStaticText6, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, border_size);

    m_DeepCtl = new wxTextCtrl( ps57Ctl, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(110, -1), 0 );
    itemStaticBoxSizer27->Add(m_DeepCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, 2);



    wxString pDepthUnitStrings[] = {
             _T("&Feet"),
             _T("&Metres"),
             _T("&Fathoms"),
    };

    pDepthUnitSelect = new wxRadioBox( ps57Ctl, ID_RADIOBOX, _T("Chart Depth Units"), wxDefaultPosition, wxDefaultSize,
                               3, pDepthUnitStrings, 1, wxRA_SPECIFY_COLS );
    pdepth_sizer->Add(pDepthUnitSelect, 0, wxALIGN_TOP | wxALL, border_size);


    itemNotebook4->AddPage(ps57Ctl, _T("Vector Charts"));


        //  Create "AIS" panel

    itemPanelAIS = new wxPanel( itemNotebook4, ID_PANELAIS, wxDefaultPosition, wxDefaultSize,
                              wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer6AIS = new wxBoxSizer(wxVERTICAL);
    itemPanelAIS->SetSizer(itemBoxSizer6AIS);

    itemNotebook4->AddPage(itemPanelAIS, _T("AIS"));

   //      General
    wxStaticBox* itemStaticBoxAISGeneral = new wxStaticBox(itemPanelAIS, wxID_ANY, _T("AIS General"));
    wxStaticBoxSizer* itemStaticBoxSizerAISGeneral= new wxStaticBoxSizer(itemStaticBoxAISGeneral, wxVERTICAL);
    itemBoxSizer6AIS->Add(itemStaticBoxSizerAISGeneral, 0, wxTOP|wxALL|wxEXPAND, border_size);

    //    Add AIS Data Input controls
    wxStaticBox* itemAISStaticBox = new wxStaticBox(itemPanelAIS, wxID_ANY, _T("AIS Data Port"));
    wxStaticBoxSizer* itemAISStaticBoxSizer = new wxStaticBoxSizer(itemAISStaticBox, wxVERTICAL);
    itemStaticBoxSizerAISGeneral->Add(itemAISStaticBoxSizer, 0, wxEXPAND|wxALL, 4);

    m_itemAISListBox = new wxComboBox(itemPanelAIS, ID_CHOICE_AIS);
    m_itemAISListBox->Append( _T("None"));

      //    Fill in the listbox with all detected serial ports
    for (iPortIndex=0 ; iPortIndex < m_pSerialArray->GetCount() ; iPortIndex++)
          m_itemAISListBox->Append( m_pSerialArray->Item(iPortIndex) );


    if(pAIS_Port->Upper().Contains(_T("SERIAL")))
    {
          wxString ais_com = pAIS_Port->Mid(7);
          sidx = m_itemAISListBox->FindString(ais_com);
    }
    else if(pAIS_Port->Upper().Contains(_T("NONE")))
          sidx = 0;
    else
          sidx = 0;                                 // malformed selection


    if(sidx ==  wxNOT_FOUND)                  // user specified in ComboBox
    {
          wxString nport = pAIS_Port->AfterFirst(':');
          m_itemAISListBox->Append( nport );
          sidx = m_itemAISListBox->FindString(nport);
    }

    m_itemAISListBox->SetSelection(sidx);

    itemAISStaticBoxSizer->Add(m_itemAISListBox, 0, wxEXPAND|wxALL, border_size);

    //      CPA Box
    wxStaticBox* itemStaticBoxCPA = new wxStaticBox(itemPanelAIS, wxID_ANY, _T("CPA Calculation"));
    wxStaticBoxSizer* itemStaticBoxSizerCPA= new wxStaticBoxSizer(itemStaticBoxCPA, wxVERTICAL);
    itemBoxSizer6AIS->Add(itemStaticBoxSizerCPA, 0, wxALL|wxEXPAND, border_size);

    wxFlexGridSizer *pCPAGrid = new wxFlexGridSizer(2);
    pCPAGrid->AddGrowableCol(1);
    itemStaticBoxSizerCPA->Add(pCPAGrid, 0, wxALL|wxEXPAND, border_size);

    m_pCheck_CPA_Max = new wxCheckBox( itemPanelAIS, -1, _T("No CPA Calculation if target range is greater than (NMi):"));
    pCPAGrid->Add(m_pCheck_CPA_Max, 0, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_CPA_Max = new wxTextCtrl(itemPanelAIS, -1);
    pCPAGrid->Add(m_pText_CPA_Max, 0, wxALIGN_RIGHT, group_item_spacing);

    m_pCheck_CPA_Warn = new wxCheckBox( itemPanelAIS, -1, _T("Warn if CPA less than (NMi):"));
    pCPAGrid->Add(m_pCheck_CPA_Warn, 0, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_CPA_Warn = new wxTextCtrl(itemPanelAIS, -1, _T(""), wxDefaultPosition, wxSize(-1, -1));
    pCPAGrid->Add(m_pText_CPA_Warn, 0, wxALIGN_RIGHT, 2);

    m_pCheck_CPA_WarnT = new wxCheckBox( itemPanelAIS, -1, _T("  ..And TCPA is less than (Minutes):"));
    pCPAGrid->Add(m_pCheck_CPA_WarnT, 0, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_CPA_WarnT = new wxTextCtrl(itemPanelAIS, -1);
    pCPAGrid->Add(m_pText_CPA_WarnT, 0, wxALIGN_RIGHT, group_item_spacing);

   //      Lost Targets
    wxStaticBox* itemStaticBoxLostTargets = new wxStaticBox(itemPanelAIS, wxID_ANY, _T("Lost Targets"));
    wxStaticBoxSizer* itemStaticBoxSizerLostTargets= new wxStaticBoxSizer(itemStaticBoxLostTargets, wxVERTICAL);
    itemBoxSizer6AIS->Add(itemStaticBoxSizerLostTargets, 0, wxTOP|wxALL|wxEXPAND, border_size);

    wxFlexGridSizer *pLostGrid = new wxFlexGridSizer(2);
    pLostGrid->AddGrowableCol(1);
    itemStaticBoxSizerLostTargets->Add(pLostGrid, 0, wxALL|wxEXPAND, border_size);

    m_pCheck_Mark_Lost = new wxCheckBox( itemPanelAIS, -1, _T("Mark targets as lost after (Minutes:):"));
    pLostGrid->Add(m_pCheck_Mark_Lost, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_Mark_Lost = new wxTextCtrl(itemPanelAIS, -1);
    pLostGrid->Add(m_pText_Mark_Lost, 1, wxALIGN_RIGHT, group_item_spacing);

    m_pCheck_Remove_Lost = new wxCheckBox( itemPanelAIS, -1, _T("Remove lost targets after (Minutes:):"));
    pLostGrid->Add(m_pCheck_Remove_Lost, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_Remove_Lost = new wxTextCtrl(itemPanelAIS, -1);
    pLostGrid->Add(m_pText_Remove_Lost, 1, wxALIGN_RIGHT, group_item_spacing);

   //      Display
    wxStaticBox* itemStaticBoxDisplay = new wxStaticBox(itemPanelAIS, wxID_ANY, _T("Display"));
    wxStaticBoxSizer* itemStaticBoxSizerDisplay= new wxStaticBoxSizer(itemStaticBoxDisplay, wxVERTICAL);
    itemBoxSizer6AIS->Add(itemStaticBoxSizerDisplay, 0, wxTOP|wxALL|wxEXPAND, border_size);

    wxFlexGridSizer *pDisplayGrid = new wxFlexGridSizer(2);
    pDisplayGrid->AddGrowableCol(1);
    itemStaticBoxSizerDisplay->Add(pDisplayGrid, 0, wxALL|wxEXPAND, border_size);

    m_pCheck_Show_COG = new wxCheckBox( itemPanelAIS, -1, _T("Show target COG arrows"));
    pDisplayGrid->Add(m_pCheck_Show_COG, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    wxStaticText *pStatic_Dummy1 = new wxStaticText( itemPanelAIS, -1, _T(""));
    pDisplayGrid->Add(pStatic_Dummy1, 1, wxALIGN_RIGHT|wxALL, group_item_spacing);

    wxStaticText *pStatic_COG_Predictor = new wxStaticText( itemPanelAIS, -1, _T("      COG arrow predictor length (Minutes):"));
    pDisplayGrid->Add(pStatic_COG_Predictor, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_COG_Predictor = new wxTextCtrl(itemPanelAIS, -1);
    pDisplayGrid->Add(m_pText_COG_Predictor, 1, wxALIGN_RIGHT, group_item_spacing);

#if 0
    m_pCheck_Show_Tracks = new wxCheckBox( itemPanelAIS, -1, _T("Show target tracks"));
    pDisplayGrid->Add(m_pCheck_Show_Tracks, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    wxStaticText *pStatic_Dummy2 = new wxStaticText( itemPanelAIS, -1, _T(""));
    pDisplayGrid->Add(pStatic_Dummy2, 1, wxALIGN_RIGHT|wxALL, group_item_spacing);

    wxStaticText *pStatic_Track_Length = new wxStaticText( itemPanelAIS, -1, _T("      Target track length (Minutes):"));
    pDisplayGrid->Add(pStatic_Track_Length, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_Track_Length = new wxTextCtrl(itemPanelAIS, -1);
                                                                            pDisplayGrid->Add(m_pText_Track_Length, 1, wxALIGN_RIGHT, group_item_spacing);
#endif

    m_pCheck_Show_Moored = new wxCheckBox( itemPanelAIS, -1, _T("Supress anchored/moored targets"));
    pDisplayGrid->Add(m_pCheck_Show_Moored, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    wxStaticText *pStatic_Dummy3 = new wxStaticText( itemPanelAIS, -1, _T(""));
    pDisplayGrid->Add(pStatic_Dummy3, 1, wxALIGN_RIGHT|wxALL, group_item_spacing);

    wxStaticText *pStatic_Moored_Speed = new wxStaticText( itemPanelAIS, -1, _T("      Max moored target speed (Kts.):"));
    pDisplayGrid->Add(pStatic_Moored_Speed, 1, wxALIGN_LEFT|wxALL, group_item_spacing);

    m_pText_Moored_Speed = new wxTextCtrl(itemPanelAIS, -1);
    pDisplayGrid->Add(m_pText_Moored_Speed, 1, wxALIGN_RIGHT, group_item_spacing);

        //      Alert Box
    wxStaticBox* itemStaticBoxAlert = new wxStaticBox(itemPanelAIS, wxID_ANY, _T("CPA/TCPA Alerts"));
    wxStaticBoxSizer* itemStaticBoxSizerAlert= new wxStaticBoxSizer(itemStaticBoxAlert, wxVERTICAL);
    itemBoxSizer6AIS->Add(itemStaticBoxSizerAlert, 0, wxALL|wxEXPAND, border_size);

    wxFlexGridSizer *pAlertGrid = new wxFlexGridSizer(2);
    pAlertGrid->AddGrowableCol(1);
    itemStaticBoxSizerAlert->Add(pAlertGrid, 0, wxALL|wxEXPAND, border_size);

    m_pCheck_AlertDialog = new wxCheckBox( itemPanelAIS, ID_AISALERTDIALOG, _T("Show CPA/TCPA Alert Dialog"));
    pAlertGrid->Add(m_pCheck_AlertDialog, 0, wxALIGN_LEFT|wxALL, group_item_spacing);

    wxButton *m_SelSound = new wxButton( itemPanelAIS, ID_AISALERTSELECTSOUND, _("Select Alert Sound"), wxDefaultPosition, small_button_size, 0 );
    pAlertGrid->Add(m_SelSound, 0, wxALIGN_RIGHT|wxALL, group_item_spacing);

    m_pCheck_AlertAudio = new wxCheckBox( itemPanelAIS, ID_AISALERTAUDIO, _T("Play Sound on CPA/TCPA Alerts"));
    pAlertGrid->Add(m_pCheck_AlertAudio, 0, wxALIGN_LEFT|wxALL, group_item_spacing);

    wxButton *m_pPlay_Sound = new wxButton( itemPanelAIS, ID_AISALERTTESTSOUND, _T("Test Alert Sound"), wxDefaultPosition, small_button_size, 0);
    pAlertGrid->Add(m_pPlay_Sound, 0, wxALIGN_RIGHT|wxALL, group_item_spacing);

    m_pCheck_Alert_Moored = new wxCheckBox( itemPanelAIS, -1, _T("Supress Alerts for anchored/moored targets"));
    pAlertGrid->Add(m_pCheck_Alert_Moored, 1, wxALIGN_LEFT|wxALL, group_item_spacing);




    //      Build Fonts panel
    itemPanelFont = new wxPanel( itemNotebook4, ID_PANELFONT, wxDefaultPosition, wxDefaultSize,
                                          wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizerFontPanel = new wxBoxSizer(wxVERTICAL);
    itemPanelFont->SetSizer(itemBoxSizerFontPanel);

    wxStaticBox* itemFontStaticBox = new wxStaticBox(itemPanelFont, wxID_ANY, _T("Font Options"));
    wxStaticBoxSizer* itemFontStaticBoxSizer = new wxStaticBoxSizer(itemFontStaticBox, wxVERTICAL);
    itemBoxSizerFontPanel->Add(itemFontStaticBoxSizer, 0, wxEXPAND|wxALL, border_size);

    wxStaticBox* itemFontElementStaticBox = new wxStaticBox(itemPanelFont, wxID_ANY, _T("Text Element"));
    wxStaticBoxSizer* itemFontElementStaticBoxSizer = new wxStaticBoxSizer(itemFontElementStaticBox, wxVERTICAL);
    itemFontStaticBoxSizer->Add(itemFontElementStaticBoxSizer, 0, wxEXPAND|wxALL, border_size);

    m_itemFontElementListBox = new wxComboBox(itemPanelFont, ID_CHOICE_FONTELEMENT);

    int nFonts = pFontMgr->GetNumFonts();
    for( int it = 0 ; it < nFonts ; it++)
    {
          wxString *t = pFontMgr->GetDialogString(it);
          m_itemFontElementListBox->Append( *t );
    }

    if(nFonts)
          m_itemFontElementListBox->SetSelection(0);

    itemFontElementStaticBoxSizer->Add(m_itemFontElementListBox, 0, wxEXPAND|wxALL, border_size);

    wxButton* itemFontChooseButton = new wxButton( itemPanelFont, ID_BUTTONFONTCHOOSE, _T("Choose Font..."),
                wxDefaultPosition, wxDefaultSize, 0 );
    itemFontElementStaticBoxSizer->Add(itemFontChooseButton, 0, wxEXPAND|wxALL, border_size);


    itemNotebook4->AddPage(itemPanelFont, _("Fonts"));

    //      Build GRIB. Page

    itemPanelGRIB = new wxPanel( itemNotebook4, ID_PANELGRIB, wxDefaultPosition, wxDefaultSize,
                                     wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizerGRIBPanel = new wxBoxSizer(wxVERTICAL);
    itemPanelGRIB->SetSizer(itemBoxSizerGRIBPanel);

    itemNotebook4->AddPage(itemPanelGRIB, _("GRIB"));

    //  Grib toolbox icon checkbox
    wxStaticBox* itemStaticBoxSizerGRIBStatic = new wxStaticBox(itemPanelGRIB, wxID_ANY, _("GRIB"));
    wxStaticBoxSizer* itemStaticBoxSizerGRIB = new wxStaticBoxSizer(itemStaticBoxSizerGRIBStatic, wxVERTICAL);
    itemBoxSizerGRIBPanel->Add(itemStaticBoxSizerGRIB, 0, wxGROW|wxALL, border_size);
    pGRIBShowIcon = new wxCheckBox( itemPanelGRIB, ID_GRIBCHECKBOX, _("Show GRIB icon"), wxDefaultPosition,
                                    wxSize(-1, -1), 0 );
    itemStaticBoxSizerGRIB->Add(pGRIBShowIcon, 1, wxALIGN_LEFT|wxALL, border_size);



    //      Build Etc. Page

    itemPanelAdvanced = new wxPanel( itemNotebook4, ID_PANELADVANCED, wxDefaultPosition, wxDefaultSize,
                                     wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizerAdvancedPanel = new wxBoxSizer(wxVERTICAL);
    itemPanelAdvanced->SetSizer(itemBoxSizerAdvancedPanel);

    itemNotebook4->AddPage(itemPanelAdvanced, _("Etc."));

    //  GPX import/export checkbox
    wxStaticBox* itemStaticBoxSizerGPXStatic = new wxStaticBox(itemPanelAdvanced, wxID_ANY, _("GPX"));
    wxStaticBoxSizer* itemStaticBoxSizerGPX = new wxStaticBoxSizer(itemStaticBoxSizerGPXStatic, wxVERTICAL);
    itemBoxSizerAdvancedPanel->Add(itemStaticBoxSizerGPX, 0, wxGROW|wxALL, border_size);
    pGPXShowIcons = new wxCheckBox( itemPanelAdvanced, ID_GPXCHECKBOX, _("Show GPX icons"), wxDefaultPosition,
                                    wxSize(-1, -1), 0 );
    pGPXShowIcons->SetValue(FALSE);
    itemStaticBoxSizerGPX->Add(pGPXShowIcons, 1, wxALIGN_LEFT|wxALL, border_size);

    //  Tracks
    wxStaticBox* itemStaticBoxSizerTrackStatic = new wxStaticBox(itemPanelAdvanced, wxID_ANY, _("Tracks"));
    wxStaticBoxSizer* itemStaticBoxSizerTrack = new wxStaticBoxSizer(itemStaticBoxSizerTrackStatic, wxVERTICAL);
    itemBoxSizerAdvancedPanel->Add(itemStaticBoxSizerTrack, 0, wxGROW|wxALL, border_size);
    pTrackShowIcon = new wxCheckBox( itemPanelAdvanced, ID_TRACKCHECKBOX, _("Show Track icon"), wxDefaultPosition,
                                    wxSize(-1, -1), 0 );
    itemStaticBoxSizerTrack->Add(pTrackShowIcon, 1, wxALIGN_LEFT|wxALL, border_size);


///////////////
    wxFlexGridSizer *pTrackGrid = new wxFlexGridSizer(2);
    pTrackGrid->AddGrowableCol(1);
    itemStaticBoxSizerTrack->Add(pTrackGrid, 0, wxALL|wxEXPAND, border_size);

    m_pCheck_Trackpoint_time = new wxRadioButton( itemPanelAdvanced, -1, _T("Place Trackpoints at time interval (Seconds):"),
                wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    pTrackGrid->Add(m_pCheck_Trackpoint_time, 0, wxALIGN_LEFT|wxALL, 2);

    m_pText_TP_Secs = new wxTextCtrl(itemPanelAdvanced, -1);
    pTrackGrid->Add(m_pText_TP_Secs, 0, wxALIGN_RIGHT, 2);

    m_pCheck_Trackpoint_distance = new wxRadioButton( itemPanelAdvanced, -1, _T("Place Trackpoints at distance interval (NMi):"));
    pTrackGrid->Add(m_pCheck_Trackpoint_distance, 0, wxALIGN_LEFT|wxALL, 2);

    m_pText_TP_Dist = new wxTextCtrl(itemPanelAdvanced, -1, _T(""), wxDefaultPosition, wxSize(-1, -1));
    pTrackGrid->Add(m_pText_TP_Dist, 0, wxALIGN_RIGHT, 2);

    // Radar rings
    wxStaticBox* itemStaticBoxSizerRadarRingsStatic = new wxStaticBox(itemPanelAdvanced, wxID_ANY, _("Radar rings"));
    wxStaticBoxSizer* itemStaticBoxSizerRadarRings = new wxStaticBoxSizer(itemStaticBoxSizerRadarRingsStatic, wxVERTICAL);
    itemBoxSizerAdvancedPanel->Add(itemStaticBoxSizerRadarRings, 0, wxGROW|wxALL, border_size);
    pNavAidShowRadarRings = new wxCheckBox( itemPanelAdvanced, ID_GPXCHECKBOX, _("Show radar rings"), wxDefaultPosition,
                                            wxSize(-1, -1), 0 );
    pNavAidShowRadarRings->SetValue(FALSE);
    itemStaticBoxSizerRadarRings->Add(pNavAidShowRadarRings, 1, wxALIGN_LEFT|wxALL, border_size);

    wxStaticText* itemStaticTextNumberRadarRings = new wxStaticText( itemPanelAdvanced, wxID_STATIC, _("Number of radar rings shown"));
    itemStaticBoxSizerRadarRings->Add(itemStaticTextNumberRadarRings, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, border_size);

    pNavAidRadarRingsNumberVisible = new wxTextCtrl( itemPanelAdvanced, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(100, -1), 0 );
    itemStaticBoxSizerRadarRings->Add(pNavAidRadarRingsNumberVisible, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, border_size);

    wxStaticText* itemStaticTextStepRadarRings = new wxStaticText( itemPanelAdvanced, wxID_STATIC, _("Distance between rings"));
    itemStaticBoxSizerRadarRings->Add(itemStaticTextStepRadarRings, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, border_size);

    pNavAidRadarRingsStep = new wxTextCtrl( itemPanelAdvanced, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(100, -1), 0 );
    itemStaticBoxSizerRadarRings->Add(pNavAidRadarRingsStep, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, border_size);

    wxString pDistUnitsStrings[] = {
          _T("&Nautical miles"),
             _T("&Kilometers"),
    };
    m_itemNavAidRadarRingsStepUnitsRadioBox = new wxRadioBox( itemPanelAdvanced, ID_RADIOBOX, _T("Units"), wxDefaultPosition, wxDefaultSize,
                2, pDistUnitsStrings, 1, wxRA_SPECIFY_COLS );
    itemStaticBoxSizerRadarRings->Add(m_itemNavAidRadarRingsStepUnitsRadioBox, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM, border_size);

    //  Disable/enable dragging waypoints while mark properties invisible
    wxStaticBox* itemStaticBoxSizerWptDraggingStatic = new wxStaticBox(itemPanelAdvanced, wxID_ANY, _("Waypoint Locking"));
    wxStaticBoxSizer* itemStaticBoxSizerWptDragging = new wxStaticBoxSizer(itemStaticBoxSizerWptDraggingStatic, wxVERTICAL);
    itemBoxSizerAdvancedPanel->Add(itemStaticBoxSizerWptDragging, 0, wxGROW|wxALL, border_size);
    pWayPointPreventDragging = new wxCheckBox( itemPanelAdvanced, ID_DRAGGINGCHECKBOX, _("Lock all waypoints unless a waypoint property dialog is visible"),
                                               wxDefaultPosition, wxSize(-1, -1), 0 );
    pWayPointPreventDragging->SetValue(FALSE);
    itemStaticBoxSizerWptDragging->Add(pWayPointPreventDragging, 1, wxALIGN_LEFT|wxALL, border_size);


    //  Various GUI opetions
    wxStaticBox* itemStaticBoxSizerGUIOptionsStatic = new wxStaticBox(itemPanelAdvanced, wxID_ANY, _("GUI Options"));
    wxStaticBoxSizer* itemStaticBoxSizerGUIOption = new wxStaticBoxSizer(itemStaticBoxSizerGUIOptionsStatic, wxVERTICAL);
    itemBoxSizerAdvancedPanel->Add(itemStaticBoxSizerGUIOption, 0, wxGROW|wxALL, border_size);
    pEnableZoomToCursor = new wxCheckBox( itemPanelAdvanced, ID_DRAGGINGCHECKBOX, _("Enable Wheel-Zoom-to-Cursor"),
                                               wxDefaultPosition, wxSize(-1, -1), 0 );
    pEnableZoomToCursor->SetValue(FALSE);
    itemStaticBoxSizerGUIOption->Add(pEnableZoomToCursor, 1, wxALIGN_LEFT|wxALL, border_size);

    //  Printing checkbox
/*    wxStaticBox* itemStaticBoxSizerPrintStatic = new wxStaticBox(itemPanel5, wxID_ANY, _("Printing"));
    wxStaticBoxSizer* itemStaticBoxSizerPrint = new wxStaticBoxSizer(itemStaticBoxSizerPrintStatic, wxVERTICAL);
    itemBoxSizer6->Add(itemStaticBoxSizerPrint, 0, wxGROW|wxALL, border_size);
    pPrintShowIcon = new wxCheckBox( itemPanel5, ID_DEBUGCHECKBOX1, _("Show Printing Icon"), wxDefaultPosition,
    wxSize(-1, -1), 0 );
    pPrintShowIcon->SetValue(FALSE);
    itemStaticBoxSizerPrint->Add(pPrintShowIcon, 1, wxALIGN_LEFT|wxALL, border_size);

    // Chart Display Options Box
    wxStaticBox* itemStaticBoxSizerCDOStatic = new wxStaticBox(itemPanel5, wxID_ANY, _("Chart Display Options"));
    wxStaticBoxSizer* itemStaticBoxSizerCDO = new wxStaticBoxSizer(itemStaticBoxSizerCDOStatic, wxVERTICAL);
    itemBoxSizer6->Add(itemStaticBoxSizerCDO, 0, wxGROW|wxALL, border_size);

    //  Chart Outlines checkbox
    pCDOOutlines = new wxCheckBox( itemPanel5, ID_DEBUGCHECKBOX1, _("Show Chart Outlines"), wxDefaultPosition,
    wxSize(-1, -1), 0 );
    pCDOOutlines->SetValue(FALSE);
    itemStaticBoxSizerCDO->Add(pCDOOutlines, 1, wxALIGN_LEFT|wxALL, border_size);


    //  Depth Unit checkbox
    pSDepthUnits = new wxCheckBox( itemPanel5, ID_SHOWDEPTHUNITSBOX1, _("Show DepthUnits"), wxDefaultPosition,
    wxSize(-1, -1), 0 );
    pSDepthUnits->SetValue(FALSE);
    itemStaticBoxSizerCDO->Add(pSDepthUnits, 1, wxALIGN_LEFT|wxALL, border_size);
*/



    // toh, 2009.02.14; end


    pSettingsCB1 = pDebugShowStat;

    SetColorScheme((ColorScheme)0);

}

void options::SetColorScheme(ColorScheme cs)
{
      SetBackgroundColour(GetGlobalColor(_T("DILG0")));

      wxColour back_color = GetGlobalColor(_T("DILG2"));
      wxColour text_color = GetGlobalColor(_T("DILG3"));

      SetControlColors(itemNotebook4, cs);
      SetControlColors(itemPanel5, cs);
      SetControlColors(itemPanel9, cs);
      SetControlColors(ps57Ctl, cs);
      SetControlColors(itemPanelFont, cs);
      SetControlColors(pDirCtl, cs);
      SetControlColors(pSelCtl, cs);
      SetControlColors(pTextCtl, cs);

      SetControlColors(m_CancelButton, cs);
      SetControlColors(m_OKButton, cs);

}


void options::SetInitialSettings()
{
      wxString s;
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

      if(m_pConfig)
            pSettingsCB1->SetValue(m_pConfig->m_bShowDebugWindows);

      pPrintShowIcon->SetValue(g_bShowPrintIcon);
      pCDOOutlines->SetValue(g_bShowOutlines);
      pSDepthUnits->SetValue(g_bShowDepthUnits);
      pAutoAnchorMark->SetValue(g_bAutoAnchorMark);

      pGPXShowIcons->SetValue(g_bShowGPXIcons);             // toh, 2009.02.14
      pNavAidShowRadarRings->SetValue(g_bNavAidShowRadarRings);   // toh, 2009.02.24
      wxString buf;
      buf.Printf(_T("%d"),g_iNavAidRadarRingsNumberVisible);
      pNavAidRadarRingsNumberVisible->SetValue(buf);  // toh, 2009.02.24
      buf.Printf(_T("%.3f"),g_fNavAidRadarRingsStep);
      pNavAidRadarRingsStep->SetValue(buf);     // toh, 2009.02.24
      m_itemNavAidRadarRingsStepUnitsRadioBox->SetSelection(g_pNavAidRadarRingsStepUnits);      // toh, 2009.02.24
      pWayPointPreventDragging->SetValue(g_bWayPointPreventDragging);   // toh, 2009.02.24

      pEnableZoomToCursor->SetValue(g_bEnableZoomToCursor);

      pTrackShowIcon->SetValue(g_bShowTrackIcon);

      s.Printf(_T("%4.0f"),g_TrackIntervalSeconds);
      m_pText_TP_Secs->SetValue(s);
      s.Printf(_T("%5.2f"),g_TrackDeltaDistance);
      m_pText_TP_Dist->SetValue(s);

      m_pCheck_Trackpoint_time->SetValue(g_bTrackTime);
      m_pCheck_Trackpoint_distance->SetValue(g_bTrackDistance);

      pGRIBShowIcon->SetValue(g_bShowGRIBIcon);


//    AIS Parameters

      //      CPA Box
      m_pCheck_CPA_Max->SetValue(g_bCPAMax);

      s.Printf(_T("%4.1f"),g_CPAMax_NM);
      m_pText_CPA_Max->SetValue(s);

      m_pCheck_CPA_Warn->SetValue(g_bCPAWarn);

      s.Printf(_T("%4.1f"),g_CPAWarn_NM);
      m_pText_CPA_Warn->SetValue(s);

      m_pCheck_CPA_WarnT->SetValue(g_bTCPA_Max);

      s.Printf(_T("%4.0f"),g_TCPA_Max);
      m_pText_CPA_WarnT->SetValue(s);

   //      Lost Targets
      m_pCheck_Mark_Lost->SetValue(g_bMarkLost);

      s.Printf(_T("%4.0f"),g_MarkLost_Mins);
      m_pText_Mark_Lost->SetValue(s);

      m_pCheck_Remove_Lost->SetValue(g_bRemoveLost);

      s.Printf(_T("%4.0f"),g_RemoveLost_Mins);
      m_pText_Remove_Lost->SetValue(s);

   //      Display
      m_pCheck_Show_COG->SetValue(g_bShowCOG);

      s.Printf(_T("%4.0f"),g_ShowCOG_Mins);
      m_pText_COG_Predictor->SetValue(s);

#if 0
      m_pCheck_Show_Tracks->SetValue(g_bShowTracks);

      s.Printf(_T("%4.0f"),g_ShowTracks_Mins);
      m_pText_Track_Length->SetValue(s);
#endif

      m_pCheck_Show_Moored->SetValue(!g_bShowMoored);

      s.Printf(_T("%4.1f"),g_ShowMoored_Kts);
      m_pText_Moored_Speed->SetValue(s);

         //      Alerts
      m_pCheck_AlertDialog->SetValue(g_bAIS_CPA_Alert);
      m_pCheck_AlertAudio->SetValue(g_bAIS_CPA_Alert_Audio);
      m_pCheck_Alert_Moored->SetValue(g_bAIS_CPA_Alert_Suppress_Moored);

      m_pSlider_CM93_Zoom->SetValue(g_cm93_zoom_factor);


#ifdef USE_S57
//    S52 Primary Filters
      ps57CtlListBox->Clear();

      for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
      {
            OBJLElement *pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));

            ps57CtlListBox->Append(wxString(pOLE->OBJLName, wxConvUTF8));
            ps57CtlListBox->Check(ps57CtlListBox->GetCount()-1, !(pOLE->nViz == 0));
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


      ps57CtlListBox->Enable(MARINERS_STANDARD == ps52plib->m_nDisplayCategory);
      itemButtonClearList->Enable(MARINERS_STANDARD == ps52plib->m_nDisplayCategory);
      itemButtonSelectList->Enable(MARINERS_STANDARD == ps52plib->m_nDisplayCategory);

      //  Other Display Filters
      pCheck_SOUNDG->SetValue(ps52plib->m_bShowSoundg);
      pCheck_META->SetValue(ps52plib->m_bShowMeta);
      pCheck_SHOWIMPTEXT->SetValue(ps52plib->m_bShowS57ImportantTextOnly);
      pCheck_SCAMIN->SetValue(ps52plib->m_bUseSCAMIN);
      pCheck_ATONTEXT->SetValue(ps52plib->m_bShowAtonText);
      pCheck_LDISTEXT->SetValue(ps52plib->m_bShowLdisText);
      pCheck_DECLTEXT->SetValue(ps52plib->m_bDeClutterText);

     // Chart Display Style
      if(ps52plib->m_nSymbolStyle == PAPER_CHART)
          pPointStyle->SetSelection(0);
      else
          pPointStyle->SetSelection(1);

      if(ps52plib->m_nBoundaryStyle == PLAIN_BOUNDARIES)
          pBoundStyle->SetSelection(0);
      else
          pBoundStyle->SetSelection(1);

      if(S52_getMarinerParam(S52_MAR_TWO_SHADES) == 1.0)
            p24Color->SetSelection(0);
      else
            p24Color->SetSelection(1);

      wxString s;
      s.Printf(_T("%6.2f"),S52_getMarinerParam(S52_MAR_SAFETY_CONTOUR));
      m_SafetyCtl->SetValue(s);

      s.Printf(_T("%6.2f"),S52_getMarinerParam(S52_MAR_SHALLOW_CONTOUR));
      m_ShallowCtl->SetValue(s);

      s.Printf(_T("%6.2f"),S52_getMarinerParam(S52_MAR_DEEP_CONTOUR));
      m_DeepCtl->SetValue(s);

      pDepthUnitSelect->SetSelection(ps52plib->m_nDepthUnitDisplay);
    }
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


void options::OnDirctrlSelChanged( wxTreeEvent& event )
{
    if(pDirCtl)
      {
            wxString SelDir;
            SelDir = pDirCtl->GetPath();
            if(pSelCtl)
            {
                pSelCtl->Clear();
                pSelCtl->AppendText(SelDir);
            }
      }

      event.Skip();
}


bool options::ShowToolTips()
{
    return TRUE;
}

void options::OnButtonaddClick( wxCommandEvent& event )
{
      wxString SelDir;
      SelDir = pDirCtl->GetPath();

      pTextCtl->AppendText(SelDir);
      pTextCtl->AppendText(_T("\n"));

      event.Skip();
}



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
                        {
                              //    This is a fix for OSX, which appends EOL to results of GetLineText()
                              while (( dirname.Last() == wxChar(_T('\n')) ) || ( dirname.Last()  == wxChar(_T('\r')) ))
                                   dirname.RemoveLast() ;

                              m_pWorkDirList->Add(dirname);
                        }
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
    g_bShowOutlines = pCDOOutlines->GetValue();
    g_bShowDepthUnits = pSDepthUnits->GetValue();
    g_bAutoAnchorMark = pAutoAnchorMark->GetValue();

    g_bShowGPXIcons = pGPXShowIcons->GetValue();        // toh, 2009.02.14
    g_bNavAidShowRadarRings = pNavAidShowRadarRings->GetValue();  // toh, 2009.02.24
    wxString buf = pNavAidRadarRingsNumberVisible->GetValue();
    g_iNavAidRadarRingsNumberVisible = atoi(buf.mb_str());  // toh, 2009.02.24
    g_fNavAidRadarRingsStep = atof(pNavAidRadarRingsStep->GetValue().mb_str());     // toh, 2009.02.24
    g_pNavAidRadarRingsStepUnits = m_itemNavAidRadarRingsStepUnitsRadioBox->GetSelection();     // toh, 2009.02.24
    g_bWayPointPreventDragging = pWayPointPreventDragging->GetValue();  // toh, 2009.02.24

    g_bShowTrackIcon = pTrackShowIcon->GetValue();
    m_pText_TP_Secs->GetValue().ToDouble(&g_TrackIntervalSeconds);
    m_pText_TP_Dist->GetValue().ToDouble(&g_TrackDeltaDistance);
    g_bTrackTime = m_pCheck_Trackpoint_time->GetValue();
    g_bTrackDistance = m_pCheck_Trackpoint_distance->GetValue();



    g_bEnableZoomToCursor = pEnableZoomToCursor->GetValue();

    //    AIS Parameters
      //      CPA Box
    g_bCPAMax = m_pCheck_CPA_Max->GetValue();
    m_pText_CPA_Max->GetValue().ToDouble(&g_CPAMax_NM);
    g_bCPAWarn = m_pCheck_CPA_Warn->GetValue();
    m_pText_CPA_Warn->GetValue().ToDouble(&g_CPAWarn_NM);
    g_bTCPA_Max = m_pCheck_CPA_WarnT->GetValue();
    m_pText_CPA_WarnT->GetValue().ToDouble(&g_TCPA_Max);

   //      Lost Targets
    g_bMarkLost = m_pCheck_Mark_Lost->GetValue();
    m_pText_Mark_Lost->GetValue().ToDouble(&g_MarkLost_Mins);
    g_bRemoveLost = m_pCheck_Remove_Lost->GetValue();
    m_pText_Remove_Lost->GetValue().ToDouble(&g_RemoveLost_Mins);

   //      Display
    g_bShowCOG = m_pCheck_Show_COG->GetValue();
    m_pText_COG_Predictor->GetValue().ToDouble(&g_ShowCOG_Mins);
#if 0
    g_bShowTracks = m_pCheck_Show_Tracks->GetValue();
    m_pText_Track_Length->GetValue().ToDouble(&g_ShowTracks_Mins);
#endif
    g_bShowMoored = !m_pCheck_Show_Moored->GetValue();
    m_pText_Moored_Speed->GetValue().ToDouble(&g_ShowMoored_Kts);

    //      Alert
    g_bAIS_CPA_Alert = m_pCheck_AlertDialog->GetValue();
    g_bAIS_CPA_Alert_Audio = m_pCheck_AlertAudio->GetValue();
    g_bAIS_CPA_Alert_Suppress_Moored = m_pCheck_Alert_Moored->GetValue();


//    NMEA Options

// Source
//      wxString sel(m_itemNMEAListBox->GetStringSelection());
      wxString sel(m_itemNMEAListBox->GetValue());

      if(sel.Contains(_T("COM")))
          sel.Prepend(_T("Serial:"));

      else if(sel.Contains(_T("/dev")))
          sel.Prepend(_T("Serial:"));

      else if(sel.Contains(_T("AIS")))
            sel.Prepend(_T("Serial:"));

      else if(sel.Contains(_T("GPSD")))
      {
            sel.Empty();
            sel.Append(_T("GPSD:"));
            sel.Append(m_itemNMEA_TCPIP_Source->GetLineText(0));
      }
    *pNMEADataSource = sel;

      //    If the selection is anything other than "GARMIN",
      //    then disable semipermanently the option to select GARMIN in future.
      //    Note if GARMIN device is found in the future, the option will be
      //    re-enabled.
      if(!sel.Contains(_T("GARMIN")))
            g_bGarminPersistance = false;

// AP Output
    wxString selp(m_itemNMEAAutoListBox->GetStringSelection());
    if(selp.Contains(_T("COM")))
        selp.Prepend(_T("Serial:"));
    else if(selp.Contains(_T("/dev")))
        selp.Prepend(_T("Serial:"));
    *pNMEA_AP_Port = selp;

// AIS Input
//    wxString selais(m_itemAISListBox->GetStringSelection());
    wxString selais(m_itemAISListBox->GetValue());
    if(selais.Contains(_T("COM")))
        selais.Prepend(_T("Serial:"));
    else if(selais.Contains(_T("/dev")))
        selais.Prepend(_T("Serial:"));
    else if(selais.Contains(_T("fifo")))
          selais.Prepend(_T("Serial:"));
    *pAIS_Port = selais;

#ifdef USE_WIFI_CLIENT
// WiFi
    wxString WiFiSource;
    WiFiSource.Empty();
    WiFiSource.Append(_T("TCP/IP:"));
    WiFiSource.Append(m_itemWIFI_TCPIP_Source->GetLineText(0));
    *pWIFIServerName = WiFiSource;
#endif

    g_cm93_zoom_factor = m_pSlider_CM93_Zoom->GetValue();

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

            ps52plib->m_bShowSoundg =  pCheck_SOUNDG->GetValue();
            ps52plib->m_bShowMeta =    pCheck_META->GetValue();
            ps52plib->m_bShowS57ImportantTextOnly = pCheck_SHOWIMPTEXT->GetValue();
            ps52plib->m_bUseSCAMIN =   pCheck_SCAMIN->GetValue();
            ps52plib->m_bShowAtonText= pCheck_ATONTEXT->GetValue();
            ps52plib->m_bShowLdisText= pCheck_LDISTEXT->GetValue();
            ps52plib->m_bDeClutterText= pCheck_DECLTEXT->GetValue();


            if(0 == pPointStyle->GetSelection())
                ps52plib->m_nSymbolStyle = PAPER_CHART;
            else
                ps52plib->m_nSymbolStyle = SIMPLIFIED;

            if(0 == pBoundStyle->GetSelection())
                ps52plib->m_nBoundaryStyle = PLAIN_BOUNDARIES;
            else
                ps52plib->m_nBoundaryStyle = SYMBOLIZED_BOUNDARIES;

            if(0 == p24Color->GetSelection())
                  S52_setMarinerParam(S52_MAR_TWO_SHADES, 1.0);
            else
                  S52_setMarinerParam(S52_MAR_TWO_SHADES, 0.0);

            double dval;

            if((m_SafetyCtl->GetValue()).ToDouble(&dval))
            {
                  S52_setMarinerParam(S52_MAR_SAFETY_DEPTH, dval);            // controls sounding display
                  S52_setMarinerParam(S52_MAR_SAFETY_CONTOUR, dval);          // controls colour
            }

            if((m_ShallowCtl->GetValue()).ToDouble(&dval))
                  S52_setMarinerParam(S52_MAR_SHALLOW_CONTOUR, dval);

            if((m_DeepCtl->GetValue()).ToDouble(&dval))
                  S52_setMarinerParam(S52_MAR_DEEP_CONTOUR, dval);


            ps52plib->UpdateMarinerParams();

            ps52plib->m_nDepthUnitDisplay = pDepthUnitSelect->GetSelection();

      }
#endif

//      Capture and store the currently selected chart tree path
    if(pDirCtl != NULL)
    {
        wxString cur_path = pDirCtl->GetPath();
        pInit_Chart_Dir->Clear();
        pInit_Chart_Dir->Append(cur_path);
    }

    delete m_pSerialArray;


//    GRIB
    g_bShowGRIBIcon= pGRIBShowIcon->GetValue();


    //      Could be a lot smarter here
    EndModal(GENERIC_CHANGED | S52_CHANGED);


}


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


void options::OnDebugcheckbox1Click( wxCommandEvent& event )
{
    event.Skip();
}



void options::OnCancelClick( wxCommandEvent& event )
{
      EndModal(0);
}

void options::OnRadioboxSelected( wxCommandEvent& event )
{
    event.Skip();
}

void options::OnChooseFont( wxCommandEvent& event )
{
      wxString sel_text_element = m_itemFontElementListBox->GetStringSelection();

      wxFont *psfont;
      wxFontData font_data;

      wxFont *pif = pFontMgr->GetFont(sel_text_element);
      wxColour init_color = pFontMgr->GetFontColor(sel_text_element);

      wxFontData init_font_data;
      if(pif)
            init_font_data.SetInitialFont(*pif);
      init_font_data.SetColour(init_color);


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
            wxColor color = font_data.GetColour();
            pFontMgr->SetFont(sel_text_element, psfont, color);

            pParent->UpdateAllFonts();
      }

      event.Skip();
}


void options::OnPageChange(wxNotebookEvent& event)
{
      int i = event.GetSelection();

      //    User selected Chart Page?
      //    If so, build the "Charts" page variants
      //    Also, show a progress dialog, since getting the GenericTreeCtrl may be slow
      //    and the user needs feedback
      if(1 == i)                        // 1 is the index of "Charts" page
      {


          itemBoxSizer10->Clear(true);
          pSelCtl = NULL;
          pDirCtl = NULL;

          //    "Available" tree control and selection
          wxStaticBox* itemStaticBoxSizer11Static = new wxStaticBox(itemPanel9, wxID_ANY,
                  _("Available Chart Directories"));
          itemStaticBoxSizer11 = new wxStaticBoxSizer(itemStaticBoxSizer11Static, wxVERTICAL);
          itemBoxSizer10->Add(itemStaticBoxSizer11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);
          pDirCtl = new wxGenericDirCtrl( itemPanel9, ID_DIRCTRL, m_init_chart_dir, wxDefaultPosition,
                                          wxDefaultSize, 0, _T("All files (*.*)|*.*"), 0 );
          pDirCtl->SetMinSize(wxSize(-1, 160));
          itemStaticBoxSizer11->Add(pDirCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);


          pSelCtl = new wxTextCtrl( itemPanel9, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxSize(-1, -1), 0 );
          itemStaticBoxSizer11->Add(pSelCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

          wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
          itemStaticBoxSizer11->Add(itemBoxSizer14, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
          wxButton* itemButton15 = new wxButton( itemPanel9, ID_BUTTONADD, _("Add Selection"), wxDefaultPosition, wxDefaultSize, 0 );
          itemBoxSizer14->Add(itemButton15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


          //    "Active" list
          itemActiveChartStaticBox = new wxStaticBox(itemPanel9, wxID_ANY, _("Active Chart Directories"));
          wxStaticBoxSizer* itemStaticBoxSizer16 = new wxStaticBoxSizer(itemActiveChartStaticBox, wxVERTICAL);
          itemBoxSizer10->Add(itemStaticBoxSizer16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);


          int tc_flags = wxTE_MULTILINE;
          //    wxX11 has some trouble with wxTextCtrl....
          //    In this case, wxTE_DONTWRAP causes corruption of the control's parent data structures....
          //    So, dont do that...
#ifndef __WXX11__
          tc_flags |= wxTE_DONTWRAP;
#endif

          pTextCtl = new wxTextCtrl( itemPanel9, ID_TEXTCTRL, _T(""),
                                     wxDefaultPosition, wxSize(-1, -1), tc_flags  );
          pTextCtl->SetMinSize(wxSize(-1, 100));
          itemStaticBoxSizer16->Add(pTextCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5);

          wxButton* itemButton18 = new wxButton( itemPanel9, ID_BUTTONDELETE, _("Delete Selection"), wxDefaultPosition, wxDefaultSize, 0 );
          itemStaticBoxSizer16->Add(itemButton18, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

          //      Establish control colors on deferred creation
          SetControlColors(pDirCtl, (ColorScheme)0);
          SetControlColors(pSelCtl, (ColorScheme)0);
          SetControlColors(pTextCtl, (ColorScheme)0);

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

          //        Selected Directory
          wxString SelDir;
          SelDir = pDirCtl->GetPath();
          pSelCtl->Clear();
          pSelCtl->AppendText(SelDir);

          itemBoxSizer10->Layout();
      }
//#endif
}


void options::OnNMEASourceChoice(wxCommandEvent& event)
{
    int i = event.GetSelection();
    wxString src(m_itemNMEAListBox->GetString(i));
    if(src.Contains(_T("GPSD")))
    {
        m_itemNMEA_TCPIP_StaticBox->Enable();
        m_itemNMEA_TCPIP_Source->Enable();

        m_itemNMEA_TCPIP_Source->Clear();
        m_itemNMEA_TCPIP_Source->WriteText(_T("localhost")); // default

        wxString source;
        source = *pNMEADataSource;
        if(source.Contains(_T("GPSD")))
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

void options::SetControlColors(wxWindow *ctrl, ColorScheme cs)
{
      if(NULL != ctrl)
      {
            ctrl->SetBackgroundColour(GetGlobalColor(_T("DILG0")));

            wxColour back_color =GetGlobalColor(_T("DILG2"));
            wxColour text_color = GetGlobalColor(_T("DILG3"));

            ctrl->SetForegroundColour(text_color);

            wxWindowList kids = ctrl->GetChildren();
            for(unsigned int i = 0 ; i < kids.GetCount() ; i++)
            {
                  wxWindowListNode *node = kids.Item(i);
                  wxWindow *win = node->GetData();

                  if(win->IsKindOf(CLASSINFO(wxListBox)))
                        win->SetBackgroundColour(back_color);

                  else if(win->IsKindOf(CLASSINFO(wxGenericDirCtrl)))
                        win->SetBackgroundColour(back_color);

                  else if(win->IsKindOf(CLASSINFO(wxTextCtrl)))
                        win->SetBackgroundColour(back_color);

                  else if(win->IsKindOf(CLASSINFO(wxComboBox)))               // note ComboBoxes don't change bg properly on gtk
                        win->SetBackgroundColour(back_color);

                  else
                        win->SetBackgroundColour(GetGlobalColor(_T("DILG0")));      // msw looks better here

                  win->SetForegroundColour(text_color);
            }
      }
}

void options::OnButtonSelectSound(wxCommandEvent& event)
{
      wxString sound_dir = g_SData_Locn;
      sound_dir.Append(_T("sounds"));

      wxFileDialog *openDialog = new wxFileDialog(this, wxT("Select Sound File"), sound_dir, wxT(""),
                  wxT("WAV files (*.wav)|*.wav|All files (*.*)|*.*"), wxFD_OPEN);
      int response = openDialog->ShowModal();
      if (response == wxID_OK)
      {
            g_sAIS_Alert_Sound_File = openDialog->GetPath();
      }

}

void options::OnButtonTestSound(wxCommandEvent& event)
{
      wxSound AIS_Sound(g_sAIS_Alert_Sound_File);

      if(AIS_Sound.IsOk())
            AIS_Sound.Play();

}

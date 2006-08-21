/******************************************************************************
 * $Id: options.h,v 1.1 2006/08/21 05:52:20 dsr Exp $
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
 * $Log: options.h,v $
 * Revision 1.1  2006/08/21 05:52:20  dsr
 * Initial revision
 *
 * Revision 1.3  2006/07/28 20:49:09  dsr
 * New NMEA Logic
 *
 * Revision 1.2  2006/07/05 02:34:55  dsr
 * Save/Restore WiFi Server
 *
 * Revision 1.1.1.1  2006/04/19 03:23:29  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.9  2006/04/19 01:00:50  dsr
 * Add Font Chooser panel
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


#ifndef _OPTIONS_H_
#define _OPTIONS_H_


/*!
 * Includes
 */


////@begin includes
#include "wx/notebook.h"
#include "wx/dirctrl.h"
////@end includes

/*!
 * Forward declarations
 */

class wxGenericDirCtrl;
class MyConfig;

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_DIALOG 10001
#define SYMBOL_OPTIONS_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_OPTIONS_TITLE _("Options")
#define SYMBOL_OPTIONS_IDNAME ID_DIALOG
#define SYMBOL_OPTIONS_SIZE wxSize(500, 500)
#define SYMBOL_OPTIONS_POSITION wxDefaultPosition
#define ID_NOTEBOOK 10002
#define ID_PANEL2 10007
#define ID_DEBUGCHECKBOX1 10010
#define ID_PANEL 10004
#define ID_DIRCTRL 10005
#define ID_TEXTCTRL1 10000
#define ID_BUTTONADD 10011
#define ID_TEXTCTRL 10003
#define ID_BUTTONDELETE 10006
#define ID_BUTTONREBUILD 10008
#define ID_PANEL3 10012
#define ID_CHECKLISTBOX 10013
#define ID_RADIOBOX 10014
#define xID_OK 10009
#define ID_PANELFONT 10015
#define ID_CHOICE_FONTELEMENT 10016
#define ID_BUTTONFONTCHOOSE 10017
////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * options class declaration
 */

class options: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( options )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    options( );
    options( wxWindow* parent, wxWindowID id = SYMBOL_OPTIONS_IDNAME, const wxString& caption = SYMBOL_OPTIONS_TITLE,
           const wxString& Initial_Chart_Dir = _(""), const wxPoint& pos = SYMBOL_OPTIONS_POSITION,
           const wxSize& size = SYMBOL_OPTIONS_SIZE, long style = SYMBOL_OPTIONS_STYLE);

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_OPTIONS_IDNAME, const wxString& caption = SYMBOL_OPTIONS_TITLE,
             const wxPoint& pos = SYMBOL_OPTIONS_POSITION, const wxSize& size = SYMBOL_OPTIONS_SIZE,
             long style = SYMBOL_OPTIONS_STYLE, const wxString& init_chart_dir = _(""));

    /// Creates the controls and sizers
    void CreateControls();

      void SetInitialSettings();

      void SetCurrentDirListPtr(wxArrayString *p)  {m_pCurrentDirList = p;}
      void SetWorkDirListPtr(wxArrayString *p)  {m_pWorkDirList = p;}

      void SetConfigPtr(MyConfig *p)  {m_pConfig = p;}

////@begin options event handler declarations

      void OnDebugcheckbox1Click( wxCommandEvent& event );

      void OnDirctrlSelChanged( wxTreeEvent& event );

      void OnButtonaddClick( wxCommandEvent& event );

      void OnButtondeleteClick( wxCommandEvent& event );

      void OnButtonrebuildClick( wxCommandEvent& event );

      void OnRadioboxSelected( wxCommandEvent& event );

      void OnXidOkClick( wxCommandEvent& event );

      void OnCancelClick( wxCommandEvent& event );
      void OnChooseFont( wxCommandEvent& event );

////@end options event handler declarations

////@begin options member function declarations

      void OnPageChange(wxNotebookEvent& event);
      void OnNMEASourceChoice(wxCommandEvent& event);


    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end options member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin options member variables
    wxCheckBox* pDebugShowStat;
    wxCheckBox  *pPrintShowIcon;
    wxPanel* ps57Ctl;
    wxCheckListBox* ps57CtlListBox;
    wxRadioBox* pDispCat;

//    For "Charts" page
        wxPanel* itemPanel9;
      wxStaticBoxSizer* itemStaticBoxSizer11;
      wxBoxSizer* itemBoxSizer10;
      wxGenericDirCtrl* pDirCtl;
      wxTextCtrl* pSelCtl;
      wxTextCtrl* pTextCtl;
      wxStaticBox* itemActiveChartStaticBox;

//    For "NMEA Options" Box
      wxStaticBox             *m_itemNMEA_TCPIP_StaticBox;
      wxStaticBoxSizer        *m_itemNMEA_TCPIP_StaticBoxSizer;
      wxTextCtrl              *m_itemNMEA_TCPIP_Source;
      wxComboBox                *m_itemNMEAListBox;
      wxChoice                *m_itemNMEAAutoListBox;

//    For "WiFi Options" Box
      wxStaticBox             *m_itemWIFI_TCPIP_StaticBox;
      wxStaticBoxSizer        *m_itemWIFI_TCPIP_StaticBoxSizer;
      wxTextCtrl              *m_itemWIFI_TCPIP_Source;
//      wxChoice                *m_itemNMEAListBox;
//      wxChoice                *m_itemNMEAAutoListBox;

//    For Fonts page

      wxChoice                *m_itemFontElementListBox;

////@end options member variables

      wxCheckBox*             pSettingsCB1;


      wxArrayString           *m_pCurrentDirList;
      wxArrayString           *m_pWorkDirList;

      MyConfig                *m_pConfig;


      wxArrayPtrVoid          OBJLBoxArray;
      wxString          *m_pinit_chart_dir;
      wxWindow          *pParent;

};




 class OptionSetup
 {
public:

      OptionSetup();
 };



#endif
    // _OPTIONS_H_

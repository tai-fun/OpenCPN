/******************************************************************************
 * $Id: options.h,v 1.5 2008/04/11 03:26:33 bdbcat Exp $
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
 * $Log: options.h,v $
 * Revision 1.5  2008/04/11 03:26:33  bdbcat
 * Implement Auto Anchor Mark
 *
 * Revision 1.4  2008/03/30 23:29:52  bdbcat
 * Cleanup/optimize
 *
 * Revision 1.3  2008/01/02 21:05:30  bdbcat
 * Update for Version 1.2.2
 *
 * Revision 1.2  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.4  2006/11/01 02:19:08  dsr
 * AIS Support
 *
 * Revision 1.3  2006/10/08 00:37:17  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:37:48  dsr
 * Major refactor/cleanup
 *
 *
 */


#ifndef _OPTIONS_H_
#define _OPTIONS_H_


#include "wx/notebook.h"
#include "wx/dirctrl.h"

//      Forward Declarations
class wxGenericDirCtrl;
class MyConfig;

#define ID_DIALOG 10001
#define SYMBOL_OPTIONS_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_OPTIONS_TITLE _("Options")
#define SYMBOL_OPTIONS_IDNAME ID_DIALOG
#define SYMBOL_OPTIONS_SIZE wxSize(500, 500)
#define SYMBOL_OPTIONS_POSITION wxDefaultPosition

enum {
        ID_TEXTCTRL1 =            10000,
        ID_NOTEBOOK,
        ID_TEXTCTRL,
        ID_PANEL,
        ID_DIRCTRL,
        ID_BUTTONDELETE,
        ID_PANEL2,
        ID_BUTTONREBUILD,
        xID_OK,
        ID_DEBUGCHECKBOX1,
        ID_BUTTONADD,
        ID_PANEL3,
        ID_CHECKLISTBOX,
        ID_RADIOBOX,
        ID_PANELFONT,
        ID_CHOICE_FONTELEMENT,
        ID_BUTTONFONTCHOOSE,
        ID_CLEARLIST,
        ID_SELECTLIST,
        ID_CHOICE_AIS,
        ID_CHOICE_AP,
        ID_SOUNDGCHECKBOX,
        ID_METACHECKBOX,
        ID_TEXTCHECKBOX,
        ID_SCAMINCHECKBOX,
        ID_SHOWDEPTHUNITSBOX1,
        ID_AUTOANCHORMARKBOX1
};

//    Define an int bit field for dialog return value
//    To indicate which types of settings have changed
#define     GENERIC_CHANGED   1
#define     S52_CHANGED       2
#define     FONT_CHANGED      4


#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif


class options: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( options )
    DECLARE_EVENT_TABLE()

public:
    options( );
    options( wxWindow* parent, wxWindowID id = SYMBOL_OPTIONS_IDNAME, const wxString& caption = SYMBOL_OPTIONS_TITLE,
           const wxString& Initial_Chart_Dir = _(""), const wxPoint& pos = SYMBOL_OPTIONS_POSITION,
           const wxSize& size = SYMBOL_OPTIONS_SIZE, long style = SYMBOL_OPTIONS_STYLE);

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_OPTIONS_IDNAME, const wxString& caption = SYMBOL_OPTIONS_TITLE,
             const wxPoint& pos = SYMBOL_OPTIONS_POSITION, const wxSize& size = SYMBOL_OPTIONS_SIZE,
             long style = SYMBOL_OPTIONS_STYLE, const wxString& init_chart_dir = _(""));

    void CreateControls();

    void SetInitialSettings();

    void SetCurrentDirListPtr(wxArrayString *p)  {m_pCurrentDirList = p;}
    void SetWorkDirListPtr(wxArrayString *p)  {m_pWorkDirList = p;}

    void SetConfigPtr(MyConfig *p)  {m_pConfig = p;}
    void OnDebugcheckbox1Click( wxCommandEvent& event );
    void OnDirctrlSelChanged( wxTreeEvent& event );
    void OnButtonaddClick( wxCommandEvent& event );
    void OnButtondeleteClick( wxCommandEvent& event );
    void OnRadioboxSelected( wxCommandEvent& event );
    void OnXidOkClick( wxCommandEvent& event );
    void OnCancelClick( wxCommandEvent& event );
    void OnChooseFont( wxCommandEvent& event );
    void OnDisplayCategoryRadioButton( wxCommandEvent& event);
    void OnButtonClearClick( wxCommandEvent& event );
    void OnButtonSelectClick( wxCommandEvent& event );
    void OnPageChange(wxNotebookEvent& event);
    void OnNMEASourceChoice(wxCommandEvent& event);

// Should we show tooltips?
    static bool ShowToolTips();

//    For General Options
    wxCheckBox              *pDebugShowStat;
    wxCheckBox              *pPrintShowIcon;
    wxCheckBox              *pCDOOutlines;
    wxCheckBox              *pSDepthUnits;
    wxCheckBox              *pAutoAnchorMark;

//    For "S57" page
    wxPanel                 *ps57Ctl;
    wxCheckListBox          *ps57CtlListBox;
    wxRadioBox              *pDispCat;
    wxButton                *itemButtonClearList;
    wxButton                *itemButtonSelectList;
    wxRadioBox              *pPointStyle;
    wxRadioBox              *pBoundStyle;
    wxRadioBox              *p24Color;
    wxCheckBox              *pCheck_SOUNDG;
    wxCheckBox              *pCheck_META;
    wxCheckBox              *pCheck_SHOWTEXT;
    wxCheckBox              *pCheck_SCAMIN;
    wxTextCtrl              *m_ShallowCtl;
    wxTextCtrl              *m_SafetyCtl;
    wxTextCtrl              *m_DeepCtl;


//    For "Charts" page
    wxPanel* itemPanel9;
    wxStaticBoxSizer          *itemStaticBoxSizer11;
    wxBoxSizer                *itemBoxSizer10;
    wxGenericDirCtrl          *pDirCtl;
    wxTextCtrl                *pSelCtl;
    wxTextCtrl                *pTextCtl;
    wxStaticBox               *itemActiveChartStaticBox;

//    For "NMEA Options" Box
    wxStaticBox             *m_itemNMEA_TCPIP_StaticBox;
    wxStaticBoxSizer        *m_itemNMEA_TCPIP_StaticBoxSizer;
    wxTextCtrl              *m_itemNMEA_TCPIP_Source;
    wxComboBox              *m_itemNMEAListBox;
    wxComboBox              *m_itemNMEAAutoListBox;

#ifdef USE_WIFI_CLIENT
//    For "WiFi Options" Box
    wxStaticBox             *m_itemWIFI_TCPIP_StaticBox;
    wxStaticBoxSizer        *m_itemWIFI_TCPIP_StaticBoxSizer;
    wxTextCtrl              *m_itemWIFI_TCPIP_Source;
#endif

//    For Fonts page
    wxComboBox              *m_itemFontElementListBox;

//    For "AIS Options"
    wxComboBox              *m_itemAISListBox;

    wxCheckBox*             pSettingsCB1;

    wxArrayString           *m_pCurrentDirList;
    wxArrayString           *m_pWorkDirList;

    MyConfig                *m_pConfig;

    wxArrayPtrVoid          OBJLBoxArray;
    wxString                *m_pinit_chart_dir;
    wxWindow                *pParent;

    wxArrayString           *m_pSerialArray;
};


#endif
    // _OPTIONS_H_

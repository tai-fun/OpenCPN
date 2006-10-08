/******************************************************************************
 * $Id: chart1.h,v 1.4 2006/10/08 00:36:25 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  OpenCP Main wxWidgets Program
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
 * $Log: chart1.h,v $
 * Revision 1.4  2006/10/08 00:36:25  dsr
 * no message
 *
 * Revision 1.3  2006/10/05 03:52:54  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.3  2006/07/28 20:47:50  dsr
 * Cleanup
 *
 * Revision 1.2  2006/05/19 19:36:18  dsr
 * Cleanup
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.7  2006/04/19 00:54:35  dsr
 * Implement ColorScheme
 *
 * Revision 1.6  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.5  2006/03/13 05:10:09  dsr
 * Cleanup
 *
 * Revision 1.4  2006/02/23 01:15:53  dsr
 * Cleanup, combine old myapp and myframe definitions
 *
 *
 */

#ifndef __CHART1_H__
#define __CHART1_H__

#include "wx/print.h"
//#include "wx/printdlg.h"


#ifdef __WXMSW__
//#include "../resource.h"
#include "wx/msw/private.h"
#endif

#include "cpl_error.h"


extern "C" void MyCPLErrorHandler( CPLErr eErrClass, int nError,
                             const char * pszErrorMsg );





// define this to 1 to use wxToolBarSimple instead of the native one
//#define USE_GENERIC_TBAR 1

// define this to use XPMs everywhere (
#define USE_XPM_BITMAPS 1

/*
#if USE_GENERIC_TBAR
      #if !wxUSE_TOOLBAR_SIMPLE
        #error wxToolBarSimple is not compiled in, set wxUSE_TOOLBAR_SIMPLE \
               to 1 in setup.h and recompile the library.
    #else
        #include <wx/tbarsmpl.h>
    #endif
#endif // USE_GENERIC_TBAR
*/

//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------

#define ID_QUIT     101


//    ToolBar Constants
const int ID_TOOLBAR = 500;

enum
{
      ID_WEST = 550,
      ID_EAST,
      ID_ZOOMIN,
      ID_ZOOMOUT,
      ID_STKUP,
      ID_STKDN,
      ID_ROUTE,
      ID_FOLLOW,
      ID_SETTINGS,
      ID_TEXT,
      ID_CURRENT,
      ID_TIDE,
      ID_HELP,
      ID_TBEXIT,
      ID_TBSTAT,
      ID_PRINT,
      ID_COLSCHEME
};


static const long TOOLBAR_STYLE = wxTB_FLAT | wxTB_DOCKABLE | wxTB_TEXT ;

enum
{
    IDM_TOOLBAR_TOGGLETOOLBARSIZE = 200,
    IDM_TOOLBAR_TOGGLETOOLBARORIENT,
    IDM_TOOLBAR_TOGGLETOOLBARROWS,
    IDM_TOOLBAR_ENABLEPRINT,
    IDM_TOOLBAR_DELETEPRINT,
    IDM_TOOLBAR_INSERTPRINT,
    IDM_TOOLBAR_TOGGLEHELP,
    IDM_TOOLBAR_TOGGLE_TOOLBAR,
    IDM_TOOLBAR_TOGGLE_ANOTHER_TOOLBAR,
    IDM_TOOLBAR_CHANGE_TOOLTIP,
    IDM_TOOLBAR_SHOW_TEXT,
    IDM_TOOLBAR_SHOW_ICONS,
    IDM_TOOLBAR_SHOW_BOTH,

    ID_COMBO = 1000
};


enum
{
      FRAME_TIMER_1 = 555,
      FRAME_TIMER_2,
};

typedef enum ColorScheme
{
      COLOR_SCHEME_DEFAULT = 0,
      DAY,
      DUSK,
      NIGHT,
      NIGHTRED,
      GRAY,
      PRC,
      PRG,
      N_COLOR_SCHEMES
};

//      Define a constant GPS signal watchdog timeout value
#define GPS_TIMEOUT_SECONDS  5

//----------------------------------------------------------------------------
// fwd class declarations
//----------------------------------------------------------------------------
class ChartBase;

//----------------------------------------------------------------------------
//   Classes
//----------------------------------------------------------------------------
WX_DECLARE_STRING_HASH_MAP(char*, string_to_pchar_hash);


class MyApp: public wxApp
{
  public:
    bool OnInit();
    int OnExit();
};

class MyFrame: public wxFrame
{
  public:
    MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style);

    ~MyFrame();

    void OnActivate(wxActivateEvent& event);
    void OnCloseWindow(wxCloseEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnFrameTimer1(wxTimerEvent& event);
    bool DoChartUpdate(int bSelectType);
    void OnEvtNMEA(wxCommandEvent& event);
    void OnChar(wxKeyEvent &event);

    void OnToolLeftClick(wxCommandEvent& event);
    void ClearRouteTool();
    void DoStackUp(void);
    void DoStackDown(void);
    void UpdateChartStatusField(int i);
    void UpdateToolbarStatusWindow(ChartBase *pchart, bool bSendSize = true);
    void MouseEvent(wxMouseEvent& event);
    void SelectChartFromStack(int index);
    void ApplyGlobalSettings(bool bFlyingUpdate, bool bnewtoolbar);
    void SetChartThumbnail(int index);
    int DoOptionsDialog();
    void DoPrint(void);

    ColorScheme GetColorScheme();
    void SetAndApplyColorScheme(ColorScheme cs);

    bool GetMemoryStatus(int& mem_total, int& mem_used);

    int                 nRoute_State;
    int                 nBlinkerTick;
    bool                m_bTimeIsSet;

    wxStatusBar         *pStatusBar;

    wxTimer             FrameTimer1;

    wxTextCtrl          *m_textWindow;

    wxToolBar           *m_tbar;

    wxStaticBitmap      *ptool_ct_dummy;           // part of toolbar
    wxBitmapButton      *ptool_ct_dummy_bb;        // part of toolbar
    int                 tool_dummy_size_x, tool_dummy_size_y;

  private:
    void CreateMyToolbar();
    void DestroyMyToolbar();
    void MyAddTool(wxToolBarBase *pTB, int toolId, const wxString& label, const wxString& bmpFile,
                   const wxString& shortHelpString, wxItemKind kind);
    void ReSizeToolbar(void);
    int  toolbar_width_without_static;

    string_to_pchar_hash tool_xpm_hash;         // hash map of [static] toolbar xpm bitmaps

    int                 tool_dummy_size_x_last;

    DECLARE_EVENT_TABLE()
};


//--------------------------------------------------------------------
//          Private Memory Management
//--------------------------------------------------------------------

//    Private malloc replacement
void *x_malloc(size_t t);

//--------------------------------------------------------------------
//          Printing Support
//--------------------------------------------------------------------

class MyPrintout: public wxPrintout
{
 public:
  MyPrintout(wxChar *title = _T("My printout")):wxPrintout(title) {}
  bool OnPrintPage(int page);
  bool HasPage(int page);
  bool OnBeginDocument(int startPage, int endPage);
  void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);

  void DrawPageOne(wxDC *dc);
};


#endif

/******************************************************************************
 * $Id: chart1.h,v 1.15 2008/08/09 23:36:46 bdbcat Exp $
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
 * Revision 1.15  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
 *
 * Revision 1.13  2008/04/10 01:01:32  bdbcat
 * Cleanup
 *
 * Revision 1.12  2008/03/30 23:21:21  bdbcat
 * *** empty log message ***
 *
 * Revision 1.11  2008/01/12 06:18:10  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.10  2008/01/10 03:38:47  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.8  2007/06/15 03:08:07  bdbcat
 * Cleanup
 *
 * Revision 1.7  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.6  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.5  2006/12/03 21:27:20  dsr
 * Implement global enum definition of some ID constants,
 * to avoid inadvertent duplication of IDs which can create ambiguity in message passing.
 * Change gFrame timer tick rate away from exactly 1000 msec to avoid syncronization problems.
 *
 * Revision 1.4  2006/10/08 00:36:25  dsr
 * no message
 *
 * Revision 1.3  2006/10/05 03:52:54  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
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


enum NMEA_EVENT_STATE
{
      NMEA_STATE_NONE = 0 ,
      NMEA_STATE_RDY,
      NMEA_STATE_DONE
} ;

extern "C" void MyCPLErrorHandler( CPLErr eErrClass, int nError,
                             const char * pszErrorMsg );

wxArrayString *EnumerateSerialPorts(void);


//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------

#define TIMER_GFRAME_1 999

#define ID_QUIT     101


//    ToolBar Constants
const int ID_TOOLBAR = 500;

enum
{
      ID_WEST = 1550,
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



typedef enum ColorScheme
{
      GLOBAL_COLOR_SCHEME_DAY,
      GLOBAL_COLOR_SCHEME_DUSK,
      GLOBAL_COLOR_SCHEME_NIGHT,
      N_COLOR_SCHEMES
}_ColorScheme;

#define N_STATUS_BAR_FIELDS_MAX     20

//      Define a constant GPS signal watchdog timeout value
#define GPS_TIMEOUT_SECONDS  5

//    Define a timer value for Tide/Current updates
//    Note that the underlying data algorithms produce fresh data only every 15 minutes
//    So maybe 5 minute updates should provide sufficient oversampling
#define TIMER_TC_VALUE_SECONDS      300
//----------------------------------------------------------------------------
// fwd class declarations
//----------------------------------------------------------------------------
class ChartBase;
class wxSocketEvent;

//----------------------------------------------------------------------------
//   Classes
//----------------------------------------------------------------------------
WX_DECLARE_STRING_HASH_MAP(char*, string_to_pchar_hash);
WX_DECLARE_STRING_HASH_MAP(wxBitmap*, string_to_pbitmap_hash);
WX_DECLARE_STRING_HASH_MAP(wxString*, string_to_string_hash);


class MyApp: public wxApp
{
  public:
    bool OnInit();
    int OnExit();

    void TestSockets(void);
    void OnSocketEvent(wxSocketEvent& event);

};

class MyFrame: public wxFrame
{
  public:
    MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style);

    ~MyFrame();

    void OnEraseBackground(wxEraseEvent& event);
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
    int  DoOptionsDialog();
    void DoPrint(void);
    void StopSockets(void);
    void ResumeSockets(void);

    ColorScheme GetColorScheme();
    void SetAndApplyColorScheme(ColorScheme cs);

    bool GetMemoryStatus(int& mem_total, int& mem_used);

    void OnFrameTCTimer(wxTimerEvent& event);

    wxStatusBar         *m_pStatusBar;
    int                 nRoute_State;
    int                 nBlinkerTick;
    bool                m_bTimeIsSet;

    wxTimer             FrameTCTimer;
    wxTimer             FrameTimer1;
    wxTextCtrl          *m_textWindow;

    wxStaticBitmap      *m_ptool_ct_dummy;           // part of toolbar
    wxBitmapButton      *m_ptool_ct_dummy_bb;        // part of toolbar
    int                 m_tool_dummy_size_x, m_tool_dummy_size_y;
    int                 m_statTool_pos;
    string_to_pbitmap_hash *m_phash;

  private:
    wxToolBar *CreateAToolbar();
    void DestroyMyToolbar();
    void UpdateToolbar(ColorScheme cs);
    void ReSizeToolbar(void);
    void PrepareToolbarBitmaps(void);
    void BuildToolBitmap(wxImage *pimg, unsigned char back_color, wxString &index, string_to_pbitmap_hash &hash);

    int  toolbar_width_without_static;

    string_to_pchar_hash tool_xpm_hash;         // hash map of [static] toolbar xpm bitmaps

    int                 tool_dummy_size_x_last;

    string_to_pbitmap_hash tool_bitmap_hash_day;
    string_to_pbitmap_hash tool_bitmap_hash_dusk;
    string_to_pbitmap_hash tool_bitmap_hash_night;

    int                 m_StatusBarFieldCount;

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


//      A global definition for window, timer and other ID's as needed.
enum {
    ID_NMEA_WINDOW      = wxID_HIGHEST,
    ID_AIS_WINDOW,
    FRAME_TIMER_1,
    FRAME_TIMER_2,
    TIMER_AIS1,
    AIS_SOCKET_ID,
    WIFI_SOCKET_ID,
    TIMER_WIFI1,
    FRAME_TIMER_DOG,
    FRAME_TC_TIMER

};

#endif

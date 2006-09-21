/******************************************************************************
 * $Id: chart1.cpp,v 1.2 2006/09/21 01:37:36 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  OpenCPN Main wxWidgets Program
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
 * $Log: chart1.cpp,v $
 * Revision 1.2  2006/09/21 01:37:36  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.8  2006/08/04 11:42:01  dsr
 * no message
 *
 * Revision 1.7  2006/07/28 20:31:00  dsr
 * Implement new NMEA/Autopilot code
 *
 * Revision 1.6  2006/07/05 02:32:06  dsr
 * Add WiFi Server
 *
 * Revision 1.5  2006/06/15 02:38:32  dsr
 * Support Database Update
 *
 * Revision 1.4  2006/05/19 19:16:09  dsr
 * New Thumbchart logic
 *
 * Revision 1.3  2006/04/23 03:56:31  dsr
 * Fix internal names
 *
 * Revision 1.2  2006/04/20 02:26:24  dsr
 * *** empty log message ***
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.17  2006/04/19 02:04:25  dsr
 * Use FontMgr
 *
 * Revision 1.16  2006/03/25 20:25:52  dsr
 * Cleanup for wx2.6.2
 *
 * Revision 1.15  2006/03/16 03:53:14  dsr
 * Cleanup
 *
 * Revision 1.14  2006/03/16 03:07:59  dsr
 * Cleanup tabs
 *
 * Revision 1.13  2006/03/13 05:48:44  dsr
 * Cleanup
 *
 * Revision 1.12  2006/03/13 05:03:15  dsr
 * Fussing with toolBar
 *
 * Revision 1.11  2006/03/04 21:14:11  dsr
 * Correct Chart Scale logic when shifting from S57 to BSB
 *
 * Revision 1.10  2006/02/24 18:02:22  dsr
 * Show PubDate and Name in toolbar info panel
 *
 * Revision 1.9  2006/02/24 03:01:33  dsr
 * Redefine pBitmap_Dir
 *
 * Revision 1.8  2006/02/23 01:32:10  dsr
 * Cleanup, fix toolbar for GTK, add Help button
 *
 *
 */
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "wx/print.h"
#include "wx/printdlg.h"
#include "wx/artprov.h"

#include "dychart.h"

#ifdef __WXMSW__
  #include <stdlib.h>
  #include <math.h>
  #include <time.h>
#endif

#ifndef __WXMSW__
#include <signal.h>
#endif

#include "chart1.h"
#include "chcanv.h"
#include "chartdb.h"
#include "navutil.h"
#include "routeman.h"
#include "statwin.h"
#include "concanv.h"
#include "nmea.h"
#include "nmea0183/nmea0183.h"
#include "dialog/options.h"
#include "about.h"
#include "thumbwin.h"
#include "tcmgr.h"
#include "cpl_error.h"

#ifdef __WXMSW__
#include <wx/image.h>
#endif



#ifdef USE_S57
#include "s52plib.h"
#include "s57chart.h"
#endif

#ifdef USE_WIFI_CLIENT
#include "wificlient.h"
#endif

//#ifdef __WXMSW__
//    #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__ )
//    #define new DEBUG_NEW
//#endif




//------------------------------------------------------------------------------
//      Static variable definition
//------------------------------------------------------------------------------
CPL_CVSID("$Id: chart1.cpp,v 1.2 2006/09/21 01:37:36 dsr Exp $");

//      These static variables are required by something in MYGDAL.LIB...sigh...

#ifdef __WXMSW__
        int errno;
#endif

double _HUGE;



MyFrame         *gFrame;


ChartCanvas     *cc1;
ConsoleCanvas   *console;
NMEAWindow      *nmea;
StatWin         *stats;

wxToolBarBase   *toolBar;
MyConfig        *pConfig;

ChartBase       *Current_Ch;
ChartDB         *ChartData;
ChartStack      *pCurrentStack;
int             CurrentStackEntry;
wxString        *pdir_list[20];

RouteList       *pRouteList;

Select          *pSelect;
Select          *pSelectTC;

Routeman        *pRouteMan;
NMEA0183        *pNMEA0183;

float           gLat, gLon, gCog, gSog, gHdg;
float           vLat, vLon;

wxArrayString   *pChartDirArray;
bool            bDBUpdateInProgress;

ThumbWin        *pthumbwin;
TCMgr           *ptcmgr;

wxLog           *logger;
wxLog           *Oldlogger;
bool            bAutoPilotOut;
bool            bDrawCurrentValues;

wxString        *pSData_Locn;
wxString        *pChartListFileName;
wxString        *pBitmap_Dir;
wxString        *pTC_Dir;
wxString        *pHome_Locn;
wxString        *pWVS_Locn;
wxString        *pInit_Chart_Dir;
wxString        *pcsv_locn;

int             user_user_id;
int             file_user_id;

int             quitflag;
int             g_tick;
int             mem_total, mem_initial;

wxString        *phost_name;

static unsigned int malloc_max;

OCP_NMEA_Thread *pNMEA_Thread;
wxString        *pNMEADataSource;
wxString        *pNMEA_AP_Port;

ChartDummy      *pDummyChart;

wxString        *pWIFIServerName;

AutoPilotWindow *pAPilot;

// Global print data, to remember settings during the session
wxPrintData *g_printData = (wxPrintData*) NULL ;

// Global page setup data
wxPageSetupData* g_pageSetupData = (wxPageSetupData*) NULL;

bool            g_bShowPrintIcon;

FontMgr         *pFontMgr;

ColorScheme     global_color_scheme;

int             gGPS_Watchdog;
bool            bGPSValid;

#ifdef USE_S57
s52plib         *ps52plib;
#endif

#ifdef USE_WIFI_CLIENT
WIFIWindow      *pWIFI;
#endif


//-----------------------------------------------------------------------------------------------------
//      OCP_NMEA_Thread Static data store
//-----------------------------------------------------------------------------------------------------
char                            rx_share_buffer[MAX_RX_MESSSAGE_SIZE];
unsigned int                    rx_share_buffer_length;
ENUM_BUFFER_STATE               rx_share_buffer_state;
wxMutex                         *ps_mutexProtectingTheRXBuffer;




#ifndef __WXMSW__
struct sigaction sa_usr1;
struct sigaction sa_usr1_old;
#endif


#ifdef __WXMSW__
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

// ----------------------------------------------------------------------------
// Icon resources
// ----------------------------------------------------------------------------

#include "bitmaps/settings.xpm"
#include "bitmaps/zoomin.xpm"
#include "bitmaps/zoomout.xpm"
#include "bitmaps/scin.xpm"
#include "bitmaps/scout.xpm"
#include "bitmaps/tide.xpm"
#include "bitmaps/text.xpm"
#include "bitmaps/route.xpm"
#include "bitmaps/exitt.xpm"
#include "bitmaps/follow.xpm"
#include "bitmaps/current.xpm"
#include "bitmaps/print.xpm"
#include "bitmaps/help.xpm"
#include "bitmaps/colscheme.xpm"

//------------------------------------------------------------------------------
//              Fwd Refs
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------
//      Signal Handlers
//-----------------------------------------------------------------------

//      SIGUSR1
//      Raised externally to cause orderly termination of application
//      Intended to act just like pushing the "EXIT" button

static void
catch_sig_usr1(int signo)
{
        quitflag++;                             // signal to the timer loop
}


// `Main program' equivalent, creating windows and returning main app frame
//------------------------------------------------------------------------------
// MyApp
//------------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)


bool MyApp::OnInit()
{

//      _CrtSetBreakAlloc(63763);

#ifdef __WXMSW__
_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG );
_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
_CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
_CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_DEBUG );
#endif


#ifndef __WXMSW__
//      Setup Linux SIGNAL handling, for external program control

//      Build the sigaction structure
        sa_usr1.sa_handler = catch_sig_usr1;            // point to my handler
        sigemptyset(&sa_usr1.sa_mask);                  // make the blocking set
                                                        // empty, so that all
                                                        // other signals will be
                                                        // unblocked during my handler
        sa_usr1.sa_flags = 0;

//      Register my request for this signal
        sigaction(SIGUSR1, &sa_usr1, &sa_usr1_old);
#endif

//      Init the private memory manager
        malloc_max = 0;

//      wxHandleFatalExceptions(true);


// Set up default FONT encoding, which should have been done by wxWidgets some time before this......
        wxFont temp_font(10, wxDEFAULT ,wxNORMAL, wxNORMAL, FALSE, wxString(""), wxFONTENCODING_SYSTEM );
        temp_font.SetDefaultEncoding(wxFONTENCODING_SYSTEM );

//  Init my private font manager
        pFontMgr = new FontMgr();

//    Init the XPM image handler
        wxImage t;
        wxXPMHandler *th = new wxXPMHandler;
        t.AddHandler(th);

//      Establish a "home" location
        pHome_Locn= new wxString;
#ifdef __WXMSW__
        pHome_Locn->Append(wxString("C:\\Program Files\\opencpn\\"));
#else
        pHome_Locn->Append(::wxGetHomeDir());                   // in the current users home
        pHome_Locn->Append("/");
#endif


//      Establish Log File location

#ifdef __WXMSW__
        logger=new wxLogStderr();
#else
        wxString log(*pHome_Locn);
        log.Append("opencpn.log");
        FILE *flog = fopen(log.c_str(), "a");
        logger=new wxLogStderr(flog);
#endif
        Oldlogger = wxLog::SetActiveTarget(logger);

//        wxLog::SetTraceMask(2);               // verbose message traces to log output

/*

        wxDateTime wxft =  wxDateTime::Now();

        wxString sdate(wxft.Format("%D"));
        sdate.Prepend("sudo /bin/date -s ");
        printf("%s\n", sdate.c_str());

        wxExecute(sdate, wxEXEC_ASYNC);

        wxString g(wxft.Format("%T"));
        g.Prepend("sudo /bin/date -s ");
        printf("%s\n", g.c_str());
*/


//      Send init message
        wxLogMessage("\n\n");
        wxString imsg(_T(" -------Starting opencpn-------"));
        wxDateTime now = wxDateTime::Now();
        imsg.Prepend(now.FormatISODate());
        wxLogMessage(imsg);

#ifdef USE_CPL
//      Set up a useable CPL library error handler
        CPLSetErrorHandler( MyCPLErrorHandler );
#endif

//      Create some static strings
        pNMEADataSource = new wxString();
        pNMEA_AP_Port = new wxString();
        pWIFIServerName = new wxString();
        pcsv_locn = new wxString();


//      Init the Chart Dir Array(s)
        pChartDirArray = new wxArrayString();

//      Init the Selectable Route Items List
        pSelect = new Select();

//      Init the Selectable Tide/Current Items List
        pSelectTC = new Select();

//      Init the Route Manager
        pRouteMan = new Routeman();


//      Who am I?
        phost_name = new wxString(::wxGetHostName());


//      (Optionally) Capture the user and file(effective) ids
//  Some build environments may need root privileges for hardware
//  port I/O, as in the NMEA data input class.  Set that up here.


#ifndef __WXMSW__
        user_user_id = getuid ();
#if 1 //def dyUSE_EUID
        file_user_id = geteuid ();
    #else
        file_user_id = user_user_id;
    #endif
#endif



//      Establish a "shared data" location
        pSData_Locn= new wxString;
#ifdef __WXMSW__
//      pSData_Locn->Append(::wxGetCwd());
        pSData_Locn->Append(wxString("\\Program Files\\opencpn\\"));
#else
        pSData_Locn->Append(wxString("/usr/local/share/opencpn/"));
#endif


//      Establish the location of the config file
#ifdef __WXMSW__
        wxString Config_File("opencpn.ini");
        Config_File.Prepend(*pHome_Locn);
#else
        wxString Config_File(".opencpn/opencpn.conf");
        Config_File.Prepend(*pHome_Locn);
#endif

        wxFileName config_test_file_name(Config_File);
        if(config_test_file_name.FileExists())
                wxLogMessage("Using existing Config_File: %s", Config_File.c_str());
        else
        {
              wxString msg1("Cannot find Config File ");
              msg1.Append(Config_File);
              msg1.Append("...OK to create? (will exit if No)");

              wxMessageDialog mdlg(gFrame, msg1, wxString("OpenCPN"),wxYES_NO  );
              if(mdlg.ShowModal() == wxID_YES)
              {
                   wxLogMessage("Creating new Config_File: %s", Config_File.c_str());
                   if(!config_test_file_name.Mkdir(config_test_file_name.GetPath()))
                       wxLogMessage("Cannot create config file directory for %s", Config_File.c_str());
              }
              else
              {
                   Config_File.Clear();
                   return false;                    // Probably will provoke some memory leakage....
              }
        }

//      Open/Create the Config Object
        MyConfig *pCF = new MyConfig(wxString(""), wxString(""), Config_File);
        pConfig = (MyConfig *)pCF;
        pConfig->LoadMyConfig(0);

//      Establish location of bitmaps and cursors
#ifdef __WXMSW__
        pBitmap_Dir = new wxString(_T("bitmaps\\"));
#else
        pBitmap_Dir = new wxString(_T("bitmaps/"));
#endif
        pBitmap_Dir->Prepend(*pSData_Locn);

//      Verify the bitmaps exist, or nothing much else can be done...
        wxFileName bm_test_file_name(*pBitmap_Dir + wxString("left.xpm"));
        if(bm_test_file_name.FileExists())
            wxLogMessage("Using bitmaps in: %s", pBitmap_Dir->c_str());
        else
        {
            wxString msg1("Cannot find bitmap directory\n ");
            msg1.Append(*pBitmap_Dir);
            msg1.Append("\n...Exiting now");

            wxLogMessage("%s", msg1.c_str());

            return false;                    // Probably will provoke some memory leakage....
        }


#ifdef USE_S57
//      Init the s57 manager, specifying the location of the required csv files.
//      If the config file contains the entry, use it.
//      Otherwise, default to [shared data dir]/s57_data
        if(pcsv_locn->IsEmpty())
        {
            pcsv_locn->Append(*pSData_Locn);

            pcsv_locn->Append("s57data");
        }

        s57_initialize(*pcsv_locn);



        wxString plib_file(*pcsv_locn);
        wxString plib_file_name("/S52RAZDS.RLE");
        plib_file += plib_file_name;

        ps52plib = new s52plib((char *)pcsv_locn->c_str(), (char *)plib_file_name.c_str(), "/SP52COL.DAT");

        if(!ps52plib->m_bOK)
                wxLogMessage("S52PLIB Initialization failed, disabling S57 charts...");

#endif  // S57


// Set default color scheme
        global_color_scheme = COLOR_SCHEME_DEFAULT;




//      Establish location and name of chart database
#ifdef __WXMSW__
        pChartListFileName = new wxString("CHRTLIST.DAT");
#else
        pChartListFileName = new wxString(".opencpn/chartlist.dat");
#endif
        pChartListFileName->Prepend(*pHome_Locn);




//      Establish location of Tide and Current data
        pTC_Dir = new wxString(_T("tcdata"));
        pTC_Dir->Prepend(*pSData_Locn);
        pTC_Dir->Append(wxFileName::GetPathSeparator());


//      Establish guessed location of chart tree
        pInit_Chart_Dir = new wxString(_T("charts"));
        pInit_Chart_Dir->Prepend(*pSData_Locn);


//      Establish the WorldVectorShoreline Dataset location
        pWVS_Locn = new wxString(_T("wvsdata"));
        pWVS_Locn->Prepend(*pSData_Locn);
        pWVS_Locn->Append(wxFileName::GetPathSeparator());

//      Reload the config data, to pick up any missing data class configuration info
//      e.g. s52plib, which could not be created until first config load completes
//      Think catch-22
        pConfig->LoadMyConfig(1);


//      Hard code the frame size for now
//      TODO??
        int dis_w, dis_h;
        wxDisplaySize(&dis_w, &dis_h);

        int cx, cy, cw, ch;
        ::wxClientDisplayRect(&cx, &cy, &cw, &ch);
        wxSize new_frame_size;
        if(dis_w > 1024)
                new_frame_size.Set(1182, 900);  //
//                new_frame_size.Set(800, 600);  // for window debug
        else
                new_frame_size.Set(cw, 735);

        // Create the main frame window
        gFrame = new MyFrame(NULL, _T("OpenCPN"), wxPoint(0, 0), new_frame_size);


//      Create Children of Frame
//              n.b.  if only one child exists, wxWindows expands the child
//                        to the parent client area automatically, (as a favor?)
//                        Here, we'll do explicit sizing on SIZE events

        cc1 =  new ChartCanvas(gFrame);                         // the chart display canvas

        console = new ConsoleCanvas(gFrame);                    // the console

        stats = new StatWin(gFrame);

        nmea = new NMEAWindow(gFrame, *pNMEADataSource);

        pAPilot = new AutoPilotWindow(gFrame, *pNMEA_AP_Port);

#ifdef USE_WIFI_CLIENT
        pWIFI = new WIFIWindow(gFrame, *pWIFIServerName );
#endif

        pNMEA0183 = new NMEA0183();

        pthumbwin = new ThumbWin(gFrame);

        gFrame->ApplyGlobalSettings(1, true);               // done once on init with resize

// Show the frame
        gFrame->Show(TRUE);

#ifdef USE_S57
//      Try to validate the ISO8211 library
//      especially the ability to do ddfrecord updates
//      which is required for s57 ENC updates.

        if(!s57_ddfrecord_test())
        {
            wxString message("GDAL/OGR library is not up-to-date.\n");
            message.Append("S57 ENC Updates will be disabled.\n");
            message.Append("Please see README file.");
            wxMessageDialog mdlg(gFrame, message, wxString("OpenCPN"),wxICON_INFORMATION | wxOK );
            mdlg.ShowModal();
        }
#endif


//      Try to load the current chart list Data file
        ChartData = new ChartDB(gFrame);
        if(!ChartData->LoadBinary(pChartListFileName))
        {
                bDBUpdateInProgress = true;

                if(pChartDirArray->GetCount())
                {
//              Create and Save the Chart Database

                        delete ChartData;
                        ChartData = new ChartDB(gFrame);

                        ChartData->Create(pChartDirArray, true);
                        ChartData->SaveBinary(pChartListFileName, pChartDirArray);

                }

                else                                            // No chart database, no config hints, so bail....
                {
                  wxLogMessage("Chartlist file not found, config chart dir array is empty.  Chartlist target file is:%s",
                              pChartListFileName->c_str());

                  wxString msg1("           No Charts Installed.\nPlease select chart folders in OPTIONS dialog.");

                  wxMessageDialog mdlg(gFrame, msg1, wxString("OpenCPN"),wxICON_ERROR | wxOK );
                  int dlg_ret;
                  dlg_ret = mdlg.ShowModal();

                  gFrame->DoOptionsDialog();
                }

                bDBUpdateInProgress = false;
        }


        pCurrentStack = new ChartStack;



//      All set to go.....

#ifndef __WXMSW__
//      Record initial memory status
        gFrame->GetMemoryStatus(mem_total, mem_initial);
        wxLogMessage("MemoryStatus:  mem_total: %d kb,  mem_initial: %d kb",
                                        mem_total, mem_initial);
#endif

//      Start up the ticker....
        gFrame->Timer1.Start(1000,wxTIMER_CONTINUOUS);

#ifdef __WXX11__
//        OptionSetup *pOS = new OptionSetup();
//        delete pOS;
#endif

   return TRUE;
}



int MyApp::OnExit()
{
        wxLogMessage("opencpn exiting cleanly...\n");

        delete pConfig;

        delete pSelect;

        delete pSelectTC;

        delete pRouteMan;

        delete pNMEA0183;

        delete pChartDirArray;

#ifdef USE_S57
        delete ps52plib;
#endif

        delete pDummyChart;

        if(ptcmgr)
                delete ptcmgr;

        if(logger)
        {
                wxLog::SetActiveTarget(Oldlogger);
                delete logger;
        }

        delete pChartListFileName;
        delete pBitmap_Dir;
        delete pHome_Locn;
        delete pSData_Locn;
        delete pTC_Dir;
        delete phost_name;
        delete pInit_Chart_Dir;
        delete pWVS_Locn;

        delete pNMEADataSource;
        delete pNMEA_AP_Port;

        delete pWIFIServerName;

        delete pFontMgr;

//        _CrtDumpMemoryLeaks( );

        return TRUE;
}





//------------------------------------------------------------------------------
// MyFrame
//------------------------------------------------------------------------------


//      Frame implementation
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_CLOSE(MyFrame::OnCloseWindow)
  EVT_MENU(wxID_EXIT, MyFrame::OnExit)
  EVT_SIZE(MyFrame::OnSize)
  EVT_MENU(-1, MyFrame::OnToolLeftClick)
  EVT_TIMER(TIMER_1, MyFrame::OnTimer1)
  EVT_ACTIVATE(MyFrame::OnActivate)
//  EVT_MOUSE_EVENTS(MyFrame::MouseEvent)
//  EVT_CHAR(MyFrame::OnChar)
  EVT_COMMAND(wxID_HIGHEST, EVT_NMEA, MyFrame::OnEvtNMEA)
END_EVENT_TABLE()


// My frame constructor
MyFrame::MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size):
  wxFrame(frame, -1, title, pos, size, wxSIMPLE_BORDER | wxCLIP_CHILDREN | wxRESIZE_BORDER)
      //wxCAPTION | wxSYSTEM_MENU | wxRESIZE_BORDER
                                                                                 //, wxSIMPLE_BORDER)
{

        pStatusBar = NULL;

//      Create the ToolBar
        CreateMyToolbar();



        //      Redirect the global heartbeat timer to this frame
        Timer1.SetOwner(this, TIMER_1);

        //      Set up some assorted member variables
        nRoute_State = 0;
        m_bTimeIsSet = false;

//  Initialize the Printer data structures
       g_printData = new wxPrintData;
       g_printData->SetOrientation(wxLANDSCAPE);

       g_pageSetupData = new wxPageSetupDialogData;

}

MyFrame::~MyFrame()
{
        Timer1.Stop();
        delete ChartData;
        delete pCurrentStack;

//      Free the Route List
        wxRouteListNode *node = pRouteList->GetFirst();

        while(node)
        {
            Route *pRouteDelete = node->GetData();

                delete pRouteDelete;

            node = node->GetNext();
        }
        delete pRouteList;



}


void MyFrame::OnActivate(wxActivateEvent& event)
{
//      Activating?
        if(event.GetActive())
        {

                if(!bDBUpdateInProgress)
                        if(Current_Ch)
                                Current_Ch->InvalidateCache();

                if(cc1)
                        cc1->m_bForceReDraw = true;
        }


}

ColorScheme MyFrame::GetColorScheme()
{
       return global_color_scheme;
}

void MyFrame::SetAndApplyColorScheme(ColorScheme cs)
{
      global_color_scheme = cs;

      if(ChartData)
      {
            ChartData->ApplyColorSchemeToCachedCharts(cs);
      }
}

void MyFrame::DestroyMyToolbar()
{

    delete ptool_ct_dummy;
    delete toolBar;

}


void MyFrame::CreateMyToolbar()
{


// Load up all the toolbar bitmap xpm data pointers into a hash map
      tool_xpm_hash.clear();
      tool_xpm_hash["settings"]     = (char *)settings;
      tool_xpm_hash["zoomin"]       = (char *)zoomin;
      tool_xpm_hash["zoomout"]      = (char *)zoomout;
      tool_xpm_hash["scin"]         = (char *)scin;
      tool_xpm_hash["scout"]        = (char *)scout;
      tool_xpm_hash["tide"]         = (char *)tide;
      tool_xpm_hash["route"]        = (char *)route;
      tool_xpm_hash["current"]      = (char *)current;
      tool_xpm_hash["text"]         = (char *)text;
      tool_xpm_hash["print"]        = (char *)print;
      tool_xpm_hash["exitt"]        = (char *)exitt;
      tool_xpm_hash["follow"]       = (char *)follow;
      tool_xpm_hash["help"]         = (char *)help;
      tool_xpm_hash["colorscheme"]  = (char *)colscheme;

    long style = 0;
    style |= wxTB_HORIZONTAL ;

    toolBar = CreateToolBar(style, ID_TOOLBAR);
    toolBar->SetBackgroundColour(wxColour(230,230,230));
        toolBar->SetToolBitmapSize(wxSize(32,32));
    toolBar->SetRows(1);

    //Set up the ToolBar


//      Think about wxUNIV themes here....


//      Set up the margins, etc...
//      All this is poorly documented, and very clumsy
//      see the wx src files

    toolBar->SetToolPacking(1);
    toolBar->SetToolSeparation(5);
    wxSize defMargins = toolBar->GetMargins();
    toolBar->SetMargins(wxSize(6, defMargins.y));

//      Calculate the tool and separator pitches
    wxSize toolsize = toolBar->GetToolSize();
    int tool_sep = toolBar->GetToolSeparation();

    int tool_packing = toolBar->GetToolPacking();
    wxSize tool_margin = toolBar->GetMargins();

        int x;                                          // running position
      int pitch_tool, pitch_sep;
      pitch_tool = toolsize.x + tool_packing + tool_margin.x;
      pitch_sep =  tool_sep   + tool_packing + tool_margin.x;
      x =tool_packing + tool_margin.x;

      // Some fixups needed here
#ifdef __WXMSW__
      pitch_tool = toolsize.x + tool_packing;
      pitch_sep =  tool_sep + tool_packing;
      x = 0;
#endif

#ifdef __WXGTK__
      pitch_tool += 2;
      x -= 1;
#endif



    MyAddTool(toolBar, ID_ZOOMIN, _T(""), _T("zoomin"), _T(""), wxITEM_NORMAL);
    x += pitch_tool;
    MyAddTool(toolBar, ID_ZOOMOUT, _T(""), _T("zoomout"), _T(""), wxITEM_NORMAL);
    x += pitch_tool;

    toolBar->AddSeparator();
    x += pitch_sep;

    MyAddTool(toolBar, ID_STKDN, _T(""), _T("scin"), _T("Stack +"), wxITEM_NORMAL);
    x += pitch_tool;
    MyAddTool(toolBar, ID_STKUP, _T(""), _T("scout"), _T("Stack -"), wxITEM_NORMAL);
    x += pitch_tool;

//    toolBar->AddSeparator();
//    x += pitch_sep;
//    toolBar->AddSeparator();
//    x += pitch_sep;
    toolBar->AddSeparator();
    x += pitch_sep;

    MyAddTool(toolBar, ID_ROUTE, _T(""), _T("route"), _T("Create Route"), wxITEM_NORMAL);
    x += pitch_tool;
    MyAddTool(toolBar, ID_FOLLOW, _T(""), _T("follow"), _T("Auto Follow"), wxITEM_CHECK);
    x += pitch_tool;

//    toolBar->AddSeparator();
//    x += pitch_sep;
//    toolBar->AddSeparator();
//    x += pitch_sep;
    toolBar->AddSeparator();
    x += pitch_sep;
    MyAddTool(toolBar, ID_SETTINGS, _T(""), _T("settings"), _T("Settings"), wxITEM_NORMAL);
    x += pitch_tool;

    MyAddTool(toolBar, ID_TEXT, _T(""), _T("text"), _T("Enable S57 Text"), wxITEM_NORMAL);
    x += pitch_tool;

    toolBar->AddSeparator();
    x += pitch_sep;
    MyAddTool(toolBar, ID_CURRENT, _T(""), _T("current"), _T("Show Currents"), wxITEM_CHECK);
    x += pitch_tool;

    MyAddTool(toolBar, ID_TIDE, _T(""), _T("tide"), _T("Show Tides"), wxITEM_CHECK);
    x += pitch_tool;

    toolBar->AddSeparator();
    x += pitch_sep;

    if(g_bShowPrintIcon)
    {
        MyAddTool(toolBar, ID_PRINT, _T(""), _T("print"), _T("Print Chart"), wxITEM_NORMAL);
        x += pitch_tool;
    }

    if(1)
    {
      MyAddTool(toolBar, ID_COLSCHEME, _T(""), _T("colorscheme"), _T("Change Color Scheme"), wxITEM_NORMAL);
      x += pitch_tool;
    }

    MyAddTool(toolBar, ID_HELP, _T(""), _T("help"), _T("About OpenCPN"), wxITEM_NORMAL);
    x += pitch_tool;


//      Create and add a dummy control, to arrange for the "exit" tool to be
//      at right margin

    int tx,ty;
    GetClientSize(&tx, &ty);                    // of the frame

    int filler_pad = tool_margin.x + tool_packing;
    int filler_width = tx - x - pitch_tool - filler_pad;

    toolbar_width_without_static = x + pitch_tool + filler_pad;     // used by Resize()

    wxImage tool_image_dummy(filler_width,32);
    wxBitmap tool_bm_dummy(tool_image_dummy);

#define DUMMY_HEIGHT    40
    ptool_ct_dummy = new wxStaticBitmap(toolBar, ID_TBSTAT, tool_bm_dummy,
                                        wxPoint(0,0), wxSize(filler_width,DUMMY_HEIGHT),wxSIMPLE_BORDER, _T("staticBitmap"));

    tool_dummy_size_x = filler_width;
    tool_dummy_size_y = DUMMY_HEIGHT;

    toolBar->AddControl(ptool_ct_dummy);

//      And add the "Exit" tool
    MyAddTool(toolBar, ID_TBEXIT, _T(""), _T("exitt"), _T("Exit"), wxITEM_NORMAL);


// Realize() the toolbar
    toolBar->Realize();

//      Set up the toggle states
    if(pConfig)
        toolBar->ToggleTool(ID_FOLLOW, pConfig->st_bFollow);

#ifdef USE_S57
    if(pConfig)
        toolBar->ToggleTool(ID_TEXT, ps52plib->GetShowS57Text());
#endif

        SetStatusBarPane(-1);                   // don't show help on status bar
}


//      Some helpers functions for Toolbar support

void MyFrame::MyAddTool(wxToolBarBase *pTB, int toolId, const wxString& label, const wxString& bmpFile,
                              const wxString& shortHelpString, wxItemKind kind)
{
//      Set up the location and type of Bitmap data
        wxFileName bmp_file(*pBitmap_Dir, _T("dummy"), _T("xpm"));

        bmp_file.SetName(bmpFile);

        wxBitmap *ptoolBarBitmap;

        wxImage *pimg;

//        pimg = new wxImage(bmp_file.GetFullPath());

        char **px1 = (char **)tool_xpm_hash[bmpFile];
        if(px1)
            pimg = new wxImage(px1);
        else
            pimg = new wxImage;

        if(pimg->Ok())
                ptoolBarBitmap = new wxBitmap(*pimg);
        else
        {
                wxString msg1("Unable to find bitmap:");
                msg1.Append(bmp_file.GetName());
                msg1.Append("...Substituting ArtProvider Bitmap");
                wxLogMessage(msg1);

//                ptoolBarBitmap = new wxBitmap(32,32, -1);
                ptoolBarBitmap = new wxBitmap(wxArtProvider::GetBitmap(wxART_MISSING_IMAGE,
                                              wxART_TOOLBAR, wxSize(32, 32)));
        }

        delete pimg;

        pTB->AddTool(toolId , _T(""), *ptoolBarBitmap, shortHelpString, kind);

        delete ptoolBarBitmap;
}

void MyFrame::ReSizeToolbar(void)
{

    int tx, ty;
    GetClientSize(&tx, &ty);                    // of the frame

    tool_dummy_size_x = tx - toolbar_width_without_static;

#ifndef __WXMSW__
    if(Current_Ch)
        UpdateToolbarStatusWindow(Current_Ch, false);
#endif

}




// Intercept menu commands
void MyFrame::OnExit(wxCommandEvent& event)
{
}

void MyFrame::OnCloseWindow(wxCloseEvent& event)
{
   Timer1.Stop();

   pConfig->UpdateSettings();


    delete g_printData;
    delete g_pageSetupData;

//      Explicitely Close some children, especially the ones with event handlers
//      or that call GUI methods

    cc1->Destroy();
    if(nmea)
    {
        nmea->Close();
        nmea = NULL;                        // This will be a signal to TCP/IP socket event handler
                                            // that any remaining events in queue are to be ignored
    }

#ifdef USE_WIFI_CLIENT
    if(pWIFI)
    {
        pWIFI->Close();
        pWIFI = NULL;
    }
#endif

    console->Destroy();
    stats->Destroy();

//    pthumbwin->Destroy();
    delete pthumbwin;

    delete pAPilot;

    this->Destroy();

}

void MyFrame::OnSize(wxSizeEvent& event)
{
        int x,y;
        this->GetClientSize(&x, &y);

//      Resize the children
        int stat_height = 0;

        if(stats)
        {
                int yt = stats->GetFontHeight();
                stat_height = (yt + 6) * stats->GetRows();
        }

        int cccw, ccch;
        if(cc1)
        {
                if(Current_Ch)
                        Current_Ch->InvalidateCache();

                cccw = x * 10/10;               // constrain to mod 4
                int wr = cccw/4;
                cccw = wr*4;
                cccw += 2;                              // account for simple border

                ccch = y - stat_height;
                cc1->SetSize(0,0,cccw, ccch);


        }

        if(console)
        {
                console->Size_X = 160;
                console->Size_Y = y/2;
                console->Pos_X = cccw - console->Size_X;
                console->Pos_Y = 0;
                console->SetSize(console->Pos_X,console->Pos_Y,console->Size_X, console->Size_Y);
//                console->Show(false);

        }

        if(stats)
        {
                stats->Size_X = cccw;
                stats->Size_Y = stat_height;
                stats->Pos_X = 0;
                stats->Pos_Y = ccch;
                stats->SetSize(stats->Pos_X,stats->Pos_Y,stats->Size_X, stats->Size_Y);
                stats->Show(true);
                stats->FormatStat();
                stats->Refresh(true);
        }

        if(pthumbwin)
        {
              pthumbwin->SetMaxSize(cc1->GetSize());
        }

//  Rebuild the Toolbar
    if(toolBar)
        ReSizeToolbar();


}


void MyFrame::OnChar(wxKeyEvent &event)
{

}



void MyFrame::OnToolLeftClick(wxCommandEvent& event)
{

  switch(event.GetId())
  {
    case ID_STKUP:
            DoStackUp();
            break;


    case ID_STKDN:
            DoStackDown();
            break;



    case ID_WEST:
    {
//            int s = ps52plib->Color_Scheme;
//            if(++s == S52_COL_SCHEME_MAX)
//                    s = S52_DAY_BRIGHT;
//            ps52plib->Color_Scheme = (Col_Scheme_t)s;

//            if(Current_Ch)
//                Current_Ch->InvalidateCache();

//            cc1->SetbNewVP(true);
//            cc1->Refresh(FALSE);
            break;
    }

    case ID_ZOOMIN:
    {
            cc1->SetVPScale(cc1->GetVPScale() / 2);
            cc1->Refresh(false);
            break;
    }

    case ID_ZOOMOUT:
    {
            cc1->SetVPScale(cc1->GetVPScale() * 2);
            cc1->Refresh(false);
            break;
    }

    case ID_ROUTE:
        {
            nRoute_State = 1;
            cc1->SetMyCursor(cc1->pCursorPencil);
            break;
        }

    case ID_FOLLOW:
        {
            cc1->m_bFollow = true;
            toolBar->ToggleTool(ID_FOLLOW, true);
//      Warp speed jump to current position
            Current_Ch->InvalidateCache();            // Add back for wxx11 This might be needed??? 8/19/06
            cc1->SetViewPoint(vLat, vLon, cc1->GetVPScale(), 1, /*CURRENT_RENDER*/FORCE_SUBSAMPLE);            // set mod 4
            cc1->Refresh(false);
            break;
        }

#ifdef USE_S57
    case ID_TEXT:
        {
            ps52plib->SetShowS57Text(!ps52plib->GetShowS57Text());
            toolBar->ToggleTool(ID_TEXT, ps52plib->GetShowS57Text());
            Current_Ch->InvalidateCache();
            cc1->m_bForceReDraw = true;
            cc1->Refresh(false);
            break;
        }
#endif

    case ID_SETTINGS:
        {

            bool bnewtoolbar = DoOptionsDialog();

//              Apply various system settings
            ApplyGlobalSettings(true, bnewtoolbar);                 // flying update

            if(Current_Ch)
                Current_Ch->InvalidateCache();
            cc1->m_bForceReDraw = true;
            cc1->Refresh(false);
            break;
        }


    case ID_CURRENT:
        {
            if(!ptcmgr)                                                     // First time, init the manager
                ptcmgr = new TCMgr(*pTC_Dir, *pHome_Locn);


            if(ptcmgr->IsReady())
            {
                  cc1->bShowCurrent = !cc1->bShowCurrent;
                  toolBar->ToggleTool(ID_CURRENT, cc1->bShowCurrent);
                  Current_Ch->InvalidateCache();
                  cc1->m_bForceReDraw = true;
                  cc1->Refresh(false);
            }
            else
            {
                  wxLogMessage("Chart1::Event...TCMgr Not Available");
                  cc1->bShowCurrent = false;
                  toolBar->ToggleTool(ID_CURRENT, false);
            }
            break;

        }

    case ID_TIDE:
        {
                if(!ptcmgr)                                                     // First time, init the manager
                      ptcmgr = new TCMgr(*pTC_Dir, *pHome_Locn);


                if(ptcmgr->IsReady())
                {
                        cc1->bShowTide = !cc1->bShowTide;
                        toolBar->ToggleTool(ID_TIDE, cc1->bShowTide);
                        Current_Ch->InvalidateCache();
                        cc1->m_bForceReDraw = true;
                        cc1->Update();
                        cc1->Refresh(false);
                }
                else
                {
                        wxLogMessage("Chart1::Event...TCMgr Not Available");
                        cc1->bShowTide = false;
                        toolBar->ToggleTool(ID_TIDE, false);
                }
            break;

        }

    case ID_HELP:
      {
        about *pAboutDlg = new about(this, pSData_Locn);
        pAboutDlg->ShowModal();


        break;


      }

    case ID_PRINT:
      {
        DoPrint();
        break;
      }

     case ID_COLSCHEME:
        {
            ColorScheme s = GetColorScheme();
            int is = (int)s;
            is++;
            s = (ColorScheme)is;
            if(s == N_COLOR_SCHEMES)
                  s = COLOR_SCHEME_DEFAULT;

            SetAndApplyColorScheme(s);
            if(cc1)
            {
                  cc1->m_bForceReDraw = true;
                  cc1->Refresh(false);
            }

            break;
        }

    case ID_TBEXIT:
       {
         Close();
         break;
       }
  }         // switch


}


void MyFrame::ApplyGlobalSettings(bool bFlyingUpdate, bool bnewtoolbar)
{
 //             ShowDebugWindows
        if(pConfig->m_bShowDebugWindows)
        {
                stats->m_rows = 3;
                if(!pStatusBar)
                {
                        pStatusBar = CreateStatusBar(6);
                }


                Refresh();
        }
        else
        {
                stats->m_rows = 2;

                if(pStatusBar)
                {
                        pStatusBar->Destroy();
                        pStatusBar = NULL;
                        SetStatusBar(NULL);
                }
                Refresh();
        }

#ifdef __WXMSW__                          // This to recreate for Printer Icon
      if(bnewtoolbar)
      {
            DestroyMyToolbar();
            CreateMyToolbar();
      }
#endif

        if(bFlyingUpdate)
        {
                wxSizeEvent sevt;
                OnSize(sevt);
        }

}

int MyFrame::DoOptionsDialog()
{
      options *pSetDlg = new options(this, -1, "Options", *pInit_Chart_Dir);

//      Pass two working pointers for Chart Dir Dialog
      pSetDlg->SetCurrentDirListPtr(pChartDirArray);
      wxArrayString *pWorkDirArray = new wxArrayString;
      pSetDlg->SetWorkDirListPtr(pWorkDirArray);

//  Grab a copy of the current NMEA source and AP Port
      wxString previous_NMEA_source(*pNMEADataSource);
      wxString previous_NMEA_APPort(*pNMEA_AP_Port);

//      Pass a ptr to MyConfig, for updates
      pSetDlg->SetConfigPtr(pConfig);

      pSetDlg->SetInitialSettings();

      bDBUpdateInProgress = true;

      bool bPrevPrintIcon = g_bShowPrintIcon;

      int rr = pSetDlg->ShowModal();

      if(rr == 1)
      {
            if(*pChartDirArray != *pWorkDirArray)
            {
                  Timer1.Stop();                  // stop asynchronous activity

                  Current_Ch = NULL;

                  delete pCurrentStack;
                  pCurrentStack = NULL;

                  *pChartDirArray = *pWorkDirArray;

                  if(NULL == ChartData)
                       ChartData = new ChartDB(gFrame);
                  ChartData->Update(pChartDirArray);
                  ChartData->SaveBinary(pChartListFileName, pChartDirArray);

                  pConfig->UpdateChartDirs(pChartDirArray);

                  Timer1.Start(1000,wxTIMER_CONTINUOUS);

            }

            if(*pNMEADataSource != previous_NMEA_source)
            {
                  nmea->Close();
                  delete nmea;
                  nmea = new NMEAWindow(gFrame, *pNMEADataSource );
            }


            if(*pNMEA_AP_Port != previous_NMEA_APPort)
            {
                pAPilot->Close();
                delete pAPilot;
                pAPilot = new AutoPilotWindow(gFrame, *pNMEA_AP_Port );
            }


            pConfig->UpdateSettings();
      }


      delete pWorkDirArray;

      bDBUpdateInProgress = false;

      return(bPrevPrintIcon != g_bShowPrintIcon);       // indicate a change of toolbar is necessary

}




void MyFrame::ClearRouteTool()
{
        toolBar->ToggleTool(ID_ROUTE, false);
}


void MyFrame::DoStackDown(void)
{
        if(CurrentStackEntry)                   // not below 0
                SelectChartFromStack(CurrentStackEntry - 1);
}



void MyFrame::DoStackUp(void)
{
        if(CurrentStackEntry < pCurrentStack->nEntry-1)
                SelectChartFromStack(CurrentStackEntry + 1);
}






void MyFrame::OnTimer1(wxTimerEvent& event)
{

      g_tick++;

//      Listen for quitflag to be set, requesting application close
      if(quitflag)
      {
          wxLogMessage("Got quitflag from SIGUSR1");
          Timer1.Stop();
          Close();
          return;
      }

      if(bDBUpdateInProgress)
            return;

      Timer1.Stop();

//  Update and check watchdog timer for GPS data source
      gGPS_Watchdog--;

      if(gGPS_Watchdog <= 0)
          bGPSValid = false;

//      Update the Toolbar Status window the first time watchdog times out
      if(gGPS_Watchdog == 0)
          UpdateToolbarStatusWindow(Current_Ch);

//      Update the chart database and displayed chart
//      bool bnew_chart = DoChartUpdate(0);
      DoChartUpdate(0);

//      Update the active route, if any
      pRouteMan->UpdateProgress();

//      Update the memory status, and display

      int mem_current;
      GetMemoryStatus(mem_total, mem_current);

      if(pStatusBar)
      {
            char buf[40];
            sprintf(buf, "%3d/%3d/%3d", mem_initial/1024, mem_current/1024, mem_total/1024);

            SetStatusText(buf, 5);
      }

#ifdef AUTO_CONFIG_SAVE_MINUTES
//  Possibly save the current configuration
      if(0 == (g_tick % (AUTO_CONFIG_SAVE_MINUTES * 60)))
      {
        pConfig->UpdateSettings();
      }
#endif


      Timer1.Start(1000,wxTIMER_CONTINUOUS);

      if(1/*bnew_chart*/)
        cc1->Refresh(false);
      else
        cc1->RefreshRect(wxRect(0,0,1,1), false);

      console->Refresh(false);

      nBlinkerTick++;

}


void MyFrame::UpdateChartStatusField(int i)
{
        char buf[80], buf1[80];
        ChartData->ChartDB::GetChartID(pCurrentStack, CurrentStackEntry, buf);
        sprintf (buf1, "  %d/%d", CurrentStackEntry, pCurrentStack->nEntry-1);
        strcat(buf, "  ");
        strcat(buf, buf1);
        strcat(buf, "  ");

        ChartData->GetStackChartScale(pCurrentStack, CurrentStackEntry, buf1);
        strcat(buf, buf1);

        if(pStatusBar)
                SetStatusText(buf, i);

        stats->Refresh(false);

        ChartData->GetChartID(pCurrentStack, CurrentStackEntry, buf);

        stats->pTStat1->TextDraw(buf);

}


void RenderShadowText(wxDC *pdc, wxFont *pFont, char *str, int x, int y)
{
#ifdef DrawText
#undef DrawText
#define FIXIT
#endif

        wxFont oldfont = pdc->GetFont(); // save current font

        pdc->SetFont(*pFont);
        pdc->SetTextForeground(wxColour(255,255,255));
        pdc->SetBackgroundMode(wxTRANSPARENT);

        pdc->DrawText(str, x, y+1);
        pdc->DrawText(str, x, y-1);
        pdc->DrawText(str, x+1, y);
        pdc->DrawText(str, x-1, y);

        pdc->SetTextForeground(wxColour(0,0,0));

        pdc->DrawText(str, x, y);

        pdc->SetFont(oldfont);                  // restore last font

#ifdef FIXIT
#undef FIXIT
#define DrawText DrawTextA
#endif


}

#include "wx/encconv.h"

void MyFrame::UpdateToolbarStatusWindow(ChartBase *pchart, bool bSendSize)
{
    if(NULL == pchart)
        return;

#ifdef __WXMSW__
      int font1_size = 24;
      int font2_size = 10;
      int font3_size = 14;
#else
      int font1_size = 22;
      int font2_size = 12;
      int font3_size = 16;
#endif


//      Create a wxBitmap for the window
      wxBitmap tool_bm_dummy(tool_dummy_size_x, tool_dummy_size_y);

      int size_x = tool_dummy_size_x;
      int size_y = tool_dummy_size_y;

//      Draw the graphics
      wxMemoryDC dc;
      dc.SelectObject(tool_bm_dummy);

// First, clear background
// Using a color depending on the state of bGPSValid
      wxBrush *p_brush;
      if(bGPSValid)
          p_brush = wxTheBrushList->FindOrCreateBrush(wxColour(200,220,200), wxSOLID);
      else
          p_brush = wxTheBrushList->FindOrCreateBrush(wxColour(220,200,200), wxSOLID);

      dc.SetBackground(*p_brush);
      dc.Clear();

// Show Pub date
// Get a Font
      wxFont *pSWFont1;
      pSWFont1 = wxTheFontList->FindOrCreateFont(font1_size, wxDEFAULT,wxNORMAL, wxBOLD,
                  FALSE, wxString("Eurostile Extended"), wxFONTENCODING_SYSTEM );
      dc.SetFont(*pSWFont1);

//      Get and show the Chart Publish Date
      wxString pub_date;
      pchart->GetPubDate(pub_date);

      int w, h, descent;
      GetTextExtent(pub_date, &w, &h, &descent, NULL, pSWFont1);

      int date_locn = size_x - w - 2;
      RenderShadowText(&dc, pSWFont1, (char *)pub_date.c_str(), date_locn, size_y - h + descent);


//    Show File Name
      wxFont *pSWFont2;
//      pSWFont2 = wxTheFontList->FindOrCreateFont(font2_size, wxDEFAULT ,wxNORMAL, wxNORMAL,
//                                           FALSE, wxString("Eurostile Extended"));

      pSWFont2 = wxTheFontList->FindOrCreateFont(font2_size, wxDEFAULT ,wxNORMAL, wxNORMAL,
                  FALSE, wxString(""), wxFONTENCODING_SYSTEM );
      dc.SetFont(*pSWFont2);

//   Get and show the Chart FullPath
      wxString full_path;
      pchart->GetFullPath(full_path);

      int height_font_2;
      GetTextExtent(full_path, &w, &height_font_2, NULL, NULL, pSWFont2);

      dc.DrawText(full_path, 0, 0);


//    Show Chart Nice Name

//   Get and show the Chart Nice Name
      wxFont *pSWFont3;
      pSWFont3 = wxTheFontList->FindOrCreateFont(font3_size, wxDEFAULT,wxNORMAL, wxBOLD,
              FALSE, wxString("Eurostile Extended"), wxFONTENCODING_SYSTEM );
      dc.SetFont(*pSWFont3);


      //    The Chart Nice Name may be encoded with 8-bit ascii encoding set,
      //    especially some French chart names in NDI data sets.
      //    Use an Encoding Converter to ensure that the name string can be
      //    rendered in the selected font.  A simple brute force way is to
      //    convert the string to ISO8859_1, which will be renderable by
      //    all (??) installed system fonts.  There may be a more elegant way,
      //    for example, try to figure out the string encoding BEFORE specifying
      //    the font, and then FindOrCreate an appropriate font...  Todo Later.

      wxString name_possibly_intl;
      pchart->GetName(name_possibly_intl);

      wxEncodingConverter ec;
      ec.Init( wxFONTENCODING_ISO8859_2,  wxFONTENCODING_ISO8859_1, wxCONVERT_SUBSTITUTE);
      wxString name = ec.Convert(name_possibly_intl);

//    Possibly adjust the font?
      GetTextExtent(name, &w, &h, NULL, NULL, pSWFont3);
      if(w > date_locn)
      {
            dc.SetFont(*pSWFont2);
            GetTextExtent(name, &w, &h, NULL, NULL, pSWFont2);
            if(w > date_locn)                                     // still too long, so shorten it
            {
              wxString nameshort;
              int l = name.Len();
              l -= 3;
              while(l)              //ell
              {
                nameshort = name.Mid(0, l);
                nameshort.Append("...");
                GetTextExtent(nameshort, &w, &h, NULL, NULL, pSWFont2);
                if(w < date_locn)
                  break;
                l -= 1;
              }
              dc.DrawText(nameshort, 0, size_y - h);                  // properly placed
            }
            else
                  dc.DrawText(name, 0, size_y - h);

      }
      else
        dc.DrawText(name, 0, size_y - h);



//    Record the control's current position
      int ct_pos = toolBar->GetToolPos(ID_TBSTAT);
#ifdef __WXMSW__
      wxStaticBitmap *pt = ptool_ct_dummy;
#endif

//      Create the control
      ptool_ct_dummy = new wxStaticBitmap(toolBar, ID_TBSTAT, tool_bm_dummy,
                wxPoint(5000,5000), wxSize(size_x, size_y),wxSIMPLE_BORDER, _T("staticBitmap"));


      if(ct_pos != -1)
      {

//   Delete the current status tool
        toolBar->DeleteTool(ID_TBSTAT);
#ifdef __WXMSW__
        delete pt;
#endif

//      Insert the new control
            toolBar->InsertControl(ct_pos, ptool_ct_dummy);

 //     Realize the toolbar to reflect changes
        toolBar->Realize();
      }

      if(bSendSize)
        SendSizeEvent();
}


void MyFrame::SelectChartFromStack(int index)
{
        if(index < pCurrentStack->nEntry)
        {
            if(nmea)
                nmea->Pause();                  // Prevent any async interrupts/recursion

//      Open the new chart
            ChartBase *pTentative_Chart = ChartData->OpenChartFromStack(pCurrentStack, index);

            if(pTentative_Chart)
            {
                Current_Ch = pTentative_Chart;
                CurrentStackEntry = index;
            }

//      Update the Status Line
            UpdateChartStatusField(2);

//      Update the Toolbar Status window
            UpdateToolbarStatusWindow(Current_Ch);

//      Setup the view
            float zLat, zLon;
            if(cc1->m_bFollow)
                        { zLat = gLat; zLon = gLon;}
            else
                        { zLat = vLat; zLon = vLon;}


            if(Current_Ch->ChartType == CHART_TYPE_S57)
                cc1->SetViewPoint(zLat, zLon, cc1->GetVPChartScale(), 0, CURRENT_RENDER);
            else
            {
                  int target_scale = (int)(cc1->GetVPChartScale());

// calculate new chart conventional scale at 1x
                  double slat, slon_left, slon_right;
                  Current_Ch->pix_to_latlong(0, 0, &slat, &slon_left);
                  Current_Ch->pix_to_latlong(cc1->GetCanvas_width(), 0, &slat, &slon_right);
                  float ppdl = cc1->GetCanvas_width() / (slon_right - slon_left);
                  int conv_scale_at_1x = (int)(cc1->canvas_scale_factor / ppdl);

// try to match to the target when going to a smaller scale chart
                  if(conv_scale_at_1x < target_scale)
                  {
                    int scf = 1;
                    while(scf < 8)
                    {
                        if((conv_scale_at_1x * scf * 2) > target_scale)
                            break;
                        else
                            scf *= 2;
                    }
                    cc1->SetViewPoint(zLat, zLon, Current_Ch->GetNativeScale() * scf, 1, CURRENT_RENDER); //set mod 4
                  }

                  else
                      cc1->SetViewPoint(zLat, zLon, Current_Ch->GetNativeScale(), 1, CURRENT_RENDER);    // set mod 4
             }

        cc1->SetbNewVP(true);
        cc1->Refresh(FALSE);

        if(nmea)
            nmea->UnPause();
        }
}

void MyFrame::SetChartThumbnail(int index)
{

        if(bDBUpdateInProgress)
            return;

        if(NULL == pCurrentStack)
            return;

        if(NULL == pthumbwin)
            return;

        if(index == -1)
        {
                pthumbwin->pThumbChart = NULL;
                pthumbwin->Show(false);
                cc1->m_bForceReDraw = true;
                cc1->Refresh(FALSE);
        }

        else if(index < pCurrentStack->nEntry)
        {
                if(ChartData->GetCSChartType(pCurrentStack, index) != CHART_TYPE_S57)
                {
                        ChartBase *new_pThumbChart = ChartData->OpenChartFromStack(pCurrentStack, index);
                        if(new_pThumbChart)         // chart opened ok
                        {

                                ThumbData *pTD = new_pThumbChart->GetThumbData(200, 200, gLat, gLon);
                                if(pTD)
                                {
                                        pthumbwin->pThumbChart = new_pThumbChart;


                                        pthumbwin->Resize();
                                        pthumbwin->Show(true);
                                        pthumbwin->Refresh(FALSE);
                                }



                                else
                                {
                                      //Todo Make this a safe wxString, need overload for GetFullPath()
                                        char pFullPath[100];
                                        ChartData->GetFullPath(pCurrentStack, index, pFullPath);

                                        wxString msg(_T("Chart file corrupt.. disabling this chart \n"));
                                        msg.Append(wxString(pFullPath));
                                        wxLogMessage(msg.c_str());
                                        wxMessageDialog dlg(gFrame, msg, "OpenCPN Message", wxOK);
                                        dlg.ShowModal();
                                        ChartData->DisableChart(pFullPath);

                                        wxLogMessage("chart1.cpp:SetChartThumbnail...\
                                                                Could not create thumbnail");
                                        pthumbwin->pThumbChart = NULL;
                                        pthumbwin->Show(false);
                                        cc1->m_bForceReDraw = true;
                                        cc1->Refresh(FALSE);
                                }

                        }
                        else                            // some problem opening chart
                        {
                char buf[80];
                ChartData->GetFullPath(pCurrentStack, index, buf);
                                wxLogMessage("chart1.cpp:SetChartThumbnail...Could not open chart %s", buf);
                                pthumbwin->pThumbChart = NULL;
                                pthumbwin->Show(false);
                                cc1->m_bForceReDraw = true;
                                cc1->Refresh(FALSE);
                        }

                }
                else if(ChartData->GetCSChartType(pCurrentStack, index) == CHART_TYPE_S57)
                {
                        ChartBase *new_pThumbChart = ChartData->OpenChartFromStack(pCurrentStack, index,
                                        THUMB_ONLY);

                        if(new_pThumbChart)
                        {
                            ThumbData *pTD = new_pThumbChart->GetThumbData(200, 200, gLat, gLon);
                            if(pTD)
                            {
                                pthumbwin->pThumbChart = new_pThumbChart;

                                pthumbwin->Resize();
                                pthumbwin->Show(true);
                                pthumbwin->Refresh(FALSE);
                            }
                            cc1->m_bForceReDraw = true;
                            cc1->Refresh(FALSE);
                        }
                }


                else
                {
                        pthumbwin->pThumbChart = NULL;
                        pthumbwin->Show(false);
                        cc1->m_bForceReDraw = true;
                        cc1->Refresh(FALSE);
                }


        }

}


//----------------------------------------------------------------------------------
//      DoChartUpdate
//      Create a chartstack based on current lat/lon.
//      Update Current_Ch, using either current chart, if still in stack, or
//      smallest scale raster chart if not.
//      Return true if Current_Ch has been changed, implying need for a full redraw
//----------------------------------------------------------------------------------
bool MyFrame::DoChartUpdate(int bSelectType)
{
        float tLat, tLon;
        float new_scale;
        bool bNewChart = false;

        if(bDBUpdateInProgress)
                return false;

//      If in auto-follow mode, use the current glat,glon to build chart stack.
//      Otherwise, use vLat, vLon gotten from double-click on chart canvas, or other means

        if(cc1->m_bFollow == true)
        {
                tLat = gLat;
                tLon = gLon;
        }
        else
        {
                tLat = vLat;
                tLon = vLon;
        }

        // Build a chart stack based on tLat, tLon
        ChartStack *pWorkStack = new ChartStack;
        int l = ChartData->BuildChartStack(pWorkStack, tLat, tLon);

        if(l == 0)                                                                      // Bogus Lat, Lon?
        {
                if(NULL == pDummyChart)
                {
                        pDummyChart = new ChartDummy;

                        Current_Ch = pDummyChart;
                        float natural_scale = Current_Ch->GetNativeScale();

                        cc1->SetViewPoint(tLat, tLon, natural_scale, 0, CURRENT_RENDER);
                }

                else
                {
                        Current_Ch = pDummyChart;
                        cc1->SetViewPoint(tLat, tLon, cc1->GetVPScale(), 0, CURRENT_RENDER);
                }

                bNewChart = true;
                goto update_finish;
        }


        //              Check to see if Chart Stack has changed
        if(!ChartData->EqualStacks(pWorkStack, pCurrentStack))
        {

        //      New chart stack, so...

        //  Make sure the target stack is valid
                if(NULL == pCurrentStack)
                        pCurrentStack = new ChartStack;

        //      Copy the new stack into the target stack
                ChartData->CopyStack(pCurrentStack, pWorkStack);


        //      Note current scale
                float current_scale;
                if(Current_Ch)
                        current_scale = cc1->GetVPScale()/Current_Ch->GetNativeScale();
                else
                        current_scale = 1;

        //  Is Current Chart in new stack?

                int tEntry = -1;
                if(NULL != Current_Ch)                                  // this handles startup case
                        tEntry = ChartData->GetStackEntry(pCurrentStack, Current_Ch->pFullPath);

                if(tEntry != -1)                // Current_Ch is in the new stack
                {
                        CurrentStackEntry = tEntry;
                        new_scale = cc1->GetVPScale()/Current_Ch->GetNativeScale();
                        bNewChart = false;
                }

                else                            // Current_Ch is NOT in new stack
                {                                       // So, need to open a new chart
                                                        //      Find the smallest scale raster chart that opens OK
                  CurrentStackEntry = 0;
                  ChartBase *ptc = NULL;
                  while(CurrentStackEntry < pCurrentStack->nEntry)
                  {
                        if(ChartData->GetCSChartType(pCurrentStack, CurrentStackEntry) != CHART_TYPE_S57)
                        {
                              if ((ptc = ChartData->OpenChartFromStack(pCurrentStack, CurrentStackEntry)))
                              {
                                    new_scale = current_scale;              // Try to set scale to current value

// For Raster Charts, scale must be 1,2,4,8... etc.
                                    if(new_scale - floor(new_scale))
                                    {
                                          float sct = 1.0;
                                          while(sct < 16.0)
                                          {
                                                if(sct > new_scale)
                                                      break;
                                                sct *= 2;
                                          }
                                          new_scale = sct;
                                    }

                                    break;
                              }
                        }
                        CurrentStackEntry++;
                  }
                  Current_Ch = ptc;
                  bNewChart = true;
                }

        // Arriving here, Current_Ch is OK, or NULL
                if(NULL == Current_Ch)
                        CurrentStackEntry = 0;                                          // safe value

        // If NULL, there is just no raster chart available.  Punt...
                if(NULL == Current_Ch)
                {
                        wxMessageDialog mdlg(this,
                                        wxString("Unable to open any raster charts...Try to return to HomeBase?"),
                                        wxString("OpenCPN"),
                                        wxICON_ERROR | wxOK | wxCANCEL);

                        int dlg_ret = mdlg.ShowModal();

                        if(wxID_OK != dlg_ret)
                                quitflag++;                             // induce controlled exit if other than OK

//              Reset Lat/Lon to home position
//              This handles the case of "really lost..."
                        vLat = START_LAT;                               // display viewpoint
                        vLon = START_LON;

                        gLat = START_LAT;                               // GPS position, as default
                        gLon = START_LON;

                }

                if(NULL != Current_Ch)
                {
//    Chart stack has changed, and may be a new chart opened
                  if(bNewChart)
                  {
//    Update the Toolbar Status window
                      UpdateToolbarStatusWindow(Current_Ch);
                  }

//      Update the Status Line
                  UpdateChartStatusField(2);

//      Setup the view
                  float natural_scale = Current_Ch->GetNativeScale();
                  cc1->SetViewPoint(tLat, tLon, natural_scale * new_scale, 1, CURRENT_RENDER);  // set mod 4

                  stats->FormatStat();
                }
        }

        else                                                                    // No change in Chart Stack
        {
                if(cc1->m_bFollow)
                    cc1->SetViewPoint(tLat, tLon, cc1->GetVPScale(), 1, CURRENT_RENDER);
        }



update_finish:
        delete pWorkStack;

        return bNewChart;

}



void MyFrame::MouseEvent(wxMouseEvent& event)
{
        int x,y;
        event.GetPosition(&x, &y);


}


//      Linux memory monitor support

bool MyFrame::GetMemoryStatus(int& mem_total, int& mem_used)
{

//      Use filesystem /proc/meminfo to determine memory status

    char *p, buf[2000];
        int len;

//      Open and read the file
        int     fd = open("/proc/meminfo", O_RDONLY);

    if (fd == -1)
        {
                mem_total = 0;
                mem_used = 0;

        return false;
        }

    len = read(fd, buf, sizeof(buf) - 1);
    if (len <= 0) {
        close(fd);
        return false;
    }
    close(fd);
    buf[len] = 0;

    p = buf;

//      Parse the file contents
//      Here is an example....at least vaild for kernel 2.6
/*
MemTotal:       255684 kB
MemFree:          5996 kB
Buffers:         15260 kB
Cached:          99840 kB
SwapCached:         48 kB
Active:         176736 kB
Inactive:        45696 kB
HighTotal:           0 kB
HighFree:            0 kB
LowTotal:       255684 kB
LowFree:          5996 kB
SwapTotal:      610460 kB
SwapFree:       610412 kB
.
.
.
Hugepagesize:     4096 kB
*/

        char *s;
        char sbuf[100], stoken[20], skb[20];
        int sval, val_cnt;

        int m_total, m_active, m_inactive, m_buffers, m_cached, m_free;

        val_cnt = 0;

//      Loop on the whole file
        while(*p)
        {
//      Extract line by line
                s=sbuf;
                while ((*p != '\n') && *p)
                        *s++ = *p++;
                *s = 0;
                p++;                    // skip \n

//      Parse  the sbuf line
                sscanf(sbuf, "%s %d %s\n", stoken, &sval, skb);

//      Look for and extract the required numbers

                if(!strcmp(stoken, "MemTotal:"))
                {
                        m_total = sval;
                        val_cnt++;
                }
                else if(!strcmp(stoken, "Active:"))
                {
                        m_active = sval;
                        val_cnt++;
                }
                else if(!strcmp(stoken, "Inactive:"))
                {
                        m_inactive = sval;
                        val_cnt++;
                }
                else if(!strcmp(stoken, "Buffers:"))
                {
                        m_buffers = sval;
                        val_cnt++;
                }
                else if(!strcmp(stoken, "Cached:"))
                {
                        m_cached = sval;
                        val_cnt++;
                }

                else if(!strcmp(stoken, "MemFree:"))
                {
                        m_free = sval;
                        val_cnt++;
                }

                if(val_cnt == 6)
                        break;
        }

//      Do the math....

//      int m_used = m_active + m_inactive - (m_buffers + m_cached);
//      mem_used = m_used;

        //      Maybe a good estimate of actual RAM available
        mem_used = (m_total - m_free) - (m_cached + m_buffers);

        mem_total = m_total;

        return true;

}

void MyFrame::DoPrint(void)
{

    wxPrintDialogData printDialogData(* g_printData);
    printDialogData.EnablePageNumbers(false);

    wxPrinter printer(& printDialogData);

    MyPrintout printout(_T("Chart Print"));
    if (!printer.Print(this, &printout, true ))
    {
        if (wxPrinter::GetLastError() == wxPRINTER_ERROR)
            wxMessageBox(_T("There was a problem printing.\nPerhaps your current printer is not set correctly?"), _T("OpenCPN"), wxOK);
//        else
//            wxMessageBox(_T("Print Cancelled"), _T("OpenCPN"), wxOK);
    }
    else
    {
        (*g_printData) = printer.GetPrintDialogData().GetPrintData();
    }


// Pass two printout objects: for preview, and possible printing.
/*
    wxPrintDialogData printDialogData(* g_printData);
    wxPrintPreview *preview = new wxPrintPreview(new MyPrintout, new MyPrintout, & printDialogData);
    if (!preview->Ok())
    {
        delete preview;
        wxMessageBox(_T("There was a problem previewing.\nPerhaps your current printer is not set correctly?"), _T("Previewing"), wxOK);
        return;
    }

    wxPreviewFrame *frame = new wxPreviewFrame(preview, this, _T("Demo Print Preview"), wxPoint(100, 100), wxSize(600, 650));
    frame->Centre(wxBOTH);
    frame->Initialize();
    frame->Show();
*/

}

//---------------------------------------------------------------------------------------------------------
//
//              Private Memory Management
//
//---------------------------------------------------------------------------------------------------------


void *x_malloc(size_t t)
{
        void *pr = malloc(t);

        //      malloc fails
        if(NULL == pr)
        {
                wxLogMessage("x_malloc...malloc fails with request of %d bytes.", t);

                // Cat the /proc/meminfo file

                char *p, buf[2000];
                int len;

                int     fd = open("/proc/meminfo", O_RDONLY);

                if (fd == -1)
                        exit(1);

                len = read(fd, buf, sizeof(buf) - 1);
                if (len <= 0) {
                        close(fd);
                        exit(1);
                }
                close(fd);
                buf[len] = 0;

                p=buf;
                while(*p)
                {
                        printf("%c", *p++);
                }


                exit(0);
                return NULL;                            // for MSVC
        }

        else
        {
                if(t > malloc_max)
                {
                        malloc_max = t;
//                      wxLogMessage("New malloc_max: %d", malloc_max);
                }

                return pr;                                      // good return
        }

}


void MyFrame::OnEvtNMEA(wxCommandEvent & event)
{
        char buf[4096];

        switch(event.GetExtraLong())
        {
            case EVT_NMEA_PARSE_RX:
            {
                if(ps_mutexProtectingTheRXBuffer->Lock() == wxMUTEX_NO_ERROR )
                {
                        if(RX_BUFFER_FULL == rx_share_buffer_state)
                        {
                                strcpy (buf, rx_share_buffer);
                                rx_share_buffer_state = RX_BUFFER_EMPTY;

                                if(rx_share_buffer_length != strlen(rx_share_buffer))
                                        wxLogMessage("Got NMEA Event with inconsistent rx_share_buffer");
                        }
                        else
                                wxLogMessage("Got NMEA Event with RX_BUFFER_EMPTY");

                        ps_mutexProtectingTheRXBuffer->Unlock();
                }


                if(pStatusBar)
                {
                    wxString buf_nolf(buf);
                    buf_nolf.RemoveLast();
                    SetStatusText(buf_nolf.c_str(), 4);
                }

//                printf("%s", buf);

                *pNMEA0183 << buf;
                pNMEA0183->Parse();

                if(pNMEA0183->LastSentenceIDReceived == _T("RMC"))
                {
                        if(pNMEA0183->Rmc.IsDataValid == NTrue)
                        {
                                float llt = pNMEA0183->Rmc.Position.Latitude.Latitude;
                                int lat_deg_int = (int)(llt / 100);
                                float lat_deg = lat_deg_int;
                                float lat_min = llt - (lat_deg * 100);
                                gLat = lat_deg + (lat_min/60.);

                                float lln = pNMEA0183->Rmc.Position.Longitude.Longitude;
                                int lon_deg_int = (int)(lln / 100);
                                float lon_deg = lon_deg_int;
                                float lon_min = lln - (lon_deg * 100);
                                float tgLon = lon_deg + (lon_min/60.);
                                gLon = -tgLon;

                                gSog = pNMEA0183->Rmc.SpeedOverGroundKnots;
                                gCog = pNMEA0183->Rmc.TrackMadeGoodDegreesTrue;

                                bool last_bGPSValid = bGPSValid;
                                bGPSValid = true;
                                if(!last_bGPSValid)
                                    UpdateToolbarStatusWindow(Current_Ch);

                                gGPS_Watchdog = GPS_TIMEOUT_SECONDS;
                        }

                }
                break;
            }       //case

            case EVT_NMEA_DIRECT:
            {
                bool last_bGPSValid = bGPSValid;
                bGPSValid = true;
                if(!last_bGPSValid)
                    UpdateToolbarStatusWindow(Current_Ch);

                gGPS_Watchdog = GPS_TIMEOUT_SECONDS;

                break;
            }

        }           // switch
}

//----------------------------------------------------------------------------------------------------------
//      Application-wide CPL Error handler
//----------------------------------------------------------------------------------------------------------

void MyCPLErrorHandler( CPLErr eErrClass, int nError,
                             const char * pszErrorMsg )

{

    if( eErrClass == CE_Debug )
                wxLogMessage("CPL: %s", pszErrorMsg);
    else if( eErrClass == CE_Warning )
                wxLogMessage("CPL Warning %d: %s", nError, pszErrorMsg);
    else
                wxLogMessage("CPL ERROR %d: %s", nError, pszErrorMsg);

}

//----------------------------------------------------------------------------------------------------------
//      Printing Framework Support
//----------------------------------------------------------------------------------------------------------

bool MyPrintout::OnPrintPage(int page)
{
    wxDC *dc = GetDC();
    if (dc)
    {
        if (page == 1)
            DrawPageOne(dc);

        return true;
    }
    else
        return false;
}

bool MyPrintout::OnBeginDocument(int startPage, int endPage)
{
    if (!wxPrintout::OnBeginDocument(startPage, endPage))
        return false;

    return true;
}

void MyPrintout::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo)
{
    *minPage = 0;
    *maxPage = 1;
    *selPageFrom = 1;
    *selPageTo = 1;
}

bool MyPrintout::HasPage(int pageNum)
{
    return (pageNum == 1);
}

void MyPrintout::DrawPageOne(wxDC *dc)
{

    // Get the Size of the Chart Canvas
    int sx, sy;
    cc1->GetClientSize(&sx, &sy);                       // of the canvas

    float maxX = sx;
    float maxY = sy;

    // Let's have at least 50 device units margin
    float marginX = 50;
    float marginY = 50;

    // Add the margin to the graphic size
    maxX += (2*marginX);
    maxY += (2*marginY);

    // Get the size of the DC in pixels
    int w, h;
    dc->GetSize(&w, &h);

    // Calculate a suitable scaling factor
    float scaleX=(float)(w/maxX);
    float scaleY=(float)(h/maxY);

    // Use x or y scaling factor, whichever fits on the DC
    float actualScale = wxMin(scaleX,scaleY);

    // Calculate the position on the DC for centring the graphic
    float posX = (float)((w - (maxX*actualScale))/2.0);
    float posY = (float)((h - (maxY*actualScale))/2.0);

    // Set the scale and origin
    dc->SetUserScale(actualScale, actualScale);
    dc->SetDeviceOrigin( (long)posX, (long)posY );

//  Get the latest bitmap as rendered by the ChartCanvas
//  And Blit/scale it onto the Printer DC
    wxMemoryDC mdc;
    mdc.SelectObject(*(cc1->pscratch_bm));

    dc->Blit(0,0,cc1->pscratch_bm->GetWidth(),cc1->pscratch_bm->GetHeight(),&mdc, 0, 0);
    mdc.SelectObject(wxNullBitmap);

}


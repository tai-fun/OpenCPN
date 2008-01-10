/******************************************************************************
 * $Id: chart1.cpp,v 1.17 2008/01/10 03:35:45 bdbcat Exp $
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
 * Revision 1.17  2008/01/10 03:35:45  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.15  2007/06/15 03:07:15  bdbcat
 * Improve toolbar color scheme support
 *
 * Revision 1.14  2007/06/10 03:19:29  bdbcat
 * Fix Leaks
 *
 * Revision 1.13  2007/06/10 02:24:17  bdbcat
 * Implement global color scheme
 *
 * Revision 1.12  2007/05/03 13:23:55  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.11  2007/03/02 02:09:06  dsr
 * Cleanup, convert to UTM Projection
 *
 * Revision 1.10  2007/02/06 02:07:39  dsr
 * Pause event generators during Settings Dialog
 *
 * Revision 1.9  2006/11/01 02:15:58  dsr
 * AIS Support
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
#include "wx/stdpaths.h"


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
#include "options.h"
#include "about.h"
#include "thumbwin.h"
#include "tcmgr.h"
#include "cpl_error.h"
#include "ais.h"
#include "chartimg.h"               // for ChartBaseBSB

#ifdef __WXMSW__
#include <wx/image.h>
#endif

#ifdef __WXMAC__                          // begin rms
#include <wx/image.h>
#endif                                    // end rms

// begin rms
#ifdef __WXOSX__
#include "macutils.h"
#endif
// end rms

#ifdef USE_S57
#include "s52plib.h"
#include "s57chart.h"
#endif

#ifdef USE_WIFI_CLIENT
#include "wificlient.h"
#endif

//#include <mcheck.h>


//------------------------------------------------------------------------------
//      Static variable definition
//------------------------------------------------------------------------------
CPL_CVSID("$Id: chart1.cpp,v 1.17 2008/01/10 03:35:45 bdbcat Exp $");

//      These static variables are required by something in MYGDAL.LIB...sigh...

#ifdef __WXMSW__
        int errno;
#endif

double _HUGE;


FILE            *flog;                  // log file
wxLog           *logger;
wxLog           *Oldlogger;

MyFrame         *gFrame;

ChartCanvas     *cc1;
ConsoleCanvas   *console;
NMEAWindow      *nmea;
StatWin         *stats;

wxToolBar       *toolBar;

MyConfig        *pConfig;

ChartBase       *Current_Vector_Ch;
ChartBase       *Current_Ch;
ChartDB         *ChartData;
ChartStack      *pCurrentStack;
int             CurrentStackEntry;
wxString        *pdir_list[20];

RouteList       *pRouteList;

Select          *pSelect;
Select          *pSelectTC;
Select          *pSelectAIS;

Routeman        *pRouteMan;
NMEA0183        *pNMEA0183;

float           gLat, gLon, gCog, gSog, gHdg;
float           kLat, kLon, kCog, kSog, kHdg;
float           vLat, vLon;
double          initial_scale_ppm;

wxArrayString   *pChartDirArray;
bool            bDBUpdateInProgress;

ThumbWin        *pthumbwin;
TCMgr           *ptcmgr;

bool            bAutoPilotOut;
bool            bDrawCurrentValues;

wxString        *pSData_Locn;
wxString        *pChartListFileName;
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

bool            s_bSetSystemTime;

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
bool            g_bShowOutlines;
bool            g_bShowDepthUnits;

FontMgr         *pFontMgr;

ColorScheme     global_color_scheme;

int             gsp_watchdog_timeout_ticks;
int             gGPS_Watchdog;
bool            bGPSValid;

#ifdef USE_S57
s52plib         *ps52plib;
// begin rms
#elif defined __WXOSX__
s52plib         *ps52plib;
// end rms
#endif

#ifdef USE_WIFI_CLIENT
WIFIWindow      *pWIFI;
#endif



static wxString *pval;          // Private environment temp storage

#ifdef __WXOSX__
NOTE   Something wrong with the diff patch here.  Looks odd, please check
#endif

// begin rms
#if defined( USE_S57) || defined ( __WXOSX__ )
#ifdef __WXMSW__
#ifdef USE_GLU_TESS
#ifdef USE_GLU_DLL
// end rms
extern bool           s_glu_dll_ready;
extern HINSTANCE      s_hGLU_DLL;                   // Handle to DLL
#endif
#endif
#endif
#endif


OCP_AIS_Thread  *pAIS_Thread;
AIS_Decoder     *pAIS;
wxString        *pAIS_Port;

bool            s_socket_test_running;
bool            s_socket_test_passed;
wxSocketClient  *s_t_sock;
wxSocketServer  *s_s_sock;

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

// begin rms
#if defined(__WXOSX__) || defined(__LINUX__)
// Mutex to handle state setup for sending GPS events to the main thread
// this allows us to make sure that a message is completely processed before sending another one.
wxMutex           s_pmutexNMEAEventState;
int               g_iNMEAEventState = NMEA_STATE_NONE ;
wxDateTime*       g_pMMEAeventTime = NULL ;
uint64_t          g_ulLastNEMATicktime = 0 ;
#endif
// end rms


static char nmea_tick_chars[] = {'|', '/', '-', '\\', '|', '/', '-', '\\'};
static int tick_idx;

#ifdef __MSVC__
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif


#ifdef __WXUNIVERSAL__
WX_USE_THEME(gtk);
WX_USE_THEME(Metal);
#endif

#ifdef __WXMSW__
     extern  long  __stdcall MyUnhandledExceptionFilter( struct _EXCEPTION_POINTERS *ExceptionInfo );
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
#ifndef __WXMSW__
//      SIGUSR1
//      Raised externally to cause orderly termination of application
//      Intended to act just like pushing the "EXIT" button

static void
catch_sig_usr1(int signo)
{
        quitflag++;                             // signal to the timer loop
}
#endif


// `Main program' equivalent, creating windows and returning main app frame
//------------------------------------------------------------------------------
// MyApp
//------------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

#ifdef __WXMSW__
    //testing
//    _controlfp( _EM_INVALID | _EM_DENORMAL /*| _EM_ZERODIVIDE*/
//    | _EM_OVERFLOW | _EM_UNDERFLOW |_EM_INEXACT, _MCW_EM );

      //    Handle any Floating Point Exceptions which may leak thru from other
      //    processes.  The exception filter is in cutil.c
    //  Dunno why it wont link in MSVC.....
#ifndef __MSVC__
    SetUnhandledExceptionFilter( &MyUnhandledExceptionFilter );
#endif
#endif


//      _CrtSetBreakAlloc(3868);

#ifdef __MSVC__
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

//      Initialize memory tracer
#ifndef __WXMSW__
//        mtrace();
#endif

//      Here is some experimental code for wxTheme support
//      Not also these lines included above....
//      They are necessary to ensure that the themes are statically loaded

//      #ifdef __WXUNIVERSAL__
//      WX_USE_THEME(gtk);
//      WX_USE_THEME(Metal);
//      #endif

#ifdef __WXUNIVERSAL__
//        wxTheme* theme = wxTheme::Create("gtk");
//        wxTheme::Set(theme);
#endif


//      Init the private memory manager
        malloc_max = 0;

//      wxHandleFatalExceptions(true);


//      Init the private environment handler
        pval = new wxString;

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
///   This will point to the application (opencpn.exe) directory in Windows
        wxStandardPaths std_path;
        std_path.Get();
        pHome_Locn->Append(std_path.GetDataDir());
        pHome_Locn->Append("\\");
#else
        pHome_Locn->Append(::wxGetHomeDir());                   // in the current users home
        pHome_Locn->Append("/");
#endif


//      Establish Log File location
 // begin rms
#ifdef __WXMAC__
        pHome_Locn->Append("openCPNfiles/");                                    // avoid clutter in the home directory
            // create the directory if we need too
        wxFileName wxHomeFiledir(*pHome_Locn) ;
                  if(true != wxHomeFiledir.DirExists(wxHomeFiledir.GetPath()))
                                if(!wxHomeFiledir.Mkdir(wxHomeFiledir.GetPath()))
                                {
                         wxASSERT_MSG(false,"Cannot create config file directory for log directory");
                                     return false ;
                                }
#endif // end rms

        wxString log(*pHome_Locn);
        log.Append("opencpn.log");
        flog = fopen(log.c_str(), "a");
        logger=new wxLogStderr(flog);

        Oldlogger = wxLog::SetActiveTarget(logger);

//        wxLog::AddTraceMask("timer");               // verbose message traces to log output


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
        pAIS_Port = new wxString();
        pcsv_locn = new wxString();


//      Init the Chart Dir Array(s)
        pChartDirArray = new wxArrayString();

//      Init the Selectable Route Items List
        pSelect = new Select();

//      Init the Selectable Tide/Current Items List
        pSelectTC = new Select();

//      Init the Selectable AIS Target List
        pSelectAIS = new Select();

//      Init the Route Manager
        pRouteMan = new Routeman();


//      Who am I?
        phost_name = new wxString(::wxGetHostName());


//      (Optionally) Capture the user and file(effective) ids
//  Some build environments may need root privileges for hardware
//  port I/O, as in the NMEA data input class.  Set that up here.


#ifndef __WXMSW__
        user_user_id = getuid ();
#if 1
        file_user_id = geteuid ();
    #else
        file_user_id = user_user_id;
    #endif
#endif



//      Establish a "shared data" location
        pSData_Locn= new wxString;
#ifdef __WXMSW__
        pSData_Locn->Append(std_path.GetDataDir());
        pSData_Locn->Append("\\");

// begin rms
#elif defined __WXMAC__
        // put in common directory for the user
        pSData_Locn = pHome_Locn ;
// end rms
#else
        pSData_Locn->Append(wxString(INSTALL_PREFIX "/share/opencpn/"));    // ./configure script sets this
#endif


//      Establish the location of the config file
#ifdef __WXMSW__
        wxString Config_File("opencpn.ini");
        Config_File.Prepend(*pHome_Locn);
 // begin rms
#elif defined __WXMAC__
        wxString Config_File("opencpn.ini");
        Config_File.Prepend(*pHome_Locn);
// end rms
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
// begin rms
#ifdef __WXMAC__
                   if(true != config_test_file_name.DirExists(config_test_file_name.GetPath()))
                                if(!config_test_file_name.Mkdir(config_test_file_name.GetPath()))
                         wxLogMessage("Cannot create config file directory for %s", Config_File.c_str());
#else
              else
              {
#endif // end rms
                   Config_File.Clear();
                   return false;                    // Probably will provoke some memory leakage....
              }
        }

//      Open/Create the Config Object
        MyConfig *pCF = new MyConfig(wxString(""), wxString(""), Config_File);
        pConfig = (MyConfig *)pCF;
        pConfig->LoadMyConfig(0);


#ifdef USE_S57
//      Init the s57 chart object, specifying the location of the required csv files
//      and error log.

//      If the config file contains an entry for s57 .csv files, use it.
//      Otherwise, default to [shared data dir]/s57_data
        if(pcsv_locn->IsEmpty())
        {
            pcsv_locn->Append(*pSData_Locn);
            pcsv_locn->Append("s57data");
        }

// Todo Maybe verify that the required support files are really present in pcsv_locn
// If not, then look in fixed location *pSData_Locn/s57data

        // s57attributes.csv
        // attdecode.csv
        // s57expectedinput.csv
        // s57objectclasses.csv
        // S52RAZDS.RLE
        // SP52COL.DAT

        ps52plib = new s52plib(*pcsv_locn, _T("/S52RAZDS.RLE"), _T("/SP52COL.DAT"));

        //  If the library load failed, try looking for the s57 data elsewhere
        if(!ps52plib->m_bOK)
        {
            delete ps52plib;

            pcsv_locn->Clear();
            pcsv_locn->Append(*pSData_Locn);
            pcsv_locn->Append("s57data");

            wxLogMessage("Looking for s57data in %s", pcsv_locn->c_str());
            ps52plib = new s52plib(*pcsv_locn, _T("/S52RAZDS.RLE"), _T("/SP52COL.DAT"));

            if(!ps52plib->m_bOK)
            {
                wxLogMessage("S52PLIB Initialization failed, disabling S57 charts...");
            }
        }

// Todo Maybe initialize only when an s57 chart is actually opened???
        s57_initialize(*pcsv_locn, flog);


#endif  // S57


// Set default color scheme
        global_color_scheme = GLOBAL_COLOR_SCHEME_DAY;


//      Establish location and name of chart database
#ifdef __WXMSW__
        pChartListFileName = new wxString("CHRTLIST.DAT");
 // begin rms
#elif defined __WXMAC__
        pChartListFileName = new wxString("/chartlist.dat");
//end rms
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


        //  Set up the frame initial visual parameters
// begin rms
#ifdef __WXOSX__
          if (false == ValidateSerialPortName(pNMEADataSource->c_str(),MAX_SERIAL_PORTS))
                  *pNMEADataSource = _T("NONE") ;
#endif
// end rms
//      Default size, resized later
        wxSize new_frame_size(-1, -1);
        int cx, cy, cw, ch;
        ::wxClientDisplayRect(&cx, &cy, &cw, &ch);

//  For Windows and GTK, provide the expected application Minimize/Close bar
       long app_style = wxDEFAULT_FRAME_STYLE;

#ifdef __WXX11__
        app_style = (wxSIMPLE_BORDER | wxCLIP_CHILDREN | wxRESIZE_BORDER);

        //      Here is a specific size set for my (dsr) specific imbedded X11 environment
        new_frame_size.Set(cw, 735);
///        new_frame_size.Set(cw, ch);
#else
        new_frame_size.Set(cw * 7/10, ch * 7/10);
#endif


// Create the main frame window
        gFrame = new MyFrame(NULL, _T("OpenCPN"), wxPoint(0, 0), new_frame_size, app_style );


//      Create Children of Frame
//              n.b.  if only one child exists, wxWindows expands the child
//                        to the parent client area automatically, (as a favor?)
//                        Here, we'll do explicit sizing on SIZE events

        cc1 =  new ChartCanvas(gFrame);                         // the chart display canvas
        if(cc1)
        {
            cc1->m_bFollow = pConfig->st_bFollow;               // set initial state
            cc1->VPoint.view_scale_ppm = initial_scale_ppm;
        }

        console = new ConsoleCanvas(gFrame);                    // the console

        stats = new StatWin(gFrame);

        nmea = new NMEAWindow(ID_NMEA_WINDOW, gFrame, *pNMEADataSource);

//        pAIS = new AIS_Decoder(ID_AIS_WINDOW, gFrame, wxString("TCP/IP:66.235.48.168"));  // a test
        pAIS = new AIS_Decoder(ID_AIS_WINDOW, gFrame, *pAIS_Port);

        pAPilot = new AutoPilotWindow(gFrame, *pNMEA_AP_Port);
// begin rms
#ifdef __WXOSX__
          if (false == ValidateSerialPortName(pAIS_Port->c_str(),MAX_SERIAL_PORTS))
                  *pNMEADataSource = _T("NONE") ;
#endif
            // end rms

#ifdef USE_WIFI_CLIENT
            // begin rms
#ifdef __WXOSX__
          if (false == ValidateSerialPortName(pNMEA_AP_Port->c_str(), MAX_SERIAL_PORTS))
                  *pNMEADataSource = _T("NONE") ;
#endif
            // end rms
        pWIFI = new WIFIWindow(gFrame, *pWIFIServerName );
#endif

        pNMEA0183 = new NMEA0183();

        pthumbwin = new ThumbWin(gFrame);

        gFrame->ApplyGlobalSettings(1, true);               // done once on init with resize

        gFrame->SetAndApplyColorScheme(global_color_scheme);

// Show the frame
        gFrame->Show(TRUE);

#ifndef __WXMSW__
        gFrame->Maximize(true);
#endif


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

//      establish GPS timeout value as multiple of frame timer
        gsp_watchdog_timeout_ticks = (GPS_TIMEOUT_SECONDS * 1000) / TIMER_GFRAME_1;

//      Start up the ticker....
        gFrame->FrameTimer1.Start(TIMER_GFRAME_1,wxTIMER_CONTINUOUS);

   return TRUE;
}



int MyApp::OnExit()
{
        wxLogMessage("opencpn exiting cleanly...\n");
        delete pConfig;
        delete pSelect;
        delete pSelectTC;
        delete pSelectAIS;

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
        delete pHome_Locn;
        delete pSData_Locn;
        delete pcsv_locn;
        delete pTC_Dir;
        delete phost_name;
        delete pInit_Chart_Dir;
        delete pWVS_Locn;
        delete pval;

        delete pNMEADataSource;
        delete pNMEA_AP_Port;
        delete pAIS_Port;

        delete pWIFIServerName;

        delete pFontMgr;

#ifdef USE_S57
#ifdef __WXMSW__
#ifdef USE_GLU_TESS
#ifdef USE_GLU_DLL
        if(s_glu_dll_ready)
            FreeLibrary(s_hGLU_DLL);           // free the glu32.dll
#endif
#endif
#endif
#endif


//        _CrtDumpMemoryLeaks( );

        return TRUE;
}


void MyApp::TestSockets(void)
{
//      wxWidgets for X11, starting with version 2.6 and extending however
//      long, has a problem handling TCP/IP socket events.
//      The problem relates to wxHashTable::Next()
//      There is a workaround:  configure wxWidgets with --enable-compat24
//      Anyway, we'll test here to be sure sockets work HERE.
//      If they don't, we shall have to disable GPSD data input support


//  Create a dynamic event handler in MyApp for wxSocketServer events
        Connect( wxID_ANY, wxEVT_SOCKET, wxSocketEventHandler(MyApp::OnSocketEvent) );

//      Make a localhost server
        wxIPV4address serv_addr;
        serv_addr.Service(3001);

        s_s_sock = new wxSocketServer(serv_addr);
        s_s_sock->SetEventHandler(*this, wxID_ANY);

        s_s_sock->SetNotify(wxSOCKET_CONNECTION_FLAG);
        s_s_sock->Notify(TRUE);

// Create the test client socket
        s_t_sock = new wxSocketClient();

//      Connect() the test socket

        wxIPV4address addr;
        addr.AnyAddress();
        addr.Service(3001);

        s_socket_test_running = true;
        s_socket_test_passed = false;

        s_t_sock->Connect(addr, FALSE);       // Non-blocking connect

//    Sleep and loop for N seconds
#define SLEEP_TEST_SEC  1
        for(int is=0 ; is<SLEEP_TEST_SEC * 10 ; is++)
{
    wxMilliSleep(100);
}

// Test requires at least one pass thru event loop.  Test will finish in first MyFrame::OnTimer

}



void MyApp::OnSocketEvent(wxSocketEvent& event)
//  Used for testing wxSocketClient event handling
{

    switch(event.GetSocketEvent())
    {
        case wxSOCKET_CONNECTION :
        case wxSOCKET_INPUT:
        case wxSOCKET_OUTPUT:
        case wxSOCKET_LOST:

            s_socket_test_passed = true;
            break;
    }
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
  EVT_TIMER(FRAME_TIMER_1, MyFrame::OnFrameTimer1)
  EVT_ACTIVATE(MyFrame::OnActivate)
  EVT_COMMAND(ID_NMEA_WINDOW, EVT_NMEA, MyFrame::OnEvtNMEA)
END_EVENT_TABLE()


// My frame constructor
MyFrame::MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
  wxFrame(frame, -1, title, pos, size, style)  //wxSIMPLE_BORDER | wxCLIP_CHILDREN | wxRESIZE_BORDER)
      //wxCAPTION | wxSYSTEM_MENU | wxRESIZE_BORDER
{
        m_pStatusBar = NULL;

        PrepareToolbarBitmaps();

        //      Redirect the global heartbeat timer to this frame
        FrameTimer1.SetOwner(this, FRAME_TIMER_1);

        //      Set up some assorted member variables
        nRoute_State = 0;
        m_bTimeIsSet = false;

        m_ptool_ct_dummy = NULL;
        m_phash = NULL;

//  Initialize the Printer data structures

//wxGTK 2.8.0 enables gnomeprint by default.  No workee under KDevelop....

#ifdef __WXDEBUG
        if( wxPORT_GTK != pPlatform->GetPortId())
        {
            g_printData = new wxPrintData;
            g_printData->SetOrientation(wxLANDSCAPE);
            g_pageSetupData = new wxPageSetupDialogData;
        }
#else
        g_printData = new wxPrintData;
        g_printData->SetOrientation(wxLANDSCAPE);
        g_pageSetupData = new wxPageSetupDialogData;

#endif

}

MyFrame::~MyFrame()
{
        FrameTimer1.Stop();
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

        Refresh(false);
    }
}


ColorScheme MyFrame::GetColorScheme()
{
       return global_color_scheme;
}

void MyFrame::SetAndApplyColorScheme(ColorScheme cs)
{
      global_color_scheme = cs;

      wxColour back_color;
      switch(cs)
      {
          case GLOBAL_COLOR_SCHEME_DAY:
              back_color = wxColour(150,150,150);
              break;
          case GLOBAL_COLOR_SCHEME_DUSK:
              back_color = wxColour(128,128,128);
              break;
          case GLOBAL_COLOR_SCHEME_NIGHT:
              back_color = wxColour(64,64,64);
              break;
          default:
              back_color = wxColour(150,150,150);
              break;
      }

      if(ChartData)
            ChartData->ApplyColorSchemeToCachedCharts(cs);

      if(stats)
          stats->SetColorScheme(cs);

      if(console)
          console->SetColorScheme(cs);

      if(m_pStatusBar != NULL)
      {
          m_pStatusBar->SetBackgroundColour(back_color);

          //    As an optimization, if color scheme is anything other than GLOBAL_COLOR_SCHEME_DAY,
          //    adjust the status bar field styles to be simple flat fields, with no unmanageable 3-D
          //    effects.

          int sb_style;
          if(cs == GLOBAL_COLOR_SCHEME_DAY)
              sb_style = wxSB_NORMAL;
          else
              sb_style = wxSB_FLAT;

          int sb_styles[N_STATUS_BAR_FIELDS_MAX];
          for(int i=0 ; i<m_StatusBarFieldCount ; i++)
          {
              if(i < N_STATUS_BAR_FIELDS_MAX)
                  sb_styles[i] = sb_style;
          }

          m_pStatusBar->SetStatusStyles(m_StatusBarFieldCount, (const int *)&sb_styles[0]);

          m_pStatusBar->Refresh();
      }

      UpdateToolbar(cs);
      UpdateToolbarStatusWindow(Current_Ch, true);
}

void MyFrame::DestroyMyToolbar()
{
    delete m_ptool_ct_dummy;
    delete toolBar;
}


wxToolBar *MyFrame::CreateAToolbar()
{
   wxToolBar *tb;

    long style = 0;
    style |= wxTB_HORIZONTAL ;
    m_ptool_ct_dummy = NULL;

    tb = new wxToolBar(this, -1, wxPoint(-1, -1), wxSize(-1, -1), wxTB_HORIZONTAL | wxNO_BORDER);

    tb->SetToolBitmapSize(wxSize(32,32));
    tb->SetRows(1);


//Set up the ToolBar

//      Think about wxUNIV themes here....


//      Set up the margins, etc...
//      All this is poorly documented, and very clumsy
//      see the wx src files

//  On MSW, ToolPacking does nothing
    tb->SetToolPacking(1);
    int tool_packing = tb->GetToolPacking();


//  On MSW, ToolMargins does nothing
    wxSize defMargins = tb->GetMargins();
//    toolBar->SetMargins(wxSize(6, defMargins.y));
    tb->SetMargins(6, defMargins.y);
    wxSize tool_margin = tb->GetMargins();


    tb->SetToolSeparation(5);                  // width of separator
    int tool_sep = tb->GetToolSeparation();

//      Calculate the tool and separator pitches
    wxSize toolsize = tb->GetToolSize();

    int x;                                          // running position
    int pitch_tool, pitch_sep;
    pitch_tool = toolsize.x + tool_packing + tool_margin.x;
    pitch_sep =  tool_sep   + tool_packing + tool_margin.x;
    x =tool_packing + tool_margin.x;

      // Some platform specific fixups needed here
#ifdef __WXMSW__
      pitch_tool = toolsize.x;
      pitch_sep =  tool_sep + 1;
      x = 3;
#endif

#ifdef __WXGTK__
    {
        pitch_tool += 2;
        x -= 1;

      //    More hacks to this sorry class.
        if((wxMAJOR_VERSION == 2) && (wxMINOR_VERSION >= 8))
            x += 2;
    }
#endif

    //  Fetch a sample bitmap for a placeholder
    string_to_pbitmap_hash *phash;
    phash = m_phash;

    tb->AddTool( ID_ZOOMIN, _T(""), *(*phash)[wxString("zoomin")], _T(""), wxITEM_NORMAL);
    x += pitch_tool;
    tb->AddTool( ID_ZOOMOUT, _T(""), *(*phash)[wxString("zoomout")], _T(""), wxITEM_NORMAL);
    x += pitch_tool;

    tb->AddSeparator();
    x += pitch_sep;

    tb->AddTool( ID_STKDN, _T(""), *(*phash)[wxString("scin")], _T("Stack +"), wxITEM_NORMAL);
    x += pitch_tool;
    tb->AddTool( ID_STKUP, _T(""),*(*phash)[wxString("scout")], _T("Stack -"), wxITEM_NORMAL);
    x += pitch_tool;

    tb->AddSeparator();
    x += pitch_sep;

    tb->AddTool( ID_ROUTE, _T(""), *(*phash)[wxString("route")], _T("Create Route"), wxITEM_NORMAL);
    x += pitch_tool;
    tb->AddTool( ID_FOLLOW, _T(""), *(*phash)[wxString("follow")], _T("Auto Follow"), wxITEM_CHECK);
    x += pitch_tool;

    tb->AddSeparator();
    x += pitch_sep;

    tb->AddTool( ID_SETTINGS, _T(""), *(*phash)[wxString("settings")], _T("Settings"), wxITEM_NORMAL);
    x += pitch_tool;
    tb->AddTool( ID_TEXT, _T(""), *(*phash)[wxString("text")], _T("Enable S57 Text"), wxITEM_CHECK);
    x += pitch_tool;

    tb->AddSeparator();
    x += pitch_sep;

    tb->AddTool( ID_CURRENT, _T(""), *(*phash)[wxString("current")], _T("Show Currents"), wxITEM_CHECK);
    x += pitch_tool;
    tb->AddTool( ID_TIDE, _T(""), *(*phash)[wxString("tide")], _T("Show Tides"), wxITEM_CHECK);
    x += pitch_tool;

    tb->AddSeparator();
    x += pitch_sep;

    if(g_bShowPrintIcon)
    {
        tb->AddTool( ID_PRINT, _T(""), *(*phash)[wxString("print")], _T("Print Chart"), wxITEM_NORMAL);
        x += pitch_tool;
        x += 1;                     // now why in the heck is this necessary?????? Grrrrrrrr.
    }

    tb->AddTool( ID_COLSCHEME, _T(""), *(*phash)[wxString("colorscheme")], _T("Change Color Scheme"), wxITEM_NORMAL);
    x += pitch_tool;
    tb->AddTool( ID_HELP, _T(""), *(*phash)[wxString("help")], _T("About OpenCPN"), wxITEM_NORMAL);
    x += pitch_tool;

    // The status tool will be here
    m_statTool_pos = tb->GetToolPos(ID_HELP) + 1;

//      Create and add a dummy control, to arrange for the "exit" tool to be
//      at right margin

    int tx,ty;
    GetClientSize(&tx, &ty);                    // of the frame

    int filler_pad = tool_margin.x + tool_packing;
    int filler_width = tx - x - pitch_tool - filler_pad;

    toolbar_width_without_static = x + pitch_tool + filler_pad;     // used by Resize()

#define DUMMY_HEIGHT    40
    m_tool_dummy_size_x = filler_width;
    m_tool_dummy_size_y = DUMMY_HEIGHT;

    //  Make sure to always create a reasonable dummy
    if(m_tool_dummy_size_x <= 0)
        m_tool_dummy_size_x = 1;

    wxImage tool_image_dummy(m_tool_dummy_size_x,32);
    wxBitmap tool_bm_dummy(tool_image_dummy);

    delete m_ptool_ct_dummy;
    m_ptool_ct_dummy = new wxStaticBitmap(tb, ID_TBSTAT, tool_bm_dummy, wxPoint(2000,0),
                                        wxSize(m_tool_dummy_size_x,DUMMY_HEIGHT),
                                        wxSIMPLE_BORDER, _T("staticBitmap"));

    tb->AddControl(m_ptool_ct_dummy);

//      And add the "Exit" tool
    tb->AddTool( ID_TBEXIT, _T(""), *(*phash)[wxString("exitt")], _T("Exit"), wxITEM_NORMAL);

// Realize() the toolbar
    tb->Realize();


//      Set up the toggle states
    if(pConfig)
        tb->ToggleTool(ID_FOLLOW, pConfig->st_bFollow);

#ifdef USE_S57
    if((pConfig) && (ps52plib))
        if(ps52plib->m_bOK)
            tb->ToggleTool(ID_TEXT, ps52plib->GetShowS57Text());
#endif

        SetStatusBarPane(-1);                   // don't show help on status bar

        return tb;
}


//      Some helpers functions for Toolbar support
void MyFrame::PrepareToolbarBitmaps(void)
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

    //  Process all members of the XPM hashmap

    string_to_pchar_hash::iterator it;
    for( it = tool_xpm_hash.begin(); it != tool_xpm_hash.end(); ++it )
    {
        wxImage *pimg;

        wxString index = it->first;
        char **px1 = (char **)tool_xpm_hash[index];

//  Build Day Bitmap
        pimg = new wxImage(px1);
        BuildToolBitmap(pimg, 230, index, tool_bitmap_hash_day);
        delete pimg;

//  Build Dusk Bitmap
        pimg = new wxImage(px1);
        BuildToolBitmap(pimg, 128, index, tool_bitmap_hash_dusk);
        delete pimg;

//  Build Night Bitmap
        pimg = new wxImage(px1);
        BuildToolBitmap(pimg,  64, index, tool_bitmap_hash_night);
        delete pimg;
    }
}

void MyFrame::BuildToolBitmap(wxImage *pimg, unsigned char back_color, wxString &index, string_to_pbitmap_hash &hash)
{

        // Substitute the mask color with a fixed background color
        unsigned char mask_r, mask_g, mask_b;
        pimg->GetOrFindMaskColour(&mask_r, &mask_g, &mask_b);

        pimg->Replace(mask_r, mask_g, mask_b, back_color,back_color,back_color);

        //Remove the mask from the image
        pimg->SetMask(false);

        //  Make a bitmap
        wxBitmap tbmp(pimg->GetWidth(),pimg->GetHeight(),-1);
        wxMemoryDC dwxdc;
        dwxdc.SelectObject(tbmp);
        wxBitmap *ptoolBarBitmap;

#ifdef __WXMSW__
        ptoolBarBitmap = new wxBitmap(*pimg, (wxDC &)dwxdc);
#else
        ptoolBarBitmap = new wxBitmap(*pimg);
#endif

        // store it
        hash[index] = ptoolBarBitmap;
}

void MyFrame::ReSizeToolbar(void)
{

    int tx, ty;
    GetClientSize(&tx, &ty);                    // of the frame

    m_tool_dummy_size_x = tx - toolbar_width_without_static;

    if(Current_Ch)
    {
        if(m_tool_dummy_size_x != tool_dummy_size_x_last)     // only update if size has changed
        {
            UpdateToolbarStatusWindow(Current_Ch, true);
        }
    }


}

//      Update inplace the current toolbar with bitmaps corresponding to the current color scheme
void MyFrame::UpdateToolbar(ColorScheme cs)
{
    wxColour back_color;

    //  Select the correct bitmap hash table and background color
    switch(cs)
    {
        case GLOBAL_COLOR_SCHEME_DAY:
            m_phash = &tool_bitmap_hash_day;
            back_color = wxColour(230,230,230);
            break;
        case GLOBAL_COLOR_SCHEME_DUSK:
            m_phash = &tool_bitmap_hash_dusk;
            back_color = wxColour(128,128,128);
            break;
        case GLOBAL_COLOR_SCHEME_NIGHT:
            m_phash = &tool_bitmap_hash_night;
            back_color = wxColour(64,64,64);
            break;
        default:
            back_color = wxColour(150,150,150);
            m_phash = &tool_bitmap_hash_day;
            break;
    }

    DestroyMyToolbar();
    toolBar = CreateAToolbar();
    SetToolBar((wxToolBar *)toolBar);

    //  Set background
    toolBar->SetBackgroundColour(back_color);

#ifdef __WXGTK__
    //  On GTK, need to be more explicit
    GdkColor color;

    color.red = back_color.Red() << 8;
    color.green = back_color.Green() << 8;
    color.blue = back_color.Blue() << 8;

    gtk_widget_modify_bg (GTK_WIDGET(toolBar->m_toolbar), GTK_STATE_NORMAL, &color);
#endif

    //  Re-establish toggle states
    toolBar->ToggleTool(ID_FOLLOW, cc1->m_bFollow);
    toolBar->ToggleTool(ID_CURRENT, cc1->bShowCurrent);
    toolBar->ToggleTool(ID_TIDE, cc1->bShowTide);

    return;
}





// Intercept menu commands
void MyFrame::OnExit(wxCommandEvent& event)
{
}

void MyFrame::OnCloseWindow(wxCloseEvent& event)
// begin rms
#ifdef __WXOSX__
      quitflag++ ;
#endif // __WXOSX__
// end rms
{
   FrameTimer1.Stop();

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

    if(pAIS)
    {
        pAIS->Close();
        pAIS = NULL;
    }

    console->Destroy();
    stats->Destroy();

//    pthumbwin->Destroy();
    delete pthumbwin;

    delete pAPilot;

    // Delete the toolbar bitmaps

    string_to_pbitmap_hash::iterator it;

    for( it = tool_bitmap_hash_day.begin(); it != tool_bitmap_hash_day.end(); ++it )
    {
        wxBitmap *pbm = it->second;
        delete pbm;
    }

    for( it = tool_bitmap_hash_dusk.begin(); it != tool_bitmap_hash_dusk.end(); ++it )
    {
        wxBitmap *pbm = it->second;
        delete pbm;
    }

    for( it = tool_bitmap_hash_night.begin(); it != tool_bitmap_hash_night.end(); ++it )
    {
        wxBitmap *pbm = it->second;
        delete pbm;
    }

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
                cccw = x * 10/10;               // constrain to mod 4
                int wr = cccw/4;
                cccw = wr*4;
                cccw += 2;                              // account for simple border

                ccch = y - stat_height;

                int cur_width, cur_height;
                cc1->GetSize(&cur_width, &cur_height);
                if((cur_width != cccw) || (cur_height != ccch))
                {
                    if(Current_Ch)
                        Current_Ch->InvalidateCache();

                    cc1->SetSize(0,0,cccw, ccch);
                }


        }

        if(console)
        {
                console->Size_X = 160;
                console->Size_Y = y/2;
                console->Pos_X = cccw - console->Size_X;
                console->Pos_Y = 0;
                console->SetSize(console->Pos_X,console->Pos_Y,console->Size_X, console->Size_Y);

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

    case ID_ZOOMIN:
    {
        //      Bound the zoomin of raster charts to at most 2x overzoom
        if((Current_Ch->ChartType == CHART_TYPE_GEO) || (Current_Ch->ChartType == CHART_TYPE_KAP))
        {
            double target_scale = cc1->GetVPScale() * 2;
            ChartBaseBSB *Cur_BSB_Ch = dynamic_cast<ChartBaseBSB *>(Current_Ch);
            double chart_1x_scale = Cur_BSB_Ch->GetPPM();
            if(target_scale > 2.1 * chart_1x_scale)
                break;
        }

        cc1->SetVPScale(cc1->GetVPScale() * 2);
        cc1->Refresh(false);
        break;
    }

    case ID_ZOOMOUT:
    {
        //      Bound the zoomout of raster charts to at most 8x underzoom
        if((Current_Ch->ChartType == CHART_TYPE_GEO) || (Current_Ch->ChartType == CHART_TYPE_KAP))
        {
            double target_scale = cc1->GetVPScale() / 2;
            ChartBaseBSB *Cur_BSB_Ch = dynamic_cast<ChartBaseBSB *>(Current_Ch);
            double chart_1x_scale = Cur_BSB_Ch->GetPPM();
            if(target_scale < chart_1x_scale / 32)
                break;
        }
        cc1->SetVPScale(cc1->GetVPScale() / 2);
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
            if(!cc1->m_bFollow)
            {
                cc1->m_bFollow = true;
//      Warp speed jump to current position
//            Current_Ch->InvalidateCache();            // Add back for wxx11 This might be needed??? 8/19/06
                cc1->SetViewPoint(vLat, vLon, cc1->GetVPScale(),
                              Current_Ch->GetChartSkew() * PI / 180., 1, FORCE_SUBSAMPLE);     // set mod 4
                cc1->Refresh(false);
            }
            else
            {
                cc1->m_bFollow = false;
            }

            toolBar->ToggleTool(ID_FOLLOW, cc1->m_bFollow);

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
                s = GLOBAL_COLOR_SCHEME_DAY;

            SetAndApplyColorScheme(s);

            if(cc1)
            {
                cc1->FlushBackgroundRender();
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
 //             ShowDebugWindow as a wxStatusBar
    m_StatusBarFieldCount = 6;
        if(pConfig->m_bShowDebugWindows)
        {
                if(!m_pStatusBar)
                    m_pStatusBar = CreateStatusBar(m_StatusBarFieldCount, 0);       // No wxST_SIZEGRIP needed
        }
        else
        {
                if(m_pStatusBar)
                {
                    m_pStatusBar->Destroy();
                    m_pStatusBar = NULL;
                    SetStatusBar(NULL);

                    Refresh();
                }
        }

      if(bnewtoolbar)
      {
          UpdateToolbar(global_color_scheme);
      }

      if(bFlyingUpdate)
      {
           wxSizeEvent sevt;
//           OnSize(sevt);
      }

}

int MyFrame::DoOptionsDialog()
{
    options *pSetDlg = new options(this, -1, "Options", *pInit_Chart_Dir);

//      Pass two working pointers for Chart Dir Dialog
      pSetDlg->SetCurrentDirListPtr(pChartDirArray);
      wxArrayString *pWorkDirArray = new wxArrayString;
      pSetDlg->SetWorkDirListPtr(pWorkDirArray);

//  Grab a copy of the current NMEA source and AP Port and AIS Port
      wxString previous_NMEA_source(*pNMEADataSource);
      wxString previous_NMEA_APPort(*pNMEA_AP_Port);
      wxString previous_AIS_Port(*pAIS_Port);

//      Pass a ptr to MyConfig, for updates
      pSetDlg->SetConfigPtr(pConfig);

      pSetDlg->SetInitialSettings();

      bDBUpdateInProgress = true;

      bool bPrevPrintIcon = g_bShowPrintIcon;

//    Grab copies of s57 Display Styles
#ifdef USE_S57
      int l_nSymbolStyle   = ps52plib->m_nSymbolStyle;
      int l_nBoundaryStyle = ps52plib->m_nBoundaryStyle;
#endif

//    Pause all of the async classes
#ifdef USE_WIFI_CLIENT
      if(pWIFI)
          pWIFI->Pause();
#endif

      if(pAIS)
          pAIS->Pause();
      if(nmea)
          nmea->Pause();

// And here goes the (modal) dialog
      int rr = pSetDlg->ShowModal();

      if(rr == 1)
      {
            if(*pChartDirArray != *pWorkDirArray)
            {
                  FrameTimer1.Stop();                  // stop other asynchronous activity

                  Current_Ch = NULL;

                  delete pCurrentStack;
                  pCurrentStack = NULL;

                  *pChartDirArray = *pWorkDirArray;

                  if(NULL == ChartData)
                       ChartData = new ChartDB(gFrame);
                  ChartData->Update(pChartDirArray);
                  ChartData->SaveBinary(pChartListFileName, pChartDirArray);

                  pConfig->UpdateChartDirs(pChartDirArray);

                  FrameTimer1.Start(TIMER_GFRAME_1,wxTIMER_CONTINUOUS);

            }

            if(*pNMEADataSource != previous_NMEA_source)
            {
                  if(nmea)
                      nmea->Close();
                  delete nmea;
                  nmea = new NMEAWindow(ID_NMEA_WINDOW, gFrame, *pNMEADataSource );
            }


            if(*pNMEA_AP_Port != previous_NMEA_APPort)
            {
                if(pAPilot)
                    pAPilot->Close();
                delete pAPilot;
                pAPilot = new AutoPilotWindow(gFrame, *pNMEA_AP_Port );
            }

            if(*pAIS_Port != previous_AIS_Port)
            {
                if(pAIS)
                    pAIS->Close();
                delete pAIS;
                pAIS = new AIS_Decoder(ID_AIS_WINDOW, gFrame, *pAIS_Port );
            }

#ifdef USE_S57
            if((l_nSymbolStyle != ps52plib->m_nSymbolStyle) ||
                   (l_nBoundaryStyle != ps52plib->m_nBoundaryStyle))
            {
                // Traverse the database of open charts.
                // Finding S57 chart, execute UpdateLUPs to link objects
                // to possibly new symbology style.
                unsigned int nCache = ChartData->pChartCache->GetCount();
                for(unsigned int i=0 ; i<nCache ; i++)
                {
                    CacheEntry *pce = (CacheEntry *)(ChartData->pChartCache->Item(i));
                    ChartBase *Ch = (ChartBase *)pce->pChart;
                    if(Ch->ChartType == CHART_TYPE_S57)
                    {
                        s57chart *S57_Ch = dynamic_cast<s57chart *>(Ch);
                        S57_Ch->UpdateLUPs();
                    }
                }
            }

#endif

            pConfig->UpdateSettings();
      }

//    Restart the async classes
#ifdef USE_WIFI_CLIENT
      if(pWIFI)
          pWIFI->UnPause();
#endif

      if(pAIS)
          pAIS->UnPause();
      if(nmea)
          nmea->UnPause();

      delete pWorkDirArray;

      bDBUpdateInProgress = false;

      delete pSetDlg;

      return((bPrevPrintIcon != g_bShowPrintIcon));    // indicate a refresh is necessary
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


void MyFrame::OnFrameTimer1(wxTimerEvent& event)
{
      g_tick++;

//      Finish TCP/IP Sockets test
// See the code in MyApp::TestSockets()
/*
      if(s_socket_test_running)
      {
          s_socket_test_running  = false;
//  Clean up
          wxTheApp->Disconnect(wxID_ANY, wxID_ANY, (wxEventType)wxEVT_SOCKET, (wxObjectEventFunction)NULL, NULL, NULL);
          delete s_s_sock;
          delete s_t_sock;

          if(!s_socket_test_passed)
          {
              wxString msg1("\
This version of wxWidgets cannot process TCP/IP socket traffic.\n\
     So, NMEA TCP/IP data input support will be disabled.\n\
            You may need a wxWidgets upgrade, or\n\
    rebuild wxWidgets with --enable-compat24 config flag.");

              wxMessageDialog mdlg(gFrame, msg1, wxString("OpenCPN"),wxICON_ERROR | wxOK );
              int dlg_ret;
              dlg_ret = mdlg.ShowModal();
          }
      }
*/


//      Listen for quitflag to be set, requesting application close
      if(quitflag)
      {
          wxLogMessage("Got quitflag from SIGUSR1");
          FrameTimer1.Stop();
          Close();
          return;
      }

      if(bDBUpdateInProgress)
            return;

      FrameTimer1.Stop();

//  Update and check watchdog timer for GPS data source
      gGPS_Watchdog--;

      if(gGPS_Watchdog <= 0)
          bGPSValid = false;

//      Update the Toolbar Status window the first time watchdog times out
      if(gGPS_Watchdog == 0)
          UpdateToolbarStatusWindow(Current_Ch, false);

//      Update the chart database and displayed chart
      bool bnew_chart = DoChartUpdate(0);

//      Update the active route, if any
      if(pRouteMan->UpdateProgress())
      {
          nBlinkerTick++;
          //    This RefreshRect will cause any active routepoint to blink
          if(pRouteMan->GetpActiveRoute())
            cc1->RefreshRect(pRouteMan->GetpActiveRoute()->active_pt_rect, false);
      }

//      Update the memory status, and display
#ifdef __LINUX__
      int mem_current;
      GetMemoryStatus(mem_total, mem_current);

      if(m_pStatusBar)
      {
            char buf[40];
            sprintf(buf, "%3d/%3d/%3d", mem_initial/1024, mem_current/1024, mem_total/1024);

            SetStatusText(buf, 5);
      }
//      printf("%d\n", mem_current);
#endif

#ifdef AUTO_CONFIG_SAVE_MINUTES
//  Possibly save the current configuration
      if(0 == (g_tick % (AUTO_CONFIG_SAVE_MINUTES * 60)))
      {
        pConfig->UpdateSettings();
      }
#endif

//  Force own-ship drawing parameters
        cc1->Ship_Color = *wxRED;
        cc1->Ship_Size  = 10;

        if(Current_Ch)
        {
           if(Current_Ch->Chart_Error_Factor > 0.02)
            {
                cc1->Ship_Color = wxColor(255,255,0);
                cc1->Ship_Size  = 20;
            }
        }

        if(!bGPSValid)
        {
            cc1->Ship_Color = *wxWHITE;
            cc1->Ship_Size  = 10;
        }


        FrameTimer1.Start(TIMER_GFRAME_1,wxTIMER_CONTINUOUS);

//        cc1->Refresh(false);


//  Invalidate the ChartCanvas window appropriately
        cc1->UpdateShips();

        cc1->UpdateAIS();

//        worry about active point blink

        if(bnew_chart || cc1->GetbNewVP())
        {
//            printf("Timer Refresh(false) bnew_chart: %d bNewVP:%d\n", bnew_chart,cc1->GetbNewVP());
            cc1->Refresh(false);
        }

        if(console->IsShown())
           console->Refresh(false);


}


void MyFrame::UpdateChartStatusField(int i)
{
        char buf[80], buf1[80];
        ChartData->ChartDB::GetChartID(pCurrentStack, CurrentStackEntry, buf, sizeof(buf));
        sprintf (buf1, "  %d/%d", CurrentStackEntry, pCurrentStack->nEntry-1);
        strcat(buf, "  ");
        strcat(buf, buf1);
        strcat(buf, "  ");

        ChartData->GetStackChartScale(pCurrentStack, CurrentStackEntry, buf1, sizeof(buf1));
        strcat(buf, buf1);

        if(m_pStatusBar)
                SetStatusText(buf, i);

        stats->Refresh(false);
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

void MyFrame::UpdateToolbarStatusWindow(ChartBase *pchart, bool bUpdate)
{
    if(NULL == pchart)
        return;

    if(m_tool_dummy_size_x <= 0)
        return;
//begin rms
      int iSysDescent = 0 ;
//end rms
#ifdef __WXMSW__
//      int font1_size = 24;
      int font2_size = 10;
      int font3_size = 14;
//begin rms
#elif defined(__WXOSX__)
      int font2_size = 10;
      int font3_size = 12;
// end rms
#else
//      int font1_size = 22;
      int font2_size = 12;
      int font3_size = 16;
#endif


//      Create a wxBitmap for the window
      wxBitmap tool_bm_dummy(m_tool_dummy_size_x, m_tool_dummy_size_y);
      tool_dummy_size_x_last = m_tool_dummy_size_x;       // record for change tracking during resize

      int size_x = m_tool_dummy_size_x;
      int size_y = m_tool_dummy_size_y;

//      Draw the graphics
      wxMemoryDC dc;
      dc.SelectObject(tool_bm_dummy);

// First, clear background
// Using a color depending on the state of bGPSValid and Chart_Error_Factor
      wxBrush *p_brush;
      p_brush = wxTheBrushList->FindOrCreateBrush(wxColour(200,220,200), wxSOLID);   // quiet green

      //    If the color sceme is "NIGHT", use a darker color
      if(global_color_scheme == GLOBAL_COLOR_SCHEME_NIGHT)
          p_brush = wxTheBrushList->FindOrCreateBrush(wxColour(100,110,100), wxSOLID);   // quiet green


      if(Current_Ch->Chart_Error_Factor > .02)                                       // X percent error
          p_brush = wxTheBrushList->FindOrCreateBrush(wxColour(255,255,0), wxSOLID);   // loud yellow

      if(!bGPSValid)
      {
          if(Current_Ch->Chart_Error_Factor > .02)                                       // X percent error
              p_brush = wxTheBrushList->FindOrCreateBrush(wxColour(255,108,0), wxSOLID);  // orange
          else
              p_brush = wxTheBrushList->FindOrCreateBrush(wxColour(220,200,200), wxSOLID);  // soft red
      }

      dc.SetBackground(*p_brush);
      dc.Clear();

// Show Pub date
// Get a Font
      wxFont *pSWFont1;
//begin rms
#ifndef __WXOSX__
      pSWFont1 = wxTheFontList->FindOrCreateFont(font3_size, wxDEFAULT,wxNORMAL, wxBOLD,
                  FALSE, wxString("Eurostile Extended"), wxFONTENCODING_SYSTEM );
#else
      pSWFont1 = wxTheFontList->FindOrCreateFont(font3_size, wxFONTFAMILY_ROMAN,wxNORMAL, wxNORMAL,
                                                                         FALSE, wxString("Roman"), wxFONTENCODING_SYSTEM );
#endif
//end rms
      dc.SetFont(*pSWFont1);

//      Get and show the Chart Publish Date
      wxString pub_date;
      pchart->GetPubDate(pub_date);

      int w, h, descent;
      GetTextExtent(pub_date, &w, &h, &descent, NULL, pSWFont1);

      int date_locn_x = size_x - w - 2;
      int date_locn_y = size_y - h;
//  begin rms
#ifdef __WXOSX__
      iSysDescent = descent ;
#endif
// end rms
      //    + descent for linux??
      RenderShadowText(&dc, pSWFont1, (char *)pub_date.c_str(), date_locn_x, date_locn_y - iSysDescent/*inline rms*/);


//    Show File Name
      wxFont *pSWFont2;

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
      if(w > date_locn_x)
      {
            dc.SetFont(*pSWFont2);
            GetTextExtent(name, &w, &h, NULL, NULL, pSWFont2);
            if(w > date_locn_x)                                     // still too long, so shorten it
            {
              wxString nameshort;
              int l = name.Len();
              l -= 3;
              while(l)              //ell
              {
                nameshort = name.Mid(0, l);
                nameshort.Append("...");
                GetTextExtent(nameshort, &w, &h, NULL, NULL, pSWFont2);
                if(w < date_locn_x)
                  break;
                l -= 1;
              }
              dc.DrawText(nameshort, 0, size_y - h - iSysDescent/*inline rms*/);                  // properly placed
            }
            else
                  dc.DrawText(name, 0, size_y - h - iSysDescent/*inline rms*/);
      }
      else
        dc.DrawText(name, 0, size_y - h - iSysDescent/*inline rms*/);

//   Delete the current status tool, if present
      int ct_pos = toolBar->GetToolPos(ID_TBSTAT);
      if(ct_pos != -1)
      {
//      Delete the EXIT tool
        toolBar->DeleteTool(ID_TBEXIT);

//      Delete the current status tool
        toolBar->DeleteTool(ID_TBSTAT);
       }

//      Create the new control tool
#ifdef __WXMSW__
//      delete m_ptool_ct_dummy;        // Gets deleted by DeleteTool?
#endif
      m_ptool_ct_dummy = new wxStaticBitmap(toolBar, ID_TBSTAT, tool_bm_dummy,
                                            wxPoint(2000,10), wxSize(size_x, size_y),wxSIMPLE_BORDER, _T("staticBitmap"));
//      Insert the new control
      toolBar->InsertControl(m_statTool_pos, m_ptool_ct_dummy);

//      Re-insert the EXIT tool
      toolBar->AddTool( ID_TBEXIT, _T(""), *(*m_phash)[wxString("exitt")], _T("Exit"), wxITEM_NORMAL);

 //     Realize the toolbar to reflect changes
      toolBar->Realize();

//      if(bUpdate)
      SendSizeEvent();
}


void MyFrame::SelectChartFromStack(int index)
{
        if(index < pCurrentStack->nEntry)
        {
//            if(nmea)
//                nmea->Pause();                  // Prevent any async interrupts/recursion

//      Open the new chart
            ChartBase *pTentative_Chart = ChartData->OpenChartFromStack(pCurrentStack, index);

            if(pTentative_Chart)
            {
                Current_Ch = pTentative_Chart;
                CurrentStackEntry = index;
            }
            else
            {
                SetChartThumbnail(index);       // need to reset thumbnail on failed chart open
            }


//      Update the Status Line
            UpdateChartStatusField(0);

//      Update the Toolbar Status window
            UpdateToolbarStatusWindow(Current_Ch, false);

//      Setup the view
            float zLat, zLon;
            if(cc1->m_bFollow)
                        { zLat = gLat; zLon = gLon;}
            else
                        { zLat = vLat; zLon = vLon;}


//  If the cache is invalid, as in new chart load, force a fast sub-sample render
            int new_sample_mode;
            if(Current_Ch->IsCacheValid())
                new_sample_mode = CURRENT_RENDER;
            else
                new_sample_mode = FORCE_SUBSAMPLE;


            if(Current_Ch->ChartType == CHART_TYPE_S57)
                cc1->SetViewPoint(zLat, zLon, cc1->GetVPScale(),
                                  Current_Ch->GetChartSkew() * PI / 180., 0, new_sample_mode);
            else
            {
                //  New chart is raster type
                // try to match new viewport scale to the previous view scale when going to a smaller scale chart
                double target_scale = cc1->GetVPScale();

                ChartBaseBSB *Cur_BSB_Ch = dynamic_cast<ChartBaseBSB *>(Current_Ch);

                double new_chart_1x_scale = Cur_BSB_Ch->GetPPM();

                int binary_scale_factor = 1;
                if(new_chart_1x_scale > target_scale)
                {
                    while(binary_scale_factor < 8)
                    {
                        if(fabs((new_chart_1x_scale / binary_scale_factor ) - target_scale) < (target_scale * 0.05))
                            break;
                        if((new_chart_1x_scale / binary_scale_factor ) < target_scale)
                            break;
                        else
                            binary_scale_factor *= 2;
                    }
                }

                else
                    binary_scale_factor = 1;

                //  And set the new view
                cc1->SetViewPoint(zLat, zLon, new_chart_1x_scale / binary_scale_factor,
                                  Current_Ch->GetChartSkew() * PI / 180., 1, new_sample_mode); //set mod 4
             }

        cc1->SetbNewVP(true);
        cc1->Refresh(FALSE);

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
            wxRect thumb_rect_in_parent = pthumbwin->GetRect();;
            pthumbwin->pThumbChart = NULL;
            pthumbwin->Show(false);
            cc1->RefreshRect(thumb_rect_in_parent, FALSE);
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

                                        cc1->m_bForceReDraw = true;

                                        pthumbwin->Resize();
                                        pthumbwin->Show(true);
                                        pthumbwin->Refresh(FALSE);
                                }



                                else
                                {
                                      //Todo Make this a safe wxString, need overload for GetFullPath()
                                        char pFullPath[100];
                                        ChartData->GetFullPath(pCurrentStack, index, pFullPath, sizeof(pFullPath));

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
                                ChartData->GetFullPath(pCurrentStack, index, buf, sizeof(buf));
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
        float new_binary_scale_factor;
        bool bNewChart = false;
        bool bNewPiano = false;

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

        //  Make sure the target stack is valid
        if(NULL == pCurrentStack)
               pCurrentStack = new ChartStack;

        // Build a chart stack based on tLat, tLon
        ChartStack *pWorkStack = new ChartStack;
        int l = ChartData->BuildChartStack(pWorkStack, tLat, tLon);

        if(l == 0)                                                                      // Bogus Lat, Lon?
        {
                if(NULL == pDummyChart)
                {
                    pDummyChart = new ChartDummy;
                    bNewChart = true;
                }

                if(Current_Ch)
                    if(Current_Ch->ChartType != CHART_TYPE_DUMMY)
                        bNewChart = true;

                Current_Ch = pDummyChart;

//    If the current viewpoint is invalid, set the default scale to something reasonable.
                double set_scale = cc1->GetVPScale();
                if(!cc1->VPoint.bValid)
                    set_scale = 1./20000.;

                cc1->SetViewPoint(tLat, tLon, set_scale, 0, 0, CURRENT_RENDER);
                bNewPiano = true;

        //      Copy the new (by definition empty) stack into the target stack
                ChartData->CopyStack(pCurrentStack, pWorkStack);

                goto update_finish;
        }


        //              Check to see if Chart Stack has changed
        if(!ChartData->EqualStacks(pWorkStack, pCurrentStack))
        {

        //      New chart stack, so...

                bNewPiano = true;

        //      Copy the new stack into the target stack
                ChartData->CopyStack(pCurrentStack, pWorkStack);


        //      Note current scale
                double current_binary_scale_factor;
                if(Current_Ch)
                    current_binary_scale_factor = cc1->GetVPBinaryScaleFactor();
                else
                    current_binary_scale_factor = 1;

        //  Is Current Chart in new stack?

                int tEntry = -1;
                if(NULL != Current_Ch)                                  // this handles startup case
                        tEntry = ChartData->GetStackEntry(pCurrentStack, Current_Ch->pFullPath);

                if(tEntry != -1)                // Current_Ch is in the new stack
                {
                        CurrentStackEntry = tEntry;
                        new_binary_scale_factor = current_binary_scale_factor;
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
                              ptc = ChartData->OpenChartFromStack(pCurrentStack, CurrentStackEntry);

                              if (NULL != ptc)
                              {
                                  new_binary_scale_factor = current_binary_scale_factor;    // Try to set scale to current value

// For Raster Charts, scale must be 1,2,4,8... etc.
                                  if(new_binary_scale_factor - floor(new_binary_scale_factor))
                                  {
                                      float sct = 1.0;
                                      while(sct < 16.0)
                                      {
                                          if(sct > new_binary_scale_factor)
                                              break;
                                          sct *= 2;
                                      }
                                      new_binary_scale_factor = sct;
                                  }

                                    break;
                              }
                        }
                        CurrentStackEntry++;
                  }
                  Current_Ch = ptc;
                  bNewChart = true;
                }

        // Arriving here, Current_Ch is opened and OK, or NULL
                if(NULL == Current_Ch)
                        CurrentStackEntry = 0;                                          // safe value

        // If NULL, there is just no raster chart available.  Punt...
                if(NULL == Current_Ch)
                {
/*
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
*/
//  Open a Dummy Chart
                        if(NULL == pDummyChart)
                        {
                            pDummyChart = new ChartDummy;
                            bNewChart = true;
                        }

                        if(Current_Ch)
                            if(Current_Ch->ChartType != CHART_TYPE_DUMMY)
                                bNewChart = true;

                        Current_Ch = pDummyChart;

                        cc1->SetViewPoint(vLat, vLon, cc1->GetVPScale(), 0, 0, CURRENT_RENDER);

                }

                if(NULL != Current_Ch)
                {

//      Update the Status Line
                  UpdateChartStatusField(0);

//      Setup the view using the current scale
                  double set_scale = cc1->GetVPScale();

                  // However, if current chart is a raster chart, set scale to a "nice" (i.e. binary) scale
                  if((Current_Ch->ChartType == CHART_TYPE_GEO) || (Current_Ch->ChartType == CHART_TYPE_KAP))
                  {
                      ChartBaseBSB *Cur_BSB_Ch = dynamic_cast<ChartBaseBSB *>(Current_Ch);
                      set_scale = Cur_BSB_Ch->GetPPM() / new_binary_scale_factor;
                  }


                  cc1->SetViewPoint(tLat, tLon, set_scale,
                                    Current_Ch->GetChartSkew() * PI / 180., 1, CURRENT_RENDER);
                }
        }

        else                                                                    // No change in Chart Stack
        {
                if(cc1->m_bFollow)
                    cc1->SetViewPoint(tLat, tLon, cc1->GetVPScale(),
                                      Current_Ch->GetChartSkew() * PI / 180., 1, CURRENT_RENDER);
        }



update_finish:
        if(bNewChart)
            UpdateToolbarStatusWindow(Current_Ch, false);

        if(bNewPiano)
            stats->FormatStat();

        //  Update the ownship position on thumbnail chart, if shown
        if(pthumbwin->IsShown())
        {
            if(pthumbwin->pThumbChart->UpdateThumbData(gLat, gLon))
                pthumbwin->Refresh(TRUE);
        }


        //  Some debug
        //  Open the smallest scale vector chart available
#if 0
        CurrentStackEntry = 0;
        ChartBase *ptcv = NULL;
        while(CurrentStackEntry < pCurrentStack->nEntry)
        {
            if(ChartData->GetCSChartType(pCurrentStack, CurrentStackEntry) == CHART_TYPE_S57)
            {
                if ((ptcv = ChartData->OpenChartFromStack(pCurrentStack, CurrentStackEntry)))
                {
                      break;
                }
            }
            CurrentStackEntry++;
        }
        Current_Vector_Ch = ptcv;
#endif
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

    char *p;
    char buf[2000];
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
        char sbuf[100];
        char stoken[20];
        char skb[20];
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

                char *p;
                char buf[2000];
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
//                        printf("%c", *p++);
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
#define LOCAL_BUFFER_LENGTH 4096

    char buf[LOCAL_BUFFER_LENGTH];
    bool bshow_tick = false;


    switch(event.GetExtraLong())
    {
        case EVT_NMEA_PARSE_RX:
        {
            if(ps_mutexProtectingTheRXBuffer->TryLock() == wxMUTEX_NO_ERROR )
            {
                if(RX_BUFFER_FULL == rx_share_buffer_state)
                {
                    int nchar = strlen(rx_share_buffer);
                    strncpy (buf, rx_share_buffer, wxMin(nchar + 1, LOCAL_BUFFER_LENGTH - 1));
                    rx_share_buffer_state = RX_BUFFER_EMPTY;

                    if(rx_share_buffer_length != strlen(rx_share_buffer))
                        wxLogMessage("Got NMEA Event with inconsistent rx_share_buffer");
                }
                else
                     wxLogMessage("Got NMEA Event with RX_BUFFER_EMPTY");

                ps_mutexProtectingTheRXBuffer->Unlock();
            }
            else
            {
                AddPendingEvent(event);
                break;
            }



/*  DEBUG
                if(pStatusBar)
                {
                    wxString buf_nolf(buf);
                    buf_nolf.RemoveLast();
                    SetStatusText(buf_nolf.c_str(), 3);
                }
*/

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
                        UpdateToolbarStatusWindow(Current_Ch, false);

                    gGPS_Watchdog = gsp_watchdog_timeout_ticks;

                    bshow_tick = true;
                }
            }
            break;
        }       //case

        case EVT_NMEA_DIRECT:
        {
                  wxMutexLocker* pstateLocker = new wxMutexLocker(s_pmutexNMEAEventState) ;

                  if ( NMEA_STATE_RDY == g_iNMEAEventState )
                  {
                        gLat = kLat;
                        gLon = kLon;
                        gCog = kCog;
                        gSog = kSog;

                        bool last_bGPSValid = bGPSValid;
                        bGPSValid = true;
                        if(!last_bGPSValid)
                        {
                              UpdateToolbarStatusWindow(Current_Ch, false);
                              cc1->Refresh(false);            // cause own-ship icon to redraw
                        }

                        gGPS_Watchdog = gsp_watchdog_timeout_ticks;

                        bshow_tick = true;
                        g_iNMEAEventState = NMEA_STATE_DONE ;
                  }
            delete (pstateLocker) ;
                  break;
        }

    }           // switch
// begin rms
#ifdef __WXOSX__
      //      Show a little heartbeat tick in StatusWindow0 on NMEA events
      if (NULL == g_pMMEAeventTime )
      {
            g_pMMEAeventTime = new wxDateTime() ;
      }
      uint64_t uiCurrentTickCount ;
      g_pMMEAeventTime->SetToCurrent() ;
      uiCurrentTickCount = g_pMMEAeventTime->GetMillisecond() ;
    if(uiCurrentTickCount > g_ulLastNEMATicktime + 100)
    {
            g_ulLastNEMATicktime = uiCurrentTickCount ;
        char tick_buf[2];
        tick_buf[0] = nmea_tick_chars[tick_idx];
        tick_buf[1] = 0;
        if(NULL != GetStatusBar())
            SetStatusText(tick_buf, 0);
    }
#else
    if(bshow_tick)
    {
    //      Show a little heartbeat tick in StatusWindow0 on NMEA events
        if(tick_idx++ > 6)
            tick_idx = 0;

        char tick_buf[2];
        tick_buf[0] = nmea_tick_chars[tick_idx];
        tick_buf[1] = 0;
        if(NULL != GetStatusBar())
            SetStatusText(tick_buf, 0);
    }

}
#endif
// end rms
void MyFrame::StopSockets(void)
{
#ifdef USE_WIFI_CLIENT
    if(pWIFI)
       pWIFI->Pause();
#endif

    if(nmea)
        nmea->Pause();
}

void MyFrame::ResumeSockets(void)
{
#ifdef USE_WIFI_CLIENT
    if(pWIFI)
       pWIFI->UnPause();
#endif

    if(nmea)
        nmea->UnPause();
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
        if (page == 0)
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
    return (pageNum == 0);
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


WX_DECLARE_STRING_HASH_MAP( wxString, EnvHash );
static EnvHash env;


//----------------------------------------------------------------------------------
//      mygetenv
//
//      Replacement for posix getenv() which works for __WXMSW__
//      Todo Make this thing into a couple of string arrays to stop leakage
//----------------------------------------------------------------------------------


extern "C" char *mygetenv(char *pvar)
{
        wxString key(pvar);
        wxString test_val = env[key];
        if(test_val.Len())
        {
                pval->Empty();
                pval->Append(wxString(test_val));
                return((char *)pval->c_str());

        }
        else
        {
                wxString val;
                wxGetEnv(key, &val);
                env[key] = val;
                pval->Empty();
                pval->Append(wxString(val));
                return((char *)pval->c_str());
        }

}


/******************************************************************************
 * $Id: nmea.h,v 1.9 2008/01/10 03:39:33 bdbcat Exp $
 *
 * Project:  OpenCP
 * Purpose:  NMEA Data Object
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
 * $Log: nmea.h,v $
 * Revision 1.9  2008/01/10 03:39:33  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.8  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.7  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.6  2006/12/03 21:22:01  dsr
 * Redefine NMEA window ctor to include explicit window ID specification.
 * Change NMEA timer tick rate away from exactly 1000 msec to avoid syncronization problems.
 *
 *
 *
 */


#ifndef __NMEA_H__
#define __NMEA_H__

// begin rms // use same threading as Linux, i.e. POSIX, probably should change most of __LINUX__ to __POSIX__
// for legibility
#ifdef __WXOSX__
#define __LINUX__
#endif

// Include wxWindows' headers



#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled header


#ifdef __WXMSW__
    #ifdef ocpnUSE_MSW_SERCOMM
            #include "sercomm.h"
            class CSyncSerialComm;
    #endif
#endif

#ifdef __LINUX__
#include <sys/termios.h>
#endif

#include "wx/socket.h"

#ifdef __WXMSW__
#include <wx/datetime.h>
#endif
//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------

#define TIMER_NMEA_MSEC      997


#define GPSD_PORT_NUMBER      2947                  // Well Known Port number for GPSD

#define SOCKET_ID             5
#define TIMER_NMEA1           777

enum
{
    EVT_NMEA_DIRECT,
    EVT_NMEA_PARSE_RX
};

// Class declarations


// The MY_FILETIME structure is a 64-bit value
//    representing the number of 100-nanosecond
//    intervals since January 1, 1601 (UTC).
// This is the format used in the NMEA server data packet
//    sigh....

typedef struct  {
  unsigned int low;
  unsigned int high;
} MyFileTime;

class     CSyncSerialComm;
class MyFrame;
//----------------------------------------------------------------------------
// NMEAWindow
//----------------------------------------------------------------------------

class NMEAWindow: public wxWindow
{
public:
      NMEAWindow(int window_id, wxFrame *frame, const wxString& NMEADataSource, const wxString& NMEAAP_Port);
      NMEAWindow(int window_id, wxFrame *frame, const wxString& NMEADataSource);
      ~NMEAWindow();

      void GetSource(wxString& source);
      void GetAP_Port(wxString& port);

      //    Stop/Start the NMEA Socket Client
      //    Used to prevent async interrupts at critical times
      void Pause(void);
      void UnPause(void);

      void AutopilotOut(const char *Sentence);

      CSyncSerialComm   *pWinComm;

private:
      void OnPaint(wxPaintEvent& event);
      void OnActivate(wxActivateEvent& event);
      void OnSocketEvent(wxSocketEvent& event);
      void OnTimerNMEA(wxTimerEvent& event);
      void OnCloseWindow(wxCloseEvent& event);

      wxIPV4address     addr;
      wxSocketClient    *m_sock;
      bool              m_busy;
      wxTimer           TimerNMEA;
      MyFrame           *parent_frame;

      wxString          *m_pdata_source_string;
      wxString          *m_pdata_ap_port_string;
      wxEvtHandler      *m_pParentEventHandler;

DECLARE_EVENT_TABLE()
};



//-------------------------------------------------------------------------------------------------------------
//
//    NMEA Input Thread
//
//    This thread manages reading the NMEA data stream from the declared NMEA serial port
//
//-------------------------------------------------------------------------------------------------------------

#ifdef __WXMSW__
#include <windows.h>
#endif

//    Constants
typedef enum ENUM_BUFFER_STATE
{
      RX_BUFFER_EMPTY,
      RX_BUFFER_FULL
}_ENUM_BUFFER_STATE;

#define MAX_RX_MESSSAGE_SIZE  4096
#define     RX_BUFFER_SIZE                4096



//          Inter-thread communication event declaration
DECLARE_EVENT_TYPE(EVT_NMEA, -1)


class OCP_NMEA_Thread: public wxThread
{

public:

      OCP_NMEA_Thread(wxWindow *MainWindow, const char *pszPortName);
      ~OCP_NMEA_Thread(void);
      void *Entry();

      void OnExit(void);

private:
      wxEvtHandler            *m_pMainEventHandler;
      wxString                *m_pPortName;
      int                     TimeOutInSec;
      char                    *put_ptr;
      char                    *tak_ptr;

      char                    *rx_buffer;

      unsigned long           error;
      MyFrame                 *m_parent_frame;

#if defined ( __LINUX__ ) || defined ( __WXOSX__)
      termios                 *pttyset;
      termios                 *pttyset_old;

      int                     m_gps_fd;
#endif

#ifdef __WXMSW__
      HANDLE                  m_hSerialComm;
#endif

};



//-------------------------------------------------------------------------------------------------------------
//
//    A simple thread to test host name resolution without blocking the main thread
//
//-------------------------------------------------------------------------------------------------------------
class DNSTestThread: public wxThread
{
public:

      DNSTestThread(wxString &name_or_ip);
      ~DNSTestThread();
      void *Entry();


private:
      wxString *m_pip;
};

//-------------------------------------------------------------------------------------------------------------
//
//    Autopilot Class Definition
//
//-------------------------------------------------------------------------------------------------------------

class AutoPilotWindow: public wxWindow
{
public:
    AutoPilotWindow(wxFrame *frame, const wxString& AP_Port);
    ~AutoPilotWindow();

    void OnCloseWindow(wxCloseEvent& event);
    void GetAP_Port(wxString& source);
    void AutopilotOut(const char *Sentence);

private:
    bool            OpenPort(wxString &port);


    wxString        *m_pdata_ap_port_string;
#ifdef __LINUX__
    termios         *pttyset;
    termios         *pttyset_old;

    int             m_ap_fd;
#endif

#ifdef __WXMSW__
    CSyncSerialComm   *pWinComm;
#endif
// begin rms
#ifdef __WXOSX__
    CSyncSerialComm   *pWinComm;
#endif
//end rms
    bool            bOK;

DECLARE_EVENT_TABLE()
};


#endif

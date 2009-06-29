/******************************************************************************
 * $Id: nmea.cpp,v 1.36 2009/06/29 01:10:19 bdbcat Exp $
 *
 * Project:  OpenCPN
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
 */
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "wx/tokenzr.h"
#include <wx/datetime.h>

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "dychart.h"

#include "nmea.h"
#include "georef.h"

#ifdef __WXOSX__              // begin rms
#include "macsercomm.h"
#endif                        // end rms


#define NMAX_MESSAGE 100

CPL_CVSID("$Id: nmea.cpp,v 1.36 2009/06/29 01:10:19 bdbcat Exp $");

extern bool             g_bNMEADebug;
extern ComPortManager   *g_pCommMan;
extern bool             g_bGPSAISMux;

int                      s_dns_test_flag;

//    A static structure storing generic position data
//    Used to communicate from NMEA threads to main application thread
static      GenericPosDat     ThreadPositionData;




//------------------------------------------------------------------------------
//    NMEA Window Implementation
//------------------------------------------------------------------------------

BEGIN_EVENT_TABLE(NMEAWindow, wxWindow)
  EVT_ACTIVATE(NMEAWindow::OnActivate)
  EVT_CLOSE(NMEAWindow::OnCloseWindow)

  EVT_SOCKET(SOCKET_ID, NMEAWindow::OnSocketEvent)
  EVT_TIMER(TIMER_NMEA1, NMEAWindow::OnTimerNMEA)

  END_EVENT_TABLE()

// constructor
NMEAWindow::NMEAWindow(int window_id, wxFrame *frame, const wxString& NMEADataSource, wxMutex *pMutex):
      wxWindow(frame, window_id,     wxPoint(20,20), wxDefaultSize, wxSIMPLE_BORDER)

{
      parent_frame = frame;
      m_pParentEventHandler = parent_frame->GetEventHandler();

      m_pShareMutex = pMutex;

      m_pSecondary_Thread = NULL;
      m_sock = NULL;
      SetSecThreadInActive();

      TimerNMEA.SetOwner(this, TIMER_NMEA1);
      TimerNMEA.Stop();

      m_data_source_string = NMEADataSource;


//      Create and manage NMEA data stream source

//    Decide upon NMEA source
      wxString msg(_T("NMEA Data Source is...."));
      msg.Append(m_data_source_string);
      wxLogMessage(msg);

//    NMEA Data Source is shared with AIS port, AIS does the muxing
//    and we don't have anything else to do......
      if(m_data_source_string.Contains(_T("AIS")))
      {
            g_bGPSAISMux = true;
      }


//    NMEA Data Source is specified serial port
      else if(m_data_source_string.Contains(_T("Serial")))
      {
          wxString comx;
          comx =  m_data_source_string.Mid(7);        // either "COM1" style or "/dev/ttyS0" style

#ifdef __WXMSW__

//  As a quick check, verify that the specified port is available
            HANDLE m_hSerialComm = CreateFile(comx.mb_str(),       // Port Name
                                             GENERIC_READ,
                                             0,
                                             NULL,
                                             OPEN_EXISTING,
                                             0,
                                             NULL);

            if(m_hSerialComm == INVALID_HANDLE_VALUE)
            {
                  wxString msg(comx);
                  msg.Prepend(_T("  Could not open serial port '"));
                  msg.Append(_T("'\nSuggestion: Try closing other applications."));
                  wxMessageDialog md(this, msg, _T("OpenCPN Message"), wxICON_ERROR );
                  md.ShowModal();

                  return;
            }

            else
                  CloseHandle(m_hSerialComm);

//    Kick off the NMEA RX thread
            m_pSecondary_Thread = new OCP_NMEA_Thread(this, frame, pMutex, comx, g_pCommMan);
            m_pSecondary_Thread->Run();

#endif

#ifdef __POSIX__
//    Kick off the NMEA RX thread
            m_pSecondary_Thread = new OCP_NMEA_Thread(this, frame, pMutex, comx, g_pCommMan);
            m_pSecondary_Thread->Run();
#endif

      }

#ifdef __WXMSW__
      else if(m_data_source_string.Contains(_T("GARMIN")))
        {
              m_pSecondary_Thread = new OCP_GARMIN_Thread(this, frame, pMutex, _T("GARMIN"));
              m_pSecondary_Thread->Run();
        }
#endif

#ifndef OCPN_DISABLE_SOCKETS
//      NMEA Data Source is private TCP/IP Server
        else if(m_data_source_string.Contains(_T("GPSD")))
        {
            wxString NMEA_data_ip;
            NMEA_data_ip = m_data_source_string.Mid(5);         // extract the IP

        // Create the socket
            m_sock = new wxSocketClient();

        // Setup the event handler and subscribe to most events
            m_sock->SetEventHandler(*this, SOCKET_ID);

            m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                    wxSOCKET_INPUT_FLAG |
                    wxSOCKET_LOST_FLAG);
            m_sock->Notify(TRUE);

            m_busy = FALSE;


//    Build the target address

//    n.b. Win98
//    wxIPV4address::Hostname() uses sockets function gethostbyname() for address resolution
//    Implications...Either name target must exist in c:\windows\hosts, or
//                            a DNS server must be active on the network.
//    If neither true, then wxIPV4address::Hostname() will block (forever?)....
//
//    Workaround....
//    Use a thread to try the name lookup, in case it hangs

            DNSTestThread *ptest_thread = NULL;
            ptest_thread = new DNSTestThread(NMEA_data_ip);

            ptest_thread->Run();                      // Run the thread from ::Entry()


//    Sleep and loop for N seconds
#define SLEEP_TEST_SEC  2

            for(int is=0 ; is<SLEEP_TEST_SEC * 10 ; is++)
            {
                wxMilliSleep(100);
                if(s_dns_test_flag)
                    break;
            }

            if(!s_dns_test_flag)
            {

                wxString msg(NMEA_data_ip);
                msg.Prepend(_T("Could not resolve TCP/IP host '"));
                msg.Append(_T("'\n Suggestion: Try 'xxx.xxx.xxx.xxx' notation"));
                wxMessageDialog md(this, msg, _T("OpenCPN Message"), wxICON_ERROR );
                md.ShowModal();

                m_sock->Notify(FALSE);
                m_sock->Destroy();
                m_sock = NULL;

                return;
            }

            //      Resolved the name, somehow, so Connect() the socket
            m_addr.Hostname(NMEA_data_ip);
            m_addr.Service(GPSD_PORT_NUMBER);
            m_sock->Connect(m_addr, FALSE);       // Non-blocking connect

            TimerNMEA.Start(TIMER_NMEA_MSEC,wxTIMER_CONTINUOUS);
    }
#endif

      Hide();
}


NMEAWindow::~NMEAWindow()
{
}

void NMEAWindow::OnCloseWindow(wxCloseEvent& event)
{
//    Kill off the NMEA Socket if alive
      if(m_sock)
      {
            m_sock->Notify(FALSE);
            m_sock->Destroy();
            TimerNMEA.Stop();
      }

//    Kill off the Secondary RX Thread if alive
      if(m_pSecondary_Thread)
      {
          if(m_bsec_thread_active)              // Try to be sure thread object is still alive
                m_pSecondary_Thread->Delete();    //  wx Docs say don't use Kill().
                                                // But how else to get rid of a hung thread?
                                                // Delete() is safer, but blocks on stalled thread....

          wxSleep(1);
      }

}


void NMEAWindow::GetSource(wxString& source)
{
      source = m_data_source_string;
}



void NMEAWindow::OnActivate(wxActivateEvent& event)
{
}

void NMEAWindow::Pause(void)
{
      TimerNMEA.Stop();

      if(m_sock)
            m_sock->Notify(FALSE);
}

void NMEAWindow::UnPause(void)
{
    TimerNMEA.Start(TIMER_NMEA_MSEC,wxTIMER_CONTINUOUS);

      if(m_sock)
            m_sock->Notify(TRUE);
}



void NMEAWindow::OnSocketEvent(wxSocketEvent& event)
{

#define RD_BUF_SIZE    200

    int nBytes;
    unsigned char *bp;
    unsigned char buf[RD_BUF_SIZE + 1];
    int char_count;
    wxString token;
    double dglat, dglon, dgcog, dgsog;
    double dtime;
    wxDateTime fix_time;
    wxString str_buf;

  switch(event.GetSocketEvent())
  {
      case wxSOCKET_INPUT :                     // from gpsd Daemon
            m_sock->SetFlags(wxSOCKET_WAITALL);                               // was (wxSOCKET_NOWAIT);

            //    Disable input event notifications to preclude re-entrancy on non-blocking socket
 //           m_sock->SetNotify(wxSOCKET_LOST_FLAG);


//          Read the reply, one character at a time, looking for 0x0a (lf)
//          If the reply contains no lf, break on the buffer full

            bp = buf;
            char_count = 0;

            while (char_count < RD_BUF_SIZE)
            {
                m_sock->Read(bp, 1);
                nBytes = m_sock->LastCount();

                if(m_sock->Error())
                      break;                    // non-specific error
                if(*bp == 0x0a)

                      break;

                bp++;
                char_count++;
            }

            *bp = 0;                        // end string

//          Validate the string

            str_buf = (wxString((const char *)buf, wxConvUTF8));

            if(str_buf.StartsWith(_T("GPSD,O")))           // valid position data?
            {
                if(str_buf.GetChar(7) != '?')              // GPSd connected and we get real data
                {
                    wxStringTokenizer tkz(str_buf, _T(" "));
                    token = tkz.GetNextToken();

                    token = tkz.GetNextToken();
                    if(token.ToDouble(&dtime))
                         ThreadPositionData.FixTime = (time_t)floor(dtime);

                    token = tkz.GetNextToken();         // skip to lat

                    token = tkz.GetNextToken();
                    if(token.ToDouble(&dglat))
                          ThreadPositionData.kLat = dglat;

                    token = tkz.GetNextToken();
                    if(token.ToDouble(&dglon))
                          ThreadPositionData.kLon = dglon;

                    token = tkz.GetNextToken();         // skip to tmg
                    token = tkz.GetNextToken();
                    token = tkz.GetNextToken();

                    token = tkz.GetNextToken();
                    if(token.ToDouble(&dgcog))
                          ThreadPositionData.kCog = dgcog;

                    token = tkz.GetNextToken();
                    if(token.ToDouble(&dgsog))
                          ThreadPositionData.kSog = dgsog;


//    Signal the main program

                    wxCommandEvent event( EVT_NMEA,  GetId() );
                    event.SetEventObject( (wxObject *)this );
                    event.SetExtraLong(EVT_NMEA_DIRECT);
                    event.SetClientData(&ThreadPositionData);
                    m_pParentEventHandler->AddPendingEvent(event);
                }
            }

                     // Enable input events again.
 //           m_sock->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);

            break;


    case wxSOCKET_LOST:
    {
//          wxSocketError e = m_sock->LastError();          // this produces wxSOCKET_WOULDBLOCK    The socket is non-blocking and the operation would block.
                                                            // which seems to be extraneous
          break;
    }

    case wxSOCKET_CONNECTION :
    {
          //      Sign up for watcher mode
//          char c[10];
//          strcpy(c, "w+\n");
//          m_sock->Write(c, strlen(c));

          break;
    }

    default                  :
          break;
  }
}



void NMEAWindow::OnTimerNMEA(wxTimerEvent& event)
{
      TimerNMEA.Stop();

      if(m_sock)
      {
        if(m_sock->IsConnected())
        {
            unsigned char c = 'O';                  // Don't need this in watcher mode
            m_sock->Write(&c, 1);
        }
        else                                    // try to connect
        {
            m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG |
                          wxSOCKET_INPUT_FLAG |
                          wxSOCKET_LOST_FLAG);

            m_sock->Connect(m_addr, FALSE);       // Non-blocking connect
        }
      }



//--------------Simulator
#if(0)
      {
            if(m_pShareMutex)
                  wxMutexLocker stateLocker(*m_pShareMutex) ;
            float kCog = 090.;
            float kSog = 6.0;

            //    Kludge the startup case
            if(ThreadPositionData.kLat < 1.0)
                  ThreadPositionData.kLat = START_LAT;
            if(fabs(ThreadPositionData.kLon) < 1.0)
                  ThreadPositionData.kLon = START_LON;

            double pred_lat;
            double pred_lon;

            double dist = kSog / 3600.;
            ll_gc_ll(ThreadPositionData.kLat, ThreadPositionData.kLon, kCog, dist, &pred_lat, &pred_lon);


            ThreadPositionData.kCog = kCog;
            ThreadPositionData.kSog = kSog;
            ThreadPositionData.kLat = pred_lat;
            ThreadPositionData.kLon = pred_lon;
            ThreadPositionData.FixTime = 0;

    //    Signal the main program thread

            wxCommandEvent event( EVT_NMEA,  GetId() );
            event.SetEventObject( (wxObject *)this );
            event.SetExtraLong(EVT_NMEA_DIRECT);
            event.SetClientData(&ThreadPositionData);
            parent_frame->GetEventHandler()->AddPendingEvent(event);

      }
#endif


      TimerNMEA.Start(TIMER_NMEA_MSEC,wxTIMER_CONTINUOUS);
}



//-------------------------------------------------------------------------------------------------------------
//
//    A simple thread to test host name resolution without blocking the main thread
//    Dontcha' love socket's name resolution logic??
//
//-------------------------------------------------------------------------------------------------------------
DNSTestThread::DNSTestThread(wxString &name_or_ip)
{
      m_pip = new wxString(name_or_ip);

      Create();
}

DNSTestThread::~DNSTestThread()
{
      delete m_pip;
}


void *DNSTestThread::Entry()
{
      s_dns_test_flag = 0;

      wxIPV4address     addr;
      addr.Hostname(*m_pip);                          // this may block forever if DNS is not active

      s_dns_test_flag = 1;                            // came back OK
      return NULL;
}


//-------------------------------------------------------------------------------------------------------------
//
//    NMEA Serial Input Thread
//
//    This thread manages reading the NMEA data stream from the declared NMEA serial port
//
//-------------------------------------------------------------------------------------------------------------

//          Inter-thread communication event implementation
DEFINE_EVENT_TYPE(EVT_NMEA)
DEFINE_EVENT_TYPE(EVT_THREADMSG)



//-------------------------------------------------------------------------------------------------------------
//    OCP_NMEA_Thread Static data store
//-------------------------------------------------------------------------------------------------------------

extern char                         rx_share_buffer[MAX_RX_MESSSAGE_SIZE];
extern unsigned int                 rx_share_buffer_length;
extern ENUM_BUFFER_STATE            rx_share_buffer_state;
extern wxMutex                      *ps_mutexProtectingTheRXBuffer;

//-------------------------------------------------------------------------------------------------------------
//    OCP_NMEA_Thread Implementation
//-------------------------------------------------------------------------------------------------------------

//    ctor

OCP_NMEA_Thread::OCP_NMEA_Thread(NMEAWindow *Launcher, wxWindow *MessageTarget, wxMutex *pMutex, const wxString& PortName, ComPortManager *pComMan)
{
      m_total_error_messages = 0;

      m_launcher = Launcher;                        // This thread's immediate "parent"

      m_pMainEventHandler = MessageTarget->GetEventHandler();

      rx_share_buffer_state = RX_BUFFER_EMPTY;

      m_pPortName = new wxString(PortName);

      rx_buffer = new char[RX_BUFFER_SIZE + 1];
      put_ptr = rx_buffer;
      tak_ptr = rx_buffer;

      m_pShareMutex = pMutex;

      m_pCommMan = pComMan;                           // store a lcal copy of the ComPortManager pointer

      Create();

}

OCP_NMEA_Thread::~OCP_NMEA_Thread(void)
{
      delete rx_buffer;
      delete m_pPortName;
}

void OCP_NMEA_Thread::OnExit(void)
{
    //  Mark the global status as dead, gone
//    m_launcher->m_pNMEA_Thread = NULL;
}

//      Sadly, the thread itself must implement the underlying OS serial port
//      in a very machine specific way....

#ifdef __POSIX__
//    Entry Point
void *OCP_NMEA_Thread::Entry()
{
      m_launcher->SetSecThreadActive();               // I am alive

      bool not_done = true;
      bool nl_found;
      wxString msg;


      //    Request the com port from the comm manager
      if ((m_gps_fd = m_pCommMan->OpenComPort(*m_pPortName, 4800)) < 0)
      {
            wxString msg(_T("NMEA input device open failed: "));
            msg.Append(*m_pPortName);
            ThreadMessage(msg);
            goto thread_exit;
      }



//    The main loop

    while(not_done)
    {
        if(TestDestroy())
        {
            not_done = false;                               // smooth exit
        }
//    Blocking, timeout protected read of one character at a time
//    Timeout value is set by c_cc[VTIME]
//    Storing incoming characters in circular buffer
//    And watching for new line character
//     On new line character, send notification to parent

        char next_byte = 0;
        ssize_t newdata;
        newdata = read(m_gps_fd, &next_byte, 1);            // read of one char
                                                            // return (-1) if no data available, timeout
        // begin rms
#ifdef __WXOSX__
        if (newdata < 0 )
            wxThread::Sleep(100) ;
#endif
            // end rms


   // Fulup patch for handling hot-plug or wakeup events
   // from serial port drivers
        {
              static int maxErrorLoop;

              if (newdata > 0)
              {
      // we have data, so clear error
                    maxErrorLoop =0;
              }
              else
              {
        // no need to retry every 1ms when on error
                    sleep (1);

        // if we have more no character for 5 second then try to reopen the port
                    if (maxErrorLoop++ > 5)
                    {

          // do not retry for the next 5s
                          maxErrorLoop = 0;

          // free old unplug current port
                          m_pCommMan->CloseComPort(m_gps_fd);

          //    Request the com port from the comm manager
                          if ((m_gps_fd = m_pCommMan->OpenComPort(*m_pPortName, 4800)) < 0)  {
                                wxString msg(_T("NMEA input device open failed (will retry): "));
                                msg.Append(*m_pPortName);
                                ThreadMessage(msg);
                          } else {
                                wxString msg(_T("NMEA input device open on hotplug OK: "));
                          }
                    }
              }
        } // end Fulup hack


        //  And process any character

        if(newdata > 0)
        {
            nl_found = false;

            *put_ptr++ = next_byte;
            if((put_ptr - rx_buffer) > RX_BUFFER_SIZE)
                put_ptr = rx_buffer;

            if(0x0a == next_byte)
                nl_found = true;


//    Found a NL char, thus end of message?
            if(nl_found)
            {
                char *tptr;
                char *ptmpbuf;
                char temp_buf[RX_BUFFER_SIZE];


//    Copy the message into a temporary _buffer

                tptr = tak_ptr;
                ptmpbuf = temp_buf;

                while((*tptr != 0x0a) && (tptr != put_ptr))
                {
                   *ptmpbuf++ = *tptr++;

                   if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                      tptr = rx_buffer;
                }

                if((*tptr == 0x0a) && (tptr != put_ptr))    // well formed sentence
                {
                    *ptmpbuf++ = *tptr++;
                    if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                    tptr = rx_buffer;

                    *ptmpbuf = 0;

                    tak_ptr = tptr;

//    Message is ready to parse and send out
                    wxString str_temp_buf(temp_buf, wxConvUTF8);
                    Parse_And_Send_Posn(str_temp_buf);
                 }

            }                   //if nl
        }                       // if newdata > 0
    }                          // the big while...


//          Close the port cleanly
    m_pCommMan->CloseComPort(m_gps_fd);



thread_exit:
      m_launcher->SetSecThreadInActive();             // I am dead
    return 0;

}


#endif          //__POSIX__



#ifdef __WXMSW__
//    Entry Point
void *OCP_NMEA_Thread::Entry()
{
      wxString msg;

      m_launcher->SetSecThreadActive();       // I am alive

      OVERLAPPED osReader = {0};

      bool not_done;
      BOOL fWaitingOnRead = FALSE;
      HANDLE hSerialComm = (HANDLE)(-1);

           //    Request the com port from the comm manager
      if ((m_gps_fd = m_pCommMan->OpenComPort(*m_pPortName, 4800)) < 0)
      {
            wxString msg(_T("NMEA input device open failed: "));
            msg.Append(*m_pPortName);
            ThreadMessage(msg);
            goto thread_exit;
      }

      hSerialComm = (HANDLE)m_gps_fd;

//    Set up read event specification

      if(!SetCommMask((HANDLE)m_gps_fd, EV_RXCHAR)) // Setting Event Type
             return (0);

// Create the overlapped event. Must be closed before exiting
// to avoid a handle leak.
      osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

      if (osReader.hEvent == NULL)
            return 0;            // Error creating overlapped event; abort.

      not_done = true;
      bool nl_found;

#define READ_BUF_SIZE 20
      char szBuf[READ_BUF_SIZE];

      DWORD dwRead;

//    The main loop

      while(not_done)
      {
            if(TestDestroy())
                  not_done = false;                               // smooth exit


            if (!fWaitingOnRead)
            {
   // Issue read operation.
                  if (!ReadFile(hSerialComm, szBuf, READ_BUF_SIZE, &dwRead, &osReader))
                {
                    if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
                    {
         // Error in communications; report it.
                    }
                    else
                        fWaitingOnRead = TRUE;
                }
                else
                {
      // read completed immediately
                    goto HandleASuccessfulRead;
                }
            }


            // Read command has been issued, and did not return immediately

#define READ_TIMEOUT      200      // milliseconds

            DWORD dwRes;

            if (fWaitingOnRead)
            {
                  //    Loop forever, checking for thread exit request
                  while(1)
                  {
                        if(TestDestroy())
                              goto fail_point;                               // smooth exit


                        dwRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
                        switch(dwRes)
                        {
                              case WAIT_OBJECT_0:
                                    if (!GetOverlappedResult(hSerialComm, &osReader, &dwRead, FALSE))
                                    {
             // Error in communications; report it.
                                    }
                                  else
             // Read completed successfully.
                                    goto HandleASuccessfulRead;

                                  break;

                              case WAIT_TIMEOUT:
                                    if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
                                    {
                                          m_total_error_messages++;
                                          wxString msg;
                                          msg.Printf(_T("NMEA timeout"));
                                          ThreadMessage(msg);
                                    }
                                    break;

                              default:
                                  break;
                        }     // switch
                  }           // while
            }                 // if



HandleASuccessfulRead:

            if(dwRead > 0)
            {
                  if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
                  {
                        m_total_error_messages++;
                        wxString msg;
                        msg.Printf(_T("NMEA activity...%d bytes"), dwRead);
                        ThreadMessage(msg);
                  }

                  int nchar = dwRead;
                  char *pb = szBuf;

                  while(nchar)
                  {
                        if(0x0a == *pb)
                              nl_found = true;

                        *put_ptr++ = *pb++;
                        if((put_ptr - rx_buffer) > RX_BUFFER_SIZE)
                              put_ptr = rx_buffer;

                        nchar--;
                  }
                  if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
                  {
                        m_total_error_messages++;
                        wxString msg1;
                        msg1.Printf(_T("Buffer is %s"), szBuf);
                        ThreadMessage(msg1);
                  }

            }

//    Found a NL char, thus end of message?
            if(nl_found)
            {
                  char *tptr;
                  char *ptmpbuf;
                  char temp_buf[RX_BUFFER_SIZE];

                  bool partial = false;
                  while (!partial)
                  {

            //    Copy the message into a temp buffer

                    tptr = tak_ptr;
                    ptmpbuf = temp_buf;

                    while((*tptr != 0x0a) && (tptr != put_ptr))
                    {
                          *ptmpbuf++ = *tptr++;

                          if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                tptr = rx_buffer;
                    }

                    if((*tptr == 0x0a) && (tptr != put_ptr))    // well formed sentence
                    {
                          *ptmpbuf++ = *tptr++;
                          if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                tptr = rx_buffer;

                          *ptmpbuf = 0;

                          tak_ptr = tptr;

    // parse and send the message

                         wxString str_temp_buf(temp_buf, wxConvUTF8);
                         Parse_And_Send_Posn(str_temp_buf);

                   }
                   else
                   {
                      partial = true;
//                    ThreadMessage("partial");
                   }
                }                 // while !partial
            }           // nl found

       fWaitingOnRead = FALSE;

      }           // the big while...

//          Close the port cleanly
      m_pCommMan->CloseComPort(m_gps_fd);


fail_point:
thread_exit:
      m_launcher->SetSecThreadInActive();             // I am dead

      return 0;
}

#endif            // __WXMSW__


void OCP_NMEA_Thread::Parse_And_Send_Posn(wxString &str_temp_buf)
{
      if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
      {
            m_total_error_messages++;
            wxString msg(_T("NMEA Sentence received..."));
            msg.Append(str_temp_buf);
            ThreadMessage(msg);
      }

   // Send the NMEA string to the decoder
      m_NMEA0183 << str_temp_buf;

   // we must check the return from parse, as some usb to serial adaptors on the MAC spew
   // junk if there is not a serial data cable connected.
      if (true == m_NMEA0183.Parse())
      {
            if(m_NMEA0183.LastSentenceIDReceived == wxString(_T("RMC")))
            {
                  if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
                  {
                        m_total_error_messages++;
                        wxString msg(_T("NMEA RMC received..."));
                        ThreadMessage(msg);
                  }

              if(m_NMEA0183.Rmc.IsDataValid == NTrue)
              {

                  if(m_pShareMutex)
                        m_pShareMutex->Lock();

                  float llt = m_NMEA0183.Rmc.Position.Latitude.Latitude;
                  int lat_deg_int = (int)(llt / 100);
                  float lat_deg = lat_deg_int;
                  float lat_min = llt - (lat_deg * 100);
                  ThreadPositionData.kLat = lat_deg + (lat_min/60.);
                  if(m_NMEA0183.Rmc.Position.Latitude.Northing == South)
                        ThreadPositionData.kLat = -ThreadPositionData.kLat;

                  float lln = m_NMEA0183.Rmc.Position.Longitude.Longitude;
                  int lon_deg_int = (int)(lln / 100);
                  float lon_deg = lon_deg_int;
                  float lon_min = lln - (lon_deg * 100);
                  ThreadPositionData.kLon = lon_deg + (lon_min/60.);
                  if(m_NMEA0183.Rmc.Position.Longitude.Easting == West)
                        ThreadPositionData.kLon = -ThreadPositionData.kLon;

                  ThreadPositionData.kSog = m_NMEA0183.Rmc.SpeedOverGroundKnots;
                  ThreadPositionData.kCog = m_NMEA0183.Rmc.TrackMadeGoodDegreesTrue;
                  ThreadPositionData.FixTime = 0;

                  if(m_pShareMutex)
                        m_pShareMutex->Unlock();

                  if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
                  {
                        m_total_error_messages++;
                        wxString msg1(_T("EVT_NMEA_DIRECT sent"));
                        ThreadMessage(msg1);
                  }

 //    Signal the main program thread
                  wxCommandEvent event( EVT_NMEA,  GetId());
                  event.SetEventObject( (wxObject *)this );
                  event.SetExtraLong(EVT_NMEA_DIRECT);
                  event.SetClientData(&ThreadPositionData);
                  m_pMainEventHandler->AddPendingEvent(event);
              }
              else
              {
                    if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
                    {
                          m_total_error_messages++;
                          wxString msg(_T("   NMEA RMC Sentence is invalid..."));
                          msg.Append(str_temp_buf);
                          ThreadMessage(msg);
                    }
              }

            }
      }
      else
      {
            if((m_total_error_messages < NMAX_MESSAGE) && g_bNMEADebug)
            {
                  m_total_error_messages++;
                  wxString msg(_T("   Unrecognized NMEA Sentence..."));
                  msg.Append(str_temp_buf);
                  ThreadMessage(msg);
            }
      }

}


void OCP_NMEA_Thread::ThreadMessage(const wxString &msg)
{

    //    Signal the main program thread
      wxCommandEvent event( EVT_THREADMSG,  GetId());
      event.SetEventObject( (wxObject *)this );
      event.SetString(msg);
      m_pMainEventHandler->AddPendingEvent(event);

}



//-------------------------------------------------------------------------------------------------------------
//
//    Garmin USB Interface Thread
//
//    This thread manages reading the positioning data stream from the declared Garmin USB device
//
//-------------------------------------------------------------------------------------------------------------

#ifdef __WXMSW__


// {2C9C45C2-8E7D-4C08-A12D-816BBAE722C0}
DEFINE_GUID(GARMIN_GUID, 0x2c9c45c2L, 0x8e7d, 0x4c08, 0xa1, 0x2d, 0x81, 0x6b, 0xba, 0xe7, 0x22, 0xc0);


//-------------------------------------------------------------------------------------------------------------
//    OCP_GARMIN_Thread Implementation
//-------------------------------------------------------------------------------------------------------------

//    ctor

OCP_GARMIN_Thread::OCP_GARMIN_Thread(NMEAWindow *Launcher, wxWindow *MessageTarget, wxMutex *pMutex, const wxString& PortName)
{
      m_launcher = Launcher;                        // This thread's immediate "parent"

      m_pMainEventHandler = MessageTarget->GetEventHandler();

      rx_share_buffer_state = RX_BUFFER_EMPTY;

      m_PortName = PortName;

      m_pShareMutex = pMutex;

#ifdef __WXMSW__
      m_usb_handle = INVALID_HANDLE_VALUE;
#endif
      Create();
}

OCP_GARMIN_Thread::~OCP_GARMIN_Thread(void)
{
}

void OCP_GARMIN_Thread::OnExit(void)
{
}

//    Entry Point
void *OCP_GARMIN_Thread::Entry()
{
      wxMutexLocker *pStateLocker;

      m_launcher->SetSecThreadActive();               // I am alive

      bool not_done = true;
      char  pvt_on[14] =
            {20, 0, 0, 0, 10, 0, 0, 0, 2, 0, 0, 0, 49, 0};

      char  pvt_off[14] =
            {20, 0, 0, 0, 10, 0, 0, 0, 2, 0, 0, 0, 50, 0};

      garmin_usb_packet iresp;

      HDEVINFO hdevinfo;
      SP_DEVICE_INTERFACE_DATA devinterface;

      int n_short_read = 0;

      //    Search for the Garmin Device Interface Class
thread_retry:
      bool bgarmin_unit_found = false;
      int nmsg = 1;

      while(!bgarmin_unit_found)
      {
            if(nmsg > 0)
                  ThreadMsg(_T("Searching for Garmin DeviceInterface..."));

            hdevinfo = SetupDiGetClassDevs( (GUID *) &GARMIN_GUID, NULL, NULL,
                  DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

            if ((hdevinfo == INVALID_HANDLE_VALUE) && (nmsg > 0))
            {
                  ThreadMsg(_T("   SetupDiGetClassDevs failed for Garmin DeviceInterface..."));
                  ThreadMsg(_T("   Is the Garmin USB driver installed?"));

                  goto thread_exit;
            }

            devinterface.cbSize = sizeof(devinterface);

            bgarmin_unit_found = SetupDiEnumDeviceInterfaces(hdevinfo, NULL,(GUID *) &GARMIN_GUID, 0, &devinterface);

            if((!bgarmin_unit_found) && (nmsg > 0))
            {
                  ThreadMsg(_T("   SetupDiEnumDeviceInterfaces failed for Garmin DeviceInterface..."));
                  ThreadMsg(_T("   Is the Garmin USB unit powered up and connected?"));

            }

            if(nmsg > 0)
                  nmsg--;

            if(TestDestroy())
                  goto thread_exit;

            if(!bgarmin_unit_found)
                  wxSleep(1);
      }


      /* Now start the specific unit. */
      m_usb_handle = garmin_usb_start(hdevinfo, &devinterface);

      if(!m_usb_handle)
      {
            ThreadMsg(_T("   Garmin USB handle is NULL..."));
            nmsg = 1;
            goto thread_retry;
      }

      //    Send out a request for Garmin PVT data

      m_receive_state = rs_fromintr;
      gusb_cmd_send((const garmin_usb_packet *) pvt_on, sizeof(pvt_on));


      //    Here comes the big while loop
    while(not_done)
    {
            if(TestDestroy())
                  not_done = false;                               // smooth exit

      //    Get one pvt packet

            //    The Windows Garmin device driver (Version 2.21) is lame...
            //    There is no indication from the driver if the device is dynamically unplugged.
            //    The driver simply repeats the last packet, over and over, as fast as it bloody can.
            //    So, we must detect this condition by using a stopwatch to measure the expired time
            //    of a driver read.  Me will assume that some number of successive reads taking less than some
            //    (small) amount of time signal this condition.
            //    Sigh.....

            wxStopWatch st;
            st.Start();

            int nr = gusb_cmd_get(&iresp, sizeof(iresp));

            st.Pause();

            if(st.Time() < 100)
            {
                  if(++n_short_read > 20)         // device unplugged?
                        goto thread_retry;        // so start over
            }
            else
                  n_short_read = 0;




            if(iresp.gusb_pkt.pkt_id[0] == GUSB_RESPONSE_SDR)     //Satellite Data Record
            {
                  unsigned char *t = (unsigned char *)&(iresp.gusb_pkt.databuf[0]);
                  for(int i=0 ; i < 12 ; i++)
                  {
                        m_sat_data[i].svid =  *t++;
                        m_sat_data[i].snr =   ((*t)<<8) + *(t+1); t += 2;
                        m_sat_data[i].elev =  *t++;
                        m_sat_data[i].azmth = ((*t)<<8) + *(t+1); t += 2;
                        m_sat_data[i].status = *t++;
                  }
            }

            if(iresp.gusb_pkt.pkt_id[0] == GUSB_RESPONSE_PVT)     //PVT Data Record
            {


                  D800_Pvt_Data_Type *ppvt = (D800_Pvt_Data_Type *)&(iresp.gusb_pkt.databuf[0]);

                  if(m_pShareMutex)
                        pStateLocker = new wxMutexLocker(*m_pShareMutex) ;

                  /*  Lat/Lon   */
                  ThreadPositionData.kLat = ppvt->lat * 180./PI;
                  ThreadPositionData.kLon = ppvt->lon * 180. / PI;

                  /* speed over ground */
                  ThreadPositionData.kSog = sqrt(ppvt->east*ppvt->east + ppvt->north*ppvt->north) * 3.6 / 1.852;

                  /* course over ground */
                  double course = atan2(ppvt->east, ppvt->north);
                  if (course < 0)
                        course += 2*PI;
                  ThreadPositionData.kCog = course * 180 / PI;

                  ThreadPositionData.FixTime = 0;

                  if(m_pShareMutex)
                        delete pStateLocker ;


                  if((ppvt->fix) >= 2 && (ppvt->fix <= 5))
                  {
    //    Signal the main program thread
                        wxCommandEvent event( EVT_NMEA,  GetId() );
                        event.SetEventObject( (wxObject *)this );
                        event.SetExtraLong(EVT_NMEA_DIRECT);
                        event.SetClientData(&ThreadPositionData);
                        m_pMainEventHandler->AddPendingEvent(event);
                  }
            }

      }

      //    Send command to turn off PVT data
    gusb_cmd_send((const garmin_usb_packet *) pvt_off, sizeof(pvt_off));

      if (m_usb_handle != INVALID_HANDLE_VALUE)
      {
            CloseHandle(m_usb_handle);
            m_usb_handle = INVALID_HANDLE_VALUE;
      }


thread_exit:
      m_launcher->SetSecThreadInActive();             // I am dead
      return 0;
}


HANDLE OCP_GARMIN_Thread::garmin_usb_start(HDEVINFO hdevinfo, SP_DEVICE_INTERFACE_DATA *infodata)
{
      DWORD size = 0;
      PSP_INTERFACE_DEVICE_DETAIL_DATA pdd = NULL;
      SP_DEVINFO_DATA devinfo;

      SetupDiGetDeviceInterfaceDetail(hdevinfo, infodata,
                  NULL, 0, &size, NULL);

      pdd = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc(size);
      pdd->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);

      devinfo.cbSize = sizeof(SP_DEVINFO_DATA);
      if (!SetupDiGetDeviceInterfaceDetail(hdevinfo, infodata,
            pdd, size, NULL, &devinfo))
      {
            ThreadMsg(_T("   SetupDiGetDeviceInterfaceDetail failed for Garmin Device..."));
                  return NULL;
      }

      /* Whew.  All that just to get something we can open... */
      wxString msg;
      msg.Printf(_T("Windows GUID for interface is %s"),pdd->DevicePath);
      ThreadMsg(msg);

      m_usb_handle = CreateFile(pdd->DevicePath, GENERIC_READ|GENERIC_WRITE,
                  0, NULL, OPEN_EXISTING, 0, NULL );
      if (m_usb_handle == INVALID_HANDLE_VALUE)
      {
            wxString msg;
            msg.Printf(_T("(usb) CreateFile on '%s' failed"), pdd->DevicePath);
            ThreadMsg(msg);
            return NULL;
      }

      if(!DeviceIoControl(m_usb_handle, IOCTL_GARMIN_USB_BULK_OUT_PACKET_SIZE,
          NULL, 0, &m_max_tx_size, GARMIN_USB_INTERRUPT_DATA_SIZE,
          &size, NULL))
      {
      ThreadMsg(_T("   Couldn't get USB packet size."));
            return NULL;
    }

      if(!gusb_syncup())
      {
            CloseHandle(m_usb_handle);
            m_usb_handle = NULL;
      }

      free(pdd);
      return m_usb_handle;
}

bool OCP_GARMIN_Thread::gusb_syncup(void)
{
      static int unit_number;
      static const char  oinit[12] =
            {0, 0, 0, 0, GUSB_SESSION_START, 0, 0, 0, 0, 0, 0, 0};
      garmin_usb_packet iresp;
      int i;

      /*
       * This is our first communication with the unit.
       */
      m_receive_state = rs_fromintr;

      for(i = 0; i < 25; i++) {
            le_write16(&iresp.gusb_pkt.pkt_id[0], 0);
            le_write32(&iresp.gusb_pkt.datasz[0], 0);
            le_write32(&iresp.gusb_pkt.databuf[0], 0);

            if(!gusb_cmd_send((const garmin_usb_packet *) oinit, sizeof(oinit)))
            {
                  ThreadMsg(_T("   Unable to establish USB syncup due to TX error."));
                  return false;;
            }

            gusb_cmd_get(&iresp, sizeof(iresp));

            if ((le_read16(iresp.gusb_pkt.pkt_id) == GUSB_SESSION_ACK) &&
                  (le_read32(iresp.gusb_pkt.datasz) == 4))
            {
//                unsigned serial_number = le_read32(iresp.gusb_pkt.databuf);
//                garmin_unit_info[unit_number].serial_number = serial_number;
//                gusb_id_unit(&garmin_unit_info[unit_number]);

                  unit_number++;

                  ThreadMsg(_T("Successful Garmin USB syncup."));
                  return true;;
            }
      }
      ThreadMsg(_T("   Unable to establish USB syncup."));
      return false;
}


int OCP_GARMIN_Thread::gusb_cmd_send(const garmin_usb_packet *opkt, size_t sz)
{
      unsigned int rv;

      unsigned char *obuf = (unsigned char *) &opkt->dbuf[0];

      rv = gusb_win_send(opkt, sz);

      /*
       * Recursion, when used in a disciplined way, can be our friend.
       *
       * The Garmin protocol requires that packets that are exactly
       * a multiple of the max tx size be followed by a zero length
       * packet.  Do that here so we can see it in debugging traces.
       */

      if (sz && !(sz % m_max_tx_size)) {
            gusb_win_send(opkt, 0);
      }

      return (rv);
}

int OCP_GARMIN_Thread::gusb_cmd_get(garmin_usb_packet *ibuf, size_t sz)
{
      int rv;
      unsigned char *buf = (unsigned char *) &ibuf->dbuf[0];
      int orig_receive_state;
top:
      orig_receive_state = m_receive_state;
      switch (m_receive_state) {
      case rs_fromintr:
            rv = gusb_win_get(ibuf, sz);
            break;
      case rs_frombulk:
            rv = gusb_win_get_bulk(ibuf, sz);
            break;
//  default:
//          fatal("Unknown receiver state %d\n", receive_state);
      }

      /* Adjust internal state and retry the read */
      if ((rv > 0) && (ibuf->gusb_pkt.pkt_id[0] == GUSB_REQUEST_BULK)) {
            m_receive_state = rs_frombulk;
            goto top;
      }
      /*
       * If we were reading from the bulk pipe and we just got
       * a zero request, adjust our internal state.
       * It's tempting to retry the read here to hide this "stray"
       * packet from our callers, but that only works when you know
       * there's another packet coming.   That works in every case
       * except the A000 discovery sequence.
      */
      if ((m_receive_state == rs_frombulk) && (rv <= 0)) {
            m_receive_state = rs_fromintr;
      }

      return rv;
}

int OCP_GARMIN_Thread::gusb_win_get(garmin_usb_packet *ibuf, size_t sz)
{
      DWORD rxed = GARMIN_USB_INTERRUPT_DATA_SIZE;
      unsigned char *buf = (unsigned char *) &ibuf->dbuf[0];
      int tsz=0;

      while (sz)
      {
            /* The driver wrongly (IMO) rejects reads smaller than
             * GARMIN_USB_INTERRUPT_DATA_SIZE
             */
            if(!DeviceIoControl(m_usb_handle, IOCTL_GARMIN_USB_INTERRUPT_IN, NULL, 0,
                  buf, GARMIN_USB_INTERRUPT_DATA_SIZE, &rxed, NULL))
            {
//                GPS_Serial_Error("Ioctl");
//                fatal("ioctl\n");
            }

            buf += rxed;
            sz  -= rxed;
            tsz += rxed;
            if (rxed < GARMIN_USB_INTERRUPT_DATA_SIZE)
                  break;
      }
      return tsz;
}

int OCP_GARMIN_Thread::gusb_win_get_bulk(garmin_usb_packet *ibuf, size_t sz)
{
      int n;
      DWORD rsz;
      unsigned char *buf = (unsigned char *) &ibuf->dbuf[0];

      n = ReadFile(m_usb_handle, buf, sz, &rsz, NULL);

      return rsz;
}

int OCP_GARMIN_Thread::gusb_win_send(const garmin_usb_packet *opkt, size_t sz)
{
      DWORD rsz;
      unsigned char *obuf = (unsigned char *) &opkt->dbuf[0];

      /* The spec warns us about making writes an exact multiple
       * of the packet size, but isn't clear whether we can issue
       * data in a single call to WriteFile if it spans buffers.
       */
      WriteFile(m_usb_handle, obuf, sz, &rsz, NULL);

//    if (rsz != sz)
//          fatal ("Error sending %d bytes.   Successfully sent %ld\n", sz, rsz);


      return rsz;
}

void
le_write16(void *addr, const unsigned value)
{
      unsigned char *p = (unsigned char *)addr;
      p[0] = value;
      p[1] = value >> 8;

}

void
le_write32(void *addr, const unsigned value)
{
      unsigned char *p = (unsigned char *)addr;
      p[0] = value;
      p[1] = value >> 8;
      p[2] = value >> 16;
      p[3] = value >> 24;
}

signed int
le_read16(const void *addr)
{
      const unsigned char *p = (const unsigned char *)addr;
      return p[0] | (p[1] << 8);
}

signed int
le_read32(const void *addr)
{
      const unsigned char *p = (const unsigned char *)addr;
      return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
}



void OCP_GARMIN_Thread::ThreadMsg(const wxString &msg)
{

    //    Signal the main program thread
     wxCommandEvent event( EVT_THREADMSG,  GetId() );
     event.SetEventObject( (wxObject *)this );
     event.SetExtraLong(EVT_NMEA_DIRECT);
     event.SetString(msg);
     m_pMainEventHandler->AddPendingEvent(event);

}
#endif            // __WXMSW__

//-------------------------------------------------------------------------------------------------------------
//
//    Autopilot Class Implementation
//
//-------------------------------------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(AutoPilotWindow, wxWindow)
        EVT_CLOSE(AutoPilotWindow::OnCloseWindow)
END_EVENT_TABLE()

// Implement a constructor
AutoPilotWindow::AutoPilotWindow(wxFrame *frame, const wxString& AP_Port):
        wxWindow(frame, wxID_ANY,     wxPoint(20,20), wxSize(5,5), wxSIMPLE_BORDER)

{

      m_pdata_ap_port_string = new wxString(AP_Port);
      m_bOK = false;

//    Create and init the Serial Port for Autopilot control

      wxString msg(_T("NMEA AutoPilot Port is...."));
      msg.Append(*m_pdata_ap_port_string);
      wxLogMessage(msg);

      if((!m_pdata_ap_port_string->IsEmpty()) && (!m_pdata_ap_port_string->IsSameAs(_T("None"), false)))
      {
            m_port = m_pdata_ap_port_string->AfterFirst(':');    // Strip "Serial"

            m_bOK = OpenPort(m_port);
    }
    Hide();
}

AutoPilotWindow::~AutoPilotWindow()
{
    delete m_pdata_ap_port_string;
}

void AutoPilotWindow::GetAP_Port(wxString& source)
{
    source = *m_pdata_ap_port_string;
}

void AutoPilotWindow::OnCloseWindow(wxCloseEvent& event)
{
    if(m_bOK)
    {
          g_pCommMan->CloseComPort(m_ap_fd);
          m_bOK = false;
    }
}

bool AutoPilotWindow::OpenPort(wxString &port)
{
      if ((m_ap_fd = g_pCommMan->OpenComPort(port, 4800)) < 0)
      {
            wxString msg(_T("Autopilot output device open failed: "));
            msg.Append(port);
            wxLogMessage(msg);
            return false;
      }

      return true;
}




int AutoPilotWindow::AutopilotOut(const wxString& Sentence)
{
      ssize_t status;
      status = g_pCommMan->WriteComPort(m_port, Sentence);
      return status;
}

//-------------------------------------------------------------------------------------------------------------
//
//    Communications Port Manager
//
//-------------------------------------------------------------------------------------------------------------
#include <wx/listimpl.cpp>
WX_DEFINE_LIST(ListOfOpenCommPorts);

ComPortManager:: ComPortManager()
{
}

ComPortManager::~ComPortManager()
{
}

//    Common Methods

int ComPortManager::OpenComPort(wxString &com_name, int baud_rate)
{
      // Already open?
      int port_descriptor = GetComPort(com_name);
      if(-1 == port_descriptor)
      {
            port_descriptor = OpenComPortPhysical(com_name, 4800);
            if( port_descriptor < 0)
                  return port_descriptor;                                // error

            OpenCommPortElement *pocpe = new OpenCommPortElement;
            pocpe->com_name = com_name;
            pocpe->port_descriptor = port_descriptor;

            m_port_list.Append(pocpe);
      }

  //    wxString s;
  //    s.Printf("OpenPD: %d", port_descriptor);
  //    wxLogMessage(com_name);
  //    wxLogMessage(s);

      return port_descriptor;
}

int ComPortManager::CloseComPort(int fd)
{
      CloseComPortPhysical(fd);

      for ( ListOfOpenCommPorts::Node *node = m_port_list.GetFirst(); node; node = node->GetNext() )
      {
            OpenCommPortElement *current = node->GetData();

            if(current->port_descriptor == fd)
            {
                  m_port_list.DeleteObject(current);
                  delete current;
                  break;
            }
      }

      return 0;
}



//------------------------------------------------------------
//    GetComPort()
//    Return the descriptor for an already open com port.
//    return -1 if the port is not already open
//------------------------------------------------------------

int ComPortManager::GetComPort(wxString &com_name)
{
      for ( ListOfOpenCommPorts::Node *node = m_port_list.GetFirst(); node; node = node->GetNext() )
      {
            OpenCommPortElement *current = node->GetData();

            if(current->com_name.IsSameAs(com_name))
                  return current->port_descriptor;
      }

      return -1;
}

int ComPortManager::WriteComPort(wxString& com_name, const wxString& string)
{
      int port_descriptor = GetComPort(com_name);
      if(-1 == port_descriptor)
            port_descriptor = OpenComPort(com_name, 4800);

      int status = WriteComPortPhysical(port_descriptor, string);

      return status;
}


#ifdef __POSIX__
int ComPortManager::OpenComPortPhysical(wxString &com_name, int baud_rate)
{

    // Declare the termios data structures
      termios ttyset_old;
      termios ttyset;

    // Open the serial port.
      int com_fd;
      if ((com_fd = open(com_name.mb_str(), O_RDWR|O_NONBLOCK|O_NOCTTY)) < 0)
//      if ((com_fd = open(com_name.mb_str(), O_RDWR|O_NOCTTY)) < 0)
            return com_fd;


      speed_t baud_parm;
      switch(baud_rate)
      {
            case 4800:
                  baud_parm = B4800;
                  break;
            case 38400:
                  baud_parm = B38400;
                  break;
            default:
                  baud_parm = B4800;
                  break;
      }



     if (isatty(com_fd) != 0)
      {
            /* Save original terminal parameters */
            if (tcgetattr(com_fd,&ttyset_old) != 0)
                  return -128;

            memcpy(&ttyset, &ttyset_old, sizeof(termios));

      //  Build the new parms off the old

      //  Baud Rate
            cfsetispeed(&ttyset, baud_parm);
            cfsetospeed(&ttyset, baud_parm);

            tcsetattr(com_fd, TCSANOW, &ttyset);

      // Set blocking/timeout behaviour
            memset(ttyset.c_cc,0,sizeof(ttyset.c_cc));
            ttyset.c_cc[VTIME] = 5;                        // 0.5 sec timeout
            fcntl(com_fd, F_SETFL, fcntl(com_fd, F_GETFL) & !O_NONBLOCK);

      // No Flow Control

            ttyset.c_cflag &= ~(PARENB | PARODD | CRTSCTS);
            ttyset.c_cflag |= CREAD | CLOCAL;
            ttyset.c_iflag = ttyset.c_oflag = ttyset.c_lflag = (tcflag_t) 0;

            int stopbits = 1;
            char parity = 'N';
            ttyset.c_iflag &=~ (PARMRK | INPCK);
            ttyset.c_cflag &=~ (CSIZE | CSTOPB | PARENB | PARODD);
            ttyset.c_cflag |= (stopbits==2 ? CS7|CSTOPB : CS8);
            switch (parity)
            {
                  case 'E':
                        ttyset.c_iflag |= INPCK;
                        ttyset.c_cflag |= PARENB;
                        break;
                  case 'O':
                        ttyset.c_iflag |= INPCK;
                        ttyset.c_cflag |= PARENB | PARODD;
                        break;
            }
            ttyset.c_cflag &=~ CSIZE;
            ttyset.c_cflag |= (CSIZE & (stopbits==2 ? CS7 : CS8));
            if (tcsetattr(com_fd, TCSANOW, &ttyset) != 0)
                  return -129;

            tcflush(com_fd, TCIOFLUSH);
      }

      return com_fd;
}


int ComPortManager::CloseComPortPhysical(int fd)
{
        /* this is the clean way to do it */
//    pttyset_old->c_cflag |= HUPCL;
//    (void)tcsetattr(fd,TCSANOW,pttyset_old);

      close(fd);

      return 0;
}


int ComPortManager::WriteComPortPhysical(int port_descriptor, const wxString& string)
{
      ssize_t status;
      status = write(port_descriptor, string.mb_str(), string.Len());

      return status;
}

#endif            // __POSIX__

#ifdef __WXMSW__
int ComPortManager::OpenComPortPhysical(wxString &com_name, int baud_rate)
{

//    Set up the serial port
      HANDLE hSerialComm = CreateFile(com_name.mb_str(),      // Port Name
                                 GENERIC_READ | GENERIC_WRITE,     // Desired Access
                                 0,                               // Shared Mode
                                 NULL,                            // Security
                                 OPEN_EXISTING,             // Creation Disposition
                                 FILE_FLAG_OVERLAPPED,
                                 NULL);                           // Non Overlapped

      if(hSerialComm == INVALID_HANDLE_VALUE)
            return (::GetLastError());

      if(!SetupComm(hSerialComm, 1024, 1024))
            return (::GetLastError());

      DCB dcbConfig;

      if(GetCommState(hSerialComm, &dcbConfig))           // Configuring Serial Port Settings
      {
            dcbConfig.BaudRate = baud_rate;
            dcbConfig.ByteSize = 8;
            dcbConfig.Parity = NOPARITY;
            dcbConfig.StopBits = ONESTOPBIT;
            dcbConfig.fBinary = TRUE;
            dcbConfig.fParity = TRUE;
      }

      else
            return (::GetLastError());

      if(!SetCommState(hSerialComm, &dcbConfig))
            return (::GetLastError());

      COMMTIMEOUTS commTimeout;
      int TimeOutInSec = 2;

      if(GetCommTimeouts(hSerialComm, &commTimeout)) // Configuring Read & Write Time Outs
      {
            commTimeout.ReadIntervalTimeout = 1000*TimeOutInSec;
            commTimeout.ReadTotalTimeoutConstant = 1000*TimeOutInSec;
            commTimeout.ReadTotalTimeoutMultiplier = 0;
            commTimeout.WriteTotalTimeoutConstant = 1000*TimeOutInSec;
            commTimeout.WriteTotalTimeoutMultiplier = 0;
      }

      else
            return (::GetLastError());

      if(!SetCommTimeouts(hSerialComm, &commTimeout))
            return (::GetLastError());


      return (int)hSerialComm;
}

int ComPortManager::CloseComPortPhysical(int fd)
{
      if((HANDLE)fd != INVALID_HANDLE_VALUE)
            CloseHandle((HANDLE)fd);
      return 0;
}

int ComPortManager::WriteComPortPhysical(int port_descriptor, const wxString& string)
{
      unsigned int dwSize = string.Len();
      char *pszBuf = (char *)malloc((dwSize + 1) * sizeof(char));
      strncpy(pszBuf, string.mb_str(), dwSize+1);

//      wxLogMessage(string);

      OVERLAPPED osWrite = {0};
      DWORD dwWritten;
      int fRes;

   // Create this writes OVERLAPPED structure hEvent.
      osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
      if (osWrite.hEvent == NULL)
      // Error creating overlapped event handle.
            return 0;

   // Issue write.
      if (!WriteFile((HANDLE)port_descriptor, pszBuf, dwSize, &dwWritten, &osWrite))
      {
            if (GetLastError() != ERROR_IO_PENDING)
            {
         // WriteFile failed, but it isn't delayed. Report error and abort.
                  fRes = 0;
            }
            else
            {
         // Write is pending.
                  if (!GetOverlappedResult((HANDLE)port_descriptor, &osWrite, &dwWritten, TRUE))
                        fRes = 0;
                  else
            // Write operation completed successfully.
                        fRes = dwWritten;
            }
      }
      else
      // WriteFile completed immediately.
            fRes = dwWritten;

      CloseHandle(osWrite.hEvent);

      free (pszBuf);

//      wxString m;
//      m.Printf("Result %d",fRes);
//      wxLogMessage(m);

      return fRes;
}

#endif            // __WXMSW__

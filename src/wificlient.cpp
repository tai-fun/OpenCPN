/******************************************************************************
 * $Id: wificlient.cpp,v 1.2 2006/09/21 01:37:37 dsr Exp $
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
 * $Log: wificlient.cpp,v $
 * Revision 1.2  2006/09/21 01:37:37  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.4  2006/08/04 11:42:03  dsr
 * no message
 *
 * Revision 1.3  2006/07/28 20:43:39  dsr
 * Implement watchdog
 *
 * Revision 1.2  2006/07/06 23:14:59  dsr
 * Add WiFi Server Status Display
 *
 * Revision 1.1  2006/07/05 02:36:21  dsr
 * Add WiFi Client
 *
 *
 */

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include "dychart.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "dychart.h"

#include "wificlient.h"
#include "chart1.h"
#include "statwin.h"

extern StatWin          *stats;

static int              wifi_s_dns_test_flag;

CPL_CVSID("$Id: wificlient.cpp,v 1.2 2006/09/21 01:37:37 dsr Exp $");

//------------------------------------------------------------------------------
//    WIFI Window Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(WIFIWindow, wxWindow)
        EVT_PAINT(WIFIWindow::OnPaint)
        EVT_ACTIVATE(WIFIWindow::OnActivate)
        EVT_CLOSE(WIFIWindow::OnCloseWindow)

        EVT_SOCKET(WIFI_SOCKET_ID, WIFIWindow::OnSocketEvent)
        EVT_TIMER(TIMER_WIFI1, WIFIWindow::OnTimer1)

        END_EVENT_TABLE()

// A constructor
WIFIWindow::WIFIWindow(wxFrame *frame, const wxString& WiFiServerName):
        wxWindow(frame, wxID_ANY,     wxPoint(20,20), wxSize(5,5), wxSIMPLE_BORDER)

{
    parent_frame = (MyFrame *)frame;
    m_sock = NULL;

    m_pdata_server_string = new wxString(WiFiServerName);

    m_watchtick = 0;

//    Decide upon Server source
      wxLogMessage("WiFi Server is....%s",m_pdata_server_string->c_str());

      if(m_pdata_server_string->Contains("TCP/IP"))
      {
          wxString WIFI_data_ip;
          WIFI_data_ip = m_pdata_server_string->Mid(7);         // extract the IP

// Create the socket
          m_sock = new wxSocketClient();

// Setup the event handler and subscribe to most events
          m_sock->SetEventHandler(*this, WIFI_SOCKET_ID);

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

          WIFIDNSTestThread *ptest_thread = NULL;
          ptest_thread = new WIFIDNSTestThread(WIFI_data_ip);

          ptest_thread->Run();                      // Run the thread from ::Entry()


//    Sleep and loop for N seconds
#define SLEEP_TEST_SEC  2

          for(int is=0 ; is<SLEEP_TEST_SEC * 10 ; is++)
          {
            wxMilliSleep(100);
            if(wifi_s_dns_test_flag)
            break;
          }

          if(!wifi_s_dns_test_flag)
          {

            wxString msg(WIFI_data_ip);
            msg.Prepend("Could not resolve TCP/IP host '");
            msg.Append("'\n Suggestion: Try 'xxx.xxx.xxx.xxx' notation");
            wxMessageDialog md(this, msg, "OpenCPN Message", wxICON_ERROR );
            md.ShowModal();

            m_sock->Notify(FALSE);
            m_sock->Destroy();

            return;
          }

          addr.Hostname(WIFI_data_ip);
          addr.Service(SERVER_PORT);
          m_sock->Connect(addr, FALSE);       // Non-blocking connect

            //  Initialize local data stores
          for(int ilocal = 0 ; ilocal < NLOCALSTORE ; ilocal++)
          {
               station_data[ilocal].bisvalid = false;
          }

          Timer1.SetOwner(this, TIMER_WIFI1);
          m_scan_interval_msec = 10000;
          Timer1.Start(m_scan_interval_msec,wxTIMER_CONTINUOUS);
      }
}


WIFIWindow::~WIFIWindow()
{
    delete m_pdata_server_string;
}

void WIFIWindow::OnCloseWindow(wxCloseEvent& event)
{
//    Kill off the WIFI Client Socket if alive
    if(m_sock)
    {
        m_sock->Notify(FALSE);
        m_sock->Destroy();
        Timer1.Stop();
    }
}


void WIFIWindow::GetSource(wxString& source)
{
    source = *m_pdata_server_string;
}



void WIFIWindow::OnActivate(wxActivateEvent& event)
{
}

void WIFIWindow::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
}

void WIFIWindow::Pause(void)
{
    Timer1.Stop();

    if(m_sock)
        m_sock->Notify(FALSE);
}

void WIFIWindow::UnPause(void)
{
    Timer1.Start(1000,wxTIMER_CONTINUOUS);

    if(m_sock)
        m_sock->Notify(TRUE);
}


void WIFIWindow::OnSocketEvent(wxSocketEvent& event)
{

//    wxString s = _("OnSocketEvent: ");
    wifi_scan_data *pt;

    int i;
    int ilocal;

    switch(event.GetSocketEvent())
    {
        case wxSOCKET_INPUT :
            m_sock->SetFlags(wxSOCKET_WAITALL); // | wxSOCKET_BLOCK );

            unsigned char buf[1024];

//          Read the reply, waiting forever for all data to be read
            m_sock->Read(buf, WIFI_SCAN_RESULT_BUFFER_LENGTH);

            m_bRX = true;                       // reset watchdog
            m_watchtick = 0;


            //  Manage the data input

            int pt_eaten[NSCAN_DATA_STRUCT];

            //  Some setup
            for(i=0 ; i < NSCAN_DATA_STRUCT ; i++)
                pt_eaten[i] = false;


            //  First, check to see if any input station data is already present in local store
            //  If it is (ESSID matches), then simply update the signal quality, and refresh the age.
            //  Also, flag the fact that the input data has been eaten.

            for(i=0 ; i < NSCAN_DATA_STRUCT ; i++)
            {
                pt = (wifi_scan_data *)(&buf[i * 256]);
                if(strlen(pt->ESSID))
                {
                    for(ilocal = 0 ; ilocal < NLOCALSTORE ; ilocal++)
                    {
                        if((!strcmp(pt->ESSID, station_data[ilocal].ESSID)) && (station_data[ilocal].bisvalid))
                        {
                            station_data[ilocal].sig_quality = pt->sig_quality;
                            station_data[ilocal].age = -1;
                            pt_eaten[i] = true;
                        }
                    }
                }
            }

            //  Now, age the local store by one
            for(ilocal = 0 ; ilocal < NLOCALSTORE ; ilocal++)
                if(station_data[ilocal].bisvalid)
                    station_data[ilocal].age ++;

            //  and free any entries that are over the specified age
            for(ilocal = 0 ; ilocal < NLOCALSTORE ; ilocal++)
            {
                if((station_data[ilocal].bisvalid) && (station_data[ilocal].age >= N_AGEDEATH))
                {
                    station_data[ilocal].bisvalid = false;
                    station_data[ilocal].ESSID[0] = 0;
                }
            }


            //  Now, check to see if any input data is un-eaten
            //  If found, then try to allocate to a local store item
            for(i=0 ; i < NSCAN_DATA_STRUCT ; i++)
            {
                if(pt_eaten[i] == false)
                {
                    pt = (wifi_scan_data *)(&buf[i * 256]);
                    if(strlen(pt->ESSID))
                    {
                        for(ilocal = 0 ; ilocal < NLOCALSTORE ; ilocal++)
                        {
                            if(station_data[ilocal].bisvalid == false)
                            {
                                strcpy(station_data[ilocal].ESSID, pt->ESSID);
                                station_data[ilocal].sig_quality = pt->sig_quality;
                                station_data[ilocal].secure = pt->secure;
                                station_data[ilocal].bisvalid = true;
                                station_data[ilocal].age = 0;
                                pt_eaten[i] = true;
                                break;
                            }
                        }
                    }
                }
            }

            //  There may still be un-eaten input data at this point......
            //  For now, ignore it.  If it is real, it will appear as soon as something else dies

            // Finally, send the data to the display window
            for(ilocal = 0 ; ilocal < NLOCALSTORE ; ilocal++)
            {
                if(station_data[ilocal].bisvalid)
                {
                    stats->pWiFi->SetStationQuality(ilocal, station_data[ilocal].sig_quality);
                    stats->pWiFi->SetStationSecureFlag(ilocal, station_data[ilocal].secure);
                    stats->pWiFi->SetStationAge(ilocal, station_data[ilocal].age);
                }
                else
                    stats->pWiFi->SetStationQuality(ilocal, 0);
            }
            stats->Refresh(true);

            break;

        case wxSOCKET_LOST       :
            break;
        case wxSOCKET_CONNECTION :
            break;
        default                  :
            break;
    }

}


void WIFIWindow::OnTimer1(wxTimerEvent& event)
{
    Timer1.Stop();

       if(m_sock->IsConnected())
    {
        //      Keep a watchdog on received data
        if(stats)
        {
            if(m_watchtick++ > WIFI_DOG_TIMEOUT)       // nothing received recently
            {
                stats->pWiFi->SetServerStatus(false);
                stats->Refresh(true);
            }
            else
                stats->pWiFi->SetServerStatus(true);
        }

        unsigned char c = WIFI_TRANSMIT_DATA;       // and call for more data
        m_sock->Write(&c, 1);
    }
    else                                     // try to connect
    {
        if(stats)
        {
            stats->pWiFi->SetServerStatus(false);
            stats->Refresh(true);
        }
        m_sock->Connect(addr, FALSE);       // Non-blocking connect
    }

    m_bRX = false;
    Timer1.Start(m_scan_interval_msec,wxTIMER_CONTINUOUS);
}


//-------------------------------------------------------------------------------------------------------------
//
//    A simple thread to test host name resolution without blocking the main thread
//
//-------------------------------------------------------------------------------------------------------------
WIFIDNSTestThread::WIFIDNSTestThread(wxString &name_or_ip)
{
    m_pip = new wxString(name_or_ip);

    Create();
}

WIFIDNSTestThread::~WIFIDNSTestThread()
{
    delete m_pip;
}


void *WIFIDNSTestThread::Entry()
{
    wifi_s_dns_test_flag = 0;

    wxIPV4address     addr;
    addr.Hostname(*m_pip);                          // this may block forever if DNS is not active

    wifi_s_dns_test_flag = 1;                       // came back OK
    return NULL;
}


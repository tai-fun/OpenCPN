/******************************************************************************
 * $Id: ais.cpp,v 1.2 2007/02/06 02:04:51 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  AIS Decoder Object
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
 * $Log: ais.cpp,v $
 * Revision 1.2  2007/02/06 02:04:51  dsr
 * Correct text decode algorithm
 *
 * Revision 1.1  2006/11/01 02:17:37  dsr
 * AIS Support
 *
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "wx/tokenzr.h"
#include "wx/datetime.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "dychart.h"

#include "ais.h"
#include "chart1.h"
#include "nmea.h"           // for DNSTestThread
#include "navutil.h"        // for Select

extern  OCP_AIS_Thread  *pAIS_Thread;
extern  wxString        *pAISDataSource;
extern  int             s_dns_test_flag;
extern  Select          *pSelectAIS;

CPL_CVSID("$Id: ais.cpp,v 1.2 2007/02/06 02:04:51 dsr Exp $");


char test_str[24][79] = {

"!AIVDM,1,1,,A,15Mnh`PP0jIcl78Csm`hCgvB2D00,0*29**",
"!AIVDM,2,1,1,A,55Mnh`P00001L@7S3GP=Dl8E8h4pB2222222220P0`A6357d07PT851F,0*75**",
"!AIVDM,2,2,1,A,0Dp0jE6H8888880,2*40**",
"!AIVDM,1,1,,A,15Mnh`PP0rIce3VCr8nPWgvt24B0,0*10**",
"!AIVDM,1,1,,A,15Mnh`PP0pIcfJ<Cs0lPFwwR24Bt,0*6B**",
"!AIVDM,1,1,,A,15Mnh`PP0pIcfKBCs23P6gvB2D00,0*7E**",
"!AIVDM,1,1,,A,15Mnh`PP0nIcfL8Cs3DPLwvt28AV,0*5C**",
"!AIVDM,1,1,,A,15Mnh`PP0mIcfSlCs7w@KOwT2L00,0*4E**",
"!AIVDM,1,1,,A,15Mnh`PP0lIcjQRCsOK1LwvB2D00,0*6A**",
"!AIVDM,1,1,,A,15Mnh`PP0mIcj`NCsPNADOvt2@AQ,0*3E**",
"!AIVDM,1,1,,A,15Mnh`PP0mIcjfhCsQLAHOwT24H0,0*2C**",
"!AIVDM,1,1,,A,15Mnh`PP0mIcjlNCsRCiBwvB2@4s,0*4A**",
"!AIVDM,1,1,,A,15Mnh`PP0nIck5@CsUBi2gvB2<00,0*42**",
"!AIVDM,1,1,,A,15Mnh`PP0nIck:PCsVO0uOvt28AQ,0*47**",
"!AIVDM,1,1,,A,15Mnh`PP0oIck?:CsWQi0?wR2L00,0*19**",
"!AIVDM,1,1,,A,15Mnh`PP0oIckRVCscni3gvB24H@,0*29**",
"!AIVDM,1,1,,A,15Mnh`PP0pIck`VCse0i8wvt20Rg,0*48**",
"!AIVDM,1,1,,A,15Mnh`PP0nIckelCsf0hrgwR2D00,0*57**",
"!AIVDM,1,1,,A,15Mnh`PP0mIckiHCsfn@kOvB20S4,0*39**",
"!AIVDM,1,1,,A,15Mnh`PP0nIckmtCsh<0h?vr2HA6,0*05**",
"!AIVDM,1,1,,A,15Mnh`PP0nIckqdCsiC@iOwR2@LP,0*34**",
"!AIVDM,1,1,,A,15Mnh`PP0nIckttCsjEhdgvB2H4m,0*75**",
"!AIVDM,1,1,,A,15Mnh`PP0mIcl0jCskPhiwvr2D00,0*47**",
"!AIVDM,1,1,,A,15Mnh`PP0mIcl4hCslVhb?wR2<00,0*5A**",

};

//-------------------------------------------------------------------------------------------------------------
//    OCP_AIS_Thread Static data store
//-------------------------------------------------------------------------------------------------------------

extern char                         ais_rx_share_buffer[MAX_RX_MESSSAGE_SIZE];
extern unsigned int                 ais_rx_share_buffer_length;
extern ENUM_BUFFER_STATE            ais_rx_share_buffer_state;
extern wxMutex                      *ais_ps_mutexProtectingTheRXBuffer;




//---------------------------------------------------------------------------------
//
//  AIS_Target_Data Implementation
//
//---------------------------------------------------------------------------------
AIS_Target_Data::AIS_Target_Data()
{
    strcpy(&ShipName[0], "UNKNOWN             ");
}

//---------------------------------------------------------------------------------
//
//  AIS_Decoder Helpers
//
//---------------------------------------------------------------------------------
AIS_Bitstring::AIS_Bitstring(const char *str)
{
    byte_length = strlen(str);

    for(int i=0 ; i<byte_length ; i++)
    {
        bitbytes[i] = to_6bit(str[i]);
    }
}


//  Convert printable characters to IEC 6 bit representation
//  according to rules in IEC AIS Specification
unsigned char AIS_Bitstring::to_6bit(const char c)
{
    if(c < 0x30)
        return (unsigned char)-1;
    if(c > 0x77)
        return (unsigned char)-1;
    if((0x57 < c) && (c < 0x60))
        return (unsigned char)-1;

    unsigned char cp = c;
    cp += 0x28;

    if(cp > 0x80)
        cp += 0x20;
    else
        cp += 0x28;

    return (cp & 0x3f);
}


int AIS_Bitstring::GetInt(int sp, int len)
{
    int acc = 0;
    int s0p = sp-1;                          // to zero base

    int cp, cx, c0, cs;


    for(int i=0 ; i<len ; i++)
    {
        acc  = acc << 1;
        cp = (s0p + i) / 6;
        cx = bitbytes[cp];
        cs = 5 - ((s0p + i) % 6);
        c0 = (cx >> (5 - ((s0p + i) % 6))) & 1;
        acc |= c0;
    }

    return acc;

}

bool AIS_Bitstring::GetStr(int sp, int len, char *dest, int max_len)
{
    char temp_str[85];

    char acc = 0;
    int s0p = sp-1;                          // to zero base

    int k=0;
    int cp, cx, c0, cs;

    int i = 0;
    while(i < len)
    {
         acc=0;
         for(int j=0 ; j<6 ; j++)
         {
            acc  = acc << 1;
            cp = (s0p + i) / 6;
            cx = bitbytes[cp];
            cs = 5 - ((s0p + i) % 6);
            c0 = (cx >> (5 - ((s0p + i) % 6))) & 1;
            acc |= c0;

            i++;
         }
         temp_str[k] = acc & 0x3f;

         if(acc < 32)
             temp_str[k] += 0x40;
         k++;

    }

    temp_str[k] = 0;

    int copy_len = wxMin((int)strlen(temp_str), max_len);
    strncpy(dest, temp_str, copy_len);

    return true;
}





//---------------------------------------------------------------------------------
//
//  AIS_Decoder Implementation
//
//---------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(AIS_Decoder, wxWindow)
  EVT_CLOSE(AIS_Decoder::OnCloseWindow)

  EVT_SOCKET(AIS_SOCKET_ID, AIS_Decoder::OnSocketEvent)
  EVT_TIMER(TIMER_AIS1, AIS_Decoder::OnTimerAIS)
  EVT_COMMAND(ID_AIS_WINDOW, EVT_AIS, AIS_Decoder::OnEvtAIS)

  END_EVENT_TABLE()




AIS_Decoder::AIS_Decoder(int window_id, wxFrame *pParent, const wxString& AISDataSource):
      wxWindow(pParent, window_id, wxPoint(20,30), wxSize(5,5), wxSIMPLE_BORDER)

{
    AISTargetList = new AIS_Target_Hash;

    OpenDataSource(pParent, AISDataSource);

    Hide();
}

AIS_Decoder::~AIS_Decoder(void)
{
    AIS_Target_Hash::iterator it;
    AIS_Target_Hash *current_targets = GetTargetList();

    for( it = (*current_targets).begin(); it != (*current_targets).end(); ++it )
    {
          AIS_Target_Data *td = it->second;

          delete td;
    }

    delete current_targets;

    delete m_pdata_source_string;

}

//----------------------------------------------------------------------------------
//     Handle events from AIS Serial Port RX thread
//----------------------------------------------------------------------------------
void AIS_Decoder::OnEvtAIS(wxCommandEvent& event)
{

#define LOCAL_BUFFER_LENGTH 4096

    char buf[LOCAL_BUFFER_LENGTH];


    switch(event.GetExtraLong())
    {
        case EVT_AIS_PARSE_RX:
        {
            if(ais_ps_mutexProtectingTheRXBuffer->Lock() == wxMUTEX_NO_ERROR )
        {
                if(RX_BUFFER_FULL == ais_rx_share_buffer_state)
                {
                    int nchar = strlen(ais_rx_share_buffer);
                    strncpy (buf, ais_rx_share_buffer, wxMin(nchar + 1, LOCAL_BUFFER_LENGTH - 1));
                    ais_rx_share_buffer_state = RX_BUFFER_EMPTY;

                    if(ais_rx_share_buffer_length != strlen(ais_rx_share_buffer))
                        wxLogMessage("Got AIS Event with inconsistent ais_rx_share_buffer");
                }
                else
                     wxLogMessage("Got AIS Event with RX_BUFFER_EMPTY");

                ais_ps_mutexProtectingTheRXBuffer->Unlock();
        }


/*
                if(pStatusBar)
                {
                    wxString buf_nolf(buf);
                    buf_nolf.RemoveLast();
                    SetStatusText(buf_nolf.c_str(), 4);
                }
*/

            Decode(buf);

            break;
        }       //case


    }           // switch

/*    if(bshow_tick)
    {
    //      Show a little heartbeat tick in StatusWindow0 on AIS events

        if(tick_idx++ > 6)
            tick_idx = 0;

        char tick_buf[2];
        tick_buf[0] = nmea_tick_chars[tick_idx];
        tick_buf[1] = 0;
        if(NULL != GetStatusBar())
            SetStatusText(tick_buf, 0);
    }
*/
}



//----------------------------------------------------------------------------------
//      Decode NMEA VDM sentence to AIS Target(s)
//----------------------------------------------------------------------------------
AIS_Error AIS_Decoder::Decode(char *str)
{
    AIS_Error ret;
    wxString string_to_parse;

    //  Make some simple tests for validity

    if(strlen(str) > 82)
        return AIS_NMEAVDM_TOO_LONG;

    if(!NMEACheckSumOK(str))
        return AIS_NMEAVDM_CHECKSUM_BAD;

    if(strncmp(&str[3], "VDM", 3))
        return AIS_NMEAVDM_BAD;

    //  OK, looks like the sentence is OK

    //  Use a tokenizer to pull out the first 4 fields
    wxString string(str);
    wxStringTokenizer tkz(string, ",");

    wxString token;
    token = tkz.GetNextToken();         // !xxVDM

    token = tkz.GetNextToken();
    nsentences = atoi(token.c_str());

    token = tkz.GetNextToken();
    isentence = atoi(token.c_str());

    token = tkz.GetNextToken();
    int sequence_id;
    if(token.IsNumber())
        sequence_id = atoi(token.c_str());
    else
        sequence_id = 0;

    token = tkz.GetNextToken();
    int channel;
    if(token.IsNumber())
        channel = atoi(token.c_str());
    else
        channel = 0;


    //  Now, some decisions

    string_to_parse.Clear();

    //  Simple case first
    //  First and only part of a one-part sentence
    if((1 == nsentences) && (1 == isentence))
    {
        string_to_parse = tkz.GetNextToken();         // the encapsulated data
    }

    else if(nsentences > 1)
    {
        if(1 == isentence)
        {
            sentence_accumulator = tkz.GetNextToken();         // the encapsulated data
        }

        else
        {
            sentence_accumulator += tkz.GetNextToken();
        }

        if(isentence == nsentences)
        {
            string_to_parse = sentence_accumulator;
        }
     }


    if(!string_to_parse.IsEmpty())
    {
        //  Create the bit accessible string
        AIS_Bitstring strbit(string_to_parse.c_str());

        //  And create a provisional target
        AIS_Target_Data *td = Parse_VDMBitstring(&strbit);
        AIS_Target_Data *temp = NULL;
        AIS_Target_Data *tm = NULL;

        if(td)
        {
        //  Search the current AISTargetList for an MMSI match
            AIS_Target_Hash::iterator it = AISTargetList->find( td->MMSI );
            if(it == AISTargetList->end())                  // not found
            {
                (*AISTargetList)[td->MMSI] = td;            // so insert this entry
                tm = td;
            }
            else
            {
                temp = (*AISTargetList)[td->MMSI];          // find current entry
                tm = Merge(temp, td);                       // merge in new data

                (*AISTargetList)[td->MMSI] = tm;            // replace the current entry
                delete temp;                                // and kill the old one
                delete td;
            }

        //  Update the AIS Target Selectable list

            pSelectAIS->DeleteSelectablePoint((void *)temp, SELTYPE_AISTARGET);
            pSelectAIS->AddSelectablePoint(tm->Lat, tm->Lon, (void *)tm, SELTYPE_AISTARGET);

            ret = AIS_NoError;
        }
    }
    else
        ret = AIS_Partial;


    return ret;
}


AIS_Target_Data *AIS_Decoder::Merge(AIS_Target_Data *tlast, AIS_Target_Data *tthis)
{
     AIS_Target_Data *result = new AIS_Target_Data;

     if((tlast->MID == 1) && (tthis->MID == 5))
     {
         *result = *tlast;
         strncpy(&result->ShipName[0], &tthis->ShipName[0], 21);
     }

     if((tlast->MID == 5) && (tthis->MID == 1))
     {
         *result = *tthis;
         strncpy(&result->ShipName[0], &tlast->ShipName[0], 21);
     }

      if((tlast->MID == 1) && (tthis->MID == 1))
     {
         *result = *tthis;
         strncpy(&result->ShipName[0], &tlast->ShipName[0], 21);
     }


     return result;
}

//----------------------------------------------------------------------------
//      Parse a NMEA VDM Bitstring
//      Returns a pointer to a new AIS_Target_Data object,
//      which is to be owned BY THE CALLER
//----------------------------------------------------------------------------
AIS_Target_Data *AIS_Decoder::Parse_VDMBitstring(AIS_Bitstring *bstr)
{
    AIS_Target_Data *res_ptr = NULL;
    AIS_Target_Data atd;                    // temporary
    bool parse_result = false;

    wxDateTime now = wxDateTime::Now();
    now.MakeGMT();

    int utc_hour = now.GetHour();
    int utc_min = now.GetMinute();
    int utc_sec = now.GetSecond();
    int utc_day = now.GetDay();
    wxDateTime::Month utc_month = now.GetMonth();
    int utc_year = now.GetYear();
    atd.ReportTicks = now.GetTicks();       // Default is my idea of NOW
                                            // which amy disagee with target...

    int message_ID = bstr->GetInt(1, 6);        // Parse on message ID

    switch (message_ID)
    {
    case 1:                                 // Position Report
    case 2:
    case 3:
        {
            atd.MID = message_ID;
            atd.MMSI = bstr->GetInt(9, 30);
            atd.NavStatus = bstr->GetInt(39, 4);
            atd.SOG = 0.1 * (bstr->GetInt(51, 10));

            int lon = bstr->GetInt(62, 28);
            if(lon & 0x08000000)                    // negative?
                lon |= 0xf0000000;
            atd.Lon = lon / 600000.;

            int lat = bstr->GetInt(90, 27);
            if(lat & 0x04000000)                    // negative?
                lat |= 0xf8000000;
            atd.Lat = lat / 600000.;

            atd.COG = 0.1 * (bstr->GetInt(117, 12));
            atd.HDG = 1.0 * (bstr->GetInt(129, 9));
            utc_sec = bstr->GetInt(138, 6);

            if((1 == message_ID) || (2 == message_ID))      // decode SOTDMA per 7.6.7.2.2
            {
                atd.SyncState = bstr->GetInt(151,2);
                atd.SlotTO = bstr->GetInt(153,2);
                if((atd.SlotTO == 1) && (atd.SyncState == 0)) // UTCDirect follows
                {
                    utc_hour = bstr->GetInt(155, 5);
                    utc_min = bstr->GetInt(160,7);
                }
            }

            if((111111111 == atd.MMSI) || (181.0 == atd.Lon) || (91.0 == atd.Lat))      // bogus data
                parse_result = false;
            else
            {
                //  Todo there may be a bug here.  Sometimes get invalid utc_hour, utc_min
                if((utc_hour < 24) && (utc_min < 60) && (utc_sec < 60))
                {
                    wxDateTime report_time(utc_day, utc_month, utc_year, utc_hour, utc_min, utc_sec, 0);
                    atd.ReportTicks = report_time.GetTicks();
                    parse_result = true;
                }
                else
                    parse_result = false;
            }
            break;
        }

    case 5:
        {
            atd.MID = message_ID;
            atd.MMSI = bstr->GetInt(9, 30);
            int DSI = bstr->GetInt(39, 2);
            if(0 == DSI)
            {
                bstr->GetStr(71,42, &atd.CallSign[0], 7);
                bstr->GetStr(113,120, &atd.ShipName[0], 20);
                atd.ShipType = (unsigned char)bstr->GetInt(233,8);

                parse_result = true;
            }
            break;
        }
    }


    if(true == parse_result)
    {
        res_ptr = new AIS_Target_Data;
        *res_ptr = atd;                                    // shallow copy is OK
    }

    return res_ptr;
}



bool AIS_Decoder::NMEACheckSumOK(char *str)
{

   unsigned char checksum_value = 0;
   int sentence_hex_sum;

   int string_length = strlen(str);;
   int index = 1; // Skip over the $ at the begining of the sentence

   while( index < string_length    &&
          str[ index ] != '*' &&
          str[ index ] != 0x0d &&
          str[ index ] != 0x0a )
   {
      checksum_value ^= str[ index ];
      index++;
   }

   if(string_length > 4)
   {
        char scanstr[3];
        scanstr[0] = str[string_length-4];
        scanstr[1] = str[string_length - 3];
        scanstr[2] = 0;
        sscanf(scanstr, "%2x", &sentence_hex_sum);
        if(sentence_hex_sum == checksum_value)
            return true;
   }

   return false;
}

//------------------------------------------------------------------------------------
//
//  AIS Target Query Support
//
//------------------------------------------------------------------------------------

//  Build a query response
//  Resulting string to OWNED BY CALLER
wxString *AIS_Decoder::BuildQueryResult(AIS_Target_Data *td)
{
    wxString *res = new wxString;
    wxString line;


    //  Clip any unused characters (@) from the name
    wxString ts;
    char *tp = &td->ShipName[0];
    while((*tp) && (*tp != '@'))
       ts.Append(*tp++);
    ts.Append((char)0);

    line.Printf("ShipName:  %s\n\n", ts.c_str());
    res->Append(line);

    line.Printf("Course: %6.0f Deg.\n", td->COG);
    res->Append(line);

    line.Printf("Speed: %5.2f Kts.\n", td->SOG);
    res->Append(line);

    wxDateTime now = wxDateTime::Now();
    now.MakeGMT();
    int target_age = now.GetTicks() - td->ReportTicks;
    line.Printf("Report Age: %d Sec.\n", target_age);
    res->Append(line);

    return res;
}



//------------------------------------------------------------------------------------
//
//      AIS Data Source Support
//
//------------------------------------------------------------------------------------


AIS_Error AIS_Decoder::OpenDataSource(wxFrame *pParent, const wxString& AISDataSource)
{
      m_pParentEventHandler = pParent->GetEventHandler();

      pAIS_Thread = NULL;
      m_sock = NULL;

      TimerAIS.SetOwner(this, TIMER_AIS1);
      TimerAIS.Stop();

      m_pdata_source_string = new wxString(AISDataSource);


//      Create and manage AIS data stream source

//    Decide upon source
      wxLogMessage("AIS Data Source is....%s",m_pdata_source_string->c_str());

//      Data Source is private TCP/IP Server
      if(m_pdata_source_string->Contains("GPSD"))
      {
            wxString AIS_data_ip;
            AIS_data_ip = m_pdata_source_string->Mid(5);         // extract the IP

// Create the socket
            m_sock = new wxSocketClient();

// Setup the event handler and subscribe to most events
            m_sock->SetEventHandler(*this, AIS_SOCKET_ID);

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
            ptest_thread = new DNSTestThread(AIS_data_ip);

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

                  wxString msg(AIS_data_ip);
                  msg.Prepend("Could not resolve TCP/IP host '");
                  msg.Append("'\n Suggestion: Try 'xxx.xxx.xxx.xxx' notation");
                  wxMessageDialog md(this, msg, "OpenCPN Message", wxICON_ERROR );
                  md.ShowModal();

                  m_sock->Notify(FALSE);
                  m_sock->Destroy();
                  m_sock = NULL;

                  return AIS_NO_TCP;
            }


            //      Resolved the name, somehow, so Connect() the socket
            addr.Hostname(AIS_data_ip);
            addr.Service(20175/*GPSD_PORT_NUMBER*/);
            m_sock->Connect(addr, FALSE);       // Non-blocking connect
      }


//    AIS Data Source is specified serial port

      else if(m_pdata_source_string->Contains("Serial"))
      {
          wxString comx;
          comx =  m_pdata_source_string->Mid(7);        // either "COM1" style or "/dev/ttyS0" style

#ifdef __WXMSW__

//  As a quick check, verify that the specified port is available
            HANDLE m_hSerialComm = CreateFile(comx.c_str(),       // Port Name
                                             GENERIC_READ,
                                             0,
                                             NULL,
                                             OPEN_EXISTING,
                                             0,
                                             NULL);

            if(m_hSerialComm == INVALID_HANDLE_VALUE)
            {
                  wxString msg(comx);
                  msg.Prepend("  Could not open AIS serial port '");
                  msg.Append("'\nSuggestion: Try closing other applications.");
                  wxMessageDialog md(this, msg, "OpenCPN Message", wxICON_ERROR );
                  md.ShowModal();

                  return AIS_NO_SERIAL;
            }

            else
                  CloseHandle(m_hSerialComm);

//    Kick off the AIS RX thread
            pAIS_Thread = new OCP_AIS_Thread(this, comx);
            pAIS_Thread->Run();
#endif


#ifdef __LINUX__
//    Kick off the NMEA RX thread
            pAIS_Thread = new OCP_AIS_Thread(this, comx);
            pAIS_Thread->Run();
#endif

      }

      TimerAIS.Start(TIMER_AIS_MSEC,wxTIMER_CONTINUOUS);

      return AIS_NoError;

}



void AIS_Decoder::OnCloseWindow(wxCloseEvent& event)
{

//    Kill off the TCP/IP Socket if alive
      if(m_sock)
      {
            m_sock->Notify(FALSE);
            m_sock->Destroy();
            TimerAIS.Stop();
      }


//    Kill off the  RX Thread if alive
//      Todo Need to fix this by re-building the comm thread to not use blocking event structure
//      Also affects the NMEA thread in nmea.cpp

      if(pAIS_Thread)
      {
          pAIS_Thread->Delete();         //was kill();
#ifdef __WXMSW__
//          wxSleep(1);
#else
          sleep(2);
#endif
      }

}


void AIS_Decoder::GetSource(wxString& source)
{
      source = *m_pdata_source_string;
}




void AIS_Decoder::Pause(void)
{
      TimerAIS.Stop();

      if(m_sock)
            m_sock->Notify(FALSE);
}

void AIS_Decoder::UnPause(void)
{
    TimerAIS.Start(TIMER_AIS_MSEC,wxTIMER_CONTINUOUS);

      if(m_sock)
            m_sock->Notify(TRUE);
}



void AIS_Decoder::OnSocketEvent(wxSocketEvent& event)
{

#define RD_BUF_SIZE    200

    int nBytes;
    char *bp;
    char buf[RD_BUF_SIZE + 1];
    int char_count;


  switch(event.GetSocketEvent())
  {
      case wxSOCKET_INPUT :                     // from  Daemon
            m_sock->SetFlags(wxSOCKET_NOWAIT);


//          Read the reply, one character at a time, looking for 0x0a (lf)
            bp = buf;
            char_count = 0;

            while (char_count < RD_BUF_SIZE)
            {
                m_sock->Read(bp, 1);
                nBytes = m_sock->LastCount();
                if(*bp == 0x0a)
                {
                    bp++;
                    break;
                }

                bp++;
                char_count++;
            }

            *bp = 0;                        // end string

//          Validate the string

            if(!strncmp((const char *)buf, "!AIVDM", 6))
            {

                if(1)           // valid data?
                {
                  Decode(buf);

//    Signal the main program thread

//                    wxCommandEvent event( EVT_AIS, ID_AIS_WINDOW );
//                    event.SetEventObject( (wxObject *)this );
//                    event.SetExtraLong(EVT_AIS_DIRECT);
//                    m_pParentEventHandler->AddPendingEvent(event);
                }
            }



    case wxSOCKET_LOST       :
    case wxSOCKET_CONNECTION :
    default                  :
          break;
  }

}



void AIS_Decoder::OnTimerAIS(wxTimerEvent& event)
{
      TimerAIS.Stop();

      //    Scrub the target hash list
      //    removing any targets older than stipulated age

      //    Todo Add a method to set this parameter
      int death_age_seconds = 300;

      wxDateTime now = wxDateTime::Now();
      now.MakeGMT();

      AIS_Target_Hash::iterator it;
      AIS_Target_Hash *current_targets = GetTargetList();

      for( it = (*current_targets).begin(); it != (*current_targets).end(); ++it )
      {
          AIS_Target_Data *td = it->second;

          int target_age = now.GetTicks() - td->ReportTicks;
          if(target_age > death_age_seconds)
          {
              current_targets->erase(it);
              delete td;
              break;        // kill only one per tick, since iterator becomes invalid...
          }
      }


//--------------TEST DATA strings
#if(0)
      char str[82];
//      if(1)
      {
          if(itime++ > 2)
          {
              itime = 0;
              strcpy(str, test_str[istr]);
              istr++;
              if(istr > 23)
                  istr = 0;
              Decode(str);
          }
      }


#endif


      TimerAIS.Start(TIMER_AIS_MSEC,wxTIMER_CONTINUOUS);
}


//-------------------------------------------------------------------------------------------------------------
//
//    AIS Serial Input Thread
//
//    This thread manages reading the AIS data stream from the declared serial port
//
//-------------------------------------------------------------------------------------------------------------

//          Inter-thread communication event implementation
DEFINE_EVENT_TYPE(EVT_AIS)



//-------------------------------------------------------------------------------------------------------------
//    OCP_AIS_Thread Implementation
//-------------------------------------------------------------------------------------------------------------

//    ctor

OCP_AIS_Thread::OCP_AIS_Thread(wxWindow *MainWindow, const char *pszPortName)
{

      m_pMainEventHandler = MainWindow->GetEventHandler();

      ais_rx_share_buffer_state = RX_BUFFER_EMPTY;

      m_pPortName = new wxString(pszPortName);

      rx_buffer = new char[RX_BUFFER_SIZE + 1];
      put_ptr = rx_buffer;
      tak_ptr = rx_buffer;

      ais_ps_mutexProtectingTheRXBuffer = new wxMutex;

      Create();
}

OCP_AIS_Thread::~OCP_AIS_Thread(void)
{
      delete m_pPortName;
      delete rx_buffer;
      delete ais_ps_mutexProtectingTheRXBuffer;
}

void OCP_AIS_Thread::OnExit(void)
{
    //  Mark the global status as dead, gone
    pAIS_Thread = NULL;
}

#ifdef __LINUX__

#if defined (HAVE_SYS_TERMIOS_H)
#include <sys/termios.h>
#else
#if defined (HAVE_TERMIOS_H)
#include <termios.h>
#endif
#endif

#include <sys/termios.h>
#endif


//      Sadly, the thread itself must implement the underlying OS serial port
//      in a very machine specific way....

#ifdef __LINUX__
//    Entry Point
void *OCP_AIS_Thread::Entry()
{


    // Allocate the termios data structures

    pttyset = (termios *)malloc(sizeof (termios));
    pttyset_old = (termios *)malloc(sizeof (termios));

    // Open the serial port.
    if ((m_ais_fd = open(m_pPortName->c_str(), O_RDWR|O_NONBLOCK|O_NOCTTY)) < 0)
//    if ((m_ais_fd = open(m_pPortName->c_str(), O_RDWR|O_NOCTTY)) < 0)
    {
        wxLogMessage("AIS NMEA input device open failed: %s\n", m_pPortName->c_str());
        return 0;
    }


    {
        (void)cfsetispeed(pttyset, B38400);
        (void)cfsetospeed(pttyset, (speed_t)B38400);
        (void)tcsetattr(m_ais_fd, TCSANOW, pttyset);
        (void)tcflush(m_ais_fd, TCIOFLUSH);
    }

    if (isatty(m_ais_fd)!=0)
    {

      /* Save original terminal parameters */
      if (tcgetattr(m_ais_fd,pttyset_old) != 0)
      {
          wxLogMessage("AIS NMEA input device getattr failed: %s\n", m_pPortName->c_str());
          return 0;
      }
      (void)memcpy(pttyset, pttyset_old, sizeof(termios));

      //  Build the new parms off the old

      // Set blocking/timeout behaviour
      memset(pttyset->c_cc,0,sizeof(pttyset->c_cc));
//      pttyset->c_cc[VMIN] = 1;
      pttyset->c_cc[VTIME] = 11;                        // 1.1 sec timeout

      /*
      * No Flow Control
      */
      pttyset->c_cflag &= ~(PARENB | PARODD | CRTSCTS);
      pttyset->c_cflag |= CREAD | CLOCAL;
      pttyset->c_iflag = pttyset->c_oflag = pttyset->c_lflag = (tcflag_t) 0;

      int stopbits = 1;
      char parity = 'N';
      pttyset->c_iflag &=~ (PARMRK | INPCK);
      pttyset->c_cflag &=~ (CSIZE | CSTOPB | PARENB | PARODD);
      pttyset->c_cflag |= (stopbits==2 ? CS7|CSTOPB : CS8);
      switch (parity)
      {
          case 'E':
              pttyset->c_iflag |= INPCK;
              pttyset->c_cflag |= PARENB;
              break;
          case 'O':
              pttyset->c_iflag |= INPCK;
              pttyset->c_cflag |= PARENB | PARODD;
              break;
      }
      pttyset->c_cflag &=~ CSIZE;
      pttyset->c_cflag |= (CSIZE & (stopbits==2 ? CS7 : CS8));
      if (tcsetattr(m_ais_fd, TCSANOW, pttyset) != 0)
      {
          wxLogMessage("NMEA input device setattr failed: %s\n", m_pPortName->c_str());
          return 0;
      }


      (void)tcflush(m_ais_fd, TCIOFLUSH);
    }



    bool not_done = true;
    bool nl_found;
    char next_byte = 0;
    ssize_t newdata = 0;

//    The main loop
//    printf("starting\n");

    while(not_done)
    {
        if(TestDestroy())
        {
            not_done = false;                               // smooth exit
//            printf("smooth exit\n");
        }

//#define oldway 1
#ifdef oldway
//    Blocking, timeout protected read of one character at a time
//    Timeout value is set by c_cc[VTIME]
//    Storing incoming characters in circular buffer
//    And watching for new line character
//     On new line character, send notification to parent


        newdata = read(m_ais_fd, &next_byte, 1);            // blocking read of one char
                                                            // return (-1) if no data available, timeout
#else
//      Kernel I/O multiplexing provides a cheap way to wait for chars

        fd_set rfds;
        struct timeval tv;
        int retval;

        //      m_ais_fd to see when it has input.
        FD_ZERO(&rfds);
        FD_SET(m_ais_fd, &rfds);
        // Wait up to 1 second
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        newdata = 0;

//      wait for a read available on m_ais_fd, we don't care about write or exceptions
        retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);

//        if (retval == -1)
//            perror("select()");
//        else if (retval)
//            printf("Data is available now.\n");
        // FD_ISSET(0, &rfds) will be true.
//        else
//            printf("No data within one seconds.\n");

        if(FD_ISSET(m_ais_fd, &rfds) && (retval != -1) && retval)
            newdata = read(m_ais_fd, &next_byte, 1);            // blocking read of one char
                                                                // bound to succeed
#endif


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


//    If the shared buffer is available....
                if(ais_ps_mutexProtectingTheRXBuffer->Lock() == wxMUTEX_NO_ERROR )
                {
                    if(RX_BUFFER_EMPTY == ais_rx_share_buffer_state)
                    {

//    Copy the message into the rx_shared_buffer

                        tptr = tak_ptr;
                        ptmpbuf = temp_buf;

                        while((*tptr != 0x0a) && (tptr != put_ptr))
                        {
                            *ptmpbuf++ = *tptr++;

                            if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                tptr = rx_buffer;
                        }

                        if(*tptr == 0x0a)                                     // well formed sentence
                        {
                            *ptmpbuf++ = *tptr++;
                            if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                tptr = rx_buffer;

                            *ptmpbuf = 0;

                            tak_ptr = tptr;
                            strcpy(ais_rx_share_buffer, temp_buf);

                            ais_rx_share_buffer_state = RX_BUFFER_FULL;
                            ais_rx_share_buffer_length = strlen(ais_rx_share_buffer);

//    Signal the main program thread

                            wxCommandEvent event( EVT_AIS, ID_AIS_WINDOW );
                            event.SetEventObject( (wxObject *)this );
                            event.SetExtraLong(EVT_AIS_PARSE_RX);
                            m_pMainEventHandler->AddPendingEvent(event);
                        }
                    }
                }

//    Release the MUTEX
                ais_ps_mutexProtectingTheRXBuffer->Unlock();

            }                   //if nl
        }                       // if newdata > 0
    }                          // the big while...


    //          Close the port cleanly


        /* this is the clean way to do it */
//    pttyset_old->c_cflag |= HUPCL;
//    (void)tcsetattr(m_ais_fd,TCSANOW,pttyset_old);
    (void)close(m_ais_fd);

    free (pttyset);
    free (pttyset_old);


    return 0;

}


#endif          //__LINUX__


#ifdef __WXMSW__
//    Entry Point
void *OCP_AIS_Thread::Entry()
{

      bool not_done;

      DWORD dwRead;
      BOOL fWaitingOnRead = FALSE;
      OVERLAPPED osReader = {0};
#define READ_BUF_SIZE 100
      char buf[READ_BUF_SIZE];

#define READ_TIMEOUT      500      // milliseconds

      DWORD dwRes;

//    Set up the serial port

      m_hSerialComm = CreateFile(m_pPortName->c_str(),      // Port Name
                                             GENERIC_READ,              // Desired Access
                                             0,                         // Shared Mode
                                             NULL,                      // Security
                                             OPEN_EXISTING,             // Creation Disposition
                                             FILE_FLAG_OVERLAPPED,
                                             NULL);                     //  Overlapped

      if(m_hSerialComm == INVALID_HANDLE_VALUE)
      {
            error = ::GetLastError();
            goto fail_point;
      }


      if(!SetupComm(m_hSerialComm, 1024, 1024))
            goto fail_point;

      DCB dcbConfig;

      if(GetCommState(m_hSerialComm, &dcbConfig))           // Configuring Serial Port Settings
      {
            dcbConfig.BaudRate = 38400;
            dcbConfig.ByteSize = 8;
            dcbConfig.Parity = NOPARITY;
            dcbConfig.StopBits = ONESTOPBIT;
            dcbConfig.fBinary = TRUE;
            dcbConfig.fParity = TRUE;
      }

      else
            goto fail_point;

      if(!SetCommState(m_hSerialComm, &dcbConfig))
            goto fail_point;

      COMMTIMEOUTS commTimeout;

      TimeOutInSec = 2;

      if(GetCommTimeouts(m_hSerialComm, &commTimeout)) // Configuring Read & Write Time Outs
      {
            commTimeout.ReadIntervalTimeout = 1000*TimeOutInSec;
            commTimeout.ReadTotalTimeoutConstant = 1000*TimeOutInSec;
            commTimeout.ReadTotalTimeoutMultiplier = 0;
            commTimeout.WriteTotalTimeoutConstant = 1000*TimeOutInSec;
            commTimeout.WriteTotalTimeoutMultiplier = 0;
      }

      else
            goto fail_point;

      if(!SetCommTimeouts(m_hSerialComm, &commTimeout))
            goto fail_point;


//    Set up event specification
      DWORD dwEventMask;

      if(!SetCommMask(m_hSerialComm, EV_RXCHAR)) // Setting Event Type
            goto fail_point;


// Create the overlapped event. Must be closed before exiting
// to avoid a handle leak.
      osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

      not_done = true;
      bool nl_found;

//    The main loop


      while(not_done)
      {
            if(TestDestroy())
                  not_done = false;                               // smooth exit


            if (osReader.hEvent == NULL)
   // Error creating overlapped event; abort.
                goto fail_point;

            if (!fWaitingOnRead)
            {
   // Issue read operation.
                if (!ReadFile(m_hSerialComm, buf, 10, &dwRead, &osReader))
                {
                    if (GetLastError() != ERROR_IO_PENDING)     // read not delayed?
   // Error in communications; report it.
                        goto fail_point;
                    else
                        fWaitingOnRead = TRUE;
                }
                else
                {
   // read completed immediately
                    HandleASuccessfulRead(buf, dwRead);
                }
            }



            if (fWaitingOnRead)
            {
                dwRes = WaitForSingleObject(osReader.hEvent, READ_TIMEOUT);
                switch(dwRes)
                {
      // Read completed.
                    case WAIT_OBJECT_0:
                        if (!GetOverlappedResult(m_hSerialComm, &osReader, &dwRead, FALSE))
          // Error in communications; report it.
                            goto fail_point;
                        else
          // Read completed successfully.
                            HandleASuccessfulRead(buf, dwRead);

          //  Reset flag so that another opertion can be issued.
                        fWaitingOnRead = FALSE;
                        break;

                    case WAIT_TIMEOUT:
          // Operation isn't complete yet. fWaitingOnRead flag isn't
          // changed since I'll loop back around, and I don't want
          // to issue another read until the first one finishes.
          //
          // This is a good time to do some background work.
                    break;

                    default:
          // Error in the WaitForSingleObject; abort.
          // This indicates a problem with the OVERLAPPED structure's
          // event handle.
                    break;
                }                   // switch
            }                       // if



      }                 // big while






/*
      while(not_done)
      {
            if(TestDestroy())
                  not_done = false;                               // smooth exit

//    Blocking read of one character at a time
//    Storing incoming characters in circular buffer
//    And watching for new line character
            if(WaitCommEvent(m_hSerialComm, &dwEventMask, NULL)) // Waiting For Event to Occur
            {
                  char szBuf;
                  DWORD dwIncommingReadSize;

                  do
                  {
                        nl_found = false;
                        dwIncommingReadSize = 0;


                        COMSTAT    ComStat ;
                        DWORD      dwErrorFlags;


                        ClearCommError( m_hSerialComm, &dwErrorFlags, &ComStat ) ;

                        if(ComStat.cbInQue )
                        {

                              if(ReadFile(m_hSerialComm, &szBuf, 1, &dwIncommingReadSize, NULL) != 0)
                              {
                                    if(dwIncommingReadSize > 0)
                                    {
                                          int nchar = dwIncommingReadSize;
                                          while(nchar)
                                          {
                                                *put_ptr++ = szBuf;
                                                if((put_ptr - rx_buffer) > RX_BUFFER_SIZE)
                                                      put_ptr = rx_buffer;

                                                if(0x0a == szBuf)
                                                      nl_found = true;

                                                nchar--;
                                          }
                                    }
                              }

                              else
                              {
                                    error = ::GetLastError();
                                    break;
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

//    If the shared buffer is available....
                                    if(ais_ps_mutexProtectingTheRXBuffer->Lock() == wxMUTEX_NO_ERROR )
                                    {
                                          if(RX_BUFFER_EMPTY == ais_rx_share_buffer_state)
                                          {

//    Copy the message into the rx_shared_buffer

                                                tptr = tak_ptr;
                                                ptmpbuf = temp_buf;

                                                while((*tptr != 0x0a) && (tptr != put_ptr))
                                                {
                                                      *ptmpbuf++ = *tptr++;

                                                      if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                                            tptr = rx_buffer;
                                                }

                                                if(*tptr == 0x0a)                                     // well formed sentence
                                                {
                                                      *ptmpbuf++ = *tptr++;
                                                      if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                                            tptr = rx_buffer;

                                                      *ptmpbuf = 0;

                                                      tak_ptr = tptr;

                                                      strcpy(ais_rx_share_buffer, temp_buf);

                                                      ais_rx_share_buffer_state = RX_BUFFER_FULL;
                                                      ais_rx_share_buffer_length = strlen(ais_rx_share_buffer);

//    Signal the main program thread

                                                      wxCommandEvent event( EVT_AIS, ID_AIS_WINDOW );
                                                      event.SetEventObject( (wxObject *)this );
                                                      event.SetExtraLong(EVT_AIS_PARSE_RX);
                                                      m_pMainEventHandler->AddPendingEvent(event);
                                                }
                                                else
                                                {
                                                      partial = true;
//                                                    wxLogMessage("partial");
                                                }
                                          }
                                    }

//    Release the MUTEX
                                    ais_ps_mutexProtectingTheRXBuffer->Unlock();

                              }                 // while

                        }

                  } while(dwIncommingReadSize > 0);

//
            }


      }           // the big while...

*/
fail_point:

      return 0;

}



bool OCP_AIS_Thread::HandleASuccessfulRead(char *buf, DWORD dwIncommingReadSize)
{
    bool nl_found;
    char *bp = buf;
    if(dwIncommingReadSize > 0)
    {
        int nchar = dwIncommingReadSize;
        while(nchar)
        {
              char c = *bp;
              *put_ptr++ = *bp++;
              if((put_ptr - rx_buffer) > RX_BUFFER_SIZE)
                  put_ptr = rx_buffer;

              if(0x0a == c)
                  nl_found = true;

              nchar--;
        }
    }
    else
    {
         error = ::GetLastError();
         return false;
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

//    If the shared buffer is available....
                if(ais_ps_mutexProtectingTheRXBuffer->Lock() == wxMUTEX_NO_ERROR )
                {
                      if(RX_BUFFER_EMPTY == ais_rx_share_buffer_state)
                      {

//    Copy the message into the rx_shared_buffer

                            tptr = tak_ptr;
                            ptmpbuf = temp_buf;

                            while((*tptr != 0x0a) && (tptr != put_ptr))
                            {
                                  *ptmpbuf++ = *tptr++;

                                  if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                        tptr = rx_buffer;
                            }

                            if(*tptr == 0x0a)                                     // well formed sentence
                            {
                                  *ptmpbuf++ = *tptr++;
                                  if((tptr - rx_buffer) > RX_BUFFER_SIZE)
                                        tptr = rx_buffer;

                                  *ptmpbuf = 0;

                                  tak_ptr = tptr;

                                  strcpy(ais_rx_share_buffer, temp_buf);

                                  ais_rx_share_buffer_state = RX_BUFFER_FULL;
                                  ais_rx_share_buffer_length = strlen(ais_rx_share_buffer);

//    Signal the main program thread

                                  wxCommandEvent event( EVT_AIS, ID_AIS_WINDOW );
                                  event.SetEventObject( (wxObject *)this );
                                  event.SetExtraLong(EVT_AIS_PARSE_RX);
                                  m_pMainEventHandler->AddPendingEvent(event);
                            }
                            else
                            {
                                  partial = true;
//                                                    wxLogMessage("partial");
                            }
                      }
                }

//    Release the MUTEX
                ais_ps_mutexProtectingTheRXBuffer->Unlock();

          }                 // while
    }                       // if nl

    return true;
}


#endif

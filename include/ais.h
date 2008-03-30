/******************************************************************************
 * $Id: ais.h,v 1.8 2008/03/30 23:13:42 bdbcat Exp $
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
<<<<<<< ais.h
 * $Log: ais.h,v $
 * Revision 1.8  2008/03/30 23:13:42  bdbcat
 * *** empty log message ***
 *
=======
 * $Log: ais.h,v $
 * Revision 1.8  2008/03/30 23:13:42  bdbcat
 * *** empty log message ***
 *
 * Revision 1.7  2008/01/12 06:17:45  bdbcat
 * Update for Mac OSX/Unicode
 *
>>>>>>> 1.7
 * Revision 1.6  2008/01/02 21:04:07  bdbcat
 * Update for Version 1.2.2
 *
 * Revision 1.5  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.4  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.3  2007/02/06 02:11:22  dsr
 * Cleanup
 *
 * Revision 1.2  2006/12/03 21:23:15  dsr
 * Redefine AIS window ctor to include explicit window ID specification.
 * Change AIS timer tick rate away from exactly 1000 msec to avoid syncronization problems.
 *
 * Revision 1.1  2006/11/01 02:18:45  dsr
 * AIS Support
 *
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

//#include "wx/tokenzr.h"

//#include <stdlib.h>
//#include <math.h>
//#include <time.h>

#include "dychart.h"


#ifdef __LINUX__
#include <sys/termios.h>
#endif

#include "wx/socket.h"

#ifdef __WXMSW__
#include <wx/datetime.h>
#endif

#include "chart1.h"

#define TIMER_AIS_MSEC      998

typedef enum AIS_Error
{
    AIS_NoError = 0,
    AIS_Partial,
    AIS_NMEAVDM_TOO_LONG,
    AIS_NMEAVDM_CHECKSUM_BAD,
    AIS_NMEAVDM_BAD,
    AIS_NO_SERIAL,
    AIS_NO_TCP
}_AIS_Error;


//      Describe NavStatus variable
typedef enum ais_nav_status
{
    UNDERWAY_USING_ENGINE = 0,
    A1,
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    UNDERWAY_SAILING

}_ais_nav_status;

//---------------------------------------------------------------------------------
//
//  AIS_Decoder Helpers
//
//---------------------------------------------------------------------------------

class AIS_Target_Data
{
public:

    AIS_Target_Data();

    int         MID;
    int         MMSI;
    int         NavStatus;
    int         SyncState;
    int         SlotTO;
    double      SOG;
    double      COG;
    double      HDG;
    double      Lon;
    double      Lat;
    int         ROTAIS;
    char        CallSign[8];                // includes terminator
    char        ShipName[21];
    unsigned char ShipType;
    time_t      ReportTicks;


};




class AIS_Bitstring
{
public:

    AIS_Bitstring(const char *str);
    unsigned char to_6bit(const char c);
    int GetInt(int sp, int len);
    bool GetStr(int sp, int len, char *dest, int max_len);


private:

    unsigned char bitbytes[82];
    int byte_length;
};




//      Implement the AISTargetList as a wxHashMap

WX_DECLARE_HASH_MAP( int, AIS_Target_Data*, wxIntegerHash, wxIntegerEqual, AIS_Target_Hash );



#define AIS_SOCKET_ID             7

enum
{
    EVT_AIS_DIRECT,
    EVT_AIS_PARSE_RX
};



//---------------------------------------------------------------------------------
//
//  AIS_Decoder Definition
//
//---------------------------------------------------------------------------------

class AIS_Decoder : public wxWindow
{

public:
    AIS_Decoder(void);
    AIS_Decoder(int window_id, wxFrame *pParent, const wxString& AISDataSource);

    ~AIS_Decoder(void);


    void OnEvtAIS(wxCommandEvent& event);
    AIS_Error Decode(const wxString& str);
    void Pause(void);
    void UnPause(void);
    void GetSource(wxString& source);
    AIS_Target_Hash *GetTargetList(void) {return AISTargetList;}
    wxString *BuildQueryResult(AIS_Target_Data *td);

private:
    AIS_Error OpenDataSource(wxFrame *pParent, const wxString& AISDataSource);
    void OnActivate(wxActivateEvent& event);
    void OnSocketEvent(wxSocketEvent& event);
    void OnTimerAIS(wxTimerEvent& event);
    void OnCloseWindow(wxCloseEvent& event);

    bool NMEACheckSumOK(const wxString& str);
    AIS_Target_Data *Parse_VDMBitstring(AIS_Bitstring *bstr);
    AIS_Target_Data *Merge(AIS_Target_Data *tlast, AIS_Target_Data *tthis);

    AIS_Target_Hash *AISTargetList;


    wxIPV4address     addr;
    wxSocketClient    *m_sock;
    bool              m_busy;
    wxTimer           TimerAIS;
    MyFrame           *parent_frame;

    wxString          *m_pdata_source_string;
    wxString          *m_pdata_ap_port_string;
    wxEvtHandler      *m_pParentEventHandler;

    int               nsentences;
    int               isentence;
    wxString          sentence_accumulator;
    bool              m_OK;
    int               m_death_age_seconds;

DECLARE_EVENT_TABLE()


};

//-------------------------------------------------------------------------------------------------------------
//
//    AIS Input Thread
//
//    This thread manages reading the AIS data stream from the declared serial port
//
//-------------------------------------------------------------------------------------------------------------

#ifdef __WXMSW__
#include <windows.h>
#endif

//    Constants


//          Inter-thread communication event declaration
DECLARE_EVENT_TYPE(EVT_AIS, -1)


class OCP_AIS_Thread: public wxThread
{

public:

      OCP_AIS_Thread(wxWindow *MainWindow, const wxString& PortName);
      ~OCP_AIS_Thread(void);
      void *Entry();

      void OnExit(void);

private:
      bool HandleRead(char *buf, int character_count);

      wxEvtHandler            *m_pMainEventHandler;
      wxString                *m_pPortName;
      int                     TimeOutInSec;
      char                    *put_ptr;
      char                    *tak_ptr;

      char                    *rx_buffer;

      unsigned long           error;
      int                     nl_count;

#ifdef __LINUX__
      termios                 *pttyset;
      termios                 *pttyset_old;

      int                     m_ais_fd;
#endif

#ifdef __WXMSW__
      HANDLE                  m_hSerialComm;
#endif

};



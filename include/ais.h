/******************************************************************************
 * $Id: ais.h,v 1.24 2009/09/11 19:50:06 bdbcat Exp $
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
 * $Log: ais.h,v $
 * Revision 1.24  2009/09/11 19:50:06  bdbcat
 * Improve message handling, format dialogs
 *
 * Revision 1.23  2009/09/04 02:22:21  bdbcat
 * New Methods
 *
 * Revision 1.22  2009/08/29 23:24:44  bdbcat
 * Various, including alert suppression logic
 *
 * Revision 1.21  2009/08/22 01:16:35  bdbcat
 * Expand Query
 *
 * Revision 1.20  2009/07/29 00:48:47  bdbcat
 * Add Debug messages
 *
 * Revision 1.19  2009/07/11 01:00:07  bdbcat
 * Correct buffer overrun on multi-part messages
 *
 * Revision 1.18  2009/07/08 03:39:42  bdbcat
 * Improve Alert dialog.
 *
 * Revision 1.17  2009/07/08 01:52:53  bdbcat
 * Convert AISDecoder to wxEvtHandler.
 *
 * Revision 1.16  2009/07/03 03:00:32  bdbcat
 * Improve AIS Dialogs.
 *
 * Revision 1.15  2009/06/17 02:48:32  bdbcat
 * Add AIS Alerts
 *
 * Revision 1.14  2009/06/14 01:51:58  bdbcat
 * AIS Alert Dialog
 *
 * Revision 1.13  2009/06/03 03:20:50  bdbcat
 * Implement AIS/GPS Port sharing
 *
 * Revision 1.12  2009/04/07 16:54:54  bdbcat
 * Support AIS Class B
 *
 * Revision 1.11  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.10  2008/04/10 00:57:08  bdbcat
 * Cleanup
 *
 * Revision 1.9  2008/03/30 23:20:36  bdbcat
 * *** empty log message ***
 *
 * Revision 1.8  2008/03/30 23:13:42  bdbcat
 * *** empty log message ***
 *
 * Revision 1.7  2008/01/12 06:17:45  bdbcat
 * Update for Mac OSX/Unicode
 *
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

#include <wx/datetime.h>
#include "wx/socket.h"
#include "wx/sound.h"

#include "dychart.h"
#include "chart1.h"

#ifdef __POSIX__
#include <sys/termios.h>
#endif


//    Constants
#ifndef PI
#define PI        3.1415926535897931160E0      /* pi */
#endif



#define TIMER_AIS_MSEC      998
#define TIMER_AIS_AUDIO_MSEC 2000

#define ID_ACKNOWLEDGE        10001
#define ID_SILENCE            10002

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
    AT_ANCHOR,
    NOT_UNDER_COMMAND,
    RESTRICTED_MANOEUVRABILITY,
    CONSTRAINED_BY_DRAFT,
    MOORED,
    AGROUND,
    FISHING,
    UNDERWAY_SAILING

}_ais_nav_status;


//      Describe Transponder Class
typedef enum ais_transponder_class
{
      AIS_CLASS_A = 0,
      AIS_CLASS_B

}_ais_transponder_class;

//    Describe AIS Alarm state
typedef enum ais_alarm_type
{
      AIS_NO_ALARM = 0,
      AIS_ALARM_SET,
      AIS_ALARM_ACKNOWLEDGED

}_ais_alarm_type;

//---------------------------------------------------------------------------------
//
//  AIS_Decoder Helpers
//
//---------------------------------------------------------------------------------

class AIS_Target_Data
{
public:

    AIS_Target_Data();
    wxString BuildQueryResult(int *pn_nl = NULL);
    char *Get_vessel_type_string(bool b_short = false);


    int                       MID;
    int                       MMSI;
    ais_transponder_class     Class;
    int                       NavStatus;
    int                       SyncState;
    int                       SlotTO;
    double                    SOG;
    double                    COG;
    double                    HDG;
    double                    Lon;
    double                    Lat;
    int                       ROTAIS;
    char                      CallSign[8];                // includes terminator
    char                      ShipName[21];
    unsigned char             ShipType;
    int                       IMO;

    int                       DimA;
    int                       DimB;
    int                       DimC;
    int                       DimD;

    int                       ETA_Mo;
    int                       ETA_Day;
    int                       ETA_Hr;
    int                       ETA_Min;

    double                    Draft;

    char                      Destination[21];

    time_t                    ReportTicks;
    int                       RecentPeriod;
    bool                      b_active;
    ais_alarm_type            n_alarm_state;
    bool                      b_suppress_audio;
    bool                      b_positionValid;
    bool                      b_nameValid;

    int                       m_utc_hour;
    int                       m_utc_min;
    int                       m_utc_sec;

    double                    Range_NM;
    double                    Brg;

    //      Per target collision parameters
    bool                      bCPA_Valid;
    double      TCPA;                     // Minutes
    double      CPA;                      // Nautical Miles


};



#define AIS_MAX_MESSAGE_LEN (10 * 82)           // AIS Spec allows up to 9 sentences per message, 82 bytes each
class AIS_Bitstring
{
public:

    AIS_Bitstring(const char *str);
    unsigned char to_6bit(const char c);
    int GetInt(int sp, int len);
    bool GetStr(int sp, int len, char *dest, int max_len);


private:

    unsigned char bitbytes[AIS_MAX_MESSAGE_LEN];
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

class AIS_Decoder : public wxEvtHandler
{

public:
    AIS_Decoder(void);
    AIS_Decoder(int window_id, wxFrame *pParent, const wxString& AISDataSource,  wxMutex *pGPSMutex = 0);

    ~AIS_Decoder(void);


    void OnEvtAIS(wxCommandEvent& event);
    AIS_Error Decode(const wxString& str);
    void Pause(void);
    void UnPause(void);
    void GetSource(wxString& source);
    AIS_Target_Hash *GetTargetList(void) {return AISTargetList;}
    AIS_Target_Data *Get_Target_Data_From_MMSI(int mmsi);
    int GetNumTargets(void){ return m_n_targets;}

private:
    AIS_Error OpenDataSource(wxFrame *pParent, const wxString& AISDataSource);
    void OnActivate(wxActivateEvent& event);
    void OnSocketEvent(wxSocketEvent& event);
    void OnTimerAIS(wxTimerEvent& event);
    void OnTimerAISAudio(wxTimerEvent& event);

    bool NMEACheckSumOK(const wxString& str);
    bool Parse_VDMBitstring(AIS_Bitstring *bstr, AIS_Target_Data *ptd);
    void UpdateAllCPA(void);
    void UpdateOneCPA(AIS_Target_Data *ptarget);
    void UpdateAllAlarms(void);
    void Parse_And_Send_Posn(wxString &str_temp_buf);
    void ThreadMessage(const wxString &msg);


    AIS_Target_Hash *AISTargetList;


    wxIPV4address     addr;
    wxSocketClient    *m_sock;
    bool              m_busy;
    wxTimer           TimerAIS;
    wxFrame           *m_parent_frame;

    wxString          m_data_source_string;
    wxEvtHandler      *m_pParentEventHandler;

    int               nsentences;
    int               isentence;
    wxString          sentence_accumulator;
    bool              m_OK;


    NMEA0183         m_NMEA0183;
    wxMutex          *m_pShareGPSMutex;
    wxEvtHandler     *m_pMainEventHandler;

    bool             m_bAIS_Audio_Alert_On;
    wxTimer          m_AIS_Audio_Alert_Timer;
    wxSound          m_AIS_Sound;
    int              m_n_targets;

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

      OCP_AIS_Thread(wxEvtHandler *pParent, const wxString& PortName);
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

#ifdef __POSIX__
      termios                 *pttyset;
      termios                 *pttyset_old;

      int                     m_ais_fd;
#endif

#ifdef __WXMSW__
      HANDLE                  m_hSerialComm;
#endif
};


class AISInfoWin;
//----------------------------------------------------------------------------------------------------------//    AISTargetAlertDialog Specification
//----------------------------------------------------------------------------------------------------------
class AISTargetAlertDialog: public wxDialog
{
      DECLARE_CLASS( AISTargetAlertDialog )
                  DECLARE_EVENT_TABLE()
      public:

           AISTargetAlertDialog( );

            ~AISTargetAlertDialog( );
            void Init();

            bool Create( int target_mmsi,
                         wxWindow *parent,
                         AIS_Decoder *pdecoder,
                         wxWindowID id = wxID_ANY,
                         const wxString& caption = wxT("AIS Alert"),
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxDefaultSize,
                         long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU );

           void CreateControls();

           int Get_Dialog_MMSI(void){ return m_target_mmsi; }
           void UpdateText();

      private:
            bool GetAlertText(int mmsi, wxString &result, int *pn_nl);
            void OnClose(wxCloseEvent& event);
            void OnIdAckClick( wxCommandEvent& event );
            void OnMove( wxMoveEvent& event );
            void OnSize( wxSizeEvent& event );
            void OnIdSilenceClick( wxCommandEvent& event );


            AISInfoWin        *m_pAlertTextCtl;
            int               m_target_mmsi;
            AIS_Decoder       *m_pdecoder;
            wxWindow          *m_pparent;

};





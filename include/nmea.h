/******************************************************************************
 * $Id: nmea.h,v 1.16 2009/03/26 22:35:35 bdbcat Exp $
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
 * Revision 1.16  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.15  2008/12/19 04:18:36  bdbcat
 * Better diagnostics
 *
 * Revision 1.14  2008/12/09 03:44:33  bdbcat
 * Cleanup Comments
 *
 * Revision 1.13  2008/11/12 04:15:44  bdbcat
 * Support Garmin Devices / Cleanup
 *
 * Revision 1.12  2008/04/10 01:01:32  bdbcat
 * Cleanup
 *
 * Revision 1.11  2008/03/30 23:22:37  bdbcat
 * *** empty log message ***
 *
 * Revision 1.10  2008/01/12 06:18:40  bdbcat
 * Update for Mac OSX/Unicode
 *
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

// Include wxWindows' headers

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled header

#include "wx/socket.h"
#include <wx/datetime.h>


#include "nmea0183.h"

#ifdef __POSIX__
#include <sys/termios.h>
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

//    A generic Position Data structure
typedef struct {
      double kLat;
      double kLon;
      double kCog;
      double kSog;
      time_t FixTime;
} GenericPosDat;


// The MY_FILETIME structure is a 64-bit value
//    representing the number of 100-nanosecond
//    intervals since January 1, 1601 (UTC).
// This is the format used in the NMEA server data packet
//    sigh....

typedef struct  {
  unsigned int low;
  unsigned int high;
} MyFileTime;


//          Fwd Declarations
class     CSyncSerialComm;
class     MyFrame;
class     OCP_NMEA_Thread;
class     OCP_GARMIN_Thread;
class     ComPortManager;


//----------------------------------------------------------------------------
// NMEAWindow
//----------------------------------------------------------------------------

class NMEAWindow: public wxWindow
{
public:
      NMEAWindow(int window_id, wxFrame *frame, const wxString& NMEADataSource, wxMutex *pMutex = 0);
      ~NMEAWindow();

      void GetSource(wxString& source);

      //    Stop/Start the NMEA Socket Client
      //    Used to prevent async interrupts at critical times
      void Pause(void);
      void UnPause(void);

          //    Secondary thread life toggle
          //    Used to inform launching object (this) to determine if the thread can
          //    be safely called or polled, e.g. wxThread->Destroy();
      void SetSecThreadActive(void){m_bsec_thread_active = true;}
      void SetSecThreadInActive(void){m_bsec_thread_active = false;}

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
      wxFrame           *parent_frame;

      wxString          m_data_source_string;
      wxEvtHandler      *m_pParentEventHandler;
      wxMutex           *m_pShareMutex;
      wxThread          *m_pSecondary_Thread;

      bool              m_bsec_thread_active;

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
#include <winioctl.h>
#include <initguid.h>
#include "setupapi.h"                   // presently stored in opencpn/src
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
DECLARE_EVENT_TYPE(EVT_THREADMSG, -1)


class OCP_NMEA_Thread: public wxThread
{

public:

      OCP_NMEA_Thread(NMEAWindow *Launcher, wxWindow *MessageTarget, wxMutex *pMutex, const wxString& PortName, ComPortManager *pComMan);
      ~OCP_NMEA_Thread(void);
      void *Entry();

      void OnExit(void);

private:
      void Parse_And_Send_Posn(wxString &str_temp_buf);
      void ThreadMessage(const wxString &msg);          // Send a wxLogMessage to main program event loop
      wxEvtHandler            *m_pMainEventHandler;
      NMEAWindow              *m_launcher;
      wxString                *m_pPortName;
      wxMutex                 *m_pShareMutex;
      char                    *put_ptr;
      char                    *tak_ptr;

      char                    *rx_buffer;

      unsigned long           error;
      int                     m_total_error_messages;

      NMEA0183                m_NMEA0183;

      ComPortManager          *m_pCommMan;

      int                     m_gps_fd;

};



//-------------------------------------------------------------------------------------------------------------
//
//    Garmin Input Thread
//
//    This thread manages reading the positioning data stream from the declared Garmin USB device
//
//-------------------------------------------------------------------------------------------------------------

#ifdef __WXMSW__
#include <windows.h>
#endif


//      Local Endian conversions
void le_write16(void *addr, const unsigned value);
void le_write32(void *addr, const unsigned value);
signed int le_read16(const void *addr);
signed int le_read32(const void *addr);



//              Some Garmin Data Structures and Constants
#define GARMIN_USB_API_VERSION 1
#define GARMIN_USB_MAX_BUFFER_SIZE 4096
#define GARMIN_USB_INTERRUPT_DATA_SIZE 64

#define IOCTL_GARMIN_USB_API_VERSION CTL_CODE \
        (FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GARMIN_USB_INTERRUPT_IN CTL_CODE \
        (FILE_DEVICE_UNKNOWN, 0x850, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GARMIN_USB_BULK_OUT_PACKET_SIZE CTL_CODE \
        (FILE_DEVICE_UNKNOWN, 0x851, METHOD_BUFFERED, FILE_ANY_ACCESS)


/*
 * New packet types in USB.
 */
#define GUSB_SESSION_START 5    /* We request units attention */
#define GUSB_SESSION_ACK   6    /* Unit responds that we have its attention */
#define GUSB_REQUEST_BULK  2    /* Unit requests we read from bulk pipe */

#define GUSB_RESPONSE_PVT  51   /* PVT Data Packet */
#define GUSB_RESPONSE_SDR  114  /* Satellite Data Record Packet */




typedef
union {
        struct {
        unsigned char type;
        unsigned char reserved1;
        unsigned char reserved2;
        unsigned char reserved3;
        unsigned char pkt_id[2];
        unsigned char reserved6;
        unsigned char reserved7;
        unsigned char datasz[4];
        unsigned char databuf[1]; /* actually a variable length array... */
        } gusb_pkt;
        unsigned char dbuf[1024];
} garmin_usb_packet;


typedef struct garmin_unit_info {
        unsigned long serial_number;
        unsigned long unit_id;
        unsigned long unit_version;
        char *os_identifier; /* In case the OS has another name for it. */
        char *product_identifier; /* From the hardware itself. */
} unit_info_type;



/*              Packet structure for Pkt_ID = 51 (PVT Data Record)   */
#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

typedef struct {
        float   alt;
        float   epe;
        float   eph;
        float   epv;
        short   fix;
        double  tow;
        double  lat;
        double  lon;
        float   east;
        float   north;
        float   up;
        float   msl_hght;
        short   leap_scnds;
        long    wn_days;
} D800_Pvt_Data_Type;

#pragma pack(pop)   /* restore original alignment from stack */




/*              Packet structure for Pkt_ID = 114 (Satellite Data Record)   */
typedef    struct
           {
           unsigned char         svid;          //space vehicle identification (1-32 and 33-64 for WAAS)
           short                 snr;           //signal-to-noise ratio
           unsigned char         elev;          //satellite elevation in degrees
           short                 azmth;         //satellite azimuth in degrees
           unsigned char         status;        //status bit-field
           } cpo_sat_data;

/*
The status bit field represents a set of booleans described below:
       Bit      Meaning when bit is one (1)
        0       The unit has ephemeris data for the specified satellite.
        1       The unit has a differential correction for the specified satellite.
        2       The unit is using this satellite in the solution.
*/


enum {
        rs_fromintr,
        rs_frombulk
};



class OCP_GARMIN_Thread: public wxThread
{

public:

      OCP_GARMIN_Thread(NMEAWindow *Launcher, wxWindow *MessageTarget, wxMutex *pMutex, const wxString& PortName);
      ~OCP_GARMIN_Thread(void);
      void *Entry();

      void OnExit(void);

private:
#ifdef __WXMSW__
      HANDLE garmin_usb_start(HDEVINFO hdevinfo, SP_DEVICE_INTERFACE_DATA *infodata);
      bool gusb_syncup(void);

      int gusb_win_get(garmin_usb_packet *ibuf, size_t sz);
      int gusb_win_get_bulk(garmin_usb_packet *ibuf, size_t sz);
      int gusb_win_send(const garmin_usb_packet *opkt, size_t sz);

      int gusb_cmd_send(const garmin_usb_packet *opkt, size_t sz);
      int gusb_cmd_get(garmin_usb_packet *ibuf, size_t sz);
#endif

      void ThreadMsg(const wxString &msg);          // Send a wxLogMessage to main program event loop

      wxEvtHandler            *m_pMainEventHandler;
      NMEAWindow              *m_launcher;
      wxMutex                 *m_pShareMutex;
      wxString                m_PortName;

#ifdef __WXMSW__
      HANDLE                  m_usb_handle;
#endif

      int                     m_max_tx_size;
      int                     m_receive_state;
      cpo_sat_data            m_sat_data[12];
      unit_info_type          grmin_unit_info[2];
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
    int AutopilotOut(const wxString& Sentence);
    bool IsOK(){ return m_bOK;}


private:
    bool            OpenPort(wxString &port);

    wxString        *m_pdata_ap_port_string;
    wxString        m_port;
    int             m_ap_fd;
    bool            m_bOK;

DECLARE_EVENT_TABLE()
};

//-------------------------------------------------------------------------------------------------------------
//
//    Communications Port Manager
//
//-------------------------------------------------------------------------------------------------------------

class OpenCommPortElement
{
public:
      wxString    com_name;
      int         port_descriptor;
};

//    Declare a list of open comm ports
WX_DECLARE_LIST(OpenCommPortElement, ListOfOpenCommPorts);


class ComPortManager:  public wxEvtHandler
{
public:
      ComPortManager();
      ~ComPortManager();

      int OpenComPort(wxString &com_name, int baud_rate);
      int GetComPort(wxString &com_name);                   // get the descriptor for an already open port, or -1 if not open
      int CloseComPort(int fd);

      int WriteComPort(wxString& com_name, const wxString& string);
private:
      int OpenComPortPhysical(wxString &com_name, int baud_rate);
      int CloseComPortPhysical(int fd);
      int WriteComPortPhysical(int port_descriptor, const wxString& string);

      ListOfOpenCommPorts     m_port_list;


};




#endif


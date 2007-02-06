/******************************************************************************
 * $Id: statwin.h,v 1.4 2007/02/06 02:11:47 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Status Window
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
 * $Log: statwin.h,v $
 * Revision 1.4  2007/02/06 02:11:47  dsr
 * Cleanup
 *
 * Revision 1.3  2006/10/01 03:24:40  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.4  2006/08/04 11:43:37  dsr
 * no message
 *
 * Revision 1.3  2006/07/06 23:15:13  dsr
 * Add WiFi Server Status Display
 *
 * Revision 1.2  2006/07/05 02:34:32  dsr
 * Add WiFi Client Status Window
 *
 *
 */


#ifndef __statwin_H__
#define __statwin_H__



//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------
#define KEY_REGIONS_MAX       20

#define NSIGBARS              4

// Class declarations

class MyFrame;
//----------------------------------------------------------------------------
// TStatWin
//----------------------------------------------------------------------------
class TStatWin: public wxWindow
{
public:
      TStatWin(wxFrame *frame);
      ~TStatWin();

      void OnSize(wxSizeEvent& event);
      void OnPaint(wxPaintEvent& event);
      void TextDraw(const char * text);

      char  *pText;
      bool  bTextSet;

DECLARE_EVENT_TABLE()
};


//----------------------------------------------------------------------------
// PianoWin
//----------------------------------------------------------------------------
class PianoWin: public wxWindow
{
public:
      PianoWin(wxFrame *frame);
      ~PianoWin();

      void OnSize(wxSizeEvent& event);
      void OnPaint(wxPaintEvent& event);
      void FormatKeys(void);
      void MouseEvent(wxMouseEvent& event);

      int         Size_X, Size_Y, Pos_X, Pos_Y;

      wxRegion    KeyRegion[KEY_REGIONS_MAX];

private:
      int         nRegions;
      int         index_last;

      wxBrush     *pbackBrush;
      wxBrush     *ptBrush;
      wxBrush     *pvBrush;
      wxBrush     *psvBrush;
      wxBrush     *puvBrush;
      wxBrush     *pslBrush;

      MyFrame     *gparent;

DECLARE_EVENT_TABLE()
};

#ifdef USE_WIFI_CLIENT
//----------------------------------------------------------------------------
// WiFiStatWin
//----------------------------------------------------------------------------
class WiFiStatWin: public wxWindow
{
    public:
        WiFiStatWin(wxFrame *frame);
        ~WiFiStatWin();

        void OnSize(wxSizeEvent& event);
        void OnPaint(wxPaintEvent& event);
        void TextDraw(const char * text);
        void SetNumberStations(int n);
        void SetStationQuality(int istation, int quality);
        void SetStationSecureFlag(int istation, int flag);
        void SetStationAge(int istation, int age);
        void SetServerStatus(bool stat) { m_bserverstat = stat; }
        void DrawBars(wxDC &dc, int x, int y, int box_width, int box_height, int val, int val_max);


        wxBrush     *pqual_hiBrush;
        wxBrush     *psecureBrush;

        wxBrush     *pqual_hiNewBrush;
        wxBrush     *psecureNewBrush;

        wxBrush     *pbackBrush;

        int         m_nstations;
        int         m_quality[NSIGBARS];
        int         m_secure[NSIGBARS];
        int         m_age[NSIGBARS];
        bool        m_bserverstat;

        DECLARE_EVENT_TABLE()
};
#endif


//----------------------------------------------------------------------------
// StatWin
//----------------------------------------------------------------------------
class StatWin: public wxWindow
{
public:
      StatWin(wxFrame *frame);
      ~StatWin();
      void OnSize(wxSizeEvent& event);
      void OnPaint(wxPaintEvent& event);
      void MouseEvent(wxMouseEvent& event);
      int  GetFontHeight();
      int  GetRows(){ return(m_rows);}

      void FormatStat(void);

      int         Size_X, Size_Y, Pos_X, Pos_Y;

      int         m_rows;

      PianoWin    *pPiano;
      TStatWin    *pTStat1;
      TStatWin    *pTStat2;
#ifdef USE_WIFI_CLIENT
      WiFiStatWin *pWiFi;
#endif

private:


DECLARE_EVENT_TABLE()
};

#endif

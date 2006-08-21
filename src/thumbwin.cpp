/******************************************************************************
 * $Id: thumbwin.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  Chart Thumbnail Object
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
 * $Log: thumbwin.cpp,v $
 * Revision 1.1  2006/08/21 05:52:19  dsr
 * Initial revision
 *
 * Revision 1.3  2006/08/04 11:42:03  dsr
 * no message
 *
 * Revision 1.2  2006/05/19 19:29:58  dsr
 * New Thumbchart logic
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.5  2006/04/19 00:53:01  dsr
 * Do not allow Thumbwin.y to be larger than parent frame.y
 *
 * Revision 1.4  2006/03/16 03:08:25  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/02/23 01:52:15  dsr
 * Cleanup
 *
 *
 *
 */

#include "dychart.h"

CPL_CVSID("$Id: thumbwin.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $");


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "thumbwin.h"
#include "chart1.h"
#include "chartdb.h"
#include "chcanv.h"


//------------------------------------------------------------------------------
//    External Static Storage
//------------------------------------------------------------------------------
extern ChartDB          *ChartData;
extern ChartStack       *pCurrentStack;
extern int              CurrentStackEntry;

extern MyFrame          *gFrame;
extern ChartBase        *Current_Ch;
extern ChartCanvas      *cc1;



//------------------------------------------------------------------------------
//    Thumbwin Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(ThumbWin, wxWindow)
  EVT_PAINT(ThumbWin::OnPaint)
  EVT_SIZE(ThumbWin::OnSize)
  EVT_MOUSE_EVENTS(ThumbWin::MouseEvent)
END_EVENT_TABLE()

// Define a constructor
ThumbWin::ThumbWin(wxFrame *frame):
 wxWindow(frame, wxID_ANY,    wxPoint(20,20), wxSize(5,5), wxSIMPLE_BORDER)



{
      pThumbChart = NULL;
      m_max_size.x = m_max_size.y = 100;
      Show(false);

 }

ThumbWin::~ThumbWin()
{

}

void ThumbWin::Resize(void)
{
    if(pThumbChart)
    {
      if(pThumbChart->GetThumbData()->pDIB)
      {
            int newheight = __min(m_max_size.y, pThumbChart->GetThumbData()->pDIB->GetHeight());
            int newwidth  = __min(m_max_size.x, pThumbChart->GetThumbData()->pDIB->GetWidth());
            SetSize(0,0,newwidth,newheight );
      }
    }

}

void ThumbWin::SetMaxSize(wxSize max_size)
{
      m_max_size = max_size;
}


void ThumbWin::OnPaint(wxPaintEvent& event)
{

    wxPaintDC dc(this);

    if(pThumbChart)
    {
      if(pThumbChart->GetThumbData())
      {
            if(pThumbChart->GetThumbData()->pDIB)
                  dc.DrawBitmap(*(pThumbChart->GetThumbData()->pDIB), 0, 0, false);

            wxPen ppPen(wxColour(0,0,0), 1, wxSOLID);
            dc.SetPen(ppPen);
            wxBrush yBrush(wxColour(255,255,0), wxSOLID);
            dc.SetBrush(yBrush);
            dc.DrawCircle(pThumbChart->GetThumbData()->ShipX, pThumbChart->GetThumbData()->ShipY, 6);
      }
    }

}


void ThumbWin::OnSize(wxSizeEvent& event)
{
}


void ThumbWin::MouseEvent(wxMouseEvent& event)
{
}

/******************************************************************************
 * $Id: concanv.h,v 1.2 2007/06/10 02:37:18 bdbcat Exp $
 *
 * Project:  OpenCP
 * Purpose:  Console Canvas
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
 * $Log: concanv.h,v $
 * Revision 1.2  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.5  2006/04/19 00:57:20  dsr
 * Use FontMgr
 *
 * Revision 1.4  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/02/23 01:20:29  dsr
 * Cleanup
 *
 *
 *
 */

#ifndef __concanv_H__
#define __concanv_H__


//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------

#include "chart1.h"             // for ColorScheme


// Class declarations
class Routeman;

//----------------------------------------------------------------------------
// CDI
//----------------------------------------------------------------------------

class CDI:public wxWindow
{
public:
      CDI(wxWindow* parent, wxWindowID id,
             const wxPoint& pos, const wxSize& size, long style, const wxString& name);

      void OnPaint(wxPaintEvent& event);
      void SetColorScheme(ColorScheme cs);

      wxBrush *pbackBrush;
      wxBrush *proadBrush;

DECLARE_EVENT_TABLE()

};

//----------------------------------------------------------------------------
// AnnunText
//----------------------------------------------------------------------------
class AnnunText : public wxWindow
{
public:
      AnnunText(wxWindow *parent, wxWindowID id,
                const wxPoint& pos, const wxSize& size, const char *LegendElement, const char *ValueElement);

      ~AnnunText();

      void SetALabel(const wxString &l);
      void SetAValue(const wxString &v);
      void OnPaint(wxPaintEvent& event);
      void RefreshFonts(void);
      void SetLegendElement(const wxString &element);
      void SetValueElement(const wxString &element);
      void SetColorScheme(ColorScheme cs);

      wxBrush     *pbackBrush;
      wxColour    m_text_color;

      wxString    *label;
      wxString    *value;
      wxFont      *plabelFont;
      wxFont      *pvalueFont;

      wxString    *pLegendTextElement;
      wxString    *pValueTextElement;

DECLARE_EVENT_TABLE()

};






//----------------------------------------------------------------------------
// ConsoleCanvas
//----------------------------------------------------------------------------
class ConsoleCanvas: public wxControl
{
public:
      ConsoleCanvas(wxFrame *frame);
      ~ConsoleCanvas();
      void OnSize(wxSizeEvent& event);
      void UpdateRouteData();
      void MouseEvent(wxMouseEvent& event);
      void ShowWithFreshFonts(void);
      void SetColorScheme(ColorScheme cs);

      wxStaticBox       *pThisLegBox;
      AnnunText         *pXTE;
      AnnunText         *pBRG;
      AnnunText         *pRNG;
      AnnunText         *pTTG;
      CDI               *pCDI;
      wxFont            *pThisLegFont;

      int               Size_X, Size_Y, Pos_X, Pos_Y;
      bool              m_bRouteDataStale;
      bool              m_bNeedClear;
      bool              m_bShowRouteTotal;

      wxRegion          *pSBoxRgn;
      wxBrush *pbackBrush;

private:
      void OnPaint(wxPaintEvent& event);


DECLARE_EVENT_TABLE()
};

#endif

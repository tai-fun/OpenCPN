/******************************************************************************
 * $Id: about.h,v 1.1 2006/08/21 05:52:11 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  About Dialog
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
 * $Log: about.h,v $
 * Revision 1.1  2006/08/21 05:52:11  dsr
 * Initial revision
 *
 * Revision 1.2  2006/04/23 04:04:28  dsr
 * Fix internal names
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.2  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.1  2006/02/23 03:39:19  dsr
 * Initial
 *
 *
 *
 */


#ifndef _ABOUT_H_
#define _ABOUT_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/notebook.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers

#define ID_DIALOG 10001
#define SYMBOL_ABOUT_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_ABOUT_TITLE _("About OpenCPN")
#define SYMBOL_ABOUT_IDNAME ID_DIALOG
#define SYMBOL_ABOUT_SIZE wxSize(500, 500)
#define SYMBOL_ABOUT_POSITION wxDefaultPosition

#define ID_NOTEBOOK 10002
#define ID_PANEL2 10007
#define ID_PANEL 10004
#define ID_DIRCTRL 10005
#define ID_TEXTCTRL 10003
#define ID_BUTTONDELETE 10006
#define ID_BUTTONREBUILD 10008
#define ID_PANEL3 10012
#define ID_CHECKLISTBOX 10013
#define ID_RADIOBOX 10014
#define xID_OK 10009

////@end control identifiers

/*!
 * Compatibility
 */

#ifndef wxCLOSE_BOX
#define wxCLOSE_BOX 0x1000
#endif
#ifndef wxFIXED_MINSIZE
#define wxFIXED_MINSIZE 0
#endif

/*!
 * about class declaration
 */

class about: public wxDialog
{
  DECLARE_DYNAMIC_CLASS( about )
      DECLARE_EVENT_TABLE()

  public:
    /// Constructors
    about( );
    about( wxWindow* parent, wxString *pLicense_Data_Locn,
           wxWindowID id = SYMBOL_ABOUT_IDNAME,
           const wxString& caption = SYMBOL_ABOUT_TITLE,
           const wxPoint& pos = SYMBOL_ABOUT_POSITION,
           const wxSize& size = SYMBOL_ABOUT_SIZE,
           long style = SYMBOL_ABOUT_STYLE);

    /// Creation
    bool Create( wxWindow* parent,
                 wxWindowID id = SYMBOL_ABOUT_IDNAME,
                 const wxString& caption = SYMBOL_ABOUT_TITLE,
                 const wxPoint& pos = SYMBOL_ABOUT_POSITION,
                 const wxSize& size = SYMBOL_ABOUT_SIZE,
                 long style = SYMBOL_ABOUT_STYLE );

    /// Creates the controls and sizers
    void CreateControls();

    void SetInitialSettings();



////@begin options event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for xID_OK
    void OnXidOkClick( wxCommandEvent& event );


    void OnPageChange(wxNotebookEvent& event);


    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end options member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    wxWindow          *pParent;
    wxString          *pLicenseLocn;

    /*
////@begin options member variables

    */
};




 class AboutSetup
{
  public:

    AboutSetup();
};




#endif    // _ABOUT_H_


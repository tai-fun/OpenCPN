/////////////////////////////////////////////////////////////////////////////
// Name:        routeprop.h
// Purpose:
// Author:
// Modified by:
// Created:     01/16/08 19:39:35
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _ROUTEPROP_H_
#define _ROUTEPROP_H_

/*!
 * Includes
 */
#include "wx/listctrl.h"
#include "chart1.h"                 // for ColorScheme

/*!
 * Forward declarations
 */

class   wxListCtrl;
class   Route;
class   RoutePoint;
/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_ROUTEPROP 7000
#define SYMBOL_ROUTEPROP_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_ROUTEPROP_TITLE _("Route Properties")
#define SYMBOL_ROUTEPROP_IDNAME ID_ROUTEPROP
#define SYMBOL_ROUTEPROP_SIZE wxSize(400, 300)
#define SYMBOL_ROUTEPROP_POSITION wxDefaultPosition

#define ID_TEXTCTRL 7001
#define ID_TEXTCTRL2 7002
#define ID_TEXTCTRL1 7003
#define ID_TEXTCTRL3 7005
#define ID_LISTCTRL 7004
#define ID_ROUTEPROP_CANCEL 7006
#define ID_ROUTEPROP_OK 7007
#define ID_PLANSPEEDCTL 7008
#define ID_TEXTCTRL4 7009

#define ID_MARKPROP 8000
#define SYMBOL_MARKPROP_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_MARKPROP_TITLE _("Mark Properties")
#define SYMBOL_MARKPROP_IDNAME ID_MARKPROP
#define SYMBOL_MARKPROP_SIZE wxSize(200, 300)
#define SYMBOL_MARKPROP_POSITION wxDefaultPosition
#define ID_MARKPROP_CANCEL 8001
#define ID_MARKPROP_OK 8002
#define ID_ICONCTRL 8003
#define ID_LATCTRL 8004
#define ID_LONCTRL 8005
#define ID_SHOWNAMECHECKBOX1 8006

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
 * RouteProp class declaration
 */


class RouteProp: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( RouteProp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    RouteProp( );
    RouteProp(wxWindow* parent, wxWindowID id = SYMBOL_ROUTEPROP_IDNAME,
        const wxString& caption = SYMBOL_ROUTEPROP_TITLE,
        const wxPoint& pos = SYMBOL_ROUTEPROP_POSITION,
        const wxSize& size = SYMBOL_ROUTEPROP_SIZE,
        long style = SYMBOL_ROUTEPROP_STYLE );
    ~RouteProp( );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_ROUTEPROP_IDNAME,
                 const wxString& caption = SYMBOL_ROUTEPROP_TITLE,
                 const wxPoint& pos = SYMBOL_ROUTEPROP_POSITION,
                 const wxSize& size = SYMBOL_ROUTEPROP_SIZE,
                 long style = SYMBOL_ROUTEPROP_STYLE );

    void CreateControls();

    void SetColorScheme(ColorScheme cs);

    void OnRoutepropCancelClick( wxCommandEvent& event );
    void OnRoutepropOkClick( wxCommandEvent& event );
    void OnPlanSpeedCtlUpdated( wxCommandEvent& event );


    /// Should we show tooltips?
    static bool ShowToolTips();

    void SetRouteAndUpdate(Route *pR);
    Route *GetRoute(void){return m_pRoute;}

    bool UpdateProperties(void);
    bool SaveChanges(void);

    wxTextCtrl* m_TotalDistCtl;
    wxTextCtrl* m_PlanSpeedCtl;
    wxTextCtrl* m_TimeEnrouteCtl;

    wxTextCtrl* m_RouteNameCtl;
    wxTextCtrl* m_RouteStartCtl;
    wxTextCtrl* m_RouteDestCtl;

    wxListCtrl* m_wpList;

    wxButton*     m_CancelButton;
    wxButton*     m_OKButton;

    Route       *m_pRoute;
    double      m_planspeed;
};


/*!
 * MarkProp class declaration
 */

class MarkProp: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( MarkProp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MarkProp( );
    MarkProp( wxWindow* parent, wxWindowID id = SYMBOL_MARKPROP_IDNAME,
        const wxString& caption = SYMBOL_MARKPROP_TITLE,
        const wxPoint& pos = SYMBOL_MARKPROP_POSITION,
        const wxSize& size = SYMBOL_MARKPROP_SIZE,
        long style = SYMBOL_MARKPROP_STYLE );

    ~MarkProp();

    /// Creation
      bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MARKPROP_IDNAME,
          const wxString& caption = SYMBOL_MARKPROP_TITLE,
          const wxPoint& pos = SYMBOL_MARKPROP_POSITION,
          const wxSize& size = SYMBOL_MARKPROP_SIZE, long style = SYMBOL_MARKPROP_STYLE );

      void SetRoutePoint(RoutePoint *pRP);
      RoutePoint *GetRoutePoint(void){return m_pRoutePoint;}

      void SetColorScheme(ColorScheme cs);

      void CreateControls();

      void OnMarkpropCancelClick( wxCommandEvent& event );
      void OnMarkpropOkClick( wxCommandEvent& event );
      void OnIconListSelected( wxListEvent& event );
      void OnPositionCtlUpdated( wxCommandEvent& event );
      void OnShowNamecheckboxClick( wxCommandEvent& event );

    /// Should we show tooltips?
      static bool ShowToolTips();

      bool UpdateProperties(void);
      bool SaveChanges(void);

      wxTextCtrl*   m_MarkNameCtl;
      wxTextCtrl*   m_MarkLatCtl;
      wxTextCtrl*   m_MarkLonCtl;
      wxListCtrl*   m_IconList;
      wxCheckBox*   m_ShowNameCheckbox;
      wxButton*     m_CancelButton;
      wxButton*     m_OKButton;

      int           m_current_icon_Index;
      double        m_lat_save;
      double        m_lon_save;
      wxString      m_IconName_save;
      bool          m_bShowName_save;

      RoutePoint  *m_pRoutePoint;
};


//    LatLonTextCtrl Specification
//    We need a derived wxText control for lat/lon input in the MarkProp dialog
//    Specifically, we need to catch loss-of-focus events and signal the parent dialog
//    to update the mark's lat/lon dynamically.

DECLARE_EVENT_TYPE(EVT_LLCHANGE, -1)

class LatLonTextCtrl: public wxTextCtrl
{
//    DECLARE_DYNAMIC_CLASS( LatLonTextCtrl )
    DECLARE_EVENT_TABLE()

public:
      LatLonTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value = _T(""),
            const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
            long style = 0, const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxTextCtrlNameStr);

      void OnKillFocus(wxFocusEvent &event);


      wxEvtHandler *m_pParentEventHandler;

};

#endif
    // _ROUTEPROP_H_

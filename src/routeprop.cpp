/////////////////////////////////////////////////////////////////////////////
// Name:        routeprop.cpp
// Purpose:
// Author:
// Modified by:
// Created:     01/16/08 19:39:35
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/listimpl.cpp>    // toh, 2009.02.22

#include "wx/datetime.h"

#include "routeprop.h"
#include "navutil.h"                // for Route
#include "georef.h"
#include "chart1.h"
#include "routeman.h"
#include "chcanv.h"


extern "C" float DistGreatCircle(double slat, double slon, double dlat, double dlon);

extern double           gLat, gLon;
extern double           g_PlanSpeed;
extern MyConfig         *pConfig;
extern WayPointman      *pWayPointMan;
extern ChartCanvas      *cc1;
extern Select           *pSelect;
extern Routeman         *pRouteMan;
extern RouteProp        *pRoutePropDialog;

WX_DEFINE_LIST(HyperlinkCtrlList);        // toh, 2009.02.22

#define MAX_NUM_HYPERLINKS    6           // toh, 2009.02.23


/*!
 * RouteProp type definition
 */

IMPLEMENT_DYNAMIC_CLASS( RouteProp, wxDialog )

/*!
 * RouteProp event table definition
 */

BEGIN_EVENT_TABLE( RouteProp, wxDialog )


    EVT_TEXT( ID_PLANSPEEDCTL, RouteProp::OnPlanSpeedCtlUpdated )
    EVT_BUTTON( ID_ROUTEPROP_CANCEL, RouteProp::OnRoutepropCancelClick )
    EVT_BUTTON( ID_ROUTEPROP_OK, RouteProp::OnRoutepropOkClick )
    EVT_LIST_ITEM_SELECTED( ID_LISTCTRL, RouteProp::OnRoutepropListClick )
    EVT_CLOSE(RouteProp::OnClose )
END_EVENT_TABLE()

/*!
 * RouteProp constructors
 */

RouteProp::RouteProp( )
{
}

RouteProp::RouteProp( wxWindow* parent, wxWindowID id,
                     const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

void RouteProp::OnRoutepropListClick( wxListEvent& event )
{
    long itemno = 0;
    const wxListItem &i = event.GetItem();
    i.GetText().ToLong(&itemno);

    m_pRoute->ClearHighlights();

    wxRoutePointListNode *node = m_pRoute->pRoutePointList->GetFirst();
    while(node && itemno--)
    {
          node = node->GetNext();
    }
    if ( node )
    {
      RoutePoint *prp = node->GetData();
      if ( prp )
      {
          prp->m_bPtIsSelected = true;                // highlight the routepoint
//          vLat = cc1->VPoint.clat = prp->m_lat;
//          vLon = cc1->VPoint.clon = prp->m_lon;
//          cc1->SetVPScale ( cc1->GetVPScale() );
//          cc1->Refresh();
          cc1->SetViewPoint(prp->m_lat, prp->m_lon);
      }
    }
}

RouteProp::~RouteProp( )
{
    delete m_TotalDistCtl;
    delete m_PlanSpeedCtl;
    delete m_TimeEnrouteCtl;

    delete m_RouteNameCtl;
    delete m_RouteStartCtl;
    delete m_RouteDestCtl;

    delete m_wpList;
}


/*!
 * RouteProp creator
 */

bool RouteProp::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin RouteProp member initialisation
    m_TotalDistCtl = NULL;
    m_wpList = NULL;
////@end RouteProp member initialisation

////@begin RouteProp creation
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();
////@end RouteProp creation
    return TRUE;
}

/*!
 * Control creation for RouteProp
 */

void RouteProp::CreateControls()
{
////@begin RouteProp content construction

    RouteProp* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Properties"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxEXPAND|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Name"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_RouteNameCtl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(680, -1), 0 );
    itemStaticBoxSizer3->Add(m_RouteNameCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);


    wxFlexGridSizer* itemFlexGridSizer6 = new wxFlexGridSizer(2, 2, 0, 0);
    itemStaticBoxSizer3->Add(itemFlexGridSizer6, 1, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("Depart From"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Destination"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, 5);

    m_RouteStartCtl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL2, _T(""), wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer6->Add(m_RouteStartCtl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_RouteDestCtl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL1, _T(""), wxDefaultPosition, wxSize(300, -1), 0 );
    itemFlexGridSizer6->Add(m_RouteDestCtl, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);


    wxFlexGridSizer* itemFlexGridSizer6a = new wxFlexGridSizer(2, 3, 0, 0);
    itemStaticBoxSizer3->Add(itemFlexGridSizer6a, 1, wxALIGN_LEFT|wxALL, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( itemDialog1, wxID_STATIC, _("Total Distance"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6a->Add(itemStaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _T("Plan Speed"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6a->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    wxStaticText* itemStaticText12a = new wxStaticText( itemDialog1, wxID_STATIC, _T("Time Enroute"),wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6a->Add(itemStaticText12a, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_TotalDistCtl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL3, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemFlexGridSizer6a->Add(m_TotalDistCtl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_PlanSpeedCtl = new wxTextCtrl( itemDialog1, ID_PLANSPEEDCTL, _T(""), wxDefaultPosition, wxSize(100, -1), wxTE_PROCESS_ENTER );
    itemFlexGridSizer6a->Add(m_PlanSpeedCtl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);

    m_TimeEnrouteCtl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL4, _T(""), wxDefaultPosition, wxSize(200, -1), wxTE_READONLY );
    itemFlexGridSizer6a->Add(m_TimeEnrouteCtl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxBOTTOM, 5);


    wxStaticBox* itemStaticBoxSizer14Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Waypoints"));
    wxStaticBoxSizer* itemStaticBoxSizer14 = new wxStaticBoxSizer(itemStaticBoxSizer14Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer14, 1, wxEXPAND|wxALL, 5);

    m_wpList = new wxListCtrl( itemDialog1, ID_LISTCTRL, wxDefaultPosition, wxSize(-1, 100),
                               wxLC_REPORT|wxLC_HRULES|wxLC_VRULES|wxLC_EDIT_LABELS );
    itemStaticBoxSizer14->Add(m_wpList, 2, wxEXPAND|wxALL, 5);

    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer16, 0, wxALIGN_RIGHT|wxALL, 5);

    m_CancelButton = new wxButton( itemDialog1, ID_ROUTEPROP_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(m_CancelButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_OKButton = new wxButton( itemDialog1, ID_ROUTEPROP_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(m_OKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    m_OKButton->SetDefault();

    //      To correct a bug in MSW commctl32, we nee to catch column width drag events, and do a Refresh()
    //      Otherwise, the column heading disappear.....
    //      Does no harm for GTK builds, so no need for conditional
    Connect(wxEVT_COMMAND_LIST_COL_END_DRAG, (wxObjectEventFunction)(wxEventFunction)&RouteProp::OnEvtColDragEnd);

    // note that under MSW for SetColumnWidth() to work we need to create the
    // items with images initially even if we specify dummy image id
    wxListItem itemCol;
    itemCol.SetImage(-1);

    itemCol.SetText(_T("Leg"));
    m_wpList->InsertColumn(0, itemCol);
    m_wpList->SetColumnWidth( 0,  50 );

    itemCol.SetText(_T("To Waypoint"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    m_wpList->InsertColumn(1, itemCol);
    m_wpList->SetColumnWidth( 1,   150 );

    itemCol.SetText(_T("Distance"));
    itemCol.SetAlign(wxLIST_FORMAT_RIGHT);
    m_wpList->InsertColumn(2, itemCol);
    m_wpList->SetColumnWidth( 2,   100 );

    itemCol.SetText(_T("Bearing"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    m_wpList->InsertColumn(3, itemCol);
    m_wpList->SetColumnWidth( 3,   80 );

    itemCol.SetText(_T("Latitude"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    m_wpList->InsertColumn(4, itemCol);
    m_wpList->SetColumnWidth( 4,  95 );

    itemCol.SetText(_T("Longitude"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    m_wpList->InsertColumn(5, itemCol);
    m_wpList->SetColumnWidth( 5,   95 );

    itemCol.SetText(_T("ETE"));
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    m_wpList->InsertColumn(6, itemCol);
    m_wpList->SetColumnWidth( 6,  120 );

//  Fetch any config file values
    m_planspeed = g_PlanSpeed;

    SetColorScheme((ColorScheme)0);

}


void RouteProp::SetColorScheme(ColorScheme cs)
{
      SetBackgroundColour(GetGlobalColor(_T("DILG1")));

      wxColour back_color =GetGlobalColor(_T("DILG2"));
      wxColour text_color = GetGlobalColor(_T("DILG3"));

      m_RouteNameCtl->SetBackgroundColour(back_color);
      m_RouteNameCtl->SetForegroundColour(text_color);

      m_RouteStartCtl->SetBackgroundColour(back_color);
      m_RouteStartCtl->SetForegroundColour(text_color);

      m_RouteDestCtl->SetBackgroundColour(back_color);
      m_RouteDestCtl->SetForegroundColour(text_color);

      m_TotalDistCtl->SetBackgroundColour(back_color);
      m_TotalDistCtl->SetForegroundColour(text_color);

      m_PlanSpeedCtl->SetBackgroundColour(back_color);
      m_PlanSpeedCtl->SetForegroundColour(text_color);

      m_TimeEnrouteCtl->SetBackgroundColour(back_color);
      m_TimeEnrouteCtl->SetForegroundColour(text_color);

      m_wpList->SetBackgroundColour(back_color);
      m_wpList->SetForegroundColour(text_color);

      m_CancelButton->SetBackgroundColour(back_color);
      m_CancelButton->SetForegroundColour(text_color);

      m_OKButton->SetBackgroundColour(back_color);
      m_OKButton->SetForegroundColour(text_color);
}
/*!
 * Should we show tooltips?
 */

bool RouteProp::ShowToolTips()
{
    return TRUE;
}


void RouteProp::SetDialogTitle(wxString title)
{
      SetTitle(title);
}



void RouteProp::SetRouteAndUpdate(Route *pR)
{
      m_pRoute = pR;
      m_wpList->DeleteAllItems();

//  Iterate on Route Points, inserting blank fields starting with index 0
      if(pR)
      {
            wxRoutePointListNode *pnode = m_pRoute->pRoutePointList->GetFirst();

            int in=0;
            while(pnode)
            {
                  m_wpList->InsertItem(in, _T(""), 0);
                  in++;
                  pnode = pnode->GetNext();
            }

            //  Set User input Text Fields
            m_RouteNameCtl->SetValue(m_pRoute->m_RouteNameString);
            m_RouteStartCtl->SetValue(m_pRoute->m_RouteStartString);
            m_RouteDestCtl->SetValue(m_pRoute->m_RouteEndString);

            m_RouteNameCtl->SetFocus();

            //      Update the plan speed control
            wxString s;
            s.Printf(_T("%5.2f"), m_planspeed);
            m_PlanSpeedCtl->SetValue(s);



      }
}



bool RouteProp::UpdateProperties()
{
    if(m_pRoute)
    {
        m_pRoute->UpdateSegmentDistances();           // get segment and total distance

    //  Total length
        wxString slen;
        slen.Printf(wxT("%5.2f"), m_pRoute->m_route_length);

        m_TotalDistCtl->SetValue(slen);

        wxString time_form;
        double total_seconds = 0.;

        if((0.1 < m_planspeed) && (m_planspeed < 1000.0))
              total_seconds= 3600 * m_pRoute->m_route_length / m_planspeed;     // in seconds

    //  Time

        wxTimeSpan time(0,0, (int)total_seconds, 0);
        if(total_seconds > 3600. * 24.)
              time_form = time.Format(_T(" %D Days  %H Hours  %M Minutes"));
        else
              time_form = time.Format(_T(" %H Hours  %M Minutes"));

        m_TimeEnrouteCtl->SetValue(time_form);


    //  Iterate on Route Points
        wxRoutePointListNode *node = m_pRoute->pRoutePointList->GetFirst();

        int i=0;
        double slat, slon;
        double tdis;

        while(node)
        {
                RoutePoint *prp = node->GetData();
                long item_line_index = i;

    //  Leg
                wxString t;
                t.Printf(_T("%d"), i);
                if(i == 0)
                    t = _T("---");
                m_wpList->SetItem(item_line_index, 0, t);


    //  Mark Name
                m_wpList->SetItem(item_line_index, 1, prp->m_MarkName);

    //  Distance
    //  Note that Distance/Bearing for Leg 000 is as from current position

                if(i == 0)
                {
                    slat = gLat;
                    slon = gLon;
                }

                double brg, leg_dist;
                DistanceBearing(prp->m_lat, prp->m_lon, slat, slon, &brg, &leg_dist);

                t.Printf(_T("%6.2f nm"),leg_dist);
                m_wpList->SetItem(item_line_index, 2, t);

    //  Bearing
                t.Printf(_T("%03.0f Deg. T"),brg);
                m_wpList->SetItem(item_line_index, 3, t);

    //  Lat/Lon
                wxString tlat = toSDMM(1, prp->m_lat);
                m_wpList->SetItem(item_line_index, 4, tlat);

                wxString tlon = toSDMM(2, prp->m_lon);
                m_wpList->SetItem(item_line_index, 5, tlon);

    // Time to each waypoint
                if ( i == 0 )
                {
                      time_form.Printf(_T("Start"));
                      tdis = 0;
                }
                else
                {
                  tdis += leg_dist;
                  if (m_planspeed)
                  {
                      double seconds = 3600 * tdis / m_planspeed;     // in seconds
                      wxTimeSpan time(0,0, (int)seconds, 0);

                      if(total_seconds > 3600. * 24.)
                            time_form = time.Format(_T(" %D D  %H H  %M M"));
                      else
                            time_form = time.Format(_T(" %H H  %M M"));
                  }

                }
                m_wpList->SetItem(item_line_index, 6, time_form);

    //  Save for iterating distance/bearing calculation
                slat = prp->m_lat;
                slon = prp->m_lon;

                i++;
                node = node->GetNext();
          }

#if 0
          m_wpList->SetColumnWidth( 0, wxLIST_AUTOSIZE/* 35 */);
          m_wpList->SetColumnWidth( 1,  wxLIST_AUTOSIZE/* 150*/ );
          m_wpList->SetColumnWidth( 2,  wxLIST_AUTOSIZE/* 80*/ );
          m_wpList->SetColumnWidth( 3,  wxLIST_AUTOSIZE/* 80*/ );
          m_wpList->SetColumnWidth( 4,  wxLIST_AUTOSIZE/* 95*/ );
          m_wpList->SetColumnWidth( 5,  wxLIST_AUTOSIZE/* 95*/ );
          m_wpList->SetColumnWidth( 6,  wxLIST_AUTOSIZE/* 120*/ );
#endif

    }
    return true;
}

bool RouteProp::SaveChanges(void)
{

//  Save the current planning speed
    g_PlanSpeed = m_planspeed;

//  Get User input Text Fields
    m_pRoute->m_RouteNameString = m_RouteNameCtl->GetValue();
    m_pRoute->m_RouteStartString = m_RouteStartCtl->GetValue();
    m_pRoute->m_RouteEndString = m_RouteDestCtl->GetValue();

    pConfig->UpdateRoute(m_pRoute);
    pConfig->UpdateSettings();

    return true;

}


void RouteProp::OnPlanSpeedCtlUpdated( wxCommandEvent& event )
{
    //  Fetch the value, and see if it is a "reasonable" speed
    wxString spd = m_PlanSpeedCtl->GetValue();
    double s;
    spd.ToDouble(&s);
    if((0.1 < s) && (s < 1000.0))
    {
        m_planspeed = s;

        UpdateProperties();
    }

    event.Skip();
}


/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void RouteProp::OnRoutepropCancelClick( wxCommandEvent& event )
{

      Hide();
//      Close();
      event.Skip();
}

/*!
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON1
 */

void RouteProp::OnRoutepropOkClick( wxCommandEvent& event )
{
    SaveChanges();              // write changes to globals and update config

    Hide();
//    Close();
    event.Skip();
}

void RouteProp::OnClose(wxCloseEvent& event)
{
//      Destroy();
//      pRoutePropDialog = NULL;
}

void RouteProp::OnEvtColDragEnd(wxListEvent& event)
{
      m_wpList->Refresh();
}



//-------------------------------------------------------------------------------
//
//    Mark Properties Dialog Implementation
//
//-------------------------------------------------------------------------------
/*!
 * MarkProp type definition
 */

DEFINE_EVENT_TYPE(EVT_LLCHANGE)           // events from LatLonTextCtrl


IMPLEMENT_DYNAMIC_CLASS( MarkProp, wxDialog )

/*!
 * MarkProp event table definition
 */

BEGIN_EVENT_TABLE( MarkProp, wxDialog )

////@begin MarkProp event table entries

    EVT_BUTTON( ID_MARKPROP_CANCEL, MarkProp::OnMarkpropCancelClick )
    EVT_BUTTON( ID_MARKPROP_OK, MarkProp::OnMarkpropOkClick )
    EVT_LIST_ITEM_SELECTED( ID_ICONCTRL, MarkProp::OnIconListSelected)
    EVT_COMMAND(ID_LATCTRL, EVT_LLCHANGE, MarkProp::OnPositionCtlUpdated)
    EVT_COMMAND(ID_LONCTRL, EVT_LLCHANGE, MarkProp::OnPositionCtlUpdated)
    EVT_CHECKBOX( ID_SHOWNAMECHECKBOX1, MarkProp::OnShowNamecheckboxClick )

////@end RouteProp event table entries

END_EVENT_TABLE()

/*!
 * MarkProp constructors
 */

MarkProp::MarkProp( )
{
}

MarkProp::MarkProp(  wxWindow* parent, wxWindowID id,
                     const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Create(parent, id, caption, pos, size, style);
}

MarkProp::~MarkProp( )
{
    delete m_MarkNameCtl;
    delete m_MarkLatCtl;
    delete m_MarkLonCtl;
}



/*!
 * MarkProp creator
 */

bool MarkProp::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Centre();

    return TRUE;
}

/*!
 * Control creation for MarkProp
 */

void MarkProp::CreateControls()
{
    MarkProp* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Properties"));

    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer3, 1, wxEXPAND|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Mark Name"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer3->Add(itemStaticText4, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_MarkNameCtl = new wxTextCtrl( itemDialog1, ID_TEXTCTRL, _T(""), wxDefaultPosition, wxSize(-1, -1), 0 );
    itemStaticBoxSizer3->Add(m_MarkNameCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);

    m_ShowNameCheckbox = new wxCheckBox( itemDialog1, ID_SHOWNAMECHECKBOX1, _("Show Name"), wxDefaultPosition, wxSize(-1, -1), 0 );
    itemStaticBoxSizer3->Add(m_ShowNameCheckbox, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);

    wxStaticText* itemStaticText4a= new wxStaticText( itemDialog1, wxID_STATIC, _("Mark Icon"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer3->Add(itemStaticText4a, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_IconList = new wxListCtrl( itemDialog1, ID_ICONCTRL, wxDefaultPosition, wxSize(300, 100),
        wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_VRULES );
    itemStaticBoxSizer3->Add(m_IconList, 2, wxEXPAND|wxALL, 5);


    wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Position"));

    wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
    itemBoxSizer2->Add(itemStaticBoxSizer4, 0, wxEXPAND|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("Latitude"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer4->Add(itemStaticText5, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_MarkLatCtl = new LatLonTextCtrl( itemDialog1, ID_LATCTRL, _T(""), wxDefaultPosition, wxSize(180, -1), 0 );
    itemStaticBoxSizer4->Add(m_MarkLatCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);


    wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticBoxSizer4->Add(itemStaticText6, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

    m_MarkLonCtl = new LatLonTextCtrl( itemDialog1, ID_LONCTRL, _T(""), wxDefaultPosition, wxSize(180, -1), 0 );
    itemStaticBoxSizer4->Add(m_MarkLonCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 5);

    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer16, 0, wxALIGN_RIGHT|wxALL, 5);

    m_CancelButton = new wxButton( itemDialog1, ID_MARKPROP_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(m_CancelButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_OKButton = new wxButton( itemDialog1, ID_MARKPROP_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer16->Add(m_OKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    m_OKButton->SetDefault();

    //  Fill in list control

    m_IconList->Hide();

    int client_x, client_y;
    m_IconList->GetClientSize(&client_x, &client_y);

    m_IconList->SetImageList(pWayPointMan->Getpmarkicon_image_list(), wxIMAGE_LIST_SMALL);

    wxListItem itemCol0;
    itemCol0.SetImage(-1);
    itemCol0.SetText(_T("Icon"));

    m_IconList->InsertColumn(0, itemCol0);
    m_IconList->SetColumnWidth( 0, 40 );

    wxListItem itemCol;
    itemCol.SetText(_T("Description"));
    itemCol.SetImage(-1);
    itemCol.SetAlign(wxLIST_FORMAT_LEFT);
    m_IconList->InsertColumn(1, itemCol);
    m_IconList->SetColumnWidth( 1, client_x - 56 );


    //      Iterate on the Icon Descriptions, filling in the control

      for(int i = 0 ; i < pWayPointMan->GetNumIcons() ; i++)
      {
            wxString *ps = pWayPointMan->GetIconDescription(i);

            long item_index = m_IconList->InsertItem(i, _T(""), 0);
            m_IconList->SetItem(item_index, 1, *ps);

            m_IconList->SetItemImage(item_index,i);
      }

      m_IconList->Show();

      SetColorScheme((ColorScheme)0);
}


void MarkProp::SetColorScheme(ColorScheme cs)
{
      SetBackgroundColour(GetGlobalColor(_T("DILG1")));

      wxColour back_color =GetGlobalColor(_T("DILG2"));
      wxColour text_color = GetGlobalColor(_T("DILG3"));

      m_MarkNameCtl->SetBackgroundColour(back_color);
      m_MarkNameCtl->SetForegroundColour(text_color);

      m_IconList->SetBackgroundColour(back_color);
      m_IconList->SetForegroundColour(text_color);

      m_MarkLatCtl->SetBackgroundColour(back_color);
      m_MarkLatCtl->SetForegroundColour(text_color);

      m_MarkLonCtl->SetBackgroundColour(back_color);
      m_MarkLonCtl->SetForegroundColour(text_color);

      m_CancelButton->SetBackgroundColour(back_color);
      m_CancelButton->SetForegroundColour(text_color);

      m_OKButton->SetBackgroundColour(back_color);
      m_OKButton->SetForegroundColour(text_color);

      m_IconList->SetImageList(pWayPointMan->Getpmarkicon_image_list(), wxIMAGE_LIST_SMALL);

}

bool MarkProp::ShowToolTips()
{
    return TRUE;
}


void MarkProp::SetRoutePoint(RoutePoint *pRP)
{
      m_pRoutePoint = pRP;

      m_lat_save = m_pRoutePoint->m_lat;
      m_lon_save = m_pRoutePoint->m_lon;
      m_IconName_save = m_pRoutePoint->m_IconName;
      m_bShowName_save = m_pRoutePoint->m_bShowName;
}


bool MarkProp::UpdateProperties()
{
      wxString t;
      if(m_pRoutePoint)
      {
//    Name
            m_MarkNameCtl->SetValue(m_pRoutePoint->m_MarkName);
            m_ShowNameCheckbox->SetValue(m_pRoutePoint->m_bShowName);
            m_MarkNameCtl->SetInsertionPoint(0);
            m_MarkNameCtl->SetSelection(-1, -1);
            m_MarkNameCtl->SetFocus();


//  Lat/Lon
            wxString s = toSDMM(1, m_pRoutePoint->m_lat);
            m_MarkLatCtl->SetValue(s);

            s = toSDMM(2, m_pRoutePoint->m_lon);
            m_MarkLonCtl->SetValue(s);

//    Highlite the icon current selection
            m_current_icon_Index = pWayPointMan->GetIconIndex(m_pRoutePoint->m_pbmIcon);

            m_IconList->SetItemState(m_current_icon_Index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
            m_IconList->EnsureVisible(m_current_icon_Index);
    }
    return true;
}

bool MarkProp::SaveChanges(void)
{
//  Get User input Text Fields
      m_pRoutePoint->m_MarkName = m_MarkNameCtl->GetValue();

      //    Here is some logic....
      //    If the Markname is completely numeric, and is part of a route,
      //    Then declare it to be of attribute m_bDynamicName = true
      //    This is later used for re-numbering points on actions like
      //    Insert Point, Delete Point, Append Point, etc

      if(m_pRoutePoint->m_bIsInRoute)
      {
            bool b_name_is_numeric = true;
            for(unsigned int i=0 ; i<m_pRoutePoint->m_MarkName.Len() ; i++)
            {
                  if(wxChar('0') > m_pRoutePoint->m_MarkName[i])
                        b_name_is_numeric = false;
                  if(wxChar('9') < m_pRoutePoint->m_MarkName[i])
                        b_name_is_numeric = false;
            }

            m_pRoutePoint->m_bDynamicName = b_name_is_numeric;
      }
      else
            m_pRoutePoint->m_bDynamicName = false;


      if(m_pRoutePoint->m_bIsInRoute)
      {
            Route *pRoute = pRouteMan->FindRouteContainingWaypoint(m_pRoutePoint);
            pConfig->UpdateRoute(pRoute);
      }
      else
            pConfig->UpdateWayPoint(m_pRoutePoint);

      pConfig->UpdateSettings();

    return true;
}


void MarkProp::OnMarkpropCancelClick( wxCommandEvent& event )
{
      //    Restore saved values for lat/lon and icon
      m_pRoutePoint->m_lat = m_lat_save;
      m_pRoutePoint->m_lon = m_lon_save;
      m_pRoutePoint->m_IconName = m_IconName_save;
      m_pRoutePoint->m_bShowName = m_bShowName_save;

      m_pRoutePoint->m_pbmIcon = pWayPointMan->GetIconBitmap(m_IconName_save);

      Show(false);
      event.Skip();
}


void MarkProp::OnMarkpropOkClick( wxCommandEvent& event )
{
    SaveChanges();              // write changes to globals and update config

    Show(false);
    event.Skip();
}

void MarkProp::OnIconListSelected( wxListEvent& event )
{
      int new_index = event.GetIndex();
      if(new_index != m_current_icon_Index)
      {
           m_current_icon_Index = new_index;

           m_pRoutePoint->m_IconName = *(pWayPointMan->GetIconKey(m_current_icon_Index));
           m_pRoutePoint->ReLoadIcon();

           // dynamically update the icon on the canvas
           cc1->RefreshRect(m_pRoutePoint->CurrentRect_in_DC, false);
      }
}

void MarkProp::OnShowNamecheckboxClick( wxCommandEvent& event )
{
      m_pRoutePoint->m_bShowName = m_ShowNameCheckbox->GetValue();

      // dynamically update the icon on the canvas
      cc1->RefreshRect(m_pRoutePoint->CurrentRect_in_DC, false);
}

void MarkProp::OnPositionCtlUpdated( wxCommandEvent& event )
{
      char str[50];
      wxString l;

      //    Fetch the control values, convert to degrees
      l = m_MarkLatCtl->GetValue();
      strncpy(str, l.mb_str(), 49);
      double lat = fromDMM(str);

      l = m_MarkLonCtl->GetValue();
      strncpy(str, l.mb_str(), 49);
      double lon = fromDMM(str);

      m_pRoutePoint->SetPosition(lat, lon);
      pSelect->ModifySelectablePoint(lat, lon, (void *)m_pRoutePoint, SELTYPE_ROUTEPOINT);

      //    Update the mark position dynamically
      cc1->Refresh();
}


//------------------------------------------------------------------------------
//    LatLonTextCtrl Window Implementation
//------------------------------------------------------------------------------
BEGIN_EVENT_TABLE(LatLonTextCtrl, wxWindow)

      EVT_KILL_FOCUS(LatLonTextCtrl::OnKillFocus)

END_EVENT_TABLE()

// constructor
LatLonTextCtrl::LatLonTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value,
            const wxPoint& pos, const wxSize& size,
            long style, const wxValidator& validator,
            const wxString& name):
wxTextCtrl(parent, id, value, pos, size, style, validator, name)
{
      m_pParentEventHandler = parent->GetEventHandler();
}


void LatLonTextCtrl::OnKillFocus(wxFocusEvent& event)
{
      //    Send an event to the Parent Dialog
      wxCommandEvent up_event( EVT_LLCHANGE,  GetId() );
      up_event.SetEventObject( (wxObject *)this );
      m_pParentEventHandler->AddPendingEvent(up_event);
}


//-------------------------------------------------------------------------------
//
//    Mark Information Dialog Implementation
//
//-------------------------------------------------------------------------------
/*!
 * MarkInfo type definition
 */

IMPLEMENT_DYNAMIC_CLASS( MarkInfo, wxDialog )

/*!
 * MarkInfo event table definition
 */

            BEGIN_EVENT_TABLE( MarkInfo, wxDialog )

////@begin MarkInfo event table entries

            EVT_BUTTON( ID_MARKINFO_CANCEL, MarkInfo::OnMarkinfoCancelClick )
            EVT_BUTTON( ID_MARKINFO_OK, MarkInfo::OnMarkinfoOkClick )

////@end MarkInfo event table entries

            END_EVENT_TABLE()

/*!
 * MarkInfo constructors
 */

            MarkInfo::MarkInfo( )
{
}

MarkInfo::MarkInfo(  wxWindow* parent, wxWindowID id,
                     const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
      Create(parent, id, caption, pos, size, style);
}

MarkInfo::~MarkInfo( )
{
      delete m_MarkNameCtl;
      delete m_MarkLatCtl;
      delete m_MarkLonCtl;
}



/*!
 * MarkInfo creator
 */

bool MarkInfo::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
      SetExtraStyle(GetExtraStyle()|wxWS_EX_BLOCK_EVENTS);
      wxDialog::Create( parent, id, caption, pos, size, style );

      CreateControls();
      GetSizer()->Fit(this);
      GetSizer()->SetSizeHints(this);
      Centre();

      return TRUE;
}

/*!
 * Control creation for MarkInfo
 */

void MarkInfo::CreateControls()
{
      MarkInfo* itemDialog1 = this;

      wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
      itemDialog1->SetSizer(itemBoxSizer2);

      wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Name"),wxDefaultPosition, wxSize(-1, -1));

      wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
      itemBoxSizer2->Add(itemStaticBoxSizer3, 0, wxEXPAND|wxALL|wxADJUST_MINSIZE, 5);

      m_MarkNameCtl = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition,wxDefaultSize, 0 );
      itemStaticBoxSizer3->Add(m_MarkNameCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxGROW, 5);

      wxStaticBox* itemStaticBoxSizer4Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Position"));

      wxStaticBoxSizer* itemStaticBoxSizer4 = new wxStaticBoxSizer(itemStaticBoxSizer4Static, wxVERTICAL);
      itemBoxSizer2->Add(itemStaticBoxSizer4, 0, wxEXPAND|wxALL|wxADJUST_MINSIZE, 5);

      wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, _("Latitude"), wxDefaultPosition, wxDefaultSize, 0 );
      itemStaticBoxSizer4->Add(itemStaticText5, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      m_MarkLatCtl = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxSize(180, -1), 0 );
      itemStaticBoxSizer4->Add(m_MarkLatCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxGROW, 5);

      wxStaticText* itemStaticText6 = new wxStaticText( itemDialog1, wxID_STATIC, _("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
      itemStaticBoxSizer4->Add(itemStaticText6, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxADJUST_MINSIZE, 5);

      m_MarkLonCtl = new wxStaticText( itemDialog1, wxID_STATIC, _T(""), wxDefaultPosition, wxSize(180, -1), 0 );
      itemStaticBoxSizer4->Add(m_MarkLonCtl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxBOTTOM|wxGROW, 5);

      // Hyperlinks etc.
      wxStaticBox* itemStaticBoxSizer8Static = new wxStaticBox(itemDialog1, wxID_ANY, _("Links"));

    // Controls for some Hyperlinks
      m_HyperlinkCtrlList = new HyperlinkCtrlList;
      wxStaticBoxSizer* itemStaticBoxSizer8 = new wxStaticBoxSizer(itemStaticBoxSizer8Static, wxVERTICAL);
      itemBoxSizer2->Add(itemStaticBoxSizer8, 1, wxEXPAND|wxALL|wxADJUST_MINSIZE, 5);
      for (int i=0;i<MAX_NUM_HYPERLINKS;i++)
      {
            wxHyperlinkCtrl *HyperlinkCtrl;
            HyperlinkCtrl = new wxHyperlinkCtrl(this,
                        wxID_ANY,
                        _T(" "),
                           _T(" "));
            itemStaticBoxSizer8->Add(HyperlinkCtrl, 1, wxALIGN_LEFT|wxLEFT|wxRIGHT|wxTOP|wxEXPAND|wxFULL_REPAINT_ON_RESIZE, 5);
            m_HyperlinkCtrlList->Append(HyperlinkCtrl);
      }

      wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxHORIZONTAL);
      itemBoxSizer2->Add(itemBoxSizer16, 0, wxALIGN_RIGHT|wxALL, 5);

      m_CancelButton = new wxButton( itemDialog1, ID_MARKINFO_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer16->Add(m_CancelButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

      m_OKButton = new wxButton( itemDialog1, ID_MARKINFO_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer16->Add(m_OKButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
      m_OKButton->SetDefault();

      SetColorScheme((ColorScheme)0);
}


void MarkInfo::SetColorScheme(ColorScheme cs)
{
      SetBackgroundColour(GetGlobalColor(_T("DILG1")));

      wxColour back_color =GetGlobalColor(_T("DILG2"));
      wxColour text_color = GetGlobalColor(_T("DILG3"));

      m_MarkNameCtl->SetBackgroundColour(back_color);
      m_MarkNameCtl->SetForegroundColour(text_color);

      m_MarkLatCtl->SetBackgroundColour(back_color);
      m_MarkLatCtl->SetForegroundColour(text_color);

      m_MarkLonCtl->SetBackgroundColour(back_color);
      m_MarkLonCtl->SetForegroundColour(text_color);

      m_CancelButton->SetBackgroundColour(back_color);
      m_CancelButton->SetForegroundColour(text_color);

      m_OKButton->SetBackgroundColour(back_color);
      m_OKButton->SetForegroundColour(text_color);
}

bool MarkInfo::ShowToolTips()
{
      return TRUE;
}


void MarkInfo::SetRoutePoint(RoutePoint *pRP)
{
      m_pRoutePoint = pRP;

      m_lat_save = m_pRoutePoint->m_lat;
      m_lon_save = m_pRoutePoint->m_lon;
}


bool MarkInfo::UpdateProperties()
{
      wxString t;
      if(m_pRoutePoint)
      {
//    Name
            m_MarkNameCtl->SetLabel(m_pRoutePoint->m_MarkName);

//  Lat/Lon
            char tc[50];

            todmm(1, m_pRoutePoint->m_lat, tc, 49);
            wxString strt(tc, wxConvUTF8);
            m_MarkLatCtl->SetLabel(strt);

            todmm(2, m_pRoutePoint->m_lon, tc, 49);
            wxString strn(tc, wxConvUTF8);
            m_MarkLonCtl->SetLabel(strn);

            int NbrOfLinks = m_pRoutePoint->m_HyperlinkList->GetCount();
            HyperlinkList *hyperlinklist = m_pRoutePoint->m_HyperlinkList;
            int len = 0;
            if (NbrOfLinks > 0)
            {
                  wxHyperlinkListNode *linknode = hyperlinklist->GetFirst();
                  wxHyperlinkCtrlListNode *ctrlnode = m_HyperlinkCtrlList->GetFirst();

                  int i=0;
                  while (linknode && ctrlnode && i<MAX_NUM_HYPERLINKS)
                  {
                        wxHyperlinkCtrl *ctrl = ctrlnode->GetData();
                        Hyperlink *link = linknode->GetData();
                        wxString Link = link->Link;
                        wxString Descr = link->DescrText;

                        ctrl->SetURL(Link);
                        ctrl->SetLabel(Descr);

                        int DescrLen = Descr.Length();
                        if (DescrLen > len)
                        {
                              len = DescrLen;
                              wxSize size = ctrl->GetBestSize();
                              ctrl->SetSize(size);
                              ctrl->Fit();
                              ctrl->SetMinSize(size);
                        }

                        linknode = linknode->GetNext();
                        ctrlnode = ctrlnode->GetNext();
                        i++;
                  }

                  if (i < 3)
                  {
                        while (ctrlnode && i<MAX_NUM_HYPERLINKS)
                        {
                              wxHyperlinkCtrl *ctrl = ctrlnode->GetData();
                              ctrl->SetURL(_T(""));
                              ctrl->SetLabel(_T(""));

                              ctrlnode = ctrlnode->GetNext();
                              i++;
                        }
                  }
            }

            GetSizer()->Fit(this);
            Centre();
      }
      return true;
}

bool MarkInfo::SaveChanges(void)
{
      return true;
}


void MarkInfo::OnMarkinfoCancelClick( wxCommandEvent& event )
{
      Show(false);
      event.Skip();
}


void MarkInfo::OnMarkinfoOkClick( wxCommandEvent& event )
{
      Show(false);
      event.Skip();
}











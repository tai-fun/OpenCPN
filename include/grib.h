/******************************************************************************
 * $Id: grib.h,v 1.3 2009/12/10 21:22:09 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  GRIB Manager Object
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
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <wx/treectrl.h>


#include "dychart.h"
#include "chart1.h"
#include "navutil.h"

#include "GribReader.h"
#include "GribRecord.h"
#include "IsoLine.h"

#define ID_OK                       10001
#define ID_GRIBRECORDREECTRL        10002
#define ID_CHOOSEGRIBDIR            10003


class GRIBFile;
class GRIBRecord;
class GribRecordTree;
class GRIBOverlayFactory;
class GribRecordSet;


WX_DECLARE_OBJARRAY(GribRecordSet, ArrayOfGribRecordSets);
WX_DECLARE_OBJARRAY(GribRecord *, ArrayOfGribRecordPtrs);

class GribRecordSet
{
      public:
            time_t                     m_Reference_Time;
            ArrayOfGribRecordPtrs      m_GribRecordPtrArray;          // all GribRecords at this time
};




typedef enum GribTreeItemType
{
      GRIB_FILE_TYPE,
      GRIB_RECORD_SET_TYPE
};
//----------------------------------------------------------------------------------------------------------
//    GRIB Selector/Control Dialog Specification
//----------------------------------------------------------------------------------------------------------
class GRIBUIDialog: public wxDialog
{
      DECLARE_CLASS( GRIBUIDialog )
                  DECLARE_EVENT_TABLE()
      public:

           GRIBUIDialog( );

            ~GRIBUIDialog( );
            void Init();

            bool Create(  wxWindow *parent, wxWindowID id = wxID_ANY,
                         const wxString& caption = wxT("GRIB Display Control"), const wxString initial_grib_dir = wxT(""),
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxDefaultSize,
                         long style = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU );

           void CreateControls();

           void PopulateTreeControlGRS(GRIBFile *pgribfile, int file_index);
           void SetGribRecordSet(GribRecordSet *pGribRecordSet);// a "notification" from Record Tree control

           void SetCursorLatLon(double lat, double lon);

      private:
            void OnClose(wxCloseEvent& event);
            void OnIdOKClick( wxCommandEvent& event );
            void OnMove( wxMoveEvent& event );
            void OnSize( wxSizeEvent& event );
            void OnChooseDirClick( wxCommandEvent& event );
            void UpdateTrackingControls(void);
            void PopulateTreeControl(void);


            //    Data
            wxFont            *m_dFont;

            GribRecordTree    *m_pRecordTree;
            wxTreeItemId      m_RecordTree_root_id;

            wxTextCtrl        *m_pWindSpeedTextCtrl;
            wxTextCtrl        *m_pWindDirTextCtrl;
            wxTextCtrl        *m_pPressureTextCtrl;
            wxTextCtrl        *m_pSigWHTextCtrl;

            int               m_n_files;

            wxTextCtrl        *m_pitemCurrentGribDirectoryCtrl;
            wxString          m_currentGribDir;
            wxBitmap          *m_pfolder_bitmap;
            GribRecordSet     *m_pCurrentGribRecordSet;

            int               m_sequence_active;

            double            m_cursor_lat, m_cursor_lon;

            int               m_RS_Idx_WIND_VX;             // These are indexes into the m_pCurrentGribRecordSet
            int               m_RS_Idx_WIND_VY;
            int               m_RS_Idx_PRESS;
            int               m_RS_Idx_HTSIGW;


};

//----------------------------------------------------------------------------------------------------------
//    Grib Overlay Factory Specification
//----------------------------------------------------------------------------------------------------------
class GRIBOverlayFactory
{
      public:
            GRIBOverlayFactory();
            ~GRIBOverlayFactory();

            void SetGribRecordSet(GribRecordSet *pGribRecordSet);
            bool RenderGribOverlay( wxMemoryDC *pmdc, ViewPort *vp );

            GribRecordSet           *m_pGribRecordSet;

      private:
            bool RenderGribWind(GribRecord *pGRX, GribRecord *pGRY, wxMemoryDC *pmdc, ViewPort *vp);
            bool RenderGribPressure(GribRecord *pGR, wxMemoryDC *pmdc, ViewPort *vp);
            bool RenderGribSigWh(GribRecord *pGR, wxMemoryDC *pmdc, ViewPort *vp);
            bool RenderGribWvDir(GribRecord *pGR, wxMemoryDC *pmdc, ViewPort *vp);

            void drawWindArrowWithBarbs(wxMemoryDC *pmdc, int x, int y, double vx, double vy, bool south, wxColour arrowColor);
            void drawWaveArrow(wxMemoryDC *pmdc, int i, int j, double dir, wxColour arrowColor);

            wxPoint GetDCPixPoint(ViewPort *vp, double lat, double lon);

            void drawTransformedLine( wxMemoryDC *pmdc, wxPen pen, double si, double co,int di, int dj, int i,int j, int k,int l);

            void drawPetiteBarbule(wxMemoryDC *pmdc, wxPen pen, bool south, double si, double co, int di, int dj, int b);
            void drawGrandeBarbule(wxMemoryDC *pmdc, wxPen pen, bool south, double si, double co, int di, int dj, int b);
            void drawTriangle(wxMemoryDC *pmdc, wxPen pen, bool south, double si, double co, int di, int dj, int b);

            wxColour GetGraphicColor(double val, double val_max);

            double                  m_last_vp_scale;
            wxArrayPtrVoid          m_IsobarArray;

            wxBitmap                *m_pbm_sigwh;

#if wxUSE_GRAPHICS_CONTEXT
            wxGraphicsContext       *m_pgc;
#endif

};



//----------------------------------------------------------------------------------------------------------
//    Grib File/Record selector Tree Control Specification
//----------------------------------------------------------------------------------------------------------

class GribRecordTree: public wxTreeCtrl
{
      DECLARE_CLASS( GribRecordTree )
                  DECLARE_EVENT_TABLE()
      public:
     // Constructors
            GribRecordTree( );
            GribRecordTree( GRIBUIDialog* parent, wxWindowID id = wxID_ANY,
                           const wxPoint& pos = wxDefaultPosition,
                           const wxSize& size = wxDefaultSize,
                           long style = wxTR_HAS_BUTTONS );

            ~GribRecordTree( );

            void Init();

      //  Override events
            void OnItemExpanding( wxTreeEvent& event);
            void OnItemSelectChange( wxTreeEvent& event);

      //    Data
            GRIBUIDialog    *m_parent;
            wxTreeItemId    *m_file_id_array;             // an array of wxTreeItemIDs

};


class GribTreeItemData : public wxTreeItemData
{
      public:
            GribTreeItemData(const GribTreeItemType type);
            ~GribTreeItemData ();


            GribTreeItemType        m_type;

            //    Data for type GRIB_FILE
            wxString                m_file_name;
            GRIBFile                *m_pGribFile;
            int                     m_file_index;

            //    Data for type GRIB_RECORD
            GribRecordSet           *m_pGribRecordSet;

};

//----------------------------------------------------------------------------------------------------------
//    GRIBFile Object Specification
//----------------------------------------------------------------------------------------------------------
class GRIBFile
{
      public:

            GRIBFile(const wxString file_name);
            ~GRIBFile();

            bool IsOK(void){ return m_bOK; }
            wxString GetLastErrorMessage(void){ return m_last_error_message; }
            ArrayOfGribRecordSets *GetRecordSetArrayPtr(void){ return &m_GribRecordSetArray; }


      private:

            bool        m_bOK;
            wxString    m_last_error_message;
            GribReader  *m_pGribReader;

            //    An array of GribRecordSets found in this GRIB file
            ArrayOfGribRecordSets   m_GribRecordSetArray;

            int         m_nGribRecords;

};


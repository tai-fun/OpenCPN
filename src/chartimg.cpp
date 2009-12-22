/******************************************************************************
 * $Id: chartimg.cpp,v 1.36 2009/12/22 22:01:40 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  ChartBase, ChartBaseBSB and Friends
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
 * $Log: chartimg.cpp,v $
 * Revision 1.36  2009/12/22 22:01:40  bdbcat
 * Improve Georef
 *
 * Revision 1.35  2009/12/17 02:49:16  bdbcat
 * Correct IDL again
 *
 * Revision 1.34  2009/12/10 21:10:13  bdbcat
 * Beta 1210
 *
 * Revision 1.33  2009/11/23 04:13:37  bdbcat
 * Various for build 1122
 *
 * Revision 1.32  2009/11/18 01:24:15  bdbcat
 * 1.3.5 Beta 1117
 *
 * Revision 1.31  2009/09/30 02:30:10  bdbcat
 * Another correction for IDL crossing
 *
 * Revision 1.30  2009/09/28 13:19:09  bdbcat
 * Correct for IDL crossing
 *
 * Revision 1.29  2009/09/18 02:13:20  bdbcat
 * Add support for DTM field in BSB charts
 *
 * Revision 1.28  2009/09/11 20:15:16  bdbcat
 * Correct possible stream buffer overrun
 *
 * Revision 1.27  2009/08/03 03:21:38  bdbcat
 * Cleanup for MSVC
 *
 * Revision 1.26  2009/07/16 02:41:53  bdbcat
 * Allow native RGB color scheme
 *
 * Revision 1.25  2009/07/10 03:51:39  bdbcat
 * Change MinScale factor for BSB charts.
 *
 * Revision 1.24  2009/07/03 02:58:10  bdbcat
 * Dorrect "WGS 84" spelling.
 *
 * Revision 1.23  2009/06/28 02:02:08  bdbcat
 * Implement Datum transforms.
 *
 * Revision 1.22  2009/06/25 02:33:02  bdbcat
 * Normalize charts near International Dateline.
 *
 * Revision 1.21  2009/06/17 02:42:45  bdbcat
 * Dummy->No Chart Available
 *
 * Revision 1.20  2009/06/03 03:15:26  bdbcat
 * Add more error log messages.
 *
 * Revision 1.19  2009/03/26 22:28:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.18  2008/12/09 03:49:36  bdbcat
 * Cleanup Comments
 *
 * Revision 1.17  2008/11/02 23:22:05  bdbcat
 * Fix wxDateTime.Set() arguments
 *
 * Revision 1.16  2008/08/26 13:47:11  bdbcat
 * Cleanup
 *
 * Revision 1.15  2008/08/09 23:58:40  bdbcat
 * Numerous revampings....
 *
 * Revision 1.14  2008/04/10 00:58:20  bdbcat
 * Change to opncpnPalette vs Pelette
 *
 * Revision 1.13  2008/03/30 21:56:15  bdbcat
 * Update for Mac OSX/Unicode
 *
 * $Log: chartimg.cpp,v $
 * Revision 1.36  2009/12/22 22:01:40  bdbcat
 * Improve Georef
 *
 * Revision 1.35  2009/12/17 02:49:16  bdbcat
 * Correct IDL again
 *
 * Revision 1.34  2009/12/10 21:10:13  bdbcat
 * Beta 1210
 *
 * Revision 1.33  2009/11/23 04:13:37  bdbcat
 * Various for build 1122
 *
 * Revision 1.32  2009/11/18 01:24:15  bdbcat
 * 1.3.5 Beta 1117
 *
 * Revision 1.31  2009/09/30 02:30:10  bdbcat
 * Another correction for IDL crossing
 *
 * Revision 1.30  2009/09/28 13:19:09  bdbcat
 * Correct for IDL crossing
 *
 * Revision 1.29  2009/09/18 02:13:20  bdbcat
 * Add support for DTM field in BSB charts
 *
 * Revision 1.28  2009/09/11 20:15:16  bdbcat
 * Correct possible stream buffer overrun
 *
 * Revision 1.27  2009/08/03 03:21:38  bdbcat
 * Cleanup for MSVC
 *
 * Revision 1.26  2009/07/16 02:41:53  bdbcat
 * Allow native RGB color scheme
 *
 * Revision 1.25  2009/07/10 03:51:39  bdbcat
 * Change MinScale factor for BSB charts.
 *
 * Revision 1.24  2009/07/03 02:58:10  bdbcat
 * Dorrect "WGS 84" spelling.
 *
 * Revision 1.23  2009/06/28 02:02:08  bdbcat
 * Implement Datum transforms.
 *
 * Revision 1.22  2009/06/25 02:33:02  bdbcat
 * Normalize charts near International Dateline.
 *
 * Revision 1.21  2009/06/17 02:42:45  bdbcat
 * Dummy->No Chart Available
 *
 * Revision 1.20  2009/06/03 03:15:26  bdbcat
 * Add more error log messages.
 *
 * Revision 1.19  2009/03/26 22:28:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.18  2008/12/09 03:49:36  bdbcat
 * Cleanup Comments
 *
 * Revision 1.17  2008/11/02 23:22:05  bdbcat
 * Fix wxDateTime.Set() arguments
 *
 * Revision 1.16  2008/08/26 13:47:11  bdbcat
 * Cleanup
 *
 * Revision 1.15  2008/08/09 23:58:40  bdbcat
 * Numerous revampings....
 *
 * Revision 1.14  2008/04/10 00:58:20  bdbcat
 * Change to opncpnPalette vs Pelette
 *
 * Revision 1.13  2008/03/30 21:56:15  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.12  2008/01/12 06:23:26  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.11  2008/01/10 03:35:57  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.9  2007/06/15 02:45:31  bdbcat
 * Use line cache by default
 *
 * Revision 1.8  2007/06/10 03:49:20  bdbcat
 * Fix background color
 *
 * Revision 1.7  2007/06/10 02:26:16  bdbcat
 * Implement  color scheme capability
 *
 * Revision 1.6  2007/05/03 13:23:55  dsr
 * Major refactor for 1.2.0
 *
 */


// ============================================================================
// declarations
// ============================================================================


// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "wx/dir.h"

#include "chartimg.h"

//  Why are these not in wx/prec.h?
#include "wx/stream.h"
#include "wx/wfstream.h"
#include "wx/tokenzr.h"
#include "wx/filename.h"
#include <wx/image.h>

#include <sys/stat.h>

extern bool             g_b_overzoom_x;                      // Allow high overzoom


// ----------------------------------------------------------------------------
// Random Prototypes
// ----------------------------------------------------------------------------

extern void *x_malloc(size_t t);
extern "C"  double     round_msvc (double flt);


CPL_CVSID("$Id: chartimg.cpp,v 1.36 2009/12/22 22:01:40 bdbcat Exp $");

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------


// ============================================================================
// ThumbData implementation
// ============================================================================

ThumbData::ThumbData()
{
    pDIBThumb = NULL;
}

ThumbData::~ThumbData()
{
    delete pDIBThumb;
}

// ============================================================================
// Palette implementation
// ============================================================================
opncpnPalette::opncpnPalette()
{
    // Index into palette is 1-based, so predefine the first entry as null
    nFwd = 1;
    nRev = 1;
    FwdPalette =(int *)malloc( sizeof(int));
    RevPalette =(int *)malloc( sizeof(int));
    FwdPalette[0] = 0;
    RevPalette[0] = 0;
}

opncpnPalette::~opncpnPalette()
{
    if(NULL != FwdPalette)
        free( FwdPalette );
    if(NULL != RevPalette)
        free( RevPalette ) ;
}

// ============================================================================
// ChartBase implementation
// ============================================================================
ChartBase::ChartBase()
{
      pcached_bitmap = NULL;

      m_depth_unit_id = DEPTH_UNIT_UNKNOWN;

      pThumbData = new ThumbData;

      m_global_color_scheme = GLOBAL_COLOR_SCHEME_DAY;

      bReadyToRender = false;

      Chart_Error_Factor = 0;

      m_Chart_Scale = 10000;              // a benign value

      m_nCOVREntries = 0;
      m_pCOVRTable = NULL;
      m_pCOVRTablePoints = NULL;

      m_EdDate.Set(1, wxDateTime::Jan, 2000);

      m_lon_datum_adjust = 0.;
      m_lat_datum_adjust = 0.;
}

ChartBase::~ChartBase()
{
      if(pcached_bitmap)
             delete pcached_bitmap;

      delete pThumbData;

      //    Free the COVR tables

      for(unsigned int j=0 ; j<(unsigned int)m_nCOVREntries ; j++)
            free( m_pCOVRTable[j] );

      free( m_pCOVRTable );
      free( m_pCOVRTablePoints );

}


// ============================================================================
// ChartDummy implementation
// ============================================================================

ChartDummy::ChartDummy()
{
      m_pBM = NULL;
      m_ChartType = CHART_TYPE_DUMMY;
      m_ChartFamily = CHART_FAMILY_UNKNOWN;


      m_FullPath = _T("No Chart Available");
      m_Description = m_FullPath;

}

ChartDummy::~ChartDummy()
{
      delete m_pBM;
}


InitReturn ChartDummy::Init( const wxString& name, ChartInitFlag init_flags )
{
      return INIT_OK;
}

void ChartDummy::SetColorScheme(ColorScheme cs, bool bApplyImmediate)
{
}


ThumbData *ChartDummy::GetThumbData(int tnx, int tny, float lat, float lon)
{
      return (ThumbData *)NULL;
}

bool ChartDummy::UpdateThumbData(float lat, float lon)
{
      return FALSE;
}


int ChartDummy::GetNativeScale()
{
      return 22000000;
}

wxString ChartDummy::GetPubDate()
{
      return _T("");
}


void ChartDummy::InvalidateCache(void)
{
      delete m_pBM;
      m_pBM = NULL;
}

bool ChartDummy::GetChartExtent(Extent *pext)
{
    pext->NLAT = 80;
    pext->SLAT = -80;
    pext->ELON = 179;
    pext->WLON = -179;

    return true;
}


bool ChartDummy::RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type)
{

      if(!m_pBM)
            m_pBM = new wxBitmap(VPoint.pix_width, VPoint.pix_height);
      dc.SelectObject(*m_pBM);

      dc.SetBackground(*wxBLACK_BRUSH);
      dc.Clear();

      return true;
}


void ChartDummy::SetVPParms(ViewPort *vpt)
{
}

bool ChartDummy::AdjustVP(ViewPort &vp_last, ViewPort &vp_proposed)
{
      return false;
}

bool ChartDummy::IsRenderDelta(ViewPort &vp_last, ViewPort &vp_proposed)
{
      if((vp_last.clat == vp_proposed.clat)  &&
          (vp_last.clon == vp_proposed.clon) &&
          (vp_last.view_scale_ppm == vp_proposed.view_scale_ppm))
            return false;
      else
            return true;
}


void ChartDummy::GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion)
{
      pValidRegion->Clear();
      pValidRegion->Union(0, 0, 1, 1);
}







// ============================================================================
// ChartGEO implementation
// ============================================================================
ChartGEO::ChartGEO()
{
      m_ChartType = CHART_TYPE_GEO;
}


ChartGEO::~ChartGEO()
{
}

InitReturn ChartGEO::Init( const wxString& name, ChartInitFlag init_flags)
{
      #define BUF_LEN_MAX 4000

      PreInit(name, init_flags, GLOBAL_COLOR_SCHEME_DAY);

      char buffer[BUF_LEN_MAX];

      ifs_hdr = new wxFileInputStream(name);          // open the file as a read-only stream

      if(!ifs_hdr->Ok())
            return INIT_FAIL_REMOVE;

      int nPlypoint = 0;
      Plypoint *pPlyTable = (Plypoint *)x_malloc(sizeof(Plypoint));

      m_FullPath = name;
      m_Description = m_FullPath;

      wxFileName GEOFile(m_FullPath);

      wxString Path;
      Path = GEOFile.GetPath(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME);


//    Read the GEO file, extracting useful information

      ifs_hdr->SeekI(0, wxFromStart);                 // rewind

      Size_X = Size_Y = 0;

      while( (ReadBSBHdrLine(ifs_hdr, &buffer[0], BUF_LEN_MAX)) != 0 )
    {
          wxString str_buf(buffer, wxConvUTF8);
            if(!strncmp(buffer, "Bitmap", 6))
            {
                wxStringTokenizer tkz(str_buf, _T("="));
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs(_T("Bitmap"), TRUE))
                  {
                        pBitmapFilePath = new wxString();

                        int i;
                        i = tkz.GetPosition();
                        pBitmapFilePath->Clear();
                        while(buffer[i])
                        {
                              pBitmapFilePath->Append(buffer[i]);
                              i++;
                        }
                  }
            }


            else if(!strncmp(buffer, "Scale", 5))
            {
                wxStringTokenizer tkz(str_buf, _T("="));
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs(_T("Scale"), TRUE))               // extract Scale
                  {
                        int i;
                        i = tkz.GetPosition();
                        m_Chart_Scale = atoi(&buffer[i]);
                  }
            }

            else if(!strncmp(buffer, "Depth", 5))
            {
                wxStringTokenizer tkz(str_buf, _T("="));
                wxString token = tkz.GetNextToken();
                if(token.IsSameAs(_T("Depth Units"), FALSE))               // extract Depth Units
                {
                    int i;
                    i = tkz.GetPosition();
                    wxString str(&buffer[i],  wxConvUTF8);
                    m_DepthUnits = str.Trim();
                }
            }

            else if (!strncmp(buffer, "Point", 5))                // Extract RefPoints
            {
                  int i, xr, yr;
                  float ltr,lnr;
                  sscanf(&buffer[0], "Point%d=%f %f %d %d", &i, &lnr, &ltr, &yr, &xr);
                  pRefTable = (Refpoint *)realloc(pRefTable, sizeof(Refpoint) * (nRefpoint+1));
                  pRefTable[nRefpoint].xr = xr;
                  pRefTable[nRefpoint].yr = yr;
                  pRefTable[nRefpoint].latr = ltr;
                  pRefTable[nRefpoint].lonr = lnr;
                  pRefTable[nRefpoint].bXValid = 1;
                  pRefTable[nRefpoint].bYValid = 1;

                  nRefpoint++;

            }

            else if (!strncmp(buffer, "Vertex", 6))
            {
                  int i;
                  float ltp,lnp;
                  sscanf(buffer, "Vertex%d=%f %f", &i, &ltp, &lnp);
                  pPlyTable = (Plypoint *)realloc(pPlyTable, sizeof(Plypoint) * (nPlypoint+1));
                  pPlyTable[nPlypoint].ltp = ltp;
                  pPlyTable[nPlypoint].lnp = lnp;

                  nPlypoint++;

            }

            else if (!strncmp(buffer, "Date Pub", 8))
            {
                  char date_string[40];
                  char date_buf[10];
                  sscanf(buffer, "Date Published=%s\r\n", &date_string[0]);
                  wxString date_wxstr(date_string,  wxConvUTF8);
                  wxDateTime dt;
                  if(dt.ParseDate(date_wxstr))       // successful parse?
                  {
                        sprintf(date_buf, "%d", dt.GetYear());
                  }
                  else
                  {
                        sscanf(date_string, "%s", date_buf);
                  }
                  m_PubYear = wxString(date_buf, wxConvUTF8);
            }

            else if (!strncmp(buffer, "Skew", 4))
            {
                wxStringTokenizer tkz(str_buf, _T("="));
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs(_T("Skew Angle"), FALSE))               // extract Skew Angle
                  {
                        int i;
                        i = tkz.GetPosition();
                        float fcs;
                        sscanf(&buffer[i], "%f,", &fcs);
                        Chart_Skew = fcs;
                  }
            }

            else if (!strncmp(buffer, "Latitude Offset", 15))
            {
                  wxStringTokenizer tkz(str_buf, _T("="));
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs(_T("Latitude Offset"), FALSE))
                  {
                        int i;
                        i = tkz.GetPosition();
                        float lto;
                        sscanf(&buffer[i], "%f,", &lto);
                        m_dtm_lat = lto;
                  }
            }


            else if (!strncmp(buffer, "Longitude Offset", 16))
            {
                  wxStringTokenizer tkz(str_buf, _T("="));
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs(_T("Longitude Offset"), FALSE))
                  {
                        int i;
                        i = tkz.GetPosition();
                        float lno;
                        sscanf(&buffer[i], "%f,", &lno);
                        m_dtm_lon = lno;
                  }
            }

            else if (!strncmp(buffer, "Datum", 5))
            {
                  wxStringTokenizer tkz(str_buf, _T("="));
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs(_T("Datum"), FALSE))
                  {
                        token = tkz.GetNextToken();
                        m_datum_str = token;
                  }
            }


            else if (!strncmp(buffer, "Name", 4))
            {
                wxStringTokenizer tkz(str_buf, _T("="));
              wxString token = tkz.GetNextToken();
              if(token.IsSameAs(_T("Name"), FALSE))                         // Name
              {
                int i;
                i = tkz.GetPosition();
                m_Name.Clear();
                while(isprint(buffer[i]) && (i < 80))
                      m_Name.Append(buffer[i++]);
               }
            }
      }     //while



//          Extract the remaining data from .NOS Bitmap file
      ifs_bitmap = NULL;

//      Something wrong with the .geo file, there is no Bitmap reference
//      This is where the arbitrarily bad file is caught, such as
//      a file with.GEO extension that is not really a chart

      if(pBitmapFilePath == NULL)
            return INIT_FAIL_REMOVE;

      wxString NOS_Name(*pBitmapFilePath);            // take a copy

      wxDir target_dir(Path);
      wxArrayString file_array;
      int nfiles = wxDir::GetAllFiles(Path, &file_array);
      int ifile;

      pBitmapFilePath->Prepend(Path);

      wxFileName NOS_filename(*pBitmapFilePath);
      if(NOS_filename.FileExists())
      {
            ifss_bitmap = new wxFileInputStream(*pBitmapFilePath); // open the bitmap file
            ifs_bitmap = new wxBufferedInputStream(*ifss_bitmap);
      }
//    File as fetched verbatim from the .geo file doesn't exist.
//    Try all possible upper/lower cases
      else
      {
//    Extract the filename and extension
            wxString fname(NOS_filename.GetName());
            wxString fext(NOS_filename.GetExt());

//    Try all four combinations, the hard way
// case 1
            fname.MakeLower();
            fext.MakeLower();
            NOS_filename.SetName(fname);
            NOS_filename.SetExt(fext);

            if(NOS_filename.FileExists())
                  goto found_uclc_file;

// case 2
            fname.MakeLower();
            fext.MakeUpper();
            NOS_filename.SetName(fname);
            NOS_filename.SetExt(fext);

            if(NOS_filename.FileExists())
                  goto found_uclc_file;

// case 3
            fname.MakeUpper();
            fext.MakeLower();
            NOS_filename.SetName(fname);
            NOS_filename.SetExt(fext);

            if(NOS_filename.FileExists())
                  goto found_uclc_file;

// case 4
            fname.MakeUpper();
            fext.MakeUpper();
            NOS_filename.SetName(fname);
            NOS_filename.SetExt(fext);

            if(NOS_filename.FileExists())
                  goto found_uclc_file;


//      Search harder

            for(ifile = 0 ; ifile < nfiles ; ifile++)
            {
                wxString file_up = file_array.Item(ifile);
                file_up.MakeUpper();

                wxString target_up = *pBitmapFilePath;
                target_up.MakeUpper();

                if(file_up.IsSameAs( target_up))
                {
                    NOS_filename.Clear();
                    NOS_filename.Assign(file_array.Item(ifile));
                    goto found_uclc_file;
                }

            }

            return INIT_FAIL_REMOVE;                  // not found at all

found_uclc_file:

            delete pBitmapFilePath;                   // fix up the member element
            pBitmapFilePath = new wxString(NOS_filename.GetFullPath());
            ifss_bitmap = new wxFileInputStream(*pBitmapFilePath); // open the bitmap file
            ifs_bitmap = new wxBufferedInputStream(*ifss_bitmap);

      }           //else


      if(ifs_bitmap == NULL)
            return INIT_FAIL_REMOVE;

      if(!ifss_bitmap->Ok())
            return INIT_FAIL_REMOVE;


      while( (ReadBSBHdrLine(ifss_bitmap, &buffer[0], BUF_LEN_MAX)) != 0 )
      {
          wxString str_buf(buffer,  wxConvUTF8);

            if(!strncmp(buffer, "NOS", 3))
            {
                wxStringTokenizer tkz(str_buf, _T(",="));
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs(_T("RA"), TRUE))                  // extract RA=x,y
                        {
                              int i;
                              tkz.GetNextToken();
                              tkz.GetNextToken();
                              i = tkz.GetPosition();
                              Size_X = atoi(&buffer[i]);
                              wxString token = tkz.GetNextToken();
                              i = tkz.GetPosition();
                              Size_Y = atoi(&buffer[i]);
                        }
                        else if(token.IsSameAs(_T("DU"), TRUE))                  // extract DU=n
                        {
                            token = tkz.GetNextToken();
                            long temp_du;
                            if(token.ToLong(&temp_du))
                                m_Chart_DU = temp_du;
                        }
                  }

            }

            else if (!strncmp(buffer, "RGB", 3))
                  CreatePaletteEntry(buffer, COLOR_RGB_DEFAULT);

            else if (!strncmp(buffer, "DAY", 3))
                  CreatePaletteEntry(buffer, DAY);

            else if (!strncmp(buffer, "DSK", 3))
                  CreatePaletteEntry(buffer, DUSK);

            else if (!strncmp(buffer, "NGT", 3))
                  CreatePaletteEntry(buffer, NIGHT);

            else if (!strncmp(buffer, "NGR", 3))
                  CreatePaletteEntry(buffer, NIGHTRED);

            else if (!strncmp(buffer, "GRY", 3))
                  CreatePaletteEntry(buffer, GRAY);

            else if (!strncmp(buffer, "PRC", 3))
                  CreatePaletteEntry(buffer, PRC);

            else if (!strncmp(buffer, "PRG", 3))
                  CreatePaletteEntry(buffer, PRG);
      }


//    Validate some of the header data
      if((Size_X == 0) || (Size_Y == 0))
          return INIT_FAIL_REMOVE;

      if(nPlypoint == 0)
          return INIT_FAIL_REMOVE;

//    Convert captured plypoint information into chart COVR structures
      m_nCOVREntries = 1;
      m_pCOVRTablePoints = (int *)malloc(sizeof(int));
      *m_pCOVRTablePoints = nPlypoint;
      m_pCOVRTable = (float **)malloc(sizeof(float *));
      *m_pCOVRTable = (float *)malloc(nPlypoint * 2 * sizeof(float));
      memcpy(*m_pCOVRTable, pPlyTable, nPlypoint * 2 * sizeof(float));

      free(pPlyTable);

      if(!SetMinMax())
            return INIT_FAIL_REMOVE;          // have to bail here

      if(init_flags == HEADER_ONLY)
            return INIT_OK;

//    Advance to the data
      char c;
      if((c = ifs_bitmap->GetC()) != 0x1a){ return INIT_FAIL_REMOVE;}
      if((c = ifs_bitmap->GetC()) == 0x0d)
      {
            if((c = ifs_bitmap->GetC()) != 0x0a){  return INIT_FAIL_REMOVE;}
            if((c = ifs_bitmap->GetC()) != 0x1a){  return INIT_FAIL_REMOVE;}
            if((c = ifs_bitmap->GetC()) != 0x00){  return INIT_FAIL_REMOVE;}
      }

      else if(c != 0x00){  return INIT_FAIL_REMOVE;}

//    Read the Color table bit size
      nColorSize = ifs_bitmap->GetC();


//    Perform common post-init actions in ChartBaseBSB
      InitReturn pi_ret = PostInit();
      if( pi_ret  != INIT_OK)
            return pi_ret;
      else
            return INIT_OK;

}




// ============================================================================
// ChartKAP implementation
// ============================================================================


ChartKAP::ChartKAP()
{
     m_ChartType = CHART_TYPE_KAP;
}


ChartKAP::~ChartKAP()
{
}


InitReturn ChartKAP::Init( const wxString& name, ChartInitFlag init_flags )
{
      #define BUF_LEN_MAX 4000

      int nPlypoint = 0;
      Plypoint *pPlyTable = (Plypoint *)x_malloc(sizeof(Plypoint));

      PreInit(name, init_flags, GLOBAL_COLOR_SCHEME_DAY);

      char buffer[BUF_LEN_MAX];

      ifs_hdr = new wxFileInputStream(name);          // open the Header file as a read-only stream

      if(!ifs_hdr->Ok())
            return INIT_FAIL_REMOVE;

      m_FullPath = name;
      m_Description = m_FullPath;

      ifss_bitmap = new wxFileInputStream(name); // Open again, as the bitmap
      ifs_bitmap = new wxBufferedInputStream(*ifss_bitmap);

      //    Clear georeferencing coefficients
      for(int icl=0 ; icl< 12 ; icl++)
      {
          wpx[icl] = 0;
          wpy[icl] = 0;
          pwx[icl] = 0;
          pwy[icl] = 0;
      }


//    Validate the BSB header
//    by reading some characters into a buffer and looking for BSB\ keyword


      unsigned int TestBlockSize = 1999;
      ifs_hdr->Read(buffer, TestBlockSize);

      if(ifs_hdr->LastRead() != TestBlockSize)
      {
          wxString msg;
          msg.Printf(_T("   Could not read first %d bytes of header for chart file: "), TestBlockSize);
          msg.Append(name);
          wxLogMessage(msg);
            return INIT_FAIL_REMOVE;
      }

      unsigned int i;
      for( i = 0; i < TestBlockSize - 4; i++ )
      {
        //Test for "BSB/"
            if( buffer[i+0] == 'B' && buffer[i+1] == 'S'
                          && buffer[i+2] == 'B' && buffer[i+3] == '/' )
                  break;

        // Test for "NOS/"
            if( buffer[i+0] == 'N' && buffer[i+1] == 'O'
                          && buffer[i+2] == 'S' && buffer[i+3] == '/' )
                  break;

      }
      if( i == TestBlockSize - 4 )
      {
          wxString msg(_T("   Chart file has no BSB header, cannot Init."));
          msg.Append(name);
          wxLogMessage(msg);
            return INIT_FAIL_REMOVE;
      }



//    Read and Parse Chart Header, line by line
      ifs_hdr->SeekI(0, wxFromStart);                                         // rewind

      Size_X = Size_Y = 0;

      int done_header_parse = 0;

      while(done_header_parse == 0)
      {
            if(ReadBSBHdrLine(ifs_hdr, buffer, BUF_LEN_MAX) == 0)
            {
                  unsigned char c;
                  c = ifs_hdr->GetC();
                  ifs_hdr->Ungetch(c);

                  if(0x1a == c)
                      done_header_parse = 1;
                  else
                      return INIT_FAIL_REMOVE;

                  continue;
            }


            wxString str_buf(buffer,  wxConvUTF8);
            wxCSConv iso_conv(wxT("ISO-8859-1"));                 // we will need a converter

            if(!strncmp(buffer, "BSB", 3))
            {
                  wxString clip_str_buf(&buffer[0],  iso_conv);  // for single byte French encodings of NAme field
                  wxStringTokenizer tkz(clip_str_buf, _T("/,="));
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs(_T("RA"), TRUE))                  // extract RA=x,y
                        {
                              int i;
                              i = tkz.GetPosition();
                              Size_X = atoi(&buffer[i]);
                              wxString token = tkz.GetNextToken();
                              i = tkz.GetPosition();
                              Size_Y = atoi(&buffer[i]);
                        }
                        if(token.IsSameAs(_T("NA"), TRUE))                  // extract NA=str
                        {
                          int i = tkz.GetPosition();
                          char nbuf[81];
                          int j=0;
                          while((buffer[i] != ',') && (i < 80))
                                nbuf[j++] = buffer[i++];
                          nbuf[j] = 0;
                          wxString n_str(nbuf,  iso_conv);
                          m_Name = n_str;

                        }
                        if(token.IsSameAs(_T("DU"), TRUE))                  // extract DU=n
                        {
                          token = tkz.GetNextToken();
                          long temp_du;
                          if(token.ToLong(&temp_du))
                                m_Chart_DU = temp_du;
                        }

                  }
            }

            else if(!strncmp(buffer, "KNP", 3))
            {
                wxStringTokenizer tkz(str_buf, _T("/,="));
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs(_T("SC"), TRUE))                  // extract Scale
                        {
                              int i;
                              i = tkz.GetPosition();
                              m_Chart_Scale = atoi(&buffer[i]);
                        }
                        if(token.IsSameAs(_T("SK"), TRUE))                  // extract Skew
                        {
                              int i;
                              i = tkz.GetPosition();
                              float fcs;
                              sscanf(&buffer[i], "%f,", &fcs);
                              Chart_Skew = fcs;
                        }
                        if(token.IsSameAs(_T("UN"), TRUE))                  // extract Depth Units
                        {
                            int i;
                            i = tkz.GetPosition();
                            wxString str(&buffer[i], wxConvUTF8);
                            m_DepthUnits = str.BeforeFirst(',');
                        }
                        if(token.IsSameAs(_T("GD"), TRUE))                  // extract Datum
                        {
                              int i;
                              i = tkz.GetPosition();
                              wxString str(&buffer[i], wxConvUTF8);
                              m_datum_str = str.BeforeFirst(',').Trim();
                        }
                        if(token.IsSameAs(_T("PP"), TRUE))                  // extract Projection Lat
                        {
                              int i;
                              i = tkz.GetPosition();
                              float fcs;
                              sscanf(&buffer[i], "%f,", &fcs);
                              m_proj_lat = fcs;
                        }

                 }
            }


            else if (!strncmp(buffer, "RGB", 3))
                  CreatePaletteEntry(buffer, COLOR_RGB_DEFAULT);

            else if (!strncmp(buffer, "DAY", 3))
                  CreatePaletteEntry(buffer, DAY);

            else if (!strncmp(buffer, "DSK", 3))
                  CreatePaletteEntry(buffer, DUSK);

            else if (!strncmp(buffer, "NGT", 3))
                  CreatePaletteEntry(buffer, NIGHT);

            else if (!strncmp(buffer, "NGR", 3))
                  CreatePaletteEntry(buffer, NIGHTRED);

            else if (!strncmp(buffer, "GRY", 3))
                  CreatePaletteEntry(buffer, GRAY);

            else if (!strncmp(buffer, "PRC", 3))
                  CreatePaletteEntry(buffer, PRC);

            else if (!strncmp(buffer, "PRG", 3))
                  CreatePaletteEntry(buffer, PRG);


            else if (!strncmp(buffer, "REF", 3))
            {
                  int i, xr, yr;
                  float ltr,lnr;
                  sscanf(&buffer[4], "%d,%d,%d,%f,%f", &i, &xr, &yr, &ltr, &lnr);
                  pRefTable = (Refpoint *)realloc(pRefTable, sizeof(Refpoint) * (nRefpoint+1));
                  pRefTable[nRefpoint].xr = xr;
                  pRefTable[nRefpoint].yr = yr;
                  pRefTable[nRefpoint].latr = ltr;
                  pRefTable[nRefpoint].lonr = lnr;
                  pRefTable[nRefpoint].bXValid = 1;
                  pRefTable[nRefpoint].bYValid = 1;

                  nRefpoint++;

            }

            else if (!strncmp(buffer, "WPX", 3))
            {
                int idx = 0;
                double d;
                wxStringTokenizer tkz(str_buf.Mid(4), _T(","));
                wxString token = tkz.GetNextToken();

                if(token.ToLong((long int *)&wpx_type))
                {
                    while ( tkz.HasMoreTokens() && (idx < 12) )
                    {
                        token = tkz.GetNextToken();
                        if(token.ToDouble(&d))
                        {
                            wpx[idx] = d;
                            idx++;
                        }
                    }
                }
                n_wpx = idx;
            }

            else if (!strncmp(buffer, "WPY", 3))
            {
                int idx = 0;
                double d;
                wxStringTokenizer tkz(str_buf.Mid(4), _T(","));
                wxString token = tkz.GetNextToken();

                if(token.ToLong((long int *)&wpy_type))
                {
                    while ( tkz.HasMoreTokens() && (idx < 12) )
                    {
                        token = tkz.GetNextToken();
                        if(token.ToDouble(&d))
                        {
                            wpy[idx] = d;
                            idx++;
                        }
                    }
                }
                n_wpy = idx;
            }

            else if (!strncmp(buffer, "PWX", 3))
            {
                int idx = 0;
                double d;
                wxStringTokenizer tkz(str_buf.Mid(4), _T(","));
                wxString token = tkz.GetNextToken();

                if(token.ToLong((long int *)&pwx_type))
                {
                    while ( tkz.HasMoreTokens() && (idx < 12) )
                    {
                        token = tkz.GetNextToken();
                        if(token.ToDouble(&d))
                        {
                            pwx[idx] = d;
                            idx++;
                        }
                    }
                }
                n_pwx = idx;
            }

            else if (!strncmp(buffer, "PWY", 3))
            {
                int idx = 0;
                double d;
                wxStringTokenizer tkz(str_buf.Mid(4), _T(","));
                wxString token = tkz.GetNextToken();

                if(token.ToLong((long int *)&pwy_type))
                {
                    while ( tkz.HasMoreTokens() && (idx < 12) )
                    {
                        token = tkz.GetNextToken();
                        if(token.ToDouble(&d))
                        {
                            pwy[idx] = d;
                            idx++;
                        }
                    }
                }
                n_pwy = idx;
            }


            else if (!strncmp(buffer, "CPH", 3))
            {
                float float_cph;
                sscanf(&buffer[4], "%f", &float_cph);
                m_cph = float_cph;
            }

            else if (!strncmp(buffer, "DTM", 3))
            {
                  float fdtmlat, fdtmlon;
                  sscanf(&buffer[4], "%f,%f", &fdtmlat, &fdtmlon);
                  m_dtm_lat = fdtmlat;
                  m_dtm_lon = fdtmlon;
            }


            else if (!strncmp(buffer, "PLY", 3))
            {
                  int i;
                  float ltp,lnp;
                  sscanf(&buffer[4], "%d,%f,%f", &i, &ltp, &lnp);
                  pPlyTable = (Plypoint *)realloc(pPlyTable, sizeof(Plypoint) * (nPlypoint+1));
                  pPlyTable[nPlypoint].ltp = ltp;
                  pPlyTable[nPlypoint].lnp = lnp;

                  nPlypoint++;
            }

            else if(!strncmp(buffer, "CED", 3))
            {
                wxStringTokenizer tkz(str_buf, _T("/,="));
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs(_T("ED"), TRUE))                  // extract Edition Date
                        {

                              int i;
                              i = tkz.GetPosition();

                              char date_string[40];
                              char date_buf[10];
                              sscanf(&buffer[i], "%s\r\n", date_string);
                              wxString date_wxstr(date_string,  wxConvUTF8);

                              wxDateTime dt;
                              if(dt.ParseDate(date_wxstr))       // successful parse?
                              {
                                  int iyear = dt.GetYear(); // GetYear() fails on W98, DMC compiler, wx2.8.3
//    BSB charts typically list publish date as xx/yy/zz, we want 19zz.
                                  if(iyear < 100)
                                  {
                                      iyear += 1900;
                                      dt.SetYear(iyear);
                                  }
                                  sprintf(date_buf, "%d", iyear);

                              //    Initialize the wxDateTime menber for Edition Date
                                  m_EdDate = dt;
                              }
                              else
                              {
                                 sscanf(date_string, "%s", date_buf);
                                 m_EdDate.Set(1, wxDateTime::Jan, 2000);                    //Todo this could be smarter
                              }

                              m_PubYear = wxString(date_buf,  wxConvUTF8);
                        }
                  }
            }

      }


      //    If imbedded coefficients are found,
      //    then use the polynomial georeferencing algorithms
      if(n_pwx && n_pwy && n_pwx && n_pwy)
          bHaveImbeddedGeoref = true;



//    Validate some of the header data
      if((Size_X == 0) || (Size_Y == 0))
      {
          return INIT_FAIL_REMOVE;
      }

      if(nPlypoint == 0)
          return INIT_FAIL_REMOVE;


//    Convert captured plypoint information into chart COVR structures
      m_nCOVREntries = 1;
      m_pCOVRTablePoints = (int *)malloc(sizeof(int));
      *m_pCOVRTablePoints = nPlypoint;
      m_pCOVRTable = (float **)malloc(sizeof(float *));
      *m_pCOVRTable = (float *)malloc(nPlypoint * 2 * sizeof(float));
      memcpy(*m_pCOVRTable, pPlyTable, nPlypoint * 2 * sizeof(float));
      free(pPlyTable);


      //    Adjust the PLY points to WGS84 datum
      Plypoint *ppp = (Plypoint *)GetCOVRTableHead(0);
      int cnPlypoint = GetCOVRTablenPoints(0);

      for(int u=0 ; u<cnPlypoint ; u++)
      {
            ppp->lnp += m_dtm_lon / 3600;
            ppp->ltp += m_dtm_lat / 3600;
            ppp++;
      }


      if(!SetMinMax())
            return INIT_FAIL_REMOVE;          // have to bail here

      if(init_flags == HEADER_ONLY)
            return INIT_OK;

//    Advance to the data
      unsigned char c;
      bool bcorrupt = false;

      if((c = ifs_hdr->GetC()) != 0x1a){ bcorrupt = true; }
      if((c = ifs_hdr->GetC()) == 0x0d)
      {
            if((c = ifs_hdr->GetC()) != 0x0a){ bcorrupt = true; }
            if((c = ifs_hdr->GetC()) != 0x1a){ bcorrupt = true; }
            if((c = ifs_hdr->GetC()) != 0x00){ bcorrupt = true; }
      }

      else if(c != 0x00){ bcorrupt = true; }


      if(bcorrupt)
      {
            wxString msg(_T("   Chart File RLL data corrupt on chart "));
            msg.Append(m_FullPath);
            wxLogMessage(msg);

            return INIT_FAIL_REMOVE;
      }


//    Read the Color table bit size
      nColorSize = ifs_hdr->GetC();

      nFileOffsetDataStart = ifs_hdr->TellI();

//    Perform common post-init actions in ChartBaseBSB
      InitReturn pi_ret = PostInit();
      if( pi_ret  != INIT_OK)
            return pi_ret;
      else
            return INIT_OK;
}



// ============================================================================
// ChartBaseBSB implementation
// ============================================================================


ChartBaseBSB::ChartBaseBSB()
{
      //    Init some private data
      m_ChartFamily = CHART_FAMILY_RASTER;

      pBitmapFilePath = NULL;

      pline_table = NULL;
      ifs_buf = NULL;

      cached_image_ok = 0;

      pRefTable = (Refpoint *)x_malloc(sizeof(Refpoint));
      nRefpoint = 0;
      cPoints.status = 0;
      bHaveImbeddedGeoref = false;
      n_wpx = 0;
      n_wpy = 0;
      n_pwx = 0;
      n_pwy = 0;


      bUseLineCache = true;
      Chart_Skew = 0.0;

      pPixCache = NULL;

      pLineCache = NULL;

      m_bilinear_limit = 8;         // bilinear scaling only up to n

      ifs_bitmap = NULL;
      ifss_bitmap = NULL;
      ifs_hdr = NULL;

      for(int i = 0 ; i < N_BSB_COLORS ; i++)
            pPalettes[i] = NULL;

      bGeoErrorSent = false;
      m_Chart_DU = 0;
      m_cph = 0.;

      m_mapped_color_index = COLOR_RGB_DEFAULT;

      m_datum_str = _T("WGS84");                // assume until proven otherwise

      m_dtm_lat = 0.;
      m_dtm_lon = 0.;

      m_bIDLcross = false;


}

ChartBaseBSB::~ChartBaseBSB()
{
//      if(pFullPath)
//            delete pFullPath;

      if(pBitmapFilePath)
            delete pBitmapFilePath;

      if(pline_table)
            free(pline_table);

      if(ifs_buf)
            free(ifs_buf);

      free(pRefTable);
//      free(pPlyTable);

      delete ifs_bitmap;
      delete ifs_hdr;
      delete ifss_bitmap;

      if(cPoints.status)
      {
          free(cPoints.tx );
          free(cPoints.ty );
          free(cPoints.lon );
          free(cPoints.lat );

          free(cPoints.pwx );
          free(cPoints.wpx );
          free(cPoints.pwy );
          free(cPoints.wpy );
      }

//    Free the line cache

      if(pLineCache)
      {
            CachedLine *pt;
            for(int ylc = 0 ; ylc < Size_Y ; ylc++)
            {
                  pt = &pLineCache[ylc];
                  if(pt->pPix)
                        free (pt->pPix);
            }
            free (pLineCache);
      }



      if(pPixCache)
            delete pPixCache;

      for(int i = 0 ; i < N_BSB_COLORS ; i++)
            delete pPalettes[i];

}

//    Report recommended minimum and maximum scale values for which use of this chart is valid

double ChartBaseBSB::GetNormalScaleMin(double canvas_scale_factor)
{
      if(g_b_overzoom_x)
            return (canvas_scale_factor / m_ppm_avg) / 32;         // allow wide range overzoom overscale
      else
            return (canvas_scale_factor / m_ppm_avg) / 2;         // don't suggest too much overscale

}

double ChartBaseBSB::GetNormalScaleMax(double canvas_scale_factor)
{
      return (canvas_scale_factor / m_ppm_avg) * 8.0;        // excessive underscale is slow, and unreadable
}



double ChartBaseBSB::GetClosestValidNaturalScalePPM(double target_scale, double scale_factor_min, double scale_factor_max)
{
      double chart_1x_scale = GetPPM();

      double binary_scale_factor = 1.;



      //    Scaling in....
      if(chart_1x_scale > target_scale)
      {
            double binary_scale_factor_max = 1 / scale_factor_min;

            while(binary_scale_factor < binary_scale_factor_max)
            {
                  if(fabs((chart_1x_scale / binary_scale_factor ) - target_scale) < (target_scale * 0.05))
                        break;
                  if((chart_1x_scale / binary_scale_factor ) < target_scale)
                        break;
                  else
                        binary_scale_factor *= 2.;
            }
      }


      //    Scaling out.....
      else
      {
            int ibsf = 1;
            int isf_max = (int)scale_factor_max;
            while(ibsf < isf_max)
            {
                  if((chart_1x_scale * ibsf ) > target_scale)
                  {
                        if(ibsf > 1)
                              ibsf /= 2;
                        break;
                  }
                  if(fabs((chart_1x_scale * ibsf ) - target_scale) < (target_scale * 0.05))
                        break;
                  else
                        ibsf *= 2;
            }

            binary_scale_factor = 1. / ibsf;
      }

      return  chart_1x_scale / binary_scale_factor;
}



InitReturn ChartBaseBSB::Init( const wxString& name, ChartInitFlag init_flags )
{
      m_global_color_scheme = GLOBAL_COLOR_SCHEME_DAY;
      return INIT_OK;
}

InitReturn ChartBaseBSB::PreInit( const wxString& name, ChartInitFlag init_flags, ColorScheme cs )
{
      m_global_color_scheme = cs;
      return INIT_OK;
}

void ChartBaseBSB::CreatePaletteEntry(char *buffer, int palette_index)
{
    if(palette_index < N_BSB_COLORS)
    {
      if(!pPalettes[palette_index])
            pPalettes[palette_index] = new opncpnPalette;
      opncpnPalette *pp = pPalettes[palette_index];

      pp->FwdPalette = (int *)realloc(pp->FwdPalette, (pp->nFwd + 1) * sizeof(int));
      pp->RevPalette = (int *)realloc(pp->RevPalette, (pp->nRev + 1) * sizeof(int));
      pp->nFwd++;
      pp->nRev++;

      int i;
      int n,r,g,b;
      sscanf(&buffer[4], "%d,%d,%d,%d", &n, &r, &g, &b);

      i=n;

      int fcolor, rcolor;
      fcolor = (b << 16) + (g << 8) + r;
      rcolor = (r << 16) + (g << 8) + b;

      pp->RevPalette[i] = rcolor;
      pp->FwdPalette[i] = fcolor;
    }
}



InitReturn ChartBaseBSB::PostInit(void)
{
     //    Validate the palette array, substituting DEFAULT for missing entries
      for(int i = 0 ; i < N_BSB_COLORS ; i++)
      {
            if(pPalettes[i] == NULL)
            {
                opncpnPalette *pNullSubPal = new opncpnPalette;

                pNullSubPal->nFwd = pPalettes[COLOR_RGB_DEFAULT]->nFwd;        // copy the palette count
                pNullSubPal->nRev = pPalettes[COLOR_RGB_DEFAULT]->nRev;        // copy the palette count
                //  Deep copy the palette rgb tables
                free( pNullSubPal->FwdPalette );
                pNullSubPal->FwdPalette = (int *)malloc(pNullSubPal->nFwd * sizeof(int));
                memcpy(pNullSubPal->FwdPalette, pPalettes[COLOR_RGB_DEFAULT]->FwdPalette, pNullSubPal->nFwd * sizeof(int));

                free( pNullSubPal->RevPalette );
                pNullSubPal->RevPalette = (int *)malloc(pNullSubPal->nRev * sizeof(int));
                memcpy(pNullSubPal->RevPalette, pPalettes[COLOR_RGB_DEFAULT]->RevPalette, pNullSubPal->nRev * sizeof(int));

                pPalettes[i] = pNullSubPal;
            }
      }

      // Establish the palette type and default palette
      palette_direction = GetPaletteDir();

      SetColorScheme(m_global_color_scheme, false);

      //    Allocate memory for ifs file buffering
      ifs_bufsize = Size_X * 4;
      ifs_buf = (unsigned char *)x_malloc(ifs_bufsize);
      if(!ifs_buf)
            return INIT_FAIL_REMOVE;

      ifs_bufend = ifs_buf + ifs_bufsize;
      ifs_lp = ifs_bufend;
      ifs_file_offset = -ifs_bufsize;


      //    Create and load the line offset index table
      pline_table = NULL;
      pline_table = (int *)x_malloc((Size_Y+1) * sizeof(int) );               //Ugly....
      if(!pline_table)
            return INIT_FAIL_REMOVE;

      ifs_bitmap->SeekI((Size_Y+1) * -4, wxFromEnd);                 // go to Beginning of offset table
      pline_table[Size_Y] = ifs_bitmap->TellI();                     // fill in useful last table entry

      int offset;
      for(int ifplt=0 ; ifplt<Size_Y ; ifplt++)
      {
          offset = 0;
          offset += (unsigned char)ifs_bitmap->GetC() * 256 * 256 * 256;
          offset += (unsigned char)ifs_bitmap->GetC() * 256 * 256 ;
          offset += (unsigned char)ifs_bitmap->GetC() * 256 ;
          offset += (unsigned char)ifs_bitmap->GetC();

          pline_table[ifplt] = offset;
      }

      //    Try to validate the line index

      bool bline_index_ok = true;
      m_nLineOffset = 0;

      for(int iplt=0 ; iplt<Size_Y - 1 ; iplt++)
      {
            if( wxInvalidOffset == ifs_bitmap->SeekI(pline_table[iplt], wxFromStart))
            {
                  wxString msg(_T("   Chart File corrupt in PostInit() on chart "));
                  msg.Append(m_FullPath);
                  wxLogMessage(msg);

                  return INIT_FAIL_REMOVE;
            }

            int thisline_size = pline_table[iplt+1] - pline_table[iplt] ;

            if(thisline_size < 0)
            {
                  wxString msg(_T("   Chart File corrupt in PostInit() on chart "));
                  msg.Append(m_FullPath);
                  wxLogMessage(msg);

                  return INIT_FAIL_REMOVE;
            }

            if(thisline_size > ifs_bufsize)
            {
                  wxString msg(_T("   ifs_bufsize too small PostInit() on chart "));
                  msg.Append(m_FullPath);
                  wxLogMessage(msg);

                  return INIT_FAIL_REMOVE;
            }

            ifs_bitmap->Read(ifs_buf, thisline_size);

            unsigned char *lp = ifs_buf;

            unsigned char byNext;
            int nLineMarker = 0;
            do
            {
                  byNext = *lp++;
                  nLineMarker = nLineMarker * 128 + (byNext & 0x7f);
            } while( (byNext & 0x80) != 0 );

            //  Linemarker Correction factor needed here
            //  Some charts start with LineMarker = 0, some with LineMarker = 1
            //  Assume the first LineMarker found is the index base, and use
            //  as a correction offset

            if(iplt == 0)
                m_nLineOffset = nLineMarker;

            if(nLineMarker != iplt + m_nLineOffset)
            {
                bline_index_ok = false;
                break;
            }

      }

        // Recreate the scan line index if the imbedded version seems corrupt
      if(!bline_index_ok)
      {
          wxString msg(_T("   Line Index corrupt, recreating Index for chart "));
          msg.Append(m_FullPath);
          wxLogMessage(msg);
          if(!CreateLineIndex())
          {
                wxString msg(_T("   Error creating Line Index for chart "));
                msg.Append(m_FullPath);
                wxLogMessage(msg);
                return INIT_FAIL_REMOVE;
          }
      }



      //    Allocate the Line Cache
      if(bUseLineCache)
      {
            pLineCache = (CachedLine *)x_malloc(Size_Y * sizeof(CachedLine));
            CachedLine *pt;

            for(int ylc = 0 ; ylc < Size_Y ; ylc++)
            {
                  pt = &pLineCache[ylc];
                  pt->bValid = false;
                  pt->xstart = 0;
                  pt->xlength = 1;
                  pt->pPix = NULL;        //(unsigned char *)malloc(1);
            }
      }
      else
            pLineCache = NULL;


      //    Validate/Set Depth Unit Type
      wxString test_str = m_DepthUnits.Upper();
      if(test_str.IsSameAs(_T("FEET"), FALSE))
          m_depth_unit_id = DEPTH_UNIT_FEET;
      else if(test_str.IsSameAs(_T("METERS"), FALSE))
          m_depth_unit_id = DEPTH_UNIT_METERS;
      else if(test_str.IsSameAs(_T("METRES"), FALSE))                  // Special case for alternate spelling
          m_depth_unit_id = DEPTH_UNIT_METERS;
      else if(test_str.IsSameAs(_T("FATHOMS"), FALSE))
          m_depth_unit_id = DEPTH_UNIT_FATHOMS;
      else if(test_str.Find(_T("FATHOMS")) != wxNOT_FOUND)             // Special case for "Fathoms and Feet"
          m_depth_unit_id = DEPTH_UNIT_FATHOMS;


      //   Analyze Refpoints
      int analyze_ret_val = AnalyzeRefpoints();
      if(0 != analyze_ret_val)
            return INIT_FAIL_REMOVE;

      //    Setup the datum transform parameters
      char d_str[100];
      strncpy(d_str, m_datum_str.mb_str(), 99);
      d_str[99] = 0;

      m_datum_index = GetDatumIndex(d_str);

      //    Establish defaults, may be overridden later
      m_lon_datum_adjust = (-m_dtm_lon) / 3600.;
      m_lat_datum_adjust = (-m_dtm_lat) / 3600.;

      bReadyToRender = true;
      return INIT_OK;
}


bool ChartBaseBSB::CreateLineIndex()
{
    //  Assumes file stream ifs_bitmap is currently open

//    wxBufferedInputStream *pbis = new wxBufferedInputStream(*ifss_bitmap);

    //  Seek to start of data
    ifs_bitmap->SeekI(nFileOffsetDataStart);                 // go to Beginning of data

    for(int iplt=0 ; iplt<Size_Y ; iplt++)
    {
        int offset = ifs_bitmap->TellI();

        int iscan;
        iscan = BSBScanScanline(ifs_bitmap);

        if(iscan > Size_Y)
        {
            wxString msg(_T("CreateLineIndex() failed on chart "));
            msg.Append(m_FullPath);
            wxLogMessage(msg);
           return false;
        }

        //  Skipped lines?
        if(iscan != iplt)
        {
            while((iplt < iscan) && (iplt < Size_Y))
            {
                pline_table[iplt] = 0;
                iplt++;
            }
        }

        pline_table[iplt] = offset;

    }

    return true;
}


//    Invalidate and Free the line cache contents
void ChartBaseBSB::InvalidateLineCache(void)
{
      if(pLineCache)
      {
            CachedLine *pt;
            for(int ylc = 0 ; ylc < Size_Y ; ylc++)
            {
                  pt = &pLineCache[ylc];
                  if(pt)
                  {
                        if(pt->pPix)
                        {
                              free (pt->pPix);
                              pt->pPix = NULL;
                        }
                        pt->bValid = 0;
                  }
            }
      }
}

bool ChartBaseBSB::GetChartExtent(Extent *pext)
{
      pext->NLAT = m_LatMax;
      pext->SLAT = m_LatMin;
      pext->ELON = m_LonMax;
      pext->WLON = m_LonMin;

      return true;
}


bool ChartBaseBSB::SetMinMax(void)
{
      //    Calculate the Chart Extents(M_LatMin, M_LonMin, etc.)
      //     from the COVR data, for fast database search
      m_LonMax = -360.0;
      m_LonMin = 360.0;
      m_LatMax = -90.0;
      m_LatMin = 90.0;

      Plypoint *ppp = (Plypoint *)GetCOVRTableHead(0);
      int cnPlypoint = GetCOVRTablenPoints(0);

      for(int u=0 ; u<cnPlypoint ; u++)
      {
            if(ppp->lnp > m_LonMax)
                  m_LonMax = ppp->lnp;
            if(ppp->lnp < m_LonMin)
                  m_LonMin = ppp->lnp;

            if(ppp->ltp > m_LatMax)
                  m_LatMax = ppp->ltp;
            if(ppp->ltp < m_LatMin)
                  m_LatMin = ppp->ltp;

            ppp++;
      }

      //    Check for special cases

      //    Case 1:  Chart spans International Date Line or Greenwich, Longitude min/max is non-obvious.
      if((m_LonMax * m_LonMin) < 0)              // min/max are opposite signs
      {
            //    Georeferencing is not yet available, so find the reference points closest to min/max ply points

            if(0 == nRefpoint)
                  return false;        // have to bail here

                  //    for m_LonMax
            double min_dist_x = 360;
            int imaxclose;
            for(int ic=0 ; ic<nRefpoint ; ic++)
            {
                  double dist = sqrt(((m_LatMax - pRefTable[ic].latr) * (m_LatMax - pRefTable[ic].latr))
                                    + ((m_LonMax - pRefTable[ic].lonr) * (m_LonMax - pRefTable[ic].lonr)));

                  if(dist < min_dist_x)
                  {
                        min_dist_x = dist;
                        imaxclose = ic;
                  }
            }

                  //    for m_LonMin
            double min_dist_n = 360;
            int iminclose;
            for(int id=0 ; id<nRefpoint ; id++)
            {
                  double dist = sqrt(((m_LatMin - pRefTable[id].latr) * (m_LatMin - pRefTable[id].latr))
                                    + ((m_LonMin - pRefTable[id].lonr) * (m_LonMin - pRefTable[id].lonr)));

                  if(dist < min_dist_n)
                  {
                        min_dist_n = dist;
                        iminclose = id;
                  }
            }

            //    Is this chart crossing IDL or Greenwich?
            // Make the check
            if(pRefTable[imaxclose].xr < pRefTable[iminclose].xr)
            {
                  //    This chart crosses IDL and needs a flip, meaning that all negative longitudes need to be normalized
                  //    and the min/max relcalculated
                  //    This code added to correct non-rectangular charts crossing IDL, such as nz14605.kap

                  m_LonMax = -360.0;
                  m_LonMin = 360.0;
                  m_LatMax = -90.0;
                  m_LatMin = 90.0;


                  Plypoint *ppp = (Plypoint *)GetCOVRTableHead(0);      // Normalize the plypoints
                  int cnPlypoint = GetCOVRTablenPoints(0);


                  for(int u=0 ; u<cnPlypoint ; u++)
                  {
                        if( ppp->lnp < 0.)
                              ppp->lnp += 360.;

                        if(ppp->lnp > m_LonMax)
                              m_LonMax = ppp->lnp;
                        if(ppp->lnp < m_LonMin)
                              m_LonMin = ppp->lnp;

                        if(ppp->ltp > m_LatMax)
                              m_LatMax = ppp->ltp;
                        if(ppp->ltp < m_LatMin)
                              m_LatMin = ppp->ltp;

                        ppp++;
                  }
            }

/*          Removed in favor of above algorithm
         if(pRefTable[imaxclose].xr < pRefTable[iminclose].xr)
         {
                  float t_lonmin = m_LonMin;
                  m_LonMin = m_LonMax;
                  m_LonMax = t_lonmin;
         }


            //  Now need to normalize the LonMax, and the plypoints table.
            if(m_LonMin > m_LonMax)
            {
                  m_LonMax += 360.;
                  Plypoint *ppp = (Plypoint *)GetCOVRTableHead(0);      // Normalize the plypoints
                  int cnPlypoint = GetCOVRTablenPoints(0);

                  for(int u=0 ; u<cnPlypoint ; u++)
                  {
                        if( m_LonMin > ppp->lnp)
                              ppp->lnp += 360.;
                        ppp++;
                  }
            }
*/

      }

      // Case 2 Lons are both < -180, which means the extent will be reported incorrectly
      // and the plypoint structure will be wrong
      // This case is seen first on 81004_1.KAP, (Mariannas)

      if((m_LonMax < -180.) && (m_LonMin < -180.))
      {
            m_LonMin += 360.;               // Normalize the extents
            m_LonMax += 360.;

            Plypoint *ppp = (Plypoint *)GetCOVRTableHead(0);      // Normalize the plypoints
            int cnPlypoint = GetCOVRTablenPoints(0);

            for(int u=0 ; u<cnPlypoint ; u++)
            {
                  ppp->lnp += 360.;
                  ppp++;
            }
      }

      return true;
}

void ChartBaseBSB::SetColorScheme(ColorScheme cs, bool bApplyImmediate)
{
    //  Here we convert (subjectively) the Global ColorScheme
    //  to an appropriate BSB_Color_Capability index.

    switch(cs)
    {
        case GLOBAL_COLOR_SCHEME_RGB:
            m_mapped_color_index = COLOR_RGB_DEFAULT;
            break;
        case GLOBAL_COLOR_SCHEME_DAY:
            m_mapped_color_index = DAY;
            break;
        case GLOBAL_COLOR_SCHEME_DUSK:
            m_mapped_color_index = DUSK;
            break;
        case GLOBAL_COLOR_SCHEME_NIGHT:
            m_mapped_color_index = NIGHT;
            break;
        default:
            m_mapped_color_index = DAY;
            break;
    }

    pPalette = GetPalettePtr(m_mapped_color_index);

    m_global_color_scheme = cs;

    if(bApplyImmediate)
        cached_image_ok = false;

    //      Force a new thumbnail
    if(pThumbData)
          pThumbData->pDIBThumb = NULL;
}


wxBitmap *ChartBaseBSB::CreateThumbnail(int tnx, int tny, ColorScheme cs)
{

//    Calculate the size and divisors

      int divx = Size_X / tnx;
      int divy = Size_Y / tny;

      int div_factor = __min(divx, divy);

      int des_width = Size_X / div_factor;
      int des_height = Size_Y / div_factor;

      wxRect gts;
      gts.x = 0;                                // full chart
      gts.y = 0;
      gts.width = Size_X;
      gts.height = Size_Y;

      int this_bpp = 24;                       // for wxImage
//    Allocate the pixel storage needed for one line of chart bits
      unsigned char *pLineT = (unsigned char *)x_malloc((Size_X+1) * BPP/8);


//    Scale the data quickly
      unsigned char *pPixTN = (unsigned char *)x_malloc(des_width * des_height * this_bpp/8 );

      int ix = 0;
      int iy = 0;
      int iyd = 0;
      int ixd = 0;
      int yoffd;
      unsigned char *pxs;
      unsigned char *pxd;

      //    Temporarily set the color scheme
      ColorScheme cs_tmp = m_global_color_scheme;
      SetColorScheme(cs, false);


      while(iyd < des_height)
      {
            if(0 == BSBGetScanline( pLineT, iy, 0, Size_X, 1))          // get a line
            {
                  free(pLineT);
                  free(pPixTN);
                  return NULL;
            }


            yoffd = iyd * des_width * this_bpp/8;                 // destination y

            ix = 0;
            ixd = 0;
            while(ixd < des_width )
            {
                  pxs = pLineT + (ix * BPP/8);
                  pxd = pPixTN + (yoffd + (ixd * this_bpp/8));
                  *pxd++ = *pxs++;
                  *pxd++ = *pxs++;
                  *pxd = *pxs;

                  ix += div_factor;
                  ixd++;

            }

            iy += div_factor;
            iyd++;
      }

      free(pLineT);

      //    Reset ColorScheme
      SetColorScheme(cs_tmp, false);



      wxBitmap *retBMP;

#ifdef ocpnUSE_ocpnBitmap
      retBMP = new ocpnBitmap(pPixTN, des_width, des_height, -1);
#else
      wxImage thumb_image(des_width, des_height, pPixTN, true);
      retBMP = new wxBitmap(thumb_image);
#endif


      free(pPixTN);

      return retBMP;

}


//-------------------------------------------------------------------------------------------------
//          Get the Chart thumbnail data structure
//          Creating the thumbnail bitmap as required
//-------------------------------------------------------------------------------------------------

ThumbData *ChartBaseBSB::GetThumbData(int tnx, int tny, float lat, float lon)
{
//    Create the bitmap if needed
      if(!pThumbData->pDIBThumb)
            pThumbData->pDIBThumb = CreateThumbnail(tnx, tny, m_global_color_scheme);


      pThumbData->Thumb_Size_X = tnx;
      pThumbData->Thumb_Size_Y = tny;

//    Plot the supplied Lat/Lon on the thumbnail
      int divx = Size_X / tnx;
      int divy = Size_Y / tny;

      int div_factor = __min(divx, divy);

      int pixx, pixy;

      latlong_to_pix(lat, lon, pixx, pixy);

      pThumbData->ShipX = pixx / div_factor;
      pThumbData->ShipY = pixy / div_factor;


      return pThumbData;
}

bool ChartBaseBSB::UpdateThumbData(float lat, float lon)
{
//    Plot the supplied Lat/Lon on the thumbnail
//  Return TRUE if the pixel location of ownship has changed

    int divx = Size_X / pThumbData->Thumb_Size_X;
    int divy = Size_Y / pThumbData->Thumb_Size_Y;

    int div_factor = __min(divx, divy);

    int pixx, pixy, pixx_test, pixy_test;

    latlong_to_pix(lat, lon, pixx, pixy);
    pixx_test = pixx / div_factor;
    pixy_test = pixy / div_factor;

    if((pixx_test != pThumbData->ShipX) || (pixy_test != pThumbData->ShipY))
    {
        pThumbData->ShipX = pixx_test;
        pThumbData->ShipY = pixy_test;
        return TRUE;
    }
    else
        return FALSE;
}


bool ChartBaseBSB::RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type)
{
      bool bnewview;
//    Get the view into the pixel buffer
      wxRect dest(0,0,VPoint.pix_width, VPoint.pix_height);
      bnewview = GetViewUsingCache(Rsrc, dest, scale_type);


      //    It could happen that this is the first render of this chart,
      //    .AND. scale_type is bi-linear
      //    .AND.  the render is interrupted by mouse movement.
      //    In this case, there is will be no pPixCache yet....

      //    So, force a subsample render which cannot be interrupted

      if(pPixCache == NULL)
            bnewview = GetViewUsingCache(Rsrc, dest, SCALE_SUBSAMP);

//    Select the data into the dc
      pPixCache->SelectIntoDC(dc);

      return bnewview;
}







//-----------------------------------------------------------------------
//          Pixel to Lat/Long Conversion helpers
//-----------------------------------------------------------------------
static double polytrans( double* coeff, double lon, double lat );

int ChartBaseBSB::pix_to_latlong(int pixx, int pixy, double *plat, double *plon)
{
//      printf("pixtolatlon %d         %d %d\n", pixx, pixy, pixy+Rsrc.y);
    if(bUseGeoRef)
    {
        if(bHaveImbeddedGeoref)
        {
            double lon = polytrans( pwx, pixx, pixy );
            lon = (lon < 0) ? lon + m_cph : lon - m_cph;
            *plon = lon - m_lon_datum_adjust;
            *plat = polytrans( pwy, pixx, pixy ) - m_lat_datum_adjust;

        }
        else                                            // use calculated coefficients
        {
            double lon = polytrans( cPoints.pwx, pixx, pixy );
            lon = (lon < 0) ? lon + m_cph : lon - m_cph;
            *plon = lon - m_lon_datum_adjust;
            *plat = polytrans( cPoints.pwy, pixx, pixy ) - m_lat_datum_adjust;

        }
        return 0;
    }
    else
        return 1;                   // report upstream as error
}

int ChartBaseBSB::vp_pix_to_latlong(ViewPort& vp, int pixx, int pixy, double *plat, double *plon)
{
      if(bUseGeoRef)
      {
      // be careful changing this to double, test it......
            float raster_scale = GetPPM() / vp.view_scale_ppm;

            return(pix_to_latlong((int)(pixx*raster_scale) + Rsrc.x, (int)(pixy*raster_scale) + Rsrc.y, plat, plon));
      }
      else
      {
                           // Use a Mercator estimator, with Eccentricity corrrection applied
            int dx = pixx - ( vp.pix_width  / 2 );
            int dy = ( vp.pix_height / 2 ) - pixy;

            double xp = ( dx * cos ( vp.skew ) ) - ( dy * sin ( vp.skew ) );
            double yp = ( dy * cos ( vp.skew ) ) + ( dx * sin ( vp.skew ) );

            double d_east = xp / vp.view_scale_ppm;
            double d_north = yp / vp.view_scale_ppm;

            double slat, slon;
            if(0)
                  fromSM ( d_east, d_north, vp.clat, vp.clon, &slat, &slon );
            else
                  fromSM_ECC ( d_east, d_north, vp.clat, vp.clon, &slat, &slon );

            *plat = slat;

            if(slon < -180.)
                  slon += 360.;
            else if(slon > 180.)
                  slon -= 360.;
            *plon = slon;

            return 0;
      }

}




int ChartBaseBSB::latlong_to_pix(double lat, double lon, int &pixx, int &pixy)
{
      double alat, alon;

      alon = lon + m_lon_datum_adjust;
      alat = lat + m_lat_datum_adjust;

      if(m_bIDLcross)
      {
            if(alon < 0.)
                  alon += 360.;
      }

    if(bUseGeoRef)
    {
        if(bHaveImbeddedGeoref)
        {
            /* change longitude phase (CPH) */
            double lonp = (alon < 0) ? alon + m_cph : alon - m_cph;
            double xd = polytrans( wpx, lonp, alat );
            double yd = polytrans( wpy, lonp, alat );
            pixx = (int)(xd + 0.5);
            pixy = (int)(yd + 0.5);

        }
        else                                            // use calculated coefficients
        {
            /* change longitude phase (CPH) */
            double lonp = (alon < 0) ? alon + m_cph : alon - m_cph;
            double xd = polytrans( cPoints.wpx, lonp, alat );
            double yd = polytrans( cPoints.wpy, lonp, alat );
            pixx = (int)(xd + 0.5);
            pixy = (int)(yd + 0.5);
        }

        return 0;
    }
    else
        return 1;                   // report upstream as error
}


int ChartBaseBSB::latlong_to_pix_vp(double lat, double lon, int &pixx, int &pixy, ViewPort& vp)
{
    int px, py;

    if(bUseGeoRef)
    {
            latlong_to_pix(lat, lon, px, py);

      // be careful changing this to double, test it......
            float raster_scale = GetPPM() / vp.view_scale_ppm;

            pixx = (int)(((px - Rsrc.x) / raster_scale) + 0.5);
            pixy = (int)(((py - Rsrc.y) / raster_scale) + 0.5);

            return 0;
    }
    else                      // Use a Mercator estimator, with Eccentricity corrrection applied
    {
                double easting, northing;
                double xlon = lon;

                //  Make sure lon and lon0 are same phase
                if(xlon * vp.clon < 0.)
                {
                      if(xlon < 0.)
                            xlon += 360.;
                      else
                            xlon -= 360.;
                }

                if(fabs(xlon - vp.clon) > 180.)
                {
                      if(xlon > vp.clon)
                            xlon -= 360.;
                      else
                            xlon += 360.;
                }

                toSM_ECC(lat, xlon, vp.clat, vp.clon, &easting, &northing);

                double epix = easting  * vp.view_scale_ppm;
                double npix = northing * vp.view_scale_ppm;

                double dx = epix * cos ( vp.skew ) + npix * sin ( vp.skew );
                double dy = npix * cos ( vp.skew ) - epix * sin ( vp.skew );

                pixx = ( int ) /*rint*/( ( vp.pix_width  / 2 ) + dx );
                pixy = ( int ) /*rint*/( ( vp.pix_height / 2 ) - dy );

                return 0;
    }
}

void ChartBaseBSB::ComputeSourceRectangle(ViewPort &vp, wxRect *pSourceRect)
{

    int pixxd, pixyd;

    //      This funny contortion is necessary to allow scale factors < 1, i.e. overzoom
    double binary_scale_factor = (round(100000 * GetPPM() / vp.view_scale_ppm)) / 100000.;

//    printf(" in ComputeSourceRect bsf %g  1_over_bsf %g\n", binary_scale_factor, 1./binary_scale_factor);

    m_raster_scale_factor = binary_scale_factor;

    if(!latlong_to_pix(vp.clat, vp.clon, pixxd, pixyd))
    {
          pSourceRect->x = pixxd - (int)(vp.pix_width  * binary_scale_factor / 2);
          pSourceRect->y = pixyd - (int)(vp.pix_height * binary_scale_factor / 2);

          pSourceRect->width =  (int)ceil(vp.pix_width  * binary_scale_factor) ;
          pSourceRect->height = (int)ceil(vp.pix_height * binary_scale_factor) ;
    }

    else
    {
                //  Internal Georeferencing on this chart has been declared bad, so
                //  use a Mercator estimator with eccentricity correction to get started
        double e_est, n_est;
        double alat, alon;

        alon =  pRefTable[m_i_ref_near_center].lonr - m_lon_datum_adjust;
        alat =  pRefTable[m_i_ref_near_center].latr - m_lat_datum_adjust;

        if(0)
            toSM(vp.clat, vp.clon, pRefTable[m_i_ref_near_center].latr, pRefTable[m_i_ref_near_center].lonr, &e_est, &n_est);
        else
            toSM_ECC(vp.clat, vp.clon, alat, alon, &e_est, &n_est);

        int dx = (int)/*rint*/(e_est * m_ppm_avg);
        int dy = (int)/*rint*/(n_est * m_ppm_avg);

        int pixxe = (int)(pRefTable[m_i_ref_near_center].xr) + dx;
        int pixye = (int)(pRefTable[m_i_ref_near_center].yr) - dy;

        pSourceRect->x = pixxe - (int)(vp.pix_width  * binary_scale_factor / 2);
        pSourceRect->y = pixye - (int)(vp.pix_height * binary_scale_factor / 2);

        pSourceRect->width =  (int)(vp.pix_width  * binary_scale_factor) ;
        pSourceRect->height = (int)(vp.pix_height * binary_scale_factor) ;
    }
}


void ChartBaseBSB::SetVPParms(ViewPort *vpt)
{
      //    Calculate the potential datum offset parameters for this viewport, if not WGS84

      if(m_datum_index == DATUM_INDEX_WGS84)
      {
            m_lon_datum_adjust = 0.;
            m_lat_datum_adjust = 0.;
      }

      else if(m_datum_index == DATUM_INDEX_UNKNOWN)
      {
            m_lon_datum_adjust = (-m_dtm_lon) / 3600.;
            m_lat_datum_adjust = (-m_dtm_lat) / 3600.;
      }

      else
      {
            double to_lat, to_lon;
            MolodenskyTransform (vpt->clat, vpt->clon, &to_lat, &to_lon, m_datum_index, DATUM_INDEX_WGS84);
            m_lon_datum_adjust = -(to_lon - vpt->clon);
            m_lat_datum_adjust = -(to_lat - vpt->clat);

      }

      ComputeSourceRectangle(*vpt, &Rsrc);
}

bool ChartBaseBSB::AdjustVP(ViewPort &vp_last, ViewPort &vp_proposed)
{
      bool ret_val = false;

                        //  Calculate binary scale factor
                        //  n.b.  parameter "scale_ppm" is always contrived to be binary multiple of native scale
                        //        in pixels per meter when this method is called for raster charts.
                        //        Phasing: (binary_scale_factor = 2.0) means zoom OUT.
                        //                  (binary_scale_factor < 1) means overzoom

      double binary_scale_factor = ( round ( 100000 * GetPPM() / vp_proposed.view_scale_ppm ) ) / 100000.;

      int pixxd, pixyd;
      int pixx, pixy;

      //    Require the ViewPort to specify a lat/lon such that the center point falls on an exact 4 pixel
      //    boundary with respect to the native chart pixels.  This simplifies the arithmetic elsewhere....

     //  If internal georeferencing on this chart is OK.......
      if ( !latlong_to_pix ( vp_proposed.clat, vp_proposed.clon, pixxd, pixyd ) )
      {
            pixx = pixxd;
            pixy = pixyd;


            int xmod = ( pixx - ( int ) ( vp_proposed.pix_width  * binary_scale_factor / 2 ) ) /4;
            xmod *= 4;
            int newx = xmod;

            int ymod = ( pixy - ( int ) ( vp_proposed.pix_height * binary_scale_factor / 2 ) ) /4;
            ymod *= 4;
            int newy = ymod;

            SetVPParms ( &vp_proposed );     // preset here for next adjustment

            //    Possible adjustment to clat/clon
            double alat, alon;
            pix_to_latlong ( ( int ) ( ( ( vp_proposed.pix_width /2 ) * binary_scale_factor ) + newx ),
                               ( int ) ( ( ( vp_proposed.pix_height/2 ) * binary_scale_factor ) + newy ),
                                             &alat, &alon );
            vp_proposed.clat = alat;
            vp_proposed.clon = alon;

            ret_val = true;
      }
      else
      {
            if(vp_last.bValid)
            {
                  latlong_to_pix_vp(vp_proposed.clat, vp_proposed.clon, pixxd, pixyd, vp_last);
                  pixx = pixxd;
                  pixy = pixyd;


                  int xmod = ( pixx - ( int ) ( vp_proposed.pix_width  * binary_scale_factor / 2 ) ) /4;
                  xmod *= 4;
                  int newx = xmod;

                  int ymod = ( pixy - ( int ) ( vp_proposed.pix_height * binary_scale_factor / 2 ) ) /4;
                  ymod *= 4;
                  int newy = ymod;

                  SetVPParms ( &vp_proposed );     // preset here for next adjustment

                  //    Possible adjustment to clat/clon
                  double alat, alon;
                  vp_pix_to_latlong(vp_last, ( int ) ( ( ( vp_proposed.pix_width /2 ) * binary_scale_factor ) + newx ),
                                    ( int ) ( ( ( vp_proposed.pix_height/2 ) * binary_scale_factor ) + newy ),
                                                &alat, &alon );

                  //    Do not adjust the proposed latitude,
                  //    since charts without internal georef have poor ypixel/lat registration typically
      //            vp_proposed.clat = alat;
                  vp_proposed.clon = alon;

                  ret_val = true;
            }
      }

      return ret_val;
}

bool ChartBaseBSB::IsRenderDelta(ViewPort &vp_last, ViewPort &vp_proposed)
{
      wxRect rlast, rthis;

      ComputeSourceRectangle(vp_last, &rlast);
      ComputeSourceRectangle(vp_proposed, &rthis);

      return ((rlast != rthis) || !(IsCacheValid()));
}

void ChartBaseBSB::GetSourceRect(wxRect *rect)
{
    *rect = Rsrc;
}


void ChartBaseBSB::GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion)
{
//      float raster_scale = 1.0 / VPoint.binary_scale_factor;
      float raster_scale =  VPoint.view_scale_ppm / GetPPM();

      int rxl, rxr;
      if(Rsrc.x < 0)
            rxl = (int)(-Rsrc.x * raster_scale);
      else
            rxl = 0;

      if(((Size_X - Rsrc.x) * raster_scale) < VPoint.pix_width)
            rxr = (int)((Size_X - Rsrc.x) * raster_scale);
      else
            rxr = VPoint.pix_width;

      int ryb, ryt;
      if(Rsrc.y < 0)
            ryt = (int)(-Rsrc.y * raster_scale);
      else
            ryt = 0;

      if(((Size_Y - Rsrc.y) * raster_scale) < VPoint.pix_height)
            ryb = (int)((Size_Y - Rsrc.y) * raster_scale);
      else
            ryb = VPoint.pix_height;

      pValidRegion->Clear();
      pValidRegion->Union(rxl, ryt, rxr - rxl, ryb - ryt);
}







bool ChartBaseBSB::GetViewUsingCache( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type )
{
      wxRect s1;
      unsigned char *pCP;
      unsigned char *pPix;
      ScaleTypeEnum scale_type_corrected;
      int xsoff, ysoff;


//    Anything to do?
      if((source == cache_rect) && (cache_scale_method == scale_type) && (cached_image_ok))
            return false;

//    Calculate the digital scale, e.g. 1,2,4,8,,,
      int cs1 = source.width/dest.width;

//    Enforce a limit on bilinear scaling, for performance reasons

      scale_type_corrected = scale_type;
      if(cs1 > m_bilinear_limit)
            scale_type_corrected = SCALE_SUBSAMP;


//    Here is the special case for rescaling to bilinear, only
//     reached after the rescale timer expires in ChartCanvas
      if(cached_image_ok)
      {
            if((cache_scale_method == SCALE_SUBSAMP) &&
                  (scale_type_corrected == SCALE_BILINEAR))
            {
                  cached_image_ok = false;
            }
      }

      cache_scale_method = scale_type_corrected;

      if(!cached_image_ok)
            return GetView( source, dest, scale_type_corrected );

      if(0 == cs1)                                        // overzoom
            return GetView( source, dest, scale_type_corrected );

      if(abs(source.x - cache_rect.x) % cs1)
            return GetView( source, dest, scale_type_corrected );
      if(abs(source.y - cache_rect.y) % cs1)
            return GetView( source, dest, scale_type_corrected );

      int stride_rows = (source.y + source.height) - (cache_rect.y + cache_rect.height);
      int scaled_stride_rows = stride_rows * dest.width / source.width;

      if(abs(stride_rows) >= source.height)                       // Pan more than one screen
            return GetView( source, dest, scale_type_corrected );

      int stride_pixels = (source.x + source.width) - (cache_rect.x + cache_rect.width);
      int   scaled_stride_pixels = stride_pixels * dest.width / source.width;

      if(abs(stride_pixels) >= source.width)                      // Pan more than one screen
            return GetView( source, dest, scale_type_corrected );

//    Setup the scale_type dependencies
      int get_bits_submap = 1;            // default, bi-linear

      if( scale_type_corrected == SCALE_SUBSAMP)
            get_bits_submap = cs1;

//    Calculate potential offset values for use in SCALE_SUBSAMP case
      xsoff = abs(source.x % get_bits_submap);              // calculate the source data offset
      ysoff =abs( source.y % get_bits_submap);              // in the buffer for SCALE_SUBSAMP case

//    Y Pan
      if(source.y != cache_rect.y)
      {

            //    Get the new bits needed
            if(stride_rows > 0)                             // pan down
                  s1 = wxRect(cache_rect.x, cache_rect.y + cache_rect.height, cache_rect.width, stride_rows);
            else                                                  // pan up
                  s1 = wxRect(cache_rect.x, source.y, cache_rect.width,  -stride_rows);


            //    Optimization in favor of memory footprint reduction
            unsigned char *ppnx = NULL;
            if(1 == cs1)                                    // unity scale
            {
                  ppnx = (unsigned char *)x_malloc((abs(stride_rows)) * source.width * BPP/8);
                  GetChartBits(s1, ppnx, get_bits_submap);
            }
            else
            {
                  GetAndScaleData(&ppnx, s1, source.width, dest,
                      scale_type_corrected);
            }

//    Now, concatenate the data

            unsigned char *ppc = (unsigned char *)pPixCache->GetpData();     // source
            PixelCache *pPCtemp = new PixelCache(dest.width, dest.height, BPP);     // destination
            pPix = pPCtemp->GetpData();


            unsigned char *ppn = ppnx;
            pCP = pPix;
            if(stride_rows > 0)                             // pan down
            {
                  unsigned char *pcac = ppc + (scaled_stride_rows * dest.width * BPP/8);
                  unsigned char *pnew = ppn;

                  memcpy(pCP, pcac, dest.width * (dest.height - scaled_stride_rows)*BPP/8);
                  pCP += dest.width * (dest.height - scaled_stride_rows) *BPP/8;
                  memcpy(pCP, pnew, dest.width * (scaled_stride_rows)*BPP/8);

            }
            else                                                  // pan up
            {
                  unsigned char *pcac = ppc;
                  unsigned char *pnew = ppn;

                  memcpy(pCP, pnew, dest.width * (-scaled_stride_rows)*BPP/8);
                  pCP += dest.width * (-scaled_stride_rows) *BPP/8;
                  memcpy(pCP, pcac, dest.width * (dest.height + scaled_stride_rows)*BPP/8);

            }

//    Delete working data
            free(ppnx);


            delete pPixCache;
            pPixCache = pPCtemp;

//    Update the cached parameters, Y only
            cache_rect.y = source.y;
//          cache_rect = source;
            cache_rect_scaled = dest;
            cached_image_ok = 1;


      }                 // Y Pan




//    X Pan
      if(source.x != cache_rect.x)
      {

            //    Get the new bits needed
            if(stride_pixels > 0)                           // pan right
                  s1 = wxRect(cache_rect.x + cache_rect.width, source.y, stride_pixels, source.height);
            else                                                  // pan left
                  s1 = wxRect(source.x, source.y, -stride_pixels, source.height);


            //    Optimization in favor of memory footprint reduction
            unsigned char *ppnx = NULL;
            if(1 == cs1)                                    // unity scale
            {
                  ppnx = (unsigned char *)x_malloc((abs(stride_pixels)) * source.height * BPP/8);
                  GetChartBits(s1, ppnx, get_bits_submap);
            }
            else
            {
                  GetAndScaleData(&ppnx, s1, source.width, dest,
                                  scale_type_corrected);
            }

//    Now, concatenate the data

            unsigned char *ppc = (unsigned char *)pPixCache->GetpData();     // source
            PixelCache *pPCtemp = new PixelCache(dest.width, dest.height, BPP);     // destination
            pPix = pPCtemp->GetpData();

            unsigned char *ppn = ppnx;
            pCP = pPix;
            if(stride_pixels > 0)                           // pan right
            {
                  unsigned char *pcac = ppc + scaled_stride_pixels * BPP/8;
                  unsigned char *pnew = ppn;

                  for(int iy=0 ; iy<cache_rect_scaled.height ; iy++)
                  {
                        memcpy(pCP, pcac, (cache_rect_scaled.width-scaled_stride_pixels) *BPP/8);

                        pCP += (cache_rect_scaled.width-scaled_stride_pixels) *BPP/8;

                        memcpy(pCP, pnew, scaled_stride_pixels * BPP/8);

                        pcac += cache_rect_scaled.width * BPP/8;
                        pnew += scaled_stride_pixels * BPP/8;

                        pCP += scaled_stride_pixels * BPP/8;
                  }
            }
            else                                                  // pan left
            {
                  unsigned char *pcac = ppc;
                  unsigned char *pnew = ppn;

                  for(int iy=0 ; iy<cache_rect_scaled.height ; iy++)
                  {
                        memcpy(pCP, pnew, scaled_stride_pixels * -BPP/8);
                        pCP += scaled_stride_pixels * -BPP/8;

                        memcpy(pCP, pcac, (cache_rect_scaled.width+scaled_stride_pixels) * BPP/8);

                        pCP += (cache_rect_scaled.width+scaled_stride_pixels) * BPP/8;


                        pcac += cache_rect_scaled.width * BPP/8;
                        pnew += scaled_stride_pixels * -BPP/8;

                  }
            }


//    Delete working data
            free(ppnx);


            delete pPixCache;
            pPixCache = pPCtemp;

//    Update the cached parameters
            cache_rect = source;
            cache_rect_scaled = dest;
            cached_image_ok = 1;

      }           // X pan

      return true;
}




bool ChartBaseBSB::GetView( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type )
{
      int cs1 = source.width/dest.width;

//    Setup the scale_type dependencies
      int get_bits_submap = 1;            // default, bi-linear

//    n.b if cs1 ==0, we are oversampling, scale > 1
      if( (scale_type == SCALE_SUBSAMP) && cs1)
            get_bits_submap = cs1;

      float canvas_scale = (float)dest.width / (float)source.width;

//      printf("canvas_scale %g\n", canvas_scale);

//    Create a temporary PixelCache
//      delete pPixCache;
      PixelCache *pPixCacheTemp = new PixelCache(dest.width, dest.height, BPP);


//    Special case for unity scale
//    In this case, need only one buffer, so make it the PixelCache buffer directly
      if(canvas_scale == 1)
      {
//    Get the chart bits directly into the PixelCache data buffer
          GetChartBits(source, pPixCacheTemp->GetpData(), get_bits_submap);
          delete pPixCache;
          pPixCache = pPixCacheTemp;
      }

//    Otherwise, non-unity scale, so need a temp buffer
      else
      {
//    Get and Rescale the data directly into the temporary PixelCache data buffer

            unsigned char *ppnx = pPixCacheTemp->GetpData();
            if(!GetAndScaleData(&ppnx, source, source.width, dest, scale_type))
            {
                delete pPixCacheTemp;                       // Some error, retain old cache
                return false;
            }
            else
            {
                delete pPixCache;                           // new cache is OK
                pPixCache = pPixCacheTemp;
            }
      }

//    Update cache parameters

      cache_rect = source;
      cache_rect_scaled = dest;

      cached_image_ok = 1;


      return TRUE;
}


bool ChartBaseBSB::GetAndScaleData(unsigned char **ppn, wxRect& source, int s_width,
                                   wxRect& dest, ScaleTypeEnum scale_type)
{
      unsigned char *s_data;

      float factor = ((float)s_width)/((float)dest.width);

      float pfactor = 1.0 / factor;

      int old_height = source.height;
      int old_width  = source.width;

      int target_width = (int)((float)old_width * pfactor) ;
      int target_height = (int)((float)old_height * pfactor);

      unsigned char *target_data;
      unsigned char *data;

      if(*ppn)                                        // Caller is supplying buffer
      {
            data = *ppn;
            target_data = data;
      }


      else                                            // else get a buffer here (and return it)
      {
            data = (unsigned char *) x_malloc( target_width*(target_height+2)*BPP/8 );
            target_data = data;
            *ppn = data;
      }


      int cs1 = s_width/dest.width;

//    Setup the scale_type dependencies
      int get_bits_submap = 1;            // default, bi-linear

//    n.b if cs1 ==0, we are oversampling, scale > 1
      if( (scale_type == SCALE_SUBSAMP) && cs1)
            get_bits_submap = cs1;


      if(factor > 1)
      {
            int Factor =  (int)factor;
            int a = (int)factor;
            int b = 0;

            if(0 == a)
                a=1;                    // shouldn't happen

            // Calculate scountre = 2 * log2(factor)
            while((a & 0x01) == 0)
            {
                  a=a>>1;
                  b++;
            }

            int scounter;
            scounter = b*2;


            if(scale_type == SCALE_BILINEAR)
            {
//    Allocate a working buffer based on scale factor
                  int wb_size = (source.width) * ((Factor + 1) * 2) * BPP/8 ;
                  s_data = (unsigned char *) x_malloc( wb_size ); // work buffer
                  unsigned char *pixel;
                  int y_offset;

                  int yr = source.y;

                  for (int y = 0; y < target_height; y++)
                  {
                  //    Read "factor" lines

                        wxRect s1;
                        s1.x = source.x;
                        s1.y = yr;
                        s1.width = source.width;
                        s1.height = Factor;
                        GetChartBits(s1, s_data, get_bits_submap);
                        yr += Factor;

                        int y_off0 = 0;
                        for (int x = 0; x < target_width; x++)
                        {
                              unsigned int avgRed = 0 ;
                              unsigned int avgGreen = 0;
                              unsigned int avgBlue = 0;
                              unsigned char *pix0 = s_data + BPP/8 * ( x * Factor ) ;
                              y_offset = y_off0;

                              if((x * Factor) < (Size_X - source.x))
                              {
            // determine average
                                    for ( int y1 = 0 ; y1 < Factor ; ++y1 )
                                    {
                                        pixel = pix0 + (BPP/8 * y_offset ) ;
                                        for ( int x1 = 0 ; x1 < Factor ; ++x1 )
                                        {
                                            avgRed += pixel[0] ;
                                            avgGreen += pixel[1] ;
                                            avgBlue += pixel[2] ;

                                            pixel += BPP/8;
                                        }
                                        y_offset += old_width ;
                                    }

                                    unsigned char *rgb_data = target_data;
                                    *(rgb_data++) = avgRed >> scounter;
                                    *(rgb_data++) = avgGreen >> scounter;
                                    *(rgb_data++) = avgBlue >> scounter;
                                    target_data += BPP/8;
                              }
                              else
                              {
                                    unsigned char *rgb_data = target_data;
                                    *(rgb_data++) = 0;
                                    *(rgb_data++) = 0;
                                    *(rgb_data++) = 0;
                                    target_data += BPP/8;
                              }

                        }  // for x

                  }  // for y

            }           // SCALE_BILINEAR

            else if (scale_type == SCALE_SUBSAMP)
            {
                  //    Find the special case of big zoom-out, lots of blank space around chart
                  //    Do this case such that the working buffer malloc is bounded.
                  if((source.x < 0) && ((source.width + source.x) > Size_X))
                  {
                        int wb_size = (Size_X) * ((Factor + 1) * 2) * BPP/8 ;
                        s_data = (unsigned char *) x_malloc( wb_size ); // work buffer
                        int yr = source.y;

                        unsigned char *y_off0;
                        int y_off0_inc = Factor * Size_X * BPP/8;

                        int y=0;                // starting here
                        while ( y < target_height)
                        {
                        //    Read "factor" lines

                              wxRect s1;
                              s1.x = 0;
                              s1.y = yr;
                              s1.width = Size_X;
                              s1.height = Factor;
                              GetChartBits(s1, s_data, get_bits_submap);
                              yr += Factor;

                              y_off0 = s_data;

                              target_data = data + (y * target_width * BPP/8);

                              unsigned char *pix0 = y_off0;
                              int xs = source.x;
                              while(xs < 0)
                              {
                                    unsigned char *rgb_data = target_data;
                                    *(rgb_data++) = 0;
                                    *(rgb_data++) = 0;
                                    *(rgb_data++) = 0;
                                    target_data += BPP/8;
                                    xs += Factor;
                              }

                              while ( xs < Size_X)
                              {


                                    unsigned char *rgb_data = target_data;
                                    *(rgb_data++) = *pix0++;
                                    *(rgb_data++) = *pix0++;
                                    *(rgb_data++) = *pix0++;
                                    target_data += BPP/8;

                                    if(BPP == 32)
                                          pix0++;

                                    xs += Factor;
                                    pix0 -= BPP/8;
                                    pix0 += Factor * BPP/8;
                              }

                              while(xs < source.width + source.x)
                              {
                                    unsigned char *rgb_data = target_data;
                                    *(rgb_data++) = 0;
                                    *(rgb_data++) = 0;
                                    *(rgb_data++) = 0;
                                    target_data += BPP/8;
                                    xs += Factor;
                              }

                              y_off0 += y_off0_inc;
                              y++;

                        }

                  }
                  //    More "normal" case
                  //    malloc of work buffer will be reasonable size , about O(Size_X)
                  else
                  {
                        int wb_size = (source.width) * ((Factor + 1) * 2) * BPP/8 ;
                        s_data = (unsigned char *) x_malloc( wb_size ); // work buffer
                        int yr = source.y;

                        unsigned char *y_off0;
                        int y_off0_inc = Factor * old_width * BPP/8;

                        int y=0;                // starting here
                        while ( y < target_height)
                        {
                        //    Read "factor" lines

                              wxRect s1;
                              s1.x = source.x;
                              s1.y = yr;
                              s1.width = source.width;
                              s1.height = Factor;
                              GetChartBits(s1, s_data, get_bits_submap);
                              yr += Factor;

                              y_off0 = s_data;

                              target_data = data + (y * target_width * BPP/8);

                              unsigned char *pix0 = y_off0;
                              int x = 0;
                              while ( x < target_width)
                              {

                                    unsigned char *rgb_data = target_data;
                                    *(rgb_data++) = *pix0++;
                                    *(rgb_data++) = *pix0++;
                                    *(rgb_data++) = *pix0++;
                                    target_data += BPP/8;

                                    if(BPP == 32)
                                          pix0++;

                                    x++;
                                    pix0 -= BPP/8;
                                    pix0 += Factor * BPP/8;
                              }

                              y_off0 += y_off0_inc;
                              y++;

                        }
                  }
            }     // SCALE_SUBSAMP

      }
      else  //factor < 1, overzoom
      {
            //    Seems safe enough to read all the required data
            int sx = wxMax(source.x, 0);

            //    Although we must adjust (increase) temporary allocation for negative source.x

            s_data = (unsigned char *) x_malloc( (sx + source.width) * source.height * BPP/8 );

            GetChartBits(source, s_data, get_bits_submap);

            unsigned char *target_line_start = target_data;

            target_height = dest.height;
            target_width = dest.width;

            for (int j = 0; j < target_height; j++)
            {
//                  int y_offset = (j  * old_height / target_height) * old_width;
                  int y_offset = (int)(j *m_raster_scale_factor) * source.width;

                  target_data = target_line_start;
                  for (int i = 0; i < target_width; i++)
                  {
                        wxASSERT((target_data - *ppn) < target_width * target_height * BPP / 8);
                        memcpy( target_data,
//                                s_data + BPP/8*(y_offset + ((i * old_width )/ target_width)),
                                s_data + BPP/8*(y_offset + (int)(i * m_raster_scale_factor)),
                                                        BPP/8 );
                        target_data += BPP/8;

                  }

                  target_line_start += target_width * BPP / 8;
            }

      }

      free(s_data);

      return true;

}


bool ChartBaseBSB::InitializeBackgroundBilinearRender(ViewPort &VPoint)
{
///    printf("Init bbr\n");
    wxRect dest(0,0,VPoint.pix_width, VPoint.pix_height);

    float factor = ((float)Rsrc.width)/((float)dest.width);

    if(factor < 1.0)            // it should never happen that we try to
        return false;           // re-scale an overzoomed chart, but....

    float pfactor = 1.0 / factor;

    int old_height = Rsrc.height;
    int old_width  = Rsrc.width;

    br_target_width = (int)((float)old_width * pfactor) ;
    br_target_height = (int)((float)old_height * pfactor);

    pPixCacheBackground = new PixelCache(dest.width, dest.height, BPP);

    br_target_data = pPixCacheBackground->GetpData();

//    Setup the scale_type dependencies
    br_get_bits_submap = 1;            // always bi-linear

    br_Factor =  (int)factor;
    int a = (int)factor;
    int b = 0;

    if(a == 0)                      // shouldn't happen
        a=1;

// Calculate scounter = 2 * log2(factor)
    while((a & 0x01) == 0)
    {
        a=a>>1;
        b++;
    }

    br_scounter = b*2;

//    Allocate a working buffer whose size is based on scale factor

    bwb_size = (Rsrc.width) * ((br_Factor + 1) * 2) * BPP/8 ;
    background_work_buffer = (unsigned char *) x_malloc( bwb_size ); // work buffer

    //  Set starting points
    br_y_source = Rsrc.y;
    br_target_y = 0;

    return true;

}

bool ChartBaseBSB::AbortBackgroundRender(void)
{
///    printf("Abort bbr\n");
    free(background_work_buffer);
    background_work_buffer = NULL;

    delete pPixCacheBackground;

    return true;
}

bool ChartBaseBSB::FinishBackgroundRender(void)
{
///    printf("Finish bbr\n");
    cache_scale_method= SCALE_BILINEAR;             // the cache is set
    cache_rect = Rsrc;

    cached_image_ok = true;

    delete pPixCache;
    pPixCache = pPixCacheBackground;

    free(background_work_buffer);
    background_work_buffer = NULL;

    return true;
}

bool ChartBaseBSB::ContinueBackgroundRender(void)
        /*
        Return true when finished
        */
{
    if(NULL == background_work_buffer)
        return true;

    if (br_target_y < br_target_height)
    {
                  //    Read "factor" lines
        wxRect s1;
        s1.x = Rsrc.x;
        s1.y = br_y_source;
        s1.width = Rsrc.width;
        s1.height = br_Factor;
        GetChartBits(s1, background_work_buffer, br_get_bits_submap);
        br_y_source += br_Factor;

        int y_off0 = 0;
        unsigned char *pixel;
        int y_offset;

        for (int x = 0; x < br_target_width; x++)
        {
            unsigned int avgRed = 0 ;
            unsigned int avgGreen = 0;
            unsigned int avgBlue = 0;
            unsigned char *pix0 = background_work_buffer + BPP/8 * ( x * br_Factor ) ;
            y_offset = y_off0;

            if((x * br_Factor) < (Size_X - Rsrc.x))
            {
            // determine average
                for ( int y1 = 0 ; y1 < br_Factor ; ++y1 )
                {
                    pixel = pix0 + (BPP/8 * y_offset ) ;
                    for ( int x1 = 0 ; x1 < br_Factor ; ++x1 )
                    {
                        avgRed += pixel[0] ;
                        avgGreen += pixel[1] ;
                        avgBlue += pixel[2] ;

                        pixel += BPP/8;
                    }
                    y_offset += Rsrc.width ;
                }


                unsigned char *rgb_data = br_target_data;
                *(rgb_data++) = avgRed >> br_scounter;
                *(rgb_data++) = avgGreen >> br_scounter;
                *(rgb_data++) = avgBlue >> br_scounter;
                br_target_data += BPP/8;
            }

            else
            {
                unsigned char *rgb_data = br_target_data;
                *(rgb_data++) = 0;
                *(rgb_data++) = 0;
                *(rgb_data++) = 0;
                br_target_data += BPP/8;
            }

        }  // for x

        br_target_y++;

        return false;                   // more to come

    }  // if y on range


    return true;                        // done
}


bool ChartBaseBSB::GetChartBits(wxRect& source, unsigned char *pPix, int sub_samp)
{

      int iy;
#define FILL_BYTE 0

//    Decode the KAP file RLL stream into image pPix

      unsigned char *pCP;
      pCP = pPix;

      iy = source.y;

      while (iy < source.y + source.height)
      {
            if((iy >= 0) && (iy < Size_Y))
            {
                    if(source.x >= 0)
                    {
                            if((source.x + source.width) > Size_X)
                            {
                                if((Size_X - source.x) < 0)
                                        memset(pCP, FILL_BYTE, source.width  * BPP/8);
                                else
                                {

                                        BSBGetScanline( pCP,  iy, source.x, Size_X, sub_samp);
                                        memset(pCP + (Size_X - source.x) * BPP/8, FILL_BYTE,
                                               (source.x + source.width - Size_X) * BPP/8);
                                }
                            }
                            else
                                BSBGetScanline( pCP, iy, source.x, source.x + source.width, sub_samp);
                    }
                    else
                    {
                            if((source.width + source.x) >= 0)
                            {
                                // Special case, black on left side
                                //  must ensure that (black fill length % sub_samp) == 0

                                int xfill_corrected = -source.x + (source.x % sub_samp);    //+ve
                                memset(pCP, FILL_BYTE, (xfill_corrected * BPP/8));
                                BSBGetScanline( pCP + (xfill_corrected * BPP/8),  iy, 0,
                                        source.width + source.x , sub_samp);

                            }
                            else
                            {
                                memset(pCP, FILL_BYTE, source.width  * BPP/8);
                            }
                    }
            }

            else              // requested y is off chart
            {
                  memset(pCP, FILL_BYTE, source.width  * BPP/8);

            }

            pCP += source.width * BPP/8 * sub_samp;

            iy += sub_samp;
      }     // while iy


      return true;
}






//-----------------------------------------------------------------------------------------------
//    BSB File Read Support
//-----------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------
//    ReadBSBHdrLine
//
//    Read and return count of a line of BSB header file
//-----------------------------------------------------------------------------------------------

int ChartBaseBSB::ReadBSBHdrLine(wxFileInputStream* ifs, char* buf, int buf_len_max)

{
      char  read_char;
      char  cr_test;
      int   line_length = 0;
      char  *lbuf;

      lbuf = buf;


      while( !ifs->Eof() && line_length < buf_len_max )
      {
            read_char = ifs->GetC();
            if(0x1A == read_char)
            {
                  ifs->Ungetch( read_char );
                        return(0);
            }

            //    Manage continued lines
            if( read_char == 10 || read_char == 13 )
            {

                  //    Check to see if there is an extra CR
                  cr_test = ifs->GetC( );
                  if(cr_test == 13)
                        cr_test = ifs->GetC( );             // skip any extra CR

                  if( cr_test != 10 && cr_test != 13 )
                        ifs->Ungetch( cr_test );
                  read_char = '\n';
            }

      //    Look for continued lines, indicated by ' ' in first position
            if( read_char == '\n' )
            {
                  cr_test = 0;
                  cr_test = ifs->GetC( );

                  if( cr_test != ' ' )
                        {
                        ifs->Ungetch( cr_test );
                        *lbuf = '\0';
                        return line_length;
                        }

      //    Merge out leading spaces
                  while( cr_test == ' ' )
                        cr_test = ifs->GetC( );
                  ifs->Ungetch( cr_test );

      //    Add a comma
                  *lbuf = ',';
                  lbuf++;
            }

            else
            {
                  *lbuf = read_char;
                  lbuf++;
                  line_length++;
            }

      }     // while


      // Terminate line
      *(lbuf-1) = '\0';

      return line_length;
}


//-----------------------------------------------------------------------
//    Scan a BSB Scan Line from raw data
//      Leaving stream pointer at start of next line
//-----------------------------------------------------------------------
int   ChartBaseBSB::BSBScanScanline(wxInputStream *pinStream )
{
      int nLineMarker, nValueShift, iPixel = 0;
      unsigned char byValueMask, byCountMask;
      unsigned char byNext;
      int coffset;

//      if(1)
      {
//      Read the line number.
            nLineMarker = 0;
            do
            {
                  byNext = pinStream->GetC();
                  nLineMarker = nLineMarker * 128 + (byNext & 0x7f);
            } while( (byNext & 0x80) != 0 );

//      Setup masking values.
            nValueShift = 7 - nColorSize;
            byValueMask = (((1 << nColorSize)) - 1) << nValueShift;
            byCountMask = (1 << (7 - nColorSize)) - 1;

//      Read and simulate expansion of runs.

            while( ((byNext = pinStream->GetC()) != 0 ) && (iPixel < Size_X))
            {

                  int   nPixValue;
                  int nRunCount;
                  nPixValue = (byNext & byValueMask) >> nValueShift;

                  nRunCount = byNext & byCountMask;

                  while( (byNext & 0x80) != 0 )
                  {
                        byNext = pinStream->GetC();
                        nRunCount = nRunCount * 128 + (byNext & 0x7f);
                  }

                  if( iPixel + nRunCount + 1 > Size_X )
                        nRunCount = Size_X - iPixel - 1;


//          Store nPixValue in the destination
//                  memset(pCL, nPixValue, nRunCount+1);
//                  pCL += nRunCount+1;
                  iPixel += nRunCount+1;
            }
            coffset = pinStream->TellI();

      }


      return nLineMarker;
}



//-----------------------------------------------------------------------
//    Get a BSB Scan Line Using Cache and scan line index if available
//-----------------------------------------------------------------------
int   ChartBaseBSB::BSBGetScanline( unsigned char *pLineBuf, int y, int xs, int xl, int sub_samp)

{
      int nLineMarker, nValueShift, iPixel = 0;
      unsigned char byValueMask, byCountMask;
      unsigned char byNext;
      CachedLine *pt;
      unsigned char *pCL;
      int rgbval;
      unsigned char *lp;
      unsigned char *xtemp_line;
      register int ix = xs;

      if(bUseLineCache)
      {
            if(pLineCache)
            {
//    Is the requested line in the cache, and valid?
                  pt = &pLineCache[y];
                  if(!pt->bValid)                                 // not valid, so get it
                  {
                        if(pt->pPix)
                              free(pt->pPix);
                        pt->pPix = (unsigned char *)x_malloc(Size_X);
                  }
            }
            xtemp_line = pt->pPix;
      }
      else
            xtemp_line = (unsigned char *)x_malloc(Size_X);


      if((bUseLineCache && !pt->bValid) || (!bUseLineCache))
      {
          if(pline_table[y] == 0)
              return 0;

          if(pline_table[y+1] == 0)
              return 0;

            int thisline_size = pline_table[y+1] - pline_table[y] ;

            if(thisline_size > ifs_bufsize)
                ifs_buf = (unsigned char *)realloc(ifs_buf, thisline_size);

            if( wxInvalidOffset == ifs_bitmap->SeekI(pline_table[y], wxFromStart))
                  return 0;

            ifs_bitmap->Read(ifs_buf, thisline_size);
            lp = ifs_buf;

//    At this point, the unexpanded, raw line is at *lp, and the expansion destination is xtemp_line

//      Read the line number.
            nLineMarker = 0;
            do
            {
                  byNext = *lp++;
                  nLineMarker = nLineMarker * 128 + (byNext & 0x7f);
            } while( (byNext & 0x80) != 0 );

//      Setup masking values.
            nValueShift = 7 - nColorSize;
            byValueMask = (((1 << nColorSize)) - 1) << nValueShift;
            byCountMask = (1 << (7 - nColorSize)) - 1;

//      Read and expand runs.

            pCL = xtemp_line;

            while( ((byNext = *lp++) != 0 ) && (iPixel < Size_X))
            {
                  int   nPixValue;
                  int nRunCount;
                  nPixValue = (byNext & byValueMask) >> nValueShift;

                  nRunCount = byNext & byCountMask;

                  while( (byNext & 0x80) != 0 )
                  {
                        byNext = *lp++;
                        nRunCount = nRunCount * 128 + (byNext & 0x7f);
                  }

                  if( iPixel + nRunCount + 1 > Size_X )     // protection
                        nRunCount = Size_X - iPixel - 1;

                  if(nRunCount < 0)                         // against corrupt data
                      nRunCount = 0;

//          Store nPixValue in the destination
                  memset(pCL, nPixValue, nRunCount+1);
                  pCL += nRunCount+1;
                  iPixel += nRunCount+1;
            }
      }

      if(bUseLineCache)
            pt->bValid = true;

//          Line is valid, de-reference thru proper pallete directly to target


      if(xl > Size_X-1)
            xl = Size_X-1;

      pCL = xtemp_line + xs;
      unsigned char *prgb = pLineBuf;

      int dest_inc_val_bytes = (BPP/8) * sub_samp;
      ix = xs;
      while(ix < xl-1)
      {
            unsigned char cur_by = *pCL;
            rgbval = (int)(pPalette[cur_by]);
            while((ix < xl-1))
            {
                  if(cur_by != *pCL)
                        break;
                  *((int *)prgb) = rgbval;
                  prgb+=dest_inc_val_bytes ;
                  pCL += sub_samp;
                  ix  += sub_samp;
            }
      }

// Get the last pixel explicitely
//  irrespective of the sub_sampling factor

      if(xs < xl-1)
      {
        unsigned char *pCLast = xtemp_line + (xl - 1);
        unsigned char *prgb_last = pLineBuf + ((xl - 1)-xs) * BPP/8;

        rgbval = (int)(pPalette[*pCLast]);        // last pixel
        unsigned char a = rgbval & 0xff;
        *prgb_last++ = a;
        a = (rgbval >> 8) & 0xff;
        *prgb_last++ = a;
        a = (rgbval >> 16) & 0xff;
        *prgb_last = a;
      }

      if(!bUseLineCache)
          free (xtemp_line);

      return 1;
}







int  *ChartBaseBSB::GetPalettePtr(BSB_Color_Capability color_index)
{
      if(pPalettes[color_index])
      {

            if(palette_direction == PaletteFwd)
                  return (int *)(pPalettes[color_index]->FwdPalette);
            else
                  return (int *)(pPalettes[color_index]->RevPalette);
      }
      else
            return NULL;
 }


PaletteDir ChartBaseBSB::GetPaletteDir(void)
 {
  // make a pixel cache
       PixelCache *pc = new PixelCache(4,4,BPP);
       RGBO r = pc->GetRGBO();
       delete pc;

       if(r == RGB)
             return PaletteFwd;
       else
             return PaletteRev;
 }



int   ChartBaseBSB::AnalyzeRefpoints(void)
{
      int i,n;
      double elt, elg;

//    Calculate the max/min reference points

      float lonmin = 1000;
      float lonmax = -1000;
      float latmin = 90.;
      float latmax = -90.;

      int plonmin = 100000;
      int plonmax = 0;
      int platmin = 100000;
      int platmax = 0;
      int nlonmin, nlonmax, nlatmax, nlatmin;

      for(n=0 ; n<nRefpoint ; n++)
      {
            //    Longitude
            if(pRefTable[n].lonr > lonmax)
            {
                  lonmax = pRefTable[n].lonr;
                  plonmax = (int)pRefTable[n].xr;
                  nlonmax = n;
            }
            if(pRefTable[n].lonr < lonmin)
            {
                  lonmin = pRefTable[n].lonr;
                  plonmin = (int)pRefTable[n].xr;
                  nlonmin = n;
            }

            //    Latitude
            if(pRefTable[n].latr < latmin)
            {
                  latmin = pRefTable[n].latr;
                  platmin = (int)pRefTable[n].yr;
                  nlatmin = n;
            }
            if(pRefTable[n].latr > latmax)
            {
                  latmax = pRefTable[n].latr;
                  platmax = (int)pRefTable[n].yr;
                  nlatmax = n;
            }
      }

      //    Special case for charts which cross the IDL
      if((lonmin * lonmax) < 0)
      {
            if(pRefTable[nlonmin].xr > pRefTable[nlonmax].xr)
            {
                  //    walk the reference table and add 360 to any longitude which is < 0
                  for(n=0 ; n<nRefpoint ; n++)
                  {
                        if(pRefTable[n].lonr < 0.0)
                              pRefTable[n].lonr += 360.;
                  }

                  //    And recalculate the  min/max
                  lonmin = 1000;
                  lonmax = -1000;

                  for(n=0 ; n<nRefpoint ; n++)
                  {
            //    Longitude
                        if(pRefTable[n].lonr > lonmax)
                        {
                              lonmax = pRefTable[n].lonr;
                              plonmax = (int)pRefTable[n].xr;
                              nlonmax = n;
                        }
                        if(pRefTable[n].lonr < lonmin)
                        {
                              lonmin = pRefTable[n].lonr;
                              plonmin = (int)pRefTable[n].xr;
                              nlonmin = n;
                        }

            //    Latitude
                        if(pRefTable[n].latr < latmin)
                        {
                              latmin = pRefTable[n].latr;
                              platmin = (int)pRefTable[n].yr;
                              nlatmin = n;
                        }
                        if(pRefTable[n].latr > latmax)
                        {
                              latmax = pRefTable[n].latr;
                              platmax = (int)pRefTable[n].yr;
                              nlatmax = n;
                        }
                  }
                  m_bIDLcross = true;
            }
      }

      //    Search for and find the reference point which is nearest the chart centroid

      double d_current_min = pow(360.0, 2);
      for(n=0 ; n<nRefpoint ; n++)
      {
          double cx = (lonmin +lonmax)/2.;
          double cy = (latmin +latmax)/2.;

          double d = pow((pRefTable[n].lonr - cx), 2) + pow((pRefTable[n].latr - cy), 2);
          if(d < d_current_min)
          {
              d_current_min = d;
              m_i_ref_near_center = n;
          }
      }


//          Build the Control Point Structure, etc

        cPoints.count = nRefpoint;

        cPoints.tx  = (double *)x_malloc(nRefpoint * sizeof(double));
        cPoints.ty  = (double *)x_malloc(nRefpoint * sizeof(double));
        cPoints.lon = (double *)x_malloc(nRefpoint * sizeof(double));
        cPoints.lat = (double *)x_malloc(nRefpoint * sizeof(double));

        cPoints.pwx = (double *)x_malloc(12 * sizeof(double));
        cPoints.wpx = (double *)x_malloc(12 * sizeof(double));
        cPoints.pwy = (double *)x_malloc(12 * sizeof(double));
        cPoints.wpy = (double *)x_malloc(12 * sizeof(double));

        for(n=0 ; n<nRefpoint ; n++)
        {
            cPoints.tx[n] = pRefTable[n].xr;
            cPoints.ty[n] = pRefTable[n].yr;
            cPoints.lon[n] = pRefTable[n].lonr;
            cPoints.lat[n] = pRefTable[n].latr;
        }

/*
        for(n=0 ; n<nRefpoint ; n++)
        {
              printf("cPoints:  %d  %g %g %g %g\n", n, cPoints.tx[n], cPoints.ty[n], (double)cPoints.lon[n], (double)cPoints.lat[n]);
        }
*/
        //      Helper parameters
        cPoints.txmax = plonmax;
        cPoints.txmin = plonmin;
        cPoints.tymax = platmax;
        cPoints.tymin = platmin;
        cPoints.lonmax = lonmax;
        cPoints.lonmin = lonmin;
        cPoints.latmax = latmax;
        cPoints.latmin = latmin;

        cPoints.status = 1;

        bUseGeoRef = true;                // default is true

        if(!bHaveImbeddedGeoref)
        {
              if(nRefpoint == 4)          // typical old BSB chart, or manually scanned/converted TIFF image
              {
                  bUseGeoRef = false;         // 4 REF points is too few for poly match.
              }
              else if(nRefpoint <= 20)
              {
                    cPoints.order = 2;      // If less than n points, use Polynomial curve fit to a quadratic equation
                                            // discovered and verified on ProblemCharts/NZ232_1 from Marco

                      // force longitude fit to linear and require no cross terms if chart is un-skewed, the usual case
                    if(Georef_Calculate_Coefficients(&cPoints, (Chart_Skew == 0)))
                        bUseGeoRef = false;         // some error in georef calculation, usually very bad fit
              }
              else
              {
                    cPoints.order = 3;

                      // force longitude fit to linear and require no cross terms if chart is un-skewed, the usual case
                    if(Georef_Calculate_Coefficients(&cPoints, (Chart_Skew == 0)))
                          bUseGeoRef = false;         // some error in georef calculation, usually very bad fit
              }
//              for(int h=0 ; h < 10 ; h++)
//                    printf(" %d  %g\n",  h, cPoints.pwy[h]);          // pix to lat
        }


//          Calculate and store errors

        if(bUseGeoRef)
        {
            double xpl_err_max = 0;
            double ypl_err_max = 0;
            double xpl_err_max_feet, ypl_err_max_feet;

            for(i=0 ; i<nRefpoint ; i++)
            {
                    pix_to_latlong((int)pRefTable[i].xr, (int)pRefTable[i].yr,
                                &elt, &elg);
                    pRefTable[i].ypl_error = elt - pRefTable[i].latr;

                    double lon_error = elg - pRefTable[i].lonr;
                    //  Longitude errors could be compunded by prior adjustment to ref points
                    if(fabs(lon_error) > 180.)
                    {
                          if(lon_error > 0.)
                              lon_error -= 360.;
                          else if(lon_error < 0.)
                              lon_error += 360.;
                    }

                    pRefTable[i].xpl_error = lon_error;

                    if(fabs(pRefTable[i].ypl_error) > fabs(ypl_err_max))
                        ypl_err_max = pRefTable[i].ypl_error;
                    if(fabs(pRefTable[i].xpl_error) > fabs(xpl_err_max))
                        xpl_err_max = pRefTable[i].xpl_error;
            }

            xpl_err_max_feet = fabs(xpl_err_max * 60 * 5280 * 1.15);
            ypl_err_max_feet = fabs(ypl_err_max * 60 * 5280 * 1.15);
            Chart_Error_Factor = fmax(fabs(xpl_err_max/(lonmax - lonmin)), fabs(ypl_err_max/(latmax - latmin)));


      //        Good enough for navigation?
            if(Chart_Error_Factor > .02)
            {
                if(!bGeoErrorSent)
                {
                      wxString msg = _T("   Georeference Chart_Error_Factor on chart ");
                      msg.Append(m_FullPath);
                      wxString msg1;
                      msg1.Printf(_T(" is %5g"), Chart_Error_Factor);
                      msg.Append(msg1);

                      wxLogMessage(msg);
//                    printf("!!Georeference Chart_Error_Factor on chart %s is %5g\n", pFullPath->mb_str(), Chart_Error_Factor);

                    bGeoErrorSent = true;
                    bUseGeoRef = false;
                }
            }
        }


            // More analysis

        // Define reference point as near "average" point
        double lat_ref = (latmax + latmin)/2.;
        double lon_ref = (lonmax + lonmin)/2.;

        if(bUseGeoRef)
        {

            // Define reference point as near "average" point
              double lat_ref = (latmax + latmin)/2.;
              double lon_ref = (lonmax + lonmin)/2.;

            // calculate the northing/easting from the reference point to a position
            // about 10% of the chart size away from the reference point

              double lat_test = lat_ref; // + 0.10 * (latmax - latmin);
              double lon_test = lon_ref + 0.10 * (lonmax - lonmin);
              double easting, northing;
              toSM(lat_test, lon_test, lat_ref, lon_ref, &easting, &northing);

            // Calculate the pixel positions of reference point and test point
              int xref, yref;
              latlong_to_pix(lat_ref, lon_ref, xref, yref);
              int x_test, y_test;
              latlong_to_pix(lat_test, lon_test, x_test, y_test);

            // And so the pixel rates, and pixels per meter.
            // Note that this type of polar length calculation works nicely on all chart skew angles
              m_ppm_avg = sqrt((double)((x_test - xref) * (x_test - xref)) + (double)((y_test - yref) * (y_test - yref))) /
                          sqrt((easting * easting) + (northing * northing));

        }
        else
            //  Algorithmic georeferencing is no good, so
            //  Try to get a ppm_avg from looking directly at the reference points
        {

            //  Search the control points for that one which is closest to chart center

              double min_dist = 360;
              int imin;
              for(i=0 ; i<nRefpoint ; i++)
              {
                    double dist = sqrt(((lat_ref - pRefTable[i].latr) * (lat_ref - pRefTable[i].latr))
                                      + ((lon_ref - pRefTable[i].lonr) * (lon_ref - pRefTable[i].lonr)));

                    if(dist < min_dist)
                    {
                          min_dist = dist;
                          imin = i;
                    }
              }

            //  Now search the control points for that one point whose latitude matches,
            //  and which is closest

              double min_distl = 360;
              int iminl = -1;
              for(i=0 ; i<nRefpoint ; i++)
              {
                    if((pRefTable[imin].latr == pRefTable[i].latr) && (i != imin))
                    {
                          double distl = fabs(pRefTable[imin].lonr - pRefTable[i].lonr);

                          if(distl < min_distl)
                          {
                                min_distl = distl;
                                iminl = i;
                          }
                    }
              }

            //  Found one?
              if(-1 != iminl)
              {
                    double easting0, northing0;
                    toSM(pRefTable[imin].latr, pRefTable[imin].lonr, lat_ref, lon_ref, &easting0, &northing0);

                    double easting1, northing1;
                    toSM(pRefTable[iminl].latr, pRefTable[iminl].lonr, lat_ref, lon_ref, &easting1, &northing1);

                    m_ppm_avg = fabs((pRefTable[imin].xr - pRefTable[iminl].xr) / (easting0 - easting1));
              }

                //  One more try, assume simple Mercator projection
                //  Find two reference points with identical latitude
              else
              {
                    m_ppm_avg = 0;
                    for(i=0 ; i<nRefpoint ; i++)
                    {
                          for(int j=i+1 ; j < nRefpoint ; j++)
                          {
                                if((pRefTable[i].latr == pRefTable[j].latr))
                                {
                                      double easting0, northing0;
                                      toSM(pRefTable[i].latr, pRefTable[i].lonr, lat_ref, lon_ref, &easting0, &northing0);

                                      double easting1, northing1;
                                      toSM(pRefTable[j].latr, pRefTable[j].lonr, lat_ref, lon_ref, &easting1, &northing1);

                                      m_ppm_avg = fabs((pRefTable[i].xr - pRefTable[j].xr) / (easting0 - easting1));

                                      break;
                                }
                          }
                          if(0.0 != m_ppm_avg)
                                break;
                    }
              }

              //  Another try
              //  Calculate ppm from chart max and min latitudes
              if(0 == m_ppm_avg)
              {
                    double easting0, northing0;
                    toSM(pRefTable[nlonmax].latr, pRefTable[nlonmax].lonr, lat_ref, lon_ref, &easting0, &northing0);

                    double easting1, northing1;
                    toSM(pRefTable[nlonmin].latr, pRefTable[nlonmin].lonr, lat_ref, lon_ref, &easting1, &northing1);

                    m_ppm_avg = fabs((pRefTable[nlonmin].xr - pRefTable[nlonmax].xr) / (easting0 - easting1));
              }


                // Last chance
                // Find any two points with different longitudes, get Simple Mercator scale from them
              if(0 == m_ppm_avg)
              {
                    for(i=0 ; i<nRefpoint ; i++)
                    {
                          for(int j=i+1 ; j < nRefpoint ; j++)
                          {
                                if((pRefTable[i].lonr != pRefTable[j].lonr))
                                {
                                      double easting0, northing0;
                                      toSM(pRefTable[i].latr, pRefTable[i].lonr, lat_ref, lon_ref, &easting0, &northing0);

                                      double easting1, northing1;
                                      toSM(pRefTable[j].latr, pRefTable[j].lonr, lat_ref, lon_ref, &easting1, &northing1);

                                      m_ppm_avg = fabs((pRefTable[i].xr - pRefTable[j].xr) / (easting0 - easting1));

                                      break;
                                }
                          }
                          if(0.0 != m_ppm_avg)
                                break;
                    }
              }
        }


             // cannot use georef at all
             // so hack out a reasonable ppm_avg from chart scale and scanning resolution (DU)
            //  converting chart scanning resolution in DotsPerInch to DotsPerMeter
            //  and then scale by cos(lat_ref) to match sm projection algorithms

        if((0 == m_ppm_avg) && (0 != m_Chart_Scale) && (0 != m_Chart_DU ))
        {
             m_ppm_avg = m_Chart_DU * 39.3701 / m_Chart_Scale;
        }


        //        Special case for very small scale charts without embedded georef constants
        if((m_Chart_Scale > 5.0e6)  &&  (Chart_Skew == 0) && !bHaveImbeddedGeoref)
        {
              wxLogMessage(_T("  Small scale chart georef Mercator override activated..."));

              bUseGeoRef = false;               // signal to use Mercator estimator
              Chart_Error_Factor = .019;        // override the Chart Error Factor to just good enough


              if(m_ppm_avg == 0.)
              {
                    if(m_Chart_Scale == 0.)
                    {
                          wxLogMessage(_T("  Cannot calculate effective pix-per-meter because SC is zero"));
                          m_ppm_avg = 1.0;                      // absolute fallback
                          return 0;
                    }
                    m_ppm_avg = m_Chart_DU * 39.3701 / m_Chart_Scale;         // direct from the scanned parameters
                    if(m_ppm_avg == 0.)
                    {
                          wxLogMessage(_T("  Cannot calculate effective pix-per-meter because DU is zero"));
                          m_ppm_avg = 1.0;                      // absolute fallback
                          return 0;
                    }
              }
              else
              {
                    wxLogMessage(_T("  Using minimal 2 REFpoint solution"));

              //  Check for consistency between DU and stated chart scale
                    double ppm_check = m_Chart_DU * 39.3701 / m_Chart_Scale;         // direct from the scanned parameters
                    if(fabs((ppm_check - m_ppm_avg) / m_ppm_avg) > .01)
                    {
                          wxLogMessage(_T("  Info:Chart DU and/or SC are inconsistent"));
                    }
              }

//              m_Chart_Scale = 127900000.;   // For BATHY.KAP
//              m_ppm_avg = m_Chart_DU * 39.3701 / m_Chart_Scale;         // direct from the scanned parameters

            //    Search for and find the reference point which is nearest the latitude projection point, longitude mid-chart
            //    We will later use this point as a reference point for mercator estimator
            //    Note that this calculation overrides a previous calculation of m_i_ref_near_center
              d_current_min = pow(360.0, 2);
              for(n=0 ; n<nRefpoint ; n++)
              {
                    double cx = (lonmin +lonmax)/2.;
                    double cy = m_proj_lat;

                    double d = pow((pRefTable[n].lonr - cx), 2) + pow((pRefTable[n].latr - cy), 2);
                    if(d < d_current_min)
                    {
                          d_current_min = d;
                          m_i_ref_near_center = n;
                    }
              }




        }


        if(0 == m_ppm_avg)
              m_ppm_avg = 1.0;                      // absolute fallback


//    Do a last little test on non-skewed charts
        if(0. == Chart_Skew)
        {
            double eastingt, northingt;
            toSM_ECC(pRefTable[nlatmin].latr, pRefTable[nlatmin].lonr, pRefTable[nlatmax].latr, pRefTable[nlatmax].lonr, &eastingt, &northingt);

            double latpix = fabs(pRefTable[nlatmin].yr - pRefTable[nlatmax].yr);

            double calc_latpix = fabs(northingt * m_ppm_avg);

            if(fabs(1.0 - calc_latpix / latpix) > .005)
            {
                  wxString msg = _T("   Georeference Square_Factor on chart ");
                  msg.Append(m_FullPath);
                  wxString msg1;
                  msg1.Printf(_T(" is %5g"), calc_latpix / latpix);
                  msg.Append(msg1);
                  wxLogMessage(msg);
             }
        }
      return(0);

}


/*
*  Extracted from bsb_io.c - implementation of libbsb reading and writing
*
*  Copyright (C) 2000  Stuart Cunningham <stuart_hc@users.sourceforge.net>
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*  $Id: chartimg.cpp,v 1.36 2009/12/22 22:01:40 bdbcat Exp $
*
*/


/**
 * generic polynomial to convert georeferenced lat/lon to char's x/y
 *
 * @param coeff list of polynomial coefficients
 * @param lon longitute or x
 * @param lat latitude or y
 *
 * @return coordinate corresponding to the coeff list
 */
static double polytrans( double* coeff, double lon, double lat )
{
    double ret = coeff[0] + coeff[1]*lon + coeff[2]*lat;
    ret += coeff[3]*lon*lon;
    ret += coeff[4]*lon*lat;
    ret += coeff[5]*lat*lat;
    ret += coeff[6]*lon*lon*lon;
    ret += coeff[7]*lon*lon*lat;
    ret += coeff[8]*lon*lat*lat;
    ret += coeff[9]*lat*lat*lat;
//    ret += coeff[10]*lat*lat*lat*lat;
//    ret += coeff[11]*lat*lat*lat*lat*lat;

//    for(int n = 0 ; n < 10 ; n++)
//          printf("  %g\n", coeff[n]);

    return ret;
}


#if 0
/**
 * converts Lon/Lat to chart's X/Y
 *
 * @param p pointer to a BSBImage structure
 * @param lon longitude (-180.0 to 180.0)
 * @param lat latitude (-180.0 to 180.0)
 * @param x  output chart X coordinate
 * @param y  output chart Y coordinate
 *
 * @return 1 on success and 0 on error
 */
extern int bsb_LLtoXY(BSBImage *p, double lon, double  lat, int* x, int* y)
{
    /* change longitude phase (CPH) */
    lon = (lon < 0) ? lon + p->cph : lon - p->cph;
    double xd = polytrans( p->wpx, lon, lat );
    double yd = polytrans( p->wpy, lon, lat );
    *x = (int)(xd + 0.5);
    *y = (int)(yd + 0.5);
    return 1;
}

/**
 * converts chart's X/Y to Lon/Lat
 *
 * @param p pointer to a BSBImage structure
 * @param x chart X coordinate
 * @param y chart Y coordinate
 * @param lon output longitude (-180.0 to 180.0)
 * @param lat output latitude (-180.0 to 180.0)
 *
 * @return 1 on success and 0 on error
 */
extern int bsb_XYtoLL(BSBImage *p, int x, int y, double* lonout, double*  latout)
{
    double lon = polytrans( p->pwx, x, y );
    lon = (lon < 0) ? lon + p->cph : lon - p->cph;
    *lonout = lon;
    *latout = polytrans( p->pwy, x, y );
    return 1;
}

#endif



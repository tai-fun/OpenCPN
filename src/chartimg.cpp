/******************************************************************************
 * $Id: chartimg.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $
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
 * Revision 1.1  2006/08/21 05:52:19  dsr
 * Initial revision
 *
 * Revision 1.8  2006/08/04 11:42:01  dsr
 * no message
 *
 * Revision 1.7  2006/07/28 20:33:47  dsr
 * Fix render abort logic
 *
 * Revision 1.6  2006/07/06 23:14:31  dsr
 * Cleanup
 *
 * Revision 1.5  2006/07/05 02:30:49  dsr
 * PeekMessage in Renderer, for better response
 *
 * Revision 1.4  2006/06/02 02:09:59  dsr
 * Add PeekMessage
 *
 * Revision 1.3  2006/05/28 00:47:44  dsr
 * Fix Duplicate palette creation/deletion
 *
 * Revision 1.2  2006/05/19 19:19:01  dsr
 * New Thumbchart logic
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
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



#include "chartimg.h"


//  Why are these not in wx/prec.h?
#include "wx/stream.h"
#include "wx/wfstream.h"
#include "wx/tokenzr.h"
#include "wx/filename.h"

#ifdef __WXMSW__
#include <wx/image.h>
#endif


#include <sys/stat.h>

#ifdef __WXX11__
#include "wx/x11/private.h"


//    For MIT-SHM Extensions
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#endif

// ----------------------------------------------------------------------------
// Random Prototypes
// ----------------------------------------------------------------------------
      extern "C" int polynomial_curve_fit(int p_order, int samples, double *x_data, double *y_data, double *p_coef);
      extern "C" void DegToUTM(float lat, float lon, char *zone, float *x, float *y, float lon0);
      extern "C" void UTMtoDeg(double long0, short southernHemisphere, double x, double y, double *lat, double *lon);

      extern "C" int compute_georef_equations(struct GeoRef *cp, double E12[],
                            double N12[], double E21[], double N21[]);
      extern "C" int georef(double e1, double n1, double *e, double *n, double E[],
              double N[], int order);

      extern void *x_malloc(size_t t);


CPL_CVSID("$Id: chartimg.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $");

// ----------------------------------------------------------------------------
// private classes
// ----------------------------------------------------------------------------


// ============================================================================
// PixelCache Implementation
// ============================================================================
PixelCache::PixelCache(int width, int height, int depth)
{
      m_width = width;
      m_height = height;
      m_depth = depth;
      m_pbm = NULL;
      m_rgbo = RGB;                        // default value;

      line_pitch_bytes =
      bytes_per_pixel = BPP / 8;
      line_pitch_bytes = bytes_per_pixel * width;


#if dyUSE_BITMAPO
      m_rgbo = BGR;
#endif


#ifdef __PIX_CACHE_DIBSECTION__
      m_pDS = new wxDIB(width, -height, BPP);
      pData = m_pDS->GetData();
#endif


#ifdef __PIX_CACHE_WXIMAGE__
      m_pimage = new wxImage(m_width, m_height, (bool)FALSE);
      pData = m_pimage->GetData();

#endif



#ifdef __PIX_CACHE_X11IMAGE__
      xdisplay = (Display *)wxGlobalDisplay();
      int xscreen = DefaultScreen( xdisplay );
      Visual* xvisual = DefaultVisual( xdisplay, xscreen );
      int bpp = wxTheApp->GetVisualInfo(xdisplay)->m_visualDepth;

      #ifdef ocpUSE_MITSHM
//    Use Shared Memory Extension
//    XShmSegmentInfo shminfo;
      pshminfo = new XShmSegmentInfo;

      m_pxim = XShmCreateImage( xdisplay, xvisual, bpp, ZPixmap, NULL, pshminfo, width, height );
      if (m_pxim == NULL) {
            wxLogError("XShmCreateImage failed!");
            return ;
      }

//    Identify and allocate the shared memory buffer
      pshminfo->shmid = shmget( IPC_PRIVATE, m_pxim->bytes_per_line * m_pxim->height, IPC_CREAT|0777 );
      if (pshminfo->shmid < 0) {
//            perror("shmget");
            XDestroyImage( m_pxim );
            m_pxim = NULL;
            wxLogMessage( "alloc_back_buffer: Shared memory error (shmget), disabling." );
//            c->shm = 0;
//            return NULL;
      }

      pshminfo->shmaddr = m_pxim->data
                  = (char*)shmat( pshminfo->shmid, 0, 0 );
      if (pshminfo->shmaddr == (char *) -1) {
//            perror("alloc_back_buffer");
            XDestroyImage( m_pxim );
            m_pxim = NULL;
            wxLogMessage("shmat failed\n");
//            return NULL;
      }

      pData = (unsigned char *)pshminfo->shmaddr;

      pshminfo->readOnly = False;

      XShmAttach( xdisplay, pshminfo );

//    Make some further checks
/*
      ErrorFlag = 0;
      XSetErrorHandler( HandleXError );
// This may trigger the X protocol error we're ready to catch:
      XShmAttach( xdisplay, &shminfo );
      XSync( xdisplay, False );

      if (ErrorFlag) {
// we are on a remote display, this error is normal, don't print it
            XFlush( xdisplay );
            ErrorFlag = 0;
            XDestroyImage( img );
            shmdt( shminfo.shmaddr );
            shmctl( shminfo.shmid, IPC_RMID, 0 );
//            return NULL;
      }
*/

      #else

      int ignore;
      bool bMIT_SHM;
      if (XQueryExtension( xdisplay, "MIT-SHM", &ignore, &ignore, &ignore ))
          bMIT_SHM = true;
      else
          bMIT_SHM = false;


      m_pxim = XCreateImage( xdisplay, xvisual, bpp, ZPixmap, 0, 0, width, height, 32, 0 );
      m_pxim->data = (char*) x_malloc( m_pxim->bytes_per_line * m_pxim->height );
      pData = (unsigned char *)m_pxim->data;
      #endif

#endif            //__PIX_CACHE_X11IMAGE__

#ifdef __PIX_CACHE_BMO__
      pData = (unsigned char *)x_malloc(width * height * depth/8);
#endif

}

PixelCache::~PixelCache()
{
#ifdef __PIX_CACHE_WXIMAGE__
      delete m_pimage;
      delete m_pbm;
#endif


#ifdef __PIX_CACHE_DIBSECTION__
      delete m_pDS;
#endif

#ifdef __PIX_CACHE_X11IMAGE__
      delete m_pbm;
      #ifdef ocpUSE_MITSHM
      XSync( xdisplay, False );                 // make sure the server is finished with this object

      XShmDetach( xdisplay, pshminfo );
      XDestroyImage( m_pxim );
      shmdt( pshminfo->shmaddr );               // free the memory
      shmctl( pshminfo->shmid, IPC_RMID, 0 );   // mark segment as destroyed
      delete pshminfo;
      #else
      XSync( xdisplay, False );                 // make sure the server is finished with this object
      XDestroyImage( m_pxim );
      #endif

#endif


#ifdef __PIX_CACHE_BMO__
      delete m_pbm;
      free (pData);
#endif


}

void PixelCache::SelectIntoDC(wxMemoryDC &dc)
{

#ifdef __PIX_CACHE_DIBSECTION__
      dyMemDC *pmdc = dynamic_cast<dyMemDC*>(&dc);
      pmdc->SelectObject (*m_pDS);

#endif      //__PIX_CACHE_DIBSECTION__


#ifdef __PIX_CACHE_WXIMAGE__
//    delete m_pbm;                       // kill the old one

      //    Convert image to bitmap
      #if dyUSE_BITMAPO
      if(!m_pbm)
            m_pbm = new wxBitmapo(*m_pimage, m_depth);
      #else
      if(!m_pbm)
            m_pbm = new wxBitmap (*m_pimage, -1);
      #endif

      if(m_pbm)
            dc.SelectObject(*m_pbm);
#endif            // __PIX_CACHE_WXIMAGE__


#ifdef __PIX_CACHE_X11IMAGE__
      #ifdef ocpUSE_MITSHM
      if(!m_pbm)
            m_pbm = new wxBitmapo(m_pxim, m_width, m_height, m_depth, TRUE);  // True, this is a shared XImage
      dc.SelectObject(*m_pbm);
      #else

      if(!m_pbm)
            m_pbm = new wxBitmapo(m_pxim, m_width, m_height, m_depth);
      dc.SelectObject(*m_pbm);

      #endif
#endif            //__PIX_CACHE_X11IMAGE__


#ifdef __PIX_CACHE_BMO__
      if(!m_pbm)
            m_pbm = new wxBitmapo(pData, m_width, m_height, m_depth);
      dc.SelectObject(*m_pbm);
#endif


}


// ============================================================================
// ThumbData implementation
// ============================================================================

ThumbData::ThumbData()
{
    pDIB = NULL;
}

ThumbData::~ThumbData()
{
    delete pDIB;
}


// ============================================================================
// ChartBase implementation
// ============================================================================
ChartBase::ChartBase()
{
      pcached_bitmap = NULL;

      pPubYear = new wxString;
      pPubYear->Clear();

      pThumbData = new ThumbData;
      pThumbData->pDIB = NULL;

      pName = new wxString;
      pName->Clear();

      m_color_scheme = COLOR_SCHEME_DEFAULT;

      bReadyToRender = false;
}

ChartBase::~ChartBase()
{
      if(pcached_bitmap)
             delete pcached_bitmap;

      delete pPubYear;

      delete pThumbData;

      delete pName;


}


// ============================================================================
// ChartDummy implementation
// ============================================================================
ChartDummy::ChartDummy()
{
      m_pBM = NULL;
      ChartType = CHART_TYPE_DUMMY;

      pFullPath = new wxString("Dummy");

}

ChartDummy::~ChartDummy()
{
      delete pFullPath;
      delete m_pBM;
}


InitReturn ChartDummy::Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs )
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

float ChartDummy::GetNativeScale()
{
      return 22000000.0;
}

void ChartDummy::GetPubDate(wxString &data)
{
      return;
}


void ChartDummy::InvalidateCache(void)
{
}


void ChartDummy::pix_to_latlong(int pixx, int pixy, double *lat, double *lon)
{
}

void ChartDummy::vp_pix_to_latlong(ViewPort& vp, int pixx, int pixy, double *lat, double *lon)
{
}


void ChartDummy::latlong_to_pix(double lat, double lon, int &pixx, int &pixy)
{
}

void ChartDummy::latlong_to_pix_vp(double lat, double lon, int &pixx, int &pixy, ViewPort& vp)
{
}


void ChartDummy::RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type)
{

      if(!m_pBM)
            m_pBM = new wxBitmap(VPoint.pix_width, VPoint.pix_height);
      dc.SelectObject(*m_pBM);

      dc.Clear();
}


void ChartDummy::SetVPParms(ViewPort *vpt)
{
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
      ChartType = CHART_TYPE_GEO;
}


ChartGEO::~ChartGEO()
{
}

InitReturn ChartGEO::Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs )
{
      #define BUF_LEN_MAX 4000
      PreInit(name, init_flags, cs);

      char buffer[BUF_LEN_MAX];

      ifs_hdr = new wxFileInputStream(name);          // open the file as a read-only stream

      if(!ifs_hdr->Ok())
            return INIT_FAIL_REMOVE;

      pFullPath = new wxString(name);

      wxFileName GEOFile(*pFullPath);

      wxString Path;
      Path = GEOFile.GetPath(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME);


//    Read the GEO file, extracting useful information

      ifs_hdr->SeekI(0, wxFromStart);                                         // rewind

      Size_X = Size_Y = 0;

      while( (ReadBSBHdrLine(ifs_hdr, &buffer[0], BUF_LEN_MAX)) != 0 )
    {
            if(!strncmp(buffer, "Bitmap", 6))
            {
                  wxStringTokenizer tkz(buffer, "=");
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs("Bitmap", TRUE))
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
                  wxStringTokenizer tkz(buffer, "=");
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs("Scale", TRUE))               // extract Scale
                  {
                        int i;
                        i = tkz.GetPosition();
                        Chart_Scale = atoi(&buffer[i]);
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
                  pRefTable[nRefpoint].ltr = ltr;
                  pRefTable[nRefpoint].lnr = lnr;
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
                  wxDateTime dt;
                  if(dt.ParseDate(date_string))       // successful parse?
                  {
                        sprintf(date_buf, "%d", dt.GetYear());
                  }
                  else
                  {
                        sscanf(date_string, "%s", date_buf);
                  }
                  pPubYear->Append(date_buf);
            }

            else if (!strncmp(buffer, "Skew", 4))
            {
                  wxStringTokenizer tkz(buffer, "=");
                  wxString token = tkz.GetNextToken();
                  if(token.IsSameAs("Skew Angle", FALSE))               // extract Skew Angle
                  {
                        int i;
                        i = tkz.GetPosition();
                        sscanf(&buffer[i], "%f", &Chart_Skew);
                  }
            }

            else if (!strncmp(buffer, "Name", 4))
            {
              wxStringTokenizer tkz(buffer, "=");
              wxString token = tkz.GetNextToken();
              if(token.IsSameAs("Name", FALSE))                         // Name
              {
                int i;
                i = tkz.GetPosition();
                while(isprint(buffer[i]) && (i < 80))
                {
                  pName->Append(buffer[i++]);
                }
              }
            }
      }     //while



//          Extract the remaining data from .NOS Bitmap file

      ifs_bitmap = NULL;

      wxString NOS_Name(*pBitmapFilePath);            // take a copy

      pBitmapFilePath->Prepend(Path);
//    wxLogMessage("ChartGEO:Init....NOS File Name is: %s", pBitmapFilePath->c_str());
      wxFileName NOS_filename(*pBitmapFilePath);
      if(NOS_filename.FileExists())
            ifs_bitmap = new wxFileInputStream(*pBitmapFilePath); // open the bitmap file
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
//          wxLogMessage("ChartGEO:Init....Trying NOS File Name: %s",
//                      (NOS_filename.GetFullPath()).c_str());
            if(NOS_filename.FileExists())
                  goto found_uclc_file;

// case 2
            fname.MakeLower();
            fext.MakeUpper();
            NOS_filename.SetName(fname);
            NOS_filename.SetExt(fext);
//          wxLogMessage("ChartGEO:Init....Trying NOS File Name: %s",
//                      (NOS_filename.GetFullPath()).c_str());
            if(NOS_filename.FileExists())
                  goto found_uclc_file;

// case 3
            fname.MakeUpper();
            fext.MakeLower();
            NOS_filename.SetName(fname);
            NOS_filename.SetExt(fext);
//          wxLogMessage("ChartGEO:Init....Trying NOS File Name: %s",
//                      (NOS_filename.GetFullPath()).c_str());
            if(NOS_filename.FileExists())
                  goto found_uclc_file;

// case 4
            fname.MakeUpper();
            fext.MakeUpper();
            NOS_filename.SetName(fname);
            NOS_filename.SetExt(fext);
//          wxLogMessage("ChartGEO:Init....Trying NOS File Name: %s",
//                      (NOS_filename.GetFullPath()).c_str());
            if(NOS_filename.FileExists())
                  goto found_uclc_file;

            return INIT_FAIL_REMOVE;                  // not found at all

found_uclc_file:
//          wxLogMessage("ChartGEO:Init....Found: %s", (NOS_filename.GetFullPath()).c_str());

            delete pBitmapFilePath;                   // fix up the member element
            pBitmapFilePath = new wxString(NOS_filename.GetFullPath());
            ifs_bitmap = new wxFileInputStream(*pBitmapFilePath); // open the bitmap file

      }           //else


      if(ifs_bitmap == NULL)
            return INIT_FAIL_REMOVE;

      if(!ifs_bitmap->Ok())
            return INIT_FAIL_REMOVE;


      while( (ReadBSBHdrLine(ifs_bitmap, &buffer[0], BUF_LEN_MAX)) != 0 )
      {

            if(!strncmp(buffer, "NOS", 3))
            {
                  wxStringTokenizer tkz(buffer, ",=");
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs("RA", TRUE))                  // extract RA=x,y
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
                  }
            }

            else if (!strncmp(buffer, "RGB", 3))
                  CreatePaletteEntry(buffer, COLOR_SCHEME_DEFAULT);

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
      {
            return INIT_FAIL_REMOVE;
      }


//    Calculate the Chart Extents from the PLY data, for fast database search

      LonMax = -179.0;
      LonMin = 179.0;
      LatMax = 0.0;
      LatMin = 90.0;

      Plypoint *ppp = pPlyTable;
      for(int u=0 ; u<nPlypoint ; u++)
      {
            if(ppp->lnp > LonMax)
                  LonMax = ppp->lnp;
            if(ppp->lnp < LonMin)
                  LonMin = ppp->lnp;
            if(ppp->ltp > LatMax)
                  LatMax = ppp->ltp;
            if(ppp->ltp < LatMin)
                  LatMin = ppp->ltp;

            ppp++;
      }


      if(init_flags == HEADER_ONLY)
            return INIT_OK;

//    Advance to the data
      unsigned char c;
      if((c = ifs_bitmap->GetC()) != 0x1a){ assert(false); return INIT_FAIL_REMOVE;}
      if((c = ifs_bitmap->GetC()) == 0x0d)
      {
            if((c = ifs_bitmap->GetC()) != 0x0a){ assert(false); return INIT_FAIL_REMOVE;}
            if((c = ifs_bitmap->GetC()) != 0x1a){ assert(false); return INIT_FAIL_REMOVE;}
            if((c = ifs_bitmap->GetC()) != 0x00){ assert(false); return INIT_FAIL_REMOVE;}
      }

      else if(c != 0x00){ assert(false); return INIT_FAIL_REMOVE;}

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
//    _CrtSetBreakAlloc(4097);
      ChartType = CHART_TYPE_KAP;
}


ChartKAP::~ChartKAP()
{
}


InitReturn ChartKAP::Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs )
{
      #define BUF_LEN_MAX 4000

      PreInit(name, init_flags, cs);

      char buffer[BUF_LEN_MAX];

      ifs_hdr = new wxFileInputStream(name);          // open the Header file as a read-only stream

      if(!ifs_hdr->Ok())
            return INIT_FAIL_REMOVE;

      pFullPath = new wxString(name);

      ifs_bitmap = new wxFileInputStream(name); // Open again, as the bitmap


//    Validate the BSB header
//    by reading some characters into a buffer and looking for BSB\ keyword


      unsigned int TestBlockSize = 999;
      ifs_hdr->Read(buffer, TestBlockSize);

      if(ifs_hdr->LastRead() != TestBlockSize)
      {
            wxLogMessage("Could not read first %d bytes of header for chart file: %s",
                       TestBlockSize, name.c_str() );
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
            wxLogMessage("Chart file %s has no BSB header, cannot Init.", name.c_str());
            return INIT_FAIL_REMOVE;
      }



//    Read and Parse Chart Header, line by line
      ifs_hdr->SeekI(0, wxFromStart);                                         // rewind

      Size_X = Size_Y = 0;

      int done_header_parse = 0;

      while(done_header_parse == 0)
      {
            if(ReadBSBHdrLine(ifs_hdr, &buffer[0], BUF_LEN_MAX) == 0)
            {
                  unsigned char c;
                  c = ifs_hdr->GetC();
                  ifs_hdr->Ungetch(c);

                  if(0x1a == c)
                  {
                        done_header_parse = 1;
                  }
                  continue;
            }



            if(!strncmp(buffer, "BSB", 3))
            {
                  wxStringTokenizer tkz(buffer, "/,=");
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs("RA", TRUE))                  // extract RA=x,y
                        {
                              int i;
                              i = tkz.GetPosition();
                              Size_X = atoi(&buffer[i]);
                              wxString token = tkz.GetNextToken();
                              i = tkz.GetPosition();
                              Size_Y = atoi(&buffer[i]);
                        }
                        if(token.IsSameAs("NA", TRUE))                  // extract NA=str
                        {
                          int i;
                          i = tkz.GetPosition();
                          while((buffer[i] != ',') && (i < 80))
                          {
                            pName->Append(buffer[i]);
                            i++;
                          }
                        }
                  }
            }

            else if(!strncmp(buffer, "KNP", 3))
            {
                  wxStringTokenizer tkz(buffer, "/,=");
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs("SC", TRUE))                  // extract Scale
                        {
                              int i;
                              i = tkz.GetPosition();
                              Chart_Scale = atoi(&buffer[i]);
                        }
                        if(token.IsSameAs("SK", TRUE))                  // extract Skew
                        {
                              int i;
                              i = tkz.GetPosition();
                              sscanf(&buffer[i], "%f,", &Chart_Skew);
                        }

                 }
            }


            else if (!strncmp(buffer, "RGB", 3))
                  CreatePaletteEntry(buffer, COLOR_SCHEME_DEFAULT);

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
                  pRefTable[nRefpoint].ltr = ltr;
                  pRefTable[nRefpoint].lnr = lnr;
                  pRefTable[nRefpoint].bXValid = 1;
                  pRefTable[nRefpoint].bYValid = 1;

                  nRefpoint++;

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
                  wxStringTokenizer tkz(buffer, "/,=");
                  while ( tkz.HasMoreTokens() )
                  {
                        wxString token = tkz.GetNextToken();
                        if(token.IsSameAs("ED", TRUE))                  // extract Edition Date
                        {
//          wxLogMessage("Extract ED from %s", this->pFullPath->c_str());
                              int i;
                              i = tkz.GetPosition();

                              char date_string[40];
                              char date_buf[10];
                              sscanf(&buffer[i], "%s\r\n", date_string);
                              wxDateTime dt;
                              if(dt.ParseDate(date_string))       // successful parse?
                              {
                                    int iyear = dt.GetYear();
//    BSB charts typically list publish date as xx/yy/zz, we want 19zz.
                                    if(iyear < 100)
                                          iyear += 1900;
                                    sprintf(date_buf, "%d", iyear);
                              }
                              else
                              {
                                    sscanf(date_string, "%s", date_buf);
                              }
                              pPubYear->Append(date_buf);
                        }
                  }
            }

      }




//    Validate some of the header data
      if((Size_X == 0) || (Size_Y == 0))
      {
            return INIT_FAIL_REMOVE;
      }


//    Calculate the Chart Extents from the PLY data, for fast database search

      LonMax = -179.0;
      LonMin = 179.0;
      LatMax = 0.0;
      LatMin = 90.0;

      Plypoint *ppp = pPlyTable;
      for(int u=0 ; u<nPlypoint ; u++)
      {
            if(ppp->lnp > LonMax)
                  LonMax = ppp->lnp;
            if(ppp->lnp < LonMin)
                  LonMin = ppp->lnp;
            if(ppp->ltp > LatMax)
                  LatMax = ppp->ltp;
            if(ppp->ltp < LatMin)
                  LatMin = ppp->ltp;


            ppp++;
      }


      if(init_flags == HEADER_ONLY)
            return INIT_OK;

//    Advance to the data
      unsigned char c;
      if((c = ifs_hdr->GetC()) != 0x1a){ assert(false); return INIT_FAIL_REMOVE;}
      if((c = ifs_hdr->GetC()) == 0x0d)
      {
            if((c = ifs_hdr->GetC()) != 0x0a){ assert(false); return INIT_FAIL_REMOVE;}
            if((c = ifs_hdr->GetC()) != 0x1a){ assert(false); return INIT_FAIL_REMOVE;}
            if((c = ifs_hdr->GetC()) != 0x00){ assert(false); return INIT_FAIL_REMOVE;}
      }

      else if(c != 0x00){ assert(false); return INIT_FAIL_REMOVE;}

//    Read the Color table bit size
      nColorSize = ifs_hdr->GetC();



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
      pFullPath = NULL;
      pBitmapFilePath = NULL;

      pline_table = NULL;
      ifs_buf = NULL;

      cached_image_ok = 0;

      pRefTable = (Refpoint *)x_malloc(sizeof(Refpoint));
      nRefpoint = 0;
      cPoints.status = 0;

      pPlyTable = (Plypoint *)x_malloc(sizeof(Plypoint));
      nPlypoint = 0;

      bUseLineCache = true;
      Chart_Skew = 0.0;

      pPixCache = NULL;

      pLineCache = NULL;


      m_bilinear_limit = 8;         // bilinear scaling only up to 4

      ifs_bitmap = NULL;
      ifs_hdr = NULL;

      for(int i = 0 ; i < N_COLOR_SCHEMES ; i++)
            pPalettes[i] = NULL;

}

ChartBaseBSB::~ChartBaseBSB()
{
      if(pFullPath)
            delete pFullPath;

      if(pBitmapFilePath)
            delete pBitmapFilePath;

      if(pline_table)
            free(pline_table);

      if(ifs_buf)
            free(ifs_buf);



      free(pRefTable);
      free(pPlyTable);

      if(ifs_hdr)
            if(ifs_hdr->Ok())
                  delete ifs_hdr;

      if(ifs_bitmap)
            if(ifs_bitmap->Ok())
                  delete ifs_bitmap;


      if(cPoints.status)
      {
            free(E12);
            free(N12);
            free(E21);
            free(N21);
            free(cPoints.e1);
            free(cPoints.n1);
            free(cPoints.e2);
            free(cPoints.n2);
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

      for(int i = 0 ; i < N_COLOR_SCHEMES ; i++)
            delete pPalettes[i];




}

InitReturn ChartBaseBSB::Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs )
{
      m_color_scheme = cs;
      return INIT_OK;
}

InitReturn ChartBaseBSB::PreInit( const wxString& name, ChartInitFlag init_flags, ColorScheme cs )
{
      m_color_scheme = cs;
      return INIT_OK;
}

void ChartBaseBSB::CreatePaletteEntry(char *buffer, int palette_index)
{
      if(!pPalettes[palette_index])
            pPalettes[palette_index] = new Palette;

      Palette *pp = pPalettes[palette_index];

      int i;
      int n,r,g,b;
      sscanf(&buffer[4], "%d,%d,%d,%d", &n, &r, &g, &b);

      i=n;
      if(i < PALETTE_SIZE)
      {
            pp->FwdPalette[i][0] = (unsigned char)r;
            pp->FwdPalette[i][1] = (unsigned char)g;
            pp->FwdPalette[i][2] = (unsigned char)b;
            pp->RevPalette[i][0] = (unsigned char)b;
            pp->RevPalette[i][1] = (unsigned char)g;
            pp->RevPalette[i][2] = (unsigned char)r;
      }
      else
            wxLogMessage("Palette has more than PALETTE_SIZE entries");


}



InitReturn ChartBaseBSB::PostInit(void)
{
     //    Validate the palette array, substituting DEFAULT for missing entries
      for(int i = 0 ; i < N_COLOR_SCHEMES ; i++)
      {
            if(pPalettes[i] == NULL)
            {
                Palette *pNullSubPal = new Palette;
                *pNullSubPal = *pPalettes[COLOR_SCHEME_DEFAULT];        // copy the palette
                pPalettes[i] = pNullSubPal;
            }
      }

      // Establish the palette type and default palette
      palette_direction = GetPaletteDir();

      pPalette = GetPalettePtr(m_color_scheme);

      //    Allocate memory for ifs file buffering
      ifs_bufsize = 64000;
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
      for(int iplt=0 ; iplt<Size_Y ; iplt++)
      {
            offset = 0;
            offset += (unsigned char)ifs_bitmap->GetC() * 256 * 256 * 256;
            offset += (unsigned char)ifs_bitmap->GetC() * 256 * 256 ;
            offset += (unsigned char)ifs_bitmap->GetC() * 256 ;
            offset += (unsigned char)ifs_bitmap->GetC();

            pline_table[iplt] = offset;
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


      //   Analyze Refpoints
      int analyze_ret_val = AnalyzeRefpoints();
      if(0 != analyze_ret_val)
            return INIT_FAIL_REMOVE;

      bReadyToRender = true;
      return INIT_OK;
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

void ChartBaseBSB::GetChartExtent(Extent *pext)
{
      pext->NLAT = LatMax;
      pext->SLAT = LatMin;
      pext->ELON = LonMax;
      pext->WLON = LonMin;
}


void ChartBaseBSB::SetColorScheme(ColorScheme cs, bool bApplyImmediate)
{
      pPalette = GetPalettePtr(cs);

      m_color_scheme = cs;

      if(bApplyImmediate)
            cached_image_ok = false;
}


wxBitmap *ChartBaseBSB::CreateThumbnail(int tnx, int tny)
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

      wxBitmap *retBMP;

/*
#ifdef __WXMSW__
      #if dyUSE_BITMAPO
      retBMP = new wxBitmapo(pPixTN, des_width, des_height, -1);
      #else
      wxImage thumb_image(des_width, des_height, pPixTN, true);
      retBMP = new wxBitmap(&thumb_image);
      #endif
#endif


//    must be for X11 or GTK
*/

#if dyUSE_BITMAPO
      retBMP = new wxBitmapo(pPixTN, des_width, des_height, -1);
#else
      wxImage thumb_image(des_width, des_height, pPixTN, true);
      retBMP = new wxBitmap(&thumb_image);
#endif


      free(pPixTN);


//      if(!retBMP->Ok())
//          int ffj = 4;

      return retBMP;

}


//-------------------------------------------------------------------------------------------------
//          Get the Chart thumbnail data structure
//          Creating the thumbnail bitmap as required
//-------------------------------------------------------------------------------------------------

ThumbData *ChartBaseBSB::GetThumbData(int tnx, int tny, float lat, float lon)
{


//    Create the bitmap if needed
      if(!pThumbData->pDIB)
            pThumbData->pDIB = CreateThumbnail(tnx, tny);


//    Plot the supplied Lat/Lon on the thumbnail
      int divx = Size_X / tnx;
      int divy = Size_Y / tny;

      int div_factor = __min(divx, divy);

      double dpix, dpiy;
      int pixx, pixy;
      float  northing, easting;

      DegToUTM(lat, lon, NULL, &easting, &northing, long0);

      georef(easting, northing, &dpix, &dpiy, this->E21, this->N21, cPoints.order);
      pixx = (int)floor((dpix + 0.5));                // rounding
      pixy = (int)floor((dpiy+ 0.5));

      pThumbData->ShipX = pixx / div_factor;
      pThumbData->ShipY = pixy / div_factor;


      return pThumbData;
}


void ChartBaseBSB::RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type)

{

//    Get the view into the pixel buffer
      wxRect dest(0,0,VPoint.pix_width, VPoint.pix_height);
      GetViewUsingCache(Rsrc, dest, scale_type);


      //    It could happen that this is the first render of this chart,
      //    .AND. scale_type is bi-linear
      //    .AND.  the render is interrupted by mouse movement.
      //    In this case, there is will be no pPixCache yet....

      //    So, force a subsample render which cannot be interrupted

      if(pPixCache == NULL)
          GetViewUsingCache(Rsrc, dest, SCALE_SUBSAMP);

//    Select the data into the dc
      pPixCache->SelectIntoDC(dc);


}







//-----------------------------------------------------------------------
//          Pixel to Lat/Long Conversion helpers
//-----------------------------------------------------------------------

void ChartBaseBSB::pix_to_latlong(int pixx, int pixy, double *plat, double *plon)
{
      double  northing, easting;

      double px = pixx;
      double py = pixy;
      georef(px, py, &easting, &northing, this->E12, this->N12, cPoints.order);

      UTMtoDeg(long0, 0, easting, northing, plat, plon);
}

void ChartBaseBSB::vp_pix_to_latlong(ViewPort& vp, int pixx, int pixy, double *plat, double *plon)
{
      float raster_scale = GetNativeScale() / vp.view_scale;

      pix_to_latlong((int)(pixx/raster_scale) + Rsrc.x, (int)(pixy/raster_scale) + Rsrc.y, plat, plon);
}


void ChartBaseBSB::SetVPParms(ViewPort *vpt)
{
    UpdateViewPortParms(*vpt);
      return;
}


void ChartBaseBSB::GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion)
{

      float raster_scale = GetNativeScale() / VPoint.view_scale;
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

//    if(cs1 == 0)
//          cs1 = 1;

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

//    canvas_scale = (float)dest.width / (float)source.width;
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
                  GetChartBits(s1, ppnx, 1, get_bits_submap);
            }
            else
            {
                  GetAndScaleData(&ppnx, s1, source.width, dest.width,
                      scale_type_corrected);
            }

//    Now, concatenate the data

            unsigned char *ppc = (unsigned char *)pPixCache->pData;     // source
            PixelCache *pPCtemp = new PixelCache(dest.width, dest.height, BPP);     // destination
            pPix = pPCtemp->pData;


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
                  GetChartBits(s1, ppnx, 1, get_bits_submap);
            }
            else
            {
                  GetAndScaleData(&ppnx, s1, source.width, dest.width,
                                  scale_type_corrected);
            }

//    Now, concatenate the data

            unsigned char *ppc = (unsigned char *)pPixCache->pData;     // source
            PixelCache *pPCtemp = new PixelCache(dest.width, dest.height, BPP);     // destination
            pPix = pPCtemp->pData;

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

//    Create a temporary PixelCache
//      delete pPixCache;
      PixelCache *pPixCacheTemp = new PixelCache(dest.width, dest.height, BPP);


//    Special case for unity scale
//    In this case, need only one buffer, so make it the PixelCache buffer directly
      if(canvas_scale == 1)
      {
//    Get the chart bits directly into the PixelCache data buffer
            GetChartBits(source, pPixCacheTemp->pData, 1, get_bits_submap);
            delete pPixCache;
            pPixCache = pPixCacheTemp;
      }

//    Otherwise, non-unity scale, so need a temp buffer
      else
      {
//    Get and Rescale the data directly into the temporary PixelCache data buffer

            unsigned char *ppnx = pPixCacheTemp->pData;
            if(!GetAndScaleData(&ppnx, source, source.width, dest.width, scale_type))
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



bool ChartBaseBSB::GetViewIntoPrivatePixelCache( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type )
{
  int cs1 = source.width/dest.width;

//    Setup the scale_type dependencies
  int get_bits_submap = 1;            // default, bi-linear

//    n.b if cs1 ==0, we are oversampling, scale > 1
  if( (scale_type == SCALE_SUBSAMP) && cs1)
    get_bits_submap = cs1;

  float l_canvas_scale = (float)dest.width / (float)source.width;

//    Create the PixelCache
  pPixCacheAlternate = new PixelCache(dest.width, dest.height, BPP);


//    Special case for unity scale
//    In this case, need only one buffer, so make it the PixelCache buffer directly
  if(l_canvas_scale == 1)
  {
//    Get the chart bits directly into the PixelCache data buffer
    GetChartBits(source, pPixCacheAlternate->pData, 1, get_bits_submap);
  }

//    Otherwise, non-unity scale, so need a temp buffer
  else
  {
//    Get and Rescale the data directly into the PixelCache data buffer

    unsigned char *ppnx = pPixCacheAlternate->pData;
    GetAndScaleData(&ppnx, source, source.width, dest.width, scale_type);
  }

      cache_rect_alt = source;
      cache_rect_scaled_alt = dest;


  return TRUE;
}
bool ChartBaseBSB::AssumeAlternateCacheParms()
{
      if(pPixCacheAlternate)
      {
            delete pPixCache;
            pPixCache = pPixCacheAlternate;

            pPixCacheAlternate = NULL;

            cache_rect = cache_rect_alt;
            cache_rect_scaled = cache_rect_scaled_alt;

            cached_image_ok = 1;
      }
      //Todo make wxLogMessage
      else
            printf("tried to assume null pixelcache\n");

      return true;
}



void ChartBaseBSB::latlong_to_pix(double lat, double lon, int &pixx, int &pixy)
{
      float  northing, easting;
//    char zone[20];;

      DegToUTM(lat, lon, NULL, &easting, &northing, long0);

      double dpix, dpiy;

      georef(easting, northing, &dpix, &dpiy, this->E21, this->N21, cPoints.order);
      pixx = (int)floor((dpix + 0.5));                // rounding
      pixy = (int)floor((dpiy+ 0.5));

}


void ChartBaseBSB::latlong_to_pix_vp(double lat, double lon, int &pixx, int &pixy, ViewPort& vp)
{
      int px, py;
      latlong_to_pix(lat, lon, px, py);

      float raster_scale = GetNativeScale() / vp.view_scale;

      pixx = (int)((px - Rsrc.x) * raster_scale);
      pixy = (int)((py - Rsrc.y) * raster_scale);

}


void ChartBaseBSB::UpdateViewPortParms(ViewPort &vp)
{
    int pixxd, pixyd;
    latlong_to_pix(vp.clat, vp.clon, pixxd, pixyd);

    float sc = vp.view_scale / GetNativeScale();    // native (1X) scale

    Rsrc.x = pixxd - (int)(vp.pix_width  * sc / 2);
    Rsrc.y = pixyd - (int)(vp.pix_height * sc / 2);

    Rsrc.width =  (int)(vp.pix_width  * sc) ;
    Rsrc.height = (int)(vp.pix_height * sc) ;
}


bool ChartBaseBSB::ScaleData(unsigned char *pPix, unsigned char **ppn, wxRect& source, int s_width,
                              int d_width, ScaleTypeEnum scale_type)
{
      float factor = ((float)s_width)/((float)d_width);

      if(factor == 1.0)
      {
            *ppn = pPix;
            return true;
      }


      float pfactor = 1.0 / factor;

      int old_height = source.height;
      int old_width  = source.width;

      int target_width = (int)((float)old_width * pfactor) ;
      int target_height = (int)((float)old_height * pfactor);


      char unsigned *source_data = pPix;                    // the source data buffer

      unsigned char *target_data;
      unsigned char *data;
      if(*ppn)                                                          // Caller is supplying buffer
      {
            data = *ppn;
            target_data = data;
      }


      else                                                              // else get a buffer here (and return it)
      {
            data = (unsigned char *) x_malloc( target_width*(target_height+2)*BPP/8 );
            target_data = data;
            *ppn = data;
      }


      if(factor > 1)
            {

                  int Factor =  (int)factor;
                  int scounter;
                  if(Factor == 2)
                        scounter = 2;
                  else if(Factor == 4)
                        scounter = 4;
                  else if(Factor == 8)
                        scounter = 6;
                  else if(Factor == 16)
                        scounter = 8;

                  assert(Factor < 17);



                  if(scale_type == SCALE_BILINEAR)
                  {
                        unsigned char *pixel;
                        int y_offset;

                        for (int y = 0; y < target_height; y++)
                        {
                              int y_off0 = (y * Factor) * old_width;
                              for (int x = 0; x < target_width; x++)
                              {
                                    unsigned int avgRed = 0 ;
                                    unsigned int avgGreen = 0;
                                    unsigned int avgBlue = 0;
                                    unsigned char *pix0 = source_data + BPP/8 * ( x * Factor ) ;
                                    y_offset = y_off0;

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
                                          y_offset += old_width;
                                    }

                                    unsigned char *rgb_data = target_data;
                                    *(rgb_data++) = avgRed >> scounter;
                                    *(rgb_data++) = avgGreen >> scounter;
                                    *(rgb_data++) = avgBlue >> scounter;
                                    target_data += BPP/8;
                              }
                        }

                  }           // SCALE_BILINEAR

                  else if (scale_type == SCALE_SUBSAMP)
                  {
                        int y=0;                // starting here
                        unsigned char *y_off0 = source_data; // + (ysoff * old_width * BPP/8);
                        int y_off0_inc = Factor * old_width * BPP/8;

                        while ( y < target_height)
                        {
                              target_data = data + (y * target_width * BPP/8);
//                            int y_off0 = ((y * Factor)+ysoff) * old_width * BPP/8;
                              unsigned char *pix0 = y_off0; // + (xsoff * BPP/8);
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

                  }     // SCALE_SUBSAMP

            }
            else  //factor < 1
            {

                  for (int j = 0; j < target_height; j++)
                  {
                        int y_offset = (j * old_height / target_height) * old_width;

                        for (int i = 0; i < target_width; i++)
                        {
                              memcpy( target_data,
                                    source_data + BPP/8*(y_offset + ((i * old_width )/ target_width)),
                                    BPP/8 );
                              target_data += BPP/8;
                        }
                  }

            }

      return true;

}



bool ChartBaseBSB::GetAndScaleData(unsigned char **ppn, wxRect& source, int s_width,
                                    int d_width, ScaleTypeEnum scale_type)
{
      unsigned char *s_data;

      float factor = ((float)s_width)/((float)d_width);

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


      int cs1 = s_width/d_width;

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

            // Calculate scountre = 2 * log2(factor)
            while((a & 0x01) == 0)
            {
                  a=a>>1;
                  b++;
            }

            int scounter;
            scounter = b*2;


//    Allocate a working buffer based on scale factor
//          s_data = (unsigned char *) x_malloc( (source.width) * ((int)factor + 9) * BPP/8 );


            if(scale_type == SCALE_BILINEAR)
            {
                s_data = (unsigned char *) x_malloc( (source.width) * ((int)factor + 9) * BPP/8 ); // work buffer
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
                        GetChartBits(s1, s_data, 1, get_bits_submap);
                        yr += Factor;

//      Take a peek into the message queue for mouse movements.
//      If found, abort this render operation
//      Profuse apologies for the direct hardware hack....
#ifdef __WXMSW__
    MSG msg;
    if(::PeekMessage(&msg, (HWND)0,  WM_MOUSEFIRST, WM_MOUSELAST,  PM_NOREMOVE))
    {
        free( s_data );
        return false;
    }
#endif
#ifdef __WXX11__
XEvent *xevt = new XEvent;
if(XCheckTypedEvent( wxGlobalDisplay(), MotionNotify, xevt))
  {
      free(s_data);
      return false;
  }
  delete xevt;
#endif

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
                        s_data = (unsigned char *) x_malloc( (Size_X) * ((int)factor + 9) * BPP/8 ); // work buffer
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
                              GetChartBits(s1, s_data, 1, get_bits_submap);
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
                        s_data = (unsigned char *) x_malloc( (source.width) * ((int)factor + 9) * BPP/8 ); // work buffer
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
                              GetChartBits(s1, s_data, 1, get_bits_submap);
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
      else  //factor < 1
      {
            //    Seems safe enough to read all the required data
            s_data = (unsigned char *) x_malloc( (source.x + source.width) * source.height * BPP/8 );

            GetChartBits(source, s_data, 1, get_bits_submap);

            for (int j = 0; j < target_height; j++)
            {
                  int y_offset = (j * old_height / target_height) * old_width;

                  for (int i = 0; i < target_width; i++)
                  {
                        memcpy( target_data,
                                s_data + BPP/8*(y_offset + ((i * old_width )/ target_width)),
                                BPP/8 );
                        target_data += BPP/8;
                  }
            }

      }

      free(s_data);

      return true;

}




bool ChartBaseBSB::GetChartBits(wxRect& source, unsigned char *pPix, int mode, int sub_samp)
{

//      int ix;
      int iy;
#define FILL_BYTE 0

//    Decode the KAP file RLL stream into image pPix

      unsigned char *pCP;
//      unsigned char *pSP;
      pCP = pPix;

      iy = source.y;

      while (iy < source.y + source.height)
      {

            if((iy >= 0) && (iy < Size_Y))
            {

                  if(mode == 0)
                  {
                        /*
                        unsigned char *pX = 0;        // cause GPF

                        pSP = pCP;
                        for(ix=source.x; ix<source.x + source.width ; ix++)
                        {
                              if((ix > 0) && (ix < Size_X))
                              {
                                    int j = *pX++;
                                    *pSP++ = RGBPallete[j][0];
                                    *pSP++ = RGBPallete[j][1];
                                    *pSP++ = RGBPallete[j][2];
                              }
                              else
                              {
                                    pSP += BPP/8;
                                    pX++;
                              }
                        }
                        */
                  }

                  else              // mode 1
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
                                                source.x + source.width - Size_X);
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





wxImage *ChartBaseBSB::ShrinkImage( wxImage *src_image, int Factor )
{


    int old_height = src_image->GetHeight(),
         old_width  = src_image->GetWidth();

    int width = old_width / Factor ;
    int height = old_height / Factor ;

      char unsigned *data = (unsigned char *) x_malloc( width*height*BPP/8 );

    wxImage *psi = new wxImage( width , height, data, false );


      int scounter;
      if(Factor == 2)
            scounter = 2;
      else if(Factor == 4)
            scounter = 4;
      else if(Factor == 8)
            scounter = 8;
      else if(Factor == 16)
            scounter = 16;

      assert(Factor < 17);

    char unsigned *source_data = src_image->GetData();
    char unsigned *target_data = data;
      unsigned char *pixel;
      int y_offset;
//    int y3 = old_width * BPP/8;

    for (int y = 0; y < height; y++)
    {
        int y_off0 = (y * Factor) * old_width;
            for (int x = 0; x < width; x++)
        {
            unsigned int avgRed = 0 ;
            unsigned int avgGreen = 0;
            unsigned int avgBlue = 0;
//            unsigned int counter = 0 ;
            unsigned char *pix0 = source_data + BPP/8 * ( x * Factor ) ;
                  y_offset = y_off0;

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
                        y_offset += old_width;
            }

                  *(target_data++) = avgRed >> scounter;
            *(target_data++) = avgGreen >> scounter;
            *(target_data++) = avgBlue >> scounter;
        }
    }


    return psi;
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


static wxMutex s_mutexProtectingIFS_Bitmap;
//-----------------------------------------------------------------------
//    Get a BSB Scan Line Using Cache
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
            int thisline_size = pline_table[y+1] - pline_table[y] ;

            wxMutexLocker lock(s_mutexProtectingIFS_Bitmap);

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

                  if( iPixel + nRunCount + 1 > Size_X )
                        nRunCount = Size_X - iPixel - 1;


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

      unsigned char *pCLast = xtemp_line + (xl - 1);
      unsigned char *prgb_last = pLineBuf + ((xl - 1)-xs) * BPP/8;

      rgbval = (int)(pPalette[*pCLast]);        // last pixel
      unsigned char a = rgbval & 0xff;
      *prgb_last++ = a;
      a = (rgbval >> 8) & 0xff;
      *prgb_last++ = a;
      a = (rgbval >> 16) & 0xff;
      *prgb_last = a;

      return 1;
}





#if 0
/************************************************************************/
/*                          BSBReadScanline()                           */
/************************************************************************/
int   ChartBaseBSB::BSBReadScanline( unsigned char *LineBuf,
                                             int y, int xs, int xl,
                                            int mode, int sub_samp)


{


      assert (y >= 0);
      assert (xl >= 0);

    int           nLineMarker = 0, nValueShift, iPixel = 0;
    unsigned char byValueMask, byCountMask;
    unsigned char byNext;
      unsigned char *lp;



 int thisline_size = pline_table[y+1] - pline_table[y] ;

      if((0/*thisline_size > ifs_bufend - ifs_lp - 1*/) ||
         (pline_table[y] < ifs_file_offset) ||
         (pline_table[y] + thisline_size > ifs_file_offset + ifs_bufsize))
      {
            ifs_bitmap->SeekI(pline_table[y], wxFromStart);
            ifs_bitmap->Read(ifs_buf, ifs_bufsize);
//          ifs_lp = ifs_buf;
            ifs_file_offset = pline_table[y];
      }

      lp = pline_table[y] - ifs_file_offset + ifs_buf;
//    lp = ifs_lp;
//    ifs_lp += thisline_size;


/* -------------------------------------------------------------------- */
/*      Read the line number.  Pre 2.0 BSB seemed to expect the line    */
/*      numbers to be zero based, while 2.0 and later seemed to         */
/*      expect it to be one based, and for a 0 to be some sort of       */
/*      missing line marker.                                            */
/* -------------------------------------------------------------------- */
    do {
        byNext = *lp++;                                     //ifs->GetC();
        nLineMarker = nLineMarker * 128 + (byNext & 0x7f);
    } while( (byNext & 0x80) != 0 );

/*HACKHACK
    if( nLineMarker != nScanline
        && nLineMarker != nScanline + 1 )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Got scanline id %d when looking for %d.",
                  nLineMarker, nScanline+1 );
        return FALSE;
    }
*/
/* -------------------------------------------------------------------- */
/*      Setup masking values.                                           */
/* -------------------------------------------------------------------- */
    nValueShift = 7 - nColorSize;
    byValueMask = (((1 << nColorSize)) - 1) << nValueShift;
    byCountMask = (1 << (7 - nColorSize)) - 1;

/* -------------------------------------------------------------------- */
/*      Read and expand runs.                                           */
/* -------------------------------------------------------------------- */

//    High speed method, using palette pointer to
//    fully expand line to RGB values into the ScanlineBuf
//    Be careful here...

      unsigned char *prgb = LineBuf;
      if(mode == 1)
      {
/*
#ifdef __WXMSW__
            int * pPalette = (int *)&BGRPallete[0][0];
#else
            int * pPalette = (int *)&RGBPallete[0][0];
#endif
   */
      while( ((byNext = *lp++) != 0 ) && (iPixel < xl))
            {
                  int   nPixValue;
                  int     nRunCount;
                  nPixValue = (byNext & byValueMask) >> nValueShift;

                  nRunCount = byNext & byCountMask;

                  while( (byNext & 0x80) != 0 )
                  {
                        byNext = *lp++;
                        nRunCount = nRunCount * 128 + (byNext & 0x7f);
                  }

                  if( iPixel + nRunCount + 1 > Size_X )
                        nRunCount = Size_X - iPixel - 1;


                  if( iPixel + nRunCount + 1 > xl)
                        nRunCount = xl - iPixel - 1;

                  int rgbval = (int)(pPalette[nPixValue]);

//    WXMSW Optimization, using inline _ASM code
#ifndef __WXMSW__


                  for( int i = 0; i < nRunCount+1; i++ )
                  {
//    Store pixels in the line buffer only if (xs =< iPixel =< xl)
                        if(iPixel >= xs)
                        {
                              *((int *)prgb) = rgbval;
                              prgb+=BPP/8;
                        }

                        iPixel++;
                        if(iPixel >= xl)
                              break;
                  }


#else
      /*
      Register usage:
            edi         prgb
            ecx         i counter
            edx         iPixel
            ebx         rgbval
            eax         xs

      */
/*
      _asm
        {
                  mov         edi,[prgb];
                  mov         ebx,[rgbval];
                  mov         ecx,[nRunCount];
                  inc         ecx;
                  mov         edx,[iPixel];
                  mov         eax,[xl];

        deloop:
                  mov         [edi], ebx;
                  add         edi,BPP/8;
                  inc         edx;
                  cmp         edx,eax;
                  jge         loop_dun;
                  loop  deloop;

        loop_dun:
                  mov         [iPixel],edx;
                  mov         [prgb],edi;
        }
*/

      _asm
        {
                  mov         edi,[prgb];
                  mov         ebx,[rgbval];
                  mov         ecx,[nRunCount];
//                inc         ecx;
                  mov         edx,[iPixel];
                  mov         eax,[xs];

                  cmp         ecx, 0;
                  jz          loop_dun;

        deloop:
                  cmp         edx,eax;
                  jae         over_skip_start;
                  inc         edx;
                  loop  deloop;
                  jmp         loop_dun;

        over_skip_start:

                  mov         [edi], ebx;
                  add         edi,BPP/8;
                  inc         edx;
                  loop  over_skip_start;

        loop_dun:
                  cmp         edx,eax;
                  jb          over_end;

                  mov         [edi], bl;
                  inc         edi;
                  mov         [edi], bh;
                  inc         edi;
                  shr         ebx, 16;
                  mov         [edi], bl;
                  inc         edi;
        over_end:
                  inc         edx;
                  mov         [iPixel],edx;
                  mov         [prgb],edi;
        } // _ASM




#endif  //__MSW__

            }     //while


      }     // if High Speed





      else        // Do low speed
      {
            while( ((byNext = *lp++) != 0 ) && (iPixel < xl))
            {
                  int   nPixValue;
                  int     nRunCount;

                  nPixValue = (byNext & byValueMask) >> nValueShift;

                  nRunCount = byNext & byCountMask;

                  while( (byNext & 0x80) != 0 )
                  {
                        byNext = *lp++;
                        nRunCount = nRunCount * 128 + (byNext & 0x7f);
                  }

                  if( iPixel + nRunCount + 1 > Size_X )
                        nRunCount = Size_X - iPixel - 1;

             for( int ip = 0; ip < nRunCount+1; ip++ )
               {
                     if(iPixel >= xs)
                        LineBuf[iPixel++] = nPixValue;
               }


//                memset(&LineBuf[iPixel], nPixValue, nRunCount+1);
//                iPixel += nRunCount+1;
            }

/* -------------------------------------------------------------------- */
/*      For reasons that are unclear, some scanlines are exactly one    */
/*      pixel short (such as in the BSB 3.0 354704.KAP product from     */
/*      NDI/CHS) but are otherwise OK.  Just add a zero if this         */
/*      appear to have occured.                                         */
/* -------------------------------------------------------------------- */
            if( iPixel == Size_X - 1 )
                  LineBuf[iPixel++] = 0;
      }     //else low speed

 //if((prgb - LineBuf) > (xl - xs)*BPP/8)
//     int yyg = 9;


// int thisline_size1 = pline_table[y+1] - pline_table[y] ;
//if(thisline_size != thisline_size1)
//     int r=0;

      return TRUE;                                    //iPixel == nXSize;
}

#endif


int  *ChartBaseBSB::GetPalettePtr(ColorScheme cs)
{

      if(palette_direction == PaletteFwd)
            return (int *)(pPalettes[cs]->FwdPalette);
      else
            return (int *)(pPalettes[cs]->RevPalette);
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
//    char zone[20];

      int e0xmax = 0;
      int e0ymax = 0;

//    Calculate the longitude/pixel rate, for later zone estimation

      float lonmin = 179;
      float lonmax = -179;
      float latmin = 90.;
      float latmax = -90.;

      int plonmin = 100000;
      int plonmax = 0;
      int platmin = 100000;
      int platmax = 0;

      for(n=0 ; n<nRefpoint ; n++)
      {
            //    Longitude
            if(pRefTable[n].lnr > lonmax)
            {
                  lonmax = pRefTable[n].lnr;
                  plonmax = (int)pRefTable[n].xr;
            }
            if(pRefTable[n].lnr < lonmin)
            {
                  lonmin = pRefTable[n].lnr;
                  plonmin = (int)pRefTable[n].xr;
            }

            //    Latitude
            if(pRefTable[n].ltr < latmin)
            {
                  latmin = pRefTable[n].ltr;
                  platmin = (int)pRefTable[n].yr;
            }
            if(pRefTable[n].ltr > latmax)
            {
                  latmax = pRefTable[n].ltr;
                  platmax = (int)pRefTable[n].yr;
            }


      }


      ppd_lon_1x = (plonmax - plonmin)/(lonmax - lonmin);
      ppd_lat_1x = fabs((platmax - platmin)/(latmax - latmin));        // always +ve, correct in canvas


      long0 = (lonmin +lonmax)/2.;

//    Calculate the northing/easting for the given ref points

//    double lat, lon;
      for(n=0 ; n<nRefpoint ; n++)
      {
            float nf, ef;

            DegToUTM(pRefTable[n].ltr, pRefTable[n].lnr, NULL,
                  &ef, &nf, long0);

            pRefTable[n].easting = ef;
            pRefTable[n].northing = nf;

//          sscanf(zone, "%d", &izone);

//          UTMtoDeg(long0, 0, pRefTable[n].easting, pRefTable[n].northing, &lat, &lon);
      }



//          Build the Control Point Structure, etc

            cPoints.count = nRefpoint;

            cPoints.e1 = (double *)x_malloc(nRefpoint * sizeof(double));
            cPoints.n1 = (double *)x_malloc(nRefpoint * sizeof(double));
            cPoints.e2 = (double *)x_malloc(nRefpoint * sizeof(double));
            cPoints.n2 = (double *)x_malloc(nRefpoint * sizeof(double));

            for(n=0 ; n<nRefpoint ; n++)
            {
                  cPoints.e1[n] = pRefTable[n].xr;
                  cPoints.n1[n] = pRefTable[n].yr;
                  cPoints.e2[n] = pRefTable[n].easting;
                  cPoints.n2[n] = pRefTable[n].northing;
            }


            E12 = (double *)x_malloc(16 * sizeof(double));
            N12 = (double *)x_malloc(16 * sizeof(double));
            E21 = (double *)x_malloc(16 * sizeof(double));
            N21 = (double *)x_malloc(16 * sizeof(double));

//    Changelog....
//    2/7/05 Explorer Abacos AB015_1 has 12 points.
//          If use order=3, results in non-linear x/lon conversions
//                So, force to order = 2.

//  2/16/05 Iteratively try all possible orders for best fit

//    2/18/05 Back to the old way....sigh

            if(nRefpoint > 15)            //12
                  cPoints.order = 3;
            else
                  cPoints.order = 2;

            if(nRefpoint <= 8)
                  cPoints.order = 1;

            compute_georef_equations(&cPoints, E12, N12,
                        E21, N21);

            cPoints.status = 1;

//    Check errors
            int ord;

            int y = Size_Y/2;

            int x = 0;
            int dx = Size_X/50;
            int x1, y1;

            double lat, lon;


            while(x < Size_X)
            {
                  pix_to_latlong(x,y, &lat, &lon);
                  latlong_to_pix(lat, lon, x1, y1);

                  e0xmax = __max(e0xmax, abs(x-x1));
                  e0ymax = __max(e0ymax, abs(y-y1));

                  x += dx;
            }
            if((e0ymax < 5) && (e0xmax < 5))
                  goto found_order;


 //         Try iteratively all orders...

            int exmax[4];
            int eymax[4];

            ord = 1;
            while(ord <= 3)
            {
                  cPoints.order = ord;
                  compute_georef_equations(&cPoints, E12, N12,
                              E21, N21);

                  cPoints.status = 1;


//    Check errors
                  int y = Size_Y/2;

                  int x = 0;
                  int dx = Size_X/50;
                  int x1, y1;

                  double lat, lon;

                  exmax[ord] = 0;
                  eymax[ord] = 0;

                  while(x < Size_X)
                  {
                        pix_to_latlong(x,y, &lat, &lon);
                        latlong_to_pix(lat, lon, x1, y1);

                        exmax[ord] = __max(exmax[ord], abs(x-x1));
                        eymax[ord] = __max(eymax[ord], abs(y-y1));

                        x += dx;
                  }

                  if((eymax[ord] < 5) && (exmax[ord] < 5))
                        goto found_order;

                  ord++;
            }

//    if arrive here, bad solution all around, so give up and use ord = 3
            cPoints.order = 3;


found_order:




//          Calculate and store errors

      double xpl_err_max = 0;
      double ypl_err_max = 0;
      double xpl_err_max_feet, ypl_err_max_feet;

      for(i=0 ; i<nRefpoint ; i++)
      {
            pix_to_latlong((int)pRefTable[i].xr, (int)pRefTable[i].yr,
                        &elt, &elg);
            pRefTable[i].ypl_error = elt - pRefTable[i].ltr;
            pRefTable[i].xpl_error = elg - pRefTable[i].lnr;

            if(fabs(pRefTable[i].ypl_error) > fabs(ypl_err_max))
                  ypl_err_max = pRefTable[i].ypl_error;
            if(fabs(pRefTable[i].xpl_error) > fabs(xpl_err_max))
                  xpl_err_max = pRefTable[i].xpl_error;
      }

      xpl_err_max_feet = fabs(xpl_err_max * 60 * 5280 * 1.15);
      ypl_err_max_feet = fabs(ypl_err_max * 60 * 5280 * 1.15);


      if(fabs(xpl_err_max) > (fabs(lonmax - lonmin) * .01))
            return(1);
      if(fabs(ypl_err_max) > (fabs(latmax - latmin) * .01))
            return(1);


      return(0);

}

//-------------------------------------------------------------------------------
//    Threaded ChartBaseBSB Implementation
//-------------------------------------------------------------------------------

ThreadChartBaseBSB::ThreadChartBaseBSB(ChartBase *pCh)
{
      ChartFileName = *(pCh->pFullPath);

      wxLogMessage(" Thread::ctor File name...%s", ChartFileName.c_str());
}



void* ThreadChartBaseBSB::Entry()
{
      wxLogMessage("Thread::Entry  Entry()");
      wxLogMessage("Thread::Entry  Do Stuff");

//    wxLogMessage("Thread::Entry  Calling Exit()");

//    Exit(0);

      return 0;               // for compiler

}


void ThreadChartBaseBSB::OnExit()
{
      wxLogMessage("Thread::OnExit()");

}

/******************************************************************************
 * $Id: chartimg.h,v 1.5 2007/03/02 02:04:49 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  ChartBaseBSB and Friends
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
 * $Log: chartimg.h,v $
 * Revision 1.5  2007/03/02 02:04:49  dsr
 * Cleanup
 *
 *
 */


#ifndef _CHARTIMG_H_
#define _CHARTIMG_H_


#include "chartbase.h"
#include "georef.h"
#include "s52s57.h"

#ifdef __WXMSW__
      #include "wx/msw/dib.h"
#endif


class WXDLLEXPORT ChartImg;

//-----------------------------------------------------------------------------
//    Constants, etc.
//-----------------------------------------------------------------------------

typedef enum PaletteDir
{
      PaletteFwd,
      PaletteRev
};

//-----------------------------------------------------------------------------
//    Fwd Refs
//-----------------------------------------------------------------------------

class ChartKAP;
class ViewPort;
class PixelCache;
class wxBitmapo;

class wxFileInputStream;

//-----------------------------------------------------------------------------
//    Helper classes
//-----------------------------------------------------------------------------

class Refpoint
{
public:
      int         bXValid;
      int         bYValid;
      float       xr;
      float       yr;
      float       ltr;
      float       lnr;
      double      northing;
      double      easting;
      float       xpl_error;
      float       xlp_error;
      float       ypl_error;
      float       ylp_error;

};


class Plypoint
{
public:
      float ltp;
      float lnp;
};




class CachedLine
{
public:
      int               xstart;
      int               xlength;
      unsigned char     *pPix;
      bool              bValid;
};

#define PALETTE_SIZE 33
class Palette
{
public:
      unsigned char FwdPalette[PALETTE_SIZE][4];
      unsigned char RevPalette[PALETTE_SIZE][4];
};

// ----------------------------------------------------------------------------
// ChartBaseBSB
// ----------------------------------------------------------------------------

class  ChartBaseBSB     :public ChartBase
{
public:
      //    Public methods

      ChartBaseBSB();
      virtual ~ChartBaseBSB() = 0;

      //    Accessors
      virtual ThumbData *GetThumbData(int tnx, int tny, float lat, float lon);
      virtual ThumbData *GetThumbData() {return pThumbData;}

      float GetNativeScale(){return (float)Chart_Scale;}
      float GetChartSkew(){return Chart_Skew;}
      int GetSize_X(){ return Size_X;}
      int GetSize_Y(){ return Size_Y;}
      double GetPPM(){ return ppm_avg;}
      bool IsCacheValid(){ return cached_image_ok; }
      void InvalidateCache(){cached_image_ok = 0;}
      Plypoint *GetPlyTable(){ return pPlyTable;}
      int       GetnPlypoints(){ return nPlypoint;}


      virtual InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );
      virtual void InvalidateLineCache();

      virtual void latlong_to_pix(double lat, double lon, int &pixx, int &pixy);
      virtual void latlong_to_pix_vp(double lat, double lon, int &pixx, int &pixy, ViewPort& vp);
      virtual void pix_to_latlong(int pixx, int pixy, double *lat, double *lon);
      virtual void vp_pix_to_latlong(ViewPort& vp, int pixx, int pixy, double *lat, double *lon);

      void RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type);

      virtual void SetVPParms(ViewPort *vpt);

      void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion  *pValidRegion);

      virtual void GetChartExtent(Extent *pext);

      PaletteDir GetPaletteDir(void);



      void SetColorScheme(ColorScheme cs, bool bApplyImmediate);

      int  *GetPalettePtr(ColorScheme);


//    Public interface for Alternate thread renderer
      bool GetViewIntoPrivatePixelCache( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type );
      wxRect &GetCurrentRsrc(){return Rsrc;}
      bool AssumeAlternateCacheParms();
      PixelCache        *pPixCache;
      PixelCache        *pPixCacheAlternate;
      wxRect            cache_rect_alt;
      wxRect            cache_rect_scaled_alt;

      //Todo  Convert to accessors
      Plypoint    *pPlyTable;
      int         nPlypoint;

protected:


//    Methods
      void CreatePaletteEntry(char *buffer, int palette_index);

      virtual wxBitmap *CreateThumbnail(int tnx, int tny);
      virtual bool GetChartBits( wxRect& source, unsigned char *pPix, int mode, int sub_samp );
      int   BSBGetScanline( unsigned char *,   int, int, int, int);

      virtual bool GetAndScaleData(unsigned char **ppn,
                                   wxRect& source, int s_width, int d_width, ScaleTypeEnum scale_type);

      virtual bool ScaleData(unsigned char *pPix, unsigned char **ppn,
                             wxRect& source, int s_width, int d_width,
                             ScaleTypeEnum scale_type);


      bool GetViewUsingCache( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type );
      bool GetView( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type );


      virtual int ReadBSBHdrLine( wxFileInputStream*, char *, int );
      virtual int AnalyzeRefpoints(void);
      virtual wxImage *ShrinkImage(wxImage *src_image, int Factor );
      void UpdateViewPortParms(ViewPort &vp);

      InitReturn PreInit( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );
      InitReturn PostInit(void);



//    Protected Data

      int         Size_X;                 // Chart native pixel dimensions
      int         Size_Y;


      wxRect      cache_rect;
      wxRect      cache_rect_scaled;
      bool        cached_image_ok;
      ScaleTypeEnum cache_scale_method;


      wxRect      Rsrc;           // Current chart source rectangle


      Refpoint    *pRefTable;
      int         nRefpoint;

      float       long0;

      int         nColorSize;
      int         *pline_table;           // pointer to Line offset table

      double      xpix_to_longitude_coef[5];
      double      ypix_to_latitude_coef[5];
      double      xlongitude_to_pix_coef[5];
      double      ylatitude_to_pix_coef[5];

      CachedLine  *pLineCache;

      wxFileInputStream *ifs_hdr;
      wxFileInputStream *ifs_bitmap;

      wxString          *pBitmapFilePath;

      unsigned char     *ifs_buf;
      unsigned char     *ifs_bufend;
      int               ifs_bufsize;
      unsigned char     *ifs_lp;
      int               ifs_file_offset;

      GeoRef            cPoints;
      double            *E12, *E21, *N12, *N21;

      float             ppd_lon_1x;
      float             ppd_lat_1x;


      Palette           *pPalettes[N_COLOR_SCHEMES];

//    Integer digital scale value above which bilinear scaling is not allowed,
//      and subsampled scaling must be performed
      int         m_bilinear_limit;

      bool        bUseLineCache;
      float       Chart_Skew;

      float       LonMax;
      float       LonMin;
      float       LatMax;
      float       LatMin;

      int         *pPalette;
      PaletteDir  palette_direction;

      bool        bGeoErrorSent;

      double      ppm_avg;              // Calculated true scale factor of the 1X chart,
                                        // pixels per meter
};


// ----------------------------------------------------------------------------
// ChartKAP
// ----------------------------------------------------------------------------

class  ChartKAP : public ChartBaseBSB
{
public:
//    Methods
      ChartKAP();
      ~ChartKAP();

      InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );//Initialize a BSB 3.x Chart


};

// ----------------------------------------------------------------------------
// ChartGEO
// ----------------------------------------------------------------------------

class  ChartGEO : public ChartBaseBSB
{
public:
//    Methods
      ChartGEO();
      ~ChartGEO();

      InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );


};

#endif

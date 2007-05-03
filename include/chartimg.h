/******************************************************************************
 * $Id: chartimg.h,v 1.6 2007/05/03 13:31:19 dsr Exp $
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
 * Revision 1.6  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
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



class WXDLLEXPORT ChartImg;

//-----------------------------------------------------------------------------
//    Constants, etc.
//-----------------------------------------------------------------------------

typedef enum PaletteDir
{
      PaletteFwd,
      PaletteRev
}_PaletteDir;

//-----------------------------------------------------------------------------
//    Fwd Refs
//-----------------------------------------------------------------------------

class ChartKAP;
class ViewPort;
class PixelCache;
class ocpnBitmap;

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
      float       latr;
      float       lonr;
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


class Palette
{
public:
    Palette();
    ~Palette();

    int *FwdPalette;
    int *RevPalette;
    int nFwd;
    int nRev;

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
      void GetSourceRect(wxRect *rect);


      virtual InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );
      virtual void InvalidateLineCache();
      virtual bool CreateLineIndex(void);

      virtual int latlong_to_pix(double lat, double lon, int &pixx, int &pixy);
      virtual int latlong_to_pix_vp(double lat, double lon, int &pixx, int &pixy, ViewPort& vp);
      virtual int pix_to_latlong(int pixx, int pixy, double *lat, double *lon);
      virtual int vp_pix_to_latlong(ViewPort& vp, int pixx, int pixy, double *lat, double *lon);

      void RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type);

      virtual void SetVPParms(ViewPort *vpt);

      void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion  *pValidRegion);

      virtual void GetChartExtent(Extent *pext);

      PaletteDir GetPaletteDir(void);


      void SetColorScheme(ColorScheme cs, bool bApplyImmediate);

      int  *GetPalettePtr(ColorScheme);

      bool InitializeBackgroundBilinearRender(ViewPort &VPoint);
      bool AbortBackgroundRender(void);
      bool ContinueBackgroundRender(void);
      bool FinishBackgroundRender(void);

      PixelCache        *pPixCache;

      //Todo  Convert to accessors
      Plypoint    *pPlyTable;
      int         nPlypoint;


protected:


//    Methods
      void CreatePaletteEntry(char *buffer, int palette_index);

      virtual wxBitmap *CreateThumbnail(int tnx, int tny);
      virtual bool GetChartBits( wxRect& source, unsigned char *pPix, int sub_samp );
      virtual int BSBGetScanline( unsigned char *pLineBuf, int y, int xs, int xl, int sub_samp);

      virtual bool GetAndScaleData(unsigned char **ppn,
                                   wxRect& source, int s_width, int d_width, ScaleTypeEnum scale_type);

      virtual bool ScaleData(unsigned char *pPix, unsigned char **ppn,
                             wxRect& source, int s_width, int d_width,
                             ScaleTypeEnum scale_type);


      bool GetViewUsingCache( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type );
      bool GetView( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type );


      virtual int BSBScanScanline(wxInputStream *pinStream);
      virtual int ReadBSBHdrLine( wxFileInputStream*, char *, int );
      virtual int AnalyzeRefpoints(void);
      void UpdateViewPortParms(ViewPort &vp);

      InitReturn PreInit( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );
      InitReturn PostInit(void);



//    Protected Data

      int         Size_X;                 // Chart native pixel dimensions
      int         Size_Y;
      int         Chart_DU;


      wxRect      cache_rect;
      wxRect      cache_rect_scaled;
      bool        cached_image_ok;
      ScaleTypeEnum cache_scale_method;


      wxRect      Rsrc;                   // Current chart source rectangle


      int         nRefpoint;
      int         m_i_ref_near_center;
      Refpoint    *pRefTable;

//      float       long0;

      int         nColorSize;
      int         *pline_table;           // pointer to Line offset table

      CachedLine  *pLineCache;

      wxFileInputStream     *ifs_hdr;
      wxFileInputStream     *ifss_bitmap;
      wxBufferedInputStream *ifs_bitmap;

      wxString          *pBitmapFilePath;

      unsigned char     *ifs_buf;
      unsigned char     *ifs_bufend;
      int               ifs_bufsize;
      unsigned char     *ifs_lp;
      int               ifs_file_offset;
      int               nFileOffsetDataStart;
      int               m_nLineOffset;

      GeoRef            cPoints;

      double            wpx[12], wpy[12], pwx[12], pwy[12];     // Imbedded georef coefficients
      int               wpx_type, wpy_type, pwx_type, pwy_type;
      int               n_wpx, n_wpy, n_pwx, n_pwy;
      bool              bUseGeoRef;
      bool              bHaveImbeddedGeoref;
      double            m_cph;

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

      //    Storage for background render machine

      PixelCache    *pPixCacheBackground;
      unsigned char *background_work_buffer;
      unsigned char *br_target_data;

      int       br_y_source;
      int       br_target_height;
      int       br_target_width;
      int       br_scounter;
      int       br_Factor;
      int       br_get_bits_submap;
      int       br_target_y;
      int       bwb_size;
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

      InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );//Initialize a BSB 2.x+ Chart


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

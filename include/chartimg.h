/******************************************************************************
 * $Id: chartimg.h,v 1.18 2009/11/18 01:26:42 bdbcat Exp $
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
 * Revision 1.18  2009/11/18 01:26:42  bdbcat
 * 1.3.5 Beta 1117
 *
 * Revision 1.17  2009/09/30 02:30:34  bdbcat
 * Another correction for IDL crossing
 *
 * Revision 1.16  2009/09/18 02:12:12  bdbcat
 * Add support for DTM field in BSB charts
 *
 * Revision 1.15  2009/06/28 02:02:29  bdbcat
 * Implement Datum transforms.
 *
 * Revision 1.14  2009/06/25 02:37:15  bdbcat
 * Normalize charts near International Dateline.
 *
 * Revision 1.13  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.12  2008/08/26 13:49:53  bdbcat
 * Better color scheme support
 *
 * Revision 1.11  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
 *
 * Revision 1.10  2008/04/10 00:58:04  bdbcat
 * Change to opncpnPalette vs Pelette
 *
 * Revision 1.9  2008/01/10 03:38:55  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.7  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
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


typedef enum BSB_Color_Capability
{
    COLOR_RGB_DEFAULT = 0,                   // Default corresponds to bsb entries "RGB"
    DAY,
    DUSK,
    NIGHT,
    NIGHTRED,
    GRAY,
    PRC,
    PRG,
    N_BSB_COLORS
}_BSB_Color_Capability;

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

class opncpnPalette
{
    public:
        opncpnPalette();
        ~opncpnPalette();

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
      virtual bool UpdateThumbData(float lat, float lon);

      int GetNativeScale(){return m_Chart_Scale;}
      double GetNormalScaleMin(double canvas_scale_factor);
      double GetNormalScaleMax(double canvas_scale_factor);
      double GetClosestValidNaturalScalePPM(double target_scale);

      double GetChartSkew(){return Chart_Skew;}
      int GetSize_X(){ return Size_X;}
      int GetSize_Y(){ return Size_Y;}
      double GetPPM(){ return m_ppm_avg;}
      bool IsCacheValid(){ return cached_image_ok; }
      void InvalidateCache(){cached_image_ok = 0;}
      void GetSourceRect(wxRect *rect);


      virtual InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );
      virtual void InvalidateLineCache();
      virtual bool CreateLineIndex(void);

      virtual int latlong_to_pix(double lat, double lon, int &pixx, int &pixy);
      virtual int latlong_to_pix_vp(double lat, double lon, int &pixx, int &pixy, ViewPort& vp);
      virtual int pix_to_latlong(int pixx, int pixy, double *lat, double *lon);
      virtual int vp_pix_to_latlong(ViewPort& vp, int pixx, int pixy, double *lat, double *lon);

      bool RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type);

      virtual void SetVPParms(ViewPort *vpt);

      virtual bool AdjustVP(ViewPort &vp_last, ViewPort &vp_proposed);

      virtual bool IsRenderDelta(ViewPort &vp_last, ViewPort &vp_proposed);

      void GetValidCanvasRegion(const ViewPort& VPoint, wxRegion  *pValidRegion);

      virtual bool GetChartExtent(Extent *pext);


      void SetColorScheme(ColorScheme cs, bool bApplyImmediate);

      PaletteDir GetPaletteDir(void);
      int  *GetPalettePtr(BSB_Color_Capability);

      bool InitializeBackgroundBilinearRender(ViewPort &VPoint);
      bool AbortBackgroundRender(void);
      bool ContinueBackgroundRender(void);
      bool FinishBackgroundRender(void);



protected:


//    Methods
      void CreatePaletteEntry(char *buffer, int palette_index);

      virtual wxBitmap *CreateThumbnail(int tnx, int tny, ColorScheme cs);
      virtual bool GetChartBits( wxRect& source, unsigned char *pPix, int sub_samp );
      virtual int BSBGetScanline( unsigned char *pLineBuf, int y, int xs, int xl, int sub_samp);

      virtual bool GetAndScaleData(unsigned char **ppn,
                                   wxRect& source, int s_width, wxRect& dest, ScaleTypeEnum scale_type);


      bool GetViewUsingCache( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type );
      bool GetView( wxRect& source, wxRect& dest, ScaleTypeEnum scale_type );


      virtual int BSBScanScanline(wxInputStream *pinStream);
      virtual int ReadBSBHdrLine( wxFileInputStream*, char *, int );
      virtual int AnalyzeRefpoints(void);
      virtual bool SetMinMax(void);

      void ComputeSourceRectangle(ViewPort &vp, wxRect *pSourceRect);

      InitReturn PreInit( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );
      InitReturn PostInit(void);



//    Protected Data
      PixelCache        *pPixCache;

      int         Size_X;                 // Chart native pixel dimensions
      int         Size_Y;
      int         m_Chart_DU;


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

      opncpnPalette     *pPalettes[N_BSB_COLORS];

      BSB_Color_Capability m_mapped_color_index;

//    Integer digital scale value above which bilinear scaling is not allowed,
//      and subsampled scaling must be performed
      int         m_bilinear_limit;


      bool        bUseLineCache;
      double      Chart_Skew;

      float       m_LonMax;
      float       m_LonMin;
      float       m_LatMax;
      float       m_LatMin;

      int         *pPalette;
      PaletteDir  palette_direction;

      bool        bGeoErrorSent;

      double      m_ppm_avg;              // Calculated true scale factor of the 1X chart,
                                        // pixels per meter

      double      m_raster_scale_factor;        // exact scaling factor for pixel oversampling calcs

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

      wxString  m_datum_str;
      int       m_datum_index;
      double    m_dtm_lat;
      double    m_dtm_lon;

      bool      m_bIDLcross;
      double    m_proj_lat;
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

      InitReturn Init( const wxString& name, ChartInitFlag init_flags, ColorScheme cs );


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

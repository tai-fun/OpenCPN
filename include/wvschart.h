/******************************************************************************
 * $Id: wvschart.h,v 1.2 2007/03/02 02:08:23 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  World Vector Shoreline (WVS) Chart Object
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
 * $Log: wvschart.h,v $
 * Revision 1.2  2007/03/02 02:08:23  dsr
 * Cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.4  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/02/23 01:28:01  dsr
 * Cleanup
 *
 *
 *
 */



#ifndef __WVSCHART_H__
#define __WVSCHART_H__


#include "chartbase.h"
// ----------------------------------------------------------------------------
// Useful Prototypes
// ----------------------------------------------------------------------------
extern "C" void toTM(float lat, float lon, float lat0, float lon0, float k0, double *x, double *y);

//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// WVSChart
//----------------------------------------------------------------------------
class WVSChart
{
public:
      WVSChart(wxWindow *parent, char * wvs_home_dir);
      ~WVSChart();

      void RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint);

private:
      wxString    *pwvs_home_dir;
      wxString    *pwvs_file_name;

      float       *plat_ray[360][180];
      float       *plon_ray[360][180];
      int         *pseg_ray[360][180];
      int         nseg[360][180];

      wxPoint     *ptp;
      int         cur_seg_cnt_max;

      bool        m_ok;


};

#endif

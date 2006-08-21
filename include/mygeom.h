/******************************************************************************
 * $Id: mygeom.h,v 1.1 2006/08/21 05:52:11 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  Triangulated Polygon Object
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
 * $Log: mygeom.h,v $
 * Revision 1.1  2006/08/21 05:52:11  dsr
 * Initial revision
 *
 * Revision 1.5  2006/07/28 20:47:50  dsr
 * Cleanup
 *
 * Revision 1.4  2006/06/02 02:06:57  dsr
 * Cleanup
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.3  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.2  2006/02/23 01:22:42  dsr
 * Cleanup
 *
 *
 *
 */


#ifndef __MYGEOM_H
#define __MYGEOM_H


#include "gpc.h"
#include <ogr_geometry.h>
#include "s52s57.h"

#define CURRENT_SENC_FORMAT_VERSION  106


class mygeom
{
public:

      mygeom(s57chart *ch);

      void develop_and_write_tristrips(Extent *pFullExtent, OGRPolygon *poly, FILE *ofs);
      void write_wkb_tristrips(Extent *pExt, gpc_tristrip *tristrip, FILE *ofs);
      void read_wkb_tristrips();
      gpc_tristrip *get_tristrips(int npt, pt* geoPt);



private:
      gpc_tristrip   *tristrip;
      s57chart       *parent;

};

/*
class polygroup
{
    public:
        int         nPolys;
        int         nCntr;
        double      **pvert_array;
        float       *pPolyGeo;
        int         *pnv_array;
        int         *pct_array;
        polygroup   *next;
};

*/



class PolyGroup
{
public:
    PolyGroup();
    ~PolyGroup();

    int             nPolys;
    int             nContours;
    int             *pn_vertex;             // pointer to array of poly vertex counts
    int             *pcontour_nvertex;      // pointer array of contour vertex counts

    double          **pvert_array;          // pointer to the array of poly vertices
    float           *pgroup_geom;           // pointer to Raw geometry, used for contour line drawing

    wxBoundingBox   *BBArray;               // Array of BBox for each poly

    PolyGroup       *ppg_next;              // next PolyGroup;
};





class PolyGeo
{
public:
    PolyGeo();
    ~PolyGeo();

    PolyGeo(unsigned char *polybuf, int nrecl, int index);                 // Build PolyGeo from SENC file record

    void develop_and_write_PolyGeo(OGRPolygon *poly, FILE *ofs);

    double Get_xmin(){ return xmin;}
    double Get_xmax(){ return xmax;}
    double Get_ymin(){ return ymin;}
    double Get_ymax(){ return ymax;}
    PolyGroup *Get_PolyGroup_head(){ return m_ppg_head;}



 private:
     int my_bufgets( char *buf, int buf_len_max );


    //  Data

     double         xmin, xmax, ymin, ymax;

     int            m_npoly_groups;
     PolyGroup      *m_ppg_head;                  // head of a PolyGroup chain
     PolyGroup      *ppg_last;

     char           *m_buf_head;
     char           *m_buf_ptr;                   // used to read passed SENC record
     int            m_nrecl;

};






#endif

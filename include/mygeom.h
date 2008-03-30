/******************************************************************************
 * $Id: mygeom.h,v 1.7 2008/03/30 23:28:29 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Tesselation of Polygon Object
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
 * Revision 1.7  2008/03/30 23:28:29  bdbcat
 * Cleanup/optimize
 *
 * Revision 1.6  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.5  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.4  2007/03/02 02:06:21  dsr
 * Convert to UTM Projection
 *
 * Revision 1.3  2006/10/01 03:24:40  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
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


#include <ogr_geometry.h>
#include "s52s57.h"

#define TESS_VERT   0                           // constants describing preferred tess orientation
#define TESS_HORZ   1

#define EQUAL_EPS 1.0e-7                        // tolerance value


//  nota bene  These definitions are identical to OpenGL prototypes
#define PTG_TRIANGLES                      0x0004
#define PTG_TRIANGLE_STRIP                 0x0005
#define PTG_TRIANGLE_FAN                   0x0006

//  Error Return Codes
#define ERROR_NO_DLL            1

//  Some external prototypes


//--------------------------------------------------------------------------------------------------
//
//      Internal data structures used for describing/rendering tesselated polygons
//
//--------------------------------------------------------------------------------------------------


class TriPrim
{
public:
        TriPrim();
        ~TriPrim();

        unsigned int type;                  // Type of triangle primitive
                                            //  May be PTG_TRIANGLES
                                            //         PTG_TRIANGLE_STRIP
                                            //         PTG_TRIANGLE_FAN

        int         nVert;
        double      *p_vertex;              //  Pointer to vertex array, x,y,x,y.....

        wxBoundingBox *p_bbox;

        TriPrim     *p_next;                // chain link
};



class PolyTriGroup
{
public:
        PolyTriGroup();
        ~PolyTriGroup();

        int             nContours;
        int             *pn_vertex;             // pointer to array of poly vertex counts
        float           *pgroup_geom;           // pointer to Raw geometry, used for contour line drawing

        TriPrim         *tri_prim_head;         // head of linked list of TriPrims

    private:
        int my_bufgets( char *buf, int buf_len_max );

};





//--------------------------------------------------------------------------------------------------
//
//      Tesselator Class
//
//--------------------------------------------------------------------------------------------------
class PolyTessGeo
{
    public:
        PolyTessGeo();
        ~PolyTessGeo();

        PolyTessGeo(unsigned char *polybuf, int nrecl, int index);      // Build this from SENC file record

        PolyTessGeo(OGRPolygon *poly, bool bSENC_SM,
            double ref_lat, double ref_lon,  bool bUseInternalTess);  // Build this from OGRPolygon

        int Write_PolyTriGroup( FILE *ofs);

        double Get_xmin(){ return xmin;}
        double Get_xmax(){ return xmax;}
        double Get_ymin(){ return ymin;}
        double Get_ymax(){ return ymax;}
        PolyTriGroup *Get_PolyTriGroup_head(){ return m_ppg_head;}
        int GetnVertexMax(){ return m_nvertex_max; }
        int     ErrorCode;


    private:
        int PolyTessGeoGL(OGRPolygon *poly, bool bSENC_SM, double ref_lat, double ref_lon);
        int PolyTessGeoTri(OGRPolygon *poly, bool bSENC_SM, double ref_lat, double ref_lon);
        int my_bufgets( char *buf, int buf_len_max );



    //  Data

        double         xmin, xmax, ymin, ymax;
        PolyTriGroup    *m_ppg_head;                  // head of a PolyTriGroup chain
        int             m_nvertex_max;                 // and computed max vertex count
                                                      // used by drawing primitives as
                                                      // optimization

        int             ncnt;
        int             nwkb;

        char           *m_buf_head;
        char           *m_buf_ptr;                   // used to read passed SENC record
        int            m_nrecl;



};

#endif

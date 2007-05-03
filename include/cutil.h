/******************************************************************************
 * $Id: cutil.h,v 1.3 2007/05/03 13:31:19 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  Extern C Linked Utilities
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
 * $Log: cutil.h,v $
 * Revision 1.3  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.2  2007/03/02 02:06:00  dsr
 * Cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.2  2006/06/02 02:06:04  dsr
 * MyPoint becomes double
 *
 * Revision 1.1  2006/05/19 19:37:07  dsr
 * Initial
 *
 */

#ifndef __CUTIL_H__
#define __CUTIL_H__



typedef struct  {
      double x;
      double y;
} MyPoint;

#ifdef __cplusplus
extern "C" int G_PtInPolygon(MyPoint *, int, float, float) ;
#endif /* __cplusplus */

int Intersect(MyPoint, MyPoint, MyPoint, MyPoint) ;
int CCW(MyPoint, MyPoint, MyPoint) ;

//-------------------------------------------------------------------------------------------------------
//  Cohen & Sutherland Line clipping algorithms
//-------------------------------------------------------------------------------------------------------
/*
*
* Copyright (C) 1999,2000,2001,2002,2003 Percy Zahl
*
* Authors: Percy Zahl <zahl@users.sf.net>
* additional features: Andreas Klust <klust@users.sf.net>
* WWW Home: http://gxsm.sf.net
*
*/

typedef enum { Visible, Invisible } ClipResult;

#ifdef __cplusplus
extern "C"  ClipResult cohen_sutherland_line_clip_d (double *x0, double *y0, double *x1, double *y1,
                                         double xmin_, double xmax_, double ymin_, double ymax_);
extern "C"  ClipResult cohen_sutherland_line_clip_i (int *x0, int *y0, int *x1, int *y1,
                                             int xmin_, int xmax_, int ymin_, int ymax_);
#endif


//      Replacement for round(x)???
#ifdef __cplusplus
extern "C"  double     round_msvc (double flt);
#endif /* __cplusplus */



#endif

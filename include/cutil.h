/******************************************************************************
 * $Id: cutil.h,v 1.1 2006/08/21 05:52:11 dsr Exp $
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
 * Revision 1.1  2006/08/21 05:52:11  dsr
 * Initial revision
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


/*
typedef struct  {
      int   left;
      int top;
      int   right;
      int bottom;
} MyRect;
*/

typedef struct  {
      double x;
      double y;
} MyPoint;



int Intersect(MyPoint, MyPoint, MyPoint, MyPoint) ;
int CCW(MyPoint, MyPoint, MyPoint) ;

#endif

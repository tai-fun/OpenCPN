/******************************************************************************
 * $Id: mygeom.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Optimized Polygon Object
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
 * $Log: mygeom.cpp,v $
 * Revision 1.1  2006/08/21 05:52:19  dsr
 * Initial revision
 *
 * Revision 1.8  2006/08/04 11:42:01  dsr
 * no message
 *
 * Revision 1.7  2006/07/28 20:36:17  dsr
 * Disable random segment selector, faults.
 *
 * Revision 1.6  2006/06/15 02:42:52  dsr
 * Inline assembly optimization
 *
 * Revision 1.5  2006/06/02 02:12:10  dsr
 * Optimize
 *
 * Revision 1.4  2006/05/28 01:45:56  dsr
 * Cleanup
 *
 * Revision 1.3  2006/05/28 00:51:29  dsr
 * Implement PolyGeo
 *
 * Revision 1.2  2006/05/19 19:10:07  dsr
 * Add POLYPOLY object definition creation and creation
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.6  2006/04/19 00:44:51  dsr
 * *** empty log message ***
 *
 * Revision 1.5  2006/03/16 03:08:15  dsr
 * Cleanup tabs
 *
 * Revision 1.4  2006/02/24 18:06:10  dsr
 * Fix Tristrip logic for degenerate(n = 3) case
 *
 * Revision 1.3  2006/02/23 01:43:15  dsr
 * Cleanup
 *
 *
 *
 */
// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include "wx/tokenzr.h"

#include "mygeom.h"

#include "dychart.h"

CPL_CVSID("$Id: mygeom.cpp,v 1.1 2006/08/21 05:52:19 dsr Exp $");

extern "C" void gpc_polygon_to_tristrip (gpc_polygon *, gpc_tristrip *);
extern "C" void gpc_free_polygon        (gpc_polygon     *polygon);
extern "C" void gpc_free_tristrip       (gpc_tristrip    *tristrip);

extern wxLog           *logger;


mygeom::mygeom(s57chart *ch)
{
      parent = ch;
}


void mygeom::write_wkb_tristrips(Extent *pEXT, gpc_tristrip *tristrip, FILE *ofs)
{
      double x, y;
      float sxmin, sxmax, symin, symax;
      float lat0, lon0;
//    float east, north;

//    Calculate wkb size
      int i,j;
      int nwkb = 0;
      for (i=0;i<tristrip->num_strips;i++)
      {
            nwkb += 4;                                            // nvertices
            nwkb += sizeof(float) * 2 * tristrip->strip[i].num_vertices;
      }

      unsigned char *bbuf = (unsigned char *)malloc(nwkb);
      float *vr = (float *)bbuf;

//    transcribe the vertex lists
   for (i=0;i<tristrip->num_strips;i++)
   {
            int *ir = (int *)vr;
            *ir = tristrip->strip[i].num_vertices;
            vr++;


            sxmax = -179.9;               // this strip BBox
            sxmin = 179.9;
            symax = 0.0;
            symin = 90.;


            x = tristrip->strip[i].vertex[0].x;
            y = tristrip->strip[i].vertex[0].y;

            *vr++ = x;
            *vr++ = y;
            lon0 = (pEXT->ELON + pEXT->WLON)/2;       //x;
            lat0 = (pEXT->NLAT + pEXT->SLAT)/2;       //y;

      for (j=1;j<tristrip->strip[i].num_vertices;j++)
        {
                x = tristrip->strip[i].vertex[j].x;
                y = tristrip->strip[i].vertex[j].y;


                        *vr++ = x;
                        *vr++ = y;
            }
   }


   fprintf(ofs, "Strips %d %d\n",  tristrip->num_strips, nwkb);


   fwrite(bbuf, 1, nwkb, ofs);
   fprintf(ofs, "\n");

   free(bbuf);
}


void mygeom::read_wkb_tristrips()
{
}


void mygeom::develop_and_write_tristrips(Extent *pFullExtent, OGRPolygon *poly, FILE *ofs)
{

      int nrings = poly->getNumInteriorRings() + 1;

//    BBox
      OGREnvelope Envelope;
      poly->getEnvelope(&Envelope);

      fprintf(ofs, "  POLYTRIS %d %f %f %f %f\n", nrings,
                  Envelope.MinX, Envelope.MinY, Envelope.MaxX, Envelope.MaxY);



//    Exterior Ring

      int nptx  = poly->getExteriorRing()->getNumPoints();
//    pt *geoPt= (pt*)poly->getExteriorRing()->getRawPoint();

      pt *geoPt = (pt*)malloc(nptx * sizeof(pt));
      pt *ppt = geoPt;
      for(int ip = 0 ; ip < nptx ; ip++)
      {
            OGRPoint p;
            poly->getExteriorRing()->getPoint(ip, &p);
            ppt->x = p.getX();
            ppt->y = p.getY();
            ppt++;
      }

//Todo could collapse below and above, replace geoPt[].x with calls to p.getX()
// test
      pt *ptn = NULL;
      ptn = (pt *)malloc(nptx * sizeof(pt));
      int ju = 0;
      int k = 0;
      if(nptx > 100)
      {
            for(int ip = 0 ; ip < nptx - 1 ; ip++)
            {
                  float dx = geoPt[ip].x - geoPt[ip+1].x;
                  float dy = geoPt[ip].y - geoPt[ip+1].y;
                  float l = sqrt(dx*dx + dy*dy);
                  float m = 10.0;         // meters
                  float mt = m * ((1/60.) / 1852);

                  if(l < mt)
                  {
                        ju++;
                        ptn[k].x = (geoPt[ip].x + geoPt[ip+1].x)/2;
                        ptn[k].y = (geoPt[ip].y + geoPt[ip+1].y)/2;
                        k++;
                        ip++;
                  }
                  else
                  {
                        ptn[k].x = geoPt[ip].x;
                        ptn[k].y = geoPt[ip].y;
                        k++;
                  }

            }
      }

      if(ju)
            tristrip = get_tristrips(k, ptn);
      else
          tristrip = get_tristrips(nptx, geoPt);

      write_wkb_tristrips(pFullExtent, tristrip, ofs);

      gpc_free_tristrip(tristrip);

      free(geoPt);
      delete tristrip;

      free(ptn);

//    Interior rings

      int nInterior = poly->getNumInteriorRings();
      for (int i=0; i<nInterior; i++)
      {
            int nptr   =      poly->getInteriorRing(i)->getNumPoints();
//          pt *geoPtr = (pt*)poly->getInteriorRing(i)->getRawPoint();

            pt *geoPtr = (pt*)malloc(nptr * sizeof(pt));
            pt *ppt = geoPtr;
            for(int ip = 0 ; ip < nptr ; ip++)
            {
                  OGRPoint p;
                  poly->getInteriorRing(i)->getPoint(ip, &p);
                  ppt->x = p.getX();
                  ppt->y = p.getY();
                  ppt++;
            }





            tristrip = get_tristrips(nptr, geoPtr);
            write_wkb_tristrips(pFullExtent, tristrip, ofs);

            gpc_free_tristrip(tristrip);

            free(geoPtr);

            delete tristrip;
      }
}



gpc_tristrip *mygeom::get_tristrips(int npt, pt* geoPt)
{
      gpc_tristrip *tristrip = new gpc_tristrip;

 //   Check for de-generate case of npt = 3
      if(3 == npt)
      {
        tristrip->num_strips = 1;

        gpc_vertex_list *strip0 = new gpc_vertex_list;
        strip0->num_vertices = 3;

        gpc_vertex *pv = (gpc_vertex *)malloc(npt * sizeof(gpc_vertex));

        double *pvd = (double *)pv;

        pt *geor = geoPt;
        double x, y;
        for(int i = 0 ; i < 3 ; i++)
        {
          x = geor->x;
          y = geor->y;

          *pvd++ = x;
          *pvd++ = y;

          geor++;
        }

        strip0->vertex = pv;
        tristrip->strip = strip0;

        return tristrip;

      }

//    Create the input structures for npt > 3

      gpc_polygon poly;


//    Poly vertices
      gpc_vertex_list   poly_vert;
      gpc_vertex *pv = (gpc_vertex *)malloc(npt * sizeof(gpc_vertex));

      poly_vert.num_vertices = npt-1;
      poly_vert.vertex = pv;
      double *pvd = (double *)pv;

      pt *geor = geoPt;
      double x, y;
      for(int i = 0 ; i < npt-1 ; i++)
      {
            x = geor->x;
            y = geor->y;

            *pvd++ = x;
            *pvd++ = y;

            geor++;
      }

      poly.num_contours = 1;
      poly.contour = &poly_vert;
      poly.hole = NULL;

      gpc_polygon_to_tristrip(&poly,tristrip);

//    Free the allocs
      for (int c= 0; c < poly.num_contours; c++)
            free(poly.contour[c].vertex);


//    gpc_free_polygon(&poly);

      return tristrip;
}




//extern "C" int triangulate_polygon(int, int[1], double (*)[2], int (*)[3]);
#include "triangulate.h"
extern "C" polyout *trapezate_polygon(int, int[1], double (*)[2]);


typedef struct {
  bool      aligned;
  int       v0;
  int       v1;
  int       source;
  int       dest;
  polyout   *psource;
  polyout   *pdest;
} neigh_def;


bool ispolysame(polyout *p1, polyout *p2)
{
    int i2;

    if(p1->nvert != p2->nvert)
        return false;

    int v10 = p1->vertex_index_list[0];


    for(i2 = 0 ; i2 < p2->nvert ; i2++)
    {
        if(p2->vertex_index_list[i2] == v10)
            break;
    }
    if(i2 == p2->nvert)
        return false;

    for(int j = 0 ; j<p1->nvert ; j++)
    {
        if(p1->vertex_index_list[j] != p2->vertex_index_list[i2])
            return false;
        i2++;
        if(i2 == p2->nvert)
            i2 = 0;
    }

    return true;



}

bool poly_mono_up(polyout *ptest, pt *geoPt)
{
    double ymin = INFINITY;
    int imin, iv;

    int *ivr = ptest->vertex_index_list;
    for(int i=0 ; i<ptest->nvert ; i++)
    {
        int ivp = ivr[i];

        if(geoPt[ivp].y < ymin)
        {
            ymin = geoPt[ivp].y;
            imin = i;
        }
    }

    int *ivtemp = (int *)malloc(ptest->nvert * sizeof(int));    // temp swap buffer
    int ivt = imin;

    for(iv = 0 ; iv < ptest->nvert ; iv++)
    {
      ivtemp[iv] = ivr[ivt];
      ivt++;
      if(ivt == ptest->nvert)
          ivt = 0;
    }
    for(iv = 0 ; iv < ptest->nvert ; iv++)
      ivr[iv] = ivtemp[iv];

    free(ivtemp);

    return true;

}



bool ensure_cw(polyout *ptest, pt *geoPt, int fix_flag)
{
    // Is the poly CW?
    int iv;

    polyout *pr = ptest;

    if(NULL != pr)
    {
      if(pr->is_valid)
      {
          int nv = pr->nvert;
          int *ivr = pr->vertex_index_list;

          double dfSum = 0.0;
          int iv0, iv1;
          for(iv = 0 ; iv < nv - 1 ; iv++)
          {
              iv0 = ivr[iv];
              iv1 = ivr[iv+1];

              dfSum += geoPt[iv0].x * geoPt[iv1].y
                     - geoPt[iv0].y * geoPt[iv1].x;
          }

          iv0 = ivr[nv-1];

          iv1 = ivr[0];
          dfSum += geoPt[iv0].x * geoPt[iv1].y
                -  geoPt[iv0].y * geoPt[iv1].x;

          if(dfSum < 0.0)
              return true;                                      // already is CW

          else if(fix_flag)                                     // otherwise, end-for-end the vertex list
          {
              int *ivtemp = (int *)malloc(nv * sizeof(int));    // temp swap buffer
              for(iv = 0 ; iv < nv ; iv++)
                  ivtemp[iv] = ivr[nv - iv - 1];
              for(iv = 0 ; iv < nv ; iv++)
                  ivr[iv] = ivtemp[iv];

              free(ivtemp);

              return false;

          }

          else
              return false;
      }
    }

    return false;
}


bool is_mono_poly(int nvert, int *ivres, float *bbuf)
{

//  find min and max y
    float ymax = -INFINITY;
    float ymin = INFINITY;
    int i, imin, imax;

    for(i = 0 ; i < nvert ; i++)
    {
        int iv = ivres[i];
        float y = bbuf[(iv * 2) + 1];
        if(y > ymax)
        {
            ymax = y;
            imax = i;
        }
        if (y < ymin)
        {
            ymin = y;
            imin = i;
        }
    }

//  Traverse the sides

    int mon = 1;
//  Going up...
    i=imin;
    float y0last = ymin;
    while(i != imax)
    {
        int iv = ivres[i];
        float y0 = bbuf[(iv * 2) + 1];
        if(y0 < y0last)
            mon = 0;

        y0last = y0;
        i++;
        if(i == nvert)
            i=0;
    }

//  Going down...
    i=imax;
    y0last = ymax;
    while(i != imin)
    {
        int iv = ivres[i];
        float y0 = bbuf[(iv * 2) + 1];
        if(y0 > y0last)
            mon = 0;

        y0last = y0;
        i++;
        if(i == nvert)
            i=0;
    }


    return mon;
}


/*
polyout *getpolyptr(polyout *polys, int ip)
{
    polyout *pr;
    pr = polys;
    for(int i=0 ; i<ip ; i++)
    {
          pr = (polyout *)pr->poly_next;
    }

    return pr;
}
*/



neigh_def *find_next_neighbor(polyout *polys, polyout *psource, polyout *pdestination)
{


//    wxLogMessage("\nfnn: source %d", psource->id_poly);

    // scan starting from start number
 //   wxLogMessage("    dest start: %d", scan_start);

    polyout *pdest = pdestination;
    while(!pdest->is_valid)
    {
        pdest = (polyout *)pdest->poly_next;
        if(NULL == pdest)
            pdest = polys;
    }
//    wxLogMessage("    dest valid: %d", pdest->id_poly);

    neigh_def *ret = (neigh_def *)malloc(sizeof(neigh_def));

    int v0, v1;
    bool not_found = 1;
    int found_neighbor = -1;
//    int tfound_neighbor;
//    int aligned;

    while(not_found)
    {

         while(pdest != psource)
         {
             if(pdest->is_valid)
             {

                 int *ivd = pdest->vertex_index_list;
                 int *ivr;
                 int nvdest = pdest->nvert;

                 int *ivs = psource->vertex_index_list;
                 for(int itest = 0 ; itest < psource->nvert ; itest++)
                 {
                      v0 = ivs[itest];
                      if(itest == psource->nvert -1)
                          v1 = ivs[0];
                      else
                          v1 = ivs[itest+1];

                      ivr = ivd;

                      // Inline assembler Optimization
#define MYGEO_OPT 1
#ifdef MYGEO_OPT

    #ifdef __WXX11__
//      OK, I formally apologize for this messy code, but it --is-- a tough problem....

                    int result;
                      asm ("pushl %%ecx\n\t"
                           "cld\n\t"
                           "repne\n\t"
                           "scasl\n\t"
                           "jne 1f\n\t"
                           " jecxz 2f\n\t"
                           " movl (%%edi),%%ebx\n\t"
                           " jmp 3f\n\t"
                           "2:\n\t"
                           " movl (%%esi), %%ebx\n\t"
                           "3:\n\t"
                           " cmpl %%ebx, %%edx\n\t"
                           " jne 5f\n\t"
                           " movl $1, %%eax\n\t"                     // fwd match
                           " jmp 4f\n\t"
                           "5:\n\t"
                           " subl $4, %%edi\n\t"
                           " cmpl %%esi, %%edi\n\t"
                           " je 6f\n\t"
                           " subl $4, %%edi\n\t"
                           " movl (%%edi), %%ebx\n\t"
                           " cmpl %%ebx, %%edx\n\t"
                           " jne 1f\n\t"
                           " movl $2, %%eax\n\t"                    // rev match
                           " jmp 4f\n\t"
                           "6:\n\t"
                           " popl %%ecx\n\t"
                           " decl %%ecx\n\t"
                           " shl  %%ecx\n\t"
                           " shl  %%ecx\n\t"
                           " addl %%ecx, %%esi\n\t"
                           " movl (%%esi), %%ebx\n\t"
                           " cmpl %%ebx, %%edx\n\t"
                           " je 7f\n\t"
                           " movl $0, %%eax\n\t"               // no reverse match
                           " jmp 8f\n\t"
                           "7:\n\t"
                           " movl $2, %%eax\n\t"              // rev match, hard way
                           " jmp 8f\n\t"
                           "1:\n\t"
                           " movl $0, %%eax\n\t"                // no possible match
                           "4:\n\t"
                           " popl %%ecx\n\t"
                           "8:\n\t"
                         : "=a" (result)
                         : "c" (nvdest), "a" (v0), "D" (ivd), "S" (ivd), "d" (v1)                // input parms
                         :
                       );


                      if(result)
                      {
                          found_neighbor = pdest->id_poly;
                          if(result == 2)
                              ret->aligned = 0;
                          else
                              ret->aligned = 1;
                      }


/*
                      vd0 = *(pdest_match-1);
                      if(out_count)
                         vd1 = *(pdest_match);
                      else
                          vd1 = *ivd;
                      if((vd1 == v1) && (vd0 == v0))
                      {
                          ret->aligned = 1;
                          found_neighbor = pdest->id_poly;
                          goto foundit;
                      }


                      asm ("cld\n\t"
                              "repne\n\t"
                              "scasl"
                         : "=c" (out_counta), "=D"(pdest_matcha)
                         : "c" (nvdest), "a" (v1), "D" (ivd)                // input parms
                         :
                          );

                      vd1 = *(pdest_matcha-1);
                      if(out_counta)
                         vd0 = *pdest_matcha;
                      else
                         vd0 = *ivd;
                      if((vd1 == v1) && (vd0 == v0))
                          {
                              ret->aligned = 0;
                              found_neighbor = pdest->id_poly;
                              goto foundit;
                          }
*/
    #else
    //  __MSW__ optimization goes here
    #endif

#else

                      for(int idest = 0 ; idest < nvdest ; idest++)
                      {

                          vd0 = *ivr++;

                          if(vd0 == v0)
                          {
                            if(idest == nvdest - 1)
                              vd1 = ivd[0];
                            else
                              vd1 = *ivr;
                            if(vd1 == v1)
                            {
                              ret->aligned = true;
                              found_neighbor = pdest->id_poly;
                              break;
                            }
                          }
                          else if(vd0 == v1)
                          {
                            if(idest == nvdest - 1)
                              vd1 = ivd[0];
                            else
                              vd1 = *ivr;
                            if(vd1 == v0)
                            {
                              ret->aligned = false;
                              found_neighbor = pdest->id_poly;
                              break;
                            }
                          }
                      }





        if(found_neighbor >= 0)
        {
            if(found_neighbor != tfound_neighbor)
                int ffl = 5;
        }
#endif

                    if(found_neighbor >= 0)
                      break;

                  } // psource for

                  if(found_neighbor >= 0)
                    break;
              }     // pdest valid


              if(found_neighbor >= 0)
                  break;

              else
              {
                  if(pdest->poly_next == NULL)              // skip psource in for loop
                      pdest = polys;
                  else
                      pdest = (polyout *)pdest->poly_next;
              }

         }      // while pdest != psource

          not_found = 0;
    }

    ret->v0 = v0;
    ret->v1 = v1;
    ret->source = psource->id_poly;
    ret->dest = found_neighbor;
    ret->psource = psource;
    ret->pdest = pdest;

    return ret;
}



int polyopt(polyout *polys, float *bbuf)
{
//  Walk the list once to get the total poly count, valid or invalid counted

      polyout *pr = polys;
      polyout *plast;
      int npoly = 0;
      while(NULL != pr)
      {
          npoly++;
          plast = pr;

          pr = (polyout *)pr->poly_next;
      }
      int np_next = npoly;


      int *ivres;
      bool newpoly = false;

      polyout *plook = polys;
//    for(int ip=0 ; ip < npoly-1 ; ip++)
      while (NULL != plook)
      {
          if(plook->is_valid)
          {

              polyout *ptest = (polyout *)plook->poly_next;
              if(NULL == ptest)
                  ptest = polys;

              neigh_def *pnd = find_next_neighbor(polys, plook, ptest);

              if(pnd->dest != -1)
              {
    //      try to combine the neighbors

                  if(1)
                  {
    //                  wxLogMessage("poly merge %d %d", pnd->source, pnd->dest);
                      int *ivs = pnd->psource->vertex_index_list;
                      int *ivd = pnd->pdest->vertex_index_list;
                      int v0 = pnd->v0;
                      int v1 = pnd->v1;

                      ivres = (int *)calloc((pnd->psource->nvert + pnd->pdest->nvert) * sizeof(int), 1);
                      int *ivr = ivres;

                      int it = 0;
                      while(ivs[it] != v0)
                      {
                          it++;
                          if(it == pnd->psource->nvert)
                              it = 0;
                      }

                      it++;                         // after v0 (aka v1)
                      if(it == pnd->psource->nvert)
                          it = 0;

                      *ivr++ = v0;                  // emit v0


                      int itd = 0;

                      if(!pnd->aligned)
                      {
                          while(ivd[itd] != v0)
                          {
                              itd++;
                              if(itd == pnd->pdest->nvert)
                                  itd = 0;
                          }

                          itd++;                        // after v0
                          if(itd == pnd->pdest->nvert)
                              itd = 0;

                          while(ivd[itd] != v1)         // emit all of dest in fwd
                          {
                              *ivr++ = ivd[itd];
                              itd++;
                              if(itd == pnd->pdest->nvert)
                                  itd = 0;
                          }
                      }
                      else
                      {
                           while(ivd[itd] != v0)
                          {
                              itd++;
                              if(itd == pnd->pdest->nvert)
                                  itd = 0;
                          }

                          itd--;                        // before v0
                          if(itd == -1)
                              itd = pnd->pdest->nvert - 1;

                          while(ivd[itd] != v1)         // emit all of dest in reverse
                          {
                              *ivr++ = ivd[itd];
                              itd--;
                              if(itd == -1)
                                  itd = pnd->pdest->nvert - 1;
                          }
                      }


                      while(ivs[it] != v0)          // emit all of source
                      {
                          *ivr++ = ivs[it];
                          it++;
                          if(it == pnd->psource->nvert)
                              it = 0;
                      }


                      newpoly = true;

    // Test resulting poly for integrity

                      int nv = pnd->psource->nvert + pnd->pdest->nvert - 2;
                      int indv;
                      for(int io = 0 ; io < nv-1 ; io++)
                      {
                          indv = ivres[io];
                          if(indv == 0)
                          {
//                              for(int ix=0 ; ix < pnd->psource->nvert ; ix++)
//                                  printf("S %d\n", ivs[ix]);
//                              for(int ix=0 ; ix < pnd->pdest->nvert ; ix++)
//                                  printf("D %d\n", ivd[ix]);


//                              int ffkg = 6;
                          }


/*                          for(int ii = io+1 ; ii < nv ; ii++)
                          {
                              if(indv == ivres[ii])
                                  int ffk = 5;
                          }
                          */
                      }



                  }  // if 1

    //  Now, try to get/confirm a monotonic polygon
                  if(newpoly)
                  {
                      int nv = pnd->psource->nvert + pnd->pdest->nvert - 2;
                      if(is_mono_poly(nv, ivres,bbuf))
                      {

    //                      wxLogMessage("Mono poly OK, adding %d", np_next);
                          polyout *pnew = (polyout *)calloc(sizeof(polyout), 1);
                          pnew->vertex_index_list = ivres;
                          pnew->nvert = nv;
                          pnew->is_valid = true;
                          pnew->id_poly = np_next;
                          np_next++;



                          plast->poly_next = pnew;                  // link in the new one
                          plast = pnew;

        //                  wxLogMessage(" Killing %d", pnd->psource->id_poly);
        //                  wxLogMessage(" Killing %d", pnd->pdest->id_poly);

                          pnd->pdest->is_valid = false;                  // kill the old two polys
                          pnd->psource->is_valid = false;

                      }
                      else
                          free( ivres );
                  }



              }

              free(pnd);
          }         // if plook valid

          plook = (polyout *)plook->poly_next;
      }


//  Walk the list once more to get the revised poly count

      pr = polys;
      int nret = 0;
      while(NULL != pr)
      {
          if(pr->is_valid)
              nret++;
          pr = (polyout *)pr->poly_next;
      }


//if(nret > 100)
//   wxLogMessage("Polyopt %d", nret);
    return nret;
}



#define EQUAL_EPS 1.0e-7                        // tolerance value


//--------------------------------------------------------------------------------------------------------------------------------------
//          PolyGroup Implementation
//--------------------------------------------------------------------------------------------------------------------------------------
PolyGroup::PolyGroup()
{
}

PolyGroup::~PolyGroup()
{
    free(pn_vertex);
    free(pcontour_nvertex);
    free(pgroup_geom);

    for(int i=0 ; i<nPolys ; i++)
    {
        free(pvert_array[i]);
    }
    free(pvert_array);


    delete BBArray;
}


//--------------------------------------------------------------------------------------------------------------------------------------
//          PolyGeo Implementation
//--------------------------------------------------------------------------------------------------------------------------------------
PolyGeo::PolyGeo()
{
    m_ppg_head = NULL;
}


PolyGeo::~PolyGeo()
{
    PolyGroup *ppg_this = m_ppg_head;

    while(ppg_this)
    {
        PolyGroup *ppg_next_del = ppg_this->ppg_next;

        delete ppg_this;

        ppg_this = ppg_next_del;
    }
}



//      Build PolyGeo Object from SENC file record
PolyGeo::PolyGeo(unsigned char *polybuf, int nrecl, int index)
{
#define POLY_LINE_MAX 10000
//    char buf[POLY_LINE_MAX];
//      Todo Add a try/catch set here, in case SENC file is corrupted??

 try
 {
    char *buf = (char *)malloc(POLY_LINE_MAX);
    int twkb_len;

    m_buf_head = (char *) polybuf;                      // buffer beginning
    m_buf_ptr = m_buf_head;
    m_nrecl = nrecl;
        int nPolyGroups;
        my_bufgets( buf, POLY_LINE_MAX );
        sscanf(buf, "  POLYGEOPROP %d %lf %lf %lf %lf", &nPolyGroups,
               &xmin, &ymin, &xmax, &ymax);
        m_npoly_groups = nPolyGroups;

        for(int ipg = 0 ; ipg<nPolyGroups ; ipg++)
        {
            PolyGroup *ppg = new PolyGroup;
            ppg->ppg_next = NULL;

            int nPolys;
            int nctr;
            my_bufgets( buf, POLY_LINE_MAX );
            sscanf(buf, "Polys/Contours/nWKB %d %d %d", &nPolys, &nctr, &twkb_len);
            ppg->nPolys = nPolys;
            ppg->nContours = nctr;
            ppg->pcontour_nvertex = (int *)malloc(nctr * sizeof(int));
            int *pctr = ppg->pcontour_nvertex;

            my_bufgets( buf, POLY_LINE_MAX );                       // contour nVert

            wxString ivc_str(buf + 10);
            wxStringTokenizer tkc(ivc_str, wxT(" ,\n"));
            int icvert = 0;
            while ( tkc.HasMoreTokens() )
            {
                wxString token = tkc.GetNextToken();
                if(token.IsNumber())
                {
                    icvert = atoi(token.c_str());
                    if(icvert)
                    {
                        *pctr = icvert;
                        pctr++;
                    }
                }
            }







            float *ppolygeo = (float *)malloc(twkb_len + 1);    // allow for crlf
            memmove(ppolygeo,  m_buf_ptr, twkb_len + 1);
            m_buf_ptr += twkb_len + 1;
            ppg->pgroup_geom = ppolygeo;

            ppg->pvert_array = (double **)malloc(nPolys * sizeof(double *));
            ppg->pn_vertex = (int *)malloc(nPolys * sizeof(int));

            wxBoundingBox *bbarray = new wxBoundingBox[nPolys];
            for(int ip = 0 ; ip < nPolys ; ip++)
            {
                int iPoly_id, nvert;
                my_bufgets( buf, POLY_LINE_MAX );
                sscanf(buf, "Poly %d, nv=%d", &iPoly_id, &nvert);

                double *pvertex_list = (double *)malloc(nvert * 2 * sizeof(double));
                ppg->pvert_array[ip] = pvertex_list;

                ppg->pn_vertex[ip] = nvert;

                int *p_int = (int *)m_buf_ptr;
                float sxmax = -179;                   // this poly BBox
                float sxmin = 170;
                float symax = 0;
                float symin = 90;

                double *pvr = pvertex_list;
                for(int iv=0 ; iv < nvert ; iv++)
                {
                        int ivert = p_int[iv];

                        float x = ppolygeo[2 * ivert];
                        float y = ppolygeo[(2 * ivert) + 1];

                        *pvr++ = (double)x;
                        *pvr++ = (double)y;

                        sxmax = fmax(x, sxmax);
                        sxmin = fmin(x, sxmin);
                        symax = fmax(y, symax);
                        symin = fmin(y, symin);
                }

                m_buf_ptr += nvert * sizeof(int) + 1;

                bbarray[ip].SetMin(sxmin, symin);
                bbarray[ip].SetMax(sxmax, symax);

            }

            ppg->BBArray = bbarray;

            if(ipg == 0)
                m_ppg_head = ppg;
            else
                ppg_last->ppg_next = ppg;

            ppg_last = ppg;
        }       // for polygroups


        free(buf);
  }       // try

        catch(...)
        {
            printf("Caught exception\n");
        }

}




void PolyGeo::develop_and_write_PolyGeo(OGRPolygon *poly, FILE *ofs)
{

    try
    {
    int iir, ip;

    int npolygroups = 1;

//    PolyGeo BBox
    OGREnvelope Envelope;
    poly->getEnvelope(&Envelope);


//      Get total number of contours
    int ncnt = 1;                         // always exterior ring
    int nint = poly->getNumInteriorRings();  // interior rings
    ncnt += nint;

//      Allocate cntr array
    int *cntr = (int *)malloc(ncnt * sizeof(int));

//      Get total number of points(vertices)
    int npta  = poly->getExteriorRing()->getNumPoints();
    npta += 2;                            // fluff

    for( iir=0 ; iir < nint ; iir++)
    {
        int nptr = poly->getInteriorRing(iir)->getNumPoints();
        npta += nptr + 2;
    }

    pt *geoPt = (pt*)malloc((npta) * sizeof(pt));     // vertex array

//      Create input structures

//    Exterior Ring
    int npte  = poly->getExteriorRing()->getNumPoints();
    cntr[0] = npte;

    pt *ppt = geoPt;
    ppt->x = 0.;
    ppt->y = 0.;
    ppt++;                                            // vertex 0 is unused

//  Check and account for winding direction of ring
    bool cw = poly->getExteriorRing()->isClockwise();

    double x0, y0, x, y;
    OGRPoint p;

    if(cw)
    {
        poly->getExteriorRing()->getPoint(0, &p);
        x0 = p.getX();
        y0 = p.getY();
    }
    else
    {
        poly->getExteriorRing()->getPoint(npte-1, &p);
        x0 = p.getX();
        y0 = p.getY();
    }


//  Transcribe points to vertex array, in proper order with no duplicates
    for(ip = 0 ; ip < npte ; ip++)
    {

        int pidx;
        if(cw)
            pidx = npte - ip - 1;

        else
            pidx = ip;

        poly->getExteriorRing()->getPoint(pidx, &p);
        x = p.getX();
        y = p.getY();

        if((fabs(x-x0) > EQUAL_EPS) || (fabs(y-y0) > EQUAL_EPS))
        {
            ppt->x = x;
            ppt->y = y;

            ppt++;
        }
        else
            cntr[0]--;

        x0 = x;
        y0 = y;
    }

//      for(int it = 0 ; it < cntr[0] + 1 ; it++)
//          wxLogMessage("%f %f", geoPt[it].x, geoPt[it].y);

//  Check for closed poly, not allowed by trapezator
//      if((fabs(x-x0) < EQUAL_EPS) && (fabs(y-y0) < EQUAL_EPS))
//      {
//           cntr[0]--;                            // strip the last point
//           ppt--;
//      }




//  Now the interior contours
    for(iir=0 ; iir < nint ; iir++)
    {
        int npti = poly->getInteriorRing(iir)->getNumPoints();
        cntr[iir + 1] = npti;

      //  Check and account for winding direction of ring
        bool cw = poly->getInteriorRing(iir)->isClockwise();

        if(!cw)
        {
            poly->getInteriorRing(iir)->getPoint(0, &p);
            x0 = p.getX();
            y0 = p.getY();
        }
        else
        {
            poly->getInteriorRing(iir)->getPoint(npti-1, &p);
            x0 = p.getX();
            y0 = p.getY();
        }

//  Transcribe points to vertex array, in proper order with no duplicates
        for(int ip = 0 ; ip < npti ; ip++)
        {
            OGRPoint p;
            int pidx;
            if(!cw)                               // interior contours must be cw
                pidx = npti - ip - 1;
            else
                pidx = ip;

            poly->getInteriorRing(iir)->getPoint(pidx, &p);
            x = p.getX();
            y = p.getY();

            if((fabs(x-x0) > EQUAL_EPS) || (fabs(y-y0) > EQUAL_EPS))
            {
                ppt->x = x;
                ppt->y = y;
                ppt++;
            }
            else
                cntr[iir+1]--;

            x0 = x;
            y0 = y;

        }

//  Check for closed poly, not allowed by trapezator
//          if((fabs(x-x0) < EQUAL_EPS) && (fabs(y-y0) < EQUAL_EPS))
//          {
//                cntr[iir + 1]--;                            // strip the last point
//                ppt--;
//          }


    }



    polyout *polys = trapezate_polygon(ncnt, cntr, (double (*)[2])geoPt);

//  Check the polys
    //  Especially looking for poorly formed polys
    //  These may come from several sources, all
    //  of which should be considered latent bugs in the trapezator.

    //  Known to occur:
    //  Trapezator fails if any two inner contours share a common vertex.
    //  Found on US5VA19M.000

    polyout *pck = polys;
    while(NULL != pck)
    {
        if(pck->is_valid)
        {
            int *ivs = pck->vertex_index_list;

            for(int i3 = 0 ; i3 < pck->nvert-1 ; i3++)
            {
                int ptest = ivs[i3];
                for(int i4=i3+1 ; i4 < pck->nvert ; i4++)
                {
                    if(ptest == ivs[i4])
                    {
//                        for(int k=0 ; k < pr->nvert ; k++)
//                            wxLogMessage(" %08X %f %f", ivs[k], geoPt[ivs[k]].x, geoPt[ivs[k]].y);
                        pck->is_valid = false;
                    }
                }
            }
        }

        pck = (polyout *)pck->poly_next;
    }


//  Walk the list once to get poly count
    polyout *pr;
    pr = polys;
    int npoly0 = 0;
    while(NULL != pr)
    {
        pr = (polyout *)pr->poly_next;
        npoly0++;
    }

//  Check the list for duplicates
    pr = polys;
    for(int idt = 0 ; idt<npoly0-1 ; idt++)
    {
        polyout *p1 = pr;

        polyout *p2 = (polyout *)pr->poly_next;
        while(NULL != p2)
        {
            if(p1->is_valid && p2->is_valid)
            {
                if(ispolysame(p1, p2))
                    p1->is_valid = false;
            }
            p2 = (polyout *)p2->poly_next;
        }

        pr = (polyout *)pr->poly_next;
    }

//  Walk the list again to get unique poly count
    pr = polys;
    int npoly = 0;
    while(NULL != pr)
    {
        if(pr->is_valid)
            npoly++;
        pr = (polyout *)pr->poly_next;

    }

//      if(npoly != npoly0)
//          wxLogMessage("Invalidating %d duplicate poly(s)", npoly0 - npoly);



    int nwkb = (npta + 1) * 2 * sizeof(float);
 //  Copy the geometry into a buffer, converting to float from double
    unsigned char *bbuf = (unsigned char *)malloc(nwkb);
    float *vr = (float *)bbuf;
    for(ip = 0 ; ip < npta ; ip++)
    {
        *vr++ = geoPt[ip].x;
        *vr++ = geoPt[ip].y;
    }


//      wxLogMessage("UnOptimized npoly: %d", npoly);

//  Try an optimization
    if(1)
    {
        int nr = polyopt(polys, (float *)bbuf);
        int enuf = 0;
        int iopt = 0;
        while(!enuf)
        {
            int nr1 = polyopt(polys, (float *)bbuf);
            if (nr1 >= nr)
                enuf = true;
            if(iopt++ > 20)
                enuf = true;
            nr = nr1;
        }
    }

//  Walk the list again, to get the revised poly count
    pr = polys;
    npoly = 0;
    while(NULL != pr)
    {
        if(pr->is_valid)
            npoly++;
        pr = (polyout *)pr->poly_next;
    }


//  Traverse the poly list, ensuring and enforcing CW winding
    pr = polys;
    while(NULL != pr)
    {
        if(pr->is_valid)
        {
            ensure_cw(pr, geoPt, 1);
//              if(!ensure_cw(pr, geoPt, 0))
//                  int ggk = 5;
        }
        pr = (polyout *)pr->poly_next;
    }

//  Traverse the poly list, arranging that the first index is YMIN
//  which makes dda rasterization much cheaper
    pr = polys;
    while(NULL != pr)
    {
        if(pr->is_valid)
        {
            poly_mono_up(pr, geoPt);
        }
        pr = (polyout *)pr->poly_next;
    }




//  All is known, so create the output record

    wxString    sout;
    wxString    sout1;
    wxString    stemp;

    stemp.sprintf( "  POLYGEOPROP %d %f %f %f %f\n", npolygroups,
            Envelope.MinX, Envelope.MinY, Envelope.MaxX, Envelope.MaxY);            // PolyGeo Header
    sout += stemp;

//  There is only one polygroup....

    //  For each polygroup....
    //  Transcribe the true number of polys, number of contours, and the wkb size
    stemp.sprintf( "Polys/Contours/nWKB %d %d %d\n",  npoly, ncnt, nwkb);
    sout += stemp;


//  Transcribe the contour counts
    stemp.sprintf("Contour nV");
    sout += stemp;
    for(int i=0 ; i<ncnt ; i++)
    {
        stemp.sprintf( " %d", cntr[i]);
        sout += stemp;
    }
    stemp.sprintf( "\n");
    sout += stemp;

 //  develop and transcribe the vertex indices for each poly

 //     Walk the list once to get the wkb length
    int ps_len = 1;
    pr = polys;
    int iwpolyt = 0;
    while(NULL != pr)
    {
        if(pr->is_valid)
        {
            int nv = pr->nvert;

            stemp.sprintf( "Poly %5d, nv=%5d\n", iwpolyt, nv);
            int this_len = (nv * sizeof(int)) + stemp.Len() + 1;
            ps_len += this_len;
        }

        pr = (polyout *)pr->poly_next;
    }


  // Now the real list
    char *ps = (char *)malloc(ps_len);
    char *psr = ps;
    *psr = '\n';
    psr++;

    pr = polys;
    int iwpoly = 0;
    while(NULL != pr)
    {
        if(pr->is_valid)
        {
            int nv = pr->nvert;
            int *ivr = pr->vertex_index_list;

            stemp.sprintf( "Poly %5d, nv=%5d\n", iwpoly, nv);
            strcpy(psr, stemp.c_str());
            psr += stemp.Len();

            int *pvi = (int *)psr;
            for(int iv = 0 ; iv < nv ; iv++)
            {
                *pvi = *ivr;
                pvi++;
                ivr++;
                psr += sizeof(int);
            }
            *psr++ = '\n';
            iwpoly++;
        }

        pr = (polyout *)pr->poly_next;
    }


    //  Calculate and stuff the record length
    int nrecl = sout.Len() + nwkb + ps_len;
    stemp.sprintf( "  POLYGEO  %d\n", nrecl);

//  Write the record in four parts....
    fwrite(stemp.c_str(), 1, stemp.Len(), ofs);                 // Header, + record length
    fwrite(sout.c_str(), 1, sout.Len(), ofs);
    fwrite(bbuf, 1, nwkb, ofs);
    fwrite(ps, 1, ps_len, ofs);


//  Free the polyout structure
    pr = polys;
    while(NULL != pr)
    {
        free(pr->vertex_index_list);

        polyout *pf = pr;
        pr = (polyout *)pr->poly_next;
        free(pf);
    }

    free(bbuf);
    free(ps);


//  Free the polyin structures

    free(cntr);
    free(geoPt);

}       // try

    catch(...)
    {
        printf("Caught exception\n");
    }

}

int PolyGeo::my_bufgets( char *buf, int buf_len_max )
{
    char        chNext;
    int         nLineLen = 0;
    char        *lbuf;

    lbuf = buf;


    while( (nLineLen < buf_len_max) &&((m_buf_ptr - m_buf_head) < m_nrecl) )
    {
        chNext = *m_buf_ptr++;

        /* each CR/LF (or LF/CR) as if just "CR" */
        if( chNext == 10 || chNext == 13 )
        {
            chNext = '\n';
        }

        *lbuf = chNext; lbuf++, nLineLen++;

        if( chNext == '\n' )
        {
            *lbuf = '\0';
            return nLineLen;
        }
    }

    *(lbuf) = '\0';
    return nLineLen;
}







#if 0

/*
 * ANSI C code from the article
 * "Centroid of a Polygon"
 * by Gerard Bashein and Paul R. Detmer,
      (gb@locke.hs.washington.edu, pdetmer@u.washington.edu)
 * in "Graphics Gems IV", Academic Press, 1994
 */

/*********************************************************************
polyCentroid: Calculates the centroid (xCentroid, yCentroid) and area
of a polygon, given its vertices (x[0], y[0]) ... (x[n-1], y[n-1]). It
is assumed that the contour is closed, i.e., that the vertex following
(x[n-1], y[n-1]) is (x[0], y[0]).  The algebraic sign of the area is
positive for counterclockwise ordering of vertices in x-y plane;
otherwise negative.

Returned values:  0 for normal execution;  1 if the polygon is
degenerate (number of vertices < 3);  and 2 if area = 0 (and the
centroid is undefined).
**********************************************************************/
int polyCentroid(double x[], double y[], int n,
             double *xCentroid, double *yCentroid, double *area)
     {
     register int i, j;
     double ai, atmp = 0, xtmp = 0, ytmp = 0;
     if (n < 3) return 1;
     for (i = n-1, j = 0; j < n; i = j, j++)
        {
        ai = x[i] * y[j] - x[j] * y[i];
        atmp += ai;
        xtmp += (x[j] + x[i]) * ai;
        ytmp += (y[j] + y[i]) * ai;
        }
     *area = atmp / 2;
     if (atmp != 0)
        {
        *xCentroid =    xtmp / (3 * atmp);
        *yCentroid =    ytmp / (3 * atmp);
        return 0;
        }
     return 2;
     }





#endif

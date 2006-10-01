/******************************************************************************
 * $Id: mygeom.cpp,v 1.3 2006/10/01 03:22:58 dsr Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Tesselated Polygon Object
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
 * Revision 1.3  2006/10/01 03:22:58  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:37:36  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
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
#include <wx/mstream.h>

#include "dychart.h"

#include "mygeom.h"

#include "triangulate.h"

#ifdef USE_GLU_TESS
#include <GL/gl.h>
#include <GL/glu.h>

#include <windows.h>
#endif

CPL_CVSID("$Id: mygeom.cpp,v 1.3 2006/10/01 03:22:58 dsr Exp $");


extern "C" polyout *triangulate_polygon(int, int[1], double (*)[2]);


//      Internal Prototypes


#ifdef USE_GLU_TESS
static int            s_nvcall;
static double         *s_pwork_buf;
static int            s_buf_len;
static int            s_buf_idx;
static unsigned int   s_gltri_type;
TriPrim               *s_pTPG_Head;
TriPrim               *s_pTPG_Last;
static GLUtesselator  *GLUtessobj;
#endif

static int            tess_orient;
static wxMemoryOutputStream *ostream1;
static wxMemoryOutputStream *ostream2;



//  For __WXMSW__ builds using GLU_TESS and glu32.dll
//  establish the dll entry points

#ifdef __WXMSW__
#ifdef USE_GLU_TESS
#ifdef USE_GLU_DLL

//  Formal definitions of required functions
typedef void (CALLBACK* LPFNDLLTESSPROPERTY)      ( GLUtesselator *tess,
                                                    GLenum        which, 
                                                    GLdouble      value );
typedef GLUtesselator * (CALLBACK* LPFNDLLNEWTESS)( void);
typedef void (CALLBACK* LPFNDLLTESSBEGINCONTOUR)  ( GLUtesselator *);
typedef void (CALLBACK* LPFNDLLTESSENDCONTOUR)    ( GLUtesselator *);
typedef void (CALLBACK* LPFNDLLTESSBEGINPOLYGON)  ( GLUtesselator *, void*);
typedef void (CALLBACK* LPFNDLLTESSENDPOLYGON)    ( GLUtesselator *);
typedef void (CALLBACK* LPFNDLLDELETETESS)        ( GLUtesselator *);
typedef void (CALLBACK* LPFNDLLTESSVERTEX)        ( GLUtesselator *, GLdouble *, GLdouble *);
typedef void (CALLBACK* LPFNDLLTESSCALLBACK)      ( GLUtesselator *, const int, void (CALLBACK *fn)() );

//  Static pointers to the functions
static LPFNDLLTESSPROPERTY      s_lpfnTessProperty;
static LPFNDLLNEWTESS           s_lpfnNewTess;
static LPFNDLLTESSBEGINCONTOUR  s_lpfnTessBeginContour;
static LPFNDLLTESSENDCONTOUR    s_lpfnTessEndContour;
static LPFNDLLTESSBEGINPOLYGON  s_lpfnTessBeginPolygon;
static LPFNDLLTESSENDPOLYGON    s_lpfnTessEndPolygon;
static LPFNDLLDELETETESS        s_lpfnDeleteTess;
static LPFNDLLTESSVERTEX        s_lpfnTessVertex;
static LPFNDLLTESSCALLBACK      s_lpfnTessCallback;

//  Mapping of pointers to glu functions by substitute macro
#define gluTessProperty         s_lpfnTessProperty
#define gluNewTess              s_lpfnNewTess
#define gluTessBeginContour     s_lpfnTessBeginContour
#define gluTessEndContour       s_lpfnTessEndContour
#define gluTessBeginPolygon     s_lpfnTessBeginPolygon
#define gluTessEndPolygon       s_lpfnTessEndPolygon
#define gluDeleteTess           s_lpfnDeleteTess
#define gluTessVertex           s_lpfnTessVertex
#define gluTessCallback         s_lpfnTessCallback

//  Flag to tell that dll is ready
bool           s_glu_dll_ready;
HINSTANCE      s_hGLU_DLL;                   // Handle to DLL

#endif
#endif
#endif



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





//------------------------------------------------------------------------------
//          PolyTessGeo Implementation
//------------------------------------------------------------------------------
PolyTessGeo::PolyTessGeo()
{
}

//      Build PolyTessGeo Object from OGR Polygon
PolyTessGeo::PolyTessGeo(OGRPolygon *poly)
{
    ErrorCode = 0;
    m_ppg_head = NULL;
    
#ifdef USE_GLU_TESS
    ErrorCode = PolyTessGeoGL(poly);
#else
    ErrorCode = PolyTessGeoTri(poly);
#endif

}



//      Build PolyGeo Object from SENC file record
PolyTessGeo::PolyTessGeo(unsigned char *polybuf, int nrecl, int index)
{
#define POLY_LINE_MAX 10000
//      Todo Add a try/catch set here, in case SENC file is corrupted??


    char *buf = (char *)malloc(POLY_LINE_MAX);
    int twkb_len;

    m_buf_head = (char *) polybuf;                      // buffer beginning
    m_buf_ptr = m_buf_head;
    m_nrecl = nrecl;
    my_bufgets( buf, POLY_LINE_MAX );
    sscanf(buf, "  POLYTESSGEOPROP %lf %lf %lf %lf",
           &xmin, &ymin, &xmax, &ymax);


    PolyTriGroup *ppg = new PolyTriGroup;
    int nctr;
    my_bufgets( buf, POLY_LINE_MAX );
    sscanf(buf, "Contours/nWKB %d %d", &nctr, &twkb_len);
    ppg->nContours = nctr;
    ppg->pn_vertex = (int *)malloc(nctr * sizeof(int));
    int *pctr = ppg->pn_vertex;

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


    //  Read Raw Geometry

    float *ppolygeo = (float *)malloc(twkb_len + 1);    // allow for crlf
    memmove(ppolygeo,  m_buf_ptr, twkb_len + 1);
    m_buf_ptr += twkb_len + 1;
    ppg->pgroup_geom = ppolygeo;



    TriPrim **p_prev_triprim = &(ppg->tri_prim_head);

    //  Read the PTG_Triangle Geometry in a loop
    unsigned int tri_type;
    int nvert;
    bool not_finished = true;
    while(not_finished)
    {
        my_bufgets( buf, POLY_LINE_MAX );                       // GL_TRI.....

        if(!strncmp(buf, "GL_TRI", 6))
        {
            sscanf(buf, "GL_TRI%d %d", &tri_type, &nvert);

            TriPrim *tp = new TriPrim;
            *p_prev_triprim = tp;                               // make the link
            p_prev_triprim = &(tp->p_next);
            tp->p_next = NULL;

            tp->type = tri_type;
            tp->nVert = nvert;
            int byte_size = nvert * 2 * sizeof(double);

            tp->p_vertex = (double *)malloc(byte_size);
            memmove(tp->p_vertex, m_buf_ptr, byte_size);
            m_buf_ptr += byte_size + 1;                 // allow for CRLF

        //  Calculate bounding box

            tp->p_bbox = new wxBoundingBox;

            float sxmax = -179;                   // this poly BBox
            float sxmin = 170;
            float symax = 0;
            float symin = 90;

            double *pvr = tp->p_vertex;
            for(int iv=0 ; iv < nvert ; iv++)
            {
                double xd, yd;
                xd = *pvr++;
                yd = *pvr++;

                sxmax = fmax(xd, sxmax);
                sxmin = fmin(xd, sxmin);
                symax = fmax(yd, symax);
                symin = fmin(yd, symin);
            }

            tp->p_bbox->SetMin(sxmin, symin);
            tp->p_bbox->SetMax(sxmax, symax);

        }
        else                                    // got end of poly
        {
            not_finished = false;
        }

    }                   // while



    m_ppg_head = ppg;

    free(buf);




}


//      Build PolyTessGeo Object from OGR Polygon
//      Using internal Triangle tesselator
int PolyTessGeo::PolyTessGeoTri(OGRPolygon *poly)
{

    int iir, ip;

    tess_orient = TESS_HORZ;                    // prefer horizontal tristrips

//    PolyGeo BBox
    OGREnvelope Envelope;
    poly->getEnvelope(&Envelope);
    xmin = Envelope.MinX;
    ymin = Envelope.MinY;
    xmax = Envelope.MaxX;
    ymax = Envelope.MaxY;


//      Get total number of contours
    ncnt = 1;                         // always exterior ring
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
    }

    polyout *polys = triangulate_polygon(ncnt, cntr, (double (*)[2])geoPt);


//  Check the triangles
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



        //  Create the data structures

    m_ppg_head = new PolyTriGroup;

    m_ppg_head->nContours = ncnt;

    m_ppg_head->pn_vertex = cntr;             // pointer to array of poly vertex counts


//  Transcribe the raw geometry buffer
//  Converting to float as we go, and
//  allowing for tess_orient

    nwkb = (npta +1) * 2 * sizeof(float);
    m_ppg_head->pgroup_geom = (float *)malloc(nwkb);
    float *vro = m_ppg_head->pgroup_geom;
    float tx,ty;

    for(ip = 1 ; ip < npta + 1 ; ip++)
    {
        if(TESS_HORZ == tess_orient)
        {
            ty = geoPt[ip].y;
            tx = geoPt[ip].x;
        }
        else
        {
            tx = geoPt[ip].x;
            ty = geoPt[ip].y;
        }

        *vro++ = tx;                  // x
        *vro++ = ty;                  // y
    }



       //  Now the Triangle Primitives

    TriPrim *pTP = NULL;
    TriPrim *pTP_Head = NULL;
    TriPrim *pTP_Last = NULL;

    pr = polys;
    while(NULL != pr)
    {
        if(pr->is_valid)
        {
            pTP = new TriPrim;
            if(NULL == pTP_Last)
            {
                pTP_Head = pTP;
                pTP_Last = pTP;
            }
            else
            {
                pTP_Last->p_next = pTP;
                pTP_Last = pTP;
            }

            pTP->p_next = NULL;
            pTP->type = PTG_TRIANGLES;
            pTP->nVert = pr->nvert;

            pTP->p_vertex = (double *)malloc(pr->nvert * 2 * sizeof(double));
            double *dbr = pTP->p_vertex;
            int *ivr = pr->vertex_index_list;
            for(int i=0 ; i<pr->nvert ; i++)
            {
                int ivp = ivr[i];
                memcpy(dbr++, &geoPt[ivp].x, sizeof(double));
                memcpy(dbr++, &geoPt[ivp].y, sizeof(double));
            }

        //  Calculate bounding box

            pTP->p_bbox = new wxBoundingBox;

            float sxmax = -179;                   // this poly BBox
            float sxmin = 170;
            float symax = 0;
            float symin = 90;

            double *pvr = pTP->p_vertex;
            for(int iv=0 ; iv < pr->nvert ; iv++)
            {
                double xd, yd;
                xd = *pvr++;
                yd = *pvr++;

                sxmax = fmax(xd, sxmax);
                sxmin = fmin(xd, sxmin);
                symax = fmax(yd, symax);
                symin = fmin(yd, symin);
            }

            pTP->p_bbox->SetMin(sxmin, symin);
            pTP->p_bbox->SetMax(sxmax, symax);

        }
        pr = (polyout *)pr->poly_next;
    }

    m_ppg_head->tri_prim_head = pTP_Head;         // head of linked list of TriPrims


//  Free the polyout structure
    pr = polys;
    while(NULL != pr)
    {
        free(pr->vertex_index_list);

        polyout *pf = pr;
        pr = (polyout *)pr->poly_next;
        free(pf);
    }

    return 0;
}

int PolyTessGeo::Write_PolyTriGroup( FILE *ofs)
{
    wxString    sout;
    wxString    sout1;
    wxString    stemp;

    PolyTriGroup *pPTG = m_ppg_head;


//  Begin creating the output record
//      Use a wxMemoryStream for temporary record output.
//      When all finished, we'll touch up a few items before
//      committing to disk.


    ostream1 = new wxMemoryOutputStream(NULL, 0);                      // auto buffer creation
    ostream2 = new wxMemoryOutputStream(NULL, 0);                      // auto buffer creation

//  Create initial known part of the output record


    stemp.sprintf( "  POLYTESSGEOPROP %f %f %f %f\n",
                   xmin, ymin, xmax, ymax);            // PolyTessGeo Properties
    sout += stemp;

//  Transcribe the true number of  contours, and the raw geometry wkb size
    stemp.sprintf( "Contours/nWKB %d %d\n",  ncnt, nwkb);
    sout += stemp;


//  Transcribe the contour counts
    stemp.sprintf("Contour nV");
    sout += stemp;
    for(int i=0 ; i<ncnt ; i++)
    {
        stemp.sprintf( " %d", pPTG->pn_vertex[i]);
        sout += stemp;
    }
    stemp.sprintf( "\n");
    sout += stemp;
    ostream1->Write(sout.c_str(), sout.Len());

//  Transcribe the raw geometry buffer

    ostream1->Write(pPTG->pgroup_geom,nwkb);
    stemp.sprintf( "\n");
    ostream1->Write(stemp.c_str(), stemp.Len());



//  Transcribe the TriPrim chain

    TriPrim *pTP = pPTG->tri_prim_head;         // head of linked list of TriPrims

    stemp.sprintf( "\n");

    while(pTP)
    {

        char buf[80];

        sprintf(buf, "GL_TRI%1d %d\n", pTP->type, pTP->nVert);
        ostream2->Write(buf, strlen(buf));

        ostream2->Write( pTP->p_vertex, pTP->nVert * 2 * sizeof(double));

        ostream2->Write(stemp.c_str(), stemp.Len());

        pTP = pTP->p_next;
    }


    stemp.sprintf( "POLYEND\n");
    ostream2->Write(stemp.c_str(), stemp.Len());


    int nrecl = ostream1->GetSize() + ostream2->GetSize();
    stemp.sprintf( "  POLYTESSGEO  %08d\n", nrecl);

    fwrite(stemp.c_str(), 1, stemp.Len(), ofs);                 // Header, + record length

    char *tb = (char *)malloc(ostream1->GetSize());
    ostream1->CopyTo(tb, ostream1->GetSize());
    fwrite(tb, 1, ostream1->GetSize(), ofs);
    free(tb);

    tb = (char *)malloc(ostream2->GetSize());
    ostream2->CopyTo(tb, ostream2->GetSize());
    fwrite(tb, 1, ostream2->GetSize(), ofs);
    free(tb);

    delete ostream1;
    delete ostream2;

    return 0;
}







int PolyTessGeo::my_bufgets( char *buf, int buf_len_max )
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



PolyTessGeo::~PolyTessGeo()
{

    delete  m_ppg_head;


#ifdef USE_GLU_TESS
    if(s_pwork_buf)
        free( s_pwork_buf );
    s_pwork_buf = NULL;
#endif

}




//      Build PolyTessGeo Object from OGR Polygon
//      Using OpenGL/GLU tesselator
#ifdef USE_GLU_TESS


#ifdef __WXMSW__
#define __CALL_CONVENTION __stdcall
#else
#define __CALL_CONVENTION 
#endif


void __CALL_CONVENTION beginCallback(GLenum which);
void __CALL_CONVENTION errorCallback(GLenum errorCode);
void __CALL_CONVENTION endCallback(void);
void __CALL_CONVENTION vertexCallback(GLvoid *vertex);
void __CALL_CONVENTION combineCallback(GLdouble coords[3],
                     GLdouble *vertex_data[4],
                     GLfloat weight[4], GLdouble **dataOut );



int PolyTessGeo::PolyTessGeoGL(OGRPolygon *poly)
{
    int iir, ip;
    int *cntr;
    GLdouble *geoPt;

    wxString    sout;
    wxString    sout1;
    wxString    stemp;


#ifdef __WXMSW__
//  If using the OpenGL dlls provided with Windows,
//  load the dll and establish addresses of the entry points needed

#ifdef USE_GLU_DLL

    if(!s_glu_dll_ready)
    {


        s_hGLU_DLL = LoadLibrary("glu32.dll");
        if (s_hGLU_DLL != NULL)
        {
            s_lpfnTessProperty = (LPFNDLLTESSPROPERTY)GetProcAddress(s_hGLU_DLL,"gluTessProperty");
            s_lpfnNewTess = (LPFNDLLNEWTESS)GetProcAddress(s_hGLU_DLL, "gluNewTess");
            s_lpfnTessBeginContour = (LPFNDLLTESSBEGINCONTOUR)GetProcAddress(s_hGLU_DLL, "gluTessBeginContour");
            s_lpfnTessEndContour = (LPFNDLLTESSENDCONTOUR)GetProcAddress(s_hGLU_DLL, "gluTessEndContour");
            s_lpfnTessBeginPolygon = (LPFNDLLTESSBEGINPOLYGON)GetProcAddress(s_hGLU_DLL, "gluTessBeginPolygon");
            s_lpfnTessEndPolygon = (LPFNDLLTESSENDPOLYGON)GetProcAddress(s_hGLU_DLL, "gluTessEndPolygon");
            s_lpfnDeleteTess = (LPFNDLLDELETETESS)GetProcAddress(s_hGLU_DLL, "gluDeleteTess");
            s_lpfnTessVertex = (LPFNDLLTESSVERTEX)GetProcAddress(s_hGLU_DLL, "gluTessVertex");
            s_lpfnTessCallback = (LPFNDLLTESSCALLBACK)GetProcAddress(s_hGLU_DLL, "gluTessCallback");

            s_glu_dll_ready = true;
        }
        else
        {
            return ERROR_NO_DLL;
        }
    }

#endif
#endif


    //  Allocate a work buffer, which will be grown as needed
#define NINIT_BUFFER_LEN 10000
    s_pwork_buf = (GLdouble *)malloc(NINIT_BUFFER_LEN * 2 * sizeof(GLdouble));
    s_buf_len = NINIT_BUFFER_LEN * 2;
    s_buf_idx = 0;


    //  Create tesselator
    GLUtessobj = gluNewTess();

    //  Register the callbacks
    gluTessCallback(GLUtessobj, GLU_TESS_BEGIN,   (GLvoid (__CALL_CONVENTION *) ())&beginCallback);
    gluTessCallback(GLUtessobj, GLU_TESS_BEGIN,   (GLvoid (__CALL_CONVENTION *) ())&beginCallback);
    gluTessCallback(GLUtessobj, GLU_TESS_VERTEX,  (GLvoid (__CALL_CONVENTION *) ())&vertexCallback);
    gluTessCallback(GLUtessobj, GLU_TESS_END,     (GLvoid (__CALL_CONVENTION *) ())&endCallback);
    gluTessCallback(GLUtessobj, GLU_TESS_COMBINE, (GLvoid (__CALL_CONVENTION *) ())&combineCallback);

//    gluTessCallback(GLUtessobj, GLU_TESS_ERROR,   (GLvoid (__CALL_CONVENTION *) ())&errorCallback);

//    glShadeModel(GL_SMOOTH);
    gluTessProperty(GLUtessobj, GLU_TESS_WINDING_RULE,
                    GLU_TESS_WINDING_POSITIVE );

    //  gluTess algorithm internally selects vertically oriented triangle strips and fans.
    //  This orientation is not optimal for conventional memory-mapped raster display shape filling.
    //  We can "fool" the algorithm by interchanging the x and y vertex values passed to gluTessVertex
    //  and then reverting x and y on the resulting vertexCallbacks.
    //  In this implementation, we will explicitely set the preferred orientation.

    //Set the preferred orientation
    tess_orient = TESS_HORZ;                    // prefer horizontal tristrips



//    PolyGeo BBox
    OGREnvelope Envelope;
    poly->getEnvelope(&Envelope);
    xmin = Envelope.MinX;
    ymin = Envelope.MinY;
    xmax = Envelope.MaxX;
    ymax = Envelope.MaxY;


//      Get total number of contours
    ncnt = 1;                         // always exterior ring
    int nint = poly->getNumInteriorRings();  // interior rings
    ncnt += nint;


//      Allocate cntr array
    cntr = (int *)malloc(ncnt * sizeof(int));


//      Get total number of points(vertices)
    int npta  = poly->getExteriorRing()->getNumPoints();
    cntr[0] = npta;
    npta += 2;                            // fluff

    for( iir=0 ; iir < nint ; iir++)
    {
        int nptr = poly->getInteriorRing(iir)->getNumPoints();
        cntr[iir+1] = nptr;

        npta += nptr + 2;
    }

    geoPt = (GLdouble *)malloc((npta) * 3 * sizeof(GLdouble));     // vertex array



   //  Grow the work buffer if necessary

    if((npta * 4) > s_buf_len)
    {
        s_pwork_buf = (GLdouble *)realloc(s_pwork_buf, npta * 4 * 2 * sizeof(GLdouble *));
        s_buf_len = npta * 4 * 2;
    }


//  Define the polygon
    gluTessBeginPolygon(GLUtessobj, NULL);


//      Create input structures

//    Exterior Ring
    int npte  = poly->getExteriorRing()->getNumPoints();
    cntr[0] = npte;

    GLdouble *ppt = geoPt;


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


    gluTessBeginContour(GLUtessobj);

//  Transcribe points to vertex array, in proper order with no duplicates
//   also, accounting for tess_orient
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
            GLdouble *ppt_temp = ppt;
            if(tess_orient == TESS_VERT)
            {
                *ppt++ = x;
                *ppt++ = y;
            }
            else
            {
                *ppt++ = y;
                *ppt++ = x;
            }

            *ppt++ = 0.0;

            gluTessVertex( GLUtessobj, ppt_temp, ppt_temp ) ;


        }
        else
            cntr[0]--;

        x0 = x;
        y0 = y;
    }

    gluTessEndContour(GLUtessobj);




//  Now the interior contours
    for(iir=0 ; iir < nint ; iir++)
    {
        gluTessBeginContour(GLUtessobj);

        int npti = poly->getInteriorRing(iir)->getNumPoints();

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
//   also, accounting for tess_orient
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
                GLdouble *ppt_temp = ppt;
                if(tess_orient == TESS_VERT)
                {
                    *ppt++ = x;
                    *ppt++ = y;
                }
                else
                {
                    *ppt++ = y;
                    *ppt++ = x;
                }
                *ppt++ = 0.0;

                gluTessVertex( GLUtessobj, ppt_temp, ppt_temp ) ;
            }
            else
                cntr[iir+1]--;

            x0 = x;
            y0 = y;

        }

        gluTessEndContour(GLUtessobj);
    }





    //      Ready to kick off the tesselator

    s_pTPG_Last = NULL;
    s_pTPG_Head = NULL;

    gluTessEndPolygon(GLUtessobj);                                           // here it goes




        //  Create the data structures

    m_ppg_head = new PolyTriGroup;

    m_ppg_head->nContours = ncnt;

    m_ppg_head->pn_vertex = cntr;             // pointer to array of poly vertex counts


//  Transcribe the raw geometry buffer
//  Converting to float as we go, and
//  allowing for tess_orient

    nwkb = (npta +1) * 2 * sizeof(float);
    m_ppg_head->pgroup_geom = (float *)malloc(nwkb);
    float *vro = m_ppg_head->pgroup_geom;
    ppt = geoPt;
    float tx,ty;

    for(ip = 0 ; ip < npta ; ip++)
    {
        if(TESS_HORZ == tess_orient)
        {
            ty = *ppt++;
            tx = *ppt++;
        }
        else
        {
            tx = *ppt++;
            ty = *ppt++;
        }

        *vro++ = tx;                  // x
        *vro++ = ty;                  // y
        ppt++;                      // skip z
    }

    m_ppg_head->tri_prim_head = s_pTPG_Head;         // head of linked list of TriPrims

    gluDeleteTess(GLUtessobj);

    free( s_pwork_buf );
    s_pwork_buf = NULL;

    free (geoPt);

    return 0;
}







// GLU tesselation support functions
void __CALL_CONVENTION beginCallback(GLenum which)
{
    s_buf_idx = 0;
    s_nvcall = 0;
    s_gltri_type = which;
}

/*
void __CALL_CONVENTION errorCallback(GLenum errorCode)
{
    const GLubyte *estring;

    estring = gluErrorString(errorCode);
    printf("Tessellation Error: %s\n", estring);
    exit(0);
}
*/

void __CALL_CONVENTION endCallback(void)
{
    //      Create a TriPrim

    char buf[40];

    switch(s_gltri_type)
    {
        case GL_TRIANGLE_FAN:
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLES:
        {
            TriPrim *pTPG = new TriPrim;
            if(NULL == s_pTPG_Last)
            {
                s_pTPG_Head = pTPG;
                s_pTPG_Last = pTPG;
            }
            else
            {
                s_pTPG_Last->p_next = pTPG;
                s_pTPG_Last = pTPG;
            }

            pTPG->p_next = NULL;
            pTPG->type = s_gltri_type;
            pTPG->nVert = s_nvcall;

            pTPG->p_vertex = (double *)malloc(s_nvcall * 2 * sizeof(double));
            memcpy(pTPG->p_vertex, s_pwork_buf, s_nvcall * 2 * sizeof(double));

        //  Calculate bounding box

            pTPG->p_bbox = new wxBoundingBox;

            float sxmax = -179;                   // this poly BBox
            float sxmin = 170;
            float symax = 0;
            float symin = 90;

            GLdouble *pvr = pTPG->p_vertex;
            for(int iv=0 ; iv < s_nvcall ; iv++)
            {
                GLdouble xd, yd;
                xd = *pvr++;
                yd = *pvr++;

                sxmax = fmax(xd, sxmax);
                sxmin = fmin(xd, sxmin);
                symax = fmax(yd, symax);
                symin = fmin(yd, symin);
            }

            pTPG->p_bbox->SetMin(sxmin, symin);
            pTPG->p_bbox->SetMax(sxmax, symax);

            break;
        }
        default:
        {
            sprintf(buf, "....begin Callback  unknown\n");
            break;
        }
    }
}

void __CALL_CONVENTION vertexCallback(GLvoid *vertex)
{
    GLdouble *pointer;

    pointer = (GLdouble *) vertex;

    if(s_buf_idx > s_buf_len - 4)
    {
        int new_buf_len = s_buf_len + 100;
        s_pwork_buf = (GLdouble *)realloc(s_pwork_buf, new_buf_len * sizeof(GLdouble));
        s_buf_len = new_buf_len;
    }

    if(tess_orient == TESS_VERT)
    {
        s_pwork_buf[s_buf_idx++] = pointer[0];
        s_pwork_buf[s_buf_idx++] = pointer[1];
    }
    else
    {
        s_pwork_buf[s_buf_idx++] = pointer[1];
        s_pwork_buf[s_buf_idx++] = pointer[0];
    }


    s_nvcall++;

}

/*  combineCallback is used to create a new vertex when edges
 *  intersect.
 */
void __CALL_CONVENTION combineCallback(GLdouble coords[3],
                     GLdouble *vertex_data[4],
                     GLfloat weight[4], GLdouble **dataOut )
{
    GLdouble *vertex = new GLdouble[6] ;

    vertex[0] = coords[0];
    vertex[1] = coords[1];
    vertex[2] = coords[2];
    vertex[3] = vertex[4] = vertex[5] = 0. ; //01/13/05 bugfix

    *dataOut = vertex;
}
#endif



//------------------------------------------------------------------------------
//          PolyTriGroup Implementation
//------------------------------------------------------------------------------
PolyTriGroup::PolyTriGroup()
{
    pn_vertex = NULL;             // pointer to array of poly vertex counts
    pgroup_geom = NULL;           // pointer to Raw geometry, used for contour line drawing
    tri_prim_head = NULL;         // head of linked list of TriPrims

}

PolyTriGroup::~PolyTriGroup()
{
    free(pn_vertex);
    free(pgroup_geom);

    //Walk the list of TriPrims, deleting as we go
    TriPrim *tp_next;
    TriPrim *tp = tri_prim_head;
    while(tp)
    {
        tp_next = tp->p_next;
        delete tp;
        tp = tp_next;
    }
}

//------------------------------------------------------------------------------
//          TriPrim Implementation
//------------------------------------------------------------------------------
TriPrim::TriPrim()
{
}

TriPrim::~TriPrim()
{

    free(p_vertex);
    delete p_bbox;
}












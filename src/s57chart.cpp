/******************************************************************************
 * $Id: s57chart.cpp,v 1.11 2008/01/10 03:38:32 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  S57 Chart Object
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
 * $Log: s57chart.cpp,v $
 * Revision 1.11  2008/01/10 03:38:32  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.9  2007/06/10 02:33:59  bdbcat
 * Color scheme support
 *
 * Revision 1.8  2007/05/03 13:23:56  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.7  2007/03/02 01:59:16  dsr
 * Convert to UTM Projection
 *
 * Revision 1.6  2007/01/19 02:18:55  dsr
 * Cleanup
 *
 * Revision 1.5  2006/10/08 00:36:44  dsr
 * no message
 *
 * Revision 1.4  2006/10/07 03:50:28  dsr
 * *** empty log message ***
 *
 * Revision 1.3  2006/10/01 03:22:59  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:37:37  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 *
 */


// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "wx/image.h"                           // for some reason, needed for msvc???
#include "wx/tokenzr.h"
#include <wx/textfile.h>

#include "dychart.h"

#include "s52s57.h"
#include "s52plib.h"

#include "s57chart.h"
#include "nmea.h"                               // for Pause/UnPause

#include "mygeom.h"
#include "cutil.h"
#include "georef.h"

#include "cpl_csv.h"
#include "setjmp.h"

CPL_CVSID("$Id: s57chart.cpp,v 1.11 2008/01/10 03:38:32 bdbcat Exp $");


void OpenCPN_OGRErrorHandler( CPLErr eErrClass, int nError,
                              const char * pszErrorMsg );               // installed GDAL OGR library error handler

const char *MyCSVGetField( const char * pszFilename,
                         const char * pszKeyFieldName,
                         const char * pszKeyFieldValue,
                         CSVCompareCriteria eCriteria,
                         const char * pszTargetField ) ;



extern s52plib  *ps52plib;

extern int    user_user_id;
extern int    file_user_id;


static jmp_buf env_ogrf;                    // the context saved by setjmp();

#include <wx/arrimpl.cpp>                   // Implement an array of S57 Objects
WX_DEFINE_OBJARRAY(ArrayOfS57Obj);

//  This needs to be temporarily static so that S57OBJ ctor can use it to
//  convert SENC SM data to lat/lon for bounding boxes.
//  Eventually, goes into private data when chart rendering is done by
//  SM methods only.
//  At that point, S57OBJ works only in SM

static double s_ref_lat, s_ref_lon;

#define S57_THUMB_SIZE  200


//----------------------------------------------------------------------------------
//      S57Obj CTOR
//----------------------------------------------------------------------------------

S57Obj::S57Obj()
{
        attList = NULL;
        attVal = NULL;
        pPolyTessGeo = NULL;
        bCS_Added = 0;
        CSrules = NULL;
        FText = NULL;
        bFText_Added = 0;
        geoPtMulti = NULL;
        geoPtz = NULL;
        geoPt = NULL;
        bIsClone = false;
        Scamin = 10000000;                              // ten million enough?
        nRef = 0;
}

//----------------------------------------------------------------------------------
//      S57Obj DTOR
//----------------------------------------------------------------------------------

S57Obj::~S57Obj()
{
    //  Don't delete any allocated records of simple copy clones
    if(!bIsClone)
    {
        for(unsigned int iv = 0 ; iv < attVal->GetCount() ; iv++)
        {
            S57attVal *vv =  attVal->Item(iv);
            void *v2 = vv->value;
            free(v2);
            delete vv;
        }
        delete attVal;
        delete attList;


        delete pPolyTessGeo;

        if(FText)
        {
            delete FText->frmtd;    // the formatted text string
            free(FText);
        }

        if(geoPt)
            free(geoPt);
        if(geoPtz)
            free(geoPtz);
        if(geoPtMulti)
            free(geoPtMulti);
    }
}

//----------------------------------------------------------------------------------
//      S57Obj CTOR from SENC file
//----------------------------------------------------------------------------------

S57Obj::S57Obj(char *first_line, wxBufferedInputStream *pfpx)
{
    attList = NULL;
    attVal = NULL;
    pPolyTessGeo = NULL;
    bCS_Added = 0;
    CSrules = NULL;
    FText = NULL;
    bFText_Added = 0;
    bIsClone = false;

    geoPtMulti = NULL;
    geoPtz = NULL;
    geoPt = NULL;
    Scamin = 10000000;                              // ten million enough?
    nRef = 0;

    int FEIndex;

    int MAX_LINE = 499999;
    char *buf = (char *)malloc(MAX_LINE + 1);
    int llmax = 0;

    char szFeatureName[20];

    char *br;
    char szAtt[20];
    char geoMatch[20];

    bool bMulti = false;

    char *hdr_buf = (char *)malloc(1);

    if(strlen(first_line) == 0)
        return;
    strcpy(buf, first_line);

//    while(!dun)
    {

        if(!strncmp(buf, "OGRF", 4))
        {
            attList = new wxString();
            attVal =  new wxArrayOfS57attVal();

            FEIndex = atoi(buf+19);

            strncpy(szFeatureName, buf+11, 6);
            szFeatureName[6] = 0;
            strcpy(FeatureName, szFeatureName);

    //      Build/Maintain a list of found OBJL types for later use
    //      And back-reference the appropriate list index in S57Obj for Display Filtering

            bool bNeedNew = true;
            OBJLElement *pOLE;

            for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
            {
                pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));
                if(!strncmp(pOLE->OBJLName, szFeatureName, 6))
                {
                    iOBJL = iPtr;
                    bNeedNew = false;
                    break;
                }
            }

            if(bNeedNew)
            {
                pOLE = (OBJLElement *)malloc(sizeof(OBJLElement));
                strcpy(pOLE->OBJLName, szFeatureName);
                pOLE->nViz = 1;

                ps52plib->pOBJLArray->Add((void *)pOLE);
                iOBJL  = ps52plib->pOBJLArray->GetCount() - 1;
            }


    //      Walk thru the attributes, adding interesting ones
            int hdr_len = 0;
            char *mybuf_ptr;
            char *hdr_end;

            int prim = -1;
            int attdun = 0;

            strcpy(geoMatch, "Dummy");

            while(!attdun)
            {
                if(hdr_len)
                {
                    int nrl = my_bufgetl( mybuf_ptr, hdr_end, buf, MAX_LINE );
                    mybuf_ptr += nrl;
                    if(0 == nrl)
                    {
                        attdun = 1;
                        my_fgets(buf, MAX_LINE, *pfpx);     // this will be PolyGeo
                        break;
                    }
                }

                else
                    my_fgets(buf, MAX_LINE, *pfpx);


                if(!strncmp(buf, "HDRLEN", 6))
                {
                    hdr_len = atoi(buf+7);
                    hdr_buf = (char *)realloc(hdr_buf, hdr_len);
                    pfpx->Read(hdr_buf, hdr_len);
                    mybuf_ptr = hdr_buf;
                    hdr_end = hdr_buf + hdr_len;
                }

                else if(!strncmp(buf, geoMatch, 6))
                {
                    attdun =1;
                    break;
                }

                else if(!strncmp(buf, "  MULT", 6))         // Special multipoint
                {
                    bMulti = true;
                    attdun =1;
                    break;
                }



                else if(!strncmp(buf, "  PRIM", 6))
                {
                    prim = atoi(buf+13);
                    switch(prim)
                    {
                        case 1:
                        {
                            strcpy(geoMatch, "  POIN");
                            break;
                        }

                        case 2:                            // linestring
                        {
                            strcpy(geoMatch, "  LINE");
                            break;
                        }

                        case 3:                            // area as polygon
                        {
                            strcpy(geoMatch, "  POLY");
                            break;
                        }

                        default:                            // unrecognized
                        {
                            break;
                        }

                    }       //switch
                }               // if PRIM


                bool iua = IsUsefulAttribute(buf);

                szAtt[0] = 0;

                if(iua)
                {
                    S57attVal *pattValTmp = new S57attVal;

                    if(buf[10] == 'I')
                    {
                        br = buf+2;
                        int i=0;
                        while(*br != ' ')
                        {
                            szAtt[i++] = *br;
                            br++;
                        }

                        szAtt[i] = 0;

                        while(*br != '=')
                            br++;

                        br += 2;

                        int AValInt = atoi(br);
                        int *pAVI = (int *)malloc(sizeof(int));         //new int;
                        *pAVI = AValInt;
                        pattValTmp->valType = OGR_INT;
                        pattValTmp->value   = pAVI;

    //      Capture SCAMIN on the fly during load
                        if(!strcmp(szAtt, "SCAMIN"))
                            Scamin = AValInt;
                    }


                    else if(buf[10] == 'S')
                    {
                        strncpy(szAtt, &buf[2], 6);
                        szAtt[6] = 0;

                        br = buf + 15;

                        int nlen = strlen(br);
                        br[nlen-1] = 0;                                 // dump the NL char
                        char *pAVS = (char *)malloc(nlen + 1);          ;
                        strcpy(pAVS, br);

                        pattValTmp->valType = OGR_STR;
                        pattValTmp->value   = pAVS;
                    }


                    else if(buf[10] == 'R')
                    {
                        br = buf+2;
                        int i=0;
                        while(*br != ' ')
                        {
                            szAtt[i++] = *br;
                            br++;
                        }

                        szAtt[i] = 0;

                        while(*br != '=')
                            br++;

                        br += 2;

                        float AValReal;
                        sscanf(br, "%f", &AValReal);

                        float *pAVR = (float *)malloc(sizeof(float));   //new float;
                        *pAVR = AValReal;
                        pattValTmp->valType = OGR_REAL;
                        pattValTmp->value   = pAVR;
                    }

                    else
                    {
                              // unknown attribute type
    //                        CPLError((CPLErr)0, 0,"Unknown Attribute Type %s", buf);
                    }


                    if(strlen(szAtt))
                    {
                        attList->Append(szAtt);
                        attList->Append('\037');

                        attVal->Add(pattValTmp);
                    }
                    else
                        delete pattValTmp;

                }        //useful
            }               // while attdun



    //              Develop Geometry

            switch(prim)
            {
                case 1:
                {
                    if(!bMulti)
                    {
                        Primitive_type = GEO_POINT;

                        my_fgets(buf, MAX_LINE, *pfpx);
                        int wkb_len = atoi(buf+2);
                        pfpx->Read(buf,  wkb_len);

                        npt  = 1;
                        float *pfs = (float *)(buf + 5);                // point to the point

                        float easting, northing;
                        easting = *pfs++;
                        northing = *pfs;

                        x = easting;                                    // and save as SM
                        y = northing;

                        //  Convert from SM to lat/lon for bbox
                        double xll, yll;
                        fromSM(easting, northing, s_ref_lat, s_ref_lon, &yll, &xll);

                        BBObj.SetMin(xll, yll);
                        BBObj.SetMax(xll, yll);

                    }
                    else
                    {
                        Primitive_type = GEO_POINT;

                        my_fgets(buf, MAX_LINE, *pfpx);
                        int wkb_len = atoi(buf+2);
                        pfpx->Read(buf,  wkb_len);

                        npt = *((int *)(buf + 5));

                        geoPtz = (double *)malloc(npt * 3 * sizeof(double));
                        geoPtMulti = (double *)malloc(npt * 2 * sizeof(double));

                        double *pdd = geoPtz;
                        double *pdl = geoPtMulti;

                        float *pfs = (float *)(buf + 9);                 // start of data
                        for(int ip=0 ; ip<npt ; ip++)
                        {
                            float easting, northing;
                            easting = *pfs++;
                            northing = *pfs++;
                            float depth = *pfs++;

                            *pdd++ = easting;
                            *pdd++ = northing;
                            *pdd++ = depth;

                        //  Convert point from SM to lat/lon for later use in decomposed bboxes
                            double xll, yll;
                            fromSM(easting, northing, s_ref_lat, s_ref_lon, &yll, &xll);

                            *pdl++ = xll;
                            *pdl++ = yll;
                        }

                        // Capture bbox limits recorded in SENC record as lon/lat
                        float xmax = *pfs++;
                        float xmin = *pfs++;
                        float ymax = *pfs++;
                        float ymin = *pfs;

                        BBObj.SetMin(xmin, ymin);
                        BBObj.SetMax(xmax, ymax);

                    }
                    break;
                }

                case 2:                                                // linestring
                {
                    Primitive_type = GEO_LINE;


                    my_fgets(buf, MAX_LINE, *pfpx);
                    int sb_len = atoi(buf+2);

                    unsigned char *buft = (unsigned char *)malloc(sb_len);
                    pfpx->Read(buft,  sb_len);

                    npt = *((int *)(buft + 5));

                    geoPt = (pt*)malloc((npt) * sizeof(pt));
                    pt *ppt = geoPt;
                    float *pf = (float *)(buft + 9);

                        // Capture SM points
                    for(int ip = 0 ; ip < npt ; ip++)
                    {
                        ppt->x = *pf++;
                        ppt->y = *pf++;
                        ppt++;
                    }

                    // Capture bbox limits recorded as lon/lat
                    float xmax = *pf++;
                    float xmin = *pf++;
                    float ymax = *pf++;
                    float ymin = *pf;

                    delete buft;

                    // set s57obj bbox as lat/lon
                    BBObj.SetMin(xmin, ymin);
                    BBObj.SetMax(xmax, ymax);

                    //  and declare x/y of the object to be average east/north of all points
                    double e1, e2, n1, n2;
                    toSM(ymax, xmax, s_ref_lat, s_ref_lon, &e1, &n1);
                    toSM(ymin, xmin, s_ref_lat, s_ref_lon, &e2, &n2);

                    x = (e1 + e2) / 2.;
                    y = (n1 + n2) / 2.;

                   break;
                }

                case 3:                                                                 // area as polygon
                {
                    Primitive_type = GEO_AREA;

                    int ll = strlen(buf);
                    if(ll > llmax)
                        llmax = ll;

                    if(!strncmp(buf, "  POLYTESSGEO", 13))
                    {
                        int nrecl;
                        sscanf(buf, "  POLYTESSGEO %d", &nrecl);

                        if (nrecl)
                        {
                            unsigned char *polybuf = (unsigned char *)malloc(nrecl + 1);
                            pfpx->Read(polybuf,  nrecl);
                            polybuf[nrecl] = 0;                     // endit
                            PolyTessGeo *ppg = new PolyTessGeo(polybuf, nrecl, FEIndex);
                            free(polybuf);

                            pPolyTessGeo = ppg;

                            //  Set the s57obj bounding box as lat/lon
                            BBObj.SetMin(ppg->Get_xmin(), ppg->Get_ymin());
                            BBObj.SetMax(ppg->Get_xmax(), ppg->Get_ymax());

                            //  and declare x/y of the object to be average east/north of all points
                            double e1, e2, n1, n2;
                            toSM(ppg->Get_ymax(), ppg->Get_xmax(), s_ref_lat, s_ref_lon, &e1, &n1);
                            toSM(ppg->Get_ymin(), ppg->Get_xmin(), s_ref_lat, s_ref_lon, &e2, &n2);

                            x = (e1 + e2) / 2.;
                            y = (n1 + n2) / 2.;

                        }
                    }

                    break;
                }
            }       //switch




            if(prim > 0)
            {
               Index = FEIndex;
            }
        }               //OGRF
    }                       //while(!dun)

    free( buf );
    free(hdr_buf);

}

//-------------------------------------------------------------------------------------------
//      Attributes in SENC file may not be needed, and can be safely ignored when creating S57Obj
//      Look at a buffer, and return true or false according to a (default) definition
//-------------------------------------------------------------------------------------------

bool S57Obj::IsUsefulAttribute(char *buf)
{

    if(!strncmp(buf, "HDRLEN", 6))
        return false;

//      Dump the first 8 standard attributes
    /* -------------------------------------------------------------------- */
    /*      RCID                                                            */
    /* -------------------------------------------------------------------- */
    if(!strncmp(buf+2, "RCID", 4))
        return false;

    /* -------------------------------------------------------------------- */
    /*      LNAM                                                            */
    /* -------------------------------------------------------------------- */
    if(!strncmp(buf+2, "LNAM", 4))
        return false;

    /* -------------------------------------------------------------------- */
    /*      PRIM                                                            */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf+2, "PRIM", 4))
        return false;

    /* -------------------------------------------------------------------- */
    /*      SORDAT                                                          */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf+2, "SORDAT", 6))
        return false;

    /* -------------------------------------------------------------------- */
    /*      SORIND                                                          */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf+2, "SORIND", 6))
        return false;

    //      All others are "Useful"
    else
        return true;

#if (0)
    /* -------------------------------------------------------------------- */
    /*      GRUP                                                            */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf, "  GRUP", 6))
        return false;

    /* -------------------------------------------------------------------- */
    /*      OBJL                                                            */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf, "  OBJL", 6))
        return false;

    /* -------------------------------------------------------------------- */
    /*      RVER                                                            */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf, "  RVER", 6))
        return false;

    /* -------------------------------------------------------------------- */
    /*      AGEN                                                            */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf, "  AGEN", 6))
        return false;

    /* -------------------------------------------------------------------- */
    /*      FIDN                                                            */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf, "  FIDN", 6))
        return false;

    /* -------------------------------------------------------------------- */
    /*      FIDS                                                            */
    /* -------------------------------------------------------------------- */
    else if(!strncmp(buf, "  FIDS", 6))
        return false;

//      UnPresent data
    else if(strstr(buf, "(null)"))
        return false;

    else
        return true;
#endif
}

//------------------------------------------------------------------------------
//      Local version of fgets for Binary Mode (SENC) file
//------------------------------------------------------------------------------
 int S57Obj::my_fgets( char *buf, int buf_len_max, wxBufferedInputStream& ifs )

{
    char        chNext;
    int         nLineLen = 0;
    char            *lbuf;

    lbuf = buf;


    while( !ifs.Eof() && nLineLen < buf_len_max )
    {
        chNext = (char)ifs.GetC();

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

//------------------------------------------------------------------------------
//      Local version of bufgetl for Binary Mode (SENC) file
//------------------------------------------------------------------------------
 int S57Obj::my_bufgetl( char *ib_read, char *ib_end, char *buf, int buf_len_max )
{
    char        chNext;
    int         nLineLen = 0;
    char        *lbuf;
    char        *ibr = ib_read;

    lbuf = buf;


    while( (nLineLen < buf_len_max) && (ibr < ib_end))
    {
        chNext = *ibr++;

        /* each CR/LF (or LF/CR) as if just "CR" */
        if( chNext == 10 || chNext == 13 )
            chNext = '\n';

        *lbuf++ = chNext;
        nLineLen++;

        if( chNext == '\n' )
        {
            *lbuf = '\0';
            return nLineLen;
        }
    }

    *(lbuf) = '\0';
    return nLineLen;
}




//----------------------------------------------------------------------------------
//      s57chart Implementation
//----------------------------------------------------------------------------------

s57chart::s57chart()
{

    ChartType = CHART_TYPE_S57;

    for(int i=0 ; i<PRIO_NUM ; i++)
            for(int j=0 ; j<LUPNAME_NUM ; j++)
                    razRules[i][j] = NULL;

    NativeScale = 1.0;                              // Will be fetched during Init()

    pDIB = NULL;

    pFullPath = NULL;

    pFloatingATONArray = NULL;
    pRigidATONArray = NULL;

    tmpup_array = NULL;
    m_pcsv_locn = NULL;

    pDepthUnits->Append("METERS");
    m_depth_unit_id = DEPTH_UNIT_METERS;

    wxString csv_dir;
    if(wxGetEnv("S57_CSV", &csv_dir))
        m_pcsv_locn = new wxString(csv_dir);

    bGLUWarningSent = false;
}

s57chart::~s57chart()
{

    FreeObjectsAndRules();

    delete pDIB;

    delete pFullPath;

    delete pFloatingATONArray;
    delete pRigidATONArray;

    delete m_pcsv_locn;


}



void s57chart::GetValidCanvasRegion(const ViewPort& VPoint, wxRegion *pValidRegion)
{
        int rxl, rxr;
        rxl = 0;
        rxr = VPoint.pix_width;

        int ryb, ryt;
        ryt = 0;
        ryb = VPoint.pix_height;

        pValidRegion->Clear();
        pValidRegion->Union(rxl, ryt, rxr - rxl, ryb - ryt);

}

void s57chart::SetColorScheme(ColorScheme cs, bool bApplyImmediate)
{
    //  Here we convert (subjectively) the Global ColorScheme
    //  to an appropriate S52 Col_Scheme_t index.

    switch(cs)
    {
        case GLOBAL_COLOR_SCHEME_DAY:
            m_S52_color_index = S52_DAY_BRIGHT;
            break;
        case GLOBAL_COLOR_SCHEME_DUSK:
            m_S52_color_index = S52_DUSK;
            break;
        case GLOBAL_COLOR_SCHEME_NIGHT:
            m_S52_color_index = S52_NIGHT;
            break;
        default:
            m_S52_color_index = S52_DAY_BRIGHT;
            break;
    }

    m_global_color_scheme = cs;

    if(bApplyImmediate)
        InvalidateCache();
}

void s57chart::GetChartExtent(Extent *pext)
{
    *pext = FullExtent;
}


void s57chart::FreeObjectsAndRules()
{
//      Delete the created ObjRazRules, including the S57Objs
    ObjRazRules *top;
    ObjRazRules *nxx;
    for (int i=0; i<PRIO_NUM; ++i)
    {
        for(int j=0 ; j<LUPNAME_NUM ; j++)
        {

            top = razRules[i][j];
            while ( top != NULL)
            {
                top->obj->nRef--;
                if(0 == top->obj->nRef)
                    delete top->obj;

                nxx  = top->next;
                free(top);
                top = nxx;
            }
        }
    }
 }


//-----------------------------------------------------------------------
//              Pixel to Lat/Long Conversion helpers
//-----------------------------------------------------------------------

void s57chart::GetPointPix(ObjRazRules *rzRules, float north, float east, wxPoint *r)
{
    r->x = (int)round(((east - easting_vp_center) * view_scale_ppm) + x_vp_center);
    r->y = (int)round(y_vp_center - ((north - northing_vp_center) * view_scale_ppm));
}

void s57chart::GetPixPoint(int pixx, int pixy, double *plat, double *plon, ViewPort *vpt)
{
     //    Use Mercator estimator
    int dx = pixx - (vpt->pix_width / 2);
    int dy = (vpt->pix_height / 2) - pixy;

    double xp = (dx * cos(vpt->skew)) - (dy * sin(vpt->skew));
    double yp = (dy * cos(vpt->skew)) + (dx * sin(vpt->skew));

    double d_east = xp / vpt->view_scale_ppm;
    double d_north = yp / vpt->view_scale_ppm;

    double slat, slon;
    fromSM(d_east, d_north, vpt->clat, vpt->clon, &slat, &slon);

    *plat = slat;
    *plon = slon;

}

//-----------------------------------------------------------------------
//              Calculate and Set ViewPoint Constants
//-----------------------------------------------------------------------

void s57chart::SetVPParms(ViewPort *vpt)
{
    //  Set up local SM rendering constants
    x_vp_center = vpt->pix_width / 2;
    y_vp_center = vpt->pix_height / 2;
    view_scale_ppm = vpt->view_scale_ppm;

    easting_vp_center = vpt->c_east;
    northing_vp_center = vpt->c_north;
}


ThumbData *s57chart::GetThumbData(int tnx, int tny, float lat, float lon)
{
    //  Plot the passed lat/lon at the thumbnail bitmap scale
    //  Using simple linear algorithm.
        if( pThumbData->pDIBThumb)
        {
                float lat_top =   FullExtent.NLAT;
                float lat_bot =   FullExtent.SLAT;
                float lon_left =  FullExtent.WLON;
                float lon_right = FullExtent.ELON;

                // Build the scale factors just as the thumbnail was built
                float ext_max = fmax((lat_top - lat_bot), (lon_right - lon_left));

                float thumb_view_scale_ppm = (S57_THUMB_SIZE/ ext_max) / (1852 * 60);
                double east, north;
                toSM(lat, lon, (lat_top + lat_bot) / 2., (lon_left + lon_right) / 2., &east, &north);

                pThumbData->ShipX = pThumbData->pDIBThumb->GetWidth()  / 2 + (int)(east  * thumb_view_scale_ppm);
                pThumbData->ShipY = pThumbData->pDIBThumb->GetHeight() / 2 - (int)(north * thumb_view_scale_ppm);

        }
        else
        {
                pThumbData->ShipX = 0;
                pThumbData->ShipY = 0;
        }

        return pThumbData;
}

bool s57chart::UpdateThumbData(float lat, float lon)
{
    //  Plot the passed lat/lon at the thumbnail bitmap scale
    //  Using simple linear algorithm.
    int test_x, test_y;
    if( pThumbData->pDIBThumb)
    {
        float lat_top =   FullExtent.NLAT;
        float lat_bot =   FullExtent.SLAT;
        float lon_left =  FullExtent.WLON;
        float lon_right = FullExtent.ELON;

                // Build the scale factors just as the thumbnail was built
        float ext_max = fmax((lat_top - lat_bot), (lon_right - lon_left));

        float thumb_view_scale_ppm = (S57_THUMB_SIZE/ ext_max) / (1852 * 60);
        double east, north;
        toSM(lat, lon, (lat_top + lat_bot) / 2., (lon_left + lon_right) / 2., &east, &north);

        test_x = pThumbData->pDIBThumb->GetWidth()  / 2 + (int)(east  * thumb_view_scale_ppm);
        test_y = pThumbData->pDIBThumb->GetHeight() / 2 - (int)(north * thumb_view_scale_ppm);

    }
    else
    {
        test_x = 0;
        test_y = 0;
    }

    if((test_x != pThumbData->ShipX) || (test_y != pThumbData->ShipY))
    {
        pThumbData->ShipX = test_x;
        pThumbData->ShipY = test_y;
        return TRUE;
    }
    else
        return FALSE;
}



void s57chart::SetFullExtent(Extent& ext)
{
  FullExtent.NLAT = ext.NLAT;
  FullExtent.SLAT = ext.SLAT;
  FullExtent.WLON = ext.WLON;
  FullExtent.ELON = ext.ELON;
}


void s57chart::RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type)
{
    ps52plib->SetColorScheme(m_S52_color_index);

    DoRenderViewOnDC(dc, VPoint, DC_RENDER_ONLY);
}



void s57chart::DoRenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, RenderTypeEnum option)
{
    wxPoint rul, rlr;

//        int bpp = BPP;          // use global value

    bool bNewVP = false;


        //Todo Add a check on last_vp.bValid
    if(VPoint.view_scale_ppm != last_vp.view_scale_ppm)
    {
        bNewVP = true;
        delete pDIB;
        pDIB = NULL;
    }

//      Calculate the desired rectangle in the last cached image space
    double easting_ul, northing_ul;
    double easting_lr, northing_lr;

    easting_ul =  VPoint.c_east -  ((VPoint.pix_width  / 2) / view_scale_ppm);
    northing_ul = VPoint.c_north + ((VPoint.pix_height / 2) / view_scale_ppm);
    easting_lr = easting_ul + (VPoint.pix_width / view_scale_ppm);
    northing_lr = northing_ul - (VPoint.pix_height / view_scale_ppm);

    prev_easting_ul =  last_vp.c_east -  ((last_vp.pix_width  / 2) / view_scale_ppm);
    prev_northing_ul = last_vp.c_north + ((last_vp.pix_height / 2) / view_scale_ppm);
    prev_easting_lr = easting_ul + (last_vp.pix_width / view_scale_ppm);
    prev_northing_lr = northing_ul - (last_vp.pix_height / view_scale_ppm);


    rul.x = (int)round((easting_ul - prev_easting_ul) * view_scale_ppm);
    rul.y = (int)round((prev_northing_ul - northing_ul) * view_scale_ppm);

    rlr.x = (int)round((easting_lr - prev_easting_ul) * view_scale_ppm);
    rlr.y = (int)round((prev_northing_ul - northing_lr) * view_scale_ppm);

    if((rul.x != 0) || (rul.y != 0))
        bNewVP = true;

    //      Using regions, calculate re-usable area of pDIB

    wxRegion rgn_last(0, 0, VPoint.pix_width, VPoint.pix_height);
    wxRegion rgn_new(rul.x, rul.y, rlr.x - rul.x, rlr.y - rul.y);
    rgn_last.Intersect(rgn_new);            // intersection is reusable portion


    if(bNewVP && (NULL != pDIB) && !rgn_last.IsEmpty())
    {

        int xu, yu, wu, hu;
        rgn_last.GetBox(xu, yu, wu, hu);

        int desx = 0;
        int desy = 0;
        int srcx = xu;
        int srcy = yu;

        if(rul.x < 0)
        {
            srcx = 0;
            desx = -rul.x;
        }
        if(rul.y < 0)
        {
            srcy = 0;
            desy = -rul.y;
        }

        ocpnMemDC dc_last;
        pDIB->SelectIntoDC(dc_last);

        ocpnMemDC dc_new;
        PixelCache *pDIBNew = new PixelCache(VPoint.pix_width, VPoint.pix_height, BPP);
        pDIBNew->SelectIntoDC(dc_new);

//                    printf("blit %d %d %d %d %d %d\n",desx, desy, wu, hu,  srcx, srcy);
        dc_new.Blit(desx, desy, wu, hu, (wxDC *)&dc_last, srcx, srcy, wxCOPY);

        dc_new.SelectObject(wxNullBitmap);
        dc_last.SelectObject(wxNullBitmap);

        delete pDIB;
        pDIB = pDIBNew;

//              OK, now have the re-useable section in place
//              Next, build the new sections

        pDIB->SelectIntoDC(dc);

        wxRegion rgn_delta(0, 0, VPoint.pix_width, VPoint.pix_height);
        wxRegion rgn_reused(desx, desy, wu, hu);
        rgn_delta.Subtract(rgn_reused);

        wxRegionIterator upd(rgn_delta); // get the update rect list
        while (upd)
        {
            wxRect rect = upd.GetRect();


//      Build temp ViewPort on this region

            ViewPort temp_vp = VPoint;

            double temp_northing_ul = prev_northing_ul - (rul.y / view_scale_ppm) - (rect.y / view_scale_ppm);
            double temp_easting_ul = prev_easting_ul + (rul.x / view_scale_ppm) + (rect.x / view_scale_ppm);
            fromSM(temp_easting_ul, temp_northing_ul, ref_lat, ref_lon, &temp_vp.lat_top, &temp_vp.lon_left);

            double temp_northing_lr = temp_northing_ul - (rect.height / view_scale_ppm);
            double temp_easting_lr = temp_easting_ul + (rect.width / view_scale_ppm);
            fromSM(temp_easting_lr, temp_northing_lr, ref_lat, ref_lon, &temp_vp.lat_bot, &temp_vp.lon_right);

            temp_vp.vpBBox.SetMin(temp_vp.lon_left, temp_vp.lat_bot);
            temp_vp.vpBBox.SetMax(temp_vp.lon_right, temp_vp.lat_top);

            //      Allow some slop in the viewport
            temp_vp.vpBBox.EnLarge(temp_vp.vpBBox.GetWidth() * .05);

//      And Render it new piece on the target dc
//     printf("Reuse, rendering %d %d %d %d \n", rect.x, rect.y, rect.width, rect.height);
            DCRenderRect(dc, temp_vp, &rect);

            upd ++ ;
        }

        dc.SelectObject(wxNullBitmap);
    }

    else if(bNewVP || (NULL == pDIB))
    {
        delete pDIB;
        pDIB = new PixelCache(VPoint.pix_width, VPoint.pix_height, BPP);     // destination
//    pDIB->SelectIntoDC(dc);

        wxRect full_rect(0, 0,VPoint.pix_width, VPoint.pix_height);
        pDIB->SelectIntoDC(dc);
        DCRenderRect(dc, VPoint, &full_rect);

        dc.SelectObject(wxNullBitmap);
    }

//      Update last_vp to reflect the current cached bitmap
        last_vp = VPoint;

    pDIB->SelectIntoDC(dc);

}



int s57chart::DCRenderRect(wxMemoryDC& dcinput, ViewPort& vp, wxRect* rect)
{

    int i;
    ObjRazRules *top;
    ObjRazRules *crnt;

    render_canvas_parms pb_spec;

//      Get some heap memory for the area renderer

      pb_spec.depth = BPP;                              // set the depth

        if(rect)
        {
                pb_spec.pb_pitch = ((rect->width * pb_spec.depth / 8 ));
                pb_spec.lclip = rect->x;
                pb_spec.rclip = rect->x + rect->width - 1;
                pb_spec.pix_buff = (unsigned char *)malloc(rect->height * pb_spec.pb_pitch);
                if(NULL == pb_spec.pix_buff)
                    wxLogMessage("PixBuf NULL 1");

                // Preset background
                memset(pb_spec.pix_buff, 0,rect->height * pb_spec.pb_pitch);
                pb_spec.width = rect->width;
                pb_spec.height = rect->height;
                pb_spec.x = rect->x;
                pb_spec.y = rect->y;
        }
        else
        {
                pb_spec.pb_pitch = ((vp.pix_width * pb_spec.depth / 8 )) ;
                pb_spec.lclip = 0;
                pb_spec.rclip = vp.pix_width-1;
                pb_spec.pix_buff = (unsigned char *)malloc(vp.pix_height * pb_spec.pb_pitch);
                // Preset background
                memset(pb_spec.pix_buff, 0,vp.pix_height * pb_spec.pb_pitch);
                pb_spec.width = vp.pix_width;
                pb_spec.height  = vp.pix_height;
                pb_spec.x = 0;
                pb_spec.y = 0;
        }

//      Render the areas quickly
    for (i=0; i<PRIO_NUM; ++i)
    {
                top = razRules[i][4];           // Area Symbolized Boundaries
                while ( top != NULL)
                {
                        crnt = top;
                        top  = top->next;               // next object
                        ps52plib->RenderArea(&dcinput, crnt, &vp, &pb_spec);
                }

                top = razRules[i][3];           // Area Plain Boundaries
                while ( top != NULL)
                {
                        crnt = top;
                        top  = top->next;               // next object
                        ps52plib->RenderArea(&dcinput, crnt, &vp, &pb_spec);
                }
    }



//      Convert the Private render canvas into a bitmap
#ifdef ocpnUSE_ocpnBitmap
        ocpnBitmap *pREN = new ocpnBitmap(pb_spec.pix_buff,
                                                pb_spec.width, pb_spec.height, pb_spec.depth);
#else
        wxImage *prender_image = new wxImage(pb_spec.width, pb_spec.height);
        prender_image->SetData((unsigned char*)pb_spec.pix_buff);
        wxBitmap *pREN = new wxBitmap(*prender_image);

#endif

//      Map it into a temporary DC
        wxMemoryDC dc_ren;
        dc_ren.SelectObject(*pREN);

//      Blit it onto the target dc
        dcinput.Blit(pb_spec.x, pb_spec.y, pb_spec.width, pb_spec.height, (wxDC *)&dc_ren, 0,0);


//      And clean up the mess
        dc_ren.SelectObject(wxNullBitmap);


#ifdef ocpnUSE_ocpnBitmap
        free(pb_spec.pix_buff);
#else
        delete prender_image;           // the image owns the data
                                        // and so will free it in due course
#endif

        delete pREN;



//      Render the rest of the objects/primitives

        DCRenderLPB(dcinput, vp, rect);

        return 1;
}

bool s57chart::DCRenderLPB(wxMemoryDC& dcinput, ViewPort& vp, wxRect* rect)
{
    int i;
    ObjRazRules *top;
    ObjRazRules *crnt;


    for (i=0; i<PRIO_NUM; ++i)
    {
//      Set up a Clipper for Lines
        wxDCClipper *pdcc = NULL;
        if(rect)
        {
            wxRect nr = *rect;
 //         pdcc = new wxDCClipper(dcinput, nr);
        }

        top = razRules[i][2];           //LINES
        while ( top != NULL)
        {
            ObjRazRules *crnt = top;
            top  = top->next;
            ps52plib->_draw(&dcinput, crnt, &vp);


        }

        if(ps52plib->m_nSymbolStyle == SIMPLIFIED)
        {
            top = razRules[i][0];           //SIMPLIFIED Points
            while ( top != NULL)
            {
                crnt = top;
                top  = top->next;
                ps52plib->_draw(&dcinput, crnt, &vp);

            }
        }
        else
        {
            top = razRules[i][1];           //Paper Chart Points Points
            while ( top != NULL)
            {
                crnt = top;
                top  = top->next;
                ps52plib->_draw(&dcinput, crnt, &vp);

            }
        }

        if(ps52plib->m_nBoundaryStyle == SYMBOLIZED_BOUNDARIES)
        {
            top = razRules[i][4];           // Area Symbolized Boundaries
            while ( top != NULL)
            {
                crnt = top;
                top  = top->next;               // next object
                ps52plib->_draw(&dcinput, crnt, &vp);
            }
        }

        else
        {
            top = razRules[i][3];           // Area Plain Boundaries
            while ( top != NULL)
            {
                crnt = top;
                top  = top->next;               // next object
                ps52plib->_draw(&dcinput, crnt, &vp);
            }
        }

        //      Destroy Clipper
        if(pdcc)
            delete pdcc;
    }

/*
        printf("Render Lines                  %ldms\n", stlines.Time());
        printf("Render Simple Points          %ldms\n", stsim_pt.Time());
        printf("Render Paper Points           %ldms\n", stpap_pt.Time());
        printf("Render Symbolized Boundaries  %ldms\n", stasb.Time());
        printf("Render Plain Boundaries       %ldms\n\n", stapb.Time());
*/
        return true;
}


InitReturn s57chart::Init( const wxString& name, ChartInitFlag flags, ColorScheme cs )
{
    pFullPath = new wxString(name);

    //  Establish a common reference point for the chart
    ref_lat = (FullExtent.NLAT + FullExtent.SLAT) /2.;
    ref_lon = (FullExtent.WLON + FullExtent.ELON) /2.;

    //  Todo Eventually s_ref_lat/lon goes away.
    s_ref_lat = ref_lat;
    s_ref_lon = ref_lon;

// Look for Thumbnail
        wxFileName ThumbFileNameLook(name);
        ThumbFileNameLook.SetExt("BMP");

        wxBitmap *pBMP;
        if(ThumbFileNameLook.FileExists())
        {
#ifdef ocpnUSE_ocpnBitmap
                pBMP =  new ocpnBitmap;
#else
                pBMP =  new wxBitmap;
#endif
                pBMP->LoadFile(ThumbFileNameLook.GetFullPath(), wxBITMAP_TYPE_BMP );
                pThumbData->pDIBThumb = pBMP;

        }

        if(flags == THUMB_ONLY)
                return INIT_OK;

 // Really can only Init and use S57 chart if the S52 Presentation Library is OK
    if(!ps52plib->m_bOK)
      return INIT_FAIL_REMOVE;

        int build_ret_val = 1;

        bool bbuild_new_senc = false;

//      Look for S57 file in the target directory
        pS57FileName = new wxFileName(name);
        pS57FileName->SetExt("S57");

        if(pS57FileName->FileExists())
        {
                wxFile f;
                if(f.Open(pS57FileName->GetFullPath()))
                {
                        if(f.Length() == 0)
                        {
                                f.Close();
                                build_ret_val = BuildS57File( name.c_str() );
                        }
                        else                                      // file exists, non-zero
                        {                                         // so check for new updates

                                f.Seek(0);
                                wxFileInputStream *pfpx_u = new wxFileInputStream(f);
                                wxBufferedInputStream *pfpx = new wxBufferedInputStream(*pfpx_u);
                                int dun = 0;
                                int last_update = 0;
                                int senc_file_version = 0;
                                int force_make_senc = 0;
                                char buf[256];
                                char *pbuf = buf;

                                while( !dun )
                                {
                                        if(my_fgets(pbuf, 256, *pfpx) == 0)
                                        {
                                                dun = 1;
                                                force_make_senc = 1;
                                                break;
                                        }
                                        else
                                        {
                                                if(!strncmp(pbuf, "OGRF", 4))
                                                {
                                                        dun = 1;
                                                        break;
                                                }
                                                else if(!strncmp(pbuf, "UPDT", 4))
                                                {
                                                        sscanf(pbuf, "UPDT=%i", &last_update);
                                                }
                                                else if(!strncmp(pbuf, "SENC", 4))
                                                {
                                                    sscanf(pbuf, "SENC Version=%i", &senc_file_version);
                                                }
                                        }
                                }

                                delete pfpx;
                                delete pfpx_u;
                                f.Close();
//              Anything to do?

// force_make_senc = 1;
                                wxString DirName(pS57FileName->GetPath((int)wxPATH_GET_SEPARATOR));
                                int most_recent_update_file = GetUpdateFileArray(DirName, NULL);

                                if(last_update != most_recent_update_file)
                                {
                                    bool bupdate_possible = s57_ddfrecord_test();
                                    bbuild_new_senc = bupdate_possible;
                                }

                                else if(senc_file_version != CURRENT_SENC_FORMAT_VERSION)
                                    bbuild_new_senc = true;

                                else if(force_make_senc)
                                    bbuild_new_senc = true;

                                if(bbuild_new_senc)
                                      build_ret_val = BuildS57File( name.c_str() );


                        }
                }
        }

        else                    // SENC file does not exist
        {
                build_ret_val = BuildS57File( name.c_str() );
                bbuild_new_senc = true;
        }

        if(0 == build_ret_val)
                return INIT_FAIL_RETRY;


        BuildRAZFromS57File( (pS57FileName->GetFullPath()).c_str() );


        //      Check for and if necessary build Thumbnail
        wxFileName ThumbFileName(name);
        ThumbFileName.SetExt("BMP");

        if(!ThumbFileName.FileExists() || bbuild_new_senc)
        {

                //      Set up a private ViewPort
                ViewPort vp;

                vp.clon = (FullExtent.ELON + FullExtent.WLON) / 2.;
                vp.clat = (FullExtent.NLAT + FullExtent.SLAT) / 2.;
                vp.lat_top =   FullExtent.NLAT;
                vp.lat_bot =   FullExtent.SLAT;
                vp.lon_left =  FullExtent.WLON;
                vp.lon_right = FullExtent.ELON;

                float ext_max = fmax((vp.lat_top - vp.lat_bot), (vp.lon_right - vp.lon_left));

                vp.view_scale_ppm = (S57_THUMB_SIZE/ ext_max) / (1852 * 60);

                vp.pix_height = S57_THUMB_SIZE;
                vp.pix_width  = S57_THUMB_SIZE;

                vp.vpBBox.SetMin(vp.lon_left, vp.lat_bot);
                vp.vpBBox.SetMax(vp.lon_right, vp.lat_top);

                vp.chart_scale = 10000000 - 1;
                vp.bValid = true;
                //Todo this becomes last_vp.bValid = false;
                last_vp.view_scale_ppm = -1;                // cause invalidation of cache
                SetVPParms(&vp);


//      Borrow the OBJLArray temporarily to set the object type visibility for this render
//      First, make a copy for the curent OBJLArray viz settings, setting current value to invisible

                unsigned int OBJLCount = ps52plib->pOBJLArray->GetCount();
                int *psave_viz = new int[OBJLCount];
                int *psvr = psave_viz;
                OBJLElement *pOLE;
                unsigned int iPtr;

                for(iPtr = 0 ; iPtr < OBJLCount ; iPtr++)
                {
                        pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));
                        *psvr++ = pOLE->nViz;
                        pOLE->nViz = 0;
                }

//      Now, set up what I want for this render
                for(iPtr = 0 ; iPtr < OBJLCount ; iPtr++)
                {
                        pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));
                        if(!strncmp(pOLE->OBJLName, "LNDARE", 6))
                                pOLE->nViz = 1;
                        if(!strncmp(pOLE->OBJLName, "DEPARE", 6))
                                pOLE->nViz = 1;
                }

//      Use display category MARINERS_STANDARD to force use of OBJLArray
                DisCat dsave = ps52plib->m_nDisplayCategory;
                ps52plib->m_nDisplayCategory = MARINERS_STANDARD;

#ifdef ocpnUSE_DIBSECTION
                ocpnMemDC memdc, dc_org;
#else
                wxMemoryDC memdc, dc_org;
#endif

//      set the color scheme
                ps52plib->SetColorScheme(S52_DAY_BRIGHT);

//      Do the render
                DoRenderViewOnDC(memdc, vp, DC_RENDER_ONLY);

//      Release the DIB
                memdc.SelectObject(wxNullBitmap);

//      Restore the plib to previous state
                psvr = psave_viz;
                for(iPtr = 0 ; iPtr < OBJLCount ; iPtr++)
                {
                        pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));
                        pOLE->nViz = *psvr++;
                }

                ps52plib->m_nDisplayCategory = dsave;

//      Reset the color scheme
                ps52plib->SetColorScheme(m_S52_color_index);

                delete psave_viz;

//      Clone pDIB into pThumbData;
                wxBitmap *pBMP;

#ifdef ocpnUSE_ocpnBitmap
                pBMP = new ocpnBitmap((unsigned char *)NULL,
                vp.pix_width, vp.pix_height, BPP);
#else
                pBMP = new wxBitmap(/*NULL,*/
                        vp.pix_width, vp.pix_height, BPP);
#endif
                wxMemoryDC dc_clone;
                dc_clone.SelectObject(*pBMP);

                pDIB->SelectIntoDC(dc_org);

                dc_clone.Blit(0,0,vp.pix_width, vp.pix_height,
                              (wxDC *)&dc_org, 0,0);

                dc_clone.SelectObject(wxNullBitmap);
                dc_org.SelectObject(wxNullBitmap);

//    May Need root to create the Thumbnail file
#ifndef __WXMSW__
                seteuid(file_user_id);
#endif
                pBMP->SaveFile(ThumbFileName.GetFullPath(), wxBITMAP_TYPE_BMP);

//  Update the member thumbdata structure
                wxBitmap *pBMP_NEW;
#ifdef ocpnUSE_ocpnBitmap
                pBMP_NEW =  new ocpnBitmap;
#else
                pBMP_NEW =  new wxBitmap;
#endif
                if(pBMP_NEW->LoadFile(ThumbFileName.GetFullPath(), wxBITMAP_TYPE_BMP ))
                {
                    delete pThumbData;
                    pThumbData = new ThumbData;
                    pThumbData->pDIBThumb = pBMP_NEW;
                }



 //   Return to default user priveleges
#ifndef __WXMSW__
                seteuid(user_user_id);
#endif

        }
        delete pS57FileName;

        m_global_color_scheme = cs;
        SetColorScheme(cs, false);

        bReadyToRender = true;

        return INIT_OK;
}

void s57chart::InvalidateCache()
{
        if(pDIB)
        {
                delete pDIB;
                pDIB = NULL;
        }

}


void s57chart::GetChartNameFromTXT(const wxString& FullPath, wxString &Name)
{

      wxFileName fn(FullPath);

      wxString target_name = fn.GetName();
 //     target_name.SetChar(target_name.Len()-1, 'E');
      target_name.RemoveLast();                             // Todo is this OK to use, eg US2EC03 ??

      wxString dir_name = fn.GetPath();

      wxDir dir(dir_name);                                  // The directory containing the file

      wxArrayString *pFileList = new wxArrayString();

      dir.GetAllFiles(fn.GetPath(), pFileList);             // list all the files

      //    Iterate on the file list...

      bool found_name = false;
      wxString name;
      name.Clear();

      for(unsigned int j=0 ; j<pFileList->GetCount() ; j++)
      {
            wxFileName file(pFileList->Item(j));
            if(((file.GetExt()).MakeUpper()) == "TXT")
            {
              //  Look for the line beginning with the name of the .000 file
              wxTextFile text_file(file.GetFullPath());
              text_file.Open();

              wxString str = text_file.GetFirstLine();
              while(!text_file.Eof())
              {
                if(0 == target_name.CmpNoCase(str.Mid(0, target_name.Len())))
                {                                                       // found it
                  wxString tname = str.AfterFirst('-');
                  name = tname.AfterFirst(' ');
                  found_name = true;
                  break;
                }
                else
                {
                  str = text_file.GetNextLine();
                }
              }

              text_file.Close();

              if(found_name)
                break;
            }
      }

      Name = name;

      delete pFileList;

}







//---------------------------------------------------------------------------------
//      S57 Database methods
//---------------------------------------------------------------------------------


//-------------------------------
//
// S57 OBJECT ACCESSOR SECTION
//
//-------------------------------

const char *s57chart::getName(OGRFeature *feature)
{
   return feature->GetDefnRef()->GetName();
}

static int ExtensionCompare(const wxString& first, const wxString& second)
{
        wxFileName fn1(first);
        wxFileName fn2(second);
        wxString ext1(fn1.GetExt());
        wxString ext2(fn2.GetExt());

    return ext1.Cmp(ext2);
}


int s57chart::GetUpdateFileArray(const wxString& DirName, wxArrayString *UpFiles)
{
        wxDir dir(DirName);
        wxString ext;
        wxArrayString *dummy_array;
        int retval = 0;

        if(UpFiles == NULL)
                dummy_array = new wxArrayString;
        else
                dummy_array = UpFiles;

        wxString filename;
        bool cont = dir.GetFirst(&filename);
        while ( cont )
        {
                wxFileName file(filename);
                ext = file.GetExt();
                if(ext.IsNumber() && ext.CmpNoCase("000"))
                {
                        wxString FileToAdd(DirName);
                        FileToAdd.Append(file.GetFullName());
                        dummy_array->Add(FileToAdd);
                }

                cont = dir.GetNext(&filename);
        }

//      Sort the candidates

        dummy_array->Sort(ExtensionCompare);

//      Get the update number of the last in the list
        if(dummy_array->GetCount())
        {
                wxString Last = dummy_array->Last();
                wxFileName fnl(Last);
                ext = fnl.GetExt();
                retval = atoi(ext.c_str());
        }

        if(UpFiles == NULL)
                delete dummy_array;

        return retval;
}


int s57chart::CountUpdates( const wxString& DirName, wxString &LastUpdateDate)
{

        int retval = 0;

        wxDir dir(DirName);
        wxArrayString *UpFiles = new wxArrayString;
        retval = GetUpdateFileArray(DirName, UpFiles);

        if(retval)
        {
            //      The s57reader of ogr requires that update set be sequentially complete
            //      to perform all the updates.  However, some NOAA ENC distributions are
            //      not complete, as apparently some interim updates have been  withdrawn.
            //      Example:  as of 20 Dec, 2005, the update set for US5MD11M.000 includes
            //      US5MD11M.017, ...018, and ...019.  Updates 001 through 016 are missing.
            //
            //      Workaround.
            //      Create temporary dummy update files to fill out the set before invoking
            //      ogr file open/ingest.  Delete after SENC file create finishes.


            tmpup_array = new wxArrayString;                // save a list of created files for later erase

            for(int iff=1 ; iff < retval ; iff++)
            {
                wxFileName ufile(*pFullPath);
                wxString sext;
                sext.Printf("%03d", iff);
                ufile.SetExt(sext);


                //      Explicit check for a short update file, possibly left over from a crash...
                int flen = 0;
                if(ufile.FileExists())
                {
                    wxFile uf(ufile.GetFullPath());
                    if(uf.IsOpened())
                    {
                        flen = uf.Length();
                        uf.Close();
                    }
                }

                if(ufile.FileExists() && (flen > 25))           // a valid update file
                    continue;

                // Create a dummy ISO8211 file with no real content

                bool bstat;
                DDFModule *dupdate = new DDFModule;
                dupdate->Initialize( '3','L','E','1','0',"!!!",3,4,4 );
                bstat = (bool)dupdate->Create(ufile.GetFullPath().c_str());
                dupdate->Close();

                if(!bstat)
                    wxLogMessage("Error creating dummy update file %s",ufile.GetFullPath().c_str());


                tmpup_array->Add(ufile.GetFullPath());
            }



            //      Extract the date field from the last of the update files
            //      which is by definition a vail, present update file....
            bool bSuccess;
            DDFModule oUpdateModule;

            bSuccess = (bool)oUpdateModule.Open( UpFiles->Last().c_str(), TRUE );

            if( bSuccess )
            {
//      Get publish/update date
                oUpdateModule.Rewind();
                DDFRecord *pr = oUpdateModule.ReadRecord();                     // Record 0

                int nSuccess;
                char *u = (char *)(pr->GetStringSubfield("DSID", 0, "ISDT", 0, &nSuccess));

                LastUpdateDate = wxString(u);
            }
        }

        delete UpFiles;
        return retval;
}



int s57chart::BuildS57File(const char *pFullPath)
{

    OGRFeature *objectDef;
    int nProg = 0;

    wxString nice_name;
    GetChartNameFromTXT(wxString(pFullPath), nice_name);


    wxFileName s57file = wxFileName(pFullPath);
    s57file.SetExt("S57");

    OGREnvelope xt;

    //      Only allow updates if ISO8211 library can do it.
    bool benable_update = s57_ddfrecord_test();


    wxString date000;
    int native_scale = 1;


    //      Fetch the Geo Feature Count, or something like it....


    DDFModule *poModule = new DDFModule();
    if(!poModule->Open( pFullPath ))
    {
        wxLogMessage("s57chart::BuildS57File  Unable to open %s )",pFullPath);
        return 0;
    }


    poModule->Rewind();
    DDFRecord *pr = poModule->ReadRecord();                               // Record 0

    int nSuccess;
    nGeoRecords = pr->GetIntSubfield("DSSI", 0, "NOGR", 0, &nSuccess);

// Todo I'll use ISDT here... but what is UADT?
    char *u = (char *)(pr->GetStringSubfield("DSID", 0, "ISDT", 0, &nSuccess));
    if(u)
        date000 = u;

//      Fetch the Native Scale
    for( ; pr != NULL; pr = poModule->ReadRecord() )
    {
        if( pr->FindField( "DSPM" ) != NULL )
        {
            native_scale = pr->GetIntSubfield("DSPM",0,"CSCL",0);
                        break;
        }
    }

    delete poModule;




    wxFileName tfn;
    wxString tmp_file = tfn.CreateTempFileName("");


    FILE *fps57;
    fps57 = fopen(tmp_file.c_str(), "wb");

    if(fps57 == NULL)
    {
            wxLogMessage("s57chart::BuildS57File  Unable to create %s )",s57file.GetFullPath().c_str());
            return 0;
    }

    fprintf(fps57, "SENC Version= %d\n", CURRENT_SENC_FORMAT_VERSION);
    fprintf(fps57, "NAME=%s\n", nice_name.c_str());
    fprintf(fps57, "DATE000=%s\n", date000.c_str());
    fprintf(fps57, "NOGR=%d\n", nGeoRecords);
    fprintf(fps57, "SCALE=%d\n", native_scale);

    wxString Message = s57file.GetFullPath();
    Message.Append("...Ingesting");

    wxString Title(_T("OpenCPN S57 SENC File Create..."));
    Title.append(s57file.GetFullPath());

    wxProgressDialog    *SENC_prog;
    SENC_prog = new wxProgressDialog(  Title, Message, nGeoRecords, NULL,
                                       wxPD_AUTO_HIDE | wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME |
                                       wxPD_REMAINING_TIME  | wxPD_SMOOTH );

    //      The created size in wxWidgets 2.8 is waaay too large, so....
    wxSize sz = SENC_prog->GetSize();
    sz.x /= 2;
    SENC_prog->SetSize(sz);
    SENC_prog->Centre();


    //      Analyze Updates
    //      The OGR library will apply updates automatically, as specified by the UPDATES=APPLY flag
    //      We need to keep track of the last sequential update applied, to look out for new updates

    int last_applied_update = 0;
    wxString LastUpdateDate = date000;
    if(benable_update)
        last_applied_update = CountUpdates( s57file.GetPath((int)wxPATH_GET_SEPARATOR), LastUpdateDate);

    fprintf(fps57, "UPDT=%d\n", last_applied_update);
    fprintf(fps57, "DATEUPD=%s\n", LastUpdateDate.c_str());


    //  Here comes the actual ISO8211 file reading
    OGRSFDriver *poDriver;
    OGRDataSource *poDS = OGRSFDriverRegistrar::Open( pFullPath, FALSE, &poDriver );
    if( poDS == NULL )
    {
        wxLogMessage("s57chart::BuildS57File  Unable to open %s )", pFullPath);
        delete SENC_prog;
        fclose(fps57);

        return 0;
    }

    //  Now that the .000 file with updates is safely ingested, delete any temporary
    //  dummy update files

    if(tmpup_array)
    {
        for(unsigned int iff = 0 ; iff < tmpup_array->GetCount() ; iff++)
           remove(tmpup_array->Item(iff).c_str());
        delete tmpup_array;
    }


    //      Insert my local error handler to catch OGR errors,
    //      Especially CE_Fatal type errors
    //      Discovered/debugged on US5MD11M.017.  VI 548 geometry deleted
    CPLPushErrorHandler( OpenCPN_OGRErrorHandler );


    //  Read all features, layer by layer
    //  Using the api defined by <ogrsf_frmts.h>
    bool bcont = true;
    int iObj = 0;
    OGRwkbGeometryType geoType;
    wxString sobj;
    int iLayObj;

    int nLayers = poDS->GetLayerCount();


    for(int iL=0 ; iL < nLayers ; iL++)
    {
        OGRLayer *pLay = poDS->GetLayer(iL);

        pLay->ResetReading();

        iLayObj = 0;

        while (bcont)
        {
            //  Prepare for possible CE_Fatal error in GDAL
            //  Corresponding longjmp() is in the local error handler
            int setjmp_ret = 0;
            setjmp_ret = setjmp(env_ogrf);
            if(setjmp_ret == 1)                 //  CE_Fatal happened in GDAL library
                                                //  in the GetNextFeature() call below.
                                                //  Seems odd, but that's setjmp/longjmp behaviour
            {
                wxString sLay("Unknown");
                if(iLayObj)
                    sLay = sobj;

                wxLogMessage("s57chart(): GDAL/OGR Fatal Error caught on Obj #%d.\n \
                        Skipping all remaining objects on Layer %s.", iObj, sLay.c_str());
                delete objectDef;
                break;                                  // pops out of while(bcont) to next layer
            }

            objectDef = pLay->GetNextFeature();
            iObj++;
            iLayObj++;

            if(objectDef == NULL)
                break;

//  Debug Hook, can safely go away
//            if(objectDef->GetFID() == 3867)
//                int hhd = 4;

            sobj = wxString(objectDef->GetDefnRef()->GetName());
            wxString idx;
            idx.Printf("  %d/%d       ", iObj, nGeoRecords);
            sobj += idx;

//  Update the progress dialog

            nProg = iObj;
            if(nProg > nGeoRecords - 1)
                nProg = nGeoRecords - 1;

            if(0 == (nProg % 100))
                bcont = SENC_prog->Update(nProg, sobj);


            geoType = wkbUnknown;
//      This test should not be necessary for real (i.e not C_AGGR) features
//      However... some update files contain errors, and have deleted some
//      geometry without deleting the corresponding feature(s).
//      So, GeometryType becomes Unknown.
//      e.g. US5MD11M.017
//      In this case, all we can do is skip the feature....sigh.

            if (objectDef->GetGeometryRef() != NULL)
                geoType = objectDef->GetGeometryRef()->getGeometryType();

// Debug
//            if(!strncmp(objectDef->GetDefnRef()->GetName(), "LIGHTS", 6))
//                int ggk = 5;

//      Look for polygons to process
            if(geoType == wkbPolygon)
            {
                int error_code;
                PolyTessGeo *ppg;

                OGRPolygon *poly = (OGRPolygon *)(objectDef->GetGeometryRef());


//              if(1)
                {
                        bcont = SENC_prog->Update(nProg, sobj);
                        CreateSENCRecord( objectDef, fps57, 0 );
                        ppg = new PolyTessGeo(poly, true, ref_lat, ref_lon, 0);   //try to use glu library
                        error_code = ppg->ErrorCode;
                        if(error_code == ERROR_NO_DLL)
                        {
                            if(!bGLUWarningSent)
                            {
                                wxLogMessage("Warning...Could not find glu32.dll, trying internal tess.");
                                bGLUWarningSent = true;
                            }

                            delete ppg;
                                //  Try with internal tesselator
                            ppg = new PolyTessGeo(poly, true, ref_lat, ref_lon, 1);
                            error_code = ppg->ErrorCode;
                         }


                        if(error_code)
                        {
                            wxLogMessage("Error: S57 SENC Create Error %d", ppg->ErrorCode);

                            delete ppg;
                            delete objectDef;
                            delete SENC_prog;
                            fclose(fps57);
                            delete poDS;
                            CPLPopErrorHandler();
                            unlink(tmp_file.c_str());           // delete the temp file....

                            return 0;                           // soft error return
                        }

                        ppg->Write_PolyTriGroup( fps57 );
                        delete ppg;
                  }
            }

//      n.b  This next line causes skip of C_AGGR features w/o geometry
            else if( geoType != wkbUnknown )                                // Write only if has wkbGeometry
                CreateSENCRecord( objectDef, fps57, 1 );

            delete objectDef;


        }           // while bcont

    }               // for

    delete SENC_prog;

    fclose(fps57);

    delete poDS;

    CPLPopErrorHandler();

//    Need root to create the SENC file
#ifndef __WXMSW__
      seteuid(file_user_id);
#endif

    int ret_code = 0;
//      Was the operation cancelled?
    if(!bcont)
    {
        unlink(tmp_file.c_str());               //      Delete the temp file....
        ret_code = 0;
    }
    else
    {
        remove(s57file.GetFullPath());
        unlink(s57file.GetFullPath());       //  Delete any existing SENC file....
        int err = rename(tmp_file.c_str(), s57file.GetFullPath()); //   mv temp file to target
        if(err)
        {
            wxLogMessage("Could not rename temporary SENC file %s to %s",tmp_file.c_str(),
                                     s57file.GetFullPath().c_str());
//            wxString msg1("Could not create SENC file, perhaps permissions not set to read/write?");
//            wxMessageDialog mdlg(this, msg1, wxString("OpenCPN"),wxICON_ERROR  );
//            if(mdlg.ShowModal() == wxID_YES)

            ret_code = 0;
        }
        else
            ret_code = 1;
     }

 //   Return to default user priveleges
#ifndef __WXMSW__
      seteuid(user_user_id);
#endif


      return ret_code;
}

int s57chart::BuildRAZFromS57File( const char *pFullPath )
{

        int nProg = 0;

        wxString ifs(pFullPath);

        wxFileInputStream fpx_u(ifs);
        wxBufferedInputStream fpx(fpx_u);

        int MAX_LINE = 499999;
        char *buf = (char *)malloc(MAX_LINE + 1);

        LUPrec           *LUP;
        LUPname          LUP_Name;

        int     nGeoFeature;

        int object_count = 0;

        OGREnvelope     Envelope;

        int dun = 0;

        hdr_buf = (char *)malloc(1);
        wxProgressDialog    *SENC_prog = NULL;
        int nGeo1000;
        wxString date_000, date_upd;

        if(my_fgets(buf, MAX_LINE, fpx) == 0)
           dun = 1;


        // Create ATON arrays, needed by S52PLIB
        pFloatingATONArray = new wxArrayPtrVoid;
        pRigidATONArray = new wxArrayPtrVoid;



        while(!dun)
        {

                if(my_fgets(buf, MAX_LINE, fpx) == 0)
                {
                        dun = 1;
                        break;
                }

                if(!strncmp(buf, "OGRF", 4))
                {

                    S57Obj *obj = new S57Obj(buf, &fpx);
                    if(obj)
                    {

//      Build/Maintain the ATON floating/rigid arrays
                         if (GEO_POINT == obj->Primitive_type)
                         {

// set floating platform
                            if ((!strncmp(obj->FeatureName, "LITFLT", 6)) ||
                                (!strncmp(obj->FeatureName, "LITVES", 6)) ||
                                (!strncmp(obj->FeatureName, "BOY",    3)))

                                pFloatingATONArray->Add(obj);

// set rigid platform
                            if (!strncmp(obj->FeatureName, "BCN",    3))
                                pRigidATONArray->Add(obj);
                         }



//      This is where Simplified or Paper-Type point features are selected
                         switch(obj->Primitive_type)
                         {
                            case GEO_POINT:
                            case GEO_META:
                            case GEO_PRIM:

                                if(PAPER_CHART == ps52plib->m_nSymbolStyle)
                                    LUP_Name = PAPER_CHART;
                                else
                                    LUP_Name = SIMPLIFIED;

                                break;

                             case GEO_LINE:
                                 LUP_Name = LINES;
                                 break;

                             case GEO_AREA:
                                 if(PLAIN_BOUNDARIES == ps52plib->m_nBoundaryStyle)
                                     LUP_Name = PLAIN_BOUNDARIES;
                                 else
                                     LUP_Name = SYMBOLIZED_BOUNDARIES;

                                 break;
                         }

 // Debug hook
 //       if(!strncmp(obj->FeatureName, "DEPCNT", 6))
 //           int ffl = 4;
                         LUP = ps52plib->S52_LUPLookup(LUP_Name, obj->FeatureName, obj);

                         if(NULL == LUP)
                             wxLogMessage("Could not find LUP for %s", obj->FeatureName);
                         else
                         {
//              Convert LUP to rules set
                            ps52plib->_LUP2rules(LUP, obj);

//              Add linked object/LUP to the working set
                            _insertRules(obj,LUP);
                         }
                    }


                    object_count++;

                    if((object_count % 500) == 0)
                    {
                        nProg = object_count / 500;
                        if(nProg > nGeo1000 - 1)
                                nProg = nGeo1000 - 1;

                        if(SENC_prog)
                            SENC_prog->Update(nProg);
                    }


                    continue;


                }               //OGRF

            else if(!strncmp(buf, "DATEUPD", 7))
            {
                  date_upd.Append(wxString(&buf[8]).BeforeFirst('\n'));
            }

            else if(!strncmp(buf, "DATE000", 7))
            {
                  date_000.Append(wxString(&buf[8]).BeforeFirst('\n'));
            }

            else if(!strncmp(buf, "SCALE", 5))
                {
                        int ins;
                        sscanf(buf, "SCALE=%d", &ins);
                        NativeScale = ins;
                }

            else if(!strncmp(buf, "NAME", 4))
            {
                  pName->Append(wxString(&buf[5]).BeforeFirst('\n'));
            }

            else if(!strncmp(buf, "NOGR", 4))
            {
                 sscanf(buf, "NOGR=%d", &nGeoFeature);

                 nGeo1000 = nGeoFeature / 500;

#ifndef __WXGTK__
                 SENC_prog = new wxProgressDialog(  _T("OpenCPN S57 SENC File Load"), pFullPath, nGeo1000, NULL,
                          wxPD_AUTO_HIDE | wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME | wxPD_SMOOTH);

    //      The created size in wxWidgets 2.8 is waaay too large, so....
                wxSize sz = SENC_prog->GetSize();
                sz.x /= 2;
                SENC_prog->SetSize(sz);
                SENC_prog->Centre();
#endif
            }
        }                       //while(!dun)


//      fclose(fpx);

        free(buf);

        free(hdr_buf);

        delete SENC_prog;

 //   Decide on pub date to show

      int d000 = atoi(wxString(date_000).Mid(0,4));
      int dupd = atoi(wxString(date_upd).Mid(0,4));

      if(dupd > d000)
        pPubYear->Append(wxString(date_upd).Mid(0,4));
      else
        pPubYear->Append(wxString(date_000).Mid(0,4));

      return 1;
}

//------------------------------------------------------------------------------
//      Local version of fgets for Binary Mode (SENC) file
//------------------------------------------------------------------------------
 int s57chart::my_fgets( char *buf, int buf_len_max, wxBufferedInputStream& ifs )

{
    char        chNext;
    int         nLineLen = 0;
    char            *lbuf;

    lbuf = buf;


    while( !ifs.Eof() && nLineLen < buf_len_max )
    {
        chNext = (char)ifs.GetC();

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



int s57chart::_insertRules(S57Obj *obj, LUPrec *LUP)
{
   ObjRazRules   *rzRules = NULL;
   int                          disPrioIdx = 0;
   int                          LUPtypeIdx = 0;

   if(LUP == NULL){
      printf("SEQuencer:_insertRules(): ERROR no rules to insert!!\n");
      return 0;
   }


   // find display priority index       --talky version
   switch(LUP->DPRI){
      case PRIO_NODATA:         disPrioIdx = 0; break;  // no data fill area pattern
      case PRIO_GROUP1:         disPrioIdx = 1; break;  // S57 group 1 filled areas
      case PRIO_AREA_1:         disPrioIdx = 2; break;  // superimposed areas
      case PRIO_AREA_2:         disPrioIdx = 3; break;  // superimposed areas also water features
      case PRIO_SYMB_POINT:     disPrioIdx = 4; break;  // point symbol also land features
      case PRIO_SYMB_LINE:      disPrioIdx = 5; break;  // line symbol also restricted areas
      case PRIO_SYMB_AREA:      disPrioIdx = 6; break;  // area symbol also traffic areas
      case PRIO_ROUTEING:       disPrioIdx = 7; break;  // routeing lines
      case PRIO_HAZARDS:        disPrioIdx = 8; break;  // hazards
      case PRIO_MARINERS:       disPrioIdx = 9; break;  // VRM & EBL, own ship
      default:
         printf("SEQuencer:_insertRules():ERROR no display priority!!!\n");
   }

   // find look up type index
   switch(LUP->TNAM){
      case SIMPLIFIED:                          LUPtypeIdx = 0; break; // points
      case PAPER_CHART:                         LUPtypeIdx = 1; break; // points
      case LINES:                                       LUPtypeIdx = 2; break; // lines
      case PLAIN_BOUNDARIES:            LUPtypeIdx = 3; break; // areas
      case SYMBOLIZED_BOUNDARIES:       LUPtypeIdx = 4; break; // areas
      default:
         printf("SEQuencer:_insertRules():ERROR no look up type !!!\n");
   }

   // insert rules
   rzRules = (ObjRazRules *)malloc(sizeof(ObjRazRules));
   rzRules->obj   = obj;
   obj->nRef++;                         // Increment reference counter for delete check;
   rzRules->LUP   = LUP;
   rzRules->chart = this;
   rzRules->next  = razRules[disPrioIdx][LUPtypeIdx];
   razRules[disPrioIdx][LUPtypeIdx] = rzRules;

   return 1;
}


//      Traverse the ObjRazRules tree, and fill in
//      any Lups/rules not linked on initial chart load.
//      For example, if chart was loaded with PAPER_CHART symbols,
//      locate and load the equivalent SIMPLIFIED symbology.
//      Likewise for PLAIN/SYMBOLIZED boundaries.
//
//      This method is usually called after a chart display style
//      change via the "Options" dialog, to ensure all symbology is
//      present iff needed.

void s57chart::UpdateLUPs()
{
    ObjRazRules *top;
    ObjRazRules *nxx;
    LUPrec      *LUP;

    for (int i=0; i<PRIO_NUM; ++i)
    {
        //  SIMPLIFIED is set, PAPER_CHART is bare
        if((razRules[i][0]) && (NULL == razRules[i][1]))
        {
            top = razRules[i][0];

            while ( top != NULL)
            {
                LUP = ps52plib->S52_LUPLookup(PAPER_CHART, top->obj->FeatureName, top->obj);
                ps52plib->_LUP2rules(LUP, top->obj);
                _insertRules(top->obj, LUP);

                nxx  = top->next;
                top = nxx;
            }
        }

                //  PAPER_CHART is set, SIMPLIFIED is bare
        if((razRules[i][1]) && (NULL == razRules[i][0]))
        {
            top = razRules[i][1];

            while ( top != NULL)
            {
                LUP = ps52plib->S52_LUPLookup(SIMPLIFIED, top->obj->FeatureName, top->obj);
                ps52plib->_LUP2rules(LUP, top->obj);
                _insertRules(top->obj, LUP);

                nxx  = top->next;
                top = nxx;
            }
        }

                //  PLAIN_BOUNDARIES is set, SYMBOLIZED_BOUNDARIES is bare
        if((razRules[i][3]) && (NULL == razRules[i][4]))
        {
            top = razRules[i][3];

            while ( top != NULL)
            {
                LUP = ps52plib->S52_LUPLookup(SYMBOLIZED_BOUNDARIES, top->obj->FeatureName, top->obj);
                ps52plib->_LUP2rules(LUP, top->obj);
                _insertRules(top->obj, LUP);

                nxx  = top->next;
                top = nxx;
            }
        }

                //  SYMBOLIZED_BOUNDARIES is set, PLAIN_BOUNDARIES is bare
        if((razRules[i][4]) && (NULL == razRules[i][3]))
        {
            top = razRules[i][4];

            while ( top != NULL)
            {
                LUP = ps52plib->S52_LUPLookup(PLAIN_BOUNDARIES, top->obj->FeatureName, top->obj);
                ps52plib->_LUP2rules(LUP, top->obj);
                _insertRules(top->obj, LUP);

                nxx  = top->next;
                top = nxx;
            }
        }

        //  Traverse this priority level again,
        //  clearing any object CS rules and flags,
        //  so that the next render operation will re-evaluate the CS

        for(int j=0 ; j<LUPNAME_NUM ; j++)
        {
            top = razRules[i][j];
            while ( top != NULL)
            {
                top->obj->bCS_Added = 0;

                nxx  = top->next;
                top = nxx;
            }
        }
    }
}






void s57chart::CreateSENCRecord( OGRFeature *pFeature, FILE * fpOut, int mode )
{

#define MAX_HDR_LINE    400

        char line[MAX_HDR_LINE + 1];
        wxString sheader;

        fprintf( fpOut, "OGRFeature(%s):%ld\n", pFeature->GetDefnRef()->GetName(),
                  pFeature->GetFID() );

        // DEBUG
//        if(pFeature->GetFID() == 3868)
//          int hhl = 5;

//      In the interests of output file size, DO NOT report fields that are not set.
        for( int iField = 0; iField < pFeature->GetFieldCount(); iField++ )
        {
                if( pFeature->IsFieldSet( iField ) )
                {
                        if((iField == 1) || (iField > 7))
                        {
                                OGRFieldDefn *poFDefn = pFeature->GetDefnRef()->GetFieldDefn(iField);

                                const char *pType = OGRFieldDefn::GetFieldTypeName(poFDefn->GetType()) ;

#ifdef __MSVC__
                                _snprintf( line, MAX_HDR_LINE - 2, "  %s (%c) = %s",
                                         poFDefn->GetNameRef(),
                                         *pType,
                                         pFeature->GetFieldAsString( iField ));
#else
                                snprintf( line, MAX_HDR_LINE - 2, "  %s (%c) = %s",
                                         poFDefn->GetNameRef(),
                                         *pType,
                                         pFeature->GetFieldAsString( iField ));
#endif


                        sheader += line;
                        sheader += '\n';
                        }
                }
        }

        OGRGeometry *pGeo = pFeature->GetGeometryRef();

        if(mode == 1)
        {
            sprintf( line, "  %s\n", pGeo->getGeometryName());
            sheader += line;
        }

        fprintf( fpOut, "HDRLEN=%d\n", sheader.Len());
        fwrite(sheader.c_str(), 1, sheader.Len(), fpOut);

        if(( pGeo != NULL ) && (mode == 1))
        {
            int wkb_len = pGeo->WkbSize();
            unsigned char *pwkb_buffer = (unsigned char *)malloc(wkb_len);

//  Get the GDAL data representation
            pGeo->exportToWkb(wkbNDR, pwkb_buffer);

    //  Convert to opencpn SENC representation

    //  Set absurd bbox starting limits
            float lonmax = -1000;
            float lonmin = 1000;
            float latmax = -1000;
            float latmin = 1000;

            int i, ip, sb_len;
            float *pdf;
            double *psd;
            unsigned char *ps;
            unsigned char *pd;
            unsigned char *psb_buffer;
            double lat, lon;
            int nPoints;

            OGRwkbGeometryType gType = pGeo->getGeometryType();
            switch(gType)
            {
                case wkbLineString:
                    sb_len = ((wkb_len - 9) / 2) + 9 + 16;                // data will be 4 byte float, not double
                                                                          // and bbox limits are tacked on end
                    fprintf( fpOut, "  %d\n", sb_len);


                    psb_buffer = (unsigned char *)malloc(sb_len);
                    pd = psb_buffer;
                    ps = pwkb_buffer;

                    memcpy(pd, ps, 9);                                    // byte order, type, and count

                    ip = *((int *)(ps + 5));                              // point count

                    pd += 9;
                    ps += 9;
                    psd = (double *)ps;
                    pdf = (float *)pd;

                    for(i = 0 ; i < ip ; i++)                           // convert doubles to floats
                    {                                                   // computing bbox as we go

                        float lon = (float)*psd++;
                        float lat = (float)*psd++;

                        //  Calculate SM from chart common reference point
                        double easting, northing;
                        toSM(lat, lon, ref_lat, ref_lon, &easting, &northing);

                        *pdf++ = easting;
                        *pdf++ = northing;

                        lonmax = fmax(lon, lonmax);
                        lonmin = fmin(lon, lonmin);
                        latmax = fmax(lat, latmax);
                        latmin = fmin(lat, latmin);

                    }

                    //      Store the Bounding Box as lat/lon
                    *pdf++ = lonmax;
                    *pdf++ = lonmin;
                    *pdf++ = latmax;
                    *pdf =   latmin;

                    fwrite(psb_buffer, 1, sb_len, fpOut);
                    free(psb_buffer);
                    break;

                case wkbMultiLineString:
                      wxLogMessage("Warning: Unimplemented SENC wkbMultiLineString record in file %s",
                                   pS57FileName->GetFullPath().c_str());

                      wkb_len = pGeo->WkbSize();
                      fprintf( fpOut, "  %d\n", wkb_len);
                      fwrite(pwkb_buffer, 1, wkb_len, fpOut);

                      break;

                case wkbPoint:
                    sb_len = ((wkb_len - 5) / 2) + 5;                   // data will be 4 byte float, not double

                    fprintf( fpOut, "  %d\n", sb_len);

                    psb_buffer = (unsigned char *)malloc(sb_len);
                    pd = psb_buffer;
                    ps = pwkb_buffer;

                    memcpy(pd, ps, 5);                                  // byte order, type

                    pd += 5;
                    ps += 5;
                    psd = (double *)ps;
                    pdf = (float *)pd;

                    lon = *psd++;                                      // fetch the point
                    lat = *psd;

                    //  Calculate SM from chart common reference point
                    double easting, northing;
                    toSM(lat, lon, ref_lat, ref_lon, &easting, &northing);

                    *pdf++ = easting;
                    *pdf   = northing;

                    //  And write it out
                    fwrite(psb_buffer, 1, sb_len, fpOut);
                    free(psb_buffer);

                    break;

                case wkbMultiPoint25D:
                    ps = pwkb_buffer;
                    ps += 5;
                    nPoints = *((int *)ps);                     // point count

                    sb_len = (9 + nPoints * 3 * sizeof(float)) + 16;     // GTYPE and count, points as floats
                                                                         // and trailing bbox
                    fprintf( fpOut, "  %d\n", sb_len);

                    psb_buffer = (unsigned char *)malloc(sb_len);
                    pd = psb_buffer;
                    ps = pwkb_buffer;

                    memcpy(pd, ps, 9);                                  // byte order, type, count

                    ps += 9;
                    pd += 9;

                    pdf = (float *)pd;

                    for(ip=0 ; ip < nPoints ; ip++)
                    {

                        // Workaround a bug?? in OGRGeometryCollection
                        // While exporting point geometries serially, OGRPoint->exportToWkb assumes that
                        // if Z is identically 0, then the point must be a 2D point only.
                        // So, the collection Wkb is corrupted with some 3D, and some 2D points.
                        // Workaround:  Get reference to the points serially, and explicitly read X,Y,Z
                        // Ignore the previously read Wkb buffer

                        OGRGeometryCollection *temp_geometry_collection = (OGRGeometryCollection *)pGeo;
                        OGRGeometry *temp_geometry = temp_geometry_collection->getGeometryRef( ip );
                        OGRPoint *pt_geom = (OGRPoint *)temp_geometry;

                        lon = pt_geom->getX();
                        lat = pt_geom->getY();
                        double depth = pt_geom->getZ();

                        /*
                        ps += 5;
                        psd = (double *)ps;

                        lon = *psd++;
                        lat = *psd++;
                        double depth = *psd;
                        */

                        //  Calculate SM from chart common reference point
                        double easting, northing;
                        toSM(lat, lon, ref_lat, ref_lon, &easting, &northing);

                        *pdf++ = easting;
                        *pdf++ = northing;
                        *pdf++ = (float)depth;

//                        ps += 3 * sizeof(double);

                        //  Keep a running calculation of min/max
                        lonmax = fmax(lon, lonmax);
                        lonmin = fmin(lon, lonmin);
                        latmax = fmax(lat, latmax);
                        latmin = fmin(lat, latmin);
                    }

                    //      Store the Bounding Box as lat/lon
                    *pdf++ = lonmax;
                    *pdf++ = lonmin;
                    *pdf++ = latmax;
                    *pdf =   latmin;

                    //  And write it out
                    fwrite(psb_buffer, 1, sb_len, fpOut);
                    free(psb_buffer);


                    break;

                    //      Special case, polygons are handled separately
                case wkbPolygon:
                    break;

                    //      All others
                default:
                    wxLogMessage("Warning: Unimplemented ogr geotype in SENC record create:file %s, geotype %d",
                                 pS57FileName->GetFullPath().c_str(), gType);
                    wkb_len = pGeo->WkbSize();
                      fprintf( fpOut, "  %d\n", wkb_len);
                      fwrite(pwkb_buffer, 1, wkb_len, fpOut);
                      break;
            }       // switch



            free(pwkb_buffer);
            fprintf( fpOut, "\n" );
        }
}


/*
      LUPname     m_nSymbolStyle;
      LUPname     m_nBoundaryStyle;
      bool        m_bOK;

      bool        m_bShowSoundg;
      bool        m_bShowMeta;
      bool        m_bShowS57Text;
      bool        m_bUseSCAMIN;
*/

ArrayOfS57Obj *s57chart::GetObjArrayAtLatLon(float lat, float lon, float select_radius, ViewPort *VPoint)
{

    ArrayOfS57Obj *ret_ptr = new ArrayOfS57Obj;


//    Iterate thru the razRules array, by object/rule type

    ObjRazRules *crnt;
    ObjRazRules *top;

    for (int i=0; i<PRIO_NUM; ++i)
    {
      // Points by type, array indices [0..1]

        int point_type = (ps52plib->m_nSymbolStyle == SIMPLIFIED) ? 0 : 1;
        top = razRules[i][point_type];

        while ( top != NULL)
        {
            crnt = top;
            top  = top->next;

            if(ps52plib->ObjectRenderCheck(crnt, VPoint))
            {
                if(DoesLatLonSelectObject(lat, lon, select_radius, crnt->obj))
                    ret_ptr->Add(crnt->obj);
            }

        }


      // Areas by boundary type, array indices [3..4]

        int area_boundary_type = (ps52plib->m_nBoundaryStyle == PLAIN_BOUNDARIES) ? 3 : 4;
        top = razRules[i][area_boundary_type];           // Area nnn Boundaries
        while ( top != NULL)
        {
            crnt = top;
            top  = top->next;
            if(ps52plib->ObjectRenderCheck(crnt, VPoint))
            {
                if(DoesLatLonSelectObject(lat, lon, select_radius, crnt->obj))
                    ret_ptr->Add(crnt->obj);
            }
        }         // while


      // Finally, lines
          top = razRules[i][2];           // Lines

          while ( top != NULL)
          {
            crnt = top;
            top  = top->next;
            if(ps52plib->ObjectRenderCheck(crnt, VPoint))
            {
                if(DoesLatLonSelectObject(lat, lon, select_radius, crnt->obj))
                ret_ptr->Add(crnt->obj);
            }
          }
      }

      return ret_ptr;
}

bool s57chart::DoesLatLonSelectObject(float lat, float lon, float select_radius, S57Obj *obj)
{
      switch(obj->Primitive_type)
      {
            case  GEO_POINT:
                //  For single Point objects, the integral object bounding box contains the lat/lon of the object,
                //  possibly expanded by text or symbol rendering
                {
                    if(1 == obj->npt)
                    {
                        if(obj->BBObj.PointInBox( lon, lat, select_radius))
                            return true;
                    }
                    //  For MultiPoint objects, make a bounding box from each point's lat/lon
                    //  and check it
                    else
                    {
                        //  Coarse test first
                        if(!obj->BBObj.PointInBox( lon, lat, select_radius))
                            return false;
                        //  Now decomposed soundings, one by one
                        double *pdl = obj->geoPtMulti;
                        for(int ip = 0 ; ip < obj->npt ;  ip++)
                        {
                            double lon_point = *pdl++;
                            double lat_point = *pdl++;
                            wxBoundingBox BB_point(lon_point, lat_point, lon_point, lat_point);
                            if(BB_point.PointInBox( lon, lat, select_radius))
                                return true;
                        }
                    }

                    break;
                }
            case  GEO_AREA:
                {
                    return IsPointInObjArea(lat, lon, select_radius, obj);
                }

            case  GEO_LINE:
            case  GEO_META:
            case  GEO_PRIM:

            break;
      }

      return false;
}

wxString *s57chart::CreateObjDescription(const S57Obj& obj)
{
      wxString *ret_str = new wxString;

      char *curr_att;
      int iatt;
      wxString att, value;
      S57attVal *pval;

      switch(obj.Primitive_type)
      {
            case  GEO_POINT:
            case  GEO_AREA:
                  {

                  //    Get Name
                  wxString name(obj.FeatureName);
                  *ret_str << name;
                  *ret_str << " - ";

                  //    Get the object's nice description from s57objectclasses.csv
                  //    using cpl_csv from the gdal library

                  const char *name_desc;
                  if(NULL != m_pcsv_locn)
                  {
                    wxString oc_file(*m_pcsv_locn);
                    oc_file.Append("/s57objectclasses.csv");
                    name_desc = MyCSVGetField(oc_file.c_str(),
                                     "Acronym",                  // match field
                                     obj.FeatureName,            // match value
                                     CC_ExactString,
                                     "ObjectClass");             // return field
                  }
                  else
                      name_desc = "";


                  *ret_str << name_desc;
                  *ret_str << '\n';


                  wxString index;
                  index.Printf("    Feature Index: %d\n", obj.Index);
                  *ret_str << index;


                  //    Get the Attributes and values

                  curr_att = (char *)(obj.attList->c_str());
                  iatt = 0;

                  while(*curr_att)
                  {
//    Attribute name
                        att.Clear();
                        while((*curr_att) && (*curr_att != '\037'))
                              att.Append(*curr_att++);

                        if(*curr_att == '\037')
                              curr_att++;

                        int is = 0;
                        while( is < 8)
                        {
                              *ret_str << ' ';
                              is++;
                        }

                        *ret_str << att;

                        is+= att.Len();
                        while( is < 25)
                        {
                              *ret_str << ' ';
                              is++;
                        }


// What we need to do...
// Change senc format, instead of (S), (I), etc, use the attribute types fetched from the S57attri...csv file
// This will be like (E), (L), (I), (F)
//  will affect lots of other stuff.  look for S57attVal.valType
// need to do this in creatsencrecord above, and update the senc format.

//    Attribute encoded value
                    value.Clear();

                    pval = obj.attVal->Item(iatt);
                    switch(pval->valType)
                    {
                        case OGR_STR:
                        {
                            if(pval->value)
                            {
                                wxString val_str((char *)(pval->value));
                                if(val_str.IsNumber())
                                {
                                    int ival = atoi(val_str.c_str());
                                    if(0 == ival)
                                        value.Printf("Unknown");
                                    else
                                    {
                                        wxString *decode_val = GetAttributeDecode(att, ival);
                                        if(decode_val)
                                            value.Printf("%s(%d)", decode_val->c_str(), ival);
                                        else
                                            value.Printf("(%d)", ival);
                                        delete decode_val;
                                    }
                                }

                                else if(val_str.IsEmpty())
                                    value.Printf("Unknown");

                                else
                                {
                                    value.Clear();
                                    wxString value_increment;
                                    wxStringTokenizer tk(val_str, wxT(","));
                                    int iv = 0;
                                    while ( tk.HasMoreTokens() )
                                    {
                                        wxString token = tk.GetNextToken();
                                        if(token.IsNumber())
                                        {
                                            int ival = atoi(token.c_str());
                                            wxString *decode_val = GetAttributeDecode(att, ival);
                                            if(decode_val)
                                                value_increment.Printf("%s", decode_val->c_str());
                                            else
                                                value_increment.Printf("(%d)", ival);

                                            delete decode_val;
                                            if(iv)
                                                value_increment.Prepend(wxT(", "));
                                        }
                                        value.Append(value_increment.c_str());

                                        iv++;
                                    }

                                    value.Append("(");
                                    value.Append(val_str.c_str());
                                    value.Append(")");
                                }
                            }
                            else
                            {
                                value.Printf("[NULL VALUE]");
                            }

                            break;
                        }

                        case OGR_INT:
                        {
                            int ival = *((int *)pval->value);
                            wxString *decode_val = GetAttributeDecode(att, ival);

                            if(decode_val)
                                value.Printf("%s(%d)", decode_val->c_str(), ival);
                            else
                                value.Printf("(%d)", ival);

                            delete decode_val;
                            break;
                        }
                        case OGR_INT_LST:
                        case OGR_REAL:
                        case OGR_REAL_LST:
                        {
                                break;
                        }
                    }


                        *ret_str << value;

                        *ret_str << '\n';
                        iatt++;
                  }

                  return ret_str;

                  }

//      wxString                *attList;
//      wxArrayOfS57attVal      *attVal;

#if 0
typedef enum _OGRatt_t{
   OGR_INT,
   OGR_INT_LST,
   OGR_REAL,
   OGR_REAL_LST,
   OGR_STR,
}OGRatt_t;

typedef struct _S57attVal{
   void *   value;
   OGRatt_t valType;
}S57attVal;
#endif


            case  GEO_LINE:
            case  GEO_META:
            case  GEO_PRIM:

            break;
      }

      return ret_str;
}

wxString *s57chart::GetAttributeDecode(wxString& att, int ival)
{

    wxString *ret_val = NULL;

    if(NULL == m_pcsv_locn)
        return NULL;

    //  Get the attribute code from the acronym
    const char *att_code;

    wxString file(*m_pcsv_locn);
    file.Append("/s57attributes.csv");
    att_code = MyCSVGetField(file.c_str(),
                                  "Acronym",                  // match field
                                  att.c_str(),               // match value
                                  CC_ExactString,
                                  "Code");             // return field


    // Now, get a nice description from s57expectedinput.csv
    //  This will have to be a 2-d search, using ID field and Code field

    bool more = true;
    wxString ei_file(*m_pcsv_locn);
    ei_file.Append("/s57expectedinput.csv");

    FILE        *fp;
    fp = VSIFOpen( ei_file.c_str(), "rb" );
    if( fp == NULL )
        return NULL;

    while(more)
    {
        char **result = CSVScanLines( fp,
                                     0,                         // first field = attribute Code
                                     att_code,
                                     CC_ExactString );

        if(NULL == result)
        {
            more = false;
            break;
        }
        if(atoi(result[1]) == ival)
        {
            ret_val = new wxString(result[2]);
        }
    }


    VSIFClose(fp);
    return ret_val;
}



//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------


bool s57chart::IsPointInObjArea(float lat, float lon, float select_radius, S57Obj *obj)
{
    bool ret = false;

    if(obj->pPolyTessGeo)
    {

//      Is the point in the PolyGeo Bounding Box?

        if(lon > obj->pPolyTessGeo->Get_xmax())
            return false;
        else if(lon < obj->pPolyTessGeo->Get_xmin())
            return false;
        else if(lat > obj->pPolyTessGeo->Get_ymax())
            return false;
        else if(lat < obj->pPolyTessGeo->Get_ymin())
            return false;


        PolyTriGroup *ppg = obj->pPolyTessGeo->Get_PolyTriGroup_head();

        TriPrim *pTP = ppg->tri_prim_head;

        MyPoint pvert_list[3];

        //  Polygon geometry is carried in SM coordinates, so...
        //  make the hit test thus.
        double easting, northing;
        toSM(lat, lon, ref_lat, ref_lon, &easting, &northing);

        while(pTP)
        {
//  Coarse test
            if(pTP->p_bbox->PointInBox(lon, lat, 0))
            {
                double *p_vertex = pTP->p_vertex;

                switch (pTP->type)
                {
                    case PTG_TRIANGLE_FAN:
                    {
                        for(int it = 0 ; it < pTP->nVert - 2 ; it++)
                        {
                            pvert_list[0].x = p_vertex[0];
                            pvert_list[0].y = p_vertex[1];

                            pvert_list[1].x = p_vertex[(it*2)+2];
                            pvert_list[1].y = p_vertex[(it*2)+3];

                            pvert_list[2].x = p_vertex[(it*2)+4];
                            pvert_list[2].y = p_vertex[(it*2)+5];

                            if(G_PtInPolygon((MyPoint *)pvert_list, 3, easting, northing))
                            {
                                ret = true;
                                break;
                            }
                        }
                        break;
                    }
                    case PTG_TRIANGLE_STRIP:
                    {
                        for(int it = 0 ; it < pTP->nVert - 2 ; it++)
                        {
                            pvert_list[0].x = p_vertex[(it*2)];
                            pvert_list[0].y = p_vertex[(it*2)+1];

                            pvert_list[1].x = p_vertex[(it*2)+2];
                            pvert_list[1].y = p_vertex[(it*2)+3];

                            pvert_list[2].x = p_vertex[(it*2)+4];
                            pvert_list[2].y = p_vertex[(it*2)+5];

                            if(G_PtInPolygon((MyPoint *)pvert_list, 3, easting, northing))
                            {
                                ret = true;
                                break;
                            }
                        }
                        break;
                    }
                    case PTG_TRIANGLES:
                    {
                        for(int it = 0 ; it < pTP->nVert ; it+=3)
                        {
                            pvert_list[0].x = p_vertex[(it*2)];
                            pvert_list[0].y = p_vertex[(it*2)+1];

                            pvert_list[1].x = p_vertex[(it*2)+2];
                            pvert_list[1].y = p_vertex[(it*2)+3];

                            pvert_list[2].x = p_vertex[(it*2)+4];
                            pvert_list[2].y = p_vertex[(it*2)+5];

                            if(G_PtInPolygon((MyPoint *)pvert_list, 3, easting, northing))
                            {
                                ret = true;
                                break;
                            }
                        }
                        break;
                    }
                }

            }
            pTP = pTP->p_next;
        }

    }           // if pPolyTessGeo




    return ret;
}



 extern wxLog *logger;

/************************************************************************/
/*                       OpenCPN_OGRErrorHandler()                      */
/*                       Use Global wxLog Class                         */
/************************************************************************/

void OpenCPN_OGRErrorHandler( CPLErr eErrClass, int nError,
                              const char * pszErrorMsg )
{

#define ERR_BUF_LEN 200

    char buf[ERR_BUF_LEN + 1];

    if( eErrClass == CE_Debug )
        snprintf( buf, ERR_BUF_LEN, "%s\n", pszErrorMsg );
    else if( eErrClass == CE_Warning )
        snprintf( buf, ERR_BUF_LEN, "Warning %d: %s\n", nError, pszErrorMsg );
    else
        snprintf( buf, ERR_BUF_LEN, "ERROR %d: %s\n", nError, pszErrorMsg );


    wxLogMessage("%s", buf);


    //      Do not simply return on CE_Fatal errors, as we don't want to abort()

    if(eErrClass == CE_Fatal)
    {
        longjmp(env_ogrf, 1);                  // jump back to the setjmp() point
    }

}



//      In GDAL-1.2.0, CSVGetField is not exported.......
//      So, make my own simplified copy
/************************************************************************/
/*                           MyCSVGetField()                            */
/*                                                                      */
/************************************************************************/


const char *MyCSVGetField( const char * pszFilename,
                         const char * pszKeyFieldName,
                         const char * pszKeyFieldValue,
                         CSVCompareCriteria eCriteria,
                         const char * pszTargetField )

{
    char        **papszRecord;
    int         iTargetField;


/* -------------------------------------------------------------------- */
/*      Find the correct record.                                        */
/* -------------------------------------------------------------------- */
    papszRecord = CSVScanFileByName( pszFilename, pszKeyFieldName,
                                     pszKeyFieldValue, eCriteria );

    if( papszRecord == NULL )
        return "";

/* -------------------------------------------------------------------- */
/*      Figure out which field we want out of this.                     */
/* -------------------------------------------------------------------- */
    iTargetField = CSVGetFileFieldId( pszFilename, pszTargetField );
    if( iTargetField < 0 )
        return "";

    if( iTargetField >= CSLCount( papszRecord ) )
        return "";

    return( papszRecord[iTargetField] );
}


//------------------------------------------------------------------------
//
//          Some s57 Utilities
//          Meant to be called "bare", usually with no class instance.
//
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//  Initialize GDAL/OGR S57ENC support
//------------------------------------------------------------------------

int s57_initialize(const wxString& csv_dir, FILE *flog)
{

    //  MS Windows Build Note:
    //  In a .dll GDAL build, the following _putenv() call DOES NOT properly
    //  set the environment accessible to GDAL/OGR.  So, S57 Reader options
    //  are not set AT ALL.  Defaults will apply.
    //  See the README file

#ifdef __WXMSW__
    wxString envs1("S57_CSV=");
    envs1.Append(csv_dir);
    _putenv((char *) envs1.c_str());
#else
    wxSetEnv( "S57_CSV", csv_dir.c_str());
#endif


        //  Set some S57 OGR Options thru environment variables

        //  n.b. THERE IS A BUG in GDAL/OGR 1.2.0 wherein the sense of the flag UPDATES= is reversed.
        //  That is, anything other than UPDATES=APPLY selects update mode.
        //  Conversely, UPDATES=APPLY deselects updates.
        //  Fixed in GDAL 1.3.2, at least, maybe earlier??
        //  Detect by GDALVersion check

    const char *version_string = GDALVersionInfo("VERSION_NUM");
    int ver_num = (int)CPLScanLong((char *)version_string, 4);

    wxString set1, set2;

    set1 ="LNAM_REFS=ON";
    set1.Append(",SPLIT_MULTIPOINT=OFF");
    set1.Append(",ADD_SOUNDG_DEPTH=OFF");
    set1.Append(",PRESERVE_EMPTY_NUMBERS=OFF");
    if(ver_num >= 1320)
        set1.Append(",RETURN_PRIMITIVES=OFF");              // older GDALs handle some "off" option poorly
    set1.Append(",RETURN_LINKAGES=OFF");



    if(ver_num < 1320)
        set2 = ",UPDATES=BUGBUG";               // updates ENABLED
    else
        set2 = ",UPDATES=APPLY";

    set1.Append(set2);

#ifdef __WXMSW__
    wxString envs2("OGR_S57_OPTIONS=");
    envs2.Append(set1);
    _putenv( (char *)envs2.c_str());

#else
    wxSetEnv("OGR_S57_OPTIONS",set1.c_str());
#endif


    RegisterOGRS57();

    return 0;
}





//----------------------------------------------------------------------------------
// Get Chart Scale
// By opening and reading directly the iso8211 file
//----------------------------------------------------------------------------------
int s57_GetChartScale(char *pFullPath)
{

    DDFModule   *poModule;
    DDFRecord   *poRecord;
    int scale;

    poModule = new DDFModule();

    if( !poModule->Open(pFullPath) )
    {
        delete poModule;
        return 0;
    }

    poRecord = poModule->ReadRecord();
    if( poRecord == NULL )
    {
        poModule->Close();
        delete poModule;
        return 0;
    }

    scale = 1;
    for( ; poRecord != NULL; poRecord = poModule->ReadRecord() )
    {
        if( poRecord->FindField( "DSPM" ) != NULL )
        {
            scale = poRecord->GetIntSubfield("DSPM",0,"CSCL",0);
            break;
        }
    }

    poModule->Close();
    delete poModule;

    return scale;

}

//----------------------------------------------------------------------------------
// Get First Chart M_COVR Object
// Directly from the ios8211 file
//              n.b. Caller owns the data source and the feature on success
//----------------------------------------------------------------------------------
bool s57_GetChartFirstM_COVR(char *pFullPath, OGRDataSource **pDS, OGRFeature **pFeature,
                                 OGRLayer **pLayer, int &catcov)
{

    OGRDataSource *poDS = OGRSFDriverRegistrar::Open( pFullPath );

    *pDS = poDS;                                    // give to caller

    if( poDS == NULL )
    {
        *pFeature = NULL;
        return false;
    }

    OGRLayer *pLay = poDS->GetLayerByName("M_COVR");
//begin rms
    if (NULL == pLay)
        return false ;
// end rms
    *pLayer = pLay;                         // Give to caller
    pLay->ResetReading();
    OGRFeature *objectDef = pLay->GetNextFeature();
    *pFeature = objectDef;                  // Give to caller

    if(objectDef)
    {
    //  Fetch the CATCOV attribute
        for( int iField = 0; iField < objectDef->GetFieldCount(); iField++ )
        {
            if( objectDef->IsFieldSet( iField ) )
            {
                OGRFieldDefn *poFDefn = objectDef->GetDefnRef()->GetFieldDefn(iField);
                if(!strcmp(poFDefn->GetNameRef(), "CATCOV"))
                    catcov = objectDef->GetFieldAsInteger( iField );
            }
        }
        return true;
    }

    else
    {
        delete poDS;
        *pDS = NULL;
        return false;
    }

}

//----------------------------------------------------------------------------------
// GetNext Chart M_COVR Object
// Directly from the ios8211 file
// Companion to s57_GetChartFirstM_COVR
//              n.b. Caller still owns the data source and the feature on success
//----------------------------------------------------------------------------------
bool s57_GetChartNextM_COVR(OGRDataSource *pDS, OGRLayer *pLayer, OGRFeature *pLastFeature,
                                OGRFeature **pFeature, int &catcov)
{


    if( pDS == NULL )
        return false;

    catcov = -1;


    int fid = pLastFeature->GetFID();

    OGRFeature *objectDef = pLayer->GetFeature(fid + 1);
    *pFeature = objectDef;                  // Give to caller

    if(objectDef)
    {
        for( int iField = 0; iField < objectDef->GetFieldCount(); iField++ )
        {
            if( objectDef->IsFieldSet( iField ) )
            {
                OGRFieldDefn *poFDefn = objectDef->GetDefnRef()->GetFieldDefn(iField);
                if(!strcmp(poFDefn->GetNameRef(), "CATCOV"))
                    catcov = objectDef->GetFieldAsInteger( iField );
            }
        }
        return true;
    }
    return false;
}


//----------------------------------------------------------------------------------
// Get Chart Extents
//----------------------------------------------------------------------------------
bool s57_GetChartExtent(char *pFullPath, Extent *pext)
{
 //   Fix this  find extents of which?? layer??
/*
    OGRS57DataSource *poDS = new OGRS57DataSource;
    poDS->Open(pFullPath, TRUE);

    if( poDS == NULL )
    return false;

    OGREnvelope Env;
    S57Reader   *poReader = poDS->GetModule(0);
    poReader->GetExtent(&Env, true);

    pext->NLAT = Env.MaxY;
    pext->ELON = Env.MaxX;
    pext->SLAT = Env.MinY;
    pext->WLON = Env.MinX;

    delete poDS;
*/
    return true;

}

//----------------------------------------------------------------------------------
//      ddfrecord_test
//----------------------------------------------------------------------------------

        /*
        GDAL/OGR 1.2.0 may have a bug in ddfrecord.cpp
        The bug is manifest on ENC updates only.
        This behaviour has been observed on ddfrecord.cpp Version 1.25 and earlier,
        and is corrected in ddfrecord.cpp Version 1.27 and above.

        This (relatively) safe run-time test will identify the pathology
        allowing run-time election of ENC update policy
        */

bool s57_ddfrecord_test()
{
        // Create a ddfrecord and populate the two simple text fields

    DDFRecord dr(NULL);
    DDFFieldDefn dfd1;
    DDFFieldDefn dfd2;

    dfd1.Create("tag1", "name", NULL, dsc_elementary, dtc_char_string);
    dfd1.AddSubfield( "sub1", "A" );
    dr.AddField( &dfd1 );
    dr.SetStringSubfield( "tag1", 0, "sub1",0, "testlongrrrrrrrrrrrrrrrrrrrr11");

    dfd2.Create("tag2", "name", NULL, dsc_elementary, dtc_char_string);
    dfd2.AddSubfield( "sub21", "A" );
    dr.AddField( &dfd2 );
    dr.SetStringSubfield( "tag2", 0, "sub21",0, "testlonggggggggggggggggggggg21");


        //  The hallmark of obsolete ddfrecord code is that shortening a data record
        //  corrupts some data following the shortened target

    char buf1[40], buf2[40];
        // get reference copy
    const char *before = dr.GetStringSubfield( "tag2", 0, "sub21", 0);
    strcpy(buf1, before);

        // Shorten early data
    dr.SetStringSubfield( "tag1", 0, "sub1",0, "test12a");

        //  and get it again
    const char *after = dr.GetStringSubfield( "tag2", 0, "sub21", 0);
    strcpy(buf2, after);

    if(strcmp(buf1, buf2))
        return false;
    else
        return true;

}

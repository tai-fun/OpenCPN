/**********************************************************************
zyGrib: meteorological GRIB file viewer
Copyright (C) 2008 - Jacques Zaninetti - http://www.zygrib.org

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include "dychart.h"        // for some compile time fixups
#include "chcanv.h"

#include "IsoLine.h"

//---------------------------------------------------------------
IsoLine::IsoLine(double val, const GribRecord *rec_)
{
    value = val;
    rec = rec_;
    W = rec->getNi();
    H = rec->getNj();
    int gr = 80;
    isoLineColor = wxColour(gr,gr,gr);
    //---------------------------------------------------------
    // Génère la liste des segments.
    extractIsoLine(rec);
//printf("create Isobar : press=%4.0f long=%d\n", pressure/100, trace.size());
}
//---------------------------------------------------------------
IsoLine::~IsoLine()
{
//printf("delete Isobar : press=%4.0f long=%d\n", pressure/100, trace.size());

    std::list<Segment *>::iterator it;
    for (it=trace.begin(); it!=trace.end(); it++) {
        delete *it;
        *it = NULL;
    }
    trace.clear();
}



//---------------------------------------------------------------
void IsoLine::drawIsoLine(wxMemoryDC *pmdc, ViewPort *vp)
{
    std::list<Segment *>::iterator it;

    //---------------------------------------------------------
    // Dessine les segments
    //---------------------------------------------------------
    for (it=trace.begin(); it!=trace.end(); it++)
    {
        Segment *seg = *it;

        {
              wxPoint ab = vp->GetMercatorPixFromLL(seg->py1, seg->px1);
              wxPoint cd = vp->GetMercatorPixFromLL(seg->py2, seg->px2);

              pmdc->DrawLine(ab.x, ab.y, cd.x, cd.y);

        }
    }
}

//---------------------------------------------------------------

void IsoLine::drawIsoLineLabels(wxMemoryDC *pmdc, wxColour couleur,
                                ViewPort *vp,
                            int density, int first, double coef)
{
    std::list<Segment *>::iterator it;
    int nb = first;
    wxString label;

    label.Printf(_T("%d"), (int)(value*coef+0.5));

    wxPen penText(couleur);

    int w, h;
    pmdc->GetTextExtent(label, &w, &h);

    pmdc->SetPen(penText);
    pmdc->SetBrush(*wxWHITE_BRUSH);

    //---------------------------------------------------------
    // Ecrit les labels
    //---------------------------------------------------------
    for (it=trace.begin(); it!=trace.end(); it++,nb++)
    {
        if (nb % density == 0) {
            Segment *seg = *it;
            wxPoint ab = vp->GetMercatorPixFromLL(seg->py1, seg->px1);
            wxPoint cd = vp->GetMercatorPixFromLL(seg->py2, seg->px2);

            int label_offset = 4;
            pmdc->DrawRoundedRectangle((ab.x + cd.x)/2 , (ab.y + cd.y)/2, w+(label_offset * 2), h, -.25);
            pmdc->DrawText(label, label_offset + (ab.x + cd.x)/2, (ab.y + cd.y)/2);

        }
    }
}



//==================================================================================
// Segment
//==================================================================================
Segment::Segment(int I, int J,
                char c1, char c2, char c3, char c4,
                const GribRecord *rec, double pressure)
{
    traduitCode(I,J, c1, i,j);
    traduitCode(I,J, c2, k,l);
    traduitCode(I,J, c3, m,n);
    traduitCode(I,J, c4, o,p);

    intersectionAreteGrille(i,j, k,l,  &px1,&py1, rec, pressure);
    intersectionAreteGrille(m,n, o,p,  &px2,&py2, rec, pressure);
}
//-----------------------------------------------------------------------
void Segment::intersectionAreteGrille(int i,int j, int k,int l, double *x, double *y,
                const GribRecord *rec, double pressure)
{
    double a,b, pa, pb, dec;
    pa = rec->getValue(i,j);
    pb = rec->getValue(k,l);
    // Abscisse
    a = rec->getX(i);
    b = rec->getX(k);
    if (pb != pa)
        dec = (pressure-pa)/(pb-pa);
    else
        dec = 0.5;
    if (fabs(dec)>1)
        dec = 0.5;
    *x = a+(b-a)*dec;
    // Ordonnée
    a = rec->getY(j);
    b = rec->getY(l);
    if (pb != pa)
        dec = (pressure-pa)/(pb-pa);
    else
        dec = 0.5;
    if (fabs(dec)>1)
        dec = 0.5;
    *y = a+(b-a)*dec;
}
//---------------------------------------------------------------
void Segment::traduitCode(int I, int J, char c1, int &i, int &j) {
    switch (c1) {
        case 'a':  i=I-1;  j=J-1; break;
        case 'b':  i=I  ;  j=J-1; break;
        case 'c':  i=I-1;  j=J  ; break;
        case 'd':  i=I  ;  j=J  ; break;
        default:   i=I  ;  j=J  ;
    }
}

//-----------------------------------------------------------------------
// Génère la liste des segments.
// Les coordonnées sont les indices dans la grille du GribRecord
//---------------------------------------------------------
void IsoLine::extractIsoLine(const GribRecord *rec)
{
    int i, j, W, H;
    double x, y, a,b,c,d;
    W = rec->getNi();
    H = rec->getNj();

    for (j=1; j<H; j++)     // !!!! 1 to end
    {
        for (i=1; i<W; i++)
        {
            x = rec->getX(i);
            y = rec->getY(j);

            a = rec->getValue( i-1, j-1 );
            b = rec->getValue( i,   j-1 );
            c = rec->getValue( i-1, j   );
            d = rec->getValue( i,   j   );

            // Détermine si 1 ou 2 segments traversent la case ab-cd
            // a  b
            // c  d
            //--------------------------------
            // 1 segment en diagonale
            //--------------------------------
            if     ((a<=value && b<=value && c<=value  && d>value)
                 || (a>value && b>value && c>value  && d<=value))
                trace.push_back(new Segment(i,j, 'c','d',  'b','d', rec,value));
            else if ((a<=value && c<=value && d<=value  && b>value)
                 || (a>value && c>value && d>value  && b<=value))
                trace.push_back(new Segment(i,j, 'a','b',  'b','d', rec,value));
            else if ((c<=value && d<=value && b<=value  && a>value)
                 || (c>value && d>value && b>value  && a<=value))
                trace.push_back(new Segment(i,j, 'a','b',  'a','c', rec,value));
            else if ((a<=value && b<=value && d<=value  && c>value)
                 || (a>value && b>value && d>value  && c<=value))
                trace.push_back(new Segment(i,j, 'a','c',  'c','d', rec,value));
            //--------------------------------
            // 1 segment H ou V
            //--------------------------------
            else if ((a<=value && b<=value   &&  c>value && d>value)
                 || (a>value && b>value   &&  c<=value && d<=value))
                trace.push_back(new Segment(i,j, 'a','c',  'b','d', rec,value));
            else if ((a<=value && c<=value   &&  b>value && d>value)
                 || (a>value && c>value   &&  b<=value && d<=value))
                trace.push_back(new Segment(i,j, 'a','b',  'c','d', rec,value));
            //--------------------------------
            // 2 segments en diagonale
            //--------------------------------
            else if  (a<=value && d<=value   &&  c>value && b>value) {
                trace.push_back(new Segment(i,j, 'a','b',  'b','d', rec,value));
                trace.push_back(new Segment(i,j, 'a','c',  'c','d', rec,value));
            }
            else if  (a>value && d>value   &&  c<=value && b<=value) {
                trace.push_back(new Segment(i,j, 'a','b',  'a','c', rec,value));
                trace.push_back(new Segment(i,j, 'b','d',  'c','d', rec,value));
            }

        }
    }
}


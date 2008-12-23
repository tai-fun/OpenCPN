/******************************************************************************
 * $Id: cm93.h,v 1.1 2008/12/23 16:33:49 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  CM93 Chart Object
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
 * $Log: cm93.h,v $
 * Revision 1.1  2008/12/23 16:33:49  bdbcat
 * Add cm93 support
 *

 */

#ifndef __CM93CHART_H__
#define __CM93CHART_H__

#include    "s57chart.h"

//    Some constants
#define     INDEX_m_sor       217                // cm93 dictionary index for object type _m_sor

//    CM93 Data structures

#pragma pack(push,1)

//    This is the 128 byte cm93 cell header, found at offset 0x0a in the cell file
typedef struct{
      double                  lon_min;
      double                  lat_min;
      double                  lon_max;
      double                  lat_max;
      double                  m_20;
      double                  m_28;
      double                  m_30;
      double                  m_38;

      unsigned short          n_vector_records;        //m_40,  number of spacial(vector) records
      unsigned int            n_vector_record_points;  //m_42, number of cm93 points in vector record block
      int                     m_46;
      int                     m_4a;
      short                   m_4e;
      int                     m_50;
      int                     m_54;
      short                   m_58;
      short                   m_5a;
      short                   m_5c;
      short                   n_feature_records;            //m_5e, number of feature records

      int                     m_60;
      int                     m_64;
      short                   m_68;
      short                   m_6a;
      short                   m_6c;
      int                     m_6e;

      int                     m_72;
      short                   m_76;

      int                     m_78;
      int                     m_7c;

}header_struct;


typedef struct{
      unsigned short    x;
      unsigned short    y;
}cm93_point;




typedef struct{
      unsigned short          n_points;
      unsigned short          x_min;
      unsigned short          y_min;
      unsigned short          x_max;
      unsigned short          y_max;
      cm93_point              *p_points;              //m_10
}geometry_descriptor;

typedef struct{
      unsigned char m_0[6];
}struct_6;

typedef struct{
      geometry_descriptor           *m_0;
      unsigned char                 m_4;
}struct_5;

typedef struct{
      unsigned char     otype;
      unsigned char     geotype;
      unsigned short    n_points;         // m_2;, cuold also be n_segs for areas and lines
      void              *pGeometry;       // m_4, may be a (cm93_point*) or a (struct_5 *);
      unsigned char     m_8;
      void              *m_9;             // is usually a link to another struct_18
      unsigned char     n_attributes;     // number of attributes
      unsigned char     *attributes_block;      // encoded attributes

}Object;

typedef struct{
      unsigned char     object_type;
      unsigned char     geom_prim;
      unsigned short    n1;
}object_definition;



typedef struct{
      int                           m_12;
      int                           m_16;
      int                           m_1a;
      int                           m_1e;

      header_struct                 *m_22;            // Pointer to malloc'ed and previously read/decoded header
                                                      // Saved for no good reason?

      Object                        *m_26;
      void                          *m_2a;
      cm93_point                    *p2dpoint_array;  //m_2e;
      int                           *m_32;            // probably not int*
      struct_5                      *m_36;
      unsigned char                 *attribute_block_top;  // attributes block
      geometry_descriptor           *m_3e;
      geometry_descriptor           *m_42;
      cm93_point                    *pvector_record_block_top;
      struct_6                      *m_4a;
      double                        m_56_x_rate;
      double                        m_5e_y_rate;
      double                        m_66_x_origin;
      double                        m_6e_y_origin;

}Cell_Info_Block;

#pragma pack(pop)

//----------------------------------------------------------------------------
// cm93_dictionary class
//    Encapsulating the conversion between binary cm_93 object class, attributes, etc
//    to standard S57 text conventions
//----------------------------------------------------------------------------

class cm93_dictionary
{
      public:

            cm93_dictionary();
            ~cm93_dictionary();

            bool LoadDictionary(wxString dictionary_dir);

            bool IsOk(void){ return m_ok; }

            wxArrayString     *m_S57ClassArray;
            int               *m_GeomTypeArray;
            wxArrayString     *m_AttrArray;
            char              *m_ValTypeArray;

            bool              m_ok;
};


class cm93_attr_block
{
      public:
            cm93_attr_block(void * block, cm93_dictionary *pdict);
            unsigned char *GetNextAttr();

            int m_cptr;
            unsigned char *m_block;

            cm93_dictionary *m_pDict;
};




//----------------------------------------------------------------------------
// cm93 Chart object class
//----------------------------------------------------------------------------
class cm93chart : public s57chart
{
      public:
            cm93chart();
            ~cm93chart();

            InitReturn Init( const wxString& name, ChartInitFlag flags, ColorScheme cs );

      private:
            bool CreateHeaderDataFromCM93Cell(void);
            int read_header_and_populate_cib(header_struct *ph, Cell_Info_Block *pCIB);
            int BuildSENCFile(const wxString& FullPathCell, const wxString& SENCFileName);
            InitReturn PostInit( ChartInitFlag flags, ColorScheme cs );
            InitReturn FindOrCreateSenc( const wxString& name );
            cm93_dictionary *FindAndLoadDict(const wxString &file);
            void *BuildGeom(Object *pobject, wxFileOutputStream *postream, wxBoundingBox box, int iobject);
            int CreateCM93SENCRecord( int iobject, Object *pobject, cm93_dictionary *pDict,
                                   wxFileOutputStream &ostream, void *geom, double ref_lat, double ref_lon, double scale );
            void SetVPParms(ViewPort *vpt);

            void Degest_CM93_Cell(void);

            //    cm93 point manipulation methods
            void Transform(cm93_point *s, double *lat, double *lon);


            header_struct     m_header;
            Cell_Info_Block   m_CIB;

            int               m_nObjectRecords;                   // this is redundant

            cm93_dictionary   *m_pDict;

            double            m_sfactor;
};


#endif

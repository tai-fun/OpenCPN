/******************************************************************************
 * $Id: s52s57.h,v 1.1 2006/08/21 05:52:11 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  S52 PLIB and S57 Chart data types
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
 * $Log: s52s57.h,v $
 * Revision 1.1  2006/08/21 05:52:11  dsr
 * Initial revision
 *
 * Revision 1.5  2006/07/28 20:47:57  dsr
 * Cleanup
 *
 * Revision 1.4  2006/05/28 00:52:15  dsr
 * Implement PolyGeo
 *
 * Revision 1.3  2006/05/19 19:36:19  dsr
 * Cleanup
 *
 * Revision 1.2  2006/04/23 04:06:18  dsr
 * Implement S57 Query
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.5  2006/04/19 00:58:48  dsr
 * *** empty log message ***
 *
 * Revision 1.4  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/02/24 17:59:13  dsr
 * ReAdd OGRGeometry *OGeo to S57obj
 *
 * Revision 1.2  2006/02/23 01:25:17  dsr
 * Cleanup
 *
 *
 *
 */


#ifndef _S52S57_H_
#define _S52S57_H_



#include "gpc.h"
#include "bbox.h"

//    Fwd Defns
class wxArrayOfS57attVal;
class OGREnvelope;
class OGRGeometry;

typedef enum _S52_table_t{
                  //S52_PL_ID,                  // S52 Library Identification Module DB
                  //S52_PL_COL,                 // Colour Table (6)
         S52_LUP_PT_SIMPL,    // Look-Up Table for simplified point symbol
         S52_LUP_PT_PAPER,    // Look-Up Table for paper chart point symbol
         S52_LUP_LINE,           // Look-Up Table for line
         S52_LUP_AREA_PLN,    // Look-up Table for plain boundaries area
         S52_LUP_AREA_SYM,    // Look-Up Table for symbolized bound. area
         S52_LINE_SYM,           // Complex Linestyle Symbolisation Table
         S52_PATT_SYM,           // Pattern Symbolisation Table
         S52_SYMB_SYM,           // Symbol Symbolisation Table
         S52_COND_SYM,        // Conditional Symbolisation Table
         S52_TABLE_NUM        // number of Tables
}S52_table_t;



//    LUP Arrays
typedef enum _S52_LUP_table_t{
         S52_LUPARRAY_PT_SIMPL,     // Look-Up Table for simplified point symbol
         S52_LUPARRAY_PT_PAPER,     // Look-Up Table for paper chart point symbol
         S52_LUPARRAY_LINE,         // Look-Up Table for line
         S52_LUPARRAY_AREA_PLN,     // Look-up Table for plain boundaries area
         S52_LUPARRAY_AREA_SYM,     // Look-Up Table for symbolized bound. area
         S52_LUPARRAY_COND_SYM,     // Dynamic Look-Up Table for Conditional Symbology
         S52_LUPARRAY_TABLE_NUM           // number of Tables
}S52_LUP_table_t;

// Addressed Object Type
typedef enum _Object_t{
   POINT_T  = 'P',
   LINES_T  = 'L',
   AREAS_T  = 'A',
   OBJ_NUM  = 3         // number of object type
}Object_t;


// Display Priority
typedef enum _DisPrio{
   PRIO_NODATA          = '0',                  // no data fill area pattern
   PRIO_GROUP1          = '1',                  // S57 group 1 filled areas
   PRIO_AREA_1          = '2',                  // superimposed areas
   PRIO_AREA_2          = '3',                  // superimposed areas also water features
   PRIO_SYMB_POINT      = '4',                  // point symbol also land features
   PRIO_SYMB_LINE       = '5',                  // line symbol also restricted areas
   PRIO_SYMB_AREA       = '6',                  // area symbol also traffic areas
   PRIO_ROUTEING        = '7',                  // routeing lines
   PRIO_HAZARDS         = '8',                  // hazards
   PRIO_MARINERS        = '9',                  // VRM &amp; EBL, own ship
   PRIO_NUM             = 10                    // number of priority levels

}DisPrio;

// RADAR Priority
typedef enum _RadPrio{
   RAD_OVER = 'O',            // presentation on top of RADAR
   RAD_SUPP = 'S',            // presentation suppressed by RADAR
   RAD_NUM  = 2
}RadPrio;


// name of the addressed look up table set (fifth letter)
typedef enum _LUPname{
   SIMPLIFIED                             = 'L', // points
   PAPER_CHART                            = 'R', // points
   LINES                                  = 'S', // lines
   PLAIN_BOUNDARIES                       = 'N', // areas
   SYMBOLIZED_BOUNDARIES                  = 'O', // areas
   LUPNAME_NUM
}LUPname;

// display category type
typedef enum _DisCat{
   DISPLAYBASE          = 'D',            //
   STANDARD             = 'S',            //
   OTHER                = '0',            //
   MARINERS_STANDARD,                     // value not defined
   MARINERS_OTHER,                        // value not defined
   DISP_CAT_NUM,                          // value not defined
}DisCat;

//    display Color Scheme
typedef enum _col_schem{
      S52_DAY_BRIGHT,
      S52_DAY_WHITEBACK,
      S52_DAY_BLACKBACK,
      S52_DUSK,
      S52_NIGHT,
      S52_COL_SCHEME_MAX
}Col_Scheme_t;

typedef enum _Rules_t{
   RUL_NONE,                        // no rule type (init)
   RUL_TXT_TX,                      // TX
   RUL_TXT_TE,                      // TE
   RUL_SYM_PT,                      // SY
   RUL_SIM_LN,                      // LS
   RUL_COM_LN,                      // LC
   RUL_ARE_CO,                      // AC
   RUL_ARE_PA,                      // AP
   RUL_CND_SY,                      // CS
   RUL_MUL_SG                       // Multipoint Sounding
}Rules_t;

//-- SYMBOLISATION MODULE STRUCTURE -----------------------------
// position parameter:  LINE,       PATTERN, SYMBOL
typedef struct _position{
   union          {int              dummy1,     PAMI,       dummy2;     } minDist;
   union          {int              dummy1,     PAMA,       dummy2;     } maxDist;
   union          {int              LICL,       PACL,       SYCL;       } pivot_x;
   union          {int              LIRW,       PARW,       SYRW;       } pivot_y;
   union          {int              LIHL,       PAHL,       SYHL;       } bnbox_w;
   union          {int              LIVL,       PAVL,       SYVL;       } bnbox_h;
   union          {int              LBXC,       PBXC,       SBXC;       } bnbox_x; // UpLft crnr
   union    {int              LBXR,       PBXR,       SBXR;       } bnbox_y; // UpLft crnr
}position;

// rule parameter for : LINE,       PATTERN,    SYMBOL
typedef struct _Rule{
   int            RCID;
   union    {char             LINM[8],    PANM[8], SYNM[8]; } name;
   union          {char             dummy,      PADF,       SYDF; } definition;
   union          {char             dummy1,     PATP,       dummy2;     } fillType;
   union          {char             dummy1,     PASP,       dummy2;     } spacing;
   union          {position   line,       patt,       symb;       } pos;
   union          {wxString   *LXPO,      *PXPO,      *SXPO;      } exposition;
   union          {wxString   *dummy,     *PBTM,      *SBTM;      } bitmap;
   union          {wxString   *LCRF,  *PCRF,  *SCRF;  } colRef;
   union          {wxString   *LVCT,      *PVCT,      *SVCT;      } vector;

   union{                                 // not a S52 field
      unsigned int            pattName;   // pattern name (in fact its a GLuint)
      unsigned int            listName;   // display list (in fact its a GLuint)
      void    *pixelPtr;                  // pixel data in processor memory
   }userData;
}Rule;

typedef struct _Rules{
   Rules_t  ruleType;
   char    *INSTstr;          // Symbology Instruction string
   Rule       *razRule;       // rule
   struct _Rules *next;
}Rules;


// LOOKUP MODULE STRUCTURE
/*
typedef struct _LUPrec{
   int      RCID;       // record identifier
   char           OBCL[7];          // Name (6 char) '\0' terminated
   Object_t FTYP;             // 'A' Area, 'L' Line, 'P' Point
   DisPrio  DPRI;             // Display Priority
   RadPrio  RPRI;             // 'O' or 'S', Radar Priority
   LUPname  TNAM;             // FTYP:  areas, points, lines
   wxString *ATTC;                  // Attribute Code/Value (repeat)
   wxString *INST;                  // Instruction Field (rules)
   DisCat   DISC;             // Display Categorie: D/S/O, DisplayBase, Standard, Other
   int            LUCM;             // Look-Up Comment (PLib3.x put 'groupes' here,
                                          // hense 'int', but its a string in the specs)
   Rules   *ruleList;   // rasterization rule list
}LUPrec;
*/

class LUPrec{
public:
   int            RCID;             // record identifier
   char           OBCL[7];          // Name (6 char) '\0' terminated
   Object_t       FTYP;             // 'A' Area, 'L' Line, 'P' Point
   DisPrio        DPRI;             // Display Priority
   RadPrio        RPRI;             // 'O' or 'S', Radar Priority
   LUPname        TNAM;             // FTYP:  areas, points, lines
   wxString       *ATTC;            // Attribute Code/Value (repeat)
   wxArrayString *ATTCArray;        // ArrayString of LUP Attributes
   wxString       *INST;            // Instruction Field (rules)
   DisCat         DISC;             // Display Categorie: D/S/O, DisplayBase, Standard, Other
   int            LUCM;             // Look-Up Comment (PLib3.x put 'groupes' here,
                                    // hense 'int', but its a string in the specs)
   Rules          *ruleList;        // rasterization rule list
};

// Conditional Symbology
typedef struct _Cond{
   char *name;
   void *(*condInst)(void *param);
}Cond;




typedef struct _color{
   char colName[5];
   float x;
   float y;
   float L;
   unsigned char  R;
   unsigned char  G;
   unsigned char  B;
}color;

typedef struct _S52_Text {
    wxString   *frmtd;       // formated text string
    char       hjust;
    char       vjust;
    char       space;
    char       style;       // CHARS
    char       weight;      // CHARS
    char       width;       // CHARS
    int        bsize;       // CHARS -body size
    int        xoffs;       // pica (1 = 0.531mm)
    int        yoffs;       // pica (1 = 0.531mm)
    color      *col;        // colour
    int        dis;         // display
} S52_Text;



//-- COLOR MODULE STRUCTURE ---------------------------------------
typedef struct _colTable{
   wxString             * tableName;
   wxArrayPtrVoid * color;
}colTable;

//
// WARNING: must be in sync OGRatt_t
// S57query.h not include to simplifie module dependencie
// but now there is one !!!
// Alternatively load attribute value type from file!
#ifndef _S57QUERY_H_
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



typedef struct _OBJLElement{
      char  OBJLName[6];
      int         nViz;
}OBJLElement;



// From s57
// WDR: class declarations

// OGR primitiv
typedef enum _geoPrim_t{
   GEO_POINT,
   GEO_LINE,
   GEO_AREA,
   GEO_META,
   GEO_PRIM,            // number of primitive
}GeoPrim_t;


// in sync with OGREnvelope

typedef struct _Extent{
  double SLAT;
  double WLON;
  double NLAT;
  double ELON;
}Extent;

typedef struct _pt{
   double x;
   double y;
}pt;

typedef struct _opt{
   double x;
   double y;
}opt;



//      Fwd References
class s57chart;
class S57Obj;
class OGRFeature;
class polygroup;
class PolyGeo;


class S57Obj
{
public:

      //  Public Methods
      S57Obj();
      ~S57Obj();
      S57Obj(char *first_line, wxBufferedInputStream *fpx);

      // Private Methods
private:
      bool IsUsefulAttribute(char *buf);
      int my_fgets( char *buf, int buf_len_max, wxBufferedInputStream& ifs );
      int my_bufgetl( char *ib_read, char *ib_end, char *buf, int buf_len_max );

public:
      // Instance Data
      S57Obj                  *thisObj;
      char                    FeatureName[8];
      GeoPrim_t               Primitive_type;

      wxString                *attList;
      wxArrayOfS57attVal      *attVal;

      OGRFeature              *objectDef;             // opaque
      int                     iOBJL;
      int                     Index;

      OGRGeometry             *OGeo;                  // pointer to the native OGR Geometry
      int                     npt;                    // number of point in geoPt
      double                  x;                      // for POINT
      double                  y;
      double                  z;
      pt                      *geoPt;                 // for LINE & AREA
      S57Obj                  *ring;                  // list of interior ring

      polygroup               *MPoly;

      gpc_tristrip            *Tristrip;

      PolyGeo                 *pPolyGeo;


      wxBoundingBox           BBObj;
      wxBoundingBox           *BBStripArray;

      Rules                   *CSrules;               // per object conditional symbology
      int                     bCS_Added;

      S52_Text                *FText;
      int                     bFText_Added;

      int                     Scamin;                 // SCAMIN attribute decoded during load

};





// object rasterization rules
typedef struct _ObjRazRules{
   LUPrec          *LUP;
   S57Obj          *obj;
   s57chart        *chart;                //dsr ... chart object owning this rule set
   struct _ObjRazRules *next;
}ObjRazRules;



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





//----------------------------------------------------------------------------------
//          Used for s52 Fast Polygon Renderer
//----------------------------------------------------------------------------------
class render_canvas_parms
{
public:
      unsigned char           *pix_buff;
      unsigned char           *mask_buff;
      int                     lclip;
      int                     rclip;
      int                     pb_pitch;
      int                     x;
      int                     y;
      int                     width;
      int                     height;
      int                     depth;
      void                    *PCPtr;      // PixelCache Pointer stored here, if used
};



#endif

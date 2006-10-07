/******************************************************************************
 * $Id: s52plib.h,v 1.3 2006/10/07 03:50:54 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  S52 Presentation Library
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
 * $Log: s52plib.h,v $
 * Revision 1.3  2006/10/07 03:50:54  dsr
 * *** empty log message ***
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.3  2006/05/28 00:52:15  dsr
 * Implement PolyGeo
 *
 * Revision 1.2  2006/05/19 19:36:19  dsr
 * Cleanup
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.5  2006/04/19 00:58:25  dsr
 * Implement Area Pattern skeleton
 *
 * Revision 1.4  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.3  2006/02/24 17:58:28  dsr
 * Add Multipoint Sounding render
 *
 * Revision 1.2  2006/02/23 01:24:39  dsr
 * Cleanup, add accessors
 *
 *
 *
 */


#ifndef _S52PLIB_H_
#define _S52PLIB_H_






#include "s52s57.h"                 //types


//    Dynamic arrays of pointers need explicit macros in wx261
#ifdef __WX261
WX_DEFINE_ARRAY_PTR(S57attVal *, wxArrayOfS57attVal);
#else
WX_DEFINE_ARRAY(S57attVal *, wxArrayOfS57attVal);
#endif



//    wxWindows Hash Map Declarations
#include <wx/hashmap.h>
class LUPHash;
class RuleHash;

WX_DECLARE_HASH_MAP( wxString, LUPrec*, wxStringHash , wxStringEqual, LUPHash );
WX_DECLARE_HASH_MAP( wxString, Rule*, wxStringHash , wxStringEqual, RuleHash );


WX_DEFINE_SORTED_ARRAY(LUPrec *, wxArrayOfLUPrec);



class ViewPort;
class PixelCache;

//-----------------------------------------------------------------------------
//    s52plib definition
//-----------------------------------------------------------------------------

class s52plib
{
public:

      s52plib(const wxString& PLPath, const wxString& PLLib, const wxString& PLCol);
      ~s52plib();

      void  SetPPMM(float ppmm){ canvas_pix_per_mm = ppmm;}
      LUPrec  *S52_lookupA(S52_LUP_table_t table_t, const char * objectName, S57Obj *pObj, bool bStrict = 0);
      int   _LUP2rules(LUPrec *LUP, S57Obj *pObj);
      color *S52_getColor(char *colorName);

//    Rendering stuff
      int _draw(wxDC *pdc, ObjRazRules *rzRules, ViewPort *vp);
      int RenderArea(wxDC *pdc, ObjRazRules *rzRules, ViewPort *vp, render_canvas_parms *pb_spec);

 // Accessors
      bool GetShowS57Text(){return m_bShowS57Text;}
      void SetShowS57Text(bool f){m_bShowS57Text = f;}

      bool GetColorScheme(){return m_ColorScheme;}
      void SetColorScheme(Col_Scheme_t c);



 //Todo accessors
      DisCat      m_nDisplayCategory;
      int         m_nSymbolStyle;
      int         m_nBoundaryStyle;
      bool         m_bOK;
//  Todo Make this type safe, it is always an array of (OBJLElement *)
      wxArrayPtrVoid    *pOBJLArray;    // Used for Display Filtering
      RuleHash          *_symb_sym;     // symbol symbolisation rules

  private:
      int   S52_load_Plib(char *pPLPath, char *pPLLib, char *pPLCol);
      int   S52Load_Plib_Ext(char *pPLPath, char *pPLExtensionDir, char *pPLExtensionType);
      int   S52_load_Plib(const wxString& PLPath, const wxString& PLLib, const wxString& PLCol);
      bool  S52_flush_Plib();




      bool ObjectRenderCheck(ObjRazRules *rzRules, ViewPort *vp);
      int _renderTX(ObjRazRules *rzRules, Rules *rules, ViewPort *vp);
      int _renderTE(ObjRazRules *rzRules, Rules *rules, ViewPort *vp);
      int _renderSY(ObjRazRules *rzRules, Rules *rules, ViewPort *vp);
      int _renderLS(ObjRazRules *rzRules, Rules *rules, ViewPort *vp);
      int _renderLSA(ObjRazRules *rzRules, Rules *rules, ViewPort *vp);
      int _renderLC(ObjRazRules *rzRules, Rules *rules, ViewPort *vp);
      int _renderMPS(ObjRazRules *rzRules, Rules *rules, ViewPort *vp);
      char *_renderCS(ObjRazRules *rzRules, Rules *rules);

      int FastRenderAC(ObjRazRules *rzRules, Rules *rules, ViewPort *vp, render_canvas_parms *pb_spec);
      int FastRenderAP(ObjRazRules *rzRules, Rules *rules, ViewPort *vp, render_canvas_parms *pb_spec);
      void FastRenderFilledPolygon(ObjRazRules *rzRules,
               S57Obj *obj, color *c, wxBoundingBox &BBView,
               render_canvas_parms *pb_spec, render_canvas_parms *mask,
               render_canvas_parms *patt_spec);

      void draw_lc_poly(wxDC *pdc, wxPoint *ptp, int npt,
                           float sym_len, float sym_factor, Rule *draw_rule);


      bool RenderHPGL(Rule * rule_in, wxDC *pdc, wxPoint &r, float rot_angle = 0);
      bool RenderRasterSymbol(Rule *prule, wxDC *pdc, wxPoint &r, float rot_angle = 0);
      wxImage *RuleXBMToImage(Rule *prule);

      int dda_poly(int nvert, int ivmin, int ivmax, wxPoint *ptp, color *c,
                      render_canvas_parms *pb_spec,
                      render_canvas_parms *mask,
                      render_canvas_parms *pPatt_spec);

      int dda_tri(wxPoint *ptp, color *c,
                           render_canvas_parms *pb_spec,
                           render_canvas_parms *mask,
                           render_canvas_parms *pPatt_spec);
      int LoadColors(char *pColorFile);

      LUPHash *s52plib::_selectLUP(LUPname TNAM);
      wxArrayOfLUPrec *SelectLUPARRAY(LUPname TNAM);

      int _loadCondSymb();
      int _collectLUP(void *key, void *LUP, void *objName);
      LUPrec *_findFromATT(wxArrayPtrVoid *nameMatch,char *objAtt, wxArrayOfS57attVal *objAttVal, bool bStrict);
      int _readS52Line( char *pBuffer, char *delim, int nCount, FILE *fp );
      int _chopS52Line(char *pBuffer, char c);
      int _parsePos(position *pos, char *buf, bool patt);
      int _parseLBID(FILE *fp);
      int _parseCOLS(FILE *fp);
      int _parseLUPT(FILE *fp);
      int _parseLNST(FILE *fp);
      int _parsePATT(FILE *fp);
      int _parseSYMB(FILE *fp, RuleHash *pHash);
      Rules *StringToRules(char *str);
      void GetAndAddCSRules(ObjRazRules *rzRules, Rules *rules);


      void DestroyLUPArray(wxArrayOfLUPrec *pLUPArray);
      void DestroyLUP(LUPrec *pLUP);

//    Library data

      wxArrayPtrVoid          *pAlloc;

// working buffer
#define  MAX_BUF  1024
      char buffer[MAX_BUF];
      char *pBuf;

/*
// Look-Up --Balanced Binary Tree
static GTree *_lineLUP          = NULL;   // lines
static GTree *_areaPlaineLUP = NULL;      // areas: PLAIN_BOUNDARIES
static GTree *_areaSymbolLUP = NULL;      // areas: SYMBOLIZED_BOUNDARIE
static GTree *_pointSimplLUP = NULL;      // points: SIMPLIFIED
static GTree *_pointPaperLUP = NULL;      // points: PAPER_CHART


// Symbolisation Rules --Balanced Binary Tree
static GTree *_line_sym = NULL;                 // line symbolisation rules
static GTree *_patt_sym = NULL;                 // pattern symbolisation rules
static GTree *_symb_sym = NULL;                 // symbol symbolisation rules
static GTree *_cond_sym = NULL;                 // conditional symbolisation rules
*/

// Look-Up --
      LUPHash *_lineLUP;                  // lines
      LUPHash *_areaPlaineLUP;      // areas: PLAIN_BOUNDARIES
      LUPHash *_areaSymbolLUP;      // areas: SYMBOLIZED_BOUNDARIE
      LUPHash *_pointSimplLUP;      // points: SIMPLIFIED
      LUPHash *_pointPaperLUP;      // points: PAPER_CHART


// Symbolisation Rules --
      RuleHash *_line_sym;                // line symbolisation rules
      RuleHash *_patt_sym;                // pattern symbolisation rules
      RuleHash *_cond_sym;                // conditional symbolisation rules
      RuleHash *_symb_symR;               // symbol symbolisation rules, Raster



//      Todo these could be eliminated as redundant
//      replace in code by LUPTable[S52_LUPARRAY_???];
//    Sorted Arrays of LUPrecs
      wxArrayOfLUPrec *lineLUPArray;            // lines
      wxArrayOfLUPrec *areaPlaineLUPArray;      // areas: PLAIN_BOUNDARIES
      wxArrayOfLUPrec *areaSymbolLUPArray;      // areas: SYMBOLIZED_BOUNDARIE
      wxArrayOfLUPrec *pointSimplLUPArray;      // points: SIMPLIFIED
      wxArrayOfLUPrec *pointPaperLUPArray;      // points: PAPER_CHART
      wxArrayOfLUPrec *condSymbolLUPArray;      // Dynamic Conditional Symbology



// Tables
      void *_table     [S52_TABLE_NUM]; // BTree holder
      int    _table_size[S52_TABLE_NUM];  // number of recorde per table

      wxArrayPtrVoid *_colTables;


      void  *LUPTable   [S52_LUPARRAY_TABLE_NUM];

      float       canvas_pix_per_mm;            // Set by parent, used to scale symbols/lines/patterns

// collect LUP that match object name
      wxArrayPtrVoid *nameMatch;

      wxFont      *pSmallFont;

      color       unused_color;
      bool        bUseRasterSym;

      bool        m_bShowS57Text;

       wxDC       *pdc;                       // The current DC

      PixelCache *pPCPatt;
      int         *ledge;
      int         *redge;

      Col_Scheme_t  m_ColorScheme;
      int         n_colTables;
};

#endif //_S52PLIB_H_

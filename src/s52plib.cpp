/******************************************************************************
 * $Id: s52plib.cpp,v 1.6 2006/12/03 21:36:23 dsr Exp $
 *
 * Project:  OpenCPN
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
 * $Log: s52plib.cpp,v $
 * Revision 1.6  2006/12/03 21:36:23  dsr
 * On text objects, define a bounding box to include text extents fully. This forces full redraw on viewport intersection, so that text objects scrolling onto the screen are always rendered.
 *
 * Revision 1.5  2006/10/08 00:36:44  dsr
 * no message
 *
 * Revision 1.4  2006/10/07 03:50:27  dsr
 * *** empty log message ***
 *
 * Revision 1.3  2006/10/01 03:22:58  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:37:36  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.9  2006/08/04 11:42:02  dsr
 * no message
 *
 * Revision 1.8  2006/07/28 20:42:23  dsr
 * Cleanup
 *
 * Revision 1.7  2006/06/15 02:47:05  dsr
 * Implement Render Symbol orientation
 *
 * Revision 1.6  2006/06/02 02:13:33  dsr
 * Improve DDA Logic
 *
 * Revision 1.5  2006/05/28 01:46:06  dsr
 * Cleanup
 *
 * Revision 1.4  2006/05/28 00:51:57  dsr
 * Implement PolyGeo
 *
 * Revision 1.3  2006/05/19 19:12:47  dsr
 * Implement new CS logic, Pattern render, and PolyPoly object render, etc...
 *
 * Revision 1.2  2006/04/23 04:01:03  dsr
 * Prettify
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.8  2006/04/19 00:48:59  dsr
 * Implement Area Pattern skeleton
 *
 * Revision 1.7  2006/03/16 03:08:24  dsr
 * Cleanup tabs
 *
 * Revision 1.6  2006/03/01 04:20:21  dsr
 * Correct Color fetch for Area Fill
 *
 * Revision 1.5  2006/02/24 18:07:04  dsr
 * Implement Render for MultiPont Soundings
 *
 * Revision 1.4  2006/02/24 03:04:36  dsr
 * Cleanup, include wximage.h
 *
 * Revision 1.3  2006/02/23 01:48:16  dsr
 * Cleanup, optimize
 *
 *
 *
 */


// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
    #include "wx/wx.h"
#endif //precompiled headers

#include "dychart.h"

#include "georef.h"

#include "s52plib.h"
#include "s57chart.h"                   // for back function references
#include "mygeom.h"
#include <stdlib.h>                             // 261, min() becomes __min(), etc.

#include "wx/image.h"                   // Missing from wxprec.h

#ifndef __WXMSW__
#include <malloc.h>
#endif


extern "C" void gpc_polygon_clip(gpc_op       operation,
                                gpc_polygon *subject_p,
                                gpc_polygon *clip_p,
                                gpc_polygon *result_p);

extern s52plib          *ps52plib;

CPL_CVSID("$Id: s52plib.cpp,v 1.6 2006/12/03 21:36:23 dsr Exp $");

//-----------------------------------------------------------------------------
//      s52plib implementation
//-----------------------------------------------------------------------------
s52plib::s52plib(const wxString& PLPath, const wxString& PLLib, const wxString& PLCol)

{
//      Set up some buffers, etc...
      pBuf = buffer;
      n_colTables = 0;

      pAlloc = new wxArrayPtrVoid;
      pOBJLArray = new wxArrayPtrVoid;

      m_bOK = S52_load_Plib(PLPath, PLLib, PLCol);

      pSmallFont = wxTheFontList->FindOrCreateFont(16, wxDEFAULT,wxNORMAL, wxBOLD,
                                                FALSE, wxString("Eurostile Extended"));

      m_bShowS57Text = false;
      m_ColorScheme = S52_DAY_BRIGHT;

      _symb_symR = NULL;
      bUseRasterSym = false;

        //      Sensible defaults
        m_nSymbolStyle = PAPER_CHART;
        m_nDisplayCategory = OTHER;

      ledge = new int[2000];
      redge = new int[2000];

      pPCPatt = NULL;



}




s52plib::~s52plib()
{
        if(m_bOK)
        {
                S52_flush_Plib();

//      Free the OBJL Array Elements
                for(unsigned int iPtr = 0 ; iPtr < pOBJLArray->GetCount() ; iPtr++)
                   free(pOBJLArray->Item(iPtr));

                delete pOBJLArray;
        }

      delete ledge;
      delete redge;

}










//------------------------
//
//      MODULES LINKING SECTION
//
//------------------------



// file to get some basic RGB
#define DUMMY_RGB_BRIGHT        "c:\\enc_root\\S52rgb.txt"

//      To Get CIE colors, see "s52RAZ.RLE"

#if 0
// convert CIE -> RGB   --NOT IMPLEMENTED!
int s52plib::_CIE2RGB()
{
   FILE         *fp;
   int  ret = 0;
   char         buffer[1024];
   char *pBuf = (char *)&buffer;
   color c1, *c2;
   int R,G,B;
   colTable *ct = (colTable *)(_colTables->Item(0));  //&g_array_index(_colTables, colTable, 0);

   int colIdx = 0;



   // read RGB from file for now!
   // DAY_BRIGHT only
   fp = fopen(DUMMY_RGB_BRIGHT, "r");
   if (fp == NULL){
      printf("ERROR unable to open color for %s\n",DUMMY_RGB_BRIGHT);
      return 0;
   }

   ret = fscanf(fp, "%[^\n]", pBuf);
   fgetc(fp);

   while (ret == 1) {
      printf("%s\n",pBuf);
      if (pBuf[0] != ';'){

         sscanf(pBuf, "%5s %i %i %i", c1.colName, &R, &G, &B);
         c1.R = (char)R;
         c1.G = (char)G;
         c1.B = (char)B;

         c2 = (color *)(ct->color->Item(colIdx++));     //&g_array_index(ct->color, color, colIdx++);

         if(0 != strncmp(c1.colName, c2->colName, 5)){
            printf("file %s not in sync with PLib at idx %d, color %s\n",
                DUMMY_RGB_BRIGHT, colIdx, c2->colName);
         }else{
            c2->R = c1.R;
            c2->G = c1.G;
            c2->B = c1.B;
         }
      }
      ret = fscanf(fp, "%[^\n]", pBuf);
      fgetc(fp);

   }
   fclose(fp);

   return FALSE;
}
#endif

//      Read private file to associate CIE colors to decent RGB values

int s52plib::LoadColors(char *pColorFile)
{
   FILE         *fp;
   int  ret = 0;
   char         buffer[1024];
   char *pBuf = (char *)&buffer;
   color c1, *c2;
   int R,G,B;
   colTable *ct = (colTable *)(_colTables->Item(0));  //&g_array_index(_colTables, colTable, 0);
   colTable *ctp;

   int colIdx = 0;
   char TableName[80];
   float x, y, Y;
        char *pBuft;

   fp = fopen(pColorFile, "r");
   if (fp == NULL){
       wxLogMessage("ERROR unable to open color file %s",pColorFile);
      return 0;
   }

   ret = fscanf(fp, "%[^\n]", pBuf);
   fgetc(fp);

   while (ret == 1) {
          if(!strncmp((const char *)pBuf, "Table", 5))
          {
                  sscanf(pBuf, "Table:%s", TableName);

                  for(unsigned int it=0 ; it < _colTables->GetCount() ; it++)
                  {
                   ctp = (colTable *)(_colTables->Item(it));
                   if(!strcmp(TableName, ctp->tableName->c_str()))
                   {
                           ct = ctp;
                           colIdx = 0;
                                break;
                        }
                  }

      fgetc(fp);
          }

//      Skip over comments "#" and blank lines
      else if ((pBuf[0] != '#') && (strlen(pBuf)))
          {

         sscanf(pBuf, "%5s", c1.colName);
                 pBuft = pBuf + 6;
                 while(*pBuft != ';')
                         pBuft++;

         sscanf(pBuft, ";%f;%f;%f;%i;%i;%i", &x, &y, &Y, &R, &G, &B);
         c1.R = (char)R;
         c1.G = (char)G;
         c1.B = (char)B;


//      Search for the matching color name in the previously loaded table
                int colMatch = 0;
                for (unsigned int ic=0; ic<ct->color->GetCount(); ++ic)
                {
                c2 = (_color *)ct->color->Item(ic);
                if (!strncmp(c1.colName, c2->colName, 5))
                        {
                    c2->R = c1.R;
                c2->G = c1.G;
                    c2->B = c1.B;
                                colMatch = 1;
                                break;
                        }
                }

                if(!colMatch)
                {
                    wxLogMessage("Color translation failed...file:%s, RGB Color name:%s",
                                        pColorFile, c1.colName);
                }

/*
         c2 = (color *)(ct->color->Item(colIdx++));     //&g_array_index(ct->color, color, colIdx++);

         if(0 != strncmp(c1.colName, c2->colName, 5)){
                         colIdx--;
                         printf("file %s not in sync with PLib at idx %d, color %s\n",
                CIE_RGB_DATA, colIdx, c2->colName);
         }else{
            c2->R = c1.R;
            c2->G = c1.G;
            c2->B = c1.B;
         }
*/
      }         //if valid color line


      buffer[0] = 0;
          ret = fscanf(fp, "%[^\n]", pBuf);
      if(fgetc(fp) == '\n')
                  ret = 1;


   }
   fclose(fp);

   //   Create an unused color, for bitmap mask creation
   //   Find one by searching all the color tables

   //   This alogorithm only tries to vary R for uniqueness
   //   ....could be better

   color ctent;
   ctent.R = ctent.G = ctent.B = 0;

   bool bdone = false;

        while((ctent.R < 254) && !bdone)
        {
                int match = 0;
                for(unsigned int it=0 ; it < _colTables->GetCount() ; it++)
                {
                        ct = (colTable *)(_colTables->Item(it));

                        for (unsigned int ic=0; ic<ct->color->GetCount(); ++ic)
                        {
                        c2 = (_color *)ct->color->Item(ic);
                                if((c2->R == ctent.R) && (c2->G == ctent.G) && (c2->B == ctent.B))
                                        match++;
                        }

                }

                if(match == 0)
                {
                        unused_color = ctent;
                        bdone = true;
                }

                ctent.R ++;
        }



   return FALSE;
}

wxArrayOfLUPrec *s52plib::SelectLUPARRAY(LUPname TNAM)
{
   switch(TNAM){
      case SIMPLIFIED:                          return pointSimplLUPArray;
      case PAPER_CHART:                         return pointPaperLUPArray;
      case LINES:                                       return lineLUPArray;
      case PLAIN_BOUNDARIES:            return areaPlaineLUPArray;
      case SYMBOLIZED_BOUNDARIES:       return areaSymbolLUPArray;
      default:
          wxLogMessage("S52:_selctLUP() ERROR");
   }

   return NULL;
}

LUPHash *s52plib::_selectLUP(LUPname TNAM)
{
/*
   switch(TNAM){
      case SIMPLIFIED:                          return _pointSimplLUP;
      case PAPER_CHART:                         return _pointPaperLUP;
      case LINES:                                               return _lineLUP;
      case PLAIN_BOUNDARIES:    return _areaPlaineLUP;
      case SYMBOLIZED_BOUNDARIES:return _areaSymbolLUP;
      default:
         printf("S52:_selctLUP() ERROR !!\n");
   }

   // should'nt reach this !?
//   g_assert_not_reached();    // turn off via G_DISABLE_ASSERT
*/
   return NULL;
}

/*
gint _compareLUP(gconstpointer keyA, gconstpointer keyB)
{
   int comp;
   GString *A = (GString*)keyA;
   GString *B = (GString*)keyB;

   comp = strcmp(A->str, B->str);
   return comp;
}

gint _compareRules(gconstpointer keyA, gconstpointer keyB)
{
   int comp;

   comp = strncmp((char*)keyA,(char*)keyB,8);
   return comp;
}
*/

// see S52cond.c
/*
static Cond condTable[];
static int _loadCondSymb()
{
   int i = 0;
   for(i=0; condTable[i].condInst != NULL; ++i)
   {
 //     g_tree_insert(_cond_sym, (gpointer*)condTable[i].name,
 //                                                              (gpointer*)condTable[i].condInst);

           wxString index = condTable[i].name;

           (*_cond_sym)[index] = (Rule *)(condTable[i].condInst);
   }
   return 1;
}
*/

extern Cond condTable[];
int s52plib::_loadCondSymb()
{
        for(int i=0 ; condTable[i].condInst != NULL; ++i)
        {
           wxString index = condTable[i].name;

           (*_cond_sym)[index] = (Rule *)(condTable[i].condInst);
   }
   return 1;
}




int s52plib::_collectLUP(void *key, void *LUP, void *objName)
{
   int comp;
   wxString *LUPobjName = (wxString*)key;

   comp = strncmp(LUPobjName->c_str(),(char*)objName, 6);

   if(comp < 0)
      return FALSE;
   if(comp > 0)
      return TRUE;      // stop searching

   nameMatch->Add(LUP);                 //g_ptr_array_add(nameMatch,LUP);

   return FALSE;
}


// get LUP with "best" Object attribute match
LUPrec *s52plib::_findFromATT(wxArrayPtrVoid *nameMatch,char *objAtt,
                              wxArrayOfS57attVal *objAttVal, bool bStrict)
{
   LUPrec *LUP = NULL;
   int nATTMatch = 0;
   int i = 0;
   int   countATT = 0;

   // setup default to the first LUP
   LUP =  (LUPrec*)nameMatch->Item(0);

   for(i=0; i<(int)nameMatch->GetCount(); ++i){
      LUPrec *LUPtmp = NULL;
      wxString *ATTC  = NULL;
      //char *attFound = NULL;
      countATT = 0;
      char *currATT  = objAtt;
      int   attIdx   = 0;

      LUPtmp = (LUPrec*)nameMatch->Item(i);
      ATTC   = (wxString*)LUPtmp->ATTC;


//      if (0 == strncmp(LUPtmp->OBCL, "BOYLAT", 6))
//         int eert = 8;


      if (ATTC == NULL)
          continue;

      if (objAtt == NULL)
         return LUP;                    // att match


      for(unsigned int iLUPAtt = 0 ; iLUPAtt < LUPtmp->ATTCArray->GetCount() ; iLUPAtt++)
          {

                        wxString LATTC;
                        LATTC = LUPtmp->ATTCArray->Item(iLUPAtt);

                          while (*currATT != '\0'){
                                 if (0 == strncmp(LATTC.c_str(), currATT,6)){
                                        //OK we have an attribute match
                                        //checking attribute value
                                        S57attVal *v;
#define BOOL bool
                                         BOOL attValMatch = FALSE;

                                        // special case (i)
                                        if ((LATTC.c_str())[6] == ' ')  // use any value
                                           attValMatch = TRUE;

                                        // special case (ii)
                              if ( strncmp(LUPtmp->OBCL, "DEPARE", 6))
                                  {
                                        if ((LATTC.c_str())[6] == '?')  // match if value is unknown
                                           attValMatch = TRUE;          // OGR bug here ???
                                  }

                                        v = (objAttVal->Item(attIdx));


                                        switch(v->valType){
                                           case OGR_INT:{    // S57 attribute type 'E' enumerated, 'I' integer
                                        int a;
                                                         sscanf(LATTC.c_str() + 6, "%d", &a);
                                                         if (a == *(int*)(v->value))
                                                                attValMatch = TRUE;
                                        break;
                                                  }

                                           case OGR_INT_LST:{   // S57 attribute type 'L' list: comma separated integer
                                        int a;
                                                         char *s = (char *)(LATTC.c_str() + 6);
                                                         int *b = (int*)v->value;
                                                         sscanf(s, "%d", &a);

                                                         while(*s != '\0'){
                                                                if ( a == *b ){
                                                                   sscanf(++s, "%d", &a);
                                                                   b++;
                                                                   attValMatch = TRUE;

                                                                }else
                                                                   attValMatch = FALSE;
                                                         }
                                        break;
                                                  }
                                           case OGR_REAL:{              // S57 attribute type'F' float
                                                        float a;
                                                        if ((LATTC.c_str())[6] != '?')
                                                        {
                                                                sscanf(LATTC.c_str() + 6, "%f", &a);
                                                                if (a == *(float*)(v->value))
                                                                        attValMatch = TRUE;
                                                        }
                                        break;
                                                  }

                                           case OGR_STR:{   // S57 attribute type'A' code string, 'S' free text
                                                        int a;                // Attribute value from LUP
                                                        char *s = (char *)(LATTC.c_str() + 6);
                                                        sscanf(s, "%d", &a);

                                                        char *c = (char *)v->value;    // Attribute from object
                                                        int b = atoi(c);

                                                        if ( a == b )
                                                        {
                                                           attValMatch = TRUE;
                                                        }


                                        break;
                                                  }

                                           default:
//                                                printf("S52:_findFromATT(): unknown attribute type\n");
                                                        break;
                                        }   //switch

                                        // value match
                                        if (attValMatch)
                                           ++countATT;

                                        goto next_LUP_Attr;
                                 }  // if attribute match

                                 while(*currATT != '\037')
                                        currATT++;
                                 currATT++;

                                 ++attIdx;

                          }  //while

next_LUP_Attr:
//                        continue;

                          currATT  = objAtt;            // restart the object attribute list
                          attIdx = 0;
          }             // for iLUPAtt

      // What should be done in the case 'countATT == nATTMatch' !!!!
      // that is, there is a match with different set of attributes.
      // Right now the first match found is returned!
      if (countATT > nATTMatch){
         nATTMatch = countATT;
         LUP = LUPtmp;
      }

   }  //for loop


//  In strict mode, we require at least one attribute to match exactly

   if(bStrict)
   {
        if(nATTMatch == 0)                  // nothing matched
            LUP = NULL;
   }
   else
   {
//      If no match found, return the first LUP in the list which has no attributes
        if(nATTMatch == 0)
        {
           for(i=0; i<(int)nameMatch->GetCount(); ++i)
           {
                  LUPrec *LUPtmp = NULL;

                  LUPtmp = (LUPrec*)nameMatch->Item(i); //g_ptr_array_index(nameMatch, i);
                  if(LUPtmp->ATTCArray == NULL)
                          return LUPtmp;
           }

        }
   }



   return LUP;
}


// scan foward stop on ; or end-of-record
#define SCANFWRD        while( !(*str == ';' || *str == '\037')) ++str;

#define INSTRUCTION(s,t)        if(0==strncmp(s,str,2)){\
                                                                        str+=3;\
                              r->ruleType = t;\
                              r->INSTstr  = str;
/*
#define LOOKUP(db)    r->razRule = g_tree_lookup(db, str);\
                      if (r->razRule == NULL)\
                         r->razRule = g_tree_lookup(db, "QUESMRK1");

*/

/*
///////////////////////////////////////////////////////////////////////////////////
                //      Maybe print some debug???  Todo fix this
                if(0 && (r->razRule->definition.SYDF == 'V'))
                {
                        wxLogMessage("\n..Vector Symbol used");
                        wxLogMessage("...Feature Class: %s", LUP->OBCL);
                        wxLogMessage("...iOBJL        : %d", pObj->iOBJL);
                        wxLogMessage("...Feature Attributes:");


                        //      Show the Object Attributes
                        char *currATT  = (char *)(pObj->attList->c_str());
                        int   attIdx   = 0;

                        char pattr[40];
                        while(*currATT)
                        {
                                strncpy(pattr, currATT, 6);
                                pattr[6] = 0;




                                        S57attVal *v;
                                        v = (pObj->attVal->Item(attIdx));


                                        switch(v->valType){
                                           case OGR_INT:{                       // S57 attribute type 'E' enumerated, 'I' integer
                                                        int a = *(int*)(v->value);
                                                        wxLogMessage("......%s, (I) %d", pattr, a);

                                        break;
                                                  }

                                           case OGR_INT_LST:{   // S57 attribute type 'L' list: comma separated integer
                                                         int *b = (int*)v->value;

                                                         char buf[40];
                                                         sprintf(buf, "......%s, (L) ", pattr);
                                                         wxString pstr(buf);

                                                         while(*b)
                                                         {
                                                                 int a = *b;
                                                                 sprintf(buf, "%d,", a);
                                                                 pstr += wxString(buf);
                                                                 b++;
                                                         }
                                                         wxLogMessage(pstr);
                                        break;
                                                  }

                                           case OGR_REAL:{              // S57 attribute type'F' float
                                                        double a = *(double*)(v->value);
                                                        wxLogMessage("......%s, (F) %f", pattr, a);
                                        break;
                                                  }

                                           case OGR_STR:{                       // S57 attribute type'A' code string, 'S' text
                                                        char *c = (char *)v->value;             // Attribute from object
                                                        wxLogMessage("......%s, (A) %s", pattr, c);


                                        break;
                                                  }

                                           default:
                                                        break;
                                        }   //switch


                                 while(*currATT != '\037')
                                        currATT++;
                                 currATT++;

                                 ++attIdx;

                          }  //while  curATT





                        wxLogMessage("...LUP RCID     : %d", LUP->RCID);
                        wxLogMessage("...LUP ATTC:");

                        if(LUP->ATTCArray)
                        {
                                for (unsigned int i=0 ; i< LUP->ATTCArray->GetCount(); i++)
                                {
                                        wxString ats = LUP->ATTCArray->Item(i);
                                        wxLogMessage("........%s", ats.c_str());
                                }
                                wxLogMessage("...Symbol Name: %s", r->razRule->name.SYNM);
                        }
                }  // if printing debug


////////////////////////////////////////////////////////////////////////
*/



Rules *s52plib::StringToRules(char *str)
{
       Rules *top;
       Rules *last;

       Rules *r = (Rules*)calloc(1, sizeof(Rules));
       top = r;
       last = top;


       while (*str != '\0')
       {
           if(r->ruleType)              // in the loop, r has been used
           {
               r = (Rules*)calloc(1, sizeof(Rules));
               last->next = r;
               last = r;
           }


      // parse Symbology instruction in string

      // SHOWTEXT
            INSTRUCTION("TX",RUL_TXT_TX) SCANFWRD }

            INSTRUCTION("TE",RUL_TXT_TE) SCANFWRD }

      // SHOWPOINT

            if(0==strncmp("SY",str,2))
            {
                str+=3;
                r->ruleType = RUL_SYM_PT;
                r->INSTstr  = str;

                wxString key(str,8);

                r->razRule = (*_symb_sym)[key];

                if (r->razRule == NULL)
                        r->razRule = (*_symb_sym)["QUESMRK1"];

                SCANFWRD
            }


      // SHOWLINE
            INSTRUCTION("LS",RUL_SIM_LN) SCANFWRD }

            INSTRUCTION("LC",RUL_COM_LN)
                  wxString key(str,8);
                  r->razRule = (*_line_sym)[key];
                  if (r->razRule == NULL)
                    r->razRule = (*_symb_sym)["QUESMRK1"];
            SCANFWRD
            }

      // SHOWAREA
            INSTRUCTION("AC",RUL_ARE_CO) SCANFWRD }

            INSTRUCTION("AP",RUL_ARE_PA)
                    wxString key(str,8);
                    key += 'R';

                    r->razRule = (*_patt_sym)[key];
                    if (r->razRule == NULL)
                        r->razRule = (*_patt_sym)["QUESMRK1V"];
            SCANFWRD
            }

      // CALLSYMPROC

            if(0==strncmp("CS",str,2))
            {
                str+=3;
                r->ruleType = RUL_CND_SY;
                r->INSTstr  = str;

//      INSTRUCTION("CS",RUL_CND_SY)
                char stt[9];
                strncpy(stt, str, 8);
                stt[8] = 0;
                wxString index(stt);
                r->razRule = (*_cond_sym)[index];
                if (r->razRule == NULL)
                    r->razRule = (*_cond_sym)["QUESMRK1"];
                SCANFWRD
            }

      ++str;
   }

//  If it should happen that no rule is built, delete the initially allocated rule

   if(0 == top->ruleType)
    {
        free(top);
        top = NULL;
    }


   return top;
}




int s52plib::_LUP2rules(LUPrec *LUP, S57Obj *pObj)
{
   // check if already parsed
   if (LUP->ruleList != NULL)
   {
      //printf("S52parser:_LUP2rules(): rule list already existe for %s\n", LUP->OBCL);
      return 0;
   }

   if(LUP->INST != NULL)
   {
        char  *str  = (char *)(LUP->INST->c_str());
        Rules *top  = StringToRules(str);
        LUP->ruleList = top;

        return 1;
   }
   else
        return 0;
}



//-------------------------
//
// S52 PARSER SECTION
//
//-------------------------

// MAX_BUF == 1024 --for buffer overflow
#define ENDLN   "%1024[^\037]"
#define NEWLN  "%1024[^\n]"

int s52plib::_readS52Line( char *pBuffer, char *delim, int nCount, FILE *fp )
{
   int ret;

   ret =  fscanf( fp, delim, pBuffer);

   fgetc(fp);

   if (nCount)  // skip \n
      fgetc(fp);

   return ret;
}


int s52plib::_chopS52Line(char *pBuffer, char c)
{
   int i;

   for (i=0; pBuffer[i] != '\0'; ++i)
      if ( pBuffer[i] == '\037' )
         pBuffer[i] = c;

   return i;
}

int s52plib::_parsePos(position *pos, char *buf, bool patt)
{
   if (patt){
      sscanf(buf,"%5d%5d",&pos->minDist.PAMI,&pos->maxDist.PAMA);
      //printf("sscanf test:%d %d %s\n",pos->minDist.PAMI, pos->maxDist.PAMA, buf);
      buf += 10;
   }

   sscanf(buf, "%5d%5d%5d%5d%5d%5d",&pos->pivot_x.PACL,&pos->pivot_y.PARW,
                                                                &pos->bnbox_w.PAHL,&pos->bnbox_h.PAVL,
                                    &pos->bnbox_x.PBXC,&pos->bnbox_y.PBXR);
   return 1;
}


int s52plib::_parseLBID(FILE *fp)
{
   return 0;
}

int s52plib::_parseCOLS(FILE *fp)
{
   int ret;
   //colTable ct;
   colTable *ct = new colTable;

   // get color table name
    _chopS52Line( pBuf, '\0' );

   ct->tableName = new wxString(pBuf+19);
   ct->color     = new wxArrayPtrVoid;

   _colTables->Add((void *)ct);
   n_colTables++;

   // read color
   ret  = _readS52Line( pBuf, NEWLN, 0,fp);
   while ( 0 != strncmp(pBuf, "****",4)){
      color *c = new color;
      _chopS52Line( pBuf, ' ' );
      strncpy(c->colName, pBuf+9, 5);
      sscanf(pBuf+14,"%f %f %f",&c->x,&c->y,&c->L);


      ct->color->Add(c);
      ret  = _readS52Line( pBuf, NEWLN, 0,fp);
   }
   return ret;
}


#define MOD_REC(str)    if(0==strncmp(#str,pBuf,4))
int s52plib::_parseLUPT(FILE *fp)
{
   int    ret;

   BOOL    inserted = FALSE;

   LUPrec  *LUP = (LUPrec*)calloc(1, sizeof(LUPrec));
   pAlloc->Add(LUP);

   LUP->DISC = (enum _DisCat)OTHER;                                     // as a default

   sscanf(pBuf+11, "%d", &LUP->RCID);

//   if(LUP->RCID == 793)
//      int uuip = 8;

   strncpy(LUP->OBCL, pBuf+19, 6);

//   if(!strncmp(LUP->OBCL, "TSSLPT", 6))
//         int qewr = 9;

   LUP->FTYP = (enum _Object_t)pBuf[25];
   LUP->DPRI = (enum _DisPrio)pBuf[30];
   LUP->RPRI = (enum _RadPrio)pBuf[31];
   LUP->TNAM = (enum _LUPname)pBuf[36];

   ret  = _readS52Line( pBuf, NEWLN, 0,fp);

   do{
      MOD_REC(ATTC){
         if ('\037' != pBuf[9])                                         // could be empty!
                 {

                        wxArrayString *pAS = new wxArrayString();
                        char *p = &pBuf[9];


                        wxString *st1 = new wxString;

                        while(*p)
                        {
                                while(*p != 0x1f)
                                {
                                  st1->Append(*p);
                                  p++;
                                }

                                pAS->Add(*st1);
                                st1->Clear();
                                p++;
                        }

                        delete st1;

                        LUP->ATTCArray = pAS;

            _chopS52Line( pBuf, ' ' );
            LUP->ATTC = new wxString(pBuf+9);                   //g_string_new(pBuf+9);



                 }
      }

      MOD_REC(INST) LUP->INST = new wxString(pBuf+9);   //g_string_new(pBuf+9);
      MOD_REC(DISC) LUP->DISC = (enum _DisCat)pBuf[9];
      MOD_REC(LUCM) sscanf(pBuf+9, "%d",&LUP->LUCM);

      MOD_REC(****){
/*
//                      wxString key((symb->name.SYNM), 8);
         // create unique key
         key = new wxString(LUP->OBCL);                                 //g_string_new(LUP->OBCL);
         if (LUP->ATTC)
            key->Append(LUP->ATTC->c_str());                                            //key = g_string_append(key, LUP->ATTC->str);

         // check if key already there
         LUPtype = _selectLUP(LUP->TNAM);
//         LUPtmp  = (LUPrec*)g_tree_lookup(LUPtype,(gpointer*)key);
//       LUPHash::iterator it;
//               it = LUPtype->find(*key);
//               LUPtmp = it->second;

                 LUPtmp  = (*LUPtype)[*key];                                            //(LUPrec*)g_tree_lookup(LUPtype,(gpointer*)key);

         // insert in BTree
         if (NULL == LUPtmp)
//            g_tree_insert(LUPtype, (gpointer*)key, (gpointer*)LUP);
            (*LUPtype)[*key] = LUP;                                                     //g_tree_insert(LUPtype, (gpointer*)key, (gpointer*)LUP);
         else{
            printf("ERROR LUP key not unique: %s",key->c_str());
//            g_assert_not_reached(); // should not reach this --ALL STOP
                        assert(0);

         }
 */

        // Add LUP to array
                 wxArrayOfLUPrec *pLUPARRAYtyped = SelectLUPARRAY(LUP->TNAM);

        // Search the LUPArray to see if there is already a LUP with this RCID
        // If found, replace it with the new LUP
        // This provides a facility for updating the LUP tables after loading a basic set


                unsigned int index = 0;

                while(index < pLUPARRAYtyped->GetCount())
                {
                        LUPrec *pLUPCandidate = pLUPARRAYtyped->Item(index);
                        if(LUP->RCID == pLUPCandidate->RCID)
                        {
                                DestroyLUP(pLUPCandidate);                              // empties the LUP
                                pLUPARRAYtyped->Remove(pLUPCandidate);
                                break;
                        }
                        index++;
                }


                pLUPARRAYtyped->Add(LUP);

          inserted = TRUE;

      }         // MOD_REC

      //if (!inserted)
         ret = _readS52Line( pBuf, NEWLN, 0,fp);
         //_chopS52Line( pBuf, '\0' );

   }while(inserted == FALSE);

   return 1;
}


int s52plib::_parseLNST(FILE *fp)
{
   int  ret;

   BOOL inserted = FALSE;
   Rule *lnstmp  = NULL;
   Rule *lnst = (Rule*)calloc(1, sizeof(Rule));         //g_malloc0(sizeof(Rule));
   pAlloc->Add(lnst);

   lnst->exposition.LXPO = new wxString;                        //g_string_new('\0');
   lnst->vector.LVCT     = new wxString;                        //g_string_new('\0');
   lnst->colRef.LCRF     = new wxString;

   sscanf(pBuf+11, "%d", &lnst->RCID);

   ret  = _readS52Line( pBuf, NEWLN, 0,fp);
   do{
      MOD_REC(LIND){
         strncpy(lnst->name.LINM, pBuf+9, 8); // could be empty!
         _parsePos(&lnst->pos.line, pBuf+17, FALSE);
      }

      MOD_REC(LXPO) lnst->exposition.LXPO->Append(pBuf+9 );
      MOD_REC(LCRF) lnst->colRef.LCRF->Append( pBuf+9);         //strcpy(lnst->colRef.LCRF,pBuf+9);     // CIDX + CTOK
      MOD_REC(LVCT) lnst->vector.LVCT->Append( pBuf+9 );
        MOD_REC(****){
         // check if key already there
                        wxString key((lnst->name.LINM), 8);
//               lnstmp  = (Rule*)g_tree_lookup(_line_sym,(gpointer*)lnst->name.LINM);
                 lnstmp  = (*_line_sym)[key];

         // insert in Hash Table
                if(NULL == lnstmp)
                        (*_line_sym)[key] = lnst;
                else if(lnst->name.LINM != lnstmp->name.LINM)
                        (*_line_sym)[key] = lnst;
        else
            assert(0); // key must be unique --should not reach this

         inserted = TRUE;
      }
      ret  = _readS52Line( pBuf, NEWLN, 0,fp);
      _chopS52Line( pBuf, '\0' );
   }while( inserted == FALSE);

   return ret;
}


void DestroyPatternRuleNode(Rule *pR);

int s52plib::_parsePATT(FILE *fp)
{
   int  ret;

   int bitmap_width;
   char pbm_line[200];                  // max bitmap width...
   BOOL inserted = FALSE;
   Rule *pattmp  = NULL;
   Rule *patt = (Rule*)calloc(1,sizeof(Rule));
   pAlloc->Add(patt);

   patt->exposition.PXPO  = new wxString;               //g_string_new('\0');
   patt->vector.PVCT      = new wxString;               //g_string_new('\0');
   patt->colRef.PCRF      = new wxString;
   patt->bitmap.PBTM     = new wxString;

   sscanf(pBuf+11, "%d", &patt->RCID);

   ret  = _readS52Line( pBuf, NEWLN, 0,fp);

   do{
      MOD_REC(PATD){
                strncpy(patt->name.PANM, pBuf+9, 8);
            patt->definition.PADF = pBuf[17];
            patt->fillType.PATP  = pBuf[18];
            patt->spacing.PASP   = pBuf[21];
            _parsePos(&patt->pos.patt, pBuf+24, TRUE);
      }

      MOD_REC(PXPO) patt->exposition.PXPO->Append( pBuf+9 );
      MOD_REC(PCRF) patt->colRef.PCRF->Append( pBuf+9 ); //strcpy(patt->colRef.PCRF,pBuf+9); // CIDX+CTOK
      MOD_REC(PVCT) patt->vector.PVCT->Append( pBuf+9 );

      MOD_REC(PBTM){
                bitmap_width = patt->pos.patt.bnbox_w.SYHL;
                if(bitmap_width > 200)
                        wxLogMessage("ParsePatt....bitmap too wide.");
                strncpy(pbm_line, pBuf+9, bitmap_width);
                pbm_line[bitmap_width] = 0;
                patt->bitmap.SBTM->Append( pbm_line );
        }






      MOD_REC(****){

         // check if key already there
         wxString key((patt->name.PANM), 8);
         key += wxString(patt->definition.SYDF, 1);

         pattmp  = (*_patt_sym)[key];

         if (NULL == pattmp)                    // not there, so....
            (*_patt_sym)[key] = patt;           // insert in hash table


         else                                   // already something here with same key...
         {
             if(patt->name.PANM != pattmp->name.PANM)   // if the pattern names are not identical
             {
                (*_patt_sym)[key] = patt;               // replace the pattern
                DestroyPatternRuleNode(pattmp);         // remember to free to replaced node
                                                        // the node itself is destroyed as part of pAlloc
             }

         }

         inserted = TRUE;
      }
      ret  = _readS52Line( pBuf, NEWLN, 0,fp);
      _chopS52Line( pBuf, '\0' );

   }while( inserted == FALSE);

   return ret;
}


void DestroyRuleNode(Rule *pR);

int s52plib::_parseSYMB(FILE *fp, RuleHash *pHash)
{
   int  ret;

   int bitmap_width;
   char pbm_line[200];                  // max bitmap width...
   BOOL inserted = FALSE;
//   Rule *symbtmp  = NULL;
   Rule *symb = (Rule*)calloc(1,sizeof(Rule));
   pAlloc->Add(symb);
   Rule *symbtmp = NULL;

   symb->exposition.SXPO = new wxString;                        //g_string_new('\0');
   symb->vector.SVCT     = new wxString;                        //g_string_new('\0');
   symb->bitmap.SBTM     = new wxString;
   symb->colRef.SCRF     = new wxString;

   sscanf(pBuf+11, "%d", &symb->RCID);

   // debug
 //  if (symb->RCID == 9504)
//              int gghj = 5;

   ret  = _readS52Line( pBuf, NEWLN, 0,fp);

   do{
      MOD_REC(SYMD){
                strncpy(symb->name.SYNM, pBuf+9, 8);
            symb->definition.SYDF = pBuf[17];
            _parsePos(&symb->pos.symb, pBuf+18, FALSE);
        }

      MOD_REC(SXPO) symb->exposition.SXPO->Append( pBuf+9 );

        MOD_REC(SBTM){
                bitmap_width = symb->pos.symb.bnbox_w.SYHL;
                if(bitmap_width > 200)
                        wxLogMessage("ParseSymb....bitmap too wide.");
                strncpy(pbm_line, pBuf+9, bitmap_width);
                pbm_line[bitmap_width] = 0;
                symb->bitmap.SBTM->Append( pbm_line );
        }

      MOD_REC(SCRF)     symb->colRef.SCRF->Append( pBuf+9 );  //strcpy(symb->colRef.SCRF, pBuf+9); // CIDX+CTOK

      MOD_REC(SVCT) symb->vector.SVCT->Append( pBuf+9 );

          if((0==strncmp("****",pBuf,4)) || (ret == -1)){
//      MOD_REC(****){

                // Create a key
                wxString key((symb->name.SYNM), 8);
//              key += wxString(symb->definition.SYDF, 1);

        // check if key already there
//                RuleHash::iterator it = pHash->find(key);

//                if(it == pHash->end())
//                        (*pHash)[key] = symb;                           // key not found, so insert


                 symbtmp  = (*pHash)[key];

                 if (NULL == symbtmp)                    // not there, so....
                    (*pHash)[key] = symb;           // insert in hash table


                 else                                   // already something here with same key...
                 {
                    if(symb->name.SYNM != symbtmp->name.SYNM)   // if the pattern names are not identical
                    {
                        (*pHash)[key] = symb;                    // replace the pattern
                        DestroyRuleNode(symbtmp);         // remember to free to replaced node
                                                         // the node itself is destroyed as part of pAlloc
                    }

                 }



         inserted = TRUE;
      }
      ret  = _readS52Line( pBuf, NEWLN, 0,fp);
//        if(ret <= 0)
//                int ffg = 5;
      _chopS52Line( pBuf, '\0' );

   }while( inserted == FALSE );

   return ret;
}



//-------------------------
//
// MAIN SECTION
//
//-------------------------
#ifndef _COMPARE_LUP_DEFN_
#define _COMPARE_LUP_DEFN_
//-----------------------------------------------------------------------------
//      Comparison Function for LUPArray sorting
//      Note Global Scope
//-----------------------------------------------------------------------------
int CompareLUPObjects(LUPrec *item1, LUPrec *item2)
{
    // sort the items by their name...
    int ir = Stricmp(item1->OBCL, item2->OBCL);
        if(ir == 0)
                return item1->RCID - item2->RCID;
        else
                return ir;
}

#endif

int s52plib::S52_load_Plib(const wxString& PLPath, const wxString& PLLib, const wxString& PLCol)
{

        //      Build file names
        wxString PLib(PLPath);
        PLib += PLLib;

        wxString PCol(PLPath);
        PCol += PLCol;

   FILE *fp = NULL;
   int  nRead;


   fp = fopen(PLib.c_str(), "r");

   if (fp == NULL)
   {
       wxLogMessage("S52PLIB: Cannot open S52 rules file: %s", PLib.c_str());
      return 0;
   }

//   _colTables         = g_array_new(FALSE,FALSE, sizeof(colTable));
   _colTables = new wxArrayPtrVoid;

/*
   _table[S52_LUP_LINE]     = _lineLUP       = g_tree_new(_compareLUP); // lines
   _table[S52_LUP_AREA_PLN] = _areaPlaineLUP = g_tree_new(_compareLUP); // areas: PLAIN_BOUNDARIES
   _table[S52_LUP_AREA_SYM] = _areaSymbolLUP = g_tree_new(_compareLUP); // areas: SYMBOLIZED_BOUNDARIE
   _table[S52_LUP_PT_SIMPL] = _pointSimplLUP = g_tree_new(_compareLUP); // points: SIMPLIFIED
   _table[S52_LUP_PT_PAPER] = _pointPaperLUP = g_tree_new(_compareLUP); // points: PAPER_CHART

   _table[S52_LINE_SYM]     = _line_sym      = g_tree_new(_compareRules);       // line
   _table[S52_PATT_SYM]     = _patt_sym      = g_tree_new(_compareRules);       // pattern
   _table[S52_SYMB_SYM]     = _symb_sym      = g_tree_new(_compareRules);       // symbol
   _table[S52_COND_SYM]     = _cond_sym      = g_tree_new(_compareRules);       // conditional
*/
/*
   _table[S52_LUP_LINE]     = _lineLUP       = new LUPHash;     // lines
   _table[S52_LUP_AREA_PLN] = _areaPlaineLUP = new LUPHash;     // areas: PLAIN_BOUNDARIES
   _table[S52_LUP_AREA_SYM] = _areaSymbolLUP = new LUPHash;     // areas: SYMBOLIZED_BOUNDARIE
   _table[S52_LUP_PT_SIMPL] = _pointSimplLUP = new LUPHash;     // points: SIMPLIFIED
   _table[S52_LUP_PT_PAPER] = _pointPaperLUP = new LUPHash;     // points: PAPER_CHART
*/
   _table[S52_LINE_SYM]     = _line_sym      = new RuleHash;    // line
   _table[S52_PATT_SYM]     = _patt_sym      = new RuleHash;    // pattern
   _table[S52_SYMB_SYM]     = _symb_sym      = new RuleHash;    // symbol
   _table[S52_COND_SYM]     = _cond_sym      = new RuleHash;    // conditional

//      Sorted Arrays of LUPrecs
   LUPTable[S52_LUPARRAY_LINE]      = new wxArrayOfLUPrec(CompareLUPObjects);   // lines
   LUPTable[S52_LUPARRAY_AREA_PLN]  = new wxArrayOfLUPrec(CompareLUPObjects);   // area plain boundary
   LUPTable[S52_LUPARRAY_AREA_SYM]  = new wxArrayOfLUPrec(CompareLUPObjects);   // area symbolized boundary
   LUPTable[S52_LUPARRAY_PT_SIMPL]  = new wxArrayOfLUPrec(CompareLUPObjects);   // point simplified
   LUPTable[S52_LUPARRAY_PT_PAPER]  = new wxArrayOfLUPrec(CompareLUPObjects);   // point traditional(paper)
   LUPTable[S52_LUPARRAY_COND_SYM]  = new wxArrayOfLUPrec(CompareLUPObjects);   // dynamic Cond Sym LUPs

     // set up some direct pointer as shortcuts
     pointSimplLUPArray    = (wxArrayOfLUPrec *)LUPTable[S52_LUPARRAY_PT_SIMPL];
     pointPaperLUPArray    = (wxArrayOfLUPrec *)LUPTable[S52_LUPARRAY_PT_PAPER];
     lineLUPArray          = (wxArrayOfLUPrec *)LUPTable[S52_LUPARRAY_LINE];
     areaPlaineLUPArray    = (wxArrayOfLUPrec *)LUPTable[S52_LUPARRAY_AREA_PLN];
     areaSymbolLUPArray    = (wxArrayOfLUPrec *)LUPTable[S52_LUPARRAY_AREA_SYM];
     condSymbolLUPArray    = (wxArrayOfLUPrec *)LUPTable[S52_LUPARRAY_COND_SYM];


        while( 1 == (nRead = _readS52Line(pBuf,NEWLN,0,fp)) ){
      // !!! order important !!!
      MOD_REC(LBID) _parseLBID(fp);
      MOD_REC(COLS) _parseCOLS(fp);
      MOD_REC(LUPT) _parseLUPT(fp);
      MOD_REC(LNST) _parseLNST(fp);
      MOD_REC(PATT) _parsePATT(fp);
      MOD_REC(SYMB) _parseSYMB(fp, _symb_sym);

      MOD_REC(0001) continue;
      MOD_REC(****) continue;

   }
   fclose(fp);

   _loadCondSymb();

//   _CIE2RGB();

   LoadColors((char *)PCol.c_str());
//      RGBFROMDAT();

        /*

   _table_size[S52_LUP_LINE]    = g_tree_nnodes(_lineLUP);      // lines
   _table_size[S52_LUP_AREA_PLN] = g_tree_nnodes(_areaPlaineLUP);       // areas: PLAIN_BOUNDARIES
   _table_size[S52_LUP_AREA_SYM] = g_tree_nnodes(_areaSymbolLUP);       // areas: SYMBOLIZED_BOUNDARIE
   _table_size[S52_LUP_PT_SIMPL] = g_tree_nnodes(_pointSimplLUP);       // points: SIMPLIFIED
   _table_size[S52_LUP_PT_PAPER] = g_tree_nnodes(_pointPaperLUP);       // points: PAPER_CHART

   _table_size[S52_LINE_SYM]     = g_tree_nnodes(_line_sym);    // line
   _table_size[S52_PATT_SYM]     = g_tree_nnodes(_patt_sym);    // pattern
   _table_size[S52_SYMB_SYM]     = g_tree_nnodes(_symb_sym);    // symbol
   _table_size[S52_COND_SYM]     = g_tree_nnodes(_cond_sym);    // conditional



   */
   return 1;                    //_table_size;
}

//
//      S52_Load_Plib_Ext
//
//      Load any extensions to the presentation library, especially symbols and patterns
//
//      Extensions are loaded from separate files, each containing one item.
//      Files are specified by caller

int s52plib::S52Load_Plib_Ext(char *pPLPath, char *pPLExtensionDir, char *pPLExtensionType)
{
        //      Build a list of the files requested
        wxString PLibDir(pPLPath);
        PLibDir += wxString(pPLExtensionDir);

    wxDir dir(PLibDir);

    if ( !dir.IsOpened() )
    {
//              wxLogMessage("S52Plib Load Extensions: Dir %s not found.", PLibDir);
        return 0;
    }

    wxString filename;
        wxString filespec("*.");
        filespec += wxString(pPLExtensionType);

        //      Iterate over the directory, picking out the required file types
        wxArrayString *pFileList = new wxArrayString();

        dir.GetAllFiles(PLibDir,pFileList, filespec);


        _symb_symR = new RuleHash;              // symbol table, Raster

        //      Process the file list
        for(unsigned int j=0 ; j<pFileList->GetCount() ; j++)
        {
                wxFileName file(pFileList->Item(j));

                FILE *fp = NULL;
                int  nRead;

//              wxLogMessage("%s",(file.GetFullPath()).c_str());
                fp = fopen((file.GetFullPath()).c_str(), "r");

                if (fp == NULL)
                        continue;

                while( 1 == (nRead = _readS52Line(pBuf,NEWLN,0,fp)) )
                {
      // !!! order important !!!
//                      MOD_REC(LBID) _parseLBID(fp);
//                      MOD_REC(COLS) _parseCOLS(fp);
//                      MOD_REC(LUPT) _parseLUPT(fp);
//                      MOD_REC(LNST) _parseLNST(fp);
//                      MOD_REC(PATT) _parsePATT(fp);
                        MOD_REC(SYMB) _parseSYMB(fp, _symb_symR);

//                      MOD_REC(0001) continue;
//                      MOD_REC(****) continue;

                }

                fclose(fp);


        }

        pFileList->Clear();
        delete pFileList;

        return 1;
}

//
//      S52_flush_Plib(): clean-up
//

void DestroyPatternRuleNode(Rule *pR)
{
    if(pR)
    {
            if(pR->exposition.LXPO)
                    delete pR->exposition.LXPO;

            if(pR->vector.LVCT)
                    delete pR->vector.LVCT;

            if(pR->bitmap.SBTM)
                    delete pR->bitmap.SBTM;

            if(pR->colRef.SCRF)
                    delete pR->colRef.SCRF;

            if(pR->pixelPtr)
            {
                if(pR->definition.PADF == 'V')
                {
                    wxBitmap *pbm = (wxBitmap *)(pR->pixelPtr);
                    delete pbm;
                }
                else if(pR->definition.PADF == 'R')
                {
                    render_canvas_parms *pp = (render_canvas_parms *)(pR->pixelPtr);
#ifdef S57USE_PIXELCACHE
                    PixelCache *pPC = (PixelCache *)pp->PCPtr;
                    delete pPC;
#else
                    free(pp->pix_buff);
#endif
                    delete pp;
                }
            }
    }
}


void DestroyRuleNode(Rule *pR)
{
    if(pR)
    {

        if(pR->exposition.LXPO)
            delete pR->exposition.LXPO;
        if(pR->vector.LVCT)
            delete pR->vector.LVCT;
        if(pR->bitmap.SBTM)
            delete pR->bitmap.SBTM;
        if(pR->colRef.SCRF)
            delete pR->colRef.SCRF;
        if(pR->pixelPtr)
        {
            if(pR->definition.PADF == 'R')
            {
                wxBitmap *pbm = (wxBitmap *)(pR->pixelPtr);
                delete pbm;
            }
        }
    }
}


void DestroyRules(RuleHash *rh)
{

    RuleHash::iterator it;
        wxString key;
        Rule *pR;

        for( it = (*rh).begin(); it != (*rh).end(); ++it )
    {
        key = it->first;
        pR = it->second;
        if(pR)
        {

            if(pR->exposition.LXPO)
                delete pR->exposition.LXPO;
            if(pR->vector.LVCT)
                delete pR->vector.LVCT;
            if(pR->bitmap.SBTM)
                delete pR->bitmap.SBTM;
            if(pR->colRef.SCRF)
                delete pR->colRef.SCRF;

            if(pR->pixelPtr)
            {
                if(pR->definition.PADF == 'R')
                {
                    wxBitmap *pbm = (wxBitmap *)(pR->pixelPtr);
                    delete pbm;
                }
            }
        }
    }

        rh->clear();
        delete rh;
}




void DestroyPattRules(RuleHash *rh)
{

    RuleHash::iterator it;
        wxString key;
        Rule *pR;

        for( it = (*rh).begin(); it != (*rh).end(); ++it )
    {
        key = it->first;
                pR = it->second;
                if(pR)
                {
                        if(pR->exposition.LXPO)
                                delete pR->exposition.LXPO;

                        if(pR->vector.LVCT)
                                delete pR->vector.LVCT;

                        if(pR->bitmap.SBTM)
                                delete pR->bitmap.SBTM;

                        if(pR->colRef.SCRF)
                                delete pR->colRef.SCRF;

                        if(pR->pixelPtr)
                        {
                            if(pR->definition.PADF == 'V')
                            {
                                wxBitmap *pbm = (wxBitmap *)(pR->pixelPtr);
                                delete pbm;
                            }
                            else if(pR->definition.PADF == 'R')
                            {
                                render_canvas_parms *pp = (render_canvas_parms *)(pR->pixelPtr);
#ifdef S57USE_PIXELCACHE
                                PixelCache *pPC = (PixelCache *)pp->PCPtr;
                                delete pPC;
#else
                                free(pp->pix_buff);
#endif
                                delete pp;
                            }
                        }
                }

    }

        rh->clear();
        delete rh;
}

void s52plib::DestroyLUP(LUPrec *pLUP)
{
        Rules  *top = pLUP->ruleList;

        while(top != NULL)
        {
            Rules *Rtmp = top->next;
            free(top);
            top = Rtmp;
        }

        delete pLUP->ATTCArray;

        delete pLUP->ATTC;
        delete pLUP->INST;
}


void s52plib::DestroyLUPArray(wxArrayOfLUPrec *pLUPArray)
{
        for(unsigned int il = 0 ; il < pLUPArray->GetCount() ; il++)
                DestroyLUP(pLUPArray->Item(il));

        pLUPArray->Clear();

        delete pLUPArray;
}

bool s52plib::S52_flush_Plib()
{

//      Color Tables
        for(unsigned int ic = 0 ; ic < _colTables->GetCount() ; ic++)
        {
           colTable *ct = (colTable *)_colTables->Item(ic);

                delete ct->tableName;
                for(unsigned int icc = 0 ; icc < ct->color->GetCount() ; icc++)
                {
                   delete (color *)(ct->color->Item(icc));
                }

                delete ct->color;
                delete ct;
        }


        delete _colTables;

   // destroy look-up tables
        DestroyLUPArray(lineLUPArray);
        DestroyLUPArray(pointSimplLUPArray);
        DestroyLUPArray(pointPaperLUPArray);
        DestroyLUPArray(areaPlaineLUPArray);
        DestroyLUPArray(areaSymbolLUPArray);
        DestroyLUPArray(condSymbolLUPArray);

//      Destroy Rules
        DestroyRules(_line_sym);
        DestroyPattRules(_patt_sym);
        DestroyRules(_symb_sym);

        if(_symb_symR)
                DestroyRules(_symb_symR);

//      Special case for CS
    RuleHash::iterator it;
        Rule *pR;
        for( it = (*_cond_sym).begin(); it != (*_cond_sym).end(); ++it )
    {
                pR = it->second;
//              delete pR;
    }
        delete  (_cond_sym);


        for(unsigned int ipa = 0 ; ipa < pAlloc->GetCount() ; ipa++)
        {
                void *t = pAlloc->Item(ipa);
                free(t);
        }

        delete pAlloc;

        return TRUE;
}



LUPrec *s52plib::S52_lookupA(S52_LUP_table_t table_t, const char * objectName, S57Obj *pObj, bool bStrict)

{
   LUPrec *LUP = NULL;
        LUPrec *LUPCandidate;


        nameMatch = new wxArrayPtrVoid;

        wxArrayOfLUPrec *la = (wxArrayOfLUPrec *)(LUPTable[table_t]);
        int ocnt = 0;

        int first_match = 0;
        int index = 0;
        int index_max = la->GetCount();

        while(!first_match && (index < index_max))
        {
                LUPCandidate = la->Item(index);
                if(!strcmp(objectName, LUPCandidate->OBCL))
                {
                        first_match = 1;
                        ocnt++;
                        nameMatch->Add(LUPCandidate);
                        index++;
                        break;
                }
                index++;
        }


        while(first_match && (index < index_max))
        {
                LUPCandidate = la->Item(index);
                if(!strcmp(objectName, LUPCandidate->OBCL))
                {
                        ocnt++;
                        nameMatch->Add(LUPCandidate);
                }
                else
                {
                        break;
                }

                index++;
        }



        if(ocnt == 0)
                goto BAILOUT;

   LUP = _findFromATT(nameMatch,(char *)pObj->attList->c_str(), pObj->attVal, bStrict);


BAILOUT:
   nameMatch->Clear();

   delete nameMatch;

   return LUP;
}





void s52plib::SetColorScheme(Col_Scheme_t c)
{
    //      Only use available color schemes
    if((int)c > (n_colTables - 1))
        m_ColorScheme = (Col_Scheme_t)(n_colTables - 1);
    else
        m_ColorScheme = c;
}



color *s52plib::S52_getColor(char *colorName)
{
   color *c;

   unsigned int i;
   colTable *ct;

   ct = (colTable *)_colTables->Item(m_ColorScheme);

   for (i=0; i<ct->color->GetCount(); ++i){

           c = (_color *)ct->color->Item(i);
      if (0 == strncmp(colorName, c->colName, 5))
         return c;
   }

/*
   c = &g_array_index(ct->color, color, 1);
   printf("S52:S52_getColor(): ERROR no color name: %s\n",colorName);
*/
   return c;
}


//----------------------------------------------------------------------------------
//
//              Object Rendering Module
//
//----------------------------------------------------------------------------------


//-----------------------------
//
// S52 TEXT COMMAND WORD PARSER
//
//-----------------------------
#define APOS   '\047'
#define MAXL       256

wxString GetStringAttr(S57Obj *obj, char *AttrName)
{
        wxString str;
        char *attList = (char *)(obj->attList->c_str());        //attList is wxString

        char *patl = attList;
        char *patr;
        int idx = 0;
        while(*patl)
        {
                patr = patl;
                while(*patr != '\037')
                        patr++;

                if(!strncmp(patl, AttrName, 6))
                        break;

                patl = patr + 1;
                idx++;
        }

        if(!*patl)
                return str;

//      using idx to get the attribute value
        wxArrayOfS57attVal      *pattrVal = obj->attVal;

        S57attVal *v = pattrVal->Item(idx);

        char *val = (char *)(v->value);

        str.Append(val);

        return str;
}

bool GetFloatAttr(S57Obj *obj, char *AttrName, float &val)
{
    char *attList = (char *)(obj->attList->c_str());        //attList is wxString

    char *patl = attList;
    char *patr;
    int idx = 0;
    while(*patl)
    {
        patr = patl;
        while(*patr != '\037')
            patr++;

        if(!strncmp(patl, AttrName, 6))
            break;

        patl = patr + 1;
        idx++;
    }

    if(!*patl)                                                      // Requested Attribute not found
    {
        return false;                                           // so don't return a value
    }

//      using idx to get the attribute value
    wxArrayOfS57attVal      *pattrVal = obj->attVal;

    S57attVal *v = pattrVal->Item(idx);
    val = *(float*)(v->value);

    return true;
}



char      *_getParamVal(ObjRazRules *rzRules, char *str, char *buf, int bsz)
// Symbology Command Word Parameter Value Parser.
//
//      str: psz to Attribute of interest
//
//      Results:Put in 'buf' one of:
//  1- LUP constant value,
//  2- ENC value,
//  3- LUP default value.
// Return pointer to the next field in the string (delim is ','), NULL to abort
{
    char    *tmp    = buf;
    wxString value;
    int      defval = 0;    // default value
    int      len    = 0;

    // parse constant parameter with concatenation operator "'"
    if (str != NULL && *str == APOS){
        str++;
        while (*str != APOS){
            *buf++ = *str++;
        }
        *buf = '\0';
        str++;  // skip "'"
        str++;  // skip ","

        return str;
    }

    while (*str!=',' && *str!=')' && *str!='\0' /*&& len<bsz*/) {
        *tmp++ = *str++;
        ++len;
    }

    //if (len > bsz)
    //    printf("ERROR: chopping input S52 line !? \n");

    *tmp = '\0';
    str++;        // skip ',' or ')'

    if (len<6)
        return str;

    // chop string if default value present
    if (len > 6 && *(buf+6) == '='){
        *(buf+6) = '\0';
        defval = 1;
    }

        value = GetStringAttr(rzRules->obj,buf);
    if (value.IsNull()) {
        if (defval)
            _getParamVal(rzRules, buf+7, buf, bsz-7);    // default value --recursion
        else {
            // PRINTF("NOTE: skipping TEXT no value for attribute:%s\n", buf);
            return NULL;                        // abort
        }
    } else {
        int vallen = value.Len();

        if (vallen >= bsz) {
            vallen =  bsz;
//            PRINTF("ERROR: chopping attribut value !? \n");
        }

        // special case ENC return an index
// Todo Build static natsur character array
        if (0/*0==strncmp(buf, "NATSUR", 6)*/) {
//            int i = atoi(value.c_str());

//            if ( 0 < i && i <= MAX_NATSUR)
//                strcpy(buf, natsur[i]);


        } else {
            strncpy(buf, value.c_str(), vallen);            // value from ENC
            buf[vallen] = '\0';
        }
    }

    return str;
}



S52_Text  *_parseTEXT(ObjRazRules *rzRules, char *str0)
{
    S52_Text *text = NULL;
    char buf[MAXL] = {'\0'};   // output string

        char *str = str0;
    text = (struct _S52_Text *)calloc(sizeof(S52_Text),1);

    str = _getParamVal(rzRules, str, &text->hjust, 1);   // HJUST
    str = _getParamVal(rzRules, str, &text->vjust, 1);   // VJUST
    str = _getParamVal(rzRules, str, &text->space, 1);   // SPACE

    // CHARS
    str         = _getParamVal(rzRules, str, buf, 5);
    text->style = buf[0];
    text->weight= buf[1];
    text->width = buf[2];
    text->bsize = atoi(buf+3);

    str         = _getParamVal(rzRules, str, buf, MAXL);
    text->xoffs = atoi(buf);             // XOFFS
    str         = _getParamVal(rzRules, str, buf, MAXL);
    text->yoffs = atoi(buf);             // YOFFS
    str         = _getParamVal(rzRules, str, buf, MAXL);
    text->col   = ps52plib->S52_getColor(buf);  // COLOUR
    str         = _getParamVal(rzRules, str, buf, MAXL);
    text->dis   = atoi(buf);             // DISPLAY

    return text;
}


S52_Text   *S52_PL_parseTX(ObjRazRules *rzRules, Rules *rules, char *cmd)
{
    S52_Text *text = NULL;
    char *str      = NULL;
    char buf[MAXL] = {'\0'};   // output string
//    char arg[MAXL] = {'\0'};   // ATTRIB list
    char val[MAXL] = {'\0'};   // value of arg
//    char *parg = arg;
    char *b    = buf;


//    str  = _getParamVal(geoData, cmd->param, buf, MAXL);   // STRING
        str = (char*)rules->INSTstr;

        str = _getParamVal(rzRules, str, val, MAXL);   // get ATTRIB list
    if (NULL == str)
        return 0;   // abort this command word if mandatory param absent


        sprintf(b, "%s", val);

        text = _parseTEXT(rzRules, str);
    if (NULL != text)
        text->frmtd = new wxString(buf);

    return text;
}


S52_Text   *S52_PL_parseTE(ObjRazRules *rzRules, Rules *rules, char *cmd)
// same as S52_PL_parseTX put parse 'C' format first
{
    char arg[MAXL] = {'\0'};   // ATTRIB list
    char fmt[MAXL] = {'\0'};   // FORMAT
    char buf[MAXL] = {'\0'};   // output string
    char *b    = buf;
    char *parg = arg;
    char *pf   = fmt;
    S52_Text *text = NULL;
    char *str  = NULL;
    //char *str  = rules->INSTstr;


        str = (char*)rules->INSTstr;
    str = _getParamVal(rzRules, str, fmt, MAXL);   // get FORMAT

   str = _getParamVal(rzRules, str, arg, MAXL);   // get ATTRIB list
    if (NULL == str)
        return 0;   // abort this command word if mandatory param absent


    //*b = *pf;
    while (*pf != '\0') {

        // begin a convertion specification
        if (*pf == '%') {
            char val[MAXL] = {'\0'};   // value of arg
            char tmp[MAXL] = {'\0'};   // temporary format string
            char *t = tmp;
            int  cc        = 0;        // 1 == Conversion Character found
            //*t = *pf;

            // get value for this attribute
            parg = _getParamVal(rzRules, parg, val, MAXL);
            if (NULL == parg)
                return 0;   // abort

            if (0==strcmp(val, "2147483641"))
                return 0;

            *t = *pf;       // stuff the '%'

            // scan for end at convertion character
            do {
                *++t = *++pf;   // fill conver spec

                switch (*pf) {
                    case 'c':
                    case 's': b += sprintf(b, tmp, val);       cc = 1; break;
                    case 'f': b += sprintf(b, tmp, atof(val)); cc = 1; break;
                    case 'd':
                    case 'i': b += sprintf(b, tmp, atoi(val)); cc = 1; break;
                }
            } while (!cc);
            pf++;             // skip conv. char

        } else
            *b++ = *pf++;
    }

    text = _parseTEXT(rzRules, str);
    if (NULL != text)
        text->frmtd = new wxString(buf);

    return text;
}
/*

gint        S52_PL_getTEXT(S52_Text  *text, S52_Color **col,
                          int *xoffs, int *yoffs, char **str)
{
    *col   = text->col;
    *xoffs = text->xoffs;
    *yoffs = text->yoffs;
    *str   = text->frmtd->str;
    return 1;
}

gint        S52_PL_doneTXT(S52_Text *text)
{
    if (NULL != text->frmtd)
        g_string_free(text->frmtd, TRUE);
    g_free(text);

    return 1;
}

*/

void RenderText(wxDC *pdc, wxFont *pFont, char *str, int x, int y, int &dx, int &dy)
{
#ifdef DrawText
#undef DrawText
#define FIXIT
#endif


        wxFont oldfont = pdc->GetFont(); // save current font

        pdc->SetFont(*pFont);
        pdc->SetTextForeground(wxColour(255,255,255));
        pdc->SetBackgroundMode(wxTRANSPARENT);

        pdc->DrawText(str, x, y+1);
        pdc->DrawText(str, x, y-1);
        pdc->DrawText(str, x+1, y);
        pdc->DrawText(str, x-1, y);

        pdc->SetTextForeground(wxColour(0,0,0));

        pdc->DrawText(str, x, y);

        wxCoord w, h;
        pdc->GetTextExtent(str, &w, &h);       // measure the text

        pdc->SetFont(oldfont);                 // restore last font


        dx = w+2;                              // report text string size
        dy = h+2;

#ifdef FIXIT
#undef FIXIT
#define DrawText DrawTextA
#endif


}








// Text
int s52plib::_renderTX(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
        if(!m_bShowS57Text)
                return 0;

        S52_Text *text = NULL;

        wxPoint r;
//  if Object is area, Render text at centroid of BoundingBox
        if(rzRules->obj->Primitive_type == GEO_AREA)
        {
            float cent_lat, cent_lon;
            wxBoundingBox *bb = &(rzRules->obj->BBObj);

            cent_lat = ((bb->GetMinY()) + (bb->GetMaxY())) / 2;
            cent_lon = ((bb->GetMinX()) + (bb->GetMaxX())) / 2;

            rzRules->chart->GetPointPix(cent_lat, cent_lon, &r);

        }
        else
        {
            float xlon = rzRules->obj->x;
            float ylat = rzRules->obj->y;

            rzRules->chart->GetPointPix(ylat, xlon, &r);
        }


/*
        //      Create the formatted text string, and cache it in the object
        if(!rzRules->obj->FText)
        {
                text = S52_PL_parseTX(rzRules, rules, NULL);
                rzRules->obj->FText = text;
        }

        if(rzRules->obj->FText && bShowS57Text)
        {
                char *str = (char *)rzRules->obj->FText->frmtd->c_str();
                RenderText(rzRules->chart->pdc, pSmallFont, str,
                        r.x + rzRules->obj->FText->xoffs, r.y + rzRules->obj->FText->yoffs);
        }
*/

        int dx, dy;
        text = S52_PL_parseTX(rzRules, rules, NULL);
        if(text)
        {
                char *str = (char *)text->frmtd->c_str();
                RenderText(pdc, pSmallFont, str,
                        r.x + text->xoffs, r.y + text->yoffs, dx, dy);

                //  Update the object Bounding box if this object is a POINT object,
                //  so that subsequent drawing operations will redraw the item fully

                if(rzRules->obj->Primitive_type == GEO_POINT)
                {
                    double plat, plon;
                    rzRules->chart->pix_to_latlong(r.x + text->xoffs, r.y + text->yoffs + dy, &plat, &plon);
                    rzRules->obj->BBObj.SetMin(plon, plat);

                    rzRules->chart->pix_to_latlong(r.x + text->xoffs + dx, r.y + text->yoffs, &plat, &plon);
                    rzRules->obj->BBObj.SetMax(plon, plat);

                }

                delete text->frmtd;
                free(text);
        }

   return 1;
}


// Text formatted
int s52plib::_renderTE(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
        if(!m_bShowS57Text)
                return 0;

        S52_Text *text = NULL;

        wxPoint r;
//  if Object is area, Render text at centroid of BoundingBox
        if(rzRules->obj->Primitive_type == GEO_AREA)
        {
            float cent_lat, cent_lon;
            wxBoundingBox *bb = &(rzRules->obj->BBObj);

            cent_lat = ((bb->GetMinY()) + (bb->GetMaxY())) / 2;
            cent_lon = ((bb->GetMinX()) + (bb->GetMaxX())) / 2;

            rzRules->chart->GetPointPix(cent_lat, cent_lon, &r);

        }
        else
        {
            float xlon = rzRules->obj->x;
            float ylat = rzRules->obj->y;

            rzRules->chart->GetPointPix(ylat, xlon, &r);
        }


        int dx, dy;
        text = S52_PL_parseTE(rzRules, rules, NULL);
        if(text)
        {
                char *str = (char *)text->frmtd->c_str();
                RenderText(pdc, pSmallFont, str,
                        r.x + text->xoffs, r.y + text->yoffs, dx, dy);

                //  Update the object Bounding box if this object is a POINT object,
                //  so that subsequent drawing operations will redraw the item fully

                if(rzRules->obj->Primitive_type == GEO_POINT)
                {
                    double plat, plon;
                    rzRules->chart->pix_to_latlong(r.x + text->xoffs, r.y + text->yoffs + dy, &plat, &plon);
                    rzRules->obj->BBObj.SetMin(plon, plat);

                    rzRules->chart->pix_to_latlong(r.x + text->xoffs + dx, r.y + text->yoffs, &plat, &plon);
                    rzRules->obj->BBObj.SetMax(plon, plat);

                }


                delete text->frmtd;
                free(text);
        }

   return 1;
}


bool s52plib::RenderHPGL(Rule * rule_in, wxDC *pdc, wxPoint &r, float rot_angle)
{
//      static int _renderHPGL(gpointer key, gpointer value, gpointer data)
//{
   int width = 1;
   double radius = 0.0;
//   double sweepAngle;
//   double startAngle;
   int    tessObj       = FALSE;
   int    polyMode      = FALSE;
   int    inBegEnd      = FALSE;
   color *newColor;
   float trans = 1.0;

//   double centerX = 0.0;
//   double centerY = 0.0;

   int x1, x2, y1, y2;
   int x,y;

   float sin_rot, cos_rot;

   if(rot_angle)
   {
           sin_rot = sin(rot_angle * PI / 180.);
           cos_rot = cos(rot_angle * PI / 180.);
   }


#define MAX_POINTS 100
   wxPoint PointArray[MAX_POINTS];
   int vIdx;



//   double scaleFac = 300000.0;                        // fixme: should be computed
//   double scaleFac = 1.0/_degPix;                     // fixme: should be computed

//   struct _vertex{GLdouble x,y,z;}vertex;
//   struct _vertex vertexV[256];

   Rule *rule           = (Rule *)rule_in;
   char *str            = (char *)(rule->vector.LVCT->c_str()); //->str;
   char *col            = (char *)(rule->colRef.LCRF)->c_str();
//   int bbx            = rule->pos.line.bnbox_x.LBXC ;
//   int bby            = rule->pos.line.bnbox_y.LBXR ;
//   int w                      = rule->pos.line.bnbox_w.LIHL / scaleFac;
//   int h                      = rule->pos.line.bnbox_h.LIVL / scaleFac;
   int pivot_x  = rule->pos.line.pivot_x.LICL;
   int pivot_y  = rule->pos.line.pivot_y.LIRW;

   //printf("Symb:%s bbx:%d bby:%d\n",rule->name.LINM,bbx,bby);

   int scaleFac =25;            // todo where does this come from?
   float fsf = 100 / canvas_pix_per_mm;
   scaleFac = (int)floor(fsf);


/*
   if (createTexture){
      glBindTexture(GL_TEXTURE_2D,*crntTextName);
      //glBindTexture(GL_TEXTURE_2D,1);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   }else{
      glNewList(listIndex, GL_COMPILE);
      glScaled(1.0,-1.0,1.0);                                   // flip coordinated in Y
   }

   //printf("pivot_x:%d pivot_y:%d\n", pivot_x,pivot_y);
*/

#define INST(cmd)               if(0==strncmp(str,#cmd,2)) {str+=2;

   while (*str != '\0'){

      // Select (Pen) color
      INST(SP)
//         GET_COL()
                                {
               char *c=col;
               while(*c != '\0'){
                  if( *c == *str)
                     break;
                  else
                     c+=6;
               }
               newColor =  S52_getColor(c+1);
            }
      }

      // Select Transparency
      else INST(ST)
         trans = atof(str);
         trans = (trans == 0)? 1 : trans*0.25;

         //test
         trans = 1.0;
      }

      // Select pen Width
      else INST(SW)
         width = atoi(str++);

         if (inBegEnd){
             wxLogMessage("bogus BegEnd in SW");
            inBegEnd = FALSE;
         }

      }

      // Pen Up
      else INST(PU)

         if (inBegEnd){
          wxLogMessage("bogus BegEnd in PU");
            inBegEnd = FALSE;
         }

                wxColour color(newColor->R, newColor->G, newColor->B);
//              wxColour color(255, 0,0);
                wxPen *pthispen = wxThePenList->FindOrCreatePen(color, width, wxSOLID);

                pdc->SetPen(*pthispen);
/*
         glColor4f(     (float)newColor-&gt;R/255.0,
                                (float)newColor-&gt;G/255.0,
                     (float)newColor-&gt;B/255.0,
                     trans);
*/
         sscanf(str, "%u,%u", &x, &y);
         x1 = x - pivot_x;      // /scaleFac;
         y1 = y - pivot_y;      // /scaleFac;

//              Rotation
         if(rot_angle)
                 {
                         float xp = (x1 * cos_rot) - (y1 * sin_rot);
                         float yp = (x1 * sin_rot) + (y1 * cos_rot);

                         x1 = (int)xp;
                         y1 = (int)yp;
                 }


                 x1 /= scaleFac;
         y1 /= scaleFac;

                 x1 += r.x;
                 y1 += r.y;

         while(*str != ';')str++;
      }

                // Pen Down
      else INST(PD)
         do{
            if (*str == ';')
               continue;

            if (!inBegEnd){
               inBegEnd = TRUE;
            }

            sscanf(str, "%u,%u", &x, &y);
            x2 = x - pivot_x;
            y2 = y - pivot_y;
                        if(rot_angle)
                        {
                                float xp = (x2 * cos_rot) - (y2 * sin_rot);
                                float yp = (x2 * sin_rot) + (y2 * cos_rot);

                                x2 = (int)xp;
                                y2 = (int)yp;
                        }

            x2 /= scaleFac;
            y2 /= scaleFac;

                        x2 += r.x;
                        y2 += r.y;

                        pdc->DrawLine(x1, y1, x2, y2);
            //printf("PD x:%d y:%d xd:%f yd:%f \n",x,y,xd,yd);
            //printf("PD x:%d y:%d\n",x,y);

                        x1=x2;                  // set for pu;pd;pd....
                        y1=y2;

            while(*str++ != ',' );                      // specs: could repeat x,y,x, ..
            while(*str   != ',' && *str != ';')str++;  // but never do!
         }while(*str != ';');                                                                    // outside poly mode

         if(0 != strncmp(str,";PD",3)){ // not very smart!!
 //           glEnd();                                                  // find better state machine
            inBegEnd = FALSE;                           // ie put glEnd in PU !?
         }
       }



//-- poly mode ---

        // trans. is 1 for CI, AA, EP, PD


      // Polygon Mode
      else INST(PM)
         tessObj = FALSE;
         polyMode= TRUE;
         do{
            if (*str == '0'){           // start a new poly
               str+=2;

               // CIrcle
               INST(CI)
                        radius = (double)atoi(str);
                                        wxColour color(newColor->R, newColor->G, newColor->B);
                                        wxBrush *pthisbrush = wxTheBrushList->FindOrCreateBrush(color, wxSOLID);
                                        wxPen *pthispen = wxThePenList->FindOrCreatePen(color, width, wxSOLID);

                                        pdc->SetPen(*pthispen);
                                        pdc->SetBrush(*pthisbrush);

                                        int r1 = (int)radius / scaleFac;

                                        pdc->DrawCircle(x1, y1, r1);

//                  gluQuadricDrawStyle(qobj, GLU_FILL);
//                  gluQuadricNormals(qobj, GLU_FLAT);
//                              gluDisk(qobj, 0.0, radius/scaleFac, 20, 4);
                  inBegEnd = FALSE;

                  while(*str != ';') ++str;

               // Arc Angle --never used!
               }else INST(AA)
                           wxLogMessage("SEQuencer:_renderHPGL(): fixme AA instruction not implemented");

                  //centerX = (double)atoi(str++);
                  //centerY = (double)atoi(str++);
                  //sweepAngle   = atoi(str++);

                  // computer startAngle and radius

                  //gluQuadricDrawStyle(qobj, GLU_LINE);
                  //gluPartialDisk(qobj,0,radius,0,0,startAngle, sweepAngle);
                  inBegEnd = FALSE;
               }else{
                  tessObj = TRUE;
//                  gluTessBeginPolygon(tobj,NULL);
//                  gluTessBeginContour(tobj);
                  inBegEnd = FALSE;
               }
            }

            if (*str == '1'){   // sub poly --never used!
               str++;
//               gluTessEndContour(tobj);
//               gluTessBeginContour(tobj);
//               printf("begin sub poly symb\n");
            }

            if (tessObj){
               str+=2;    // skip PD
               do{
                if (!inBegEnd){
                                          PointArray[0].x =x1;
                                          PointArray[0].y =y1;
                                          vIdx = 1;
                     inBegEnd = TRUE;
                }                                               // no need to remember PU!

                  // read tess vertex
                                sscanf(str, "%u,%u", &x, &y);
                        x2 = x - pivot_x;
                            y2 = y - pivot_y;
                                 if(rot_angle)
                                 {
                                         float xp = (x2 * cos_rot) - (y2 * sin_rot);
                                         float yp = (x2 * sin_rot) + (y2 * cos_rot);

                                         x2 = (int)xp;
                                         y2 = (int)yp;
                                 }
                                x2 /= scaleFac;
                                y2 /= scaleFac;

                                x2 += r.x;
                                y2 += r.y;

                                if(vIdx < MAX_POINTS)
                                {
                                        PointArray[vIdx].x =x2;
                                        PointArray[vIdx].y =y2;
                                }

                ++vIdx;

                 while(*str++ != ',' );                 // specs: could repeat x,y,x, ..
                 while(*str   != ',' && *str != ';')str++;
                 if (*str == ',') str++;
                 if (0 == strncmp(str,";PD",3)) str += 3;
               }while(*str != ';');
            }
         }while(0 != strncmp(str,";PM2",4));

         // exit polygon mode
         str++;
         while(*str != ';') ++str;


      } // PM

      // Edge Polygon --draw polygon with lines
      // never called --not tested
      else INST(EP)
         if(tessObj){
          wxLogMessage("SEQuencer:_renderHPGL(): fixme EP instruction not implemented ");
            //gluTessProperty(tobj,GLU_TESS_BOUNDARY_ONLY, GL_TRUE);
            //gluTessEndPolygon(tobj);
            //inBegEnd = FALSE;
            //vIdx = 0;
         }

      }

      // Fill Polygon
      else INST(FP)
         if(tessObj){
                        wxColour color(newColor->R, newColor->G, newColor->B);
                        wxBrush *pthisbrush = wxTheBrushList->FindOrCreateBrush(color, wxSOLID);

                        pdc->SetBrush(*pthisbrush);
                        pdc->DrawPolygon(vIdx, PointArray);
            inBegEnd = FALSE;
            //vIdx = 0;
         }
      }

      // Symbol Call    --never used
      else INST(SC)
                  wxLogMessage("SEQuencer:_renderHPGL(): fixme SC instruction not implemented ");
      }



      ++str;

   } /* while */



/*

   if(createTexture)
   {
      int err=0;
      GLint texSize;


      //glGetIntegerv(GL_MAX_TEXTURE_SIZE, &amp;texSize);
      //printf("texSize:%d\n",texSize);

      w=64;     // 16 ok
      h=32;

      //printf("w: %d h:%d\n",w,h);
      //if ( w%2 == 1) w++;
      //if ( h%2 == 1) h++;
      //printf("w: %d h:%d\n",w,h);

//      glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,0,0,w,h,0);
      glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGB,0,0,64,64,0);
      //glCopyTexSubImage2D(GL_TEXTURE_2D,0,GL_RGBA,0,0,w,h,0);
      //printf("ERROR: %s --errno:%d\n",glGetString(glGetError()), glGetError());
      rule-&gt;userData.pattName = *crntTextName;
      printf("create pattern name:%d\n",*crntTextName);
      crntTextName++;
//      glDisable(GL_TEXTURE_2D);

   }else{
      glEndList();


      //if (polyMode)
      //   rule-&gt;userData.listName = 0; // discard poly --debug
      //else
         rule-&gt;userData.listName = listIndex++;
   }

dsr
*/

/*
// test to create symb. texture in processor memory
// could be of some use later!

   else{
      int err;
      void *ptr=NULL;


      ptr = g_new0(int,4*w*h);
      GLOB_w = w;
      GLOB_h = h;

   err = glGetError();
   printf("before glReadPixels: %s\n",gluErrorString(err));

      glPixelStorei(GL_PACK_ALIGNMENT,1);


      glReadBuffer(GL_BACK);
      glReadPixels(0,0,w,h,GL_RGBA, GL_UNSIGNED_BYTE, ptr);
      rule-&gt;userData.pixelPtr = ptr;
      pixelPtr = ptr;

   err = glGetError();
   printf("after glReadPixels: %s\n",gluErrorString(err));

      //printf("glReadPixels\n");

     //glPixelStorei(GL_UNPACK_ALIGNMENT,1);

   glRasterPos2i(100,100);
   //glRasterPos2i(rzRules-&gt;obj-&gt;x,rzRules-&gt;obj-&gt;y);
   //rzRules-&gt;obj-&gt;x,rzRules-&gt;obj-&gt;y

   //glDrawPixels(64,64,GL_RGBA,GL_UNSIGNED_BYTE,rule-&gt;razRule-&gt;userData.pixelPtr);

   err = glGetError();
   printf("before glDrawPixels: %s\n",gluErrorString(err));

   glRotatef(30.0,0.0,0.0,1.0);

   //glDrawBuffer(GL_BACK);
   glDrawPixels(GLOB_w,GLOB_GL_RGBA,GL_UNSIGNED_BYTE,pixelPtr);
   err = glGetError();
   printf("glDrawPixels: %s\n",gluErrorString(err));
   glFlush();
   }
*/


//dsr   return 0;       // return 0 to continue BTree traversal

   //return 1;  // return 1 to stop BTree traversal
//dsr}








        return true;
}

//-----------------------------------------------------------------------------------------
//      Instantiate a Symbol or Pattern stored as XBM ascii in a rule
//      Producing a wxImage
//-----------------------------------------------------------------------------------------
wxImage *s52plib::RuleXBMToImage(Rule *prule)
{
    //      Decode the color definitions
    wxArrayPtrVoid *pColorArray = new wxArrayPtrVoid;

    wxString cstr(*prule->colRef.SCRF);
    unsigned int i = 0;

    while(i < (unsigned int)cstr.Len())
    {
            i++;
            wxString thiscolor = cstr(i, 5);

            color *pColor =  S52_getColor((char *)thiscolor.c_str());

            pColorArray->Add((void *) pColor);

            i+=5;
    }


    //      Get geometry
    int width  = prule->pos.line.bnbox_w.SYHL;
    int height = prule->pos.line.bnbox_h.SYVL;

    wxString gstr(*prule->bitmap.SBTM);                     // the bit array

    wxImage *pImage = new wxImage(width, height );          // put the bits here temporarily

    for(int iy = 0 ; iy < height ; iy++)
    {
            wxString thisrow = gstr(iy * width, width);             // extract a row

            for(int ix = 0 ; ix < width ; ix++)
            {
                    int cref = (int)(thisrow[ix] - 'A');            // make an index
                    if(cref >= 0)
                    {
                            color *pthisbitcolor = (color *)(pColorArray->Item(cref));
                            pImage->SetRGB(ix, iy, pthisbitcolor->R, pthisbitcolor->G, pthisbitcolor->B);
                    }
                    else
                    {
                            pImage->SetRGB(ix, iy, unused_color.R, unused_color.G, unused_color.B);
                    }

            }
    }

    pColorArray->Clear();
    delete pColorArray;

    return pImage;
}




//
//      Render Raster Symbol
//      Symbol is instantiated as a bitmap the first time it is needed
//      and re-built on color scheme change
//
bool s52plib::RenderRasterSymbol(Rule *prule, wxDC *pdc, wxPoint &r, float rot_angle)
{
        //Instantiate the symbol if necessary
    if((prule->pixelPtr == NULL) || (prule->parm1 != m_ColorScheme))
        {
            wxImage *pImage = RuleXBMToImage(prule);

            //      Make the bitmap
            wxBitmap *pbm = new wxBitmap(*pImage);

            //      Make the mask
            wxMask *pmask = new wxMask(*pbm,
                    wxColour(unused_color.R, unused_color.G, unused_color.B));

            //      Associate the mask with the bitmap
            pbm->SetMask(pmask);

            // delete any old private data
            wxBitmap *pbmo = (wxBitmap *)(prule->pixelPtr);
            delete pbmo;

            //      Save the bitmap ptr and aux parms in the rule
            prule->pixelPtr = pbm;
            prule->parm1 = m_ColorScheme;

            //      Clean up
            delete pImage;

        }               // instantiation

        //      Now render the symbol

        //      Get the bitmap into a memory dc
        wxMemoryDC mdc;

        mdc.SelectObject((wxBitmap &)(*((wxBitmap *)(prule->pixelPtr))));

        int width  = prule->pos.line.bnbox_w.SYHL;
        int height = prule->pos.line.bnbox_h.SYVL;

        int pivot_x = prule->pos.line.pivot_x.SYCL;
        int pivot_y = prule->pos.line.pivot_y.SYRW;

        //      Blit it into the target dc
        pdc->Blit(r.x - pivot_x, r.y - pivot_y, width, height, &mdc, 0, 0, wxCOPY,  true);

        mdc.SelectObject(wxNullBitmap);


        return true;

}



// SYmbol
int s52plib::_renderSY(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
    float angle = 0;
    float orient;

    if(rules->razRule != NULL)
    {
        if(GetFloatAttr(rzRules->obj, "ORIENT", orient))
           angle = orient;

        if(!strncmp(rules->INSTstr, "LIGHTS0", 7))  // matches LIGHTS01 and 02
           angle = 135;


        float xlon = rzRules->obj->x;
        float ylat = rzRules->obj->y;

        wxPoint r;
        rzRules->chart->GetPointPix(ylat, xlon, &r);


        if(rzRules->obj->Primitive_type == GEO_AREA)
        {
            //  Render symbol at centroid of BoundingBox
            float cent_lat, cent_lon;
            wxBoundingBox *bb = &(rzRules->obj->BBObj);

            cent_lat = ((bb->GetMinY()) + (bb->GetMaxY())) / 2;
            cent_lon = ((bb->GetMinX()) + (bb->GetMaxX())) / 2;

            wxPoint rc;
            rzRules->chart->GetPointPix(cent_lat, cent_lon, &rc);

            r=rc;
        }


        if(rules->razRule->definition.SYDF == 'V')
                RenderHPGL(rules->razRule, pdc, r, angle);

        else if(rules->razRule->definition.SYDF == 'R')
                RenderRasterSymbol(rules->razRule, pdc, r, angle);

    }

return 0;

/*dsr
/////   glCallList(rules->razRule->userData.listName);

   // note: OGL set meta to none so this is not
   // a bug in every case
   // this need to be fix any way!!
   if (rules->ruleType == RUL_NONE){
      printf("SEQuencer:_renderSY(): fixme, draw QUESTION MARK here!!!\n");
      return 0;
   }


   // find center of g
   if(rzRules->obj->geoPrim == GEO_AREA){
      pt        *ppt;
      pt3   *ppt3, *p;
      int npt = rzRules->obj->npt;
      int i;

      // signal center of g begin
      computeCenter = TRUE;
      gluTessBeginPolygon(tobj,NULL);

      gluTessBeginContour(tobj);
      ppt  = rzRules->obj->geoPt;
//      ppt += (rzRules->obj->npt-1) * sizeof(pt*);
//      ppt3 = (pt3*)ppt;
        ppt3 = p = g_new0(pt3,npt);
      printf("SY GEO_AREA nbr pt: %d \n",npt);
      for (i=0;i&lt;npt;++i){
         ppt3->x = ppt->x;
         ppt3->y = ppt->y;
         ppt3->z = 0.0;
//      printf("x:%f y:%f z:%f\n",ppt3->x,ppt3->y,ppt3->z);

        gluTessVertex(tobj,(GLdouble*)ppt3,(GLdouble*)ppt3);
         ++ppt;
         ++ppt3;
      }
      gluTessEndContour(tobj);
      gluTessEndPolygon(tobj);

      g_free(p);


   }


   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   // set new coord. system centerG
   if (computeCenter)
      glTranslatef( centerG.x, centerG.y, 0.0);
   else
      glTranslatef(rzRules->obj->x,rzRules->obj->y, 0.0);

   computeCenter = FALSE;

   //glRotated(?.?, 0.0, 0.0, 1.0);

   // draw symb
   glCallList(rules->razRule->userData.listName);

   //glCallList(149);
   //printf("listName:%d\n",rules->razRule->userData.listName);

   glFlush();
   glPopMatrix();


   printf("drawn SY\n");

   return 1;
*/
}

//-----------------------------------------------------------------------------
//          C Linkage to clip.c
//-----------------------------------------------------------------------------

extern "C" {
      typedef enum { Visible, Invisible } ClipResult;
      ClipResult cohen_sutherland_line_clip_i (int *x0, int *y0, int *x1, int *y1,
                                   int xmin_, int xmax_, int ymin_, int ymax_);
}



// Line Simple Style
int s52plib::_renderLS(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{

        wxPoint         *ptp;
        int     npt;
        color   *c;
        int     w;

        char *str = (char*)rules->INSTstr;

        c = S52_getColor(str+7);                // Colour
        wxColour color(c->R, c->G, c->B);

        w = atoi(str+5);                        // Width

        int style = wxSOLID;                    // Style

// Windows98 cannot reliably draw dashed lines
#ifndef __WXMSW__
        if(!strncmp(str, "DASH", 4))
            style = wxSHORT_DASH;
#endif


        wxPen *pthispen = wxThePenList->FindOrCreatePen(color, w, style);
        pdc->SetPen(*pthispen);

        if(rzRules->obj->pPolyTessGeo)
        {
            int xmin_ = 0;
            int xmax_ = vp->pix_width;
            int ymin_ = 0;
            int ymax_ = vp->pix_height;
            int x0, y0, x1, y1;

            PolyTriGroup *pptg = rzRules->obj->pPolyTessGeo->Get_PolyTriGroup_head();

            float *ppolygeo = pptg->pgroup_geom;

            int ctr_offset = 0;
            for(int ic = 0; ic < pptg->nContours ; ic++)
            {

                int npt = pptg->pn_vertex[ic];
                wxPoint *ptp = (wxPoint *)malloc((npt + 1) * sizeof(wxPoint));
                wxPoint *pr = ptp;

                float *pf = &ppolygeo[ctr_offset];
                for(int ip=0 ; ip < npt ; ip++)
                {

//                        float plon = ppolygeo[(2 * ip) + ctr_offset];
//                        float plat = ppolygeo[(2 * ip) + ctr_offset + 1];

                    float plon = *pf++;
                    float plat = *pf++;

                    rzRules->chart->GetPointPix(plat, plon, pr);
                    pr++;
                }
                float plon = ppolygeo[ ctr_offset];             // close the polyline
                float plat = ppolygeo[ ctr_offset + 1];
                rzRules->chart->GetPointPix(plat, plon, pr);


                for(int ipc=0 ; ipc < npt ; ipc++)
                {
                    x0 = ptp[ipc].x;
                    y0 = ptp[ipc].y;
                    x1 = ptp[ipc+1].x;
                    y1 = ptp[ipc+1].y;

                    // Do not draw null segments
                    if((x0 == x1) && (y0 == y1))
                        continue;

                    ClipResult res = cohen_sutherland_line_clip_i (&x0, &y0, &x1, &y1,
                            xmin_, xmax_, ymin_, ymax_);

                    if(res != Invisible)
                        pdc->DrawLine(x0,y0,x1,y1);
                }

//                    pdc->DrawLines(npt + 1, ptp);
                free(ptp);
                ctr_offset += npt*2;
            }
        }

        else if(rzRules->obj->geoPt)
        {
            pt *ppt = rzRules->obj->geoPt;
            npt = rzRules->obj->npt;
            ptp = (wxPoint *)malloc(npt * sizeof(wxPoint));
            wxPoint *pr = ptp;
            wxPoint p;
            for(int ip=0 ; ip<npt ; ip++)
            {
                    float plat = ppt->y;
                    float plon = ppt->x;

                    rzRules->chart->GetPointPix(plat, plon, &p);

                    *pr = p;

                    pr++;
                    ppt++;
            }

            pdc->DrawLines(npt, ptp);
            free(ptp);
        }

        return 1;
}


// Line Complex
int s52plib::_renderLC(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
        wxPoint   *ptp;
        int       npt;
        color     *c;
        int       w;
        wxPoint   r;
        return 1;

        int isym_len = rules->razRule->pos.line.bnbox_w.SYHL;
        float sym_len = isym_len * canvas_pix_per_mm / 100;
        float sym_factor = 1.50;                        // gives nicer effect


//      Create a pen for drawing adjustments outside of HPGL renderer
        char *tcolptr = (char *)(rules->razRule->colRef.LCRF->c_str());
        c = S52_getColor(tcolptr + 1);          // +1 skips "n" in HPGL SPn format
        w = 1;
        wxColour color(c->R, c->G, c->B);
        wxPen *pthispen = wxThePenList->FindOrCreatePen(color, 1, wxSOLID);
        pdc->SetPen(*pthispen);

        if(rzRules->obj->pPolyTessGeo)
        {
            PolyTriGroup *pptg = rzRules->obj->pPolyTessGeo->Get_PolyTriGroup_head();
            float *ppolygeo = pptg->pgroup_geom;

            int ctr_offset = 0;
            for(int ic = 0; ic < pptg->nContours ; ic++)
            {

                int npt = pptg->pn_vertex[ic];
                wxPoint *ptp = (wxPoint *)malloc((npt + 1) * sizeof(wxPoint));
                wxPoint *pr = ptp;
                for(int ip=0 ; ip < npt ; ip++)
                {
                    float plon = ppolygeo[(2 * ip) + ctr_offset];
                    float plat = ppolygeo[(2 * ip) + ctr_offset + 1];

                    rzRules->chart->GetPointPix(plat, plon, pr);
                    pr++;
                }
                float plon = ppolygeo[ ctr_offset];             // close the polyline
                float plat = ppolygeo[ ctr_offset + 1];
                rzRules->chart->GetPointPix(plat, plon, pr);


                draw_lc_poly(pdc, ptp, npt + 1, sym_len, sym_factor, rules->razRule);

                free(ptp);

                ctr_offset += npt*2;
            }
        }

        else if(rzRules->obj->geoPt)                            // if the object is not described by a poly structure
        {
                pt *ppt = rzRules->obj->geoPt;


                npt = rzRules->obj->npt;
                ptp = (wxPoint *)malloc(npt * sizeof(wxPoint));
                wxPoint *pr = ptp;
                wxPoint p;
                for(int ip=0 ; ip<npt ; ip++)
                {
                        float plat = ppt->y;
                        float plon = ppt->x;

                        rzRules->chart->GetPointPix(plat, plon, &p);

                        *pr = p;

                        pr++;
                        ppt++;
                }


                draw_lc_poly(pdc, ptp, npt, sym_len, sym_factor, rules->razRule);

                free(ptp);
        }

        return 1;
}


//      Render Line Complex Polyline

void s52plib::draw_lc_poly(wxDC *pdc, wxPoint *ptp, int npt,
                           float sym_len, float sym_factor, Rule *draw_rule)
{
    wxPoint   r;

    for(int iseg = 0 ; iseg < npt - 1 ; iseg++)
    {
            float dx = ptp[iseg + 1].x - ptp[iseg].x;
            float dy = ptp[iseg + 1].y - ptp[iseg].y;
            float seg_len = sqrt(dx*dx + dy*dy);
            float theta = atan2(dy,dx);
            float cth = cos(theta);
            float sth = sin(theta);
            float tdeg = theta * 180. / PI;

            if(seg_len >= 1.0)
            {
                if(seg_len <= sym_len * sym_factor)
                {
                        if(seg_len >= sym_len)
                        {
                            int xst1 = ptp[iseg].x;
                            float xst2 = xst1 + (sym_len * cth);

                            int yst1 = ptp[iseg].y;
                            float yst2 = yst1 + (sym_len * sth);

                            pdc->DrawLine(xst1, yst1, (wxCoord)floor(xst2), (wxCoord)floor(yst2));
                        }
                        else
                        {
                            pdc->DrawLines(2, &ptp[iseg]);
                        }
                }

                else
                {

                        float s=0;
                        float xs = ptp[iseg].x;
                        float ys = ptp[iseg].y;

                        while(s + (sym_len * sym_factor) < seg_len)
                        {
                                r.x = (int)xs;
                                r.y = (int)ys;
                                RenderHPGL(draw_rule, pdc, r, tdeg);

                                xs += sym_len * cth * sym_factor;
                                ys += sym_len * sth * sym_factor;
                                s += sym_len * sym_factor;
                        }
//                        pdc->SetPen(*pthispen);
                        pdc->DrawLine((int)xs, (int)ys, ptp[iseg+1].x, ptp[iseg+1].y);


                }
            }
    }
}




// Multipoint Sounding
int s52plib::_renderMPS(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
      OGRMultiPoint *pMP = (OGRMultiPoint *)(rzRules->obj->OGeo);
      int npt = pMP->getNumGeometries();

      wxPoint p;
      for(int ip=0 ; ip<npt ; ip++)
      {
            OGRPoint *poPoint = (OGRPoint *)( pMP->getGeometryRef( ip ));

            float plat = poPoint->getY();
            float plon = poPoint->getX();
            float z = poPoint->getZ();

            rzRules->chart->GetPointPix(plat, plon, &p);

            char str[10];
            if(z < 10)
                  sprintf(str, "%3.1f", z);
            else
                  sprintf(str, "%3.0f", z);

            int dx, dy;
            RenderText(pdc, pSmallFont, str,
                       p.x, p.y, dx, dy);

      }


      return 1;
}










// Conditional Symbology
char *s52plib::_renderCS(ObjRazRules *rzRules, Rules *rules)
{
   void *ret;
   void* (*f)(void*);

   static int f05;

   if (rules->razRule == NULL){
           if(!f05)
                  CPLError((CPLErr)0, 0,"S52plib:_renderCS(): ERROR no conditional symbology for: %s\n",
                        rules->INSTstr);
           f05++;
      return 0;
   }


   void *g = (void *) rules->razRule;

#ifdef FIX_FOR_MSVC  //__WXMSW__
//#warning Fix this cast, somehow...
//      dsr             sigh... can't get the cast right
   _asm
   {
                mov eax,[dword ptr g]
                mov [dword ptr f],eax
   }
   ret = f((void *)rzRules);    // call cond symb
#else

    f= (void *(*)(void *))g;
    ret = f((void *)rzRules);

#endif

   return (char *)ret;
}


int s52plib::_draw(wxDC *pdcin, ObjRazRules *rzRules, ViewPort *vp)
{
    if(!ObjectRenderCheck(rzRules, vp))
        return 0;

    pdc = pdcin;                    // use this DC
    Rules *rules = rzRules->LUP->ruleList;

//       if(!strncmp(rzRules->LUP->OBCL, "CTNARE", 6))
//        int yyrt = 4;



        while (rules != NULL)
        {
                  switch (rules->ruleType){
//                         case RUL_ARE_CO:       _renderAC(rzRules,rules, vp);break;             // AC
                         case RUL_TXT_TX:       _renderTX(rzRules,rules, vp);break;             // TX
                         case RUL_TXT_TE:       _renderTE(rzRules,rules, vp);break;             // TE
                         case RUL_SYM_PT:       _renderSY(rzRules,rules, vp);break;             // SY
                         case RUL_SIM_LN:       _renderLS(rzRules,rules, vp);break;             // LS
                         case RUL_COM_LN:       _renderLC(rzRules,rules, vp);break;             // LC
                         case RUL_MUL_SG:       _renderMPS(rzRules,rules, vp);break;            // MultiPoint Sounding

                         case RUL_CND_SY:
                             {
                                if(!rzRules->obj->bCS_Added)
                                {
                                    rzRules->obj->CSrules = NULL;
                                    GetAndAddCSRules(rzRules, rules);
                                    rzRules->obj->bCS_Added = 1;                // mark the object
                                }
                                Rules *rules_last = rules;
                                rules = rzRules->obj->CSrules;

                                while(NULL != rules)
                                {
                                    switch (rules->ruleType)
                                    {
//                                        case RUL_ARE_CO:       _renderAC(rzRules,rules, vp);break;             // AC
                                        case RUL_TXT_TX:       _renderTX(rzRules,rules, vp);break;             // TX
                                        case RUL_TXT_TE:       _renderTE(rzRules,rules, vp);break;             // TE
                                        case RUL_SYM_PT:       _renderSY(rzRules,rules, vp);break;             // SY
                                        case RUL_SIM_LN:       _renderLS(rzRules,rules, vp);break;             // LS
                                        case RUL_COM_LN:       _renderLC(rzRules,rules, vp);break;             // LC
                                        case RUL_MUL_SG:       _renderMPS(rzRules,rules, vp);break;            // MultiPoint Sounding
                                        case RUL_NONE:
                                        default:
                                          break; // no rule type (init)
                                    }
                                    rules_last = rules;
                                    rules = rules->next;
                                }

                                rules = rules_last;
                                break;
                             }

                         case RUL_NONE:
                         default:
                                 break; // no rule type (init)
                  }                                     // switch

                  rules = rules->next;
         }

    return 1;
}


//----------------------------------------------------------------------------------
//
//              Fast Basic Canvas Rendering
//              Render triangle
//
//----------------------------------------------------------------------------------
int s52plib::dda_tri(wxPoint *ptp, color *c,
                      render_canvas_parms *pb_spec,
                      render_canvas_parms *mask,
                      render_canvas_parms *pPatt_spec)

{
    unsigned char r, g, b;

    if(NULL != c)
    {
#ifdef dyUSE_BITMAPO_S57
        r = c->R;
        g = c->G;
        b = c->B;
#else
        b = c->R;
        g = c->G;
        r = c->B;
#endif
    }

    //      Determine ymin and ymax indices


    int ymax = ptp[0].y;
    int ymin = ptp[0].y;
    int imin = 0;
    int imax = 0;
    int imid;

    for(int ip=1 ; ip < 3 ; ip++)
    {
//        printf("%d %d\n", ptp[ip].x, ptp[ip].y);
        if(ptp[ip].y > ymax)
        {
            imax = ip;
            ymax = ptp[ip].y;
        }
        if(ptp[ip].y <= ymin)
        {
            imin = ip;
            ymin= ptp[ip].y;
        }
    }

    imid = 3 - (imin + imax);            // do the math...

    if(imid == 3)
    {
        for(int ip=0 ; ip < 3 ; ip++)
            printf(" 3v %d %d %d\n", ip, ptp[ip].x, ptp[ip].y);
    }

    //      Create edge arrays using fast integer DDA

    int m, x, dy, count;



   // left edge
//    if((ptp[imin].y >= 0 ) && (ptp[imin].y < 1500))           // left begin point
//            ledge[ptp[imin].y] = ptp[imin].x;

    dy = (ptp[imax].y - ptp[imin].y);
    if(dy)
    {
            m = (ptp[imax].x - ptp[imin].x) << 16;
            m /= dy;

            x = ptp[imin].x << 16;
//            x += m;

            for (count = ptp[imin].y; count <= ptp[imax].y; count++)
            {
                    if((count >= 0 ) && (count < 1500))
                            ledge[count] = x >> 16;
                    x += m;
            }
    }
    else
    {
//            if((ptp[imin].y >= 0 ) && (ptp[imin].y < 1500))
//                    ledge[ptp[imin].y] = __min(ledge[ptp[imin].y], ptp[imax].x);
    }

   // right edge lower
//    if((ptp[imin].y >= 0 ) && (ptp[imin].y < 1500))           // right begin point
//        redge[ptp[imin].y] = ptp[imin].x;

    dy = (ptp[imid].y - ptp[imin].y);
    if(dy)
    {
        m = (ptp[imid].x - ptp[imin].x) << 16;
        m /= dy;

        x = ptp[imin].x << 16;
//        x += m;

        for (count = ptp[imin].y; count <= ptp[imid].y; count++)
        {
            if((count >= 0 ) && (count < 1500))
                redge[count] = x >> 16;
            x += m;
        }
    }
    else
    {
//        if((ptp[imin].y >= 0 ) && (ptp[imin].y < 1500))
//            redge[ptp[imin].y] = __min(ledge[ptp[imin].y], ptp[imid].x);
    }

   // right edge upper
//    if((ptp[imid].y >= 0 ) && (ptp[imid].y < 1500))           // right begin point
//        redge[ptp[imid].y] = ptp[imid].x;

    dy = (ptp[imax].y - ptp[imid].y);
    if(dy)
    {
        m = (ptp[imax].x - ptp[imid].x) << 16;
        m /= dy;

        x = ptp[imid].x << 16;
//        x += m;

        for (count = ptp[imid].y; count <= ptp[imax].y; count++)
        {
            if((count >= 0 ) && (count < 1500))
                redge[count] = x >> 16;
            x += m;
        }
    }
    else
    {
 //       if((ptp[imid].y >= 0 ) && (ptp[imid].y < 1500))
 //           redge[ptp[imid].y] = __min(ledge[ptp[imid].y], ptp[imax].x);
    }



//    if((ptp[imax].y >= 0 ) && (ptp[imax].y < 1500))         // right, top begin point
//            redge[ptp[imax].y] = ptp[imax].x;


    //      Check the triangle edge winding direction
    int dfSum = 0;
    dfSum += ptp[imin].x * ptp[imax].y
            - ptp[imin].y * ptp[imax].x;
    dfSum += ptp[imax].x * ptp[imid].y
            - ptp[imax].y * ptp[imid].x;
    dfSum += ptp[imid].x * ptp[imin].y
            - ptp[imid].y * ptp[imin].x;

    bool cw = dfSum < 0;

    //      if cw is true, redge is actually on the right



    //              Clip the triangle

    int y1 = ptp[imax].y;
    int y2 = ptp[imin].y;

    int ybt = pb_spec->y;
    int yt = pb_spec->y + pb_spec->height;

//    if(pb_spec->height ==  1)
 //       int ggld = 5;

    if(y1 > yt)
            y1 = yt;
    if(y1 < ybt)
            y1 = ybt;

    if(y2 > yt)
            y2 = yt;
    if(y2 < ybt)
            y2 = ybt;

    int lclip = pb_spec->lclip;
    int rclip = pb_spec->rclip;

    if(cw)
    {
        for(int iy = y2 ; iy <= y1 ; iy++)
        {

            if(ledge[iy] < lclip)
            {
                    if(redge[iy] < lclip)
                            ledge[iy] = -1;
                    else
                            ledge[iy] = lclip;
            }

            if(redge[iy] > rclip)
            {
                    if(ledge[iy] > rclip)
                            ledge[iy] = -1;
                    else
                            redge[iy] = rclip;
            }
        }
    }
    else
    {
        for(int iy = y2 ; iy <= y1 ; iy++)
        {

            if(redge[iy] < lclip)
            {
                if(ledge[iy] < lclip)
                    ledge[iy] = -1;
                else
                    redge[iy] = lclip;
            }

            if(ledge[iy] > rclip)
            {
                if(redge[iy] > rclip)
                    ledge[iy] = -1;
                else
                    ledge[iy] = rclip;
            }
        }
    }



    //              Fill the triangle

    int ya = y2;
    int yb = y1;

    unsigned char *pix_buff = pb_spec->pix_buff;
    unsigned char *pbm=0;
    if(mask)
        pbm = mask->pix_buff;

    int patt_size_x, patt_size_y, patt_pitch;
    unsigned char *patt_s0;
    if(pPatt_spec)
    {
        patt_size_y = pPatt_spec->height;
        patt_size_x = pPatt_spec->width;
        patt_pitch =  pPatt_spec->pb_pitch;
        patt_s0 =     pPatt_spec->pix_buff;
    }


    if(pb_spec->depth == 24)
    {
            for(int iyp = ya ; iyp < yb ; iyp++)
            {
                    if((iyp >= ybt) && (iyp < yt))
                    {
                            int yoff = (iyp - pb_spec->y) * pb_spec->pb_pitch;

                            unsigned char *py =  pix_buff + yoff;
                            unsigned char *pym = pbm      + yoff;

                            int ix, ixm;
                            if(cw)
                            {
                                ix = ledge[iyp];
                                ixm = redge[iyp];
                            }
                            else
                            {
                                ixm = ledge[iyp];
                                ix = redge[iyp];
                            }

//                           int ix = ledge[iyp];
//                            if(ix != -1)                    // special clip case
                            if(ledge[iyp] != -1)
                            {
                                    int xoff = (ix-pb_spec->x) * 3;

                                    unsigned char *px =  py  + xoff;
                                    unsigned char *pxm = pym + xoff;

 //                                   int ixm = redge[iyp];

                                    if(mask)                 // use the mask
                                    {
                                            while(ix <= ixm)
                                            {
                                                    if(*pxm == 0)
                                                    {
                                                            *px++ = b;
                                                            *px++ = g;
                                                            *px++ = r;
                                                    }
                                                    else
                                                    {
                                                            px += 3;
                                                    }

                                                    pxm += 3;
                                                    ix++;
                                            }
                                    }
                                    else                        // no mask
                                    {
                                        if(pPatt_spec)          // Pattern
                                        {
                                            while(ix <= ixm)
                                            {
                                                int patt_x = ix  % patt_size_x;
                                                int patt_y = iyp % patt_size_y;

                                                unsigned char *pp = patt_s0 + (patt_y * patt_pitch) +
                                                    patt_x * 3;

    //  Todo    This line assumes unused_color is always 0,0,0
                                                if(*pp && *(pp+1) && *(pp+2))
                                                {
                                                    *px++ = *pp++;
                                                    *px++ = *pp++;
                                                    *px++ = *pp++;
                                                }
                                                else
                                                {
                                                    px+=3;
                                                    pp+=3;
                                                }

                                                ix++;
                                            }
                                        }


                                        else                    // No Pattern
                                        {
                                            while(ix <= ixm)
                                            {
                                                *px++ = b;
                                                *px++ = g;
                                                *px++ = r;

                                                ix++;
                                                if((px - pb_spec->pix_buff) > ((pb_spec->pb_pitch * pb_spec->height) * pb_spec->depth))
                                                     wxLogMessage("pix 2");

                                            }
                                        }
                                    }
                            }
                    }
            }
    }

    if(pb_spec->depth == 32)
    {
            int color_int;
            if(NULL != c)
                color_int =  ((c->R) << 16) + ((c->G) << 8) + (c->B);

            assert(ya <= yb);

            for(int iyp = ya ; iyp < yb ; iyp++)
            {
                if((iyp >= ybt) && (iyp < yt))
                    {
                            int yoff =      (iyp - pb_spec->y) * pb_spec->pb_pitch;

                            unsigned char *py = pix_buff + yoff;
                            unsigned char *pym = pbm + yoff;


                            int ix, ixm;
                            if(cw)
                            {
                                ix = ledge[iyp];
                                ixm = redge[iyp];
                            }
                            else
                            {
                                ixm = ledge[iyp];
                                ix = redge[iyp];
                            }

//                            assert(ix <= ixm);
//                            if(ix > ixm)
//                                int ggl = 4;
                            if((ledge[iyp] != -1) /*&& cw && (ix <= ixm)*/)
                            {
                                    int xoff = (ix-pb_spec->x) * pb_spec->depth / 8;

                                    unsigned char *px = py + xoff;
                                    unsigned char *pxm = pym + xoff;


                                    if(mask)                                // use the mask
                                    {
                                            int *pxi = (int *)px ;
                                            while(ix <= ixm)
                                            {
                                                    if(*pxm == 0)
                                                            *pxi = color_int;
                                                    pxi++;
                                                    pxm += pb_spec->depth / 8;
                                                    ix++;
                                            }
                                    }
                                    else                                    // no mask
                                    {
                                        if(pPatt_spec)          // Pattern
                                        {
                                            while(ix <= ixm)
                                            {
                                                int patt_x = ix  % patt_size_x;
                                                int patt_y = iyp % patt_size_y;

                                                unsigned char *pp = patt_s0 + (patt_y * patt_pitch) +
                                                        patt_x * 4;

    //  Todo    This line assumes unused_color is always 0,0,0
                                                if(*pp && *(pp+1) && *(pp+2))
                                                {
                                                    *px++ = *pp++;
                                                    *px++ = *pp++;
                                                    *px++ = *pp++;
                                                    px++;
                                                    pp++;
                                                }
                                                else
                                                {
                                                    px+=4;
                                                    pp+=4;
                                                }

                                                ix++;
                                            }
                                        }

                                        else                    // No Pattern
                                        {
                                            int *pxi = (int *)px ;
                                            while(ix <= ixm)
                                            {
                                                *pxi++ = color_int;
                                                ix++;
                                            }
                                        }

                                    }
                            }
                    }
            }
    }

    return true;
}



void s52plib::FastRenderFilledPolygon(ObjRazRules *rzRules,
               S57Obj *obj, color *c, wxBoundingBox &BBView,
               render_canvas_parms *pb_spec, render_canvas_parms *mask,
               render_canvas_parms *pPatt_spec)
{


    color cp;
    if(NULL != c)
    {
        cp.R = c->R;
        cp.G = c->G;
        cp.B = c->B;
    }

    if(obj->pPolyTessGeo)
    {
        PolyTriGroup *ppg = obj->pPolyTessGeo->Get_PolyTriGroup_head();

        TriPrim *p_tp = ppg->tri_prim_head;
        while(p_tp)
        {

            if(BBView.Intersect(*(p_tp->p_bbox), 0) != _OUT)
            {
                //      Get and convert the points
                wxPoint *ptp = (wxPoint *)malloc((p_tp->nVert + 1) * sizeof(wxPoint));
                wxPoint *pr = ptp;

                wxPoint *pp3 = (wxPoint *)malloc(3 * sizeof(wxPoint));

                double *pvert_list = p_tp->p_vertex;

                for(int iv =0 ; iv < p_tp->nVert ; iv++)
                {
                    double lon = *pvert_list++;
                    double lat = *pvert_list++;
                    rzRules->chart->GetPointPixEst(lat, lon, pr);

                    pr++;
                }


                switch (p_tp->type)
                {
                    case PTG_TRIANGLE_FAN:
                    {
                        for(int it = 0 ; it < p_tp->nVert - 2 ; it++)
                        {
                            pp3[0].x = ptp[0].x;
                            pp3[0].y = ptp[0].y;

                            pp3[1].x = ptp[it+1].x;
                            pp3[1].y = ptp[it+1].y;

                            pp3[2].x = ptp[it+2].x;
                            pp3[2].y = ptp[it+2].y;

                            dda_tri(pp3, &cp, pb_spec, mask, pPatt_spec);
                        }
                        break;
                    }
                    case PTG_TRIANGLE_STRIP:
                    {
                        for(int it = 0 ; it < p_tp->nVert - 2 ; it++)
                        {
                            pp3[0].x = ptp[it].x;
                            pp3[0].y = ptp[it].y;

                            pp3[1].x = ptp[it+1].x;
                            pp3[1].y = ptp[it+1].y;

                            pp3[2].x = ptp[it+2].x;
                            pp3[2].y = ptp[it+2].y;

                            dda_tri(pp3, &cp, pb_spec, mask, pPatt_spec);
                        }
                        break;
                    }
                    case PTG_TRIANGLES:
                    {
                        for(int it = 0 ; it < p_tp->nVert ; it+=3)
                        {
                            pp3[0].x = ptp[it].x;
                            pp3[0].y = ptp[it].y;

                            pp3[1].x = ptp[it+1].x;
                            pp3[1].y = ptp[it+1].y;

                            pp3[2].x = ptp[it+2].x;
                            pp3[2].y = ptp[it+2].y;

                            dda_tri(pp3, &cp, pb_spec, mask, pPatt_spec);
                        }
                        break;
                    }
                }

                free(ptp);
                free(pp3);

            }   // if bbox
            p_tp = p_tp->p_next;                // pick up the next in chain
        }       // while
    }       // if pPolyTessGeo

}


int s52plib::FastRenderAP(ObjRazRules *rzRules, Rules *rules, ViewPort *vp,
                          render_canvas_parms *pb_spec)
{


      /*
      //    Create a bitmap consisting of repeat images of the pattern

      //    Calculate size of the pattern
      wxMemoryDC mdc_patt;
      wxBitmap bm_patt(500,500,-1);
      mdc_patt.SelectObject(bm_patt);
      wxPoint r(0,0);

      mdc_patt.ResetBoundingBox();
      RenderHPGL(rules->razRule, &mdc_patt, r, 0);
      int patt_width  = mdc_patt.MaxX() - mdc_patt.MinX();
      int patt_height = mdc_patt.MaxY() - mdc_patt.MinY();

      //    Now step and repeat
      rep_width = 2000;
      rep_height = 2000;
      wxMemoryDC mdc_patt_rep;
      wxBitmap bm_patt_rep(rep_width, rep_height,-1);
      mdc_patt_rep.SelectObject(bm_patt_rep);
      wxPoint rp(0,0);

      while(rp.y < rep_height)
      {
            while(rp.x < rep_width)
            {
                  RenderHPGL(rules->razRule, &mdc_patt_rep, rp, 0);
                  rp.x += patt_width * 2;
            }

            rp.y += patt_height * 2;
      }
*/

    if(rules->razRule->definition.SYDF == 'R')
    {
        if(rules->razRule->pixelPtr == NULL)
        {
            wxImage *pImage = RuleXBMToImage(rules->razRule);

//  Convert the initial wxImage in the rule to a useful PixelBuff

            int sizex = pImage->GetWidth();
            int sizey = pImage->GetHeight();

            render_canvas_parms *patt_spec = new render_canvas_parms;
            patt_spec->depth = BPP;                              // set the depth

            patt_spec->pb_pitch = ((sizex * patt_spec->depth / 8 ));
            patt_spec->lclip = 0;
            patt_spec->rclip = sizex - 1;
#ifdef S57USE_PIXELCACHE
            PixelCache *pDIBRect = new PixelCache(sizex, sizey, patt_spec->depth);
            patt_spec->pix_buff = pDIBRect->pData;
            patt_spec->PCPtr = (void *)pDIBRect;
#else
            patt_spec->pix_buff = (unsigned char *)malloc(sizey * patt_spec->pb_pitch);
#endif
                // Preset background
            memset(pb_spec->pix_buff, 0,sizey * patt_spec->pb_pitch);
            patt_spec->mask_buff = NULL;
            patt_spec->width = sizex;
            patt_spec->height = sizey;
            patt_spec->x = 0;
            patt_spec->y = 0;

            unsigned char *pd0 = patt_spec->pix_buff;
            unsigned char *pd;
            unsigned char *ps0 = pImage->GetData();
            unsigned char *ps;

            if(pb_spec->depth == 24)
            {
                for(int iy = 0 ; iy < sizey ; iy++)
                {
                    pd = pd0 + (iy * patt_spec->pb_pitch);
                    ps = ps0 + (iy * sizex * 3);
                    for(int ix = 0 ; ix<sizex ; ix++)
                    {
                        *pd++ = *ps++;
                        *pd++ = *ps++;
                        *pd++ = *ps++;
                    }
                }
            }

            else if(pb_spec->depth == 32)
            {
                for(int iy = 0 ; iy < sizey ; iy++)
                {
                    pd = pd0 + (iy * patt_spec->pb_pitch);
                    ps = ps0 + (iy * sizex * 3);
                    for(int ix = 0 ; ix<sizex ; ix++)
                    {
                        *pd++ = *ps++;
                        *pd++ = *ps++;
                        *pd++ = *ps++;
                        pd++;
                    }
                }
            }

            rules->razRule->pixelPtr = patt_spec;
//      Clean up
            delete pImage;
        }


        render_canvas_parms *ppatt_spec = (render_canvas_parms *)rules->razRule->pixelPtr;


/*
      //    Create a bitmap consisting of full screen of the pattern

        if( !pPCPatt)
        {
            dyMemDC dc_patt;

            pPCPatt = new PixelCache(vp->pix_width, vp->pix_height, BPP);
            pPCPatt->SelectIntoDC(dc_patt);

            wxBrush patt_brush(wxColour(255,255,255), wxVERTICAL_HATCH);
            dc_patt.SetBrush(patt_brush);
            wxBrush patt_bgbrush(wxColour(0,0,0));
            dc_patt.SetBackground(patt_bgbrush);
            dc_patt.Clear();
            dc_patt.DrawRectangle(0,0,vp->pix_width, vp->pix_height);
            dc_patt.SelectObject(wxNullBitmap);
        }
*/

//  Establish Color
/*
    color *c;
    char *str = (char*)rules->INSTstr;
    c = ps52plib->S52_getColor(str);
*/
//    color ctest;
//    ctest.R = 255;
//    ctest.G = 0;
//    ctest.B = 255;



//  Use the current viewport as a bounding box
    wxBoundingBox BBView(vp->lon_left, vp->lat_bot, vp->lon_right, vp->lat_top);

//  If no interior rings occur, then make a call to renderer directly without mask

    S57Obj    *ring = rzRules->obj->ring;

    if(ring == NULL)
    {
        FastRenderFilledPolygon(rzRules, rzRules->obj, NULL, BBView, pb_spec, NULL, ppatt_spec);
    }

//    Else build a mask of the object, considering interior rings as "holes"
    else
    {
/*

        render_canvas_parms patt_mask;
        patt_mask = *pb_spec;                   // mask geometry is identical to canvas

        patt_mask.pix_buff = (unsigned char *)calloc(patt_mask.height * pb_spec->pb_pitch, 1);
                    patt_mask.pix_buff = pb_spec->mask_buff;
        memset(patt_mask.pix_buff, 0, patt_mask.height * pb_spec->pb_pitch);

        // set the mask color
        color ctb;
        ctb.R = 255;
        ctb.G = 255;
        ctb.B = 255;

        FastRenderFilledPolygon(rzRules, rzRules->obj, &ctb, BBView, &patt_mask, NULL, NULL);






        //  Do an area render using pattern, color, and mask

        FastRenderFilledPolygon(rzRules, rzRules->obj, c, BBView, pb_spec, &patt_mask, pPCPatt);
  */
    }
    // Clean up

}       // Raster

    return 1;
}


int s52plib::FastRenderAC(ObjRazRules *rzRules, Rules *rules, ViewPort *vp,
                                 render_canvas_parms *pb_spec)
{
   color *c;
   char *str = (char*)rules->INSTstr;
   S57Obj    *ring = NULL;
   wxBoundingBox BBView(vp->lon_left, vp->lat_bot, vp->lon_right, vp->lat_top);

   c = ps52plib->S52_getColor(str);


   ring = rzRules->obj->ring;

   if(ring == NULL)                                                     // no holes
   {
           FastRenderFilledPolygon(rzRules,     rzRules->obj, c, BBView, pb_spec, NULL, NULL);
           return 1;
   }

   else
   {

//              Build a mask of the inner rings
                render_canvas_parms mask;
                mask = *pb_spec;                                // mask is identical to canvas

//              mask.pix_buff = (unsigned char *)calloc(mask.height * pb_spec->pb_pitch, 1);
                mask.pix_buff = pb_spec->mask_buff;

                //      Inline optimization of memset
#ifndef __WXMSW__
            if(32 == BPP)
            {
                    unsigned char *destination = mask.pix_buff;
                    char fill_value = 0;
                    int int_count = (mask.height * pb_spec->pb_pitch) >> 2;     // convert byte count to dword

                    asm ("cld\n\t"
                           "rep\n\t"
                           "stosl"
                          :
                          : "c" (int_count), "a" (fill_value), "D" (destination)                // input parms
                          :
                        );
            }
            else
               memset(mask.pix_buff, 0, mask.height * pb_spec->pb_pitch);

#else
               memset(mask.pix_buff, 0, mask.height * pb_spec->pb_pitch);
#endif

//              iterate on the inner rings to build a mask
//                      which is white for holes, black otherwise
               color ctb;
               ctb.R = 255;
               ctb.G = 255;
               ctb.B = 255;

               while(ring)
               {
                    if(BBView.Intersect(ring->BBObj, 0) != _OUT)            // Object is not wholly outside window
                    {
                          FastRenderFilledPolygon(rzRules, ring, &ctb, BBView, &mask, NULL, NULL);
                    }

                    ring = ring->ring;
               }

//      Now render the outer ring, using the mask to leave holes
               FastRenderFilledPolygon(rzRules, rzRules->obj, c, BBView, pb_spec, &mask, NULL);

   }    // else ring


   return 1;
}


int s52plib::RenderArea(wxDC *pdcin, ObjRazRules *rzRules, ViewPort *vp,
                                                render_canvas_parms *pb_spec)
{
    if(!ObjectRenderCheck(rzRules, vp))
        return 0;

    pdc = pdcin;                    // use this DC
    Rules *rules = rzRules->LUP->ruleList;


    while (rules != NULL)
    {
          switch (rules->ruleType){
                 case RUL_ARE_CO:       FastRenderAC(rzRules,rules, vp, pb_spec);break;         // AC
                 case RUL_ARE_PA:       FastRenderAP(rzRules,rules, vp, pb_spec);break;         // AP

                 case RUL_CND_SY:
                     {
                        if(!rzRules->obj->bCS_Added)
                        {
                            rzRules->obj->CSrules = NULL;
                            GetAndAddCSRules(rzRules, rules);
                            rzRules->obj->bCS_Added = 1;                // mark the object
                        }
                        Rules *rules_last = rules;
                        rules = rzRules->obj->CSrules;

                        while(NULL != rules)
                        {
                            switch (rules->ruleType)
                            {
                                case RUL_ARE_CO:       FastRenderAC(rzRules,rules, vp, pb_spec);break;
                                case RUL_ARE_PA:       FastRenderAP(rzRules,rules, vp, pb_spec);break;
                                case RUL_NONE:
                                default:
                                  break; // no rule type (init)
                            }
                            rules_last = rules;
                            rules = rules->next;
                        }

                        rules = rules_last;
                        break;
                     }



                 case RUL_NONE:
                 default:
                         break; // no rule type (init)
          }                                     // switch

          rules = rules->next;
    }

    return 1;

}

void s52plib::GetAndAddCSRules(ObjRazRules *rzRules, Rules *rules)
{

                    LUPrec  *NewLUP;
                    LUPrec  *LUP;
                    LUPrec  *LUPCandidate;

//  Try to find a match for this object/attribute set in dynamic CS LUP Table

//  Do this by checking each LUP in the CS LUPARRAY and checking....
//  a) is Object Name the same? and
//  b) was LUP created earlier by exactly the same INSTruction string?

                    char *rule_str1 = _renderCS(rzRules, rules);
                    wxString cs_string(rule_str1);
                    delete rule_str1;


                    wxArrayOfLUPrec *la = (wxArrayOfLUPrec *)(LUPTable[S52_LUPARRAY_COND_SYM]);
                    int index = 0;
                    int index_max = la->GetCount();
                    LUP = NULL;

                    while((index < index_max))
                    {
                        LUPCandidate = la->Item(index);
                        if(!strcmp(rzRules->LUP->OBCL, LUPCandidate->OBCL))
                        {
                            if(LUPCandidate->INST->IsSameAs(cs_string))
                            {
                                LUP = LUPCandidate;
                                break;
                            }
                        }
                        index++;
                    }






//  If not found, need to create a dynamic LUP and add to CS LUP Table

                    if(NULL == LUP)                                 // Not found
                    {

                        NewLUP = (LUPrec*)calloc(1, sizeof(LUPrec));
                        pAlloc->Add(NewLUP);

                        NewLUP->DISC = (enum _DisCat)OTHER;            // as a default

                        //sscanf(pBuf+11, "%d", &LUP->RCID);

                        strncpy(NewLUP->OBCL, rzRules->LUP->OBCL, 6);  // the object class name
//  if(!strncmp(LUP->OBCL, "LNDARE", 6))
//         int qewr = 9;

//                        NewLUP->FTYP = (enum _Object_t)pBuf[25];
//                        NewLUP->DPRI = (enum _DisPrio)pBuf[30];
//                        NewLUP->RPRI = (enum _RadPrio)pBuf[31];
//                        NewLUP->TNAM = (enum _LUPname)pBuf[36];


// Parse the instant object's attribute name string and attribute values to the LUP
// Attribute values are neede to ensure exact match


/*
                        wxString *pobj_attList = rzRules->obj->attList;
                        if ('\037' != pobj_attList[0])                                // could be empty!
                        {

                            wxString *LUPATTC = new wxString;

                            wxArrayString *pAS = new wxArrayString();
                            char *p = (char *)pobj_attList->c_str();

                            wxString *st1 = new wxString;
                            int attIdx = 0;

                            while(*p)
                            {
                                while(*p != 0x1f)
                                {
                                  st1->Append(*p);
                                  p++;
                                }

                                S57attVal *v;
                                v = rzRules->obj->attVal->Item(attIdx);
                                wxString apf = AttValPrintf(v);
                                st1->Append(apf);

                                LUPATTC->Append(*st1);
                                LUPATTC->Append('\037');

                                pAS->Add(*st1);
                                st1->Clear();
                                p++;
                                attIdx++;
                            }

                            delete st1;

                            NewLUP->ATTCArray = pAS;
                            NewLUP->ATTC = LUPATTC;
                        }


*/

//      Add the complete CS string to the LUP

                        wxString *pINST = new wxString(cs_string);
                        NewLUP->INST = pINST;

                        _LUP2rules(NewLUP, rzRules->obj);

// Add LUP to array
                        wxArrayOfLUPrec *pLUPARRAYtyped = condSymbolLUPArray;

                        pLUPARRAYtyped->Add(NewLUP);


                        LUP = NewLUP;
                    }       // if (LUP = NULL)


                    Rules *top = LUP->ruleList;
                    rzRules->obj->CSrules = top;                // patch in a new rule set
}





bool s52plib::ObjectRenderCheck(ObjRazRules *rzRules, ViewPort *vp)
{
    wxBoundingBox BBView(vp->lon_left, vp->lat_bot, vp->lon_right, vp->lat_top);

    if (rzRules->obj==NULL)
        return false;


//      Do Object Type Filtering

    if(m_nDisplayCategory == MARINERS_STANDARD)
    {
        if(!((OBJLElement *)(pOBJLArray->Item(rzRules->obj->iOBJL)))->nViz)
            return false;
    }

    if(m_nDisplayCategory == OTHER)
    {
        if((DISPLAYBASE != rzRules->LUP->DISC)
            && (STANDARD != rzRules->LUP->DISC)
            && (OTHER != rzRules->LUP->DISC))
        {
            return false;
        }
    }

    else if(m_nDisplayCategory == STANDARD)
    {
        if((DISPLAYBASE != rzRules->LUP->DISC) && (STANDARD != rzRules->LUP->DISC))
        {
            return false;
        }
    }
    else if(m_nDisplayCategory == DISPLAYBASE)
    {
        if(DISPLAYBASE != rzRules->LUP->DISC)
        {
            return false;
        }
    }


// must be visible

//      View BBox filtering

    if(BBView.Intersect(rzRules->obj->BBObj, 0) == _OUT)// Object is wholly outside window
        return false;

//      SCAMIN Filtering
    if(vp->chart_scale > rzRules->obj->Scamin)
        return false;

    return true;
}


//----------------------------------------------------------------------------------------------------------
//          Dead Code
//----------------------------------------------------------------------------------------------------------
#if 0

// Area Pattern
int s52plib::_renderAP(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{

        int i;
   pt   *ppt;
   pt3   *ppt3, *p;
   int   npt = rzRules->obj->npt;
   static GLfloat xequalzero[] = {1.0, 0.0, 0.0, 0.0};
   static int stop = 0;

/* draw the first pattern --debug
   if (stop)
   return 0;
   stop = 1;
*/

   // WARNING this call must be done from inside the main loop!


   printf("**** _renderAP **** PATT NAME: %8s\n", rules->razRule->name.PANM);
   //rules->razRule->userData.pattName);


   if ( 0 == rules->razRule->userData.pattName )
       return 0;


   //glPixelStorei(GL_PACK_ALIGNMENT,1);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D,rules->razRule->userData.pattName);
//   glBindTexture(GL_TEXTURE_2D,1);    // area51
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
//   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_DECAL);
//   glBindTexture(GL_TEXTURE_2D,1);    // area51
//   glEnable(GL_TEXTURE_2D);

//   glPushMatrix();
   //glMatrixMode(GL_MODELVIEW);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluOrtho2D(0,1000,0,500);

   glEnable(GL_TEXTURE_GEN_S);
   glEnable(GL_TEXTURE_GEN_T);
//   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
//   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
   glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
   glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
//   glTexGenfv(GL_S,GL_OBJECT_PLANE, xequalzero);
//   glTexGenfv(GL_T,GL_OBJECT_PLANE, xequalzero);


// test
   ppt  = rzRules->obj->geoPt;
   //glBegin(GL_POLYGON);
   //glBegin(GL_TRIANGLES);
   glBegin(GL_QUADS);
   printf("patt coord x:%f y:%f\n",ppt->x,ppt->y);
   glTexCoord2f(0.0,0.0);glVertex2f(ppt->x,ppt->y);
   glTexCoord2f(0.0,1.0);glVertex2f(ppt->x,ppt->y-0.01);
   glTexCoord2f(1.0,1.0);glVertex2f(ppt->x-0.01,ppt->y-0.01);
   glTexCoord2f(1.0,0.0);glVertex2f(ppt->x-0.01,ppt->y);
     // glTexCoord2f(0.0,0.0);glVertex2i(200,200);
     // glTexCoord2f(0.0,1.0);glVertex2i(200,500);
     // glTexCoord2f(1.0,1.0);glVertex2i(500,500);
     // glTexCoord2f(1.0,0.0);glVertex2i(500,200);
   glEnd();
   glFlush();
   //glPopMatrix();


/*
   gluTessBeginPolygon(tobj,NULL);
   gluTessBeginContour(tobj);
   ppt  = rzRules->obj->geoPt;
//   ppt += (rzRules->obj->npt-1) * sizeof(pt*);
//   ppt3 = (pt3*)ppt;
   ppt3 = p = g_new0(pt3,npt);
   printf("AP contour: %d ",npt);
   for (i=0;i&lt;npt;++i){
   ppt3->x = ppt->x;
   ppt3->y = ppt->y;
   ppt3->z = 0.0;
//     printf("x:%f y:%f z:%f\n",ppt3->x,ppt3->y,ppt3->z);
        //glTexCoord2f(ppt->x,ppt->y);

   gluTessVertex(tobj,(GLdouble*)ppt3,(GLdouble*)ppt3);

   ++ppt;
   ++ppt3;
}
   gluTessEndContour(tobj);
*/

   // holes
   /*
   gluTessBeginContour(tobj);

   ppt = rzRules->obj->geoPt;
   printf("AC: %d\n",rzRules->obj->npt);
   for (i=0;i&lt;rzRules->obj->npt;++i){
   printf("AC interior: %d ",npt);

     //glVertex2f((double)ppt->x,(double)ppt->y);
     //printf("%g,%g\n",ppt->x,ppt->y);
   gluTessVertex(tobj,ppt++,NULL);
     //++ppt;
}


   gluTessEndContour(tobj);
   */

//   gluTessEndPolygon(tobj);


   glDisable(GL_TEXTURE_GEN_S);
   glDisable(GL_TEXTURE_GEN_T);
   glDisable(GL_TEXTURE_2D);

   //g_free(p);

   printf("AP drawn\n");

   return 1;
}




// Area Color
int s52plib::_renderAC(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{

    char *str = (char*)rules->INSTstr;
    color *c = S52_getColor(str);

    polygroup *ppg = rzRules->obj->MPoly;
    if(ppg)
    {
        int nPolys = ppg->nPolys;

        double **pvert_array = ppg->pvert_array;
        int *pnv_array = ppg->pnv_array;

        for(int ip = 0 ; ip < nPolys ; ip++)
        {
            int nvert = pnv_array[ip];
            wxPoint *ptp = (wxPoint *)malloc(nvert * sizeof(wxPoint));
            wxPoint *pr = ptp;
            wxPoint p;

            double *pvert_list = pvert_array[ip];

            for(int iv =0 ; iv < nvert ; iv++)
            {
                double lon = pvert_list[2 * iv];
                double lat = pvert_list[(2 * iv) + 1];

                rzRules->chart->GetPointPixEst(lat, lon, pr);
                pr++;
            }


            wxBrush *pthisbrush;

//            int r,g,b;
//            r = ip * 20;

 //           pthisbrush = wxTheBrushList->FindOrCreateBrush(wxColour(r,r,r), wxSOLID);


            if(ip & 1)
            {
                wxColour color(255, 0, 0);
                pthisbrush = wxTheBrushList->FindOrCreateBrush(color, wxSOLID);
            }
            else
            {
                wxColour color(0, 255, 0);
                pthisbrush = wxTheBrushList->FindOrCreateBrush(color, wxSOLID);
            }
/*
            else
            {
            wxColour color(c->R, c->G, c->B);
            pthisbrush = wxTheBrushList->FindOrCreateBrush(color, wxSOLID);
        }
*/
            wxPen *pthispen = wxThePenList->FindOrCreatePen(wxColour(c->R, c->G, c->B), 1, wxSOLID);

            pdc->SetPen(*pthispen);
            pdc->SetBrush(*pthisbrush);

            pdc->DrawPolygon(nvert, ptp);

            free(ptp);
        }

    }       // if ppg



/*
    wxBoundingBox BBView(vp->lon_left, vp->lat_bot, vp->lon_right, vp->lat_top);


// return 1;
//      float plat, plon;

//   int        i;
    color *c;
    pt   *ppt;
//   pt3   *ppt3, *p, *r;
    char *str = (char*)rules->INSTstr;
    int npt;
    S57Obj    *ring      = NULL;

    c = S52_getColor(str);

    if (str[5] == ','){
    int trans = atoi(str+6);
    float f = (trans == 0)? 1 :(float)(trans * 25 / 100);
//      glColor4ub(c->R,c->G,c->B, f);
    printf("trans:%f\n",f);
}else{
//      glColor3ub(c->R,c->G,c->B);
//      glColor3ub(255,255,255);
}

    if(rzRules->obj->Index == 1032)
    int yyse = 3;

    ring = rzRules->obj->ring;

    if(ring == NULL)                                                     // no holes
    {
    npt  = rzRules->obj->npt;
    ppt  = rzRules->obj->geoPt;
    RenderFilledPolygonA(rzRules->chart->pdc, rzRules, rzRules->obj, c, BBView);
}

    else
    {
    rzRules->chart->pswc->Resume();

//              Create a compatible bitmap for simulating FloodFill
    wxMemoryDC temp_dc_full;
    temp_dc_full.ResetBoundingBox();
    int w,h;
    rzRules->chart->pdc->GetSize(&w,&h);
    wxBitmap temp_bmp_full(w,h);
    temp_dc_full.SelectObject(temp_bmp_full);
    temp_dc_full.SetBackground(*wxBLACK_BRUSH);
    temp_dc_full.Clear();

    RenderFilledPolygonA(&temp_dc_full, rzRules, rzRules->obj, c, BBView);

    color ctb;
    ctb.R = 0;
    ctb.G = 0;
    ctb.B = 0;

    while(ring)
    {
    if(BBView.Intersect(ring->BBObj, 0) != _OUT)            // Object is not wholly outside window
    {
    RenderFilledPolygonA(&temp_dc_full, rzRules, ring, &ctb, BBView);
}

    ring = ring->ring;
}

//      Extract  the bitmap representing the current extents of drawing
    int xo = temp_dc_full.MinX();
    int yo = temp_dc_full.MinY();
    int xx = temp_dc_full.MaxX();
    int yx = temp_dc_full.MaxY();

    xo = max(xo,0);
    yo = max(yo,0);
    xx = min(xx, w);
    yx = min(yx, h);

    int sx = xx - xo;
    int sy = yx - yo;

    wxMemoryDC temp_dc;
    wxBitmap temp_bmp(sx, sy);
    temp_dc.SelectObject(temp_bmp);
    temp_dc.SetBackground(*wxBLACK_BRUSH);
    temp_dc.Clear();

    temp_dc.Blit(0, 0, sx, sy, (wxDC *)&temp_dc_full, xo, yo);


    temp_dc_full.SelectObject(wxNullBitmap);
    temp_dc.SelectObject(wxNullBitmap);

//              wxMask *ptemp_mask = new wxMask(temp_bmp, wxColour(0,0,0));
//              temp_bmp.SetMask(ptemp_mask);

    temp_dc.SelectObject(temp_bmp);
//              rzRules->chart->pdc->Blit(xo, yo, sx, sy, (wxDC *)&temp_dc, 0, 0, wxCOPY, TRUE);
    rzRules->chart->pdc->Blit(xo, yo, sx, sy, (wxDC *)&temp_dc, 0, 0, wxOR);
    temp_dc_full.SelectObject(wxNullBitmap);

    rzRules->chart->pswc->Pause();

}    // else

*/



/*
    gluTessBeginPolygon(tobj,NULL);

    gluTessBeginContour(tobj);
    ppt  = rzRules->obj->geoPt;
//   ppt += (rzRules->obj->npt-1) * sizeof(pt*);
//   ppt3 = (pt3*)ppt;
    ppt3 = p = g_new0(pt3,npt);
    printf("AC contour: %d ",npt);
    for (i=0;i&lt;npt;++i){
    ppt3->x = ppt->x;
    ppt3->y = ppt->y;
    ppt3->z = 0.0;
//     printf("x:%f y:%f z:%f\n",ppt3->x,ppt3->y,ppt3->z);

    gluTessVertex(tobj,(GLdouble*)ppt3,(GLdouble*)ppt3);
    ++ppt;
    ++ppt3;
}
    gluTessEndContour(tobj);
*/
/*
   // holes
    ring = rzRules->obj->ring;
    while (ring){
    if (!ringArray)
    ringArray = g_ptr_array_new();

    gluTessBeginContour(tobj);

    npt  = ring->npt;
    ppt  = ring->geoPt;
    ppt3 = r = g_new0(pt3,npt);
    g_ptr_array_add(ringArray,r);
    printf("AC: %d\n",ring->npt);
    for (i=0;i&lt;ring->npt;++i){
    ppt3->x = ppt->x;
    ppt3->y = ppt->y;
    ppt3->z = 0.0;

         //printf("%g,%g\n",ppt->x,ppt->y);
    gluTessVertex(tobj,(GLdouble*)ppt3,(GLdouble*)ppt3);
    ++ppt;
    ++ppt3;
}
    gluTessEndContour(tobj);
    ring = ring->ring;
}



    gluTessEndPolygon(tobj);

    g_free(p);

    if (ringArray)
    g_ptr_array_free(ringArray, FALSE);

    printf("AC drawn\n");

*/
    return 1;
}




void RenderFilledPolygon(wxDC *pdc, s57chart *chart, color *c,
                         pt *geoPt_list, int npt, wxBoundingBox& BBView)
{
//CPLError((CPLErr)0, 0, "Ply npt %d\n", npt);

    int hp = 0;
    if(npt > 1000)
        hp++;

    pt *geor = geoPt_list;
    wxPoint *ptp = (wxPoint *)malloc(npt * sizeof(wxPoint));
    wxPoint *pr = ptp;
    wxPoint p;
    for(int i=0 ; i<npt ; i++)
    {
        chart->GetPointPix(geor->y, geor->x, pr);
        pr++;
        geor++;
    }


    if(hp)
    {
        wxColour color(255,0,0);
        wxBrush *pthisbrush = wxTheBrushList->FindOrCreateBrush(color, wxSOLID);
        wxPen *pthispen = wxThePenList->FindOrCreatePen(color, 1, wxSOLID);
        pdc->SetPen(*pthispen);
        pdc->SetBrush(*pthisbrush);

        gpc_polygon *ClipResult;
//              ClipResult = ClipPoly(npt,geoPt_list, BBView);

        if(0 /*ClipResult->num_contours == 1*/)
        {
            wxPoint *ptp = (wxPoint *)malloc(npt * sizeof(wxPoint));
            wxPoint *pr = ptp;

            gpc_vertex_list *pvl = ClipResult->contour;
            double *pd = (double *)pvl->vertex;
            float x,y;

            for(int i=0 ; i<pvl->num_vertices ; i++)
            {
                x = *pd++;
                y = *pd++;

                chart->GetPointPix(y, x, pr);
                pr++;
            }

            pdc->DrawLines(pvl->num_vertices, ptp);



        }

        else
        {
            pdc->DrawLines(npt, ptp);
        }
    }
    else
    {
        wxColour color(c->R, c->G, c->B);
        wxBrush *pthisbrush = wxTheBrushList->FindOrCreateBrush(color, wxSOLID);
        wxPen *pthispen = wxThePenList->FindOrCreatePen(color, 1, wxSOLID);

        pdc->SetPen(*pthispen);
        pdc->SetBrush(*pthisbrush);
        pdc->DrawPolygon(npt, ptp);
    }

    free(ptp);
}



int inpoly(wxPoint *ppoly,int npoints, int xt, int yt)
{
    int xnew,ynew;
    int xold,yold;
    int x1,y1;
    int x2,y2;
    int i;
    int inside=0;

    if (npoints < 3) {
        return(0);
    }
    xold=ppoly[npoints-1].x;
    yold=ppoly[npoints-1].y;
    for (i=0 ; i < npoints ; i++) {
        xnew=ppoly[i].x;
        ynew=ppoly[i].y;
        if (xnew > xold) {
            x1=xold;
            x2=xnew;
            y1=yold;
            y2=ynew;
        }
        else {
            x1=xnew;
            x2=xold;
            y1=ynew;
            y2=yold;
        }
        if ((xnew < xt) == (xt <= xold)
             /* edge "open" at one end */
             && ((long)yt-(long)y1)*(long)(x2-x1)
             < ((long)y2-(long)y1)*(long)(xt-x1)) {
            inside=!inside;
             }
             xold=xnew;
             yold=ynew;
    }
    return(inside);
}




int FindDCPointInPoly(wxPoint *presult, wxDC *pdc, s57chart *chart, pt *geoPt_list, int npt)
{
    int w, h;
    pdc->GetSize(&w,&h);

    float plat, plon;

    wxPoint *ptp = (wxPoint *)malloc(npt * sizeof(wxPoint));
    wxPoint *pr = ptp;
    wxPoint p;
    for(int i=0 ; i<npt ; i++)
    {
        plat = geoPt_list->y;
        plon = geoPt_list->x;

        chart->GetPointPix(plat, plon, &p);

        *pr = p;

        pr++;
        geoPt_list++;
    }

    int x,y;
    for( x = 1 ; x < w ; x++)
    {
        for( y = 1 ; y < h ; y++)
        {
            if(inpoly(ptp, npt, x, y))
            {
                if(inpoly(ptp, npt, x, y+1))
                {
                    presult->x = x;
                    presult->y = y+1;
                    goto gotit;
                }
            }
        }
    }

gotit:


        return 1;


}




#endif

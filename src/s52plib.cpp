/******************************************************************************
 * $Id: s52plib.cpp,v 1.14 2008/03/30 22:17:41 bdbcat Exp $
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
<<<<<<< s52plib.cpp
 * $Log: s52plib.cpp,v $
 * Revision 1.14  2008/03/30 22:17:41  bdbcat
 * Optimize HPGL cacheing
 *
=======
 * $Log: s52plib.cpp,v $
 * Revision 1.14  2008/03/30 22:17:41  bdbcat
 * Optimize HPGL cacheing
 *
 * Revision 1.13  2008/01/12 06:24:20  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.12  2008/01/11 01:39:59  bdbcat
 * Update for Mac OSX
 *
>>>>>>> 1.13
 * Revision 1.11  2008/01/10 03:37:47  bdbcat
 * Update for Mac OSX
 *
 * Revision 1.9  2007/06/10 02:33:11  bdbcat
 * Cleanup
 *
 * Revision 1.8  2007/05/03 13:23:56  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.7  2007/03/02 01:59:23  dsr
 * Convert to UTM Projection
 *
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
#include "cutil.h"
#include "s52utils.h"

#include <stdlib.h>                             // 261, min() becomes __min(), etc.

#include "wx/image.h"                   // Missing from wxprec.h

#ifndef __WXMSW__
#ifndef __WXOSX__             // begin rms
#include <malloc.h>
#endif                                    // end rms
#endif

extern s52plib          *ps52plib;

extern bool GetDoubleAttr(S57Obj *obj, char *AttrName, double &val);

CPL_CVSID("$Id: s52plib.cpp,v 1.14 2008/03/30 22:17:41 bdbcat Exp $");

//-----------------------------------------------------------------------------
//      s52plib implementation
//-----------------------------------------------------------------------------
s52plib::s52plib(const wxString& PLPath, const wxString& PLLib, const wxString& PLCol)

{
//      Set up some buffers, etc...
      pBuf = buffer;
      n_colTables = 0;

      pOBJLArray = new wxArrayPtrVoid;

      m_bOK = S52_load_Plib(PLPath, PLLib, PLCol);

      pSmallFont = wxTheFontList->FindOrCreateFont(16, wxDEFAULT,wxNORMAL, wxBOLD,
              FALSE, wxString(_T("Eurostile Extended")));

      m_bShowS57Text = false;
      m_ColorScheme = S52_DAY_BRIGHT;

      _symb_symR = NULL;
      bUseRasterSym = false;

      //      Sensible defaults
      m_nSymbolStyle = PAPER_CHART;
      m_nBoundaryStyle = PLAIN_BOUNDARIES;
      m_nDisplayCategory = OTHER;

      UpdateMarinerParams();

      ledge = new int[2000];
      redge = new int[2000];
}




s52plib::~s52plib()
{
      if(m_bOK)
         S52_flush_Plib();

//      Free the OBJL Array Elements
      for(unsigned int iPtr = 0 ; iPtr < pOBJLArray->GetCount() ; iPtr++)
          free(pOBJLArray->Item(iPtr));

      delete pOBJLArray;


      delete ledge;
      delete redge;

}


/*
    Update the S52 Conditional Symbology Parameter Set to reflect the
    current state of the library member options.
*/

void s52plib::UpdateMarinerParams(void)
{

    //      Symbol Style
    if(SIMPLIFIED == m_nSymbolStyle)
        S52_setMarinerParam(S52_MAR_SYMPLIFIED_PNT, 1.0);
    else
        S52_setMarinerParam(S52_MAR_SYMPLIFIED_PNT, 0.0);

    //      Boundary Style
    if(SYMBOLIZED_BOUNDARIES == m_nBoundaryStyle)
        S52_setMarinerParam(S52_MAR_SYMBOLIZED_BND, 1.0);
    else
        S52_setMarinerParam(S52_MAR_SYMBOLIZED_BND, 0.0);

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

int s52plib::LoadColors(const wxString& ColorFile)
{
   FILE         *fp;
   int  ret = 0;
   char         buffer[1024];
   char *pBuf = (char *)&buffer[0];
   color c1;
   color *c2;
   int R,G,B;
   colTable *ct = (colTable *)(_colTables->Item(0));  //&g_array_index(_colTables, colTable, 0);
   colTable *ctp;

   int colIdx = 0;
   char TableName[80];
   float x, y, Y;
        char *pBuft;

        fp = fopen(ColorFile.mb_str(), "r");
   if (fp == NULL)
   {
       wxString msg(_T("ERROR unable to open color file:"));
       msg.Append(*ColorFile);
       wxLogMessage(msg);
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
                   if(!strcmp(TableName, ctp->tableName->mb_str()))
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
                    wxString msg(_T("Color translation failed...file, ColorName"));
                    msg.Append(*ColorFile);
                    msg.Append(_T("  "));
                    msg.Append(wxString(c1.colName, wxConvUTF8));
                    wxLogMessage(msg);
                }

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
      case SIMPLIFIED:                  return pointSimplLUPArray;
      case PAPER_CHART:                 return pointPaperLUPArray;
      case LINES:                       return lineLUPArray;
      case PLAIN_BOUNDARIES:            return areaPlaineLUPArray;
      case SYMBOLIZED_BOUNDARIES:       return areaSymbolLUPArray;
      default:                          return NULL;
//          wxLogMessage(_T("S52:_selctLUP() ERROR"));
   }

   return NULL;
}



extern Cond condTable[];



// get LUP with "best" Object attribute match
LUPrec *s52plib::FindBestLUP(wxArrayPtrVoid *nameMatch, char *objAtt,
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
                                 if (0 == strncmp(LATTC.mb_str(), currATT,6)){
                                        //OK we have an attribute match
                                        //checking attribute value
                                        S57attVal *v;
#define BOOL bool
                                         BOOL attValMatch = FALSE;

                                        // special case (i)
                                        if (LATTC[6] == ' ')  // use any value
                                           attValMatch = TRUE;

                                        // special case (ii)
                              if ( strncmp(LUPtmp->OBCL, "DEPARE", 6))
                                  {
                                        if (LATTC[6] == '?')  // match if value is unknown
                                           attValMatch = TRUE;          // OGR bug here ???
                                  }

                                        v = (objAttVal->Item(attIdx));


                                        switch(v->valType){
                                           case OGR_INT:{    // S57 attribute type 'E' enumerated, 'I' integer
                                        int a;
                                                         sscanf(LATTC.mb_str() + 6, "%d", &a);
                                                         if (a == *(int*)(v->value))
                                                                attValMatch = TRUE;
                                        break;
                                                  }

                                           case OGR_INT_LST:{   // S57 attribute type 'L' list: comma separated integer
                                        int a;
                                                         char *s = (char *)(LATTC.mb_str() + 6);
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
                                                        if (LATTC[6] != '?')
                                                        {
                                                                sscanf(LATTC.mb_str() + 6, "%f", &a);
                                                                if (a == *(float*)(v->value))
                                                                        attValMatch = TRUE;
                                                        }
                                        break;
                                                  }

                                           case OGR_STR:{   // S57 attribute type'A' code string, 'S' free text
                                                        int a;                // Attribute value from LUP
                                                        char *s = (char *)(LATTC.mb_str() + 6);
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

Rules *s52plib::StringToRules(const wxString& str_in)
{
    char *str0 = (char *)calloc(str_in.Len()+1, 1);
    strncpy(str0, str_in.mb_str(), str_in.Len());
    char *str = str0;
//    char *str = (char *)str_in;

       Rules *top;
       Rules *last;
       char strk[20];

       Rules *r = (Rules*)calloc(1, sizeof(Rules));
       top = r;
       last = top;

       r->INST0 = str0;                 // save the head for later free

       while (*str != '\0')
       {
           if(r->ruleType)              // in the loop, r has been used
           {
               r = (Rules*)calloc(1, sizeof(Rules));
               last->next = r;
               last = r;
           }


      // parse Symbology instruction in string

      // Special Case for MultPoint Soundings
           INSTRUCTION("MP",RUL_MUL_SG) SCANFWRD }

      // SHOWTEXT
            INSTRUCTION("TX",RUL_TXT_TX) SCANFWRD }

            INSTRUCTION("TE",RUL_TXT_TE) SCANFWRD }

      // SHOWPOINT

            if(0==strncmp("SY",str,2))
            {
                str+=3;
                r->ruleType = RUL_SYM_PT;
                r->INSTstr  = str;

                strncpy(strk, str, 8);
                strk[8]=0;
                wxString key(strk,wxConvUTF8);

                r->razRule = (*_symb_sym)[key];

                if (r->razRule == NULL)
                    r->razRule = (*_symb_sym)[_T("QUESMRK1")];

                SCANFWRD
            }


      // SHOWLINE
            INSTRUCTION("LS",RUL_SIM_LN) SCANFWRD }

            INSTRUCTION("LC",RUL_COM_LN)
                    strncpy(strk, str, 8);
                    strk[8]=0;
                    wxString key(strk,wxConvUTF8);

                  r->razRule = (*_line_sym)[key];

                  if (r->razRule == NULL)
                        r->razRule = (*_symb_sym)[_T("QUESMRK1")];
            SCANFWRD
            }

      // SHOWAREA
            INSTRUCTION("AC",RUL_ARE_CO) SCANFWRD }

            INSTRUCTION("AP",RUL_ARE_PA)
                    strncpy(strk, str, 8);
                    strk[8]=0;
                    wxString key(strk,wxConvUTF8);
                    key += 'R';

                    r->razRule = (*_patt_sym)[key];
                    if (r->razRule == NULL)
                        r->razRule = (*_patt_sym)[_T("QUESMRK1V")];
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
                wxString index(stt, wxConvUTF8);
                r->razRule = (*_cond_sym)[index];
                if (r->razRule == NULL)
                    r->razRule = (*_cond_sym)[_T("QUESMRK1")];
                SCANFWRD
            }

      ++str;
   }

//  If it should happen that no rule is built, delete the initially allocated rule
   if(0 == top->ruleType)
    {
        if(top->INST0)
            free(top->INST0);

        free(top);

        top = NULL;
    }

//   Traverse the entire rule set tree, pruning after first unallocated (dead) rule
    r = top;
    while(r)
    {
        if(0 == r->ruleType)
        {
            free(r);
            last->next = NULL;
            break;
        }

        last = r;
        Rules *n = r->next;
        r = n;
    }


//    free(str0);
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
       Rules *top  = StringToRules(*LUP->INST);
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

int s52plib::ReadS52Line( char *pBuffer, char *delim, int nCount, FILE *fp )
{
   int ret;

   ret =  fscanf( fp, delim, pBuffer);

   fgetc(fp);

   if (nCount)  // skip \n
      fgetc(fp);

   return ret;
}


int s52plib::ChopS52Line(char *pBuffer, char c)
{
   int i;

   for (i=0; pBuffer[i] != '\0'; ++i)
      if ( pBuffer[i] == '\037' )
         pBuffer[i] = c;

   return i;
}

int s52plib::ParsePos(position *pos, char *buf, bool patt)
{
   if (patt)
   {
      sscanf(buf,"%5d%5d",&pos->minDist.PAMI,&pos->maxDist.PAMA);
      buf += 10;
   }

   sscanf(buf, "%5d%5d%5d%5d%5d%5d",&pos->pivot_x.PACL,&pos->pivot_y.PARW,
                                    &pos->bnbox_w.PAHL,&pos->bnbox_h.PAVL,
                                    &pos->bnbox_x.PBXC,&pos->bnbox_y.PBXR);
   return 1;
}


int s52plib::ParseLBID(FILE *fp)
{
   return 0;
}

int s52plib::ParseCOLS(FILE *fp)
{
   int ret;
   //colTable ct;
   colTable *ct = new colTable;

   // get color table name
    ChopS52Line( pBuf, '\0' );

    ct->tableName = new wxString(pBuf+19,  wxConvUTF8);
   ct->color     = new wxArrayPtrVoid;

   _colTables->Add((void *)ct);
   n_colTables++;

   // read color
   ret  = ReadS52Line( pBuf, NEWLN, 0,fp);
   while ( 0 != strncmp(pBuf, "****",4)){
      color *c = new color;
      ChopS52Line( pBuf, ' ' );
      strncpy(c->colName, pBuf+9, 5);
      sscanf(pBuf+14,"%f %f %f",&c->x,&c->y,&c->L);


      ct->color->Add(c);
      ret  = ReadS52Line( pBuf, NEWLN, 0,fp);
   }
   return ret;
}


#define MOD_REC(str)    if(0==strncmp(#str,pBuf,4))
int s52plib::ParseLUPT(FILE *fp)
{
   int    ret;

   BOOL    inserted = FALSE;

   LUPrec  *LUP = (LUPrec*)calloc(1, sizeof(LUPrec));
   pAlloc->Add(LUP);

   LUP->DISC = (enum _DisCat)OTHER;                                     // as a default

   sscanf(pBuf+11, "%d", &LUP->RCID);

   //   Debug hook
//   if(LUP->RCID == 855)
//      int uuip = 8;

   strncpy(LUP->OBCL, pBuf+19, 6);

//   if(!strncmp(LUP->OBCL, "TSSLPT", 6))
//         int qewr = 9;

   LUP->FTYP = (enum _Object_t)pBuf[25];
   LUP->DPRI = (enum _DisPrio)pBuf[30];
   LUP->RPRI = (enum _RadPrio)pBuf[31];
   LUP->TNAM = (enum _LUPname)pBuf[36];

   ret  = ReadS52Line( pBuf, NEWLN, 0,fp);

   do{
      MOD_REC(ATTC){
         if ('\037' != pBuf[9])                        // could be empty!
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

                ChopS52Line( pBuf, ' ' );
                LUP->ATTC = new wxString(pBuf+9, wxConvUTF8);
         }
      }

      MOD_REC(INST) LUP->INST = new wxString(pBuf+9, wxConvUTF8);
      MOD_REC(DISC) LUP->DISC = (enum _DisCat)pBuf[9];
      MOD_REC(LUCM) sscanf(pBuf+9, "%d",&LUP->LUCM);

      MOD_REC(****){

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
                                DestroyLUP(pLUPCandidate);            // empties the LUP
                                pLUPARRAYtyped->Remove(pLUPCandidate);
                                break;
                        }
                        index++;
                }


                pLUPARRAYtyped->Add(LUP);

          inserted = TRUE;

      }         // MOD_REC

         ret = ReadS52Line( pBuf, NEWLN, 0,fp);

   }while(inserted == FALSE);

   return 1;
}


int s52plib::ParseLNST(FILE *fp)
{
   int  ret;

   char strk[20];

   BOOL inserted = FALSE;
   Rule *lnstmp  = NULL;
   Rule *lnst = (Rule*)calloc(1, sizeof(Rule));
   pAlloc->Add(lnst);

   lnst->exposition.LXPO = new wxString;
   wxString LVCT;
   wxString LCRF;

   sscanf(pBuf+11, "%d", &lnst->RCID);

   ret  = ReadS52Line( pBuf, NEWLN, 0,fp);
   do{
      MOD_REC(LIND){
         strncpy(lnst->name.LINM, pBuf+9, 8); // could be empty!
         ParsePos(&lnst->pos.line, pBuf+17, FALSE);
      }

      MOD_REC(LXPO) lnst->exposition.LXPO->Append(wxString(pBuf+9, wxConvUTF8 ));
      MOD_REC(LCRF) LCRF.Append( wxString(pBuf+9, wxConvUTF8 ));       // CIDX + CTOK
      MOD_REC(LVCT) LVCT.Append( wxString(pBuf+9, wxConvUTF8 ));
        MOD_REC(****){

            lnst->vector.LVCT = (char *)calloc(LVCT.Len()+1, 1);
            strncpy(lnst->vector.LVCT, LVCT.mb_str(), LVCT.Len());

            lnst->colRef.LCRF = (char *)calloc(LCRF.Len()+1, 1);
            strncpy(lnst->colRef.LCRF, LCRF.mb_str(), LCRF.Len());

         // check if key already there
                 strncpy(strk, lnst->name.LINM, 8);
                 strk[8]=0;
                 wxString key(strk,wxConvUTF8);

                   //wxString key((lnst->name.LINM), 8);
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
      ret  = ReadS52Line( pBuf, NEWLN, 0,fp);
      ChopS52Line( pBuf, '\0' );
   }while( inserted == FALSE);

   return ret;
}


//void DestroyPatternRuleNode(Rule *pR);

int s52plib::ParsePATT(FILE *fp)
{
   int  ret;

   int bitmap_width;
   char pbm_line[200];                  // max bitmap width...
   char strk[20];

   BOOL inserted = FALSE;
   Rule *pattmp  = NULL;
   Rule *patt = (Rule*)calloc(1,sizeof(Rule));
   pAlloc->Add(patt);

   patt->exposition.PXPO  = new wxString;
   patt->bitmap.PBTM     = new wxString;
   wxString PVCT;
   wxString PCRF;

   sscanf(pBuf+11, "%d", &patt->RCID);

   ret  = ReadS52Line( pBuf, NEWLN, 0,fp);

   do{
      MOD_REC(PATD){
            strncpy(patt->name.PANM, pBuf+9, 8);
            patt->definition.PADF = pBuf[17];
            patt->fillType.PATP  = pBuf[18];
            patt->spacing.PASP   = pBuf[21];
            ParsePos(&patt->pos.patt, pBuf+24, TRUE);
      }

      MOD_REC(PXPO) patt->exposition.PXPO->Append( wxString(pBuf+9, wxConvUTF8) );
      MOD_REC(PCRF) PCRF.Append( wxString(pBuf+9, wxConvUTF8) );  // CIDX+CTOK
      MOD_REC(PVCT) PVCT.Append( wxString(pBuf+9, wxConvUTF8) );

      MOD_REC(PBTM){
                bitmap_width = patt->pos.patt.bnbox_w.SYHL;
//                if(bitmap_width > 200)
//                        wxLogMessage(_T("ParsePatt....bitmap too wide."));
                strncpy(pbm_line, pBuf+9, bitmap_width);
                pbm_line[bitmap_width] = 0;
                patt->bitmap.SBTM->Append( wxString(pbm_line, wxConvUTF8) );
        }


      MOD_REC(****){

          patt->vector.PVCT = (char *)calloc(PVCT.Len()+1, 1);
          strncpy(patt->vector.PVCT, PVCT.mb_str(), PVCT.Len());

          patt->colRef.PCRF = (char *)calloc(PCRF.Len()+1, 1);
          strncpy(patt->colRef.PCRF, PCRF.mb_str(), PCRF.Len());

         // check if key already there
          strncpy(strk, patt->name.PANM, 8);
          strk[8]=0;
          wxString key(strk, wxConvUTF8);

          char key_plus[20];
          strncpy(key_plus, &patt->definition.SYDF, 1);
          key_plus[1] = 0;
          key += wxString(key_plus, wxConvUTF8);

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
      ret  = ReadS52Line( pBuf, NEWLN, 0,fp);
      ChopS52Line( pBuf, '\0' );

   }while( inserted == FALSE);

   return ret;
}



int s52plib::ParseSYMB(FILE *fp, RuleHash *pHash)
{
   int  ret;

   int bitmap_width;
   char pbm_line[200];                  // max bitmap width...
   BOOL inserted = FALSE;
//   Rule *symbtmp  = NULL;
   Rule *symb = (Rule*)calloc(1,sizeof(Rule));
   pAlloc->Add(symb);
   Rule *symbtmp = NULL;

   symb->exposition.SXPO = new wxString;
   symb->bitmap.SBTM     = new wxString;
   wxString SVCT;
   wxString SCRF;

   sscanf(pBuf+11, "%d", &symb->RCID);

   // debug
 //  if (symb->RCID == 9504)
//              int gghj = 5;

   ret  = ReadS52Line( pBuf, NEWLN, 0,fp);

   do{
      MOD_REC(SYMD){
            strncpy(symb->name.SYNM, pBuf+9, 8);
            symb->definition.SYDF = pBuf[17];
            ParsePos(&symb->pos.symb, pBuf+18, FALSE);
        }

        MOD_REC(SXPO) symb->exposition.SXPO->Append( wxString(pBuf+9, wxConvUTF8) );

        MOD_REC(SBTM){
                bitmap_width = symb->pos.symb.bnbox_w.SYHL;
                if(bitmap_width > 200)
                    wxLogMessage(_T("ParseSymb....bitmap too wide."));
                strncpy(pbm_line, pBuf+9, bitmap_width);
                pbm_line[bitmap_width] = 0;
                symb->bitmap.SBTM->Append( wxString(pbm_line, wxConvUTF8) );
        }

        MOD_REC(SCRF)     SCRF.Append( wxString(pBuf+9, wxConvUTF8) );  // CIDX+CTOK

        MOD_REC(SVCT)     SVCT.Append( wxString(pBuf+9, wxConvUTF8) );

          if((0==strncmp("****",pBuf,4)) || (ret == -1))
          {
              symb->vector.SVCT = (char *)calloc(SVCT.Len()+1, 1);
              strncpy(symb->vector.SVCT, SVCT.mb_str(), SVCT.Len());

              symb->colRef.SCRF = (char *)calloc(SCRF.Len()+1, 1);
              strncpy(symb->colRef.SCRF, SCRF.mb_str(), SCRF.Len());

            // Create a key
              char keyt[20];
              strncpy(keyt, symb->name.SYNM, 8);
              keyt[8]=0;
              wxString key(keyt, wxConvUTF8);

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
      ret  = ReadS52Line( pBuf, NEWLN, 0,fp);
      ChopS52Line( pBuf, '\0' );

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


   fp = fopen(PLib.mb_str(), "r");

   if (fp == NULL)
   {
       wxString msg(_T("S52PLIB: Cannot open S52 rules file:"));
       msg.Append(*PLib);
       wxLogMessage(msg);
       return 0;
   }

   _colTables = new wxArrayPtrVoid;
   pAlloc = new wxArrayPtrVoid;


   //   Create the Rule Lookup Hash Tables
   _line_sym      = new RuleHash;    // line
   _patt_sym      = new RuleHash;    // pattern
   _symb_sym      = new RuleHash;    // symbol
   _cond_sym      = new RuleHash;    // conditional



   //   Build the initially empty sorted arrays of LUP Records, per LUP type.
   //   Sorted on object name, e.g. ACHARE.  Why sorted?  Helps in the S52_LUPLookup method....
   pointSimplLUPArray    = new wxArrayOfLUPrec(CompareLUPObjects);   // point simplified
   pointPaperLUPArray    = new wxArrayOfLUPrec(CompareLUPObjects);   // point traditional(paper)
   lineLUPArray          = new wxArrayOfLUPrec(CompareLUPObjects);   // lines;
   areaPlaineLUPArray    = new wxArrayOfLUPrec(CompareLUPObjects);   // area plain boundary
   areaSymbolLUPArray    = new wxArrayOfLUPrec(CompareLUPObjects);   // area symbolized boundary
   condSymbolLUPArray    = new wxArrayOfLUPrec(CompareLUPObjects);   // dynamic Cond Sym LUPs



        while( 1 == (nRead = ReadS52Line(pBuf,NEWLN,0,fp)) ){
      // !!! order important !!!
      MOD_REC(LBID) ParseLBID(fp);
      MOD_REC(COLS) ParseCOLS(fp);
      MOD_REC(LUPT) ParseLUPT(fp);
      MOD_REC(LNST) ParseLNST(fp);
      MOD_REC(PATT) ParsePATT(fp);
      MOD_REC(SYMB) ParseSYMB(fp, _symb_sym);

      MOD_REC(0001) continue;
      MOD_REC(****) continue;

   }
   fclose(fp);

   //   Initialize the _cond_sym Hash Table from the jump table found in S52CNSY.CPP
   //   Hash Table indices are the literal CS Strings, e.g. "RESARE02"
   //   Hash Results Values are the Rule *, i.e. the CS procedure entry point

   for(int i=0 ; condTable[i].condInst != NULL; ++i)
   {
       wxString index(condTable[i].name, wxConvUTF8);
       (*_cond_sym)[index] = (Rule *)(condTable[i].condInst);
   }



//   _CIE2RGB();

   LoadColors(PCol);
//      RGBFROMDAT();

   return 1;                    //_table_size;
}

void s52plib::DestroyPatternRuleNode(Rule *pR)
{
    if(pR)
    {
            if(pR->exposition.LXPO)
                    delete pR->exposition.LXPO;

            free( pR->vector.LVCT );

            if(pR->bitmap.SBTM)
                    delete pR->bitmap.SBTM;

            free( pR->colRef.SCRF);

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
                    free(pp->pix_buff);
                    delete pp;
                }
            }
    }
}


void s52plib::DestroyRuleNode(Rule *pR)
{
    if(pR)
    {

        if(pR->exposition.LXPO)
            delete pR->exposition.LXPO;

        free( pR->vector.LVCT);

        if(pR->bitmap.SBTM)
            delete pR->bitmap.SBTM;

        free( pR->colRef.SCRF);

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


void s52plib::DestroyRules(RuleHash *rh)
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

            free( pR->vector.LVCT );

            if(pR->bitmap.SBTM)
                delete pR->bitmap.SBTM;

            free( pR->colRef.SCRF );

            if(pR->pixelPtr)
            {
//                if(pR->definition.PADF == 'R')
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




void s52plib::DestroyPattRules(RuleHash *rh)
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

                        free( pR->vector.LVCT );

                        if(pR->bitmap.SBTM)
                                delete pR->bitmap.SBTM;

                        free( pR->colRef.SCRF );

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
                                free(pp->pix_buff);
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

            if(top->INST0)
                free(top->INST0);           // free the Instruction string head

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


void s52plib::ClearCNSYLUPArray(void)
{
      for(unsigned int i = 0 ; i < condSymbolLUPArray->GetCount() ; i++)
            DestroyLUP(condSymbolLUPArray->Item(i));

      condSymbolLUPArray->Clear();
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



LUPrec *s52plib::S52_LUPLookup(LUPname LUP_Name, const char * objectName, S57Obj *pObj, bool bStrict)

{
   LUPrec *LUP = NULL;
        LUPrec *LUPCandidate;


        nameMatch = new wxArrayPtrVoid;

//        wxArrayOfLUPrec *la = (wxArrayOfLUPrec *)(LUPTable[table_t]);
        wxArrayOfLUPrec *la = SelectLUPARRAY(LUP_Name);     //LUPname

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


        char *temp;

        if(ocnt == 0)
                goto BAILOUT;

        temp = (char *)calloc(pObj->attList->Len()+1, 1);
        strncpy(temp, pObj->attList->mb_str(), pObj->attList->Len());

        LUP = FindBestLUP(nameMatch,temp, pObj->attVal, bStrict);

        free(temp);


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
        char *attList = (char *)calloc(obj->attList->Len()+1, 1);
        strncpy(attList, obj->attList->mb_str(), obj->attList->Len());
//        char *attList = (char *)(obj->attList->);        //attList is wxString

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
        {
            free(attList);
                return str;
        }

//      using idx to get the attribute value
        wxArrayOfS57attVal      *pattrVal = obj->attVal;

        S57attVal *v = pattrVal->Item(idx);

        char *val = (char *)(v->value);

        str.Append(wxString(val,wxConvUTF8));

        free(attList);
        return str;
}

/*
bool GetFloatAttr(S57Obj *obj, char *AttrName, float &val)
{
    char *attList = (char *)calloc(obj->attList->Len()+1, 1);
    strncpy(attList, obj->attList->mb_str(), obj->attList->Len());
//    char *attList = (char *)(obj->attList->);        //attList is wxString

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

    if(!*patl)                                                   // Requested Attribute not found
    {
        free(attList);
        return false;                                           // so don't return a value
    }

//      using idx to get the attribute value
    wxArrayOfS57attVal      *pattrVal = obj->attVal;

    S57attVal *v = pattrVal->Item(idx);
    val = *(float*)(v->value);

    free(attList);
    return true;
}


bool GetDoubleAttr(S57Obj *obj, char *AttrName, double &val)
{
    char *attList = (char *)calloc(obj->attList->Len()+1, 1);
    strncpy(attList, obj->attList->mb_str(), obj->attList->Len());

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

    if(!*patl)                                                   // Requested Attribute not found
    {
        free(attList);
        return false;                                           // so don't return a value
    }

//      using idx to get the attribute value
    wxArrayOfS57attVal      *pattrVal = obj->attVal;

    S57attVal *v = pattrVal->Item(idx);
    val = *(double*)(v->value);

    return true;
}
*/

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
// Todo parse value, including comma delimiters, pass to GetAttributeDecode,
        // and format str.  Think about cacheing this??
        if (!strncmp(buf, "NATSUR", 6))
        {

            wxString att(_T("NATSUR"));
//            wxString *pnat = rzRules->chart->GetAttributeDecode(att, 17);

//            int i = atoi(value.mb_str());

//            if ( 0 < i && i <= MAX_NATSUR)
//                strcpy(buf, natsur[i]);


        }
        else
        {
            strncpy(buf, value.mb_str(), vallen);            // value from ENC
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
        text->frmtd = new wxString(buf, wxConvUTF8);

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
        text->frmtd = new wxString(buf, wxConvUTF8);

    return text;
}

void RenderText(wxDC *pdc, wxFont *pFont, const wxString& str, int x, int y, int &dx, int &dy)
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
int s52plib::RenderTX(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
        if(!m_bShowS57Text)
                return 0;

        S52_Text *text = NULL;

//  Render text at declared x/y of object
        wxPoint r;
        rzRules->chart->GetPointPix(rzRules, rzRules->obj->y, rzRules->obj->x, &r);


        int dx, dy;
        text = S52_PL_parseTX(rzRules, rules, NULL);
        if(text)
        {
            wxString str(*text->frmtd);
            RenderText(pdc, pSmallFont, str, r.x + text->xoffs, r.y + text->yoffs, dx, dy);

                //  Update the object Bounding box if this object is a POINT object,
                //  so that subsequent drawing operations will redraw the item fully

                if(rzRules->obj->Primitive_type == GEO_POINT)
                {
                    double plat, plon;
                    rzRules->chart->GetPixPoint(r.x + text->xoffs, r.y + text->yoffs + dy, &plat, &plon, vp);
                    rzRules->obj->BBObj.SetMin(plon, plat);

                    rzRules->chart->GetPixPoint(r.x + text->xoffs + dx, r.y + text->yoffs, &plat, &plon, vp);
                    rzRules->obj->BBObj.SetMax(plon, plat);

                }

                delete text->frmtd;
                free(text);
        }

   return 1;
}


// Text formatted
int s52plib::RenderTE(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
        if(!m_bShowS57Text)
                return 0;

        S52_Text *text = NULL;

        //  Render text at declared x/y of object
        wxPoint r;
        rzRules->chart->GetPointPix(rzRules, rzRules->obj->y, rzRules->obj->x, &r);


        int dx, dy;
        text = S52_PL_parseTE(rzRules, rules, NULL);
        if(text)
        {
                wxString str(*text->frmtd);
                RenderText(pdc, pSmallFont, str, r.x + text->xoffs, r.y + text->yoffs, dx, dy);

                //  Update the object Bounding box if this object is a POINT object,
                //  so that subsequent drawing operations will redraw the item fully

                if(rzRules->obj->Primitive_type == GEO_POINT)
                {
                    double plat, plon;
                    rzRules->chart->GetPixPoint(r.x + text->xoffs, r.y + text->yoffs + dy, &plat, &plon, vp);
                    rzRules->obj->BBObj.SetMin(plon, plat);

                    rzRules->chart->GetPixPoint(r.x + text->xoffs + dx, r.y + text->yoffs, &plat, &plon, vp);
                    rzRules->obj->BBObj.SetMax(plon, plat);

                }


                delete text->frmtd;
                free(text);
        }

   return 1;
}

bool s52plib::RenderHPGLtoDC(char *str, char *col, wxDC *pdc, wxPoint &r, wxPoint &pivot, double rot_angle)
{
      int width = 1;
      double radius = 0.0;
      int    tessObj       = FALSE;
      int    polyMode      = FALSE;
      int    inBegEnd      = FALSE;
      color *newColor;
      float trans = 1.0;

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


   float fsf = 100 / canvas_pix_per_mm;
   int scaleFac = (int)floor(fsf);




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

      if (inBegEnd)
      {
            wxLogMessage(_T("bogus BegEnd in SW"));
            inBegEnd = FALSE;
      }

}

      // Pen Up
      else INST(PU)

            if (inBegEnd)
            {
            wxLogMessage(_T("bogus BegEnd in PU"));
            inBegEnd = FALSE;
            }

                        wxColour color(newColor->R, newColor->G, newColor->B);
                        wxPen *pthispen = wxThePenList->FindOrCreatePen(color, width, wxSOLID);

                        pdc->SetPen(*pthispen);
                        sscanf(str, "%u,%u", &x, &y);
                        x1 = x - pivot.x;
                        y1 = y - pivot.y;

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
            do
            {
                  if (*str == ';')
                        continue;

                  if (!inBegEnd){
                        inBegEnd = TRUE;
            }

            sscanf(str, "%u,%u", &x, &y);
            x2 = x - pivot.x;
            y2 = y - pivot.y;
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

            x1=x2;                  // set for pu;pd;pd....
            y1=y2;

            while(*str++ != ',' );                      // specs: could repeat x,y,x, ..
            while(*str   != ',' && *str != ';')str++;  // but never do!
            }while(*str != ';');           // outside poly mode

            if(0 != strncmp(str,";PD",3))
            { // not very smart!!
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

                        inBegEnd = FALSE;

                        while(*str != ';') ++str;

               // Arc Angle --never used!
                  }
                  else INST(AA)
                        wxLogMessage(_T("SEQuencer:_renderHPGL(): fixme AA instruction not implemented"));
                        inBegEnd = FALSE;
                  }
                  else
                  {
                        tessObj = TRUE;
                        inBegEnd = FALSE;
      }
}

            if (*str == '1')
            {   // sub poly --never used!
                  str++;
            }

            if (tessObj)
            {
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
                        x2 = x - pivot.x;
                        y2 = y - pivot.y;
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
            wxLogMessage(_T("SEQuencer:_renderHPGL(): fixme EP instruction not implemented "));
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
                        }
}

      // Symbol Call    --never used
      else INST(SC)
                        wxLogMessage(_T("SEQuencer:_renderHPGL(): fixme SC instruction not implemented "));
}
      ++str;

} /* while */

        return true;
}








bool s52plib::RenderHPGL(Rule *prule, wxDC *pdc, wxPoint &r, float rot_angle)
{

      float fsf = 100 / canvas_pix_per_mm;

      int width  = prule->pos.symb.bnbox_x.SBXC + prule->pos.symb.bnbox_w.SYHL;
      width *= 2;
      width = (int)(width/fsf);
      int height = prule->pos.symb.bnbox_y.SBXR + prule->pos.symb.bnbox_h.SYVL;
      height *= 2;
      height = (int)(height/fsf);

      int pivot_x = prule->pos.symb.pivot_x.SYCL;
      int pivot_y = prule->pos.symb.pivot_y.SYRW;

      //Instantiate the symbol if necessary
      if((prule->pixelPtr == NULL) || (prule->parm1 != m_ColorScheme))
      {
            wxBitmap *pbm = new wxBitmap(width, height);
            wxMemoryDC mdc;
            mdc.SelectObject(*pbm);
            mdc.SetBackground(wxBrush(wxColour(unused_color.R, unused_color.G, unused_color.B)));
            mdc.Clear();

            char *str = prule->vector.LVCT;
            char *col = prule->colRef.LCRF;
            wxPoint pivot(pivot_x, pivot_y);
            wxPoint r0((int)(pivot_x/fsf), (int)(pivot_y/fsf));
            RenderHPGLtoDC(str, col, &mdc, r0, pivot, (double)rot_angle);

            int bm_width  = (mdc.MaxX() - mdc.MinX()) + 1;
            int bm_height = (mdc.MaxY() - mdc.MinY()) + 1;
            int bm_orgx = wxMax(0, mdc.MinX());
            int bm_orgy = wxMax(0, mdc.MinY());

            mdc.SelectObject(wxNullBitmap);

            //          Get smallest containing bitmap
            wxBitmap *sbm = new wxBitmap(pbm->GetSubBitmap(wxRect(bm_orgx, bm_orgy, bm_width, bm_height)));

            delete pbm;

            //      Make the mask
            wxMask *pmask = new wxMask(*sbm,
                                        wxColour(unused_color.R, unused_color.G, unused_color.B));

            //      Associate the mask with the bitmap
            sbm->SetMask(pmask);

            // delete any old private data
            wxBitmap *pbmo = (wxBitmap *)(prule->pixelPtr);
            delete pbmo;

            //      Save the bitmap ptr and aux parms in the rule
            prule->pixelPtr = sbm;
            prule->parm1 = m_ColorScheme;
            prule->parm2 = bm_orgx- (int)(pivot_x/fsf);
            prule->parm3 = bm_orgy- (int)(pivot_y/fsf);
            prule->parm4 = (int)rot_angle;


      }               // instantiation

      //    If the rotation angle of the cached symbol is not equal to the request,
      //    then render the symbol directly in HPGL
      if((int)rot_angle != prule->parm4)
      {
            char *str = prule->vector.LVCT;
            char *col = prule->colRef.LCRF;
            wxPoint pivot(prule->pos.line.pivot_x.LICL, prule->pos.line.pivot_y.LIRW);
            RenderHPGLtoDC(str, col, pdc, r, pivot, (double)rot_angle);

            return true;
      }


        //      Now render the symbol from the cached bitmap

        //      Get the bitmap into a memory dc
      wxMemoryDC mdc;

      mdc.SelectObject((wxBitmap &)(*((wxBitmap *)(prule->pixelPtr))));

        //      Blit it into the target dc
      pdc->Blit(r.x + prule->parm2, r.y + prule->parm3, width, height, &mdc, 0, 0, wxCOPY,  true);

      mdc.SelectObject(wxNullBitmap);


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

/*
    wxString cstr(*prule->colRef.SCRF);
    unsigned int i = 0;

    char colname[6];
    while(i < (unsigned int)cstr.Len())
    {
            i++;
            wxString thiscolor = cstr(i, 5);

            strncpy(colname, thiscolor.mb_str(), 5);
            colname[5]=0;
            color *pColor =  S52_getColor(colname);

            pColorArray->Add((void *) pColor);

            i+=5;
    }
*/
    int i = 0;
    char *cstr = prule->colRef.SCRF;

    char colname[6];
    int nl = strlen(cstr);

    while(i < nl)
    {
        i++;

        strncpy(colname, &cstr[i], 5);
        colname[5]=0;
        color *pColor =  S52_getColor(colname);

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
int s52plib::RenderSY(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
    float angle = 0;
    double orient;

    //      Debug
//    if(!strncmp(rzRules->obj->FeatureName, "TSSLPT", 6))
//          int ggk = 3;

    if(rules->razRule != NULL)
    {
        if(GetDoubleAttr(rzRules->obj, "ORIENT", orient))
           angle = orient;

        if(!strncmp(rules->INSTstr, "LIGHTS0", 7))  // matches LIGHTS01 and 02
           angle = 135;


        //  Render symbol at object's x/y
        wxPoint r;
        rzRules->chart->GetPointPix(rzRules, rzRules->obj->y, rzRules->obj->x, &r);


        //  Render a raster or vector symbol, as specified by LUP rules
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

// Line Simple Style
int s52plib::RenderLS(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
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

                npt = pptg->pn_vertex[ic];
                wxPoint *ptp = (wxPoint *)malloc((npt + 1) * sizeof(wxPoint));
                wxPoint *pr = ptp;

                float *pf = &ppolygeo[ctr_offset];
                for(int ip=0 ; ip < npt ; ip++)
                {
                    float plon = *pf++;
                    float plat = *pf++;

                    rzRules->chart->GetPointPix(rzRules, plat, plon, pr);
                    pr++;
                }
                float plon = ppolygeo[ ctr_offset];             // close the polyline
                float plat = ppolygeo[ ctr_offset + 1];
                rzRules->chart->GetPointPix(rzRules, plat, plon, pr);


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

                    rzRules->chart->GetPointPix(rzRules, plat, plon, &p);

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
int s52plib::RenderLC(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{

        wxPoint   *ptp;
        int       npt;
        color     *c;
        int       w;
        wxPoint   r;

        int isym_len = rules->razRule->pos.line.bnbox_w.SYHL;
        float sym_len = isym_len * canvas_pix_per_mm / 100;
        float sym_factor = 1.0 ; ///1.50;                        // gives nicer effect


//      Create a pen for drawing adjustments outside of HPGL renderer
        char *tcolptr = rules->razRule->colRef.LCRF;
//        strncpy(tcolptr,rules->razRule->colRef.LCRF->mb_str(), 7);
//        tcolptr[8]=0;
//        char *tcolptr = (char *)(rules->razRule->colRef.LCRF->mb_str());
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

                    rzRules->chart->GetPointPix(rzRules, plat, plon, pr);
                    pr++;
                }
                float plon = ppolygeo[ ctr_offset];             // close the polyline
                float plat = ppolygeo[ ctr_offset + 1];
                rzRules->chart->GetPointPix(rzRules, plat, plon, pr);


                draw_lc_poly(pdc, ptp, npt + 1, sym_len, sym_factor, rules->razRule, vp);

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

                        rzRules->chart->GetPointPix(rzRules, plat, plon, &p);

                        *pr = p;

                        pr++;
                        ppt++;
                }


                draw_lc_poly(pdc, ptp, npt, sym_len, sym_factor, rules->razRule, vp);

                free(ptp);
        }

        return 1;
}


//      Render Line Complex Polyline

void s52plib::draw_lc_poly(wxDC *pdc, wxPoint *ptp, int npt,
                           float sym_len, float sym_factor, Rule *draw_rule, ViewPort *vp)
{
    wxPoint   r;
    int x0, y0, x1, y1;
    int xmin_ = 0;
    int xmax_ = vp->pix_width;
    int ymin_ = 0;
    int ymax_ = vp->pix_height;

    for(int iseg = 0 ; iseg < npt - 1 ; iseg++)
    {
          // Do not bother with segments that are invisible

        x0 = ptp[iseg].x;
        y0 = ptp[iseg].y;
        x1 = ptp[iseg+1].x;
        y1 = ptp[iseg+1].y;

        ClipResult res = cohen_sutherland_line_clip_i (&x0, &y0, &x1, &y1,
                      xmin_, xmax_, ymin_, ymax_);

        if(res == Invisible)
                continue;


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
                        char *str = draw_rule->vector.LVCT;
                        char *col = draw_rule->colRef.LCRF;
                        wxPoint pivot(draw_rule->pos.line.pivot_x.LICL, draw_rule->pos.line.pivot_y.LIRW);

                        RenderHPGLtoDC(str, col, pdc, r, pivot, (double)tdeg);


                        xs += sym_len * cth * sym_factor;
                        ys += sym_len * sth * sym_factor;
                        s += sym_len * sym_factor;
                }
                pdc->DrawLine((int)xs, (int)ys, ptp[iseg+1].x, ptp[iseg+1].y);
            }
        }
    }
}




// Multipoint Sounding
int s52plib::RenderMPS(ObjRazRules *rzRules, Rules *rules, ViewPort *vp)
{
    if(!m_bShowSoundg)
        return 0;

    int npt = rzRules->obj->npt;

    wxPoint p;
    double *pd = rzRules->obj->geoPtz;            // the SM points
    double *pdl = rzRules->obj->geoPtMulti;       // and corresponding lat/lon

    for(int ip=0 ; ip<npt ; ip++)
    {
        double east = *pd++;
        double nort = *pd++;;
        double depth = *pd++;

        ObjRazRules *point_rzRules = new ObjRazRules;
        *point_rzRules = *rzRules;              // take a copy of attributes, etc

        //  Need a new LUP
        LUPrec *NewLUP = new LUPrec;
        *NewLUP = *(rzRules->LUP);
        point_rzRules->LUP = NewLUP;

        //  Need a new S57Obj
        S57Obj *point_obj = new S57Obj;
        *point_obj = *(rzRules->obj);
        point_rzRules->obj = point_obj;

        //  Touchup the new items
        point_rzRules->obj->bCS_Added = false;
        point_rzRules->obj->bIsClone = true;

        point_rzRules->next = NULL;
        Rules *ru = StringToRules(_T("CS(SOUNDG03;"));
        point_rzRules->LUP->ruleList = ru;

        point_obj->x = east;
        point_obj->y = nort;
        point_obj->z = depth;

        double lon = *pdl++;
        double lat = *pdl++;
        point_obj->BBObj.SetMin(lon, lat);
        point_obj->BBObj.SetMax(lon, lat);

        _draw(pdc, point_rzRules, vp);

        delete ru;
        delete point_obj;
        delete point_rzRules;
        delete NewLUP;
    }

    return 1;
}










// Conditional Symbology
char *s52plib::RenderCS(ObjRazRules *rzRules, Rules *rules)
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

//  Debug Hook
//    if(!strncmp(rzRules->LUP->OBCL, "M_COVR", 6))
//        int yyrt = 4;

//    if(rzRules->obj->Index == 1706)
//          int rrt = 5;


        while (rules != NULL)
        {
                switch (rules->ruleType){
//                         case RUL_ARE_CO:       RenderAC(rzRules,rules, vp);break;             // AC
                        case RUL_TXT_TX:       RenderTX(rzRules,rules, vp);break;             // TX
                        case RUL_TXT_TE:       RenderTE(rzRules,rules, vp);break;             // TE
                        case RUL_SYM_PT:       RenderSY(rzRules,rules, vp);break;             // SY
                        case RUL_SIM_LN:       RenderLS(rzRules,rules, vp);break;             // LS
                        case RUL_COM_LN:       RenderLC(rzRules,rules, vp);break;             // LC
                        case RUL_MUL_SG:       RenderMPS(rzRules,rules, vp);break;            // MultiPoint Sounding

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
//                                        case RUL_ARE_CO:       RenderAC(rzRules,rules, vp);break;
                                        case RUL_TXT_TX:       RenderTX(rzRules,rules, vp);break;
                                        case RUL_TXT_TE:       RenderTE(rzRules,rules, vp);break;
                                        case RUL_SYM_PT:       RenderSY(rzRules,rules, vp);break;
                                        case RUL_SIM_LN:       RenderLS(rzRules,rules, vp);break;
                                        case RUL_COM_LN:       RenderLC(rzRules,rules, vp);break;
                                        case RUL_MUL_SG:       RenderMPS(rzRules,rules, vp);break;   // MultiPoint Sounding
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
int s52plib::dda_tri(wxPoint *ptp, color *c, render_canvas_parms *pb_spec, render_canvas_parms *pPatt_spec)
{
    unsigned char r, g, b;

    if(NULL != c)
    {
#ifdef ocpnUSE_ocpnBitmap
        r = c->R;
        g = c->G;
        b = c->B;
#else
        b = c->R;
        g = c->G;
        r = c->B;
#endif
    }

    //      Color Debug
/*    int fc = rand();
    b = fc & 0xff;
    g = fc & 0xff;
    r = fc & 0xff;
*/

    int color_int;
    if(NULL != c)
          color_int =  ((r) << 16) + ((g) << 8) + (b);

    //      Determine ymin and ymax indices

    int ymax = ptp[0].y;
    int ymin = ymax;
    int xmin, xmax, xmid, ymid;
    int imin = 0;
    int imax = 0;
    int imid;

    for(int ip=1 ; ip < 3 ; ip++)
    {
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

    xmax = ptp[imax].x;
    xmin = ptp[imin].x;
    xmid = ptp[imid].x;
    ymid = ptp[imid].y;


    //      Create edge arrays using fast integer DDA
    int m, x, dy, count;

// left edge
//    if((ptp[imin].y >= 0 ) && (ptp[imin].y < 1500))           // left begin point
//            ledge[ptp[imin].y] = ptp[imin].x;

    dy = (ymax - ymin);
    if(dy)
    {
            m = (xmax - xmin) << 16;
            m /= dy;

            x = xmin << 16;

//            for (count = ptp[imin].y; count <= ptp[imax].y; count++)
            for (count = ymin; count <= ymax; count++)
            {
                    if((count >= 0 ) && (count < 1500))
                            ledge[count] = x >> 16;
                    x += m;
            }
    }

    dy = (ymid - ymin);
    if(dy)
    {
        m = (xmid - xmin) << 16;
        m /= dy;

        x = xmin << 16;

        for (count = ymin; count <= ymid; count++)
        {
            if((count >= 0 ) && (count < 1500))
                redge[count] = x >> 16;
            x += m;
        }
    }

    dy = (ymax - ymid);
    if(dy)
    {
        m = (xmax - xmid) << 16;
        m /= dy;

        x = xmid << 16;

        for (count = ymid; count <=ymax; count++)
        {
            if((count >= 0 ) && (count < 1500))
                redge[count] = x >> 16;
            x += m;
        }
    }

    //      Check the triangle edge winding direction
    int dfSum = 0;
    dfSum += xmin * ymax - ymin * xmax;
    dfSum += xmax * ymid - ymax * xmid;
    dfSum += xmid * ymin - ymid * xmin;

    bool cw = dfSum < 0;

    //      if cw is true, redge is actually on the right

    //              Clip the triangle

    int y1 = ymax;
    int y2 = ymin;

    int ybt = pb_spec->y;
    int yt = pb_spec->y + pb_spec->height;

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

 //                                   int ixm = redge[iyp];

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
#ifdef __WXGTK__
#define memset3(dest, value, count) \
__asm__ __volatile__ ( \
"cmp $0,%2\n\t" \
"jg l0\n\t" \
"je l1\n\t" \
"jmp l2\n\t" \
"l0:\n\t" \
"movl  %0,(%1)\n\t" \
"add $3,%1\n\t" \
"dec %2\n\t" \
"jnz l0\n\t" \
"l1:\n\t" \
"movb %b0,(%1)\n\t" \
"inc %1\n\t" \
"movb %h0,(%1)\n\t" \
"inc %1\n\t" \
"shr $16,%0\n\t" \
"movb %b0,(%1)\n\t" \
"l2:\n\t" \
: : "a"(value), "D"(dest), "r"(count) :  );
                                           int count = ixm-ix;
                                           memset3(px, color_int, count)
#else

                                           while(ix <= ixm)
                                           {
                                                *px++ = b;
                                                *px++ = g;
                                                *px++ = r;

                                                ix++;
                                           }
#endif
                                   }
                           }
                    }
            }
    }

    if(pb_spec->depth == 32)
    {

            assert(ya <= yb);

            for(int iyp = ya ; iyp < yb ; iyp++)
            {
                if((iyp >= ybt) && (iyp < yt))
                    {
                            int yoff =      (iyp - pb_spec->y) * pb_spec->pb_pitch;

                            unsigned char *py = pix_buff + yoff;


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

                            if((ledge[iyp] != -1) /*&& cw && (ix <= ixm)*/)
                            {
                                    int xoff = (ix-pb_spec->x) * pb_spec->depth / 8;

                                    unsigned char *px = py + xoff;


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

    return true;
}



void s52plib::RenderToBufferFilledPolygon(ObjRazRules *rzRules, S57Obj *obj, color *c, wxBoundingBox &BBView,
               render_canvas_parms *pb_spec, render_canvas_parms *pPatt_spec)
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
        wxPoint *pp3 = (wxPoint *)malloc(3 * sizeof(wxPoint));
        wxPoint *ptp = (wxPoint *)malloc((obj->pPolyTessGeo->GetnVertexMax() + 1) * sizeof(wxPoint));

        //  Allow a little slop in calculating whether a triangle
        //  is within the requested Viewport
        double margin = BBView.GetWidth() * .05;

        PolyTriGroup *ppg = obj->pPolyTessGeo->Get_PolyTriGroup_head();

        TriPrim *p_tp = ppg->tri_prim_head;
        while(p_tp)
        {
            if(BBView.Intersect(*(p_tp->p_bbox), margin) != _OUT)
            {
                //      Get and convert the points
                wxPoint *pr = ptp;

                double *pvert_list = p_tp->p_vertex;

                for(int iv =0 ; iv < p_tp->nVert ; iv++)
                {
                    double lon = *pvert_list++;
                    double lat = *pvert_list++;
                    rzRules->chart->GetPointPix(rzRules, lat, lon, pr);

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

                            dda_tri(pp3, &cp, pb_spec, pPatt_spec);
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

                            dda_tri(pp3, &cp, pb_spec, pPatt_spec);
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

                            dda_tri(pp3, &cp, pb_spec, pPatt_spec);
                        }
                        break;
                    }
                }
            }   // if bbox
            p_tp = p_tp->p_next;                // pick up the next in chain
        }       // while
        free(ptp);
        free(pp3);
    }       // if pPolyTessGeo

}


int s52plib::RenderToBufferAP(ObjRazRules *rzRules, Rules *rules, ViewPort *vp,
                          render_canvas_parms *pb_spec)
{
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
            patt_spec->pix_buff = (unsigned char *)malloc(sizey * patt_spec->pb_pitch);

                // Preset background
            memset(pb_spec->pix_buff, 0,sizey * patt_spec->pb_pitch);
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

//  Use the current viewport as a bounding box
        wxBoundingBox BBView(vp->lon_left, vp->lat_bot, vp->lon_right, vp->lat_top);

        RenderToBufferFilledPolygon(rzRules, rzRules->obj, NULL, BBView, pb_spec, ppatt_spec);

    }        // Raster

    return 1;
}


int s52plib::RenderToBufferAC(ObjRazRules *rzRules, Rules *rules, ViewPort *vp,
                                 render_canvas_parms *pb_spec)
{
   color *c;
   char *str = (char*)rules->INSTstr;
   wxBoundingBox BBView(vp->lon_left, vp->lat_bot, vp->lon_right, vp->lat_top);

   c = ps52plib->S52_getColor(str);

   RenderToBufferFilledPolygon(rzRules, rzRules->obj, c, BBView, pb_spec, NULL);
   return 1;
}


int s52plib::RenderArea(wxDC *pdcin, ObjRazRules *rzRules, ViewPort *vp,
                                                render_canvas_parms *pb_spec)
{
    if(!ObjectRenderCheck(rzRules, vp))
        return 0;

    pdc = pdcin;                    // use this DC
    Rules *rules = rzRules->LUP->ruleList;

    //Debug Hooks
//    if(!strncmp(rzRules->LUP->OBCL, "M_COVR", 6))
//        int yyrt = 4;

//    if(rzRules->obj->Index == 2009)
//        int rrt = 5;

    while (rules != NULL)
    {
          switch (rules->ruleType){
                 case RUL_ARE_CO:       RenderToBufferAC(rzRules,rules, vp, pb_spec);break;         // AC
                 case RUL_ARE_PA:       RenderToBufferAP(rzRules,rules, vp, pb_spec);break;         // AP

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
                                case RUL_ARE_CO:       RenderToBufferAC(rzRules,rules, vp, pb_spec);break;
                                case RUL_ARE_PA:       RenderToBufferAP(rzRules,rules, vp, pb_spec);break;
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

                    char *rule_str1 = RenderCS(rzRules, rules);
                    wxString cs_string(rule_str1, wxConvUTF8);
                    delete rule_str1;


                    wxArrayOfLUPrec *la = condSymbolLUPArray;
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
                            char *p = (char *)pobj_attList->mb_str();

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
    if (rzRules->obj==NULL)
        return false;

    // Debug for testing US5FL51.000 slcons
//    if((rzRules->obj->Index == 3868) || (rzRules->obj->Index == 3870))
//        return false;

    // Of course, the object must be at least partly visible in the viewport
    wxBoundingBox BBView = vp->vpBBox;
    if(BBView.Intersect(rzRules->obj->BBObj, 0) == _OUT)// Object is wholly outside window
          return false;

    bool b_catfilter = true;

//      Do Object Type Filtering

    if(m_nDisplayCategory == MARINERS_STANDARD)
    {
        if(!((OBJLElement *)(pOBJLArray->Item(rzRules->obj->iOBJL)))->nViz)
            b_catfilter = false;
    }

    if(m_nDisplayCategory == OTHER)
    {
        if((DISPLAYBASE != rzRules->LUP->DISC)
            && (STANDARD != rzRules->LUP->DISC)
            && (OTHER != rzRules->LUP->DISC))
        {
            b_catfilter = false;
        }
    }

    else if(m_nDisplayCategory == STANDARD)
    {
        if((DISPLAYBASE != rzRules->LUP->DISC) && (STANDARD != rzRules->LUP->DISC))
        {
            b_catfilter = false;
        }
    }
    else if(m_nDisplayCategory == DISPLAYBASE)
    {
        if(DISPLAYBASE != rzRules->LUP->DISC)
        {
            b_catfilter = false;
        }
    }

//  Soundings override
    if(!strncmp(rzRules->LUP->OBCL, "SOUNDG", 6))
        b_catfilter = m_bShowSoundg;

//  Meta object override
    if(!strncmp(rzRules->LUP->OBCL, "M_", 2))
        if(!m_bShowMeta)
            b_catfilter = false;

    bool b_visible = false;
    if(b_catfilter)
    {
          b_visible = true;

//      SCAMIN Filtering
          //      Implementation note:
          //      According to S52 specs, SCAMIN must not apply to GROUP1 objects, Meta Objects
          //      or DisplayCategoryBase objects.
          //      Occasionally, an ENC will encode a spurious SCAMIN value for one of these objects.
          //      see, for example, US5VA18M, in OpenCPN SENC as Feature 350(DEPARE), LNAM = 022608187ED20ACC.
          //      We shall explicitly ignore SCAMIN filtering for these types of objects.

          if(m_bUseSCAMIN)
          {
                if((DISPLAYBASE == rzRules->LUP->DISC) || (PRIO_GROUP1 == rzRules->LUP->DPRI))
                      b_visible = true;
                else if(vp->chart_scale > rzRules->obj->Scamin)
                      b_visible = false;
          }

        return b_visible;
    }


    return false;
}



/******************************************************************************
 * $Id: cm93.cpp,v 1.16 2009/08/03 04:23:28 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  cm93 Chart Object
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

 * $Log: cm93.cpp,v $
 * Revision 1.16  2009/08/03 04:23:28  bdbcat
 * Correct Logic
 *
 * Revision 1.15  2009/08/03 03:19:52  bdbcat
 * Cleanup for MSVC
 *
 * Revision 1.14  2009/07/29 20:07:18  bdbcat
 * Update for gcc 4.2.4
 *
 * Revision 1.13  2009/07/29 00:56:18  bdbcat
 * Update dictionary and chart search algorithms
 *
 * Revision 1.12  2009/07/10 04:03:09  bdbcat
 * Improve Scale logic.
 *
 * Revision 1.11  2009/07/08 01:47:54  bdbcat
 * Update CM93 chart naming logic.
 *
 * Revision 1.10  2009/06/22 02:46:54  bdbcat
 * Optimize CM93 ATON displayed leabels.
 *
 * Revision 1.9  2009/06/17 02:46:12  bdbcat
 * Add line priority rescan
 *
 * Revision 1.8  2009/06/03 03:16:55  bdbcat
 * Correct 360 longitude logic.
 *
 * Revision 1.7  2009/05/05 03:58:53  bdbcat
 * Correct object lat/lon declaration
 *
 * Revision 1.6  2009/04/18 03:29:53  bdbcat
 * Correct Area Geometry
 *
 * Revision 1.5  2009/04/13 02:33:44  bdbcat
 * Improve dictionary logic
 *
 * Revision 1.4  2009/04/07 16:49:48  bdbcat
 * No debug printf
 *
 * Revision 1.3  2009/03/30 19:06:17  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.2  2009/03/27 01:02:54  bdbcat
 * No pragma pack()
 *
 * Revision 1.1  2009/03/26 22:25:46  bdbcat
 * Add cm93 support
 *
 *
 *
 */


// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/textfile.h>
#include <wx/tokenzr.h>
#include <wx/arrstr.h>
#include <wx/mstream.h>

#include "ogr_api.h"
#include "s57chart.h"
#include "cm93.h"
#include "s52plib.h"
#include "georef.h"
#include "mygeom.h"
#include "cutil.h"
#include "navutil.h"                            // for LogMessageOnce

#include <stdio.h>



extern wxString         *g_pSENCPrefix;
extern s52plib          *ps52plib;
extern cm93manager      *s_pcm93mgr;
extern MyConfig         *pConfig;
extern wxString         g_CM93DictDir;

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(Array_Of_M_COVR_Desc);


//#define CM93_DEBUG_PRINTF 1


//    CM93 Encode/Decode support tables


static unsigned char Table_0[] = {
      0x0CD,0x0EA,0x0DC,0x048,0x03E,0x06D,0x0CA,0x07B,0x052,0x0E1,0x0A4,0x08E,0x0AB,0x005,0x0A7,0x097,
      0x0B9,0x060,0x039,0x085,0x07C,0x056,0x07A,0x0BA,0x068,0x06E,0x0F5,0x05D,0x002,0x04E,0x00F,0x0A1,
      0x027,0x024,0x041,0x034,0x000,0x05A,0x0FE,0x0CB,0x0D0,0x0FA,0x0F8,0x06C,0x074,0x096,0x09E,0x00E,
      0x0C2,0x049,0x0E3,0x0E5,0x0C0,0x03B,0x059,0x018,0x0A9,0x086,0x08F,0x030,0x0C3,0x0A8,0x022,0x00A,
      0x014,0x01A,0x0B2,0x0C9,0x0C7,0x0ED,0x0AA,0x029,0x094,0x075,0x00D,0x0AC,0x00C,0x0F4,0x0BB,0x0C5,
      0x03F,0x0FD,0x0D9,0x09C,0x04F,0x0D5,0x084,0x01E,0x0B1,0x081,0x069,0x0B4,0x009,0x0B8,0x03C,0x0AF,
      0x0A3,0x008,0x0BF,0x0E0,0x09A,0x0D7,0x0F7,0x08C,0x067,0x066,0x0AE,0x0D4,0x04C,0x0A5,0x0EC,0x0F9,
      0x0B6,0x064,0x078,0x006,0x05B,0x09B,0x0F2,0x099,0x0CE,0x0DB,0x053,0x055,0x065,0x08D,0x007,0x033,
      0x004,0x037,0x092,0x026,0x023,0x0B5,0x058,0x0DA,0x02F,0x0B3,0x040,0x05E,0x07F,0x04B,0x062,0x080,
      0x0E4,0x06F,0x073,0x01D,0x0DF,0x017,0x0CC,0x028,0x025,0x02D,0x0EE,0x03A,0x098,0x0E2,0x001,0x0EB,
      0x0DD,0x0BC,0x090,0x0B0,0x0FC,0x095,0x076,0x093,0x046,0x057,0x02C,0x02B,0x050,0x011,0x00B,0x0C1,
      0x0F0,0x0E7,0x0D6,0x021,0x031,0x0DE,0x0FF,0x0D8,0x012,0x0A6,0x04D,0x08A,0x013,0x043,0x045,0x038,
      0x0D2,0x087,0x0A0,0x0EF,0x082,0x0F1,0x047,0x089,0x06A,0x0C8,0x054,0x01B,0x016,0x07E,0x079,0x0BD,
      0x06B,0x091,0x0A2,0x071,0x036,0x0B7,0x003,0x03D,0x072,0x0C6,0x044,0x08B,0x0CF,0x015,0x09F,0x032,
      0x0C4,0x077,0x083,0x063,0x020,0x088,0x0F6,0x0AD,0x0F3,0x0E8,0x04A,0x0E9,0x035,0x01C,0x05F,0x019,
      0x01F,0x07D,0x070,0x0FB,0x0D1,0x051,0x010,0x0D3,0x02E,0x061,0x09D,0x05C,0x02A,0x042,0x0BE,0x0E6
};

static unsigned char Encode_table[256];
static unsigned char Decode_table[256];

static bool  cm93_decode_table_created;

cm93_dictionary::cm93_dictionary()
{
      m_S57ClassArray   = NULL;
      m_AttrArray       = NULL;
      m_GeomTypeArray   = NULL;;
      m_ValTypeArray    = NULL;
      m_max_class       = 0;
      m_ok = false;

}


bool cm93_dictionary::LoadDictionary(wxString dictionary_dir)
{
      int i, nline;
      wxString line;
      wxString dir(dictionary_dir);       // a copy
      bool  ret_val = false;

      wxChar sep = wxFileName::GetPathSeparator();
      if (dir.Last() != sep)
            dir.Append(sep);

      m_dict_dir = dir;


      //    Build some array strings for Feature decoding

      wxString sf(dir);
      sf.Append(_T("CM93OBJ.DIC"));

      if(!wxFileName::FileExists(sf))
            return false;

      wxTextFile file;
      if(!file.Open(sf))
            return false;


      nline = file.GetLineCount();

      if(!nline)
            return false;

      //    Read the file once to get the max class number
      int iclass_max = 0;

      for( i=0 ; i<nline ; i++)
      {
            line = file.GetLine(i);

            wxStringTokenizer tkz(line, wxT("|"));
//            while ( tkz.HasMoreTokens() )
            {
                  //  6 char class name
                  wxString class_name = tkz.GetNextToken();

                  //  class number, ascii
                  wxString token = tkz.GetNextToken();
                  long liclass;
                  token.ToLong(&liclass);
                  int iclass = liclass;
                  if(iclass > iclass_max)
                        iclass_max = iclass;

                  //  geom type, ascii
                  wxString geo_type = tkz.GetNextToken();

            }

      }

      m_max_class = iclass_max;

      //    Create the class name array
      m_S57ClassArray = new wxArrayString;
      m_S57ClassArray->Add(_T("NULLNM"), iclass_max+1);

      //    And an array of ints describing the geometry type per class
      m_GeomTypeArray = (int *)malloc((iclass_max + 1) * sizeof(int));

      //    Iterate over the file, filling in the values
      for( i=0 ; i<nline ; i++)
      {
            line = file.GetLine(i);

            wxStringTokenizer tkz(line, wxT("|"));
 //           while ( tkz.HasMoreTokens() )
            {
                  //  6 char class name
                  wxString class_name = tkz.GetNextToken();

                  //  class number, ascii
                  wxString token = tkz.GetNextToken();
                  long liclass;
                  token.ToLong(&liclass);
                  int iclass = liclass;

                  //  geom type, ascii
                  wxString geo_type = tkz.GetNextToken();

                  m_S57ClassArray->Insert( class_name, iclass);
                  m_S57ClassArray->RemoveAt( iclass + 1);

                  int igeom_type = -1;                            // default unknown
                  wxChar geo_type_primary = geo_type[0];

                  if(geo_type_primary == 'A')
                        igeom_type = 3;
                  else if(geo_type_primary == 'L')
                        igeom_type = 2;
                  else if(geo_type_primary == 'P')
                        igeom_type = 1;

                  //    Note:  there are other types in the file, e.g. 'C'.  Dunno what this is
                  //    Also, some object classes want multiple geometries, like PA, PLA, etc.
                  //    Take only primary, ignore the rest

                  m_GeomTypeArray[iclass] = igeom_type;

            }
      }
      file.Close();

     //    Build some array strings for Attribute decoding

      wxString sfa(dir);
      sfa.Append(_T("ATTRLUT.DIC"));

      if(wxFileName::FileExists(sfa))
      {
            wxFileInputStream filea(sfa);

            if(filea.IsOk())
            {
      //    Read the file once to get the max attr number
                  int iattr_max = 0;


                  while(!filea.Eof())
                  {

            //read a line
                        line.Empty();
                        while(1)
                        {
                              char a = filea.GetC();
                              if(filea.Eof())
                                    break;
                              line.Append(a);
                              if(a == 0x0a)
                                    break;
                        }


                        if(!line.StartsWith((const wxChar *)wxT(";")))
                        {
                              wxStringTokenizer tkz(line, wxT("|"));
                              {
                  //  6 attribute label
                                    wxString class_name = tkz.GetNextToken();

                  //  attribute number, ascii
                                    wxString token = tkz.GetNextToken();
                                    long liattr;
                                    token.ToLong(&liattr);
                                    int iattr = liattr;
                                    if(iattr > iattr_max)
                                    iattr_max = iattr;
                              }
                        }
                  }

                  m_max_attr = iattr_max;

                  filea.SeekI(0);


      //    Create the attribute label array

                  m_AttrArray = new wxArrayString;
                  m_AttrArray->Add(_T("NULLNM"), iattr_max+1);

      //    And an array of chars describing the attribute value type
                  m_ValTypeArray = (char *)malloc((iattr_max + 1) * sizeof(char));


      //    Iterate over the file, filling in the values
                  while(!filea.Eof())
                  {
            //read a line
                        line.Empty();
                        while(1)
                        {
                              char a = filea.GetC();
                              if(filea.Eof())
                                    break;
                              line.Append(a);
                              if(a == 0x0a)
                                    break;
                        }


                  if(!line.StartsWith((const wxChar *)wxT(";")))
                        {
                              wxStringTokenizer tkz(line, wxT("|"));
                              {
                  //  6 char class name
                                    wxString attr_name = tkz.GetNextToken();

                  //  class number, ascii
                                    wxString token = tkz.GetNextToken();
                                    long liattr;
                                    token.ToLong(&liattr);
                                    int iattr = liattr;

                                    m_AttrArray->Insert( attr_name, iattr);
                                    m_AttrArray->RemoveAt( iattr + 1);

                  //    Skip some
                                    token = tkz.GetNextToken();
                                    token = tkz.GetNextToken();
                                    token = tkz.GetNextToken();
                                    token = tkz.GetNextToken().Trim();

                                    char atype = '?';
                                    if(token.IsSameAs(_T("aFLOAT")))
                                          atype = 'R';
                                    else if(token.IsSameAs(_T("aBYTE")))
                                          atype = 'B';
                                    else if(token.IsSameAs(_T("aSTRING")))
                                          atype = 'S';
                                    else if(token.IsSameAs(_T("aCMPLX")))
                                          atype = 'C';
                                    else if(token.IsSameAs(_T("aLIST")))
                                          atype = 'L';
                                    else if(token.IsSameAs(_T("aWORD10")))
                                          atype = 'W';
                                    else if(token.IsSameAs(_T("aLONG")))
                                          atype = 'G';

                                    m_ValTypeArray[iattr] = atype;

                              }
                        }
                  }
                  ret_val = true;
            }
            else              // stream IsOK
            {
                  ret_val = false;
            }
      }


      else                    //    Look for alternate file
      {
            sfa = dir;
            sfa.Append(_T("CM93ATTR.DIC"));

            if(wxFileName::FileExists(sfa))
            {
                  wxFileInputStream filea(sfa);

                  if(filea.IsOk())
                  {
      //    Read the file once to get the max attr number
                        int iattr_max = 0;


                        while(!filea.Eof())
                        {

            //read a line
                              line.Empty();
                              while(1)
                              {
                                    char a = filea.GetC();
                                    if(filea.Eof())
                                          break;
                                    line.Append(a);
                                    if(a == 0x0a)
                                          break;
                              }


                              if(!line.StartsWith((const wxChar *)wxT(";")))
                              {
                                    wxStringTokenizer tkz(line, wxT("|"));
                                    {
                  //  6 attribute label
                                          wxString class_name = tkz.GetNextToken();

                  //  attribute number, ascii
                                          wxString token = tkz.GetNextToken();
                                          long liattr;
                                          token.ToLong(&liattr);
                                          int iattr = liattr;
                                          if(iattr > iattr_max)
                                                iattr_max = iattr;
                                    }
                              }
                        }

                        m_max_attr = iattr_max;

                        filea.SeekI(0);


      //    Create the attribute label array

                        m_AttrArray = new wxArrayString;
                        m_AttrArray->Add(_T("NULLNM"), iattr_max+1);

      //    And an array of chars describing the attribute value type
                        m_ValTypeArray = (char *)malloc((iattr_max + 1) * sizeof(char));
                        for(int iat=0 ; iat < iattr_max + 1 ; iat++)
                              m_ValTypeArray[iat] = '?';


      //    Iterate over the file, filling in the values
                        while(!filea.Eof())
                        {
            //read a line
                              line.Empty();
                              while(1)
                              {
                                    char a = filea.GetC();
                                    if(filea.Eof())
                                          break;
                                    line.Append(a);
                                    if(a == 0x0a)
                                          break;
                              }


                              if(!line.StartsWith((const wxChar *)wxT(";")))
                              {
                                    wxStringTokenizer tkz(line, wxT("|\r\n"));
                                    {
                  //  6 char class name
                                          wxString attr_name = tkz.GetNextToken();

                  //  class number, ascii
                                          wxString token = tkz.GetNextToken();
                                          long liattr;
                                          token.ToLong(&liattr);
                                          int iattr = liattr;

                                          m_AttrArray->Insert( attr_name, iattr);
                                          m_AttrArray->RemoveAt( iattr + 1);

                                         token = tkz.GetNextToken().Trim();

                                          char atype = '?';
                                          if(token.IsSameAs(_T("aFLOAT")))
                                                atype = 'R';
                                          else if(token.IsSameAs(_T("aBYTE")))
                                                atype = 'B';
                                          else if(token.IsSameAs(_T("aSTRING")))
                                                atype = 'S';
                                          else if(token.IsSameAs(_T("aCMPLX")))
                                                atype = 'C';
                                          else if(token.IsSameAs(_T("aLIST")))
                                                atype = 'L';
                                          else if(token.IsSameAs(_T("aWORD10")))
                                                atype = 'W';
                                          else if(token.IsSameAs(_T("aLONG")))
                                                atype = 'G';

                                          m_ValTypeArray[iattr] = atype;

                                    }
                              }
                        }
                        ret_val = true;
                  }
                  else              // stream IsOK
                        ret_val = false;
            }
      }

      if(ret_val)
      {
            m_ok = true;

            wxString msg(_T("Loaded CM93 Dictionary from "));
            msg.Append(dir);
            wxLogMessage(msg);
      }

      return ret_val;
}

wxString cm93_dictionary::GetClassName(int iclass)
{
      if((iclass > m_max_class) || (iclass < 0))
            return(_T("Unknown"));
      else
            return(m_S57ClassArray->Item(iclass));
}

wxString cm93_dictionary::GetAttrName(int iattr)
{
      if((iattr > m_max_attr) || (iattr < 0))
            return(_T("UnknownAttr"));
      else
            return(m_AttrArray->Item(iattr));
}

//      char vtype = m_pDict->m_ValTypeArray[iattr];
char cm93_dictionary::GetAttrType(int iattr)
{
      if((iattr > m_max_attr) || (iattr < 0))
            return('?');
      else
            return(m_ValTypeArray[iattr]);
}




cm93_dictionary::~cm93_dictionary()
{
      delete m_S57ClassArray;
      free( m_GeomTypeArray );
      delete m_AttrArray;
      free( m_ValTypeArray);
}





//    CM93 Decode support routines

void CreateDecodeTable(void)
{
      int i;
      for( i=0 ; i < 256 ; i++)
      {
            Encode_table[i] = Table_0[i] ^ 8;
      }

      for( i=0 ; i < 256 ; i++)
      {
            unsigned char a = Encode_table[i];
            Decode_table[(int)a] = (unsigned char)i;
      }
}


int   read_and_decode_bytes(FILE *stream, void *p, int nbytes)
{
      if(0 == nbytes)                     // declare victory if no bytes requested
            return 1;

      //    read into callers buffer
      if(!fread( p, nbytes, 1, stream))
             return 0;

      //    decode inplace
      unsigned char *q = (unsigned char *)p;

      for(int i=0 ; i < nbytes ; i++)
      {
            unsigned char a = *q;
            int b = a;
            unsigned char c = Decode_table[b];
            *q = c;

            q++;
      }
      return 1;
}


int read_and_decode_double(FILE *stream, double *p)
{
      double t;
     //    read into temp buffer
      if(!fread( &t, sizeof(double), 1, stream))
            return 0;

      //    decode inplace
      unsigned char *q = (unsigned char *)&t;

      for(unsigned int i=0 ; i < sizeof(double) ; i++)
      {
            unsigned char a = *q;
            int b = a;
            unsigned char c = Decode_table[b];
            *q = c;

            q++;
      }

      //    copy to target
      *p = t;

      return 1;
}

int read_and_decode_int(FILE *stream, int *p)
{
      int t;
     //    read into temp buffer
      if(!fread( &t, sizeof(int), 1, stream))
            return 0;

      //    decode inplace
      unsigned char *q = (unsigned char *)&t;

      for(unsigned int i=0 ; i < sizeof(int) ; i++)
      {
            unsigned char a = *q;
            int b = a;
            unsigned char c = Decode_table[b];
            *q = c;

            q++;
      }

      //    copy to target
      *p = t;

      return 1;
}

int read_and_decode_ushort(FILE *stream, unsigned short *p)
{
      unsigned short t;
     //    read into temp buffer
      if(!fread( &t, sizeof(unsigned short), 1, stream))
            return 0;

      //    decode inplace
      unsigned char *q = (unsigned char *)&t;

      for(unsigned int i=0 ; i < sizeof(unsigned short) ; i++)
      {
            unsigned char a = *q;
            int b = a;
            unsigned char c = Decode_table[b];
            *q = c;

            q++;
      }

      //    copy to target
      *p = t;

      return 1;
}



//    Calculate the CM93 CellIndex integer for a given Lat/Lon, at a given scale

int Get_CM93_CellIndex(double lat, double lon, int scale)
{
      int retval = 0;

      int dval;
      switch (scale)
      {
            case 20000000: dval = 120; break;         // Z
            case  3000000: dval =  60; break;         // A
            case  1000000: dval =  30; break;         // B
            case   200000: dval =  12; break;         // C
            case   100000: dval =   3; break;         // D
            case    50000: dval =   1; break;         // E
            case    20000: dval =   1; break;         // F
            case     7500: dval =   1; break;         // G
            default: dval =   1; break;
      }

      //    Longitude
      double lon1 = (lon + 360.) * 3.;                      // basic cell size
      while(lon1 >= 1080.0)
            lon1 -= 1080.0;
      unsigned int lon2 = ((unsigned int)lon1) / dval;      // normalize
      unsigned int lon3 = lon2 * dval;

      retval = lon3;

      //    Latitude
      double lat1 = (lat * 3.) + 270. - 30;
      unsigned int lat2 = ((unsigned int)lat1) / dval;      // normalize
      unsigned int lat3 = lat2 * dval;


      retval += (lat3 + 30) * 10000;


      return retval;
}

//    Calculate the Lat/Lon of the lower left corner of a CM93 cell,
//    given a CM93 CellIndex and scale
//    Returned longitude value is always > 0
void Get_CM93_Cell_Origin(int cellindex, int scale, double *lat, double *lon)
{
      //    Longitude
      double idx1 = cellindex % 10000;
      double lont = (idx1 / 3.);

      *lon = lont;

      //    Latitude
      int idx2 = cellindex / 10000;
      double lat1 = idx2 - 270.;
      *lat = lat1 / 3.;
}


//    Answer the query: "Is there a cm93 cell at the specified scale which contains a given lat/lon?"
bool Is_CM93Cell_Present(wxString &fileprefix, double lat, double lon, int scale_index)
{
      int scale;
      int dval;
      wxChar scale_char;

      switch (scale_index)
      {
            case 0: scale =  20000000; dval = 120; scale_char = 'Z'; break;         // Z
            case 1: scale =   3000000; dval =  60; scale_char = 'A'; break;         // A
            case 2: scale =   1000000; dval =  30; scale_char = 'B'; break;         // B
            case 3: scale =    200000; dval =  12; scale_char = 'C'; break;         // C
            case 4: scale =    100000; dval =   3; scale_char = 'D'; break;         // D
            case 5: scale =     50000; dval =   1; scale_char = 'E'; break;         // E
            case 6: scale =     20000; dval =   1; scale_char = 'F'; break;         // F
            case 7: scale =      7500; dval =   1; scale_char = 'G'; break;         // G
            default: scale = 20000000; dval = 120; break;
      }

      int cellindex = Get_CM93_CellIndex(lat, lon, scale);


      //    Create the file name
      wxString file;

      int ilat = cellindex / 10000;
      int ilon = cellindex % 10000;

      int jlat = (((ilat - 30) / dval) * dval) + 30;              // normalize
      int jlon = (ilon / dval) * dval;

      int ilatroot = (((ilat - 30) / 60) * 60) + 30;
      int ilonroot = (ilon / 60) * 60;

      wxString fileroot;
      fileroot.Printf(_T("%04d%04d/"), ilatroot, ilonroot);

/*
      file.Printf(_T("/%04d%04d."), jlat, jlon);
      file += scale_char;
      file.Prepend(scale_char);
      file.Prepend(fileroot);
      file.Prepend(fileprefix);

      if(::wxFileExists(file))
            return true;
*/
      /// here
      wxString sdir(fileprefix);
      sdir += fileroot;
      sdir += scale_char;

      wxString tfile;
      tfile.Printf(_T("?%03d%04d."), jlat, jlon);
      tfile += scale_char;

      wxDir dir(sdir);

      wxArrayString file_array;
      int n_files = dir.GetAllFiles(sdir, &file_array, tfile, wxDIR_FILES);

      if(n_files)
            return true;

      else
      {

       //    Try with alternate case of m_scalechar
            wxString old_scalechar(scale_char);
            wxString new_scalechar = old_scalechar.Lower();

/*
            wxString file1;
            file1.Printf(_T("/%04d%04d."), jlat, jlon);
            file1 += new_scalechar;
            file1.Prepend(new_scalechar);

            file1.Prepend(fileroot);
            file1.Prepend(fileprefix);

            return(::wxFileExists(file1));
*/
            wxString tfile1;
            tfile1.Printf(_T("?%03d%04d."), jlat, jlon);
            tfile1 += new_scalechar;

            int n_files1 = dir.GetAllFiles(sdir, &file_array, tfile1, wxDIR_FILES);

            return (n_files1 > 0);

      }

}


bool read_header_and_populate_cib(FILE *stream, Cell_Info_Block *pCIB)
{
      //    Read header, populate Cell_Info_Block

      //    This 128 byte block is read element-by-element, to allow for
      //    endian-ness correction by element.
      //    Unused elements are read and, well, unused.

      header_struct header;

      read_and_decode_double(stream,&header.lon_min);
      read_and_decode_double(stream,&header.lat_min);
      read_and_decode_double(stream,&header.lon_max);
      read_and_decode_double(stream,&header.lat_max);

      read_and_decode_double(stream,&header.easting_min);
      read_and_decode_double(stream,&header.northing_min);
      read_and_decode_double(stream,&header.easting_max);
      read_and_decode_double(stream,&header.northing_max);

      read_and_decode_ushort(stream,&header.usn_vector_records);
      read_and_decode_int(stream,&header.n_vector_record_points);
      read_and_decode_int(stream,&header.m_46);
      read_and_decode_int(stream,&header.m_4a);
      read_and_decode_ushort(stream,&header.usn_point3d_records);
      read_and_decode_int (stream,&header.m_50);
      read_and_decode_int(stream,&header.m_54);
      read_and_decode_ushort(stream,&header.usn_point2d_records);
      read_and_decode_ushort(stream,&header.m_5a);
      read_and_decode_ushort(stream,&header.m_5c);
      read_and_decode_ushort(stream,&header.usn_feature_records);

      read_and_decode_int(stream,&header.m_60);
      read_and_decode_int(stream,&header.m_64);
      read_and_decode_ushort(stream,&header.m_68);
      read_and_decode_ushort(stream,&header.m_6a);
      read_and_decode_ushort(stream,&header.m_6c);
      read_and_decode_int(stream,&header.m_nrelated_object_pointers);

      read_and_decode_int(stream,&header.m_72);
      read_and_decode_ushort(stream,&header.m_76);

      read_and_decode_int(stream,&header.m_78);
      read_and_decode_int(stream,&header.m_7c);


      //    Calculate and record the cell coordinate transform coefficients


      double delta_x = header.easting_max - header.easting_min;
      if(delta_x < 0)
            delta_x += CM93_semimajor_axis_meters * 2.0 * PI;              // add one trip around

      pCIB->transform_x_rate = delta_x / 65535;
      pCIB->transform_y_rate = (header.northing_max - header.northing_min) / 65535;

      //    Force all transforms to produce positive longitude only
      pCIB->transform_x_origin = header.easting_min;
      if(pCIB->transform_x_origin < 0)
            pCIB->transform_x_origin += CM93_semimajor_axis_meters * 2.0 * PI;              // add one trip around
      pCIB->transform_y_origin = header.northing_min;


#if 0
      header.lon_min = /*round*/(header.lon_min * 6.0) / 6.0;
      header.lat_min = /*round*/(header.lat_min * 6.0) / 6.0;
      header.lon_max = /*round*/(header.lon_max * 6.0) / 6.0;
      header.lat_max = /*round*/(header.lat_max * 6.0) / 6.0;
#endif


      //    Extract some table sizes from the header, and pre-allocate the tables
      //    We do it this way to avoid incremental realloc() calls, which are expensive

      pCIB->m_nfeature_records = header.usn_feature_records;
      pCIB->pobject_block = (Object *)calloc( pCIB->m_nfeature_records * sizeof(Object), 1);

      pCIB->m_n_point2d_records = header.usn_point2d_records;
      pCIB->p2dpoint_array = (cm93_point *)malloc( pCIB->m_n_point2d_records * sizeof(cm93_point));

      pCIB->pprelated_object_block = (Object **)malloc( header.m_nrelated_object_pointers * sizeof(Object *));

      pCIB->object_vector_record_descriptor_block = (vector_record_descriptor *)malloc((header.m_4a + header.m_46) * sizeof(vector_record_descriptor));

      pCIB->attribute_block_top = (unsigned char *)calloc(header.m_78, 1);

      pCIB->m_nvector_records = header.usn_vector_records;
      pCIB->edge_vector_descriptor_block = (geometry_descriptor *)malloc(header.usn_vector_records * sizeof(geometry_descriptor));

      pCIB->pvector_record_block_top = (cm93_point *)malloc(header.n_vector_record_points * sizeof(cm93_point));

      pCIB->m_n_point3d_records = header.usn_point3d_records;
      pCIB->point3d_descriptor_block = (geometry_descriptor *)malloc(pCIB->m_n_point3d_records * sizeof(geometry_descriptor));

      pCIB->p3dpoint_array = (cm93_point_3d *)malloc(header.m_50 * sizeof(cm93_point_3d));

      return true;
}

bool read_vector_record_table(FILE *stream, int count, Cell_Info_Block *pCIB)
{
      bool brv;

      geometry_descriptor *p = pCIB->edge_vector_descriptor_block;
      cm93_point *q = pCIB->pvector_record_block_top;

      for(int iedge=0 ; iedge < count ; iedge++)
      {

            p->index = iedge;

            unsigned short npoints;
            brv = !(read_and_decode_ushort(stream, &npoints) == 0);
            if(!brv)
                  return false;

            p->n_points = npoints;
            p->p_points = q;

//           brv = read_and_decode_bytes(stream, q, p->n_points * sizeof(cm93_point));
//            if(!brv)
//                  return false;

            unsigned short x, y;
            for(int index = 0 ; index <  p->n_points ; index++)
            {
                  if(!read_and_decode_ushort(stream, &x))
                        return false;
                  if(!read_and_decode_ushort(stream, &y))
                        return false;

                  q[index].x = x;
                  q[index].y = y;
            }


            //    Compute and store the min/max of this block of n_points
            cm93_point *t = p->p_points;

            p->x_max = t->x;
            p->x_min = t->x;
            p->y_max = t->y;
            p->y_min = t->y;

            t++;

            for(int j=0 ; j < p->n_points-1 ; j++)
            {
                  if(t->x >= p->x_max)
                        p->x_max = t->x;

                  if(t->x <= p->x_min)
                        p->x_min = t->x;

                  if(t->y >= p->y_max)
                        p->y_max = t->y;

                  if(t->y <= p->y_max)
                        p->y_min = t->y;

                  t++;
            }

            //    Advance the block pointer
            q += p->n_points;

            //    Advance the geometry descriptor pointer
            p++;

      }

      return true;
}


bool read_3dpoint_table(FILE *stream, int count, Cell_Info_Block *pCIB)
{
      geometry_descriptor *p = pCIB->point3d_descriptor_block;
      cm93_point_3d *q = pCIB->p3dpoint_array;

      for(int i = 0 ; i < count ; i++)
      {
            unsigned short npoints;
            if(!read_and_decode_ushort(stream, &npoints))
                  return false;

            p->n_points = npoints;
            p->p_points = (cm93_point *)q;          // might not be the right cast

//            unsigned short t = p->n_points;

//            if(!read_and_decode_bytes(stream, q, t*6))
//                  return false;

            unsigned short x, y, z;
            for(int index = 0 ; index < p->n_points ; index++)
            {
                  if(!read_and_decode_ushort(stream, &x))
                        return false;
                  if(!read_and_decode_ushort(stream, &y))
                        return false;
                  if(!read_and_decode_ushort(stream, &z))
                        return false;

                  q[index].x = x;
                  q[index].y = y;
                  q[index].z = z;
            }


            p++;
            q++;
      }

      return true;
}


bool read_2dpoint_table(FILE *stream, int count, Cell_Info_Block *pCIB)
{

//      int rv = read_and_decode_bytes(stream, pCIB->p2dpoint_array, count * 4);

      unsigned short x, y;
      for(int index = 0 ; index < count ; index++)
      {
            if(!read_and_decode_ushort(stream, &x))
                return false;
            if(!read_and_decode_ushort(stream, &y))
                return false;

            pCIB->p2dpoint_array[index].x = x;
            pCIB->p2dpoint_array[index].y = y;
      }


      return true;
}


bool read_feature_record_table(FILE *stream, int n_features, Cell_Info_Block *pCIB)
{
	try
	{

      Object *pobj = pCIB->pobject_block;                // head of object array

      vector_record_descriptor *pobject_vector_collection = pCIB->object_vector_record_descriptor_block;

      Object **p_relob = pCIB->pprelated_object_block;             // head of previously allocated related object pointer block

      unsigned char *puc_var10 = pCIB->attribute_block_top;       //m_3a;
      int puc10count = 0;                 // should be same as header.m_78

      unsigned char object_type;
      unsigned char geom_prim;
      unsigned short obj_desc_bytes;

      unsigned int t;
      unsigned short index;
      unsigned short n_elements;


      for(int iobject = 0 ; iobject < n_features ; iobject++)
      {

            // read the object definition
            read_and_decode_bytes(stream, &object_type, 1);              // read the object type
            read_and_decode_bytes(stream, &geom_prim, 1);                // read the object geometry primitive type
            read_and_decode_ushort(stream, &obj_desc_bytes);             // read the object byte count

            pobj->otype = object_type;
            pobj->geotype = geom_prim;


            switch ( pobj->geotype & 0x0f)
            {
                  case 4:                                                     // AREA, 408c3d
                  {


                        if(!read_and_decode_ushort(stream, &n_elements))
                              return false;

                        pobj->n_geom_elements = n_elements;
                        t = (pobj->n_geom_elements * 2) + 2;
                        obj_desc_bytes -= t;

                        pobj->pGeometry = pobject_vector_collection;           // save pointer to created vector_record_descriptor in the object

                        for(unsigned short i = 0 ; i < pobj->n_geom_elements ; i++)
                        {
                              if(!read_and_decode_ushort(stream, &index))
                                     return false;

                              if((index & 0x1fff) > pCIB->m_nvector_records)
                                    *(int *)(0) = 0;                              // error
//                              return 0;               // error, bad pointer

                              geometry_descriptor *u = &pCIB->edge_vector_descriptor_block[(index & 0x1fff)];   //point to the vector descriptor

                              pobject_vector_collection->pGeom_Description = u;
                              pobject_vector_collection->segment_usage = (unsigned char)(index >> 13);

                              pobject_vector_collection++;
                        }

                        break;
                  }                                   // AREA geom



                  case 2:                                         // LINE geometry
                  {

                        if(!read_and_decode_ushort(stream, &n_elements))      // read geometry element count
                              return false;

                        pobj->n_geom_elements = n_elements;
                        t = (pobj->n_geom_elements * 2) + 2;
                        obj_desc_bytes -= t;

                        pobj->pGeometry = pobject_vector_collection;                     // save pointer to created vector_record_descriptor in the object

                        for(unsigned short i = 0 ; i < pobj->n_geom_elements ; i++)
                        {
                              unsigned short geometry_index;

                              if(!read_and_decode_ushort(stream, &geometry_index))
                               return false;


                              if((geometry_index & 0x1fff) > pCIB->m_nvector_records)
//                                    *(int *)(0) = 0;                              // error
                              return 0;               // error, bad pointer

                              geometry_descriptor *u = &pCIB->edge_vector_descriptor_block[(geometry_index & 0x1fff)];  //point to the vector descriptor

                              pobject_vector_collection->pGeom_Description = u;
                              pobject_vector_collection->segment_usage = (unsigned char)(geometry_index >> 13);

                              pobject_vector_collection++;
                        }

                        break;


                  }

                  case 1:
                  {
                        if(!read_and_decode_ushort(stream, &index))
                              return false;

                        obj_desc_bytes -= 2;

                        pobj->n_geom_elements = 1;                 // one point

                        pobj->pGeometry = &pCIB->p2dpoint_array[index];            //cm93_point *

                        break;
                  }

                  case 8:
                  {
                        if(!read_and_decode_ushort(stream, &index))
                              return false;
                        obj_desc_bytes -= 2;

                        pobj->n_geom_elements = 1;                 // one point

                        pobj->pGeometry = &pCIB->point3d_descriptor_block[index];          //geometry_descriptor *

                        break;
                  }

            }           // switch



            if((pobj->geotype & 0x10) == 0x10)             // children/related
            {
                  unsigned short nrelated;
                  if(!read_and_decode_bytes(stream, &nrelated, 1))
                        return false;

                  pobj->n_related_objects = nrelated;
                  t = (pobj->n_related_objects * 2) + 1;
                  obj_desc_bytes -= t;

                  pobj->p_related_object_pointer_array = p_relob;
                  p_relob += pobj->n_related_objects;

                  Object **w = (Object **)pobj->p_related_object_pointer_array;
                  for(unsigned char j = 0 ; j < pobj->n_related_objects ; j++)
                  {
                        if(!read_and_decode_ushort(stream, &index))
                              return false;

                        if(index > pCIB->m_nfeature_records)
//                              *(int *)(0) = 0;                              // error
                              return false;

                        Object *prelated_object = &pCIB->pobject_block[index];
                        *w = prelated_object;                       // fwd link

                        prelated_object->p_related_object_pointer_array = pobj;              // back link, array of 1 element

                        w++;
                  }
            }

            if((pobj->geotype & 0x20) == 0x20)
            {
//                  _asm int 3;                               // just after loc_408D8E
                  //TODO This is not right, n_related_objects is unsigned char.....
//                   *(int *)(0) = 0;                              // cause break error

                  unsigned short nrelated;
                  if(!read_and_decode_ushort(stream, &nrelated))
                        return false;

                  pobj->n_related_objects = nrelated;
                  obj_desc_bytes -= 2;
            }

            if((pobj->geotype & 0x40) == 0x40)
            {
//                  _asm int 3;                               // just after loc_408DCA"Relates to relation not implemented"
            }


            if((pobj->geotype & 0x80) == 0x80)             // attributes
            {
//                      _asm int 3;                               // just after loc_408DE2

                  unsigned char nattr;
                  if(!read_and_decode_bytes(stream, &nattr, 1))
                        return false;        //m_od

                  pobj->n_attributes = nattr;
                  obj_desc_bytes -= 5;

                  pobj->attributes_block = puc_var10;
                  puc_var10 += obj_desc_bytes;

                  puc10count += obj_desc_bytes;


                  if(!read_and_decode_bytes(stream, pobj->attributes_block, obj_desc_bytes))
                        return false;           // the attributes....

                  if((pobj->geotype & 0x0f) == 1)
                  {
//                        int yyp = 5;
//                        if(pobj->n_attributes != 1)
//                              int yyr = 5;
                  }

            }


            pobj++;                       // next object
      }

//      wxASSERT(puc10count == pCIB->m_22->m_78);
    }

 catch(...)
 {
//	 int yyp = 6;
       printf("catch on read_feature_record_table\n");
 }

      return true;
}







bool Ingest_CM93_Cell(const char * cell_file_name, Cell_Info_Block *pCIB)
{

  try
  {

      int file_length;

      //    Get the file length
      FILE *flstream = fopen(cell_file_name, "rb");
      if(!flstream)
            return false;

      fseek(flstream, 0, SEEK_END);
      file_length = ftell(flstream);
      fclose(flstream);

      //    Open the file
      FILE *stream = fopen(cell_file_name, "rb");
      if(!stream)
            return false;

      //    Validate the itegrity of the cell file

      unsigned short word0;
      int int0, int1;

      read_and_decode_ushort(stream, &word0);        // length of prolog + header (10 + 128)
      read_and_decode_int(stream, &int0);            // length of table 1
      read_and_decode_int(stream, &int1);            // length of table 2

      int test = word0 + int0 + int1;
      if(test != file_length)
      {
            fclose(stream);
            return false;                           // file is corrupt
      }

      //    Cell is OK, proceed to ingest


      if(!read_header_and_populate_cib(stream, pCIB))
      {
            fclose(stream);
            return false;
      }


      if(!read_vector_record_table(stream, pCIB->m_nvector_records, pCIB))
      {
            fclose(stream);
            return false;
      }

      if(!read_3dpoint_table(stream, pCIB->m_n_point3d_records, pCIB))
      {
            fclose(stream);
            return false;
      }

      if(!read_2dpoint_table(stream, pCIB->m_n_point2d_records, pCIB))
      {
            fclose(stream);
            return false;
      }

      if(!read_feature_record_table(stream, pCIB->m_nfeature_records, pCIB))
      {
            fclose(stream);
            return false;
      }

//      int file_end = ftell(stream);

//      wxASSERT(file_end == file_length);

      fclose(stream);


      return true;
  }

catch ( ... )
  {
//	  int yyp = 5;
        return false;
  }


}




//----------------------------------------------------------------------------------
//      cm93chart Implementation
//----------------------------------------------------------------------------------

cm93chart::cm93chart()
{
      m_ChartType = CHART_TYPE_CM93;

//    Create the decode table once, if needed
      if(!cm93_decode_table_created)
      {
            CreateDecodeTable();
            cm93_decode_table_created = true;
      }

 //    Create a global instance of the cm93 manager
      if(!s_pcm93mgr)
          s_pcm93mgr = new cm93manager();

      m_pDict = NULL;
      m_bref_is_set = false;

      m_current_cell_vearray_offset = 0;

      m_ncontour_alloc = 100;                   // allocate inital vertex count container array
      m_pcontour_array = (int *)malloc(m_ncontour_alloc * sizeof(int));

}

cm93chart::~cm93chart()
{
      for(unsigned int im=0 ; im < m_covr_array.GetCount() ; im++)
      {
            M_COVR_Desc mcd = m_covr_array.Item(im);
            free(mcd.pvertices);
      }

      free(m_pcontour_array);
}

void  cm93chart::Unload_CM93_Cell(void)
{
      free(m_CIB.pobject_block);
//      free(m_CIB.m_2a);
      free(m_CIB.p2dpoint_array);
      free(m_CIB.pprelated_object_block);
      free(m_CIB.object_vector_record_descriptor_block);
      free(m_CIB.attribute_block_top);
      free(m_CIB.edge_vector_descriptor_block);
      free(m_CIB.pvector_record_block_top);
      free(m_CIB.point3d_descriptor_block);
      free(m_CIB.p3dpoint_array);
}


//    The idea here is to suggest to upper layers the appropriate scale values to be used with this chart
//    If max is too large, performance suffers, and the charts are very cluttered onscreen.
//    If the min is too small, then the chart rendereding will be over-scaled, and accuracy suffers.
//    In some ways, this is subjective.....

double cm93chart::GetNormalScaleMin(double canvas_scale_factor)
{
      switch(GetNativeScale())
      {
            case 20000000: return 3000000.;           // Z
            case  3000000: return 1000000.;           // A
            case  1000000: return 200000.;            // B
            case   200000: return 40000.;             // C
            case   100000: return 20000.;             // D
            case    50000: return 10000.;             // E
            case    20000: return 5000.;              // F
            case     7500: return 3500.;              // G
      }

      return 1.0;
}

double cm93chart::GetNormalScaleMax(double canvas_scale_factor)
{
      switch(GetNativeScale())
      {
            case 20000000: return 50000000.;          // Z
            case  3000000: return 6000000.;           // A
            case  1000000: return 2000000.;           // B
            case   200000: return 400000.;            // C
            case   100000: return 200000.;            // D
            case    50000: return 100000.;            // E
            case    20000: return 40000.;             // F
            case     7500: return 15000.;             // G
      }

      return 1.0e7;
}

wxString cm93chart::GetName()
{
      wxString data = _T("CM93Chart ");
      data.Append(m_scalechar);
      wxString s;
      s.Printf(_T("  1/%d"), m_Chart_Scale);
      data.Append(s);
      return data;
}

void cm93chart::GetPointPix(ObjRazRules *rzRules, float north, float east, wxPoint *r)
{
      S57Obj *obj = rzRules->obj;

      double valx = (east * obj->x_rate)  + obj->x_origin;
      double valy = (north * obj->y_rate) + obj->y_origin;

            //    Crossing Greenwich right
      if(m_vp_current.vpBBox.GetMaxX() > 360.)
      {
            wxBoundingBox bbRight(0., m_vp_current.vpBBox.GetMinY(), m_vp_current.vpBBox.GetMaxX() - 360., m_vp_current.vpBBox.GetMaxY());
            if ( bbRight.Intersect ( rzRules->obj->BBObj, 0 ) != _OUT )
            {
                  valx += mercator_k0 * WGS84_semimajor_axis_meters * 2.0 * PI;      //6375586.0;
            }
      }

      r->x = (int)round(((valx - m_easting_vp_center) * m_view_scale_ppm) + m_pixx_vp_center);
      r->y = (int)round(m_pixy_vp_center - ((valy - m_northing_vp_center) * m_view_scale_ppm));
}

void cm93chart::GetPointPix(ObjRazRules *rzRules, wxPoint2DDouble *en, wxPoint *r, int nPoints)
{
      S57Obj *obj = rzRules->obj;

      double xr =  obj->x_rate;
      double xo =  obj->x_origin;
      double yr =  obj->y_rate;
      double yo =  obj->y_origin;

      //    Crossing Greenwich right
      if(m_vp_current.vpBBox.GetMaxX() > 360.)
      {
            wxBoundingBox bbRight(0., m_vp_current.vpBBox.GetMinY(), m_vp_current.vpBBox.GetMaxX() - 360., m_vp_current.vpBBox.GetMaxY());
            if ( bbRight.Intersect ( rzRules->obj->BBObj, 0 ) != _OUT )
            {
                  xo += mercator_k0 * WGS84_semimajor_axis_meters * 2.0 * PI;
            }
      }


      for(int i=0 ; i < nPoints ; i++)
      {
            double valx = (en[i].m_x * xr) + xo;
            double valy = (en[i].m_y * yr) + yo;
            r[i].x = (int)round(((valx - m_easting_vp_center) * m_view_scale_ppm) + m_pixx_vp_center);
            r[i].y = (int)round(m_pixy_vp_center - ((valy - m_northing_vp_center) * m_view_scale_ppm));
      }
}

//-----------------------------------------------------------------------
//              Calculate and Set ViewPoint Constants
//-----------------------------------------------------------------------

void cm93chart::SetVPParms(ViewPort *vpt)
{
      //    Save a copy for later reference

      m_vp_current = *vpt;

      if(!m_bref_is_set)
      {
            ref_lat = 0.;//vpt->clat;
            ref_lon = 0.;//vpt->clon;
            m_bref_is_set = true;
      }


     //  Set up local SM rendering constants
      m_pixx_vp_center = vpt->pix_width / 2;
      m_pixy_vp_center = vpt->pix_height / 2;
      m_view_scale_ppm = vpt->view_scale_ppm;

      toSM ( vpt->clat, vpt->clon, ref_lat, ref_lon, &m_easting_vp_center, &m_northing_vp_center );

      //    Fetch the lat/lon of the screen corner points
      double ll_lon = vpt->vpBBox.GetMinX();
      double ll_lat = vpt->vpBBox.GetMinY();

      double ur_lon = vpt->vpBBox.GetMaxX();
      double ur_lat = vpt->vpBBox.GetMaxY();


      //    Adjust to always positive for easier cell calculations
      if(ll_lon < 0)
      {
            ll_lon += 360;
            ur_lon += 360;
      }

      //    Create an array of CellIndexes covering the current viewport
      ArrayOfInts vpcells;

      vpcells.Clear();

      int lower_left_cell = Get_CM93_CellIndex(ll_lat, ll_lon, GetNativeScale());
      vpcells.Add(lower_left_cell);                   // always add the lower left cell

      double rlat, rlon;
      Get_CM93_Cell_Origin(lower_left_cell, GetNativeScale(), &rlat, &rlon);

      double dval;
      switch (GetNativeScale())
      {
            case 20000000: dval = 120; break;         // Z
            case  3000000: dval =  60; break;         // A
            case  1000000: dval =  30; break;         // B
            case   200000: dval =  12; break;         // C
            case   100000: dval =   3; break;         // D
            case    50000: dval =   1; break;         // E
            case    20000: dval =   1; break;         // F
            case     7500: dval =   1; break;         // G
            default: dval =   1; break;
      }


      double dlat = dval / 3.;
      double dlon = dval / 3.;


      double loni = rlon + dlon;
      double lati = rlat;

      while(lati < ur_lat)
      {
            while(loni < ur_lon)
            {
                  int next_cell = Get_CM93_CellIndex(lati, loni, GetNativeScale());
                  vpcells.Add(next_cell);

                  loni += dlon;
            }
            lati += dlat;
            loni = rlon;
      }


      //    Check the member array to see if all these viewport cells have been loaded
      bool bcell_is_in;

      for(unsigned int i=0 ; i < vpcells.GetCount() ; i++)
      {
            bcell_is_in = false;
            for(unsigned int j=0 ; j < m_cells_loaded_array.GetCount() ; j++)
            {
                  if(vpcells.Item(i) == m_cells_loaded_array.Item(j))
                  {
                        bcell_is_in = true;
                        break;
                  }
            }

            //    The cell is not in place, so go load it
            if(!bcell_is_in)
            {
                  int rv = loadcell(vpcells.Item(i));

                  //    On successful load, add it to the member list
                  if(rv)
                  {
                        m_cells_loaded_array.Add(vpcells.Item(i));
                        ForceEdgePriorityEvaluate();              // need to re-evaluate priorities
                  }
            }
      }
}


int cm93chart::loadcell(int cellindex)
{
      //    Try to load the simple case, where sub_char is '0'

      int rv = loadsubcell(cellindex, '0');

      //    Some error, maybe there are alpha subcells....
      if(!rv)
      {
            //Create file name in pieces

            int ilat = cellindex / 10000;
            int ilon = cellindex % 10000;

            int dval;
            switch (GetNativeScale())
            {
                  case 20000000: dval = 120; break;         // Z
                  case  3000000: dval =  60; break;         // A
                  case  1000000: dval =  30; break;         // B
                  case   200000: dval =  12; break;         // C
                  case   100000: dval =   3; break;         // D
                  case    50000: dval =   1; break;         // E
                  case    20000: dval =   1; break;         // F
                  case     7500: dval =   1; break;         // G
                  default: dval =   1; break;
            }


            int jlat = (((ilat - 30) / dval) * dval) + 30;              // normalize
            int jlon = (ilon / dval) * dval;

            int ilatroot = (((ilat - 30) / 60) * 60) + 30;
            int ilonroot = (ilon / 60) * 60;

            wxString file;
            file.Printf(_T("%04d%04d."), jlat, jlon);
            file += m_scalechar;

            wxString fileroot;
            fileroot.Printf(_T("%04d%04d/"), ilatroot, ilonroot);
            fileroot += m_scalechar;
            fileroot += _T("/");
            fileroot.Prepend( m_prefix );

            wxChar sub_char = 'A';

            file[0] = sub_char;
            bool b_keep_looking = true;

            while(b_keep_looking)
            {
                  file[0] = sub_char;
                  wxString lfile = file;
                  lfile.Prepend(fileroot);

                  if(::wxFileExists(lfile))
                  {
                        rv = loadsubcell(cellindex, sub_char);
                        sub_char ++;
                  }
                  else
                  {
                        b_keep_looking = false;
                  }
            }
      }

      return rv;
}




wxStopWatch *s_stw;
extern wxStopWatch *s_stwt;
wxStopWatch *s_stwl;
wxStopWatch *s_stwg;
wxStopWatch *s_stwp;


int cm93chart::loadsubcell(int cellindex, wxChar sub_char)
{
      wxBusyCursor wait;                        // This may take awhile....

      delete s_stw;
      s_stw = new wxStopWatch;
      s_stw->Pause();

      delete s_stwt;
      s_stwt = new wxStopWatch;
      s_stwt->Pause();

      delete s_stwl;
      s_stwl = new wxStopWatch;
      s_stwl->Pause();

      delete s_stwg;
      s_stwg = new wxStopWatch;
      s_stwg->Pause();

      delete s_stwp;
      s_stwp = new wxStopWatch;
      s_stwp->Pause();


      //    Create the file name

      int ilat = cellindex / 10000;
      int ilon = cellindex % 10000;

      int dval;
      switch (GetNativeScale())
      {
            case 20000000: dval = 120; break;         // Z
            case  3000000: dval =  60; break;         // A
            case  1000000: dval =  30; break;         // B
            case   200000: dval =  12; break;         // C
            case   100000: dval =   3; break;         // D
            case    50000: dval =   1; break;         // E
            case    20000: dval =   1; break;         // F
            case     7500: dval =   1; break;         // G
            default: dval =   1; break;
      }

#ifdef CM93_DEBUG_PRINTF
      double dlat = dval / 3.;
      double dlon = dval / 3.;
      double lat, lon;
      Get_CM93_Cell_Origin(cellindex, GetNativeScale(), &lat, &lon);
      printf(" loadcell %d at lat: %g/%g lon:%g/%g\n", cellindex, lat, lat + dlat, lon, lon+dlon);
#endif



      int jlat = (((ilat - 30) / dval) * dval) + 30;              // normalize
      int jlon = (ilon / dval) * dval;

      int ilatroot = (((ilat - 30) / 60) * 60) + 30;
      int ilonroot = (ilon / 60) * 60;

      wxString file;
      file.Printf(_T("%04d%04d."), jlat, jlon);
      file += m_scalechar;



      wxString fileroot;
      fileroot.Printf(_T("%04d%04d/"), ilatroot, ilonroot);
      fileroot += m_scalechar;
      fileroot += _T("/");
      fileroot.Prepend(m_prefix);

      file[0] = sub_char;
      file.Prepend(fileroot);

      if(!::wxFileExists(file))
      {
            //    Try with alternate case of m_scalechar
            wxString new_scalechar = m_scalechar.Lower();

            wxString file1;
            file1.Printf(_T("%04d%04d."), jlat, jlon);
            file1 += new_scalechar;

            file1[0] = sub_char;

            file1.Prepend(fileroot);


            if(!::wxFileExists(file1))
            {

            //    This is not really an error....
//            wxString msg(_T("   Tried to load non-existent CM93 cell "));
//            msg += file;
//            wxLogMessage(msg);

                  return 0;
            }
            else
                  file = file1;                       // found the file as lowercase, substitute the name
      }

      //    File is known to exist

      wxString msg(_T("Loading CM93 cell "));
      msg += file;
      wxLogMessage(msg);

#ifdef CM93_DEBUG_PRINTF
      {
            char str[256];
            strncpy(str, msg.mb_str(), 255);
            printf("%s\n", str);
      }
#endif


      //    Ingest it
      if(!Ingest_CM93_Cell((const char *)file.mb_str(), &m_CIB))
      {
            wxString msg(_T("   cm93chart  Error ingesting "));
            msg.Append(file);
            wxLogMessage(msg);
            return 0;
      }

      //    Create the vector(edge) table for this cell, appending to the existing member table

      m_current_cell_vearray_offset = m_nve_elements;              // add to the table at this offset
      m_nve_elements += m_CIB.m_nvector_records;

      if(NULL == m_pve_array)
            m_pve_array = (VE_Element **)malloc(m_nve_elements * sizeof(VE_Element *));
      else
            m_pve_array = (VE_Element **)realloc(m_pve_array, m_nve_elements * sizeof(VE_Element *));

      geometry_descriptor *pgd = m_CIB.edge_vector_descriptor_block;

      for(int iedge = 0 ; iedge < m_CIB.m_nvector_records ; iedge++)
      {
            VE_Element *vep = new VE_Element;
            vep->index = iedge + m_current_cell_vearray_offset;
            vep->nCount = pgd->n_points;
            vep->pPoints = NULL;
            vep->max_priority = -99;            // Default

            if(pgd->n_points)
            {
                  double *pPoints = (double *)malloc(pgd->n_points * 2 * sizeof(double));
                  vep->pPoints = pPoints;

                  cm93_point *ppt = pgd->p_points;
                  for(int ip = 0 ; ip < pgd->n_points ; ip++)
                  {
                        *pPoints++ = ppt->x;
                        *pPoints++ = ppt->y;
                        ppt++;
                  }
            }

            m_pve_array[iedge + m_current_cell_vearray_offset] = vep;

            pgd++;                              // next geometry descriptor
      }


    //  Establish a common reference point for the cell
      ref_lat = 0.;
      ref_lon = 0.;




      //    Convert directly to s57chart obj structures
 s_stw->Resume();

      CreateObjChain();

s_stw->Pause();

 wxString msgs;
 msgs.Printf(_T("ObjChain:%ld  Tess Subroutine: %ld  CreateObj: %ld Geom: %ld LUP+ %ld"), s_stw->Time(), s_stwt->Time(), s_stwl->Time(), s_stwg->Time(), s_stwp->Time());
 //wxLogMessage(msgs);

      Unload_CM93_Cell();

      return 1;
}

int cm93chart::CreateObjChain()
{
      LUPrec           *LUP;
      LUPname          LUP_Name;


      wxStopWatch stop;

 //     CALLGRIND_START_INSTRUMENTATION


      Object *pobjectDef = m_CIB.pobject_block;           // head of object array

      int iObj = 0;
      S57Obj *obj;

      while(iObj < m_CIB.m_nfeature_records/*m_header.usn_feature_records*/)
      {
//            printf("%d...%d\n", iObj, m_header.n_feature_records);

            if((pobjectDef != NULL) /*&& (iObj <= 1390)*/)  // no run at 391, ok at 390
            {

//                  if(iObj == 390)
//                        int ggl = 5;

//                  if(iObj < 10000)
                  {
//                        if(iObj == 494)
//                              int yyp = 5;

  s_stwg->Resume();
                        Extended_Geometry *xgeom = BuildGeom(pobjectDef, NULL, iObj);
  s_stwg->Pause();



                  obj = NULL;
                  if(NULL != xgeom)
                  {

                        obj = CreateS57Obj( iObj,  pobjectDef, m_pDict, xgeom, ref_lat, ref_lon, GetNativeScale(), true );

                  }

//                  if(NULL == obj)
//                        int ggs = 4;


                  if(obj)
                  {

                        //    Set the per-object transform coefficients
                        obj->x_rate   = m_CIB.transform_x_rate * (mercator_k0 * WGS84_semimajor_axis_meters / CM93_semimajor_axis_meters);
                        obj->y_rate   = m_CIB.transform_y_rate * (mercator_k0 * WGS84_semimajor_axis_meters / CM93_semimajor_axis_meters);
                        obj->x_origin = m_CIB.transform_x_origin * (mercator_k0 * WGS84_semimajor_axis_meters / CM93_semimajor_axis_meters);
                        obj->y_origin = m_CIB.transform_y_origin * (mercator_k0 * WGS84_semimajor_axis_meters / CM93_semimajor_axis_meters);


//      Build/Maintain the ATON floating/rigid arrays
                        if (GEO_POINT == obj->Primitive_type)
                        {

                        // set floating platform
                              if ((!strncmp(obj->FeatureName, "LITFLT", 6)) ||
                                    (!strncmp(obj->FeatureName, "LITVES", 6)) ||
                                    (!strncmp(obj->FeatureName, "BOY",    3)))
                                    {
                                          pFloatingATONArray->Add(obj);
                                    }

                        // set rigid platform
                              if (!strncmp(obj->FeatureName, "BCN",    3))
                              {
                                    pRigidATONArray->Add(obj);
                              }
                        }

                        //    Mark the object as an ATON
                        if ((!strncmp(obj->FeatureName,   "LIT",    3)) ||
                              (!strncmp(obj->FeatureName, "LIGHTS", 6)) ||
                              (!strncmp(obj->FeatureName, "BCN",    3)) ||
                              (!strncmp(obj->FeatureName, "_slgto", 6)) ||
                              (!strncmp(obj->FeatureName, "_boygn", 6)) ||
                              (!strncmp(obj->FeatureName, "_bcngn", 6)) ||
                              (!strncmp(obj->FeatureName, "_extgn", 6)) ||
                              (!strncmp(obj->FeatureName, "TOWERS", 6)) ||
                              (!strncmp(obj->FeatureName, "BOY",    3)))
                        {
                              obj->bIsAton = true;
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

 // Debug hooks
//        if(!strncmp(obj->FeatureName, "_m_sor", 6))
//            int ffl = 4;
//    if(obj->Index == 2173)
//        int rrt = 5;

 s_stwp->Resume();
                         LUP = ps52plib->S52_LUPLookup(LUP_Name, obj->FeatureName, obj);
  s_stwp->Pause();

                         if(NULL == LUP)
                         {
                              wxString msg(obj->FeatureName, wxConvUTF8);
                              msg.Prepend(_T("   Could not find LUP for "));
                              LogMessageOnce(msg);
                               delete obj;
                         }
                         else
                         {
//              Convert LUP to rules set
                            ps52plib->_LUP2rules(LUP, obj);

//              Add linked object/LUP to the working set
                            _insertRules(obj,LUP, this);
                         }
                    }
                  } //iObj == 390


            }

            else                    // objectdef == NULL
                  break;

            pobjectDef++;

            iObj++;
      }



 //     CALLGRIND_STOP_INSTRUMENTATION

            stop.Pause();
//            printf("ObjChain: %ld\n", stop.Time());


      return 1;
}



InitReturn cm93chart::Init( const wxString& name, ChartInitFlag flags, ColorScheme cs )
{
//      InitReturn ret_value;


      m_pFullPath = new wxString(name);

      wxFileName fn(name);

      m_scalechar = fn.GetExt();

      //    Figure out the scale from the file name

      int scale;
      switch((m_scalechar.mb_str())[(size_t)0])
      {
            case 'Z': scale = 20000000;  break;
            case 'A': scale =  3000000;  break;
            case 'B': scale =  1000000;  break;
            case 'C': scale =   200000;  break;
            case 'D': scale =   100000;  break;
            case 'E': scale =    50000;  break;
            case 'F': scale =    20000;  break;
            case 'G': scale =     7500;  break;
            default:  scale = 20000000;  break;
      }

      m_Chart_Scale = scale;




        //  Establish a common reference point for the chart
      ref_lat = 0;
      ref_lon = 0;


      if(flags == THUMB_ONLY)
      {
/*
    // Look for Thumbnail
    // Set the proper directory for the SENC/BMP files
            wxString SENCdir = *g_pSENCPrefix;

            if(SENCdir.Last() != fn.GetPathSeparator())
                  SENCdir.Append(fn.GetPathSeparator());

            wxFileName tsfn(SENCdir);
            tsfn.SetFullName(fn.GetFullName());

            wxFileName ThumbFileNameLook(tsfn);
            ThumbFileNameLook.SetExt(_T("BMP"));

            wxBitmap *pBMP;
            if(ThumbFileNameLook.FileExists())
            {
//#ifdef ocpnUSE_ocpnBitmap
//                pBMP =  new ocpnBitmap;
//#else
                  pBMP =  new wxBitmap;
//#endif
                  pBMP->LoadFile(ThumbFileNameLook.GetFullPath(), wxBITMAP_TYPE_BMP );
                  m_pDIBThumbDay = pBMP;
            }
*/
            SetColorScheme(cs, false);

            return INIT_OK;
      }


      if(flags == HEADER_ONLY)
            return CreateHeaderDataFromCM93Cell();


      //    Load the cm93 dictionary if necessary
      if(!m_pDict)
      {
            if(s_pcm93mgr->Loadcm93Dictionary(name))
                  m_pDict = s_pcm93mgr->m_pcm93Dict;
            else
            {
                  wxLogMessage(_T("   CM93Chart Init cannot locate CM93 dictionary."));
                  return INIT_FAIL_REMOVE;
            }
      }



//    Set the color scheme
      m_global_color_scheme = cs;
      SetColorScheme(cs, false);


      bReadyToRender = true;

      return INIT_OK;

}

Extended_Geometry *cm93chart::BuildGeom(Object *pobject, wxFileOutputStream *postream, int iobject)

{
      wxString s;
      int geomtype;

      int geom_type_maybe = pobject->geotype;

      switch(geom_type_maybe){
            case 1:    geomtype = 1; break;
            case 2:    geomtype = 2; break;
            case 4:    geomtype = 3; break;
            case 129:  geomtype = 1; break;
            case 130:  geomtype = 2; break;
            case 132:  geomtype = 3; break;
            case 8:    geomtype = 8; break;
            case 16:   geomtype = 16; break;
            case 161:  geomtype = 1; break;    // lighthouse first child
            case 33:   geomtype = 1; break;
            default:
                  geomtype = -1; break;
      }

      int iseg;

      Extended_Geometry *ret_ptr = new Extended_Geometry; //(Extended_Geometry *)malloc(sizeof(Extended_Geometry));

      int lon_max, lat_max, lon_min, lat_min;
      lon_max = 0; lon_min = 65536; lat_max = 0; lat_min = 65536;

      switch(geomtype){

            case 3:                               // Areas
            {
                  vector_record_descriptor *psegs = (vector_record_descriptor *)pobject->pGeometry;

                  int nsegs = pobject->n_geom_elements;

                  ret_ptr->n_vector_indices = nsegs;
                  ret_ptr->pvector_index = (int *)malloc(nsegs * 3 * sizeof(int));

                  cm93_point start_point, cur_end_point;

                  //Traverse the object once to get a maximum polygon vertex count
                  int n_maxvertex = 0;
                  for(int i=0 ; i < nsegs ; i++)
                  {
                        geometry_descriptor *pgd = (geometry_descriptor*)(psegs[i].pGeom_Description);
                        n_maxvertex += pgd->n_points;
                  }

                  n_maxvertex += 2;       // fluff


                  wxPoint2DDouble *pPoints = (wxPoint2DDouble *)malloc(n_maxvertex * sizeof(wxPoint2DDouble));

                  int ip = 1;
                  int n_prev_vertex_index = 1;
                  bool bnew_ring = true;
                  int ncontours = 0;
                  iseg = 0;

                  while(iseg < nsegs)
                  {

                        int type_seg = psegs[iseg].segment_usage;

                        geometry_descriptor *pgd = (geometry_descriptor*)(psegs[iseg].pGeom_Description);

                        int npoints = pgd->n_points;
                        cm93_point *rseg = pgd->p_points;


                        //    Establish ring starting conditions
                        if(bnew_ring)
                        {
                              bnew_ring = false;

                              if((type_seg & 4) == 0)
                                    start_point = rseg[0];
                              else
                                    start_point = rseg[npoints-1];
                        }



                        if(((type_seg & 4) == 0))
                        {
                              cur_end_point = rseg[npoints-1];
                              for(int j=0 ; j<npoints  ; j++)
                              {
//                                    if(ncontours == 0)                             // outer ring describes envelope
                                    {
                                          lon_max = wxMax(lon_max, rseg[j].x);
                                          lon_min = wxMin(lon_min, rseg[j].x);
                                          lat_max = wxMax(lat_max, rseg[j].y);
                                          lat_min = wxMin(lat_min, rseg[j].y);
                                    }

                                    pPoints[ip].m_x = rseg[j].x;
                                    pPoints[ip].m_y = rseg[j].y;
                                    ip++;
                              }
                       }
                        else if((type_seg & 4) == 4)        // backwards
                        {
                              cur_end_point = rseg[0];
                              for(int j=npoints-1 ; j>= 0  ; j--)
                              {
//                                    if(ncontours == 0)                             // outer ring describes envelope
                                    {
                                          lon_max = wxMax(lon_max, rseg[j].x);
                                          lon_min = wxMin(lon_min, rseg[j].x);
                                          lat_max = wxMax(lat_max, rseg[j].y);
                                          lat_min = wxMin(lat_min, rseg[j].y);
                                    }

                                    pPoints[ip].m_x = rseg[j].x;
                                    pPoints[ip].m_y = rseg[j].y;
                                    ip++;
                              }
                        }

                        ip--;                                                 // skip the last point in each segment

                        ret_ptr->pvector_index[iseg * 3 + 0] = -1;                 // first connected node
                        ret_ptr->pvector_index[iseg * 3 + 1] = pgd->index + m_current_cell_vearray_offset;         // edge index
                        ret_ptr->pvector_index[iseg * 3 + 2] = -2;                 // last connected node

                        if((cur_end_point.x == start_point.x) && (cur_end_point.y == start_point.y))
                        {
                              // done with a ring

                              ip++;                                                 // leave in ring closure point

                              int nRingVertex = ip - n_prev_vertex_index;

                              //    possibly increase contour array size
                              if(ncontours > m_ncontour_alloc - 1)
                              {
                                    m_ncontour_alloc *= 2;
                                    m_pcontour_array = (int *)realloc(m_pcontour_array, m_ncontour_alloc * sizeof(int));
                              }
                              m_pcontour_array[ncontours] = nRingVertex;               // store the vertex count

                              bnew_ring = true;                                               // set for next ring
                              n_prev_vertex_index = ip;
                              ncontours++;

                        }
                        iseg++;
                  }           // while iseg



                  ret_ptr->n_contours = ncontours;                          // parameters passed to trapezoid tesselator

                  ret_ptr->contour_array = (int *)malloc(ncontours * sizeof(int));
                  memcpy(ret_ptr->contour_array, m_pcontour_array, ncontours * sizeof(int));

                  ret_ptr->vertex_array = pPoints;
                  ret_ptr->n_max_vertex = n_maxvertex;

                  ret_ptr->pogrGeom = NULL;

                  ret_ptr->xmin = lon_min;
                  ret_ptr->xmax = lon_max;
                  ret_ptr->ymin = lat_min;
                  ret_ptr->ymax = lat_max;

                  break;
            }           // case 3



            case 1:     //single points
            {
                  cm93_point *pt = (cm93_point *)pobject->pGeometry;
                  ret_ptr->pogrGeom = NULL; //t;

                  ret_ptr->pointx = pt->x;
                  ret_ptr->pointy = pt->y;
                  break;
            }

            case 2:                                               // LINE geometry
            {
                  vector_record_descriptor *psegs = (vector_record_descriptor *)pobject->pGeometry;

                  int nsegs = pobject->n_geom_elements;

                  ret_ptr->n_vector_indices = nsegs;
                  ret_ptr->pvector_index = (int *)malloc(nsegs * 3 * sizeof(int));

                  //    Calculate the number of points
                  int n_maxvertex = 0;
                  for(int imseg = 0 ; imseg < nsegs ; imseg++)
                  {
                        geometry_descriptor *pgd = (geometry_descriptor*)psegs->pGeom_Description;

                        n_maxvertex += pgd->n_points;
                        psegs++;
                  }


                  wxPoint2DDouble *pPoints = (wxPoint2DDouble *)malloc(n_maxvertex * sizeof(wxPoint2DDouble));

                  psegs = (vector_record_descriptor *)pobject->pGeometry;

                  int ip = 0;
                  int lon_max, lat_max, lon_min, lat_min;
                  lon_max = 0; lon_min = 65536; lat_max = 0; lat_min = 65536;

                  for(int iseg = 0 ; iseg < nsegs ; iseg++)
                  {

                        int type_seg = psegs->segment_usage;

                        geometry_descriptor *pgd = (geometry_descriptor*)psegs->pGeom_Description;

                        psegs++;          // next segment

                        int npoints = pgd->n_points;
                        cm93_point *rseg = pgd->p_points;


                        if(((type_seg & 4) != 4))
                        {
                              for(int j=0 ; j<npoints  ; j++)
                              {
                                    lon_max = wxMax(lon_max, rseg[j].x);
                                    lon_min = wxMin(lon_min, rseg[j].x);
                                    lat_max = wxMax(lat_max, rseg[j].y);
                                    lat_min = wxMin(lat_min, rseg[j].y);

                                    pPoints[ip].m_x = rseg[j].x;
                                    pPoints[ip].m_y = rseg[j].y;
                                    ip++;

                              }
                        }

                        else if((type_seg & 4) == 4)        // backwards
                        {
                              for(int j=npoints-1 ; j>= 0  ; j--)
                              {
                                     lon_max = wxMax(lon_max, rseg[j].x);
                                     lon_min = wxMin(lon_min, rseg[j].x);
                                     lat_max = wxMax(lat_max, rseg[j].y);
                                     lat_min = wxMin(lat_min, rseg[j].y);

                                     pPoints[ip].m_x = rseg[j].x;
                                     pPoints[ip].m_y = rseg[j].y;
                                     ip++;
                              }
                        }

                        ret_ptr->pvector_index[iseg * 3 + 0] = -1;                 // first connected node
                        ret_ptr->pvector_index[iseg * 3 + 1] = pgd->index + m_current_cell_vearray_offset;         // edge index
                        ret_ptr->pvector_index[iseg * 3 + 2] = -2;                 // last connected node

                  }           //for

                  ret_ptr->vertex_array = pPoints;
                  ret_ptr->n_max_vertex = n_maxvertex;

                  ret_ptr->pogrGeom = NULL;

                  ret_ptr->xmin = lon_min;
                  ret_ptr->xmax = lon_max;
                  ret_ptr->ymin = lat_min;
                  ret_ptr->ymax = lat_max;

                  break;
            }           //case 2  (lines)

            case 8:
            {
                  geometry_descriptor *pgd = (geometry_descriptor*)pobject->pGeometry;

                  int npoints = pgd->n_points;
                  cm93_point_3d *rseg = (cm93_point_3d *)pgd->p_points;

                  OGRMultiPoint *pSMP = new OGRMultiPoint;

                  int z;
                  double zp;
                  for(int ip=0 ; ip < npoints ; ip++)
                  {
                        z = rseg[ip].z;

                        //    This is a magic number if there ever was one.....
                        if(z >= 12000)
                              zp = double(z - 12000);
                        else
                              zp = z / 10.;

                        OGRPoint *ppoint = new OGRPoint(rseg[ip].x, rseg[ip].y, zp);
                        pSMP->addGeometryDirectly( ppoint );

                        lon_max = wxMax(lon_max, rseg[ip].x);
                        lon_min = wxMin(lon_min, rseg[ip].x);
                        lat_max = wxMax(lat_max, rseg[ip].y);
                        lat_min = wxMin(lat_min, rseg[ip].y);

                  }

                  ret_ptr->pogrGeom = pSMP;

                  ret_ptr->xmin = lon_min;
                  ret_ptr->xmax = lon_max;
                  ret_ptr->ymin = lat_min;
                  ret_ptr->ymax = lat_max;


                  break;
            }


            case 16:
                  break;                        // this is the case of objects with children
                                                      // the parent has no geometry.....

            default:
            {
                  wxPrintf(_T("Unexpected geomtype %d for Feature %d\n"), geomtype,iobject);
                  break;
            }

      }     // switch


      return ret_ptr;
}

void cm93chart::Transform(cm93_point *s, double *lat, double *lon)
{
      //    Simple linear transform
      double valx = (s->x * m_CIB.transform_x_rate) + m_CIB.transform_x_origin;
      double valy = (s->y * m_CIB.transform_y_rate) + m_CIB.transform_y_origin;


      //    Convert to lat/lon
      *lat = (2.0 * atan(exp(valy/CM93_semimajor_axis_meters)) - PI/2.) / DEGREE;

      *lon = (valx / (DEGREE * CM93_semimajor_axis_meters));
}


cm93_attr_block::cm93_attr_block(void * block, cm93_dictionary *pdict)
{
      m_cptr = 0;
      m_block = (unsigned char *)block;
      m_pDict = pdict;
}


unsigned char *cm93_attr_block::GetNextAttr()
{
      //    return current pointer
      unsigned char *ret_val = m_block + m_cptr;

      //    Advance the pointer

      unsigned char iattr = *(m_block + m_cptr);
      m_cptr++;

//      char vtype = m_pDict->m_ValTypeArray[iattr];
      char vtype = m_pDict->GetAttrType(iattr);

      switch(vtype){
            case 'I':                           // never seen?
                  m_cptr += 2;
                  break;
            case 'B':
                  m_cptr += 1;
//                  pb = (unsigned char *)aval;
//                  sprintf(val, "%d", *pb);
//                  pvtype = 'I';                 // override
                  break;
            case 'S':
                  while(*(m_block + m_cptr))
                        m_cptr++;
                  m_cptr++;                           // skip terminator
//                  sprintf(val, "%s", aval);
                  break;
            case 'R':
                  m_cptr += 4;
//                  pf = (float *)aval;
//                  sprintf(val, "%g", *pf);
                  break;
            case 'W':
                  m_cptr += 2;
                  break;
            case 'G':
                  m_cptr += 4;
                  break;
            case 'C':
                  m_cptr += 3;
                  while(*(m_block + m_cptr))
                        m_cptr++;
                  m_cptr++;                           // skip terminator
//                  sprintf(val, "%s", &aval[3]);
//                  pvtype = 'S';                 // override
                  break;
            case 'L':
            {
                  unsigned char nl = *(m_block + m_cptr);
                  m_cptr++;
                  m_cptr += nl;

//                  pb = (unsigned char *)aval;
//                  unsigned char nl = *pb++;
//                  char vi[20];
//                  val[0] = 0;
//                  for(int i=0 ; i<nl ; i++)
//                  {
//                        sprintf(vi, "%d,", *pb++);
//                        strcat(val, vi);
//                  }
//                  if(strlen(val))
//                        val[strlen(val)-1] = 0;         // strip last ","
//                  pvtype = 'S';                 // override
                  break;
            }
            default:
//                  sprintf(val, "Unknown Value Type");
                  break;
      }

      return ret_val;

}

/*
4,1,"conical (nun, ogival)"
4,2,can (cylindrical)
4,3,spherical
4,4,pillar
4,5,spar (spindle)
4,6,barrel (tun)
4,7,super-buoy
4,8,ice buoy

75,1,white
75,2,black
75,3,red
75,4,green
75,5,blue
75,6,yellow
75,7,grey
75,8,brown
75,9,amber
75,10,violet
75,11,orange
75,12,magenta
75,13,pink
*/




wxString ParseSLGTA(wxString& val)
{
      wxString result;
      char line[30];

      wxString s;
      wxStringTokenizer tkz(val, wxT("|"));

      s = tkz.GetNextToken();
      s = tkz.GetNextToken();
      s = tkz.GetNextToken();             // Mark attributes

      //  Defaults, black can
      wxString sc, st, sp;
      int color = 0;  sc = _T("");
      int type = 0;   st = _T("");
      int colpat = 0; sp = _T("");

      if(s[0] == 'R')
      {
            color = 3;
            sc = _T("3");
      }

      else if(s[0] == 'G')
      {
            color = 4;
            sc = _T("4");
      }
      else if(s.Mid(0,3) == _T("W/O"))
      {
            color = 1;
            sc = _T("1,11");

            colpat = 1;
            sp = _T("1");
      }
      else if(s.Mid(0,5) == _T("LIGHT"))
      {
            color = 0;
            type = 0;
      }


      if(val.Find(_T("Spar")) !=  wxNOT_FOUND)
      {
            type = 5;
            st = _T("5");
      }
      if(val.Find(_T("SPAR")) !=  wxNOT_FOUND)
      {
            type = 5;
            st = _T("5");
      }

      if((type == 2) && (color == 3))     // red can?
      {
            type = 1;                      // change to nun
            st = _T("1");
      }


      if(color)
      {
            sprintf( line, "  %s (%c) = %s", "COLOUR", 'I', (const char *)sc.mb_str());
            result += wxString(line, wxConvUTF8);
            result += '\n';
            if(!type)
            {
                  sprintf( line, "  %s (%c) = %s", "BOYSHP", 'I', "4");
                  result += wxString(line, wxConvUTF8);
                  result += '\n';
            }

      }

      if(type)
      {
            sprintf( line, "  %s (%c) = %s", "BOYSHP", 'I', (const char *)st.mb_str());
            result += wxString(line, wxConvUTF8);
            result += '\n';
            if(!color)
            {
                  sprintf( line, "  %s (%c) = %s", "COLOUR", 'I', "2");
                  result += wxString(line, wxConvUTF8);
                  result += '\n';
            }
      }


      if(colpat)
      {
            sprintf( line, "  %s (%c) = %s", "COLPAT", 'I', (const char *)sp.mb_str());
            result += wxString(line, wxConvUTF8);
            result += '\n';
      }


      return result;
}


wxString ParseTEXTA(wxString& val)
{
      wxString result;
      char line[30];

      if(val.Contains(_T("WK S")))
      {
            sprintf( line, "  %s (%c) = %s", "WRKATT", 'I', "1");
            result += wxString(line, wxConvUTF8);
            result += '\n';
      }

      return result;
}




void cm93chart::translate_colmar(wxString &sclass, S57attVal *pattValTmp)
{
      int *pcur_attr = (int *)pattValTmp->value;
      int cur_attr = *pcur_attr;

      wxString lstring;

      switch(cur_attr)
      {
            case 1: lstring = _T("4"); break;               // green
            case 2: lstring = _T("2"); break;               // black
            case 3: lstring = _T("3"); break;               // red
            case 4: lstring = _T("6"); break;               // yellow
            case 5: lstring = _T("1"); break;               // white
            case 6: lstring = _T("11"); break;              // orange
            case 7: lstring = _T("2,6"); break;             // black/yellow
            case 8: lstring = _T("2,6,2"); break;           // black/yellow/black
            case 9: lstring = _T("6,2"); break;              // yellow/black
            case 10: lstring = _T("6,2,6"); break;           // yellow/black/yellow
            case 11: lstring = _T("3,1"); break;             // red/white
            case 12: lstring = _T("4,3,4"); break;           // green/red/green
            case 13: lstring = _T("3,4,3"); break;           // red/green/red
            case 14: lstring = _T("2,3,2"); break;           // black/red/black
            case 15: lstring = _T("6,3,6"); break;           // yellow/red/yellow
            case 16: lstring = _T("4,3"); break;             // green/red
            case 17: lstring = _T("3,4"); break;             // red/green
            case 18: lstring = _T("4,1"); break;             // green/white
            default: break;
      }

      if(lstring.Len())
      {
            free(pattValTmp->value);                          // free the old int pointer

            pattValTmp->valType = OGR_STR;
            pattValTmp->value = (char *)malloc(lstring.Len() + 1);      // create a new Lstring attribute
            strcpy((char *)pattValTmp->value, lstring.mb_str());

      }
}


S57Obj *cm93chart::CreateS57Obj( int iobject, Object *pobject, cm93_dictionary *pDict, Extended_Geometry *xgeom,
                                     double ref_lat, double ref_lon, double scale,
                                     bool bDeleteGeomInline)
{
 s_stwl->Resume();

#define MAX_HDR_LINE    4000

// printf("%d\n", iobject);

      int npub_year;

      int iclass = pobject->otype;
      int geomtype = pobject->geotype & 0x0f;

//        if(geomtype == 2)
//              return;

        // Debug Hook
//      if(iobject == 4415)
//            int ffk = 3;

      wxString sclass = pDict->GetClassName(iclass);
      if(sclass == _T("Unknown"))
      {
            wxString msg;
            msg.Printf(_T("   CM93 Error...object type %d not found in CM93OBJ.DIC"), iclass);
            wxLogMessage(msg);
            return NULL;
      }

//      wxString sclass = pDict->m_S57ClassArray->Item(iclass);
      wxString sclass_sub = sclass;

        //  Going to make some substitutions here
      if(sclass.IsSameAs(_T("ITDARE")))
          sclass_sub = _T("DEPARE");

      if(sclass.IsSameAs(_T("_m_sor")))
         sclass_sub = _T("M_COVR");

      if(sclass.IsSameAs(_T("SPOGRD")))
            sclass_sub = _T("DMPGRD");

      if(sclass.IsSameAs(_T("FSHHAV")))
            sclass_sub = _T("FSHFAC");





//        else if(sclass.IsSameAs(_T("_texto")))
//             sclass_sub = _T("$TEXTS");

      /*
      _cmapl|L|7|Line, generic|_lcode|INFORM|NINFOM|SCAMAX|SCAMIN|RECDAT|RECIND|SORDAT|SORIND
      _texto|198|P|8|Text|$JUSTH|$JUSTV|$SPACE|$CHARS|$COLOR|$ROTAT|_texta|INFORM|NINFOM|SCAMAX|SCAMIN|RECDAT|RECIND|SORDAT|SORIND
      _slgto|199|P|8|Navigational aid, generic|_slgta|INFORM|NINFOM|SCAMAX|SCAMIN|RECDAT|RECIND|SORDAT|SORIND
      _boygn|200|P|8|Buoy, generic|BOYSHP|COLMAR|COLPAT|CONRAD|DATEND|DATSTA|MARSYS|NOBJNM|OBJNAM|PEREND|PERSTA|QUAVEM|STATUS|VERLEN|INFORM|NINFOM|PICREP|SCAMAX|SCAMIN|RECDAT|RECIND|SORDAT|SORIND
      _extgn|201|P|8|Extended navigational aid, generic|CATCAM|CATLAM|COLMAR|MARSYS|NOBJNM|OBJNAM|INFORM|NINFOM|SCAMAX|SCAMIN|RECDAT|RECIND|SORDAT|SORIND
      _cmapa|202|LA|4|Area, generic|_acode|INFORM|NINFOM|SCAMAX|SCAMIN|RECDAT|RECIND|SORDAT|SORIND
      _bcngn|203|P|8|Beacon, generic|BCNSHP|COLMAR|COLPAT|CONRAD|DATEND|DATSTA|MARSYS|NOBJNM|OBJNAM|PEREND|PERSTA|QUAVEM|STATUS|VERDAT|VERLEN|INFORM|NINFOM|PICREP|SCAMAX|SCAMIN|RECDAT|RECIND|SORDAT|SORIND
      _m_sor|217|A|0|Source of data|CSCALE|DUNITS|HUNITS|HORACC|NMDATE|HORDAT|_sorhd|_wgsox|_wgsoy|SORDAT|SORIND|VERACC|VERDAT|_hvdat|MARSYS|_chcod|_dgdat|_quart|INFORM|NINFOM|RECDAT|RECIND
      */


      //    Create the S57 Object
      S57Obj *pobj = new S57Obj();

      pobj->Index = iobject;

      char u[200];
      strncpy(u, sclass_sub.mb_str(), 199);
      strncpy(pobj->FeatureName, u, 7);

    //  Touch up the geom types
      int geomtype_sub = geomtype;
      if(geomtype == 8)                       // sounding....
            geomtype_sub = 1;

      if(geomtype == 4)                       // convert cm93 area(4) to GDAL area(3)...
            geomtype_sub = 3;

//      pobj->prim = geomtype_sub;

        //  Debug hook
//        if(sclass.IsSameAs((char *)"OBSTRN"))
//              int ggk = 5;


      pobj->attList = new wxString();
      pobj->attVal =  new wxArrayOfS57attVal();


      cm93_attr_block *pab = new cm93_attr_block(pobject->attributes_block, pDict);


      for( int jattr = 0 ; jattr  < pobject->n_attributes ; jattr++)
      {

            unsigned char *curr_attr = pab->GetNextAttr();

            unsigned char iattr = *curr_attr;

            wxString sattr = pDict->GetAttrName(iattr);

            char vtype = pDict->GetAttrType(iattr);

            unsigned char *aval = curr_attr + 1;

                   //  Debug hook
//            if(sattr.IsSameAs((char *)"SIGPER"))
//                  int ggk = 5;


            char val[4000];
            int *pi;
            float *pf;
            unsigned short *pw;
            unsigned char *pb;
            int *pAVI;
            char *pAVS;
            double *pAVR;
            int nlen;
            double dival;
            int ival;

            S57attVal *pattValTmp = new S57attVal;

            switch(vtype){
                  case 'I':                           // never seen?
                        pi = (int *)aval;
                        pAVI = (int *)malloc(sizeof(int));         //new int;
                        *pAVI = *pi;
                        pattValTmp->valType = OGR_INT;
                        pattValTmp->value   = pAVI;
                        break;
                  case 'B':
                        pb = (unsigned char *)aval;
                        pAVI = (int *)malloc(sizeof(int));         //new int;
                        *pAVI = (int)(*pb);
                        pattValTmp->valType = OGR_INT;
                        pattValTmp->value   = pAVI;
                        break;
                  case 'W':                                       // aWORD10
                        pw = (unsigned short *)aval;
                        ival = (int)(*pw);
                        dival = ival;

                        pAVR = (double *)malloc(sizeof(double));   //new double;
                        *pAVR = dival/10.;
                        pattValTmp->valType = OGR_REAL;
                        pattValTmp->value   = pAVR;
                        break;
                  case 'G':
                        pi = (int *)aval;
                        pAVI = (int *)malloc(sizeof(int));         //new int;
                        *pAVI = (int)(*pi);
                        pattValTmp->valType = OGR_INT;
                        pattValTmp->value   = pAVI;
                        break;

                  case 'S':
                        nlen = strlen((const char *)aval);
                        pAVS = (char *)malloc(nlen + 1);          ;
                        strcpy(pAVS,(char *) aval);
                        pattValTmp->valType = OGR_STR;
                        pattValTmp->value   = pAVS;
                        break;

                  case 'C':
                        nlen = strlen((const char *)&aval[3]);
                        pAVS = (char *)malloc(nlen + 1);          ;
                        strcpy(pAVS, (const char *)&aval[3]);
                        pattValTmp->valType = OGR_STR;
                        pattValTmp->value   = pAVS;
                        break;
                  case 'L':
                  {
                        pb = (unsigned char *)aval;
                        unsigned char nl = *pb++;
                        char vi[20];
                        val[0] = 0;
                        for(int i=0 ; i<nl ; i++)
                        {
                              sprintf(vi, "%d,", *pb++);
                              strcat(val, vi);
                        }
                        if(strlen(val))
                              val[strlen(val)-1] = 0;         // strip last ","

                        int nlen = strlen(val);
                        pAVS = (char *)malloc(nlen + 1);          ;
                        strcpy(pAVS, val);
                        pattValTmp->valType = OGR_STR;
                        pattValTmp->value   = pAVS;
                        break;
                  }
                  case 'R':
                        pf = (float *)aval;
                        pAVR = (double *)malloc(sizeof(double));   //new double;
                        *pAVR = *pf;
                        pattValTmp->valType = OGR_REAL;
                        pattValTmp->value   = pAVR;
                        break;
                  default:
                        sattr.Clear();               // Unknown, TODO track occasional case '?'
                        break;
            }     // switch


            if(sattr.IsSameAs(_T("COLMAR")))
            {
                  translate_colmar(sclass, pattValTmp);
                  sattr = _T("COLOUR");
            }




//            Next:  consider added LUPS for _extgn objects like boylat(w/catlam and colour(or colmar));
//            Like Winyah bay entrance channel


/*
            if(sclass.IsSameAs(_T("_slgto")) && (vtype == 'S') && sattr.IsSameAs(_T("_slgta")))
            {
                  wxString aa(val, wxConvUTF8);
                  wxString add_attr = ParseSLGTA(aa);
                  sheader += add_attr;
            }



            if(sclass.IsSameAs(_T("_texto")) && (vtype == 'C') && sattr.IsSameAs(_T("_texta")))
            {
                  wxString aa(val, wxConvUTF8);
                  wxString add_attr = ParseTEXTA(aa);
                  sheader += add_attr;
            }
*/

            //    Do CM93 $SCODE attribute substitutions
            if(sclass.IsSameAs(_T("$AREAS")) && (vtype == 'S') && sattr.IsSameAs(_T("$SCODE")))
            {
                  if(!strcmp((char *)pattValTmp->value, "II25"))
                  {
                        free (pattValTmp->value);
                        pattValTmp->value   = (char *) malloc (strlen("BACKGROUND"));
                        strcpy((char *)pattValTmp->value, "BACKGROUND");
                  }
            }


            //    Capture some attributes on the fly as needed
            if(sattr.IsSameAs(_T("RECDAT")) || sattr.IsSameAs(_T("_dgdat")))
            {
                  if(sclass_sub.IsSameAs(_T("M_COVR")) && (vtype == 'S') )
                  {
                        wxString pub_year((char *)pattValTmp->value, wxConvUTF8);
                        pub_year.Truncate(4);

                        long nyear = 0;
                        pub_year.ToLong(&nyear);
                        npub_year = nyear;
                  }
            }


            if(sattr.Len())
            {
                  pobj->attList->Append(sattr);
                  pobj->attList->Append('\037');

                  pobj->attVal->Add(pattValTmp);
            }
            else
                  delete pattValTmp;


      }     //for

      delete pab;

/*
        //  Add any attributes unspecified by CMAP

      if(sclass.IsSameAs(_T("SOUNDG")))
      {
            sprintf( line, "  %s (%c) = %d", "SCAMIN", 'I', (int)(scale * 2));
            sheader += wxString(line, wxConvUTF8);
            sheader += '\n';
      }

      else if(sclass.IsSameAs(_T("ITDARE")))
      {
            sprintf( line, "  %s (%c) = %g\n", "DRVAL1", 'R', -0.8);
            sheader += wxString(line, wxConvUTF8);
            sprintf( line, "  %s (%c) = %g\n", "DRVAL2", 'R', 0.);
            sheader += wxString(line, wxConvUTF8);
      }

      else if(sclass.IsSameAs(_T("_texto")))
      {
            sprintf( line, "  %s (%c) = %d", "SCAMIN", 'I', (int)(scale * 3));      // increase to make visible at higher scale
            sheader += wxString(line, wxConvUTF8);
            sheader += '\n';
      }
*/

      //    ATON label optimization:
      //    Some CM93 ATON objects do not contain OBJNAM attribute, which means that no label is shown
      //    for these objects when ATON labals are requested
      //    Look for these cases, and change the OBJNAM attribute label to INFORM, if present.


      if (1 == geomtype)
      {
            if ((!strncmp(pobj->FeatureName,   "LIT",    3)) ||
                  (!strncmp(pobj->FeatureName, "LIGHTS", 6)) ||
                  (!strncmp(pobj->FeatureName, "BCN",    3)) ||
                  (!strncmp(pobj->FeatureName, "_slgto", 6)) ||
                  (!strncmp(pobj->FeatureName, "_boygn", 6)) ||
                  (!strncmp(pobj->FeatureName, "_bcngn", 6)) ||
                  (!strncmp(pobj->FeatureName, "_extgn", 6)) ||
                  (!strncmp(pobj->FeatureName, "TOWERS", 6)) ||
                  (!strncmp(pobj->FeatureName, "BOY",    3)))
                  {
                        // Walk the attribute list  looking for OBJNAM and INFORM
                        char *curr_att0 = (char *)calloc(pobj->attList->Len()+1, 1);
                        strncpy(curr_att0, pobj->attList->mb_str(), pobj->attList->Len());
                        char *curr_att = curr_att0;

                        int iatt = 0;
                        int iOBJNAM, iINFORM;
                        bool bfound_OBJNAM = false;
                        bool bfound_INFORM = false;

                        char *pszatt_name;
                        char *psz_INFORM;
                        wxString att;

                        while(*curr_att)
                        {
                              pszatt_name = curr_att;       //Pointer to current attribute name

                              att.Clear();
                              while((*curr_att) && (*curr_att != '\037'))
                              {
                                    char t = *curr_att++;
                                    att.Append(t);
                              }

                              if(*curr_att == '\037')
                                    curr_att++;


                              if(att.IsSameAs(_T("OBJNAM")))
                              {
                                    iOBJNAM = iatt;
                                    bfound_OBJNAM = true;
                              }


                              if(att.IsSameAs(_T("INFORM")))
                              {
                                    iINFORM = iatt;
                                    bfound_INFORM = true;
                                    psz_INFORM = pszatt_name;
                              }

//  Debug
/*
                              S57attVal *pval;
                              pval = pobj->attVal->Item(iatt);
                              if(pval->valType == OGR_STR)
                              {
                                    char * t = (char *)pval->value;

                                    if(!strncmp((const char *)pval->value, "R_CONOLL", 8))
                                          int yyp = 5;
                              }
*/

                              iatt++;
                        }

                        if((!bfound_OBJNAM) && (bfound_INFORM))               // can make substitution
                        {
                              memcpy(psz_INFORM, "OBJNAM", 6);               // make it
                              pobj->attList->Clear();
                              pobj->attList->Append(wxString(curr_att0, wxConvUTF8));
                        }

                        free(curr_att0);

                  }
      }



      double lat, lon;

      switch(geomtype){
            case 4:
            {
                  pobj->Primitive_type = GEO_AREA;

                  //    Check for and maintain the array of M_COVR polygons for hit testing
                  if(sclass_sub.IsSameAs(_T("M_COVR")))
                  {
                        double lat, lon;

                        M_COVR_Desc *pmcd = new M_COVR_Desc;

                  //    Record the Publication Year of this cell
                        pmcd->m_npub_year = npub_year;

                  //      Get number of exterior ring points(vertices)
                        int npta  = xgeom->contour_array[0];
                        pt *geoPt = (pt*)malloc((npta + 2) * sizeof(pt));     // vertex array
                        pt *ppt = geoPt;

//  Transcribe exterior ring points to vertex array, in Lat/Lon coordinates
                        for(int ip = 0 ; ip < npta ; ip++)
                        {
                              cm93_point p;
                              p.x = (int)xgeom->vertex_array[ip + 1].m_x;
                              p.y = (int)xgeom->vertex_array[ip + 1].m_y;
                              Transform(&p, &lat, &lon);
                              ppt->x = lon;
                              ppt->y = lat;

                              ppt++;
                        }
                        pmcd->m_nvertices = npta;
                        pmcd->pvertices = (double *)geoPt;

                       //     Add this geometry to the M_COVR array
                        m_covr_array.Add(pmcd);
                  }


                  PolyTessGeoTrap *ppg = new PolyTessGeoTrap(xgeom, ref_lat, ref_lon);

                  pobj->pPolyTrapGeo = ppg;

                  //  Set the s57obj bounding box as lat/lon
                  double lat, lon;
                  cm93_point p;

                  p.x = (int)xgeom->xmin;
                  p.y = (int)xgeom->ymin;
                  Transform(&p, &lat, &lon);
                  pobj->BBObj.SetMin(lon, lat);

                  p.x = (int)xgeom->xmax;
                  p.y = (int)xgeom->ymax;
                  Transform(&p, &lat, &lon);
                  pobj->BBObj.SetMax(lon, lat);


                  //  and declare x/y of the object to be average of all cm93points
                  pobj->x = (xgeom->xmin + xgeom->xmax) / 2.;
                  pobj->y = (xgeom->ymin + xgeom->ymax) / 2.;

                  //    associate the vector(edge) index table
                  pobj->m_n_lsindex = xgeom->n_vector_indices;
                  pobj->m_lsindex_array = xgeom->pvector_index;         // object now owns the array

                  break;

            }


            case 1:
            {
                  pobj->Primitive_type = GEO_POINT;
                  pobj->npt = 1;


                  pobj->x = xgeom->pointx;
                  pobj->y = xgeom->pointy;

                  double lat, lon;
                  cm93_point p;
                  p.x = xgeom->pointx;
                  p.y = xgeom->pointy;
                  Transform(&p, &lat, &lon);

                  pobj->BBObj.SetMin(lon, lat);
                  pobj-> BBObj.SetMax(lon, lat);

                  break;
            }



            case 8:               //wkbMultiPoint25D:
            {


                  pobj->Primitive_type = GEO_POINT;

                  OGRMultiPoint *pGeo = (OGRMultiPoint *)xgeom->pogrGeom;
                  pobj->npt = pGeo->getNumGeometries();

                  pobj->geoPtz = (double *)malloc(pobj->npt * 3 * sizeof(double));
                  pobj->geoPtMulti = (double *)malloc(pobj->npt * 2 * sizeof(double));

                  double *pdd = pobj->geoPtz;
                  double *pdl = pobj->geoPtMulti;


                  for(int ip=0 ; ip<pobj->npt ; ip++)
                  {
                        OGRPoint *ppt = (OGRPoint *)(pGeo->getGeometryRef( ip ));

                        cm93_point p;
                        p.x = (int)ppt->getX();
                        p.y = (int)ppt->getY();
                        double depth = ppt->getZ();

                        *pdd++ = p.x;
                        *pdd++ = p.y;
                        *pdd++ = depth;

                        Transform(&p, &lat, &lon);

                        //  Save lat/lon of point in obj->geoPtMulti for later use in decomposed bboxes

                        *pdl++ = lon;
                        *pdl++ = lat;
                  }

                  //  Set the s57obj bounding box as lat/lon
                  double lat, lon;
                  cm93_point p;

                  p.x = (int)xgeom->xmin;
                  p.y = (int)xgeom->ymin;
                  Transform(&p, &lat, &lon);
                  pobj->BBObj.SetMin(lon, lat);

                  p.x = (int)xgeom->xmax;
                  p.y = (int)xgeom->ymax;
                  Transform(&p, &lat, &lon);
                  pobj->BBObj.SetMax(lon, lat);


                  //  and declare x/y of the object to be average of all cm93points
                  pobj->x = (xgeom->xmin + xgeom->xmax) / 2.;
                  pobj->y = (xgeom->ymin + xgeom->ymax) / 2.;

                  if(bDeleteGeomInline)
                        delete pGeo;

                  break;
            }         // case 8





            case 2:
            {
                  pobj->Primitive_type = GEO_LINE;

                  pobj->npt = xgeom->n_max_vertex;
                  pobj->geoPt = (pt *)xgeom->vertex_array;


                  //  Set the s57obj bounding box as lat/lon
                  double lat, lon;
                  cm93_point p;

                  p.x = (int)xgeom->xmin;
                  p.y = (int)xgeom->ymin;
                  Transform(&p, &lat, &lon);
                  pobj->BBObj.SetMin(lon, lat);

                  p.x = (int)xgeom->xmax;
                  p.y = (int)xgeom->ymax;
                  Transform(&p, &lat, &lon);
                  pobj->BBObj.SetMax(lon, lat);

                  //  and declare x/y of the object to be average of all cm93points
                  pobj->x = (xgeom->xmin + xgeom->xmax) / 2.;
                  pobj->y = (xgeom->ymin + xgeom->ymax) / 2.;

                  //    associate the vector(edge) index table
                  pobj->m_n_lsindex = xgeom->n_vector_indices;
                  pobj->m_lsindex_array = xgeom->pvector_index;         // object now owns the array

                  break;

            }                // case 2
            default:
            {
                  //TODO GEO_PRIM here is a placeholder.  Trace this code....
                  pobj->Primitive_type = GEO_PRIM;
                  break;
            }

      }         // geomtype switch


   //      Build/Maintain a list of found OBJL types for later use
   //      And back-reference the appropriate list index in S57Obj for Display Filtering

      bool bNeedNew = true;
      OBJLElement *pOLE;



      if(pobj)
      {
            for(unsigned int iPtr = 0 ; iPtr < ps52plib->pOBJLArray->GetCount() ; iPtr++)
            {
            pOLE = (OBJLElement *)(ps52plib->pOBJLArray->Item(iPtr));
            if(!strncmp(pOLE->OBJLName, pobj->FeatureName, 6))
            {
                  pobj->iOBJL = iPtr;
                  bNeedNew = false;
                  break;
            }
            }

            if(bNeedNew)
            {
            pOLE = (OBJLElement *)malloc(sizeof(OBJLElement));
            strcpy(pOLE->OBJLName, pobj->FeatureName);
            pOLE->nViz = 1;

            ps52plib->pOBJLArray->Add((void *)pOLE);
            pobj->iOBJL  = ps52plib->pOBJLArray->GetCount() - 1;
            }
      }


s_stwl->Pause();


      // Everything in Xgeom that is needed later has been given to the object
      // So, the xgeom object can be deleted
      if(bDeleteGeomInline)
          free(xgeom);

      return pobj;
}






#include <wx/arrimpl.cpp>
WX_DEFINE_ARRAY(float*, MyFloatPtrArray1);



//    Read the cm93 cell file header and create required Chartbase data structures
InitReturn cm93chart::CreateHeaderDataFromCM93Cell(void)
{

      //    Figure out the scale from the file name
      wxFileName fn(*m_pFullPath);
      wxString ext = fn.GetExt();

      int scale;
      switch((ext.mb_str())[(size_t)0])
      {
            case 'Z': scale = 20000000;  break;
            case 'A': scale =  3000000;  break;
            case 'B': scale =  1000000;  break;
            case 'C': scale =   200000;  break;
            case 'D': scale =   100000;  break;
            case 'E': scale =    50000;  break;
            case 'F': scale =    20000;  break;
            case 'G': scale =     7500;  break;
            default:  scale = 20000000;  break;
      }

      m_Chart_Scale = scale;



      //    Check with the manager to see if a chart of this scale has been processed
      bool bproc;
      switch(m_Chart_Scale)
      {
      case 20000000: bproc = s_pcm93mgr->m_bfoundZ; break;
      case  3000000: bproc = s_pcm93mgr->m_bfoundA; break;
      case  1000000: bproc = s_pcm93mgr->m_bfoundB; break;
      case   200000: bproc = s_pcm93mgr->m_bfoundC; break;
      case   100000: bproc = s_pcm93mgr->m_bfoundD; break;
      case    50000: bproc = s_pcm93mgr->m_bfoundE; break;
      case    20000: bproc = s_pcm93mgr->m_bfoundF; break;
      case     7500: bproc = s_pcm93mgr->m_bfoundG; break;
      }


      if(bproc)
            return INIT_FAIL_NOERROR;



//      if(!Ingest_CM93_Cell((*m_pFullPath).mb_str(), &m_header, &m_CIB))
//            return INIT_FAIL_REMOVE;


      //    Inform the manager that a chart of this scale has been processed
      switch(m_Chart_Scale)
      {
      case 20000000: s_pcm93mgr->m_bfoundZ = true; break;
      case  3000000: s_pcm93mgr->m_bfoundA = true; break;
      case  1000000: s_pcm93mgr->m_bfoundB = true; break;
      case   200000: s_pcm93mgr->m_bfoundC = true; break;
      case   100000: s_pcm93mgr->m_bfoundD = true; break;
      case    50000: s_pcm93mgr->m_bfoundE = true; break;
      case    20000: s_pcm93mgr->m_bfoundF = true; break;
      case     7500: s_pcm93mgr->m_bfoundG = true; break;
      }


      //    Specify the whole world as chart coverage
      m_FullExtent.ELON = 179.0;
      m_FullExtent.WLON = -179.0;
      m_FullExtent.NLAT = 70.0;
      m_FullExtent.SLAT = -70.0;
      m_bExtentSet = true;


      //    Populate one (huge) M_COVR Entry
      m_nCOVREntries = 1;
      m_pCOVRContourTable = (int *)malloc(sizeof(int));
      *m_pCOVRContourTable = 4;
      m_pCOVRTable = (float **)malloc(sizeof(float *));
      float *pf = (float *)malloc(2 * 4 * sizeof(float));
      *m_pCOVRTable = pf;
      float *pfe = pf;

      *pfe++ = m_FullExtent.NLAT; //LatMax;
      *pfe++ = m_FullExtent.WLON; //LonMin;

      *pfe++ = m_FullExtent.NLAT; //LatMax;
      *pfe++ = m_FullExtent.ELON; //LonMax;

      *pfe++ = m_FullExtent.SLAT; //LatMin;
      *pfe++ = m_FullExtent.ELON; //LonMax;

      *pfe++ = m_FullExtent.SLAT; //LatMin;
      *pfe++ = m_FullExtent.WLON; //LonMin;



      return INIT_OK;
}


//-----------------------------------------------------------------------------------------------
//  cm93manager Implementation
//-----------------------------------------------------------------------------------------------

cm93manager::cm93manager(void)
{

    m_pcm93Dict = NULL;


    m_bfoundA = false;
    m_bfoundB = false;
    m_bfoundC = false;
    m_bfoundD = false;
    m_bfoundE = false;
    m_bfoundF = false;
    m_bfoundG = false;
    m_bfoundZ = false;

}

cm93manager::~cm93manager(void)
{
      delete m_pcm93Dict;
}

bool cm93manager::Loadcm93Dictionary(wxString name)
{

      //  Find and load cm93_dictionary
      if(!m_pcm93Dict)
      {
            m_pcm93Dict = FindAndLoadDict(name);

            if(!m_pcm93Dict)
            {
                  wxLogMessage(_T("   Cannot load CM93 Dictionary."));
                  return false;
            }


           if(!m_pcm93Dict->IsOk())
            {
                  wxLogMessage(_T("   Error in loading CM93 Dictionary."));
                  delete m_pcm93Dict;
                  m_pcm93Dict = NULL;
                  return false;;
            }
      }
      else if(!m_pcm93Dict->IsOk())
      {
            wxLogMessage(_T("   CM93 Dictionary is not OK."));
            return false;
      }

      return true;
}

cm93_dictionary *cm93manager::FindAndLoadDict(const wxString &file)
{
      cm93_dictionary *retval = NULL;
      cm93_dictionary *pdict = new cm93_dictionary();

      //    Search for the dictionary files all along the path of the passed parameter filename

      wxFileName fn(file);
      wxString path = fn.GetPath((int)(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME));
      wxString target;
      unsigned int i = 0;

//      if(path[0] == fn.GetPathSeparator())      // path starts with sep
//            target.Append(path[i++]);

      while(i < path.Len())
      {
            target.Append(path[i]);
            if(path[i] == fn.GetPathSeparator())
            {
                  if(pdict->LoadDictionary(target))
                  {
                        retval = pdict;
                        break;
                  }
                  if(pdict->LoadDictionary(target + _T("CM93ATTR")))
                  {
                        retval = pdict;
                        break;
                  }
            }
            i++;
      }

      char t[100];
      strncpy(t, target.mb_str(), 99);

      if(retval == NULL)
            delete pdict;

      return retval;


}


//----------------------------------------------------------------------------
// cm93 Composite Chart object class Implementation
//----------------------------------------------------------------------------
cm93compchart::cm93compchart()
{
      m_ChartType = CHART_TYPE_CM93COMP;
      m_pDict = NULL;

      //    Supply a default name for status bar field
      m_pFullPath = new wxString(_T("CM93"));

      for(int i = 0 ; i < 8 ; i++)
            m_pcm93chart_array[i] = NULL;

      m_pcm93chart_current = NULL;

      m_cmscale = -1;

}

cm93compchart::~cm93compchart()
{
      for(int i = 0 ; i < 7 ; i++)
            delete m_pcm93chart_array[i];

      delete m_pDict;
}


InitReturn cm93compchart::Init( const wxString& name, ChartInitFlag flags, ColorScheme cs )
{
      //    Update the FullPath with the exact value
      m_pFullPath->Clear();
      m_pFullPath->Append(name);

      wxFileName fn(name);

      //    Verify that the passed file name exists
      if(!fn.FileExists())
      {
            wxString msg(_T("   CM93Composite Chart Init cannot find "));
            msg.Append(name);
            wxLogMessage(msg);
            return INIT_FAIL_REMOVE;
      }

      //    Get the cm93 cell database prefix
      //    Search for the directory called 00300000 all along the path of the passed parameter filename
      wxString path = fn.GetPath((int)(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME));
      wxString target;
      unsigned int i = 0;

      while(i < path.Len())
      {
            target.Append(path[i]);
            if(path[i] == fn.GetPathSeparator())
            {
                  wxString dirtest = target;
                  dirtest << _T("00300000");
                  if(wxFileName::DirExists(dirtest))
                        break;
            }
            i++;
      }
      m_prefix = target;



      if(flags == THUMB_ONLY)
      {
            SetColorScheme(cs, false);

            return INIT_OK;
      }


      if(flags == HEADER_ONLY)
            return CreateHeaderData();


      //    Load the cm93 dictionary if necessary
      if(!m_pDict)
      {
            if(g_CM93DictDir.Len())                 // a hint...
                  m_pDict = FindAndLoadDictFromDir(g_CM93DictDir);

            if(!m_pDict)                              // second try from the file
                  m_pDict = FindAndLoadDictFromDir(path);

            if(!m_pDict)
            {
                  wxLogMessage(_T("   CM93Composite Chart Init cannot locate CM93 dictionary."));
                  return INIT_FAIL_REMOVE;
            }

            else
            {
                  if(pConfig)                                           // update the hint
                  {
                        if(!m_pDict->GetDictDir().IsSameAs(g_CM93DictDir))
                        {
                              g_CM93DictDir = m_pDict->GetDictDir();
                              pConfig->UpdateSettings();
                        }
                  }
            }

      }


//    Set the color scheme
      m_global_color_scheme = cs;
      SetColorScheme(cs, false);


//      ps52plib->SetTextOverlapAvoid(true);
//      ps52plib->SetShowAtonText(false);

      bReadyToRender = true;

      return INIT_OK;


}



//-----------------------------------------------------------------------
//              Calculate and Set ViewPoint Constants
//-----------------------------------------------------------------------

void cm93compchart::SetVPParms(ViewPort *vpt)
{
      double scale_mpp = 3000 / vpt->view_scale_ppm;

      int cmscale = 7;
      while(cmscale > 0)
      {

            if(scale_mpp < 5000)
                  break;                        // G, 7500
            cmscale--;

            if(scale_mpp < 15000/*10000*/)
                  break;                        // F, 20000
            cmscale--;

            if(scale_mpp < 40000/*30000*/)
                  break;                        // E, 50000
            cmscale--;

            if(scale_mpp < 150000)
                  break;                        // D, 100000
            cmscale--;

            if(scale_mpp < 300000)
                  break;                        // C, 200000
            cmscale--;

            if(scale_mpp < 1000000)
                  break;                        // B, 1000000
            cmscale--;

            if(scale_mpp < 3000000)
                  break;                        // A, 3000000
            cmscale--;
      }

#ifdef CM93_DEBUG_PRINTF
//      if(cmscale != m_cmscale)
            printf("on SetVPParms, scale_mpp %g...resulting in cmscale:%d, %c\n", scale_mpp, cmscale, (char)('A' + cmscale -1));
#endif

      m_cmscale = cmscale;

      wxChar ext;
      bool cellscale_is_useable = false;

      while(!cellscale_is_useable)
      {
      //    Open the proper scale chart, if not already open
            while(NULL == m_pcm93chart_array[cmscale])
            {
                  if(Is_CM93Cell_Present(m_prefix, vpt->clat, vpt->clon, cmscale))
                  {
#ifdef CM93_DEBUG_PRINTF
                        printf(" chart %c at VP clat/clon is present\n", (char)('A' + cmscale -1));
#endif
                        m_pcm93chart_array[cmscale] = new cm93chart();


                        ext = (wxChar)('A' + cmscale - 1);
                        if(cmscale == 0)
                              ext = 'Z';

                        wxString file_dummy = _T("CM93.");
                        file_dummy << ext;

                        m_pcm93chart_array[cmscale]->SetCM93Dict(m_pDict);
                        m_pcm93chart_array[cmscale]->SetCM93Prefix(m_prefix);

                        m_pcm93chart_array[cmscale]->Init( file_dummy, FULL_INIT, m_global_color_scheme );
                  }
                  else if(cmscale == 0)
                  {
                        wxString msg;
                        msg.Printf(_T("   CM93 finds no chart of any scale present at Lat/Lon  %g %g"), vpt->clat, vpt->clon);
                        wxLogMessage(msg);
#ifdef CM93_DEBUG_PRINTF
                        printf("   CM93 finds no chart of any scale present at Lat/Lon  %g %g\n", vpt->clat, vpt->clon);
#endif
                        break;
                  }

                  else
                  {
                        cmscale--;                          // revert to larger scale if selected is not present
#ifdef CM93_DEBUG_PRINTF
                        printf(" no %c scale chart present, adjusting cmscale to %c\n", (char)('A' + cmscale), (char)('A' + cmscale -1));
#endif
                  }

            }

            m_pcm93chart_current = m_pcm93chart_array[cmscale];

            //    Pass the parameters to the proper scale chart
            //    Which will also load the needed cell(s)
            m_pcm93chart_current->SetVPParms(vpt);

            //    Check to see if the viewpoint center is actually on the selected chart
            float yc = vpt->clat;
            float xc = vpt->clon;


            while(xc < 0)
            {
                  xc += 360.;
            }

            bool bin_mcovr = false;
            if(!m_pcm93chart_current->m_covr_array.GetCount())
            {
#ifdef CM93_DEBUG_PRINTF
                  printf(" chart %c has no M_COVR\n", (char)('A' + cmscale -1));
#endif
            }


            for(unsigned int im=0 ; im < m_pcm93chart_current->m_covr_array.GetCount() ; im++)
            {
                  M_COVR_Desc mcd = m_pcm93chart_current->m_covr_array.Item(im);

                  if(G_PtInPolygon((MyPoint *)mcd.pvertices, mcd.m_nvertices, xc, yc))
                  {
                        bin_mcovr = true;

                        //    As an assist for later, record the publish date of the cell at the ViewPort clat/clon
                        m_current_cell_pub_date = mcd.m_npub_year;
                        break;
                  }
            }


            if(bin_mcovr)
            {
#ifdef CM93_DEBUG_PRINTF
                  printf(" chart %c contains clat/clon\n", (char)('A' + cmscale -1));
#endif
                  cellscale_is_useable = true;
                  break;
            }

            else if(cmscale == 0)
            {
                  cellscale_is_useable = true;
                  break;
            }

            else
            {
                  cmscale--;        // revert to larger scale if the current scale cells do not contain VP
#ifdef CM93_DEBUG_PRINTF
                  printf(" VP is not in M_COVR, adjusting cmscale to %c\n", (char)('A' + cmscale -1));
#endif
            }

      }
}

//    Populate the member bool array describing which chart scales are available at any location
void cm93compchart::FillScaleArray(double lat, double lon)
{
      for(int cmscale = 0 ; cmscale < 8 ; cmscale++)
            m_bScale_Array[cmscale] = Is_CM93Cell_Present(m_prefix, lat, lon, cmscale);
}

//    These methods simply pass the called parameters to the currently active cm93chart
wxString cm93compchart::GetFullPath()
{
      //TODO this doesnt work since method is called only once on composite chart load,
      // and the particular CM93Chart to be used is unknown, and the scale is unknown....
/*
      if(NULL != m_pcm93chart_current)
            return m_pcm93chart_current->GetFullPath(data);
      else
            return;
*/
      return _T("CM93Composite");
}

wxString cm93compchart::GetName()
{

      if(NULL != m_pcm93chart_current)
            return m_pcm93chart_current->GetName();
      else
            return _T("CM93CompositeName");
}

wxString cm93compchart::GetPubDate()
{
      wxString data;

      if(NULL != m_pcm93chart_current)

            data.Printf(_T("%4d"), m_current_cell_pub_date);
      else
            data = _T("????");
      return data;
}

int cm93compchart::GetNativeScale()
{
      if(m_pcm93chart_current)
            return m_pcm93chart_current->GetNativeScale();
      else
            return 1;
}

double cm93compchart::GetNormalScaleMin(double canvas_scale_factor)
{
      if(m_pcm93chart_current)
      {
            if(m_pcm93chart_current->m_last_vp.IsValid())
                  FillScaleArray(m_pcm93chart_current->m_last_vp.clat,m_pcm93chart_current-> m_last_vp.clon);

            //    Find out what the smallest available scale is
            int cmscale = 7;
            while(cmscale > 0)
            {
                  if(m_bScale_Array[cmscale])
                        break;
                  cmscale--;
            }

            //    And return a sensible minimum scale, allowing 4x overzoom.
            switch(cmscale)
            {
                  case  0: return 20000000. / 4.;            // Z
                  case  1: return 3000000.  / 4.;            // A
                  case  2: return 1000000.  / 4.;            // B
                  case  3: return 200000.   / 4.;            // C
                  case  4: return 100000.   / 4.;            // D
                  case  5: return 50000.    / 4.;            // E
                  case  6: return 20000.    / 4.;            // F
                  case  7: return 7500.     / 4.;            // G
                  default: return 10.;
            }
      }
      else
            return 10.0;
}

double cm93compchart::GetNormalScaleMax(double canvas_scale_factor)
{
      return 1.0e8;
}


void cm93compchart::SetVPPositive(ViewPort *pvp)
{
      while(pvp->vpBBox.GetMinX() < 0)
      {
            pvp->clon += 360.;
            wxPoint2DDouble t(360., 0.);
            pvp->vpBBox.Translate(t);
      }
}

bool cm93compchart::RenderViewOnDC(wxMemoryDC& dc, ViewPort& VPoint, ScaleTypeEnum scale_type)
{
      ViewPort *pvp_positive = new ViewPort;
      *pvp_positive = VPoint;

      SetVPPositive(pvp_positive);
      m_pcm93chart_current->SetVPParms(pvp_positive);

      bool render_return = m_pcm93chart_current->RenderViewOnDC(dc, *pvp_positive, scale_type);

      delete pvp_positive;
      return render_return;
}

void cm93compchart::GetPointPix(ObjRazRules *rzRules, float rlat, float rlon, wxPoint *r)
{
      m_pcm93chart_current->GetPointPix(rzRules, rlat, rlon, r);
}

void cm93compchart::GetPointPix(ObjRazRules *rzRules, wxPoint2DDouble *en, wxPoint *r, int nPoints)
{
      m_pcm93chart_current->GetPointPix(rzRules, en, r, nPoints);
}

void cm93compchart::GetPixPoint(int pixx, int pixy, double *plat, double *plon, ViewPort *vpt)
{
      m_pcm93chart_current->GetPixPoint(pixx, pixy, plat, plon, vpt);
}

void cm93compchart::UpdateLUPs(s57chart *pOwner)
{
      for(int i = 0 ; i < 8 ; i++)
      {
            if(m_pcm93chart_array[i])
                  m_pcm93chart_array[i]->UpdateLUPs(pOwner);
      }
}

void cm93compchart::InvalidateCache()
{
      for(int i = 0 ; i < 8 ; i++)
      {
            if(m_pcm93chart_array[i])
                  m_pcm93chart_array[i]->InvalidateCache();
      }
}

void cm93compchart::ForceEdgePriorityEvaluate(void)
{
      for(int i = 0 ; i < 8 ; i++)
      {
            if(m_pcm93chart_array[i])
                  m_pcm93chart_array[i]->ForceEdgePriorityEvaluate();
      }
}

ListOfS57Obj *cm93compchart::GetObjListAtLatLon(float lat, float lon, float select_radius, ViewPort *VPoint)
{
      float alon = lon;

      while(alon < 0)               // CM93 longitudes are all positive
            alon += 360;

      ViewPort *pvp_positive = new ViewPort;          // needs a new ViewPort also for ObjectRenderCheck()
      *pvp_positive = *VPoint;

      SetVPPositive(pvp_positive);

      return  m_pcm93chart_current->GetObjListAtLatLon(lat, alon, select_radius, pvp_positive);
}

S57ObjectDesc *cm93compchart::CreateObjDescription(const S57Obj *obj)
{
      return m_pcm93chart_current->CreateObjDescription(obj);
}

int cm93compchart::Get_nve_elements(void)
{
      return m_pcm93chart_current->Get_nve_elements();
}

int cm93compchart::Get_nvc_elements(void)
{
      return m_pcm93chart_current->Get_nvc_elements();
}


VE_Element **cm93compchart::Get_pve_array(void)
{
      return m_pcm93chart_current->Get_pve_array();
}

VC_Element **cm93compchart::Get_pvc_array(void)
{
      return m_pcm93chart_current->Get_pvc_array();
}

bool cm93compchart::AdjustVP(ViewPort &vp_last, ViewPort &vp_proposed)
{
//      SetVPParms ( &vp_proposed );                    // This will ensure that the required CM93 cell is loaded

      if(NULL != m_pcm93chart_current)
            return m_pcm93chart_current->AdjustVP(vp_last, vp_proposed);
      else
            return false;
}

bool cm93compchart::IsRenderDelta(ViewPort &vp_last, ViewPort &vp_proposed)
{
      if(NULL != m_pcm93chart_current)
            return m_pcm93chart_current->IsRenderDelta(vp_last, vp_proposed);
      else
            return true;
}

ThumbData *cm93compchart::GetThumbData(int tnx, int tny, float lat, float lon)
{
      return (ThumbData *)NULL;
}

InitReturn cm93compchart::CreateHeaderData()
{

      m_Chart_Scale = 20000000;

      //    Specify the whole world as chart coverage
      //    Note the odd longitude range, to align with cm93 cell boundaries
      m_FullExtent.ELON = 360.0;
      m_FullExtent.WLON = -360.0;
      m_FullExtent.NLAT = 80.0;
      m_FullExtent.SLAT = -80.0;
      m_bExtentSet = true;


      //    Populate one (huge) M_COVR Entry
      m_nCOVREntries = 1;
      m_pCOVRContourTable = (int *)malloc(sizeof(int));
      *m_pCOVRContourTable = 4;
      m_pCOVRTable = (float **)malloc(sizeof(float *));
      float *pf = (float *)malloc(2 * 4 * sizeof(float));
      *m_pCOVRTable = pf;
      float *pfe = pf;

      *pfe++ = m_FullExtent.NLAT; //LatMax;
      *pfe++ = m_FullExtent.WLON; //LonMin;

      *pfe++ = m_FullExtent.NLAT; //LatMax;
      *pfe++ = m_FullExtent.ELON; //LonMax;

      *pfe++ = m_FullExtent.SLAT; //LatMin;
      *pfe++ = m_FullExtent.ELON; //LonMax;

      *pfe++ = m_FullExtent.SLAT; //LatMin;
      *pfe++ = m_FullExtent.WLON; //LonMin;


      return INIT_OK;
}

cm93_dictionary *cm93compchart::FindAndLoadDictFromDir(const wxString &dir)
{
      cm93_dictionary *retval = NULL;
      cm93_dictionary *pdict = new cm93_dictionary();

      //    Quick look at the supplied directory...
      if(pdict->LoadDictionary(dir))
            return pdict;


      //    Otherwise, search for the dictionary files all along the path of the passed parameter

      wxString path = dir;
      wxString target;
      unsigned int i = 0;

      while(i < path.Len())
      {
            target.Append(path[i]);
            if(path[i] == wxFileName::GetPathSeparator())
            {
                  if(pdict->LoadDictionary(target))
                  {
                        retval = pdict;
                        break;
                  }
            }
            i++;
      }

      if(NULL != retval)                              // Found it....
            return retval;




      //    Dictionary was not found in linear path of supplied dir.
      //    Could be on branch, so, look at entire tree the hard way.

      wxFileName fnc(dir);
      wxString found_dict_file_name;

      bool bdone = false;
      while (!bdone)
      {
            path = fnc.GetPath(wxPATH_GET_VOLUME);        // get path without sep


            if((path.Len() == 0) || path.IsSameAs(fnc.GetPathSeparator()))
            {
                  bdone = true;
                  break;
            }

            //    Abort the search loop if the directory tree does not contain some indication of CM93
            if((wxNOT_FOUND == path.Find((const wxChar *)"cm93")) && (wxNOT_FOUND == path.Find((const wxChar *)"CM93")))
            {
                  bdone = true;
                  break;
            }

//    Search here
//    This takeas a while to search a fully populated cm93 tree....
            wxDir dir(path);
            if(dir.IsOpened())
            {
                  found_dict_file_name = dir.FindFirst(path, _T("CM93OBJ.dic"));
                  if(found_dict_file_name.Len())
                        bdone = true;

                  else
                  {
                        found_dict_file_name = dir.FindFirst(path, _T("CM93OBJ.DIC"));
                        if(found_dict_file_name.Len())
                               bdone = true;
                  }
            }

            fnc.Assign(path);                                 // convert the path to a filename for next loop
      }

      if(found_dict_file_name.Len())
      {
            wxFileName fnd(found_dict_file_name);
            wxString dpath = fnd.GetPath((int)(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME));

            if(pdict->LoadDictionary(dpath))
                  retval = pdict;
      }


      if(NULL == retval)
            delete pdict;

      return retval;


}


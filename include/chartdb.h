/******************************************************************************
 * $Id: chartdb.h,v 1.14 2009/08/22 01:17:52 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Chart Database Object
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
 * $Log: chartdb.h,v $
 * Revision 1.14  2009/08/22 01:17:52  bdbcat
 * Better CM93 detect
 *
 * Revision 1.13  2009/06/18 01:33:35  bdbcat
 * Allow u/l case dir search.
 *
 * Revision 1.12  2009/05/05 04:02:49  bdbcat
 * *** empty log message ***
 *
 * Revision 1.11  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.10  2008/10/27 03:06:13  bdbcat
 * Fix Chartstack ctor
 *
 * Revision 1.9  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
 *
 * Revision 1.8  2008/03/30 23:21:45  bdbcat
 * *** empty log message ***
 *
 * $Log: chartdb.h,v $
 * Revision 1.14  2009/08/22 01:17:52  bdbcat
 * Better CM93 detect
 *
 * Revision 1.13  2009/06/18 01:33:35  bdbcat
 * Allow u/l case dir search.
 *
 * Revision 1.12  2009/05/05 04:02:49  bdbcat
 * *** empty log message ***
 *
 * Revision 1.11  2009/03/26 22:35:35  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.10  2008/10/27 03:06:13  bdbcat
 * Fix Chartstack ctor
 *
 * Revision 1.9  2008/08/09 23:36:46  bdbcat
 * *** empty log message ***
 *
 * Revision 1.8  2008/03/30 23:21:45  bdbcat
 * *** empty log message ***
 *
 * Revision 1.7  2008/01/12 06:18:22  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.6  2007/06/10 02:37:18  bdbcat
 * Cleanup
 *
 * Revision 1.5  2007/05/03 13:31:19  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.4  2007/03/02 02:04:09  dsr
 * Cleanup
 *
 * Revision 1.3  2006/10/08 00:36:25  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 *
 *
 */

#ifndef __CHARTDB_H__
#define __CHARTDB_H__


#include "wx/file.h"
#include "wx/stream.h"
#include "wx/wfstream.h"
#include "wx/tokenzr.h"
#include "wx/dir.h"
#include "wx/filename.h"
#include "chartbase.h"        // for enum ChartInitFlag

#define     MAXSTACK          20

#include "s52s57.h"           //types


// ----------------------------------------------------------------------------
//    Constants, etc.
// ----------------------------------------------------------------------------

#define           DB_VERSION  14


typedef struct  {
    float y;
    float x;
} MyFlPoint;


// ----------------------------------------------------------------------------
//    Fwd Declarations
// ----------------------------------------------------------------------------
class ChartBase;

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

class ChartTableEntry
{
public:
      int         EntryOffset;
      int         ChartType;
      char        ChartID[16];
      float       LatMax;
      float       LatMin;
      float       LonMax;
      float       LonMin;
      char        *pFullPath;
      int         Scale;
      time_t      edition_date;
      float       *pPlyTable;
      int         nPlyEntries;
      int         nAuxPlyEntries;
      float       **pAuxPlyTable;
      int         *pAuxCntTable;
      bool        bValid;

};

class ChartStack
{
public:
      ChartStack() { nEntry = 0; CurrentStackEntry = 0;}

      int         nEntry;
      int         CurrentStackEntry;
      int         DBIndex[MAXSTACK];
};

class ChartTableHeader
{
public:
      char        dbVersion[4];
      int         nTableEntries;
      int         nDirEntries;
};

class CacheEntry
{
public:
      wxString    FullPath;
      void        *pChart;
      int         RecentTime;
};



// ----------------------------------------------------------------------------
// Chart Database
// ----------------------------------------------------------------------------

class ChartDB
{
public:

      ChartDB(MyFrame *parent);
      virtual ~ChartDB();

      bool Create(wxArrayString *dir_list, bool show_prog = true);
      bool Update(wxArrayString *dir_list, bool show_prog = true);


      bool LoadBinary(wxString *filename);
      bool SaveBinary(wxString *filename, wxArrayString *pChartDirArray);
      int  BuildChartStack(ChartStack * cstk, float lat, float lon);
      bool EqualStacks(ChartStack *, ChartStack *);
      bool CopyStack(ChartStack *pa, ChartStack *pb);
      wxString GetFullPath(ChartStack *ps, int stackindex);
      bool GetChartID(ChartStack *ps, int stackindex, char *buf, int nbuf);
      int  GetStackChartScale(ChartStack *ps, int stackindex, char *buf, int nbuf);
      int  GetCSPlyPoint(ChartStack *ps, int stackindex, int plyindex, float *lat, float *lon);
      int  GetCSChartType(ChartStack *ps, int stackindex);
      ChartFamilyEnum GetCSChartFamily(ChartStack *ps, int stackindex);
      int  GetDBChartType(int dbIndex);
      bool GetDBFullPath(int dbIndex, char *buf);
      bool GetDBBoundingBox(int dbindex, wxBoundingBox *box);
      bool SearchForChartDir(wxString &dir);
      ChartBase *OpenStackChartConditional(ChartStack *ps, bool bLargest, ChartTypeEnum New_Type, ChartFamilyEnum New_Family_Fallback);

      int  GetnAuxPlyEntries(int dbIndex){ return pChartTable[dbIndex].nAuxPlyEntries; }
      int  GetDBPlyPoint(int dbIndex, int plyindex, float *lat, float *lon);
      int  GetDBAuxPlyPoint(int dbIndex, int plyindex, int iAuxPly, float *lat, float *lon);


      virtual int  GetStackEntry(ChartStack *ps, wxString *pfp);
      ChartBase *OpenChartFromStack(ChartStack *pStack, int StackEntry, ChartInitFlag iflag = FULL_INIT);
      int DisableChart(wxString& PathToDisable);
      void ApplyColorSchemeToCachedCharts(ColorScheme cs);

      bool DetectDirChange(wxString dir_path, wxString magic, wxString &new_magic);

      // Public data
      //Todo build accessors
      int   nEntry;

      wxArrayPtrVoid    *pChartCache;

private:

      InitReturn CreateChartTableEntry(wxString full_name, ChartTableEntry *pEntry);
      int TraverseDirAndAddCharts(wxString dir_name, bool bshow_prog, bool bupdate, wxString& dir_magic);
      int SearchDirAndAddCharts(wxString& dir, const wxString& filespec, bool bshow_prog, bool bupdate, bool bCheckBothCases = false);

      int SearchDirAndAddSENC(wxString& dir, bool bshow_prog, bool bupdate);
      bool CreateS57SENCChartTableEntry(wxString full_name, ChartTableEntry *pEntry, Extent *pext);

      MyFrame           *pParent;
      wxFileInputStream *ifs;

      bool              bValid;
      ChartTableEntry   *pChartTable;

};


#endif


/******************************************************************************
 * $Id: chartdb.h,v 1.7 2008/01/12 06:18:22 bdbcat Exp $
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

#define           DB_VERSION  13


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
      ChartStack() { nEntry = 0; }

      int         nEntry;
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
      int  GetDBPlyPoint(int dbIndex, int plyindex, float *lat, float *lon);
      int  GetCSChartType(ChartStack *ps, int stackindex);
      int  GetDBChartType(int dbIndex);
      bool GetDBFullPath(int dbIndex, char *buf);
      bool GetDBBoundingBox(int dbindex, wxBoundingBox *box);

      virtual int  GetStackEntry(ChartStack *ps, wxString *pfp);
      ChartBase *OpenChartFromStack(ChartStack *pStack, int StackEntry, ChartInitFlag iflag = FULL_INIT);
      int DisableChart(wxString& PathToDisable);
      void ApplyColorSchemeToCachedCharts(ColorScheme cs);

      // Public data
      //Todo build accessors
      int   nEntry;

      wxArrayPtrVoid    *pChartCache;

private:

      bool CreateBSBChartTableEntry(wxString full_name, ChartTableEntry *pEntry);
      bool CreateS57ChartTableEntry(wxString full_name, ChartTableEntry *pEntry, Extent *pext);
      int TraverseDirAndAddBSB(wxString dir_name, bool bshow_prog, bool bupdate);
      int SearchDirAndAddBSB(wxString& dir, const wxString& filespec, bool bshow_prog, bool bupdate);
      int TraverseDirAndAddS57(wxString dir_name, bool bshow_prog, bool bupdate);
      int SearchDirAndAddS57(wxString& dir, bool bshow_prog, bool bupdate);


      MyFrame           *pParent;
      wxFileInputStream *ifs;

      bool              bValid;
      ChartTableEntry   *pChartTable;

};


//--------------------------------------------------------------------------------------------------------
//    Dir Traverser used for Chart file search
//--------------------------------------------------------------------------------------------------------
    class wxDirTraverserCharts : public wxDirTraverser    {
          public:
                wxDirTraverserCharts(wxArrayString& files, wxArrayString& dirs ) : m_files(files),
                m_dirs(dirs) { }
                virtual wxDirTraverseResult OnFile(const wxString& filename)
                {
                      m_files.Add(filename);
                      return wxDIR_CONTINUE;
                }
                virtual wxDirTraverseResult OnDir(const wxString& dirname)
                {
                      m_dirs.Add(dirname);
                      return wxDIR_CONTINUE;
                }
          private:
                wxArrayString& m_files;
                wxArrayString& m_dirs;
    };
#endif


/******************************************************************************
 * $Id: chartdb.h,v 1.4 2007/03/02 02:04:09 dsr Exp $
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
 * Revision 1.4  2007/03/02 02:04:09  dsr
 * Cleanup
 *
 * Revision 1.3  2006/10/08 00:36:25  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:38:23  dsr
 * Major refactor/cleanup
 *
 * Revision 1.1.1.1  2006/08/21 05:52:11  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.4  2006/07/05 02:33:48  dsr
 * DB Version 13
 *
 * Revision 1.3  2006/06/15 02:36:25  dsr
 * New Database Version
 *
 * Revision 1.2  2006/06/02 02:04:40  dsr
 * Localize MyFlPoint
 *
 * Revision 1.1.1.1  2006/04/19 03:23:27  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.6  2006/04/19 00:55:10  dsr
 * Implement ColorScheme
 *
 * Revision 1.5  2006/03/16 03:28:12  dsr
 * Cleanup tabs
 *
 * Revision 1.4  2006/02/23 01:17:32  dsr
 * Cleanup
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
      bool GetFullPath(ChartStack *ps, int stackindex, char *buf);
      bool GetChartID(ChartStack *ps, int stackindex, char *buf);
      int  GetStackChartScale(ChartStack *ps, int stackindex, char *buf);
      int  GetCSPlyPoint(ChartStack *ps, int stackindex, int plyindex, float *lat, float *lon);
      int  GetDBPlyPoint(int dbIndex, int plyindex, float *lat, float *lon);
      int  GetCSChartType(ChartStack *ps, int stackindex);
      int  GetDBChartType(int dbIndex);
      bool GetDBFullPath(int dbIndex, char *buf);

      virtual int  GetStackEntry(ChartStack *ps, wxString *pfp);
      ChartBase *OpenChartFromStack(ChartStack *pStack, int StackEntry, ChartInitFlag iflag = FULL_INIT);
      int DisableChart(const char *pPathToDisable);
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
      bool SearchDirAndAddS57FromCatalog(wxString& dir_name, bool bshow_prog);


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


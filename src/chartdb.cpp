/******************************************************************************
 * $Id: chartdb.cpp,v 1.19 2009/07/29 00:52:03 bdbcat Exp $
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
 * $Log: chartdb.cpp,v $
 * Revision 1.19  2009/07/29 00:52:03  bdbcat
 * Correct stack index logic.
 *
 * Revision 1.18  2009/06/30 03:05:29  bdbcat
 * Fix compile bug.
 *
 * Revision 1.17  2009/06/30 03:02:03  bdbcat
 * Add configurable chart cache limit.
 *
 * Revision 1.16  2009/06/18 01:33:48  bdbcat
 * Allow u/l case dir search.
 *
 * Revision 1.15  2009/06/03 03:14:29  bdbcat
 * Correct chart discard logic for thumbnail window.
 *
 * Revision 1.14  2009/05/05 03:57:36  bdbcat
 * New logic for db update, incomplete....
 *
 * Revision 1.13  2009/03/26 22:28:55  bdbcat
 * Opencpn 1.3.0 Update
 *
 * Revision 1.12  2008/12/19 04:16:57  bdbcat
 * Improve database logic.
 *
 * Revision 1.11  2008/10/24 00:09:19  bdbcat
 * Validate GetEditionDate() return
 *
 * Revision 1.10  2008/08/09 23:58:40  bdbcat
 * Numerous revampings....
 *
 * Revision 1.9  2008/04/20 20:53:04  bdbcat
 * Cache optimization
 *
 * Revision 1.8  2008/03/30 21:54:29  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.7  2008/01/12 06:23:19  bdbcat
 * Update for Mac OSX/Unicode
 *
 * Revision 1.6  2007/06/10 02:25:09  bdbcat
 * Fix leaks
 *
 * Revision 1.5  2007/05/03 13:23:55  dsr
 * Major refactor for 1.2.0
 *
 * Revision 1.4  2006/10/08 14:15:00  dsr
 * no message
 *
 * Revision 1.3  2006/10/08 00:36:44  dsr
 * no message
 *
 * Revision 1.2  2006/09/21 01:37:36  dsr
 * Major refactor/cleanup
 *
 */


// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
      #include "wx/wx.h"
#endif //precompiled headers

#include <wx/stopwatch.h>

#include "chartdb.h"
#include "chartimg.h"
#include "chart1.h"
#include "thumbwin.h"

#include <stdio.h>
#include <math.h>

#include "wx/generic/progdlgg.h"

#ifdef USE_S57
#include "s57chart.h"
#include "s57.h"
#endif

#include "cm93.h"


extern ChartBase    *Current_Ch;
extern ThumbWin     *pthumbwin;
extern int          g_nCacheLimit;


bool G_FloatPtInPolygon(MyFlPoint *rgpts, int wnumpts, float x, float y) ;


CPL_CVSID("$Id: chartdb.cpp,v 1.19 2009/07/29 00:52:03 bdbcat Exp $");

// ============================================================================
// implementation
// ============================================================================

ChartDB::ChartDB(MyFrame *parent)
{
      pParent = parent;
      ifs = 0;
      pChartTable = 0;

      pChartCache = new wxArrayPtrVoid;

      bValid = false;                           // until loaded or created
}


ChartDB::~ChartDB()
{
      if(pChartTable)
      {
            for(int i=0 ; i<nEntry ; i++)
            {
                  if(pChartTable[i].pFullPath)
                        free(pChartTable[i].pFullPath);
                  if(pChartTable[i].pPlyTable)
                        free(pChartTable[i].pPlyTable);

                  if(pChartTable[i].nAuxPlyEntries)
                  {
                      for(int j=0 ; j<pChartTable[i].nAuxPlyEntries ; j++)
                          free ( (pChartTable[i].pAuxPlyTable)[j] );
                      free( pChartTable[i].pAuxPlyTable );
                      free( pChartTable[i].pAuxCntTable );
                  }
            }

            free(pChartTable);
      }

      if(ifs)
            delete ifs;

//    Empty the cache
      unsigned int nCache = pChartCache->GetCount();
      for(unsigned int i=0 ; i<nCache ; i++)
      {
            CacheEntry *pce = (CacheEntry *)(pChartCache->Item(i));
            ChartBase *Ch = (ChartBase *)pce->pChart;
            delete Ch;
            delete pce;
      }

      delete pChartCache;
}


// ----------------------------------------------------------------------------
// Load Chart Table Database from binary .DAT file
// ----------------------------------------------------------------------------
bool ChartDB::LoadBinary(wxString *filename)
{
      unsigned char buf[200];
      wxFileInputStream *ifs;

      wxFile test;
      if (!test.Exists(*filename))
             return false;

      ifs = new wxFileInputStream(*filename);         // open the file as a read-only stream

      if(!ifs->Ok())
      {
            delete ifs;
            return false;
      }


      ifs->Read(buf, sizeof(ChartTableHeader));
      ChartTableHeader *pcth = (ChartTableHeader *)buf;
      int n_entries = pcth->nTableEntries;


      char vb[5];
      sprintf(vb, "V%03d", DB_VERSION);
      if(strncmp((const char *)buf, vb, 4))
      {
            wxString msg = _T("   Warning: Chartdb LoadBinary() found incorrect database version");
            wxLogMessage(msg);

            return false;
      }

//    Read source directory names
      for(int iDir = 0 ; iDir < pcth->nDirEntries ; iDir++)
      {
            int ldir;
            ifs->Read(&ldir, sizeof(int));

            wxString dir;
            dir.Clear();
            for(int ic=0 ; ic<ldir ; ic++)
            {
                  char c;
                  ifs->Read(&c, 1);
                  dir.Append(c);
            }

      }

      pChartTable = (ChartTableEntry *)calloc(n_entries * sizeof(ChartTableEntry), 1);

      ChartTableEntry *pe = pChartTable;
      for(int iEntry = 0 ; iEntry < n_entries ; iEntry++)
      {
            char *s = (char *)buf;

            int ifp = 0;
            while((*s = (char)ifs->GetC()) != 0)
            {
                  s++;
                  ifp++;
            }
            ifp++;
            char *pfp = (char *)malloc(ifp);

            s = (char *)buf;
            char *t = pfp;
            for(int ic = 0 ; ic < ifp ; ic++)
                  *t++ = *s++;

            ifs->Read(pe, sizeof(ChartTableEntry));
            pe->pFullPath = pfp;

            int nplies = pe->nPlyEntries;

            float *pfe = (float *)malloc(nplies * sizeof(float) * 2);
            ifs->Read(pfe, nplies * sizeof(float) * 2);
            pe->pPlyTable = pfe;

            //  Read Aux Ply Table Entries
            if(pe->nAuxPlyEntries)
            {
                pe->pAuxCntTable = (int *)malloc(pe->nAuxPlyEntries * sizeof(int));
                ifs->Read(pe->pAuxCntTable, pe->nAuxPlyEntries * sizeof(int));

                float **pfp = (float **)malloc(pe->nAuxPlyEntries * sizeof(float *));

                for(int j=0 ; j<pe->nAuxPlyEntries ; j++)
                {
                    float *pfl = (float *)malloc(pe->pAuxCntTable[j] * 2 * sizeof(float));
                    pfp[j] = pfl;
                    ifs->Read(pfl, pe->pAuxCntTable[j] * 2 * sizeof(float));
                }
                pe->pAuxPlyTable = pfp;
            }



            pe++;
      }

      nEntry = n_entries;


      delete ifs;

      bValid = true;
      return true;
}


// ----------------------------------------------------------------------------
// Save Chart Table Database to binary .DAT file
// ----------------------------------------------------------------------------
bool ChartDB::SaveBinary(wxString *filename, wxArrayString *pChartDirArray)
{
      wxFileOutputStream *ofs;

//    Verify that the target directory exists, make it if not
      wxFileName file(*filename);
//    Note the explicit cast on GetPath argument, required by MSVC???
      wxFileName dir(file.GetPath((int)(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME), wxPATH_NATIVE));

      if( ! dir.DirExists() )
      {
            if(! dir.Mkdir())
                  return false;
      }



      ofs = new wxFileOutputStream(*filename);        // open the file as write only

      if(!ofs->Ok())
            return false;

      ChartTableHeader cth;
      cth.nTableEntries = nEntry;
      cth.nDirEntries = pChartDirArray->GetCount();

      char *ctp = (char *)(&cth.dbVersion[0]);
      char vb[5];
      sprintf(vb, "V%03d", DB_VERSION);
      for(int i = 0 ; i<4 ; i++)
        *ctp++ = vb[i];


      ofs->Write(&cth, sizeof(ChartTableHeader));

//    Write source directory names
      for(int iDir = 0 ; iDir < cth.nDirEntries ; iDir++)
      {
            wxString dir = pChartDirArray->Item(iDir);
            int ldir = dir.Len();
            ofs->Write(&ldir, sizeof(int));                 // length
            ofs->Write(dir.mb_str(), ldir);                  // name
      }



      ChartTableEntry *pe = pChartTable;
      for(int iEntry = 0 ; iEntry < nEntry ; iEntry++)
      {
            char *s = pe->pFullPath;

            while(*s)
            {
                  ofs->PutC(*s);
                  s++;
            }
            ofs->PutC(0);

            ofs->Write(pe, sizeof(ChartTableEntry));

            int nplies = pe->nPlyEntries;
            float *pfe = pe->pPlyTable;
            ofs->Write(pfe, nplies * sizeof(float) * 2);

            //  Write Aux Ply Table Entries
            if(pe->nAuxPlyEntries)
            {
                ofs->Write(pe->pAuxCntTable, pe->nAuxPlyEntries * sizeof(int));
                for(int j=0 ; j<pe->nAuxPlyEntries ; j++)
                {
                    float *pfl = pe->pAuxPlyTable[j];
                    ofs->Write(pfl, pe->pAuxCntTable[j] * 2 * sizeof(float));
                }
            }


            pe++;
      }

      delete ofs;

      return true;
}

// ----------------------------------------------------------------------------
// Create Chart Table Database by directory search
//    resulting in valid pChartTable in (this)
// ----------------------------------------------------------------------------
bool ChartDB::Create(wxArrayString *dir_list, bool bshow_prog)
{
      pChartTable = (ChartTableEntry *)malloc(sizeof(ChartTableEntry));
      nEntry = 0;

      Update(dir_list, bshow_prog);

      bValid = true;
      return true;
}

// ----------------------------------------------------------------------------
// Update existing ChartTable Database by directory search
//    resulting in valid pChartTable in (this)
// ----------------------------------------------------------------------------
bool ChartDB::Update(wxArrayString *dir_list, bool bshow_prog)
{
    int i;

    if(NULL == pChartTable)
    {
        pChartTable = (ChartTableEntry *)malloc(sizeof(ChartTableEntry));
        nEntry = 0;
    }

    //  Mark all charts provisionally invalid
    for(i=0 ; i<nEntry ; i++)
    {
        pChartTable[i].bValid = false;
    }


    //  Get the new charts

    for(unsigned int j=0 ; j<dir_list->GetCount() ; j++)
    {
        wxString dir_name = dir_list->Item(j);

        wxString dir_magic;
        TraverseDirAndAddCharts(dir_name, bshow_prog, true, dir_magic);

#if 0
        //  Update the dir_list entry, even if the magic values are the same
        wxString dir_path = dir_name.BeforeFirst('^');

        dir_path.Append('^');
        dir_path.Append(dir_magic);

        dir_list->RemoveAt(j);
        dir_list->Insert(dir_path, j);
#endif
    }           //for

    //  It is likely that there are duplicate charts in the list now.
    //  These occur as identical large area charts are included in multiple
    //  Maptech Regions.  For example, the GreatLakes overview chart NOAA 14500
    //  is found in Maptech Regions 81 (Lake Superior), 82 (Lake Huron), 83
    //  (Lake Erie), etc....

    //  So, look for identical charts and mark older charts as invalid
    int iremove, ikeep;;
    for(int ic=0 ; ic<nEntry - 1 ; ic++)
    {
        if(pChartTable[ic].bValid)
        {
            for(int jc=ic + 1 ; jc<nEntry ; jc++)
            {
                if(pChartTable[jc].bValid)
                {
                    if(!strcmp(pChartTable[ic].ChartID, pChartTable[jc].ChartID))
                    {
                          wxDateTime first_chart(pChartTable[ic].edition_date);
                          wxDateTime second_chart(pChartTable[jc].edition_date);
                          if(first_chart.IsEarlierThan(second_chart))
                          {
                                iremove = ic;
                                ikeep = jc;
                          }
                          else
                          {
                                iremove = jc;
                                ikeep = ic;
                          }

                          pChartTable[iremove].bValid = false;

//          printf("Removing duplicate %s, %s and keeping %s \n",pChartTable[iremove].ChartID, pChartTable[iremove].pFullPath, pChartTable[ikeep].pFullPath);
                    }
                }
            }
        }
     }



    //  Count the valid charts
    int iValid = 0;
    for(i=0 ; i<nEntry ; i++)
    {
        if(pChartTable[i].bValid)
            iValid++;
    }

    // Allocate a new chart table
    ChartTableEntry *pTempChartTable = (ChartTableEntry *)malloc((iValid) * sizeof(ChartTableEntry));
    ChartTableEntry *pEntry = pTempChartTable;

    // compress the existing table into the new table, and while we are at it
    // free the imbedded pointers in invalid entries

    int nNewEntry = 0;
    for(i=0 ; i<nEntry ; i++)
    {
        if(pChartTable[i].bValid)
        {
            memcpy(pEntry, (const void *)(&pChartTable[i]), sizeof(ChartTableEntry));

            pEntry++;
            nNewEntry++;
        }

        if(!pChartTable[i].bValid)
        {
            free (pChartTable[i].pPlyTable);
            free (pChartTable[i].pFullPath);

            //  Free Aux Ply Table Entries
            if(pChartTable[i].nAuxPlyEntries)
            {
                float **pfp = pChartTable[i].pAuxPlyTable;

                for(int j=0 ; j<pChartTable[i].nAuxPlyEntries ; j++)
                {
                    free (pfp[j]);
                }

                free(pChartTable[i].pAuxPlyTable);
                free(pChartTable[i].pAuxCntTable);
             }
        }
    }


    free(pChartTable);
    pChartTable = pTempChartTable;
    nEntry = nNewEntry;

    bValid = true;
    return true;
}






// ----------------------------------------------------------------------------
//  Traverse the given directory looking for charts
//  If bupdate is true, also search the existing database for a name match.
//  If target chart is already in database, mark the entry valid and skip additional processing
// ----------------------------------------------------------------------------

int ChartDB::TraverseDirAndAddCharts(wxString dir_name, bool bshow_prog, bool bupdate, wxString &dir_magic)
{
      //    Extract the true dir name and magic number from the compound string
      wxString dir_path = dir_name.BeforeFirst('^');
      wxString old_magic = dir_name.AfterFirst('^');
      wxString new_magic = old_magic;
      dir_magic = old_magic;              // provisionally the same

      //    Quick scan the directory to see if it has changed
      //    If not, there is no need to scan again.....

/*
this logic is busted.... We need a true update method, and some good struct to hold dirs.....
            current problem is that old database is deleted and recreated from scratch always
      if(!DetectDirChange(dir_path, old_magic, new_magic))
      {
            wxString msg(_T("   No change detected on directory "));
            msg.Append(dir_path);
            wxLogMessage(msg);

            return 0;
      }
*/
      //    There presumably was a change in the directory contents.  Return the new magic number
      dir_magic = new_magic;

    int nAdd = 0;

    wxLogMessage(_T("  searching for .geo"));
    nAdd += SearchDirAndAddCharts(dir_path, wxString(_T("*.geo")), bshow_prog, bupdate);

    wxLogMessage(_T("  searching for .KAP"));
    nAdd += SearchDirAndAddCharts(dir_path, wxString(_T("*.KAP")), bshow_prog, bupdate, true);

#ifdef USE_S57
    wxLogMessage(_T("  searching for .000"));
    nAdd += SearchDirAndAddCharts(dir_path, wxString(_T("*.000")), bshow_prog, bupdate);

    wxLogMessage(_T("  searching for .S57"));
    nAdd += SearchDirAndAddCharts(dir_path, wxString(_T("*.S57")), bshow_prog, bupdate);

#endif

#ifdef USE_CM93
    wxLogMessage(_T("  searching for .CM93"));
    nAdd += SearchDirAndAddCharts(dir_path, wxString(_T("00300000.A")), bshow_prog, bupdate);     // for cm93
#endif

    return nAdd;


// TODO Add code to prevent duplicate charts coming into the database
//          Duplicate meaning "the SAME FILE", considering VFAT's file naming conventions
//          For now, though, just assume file extensions are upper case "KAP"

//          wxString filespec_kap("*.kap");
//          SearchDirAndAddBSB(dir_name, filespec_kap);

//          SearchDirAndAddBSB(dir_name,  (const wxString &)wxString("*.KAP"), bshow_prog);

}

bool ChartDB::DetectDirChange(wxString dir_path, wxString magic, wxString &new_magic)
{
      //    parse the magic number
      long long unsigned int nmagic;
      wxULongLong nacc = 0;

      magic.ToULongLong(&nmagic, 10);

      //    Get an arraystring of all files
      wxArrayString FileList;
      wxDir dir(dir_path);
      int n_files = dir.GetAllFiles(dir_path, &FileList);

      //Traverse the list of files, getting their interesting stuff to add to accumulator
      for(int ifile=0 ; ifile < n_files ; ifile++)
      {
            wxFileName file(FileList.Item(ifile));

            //    File Size;
            wxULongLong size = file.GetSize();
            if(wxInvalidSize != size)
                  nacc = nacc + size;

            //    Mod time, in ticks
            wxDateTime t = file.GetModificationTime();
            nacc += t.GetTicks();

      }

      //    Return the calculated magic number
      new_magic = nacc.ToString();

      //    And do the test
      if(new_magic != magic)
            return true;
      else
            return false;
}

#include <wx/encconv.h>

// ----------------------------------------------------------------------------
// Populate Chart Table by directory search for specified file type
// If bupdate flag is true, search the Chart Table for matching chart.
//  if target chart is already in table, mark it valid and skip chart processing
// ----------------------------------------------------------------------------

int ChartDB::SearchDirAndAddCharts(wxString& dir_name_base, const wxString& filespec,
                                                      bool bshow_prog, bool bupdate,
                                                      bool bCheckBothCases)
{
      wxString dir_name = dir_name_base;
//      wxString dir_name(dir_name_base.fn_str(), wxConvFileName);


      wxString filename;

      wxProgressDialog *pprog = NULL;

//    Count the files
      wxArrayString FileList;
      int gaf_flags = wxDIR_DEFAULT;                  // as default, recurse into subdirs

      //    An optimization, peephole-wise, especially for __WXMSW__....
      //    If the dir seems to be cm93 root, optimize the directory searching.
      //    If the filespec is not looking for the base cm93 cell,
      //    then clip the search by making the search flags parameter empty....
      //    Otherwise, for instance, .KAP searches will have to traverse the entire cm93 tree.
      //    Very slow on MSW, and clearly unproductive.
      //    If the target filespec is the CM93 reference file, search only its directory

      wxString cm93_test = dir_name;
      cm93_test += _T("/00300000/A/00300000.A");
      if(wxFile::Exists(cm93_test))                   // The target dir probably is cm93
      {
            gaf_flags =  wxDIR_FILES;                 // dont recurse

            if(filespec.IsSameAs(_T("00300000.A")))
                dir_name += _T("/00300000/A");              // Manage the directory search
      }


      wxDir dir(dir_name);

      if(bCheckBothCases)
      {
            wxString fs_upper = filespec.Upper();
            dir.GetAllFiles(dir_name, &FileList, fs_upper, gaf_flags);

            wxString fs_lower = filespec.Lower();
            dir.GetAllFiles(dir_name, &FileList, fs_lower, gaf_flags);
      }
      else
            dir.GetAllFiles(dir_name, &FileList, filespec, gaf_flags);


      int nFile = FileList.GetCount();

      if(!nFile)
          return false;


      InitReturn rc;

      ChartTableEntry *pTempChartTable = (ChartTableEntry *)calloc((nFile ) * sizeof(ChartTableEntry), 1);
      ChartTableEntry *pEntry = pTempChartTable;
      int nDirEntry = 0;

      //    Check to see if there are any charts in the DB which refer to this directory
      //    If none at all, there is no need to scan the DB for each potential addition
      //    and bneed_full_search is false.
      bool bneed_full_search = SearchForChartDir(dir_name);

      int isearch = 0;              // create a smarter search index
                                          // indexing the DB starting from the last found item

      for(int ifile=0 ; ifile < nFile ; ifile++)
      {
            wxFileName file(FileList.Item(ifile));
            wxString full_name = file.GetFullPath(); //dir_name;

            if(bshow_prog)
            {
                  if(NULL == pprog)
                        pprog = new wxProgressDialog (  _T("OpenCPN Add Chart"), full_name, nFile, NULL,
                              wxPD_AUTO_HIDE | wxPD_SMOOTH | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);

                  pprog->Update(ifile, full_name);
            }


            //    As a speed optimization, use strcmp instead of wxString::IsSameAs()
            char test_str[512];
            strncpy(test_str, full_name.mb_str(), 511);

            //    Create a string equal to what the chart name (ID) would be if it was created
            char test_str_ID[512];
            wxFileName base(full_name);
            strncpy(test_str_ID, base.GetFullName().mb_str(), 511);


            bool bDuplicateName = false;
            bool bDuplicatePath = false;
            int iDuplicate;
            if(bupdate)
            {
                if(bneed_full_search)
                {
                      for(int i=0 ; i<nEntry ; i++)
                      {
                            if(!strcmp(test_str, pChartTable[isearch].pFullPath))
                            {
                              bDuplicatePath = true;
                              pChartTable[isearch].bValid = true;
                              break;
                            }

                    //  Look at the chart name (ID) itself for a further check
                    //  This catches the case in which the "same" chart is in different locations,
                    //  and one may be newer than the other, which we will later check for.
                            if(!strcmp(pChartTable[isearch].ChartID, test_str_ID))
                            {
                               bDuplicateName = true;
                               iDuplicate = isearch;
                               break;
                            }

                            isearch++;
                            if(nEntry == isearch)
                                  isearch = 0;
                     }
                }
            }


            pEntry->bValid = false;
            bool bAddFinal = true;

            //      If updating the database, and this is a duplicate chart, need to check the Edition date of the candidate chart
            if(bupdate && bDuplicateName)
            {
                  rc = CreateChartTableEntry(full_name, pEntry);
                  if(rc == INIT_OK)
                  {
                        wxDateTime candidate_ed(pEntry->edition_date);
                        wxDateTime existing_chart_ed(pChartTable[iDuplicate].edition_date);
                        ChartTableEntry t = pChartTable[iDuplicate];
                        if(candidate_ed.IsEarlierThan(existing_chart_ed))
                        {
                              pChartTable[iDuplicate].bValid = true;
                              bAddFinal = false;
                        }
                  }
                  else
                  {
                        bAddFinal = false;

                        if(rc != INIT_FAIL_NOERROR)
                        {
                              wxString msg = _T("   CreateChartTableEntry() failed for file: ");
                              msg.Append(full_name);
                              wxLogMessage(msg);
                        }
                  }
            }
            else if(bupdate && bDuplicatePath)                // exactly the same chart
                  bAddFinal = false;


            if(bAddFinal)
            {
                  if(!pEntry->bValid)
                  {
                        rc = CreateChartTableEntry(full_name, pEntry);
                        if(rc != INIT_OK)
                        {
                              bAddFinal = false;
                              if(rc != INIT_FAIL_NOERROR)
                              {
                                    wxString msg = _T("   CreateChartTableEntry() failed for file: ");
                                    msg.Append(full_name);
                                    wxLogMessage(msg);
                              }
                        }
                  }


                  if(bAddFinal)
                  {
                        nDirEntry++;
                        pEntry++;
                  }
            }
      }

      ChartTableEntry *pt = (ChartTableEntry *)malloc( (nEntry + nDirEntry)*sizeof(ChartTableEntry));
      memcpy(pt, pChartTable, nEntry * sizeof(ChartTableEntry));
      memcpy((char *)pt + (nEntry * sizeof(ChartTableEntry)), pTempChartTable, nDirEntry * sizeof(ChartTableEntry));

      free(pChartTable);
      free(pTempChartTable);

      pChartTable = pt;
      nEntry += nDirEntry;

      if(pprog)                     // looks nicer
            pprog->Hide();
      delete pprog;
      return nDirEntry;
}





// ----------------------------------------------------------------------------
// Create Chart Table entry by reading chart header info, etc.
// ----------------------------------------------------------------------------
InitReturn ChartDB::CreateChartTableEntry(wxString full_name, ChartTableEntry *pEntry)
{
      wxFileName fn(full_name);

//    Quick sanity check for file existence
      if(!fn.FileExists())
            return INIT_FAIL_REMOVE;

      wxString msg(_T("Create ChartTable Entry for "));
      msg.Append(full_name);
      wxLogMessage(msg);

      wxString charttype = fn.GetExt();
      ChartBase *pch = NULL;

      if(charttype.Upper() == _T("KAP"))
      {
            pch = new ChartKAP;
            pEntry->ChartType = CHART_TYPE_KAP;
      }
      else if(charttype.Upper() == _T("GEO"))
      {
            pch = new ChartGEO;
            pEntry->ChartType = CHART_TYPE_GEO;
      }

      else if(charttype.Upper() == _T("000"))
      {
            pch = new s57chart;
            pEntry->ChartType = CHART_TYPE_S57;
      }

      else if(charttype.Upper() == _T("S57"))
      {
            pch = new s57chart;
            pEntry->ChartType = CHART_TYPE_S57;
      }


#ifdef USE_CM93
/*
      else if(charttype.Len() == 1)                   // speculative, assuming the file will be found to be a cm93 cell...
      {
            pch = new cm93chart;
            pEntry->ChartType = CHART_TYPE_CM93;
      }
*/
      else if(fn.GetFullName().IsSameAs(_T("00300000.A")))
      {
            pch = new cm93compchart;
            pEntry->ChartType = CHART_TYPE_CM93COMP;

      }
#endif

      if(NULL == pch)
            return INIT_FAIL_REMOVE;

      InitReturn rc = pch->Init(full_name, HEADER_ONLY, GLOBAL_COLOR_SCHEME_DAY);
      if(rc != INIT_OK)
      {
            delete pch;
            return rc;
      }

      char *pt = (char *)malloc(full_name.Length() + 1);
      strcpy(pt, full_name.mb_str( wxConvUTF8));
      pEntry->pFullPath = pt;

      strncpy(pEntry->ChartID, fn.GetFullName().mb_str( wxConvUTF8), sizeof(pEntry->ChartID));
      pEntry->ChartID[sizeof(pEntry->ChartID)-1] = 0;

      pEntry->Scale = pch->GetNativeScale();

      if(pch->GetEditionDate().IsValid())
            pEntry->edition_date = pch->GetEditionDate().GetTicks();
      else
            pEntry->edition_date = 0;

      Extent ext;
      pch->GetChartExtent(&ext);

      pEntry->LatMax = ext.NLAT;
      pEntry->LatMin = ext.SLAT;
      pEntry->LonMin = ext.WLON;
      pEntry->LonMax = ext.ELON;

//          Fill in the PLY information
//          If  COVR table has only one entry, us it for the primary Ply Table
      if(pch->m_nCOVREntries == 1)
      {

            pEntry->nPlyEntries = pch->GetCOVRTablenPoints(0);

            float *pf = (float *)malloc(2 * pEntry->nPlyEntries * sizeof(float));

            pEntry->pPlyTable = pf;

            float *pfe = pf;
            Plypoint *ppp = (Plypoint *)pch->GetCOVRTableHead(0);

            for(int i=0 ; i<pEntry->nPlyEntries ; i++)
            {
                  *pfe++ = ppp->ltp;
                  *pfe++ = ppp->lnp;

                  ppp++;
            }
      }
//    Else create a rectangular primary Ply Table from the chart extents
//    and create AuxPly table from the COVR tables
      else
      {
            //    Create new artificial Ply table from chart extents
            pEntry->nPlyEntries = 4;
            float *pf1 = (float *)malloc(2 * 4 * sizeof(float));
//            free (pEntry->pPlyTable);
            pEntry->pPlyTable = pf1;

            float *pfe = pf1;
            Extent fext;
            pch->GetChartExtent(&fext);

            *pfe++ = fext.NLAT; //LatMax;
            *pfe++ = fext.WLON; //LonMin;

            *pfe++ = fext.NLAT; //LatMax;
            *pfe++ = fext.ELON; //LonMax;

            *pfe++ = fext.SLAT; //LatMin;
            *pfe++ = fext.ELON; //LonMax;

            *pfe++ = fext.SLAT; //LatMin;
            *pfe++ = fext.WLON; //LonMin;


//    Fill in the structure for pAuxPlyTable

            unsigned int nAuxPlyEntries = pch->m_nCOVREntries;
            float **pfp = (float **)malloc(nAuxPlyEntries * sizeof(float *));
            float **pft0 = pfp;
            int *pip = (int *)malloc(nAuxPlyEntries * sizeof(int));

            for(unsigned int j=0 ; j<nAuxPlyEntries ; j++)
            {
                  float *pf_entry = (float *)malloc(pch->m_pCOVRContourTable[j] * 2 * sizeof(float));
                  memcpy(pf_entry, pch->m_pCOVRTable[j], pch->m_pCOVRContourTable[j] * 2 * sizeof(float));
                  pft0[j] = pf_entry;
                  pip[j] = pch->m_pCOVRContourTable[j];
            }

            pEntry->pAuxPlyTable = pfp;
            pEntry->pAuxCntTable = pip;
            pEntry->nAuxPlyEntries = nAuxPlyEntries;
      }



      delete pch;

      pEntry->bValid = true;
      return INIT_OK;
}


//-------------------------------------------------------------------------------------------------------
//
//      Database access methods
//
//-------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------
//    Search database for any chart entries pointing to specified directory
//     (with or without trailing path separator)
//-------------------------------------------------------------------------------------------------------

bool ChartDB::SearchForChartDir(wxString &dir)
{
      wxString dir_copy(dir);
      if((dir_copy.Last() == wxFileName::GetPathSeparator()) || (dir_copy.Last() == '/'))
            dir_copy.RemoveLast();

      dir_copy.Append(_T("*"));           // make match string
      for(int i=0 ; i<nEntry ; i++)
      {
            wxString entry_name(pChartTable[i].pFullPath, wxConvUTF8);
            if(entry_name.Matches(dir_copy))
               return true;

      }
      return false;
}

//-------------------------------------------------------------------
//    Get Full Path from db
//-------------------------------------------------------------------
bool ChartDB::GetDBFullPath(int dbIndex, char *buf)
{
      strcpy(buf, pChartTable[dbIndex].pFullPath);
      return true;
}

//-------------------------------------------------------------------
//    Get Lat/Lon Bounding Box from db
//-------------------------------------------------------------------
bool ChartDB::GetDBBoundingBox(int dbIndex, wxBoundingBox *box)
{
    box->SetMax(pChartTable[dbIndex].LonMax, pChartTable[dbIndex].LatMax);
    box->SetMin(pChartTable[dbIndex].LonMin, pChartTable[dbIndex].LatMin);

    return true;
}


//-------------------------------------------------------------------
//    Build Chart stack
//-------------------------------------------------------------------
int ChartDB::BuildChartStack(ChartStack * cstk, float lat, float lon)
{
      int i=0;
      int j=0;

      if(!bValid)
            return 0;                           // Database is not properly initialized

      for(i=0 ; i<nEntry ; i++)
      {

//    First check on rough Bounding box

            if((lat < pChartTable[i].LatMax) &&
               (lat > pChartTable[i].LatMin) &&
               (lon > pChartTable[i].LonMin) &&
               (lon < pChartTable[i].LonMax) &&
               (j < MAXSTACK))

            {
//    Double check on Ply points polygon

                  bool bInside = G_FloatPtInPolygon((MyFlPoint *)pChartTable[i].pPlyTable,
                                                             pChartTable[i].nPlyEntries,
                                                             lon, lat);

                  if(bInside )
                  {
                      if(pChartTable[i].nAuxPlyEntries)
                      {
                          for(int k=0 ; k<pChartTable[i].nAuxPlyEntries ; k++)
                          {
                              bool bAuxInside = G_FloatPtInPolygon((MyFlPoint *)pChartTable[i].pAuxPlyTable[k],
                                                        pChartTable[i].pAuxCntTable[k],lon, lat);
                              if(bAuxInside)
                              {
                                  cstk->DBIndex[j] = i;
                                  j++;
                                  break;
                              }
                          }

                      }
                      else
                      {
                            cstk->DBIndex[j] = i;
                            j++;
                      }
                  }

            }
      }

      cstk->nEntry = j;

//    Sort the stack on scale
      int swap = 1;
      int n,m,ti;
      while(swap == 1)
      {
            swap = 0;
            for(i=0 ; i<j-1 ; i++)
            {
                  m = cstk->DBIndex[i];
                  n = cstk->DBIndex[i+1];

                  if(pChartTable[n].Scale < pChartTable[m].Scale)
                  {
                        ti = cstk->DBIndex[i];
                        cstk->DBIndex[i] = cstk->DBIndex[i+1];
                        cstk->DBIndex[i+1] = ti;
                        swap = 1;
                  }
            }
      }


      return j;
}

//-------------------------------------------------------------------
//    Compare Chart Stacks
//-------------------------------------------------------------------
bool ChartDB::EqualStacks(ChartStack *pa, ChartStack *pb)
{
      if((pa == 0) || (pb == 0))
            return false;
      if(pa->nEntry != pb->nEntry)
            return false;

      for(int i=0 ; i<pa->nEntry ; i++)
      {
            if(pa->DBIndex[i] != pb->DBIndex[i])
                  return false;
      }

      return true;
}

//-------------------------------------------------------------------
//    Copy Chart Stacks
//-------------------------------------------------------------------
bool ChartDB::CopyStack(ChartStack *pa, ChartStack *pb)
{
      if((pa == 0) || (pb == 0))
            return false;
      pa->nEntry = pb->nEntry;

      for(int i=0 ; i<pa->nEntry ; i++)
            pa->DBIndex[i] = pb->DBIndex[i];

      pa->CurrentStackEntry = pb->CurrentStackEntry;

      return true;
}

//-------------------------------------------------------------------
//    Get Full Path
//-------------------------------------------------------------------
wxString ChartDB::GetFullPath(ChartStack *ps, int stackindex)
{
      int dbIndex = ps->DBIndex[stackindex];
      return wxString(pChartTable[dbIndex].pFullPath,  wxConvUTF8);
}

//-------------------------------------------------------------------
//    Get PlyPoint from stack
//-------------------------------------------------------------------
int ChartDB::GetCSPlyPoint(ChartStack *ps, int stackindex, int plyindex, float *lat, float *lon)
{
      int dbIndex = ps->DBIndex[stackindex];
      if(pChartTable[dbIndex].nPlyEntries)
      {
            float *fp = pChartTable[dbIndex].pPlyTable;
            fp += plyindex*2;
            *lat = *fp;
            fp++;
            *lon = *fp;
      }

      return pChartTable[dbIndex].nPlyEntries;
}

//-------------------------------------------------------------------
//    Get PlyPoint from Database
//-------------------------------------------------------------------
int ChartDB::GetDBPlyPoint(int dbIndex, int plyindex, float *lat, float *lon)
{
      if(pChartTable[dbIndex].nPlyEntries)
      {
            float *fp = pChartTable[dbIndex].pPlyTable;
            fp += plyindex*2;
            *lat = *fp;
            fp++;
            *lon = *fp;
      }

      return pChartTable[dbIndex].nPlyEntries;
}

//-------------------------------------------------------------------
//    Get AuxPlyPoint from Database
//-------------------------------------------------------------------
int ChartDB::GetDBAuxPlyPoint(int dbIndex, int plyindex, int ply, float *lat, float *lon)
{
      if(pChartTable[dbIndex].nAuxPlyEntries)
      {
            float *fp = pChartTable[dbIndex].pAuxPlyTable[ply];

            fp += plyindex*2;
            *lat = *fp;
            fp++;
            *lon = *fp;
      }

      return pChartTable[dbIndex].pAuxCntTable[ply];
}



//-------------------------------------------------------------------
//    Get Chart ID
//-------------------------------------------------------------------
bool ChartDB::GetChartID(ChartStack *ps, int stackindex, char *buf, int nbuf)
{
      int dbIndex = ps->DBIndex[stackindex];
      strncpy(buf, pChartTable[dbIndex].ChartID, nbuf);
      buf[nbuf-1] = 0;

      return true;
}
//-------------------------------------------------------------------
//    Get Chart Scale
//-------------------------------------------------------------------
int ChartDB::GetStackChartScale(ChartStack *ps, int stackindex, char *buf, int nbuf)
{
      int dbIndex = ps->DBIndex[stackindex];
      int sc = pChartTable[dbIndex].Scale;
      sprintf(buf, "%d", sc);

      return sc;
}
//-------------------------------------------------------------------
//    Find ChartStack entry index corresponding to Full Path name, if present
//-------------------------------------------------------------------
int ChartDB::GetStackEntry(ChartStack *ps, wxString *pfp)
{
      for(int i=0 ; i<ps->nEntry ; i++)
      {
            int dbIndex = ps->DBIndex[i];
            if(pfp->IsSameAs( wxString(pChartTable[dbIndex].pFullPath,  wxConvUTF8)) )
                  return i;
      }

      return -1;
}

//-------------------------------------------------------------------
//    Get CSChart Type
//-------------------------------------------------------------------
int ChartDB::GetCSChartType(ChartStack *ps, int stackindex)
{
      if((bValid) && (stackindex < nEntry))
      {
            int dbIndex = ps->DBIndex[stackindex];
            return pChartTable[dbIndex].ChartType;
      }
      else
            return 0;
}


//-------------------------------------------------------------------
//    Get DBChart Type
//-------------------------------------------------------------------
int ChartDB::GetDBChartType(int dbIndex)
{
      if(bValid)
            return pChartTable[dbIndex].ChartType;
      else
            return 0;
}

//-------------------------------------------------------------------
//    Open Chart
//-------------------------------------------------------------------

ChartBase *ChartDB::OpenChartFromStack(ChartStack *pStack, int StackEntry, ChartInitFlag init_flag)
{

      ChartBase *Ch;
      CacheEntry *pce;

      wxString ChartFullPath = GetFullPath(pStack, StackEntry);

      wxDateTime now = wxDateTime::Now();                   // get time for LRU use

      bool bInCache = false;

//    Search the cache

      unsigned int nCache = pChartCache->GetCount();
      for(unsigned int i=0 ; i<nCache ; i++)
      {
            pce = (CacheEntry *)(pChartCache->Item(i));
            if(pce->FullPath == ChartFullPath)
            {
                  Ch = (ChartBase *)pce->pChart;
                  bInCache = true;
                  break;
            }
      }

      if(bInCache)
      {
          if(FULL_INIT == init_flag)                            // asking for full init?
          {
              if(Ch->IsReadyToRender())
              {
                    pce->RecentTime = now.GetTicks();           // chart is OK
                    return Ch;
              }
              else
              {
                    delete Ch;                                  // chart is not useable
                    pChartCache->Remove(pce);                   // so remove it
                    delete pce;
                    bInCache = false;
              }
          }
          else                                                  // assume if in cache, the chart can do thumbnails
          {
               pce->RecentTime = now.GetTicks();
               return Ch;
          }

      }

      if(!bInCache)                    // not in cache
      {

//#ifndef __WXMSW__       // for MSW, we assume the cache upper size limit is unbounded,
                        // and so NEVER remove a chart from the cache

#ifdef CACHE_MEM_LIMIT
#define MEM_FREE_THRESHOLD    CACHE_MEM_LIMIT             // in KBytes

          //    Check memory status to see if enough room to open another chart
            int omem_total, omem_used;
            pParent->GetMemoryStatus(omem_total, omem_used);
            int omem_free = omem_total - omem_used;
            if(omem_free < MEM_FREE_THRESHOLD)
            {
                  // Search the cache for oldest entry that is not Current_Ch
                  unsigned int nCache = pChartCache->GetCount();
                  if(nCache > 2)
                  {
                      wxLogMessage(_T("Searching chart cache for oldest entry"));
                        int LRUTime = now.GetTicks();
                        int iOldest = 0;
                        for(unsigned int i=0 ; i<nCache ; i++)
                        {
                              pce = (CacheEntry *)(pChartCache->Item(i));
                              if((ChartBase *)(pce->pChart) != Current_Ch)
                              {
                                    if(pce->RecentTime < LRUTime)
                                    {
                                          LRUTime = pce->RecentTime;
                                          iOldest = i;
                                    }
                              }
                        }
                      int dt = now.GetTicks() - LRUTime;
                      wxLogMessage(_T("Oldest cache index is %d, delta t is %d"), iOldest, dt);

                        pce = (CacheEntry *)(pChartCache->Item(iOldest));
                        ChartBase *pDeleteCandidate =  (ChartBase *)(pce->pChart);

                        if(Current_Ch == pDeleteCandidate)
                        {
                            wxLogMessage(_T("...However, it is Current_Ch"));
                        }
                        else
                        {
                            wxLogMessage(_T("Deleting/Removing oldest chart from cache"));
//                            wxLogMessage(_T("oMem_Free before chart removal is %d"), omem_free);

                              //  If this chart should happen to be in the thumbnail window....
                              if(pthumbwin)
                              {
                                    if(pthumbwin->pThumbChart == pDeleteCandidate)
                                          pthumbwin->pThumbChart = NULL;
                              }

                              //    Delete the chart
                              delete pDeleteCandidate;

                              //remove the cache entry
                              pChartCache->Remove(pce);

                              pParent->GetMemoryStatus(omem_total, omem_used);
//                            int omem_free = omem_total - omem_used;
//                            wxLogMessage(_T("oMem_Free after chart removal is %d"), omem_free);

                        }
                  }
            }

#endif      //CACHE_MEM_LIMIT

#ifdef CACHE_N_LIMIT_DEFAULT
//#define N_CACHE CACHE_N_LIMIT

//      Limit cache to n charts, tossing out the oldest when space is needed
            unsigned int nCache = pChartCache->GetCount();
            if(nCache >= (unsigned int)g_nCacheLimit)
            {
///                  wxLogMessage("Searching chart cache for oldest entry");
                  int LRUTime = now.GetTicks();
                  int iOldest = 0;
                  for(unsigned int i=0 ; i<nCache ; i++)
                  {
                        pce = (CacheEntry *)(pChartCache->Item(i));
                        if((ChartBase *)(pce->pChart) != Current_Ch)
                        {
                              if(pce->RecentTime < LRUTime)
                              {
                                    LRUTime = pce->RecentTime;
                                    iOldest = i;
                              }
                        }
                  }

                  pce = (CacheEntry *)(pChartCache->Item(iOldest));
                  ChartBase *pDeleteCandidate =  (ChartBase *)(pce->pChart);

                  if(Current_Ch != pDeleteCandidate)
                  {
 ///                     wxLogMessage("Deleting/Removing oldest chart from cache");
///                      wxLogMessage("oMem_Free before chart removal is %d", omem_free);

                    //  If this chart should happen to be in the thumbnail window....
                        if(pthumbwin)
                        {
                              if(pthumbwin->pThumbChart == pDeleteCandidate)
                                    pthumbwin->pThumbChart = NULL;
                        }

                   //    Delete the chart
                        delete pDeleteCandidate;

                   //remove the cache entry
                        pChartCache->Remove(pce);

                        if(pthumbwin)
                        {
                              if(pthumbwin->pThumbChart == pDeleteCandidate)
                                    pthumbwin->pThumbChart = NULL;
                        }

                  }
            }
#endif      //CACHE_N_LIMIT



//#endif      // ndef __WXMSW__

            if(GetCSChartType(pStack, StackEntry) == CHART_TYPE_KAP)
                  Ch = new ChartKAP();

            else if(GetCSChartType(pStack, StackEntry) == CHART_TYPE_GEO)
                  Ch = new ChartGEO();

#ifdef USE_S57
            else if(GetCSChartType(pStack, StackEntry) == CHART_TYPE_S57)
            {
                  Ch = new s57chart();
                  int dbIndex = pStack->DBIndex[StackEntry];

                  s57chart *Chs57 = dynamic_cast<s57chart*>(Ch);

                  Chs57->SetNativeScale(pChartTable[dbIndex].Scale);

                  //    Explicitely set the chart extents from the database to
                  //    support the case wherein the SENC file has not yet been built
                  Extent ext;
                  ext.NLAT = pChartTable[dbIndex].LatMax;
                  ext.SLAT = pChartTable[dbIndex].LatMin;
                  ext.WLON = pChartTable[dbIndex].LonMin;
                  ext.ELON = pChartTable[dbIndex].LonMax;
                  Chs57->SetFullExtent(ext);
            }
#endif

#ifdef USE_CM93
            else if(GetCSChartType(pStack, StackEntry) == CHART_TYPE_CM93)
            {
                  Ch = new cm93chart();
                  int dbIndex = pStack->DBIndex[StackEntry];

                  cm93chart *Chcm93 = dynamic_cast<cm93chart*>(Ch);

                  Chcm93->SetNativeScale(pChartTable[dbIndex].Scale);

                  //    Explicitely set the chart extents from the database to
                  //    support the case wherein the SENC file has not yet been built
                  Extent ext;
                  ext.NLAT = pChartTable[dbIndex].LatMax;
                  ext.SLAT = pChartTable[dbIndex].LatMin;
                  ext.WLON = pChartTable[dbIndex].LonMin;
                  ext.ELON = pChartTable[dbIndex].LonMax;
                  Chcm93->SetFullExtent(ext);
            }

            else if(GetCSChartType(pStack, StackEntry) == CHART_TYPE_CM93COMP)
            {
                  Ch = new cm93compchart();
                  int dbIndex = pStack->DBIndex[StackEntry];

                  cm93compchart *Chcm93 = dynamic_cast<cm93compchart*>(Ch);

                  Chcm93->SetNativeScale(pChartTable[dbIndex].Scale);

                  //    Explicitely set the chart extents from the database to
                  //    support the case wherein the SENC file has not yet been built
                  Extent ext;
                  ext.NLAT = pChartTable[dbIndex].LatMax;
                  ext.SLAT = pChartTable[dbIndex].LatMin;
                  ext.WLON = pChartTable[dbIndex].LonMin;
                  ext.ELON = pChartTable[dbIndex].LonMax;
                  Chcm93->SetFullExtent(ext);
            }



#endif

            else
                  Ch = NULL;


            if(Ch)
            {
                  InitReturn ir;

                  wxString msg(_T("Initializing Chart "));
                  msg.Append(ChartFullPath);
                  wxLogMessage(msg);

                  ir = Ch->Init(ChartFullPath, init_flag, pParent->GetColorScheme());    // using the passed flag

                  if(INIT_OK == ir)
                  {
//    Only add to cache if requesting a full init
                        if(FULL_INIT == init_flag)
                        {
                              pce = new CacheEntry;
                              pce->FullPath = ChartFullPath;
                              pce->pChart = Ch;
                              pce->RecentTime = now.GetTicks();

                              pChartCache->Add((void *)pce);
                        }
                  }
                  else if(INIT_FAIL_REMOVE == ir)                 // some problem in chart Init()
                  {
                        delete Ch;
                        Ch = NULL;

//          Mark this chart in the database, so that it will not be seen during this run, but will stay in the database
                        int dbIndex = pStack->DBIndex[StackEntry];
                        wxString ChartToDisable = wxString(pChartTable[dbIndex].pFullPath,  wxConvUTF8);
                        DisableChart(ChartToDisable);


                  }
                  else if(INIT_FAIL_RETRY == ir)                  // recoverable problem in chart Init()
                  {
                        delete Ch;
                        Ch = NULL;
                  }


                  if(INIT_OK != ir)
                  {
                        wxString fp = GetFullPath(pStack, StackEntry);
                        fp.Prepend(_T("   OpenChartFromStack...Error opening chart "));
                        wxString id;
                        id.Printf(_T(" at index %d, return code %d"), StackEntry, ir);
                        fp.Append(id);
                        wxLogMessage(fp);
                  }

            }


            return Ch;
      }

      return NULL;
}

//-------------------------------------------------------------------
//    Disable Chart
//-------------------------------------------------------------------

int ChartDB::DisableChart(wxString& PathToDisable)
{
      //    Find the chart
      for(int i=0 ; i<nEntry ; i++)
      {
          if(PathToDisable.IsSameAs(wxString(pChartTable[i].pFullPath, wxConvUTF8)))
            {
//          Mark this chart in the database, so that it will not be seen during this run
//          How?  By setting the chart bounding box to an absurd value
//          Todo... Fix this heinous hack
                  pChartTable[i].LatMax = 0;
                  pChartTable[i].LatMin = .0001;

                  return 1;
            }
      }

      return 0;
}

void ChartDB::ApplyColorSchemeToCachedCharts(ColorScheme cs)
{
      ChartBase *Ch;
      CacheEntry *pce;
     //    Search the cache

      unsigned int nCache = pChartCache->GetCount();
      for(unsigned int i=0 ; i<nCache ; i++)
      {
            pce = (CacheEntry *)(pChartCache->Item(i));
            Ch = (ChartBase *)pce->pChart;
            if(Ch)
                  Ch->SetColorScheme(cs, true);

      }
}

//-------------------------------------------------------------------
//    Open a chart from the stack with conditions
//      a) Smallest or Largest scale
//      b) Raster or Vector
//-------------------------------------------------------------------

ChartBase *ChartDB::OpenStackChartConditional(ChartStack *ps, bool bLargest, bool bVector)
{
      int index;
      ChartBase *ptc = NULL;

      if(bLargest)
      {
            index = ps->nEntry - 1;

            while(index >= 0)
            {
                  bool bis_vector = (GetCSChartType(ps, index) == CHART_TYPE_S57) | (GetCSChartType(ps, index) == CHART_TYPE_CM93);
                  if((!bis_vector && !bVector) || (bis_vector && bVector))
                  {
                        ptc = OpenChartFromStack(ps, index);

                        if (NULL != ptc)
                            break;

                  }
                  index--;
            }
      }
      else
      {
            index = 0;

            while(index < ps->nEntry)
            {
                  bool bis_vector = (GetCSChartType(ps, index) == CHART_TYPE_S57) | (GetCSChartType(ps, index) == CHART_TYPE_CM93);
                  if((!bis_vector && !bVector) || (bis_vector && bVector))
                  {
                        ptc = OpenChartFromStack(ps, index);

                        if (NULL != ptc)
                              break;

                  }
                  index++;
            }
      }

      ps->CurrentStackEntry = index;
      return ptc;
}




//  Private version of PolyPt testing using floats instead of doubles

bool Intersect(MyFlPoint p1, MyFlPoint p2, MyFlPoint p3, MyFlPoint p4) ;
int CCW(MyFlPoint p0, MyFlPoint p1, MyFlPoint p2) ;

/*************************************************************************


 * FUNCTION:   G_FloatPtInPolygon
 *
 * PURPOSE
 * This routine determines if the point passed is in the polygon. It uses

 * the classical polygon hit-testing algorithm: a horizontal ray starting

 * at the point is extended infinitely rightwards and the number of
 * polygon edges that intersect the ray are counted. If the number is odd,

 * the point is inside the polygon.
 *
 * RETURN VALUE
 * (bool) TRUE if the point is inside the polygon, FALSE if not.
 *************************************************************************/


bool G_FloatPtInPolygon(MyFlPoint *rgpts, int wnumpts, float x, float y)

{

   MyFlPoint  *ppt, *ppt1 ;
   int   i ;
   MyFlPoint  pt1, pt2, pt0 ;
   int   wnumintsct = 0 ;

   pt0.x = x;
   pt0.y = y;

   pt1 = pt2 = pt0 ;
   pt2.x = 1.e6;

   // Now go through each of the lines in the polygon and see if it
   // intersects
   for (i = 0, ppt = rgpts ; i < wnumpts-1 ; i++, ppt++)
   {
      ppt1 = ppt;
        ppt1++;
        if (Intersect(pt0, pt2, *ppt, *(ppt1)))
         wnumintsct++ ;
   }

   // And the last line
   if (Intersect(pt0, pt2, *ppt, *rgpts))
      wnumintsct++ ;

   return (bool)(wnumintsct&1) ;

}


/*************************************************************************


 * FUNCTION:   Intersect
 *
 * PURPOSE
 * Given two line segments, determine if they intersect.
 *
 * RETURN VALUE
 * TRUE if they intersect, FALSE if not.
 *************************************************************************/


inline bool Intersect(MyFlPoint p1, MyFlPoint p2, MyFlPoint p3, MyFlPoint p4) {
      int i;
      i = CCW(p1, p2, p3);
      i = CCW(p1, p2, p4);
      i = CCW(p3, p4, p1);
      i = CCW(p3, p4, p2);
   return ((( CCW(p1, p2, p3) * CCW(p1, p2, p4)) <= 0)
        && (( CCW(p3, p4, p1) * CCW(p3, p4, p2)  <= 0) )) ;

}
/*************************************************************************


 * FUNCTION:   CCW (CounterClockWise)
 *
 * PURPOSE
 * Determines, given three points, if when travelling from the first to
 * the second to the third, we travel in a counterclockwise direction.
 *
 * RETURN VALUE
 * (int) 1 if the movement is in a counterclockwise direction, -1 if
 * not.
 *************************************************************************/


inline int CCW(MyFlPoint p0, MyFlPoint p1, MyFlPoint p2) {
   float dx1, dx2 ;
   float dy1, dy2 ;

   dx1 = p1.x - p0.x ; dx2 = p2.x - p0.x ;
   dy1 = p1.y - p0.y ; dy2 = p2.y - p0.y ;

   /* This is basically a slope comparison: we don't do divisions because

    * of divide by zero possibilities with pure horizontal and pure
    * vertical lines.
    */
   return ((dx1 * dy2 > dy1 * dx2) ? 1 : -1) ;

}


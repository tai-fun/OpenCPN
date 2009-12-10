/******************************************************************************
 * $Id: chartdb.cpp,v 1.29 2009/12/10 21:18:50 bdbcat Exp $
 *
 * Project:  OpenCPN
 * Purpose:  Chart Database Object
 * Author:   David Register, Mark A Sikes
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
 * Revision 1.29  2009/12/10 21:18:50  bdbcat
 * Beta 1210
 *
 * Revision 1.28  2009/11/18 01:24:15  bdbcat
 * 1.3.5 Beta 1117
 *
 * Revision 1.27  2009/09/30 02:28:52  bdbcat
 * Cleanup
 *
 * Revision 1.26  2009/09/28 23:05:21  bdbcat
 * Correct again for IDL crossing
 *
 * Revision 1.25  2009/09/28 13:20:14  bdbcat
 * Correct for IDL crossing
 *
 * Revision 1.24  2009/08/30 03:34:07  bdbcat
 * New Methods
 *
 * Revision 1.23  2009/08/22 15:50:44  bdbcat
 * Unicode fixup
 *
 * Revision 1.22  2009/08/22 14:04:19  bdbcat
 * Correct dir scan logic
 *
 * Revision 1.21  2009/08/22 01:17:39  bdbcat
 * Better CM93 detect
 *
 * Revision 1.20  2009/08/03 03:26:48  bdbcat
 * Cleanup for MSVC
 *
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
#include <wx/regex.h>

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


CPL_CVSID("$Id: chartdb.cpp,v 1.29 2009/12/10 21:18:50 bdbcat Exp $");

// ============================================================================
// implementation
// ============================================================================

ChartDB::ChartDB(MyFrame *parent)
{
      pParent = parent;
      pChartCache = new wxArrayPtrVoid;

      SetValid(false);                           // until loaded or created
}


ChartDB::~ChartDB()
{
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


//-------------------------------------------------------------------------------------------------------
//      Create a Chart
//      This version creates a fully functional UI-capable chart.
//-------------------------------------------------------------------------------------------------------

ChartBase *ChartDB::GetChart(const wxChar *theFilePath) const
{
      wxFileName fn(theFilePath);

      if(!fn.FileExists()) {
            wxLogMessage(wxT("   ...file does not exist: %s"), theFilePath);
            return NULL;
      }

      ChartBase *pch = NULL;

      wxString chartExt = fn.GetExt().Upper();
      if (chartExt == wxT("KAP")) {
            pch = new ChartKAP;
      }
      else if (chartExt == wxT("GEO")) {
            pch = new ChartGEO;
      }
      else if (chartExt == wxT("000") || chartExt == wxT("S57")) {
            pch = new s57chart;
      }
#ifdef USE_CM93
      else {
            wxRegEx rxName(wxT("[0-9]+"));
            wxRegEx rxExt(wxT("[A-G]"));
            if (rxName.Matches(fn.GetName()) && rxExt.Matches(fn.GetExt())) {
                  pch = new cm93compchart;
            }
      }
#endif

      return pch;
}




int ChartDB::BuildChartStack(ChartStack * cstk, float lat, float lon)
{
      int i=0;
      int j=0;

      if(!IsValid())
            return 0;                           // Database is not properly initialized

      int nEntry = GetChartTableEntries();

      for(i=0 ; i<nEntry ; i++)
      {

            ChartTableEntry *pt = (ChartTableEntry *)&GetChartTableEntry(i);

            if(CheckPositionWithinChart(i, lat, lon)  &&  (j < MAXSTACK) )
            {
                  cstk->DBIndex[j] = i;
                  j++;
            }

            //    Check the special case where chart spans the international dateline
            else if( (pt->GetLonMax() > 180.) && (pt->GetLonMin() < 180.) )
            {
                  if(CheckPositionWithinChart(i, lat, lon + 360.)  &&  (j < MAXSTACK) )
                  {
                        cstk->DBIndex[j] = i;
                        j++;
                  }
            }


      }

      cstk->nEntry = j;

//    Sort the stack on scale
      int swap = 1;
      int ti;
      while(swap == 1)
      {
            swap = 0;
            for(i=0 ; i<j-1 ; i++)
            {
                  const ChartTableEntry &m = GetChartTableEntry(cstk->DBIndex[i]);
                  const ChartTableEntry &n = GetChartTableEntry(cstk->DBIndex[i+1]);


                  if(n.GetScale() < m.GetScale())
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
//    Check to see it lat/lon is within a database chart at index
//-------------------------------------------------------------------
bool ChartDB::CheckPositionWithinChart(int index, float lat, float lon)
{
//           ChartTableEntry *pt = &pChartTable[index];
            const ChartTableEntry *pt = &GetChartTableEntry(index);

//    First check on rough Bounding box

            if((lat < pt->GetLatMax()) &&
                (lat > pt->GetLatMin()) &&
                (lon > pt->GetLonMin()) &&
                (lon < pt->GetLonMax()))
            {
//    Double check on Primary Ply points polygon

                  bool bInside = G_FloatPtInPolygon((MyFlPoint *)pt->GetpPlyTable(),
                              pt->GetnPlyEntries(),
                              lon, lat);

                  if(bInside )
                  {
                        if(pt->GetnAuxPlyEntries())
                        {
                              for(int k=0 ; k<pt->GetnAuxPlyEntries() ; k++)
                              {
                                    bool bAuxInside = G_FloatPtInPolygon((MyFlPoint *)pt->GetpAuxPlyTableEntry(k),
                                                                                    pt->GetAuxCntTableEntry(k),lon, lat);
                                    if(bAuxInside)
                                          return true;;
                              }

                        }
                        else
                              return true;
                  }
            }

            return false;
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


wxString ChartDB::GetFullPath(ChartStack *ps, int stackindex)
{
      int dbIndex = ps->DBIndex[stackindex];
      return wxString(GetChartTableEntry(dbIndex).GetpFullPath(),  wxConvUTF8);
}

//-------------------------------------------------------------------
//    Get PlyPoint from stack
//-------------------------------------------------------------------

int ChartDB::GetCSPlyPoint(ChartStack *ps, int stackindex, int plyindex, float *lat, float *lon)
{
      const ChartTableEntry &entry = GetChartTableEntry(ps->DBIndex[stackindex]);
      if(entry.GetnPlyEntries())
      {
            float *fp = entry.GetpPlyTable();
            fp += plyindex*2;
            *lat = *fp;
            fp++;
            *lon = *fp;
      }

      return entry.GetnPlyEntries();
}




//-------------------------------------------------------------------
//    Get Chart Scale
//-------------------------------------------------------------------
int ChartDB::GetStackChartScale(ChartStack *ps, int stackindex, char *buf, int nbuf)
{
      const ChartTableEntry &entry = GetChartTableEntry(ps->DBIndex[stackindex]);
      int sc = entry.GetScale();
      sprintf(buf, "%d", sc);

      return sc;
}

//-------------------------------------------------------------------
//    Find ChartStack entry index corresponding to Full Path name, if present
//-------------------------------------------------------------------
int ChartDB::GetStackEntry(ChartStack *ps, wxString fp)
{
      for(int i=0 ; i<ps->nEntry ; i++)
      {
            const ChartTableEntry &entry = GetChartTableEntry(ps->DBIndex[i]);
            if(fp.IsSameAs( wxString(entry.GetpFullPath(),  wxConvUTF8)) )
                  return i;
      }

      return -1;
}

//-------------------------------------------------------------------
//    Get CSChart Type
//-------------------------------------------------------------------
ChartTypeEnum ChartDB::GetCSChartType(ChartStack *ps, int stackindex)
{
      if((IsValid()) && (stackindex >= 0) && (stackindex < GetChartTableEntries()))
            return (ChartTypeEnum)GetChartTableEntry(ps->DBIndex[stackindex]).GetChartType();
      else
            return CHART_TYPE_UNKNOWN;
}


ChartFamilyEnum ChartDB::GetCSChartFamily(ChartStack *ps, int stackindex)
{
      if((IsValid()) && (stackindex < GetChartTableEntries()))
      {
            const ChartTableEntry &entry = GetChartTableEntry(ps->DBIndex[stackindex]);

            ChartTypeEnum type = (ChartTypeEnum)entry.GetChartType();
            switch(type)
            {
                  case  CHART_TYPE_KAP:          return CHART_FAMILY_RASTER;
                  case  CHART_TYPE_GEO:          return CHART_FAMILY_RASTER;
                  case  CHART_TYPE_S57:          return CHART_FAMILY_VECTOR;
                  case  CHART_TYPE_CM93:         return CHART_FAMILY_VECTOR;
                  case  CHART_TYPE_CM93COMP:     return CHART_FAMILY_VECTOR;
                  case  CHART_TYPE_DUMMY:        return CHART_FAMILY_RASTER;
                  default:                       return CHART_FAMILY_UNKNOWN;
            }
      }
      else
            return CHART_FAMILY_UNKNOWN;
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
//                  Ch = new s57chart();
//                  int dbIndex = pStack->DBIndex[StackEntry];

//                  s57chart *Chs57 = dynamic_cast<s57chart*>(Ch);

//                  Chs57->SetNativeScale(pChartTable[dbIndex].Scale);

                  Ch = new s57chart();
                  const ChartTableEntry &entry = GetChartTableEntry(pStack->DBIndex[StackEntry]);
                  s57chart *Chs57 = dynamic_cast<s57chart*>(Ch);

                  Chs57->SetNativeScale(entry.GetScale());

                  //    Explicitely set the chart extents from the database to
                  //    support the case wherein the SENC file has not yet been built
                  Extent ext;
                  ext.NLAT = entry.GetLatMax();
                  ext.SLAT = entry.GetLatMin();
                  ext.WLON = entry.GetLonMin();
                  ext.ELON = entry.GetLonMax();
                  Chs57->SetFullExtent(ext);
            }
#endif

#ifdef USE_CM93
            else if(GetCSChartType(pStack, StackEntry) == CHART_TYPE_CM93)
            {
//                  Ch = new cm93chart();
//                  int dbIndex = pStack->DBIndex[StackEntry];

//                  cm93chart *Chcm93 = dynamic_cast<cm93chart*>(Ch);

//                  Chcm93->SetNativeScale(pChartTable[dbIndex].Scale);

                  Ch = new cm93chart();
                  const ChartTableEntry &entry = GetChartTableEntry(pStack->DBIndex[StackEntry]);

                  cm93chart *Chcm93 = dynamic_cast<cm93chart*>(Ch);

                  Chcm93->SetNativeScale(entry.GetScale());

                  //    Explicitely set the chart extents from the database to
                  //    support the case wherein the SENC file has not yet been built
                  Extent ext;
                  ext.NLAT = entry.GetLatMax();
                  ext.SLAT = entry.GetLatMin();
                  ext.WLON = entry.GetLonMin();
                  ext.ELON = entry.GetLonMax();
                  Chcm93->SetFullExtent(ext);
            }

            else if(GetCSChartType(pStack, StackEntry) == CHART_TYPE_CM93COMP)
            {
//                  Ch = new cm93compchart();
//                  int dbIndex = pStack->DBIndex[StackEntry];

//                  cm93compchart *Chcm93 = dynamic_cast<cm93compchart*>(Ch);

//                  Chcm93->SetNativeScale(pChartTable[dbIndex].Scale);

                  Ch = new cm93compchart();
                  const ChartTableEntry &entry = GetChartTableEntry(pStack->DBIndex[StackEntry]);

                  cm93compchart *Chcm93 = dynamic_cast<cm93compchart*>(Ch);

                  Chcm93->SetNativeScale(entry.GetScale());

                  //    Explicitely set the chart extents from the database to
                  //    support the case wherein the SENC file has not yet been built
                  Extent ext;
                  ext.NLAT = entry.GetLatMax();
                  ext.SLAT = entry.GetLatMin();
                  ext.WLON = entry.GetLonMin();
                  ext.ELON = entry.GetLonMax();
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

                  Ch->SetColorScheme(pParent->GetColorScheme());
                  ir = Ch->Init(ChartFullPath, init_flag);    // using the passed flag

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
//                        int dbIndex = pStack->DBIndex[StackEntry];
//                        wxString ChartToDisable = wxString(pChartTable[dbIndex].pFullPath,  wxConvUTF8);
//                        DisableChart(ChartToDisable);

                        const ChartTableEntry &entry = GetChartTableEntry(pStack->DBIndex[StackEntry]);
                        wxString ChartToDisable = wxString(entry.GetpFullPath(),  wxConvUTF8);
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

/*
*/
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
//      a) Search Direction Start
//      b) Requested Chart Type
//-------------------------------------------------------------------

ChartBase *ChartDB::OpenStackChartConditional(ChartStack *ps, int index_start, bool bSearchDir, ChartTypeEnum New_Type, ChartFamilyEnum New_Family_Fallback)
{
      int index;

      int delta_index;
      ChartBase *ptc = NULL;

      if(bSearchDir == 1)
            delta_index = -1;

      else
            delta_index = 1;



      index = index_start;

      while((index >= 0) && (index < ps->nEntry))
      {
            ChartTypeEnum chart_type = (ChartTypeEnum)GetCSChartType(ps, index);
            if((chart_type == New_Type) || (New_Type == CHART_TYPE_DONTCARE))
            {
                  ptc = OpenChartFromStack(ps, index);
                  if (NULL != ptc)
                       break;
            }
                  index += delta_index;
      }

      //    Fallback, no useable chart of specified type found, so try for family match
      if(NULL == ptc)
      {
            index = index_start;

            while((index >= 0) && (index < ps->nEntry))
            {
                  ChartFamilyEnum chart_family = GetCSChartFamily(ps, index);
                  if(chart_family == New_Family_Fallback)
                  {
                        ptc = OpenChartFromStack(ps, index);

                        if (NULL != ptc)
                              break;

                  }
                  index += delta_index;
            }
      }

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

//   return(wnumintsct&1);

   //       If result is false, check the degenerate case where test point lies on a polygon endpoint
   if(!(wnumintsct&1))
   {
         for (i = 0, ppt = rgpts ; i < wnumpts ; i++, ppt++)
         {
               if(((*ppt).x == x) && ((*ppt).y == y))
                     return true;
         }
   }
   else
       return true;

   return false;
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


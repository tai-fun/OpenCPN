/******************************************************************************
 * $Id: cpl_csv.h,v 1.3 2008/08/09 23:45:10 bdbcat Exp $
 *
 * Project:  Common Portability Library
 * Purpose:  Functions for reading and scaning CSV (comma separated,
 *           variable length text files holding tables) files.  
 * Author:   Frank Warmerdam, warmerda@home.com
 *
 ******************************************************************************
 * Copyright (c) 1999, Frank Warmerdam
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************
 *
 * $Log: cpl_csv.h,v $
 * Revision 1.3  2008/08/09 23:45:10  bdbcat
 * *** empty log message ***
 *
 * Revision 1.2  2008/04/20 21:03:18  bdbcat
 * Export more csv functions
 *
 * Revision 1.1.1.1  2006/08/21 05:52:19  dsr
 * Initial import as opencpn, GNU Automake compliant.
 *
 * Revision 1.1.1.1  2006/04/19 03:23:28  dsr
 * Rename/Import to OpenCPN
 *
 * Revision 1.2  2003/06/27 16:14:22  warmerda
 * export CSV functions with CPL_DLL
 *
 * Revision 1.1  2000/04/05 21:55:59  warmerda
 * New
 *
 */

#ifndef CPL_CSV_H_INCLUDED
#define CPL_CSV_H_INCLUDED

#include "cpl_conv.h"
#include "cpl_string.h"
#include "cpl_vsi.h"

CPL_C_START

typedef enum {
    CC_ExactString,
    CC_ApproxString,
    CC_Integer
} CSVCompareCriteria;


/* ==================================================================== */
/*      The CSVTable is a persistant set of info about an open CSV      */
/*      table.  While it doesn't currently maintain a record index,     */
/*      or in-memory copy of the table, it could be changed to do so    */
/*      in the future.                                                  */
/* ==================================================================== */
typedef struct ctb {
    FILE        *fp;

    struct ctb *psNext;

    char        *pszFilename;

    char        **papszFieldNames;

    char        **papszRecFields;

    int         iLastLine;

    /* Cache for whole file */
    int         nLineCount;
    char        **papszLines;
    int         *panLineIndex;
    char        *pszRawData;
} CSVTable;

CSVTable *CSVAccess( const char * pszFilename );
CPL_DLL char **CSVSplitLine( const char *pszString );
CPL_DLL void CSVIngest( const char *pszFilename );



/* ==================================================================== */
/*      The CSVTable is a persistant set of info about an open CSV      */
/*      table.  While it doesn't currently maintain a record index,     */
/*      or in-memory copy of the table, it could be changed to do so    */
/*      in the future.                                                  */
/* ==================================================================== */
typedef struct ctb {
    FILE        *fp;

    struct ctb *psNext;

    char        *pszFilename;

    char        **papszFieldNames;

    char        **papszRecFields;

    int         iLastLine;

    /* Cache for whole file */
    int         nLineCount;
    char        **papszLines;
    int         *panLineIndex;
    char        *pszRawData;
} CSVTable;

CSVTable *CSVAccess( const char * pszFilename );
CPL_DLL char **CSVSplitLine( const char *pszString );
CPL_DLL void CSVIngest( const char *pszFilename );


const char CPL_DLL *CSVFilename( const char * );

char CPL_DLL  **CSVReadParseLine( FILE * );
char CPL_DLL **CSVScanLines( FILE *, int, const char *, CSVCompareCriteria );
char CPL_DLL **CSVScanFile( const char *, int, const char *,
                            CSVCompareCriteria );
char CPL_DLL **CSVScanFileByName( const char *, const char *, const char *,
                                  CSVCompareCriteria );
int CPL_DLL CSVGetFieldId( FILE *, const char * );
int CPL_DLL CSVGetFileFieldId( const char *, const char * );

void CPL_DLL CSVDeaccess( const char * );

const char  *CSVGetField( const char *, const char *, const char *,
                                 CSVCompareCriteria, const char * );

void CPL_DLL SetCSVFilenameHook( const char *(*)(const char *) );

CPL_C_END

#endif /* ndef CPL_CSV_H_INCLUDED */


/******************************************************************************
 * $Id: ogr_nullattrind.cpp,v 1.1 2006/08/21 05:52:20 dsr Exp $
 *
 * Project:  OpenCP
 * Purpose:  Implements Generic Null and NOP interface to atttribute index which
 *           is required by OGRLayer().
 *	     Derives from ogr_attrid.cpp, realizing pure virtuals as needed by
 *           OGRAttrIndex and OGRLayerAttrIndex.
 *             
 * Author:   David Register
 *
 ******************************************************************************
 * Copyright (c) 2006, David Register
 * Copyright (c) 2003, Frank Warmerdam
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
 * $Log: ogr_nullattrind.cpp,v $
 * Revision 1.1  2006/08/21 05:52:20  dsr
 * Initial revision
 *
 * Revision 1.1.1.1  2006/04/19 03:23:29  dsr
 * Rename/Import to OpenCPN
 *
 *
 */

#include "ogr_attrind.h"

CPL_CVSID("$Id: ogr_nullattrind.cpp,v 1.1 2006/08/21 05:52:20 dsr Exp $");

/************************************************************************/
/*                            OGRNullAttrIndex                          */
/*                                                                      */
/************************************************************************/

class OGRNullLayerAttrIndex;

class OGRNullAttrIndex : public OGRAttrIndex
{
public:
                OGRNullAttrIndex( OGRNullLayerAttrIndex *, int iIndex, int iField);
               ~OGRNullAttrIndex();

	       /* base class virtual methods */
    long        GetFirstMatch( OGRField *psKey );
    long       *GetAllMatches( OGRField *psKey );

    OGRErr      AddEntry( OGRField *psKey, long nFID );
    OGRErr      RemoveEntry( OGRField *psKey, long nFID );

    OGRErr      Clear();
};

/************************************************************************/
/* ==================================================================== */
/*                         OGRNullLayerAttrIndex                        */
/*                                                                      */
/*      MapInfo .ID specific implementation of a layer attribute        */
/*      index.                                                          */
/* ==================================================================== */
/************************************************************************/

class OGRNullLayerAttrIndex : public OGRLayerAttrIndex
{
public:
    
                OGRNullLayerAttrIndex();
    virtual     ~OGRNullLayerAttrIndex();

    /* base class virtual methods */
    OGRErr      Initialize( const char *pszIndexPath, OGRLayer * );
    OGRErr      CreateIndex( int iField );
    OGRErr      DropIndex( int iField );
    OGRErr      IndexAllFeatures( int iField = -1 );

    OGRErr      AddToIndex( OGRFeature *poFeature, int iField = -1 );
    OGRErr      RemoveFromIndex( OGRFeature *poFeature );

    OGRAttrIndex *GetFieldIndex( int iField );

};

/************************************************************************/
/*                        OGRNullLayerAttrIndex()                         */
/************************************************************************/

OGRNullLayerAttrIndex::OGRNullLayerAttrIndex()

{
}

/************************************************************************/
/*                        ~OGRNullLayerAttrIndex()                        */
/************************************************************************/

OGRNullLayerAttrIndex::~OGRNullLayerAttrIndex()

{
}

/************************************************************************/
/*                             Initialize()                             */
/************************************************************************/

OGRErr OGRNullLayerAttrIndex::Initialize( const char *pszIndexPathIn, 
                                        OGRLayer *poLayerIn )

{
     return OGRERR_NONE;
}


/************************************************************************/
/*                          IndexAllFeatures()                          */
/************************************************************************/

OGRErr OGRNullLayerAttrIndex::IndexAllFeatures( int iField )

{

    return OGRERR_NONE;
}

/************************************************************************/
/*                            CreateIndex()                             */
/************************************************************************/

OGRErr OGRNullLayerAttrIndex::CreateIndex( int iField )

{
    return OGRERR_FAILURE;

}

/************************************************************************/
/*                             DropIndex()                              */
/************************************************************************/

OGRErr OGRNullLayerAttrIndex::DropIndex( int iField )

{
    return OGRERR_NONE;

}


/************************************************************************/
/*                         GetFieldAttrIndex()                          */
/************************************************************************/

OGRAttrIndex *OGRNullLayerAttrIndex::GetFieldIndex( int iField )

{
     return NULL;
}

/************************************************************************/
/*                             AddToIndex()                             */
/************************************************************************/

OGRErr OGRNullLayerAttrIndex::AddToIndex( OGRFeature *poFeature,
                                        int iTargetField )

{

    return OGRERR_UNSUPPORTED_OPERATION;
}

/************************************************************************/
/*                          RemoveFromIndex()                           */
/************************************************************************/

OGRErr OGRNullLayerAttrIndex::RemoveFromIndex( OGRFeature * /*poFeature*/ )

{
    return OGRERR_UNSUPPORTED_OPERATION;
}

/************************************************************************/
/*                     OGRCreateDefaultLayerIndex()                     */
/************************************************************************/

OGRLayerAttrIndex *OGRCreateDefaultLayerIndex()

{
    return new OGRNullLayerAttrIndex();
}

/************************************************************************/
/* ==================================================================== */
/*                            OGRNullAttrIndex                            */
/* ==================================================================== */
/************************************************************************/

/* class declared at top of file */

/************************************************************************/
/*                           OGRNullAttrIndex()                           */
/************************************************************************/

OGRNullAttrIndex::OGRNullAttrIndex( OGRNullLayerAttrIndex *poLayerIndex, 
                                int iIndexIn, int iFieldIn )

{
}

/************************************************************************/
/*                          ~OGRNullAttrIndex()                           */
/************************************************************************/

OGRNullAttrIndex::~OGRNullAttrIndex()
{
}

/************************************************************************/
/*                              AddEntry()                              */
/************************************************************************/

OGRErr OGRNullAttrIndex::AddEntry( OGRField *psKey, long nFID )

{
    return OGRERR_NONE;
}

/************************************************************************/
/*                            RemoveEntry()                             */
/************************************************************************/

OGRErr OGRNullAttrIndex::RemoveEntry( OGRField * /*psKey*/, long /*nFID*/ )

{
    return OGRERR_UNSUPPORTED_OPERATION;
}


/************************************************************************/
/*                           GetFirstMatch()                            */
/************************************************************************/

long OGRNullAttrIndex::GetFirstMatch( OGRField *psKey )

{
    return 0l;
}

/************************************************************************/
/*                           GetAllMatches()                            */
/************************************************************************/

long *OGRNullAttrIndex::GetAllMatches( OGRField *psKey )

{
    return 0L;
}

/************************************************************************/
/*                               Clear()                                */
/************************************************************************/

OGRErr OGRNullAttrIndex::Clear()

{
    return OGRERR_UNSUPPORTED_OPERATION;
}

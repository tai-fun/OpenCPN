#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( LINE_OF_POSITION, CObject )

LINE_OF_POSITION::LINE_OF_POSITION()
{
   Empty();
}

LINE_OF_POSITION::~LINE_OF_POSITION()
{
   Empty();
}

void LINE_OF_POSITION::Empty( void )
{
   ASSERT_VALID( this );

   ZoneID.Empty();
   LineOfPosition = 0.0;
   MasterLine     = Unknown;
}

void LINE_OF_POSITION::Parse( int first_field_number, const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   ZoneID         = sentence.Field(   first_field_number );
   LineOfPosition = sentence.Double(  first_field_number + 1 );
   MasterLine     = sentence.Boolean( first_field_number + 2 );
}

void LINE_OF_POSITION::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   sentence += ZoneID;
   sentence += LineOfPosition;
   sentence += MasterLine;
}

const LINE_OF_POSITION& LINE_OF_POSITION::operator = ( const LINE_OF_POSITION& source )
{
   ASSERT_VALID( this );

   ZoneID         = source.ZoneID;
   LineOfPosition = source.LineOfPosition;
   MasterLine     = source.MasterLine;

   return( *this );
}

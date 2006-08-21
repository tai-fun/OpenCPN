#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( FREQUENCY_AND_MODE, CObject )

FREQUENCY_AND_MODE::FREQUENCY_AND_MODE()
{
   Empty();
}

FREQUENCY_AND_MODE::~FREQUENCY_AND_MODE()
{
   Empty();
}

void FREQUENCY_AND_MODE::Empty( void )
{
   ASSERT_VALID( this );

   Frequency = 0.0;
   Mode      = CommunicationsModeUnknown;
}

void FREQUENCY_AND_MODE::Parse( int first_field_number, const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   Frequency = sentence.Double( first_field_number );
   Mode      = sentence.CommunicationsMode( first_field_number + 1 );
}

void FREQUENCY_AND_MODE::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   sentence += Frequency;
   sentence += Mode;
}

const FREQUENCY_AND_MODE& FREQUENCY_AND_MODE::operator = ( const FREQUENCY_AND_MODE& source )
{
   ASSERT_VALID( this );

   Frequency = source.Frequency;
   Mode      = source.Mode;

   return( *this );
}

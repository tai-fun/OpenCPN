#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( RATIO_AND_PULSE, CObject )

RATIO_AND_PULSE::RATIO_AND_PULSE()
{
   Empty();
}

RATIO_AND_PULSE::~RATIO_AND_PULSE()
{
   Empty();
}

void RATIO_AND_PULSE::Empty( void )
{
   ASSERT_VALID( this );

   SignalToNoiseRatio = 0;
   PulseShapeECD      = 0;
}

void RATIO_AND_PULSE::Parse( int first_field_number, const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   SignalToNoiseRatio = sentence.Integer( first_field_number );
   PulseShapeECD      = sentence.Integer( first_field_number + 1 );
}

void RATIO_AND_PULSE::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   sentence += SignalToNoiseRatio;
   sentence += PulseShapeECD;
}

const RATIO_AND_PULSE& RATIO_AND_PULSE::operator = ( const RATIO_AND_PULSE& source )
{
   ASSERT_VALID( this );

   SignalToNoiseRatio = source.SignalToNoiseRatio;
   PulseShapeECD      = source.PulseShapeECD;

   return( *this );
}

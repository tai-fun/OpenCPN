#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( VLW, RESPONSE )

VLW::VLW()
{
   Mnemonic = "VLW";
   Empty();
}

VLW::~VLW()
{
   Mnemonic.Empty();
   Empty();
}

void VLW::Empty( void )
{
   ASSERT_VALID( this );

   TotalDistanceNauticalMiles      = 0.0;
   DistanceSinceResetNauticalMiles = 0.0;
}

BOOL VLW::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** VLW - Distance Traveled through Water
   **
   **        1   2 3   4 5
   **        |   | |   | |
   ** $--VLW,x.x,N,x.x,N*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Total cumulative distance
   **  2) N = Nautical Miles
   **  3) Distance since Reset
   **  4) N = Nautical Miles
   **  5) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 5 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   TotalDistanceNauticalMiles      = sentence.Double( 1 );
   DistanceSinceResetNauticalMiles = sentence.Double( 3 );

   return( TRUE );
}

BOOL VLW::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += TotalDistanceNauticalMiles;
   sentence += "N";
   sentence += DistanceSinceResetNauticalMiles;
   sentence += "N";

   sentence.Finish();

   return( TRUE );
}

const VLW& VLW::operator = ( const VLW& source )
{
   ASSERT_VALID( this );

   TotalDistanceNauticalMiles      = source.TotalDistanceNauticalMiles;
   DistanceSinceResetNauticalMiles = source.DistanceSinceResetNauticalMiles;

   return( *this );
}

#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( WNC, RESPONSE )

WNC::WNC()
{
   Mnemonic = "WNC";
   Empty();
}

WNC::~WNC()
{
   Mnemonic.Empty();
   Empty();
}

void WNC::Empty( void )
{
   ASSERT_VALID( this );

   MilesDistance      = 0.0;
   KilometersDistance = 0.0;
   To.Empty();
   From.Empty();
}

BOOL WNC::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** WNC - Distance - Waypoint to Waypoint
   **
   **        1   2 3   4 5    6    7
   **        |   | |   | |    |    |
   ** $--WNC,x.x,N,x.x,K,c--c,c--c*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Distance, Nautical Miles
   **  2) N = Nautical Miles
   **  3) Distance, Kilometers
   **  4) K = Kilometers
   **  5) TO Waypoint
   **  6) FROM Waypoint
   **  7) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   MilesDistance      = sentence.Double( 1 );
   KilometersDistance = sentence.Double( 3 );
   To                 = sentence.Field( 5 );
   From               = sentence.Field( 6 );

   return( TRUE );
}

BOOL WNC::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += MilesDistance;
   sentence += "N";
   sentence += KilometersDistance;
   sentence += "K";
   sentence += To;
   sentence += From;

   sentence.Finish();

   return( TRUE );
}

const WNC& WNC::operator = ( const WNC& source )
{
   ASSERT_VALID( this );

   MilesDistance      = source.MilesDistance;
   KilometersDistance = source.KilometersDistance;
   To                 = source.To;
   From               = source.From;

   return( *this );
}

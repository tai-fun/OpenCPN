#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( BOD, RESPONSE )

BOD::BOD()
{
   Mnemonic = "BOD";
   Empty();
}

BOD::~BOD()
{
   Mnemonic.Empty();
   Empty();
}

void BOD::Empty( void )
{
   ASSERT_VALID( this );

   BearingTrue     = 0.0;
   BearingMagnetic = 0.0;
   To.Empty();
   From.Empty();
}

BOOL BOD::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** BOD - Bearing - Waypoint to Waypoint
   **
   **        1   2 3   4 5    6    7
   **        |   | |   | |    |    |
   ** $--BOD,x.x,T,x.x,M,c--c,c--c*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Bearing Degrees, TRUE
   **  2) T = True
   **  3) Bearing Degrees, Magnetic
   **  4) M = Magnetic
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

   BearingTrue     = sentence.Double( 1 );
   BearingMagnetic = sentence.Double( 3 );
   To              = sentence.Field( 5 );
   From            = sentence.Field( 6 );

   return( TRUE );
}

BOOL BOD::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += BearingTrue;
   sentence += "T";
   sentence += BearingMagnetic;
   sentence += "M";
   sentence += To;
   sentence += From;

   sentence.Finish();

   return( TRUE );
}

const BOD& BOD::operator = ( const BOD& source )
{
   ASSERT_VALID( this );

   BearingTrue     = source.BearingTrue;
   BearingMagnetic = source.BearingMagnetic;
   To              = source.To;
   From            = source.From;

   return( *this );
}

#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( BEC, RESPONSE )

BEC::BEC()
{
   Mnemonic = "BEC";
   Empty();
}

BEC::~BEC()
{
   Mnemonic.Empty();
   Empty();
}

void BEC::Empty( void )
{
   ASSERT_VALID( this );

   UTCTime.Empty();
   BearingTrue           = 0.0;
   BearingMagnetic       = 0.0;
   DistanceNauticalMiles = 0.0;
   To.Empty();
}

BOOL BEC::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** BEC - Bearing & Distance to Waypoint - Dead Reckoning
   **                                                         12
   **        1         2       3 4        5 6   7 8   9 10  11|    13
   **        |         |       | |        | |   | |   | |   | |    |
   ** $--BEC,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c*hh<CR><LF>
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 13 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   UTCTime               = sentence.Field( 1 );
   Position.Parse( 2, 3, 4, 5, sentence );
   BearingTrue           = sentence.Double( 6 );
   BearingMagnetic       = sentence.Double( 8 );
   DistanceNauticalMiles = sentence.Double( 10 );
   To                    = sentence.Field( 12 );

   return( TRUE );
}

BOOL BEC::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Position;
   sentence += BearingTrue;
   sentence += "T";
   sentence += BearingMagnetic;
   sentence += "M";
   sentence += DistanceNauticalMiles;
   sentence += "N";
   sentence += To;

   sentence.Finish();

   return( TRUE );
}

const BEC& BEC::operator = ( const BEC& source )
{
   ASSERT_VALID( this );

   UTCTime               = source.UTCTime;
   Position              = source.Position;
   BearingTrue           = source.BearingTrue;
   BearingMagnetic       = source.BearingMagnetic;
   DistanceNauticalMiles = source.DistanceNauticalMiles;
   To                    = source.To;

   return( *this );
}

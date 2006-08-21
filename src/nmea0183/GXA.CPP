#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( GXA, RESPONSE )

GXA::GXA()
{
   Mnemonic = "GXA";
}

GXA::~GXA()
{
   Mnemonic.Empty();
}

void GXA::Empty( void )
{
   ASSERT_VALID( this );

   UTCTime.Empty();
   Position.Empty();
   WaypointID.Empty();
   SatelliteNumber = 0;
}

BOOL GXA::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** GXA - TRANSIT Position - Latitude/Longitude
   ** Location and time of TRANSIT fix at waypoint
   **
   **        1         2       3 4        5 6    7 8
   **        |         |       | |        | |    | |
   ** $--GXA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c,X*hh<CR><LF>
   **
   ** 1) UTC of position fix
   ** 2) Latitude
   ** 3) East or West
   ** 4) Longitude
   ** 5) North or South
   ** 6) Waypoint ID
   ** 7) Satelite number
   ** 8) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 8 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   UTCTime         = sentence.Field( 1 );
   Position.Parse( 2, 3, 4, 5, sentence );
   WaypointID      = sentence.Field( 6 );
   SatelliteNumber = (WORD) sentence.Integer( 7 );

   return( TRUE );
}

BOOL GXA::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Position;
   sentence += WaypointID;
   sentence += SatelliteNumber;

   sentence.Finish();

   return( TRUE );
}

const GXA& GXA::operator = ( const GXA& source )
{
   ASSERT_VALID( this );

   UTCTime         = source.UTCTime;
   Position        = source.Position;
   WaypointID      = source.WaypointID;
   SatelliteNumber = source.SatelliteNumber;

   return( *this );
}

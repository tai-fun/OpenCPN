#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( RSA, RESPONSE )

RSA::RSA()
{
   Mnemonic = "RSA";
   Empty();
}

RSA::~RSA()
{
   Mnemonic.Empty();
   Empty();
}

void RSA::Empty( void )
{
   ASSERT_VALID( this );

   Starboard            = 0.0;
   IsStarboardDataValid = Unknown;
   Port                 = 0.0;
   IsPortDataValid      = Unknown;
}

BOOL RSA::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** RSA - Rudder Sensor Angle
   **
   **        1   2 3   4 5
   **        |   | |   | |
   ** $--RSA,x.x,A,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Starboard (or single) rudder sensor, "-" means Turn To Port
   **  2) Status, A means data is valid
   **  3) Port rudder sensor
   **  4) Status, A means data is valid
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

   Starboard            = sentence.Double(  1 );
   IsStarboardDataValid = sentence.Boolean( 2 );
   Port                 = sentence.Double(  3 );
   IsPortDataValid      = sentence.Boolean( 4 );

   return( TRUE );
}

BOOL RSA::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Starboard;
   sentence += IsStarboardDataValid;
   sentence += Port;
   sentence += IsPortDataValid;
   
   sentence.Finish();

   return( TRUE );
}

const RSA& RSA::operator = ( const RSA& source )
{
   ASSERT_VALID( this );

   Starboard            = source.Starboard;
   IsStarboardDataValid = source.IsStarboardDataValid;
   Port                 = source.Port;
   IsPortDataValid      = source.IsPortDataValid;

   return( *this );
}

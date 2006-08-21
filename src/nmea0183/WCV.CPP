#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( WCV, RESPONSE )

WCV::WCV()
{
   Mnemonic = "WCV";
   Empty();
}

WCV::~WCV()
{
   Mnemonic.Empty();
   Empty();
}

void WCV::Empty( void )
{
   ASSERT_VALID( this );

   Velocity = 0.0;
   To.Empty();
}

BOOL WCV::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** WCV - Waypoint Closure Velocity
   **
   **        1   2 3    4
   **        |   | |    |
   ** $--WCV,x.x,N,c--c*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Velocity
   **  2) N = knots
   **  3) Waypoint ID
   **  4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 4 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   Velocity = sentence.Double( 1 );
   To       = sentence.Field( 3 );

   return( TRUE );
}

BOOL WCV::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Velocity;
   sentence += "N";
   sentence += To;

   sentence.Finish();
   return( TRUE );
}

const WCV& WCV::operator = ( const WCV& source )
{
   ASSERT_VALID( this );

   Velocity = source.Velocity;
   To       = source.To;

   return( *this );
}

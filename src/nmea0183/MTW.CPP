#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( MTW, RESPONSE )

MTW::MTW()
{
   Mnemonic = "MTW";
   Empty();
}

MTW::~MTW()
{
   Mnemonic.Empty();
   Empty();
}

void MTW::Empty( void )
{
   ASSERT_VALID( this );

   Temperature = 0.0;
   UnitOfMeasurement.Empty();
}

BOOL MTW::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** MTW - Water Temperature
   **
   **        1   2 3
   **        |   | | 
   ** $--MTW,x.x,C*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Degrees
   **  2) Unit of Measurement, Celcius
   **  3) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 3 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   Temperature       = sentence.Double( 1 );
   UnitOfMeasurement = sentence.Field( 2 );

   return( TRUE );
}

BOOL MTW::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Temperature;
   sentence += UnitOfMeasurement;

   sentence.Finish();

   return( TRUE );
}

const MTW& MTW::operator = ( const MTW& source )
{
   ASSERT_VALID( this );

   Temperature       = source.Temperature;
   UnitOfMeasurement = source.UnitOfMeasurement;

   return( *this );
}

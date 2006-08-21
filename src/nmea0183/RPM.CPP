#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( RPM, RESPONSE )

RPM::RPM()
{
   Mnemonic = "RPM";
   Empty();
}

RPM::~RPM()
{
   Mnemonic.Empty();
   Empty();
}

void RPM::Empty( void )
{
   ASSERT_VALID( this );

   Source.Empty();
   SourceNumber             = 0;
   RevolutionsPerMinute     = 0.0;
   PropellerPitchPercentage = 0.0;
   IsDataValid              = Unknown;
}

BOOL RPM::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** RPM - Revolutions
   **
   **        1 2 3   4   5 6
   **        | | |   |   | |
   ** $--RPM,a,x,x.x,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Sourse, S = Shaft, E = Engine
   **  2) Engine or shaft number
   **  3) Speed, Revolutions per minute
   **  4) Propeller pitch, % of maximum, "-" means astern
   **  5) Status, A means data is valid
   **  6) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 6 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   Source                   = sentence.Field( 1 );
   SourceNumber             = sentence.Integer( 2 );
   RevolutionsPerMinute     = sentence.Double( 3 );
   PropellerPitchPercentage = sentence.Double( 4 );
   IsDataValid              = sentence.Boolean( 5 );

   return( TRUE );
}

BOOL RPM::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Source;
   sentence += SourceNumber;
   sentence += RevolutionsPerMinute;
   sentence += PropellerPitchPercentage;
   sentence += IsDataValid;
   
   sentence.Finish();

   return( TRUE );
}

const RPM& RPM::operator = ( const RPM& source )
{
   ASSERT_VALID( this );

   Source                   = source.Source;
   SourceNumber             = source.SourceNumber;
   RevolutionsPerMinute     = source.RevolutionsPerMinute;
   PropellerPitchPercentage = source.PropellerPitchPercentage;
   IsDataValid              = source.IsDataValid;

   return( *this );
}

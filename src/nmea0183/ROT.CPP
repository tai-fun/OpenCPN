#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( ROT, RESPONSE )

ROT::ROT()
{
   Mnemonic = "ROT";
   Empty();
}

ROT::~ROT()
{
   Mnemonic.Empty();
   Empty();
}

void ROT::Empty( void )
{
   ASSERT_VALID( this );

   RateOfTurn  = 0.0;
   IsDataValid = Unknown;
}

BOOL ROT::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** ROT - Rate Of Turn
   **
   **        1   2 3
   **        |   | |
   ** $--ROT,x.x,A*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Rate Of Turn, degrees per minute, "-" means bow turns to port
   **  2) Status, A means data is valid
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

   RateOfTurn  = sentence.Double( 1 );
   IsDataValid = sentence.Boolean( 2 );

   return( TRUE );
}

BOOL ROT::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += RateOfTurn;
   sentence += IsDataValid;
   
   sentence.Finish();

   return( TRUE );
}

const ROT& ROT::operator = ( const ROT& source )
{
   ASSERT_VALID( this );

   RateOfTurn  = source.RateOfTurn;
   IsDataValid = source.IsDataValid;

   return( *this );
}

#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( HDT, RESPONSE )

HDT::HDT()
{
   Mnemonic = "HDT";
   Empty();
}

HDT::~HDT()
{
   Mnemonic.Empty();
   Empty();
}

void HDT::Empty( void )
{
   ASSERT_VALID( this );

   DegreesTrue = 0.0;
}

BOOL HDT::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** HDT - Heading - True
   **
   **        1   2 3
   **        |   | |
   ** $--HDT,x.x,T*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Heading Degrees, TRUE
   **  2) T = True
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

   DegreesTrue = sentence.Double( 1 );

   return( TRUE );
}

BOOL HDT::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += DegreesTrue;
   sentence += "T";

   sentence.Finish();

   return( TRUE );
}

const HDT& HDT::operator = ( const HDT& source )
{
   ASSERT_VALID( this );

   DegreesTrue = source.DegreesTrue;

   return( *this );
}

#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( STN, RESPONSE )

STN::STN()
{
   Mnemonic = "STN";
   Empty();
}

STN::~STN()
{
   Mnemonic.Empty();
   Empty();
}

void STN::Empty( void )
{
   ASSERT_VALID( this );

   TalkerIDNumber = 0;
}

BOOL STN::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** STN - Multiple Data ID
   **
   **        1   2
   **        |   |
   ** $--STN,x.x,*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Talker ID Number
   **  2) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 2 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   TalkerIDNumber   = sentence.Integer( 1 );

   return( TRUE );
}

BOOL STN::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += TalkerIDNumber;

   sentence.Finish();

   return( TRUE );
}

const STN& STN::operator = ( const STN& source )
{
   ASSERT_VALID( this );

   TalkerIDNumber = source.TalkerIDNumber;

   return( *this );
}

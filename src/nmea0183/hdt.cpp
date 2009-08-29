#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


HDT::HDT()
{
   Mnemonic = _T("HDT");
   Empty();
}

HDT::~HDT()
{
   Mnemonic.Empty();
   Empty();
}

void HDT::Empty( void )
{
   DegreesTrue = 0.0;
}

bool HDT::Parse( const SENTENCE& sentence )
{

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

   if ( sentence.IsChecksumBad( 3 ) == TRUE )
   {
      SetErrorMessage( _T("Invalid Checksum") );
      return( FALSE );
   }

   DegreesTrue = sentence.Double( 1 );

   return( TRUE );
}

bool HDT::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += DegreesTrue;
   sentence += _T("T");

   sentence.Finish();

   return( TRUE );
}

const HDT& HDT::operator = ( const HDT& source )
{
   DegreesTrue = source.DegreesTrue;

   return( *this );
}

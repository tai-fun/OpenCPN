#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


HDM::HDM()
{
   Mnemonic = _T("HDM");
   Empty();
}

HDM::~HDM()
{
   Mnemonic.Empty();
   Empty();
}

void HDM::Empty( void )
{
   DegreesMagnetic = 0.0;
}

bool HDM::Parse( const SENTENCE& sentence )
{

   /*
   ** HDM - Heading - Magnetic
   **
   **        1   2 3
   **        |   | |
   ** $--HDM,x.x,M*hh<CR><LF>
   **
   ** Field Number:
   **  1) Heading Degrees, Magnetic
   **  2) M = Magnetic
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

   DegreesMagnetic = sentence.Double( 1 );

   return( TRUE );
}

bool HDM::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += DegreesMagnetic;
   sentence += _T("M");

   sentence.Finish();

   return( TRUE );
}

const HDM& HDM::operator = ( const HDM& source )
{
      DegreesMagnetic = source.DegreesMagnetic;

   return( *this );
}

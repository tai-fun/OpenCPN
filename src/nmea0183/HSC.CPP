#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( HSC, RESPONSE )

HSC::HSC()
{
   Mnemonic = "HSC";
   Empty();
}

HSC::~HSC()
{
   Mnemonic.Empty();
   Empty();
}

void HSC::Empty( void )
{
   ASSERT_VALID( this );

   DegreesTrue     = 0.0;
   DegreesMagnetic = 0.0;
}

BOOL HSC::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** HSC - Heading Steering Command
   **
   **        1   2 3   4  5
   **        |   | |   |  |
   ** $--HSC,x.x,T,x.x,M,*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Heading Degrees, True
   **  2) T = True
   **  3) Heading Degrees, Magnetic
   **  4) M = Magnetic
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

   DegreesTrue     = sentence.Double( 1 );
   DegreesMagnetic = sentence.Double( 3 );

   return( TRUE );
}

BOOL HSC::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += DegreesTrue;
   sentence += "T";
   sentence += DegreesMagnetic;
   sentence += "M";

   sentence.Finish();

   return( TRUE );
}

const HSC& HSC::operator = ( const HSC& source )
{
   ASSERT_VALID( this );

   DegreesTrue     = source.DegreesTrue;
   DegreesMagnetic = source.DegreesMagnetic;

   return( *this );
}

#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( VHW, RESPONSE )

VHW::VHW()
{
   Mnemonic = "VHW";
   Empty();
}

VHW::~VHW()
{
   Mnemonic.Empty();
   Empty();
}

void VHW::Empty( void )
{
   ASSERT_VALID( this );

   DegreesTrue       = 0.0;
   DegreesMagnetic   = 0.0;
   Knots             = 0.0;
   KilometersPerHour = 0.0;
}

BOOL VHW::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** VHW - Water speed and heading
   **
   **        1   2 3   4 5   6 7   8 9
   **        |   | |   | |   | |   | |
   ** $--VHW,x.x,T,x.x,M,x.x,N,x.x,K*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Degress True
   **  2) T = True
   **  3) Degrees Magnetic
   **  4) M = Magnetic
   **  5) Knots (speed of vessel relative to the water)
   **  6) N = Knots
   **  7) Kilometers (speed of vessel relative to the water)
   **  8) K = Kilometers
   **  9) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 9 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   DegreesTrue       = sentence.Double( 1 );
   DegreesMagnetic   = sentence.Double( 3 );
   Knots             = sentence.Double( 5 );
   KilometersPerHour = sentence.Double( 7 );

   return( TRUE );
}

BOOL VHW::Write( SENTENCE& sentence )
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
   sentence += Knots;
   sentence += "N";
   sentence += KilometersPerHour;
   sentence += "K";

   sentence.Finish();

   return( TRUE );
}

const VHW& VHW::operator = ( const VHW& source )
{
   ASSERT_VALID( this );

   DegreesTrue       = source.DegreesTrue;
   DegreesMagnetic   = source.DegreesMagnetic;
   Knots             = source.Knots;
   KilometersPerHour = source.KilometersPerHour;

   return( *this );
}

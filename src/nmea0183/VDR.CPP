#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( VDR, RESPONSE )

VDR::VDR()
{
   Mnemonic = "VDR";
   Empty();
}

VDR::~VDR()
{
   Mnemonic.Empty();
   Empty();
}

void VDR::Empty( void )
{
   ASSERT_VALID( this );

   DegreesTrue     = 0.0;
   DegreesMagnetic = 0.0;
   Knots           = 0.0;
}

BOOL VDR::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** VDR - Set and Drift
   **
   **        1   2 3   4 5   6 7
   **        |   | |   | |   | |
   ** $--VDR,x.x,T,x.x,M,x.x,N*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Degress True
   **  2) T = True
   **  3) Degrees Magnetic
   **  4) M = Magnetic
   **  5) Knots (speed of current)
   **  6) N = Knots
   **  7) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   DegreesTrue     = sentence.Double( 1 );
   DegreesMagnetic = sentence.Double( 3 );
   Knots           = sentence.Double( 5 );

   return( TRUE );
}

BOOL VDR::Write( SENTENCE& sentence )
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

   sentence.Finish();

   return( TRUE );
}

const VDR& VDR::operator = ( const VDR& source )
{
   ASSERT_VALID( this );

   DegreesTrue     = source.DegreesTrue;
   DegreesMagnetic = source.DegreesMagnetic;
   Knots           = source.Knots;

   return( *this );
}

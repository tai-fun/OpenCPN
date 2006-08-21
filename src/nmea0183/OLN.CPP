#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( OLN, RESPONSE )

OLN::OLN()
{
   Mnemonic = "OLN";
   Empty();
}

OLN::~OLN()
{
   Mnemonic.Empty();
   Empty();
}

void OLN::Empty( void )
{
   ASSERT_VALID( this );

   Pair1.Empty();
   Pair2.Empty();
   Pair3.Empty();
}

BOOL OLN::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** OLN - Omega Lane Numbers
   **
   **        1          2          3          4
   **        |--------+ |--------+ |--------+ |
   ** $--OLN,aa,xxx,xxx,aa,xxx,xxx,aa,xxx,xxx*hh<CR><LF>
   **
   **  1) Omega Pair 1
   **  2) Omega Pair 1
   **  3) Omega Pair 1
   **  4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 10 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   Pair1.Parse( 1, sentence );
   Pair2.Parse( 4, sentence );
   Pair3.Parse( 7, sentence );

   return( TRUE );
}

BOOL OLN::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   Pair1.Write( sentence );
   Pair2.Write( sentence );
   Pair3.Write( sentence );

   sentence.Finish();

   return( TRUE );
}

const OLN& OLN::operator = ( const OLN& source )
{
   ASSERT_VALID( this );

   Pair1 = source.Pair1;
   Pair2 = source.Pair2;
   Pair3 = source.Pair3;

   return( *this );
}

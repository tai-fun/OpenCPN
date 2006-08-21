#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( DPT, RESPONSE )

DPT::DPT()
{
   Mnemonic = "DPT";
   Empty();
}

DPT::~DPT()
{
   Mnemonic.Empty();
   Empty();
}

void DPT::Empty( void )
{
   ASSERT_VALID( this );

   DepthMeters                = 0.0;
   OffsetFromTransducerMeters = 0.0;
}

BOOL DPT::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** DPT - Heading - Deviation & Variation
   **
   **        1   2   3
   **        |   |   |
   ** $--DPT,x.x,x.x*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Depth, meters
   **  2) Offset from transducer, 
   **     positive means distance from tansducer to water line
   **     negative means distance from transducer to keel
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

   DepthMeters                = sentence.Double( 1 );
   OffsetFromTransducerMeters = sentence.Double( 2 );

   return( TRUE );
}

BOOL DPT::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += DepthMeters;
   sentence += OffsetFromTransducerMeters;

   sentence.Finish();

   return( TRUE );
}

const DPT& DPT::operator = ( const DPT& source )
{
   ASSERT_VALID( this );

   DepthMeters                = source.DepthMeters;
   OffsetFromTransducerMeters = source.OffsetFromTransducerMeters;

   return( *this );
}

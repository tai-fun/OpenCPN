#include "nmea0183.h"
//#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

//IMPLEMENT_DYNAMIC( VTG, RESPONSE )

VTG::VTG()
{
   Mnemonic = _T("VTG");
   Empty();
}

VTG::~VTG()
{
   Mnemonic.Empty();
   Empty();
}

void VTG::Empty( void )
{
//   ASSERT_VALID( this );

   TrackDegreesTrue       = 0.0;
   TrackDegreesMagnetic   = 0.0;
   SpeedKnots             = 0.0;
   SpeedKilometersPerHour = 0.0;
}

bool VTG::Parse( const SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** VTG - Track made good and Ground speed
   **
   **        1   2 3   4 5	 6 7   8 9
   **        |   | |   | |	 | |   | |
   ** $--VTG,x.x,T,x.x,M,x.x,N,x.x,K*hh<CR><LF>
   **
   ** Field Number:
   **  1) Track Degrees
   **  2) T = True
   **  3) Track Degrees
   **  4) M = Magnetic
   **  5) Speed Knots
   **  6) N = Knots
   **  7) Speed Kilometers Per Hour
   **  8) K = Kilometers Per Hour
   **  9) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 9 ) == TRUE )
   {
      SetErrorMessage( _T("Invalid Checksum") );
      return( FALSE );
   }

   if ( sentence.GetNumberOfDataFields() != 8 )
   {
         SetErrorMessage( _T("Invalid FieldCount") );
         return( FALSE );
   }


   TrackDegreesTrue       = sentence.Double( 1 );
   TrackDegreesMagnetic   = sentence.Double( 3 );
   SpeedKnots             = sentence.Double( 5 );
   SpeedKilometersPerHour = sentence.Double( 7 );

   return( TRUE );
}

bool VTG::Write( SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += TrackDegreesTrue;
   sentence += _T("T");
   sentence += TrackDegreesMagnetic;
   sentence += _T("M");
   sentence += SpeedKnots;
   sentence += _T("N");
   sentence += SpeedKilometersPerHour;
   sentence += _T("K");

   sentence.Finish();

   return( TRUE );
}

const VTG& VTG::operator = ( const VTG& source )
{
//   ASSERT_VALID( this );

   TrackDegreesTrue       = source.TrackDegreesTrue;
   TrackDegreesMagnetic   = source.TrackDegreesMagnetic;
   SpeedKnots             = source.SpeedKnots;
   SpeedKilometersPerHour = source.SpeedKilometersPerHour;

   return( *this );
}

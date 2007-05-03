#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


RMC::RMC()
{
   Mnemonic = "RMC";
   Empty();
}

RMC::~RMC()
{
   Mnemonic.Empty();
   Empty();
}

void RMC::Empty( void )
{

   UTCTime.Empty();
   IsDataValid                = Unknown0183;
   SpeedOverGroundKnots       = 0.0;
   Position.Empty();
   TrackMadeGoodDegreesTrue   = 0.0;
   Date.Empty();
   MagneticVariation          = 0.0;
   MagneticVariationDirection = EW_Unknown;
}

bool RMC::Parse( const SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** RMC - Recommended Minimum Navigation Information
   **                                                            12
   **        1         2 3       4 5        6 7   8   9    10  11|
   **        |         | |       | |        | |   |   |    |   | |
   ** $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxx,x.x,a*hh<CR><LF>
   **
   ** Field Number: 
   **  1) UTC Time
   **  2) Status, V = Navigation receiver warning
   **  3) Latitude
   **  4) N or S
   **  5) Longitude
   **  6) E or W
   **  7) Speed over ground, knots
   **  8) Track made good, degrees true
   **  9) Date, ddmmyy
   ** 10) Magnetic Variation, degrees
   ** 11) E or W
   ** 12) Checksum
   */

   /*
   ** First we check the checksum...
   */

   NMEA0183_BOOLEAN check = sentence.IsChecksumBad( 12 );

   if ( check == NTrue )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   }
   
   if ( check == Unknown0183 )
   {
      SetErrorMessage( "Missing Checksum" );
      return( FALSE );
   } 

   UTCTime                    = sentence.Field( 1 );
   IsDataValid                = sentence.Boolean( 2 );
   Position.Parse( 3, 4, 5, 6, sentence );
   SpeedOverGroundKnots       = sentence.Double( 7 );
   TrackMadeGoodDegreesTrue   = sentence.Double( 8 );
   Date                       = sentence.Field( 9 );
   MagneticVariation          = sentence.Double( 10 );
   MagneticVariationDirection = sentence.EastOrWest( 11 );

   return( TRUE );
}

bool RMC::Write( SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += IsDataValid;
   sentence += Position;
   sentence += SpeedOverGroundKnots;
   sentence += TrackMadeGoodDegreesTrue;
   sentence += Date;
   sentence += MagneticVariation;
   sentence += MagneticVariationDirection;

   sentence.Finish();

   return( TRUE );
}

const RMC& RMC::operator = ( const RMC& source )
{
//   ASSERT_VALID( this );

   UTCTime                    = source.UTCTime;
   IsDataValid                = source.IsDataValid;
   Position                   = source.Position;
   SpeedOverGroundKnots       = source.SpeedOverGroundKnots;
   TrackMadeGoodDegreesTrue   = source.TrackMadeGoodDegreesTrue;
   Date                       = source.Date;
   MagneticVariation          = source.MagneticVariation;
   MagneticVariationDirection = source.MagneticVariationDirection;

  return( *this );
}

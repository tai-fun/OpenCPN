#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( ZDA, RESPONSE )

ZDA::ZDA()
{
   Mnemonic = "ZDA";
   Empty();
}

ZDA::~ZDA()
{
   Mnemonic.Empty();
   Empty();
}

void ZDA::Empty( void )
{
   ASSERT_VALID( this );

   UTCTime.Empty();
   Day                   = 0;
   Month                 = 0;
   Year                  = 0;
   LocalHourDeviation    = 0;
   LocalMinutesDeviation = 0;
}

BOOL ZDA::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** ZDA - Time & Date
   ** UTC, day, month, year and local time zone
   **
   ** $--ZDA,hhmmss.ss,xx,xx,xxxx,xx,xx*hh<CR><LF>
   **        |         |  |  |    |  |
   **        |         |  |  |    |  +- Local zone minutes description, same sign as local hours
   **        |         |  |  |    +- Local zone description, 00 to +- 13 hours
   **        |         |  |  +- Year
   **        |         |  +- Month, 01 to 12
   **        |         +- Day, 01 to 31
   **        +- Universal Time Coordinated (UTC)
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   UTCTime               = sentence.Field( 1 );
   Day                   = sentence.Integer( 2 );
   Month                 = sentence.Integer( 3 );
   Year                  = sentence.Integer( 4 );
   LocalHourDeviation    = sentence.Integer( 5 );
   LocalMinutesDeviation = sentence.Integer( 6 );

   return( TRUE );
}

BOOL ZDA::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += Day;
   sentence += Month;
   sentence += Year;
   sentence += LocalHourDeviation;
   sentence += LocalMinutesDeviation;

   sentence.Finish();

   return( TRUE );
}

const ZDA& ZDA::operator = ( const ZDA& source )
{
   ASSERT_VALID( this );

   UTCTime               = source.UTCTime;
   Day                   = source.Day;
   Month                 = source.Month;
   Year                  = source.Year;
   LocalHourDeviation    = source.LocalHourDeviation;
   LocalMinutesDeviation = source.LocalMinutesDeviation;

   return( *this );
}

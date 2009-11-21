#include "nmea0183.h"
//#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

//IMPLEMENT_DYNAMIC( GLL, RESPONSE )

GLL::GLL()
{
   Mnemonic = _T("GLL");
   Empty();
}

GLL::~GLL()
{
   Mnemonic.Empty();
   Empty();
}

void GLL::Empty( void )
{
//   ASSERT_VALID( this );

   Position.Empty();
   UTCTime.Empty();
   IsDataValid = Unknown0183;
}

bool GLL::Parse( const SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** GLL - Geographic Position - Latitude/Longitude
   ** Latitude, N/S, Longitude, E/W, UTC, Status
   **
   **        +-------------------------------- 1) Latitude
   **        |       +------------------------ 2) N or S (North or South)
   **        |       | +---------------------- 3) Longitude
   **        |       | |        +------------- 4) E or W (East or West)
   **        |       | |        | +----------- 5) Universal Time Coordinated (UTC)
   **        |       | |        | |         +- 6) Status A - Data Valid, V - Data Invalid
   **        |       | |        | |         | +7) Checksum
   ** $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,A*hh<CR><LF>
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 7 ) == NTrue )
   {
      SetErrorMessage( _T("Invalid Checksum") );
      return( FALSE );
   }

   if ( sentence.GetNumberOfDataFields() != 6 )
   {
         SetErrorMessage( _T("Invalid FieldCount") );
         return( FALSE );
   }


   Position.Parse( 1, 2, 3, 4, sentence );
   UTCTime     = sentence.Field( 5 );
   IsDataValid = sentence.Boolean( 6 );

   return( TRUE );
}


const wxString& GLL::PlainEnglish( void )
{
//   ASSERT_VALID( this );

   static wxString return_string;

   return_string.Empty();
/*
   char temp_string[ 128 ];

   sprintf( temp_string, "At %d, you were at Latitude %ld %s, Longitude %ld %s.",
            (const char *) UTCTime,
            Position.Latitude.Latitude,
            ( Position.Latitude.Northing == North ) ? "North" : "South",
            Position.Longitude.Longitude,
            ( Position.Longitude.Easting == East ) ? "East" : "West" );

   return_string = temp_string;
*/
   return( return_string );
}


bool GLL::Write( SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += Position;
   sentence += UTCTime;
   sentence += IsDataValid;

   sentence.Finish();

   return( TRUE );
}

const GLL& GLL::operator = ( const GLL& source )
{
//   ASSERT_VALID( this );

   Position    = source.Position;
   UTCTime     = source.UTCTime;
   IsDataValid = source.IsDataValid;

   return( *this );
}

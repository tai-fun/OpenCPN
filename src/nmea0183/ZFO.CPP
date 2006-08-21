#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( ZFO, RESPONSE )

ZFO::ZFO()
{
   Mnemonic = "ZFO";
   Empty();
}

ZFO::~ZFO()
{
   Mnemonic.Empty();
   Empty();
}

void ZFO::Empty( void )
{
   ASSERT_VALID( this );

   UTCTime.Empty();
   ElapsedTime.Empty();
   From.Empty();
}

BOOL ZFO::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** ZFO - UTC & Time from origin Waypoint
   **
   **        1         2         3    4
   **        |         |         |    |
   ** $--ZFO,hhmmss.ss,hhmmss.ss,c--c*hh<CR><LF>
   **
   ** Fields:
   **  1) Universal Time Coordinated (UTC)
   **  2) Elapsed Time
   **  3) Origin Waypoint ID
   **  4) Checksum
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 4 ) == True )
   {
      SetErrorMessage( "Invalid Checksum" );
      return( FALSE );
   } 

   UTCTime     = sentence.Field( 1 );
   ElapsedTime = sentence.Field( 2 );
   From        = sentence.Field( 3 );

   return( TRUE );
}

BOOL ZFO::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += UTCTime;
   sentence += ElapsedTime;
   sentence += From;

   sentence.Finish();

   return( TRUE );
}

const ZFO& ZFO::operator = ( const ZFO& source )
{
   ASSERT_VALID( this );

   UTCTime     = source.UTCTime;
   ElapsedTime = source.ElapsedTime;
   From        = source.From;

   return( *this );
}

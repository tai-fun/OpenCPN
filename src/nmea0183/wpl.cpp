#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

//IMPLEMENT_DYNAMIC( WPL, RESPONSE )

WPL::WPL()
{
   Mnemonic = _T("WPL");
   Empty();
}

WPL::~WPL()
{
   Mnemonic.Empty();
   Empty();
}

void WPL::Empty( void )
{

   Position.Empty();
   To.Empty();
}

bool WPL::Parse( const SENTENCE& sentence )
{

   /*
   ** WPL - Waypoint Location
   **
   **        +-------------------------------- 1) Latitude
   **        |       +------------------------ 2) N or S (North or South)
   **        |       | +---------------------- 3) Longitude
   **        |       | |        +------------- 4) E or W (East or West)
   **        |       | |        | +----------- 5) Waypoint name
   **        |       | |        | |    +-------6) Checksum
   **        |       | |        | |    |
   ** $--WPL,llll.ll,a,yyyyy.yy,a,c--c*hh<CR><LF>
   */

   /*
   ** First we check the checksum...
   */

   if ( sentence.IsChecksumBad( 6 ) == NTrue )
   {
      SetErrorMessage( _T("Invalid Checksum") );
      return( FALSE );
   }

   Position.Parse( 1, 2, 3, 4, sentence );
   To = sentence.Field( 5 );

   return( TRUE );
}

bool WPL::Write( SENTENCE& sentence )
{
   /*
   ** Let the parent do its thing
   */

   RESPONSE::Write( sentence );

   sentence += Position;
   sentence += To;

   sentence.Finish();

   return( TRUE );
}

const WPL& WPL::operator = ( const WPL& source )
{

   Position = source.Position;
   To       = source.To;

   return( *this );
}

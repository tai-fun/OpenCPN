#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( ASD, RESPONSE )

ASD::ASD()
{
   Mnemonic = "ASD";
}

ASD::~ASD()
{
   Mnemonic.Empty();
}

void ASD::Empty( void )
{
   ASSERT_VALID( this );

}

#pragma warning( disable : 4100 )

BOOL ASD::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** ASD - Autopilot System Data
   **
   ** FORMAT TO BE DETERMINED
   **
   ** As soon as NMEA makes up their mind and publishes this we can't do anything but return TRUE
   */

   return( TRUE );
}

#pragma warning( default : 4100 )

BOOL ASD::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence.Finish();

   return( TRUE );
}

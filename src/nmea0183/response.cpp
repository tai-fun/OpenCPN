#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


RESPONSE::RESPONSE()
{
   Talker.Empty();
   ErrorMessage.Empty();
}

RESPONSE::~RESPONSE()
{
   Mnemonic.Empty();
   Talker.Empty();
   ErrorMessage.Empty();
}

void RESPONSE::SetContainer( NMEA0183 *container )
{
//   ASSERT_VALID( this );
   assert( container != NULL );

   container_p = container;
}

void RESPONSE::SetErrorMessage( const wxString& error_message )
{
//   ASSERT_VALID( this );

   ErrorMessage  = Mnemonic;
   ErrorMessage += _T(", ");
   ErrorMessage += error_message;
}

bool RESPONSE::Write( SENTENCE& sentence )
{
//   ASSERT_VALID( this );

   /*
   ** All NMEA0183 sentences begin with the mnemonic...
   */

    sentence  = _T("$--");
   sentence.Sentence.Append(Mnemonic);

//   sentence += Mnemonic;
//   sentence += ",";

   return( TRUE );
}

const wxString& RESPONSE::PlainEnglish( void )
{
   static wxString return_string;

   return_string.Empty();

   return( return_string );
}

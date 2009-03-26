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
   container_p = container;
}

void RESPONSE::SetErrorMessage( const wxString& error_message )
{
   ErrorMessage  = Mnemonic;
   ErrorMessage += _T(", ");
   ErrorMessage += error_message;
}

bool RESPONSE::Write( SENTENCE& sentence )
{
   /*
   ** All NMEA0183 sentences begin with the mnemonic...
   */

    sentence  = _T("$");

    if(NULL == container_p)
          sentence.Sentence.Append(_T("--"));
    else
          sentence.Sentence.Append(container_p->TalkerID);

    sentence.Sentence.Append(Mnemonic);

   return( TRUE );
}

const wxString& RESPONSE::PlainEnglish( void )
{
   static wxString return_string;

   return_string.Empty();

   return( return_string );
}

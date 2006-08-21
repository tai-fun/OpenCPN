#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

 wxString& talker_id( const wxString &sentence )
{
   static wxString return_string;

   return_string.Empty();

   if ( sentence.Len() >= 3 )
   {
      if ( sentence[ 0 ] == '$' )
      {
         return_string = sentence.Mid( 1, 2 );
      }
   }

   return( return_string );
}

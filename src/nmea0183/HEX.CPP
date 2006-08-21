#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

const wxString& Hex( DWORD value )
{
   static wxString return_string;

   return_string.Empty();

   char temp_string[ 20 ];

   sprintf( temp_string, "%04lX", value );

   return_string = temp_string;

   return( return_string );
}

#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

int HexValue( const char *hex_string )
{
   int return_value = 0;

   long scan_value = 0;

   sscanf( hex_string, "%lx",  &scan_value );

   return_value = (int)scan_value;
   return( return_value );
}

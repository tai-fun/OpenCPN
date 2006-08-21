#include "nmea0183.h"

BYTE ComputeChecksum( const wxString &line_to_parse )
{
   BYTE checksum_value = 0;

   int string_length = line_to_parse.GetLength();
   int index = 1; // Skip over the $ at the begining of the sentence

   while( index < string_length && line_to_parse[ index ] != '*' )
   {
      checksum_value ^= line_to_parse[ index ];
      index++;
   }

   return( checksum_value );
}

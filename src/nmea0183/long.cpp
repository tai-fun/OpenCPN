#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


LONGITUDE::LONGITUDE()
{
   Empty();
}

LONGITUDE::~LONGITUDE()
{
   Empty();
}

void LONGITUDE::Empty( void )
{

   Longitude = 0.0;
   Easting   = EW_Unknown;
}

bool LONGITUDE::IsDataValid( void )
{
   if ( Easting != East && Easting != West )
   {
      return( FALSE );
   }

   return( TRUE );
}

void LONGITUDE::Parse( int position_field_number, int east_or_west_field_number, const SENTENCE& sentence )
{
   wxString w_or_e = sentence.Field( east_or_west_field_number );
   Set( sentence.Double( position_field_number ), w_or_e );
}

void LONGITUDE::Set( double position, const wxString& east_or_west )
{
//   assert( east_or_west != NULL );

   Longitude = position;

   if ( east_or_west[ 0 ] == 'E' )
   {
      Easting = East;
   }
   else if ( east_or_west[ 0 ] == 'W' )
   {
      Easting = West;
   }
   else
   {
      Easting = EW_Unknown;
   }
}

void LONGITUDE::Write( SENTENCE& sentence )
{

    wxString temp_string;
    int neg = 0;
    int d;
    int m;

    if (Longitude < 0.0) {
            Longitude = -Longitude;
            neg = 1;
            }
    d = (int) Longitude;
    m = (int) ((Longitude - (double) d) * 60000.0);

    if (neg)
            d = -d;

      float f = (m % 1000)/10. + 0.5;
      int g = (int)f;

      temp_string.Printf(_T("%03d%02d.%03d"), d, m / 1000, g);


   sentence += temp_string;

   if ( Easting == East )
   {
       sentence += _T("E");
   }
   else if ( Easting == West )
   {
       sentence += _T("W");
   }
   else
   {
      /*
      ** Add Nothing
      */
   }
}

const LONGITUDE& LONGITUDE::operator = ( const LONGITUDE& source )
{

   Longitude = source.Longitude;
   Easting   = source.Easting;

   return( *this );
}

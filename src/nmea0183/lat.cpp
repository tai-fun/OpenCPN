#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


LATITUDE::LATITUDE()
{
   Empty();
}

LATITUDE::~LATITUDE()
{
   Empty();
}

void LATITUDE::Empty( void )
{

   Latitude = 0.0;
   Northing = NS_Unknown;
}

bool LATITUDE::IsDataValid( void )
{
   if ( Northing != North && Northing != South )
   {
      return( FALSE );
   }

   return( TRUE );
}

void LATITUDE::Parse( int position_field_number, int north_or_south_field_number, const SENTENCE& sentence )
{
   Set( sentence.Double( position_field_number ), sentence.Field( north_or_south_field_number ) );
}

void LATITUDE::Set( double position, const char *north_or_south )
{
   assert( north_or_south != NULL );

   Latitude = position;
   
   if ( north_or_south[ 0 ] == 'N' )
   {
      Northing = North;
   }
   else if ( north_or_south[ 0 ] == 'S' )
   {
      Northing = South;
   }
   else
   {
      Northing = NS_Unknown;
   }
}

void LATITUDE::Write( SENTENCE& sentence )
{

   char temp_string[ 80 ];
    int neg = 0;
    int d;
    int m;

    if (Latitude < 0.0) {
		Latitude = -Latitude;
		neg = 1;
		}
    d = (int) Latitude;
    m = (int) ((Latitude - (double) d) * 60000.0);

    if (neg)
		d = -d;

	float f = (m % 1000)/10. + 0.5;
      int g = (int)f;

	sprintf(temp_string, "%d%02d.%02d", d, m / 1000, g);

   
   
   
   
   sentence += temp_string;
   
   if ( Northing == North )
   {
      sentence += "N";
   }
   else if ( Northing == South )
   {
      sentence += "S";
   }
   else
   {
      /*
      ** Add Nothing
      */
   }
}

const LATITUDE& LATITUDE::operator = ( const LATITUDE& source )
{

   Latitude = source.Latitude;
   Northing = source.Northing;

   return( *this );
}

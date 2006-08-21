#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


LATLONG::LATLONG()
{
   Empty();
}

LATLONG::~LATLONG()
{
   Empty();
}

void LATLONG::Empty( void )
{

   Latitude.Empty();
   Longitude.Empty();
}

bool LATLONG::Parse( int LatitudePositionFieldNumber, int NorthingFieldNumber, int LongitudePositionFieldNumber, int EastingFieldNumber, const SENTENCE& LineToParse )
{

   Latitude.Parse(  LatitudePositionFieldNumber, NorthingFieldNumber, LineToParse );
   Longitude.Parse( LongitudePositionFieldNumber, EastingFieldNumber, LineToParse );

   if ( Latitude.IsDataValid() && Longitude.IsDataValid() )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

void LATLONG::Write( SENTENCE& sentence )
{

   Latitude.Write( sentence );
   Longitude.Write( sentence );
}

const LATLONG& LATLONG::operator = ( const LATLONG& source )
{

   Latitude  = source.Latitude;
   Longitude = source.Longitude;

   return( *this );
}

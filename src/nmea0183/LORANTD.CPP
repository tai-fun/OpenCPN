#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( LORAN_TIME_DIFFERENCE, CObject )

LORAN_TIME_DIFFERENCE::LORAN_TIME_DIFFERENCE()
{
   Empty();
}

LORAN_TIME_DIFFERENCE::~LORAN_TIME_DIFFERENCE()
{
   Empty();
}

void LORAN_TIME_DIFFERENCE::Empty( void )
{
   ASSERT_VALID( this );
   Microseconds = 0.0;
   SignalStatus = LoranUnknown;
}

void LORAN_TIME_DIFFERENCE::Parse( int first_field_number, const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   Microseconds  = sentence.Double( first_field_number );

   wxString field_data = sentence.Field( first_field_number + 1 );

   if ( field_data == "B" )
   {
      SignalStatus = LoranBlinkWarning;   
   }
   else if ( field_data == "C" )
   {
      SignalStatus = LoranCycleWarning;
   }
   else if ( field_data == "C" )
   {
      SignalStatus = LoranSNRWarning;
   }
   else if ( field_data == "A" )
   {
      SignalStatus = LoranValid;
   }
   else
   {
      SignalStatus = LoranUnknown;
   }
}

void LORAN_TIME_DIFFERENCE::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   sentence += Microseconds;

   switch( SignalStatus )
   {
      case LoranValid:
      
         sentence += "A";
         break; 

      case LoranBlinkWarning:
      
         sentence += "B";
         break; 

      case LoranCycleWarning:
      
         sentence += "C";
         break; 

      case LoranSNRWarning:
      
         sentence += "S";
         break; 

      default:

         sentence += "";
   }
}

const LORAN_TIME_DIFFERENCE& LORAN_TIME_DIFFERENCE::operator = ( const LORAN_TIME_DIFFERENCE& source )
{
   ASSERT_VALID( this );

   Microseconds = source.Microseconds;
   SignalStatus = source.SignalStatus;

   return( *this );
}

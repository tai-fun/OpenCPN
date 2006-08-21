#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( RTE, RESPONSE )

RTE::RTE()
{
   Mnemonic = "RTE";
   Empty();
}

RTE::~RTE()
{
   Mnemonic.Empty();
   Empty();
}

void RTE::Empty( void )
{
   ASSERT_VALID( this );

   total_number_of_messages     = 0.0;
   last_message_number_received = 0.0;
   message_number               = 0.0;
   last_waypoint_number_written = 0;

   TypeOfRoute = RouteUnknown;
   RouteName.Empty();
                  
   delete_all_entries();
}

BOOL RTE::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** RTE - Routes
   **
   **        1   2   3 4	 5		       x    n
   **        |   |   | |    |           |    |
   ** $--RTE,x.x,x.x,a,c--c,c--c, ..... c--c*hh<CR><LF>
   **
   ** Field Number: 
   **  1) Total number of messages being transmitted
   **  2) Message Number
   **  3) Message mode
   **     c = complete route, all waypoints
   **     w = working route, the waypoint you just left, the waypoint you're heading to then all the rest
   **  4) Waypoint ID
   **  x) More Waypoints
   **  n) Checksum
   */

   delete_all_entries();

   int field_number = 1;

   total_number_of_messages = sentence.Double( 1 );
   
   double this_message_number = sentence.Double( 2 );
   
   if ( this_message_number == 1.0 )
   {
      /*
      ** Make sure we've got a clean list
      */

      delete_all_entries();
   }

   CString field_data = sentence.Field( 3 );

   if ( field_data == "c" )
   {
      TypeOfRoute = CompleteRoute;
   }
   else if ( field_data == "w" )
   {
      TypeOfRoute = WorkingRoute;
   }
   else
   {
      TypeOfRoute = RouteUnknown;
   }

   RouteName = sentence.Field( 4 );

   int number_of_data_fields = sentence.GetNumberOfDataFields();
   field_number = 5;

   while( field_number < number_of_data_fields )
   {
      Waypoints.Add( new CString( sentence.Field( field_number ) ) );
      field_number++;
   }

   return( TRUE );
}

BOOL RTE::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += total_number_of_messages;
   sentence += message_number;

   switch( TypeOfRoute )
   {
      case CompleteRoute:

         sentence += "c";
         break;

      case WorkingRoute:

         sentence += "w";
         break;

      default:

         sentence += "";
         break;
   }

   sentence += RouteName;

   /*
   ** To Be done
   ** Take the number of entries in the list and write them out until we're done
   */

   sentence.Finish();

   return( TRUE );
}

void RTE::delete_all_entries( void )
{
   ASSERT_VALID( this );

   int index = 0;
   int number_of_entries = Waypoints.GetSize();

   while( index < number_of_entries )
   {
      delete Waypoints[ index ];
      index++;
   }

   Waypoints.RemoveAll();
}

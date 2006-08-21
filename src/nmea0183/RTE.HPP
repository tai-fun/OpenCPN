#if ! defined( RTE_CLASS_HEADER )
#define RTE_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RTE : public RESPONSE
{

   private:

      void delete_all_entries( void );

      double total_number_of_messages;
      double last_message_number_received;
      double message_number;

      int last_waypoint_number_written;

   public:

      RTE();
     ~RTE();

      typedef enum
      {
         RouteUnknown = 0,
         CompleteRoute,
         WorkingRoute
      }
      ROUTE_TYPE;

      ROUTE_TYPE TypeOfRoute;
      wxString    RouteName;
//      CPtrArray  Waypoints; // Yes, I tried using CStringArray but it is not an array of CStrings, it is an array of LPCSTRs

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );
};

#endif // RTE_CLASS_HEADER

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

      double last_message_number_received;

      int last_waypoint_number_written;

   public:

      RTE();
     ~RTE();


      ROUTE_TYPE TypeOfRoute;
      wxString    RouteName;
      wxArrayString Waypoints;
      int message_number;
      int total_number_of_messages;

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );
      virtual bool AddWaypoint(const wxString& name);
};

#endif // RTE_CLASS_HEADER

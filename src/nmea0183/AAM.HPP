#if ! defined( AAM_CLASS_HEADER )
#define AAM_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class AAM : public RESPONSE
{


   public:

      AAM();
     ~AAM();

      /*
      ** Data
      */

      NMEA0183_BOOLEAN IsArrivalCircleEntered;
      NMEA0183_BOOLEAN IsPerpendicular;
      double           CircleRadius;
      wxString          WaypointID;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const AAM& operator = ( const AAM& source );
};

#endif // AAM_CLASS_HEADER

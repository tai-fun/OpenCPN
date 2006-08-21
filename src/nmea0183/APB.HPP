#if ! defined( APB_CLASS_HEADER )
#define APB_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class APB : public RESPONSE
{


   public:

      APB();
     ~APB();

      /*
      ** Data
      */

      NMEA0183_BOOLEAN IsLoranBlinkOK;
      NMEA0183_BOOLEAN IsLoranCCycleLockOK;
      double           CrossTrackErrorMagnitude;
      LEFTRIGHT        DirectionToSteer;
      wxString          CrossTrackUnits;
      NMEA0183_BOOLEAN IsArrivalCircleEntered;
      NMEA0183_BOOLEAN IsPerpendicular;
      double           BearingOriginToDestination;
      wxString          BearingOriginToDestinationUnits;
      wxString          To;
      double           BearingPresentPositionToDestination;
      wxString          BearingPresentPositionToDestinationUnits;
      double           HeadingToSteer;
      wxString          HeadingToSteerUnits;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const APB& operator = ( const APB& source );
};

#endif // APB_CLASS_HEADER

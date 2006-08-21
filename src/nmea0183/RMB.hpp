#if ! defined( RMB_CLASS_HEADER )
#define RMB_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RMB : public RESPONSE
{

   public:

      RMB();
      virtual ~RMB();

      /*
      ** Data
      */

      NMEA0183_BOOLEAN IsDataValid;
      double           CrossTrackError;
      LEFTRIGHT        DirectionToSteer;
      wxString          To;
      wxString          From;
      LATLONG          DestinationPosition;
      double           RangeToDestinationNauticalMiles;
      double           BearingToDestinationDegreesTrue;
      double           DestinationClosingVelocityKnots;
      NMEA0183_BOOLEAN IsArrivalCircleEntered;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const RMB& operator = ( const RMB& source );
};

#endif // RMB_CLASS_HEADER

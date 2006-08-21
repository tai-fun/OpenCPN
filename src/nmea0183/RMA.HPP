#if ! defined( RMA_CLASS_HEADER )
#define RMA_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RMA : public RESPONSE
{

   public:

      RMA();
     ~RMA();

      /*
      ** Data
      */

      NMEA0183_BOOLEAN IsDataValid;
      LATLONG          Position;
      double           TimeDifferenceA;
      double           TimeDifferenceB;
      double           SpeedOverGroundKnots;
      double           TrackMadeGoodDegreesTrue;
      double           MagneticVariation;
      EASTWEST         MagneticVariationDirection;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const RMA& operator = ( const RMA& source );
};

#endif // RMA_CLASS_HEADER

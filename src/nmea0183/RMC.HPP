#if ! defined( RMC_CLASS_HEADER )
#define RMC_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RMC : public RESPONSE
{

   public:

      RMC();
     ~RMC();

      /*
      ** Data
      */

      wxString          UTCTime;
      NMEA0183_BOOLEAN IsDataValid;
      LATLONG          Position;
      double           SpeedOverGroundKnots;
      double           TrackMadeGoodDegreesTrue;
      wxString          Date;
      double           MagneticVariation;
      EASTWEST         MagneticVariationDirection;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const RMC& operator = ( const RMC& source );
};

#endif // RMC_CLASS_HEADER

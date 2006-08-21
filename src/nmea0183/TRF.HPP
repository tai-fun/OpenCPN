#if ! defined( TRF_CLASS_HEADER )
#define TRF_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class TRF : public RESPONSE
{

   public:

      TRF();
     ~TRF();

      /*
      ** Data
      */

      wxString          UTCTime;
      wxString          Date;
      LATLONG          Position;
      double           ElevationAngle;
      double           NumberOfIterations;
      double           NumberOfDopplerIntervals;
      double           UpdateDistanceNauticalMiles;
      double           SatelliteID;
      NMEA0183_BOOLEAN IsDataValid;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const TRF& operator = ( const TRF& source );
};

#endif // TRF_CLASS_HEADER

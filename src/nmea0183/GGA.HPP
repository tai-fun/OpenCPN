#if ! defined( GGA_CLASS_HEADER )
#define GGA_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class GGA : public RESPONSE
{

   public:

      GGA();
     ~GGA();

      /*
      ** Data
      */

      wxString          UTCTime;
      LATLONG          Position;
      int              GPSQuality;
      int              NumberOfSatellitesInUse;
      double           HorizontalDilutionOfPrecision;
      double           AntennaAltitudeMeters;
      double           GeoidalSeparationMeters;
      double           AgeOfDifferentialGPSDataSeconds;
      int              DifferentialReferenceStationID;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const GGA& GGA::operator = ( const GGA& source );
};

#endif // GGA_CLASS_HEADER

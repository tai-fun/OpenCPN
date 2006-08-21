#if ! defined( OSD_CLASS_HEADER )
#define OSD_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class OSD : public RESPONSE
{

   public:

      OSD();
     ~OSD();

      /*
      ** Data
      */

      double           HeadingDegreesTrue;
      NMEA0183_BOOLEAN IsHeadingValid;
      double           VesselCourseDegreesTrue;
      REFERENCE        VesselCourseReference;
      double           VesselSpeed;
      REFERENCE        VesselSpeedReference;
      double           VesselSetDegreesTrue;
      double           VesselDriftSpeed;
      wxString          VesselDriftSpeedUnits;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const OSD& operator = ( const OSD& source );
};

#endif // OSD_CLASS_HEADER

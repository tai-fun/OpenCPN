#if ! defined( GXA_CLASS_HEADER )
#define GXA_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class GXA : public RESPONSE
{

   public:

      GXA();
     ~GXA();

      /*
      ** Data
      */

      wxString UTCTime;
      LATLONG Position;
      wxString WaypointID;
      WORD    SatelliteNumber;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const GXA& operator = ( const GXA& source );
};

#endif // GXA_CLASS_HEADER

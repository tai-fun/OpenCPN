#if ! defined( VTG_CLASS_HEADER )
#define VTG_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class VTG : public RESPONSE
{

   public:

      VTG();
     ~VTG();

      /*
      ** Data
      */

      double TrackDegreesTrue;
      double TrackDegreesMagnetic;
	   double SpeedKnots;
	   double SpeedKilometersPerHour;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const VTG& operator = ( const VTG& source );
};

#endif // VTG_CLASS_HEADER

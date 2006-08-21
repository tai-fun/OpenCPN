#if ! defined( HDG_CLASS_HEADER )
#define HDG_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class HDG : public RESPONSE
{

   public:

      HDG();
     ~HDG();

      /*
      ** Data
      */

      double   MagneticSensorHeadingDegrees;
      double   MagneticDeviationDegrees;
      EASTWEST MagneticDeviationDirection;
      double   MagneticVariationDegrees;
      EASTWEST MagneticVariationDirection;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const HDG& operator = ( const HDG& source );
};

#endif // HDG_CLASS_HEADER

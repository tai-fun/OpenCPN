#if ! defined( VLW_CLASS_HEADER )
#define VLW_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class VLW : public RESPONSE
{

   public:

      VLW();
     ~VLW();

      /*
      ** Data
      */

      double TotalDistanceNauticalMiles;
      double DistanceSinceResetNauticalMiles;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const VLW& operator = ( const VLW& source );
};

#endif // VLW_CLASS_HEADER

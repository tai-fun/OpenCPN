#if ! defined( VPW_CLASS_HEADER )
#define VPW_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class VPW : public RESPONSE
{

   public:

      VPW();
     ~VPW();

      /*
      ** Data
      */

      double Knots;
      double MetersPerSecond;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const VPW& operator = ( const VPW& source );
};

#endif // VPW_CLASS_HEADER

#if ! defined( VDR_CLASS_HEADER )
#define VDR_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class VDR : public RESPONSE
{

   public:

      VDR();
     ~VDR();

      /*
      ** Data
      */

      double DegreesTrue;
      double DegreesMagnetic;
      double Knots;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const VDR& operator = ( const VDR& source );
};

#endif // VDR_CLASS_HEADER

#if ! defined( HSC_CLASS_HEADER )
#define HSC_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class HSC : public RESPONSE
{

   public:

      HSC();
     ~HSC();

      /*
      ** Data
      */

      double DegreesMagnetic;
      double DegreesTrue;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const HSC& operator = ( const HSC& source );
};

#endif // HSC_CLASS_HEADER

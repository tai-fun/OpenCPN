#if ! defined( HDM_CLASS_HEADER )
#define HDM_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class HDM : public RESPONSE
{

   public:

      HDM();
     ~HDM();

      /*
      ** Data
      */

     double DegreesMagnetic;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const HDM& operator = ( const HDM& source );
};

#endif // HDM_CLASS_HEADER

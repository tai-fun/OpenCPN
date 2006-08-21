#if ! defined( OLN_CLASS_HEADER )
#define OLN_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class OLN : public RESPONSE
{

   public:

      OLN();
     ~OLN();

      /*
      ** Data
      */

      OMEGA_PAIR Pair1;
      OMEGA_PAIR Pair2;
      OMEGA_PAIR Pair3;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const OLN& operator = ( const OLN& source );
};

#endif // OLN_CLASS_HEADER

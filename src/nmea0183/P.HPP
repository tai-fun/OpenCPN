#if ! defined( P_CLASS_HEADER )
#define P_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class P : public RESPONSE
{

   public:

      P();
     ~P();

      /*
      ** Data
      */

      wxString Sentence;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const P& operator = ( const P& source );
};

#endif // P_CLASS_HEADER

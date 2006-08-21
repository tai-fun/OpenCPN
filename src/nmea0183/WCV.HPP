#if ! defined( WCV_CLASS_HEADER )
#define WCV_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class WCV : public RESPONSE
{

   public:

      WCV();
     ~WCV();

      /*
      ** Data
      */

      double  Velocity;
      wxString To;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const WCV& operator = ( const WCV& source );
};

#endif // WCV_CLASS_HEADER

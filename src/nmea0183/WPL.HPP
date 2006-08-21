#if ! defined( WPL_CLASS_HEADER )
#define WPL_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class WPL : public RESPONSE
{

   public:

      WPL();
     ~WPL();

      /*
      ** Data
      */

      LATLONG Position;
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

      virtual const WPL& operator = ( const WPL& source );
};

#endif // WPL_CLASS_HEADER

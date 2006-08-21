#if ! defined( WNC_CLASS_HEADER )
#define WNC_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class WNC : public RESPONSE
{

   public:

      WNC();
     ~WNC();

      /*
      ** Data
      */

      double  MilesDistance;
      double  KilometersDistance;
      wxString To;
      wxString From;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const WNC& operator = ( const WNC& source );
};

#endif // WNC_CLASS_HEADER

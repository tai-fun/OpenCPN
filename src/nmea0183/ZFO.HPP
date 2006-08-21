#if ! defined( ZFO_CLASS_HEADER )
#define ZFO_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class ZFO : public RESPONSE
{

   public:

      ZFO();
     ~ZFO();

      /*
      ** Data
      */

      wxString UTCTime;
      wxString ElapsedTime;
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

      virtual const ZFO& operator = ( const ZFO& source );
};

#endif // ZFO_CLASS_HEADER

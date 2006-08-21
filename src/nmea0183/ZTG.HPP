#if ! defined( ZTG_CLASS_HEADER )
#define ZTG_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class ZTG : public RESPONSE
{

   public:

      ZTG();
     ~ZTG();

      /*
      ** Data
      */

      wxString UTCTime;
      wxString TimeRemaining;
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

      virtual const ZTG& operator = ( const ZTG& source );
};

#endif // ZTG_CLASS_HEADER

#if ! defined( MTW_CLASS_HEADER )
#define MTW_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class MTW : public RESPONSE
{

   public:

      MTW();
     ~MTW();

      /*
      ** Data
      */

      double  Temperature;
      wxString UnitOfMeasurement;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const MTW& operator = ( const MTW& source );
};

#endif // MTW_CLASS_HEADER

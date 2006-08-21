#if ! defined( BOD_CLASS_HEADER )
#define BOD_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class BOD : public RESPONSE
{

   public:

      BOD();
     ~BOD();

      /*
      ** Data
      */

      double  BearingTrue;
      double  BearingMagnetic;
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

      virtual const BOD& operator = ( const BOD& source );
};

#endif // BOD_CLASS_HEADER

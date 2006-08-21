#if ! defined( BWW_CLASS_HEADER )
#define BWW_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class BWW : public RESPONSE
{

   public:

      BWW();
     ~BWW();

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

      virtual const BWW& operator = ( const BWW& source );
};

#endif // BWW_CLASS_HEADER

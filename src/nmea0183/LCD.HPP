#if ! defined( LCD_CLASS_HEADER )
#define LCD_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class LCD : public RESPONSE
{

   public:

      LCD();
     ~LCD();

      /*
      ** Data
      */

      int             GRI;
      RATIO_AND_PULSE Master;
      RATIO_AND_PULSE Secondary1;
      RATIO_AND_PULSE Secondary2;
      RATIO_AND_PULSE Secondary3;
      RATIO_AND_PULSE Secondary4;
      RATIO_AND_PULSE Secondary5;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LCD& operator = ( const LCD& source );
};

#endif // LCD_CLASS_HEADER

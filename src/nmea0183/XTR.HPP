#if ! defined( XTR_CLASS_HEADER )
#define XTR_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class XTR : public RESPONSE
{

   public:

      XTR();
     ~XTR();

      /*
      ** Data
      */

      double    Magnitude;
      LEFTRIGHT DirectionToSteer;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const XTR& operator = ( const XTR& source );
};

#endif // XTR_CLASS_HEADER

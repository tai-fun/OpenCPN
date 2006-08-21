#if ! defined( ROT_CLASS_HEADER )
#define ROT_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class ROT : public RESPONSE
{

   public:

      ROT();
     ~ROT();

      /*
      ** Data
      */

      double           RateOfTurn;
      NMEA0183_BOOLEAN IsDataValid;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const ROT& operator = ( const ROT& source );
};

#endif // ROT_CLASS_HEADER

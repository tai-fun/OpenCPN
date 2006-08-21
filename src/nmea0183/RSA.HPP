#if ! defined( RSA_CLASS_HEADER )
#define RSA_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RSA : public RESPONSE
{

   public:

      RSA();
     ~RSA();

      /*
      ** Data
      */

      double           Starboard;
      NMEA0183_BOOLEAN IsStarboardDataValid;
      double           Port;
      NMEA0183_BOOLEAN IsPortDataValid;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const RSA& operator = ( const RSA& source );
};

#endif // RSA_CLASS_HEADER

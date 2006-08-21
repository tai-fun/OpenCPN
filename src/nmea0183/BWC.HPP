#if ! defined( BWC_CLASS_HEADER )
#define BWC_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class BWC : public RESPONSE
{

   public:

      BWC();
     ~BWC();

      /*
      ** Data
      */

      wxString UTCTime;
      double  BearingTrue;
      double  BearingMagnetic;
      double  NauticalMiles;
      wxString To;
      LATLONG Position;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      const BWC& operator = ( const BWC& source );
};

#endif // BWC_CLASS_HEADER

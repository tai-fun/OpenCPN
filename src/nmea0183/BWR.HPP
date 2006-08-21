#if ! defined( BWR_CLASS_HEADER )
#define BWR_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class BWR : public RESPONSE
{

   public:

      BWR();
     ~BWR();

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

      virtual const BWR& operator = ( const BWR& source );
};

#endif // BWR_CLASS_HEADER

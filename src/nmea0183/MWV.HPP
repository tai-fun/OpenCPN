#if ! defined( MWV_CLASS_HEADER )
#define MWV_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class MWV : public RESPONSE
{

   public:

      MWV();
     ~MWV();

      /*
      ** Data
      */

      double           WindAngle;
      wxString          Reference;
      double           WindSpeed;
      wxString          WindSpeedUnits;
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

      virtual const MWV& operator = ( const MWV& source );
};

#endif // MWV_CLASS_HEADER

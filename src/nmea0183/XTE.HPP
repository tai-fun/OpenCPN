#if ! defined( XTE_CLASS_HEADER )
#define XTE_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class XTE : public RESPONSE
{

   public:

      XTE();
     ~XTE();

      /*
      ** Data
      */

      NMEA0183_BOOLEAN IsLoranBlinkOK;
      NMEA0183_BOOLEAN IsLoranCCycleLockOK;
      double           CrossTrackErrorMagnitude;
      LEFTRIGHT        DirectionToSteer;
      wxString          CrossTrackUnits;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const XTE& operator = ( const XTE& source );
};

#endif // XTE_CLASS_HEADER

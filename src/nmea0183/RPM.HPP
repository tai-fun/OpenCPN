#if ! defined( RPM_CLASS_HEADER )
#define RPM_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RPM : public RESPONSE
{

   public:

      RPM();
     ~RPM();

      /*
      ** Data
      */

      wxString          Source;
      int              SourceNumber;
      double           RevolutionsPerMinute;
      double           PropellerPitchPercentage;
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

      virtual const RPM& operator = ( const RPM& source );
};

#endif // RPM_CLASS_HEADER

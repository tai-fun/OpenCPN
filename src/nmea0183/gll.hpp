#if ! defined( GLL_CLASS_HEADER )
#define GLL_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class GLL : public RESPONSE
{

   public:

      GLL();
     ~GLL();

      /*
      ** Data
      */

      wxString          UTCTime;
      NMEA0183_BOOLEAN IsDataValid;
      LATLONG          Position;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual const wxString& PlainEnglish( void );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const GLL& operator = ( const GLL& source );
};

#endif // GLL_CLASS_HEADER

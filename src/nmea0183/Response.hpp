#if ! defined( RESPONSE_CLASS_HEADER )
#define RESPONSE_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class NMEA0183;

class RESPONSE 
{

   private:

      NMEA0183 *container_p;

   public:

      RESPONSE();
      virtual ~RESPONSE();

      /*
      ** Data
      */

      wxString ErrorMessage;
      wxString Mnemonic;
      wxString Talker;

      /*
      ** Methods
      */

      virtual void Empty( void ) = 0;
      virtual bool Parse( const SENTENCE& sentence ) = 0;
      virtual const wxString& PlainEnglish( void );
      virtual void SetErrorMessage( const wxString& );
      virtual void SetContainer( NMEA0183 *container );
      virtual bool Write( SENTENCE& sentence );
};


 
#endif // RESPONSE_CLASS_HEADER

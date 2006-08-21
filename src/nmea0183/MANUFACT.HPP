#if ! defined( MANUFACTURER_CLASS_HEADER )
#define MANUFACTURER_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class MANUFACTURER 
{

   public:

      MANUFACTURER();
      MANUFACTURER( const char *mnemonic, const char *company_name );
     ~MANUFACTURER();

      wxString Mnemonic;
      wxString CompanyName;
};

#endif // MANUFACTURER_CLASS_HEADER    

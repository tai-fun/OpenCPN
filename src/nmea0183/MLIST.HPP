#if ! defined( MANUFACTURER_LIST_CLASS_HEADER )
#define MANUFACTURER_LIST_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class MANUFACTURER_LIST
{

   public:

      MANUFACTURER_LIST();
     ~MANUFACTURER_LIST();

      /*
      ** Data
      */

//      CObArray ManufacturerTable;

      /*
      ** Methods
      */

      virtual void Add( MANUFACTURER *manufacturer_p );
      virtual void Fill( void );
      virtual const wxString& Find( const wxString& mnemonic );
      virtual void Sort( void );

      /*
      ** Operators
      */

      virtual const wxString& operator [] ( const char *mnemonic );
};

#endif // MANUFACTURER_LIST_CLASS_HEADER    

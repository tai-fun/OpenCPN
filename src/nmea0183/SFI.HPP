#if ! defined( SFI_CLASS_HEADER )
#define SFI_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class SFI : public RESPONSE
{

   public:

      SFI();
     ~SFI();

      /*
      ** Data
      */
       
      double             TotalMessages;
      double             MessageNumber;
      FREQUENCY_AND_MODE Frequencies[ 6 ];

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const SFI& operator = ( const SFI& source );
};

#endif // SFI_CLASS_HEADER

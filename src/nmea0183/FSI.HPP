#if ! defined( FSI_CLASS_HEADER )
#define FSI_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class FSI : public RESPONSE
{

   public:

      FSI();
     ~FSI();

      /*
      ** Data
      */

      double              TransmittingFrequency;
      double              ReceivingFrequency;
      COMMUNICATIONS_MODE Mode;
      short               PowerLevel;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const FSI& operator = ( const FSI& source );
};

#endif // FSI_CLASS_HEADER

#if ! defined( FREQUENCY_AND_MODE_CLASS_HEADER )
#define FREQUENCY_AND_MODE_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class FREQUENCY_AND_MODE 
{


   public:

      FREQUENCY_AND_MODE();
     ~FREQUENCY_AND_MODE();

      /*
      ** Data
      */

      double              Frequency;
      COMMUNICATIONS_MODE Mode;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual void Parse( int field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const FREQUENCY_AND_MODE& FREQUENCY_AND_MODE::operator = ( const FREQUENCY_AND_MODE& source );
};

#endif // FREQUENCY_AND_MODE_CLASS_HEADER

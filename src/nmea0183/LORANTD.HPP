#if ! defined( LORAN_TIME_DIFFERENCE_CLASS_HEADER )
#define LORAN_TIME_DIFFERENCE_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

typedef enum
{
   LoranUnknown = 0,
   LoranValid,
   LoranBlinkWarning,
   LoranCycleWarning,
   LoranSNRWarning
}
LORAN_SIGNAL_STATUS;

class LORAN_TIME_DIFFERENCE 
{

   public:

      LORAN_TIME_DIFFERENCE();
     ~LORAN_TIME_DIFFERENCE();

      /*
      ** Data
      */

      double              Microseconds;
      LORAN_SIGNAL_STATUS SignalStatus;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual void Parse( int field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LORAN_TIME_DIFFERENCE& LORAN_TIME_DIFFERENCE::operator = ( const LORAN_TIME_DIFFERENCE& source );
};

#endif // LORAN_TIME_DIFFERENCE_CLASS_HEADER

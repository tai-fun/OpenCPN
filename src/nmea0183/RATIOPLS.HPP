#if ! defined( RATIO_AND_PULSE_CLASS_HEADER )
#define RATIO_AND_PULSE_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RATIO_AND_PULSE 
{


   public:

      RATIO_AND_PULSE();
     ~RATIO_AND_PULSE();

      /*
      ** Data
      */

      int SignalToNoiseRatio;
      int PulseShapeECD;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual void Parse( int field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const RATIO_AND_PULSE& operator = ( const RATIO_AND_PULSE& source );
};

#endif // RATIO_AND_PULSE_CLASS_HEADER

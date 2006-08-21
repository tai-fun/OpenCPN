#if ! defined( VHW_CLASS_HEADER )
#define VHW_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class VHW : public RESPONSE
{

   public:

      VHW();
     ~VHW();

      /*
      ** Data
      */

      double DegreesTrue;
      double DegreesMagnetic;
      double Knots;
      double KilometersPerHour;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const VHW& operator = ( const VHW& source );
};

#endif // VHW_CLASS_HEADER

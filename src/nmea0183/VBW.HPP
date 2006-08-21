#if ! defined( VBW_CLASS_HEADER )
#define VBW_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class VBW : public RESPONSE
{

   public:

      VBW();
     ~VBW();

      /*
      ** Data
      */

      double           LongitudinalWaterSpeed;
      double           TransverseWaterSpeed;
      NMEA0183_BOOLEAN IsWaterSpeedValid;
      double           LongitudinalGroundSpeed;
      double           TransverseGroundSpeed;
      NMEA0183_BOOLEAN IsGroundSpeedValid;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const VBW& operator = ( const VBW& source );
};

#endif // VBW_CLASS_HEADER

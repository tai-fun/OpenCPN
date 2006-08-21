#if ! defined( DCN_CLASS_HEADER )
#define DCN_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

typedef enum
{
   BasisUnknown = 0,
   NormalPatternBasis,
   LaneIdentificationPatternBasis,
   LaneIdentificationTransmissionsBasis
}
FIX_DATA_BASIS;

class DCN : public RESPONSE
{

   public:

      DCN();
     ~DCN();

      /*
      ** Data
      */

      int              DeccaChainID;
      LINE_OF_POSITION Red;
      LINE_OF_POSITION Green;
      LINE_OF_POSITION Purple;
      NMEA0183_BOOLEAN RedLineNavigationUse;
      NMEA0183_BOOLEAN GreenLineNavigationUse;
      NMEA0183_BOOLEAN PurpleLineNavigationUse;
      double           PositionUncertaintyNauticalMiles;
      FIX_DATA_BASIS   Basis;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const DCN& operator = ( const DCN& source );
};

#endif // DCN_CLASS_HEADER

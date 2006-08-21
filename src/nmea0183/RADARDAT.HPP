#if ! defined( RADAR_DATA_CLASS_HEADER )
#define RADAR_DATA_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class RADAR_DATA 
{


   public:

      RADAR_DATA();
     ~RADAR_DATA();

      /*
      ** Data
      */

      double OriginRangeFromOwnShip;
      double OriginBearingDegreesFromZero;
      double VariableRangeMarkerRange;
      double BearingLineDegreesFromZero;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual void Parse( int field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const RADAR_DATA& operator = ( const RADAR_DATA& source );
};

#endif // RADAR_DATA_CLASS_HEADER

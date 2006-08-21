#if ! defined( RSD_CLASS_HEADER )
#define RSD_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

typedef enum
{
   RotationUnknown = 0,
   CourseUpRotation,
   HeadUpRotation,
   NorthUpRotation
}
ROTATION;

class RSD : public RESPONSE
{

   public:

      RSD();
     ~RSD();

      /*
      ** Data
      */

      RADAR_DATA Data1;
      RADAR_DATA Data2;
      double     CursorRangeFromOwnShip;
      double     CursorBearingDegreesClockwiseFromZero;
      double     RangeScale;
      wxString    RangeUnits;
      ROTATION   DisplayRotation;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const RSD& operator = ( const RSD& source );
};

#endif // RSD_CLASS_HEADER

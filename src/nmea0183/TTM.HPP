#if ! defined( TTM_CLASS_HEADER )
#define TTM_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

typedef enum
{
   TargetUnknown = 0,
   TargetLost,
   TargetQuery,
   TargetTracking
}
TARGET_STATUS;

class TTM : public RESPONSE
{

   public:

      TTM();
     ~TTM();

      /*
      ** Data
      */

      int           TargetNumber;
      double        TargetDistance;
      double        BearingFromOwnShip;
      wxString       BearingUnits;
      double        TargetSpeed;
      double        TargetCourse;
      wxString       TargetCourseUnits;
      double        DistanceOfClosestPointOfApproach;
      double        NumberOfMinutesToClosestPointOfApproach;
      wxString       Increasing;
      wxString       TargetName;
      TARGET_STATUS TargetStatus;
      wxString       ReferenceTarget;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const TTM& operator = ( const TTM& source );
};

#endif // TTM_CLASS_HEADER

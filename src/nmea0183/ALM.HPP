#if ! defined( ALM_CLASS_HEADER )
#define ALM_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class ALM : public RESPONSE
{

   public:

      ALM();
     ~ALM();

      /*
      ** Data
      */

      int  NumberOfMessages;
      int  MessageNumber;
      int  PRNNumber;
      int  WeekNumber;
      int  SVHealth;
      int  Eccentricity;
      int  AlmanacReferenceTime;
      int  InclinationAngle;
      int  RateOfRightAscension;
      int RootOfSemiMajorAxis;
      int ArgumentOfPerigee;
      int LongitudeOfAscensionNode;
      int MeanAnomaly;
      int  F0ClockParameter;
      int  F1ClockParameter;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      const ALM& operator = ( const ALM& source );
};

#endif // ALM_CLASS_HEADER

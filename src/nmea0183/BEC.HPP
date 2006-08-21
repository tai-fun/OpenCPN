#if ! defined( BEC_CLASS_HEADER )
#define BEC_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class BEC : public RESPONSE
{


   public:

      BEC();
     ~BEC();

      /*
      ** Data
      */

      wxString UTCTime;
      LATLONG Position;
      double  BearingTrue;
      double  BearingMagnetic;
      double  DistanceNauticalMiles;
      wxString To;

      /*
      ** Methods
      */
       
      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      const BEC& operator = ( const BEC& source );
};

#endif // BEC_CLASS_HEADER

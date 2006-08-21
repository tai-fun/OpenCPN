#if ! defined( GLC_CLASS_HEADER )
#define GLC_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class GLC : public RESPONSE
{

   public:

      GLC();
     ~GLC();

      /*
      ** Data
      */
       
      int                   GRI;
      LORAN_TIME_DIFFERENCE MasterTOA;
      LORAN_TIME_DIFFERENCE TimeDifference1;
      LORAN_TIME_DIFFERENCE TimeDifference2;
      LORAN_TIME_DIFFERENCE TimeDifference3;
      LORAN_TIME_DIFFERENCE TimeDifference4;
      LORAN_TIME_DIFFERENCE TimeDifference5;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const GLC& operator = ( const GLC& source );
};

#endif // GLC_CLASS_HEADER

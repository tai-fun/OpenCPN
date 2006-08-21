#if ! defined( ZDA_CLASS_HEADER )
#define ZDA_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class ZDA : public RESPONSE
{

   public:

      ZDA();
     ~ZDA();

      /*
      ** Data
      */

      wxString UTCTime;
      int     Day;
      int     Month;
      int     Year;
      int     LocalHourDeviation;
      int     LocalMinutesDeviation;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const ZDA& operator = ( const ZDA& source );
};

#endif // ZDA_CLASS_HEADER

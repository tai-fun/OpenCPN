#if ! defined( DBT_CLASS_HEADER )
#define DBT_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class DBT : public RESPONSE
{

   public:

      DBT();
     ~DBT();

      /*
      ** Data
      */

      double DepthFeet;
      double DepthMeters;
      double DepthFathoms;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      const DBT& operator = ( const DBT& source );
};

#endif // DBT_CLASS_HEADER

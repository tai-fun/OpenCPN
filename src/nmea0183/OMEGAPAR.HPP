#if ! defined( OMEGA_PAIR_CLASS_HEADER )
#define OMEGA_PAIR_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class OMEGA_PAIR
{

   public:

      OMEGA_PAIR();
     ~OMEGA_PAIR();

      /*
      ** Data
      */

      wxString Name;
      int     LaneNumber;
      int     CentilaneNumber;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual void Parse( int field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const OMEGA_PAIR& operator = ( const OMEGA_PAIR& source );
};

#endif // OMEGA_PAIR_CLASS_HEADER

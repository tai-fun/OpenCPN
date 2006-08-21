#if ! defined( LINE_OF_POSITION_CLASS_HEADER )
#define LINE_OF_POSITION_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class LINE_OF_POSITION 
{

   public:

      LINE_OF_POSITION();
     ~LINE_OF_POSITION();

      /*
      ** Data
      */

      wxString          ZoneID;
      double           LineOfPosition;
      NMEA0183_BOOLEAN MasterLine;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual void Parse( int field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LINE_OF_POSITION& operator = ( const LINE_OF_POSITION& source );
};

#endif // LINE_OF_POSITION_CLASS_HEADER

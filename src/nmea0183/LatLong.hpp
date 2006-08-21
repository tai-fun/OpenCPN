#if ! defined( LATLONG_CLASS_HEADER )
#define LATLONG_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class SENTENCE;

class LATITUDE 
{

   public:

      LATITUDE();
      virtual ~LATITUDE();

      /*
      ** Data
      */

      double Latitude;

      NORTHSOUTH Northing;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool IsDataValid( void );
      virtual void Parse( int PositionFieldNumber, int NorthingFieldNumber, const SENTENCE& LineToParse );
      virtual void Set( double Position, const char *Northing );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LATITUDE& operator = ( const LATITUDE& source );
};

class LONGITUDE 
{

   public:

      LONGITUDE();
      virtual ~LONGITUDE();

      /*
      ** Data
      */

      double Longitude;

      EASTWEST Easting;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual bool IsDataValid( void );
      virtual void Parse( int PositionFieldNumber, int EastingFieldNumber, const SENTENCE& LineToParse );
      virtual void Set( double Position, const char *Easting );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LONGITUDE& operator = ( const LONGITUDE& source );
};

class LATLONG 
{

   public:

      LATLONG();
      virtual ~LATLONG();

      /*
      ** Data
      */

      LATITUDE  Latitude;
      LONGITUDE Longitude;

      /*
      ** Methods
      */
       
      virtual void Empty( void );
      virtual bool Parse( int LatitudePostionFieldNumber, int NorthingFieldNumber, int LongitudePositionFieldNumber, int EastingFieldNumber, const SENTENCE& LineToParse );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const LATLONG& operator = ( const LATLONG& source );
};

#endif // LATLONG_CLASS_HEADER

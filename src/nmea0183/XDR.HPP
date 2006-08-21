#if ! defined( XDR_CLASS_HEADER )
#define XDR_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class TRANSDUCER_DATA 
{

   public:

      TRANSDUCER_DATA();
	  ~TRANSDUCER_DATA();

	   /*
      ** Data
      */

	   TRANSDUCER_TYPE TransducerType;
	   double          MeasurementData;
	   wxString         MeasurementUnits;
	   wxString         TransducerName;

	   /*
      ** Methods
      */

      virtual void Empty( void );
	   virtual void Parse( int first_field_number, const SENTENCE& sentence );
      virtual void Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const TRANSDUCER_DATA& operator = ( const TRANSDUCER_DATA& source );
};

class XDR : public RESPONSE
{

   private:

      void delete_all_entries( void );

   public:

      XDR();
     ~XDR();

//      CObArray Transducers;

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );
};

#endif // XDR_CLASS_HEADER

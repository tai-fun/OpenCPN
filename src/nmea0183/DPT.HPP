#if ! defined( DPT_CLASS_HEADER )
#define DPT_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class DPT : public RESPONSE
{

   public:

      DPT();
     ~DPT();

      /*
      ** Data
      */

      double DepthMeters;
      double OffsetFromTransducerMeters;

      /*
      ** Methods
      */

      virtual void Empty( void );
      virtual BOOL Parse( const SENTENCE& sentence );
      virtual BOOL Write( SENTENCE& sentence );

      /*
      ** Operators
      */

      virtual const DPT& operator = ( const DPT& source );
};

#endif // DPT_CLASS_HEADER

#if ! defined( ASD_CLASS_HEADER )
#define ASD_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

class ASD : public RESPONSE
{


   public:

      ASD();
     ~ASD();

      virtual void Empty( void );
      virtual bool Parse( const SENTENCE& sentence );
      virtual bool Write( SENTENCE& sentence );
};

#endif // ASD_CLASS_HEADER

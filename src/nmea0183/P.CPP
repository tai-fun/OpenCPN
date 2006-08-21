#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( P, RESPONSE )

P::P()
{
   Mnemonic = "P";
   Empty();
}

P::~P()
{
   Mnemonic.Empty();
   Empty();
}

void P::Empty( void )
{
   ASSERT_VALID( this );

   Sentence.Empty();
}

BOOL P::Parse( const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** This is where parsing of proprietary sentences will go...
   */

   Sentence = sentence;

   return( TRUE );
}

BOOL P::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   /*
   ** Let the parent do its thing
   */
   
   RESPONSE::Write( sentence );

   sentence += Sentence;

   sentence.Finish();

   return( TRUE );
}

const P& P::operator = ( const P& source )
{
   ASSERT_VALID( this );

   Sentence = source.Sentence;

   return( *this );
}

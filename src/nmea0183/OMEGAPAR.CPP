#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( OMEGA_PAIR, CObject )

OMEGA_PAIR::OMEGA_PAIR()
{
   Empty();
}

OMEGA_PAIR::~OMEGA_PAIR()
{
   Empty();
}

void OMEGA_PAIR::Empty( void )
{
   ASSERT_VALID( this );

   Name.Empty();
   LaneNumber      = 0;
   CentilaneNumber = 0;
}

void OMEGA_PAIR::Parse( int first_field_number, const SENTENCE& sentence )
{
   ASSERT_VALID( this );

   Name            = sentence.Field( first_field_number );
   LaneNumber      = sentence.Integer( first_field_number + 1 );
   CentilaneNumber = sentence.Integer( first_field_number + 2 );
}

void OMEGA_PAIR::Write( SENTENCE& sentence )
{
   ASSERT_VALID( this );

   sentence += Name;
   sentence += LaneNumber;
   sentence += CentilaneNumber;
}

const OMEGA_PAIR& OMEGA_PAIR::operator = ( const OMEGA_PAIR& source )
{
   ASSERT_VALID( this );

   Name            = source.Name;
   LaneNumber      = source.LaneNumber;
   CentilaneNumber = source.CentilaneNumber;

   return( *this );
}

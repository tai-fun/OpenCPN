#include "nmea0183.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

IMPLEMENT_DYNAMIC( MANUFACTURER, CObject );

MANUFACTURER::MANUFACTURER()
{
   Mnemonic.Empty();
   CompanyName.Empty();
}

MANUFACTURER::MANUFACTURER( const char *mnemonic, const char *company_name )
{
   Mnemonic    = mnemonic;
   CompanyName = company_name;
}

MANUFACTURER::~MANUFACTURER()
{
   Mnemonic.Empty();
   CompanyName.Empty();
}

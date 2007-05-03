//----------------------------------------------------------------------------------
//          Global Build options for opencpn
//----------------------------------------------------------------------------------

#ifndef _DYCHART_H_
#define _DYCHART_H_


//  Chart cacheing policy
//  n.b. use only one of the following policy options....
#define CACHE_N_LIMIT 3                                     // Cache no more than n charts
//#define CACHE_MEM_LIMIT 60000                             // Free mem threshold for freeing a chart from cache


//          MSWindows Autopilot Control output through Serial Comm Port
#define     ocpnUSE_MSW_SERCOMM           1


// Optional
//  Some build environments may need root privileges for hardware
//  port I/O, such as is needed by the raw NMEA data input class.
//  Enable opencpn temporary root privileges via seteuid() function here.
//  And don't forget to make opencpn binary executable file "+SUID".
//#define dyUSE_EUID 1

//          Auto save config file occasionally during run
//          protecting against inadvertant crash....
//          Set in minutes.
#define AUTO_CONFIG_SAVE_MINUTES 5


//          If defined, update the system time using GPS receiver data.
//          Time update is applied if the system time and GPS time differ
//          by more than one minute, and only once per session.
//          On Linux, this option requires root privileges, obtained by sudo.
//          Thus, the following line is required in etc/sudoers:
//
//              nav ALL=NOPASSWD:/bin/date -s *
//
//          Where "nav" is the user's user name.
//
//          Also, the opencpn configuration file must contain the key
//          [Settings]
//              SetSystemTime=1
//          For security, this option is not available on the "Options" dialog
#define ocpnUPDATE_SYSTEM_TIME


//------------------------------------------------------------------------------
//          Some private, app global type definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//          Various compile time options
//------------------------------------------------------------------------------

#ifdef __MSVC__
#pragma warning(disable:4114)
#pragma warning(disable:4284)             // This one is to do with "reverse iterator UDT..." Huh?


#endif

//    Following definition required by GDAL
#define notdef 1

//------------------------------------------------------------------------------
// Some Portable math definitions
//------------------------------------------------------------------------------

//    Floating Point Max/Min

#ifndef __max
      #define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#ifndef __min
      #define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif

#ifdef __WXMSW__
      #define fmin __min
      #define fmax __max

//      #define round(x) floor(x)
#endif

#define round(x) round_msvc(x)
//------------------------------------------------------------------------------
//          Some Build constants
//------------------------------------------------------------------------------

//    Home Base, used if the config file lat/lon seems bogus or missing


//#define START_LAT   35.1025              // New Bern (Ver 1.0)
//#define START_LON  -77.0342

#define START_LAT   26.783               // Green Turtle Key  (Ver 1.2)
#define START_LON  -77.333

//------------------------------------------------------------------------------
//          Some MSW and MSVCRT Specific Includes
//------------------------------------------------------------------------------
#ifdef __WXMSW__
    #include "wx/msw/private.h"
#endif

//------------------------------------------------------------------------------
//          Some Memory Leak Detection Code
//------------------------------------------------------------------------------



#ifdef __MSVC__
        #ifdef _DEBUG
            #define _CRTDBG_MAP_ALLOC
            #include <crtdbg.h>
            #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__ )
            #define new DEBUG_NEW
        #endif
#endif

//----------------------------------------------------------------------------
//		Environment Access functions
//----------------------------------------------------------------------------
#ifdef __MSVC__
#define _putenv _putenv		// This is for MSVC
#else
#define _putenv putenv		// This is for other Windows compiler
#endif

//----------------------------------------------------------------------------
//              Use and compile for S57 ENCs?
//----------------------------------------------------------------------------
//      Linux ./configure utility defines USE_S57 by default

//----------------------------------------------------------------------------
//              Use the CPL Portability library only if S57 is enabled
//----------------------------------------------------------------------------

#ifdef USE_S57
#define USE_CPL
#include "cpl_port.h"
#endif

//      Fix up CPL_CVSID if not available
//      This code block taken directly from <cpl_port.h>
#ifndef CPL_CVSID
#ifndef NULL
#define NULL 0
#endif

/***********************************************************************
 * Define CPL_CVSID() macro.  It can be disabled during a build by
 * defining DISABLE_CPLID in the compiler options.
 *
 * The cvsid_aw() function is just there to prevent reports of cpl_cvsid()
 * being unused.
 */

#ifndef DISABLE_CVSID
#  define CPL_CVSID(string)     static char cpl_cvsid[] = string; \
static char *cvsid_aw() { return( cvsid_aw() ? ((char *) NULL) : cpl_cvsid ); }
#else
#  define CPL_CVSID(string)
#endif

#endif


#endif      // __FILE__

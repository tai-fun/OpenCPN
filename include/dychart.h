//----------------------------------------------------------------------------------
//          Global Build options for opencpn
//----------------------------------------------------------------------------------

#ifndef _DYCHART_H_
#define _DYCHART_H_


//  Chart cacheing policy
//  n.b. use only one of the following policy options....
#define CACHE_N_LIMIT 3                                     // Cache no more than n charts
//#define CACHE_MEM_LIMIT 60000                             // Free mem threshold for freeing a chart from cache


//          Specify the Pixel Cache type
//          Only one of the following must be selected
//          with due regard for the system type

//#define __PIX_CACHE_WXIMAGE__                               // a safe default
//#define __PIX_CACHE_DIBSECTION__                            // for MSW
//#define __PIX_CACHE_X11IMAGE__                              // for X11/Universal, requires dyUSE_BITMAPO
//#define __PIX_CACHE_BMO__                                   // Bitmapo raw, goes to X11 Pixmap

//  I use these shortcuts....
#ifdef __WXX11__
#define     __PIX_CACHE_X11IMAGE__
#define     dyUSE_BITMAPO     1
#define     S57USE_PIXELCACHE 1
#define     dyUSE_BITMAPO_S57 1
#endif

#ifdef __WXGTK__
#define __PIX_CACHE_WXIMAGE__
#endif

#ifdef __WXMSW__
#define __PIX_CACHE_DIBSECTION__
#define     dyUSE_DIBSECTION
#define     dyUSE_BITMAPO     1
#define     dyUSE_BITMAPO_S57 1
//#define     S57USE_PIXELCACHE 1
#endif



//          Use Bitmapo (Optimized wxBitmap)
//          Required for X11 native systems and __PIX_CACHE_BMO__, optional on MSW

#ifdef      __PIX_CACHE_X11IMAGE__
#define     dyUSE_BITMAPO     1
#define     dyUSE_BITMAPO_S57 1
#endif

#ifdef      __PIX_CACHE_BMO__
#define     dyUSE_BITMAPO     1
#define     dyUSE_BITMAPO_S57 1
#endif


//          For Optimized X11 systems, use MIT shared memory XImage, requires dyUSE_BITMAPO
#ifdef __PIX_CACHE_X11IMAGE__
#define ocpUSE_MITSHM
#endif


//          The BitsPerPixel value for chart data storage
//          Todo get this during pixcache ctor
#ifdef __PIX_CACHE_WXIMAGE__                               // a safe default
      #define BPP 24
#endif
#ifdef __PIX_CACHE_DIBSECTION__                            // for MSW
      #define BPP 24
#endif
#ifdef __PIX_CACHE_X11IMAGE__                              // for X11/Universal
      #define BPP 32
#endif
#ifdef __PIX_CACHE_BMO__                                   // Bitmapo raw, goes to X11 Pixmap
      #define BPP 24
#endif


//          MSWindows Autopilot Control output through Serial Comm Port
#define     dyUSE_MSW_SERCOMM           1


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



//------------------------------------------------------------------------------
//          Some private, app global tye definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//          Various compile time options
//------------------------------------------------------------------------------

#ifdef __WXMSW__
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
#endif

//------------------------------------------------------------------------------
//          Some Build constants
//------------------------------------------------------------------------------

//    Home Base, used if the config file lat/lon seems bogus or missing


#define START_LAT  36.4
#define START_LON  -76.00

//------------------------------------------------------------------------------
//          Some MSW and MSVCRT Specific Includes
//------------------------------------------------------------------------------
#ifdef __WXMSW__
    #include "wx/msw/private.h"
#endif

//------------------------------------------------------------------------------
//          Some Memory Leak Detection Code
//------------------------------------------------------------------------------



#ifdef __WXMSW__
        #ifdef _DEBUG
            #define _CRTDBG_MAP_ALLOC
            #include <crtdbg.h>
            #define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__ )
            #define new DEBUG_NEW
        #endif
#endif



//----------------------------------------------------------------------------
//              Use and compile for S57 ENCs?
//----------------------------------------------------------------------------
//      Linux ./configure utility defines USE_S57 by default
//#define USE_S57

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

#ifndef __CPL_CONFIG__
#define __CPL_CONFIG__

/* Define if you don't have vprintf but do have _doprnt.  */
#undef HAVE_DOPRNT

/* Define if you have the vprintf function.  */
/* Note that some are predefined by wxWidgets	*/

#define HAVE_VPRINTF

#ifndef HAVE_VSNPRINTF
//DSR ....comment for MSW #define HAVE_VSNPRINTF
#endif

//DSR ....comment for MSW #define HAVE_SNPRINTF
//#define vsnprintf _vsnprintf
#ifdef __WXMSW__
	#define snprintf _snprintf
#endif

/* Define if you have the ANSI C header files.  */
#ifndef STDC_HEADERS
#  define STDC_HEADERS
#endif

/* Define if you have the <fcntl.h> header file.  */
#undef HAVE_FCNTL_H

/* Define if you have the <unistd.h> header file.  */
#undef HAVE_UNISTD_H

/* Define if you have the <stdint.h> header file.  */
#undef HAVE_STDINT_H

#undef HAVE_LIBDL 

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `localtime_r' function. */
#undef HAVE_LOCALTIME_R

#undef HAVE_DLFCN_H
#undef HAVE_DBMALLOC_H
#undef HAVE_LIBDBMALLOC
#undef WORDS_BIGENDIAN

/* #define CPL_DISABLE_DLL */


//	MSW doesn't do getenv properly.
//	getenv() is needed by GDAL, so...
//	Replacement function is in s57mgr.cpp
#ifdef __WXMSW__
#ifndef __MYGETENV__
#define __MYGETENV__
#define getenv mygetenv

#endif
#endif	//__WXMSW__

#endif

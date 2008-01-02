/****************************************************************************/
/*                                                                          */
/*                                                                          */
/* Parts of this file have been extracted from gpstrans                     */
/* Parts are taken from John F. Waers (jfwaers@csn.net) program MacGPS.     */
/*                                                                          */
/*                                                                          */
/*    Copyright (c) 1995 by Carsten Tschach (tschach@zedat.fu-berlin.de)    */
/*                                                                          */
/* Permission  to use, copy,  modify, and distribute  this software and its */
/* documentation for non-commercial purpose, is hereby granted without fee, */
/* providing that the  copyright notice  appear in all copies and that both */
/* the  copyright notice and  this permission  notice appear in  supporting */
/* documentation.  I make no representations about  the suitability of this */
/* software  for any  purpose.  It is  provides "as is" without  express or */
/* implid warranty.                                                         */
/*                                                                          */
/****************************************************************************/

#ifndef     __GEOREF_H__
#define __GEOREF_H__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//------------------------
struct DATUM {
        char *name;
        short ellipsoid;
        double dx;
        double dy;
        double dz;
};

struct ELLIPSOID {
        char *name;             // name of ellipsoid
        double a;               // semi-major axis, meters
        double invf;            // 1/f
};

struct GeoRef {
  int status;
  int count;
  int order;
  double *tx;
  double *ty;
  double *lon;
  double *lat;
  double *pwx;
  double *pwy;
  double *wpx;
  double *wpy;
  int    txmax;
  int    tymax;
  int    txmin;
  int    tymin;
  double lonmax;
  double lonmin;
  double latmax;
  double latmin;

};


#ifndef PI
      #define PI        3.1415926535897931160E0      /* pi */
#endif
#define DEGREE    (PI/180.0)
#define RADIAN    (180.0/PI)


void datumParams(short datum, double *a, double *es);


//      Make these conversion routines useable by C or C++


#ifdef __cplusplus
extern "C" void toDMS(double a, char *bufp, int bufplen);
extern "C" void toDMM(double a, char *bufp, int bufplen);

extern "C" void toTM(float lat, float lon, float lat0, float lon0, double *x, double *y);
extern "C" void fromTM(double x, double y, double lat0, double lon0, double *lat, double *lon);

extern "C" void toSM(float lat, float lon, float lat0, float lon0, double *x, double *y);
extern "C" void fromSM(double x, double y, double lat0, double lon0, double *lat, double *lon);

extern "C" void ll_gc_ll(double lat, double lon, double crs, double dist, double *dlat, double *dlon);


#else
void toDMS(double a, char *bufp, int bufplen);
void toDMM(double a, char *bufp, int bufplen);
#endif

double fromDMM(char *dms);
double fromDMS(char *dms);


#ifdef __cplusplus
extern "C" int Georef_Calculate_Coefficients(struct GeoRef *cp);
#endif





//--------------------

/*
 * lmfit
 *
 * Solves or minimizes the sum of squares of m nonlinear
 * functions of n variables.
 *
 * From public domain Fortran version
 * of Argonne National Laboratories MINPACK
 *     argonne national laboratory. minpack project. march 1980.
 *     burton s. garbow, kenneth e. hillstrom, jorge j. more
 * C translation by Steve Moshier
 * Joachim Wuttke converted the source into C++ compatible ANSI style
 * and provided a simplified interface
 */

// parameters for calling the high-level interface lmfit
//   ( lmfit.c provides lm_initialize_control which sets default values ):
typedef struct {
    double ftol;       // relative error desired in the sum of squares.
    double xtol;       // relative error between last two approximations.
    double gtol;       // orthogonality desired between fvec and its derivs.
    double epsilon;    // step used to calculate the jacobian.
    double stepbound;  // initial bound to steps in the outer loop.
    double fnorm;      // norm of the residue vector fvec.
    int maxcall;       // maximum number of iterations.
    int nfev;          // actual number of iterations.
    int info;          // status of minimization.
} lm_control_type;


// the subroutine that calculates fvec:
typedef void (lm_evaluate_ftype) (
        double* par, int m_dat, double* fvec, void *data, int *info );
// default implementation therof, provided by lm_eval.c:
void lm_evaluate_default (
        double* par, int m_dat, double* fvec, void *data, int *info );

// the subroutine that informs about fit progress:
typedef void (lm_print_ftype) (
        int n_par, double* par, int m_dat, double* fvec, void *data,
    int iflag, int iter, int nfev );
// default implementation therof, provided by lm_eval.c:
void lm_print_default (
        int n_par, double* par, int m_dat, double* fvec, void *data,
    int iflag, int iter, int nfev );

// compact high-level interface:
void lm_initialize_control( lm_control_type *control );
void lm_minimize ( int m_dat, int n_par, double* par,
                   lm_evaluate_ftype *evaluate, lm_print_ftype *printout,
                   void *data, lm_control_type *control );
double lm_enorm( int, double* );

// low-level interface for full control:
void lm_lmdif( int m, int n, double* x, double* fvec, double ftol, double xtol,
               double gtol, int maxfev, double epsfcn, double* diag, int mode,
               double factor, int *info, int *nfev,
               double* fjac, int* ipvt, double* qtf,
               double* wa1, double* wa2, double* wa3, double* wa4,
               lm_evaluate_ftype *evaluate, lm_print_ftype *printout,
               void *data );


#ifndef _LMDIF
extern char *lm_infmsg[];
extern char *lm_shortmsg[];
#endif

//      This is an opaque (to lmfit) structure set up before the call to lmfit()
typedef struct {
    double* user_tx;
    double* user_ty;
    double* user_y;
    double (*user_func)( double user_tx_point, double user_ty_point, int n_par, double* par );
    int     print_flag;
    int     n_par;
} lm_data_type;



#endif

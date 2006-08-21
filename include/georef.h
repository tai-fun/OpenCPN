
/*
 *    Copyright  1996, 1997, 1998, 1999, 2000 by Remco Treffkorn
 *    Distributed under the terms of the Q Public License. Please see
 *    the included file LICENSE.
 *
 * This module is a mess as far as static buffers, should be a real pain
 * to fix...
 */

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
  double *e1;
  double *n1;
  double *n2;
  double *e2;
};

enum FORMAT {DMS, DMM, DDD, UTM};

#ifndef PI
      #define PI        3.1415926535897931160E0      /* pi */
#endif
#define DEGREE    (PI/180.0)
#define RADIAN    (180.0/PI)


int my_snprintf (char *str, size_t sz, const char *format, ...);

void datumParams(short datum, double *a, double *es);

void toUserFormat(int format, double a, char *bufp, int bufplen);
void toUserFormatLat(int format, double a, char *bufp, int bufplen);
void toUserFormatLon(int format, double a, char *bufp, int bufplen);

double fromUserFormat(int format, char *a);

void toRawLatDMM(double a, char *bufp, int bufplen);
void toRawLonDMM(double a, char *bufp, int bufplen);


//--------------------

#endif

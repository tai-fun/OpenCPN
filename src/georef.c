/*
 *    Copyright  1996, 1997, 1998, 1999, 2000 by Remco Treffkorn
 *    Distributed under the terms of the Q Public License. Please see
 *    the included file LICENSE.
 *
 * This module is a mess as far as static buffers, should be a real pain
 * to fix...
 */

//#include "dychart.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "georef.h"

void toDMS(double a, char *bufp, int bufplen);
static double fromDMS(char *dms);
void toDMM(double a, char *bufp, int bufplen);
static double fromDMM(char *dms);

//CPL_CVSID("$Id: georef.c,v 1.2 2006/10/07 03:50:27 dsr Exp $");

static char buf[20];
static char r[20];


void datumParams(short datum, double *a, double *es)
{
    extern struct DATUM const gDatum[];
    extern struct ELLIPSOID const gEllipsoid[];

    double f = 1.0 / gEllipsoid[gDatum[datum].ellipsoid].invf;    // flattening
    *es = 2 * f - f * f;      // eccentricity^2
    *a = gEllipsoid[gDatum[datum].ellipsoid].a;       // semimajor axis
}

double fromUserFormat(int format, char *a)
{
    double d;

    switch (format) {
    case DMS:
      return fromDMS(a);

    case DMM:
      return fromDMM(a);

    case DDD:
      sscanf(a, "%lf", &d);
      return d;

    default:
//    error("Illegal Conversion attempt!\nPlease report.\n", 0);
      return (double) 0.0;
    }
}

void toUserFormatLat(int format, double a, char *bufp, int bufplen)
{
    char *p = "N";

    if (a < 0) {
      p = "S";
      a = -a;
    }
    /* Leave 1 for N/S, 1 for - */
    toUserFormat(format, a, bufp, bufplen-2);
    strcat(bufp, p);
    return;
}

void toUserFormatLon(int format, double a, char *bufp, int bufplen)
{
    char *p = "E";

    if (a < 0) {
      p = "W";
      a = -a;
    }
    /* Leave 1 for N/S, 1 for - */
    toUserFormat(format, a, bufp, bufplen-2);
    strcat(bufp, p);
    return;
}

void toUserFormat(int format, double a, char *bufp, int bufplen)
{
    switch (format) {
    case DMS:
      toDMS(a, bufp, bufplen);
      break;

    case DMM:
    default:
      toDMM(a, bufp, bufplen);
      break;

    case DDD:
      my_snprintf(bufp, (bufplen-1), "%.5lf", a);
      break;
    }
    return;
}

/****************************************************************************/
/* Convert degrees to dd mm'ss.s" (DMS-Format)                              */
/****************************************************************************/
void toDMS(double a, char *bufp, int bufplen)
{
    short neg = 0;
    int d, m, s;
    long n;

    if (a < 0.0) {
      a = -a;
      neg = 1;
    }
    d = (int) a;
    n = (long) ((a - (double) d) * 36000.0);

    m = n / 600;
    s = n % 600;

    if (neg)
      d = -d;

    sprintf(bufp, "%d%02d'%02d.%01d\"", d, m, s / 10, s % 10);
    return;
}


/****************************************************************************/
/* Convert dd mm'ss.s" (DMS-Format) to degrees.                             */
/****************************************************************************/
static double fromDMS(char *dms)
{
    int d = 0, m = 0;
    double s = 0.0;

    buf[0] = '\0';

    sscanf(dms, "%d%[ ]%d%[ ']%lf%[ \"NSWEnswe]", &d, buf, &m, buf, &s, buf);

    s = (double) (abs(d)) + ((double) m + s / 60.0) / 60.0;

    if (d >= 0 && strpbrk(buf, "SWsw") == NULL)
      return s;
    else
      return -s;
}


/****************************************************************************/
/* Convert degrees to dd mm.mmm' (DMM-Format)                               */
/****************************************************************************/
static void todmm(int flag, double a, char *bufp, int bufplen)
{
    short neg = 0;
    int d;
    long m;

    if (a < 0.0) {
      a = -a;
      neg = 1;
    }
    d = (int) a;
    m = (long) ((a - (double) d) * 60000.0);

    if (neg)
      d = -d;

    if (!flag)
      sprintf(bufp, "%d %02ld.%03ld'", d, m / 1000, m % 1000);
    else {
      if (flag == 1) {
          char c = 'N';

          if (d < 0) {
            d = -d;
            c = 'S';
          }
          sprintf(bufp,
                 "%02d%02ld%02ld%c", d, m / 1000, (m % 1000) / 10, c);
      } else if (flag == 2) {
          char c = 'E';

          if (d < 0) {
            d = -d;
            c = 'W';
          }
          sprintf(bufp,
                 "%03d%02ld%02ld%c", d, m / 1000, (m % 1000) / 10, c);
      }
    }
    return;
}

void toDMM(double a, char *bufp, int bufplen)
{
    todmm(0, a, bufp, bufplen);
    return;
}

void toRawLatDMM(double a, char *bufp, int bufplen)
{
    todmm(1, a, bufp, bufplen);
    return;
}

void toRawLonDMM(double a, char *bufp, int bufplen)
{
    todmm(2, a, bufp, bufplen);
    return;
}

/****************************************************************************/
/* Convert dd mm.mmm' (DMM-Format) to degree.                               */
/****************************************************************************/
static double fromDMM(char *dms)
{
    int d = 0;
    double m = 0.0;

    buf[0] = r[0] = '\0';
    sscanf(dms, "%d%[ ]%lf%[ 'NSWEnswe]", &d, buf, &m, buf);

    m = (double) (abs(d)) + m / 60.0;

    if (d >= 0 && strpbrk(buf, "SWsw") == NULL)
      return m;
    else
      return -m;
}

/****************************************************************************/
/* Convert                                                                  */
/****************************************************************************/
//#define CHUCK 1
#ifdef CHUCK

char UTMLetterDesignator(double lat)
{
    char nz;

//FIXME: we need to handle the z case

    nz = 'C' + ((int) (lat + 80.0)) / 8;
    if (nz > 'H')
      ++nz;             // skip 'I' and 'O'

    if (nz > 'N')
      ++nz;
    return nz;
}

void DegToUTM(float Lat, float Long, char *UTMZone, float *UTMNorthing, float *UTMEasting)
{
    //Does not take into account thespecial UTM zones between 0 degrees and
    //36 degrees longitude above 72 degrees latitude and a special zone 32
    //between 56 degrees and 64 degrees north latitude
    //Written by Chuck Gantz- chuck.gantz@globalstar.com

    double a, eccSquared;
    double k0 = 0.9996;

    double LongOrigin;
    double eccPrimeSquared;
    double N, T, C, A, M;

    double LatRad = Lat * DEGREE;
    double LongRad = Long * DEGREE;
    double LongOriginRad;

//    datumParams(mapdata.mapdatum, &a, &eccSquared);
    datumParams(100, &a, &eccSquared);

    if (Long > -6 && Long <= 0)
      LongOrigin = -3;  //arbitrarily set origin at 0 longitude to 3W

    else if (Long < 6 && Long > 0)
      LongOrigin = 3;
    else
      LongOrigin = (int) (Long / 6) * 6 + 3 * (int) (Long / 6) / abs((int) (Long / 6));
    LongOriginRad = LongOrigin * DEGREE;

    //compute the UTM Zone from the latitude and longitude
    sprintf(UTMZone, "%d%c", (int) ((Long + 180) / 6) + 1, UTMLetterDesignator(Lat));

    eccPrimeSquared = (eccSquared) / (1 - eccSquared);

    N = a / sqrt(1 - eccSquared * sin(LatRad) * sin(LatRad));
    T = tan(LatRad) * tan(LatRad);
    C = eccPrimeSquared * cos(LatRad) * cos(LatRad);
    A = cos(LatRad) * (LongRad - LongOriginRad);

    M = a * ((1 - eccSquared / 4 - 3 * eccSquared * eccSquared / 64 - 5
      * eccSquared * eccSquared * eccSquared / 256) * LatRad
      - (3 * eccSquared / 8 + 3 * eccSquared * eccSquared / 32 + 45
      * eccSquared * eccSquared * eccSquared / 1024) * sin(2 * LatRad)
      + (15 * eccSquared * eccSquared / 256 + 45 * eccSquared * eccSquared
      * eccSquared / 1024) * sin(4 * LatRad)
      - (35 * eccSquared * eccSquared * eccSquared / 3072) * sin(6 * LatRad));

    *UTMEasting = (double) (k0 * N * (A + (1 - T + C) * A * A * A / 6
      + (5 - 18 * T + T * T + 72 * C - 58 * eccPrimeSquared)
      * A * A * A * A * A / 120.0) + 500000.0);

    *UTMNorthing = (double) (k0 * (M + N * tan(LatRad)
      *(A * A / 2 + (5 - T + 9 * C + 4 * C * C) * A * A * A * A / 24
      + (61 - 58 * T + T * T + 600 * C - 330 * eccPrimeSquared)
      * A * A * A * A * A * A / 720)));
    if (Lat < 0)
      *UTMNorthing += 10000000.0;   //10000000 meter offset for southern hemisphere

}

void aUTMtoDeg(char *UTMZone, short southernHemisphere, double UTMNorthing, double UTMEasting,
      double *Lat, double *Long)
{
    //Lat and Long are in decimal degrees.
    //Does not take into account the special UTM zones between 0 degrees
    //and 36 degrees longitude above 72 degrees latitude and a special
    //zone 32 between 56 degrees and 64 degrees north latitude
    //Written by Chuck Gantz- chuck.gantz@globalstar.com

    double k0 = 0.9996;
    double a, eccSquared;
    double eccPrimeSquared;
    double e1;
    double N1, T1, C1, R1, D, M;
    double LongOrigin;
    double mu, phi1, phi1Rad;
    double x, y;
    int ZoneNumber;
    char *ZoneLetter;
    int NorthernHemisphere;   //1 for northern hemispher, 0 for southern

      double sLat, sLong;
      double rad2deg;
      rad2deg = 180. / PI;

//    datumParams(mapdata.mapdatum, &a, &eccSquared);
    datumParams(100, &a, &eccSquared);
    e1 = (1 - sqrt(1 - eccSquared)) / (1 + sqrt(1 - eccSquared));
    x = UTMEasting - 500000.0;      //remove 500,000 meter offset for longitude

    y = UTMNorthing;

    sscanf(UTMZone, "%d%c", &ZoneNumber, &ZoneLetter);
    if ((toupper(*ZoneLetter) - 'N') > 0)
      NorthernHemisphere = 1; //point is in northern hemisphere

    else {
      NorthernHemisphere = 0; //point is in southern hemisphere

      y -= 10000000.0;  //remove 10,000,000 meter offset used for southern hemisphere

    }

    LongOrigin = (ZoneNumber - 1) * 6 - 180 + 3;      //+3 puts origin in middle of zone

    eccPrimeSquared = (eccSquared) / (1 - eccSquared);

    M = y / k0;
    mu = M / (a * (1 - eccSquared / 4 - 3 * eccSquared * eccSquared / 64 - 5 * eccSquared * eccSquared * eccSquared / 256));

    phi1Rad = mu + (3 * e1 / 2 - 27 * e1 * e1 * e1 / 32) * sin(2 * mu)
      + (21 * e1 * e1 / 16 - 55 * e1 * e1 * e1 * e1 / 32) * sin(4 * mu)
      + (151 * e1 * e1 * e1 / 96) * sin(6 * mu);
    phi1 = phi1Rad * rad2deg;

    N1 = a / sqrt(1 - eccSquared * sin(phi1Rad) * sin(phi1Rad));
    T1 = tan(phi1Rad) * tan(phi1Rad);
    C1 = eccPrimeSquared * cos(phi1Rad) * cos(phi1Rad);
    R1 = a * (1 - eccSquared) / pow(1 - eccSquared * sin(phi1Rad) * sin(phi1Rad), 1.5);
    D = x / (N1 * k0);

    sLat = phi1Rad - (N1 * tan(phi1Rad) / R1) * (D * D / 2 - (5 + 3 * T1 + 10 * C1 - 4 * C1 * C1 - 9 * eccPrimeSquared) * D * D * D * D / 24
                                    + (61 + 90 * T1 + 298 * C1 + 45 * T1 * T1 - 252 * eccPrimeSquared - 3 * C1 * C1) * D * D * D * D * D * D / 720);
    sLat = sLat * rad2deg;
      *Lat = sLat;

    sLong = (D - (1 + 2 * T1 + C1) * D * D * D / 6 + (5 - 2 * C1 + 28 * T1 - 3 * C1 * C1 + 8 * eccPrimeSquared + 24 * T1 * T1)
          * D * D * D * D * D / 120) / cos(phi1Rad);
    sLong = LongOrigin + sLong * rad2deg;
      *Long = sLong;

}

#else

static const float lat0 = 0.0;      // reference transverse mercator latitude
static const float k0 = 0.9996;

//static void calcPhi(double *phi, double e, double t);

static double M(double phi, double a, double es);

/* --------------------------------------------------------------------------------- */

void
toTM(float lat, float lon, float lat0, float lon0, float k0, float *x, float *y)
{
//    extern struct PREFS gPrefs;
      double m, et2, n, t, c, A, a, m0, es, lambda, phi, lambda0, phi0;
      double f;

//    datumParams(mapdata.mapdatum, &a, &es);
//
//    datumParams(100, &a, &es);                      // = WGS84

// DSR Shortcut, constants for WGS-84
      a = 6378137.0;

      f = 1.0 / 298.257223563;                              // flattening
    es = 2 * f - f * f;                                     // eccentricity^2

      lambda = lon * DEGREE;
      phi = lat * DEGREE;

      phi0 = lat0 * DEGREE;
      lambda0 = lon0 * DEGREE;

      m0 = M(phi0, a, es);
      m = M(phi, a, es);

      et2 = es / (1 - es);
      n = a / sqrt(1 - es * pow(sin(phi), 2.0));
      t = pow(tan(phi), 2.0);
      c = et2 * pow(cos(phi), 2.0);
      A = (lambda - lambda0) * cos(phi);
      *x = k0*n*(A + (1.0 - t + c)*A*A*A/6.0
                  + (5.0 - 18.0*t + t*t + 72.0*c - 58.0*et2)*pow(A, 5.0) / 120.0);
      *y = k0*(m - m0 + n*tan(phi)*(A*A/2.0
                  + (5.0 - t + 9.0*c + 4*c*c)*pow(A, 4.0)/24.0
                  + (61.0 - 58.0*t + t*t + 600.0*c - 330.0*et2)*pow(A, 6.0)/720.0) );



}

/* --------------------------------------------------------------------------------- */

void
fromTM(double x, double y, double lat0, double lon0, double k0, double *lat, double *lon)
{
//    extern struct PREFS gFilePrefs;
      double a, m0, es, et2, m, e1, mu, phi1, c1, t1, n1, r1, d, phi0, lambda0;

      phi0 = lat0 * DEGREE;
      lambda0 = lon0 * DEGREE;

//    datumParams(mapdata.mapdatum, &a, &es);
    datumParams(100, &a, &es);

      m0 = M(phi0, a, es);

      et2 = es / (1.0 - es);
      m = m0 + y / k0;
      e1 = (1.0 - sqrt(1.0 - es)) / (1.0 + sqrt(1.0 - es));
      mu = m / (a * (1.0 - es/4.0 - 3.0 * es*es/64.0 - 5.0 * es*es*es/256.0));
      phi1 = mu + (3.0 * e1/2.0 - 27.0 * pow(e1, 3.0)/32.0) * sin(2.0 * mu)
                  + (21.0 * e1*e1/16.0 - 55.0 * pow(e1, 4.0)/32.0)
                  * sin(4.0 * mu) + 151.0 * pow(e1, 3.0)/96.0 * sin(6.0 * mu)
                  + 1097.0 * pow(e1, 4.0)/512.0 * sin(8.0 * mu);
      c1 = et2 * pow(cos(phi1), 2.0);
      t1 = pow(tan(phi1), 2.0);
      n1 = a / sqrt(1 - es * pow(sin(phi1), 2.0));
      r1 = a * (1.0 - es) / pow(1.0 - es * pow(sin(phi1), 2.0), 1.5);
      d = x / (n1 * k0);
      *lat = (phi1 - n1 * tan(phi1) / r1
                  * (d*d / 2.0 - (5.0 + 3.0 * t1 + 10.0 * c1 - 4.0 * c1*c1 - 9.0 * et2)
                  * pow(d, 4.0) / 24.0 + (61.0 + 90.0 * t1 + 298.0 * c1 + 45.0 * t1*t1
                  - 252.0 * et2 - 3.0 * c1*c1) * pow(d, 6.0) / 720.0 )) / DEGREE;
      *lon = (lambda0 + (d - (1.0 + 2.0 * t1 + c1) * pow(d, 3.0)/6.0
                  + (5.0 -2.0 * c1 + 28.0 * t1 - 3.0 * c1*c1 + 8.0 * et2 + 24.0 * t1*t1)
                  * pow(d, 5.0)/120.0) / cos(phi1)) / DEGREE;
}

/* --------------------------------------------------------------------------------- */

static double M(double phi, double a, double es)
{
      if (phi == 0.0)
            return 0.0;
      else {
            return a * (
                  ( 1.0 - es/4.0 - 3.0*es*es/64.0 - 5.0*es*es*es/256.0 ) * phi -
                  ( 3.0*es/8.0 + 3.0*es*es/32.0 + 45.0*es*es*es/1024.0 ) * sin(2.0 * phi) +
                  ( 15.0*es*es/256.0 + 45.0*es*es*es/1024.0 ) * sin(4.0 * phi) -
                  ( 35.0*es*es*es/3072.0 ) * sin(6.0 * phi) );
      }
}


/* --------------------------------------------------------------------------------- */
/*
static void toUPS(double lat, double lon, double *x, double *y)
{
//    extern struct PREFS gPrefs;
      double a, t, e, es, rho;
      const double k0 = 0.994;

      double lambda = lon * DEGREE;
      double phi = fabs(lat * DEGREE);

 //   datumParams(mapdata.mapdatum, &a, &es);
    datumParams(100, &a, &es);
      e = sqrt(es);
      t = tan(PI/4.0 - phi/2.0) / pow( (1.0 - e * sin(phi)) / (1.0 + e * sin(phi)), (e/2.0) );
      rho = 2.0 * a * k0 * t / sqrt(pow(1.0+e, 1.0+e) * pow(1.0-e, 1.0-e));
      *x = rho * sin(lambda);
      *y = rho * cos(lambda);

      if (lat > 0.0)    // Northern hemisphere
            *y = -(*y);
      *x += 2.0e6;      // Add in false easting and northing
      *y += 2.0e6;
}
*/

/* --------------------------------------------------------------------------------- */

/*
static void fromUPS(short southernHemisphere, double x, double y, double *lat, double *lon)
{
//    extern struct PREFS gFilePrefs;
      double a, es, e, t, rho;
      const double k0 = 0.994;

//    datumParams(mapdata.mapdatum, &a, &es);
    datumParams(100, &a, &es);
      e = sqrt(es);

      x -= 2.0e6;       // Remove false easting and northing
      y -= 2.0e6;

      rho = sqrt(x*x + y*y);
      t = rho * sqrt(pow(1.0+e, 1.0+e) * pow(1.0-e, 1.0-e)) / (2.0 * a * k0);

      calcPhi(lat, e, t);
      *lat /= DEGREE;

      if (y != 0.0)
            t = atan(fabs(x/y));
      else {
            t = PI / 2.0;
            if (x < 0.0) t = -t;
      }

      if (!southernHemisphere)
            y = -y;

      if (y < 0.0)
            t = PI - t;

      if (x < 0.0)
            t = -t;

      *lon = t / DEGREE;
}
*/

/* --------------------------------------------------------------------------------- */
/*
static void calcPhi(double *phi, double e, double t)
{
      double old = PI/2.0 - 2.0 * atan(t);
      short maxIterations = 20;

      while ( (fabs((*phi - old) / *phi) > 1.0e-8) && maxIterations-- ) {
            old = *phi;
            *phi = PI/ 2.0 - 2.0 * atan( t * pow((1.0 - e * sin(*phi)) / ((1.0 + e * sin(*phi))), (e / 2.0)) );
      }
}
*/

void DegToUTM(float lat, float lon, char *zone, float *x, float *y, float long0)
{
//    char nz;
//    float lon0;

      toTM(lat, lon, lat0, long0, k0, x, y);
      *x += 5.0e6;                        // false easting
//    *y += 1.0e7;
//    if (lat < 0.0)                      // false northing for southern hemisphere
//                *y = 10000000.0 - *y;

// DSR No Zone needed, never southern hemisphere or polar regions  brrrrrr....

/*
      if ((lat >= -80.0) && (lat <= 84.0)) {
            nz = 'C'+((short)(lat + 80.0)) / 8;
            if (nz > 'H') ++nz;                             // skip 'I' and 'O'
            if (nz > 'N') ++nz;
            lon0 = 6.0 * floor(lon / 6.0) + 3.0;
            if(zone)
                  sprintf(zone, "%02d %c", ((short)lon0 +183) / 6, nz);

            lon0 = long0;

            toTM(lat, lon, lat0, lon0, k0, x, y);
            *x += 5.0e5;                        // false easting
            if (lat < 0.0)                      // false northing for southern hemisphere
                  *y = 10000000.0 - *y;
      }
      else {
            if(zone)
            {
                  strcpy(zone, "00\tx");
                  if (lat > 0.0)
                        if (lon < 0.0) zone[3] = 'Y';
                                      else zone[3] = 'Z';
                  else
                        if (lon < 0.0) zone[3] = 'A';
                                      else zone[3] = 'B';
            }

            toUPS(lat, lon, x, y);
      }
*/

}

/* --------------------------------------------------------------------------------- */

void UTMtoDeg(double long0, short southernHemisphere, double x, double y, double *lat, double *lon)
{
//    double lon0;

      x -= 5.0e6;                   //   remove false easting
//    if(y > 10000000)
//                y = 1.0e7 - y;                // remove false northing for southern hemisphere
//    y -= 1.0e7;
      fromTM(x, y, lat0, long0, k0, lat, lon);

      return;

/*
      if (zone != 0) {
            lon0 = (double)((-183 + 6 * zone));
            if (southernHemisphere)
                  y = 1.0e7 - y;                // remove false northing for southern hemisphere
            x -= 5.0e5;                   //   and false easting
            fromTM(x, y, lat0, lon0, k0, lat, lon);
      }
      else
            fromUPS(southernHemisphere, x, y, lat, lon);
*/
}

#if 0
void aUTMtoDeg(char *zone, char *x, char *y, double *lat, double *lon)
{
    double dx, dy;
    int izone;

    sscanf(zone, "%d", &izone);
    sscanf(x, "%lf", &dx);
    sscanf(y, "%lf", &dy);

    /*FIXME: handle southern hemisphere*/
    UTMtoDeg(izone, 0, dx, dy, lat, lon);
}
#endif

#endif


#include <stdarg.h>
#include <stdlib.h>

int my_snprintf (char *str, size_t sz, const char *format, ...)
{
      va_list args;
      int ret;
      char * tmp;

      va_start(args, format);

      tmp = malloc (sz);
    if (tmp == NULL)
      return 0;

    ret = sprintf (tmp, format, args);

    strcpy(str, tmp);

      free (tmp);



      va_end(args);
      return ret;
}


/*
 *    Copyright  1996, 1997, 1998, 1999, 2000 by Remco Treffkorn
 *    Distributed under the terms of the Q Public License. Please see
 *    the included file LICENSE.
 */



#define MAXORDER 3

typedef double DOUBLE;

/* structure for use internally with these functions.  these functions expect
   square matrices so only one variable is given (n) for the matrix size */

struct MATRIX {
    int n;              /* size of this matrix (n x n) */
    DOUBLE *v;
};

/* calculate offset into array based on r/c */

#define M(row,col) m->v[(((row)-1)*(m->n))+(col)-1]

/***************************************************************************/
/*
 */
/***************************************************************************/

#define MSUCCESS     1        /* success */
#define MNPTERR      0        /* not enough points */
#define MUNSOLVABLE -1        /* not solvable */
#define MMEMERR     -2        /* not enough memory */
#define MPARMERR    -3        /* parameter error */
#define MINTERR     -4        /* internal error */

static int calccoef();
static int calcls();
static int exactdet();
static int solvemat();
static DOUBLE term();



/*
   transform a single coordinate pair.
 */

int georef(double e1, double n1, double *e, double *n, double E[], double N[], int order)
{
    DOUBLE e3, e2n, en2, n3, e2, en, n2;

    switch (order) {
    case 1:

      *e = E[0] + E[1] * e1 + E[2] * n1;
      *n = N[0] + N[1] * e1 + N[2] * n1;
      break;

    case 2:

      e2 = e1 * e1;
      n2 = n1 * n1;
      en = e1 * n1;

      *e = E[0] + E[1] * e1 + E[2] * n1 +
          E[3] * e2 + E[4] * en + E[5] * n2;
      *n = N[0] + N[1] * e1 + N[2] * n1 +
          N[3] * e2 + N[4] * en + N[5] * n2;
      break;

    case 3:

      e2 = e1 * e1;
      en = e1 * n1;
      n2 = n1 * n1;
      e3 = e1 * e2;
      e2n = e2 * n1;
      en2 = e1 * n2;
      n3 = n1 * n2;

      *e = E[0] +
          E[1] * e1 + E[2] * n1 +
          E[3] * e2 + E[4] * en + E[5] * n2 +
          E[6] * e3 + E[7] * e2n + E[8] * en2 + E[9] * n3;
      *n = N[0] +
          N[1] * e1 + N[2] * n1 +
          N[3] * e2 + N[4] * en + N[5] * n2 +
          N[6] * e3 + N[7] * e2n + N[8] * en2 + N[9] * n3;
      break;

    default:

      return (MPARMERR);
      break;
    }

    return (MSUCCESS);
}

/***************************************************************************/
/*
   compute the georefferencing coefficients based on a set of control points
 */
/***************************************************************************/

int compute_georef_equations(struct GeoRef *cp, double E12[], double N12[],
                              double E21[], double N21[])
{
    double *tempptr;
    int status;

    if (cp->order < 1 || cp->order > MAXORDER)
      return (MPARMERR);

    /* calculate the forward transformation coefficients */

    status = calccoef(cp, E12, N12, cp->order);
    if (status != MSUCCESS)
      return (status);

    /* switch the 1 and 2 easting and northing arrays */

    tempptr = cp->e1;
    cp->e1 = cp->e2;
    cp->e2 = tempptr;
    tempptr = cp->n1;
    cp->n1 = cp->n2;
    cp->n2 = tempptr;

    /* calculate the backward transformation coefficients */

    status = calccoef(cp, E21, N21, cp->order);

    /* switch the 1 and 2 easting and northing arrays back */

    tempptr = cp->e1;
    cp->e1 = cp->e2;
    cp->e2 = tempptr;
    tempptr = cp->n1;
    cp->n1 = cp->n2;
    cp->n2 = tempptr;

    return (status);
}

/***************************************************************************/
/*
   compute the georefferencing coefficients based on a set of control points
 */
/***************************************************************************/

static int calccoef(cp, E, N, order)
struct GeoRef *cp;
double E[];
double N[];
int order;
{
    struct MATRIX m;
    DOUBLE *a;
    DOUBLE *b;
    int numactive;            /* number of active control points */
    int status;

    /* calculate the number of valid control points */

    numactive = cp->count;

    /* calculate the minimum number of control points needed to determine
       a transformation of this order */

    m.n = ((order + 1) * (order + 2)) / 2;

    if (numactive < m.n)
      return (MNPTERR);

    /* INITIALIZE MATRIX */

    m.v = (DOUBLE *) calloc(m.n * m.n, sizeof(DOUBLE));
    if (m.v == NULL) {
      return (MMEMERR);
    }
    a = (DOUBLE *) calloc(m.n, sizeof(DOUBLE));
    if (a == NULL) {
      free((char *) m.v);
      return (MMEMERR);
    }
    b = (DOUBLE *) calloc(m.n, sizeof(DOUBLE));
    if (b == NULL) {
      free((char *) m.v);
      free((char *) a);
      return (MMEMERR);
    }
    if (numactive == m.n)
      status = exactdet(cp, &m, a, b, E, N);
    else
      status = calcls(cp, &m, a, b, E, N);

    free((char *) m.v);
    free((char *) a);
    free((char *) b);

    return (status);
}

/***************************************************************************/
/*
   calculate the transformation coefficients with exactly the minimum
   number of control points required for this transformation.
 */
/***************************************************************************/

static int exactdet(cp, m, a, b, E, N)
struct GeoRef *cp;
struct MATRIX *m;
DOUBLE a[];
DOUBLE b[];
double E[];             /* easting coefficients */
double N[];             /* northing coefficients */
{
    int pntnow, currow, j;

    currow = 1;
    for (pntnow = 0; pntnow < cp->count; pntnow++) {
          /* POPULATE MATRIX M */

          for (j = 1; j <= m->n; j++) {
            M(currow, j) = term(j, cp->e1[pntnow], cp->n1[pntnow]);
          }

          /* populate matrix a and b */

          a[currow - 1] = cp->e2[pntnow];
          b[currow - 1] = cp->n2[pntnow];

          currow++;
    }

    if (currow - 1 != m->n)
      return (MINTERR);

    return (solvemat(m, a, b, E, N));
}

/***************************************************************************/
/*
   calculate the transformation coefficients with more than the minimum
   number of control points required for this transformation.  this
   routine uses the least squares method to compute the coefficients.
 */
/***************************************************************************/

static int calcls(cp, m, a, b, E, N)
struct GeoRef *cp;
struct MATRIX *m;
DOUBLE a[];
DOUBLE b[];
double E[];             /* EASTING COEFFICIENTS */
double N[];             /* NORTHING COEFFICIENTS */
{
    int i, j, n, numactive = 0;

    /* initialize the upper half of the matrix and the two column vectors */

    for (i = 1; i <= m->n; i++) {
      for (j = i; j <= m->n; j++)
          M(i, j) = 0.0;
      a[i - 1] = b[i - 1] = 0.0;
    }

    /* sum the upper half of the matrix and the column vectors according to
       the least squares method of solving over determined systems */

    for (n = 0; n < cp->count; n++) {
          numactive++;
          for (i = 1; i <= m->n; i++) {
            for (j = i; j <= m->n; j++)
                M(i, j) += term(i, cp->e1[n], cp->n1[n]) * term(j, cp->e1[n], cp->n1[n]);

            a[i - 1] += cp->e2[n] * term(i, cp->e1[n], cp->n1[n]);
            b[i - 1] += cp->n2[n] * term(i, cp->e1[n], cp->n1[n]);
          }
    }

    if (numactive <= m->n)
      return (MINTERR);

    /* transpose values in upper half of m to other half */

    for (i = 2; i <= m->n; i++) {
      for (j = 1; j < i; j++)
          M(i, j) = M(j, i);
    }

    return (solvemat(m, a, b, E, N));
}

/***************************************************************************/
/*
   calculate the x/y term based on the term number

   ORDER\TERM   1    2    3    4    5    6    7    8    9   10
   1        e0n0 e1n0 e0n1
   2        e0n0 e1n0 e0n1 e2n0 e1n1 e0n2
   3        e0n0 e1n0 e0n1 e2n0 e1n1 e0n2 e3n0 e2n1 e1n2 e0n3
 */
/***************************************************************************/

static DOUBLE term(term, e, n)
int term;
double e;
double n;
{
    switch (term) {
    case 1:
      return ((DOUBLE) 1.0);
    case 2:
      return ((DOUBLE) e);
    case 3:
      return ((DOUBLE) n);
    case 4:
      return ((DOUBLE) (e * e));
    case 5:
      return ((DOUBLE) (e * n));
    case 6:
      return ((DOUBLE) (n * n));
    case 7:
      return ((DOUBLE) (e * e * e));
    case 8:
      return ((DOUBLE) (e * e * n));
    case 9:
      return ((DOUBLE) (e * n * n));
    case 10:
      return ((DOUBLE) (n * n * n));
    }
    return ((DOUBLE) 0.0);
}

/***************************************************************************/
/*
   solve for the 'E' and 'N' coefficients by using a somewhat modified
   gaussian elimination method.

   | M11 M12 ... M1n | | E0   |   | a0   |
   | M21 M22 ... M2n | | E1   | = | a1   |
   |  .   .   .   .  | | .    |   | .    |
   | Mn1 Mn2 ... Mnn | | En-1 |   | an-1 |

   and

   | M11 M12 ... M1n | | N0   |   | b0   |
   | M21 M22 ... M2n | | N1   | = | b1   |
   |  .   .   .   .  | | .    |   | .    |
   | Mn1 Mn2 ... Mnn | | Nn-1 |   | bn-1 |
 */
/***************************************************************************/

static int solvemat(m, a, b, E, N)
struct MATRIX *m;
DOUBLE a[];
DOUBLE b[];
double E[];
double N[];
{
    int i, j, i2, j2, imark;
    DOUBLE factor, temp;
    DOUBLE pivot;       /* actual value of the largest pivot candidate */

    for (i = 1; i <= m->n; i++) {
      j = i;

      /* find row with largest magnitude value for pivot value */

      pivot = M(i, j);
      imark = i;
      for (i2 = i + 1; i2 <= m->n; i2++) {
          temp = fabs(M(i2, j));
          if (temp > fabs(pivot)) {
            pivot = M(i2, j);
            imark = i2;
          }
      }

      /* if the pivot is very small then the points are nearly co-linear */
      /* co-linear points result in an undefined matrix, and nearly */
      /* co-linear points results in a solution with rounding error */

      if (pivot == 0.0)
          return (MUNSOLVABLE);

      /* if row with highest pivot is not the current row, switch them */

      if (imark != i) {
          for (j2 = 1; j2 <= m->n; j2++) {
            temp = M(imark, j2);
            M(imark, j2) = M(i, j2);
            M(i, j2) = temp;
          }

          temp = a[imark - 1];
          a[imark - 1] = a[i - 1];
          a[i - 1] = temp;

          temp = b[imark - 1];
          b[imark - 1] = b[i - 1];
          b[i - 1] = temp;
      }
      /* compute zeros above and below the pivot, and compute
         values for the rest of the row as well */

      for (i2 = 1; i2 <= m->n; i2++) {
          if (i2 != i) {
            factor = M(i2, j) / pivot;
            for (j2 = j; j2 <= m->n; j2++)
                M(i2, j2) -= factor * M(i, j2);
            a[i2 - 1] -= factor * a[i - 1];
            b[i2 - 1] -= factor * b[i - 1];
          }
      }
    }

    /* since all other values in the matrix are zero now, calculate the
       coefficients by dividing the column vectors by the diagonal values. */

    for (i = 1; i <= m->n; i++) {
      E[i - 1] = a[i - 1] / M(i, i);
      N[i - 1] = b[i - 1] / M(i, i);
    }

    return (MSUCCESS);
}

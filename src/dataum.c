/*
 *    Copyright  1996, 1997, 1998, 1999, 2000 by Remco Treffkorn
 *    Distributed under the terms of the Q Public License. Please see
 *    the included file LICENSE.
 */

#include <math.h>

//#include "dychart.h"

//CPL_CVSID("$Id: dataum.c,v 1.2 2007/05/03 13:26:12 dsr Exp $");



/* For NAD27 shift table */
//extern struct CTABLE conus_ct[];

//  ellipsoid: index into the gEllipsoid[] array, in which
//             a is the ellipsoid semimajor axis
//             invf is the inverse of the ellipsoid flattening f
//  dx, dy, dz: ellipsoid center with respect to WGS84 ellipsoid center
//    x axis is the prime meridian
//    y axis is 90 degrees east longitude
//    z axis is the axis of rotation of the ellipsoid

// The following values for dx, dy and dz were extracted from the output of
// the GARMIN PCX5 program. The output also includes values for da and df, the
// difference between the reference ellipsoid and the WGS84 ellipsoid semi-
// major axis and flattening, respectively. These are replaced by the
// data contained in the structure array gEllipsoid[], which was obtained from
// the Defence Mapping Agency document number TR8350.2, "Department of Defense
// World Geodetic System 1984."

struct DATUM const gDatum[] = {
//         name               ellipsoid   dx      dy       dz
      { "Adindan",                5,   -162,    -12,    206 },    // 0
      { "Afgooye",               15,    -43,   -163,     45 },    // 1
      { "Ain el Abd 1970",       14,   -150,   -251,     -2 },    // 2
      { "Anna 1 Astro 1965",      2,   -491,    -22,    435 },    // 3
      { "Arc 1950",               5,   -143,    -90,   -294 },    // 4
      { "Arc 1960",               5,   -160,     -8,   -300 },    // 5
      { "Ascension Island �8",  14,   -207,    107,     52 },     // 6
      { "Astro B4 Sorol Atoll",  14,    114,   -116,   -333 },    // 7
      { "Astro Beacon ��",      14,    145,     75,   -272 },     // 8
      { "Astro DOS 71/4",        14,   -320,    550,   -494 },    // 9
      { "Astronomic Stn �2",    14,    124,   -234,    -25 },     // 10
      { "Australian Geod �6",    2,   -133,    -48,    148 },     // 11
      { "Australian Geod �4",    2,   -134,    -48,    149 },     // 12
      { "Bellevue (IGN)",        14,   -127,   -769,    472 },    // 13
      { "Bermuda 1957",           4,    -73,    213,    296 },    // 14
      { "Bogota Observatory",    14,    307,    304,   -318 },    // 15
      { "Campo Inchauspe",       14,   -148,    136,     90 },    // 16
      { "Canton Astro 1966",     14,    298,   -304,   -375 },    // 17
      { "Cape",                   5,   -136,   -108,   -292 },    // 18
      { "Cape Canaveral",         4,     -2,    150,    181 },    // 19
      { "Carthage",               5,   -263,      6,    431 },    // 20
      { "CH-1903",                3,    674,     15,    405 },    // 21
      { "Chatham 1971",          14,    175,    -38,    113 },    // 22
      { "Chua Astro",            14,   -134,    229,    -29 },    // 23
      { "Corrego Alegre",        14,   -206,    172,     -6 },    // 24
      { "Djakarta (Batavia)",     3,   -377,    681,    -50 },    // 25
      { "DOS 1968",              14,    230,   -199,   -752 },    // 26
      { "Easter Island 1967",    14,    211,    147,    111 },    // 27
      { "European 1950",         14,    -87,    -98,   -121 },    // 28
      { "European 1979",         14,    -86,    -98,   -119 },    // 29
      { "Finland Hayford",       14,    -78,   -231,    -97 },    // 30
      { "Gandajika Base",        14,   -133,   -321,     50 },    // 31
      { "Geodetic Datum �9",    14,     84,    -22,    209 },     // 32
      { "Guam 1963",              4,   -100,   -248,    259 },    // 33
      { "GUX 1 Astro",           14,    252,   -209,   -751 },    // 34
      { "Hjorsey 1955",          14,    -73,     46,    -86 },    // 35
      { "Hong Kong 1963",        14,   -156,   -271,   -189 },    // 36
      { "Indian Bangladesh",      6,    289,    734,    257 },    // 37
      { "Indian Thailand",        6,    214,    836,    303 },    // 38
      { "Ireland 1965",           1,    506,   -122,    611 },    // 39
      { "ISTS 073 Astro �9",    14,    208,   -435,   -229 },     // 40
      { "Johnston Island",       14,    191,    -77,   -204 },    // 41
      { "Kandawala",              6,    -97,    787,     86 },    // 42
      { "Kerguelen Island",      14,    145,   -187,    103 },    // 43
      { "Kertau 1948",            7,    -11,    851,      5 },    // 44
      { "L.C. 5 Astro",           4,     42,    124,    147 },    // 45
      { "Liberia 1964",           5,    -90,     40,     88 },    // 46
      { "Luzon Mindanao",         4,   -133,    -79,    -72 },    // 47
      { "Luzon Philippines",      4,   -133,    -77,    -51 },    // 48
      { "Mahe 1971",              5,     41,   -220,   -134 },    // 49
      { "Marco Astro",           14,   -289,   -124,     60 },    // 50
      { "Massawa",                3,    639,    405,     60 },    // 51
      { "Merchich",               5,     31,    146,     47 },    // 52
      { "Midway Astro 1961",     14,    912,    -58,   1227 },    // 53
      { "Minna",                  5,    -92,    -93,    122 },    // 54
      { "NAD27 Alaska",           4,     -5,    135,    172 },    // 55
      { "NAD27 Bahamas",          4,     -4,    154,    178 },    // 56
      { "NAD27 Canada",           4,    -10,    158,    187 },    // 57
      { "NAD27 Canal Zone",       4,      0,    125,    201 },    // 58
      { "NAD27 Caribbean",        4,     -7,    152,    178 },    // 59
      { "NAD27 Central",          4,      0,    125,    194 },    // 60
      { "NAD27 CONUS",            4,     -8,    160,    176 },    // 61
      { "NAD27 Cuba",             4,     -9,    152,    178 },    // 62
      { "NAD27 Greenland",        4,     11,    114,    195 },    // 63
      { "NAD27 Mexico",           4,    -12,    130,    190 },    // 64
      { "NAD27 San Salvador",     4,      1,    140,    165 },    // 65
      { "NAD83",                 11,      0,      0,      0 },    // 66
      { "Nahrwn Masirah Ilnd",    5,   -247,   -148,    369 },    // 67
      { "Nahrwn Saudi Arbia",     5,   -231,   -196,    482 },    // 68
      { "Nahrwn United Arab",     5,   -249,   -156,    381 },    // 69
      { "Naparima BWI",          14,     -2,    374,    172 },    // 70
      { "Observatorio 1966",     14,   -425,   -169,     81 },    // 71
      { "Old Egyptian",          12,   -130,    110,    -13 },    // 72
      { "Old Hawaiian",           4,     61,   -285,   -181 },    // 73
      { "Oman",                   5,   -346,     -1,    224 },    // 74
      { "Ord Srvy Grt Britn",     0,    375,   -111,    431 },    // 75
      { "Pico De Las Nieves",    14,   -307,    -92,    127 },    // 76
      { "Pitcairn Astro 1967",   14,    185,    165,     42 },    // 77
      { "Prov So Amrican �6",   14,   -288,    175,   -376 },     // 78
      { "Prov So Chilean �3",   14,     16,    196,     93 },     // 79
      { "Puerto Rico",            4,     11,     72,   -101 },    // 80
      { "Qatar National",        14,   -128,   -283,     22 },    // 81
      { "Qornoq",                14,    164,    138,   -189 },    // 82
      { "Reunion",               14,     94,   -948,  -1262 },    // 83
      { "Rome 1940",             14,   -225,    -65,      9 },    // 84
      { "RT 90",                  3,    498,    -36,    568 },    // 85
      { "Santo (DOS)",           14,    170,     42,     84 },    // 86
      { "Sao Braz",              14,   -203,    141,     53 },    // 87
      { "Sapper Hill 1943",      14,   -355,     16,     74 },    // 88
      { "Schwarzeck",            21,    616,     97,   -251 },    // 89
      { "South American �9",    16,    -57,      1,    -41 },     // 90
      { "South Asia",             8,      7,    -10,    -26 },    // 91
      { "Southeast Base",        14,   -499,   -249,    314 },    // 92
      { "Southwest Base",        14,   -104,    167,    -38 },    // 93
      { "Timbalai 1948",          6,   -689,    691,    -46 },    // 94
      { "Tokyo",                  3,   -128,    481,    664 },    // 95
      { "Tristan Astro 1968",    14,   -632,    438,   -609 },    // 96
      { "Viti Levu 1916",         5,     51,    391,    -36 },    // 97
      { "Wake-Eniwetok �0",     13,    101,     52,    -39 },     // 98
      { "WGS 72",                19,      0,      0,      5 },    // 99
      { "WGS 84",                20,      0,      0,      0 },    // 100
      { "Zanderij",              14,   -265,    120,   -358 },    // 101
      { 0 },
};

struct ELLIPSOID const gEllipsoid[] = {
//  name                               a        1/f
{  "Airy 1830",                  6377563.396, 299.3249646   }, // 0
{  "Modified Airy",              6377340.189, 299.3249646   }, // 1
{  "Australian National",        6378160.0,   298.25        }, // 2
{  "Bessel 1841",                6377397.155, 299.15281282  }, // 3
{  "Clarke 1866",                6378206.4,   294.9786982   }, // 4
{  "Clarke 1880",                6378249.145, 293.465       }, // 5
{  "Everest (India 1830)",       6377276.345, 300.8017      }, // 6
{  "Everest (1948)",             6377304.063, 300.8017      }, // 7
{  "Modified Fischer 1960",      6378155.0,   298.3         }, // 8
{  "Everest (Pakistan)",         6377309.613, 300.8017      }, // 9
{  "Indonesian 1974",            6378160.0,   298.247       }, // 10 ?
{  "GRS 80",                     6378137.0,   298.257222101 }, // 11
{  "Helmert 1906",               6378200.0,   298.3         }, // 12
{  "Hough 1960",                 6378270.0,   297.0         }, // 13
{  "International 1924",         6378388.0,   297.0         }, // 14
{  "Krassovsky 1940",            6378245.0,   298.3         }, // 15
{  "South American 1969",        6378160.0,   298.25        }, // 16
{  "Everest (Malaysia 1969)",    6377295.664, 300.8017      }, // 17
{  "Everest (Sabah Sarawak)",    6377298.556, 300.8017      }, // 18
{  "WGS 72",                     6378135.0,   298.26        }, // 19
{  "WGS 84",                     6378137.0,   298.257223563 }, // 20
{  "Bessel 1841 (Namibia)",      6377483.865, 299.1528128   }, // 21
{  "Everest (India 1956)",       6377301.243, 300.8017      }, // 22
{  "Fischer 1960",               6378166.0,   298.3         }, // 23
{  "WGS 60",                     6378165.0,   298.3         }, // 24
{  "WGS 66",                     6378145.0,   298.25        }, // 25
{  "SGS 85",                     6378136.0,   298.257       }, // 26
{ 0 },
};

/* define constants */
static const double WGSa     = 6378137.0;           /* WGS84 semimajor axis */
static const double WGSinvf  = 298.257223563;                  /* WGS84 1/f */
static const short  WGS84ID  = 100;                    /* ID of WGS84 datum */

#ifdef DATUM_CONV
/****************************************************************************/
/* Converts latitude and longitude in decimal degrees from WGS84 to another */
/* datum or from another datum to WGS84. The arguments to this function     */
/* include a direction flag 'fromWGS84', pointers to double precision       */
/* latitude and longitude, and an index to the gDatum[] array.              */
/****************************************************************************/
void table_translate(short fromWGS84, double *latitude, double *longitude,
                 short datumID)
{
  extern struct DATUM     const gDatum[];
  extern struct ELLIPSOID const gEllipsoid[];
  double a, f;

  if (datumID == WGS84ID)            /* do nothing if current datum is WGS84 */
    return;

  a = gEllipsoid[gDatum[datumID].ellipsoid].a;
  f = 1.0 / gEllipsoid[gDatum[datumID].ellipsoid].invf;
  molod_translate(fromWGS84, latitude, longitude, gDatum[datumID].dx,
              gDatum[datumID].dy, gDatum[datumID].dz, a, f);
}

void molod_translate(short fromWGS84, double *latitude, double *longitude,
                 double dx, double dy, double dz,
                 double a, double f)
{
  double phi    = *latitude  * DEGREE;
  double lambda = *longitude * DEGREE;
  double a0, b0, es0, f0;               /* Reference ellipsoid of input data */
  double a1, b1, es1, f1;              /* Reference ellipsoid of output data */
  double psi;                                         /* geocentric latitude */
  double x, y, z;           /* 3D coordinates with respect to original datum */
  double psi1;                            /* transformed geocentric latitude */

  if (fromWGS84) {                        /* convert from WGS84 to new datum */
    a0 = WGSa;                                       /* WGS84 semimajor axis */
    f0 = 1.0 / WGSinvf;                                  /* WGS84 flattening */
    a1 = a;
    f1 = f;
  }
  else {                                      /* convert from datum to WGS84 */
    a0 = a;                                                /* semimajor axis */
    f0 = f;                                                    /* flattening */
    a1 = WGSa;                                       /* WGS84 semimajor axis */
    f1 = 1.0 / WGSinvf;                                  /* WGS84 flattening */
    dx = -dx;
    dy = -dy;
    dz = -dz;
  }
  b0 = a0 * (1 - f0);                      /* semiminor axis for input datum */
  es0 = 2 * f0 - f0*f0;                                    /* eccentricity^2 */

  b1 = a1 * (1 - f1);                     /* semiminor axis for output datum */
  es1 = 2 * f1 - f1*f1;                                    /* eccentricity^2 */

  /* Convert geodedic latitude to geocentric latitude, psi */
  if (*latitude == 0.0 || *latitude == 90.0 || *latitude == -90.0)
    psi = phi;
  else
    psi = atan((1 - es0) * tan(phi));

  /* Calc x and y axis coordinates with respect to original ellipsoid */
  if (*longitude == 90.0 || *longitude == -90.0) {
    x = 0.0;
    y = fabs(a0 * b0 / sqrt(b0*b0 + a0*a0*pow(tan(psi), 2.0)));
  }
  else {
    x = fabs((a0 * b0) /
           sqrt((1 + pow(tan(lambda), 2.0)) *
              (b0*b0 + a0*a0 * pow(tan(psi), 2.0))));
    y = fabs(x * tan(lambda));
  }

  if (*longitude < -90.0 || *longitude > 90.0)
    x = -x;
  if (*longitude < 0.0)
    y = -y;

  /* Calculate z axis coordinate with respect to the original ellipsoid */
  if (*latitude == 90.0)
    z = b0;
  else if (*latitude == -90.0)
    z = -b0;
  else
    z = tan(psi) * sqrt((a0*a0 * b0*b0) / (b0*b0 + a0*a0 * pow(tan(psi), 2.0)));

  /* Calculate the geodetic latitude with respect to the new ellipsoid */
  psi1 = atan((z - dz) / sqrt((x - dx)*(x - dx) + (y - dy)*(y - dy)));

  /* Convert to geocentric latitude and save return value */
  *latitude = atan(tan(psi1) / (1 - es1)) * 180.0 / PI;

  /* Calculate the longitude with respect to the new ellipsoid */
  *longitude = atan((y - dy) / (x - dx)) * 180.0 / PI;

  /* Correct the resultant for negative x values */
  if (x-dx < 0.0) {
    if (y-dy > 0.0)
      *longitude = 180.0 + *longitude;
    else
      *longitude = -180.0 + *longitude;
  }
}

void datum_translate(short fromWGS84, double *latitude, double *longitude,
                 short datum)
{
  char *projc[10];
  short nprojc;
  PJ *cnv;
  UV val;

  /* do nothing if current datum is WGS84 */
  if (datum == WGS84ID)
    return;

  val.u = *longitude * DEGREE;
  val.v = *latitude * DEGREE;

  if (!fromWGS84) {
    /* Special case for NAD27 */
    if (datum == 61) {
      val = nad_cvt(val, 0, conus_ct);
      *longitude = val.u * RADIAN;
      *latitude = val.v * RADIAN;
    }

    /* Now convert NAD83 to WGS84 */
    if ((datum == 61) || (datum == 66)) {
#if 0 /* Close enough for government work */
      projc[0] = "ellps=GRS80";
      projc[1] = "proj=poly";
      projc[2] = "no_defs";
      nprojc = 3;

      cnv = pj_init(nprojc, projc);
      val = pj_fwd(val, cnv);

      projc[0] = "ellps=WGS84";
      projc[1] = "proj=poly";
      projc[2] = "no_defs";
      nprojc = 3;

      cnv = pj_init(nprojc, projc);
      val = pj_inv(val, cnv);

      *longitude = val.u * RADIAN;
      *latitude = val.v * RADIAN;
#endif

      return;
    }
  } else {
    /* Convert WGS84 to NAD83 */
    if ((datum == 61) || (datum == 66)) {
#if 0 /* Close enough for government work */
      projc[0] = "ellps=WGS84";
      projc[1] = "proj=poly";
      projc[2] = "no_defs";
      nprojc = 3;

      cnv = pj_init(nprojc, projc);
      val = pj_fwd(val, cnv);

      projc[0] = "ellps=GRS80";
      projc[1] = "proj=poly";
      projc[2] = "no_defs";
      nprojc = 3;

      cnv = pj_init(nprojc, projc);
      val = pj_inv(val, cnv);
#endif
      /* Apply NAD27 shift */
      if (datum == 61) {
      val = nad_cvt(val, 1, conus_ct);

      *longitude = val.u * RADIAN;
      *latitude = val.v * RADIAN;
      }

      return;
    }
  }

  table_translate(fromWGS84, latitude, longitude, datum);
}
#endif

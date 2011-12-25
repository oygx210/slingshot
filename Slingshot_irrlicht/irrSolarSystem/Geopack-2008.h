/***************************************************************************
geopack.h  - 	header to integrate the Tsyganenko GEOPACK
FORTRAN routines into a C++ program

***************************************************************************/
/* This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA */

#include "f2c.h"

// Define the fortran subroutines as "C" externs, so that we can use
// them in C++

//----------------------------------------------------------------------------------------------------
// Function: recalc()
//           sets up FORTRAN common blocks which hold the parameters for the
//           model
// INPUT:    date
extern "C" { int recalc_08__(integer *iyear, integer *iday, 
							 integer *ihour, integer *min__, integer *isec, real *vgsex, real *vgsey, real *vgsez); }

//----------------------------------------------------------------------------------------------------
/*  TRACES A FIELD LINE FROM AN ARBITRARY POINT OF SPACE TO THE EARTH'S */
/*  SURFACE OR TO A MODEL LIMITING BOUNDARY. */

/*  THIS SUBROUTINE ALLOWS TWO OPTIONS: */

/*  (1) IF INNAME=IGRF_GSW_08, THEN THE IGRF MODEL WILL BE USED FOR CALCULATING */
/*      CONTRIBUTION FROM EARTH'S INTERNAL SOURCES. IN THIS CASE, SUBROUTINE */
/*      RECALC_08 MUST BE CALLED BEFORE USING TRACE_08, WITH PROPERLY SPECIFIED DATE, */
/*      UNIVERSAL TIME, AND SOLAR WIND VELOCITY COMPONENTS, TO CALCULATE IN ADVANCE */
/*      ALL QUANTITIES NEEDED FOR THE MAIN FIELD MODEL AND FOR TRANSFORMATIONS */
/*      BETWEEN INVOLVED COORDINATE SYSTEMS. */

/*  (2) IF INNAME=DIP_08, THEN A PURE DIPOLE FIELD WILL BE USED INSTEAD OF THE IGRF MODEL. */
/*      IN THIS CASE, THE SUBROUTINE RECALC_08 MUST ALSO BE CALLED BEFORE TRACE_08. */
/*      HERE ONE CAN CHOOSE EITHER TO */
/*      (a) CALCULATE DIPOLE TILT ANGLE BASED ON DATE, TIME, AND SOLAR WIND DIRECTION, */
/*   OR (b) EXPLICITLY SPECIFY THAT ANGLE, WITHOUT ANY REFERENCE TO DATE/UT/SOLAR WIND. */
/*      IN THE LAST CASE (b), THE SINE (SPS) AND COSINE (CPS) OF THE DIPOLE TILT */
/*      ANGLE MUST BE SPECIFIED IN ADVANCE (BUT AFTER HAVING CALLED RECALC_08) AND FORWARDED */
/*      IN THE COMMON BLOCK /GEOPACK1/ (IN ITS 11th AND 12th ELEMENTS, RESPECTIVELY). */
/*      IN THIS CASE THE ROLE OF THE SUBROUTINE RECALC_08 IS REDUCED TO ONLY CALCULATING */
/*      THE COMPONENTS OF THE EARTH'S DIPOLE MOMENT. */

/* ------------- INPUT PARAMETERS: */

/*   XI,YI,ZI - GSW COORDS OF THE FIELD LINE STARTING POINT (IN EARTH RADII, 1 RE = 6371.2 km), */

/*   DIR - SIGN OF THE TRACING DIRECTION: IF DIR=1.0 THEN THE TRACING IS MADE ANTIPARALLEL */
/*     TO THE TOTAL FIELD VECTOR (E.G., FROM NORTHERN TO SOUTHERN CONJUGATE POINT); */
/*     IF DIR=-1.0 THEN THE TRACING PROCEEDS IN THE OPPOSITE DIRECTION, THAT IS, PARALLEL TO */
/*     THE TOTAL FIELD VECTOR. */

/*   DSMAX - UPPER LIMIT ON THE STEPSIZE (SETS A DESIRED MAXIMAL SPACING BETWEEN */
/*                 THE FIELD LINE POINTS) */

/*   ERR - PERMISSIBLE STEP ERROR. A REASONABLE ESTIMATE PROVIDING A SUFFICIENT ACCURACY FOR MOST */
/*         APPLICATIONS IS ERR=0.0001. SMALLER/LARGER VALUES WILL RESULT IN LARGER/SMALLER NUMBER */
/*         OF STEPS AND, HENCE, OF OUTPUT FIELD LINE POINTS. NOTE THAT USING MUCH SMALLER VALUES */
/*         OF ERR MAY REQUIRE USING A DOUBLE PRECISION VERSION OF THE ENTIRE PACKAGE. */

/*   R0 -  RADIUS OF A SPHERE (IN RE), DEFINING THE INNER BOUNDARY OF THE TRACING REGION */
/*         (USUALLY, EARTH'S SURFACE OR THE IONOSPHERE, WHERE R0~1.0) */
/*         IF THE FIELD LINE REACHES THAT SPHERE FROM OUTSIDE, ITS INBOUND TRACING IS */
/*         TERMINATED AND THE CROSSING POINT COORDINATES XF,YF,ZF  ARE CALCULATED. */

/*   RLIM - RADIUS OF A SPHERE (IN RE), DEFINING THE OUTER BOUNDARY OF THE TRACING REGION; */
/*         IF THE FIELD LINE REACHES THAT BOUNDARY FROM INSIDE, ITS OUTBOUND TRACING IS */
/*         TERMINATED AND THE CROSSING POINT COORDINATES XF,YF,ZF ARE CALCULATED. */

/*   IOPT - A MODEL INDEX; CAN BE USED FOR SPECIFYING A VERSION OF THE EXTERNAL FIELD */
/*       MODEL (E.G., A NUMBER OF THE KP-INDEX INTERVAL). ALTERNATIVELY, ONE CAN USE THE ARRAY */
/*       PARMOD FOR THAT PURPOSE (SEE BELOW); IN THAT CASE IOPT IS JUST A DUMMY PARAMETER. */

/*   PARMOD -  A 10-ELEMENT ARRAY CONTAINING INPUT PARAMETERS NEEDED FOR A UNIQUE */
/*      SPECIFICATION OF THE EXTERNAL FIELD MODEL. THE CONCRETE MEANING OF THE COMPONENTS */
/*      OF PARMOD DEPENDS ON A SPECIFIC VERSION OF THAT MODEL. */

/*   EXNAME - NAME OF A SUBROUTINE PROVIDING COMPONENTS OF THE EXTERNAL MAGNETIC FIELD */
/*    (E.G., T89, OR T96_01, ETC.). */
/*   INNAME - NAME OF A SUBROUTINE PROVIDING COMPONENTS OF THE INTERNAL MAGNETIC FIELD */
/*    (EITHER DIP_08 OR IGRF_GSW_08). */

/*   LMAX - MAXIMAL LENGTH OF THE ARRAYS XX,YY,ZZ, IN WHICH COORDINATES OF THE FIELD */
/*          LINE POINTS ARE STORED. LMAX SHOULD BE SET EQUAL TO THE ACTUAL LENGTH OF */
/*          THE ARRAYS, DEFINED IN THE MAIN PROGRAM AS ACTUAL ARGUMENTS OF THIS SUBROUTINE. */

/* -------------- OUTPUT PARAMETERS: */

/*   XF,YF,ZF - GSW COORDINATES OF THE ENDPOINT OF THE TRACED FIELD LINE. */
/*   XX,YY,ZZ - ARRAYS OF LENGTH LMAX, CONTAINING COORDINATES OF THE FIELD LINE POINTS. */
/*   L - ACTUAL NUMBER OF FIELD LINE POINTS, GENERATED BY THIS SUBROUTINE. */

extern "C" { int trace_08__(real *xi, real *yi, real *zi, real *dir, 
							real *dsmax, real *err, real *rlim, real *r0, integer *iopt, real *parmod, 
							S_fp exname, S_fp inname__, real *xf, real *yf, real *zf, real *xx, 
							real *yy, real *zz, integer *l, integer *lmax); }

//----------------------------------------------------------------------------------------------------
/*   CONVERTS SPHERICAL COORDS INTO CARTESIAN ONES AND VICE VERSA */
/*    (THETA AND PHI IN RADIANS). */

/*                  J>0            J<0 */
/* -----INPUT:   J,R,THETA,PHI     J,X,Y,Z */
/* ----OUTPUT:      X,Y,Z        R,THETA,PHI */

/*  NOTE: AT THE POLES (X=0 AND Y=0) WE ASSUME PHI=0 WHEN CONVERTING */
/*        FROM CARTESIAN TO SPHERICAL COORDS (I.E., FOR J<0) */
extern "C" { int sphcar_08__(real *r__, real *theta, real *phi, real *x, 
							 real *y, real *z__, integer *j); }

//----------------------------------------------------------------------------------------------------
/* CONVERTS GEOGRAPHIC (GEO) TO GEOCENTRIC SOLAR-WIND (GSW) COORDINATES OR VICE VERSA. */

/*                   J>0                   J<0 */
/* ----- INPUT:  J,XGEO,YGEO,ZGEO    J,XGSW,YGSW,ZGSW */
/* ---- OUTPUT:    XGSW,YGSW,ZGSW      XGEO,YGEO,ZGEO */

/*  ATTENTION:  SUBROUTINE  RECALC_08  MUST BE INVOKED BEFORE GEOGSW_08 IN THREE CASES: */
/*     /A/  BEFORE THE FIRST TRANSFORMATION OF COORDINATES, OR */
/*     /B/  IF THE VALUES OF IYEAR,IDAY,IHOUR,MIN,ISEC  HAVE CHANGED, AND/OR */
/*     /C/  IF THE VALUES OF COMPONENTS OF THE SOLAR WIND FLOW VELOCITY HAVE CHANGED */

/*  NOTE: THIS SUBROUTINE CONVERTS GEO VECTORS TO AND FROM THE SOLAR-WIND GSW COORDINATE */
/*        SYSTEM, TAKING INTO ACCOUNT POSSIBLE DEFLECTIONS OF THE SOLAR WIND DIRECTION FROM */
/*        STRICTLY RADIAL.  BEFORE CONVERTING TO/FROM STANDARD GSM COORDINATES, INVOKE RECALC_08 */
/*        WITH VGSEX=-400.0 and VGSEY=0.0, VGSEZ=0.0 */

extern "C" { int geogsw_08__(real *xgeo, real *ygeo, real *zgeo, 
							 real *xgsw, real *ygsw, real *zgsw, integer *j); }

//----------------------------------------------------------------------------------------------------
/*  CALCULATES COMPONENTS OF THE MAIN (INTERNAL) GEOMAGNETIC FIELD IN THE GEOCENTRIC SOLAR-WIND */
/*  (GSW) COORDINATE SYSTEM, USING IAGA INTERNATIONAL GEOMAGNETIC REFERENCE MODEL COEFFICIENTS */
/*  (e.g., http://www.ngdc.noaa.gov/IAGA/vmod/igrf.html, revised 22 March, 2005) */

/*  THE GSW SYSTEM IS ESSENTIALLY SIMILAR TO THE STANDARD GSM (THE TWO SYSTEMS BECOME IDENTICAL */
/*  TO EACH OTHER IN THE CASE OF STRICTLY ANTI-SUNWARD SOLAR WIND FLOW). FOR A DETAILED */
/*  DEFINITION, SEE INTRODUCTORY COMMENTS FOR THE SUBROUTINE GSWGSE_08 . */

/*  BEFORE THE FIRST CALL OF THIS SUBROUTINE, OR, IF THE DATE/TIME (IYEAR,IDAY,IHOUR,MIN,ISEC), */
/*  OR THE SOLAR WIND VELOCITY COMPONENTS (VGSEX,VGSEY,VGSEZ) HAVE CHANGED, THE MODEL COEFFICIENTS */
/*  AND GEO-GSW ROTATION MATRIX ELEMENTS SHOULD BE UPDATED BY CALLING THE SUBROUTINE RECALC_08. */

/* -----INPUT PARAMETERS: */

/*     XGSW,YGSW,ZGSW - CARTESIAN GEOCENTRIC SOLAR-WIND COORDINATES (IN UNITS RE=6371.2 KM) */

/* -----OUTPUT PARAMETERS: */

/*     HXGSW,HYGSW,HZGSW - CARTESIAN GEOCENTRIC SOLAR-WIND COMPONENTS OF THE MAIN GEOMAGNETIC */
/*                           FIELD IN NANOTESLA */

/*     LAST MODIFICATION:  FEB 07, 2008. */
/*     THIS VERSION OF THE CODE ACCEPTS DATES FROM 1965 THROUGH 2010. */

/*     AUTHOR: N. A. TSYGANENKO */
extern "C" {int igrf_gsw_08__(real *xgsw, real *ygsw, real *zgsw, real *
							  hxgsw, real *hygsw, real *hzgsw); }

//----------------------------------------------------------------------------------------------------
/*  CALCULATES GSW (GEOCENTRIC SOLAR-WIND) COMPONENTS OF GEODIPOLE FIELD WITH THE DIPOLE MOMENT */
/*  CORRESPONDING TO THE EPOCH, SPECIFIED BY CALLING SUBROUTINE RECALC_08 (SHOULD BE */
/*  INVOKED BEFORE THE FIRST USE OF THIS ONE, OR IF THE DATE/TIME, AND/OR THE OBSERVED */
/*  SOLAR WIND DIRECTION, HAVE CHANGED. */

/*  THE GSW COORDINATE SYSTEM IS ESSENTIALLY SIMILAR TO THE STANDARD GSM (THE TWO SYSTEMS BECOME */
/*  IDENTICAL TO EACH OTHER IN THE CASE OF STRICTLY RADIAL ANTI-SUNWARD SOLAR WIND FLOW). ITS */
/*  DETAILED DEFINITION IS GIVEN IN INTRODUCTORY COMMENTS FOR THE SUBROUTINE GSWGSE_08 . */
/* --INPUT PARAMETERS: XGSW,YGSW,ZGSW - GSW COORDINATES IN RE (1 RE = 6371.2 km) */

/* --OUTPUT PARAMETERS: BXGSW,BYGSW,BZGSW - FIELD COMPONENTS IN GSW SYSTEM, IN NANOTESLA. */

/*  LAST MODIFICATION: JAN 28, 2008. */

/*  AUTHOR: N. A. TSYGANENKO */

extern "C" {int dip_08__(real *xgsw, real *ygsw, real *zgsw, real *bxgsw,
						 real *bygsw, real *bzgsw); }

extern "C" {int igrf_geo_08__(real *r__, real *theta, real *phi, 
							  real *br, real *btheta, real *bphi); }

extern "C" {int sun_08__(integer *iyear, integer *iday, integer *ihour, 
						integer *min__, integer *isec, real *gst, real *slong, real *srasn, 
						real *sdec); }

extern "C" {int bspcar_08__(real *theta, real *phi, real *br, 
							real *btheta, real *bphi, real *bx, real *by, real *bz); }

extern "C" {int bcarsp_08__(real *x, real *y, real *z__, real *bx, 
							real *by, real *bz, real *br, real *btheta, real *bphi); }

extern "C" {int gswgse_08__(real *xgsw, real *ygsw, real *zgsw, 
							real *xgse, real *ygse, real *zgse, integer *j); }

extern "C" {int geomag_08__(real *xgeo, real *ygeo, real *zgeo, 
							real *xmag, real *ymag, real *zmag, integer *j); }

extern "C" {int geigeo_08__(real *xgei, real *ygei, real *zgei, 
							real *xgeo, real *ygeo, real *zgeo, integer *j); }

extern "C" {int magsm_08__(real *xmag, real *ymag, real *zmag, real *xsm,
						   real *ysm, real *zsm, integer *j); }

extern "C" {int smgsw_08__(real *xsm, real *ysm, real *zsm, real *xgsw, 
						   real *ygsw, real *zgsw, integer *j); }

extern "C" {int geodgeo_08__(real *h__, real *xmu, real *r__, 
							 real *theta, integer *j); }

extern "C" {int rhand_08__(real *x, real *y, real *z__, real *r1, 
						   real *r2, real *r3, integer *iopt, real *parmod, S_fp exname, S_fp inname__); }

extern "C" {int step_08__(real *x, real *y, real *z__, real *ds, 
						  real *dsmax, real *errin, integer *iopt, real *parmod, S_fp exname, S_fp inname__);}

extern "C" {int shuetal_mgnp_08__(real *xn_pd__, real *vel, real *bzimf, 
								  real *xgsw, real *ygsw, real *zgsw, real *xmgnp, real *ymgnp, 
								  real *zmgnp, real *dist, integer *id); }

extern "C" {int t96_mgnp_08__(real *xn_pd__, real *vel, real *xgsw, 
							  real *ygsw, real *zgsw, real *xmgnp, real *ymgnp, real *zmgnp, real *dist, 
							  integer *id); }
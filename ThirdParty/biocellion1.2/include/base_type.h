/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__

#include <float.h>
#include <limits.h>
#include <math.h>

#if REAL_IS_FLOAT

#define REAL float
#define REAL_MIN FLT_MIN
#define REAL_MAX FLT_MAX
#define REAL_EPSILON FLT_EPSILON

#define ROUND( x ) roundf( x )
#define FLOOR( x ) floorf( x )
#define CEIL( x ) ceilf( x )
#define FABS( x ) fabsf( x )
#define POW( x, y ) powf( x, y )
#define EXP( x ) expf( x )
#define LOG( x ) logf( x )
#define SQRT( x ) sqrtf( x )
#define CBRT( x ) cbrtf( x )
#define SIN( x ) sinf( x )
#define COS( x ) cosf( x )
#define TAN( x ) tanf( x )
#define ASIN( x ) asinf( x )
#define ACOS( x ) acosf( x )
#define ATAN( x ) atanf( x )
#define FMIN( x, y ) fminf( x, y )
#define FMAX( x, y ) fmaxf( x, y )

#else

#define REAL double
#define REAL_MIN DBL_MIN
#define REAL_MAX DBL_MAX
#define REAL_EPSILON DBL_EPSILON

#define ROUND( x ) round( x )
#define FLOOR( x ) floor( x )
#define CEIL( x ) ceil( x )
#define FABS( x ) fabs( x )
#define POW( x, y ) pow( x, y )
#define EXP( x ) exp( x )
#define LOG( x ) log( x )
#define SQRT( x ) sqrt( x )
#define CBRT( x ) cbrt( x )
#define SIN( x ) sin( x )
#define COS( x ) cos( x )
#define TAN( x ) tan( x )
#define ASIN( x ) asin( x )
#define ACOS( x ) acos( x )
#define ATAN( x ) atan( x )
#define FMIN( x, y ) fmin( x, y )
#define FMAX( x, y ) fmax( x, y )

#endif

#define FABS80( x ) ( ( ( x ) >= 0.0 )? ( x ) : -( x ) )
#define POW80( x, y ) powl( x, y )
#define COS80( x ) cosl( x )
#define ACOS80( x ) acosl( x )
#define SQRT80( x ) sqrtl( x )
#define CBRT80( x ) cbrtl( x )
#define FMIN80( x, y ) ( ( ( x ) <= ( y ) )? ( x ) : ( y ) )
#define FMAX80( x, y ) ( ( ( x ) >= ( y ) )? ( x ) : ( y ) )

#define MY_PI 3.14159265358979323846

static inline REAL FSIGN( REAL x );

#define U8 unsigned char
#define U8_MAX UCHAR_MAX
#define S8 char
#define S8_MAX SCHAR_MAX
#define S8_MIN SCHAR_MIN

#define U16 unsigned short
#define U16_MAX USHRT_MAX
#define S16 short
#define S16_MAX SHRT_MAX
#define S16_MIN SHRT_MIN

#define U32 unsigned int
#define U32_MAX UINT_MAX
#define S32 int
#define S32_MAX INT_MAX
#define S32_MIN INT_MIN

#define U64 unsigned long long
#define U64_MAX ULLONG_MAX
#define S64 long long
#define S64_MAX LLONG_MAX
#define S64_MIN LLONG_MIN

#define BOOL U8

#define idx_t S16/* maximum grid size at the interface level = 2^15 - 1 in each dimension, IDX_T_SIZE needs to be set to sizeof( idx_t ) */
#define IDX_T_SIZE 2/* should be set to sizeof( idx_t ) */
#define IDX_T_MAX S16_MAX/* should be the maximum value of idx_t */

#define IMAX( x, y ) ( ( x >= y )? x : y )
#define IMIN( x, y ) ( ( x <= y )? x : y )
#define IABS( x ) ( ( x < 0 )? ( ( x ) * -1 ) : x )

static inline REAL FSIGN( REAL x )  __attribute__( ( always_inline ) );

static inline REAL FSIGN( REAL x ) {
	if( x > 0.0 ) {
		return 1.0;
	}
	else if( x < 0.0 ) {
		return -1.0;
	}
	else {
		return 0.0;
	}
}

#endif/* #ifndef __BASE_TYPE_H__ */


/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <assert.h>

#include <string>

#include "base_type.h"
#include "dim_type.h"
#include "info.h"

static const S32 COMPUTE_SPHERE_UB_VOL_OVLP_MAX_LEVEL = 7;/* sets the resolution of the computeSphereUBVolOvlpRatio functions, divide the sphere bounding box to the ( 1 << COMPUTE_SPHERE_UB_VOL_OVLP_MAX_LEVEL ) x ( 1 << COMPUTE_SPHERE_UB_VOL_OVLP_MAX_LEVEL ) x ( 1 << COMPUTE_SPHERE_UB_VOL_OVLP_MAX_LEVEL ) sub-boxes */
static const REAL COMPUTE_SPHERE_UB_VOL_OVLP_MIN_RADIUS_RATIO = 0.01;/* if the radius of a sphere is smaller than the interface grid spcing multiplied by COMPUTE_SPHERE_UB_VOL_OVLP_MIN_RADIUS_RATIO, Biocellion assumes that the sphere belongs to only one box */
#if REAL_IS_FLOAT
static const REAL COMPUTE_SPHERE_UB_VOL_OVLP_MIN_RADIUS_VAL = 1e-10;/* if the radius of a sphere is smaller than COMPUTE_SPHERE_UB_VOL_OVLP_MIN_RADIUS_VAL, Biocellion assumes that the sphere belongs to only one box */
#else
static const REAL COMPUTE_SPHERE_UB_VOL_OVLP_MIN_RADIUS_VAL = 1e-100;/* if the radius of a sphere is smaller than COMPUTE_SPHERE_UB_VOL_OVLP_MIN_RADIUS_VAL, Biocellion assumes that the sphere belongs to only one box */
#endif

class Util {
public:
#if THIS_IS_LIBMODEL
	static inline REAL getModelRand( const S32 idx ) __attribute__( ( always_inline ) );

	static inline void computeSphereUBVolOvlpRatio( const S32 maxLevel/* sets the resolution */, const VReal& vOffset, const REAL radius, REAL aaa_ratio[3][3][3] ) __attribute__( ( always_inline ) );
	static inline REAL computeSphereUBVolOvlpRatio( const S32 maxLevel/* sets the resolution */, const VReal& vOffset, const REAL radius, const VIdx& ubVIdxOffset ) __attribute__( ( always_inline ) );

	static inline void changePosFormat2LvTo1Lv( const VIdx& vIdx, const VReal& vOffset, VReal& vPos ) __attribute__( ( always_inline ) );
	static inline void changePosFormat1LvTo2Lv( const VReal& vPos, VIdx& vIdx, VReal& vOffset ) __attribute__( ( always_inline ) );
#endif

private:
	static Vector<Vector<Vector<S32> > > vvv_computeSphereUBVolOvlpNumValidMinBoxes;

	static REAL getModelRandNoInputCheck( const S32 idx );

	static void initSphereUBVolOvlpRatioData( void );
	static void computeSphereUBVolOvlpRatioNoInputCheck( const S32 maxLevel/* sets the resolution */, const VReal& vOffset, const REAL radius, REAL aaa_ratio[3][3][3] );
	static REAL computeSphereUBVolOvlpRatioNoInputCheck( const S32 maxLevel/* sets the resolution */, const VReal& vOffset, const REAL radius, const VIdx& ubVIdxOffset );

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
#endif
};

#if THIS_IS_LIBMODEL
inline REAL Util::getModelRand( const S32 idx ) {
	CHECK( idx < Info::getNumModelRNGs() );
	return Util::getModelRandNoInputCheck( idx );
}

inline void Util::computeSphereUBVolOvlpRatio( const S32 maxLevel, const VReal& vOffset, const REAL radius, REAL aaa_ratio[3][3][3] ) {
	CHECK( maxLevel >= 0 );
	CHECK( maxLevel <= COMPUTE_SPHERE_UB_VOL_OVLP_MAX_LEVEL );
	CHECK( radius > 0.0 );
	CHECK( radius <= Info::ifGridSpacing * 0.5 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( vOffset[dim] >= Info::ifGridSpacing * -0.5 ) && ( vOffset[dim] <= Info::ifGridSpacing * 0.5 ) );
	}

	return Util::computeSphereUBVolOvlpRatioNoInputCheck( maxLevel, vOffset, radius, aaa_ratio );
}

inline REAL Util::computeSphereUBVolOvlpRatio( const S32 maxLevel, const VReal& vOffset, const REAL radius, const VIdx& ubVIdxOffset ) {
	CHECK( maxLevel >= 0 );
	CHECK( maxLevel <= COMPUTE_SPHERE_UB_VOL_OVLP_MAX_LEVEL );
	CHECK( radius > 0.0 );
	CHECK( radius <= Info::ifGridSpacing * 0.5 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( vOffset[dim] >= Info::ifGridSpacing * -0.5 ) && ( vOffset[dim] <= Info::ifGridSpacing * 0.5 ) );
		CHECK( ( ubVIdxOffset[dim] >= -1 ) && ( ubVIdxOffset[dim] <= 1 ) );
	}

	return computeSphereUBVolOvlpRatioNoInputCheck( maxLevel, vOffset, radius, ubVIdxOffset );
}

inline void Util::changePosFormat2LvTo1Lv( const VIdx& vIdx, const VReal& vOffset, VReal& vPos ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vPos[dim] = ( ( REAL )vIdx[dim] + 0.5 ) * Info::ifGridSpacing + vOffset[dim];
	}
	return;
}

inline void Util::changePosFormat1LvTo2Lv( const VReal& vPos, VIdx& vIdx, VReal& vOffset ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx[dim] = ( idx_t )FLOOR( vPos[dim] / Info::ifGridSpacing );
		vOffset[dim] = vPos[dim] - ( ( REAL )vIdx[dim] + 0.5 ) * Info::ifGridSpacing;
		if( vOffset[dim] > Info::ifGridSpacing * 0.5 ) {/* due to the limited resolution of floating point number */
			vOffset[dim] = Info::ifGridSpacing * 0.5;
		}
		else if( vOffset[dim] < Info::ifGridSpacing * -0.5 ) {/* due to the limited resolution of floating point number */
			vOffset[dim] = Info::ifGridSpacing * -0.5;
		}
	}
	return;
}
#endif

#endif/* #ifndef __UTIL_H__ */


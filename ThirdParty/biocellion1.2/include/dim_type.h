/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __DIM_TYPE_H__
#define __DIM_TYPE_H__

#include <float.h>
#include <limits.h>

#include "base_type.h"

/* class definitions */

class VIdx {
public:
	static const VIdx ZERO;
	static const VIdx UNIT;
	static const VIdx A_BASIS[DIMENSION];
	
public:
	inline VIdx( void ) __attribute__( ( always_inline ) );
	inline VIdx( idx_t x, idx_t y, idx_t z ) __attribute__( ( always_inline ) );
	inline ~VIdx( void ) __attribute__( ( always_inline ) );

	inline VIdx operator+( const idx_t delta ) const __attribute__( ( always_inline ) );
	inline VIdx& operator+=( const idx_t delta ) __attribute__( ( always_inline ) );
	inline VIdx operator+( const VIdx& vDelta ) const __attribute__( ( always_inline ) );
	inline VIdx& operator+=( const VIdx& vDelta ) __attribute__( ( always_inline ) );
	inline VIdx operator-( const idx_t delta ) const __attribute__( ( always_inline ) );
	inline VIdx& operator-=( const idx_t delta ) __attribute__( ( always_inline ) );
	inline VIdx operator-( const VIdx& vDelta ) const __attribute__( ( always_inline ) );
	inline VIdx& operator-=( const VIdx& vDelta ) __attribute__( ( always_inline ) );
	inline VIdx operator*( const idx_t scale ) const __attribute__( ( always_inline ) );
	inline VIdx& operator*=( const idx_t scale ) __attribute__( ( always_inline ) );
	inline VIdx operator*( const VIdx& vScale ) const __attribute__( ( always_inline ) );
	inline VIdx& operator*=( const VIdx& vScale ) __attribute__( ( always_inline ) );
	inline VIdx operator/( const idx_t scale ) const __attribute__( ( always_inline ) );
	inline VIdx& operator/=( const idx_t scale ) __attribute__( ( always_inline ) );
	inline VIdx operator/( const VIdx& vScale ) const __attribute__( ( always_inline ) );
	inline VIdx& operator/=( const VIdx& vScale ) __attribute__( ( always_inline ) );
	inline BOOL operator==( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline BOOL operator!=( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline BOOL operator<( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline BOOL operator<=( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline BOOL operator>( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline BOOL operator>=( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline idx_t& operator[]( const S32 dim ) __attribute__( ( always_inline ) );
	inline const idx_t& operator[]( const S32 dim ) const __attribute__( ( always_inline ) );

	inline VIdx& shift( const S32 dim, const idx_t offset ) __attribute__( ( always_inline ) );
	inline VIdx& shift( const VIdx& vOffset ) __attribute__( ( always_inline ) );
	inline VIdx& diagShift( const idx_t offset ) __attribute__( ( always_inline ) );
	inline VIdx& coarsen( const idx_t ratio ) __attribute__( ( always_inline ) );
	inline VIdx& coarsen( const VIdx& vRatio ) __attribute__( ( always_inline ) );
	inline VIdx& min( const VIdx& vIdx ) __attribute__( ( always_inline ) );
	inline VIdx& max( const VIdx& vIdx ) __attribute__( ( always_inline ) );
	inline void setVal( const S32 dim, const idx_t val ) __attribute__( ( always_inline ) );

	inline S32 product( void ) const __attribute__( ( always_inline ) );
	inline BOOL lexLT( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline BOOL lexGT( const VIdx& vIdx ) const __attribute__( ( always_inline ) );

	static inline VIdx mult( const VIdx& vIdx, const idx_t scale ) __attribute__( ( always_inline ) );

	static inline VIdx diagShift( const VIdx& vIdx, const idx_t offset ) __attribute__( ( always_inline ) );
	static inline VIdx coarsen( const VIdx& vIdx, const idx_t ratio ) __attribute__( ( always_inline ) );

	static inline S64 getIdx3DTo1D( const VIdx& vIdx, const VIdx& regionSize ) __attribute__( ( always_inline ) );
	static inline S64 getIdx3DTo1D( const VIdx& vIdx, const idx_t size ) __attribute__( ( always_inline ) );
	static inline S64 getIdx3DTo1D( const idx_t i, const idx_t j, const idx_t k, const VIdx& regionSize ) __attribute__( ( always_inline ) );
	static inline S64 getIdx3DTo1D( const idx_t i, const idx_t j, const idx_t k, const idx_t size ) __attribute__( ( always_inline ) );
	static inline VIdx getIdx1DTo3D( const S64 idx, const VIdx& regionSize ) __attribute__( ( always_inline ) );
	static inline VIdx getIdx1DTo3D( const S64 idx, const idx_t size ) __attribute__( ( always_inline ) );

private:
	idx_t a_idx[DIMENSION];
};

class VReal {
public:
	static const VReal ZERO;
	static const VReal UNIT;
	static const VReal A_BASIS[DIMENSION];

public:
	inline VReal( void ) __attribute__( ( always_inline ) );
	inline VReal( REAL x, REAL y, REAL z ) __attribute__( ( always_inline ) );
	inline ~VReal( void ) __attribute__( ( always_inline ) );

	inline VReal operator+( const REAL delta ) const __attribute__( ( always_inline ) );
	inline VReal& operator+=( const REAL delta ) __attribute__( ( always_inline ) );
	inline VReal operator+( const VReal& vDelta ) const __attribute__( ( always_inline ) );
	inline VReal& operator+=( const VReal& vDelta ) __attribute__( ( always_inline ) );
	inline VReal operator-( const REAL delta ) const __attribute__( ( always_inline ) );
	inline VReal& operator-=( const REAL delta ) __attribute__( ( always_inline ) );
	inline VReal operator-( const VReal& vDelta ) const __attribute__( ( always_inline ) );
	inline VReal& operator-=( const VReal& vDelta ) __attribute__( ( always_inline ) );
	inline VReal operator*( const REAL scale ) const __attribute__( ( always_inline ) );
	inline VReal& operator*=( const REAL scale ) __attribute__( ( always_inline ) );
	inline VReal operator/( const REAL scale ) const __attribute__( ( always_inline ) );
	inline VReal& operator/=( const REAL scale ) __attribute__( ( always_inline ) );
	inline REAL dotProduct( const VReal vOther ) const __attribute__( ( always_inline ) );
	inline REAL& operator[]( const S32 dim ) __attribute__( ( always_inline ) );
	inline const REAL& operator[]( const S32 dim ) const __attribute__( ( always_inline ) );

	inline REAL length( void ) const __attribute__( ( always_inline ) );
	inline REAL lengthSquare( void ) const __attribute__( ( always_inline ) );/* avoid SQRT(), so computationally cheaper than length() */

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
	inline REAL* getValPtr( void ) __attribute__( ( always_inline ) );
	inline const REAL* getValPtr( void ) const __attribute__( ( always_inline ) );
#endif

	static inline VReal crossProduct( const VReal& vLeft, const VReal& vRight ) __attribute__( ( always_inline ) );/* returns vLeft X vRight */
	static inline VReal rotate( const VReal& vNormalizedAxisDir, const VReal& point, const REAL theta ) __attribute__( ( always_inline ) );/* rotates point around the axis defined by vNormalizedAxisDir by theta (counter-clockwise, right-handed rule) */
	static inline VReal normalize( const REAL epsilon/* return VReal::ZERO if the magnitude of vUnnormalized is smaller than epsilon */, const VReal&  vUnnormalized ) __attribute__( ( always_inline ) );

private:
	REAL a_val[DIMENSION];
};

inline VIdx::VIdx( void ) {
	this->a_idx[0] = 0;
	this->a_idx[1] = 0;
	this->a_idx[2] = 0;
}

inline VIdx::VIdx( idx_t x, idx_t y, idx_t z ) {
	this->a_idx[0] = x;
	this->a_idx[1] = y;
	this->a_idx[2] = z;
}

inline VIdx::~VIdx( void ) {
	/* nothing to do */
}

inline VIdx VIdx::operator+( const idx_t delta ) const {
	VIdx vIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] + delta );
	}
	return vIdx;
}

inline VIdx& VIdx::operator+=( const idx_t delta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] + delta );
	}
	return *this;
}

inline VIdx VIdx::operator+( const VIdx& vDelta ) const {
	VIdx vIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] + vDelta.a_idx[dim] );
	}
	return vIdx;
}

inline VIdx& VIdx::operator+=( const VIdx& vDelta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] + vDelta.a_idx[dim] );
	}
	return *this;
}

inline VIdx VIdx::operator-( const idx_t delta ) const {
	VIdx vIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] - delta );
	}
	return vIdx;
}

inline VIdx& VIdx::operator-=( const idx_t delta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] - delta );
	}
	return *this;
}

inline VIdx VIdx::operator-( const VIdx& vDelta ) const {
	VIdx vIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] - vDelta.a_idx[dim] );
	}
	return vIdx;
}

inline VIdx& VIdx::operator-=( const VIdx& vDelta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] - vDelta.a_idx[dim] );
	}
	return *this;
}

inline VIdx VIdx::operator*( const idx_t scale ) const {
	VIdx vIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] * scale );
	}
	return vIdx;
}

inline VIdx& VIdx::operator*=( const idx_t scale ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] * scale );
	}
	return *this;
}

inline VIdx VIdx::operator*( const VIdx& vScale ) const {
	VIdx vIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] * vScale.a_idx[dim] );
	}
	return vIdx;
}

inline VIdx& VIdx::operator*=( const VIdx& vScale ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] * vScale.a_idx[dim] );
	}
	return *this;
}

inline VIdx VIdx::operator/( const idx_t scale ) const {
	VIdx vIdx;
	CHECK( scale != 0 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] / scale );
	}
	return vIdx;
}

inline VIdx& VIdx::operator/=( const idx_t scale ) {
	CHECK( scale != 0 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] / scale );
	}
	return *this;
}

inline VIdx VIdx::operator/( const VIdx& vScale ) const {
	VIdx vIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( vScale.a_idx[dim] != 0 );
		vIdx.a_idx[dim] = ( idx_t )( this->a_idx[dim] / vScale.a_idx[dim] );
	}
	return vIdx;
}

inline VIdx& VIdx::operator/=( const VIdx& vScale ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( vScale.a_idx[dim] != 0 );
		this->a_idx[dim] = ( idx_t )( this->a_idx[dim] / vScale.a_idx[dim] );
	}
	return *this;
}

inline BOOL VIdx::operator==( const VIdx& vIdx ) const {
	BOOL ret = true;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] != vIdx.a_idx[dim] ) {
			ret = false;
			break;
		}
	}
	return ret;
}

inline BOOL VIdx::operator!=( const VIdx& vIdx ) const {
	BOOL ret = false;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] != vIdx.a_idx[dim] ) {
			ret = true;
			break;
		}
	}
	return ret;
}

inline BOOL VIdx::operator<( const VIdx& vIdx ) const {
	BOOL ret = true;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] >= vIdx.a_idx[dim] ) {
			ret = false;
			break;
		}
	}
	return ret;
}

inline BOOL VIdx::operator<=( const VIdx& vIdx ) const {
	BOOL ret = true;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] > vIdx.a_idx[dim] ) {
			ret = false;
			break;
		}
	}
	return ret;
}

inline BOOL VIdx::operator>( const VIdx& vIdx ) const {
	BOOL ret = true;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] <= vIdx.a_idx[dim] ) {
			ret = false;
			break;
		}
	}
	return ret;
}

inline BOOL VIdx::operator>=( const VIdx& vIdx ) const {
	BOOL ret = true;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] < vIdx.a_idx[dim] ) {
			ret = false;
			break;
		}
	}
	return ret;
}

inline idx_t& VIdx::operator[]( const S32 dim ) {
	CHECK( ( dim >= 0 ) && ( dim < DIMENSION ) );
	return this->a_idx[dim];
}

inline const idx_t& VIdx::operator[]( const S32 dim ) const {
	CHECK( ( dim >= 0 ) && ( dim < DIMENSION ) );
	return this->a_idx[dim];
}

inline VIdx& VIdx::shift( const S32 dim, const idx_t offset ) {
	CHECK( ( dim >= 0 ) && ( dim < DIMENSION ) );
	this->a_idx[dim] += offset;
	return *this;
}

inline VIdx& VIdx::shift( const VIdx& vOffset ) {
	*this += vOffset;
	return *this;
}

inline VIdx& VIdx::diagShift( const idx_t offset ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_idx[dim] += offset;
	}
	return *this;
}

inline VIdx& VIdx::coarsen( const idx_t ratio ) {
	CHECK( ratio > 0 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] < 0 ) {
			this->a_idx[dim] = ( this->a_idx[dim] + 1 ) / ratio - 1;
		}
		else {
			this->a_idx[dim] = this->a_idx[dim] / ratio;
		}
	}
	return *this;
}

inline VIdx& VIdx::coarsen( const VIdx& vRatio ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( vRatio.a_idx[dim] > 0 );
		if( this->a_idx[dim] < 0 ) {
			this->a_idx[dim] = ( this->a_idx[dim] + 1 ) / vRatio.a_idx[dim] - 1;
		}
		else {
			this->a_idx[dim] = this->a_idx[dim] / vRatio.a_idx[dim];
		}
	}
	return *this;
}

inline VIdx& VIdx::min( const VIdx& vIdx ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] > vIdx.a_idx[dim] ) {
			this->a_idx[dim] = vIdx.a_idx[dim];
		}
	}
	return *this;
}

inline VIdx& VIdx::max( const VIdx& vIdx ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( this->a_idx[dim] < vIdx.a_idx[dim] ) {
			this->a_idx[dim] = vIdx.a_idx[dim];
		}
	}
	return *this;
}

inline void VIdx::setVal( const S32 dim, const idx_t val ) {
	this->a_idx[dim] = val;
	return;
}

inline S32 VIdx::product( void ) const {
	CHECK( ( S64 )this->a_idx[0] * ( S64 )this->a_idx[1] * ( S64 )this->a_idx[2] <= S32_MAX );
	return ( ( S32 )this->a_idx[0] * ( S32 )this->a_idx[1] * ( S32 )this->a_idx[2] );
}

inline BOOL VIdx::lexLT( const VIdx& vIdx ) const {
	if( this->a_idx[0] < vIdx.a_idx[0] ) {
		return true;
	}
	else if( this->a_idx[0] > vIdx.a_idx[0] ) {
		return false;
	}
	else if( this->a_idx[1] < vIdx.a_idx[1] ) {
		return true;
	}
	else if( this->a_idx[1] > vIdx.a_idx[1] ) {
		return false;
	}
	else if( this->a_idx[2] < vIdx.a_idx[2] ) {
		return true;
	}
	else {
		return false;
	}
}

inline BOOL VIdx::lexGT( const VIdx& vIdx ) const {
	if( this->a_idx[0] > vIdx.a_idx[0] ) {
		return true;
	}
	else if( this->a_idx[0] < vIdx.a_idx[0] ) {
		return false;
	}
	else if( this->a_idx[1] > vIdx.a_idx[1] ) {
		return true;
	}
	else if( this->a_idx[1] < vIdx.a_idx[1] ) {
		return false;
	}
	else if( this->a_idx[2] > vIdx.a_idx[2] ) {
		return true;
	}
	else {
		return false;
	}
}

inline VIdx VIdx::mult( const VIdx& vIdx, const idx_t scale ) {
	VIdx retVIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVIdx[dim] = vIdx.a_idx[dim] * scale;
	}
	return retVIdx;
}

inline VIdx VIdx::diagShift( const VIdx& vIdx, const idx_t offset ) {
	VIdx retVIdx;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVIdx[dim] = vIdx.a_idx[dim] + offset;
	}
	return retVIdx;
}

inline VIdx VIdx::coarsen( const VIdx& vIdx, const idx_t ratio ) {
	VIdx retVIdx;
	CHECK( ratio > 0 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( vIdx.a_idx[dim] < 0 ) {
			retVIdx[dim] = ( vIdx.a_idx[dim] + 1 ) / ratio - 1;
		}
		else {
			retVIdx[dim] = vIdx.a_idx[dim] / ratio;
		}
	}
	return retVIdx;
}

inline S64 VIdx::getIdx3DTo1D( const VIdx& vIdx, const VIdx& regionSize ) {
	CHECK( ( vIdx[0] < regionSize[0] ) && ( vIdx[1] < regionSize[1] ) && ( vIdx[2] < regionSize[2] ) );
	return ( ( S64 )( vIdx[0] ) * ( S64 )( regionSize[1] ) * ( S64 )( regionSize[2] ) + ( S64 )( vIdx[1] ) * ( S64 )( regionSize[2] ) + ( S64 )( vIdx[2] ) );
}

inline S64 VIdx::getIdx3DTo1D( const VIdx& vIdx, const idx_t size ) {
	CHECK( ( vIdx[0] < size ) && ( vIdx[1] < size ) && ( vIdx[2] < size ) );
	return ( ( S64 )( vIdx[0] ) * ( S64 )( size ) * ( S64 )( size ) + ( S64 )( vIdx[1] ) * ( S64 )( size ) + ( S64 )( vIdx[2] ) );
}

inline S64 VIdx::getIdx3DTo1D( const idx_t i, const idx_t j, const idx_t k, const VIdx& regionSize ) {
	CHECK( ( i < regionSize[0] ) && ( j < regionSize[1] ) && ( k < regionSize[2] ) );
	return ( ( S64 )( i ) * ( S64 )( regionSize[1] ) * ( S64 )( regionSize[2] ) + ( S64 )( j ) * ( S64 )( regionSize[2] ) + ( S64 )( k ) );
}

inline S64 VIdx::getIdx3DTo1D( const idx_t i, const idx_t j, const idx_t k, const idx_t size ) {
	CHECK( ( i < size ) && ( j < size ) && ( k < size ) );
	return ( ( S64 )( i ) * ( S64 )( size ) * ( S64 )( size ) + ( S64 )( j ) * ( S64 )( size ) + ( S64 )( k ) );
}

inline VIdx VIdx::getIdx1DTo3D( const S64 idx, const VIdx& regionSize ) {
	VIdx vIdx;
	S64 tmp = idx;
	for( S32 dim = DIMENSION - 1 ; dim >= 0 ; dim-- ) {
		vIdx[dim] = ( idx_t )( tmp % regionSize[dim] );
		CHECK( ( S64 )vIdx[dim] == ( tmp % regionSize[dim] ) );/* no overflow */
		tmp /= regionSize[dim];
	}
	CHECK( tmp == 0 );

	return vIdx;
}

inline VIdx VIdx::getIdx1DTo3D( const S64 idx, const idx_t size ) {
	VIdx vIdx;
	S64 tmp = idx;
	for( S32 dim = DIMENSION - 1 ; dim >= 0 ; dim-- ) {
		vIdx[dim] = ( idx_t )( tmp % size );
		CHECK( ( S64 )vIdx[dim] == ( tmp % size ) );/* no overflow */
		tmp /= size;
	}
	CHECK( tmp == 0 );

	return vIdx;
}

inline VReal::VReal( void ) {
	this->a_val[0] = 0.0;
	this->a_val[1] = 0.0;
	this->a_val[2] = 0.0;
}

inline VReal::VReal( REAL x, REAL y, REAL z ) {
	this->a_val[0] = x;
	this->a_val[1] = y;
	this->a_val[2] = z;
}

inline VReal::~VReal( void ) {
	/* nothing to do */
}

inline VReal VReal::operator+( const REAL delta ) const {
	VReal retVReal;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVReal.a_val[dim] = this->a_val[dim] + delta;
	}
	return retVReal;
}

inline VReal& VReal::operator+=( const REAL delta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_val[dim] += delta;
	}
	return *this;
}

inline VReal VReal::operator+( const VReal& vDelta ) const {
	VReal retVReal;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVReal.a_val[dim] = this->a_val[dim] + vDelta.a_val[dim];
	}
	return retVReal;
}

inline VReal& VReal::operator+=( const VReal& vDelta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_val[dim] += vDelta.a_val[dim];
	}
	return *this;
}

inline VReal VReal::operator-( const REAL delta ) const {
	VReal retVReal;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVReal.a_val[dim] = this->a_val[dim] - delta;
	}
	return retVReal;
}

inline VReal& VReal::operator-=( const REAL delta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_val[dim] -= delta;
	}
	return *this;
}

inline VReal VReal::operator-( const VReal& vDelta ) const {
	VReal retVReal;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVReal.a_val[dim] = this->a_val[dim] - vDelta.a_val[dim];
	}
	return retVReal;
}

inline VReal& VReal::operator-=( const VReal& vDelta ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_val[dim] -= vDelta.a_val[dim];
	}
	return *this;
}

inline VReal VReal::operator*( const REAL scale ) const {
	VReal retVReal;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVReal.a_val[dim] = this->a_val[dim] * scale;
	}
	return retVReal;
}

inline VReal& VReal::operator*=( const REAL scale ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_val[dim] *= scale;
	}
	return *this;
}

inline VReal VReal::operator/( const REAL scale ) const {
	VReal retVReal;
	CHECK( FABS( scale ) > 0.0 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVReal.a_val[dim] = this->a_val[dim] / scale;
	}
	return retVReal;
}

inline VReal& VReal::operator/=( const REAL scale ) {
	CHECK( FABS( scale ) > 0.0 );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->a_val[dim] /= scale;
	}
	return *this;
}

inline REAL VReal::dotProduct( const VReal vOther ) const {
	return ( this->a_val[0] * vOther.a_val[0] ) + ( this->a_val[1] * vOther.a_val[1] ) + ( this->a_val[2] * vOther.a_val[2] );
}

inline REAL& VReal::operator[]( const S32 dim ) {
	CHECK( ( dim >= 0 ) && ( dim < DIMENSION ) );
	return this->a_val[dim];
}

inline const REAL& VReal::operator[]( const S32 dim ) const {
	CHECK( ( dim >= 0 ) && ( dim < DIMENSION ) );
	return this->a_val[dim];
}

inline REAL VReal::length( void ) const {
	return SQRT( this->a_val[0] * this->a_val[0] + this->a_val[1] * this->a_val[1] + this->a_val[2] * this->a_val[2] );
}

inline REAL VReal::lengthSquare( void ) const {
	return this->a_val[0] * this->a_val[0] + this->a_val[1] * this->a_val[1] + this->a_val[2] * this->a_val[2];
}

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
inline REAL* VReal::getValPtr( void ) {
	return &( this->a_val[0] );
}

inline const REAL* VReal::getValPtr( void ) const {
	return &( this->a_val[0] );
}
#endif

inline VReal VReal::crossProduct( const VReal& vLeft, const VReal& vRight ) {/* returns vLeft X vRight */
	VReal retVal;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		retVal[dim] = vLeft.a_val[( dim + 1 ) % DIMENSION] * vRight.a_val[( dim + 2 ) % DIMENSION] - vLeft.a_val[( dim + 2 ) % DIMENSION] * vRight.a_val[( dim + 1 ) % DIMENSION];
	}
	return retVal;
}

inline VReal VReal::rotate( const VReal& vNormalizedAxisDir, const VReal& point, const REAL theta ) {/* rotates point around the axis defined by vNormalizedAxisDir by theta (counter-clockwise, right-handed rule) */
	CHECK( FABS( 1.0 - SQRT( vNormalizedAxisDir[0] * vNormalizedAxisDir[0] +  vNormalizedAxisDir[1] * vNormalizedAxisDir[1] +  vNormalizedAxisDir[2] * vNormalizedAxisDir[2] ) ) <= 1e-14 );
	VReal vRot = point * COS( theta ) + VReal::crossProduct( vNormalizedAxisDir, point ) * SIN( theta ) + vNormalizedAxisDir * ( vNormalizedAxisDir.dotProduct( point ) * ( 1.0 - COS( theta ) ) );
	return vRot;
}

inline VReal VReal::normalize( const REAL epsilon/* return VReal::ZERO if the magnitude of vUnnormalized is smaller than epsilon */, const VReal& vUnnormalized ) {
	REAL scale = 0.0;

	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		scale += vUnnormalized[dim] * vUnnormalized[dim];
	}
	scale = SQRT( scale );

	if( scale < epsilon ) {
		return VReal::ZERO;
	}
	else {
		return vUnnormalized / scale;
	}
}

#endif/* #ifndef __DIM_TYPE_H__ */


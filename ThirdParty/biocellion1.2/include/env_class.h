/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __ENV_CLASS_H__
#define __ENV_CLASS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "base_type.h"
#include "vector_type.h"
#include "ext_type.h"
#include "info.h"
#include "report.h"

class UBEnv {
public:
#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
	inline UBEnv( void ) __attribute( ( always_inline ) );
	inline ~UBEnv( void ) __attribute( ( always_inline ) );

	inline void reset( void ) __attribute( ( always_inline ) );
#endif

	inline REAL getPhi( const S32 elemIdx ) const __attribute( ( always_inline ) );/* average if the interface subgrid is finer than the interface grid */
	inline Vector<REAL> getPhiArray( void ) const __attribute( ( always_inline ) );/* average if the interface subgrid is finer than the interface grid */
	inline REAL getSubgridPhi( const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline REAL getSubgridPhi( const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getSubgridPhis( const S32 elemIdx ) const __attribute( ( always_inline ) );/* use VIdx::getIdx3DTo1D() to index return value */
	inline void setPhi( const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void setPhiArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void setSubgridPhi( const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setSubgridPhi( const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setSubgridPhis( const S32 elemIdx, const Vector<REAL>& v_val ) const __attribute( ( always_inline ) );/* use VIdx::getIdx3DTo1D() to index v_val */
	inline void incPhi( const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );/* increase every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void incSubgridPhi( const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );
	inline void incSubgridPhi( const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );

	inline REAL getModelReal( const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( void ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( void ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 elemIdx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 elemIdx, const S32 inc ) __attribute( ( always_inline ) );

private:
	Vector<U8> v_aux;

	friend class NbrUBEnv;

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
	friend class Misc;
#endif
};

class UBEnvModelVar {
public:
#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
	inline UBEnvModelVar( void ) __attribute( ( always_inline ) );
	inline ~UBEnvModelVar( void ) __attribute( ( always_inline ) );

	inline void reset( void ) __attribute( ( always_inline ) );
#endif

	inline REAL getModelReal( const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( void ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( void ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 elemIdx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 elemIdx, const S32 inc ) __attribute( ( always_inline ) );

private:
	Vector<U8> v_aux;

	friend class NbrUBEnvModelVar;

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
	friend class Misc;
#endif
};

class NbrUBEnvAux {
private:
	BOOL a_changed[3 * 3 * 3];/* if any variable is changed */
	Vector<BOOL> av_changed[3 * 3 * 3];
	Vector<S32> av_idx[3 * 3 * 3];/* variable idx within an interface grid box */

	inline NbrUBEnvAux( void ) __attribute( ( always_inline ) );
	inline ~NbrUBEnvAux( void ) __attribute( ( always_inline ) );

	friend class NbrUBEnv;
	friend class NbrUBEnvModelVar;

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
	friend class Misc;
#endif
};

class NbrUBEnv {
public:
#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
	inline NbrUBEnv( void ) __attribute( ( always_inline ) );
	inline ~NbrUBEnv( void ) __attribute( ( always_inline ) );

	inline void allocateAux( void );
	inline void clearAux( void );
#endif

	inline BOOL getValidFlag( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute__( ( always_inline ) );
	inline BOOL getValidFlag( const VIdx& nbrVOffset ) const __attribute__( ( always_inline ) );

	inline REAL getPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );/* average if the interface subgrid is finer than the interface grid */
	inline REAL getPhi( const VIdx& nbrVOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );/* average if the interface subgrid is finer than the interface grid */
	inline Vector<REAL> getPhiArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute( ( always_inline ) );/* average if the interface subgrid is finer than the interface grid */
	inline Vector<REAL> getPhiArray( const VIdx& nbrVOffset ) const __attribute( ( always_inline ) );/* average if the interface subgrid is finer than the interface grid */
	inline REAL getSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline REAL getSubgridPhi( const VIdx& nbrVOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline REAL getSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline REAL getSubgridPhi( const VIdx& nbrVOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getSubgridPhis( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, S32 elemIdx ) const __attribute( ( always_inline ) );/* use VIdx::getIdx3DTo1D() to index return value */
	inline Vector<REAL> getSubgridPhis( const VIdx& nbrVOffset, S32 elemIdx ) const __attribute( ( always_inline ) );/* use VIdx::getIdx3DTo1D() to index return value */
	inline void setPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void setPhi( const VIdx& nbrVOffset, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void setPhiArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void setPhiArray( const VIdx& nbrVOffset, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void setSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setSubgridPhi( const VIdx& nbrVOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setSubgridPhi( const VIdx& nbrVOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setSubgridPhis( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const Vector<REAL>& v_val ) const __attribute( ( always_inline ) );/* use VIdx::getIdx3DTo1D() to index v_val */
	inline void setSubgridPhis( const VIdx& nbrVOffset, const S32 elemIdx, const Vector<REAL>& v_val ) const __attribute( ( always_inline ) );/* use VIdx::getIdx3DTo1D() to index v_val */
	inline void incPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );/* increase every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void incPhi( const VIdx& nbrVOffset, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );/* increase every value within this interface grid box if the interface subgrid is finer than the interface grid */
	inline void incSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );
	inline void incSubgridPhi( const VIdx& nbrVOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );
	inline void incSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );
	inline void incSubgridPhi( const VIdx& nbrVOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );
	inline REAL getModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline REAL getModelReal( const VIdx& nbrVOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( const VIdx& nbrVOffset ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const VIdx& nbrVOffset, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );
	inline void incModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline S32 getModelInt( const VIdx& nbrVOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( const VIdx& nbrVOffset ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const VIdx& nbrVOffset, const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 inc ) __attribute( ( always_inline ) );
	inline void incModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 inc ) __attribute( ( always_inline ) );

private:
	BOOL a_valid[3 * 3 * 3];
	UBEnv a_env[3 * 3 * 3];

	NbrUBEnvAux* p_aux;/* only when this NbrUBEnv object can be modified by users */

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
	friend class Misc;
	friend class PartSupplData;
#endif
};

class NbrUBEnvModelVar {
public:
#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
	inline NbrUBEnvModelVar( void ) __attribute( ( always_inline ) );
	inline ~NbrUBEnvModelVar( void ) __attribute( ( always_inline ) );

	inline void allocateAux( void );
	inline void clearAux( void );
#endif

	inline BOOL getValidFlag( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute__( ( always_inline ) );
	inline BOOL getValidFlag( const VIdx& nbrVOffset ) const __attribute__( ( always_inline ) );

	inline REAL getModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline REAL getModelReal( const VIdx& nbrVOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( const VIdx& nbrVOffset ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const VIdx& nbrVOffset, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );
	inline void incModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline S32 getModelInt( const VIdx& nbrVOffset, const S32 elemIdx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( const VIdx& nbrVOffset ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const VIdx& nbrVOffset, const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 inc ) __attribute( ( always_inline ) );
	inline void incModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 inc ) __attribute( ( always_inline ) );

private:
	BOOL a_valid[3 * 3 * 3];
	UBEnvModelVar a_env[3 * 3 * 3];

	NbrUBEnvAux* p_aux;/* only when this NbrUBEnv object can be modified by users */

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
	friend class Misc;
#endif
};

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
inline UBEnv::UBEnv( void ) {
	this->v_aux.assign( Info::envAuxDataInfo.dataSize, 0 );
}

inline UBEnv::~UBEnv( void ) {
	/* nothing to do */
}

inline void UBEnv::reset( void ) {
	this->v_aux.assign( Info::envAuxDataInfo.dataSize, 0 );
	return;
}
#endif

inline REAL UBEnv::getPhi( const S32 elemIdx ) const {/* average if the interface subgrid is finer than the interface grid */
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	S32 ratioCubed = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	CHECK( ratioCubed == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	if( ratioCubed == 1 ) {
		return *p_reals;
	}
	else {
		CHECK( ratioCubed > 1 );
		REAL val = 0.0;
		for( S32 i = 0 ; i < ratioCubed ; i++ ) {
			val += p_reals[i];
		}
		return val / ( REAL )ratioCubed;
	}
}

inline Vector<REAL> UBEnv::getPhiArray( void ) const {/* average if the interface subgrid is finer than the interface grid */
	Vector<REAL> v_val;
	v_val.assign( Info::numGridPhis, 0.0 );
	if( Info::numGridPhis > 0 ) {
		for( S32 elemIdx = 0 ; elemIdx < Info::numGridPhis ; elemIdx++ ) {
			S32 ratioCubed = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
			CHECK( ratioCubed == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
			const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
			if( ratioCubed == 1 ) {
				v_val[elemIdx] = *p_reals;
			}
			else {
				CHECK( ratioCubed > 1 );
				REAL val = 0.0;
				for( S32 j = 0 ; j < ratioCubed ; j++ ) {
					val += p_reals[j];
				}
				v_val[elemIdx] = val / ( REAL )ratioCubed;
			}
		}
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline REAL UBEnv::getSubgridPhi( const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx ) const {
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	return p_reals[VIdx::getIdx3DTo1D( subgridXOffset, subgridYOffset, subgridZOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] )];
}

inline REAL UBEnv::getSubgridPhi( const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx ) const {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	return p_reals[VIdx::getIdx3DTo1D( subgridVOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] )];
}

inline Vector<REAL> UBEnv::getSubgridPhis( const S32 elemIdx ) const {/* use VIdx::getIdx3DTo1D() to index return value */
	Vector<REAL> v_val;
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	S32 ratioCubed = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	CHECK( ratioCubed == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	v_val.assign( p_reals, p_reals + ratioCubed );
	return v_val;
}

inline void UBEnv::setPhi( const S32 elemIdx, const REAL val ) {/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	S32 ratioCubed = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	CHECK( ratioCubed == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	if( ratioCubed == 1 ) {
		*p_reals = val;
	}
	else {
		CHECK( ratioCubed > 1 );
		for( S32 i = 0 ; i < ratioCubed ; i++ ) {
			p_reals[i] = val;
		}
	}
	return;
}

inline void UBEnv::setPhiArray( const Vector<REAL>& v_val ) {/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( S32 )v_val.size() == Info::numGridPhis );
	if( Info::numGridPhis > 0 ) {
		for( S32 elemIdx = 0 ; elemIdx < Info::numGridPhis ; elemIdx++ ) {
			S32 ratioCubed = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
			CHECK( ratioCubed == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
			REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
			if( ratioCubed == 1 ) {
				*p_reals = v_val[elemIdx];
			}
			else {
				CHECK( ratioCubed > 1 );
				REAL val = v_val[elemIdx];
				for( S32 j = 0 ; j < ratioCubed ; j++ ) {
					p_reals[j] = val;
				}
			}
		}
	}
	return;
}

inline void UBEnv::setSubgridPhi( const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) {
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	p_reals[VIdx::getIdx3DTo1D( subgridXOffset, subgridYOffset, subgridZOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] )] = val;
	return;
}

inline void UBEnv::setSubgridPhi( const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	p_reals[VIdx::getIdx3DTo1D( subgridVOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] )] = val;
	return;
}

inline void UBEnv::setSubgridPhis( const S32 elemIdx, const Vector<REAL>& v_val ) const {/* use VIdx::getIdx3DTo1D() to index v_val */
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	S32 ratioCubed = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	CHECK( ratioCubed == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( S32 )v_val.size() == ratioCubed );
	memcpy( p_reals, &( v_val[0] ), ratioCubed * sizeof( REAL ) );
	return;
}

inline void UBEnv::incPhi( const S32 elemIdx, const REAL inc ) {/* increase every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	S32 ratioCubed = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	CHECK( ratioCubed == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	if( ratioCubed == 1 ) {
		*p_reals += inc;
	}
	else {
		CHECK( ratioCubed > 1 );
		for( S32 i = 0 ; i < ratioCubed ; i++ ) {
			p_reals[i] += inc;
		}
	}
	return;
}

inline void UBEnv::incSubgridPhi( const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) {
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	p_reals[VIdx::getIdx3DTo1D( subgridXOffset, subgridYOffset, subgridZOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] )] += inc;
	return;
}

inline void UBEnv::incSubgridPhi( const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) {
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.v_phiOffset[elemIdx]] );
	p_reals[VIdx::getIdx3DTo1D( subgridVOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] )] += inc;
	return;
}

inline REAL UBEnv::getModelReal( const S32 elemIdx ) const {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envAuxDataInfo.modelRealOffset] );
	return p_reals[elemIdx];
}

inline Vector<REAL> UBEnv::getModelRealArray( void ) const {
	Vector<REAL> v_val;
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envAuxDataInfo.modelRealOffset] );
	v_val.assign( p_reals, p_reals + Info::numGridModelReals );
	return v_val;
}

inline void UBEnv::setModelReal( const S32 elemIdx, const REAL val ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.modelRealOffset] );
	p_reals[elemIdx] = val;
	return;
}

inline void UBEnv::setModelRealArray( const Vector<REAL>& v_val ) {
	CHECK( ( S32 )v_val.size() == Info::numGridModelReals );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.modelRealOffset] );
	memcpy( p_reals, &( v_val[0] ), Info::numGridModelReals * sizeof( REAL ) );
	return;
}

inline void UBEnv::incModelReal( const S32 elemIdx, const REAL inc ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envAuxDataInfo.modelRealOffset] );
	p_reals[elemIdx] += inc;
	return;
}

inline S32 UBEnv::getModelInt( const S32 elemIdx ) const {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	const S32* p_ints = ( const S32* )&( this->v_aux[Info::envAuxDataInfo.modelIntOffset] );
	return p_ints[elemIdx];
}

inline Vector<S32> UBEnv::getModelIntArray( void ) const {
	Vector<S32> v_val;
	const S32* p_ints = ( const S32* )&( this->v_aux[Info::envAuxDataInfo.modelIntOffset] );
	v_val.assign( p_ints, p_ints + Info::numGridModelInts );
	return v_val;
}

inline void UBEnv::setModelInt( const S32 elemIdx, const S32 val ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	S32* p_ints = ( S32* )&( this->v_aux[Info::envAuxDataInfo.modelIntOffset] );
	p_ints[elemIdx] = val;
	return;
}

inline void UBEnv::setModelIntArray( const Vector<S32>& v_val ) {
	CHECK( ( S32 )v_val.size() == Info::numGridModelInts );
	S32* p_ints = ( S32* )&( this->v_aux[Info::envAuxDataInfo.modelIntOffset] );
	memcpy( p_ints, &( v_val[0] ), Info::numGridModelInts * sizeof( S32 ) );
	return;
}

inline void UBEnv::incModelInt( const S32 elemIdx, const S32 inc ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	S32* p_ints = ( S32* )&( this->v_aux[Info::envAuxDataInfo.modelIntOffset] );
	p_ints[elemIdx] += inc;
	return;
}

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
inline UBEnvModelVar::UBEnvModelVar( void ) {
	this->v_aux.assign( Info::envModelVarAuxDataInfo.dataSize, 0 );
}

inline UBEnvModelVar::~UBEnvModelVar( void ) {
	/* nothing to do */
}

inline void UBEnvModelVar::reset( void ) {
	this->v_aux.assign( Info::envModelVarAuxDataInfo.dataSize, 0 );
	return;
}
#endif

inline REAL UBEnvModelVar::getModelReal( const S32 elemIdx ) const {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelRealOffset] );
	return p_reals[elemIdx];
}

inline Vector<REAL> UBEnvModelVar::getModelRealArray( void ) const {
	Vector<REAL> v_val;
	const REAL* p_reals = ( const REAL* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelRealOffset] );
	v_val.assign( p_reals, p_reals + Info::numGridModelReals );
	return v_val;
}

inline void UBEnvModelVar::setModelReal( const S32 elemIdx, const REAL val ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelRealOffset] );
	p_reals[elemIdx] = val;
	return;
}

inline void UBEnvModelVar::setModelRealArray( const Vector<REAL>& v_val ) {
	CHECK( ( S32 )v_val.size() == Info::numGridModelReals );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelRealOffset] );
	memcpy( p_reals, &( v_val[0] ), Info::numGridModelReals * sizeof( REAL ) );
	return;
}

inline void UBEnvModelVar::incModelReal( const S32 elemIdx, const REAL inc ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	REAL* p_reals = ( REAL* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelRealOffset] );
	p_reals[elemIdx] += inc;
	return;
}

inline S32 UBEnvModelVar::getModelInt( const S32 elemIdx ) const {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	const S32* p_ints = ( const S32* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelIntOffset] );
	return p_ints[elemIdx];
}

inline Vector<S32> UBEnvModelVar::getModelIntArray( void ) const {
	Vector<S32> v_val;
	const S32* p_ints = ( const S32* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelIntOffset] );
	v_val.assign( p_ints, p_ints + Info::numGridModelInts );
	return v_val;
}

inline void UBEnvModelVar::setModelInt( const S32 elemIdx, const S32 val ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	S32* p_ints = ( S32* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelIntOffset] );
	p_ints[elemIdx] = val;
	return;
}

inline void UBEnvModelVar::setModelIntArray( const Vector<S32>& v_val ) {
	CHECK( ( S32 )v_val.size() == Info::numGridModelInts );
	S32* p_ints = ( S32* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelIntOffset] );
	memcpy( p_ints, &( v_val[0] ), Info::numGridModelInts * sizeof( S32 ) );
	return;
}

inline void UBEnvModelVar::incModelInt( const S32 elemIdx, const S32 inc ) {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	S32* p_ints = ( S32* )&( this->v_aux[Info::envModelVarAuxDataInfo.modelIntOffset] );
	p_ints[elemIdx] += inc;
	return;
}

inline NbrUBEnvAux::NbrUBEnvAux( void ) {
	for( S32 i = 0 ; i < 3 * 3 * 3 ; i++ ) {
		this->a_changed[i] = false;
		this->av_changed[i].assign( Info::envAuxDataInfo.numVars, false );
	}
}

inline NbrUBEnvAux::~NbrUBEnvAux( void ) {
	/* nothing to do */
}

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
inline NbrUBEnv::NbrUBEnv( void ) {
	for( S32 i = 0 ; i < 3 * 3 * 3 ; i++ ) {
		this->a_valid[i] = false;
	}
	this->p_aux = NULL;
}

inline NbrUBEnv::~NbrUBEnv( void ) {
	CHECK( this->p_aux == NULL );
}

inline void NbrUBEnv::allocateAux( void ) {
	CHECK( this->p_aux == NULL );
	this->p_aux = new NbrUBEnvAux;
}

inline void NbrUBEnv::clearAux( void ) {
	CHECK( this->p_aux != NULL );
	delete this->p_aux;
	this->p_aux = NULL;
}
#endif

inline BOOL NbrUBEnv::getValidFlag( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	return this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )];
}

inline BOOL NbrUBEnv::getValidFlag( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	return this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )];
}

inline REAL NbrUBEnv::getPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const {/* average if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getPhi( elemIdx );
}

inline REAL NbrUBEnv::getPhi( const VIdx& nbrVOffset, const S32 elemIdx ) const {/* average if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getPhi( elemIdx );
}

inline Vector<REAL> NbrUBEnv::getPhiArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {/* average if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getPhiArray();
}

inline Vector<REAL> NbrUBEnv::getPhiArray( const VIdx& nbrVOffset ) const {/* average if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getPhiArray();
}

inline REAL NbrUBEnv::getSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getSubgridPhi( subgridVOffset, elemIdx );
}

inline REAL NbrUBEnv::getSubgridPhi( const VIdx& nbrVOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getSubgridPhi( subgridVOffset, elemIdx );
}

inline REAL NbrUBEnv::getSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getSubgridPhi( subgridXOffset, subgridYOffset, subgridZOffset, elemIdx );
}

inline REAL NbrUBEnv::getSubgridPhi( const VIdx& nbrVOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getSubgridPhi( subgridXOffset, subgridYOffset, subgridZOffset, elemIdx );
}

inline Vector<REAL> NbrUBEnv::getSubgridPhis( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const {/* use VIdx::getIdx3DTo1D() to index return value */
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getSubgridPhis( elemIdx );
}

inline Vector<REAL> NbrUBEnv::getSubgridPhis( const VIdx& nbrVOffset, const S32 elemIdx ) const {/* use VIdx::getIdx3DTo1D() to index return value */
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getSubgridPhis( elemIdx );
}

inline void NbrUBEnv::setPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL val ) {/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
	S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
		if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] == false ) {
			this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] = true;
			this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( i );
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setPhi( elemIdx, val );
}

inline void NbrUBEnv::setPhi( const VIdx& nbrVOffset, const S32 elemIdx, const REAL val ) {/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
	S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
		if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] == false ) {
			this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] = true;
			this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( i );
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setPhi( elemIdx, val );
}

inline void NbrUBEnv::setPhiArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<REAL>& v_val ) {/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridPhis );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridPhis ; elemIdx++ ) {
		S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
		S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
		for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
			if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] == false ) {
				this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] = true;
				this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( i );
			}
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setPhiArray( v_val );
}

inline void NbrUBEnv::setPhiArray( const VIdx& nbrVOffset, const Vector<REAL>& v_val ) {/* set every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridPhis );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridPhis ; elemIdx++ ) {
		S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
		S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
		for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
			if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] == false ) {
				this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] = true;
				this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( i );
			}
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setPhiArray( v_val );
}

inline void NbrUBEnv::setSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridVOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setSubgridPhi( subgridVOffset, elemIdx, val );
}

inline void NbrUBEnv::setSubgridPhi( const VIdx& nbrVOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridVOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setSubgridPhi( subgridVOffset, elemIdx, val );
}

inline void NbrUBEnv::setSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridXOffset, subgridYOffset, subgridZOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setSubgridPhi( subgridXOffset, subgridYOffset, subgridZOffset, elemIdx, val );
}

inline void NbrUBEnv::setSubgridPhi( const VIdx& nbrVOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridXOffset, subgridYOffset, subgridZOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setSubgridPhi( subgridXOffset, subgridYOffset, subgridZOffset, elemIdx, val );
}

inline void NbrUBEnv::setSubgridPhis( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const Vector<REAL>& v_val ) const {/* use VIdx::getIdx3DTo1D() to index v_val */
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx] == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( S32 )v_val.size() == Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx] );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
	S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
		if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] == false ) {
			this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] = true;
			this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( i );
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setSubgridPhis( elemIdx, v_val );
}

inline void NbrUBEnv::setSubgridPhis( const VIdx& nbrVOffset, const S32 elemIdx, const Vector<REAL>& v_val ) const {/* use VIdx::getIdx3DTo1D() to index v_val */
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx] == ( Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] * Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( S32 )v_val.size() == Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx] );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
	S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
		if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] == false ) {
			this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] = true;
			this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( i );
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setSubgridPhis( elemIdx, v_val );
}

inline void NbrUBEnv::incPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL inc ) {/* increase every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
	S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
		if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] == false ) {
			this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][i] = true;
			this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( i );
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].incPhi( elemIdx, inc );
}

inline void NbrUBEnv::incPhi( const VIdx& nbrVOffset, const S32 elemIdx, const REAL inc ) {/* increase every value within this interface grid box if the interface subgrid is finer than the interface grid */
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 startIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx];
	S32 numVars = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgridCubed[elemIdx];
	for( S32 i = startIdx ; i < startIdx + numVars ; i++ ) {
		if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] == false ) {
			this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][i] = true;
			this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( i );
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].incPhi( elemIdx, inc );
}

inline void NbrUBEnv::incSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridVOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].incSubgridPhi( subgridVOffset, elemIdx, inc );
}

inline void NbrUBEnv::incSubgridPhi( const VIdx& nbrVOffset, const VIdx& subgridVOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( subgridVOffset[dim] >= 0 ) && ( subgridVOffset[dim] < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	}
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridVOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].incSubgridPhi( subgridVOffset, elemIdx, inc );
}

inline void NbrUBEnv::incSubgridPhi( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridXOffset, subgridYOffset, subgridZOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].incSubgridPhi( subgridXOffset, subgridYOffset, subgridZOffset, elemIdx, inc );
}

inline void NbrUBEnv::incSubgridPhi( const VIdx& nbrVOffset, const S32 subgridXOffset/* within this interface grid box */, const S32 subgridYOffset/* within this interface grid box */, const S32 subgridZOffset/* within this interface grid box */, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( subgridXOffset >= 0 ) && ( subgridXOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridYOffset >= 0 ) && ( subgridYOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( subgridZOffset >= 0 ) && ( subgridZOffset < Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] ) );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridPhis ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.v_phiStartIdx[elemIdx] + VIdx::getIdx3DTo1D( subgridXOffset, subgridYOffset, subgridZOffset, Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx] );
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].incSubgridPhi( subgridXOffset, subgridYOffset, subgridZOffset, elemIdx, inc );
}

inline REAL NbrUBEnv::getModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelReal( elemIdx );
}

inline REAL NbrUBEnv::getModelReal( const VIdx& nbrVOffset, const S32 elemIdx ) const {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelReal( elemIdx );
}

inline Vector<REAL> NbrUBEnv::getModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelRealArray();
}

inline Vector<REAL> NbrUBEnv::getModelRealArray( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelRealArray();
}

inline void NbrUBEnv::setModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelReal( elemIdx, val );
}

inline void NbrUBEnv::setModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelReal( elemIdx, val );
}

inline void NbrUBEnv::setModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<REAL>& v_val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelReals );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelReals ; elemIdx++ ) {
		S32 valIdx = Info::envAuxDataInfo.modelRealStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelRealArray( v_val );
}

inline void NbrUBEnv::setModelRealArray( const VIdx& nbrVOffset, const Vector<REAL>& v_val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelReals );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelReals ; elemIdx++ ) {
		S32 valIdx = Info::envAuxDataInfo.modelRealStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelRealArray( v_val );
}

inline void NbrUBEnv::incModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].incModelReal( elemIdx, inc );
}

inline void NbrUBEnv::incModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].incModelReal( elemIdx, inc );
}

inline S32 NbrUBEnv::getModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelInt( elemIdx );
}

inline S32 NbrUBEnv::getModelInt( const VIdx& nbrVOffset, const S32 elemIdx ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelInt( elemIdx );
}

inline Vector<S32> NbrUBEnv::getModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelIntArray();
}

inline Vector<S32> NbrUBEnv::getModelIntArray( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelIntArray();
}

inline void NbrUBEnv::setModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelInt( elemIdx, val );
}

inline void NbrUBEnv::setModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelInt( elemIdx, val );
}

inline void NbrUBEnv::setModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<S32>& v_val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelInts );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelInts ; elemIdx++ ) {
		S32 valIdx = Info::envAuxDataInfo.modelIntStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelIntArray( v_val );
}

inline void NbrUBEnv::setModelIntArray( const VIdx& nbrVOffset, const Vector<S32>& v_val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelInts );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelInts ; elemIdx++ ) {
		S32 valIdx = Info::envAuxDataInfo.modelIntStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelIntArray( v_val );
}

inline void NbrUBEnv::incModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 inc ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].incModelInt( elemIdx, inc );
}

inline void NbrUBEnv::incModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 inc ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].incModelInt( elemIdx, inc );
}

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
inline NbrUBEnvModelVar::NbrUBEnvModelVar( void ) {
	for( S32 i = 0 ; i < 3 * 3 * 3 ; i++ ) {
		this->a_valid[i] = false;
	}
	this->p_aux = NULL;
}

inline NbrUBEnvModelVar::~NbrUBEnvModelVar( void ) {
	CHECK( this->p_aux == NULL );
}

inline void NbrUBEnvModelVar::allocateAux( void ) {
	CHECK( this->p_aux == NULL );
	this->p_aux = new NbrUBEnvAux;
}

inline void NbrUBEnvModelVar::clearAux( void ) {
	CHECK( this->p_aux != NULL );
	delete this->p_aux;
	this->p_aux = NULL;
}
#endif

inline BOOL NbrUBEnvModelVar::getValidFlag( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	return this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )];
}

inline BOOL NbrUBEnvModelVar::getValidFlag( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	return this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )];
}

inline REAL NbrUBEnvModelVar::getModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelReal( elemIdx );
}

inline REAL NbrUBEnvModelVar::getModelReal( const VIdx& nbrVOffset, const S32 elemIdx ) const {
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelReal( elemIdx );
}

inline Vector<REAL> NbrUBEnvModelVar::getModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelRealArray();
}

inline Vector<REAL> NbrUBEnvModelVar::getModelRealArray( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelRealArray();
}

inline void NbrUBEnvModelVar::setModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelReal( elemIdx, val );
}

inline void NbrUBEnvModelVar::setModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelReal( elemIdx, val );
}

inline void NbrUBEnvModelVar::setModelRealArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<REAL>& v_val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelReals );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelReals ; elemIdx++ ) {
		S32 valIdx = Info::envModelVarAuxDataInfo.modelRealStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelRealArray( v_val );
}

inline void NbrUBEnvModelVar::setModelRealArray( const VIdx& nbrVOffset, const Vector<REAL>& v_val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelReals );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelReals ; elemIdx++ ) {
		S32 valIdx = Info::envModelVarAuxDataInfo.modelRealStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelRealArray( v_val );
}

inline void NbrUBEnvModelVar::incModelReal( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].incModelReal( elemIdx, inc );
}

inline void NbrUBEnvModelVar::incModelReal( const VIdx& nbrVOffset, const S32 elemIdx, const REAL inc ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelReals ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelRealStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].incModelReal( elemIdx, inc );
}

inline S32 NbrUBEnvModelVar::getModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelInt( elemIdx );
}

inline S32 NbrUBEnvModelVar::getModelInt( const VIdx& nbrVOffset, const S32 elemIdx ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelInt( elemIdx );
}

inline Vector<S32> NbrUBEnvModelVar::getModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].getModelIntArray();
}

inline Vector<S32> NbrUBEnvModelVar::getModelIntArray( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].getModelIntArray();
}

inline void NbrUBEnvModelVar::setModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelInt( elemIdx, val );
}

inline void NbrUBEnvModelVar::setModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelInt( elemIdx, val );
}

inline void NbrUBEnvModelVar::setModelIntArray( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const Vector<S32>& v_val ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelInts );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelInts ; elemIdx++ ) {
		S32 valIdx = Info::envModelVarAuxDataInfo.modelIntStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].setModelIntArray( v_val );
}

inline void NbrUBEnvModelVar::setModelIntArray( const VIdx& nbrVOffset, const Vector<S32>& v_val ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( S32 )v_val.size() == Info::numGridModelInts );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridModelInts ; elemIdx++ ) {
		S32 valIdx = Info::envModelVarAuxDataInfo.modelIntStartIdx + elemIdx;
		if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
			this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
			this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
		}
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].setModelIntArray( v_val );
}

inline void NbrUBEnvModelVar::incModelInt( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset, const S32 elemIdx, const S32 inc ) {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )].incModelInt( elemIdx, inc );
}

inline void NbrUBEnvModelVar::incModelInt( const VIdx& nbrVOffset, const S32 elemIdx, const S32 inc ) {
	CHECK( ( nbrVOffset[0] >= -1 ) || ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) || ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) || ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	CHECK( ( elemIdx >= 0 ) && ( elemIdx < Info::numGridModelInts ) );
	CHECK( this->p_aux != NULL );
	this->p_aux->a_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] = true;
	S32 valIdx = Info::envModelVarAuxDataInfo.modelIntStartIdx + elemIdx;
	if( this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] == false ) {
		this->p_aux->av_changed[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )][valIdx] = true;
		this->p_aux->av_idx[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].push_back( valIdx );
	}
	return this->a_env[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )].incModelInt( elemIdx, inc );
}

#endif/* #ifndef __ENV_CLASS_H__ */


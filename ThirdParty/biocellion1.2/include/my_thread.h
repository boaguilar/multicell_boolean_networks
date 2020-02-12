/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __MY_THREAD_H__
#define __MY_THREAD_H__

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

#include <string>

#include "base_type.h"
#include "vector_type.h"
#include "report.h"
#include "rng.h"

typedef enum _load_type_idx_e {
	LOAD_TYPE_UNMEASURED_IDX = -1,
	LOAD_TYPE_AGENT_INJECTION_IDX = 0,
	LOAD_TYPE_AGENT_BIRTH_DEATH_POS_IDX = 1,
	LOAD_TYPE_AGENT_STATE_IDX = 2,
	LOAD_TYPE_PDE_PARAM_IDX = 3,
	NUM_MIN_LOAD_TYPES = 4
} load_type_idx_e;

#if USE_DIST_MEM_PAR
class PartLoadData {
public:
	Vector<REAL> v_load;

public:
	inline void reset( void ) __attribute__( ( always_inline ) );
};
#endif

class MyThreadData {
public:
#if USE_DIST_MEM_PAR
	/* load */

	BOOL started;

	S32 loadTypeIdx;
	S32 spartPos;
	S32 partPosInSpart;

	struct timeval start;
	struct timeval end;

	Vector<Vector<PartLoadData> > vv_partLoad;
#endif

	/* random number generator */

	RNG execUniformRNG;
	RNG execGaussianRNG;
	Vector<RNG> v_modelRNG;

public:
	MyThreadData( void );
	~MyThreadData( void );
};

typedef tbb::enumerable_thread_specific<MyThreadData> threadLocalData_t;

#if USE_DIST_MEM_PAR
#define START_LOAD_MEASUREMENT( thLoadTypeIdx, thSpartPos, thPartPosInSpart ) {\
	threadLocalData_t::reference localData = MyThread::threadLocalData.local();\
	if( MyThread::loadMeasurementOn == true ) {\
		CHECK( localData.started == false );\
		localData.loadTypeIdx = thLoadTypeIdx;\
		if( thLoadTypeIdx != LOAD_TYPE_UNMEASURED_IDX ) {\
			CHECK( thSpartPos >= 0 );\
			CHECK( thSpartPos < ( S32 )localData.vv_partLoad.size() );\
			CHECK( thPartPosInSpart >= 0 );\
			CHECK( thPartPosInSpart < ( S32 )localData.vv_partLoad[thSpartPos].size() );\
			localData.spartPos = thSpartPos;\
			localData.partPosInSpart = thPartPosInSpart;\
			gettimeofday( &( localData.start ), NULL );\
		}\
		localData.started = true;\
	}\
}

#define END_LOAD_MEASUREMENT {\
	threadLocalData_t::reference localData = MyThread::threadLocalData.local();\
	if( MyThread::loadMeasurementOn == true ) {\
		CHECK( localData.started == true );\
		localData.started = false;\
		if( localData.loadTypeIdx != LOAD_TYPE_UNMEASURED_IDX ) {\
			REAL elapsed;\
			gettimeofday( &( localData.end ), NULL );\
			elapsed = ( ( REAL )( localData.end.tv_sec - localData.start.tv_sec ) * 1e6 + ( REAL )( localData.end.tv_usec - localData.start.tv_usec ) ) / 1e6;\
			CHECK( elapsed >= 0.0 );\
			CHECK( localData.loadTypeIdx >= 0 );\
			CHECK( localData.loadTypeIdx < MyThread::totLoadTypes );\
			localData.vv_partLoad[localData.spartPos][localData.partPosInSpart].v_load[localData.loadTypeIdx] += elapsed;\
		}\
	}\
}

#define GET_LOAD_TYPE_IDX_AND_PART_POS( thLoadTypeIdx, thSpartPos, thPartPosInSpart ) {\
	threadLocalData_t::reference localData = MyThread::threadLocalData.local();\
	if( MyThread::loadMeasurementOn == true ) {\
		CHECK( localData.started == true );\
		thLoadTypeIdx = localData.loadTypeIdx;\
		thSpartPos = localData.spartPos;\
		thPartPosInSpart = localData.partPosInSpart;\
	}\
}

#define CHECK_LOAD_TYPE_IDX( thLoadTypeIdx ) {\
	threadLocalData_t::reference localData = MyThread::threadLocalData.local();\
	if( MyThread::loadMeasurementOn == true ) {\
		CHECK( localData.loadTypeIdx == thLoadTypeIdx );\
	}\
}
#else
#define START_LOAD_MEASUREMENT( thLoadTypeIdx, thSpartPos, thPartPosInSpart )
#define END_LOAD_MEASUREMENT
#define GET_LOAD_TYPE_IDX_AND_PART_POS( thLoadTypeIdx, thSpartPos, thPartPosInSpart )
#define CHECK_LOAD_TYPE_IDX( thLoadTypeIdx )
#endif

class MyThread {
public:
#if USE_DIST_MEM_PAR
	static BOOL loadMeasurementOn;

	static S32 numSparts;/* should be initialized */
	static Vector<S32> v_numParts;/* should be initialized */

	static S32 loadTypeComputeMechIntrctStartIdx;/* should be initialized */
	static S32 loadTypeUpdateIfGridPreStartIdx;/* should be initialized */
	static S32 loadTypeUpdateIfGridPostStartIdx;/* should be initialized */
	static Vector<S32> v_loadTypePDEStartIdx;/* should be initialized */
	static S32 totLoadTypes;/* should be initialized */
#endif
	static threadLocalData_t threadLocalData;

public:
#if USE_DIST_MEM_PAR
	static inline void init( const S32 numComputeMechIntrctIters, const S32 numUpdateIfGridVarPreStateAndGridStepIters, const S32 numUpdateIfGridVarPostStateAndGridStepIters, const Vector<S32> v_pdeNumLevels ) __attribute__( ( always_inline ) );/* should not be called by multiple threads at the same time */
	static inline void term( void );
	static inline void resetLoad( const S32 numSparts, const Vector<S32>& v_numParts ) __attribute__( ( always_inline ) );/* should not be called by multiple threads at the same time */

	static inline void turnOnLoadMeasurement( void ) __attribute__( ( always_inline ) );/* should not be called by multiple threads at the same time */
	static inline void turnOffLoadMeasurement( void ) __attribute__( ( always_inline ) );/* should not be called by multiple threads at the same time */

	static inline REAL sumPartLoad( const S32 loadTypeIdx, const S32 spartPos, const S32 partPosInSpart ) __attribute__( ( always_inline ) );
#endif

	static inline REAL getExecUniformRand( void ) __attribute__( ( always_inline ) );
	static inline REAL getExecGaussianRand( void ) __attribute__( ( always_inline ) );
	static inline REAL getModelRand( const S32 idx ) __attribute__( ( always_inline ) );
};

#if USE_DIST_MEM_PAR
inline void PartLoadData::reset( void ) {
	CHECK( MyThread::totLoadTypes >= NUM_MIN_LOAD_TYPES );
	this->v_load.assign( MyThread::totLoadTypes, 0.0 );
};

inline void MyThread::init( const S32 numComputeMechIntrctIters, const S32 numUpdateIfGridVarPreStateAndGridStepIters, const S32 numUpdateIfGridVarPostStateAndGridStepIters, const Vector<S32> v_pdeNumLevels ) {/* should not be called by multiple threads at the same time */
	MyThread::totLoadTypes = NUM_MIN_LOAD_TYPES;

	MyThread::loadTypeComputeMechIntrctStartIdx = MyThread::totLoadTypes;
	MyThread::totLoadTypes += numComputeMechIntrctIters;

	MyThread::loadTypeUpdateIfGridPreStartIdx = MyThread::totLoadTypes;
	MyThread::totLoadTypes += numUpdateIfGridVarPreStateAndGridStepIters;

	MyThread::loadTypeUpdateIfGridPostStartIdx = MyThread::totLoadTypes;
	MyThread::totLoadTypes += numUpdateIfGridVarPostStateAndGridStepIters;

	MyThread::v_loadTypePDEStartIdx.assign( v_pdeNumLevels.size(), 0 );
	for( S32 i = 0 ; i < ( S32 )v_pdeNumLevels.size() ; i++ ) {
		MyThread::v_loadTypePDEStartIdx[i] = totLoadTypes;
		MyThread::totLoadTypes += v_pdeNumLevels[i] + 1;/* + 1 for the model interface level (with the interface grid spacing or PDE buffer grid spacings) */
	}

	return;
}

inline void MyThread::term( void ) {
	/* nothing to do */
	return;
}

inline void MyThread::resetLoad( const S32 numSparts, const Vector<S32>& v_numParts ) {/* should not be called by multiple threads at the same time */
	PartLoadData nullLoadData;

	MyThread::loadMeasurementOn = false;
	MyThread::numSparts = numSparts;
	MyThread::v_numParts = v_numParts;

	nullLoadData.reset();

	for( threadLocalData_t::iterator iter = MyThread::threadLocalData.begin() ; iter != MyThread::threadLocalData.end() ; iter++ ) {
		iter->started = false;
		iter->loadTypeIdx = LOAD_TYPE_UNMEASURED_IDX;
		iter->spartPos = INVALID_IDX;
		iter->partPosInSpart = INVALID_IDX;
		iter->vv_partLoad.resize( MyThread::numSparts );
		for( S32 i = 0 ; i < MyThread::numSparts ; i++ ) {
			iter->vv_partLoad[i].assign( MyThread::v_numParts[i], nullLoadData );
		}
	}

	return;
}

inline void MyThread::turnOnLoadMeasurement( void ) {/* should not be called by multiple threads at the same time */
	CHECK( MyThread::loadMeasurementOn == false );
#if ENABLE_CHECK
	for( threadLocalData_t::iterator i = MyThread::threadLocalData.begin() ; i != MyThread::threadLocalData.end() ; i++ ) {
		CHECK( i->started == false );
	}
#endif

	MyThread::loadMeasurementOn = true;

	return;
}

inline void MyThread::turnOffLoadMeasurement( void ) {/* should not be called by multiple threads at the same time */
	CHECK( MyThread::loadMeasurementOn == true );
#if ENABLE_CHECK
	for( threadLocalData_t::iterator i = MyThread::threadLocalData.begin() ; i != MyThread::threadLocalData.end() ; i++ ) {
		CHECK( i->started == false );
	}
#endif

	MyThread::loadMeasurementOn = false;

	return;
}

inline REAL MyThread::sumPartLoad( const S32 loadTypeIdx, const S32 spartPos, const S32 partPosInSpart ) {
	REAL sum = 0.0;

	CHECK( loadTypeIdx >= 0 );
	CHECK( loadTypeIdx < MyThread::totLoadTypes );

	for( threadLocalData_t::const_iterator iter = MyThread::threadLocalData.begin() ; iter != MyThread::threadLocalData.end() ; iter++ ) {
		CHECK( iter->vv_partLoad[spartPos][partPosInSpart].v_load[loadTypeIdx] >= 0.0 );
		sum += iter->vv_partLoad[spartPos][partPosInSpart].v_load[loadTypeIdx];
	}

	return sum;
}
#endif

inline REAL MyThread::getExecUniformRand( void ) {
	threadLocalData_t::reference localData = MyThread::threadLocalData.local();
	return localData.execUniformRNG.rand();
}

inline REAL MyThread::getExecGaussianRand( void ) {
	threadLocalData_t::reference localData = MyThread::threadLocalData.local();
	return localData.execGaussianRNG.rand();
}

inline REAL MyThread::getModelRand( const S32 idx ) {
	threadLocalData_t::reference localData = MyThread::threadLocalData.local();
	return localData.v_modelRNG[idx].rand();
}

#define PARALLEL

#define BEGIN_ATOMIC

#define END_ATOMIC

#endif/* #ifndef __MY_THREAD_H__ */


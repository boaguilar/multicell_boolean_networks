/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __AGENT_CLASS_H__
#define __AGENT_CLASS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "base_type.h"
#include "vector_type.h"
#include "ext_type.h"
#include "info.h"
#include "report.h"

class SubAgentState {
#if HAS_MPAGENT
public:
	inline SubAgentState( void ) __attribute( ( always_inline ) );
	inline SubAgentState( const agentType_t type ) __attribute( ( always_inline ) );
	inline ~SubAgentState( void ) __attribute( ( always_inline ) );

	inline agentType_t getType( void ) const __attribute( ( always_inline ) );
	inline void setType( const agentType_t type ) __attribute( ( always_inline ) );/* note that this reset state.v_aux */
	inline REAL getRadius( void ) const __attribute( ( always_inline ) );
	inline void setRadius( const REAL radius ) __attribute( ( always_inline ) );

	inline REAL getModelReal( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( void ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 idx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 idx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( void ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 idx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 idx, const S32 inc ) __attribute( ( always_inline ) );

	inline SubAgentState& operator=( const SubAgentState& subAgentSrc ) __attribute( ( always_inline ) );

private:
	agentType_t type;
	REAL radius;
	Vector<U8> v_aux;

	friend class SubAgent;

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Pack;
	friend class Xml;
	friend class Sim;
#endif
#endif
};

class SpAgentState {
#if HAS_SPAGENT
public:
	inline SpAgentState( void ) __attribute( ( always_inline ) );
	inline SpAgentState( const agentType_t type ) __attribute( ( always_inline ) );
	inline ~SpAgentState( void ) __attribute( ( always_inline ) );

	inline agentType_t getType( void ) const __attribute( ( always_inline ) );
	inline void setType( const agentType_t type ) __attribute( ( always_inline ) );/* note that this reset state.v_aux */
	inline REAL getRadius( void ) const __attribute( ( always_inline ) );
	inline void setRadius( const REAL radius ) __attribute( ( always_inline ) );

	inline BOOL getBoolVal( const S32 varIdx ) const __attribute( ( always_inline ) );
	inline Vector<BOOL> getBoolValArray( void ) const __attribute( ( always_inline ) );
	inline void setBoolVal( const S32 varIdx, const BOOL val ) __attribute( ( always_inline ) );
	inline void setBoolValArray( const Vector<BOOL>& v_val ) __attribute( ( always_inline ) );

	inline REAL getODEVal( const S32 odeNetIdx, const S32 varIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getODEValArray( const S32 odeNetIdx ) const __attribute( ( always_inline ) );
	inline void setODEVal( const S32 odeNetIdx, const S32 varIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setODEValArray( const S32 odeNetIdx, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );

	inline REAL getModelReal( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( void ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 idx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 idx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( void ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 idx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 idx, const S32 inc ) __attribute( ( always_inline ) );

	inline SpAgentState& operator=( const SpAgentState& spAgentSrc ) __attribute( ( always_inline ) );

private:
	agentType_t type;
	REAL radius;
	Vector<U8> v_aux;

	inline ODESolverData& getODENetSolverDataRef( const S32 odeNetIdx ) __attribute( ( always_inline ) );
	inline REAL* getODENetVarArrayPtr( const S32 odeNetIdx ) __attribute( ( always_inline ) );

	friend class SpAgent;
#if ( THIS_IS_LIBMODEL == 0 )
	friend class Pack;
	friend class Xml;
	friend class Sim;
#endif
#endif
};

class JunctionEnd {
public:
	inline JunctionEnd( void ) __attribute( ( always_inline ) );
	inline JunctionEnd( const junctionEndType_t type ) __attribute( ( always_inline ) );
	inline ~JunctionEnd( void ) __attribute( ( always_inline ) );

	inline junctionEndType_t getType( void ) const __attribute( ( always_inline ) );
	inline void setType( const junctionEndType_t type ) __attribute( ( always_inline ) );

	inline REAL getModelReal( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( void ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 idx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 idx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( void ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 idx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 idx, const S32 inc ) __attribute( ( always_inline ) );

	inline JunctionEnd& operator=( const JunctionEnd& junctionEndSrc ) __attribute( ( always_inline ) );

private:
	junctionEndType_t type;
	Vector<U8> v_aux;

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Pack;
	friend class Sim;
#endif
};

class JunctionData {
public:
	inline JunctionData( void ) __attribute( ( always_inline ) );
	inline JunctionData( const S64 prevId, const S64 curId ) __attribute( ( always_inline ) );
	inline ~JunctionData( void ) __attribute( ( always_inline ) );

	inline S64 getPrevId( void ) const __attribute( ( always_inline ) );
	inline S64 getCurId( void ) const __attribute( ( always_inline ) );

	inline S32 getNumJunctions( void ) const __attribute( ( always_inline ) );

	inline S64 getOtherEndId( const S32 idx ) const __attribute( ( always_inline ) );
	inline const JunctionEnd& getJunctionEndRef( const S32 idx ) const __attribute( ( always_inline ) );
	inline JunctionEnd& getJunctionEndRef( const S32 idx ) __attribute( ( always_inline ) );

	inline BOOL isLinked( const JunctionData& otherData ) const __attribute( ( always_inline ) );
	inline BOOL isLinked( const JunctionData& otherData, S32& idxThis/* valid only when linked */, S32& idxOther/* valid only when linked */ ) const __attribute( ( always_inline ) );

	inline JunctionData& operator=( const JunctionData& junctionDataSrc ) __attribute( ( always_inline ) );

private:
	S64 prevId;/* mother id if this agent was born in the previous baseline time step, otherwise prevId == curId */
	S64 curId;
	Vector<S64> v_otherEndId;
	Vector<JunctionEnd> v_junctionEnd;

	inline void setId( const S64 prevId, const S64 curId ) __attribute( ( always_inline ) );
	inline void link( const JunctionEnd& endThis, const JunctionEnd& endOther, JunctionData& otherData ) __attribute( ( always_inline ) );
	inline void split( const Vector<BOOL>& v_junctionDivide, JunctionData& daughterData ) __attribute( ( always_inline ) );

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Pack;
	friend class Sim;
#endif
};

class MpAgent {
#if HAS_MPAGENT
public:
	inline MpAgent( void ) __attribute( ( always_inline ) );
	inline MpAgent( const agentType_t type ) __attribute( ( always_inline ) );
	inline ~MpAgent( void ) __attribute( ( always_inline ) );

	inline agentType_t getType( void ) const __attribute( ( always_inline ) );
	inline void setType( const agentType_t type ) __attribute( ( always_inline ) );/* note that this reset state.v_aux */

	inline BOOL getBoolVal( const S32 varIdx ) const __attribute( ( always_inline ) );
	inline Vector<BOOL> getBoolValArray( void ) const __attribute( ( always_inline ) );
	inline void setBoolVal( const S32 varIdx, const BOOL val ) __attribute( ( always_inline ) );
	inline void setBoolValArray( const Vector<BOOL>& v_val ) __attribute( ( always_inline ) );

	inline REAL getODEVal( const S32 odeNetIdx, const S32 varIdx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getODEValArray( const S32 odeNetIdx ) const __attribute( ( always_inline ) );
	inline void setODEVal( const S32 odeNetIdx, const S32 varIdx, const REAL val ) __attribute( ( always_inline ) );
	inline void setODEValArray( const S32 odeNetIdx, const Vector<REAL>& v_val ) __attribute( ( always_inline ) );

	inline REAL getModelReal( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( void ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 idx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 idx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( void ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 idx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 idx, const S32 inc ) __attribute( ( always_inline ) );

	inline MpAgent& operator=( const MpAgent& mpAgentSrc ) __attribute( ( always_inline ) );

private:
	agentType_t type;
	Vector<U8> v_aux;

	inline ODESolverData& getODENetSolverDataRef( const S32 odeNetIdx ) __attribute( ( always_inline ) );
	inline REAL* getODENetVarArrayPtr( const S32 odeNetIdx ) __attribute( ( always_inline ) );

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Pack;
	friend class Xml;
	friend class Sim;
#endif
#endif
};

class SubAgent {
#if HAS_MPAGENT
public:
	SubAgentState state;
	JunctionData junctionData;
	VReal vOffset;

	inline SubAgent( void ) __attribute( ( always_inline ) );
	inline SubAgent( const agentType_t type ) __attribute( ( always_inline ) );
	inline ~SubAgent( void ) __attribute( ( always_inline ) );
#endif
};

class SpAgent {
#if HAS_SPAGENT
public:
	SpAgentState state;
	JunctionData junctionData;
	VReal vOffset;

	inline SpAgent( void ) __attribute( ( always_inline ) );
	inline SpAgent( const agentType_t type ) __attribute( ( always_inline ) );
	inline ~SpAgent( void ) __attribute( ( always_inline ) );
#endif
};

class UBAgentData {
public:
#if HAS_MPAGENT
	Vector<SubAgent> v_subAgent;
	Vector<partMpAgentIdx_t> v_mpAgentIdx;
#endif
#if HAS_SPAGENT
	Vector<SpAgent> v_spAgent;
#endif
};

class MechIntrctData {
public:
	inline REAL getModelReal( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<REAL> getModelRealArray( void ) const __attribute( ( always_inline ) );
	inline void setModelReal( const S32 idx, const REAL val ) __attribute( ( always_inline ) );
	inline void setModelRealArray( const Vector<REAL>& v_val ) __attribute( ( always_inline ) );
	inline void incModelReal( const S32 idx, const REAL inc ) __attribute( ( always_inline ) );

	inline S32 getModelInt( const S32 idx ) const __attribute( ( always_inline ) );
	inline Vector<S32> getModelIntArray( void ) const __attribute( ( always_inline ) );
	inline void setModelInt( const S32 idx, const S32 val ) __attribute( ( always_inline ) );
	inline void setModelIntArray( const Vector<S32>& v_val ) __attribute( ( always_inline ) );
	inline void incModelInt( const S32 idx, const S32 inc ) __attribute( ( always_inline ) );

private:
	agent_class_e agentClass;
	agentType_t type;
	Vector<U8> v_aux;

	inline agent_class_e getClass( void ) const __attribute( ( always_inline ) );
	inline agentType_t getType( void ) const __attribute( ( always_inline ) );
	inline void setClassAndType( const agent_class_e agentClass, const agentType_t type ) __attribute( ( always_inline ) );/* note that this reset v_aux */

	inline void resetChangeFlag( void ) __attribute( ( always_inline ) );
	inline void resetModelVar( void ) __attribute( ( always_inline ) );
	inline BOOL getModelRealChanged( const S32 idx ) const __attribute( ( always_inline ) );
	inline BOOL getModelIntChanged( const S32 idx ) const __attribute( ( always_inline ) );

	friend class SubAgent;
#if ( THIS_IS_LIBMODEL == 0 )
	friend class Pack;
	friend class Xml;
	friend class Sim;
#endif
};

class NbrUBAgentData {
public:
#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
	inline NbrUBAgentData( void ) __attribute__( ( always_inline ) );
	inline ~NbrUBAgentData( void ) __attribute__( ( always_inline ) );
#endif

	inline BOOL getValidFlag( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute__( ( always_inline ) );
	inline BOOL getValidFlag( const VIdx& nbrVOffset ) const __attribute__( ( always_inline ) );
	inline const UBAgentData* getConstPtr( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const __attribute__( ( always_inline ) );
	inline const UBAgentData* getConstPtr( const VIdx& nbrVOffset ) const __attribute__( ( always_inline ) );

private:
	BOOL a_valid[3 * 3 * 3];
	const UBAgentData* ap_val[3 * 3 * 3];

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
	friend class Misc;
#endif
};

#if HAS_MPAGENT
inline SubAgentState::SubAgentState( void ) {
	this->type = ( agentType_t )INVALID_TYPE;
	this->radius = 0.0;
	this->v_aux.clear();
}

inline SubAgentState::SubAgentState( const agentType_t type ) {
	CHECK( type < Info::numSubAgentTypes );
	this->type = ( agentType_t )INVALID_TYPE;
	this->radius = 0.0;
	this->v_aux.clear();
	this->setType( type );
}

inline SubAgentState::~SubAgentState( void ) {
	/* nothing to do */
}

inline agentType_t SubAgentState::getType( void ) const {
	return this->type;
}

inline void SubAgentState::setType( const agentType_t type ) {
	CHECK( type < Info::numSubAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][type];
	this->type = type;
	this->v_aux.assign( auxDataInfo.stateDataSize, 0 );
	return;
}

inline REAL SubAgentState::getRadius( void ) const {
	return this->radius;
}

inline void SubAgentState::setRadius( const REAL radius ) {
	this->radius = radius;
	return;
}

inline REAL SubAgentState::getModelReal( const S32 idx ) const {
	const REAL* p_reals = NULL;
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelRealOffset] );
	return p_reals[idx];
}

inline Vector<REAL> SubAgentState::getModelRealArray( void ) const {
	Vector<REAL> v_val;
	CHECK( this->type < Info::numSubAgentTypes );
	if( Info::v_subAgentNumStateModelReals[this->type] > 0 ) {
		const REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelRealOffset] );
		v_val.assign( p_reals, p_reals + Info::v_subAgentNumStateModelReals[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void SubAgentState::setModelReal( const S32 idx, const REAL val ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelRealOffset] );
	p_reals[idx] = val;
	return;
}

inline void SubAgentState::setModelRealArray( const Vector<REAL>& v_val ) {
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( S32 )v_val.size() == Info::v_subAgentNumStateModelReals[this->type] );
	if( v_val.size() > 0 ) {
		REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelRealOffset] );
		memcpy( p_reals, &v_val[0], Info::v_subAgentNumStateModelReals[this->type] * sizeof( REAL ) );
	}
	return;
}

inline void SubAgentState::incModelReal( const S32 idx, const REAL inc ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelRealOffset] );
	p_reals[idx] += inc;
	return;
}

inline S32 SubAgentState::getModelInt( const S32 idx ) const {
	const S32* p_ints = NULL;
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelIntOffset] );
	return p_ints[idx];
}

inline Vector<S32> SubAgentState::getModelIntArray( void ) const {
	Vector<S32> v_val;
	CHECK( this->type < Info::numSubAgentTypes );
	if( Info::v_subAgentNumStateModelInts[this->type] > 0 ) {
		const S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelIntOffset] );
		v_val.assign( p_ints, p_ints + Info::v_subAgentNumStateModelInts[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void SubAgentState::setModelInt( const S32 idx, const S32 val ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelIntOffset] );
	p_ints[idx] = val;
	return;
}

inline void SubAgentState::setModelIntArray( const Vector<S32>& v_val ) {
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( S32 )v_val.size() == Info::v_subAgentNumStateModelInts[this->type] );
	if( v_val.size() > 0 ) {
		S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelIntOffset] );
		memcpy( p_ints, &v_val[0], Info::v_subAgentNumStateModelInts[this->type] * sizeof( S32 ) );
	}
	return;
}

inline void SubAgentState::incModelInt( const S32 idx, const S32 inc ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numSubAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SUBAGENT][this->type].stateModelIntOffset] );
	p_ints[idx] += inc;
	return;
}

inline SubAgentState& SubAgentState::operator=( const SubAgentState& subAgentStateSrc ) {
	this->type = subAgentStateSrc.type;
	this->radius = subAgentStateSrc.radius;
	if( this->v_aux.size() != subAgentStateSrc.v_aux.size() ) {
		this->v_aux.resize( subAgentStateSrc.v_aux.size() );
	}
	if( subAgentStateSrc.v_aux.size() > 0 ) {
		memcpy( &( this->v_aux[0] ), &( subAgentStateSrc.v_aux[0] ), subAgentStateSrc.v_aux.size() * sizeof( U8 ) );
	}
	return *this;
}
#endif

#if HAS_SPAGENT
inline SpAgentState::SpAgentState( void ) {
	this->type = ( agentType_t )INVALID_TYPE;
	this->radius = 0.0;
	this->v_aux.clear();
}

inline SpAgentState::SpAgentState( const agentType_t type ) {
	CHECK( type < Info::numSpAgentTypes );
	this->type = ( agentType_t )INVALID_TYPE;
	this->radius = 0.0;
	this->v_aux.clear();
	this->setType( type );
}

inline SpAgentState::~SpAgentState( void ) {
	/* nothing to do */
}

inline agentType_t SpAgentState::getType( void ) const {
	return this->type;
}

inline void SpAgentState::setType( const agentType_t type ) {
	CHECK( type < Info::numSpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][type];
	this->type = type;
	this->v_aux.assign( auxDataInfo.stateDataSize, 0 );
	CHECK( ( S32 )auxDataInfo.v_odeNetSolverDataOffset.size() == Info::v_spAgentNumODENets[type] );
	for( S32 i = 0 ; i < ( S32 )Info::v_spAgentNumODENets[type] ; i++ ) {
		ODESolverData& odeSolverData = *( ( ODESolverData* )&( this->v_aux[auxDataInfo.v_odeNetSolverDataOffset[i]] ) );
		odeSolverData.h = Info::vv_spAgentODEH[type][i] * Info::durationStateAndGridTimeStep;
	}
	return;
}

inline REAL SpAgentState::getRadius( void ) const {
	return this->radius;
}

inline void SpAgentState::setRadius( const REAL radius ) {
	this->radius = radius;
	return;
}

inline BOOL SpAgentState::getBoolVal( const S32 varIdx ) const {
	CHECK( this->type < Info::numSpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	CHECK( ( varIdx >= 0 ) && ( varIdx < ( S32 )Info::v_spAgentNumBoolVars[this->type] ) );
	return p_boolVars[varIdx];
}

inline Vector<BOOL> SpAgentState::getBoolValArray( void ) const {
	Vector<BOOL> v_val;
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( Info::v_spAgentNumBoolVars[this->type] > 0 );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	v_val.assign( p_boolVars, p_boolVars + Info::v_spAgentNumBoolVars[this->type] );
	return v_val;
}

inline void SpAgentState::setBoolVal( const S32 varIdx, const BOOL val ) {
	CHECK( this->type < Info::numSpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	CHECK( ( varIdx >= 0 ) && ( varIdx < ( S32 )Info::v_spAgentNumBoolVars[this->type] ) );
	p_boolVars[varIdx] = val;
	return;
}

inline void SpAgentState::setBoolValArray( const Vector<BOOL>& v_val ) {
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( Info::v_spAgentNumBoolVars[this->type] > 0 );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	CHECK( ( S32 )v_val.size() == ( S32 )Info::v_spAgentNumBoolVars[this->type] );
	if( v_val.size() > 0 ) {
		memcpy( p_boolVars, &v_val[0], Info::v_spAgentNumBoolVars[this->type] * sizeof( BOOL ) );
	}
	return;
}

inline REAL SpAgentState::getODEVal( const S32 odeNetIdx, const S32 varIdx ) const {
	CHECK( this->type < Info::numSpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	CHECK( varIdx < ( S32 )Info::vv_spAgentNumODENetVars[this->type][odeNetIdx] );
	return p_odeNetVars[varIdx];
}

inline Vector<REAL> SpAgentState::getODEValArray( const S32 odeNetIdx ) const {
	Vector<REAL> v_val;
	CHECK( this->type < Info::numSpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	v_val.assign( p_odeNetVars, p_odeNetVars + Info::vv_spAgentNumODENetVars[this->type][odeNetIdx] );
	return v_val;
}

inline void SpAgentState::setODEVal( const S32 odeNetIdx, const S32 varIdx, REAL val ) {
	CHECK( this->type < Info::numSpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	CHECK( varIdx < ( S32 )Info::vv_spAgentNumODENetVars[this->type][odeNetIdx] );
	p_odeNetVars[varIdx] = val;
	return;
}

inline void SpAgentState::setODEValArray( const S32 odeNetIdx, const Vector<REAL>& v_val ) {
	CHECK( this->type < Info::numSpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	CHECK( ( S32 )v_val.size() == Info::vv_spAgentNumODENetVars[this->type][odeNetIdx] );
	if( v_val.size() > 0 ) {
		memcpy( p_odeNetVars, &v_val[0], Info::vv_spAgentNumODENetVars[this->type][odeNetIdx] * sizeof( REAL ) );
	}
	return;
}

inline REAL SpAgentState::getModelReal( const S32 idx ) const {
	const REAL* p_reals = NULL;
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelRealOffset] );
	return p_reals[idx];
}

inline Vector<REAL> SpAgentState::getModelRealArray( void ) const {
	Vector<REAL> v_val;
	CHECK( this->type < Info::numSpAgentTypes );
	if( Info::v_spAgentNumStateModelReals[this->type] > 0 ) {
		const REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelRealOffset] );
		v_val.assign( p_reals, p_reals + Info::v_spAgentNumStateModelReals[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void SpAgentState::setModelReal( const S32 idx, const REAL val ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelRealOffset] );
	p_reals[idx] = val;
	return;
}

inline void SpAgentState::setModelRealArray( const Vector<REAL>& v_val ) {
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( S32 )v_val.size() == Info::v_spAgentNumStateModelReals[this->type] );
	if( v_val.size() > 0 ) {
		REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelRealOffset] );
		memcpy( p_reals, &v_val[0], Info::v_spAgentNumStateModelReals[this->type] * sizeof( REAL ) );
	}
	return;
}

inline void SpAgentState::incModelReal( const S32 idx, const REAL inc ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelRealOffset] );
	p_reals[idx] += inc;
	return;
}

inline S32 SpAgentState::getModelInt( const S32 idx ) const {
	const S32* p_ints = NULL;
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelIntOffset] );
	return p_ints[idx];
}

inline Vector<S32> SpAgentState::getModelIntArray( void ) const {
	Vector<S32> v_val;
	CHECK( this->type < Info::numSpAgentTypes );
	if( Info::v_spAgentNumStateModelInts[this->type] > 0 ) {
		const S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelIntOffset] );
		v_val.assign( p_ints, p_ints + Info::v_spAgentNumStateModelInts[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void SpAgentState::setModelInt( const S32 idx, const S32 val ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelIntOffset] );
	p_ints[idx] = val;
	return;
}

inline void SpAgentState::setModelIntArray( const Vector<S32>& v_val ) {
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( S32 )v_val.size() == Info::v_spAgentNumStateModelInts[this->type] );
	if( v_val.size() > 0 ) {
		S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelIntOffset] );
		memcpy( p_ints, &v_val[0], Info::v_spAgentNumStateModelInts[this->type] * sizeof( S32 ) );
	}
	return;
}

inline void SpAgentState::incModelInt( const S32 idx, const S32 inc ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].stateModelIntOffset] );
	p_ints[idx] += inc;
	return;
}

inline SpAgentState& SpAgentState::operator=( const SpAgentState& spAgentStateSrc ) {
	this->type = spAgentStateSrc.type;
	this->radius = spAgentStateSrc.radius;
	if( this->v_aux.size() != spAgentStateSrc.v_aux.size() ) {
		this->v_aux.resize( spAgentStateSrc.v_aux.size() );
	}
	if( spAgentStateSrc.v_aux.size() > 0 ) {
		memcpy( &( this->v_aux[0] ), &( spAgentStateSrc.v_aux[0] ), spAgentStateSrc.v_aux.size() * sizeof( U8 ) );
	}
	return *this;
}

inline ODESolverData& SpAgentState::getODENetSolverDataRef( const S32 odeNetIdx ) {
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( odeNetIdx < Info::v_spAgentNumODENets[this->type] );
	return *( ( ODESolverData* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].v_odeNetSolverDataOffset[odeNetIdx]] ) );
}

inline REAL* SpAgentState::getODENetVarArrayPtr( const S32 odeNetIdx ) {
	CHECK( this->type < Info::numSpAgentTypes );
	CHECK( odeNetIdx < Info::v_spAgentNumODENets[this->type] );
	return ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_SPAGENT][this->type].v_odeNetVarOffset[odeNetIdx]] );
}
#endif

inline JunctionEnd::JunctionEnd( void ) {
	this->type = ( junctionEndType_t )INVALID_TYPE;
	this->v_aux.clear();
}

inline JunctionEnd::JunctionEnd( const junctionEndType_t type ) {
	this->type = ( junctionEndType_t )INVALID_TYPE;
	this->v_aux.clear();
	this->setType( type );
}

inline JunctionEnd::~JunctionEnd( void ) {
	/* nothing to do */
}

inline junctionEndType_t JunctionEnd::getType( void ) const {
	return this->type;
}

inline void JunctionEnd::setType( const junctionEndType_t type ) {
	CHECK( type < Info::numJunctionEndTypes );
	this->type = type;
	this->v_aux.assign( Info::v_junctionEndAuxDataInfo[this->type].dataSize, 0 );
	return;
}

inline REAL JunctionEnd::getModelReal( const S32 idx ) const {
	const REAL* p_reals = NULL;
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_junctionEndNumModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelRealOffset] );
	return p_reals[idx];
}

inline Vector<REAL> JunctionEnd::getModelRealArray( void ) const {
	Vector<REAL> v_val;
	CHECK( this->type < Info::numJunctionEndTypes );
	if( Info::v_junctionEndNumModelReals[this->type] > 0 ) {
		const REAL* p_reals = ( REAL* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelRealOffset] );
		v_val.assign( p_reals, p_reals + Info::v_junctionEndNumModelReals[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void JunctionEnd::setModelReal( const S32 idx, const REAL val ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_junctionEndNumModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelRealOffset] );
	p_reals[idx] = val;
	return;
}

inline void JunctionEnd::setModelRealArray( const Vector<REAL>& v_val ) {
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( S32 )v_val.size() == Info::v_junctionEndNumModelReals[this->type] );
	if( v_val.size() > 0 ) {
		REAL* p_reals = ( REAL* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelRealOffset] );
		memcpy( p_reals, &v_val[0], Info::v_junctionEndNumModelReals[this->type] * sizeof( REAL ) );
	}
	return;
}

inline void JunctionEnd::incModelReal( const S32 idx, const REAL inc ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_junctionEndNumModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelRealOffset] );
	p_reals[idx] += inc;
	return;
}

inline S32 JunctionEnd::getModelInt( const S32 idx ) const {
	const S32* p_ints = NULL;
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_junctionEndNumModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelIntOffset] );
	return p_ints[idx];
}

inline Vector<S32> JunctionEnd::getModelIntArray( void ) const {
	Vector<S32> v_val;
	CHECK( this->type < Info::numJunctionEndTypes );
	if( Info::v_junctionEndNumModelInts[this->type] > 0 ) {
		const S32* p_ints = ( S32* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelIntOffset] );
		v_val.assign( p_ints, p_ints + Info::v_junctionEndNumModelInts[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void JunctionEnd::setModelInt( const S32 idx, const S32 val ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_junctionEndNumModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelIntOffset] );
	p_ints[idx] = val;
	return;
}

inline void JunctionEnd::setModelIntArray( const Vector<S32>& v_val ) {
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( S32 )v_val.size() == Info::v_junctionEndNumModelInts[this->type] );
	if( v_val.size() > 0 ) {
		S32* p_ints = ( S32* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelIntOffset] );
		memcpy( p_ints, &v_val[0], Info::v_junctionEndNumModelInts[this->type] * sizeof( S32 ) );
	}
	return;
}

inline void JunctionEnd::incModelInt( const S32 idx, const S32 inc ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numJunctionEndTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_junctionEndNumModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::v_junctionEndAuxDataInfo[this->type].modelIntOffset] );
	p_ints[idx] += inc;
	return;
}

inline JunctionEnd& JunctionEnd::operator=( const JunctionEnd& junctionEndSrc ) {
	this->type = junctionEndSrc.type;
	if( this->v_aux.size() != junctionEndSrc.v_aux.size() ) {
		this->v_aux.resize( junctionEndSrc.v_aux.size() );
	}
	if( junctionEndSrc.v_aux.size() > 0 ) {
		memcpy( &( this->v_aux[0] ), &( junctionEndSrc.v_aux[0] ), junctionEndSrc.v_aux.size() * sizeof( U8 ) );
	}
	return *this;
}

inline JunctionData::JunctionData( void ) {
	this->prevId = INVALID_ID;
	this->curId = INVALID_ID;
	this->v_otherEndId.clear();
	this->v_junctionEnd.clear();
};

inline JunctionData::JunctionData( const S64 prevId, const S64 curId ) {
	this->prevId = prevId;
	this->curId = curId;
	this->v_otherEndId.clear();
	this->v_junctionEnd.clear();
};

inline JunctionData::~JunctionData( void ) {
	/* nothing to do */
}

inline S64 JunctionData::getPrevId( void ) const {
	return this->prevId;
}

inline S64 JunctionData::getCurId( void ) const {
	return this->curId;
}

inline S32 JunctionData::getNumJunctions( void ) const {
	CHECK( v_otherEndId.size() == v_junctionEnd.size() );
	return ( S32 )v_otherEndId.size();
}

inline S64 JunctionData::getOtherEndId( const S32 idx ) const {
	CHECK( ( idx >= 0 ) && ( idx < ( S32 )this->v_otherEndId.size() ) );
	CHECK( this->v_otherEndId.size() == this->v_junctionEnd.size() );
	return this->v_otherEndId[idx];
}

inline const JunctionEnd& JunctionData::getJunctionEndRef( const S32 idx ) const {
	CHECK( ( idx >= 0 ) && ( idx < ( S32 )this->v_otherEndId.size() ) );
	CHECK( this->v_otherEndId.size() == this->v_junctionEnd.size() );
	return this->v_junctionEnd[idx];
}

inline JunctionEnd& JunctionData::getJunctionEndRef( S32 idx ) {
	CHECK( ( idx >= 0 ) && ( idx < ( S32 )this->v_otherEndId.size() ) );
	CHECK( this->v_otherEndId.size() == this->v_junctionEnd.size() );
	return this->v_junctionEnd[idx];
}

inline BOOL JunctionData::isLinked( const JunctionData& otherData ) const {
	BOOL linked = false;

	for( S32 i = 0 ; i < ( S32 )this->v_otherEndId.size() ; i++ ) {
		if( this->v_otherEndId[i] == otherData.prevId ) {
			linked = true;
			break;
		}
	}

	if( linked == true ) {
		linked = false;
		for( S32 i = 0 ; i < ( S32 )otherData.v_otherEndId.size() ; i++ ) {
			if( otherData.v_otherEndId[i] == this->prevId ) {
				linked = true;
				break;
			}
		}
		return linked;
	}
	else {
		return false;
	}
}

inline BOOL JunctionData::isLinked( const JunctionData& otherData, S32& idxThis/* valid only when linked */, S32& idxOther/* valid only when linked */ ) const {
	BOOL linked = false;

	idxThis = INVALID_IDX;
	idxOther = INVALID_IDX;

	for( S32 i = 0 ; i < ( S32 )this->v_otherEndId.size() ; i++ ) {
		if( this->v_otherEndId[i] == otherData.prevId ) {
			idxThis = i;
			linked = true;
			break;
		}
	}

	if( linked == true ) {
		linked = false;
		for( S32 i = 0 ; i < ( S32 )otherData.v_otherEndId.size() ; i++ ) {
			if( otherData.v_otherEndId[i] == this->prevId ) {
				idxOther = i;
				linked = true;
				break;
			}
		}
		return linked;
	}
	else {
		return false;
	}
}

inline JunctionData& JunctionData::operator=( const JunctionData& junctionDataSrc ) {
	this->prevId = junctionDataSrc.prevId;
	this->curId = junctionDataSrc.curId;
	if( this->v_otherEndId.size() != junctionDataSrc.v_otherEndId.size() ) {
		this->v_otherEndId.resize( junctionDataSrc.v_otherEndId.size() );
	}
	if( junctionDataSrc.v_otherEndId.size() > 0 ) {
		memcpy( &( this->v_otherEndId[0] ), &( junctionDataSrc.v_otherEndId[0] ), junctionDataSrc.v_otherEndId.size() * sizeof( S64 ) );
	}
	if( this->v_junctionEnd.size() != junctionDataSrc.v_junctionEnd.size() ) {
		this->v_junctionEnd.resize( junctionDataSrc.v_junctionEnd.size() );
	}
	for( S32 i = 0 ; i < ( S32 )this->v_junctionEnd.size() ; i++ ) {
		this->v_junctionEnd[i] = junctionDataSrc.v_junctionEnd[i];
	}
	return *this;
}

inline void JunctionData::setId( const S64 prevId, const S64 curId ) {
	this->prevId = prevId;
	this->curId = curId;
	return;
}

inline void JunctionData::link( const JunctionEnd& endThis, const JunctionEnd& endOther, JunctionData& otherData ) {
	S32 idxThis;
	S32 idxOther;
	BOOL linked;

	linked = this->isLinked( otherData, idxThis, idxOther );

	if( linked == true ) {/* update junction end */
		CHECK( idxThis != INVALID_IDX );
		CHECK( idxThis < ( S32 )this->v_junctionEnd.size() );
		CHECK( idxOther != INVALID_IDX );
		CHECK( idxOther < ( S32 )otherData.v_junctionEnd.size() );
		this->v_junctionEnd[idxThis] = endThis;
		otherData.v_junctionEnd[idxOther] = endOther;
	}
	else {
		this->v_otherEndId.push_back( otherData.curId );
		this->v_junctionEnd.push_back( endThis );
		CHECK( this->v_otherEndId.size() == this->v_junctionEnd.size() );

		otherData.v_otherEndId.push_back( this->curId );
		otherData.v_junctionEnd.push_back( endOther );
		CHECK( otherData.v_otherEndId.size() == otherData.v_junctionEnd.size() );
	}

	return;
}

inline void JunctionData::split( const Vector<BOOL>& v_junctionDivide/* true if belongs to this info, false if belongs to the daughter info */, JunctionData& daughterData ) {
	CHECK( this->v_otherEndId.size() == this->v_junctionEnd.size() );
	CHECK( v_junctionDivide.size() == this->v_otherEndId.size() );
	Vector<S64> v_otherEndIdCopy = this->v_otherEndId;
	Vector<JunctionEnd> v_junctionEndCopy = this->v_junctionEnd;
	this->v_otherEndId.clear();	
	this->v_junctionEnd.clear();
	daughterData.v_otherEndId.clear();	
	daughterData.v_junctionEnd.clear();
	for( S32 i = 0 ; i < ( S32 )v_junctionDivide.size() ; i++ ) {
		if( v_junctionDivide[i] == true ) {
			this->v_otherEndId.push_back( v_otherEndIdCopy[i] );
			this->v_junctionEnd.push_back( v_junctionEndCopy[i] );
		}
		else {
			daughterData.v_otherEndId.push_back( v_otherEndIdCopy[i] );
			daughterData.v_junctionEnd.push_back( v_junctionEndCopy[i] );
		}
	}
	return;
}

#if HAS_MPAGENT
inline MpAgent::MpAgent( void ) {
	this->type = ( agentType_t )INVALID_TYPE;
	this->v_aux.clear();
}

inline MpAgent::MpAgent( const agentType_t type ) {
	CHECK( type < Info::numMpAgentTypes );
	this->type = ( agentType_t )INVALID_TYPE;
	this->v_aux.clear();
	this->setType( type );
}

inline MpAgent::~MpAgent( void ) {
	/* nothing to do */
}

inline agentType_t MpAgent::getType( void ) const {
	return this->type;
}

inline void MpAgent::setType( const agentType_t type ) {
	CHECK( type < Info::numMpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][type];
	this->type = type;
	this->v_aux.assign( auxDataInfo.stateDataSize, 0 );
	CHECK( ( S32 )auxDataInfo.v_odeNetSolverDataOffset.size() == Info::v_mpAgentNumODENets[type] );
	for( S32 i = 0 ; i < ( S32 )Info::v_mpAgentNumODENets[type] ; i++ ) {
		ODESolverData& odeSolverData = *( ( ODESolverData* )&( this->v_aux[auxDataInfo.v_odeNetSolverDataOffset[i]] ) );
		odeSolverData.h = Info::vv_mpAgentODEH[type][i] * Info::durationStateAndGridTimeStep;
	}
	return;
}

inline BOOL MpAgent::getBoolVal( const S32 varIdx ) const {
	CHECK( this->type < Info::numMpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	CHECK( ( varIdx >= 0 ) && ( varIdx < ( S32 )Info::v_mpAgentNumBoolVars[this->type] ) );
	return p_boolVars[varIdx];
}

inline Vector<BOOL> MpAgent::getBoolValArray( void ) const {
	Vector<BOOL> v_val;
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( Info::v_mpAgentNumBoolVars[this->type] > 0 );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	v_val.assign( p_boolVars, p_boolVars + Info::v_mpAgentNumBoolVars[this->type] );
	return v_val;
}

inline void MpAgent::setBoolVal( const S32 varIdx, const BOOL val ) {
	CHECK( this->type < Info::numMpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	CHECK( ( varIdx >= 0 ) && ( varIdx < ( S32 )Info::v_mpAgentNumBoolVars[this->type] ) );
	p_boolVars[varIdx] = val;
	return;
}

inline void MpAgent::setBoolValArray( const Vector<BOOL>& v_val ) {
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( Info::v_mpAgentNumBoolVars[this->type] > 0 );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	BOOL* p_boolVars = ( BOOL* )&( this->v_aux[auxDataInfo.boolVarOffset] );
	CHECK( ( S32 )v_val.size() == ( S32 )Info::v_mpAgentNumBoolVars[this->type] );
	if( v_val.size() > 0 ) {
		memcpy( p_boolVars, &v_val[0], Info::v_mpAgentNumBoolVars[this->type] * sizeof( BOOL ) );
	}
	return;
}

inline REAL MpAgent::getODEVal( const S32 odeNetIdx, const S32 varIdx ) const {
	CHECK( this->type < Info::numMpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	CHECK( varIdx < ( S32 )Info::vv_mpAgentNumODENetVars[this->type][odeNetIdx] );
	return p_odeNetVars[varIdx];
}

inline Vector<REAL> MpAgent::getODEValArray( const S32 odeNetIdx ) const {
	Vector<REAL> v_val;
	CHECK( this->type < Info::numMpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	v_val.assign( p_odeNetVars, p_odeNetVars + Info::vv_mpAgentNumODENetVars[this->type][odeNetIdx] );
	return v_val;
}

inline void MpAgent::setODEVal( const S32 odeNetIdx, const S32 varIdx, REAL val ) {
	CHECK( this->type < Info::numMpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	CHECK( varIdx < ( S32 )Info::vv_mpAgentNumODENetVars[this->type][odeNetIdx] );
	p_odeNetVars[varIdx] = val;
	return;
}

inline void MpAgent::setODEValArray( const S32 odeNetIdx, const Vector<REAL>& v_val ) {
	CHECK( this->type < Info::numMpAgentTypes );
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type];
	CHECK( odeNetIdx < ( S32 )auxDataInfo.v_odeNetVarOffset.size() );
	REAL* p_odeNetVars = ( REAL* )&( this->v_aux[auxDataInfo.v_odeNetVarOffset[odeNetIdx]] );
	CHECK( ( S32 )v_val.size() == Info::vv_mpAgentNumODENetVars[this->type][odeNetIdx] );
	if( v_val.size() > 0 ) {
		memcpy( p_odeNetVars, &v_val[0], Info::vv_mpAgentNumODENetVars[this->type][odeNetIdx] * sizeof( REAL ) );
	}
	return;
}

inline REAL MpAgent::getModelReal( const S32 idx ) const {
	const REAL* p_reals = NULL;
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_mpAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelRealOffset] );
	return p_reals[idx];
}

inline Vector<REAL> MpAgent::getModelRealArray( void ) const {
	Vector<REAL> v_val;
	CHECK( this->type < Info::numMpAgentTypes );
	if( Info::v_mpAgentNumStateModelReals[this->type] > 0 ) {
		const REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelRealOffset] );
		v_val.assign( p_reals, p_reals + Info::v_mpAgentNumStateModelReals[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void MpAgent::setModelReal( const S32 idx, const REAL val ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_mpAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelRealOffset] );
	p_reals[idx] = val;
	return;
}

inline void MpAgent::setModelRealArray( const Vector<REAL>& v_val ) {
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( S32 )v_val.size() == Info::v_mpAgentNumStateModelReals[this->type] );
	if( v_val.size() > 0 ) {
		REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelRealOffset] );
		memcpy( p_reals, &v_val[0], Info::v_mpAgentNumStateModelReals[this->type] * sizeof( REAL ) );
	}
	return;
}

inline void MpAgent::incModelReal( const S32 idx, const REAL inc ) {
	REAL* p_reals = NULL;
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_mpAgentNumStateModelReals[this->type] ) );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelRealOffset] );
	p_reals[idx] += inc;
	return;
}

inline S32 MpAgent::getModelInt( const S32 idx ) const {
	const S32* p_ints = NULL;
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_mpAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelIntOffset] );
	return p_ints[idx];
}

inline Vector<S32> MpAgent::getModelIntArray( void ) const {
	Vector<S32> v_val;
	CHECK( this->type < Info::numMpAgentTypes );
	if( Info::v_mpAgentNumStateModelInts[this->type] > 0 ) {
		const S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelIntOffset] );
		v_val.assign( p_ints, p_ints + Info::v_mpAgentNumStateModelInts[this->type] );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void MpAgent::setModelInt( const S32 idx, const S32 val ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_mpAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelIntOffset] );
	p_ints[idx] = val;
	return;
}

inline void MpAgent::setModelIntArray( const Vector<S32>& v_val ) {
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( S32 )v_val.size() == Info::v_mpAgentNumStateModelInts[this->type] );
	if( v_val.size() > 0 ) {
		S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelIntOffset] );
		memcpy( p_ints, &v_val[0], Info::v_mpAgentNumStateModelInts[this->type] * sizeof( S32 ) );
	}
	return;
}

inline void MpAgent::incModelInt( const S32 idx, const S32 inc ) {
	S32* p_ints = NULL;
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( ( idx >= 0 ) && ( idx < Info::v_mpAgentNumStateModelInts[this->type] ) );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].stateModelIntOffset] );
	p_ints[idx] += inc;
	return;
}

inline MpAgent& MpAgent::operator=( const MpAgent& mpAgentSrc ) {
	this->type = mpAgentSrc.type;
	if( this->v_aux.size() != mpAgentSrc.v_aux.size() ) {
		this->v_aux.resize( mpAgentSrc.v_aux.size() );
	}
	if( mpAgentSrc.v_aux.size() > 0 ) {
		memcpy( &( this->v_aux[0] ), &( mpAgentSrc.v_aux[0] ), mpAgentSrc.v_aux.size() * sizeof( U8 ) );
	}
	return *this;
}

inline ODESolverData& MpAgent::getODENetSolverDataRef( const S32 odeNetIdx ) {
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( odeNetIdx < Info::v_mpAgentNumODENets[this->type] );
	return *( ( ODESolverData* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].v_odeNetSolverDataOffset[odeNetIdx]] ) );
}

inline REAL* MpAgent::getODENetVarArrayPtr( const S32 odeNetIdx ) {
	CHECK( this->type < Info::numMpAgentTypes );
	CHECK( odeNetIdx < Info::v_mpAgentNumODENets[this->type] );
	return ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[AGENT_CLASS_MPAGENT][this->type].v_odeNetVarOffset[odeNetIdx]] );
}

inline SubAgent::SubAgent( void ) {
	this->state.type = ( agentType_t )INVALID_TYPE;
	this->state.radius = 0.0;
	this->state.v_aux.clear();
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->vOffset[dim] = 0.0;
	}
}

inline SubAgent::SubAgent( const agentType_t type ) {
	CHECK( type < Info::numSubAgentTypes );
	this->state.type = ( agentType_t )INVALID_TYPE;
	this->state.radius = 0.0;
	this->state.v_aux.clear();
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->vOffset[dim] = 0.0;
	}
	this->state.setType( type );
}

inline SubAgent::~SubAgent( void ) {
	/* nothing to do */
}
#endif/* HAS_MPAGENT */

#if HAS_SPAGENT
inline SpAgent::SpAgent( void ) {
	this->state.type = ( agentType_t )INVALID_TYPE;
	this->state.radius = 0.0;
	this->state.v_aux.clear();
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->vOffset[dim] = 0.0;
	}
}

inline SpAgent::SpAgent( const agentType_t type ) {
	CHECK( type < Info::numSpAgentTypes );
	this->state.type = ( agentType_t )INVALID_TYPE;
	this->state.radius = 0.0;
	this->state.v_aux.clear();
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->vOffset[dim] = 0.0;
	}
	this->state.setType( type );
}

inline SpAgent::~SpAgent( void ) {
	/* nothing to do */
}
#endif/* HAS_SPAGENT */

inline void MechIntrctData::setClassAndType( agent_class_e agentClass, const agentType_t type ) {
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( type < Info::numSpAgentTypes );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( type < Info::numSubAgentTypes );
	}
#endif
	else {
		CHECK( 0 );
	}
	AgentAuxDataInfo& auxDataInfo = Info::av_agentAuxDataInfo[agentClass][type];
	this->agentClass = agentClass;
	this->type = type;
	this->v_aux.assign( auxDataInfo.mechIntrctDataSize, 0 );
	return;
}

inline agent_class_e MechIntrctData::getClass( void ) const {
	return this->agentClass;
}

inline agentType_t MechIntrctData::getType( void ) const {
	return this->type;
}

inline REAL MechIntrctData::getModelReal( const S32 idx ) const {
	const REAL* p_reals = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealOffset] );
	return p_reals[idx];
}

inline Vector<REAL> MechIntrctData::getModelRealArray( void ) const {
	Vector<REAL> v_val;
	S32 numModelReals = 0;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		numModelReals = Info::v_spAgentNumMechIntrctModelReals[this->type];
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		numModelReals = Info::v_subAgentNumMechIntrctModelReals[this->type];
	}
#endif
	else {
		CHECK( 0 );
	}
	if( numModelReals > 0 ) {
		const REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealOffset] );
		v_val.assign( p_reals, p_reals + numModelReals );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void MechIntrctData::setModelReal( const S32 idx, const REAL val ) {
	BOOL* p_changeFlags = NULL;
	REAL* p_reals = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealChangeFlagOffset] );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealOffset] );
	p_changeFlags[idx] = true;
	p_reals[idx] = val;
	return;
}

inline void MechIntrctData::setModelRealArray( const Vector<REAL>& v_val ) {
	S32 numModelReals = 0;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		numModelReals = Info::v_spAgentNumMechIntrctModelReals[this->type];
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		numModelReals = Info::v_subAgentNumMechIntrctModelReals[this->type];
	}
#endif
	else {
		CHECK( 0 );
	}
	if( numModelReals > 0 ) {
		BOOL* p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealChangeFlagOffset] );
		REAL* p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealOffset] );
		CHECK( ( S32 )v_val.size() == numModelReals );
		CHECK( sizeof( BOOL ) == 1 );
		memset( p_changeFlags, true, numModelReals );
		memcpy( p_reals, &v_val[0], numModelReals * sizeof( REAL ) );
	}
	return;
}

inline void MechIntrctData::incModelReal( const S32 idx, const REAL inc ) {
	BOOL* p_changeFlags = NULL;
	REAL* p_reals = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealChangeFlagOffset] );
	p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealOffset] );
	p_changeFlags[idx] = true;
	p_reals[idx] += inc;
	return;
}

inline S32 MechIntrctData::getModelInt( const S32 idx ) const {
	const S32* p_ints = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntOffset] );
	return p_ints[idx];
}

inline Vector<S32> MechIntrctData::getModelIntArray( void ) const {
	Vector<S32> v_val;
	S32 numModelInts = 0;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		numModelInts = Info::v_spAgentNumMechIntrctModelInts[this->type];
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		numModelInts = Info::v_subAgentNumMechIntrctModelInts[this->type];
	}
#endif
	else {
		CHECK( 0 );
	}
	if( numModelInts > 0 ) {
		const S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntOffset] );
		v_val.assign( p_ints, p_ints + numModelInts );
	}
	else {
		CHECK( v_val.size() == 0 );
	}
	return v_val;
}

inline void MechIntrctData::setModelInt( const S32 idx, const S32 val ) {
	BOOL* p_changeFlags = NULL;
	S32* p_ints = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntChangeFlagOffset] );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntOffset] );
	p_changeFlags[idx] = true;
	p_ints[idx] = val;
	return;
}

inline void MechIntrctData::setModelIntArray( const Vector<S32>& v_val ) {
	S32 numModelInts = 0;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		numModelInts = Info::v_spAgentNumMechIntrctModelInts[this->type];
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		numModelInts = Info::v_subAgentNumMechIntrctModelInts[this->type];
	}
#endif
	else {
		CHECK( 0 );
	}
	if( numModelInts > 0 ) {
		BOOL* p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntChangeFlagOffset] );
		S32* p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntOffset] );
		CHECK( ( S32 )v_val.size() == numModelInts );
		CHECK( sizeof( BOOL ) == 1 );
		memset( p_changeFlags, true, numModelInts );
		memcpy( p_ints, &v_val[0], numModelInts * sizeof( S32 ) );
	}
	return;
}

inline void MechIntrctData::incModelInt( const S32 idx, const S32 inc ) {
	BOOL* p_changeFlags = NULL;
	S32* p_ints = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntChangeFlagOffset] );
	p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntOffset] );
	p_changeFlags[idx] = true;
	p_ints[idx] += inc;
	return;
}

inline void MechIntrctData::resetChangeFlag( void ) {
	BOOL* p_changeFlags = NULL;
	S32 numModelReals = 0;
	S32 numModelInts = 0;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		numModelReals = Info::v_spAgentNumMechIntrctModelReals[this->type];
		numModelInts = Info::v_spAgentNumMechIntrctModelInts[this->type];
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		numModelReals = Info::v_subAgentNumMechIntrctModelReals[this->type];
		numModelInts = Info::v_subAgentNumMechIntrctModelInts[this->type];
	}
#endif
	else {
		CHECK( 0 );
	}
	if( numModelReals > 0 ) {
		p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealChangeFlagOffset] );
		CHECK( sizeof( BOOL ) == 1 );
		memset( p_changeFlags, false, numModelReals );
	}
	if( numModelInts > 0 ) {
		p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntChangeFlagOffset] );
		CHECK( sizeof( BOOL ) == 1 );
		memset( p_changeFlags, false, numModelInts );
	}
	return;
}

inline void MechIntrctData::resetModelVar( void ) {
	REAL* p_reals = NULL;
	S32* p_ints = NULL;
	S32 numModelReals = 0;
	S32 numModelInts = 0;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		numModelReals = Info::v_spAgentNumMechIntrctModelReals[this->type];
		numModelInts = Info::v_spAgentNumMechIntrctModelInts[this->type];
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		numModelReals = Info::v_subAgentNumMechIntrctModelReals[this->type];
		numModelInts = Info::v_subAgentNumMechIntrctModelInts[this->type];
	}
#endif
	else {
		CHECK( 0 );
	}
	if( numModelReals > 0 ) {
		p_reals = ( REAL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealOffset] );
		for( S32 i = 0 ; i < numModelReals ; i++ ) {
			p_reals[i] = 0.0;
		}
	}
	if( numModelInts > 0 ) {
		p_ints = ( S32* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntOffset] );
		for( S32 i = 0 ; i < numModelInts ; i++ ) {
			p_ints[i] = 0;
		}
	}
	return;
}

inline BOOL MechIntrctData::getModelRealChanged( const S32 idx ) const {
	const BOOL* p_changeFlags = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelReals[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelRealChangeFlagOffset] );
	CHECK( sizeof( BOOL ) == 1 );
	return p_changeFlags[idx];
}

inline BOOL MechIntrctData::getModelIntChanged( const S32 idx ) const {
	const BOOL* p_changeFlags = NULL;
	if( agentClass >= NUM_AGENT_CLASSES ) {
		CHECK( 0 );
	}
#if HAS_SPAGENT
	else if( agentClass == AGENT_CLASS_SPAGENT ) {
		CHECK( this->type < Info::numSpAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_spAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
#if HAS_MPAGENT
	else if( agentClass == AGENT_CLASS_SUBAGENT ) {
		CHECK( this->type < Info::numSubAgentTypes );
		CHECK( ( idx >= 0 ) && ( idx < Info::v_subAgentNumMechIntrctModelInts[this->type] ) );
	}
#endif
	else {
		CHECK( 0 );
	}
	p_changeFlags = ( BOOL* )&( this->v_aux[Info::av_agentAuxDataInfo[this->agentClass][this->type].mechIntrctModelIntChangeFlagOffset] );
	CHECK( sizeof( BOOL ) == 1 );
	return p_changeFlags[idx];
}

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
inline NbrUBAgentData::NbrUBAgentData( void ) {
	for( S32 i = 0 ; i < 3 * 3 * 3 ; i++ ) {
		this->a_valid[i] = false;
		this->ap_val[i] = NULL;
	}
}

inline NbrUBAgentData::~NbrUBAgentData( void ) {
	/* nothing to do */
}
#endif

inline BOOL NbrUBAgentData::getValidFlag( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	return this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )];
}

inline BOOL NbrUBAgentData::getValidFlag( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) && ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) && ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) && ( nbrVOffset[2] <= 1 ) );
	return this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )];
}

inline const UBAgentData* NbrUBAgentData::getConstPtr( const S32 nbrXOffset, const S32 nbrYOffset, const S32 nbrZOffset ) const {
	CHECK( ( nbrXOffset >= -1 ) && ( nbrXOffset <= 1 ) );
	CHECK( ( nbrYOffset >= -1 ) && ( nbrYOffset <= 1 ) );
	CHECK( ( nbrZOffset >= -1 ) && ( nbrZOffset <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )] == true );
	return this->ap_val[( 1 + nbrXOffset ) * 3 * 3 + ( 1 + nbrYOffset ) * 3 + ( 1 + nbrZOffset )];
}

inline const UBAgentData* NbrUBAgentData::getConstPtr( const VIdx& nbrVOffset ) const {
	CHECK( ( nbrVOffset[0] >= -1 ) && ( nbrVOffset[0] <= 1 ) );
	CHECK( ( nbrVOffset[1] >= -1 ) && ( nbrVOffset[1] <= 1 ) );
	CHECK( ( nbrVOffset[2] >= -1 ) && ( nbrVOffset[2] <= 1 ) );
	CHECK( this->a_valid[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )] == true );
	return this->ap_val[( 1 + nbrVOffset[0] ) * 3 * 3 + ( 1 + nbrVOffset[1] ) * 3 + ( 1 + nbrVOffset[2] )];
}

#endif/* #ifndef __AGENT_CLASS_H__ */


#include <math.h>

#include "biocellion.h"
#include "model_if.h"

#include "model_routine.h"

using namespace std;

void ModelIf::addAgents( const BOOL init, const VIdx& startVIdx, const VIdx& regionSize, const IfGridBoxData<BOOL>& ifGridHabitableBoxData, Vector<MpAgent>& v_newMpAgent/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<VIdx> >& vv_newSubAgentVIdx/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<SubAgentState> >& vv_newSubAgentState/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<VReal> >& vv_newSubAgentOffset/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx0/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx1/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<JunctionEnd> >& vv_end0/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<JunctionEnd> >& vv_end1/* dummy if HAS_MPAGENT == 0 */, Vector<VIdx>& v_newSpAgentVIdx/* dummy if HAS_SPAGENT == 0 */, Vector<SpAgentState>& v_newSpAgentState/* dummy if HAS_SPAGENT == 0 */, Vector<VReal>& v_newSpAgentOffset/* dummy if HAS_SPAGENT == 0 */ ) {
#if ENABLE_CHECK
	VIdx endVIdx;
#if HAS_MPAGENT
	VIdx subAgentValidRegionStartVIdx;
	VIdx subAgentValidRegionEndVIdx;
#endif
#endif

	CHECK( v_newMpAgent.size() == 0 );
	CHECK( vv_newSubAgentState.size() == 0 );
	CHECK( vv_newSubAgentOffset.size() == 0 );
	CHECK( vv_junctionSubAgentIdx0.size() == 0 );
	CHECK( vv_junctionSubAgentIdx1.size() == 0 );
	CHECK( vv_end0.size() == 0 );
	CHECK( vv_end1.size() == 0 );
	CHECK( v_newSpAgentState.size() == 0 );
	CHECK( v_newSpAgentOffset.size() == 0 );
	
#if ENABLE_CHECK
	endVIdx = startVIdx + regionSize - VIdx::UNIT;
#if HAS_MPAGENT
	subAgentValidRegionStartVIdx = startVIdx - MPAGENT_MAX_WIDTH;
	subAgentValidRegionEndVIdx = endVIdx - MPAGENT_MAX_WIDTH;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		if( ( Info::a_domainBdryType[dim] == DOMAIN_BDRY_TYPE_NONPERIODIC_HARD_WALL ) || ( Info::a_domainBdryType[dim] == DOMAIN_BDRY_TYPE_NONPERIODIC_HARD_WALL ) ) {
			if( subAgentValidRegionStartVIdx[dim] < 0 ) {
				CHECK( startVIdx[dim] == 0 );
				subAgentValidRegionStartVIdx[dim] = 0;
			}
			else if( subAgentValidRegionEndVIdx[dim] >= Info::a_domainSize[dim] ) {
				CHECK( endVIdx[dim] == ( idx_t )( Info::a_domainSize[dim] - 1 ) );
				subAgentValidRegionEndVIdx[dim] = ( idx_t )( Info::a_domainSize[dim] - 1 );
			}
		}
		else {
			CHECK( Info::a_domainBdryType[dim] == DOMAIN_BDRY_TYPE_PERIODIC );
		}
	}
#endif
#endif

#if HAS_MPAGENT
	if( Info::numMpAgentTypes > 0 ) {
#if 1
		ERROR( "unimplemented." );
#else
		ModelRoutine::addMpAgents( init, startVIdx, regionSize, ifGridHabitableBoxData, v_newMpAgent, vv_newSubAgentVIdx, vv_newSubAgentState, vv_newSubAgentOffset, vv_junctionSubAgentIdx0, vv_junctionSubAgentIdx1, vv_end0, vv_end1 );
#if ENABLE_CHECK
		CHECK( v_newMpAgent.size() == vv_newSubAgentVIdx.size() );
		CHECK( v_newMpAgent.size() == vv_newSubAgentState.size() );
		CHECK( v_newMpAgent.size() == vv_newSubAgentOffset.size() );
		CHECK( v_newMpAgent.size() == vv_junctionSubAgentIdx0.size() );
		CHECK( v_newMpAgent.size() == vv_junctionSubAgentIdx1.size() );
		CHECK( v_newMpAgent.size() == vv_end0.size() );
		CHECK( v_newMpAgent.size() == vv_end1.size() );
		for( partMpAgentIdx_t i = 0 ; i < ( partMpAgentIdx_t )v_newMpAgent.size() ; i++ ) {
			CHECK( vv_newSubAgentVIdx[i].size() > 0 );
			CHECK( vv_newSubAgentVIdx[i].size() == vv_newSubAgentState[i].size() );
			CHECK( vv_newSubAgentVIdx[i].size() == vv_newSubAgentOffset[i].size() );

			CHECK( vv_junctionSubAgentIdx0[i].size() == vv_junctionSubAgentIdx1[i].size() );
			CHECK( vv_junctionSubAgentIdx0[i].size() == vv_end0[i].size() );
			CHECK( vv_junctionSubAgentIdx0[i].size() == vv_end1[i].size() );

			for( subAgentIdx_t j = 0 ; j < ( subAgentIdx_t )vv_newSubAgentVIdx[i].size() ; j++ ) {
				const VIdx& vIdx = vv_newSubAgentVIdx[i][j];
				const VReal& vOffset = vv_newSubAgentOffset[i][j];
				VIdx partVOffset;
				VIdx partStartVIdx;
				for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
					CHECK( ( vIdx[dim] >= subAgentValidRegionStartVIdx[dim] ) && ( vIdx[dim] <= subAgentValidRegionEndVIdx[dim] ) );
					CHECK( ( vOffset[dim] >= Info::ifGridSpacing * -0.5 ) && ( vOffset[dim] <= Info::ifGridSpacing * 0.5 ) );
				}
				CHECK( ifGridHabitableBoxData.get( vIdx ) == true );
			}
		}
#endif
#endif
	}
#endif

#if HAS_SPAGENT
	if( Info::numSpAgentTypes > 0 ) {
		ModelRoutine::addSpAgents( init, startVIdx, regionSize, ifGridHabitableBoxData, v_newSpAgentVIdx, v_newSpAgentState, v_newSpAgentOffset );
#if ENABLE_CHECK
		CHECK( v_newSpAgentVIdx.size() == v_newSpAgentState.size() );
		CHECK( v_newSpAgentVIdx.size() == v_newSpAgentOffset.size() );
		for( S64 i = 0 ; i < ( S64 )v_newSpAgentVIdx.size() ; i++ ) {
			const VIdx& vIdx = v_newSpAgentVIdx[i];
			const VReal& vOffset = v_newSpAgentOffset[i];
			for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
				CHECK( ( vIdx[dim] >= startVIdx[dim] ) && ( vIdx[dim] <= endVIdx[dim] ) );
				CHECK( ( vOffset[dim] >= Info::ifGridSpacing * -0.5 ) && ( vOffset[dim] <= Info::ifGridSpacing * 0.5 ) );
			}
			CHECK( ifGridHabitableBoxData.get( vIdx ) == true );
		}
#endif
	}
#endif

	return;
}

#if HAS_MPAGENT
void ModelIf::mpAgentCRNODERHS( const S32 odeNetIdx, const MpAgent& mpAgent, const Vector<VIdx>& v_subAgentVIdx, const Vector<SubAgent*>& vp_subAgent, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, const Vector<double>& v_y, Vector<double>& v_f ) {
	( void )odeNetIdx;
	( void )mpAgent;
	( void )v_subAgentVIdx;
	( void )vp_subAgent;
	( void )v_nbrUBEnv;
	( void )v_y;
	( void )v_f;

	ERROR( "unimplemented." );

	return;
}

void ModelIf::updateMpAgentState( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent, Vector<SubAgentState*>& vp_subAgentState ) {
	( void )v_subAgentVIdx;
	( void )vp_subJunctionData;
	( void )v_subAgentOffset;
	( void )v_nbrUBEnv;
	( void )mpAgent;
	( void )vp_subAgentState;

	ERROR( "unimplemented." );

	return;
}

void ModelIf::mpAgentSecretionByMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_subMechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent, Vector<SubAgentState*>& vp_subAgentState, Vector<subAgentIdx_t>& v_srcIdx, Vector<MpAgent>& v_mpAgent, Vector<Vector<SubAgentState> >& vv_subAgentState, Vector<Vector<VReal> >& vv_subAgentDisp, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx0, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx1, Vector<Vector<JunctionEnd> >& vv_end0, Vector<Vector<JunctionEnd> >& vv_end1 ) {
	( void )v_subAgentVIdx;
	( void )vp_subJunctionData;
	( void )v_subAgentOffset;
	( void )vp_subMechIntrctData;
	( void )v_nbrUBEnv;
	( void )mpAgent;
	( void )vp_subAgentState;
	( void )v_srcIdx;
	( void )v_mpAgent;
	( void )vv_subAgentState;
	( void )vv_subAgentDisp;
	( void )vv_junctionSubAgentIdx0;
	( void )vv_junctionSubAgentIdx1;
	( void )vv_end0;
	( void )vv_end1;

	ERROR( "unimplemented." );

	return;
}

#if HAS_SPAGENT
void ModelIf::spAgentSecretionByMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_subMechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent, Vector<SubAgentState*>& vp_subAgentState, Vector<subAgentIdx_t>& v_srcIdx, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentDisp ) {
	( void )v_subAgentVIdx;
	( void )vp_subJunctionData;
	( void )v_subAgentOffset;
	( void )vp_subMechIntrctData;
	( void )v_nbrUBEnv;
	( void )mpAgent;
	( void )vp_subAgentState;
	( void )v_srcIdx;
	( void )v_spAgentState;
	( void )v_spAgentDisp;

	ERROR( "unimplemented." );

	return;
}
#endif

void ModelIf::updateMpAgentBirthDeath( const MpAgent& mpAgent, const Vector<VIdx>& v_subAgentVIdx, const Vector<SubAgent*>& vp_subAgent, const Vector<const MechIntrctData*>& vp_subMechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, BOOL& divide, BOOL& disappear ) {
	( void )mpAgent;
	( void )v_subAgentVIdx;
	( void )vp_subAgent;
	( void )vp_subMechIntrctData;
	( void )v_nbrUBEnv;
	( void )divide;
	( void )disappear;

	divide = false;
	disappear = false;

	ERROR( "unimplemented." );

	CHECK( ( divide == false ) || ( disappear == false ) );/* dividing cells cannot disappear */

	return;
}

void ModelIf::adjustMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_subMechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent, Vector<SubAgentState*>& vp_subAgentState, Vector<VReal>& v_subAgentDisp, Vector<subAgentIdx_t>& v_divideSubAgentIdx, Vector<SubAgentState>& v_daughterSubAgentState, Vector<VReal>& v_daughterSubAgentDisp, Vector<Vector<BOOL> >& vv_junctionDivide/* true if belongs to the mother sub-agent, false if belongs to the daughter sub-agent */, Vector<BOOL>& v_motherDaughterLinked, Vector<JunctionEnd>& v_motherEnd, Vector<JunctionEnd>& v_daughterEnd, Vector<subAgentIdx_t>& v_disappearSubAgentIdx ) {
	( void )v_subAgentVIdx;
	( void )vp_subJunctionData;
	( void )v_subAgentOffset;
	( void )vp_subMechIntrctData;
	( void )v_nbrUBEnv;
	( void )mpAgent;
	( void )vp_subAgentState;
	( void )v_subAgentDisp;
	( void )v_divideSubAgentIdx;
	( void )v_daughterSubAgentState;
	( void )v_daughterSubAgentDisp;
	( void )vv_junctionDivide;
	( void )v_motherDaughterLinked;
	( void )v_motherEnd;
	( void )v_daughterEnd;
	( void )v_disappearSubAgentIdx;

	ERROR( "unimplemented." );

	return;
}

void ModelIf::divideMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_subMechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& motherMpAgent/* INOUT */, MpAgent& daughterMpAgent, Vector<SubAgentState*>& vp_subAgentState, Vector<VReal>& v_subAgentDisp, Vector<BOOL>& v_divide/* true if belongs to the mother multi-particle agent, false if belongs to the daughter multi-particle agent */ ) {
	( void )v_subAgentVIdx;
	( void )vp_subJunctionData;
	( void )v_subAgentOffset;
	( void )vp_subMechIntrctData;
	( void )v_nbrUBEnv;
	( void )motherMpAgent;
	( void )daughterMpAgent;
	( void )vp_subAgentState;
	( void )v_subAgentDisp;
	( void )v_divide;

	ERROR( "unimplemented." );

	return;
}
#endif

#if HAS_SPAGENT
void ModelIf::spAgentCRNODERHS( const S32 odeNetIdx, const VIdx& vIdx, const SpAgent& spAgent, const NbrUBEnv& nbrUBEnv, const Vector<double>& v_y, Vector<double>& v_f ) {
	CHECK( v_y.size() == v_f.size() );
	CHECK( ( S32 )v_f.size() == Info::vv_spAgentNumODENetVars[spAgent.state.getType()][odeNetIdx] );

	ModelRoutine::spAgentCRNODERHS( odeNetIdx, vIdx, spAgent, nbrUBEnv, v_y, v_f );

	return;
}

void ModelIf::updateSpAgentState( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const NbrUBEnv& nbrUBEnv, SpAgentState& state ) {
	ModelRoutine::updateSpAgentState( vIdx, junctionData, vOffset, nbrUBEnv, state );

	return;
}

#if HAS_MPAGENT
void ModelIf::mpAgentSecretionBySpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state, Vector<MpAgent>& v_mpAgent, Vector<Vector<SubAgentState> >& vv_subAgentState, Vector<Vector<VReal> >& vv_subAgentDisp, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx0, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx1, Vector<Vector<JunctionEnd> >& vv_end0, Vector<Vector<JunctionEnd> >& vv_end1 ) {
	( void )vIdx;
	( void )junctionData;
	( void )vOffset;
	( void )mechIntrctData;
	( void )nbrUBEnv;
	( void )state;
	( void )v_mpAgent;
	( void )vv_subAgentState;
	( void )vv_subAgentDisp;
	( void )vv_junctionSubAgentIdx0;
	( void )vv_junctionSubAgentIdx1;
	( void )vv_end0;
	( void )vv_end1;

	ERROR( "unimplemented." );

	return;
}
#endif

void ModelIf::spAgentSecretionBySpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentDisp ) {
	CHECK( v_spAgentState.size() == 0 );
	CHECK( v_spAgentDisp.size() == 0 );

	ModelRoutine::spAgentSecretionBySpAgent( vIdx, junctionData, vOffset, mechIntrctData, nbrUBEnv, state, v_spAgentState, v_spAgentDisp );
#if ENABLE_CHECK
	CHECK( v_spAgentState.size() == v_spAgentDisp.size() );

	for( ubAgentIdx_t i = 0 ; i < ( ubAgentIdx_t )v_spAgentDisp.size() ; i++ ) {
		for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
			CHECK( FABS( v_spAgentDisp[i][dim] ) <= Info::ifGridSpacing );
		}
	}
#endif

	return;
}

void ModelIf::updateSpAgentBirthDeath( const VIdx& vIdx, const SpAgent& spAgent, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, BOOL& divide, BOOL& disappear ) {
	divide = false;
	disappear = false;

	ModelRoutine::updateSpAgentBirthDeath( vIdx, spAgent, mechIntrctData, nbrUBEnv, divide, disappear );

	CHECK( ( divide == false ) || ( disappear == false ) );/* dividing cells cannot disappear */

	return;
}

void ModelIf::adjustSpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state, VReal& disp ) {
	disp = VReal::ZERO;
	ModelRoutine::adjustSpAgent( vIdx, junctionData, vOffset, mechIntrctData, nbrUBEnv, state, disp );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( FABS( disp[dim] ) <= Info::ifGridSpacing );
	}

	return;
}

void ModelIf::divideSpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& motherState/* INOUT */, VReal& motherDisp, SpAgentState& daughterState, VReal& daughterDisp, Vector<BOOL>& v_junctionDivide, BOOL& motherDaughterLinked, JunctionEnd& motherEnd, JunctionEnd& daughterEnd ) {
	CHECK( ( S32 )v_junctionDivide.size() == junctionData.getNumJunctions() );

	motherDisp = VReal::ZERO;
	daughterDisp = VReal::ZERO;
	motherDaughterLinked = false;
	ModelRoutine::divideSpAgent( vIdx, junctionData, vOffset, mechIntrctData, nbrUBEnv, motherState, motherDisp, daughterState, daughterDisp, v_junctionDivide, motherDaughterLinked, motherEnd, daughterEnd );

	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( FABS( motherDisp[dim] ) <= Info::ifGridSpacing );
		CHECK( FABS( daughterDisp[dim] ) <= Info::ifGridSpacing );
	}
	CHECK( ( S32 )v_junctionDivide.size() == junctionData.getNumJunctions() );

	return;
}
#endif


#include <math.h>

#include "biocellion.h"
#include "model_if.h"

#include "model_routine.h"

using namespace std;

#if HAS_MPAGENT
void ModelIf::updateSubAgentOutput( const VIdx& vIdx, const Vector<MpAgent>& v_mpAgent, const Vector<SubAgent>& v_subAgent, const Vector<partMpAgentIdx_t>& v_mpAgentIdx, const ubAgentIdx_t offsetIdx, Vector<REAL>& v_color, Vector<Vector<REAL> >& vv_extraScalar, Vector<Vector<REAL> >& vv_extraVector ) {
	( void )vIdx;
	( void )v_mpAgent;
	( void )v_subAgent;
	( void )v_mpAgentIdx;
	( void )offsetIdx;
	( void )v_color;
	( void )vv_extraScalar;
	( void )vv_extraVector;
	CHECK( v_subAgent.size() == v_mpAgentIdx.size() );
	CHECK( offsetIdx + ( ubAgentIdx_t )v_subAgent.size() <= ( ubAgentIdx_t )v_color.size() );
	CHECK( vv_extraScalar.size() == Info::v_particleExtraOutputScalarVarName.size() );
	CHECK( vv_extraVector.size() == Info::v_particleExtraOutputVectorVarName.size() );
	for( S32 i = 0 ; i < ( S32 )Info::v_particleExtraOutputScalarVarName.size() ; i++ ) {
		CHECK( vv_extraScalar[i].size() == v_color.size() );
	}
	for( S32 i = 0 ; i < ( S32 )Info::v_particleExtraOutputVectorVarName.size() ; i++ ) {
		CHECK( vv_extraVector[i].size() == v_color.size() * DIMENSION );
	}

	ERROR( "unimplemented." );

	return;
}
#endif

#if HAS_SPAGENT
void ModelIf::updateSpAgentOutput( const VIdx& vIdx, const Vector<SpAgent>& v_spAgent, const ubAgentIdx_t offsetIdx, Vector<REAL>& v_color, Vector<Vector<REAL> >& vv_extraScalar, Vector<Vector<REAL> >& vv_extraVector ) {
	CHECK( offsetIdx + ( ubAgentIdx_t )v_spAgent.size() <= ( ubAgentIdx_t )v_color.size() );
	CHECK( vv_extraScalar.size() == Info::v_particleExtraOutputScalarVarName.size() );
	CHECK( vv_extraVector.size() == Info::v_particleExtraOutputVectorVarName.size() );
	for( S32 i = 0 ; i < ( S32 )Info::v_particleExtraOutputScalarVarName.size() ; i++ ) {
		CHECK( vv_extraScalar[i].size() == v_color.size() );
	}
	for( S32 i = 0 ; i < ( S32 )Info::v_particleExtraOutputVectorVarName.size() ; i++ ) {
		CHECK( vv_extraVector[i].size() == v_color.size() * DIMENSION );
	}

	for( ubAgentIdx_t i = 0 ; i < ( ubAgentIdx_t )v_spAgent.size() ; i++ ) {
		const SpAgent& spAgent = v_spAgent[i];
		REAL& color = v_color[offsetIdx + i];
		Vector<REAL> v_extraScalar;
		Vector<VReal> v_extraVector;

		v_extraScalar.assign( Info::v_particleExtraOutputScalarVarName.size(), 0.0 );
		v_extraVector.assign( Info::v_particleExtraOutputVectorVarName.size(), VReal::ZERO );
		ModelRoutine::updateSpAgentOutput( vIdx, spAgent, color, v_extraScalar, v_extraVector );
		CHECK( v_extraScalar.size() == Info::v_particleExtraOutputScalarVarName.size() );
		CHECK( v_extraVector.size() == Info::v_particleExtraOutputVectorVarName.size() );

		for( S32 j = 0 ; j < ( S32 )Info::v_particleExtraOutputScalarVarName.size() ; j++ ) {
			vv_extraScalar[j][offsetIdx + i] = v_extraScalar[j];
		}
		for( S32 j = 0 ; j < ( S32 )Info::v_particleExtraOutputVectorVarName.size() ; j++ ) {
			for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
				vv_extraVector[j][( offsetIdx + i ) * DIMENSION + dim] = v_extraVector[j][dim];
			}
		}
	}

	return;
}
#endif

void ModelIf::updateSummaryVar( const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, const NbrUBEnv& nbrUBEnv, Vector<REAL>& v_realVal/* [elemIdx] */, Vector<S32>& v_intVal/* [elemIdx] */ ) {
	ModelRoutine::updateSummaryVar( vIdx, nbrUBAgentData, nbrUBEnv, v_realVal, v_intVal );
	CHECK( ( S32 )v_realVal.size() == Info::numSummaryReals );
	CHECK( ( S32 )v_intVal.size() == Info::numSummaryInts );
	return;
}


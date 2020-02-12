#include <math.h>

#include "biocellion.h"
#include "model_if.h"

#include "model_routine.h"

using namespace std;

void ModelIf::initIfGridVar( const VIdx& vIdx, const UBAgentData& ubAgentData, UBEnv& ubEnv ) {
	ModelRoutine::initIfGridVar( vIdx, ubAgentData, ubEnv );
#if ENABLE_CHECK
	for( S32 elemIdx = 0 ; elemIdx < Info::numGridPhis ; elemIdx++ ) {
		S32 ratio = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx];
		for( S32 i = 0 ; i < ratio ; i++ ) {
			for( S32 j = 0 ; j < ratio ; j++ ) {
				for( S32 k = 0 ; k < ratio ; k++ ) {
					VIdx subgridVOffset;
					subgridVOffset[0] = i;
					subgridVOffset[1] = j;
					subgridVOffset[2] = k;
					CHECK( ubEnv.getSubgridPhi( subgridVOffset, elemIdx ) >= 0.0 );
				}
			}
		}
	}
#endif

	return;
}

void ModelIf::initIfSubgridKappa( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridKappa ) {/* relevant only if v_gridPhiOutputDivideByKappa[pdeIdx] is set to true in updateFileOutputInfo() */
	ModelRoutine::initIfSubgridKappa( pdeIdx, vIdx, subgridVOffset, ubAgentData, ubEnv, gridKappa );
	CHECK( ( gridKappa > 0.0 ) && ( gridKappa <= 1.0 ) );
	return;
}

void ModelIf::updateIfGridVar( const BOOL pre, const S32 iter, const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, NbrUBEnv& nbrUBEnv ) {
	ModelRoutine::updateIfGridVar( pre, iter, vIdx, nbrUBAgentData, nbrUBEnv );
	return;
}

void ModelIf::updateIfSubgridKappa( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridKappa ) {
	ModelRoutine::updateIfSubgridKappa( pdeIdx, vIdx, subgridVOffset, ubAgentData, ubEnv, gridKappa );
	CHECK( ( gridKappa > 0.0 ) && ( gridKappa <= 1.0 ) );
	return;
}

void ModelIf::updateIfSubgridAlpha( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridAlpha ) {
	ModelRoutine::updateIfSubgridAlpha( elemIdx, vIdx, subgridVOffset, ubAgentData, ubEnv, gridAlpha );
	CHECK( gridAlpha <= 0.0 );
	CHECK( gridAlpha > -1.0 );

	return;
}

void ModelIf::updateIfSubgridBetaInIfRegion( const S32 elemIdx, const S32 dim, const VIdx& vIdx0, const VIdx& subgridVOffset0, const UBAgentData& ubAgentData0, const UBEnv& ubEnv0, const VIdx& vIdx1, const VIdx& subgridVOffset1, const UBAgentData& ubAgentData1, const UBEnv& ubEnv1, REAL& gridBeta ) {
	ModelRoutine::updateIfSubgridBetaInIfRegion( elemIdx, dim, vIdx0, subgridVOffset0, ubAgentData0, ubEnv0, vIdx1, subgridVOffset1, ubAgentData1, ubEnv1, gridBeta );
#if ENABLE_CHECK
	S32 pdeIdx = Info::v_gridPhiPDEIdx[elemIdx];
	pde_type_e pdeType = Info::v_pdeType[pdeIdx];
	if( pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) {
		CHECK( gridBeta > 0.0 );
	}
	else {
		CHECK( ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) );
		CHECK( gridBeta >= 0.0 );
	}
#endif

	return;
}

void ModelIf::updateIfSubgridBetaPDEBufferBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridBeta ) {
	ModelRoutine::updateIfSubgridBetaPDEBufferBdry( elemIdx, dim, vIdx, subgridVOffset, ubAgentData, ubEnv, gridBeta );
#if ENABLE_CHECK
	S32 pdeIdx = Info::v_gridPhiPDEIdx[elemIdx];
	pde_type_e pdeType = Info::v_pdeType[pdeIdx];
	if( pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) {
		CHECK( gridBeta > 0.0 );
	}
	else {
		CHECK( ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) );
		CHECK( gridBeta >= 0.0 );
	}
#endif

	return;
}

void ModelIf::updateIfSubgridBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridBeta ) {
	ModelRoutine::updateIfSubgridBetaDomainBdry( elemIdx, dim, vIdx, subgridVOffset, ubAgentData, ubEnv, gridBeta );
#if ENABLE_CHECK
	S32 pdeIdx = Info::v_gridPhiPDEIdx[elemIdx];
	pde_type_e pdeType = Info::v_pdeType[pdeIdx];
	if( pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) {
		CHECK( gridBeta > 0.0 );
	}
	else {
		CHECK( ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) );
		CHECK( gridBeta >= 0.0 );
	}
#endif

	return;
}

void ModelIf::updateIfSubgridAdvVelInIfRegion( const S32 pdeIdx, const S32 dim, const VIdx& vIdx0, const VIdx& subgridVOffset0, const UBAgentData& ubAgentData0, const UBEnv& ubEnv0, const VIdx& vIdx1, const VIdx& subgridVOffset1, const UBAgentData& ubAgentData1, const UBEnv& ubEnv1, REAL& gridAdvVel ) {
#if 0/* HAS_FLOW */
	ModelRoutine::updateIfSubgridAdvVelInIfRegion( pdeIdx, dim, vIdx0, subgridVOffset0, ubAgentData0, ubEnv0, vIdx1, subgridVOffset1, ubAgentData1, ubEnv1, gridAdvVel );
#else
	ERROR( "unimplemented." );
#endif

	return;
}

void ModelIf::updateIfSubgridAdvVelPDEBufferBdry( const S32 pdeIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridAdvVel ) {
#if 0/* HAS_FLOW */
	ModelRoutine::updateIfSubgridAdvVelPDEBufferBdry( pdeIdx, dim, vIdx, subgridVOffset, ubAgentData, ubEnv, gridAdvVel );
#else
	ERROR( "unimplemented." );
#endif

	return;
}

void ModelIf::updateIfSubgridAdvVelDomainBdry( const S32 pdeIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridAdvVel ) {
#if 0/* HAS_FLOW */
	ModelRoutine::updateIfSubgridAdvVelDomainBdry( pdeIdx, dim, vIdx, subgridVOffset, ubAgentData, ubEnv, gridAdvVel );
#else
	ERROR( "unimplemented." );
#endif

	return;
}

void ModelIf::updateIfSubgridRHSLinear( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridRHS ) {
	ModelRoutine::updateIfSubgridRHSLinear( elemIdx, vIdx, subgridVOffset, ubAgentData, ubEnv, gridRHS );
	CHECK( ( gridRHS >= - REAL_MAX ) && ( gridRHS <= REAL_MAX ) );

	return;
}

void ModelIf::adjustIfSubgridRHSTimeDependentLinear( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnvModelVar& ubEnvModelVar, const REAL gridPhi, REAL& gridRHS/* INOUT */ ) {
	ModelRoutine::adjustIfSubgridRHSTimeDependentLinear( elemIdx, vIdx, subgridVOffset, ubAgentData, ubEnvModelVar, gridPhi, gridRHS );
	CHECK( ( gridRHS >= - REAL_MAX ) && ( gridRHS <= REAL_MAX ) );
	return;
}

void ModelIf::updateIfSubgridRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnvModelVar& ubEnvModelVar, const Vector<REAL>& v_gridPhi/* [idx] */, Vector<double>& v_gridRHS ) {
	if( ( Info::v_pdeType[pdeIdx] == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( Info::v_pdeType[pdeIdx] == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) ) {
		CHECK( ( S32 )v_gridRHS.size() == ( S32 )( Info::vv_pdeGridPhiIdx[pdeIdx].size() ) );
	}
	else {
		CHECK( ( S32 )v_gridRHS.size() == 1 );
	}

	for( S32 i = 0 ; i < ( S32 )v_gridRHS.size() ; i++ ) {
		v_gridRHS[i] = 0.0;
	}
	ModelRoutine::updateIfSubgridRHSTimeDependentSplitting( pdeIdx, vIdx, subgridVOffset, ubAgentData, ubEnvModelVar, v_gridPhi, v_gridRHS );
#if ENABLE_CHECK
	for( S32 i = 0 ; i < ( S32 )v_gridRHS.size() ; i++ ) {
		CHECK( ( v_gridRHS[i] >= - REAL_MAX ) && ( v_gridRHS[i] <= REAL_MAX ) );
	}
#endif

	return;
}

void ModelIf::updateIfGridAMRTags( const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, const NbrUBEnv& nbrUBEnv, Vector<S32>& v_finestLevel/* [elemIdx] */ ) {
	ModelRoutine::updateIfGridAMRTags( vIdx, nbrUBAgentData, nbrUBEnv, v_finestLevel );
#if ENABLE_CHECK
	CHECK( ( S32 )v_finestLevel.size() == Info::numPDEs );
	for( S32 pdeIdx = 0 ; pdeIdx < Info::numPDEs ; pdeIdx++ ) {
		S32 finestLevel = v_finestLevel[pdeIdx];
		CHECK( finestLevel >= 0 );
		CHECK( finestLevel < Info::v_pdeNumLevels[pdeIdx] );
	}
#endif

	return;
}

void ModelIf::updateIfGridDirichletBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const UBEnvModelVar a_ubEnvModelVar[3], const Vector<REAL> av_gridPhi[3]/* av_gridPhi[].size() == ratio * raito * ratio (ratio = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx]), use VIdx::getIdx3DTo1D() to index */, REAL& bcVal ) {
	ModelRoutine::updateIfGridDirichletBCVal( elemIdx, pos, dim, lowSide, a_ubEnvModelVar, av_gridPhi, bcVal );
	CHECK( bcVal >= 0.0 );
	CHECK( bcVal < REAL_MAX );

	return;
}

void ModelIf::updateIfGridNeumannBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const UBEnvModelVar a_ubEnvModelVar[3], const Vector<REAL> av_gridPhi[3]/* av_gridPhi[].size() == ratio * raito * ratio (ratio = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx]), use VIdx::getIdx3DTo1D() to index */, REAL& bcVal ) {
	ModelRoutine::updateIfGridNeumannBCVal( elemIdx, pos, dim, lowSide, a_ubEnvModelVar, av_gridPhi, bcVal );
	CHECK( bcVal > REAL_MAX * -1.0 );
	CHECK( bcVal < REAL_MAX );

	return;
}

void ModelIf::initPDEBufferVel( const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL a_gridVel[DIMENSION] ) {
#if 0/* HAS_FLOW */
	ModelRoutine::initPDEBufferVel( startVIdx, pdeBufferBoxSize, a_gridVel );
#else
	ERROR( "unimplemented." );
#endif

	return;
}

void ModelIf::initPDEBufferPhi( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, Vector<REAL>& v_gridPhi ) {
	if( ( Info::v_pdeType[pdeIdx] == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( Info::v_pdeType[pdeIdx] == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) ) {
		CHECK( ( S32 )v_gridPhi.size() == ( S32 )( Info::vv_pdeGridPhiIdx[pdeIdx].size() ) );
	}
	else {
		CHECK( ( S32 )v_gridPhi.size() == 1 );
	}

	ModelRoutine::initPDEBufferPhi( pdeIdx, startVIdx, pdeBufferBoxSize, v_gridPhi );
	for( S32 i = 0 ; i < ( S32 )v_gridPhi.size() ; i++ ) {
		CHECK( v_gridPhi[i] >= 0.0 );
	}

	return;
}

void ModelIf::initPDEBufferKappa( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridKappa ) {/* relevant only if v_gridPhiOutputDivideByKappa[pdeIdx] is set to true in updateFileOutputInfo() */
	ModelRoutine::initPDEBufferKappa( pdeIdx, startVIdx, pdeBufferBoxSize, gridKappa );
	CHECK( ( gridKappa > 0.0 ) && ( gridKappa <= 1.0 ) );

	return;
}

void ModelIf::updatePDEBufferKappa( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridKappa ) {
	ModelRoutine::updatePDEBufferKappa( pdeIdx, startVIdx, pdeBufferBoxSize, gridKappa );
	CHECK( ( gridKappa > 0.0 ) && ( gridKappa <= 1.0 ) );

	return;
}

void ModelIf::updatePDEBufferAlpha( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridAlpha ) {
	ModelRoutine::updatePDEBufferAlpha( elemIdx, startVIdx, pdeBufferBoxSize, gridAlpha );
	CHECK( gridAlpha <= 0.0 );
	CHECK( gridAlpha > -1.0 );

	return;
}

void ModelIf::updatePDEBufferBetaInPDEBufferRegion( const S32 elemIdx, const S32 dim, const VIdx& startVIdx0, const VIdx& startVIdx1, const VIdx& pdeBufferBoxSize, REAL& gridBeta ) {
	ModelRoutine::updatePDEBufferBetaInPDEBufferRegion( elemIdx, dim, startVIdx0, startVIdx1, pdeBufferBoxSize, gridBeta );
#if ENABLE_CHECK
	S32 pdeIdx = Info::v_gridPhiPDEIdx[elemIdx];
	pde_type_e pdeType = Info::v_pdeType[pdeIdx];
	if( pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) {
		CHECK( gridBeta > 0.0 );
	}
	else {
		CHECK( ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) );
		CHECK( gridBeta >= 0.0 );
	}
#endif

	return;
}

void ModelIf::updatePDEBufferBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridBeta ) {
	ModelRoutine::updatePDEBufferBetaDomainBdry( elemIdx, dim, startVIdx, pdeBufferBoxSize, gridBeta );
#if ENABLE_CHECK
	S32 pdeIdx = Info::v_gridPhiPDEIdx[elemIdx];
	pde_type_e pdeType = Info::v_pdeType[pdeIdx];
	if( pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) {
		CHECK( gridBeta > 0.0 );
	}
	else {
		CHECK( ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) );
		CHECK( gridBeta >= 0.0 );
	}
#endif

	return;
}

void ModelIf::updatePDEBufferAdvVelInPDEBufferRegion( const S32 pdeIdx, const S32 dim, const VIdx& startVIdx0, const VIdx& startVIdx1, const VIdx& pdeBufferBoxSize, REAL& gridAdvVel ) {
#if 0/* HAS_FLOW */
	ModelRoutine::updatePDEBufferAdvVelInPDEBufferRegion( pdeIdx, dim, startVIdx0, startVIdx1, pdeBufferBoxSize, gridAdvVel );
#else
	ERROR( "unimplemented." );
#endif

	return;
}

void ModelIf::updatePDEBufferAdvVelDomainBdry( const S32 pdeIdx, const S32 dim, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridAdvVel ) {
#if 0/* HAS_FLOW */
	ModelRoutine::updatePDEBufferAdvVelDomainBdry( pdeIdx, dim, startVIdx, pdeBufferBoxSize, gridAdvVel );
#else
	ERROR( "unimplemented." );
#endif

	return;
}

void ModelIf::updatePDEBufferRHSLinear( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const REAL gridPhi, REAL& gridRHS ) {
	ModelRoutine::updatePDEBufferRHSLinear( elemIdx, startVIdx, pdeBufferBoxSize, gridPhi, gridRHS );
	CHECK( ( gridRHS >= - REAL_MAX ) && ( gridRHS <= REAL_MAX ) );
	return;
}

void ModelIf::adjustPDEBufferRHSTimeDependentLinear( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const REAL gridPhi, REAL& gridRHS/* INOUT */ ) {
	ModelRoutine::adjustPDEBufferRHSTimeDependentLinear( elemIdx, startVIdx, pdeBufferBoxSize, gridPhi, gridRHS );
	CHECK( ( gridRHS >= - REAL_MAX ) && ( gridRHS <= REAL_MAX ) );
	return;
}

void ModelIf::updatePDEBufferRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const Vector<double>& v_gridPhi, Vector<double>& v_gridRHS ) {
	if( ( Info::v_pdeType[pdeIdx] == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( Info::v_pdeType[pdeIdx] == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) ) {
		CHECK( ( S32 )v_gridRHS.size() == ( S32 )( Info::vv_pdeGridPhiIdx[pdeIdx].size() ) );
	}
	else {
		CHECK( ( S32 )v_gridRHS.size() == 1 );
	}

	for( S32 i = 0 ; i < ( S32 )v_gridRHS.size() ; i++ ) {
		v_gridRHS[i] = 0.0;
	}
	ModelRoutine::updatePDEBufferRHSTimeDependentSplitting( pdeIdx, startVIdx, pdeBufferBoxSize, v_gridPhi, v_gridRHS );
#if ENABLE_CHECK
	for( S32 i = 0 ; i < ( S32 )v_gridRHS.size() ; i++ ) {
		CHECK( ( v_gridRHS[i] >= - REAL_MAX ) && ( v_gridRHS[i] <= REAL_MAX ) );
	}
#endif

	return;
}

void ModelIf::updatePDEBufferDirichletBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal ) {
	ModelRoutine::updatePDEBufferDirichletBCVal( elemIdx, startPos, pdeBufferFaceSize, dim, lowSide, bcVal );
	CHECK( bcVal >= 0.0 );
	CHECK( bcVal < REAL_MAX );
}

void ModelIf::updatePDEBufferNeumannBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal ) {
	ModelRoutine::updatePDEBufferNeumannBCVal( elemIdx, startPos, pdeBufferFaceSize, dim, lowSide, bcVal );
	CHECK( bcVal > REAL_MAX * -1.0 );
	CHECK( bcVal < REAL_MAX );
}


#include "biocellion.h"
#include "model_if.h"

#include "model_routine.h"

using namespace std;

void ModelIf::updateIfGridSpacing( REAL& ifGridSpacing ) {
	ModelRoutine::updateIfGridSpacing( ifGridSpacing );
	CHECK( ifGridSpacing > 0.0 );
	return;
}

void ModelIf::updateOptModelRoutineCallInfo( OptModelRoutineCallInfo& callInfo ) {
	ModelRoutine::updateOptModelRoutineCallInfo( callInfo );
	CHECK( callInfo.numComputeMechIntrctIters >= 0 );
	CHECK( callInfo.numUpdateIfGridVarPreStateAndGridStepIters >= 0 );
	CHECK( callInfo.numUpdateIfGridVarPostStateAndGridStepIters >= 0 );
	return;
}

void ModelIf::updateBdryType( domain_bdry_type_e a_domainBdryType[DIMENSION], pde_buffer_bdry_type_e& pdeBufferBdryType ) {
	ModelRoutine::updateDomainBdryType( a_domainBdryType );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		CHECK( ( a_domainBdryType[dim] == DOMAIN_BDRY_TYPE_NONPERIODIC_HARD_WALL ) || ( a_domainBdryType[dim] == DOMAIN_BDRY_TYPE_PERIODIC ) );
	}

	ModelRoutine::updatePDEBufferBdryType( pdeBufferBdryType );
	CHECK( pdeBufferBdryType == PDE_BUFFER_BDRY_TYPE_HARD_WALL );
 
	return;
}

void ModelIf::updateTimeStepInfo( TimeStepInfo& timeStepInfo ) {
	ModelRoutine::updateTimeStepInfo( timeStepInfo );
	CHECK( timeStepInfo.durationBaselineTimeStep > 0.0 );
	CHECK( timeStepInfo.numStateAndGridTimeStepsPerBaseline >= 0 );
	return;
}

void ModelIf::updateSyncMethod( sync_method_e& mechIntrctSyncMethod, sync_method_e& updateIfGridVarSyncMethod/* dummy if both callInfo.callUpdateIfGridVarPreStateAndGridStep and callInfo.callUpdateIfGridVarPostStateAndGridStep are set to false in ModelRoutine::updateOptModelRoutineCallInfo */ ) {
	ModelRoutine::updateSyncMethod( mechIntrctSyncMethod, updateIfGridVarSyncMethod );
	CHECK( ( mechIntrctSyncMethod == SYNC_METHOD_PER_ATTR ) || ( mechIntrctSyncMethod == SYNC_METHOD_TRANSACTIONAL ) );
	CHECK( ( updateIfGridVarSyncMethod == SYNC_METHOD_PER_ATTR ) || ( updateIfGridVarSyncMethod == SYNC_METHOD_TRANSACTIONAL ) );
	if( mechIntrctSyncMethod == SYNC_METHOD_TRANSACTIONAL ) {
		ERROR( "unimplemented." );
	}
	if( updateIfGridVarSyncMethod == SYNC_METHOD_TRANSACTIONAL ) {
		ERROR( "unimplemented." );
	}
	return;
}

void ModelIf::updateAgentInfo( Vector<MpAgentInfo>& v_mpAgentInfo, Vector<SubAgentInfo>& v_subAgentInfo, Vector<SpAgentInfo>& v_spAgentInfo ) {
#if HAS_MPAGENT
#if 1
	( void )v_mpAgentInfo;
	( void )v_subAgentInfo;
	ERROR( "unimplemented." );
#else
	ModelRoutine::updateMpAgentInfo( v_mpAgentInfo, v_subAgentInfo );
	for( agentType_t i = 0 ; i < ( agentType_t )v_mpAgentInfo.size() ; i++ ) {
		MpAgentInfo& mpAgentInfo = v_mpAgentInfo[i];
		CHECK( mpAgentInfo.numBoolVars >= 0 );/* currently, Biocellion does not directly support boolean network */
		CHECK( mpAgentInfo.numStateModelReals >= 0 );
		CHECK( mpAgentInfo.numStateModelInts >= 0 );
		for( S32 j = 0 ; j < ( S32 )mpAgentInfo.v_odeNetInfo.size() ; j++ ) {
			ODENetInfo& odeNetInfo = mpAgentInfo.v_odeNetInfo[j];
			CHECK( odeNetInfo.numVars >= 0 );
			CHECK( ( odeNetInfo.stiff == ODE_STIFF_NORMAL ) || ( odeNetInfo.stiff == ODE_STIFF_HIGH ) );
			CHECK( odeNetInfo.h > 0.0 );
			CHECK( odeNetInfo.h <= 1.0 );
			CHECK( odeNetInfo.hm > 0.0 );
			CHECK( odeNetInfo.hm <= odeNetInfo.h );
			CHECK( ( odeNetInfo.epsilon > 0.0 ) && ( odeNetInfo.epsilon <= 1.0 ) );
			CHECK( odeNetInfo.threshold > 0.0 );
			CHECK( odeNetInfo.errorThresholdVal <= 0.0 );
			CHECK( odeNetInfo.warningThresholdVal <= 0.0 );
			CHECK( odeNetInfo.warningThresholdVal >= odeNetInfo.errorThresholdVal );
		}
	}

	for( agentType_t i = 0 ; i < ( agentType_t )v_subAgentInfo.size() ; i++ ) {
		SubAgentInfo& subAgentInfo = v_subAgentInfo[i];
		CHECK( subAgentInfo.dMax > 0.0 );
		CHECK( subAgentInfo.numStateModelReals >= 0 );
		CHECK( subAgentInfo.numStateModelInts >= 0 );
		for( S32 j = 0 ; j < ( S32 )subAgentInfo.v_mechIntrctModelRealInfo.size() ; j++ ) {
			const MechModelVarInfo& modelVarInfo = subAgentInfo.v_mechIntrctModelRealInfo[j];
			CHECK( ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_OVERWRITE ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_DELTA ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MIN ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MAX ) );
		}
		for( S32 j = 0 ; j < ( S32 )subAgentInfo.v_mechIntrctModelIntInfo.size() ; j++ ) {
			const MechModelVarInfo& modelVarInfo = subAgentInfo.v_mechIntrctModelIntInfo[j];
			CHECK( ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_OVERWRITE ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_DELTA ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MIN ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MAX ) );
		}
	}
#endif
#endif

#if HAS_SPAGENT
	ModelRoutine::updateSpAgentInfo( v_spAgentInfo );
#if ENABLE_CHECK
	for( agentType_t i = 0 ; i < ( agentType_t )v_spAgentInfo.size() ; i++ ) {
		SpAgentInfo& spAgentInfo = v_spAgentInfo[i];
		CHECK( spAgentInfo.dMax > 0.0 );
		CHECK( spAgentInfo.numBoolVars >= 0 );/* currently, Biocellion does not directly support boolean network */
		CHECK( spAgentInfo.numStateModelReals >= 0 );
		CHECK( spAgentInfo.numStateModelInts >= 0 );
		for( S32 j = 0 ; j < ( S32 )spAgentInfo.v_mechIntrctModelRealInfo.size() ; j++ ) {
			const MechModelVarInfo& modelVarInfo = spAgentInfo.v_mechIntrctModelRealInfo[j];
			CHECK( ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_OVERWRITE ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_DELTA ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MIN ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MAX ) );
		}
		for( S32 j = 0 ; j < ( S32 )spAgentInfo.v_mechIntrctModelIntInfo.size() ; j++ ) {
			const MechModelVarInfo& modelVarInfo = spAgentInfo.v_mechIntrctModelIntInfo[j];
			CHECK( ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_OVERWRITE ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_DELTA ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MIN ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MAX ) );
		}
		for( S32 j = 0 ; j < ( S32 )spAgentInfo.v_odeNetInfo.size() ; j++ ) {
			ODENetInfo& odeNetInfo = spAgentInfo.v_odeNetInfo[j];
			CHECK( odeNetInfo.numVars >= 0 );
			CHECK( ( odeNetInfo.stiff == ODE_STIFF_NORMAL ) || ( odeNetInfo.stiff == ODE_STIFF_HIGH ) );
			CHECK( odeNetInfo.h > 0.0 );
			CHECK( odeNetInfo.h <= 1.0 );
			CHECK( odeNetInfo.hm > 0.0 );
			CHECK( odeNetInfo.hm <= odeNetInfo.h );
			CHECK( ( odeNetInfo.epsilon > 0.0 ) && ( odeNetInfo.epsilon <= 1.0 ) );
			CHECK( odeNetInfo.threshold > 0.0 );
			CHECK( odeNetInfo.errorThresholdVal <= 0.0 );
			CHECK( odeNetInfo.warningThresholdVal <= 0.0 );
			CHECK( odeNetInfo.warningThresholdVal >= odeNetInfo.errorThresholdVal );
		}
	}
#endif
#endif

	return;
}

void ModelIf::updateJunctionEndInfo( Vector<JunctionEndInfo>& v_junctionEndInfo ) {
	ModelRoutine::updateJunctionEndInfo( v_junctionEndInfo );
#if ENABLE_CHECK
	for( junctionEndType_t i = 0 ; i < ( junctionEndType_t )v_junctionEndInfo.size() ; i++ ) {
		JunctionEndInfo& junctionEndInfo = v_junctionEndInfo[i];
		CHECK( junctionEndInfo.numModelReals >= 0 );
		CHECK( junctionEndInfo.numModelInts >= 0 );
	}
#endif
	return;
}

void ModelIf::updateGridInfo( BOOL& computeVelocity, PDEInfo& velPDEInfo/* valid only when computeVelocity is set to true */, Vector<PDEInfo>& v_phiPDEInfo, Vector<IfGridModelVarInfo>& v_ifGridModelRealInfo, Vector<IfGridModelVarInfo>& v_ifGridModelIntInfo ) {
#if ENABLE_CHECK
	S32 numPDEs = 0;
	S32 numGridPhis = 0;
	Vector<BOOL> v_pdeAppeared;
	Vector<BOOL> v_gridPhiAppeared;

	CHECK( computeVelocity == false );
	CHECK( v_phiPDEInfo.size() == 0 );
	CHECK( v_ifGridModelRealInfo.size() == 0 );
	CHECK( v_ifGridModelIntInfo.size() == 0 );
#endif

#if 0/* HAS_FLOW */
	ModelRoutine::updateVelPDEInfo( computeVelocity, velPDEInfo, v_phiPDEInfo );
#else
	computeVelocity = false;
#endif
	ModelRoutine::updatePhiPDEInfo( v_phiPDEInfo );

#if ENABLE_CHECK
	if( computeVelocity == true ) {
		numPDEs++;
	}
	numPDEs += ( S32 )v_phiPDEInfo.size();
	v_pdeAppeared.assign( numPDEs, false );
#endif

#if ENABLE_CHECK
	if( computeVelocity == true ) {
		CHECK( velPDEInfo.pdeIdx >= 0 );
		CHECK( velPDEInfo.pdeIdx < numPDEs );
		CHECK( v_pdeAppeared[velPDEInfo.pdeIdx] == false );
		v_pdeAppeared[velPDEInfo.pdeIdx] = true;
		CHECK( velPDEInfo.pdeType == PDE_TYPE_INCOMPRESSIBLE_NAVIER_STOKES_TIME_DEPENDENT );

		CHECK( velPDEInfo.numLevels >= 1 );
		CHECK( ( velPDEInfo.ifLevel >= 0 ) && ( velPDEInfo.ifLevel < velPDEInfo.numLevels ) );
		CHECK( ( S32 )velPDEInfo.v_tagExpansionSize.size() == velPDEInfo.numLevels );
		CHECK( ( S32 )velPDEInfo.v_tagExpansionSize[0] == 0 );
		for( S32 level = 0 ; level < velPDEInfo.numLevels ; level++ ) {
			CHECK( velPDEInfo.v_tagExpansionSize[level] >= 0 );
		}

		CHECK( velPDEInfo.numTimeSteps >= 1 );
		CHECK( velPDEInfo.callAdjustRHSTimeDependentLinear == false );

		MGSolveInfo& mgSolveInfo = velPDEInfo.mgSolveInfo;
		CHECK( mgSolveInfo.numPre >= 1 );
		CHECK( mgSolveInfo.numPost >= 1 );
		CHECK( mgSolveInfo.numBottom >= 1 );
		CHECK( mgSolveInfo.maxIters >= 1 );
		CHECK( ( mgSolveInfo.epsilon > 0.0 ) && ( mgSolveInfo.epsilon <= 1.0 ) );
		CHECK( ( mgSolveInfo.hang > 0.0 ) && ( mgSolveInfo.hang <= 1.0 ) );
		CHECK( mgSolveInfo.normThreshold > 0.0 );

		AdvectionInfo& advectionInfo = velPDEInfo.advectionInfo;
		CHECK( advectionInfo.courantNumber > 0.0 );

		GridVelInfo& gridVelInfo = velPDEInfo.gridVelInfo;
		CHECK( gridVelInfo.kinematicViscosity >= 0.0 );
		for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
			CHECK( ( gridVelInfo.aa_bcType[dim][0] == VEL_BC_TYPE_INFLOW_CONST ) || ( gridVelInfo.aa_bcType[dim][0] == VEL_BC_TYPE_INFLOW_MODEL ) || ( gridVelInfo.aa_bcType[dim][0] == VEL_BC_TYPE_OUTFLOW ) || ( gridVelInfo.aa_bcType[dim][0] == VEL_BC_TYPE_HARD_WALL ) );
			CHECK( ( gridVelInfo.aa_bcType[dim][1] == VEL_BC_TYPE_INFLOW_CONST ) || ( gridVelInfo.aa_bcType[dim][1] == VEL_BC_TYPE_INFLOW_MODEL ) || ( gridVelInfo.aa_bcType[dim][1] == VEL_BC_TYPE_OUTFLOW ) || ( gridVelInfo.aa_bcType[dim][1] == VEL_BC_TYPE_HARD_WALL ) );
		}

		CHECK( velPDEInfo.v_gridPhiInfo.size() == 0 );
	}

	for( S32 pdeIdx = 0 ; pdeIdx < ( S32 )v_phiPDEInfo.size() ; pdeIdx++ ) {
		numGridPhis += v_phiPDEInfo[pdeIdx].v_gridPhiInfo.size();
	}
	if( numGridPhis > 0 ) {
		v_gridPhiAppeared.assign( numGridPhis, false );
	}

	for( S32 idx = 0 ; idx < ( S32 )v_phiPDEInfo.size() ; idx++ ) {
		PDEInfo& pdeInfo = v_phiPDEInfo[idx];

		CHECK( pdeInfo.pdeIdx >= 0 );
		CHECK( pdeInfo.pdeIdx < numPDEs );
		CHECK( v_pdeAppeared[pdeInfo.pdeIdx] == false );
		v_pdeAppeared[pdeInfo.pdeIdx] = true;

		CHECK( ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) );
		if( ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) ) {
			CHECK( pdeInfo.v_gridPhiInfo.size() == 1 );
		}
		else {
			CHECK( ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) );
			CHECK( pdeInfo.v_gridPhiInfo.size() > 0 );
		}

		CHECK( pdeInfo.numLevels >= 1 );
		CHECK( ( pdeInfo.ifLevel >= 0 ) && ( pdeInfo.ifLevel < pdeInfo.numLevels ) );
		CHECK( ( S32 )pdeInfo.v_tagExpansionSize.size() == pdeInfo.numLevels );
		CHECK( ( S32 )pdeInfo.v_tagExpansionSize[0] == 0 );
		for( S32 level = 0 ; level < pdeInfo.numLevels ; level++ ) {
			CHECK( pdeInfo.v_tagExpansionSize[level] >= 0 );
		}

		if( ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) ) {
			CHECK( pdeInfo.numTimeSteps >= 1 );
		}
		else {
			CHECK( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR );
			CHECK( pdeInfo.numTimeSteps == 0 );
		}

		if( ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) ) {
			CHECK( pdeInfo.callAdjustRHSTimeDependentLinear == false );
		}
		else {
			CHECK( ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) );
		}

		MGSolveInfo& mgSolveInfo = pdeInfo.mgSolveInfo;
		CHECK( mgSolveInfo.numPre >= 1 );
		CHECK( mgSolveInfo.numPost >= 1 );
		CHECK( mgSolveInfo.numBottom >= 1 );
		CHECK( mgSolveInfo.maxIters >= 1 );
		CHECK( ( mgSolveInfo.epsilon > 0.0 ) && ( mgSolveInfo.epsilon <= 1.0 ) );
		CHECK( ( mgSolveInfo.hang > 0.0 ) && ( mgSolveInfo.hang <= 1.0 ) );
		CHECK( mgSolveInfo.normThreshold > 0.0 );

		if( ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) ) {
			AdvectionInfo& advectionInfo = pdeInfo.advectionInfo;
			CHECK( advectionInfo.courantNumber > 0.0 );
		}

		if( ( pdeInfo.pdeType == PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) || ( pdeInfo.pdeType == PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING ) ) {
			SplittingInfo& splittingInfo = pdeInfo.splittingInfo;
			CHECK( splittingInfo.v_diffusionTimeSteps.size() == pdeInfo.v_gridPhiInfo.size() );
			for( S32 i = 0 ; i < ( S32 )splittingInfo.v_diffusionTimeSteps.size() ; i++ ) {
				CHECK( splittingInfo.v_diffusionTimeSteps[i] >= 1 );
			}
			CHECK( ( splittingInfo.odeStiff == ODE_STIFF_NORMAL ) || ( splittingInfo.odeStiff == ODE_STIFF_HIGH ) );
			CHECK( splittingInfo.odeH > 0.0 );
			CHECK( splittingInfo.odeH <= 1.0 );
			CHECK( splittingInfo.odeHm > 0.0 );
			CHECK( splittingInfo.odeHm <= splittingInfo.odeH );
			CHECK( ( splittingInfo.odeEpsilon > 0.0 ) && ( splittingInfo.odeEpsilon <= 1.0 ) );
			CHECK( splittingInfo.odeThreshold > 0.0 );
		}

		for( S32 i = 0 ; i < ( S32 )pdeInfo.v_gridPhiInfo.size() ; i++ ) {
			GridPhiInfo& gridPhiInfo = pdeInfo.v_gridPhiInfo[i];
			CHECK( gridPhiInfo.elemIdx >= 0 );
			CHECK( gridPhiInfo.elemIdx < numGridPhis );
			CHECK( ( gridPhiInfo.syncMethod == VAR_SYNC_METHOD_OVERWRITE ) || ( gridPhiInfo.syncMethod == VAR_SYNC_METHOD_DELTA ) || ( gridPhiInfo.syncMethod == VAR_SYNC_METHOD_MIN ) || ( gridPhiInfo.syncMethod == VAR_SYNC_METHOD_MAX ) );
			CHECK( v_gridPhiAppeared[gridPhiInfo.elemIdx] == false );
			v_gridPhiAppeared[gridPhiInfo.elemIdx] = true;
			for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
				CHECK( ( gridPhiInfo.aa_bcType[dim][0] == BC_TYPE_DIRICHLET_CONST ) || ( gridPhiInfo.aa_bcType[dim][0] == BC_TYPE_DIRICHLET_MODEL ) || ( gridPhiInfo.aa_bcType[dim][0] == BC_TYPE_NEUMANN_CONST ) || ( gridPhiInfo.aa_bcType[dim][0] == BC_TYPE_NEUMANN_MODEL ) );
				CHECK( ( gridPhiInfo.aa_bcType[dim][1] == BC_TYPE_DIRICHLET_CONST ) || ( gridPhiInfo.aa_bcType[dim][1] == BC_TYPE_DIRICHLET_MODEL ) || ( gridPhiInfo.aa_bcType[dim][1] == BC_TYPE_NEUMANN_CONST ) || ( gridPhiInfo.aa_bcType[dim][1] == BC_TYPE_NEUMANN_MODEL ) );
				if( gridPhiInfo.aa_bcType[dim][0] == BC_TYPE_DIRICHLET_CONST ) {
					CHECK( gridPhiInfo.aa_bcVal[dim][0] >= 0.0 );
				}
				if( gridPhiInfo.aa_bcType[dim][1] == BC_TYPE_DIRICHLET_CONST ) {
					CHECK( gridPhiInfo.aa_bcVal[dim][1] >= 0.0 );
				}
			}
			CHECK( gridPhiInfo.errorThresholdVal <= 0.0 );
			CHECK( gridPhiInfo.warningThresholdVal <= 0.0 );
			CHECK( gridPhiInfo.warningThresholdVal >= gridPhiInfo.errorThresholdVal );
		}
	}

	for( S32 elemIdx = 0 ; elemIdx < ( S32 )v_gridPhiAppeared.size() ; elemIdx++ ) {
		CHECK( v_gridPhiAppeared[elemIdx] == true );
	}
#endif

	ModelRoutine::updateIfGridModelVarInfo( v_ifGridModelRealInfo, v_ifGridModelIntInfo );
#if ENABLE_CHECK
	for( S32 elemIdx = 0 ; elemIdx < ( S32 )v_ifGridModelRealInfo.size() ; elemIdx++ ) {
		const IfGridModelVarInfo& modelVarInfo = v_ifGridModelRealInfo[elemIdx];
		CHECK( ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_OVERWRITE ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_DELTA ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MIN ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MAX ) );
	}

	for( S32 elemIdx = 0 ; elemIdx < ( S32 )v_ifGridModelIntInfo.size() ; elemIdx++ ) {
		const IfGridModelVarInfo& modelVarInfo = v_ifGridModelIntInfo[elemIdx];
		CHECK( ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_OVERWRITE ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_DELTA ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MIN ) || ( modelVarInfo.syncMethod == VAR_SYNC_METHOD_MAX ) );
	}
#endif

	return;
}

void ModelIf::updateRNGInfo( Vector<RNGInfo>& v_rngInfo ) {
	ModelRoutine::updateRNGInfo( v_rngInfo );
	for( S32 i = 0 ; i < ( S32 )v_rngInfo.size() ; i++ ) {
		RNGInfo& rngInfo = v_rngInfo[i];

		CHECK( ( rngInfo.type == RNG_TYPE_UNIFORM ) || ( rngInfo.type == RNG_TYPE_GAUSSIAN ) || ( rngInfo.type == RNG_TYPE_EXPONENTIAL ) || ( rngInfo.type == RNG_TYPE_GAMMA ) );
		if( rngInfo.type == RNG_TYPE_UNIFORM ) {
			CHECK( rngInfo.param0 < rngInfo.param1 );
		}
		else if( rngInfo.type == RNG_TYPE_GAUSSIAN ) {
			CHECK( rngInfo.param1 > 0.0 );
		}
		else if( rngInfo.type == RNG_TYPE_EXPONENTIAL ) {
			CHECK( rngInfo.param0 > 0.0 );
		}
		else if( rngInfo.type == RNG_TYPE_GAMMA ) {
			CHECK( rngInfo.param0 > 0.0 );
			CHECK( rngInfo.param1 > 0.0 );
		}
	}

	return;
}

void ModelIf::updateFileOutputInfo( FileOutputInfo& fileOutputInfo ) {
	ModelRoutine::updateFileOutputInfo( fileOutputInfo );
	CHECK( fileOutputInfo.v_gridPhiOutput.size() == fileOutputInfo.v_gridPhiOutputDivideByKappa.size() );
	return;
}

void ModelIf::updateSummaryOutputInfo( Vector<SummaryOutputInfo>& v_summaryOutputRealInfo, Vector<SummaryOutputInfo>& v_summaryOutputIntInfo ) {
	ModelRoutine::updateSummaryOutputInfo( v_summaryOutputRealInfo, v_summaryOutputIntInfo );
#if ENABLE_CHECK
	for( S32 i = 0 ; i < ( S32 )v_summaryOutputRealInfo.size() ; i++ ) {
		const SummaryOutputInfo& info = v_summaryOutputRealInfo[i];
		CHECK( ( info.type == SUMMARY_TYPE_SUM ) || ( info.type == SUMMARY_TYPE_AVG ) || ( info.type == SUMMARY_TYPE_MIN ) || ( info.type == SUMMARY_TYPE_MAX ) );
	}

	for( S32 i = 0 ; i < ( S32 )v_summaryOutputIntInfo.size() ; i++ ) {
		const SummaryOutputInfo& info = v_summaryOutputIntInfo[i];
		CHECK( ( info.type == SUMMARY_TYPE_SUM ) || ( info.type == SUMMARY_TYPE_AVG ) || ( info.type == SUMMARY_TYPE_MIN ) || ( info.type == SUMMARY_TYPE_MAX ) );
	}
#endif

	return;
}

void ModelIf::initGlobal( Vector<U8>& v_globalData ) {
	ModelRoutine::initGlobal( v_globalData );
	return;
}

void ModelIf::init( void ) {
	ModelRoutine::init();
	return;
}

void ModelIf::term( void ) {
	ModelRoutine::term();
	return;
}

void ModelIf::setPDEBuffer( const VIdx& startVIdx, const VIdx& regionSize, BOOL& isPDEBuffer ) {
	ModelRoutine::setPDEBuffer( startVIdx, regionSize, isPDEBuffer );
	return;
}

void ModelIf::setHabitable( const VIdx& vIdx, BOOL& habitable ) {
	ModelRoutine::setHabitable( vIdx, habitable );
	return;
}


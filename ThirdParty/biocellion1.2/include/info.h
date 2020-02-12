/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __INFO_H__
#define __INFO_H__

#include <string>

#include "base_type.h"
#include "vector_type.h"
#include "ext_type.h"
#include "rng.h"

const S32 MPAGENT_MAX_WIDTH = 4;/* the maximum size of a multi-particle agent in the x, y, and z directions */

class AgentAuxDataInfo {
public:
	/* agent state */

	U32 boolVarOffset;
	Vector<U32> v_odeNetVarOffset;
	Vector<U32> v_odeNetSolverDataOffset;
	U32 stateModelRealOffset;
	U32 stateModelIntOffset;
	U32 stateDataSize;

	/* agent-agent extra-mechanical interaction */

	U32 mechIntrctModelRealChangeFlagOffset;
	U32 mechIntrctModelRealOffset;
	U32 mechIntrctModelIntChangeFlagOffset;
	U32 mechIntrctModelIntOffset;
	U32 mechIntrctDataSize;
};

class JunctionEndAuxDataInfo {
public:
	U32 modelRealOffset;
	U32 modelIntOffset;
	U32 dataSize;
};

class EnvAuxDataInfo {
public:
	U32 velOffset;
	Vector<U32> v_phiOffset;/* [elemIdx] */
	U32 modelRealOffset;
	U32 modelIntOffset;
	U32 dataSize;

	S32 velStartIdx;
	Vector<S32> v_phiStartIdx;/* [elemIdx] */
	S32 modelRealStartIdx;
	S32 modelIntStartIdx;
	S32 numVars;/* sum (# phis in the finest layer for each phi) + # model reals + # model ints */

	S32 velRatioFromIfGridToIfSubgrid;/* [elemIdx], between the interface level and the finest level */
	S32 velRatioFromIfGridToIfSubgridCubed;/* [elemIdx], between the interface level and the finest level */
	Vector<S32> v_phiRatioFromIfGridToIfSubgrid;/* [elemIdx], between the interface level and the finest level */
	Vector<S32> v_phiRatioFromIfGridToIfSubgridCubed;/* [elemIdx], between the interface level and the finest level */

	Vector<if_grid_var_type_e> v_valIdxToVarType;
	Vector<S32> v_valIdxToElemIdx;
};

class Info {
public:
#if THIS_IS_LIBMODEL
	/* compile */

	static inline void getFrameworkInfo( BOOL& realIsFloat, BOOL& hasMpAgent, BOOL& hasSpAgent ) __attribute__( ( always_inline ) );

	/* dynamic */

	static inline S32 getCurBaselineTimeStep( void ) __attribute__( ( always_inline ) );
	static inline S32 getCurStateAndGridTimeStep( void ) __attribute__( ( always_inline ) );/* within a baseline time step */
	static inline S32 getCurPDETimeStep( const S32 pdeIdx ) __attribute__( ( always_inline ) );/* within a state-and-grid time step */
	static inline const Vector<U8>& getGlobalDataRef( void ) __attribute__( ( always_inline ) );

	static inline REAL getRecentSummaryRealVal( const S32 elemIdx ) __attribute__( ( always_inline ) );
	static inline S32 getRecentSummaryIntVal( const S32 elemIdx ) __attribute__( ( always_inline ) );

	/* required - domain */

	static inline idx_t getDomainSize( const S32 dim ) __attribute__( ( always_inline ) );

	/* required - init */

	static inline idx_t getPartSize( void ) __attribute__( ( always_inline ) );
	static inline sim_init_type_e getSimInitType( void ) __attribute__( ( always_inline ) );

	/* required - output */

	static S32 getParticleNumExtraOutputScalarVars( void ) __attribute__( ( always_inline ) );
	static S32 getParticleNumExtraOutputVectorVars( void ) __attribute__( ( always_inline ) );

	/* optional - model */

	static inline std::string getModelParam( void ) __attribute__( ( always_inline ) );

	/* optional - rng */

	static inline S32 getNumModelRNGs( void ) __attribute__( ( always_inline ) );

	/* optional - amr */

	static inline S32 getSummaryInterval( void ) __attribute__( ( always_inline ) );
	static inline S32 getRegriddingInterval( void ) __attribute__( ( always_inline ) );

	/* optional - AMR */

	static inline S32 getAMRRatio( void ) __attribute__( ( always_inline ) );
#else
#if USE_DIST_MEM_PAR
	static inline S32 getMyProcIdInWorld( void ) __attribute__( ( always_inline ) );
	static inline S32 getNumProcs( void ) __attribute__( ( always_inline ) );
#endif
	static inline S32 getNumThreads( void ) __attribute__( ( always_inline ) );
#endif

private:
	/* compile */

	static BOOL realIsFloat;
	static BOOL hasMpAgent;
	static BOOL hasSpAgent;

	/* dynamic */

#if USE_DIST_MEM_PAR
	static S32 myProcIdInWorld;
	static S32 myNodeGrpId;
	static S32 myProcIdInNodeGrp;
#endif

	static S32 curBaselineTimeStep;
	static S32 curStateAndGridTimeStep;
	static Vector<S32> v_curPDETimeStep;
	static Vector<U8> v_globalData;

	static Vector<REAL> v_summaryRealVal;
	static Vector<S32> v_summaryIntVal;

	/* required */

	/* required - common */

	static S32 numBaselineTimeSteps;
	static REAL durationBaselineTimeStep;
	static S32 numStateAndGridTimeStepsPerBaseline;
	static REAL durationStateAndGridTimeStep;

	static REAL ifGridSpacing;
	static domain_bdry_type_e a_domainBdryType[DIMENSION];
	static pde_buffer_bdry_type_e pdeBufferBdryType;
	static idx_t a_domainSize[DIMENSION];
	static idx_t partSize;

	static std::string simInitDataDirPath;
	static std::string simOutputDirPath;
	static S32 outputInterval;
	static sim_init_type_e simInitType;
	static particle_output_type_e particleOutputType;
	static grid_output_type_e gridOutputType;

	static sync_method_e mechIntrctSyncMethod;
	static sync_method_e updateIfGridVarSyncMethod;

	static S32 numComputeMechIntrctIters;
	static S32 numUpdateIfGridVarPreStateAndGridStepIters;
	static S32 numUpdateIfGridVarPostStateAndGridStepIters;
	static BOOL callSetPDEBdryVel;
	static Vector<BOOL> v_callSetPDEBdryPhi;/* [elemIdx] */
	static Vector<BOOL> v_callAdjustRHSTimeDependentLinear;/* [elemIdx] */

	/* required - agent */

#if HAS_MPAGENT
	static agentType_t numMpAgentTypes;
	static Vector<S32> v_mpAgentNumBoolVars;
	static Vector<S32> v_mpAgentNumODENets;
	static Vector<Vector<S32> > vv_mpAgentNumODENetVars;/* [type][odeNetIdx] */
	static Vector<Vector<ode_stiff_e> > vv_mpAgentODEStiff;
	static Vector<Vector<REAL> > vv_mpAgentODEH;
	static Vector<Vector<REAL> > vv_mpAgentODEHm;
	static Vector<Vector<REAL> > vv_mpAgentODEEpsilon;
	static Vector<Vector<REAL> > vv_mpAgentODEThreshold;
	static Vector<Vector<REAL> > vv_mpAgentODEErrorThresholdVal;
	static Vector<Vector<REAL> > vv_mpAgentODEWarningThresholdVal;
	static Vector<Vector<BOOL> > vv_mpAgentODESetNegToZero;
	static Vector<S32> v_mpAgentNumStateModelReals;
	static Vector<S32> v_mpAgentNumStateModelInts;

	static agentType_t numSubAgentTypes;
	static Vector<REAL> v_subAgentDMax;
	static Vector<S32> v_subAgentNumStateModelReals;
	static Vector<S32> v_subAgentNumStateModelInts;
	static Vector<S32> v_subAgentNumMechIntrctModelReals;
	static Vector<Vector<var_sync_method_e> > vv_subAgentMechIntrctModelRealSyncMethod;
	static Vector<S32> v_subAgentNumMechIntrctModelInts;
	static Vector<Vector<var_sync_method_e> > vv_subAgentMechIntrctModelIntSyncMethod;
	static Vector<S32> v_subAgentUBSubpartLevel;
	static S32 subAgentMaxUBSubpartLevel;
#endif

#if HAS_SPAGENT
	static agentType_t numSpAgentTypes;
	static Vector<REAL> v_spAgentDMax;
	static Vector<S32> v_spAgentNumBoolVars;
	static Vector<S32> v_spAgentNumODENets;
	static Vector<Vector<S32> > vv_spAgentNumODENetVars;/* [type][odeNetIdx] */
	static Vector<Vector<ode_stiff_e> > vv_spAgentODEStiff;
	static Vector<Vector<REAL> > vv_spAgentODEH;
	static Vector<Vector<REAL> > vv_spAgentODEHm;
	static Vector<Vector<REAL> > vv_spAgentODEEpsilon;
	static Vector<Vector<REAL> > vv_spAgentODEThreshold;
	static Vector<Vector<REAL> > vv_spAgentODEErrorThresholdVal;
	static Vector<Vector<REAL> > vv_spAgentODEWarningThresholdVal;
	static Vector<Vector<BOOL> > vv_spAgentODESetNegToZero;
	static Vector<S32> v_spAgentNumStateModelReals;
	static Vector<S32> v_spAgentNumStateModelInts;
	static Vector<S32> v_spAgentNumMechIntrctModelReals;
	static Vector<Vector<var_sync_method_e> > vv_spAgentMechIntrctModelRealSyncMethod;
	static Vector<S32> v_spAgentNumMechIntrctModelInts;
	static Vector<Vector<var_sync_method_e> > vv_spAgentMechIntrctModelIntSyncMethod;
	static Vector<S32> v_spAgentUBSubpartLevel;
	static S32 spAgentMaxUBSubpartLevel;
#endif

	static junctionEndType_t numJunctionEndTypes;
	static Vector<S32> v_junctionEndNumModelReals;
	static Vector<S32> v_junctionEndNumModelInts;

	/* required - grid */

	static S32 numPDEs;

	static BOOL computeVelocity;

	static S32 numGridPhis;
	static S32 numGridModelReals;
	static S32 numGridModelInts;

	static S32 numSummaryReals;
	static S32 numSummaryInts;

	/* PDE solvers */

	static Vector<pde_type_e> v_pdeType;/* [pdeIdx] */
	static Vector<Vector<S32> > vv_pdeGridPhiIdx;/* [pdeIdx] */
	static Vector<S32> v_pdeNumLevels;/* [pdeIdx] */
	static Vector<S32> v_pdeIfLevel;/* [pdeIdx] */
	static Vector<Vector<S32> > vv_pdeTagExpansionSize;/* [pdeIdx][level] */

	static Vector<S32> v_pdeNumTimeSteps;/* [pdeIdx], valid only for time-dependent PDEs */

	static Vector<S32> v_pdeMGSolveNumPre;/* [pdeIdx] */
	static Vector<S32> v_pdeMGSolveNumPost;/* [pdeIdx] */
	static Vector<S32> v_pdeMGSolveNumBottom;/* [pdeIdx] */
	static Vector<BOOL> v_pdeMGSolveVCycle;/* [pdeIdx] */
	static Vector<S32> v_pdeMGSolveMaxIters;/* [pdeIdx] */
	static Vector<REAL> v_pdeMGSolveEpsilon;/* [pdeIdx] */
	static Vector<REAL> v_pdeMGSolveHang;/* [pdeIdx] */
	static Vector<REAL> v_pdeMGSolveNormThreshold;/* [pdeIdx] */

	static Vector<REAL> v_pdeCourantNumber;/* [pdeIdx], valid only for time-dependent advection PDEs */

	static Vector<Vector<S32> > vv_pdeSplittingDiffusionTimeSteps;/* [pdeIdx], valid only for time-splitting PDEs */
	static Vector<ode_stiff_e> v_pdeSplittingODEStiff;/* [pdeIdx], valid only for time-splitting PDEs */
	static Vector<REAL> v_pdeSplittingODEH;/* [pdeIdx], valid only for time-splitting PDEs */
	static Vector<REAL> v_pdeSplittingODEHm;/* [pdeIdx], valid only for time-splitting PDEs */
	static Vector<REAL> v_pdeSplittingODEEpsilon;/* [pdeIdx], valid only for time-splitting PDEs */
	static Vector<REAL> v_pdeSplittingODEThreshold;/* [pdeIdx], valid only for time-splitting PDEs */

	/* velocity */

	static S32 gridVelPDEIdx;

	static REAL gridVelKinematicViscosity;

	static Vector<vel_bc_type_e> v_gridVelLowBCType;/* [dim] */
	static Vector<VReal> v_gridVelLowBCVal;/* [dim] */
	static Vector<vel_bc_type_e> v_gridVelHighBCType;/* [dim] */
	static Vector<VReal> v_gridVelHighBCVal;/* [dim] */

	/* phi */

	static Vector<S32> v_gridPhiPDEIdx;/* [elemIdx] */
	static Vector<std::string> v_gridPhiName;/* [elemIdx] */
	static Vector<var_sync_method_e> v_gridPhiSyncMethod;/* [elemIdx] */

	static Vector<Vector<bc_type_e> > vv_gridPhiLowBCType;/* [elemIdx][dim] */
	static Vector<Vector<REAL> > vv_gridPhiLowBCVal;/* [elemIdx][dim] */
	static Vector<Vector<bc_type_e> > vv_gridPhiHighBCType;/* [elemIdx][dim] */
	static Vector<Vector<REAL> > vv_gridPhiHighBCVal;/* [elemIdx][dim] */

	static Vector<REAL> v_gridPhiErrorThresholdVal;/* [elemIdx] */
	static Vector<REAL> v_gridPhiWarningThresholdVal;/* [elemIdx] */
	static Vector<BOOL> v_gridPhiSetNegToZero;/* [elemIdx] */

	/* model specific varialbes */

	static Vector<std::string> v_gridModelRealName;/* [elemIdx] */
	static Vector<var_sync_method_e> v_gridModelRealSyncMethod;/* [elemIdx] */

	static Vector<std::string> v_gridModelIntName;/* [elemIdx] */
	static Vector<var_sync_method_e> v_gridModelIntSyncMethod;/* [elemIdx] */

	/* summary variables */

	static Vector<std::string> v_summaryRealName;/* [elemIdx] */
	static Vector<summary_type_e> v_summaryRealType;/* [elemIdx] */

	static Vector<std::string> v_summaryIntName;/* [elemIdx] */
	static Vector<summary_type_e> v_summaryIntType;/* [elemIdx] */

	/* required - file output */

	static BOOL particleOutput;
	static Vector<std::string> v_particleExtraOutputScalarVarName;
	static Vector<std::string> v_particleExtraOutputVectorVarName;
	static Vector<BOOL> v_gridPhiOutput;/* [elemIdx] */
	static Vector<BOOL> v_gridPhiOutputDivideByKappa;/* [elemIdx] */
	static VIdx outputStartVIdx;
	static VIdx outputRegionSize;

	/* optional */

	/* optional - model */

	static std::string modelParam;

	/* optional - stdout */

	static std::string stdoutRedirectDirPath;
	static S32 verbosity;
	static BOOL useTimeStamp;

	/* optional - rng */

	static S32 numModelRNGs;
	static Vector<rng_type_e> v_rngType;
	static Vector<REAL> v_rngParam0;/* mean for uniform, avg for gaussian, beta for exponential, alpha for gamma */
	static Vector<REAL> v_rngParam1;/* max for unifrom, sd for gaussian, disp for exponential, beta for gamma */
	static Vector<REAL> v_rngParam2;/* only for gamma, disp */

	/* optional - system */

	static S32 numNodeGrps;/* valid only when USE_DIST_MEM_PAR == 1 */
	static S32 numNodesPerGrp;/* valid only when USE_DIST_MEM_PAR == 1 */
	static S32 numSocketsPerNode;/* valid only when USE_DIST_MEM_PAR == 1 */
	static S32 numThreads;

	/* optional - super_partition */

	static idx_t a_spartSize[DIMENSION];

	/* optional - interval */

	static S32 summaryInterval;
	static S32 loadBalanceInterval;/* valid only when USE_DIST_MEM_PAR == 1 */
	static S32 regriddingInterval;
	static S32 checkpointInterval;

	/* optional - AMR */

	static S32 amrRefRatio;
	static REAL amrFillRatio;

	/* other */

	static Vector<AgentAuxDataInfo> av_agentAuxDataInfo[NUM_AGENT_CLASSES];
	static Vector<JunctionEndAuxDataInfo> v_junctionEndAuxDataInfo;
	static EnvAuxDataInfo envAuxDataInfo;/* phi and model-specific real and int variables */
	static EnvAuxDataInfo envModelVarAuxDataInfo;/* model-specific real and int variables */

	friend class ModelIf;
	friend class MpAgent;
	friend class SubAgent;
	friend class SpAgent;
	friend class SubAgentState;
	friend class SpAgentState;
	friend class JunctionData;
	friend class JunctionEnd;
	friend class MechIntrctData;
	friend class UBEnv;
	friend class UBEnvModelVar;
	friend class NbrUBEnvAux;
	friend class NbrUBEnv;
	friend class NbrUBEnvModelVar;
	friend class Util;
	friend class Report;

#if ( THIS_IS_LIBMODEL == 0 )
	friend class Sim;
	friend class Comm;
	friend class Pack;
	friend class Xml;
	friend class Misc;
	friend class InitData;
	friend class PartGridData;
	friend class MyThreadData;

	friend void biocellion( const std::string xmlFile );
#endif
};

#if THIS_IS_LIBMODEL
inline void Info::getFrameworkInfo( BOOL& realIsFloat, BOOL& hasMpAgent, BOOL& hasSpAgent ) {
	realIsFloat = Info::realIsFloat;
	hasMpAgent = Info::hasMpAgent;
	hasSpAgent = Info::hasSpAgent;
	return;
}

inline S32 Info::getCurBaselineTimeStep( void ) {
	CHECK( Info::curBaselineTimeStep >= 0 );/* invalid to call this function during initialization */
	return Info::curBaselineTimeStep;
}

inline S32 Info::getCurStateAndGridTimeStep( void ) {
	CHECK( Info::curBaselineTimeStep >= 0 );/* invalid to call this function during initialization */
	return Info::curStateAndGridTimeStep;
}

inline S32 Info::getCurPDETimeStep( const S32 pdeIdx ) {
	CHECK( Info::curBaselineTimeStep >= 0 );/* invalid to call this function during initialization */
	CHECK( pdeIdx < ( S32 )Info::v_curPDETimeStep.size() );
	return Info::v_curPDETimeStep[pdeIdx];
}

inline const Vector<U8>& Info::getGlobalDataRef( void ) {
	return Info::v_globalData;
}

inline REAL Info::getRecentSummaryRealVal( const S32 elemIdx ) {
	CHECK( Info::curBaselineTimeStep >= 0 );/* invalid to call this function during initialization */
	CHECK( elemIdx < Info::numSummaryReals );
	return Info::v_summaryRealVal[elemIdx];
}

inline S32 Info::getRecentSummaryIntVal( const S32 elemIdx ) {
	CHECK( Info::curBaselineTimeStep >= 0 );/* invalid to call this function during initialization */
	CHECK( elemIdx < Info::numSummaryInts );
	return Info::v_summaryIntVal[elemIdx];
}

inline idx_t Info::getDomainSize( const S32 dim ) {
	return Info::a_domainSize[dim];
}

inline idx_t Info::getPartSize( void ) {
	return Info::partSize;
}

inline sim_init_type_e Info::getSimInitType( void ) {
	return Info::simInitType;
}

inline S32 Info::getParticleNumExtraOutputScalarVars( void ) {
	return ( S32 )Info::v_particleExtraOutputScalarVarName.size();
}

inline S32 Info::getParticleNumExtraOutputVectorVars( void ) {
	return ( S32 )Info::v_particleExtraOutputVectorVarName.size();
}

inline std::string Info::getModelParam( void ) {
	return Info::modelParam;
}

inline S32 Info::getNumModelRNGs( void ) {
	return Info::numModelRNGs;
}

inline S32 Info::getSummaryInterval( void ) {
	return Info::summaryInterval;
}

inline S32 Info::getRegriddingInterval( void ) {
	return Info::regriddingInterval;
}

inline S32 Info::getAMRRatio( void ) {
	return Info::amrRefRatio;
}
#else
#if USE_DIST_MEM_PAR
inline S32 Info::getMyProcIdInWorld( void ) {
	return Info::myProcIdInWorld;
}

inline S32 Info::getNumProcs( void ) {
	return Info::numNodeGrps * Info::numNodesPerGrp * Info::numSocketsPerNode;
}
#endif

inline S32 Info::getNumThreads( void ) {
	return Info::numThreads;
}
#endif

#endif/* #ifndef __INFO_H__ */
 

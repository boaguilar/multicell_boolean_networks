/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __MODEL_IF_H__
#define __MODEL_IF_H__

#include <string>

#include "base_type.h"
#include "vector_type.h"
#include "ext_type.h"

class ModelIf {
public:
	/* model configuration */

	static void updateIfGridSpacing( REAL& ifGridSpacing );

	static void updateOptModelRoutineCallInfo( OptModelRoutineCallInfo& callInfo );

	static void updateBdryType( domain_bdry_type_e a_domainBdryType[DIMENSION], pde_buffer_bdry_type_e& pdeBufferBdryType );

	static void updateTimeStepInfo( TimeStepInfo& timeStepInfo );

	static void updateSyncMethod( sync_method_e& extraMechIntrctSyncMethod, sync_method_e& updateIfGridVarSyncMethod/* dummy if both numUpdateIfGridVarPreStateAndGridStepIters and numUpdateIfGridVarPostStateAndGridStepIters are set to 0 in ModelRoutine::updateOptModelRoutineCallInfo */ );

	static void updateAgentInfo( Vector<MpAgentInfo>& v_mpAgentInfo, Vector<SubAgentInfo>& v_subAgentInfo, Vector<SpAgentInfo>& v_spAgentInfo );
	static void updateJunctionEndInfo( Vector<JunctionEndInfo>& v_junctionEndInfo );
	static void updateGridInfo( BOOL& computeVelocity, PDEInfo& velPDEInfo, Vector<PDEInfo>& v_phiPDEInfo, Vector<IfGridModelVarInfo>& v_ifGridModelRealInfo, Vector<IfGridModelVarInfo>& v_ifGridModelIntInfo );
	static void updateRNGInfo( Vector<RNGInfo>& v_rngInfo );
	static void updateFileOutputInfo( FileOutputInfo& fileOutputInfo );
	static void updateSummaryOutputInfo( Vector<SummaryOutputInfo>& v_summaryOutputRealInfo, Vector<SummaryOutputInfo>& v_summaryOutputIntInfo );

	/* initialize global model information */

	static void initGlobal( Vector<U8>& v_globalData );

	/* initialization and termination */

	static void init( void );
	static void term( void );

	static void setPDEBuffer( const VIdx& startVIdx, const VIdx& regionSize, BOOL& isPDEBuffer );

	static void setHabitable( const VIdx& vIdx, BOOL& habitable );

	/* init agent, update agent state, and simulate agent birth and death */

	static void addAgents( const BOOL init, const VIdx& startVIdx, const VIdx& regionSize, const IfGridBoxData<BOOL>& ifGridHabitableBoxData, Vector<MpAgent>& v_newMpAgent/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<VIdx> >& vv_newSubAgentVIdx/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<SubAgentState> >& vv_newSubAgentState/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<VReal> >& vv_newSubAgentOffset/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx0/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx1/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<JunctionEnd> >& vv_end0/* dummy if HAS_MPAGENT == 0 */, Vector<Vector<JunctionEnd> >& vv_end1/* dummy if HAS_MPAGENT == 0 */, Vector<VIdx>& v_newSpAgentVIdx/* dummy if HAS_SPAGENT == 0 */, Vector<SpAgentState>& v_newSpAgentState/* dummy if HAS_SPAGENT == 0 */, Vector<VReal>& v_newSpAgentOffset/* dummy if HAS_SPAGENT == 0 */ );

#if HAS_MPAGENT
	static void mpAgentCRNODERHS( const S32 odeNetIdx, const MpAgent& mpAgent, const Vector<VIdx>& v_subAgentVIdx, const Vector<SubAgent*>& vp_subAgent, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, const Vector<double>& v_y, Vector<double>& v_f );

	static void updateMpAgentState( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent/* INOUT */, Vector<SubAgentState*>& vp_subAgentState/* INOUT */ );

	static void mpAgentSecretionByMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_mechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent/* INOUT */, Vector<SubAgentState*>& vp_subAgentState/* INOUT */, Vector<subAgentIdx_t>& v_srcIdx, Vector<MpAgent>& v_mpAgent, Vector<Vector<SubAgentState> >& vv_subAgentState, Vector<Vector<VReal> >& vv_subAgentDisp, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx0, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx1, Vector<Vector<JunctionEnd> >& vv_end0, Vector<Vector<JunctionEnd> >& vv_end1 );
#if HAS_SPAGENT
	static void spAgentSecretionByMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_mechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent/* INOUT */, Vector<SubAgentState*>& vp_subAgentState/* INOUT */, Vector<subAgentIdx_t>& v_srcIdx, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentDisp );
#endif

	static void updateMpAgentBirthDeath( const MpAgent& mpAgent, const Vector<VIdx>& v_subAgentVIdx, const Vector<SubAgent*>& vp_subAgent, const Vector<const MechIntrctData*>& vp_mechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, BOOL& divide, BOOL& disappear );

	static void adjustMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_mechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& mpAgent/* INOUT */, Vector<SubAgentState*>& vp_subAgentState/* INOUT */, Vector<VReal>& v_subAgentDisp, Vector<subAgentIdx_t>& v_divideSubAgentIdx, Vector<SubAgentState>& v_daughterSubAgentState, Vector<VReal>& v_daughterSubAgentDisp, Vector<Vector<BOOL> >& vv_junctionDivide/* true if belongs to the mother sub-agent, false if belongs to the daughter sub-agent */, Vector<BOOL>& v_motherDaughterLinked, Vector<JunctionEnd>& v_motherEnd, Vector<JunctionEnd>& v_daughterEnd, Vector<subAgentIdx_t>& v_disappearSubAgentIdx );

	static void divideMpAgent( const Vector<VIdx>& v_subAgentVIdx, const Vector<const JunctionData*>& vp_subJunctionData, const Vector<VReal>& v_subAgentOffset, const Vector<const MechIntrctData*>& vp_mechIntrctData, const Vector<NbrUBEnv>& v_nbrUBEnv/* [subAgentIdx] */, MpAgent& motherMpAgent/* INOUT */, MpAgent& daughterMpAgent, Vector<SubAgentState*>& vp_subAgentState/* INOUT */, Vector<VReal>& v_subAgentDisp, Vector<BOOL>& v_divide/* true if belongs to the mother multi-particle agent, false if belongs to the daughter multi-particle agent */ );
#endif

#if HAS_SPAGENT
	static void spAgentCRNODERHS( const S32 odeNetIdx, const VIdx& vIdx, const SpAgent& spAgent, const NbrUBEnv& nbrUBEnv, const Vector<double>& v_y, Vector<double>& v_f );

	static void updateSpAgentState( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const NbrUBEnv& nbrUBEnv, SpAgentState& state );

#if HAS_MPAGENT
	static void mpAgentSecretionBySpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state/* INOUT */, Vector<MpAgent>& v_mpAgent, Vector<Vector<SubAgentState> >& vv_subAgentState, Vector<Vector<VReal> >& vv_subAgentDisp, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx0, Vector<Vector<subAgentIdx_t> >& vv_junctionSubAgentIdx1, Vector<Vector<JunctionEnd> >& vv_end0, Vector<Vector<JunctionEnd> >& vv_end1 );
#endif
	static void spAgentSecretionBySpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state/* INOUT */, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentDisp );

	static void updateSpAgentBirthDeath( const VIdx& vIdx, const SpAgent& spAgent, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, BOOL& divide, BOOL& disappear );

	static void adjustSpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state/* INOUT */, VReal& disp );

	static void divideSpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& motherState/* INOUT */, VReal& motherDisp, SpAgentState& daughterState, VReal& daughterDisp, Vector<BOOL>& v_junctionDivide, BOOL& motherDaughterLinked, JunctionEnd& motherEnd, JunctionEnd& daughterEnd );
#endif

	/* mechanical interaction */

#if HAS_MPAGENT
	static void initJunctionSubAgent( const VIdx& vIdx0, const MpAgent& mpAgent0, const SubAgent& subAgent0, const VIdx& vIdx1, const MpAgent& mpAgent1, const SubAgent& subAgent1, const VReal& dir, const REAL& dist, BOOL& link, JunctionEnd& end0, JunctionEnd& end1 );

	static void computeMechIntrctSubAgent( const S32 iter, const VIdx& vIdx0, const MpAgent& mpAgent0, const SubAgent& subAgent0, const UBEnv& ubEnv0, const VIdx& vIdx1, const MpAgent& mpAgent1, const SubAgent& subAgent1, const UBEnv& ubEnv1, const VReal& dir, const REAL& dist, MechIntrctData& mechIntrctData0, MechIntrctData& mechIntrctData1, BOOL& link, JunctionEnd& end0, JunctionEnd& end1, BOOL& unlink );
#endif

#if HAS_SPAGENT
	static void initJunctionSpAgent( const VIdx& vIdx0, const SpAgent& spAgent0, const VIdx& vIdx1, const SpAgent& spAgent1, const VReal& dir, const REAL& dist, BOOL& link, JunctionEnd& end0, JunctionEnd& end1 );

	static void computeMechIntrctSpAgent( const S32 iter, const VIdx& vIdx0, const SpAgent& spAgent0, const UBEnv& ubEnv0, const VIdx& vIdx1, const SpAgent& spAgent1, const UBEnv& ubEnv1, const VReal& dir, const REAL& dist, MechIntrctData& mechIntrctData0, MechIntrctData& mechIntrctData1, BOOL& link, JunctionEnd& end0, JunctionEnd& end1, BOOL& unlink );
#endif

#if ( ( HAS_MPAGENT == 1 ) && ( HAS_SPAGENT == 1 ) )
	static void initJunctionSubAgentSpAgent( const VIdx& vIdx0, const MpAgent& mpAgent, const SubAgent& subAgent, const VIdx& vIdx1, const SpAgent& spAgent, const VReal& dir, const REAL& dist, BOOL& link, JunctionEnd& end0, JunctionEnd& end1 );

	static void computeMechIntrctSubAgentSpAgent( const S32 iter, const VIdx& vIdx0, const MpAgent& mpAgent, const SubAgent& subAgent, const UBEnv& ubEnv0, const VIdx& vIdx1, const SpAgent& spAgent, const UBEnv& ubEnv1, const VReal& dir, const REAL& dist, MechIntrctData& mechIntrctData0, MechIntrctData& mechIntrctData1, BOOL& link, JunctionEnd& end0, JunctionEnd& end1, BOOL& unlink );
#endif

	/* (advection) reaction diffusion PDE - interface grid */

	static void initIfGridVar( const VIdx& vIdx, const UBAgentData& ubAgentData, UBEnv& ubEnv );
	static void initIfSubgridKappa( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridKappa );/* relevant only if v_gridPhiOutputDivideByKappa[pdeIdx] is set to true in updateFileOutputInfo() */

	static void updateIfGridVar( const BOOL pre, const S32 iter, const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, NbrUBEnv& nbrUBEnv );/* if pre == true, adjust grid phi and model variables before a state-grid time step, if pre == false, adjust grid phi and model variables after a state-grid time step */

	static void updateIfSubgridKappa( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridKappa );

	static void updateIfSubgridAlpha( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridAlpha );
	static void updateIfSubgridBetaInIfRegion( const S32 elemIdx, const S32 dim, const VIdx& vIdx0, const VIdx& subgridVOffset0, const UBAgentData& ubAgentData0, const UBEnv& ubEnv0, const VIdx& vIdx1, const VIdx& subgridVOffset1, const UBAgentData& ubAgentData1, const UBEnv& ubEnv1, REAL& gridBeta );
	static void updateIfSubgridBetaPDEBufferBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridBeta );
	static void updateIfSubgridBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridBeta );

	static void updateIfSubgridAdvVelInIfRegion( const S32 pdeIdx, const S32 dim, const VIdx& vIdx0, const VIdx& subgridVOffset0, const UBAgentData& ubAgentData0, const UBEnv& ubEnv0, const VIdx& vIdx1, const VIdx& subgridVOffset1, const UBAgentData& ubAgentData1, const UBEnv& ubEnv1, REAL& gridAdvVel );
	static void updateIfSubgridAdvVelPDEBufferBdry( const S32 pdeIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridAdvVel );
	static void updateIfSubgridAdvVelDomainBdry( const S32 pdeIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridAdvVel );

	static void updateIfSubgridRHSLinear( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridRHS );
	static void adjustIfSubgridRHSTimeDependentLinear( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnvModelVar& ubEnvModelVar, const REAL gridPhi, REAL& gridRHS/* INOUT */ );
	static void updateIfSubgridRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnvModelVar& ubEnvModelVar, const Vector<REAL>& v_gridPhi/* [idx] */, Vector<double>& v_gridRHS );

	static void updateIfGridAMRTags( const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, const NbrUBEnv& nbrUBEnv, Vector<S32>& v_finestLevel/* [pdeIdx] */ );

	static void updateIfGridDirichletBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const UBEnvModelVar a_ubEnvModelVar[3], const Vector<REAL> av_gridPhi[3]/* av_gridPhi[].size() == ratio * raito * ratio (ratio = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx]), use VIdx::getIdx3DTo1D() to index */, REAL& bcVal );
	static void updateIfGridNeumannBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const UBEnvModelVar a_ubEnvModelVar[3], const Vector<REAL> av_gridPhi[3]/* av_gridPhi[].size() == ratio * raito * ratio (ratio = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx]), use VIdx::getIdx3DTo1D() to index */, REAL& bcVal );

	/* (advection) reaction diffusion PDE - PDE buffer */

	static void initPDEBufferVel( const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL a_gridVel[DIMENSION] );
	static void initPDEBufferPhi( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, Vector<REAL>& v_gridPhi );
	static void initPDEBufferKappa( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridKappa );/* relevant only if v_gridPhiOutputDivideByKappa[pdeIdx] is set to true in updateFileOutputInfo() */

	static void updatePDEBufferKappa( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridKappa );

	static void updatePDEBufferAlpha( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridAlpha );
	static void updatePDEBufferBetaInPDEBufferRegion( const S32 elemIdx, const S32 dim, const VIdx& startVIdx0, const VIdx& startVIdx1, const VIdx& pdeBufferBoxSize, REAL& gridBeta );
	static void updatePDEBufferBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridBeta );

	static void updatePDEBufferAdvVelInPDEBufferRegion( const S32 pdeIdx, const S32 dim, const VIdx& startVIdx0, const VIdx& startVIdx1, const VIdx& pdeBufferBoxSize, REAL& gridAdvVel );
	static void updatePDEBufferAdvVelDomainBdry( const S32 pdeIdx, const S32 dim, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridAdvVel );

	static void updatePDEBufferRHSLinear( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const REAL gridPhi, REAL& gridRHS );
	static void adjustPDEBufferRHSTimeDependentLinear( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const REAL gridPhi, REAL& gridRHS/* INOUT */ );
	static void updatePDEBufferRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const Vector<double>& v_gridPhi, Vector<double>& v_gridRHS );

	static void updatePDEBufferDirichletBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal );
	static void updatePDEBufferNeumannBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal );

	/* (file & summary) output */

#if HAS_MPAGENT
	static void updateSubAgentOutput( const VIdx& vIdx, const Vector<MpAgent>& v_mpAgent, const Vector<SubAgent>& v_subAgent, const Vector<partMpAgentIdx_t>& v_mpAgentIdx, const ubAgentIdx_t offsetIdx, Vector<REAL>& v_color, Vector<Vector<REAL> >& vv_extraScalar, Vector<Vector<REAL> >& vv_extraVector );
#endif

#if HAS_SPAGENT
	static void updateSpAgentOutput( const VIdx& vIdx, const Vector<SpAgent>& v_spAgent, const ubAgentIdx_t offsetIdx, Vector<REAL>& v_color, Vector<Vector<REAL> >& vv_extraScalar, Vector<Vector<REAL> >& vv_extraVector );
#endif

	static void updateSummaryVar( const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, const NbrUBEnv& nbrUBEnv, Vector<REAL>& v_realVal/* [elemIdx] */, Vector<S32>& v_intVal/* [elemIdx] */ );
};

#endif/* #ifndef __MODEL_IF_H__ */


/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

/* DO NOT USE FUNCTIONS THAT ARE NOT THREAD SAFE (e.g. rand(), use Util::getModelRand() instead) */

#include "biocellion.h"

#include "model_routine.h"

/* MODEL START */

#include "model_define.h"

/* MODEL END */

using namespace std;

void ModelRoutine::updateIfGridSpacing( REAL& ifGridSpacing ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateOptModelRoutineCallInfo( OptModelRoutineCallInfo& callInfo ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateDomainBdryType( domain_bdry_type_e a_domainBdryType[DIMENSION] ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferBdryType( pde_buffer_bdry_type_e& pdeBufferBdryType ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateTimeStepInfo( TimeStepInfo& timeStepInfo ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateSyncMethod( sync_method_e& mechIntrctSyncMethod, sync_method_e& updateIfGridVarSyncMethod/* dummy if both callUpdateIfGridVarPreStateAndGridStep and callUpdateIfGridVarPostStateAndGridStep are set to false in ModelRoutine::updateOptModelRoutineCallInfo */ ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

#if HAS_SPAGENT
void ModelRoutine::updateSpAgentInfo( Vector<SpAgentInfo>& v_spAgentInfo ) {/* set the mechanical interaction range & the numbers of model specific variables */
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}
#endif

void ModelRoutine::updateJunctionEndInfo( Vector<JunctionEndInfo>& v_junctionEndInfo ) {/* set the numbers of model specific variables */
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePhiPDEInfo( Vector<PDEInfo>& v_phiPDEInfo ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridModelVarInfo( Vector<IfGridModelVarInfo>& v_ifGridModelRealInfo, Vector<IfGridModelVarInfo>& v_ifGridModelIntInfo ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateRNGInfo( Vector<RNGInfo>& v_rngInfo ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateFileOutputInfo( FileOutputInfo& fileOutputInfo ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateSummaryOutputInfo( Vector<SummaryOutputInfo>& v_summaryOutputRealInfo, Vector<SummaryOutputInfo>& v_summaryOutputIntInfo ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::initGlobal( Vector<U8>& v_globalData ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::init( void ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::term( void ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::setPDEBuffer( const VIdx& startVIdx, const VIdx& regionSize, BOOL& isPDEBuffer ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::setHabitable( const VIdx& vIdx, BOOL& isHabitable ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}


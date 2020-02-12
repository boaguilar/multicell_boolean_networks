/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

/* DO NOT USE FUNCTIONS THAT ARE NOT THREAD SAFE (e.g. rand(), use Util::getModelRand() instead) */

#include "biocellion.h"

#include "model_routine.h"

#include "model_define.h"

using namespace std;

void ModelRoutine::initIfGridVar( const VIdx& vIdx, const UBAgentData& ubAgentData, UBEnv& ubEnv ) {
    /* MODEL START */

    for( S32 elemIdx = 0 ; elemIdx < NUM_CYTOKINES; elemIdx++ ) {
       ubEnv.setPhi( elemIdx, 0.0  );
    }

    for( S32 elemIdx = 0 ; elemIdx < NUM_GRID_MODEL_REALS ; elemIdx++ ) {
       ubEnv.setModelReal( elemIdx, 0.0 );
    }

    /* MODEL END */

    return;
}

void ModelRoutine::initIfSubgridKappa( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridKappa ) {/* relevant only if v_gridPhiOutputDivideByKappa[pdeIdx] is set to true in updateFileOutputInfo() */
	/* MODEL START */
        
	gridKappa = 1.0;
        
	/* MODEL END */
        
	return;
}


void ModelRoutine::updateIfGridVar( const BOOL pre, const S32 iter, const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, NbrUBEnv& nbrUBEnv/* [INOUT] */ ) {
    /* MODEL START */
    
    CHECK( pre == true );
    CHECK( iter == 0 );
 
    const Vector<U8>& v_globalData = Info::getGlobalDataRef(); // data passed to all mpi proce 
    REAL colonyVolRatio = 0.0;
    REAL a_q[ NUM_CYTOKINES ];
    REAL dt = BASELINE_TIME_STEP_DURATION / NUM_STATE_AND_GRID_TIME_STEPS_PER_BASELINE;

    // Real cytoine parameters of secretion from  Global Data
    VIdx ifRegionSize;  // Help computing Index for data in global data
    ifRegionSize[0] = Info::getDomainSize(0) ;
    ifRegionSize[1] = Info::getDomainSize(1) ;
    ifRegionSize[2] = Info::getDomainSize(2) ;

    size_t CellDataSize = 2*sizeof(REAL) + sizeof(S32) + ifRegionSize[0]*ifRegionSize[1]*ifRegionSize[2]*sizeof(UBInitData) + INI_N_CELLS*sizeof(IniCellData) + INI_N_CELLS * MAX_NUM_NODES * sizeof(S32) ;

    const S32* p_cyto_secretion =  ( const S32* )&( v_globalData[ CellDataSize + NUM_CYTOKINES*NUM_BN_NETWORKS*2*sizeof(S32)  ] );
    const REAL* p_cyto_secretion_rate = ( const REAL* )&( v_globalData[ CellDataSize + NUM_CYTOKINES*NUM_BN_NETWORKS*(2*sizeof(S32) + sizeof(REAL)  )  ] ); 


    /* initialize variables of UnitBox */
    for( S32 elemIdx = 0 ; elemIdx < NUM_CYTOKINES; elemIdx++ ) {
       a_q[elemIdx] = 0.0;
    }

    /* iterate over 3 * 3 * 3 boxes */
    for( S32 i = -1 ; i <= 1 ; i++ ) {
        for( S32 j = -1 ; j <= 1 ; j++ ) {
            for( S32 k = -1 ; k <= 1 ; k++ ) {
                const UBAgentData& ubAgentData = *( nbrUBAgentData.getConstPtr(i,j,k));         
                VIdx ubVIdxOffset;
                ubVIdxOffset[0] = i* -1;
                ubVIdxOffset[1] = j* -1;
                ubVIdxOffset[2] = k* -1;

                for(ubAgentIdx_t l=0; l<(ubAgentIdx_t)ubAgentData.v_spAgent.size(); l++ ) {     
                    const SpAgent& spAgent = ubAgentData.v_spAgent[l];
                    REAL ratio = Util::computeSphereUBVolOvlpRatio( SPHERE_UB_VOL_OVLP_RATIO_MAX_LEVEL, spAgent.vOffset, spAgent.state.getRadius(), ubVIdxOffset );
                    agentType_t type = spAgent.state.getType();
     
                    if( ratio > 0.0 ) {
                        REAL radius;
                        REAL vol;
                         
                        Vector<S32> v_BState = spAgent.state.getModelIntArray(); 

                        /* compute colony volume */
                        radius = spAgent.state.getRadius();
                        vol = ( 4.0 * MY_PI / 3.0 ) * radius * radius * radius;
                        colonyVolRatio += vol * ratio;

                        S32 BNid = V_CELL_BN_ID[type]; 

                        /* compute total secretion of molecules   */
                        for( S32 elemIdx = 0 ; elemIdx < NUM_CYTOKINES ; elemIdx++ ) {

                            REAL local_ron = 1.0 ;
                            //*( p_cyto_secretion + type*NUM_CYTOKINES  +  elemIdx )

                            if ( BNid >= 0 )  {
                               S32 BoolId =  *( p_cyto_secretion + BNid*NUM_CYTOKINES  +  elemIdx )   ;
                               if (( BoolId >= 0 && BoolId < MAX_NUM_NODES ) && ( v_BState[BoolId] == 1)) {

                                   local_ron = *( p_cyto_secretion_rate + type*NUM_CYTOKINES  +  elemIdx )  ;
                                   a_q[elemIdx] += ratio* local_ron * dt;

                               }
                               else {
                               //else if ( ( BoolId >= 0 ) && ( v_BState[BoolId] == 0)) {
                                   a_q[elemIdx] += ratio*SECRETION_RATE_OFF  * dt;
                               //}
                               //else if ( ( BoolId >= 0 ) && ( v_BState[BoolId] == -1)) {
                               //    a_q[elemIdx] += ratio*SECRETION_RATE_OFF  * dt;
                               }  
                           }
                        }
                    }   
                }
            }
        }
    } 
    colonyVolRatio /= ( IF_GRID_SPACING * IF_GRID_SPACING * IF_GRID_SPACING );
    if( colonyVolRatio > 1.0 ) {
        colonyVolRatio = 1.0;
    }
    nbrUBEnv.setModelReal(0,0,0, GRID_MODEL_REAL_AGENT_VOL_RATIO ,colonyVolRatio);

    /* initialize variables of UnitBox */
    for( S32 elemIdx = 0 ; elemIdx < NUM_CYTOKINES; elemIdx++ ) {
       a_q[elemIdx] /= (IF_GRID_SPACING*IF_GRID_SPACING*IF_GRID_SPACING) ;
       nbrUBEnv.setModelReal(0,0,0, elemIdx, a_q[elemIdx]);
    }
 
    

    //cout << "a_q: "; 
    //for( S32 elemIdx = 0 ; elemIdx < NUM_GRID_PHIS; elemIdx++ ) {
    //      cout <<  a_q[elemIdx] << " " ;
    //} cout << endl ;
    /* MODEL END */

    return;
}

void ModelRoutine::updateIfSubgridKappa( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridKappa/* to consider cell volume exclusion in computing diffusion flux, set to 1.0 to ignore the volume occupied by cells */ ) {
	/* MODEL START */

        gridKappa = 1.0;

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfSubgridAlpha( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridAlpha/* decay (-) */ ) {
	/* MODEL START */

        //if ( (elemIdx == GRID_PHI_TOXIC) || (elemIdx == GRID_PHI_PDL1) || (elemIdx == GRID_PHI_AG) ) {
        //    gridAlpha = -1.0*GAMMA_SHORT_DIST  ;
        //    
        //}
        //else {
	    gridAlpha = -1.0* GAMMA  ;
        //}

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfSubgridBetaInIfRegion( const S32 elemIdx, const S32 dim, const VIdx& vIdx0, const VIdx& subgridVOffset0, const UBAgentData& ubAgentData0, const UBEnv& ubEnv0, const VIdx& vIdx1, const VIdx& subgridVOffset1, const UBAgentData& ubAgentData1, const UBEnv& ubEnv1, REAL& gridBeta ) {
	/* MODEL START */

	gridBeta = DIFFUSION_COEFF; 

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfSubgridBetaPDEBufferBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridBeta ) {
	/* MODEL START */

	gridBeta = 0.0;

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfSubgridBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridBeta ) {
	/* MODEL START */

        gridBeta = DIFFUSION_COEFF;

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfSubgridRHSLinear( const S32 elemIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnv& ubEnv, REAL& gridRHS/* uptake(-) and secretion (+) */ ) {
	/* MODEL START */

       gridRHS = ubEnv.getModelReal( elemIdx ); 
	/* MODEL END */

	return;
}

void ModelRoutine::updateIfSubgridRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& vIdx, const VIdx& subgridVOffset, const UBAgentData& ubAgentData, const UBEnvModelVar& ubEnvModelVar, const Vector<double>& v_gridPhi/* [idx] */, Vector<double>& v_gridRHS/* [idx], uptake(-) and secretion (+) */ ) {/* for Wnt & SFRP */
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridAMRTags( const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, const NbrUBEnv& nbrUBEnv, Vector<S32>& v_finestLevel/* [pdeIdx] */ ) {
	/* MODEL START */

	v_finestLevel.assign( NUM_CYTOKINES  , NUM_AMR_LEVELS - 1 );/* finest level */
	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridDirichletBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const UBEnvModelVar a_ubEnvModelVar[3], const Vector<REAL> av_gridPhi[3]/* av_gridPhi[].size() == ratio * raito * ratio (ratio = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx]), use VIdx::getIdx3DTo1D() to index */, REAL& bcVal ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridNeumannBCVal( const S32 elemIdx, const VReal& pos, const S32 dim, const BOOL lowSide, const UBEnvModelVar a_ubEnvModelVar[3], const Vector<REAL> av_gridPhi[3]/* av_gridPhi[].size() == ratio * raito * ratio (ratio = Info::envAuxDataInfo.v_phiRatioFromIfGridToIfSubgrid[elemIdx]), use VIdx::getIdx3DTo1D() to index */, REAL& bcVal ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::initPDEBufferPhi( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, Vector<REAL>& v_gridPhi/* [idx] */ ) {
	/* MODEL START */

	ERROR( "unimplemented." );
	//v_gridPhi[ GRID_PHI_EGF ] = 0.0 ; 

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferKappa( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridKappa/* to consider cell volume exclusion in computing diffusion flux, set to 1.0 to ignore the volume occupied by cells */ ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferAlpha( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridAlpha/* decay (-) */ ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferBetaInPDEBufferRegion( const S32 elemIdx, const S32 dim, const VIdx& startVIdx0, const VIdx& startVIdx1, const VIdx& pdeBufferBoxSize, REAL& gridBeta ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferBetaDomainBdry( const S32 elemIdx, const S32 dim, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, REAL& gridBeta ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferRHSLinear( const S32 elemIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const REAL gridPhi, REAL& gridRHS/* uptake(-) and secretion (+) */ ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferRHSTimeDependentSplitting( const S32 pdeIdx, const VIdx& startVIdx, const VIdx& pdeBufferBoxSize, const Vector<double>& v_gridPhi/* [idx] */, Vector<double>& v_gridRHS/* [idx], uptake(-) and secretion (+) */ ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferDirichletBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal ) {
	/* MODEL START */

	ERROR( "unimplmented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferNeumannBCVal( const S32 elemIdx, const VReal& startPos, const VReal& pdeBufferFaceSize, const S32 dim, const BOOL lowSide, REAL& bcVal ) {
	/* MODEL START */

	ERROR( "unimplmented." );

	/* MODEL END */

	return;
}


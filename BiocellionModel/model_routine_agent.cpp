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

#if HAS_SPAGENT
void ModelRoutine::addSpAgents( const BOOL init, const VIdx& startVIdx, const VIdx& regionSize, const IfGridBoxData<BOOL>& ifGridHabitableBoxData, Vector<VIdx>& v_spAgentVIdx, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentOffset ) {/* initialization */
	/* MODEL START */
	if( init == true ) {

                //cout << " SEEEEEEEEEEEEe " << endl;   
                const Vector<U8>& v_globalData = Info::getGlobalDataRef(); // data passed to all mpi proce
                VIdx ifRegionSize;  // Help computing Index for data in global data
                const UBInitData* p_ubInitData; // recreating pointers to the data
                const IniCellData* p_IniCellData;
                const S32* p_InitStatesData;

                ifRegionSize[0] = Info::getDomainSize(0) ;
                ifRegionSize[1] = Info::getDomainSize(1) ;
                ifRegionSize[2] = Info::getDomainSize(2) ;

                // Reading the address where data is located.
                p_ubInitData = ( const UBInitData* )&(  v_globalData[ 2*sizeof(REAL) + sizeof(S32) ] );
                p_IniCellData = ( const IniCellData* )&( v_globalData[ 2*sizeof(REAL) + sizeof(S32) + ifRegionSize[0]*ifRegionSize[1]*ifRegionSize[2]*sizeof(UBInitData)] );
                p_InitStatesData = ( const S32* )&( v_globalData[ 2*sizeof(REAL) + sizeof(S32) + ifRegionSize[0]*ifRegionSize[1]*ifRegionSize[2]*sizeof(UBInitData) + INI_N_CELLS*sizeof(IniCellData)] );

                S32 CellCounter = 0;
                // Place cells according to input file

                for ( S32 i = startVIdx[0]; i < startVIdx[0] + regionSize[0] ; i++ ) {
                        for ( S32 j = startVIdx[1]; j < startVIdx[1] + regionSize[1] ; j++ ) {
                                for ( S32 k = startVIdx[2]; k < startVIdx[2] + regionSize[2] ; k++ ) {
                                        VIdx posVIdx;     // Voxel in the biocellion
                                        VIdx vIdxOffset;  // Voxel in the input file
   

                                        posVIdx[0] = i;
                                        posVIdx[1] = j;
                                        posVIdx[2] = k;

                                        vIdxOffset = posVIdx;
                                        const UBInitData& ubInitData = p_ubInitData[VIdx::getIdx3DTo1D( vIdxOffset, ifRegionSize )];

                                        if ( ubInitData.numCells > 0 ) {
                                                S32 IdxCell = ubInitData.IdxIniCellData ;
                                                for ( S32 i = 0; i < ubInitData.numCells ; i++) {

                                                        const IniCellData& cellInitData = p_IniCellData[IdxCell];
                                                        SpAgentState state;
                                                        VReal posOffset;
                                                        S32 atype;
                                                        S32 line_id ;
                                                        REAL radius;

                                                        posOffset[0] = cellInitData.x_offset ;
                                                        posOffset[1] = cellInitData.y_offset ;
                                                        posOffset[2] = cellInitData.z_offset ;
                                                        radius = cellInitData.r_size;
                                                        atype  = cellInitData.a_type;
                                                        line_id = cellInitData.line_id;
                                                        
							Vector <S32> v_testArray;
                                                        for ( S32 n = 0; n < MAX_NUM_NODES; n++ ){
                                                              v_testArray.push_back( *(p_InitStatesData + IdxCell *MAX_NUM_NODES + n));
                                                        }
                                                        //if ( atype == 1 ) {
                                                        //    v_testArray[0] = 0;
                                                        //}
                                                        //else if ( atype == 3 ) { 
                                                        //    v_testArray[0] = 1;
							//    v_testArray[1] = 1;
							//    v_testArray[3] = 1;
                                                        //}
							//else if ( atype == 4 ) {
							//    v_testArray[0] =
							//}

                                                        CellCounter += 1;

                                                        state.setType( atype );
                                                        state.setRadius( radius );
                                                        state.setModelIntArray( v_testArray); // initial states of the boolean networks
                                                        state.setModelReal( CELL_MODEL_REAL_LINE_ID, line_id  )
                                                        
                                                        CHECK( ifGridHabitableBoxData.get( posVIdx ) == true );
                                                        v_spAgentVIdx.push_back( posVIdx );
                                                        v_spAgentState.push_back( state );
                                                        v_spAgentOffset.push_back( posOffset );
                                                       

                                                        IdxCell = cellInitData.IdxIniCellData ;

                                                }
                                        }
                                }
                        }
                }

                //cout << " NOOOOOO " << endl;
        }

        
	/* MODEL END */

	return;
}

void ModelRoutine::spAgentCRNODERHS( const S32 odeNetIdx, const VIdx& vIdx, const SpAgent& spAgent, const NbrUBEnv& nbrUBEnv, const Vector<double>& v_y, Vector<double>& v_f ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateSpAgentState( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const NbrUBEnv& nbrUBEnv, SpAgentState& state/* INOUT */ ) {
   /* MODEL START */

   // do nothing

   /* MODEL END */

   return;
}

void ModelRoutine::spAgentSecretionBySpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state/* INOUT */, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentDisp ) {
	/* MODEL START */


	/* MODEL END */

	return;
}

void ModelRoutine::updateSpAgentBirthDeath( const VIdx& vIdx, const SpAgent& spAgent, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, BOOL& divide, BOOL& disappear ) {
	/* MODEL START */

	divide = false;
	disappear = false;

	/* MODEL END */

	return;
}

void ModelRoutine::adjustSpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& state/* INOUT */, VReal& disp ) {/* if not dividing or disappearing */
	/* MODEL START */
        
	Vector <S32> v_tempState;
        Vector <S32> v_holdState;
        Vector <BOOL> v_noiseflag( MAX_NUM_NODES , true  ) ;
        v_tempState = state.getModelIntArray();
        v_holdState = state.getModelIntArray(); // state doesn't change. use only for reference
        S32 type = state.getType();  
        //S32 BNid = V_CELL_BN_ID[type];

        // mutations are specified by -1 in the initial state
        for ( S32 i = 0; i < (S32) v_tempState.size() ; i++ ){ // gene loop
            if ( v_tempState[i] == -1 ) {
                v_holdState[i] = 0 ;
            }
        }

        // estimate average concentration
        REAL aaa_ratio[3][3][3];
        REAL a_avg_phi[ NUM_CYTOKINES ];
        for ( S32 elemIdx = 0; elemIdx < NUM_CYTOKINES ;  elemIdx++){
             a_avg_phi[ elemIdx ] = 0.0;
        }
        Util::computeSphereUBVolOvlpRatio( SPHERE_UB_VOL_OVLP_RATIO_MAX_LEVEL, vOffset, state.getRadius(), aaa_ratio );
        for( S32 i = -1 ; i <= 1 ; i++ ) {
          for( S32 j = -1 ; j <= 1 ; j++ ) {
            for( S32 k = -1 ; k <= 1 ; k++ ) {
               for ( S32 elemIdx = 0; elemIdx < NUM_CYTOKINES ; elemIdx++){
                  a_avg_phi[elemIdx] += nbrUBEnv.getPhi(i,j,k,elemIdx)*aaa_ratio[i+1][j+1][k+1];
               }
            }
          }
        }    
 
        
        // looking up the Truth Table
        const Vector<U8>& v_globalData = Info::getGlobalDataRef(); // data passed to all mpi proce
        VIdx ifRegionSize;  // Help computing Index for data in global data
        const S32* p_TtableData;
        const S32* p_varFData;
        const S32* p_BNetwork  ;
  
        S32 NumGenes = 0; 
        S32 NumVarfRows =0 ;
        S32 NumTTRows =0 ; 

        ifRegionSize[0] = Info::getDomainSize(0) ;
        ifRegionSize[1] = Info::getDomainSize(1) ;
        ifRegionSize[2] = Info::getDomainSize(2) ;

        size_t CellDataSize = 2*sizeof(REAL) + sizeof(S32) + ifRegionSize[0]*ifRegionSize[1]*ifRegionSize[2]*sizeof(UBInitData) + INI_N_CELLS*sizeof(IniCellData) + INI_N_CELLS * MAX_NUM_NODES * sizeof(S32) ;
        size_t CytokineSize =  NUM_CYTOKINES * NUM_BN_NETWORKS * 2 * ( sizeof(REAL) + sizeof(S32) ) ; 
        size_t DataBeforeBNs = CellDataSize + CytokineSize ;

        // Data of cytoine receptors 
        const S32* p_cyto_receptors  =  ( const S32* )&( v_globalData[ CellDataSize ] );
        const REAL* p_cyto_receptors_rate  = ( const REAL* )&( v_globalData[ CellDataSize  + NUM_CYTOKINES*NUM_BN_NETWORKS*2*sizeof(S32) ] );

        S32 BNetwork_id = V_CELL_BN_ID[ (S32) state.getType() ] ;// This is to link BNetwork with CellTypes 

        // obtain the length of memory just before the desired BN      
        for ( S32 i = 0; i <= BNetwork_id; i++ ) {
              p_BNetwork  =  ( const S32* )&( v_globalData[ DataBeforeBNs ] );   
              NumGenes = *( p_BNetwork ) ;
              NumVarfRows  = *( p_BNetwork + 1) ;
              NumTTRows   = *( p_BNetwork + 2 ) ;
              p_varFData = (const S32*)&(v_globalData[ DataBeforeBNs + (3 + NumGenes)*sizeof(S32)]);
              p_TtableData = (const S32*)&(v_globalData[ DataBeforeBNs + (3 + NumGenes + NumGenes*NumVarfRows)*sizeof(S32) ] );
              DataBeforeBNs += (3 + NumGenes + NumGenes*NumVarfRows + NumGenes*NumTTRows)*sizeof(S32); 

        }

        // Mark genes with noise  
        for ( S32 i = 0; i < NumGenes ; i++ ){ // gene loop
            BOOL noinputs = true ;  
            for ( S32 k = 0; k < NumVarfRows; k++ ) {
                 if ( *( p_varFData + k*NumGenes  + i) != -1 ) {
                       noinputs = false ;
                       break;
                 }
            } 
            v_noiseflag[i] = ! noinputs ;        
        }
        for ( S32 elemIdx = 0; elemIdx < NUM_CYTOKINES ; elemIdx++) {
            S32 gene_id = *( p_cyto_receptors + type*NUM_CYTOKINES  +  elemIdx ); 
            //S32 gene_id = AA_BOOLNET_INPUTS[elemIdx][BNid];
            if ( gene_id >= 0 )  {
                 v_noiseflag[ gene_id ] = true; 
            }
        }
 

        // Perturbation
        if ( (BN_PERTURBATION > 0) && (Util::getModelRand( MODEL_RNG_UNIFORM ) < BN_PERTURBATION )) {
              
            for ( S32 i = 0; i < NumGenes ; i++ ){ // gene loop  
                    if ( v_noiseflag[i] && ( Util::getModelRand( MODEL_RNG_UNIFORM ) < GENE_PERTURBATION) ) {
                       if ( v_tempState[i] == 0 ) 
                           v_tempState[i] = 1;
                       else if ( v_tempState[i] == 1) // state -1 is possible
                           v_tempState[i] = 0; 
                    }
            }
        }
        else {
            for ( S32 i = 0; i < NumGenes ; i++ ){ /** gene loop */
                       
                if ( v_tempState[i] != -1 ) {               
 
                    Vector <S32> v_wiringNode;
                    Vector <S32> v_lookupNode;
                	
                    for ( S32 k = 0; k < NumVarfRows; k++ ) { 
                       	v_wiringNode.push_back( *( p_varFData + k*NumGenes  + i) ) ; 

                    }
                                       

                    //from varF, translate each column of varF to wiringNode 
                    for ( S32 l = 0 ; l < ( S32 )v_wiringNode.size(); l++ ) {
                        if (v_wiringNode[l] != -1) { 
                            v_lookupNode.push_back( v_holdState[ v_wiringNode[l] ] );// was -1, modified for indexing starting in zero
                        }
                    }
 
	            // change lookedup number to binary
                    S32 lookupNumber = -1;
                    if (v_lookupNode.size() != 0 ) {
                       	lookupNumber = 0;
                       	for ( S32 z = 0; z < ( S32 )v_lookupNode.size() ; z++ ) {
                            lookupNumber += pow(2, v_lookupNode.size() - z - 1)* v_lookupNode[z];
                       	}
                    }

                    // with the lookupNumber, look it up in Truth Table, and store it in v_tempState
                    if ( lookupNumber != -1 ) {
                        v_tempState[i] = ( *( p_TtableData + (lookupNumber) *NumGenes  + i ) );
                    }

                    v_wiringNode.clear();
                    v_lookupNode.clear();
                }
            }
  
 
            /** Update receptor using concentrations */
            for ( S32 elemIdx = 0; elemIdx < NUM_CYTOKINES; elemIdx++){
   
                S32 gene_id = *( p_cyto_receptors + type*NUM_CYTOKINES  +  elemIdx );
                REAL local_tresh =  *( p_cyto_receptors_rate + type*NUM_CYTOKINES + elemIdx )  ;

                REAL local_phi_off = PHI_OFF ;

                if ( (gene_id >= 0) && ( v_tempState[ gene_id ] != -1 ) )  {
                    if ( ( a_avg_phi[elemIdx] / local_phi_off  ) > local_tresh  ) 
                        v_tempState[ gene_id ] = 1 ;          
                    else 
                        v_tempState[ gene_id ] = 0 ;
                }

            }
                
        }
                   
	state.setModelIntArray( v_tempState );

        
        //cout << "NOOOOOOOOOO" << endl;

	/* MODEL END */

	return;
}

void ModelRoutine::divideSpAgent( const VIdx& vIdx, const JunctionData& junctionData, const VReal& vOffset, const MechIntrctData& mechIntrctData, const NbrUBEnv& nbrUBEnv, SpAgentState& motherState/* INOUT */, VReal& motherDisp, SpAgentState& daughterState, VReal& daughterDisp, Vector<BOOL>& v_junctionDivide, BOOL& motherDaughterLinked, JunctionEnd& motherEnd, JunctionEnd& daughterEnd ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}
#endif


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

                
                const Vector<U8>& v_globalData = Info::getGlobalDataRef(); // data passed to all mpi proce
                VIdx ifRegionSize;  // Help computing Index for data in global data
                const UBInitData* p_ubInitData; // recreating pointers to the data
                const IniCellData* p_IniCellData;
                const S32* p_InitStatesData;


                ifRegionSize[0] = Info::getDomainSize(0) ;
                ifRegionSize[1] = Info::getDomainSize(1) ;
                ifRegionSize[2] = Info::getDomainSize(2) ;

                // !!!!!! This check would be a little bit more complex now
                //CHECK( v_globalData.size() == ( ifRegionSize[ 0 ] * ifRegionSize [ 1 ] * ifRegionSize [ 2 ] * sizeof( UBInitData ) ) + INI_N_CELLS * sizeof( IniCellData ) + INI_N_CELLS * NUM_NODES * sizeof( S32 ) + T_TABLE_ROWS * NUM_NODES * sizeof( S32 ) + VAR_F_ROWS * NUM_NODES * sizeof( S32 ) + NUM_NODES * sizeof( S32 ) );

                // Reading the address where data is located.
                p_ubInitData = ( const UBInitData* )&( v_globalData[0] );
                p_IniCellData = ( const IniCellData* )&( v_globalData[ ifRegionSize[0]*ifRegionSize[1]*ifRegionSize[2]*sizeof(UBInitData)] );
                p_InitStatesData = ( const S32* )&( v_globalData[ifRegionSize[0]*ifRegionSize[1]*ifRegionSize[2]*sizeof(UBInitData) + INI_N_CELLS*sizeof(IniCellData)] );


                S32 CellCounter;
                CellCounter = 0;
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
                                                        REAL radius;

                                                        posOffset[0] = cellInitData.x_offset ;
                                                        posOffset[1] = cellInitData.y_offset ;
                                                        posOffset[2] = cellInitData.z_offset ;
                                                        radius = cellInitData.r_size;
                                                        atype  = cellInitData.a_type;
							Vector <S32> v_testArray;
                                                        for ( S32 n = 0; n < MAX_NUM_NODES; n++ ){
                                                              v_testArray.push_back( *(p_InitStatesData + CellCounter*MAX_NUM_NODES + n));
                                                        }
                                                        CellCounter += 1;

                                                        state.setType( atype );
                                                        state.setRadius( radius );
                                                        state.setModelIntArray( v_testArray); // initial states of the boolean networks
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
        v_tempState = state.getModelIntArray();
        v_holdState = state.getModelIntArray(); // state doesn't change. use only for reference

        if ( ( Info::getCurBaselineTimeStep() > -1) ) {  //wait for the boolean network to be initialized, so don't update on first time step. 
        
        
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

                size_t  CellDataSize = ifRegionSize[0]*ifRegionSize[1]*ifRegionSize[2]*sizeof(UBInitData) + INI_N_CELLS*sizeof(IniCellData) + INI_N_CELLS * MAX_NUM_NODES * sizeof(S32);

                S32 BNetwork_id = V_CELL_BN_ID[ (S32) state.getType() ] ;// This is to link BNetwork with CellTypes 
                // obtain the length of memory just before the desired BN      
                for ( S32 i = 0; i <= BNetwork_id; i++ ) {
                    p_BNetwork  =  ( const S32* )&( v_globalData[ CellDataSize ] );   ;
                    NumGenes = *( p_BNetwork ) ;
                    NumVarfRows  = *( p_BNetwork + 1) ;
                    NumTTRows   = *( p_BNetwork + 2 ) ;
                    p_varFData = (const S32*)&(v_globalData[CellDataSize + (3 + NumGenes)*sizeof(S32)]);
                    p_TtableData = (const S32*)&(v_globalData[ CellDataSize + (3 + NumGenes + NumGenes*NumVarfRows)*sizeof(S32) ] );
                    CellDataSize += (3 + NumGenes + NumGenes*NumVarfRows + NumGenes*NumTTRows)*sizeof(S32); 
                }
       

        	for ( S32 i = 0; i < NumGenes ; i++ ){ // gene loop
                
                	Vector <S32> v_wiringNode;
                	Vector <S32> v_lookupNode;
                	
                	for ( S32 k = 0; k < NumVarfRows; k++ ) { 
                        	v_wiringNode.push_back( *( p_varFData + k*NumGenes  + i) ) ; 
                	}

                	//from varF, translate each column of varF to wiringNode 
                	for ( S32 l = 0 ; l < ( S32 )v_wiringNode.size(); l++ ) {
                        	if (v_wiringNode[l] == -1) {  // !!!! replace by a single if statement
                                	// do nothing
                        	} else{
                                	v_lookupNode.push_back( v_holdState[ v_wiringNode[l] -1 ] ) ; // -1 one because each gene indexing goes from [0,17] not [1,18]
                                	
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

        //cout << "------------------ End of adjustSpAgent -------------------------" << endl << endl;
	state.setModelIntArray( v_tempState );
	
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


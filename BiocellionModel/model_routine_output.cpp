/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

/* DO NOT USE FUNCTIONS THAT ARE NOT THREAD SAFE (e.g. rand(), use Util::getModelRand() instead) */

#include "biocellion.h"

#include "model_routine.h"

/* UESR START */

#include "model_define.h"

/* UESR END */

using namespace std;

#if HAS_SPAGENT
void ModelRoutine::updateSpAgentOutput( const VIdx& vIdx, const SpAgent& spAgent, REAL& color, Vector<REAL>& v_extraScalar, Vector<VReal>& v_extraVector ) {

	/* MODEL START */
        Vector <S32> v_temp;
        v_temp = spAgent.state.getModelIntArray();
        for ( S32 i = 0; i < MAX_NUM_NODES ; i++ ) {
           if ( v_temp[i] < 1 ) {
              v_temp[i] = 0;
           } else {
              v_temp[i] = 1;
           }
        }  

        S32 type = spAgent.state.getType() ;
        //S32 bn_id = V_CELL_BN_ID[type];
        color = type ;
        S32 State_1 = 0;
        S32 State_2 = 0; 
         
        
        S32 BIT_LENGTH = 25 ;
         
        for ( S32 i = 0; i < BIT_LENGTH  ;  i++ )
             if ( i < MAX_NUM_NODES )  
                 State_1 = State_1 +  v_temp[ i  ] * pow(2,i) ;
        
        for ( S32 i = BIT_LENGTH ; i < 50  ; i++ )
             if ( i < MAX_NUM_NODES )  
                  State_2 = State_2 +  v_temp[ i  ] * pow(2,i- BIT_LENGTH  ) ;
            

        v_extraScalar[ CELL_EXTRA_OUTPUT_ALLBN1 ] = State_1 ;
        v_extraScalar[ CELL_EXTRA_OUTPUT_ALLBN2 ] = State_2 ;
	/* MODEL END */

	return;
}
#endif

void ModelRoutine::updateSummaryVar( const VIdx& vIdx, const NbrUBAgentData& nbrUBAgentData, const NbrUBEnv& nbrUBEnv, Vector<REAL>& v_realVal/* [elemIdx] */, Vector<S32>& v_intVal/* [elemIdx] */ ) {
	/* MODEL START */

        const UBAgentData& ubAgentData = *( nbrUBAgentData.getConstPtr( 0, 0, 0 ) );
        REAL sum_bn_states[ NUM_BN_NETWORKS *  MAX_NUM_NODES  ]; 
        for ( S32 i = 0 ; i < ( NUM_BN_NETWORKS*MAX_NUM_NODES ) ; i++ ) { 
            sum_bn_states[ i ] = 0 ;  
        } 

        for (S32 i = 0 ; i < ( S32 )ubAgentData.v_spAgent.size() ; i++ ) {

            S32 bnid = V_CELL_BN_ID[ (S32) ubAgentData.v_spAgent[i].state.getType()   ] ; 
            if ( bnid > -1 ) {
                Vector<S32> v_tempState  =  ubAgentData.v_spAgent[i].state.getModelIntArray();
                for ( S32 j = 0; j < MAX_NUM_NODES  ; j++ ){
                    if ( v_tempState[ j ] > 0  ) {
                        sum_bn_states[ ( bnid*MAX_NUM_NODES ) + j  ] += v_tempState[ j ] ;
                    }
                }
            }
          
        }

        // GRID_SUMMARY_REAL_LIVE_CELLS is set in mdoel_routine_config.cpp.
        v_realVal[GRID_SUMMARY_REAL_LIVE_CELLS] =  ( REAL )ubAgentData.v_spAgent.size()   ;
        v_realVal[GRID_SUMMARY_REAL_DENSITY] = nbrUBEnv.getModelReal(0,0,0,GRID_MODEL_REAL_AGENT_VOL_RATIO );

        for ( S32 cytokineID = 0; cytokineID < NUM_CYTOKINES; cytokineID++ ) {
            v_realVal[ NUM_GRID_SUMMARY_REALS + cytokineID ] = nbrUBEnv.getPhi(0,0,0, cytokineID )  ;
        }
  
        for (S32 i = 0 ; i < ( NUM_BN_NETWORKS*MAX_NUM_NODES   )  ; i++ ) {
           v_intVal[i] = sum_bn_states[ i ] ;  
        }

	return;
}


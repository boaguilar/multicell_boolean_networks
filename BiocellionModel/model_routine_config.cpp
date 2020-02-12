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

S32 INI_N_CELLS;
S32 NUM_BN_NETWORKS;
S32 MAX_NUM_NODES; 
S32 NUM_CYTOKINES;
REAL GAMMA;      
REAL PHI_OFF; 

using namespace std;

// user defined functions
static Vector<string> readXMLParameters() ;
static Vector<S32>  readINTvaluesLine( S8* p_buf ) ;

void ModelRoutine::updateIfGridSpacing( REAL& ifGridSpacing ) {
	/* MODEL START */

	ifGridSpacing = IF_GRID_SPACING;

	/* MODEL START */
		
	return;
}

void ModelRoutine::updateOptModelRoutineCallInfo( OptModelRoutineCallInfo& callInfo ) {
	/* MODEL START */

     	callInfo.numComputeMechIntrctIters = 1;
        callInfo.numUpdateIfGridVarPreStateAndGridStepIters = 1;
        callInfo.numUpdateIfGridVarPostStateAndGridStepIters = 0;

	/* MODEL END */

	return;
}

void ModelRoutine::updateDomainBdryType( domain_bdry_type_e a_domainBdryType[DIMENSION] ) {
	/* MODEL START */

        a_domainBdryType[0] = DOMAIN_BDRY_TYPE_PERIODIC;
        a_domainBdryType[1] = DOMAIN_BDRY_TYPE_PERIODIC;
        a_domainBdryType[2] = DOMAIN_BDRY_TYPE_PERIODIC;

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferBdryType( pde_buffer_bdry_type_e& pdeBufferBdryType ) {
	/* MODEL START */

      	pdeBufferBdryType = PDE_BUFFER_BDRY_TYPE_HARD_WALL;

	/* MODEL END */

	return;
}

void ModelRoutine::updateTimeStepInfo( TimeStepInfo& timeStepInfo ) {
	/* MODEL START */

 	timeStepInfo.durationBaselineTimeStep = BASELINE_TIME_STEP_DURATION;
        timeStepInfo.numStateAndGridTimeStepsPerBaseline = NUM_STATE_AND_GRID_TIME_STEPS_PER_BASELINE;

	/* MODEL END */

	return;
}

void ModelRoutine::updateSyncMethod( sync_method_e& mechIntrctSyncMethod, sync_method_e& updateIfGridVarSyncMethod/* dummy if both callUpdateIfGridVarPreStateAndGridStep and callUpdateIfGridVarPostStateAndGridStep are set to false in ModelRoutine::updateOptModelRoutineCallInfo */ ) {
	/* MODEL START */

        mechIntrctSyncMethod = SYNC_METHOD_PER_ATTR;
        updateIfGridVarSyncMethod = SYNC_METHOD_PER_ATTR;

	/* MODEL END */

	return;
}

#if HAS_SPAGENT
void ModelRoutine::updateSpAgentInfo( Vector<SpAgentInfo>& v_spAgentInfo ) {/* set the mechanical interaction range & the numbers of model specific variables */
	/* MODEL START */

        Vector<string> v_modelParam = readXMLParameters();
        if ( v_modelParam.size() != NUM_PARAMETERS ) {
                ERROR( "invalid model parameters: invalid number of parameters." );
        }

        FILE* p_file;
        size_t bufSize;
        ssize_t numCharsRead;
        Vector<S32> v_numNodes;

        string nvfile = v_modelParam[3].append(".nv")  ;
        p_file = fopen( nvfile.c_str(), "r" ); //check if the second param (nv.txt) is Non-Empty

        //check if the second param (nv.txt) is Non-Empty         
        if( p_file == NULL ) {
                ERROR( "Can't open nv.txt" );
        }else {
                S8* p_buf = NULL; 
                bufSize = 0;
                
                while( ( numCharsRead = getline( &p_buf, &bufSize, p_file ) ) != -1 ) {
                     Vector<S32> v_nv = readINTvaluesLine( p_buf ) ;
                     if (  v_nv.empty() ) { 
                        ERROR("Can not read nv line ");
                     }
                     v_numNodes.push_back( v_nv.size()) ;
                }

                if ( p_buf != NULL ) {
                        free (p_buf);
                }
        }
        fclose(p_file);

        // we will allocate same space for all celltypes !!! needs improvement
        S32 MaxNumGenes = -1;
        for ( S32 i = 0; i < (S32) v_numNodes.size(); i++ ){
            if ( MaxNumGenes < v_numNodes[i] ) 
               MaxNumGenes = v_numNodes[i];
        }

        // TODO : prompt error if this number is greater than MAXNUM_CELL_TYPE
        NUM_BN_NETWORKS = (S32) v_numNodes.size();
        MAX_NUM_NODES = MaxNumGenes ;

	MechModelVarInfo modelVarInfo;
        modelVarInfo.syncMethod = VAR_SYNC_METHOD_DELTA;/* computeMechIntrct */
        v_spAgentInfo.resize( NUM_BN_NETWORKS  );

        for( S32 i = 0 ; i <  NUM_BN_NETWORKS  ; i++ ) {
                SpAgentInfo info;

                info.dMax = IF_GRID_SPACING;
                //info.hasBool = false;
                info.numBoolVars = 0;
                info.numStateModelReals = CELL_NUM_MODEL_REALS; // 
                info.numStateModelInts = MAX_NUM_NODES ; // !!!!!!!!! needs change
		info.v_mechIntrctModelRealInfo.clear();
               	info.v_mechIntrctModelIntInfo.clear(); // 
               	//info.v_mechIntrctModelIntInfo.assign( 3, modelVarInfo ); // 
	      	info.v_odeNetInfo.clear();

                v_spAgentInfo[i] = info;
        }

	/* MODEL END */

	return;
}
#endif

void ModelRoutine::updateJunctionEndInfo( Vector<JunctionEndInfo>& v_junctionEndInfo ) {/* set the numbers of model specific variables */
	/* MODEL START */

        v_junctionEndInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updatePhiPDEInfo( Vector<PDEInfo>& v_phiPDEInfo ) {
	/* MODEL START */

        Vector<string> v_modelParam = readXMLParameters();
        if ( v_modelParam.size() != NUM_PARAMETERS ) {
                ERROR( "invalid model parameters: invalid number of parameters." );
        }

        S32 NumCytokines =  ( REAL )strtol( v_modelParam[2].c_str(), NULL, 10 );

        PDEInfo pdeInfo;
        GridPhiInfo gridPhiInfo; 
        v_phiPDEInfo.resize( NumCytokines );
 

        for ( S32 cytokineID = 0; cytokineID < NumCytokines; cytokineID++ ) {  
  
            string cytokStrIdx = static_cast<ostringstream*>( &(ostringstream() << cytokineID) )->str();

            pdeInfo.pdeIdx = cytokineID;
            pdeInfo.pdeType = PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR;
            pdeInfo.numLevels = NUM_AMR_LEVELS;
            pdeInfo.ifLevel = NUM_AMR_LEVELS - 1;
            pdeInfo.mgSolveInfo.numPre = 3;/*multigrid parameters */
            pdeInfo.mgSolveInfo.numPost = 3;/*multigrid parameters */
            pdeInfo.mgSolveInfo.numBottom = 3;/*multigrid parameters */
            pdeInfo.mgSolveInfo.vCycle = true;/*multigrid parameters */
            pdeInfo.mgSolveInfo.maxIters = 30;/*multigrid parameters */
            pdeInfo.mgSolveInfo.epsilon = 1e-8;/*multigrid parameters */
            pdeInfo.mgSolveInfo.hang = 1e-6;/*multigrid parameters */
            pdeInfo.mgSolveInfo.normThreshold = 1e-10;/* multigrid parameters */ 
            pdeInfo.numTimeSteps = A_NUM_PDE_TIME_STEPS_PER_STATE_AND_GRID_TIME_STEP;
            pdeInfo.callAdjustRHSTimeDependentLinear = false;
            pdeInfo.v_gridPhiInfo.resize( 1 );
            gridPhiInfo.elemIdx = cytokineID;
            gridPhiInfo.name = "cytokine" + cytokStrIdx ;
            gridPhiInfo.syncMethod = VAR_SYNC_METHOD_DELTA;/* updateIfGridVar */
            gridPhiInfo.aa_bcType[0][0] = BC_TYPE_NEUMANN_CONST;/* dummy */
            gridPhiInfo.aa_bcVal[0][0] = 0.0;/* dummy */
            gridPhiInfo.aa_bcType[0][1] = BC_TYPE_NEUMANN_CONST;/* dummy */
            gridPhiInfo.aa_bcVal[0][1] = 0.0;/* dummy */
            gridPhiInfo.aa_bcType[1][0] = BC_TYPE_NEUMANN_CONST;/* dummy */
            gridPhiInfo.aa_bcVal[1][0] = 0.0;/* dummy */
            gridPhiInfo.aa_bcType[1][1] = BC_TYPE_NEUMANN_CONST;/* dummy */
            gridPhiInfo.aa_bcVal[1][1] = 0.0;/* dummy */
            gridPhiInfo.aa_bcType[2][0] = BC_TYPE_NEUMANN_CONST;
            gridPhiInfo.aa_bcVal[2][0] = 0.0;
            gridPhiInfo.aa_bcType[2][1] = BC_TYPE_NEUMANN_CONST;
            gridPhiInfo.aa_bcVal[2][1] = 0.0;
            gridPhiInfo.errorThresholdVal = GRID_PHI_NORM_THRESHOLD * -1.0;
            gridPhiInfo.warningThresholdVal = GRID_PHI_NORM_THRESHOLD * -1.0;
            gridPhiInfo.setNegToZero = true;
            pdeInfo.v_gridPhiInfo.assign(1,gridPhiInfo);
            v_phiPDEInfo[ cytokineID ] = pdeInfo;
        }

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridModelVarInfo( Vector<IfGridModelVarInfo>& v_ifGridModelRealInfo, Vector<IfGridModelVarInfo>& v_ifGridModelIntInfo ) {
	/* MODEL START */

        Vector<string> v_modelParam = readXMLParameters();
        if ( v_modelParam.size() != NUM_PARAMETERS ) {
                ERROR( "invalid model parameters: invalid number of parameters." );
        }

        S32 NumCytokines =  ( REAL )strtol( v_modelParam[2].c_str(), NULL, 10 );
        IfGridModelVarInfo info;
        v_ifGridModelRealInfo.resize( NumCytokines + NUM_GRID_MODEL_REALS );

        info.name = "agent_vol_ratio";
        info.syncMethod = VAR_SYNC_METHOD_DELTA;/* updateIfGridVar */
        v_ifGridModelRealInfo[GRID_MODEL_REAL_AGENT_VOL_RATIO] = info;

        for ( S32 cytokineID = 0; cytokineID < NumCytokines; cytokineID++ ) {

            string cytokStrIdx = static_cast<ostringstream*>( &(ostringstream() << cytokineID) )->str();

            info.name =  string( cytokStrIdx ) + "_RHS" ;
            info.syncMethod = VAR_SYNC_METHOD_DELTA;/* updateIfGridVar */
            v_ifGridModelRealInfo[ cytokineID + NUM_GRID_MODEL_REALS ] = info;

        }

        v_ifGridModelIntInfo.clear();


	/* MODEL END */

	return;
}

void ModelRoutine::updateRNGInfo( Vector<RNGInfo>& v_rngInfo ) {
	/* MODEL START */


        RNGInfo rngInfo;

        rngInfo.type = RNG_TYPE_UNIFORM;
        rngInfo.param0 = 0.0;
        rngInfo.param1 = 1.0;
        rngInfo.param2 = 0.0;/* dummy */

        v_rngInfo.push_back( rngInfo );  


	/* MODEL END */

	return;
}

void ModelRoutine::updateFileOutputInfo( FileOutputInfo& fileOutputInfo ) {
	/* MODEL START */

        Vector<string> v_modelParam = readXMLParameters();
        if ( v_modelParam.size() != NUM_PARAMETERS ) {
                ERROR( "invalid model parameters: invalid number of parameters." );
        }

        S32 NumCytokines =  ( REAL )strtol( v_modelParam[2].c_str(), NULL, 10 );
        // NUM_CELL_EXTRA_OUTPUT_SCALAR_VARS
        fileOutputInfo.particleOutput = true;
        fileOutputInfo.v_particleExtraOutputScalarVarName.assign( NUM_CELL_EXTRA_OUTPUT_SCALAR_VARS, "");

        fileOutputInfo.v_particleExtraOutputScalarVarName[CELL_EXTRA_OUTPUT_ALLBN1] = "BN1";  
        fileOutputInfo.v_particleExtraOutputScalarVarName[CELL_EXTRA_OUTPUT_ALLBN2] = "BN2";      

        fileOutputInfo.v_particleExtraOutputVectorVarName.clear();

        fileOutputInfo.v_gridPhiOutput.assign( NumCytokines, false  );
        fileOutputInfo.v_gridPhiOutputDivideByKappa.assign( NumCytokines,false );

	/* MODEL END */

	return;
}

void ModelRoutine::updateSummaryOutputInfo( Vector<SummaryOutputInfo>& v_summaryOutputRealInfo, Vector<SummaryOutputInfo>& v_summaryOutputIntInfo ) {
	/* MODEL START */


        Vector<string> v_modelParam = readXMLParameters();
        if ( v_modelParam.size() != NUM_PARAMETERS ) {
                ERROR( "invalid model parameters: invalid number of parameters." );
        }
        S32 NumCytokines =  ( REAL )strtol( v_modelParam[2].c_str(), NULL, 10 );


        SummaryOutputInfo info;
        v_summaryOutputIntInfo.resize( NUM_BN_NETWORKS * MAX_NUM_NODES  );
        v_summaryOutputRealInfo.resize( NUM_GRID_SUMMARY_REALS + NumCytokines  );
        

        info.name = "Number of Cells";
        info.type = SUMMARY_TYPE_SUM;
        v_summaryOutputRealInfo[GRID_SUMMARY_REAL_LIVE_CELLS] = info;

        info.name = "Volumetric Density";
        info.type = SUMMARY_TYPE_MAX;
        v_summaryOutputRealInfo[GRID_SUMMARY_REAL_DENSITY] = info;
  

        for ( S32 cytokineID = 0; cytokineID < NumCytokines; cytokineID++ ) { 
           
            string cytokStrIdx = static_cast<ostringstream*>( &(ostringstream() << cytokineID) )->str();
            info.name = "[" + cytokStrIdx   + "]";
            info.type = SUMMARY_TYPE_AVG;
            v_summaryOutputRealInfo[ NUM_GRID_SUMMARY_REALS + cytokineID ] = info;

        }

        for ( S32 bnid = 0 ;  bnid < NUM_BN_NETWORKS; bnid++ ) { 
            for  ( int i = 0 ;  i < MAX_NUM_NODES ; i++ ) {

               string Idx = static_cast<ostringstream*>( &(ostringstream() << i ) )->str();

               if ( bnid == 0 ) 
                    info.name = "BN_0_" + Idx ;
               else if ( bnid == 1 )
                    info.name = "BN_1_" + Idx ;
               else if ( bnid == 2 )
                    info.name = "BN_2_" + Idx ; 
               else if ( bnid == 3 ) 
                    info.name = "BN_3_" + Idx ;
               else if ( bnid == 4 ) 
                    info.name = "BN_4_" + Idx ;

               info.type = SUMMARY_TYPE_SUM;              
               v_summaryOutputIntInfo[ (bnid*MAX_NUM_NODES ) + i] = info;
            }
        }

	/* MODEL END */

	return;
}

void ModelRoutine::initGlobal( Vector<U8>& v_globalData ) {
	/* MODEL START */
        REAL* p_gamma ;
        REAL* p_phi_off ;
        S32* p_num_cytokines ;

        size_t SizeParam = 2 * sizeof(REAL) + sizeof(S32)  ;

        Vector<string> v_modelParam = readXMLParameters(); 
        if( v_modelParam.size() != NUM_PARAMETERS ) {
                ERROR( "invalid model parameters: invalid number of parameters." );
        }
 
        GAMMA = ( REAL )strtod( v_modelParam[0].c_str(), NULL ); 
        PHI_OFF  = ( REAL ) strtod( v_modelParam[1].c_str(), NULL );
        NUM_CYTOKINES  = ( S32 ) strtol( v_modelParam[2].c_str(), NULL, 10 );

 	//------ 1. Read the first line to get number of cells --------//
        FILE* p_file;
        S32 IniNumberCells = 0;

        p_file = fopen( v_modelParam[5].c_str(), "r" ); //check if the first param is Non-Empty 
        if( p_file == NULL ) {
                ERROR( "invalid model parameters: invalid blocked_grid_points file path. can't open first parameter" );
        }


        S8* p_buf;
        size_t bufSize;
        p_buf = NULL; // if non-NULL, proceed by initializing p_buf and buf_size
        bufSize = 0;

        ssize_t numCharsRead;
        if (( numCharsRead = getline( &p_buf, &bufSize, p_file ) ) != -1 ) { //  p_buf is the extracted entire line
                S8* p_token;
                p_token = strtok( p_buf, " \t\n" );      //split string into tokens
                IniNumberCells = (S32) strtol( p_token, NULL, 10 ); // just get the first token (which is the only number for IninumberCells)
        }else {
                ERROR( "Unable to read number of cells" );
        }
        INI_N_CELLS = IniNumberCells;
 
	// ----- 2. Allocate Memory for Global Data v_globalData and initialize ubInitData and cellInitData to -----------------------------//

        S32 NumberVoxels = 0;
        VIdx ifRegionSize;
        ifRegionSize[0] = Info::getDomainSize(0); //x = 36
        ifRegionSize[1] = Info::getDomainSize(1); //y = 36
        ifRegionSize[2] = Info::getDomainSize(2); //z = 36
        NumberVoxels = ifRegionSize[0] * ifRegionSize[1] * ifRegionSize[2]; // Number of Unit Boxes

        UBInitData* p_ubInitData;
        IniCellData* p_IniCellData;

        v_globalData.resize( SizeParam +  NumberVoxels * sizeof( UBInitData ) + IniNumberCells * sizeof( IniCellData ));//Allocate the memory that will be used for v_globalData 
        p_ubInitData = ( UBInitData* )&( v_globalData[ SizeParam   ] );  // Location of memory where UBInitData starts                           
        p_IniCellData = ( IniCellData* )&( v_globalData[SizeParam + NumberVoxels * sizeof( UBInitData )] );  // Location of memory where IniCellData starts

        for( idx_t i = 0 ; i <  ifRegionSize[0] ; i++ ) {   // Define all voxels to be empty (numCells = 0 , and IdxIniCellData = -1)
                for( idx_t j = 0 ; j < ifRegionSize[1]  ; j++ ) {
                        for( idx_t k = 0 ; k < ifRegionSize[2]  ; k++ ) {
                                UBInitData& ubInitData = p_ubInitData[VIdx::getIdx3DTo1D( i, j, k, ifRegionSize )];
                                ubInitData.numCells = 0;
                                ubInitData.IdxIniCellData  = -1 ;
                        }
                }
        }

        for ( S32 i=0; i < IniNumberCells; i++){                                                        // Define all IniCellData to be 0's and such
                IniCellData& cellInitData = p_IniCellData[i];
                cellInitData.x_offset = 0.0 ;
                cellInitData.y_offset = 0.0 ;
                cellInitData.z_offset = 0.0 ;
                cellInitData.r_size = 0.0 ;
                cellInitData.a_type = 0 ;
                cellInitData.IdxIniCellData  = -1 ;
        }

        // ------------ 3. Read in Cell Information and Store them into ubInitData and cellInitData -------------------//
        S32 count = 0;
        while( (( numCharsRead = getline( &p_buf, &bufSize, p_file ) ) != -1) && ( count < IniNumberCells )  ) { //loop through all the lines after numCells

                // ----- store Voxels and posOffsets based on x, y, z data -------------------------//
                VIdx vIdxOffset;
                VReal posOffset;

                S8* p_token;
                p_token = strtok( p_buf, " \t\n" );
                for ( S32 dim = 0 ; dim < DIMENSION ; dim++ ) { //for-loop tokens for x, y, and z (each line/cell). Defines vIdxOffset and posOffset
                        if( p_token == NULL ) {
                                ERROR( "invalid blocked_grid_points file." );
                        }
                        REAL Position  = ( REAL )strtod( p_token, NULL );
                        vIdxOffset[dim] = ( idx_t ) ( Position/IF_GRID_SPACING) ;
                        posOffset[dim] = Position - (( (REAL)vIdxOffset[dim]*IF_GRID_SPACING ) + 0.5 * IF_GRID_SPACING ) ;

                        if( posOffset[dim] < IF_GRID_SPACING * -0.5 )
                                posOffset[dim] = IF_GRID_SPACING  * -0.5;
                        else if( posOffset[dim] > IF_GRID_SPACING  * 0.5 )
                                posOffset[dim] = IF_GRID_SPACING * 0.5;

                        p_token = strtok( NULL, " \t\n" );

                        if( ( vIdxOffset[dim] < 0 )   ) {
                                ERROR( "invalid blocked_grid_points file." );
                        }
                        else if ( vIdxOffset[dim] >= Info::getDomainSize(dim) ) {
                                ERROR( "invalid blocked_grid_points file." );
                        }
                }

                UBInitData& ubInitData = p_ubInitData[VIdx::getIdx3DTo1D( vIdxOffset, ifRegionSize )]; //Store the voxels.

                IniCellData& cellInitData = p_IniCellData[count];

                cellInitData.x_offset = (REAL) posOffset[0] ;
                cellInitData.y_offset = (REAL) posOffset[1] ;
                cellInitData.z_offset = (REAL)  posOffset[2] ;
	
		// ------------------------ store r_Size ----------------------------------------//

                if( p_token == NULL ) {
                        ERROR( "invalid blocked_grid_points file." );
                }else {
                        cellInitData.r_size  = ( REAL )strtod( p_token, NULL );
                }

                //------------------------reading cell type-------------------------------------//
                p_token = strtok( NULL, " \t\n" );
                if( p_token == NULL ) {
                        ERROR( "invalid blocked_grid_points file." );
                }else {
                        cellInitData.a_type  = strtol( p_token, NULL, 10 ) ;
                        if ( cellInitData.a_type >= NUM_BN_NETWORKS  ) {
                             ERROR( "found : cell type > NUM_CELL_TYPES " );
                        }
                }
                // ------------------------ line id
                cellInitData.line_id = count ;

                // --------------------- end of the line token check --------------------------//
                p_token = strtok( NULL, " \t\n" );
                if( p_token != NULL ) {
                        ERROR( "invalid blocked_grid_points file." );
                }

                // -------- Place CellData id in Voxel at the end of list of cells -----//  
                if ( ubInitData.numCells == 0 ) {
                        ubInitData.IdxIniCellData  = count ;
                }else {
                        S32 nextIdx = ubInitData.IdxIniCellData;
                        if ( nextIdx == -1 ) {
                                ERROR( "invalid blocked_grid_points file." );
                        }

                        for ( S32 i = 1; i < ubInitData.numCells; i++) {
                                if ( nextIdx == -1 ){
                                        ERROR( "invalid blocked_grid_points file." );
                                }
                                IniCellData& cellData = p_IniCellData[ nextIdx ];
                                nextIdx = cellData.IdxIniCellData  ;
                        }

                        IniCellData& cellData = p_IniCellData[ nextIdx ];
                        if ( cellData.IdxIniCellData != -1 ) {
                                ERROR( "invalid blocked_grid_points file." );
                        }
                        cellData.IdxIniCellData = count;
                }
                ubInitData.numCells++ ;
                count++;
        }
        if ( p_buf != NULL ) {
                free( p_buf );
        }
        //cout << "Finished reading in cells.txt. x, y, z, and r initialized in 'v_globalData' via UBIniData and IniCellData." << endl;
        fclose( p_file);

        //****************************** RBN STARTS HERE *******************************/ 
        //              all the read in vectors are stored at the end                   /
        // ----------------- 4. Read in nv.text ----------------------------------------/
        S32 num_bn_networks = 0 ;
        S32  MaxNumGenes  = -1 ;
        Vector<S32> v_numNodes ;   // Store number of genes for each bn 
        Vector<S32> v_num_varf_rows ;   //  
        Vector<S32> v_num_tt_rows ;   // 
        Vector< Vector<S32> > vv_nv ; // Store number of inpus for each gene for each bn
        Vector< Vector<S32> > vv_varf ; // 
        Vector< Vector<S32> > vv_tt ; //
        Vector< Vector<S32> > v_initStates; 

        // ---------------------4. Read in *.nv ---------------------------------------
        string nvfile = v_modelParam[3]  ;
        nvfile.append(".nv") ;
        p_file = fopen( nvfile.c_str(), "r" ); //check if the second param (nv.txt) is Non-Empty 
        if( p_file == NULL ) {
                ERROR( "Can't open *.nv" );
        }else {
                S8* p_buf = NULL; 
                bufSize = 0;
                while( ( numCharsRead = getline( &p_buf, &bufSize, p_file ) ) != -1 ) {
                     Vector<S32> v_nv = readINTvaluesLine( p_buf ) ;
                     v_numNodes.push_back( v_nv.size()) ;
                     vv_nv.push_back( v_nv); 
                }
                if ( p_buf != NULL ) {
                        free (p_buf);
                }
        }
  	fclose(p_file);

        num_bn_networks = (S32)  v_numNodes.size() ;
        // compute maximun number of genes of the BNs included here for clarity
        for ( S32 i = 0; i < num_bn_networks; i ++ ) {
            if ( v_numNodes[i] > MaxNumGenes )
                 MaxNumGenes  =  v_numNodes[i] ; 
        } 
        // compute the num of rows in varf files
        for (S32  i = 0; i < num_bn_networks; i++ ) {
             Vector<S32> v_nv = vv_nv[i] ; 
             S32 max_val = -1 ; 
             for ( S32 j = 0; j < v_numNodes[i] ; j++ ) {
                 if( max_val < v_nv[j] ) 
                     max_val = v_nv[j] ;
             }
             v_num_varf_rows.push_back(max_val) ;
             v_num_tt_rows.push_back( (S32) pow( 2, max_val ) ); //!!!! probably slow 
        }  
       
        NUM_BN_NETWORKS = num_bn_networks ;
        MAX_NUM_NODES = MaxNumGenes;

        // ----------------- 5. Read in Ttable.txt ----------------------------------------/
        string ttfile = v_modelParam[3]   ;
        ttfile.append(".tt") ;
        p_file = fopen( ttfile.c_str(), "r" ); //  
        if( p_file == NULL ) {
                ERROR( "Can't open Ttable.txt" );
        } else {

           S8* p_buf = NULL;  
           bufSize = 0; 
      
           for ( S32 i = 0; i < num_bn_networks; i++ ){
               Vector<S32> v_tt; 
               for (S32 j = 0; j < v_num_tt_rows[i]; j++){ 
               
                   numCharsRead = getline( &p_buf, &bufSize, p_file ); 
                   if ( numCharsRead == -1) 
                        ERROR("Error reading tt file (getline) ")

                   Vector<S32> temp = readINTvaluesLine( p_buf ) ;

                   if ( (S32) temp.size() != v_numNodes[i] )
                        ERROR("Error reading tt file (wrong num. of genes) ")

                   for ( S32 k = 0 ;  k < (S32)  temp.size(); k++ )
                        v_tt.push_back( temp[k] );
               }         
               vv_tt.push_back( v_tt ) ;
           }
           if ( p_buf != NULL ) 
               free (p_buf);
        }
        fclose(p_file);

        // ----------------- 6. Read in varF.txt ---------------------------
        string varffile = v_modelParam[3 ]; 
        varffile.append(".varf")  ;
        p_file = fopen( varffile.c_str(), "r" ); 
        if( p_file == NULL ) {
                ERROR( "Can't open varF.txt" );
        }else {
           S8* p_buf = NULL;
           bufSize = 0;
           for ( S32 i = 0; i < num_bn_networks; i++ ){
               Vector<S32> v_varf ;  // !!! this can be avoided  using resize or reserve ... I guess
               for (S32 j = 0; j < v_num_varf_rows[i]; j++){
                   numCharsRead = getline( &p_buf, &bufSize, p_file );
                   if ( numCharsRead == -1)
                        ERROR("Error reading varf file (getline) ")

                   Vector<S32> temp = readINTvaluesLine( p_buf ) ;
                   if ( (S32)  temp.size() != v_numNodes[i] )
                        ERROR("Error reading varf file (wrong num. of genes) ")
 
                   for ( S32 k = 0 ;  k < (S32) temp.size(); k++ )
                        v_varf.push_back( temp[k] );
               } 
               vv_varf.push_back( v_varf );
           }
           if ( p_buf != NULL )
               free (p_buf);

        }
        fclose(p_file);

        // ----------------- 7. Read Cytokine network  ----------/
        Vector< Vector<S32> >  vv_receptors_net(NUM_BN_NETWORKS,  Vector<S32> (NUM_CYTOKINES,-1));
        Vector< Vector<S32> >  vv_secretion_net(NUM_BN_NETWORKS,  Vector<S32> (NUM_CYTOKINES,-1)); 
        Vector< Vector<REAL> > vv_receptor_threshold(NUM_BN_NETWORKS,  Vector<REAL> (NUM_CYTOKINES, 0.0 ));
        Vector< Vector<REAL> > vv_secretion_rate(NUM_BN_NETWORKS,  Vector<REAL> (NUM_CYTOKINES, 1.0  ));

        p_file = fopen( v_modelParam[4].c_str(), "r" ); 
        if( p_file == NULL ) {
                ERROR( "Can't open initStates.txt" );
        }else {
                S8* p_buf = NULL;
                bufSize = 0;

                S32  cytokineID;
                S32  cellID; 
                S32  geneID;
                REAL rate ;
                
                while( ( numCharsRead = getline( &p_buf, &bufSize, p_file ) ) != -1 )  {

                   
                    S8* p_token = strtok( p_buf, " \t\n" );
                    if (p_token == NULL) {
                         ERROR( "Can't read rector/secretion column in cytokine network file" );
                    }
                    string label = string( p_token );
 
                    p_token = strtok( NULL, " \t\n" );
                    if (p_token == NULL) {
                         ERROR( "Can't read cytokine id column in cytokine network file" );
                    }
                    cytokineID = ( S32 ) strtol( p_token, NULL, 10 );

                    p_token = strtok( NULL, " \t\n" );
                    if (p_token == NULL) {
                         ERROR( "Can't read cell id column in cytokine network file" );
                    }
                    cellID = ( S32 ) strtol( p_token, NULL, 10 );

                    p_token = strtok( NULL, " \t\n" );
                    if (p_token == NULL) {
                         ERROR( "Can't read gene id column in cytokine network file" );
                    }
                    geneID = ( S32 ) strtol( p_token, NULL, 10 );

                    p_token = strtok( NULL, " \t\n" );
                    if (p_token == NULL) {
                         ERROR( "Can't read rate column in cytokine network file" );
                    }
                    rate = ( REAL ) strtod( p_token, NULL );
                    
                    if (( cytokineID >= NUM_CYTOKINES ) || ( cellID >= NUM_BN_NETWORKS ) || ( geneID >= MAX_NUM_NODES ) ) { 
                         ERROR( "Indexes off limits in cytokine network file" ); 
                    }
                    
                    if ( label == "R" )  {
                         vv_receptors_net[cellID][cytokineID] = geneID;
                         vv_receptor_threshold[cellID][cytokineID] = rate;
                    }
                    else if  ( label == "S" ) {
                         vv_secretion_net[cellID][cytokineID] = geneID;
                         vv_secretion_rate[cellID][cytokineID] = rate;
                    }
                }
        }  


        // ----------------- 7. Read in initStates.txt ----------/
        p_file = fopen( v_modelParam[6].c_str(), "r" ); 
        if( p_file == NULL ) {
                ERROR( "Can't open initStates.txt" );
        }else {
                S8* p_buf = NULL; 
                bufSize = 0;
                S32 counter=0;
                while(( ( numCharsRead = getline( &p_buf, &bufSize, p_file ) ) != -1 ) && ( counter < INI_N_CELLS  ) ) {
                     Vector<S32> v_initStatesRow = readINTvaluesLine( p_buf ) ;
                     if ( (S32) v_initStatesRow.size() != MaxNumGenes )  // !!!! This should be improved  
                         ERROR("Error reading Booelean states (Num of colums should be the maximun of the num. of BN genes)");

                     v_initStates.push_back( v_initStatesRow );
                     counter++;
                }

                if ( p_buf != NULL ) {
                        free (p_buf);
                }
        }
        fclose(p_file);

        if ( (S32) v_initStates.size()  <  INI_N_CELLS ) {
                ERROR( " Number of cells in cells.txt grater than that in iniStates.txt " )
        }

	/********************************* RBN ENDS HERE **************************************/

        //  Resize Global data for cell data, and Boolean networks
        size_t CellDataSize = NumberVoxels*sizeof(UBInitData) + INI_N_CELLS*sizeof(IniCellData) + INI_N_CELLS *MaxNumGenes*sizeof( S32 ) ; 
        size_t BNDataSize = 0;
        for ( S32 i = 0; i < num_bn_networks; i++ ) {
            BNDataSize += 3*sizeof(S32); //three values to store sizes of the data 
            BNDataSize += v_numNodes[i]*sizeof(S32) ;  // number of nodes variables per node
            BNDataSize += v_numNodes[i]*v_num_varf_rows[i]*sizeof(S32);  // the inputs ids per node 
            BNDataSize += v_numNodes[i]*v_num_tt_rows[i]*sizeof(S32);  // truth table data
        }
        size_t CytokineNetSize = 2*NUM_BN_NETWORKS*NUM_CYTOKINES*( sizeof(S32) + sizeof(REAL) );
        

        v_globalData.resize( SizeParam + CellDataSize + BNDataSize + CytokineNetSize );

        //Add Initial Cell States at the end of globalData
        S32* p_InitStatesData = ( S32* ) & ( v_globalData[ SizeParam + NumberVoxels * sizeof( UBInitData ) + IniNumberCells * sizeof( IniCellData)  ]);
        for (S32 i = 0 ; i < INI_N_CELLS ; i++ ){ 
              for (S32 j = 0 ; j < MaxNumGenes; j++ ){
                    *( p_InitStatesData + (i*MaxNumGenes + j) ) = v_initStates[i][j];
              }
        }

        //Fill the globalData with cytokine Networks 
        size_t MemorySize = SizeParam + CellDataSize;
        S32* p_CytokineReceptors = ( S32* ) & (  v_globalData[ MemorySize ] ) ;
        MemorySize +=  NUM_BN_NETWORKS * NUM_CYTOKINES * sizeof(S32) ;   
        S32* p_CytokineSecretion = ( S32* ) & (  v_globalData[ MemorySize ] );
        MemorySize +=  NUM_BN_NETWORKS * NUM_CYTOKINES * sizeof(S32)  ;  
        REAL* p_CytokineReceptorsRate = ( REAL* ) & (  v_globalData[ MemorySize ] ) ;
        MemorySize +=  NUM_BN_NETWORKS * NUM_CYTOKINES * sizeof( REAL ) ;   
        REAL* p_CytokineSecretionRate = ( REAL* ) & (  v_globalData[ MemorySize ] ) ;
         
        S32 ccounter = 0 ;
        for ( S32 bnid = 0; bnid < NUM_BN_NETWORKS; bnid++ ) {
            for ( S32 cytokineid = 0; cytokineid < NUM_CYTOKINES; cytokineid++ ) {
                *( p_CytokineReceptors     + ccounter ) = vv_receptors_net[bnid][cytokineid]; 
                *( p_CytokineSecretion     + ccounter ) = vv_secretion_net[bnid][cytokineid];
                *( p_CytokineReceptorsRate + ccounter ) = vv_receptor_threshold[bnid][cytokineid];
                *( p_CytokineSecretionRate + ccounter ) = vv_secretion_rate[bnid][cytokineid];
                ccounter++ ;
            }
        } 


        //Fill the last part of globalData with the information of Boolean Networks
        MemorySize = SizeParam + CellDataSize + CytokineNetSize ;
        for (S32 i = 0 ; i < num_bn_networks; i++ ){
 
             S32* p_BNpointer = ( S32* ) & ( v_globalData[ MemorySize  ]);
              
             S32 counter = 3;
             *( p_BNpointer + 0 ) = v_numNodes[i] ;
             *( p_BNpointer + 1 ) = v_num_varf_rows[i];
             *( p_BNpointer + 2 ) = v_num_tt_rows[i];
           
             for ( S32 j = 0; j < v_numNodes[i]; j++ ) 
                *( p_BNpointer + counter++  ) = vv_nv[i][j] ; /// !!! I dont really need to store nv 
             for ( S32 j = 0; j < v_numNodes[i]*v_num_varf_rows[i]; j++ ) 
                *( p_BNpointer + counter++ ) = vv_varf[i][j] ; 
          
             for ( S32 j = 0; j < v_numNodes[i]*v_num_tt_rows[i] ; j++ ) 
                *( p_BNpointer + counter++ ) = vv_tt[i][j] ; 
             
             MemorySize += counter*sizeof(S32);
          
        }
      

        // Fill memory region of  parameters to global access
        p_gamma = ( REAL* )&( v_globalData[ 0 ] ) ;
        *p_gamma = GAMMA ;

        p_phi_off  = ( REAL* )&( v_globalData[ 1 * sizeof(REAL)   ] ) ;
        *p_phi_off = PHI_OFF ;

        p_num_cytokines = ( S32* )&( v_globalData[ 2 * sizeof(REAL) ] );
        *p_num_cytokines = NUM_CYTOKINES ;         
	/* MODEL END */

	return;
}

void ModelRoutine::init( void ) {

	/* MODEL START */
        const Vector<U8>& v_globalData = Info::getGlobalDataRef();

        REAL* p_gamma  = ( REAL* )&( v_globalData[ 0 ] ) ;
        GAMMA = *p_gamma  ;

        REAL* p_phi_off  = ( REAL* )&( v_globalData[ 1*sizeof(REAL) ]);
        PHI_OFF = *p_phi_off   ;

        S32* p_num_cytokines  = ( S32* )&(  v_globalData[ 2*sizeof(REAL)  ] ) ;
        NUM_CYTOKINES = *p_num_cytokines ;

	/* MODEL END */

	return;
}

void ModelRoutine::term( void ) {
	/* MODEL START */

	/* MODEL END */

	return;
}

void ModelRoutine::setPDEBuffer( const VIdx& startVIdx, const VIdx& regionSize, BOOL& isPDEBuffer ) {
	/* MODEL START */

	isPDEBuffer = false;
	
	/* MODEL END */

	return;
}

void ModelRoutine::setHabitable( const VIdx& vIdx, BOOL& isHabitable ) {
	/* MODEL START */

	isHabitable = true;

	/* MODEL END */

	return;
}


////////////////////////////////////////
//  User defined functions
//////////////////////////////////////////


//Get the Param from the XML file and Parse the strings and store to v_modelParam
static Vector<string> readXMLParameters()  {
        Vector<string> v_modelParam; // This will be returned
        S8* p_modelParams;
        S8* p_param;

        p_modelParams = new S8[Info::getModelParam().size() + 1]; //Set the pointer size. +1 for Null Termination
        strcpy( p_modelParams, Info::getModelParam().c_str() ); //copy the string Param string to p_modelParams

        p_param = strtok( p_modelParams, " \t\n" );
        while( p_param != NULL ) {
                v_modelParam.push_back( string( p_param ) ); //store all the broken down strings to v_modelParam. cells.txt, Ttable.txt, varF.txt, nv.txt, initStates,txt
                p_param = strtok( NULL, " \t\n" );
        }
        delete[] p_modelParams;
        delete[] p_param;
      
        return v_modelParam;
}

// !!!!! USE a template for S32 and REAL types
// Read S32 values from a single line stored in p_buf,
static Vector<S32>  readINTvaluesLine( S8* p_buf )  {
        Vector<S32> v_Values;
        S8* p_token = strtok( p_buf, " \t\n" );
        while (p_token != NULL) {
             v_Values.push_back( strtol( p_token, NULL, 10 ) );
             p_token = strtok( NULL, " \t\n" );
        }
         
        if ( v_Values.empty() ) {
             ERROR("Can not read a line (Function readINTvaluesLine)   ");
        }
        
        return v_Values;
} 



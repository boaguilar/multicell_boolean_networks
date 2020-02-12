/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __MY_DEFINE_H__
#define __MY_DEFINE_H__

#include "biocellion.h"

/* define constants to be used inside model functions */

/* MODEL START */
extern S32 INI_N_CELLS;
extern S32 NUM_BN_NETWORKS;
extern S32 MAX_NUM_NODES; 

extern REAL GAMMA;      // Degradation rate  [1 / second ]
extern REAL R_ON;       // Ratio of secretion rate of ON cells, relative to OFF 
extern REAL THRESH_ON;  // Treshold concentration for activaction 
extern REAL THRESH_SHORT_DIST; // Treshold concentration for deactivation
extern REAL PHI_OFF;    // Concentration for OFF


typedef enum _cell_type_e {
        CELL_TYPE_PCC,  // Pancreatic Cancer cell ;
        CELL_TYPE_PSC,  // Pancreatic Stellate cell 
        CELL_TYPE_CD4,  // T cell CD4
        CELL_TYPE_TAM,  // Tumor associated macrophages
        CELL_TYPE_CD8,  // T cell CD8
        NUM_CELL_TYPES
} cell_type_e;

typedef enum _alive_cell_model_real_e {
        CELL_MODEL_REAL_LINE_ID,
        CELL_NUM_MODEL_REALS
} alive_cell_model_real_e;

const S32 MAX_BOOL_NODES = 41;
typedef enum _bn_type_e {
        BN_TYPE_PCCPHENO,
        BN_TYPE_PSCPHENO,
        BN_TYPE_CD4PHENO,
        BN_TYPE_TAMPHENO,
        BN_TYPE_CD8PHENO,
        NUM_BN_TYPES
} bn_type_e;

typedef enum _model_rng_type_e {
        MODEL_RNG_UNIFORM,
        NUM_MODEL_RNGS
} model_rng_type_e;

const S32 V_CELL_BN_ID[NUM_CELL_TYPES] = {BN_TYPE_PCCPHENO, BN_TYPE_PSCPHENO, BN_TYPE_CD4PHENO, BN_TYPE_TAMPHENO, BN_TYPE_CD8PHENO};  // BN index for four cell types

// Diffusible molecules
typedef enum _grid_phi_e {
        GRID_PHI_VEGF,
        GRID_PHI_EGF,
        GRID_PHI_bFGF,
        GRID_PHI_PDGFBB,
        GRID_PHI_TGFb1,
        GRID_PHI_IFNgamma,
        GRID_PHI_IL10,
        GRID_PHI_IL6,
        GRID_PHI_IL4,
        GRID_PHI_TNFalpha,
        GRID_PHI_IL23,
        GRID_PHI_IL12,
        GRID_PHI_IL2,
        GRID_PHI_TOXIC,
        GRID_PHI_PDL1,
        GRID_PHI_AG,
        NUM_GRID_PHIS 
} grid_phi_e;
// Variables mantained in each grid cell
typedef enum _grid_model_real_e {
        GRID_MODEL_REAL_VEGF_RHS,
        GRID_MODEL_REAL_EGF_RHS,
        GRID_MODEL_REAL_bFGF_RHS,
        GRID_MODEL_REAL_PDGFBB_RHS,
        GRID_MODEL_REAL_TGFb1_RHS,
        GRID_MODEL_REAL_IFNgamma_RHS,
        GRID_MODEL_REAL_IL10_RHS,
        GRID_MODEL_REAL_IL6_RHS,
        GRID_MODEL_REAL_IL4_RHS,
        GRID_MODEL_REAL_TNFalpha_RHS,
        GRID_MODEL_REAL_IL23_RHS,
        GRID_MODEL_REAL_IL12_RHS,
        GRID_MODEL_REAL_IL2_RHS,
        GRID_MODEL_REAL_TOXIC_RHS,
        GRID_MODEL_REAL_PDL1_RHS,
        GRID_MODEL_REAL_AG_RHS,
        GRID_MODEL_REAL_AGENT_VOL_RATIO,
        NUM_GRID_MODEL_REALS
} grid_model_real_e;


typedef enum _grid_summary_real_e {
        GRID_SUMMARY_REAL_VEGF,
        GRID_SUMMARY_REAL_EGF,
        GRID_SUMMARY_REAL_bFGF,
        GRID_SUMMARY_REAL_PDGFBB,
        GRID_SUMMARY_REAL_TGFb1,
        GRID_SUMMARY_REAL_IFNgamma,
        GRID_SUMMARY_REAL_IL10,
        GRID_SUMMARY_REAL_IL6,
        GRID_SUMMARY_REAL_IL4,
        GRID_SUMMARY_REAL_TNFalpha,
        GRID_SUMMARY_REAL_IL23,
        GRID_SUMMARY_REAL_IL12,
        GRID_SUMMARY_REAL_IL2,                  
        GRID_SUMMARY_REAL_TOXIC,                  
        GRID_SUMMARY_REAL_PDL1,
        GRID_SUMMARY_REAL_AG, 
        GRID_SUMMARY_REAL_QUI,
        GRID_SUMMARY_REAL_PRO,
        GRID_SUMMARY_REAL_APO,
        GRID_SUMMARY_REAL_AUT,
        GRID_SUMMARY_REAL_DENSITY,
        GRID_SUMMARY_REAL_LIVE_CELLS,
        NUM_GRID_SUMMARY_REALS
} grid_summary_real_e;

typedef enum _cell_extra_output_scalar_var_e {
        CELL_EXTRA_OUTPUT_STATE,
        CELL_EXTRA_OUTPUT_ID,
        CELL_EXTRA_OUTPUT_ALLBN1,
        CELL_EXTRA_OUTPUT_ALLBN2,
        NUM_CELL_EXTRA_OUTPUT_SCALAR_VARS
} cell_extra_output_scalar_var_e;


struct IniCellData {
        REAL x_offset;
        REAL y_offset;
        REAL z_offset;
        REAL r_size;
        S32 a_type;
        S32 line_id;
        S32 IdxIniCellData;
};

class UBInitData {
        public:
                S32 numCells;
                S32 IdxIniCellData;
};

// General simulation parameters
const REAL IF_GRID_SPACING = 20.0;
const REAL BASELINE_TIME_STEP_DURATION = 1.0;
const S32 NUM_STATE_AND_GRID_TIME_STEPS_PER_BASELINE = 1;
const REAL GENE_PERTURBATION = 0.01;
const REAL BN_PERTURBATION = 0.0956 ; // ( 1 -(1-q)^n ) for q = 0.01

// PARAMETERS FOR CELL COMUNICATION
const REAL DECAY_RATE  = 0.2;
const REAL DIFFUSION_COEFF  =  5.0 ;// um^2 / sec
const REAL LAMBDA = SQRT( DIFFUSION_COEFF  / DECAY_RATE  ) ;
const REAL INI_RAD = 10.0; 
const REAL SECRETION_RATE_ON = 5.0 ;
const REAL SECRETION_RATE_OFF  = 1.0 ;
const REAL C_R_OFF = 0.00460363 ; 
const REAL PHI_THRESHOLD = 0.0736 ; 
const REAL PHI_SHORT_DIST = 0.00197212;   
const REAL GAMMA_SHORT_DIST  = 0.0055555556;


// Threshold value for activation boolean inputesi               0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
const S32 AA_BOOLNET_SECRETION[NUM_BN_TYPES][NUM_GRID_PHIS] = {{30,31,32,33,34,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,38},
                                                               {24,-1,25,26,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
                                                               {-1,-1,-1,-1,-1,32,31,29,30,-1,-1,-1,-1,-1,-1,-1},
                                                               {21,-1,-1,22,20,-1,19,15,-1,18,17,16,-1,-1,-1,-1},
                                                               {-1,-1,-1,-1,-1,28,30,-1,-1,27,-1,-1,26,29,-1,-1}};

// 
const S32 AA_BOOLNET_INPUTS[NUM_GRID_PHIS][NUM_BN_TYPES] = {{-1, 3,-1,-1,-1}, //VEGF 0
                                                            { 2, 4,-1,-1,-1}, //EGF  1
                                                            { 3, 5,-1,-1,-1}, //bFGF 2
                                                            {-1, 6,-1,-1,-1}, //PDGFBB 3
                                                            { 4, 7,10,-1, 5}, //TGFb1  4
                                                            {-1, 2, 9, 1,-1}, //IFNgamma 5
                                                            {-1,-1, 7, 2, 3}, //IL10 6
                                                            {-1,-1, 6,-1, 4}, //IL6 7
                                                            {-1,-1, 8, 3,-1}, //IL4 8 
                                                            {-1, 1,-1,-1,-1}, //TNFalpha 9
                                                            {-1,-1, 0,-1,-1}, //IL23 10
                                                            {-1,-1, 2,-1, 2}, //IL12 11
                                                            {-1,-1, 1,-1,-1}, //IL2 12
                                                            {39,-1,-1,-1,-1}, //TOXIC 13
                                                            {-1,-1,-1,-1, 1}, //PDL1 14
                                                            {-1,-1, 5, 0, 0}};//AG  15


const S32 NUM_OUTPUT_PCCPHENO = 3 ;
const S32 NUM_OUTPUT_PSCPHENO = 4 ;
const S32 NUM_OUTPUT_CD4PHENO = 18 ;
const S32 NUM_OUTPUT_TAMPHENO = 10 ;
const S32 NUM_OUTPUT_CD8PHENO =  2; 
const S32 A_OUTPUT_GENES_PCC[NUM_OUTPUT_PCCPHENO] = { 35, 36, 37  };
const S32 A_OUTPUT_GENES_PSC[NUM_OUTPUT_PSCPHENO] = { 28,29,30,31 };
const S32 A_OUTPUT_GENES_CD4[NUM_OUTPUT_CD4PHENO] = { 32,9,23,21, 24,31,7,30,8,17,16, 28,29,6,14,22,17, 20 };
const S32 A_OUTPUT_GENES_TAM[NUM_OUTPUT_TAMPHENO] = { 4,5,6,7,8,9,10,11,12,13 };
const S32 A_OUTPUT_GENES_CD8[NUM_OUTPUT_CD8PHENO] = { 24, 25};

// Parameters for PDE solvers
const REAL A_NUM_PDE_TIME_STEPS_PER_STATE_AND_GRID_TIME_STEP[NUM_GRID_PHIS] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
const S32 NUM_AMR_LEVELS = 1;
const REAL GRID_PHI_NORM_THRESHOLD = 1e-10 ; 
const S32 SPHERE_UB_VOL_OVLP_RATIO_MAX_LEVEL = 1;
/* MODEL END */




#endif/* #ifndef __MY_DEFINE_H__ */


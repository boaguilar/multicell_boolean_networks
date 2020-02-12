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
extern S32 NUM_CYTOKINES;
extern REAL GAMMA;      // Degradation rate  [1 / second ]
extern REAL PHI_OFF;    // Concentration for OFF

const S32 NUM_PARAMETERS = 7; // The parameteres are specified in the xml file 

typedef enum _cell_type_e {
        CELL_TYPE_PCC,  // Pancreatic Cancer cell ;
        CELL_TYPE_PSC,  // Pancreatic Stellate cell 
        CELL_TYPE_CD4,  // T cell CD4
        CELL_TYPE_TAM,  // Tumor associated macrophages
        CELL_TYPE_CD8,  // T cell CD8
        MAXNUM_CELL_TYPES
} cell_type_e;

typedef enum _alive_cell_model_real_e {
        CELL_MODEL_REAL_LINE_ID,
        CELL_NUM_MODEL_REALS
} alive_cell_model_real_e;

//const S32 MAX_BOOL_NODES = 44;
typedef enum _bn_type_e {
        BN_TYPE_PCCPHENO,
        BN_TYPE_PSCPHENO,
        BN_TYPE_CD4PHENO,
        BN_TYPE_TAMPHENO,
        BN_TYPE_CD8PHENO,
        NUM_BN_TYPES
} bn_type_e;

typedef enum _grid_model_real_e {
        GRID_MODEL_REAL_AGENT_VOL_RATIO,
        NUM_GRID_MODEL_REALS
} grid_model_real_e;


typedef enum _model_rng_type_e {
        MODEL_RNG_UNIFORM,
        NUM_MODEL_RNGS
} model_rng_type_e;

const S32 V_CELL_BN_ID[MAXNUM_CELL_TYPES] = {BN_TYPE_PCCPHENO, BN_TYPE_PSCPHENO, BN_TYPE_CD4PHENO, BN_TYPE_TAMPHENO, BN_TYPE_CD8PHENO};  // BN index for four cell types


typedef enum _grid_summary_real_e {
        GRID_SUMMARY_REAL_DENSITY,
        GRID_SUMMARY_REAL_LIVE_CELLS,
        NUM_GRID_SUMMARY_REALS
} grid_summary_real_e;

typedef enum _cell_extra_output_scalar_var_e {
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


// Parameters for PDE solvers
// Same parameteres will be used for all cytokines
const REAL A_NUM_PDE_TIME_STEPS_PER_STATE_AND_GRID_TIME_STEP = 1;
const S32 NUM_AMR_LEVELS = 1;
const REAL GRID_PHI_NORM_THRESHOLD = 1e-10 ; 
const S32 SPHERE_UB_VOL_OVLP_RATIO_MAX_LEVEL = 1;
/* MODEL END */

#endif/* #ifndef __MY_DEFINE_H__ */


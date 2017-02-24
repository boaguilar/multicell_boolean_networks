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

typedef enum _cell_type_e {
        CELL_TYPE_PCC,  // Pancreatic Cancer cell ; 
        CELL_TYPE_PSC,  // Pancreatic Stellate cell
        NUM_CELL_TYPES
} cell_type_e;

typedef enum _bn_type_e {
        BN_TYPE_PCCPHENO,
        NUM_BN_TYPES
} bn_type_e;

const S32  V_CELL_BN_ID[NUM_CELL_TYPES] = {BN_TYPE_PCCPHENO, -1 } ;  // PCC celss PCCPHENO, PSC cells no bn


typedef enum _grid_summary_real_e {
        GRID_SUMMARY_REAL_LIVE_CELLS,
        NUM_GRID_SUMMARY_REALS
} grid_summary_real_e;

typedef enum _cell_extra_output_scalar_var_e {
        CELL_EXTRA_OUTPUT_STATE,
        CELL_EXTRA_OUTPUT_PHENO,
        NUM_CELL_EXTRA_OUTPUT_SCALAR_VARS
} cell_extra_output_scalar_var_e;


struct IniCellData {
        REAL x_offset;
        REAL y_offset;
        REAL z_offset;
        REAL r_size;
        S32 a_type;
        S32 IdxIniCellData;
};

class UBInitData {
        public:
                S32 numCells;
                S32 IdxIniCellData;
};

const REAL IF_GRID_SPACING = 8.0;
const REAL BASELINE_TIME_STEP_DURATION = 1.0;
const S32 NUM_STATE_AND_GRID_TIME_STEPS_PER_BASELINE = 1;

/* MODEL END */

#endif/* #ifndef __MY_DEFINE_H__ */


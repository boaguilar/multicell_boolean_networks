/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __EXT_TYPE_H__
#define __EXT_TYPE_H__

#include <float.h>
#include <limits.h>

#include "base_type.h"
#include "vector_type.h"
#include "rng.h"

/* range */

#define agentType_t U16/* up to 2^16 - 1 agent types */
#define junctionEndType_t U16/* up to 2^16 - 1 junction end types */

#define agentId_t S64

#define partMpAgentIdx_t U32/* up to 2^32 - 1 multi-particle agents per partition */
#define ubAgentIdx_t U16/* up to 2^16 - 1 particles in a unit box */

#define subAgentIdx_t U16/* up to 2^16 sub-elements per multi-particle agent */

#define INVALID_IDX -1
#define INVALID_ID -1
#define INVALID_TYPE -1

/* enumerations */

typedef enum _domain_bdry_type_e {
	DOMAIN_BDRY_TYPE_NONPERIODIC_HARD_WALL,/* agents cannot pass the boundary, Dirichlet or Neumann boundary condition for PDEs */
	DOMAIN_BDRY_TYPE_PERIODIC/* agents passing the boundary will appear in the opposite side, periodic boundary condition for PDEs */
} domain_bdry_type_e;

typedef enum _pde_buffer_bdry_type_e {
	PDE_BUFFER_BDRY_TYPE_HARD_WALL/* agents cannot pass the boundary, if DOMAIN_BDRY_TYPE_PERIODIC is selected and the partition in the oppsite side is a PDE buffer, agents cannot pass the domain boundary */
} pde_buffer_bdry_type_e;

typedef enum _pde_type_e {
	PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR,
	PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR,
	PDE_TYPE_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING,/* use time-splitting to solve diffusion and reaction separately */
	PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_LINEAR,
	PDE_TYPE_ADVECTION_REACTION_DIFFUSION_TIME_DEPENDENT_SPLITTING,/* use time-splitting to solve advection-diffusion and reaction separately */
	PDE_TYPE_INCOMPRESSIBLE_NAVIER_STOKES_TIME_DEPENDENT,
	PDE_TYPE_INVALID
} pde_type_e;

typedef enum _bc_type_e {
	BC_TYPE_DIRICHLET_CONST,
	BC_TYPE_DIRICHLET_MODEL,
	BC_TYPE_NEUMANN_CONST,
	BC_TYPE_NEUMANN_MODEL,
	BC_TYPE_INVALID
} bc_type_e;

typedef enum _vel_bc_type_e {
	VEL_BC_TYPE_INFLOW_CONST,
	VEL_BC_TYPE_INFLOW_MODEL,
	VEL_BC_TYPE_OUTFLOW,
	VEL_BC_TYPE_HARD_WALL,
	VEL_BC_TYPE_INVALID
} vel_bc_type_e;

typedef enum _ode_stiff_e {
	ODE_STIFF_NORMAL,
	ODE_STIFF_HIGH
} ode_stiff_e;

typedef enum _agent_class_e {
#if HAS_MPAGENT
	AGENT_CLASS_MPAGENT,
#endif
#if HAS_SPAGENT
	AGENT_CLASS_SPAGENT,
#endif
#if HAS_MPAGENT
	AGENT_CLASS_SUBAGENT,
#endif
	NUM_AGENT_CLASSES
} agent_class_e;

typedef enum _sync_method_e {
	SYNC_METHOD_PER_ATTR,
	SYNC_METHOD_TRANSACTIONAL
} sync_method_e;

typedef enum _var_sync_method_e {
	VAR_SYNC_METHOD_OVERWRITE,
	VAR_SYNC_METHOD_DELTA,
	VAR_SYNC_METHOD_MIN,
	VAR_SYNC_METHOD_MAX,
} var_sync_method_e;

typedef enum _if_grid_var_type_e {
	IF_GRID_VAR_TYPE_VEL,
	IF_GRID_VAR_TYPE_PHI,
	IF_GRID_VAR_TYPE_MODEL_REAL,
	IF_GRID_VAR_TYPE_MODEL_INT
} if_grid_var_type_e;

typedef enum _sim_init_type_e {
	SIM_INIT_TYPE_CODE,
	SIM_INIT_TYPE_BINARY,
	SIM_INIT_TYPE_INVALID
} sim_init_type_e;

typedef enum _particle_output_type_e {
	PARTICLE_OUTPUT_TYPE_PVTP,
	PARTICLE_OUTPUT_TYPE_INVALID
} particle_output_type_e;

typedef enum _grid_output_type_e {
	GRID_OUTPUT_TYPE_VTHB,
	GRID_OUTPUT_TYPE_INVALID
} grid_output_type_e;

typedef enum _summary_type_e {
	SUMMARY_TYPE_SUM,
	SUMMARY_TYPE_AVG,
	SUMMARY_TYPE_MIN,
	SUMMARY_TYPE_MAX,
	NUM_SUMMARY_TYPES
} summary_type_e;

/* class definitions */

class ODENetInfo {
public:
	S32 numVars;

	ode_stiff_e stiff;
	REAL h;/* default step size relative to the duration of (agent-)state-grid time step */
	REAL hm;/* minimum step size relative to the duration of (agent-)state-grid time step */
	REAL epsilon;/* relative error tolerance=epsilon, this code cannot ensure the requested accuracy if epsilon is smaller than -9 */
	REAL threshold;/* if the absolute value of solution is larger than threshold, the relative error is controlled, otherwise absolute error (epsilon * threshold) is controlled */

	REAL errorThresholdVal;/* this value should be non-positive, aborts the program if ODE solve results have a value smaller than errorThresholdVal, set this to REAL_MAX * -1.0 to turn off */
	REAL warningThresholdVal;/* this value should be non-positive and equal to or larger than errorThresholdVal, prints warning if ODE solve results have a value larger than errorThresholdVal but smaller than warningThresholdVal, set this to REAL_MAX * -1.0 to turn off */
	BOOL setNegToZero;/* if true negative values (equal to or larger than the errorThresholdVal) are reset to 0.0, set this to false to turn off */

public:
	inline ODENetInfo( void ) __attribute__( ( always_inline ) );
	inline ~ODENetInfo( void ) __attribute__( ( always_inline ) );
};

class TimeStepInfo {
public:
	REAL durationBaselineTimeStep;
	S32 numStateAndGridTimeStepsPerBaseline;

public:
	inline TimeStepInfo( void ) __attribute__( ( always_inline ) );
	inline ~TimeStepInfo( void ) __attribute__( ( always_inline ) );
};

class OptModelRoutineCallInfo {
public:
	S32 numComputeMechIntrctIters;
	S32 numUpdateIfGridVarPreStateAndGridStepIters;
	S32 numUpdateIfGridVarPostStateAndGridStepIters;

public:
	inline OptModelRoutineCallInfo( void ) __attribute__( ( always_inline ) );
	inline ~OptModelRoutineCallInfo( void ) __attribute__( ( always_inline ) );
};

class MechModelVarInfo {
public:
	var_sync_method_e syncMethod;

public:
	inline MechModelVarInfo( void ) __attribute__( ( always_inline ) );
	inline ~MechModelVarInfo( void ) __attribute__( ( always_inline ) );
};

class MpAgentInfo {
public:
	S32 numBoolVars;
	S32 numStateModelReals;
	S32 numStateModelInts;
	Vector<ODENetInfo> v_odeNetInfo;

public:
	inline MpAgentInfo( void ) __attribute__( ( always_inline ) );
	inline ~MpAgentInfo( void ) __attribute__( ( always_inline ) );
};

class SubAgentInfo {
public:
	REAL dMax;
	S32 numStateModelReals;
	S32 numStateModelInts;
	Vector<MechModelVarInfo> v_mechIntrctModelRealInfo;
	Vector<MechModelVarInfo> v_mechIntrctModelIntInfo;

public:
	inline SubAgentInfo( void ) __attribute__( ( always_inline ) );
	inline ~SubAgentInfo( void ) __attribute__( ( always_inline ) );
};

class SpAgentInfo {
public:
	REAL dMax;
	S32 numBoolVars;
	S32 numStateModelReals;
	S32 numStateModelInts;
	Vector<MechModelVarInfo> v_mechIntrctModelRealInfo;
	Vector<MechModelVarInfo> v_mechIntrctModelIntInfo;
	Vector<ODENetInfo> v_odeNetInfo;

public:
	inline SpAgentInfo( void ) __attribute__( ( always_inline ) );
	inline ~SpAgentInfo( void ) __attribute__( ( always_inline ) );
};

class JunctionEndInfo {
public:
	S32 numModelReals;
	S32 numModelInts;

public:
	inline JunctionEndInfo( void ) __attribute__( ( always_inline ) );
	inline ~JunctionEndInfo( void ) __attribute__( ( always_inline ) );
};

class GridVelInfo {
public:
	REAL kinematicViscosity;

	vel_bc_type_e aa_bcType[DIMENSION][2];/* ignored if the boundary is periodic */
	VReal aa_bcVal[DIMENSION][2];/* ignored if the boundary is periodic */

public:
	inline GridVelInfo( void ) __attribute__( ( always_inline ) );
	inline ~GridVelInfo( void ) __attribute__( ( always_inline ) );
};

class GridPhiInfo {
public:
	S32 elemIdx;/* should be unqiue and smaller than the total number of extracellular molecule types updated by solving PDEs */
	std::string name;
	var_sync_method_e syncMethod;/* updateIfGridVar */

	bc_type_e aa_bcType[DIMENSION][2];/* ignored if the boundary is periodic */
	REAL aa_bcVal[DIMENSION][2];/* ignored if the boundary is periodic */

	REAL errorThresholdVal;/* this value should be non-positive, aborts the program if PDE solve results have a value smaller than errorThresholdVal, set this to REAL_MAX * -1.0 to turn off */
	REAL warningThresholdVal;/* this value should be non-positive and equal to or larger than errorThresholdVal, prints warning if PDE solve results have a value larger than errorThresholdVal but smaller than warningThresholdVal, set this to REAL_MAX * -1.0 to turn off */
	BOOL setNegToZero;/* if true negative values (equal to or larger than the errorThresholdVal) are reset to 0.0, set this to false to turn off */

public:
	inline GridPhiInfo( void ) __attribute__( ( always_inline ) );
	inline ~GridPhiInfo( void ) __attribute__( ( always_inline ) );
};

class MGSolveInfo {
public:
	S32 numPre;
	S32 numPost;
	S32 numBottom;
	BOOL vCycle;/* set to true to use "V" cycle, set to false to use "W" cycle */
	S32 maxIters;
	REAL epsilon;
	REAL hang;
	REAL normThreshold;

public:
	inline MGSolveInfo( void ) __attribute__( ( always_inline ) );
	inline ~MGSolveInfo( void ) __attribute__( ( always_inline ) );
};

class AdvectionInfo {
public:
	REAL courantNumber;/* dt = min(diffusion step size, courantNumber * dx / maximum wave speed) */

public:
	inline AdvectionInfo( void ) __attribute__( ( always_inline ) );
	inline ~AdvectionInfo( void ) __attribute__( ( always_inline ) );
};

class SplittingInfo {
public:
	Vector<S32> v_diffusionTimeSteps;/* per single PDE time step */

	ode_stiff_e odeStiff;
	REAL odeH;/* default step size relative to the duration of a single PDE time step */
	REAL odeHm;/* minimum step size relative to the duration of a single PDE time step */
	REAL odeEpsilon;/* relative error tolerance=epsilon, this code cannot ensure the requested accuracy if epsilon is smaller than -9 */
	REAL odeThreshold;/* if the absolute value of solution is larger than threshold, the relative error is controlled, otherwise absolute error (epsilon * threshold) is controlled */

public:
	inline SplittingInfo( void ) __attribute__( ( always_inline ) );
	inline ~SplittingInfo( void ) __attribute__( ( always_inline ) );
};

class PDEInfo {
public:
	S32 pdeIdx;

	pde_type_e pdeType;

	S32 numLevels;/* level 0 is the coarsest level, level numLevels - 1 is the finest level */
	S32 ifLevel;
	Vector<S32> v_tagExpansionSize;/* v_tagExpansionSize[0] should be always 0 */

	S32 numTimeSteps;/* valid only for time-dependent PDEs */

	BOOL callAdjustRHSTimeDependentLinear;/* valid only for time-dependent linear PDEs */

	MGSolveInfo mgSolveInfo;
	AdvectionInfo advectionInfo;/* valid only for advection PDEs */
	SplittingInfo splittingInfo;/* valid only for time-splitting PDEs */

	GridVelInfo gridVelInfo;/* valid only when pdeType == PDE_TYPE_INCOMPRESSIBLE_NAVIER_STOKES_TIME_DEPENDENT */

	Vector<GridPhiInfo> v_gridPhiInfo;/* invalid if pdeType == PDE_TYPE_INCOMPRESSIBLE_NAVIER_STOKES_TIME_DEPENDENT */

public:
	inline PDEInfo( void ) __attribute__( ( always_inline ) );
	inline ~PDEInfo( void ) __attribute__( ( always_inline ) );
};

class IfGridModelVarInfo {
public:
	std::string name;
	var_sync_method_e syncMethod;/* updateIfGridVar */

public:
	inline IfGridModelVarInfo( void ) __attribute__( ( always_inline ) );
	inline ~IfGridModelVarInfo( void ) __attribute__( ( always_inline ) );
};

class RNGInfo {
public:
	rng_type_e type;

	REAL param0;/* min for uniform, avg for gaussian, beta for exponential, alpha for gamma */
	REAL param1;/* max for unifrom, sd for gaussian, disp for exponential, beta for gamma */
	REAL param2;/* only for gamma, disp */

	/* exponential pdf = (1/beta)*e^(-x/beta) */
	/* gamma pdf=(beta^alpha)*(x^(alpha-1))*(e^(-beta*x))/Gamma(alpha) */

public:
	inline RNGInfo( void ) __attribute__( ( always_inline ) );
	inline ~RNGInfo( void ) __attribute__( ( always_inline ) );
};

class FileOutputInfo {
public:
	BOOL particleOutput;
	Vector<std::string> v_particleExtraOutputScalarVarName;
	Vector<std::string> v_particleExtraOutputVectorVarName;

	Vector<BOOL> v_gridPhiOutput;
	Vector<BOOL> v_gridPhiOutputDivideByKappa;

public:
	inline FileOutputInfo( void ) __attribute__( ( always_inline ) );
	inline ~FileOutputInfo( void ) __attribute__( ( always_inline ) );
};

class SummaryOutputInfo {
public:
	std::string name;
	summary_type_e type;
};

class ODESolverData {
public:
	double h;/* step size */
};

inline ODENetInfo::ODENetInfo( void ) {
	this->numVars = 0;
	this->stiff = ODE_STIFF_NORMAL;
	this->h = 0.0;
	this->hm = 0.0;
	this->epsilon = 1e-6;/* default value */
	this->threshold = 1e-19;/* default value */
	this->errorThresholdVal = 0.0;
	this->warningThresholdVal = 0.0;
	this->setNegToZero = false;
}

inline ODENetInfo::~ODENetInfo( void ) {
	/* nothing to do */
}

inline TimeStepInfo::TimeStepInfo( void ) {
	this->durationBaselineTimeStep = 0.0;
	this->numStateAndGridTimeStepsPerBaseline = 0;
}

inline TimeStepInfo::~TimeStepInfo( void ) {
	/* nothing to do */
}

inline OptModelRoutineCallInfo::OptModelRoutineCallInfo( void ) {
	this->numComputeMechIntrctIters = 0;
	this->numUpdateIfGridVarPreStateAndGridStepIters = 0;
	this->numUpdateIfGridVarPostStateAndGridStepIters = 0;
}

inline OptModelRoutineCallInfo::~OptModelRoutineCallInfo( void ) {
	/* nothing to do */
}

inline MechModelVarInfo::MechModelVarInfo( void ) {
	this->syncMethod = VAR_SYNC_METHOD_OVERWRITE;
}

inline MechModelVarInfo::~MechModelVarInfo( void ) {
	/* nothing to do */
}

inline MpAgentInfo::MpAgentInfo( void ) {
	this->numBoolVars = 0;
	this->numStateModelReals = 0;
	this->numStateModelInts = 0;
}

inline MpAgentInfo::~MpAgentInfo( void ) {
	/* nothing to do */
}

inline SubAgentInfo::SubAgentInfo( void ) {
	this->dMax = 0.0;
	this->numStateModelReals = 0;
	this->numStateModelInts = 0;
}

inline SubAgentInfo::~SubAgentInfo( void ) {
	/* nothing to do */
}

inline SpAgentInfo::SpAgentInfo( void ) {
	this->dMax = 0.0;
	this->numBoolVars = 0;
	this-> numStateModelReals = 0;
	this-> numStateModelInts = 0;
}

inline SpAgentInfo::~SpAgentInfo( void ) {
	/* nothing to do */
}

inline JunctionEndInfo::JunctionEndInfo( void ) {
	this->numModelReals = 0;
	this->numModelInts = 0;
}

inline JunctionEndInfo::~JunctionEndInfo( void ) {
	/* nothing to do */
}

inline GridVelInfo::GridVelInfo( void ) {
	this->kinematicViscosity = 0.0;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->aa_bcType[dim][0] = VEL_BC_TYPE_HARD_WALL;
		this->aa_bcType[dim][1] = VEL_BC_TYPE_HARD_WALL;
		this->aa_bcVal[dim][0] = VReal::ZERO;
		this->aa_bcVal[dim][1] = VReal::ZERO;
	}
}

inline GridVelInfo::~GridVelInfo( void ) {
	/* nothing to do */
}

inline GridPhiInfo::GridPhiInfo( void ) {
	this->elemIdx = 0;
	this->name = "";
	this->syncMethod = VAR_SYNC_METHOD_OVERWRITE;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		this->aa_bcType[dim][0] = BC_TYPE_DIRICHLET_CONST;
		this->aa_bcType[dim][1] = BC_TYPE_DIRICHLET_CONST;
		this->aa_bcVal[dim][0] = 0.0;
		this->aa_bcVal[dim][1] = 0.0;
	}
	this->errorThresholdVal = 0.0;
	this->warningThresholdVal = 0.0;
	this->setNegToZero = false;
}

inline GridPhiInfo::~GridPhiInfo( void ) {
	/* nothing to do */
}

inline MGSolveInfo::MGSolveInfo( void ) {
	this->numPre = 3;/* default value */
	this->numPost = 3;/* default value */
	this->numBottom = 3;/* default value */
	this->vCycle = true;/* default value */
	this->maxIters = 30;/* default value */
	this->epsilon = 1e-6;/* default value */
	this->hang = 1e-10;/* default value */
	this->normThreshold = 1e-25;/* default value */
};

inline MGSolveInfo::~MGSolveInfo( void ) {
	/* nothing to do */
}

inline AdvectionInfo::AdvectionInfo( void ) {
	this->courantNumber = 0.0;
};

inline AdvectionInfo::~AdvectionInfo( void ) {
	/* nothing to do */
}

inline SplittingInfo::SplittingInfo( void ) {
	this->odeStiff = ODE_STIFF_NORMAL;
	this->odeH = 0.0;
	this->odeHm = 0.0;
	this->odeEpsilon = 1e-6;/* default value */
	this->odeThreshold = 1e-19;/* default value */
}

inline SplittingInfo::~SplittingInfo( void ) {
	/* nothing to do */
}

inline PDEInfo::PDEInfo( void ) {
	this->pdeIdx = INVALID_IDX;
	this->pdeType = PDE_TYPE_REACTION_DIFFUSION_STEADY_STATE_LINEAR;
	this->numLevels = 0;
	this->ifLevel = 0;
	this->numTimeSteps = 0;
	this->callAdjustRHSTimeDependentLinear = false;
}

inline PDEInfo::~PDEInfo( void ) {
	/* nothing to do */
}

inline IfGridModelVarInfo::IfGridModelVarInfo( void ) {
	this->name = "";
	this->syncMethod = VAR_SYNC_METHOD_OVERWRITE;
}

inline IfGridModelVarInfo::~IfGridModelVarInfo( void ) {
	/* nothing to do */
}

inline RNGInfo::RNGInfo( void ) {
	this->type = RNG_TYPE_UNIFORM;
	this->param0 = 0.0;
	this->param1 = 0.0;
	this->param2 = 0.0;
}

inline RNGInfo::~RNGInfo( void ) {
	/* nothing to do */
}

inline FileOutputInfo::FileOutputInfo( void ) {
	this->particleOutput = false;
}

inline FileOutputInfo::~FileOutputInfo( void ) {
	/* nothing to do */
}

#endif/* #ifndef __EXT_TYPE_H__ */


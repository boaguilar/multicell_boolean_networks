/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __BIOCELLION_H__
#define __BIOCELLION_H__

#if ( ( DIMENSION != 2 ) && ( DIMENSION != 3 ) )
#error DIMENSION should be 2 or 3
#endif
#if ( ( REAL_IS_FLOAT != 0 ) && ( REAL_IS_FLOAT != 1 ) )
#error REAL_IS_FLOAT should be 0 or 1
#endif
#if ( ( HAS_MPAGENT != 0 ) && ( HAS_MPAGENT != 1 ) )
#error HAS_MPAGENT should be 0 or 1
#endif
#if ( ( HAS_SPAGENT != 0 ) && ( HAS_SPAGENT != 1 ) )
#error HAS_SPAGENT should be 0 or 1
#endif
#if ( ( HAS_MPAGENT == 0 ) && ( HAS_SPAGENT == 0 ) )
#error at least one of HAS_MPAGENT and HAS_SPAGENT should be 1
#endif

#if ( THIS_IS_LIBMODEL == 0 )
#if ( ( USE_DIST_MEM_PAR != 0 ) && ( USE_DIST_MEM_PAR != 1 ) )
#error USE_DIST_MEM_PAR should be 0 or 1
#endif
#endif

#include "base_type.h"
#include "check.h"
#include "report.h"
#include "vector_type.h"
#include "dim_type.h"
#include "ext_type.h"
#include "box_type.h"
#include "rng.h"
#include "info.h"
#include "agent_class.h"
#include "env_class.h"
#include "util.h"

#if ( THIS_IS_LIBMODEL == 0 )
#include "my_thread.h"
#endif

#endif/* #ifndef __BIOCELLION_H__ */


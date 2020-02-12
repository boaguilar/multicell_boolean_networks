/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __RNG_H__
#define __RNG_H__

#include <string>

#include "base_type.h"

/* random number generator */

typedef enum _rng_type_e {
	RNG_TYPE_UNIFORM,
	RNG_TYPE_GAUSSIAN,
	RNG_TYPE_EXPONENTIAL,
	RNG_TYPE_GAMMA,
	RNG_TYPE_INVALID
} rng_type_e;

class RNG {
public:
	RNG();
	~RNG();

	void initUniform( const REAL min, const REAL max );
	void initGaussian( const REAL avg, const REAL sd );
	void initExponential( const REAL beta, const REAL disp );
	void initGamma( const REAL alpha, const REAL beta, const REAL disp );
	void term( void );
	REAL rand( void );

private:
	static const S32 BUFFER_SIZE = 8192;

	rng_type_e type;
	void* p_stream;

	/* valid only when type == RNG_TYPE_UNIFORM */

	REAL min;
	REAL max;

	/* valid only when type == RNG_TYPE_GAUSSIAN */

	REAL avg;
	REAL sd;

	/* valid only when type == RNG_TYPE_EXPONENTIAL(or GAMMA) */

	REAL alpha;/* valid only when type == RNG_TYPE_GAMMA */
	REAL beta;
	REAL disp;

	/* buffer for random numbers */

	REAL* p_rands;
	S32 bufOffset;

	void gen( void );
};

#endif/* #ifndef __RNG_H__ */


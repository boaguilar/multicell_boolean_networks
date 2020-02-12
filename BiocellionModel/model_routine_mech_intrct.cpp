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
void ModelRoutine::initJunctionSpAgent( const VIdx& vIdx0, const SpAgent& spAgent0, const VIdx& vIdx1, const SpAgent& spAgent1, const VReal& dir/* unit direction vector from spAgent1 to spAgent0 */, const REAL& dist, BOOL& link, JunctionEnd& end0/* dummy if link == false */, JunctionEnd& end1/* dummy if link == false */
) {
	/* MODEL START */

	link = false;
        

	/* MODEL END */

	return;
}

void ModelRoutine::computeMechIntrctSpAgent( const S32 iter, const VIdx& vIdx0, const SpAgent& spAgent0, const UBEnv& ubEnv0, const VIdx& vIdx1, const SpAgent& spAgent1, const UBEnv& ubEnv1, const VReal& dir/* unit direction vector from spAgent1 to spAgent0 */, const REAL& dist, MechIntrctData& mechIntrctData0, MechIntrctData& mechIntrctData1, BOOL& link, JunctionEnd& end0/* dummy if link == false */, JunctionEnd& end1/* dummy if link == false */, BOOL& unlink ) {
	/* MODEL START */

	//if (Info::getCurBaselineTimeStep() > 0 ){
		
	//	Vector <S32> v_spAgent0;
       // 	Vector <S32> v_spAgent1;
        //	v_spAgent0 = spAgent0.state.getModelIntArray();
        //	v_spAgent1 = spAgent1.state.getModelIntArray();
	
		//cout << "In mech: v_spAgent0[WG]: " << v_spAgent0[WG] << " v_spAgent0[HH]: " << v_spAgent0[HH] << " v_spAgent0[hh]: " << v_spAgent0[hh] << " v_spAgent1[WG]: " << v_spAgent1[WG] << " v_spAgent1[HH]: " << v_spAgent1[HH] << " v_spAgent1[hh]: " << v_spAgent1[hh] << " spagent0: <" << vIdx0[0] << ", " << vIdx0[1] << ", " << vIdx0[2] << "> " << "spagent1: <" << vIdx1[0] << ", " << vIdx1[1] << ", " << vIdx1[2] << "> " << endl;

        	//mechIntrctData0.setModelInt( 0, v_spAgent1[WG]);
        	//mechIntrctData1.setModelInt( 0, v_spAgent0[WG]);

        	//mechIntrctData0.setModelInt( 1, v_spAgent1[HH]);
        	//mechIntrctData1.setModelInt( 1, v_spAgent0[HH]);

        	//mechIntrctData0.setModelInt( 2, v_spAgent1[hh]);
        	//mechIntrctData1.setModelInt( 2, v_spAgent0[hh]);
	
        	link = false;
        	unlink = false;
	
//	}
	/* MODEL END */

	return;
}
#endif


#include <float.h>

#include "biocellion.h"
#include "model_if.h"

#include "model_routine.h"

using namespace std;

#if HAS_MPAGENT
void ModelIf::initJunctionSubAgent( const VIdx& vIdx0, const MpAgent& mpAgent0, const SubAgent& subAgent0, const VIdx& vIdx1, const MpAgent& mpAgent1, const SubAgent& subAgent1, const VReal& dir, const REAL& dist, BOOL& link, JunctionEnd& end0, JunctionEnd& end1 ) {
	( void )vIdx0;
	( void )mpAgent0;
	( void )subAgent0;
	( void )vIdx1;
	( void )mpAgent1;
	( void )subAgent1;
	( void )dir;
	( void )dist;
	( void )link;
	( void )end0;
	( void )end1;

	ERROR( "unimplemented." );

	return;
}

void ModelIf::computeMechIntrctSubAgent( const S32 iter, const VIdx& vIdx0, const MpAgent& mpAgent0, const SubAgent& subAgent0, const UBEnv& ubEnv0, const VIdx& vIdx1, const MpAgent& mpAgent1, const SubAgent& subAgent1, const UBEnv& ubEnv1, const VReal& dir, const REAL& dist, MechIntrctData& mechIntrctData0, MechIntrctData& mechIntrctData1, BOOL& link, JunctionEnd& end0, JunctionEnd& end1, BOOL& unlink ) {
	( void )iter;
	( void )vIdx0;
	( void )mpAgent0;
	( void )subAgent0;
	( void )vIdx1;
	( void )mpAgent1;
	( void )subAgent1;
	( void )dir;
	( void )dist;
	( void )link;
	( void )mechIntrctData0;
	( void )mechIntrctData1;
	( void )link;
	( void )end0;
	( void )end1;
	( void )unlink;

	ERROR( "unimplemented." );

	return;
}
#endif

#if HAS_SPAGENT
void ModelIf::initJunctionSpAgent( const VIdx& vIdx0, const SpAgent& spAgent0, const VIdx& vIdx1, const SpAgent& spAgent1, const VReal& dir, const REAL& dist, BOOL& link, JunctionEnd& end0, JunctionEnd& end1 ) {
	CHECK( spAgent0.state.getRadius() + spAgent1.state.getRadius() > 0.0 );

	ModelRoutine::initJunctionSpAgent( vIdx0, spAgent0, vIdx1, spAgent1, dir, dist, link, end0, end1 );

	return;
}

void ModelIf::computeMechIntrctSpAgent( const S32 iter, const VIdx& vIdx0, const SpAgent& spAgent0, const UBEnv& ubEnv0, const VIdx& vIdx1, const SpAgent& spAgent1, const UBEnv& ubEnv1, const VReal& dir, const REAL& dist, MechIntrctData& mechIntrctData0, MechIntrctData& mechIntrctData1, BOOL& link, JunctionEnd& end0, JunctionEnd& end1, BOOL& unlink ) {
	link = false;
	unlink = false;

	ModelRoutine::computeMechIntrctSpAgent( iter, vIdx0, spAgent0, ubEnv0, vIdx1, spAgent1, ubEnv1, dir, dist, mechIntrctData0, mechIntrctData1, link, end0, end1, unlink );

	CHECK( ( link == false ) || ( unlink == false ) );/* cannot link and unlink at the same time */

	return;
}
#endif

#if ( ( HAS_MPAGENT == 1 ) && ( HAS_SPAGENT == 1 ) )
void ModelIf::initJunctionSubAgentSpAgent( const VIdx& vIdx0, const MpAgent& mpAgent, const SubAgent& subAgent, const VIdx& vIdx1, const SpAgent& spAgent, const VReal& dir, const REAL& dist, BOOL& link, JunctionEnd& end0, JunctionEnd& end1 ) {
	( void )vIdx0;
	( void )mpAgent;
	( void )subAgent;
	( void )vIdx1;
	( void )spAgent;
	( void )dir;
	( void )dist;
	( void )link;
	( void )end0;
	( void )end1;

	ERROR( "unimplemented." );

	return;
}

void ModelIf::computeMechIntrctSubAgentSpAgent( const S32 iter, const VIdx& vIdx0, const MpAgent& mpAgent, const SubAgent& subAgent, const UBEnv& ubEnv0, const VIdx& vIdx1, const SpAgent& spAgent, const UBEnv& ubEnv1, const VReal& dir, const REAL& dist, MechIntrctData& mechIntrctData0, MechIntrctData& mechIntrctData1, BOOL& link, JunctionEnd& end0, JunctionEnd& end1, BOOL& unlink ) {
	( void )iter;
	( void )vIdx0;
	( void )mpAgent;
	( void )subAgent;
	( void )vIdx1;
	( void )spAgent;
	( void )ubEnv0;
	( void )ubEnv1;
	( void )dir;
	( void )dist;
	( void )mechIntrctData0;
	( void )mechIntrctData1;
	( void )link;
	( void )end0;
	( void )end1;
	( void )unlink;

	ERROR( "unimplemented." );

	return;
}
#endif


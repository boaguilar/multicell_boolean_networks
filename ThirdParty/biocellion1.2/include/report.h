/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __REPORT_H__
#define __REPORT_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "base_type.h"

class Report {
	static std::ofstream outputFileStream;

public:
	static void init( void );
	static void term( void );
	static void check( const std::string fileName, const S32 lineNum, const std::string expression, const BOOL isTrue );
	static void output( const S32 minVerbosity, const std::string msg );
	static void warning( const std::string msg );
	static void error( const std::string fileName, const S32 lineNum, const std::string msg );
};

#define OUTPUT( minVerbosity, msg ) {\
	std::stringstream outputTmpStream;\
	outputTmpStream << msg;\
	Report::output( ( minVerbosity ), outputTmpStream.str() );\
}

#define WARNING( msg ) {\
	std::stringstream warningTmpStream;\
	warningTmpStream << msg;\
	Report::warning( warningTmpStream.str() );\
}

#define ERROR( msg ) {\
	std::stringstream errorTmpStream;\
	errorTmpStream << msg;\
	Report::error( __FILE__, __LINE__, errorTmpStream.str() );\
}

#endif/* #ifndef __REPORT_H__ */


/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __BOX_TYPE_H__
#define __BOX_TYPE_H__

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>

#include "base_type.h"
#include "dim_type.h"

template <class T>
class IfGridBoxData {
public:
#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
	inline IfGridBoxData( void ) __attribute__( ( always_inline ) );
	inline ~IfGridBoxData( void ) __attribute__( ( always_inline ) );

	inline void init( const VIdx& startVIdx, const VIdx& regionSize, T* p_vals ) __attribute__( ( always_inline ) );
#endif

	inline T get( const VIdx& vIdx ) const __attribute__( ( always_inline ) );
	inline void set( const VIdx& vIdx, const T val ) __attribute__( ( always_inline ) );

	inline VIdx getSmallEnd( void ) const __attribute__( ( always_inline ) );
	inline VIdx size( void ) const __attribute__( ( always_inline ) );
	inline idx_t size( const S32 dim ) const __attribute__( ( always_inline ) );

private:
	VIdx startVIdx;
	VIdx regionSize;
	T* p_vals;
};

#if ( THIS_IS_LIBMODEL == 0 )/* not for model routines */
template <class T>
inline IfGridBoxData<T>::IfGridBoxData( void ) {
	this->startVIdx = VIdx::ZERO;
	this->regionSize = VIdx::ZERO;
	this->p_vals = NULL;
}

template <class T>
inline IfGridBoxData<T>::~IfGridBoxData( void ) {
	/* nothing to do */
}

template <class T>
inline void IfGridBoxData<T>::init( const VIdx& startVIdx, const VIdx& regionSize, T* p_vals ) {
	this->startVIdx = startVIdx;
	this->regionSize = regionSize;
	this->p_vals = p_vals;
	return;
}
#endif

template <class T>
inline T IfGridBoxData<T>::get( const VIdx& vIdx ) const {
	CHECK( vIdx >= this->startVIdx );
	CHECK( vIdx < ( this->startVIdx + this->regionSize ) );
	return this->p_vals[VIdx::getIdx3DTo1D( vIdx - this->startVIdx, this->regionSize )];
}

template <class T>
inline void IfGridBoxData<T>::set( const VIdx& vIdx, const T val ) {
	CHECK( vIdx >= this->startVIdx );
	CHECK( vIdx < ( this->startVIdx + this->regionSize ) );
	this->p_vals[VIdx::getIdx3DTo1D( vIdx - this->startVIdx, this->regionSize )] = val;
	return;
}

template <class T>
inline VIdx IfGridBoxData<T>::getSmallEnd( void ) const {
	return this->startVIdx;
}

template <class T>
inline VIdx IfGridBoxData<T>::size( void ) const {
	return this->regionSize;
}

template <class T>
inline idx_t IfGridBoxData<T>::size( const S32 dim ) const {
	return this->regionSize[dim];
}

#endif/* #ifndef __BOX_TYPE_H__ */


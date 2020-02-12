/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

#ifndef __VECTOR_TYPE_H__
#define __VECTOR_TYPE_H__

#include <vector>

#include "base_type.h"

template <class T>
class Vector {
public:
	inline Vector( void ) __attribute( ( always_inline ) );
	inline explicit Vector( const std::size_t n, const T& val = T() ) __attribute( ( always_inline ) );
	template <class InputIterator>
	inline Vector( InputIterator first, InputIterator last ) __attribute( ( always_inline ) );
	inline Vector( const Vector<T>& v_other ) __attribute( ( always_inline ) );
	inline ~Vector( void ) __attribute( ( always_inline ) );

	template <class InputIterator>
	inline void assign( InputIterator first, InputIterator last ) __attribute( ( always_inline ) );

	inline void assign( const std::size_t n, const T& val ) __attribute( ( always_inline ) );

	inline T& back( void ) __attribute( ( always_inline ) );
	inline const T& back( void ) const __attribute( ( always_inline ) );

	inline typename std::vector<T>::iterator begin( void ) __attribute( ( always_inline ) );
	inline typename std::vector<T>::const_iterator begin( void ) const __attribute( ( always_inline ) );

	inline void clear( void ) __attribute( ( always_inline ) );

	inline BOOL empty( void ) const __attribute( ( always_inline ) );

	inline typename std::vector<T>::iterator end( void ) __attribute( ( always_inline ) );
	inline typename std::vector<T>::const_iterator end( void ) const __attribute( ( always_inline ) );

	inline T& front( void ) __attribute( ( always_inline ) );
	inline const T& front( void ) const __attribute( ( always_inline ) );

	inline typename std::vector<T>::iterator insert( typename std::vector<T>::iterator pos, const T& val ) __attribute( ( always_inline ) );
	inline void insert( typename std::vector<T>::iterator pos, const std::size_t n, const T& val ) __attribute( ( always_inline ) );
	template <class InputIterator>
	inline void insert( typename std::vector<T>::iterator pos, InputIterator first, InputIterator last ) __attribute( ( always_inline ) );

	inline typename std::vector<T>::iterator erase( typename std::vector<T>::iterator pos ) __attribute( ( always_inline ) );
	inline typename std::vector<T>::iterator erase( typename std::vector<T>::iterator first, typename std::vector<T>::iterator last ) __attribute( ( always_inline ) );

	inline Vector<T>& operator=( const Vector<T> v_other ) __attribute( ( always_inline ) );

	inline T& operator[]( const std::size_t idx ) __attribute( ( always_inline ) );
	inline const T& operator[]( const std::size_t idx ) const __attribute( ( always_inline ) );

	inline void push_back( const T& val ) __attribute( ( always_inline ) );

	inline void resize( const std::size_t n, const T& val = T() ) __attribute( ( always_inline ) );

	inline std::size_t size( void ) const __attribute( ( always_inline ) );

private:
	std::vector<T> v_val;
};

template <class T>
inline Vector<T>::Vector( void ) {
	/* nothing to do */
}

template <class T>
inline Vector<T>::Vector( const std::size_t n, const T& val ) {
	this->v_val.assign( n, val );
}

template <class T>
template <class InputIterator>
inline Vector<T>::Vector( InputIterator first, InputIterator last ) {
	this->v_val.assign( first, last );
}

template <class T>
inline Vector<T>::Vector( const Vector<T>& v_other ) {
	this->v_val = v_other.v_val;
}

template <class T>
inline Vector<T>::~Vector( void ) {
	/* nothing to do */
}

template <class T>
template <class InputIterator>
inline void Vector<T>::assign( InputIterator first, InputIterator last ) {
	this->v_val.assign( first, last );
	return;
}

template <class T>
inline void Vector<T>::assign( const std::size_t n, const T& val ) {
	this->v_val.assign( n, val );
	return;
}

template <class T>
inline T& Vector<T>::back( void ) {
	return this->v_val.back();
}

template <class T>
inline const T& Vector<T>::back( void ) const {
	return this->v_val.back();
}

template <class T>
inline typename std::vector<T>::iterator Vector<T>::begin( void ) {
	return this->v_val.begin();
}

template <class T>
inline typename std::vector<T>::const_iterator Vector<T>::begin( void ) const {
	return this->v_val.begin();
}

template <class T>
inline void Vector<T>::clear( void ) {
	this->v_val.clear();
	return;
}

template <class T>
inline BOOL Vector<T>::empty( void ) const {
	return ( BOOL )( this->v_val.empty() );
}

template <class T>
inline typename std::vector<T>::iterator Vector<T>::end( void ) {
	return this->v_val.end();
}

template <class T>
inline typename std::vector<T>::const_iterator Vector<T>::end( void ) const {
	return this->v_val.end();
}

template <class T>
inline T& Vector<T>::front( void ) {
	return this->v_val.front();
}

template <class T>
inline const T& Vector<T>::front( void ) const {
	return this->v_val.front();
}

template <class T>
inline typename std::vector<T>::iterator Vector<T>::insert( typename std::vector<T>::iterator pos, const T& val ) {
	return this->v_val.insert( pos, val );
}

template <class T>
inline void Vector<T>::insert( typename std::vector<T>::iterator pos, const std::size_t n, const T& val ) {
	this->v_val.insert( pos, n, val );
	return;
}

template <class T>
inline typename std::vector<T>::iterator Vector<T>::erase( typename std::vector<T>::iterator pos ) {
	return this->v_val.erase( pos );
}

template <class T>
inline typename std::vector<T>::iterator Vector<T>::erase( typename std::vector<T>::iterator first, typename std::vector<T>::iterator last ) {
	return this->v_val.erase( first, last );
}

template <class T>
template <class InputIterator>
inline void Vector<T>::insert( typename std::vector<T>::iterator pos, InputIterator first, InputIterator last ) {
	this->v_val.insert( pos, first, last );
	return;
}

template <class T>
inline Vector<T>& Vector<T>::operator=( const Vector<T> v_other ) {
	this->v_val = v_other.v_val;
	return *this;
}

template <class T>
inline T& Vector<T>::operator[]( const std::size_t idx ) {
	CHECK( idx < this->v_val.size() );
	return this->v_val[idx];
}

template <class T>
inline const T& Vector<T>::operator[]( const std::size_t idx ) const {
	CHECK( idx < this->v_val.size() );
	return this->v_val[idx];
}

template <class T>
inline void Vector<T>::push_back( const T& val ) {
	this->v_val.push_back( val );
	return;
}

template <class T>
inline void Vector<T>::resize( const std::size_t n, const T& val ) {
	this->v_val.resize( n, val );
	return;
}

template <class T>
inline std::size_t Vector<T>::size( void ) const {
	return this->v_val.size();
}

#endif/* #ifndef __VECTOR_TYPE_H__ */


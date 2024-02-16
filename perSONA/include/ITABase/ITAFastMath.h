/*
 * ----------------------------------------------------------------
 *
 *		ITA core libs
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 *				    ____  __________  _______
 *				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 *				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 * ----------------------------------------------------------------
 *
 */

#ifndef INCLUDE_WATCHER_ITA_FAST_MATH
#define INCLUDE_WATCHER_ITA_FAST_MATH

#include <ITABaseDefinitions.h>
#include <string>

void ITA_BASE_API fm_init( );
unsigned int ITA_BASE_API fm_flags( );
std::string ITA_BASE_API fm_flags_str( );
ITA_BASE_API float* fm_falloc( unsigned int len, bool zeroinit );
void ITA_BASE_API fm_free( float* ptr );
void ITA_BASE_API fm_set( float* buf, float value, unsigned int count );
void ITA_BASE_API fm_zero( float* buf, unsigned int count );
void ITA_BASE_API fm_copy( float* dest, const float* src, unsigned int count );
void ITA_BASE_API fm_add( float* dest, const float* summand, unsigned int count );
void ITA_BASE_API fm_sub( float* dest, const float* src, unsigned int count );
void ITA_BASE_API fm_mul( float* dest, float factor, unsigned int count );
void ITA_BASE_API fm_cmul( float* dest, const float* factor, unsigned int count );
void ITA_BASE_API fm_cmul_x( float* dest, const float* factor1, const float* factor2, unsigned int count );
void ITA_BASE_API fm_cdiv( float* dest, const float* div, unsigned int count );
void ITA_BASE_API fm_cmul_f32( float* dest, const float* src1, const float* src2, int count );
void ITA_BASE_API fm_cmuladd_f32( float* srcdest, const float* src1, const float* src2, int count );

#endif // INCLUDE_WATCHER_ITA_FAST_MATH

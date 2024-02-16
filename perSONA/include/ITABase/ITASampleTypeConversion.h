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

#ifndef INCLUDE_WATCHER_ITA_SAMPLE_TYPE_CONVERSION
#define INCLUDE_WATCHER_ITA_SAMPLE_TYPE_CONVERSION

// ITABase
#include <ITABaseDefinitions.h>
#include <stddef.h>

//! Converts signed integer 16-Bit -> single precision floating point (32-Bit)
void ITA_BASE_API stc_sint16_to_float( float* dest, const short* src, size_t count, int input_stride = 1, int output_stride = 1 );

//! Converts signed integer 24-Bit -> single precision floating point (32-Bit)
void ITA_BASE_API stc_sint24_to_float( float* dest, const void* src, size_t count, int input_stride = 1, int output_stride = 1 );

//! Converts signed integer 32-Bit -> single precision floating point (32-Bit)
void ITA_BASE_API stc_sint32_to_float( float* dest, const int* src, size_t count, int input_stride = 1, int output_stride = 1 );

//! Converts double precision floating point (64-Bit) -> single precision floating point (32-Bit)
void ITA_BASE_API stc_double_to_float( float* dest, const double* src, size_t count, int input_stride = 1, int output_stride = 1 );

//! Converts single precision floating point (32-Bit) -> signed integer 16-Bit
void ITA_BASE_API stc_float_to_sint16( short* dest, const float* src, size_t count, int input_stride = 1, int output_stride = 1 );

//! Converts single precision floating point (32-Bit) -> signed integer 32-Bit
void ITA_BASE_API stc_float_to_sint32( int* dest, const float* src, size_t count, int input_stride = 1, int output_stride = 1 );

//! Converts single precision floating point (32-Bit) -> double precision floating point (64-Bit)
void ITA_BASE_API stc_float_to_double( double* dest, const float* src, size_t count, int input_stride = 1, int output_stride = 1 );

#endif // INCLUDE_WATCHER_ITA_SAMPLE_TYPE_CONVERSION

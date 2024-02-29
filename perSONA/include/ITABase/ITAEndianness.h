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

#ifndef INCLUDE_WATCHER_ITA_ENDIANNESS
#define INCLUDE_WATCHER_ITA_ENDIANNESS

// ITABase
#include <ITABaseDefinitions.h>
#include <stddef.h>

//! Literals for Endianness
enum ITA_BASE_API
{
	ITA_LITTLE_ENDIAN = 0,
	ITA_BIG_ENDIAN    = 1
};

int ITA_BASE_API GetEndianness( );

/**
 * Byte-Swapping functions, swaping order of bytes to convert between endianness
 */

//! Byte-order swap for 2-Byte (16-Bit) fields
void ITA_BASE_API byteswap_2byte( void* src, size_t count );

//! Byte-order swap for 4-Byte (32-Bit) fields
void ITA_BASE_API byteswap_4byte( void* src, size_t count );

//! Byte-order swap for 8-Byte (64-Bit) fields
void ITA_BASE_API byteswap_8byte( void* src, size_t count );

//! Byte-order swap for 16-Byte (128-Bit) fields
void ITA_BASE_API byteswap_16byte( void* src, size_t count );

/**
 * Endianness-Converter
 */

//! Little endian -> System endianness for 2-Byte (16-Bit) fields
ITA_BASE_API extern void ( *le2se_2byte )( void* src, size_t count );

//! Little endian -> System endianness for 4-Byte (32-Bit) fields
ITA_BASE_API extern void ( *le2se_4byte )( void* src, size_t count );

//! Little endian -> System endianness for 8-Byte (64-Bit) fields
ITA_BASE_API extern void ( *le2se_8byte )( void* src, size_t count );

//! Little endian -> System endianness for 16-Byte (128-Bit) fields
ITA_BASE_API extern void ( *le2se_16byte )( void* src, size_t count );

//! Big endian -> System endianness for 2-Byte (16-Bit) fields
ITA_BASE_API extern void ( *be2se_2byte )( void* src, size_t count );

//! Big endian -> System endianness f�r 4-Byte (32-Bit) fields
ITA_BASE_API extern void ( *be2se_4byte )( void* src, size_t count );

//! Big endian -> System endianness f�r 8-Byte (64-Bit) fields
ITA_BASE_API extern void ( *be2se_8byte )( void* src, size_t count );

//! Big endian -> System endianness f�r 16-Byte (128-Bit) fields
ITA_BASE_API extern void ( *be2se_16byte )( void* src, size_t count );

#endif // INCLUDE_WATCHER_ITA_ENDIANNESS

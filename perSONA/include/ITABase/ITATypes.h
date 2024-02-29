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

#ifndef INCLUDE_WATCHER_ITA_TYPES
#define INCLUDE_WATCHER_ITA_TYPES

#include <ITABaseDefinitions.h>
#include <ITATypes.h>
#include <string>

//! Quantization type
enum struct ITAQuantization
{
	ITA_UNKNOWN_QUANTIZATION,
	ITA_INT16,
	ITA_INT20,
	ITA_INT24,
	ITA_INT32,
	ITA_FLOAT,
	ITA_DOUBLE
};

//! Return quantization as human readible string
ITA_BASE_API std::string toString( ITAQuantization eQuantization );

//! Domain type
enum struct ITADomain
{
	ITA_UNKNOWN_DOMAIN,
	ITA_TIME_DOMAIN,
	ITA_FREQUENCY_DOMAIN,
	ITA_SPHERICAL_HARMONICS_DOMAIN,
};

//! Return domain as human readible string
ITA_BASE_API std::string toString( ITADomain eDomain );

#ifdef WIN32
// Define necessary typedef from stdint.h for Microsoft compilers before Visual C++ 2010
#	if _MSC_VER < 1600

typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

#	else
#		include <stdint.h>
#	endif

#else // UNIX

#	include <stdint.h>

#endif // WIN32 & UNIX

#ifndef NULL
#	define NULL 0
#endif

#endif // INCLUDE_WATCHER_ITA_TYPES

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

#ifndef INCLUDE_WATCHER_ITA_AUDIOFILE_COMMON
#define INCLUDE_WATCHER_ITA_AUDIOFILE_COMMON

#include <ITABaseDefinitions.h>
#include <ITATypes.h>
#include <string>

struct ITA_BASE_API ITAAudiofileProperties
{
	inline ITAAudiofileProperties( )
	{
		eQuantization = ITAQuantization::ITA_FLOAT;
		eDomain       = ITADomain::ITA_TIME_DOMAIN;
		iChannels     = -1;
		dSampleRate   = 44100.0f;
		iLength       = -1;
	};

	inline ~ITAAudiofileProperties( ) { };

	ITAQuantization eQuantization;
	ITADomain eDomain;
	int iChannels;
	double dSampleRate;
	int iLength;
	std::string sComment;
};

//! Print audio file properties to console
ITA_BASE_API void print( const ITAAudiofileProperties& props );

#endif // INCLUDE_WATCHER_ITA_AUDIOFILE_COMMON

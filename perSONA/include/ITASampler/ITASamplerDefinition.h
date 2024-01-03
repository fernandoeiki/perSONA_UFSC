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

#ifndef INCLUDE_WATCHER_ITA_SAMPLER_DEFINITIONS
#define INCLUDE_WATCHER_ITA_SAMPLER_DEFINITIONS

#if( defined WIN32 ) && !( defined ITA_SAMPLER_STATIC )
#	ifdef ITA_SAMPLER_EXPORT
#		define ITA_SAMPLER_API __declspec( dllexport )
#	else
#		define ITA_SAMPLER_API __declspec( dllimport )
#	endif
#else
#	define ITA_SAMPLER_API
#endif

#endif // INCLUDE_WATCHER_ITA_SAMPLER_DEFINITIONS

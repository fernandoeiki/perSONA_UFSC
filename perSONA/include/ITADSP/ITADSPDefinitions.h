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

#ifndef INCLUDE_WATCHER_ITA_DSP_DEFINITIONS
#define INCLUDE_WATCHER_ITA_DSP_DEFINITIONS

#if( defined WIN32 ) && !( defined ITA_DSP_STATIC )
#	ifdef ITA_DSP_EXPORT
#		define ITA_DSP_API __declspec( dllexport )
#	else
#		define ITA_DSP_API __declspec( dllimport )
#	endif
#else
#	define ITA_DSP_API
#endif

#endif // INCLUDE_WATCHER_ITA_DSP_DEFINITIONS

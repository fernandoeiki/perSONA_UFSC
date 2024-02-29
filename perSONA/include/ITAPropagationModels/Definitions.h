/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
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

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_DEFINITIONS
#define INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_DEFINITIONS

#if( defined WIN32 ) && !( defined ITA_PROPAGATION_MODELS_STATIC )
#	ifdef ITA_PROPAGATION_MODELS_EXPORT
#		define ITA_PROPAGATION_MODELS_API __declspec( dllexport )
#	else
#		define ITA_PROPAGATION_MODELS_API __declspec( dllimport )
#	endif
#else
#	define ITA_PROPAGATION_MODELS_API
#endif

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_DEFINITIONS

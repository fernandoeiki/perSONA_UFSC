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


#ifndef INCLUDE_WATCHER_ITA_GEO_DEFINITIONS
#define INCLUDE_WATCHER_ITA_GEO_DEFINITIONS

#if( defined WIN32 ) && !( defined ITA_GEO_STATIC )
#	ifdef ITA_GEO_EXPORT
#		define ITA_GEO_API __declspec( dllexport )
#	else
#		define ITA_GEO_API __declspec( dllimport )
#	endif
#else
#	define ITA_GEO_API
#endif

#endif // INCLUDE_WATCHER_ITA_GEO_DEFINITIONS

/*
 * ----------------------------------------------------------------
 *
 *		ITA simulation scheduler
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2019-2022
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

#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_DEFINITIONS
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_DEFINITIONS

#if( defined WIN32 ) && !( defined ITA_SIMULATION_SCHEDULER_STATIC )
#	ifdef ITA_SIMULATION_SCHEDULER_EXPORT
#		define ITA_SIMULATION_SCHEDULER_API __declspec( dllexport )
#	else
#		define ITA_SIMULATION_SCHEDULER_API __declspec( dllimport )
#	endif
#else
#	define ITA_SIMULATION_SCHEDULER_API
#endif

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_DEFINITIONS

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

#ifndef INCLUDE_WATCHER_ITA_DEBUG
#define INCLUDE_WATCHER_ITA_DEBUG

#include <ITABaseDefinitions.h>

void ITA_BASE_API DEBUG_PRINTF( const char* format, ... );

// Setzt den Namen eines Thread, welcher in der VisualStudio Thread-Liste angezeigt wird
void ITA_BASE_API SetThreadName( long lThreadID, const char* szThreadName );

#endif // INCLUDE_WATCHER_ITA_DEBUG

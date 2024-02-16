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

#ifndef INCLUDE_WATCHER_ITA_UNCOPYABLE
#define INCLUDE_WATCHER_ITA_UNCOPYABLE

#include <ITABaseDefinitions.h>

// Idee: Scott Meyers - Effective C++

class ITA_BASE_API ITAUncopyable
{
protected:
	// Erlaubt für Unterklassen: Standardkonstruktor
	inline ITAUncopyable( ) { };

	// Erlaubt für Unterklassen: Destruktor
	virtual inline ~ITAUncopyable( ) { };

private:
	// Verboten für alle: Kopierkonstruktor
	inline ITAUncopyable( const ITAUncopyable& ) { };

	// Verboten für alle: Zuweisungsoperator
	ITAUncopyable& operator=( const ITAUncopyable& );
};

#endif // INCLUDE_WATCHER_ITA_UNCOPYABLE

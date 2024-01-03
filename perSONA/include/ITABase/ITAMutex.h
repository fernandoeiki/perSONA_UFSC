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

#ifndef INCLUDE_WATCHER_ITA_MUTEX
#define INCLUDE_WATCHER_ITA_MUTEX

#include <ITAUncopyable.h>

#ifndef _WIN32_WINNT // @todo: remove
#	define _WIN32_WINNT 0x0501
#endif

#include <windows.h>

/**
 * Die Klasse ITAMutex ist eine Wrapper-Klasse zu Win32 Mutexen.
 * Die Klasse übernimmt im Konstruktor/Destruktor
 * die Erzeugung/Freigabe des Mutex-Kernelobjektes.
 * Sinn der  Klasse ist es, die Verwendung von Mutexen, durch
 * Erzeugung/Freigabe im Konstruktor/Destruktor, zu vereinfachen.
 *
 * \note Der Unterschied zur Klasse ITACriticalSection entspricht dem Unterschied
 *       Mutex vs. CRITICAL_SECTION. Kritische Bereiche können nur innerhalb
 *       eines Threads benutzt werden, Mutexe hingegen prozeßübergreifend.
 *       Dafür sind CRITICAL_SECTIONs laut Microsoft etwas effizienter.
 */

class ITA_BASE_API ITAMutex : public ITAUncopyable
{
public:
	ITAMutex( );
	~ITAMutex( );

	void request( ) { WaitForSingleObject( hMutex, INFINITE ); }
	void release( ) { ReleaseMutex( hMutex ); }

private:
	HANDLE hMutex;
};

#endif
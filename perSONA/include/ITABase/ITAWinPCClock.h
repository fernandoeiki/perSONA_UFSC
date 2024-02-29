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

#ifndef INCLUDE_WATCHER_ITA_WINPCCLOCK
#define INCLUDE_WATCHER_ITA_WINPCCLOCK

// ITABase
#include <ITABaseDefinitions.h>
#include <ITAClock.h>

/**
 * Diese Klasse realisiert Zeitgeber mittels der Windows Performance Counters.
 * Windows Performance Counters ermöglichen hochgenaue Zeitnahme mit einer
 * minimalen Auflösung von 100-Nanosekunden-Intervallen oder besser.
 * Microsoft garantiert die Synchronität der Zeitgeber auf unterschiedlichen
 * Prozessoren bzw. Prozessorkernen.
 *
 * Die Klasse ist als Singleton implementiert. Es existiert also maximal
 * eine Instanz, welche mit der Methode getInstance() abgerufen werden kann.
 */

class ITA_BASE_API ITAWinPCClock : public ITAClock
{
public:
	//! Singleton-Instanz abrufen
	static ITAWinPCClock* getInstance( );

	std::string getName( ) const { return "Windows Performance Counters"; }
	double getResolution( ) const;
	double getFrequency( ) const;
	double getTime( );

private:
	ITAWinPCClock( );

	static ITAWinPCClock* m_pInstance;
	double m_dFrequency;
};

#endif // INCLUDE_WATCHER_ITA_WINPCCLOCK

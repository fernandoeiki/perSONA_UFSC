/*
 * ----------------------------------------------------------------
 *
 *		ITA core libs
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-today
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
// $Id: ITAPosixRealtimeClock.h 2057 2011-10-24 20:08:48Z fwefers $

#ifndef __ITA_POSIXRTC_H__
#define __ITA_POSIXRTC_H__

#include <ITAClock.h>

/**
 * Diese Klasse realisiert Zeitgeber mittels der Linux real-time clock (RTC).
 * Synchronität der Zeitgeber auf unterschiedlichen Prozessoren bzw. Prozessorkernen
 * wird vom Linux-System garantiert.
 *
 * Die Klasse ist als Singleton implementiert. Es existiert also maximal
 * eine Instanz, welche mit der Methode getInstance() abgerufen werden kann.
 */

class ITAPosixRealtimeClock : public ITAClock
{
public:
	//! Singleton-Instanz abrufen
	static ITAPosixRealtimeClock* getInstance( );

	std::string getName( ) const { return "POSIX real-time clock"; }
	double getResolution( ) const;
	double getFrequency( ) const;
	double getTime( );

private:
	ITAPosixRealtimeClock( );

	static ITAPosixRealtimeClock* m_pInstance;
	double m_dResolution;
};

#endif // __ITA_POSIXRTC_H__

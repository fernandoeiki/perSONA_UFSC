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

#ifndef INCLUDE_WATCHER_ITA_SAMPLE_CLOCK
#define INCLUDE_WATCHER_ITA_SAMPLE_CLOCK

#include <ITAHPT.h>
#include <ITASamplerDefinition.h>


/**
 * Diese Klasse definiert eine Schnittstelle die es erlaubt
 * Zeitangaben eines ... in Sample-Indizes
 * eines Audio-Datenstroms umzurechnen und umgekehrt.
 */

class ITA_SAMPLER_API ITASampleClock
{
public:
	inline ITASampleClock( double dSamplerate, double dScale = 1.0 ) : m_dSamplerate( dSamplerate ), m_dScale( dScale ), m_ttRef( ITAHPT_now( ) ) { };
	inline virtual ~ITASampleClock( ) { };

	//! Skalierung [in Sekunden] zurückgeben
	inline double GetScale( ) { return m_dScale; };

	//! Zeitpunkt eines gewissen Samples setzen [Timerticks]
	inline void Adjust( int iSample, ITATimerTicks ttRef )
	{
		// Timerticks bei Sample 0 berechnen
		m_ttRef = ttRef - toTimerTicks( (double)iSample / m_dSamplerate );
	};

	//! Sample-Index in Zeitmarke umrechnen
	inline double GetTimeForSample( int iSample ) { return (double)iSample / m_dSamplerate / m_dScale; };

	//! Zeitmarke in Sample-Index umrechnen
	inline int GetSampleForTime( double dTime )
	{
		// Auf nächstgelegenen Wert runden
		return (int)( dTime * m_dScale * m_dSamplerate );
	};

	//! Sample-Index in Timerticks umrechnen
	inline ITATimerTicks GetTicksForSample( int iSample ) { return m_ttRef + toTimerTicks( (double)iSample / m_dSamplerate ); };

	//! Zeitmarke in Timerticks umrechnen
	inline ITATimerTicks GetTicksForTime( double dTime ) { return m_ttRef + toTimerTicks( dTime * m_dScale ); };

protected:
	double m_dSamplerate;
	double m_dScale;
	ITATimerTicks m_ttRef; // Reference: timer ticks at sample 0
};

#endif // INCLUDE_WATCHER_ITA_SAMPLE_CLOCK

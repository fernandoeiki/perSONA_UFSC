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

/*
 * Very ugly, only works with Win32.
 */

#ifndef INCLUDE_WATCHER_ITA_TIMER
#define INCLUDE_WATCHER_ITA_TIMER

#include <ITABaseDefinitions.h>

// STL Includes
#include <vector>

#ifdef WIN32
#	include <Windows.h>
#endif

// Weitere Includes
#ifndef _WIN32_WINNT // @todo: remove
#	define _WIN32_WINNT 0x0501
#endif

// Vorwärtsdeklarationen
class ITATimer;

//! Schnittstelle für Timer-Ereignisse
class ITA_BASE_API ITATimerEventHandler
{
public:
	/**
	 * Handler für Timer-Ereignisse.
	 *
	 * \param tSource Aufrufende Timer-Instanz
	 */
	virtual void handleTimerEvent( const ITATimer& tSource ) = 0;
};

//! Typdefinition einer Callback-Funktion für Timer-Handling
typedef void( ITATimerCallback )( const ITATimer& );

/**
 * Diese Klasse realisiert einen Zeitgeber (timer).
 * Ein Timer löst nach einer vorgegeben Zeit einmalig
 * oder periodisch ein Timer-Ereignis aus. Dabei wird
 * eine Rückruffunktion (callback) aufgerufen bzw.
 * ein assozierter Timer-Event-Handler aufgerufen.
 */

class ITA_BASE_API ITATimer
{
public:
	//! Konstruktor
	/**
	 * Erzeugt einen Timer mit dem gewünschten Interval
	 *
	 * \param dDuration Timer-Intervall in Sekunden
	 * \param bPeriodic Periodischen Timer erzeugen?
	 *
	 * \note Wenn das gewüschte Intervall nicht unterstützt wird,
	 *       wird eine ITAException ausgelöst
	 *
	 * \note Die Implementierung beruht auf Win32-Timern, deren
	 *       Auslösung auf Millisekunden beschränkt ist!
	 */
	ITATimer( double dDuration, bool bPeriodic = true );

	//! Destruktor
	virtual ~ITATimer( );

	//! Timer-Intervall zurückgeben
	double getDuration( ) const;

	//! Zurückgeben, ob der Timer periodisch ist
	bool isPeriodic( ) const;

	//! Timer starten
	void start( );

	//! Timer stoppen
	void stop( );

	//! Zurückgeben, ob der Timer gestartet ist
	bool isActive( );

	//! Einen Handler beim Timer anmelden
	void attach( ITATimerEventHandler* pHandler );

	//! Einen Handler beim Timer abmelden
	void detach( ITATimerEventHandler* pHandler );

	//! Ein Callback beim Timer anmelden
	void attach( ITATimerCallback* pCallback );

	//! Ein Callback beim Timer abmelden
	void detach( ITATimerCallback* pCallback );

private:
	HANDLE m_hThread;
	HANDLE m_hWaitableTimer;
	HANDLE m_hTerminateEvent;
	CRITICAL_SECTION m_cs;
	double m_dDuration;
	bool m_bPeriodic;
	bool m_bActive;
	std::vector<ITATimerEventHandler*> m_vHandlers;
	std::vector<ITATimerCallback*> m_vCallbacks;

	// Interne temporäre Handler/Callback Container
	std::vector<ITATimerEventHandler*> m_vHandlersInternal;
	std::vector<ITATimerCallback*> m_vCallbacksInternal;

	bool m_bDirty;

	// Methode zum Auslösen der Timer-Ereignisses
	void fire( );

	// Thread-Funktion
	static DWORD WINAPI threadProc( LPVOID lpParameter );
};

#endif // INCLUDE_WATCHER_ITA_TIMER

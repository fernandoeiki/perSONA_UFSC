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

#ifndef INCLUDE_WATCHER_ITA_CLOCK
#define INCLUDE_WATCHER_ITA_CLOCK

#include <ITABaseDefinitions.h>
#include <string>

/**
 * Diese abstrakte Klasse definiert die Schnittstelle für Zeitgeber
 * welche zur (hochgenauen) Zeitmessung eingesetzt werden können.
 * Anwendung des Zeitgebers ist das (hochgenaue) Messen von Zeitintervallen.
 * Ein Zeitgeber gibt die Zeit in Sekunden aus. Diese Zeit hat nicht
 * zunächst keine Bezugszeit. Die Semantik des Zahlenwertes (Sekunden)
 * ist im Allgemeinen nicht bekannt. Konkrete Realisierungen
 * können jedoch Semantik vorgeben (z.B. Wallclock-Time oder
 * vergangene Sekunden nach Systemstart).
 *
 * Intern arbeiten Zeitgeber meist mit Zeit-Zählern (vgl. Performance Counter,
 * TSC-Register), welche Zeitschritte als Ganzzahlen repräsentieren.
 * Jeder Zeitgeber hat eine Auflösung  (kleinstes noch messbares Zeitintervall)
 * und damit auch eine Frequenz [Hertz] (Zähler-Schritte pro Sekunde).
 * WICHTIG: Entwurfsvorgabe ist, das jeder Zeitgeber über seine gesamte
 * Lebenszeit eine konstante Auflösung und Frequenz hat.
 *
 * Um die Benutzung der Zeitgeber möglichst einfach zu gestalten und eine
 * einheitliche Maßeinheit vorzugeben, werden Zeiten in Sekunden gemessen.
 *
 * Intern verwaltet die Klasse einen Standard-Zeitgebers für die jeweilige
 * Zielplatform (implementiert als Singleton). Dieser kann mit der Methode
 * getDefaultClock() bezogen werden.
 */

class ITA_BASE_API ITAClock
{
public:
	virtual ~ITAClock( ) { };

	//! Standard Zeitgeber zurückgeben
	static ITAClock* getDefaultClock( );

	//! Name zurückgeben
	/**
	 * Gibt den Namen des Zeitmessers zurück (z.B. Windows Performance Counters, Posix Real-time Clock)
	 */
	virtual std::string getName( ) const = 0;

	//! Auflösung zurückgeben
	/**
	 * Gibt die Auflösung, das heißt das kleinste noch messbare Zeitintervall,
	 * in Sekunden zurück. In der Interpretation von Zeitzählern, entspricht die
	 * Auflösung der Periodendauer eines Zählerschrittes (timerticks).
	 */
	virtual double getResolution( ) const = 0;

	//! Frequenz zurückgeben
	/**
	 * Gibt die Frequenz, den Kehrwert der Auflösung, zurück in Hertz zurück.
	 * In der Interpretation von Zeitzählern, entspricht die Frequenz der
	 * Anzahl der Zählerschritte (timerticks) pro Sekunde.
	 */
	virtual double getFrequency( ) const = 0;

	//! Aktuelle Zeit zurückgeben
	/**
	 * Gibt die aktuelle Zeit des Zeitgebers in Sekunden zurück.
	 */
	virtual double getTime( ) = 0;
};

#endif // INCLUDE_WATCHER_ITA_CLOCK

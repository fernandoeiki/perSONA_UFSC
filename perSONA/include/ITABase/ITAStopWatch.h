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

#ifndef INCLUDE_WATCHER_ITA_STOP_WATCH
#define INCLUDE_WATCHER_ITA_STOP_WATCH

// ITABase
#include <ITABase/ITAStatistics.h>
#include <ITABaseDefinitions.h>
#include <ITAClock.h>
#include <ITACriticalSection.h>
#include <algorithm>

//! Eine Klasse zum Messen von Zeitintervallen
/**
 * ISPL::Stopwatch ist eine Klasse, welche die Funktionalität des
 * Zeitmessens wie mit einer Stoppuhr realisiert. Dazu verwendet
 * die Klasse die High Performance Timer (HPT). Ferner bietet sie
 * die Möglichkeit den Durchschnittswert der gemessenen Zeiten zu
 * ermitteln, was bei Benchmarking-Anwendung interessant ist.
 *
 * \important Die Klasse ist nicht (mehr) Thread-Safe! Um eine hohe
 *            Messgenauigkeit zu erreichen, wurde auf
 *            Synchronisationsmechanismen verzichtet. Sie müssen
 *            in ihrem Code selbst dafür Sorgen, das Zugriffe auf die
 *            Methoden von Instanzen der Klasse exklusiv geschehen!
 */

class ITA_BASE_API ITAStopWatch
{
public:
	//! Konstruktor
	ITAStopWatch( bool bStartImmediately = false );

	//! Konstruktor
	ITAStopWatch( ITAClock* pClock );

	//! Zurücksetzen
	/**
	 * Setzt den internen Zähler für die Anzahl der Messzyklen,
	 * sowie den Minimal-, Maximal- und Mittelwert zurück.
	 *
	 * \note Laufende Zeitnahmen werden abgebrochen
	 */
	void reset( );

	//! Feststellen ob die Zeitnahme bereits gestartet wurde
	bool started( ) const;

	//! Zeitnahme beginnen
	/**
	 * \note Wurde bereits die Zeitnahme gestartet, wird eine Ausnahme ausgelöst
	 */
	void start( );

	//! Zeitnahme stoppen
	/**
	 * Stoppt die aktuelle Zeitnahme und gibt die Dauer des gemessenen
	 * Zeitintervalls in Sekunden zurück.
	 *
	 * \return Gemessenes Zeitinterval [in Sekunden]
	 *
	 * \note Ist keine Zeitnahme gestartet, wird eine Ausnahme ausgelöst
	 */
	double stop( );

	//! Anzahl der gemessenen Zeitintervalle (Messzyklen) zurückgeben
	unsigned int cycles( ) const;

	//! Setzt Anzahl der berücksichtigten Zeitintervalle (Messzyklen)
	// Deprecated: void setMaxCycles(unsigned int uiMaxCycles);

	//! Kürzeste gemessene Zeit zurückgeben
	/**
	 * \return Kürzeste gemessene Zeit [in Sekunden]
	 * \note Wurden noch keine Messungen durchgeführt, ist der Rückgabewert 0
	 */
	double minimum( ) const;

	//! Längste gemessene Zeit zurückgeben
	/**
	 * \return Längste gemessene Zeit [in Sekunden]
	 * \note Wurden noch keine Messungen durchgeführt, ist der Rückgabewert 0
	 */
	double maximum( ) const;

	//! Summierte Laufzeiten seit dem letzten Reset aller gemessenen Zeiten zurückgeben
	/**
	 * \return Summe aller gemessenen Zeiten [in Sekunden]
	 * \note Wurden noch keine Messungen durchgeführt, ist der Rückgabewert 0
	 */
	inline double sum( ) { return m_dSum; }

	//! Arithmetischer Mittelwert (mean) aller gemessenen Zeiten zurückgeben
	/**
	 * \return Arithmetischer Mittelwert (mean) aller gemessenen Zeiten [in Sekunden]
	 * \note Wurden noch keine Messungen durchgeführt, ist der Rückgabewert 0
	 */
	double mean( ) const;

	//! Varianz (Moment 2. Ordnung) aller gemessenen Zeiten zurückgeben
	/**
	 * Die Varianz (das Moment 2. Ordnung) aller gemessenen Zeiten berechnet
	 * sich zu omega = sqrt( 1/n * sum_over_x[i](mju - x[i]) ), wobei
	 * mju der arithmethische Mittelwert (mean, oder auch Erwartungswert)
	 * und die x[i] die Messwerte sind.

	 * \return Varianz aller gemessenen Zeiten [in Sekunden]
	 * \note Wurden noch keine Messungen durchgeführt, ist der Rückgabewert 0
	 */
	double variance( ) const;

	//! Standardabweichung aller gemessenen Zeiten zurückgeben
	/**
	 * Die Standardabweichung aller gemessenen Zeiten berechnet
	 * sich als Quadratwurzel der Varianz.
	 *
	 * \return Standardabweichung aller gemessenen Zeiten [in Sekunden]
	 * \note Wurden noch keine Messungen durchgeführt, ist der Rückgabewert 0
	 */
	double std_deviation( ) const;

	//! Selbsttest durchführen
	/**
	 * Diese Methode misst den Durchschnittswert der Dauer zwischen
	 * zwei direkten aufeinanderfolgenden Aufrufen der Methoden
	 * start() und stop(). Idealerweise sollte dieser Wert nahe 0 sein.
	 * (Hinweis: Die Stopwatch berücksichtigt eine Grundlatenz (Verzögerung
	 * zwischen Aufrufen von start() und stop()), welche von allen Messwerten
	 * abgezogen wird die stop() zurückgibt).
	 *
	 * In der Praxis ergeben sich größere Werte, falls im Debug-Modus
	 * kompiliert wurde. In allen Fällen sollte der Wert aber <= 1ns sein.
	 * (Testsystem: Pentium M 1.4 GHz)
	 *
	 * \return Durchschnittsdauer in Sekunden
	 */
	static double selftest( );

	//! Einen formattierten String ausgeben, der den status der Stopwatch formuliert
	std::string ToString( ) const;

	//! Returns statistics as class
	ITABase::CStatistics GetStatistics( std::string sName ) const;

private:
	bool m_bStarted;
	double m_dStart, m_dStop;
	double m_dSum, m_dSquareSum, m_dMin, m_dMax;
	unsigned int m_uiCycles;

	ITAClock* m_pClock;
	static bool m_bInstanceCreated;    // Bereits eine Instanz dieser Klasse erzeugt?
	static double m_dStartStopLatency; // Latenz zwischen Start/Stop (Messfehler)
	ITACriticalSection m_csReadWrite;
};

//! Outstream operator
inline std::ostream& operator<<( std::ostream& os, ITAStopWatch& sw )
{
	os << sw.ToString( );
	return os;
};

#endif // INCLUDE_WATCHER_ITA_STOP_WATCH

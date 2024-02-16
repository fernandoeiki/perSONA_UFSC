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

#ifndef IW_ITA_SIMO_VARIABLE_DELAY_LINE
#define IW_ITA_SIMO_VARIABLE_DELAY_LINE

#include <ITACriticalSection.h>
#include <ITADSPDefinitions.h>
#include <ITADataLog.h>
#include <ITASIMOVariableDelayLineBase.h>
#include <ITAStopWatch.h>
#include <atomic>
#include <map>

//! Vorwärtsdeklarationen
class ITASampleBuffer;
class ITASampleFrame;
class IITASampleInterpolationRoutine;

//! Single-input multiple-output block-based variable delay line
/**
 * Diese Klasse realisiert Verzögerungsglieder (variable delay-lines, VDLs)
 * mit frei einstellbarer und zur Laufzeit veränderbarer Verzögerung.
 * Hierbei wird nur ein Kanal betrachtet.
 *
 * Die maximale Verzögerung wird durch den internen Pufferspeicher voralloziert.
 * Da das Reservieren von Speicherplatz zur Laufzeit teuer sein kann, ist es ratsam,
 * eine grobe Schätzung vor Ausführung einer Szene zu vollziehen und dem entsprechend
 * eine Verzögerung zu setzen.
 *
 * Berechnungsvorschrift: Samples = ( Distance / SpeedOfSound ) * SampleRate
 *
 * Beispiel:
 * - Raumakustik, Ausbreitungspfade maximal rund 100 m: 13000 = 13e3 Samples
 * - Fluglärm, Ausbreitungspfade bis zu 10 km: 1300000 = 13e5 Samples
 *
 * Mittels der Methode ReserveMaximumDelaySamples() oder
 * ReserveMaximumDelayTime() kann dieser Speicher den
 * benötigten Verzögerungen zur Laufzeit angepasst werden.
 *
 * Dieses Modul erzeugt nur dann Latenz, wenn für den aktuellen Switching-Algorithmus
 * nicht genügend Stützstellen zur Verfügung stehen. Diese Latenz tritt nur dann auf,
 * wenn die Gesamtverzögerung der VDL unter die Latenz der Interpolationsroutine
 * fällt. Die VDL Implementierung erzwingt dann diese Latenz, um auf weitere Stützwerte
 * zu warten. Anders interpretiert funktioniert die Verzögerung durch die VDL nur bis
 * zu einem Minimalabstand, welcher durch die Interpolationsroutine begrenzt wird. Unterhalb
 * dieser Grenze kommt es zu keiner zeitlich korrekten Wiedergabe der Samples.
 *
 * Beispiel:
 * - lineare Interpolation: 1 Sample Latenz, d.h. VDL Verzögerung 0 = t < 1 Sample => 1 - t = 1 Sample Latenz
 * - sinc-Interpolation: z.B. 12 Sample Latenz, d.h. VDL Verzögerung t < 12 Sample => 12 - t Samples Latenz
 * *
 * TODO: Doku, Synchronität
 * - Wächst automatisch mit Setzen der Verzögerung
 */

class ITA_DSP_API CITASIMOVariableDelayLine : public CITASIMOVariableDelayLineBase
{
public:
	//! Konstruktor der variablen Verzögerungsleitung
	/**
	 * \param dSamplerate				Abtastrate [Hz]
	 * \param iBlocklength				Streaming-Blocklänge [Anzahl Samples]
	 * \param fReservedMaxDelaySamples	Initiale maximale Verzögerung [Anzahl Samples]
	 * \param iAlgorithm				Algorithmus (siehe #ITABase::InterpolationFunctions)
	 */
	CITASIMOVariableDelayLine( const double dSamplerate, const int iBlocklength, const float fReservedMaxDelaySamples, const int iAlgorithm );

	//! Destruktor der variablen Verzögerungsleitung
	~CITASIMOVariableDelayLine( );

	//! Verfahren zur Änderung der Verzögerung zurückgeben
	/**
	 * Gibt das momentan benutzte Verfahren zur Umsetzung der Verzögerungsänderung zurück
	 *
	 * \return Eine Nummer aus der Auflistung #SwitchingAlgorithm
	 *
	 */
	int GetAlgorithm( ) const;

	//! Verfahren zur Änderung der Verzögerung setzen
	/**
	 * Setzt das momentan zu benutzende Verfahren zur Umsetzung der Verzögerungsänderung
	 *
	 * \param iAlgorithm Eine Nummer aus der Auflistung #SwitchingAlgorithm
	 *
	 */
	void SetAlgorithm( const int iAlgorithm );

	//! Minimal mögliche Verzögerung in Samples zurückgeben
	int GetMinimumDelaySamples( ) const;

	//! Minimal mögliche Verzögerung in Sekunden zurückgeben
	float GetMinimumDelayTime( ) const;

	//! Maximal Verzögerung zurückgeben [Sekunden]
	/**
	 * Maximale mögliche Verzögerung auf dem momentan
	 * reservierten Pufferspeicher in Sekunden zurückgeben
	 *
	 * Siehe auch: CITAVariableDelayLine::ReserveMaximumDelaySamples(), CITAVariableDelayLine::SetDelaySamples()
	 */
	float GetReservedMaximumDelayTime( ) const;

	//! Pufferspeicher reservieren für die angegebene maximale Verzögerung [Sekunden]
	/**
	 * Wie ReserveMaximumDelaySamples(), nur für Zeit in Sekunden
	 */
	void ReserveMaximumDelayTime( const float fMaxDelaySecs );

	//! Overall current latency of a cursor in seconds
	/**
	 * \return Delay and fractional delay in seconds
	 *
	 * \note Raises ITAException if cursor not valid
	 */
	float GetCurrentDelayTime( const int iCursorID ) const;

	//! Overall new latency of a cursor in seconds
	/**
	 * Gibt die neu eingestellte (und möglicherweise noch nicht übernommene) Gesamtverzögerung der VDL als Zusammensetzung der Ganzzahl und des Sub-Sample zurück
	 *
	 * \note Raises ITAException if cursor not valid
	 */
	float GetNewDelayTime( const int iCursorID ) const;

	//! Verzögerung setzen [Sekunden]
	/**
	 * Wie SetDelaySamples(), aber für Zeit in Sekunden.
	 */
	void SetDelayTime( const int iID, const float fDelaySecs );

	//! Pushes a block of samples at front of delay line
	/**
	 * Writes a block of samples to the input of the VDL.
	 * Does not increment block, has to be done manually (i.e. after read)
	 *
	 * @note block-oriented VDL usage is usually a three-step process: write-read-increment.
	 *
	 * @param[in] psbInput Buffer source for incoming samples
	 */
	void WriteBlock( const ITASampleBuffer* psbInput );

	//! Reads a block of samples for a read cursor and switches to new delay
	/**
	 * @note Incremet block processing after all cursors have benn processed / read.
	 *
	 * @param[in] iID Cursor identifier
	 * @param[out] psbOutput Buffer target for processed samples (must be initialized)
	 */
	void ReadBlock( const int iID, ITASampleBuffer* psbOutput );

	//! Increments processing to next block
	/**
	 * @note Make sure that all cursors have been processed, i.e. have read a block from
	 *       the delay line. Otherwise, dropouts occur.
	 */
	void Increment( );

	//! Reads a block of samples at all cursors (switches to new delay)
	/**
	 * The order of the channels in the sample frame will be linear over the
	 * internal cursor list, see GetCursorIDs()
	 *
	 * @param[in] psfOutput Initialized sample frame
	 *
	 */
	void ReadBlockAndIncrement( ITASampleFrame* psfOutput );

private:
	double m_dSampleRate; //!< Audio-Abtastrate
	int m_iBlockLength;   //!< Audio-Blockgröße

	int m_iMaxDelay;           //!< Maximal einstellbare Verzögerung (hängt von Puffergröße ab)
	int m_iSwitchingAlgorithm; //!< Eingestellter Algorithmus zum Umschalten der Verzögerung

	int m_iFadeLength; //!< Überblendlänge für das Umschaltverfahren mittels Kreuzblende (Minimum von Blocklänge oder 32 Samples)

	bool m_bBenchmark;
	ITAStopWatch m_swProcess; //!< StopWatch zur Überwachung der Berechnungsschleife

	IITASampleInterpolationRoutine* m_pInterpolationRoutine; //!< Zeiger auf Interpolationsroutine
};


#endif // IW_ITA_SIMO_VARIABLE_DELAY_LINE

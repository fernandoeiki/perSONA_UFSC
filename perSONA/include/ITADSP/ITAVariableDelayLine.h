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

#ifndef IW_ITA_VARIABLE_DELAY_LINE
#define IW_ITA_VARIABLE_DELAY_LINE

#include <ITACriticalSection.h>
#include <ITADSPDefinitions.h>
#include <ITADataLog.h>
#include <ITAStopWatch.h>
#include <atomic>

//! Vorwärtsdeklarationen
class ITASampleBuffer;
class IITASampleInterpolationRoutine;

//! Daten-Logger der VDL aktivieren
#define ITA_DSP_VDL_DATA_LOG 0

//! Klasse für variable Verzögerungsglieder (variable delay-lines, VDLs)
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
 *
 * TODO: Doku, Synchronität
 * - Wächst automatisch mit Setzen der Verzögerung
 */
class ITA_DSP_API CITAVariableDelayLine
{
public:
	//! Umsetzung der Verzögerungsänderung
	/**
	 * Auflistung der Algorithmen, die zur Umsetzung einer Verzögerungsänderung
	 * zur Verfügung stehen.
	 */
	enum SwitchingAlgorithm
	{
		SWITCH = 0,                  //!< Hartes umschalten
		CROSSFADE,                   //!< Überblenden im Zeitbereich mittels Kreuzblende (Kosinus-Quadrat)
		LINEAR_INTERPOLATION,        //!< Stauchen und Strecken im Zeitbereich durch lineare Interpolation (Polynominterpolation der Ordnung 1)
		WINDOWED_SINC_INTERPOLATION, //!< Stauchen und Strecken im Zeitbereich durch Interpolation mittels gefensterter si-Funktion
		CUBIC_SPLINE_INTERPOLATION,  //!< Stauchen und Strecken im Zeitbereich durch kubische Spline-Interpolation
	};

	//! Konstruktor der variablen Verzögerungsleitung
	/**
	 * @param[in] dSampleRate				Abtastrate [Hz]
	 * \param iBlocklength				Streaming-Blocklänge [Anzahl Samples]
	 * \param fReservedMaxDelaySamples	Initiale maximale Verzögerung [Anzahl Samples]
	 * \param iAlgorithm				Algorithmus (siehe #SwitchingAlgorithm)
	 */
	CITAVariableDelayLine( const double dSampleRate, const int iBlocklength, const float fReservedMaxDelaySamples,
	                       const int iAlgorithm = CITAVariableDelayLine::CUBIC_SPLINE_INTERPOLATION );

	//! Destruktor der variablen Verzögerungsleitung
	~CITAVariableDelayLine( );

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
	void SetAlgorithm( int iAlgorithm );

	//! Minimal mögliche Verzögerung in Samples zurückgeben
	int GetMinimumDelaySamples( ) const;

	//! Minimal mögliche Verzögerung in Sekunden zurückgeben
	float GetMinimumDelayTime( ) const;

	//! Maximal Verzögerung zurückgeben [Samples]
	/**
	 * Maximale mögliche Verzögerung auf dem momentan
	 *	reservierten Pufferspeicher in Samples zurückgeben
	 */
	float GetReservedMaximumDelaySamples( ) const;

	//! Maximal Verzögerung zurückgeben [Sekunden]
	/**
	 * Maximale mögliche Verzögerung auf dem momentan
	 * reservierten Pufferspeicher in Sekunden zurückgeben
	 *
	 * Siehe auch: CITAVariableDelayLine::ReserveMaximumDelaySamples(), CITAVariableDelayLine::SetDelaySamples()
	 */
	float GetReservedMaximumDelayTime( ) const;

	//! Pufferspeicher reservieren für die angegebene maximale Verzögerung [Samples]
	/**
	 * \note Die vorhandenen Daten bleiben erhalten
	 * \note Nicht vor parallelem Einstieg sicher
	 */
	void ReserveMaximumDelaySamples( float fMaxDelaySamples );

	//! Pufferspeicher reservieren für die angegebene maximale Verzögerung [Sekunden]
	/**
	 * Wie ReserveMaximumDelaySamples(), nur für Zeit in Sekunden
	 */
	void ReserveMaximumDelayTime( float fMaxDelaySecs );

	//! Sub-Sample-Verzögerung aktiviert
	/**
	 * \return Gibt zurück, ob Sub-Sample-Verzögerungen aktiviert (true) oder deaktiviert (false) ist
	 */
	bool GetFractionalDelaysEnabled( ) const;

	//! Sub-Sample-Verzögerung setzen
	/**
	 * \param bEnabled Aktiviert (true) oder deaktiviert (false) Sub-Sample-Verzögerungen
	 */
	void SetFractionalDelaysEnabled( bool bEnabled );

	//! Gesamtverzögerung zurückgeben [Samples]
	/**
	 * Gibt die Gesamtverzögerung der VDL als Zusammensetzung der Ganzzahl und des Sub-Sample zurück
	 */
	float GetDelaySamples( ) const;

	//! Gesamtverzögerung zurückgeben
	/**
	 * Gibt die Gesamtverzögerung der VDL als Zusammensetzung der Ganzzahl und des Sub-Sample zurück
	 */

	float GetDelayTime( ) const;

	//! Gesamtverzögerung zurückgeben [Zeit]
	/**
	 * Gibt die neu eingestellte (und möglicherweise noch nicht übernommene) Gesamtverzögerung der VDL als Zusammensetzung der Ganzzahl und des Sub-Sample zurück
	 */
	float GetNewDelayTime( ) const;

	//! Gesamtverzögerung zurückgeben [Samples]
	/**
	 * Gibt die Gesamtverzögerung der VDL als Ganzzahl und als Sub-Sample zurück
	 *
	 * \return iIntegerDelay Ganzzahlwert der Verzögerung (kleiner oder gleich der Gesamtverzögerung)
	 * \return fFractionalDelay Bruch der Sub-Sample-Verzögerung aus dem Wertebereich [0, 1)
	 *
	 */
	float GetDelaySamples( int& iIntegerDelay, float& fFractionalDelay ) const;

	//! Verzögerung setzen [Samples]
	/**
	 * Setzt die Verzögerung der VDL. Die Verzögerungsanpassung wird
	 * sofort auf den aktuellen Leseblock angewendet.
	 *
	 * \note	Vergrößert gegebenenfalls den internen Puffer auf das Doppelte der aktuellen Größe.
	 *			Dies kann unter Umständen zu einem Blockausfall führen, da die Operation teuer ist.
	 *			Es empfiehlt sich bereits bei der Initialisierung für ausreichend Speicher zu sorgen,
	 *			siehe ReserveMaximumDelaySamples().
	 *
	 * \note	Die Funktion darf nicht parallel betreten werden (non-reentrant)
	 */
	void SetDelaySamples( float fDelaySamples );

	//! Verzögerung setzen [Sekunden]
	/**
	 * Wie SetDelaySamples(), aber für Zeit in Sekunden.
	 */
	void SetDelayTime( float fDelaySecs );

	//! Löscht alle internen gespeicherten Samples und setzt die Distanz auf 0
	void Clear( );

	//! Daten verarbeiten
	/**
	 * Diese Funktion wird immer dann aufgerufen, wenn ein neuer Block für die Audiohardware
	 * verarbeitet werden soll (1 Block eingeben, 1 Block entnehmen).
	 *
	 * \param psbInput Eingabepuffer (Block) der VDL
	 * \param psbOutput Ausgabepuffer (Block) der VDL
	 *
	 */
	void Process( const ITASampleBuffer* psbInput, ITASampleBuffer* psbOutput );

private:
	double m_dSampleRate;            //!< Audio-Abtastrate
	int m_iBlockLength;              //!< Audio-Blockgröße
	int m_iVDLBufferSize;            //!< Größe des Puffers zum Speichern verzögerter Samples
	ITASampleBuffer* m_psbVDLBuffer; //!< Puffer zum Speichern verzögerter Samples (variable Größe, mindestens 2xBlocklänge)
	ITASampleBuffer* m_psbTemp;      //!< Temporärer Puffer zum Arbeiten mit Samples (Größe: 2xBlocklänge) (das könnte evtl. knapp sein)
	ITACriticalSection m_csBuffer;   //!< Zugriff auf Puffer schützen

	int m_iWriteCursor;                 //!< Der Schreibzeiger ist immer Vielfaches der Blocklänge
	int m_iMaxDelay;                    //!< Maximal einstellbare Verzögerung (hängt von Puffergröße ab)
	int m_iSwitchingAlgorithm;          //!< Eingestellter Algorithmus zum Umschalten der Verzögerung
	std::atomic<float> m_fCurrentDelay; //!< Aktuelle Verzögerung in Samples
	std::atomic<float> m_fNewDelay;     //!< Neue Verzögerung in Samples
	bool m_bFracDelays;                 //!< Fractional Delay Filterung an/aus

	int m_iFadeLength; //!< Überblendlänge für das Umschaltverfahren mittels Kreuzblende (Minimum von Blocklänge oder 32 Samples)

	bool m_bStarted; //!< Statusvariable zur Initialisierung

	ITAStopWatch m_swBufferSizeInc; //!< StopWatch zur Überwachung von Speicherallozierungszeiten
	ITAStopWatch m_swProcess;       //!< StopWatch zur Überwachung der Berechnungsschleife
	int m_iNumberOfDropouts;        //!< Zählt die Anzahl durch die VDL verursachten Ausfälle

	IITASampleInterpolationRoutine* m_pInterpolationRoutine; //!< Zeiger auf Interpolationsroutine

#if( ITA_DSP_VDL_DATA_LOG == 1 )

	//! Implementierungsklasse für Logger-Datum
	class VDLLogData : ITALogDataBase
	{
	public:
		static std::ostream& outputDesc( std::ostream& os );
		std::ostream& outputData( std::ostream& os ) const;

		float fCurrentDelay;
		float fNewDelay;
		float fResamplingFactor;
		int iTargetBlockSize;
		float fProcessingTime; //!< Zeit der Process-Routine in Millisekunden
	};

	ITABufferedDataLogger<VDLLogData> m_oDataLog; //!< Logger Datum für VDL spezifische Prozess-Information
#endif
};

#endif // IW_ITA_VARIABLE_DELAY_LINE

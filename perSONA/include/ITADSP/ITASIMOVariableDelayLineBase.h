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

#ifndef IW_ITA_SIMO_VARIABLE_DELAY_LINE_BASE
#define IW_ITA_SIMO_VARIABLE_DELAY_LINE_BASE

#include <ITACriticalSection.h>
#include <ITADSPDefinitions.h>
#include <ITAStopWatch.h>
#include <atomic>
#include <map>
#include <vector>

//! Vorwärtsdeklarationen
class ITASampleBuffer;
class ITASampleFrame;

//! Single-input multiple-output block-based variable delay line base
/**
 * This class defines and partly implements functionality variable delay-lines, VDLs
 * for multiple cursors without interpolating read-out.
 * @sa CITASIMOVariableDelayLine
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

class ITA_DSP_API CITASIMOVariableDelayLineBase
{
public:
	struct CITAVDLReadCursor
	{
		std::atomic<int> iNewReadCursorSamples; //!< Read cursor that will be forwarded to on next processing block
		std::atomic<int> iOldReadCursorSamples; //!< Read cursor from last calculation

		int iOverlapSamplesLeft;  //! Defines the overlapping samples to the left (towards write cursor) included in each read() call
		int iOverlapSamplesRight; //! Defines the overlapping samples to the right (towards beginning of delay line) included in each read() call

		bool bInitialized;

		//! Default constructor for read cursor with zero delay
		inline CITAVDLReadCursor( )
		{
			bInitialized          = false;
			iNewReadCursorSamples = 0;
			iOldReadCursorSamples = 0;
			iOverlapSamplesLeft   = 0;
			iOverlapSamplesRight  = 0;
		};

		inline CITAVDLReadCursor( const CITAVDLReadCursor& rhs )
		{
			iNewReadCursorSamples.store( rhs.iNewReadCursorSamples );
			iOldReadCursorSamples.store( rhs.iOldReadCursorSamples );
			iOverlapSamplesLeft  = rhs.iOverlapSamplesLeft;
			iOverlapSamplesRight = rhs.iOverlapSamplesRight;
			bInitialized         = rhs.bInitialized;
		};

		inline CITAVDLReadCursor& operator=( const CITAVDLReadCursor& rhs )
		{
			iNewReadCursorSamples.store( rhs.iNewReadCursorSamples );
			iOldReadCursorSamples.store( rhs.iOldReadCursorSamples );
			iOverlapSamplesLeft  = rhs.iOverlapSamplesLeft;
			iOverlapSamplesRight = rhs.iOverlapSamplesRight;
			bInitialized         = rhs.bInitialized;

			return *this;
		};
	};

	//! Konstruktor der variablen Verzögerungsleitung
	/**
	 * @param iReservedMaxDelaySamples	Initiale maximale Verzögerung [Anzahl Samples]
	 */
	CITASIMOVariableDelayLineBase( const int iReservedMaxDelaySamples );
	CITASIMOVariableDelayLineBase( );

	//! Destruktor der variablen Verzögerungsleitung
	~CITASIMOVariableDelayLineBase( );

	void Initialise( const int iReservedMaxDelaySamples );
	//! Maximal Verzögerung zurückgeben [Samples]
	/**
	 * Maximale mögliche Verzögerung auf dem momentan
	 *	reservierten Pufferspeicher in Samples zurückgeben
	 */
	int GetReservedMaximumDelaySamples( ) const;

	//! Pufferspeicher reservieren für die angegebene maximale Verzögerung [Samples]
	/**
	 * \note Die vorhandenen Daten bleiben erhalten
	 * \note Nicht vor parallelem Einstieg sicher
	 */
	void ReserveMaximumDelaySamples( const int iMaxDelaySamples );

	//! Adds a new reading cursor
	/**
	 * @return Cursor ID
	 */
	int AddCursor( );

	//! Remove cursor
	/**
	 * Removes cursor of given ID
	 * @param[in] iCursorID Cursor ID
	 * @return False, if cursor not valid
	 */
	bool RemoveCursor( const int iCursorID );

	//! Checks existance of a cursor
	/**
	 * @param[in] iCursorID Cursor identifier
	 * @return True, if cursor exists, false otherwise
	 */
	bool CursorExists( const int iCursorID ) const;

	//! Returns the IDs of the current cursors
	/**
	 * @return Cursor identifier
	 */
	std::vector<int> GetCursorIDs( ) const;

	//! Returns number of current cursors
	/**
	 * @return Number of user cursors
	 */
	int GetNumCursors( ) const;

	//! Overall current latency of a cursor in samples
	/**
	 * \return Delay and fractional delay in samples (which is rounded during VDL processing)
	 *
	 * \note Raises ITAException if cursor not valid
	 */
	int GetCurrentDelaySamples( const int iCursorID ) const;

	//! Overall new latency of a cursor in samples (not yet effective)
	/**
	 * \return New delay and fractional delay in samples (which is rounded during VDL processing)
	 *
	 * \note Raises ITAException if cursor not valid
	 */
	int GetNewDelaySamples( const int iCursorID ) const;

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
	void SetDelaySamples( const int iID, const int iDelaySamples );

	//! Sets the overlapping region to the left & right of a read block (required for interpolation at boundary)
	void SetOverlapSamples( const int iCursorID, const int iLeft, const int iRight );

	//! Returns the effective number of samples return by next read() call (includes switch to new delay & overlapping samples!)
	/**
	 * @param[in] iCursorID Cursor identifier
	 * @param[in] iLength Number of samples that should be read from the VDL
	 *
	 * @return Effective number of samples required for read() call with included difference cause by switching from old to new delay
	 */
	int GetEffectiveReadLength( const int iCursorID, int iLength ) const;

	//! Returns the headroom between write and read cursor
	int GetHeadroomSamples( const int iCursorID ) const;

	int GetOverlappingSamplesLeft( const int iCursorID ) const;
	int GetOverlappingSamplesRight( const int iCursorID ) const;

	inline int GetOverlappingSamples( const int iCursorID ) const { return GetOverlappingSamplesLeft( iCursorID ) + GetOverlappingSamplesRight( iCursorID ); };

	//! Löscht alle internen gespeicherten Samples und setzt die Distanz auf 0
	void Clear( );

	//! Pushes a block of samples at front of delay line
	/**
	 * Writes a block of samples to the input of the VDL.
	 * Does not increment block, has to be done manually (i.e. after read)
	 *
	 * @note block-oriented VDL usage is usually a three-step process: write-read-increment.
	 *
	 * @param[in] pfInputSamples Sample buffer
	 * @param[in] iNumSamples Sample count
	 */
	void Write( const int iNumSamples, const float* pfInputSamples );

	//! Reads a block of samples for a read cursor and switches to new delay
	/**
	 * @note Incremet block processing after all cursors have been processed / read.
	 *
	 * @param[in] iCursorID Cursor identifier
	 * @param[in] iNumSamples Sample count
	 * @param[out] pfOutputSamples Buffer target for processed samples (must be initialized and requires GetEffectiveReadLength() samples)
	 */
	void Read( const int iCursorID, const int iNumSamples, float* pfOutputSamples );

	//! Increment write cursor (use write( N ) -> read(n1), read(n2), ... read(nn) -> increment( N )
	void Increment( const int iNumSamples );

protected:
	int m_iVDLBufferSize;            //!< Größe des Puffers zum Speichern verzögerter Samples
	ITASampleBuffer* m_psbVDLBuffer; //!< Buffer for samples (variable size at multiples of block leng, but minimum is 2 blocks)
	ITASampleBuffer* m_psbTemp;      //!< Temp buffer used during data read-out
	ITACriticalSection m_csBuffer;   //!< Zugriff auf Puffer schützen

	int m_iWriteCursor; //!< Der Schreibzeiger ist immer Vielfaches der Blocklänge
	int m_iMaxDelay;    //!< Maximal einstellbare Verzögerung (hängt von Puffergröße ab)

	std::map<int, CITAVDLReadCursor> m_lUserCursors;     //!< List of read cursors (managed by user) @todo maybe enforced thread-safe access required
	std::map<int, CITAVDLReadCursor> m_lInternalCursors; //!< List of read cursors (synced for processing)

	bool m_bStarted; //!< Statusvariable zur Initialisierung
};

#endif // IW_ITA_SIMO_VARIABLE_DELAY_LINE_BASE

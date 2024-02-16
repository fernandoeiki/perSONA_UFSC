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

#ifndef INCLUDE_WATCHER_ITA_UP_CONVOLVER
#define INCLUDE_WATCHER_ITA_UP_CONVOLVER

#include <ITABaseDefinitions.h>
#include <ITAConvolutionDefinitions.h>
#include <ITACriticalSection.h>
#include <ITAUPTrigger.h>
#include <ITAUncopyable.h>
#include <atomic>
#include <tbb/concurrent_queue.h>
#include <vector>

// Vorwürtsdeklarationen
class ITAUPFilter;
class ITAUPFilterPool;
class ITAFFT;

/**
 * Diese Klasse realisiert einen schnellen (einkanaligen) Falter (dynamic single-channel multi-block convolver),
 * welcher die effiziente Overlap-Save Blockfaltung zusammen mit einer frequency-domain delay-line (FDL)
 * benutzt um eine Impulsantwortet zu falten, welche in mehrere gleichlange Teile zerlegt wird.
 * Dieser Ansatz ermüglicht eine wesentlich grüüere Leistung als ein einfacher Blockfaltungsansatz,
 * bei welchem die komplette Impulsantwort mit einem Block gefaltet werden. Der Falter ist dynamisch,
 * d.h. er erlaubt den Austausch der Filter zur Laufzeit bzw. Streamingzeit. Der Austausch der Filter
 * geschieht entweder durch hartes Umschalten oder überblendung im Zeitbereich.
 *
 * Nebenlüufigkeit & Synchronisation:
 *
 * Folgende Methoden sind synchronisiert:
 *
 * - getFilterPool, setFilterPool, requestFilter, releaseFilter => Blocking aber leichtgewichtig, reentrant
 * - getFilterExchangeMode, setFilterExchangeMode, getFilterCrossfadeLength, setFilterCrossfadeLength,
 *   getActiveFilter, exchangeFilter => Non-blocking und wait-free, reentrant
 * - process => Non-blocking, wait-free aber NICHT REENTRANT (!!)
 *
 * Alle anderen Methoden sind nicht synchronisiert.
 *
 * Müchtest Du mehr zu den Details wissen? Frag mich! -> Frank.Wefers@akustik.rwth-aachen.de
 */

class ITA_CONVOLUTION_API ITAUPConvolution : public ITAUncopyable
{
public:
	//! Standard-Konstruktor
	/**
	 * Erzeugt einen Falter der seinen eigenen Filterpool betreibt
	 */
	ITAUPConvolution( );

	//! Initialierungs-Konstruktor
	/**
	 * Erzeugt einen Falter.
	 *
	 * \param iBlocklength		Blocklänge [in Samples]
	 * \param iMaxFilterlength  Maximale Filterlänge [Anzahl Filterkoeffizienten]
	 */
	ITAUPConvolution( const int iBlocklength, const int iMaxFilterlength, ITAUPFilterPool* pFilterPool = NULL );

	//! Destruktor
	virtual ~ITAUPConvolution( );

	//! Initialisieren
	/**
	 * Initialisiert einen Falter.
	 *
	 * \param iBlocklength		Blocklänge [in Samples]
	 * \param iMaxFilterlength  Maximale Filterlänge [Anzahl Filterkoeffizienten]
	 */
	void Init( const int iBlocklength, const int iFilterLength );

	//! Blocklänge zurückgeben
	int GetBlocklength( ) const;

	//! Maximale Filterlänge [Anzahl Filterkoeffizienten] zurückgeben
	int GetMaxFilterlength( ) const;

	//! Trigger für den Filteraustausch zurückgeben (NULL falls keiner zugeordnet)
	const ITAUPTrigger* GetFilterExchangeTrigger( ) const;

	//! Trigger für den Filteraustausch setzen
	void SetFilterExchangeTrigger( const ITAUPTrigger* pTrigger );

	//! Filteraustausch-Modus zurückgeben
	int GetFilterExchangeFadingFunction( );

	//! Filteraustausch-Modus setzen
	void SetFilterExchangeFadingFunction( const int iMode );

	//! überblendlänge [Samples] des Filteraustauschs zurückgeben
	int GetFilterCrossfadeLength( );

	//! überblendlänge [Samples] für den Filteraustausch setzen
	void SetFilterCrossfadeLength( const int iLength );

	//! Verstärkung zurückgeben
	float GetGain( ) const;

	//! Verstärkung setzen
	// Hinweis: Falls bSetImmediately==true gesetzt, wird die Verstärkung nicht
	// dynamisch angepasst, sondern hart auf den angegebenen Wert gesetzt.
	void SetGain( const float fGain, const bool bSetImmediately = false );

	//! Filterpool zurückgeben
	ITAUPFilterPool* GetFilterPool( ) const;

	//! Filterpool setzen
	/**
	 * NULL => Falter-eigenen Pool benutzen
	 */
	void SetFilterPool( ITAUPFilterPool* pFilterPool );

	//! Freies Filter anfordern
	ITAUPFilter* RequestFilter( );

	//! Filter wieder zur anderweitigen Benutzung freigeben
	void ReleaseFilter( ITAUPFilter* pFilter );

	//! Aktives Filter zurückgeben
	/**
	 * Das aktive Filter ist jenes, welches der Falter momentan benutzt.
	 */
	ITAUPFilter* GetActiveFilter( );

	//! Filter austauschen
	/**
	 * Hinweis: Nullzeiger => Aktives Filter entfernen
	 */
	void ExchangeFilter( ITAUPFilter* pNewFilter, const int iExchangeMode = ITABase::FadingFunction::COSINE_SQUARE, const int iCrossfadeLength = -1 );

	//! Löscht alle internen Samplepuffer
	void clear( );

	//! Faltungsmethode
	/**
	 * Nimmt einen neuen Block Eingangsdaten entgegen und faltet ihn mit der Impulsantwortet.
	 * Das (partielle) Ausgangssignal wird als Block im Zielarray gespeichert.
	 *
	 * \param pfInputData   Array der Eingangsdaten (Exakt soviele Elemente wie die Blocklänge ist)
	 * \param pfOutputData  Array der Ausgangsdaten (Exakt soviele Elemente wie die Blocklänge ist)
	 * \param iOutputMode   Ausgabemodus (überschreiben oder Einmischen)
	 */

	// TODO: Hier wird Austausch durchgeführt!
	void Process( const float* pfInputData, float* pfOutputData, const int iOutputMode = ITABase::MixingMethod::OVERWRITE );

	//! Faltungsmethode (Erweitert)
	/**
	 * Nimmt einen neuen Block Eingangsdaten entgegen und faltet ihn mit der Impulsantwortet.
	 * Das (partielle) Ausgangssignal wird als Block im Zielarray gespeichert.
	 *
	 * \param pfInputData   Array der Eingangsdaten
	 * \param iInputLength  Anzahl der Samples in den Eingangsdaten
	 * \param pfOutputData  Array der Ausgangsdaten (Exakt soviele Elemente wie die Blocklänge ist)
	 * \param iOutputLength Anzahl der Samples in den Ausgabedaten
	 * \param iOutputMode   Ausgabemodus (überschreiben oder Einmischen)
	 */

	void Process( const float* pfInputData, const int iInputLength, float* pfOutputData, const int iOutputLength,
	              const int iOutputMode = ITABase::MixingMethod::OVERWRITE );

private:
	typedef struct
	{
		ITAUPFilter* pFilter;
		int iExchangeMode;
		int iCrossfadeLength;
	} FilterUpdate;

	int m_iBlocklength;
	int m_iMaxFilterlength;

	std::atomic<int> m_iExchangeFadingFunction;             // Austauschmodus
	std::atomic<int> m_iCrossfadeLength;                    // überblendlänge
	std::atomic<float> m_fCurrentGain;                      // Aktuelle Verstärkung
	std::atomic<float> m_fNewGain;                          // Gewünschte Verstärkung
	std::atomic<ITAUPFilter*> m_pCurrentFilter;             // Aktives Filter
	tbb::concurrent_queue<FilterUpdate> m_qExchangeFilters; // Queue: Nächste Filter zum Austausch

	float* m_pfTimeInputBuffer;             // Eingangspuffer (Zeitbereich)
	float* m_pfTimeOutputBuffer1;           // Ausgangspuffer (Zeitbereich)
	float* m_pfTimeOutputBuffer2;           // Ausgangspuffer (Zeitbereich)
	float* m_pfFreqAuxBuffer;               // Hilfspuffer (Frequenz-bereich)
	float* m_pfFreqMixdownBuffer;           // Mischpuffer (Frequenz-bereich)
	int m_iFreqCoeffs;                      // Anzahl DFT-Koeffizienten (Symetrien eingerechnet)
	std::vector<float*> m_vpfFreqDelayLine; // Frequency-domain delay line (FDL)
	ITAFFT *m_pFFT, *m_pIFFT;               // FFT, IFFT der Daten
	ITACriticalSection m_csPool;            // Exklusiver Zugriff auf den Filterpool

	ITAUPFilterPool* m_pCurrentPool;   // Gesetzer Filterpool
	ITAUPFilterPool* m_pOwnPool;       // Falter-eigener Filterpool
	ITAUPTriggerWatch m_oTriggerWatch; // TriggerWatch für den Filteraustausch


	void CopyOutputApplyGain1( float* pfDest, const float* pfSrc, const int iNumSamples, const int iOutputMode );
	void CopyOutputApplyGain2( float* pfDest, const float* pfSrc1, const float* pfSrc2, const int iOutputLength, const int iCrossfadeLength, const int iOutputMode );
};

#endif // INCLUDE_WATCHER_ITA_UP_CONVOLVER

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

#ifndef INCLUDE_WATCHER_ITA_UP_FILTER
#define INCLUDE_WATCHER_ITA_UP_FILTER

#include <ITAConvolutionDefinitions.h>
#include <ITACriticalSection.h>
#include <ITATypes.h>
#include <ITAUncopyable.h>
#include <atomic>
#include <vector>

// Vorwärtsdeklarationen
class ITAUPFilterPool;
class ITAFFT;

/**
 * Diese Klasse realisiert Filter (d.h. Representationen von Impulsantworten im Frequenzbereich)
 * für DSMBCConvolver. Solche Filter haben einen Zustand: 1) unbenutzt oder 2) momentan in einem
 * Falter in Benutzung. Generell kann 1 Filter in beliebig vielen Faltern verwendet werden.
 * Seine Daten dürfen aber nur modifiziert werden, wenn es nicht in Benutzung ist.
 *
 * Eine neue Impulsantwort wird mittels der Methode load geladen und intern transformiert.
 *
 * Nebenläufigkeit & Synchronisation:
 *
 * Instanzen der Klasse sollen nur von einem Thread zu einer Zeit benutzt werden
 * (üblicherweise der Thread der die Filterdaten generiert hat). Im Sinne der Anwendung
 * macht es keinen Sinn das mehrere Threads um beispielsweise die load-Methode konkurrieren.
 * Deshalb unternimmt die Klasse keine Maßnahmen zur Synchronisation.
 */

class ITA_CONVOLUTION_API ITAUPFilter : public ITAUncopyable
{
public:
	//! Konstruktor
	ITAUPFilter( const int iBlocklength, const int iMaxFilterLength );

	//! Destruktor
	/**
	 * Hinweis: Das Objekt kann nur freigegeben werden, wenn es nicht mehr benutzt wird!
	 */
	virtual ~ITAUPFilter( );

	//! Gibt zurück ob der Filter aktuell in Benutzung ist
	bool IsInUse( ) const;

	//! übergeordneten Filterpool zurückgeben (falls nicht vorhanden NULL)
	ITAUPFilterPool* getParentFilterPool( ) const;

	//! Filter übergeordneten Filterpool freigeben (falls Teil eines Filterpools)
	void Release( );

	//! Filterdaten laden
	/**
	 * \param pfFilterData Array mit den Filterkoeffizienten
	 * \param iFilterLength Anzahl Filterkoeffizienten in pfFilterData (maximal iMaxFilterLength)
	 *
	 * \note Falls das Filter in Benutzung ist wird eine ITAException geworfen!
	 */
	void Load( const float* pfFilterData, const int iFilterLength );

	//! Nullen setzen
	void Zeros( );

	//! Einheitsimpuls (Dirac) setzen
	void identity( );

	// Interne Zustandklasse, welche Referenzzähler enthält.
	// Es werden immer zwei Zähler benötigt: Prep und Use.
	class State
	{
	public:
		State( ITAUPFilter* pParent );

		bool IsInUse( ) const;
		void AddPrep( );
		void RemovePrep( );
		void ExchangePrep2Use( );
		void RemoveUse( );

		// Damit auf älteren Windows-System, welche keine DCAS-Operationen bereistellen,
		// dieser zwei-elementige Zustand atomar verändert werden kann,
		// muss eine Datenstruktur von 32-Bit realisiert werden.
		// 16-Bit für die Zähler ist immer noch ausreichend
		typedef struct
		{
			std::atomic<int16_t> iPrepRefCount;
			std::atomic<int16_t> iUseRefCount;
		} StateStruct;

		ITAUPFilter* m_pParent;
		StateStruct m_oState;

		void ModifyState( const int16_t iPrepDelta, const int16_t iUseDelta );
	};

	ITAUPFilterPool* m_pParent;        // Übergeordneter Filterpool
	int m_iBlocklength;                // Blocklänge (Zeitbereich)
	int m_iNumFilterParts;             // Anzahl Filterteile
	int m_iNumEffectiveFilterParts;    // Anzahl effektiver Filterteile mit Filterkoeff. != 0
	std::vector<float*> m_vpfFreqData; // Filterdaten im Frequenzbereich (DFT-Spektren der Teile)
	ITAFFT* m_pFFT;
	ITACriticalSection m_csReentrance; // Reentrance-Lock für die Load-Methode
	State m_oState;                    // Zustand

	friend class ITAUPConvolution;
	friend class ITAUPFilterPool;
};

#endif // INCLUDE_WATCHER_ITA_UP_FILTER

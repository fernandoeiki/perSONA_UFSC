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

#ifndef __ITA_DUALCTC_STREAMFILTER_H__
#define __ITA_DUALCTC_STREAMFILTER_H__

#include <ITACriticalSection.h>
#include <ITADatasource.h>
#include <ITADatasourceRealization.h>
#include <ITAStopwatch.h>
#include <vector>
#include <windows.h>

class DSMBCConvolver;
class DSMBCFilter;
class DSMBCFilterPool;
class DSMBCTrigger;

/*
 *  Diese Klasse realisiert die Echtzeitfilterung für die Dual-CTC.
 *  Sie filtert das 2-kanalige Eingangssignal mit den CTC-Filtern
 *  aller 2 Lautsprecher (4 an der Zahl) und stellt Methoden für deren
 *  Filter-Aktualisierung bereit. Das Ausgangssignal eines jeden Lautsprechers
 *  besteht aus der Summe eines Filteranteils des linken Eingangssignals,
 *  sowie eines Filteranteils des rechten Eingangssignals. Daher gibt es
 *  4 individuelle Filter(impulsantworten).
 *
 *  Blackbox-Sicht:        CTC-Filter (4)
 *                            o o o o
 *                            | | | |
 *                            V V V V
 *                     +--------------------+
 *                     |                    |
 *  Eingang L o------->|        CTC         |-------->o Lautsprecher 1
 *  Eingang R o------->|    Streamfilter    |-------->o Lautsprecher 2
 *                     |                    |
 *                     +--------------------+
 *
 *
 *
 *  Die Filterstruktur ist wiefolgt: (Nomenklatur: CTC<X><Y>, X = Eingang, Y = Lautsprecher)
 *
 *                        +--------------+       +---+
 *                +------>| CTC-Filter00 |------>|   |
 *                |       +--------------+       |   |
 *                |                              | + |------>O Lautsprecher 1
 *  Eingang L O---+       +--------------+       |   |
 *                |   +-->| CTC-Filter10 |------>|   |
 *                |   |   +--------------+       +---+
 *  Eingang R O-------+
 *                |   |   +--------------+       +---+
 *                +------>| CTC-Filter01 |------>|   |
 *                    |   +--------------+       |   |
 *                    |                          | + |------>O Lautsprecher 2
 *                    |   +--------------+       |   |
 *                    +-->| CTC-Filter11 |------>|   |
 *                        +--------------+       +---+
 *
 *  Sie hat immer vier Ausgangskanäle und übernimmt die Samplerate und Blocklänge ihrer Eingangsquelle.
 *  Die Realisierung der Filterung erfolgt als gleichförmige Zerlegte partitionierte
 *  Overlap-save Blockfaltung im Frequenzbereich (uniform partitioned frequency-domain).
 *  Der Austausch aller CTC-Filter geschieht stets atomar (in einem Aufruf).
 */

class ITADualCTCStreamfilter : public ITADatasourceRealizationEventHandler
{
public:
	//! Konstruktor
	/**
	 * \param pdsInput 2-Kanalige Eingangsdatenquelle
	 * \param iFilterlength Anzahl Filterkoeffizienten aller CTC-Filter (muss/sollte 2er-Potenz sein)
	 * \param iFilterExchangeMode Austauschstrategie für alle Filter
	 * \param iFilterCrossfadeLength Überblendlänge [Anzahl Samples] für alle Filter
	 */

	ITADualCTCStreamfilter( double dSamplerate, int iBlocklength, int iFilterlength, int iFilterExchangeMode, int iFilterCrossfadeLength );

	//! Destruktor
	~ITADualCTCStreamfilter( );

	// Eingangsdatenquelle setzen
	// (Hinweis: Muss genau zwei Kanäle haben)
	void setInputDatasource( ITADatasource* pdsInput );

	// Ausgangsdatenquelle zurückgeben
	ITADatasource* getOutputDatasource( ) const;

	//! Den kompletten Filtersatz austauschen
	/**
	 * Tauscht den kompletten Satz CTC-Filter aus.
	 * Damit der CTC-Filtergenerator direkt weiterarbeiten kann,
	 * kommt die Methode sofort zurück sobald der Austausch initiiert ist.
	 * Trotzdem ist die Funktion strikt nicht-reentrant und intern gegen
	 * reentrance abgesichert. Der erneute Eintritt in die Methode geschieht
	 * erst wenn der vorherige Filteraustausch abgeschlossen ist.
	 *
	 * \note Für leere Filter dürfen auch Nullzeiger übergeben werden (Geschwindigkeitsvorteil)
	 */
	void setFilters( const float* pfCTCFilter00, const float* pfCTCFilter10, const float* pfCTCFilter01, const float* pfCTCFilter11
	                 //					const float* pfCTCFilter02, const float* pfCTCFilter12,
	                 //					const float* pfCTCFilter03, const float* pfCTCFilter13
	);

	// --= Implementierung der Hooks für "ITADatasourceRealization" =--

	void HandleProcessStream( ITADatasourceRealization* pSender, const ITAStreamInfo* pStreamInfo );
	void HandlePostIncrementBlockPointer( ITADatasourceRealization* pSender );

private:
	double m_dSamplerate; // Abtastrate [Hz]
	int m_iBlocklength;   // Streaming-Blocklänge
	ITADatasource* m_pdsInput;
	ITADatasourceRealization* m_pdsOutput;
	int m_iFilterlength;
	DSMBCFilterPool* m_pFilterPool;
	DSMBCTrigger* m_pFilterExchangeTrigger;
	std::vector<DSMBCConvolver*> m_vpConvolvers; // 8 individuelle Blockfalter für jedes CTC-Filter

	typedef std::vector<DSMBCFilter*> FilterSet;
	std::vector<FilterSet> m_vNextFilters; // Queue: Nächste Filtersätze zum Austausch
	ITACriticalSection m_csNextFilters;    // Lock für Queue (siehe oben)

	// Für interne Zeitnahme
	ITAStopwatch m_swLoadFilters;
	ITAStopwatch m_swConvolution;

	// Filter für einen Kanal setzen
	void setFilter( int iIndex, const float* pfFilter );
};

#endif // __ITA_DUALCTC_STREAMFILTER_H__

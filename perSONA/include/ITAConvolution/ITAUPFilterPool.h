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

#ifndef INCLUDE_WATCHER_DSMBC_FILTER_POOL
#define INCLUDE_WATCHER_DSMBC_FILTER_POOL

#include <ITAConvolutionDefinitions.h>
#include <ITACriticalSection.h>
#include <ITAFFT.h>
#include <list>

// Vorwärtsdeklarationen
class ITAUPFilter;

/**
 * Diese Klasse realisiert eine Verwalter für Filterobjekte und
 * ermöglicht ein effizientes Filter-Management mit geringem Speicherverbrauch,
 * durch die automatische Wiederverwendung von Filtern.
 *
 * Nebenläufigkeit & Synchronisation:
 *
 * Instanzen der Klasse können von beliebig vielen Threads gleichzeitig benutzt werden.
 * Alle Methoden mittels synchronisiert und dürfen auch mehrfach parallel aufgerufen
 * werden (reentrant). Die Synchronisation ist blocking, aber die Wartezeiten sind
 * gering, da innerhalb des exklusiven Zugriffs nur kurze Operationen durchgeführt werden.
 *
 */

class ITA_CONVOLUTION_API ITAUPFilterPool
{
public:
	//! Konstruktor
	ITAUPFilterPool( const int iBlocklength, const int iMaxFilterLength, const int iInitialSize );

	//! Destruktor
	/**
	 * Hinweis: Das Objekt kann nur freigegeben werden, wenn es nicht mehr benutzt wird!
	 */
	virtual ~ITAUPFilterPool( );

	//! Blocklänge zurückgeben
	int GetBlocklength( ) const;

	//! Maximale Filterlänge [Anzahl Filterkoeffizienten] zurückgeben
	int GetMaxFilterlength( ) const;

	//! Anzahl freier Filter zurückgeben
	int GetNumFreeFilters( ) const;

	//! Anzahl freier Filter zurückgeben
	int GetNumUsedFilters( ) const;

	//! Anzahl freier Filter zurückgeben
	int GetNumTotalFilters( ) const;

	//! Freies Filter anfordern
	ITAUPFilter* RequestFilter( );

	//! Filter wieder zur anderweitigen Benutzung freigeben
	/**
	 * Ist das Filter nicht in Benutzung, so kann es sofort weiterbenutzt werden.
	 * Ist das Filter in Benutzung, so wird es für die Weiterbenutzung freigebenen,
	 * sobald es in einem Falter (ITAUPConvolution) nicht mehr in Benutzung ist
	 */
	void ReleaseFilter( ITAUPFilter* pFilter );

private:
	int m_iBlocklength;
	int m_iMaxFilterLength;
	std::list<ITAUPFilter*> m_lpFreeFilters; // Unbenutzte (freie) Filter im Pool
	std::list<ITAUPFilter*> m_lpUsedFilters; // Benutzte Filter im Pool
	std::list<ITAUPFilter*> m_lpAutoFilters; // Filter welche nicht mehr seitens den Benutzers gebraucht werden, aber noch in einem Falter benutzt werden
	ITACriticalSection m_csFilters;          // Exklusiver Zugriff auf die Listen
};

#endif // INCLUDE_WATCHER_DSMBC_FILTER_POOL
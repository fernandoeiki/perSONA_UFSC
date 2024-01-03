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

#ifndef INCLUDE_WATCHER_ITA_CONVOLUTION
#define INCLUDE_WATCHER_ITA_CONVOLUTION

#include <ITAConvolutionDefinitions.h>
#include <ITASampleBuffer.h>
#include <ITASampleFrame.h>
#include <ITAUncopyable.h>

// Vorwärtsdeklarationen
class ITADirectConvolutionImpl;

/**
 * Diese Klasse definiert die Schnittstelle für schnelle (offline) Faltungen.
 * Die Funktionalität besteht darin zwei Signale möglichst schnell und effizient
 * miteinander zu falten. Die Eingaben und Ausgaben werden im Zeitbereich übergeben.
 * Instanzen der Klasse repräsentieren Faltungen eines bestimmten Typs
 * (bestimmte Eingabeparameter). Damit die maximale Leistung erreicht werden kann,
 * müssen vorher die Faltungsoperationen geplant werden.
 */

class ITA_CONVOLUTION_API ITADirectConvolution : public ITAUncopyable
{
public:
	// TODO: Flags static const int
	static const int DEFAULT_FLAGS = 0;

	//! Standardkonstruktor
	ITADirectConvolution( );

	//! Initialisierungskonstruktor (Arrays)
	ITADirectConvolution( const int src1length, const int src2length, const int flags = DEFAULT_FLAGS );

	//! Destruktor
	virtual ~ITADirectConvolution( );

	//! Planungsmethode (Arrays)
	void Plan( const int src1length, const int src2length, const int flags = DEFAULT_FLAGS );


	//! Gibt zurück ob die Faltung schon geplant ist
	bool IsPlanned( ) const;

	//! Faltungsmethode (Arrays)
	virtual void Convolve( const float* src1, const int src1length, const float* src2, const int src2length, float* dest, const int destlength );

private:
	ITADirectConvolutionImpl* m_pImpl;
};

#endif // INCLUDE_WATCHER_ITA_CONVOLUTION

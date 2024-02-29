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
/*
 *      +------------------+
 *  --->| ITA Sampler      |--->
 *  --->| o o o o      /// |--->
 *      +------------------+
 *
 *  ITASampler ist eine C++ Bibliothek die einen Sound sampler zur wavetable-basierten
 *  Klangsynthese bereitstellt. Der Begriff "sampler" bezieht sich hier auf den Terminus
 *  aus der Musikproduktion und nicht auf Abtastwerte.
 *
 *  Datei:		ITASoundSample.h
 *  Zweck:		Schnittstellendefinition für sound samples
 *  Autoren:	Frank Wefers (Frank.Wefers@akustik.rwth-aachen.de)
 *  CVS-Datum:	$Id: ITASoundSample.h,v 1.1 2008-12-10 14:15:03 fwefers Exp $
 *
 *  (c) Copyright Institut für Technische Akustik (ITA) RWTH Aachen, 2008
 */

#ifndef INCLUDE_WATCHER_ITA_SOUND_SAMPLE
#define INCLUDE_WATCHER_ITA_SOUND_SAMPLE

#include <string>
#include <vector>

/**
 * Diese abstrakte Klasse definiert die Zugriffsschnittstelle
 * zu einzelnen Samples im SamplePool.
 */

class ITASoundSample
{
public:
	//! Destruktor
	inline virtual ~ITASoundSample( ) { };

	//! Gibt zurück ob dieses Sample aus einer Datei geladen wurde
	virtual bool OriginFile( ) const = 0;

	//! Name zurückgeben
	virtual std::string GetName( ) const = 0;

	//! Name setzen
	void SetName( const std::string& sName );

	//! Dateiname zurückgeben (nur bei Samples die aus Dateien geladen wurden)
	virtual std::string GetFilename( ) const = 0;

	//! Anzahl Kanäle zurückgeben
	virtual int GetNumberOfChannels( ) const = 0;

	//! Länge [Anzahl Samples]
	virtual int GetLength( ) const = 0;

	// Zeiger auf die Daten eines Kanals zurückgeben
	virtual const float* GetChannelData( int iChannel ) const = 0;
};

#endif // INCLUDE_WATCHER_ITA_SOUND_SAMPLE

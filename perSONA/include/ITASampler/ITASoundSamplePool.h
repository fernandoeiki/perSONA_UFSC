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
 *  Datei:		ITASoundSamplePool.h
 *  Zweck:		Schnittstellendefinition für Kontainer/Verwalter von sound samples
 *  Autoren:	Frank Wefers (Frank.Wefers@akustik.rwth-aachen.de)
 *  CVS-Datum:	$Id: ITASoundSamplePool.h,v 1.1 2008-12-10 14:15:03 fwefers Exp $
 *
 *  (c) Copyright Institut für Technische Akustik (ITA) RWTH Aachen, 2008
 */

#ifndef INCLUDE_WATCHER_ITA_SOUND_SAMPLE_POOL
#define INCLUDE_WATCHER_ITA_SOUND_SAMPLE_POOL

#include <ITASamplerDefinition.h>
#include <string>
#include <vector>

// Vorwärtsdeklarationen
class ITASoundSample;

/**
 * Diese Klasse realisiert eine Verwaltung für Samples.
 * Die Trennung von der Klasse ITASampler ermöglicht es mehrer
 * Sampler mit einem SamplePool zu betreiben. So kann vermieden
 * werden mehrere gleiche Samples mehrfach zu laden und den
 * Speicher unnötig zu belasten.
 */

class ITA_SAMPLER_API ITASoundSamplePool
{
public:
	//! Factory method
	static ITASoundSamplePool* Create( int iMaxNumberOfChannels, double dSamplerate );

	//! Destruktor
	inline virtual ~ITASoundSamplePool( ) { };

	//! Maximale Anzahl Kanäle zurückgeben
	virtual int GetMaximumNumberOfChannels( ) const = 0;

	//! Abtastrate [Hz] zurückgeben
	virtual double GetSampleRate( ) const = 0;

	//! Mono-Sample aus Puffer erzeugen
	virtual int CreateSample( const float* pfData, int iLength, double dSamplerate, std::string sName = "" ) = 0;

	//! Stereo-Sample aus Puffer erzeugen
	virtual int CreateSample( const float* pfLeftChannelData, const float* pfRightChannelData, int iLength, double dSamplerate, std::string sName = "" ) = 0;

	//! Sample aus Puffer erzeugen
	virtual int CreateSample( const float** ppfChannelData, int iNumChannels, int iLength, double dSamplerate, std::string sName = "" ) = 0;

	//! Sample aus Puffer erzeugen
	virtual int CreateSample( std::vector<float*> vpfChannelData, int iLength, double dSamplerate, std::string sName = "" ) = 0;

	//! Sample aus Datei laden
	virtual int LoadSample( const std::string& sFilename, std::string sName = "" ) = 0;

	//! Sample freigeben
	virtual void FreeSample( int iSampleID ) = 0;

	//! IDs aller enthaltenen Samples zurückgeben
	virtual void GetSampleIDs( std::vector<int>& viSampleIDs ) const = 0;

	//! Sample-Objekt zurückgeben
	virtual const ITASoundSample* GetSample( int iSampleID, bool bAddPlaybackReference ) = 0;
};

#endif // INCLUDE_WATCHER_ITA_SOUND_SAMPLE_POOL

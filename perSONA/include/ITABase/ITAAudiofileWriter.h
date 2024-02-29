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

#ifndef INCLUDE_WATCHER_ITA_AUDIOFILE_WRITER
#define INCLUDE_WATCHER_ITA_AUDIOFILE_WRITER

#include <ITAAudiofileCommon.h>
#include <ITABaseDefinitions.h>
#include <string>
#include <vector>

class ITASampleBuffer;
class ITASampleFrame;

//! Abstract class for writing audio files
class ITA_BASE_API ITAAudiofileWriter
{
public:
	//! Factory-Method
	static ITAAudiofileWriter* create( const std::string& sFilePath, const ITAAudiofileProperties& props );
	virtual ~ITAAudiofileWriter( );

	//! Schreiben
	/**
	 * Schreibt uiLength Samples aus den im �bergebenen Vektor enthaltenen
	 * Float-Puffern in die Audiodatei. Die Anzahl der Float-Puffer ist muss
	 * <b>nicht</b> gleich der Anzahl der Kan�le der Audiodatei sein,
	 * darf diese Anzahl aber nicht �berschreiten.
	 * Enth�lt der �bergebene Vektor weniger Zeiger als die Audiodatei
	 * Kan�le hat, werden nur die ersten Kan�le geschrieben. Alle weiteren
	 * Kan�le werden mit Nullsamples belegt.
	 * Ferner kann man den Schreiber anweisen, nur gewisse Kan�le zu schreiben,
	 * indem man in den Vektor Nullzeiger einf�gt. Ist ein Zeiger Null,
	 * so ignoriert der Schreiber diesen und belegt den korrespondierenden
	 * Kanal mit Nullsamples.
	 *
	 * \param uiLength   Anzahl der zu lesenden Samples
	 * \param vpfSource  Vektor mit Zeigern auf die Puffer,
	 *                   aus denen die Daten gelesen werden sollen.
	 *
	 * \note Im Fehlerfall l�st die Methode eine Ausnahme des Typs ITAException aus
	 */
	virtual void write( int iLength, std::vector<const float*> vpfSource ) = 0;

	//! Schreiben
	/**
	 * Variante ohne const-Pointer.
	 */
	virtual void write( int iLength, std::vector<float*> vpfSource );

	//! Schreiben (SampleFrame)
	/**
	 * Diese Variante schreibt einen kompletten SampleFrame in die Datei
	 */
	virtual void write( const ITASampleFrame* psfSource );

	//! Schreiben (SampleFrame)
	/**
	 * Diese Variante schreibt einen SampleFrame in die Datei, wobei
	 * die Anzahl Samples und der Startoffset im Frame gesetzt werden können.
	 */
	virtual void write( const ITASampleFrame* psfSource, int iNumSamples, int iOffset = 0 );
};

ITA_BASE_API void writeAudiofile( const std::string& sFilename, const ITAAudiofileProperties& props, std::vector<const float*>& vpfSource );
ITA_BASE_API void writeAudiofile( const std::string& sFilename, const ITAAudiofileProperties& props, std::vector<float*>& vpfSource );

//! Mono-Zeitsignal in Audiodatei schreiben
ITA_BASE_API void writeAudiofile( const std::string& sFilename, const float* pfData, int iLength, double dSampleRate,
                                  ITAQuantization eQuantization = ITAQuantization::ITA_FLOAT );

//! Stereo-Zeitsignal in Audiodatei schreiben
ITA_BASE_API void writeAudiofile( const std::string& sFilename, const float* pfDataCh0, const float* pfDataCh1, int iLength, double dSampleRate,
                                  ITAQuantization eQuantization = ITAQuantization::ITA_FLOAT );

//! Inhalt eines Samplebuffer in Audiodatei schreiben
ITA_BASE_API void writeAudiofile( const std::string& sFilename, const ITASampleBuffer* psbData, double dSampleRate,
                                  ITAQuantization eQuantization = ITAQuantization::ITA_FLOAT );

//! Inhalt eines Sampleframe in Audiodatei schreiben
ITA_BASE_API void writeAudiofile( const std::string& sFilename, const ITASampleFrame* psfData, double dSampleRate,
                                  ITAQuantization eQuantization = ITAQuantization::ITA_FLOAT );

#endif // INCLUDE_WATCHER_ITA_AUDIOFILE_WRITER

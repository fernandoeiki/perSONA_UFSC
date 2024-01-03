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
 *  Datei:		ITASoundSampler.h
 *  Zweck:		Schnittstellendefinition des sound samplers selbst
 *  Autoren:	Frank Wefers (Frank.Wefers@akustik.rwth-aachen.de)
 *  CVS-Datum:	$Id: ITASoundSampler.h,v 1.2 2008-12-11 20:34:34 fwefers Exp $
 *
 *  (c) Copyright Institut für Technische Akustik (ITA) RWTH Aachen, 2008
 */

#ifndef INCLUDE_WATCHER_ITA_SOUND_SAMPLER
#define INCLUDE_WATCHER_ITA_SOUND_SAMPLER

#include <ITADataSource.h>
#include <ITASamplerDefinition.h>
#include <string>
#include <vector>

class ITASampleClock;
class ITASoundSampler;
class ITASoundSamplePool;

class ITA_SAMPLER_API ITASoundSamplerEventHandler
{
public:
	inline virtual ~ITASoundSamplerEventHandler( ) { };

	virtual void HandleSamplerEvent( ITASoundSampler* pSource, double dTimecode, int iTag, void* pParam ) = 0;
};

/**
 *
 *
 * - Playback-ID global eindeutig. Eine Playback-ID existiert niemals auf mehreren Samplern.
 *   So kann anhand der Playback-ID eindeutig auf den Sampler zurückgeschlossen werden, sofern
 *   man die Playback-IDs mit ihren Samplern assoziiert.
 * - Sample-ID sind nur lokal (in ihrem Samplepool) eindeutig, nicht aber global.
 * - Track-ID sind nur lokal (in ihrem Sampler) eindeutig, nicht aber global.
 */

class ITA_SAMPLER_API ITASoundSampler : public ITADatasource
{
public:
	/*
	//! Return values / errorcodes for class methods
	enum {
	    NOERROR = 0,		//! Kein Fehler - Alles in Ordnung
	    INVALID_ID = 1,		//! Ungültige Sample-/Playback-ID
	};
	*/

	//! Factory method
	static ITASoundSampler* Create( int iOutputChannels, double dSamplerate, int iBlocklength, ITASoundSamplePool* pSamplePool = NULL );

	//! Destruktor
	inline virtual ~ITASoundSampler( ) { };

	//! Sampleclock (Umrechnung Timecode -> Sample im Datenstrom) setzen
	virtual void SetSampleClock( ITASampleClock* pClock ) = 0;

	//! Samplepool zurückgeben
	virtual ITASoundSamplePool* GetSamplePool( ) const = 0;

	//! Samplezähler zurücksetzen
	/**
	 * Setzt den internen Samplezähler des Sampler zurück.
	 * Dies bewirkt das das erste Samples des als nächstes zurückgegeben Block
	 * den Index 0 zugewiesen bekommt.
	 */
	virtual void ResetSampleCount( ) = 0;

	//! Nächstabzuspielendes Sample zurückgeben
	/**
	 * Gibt den Index das ersten Samples im als nächstes zurückgegeben Block zurück.
	 * Der Wert ist deshalb immer ein Vielfaches der Blocklänge.
	 */
	virtual int GetSampleCount( ) = 0;

	//! Spur hinzufügen
	virtual int AddTrack( int iTrackChannels ) = 0;

	//! Kanäle einer Spur mit Ausgangskanälen verbinden
	virtual void RouteTrackChannel( int iTrackID, int iTrackChannel, int iOutputChannel ) = 0;

	//! Mono-Spur hinzufügen
	virtual int AddMonoTrack( int iOutputChannel = 0 ) = 0;

	//! Stereo-Spur hinzufügen
	virtual int AddStereoTrack( int iLeftOutputChannel = 0, int iRightOutputChannel = 1 ) = 0;

	//! Spur entfernen
	virtual void RemoveTrack( int iTrackID ) = 0;

	//! Namen einer Spur zurückgeben
	virtual std::string GetTrackName( int iTrackID ) = 0;

	//! Namen einer Spur setzen
	virtual void SetTrackName( int iTrackID, const std::string& sName ) = 0;

	//! Anzahl der Kanäle einer Spur zurückgeben
	virtual int GetTrackNumberOfChannels( int iTrackID ) = 0;

	//! Gesamtlautstärke zurückgeben
	virtual double GetMasterGain( ) = 0;

	//! Gesamtlautstärke setzen
	virtual void SetMasterGain( double dGain ) = 0;

	//! Lautstärke einer Spur zurückgeben
	virtual double GetTrackGain( int iTrackID ) = 0;

	//! Lautstärke einer Spur setzen
	virtual void SetTrackGain( int iTrackID, double dGain ) = 0;

	//! Lautstärke eines Kanals einer Spur zurückgeben
	virtual double GetTrackChannelGain( int iTrackID, int iTrackChannel ) = 0;

	//! Lautstärke eines Kanals einer Spur setzen
	virtual void SetTrackChannelGain( int iTrackID, int iTrackChannel, double dGain ) = 0;

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

	//! Wiedergabe eines Samples in einer Spur platzieren (auf Basis des Samplecount)
	/**
	 * - iSamplecount = 0 -> Sofort abspielen!
	 * - iSamplecount < 0 -> -iSamplecount Samples nach Beginn des nächsten Blocks abspielen
	 * - bSetPaused = true -> Hinzugefügtes Sample direkt pausiert setzen.
	 */
	virtual int AddPlaybackBySamplecount( int iSampleID, int iTrackID, int iSamplecount, bool bSetPaused = false, double dGain = 1.0 ) = 0;

	//!  Wiedergabe eines Samples in einer Spur platzieren (auf Basis des Timecode)
	/**
	 * - dTimecode = 0 -> Sofort abspielen!
	 * - bSetPaused = true -> Hinzugefügtes Sample direkt pausiert setzen.
	 */
	virtual int AddPlaybackByTimecode( int iSampleID, int iTrackID, double dTimecode, bool bSetPaused = false, double dGain = 1.0 ) = 0;

	//! Wiedergabe eines Samples entfernen
	/**
	 * Entfernt die Platzierung eines Samples.
	 * Diese Methode wirft niemals eine Ausnahme (ITAException, u.A.).
	 * Die Methode arbeitet wiefolgt:
	 *
	 * - Playback mit angegebener ID existiert -> Playback wird gelöscht. Danach ist die ID ungültig.
	 * - Angegebene ID existiert nicht (mehr) -> Verlassen der Funktion ohne Fehler.
	 */
	virtual void RemovePlayback( int iPlaybackID ) = 0;

	//! Alle Wiedergaben in einer Spur entfernen
	/**
	 * Entfernt alle Wiedergaben innerhalb einer Spur des Samplers.
	 * Diese Methode wirft eine Ausnahme wenn die Track-ID ungültig ist
	 */
	virtual void RemovePlaybacksOfTrack( int iTrackID ) = 0;

	//! Alle Wiedergaben aller Spuren entfernen
	virtual void RemoveAllPlaybacks( ) = 0;

	//! Gibt zurück ob die Wiedergabe eines Samples pausiert wird
	/**
	 * \return true  Falls das Playback existiert und pausiert ist
	 *         false Sonst (einschließlich dem Fall das die ID ungültig ist)
	 */
	virtual bool IsPlaybackPaused( int iPlaybackID ) = 0;

	//! Wiedergabe eines Playbacks pausieren bzw. Fortsetzen
	/**
	 * Kombinierte Methode zum Pausieren bzw. Fortsetzen einer Wiedergabe.
	 * Funktionsweise siehe PausePlayback und ResumePlayback.
	 *
	 * \param bPaused true  -> Wiedergabe pausieren,
	 *                false -> Wiedergabe fortsetzen
	 */
	virtual void SetPlaybackPaused( int iPlaybackID, bool bPaused ) = 0;

	//! Wiedergabe eines Samples pausieren
	/**
	 * Unterbricht die Wiedergabe eines Samples. Der Wiedergabezeitpunkt eines
	 * jeden Samples bleibt stets unberührt. Die Methode arbeitet wiefolgt:
	 *
	 * - Die Wiedergabe wird ausgesetzt, solange bis die Pause aufgehoben wird.
	 * - Wird die Pause aufgehoben, so wird das Sample abgespielt auch wenn
	 *   der tatsächliche Wiedergabezeitpunkt bzw. der Zeitpunkt des Endes
	 *   der Wiedergabe hinter dem ursprünglichen Zeitpunkt (ohne Pause) liegt.
	 *
	 * Beispiel 1)
	 *
	 * - Planung: Spiele Sample bei t=5s
	 * - Pause bei t=2s
	 * - Aufhebung der Pause bei t=10s -> Wiedergabe beginnt bei t=10s
	 *
	 * Beispiel 2)
	 *
	 * - Planung: Spiele Sample bei t=5s
	 * - Pause bei t=2s
	 * - Aufhebung der Pause bei t=3s
	 * -> Wiedergabe des Samples beginnt wie geplant bei t=5s
	 *
	 */
	virtual void PausePlayback( int iPlaybackID ) = 0;

	//! Wiedergabe eines pausierten Playbacks wieder aufnehmen
	virtual void ResumePlayback( int iPlaybackID ) = 0;

	//! Ereignis platzieren
	virtual int AddEvent( double dTimecode, ITASoundSamplerEventHandler* pHandler, int iTag, void* pParam ) = 0;

	//! Ereignis entfernen
	virtual void RemoveEvent( int iPlaybackID ) = 0;

	//! Informationen auf der Console ausgeben
	virtual void Print( ) = 0;
};

#endif // INCLUDE_WATCHER_ITA_SOUND_SAMPLER

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

#ifndef INCLUDE_WATCHER_ITA_AUDIOFILE_READER
#define INCLUDE_WATCHER_ITA_AUDIOFILE_READER

#include <ITAAudiofileCommon.h>
#include <ITABaseDefinitions.h>
#include <string>
#include <vector>

//! Abstract reader interface for audio files
class ITA_BASE_API ITAAudiofileReader
{
public:
	//! Factory-Method (creates loader)
	/**
	 * \note Never returns NULL but raises ITAException on error.
	 */
	static ITAAudiofileReader* create( const std::string& sFilePath );
	virtual ~ITAAudiofileReader( );
	ITAAudiofileProperties getAudiofileProperties( ) const;
	ITAQuantization getQuantization( ) const;
	ITADomain getDomain( ) const;
	int getNumberOfChannels( ) const;
	double getSamplerate( ) const;

	//! Returns absolute length of audio file in samples
	int getLength( ) const;

	//! Returns current read cursor position
	int getCursor( ) const;

	std::string getComment( ) const;

	//! Seek to a specified position inside audio file
	virtual void seek( int iOffset ) = 0;

	//! Lesen und Zielpuffer erzeugen
	/**
	 * Ließt uiLength Samples aus der Audiodatei in Float-Puffer,
	 * welche automatisch von der Methode erzeugt werden. Die Anzahl
	 * der Float-Puffer ist gleich der Anzahl der Kanäle der Audiodatei.
	 *
	 * \param uiLength Anzahl der zu lesenden Samples
	 * \return Vektor mit den Allozierten und mit Daten gefüllten Float-Puffern
	 *
	 * \note Im Fehlerfall löst die Methode eine Ausnahme des Typs ITAException aus
	 */
	std::vector<float*> read( int iLength );

	//! Lesen in vorgegebene Zielpuffer
	/**
	 * Ließt uiLength Samples aus der Audiodatei in Float-Puffer,
	 * welche der Methode als Parameter übergeben werden. Die Anzahl
	 * der Float-Puffer ist muss <b>nicht</b> gleich der Anzahl der Kanäle
	 * der Audiodatei sein, darf diese Anzahl aber nicht überschreiten.
	 * Enthält der übergebene Vektor weniger Zeiger als die Audiodatei
	 * Kanäle hat, werden nur die ersten Kanäle gelesen.
	 * Ferner kann man den Lader anweisen, nur gewisse Kanäle zu laden,
	 * indem man in den Vektor Nullzeiger einfügt. Ist ein Zeiger Null,
	 * so ignoriert der Lader diesen.
	 *
	 * \param uiLength Anzahl der zu lesenden Samples
	 * \param vpfDest  Vektor mit Zeigern auf die Puffer,
	 *                 in denen die Daten abgelegt werden sollen.
	 *
	 * \note Im Fehlerfall löst die Methode eine Ausnahme des Typs ITAException aus
	 */
	virtual void read( int iLength, std::vector<float*> vpfDest ) = 0;

protected:
	ITAQuantization m_eQuantization;
	ITADomain m_eDomain;
	int m_iChannels;
	double m_dSampleRate;
	int m_iLength;
	int m_iCursor;
	std::string m_sComment;
};

//! Schnüffelfunktion (Nur die Eigenschaften einer Audiodatei ermitteln)
ITA_BASE_API void sneakAudiofile( const std::string& sFilePath, ITAAudiofileProperties& props );

//! Audiodatei in Puffer laden (Puffer werden erzeugt)
ITA_BASE_API std::vector<float*> readAudiofile( const std::string& sFilePath, ITAAudiofileProperties& props );

//! Audiodatei in Puffer laden (Puffer sind vorgegeben)
ITA_BASE_API void readAudiofile( const std::string& sFilePath, ITAAudiofileProperties& props, std::vector<float*>& vpfData );

#endif // INCLUDE_WATCHER_ITA_AUDIOFILE_READER

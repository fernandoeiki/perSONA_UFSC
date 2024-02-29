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

#ifndef INCLUDE_WATCHER_ITA_DATA_LOG
#define INCLUDE_WATCHER_ITA_DATA_LOG

#include <ITABaseDefinitions.h>
#include <ITAException.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//! Basisklasse für Logdaten
/**
 * Realisiert Formattierungsfunktionen für Konsolen-/Dateiausgabe
 */
class ITALogDataBase
{
public:
	inline virtual ~ITALogDataBase( ) { };

	//! Hook: Ausgabe der Beschreibung des Datums (z.B. Felder) in einen Stream
	// Dies wird für den Header in der Datei verwendet
	// Zum Beispiel so: [0] Index, [1] Time, ...
	static std::ostream& outputDesc( std::ostream& os );

	//! Hook: Ausgabe eines konkreten Datums in einen Stream (Formattierer)
	virtual std::ostream& outputData( std::ostream& os ) const = 0;
};

//! Gepufferter Logger für Daten
template<class T>
class ITABufferedDataLogger
{
public:
	ITABufferedDataLogger( int iNumItems = 100, bool bHeaderIncluded = true );

	ITABufferedDataLogger( const std::string& sOutputFilePath, int iNumItems, bool bHeaderIncluded = true );

	virtual ~ITABufferedDataLogger( );

	//! Include header in exported file
	void SetIncludeHeader( bool bEnabled );

	//! Setzt die Ausgabedatei
	/**
	 * Falls diese angegeben wird, so werden alle geloggten Daten
	 * beim Aufruf des Destruktors in diese Datei geschrieben
	 */
	void setOutputFile( const std::string& sFilePath );

	std::string GetOutputFileName( ) const;

	//! Alle geloggten Einträge löschen
	void clear( );

	//! Platz für Datenfelder reservieren
	void reserve( int iNumItems );

	//! Datum loggen
	void log( const T& oLogItem );

	//! Alle geloggten Einträge in eine Datei schreiben
	void store( const std::string& sFilePath );

private:
	std::vector<T> m_vLogItems;
	std::string m_sOutputFile;
	bool m_bIncludeHeader;
};

// Header impl to avoid explicit definitions

template<class T>
ITABufferedDataLogger<T>::ITABufferedDataLogger( int iNumItems, bool bIncludeHeader ) : m_bIncludeHeader( bIncludeHeader )
{
	m_vLogItems.reserve( iNumItems );
};

template<class T>
ITABufferedDataLogger<T>::ITABufferedDataLogger( const std::string& sOutputFile, int iNumItems, bool bIncludeHeader )
    : m_sOutputFile( sOutputFile )
    , m_bIncludeHeader( bIncludeHeader )
{
	m_vLogItems.reserve( iNumItems );
};

template<class T>
ITABufferedDataLogger<T>::~ITABufferedDataLogger( )
{
	if( !m_sOutputFile.empty( ) )
		store( m_sOutputFile );
};

template<class T>
std::string ITABufferedDataLogger<T>::GetOutputFileName( ) const
{
	return m_sOutputFile;
};

template<class T>
void ITABufferedDataLogger<T>::SetIncludeHeader( bool bEnabled )
{
	m_bIncludeHeader = bEnabled;
};

template<class T>
void ITABufferedDataLogger<T>::setOutputFile( const std::string& sFilename )
{
	m_sOutputFile = sFilename;
};

template<class T>
void ITABufferedDataLogger<T>::clear( )
{
	m_vLogItems.clear( );
};

template<class T>
void ITABufferedDataLogger<T>::reserve( int iNumItems )
{
	m_vLogItems.reserve( iNumItems );
};

template<class T>
void ITABufferedDataLogger<T>::log( const T& oLogItem )
{
	m_vLogItems.push_back( oLogItem );
};

template<class T>
void ITABufferedDataLogger<T>::store( const std::string& sFilename )
{
	std::ofstream os( sFilename.c_str( ), std::ios::out | std::ios::trunc | std::ios::binary );

	if( !os.is_open( ) )
		ITA_EXCEPT1( IO_ERROR, std::string( "Could not create log output file \"" ) + sFilename + std::string( "\"" ) );

	if( m_bIncludeHeader )
		T::outputDesc( os );

	for( int i = 0; i < (int)m_vLogItems.size( ); i++ )
	{
		T& oItem = m_vLogItems[i];
		oItem.outputData( os );
	}

	os.close( );
};

#endif // INCLUDE_WATCHER_ITA_DATA_LOG

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

#ifndef INCLUDE_WATCHER_ITA_SAMPLE_FRAME
#define INCLUDE_WATCHER_ITA_SAMPLE_FRAME

// ITABase
#include <ITABaseDefinitions.h>
#include <ITASampleBuffer.h>

// STL
#include <vector>

/**
 * Ein SampleFrame in eine Menge von SamplePuffern
 */

class ITA_BASE_API ITASampleFrame
{
public:
	//! Standardkonstruktor
	/**
	 * Dieser Konstruktor erzeugt einen leeren Frame, ohne Kanäle und der Länge 0.
	 */
	ITASampleFrame( );

	//! Konstruktor
	/**
	 * Erzeugt einen Frame der gewünschten Anzahl Kanäle und Länge, ohne Abtastrate.
	 * Standardmäßig werden Samples mit Nullen initialisiert.
	 * Für manche Anwendungen ist im Sinne maximaler Geschwindigkeit
	 * sinnvoll diese Initialisierung auszulassen. Die Samples des Frame
	 * enthalten dann allerdings unbestimmte (mehr oder weniger zufällige) Werte.
	 *
	 * \param iChannels	Anzahl Kanäle
	 * \param iLength	Länge [Anzahl Samples]
	 * \param bZeroinit	Frame mit Nullen initialisieren?
	 */

	explicit ITASampleFrame( const int iChannels, const int iLength, const bool bZeroinit = 0 );

	//! Kopierkonstruktor (Zeiger)
	/**
	 * Erzeugt einen unabhängigen Frame als Kopie des gegebenen Frames.
	 * Der neue Frame hat die selbe Anzahl Kanäle und Länge und enthält
	 * die gleichen Werte wie der Quellframe.
	 *
	 * \param pSource Zeiger auf den Quellframe
	 */
	ITASampleFrame( const ITASampleFrame* pSource );

	//! Kopierkonstruktor (Referenz)
	/**
	 * Erzeugt einen unabhängigen Frame als Kopie des gegebenen Frames.
	 * Der neue Frame hat die selbe Anzahl Kanäle und Länge und enthält
	 * die gleichen Werte wie der Quellframe.
	 *
	 * \param bSource Referenz auf den Quellframe
	 */
	ITASampleFrame( const ITASampleFrame& fSource );

	//! Ladekonstruktor (Audiodatei)
	/**
	 * Dieser Konstruktor erzeugt einen Frame indem er ihn aus einer Audiodatei lädt.
	 *
	 * \note Im Fehlerfall wird eine ITAException ausgelöst.
	 */
	ITASampleFrame( const std::string& sFilePath );

	//! Destruktor
	virtual ~ITASampleFrame( );

	//! Ist der Frame leer?
	/**
	 * Ein Frame ist leer wenn er die Länge 0 und/oder keine Kanäle hat
	 */
	bool empty( ) const;

	//! Anzahl Kanäle zurückgeben
	inline int channels( ) const { return GetNumChannels( ); };

	int GetNumChannels( ) const;

	// Deprecated
	int length( ) const;

	//! Länge [Anzahl Samples] zurückgeben
	int GetLength( ) const { return length( ); };

	//! Frame initialisieren
	/**
	 * Mit dieser Methode wird ein Frame initialisiert. Dies bedeutet das seine
	 * Anzahl Kanäle und Länge festgelegt wird und der Speicher alloziert wird.
	 * Falls ein Frame bereits initialisiert war, gehen alle vorherigen Daten verloren.
	 * Die Methode ermöglich bequemes programmieren, da Frames zunächst per
	 * Standard-Konstruktor erzeugt werden können und erst später initialisiert werden.
	 *
	 * \param dSamplerate  Abtastrate [Hz] (0 => unbestimmt)
	 * \param iChannels	Anzahl Kanäle
	 * \param iLength	Länge [Anzahl Samples]
	 * \param bZeroinit	Samples mit Nullen initialisieren?
	 */
	void Init( int iChannels, int iLength, bool bZeroinit );

	//! Legacy Init with small caps style
	inline void init( int iChannels, int iLength, bool bZeroinit ) { return Init( iChannels, iLength, bZeroinit ); };

	void Load( const std::string& sFilePath );
	void Load( const std::string& sFilePath, double& dSampleRate );
	void Store( const std::string& sFilePath, double dSampleRate = 44100.0f ) const;

	//! Speicher freigeben
	/**
	 * Gibt den für den Frame allozierten Speicher frei und setzt seine
	 * Anzahl Kanäle und Länge auf 0. Hierbei gehen natürlich alle Daten verloren.
	 */
	void free( );

	//! Setzt alle Samples alles Kanäle auf den gegebenen Wert
	void fill( float fValue );

	//! Setzt die Samples aller Kanäle in einem Bereich auf den angegebenen Wert
	/**
	 * \param iOffset Startindex
	 * \param iCount  Anzahl Samples
	 * \param fFloat  Wert
	 */
	void fill( int iOffset, int iCount, float fValue );

	//! Setzt alle Samples aller Kanäle zu Null
	void zero( );

	//! Setzt einen Bereich von Samples aller Kanäle zu Null
	void zero( int iOffset, int iCount );

	//! Setzt Einheitsimpulse in jedem Kanal
	void identity( );

	//! Ein-/Ausblenden
	/**
	 * Blendet die Samples im Bereich [iOffset, iOffset+iCount] mit der
	 * angegebenen Blendfunktion ein.
	 */
	void fade( int iOffset, int iCount, int iFadeDirection, int iFadeFunction );

	//! Kreuzblenden
	/**
	 * Führt eine Kreuzblende von angebenen Frame in diesen Frame durch.
	 *
	 * Für den Modus CROSSFADE_FROM gilt:
	 *
	 * Zunächst werden iOffset Samples vom angebenen Puffer kopiert.
	 * Danach werden iCount Samples zwischen den beiden Puffern kreuzgeblendet.
	 * Dahinter folgen nur noch Samples dieses Puffers.
	 */
	void crossfade( const ITASampleFrame* psfSrc, int iOffset, int iCount, int iFadeDirection, int iFadeFunction );
	void crossfade( const ITASampleFrame& sfSrc, int iOffset, int iCount, int iFadeDirection, int iFadeFunction );

	//! Einhüllende
	/**
	/* Wendet eine lineare Einhüllende (envelope) auf den Frame an.
	*
	* \param fGain0	Startwert [0..1]
	* \param fGain1	Endwert [0..1]
	*/
	void envelope( float fGain0, float fGain1 );

	//! Samples aus einem anderen Frame in den Frame kopieren
	/**
	 * Kopiert iCount Samples aus angegebenen Frame beginnend bei Leseposition iSrcOffset
	 * in disen Frame, dort beginnend ab Schreibposition iDestOffset.
	 *
	 * \param psfSrc		Quellframe
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iSrcOffset	Leseposition im Quellframe
	 * \param iDestOffset	Schreibposition in diesem Frame
	 *
	 * \note Kein Schreiben über das Frameende hinaus!
	 * \note Beide Frames müssen die gleiche Anzahl Kanäle haben
	 */
	void write( const ITASampleFrame* psfSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );
	void write( const ITASampleFrame& sfSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );

	//! Zyklisches Schreiben
	/**
	 * Diese Methode erlaubt das zylische Schreiben von Samples in den Frame.
	 * Wenn die Leseanforderung das Ende der Frames überschreitet wird das
	 * Lesen einfach am Anfang des Frames fortgesetzt. Nützlich ist diese
	 * Funktionalität vorallem für das Implementieren von Ringpuffern.
	 * Semantik ansonsten wie read().
	 *
	 * \param psfSrc		Quellframe
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iSrcOffset	Leseposition im Quellframe
	 * \param iDestOffset	Schreibposition in diesem Frame
	 *
	 * \note Beide Frames müssen die gleiche Anzahl Kanäle haben
	 *
	 * TODO: Memory alignment für SSE?
	 */
	void cyclic_write( const ITASampleFrame* psfSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );
	void cyclic_write( const ITASampleFrame& sfSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );

	//! Cyclic shifting of samples
	/**
	 * @param [in] iCount Shifts the samples in frames by given count
	 */
	void CyclicShift( int iCount );

	//! In-place Addition: Jedem Sample einen konstanten Wert addieren
	void add_scalar( float fValue );

	//! In-place Subtraktion: Jedem Sample einen konstanten Wert subtrahieren
	void sub_scalar( float fValue );

	//! In-place Multiplikation: Jedes Sample mit einem konstanten Wert multiplizieren
	void mul_scalar( float fValue );

	//! In-place Division: Jedes Sample durch einen konstanten Wert dividieren
	void div_scalar( float fValue );

	// TODO: Bereiche Addieren usw.

	// Operatoren: Alle Kanäle mit einem SampleBuffer
	void add_buf( const ITASampleBuffer* psbSource );
	void sub_buf( const ITASampleBuffer* psbSource );
	void mul_buf( const ITASampleBuffer* psbSource );
	void div_buf( const ITASampleBuffer* psbSource );

	// Varianten mit Referenzen
	void add_buf( const ITASampleBuffer& sbSource );
	void sub_buf( const ITASampleBuffer& sbSource );
	void mul_buf( const ITASampleBuffer& sbSource );
	void div_buf( const ITASampleBuffer& sbSource );

	//! Paarweise alle Samples des gegebenen Blockes zu den Samples diesem addieren
	/*
	 * - Müssen gleiche Anzahl Kanäle und Längen haben!
	 */
	void add_frame( const ITASampleFrame* psfSource );
	void add_frame( const ITASampleFrame* psfSource, int iNumSamples );
	void sub_frame( const ITASampleFrame* psfSource );
	void mul_frame( const ITASampleFrame* psfSource );
	void div_frame( const ITASampleFrame* psfSource );

	// Varianten mit Referenzen
	void add_frame( const ITASampleFrame& sfSource );
	void sub_frame( const ITASampleFrame& sfSource );
	void mul_frame( const ITASampleFrame& sfSource );
	void div_frame( const ITASampleFrame& sfSource );

	// mit Übergabe der Position - keine identische Länge benötigt
	void add_frame_pos( const ITASampleFrame* psfSource, int iPos );

	// Kombinierte Operatoren

	// Werte eines anderen Frames mit einer Konstante multiplizieren und dann hierauf addieren
	// Semantik:
	// for i from 0 to iCount-1 do
	//   this[dest_offset + i] += (scalar * source[src_offset + i])
	//
	// iSrcOffset = Leseposition im Quellpuffer
	// iDestOffset = Schreibposition in diesem Puffer
	// iCount = Anzahl Samples
	void muladd_frame( const ITASampleFrame* psfSource, float fScalar, int iSrcOffset, int iDestOffset, int iCount );
	void muladd_frame( const ITASampleFrame& sfSource, float fScalar, int iSrcOffset, int iDestOffset, int iCount );


	//! Spitzenwert suchen
	/**
	 * Sucht den betragsgrößten Wert unter allen Samples im Frame und gibt dessen Betragswert zurück.
	 * Auf Wunsch wird auch der Kanal und Index der ersten Samples zurückgegeben, das diesen
	 * Spitzenwert erreichte (erste Fundstelle).
	 */
	float findPeak( int* piChannel = NULL, int* piPeakIndex = NULL );

	//! Negieren (Multiplikation mit -1 bzw. Phasendrehungum 180°)
	void negate( );

	//! Normalize
	/*
	 * Normalizes all data with regard to the overall maximum peak, i.e. all buffers are
	 * devided by the same value.
	 *
	 * \return Overall peak value that has been used for normalization (can be negative)
	 */
	float Normalize( );
	inline float normalize( ) { return Normalize( ); };

	//! Read/Write Indizierungsoperator für Zugriff auf Kanaldaten
	ITASampleBuffer& operator[]( int iChannel );

	//! Read-only Indizierungsoperator
	const ITASampleBuffer& operator[]( int iChannel ) const;

	//! Zuweisungsoperator
	/**
	 * Dieser Operator weist dem Puffer alle Samples eines anderen Quellpuffers zu.
	 * Hierzu wird zunächst die Länge des Puffer der des Quellpuffers angepasst.
	 * Anschließend werden alle Samples kopiert.
	 */
	ITASampleFrame& operator=( const ITASampleFrame& rhs );

	//! Arithemtische Operatoren (Aliase für arithmetische Methoden - siehe oben)
	ITASampleFrame& operator+=( const float rhs );
	ITASampleFrame& operator-=( const float rhs );
	ITASampleFrame& operator*=( const float rhs );
	ITASampleFrame& operator/=( const float rhs );
	ITASampleFrame& operator+=( const ITASampleBuffer& rhs );
	ITASampleFrame& operator-=( const ITASampleBuffer& rhs );
	ITASampleFrame& operator*=( const ITASampleBuffer& rhs );
	ITASampleFrame& operator/=( const ITASampleBuffer& rhs );
	ITASampleFrame& operator+=( const ITASampleFrame& rhs );
	ITASampleFrame& operator-=( const ITASampleFrame& rhs );
	ITASampleFrame& operator*=( const ITASampleFrame& rhs );
	ITASampleFrame& operator/=( const ITASampleFrame& rhs );

	//! Informationen über den Puffer als Zeichenkette zurückgeben
	std::string toString( ) const;

	//! Überblendfunktionen
	enum
	{
		LINEAR        = 0, //!< Lineare Überblendung aka. Rampe
		COSINE_SQUARE = 1  //!< Cosinus-Quadrat Überblendung (aka Hanning-Fenster)
	};

	//! Überblendrichtungen
	enum
	{
		FADE_IN  = 0, //!< Einblenden
		FADE_OUT = 1  //!< Ausblenden
	};

	enum
	{
		CROSSFADE_TO_SOURCE   = 0, //!< Kreuzblende hin zum Quellsignal
		CROSSFADE_FROM_SOURCE = 1  //!< Kreuzblende weg vom Quellsignal
	};

private:
	int m_iChannels;
	int m_iLength;
	std::vector<ITASampleBuffer> m_vChannels;

	// Alias für Iteratoren auf den Kanälen (weniger Schreibarbeit ;-)
	typedef std::vector<ITASampleBuffer>::iterator ch_it;
};

#endif // INCLUDE_WATCHER_ITA_SAMPLE_FRAME

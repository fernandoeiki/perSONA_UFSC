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

#ifndef INCLUDE_WATCHER_ITA_SAMPLE_BUFFER
#define INCLUDE_WATCHER_ITA_SAMPLE_BUFFER

// ITABase
#include <ITABaseDefinitions.h>

// STL
#include <string>

// Forwards
class ITASampleFrame;

//! Buffer for a field of audio samples of type 32-bit floating point
/**
 *
 */
class ITA_BASE_API ITASampleBuffer
{
public:
	ITASampleBuffer( );

	//! Create sample buffer of certain size
	/**
	 * \param iLength	Length (size) of buffer in samples
	 */
	explicit ITASampleBuffer( int iLength, bool bZeroInit = true );

	//! Copy constructor as pointer
	/**
	 * \param pSource Pointer to source buffer
	 */
	ITASampleBuffer( const ITASampleBuffer* pSource );

	//! Copy constructor as reference
	/**
	 * \param pbSource Reference to source buffer
	 */
	ITASampleBuffer( const ITASampleBuffer& sbSource );

	virtual ~ITASampleBuffer( );

	bool IsEmpty( ) const;

	//! Deprecated
	inline int length( ) { return GetLength( ); };

	//! Length (size) of buffer (number of samples)
	int GetLength( ) const;

	//! Deprecated
	inline const float* data( ) const { return GetData( ); };

	inline float* data( ) { return GetData( ); };

	//! Data pointer read-only
	const float* GetData( ) const;

	//! Data pointer
	float* GetData( );

	//! Initialize
	/**
	 * (Re-)Initialize a sample buffer
	 *
	 * \param iLength	   Number of new samples
	 * \param bZeroInit	   Init with zeros
	 */
	void Init( int iLength, bool bZeroInit = true );

	//! Free allocated samples
	void Free( );

	//! Sets all buffer samples to given value
	void Fill( float fValue );

	//! Sets defined samples to given value
	/**
	 * \param iOffset Startindex
	 * \param iCount  Anzahl Samples
	 * \param fFloat  Wert
	 */
	void Fill( int iOffset, int iCount, float fValue );

	//! Sets all samples to zero
	void Zero( );

	//! Sets given samples to zero
	void Zero( int iOffset, int iCount );

	//! Sets a Cronecker-Delta function (diskrete Dirac impulse)
	void Identity( );

	//! Fade ind or fade out
	/**
	 * Fades in sample region [iOffset, iOffset+iCount] using given fading function
	 */
	void Fade( int iOffset, int iCount, int iFadingSign, int iFadingFunction = ITABase::FadingFunction::COSINE_SQUARE );

	//! Crossfade
	/**
	 * Führt eine Kreuzblende von angebenen Puffer in diesen Puffer durch.
	 *
	 * Für den Modus CROSSFADE_FROM gilt:
	 *
	 * Zunächst werden iOffset Samples vom angebenen Puffer kopiert.
	 * Danach werden iCount Samples zwischen den beiden Puffern kreuzgeblendet.
	 * Dahinter folgen nur noch Samples dieses Puffers.
	 */
	void Crossfade( const ITASampleBuffer* psbSrc, int iOffset, int iCount, int iCrossfadeDirection, int iFadingFunction = ITABase::FadingFunction::COSINE_SQUARE );
	void Crossfade( const ITASampleBuffer& sbSrc, int iOffset, int iCount, int iCrossfadeDirection, int iFadingFunction = ITABase::FadingFunction::COSINE_SQUARE );

	//! Envelope
	/**
	/* Wendet eine lineare Einhüllende (envelope) auf den Puffer an.
	*
	* \param fGain0	Startwert [0..1]
	* \param fGain1	Endwert [0..1]
	*/
	void Envelope( float fGain0, float fGain1 );

	//! Samples in ein Array kopieren
	/**
	 * Kopiert iCount Samples aus dem Block beginnend bei Leseposition iOffset
	 * in den angegebenen Zielpuffer, dort beginnend ab Schreibposition 0.
	 *
	 * \param pfDest		Zielarray
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iSrcOffset	Leseposition in diesem Puffer (SampleBuffer)
	 *
	 * TODO: Memory alignment für SSE?
	 * \note Kein Lesen über das Pufferende hinaus!
	 */
	void read( float* pfDest, int iCount, int iSrcOffset = 0 ) const;

	//! Samples aus einem Array in den Puffer kopieren
	/**
	 * Kopiert iCount Samples aus angegebenen Array beginnend bei Leseposition 0
	 * in den Puffer (SampleBuffer), dort beginnend ab Schreibposition iDestOffset.
	 *
	 * \param pfSrc			Quellarray
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iDestOffset	Schreibposition in diesem Puffer (SampleBuffer)
	 *
	 * \note Kein Schreiben über das Pufferende hinaus!
	 */
	void write( const float* pfSrc, int iCount, int iDestOffset = 0 );


	//! Write samples from a source to the buffer (overwrites!)
	/**
	 * Writes iCount samples from the given buffer starting at read position 0
	 * into the sample buffer beginning at given destination offset.
	 *
	 * @param pfSrc			Source buffer / float array / vector
	 * @param iCount		Number of samples to be added from source buffer into sample buffer
	 * @param iDestOffset	Write position in sample buffer
	 *
	 * \@ote Make sure source buffer has iCount valid samples. Buffer will be overwritten by new samples.
	 */
	inline void WriteSamples( const float* pfSrc, int iCount, int iDestOffset = 0 ) { write( pfSrc, iCount, iDestOffset ); };

	//! Add samples from a source to the buffer
	/**
	 * Adds iCount samples from the given buffer starting at read position 0
	 * into the sample buffer beginning at given destination offset.
	 *
	 * @param pfSrc			Source buffer / float array / vector
	 * @param iCount		Number of samples to be added from source buffer into sample buffer
	 * @param iDestOffset	Write position in sample buffer
	 *
	 * \@ote Make sure source buffer has iCount valid samples
	 */
	void AddSamples( const float* pfSrc, int iCount, int iDestOffset = 0 );

	//! Samples aus einem anderen Puffer in den Puffer kopieren
	/**
	 * Kopiert iCount Samples aus angegebenen Puffer beginnend bei Leseposition iSrcOffset
	 * in disen Puffer, dort beginnend ab Schreibposition iDestOffset.
	 *
	 * \param psbSrc		Quellpuffer
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iSrcOffset	Leseposition im Quellpuffer
	 * \param iDestOffset	Schreibposition in diesem Puffer
	 *
	 * \note Kein Schreiben über das Pufferende hinaus!
	 */
	void write( const ITASampleBuffer* psbSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );
	void write( const ITASampleBuffer& sbSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );

	//! Zyklisches Lesen
	/**
	 * Diese Methode erlaubt das zylische Lesen von Samples aus dem Puffer.
	 * Wenn die Leseanforderung das Ende der Puffers überschreitet wird das
	 * Lesen einfach am Anfang des Puffers fortgesetzt. Nützlich ist diese
	 * Funktionalität vorallem für das Implementieren von Ringpuffern.
	 * Semantik ansonsten wie read().
	 *
	 * \param pfDest		Zielarray
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iSrcOffset	Leseposition in diesem Puffer (SampleBuffer)
	 *
	 * TODO: Memory alignment für SSE?
	 */
	void cyclic_read( float* pfDest, int iCount, int iSrcOffset = 0 ) const;

	//! Zyklisches Schreiben
	/**
	 * Diese Methode erlaubt das zylische Lesen von Samples aus dem Puffer.
	 * Wenn die Leseanforderung das Ende der Puffers überschreitet wird das
	 * Lesen einfach am Anfang des Puffers fortgesetzt. Nützlich ist diese
	 * Funktionalität vorallem für das Implementieren von Ringpuffern.
	 * Semantik ansonsten wie read().
	 *
	 * \param pfSrc			Quellarray
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iDestOffset	Schreibposition in diesem Puffer (SampleBuffer)
	 *
	 * TODO: Memory alignment für SSE?
	 */
	void cyclic_write( const float* pfSrc, int iCount, int iDestOffset = 0 );

	//! Zyklisches Schreiben
	/**
	 * Diese Methode erlaubt das zylische Lesen von Samples aus dem Puffer.
	 * Wenn die Leseanforderung das Ende der Puffers überschreitet wird das
	 * Lesen einfach am Anfang des Puffers fortgesetzt. Nützlich ist diese
	 * Funktionalität vorallem für das Implementieren von Ringpuffern.
	 * Semantik ansonsten wie read().
	 *
	 * \param psbSrc		Quellpuffer
	 * \param iCount		Anzahl zu kopierender Samples
	 * \param iSrcOffset	Leseposition im Quellpuffer
	 * \param iDestOffset	Schreibposition in diesem Puffer
	 *
	 * TODO: Memory alignment für SSE?
	 */
	void cyclic_write( const ITASampleBuffer* psbSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );
	void cyclic_write( const ITASampleBuffer& sbSrc, int iCount, int iSrcOffset = 0, int iDestOffset = 0 );

	//! Cyclic shifting of samples
	/**
	 * @param [in] iCount Shifts the samples in buffer by given count
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

	//! Paarweise alle Samples des gegebenen Puffers zu den Samples diesem addieren
	/*
	 * - Müssen gleiche Längen haben!
	 */
	void add_buf( const ITASampleBuffer* pSource, int iCount );
	void add_buf( const ITASampleBuffer* pSource );
	void sub_buf( const ITASampleBuffer* pSource );
	void mul_buf( const ITASampleBuffer* pSource );
	void div_buf( const ITASampleBuffer* pSource );

	void add_buf_pos( const ITASampleBuffer* pSource, int iPos );
	void add_buf_pos( float* fSource, int iSize, int iPos );

	// Implementierung mittels Referenzen
	void add_buf( const ITASampleBuffer& sbSource, int iCount );
	void add_buf( const ITASampleBuffer& sbSource );
	void sub_buf( const ITASampleBuffer& sbSource );
	void mul_buf( const ITASampleBuffer& sbSource );
	void div_buf( const ITASampleBuffer& sbSource );

	// Spezial-Operatoren

	// Werte eines anderen Puffers mit einer Konstante multiplizieren und dann hierauf addieren
	// Semantik:
	// for i from 0 to iCount-1 do
	//   this[dest_offset + i] += (scalar * source[src_offset + i])
	//
	// iSrcOffset = Leseposition im Quellpuffer
	// iDestOffset = Schreibposition in diesem Puffer
	// iCount = Anzahl Samples
	void MulAdd( const ITASampleBuffer* pSource, float fScalar, int iSrcOffset, int iDestOffset, int iCount );
	void MulAdd( const ITASampleBuffer& sbSource, float fScalar, int iSrcOffset, int iDestOffset, int iCount );

	//! Spitzenwert suchen
	/**
	 * Sucht den betragsgrößten Wert im Puffer und gibt dessen Betragswert zurück.
	 * Auf Wunsch wird auch der Index der ersten Samples zurückgegeben, das diesen
	 * Spitzenwert erreichte (erste Fundstelle).
	 */
	float FindPeak( int* piPeakIndex = NULL );

	//! Negieren (Multiplikation mit -1 bzw. Phasendrehungum 180°)
	void Negate( );

	//! Normalize data
	void Normalize( );

	//! Calculate root-mean-square
	/**
	 * @param[in] bPower If true, the RMS value is divided by the length of the buffer
	 *
	 * @return Root-Mean-Square value
	 */
	float RootMeanSquare( bool bPower = true ) const;

	//! Read/Write Indizierungsoperator
	float& operator[]( int iSample );

	//! Read-only Indizierungsoperator
	const float& operator[]( int iSample ) const;

	//! Zuweisungsoperator
	/**
	 * Dieser Operator weist dem Puffer alle Samples eines anderen Quellpuffers zu.
	 * Hierzu wird zunächst die Länge des Puffer der des Quellpuffers angepasst.
	 * Anschließend werden alle Samples kopiert.
	 */
	ITASampleBuffer& operator=( const ITASampleBuffer& rhs );

	//! Arithemtische Operatoren (Aliase für arithmetische Methoden - siehe oben)
	ITASampleBuffer& operator+=( float rhs );
	ITASampleBuffer& operator-=( float rhs );
	ITASampleBuffer& operator*=( float rhs );
	ITASampleBuffer& operator/=( float rhs );
	ITASampleBuffer& operator+=( const ITASampleBuffer& rhs );
	ITASampleBuffer& operator-=( const ITASampleBuffer& rhs );
	ITASampleBuffer& operator*=( const ITASampleBuffer& rhs );
	ITASampleBuffer& operator/=( const ITASampleBuffer& rhs );

	//! Informationen über den Puffer als Zeichenkette zurückgeben
	std::string toString( ) const;

	//! Werte als Zeichenkette zurückgeben
	std::string ValuesToString( ) const;

	void Load( const std::string& sFilePath );
	void Load( const std::string& sFilePath, float& fSampleRate );
	void Store( const std::string& sFilePath, const float fSampleRate = 44100.0f ) const;

private:
	int m_iLength;
	float* m_pfData;
	ITASampleFrame* m_pParent;

	friend class ITASampleFrame;
};

#endif // INCLUDE_WATCHER_ITA_SAMPLE_BUFFER

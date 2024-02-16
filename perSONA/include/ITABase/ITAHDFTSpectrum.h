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

#ifndef __ITA_HDFT_SPECTRUM_H__
#define __ITA_HDFT_SPECTRUM_H__

#include <ITABaseDefinitions.h>
#include <ccomplex>
#include <string>
#include <vector>

namespace ITABase
{
	/**
	 * Diese Klasse realisiert half-size DFT-Spektren. Dies sind die DFT-Spektren
	 * rein reellwertiger Signale, wie sie in der Akustik/Audiosignalverarbeitung
	 * üblich sind. Das DFT-Spektrum solcher Signale erfüllt die Hermitische Symetrie.
	 * Daher müssen von n komplexwertigen diskreten Fourierkoeffizienten eines
	 * vollständigen DFT-Spektrums nur n/2+1 komplexwertigen Koeffizienten
	 * gespeichert werden.
	 *
	 * Grundsätzlich werden die komplexwertigen Fourierkoeffizienten im
	 * interleaved Speicherlayout abgelegt, d.h. Re(0), Im(0), Re(1), Im(1), ...
	 *
	 * Die Klasse stellt Methoden für die Arbeit mit solchen Spektren bereit.
	 *
	 */

	class ITA_BASE_API CHDFTSpectrum
	{
	public:
		//! Standard-Konstruktor
		CHDFTSpectrum( );

		//! Constructor
		/**
		 * Erzeugt ein Spektrum mit vorgegebener Größe und optional zu Null gesetztem Puffer
		 *
		 * \param fSampleRate Sampling rate
		 * \param iDFTSize DFT-Spektrum-Größe
		 * \param bZeroInit Setzt den Speicher bei wahr auf Null
		 */
		explicit CHDFTSpectrum( const float fSampleRate, const int iDFTSize, const bool bZeroInit );

		//! Kopierkonstruktor (Zeiger)
		/**
		 * Erzeugt einen unabhängiges Spektrum als Kopie des gegebenen Spektrums.
		 * Das neue Spektrum hat die selbe Länge und enthält die gleichen Werte
		 * wie das Quellspektrum.
		 *
		 * \param pSource Zeiger auf das Quellspektrum
		 */
		explicit CHDFTSpectrum( const CHDFTSpectrum* pSource );

		//! Kopierkonstruktor (Referenz)
		/**
		 * Erzeugt einen unabhängiges Spektrum als Kopie des gegebenen Spektrums.
		 * Das neue Spektrum hat die selbe Länge und enthält die gleichen Werte
		 * wie das Quellspektrum.
		 *
		 * \param oSource Zeiger auf das Quellspektrum
		 */
		explicit CHDFTSpectrum( const CHDFTSpectrum& oSource );

		//! Destruktor
		virtual ~CHDFTSpectrum( );

		// Initialisieren
		/**
		 * init(0) gibt belegten Speicher frei
		 * vorherige Werte werden grundsätzlich verworfen!
		 */
		void Init( const int iDFTSize, const bool bZeroinit = true );

		// Größe des Spektrums (Anzahl Koeffizienten insgesamt) zurückgeben
		// Hinweis: Symmetrische Koeffizienten werden hier nicht mitgezählt.
		int GetSize( ) const;

		// Länge des korrespondieren Zeitsignals zurückgeben (Größe der DFT)
		int GetDFTSize( ) const;

		// Abtastrate des korrespondieren Zeitsignals zurückgeben
		float GetSampleRate( ) const;

		// Abtastrate des korrespondieren Zeitsignals setzen
		void SetSampleRate( const float fSampleRate );

		// Frequenzauflösung des Spektrums [Hz] zurückgeben
		float GetFrequencyResolution( ) const;

		float GetFrequencyOfBin( const int iBinIndex ) const;

		// Datenzeiger abrufen
		float* GetData( ) const;

		// DFT Koeffizient(en) setzen (Real-/Imaginärteil bzw. Betrag/Phase)
		void SetCoeffRI( const int iIndex, const float fReal, const float fImag = 0 );
		void SetCoeffsRI( const float fReal, const float fImag = 0 );
		void SetCoeffsRI( const int iOffset, const int iCount, const float fReal, const float fImag = 0 );

		//! Get complex value by index
		std::complex<float> GetCoeff( const int iIndex ) const;

		//! Set coefficient by index
		void SetCoeff( const int iIndex, std::complex<float>& cfCoeff );

		void SetCoeffMP( const int iIndex, const float fMagnitude, const float fPhase );
		void SetCoeffsMP( const float fMagnitude, const float fPhase );
		void SetCoeffsMP( const int iOffset, const int iCount, const float fMagnitude, const float fPhase );

		//! Betragswert setzen, vorhandene Phasen erhalten
		void SetMagnitudePreservePhase( const int iIndex, const float fMagnitude );
		void SetMagnitudesPreservePhases( const float fMagnitude );
		void SetMagnitudesPreservePhases( const int iOffset, const int iCount, const float fMagnitude );

		//! Phase setzen, vorhandene Beträge erhalten
		void SetPhasePreserveMagnitude( const int iIndex, const float fPhase );
		void SetPhasesPreserveMagnitudes( const float fPhase );
		void SetPhasesPreserveMagnitudes( const int iOffset, const int iCount, const float fPhase );

		// Konstante addieren
		void Add( const float fReal, const float fImag = 0 );
		void Sub( const float fReal, const float fImag = 0 );

		// Spektrum addieren
		void Add( const CHDFTSpectrum& s );
		void Add( const CHDFTSpectrum* );
		void Sub( const CHDFTSpectrum& s );
		void Sub( const CHDFTSpectrum* );
		void Mul( const CHDFTSpectrum& s );
		void Mul( const float fFactor );
		void Mul( const CHDFTSpectrum* );

		//! Multiplies the conjugate of the given spectrum without data copy
		void MulConj( const CHDFTSpectrum* );

		//! Devide spectrum
		void Div( const CHDFTSpectrum& s );
		void Div( const CHDFTSpectrum* );

		//! Betragsspektrum berechnen und in gegebenes Array speichern
		// Zeiger dürfen Null sein
		void CalcMagnitudes( float* pfMagnitudes ) const;

		//! Calculates magnitude from real and imaginary part for a given frequency bin
		float CalcMagnitude( const int iIndex ) const;

		//! Phasenspektrum berechnen und in gegebenes Array speichern
		// Zeiger dürfen Null sein
		void CalcPhases( float* pfPhasess );

		//! Betragsgrößten Koeffizienten ermitteln
		float FindMax( ) const;
		float FindMax( int& iMaxIndex ) const;

		//! Negieren (Multiplikation mit -1 bzw. Phasendrehungum 180°)
		void Negate( );

		//! Konjugiert das Spectrum
		void Conjugate( );

		//! Set unity DFT coeffs (re == 1, im == 0)
		void SetUnity( );

		//! Set unity DFT coeffs (re == 1, im == 0)
		void SetZero( );

		//! Komplexen bzw. rellen natürlichen Logarithmus berechnen
		/**
		 * Reller log entspricht dem Betrag des komplexen log.
		 * Intern wird std::logf verwendet, so dass Betrag 0 den Wert -HUGE_VAL und der relle
		 * Logarithmus für negative Werte den Wert NAN zurückgibt
		 */
		void Log( const bool bComplex = true );

		//! Komplexe bzw. reelle Exponentialfunktion berechnen
		/**
		 * Intern wird std::exp verwendet, so dass große Beträge +-HUGE_VAL zurückgeben
		 */
		void Exp( const bool bComplex = true );

		//! Alle Filterkoeffizienten eines anderen Spektrums in dieses kopieren
		void CopyFrom( const CHDFTSpectrum& s );
		void Copy( const CHDFTSpectrum* );

		//! Einen Teil der Filterkoeffizienten eines anderen Spektrums in dieses kopieren
		void CopyFrom( const CHDFTSpectrum& s, const int iOffset, const int iCount );

		//! Zuweisungsoperator
		/**
		 * Dieser Operator weist dem Spektrum eines anderen Spektrums zu.
		 * Hierzu wird zunächst die Größe des Spektrums angepasst.
		 * Anschließend werden alle Koeffizienten kopiert.
		 */
		CHDFTSpectrum& operator=( const CHDFTSpectrum& rhs );

		//! Zeichenkette mit den Werten zurückgeben
		std::string ToString( );

		//! Calculates the energy of the spectrum
		/**
		 * Returns the energy of a HDFTSpectrum as a float
		 */
		float GetEnergy( ) const;


	private:
		int m_iSize;
		int m_iDFTSize;
		float m_fSampleRate;

		mutable std::vector<float> m_vfData;
	};
} // namespace ITABase

#endif // __ITA_HDFT_SPECTRUM_H__

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

#ifndef IW_ITA_THIRD_OCTAVE_FILTER_GENERATOR
#define IW_ITA_THIRD_OCTAVE_FILTER_GENERATOR

#include <ITADSPDefinitions.h>
#include <ITAFFT.h>
#include <ITASampleBuffer.h>
#include <ITAThirdOctaveMagnitudeSpectrum.h>
#include <string.h>
#include <vector>

/**
 * Diese Klasse erzeugt FIR-Filter (Impulsantworten) aus Terzband-Betragsspektren.
 * Hierzu wird ein linear-phasiges FIR-Filter mittels Spline-Interpolation erzeugt.
 * Die Filter erzeugen eine Latenz der halben Filterl�nge.
 */
class ITA_DSP_API CITAThirdOctaveFIRFilterGenerator
{
public:
	// Konstruktor
	CITAThirdOctaveFIRFilterGenerator( const double dSampleRate, const int iFilterLength );

	// Destruktor
	~CITAThirdOctaveFIRFilterGenerator( );

	// Filterl�nge zur�ckgeben [Samples]
	int GetFilterLength( ) const;

	//! Returns sampling rate [Samples/s]
	double GetSampleRate( ) const;

	// Latenz in den Filtern zur�ckgeben [Samples]
	int GetLatency( ) const;

	// Mittlere Laufzeit der Erzeuger-Methode zur�ckgeben
	double GetAverageRuntime( ) const;

	// Filter erzeugen
	void GenerateFilter( const ITABase::CThirdOctaveGainMagnitudeSpectrum& oTOMagnitudes, float* pfFilterCoeffs, bool bMinimumPhase = false ) const;

	//! Generate FIR filter from third octave (linear) magnitude spectrum
	/**
	 * @param[in] oTOGainMagnitudes Target energetic spectrum
	 * @param[out] sbImpulseResponse Generated impulse response (time domain filter coefficients) (must be equal or longer than initial filter length of generator class)
	 * @param[out] bMinimumPhase Request minimum phase
	 */
	void GenerateFilter( const ITABase::CThirdOctaveGainMagnitudeSpectrum& oTOGainMagnitudes, ITASampleBuffer& sbImpulseResponse, bool bMinimumPhase /*=false*/ ) const;

private:
	double m_dSamplerate;                         // Abtastrate der Ausgabefilter [Hz]
	int m_iFilterLength;                          // L�nge der Ausgabefilter
	int m_iDFTCoeffs;                             // Anzahl symetrischer DFT-Koeffizienten
	float m_fDeltaF;                              // DFT-Frequenzaufl�sung [Hz]
	int m_iNumInputFreqs;                         // Anzahl Frequenzst�tzstellen f�r Interpolation (31 Terzen + 2 R�nder)
	std::vector<float> m_vfInputFreqVector;       // Frequenzst�tzstellen der Eingabedaten (Terzen) @todo jst: std::vector
	mutable std::vector<float> m_vfInputFreqData; // Zwischenspeicher f�r die Interpolation @todo jst: std::vector
	mutable float* m_ypp;                         //! Cubic spline interplation data
	mutable std::vector<float> m_vfFreqDataInterpolated;
	std::vector<float> m_vfImpulseResponse;
	mutable ITAFFT m_ifft;
};

#endif // IW_ITA_THIRD_OCTAVE_FILTER_GENERATOR

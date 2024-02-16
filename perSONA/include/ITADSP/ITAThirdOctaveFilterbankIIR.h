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

#ifndef IW_ITA_THIRD_OCTAVE_FILTERBANK_IIR
#define IW_ITA_THIRD_OCTAVE_FILTERBANK_IIR

#include <ITABiquad.h>
#include <ITADSPDefinitions.h>
#include <ITAThirdOctaveFilterbank.h>
#include <tbb/concurrent_queue.h>
#include <vector>

//! Terzfilterbank mittels Biquads (IIR Filter)
/**
 * Diese Klasse realisiert eine Terzfilterbank (#CVAThirdOctaveFilterbank) mit der Methode der kaskadierten
 * Biquads (#CVABiquad) für Verstärkungsfaktoren eines Terzbank-Betragsspektrums (#CVAThirdOctaveMagnitudes).
 *
 */
class ITA_DSP_API CITAThirdOctaveFilterbankIIR : public CITAThirdOctaveFilterbank
{
public:
	//! Konstruktor mit Samplerate und Blocklänge
	/**
	 * \param dSamplerate Samplingrate
	 * \param iBlocklength Blocklänge
	 */
	CITAThirdOctaveFilterbankIIR( const double dSampleRate, const int iBlockLength );

	//! Destruktor
	virtual ~CITAThirdOctaveFilterbankIIR( );

	//! Filterlatenz in Samples zurückgeben
	int GetLatency( ) const;

	//! Verstärkungen (Gains) setzen
	/**
	 * \param oGains Verstärkungsfaktoren
	 * \param bSmoothChangeover Wenn true, dann überblenden (default), sonst sofort internen Gain umschalten
	 */
	void SetGains( const ITABase::CThirdOctaveGainMagnitudeSpectrum& oGains, const bool bSmoothChangeover = true );
	void SetMagnitudes( const ITABase::CThirdOctaveGainMagnitudeSpectrum& oGains, const bool bSmoothChangeover = true );


	//! Alle internen Zustände zurücksetzen (Akkumulatoren der Biquads)
	void Clear( );

	//! Verarbeite Samples (Filtern)
	/**
	 * \param pfInputSamples Eingabesamples (Anzahl = Blocklänge)
	 * \param pfOutputSamples Ausgabesamples (Anzahl = Blocklänge)
	 */
	void Process( const float* pfInputSamples, float* pfOutputSamples );

private:
	//! Interne Datenklasse für das Verarbeiten eines neuen Gain Datensatzes
	class GainUpdate
	{
	public:
		ITABase::CThirdOctaveGainMagnitudeSpectrum oGains; //!< Gain-Daten
		int iBlendSamples;                                 //!< Anzahl Samples zum Überblenden
	};

	double m_dSampleRate;                                        //!< Samplingrate
	int m_iBlockLength;                                          //!< Blocklänge
	int m_nBandsInternal;                                        //!< Anzahl der internen Bänder
	int m_nBiquadsPerBand;                                       //!< Anzahl von Biqads pro Band
	std::vector<CITABiquad> m_vBiquads;                          //!< Biquads, Zugriff: [Band][BiquadNummer]
	tbb::concurrent_queue<GainUpdate> m_qGains;                  //!< Liste von neuen Verstärkungsfaktoren
	ITABase::CThirdOctaveGainMagnitudeSpectrum m_oGainsInternal; //!< Interne Verstärkungsfaktoren
	float* m_pfTempFilterBuf;                                    //!< Zwischenpuffer für Filter
	float* m_pfTempOutputBuf;                                    //!< Zwischenpuffer für Ausgabe
};

#endif // IW_ITA_THIRD_OCTAVE_FILTERBANK_IIR

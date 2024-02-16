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

#ifndef IW_ITA_THIRD_OCTAVE_FILTERBANK
#define IW_ITA_THIRD_OCTAVE_FILTERBANK

#include <ITADSPDefinitions.h>
#include <ITAThirdOctaveMagnitudeSpectrum.h>

#include <memory>

//! Terzbandspektrum-Filterbank zur digitalen Filterung
/**
 * Diese Oberklasse für Filterbänke, die zur Realisierung der Filterung von Terzbandspektren dient,
 * definiert die Schnittstellen zur Nutzung einer solchen Filterbank.
 *
 * Sie wird durch die Realisierungsmethoden (#FilterbankRealisationMethods) mittels Factory Method
 * erstellt und kann dann Eingabesamples im Process()-Schritt filtern.
 *
 * Die Datensätze der Terzbandspektren werden durch die Klasse \CThirdOctaveMagnitudeSpectrum verwaltet.
 *
 */
class ITA_DSP_API CITAThirdOctaveFilterbank
{
public:
	//! Realisierungsmethoden
	enum
	{
		FIR_SPLINE_LINEAR_PHASE = 0, //!< Linearphasiges FIR Filter mit Spline-Interpolation
		IIR_BIQUADS_ORDER10,         //!< Rekursives IIR Filter umgesetzt durch kaskadierte Biquads
		IIR_BURG_ORDER4,             //!< Recursive 4th-order IIR filtering with a Burg coefficient design
		IIR_BURG_ORDER10,            //!< Recursive 10th-order IIR filtering with a Burg coefficient design
	} FilterbankRealisationMethods;

	//! Factory method zum erzeugen einer Filterbank
	/**
	 * \param dSamplerate Samplingrate
	 * \param iBlocklength Blockgröße
	 * \param iMethod Realisierungsmethode, eines von #FilterbankRealisationMethods (default: linearphasiges FIR Filter)
	 *
	 * \return Zeiger auf die erzeugte Terzfilterbank
	 */
	static CITAThirdOctaveFilterbank* Create( const double dSampleRate, const int iBlockLength, const int iMethod = FIR_SPLINE_LINEAR_PHASE );

	/// Factory method similar to Create(), but returns a unique pointer
	static std::unique_ptr<CITAThirdOctaveFilterbank> CreateUnique( const double dSampleRate, const int iBlockLength, const int iMethod = FIR_SPLINE_LINEAR_PHASE );

	//! Destruktor
	virtual inline ~CITAThirdOctaveFilterbank( ) { };

	//! Idealer Übertrager setzen
	/**
	 * \param bSmoothChangeover Überbenden (default, true) oder direktes Umschalten (false)
	 */
	virtual inline void SetIdentity( const bool bSmoothChangeover = true )
	{
		ITABase::CThirdOctaveGainMagnitudeSpectrum oIdentity;
		oIdentity.SetIdentity( );
		SetMagnitudes( oIdentity, bSmoothChangeover );
	};

	//! Verstärkungsfaktoren setzen
	/**
	 * \param oGains Neue Verstärkungsfaktoren
	 * \param bSmoothChangeover Überbenden (default, true) oder direktes Umschalten (false)
	 */
	virtual void SetMagnitudes( const ITABase::CThirdOctaveGainMagnitudeSpectrum& oGains, const bool bSmoothChangeover = true ) = 0;

	//! Latenz (Verzögerung) der Filterbank zurückgeben
	/**
	 * \return Latenz (Verzögerung) in ganzzahligen Sample
	 */
	int GetLatency( ) const;

	//! Löscht alle internen Puffer
	virtual void Clear( ) = 0;

	//! Filtert einen Block Samples (muss die angegebene Blocklänge haben, s.o.)
	/**
	 * \pfInputSamples Eingabesamples (Anzahl = Blocklänge)
	 * \pfOutputSamples Ausgabesamples (Anzahl = Blocklänge)
	 *
	 * @todo jst: check if this couln't be decoupled from block-bound processing (like ITABiquad)
	 */
	virtual void Process( const float* pfInputSamples, float* pfOutputSamples ) = 0;

protected:
	//! Standardkonstruktor (Deaktiviert, FactoryMethod Create() benutzen)
	inline CITAThirdOctaveFilterbank( ) { };
};

#endif // IW_ITA_THIRD_OCTAVE_FILTERBANK

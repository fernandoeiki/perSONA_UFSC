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

#ifndef INCLUDE_WATCHER_ITA_MAGNITUDE_SPECTRUM
#define INCLUDE_WATCHER_ITA_MAGNITUDE_SPECTRUM

#include <ITABaseDefinitions.h>
#include <ITASpectrum.h>

namespace ITABase
{
	// Forward for aliasing classes
	class CGainMagnitudeSpectrum;

	//! A factor magnitude spectrum with linear values that are greater zero and usually between 0..1, but can also exceed.
	/**
	 * This alias class is used to give the user a hint that the underlying data should be treated as linear values (factors)
	 * or gains, because a magnitude spectrum does not specify on that. It is used like a CITAMagnitudeSpectrum.
	 * There is no real difference between a factor and a gain except that gains are commonly used in DSP (i.e. for "gain" control
	 * of audio signal channels) and factors are more common in acoustic materials such as absorption and transmission "factor".
	 */
	typedef CGainMagnitudeSpectrum CFactorMagnitudeSpectrum;

	//! Magnitude spectrum of arbitrary size and base frequencies
	/**
	 * Implementation class for magnitude spectra, that does not specify on underlying data. To be more precise in your code and
	 * for validation of data it is recommended to use the alias classes CITADecibelMagnitudeSpectrum, CITAGainMagnitudeSpectrum or CITAFactorMagnitudeSpectrum,
	 * which implement the abstract methods and are ready to use.
	 *
	 * Will raise CITAException on errors.
	 *
	 * @sa CITAThirdOctaveSpectrum, CITAPhaseSpectrum, CITAHDFTSpectrum
	 *
	 */
	class ITA_BASE_API CMagnitudeSpectrum : public CITASpectrum
	{
	public:
		CMagnitudeSpectrum( const int nNumBands );
		virtual inline ~CMagnitudeSpectrum( ) { };

		std::vector<float> GetMagnitudesCopy( ) const;
		const std::vector<float>& GetMagnitudes( ) const;

		void SetMagnitudes( const std::vector<float>& vfMagnitudes );
		void SetMagnitude( const int iFrequencyBandIndex, const float fMagnitudeValue );

		bool CompareEqualValues( const CMagnitudeSpectrum& oOtherSpectrum, const float fThreshold = 10.0e-10 ) const;
	};


	//! A decibel magnitude spectrum with values that have been transformed into logarithmic scale. Values are mostly between -\infinity and 0, but can also exceed.
	/**
	 * This alias class is used to give the user a hint that the underlying data should be treated as decibel values (log scale),
	 * because a magnitude spectrum does not specify on that. It is used like a CITAMagnitudeSpectrum.
	 */
	class ITA_BASE_API CDecibelMagnitudeSpectrum : public CMagnitudeSpectrum
	{
	public:
		CDecibelMagnitudeSpectrum( const int nNumBands );
		virtual ~CDecibelMagnitudeSpectrum( );

		void SetIdentity( );
		void SetZero( );
		bool IsIdentity( ) const;
		bool IsZero( ) const;
	};

	//! A gain magnitude spectrum with linear values that are greater zero and usually between 0..1, but can also exceed.
	/**
	 * @sa CITAFactorMagnitudeSpectrum
	 */
	class ITA_BASE_API CGainMagnitudeSpectrum : public CMagnitudeSpectrum
	{
	public:
		CGainMagnitudeSpectrum( const int nNumBands );
		virtual ~CGainMagnitudeSpectrum( );

		void SetIdentity( );
		void SetZero( );
		bool IsIdentity( ) const;
		bool IsZero( ) const;
	};

} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_MAGNITUDE_SPECTRUM

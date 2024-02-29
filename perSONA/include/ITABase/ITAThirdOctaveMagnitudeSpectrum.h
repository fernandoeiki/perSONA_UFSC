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

#ifndef INCLUDE_WATCHER_ITA_THIRD_OCTAVE_MAGNITUDE_SPECTRUM
#define INCLUDE_WATCHER_ITA_THIRD_OCTAVE_MAGNITUDE_SPECTRUM

#include <ITABaseDefinitions.h>
#include <ITAConstants.h>
#include <ITAException.h>
#include <ITAMagnitudeSpectrum.h>

namespace ITABase
{
	//! Third octave magnitude spectrum
	/**
	 * ABSTRACT class for third octave magnitude spectra with predefined center frequencies.
	 * Full implementation in derived classes CThirdOctaveGainMagnitudeSpectrum and CThirdOctaveDecibelMagnitudeSpectrum.
	 *
	 * Will raise CITAException on errors.
	 *
	 * @sa CITAWholeOctaveMagnitudeSpectrum
	 */
	class CThirdOctaveMagnitudeSpectrum : public CMagnitudeSpectrum
	{
	public:
		inline CThirdOctaveMagnitudeSpectrum( ) : CMagnitudeSpectrum( GetNumBands( ) ) { m_vfCenterFrequencies = GetCenterFrequencies( ); };

		inline static int GetNumBands( ) { return 31; };

		inline static const std::vector<float>& GetCenterFrequencies( ) { return ITAConstants::THIRD_OCTAVE_CENTER_FREQUENCIES_ISO_F; };

		virtual inline ~CThirdOctaveMagnitudeSpectrum( ) { };

		virtual inline bool CompareEqualValues( const CThirdOctaveMagnitudeSpectrum& oOtherSpectrum, const float fThreshold = 10.0e-10 )
		{
			return CITASpectrum::CompareEqualValues( oOtherSpectrum, fThreshold );
		};

	protected:
		void SetCenterFrequencies( const std::vector<float>& vfCenterFrequencies );
	};


	//! A decibel magnitude spectrum with values that have been transformed into logarithmic scale. Values are mostly between -\infinity and 0, but can also exceed.
	class CThirdOctaveDecibelMagnitudeSpectrum : public CThirdOctaveMagnitudeSpectrum
	{
	public:
		inline CThirdOctaveDecibelMagnitudeSpectrum( )
		    : CThirdOctaveMagnitudeSpectrum( ) {

		    };

		virtual ~CThirdOctaveDecibelMagnitudeSpectrum( ) { };

		inline void SetValueFromFactor( const int iFrequencyBandIndex, const float fFactorValue )
		{
			if( fFactorValue < 0.0f )
				ITA_EXCEPT_INVALID_PARAMETER( "Cannot convert a negative value into a log-scale value" );
			SetValue( iFrequencyBandIndex, std::log10( fFactorValue ) );
		};

		inline void SetValuesFromFactors( const std::vector<float>& vfValues )
		{
			if( vfValues.size( ) != GetNumBands( ) )
				ITA_EXCEPT_INVALID_PARAMETER( "Number of bands and given values are not of same length" );

			for( size_t n = 0; n < m_vfValues.size( ); n++ )
				SetValueFromFactor( int( n ), vfValues[n] );
		};

		inline void SetIdentity( )
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
				m_vfValues[n] = 0.0f;
		};

		inline void SetZero( )
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
				m_vfValues[n] = ITAConstants::MINUS_INFINITY_F;
		};

		inline bool IsIdentity( ) const
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
			{
				if( m_vfValues[n] != 0.0f )
					return false;
			}

			return true;
		};

		inline bool IsZero( ) const
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
			{
				if( m_vfValues[n] != ITAConstants::MINUS_INFINITY_F )
					return false;
			}

			return true;
		};
	};


	//! Implementation of magnitude spectrum for gain values
	class CThirdOctaveGainMagnitudeSpectrum : public CThirdOctaveMagnitudeSpectrum
	{
	public:
		inline CThirdOctaveGainMagnitudeSpectrum( )
		    : CThirdOctaveMagnitudeSpectrum( ) {

		    };

		virtual ~CThirdOctaveGainMagnitudeSpectrum( ) { };

		inline void SetIdentity( )
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
				m_vfValues[n] = 1.0f;
		};

		inline void SetZero( )
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
				m_vfValues[n] = 0.0f;
		};

		inline bool IsIdentity( ) const
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
			{
				if( m_vfValues[n] != 1.0f )
					return false;
			}

			return true;
		};

		inline bool IsZero( ) const
		{
			for( size_t n = 0; n < m_vfValues.size( ); n++ )
			{
				if( m_vfValues[n] != 0.0f )
					return false;
			}

			return true;
		};

		inline CThirdOctaveDecibelMagnitudeSpectrum GetDecibelSpectrum( ) const
		{
			CThirdOctaveDecibelMagnitudeSpectrum oDecibelMagnitudes;
			oDecibelMagnitudes.SetName( GetName( ) );
			oDecibelMagnitudes.SetValueUnit( GetValueUnit( ) );
			oDecibelMagnitudes.SetValuesFromFactors( GetValues( ) );
			return oDecibelMagnitudes;
		};
	};


	//! A factor magnitude spectrum with linear values that are greater zero and usually between 0..1, but can also exceed.
	/**
	 * This alias class is used to give the user a hint that the underlying data should be treated as linear values (factors)
	 * or gains, because a magnitude spectrum does not specify on that. It is used like a CITAThirdOctaveMagnitudeSpectrum.
	 * There is no real difference between a factor and a gain except that gains are commonly used in DSP (i.e. for "gain" control
	 * of audio signal channels) and factors are more common in acoustic materials such as absorption and transmission "factor".
	 */
	typedef CThirdOctaveGainMagnitudeSpectrum CThirdOctaveFactorMagnitudeSpectrum;


} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_THIRD_OCTAVE_MAGNITUDE_SPECTRUM

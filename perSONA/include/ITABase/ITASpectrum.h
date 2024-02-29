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

#ifndef INCLUDE_WATCHER_ITA_SPECTRUM
#define INCLUDE_WATCHER_ITA_SPECTRUM

#include <ITABaseDefinitions.h>
#include <iostream>
#include <string>
#include <vector>

//! Partly abstract scalar spectrum of arbitrary size and base frequencies
/**
 * Class for scalar spectra, intended to be used as a base class for decibel values (magnitudes) or
 * amplitude values (gains) or phase values (radiants, degrees) or group delays etc.
 *
 * Will raise CITAException on errors, also in constructor.
 *
 * @sa CITAHDFTSpectrum for complex-valued spectrum
 *
 */
class ITA_BASE_API CITASpectrum
{
public:
	CITASpectrum( const int nNumBands );
	virtual inline ~CITASpectrum( ) { };

	void SetName( const std::string& sVolatileName );
	std::string GetName( ) const;

	std::string GetValueUnit( ) const;
	void SetValueUnit( const std::string& sUnit );

	int GetNumBands( ) const;

	const std::vector<float>& GetCenterFrequencies( ) const;
	void SetCenterFrequencies( const std::vector<float>& vfCenterFrequencies );

	void SetValues( const std::vector<float>& vfValues );
	void SetValue( const int iFrequencyBandIndex, const float fValue );

	virtual void SetIdentity( )      = 0;
	virtual void SetZero( )          = 0;
	virtual bool IsIdentity( ) const = 0;
	virtual bool IsZero( ) const     = 0;

	//! Get a copy of the values (slow, do not use for read access)
	std::vector<float> GetValuesCopy( ) const;

	//! Get values (read-only)
	const std::vector<float>& GetValues( ) const;

	//! Scalar multiplication
	void Multiply( const float fFactor );

	//! Element-wise multiplication
	void Multiply( const CITASpectrum& oOtherSpetrum );

	//! Scalar addition
	void Add( const float fSummand );

	//! Element-wise addition
	void Add( const CITASpectrum& oOtherSpectrum );

	//! Element-wise subtraction
	void Sub( const CITASpectrum& oOtherSpectrum );

	//! Element-wise inversion (throws ITAException if values are zero)
	void Invert( );

	//! Compare equality of values (ignores center frequencies, but requires matching number of bands)
	bool CompareEqualValues( const CITASpectrum& oOtherSpectrum, const float fThreshold = 10.0e-10 ) const;

	//! Index operator for const values
	const float& operator[]( int iFrequencyBandIndex ) const;

	//! Index operator for actual values
	float& operator[]( int iFrequencyBandIndex );

	//! Set entire values of the spectrum by extrapolating range
	void SetValuesExtrapolated( const std::vector<float>& vfProvidedFrequencies, const std::vector<float>& vfProvidedValues,
	                            const int iStrategy = ITABase::InterpolationFunctions::NONE );


	CITASpectrum& operator*=( const float rhs );
	CITASpectrum& operator*=( const CITASpectrum& rhs );
	CITASpectrum& operator+=( const float rhs );
	CITASpectrum& operator+=( const CITASpectrum& rhs );
	CITASpectrum& operator-=( const float rhs );
	CITASpectrum& operator-=( const CITASpectrum& rhs );

protected:
	std::vector<float> m_vfValues;            //!< Scalar spectrum values of any kind
	std::vector<float> m_vfCenterFrequencies; //!< Base or center frequencies for bands

private:
	std::string m_sName;      //!< Volatile name for output formatting
	std::string m_sValueUnit; //!< Value unit, such as dB, dB(A) ... for output formatting.
};

//! STL stream output operator
ITA_BASE_API std::ostream& operator<<( std::ostream& os, const CITASpectrum& oSpectrum );

#endif // INCLUDE_WATCHER_ITA_SPECTRUM

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

#ifndef INCLUDE_WATCHER_ITA_HDFT_SPECTRA
#define INCLUDE_WATCHER_ITA_HDFT_SPECTRA

// ITA includes
#include <ITABaseDefinitions.h>
#include <ITAException.h>

// STL includes
#include <vector>

namespace ITABase
{
	class CHDFTSpectrum;

	//! Multi-channel half-sided discrete fourier spectra
	/**
	 *
	 * This class describes DFT spectrum data with variable number channels
	 * and provides functionality for manipulation and math operations.
	 *
	 * This class extends the \ITAHDFTSpectrum for multi-channel applications.
	 *
	 */
	class ITA_BASE_API CHDFTSpectra
	{
	public:
		//! Constructor that initializes the
		CHDFTSpectra( const float fSampleRate, const int iNumChannels, const int iDFTSize, const bool bZeroInit = true );

		//! Constructor that uses a non-empty HDFTSpectrum vector
		CHDFTSpectra( const std::vector<CHDFTSpectrum*>& vpSpectrumVec );

		//! Standard destructor
		~CHDFTSpectra( );

		//! Return number of channels
		/**
		 * \return Number of spectra / dimension of filter
		 */
		int GetNumChannels( ) const;

		//! Return DFT size
		/**
		 * \return Number of coeffs + 1 for DC value
		 */
		int GetDFTSize( ) const;

		//! Returns the frequency of a bin by index (0 .. DFT-size - 1)
		float GetFrequencyOfBin( const int iBinIndex ) const;

		//! Return sampling rate
		double GetSampleRate( ) const;

		float GetFrequencyResolution( ) const;

		//! Adds the given spectra channel-wise
		void add( const CHDFTSpectra* );

		//! Subtracts the given spectra channel-wise
		void sub( const CHDFTSpectra* );

		//! Multiplies the given spectra channel-wise
		void mul( const CHDFTSpectra* );

		//! Multiplies the conjugate of the given spectra without data copy channel-wise
		void mul_conj( const CHDFTSpectra* );

		//! Multiplies a scalar
		void mul_scalar( double );

		//! Divides the given spectra channel-wise
		void div( const CHDFTSpectra* );

		//! Set unity (all coefficiants real one)
		void SetUnity( );

		//! Set unity (all coefficiants real one)
		void SetZero( );

		//! Copy from another Spectra
		void CopyFrom( const CHDFTSpectra* otherSpectra );

		//! Returns maximum energy from all spectra
		float GetMaxEnergy( int* piChannelIndex = nullptr ) const;

		//! Subscript operator gives direct access to spectrum channel
		const CHDFTSpectrum* operator[]( const int ) const;
		CHDFTSpectrum* operator[]( const int );

	private:
		//! Standard constructor
		CHDFTSpectra( );

		std::vector<CHDFTSpectrum*> m_vpSpectra; //! DFT spectra
	};
} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_HDFT_SPECTRA

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

#ifndef INCLUDE_WATCHER_ITA_FFT_UTILS
#define INCLUDE_WATCHER_ITA_FFT_UTILS

#include "ITAFFTDefinitions.h"

#include <ITAFiniteImpulseResponse.h>
#include <ITAHDFTSpectra.h>
#include <ITAHDFTSpectrum.h>
#include <ITAMultichannelFiniteImpulseResponse.h>
#include <ITASampleBuffer.h>
#include <ITASampleFrame.h>


namespace ITAFFTUtils
{
	//! Convert a single-channel HDFT spectrum into time-domain representation
	/**
	 * \param[in] pFreqDomainSpectrum HDFT spectrum in frequency domain
	 * \param[out] sfIR Impulse response in time domain
	 * \param[in] bNormalize Normalize time data
	 */
	ITA_FFT_API void Convert( const ITABase::CHDFTSpectrum* pFreqDomainSpectrum, ITASampleBuffer& sfIR );

	//! Convert a multi-channel HDFT spectrum into time-domain representation
	/**
	 * \param[in] pFreqDomainSpectra HDFT spectrum in frequency domain
	 * \param[out] sfIR Impulse response in time domain
	 * \param[in] bNormalize Normalize time data
	 */
	ITA_FFT_API void Convert( const ITABase::CHDFTSpectra* pFreqDomainSpectra, ITASampleFrame& sfIR );


	ITA_FFT_API void Convert( const ITABase::CFiniteImpulseResponse& oIR, ITABase::CHDFTSpectrum* pSpectrum );
	ITA_FFT_API void Convert( const ITABase::CMultichannelFiniteImpulseResponse& oIR, ITABase::CHDFTSpectra* pSpectra );

	//! Export a single-channel HDFT spectrum as a WAV file
	/**
	 * \param[in] pFreqDomainSpectrum HDFT spectra in frequency domain
	 * \param[in] sFilePath File path with or without wav extension
	 * \param[in] bNormalize Normalize time data
	 */
	ITA_FFT_API void Export( const ITABase::CHDFTSpectrum* pFreqDomainSpectrum, const std::string& sFilePath, bool bNormalize = false );

	//! Export a multi-channel HDFT spectrum as a WAV file
	/**
	 * \param[in] pFreqDomainSpectra HDFT spectrum in frequency domain
	 * \param[in] sFilePath File path with or without wav extension
	 * \param[in] bNormalize Normalize time data
	 */
	ITA_FFT_API void Export( const ITABase::CHDFTSpectra* pFreqDomainSpectra, const std::string& sFilePath, bool bNormalize = false );
}; // namespace ITAFFTUtils

#endif // INCLUDE_WATCHER_ITA_FFT_UTILS

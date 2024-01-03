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

#ifndef INCLUDE_WATCHER_ITA_WHOLE_OCTAVE_MAGNITUDE_SPECTRUM
#define INCLUDE_WATCHER_ITA_WHOLE_OCTAVE_MAGNITUDE_SPECTRUM

#include <ITABaseDefinitions.h>
#include <ITAConstants.h>
#include <ITAMagnitudeSpectrum.h>


namespace ITABase
{
	//! Third octave Magnitude spectrum
	/**
	 * Class for third octave magnitude spectra with predefined center frequencies.
	 *
	 * Will raise CITAException on errors.
	 *
	 * @sa
	 *
	 */
	class ITA_BASE_API CWholeOctaveMagnitudeSpectrum : public CMagnitudeSpectrum
	{
	public:
		inline CWholeOctaveMagnitudeSpectrum( ) : CMagnitudeSpectrum( 10 ) { m_vfCenterFrequencies = ITAConstants::OCTAVE_CENTER_FREQUENCIES_ISO_F; };

		virtual inline ~CWholeOctaveMagnitudeSpectrum( ) { };

	protected:
		void SetCenterFrequencies( const std::vector<float>& vfCenterFrequencies );
	};

} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_WHOLE_OCTAVE_MAGNITUDE_SPECTRUM

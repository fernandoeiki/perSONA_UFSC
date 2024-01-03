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

#ifndef INCLUDE_WATCHER_ITA_AUDIO_SAMPLE
#define INCLUDE_WATCHER_ITA_AUDIO_SAMPLE

// ITABase
#include <ITABaseDefinitions.h>
#include <ITASampleFrame.h>
#include <string>

//! Multi-channel audio sample with single precision floating point quantization
/**
 * An audio sample is basically an ITASampleFrame with a given sampling rate.
 */
class ITA_BASE_API CITAAudioSample : public ITASampleFrame
{
public:
	//! Create empty audio sample
	/**
	 * Creates an uninitialized audio sample with given a sampling rate, only.
	 *
	 * @note Requires initialization or load to be used, otherwise methods will throw ITAException.
	 */
	CITAAudioSample( const float fSampleRate = 44100.0f );

	//! Create audio sample from file
	/**
	 * Will load audio sample from file and adopts number of channels and sample rate.
	 *
	 * @param[in] sFilePath Path to audio file
	 *
	 * @note Will raise ITAException on error.
	 */
	CITAAudioSample( const std::string& sFilePath );

	//! Create (empty) audio sample with given parameters
	/**
	 * @param[in] iNumChannels	   Number of channels
	 * @param[in] iLengthSamples	   Number of new samples
	 * @param[in] fSampleRate Sampling rate of audio sample
	 * @param[in] bZeroInit	   Init with zeros
	 */
	explicit CITAAudioSample( const int iNumChannels, const int iLengthSamples, const float fSampleRate, const bool bZeroInit = true );

	//! Copy constructor as pointer
	/**
	 * @param[in] pSource Pointer to source audio sample
	 */
	CITAAudioSample( const CITAAudioSample* pSource );

	//! Copy constructor as reference
	/**
	 * @param[in] pbSource Reference to source audio sample
	 */
	CITAAudioSample( const CITAAudioSample& sbSource );

	virtual inline ~CITAAudioSample( ) { };

	//! Sampling frequency of audio sample
	/**
	 * @return Sampling rate of audio sample
	 *
	 */
	float GetSampleRate( ) const;

	//! Initialize
	/**
	 * (Re-)Initialize an audio sample
	 *
	 * @param[in] iNumChannels	   Number of channels
	 * @param[in] iLengthSamples	   Number of new samples
	 * @param[in] fSampleRate Sampling rate of audio sample
	 * @param[in] bZeroInit	   Init with zeros
	 */
	void Init( const int iNumChannels, const int iLengthSamples, const float fSampleRate, const bool bZeroInit = true );

	//! Read from sample buffer with sample rate conversion, if necessary
	/**
	 * Reads audio samples from sample frame and converts to internal sample rate, if given source sample rate is mismatching.
	 *
	 * @param[in] sfSource Source sample frame
	 * @param[in] fSourceSampleRate Sample rate of source sample frame
	 *
	 */
	void Load( const ITASampleFrame& sfSource, const float fSourceSampleRate );

	//! Read from other audio sample with sample rate conversion, if necessary
	/**
	 * Reads audio samples from sample frame and converts to internal sample rate, if given source sample rate is mismatching.
	 *
	 * @param[in] oSource Source audio sample
	 */
	void Load( const CITAAudioSample& oSource );

	//! Load audio sample from file and adopt it's sample rate
	/**
	 * Will load audio sample from file and adopts number of channels and sample rate.
	 *
	 * @param[in] sFilePath Path to audio file
	 *
	 * @note Will raise ITAException on error.
	 * @sa LoadWithSampleRateConversion()
	 */
	void Load( const std::string& sFilePath );

	//! Load audio sample from file and convert sample rate to internal sample rate, if necessary
	/**
	 * Will load audio sample from file and adopts number of channels but not sample rate. Converts audio samples into internal sampling rate if mismatched.
	 *
	 * @param[in] sFilePath Path to audio file
	 *
	 * @note Will raise ITAException on error.
	 */
	void LoadWithSampleRateConversion( const std::string& sFilePath );

private:
	//! Disable this Init method from sample buffer
	void Init( int, int, bool );

	//! Disable load without sample rate
	void Load( const std::string&, const double& );

	float m_fSampleRate; //!< Sampling rate
};

#endif // INCLUDE_WATCHER_ITA_AUDIO_SAMPLE

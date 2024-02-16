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

#ifndef INCLUDE_WATCHER_ITA_MULTICHANNEL_FINITE_IMPULSE_RESPONSE
#define INCLUDE_WATCHER_ITA_MULTICHANNEL_FINITE_IMPULSE_RESPONSE

// ITABase
#include <ITABaseDefinitions.h>
#include <ITASampleFrame.h>

namespace ITABase
{
	//! Multichannel finite impulse response class / FIR filters
	/**
	 * ITASampleFrame with a sampling rate = multichannel finite impulse response.
	 */
	class ITA_BASE_API CMultichannelFiniteImpulseResponse : public ITASampleFrame
	{
	public:
		//! Create empty FIR filters
		/**
		 * Requires initialization to be used, otherwise methods will throw ITAException.
		 */
		CMultichannelFiniteImpulseResponse( );

		//! Create FIR filter of certain size with given sampling frequency
		/**
		 * \param iLength	Length (size) of buffer in samples
		 */
		explicit CMultichannelFiniteImpulseResponse( const int iNumChannels, const int iLength, const double dSampleRate, const bool bZeroInit = true );

		//! Copy constructor as pointer
		/**
		 * \param pSource Pointer to source buffer
		 */
		CMultichannelFiniteImpulseResponse( const CMultichannelFiniteImpulseResponse* pSource );

		//! Copy constructor as reference
		/**
		 * \param pbSource Reference to source buffer
		 */
		CMultichannelFiniteImpulseResponse( const CMultichannelFiniteImpulseResponse& sbSource );

		virtual inline ~CMultichannelFiniteImpulseResponse( ) { };

		//! Load from file constructor (audiofile)
		/**
		 * Loads FIR data from an audio file.
		 *
		 * @note Will throw ITAException on error.
		 */
		CMultichannelFiniteImpulseResponse( const std::string& sFilePath );

		//! Loads FIR from file (will re-init length, if necessary)
		void LoadFromFile( const std::string& sFilePath );

		void StoreToFile( const std::string& sFilePath ) const;

		//! Sampling frequency of FIR filter (double of Nyquist frequency)
		double GetSampleRate( ) const;

		//! Nyquist frequency of FIR filter (half of sample rate)
		double GetNyquistFrequency( ) const;

		//! Initialize
		/**
		 * (Re-)Initialize a sample buffer
		 *
		 * @param[in] iNumChannels Number of FIR channels
		 * \param iLength	   Number of new samples
		 * @param[in] dSampleRate Sampling rate of FIR filter (double of Nyquist frequency)
		 * \param bZeroInit	   Init with zeros
		 */
		void Init( const int iNumChannels, const int iLength, const double dSampleRate, const bool bZeroInit = true );

	private:
		//! Disable these methods from ITASampleFrame
		void Init( int, int, bool );
		void Load( const std::string& );
		void Load( const std::string&, double& );
		void Store( const std::string&, double );

		double m_dSampleRate; //!< Sampling rate
	};
} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_MULTICHANNEL_FINITE_IMPULSE_RESPONSE

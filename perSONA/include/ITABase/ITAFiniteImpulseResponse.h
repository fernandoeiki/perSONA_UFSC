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

#ifndef INCLUDE_WATCHER_ITA_FINITE_IMPULSE_RESPONSE
#define INCLUDE_WATCHER_ITA_FINITE_IMPULSE_RESPONSE

// ITABase
#include <ITABaseDefinitions.h>
#include <ITASampleBuffer.h>
#include <string>

namespace ITABase
{
	//! Single channel finite impulse response class / FIR filter
	/**
	 * ITASampleBuffer with a sampling rate = finite impulse response.
	 * For multi channel FIR filter, @sa ITAMultichannelFiniteImpulseResponse
	 */
	class ITA_BASE_API CFiniteImpulseResponse : public ITASampleBuffer
	{
	public:
		//! Create empty FIR filter
		/**
		 * Requires initialization to be used, otherwise methods will throw ITAException.
		 */
		CFiniteImpulseResponse( );

		//! Create FIR filter of certain size with given sampling frequency
		/**
		 * \param iLength	Length (size) of buffer in samples
		 */
		explicit CFiniteImpulseResponse( const int iLength, const float fSampleRate, const bool bZeroInit = true );

		//! Copy constructor as pointer
		/**
		 * \param pSource Pointer to source buffer
		 */
		CFiniteImpulseResponse( const CFiniteImpulseResponse* pSource );

		//! Copy constructor as reference
		/**
		 * \param pbSource Reference to source buffer
		 */
		CFiniteImpulseResponse( const CFiniteImpulseResponse& sbSource );

		virtual inline ~CFiniteImpulseResponse( ) { };

		//! Sampling frequency of FIR filter (double of Nyquist frequency)
		float GetSampleRate( ) const;

		//! Nyquist frequency of FIR filter (half of sample rate)
		float GetNyquistFrequency( ) const;

		//! Initialize
		/**
		 * (Re-)Initialize a sample buffer
		 *
		 * @param[in] iLength	   Number of new samples
		 * @param[in] fSampleRate Sampling rate of FIR filter (double of Nyquist frequency)
		 * @param[in] bZeroInit	   Init with zeros
		 */
		void Init( const int iLength, const float fSampleRate, const bool bZeroInit = true );

		//! Set a dirac pulse / delta function (first sample 1 (or amplitude), rest 0)
		void SetDirac( float fAmplitude = 1.0f );

		//! Set a unit step function (all samples 1 (or amplitude))
		void SetUnitStepFunction( float fAmplitude = 1.0f );


	private:
		//! Disable this Init method from sample buffer
		void Init( int, bool );

		float m_fSampleRate; //!< Sampling rate
	};

} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_FINITE_IMPULSE_RESPONSE

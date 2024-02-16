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

#ifndef IW_ITA_DSP_PD_JET_ENGINE
#define IW_ITA_DSP_PD_JET_ENGINE

#include <DspFilters/Butterworth.h>
#include <ITADSPDefinitions.h>
#include <ITAThirdOctaveFilterbank.h>
#include <VistaTools/VistaRandomNumberGenerator.h>
#include <algorithm>
#include <atomic>
#include <tbb/concurrent_queue.h>
#include <vector>

class CITAIIRFilterEngine;
class CITAThirdOctaveFIRFilterGenerator;

namespace ITADSP
{
	namespace PD
	{
		//! Pure data patch implementation of a jet engine
		/**
		 * Manual implementation of the "jet engine" pure data patch (combining "forced flame" and "turbine") from Andy Farnell's Designing Sound
		 */
		class ITA_DSP_API CJetEngine
		{
		public:
			CJetEngine( double dSampleRate = 44100.0f, float fRPMInit = 1000.0f, bool bColdStart = true );
			virtual ~CJetEngine( );

			virtual void SetRPM( float fNewRPM );
			virtual void Process( float* pfOutputBuffer, int iNumSamples );

		protected:
			// We'll protect data exchange between user and audio thread
			// with atomics, but a request, swap & acknowledge approach with
			// mutex / locking would be more elegant
			struct CAudioContext
			{
				std::atomic<float> vfRPM;
				std::vector<float> vfTurbineModeFrequencies;
				std::vector<float> vfTurbineModePhaseShift;
			} oCtxAudio;

			float GetRPMNormalized( float fRPM ) const;

		private:
			VistaRandomNumberGenerator oRNG;
			Dsp::SimpleFilter<Dsp::Butterworth::BandPass<1>, 1> m_oForcedFlameBP1, m_oForcedFlameBP2, m_oForcedFlameBP3;
			Dsp::SimpleFilter<Dsp::Butterworth::HighPass<1>, 1> m_oForcedFlameHP1;
			Dsp::SimpleFilter<Dsp::Butterworth::LowPass<1>, 1> m_oJetEngineLP1, m_oJetEngineLP2;

			std::vector<float> m_vfTurbineBaseModeFrequencies, m_vfTurbineBaseModeAmplitudes, m_vfRPMRange;

			float m_fTempSample;
			double m_dSampleRate;
		};
	} // namespace PD
} // namespace ITADSP

#endif // IW_ITA_DSP_PD_JET_ENGINE

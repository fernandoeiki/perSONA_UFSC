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

#ifndef IW_ITA_DSP_THIRD_OCTAVE_FILTERBANK_IIR_BURG
#define IW_ITA_DSP_THIRD_OCTAVE_FILTERBANK_IIR_BURG

#include <ITADSPDefinitions.h>
#include <ITAThirdOctaveFilterbank.h>
#include <tbb/concurrent_queue.h>
#include <vector>

class CITAIIRFilterEngine;
class CITAThirdOctaveFIRFilterGenerator;

namespace ITADSP
{
	namespace ThirdOctaveFilterbank
	{
		//! Third-octave filterbank realisation using IIR filter structur und Burg coefficient design
		/**
		 * Diese Klasse realisiert eine Terzfilterbank (#CVAThirdOctaveFilterbank) mit der Methode der direct form II
		 * für Verstärkungsfaktoren eines Terzbank-Betragsspektrums (#CVAThirdOctaveMagnitudes).
		 *
		 */
		class ITA_DSP_API CIIRBurg : public CITAThirdOctaveFilterbank
		{
		public:
			//! Konstruktor mit Samplerate und Blocklänge
			/**
			 * \param dSamplerate Samplingrate
			 * \param iBlocklength Blocklänge
			 */
			CIIRBurg( const double dSampleRate, const int iBlockLength, const int iFilterOrder = 4 );

			//! Destruktor
			virtual ~CIIRBurg( );

			//! Verstärkungen (Gains) setzen
			/**
			 * \param oGains Verstärkungsfaktoren
			 * \param bSmoothChangeover Wenn true, dann überblenden (default), sonst sofort internen Gain umschalten
			 */
			void SetMagnitudes( const ITABase::CThirdOctaveGainMagnitudeSpectrum& oGains, const bool );


			//! Alle internen Zustände zurücksetzen (Akkumulatoren der Biquads)
			void Clear( );

			//! Verarbeite Samples (Filtern)
			/**
			 * \param pfInputSamples Eingabesamples (Anzahl = Blocklänge)
			 * \param pfOutputSamples Ausgabesamples (Anzahl = Blocklänge)
			 */
			void Process( const float* pfInputSamples, float* pfOutputSamples );

		private:
			int m_iBlockLength; //!< Blocklänge

			CITAIIRFilterEngine* m_pFilterEngine;
			CITAThirdOctaveFIRFilterGenerator* m_pFilterGenerator;
		};
	} // namespace ThirdOctaveFilterbank
} // namespace ITADSP

#endif // IW_ITA_DSP_THIRD_OCTAVE_FILTERBANK_IIR_BURG

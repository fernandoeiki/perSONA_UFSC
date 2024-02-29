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

#ifndef IW_ITA_THIRD_OCTAVE_FILTERBANK_FIR
#define IW_ITA_THIRD_OCTAVE_FILTERBANK_FIR

#include <ITAFastMath.h>
#include <ITAThirdOctaveFIRFilterGenerator.h>
#include <ITAThirdOctaveFilterbank.h>
#include <ITAUPFilter.h>
#include <cassert>

class ITAUPConvolution;

//! Terzfilterbank mittels Dynamic Single-Channel Blockfalter (FIR Filter)
class ITA_DSP_API CITAThirdOctaveFilterbankFIR : public CITAThirdOctaveFilterbank
{
public:
	CITAThirdOctaveFilterbankFIR( const double dSampleRate, const int iBlockLength );

	virtual ~CITAThirdOctaveFilterbankFIR( );

	virtual void SetIdentity( const bool bSmoothChangeover = true );
	virtual void SetMagnitudes( const ITABase::CThirdOctaveGainMagnitudeSpectrum& oMags, const bool bSmoothChangeover = true );
	int GetLatency( ) const;
	virtual void Clear( );
	virtual void Process( const float* pfInputSamples, float* pfOutputSamples );

private:
	int m_iBlocklength;
	int m_iConvolutionTaps;
	int m_iGeneratorFilterLength;
	std::vector<float> m_vfGeneratedFIR;
	CITAThirdOctaveFIRFilterGenerator* m_pGenerator;
	ITAUPConvolution* m_pConvolver;
};

#endif // IW_ITA_THIRD_OCTAVE_FILTERBANK_FIR

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

#ifndef IW_ITA_IIR_FILTER_GENERATOR
#define IW_ITA_IIR_FILTER_GENERATOR

#include <ITADSPDefinitions.h>
#include <ITAFiniteImpulseResponse.h>
#include <ITAIIRCoefficients.h>

namespace ITADSP
{
	//! Implements digital biquad component for IIR filtering
	/**
	 * @todo jst: translate comments to English.
	 *
	 * Diese Klasse realisiert ein Biquad IIR Filter. Es hat einen globalen Verstärkungsfaktor (Gain),
	 * damit eine Kaskadierung vieler Biquads zur Bandfilterung benutzt werden kann.
	 * Die Umsetzung erfolgt in Kanonischer Form, um möglichst wenig Multiplizierer/Addierer und
	 * Verzögerer zu benutzen.
	 */
	namespace IIRFilterGenerator
	{
		ITA_DSP_API void Yulewalk( const ITABase::CFiniteImpulseResponse &oIR, CFilterCoefficients &oCoeffs );

		ITA_DSP_API void Burg( const ITABase::CFiniteImpulseResponse &oIR, CFilterCoefficients &oCoeffs );

		ITA_DSP_API float InnerProduct( const float *x, const float *y, const int length );

		ITA_DSP_API void numf( );

		ITA_DSP_API void denf( float *A, const ITASampleBuffer &R, int na );

		ITA_DSP_API void toeplitz( float **out, const ITASampleBuffer &row, const ITASampleBuffer &column );

		ITA_DSP_API void toeplitz( float **out, const ITASampleBuffer &in, int na );

	} // namespace IIRFilterGenerator
} // namespace ITADSP

#endif // IW_ITA_IIR_FILTER_GENERATOR

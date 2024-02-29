/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
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
 *		Svensson diffraction model based on Biot-Tolstoy exact
 *      solution and the extension by Medwin.
 *
 */

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_SVENSSON
#define INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_SVENSSON

#include "Definitions.h"

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes
#include <ITAConstants.h>
#include <ITAFiniteImpulseResponse.h>
#include <ITAGeo/Base.h>
#include <ITASampleBuffer.h>


namespace ITAPropagationModels
{
	namespace Svensson
	{
		//! Calculates the impulse response of Svensson diffraction model for a given constellation
		/**
		 * @sa Svensson, P.; Fred, R. & Vanderkooy, J.; An analytic secondary source model of edge diffraction impulse responses; J. Acoust. Soc. Am., 1999, 106, 2331
		 *
		 * @param[in] v3SourcePos Source position (outside wedge), rojected position may have to be used for correct distances!
		 * @param[in] v3TargetPos target position (outside wedge)
		 * @param[in] pApex Aperture point including wedge parameters (angles, etc)
		 * @param[out] oEffectiveDiffractionIR Effective impulse response for diffraction part of sound path from source to target (not including delay)
		 *
		 * @sa GetMinimumWavefrontDelayTime, GetMaximumWavefrontDelayTime
		 */
		ITA_PROPAGATION_MODELS_API bool CalculateDiffractionIR( const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos,
		                                                        std::shared_ptr<const ITAGeo::CITADiffractionWedgeApertureBase> pApex,
		                                                        ITABase::CFiniteImpulseResponse& oEffectiveDiffractionIR,
		                                                        const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );
	} // namespace Svensson
} // namespace ITAPropagationModels

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_SVENSSON

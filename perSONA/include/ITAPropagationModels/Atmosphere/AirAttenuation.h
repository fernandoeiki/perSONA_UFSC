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
 */

#ifndef IW_ITA_PROPAGATION_MODELS_AIR_ATTENUATION
#define IW_ITA_PROPAGATION_MODELS_AIR_ATTENUATION

// ITAPropagationModel includes
#include <ITAPropagationModels/Definitions.h>

// ITA includes
#include <ITAGeo/Atmosphere/StratifiedAtmosphere.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/Rays.h>
#include <ITAThirdOctaveMagnitudeSpectrum.h>

// STL includes

namespace ITAPropagationModels
{
	namespace Atmosphere
	{
		//! Returns a third octave magnitude spectrum containing a filter describing the effects of attenuation due to sound propagation through the atmosphere
		/**
		 * Evaluates and accumulates the air attenuation between adjacent ray points according to ISO 9613.
		 * The result contains factors representing the remaining portion of sound pressure after sound travelled along the ray path.
		 * Optionally, a downsampling factor can be given to the function in order to only evaluate for every x-th ray point.
		 */
		ITA_PROPAGATION_MODELS_API ITABase::CThirdOctaveFactorMagnitudeSpectrum AirAttenuationSpectrum( const ITAPropagationPathSim::AtmosphericRayTracing::CRay& oRay,
		                                                                                                const ITAGeo::CStratifiedAtmosphere& oAtmosphere,
		                                                                                                const int iDownSamplingFactor = 1 );

		//! Writes a third octave magnitude spectrum containing a filter describing the effects of attenuation due to sound propagation through the atmosphere
		/**
		 * Evaluates and accumulates the air attenuation between adjacent ray points according to ISO 9613.
		 * The result contains factors representing the remaining portion of sound pressure after sound travelled along the ray path.
		 * Optionally, a downsampling factor can be given to the function in order to only evaluate for every x-th ray point.
		 */
		ITA_PROPAGATION_MODELS_API void AirAttenuationSpectrum( ITABase::CThirdOctaveFactorMagnitudeSpectrum& outputSpectrum,
		                                                        const ITAPropagationPathSim::AtmosphericRayTracing::CRay& oRay,
		                                                        const ITAGeo::CStratifiedAtmosphere& oAtmosphere, const int iDownSamplingFactor = 1 );
	} // namespace Atmosphere
} // namespace ITAPropagationModels

#endif // IW_ITA_PROPAGATION_MODELS_AIR_ATTENUATION

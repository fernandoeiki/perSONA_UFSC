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

#ifndef IW_ITA_GEO_DIRECTIVITY_UTILS
#define IW_ITA_GEO_DIRECTIVITY_UTILS

#ifdef THIRD_OCTAVE
#	undef THIRD_OCTAVE
#endif

// ITAGeo includes
#include "../Definitions.h"
#include "Base.h"

#include <ITAConstants.h>

// STL includes
#include <memory>

namespace ITAGeo
{
	namespace Directivity
	{
		namespace Utils
		{
			ITA_GEO_API float EstimateFilterLengthSamples( std::shared_ptr<const IDirectivity> pMaterial, const float fSampleRate,
			                                               const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );
		}
	} // namespace Directivity
} // namespace ITAGeo

#endif // IW_ITA_GEO_DIRECTIVITY_UTILS

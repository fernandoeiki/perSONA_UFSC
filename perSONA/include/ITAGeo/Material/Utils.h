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

#ifndef IW_ITA_GEO_MATERIAL_UTILS
#define IW_ITA_GEO_MATERIAL_UTILS

#ifdef THIRD_OCTAVE
#	undef THIRD_OCTAVE
#endif

// ITAGeo includes
#include "../Definitions.h"
#include "Material.h"

// STL includes
#include <memory>
#include <string>
#include <vector>

namespace ITAGeo
{
	namespace Material
	{
		namespace Utils
		{
			ITA_GEO_API float EstimateFilterLengthSamples( std::shared_ptr<const IMaterial> pMaterial, const float fSampleRate,
			                                               const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );
		}
	} // namespace Material
} // namespace ITAGeo

#endif // IW_ITA_GEO_ACOUSTIC_MATERIAL

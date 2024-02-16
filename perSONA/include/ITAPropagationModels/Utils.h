/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 * 				    ____  __________  _______
 *				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 *				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 * ----------------------------------------------------------------
 *
 */

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_UTILS
#define INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_UTILS

#include "Definitions.h"

#include <ITAConstants.h>
#include <ITAGeo/Base.h>

namespace ITAPropagationModels
{
	namespace Utils
	{
		//! Estimates the required filter length on a best guess approach and by using path length and directivities / meterials into account
		/**
		 * @note Set the minimum at least to the block length of your audio stream
		 */
		ITA_PROPAGATION_MODELS_API float EstimateFilterLengthSamples( const ITAGeo::CPropagationPath& oPath, const float fSampleRate, const float fMinimumSamples = 64,
		                                                              const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );
	} // namespace Utils
} // namespace ITAPropagationModels

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_UTILS

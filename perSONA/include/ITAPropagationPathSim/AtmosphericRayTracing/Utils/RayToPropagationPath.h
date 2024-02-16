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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_UTILS_RAYTOPROPAGATIONPATH
#define IW_ITA_PROPAGATIONPATHSIM_ART_UTILS_RAYTOPROPAGATIONPATH

#include <ITAPropagationPathSim/Definitions.h>

// ITA includes
#include <ITAGeo/Base.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/Rays.h>

// STD
#include <memory>
#include <vector>

namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		namespace Utils
		{
			ITA_PROPAGATION_PATH_SIM_API ITAGeo::CPropagationPath ToPropagationPath( const CRay& ray );

			ITA_PROPAGATION_PATH_SIM_API ITAGeo::CPropagationPathList ToPropagationPath( const std::vector<std::shared_ptr<CRay>>& vpRays );
		} // namespace Utils
	}     // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_UTILS_RAYTOPROPAGATIONPATH
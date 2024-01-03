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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_ENGINE
#define IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_ENGINE

#include <ITAPropagationPathSim/Definitions.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes
#include <ITAGeo/Atmosphere/StratifiedAtmosphere.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/EigenraySearch/EigenraySettings.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/Rays.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/Simulation/ARTSettings.h>

// STD
#include <memory>
#include <vector>


namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		namespace EigenraySearch
		{
			class ITA_PROPAGATION_PATH_SIM_API CEngine
			{
			public:
				EigenraySearch::Settings eigenraySettings;
				Simulation::Settings simulationSettings;

			public:
				inline CEngine( ) { };

				std::vector<std::shared_ptr<CRay>> Run( const ITAGeo::CStratifiedAtmosphere& atmosphere, const VistaVector3D& sourcePosition,
				                                        const VistaVector3D& receiverPosition ) const;
			};
		} // namespace EigenraySearch
	}     // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_ENGINE
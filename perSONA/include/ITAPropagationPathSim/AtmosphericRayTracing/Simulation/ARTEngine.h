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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_ENGINE
#define IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_ENGINE

#include <ITAPropagationPathSim/Definitions.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes
#include <ITAGeo/Atmosphere/StratifiedAtmosphere.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/Rays.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/Simulation/ARTSettings.h>

// STD
#include <memory>
#include <set>
#include <vector>

namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		namespace Simulation
		{
			class ITA_PROPAGATION_PATH_SIM_API CEngine
			{
			public:
				std::shared_ptr<IExternalWatcher> pExternalWatcher; //!< Reference to externally defined abort criterion.
				Simulation::Settings settings;

			public:
				inline CEngine( ) { pExternalWatcher = std::make_shared<CAbortAtMaxTime>( ); };
				inline CEngine( std::shared_ptr<IExternalWatcher> pWatcher ) : pExternalWatcher( pWatcher ) { };

			public:
				std::vector<std::shared_ptr<CRay>> Run( const ITAGeo::CStratifiedAtmosphere& atmosphere, const VistaVector3D& m_v3SourcePosition,
				                                        const std::vector<VistaVector3D>& v3RayDirections ) const;
				void Run( const ITAGeo::CStratifiedAtmosphere& atmosphere, const std::set<std::shared_ptr<CRay>>& rays ) const;

			private:
				void TraceRays( const ITAGeo::CStratifiedAtmosphere& atmosphere, const std::vector<std::shared_ptr<CRay>>& rays ) const;
			};
		} // namespace Simulation
	}     // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_ENGINE
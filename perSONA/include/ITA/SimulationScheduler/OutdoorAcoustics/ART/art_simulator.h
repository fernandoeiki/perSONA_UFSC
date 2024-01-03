#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_ART_SIMULATOR
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_ART_SIMULATOR

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// std includes
#include <memory>
#include <string>
//#include <type_traits>

// simulation scheduler includes
#include <ITA/SimulationScheduler/OutdoorAcoustics/outdoor_simulator_interface.h>

// ART includes
#include <ITAGeo/Atmosphere/StratifiedAtmosphere.h>
#include <ITAPropagationPathSim/AtmosphericRayTracing/EigenraySearch/EigenrayEngine.h>

using namespace ITAGeo;
using namespace ITAPropagationPathSim ::AtmosphericRayTracing;
namespace ITA
{
	namespace SimulationScheduler
	{
		namespace OutdoorAcoustics
		{
			namespace ART
			{
				//! \brief Simulator using the Atmospheric Ray Tracing framework from ITAGeometricalAcoustics.
				/**
				 * This Simulator uses a single Atmosphere::EigenraySearch::Engine instance.
				 * The simulation is run synchronous/blocking. Thus, only one simulation can be run at the same time.
				 */
				class ITA_SIMULATION_SCHEDULER_API CARTSimulator : public OutdoorAcoustics::ISimulatorInterface
				{
				public:
					//! \brief Configuration class for a outdoor acoustics simulator.
					struct ITA_SIMULATION_SCHEDULER_API ARTSimulatorConfig : public ISimulatorInterface::SimulatorConfig
					{
						inline explicit ARTSimulatorConfig( ) { };

						VistaPropertyList Store( ) const override;
						void Load( const VistaPropertyList& oProperties ) override;

						CoordinateSystem eClientCoordinateSystem = CoordinateSystem::Cartesian; //!< 0 = Cartesian, 1 = OpenGL
						std::string sJsonAtmosphere              = "";                          //!< Either JSON formatted string or path to atmosphere JSON file.
					};


					CARTSimulator( const ARTSimulatorConfig& oConfig );

					CARTSimulator( const CARTSimulator& other ) = delete;
					CARTSimulator( CARTSimulator&& other )      = delete;
					CARTSimulator& operator=( const CARTSimulator& other ) = delete;
					CARTSimulator& operator=( CARTSimulator&& other ) = delete;


					static std::unique_ptr<ISimulatorInterface> Create( std::shared_ptr<const ISimulatorInterface::SimulatorConfig> );

					//! \brief Reset the simulator.
					inline void Reset( ) override { };

					//! \brief Simulate the given task.
					std::unique_ptr<COutdoorSimulationResult> Compute( std::unique_ptr<CUpdateScene> pSceneUpdate ) override;

					static std::string GetType( ) { return "ARTSimulator"; };

				private:
					static VistaVector3D OpenGLToCart( const VistaVector3D& v3In );
					static VistaVector3D CartToOpenGL( const VistaVector3D& v3In );

				private:
					//! \brief Coordinate system used by client (e.g. VA)
					CoordinateSystem m_eClientCoordinateSystem;

					//! \brief ART Eigenray-Engine instance.
					EigenraySearch::CEngine m_oEngine;

					//! \brief Stratified atmosphere
					CStratifiedAtmosphere m_oAtmosphere;

					std::unique_ptr<CUpdateScene> m_pSceneUpdate;
				};

			} // namespace ART
		}     // namespace OutdoorAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_ART_SIMULATOR
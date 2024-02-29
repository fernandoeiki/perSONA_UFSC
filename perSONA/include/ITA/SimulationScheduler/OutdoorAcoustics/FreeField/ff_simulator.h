#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_URBAN_FREEFIELD
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_URBAN_FREEFIELD

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// std includes
#include <memory>
#include <string>

// simulation scheduler includes
#include <ITA/SimulationScheduler/OutdoorAcoustics/outdoor_simulator_interface.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace OutdoorAcoustics
		{
			namespace FreeField
			{
				//! \brief Simulator using the Atmospheric Ray Tracing framework from ITAGeometricalAcoustics.
				/**
				 * This Simulator uses a single Atmosphere::EigenraySearch::Engine instance.
				 * The simulation is run synchronous/blocking. Thus, only one simulation can be run at the same time.
				 */
				class ITA_SIMULATION_SCHEDULER_API CFreeFieldSimulator : public OutdoorAcoustics::ISimulatorInterface
				{
				public:
					//! \brief Configuration class for a outdoor acoustics simulator.
					struct ITA_SIMULATION_SCHEDULER_API FreeFieldSimulatorConfig : public ISimulatorInterface::SimulatorConfig
					{
						inline explicit FreeFieldSimulatorConfig( ) { };

						VistaPropertyList Store( ) const override;
						void Load( const VistaPropertyList& oProperties ) override;

						CoordinateSystem eClientCoordinateSystem = CoordinateSystem::Cartesian; //!< 0 = Cartesian, 1 = OpenGL

						double dSpeedOfSound = 343;
					};


					CFreeFieldSimulator( const FreeFieldSimulatorConfig& oConfig );

					CFreeFieldSimulator( const CFreeFieldSimulator& other ) = delete;
					CFreeFieldSimulator( CFreeFieldSimulator&& other )      = delete;
					CFreeFieldSimulator& operator=( const CFreeFieldSimulator& other ) = delete;
					CFreeFieldSimulator& operator=( CFreeFieldSimulator&& other ) = delete;


					static std::unique_ptr<ISimulatorInterface> Create( std::shared_ptr<const ISimulatorInterface::SimulatorConfig> );

					//! \brief Reset the simulator.
					inline void Reset( ) override { };

					//! \brief Simulate the given task.
					std::unique_ptr<COutdoorSimulationResult> Compute( std::unique_ptr<CUpdateScene> pSceneUpdate ) override;

					inline static std::string GetType( ) { return "FreeFieldSimulator"; };

				private:
					inline static VistaVector3D OpenGLToCart( const VistaVector3D& v3In ) { return VistaVector3D( v3In[Vista::X], -v3In[Vista::Z], v3In[Vista::Y] ); };

					inline static VistaVector3D CartToOpenGL( const VistaVector3D& v3In ) { return VistaVector3D( v3In[Vista::X], v3In[Vista::Z], -v3In[Vista::Y] ); };

				private:
					//! \brief Coordinate system used by client (e.g. VA)
					CoordinateSystem m_eClientCoordinateSystem;

					std::unique_ptr<CUpdateScene> m_pSceneUpdate;

					FreeFieldSimulatorConfig m_oInitialConfig;
				};

			} // namespace FreeField
		}     // namespace OutdoorAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_URBAN_FREEFIELD
#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_URBAN_SIMULATOR
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_URBAN_SIMULATOR

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// std includes
#include <memory>
#include <string>
//#include <type_traits>

// simulation scheduler includes
#include <ITA/SimulationScheduler/OutdoorAcoustics/outdoor_simulator_interface.h>
#include <ITAPropagationPathSim/CombinedModel/PropagationEngine.h>

// Urban includes

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace OutdoorAcoustics
		{
			namespace Urban
			{
				//! \brief Simulator using the Atmospheric Ray Tracing framework from ITAGeometricalAcoustics.
				/**
				 * This Simulator uses a single Atmosphere::EigenraySearch::Engine instance.
				 * The simulation is run synchronous/blocking. Thus, only one simulation can be run at the same time.
				 */
				class ITA_SIMULATION_SCHEDULER_API CUrbanSimulator : public OutdoorAcoustics::ISimulatorInterface
				{
				public:
					//! \brief Configuration class for a outdoor acoustics simulator.
					struct ITA_SIMULATION_SCHEDULER_API UrbanSimulatorConfig : public ISimulatorInterface::SimulatorConfig
					{
						inline explicit UrbanSimulatorConfig( ) { };

						VistaPropertyList Store( ) const override;
						void Load( const VistaPropertyList& oProperties ) override;

						CoordinateSystem eClientCoordinateSystem = CoordinateSystem::Cartesian; //!< 0 = Cartesian, 1 = OpenGL
						std::string sJSONGeometryFilePath;

						double dSpeedOfSound;
						int iMaxReflectionOrder;
						int iMaxDiffractionOrder;
					};


					CUrbanSimulator( const UrbanSimulatorConfig& oConfig );

					CUrbanSimulator( const CUrbanSimulator& other ) = delete;
					CUrbanSimulator( CUrbanSimulator&& other )      = delete;
					CUrbanSimulator& operator=( const CUrbanSimulator& other ) = delete;
					CUrbanSimulator& operator=( CUrbanSimulator&& other ) = delete;


					static std::unique_ptr<ISimulatorInterface> Create( std::shared_ptr<const ISimulatorInterface::SimulatorConfig> );

					//! \brief Reset the simulator.
					inline void Reset( ) override { };

					//! \brief Simulate the given task.
					std::unique_ptr<COutdoorSimulationResult> Compute( std::unique_ptr<CUpdateScene> pSceneUpdate ) override;

					inline static std::string GetType( ) { return "UrbanSimulator"; };

				private:
					inline static VistaVector3D OpenGLToISO( const VistaVector3D& v3In ) { return VistaVector3D( v3In[Vista::X], -v3In[Vista::Z], v3In[Vista::Y] ); };

					inline static VistaVector3D ISOToOpenGL( const VistaVector3D& v3In ) { return VistaVector3D( v3In[Vista::X], v3In[Vista::Z], -v3In[Vista::Y] ); };

				private:
					//! \brief Coordinate system used by client (e.g. VA)
					CoordinateSystem m_eClientCoordinateSystem;
					std::shared_ptr<ITAPropagationPathSim::CombinedModel::CPathEngine> m_pPathEngine;

					std::shared_ptr<ITAGeo::Halfedge::CMeshModelList> m_pMeshModelList; //! Static geo model

					std::shared_ptr<ITAGeo::CSensor> m_pSensor;
					std::shared_ptr<ITAGeo::CEmitter> m_pEmitter;

					std::unique_ptr<CUpdateScene> m_pSceneUpdate;

					UrbanSimulatorConfig m_oInitialConfig;
				};

			} // namespace Urban
		}     // namespace OutdoorAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_URBAN_SIMULATOR
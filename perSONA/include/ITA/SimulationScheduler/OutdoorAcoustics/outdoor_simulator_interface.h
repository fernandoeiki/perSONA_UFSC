#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_SIMULATOR_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_SIMULATOR_INTERFACE

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// std includes
#include <functional>
#include <memory>
#include <string>

// simulation scheduler includes
#include <ITA/SimulationScheduler/OutdoorAcoustics/outdoor_simulation_result.h>
#include <ITA/SimulationScheduler/config_interface.h>
#include <ITA/SimulationScheduler/update_scene.h>


namespace ITA
{
	namespace SimulationScheduler
	{
		namespace OutdoorAcoustics
		{
			//! \brief Interface to a Simulator for outdoor acoustics.
			/**
			 * Defines the basic methods - especially running a simulation - to be used by the outdoor acoustic workers
			 */
			class ITA_SIMULATION_SCHEDULER_API ISimulatorInterface
			{
			public:
				//! \brief Configuration class for a outdoor acoustics simulator.
				struct ITA_SIMULATION_SCHEDULER_API SimulatorConfig : public IConfig
				{
					explicit SimulatorConfig( );
					explicit SimulatorConfig( const std::string& sType );
					SimulatorConfig( const SimulatorConfig& other );
					SimulatorConfig& operator=( const SimulatorConfig& other );

					VistaPropertyList Store( ) const override;
					void Load( const VistaPropertyList& oProperties ) override;

					const std::string& sSimulatorType;

				private:
					std::string m_sSimulatorType;
				};


				//! \brief Reset the outdoor acoustics simulator.
				virtual void Reset( ) = 0;

				//! \brief Simulate the given task.
				virtual std::unique_ptr<COutdoorSimulationResult> Compute( std::unique_ptr<CUpdateScene> pSceneUpdate ) = 0;

				//! Static methods to be implemented by derived simulators for factory purposes
				// static std::unique_ptr<ISimulatorInterface> Create(const std::shared_ptr <ISimulatorInterface::SimulatorConfig>&);
				// static std::string GetType();
			};


			///
			/// \brief Factory class for outdoor acoustic simulators.
			///
			/// This class implements an extensible factory for outdoor acoustic simulators.
			/// After a type of simulator is registered with its IWorkerInterface::createWorker, it can be created using this factory.
			/// \todo Add a way to get the correct config from the type. The factory already knows of all possible workers.
			///
			class ITA_SIMULATION_SCHEDULER_API CSimulatorFactory
			{
			public:
				//! \brief The function signature for a create function.
				typedef std::function<std::unique_ptr<ISimulatorInterface>( const std::shared_ptr<ISimulatorInterface::SimulatorConfig>& )> CreateCallback;

				//! \brief The function signature for a config create function.
				typedef std::function<std::shared_ptr<ISimulatorInterface::SimulatorConfig>( )> ConfigCreateCallback;


				//! \brief Register a type of simulator to the factory.
				static void RegisterSimulator( const std::string& type, CreateCallback createFunction, ConfigCreateCallback configCreateFunction );

				//! \brief Unregister a type of simulator from the factory.
				static void UnregisterSimulator( const std::string& type );


				//! \brief Factory method for simulators.
				//! \param pConfig the configuration for the worker.
				//! \param pParent the parent scheduler.
				//! \return a pointer to the created worker.
				static std::unique_ptr<ISimulatorInterface> CreateSimulator( const std::shared_ptr<ISimulatorInterface::SimulatorConfig>& pConfig );

				//! \brief Factory method for corresponding configs.
				//! \param sType the configuration for the filter.
				//! \return a pointer to the created filter config.
				static std::shared_ptr<ISimulatorInterface::SimulatorConfig> CreateConfig( const std::string& sType );

			private:
				//! \brief Map containing all creation functions.
				static std::map<std::string, std::pair<CreateCallback, ConfigCreateCallback> > m_mRegisteredSimulatorTypes;
			};

		} // namespace OutdoorAcoustics
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_SIMULATOR_INTERFACE
#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_WORKER_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_WORKER_INTERFACE

// std includes
#include <functional>
#include <memory>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/config_interface.h>
#include <ITA/SimulationScheduler/update_scene.h>


namespace ITA
{
	namespace SimulationScheduler
	{
		class ISchedulerInterface;

		///
		/// \brief Interface for worker.
		///
		/// A worker is used by the scheduler to simulate an update.
		/// When an update is passed to a worker, it is imitatively simulated.
		/// The simulation is blocking.
		/// When the simulation is finished, the result is passed back to the scheduler.
		///
		/// A worker is created by CWorkerFactory.
		/// For this, a function like this is necessary:
		/// \code{.cpp}
		/// ///
		/// /// \brief Factory function for a worker.
		/// /// \remark This function should to be static when overwritten.
		/// ///
		/// static std::unique_ptr<IWorkerInterface> createWorker ( const std::shared_ptr<IWorkerInterface::WorkerConfig>& pConfig, CScheduler* pParent );
		/// \endcode
		///
		class ITA_SIMULATION_SCHEDULER_API IWorkerInterface
		{
		public:
			///
			/// \brief Base configuration class for worker.
			///
			/// \note ::sWorkerType is a read only property of the WorkerConfig.
			/// Due to this the copy constructor and assignment operator are needed.
			///
			struct ITA_SIMULATION_SCHEDULER_API WorkerConfig : public IConfig
			{
				WorkerConfig( );

				explicit WorkerConfig( std::string sType );

				WorkerConfig( const WorkerConfig& other );

				WorkerConfig& operator=( const WorkerConfig& other );

				const std::string& sWorkerType;

				VistaPropertyList Store( ) const override = 0;

				void Load( const VistaPropertyList& oProperties ) override = 0;

			private:
				std::string m_sWorkerType;
			};

			///
			/// \brief Constructor for IWorkerInterface.
			/// \param pParent the parent scheduler of the worker.
			///
			IWorkerInterface( ISchedulerInterface* pParent );

			virtual ~IWorkerInterface( ) = default;

			///
			/// \brief Checks if the worker is busy.
			/// \return true if the worker is busy, else false.
			///
			virtual bool IsBusy( ) = 0;

			///
			/// \brief Push a new update to the worker.
			///
			/// After a new Update is pushed to a worker, the update gets simulated immediately.
			/// \note This method takes ownership of the update.
			/// \param pUpdateMessage the new update for the scheduler.
			///
			virtual void PushUpdate( std::unique_ptr<CUpdateScene> pUpdateMessage ) = 0;

			///
			/// \brief Reset the worker.
			///
			virtual void Reset( ) = 0;

			///
			/// \brief Shutdown the worker safely.
			///
			virtual void Shutdown( ) = 0;

		protected:
			///
			/// \brief Pointer to the parent scheduler.
			///
			/// Via this pointer the result of the simulation is passed to the parent scheduler.
			///
			ISchedulerInterface* m_pParentScheduler = nullptr;
		};


		///
		/// \brief Factory class for Worker.
		///
		/// This class implements an extensible factory for worker.
		/// After a type of worker is registered with its IWorkerInterface::createWorker, it can be created using this factory.
		/// \todo Add a way to get the correct config from the type. The factory already knows of all possible workers.
		///
		class ITA_SIMULATION_SCHEDULER_API CWorkerFactory
		{
		public:
			///
			/// \brief The function signature for a create function.
			///
			typedef std::function<std::unique_ptr<IWorkerInterface>( const std::shared_ptr<IWorkerInterface::WorkerConfig>&, ISchedulerInterface* )> CreateCallback;

			///
			/// \brief The function signature for a config create function.
			///
			typedef std::function<std::shared_ptr<IWorkerInterface::WorkerConfig>( )> ConfigCreateCallback;

			///
			/// \brief Register a type of worker to the factory.
			/// \param type name of the worker type to be registered.
			/// \param createFunction the corresponding create function.
			/// \param configCreateFunction the corresponding config create function.
			///
			static void RegisterWorker( const std::string& type, CreateCallback createFunction, ConfigCreateCallback configCreateFunction );

			///
			/// \brief Unregister a type of worker from the factory.
			/// \param type name of the worker type to be removed.
			///
			static void UnregisterWorker( const std::string& type );

			///
			/// \brief Factory method.
			/// \param pConfig the configuration for the worker.
			/// \param pParent the parent scheduler.
			/// \return a pointer to the created worker.
			///
			static std::unique_ptr<IWorkerInterface> CreateWorker( const std::shared_ptr<IWorkerInterface::WorkerConfig>& pConfig, ISchedulerInterface* pParent );
			///
			/// \brief Factory method for filter configs.
			/// \param sType the configuration for the filter.
			/// \return a pointer to the created filter config.
			///
			static std::shared_ptr<IWorkerInterface::WorkerConfig> CreateConfig( const std::string& sType );

		private:
			///
			/// \brief Map containing all creation functions.
			///
			static std::map<std::string, std::pair<CreateCallback, ConfigCreateCallback> > m_mWorkers;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_WORKER_INTERFACE
#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_WORKER_REMOTE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_WORKER_REMOTE

// std includes
#include <memory>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/worker_interface.h>


namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief A worker, that uses remote procedure calls to run the simulation on a separate computer.
		///
		/// The RPC is done using gRPC over TCP.
		///
		/// This woker can be used to offload the heavier simulation tasks to a separate computer.
		///
		/// Note however, that the configuration of the workers has to match for the remote computer.
		/// \todo implement a local fallback?
		///
		class ITA_SIMULATION_SCHEDULER_API CWorkerRemote : public IWorkerInterface
		{
		public:
			///
			/// \brief Configuration class for a remote worker.
			///
			struct ITA_SIMULATION_SCHEDULER_API WorkerRemoteConfig : public IWorkerInterface::WorkerConfig
			{
				explicit WorkerRemoteConfig( );

				///
				/// \brief Address of the computer running the simulation.
				///
				/// The format is "<ip address>:<port number>".
				///
				std::string sRemoteAddress;

				///
				/// \brief Configurations for the workers that will be running on the remote.
				///
				/// Note, that they have to be configured like they will be used on the remote computer.
				/// Also, the configurations cannot be changed by the parent scheduler.
				///
				std::vector<std::shared_ptr<IWorkerInterface::WorkerConfig>> vpWorkerConfigs;

				VistaPropertyList Store( ) const override;

				void Load( const VistaPropertyList& oProperties ) override;
			};

			///
			/// \brief Constructor for CWorkerRemote.
			/// \param oConfig the WorkerConfig used to configure the CWorkerRemote.
			/// \param pParent the parent scheduler of the worker.
			///
			CWorkerRemote( const WorkerRemoteConfig& oConfig, ISchedulerInterface* pParent );

			///
			/// \brief Default destructor of CWorkerRemote.
			///
			~CWorkerRemote( );

			///
			/// \copydoc IWorkerInterface::IsBusy
			///
			bool IsBusy( ) override;

			///
			/// \copydoc IWorkerInterface::PushUpdate
			///
			void PushUpdate( std::unique_ptr<CUpdateScene> pUpdate ) override;

			///
			/// \copydoc IWorkerInterface::Reset
			/// \detail With the reset, the simulator get reset.
			///
			void Reset( ) override;

			///
			/// \copydoc IWorkerInterface::Shutdown
			///
			void Shutdown( ) override;

			///
			/// \brief Factory function for CWorkerRemote.
			/// \param pConfig the WorkerConfig used to configure the CWorkerRemote.
			/// \param pParent the parent scheduler of the worker.
			///
			static std::unique_ptr<IWorkerInterface> CreateWorker( const std::shared_ptr<IWorkerInterface::WorkerConfig>& pConfig, ISchedulerInterface* pParent );

			///
			/// \brief Return a unique type identifying string.
			/// \return a unique type identifying string.
			///
			static std::string GetType( );

		private:
			class Impl;

			///
			/// \brief Pointer to the implementation of the worker.
			///
			/// \remark This worker uses the pImpl idiom to hide the implementation in the cpp file.
			/// This is done so that gRPC is not exposed in the interface of the ITASimulationScheduler.
			///
			std::unique_ptr<Impl> pImpl;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_WORKER_REMOTE
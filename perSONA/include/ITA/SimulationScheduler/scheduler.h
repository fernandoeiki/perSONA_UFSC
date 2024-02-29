#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SCHEDULER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SCHEDULER

// std includes
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/AudibilityFilter/audibility_filter_interface.h>
#include <ITA/SimulationScheduler/AudibilityFilter/filter_network.h>
#include <ITA/SimulationScheduler/RoomAcoustics/rir_simulation_result.h>
#include <ITA/SimulationScheduler/scheduler_interface.h>
#include <ITA/SimulationScheduler/update_config.h>
#include <ITA/SimulationScheduler/update_message.h>
#include <ITA/SimulationScheduler/update_scene.h>
#include <ITA/SimulationScheduler/worker_interface.h>

// VISTA includes
#include <VistaInterProcComm/Concurrency/VistaThreadEvent.h>
#include <VistaInterProcComm/Concurrency/VistaThreadLoop.h>

// ITA includes
#include <ITAAtomicPrimitives.h>

// Other includes
#include <tbb/concurrent_queue.h>


namespace ITA
{
	namespace SimulationScheduler
	{
		class CUpdateScene;
		class CUpdateConfig;
		class IWorkerInterface;

		///
		/// \brief Handles the filtering and scheduling of updates to its workers
		///
		/// CScheduler is kind of the main class of the SimulationScheduler Library.
		/// This scheduler runs local to where it was created.
		///
		/// It allows for easy interaction and configuration of the system.
		///  - Updates can be issued via PushUpdate().
		///  - A IResultHandler can be registered via attachResultHandler.
		///  - A simple replacement filter can be enabled for the CScheduler.
		///
		/// It receives updates, depending on what type of update it is, it either applies the config change (CUpdateConfig), or processes the CUpdateScene.
		/// For this, the CScheduler uses its audibility filters to determine if the update is indeed audible.
		/// If the update is in fact audible, CScheduler distributes the update to idle workers who actually simulate the update.
		/// When the update is simulated, the result is passed to all attached result handlers.
		///
		/// The actual computation takes place in its own thread (loop), see LoopBody().
		/// \todo Determine where whe save the last simulated update, before sending it to the worker or when receiving it from the worker.
		///
		class ITA_SIMULATION_SCHEDULER_API CScheduler
		    : public ISchedulerInterface
		    , public VistaThreadLoop
		{
		public:
			///
			/// \brief Configuration class for local schedulers.
			///
			struct ITA_SIMULATION_SCHEDULER_API LocalSchedulerConfig : public SchedulerConfig
			{
				explicit LocalSchedulerConfig( );

				bool bReplaceUpdates = true;

				std::vector<std::shared_ptr<IWorkerInterface::WorkerConfig>> vpWorkerConfigs;

				AudibilityFilter::CFilterNetwork::FilterNetworkConfig oFilterNetworkConfig;

				VistaPropertyList Store( ) const override;

				void Load( const VistaPropertyList& oProperties ) override;
			};

			CScheduler( ) = delete;

			///
			/// \brief Constructor for a local CScheduler.
			///
			/// The scheduler is configured via its SchedulerConfig.
			/// \param pConfig the SchedulerConfig used to configure the CScheduler.
			///
			explicit CScheduler( const LocalSchedulerConfig& pConfig );

			///
			/// \brief Destructor of CScheduler.
			///
			/// It stops the loop.
			///
			virtual ~CScheduler( );

			///
			/// \copydoc ISchedulerInterface::PushUpdate()
			///
			virtual void PushUpdate( std::unique_ptr<IUpdateMessage> pUpdateMessage ) override;

			///
			/// \copydoc ISchedulerInterface::AttachResultHandler()
			///
			virtual void AttachResultHandler( IResultHandler* pResultHandler ) override;

			///
			/// \copydoc ISchedulerInterface::DetachResultHandler()
			///
			virtual void DetachResultHandler( IResultHandler* pResultHandler ) override;

			///
			/// \copydoc ISchedulerInterface::HandleSimulationFinished()
			///
			virtual void HandleSimulationFinished( std::unique_ptr<CSimulationResult> pResult ) override;

			///
			/// \brief Checks if the scheduler is busy.
			///
			/// The scheduler is busy if any of its workers is busy.
			/// \return true if the scheduler is busy, else false.
			///
			virtual bool IsBusy( ) const override;

			///
			/// \brief Return a unique type identifying string.
			/// \return a unique type identifying string.
			///
			static std::string GetType( );

		protected:
			///
			/// \brief Loop body for the CScheduler.
			///
			/// The following steps are done in the loop:
			/// -# Wait for a new update in m_qUpdateQueue.
			/// -# move the updates from the concurrent queue to a list.
			/// -# The updates are processed depending on their type
			/// 	- \b CUpdateConfig: The config change is applied.
			/// 	- \b CUpdateScene: The audibility of the update is determined and if the update is audible, placed in m_qPendingUpdateQueue.
			/// -# The m_lUpdateList gets cleared for the next loop iteration.
			/// -# If the updates should be filtered, filterReplace() is called.
			/// -# The updates are distributed to the workers.
			/// -# When a update is posted to a worker, it is saved as the latest update for its source-receiver-pair for the filters to reference..
			/// \return true if VistaThreadLoop::ThreadBody() shall call VistaThread::YieldThread() before the next loop, false else
			///
			bool LoopBody( ) override;

			///
			/// \brief Pre loop function.
			///
			/// This function is called once before the thread starts.
			/// \note This is primarily used to set the thread name while profiling.
			///
			void PreLoop( ) override;

			///
			/// \brief Gets a vector of pointers to the workers.
			/// \note This function is primarily for testing.
			/// However, it could also be useful in the long run.
			/// \return a vector of pointers to the workers.
			///
			std::vector<IWorkerInterface*> GetWorker( ) const;

			///
			/// \brief Gets pointer to the filter network.
			/// \note This function is primarily for testing.
			/// However, it could also be useful in the long run.
			/// \return a pointer to the filter network.
			///
			AudibilityFilter::CFilterNetwork* GetFilterNetwork( ) const;

			///
			/// \brief Shutdown the scheduler safely.
			///
			void Shutdown( );

			///
			/// \brief Balance the update requests for multiple source receiver pairs.
			///
			/// Due to the implementation of the replacement scheme, the order in which updates with different source receiver pairs are pushed to the scheduler also
			/// corresponds to the order in which they are likely to be passed to the workers.
			/// This method tries to balance the simulation of multiple source receiver pairs by ordering them with the least up to date source receiver pair first.
			/// Additionally, source receiver pairs that have not been simulated yet will however be prioritized.
			///
			void BalanceUpdateRequests( );

		private:
			///
			/// \brief Process a CUpdateScene.
			///
			/// In this function the CUpdateScene is compared to the latest simulated CUpdateScene that was simulated to determine its audibility.
			/// If the update is audible, it is moved to m_qPendingUpdateQueue.
			/// \param pUpdate the CUpdateScene to check for audibility.
			///
			void ProcessUpdateScene( std::unique_ptr<CUpdateScene> pUpdate );

			///
			/// \brief Process a CUpdateConfig and apply it.
			/// \param pUpdate the CUpdateConfig to apply.
			///
			void ProcessUpdateConfig( std::unique_ptr<CUpdateConfig> pUpdate );

			///
			/// \brief Perform a reset.
			///
			/// This function signals a reset to all workers and clears all update lists.
			/// \todo Make the reset process more elegant if possible.
			///
			void Reset( );

			///
			/// \brief Vector of all attached IResultHandlers.
			///
			std::vector<IResultHandler*> m_vpResultHandlers;

			///
			/// \brief All workers belonging to the CScheduler.
			///
			std::vector<std::unique_ptr<IWorkerInterface>> m_vWorker;

			///
			/// \brief Filter network of the CScheduler.
			///
			std::unique_ptr<AudibilityFilter::CFilterNetwork> m_pFilterNetwork;

			///
			/// \brief Concurrent queue to handle the input of new Updates.
			///
			/// This queue is thus accessed by two threads the calling and the loop thread.
			///
			tbb::concurrent_queue<std::unique_ptr<IUpdateMessage>> m_qUpdateQueue;

			///
			/// \brief List to temporarily move the new updates in from the queue.
			///
			/// This list simplifies the access to the updates, as this list now only is accessed by one thread.
			///
			std::list<std::unique_ptr<IUpdateMessage>> m_lUpdateList;

			///
			/// \brief List with CUpdateScenes pending for simulation.
			///
			std::deque<std::unique_ptr<CUpdateScene>> m_qPendingUpdateQueue;

			///
			/// \brief Map containing all latest simulated updates.
			///
			/// This is map is used for the filters to be able to reference the latest simulated update for its decision.
			/// The key is comprised of the receiver ID as first and source ID as second.
			/// \remark Note the use of unordered_map. This type of map has on average constant complexity for \p find.
			///
			std::unordered_map<std::pair<int, int>, CUpdateScene*, pair_hash> m_mPreviousStates;

			///
			/// \brief True if the controller should filter its received updates using filterReplace().
			///
			bool m_bReplaceUpdates;

			///
			/// \brief Trigger for starting a thread loop.
			///
			VistaThreadEvent m_evTriggerLoop;

			///
			/// \{
			/// \brief Bools for handling the stop of the loop.
			///
			/// As these will be accessed by two threads, they have to be atomic.
			///
			ITAAtomicBool m_bStopIndicated = false;
			ITAAtomicBool m_bStopACK       = false;
			/// \}

			///
			/// \brief Bool for handeling the reset.
			/// \todo This probably does not have to be atomic as the reset happens in the same thread.
			///
			ITAAtomicBool m_bResetIndicated = false;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SCHEDULER
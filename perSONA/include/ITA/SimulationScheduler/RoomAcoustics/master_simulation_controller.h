#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_MASTER_SIMULATION_CONTROLLER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_MASTER_SIMULATION_CONTROLLER

// std includes
#include <list>
#include <memory>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/scheduler.h>
#include <ITA/SimulationScheduler/scheduler_interface.h>
#include <ITA/SimulationScheduler/update_message.h>

// VISTA includes
#include <VistaAspects/VistaPropertyList.h>
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
		class IResultHandler;

		namespace RoomAcoustics
		{
			///
			/// \brief Primary interaction class for room acoustic simulations.
			///
			/// This class represents the interface with which external software should interact with the simulation scheduler for room acoustic simulations.
			/// It allows for easy interaction and configuration of the system.
			///  - Updates can be issued via PushUpdate().
			///  - A IResultHandler can be registered via attachResultHandler.
			///  - A simple replacement filter can be enabled for the CMasterSimulationController.
			///
			///  The actual computation takes place in its own thread (loop), see LoopBody().
			///  \todo Inherit the scheduler interface? But we dont need handle simulation here :/
			///
			class ITA_SIMULATION_SCHEDULER_API CMasterSimulationController : public VistaThreadLoop
			{
			public:
				///
				/// \brief Configuration class for the master simulation controller.
				///
				struct ITA_SIMULATION_SCHEDULER_API MasterSimulationControllerConfig : public IConfig
				{
					std::shared_ptr<ISchedulerInterface::SchedulerConfig> oDSSchedulerConfig;

					std::shared_ptr<ISchedulerInterface::SchedulerConfig> oERSchedulerConfig;

					std::shared_ptr<ISchedulerInterface::SchedulerConfig> oDDSchedulerConfig;

					bool bReplaceUpdates = true;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				///
				/// \brief Constructor for the CMasterSimulationController.
				///
				/// This constructor configures itself via the given configuration.
				/// After a resultHandler is attached the controller is functional.
				/// Note, that external schedulers have to be running for the master controller to work correctly.
				/// \throw ITAException When creation or connection to schedulers failed.
				/// \param pConfig the configuration from which to construct the CMasterSimulationController.
				///
				explicit CMasterSimulationController( const MasterSimulationControllerConfig& pConfig );

				///
				/// \brief Destructor for CMasterSimulationController
				///
				~CMasterSimulationController( );

				///
				/// \brief Push a new update to the CMasterSimulationController.
				///
				/// \note This method takes ownership of the update.
				/// \param pUpdateMessage the new update for the CMasterSimulationController.
				///
				void PushUpdate( std::unique_ptr<IUpdateMessage> pUpdateMessage );

				///
				/// \brief Attach a IResultHandler to the controller.
				/// \remark Internally, the IResultHandler is attached to the simulators themselves.
				/// \param pResultHandler the new IResultHandler.
				/// \todo Maybe use shared_ptr ... resultHandler have to support make shared form this ... and consequently have to be shared_ptr. This would also mean
				/// ,that the scheduler own the handler.
				///
				void AttachResultHandler( IResultHandler* pResultHandler ) const;

				///
				/// \brief Detach a IResultHandler from the controller.
				/// \param pResultHandler the IResultHandler to detach.
				///
				void DetachResultHandler( IResultHandler* pResultHandler ) const;

				///
				/// \brief Checks if the CMasterSimulationController is busy.
				///
				/// The CMasterSimulationController is busy if any of its scheduler is busy.
				/// \return true if the CMasterSimulationController is busy, else false.
				///
				virtual bool IsBusy( );

			protected:
				///
				/// \brief Loop body for the CMasterSimulationController.
				///
				/// The following steps are done in the loop:
				/// - Wait for a new update in m_qUpdateQueue.
				/// - move the updates from the concurrent queue to a list.
				/// - If the updates should be filtered, filterReplace() is called.
				/// - The updates get copied, and send to the three schedulers.
				/// - The m_lUpdateList gets cleared for the next loop iteration.
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
				/// \brief Removes duplicate updates for source-receiver-pairs in its m_qUpdateList.
				///
				/// If the m_qUpdateQueue has multiple updates for the same source-receiver-pair, this method removes all but the newest update.
				///
				void FilterReplace( );

				///
				/// \brief Setter for the scheduler.
				/// \note This function is primarily for testing.
				/// However, it could also be useful in the long run.
				/// \param pDSScheduler the DS scheduler.
				/// \param pERScheduler the ER scheduler.
				/// \param pDDScheduler the DD scheduler.
				///
				void SetScheduler( std::unique_ptr<ISchedulerInterface> pDSScheduler, std::unique_ptr<ISchedulerInterface> pERScheduler,
				                   std::unique_ptr<ISchedulerInterface> pDDScheduler );

			private:
				///
				/// \brief Modify a CScheduler::LocalSchedulerConfig so that all worker have the given ::FieldOfDuty.
				/// \param oConfig the CScheduler::LocalSchedulerConfig to be modified.
				/// \param eFOD the ::FieldOfDuty to set the workers to.
				/// \throw std::bad_cast one of the worker configs is not a ::IRoomAcousticsWorkerInterface::RoomAcousticsWorkerInterfaceConfig
				/// \return a modified copy of the given config.
				///
				static CScheduler::LocalSchedulerConfig SetWorkerFieldOfDuty( const CScheduler::LocalSchedulerConfig& oConfig, FieldOfDuty eFOD );

				///
				/// \brief Update queue for the controller.
				///
				/// PushUpdate() adds new updates to this queue before they get passed to the schedulers in LoopBody().
				///
				tbb::concurrent_queue<std::unique_ptr<IUpdateMessage>> m_qUpdateQueue;

				std::list<std::unique_ptr<IUpdateMessage>> m_lUpdateList;

				///
				/// \brief True if the controller should filter its received updates using filterReplace().
				///
				bool m_bReplaceUpdates;

				///
				/// \brief The scheduler for the direct sound of the RIR.
				///
				std::unique_ptr<ISchedulerInterface> m_pDSScheduler;

				///
				/// \brief The scheduler for the early reflections of the RIR.
				///
				std::unique_ptr<ISchedulerInterface> m_pERScheduler;

				///
				/// \brief The scheduler for the diffuse decay of the RIR.
				///
				std::unique_ptr<ISchedulerInterface> m_pDDScheduler;

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
			};
		} // namespace RoomAcoustics
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_MASTER_SIMULATION_CONTROLLER

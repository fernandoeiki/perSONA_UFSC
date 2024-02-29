#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_WORKER_THREAD
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_WORKER_THREAD

// std include
#include <memory>
#include <string>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/RoomAcoustics/raven/raven_worker_interface.h>
#include <ITA/SimulationScheduler/RoomAcoustics/raven/simulator_interface.h>
#include <ITA/SimulationScheduler/update_scene.h>

// Vista includes
#include <ITAAtomicPrimitives.h>
#include <VistaInterProcComm/Concurrency/VistaThreadEvent.h>
#include <VistaInterProcComm/Concurrency/VistaThreadLoop.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			namespace Raven
			{
				struct CRavenConfig;

				///
				/// \brief Raven worker utilizing a thread to run the actual simulation.
				///
				class ITA_SIMULATION_SCHEDULER_API CWorkerThread
				    : public IRavenWorkerInterface
				    , VistaThreadLoop
				{
				public:
					///
					/// \brief Configuration class for a raven thread worker.
					///
					struct ITA_SIMULATION_SCHEDULER_API WorkerThreadConfig : public IRavenWorkerInterface::RavenWorkerConfig
					{
						explicit WorkerThreadConfig( );

						std::string sRavenProjectFilePath = "path/to/raven/project/file.rpf";

						VistaPropertyList Store( ) const override;

						void Load( const VistaPropertyList& oProperties ) override;
					};

					///
					/// \brief Constructor for CWorkerThread.
					/// \param oConfig the WorkerConfig used to configure the CWorkerThread.
					/// \param pParent the parent scheduler of the worker.
					///
					CWorkerThread( const WorkerThreadConfig& oConfig, ISchedulerInterface* pParent );

					///
					/// \brief Destructor of CWorkerThread.
					///
					/// This waits till the simulation is finished and stops the thread loop gently.
					///
					~CWorkerThread( );

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
					/// \brief Factory function for CWorkerThread.
					/// \param pConfig the WorkerConfig used to configure the CWorkerThread.
					/// \param pParent the parent scheduler of the worker.
					///
					static std::unique_ptr<IWorkerInterface> CreateWorker( const std::shared_ptr<IWorkerInterface::WorkerConfig>& pConfig, ISchedulerInterface* pParent );

					///
					/// \brief Return a unique type identifying string.
					/// \return a unique type identifying string.
					///
					static std::string GetType( );

				protected:
					///
					/// \brief Loop body for the CWorkerThread.
					///
					/// The following steps are done in the loop:
					/// - Check if the scene is loaded, and load it if not.
					/// - Simulate the Task.
					/// - Forward the result to the scheduler.
					/// \return true if VistaThreadLoop::ThreadBody() shall call VistaThread::YieldThread() before the next loop, false else
					///
					virtual bool LoopBody( ) override;

					///
					/// \brief Pre loop function.
					///
					/// This function is called once before the thread starts.
					/// \note This is primarily used to set the thread name while profiling.
					///
					void PreLoop( ) override;

					///
					/// \brief Set the simulator of the worker.
					/// \param pSimulator the new simulator.
					/// \note This function is primarily for testing.
					/// However, it could also be useful in the long run.
					///
					void SetSimulator( std::unique_ptr<ISimulatorInterface> pSimulator );

				private:
					///
					/// \brief The actual raven simulator
					///
					std::unique_ptr<ISimulatorInterface> m_pSimulator;

					///
					/// \brief True if a scene is loaded.
					///
					ITAAtomicBool m_bSceneLoaded;

					///
					/// \brief Trigger for starting a thread loop.
					///
					VistaThreadEvent m_evTriggerLoop;

					///
					/// \brief The task that is currently being simulated.
					///
					/// We need this to later reference the task when creating the result.
					///
					std::unique_ptr<CSimulationTask> m_pCurrentTask;

					///
					/// \{
					/// \brief Bools for handling the stop of the loop.
					///
					/// As these will be accessed by two threads, they have to be atomic.
					///
					ITAAtomicBool m_bStopIndicated = false;

					ITAAtomicBool m_bResetIndicated = false;
					/// \}

					//! \brief Indicates whether worker is busy or not
					ITAAtomicBool m_bBusy = false;

#ifdef WITH_PROFILER
					static std::size_t iWorkerMaxID;
#endif
				};
			} // namespace Raven
		}     // namespace RoomAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_WORKER_THREAD
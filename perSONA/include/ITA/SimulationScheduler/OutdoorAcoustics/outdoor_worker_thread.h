#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_WORKER_THREAD
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_WORKER_THREAD

// std include
#include <memory>
#include <string>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/OutdoorAcoustics/outdoor_simulator_interface.h>
#include <ITA/SimulationScheduler/config_interface.h>
#include <ITA/SimulationScheduler/update_scene.h>
#include <ITA/SimulationScheduler/worker_interface.h>

#ifdef WITH_ART
#	include <ITA/SimulationScheduler/OutdoorAcoustics/ART/art_simulator.h>
#endif

// Vista includes
#include <ITAAtomicPrimitives.h>
#include <VistaInterProcComm/Concurrency/VistaThreadEvent.h>
#include <VistaInterProcComm/Concurrency/VistaThreadLoop.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace OutdoorAcoustics
		{
			// struct CARonfig;

			//! \brief Outdoor simulation worker utilizing a thread to run the actual simulation.
			class ITA_SIMULATION_SCHEDULER_API CWorkerThread
			    : public IWorkerInterface
			    , VistaThreadLoop
			{
			public:
				//! \brief Configuration class for a outdoor acoustics thread worker.
				struct ITA_SIMULATION_SCHEDULER_API WorkerThreadConfig : public IWorkerInterface::WorkerConfig
				{
					explicit WorkerThreadConfig( );
					explicit WorkerThreadConfig( const std::string& sType );

					VistaPropertyList Store( ) const override;
					void Load( const VistaPropertyList& oProperties ) override;

					std::shared_ptr<ISimulatorInterface::SimulatorConfig> pSimulatorConfig;
				};

				//! \brief Constructor for CWorkerThread.
				//! \param oConfig the WorkerConfig used to configure the CWorkerThread.
				//! \param pParent the parent scheduler of the worker.
				CWorkerThread( const WorkerThreadConfig& oConfig, ISchedulerInterface* pParent );

				//! \brief Destructor of CWorkerThread.
				/**
				 * This waits till the simulation is finished and stops the thread loop gently.
				 */
				~CWorkerThread( );

				//! \brief Checks if the worker is busy.
				inline bool IsBusy( ) override { return m_bBusy; };

				//! \brief Push a new update to the worker.
				//!
				//! After a new Update is pushed to a worker, the update gets simulated immediately.
				//! \note This method takes ownership of the update.
				//! \param pUpdateMessage the new update for the scheduler.
				void PushUpdate( std::unique_ptr<CUpdateScene> pUpdate ) override;

				//! \brief Reset the worker.
				//! \detail Also resets the simulator
				void Reset( ) override;

				//! \brief Shutdown the worker safely.
				void Shutdown( ) override;

				//! \brief Factory function for CWorkerThread.
				//! \param pConfig the WorkerConfig used to configure the CWorkerThread.
				//! \param pParent the parent scheduler of the worker.
				static std::unique_ptr<IWorkerInterface> CreateWorker( const std::shared_ptr<IWorkerInterface::WorkerConfig>& pConfig, ISchedulerInterface* pParent );

				//! \brief Return a unique type identifying string.
				//! \return a unique type identifying string.
				inline static std::string GetType( ) { return "OutdoorAcousticsWorkerThread"; };

			protected:
				//! \brief Loop body for the CWorkerThread.
				/** The following steps are done in the loop:
				 * - Check if the scene is loaded, and load it if not.
				 * - Simulate the Task.
				 * - Forward the result to the scheduler.
				 * \return true if VistaThreadLoop::ThreadBody() shall call VistaThread::YieldThread() before the next loop, false else
				 */
				virtual bool LoopBody( ) override;

				//! \brief Pre loop function.
				/**
				 * This function is called once before the thread starts.
				 * \note This is primarily used to set the thread name while profiling.
				 */
				void PreLoop( ) override;

				//! \brief Set the simulator of the worker.
				/**
				 * \param pSimulator the new simulator.
				 * \note This function is primarily for testing.
				 *  However, it could also be useful in the long run.
				 */
				void SetSimulator( std::unique_ptr<ISimulatorInterface> pSimulator );

			private:
				//! \brief Pointer to simulator interface for outdoor scenarios
				std::unique_ptr<ISimulatorInterface> m_pSimulator;

				//! \brief If busy, this holds a pointer to the scene update to be simulated
				std::unique_ptr<CUpdateScene> m_pUpdate = nullptr;

				//! \brief Trigger for starting a thread loop.
				VistaThreadEvent m_evTriggerLoop;

				//! Indicates whether worker is busy or not
				ITAAtomicBool m_bBusy = false;

				///
				/// \{
				/// \brief Bools for handling the stop of the loop.
				///
				/// As these will be accessed by two threads, they have to be atomic.
				///
				ITAAtomicBool m_bStopIndicated = false;

				ITAAtomicBool m_bResetIndicated = false;
				/// \}

#ifdef WITH_PROFILER
				static std::size_t iWorkerMaxID;
#endif
			};
		} // namespace OutdoorAcoustics
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_WORKER_THREAD
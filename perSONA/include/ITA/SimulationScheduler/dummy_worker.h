#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_DUMMY_WORKER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_DUMMY_WORKER

// std include
#include <memory>
#include <string>

// API includes
#include <ITA/SimulationScheduler/definitions.h>
#include <ITA/SimulationScheduler/worker_interface.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/update_scene.h>

// Vista includes
#include <ITAAtomicPrimitives.h>
#include <VistaInterProcComm/Concurrency/VistaThreadEvent.h>
#include <VistaInterProcComm/Concurrency/VistaThreadLoop.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Raven worker utilizing a thread to run the actual simulation.
		///
		class ITA_SIMULATION_SCHEDULER_API CDummyWorker
		    : public IWorkerInterface
		    , VistaThreadLoop
		{
		public:
			///
			/// \brief Configuration class for a raven thread worker.
			///
			struct ITA_SIMULATION_SCHEDULER_API DummyWorkerConfig : public IWorkerInterface::WorkerConfig
			{
				explicit DummyWorkerConfig( );

				double dTime;

				std::string sReturnResult;

				VistaPropertyList Store( ) const override;

				void Load( const VistaPropertyList& oProperties ) override;
			};

			///
			/// \brief Constructor for CDummyWorker.
			/// \param oConfig the WorkerConfig used to configure the CDummyWorker.
			/// \param pParent the parent scheduler of the worker.
			///
			CDummyWorker( const DummyWorkerConfig& oConfig, ISchedulerInterface* pParent );

			///
			/// \brief Destructor of CDummyWorker.
			///
			/// This waits till the dummy simulation is finished and stops the thread loop gently.
			///
			~CDummyWorker( );

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
			/// \brief Factory function for CDummyWorker.
			/// \param pConfig the WorkerConfig used to configure the CDummyWorker.
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
			/// \brief Loop body for the CDummyWorker.
			///
			/// The following steps are done in the loop:
			/// - wait the configured amount inside the loop
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

		private:
			///
			/// \brief Time, the worker needs to complete its dummy task in seconds.
			///
			double dTime;

			///
			/// \brief The type of result to return.
			///
			/// When empty, no result is returned.
			/// Currently supported values are: RIR.
			///
			std::string sReturnResult;

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
			std::atomic_bool m_bStopIndicated;

			std::atomic_bool m_bResetIndicated;
			/// \}

			//! \brief Indicates whether worker is busy or not
			std::atomic_bool m_bBusy;

			//! \brief Helper variable to keep track of the currently "simulating" update.
			unsigned m_iUpdateID;

#ifdef WITH_PROFILER
			static std::size_t iWorkerMaxID;
#endif
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif
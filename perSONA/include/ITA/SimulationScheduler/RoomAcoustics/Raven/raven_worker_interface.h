#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_WORKER_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_WORKER_INTERFACE

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/RoomAcoustics/rir_simulation_result.h>
#include <ITA/SimulationScheduler/RoomAcoustics/room_acoustics_worker_interface.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			namespace Raven
			{
				class CSimulationTask;
				class CRavenConfig;
				class CRavenSimulationResult;
				class CSimulationTask;

				///
				/// \brief Interface for room acoustics worker that use raven to simulate updates.
				/// \todo Add functions to change the config.
				///
				class ITA_SIMULATION_SCHEDULER_API IRavenWorkerInterface : public IRoomAcousticsWorkerInterface
				{
				public:
					///
					/// \brief Configuration class for Raven worker.
					///
					struct ITA_SIMULATION_SCHEDULER_API RavenWorkerConfig : public RoomAcousticsWorkerInterfaceConfig
					{
						explicit RavenWorkerConfig( std::string sType );

						VistaPropertyList Store( ) const override = 0;

						void Load( const VistaPropertyList& oProperties ) override = 0;
					};

					IRavenWorkerInterface( ) = delete;

					///
					/// \brief Constructor for a IRavenWorkerInterface.
					/// \param oConfig the WorkerConfig used to configure the IWorkerInterface.
					/// \param pParent the parent scheduler of the worker.
					///
					explicit IRavenWorkerInterface( const RavenWorkerConfig& oConfig, ISchedulerInterface* pParent );

					///
					/// \brief Pure virtual destructor.
					///
					virtual ~IRavenWorkerInterface( ) = 0;

				protected:
					///
					/// \brief Converts a CUpdateScene into a CSimulationTask.
					/// \param pUpdate the update to be converted.
					/// \return a suitable CSimulationTask containing the information of the update.
					/// \todo Setting of the CRavenConfig: Why only set certain members.
					///
					std::unique_ptr<CSimulationTask> CreateTaskFromUpdate( std::unique_ptr<CUpdateScene> pUpdate ) const;

					///
					/// \brief Converts between the CRavenSimulationResult and CRIRSimulationResult.
					/// \param pResult the CRavenSimulationResult to be converted.
					/// \param pTask the task used to compute the result.
					/// \return the according CRIRSimulationResult.
					/// \todo Change the API of the simulator so that this is not necessary anymore.
					///
					static std::unique_ptr<CRIRSimulationResult> ConvertSimulationResult( std::unique_ptr<CRavenSimulationResult> pResult, CSimulationTask* pTask );
				};
			} // namespace Raven
		}     // namespace RoomAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_WORKER_INTERFACE
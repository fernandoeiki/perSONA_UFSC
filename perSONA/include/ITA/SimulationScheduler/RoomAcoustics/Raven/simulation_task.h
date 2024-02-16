#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATION_TASK
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATION_TASK

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/RoomAcoustics/raven/raven_scene.h>
#include <ITA/SimulationScheduler/types.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			namespace Raven
			{
				///
				/// \brief Simulation task for a simulator that uses Raven.
				///
				struct ITA_SIMULATION_SCHEDULER_API CSimulationTask
				{
					///
					/// \brief Unique identifier for this task
					///
					unsigned long int uiID;


					///
					/// \brief The type of simulation to run i.e. its filed of duty.
					///
					FieldOfDuty eSimulationType;

					///
					/// \brief The scene to be simulated.
					///
					/// All sources an d receivers in this scene get simulated.
					///
					CRavenScene oScene;

					///
					/// \brief Task profiler status
					///
					struct CProfiler
					{
						///
						/// \brief Discard reasons
						///
						enum class DiscardReason
						{
							unspecified,         ///< Unknown or unspecified reason
							resetIndicated,      ///< Discarded due to reset request
							replacedByNewer,     ///< Task was replaced by a newer task with same reference id
							replacedByPreferred, ///< Task was replaced by a preferred task
							unhandable,          ///< Task could not be handled by scheduler
						};

						double dCreationTime;
						double dSchedulerEnqueueTime;
						double dSchedulerTurnaroundTime;
						double dComputeTime;
						DiscardReason eDiscardReason;
					};

					///
					/// \brief Pofiler for this task.
					///
					CProfiler oProfiler;


					///
					/// \brief Check if the task is valid.
					/// \return true if the task is valid, else false.
					///
					bool isValid( ) const { return true; };
				};

			} // namespace Raven
		}     // namespace RoomAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATION_TASK
#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATOR_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATOR_INTERFACE

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes


namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			namespace Raven
			{
				class CRavenSimulationResult;
				class CSimulationTask;

				///
				/// \brief Interface class for simulators.
				/// \remark This interface mainly exists for testing purposes.
				///
				class ITA_SIMULATION_SCHEDULER_API ISimulatorInterface
				{
				public:
					virtual ~ISimulatorInterface( ) = 0 {}

					///
					/// \brief Reset the simulator.
					///
					virtual void Reset( ) = 0;

					///
					/// \brief Simulate the given task.
					/// \param pTask the task to be simulated.
					/// \param[out] pResult the result of the simulation
					///
					virtual void Compute( CSimulationTask* pTask, CRavenSimulationResult* pResult ) = 0;
				};
			} // namespace Raven
		}     // namespace RoomAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATOR_INTERFACE
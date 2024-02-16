#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_WORKER_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_WORKER_INTERFACE

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/Utils/utils.h>
#include <ITA/SimulationScheduler/types.h>
#include <ITA/SimulationScheduler/worker_interface.h>


namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			///
			/// \brief Interface for a room acoustics worker.
			///
			class ITA_SIMULATION_SCHEDULER_API IRoomAcousticsWorkerInterface : public IWorkerInterface
			{
			public:
				struct ITA_SIMULATION_SCHEDULER_API RoomAcousticsWorkerInterfaceConfig : public IWorkerInterface::WorkerConfig
				{
					explicit RoomAcousticsWorkerInterfaceConfig( std::string sType );

					FieldOfDuty eFOD = FieldOfDuty::directSound;

					VistaPropertyList Store( ) const override = 0;

					void Load( const VistaPropertyList& oProperties ) override = 0;
				};

				///
				/// \brief Constructor for IRoomAcousticsWorkerInterface.
				/// \param oConfig the config for the IRoomAcousticsWorkerInterface.
				/// \param pParent the parent scheduler of the worker.
				///
				IRoomAcousticsWorkerInterface( const RoomAcousticsWorkerInterfaceConfig& oConfig, ISchedulerInterface* pParent );

				virtual ~IRoomAcousticsWorkerInterface( ) = 0;

				///
				/// \brief Get the workers field of duty.
				/// \return the workers field of duty.
				///
				FieldOfDuty GetFieldOfDuty( ) const;

			protected:
				///
				/// \brief Field of duty of the worker.
				///
				FieldOfDuty m_eFieldOfDuty = FieldOfDuty::directSound;
			};
		} // namespace RoomAcoustics
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_WORKER_INTERFACE
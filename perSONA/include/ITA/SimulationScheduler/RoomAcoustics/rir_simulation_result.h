#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RIR_SIMULATION_RESULT
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RIR_SIMULATION_RESULT

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/ir_simulation_result.h>

// ITA includes
#include <ITASampleFrame.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			///
			/// \brief Result of a room acoustic simulation.
			///
			/// This class is primarily just a container for the data of an update.
			///
			struct ITA_SIMULATION_SCHEDULER_API CRIRSimulationResult : public CIRSimulationResult
			{
				///
				/// \brief Type of result.
				/// \sa #FieldOfDuty
				///
				FieldOfDuty eResultType = FieldOfDuty::directSound;

				///
				/// \brief True if the Source and receiver are in the same room for this result.
				///
				bool bSameRoom = true;

				///
				/// \brief Serialize the object.
				/// \param pSerializer the IVistaSerializer to use.
				/// \return the number of bytes written or -1 on failure.
				///
				int Serialize( IVistaSerializer& pSerializer ) const override;

				///
				/// \brief DeSerialize the object.
				/// \param pDeserializer the IVistaDeSerializer to use.
				/// \return the number of bytes written or -1 on failure.
				///
				int DeSerialize( IVistaDeSerializer& pDeserializer ) override;

				///
				/// \brief Return a unique identifier for the object for serialization.
				/// \return "CRIRSimulationResult".
				///
				virtual std::string GetSignature( ) const override;

				///
				/// \brief Method to clone the object.
				/// \return a clone of the object.
				///
				std::unique_ptr<CSimulationResult> Clone( ) const override;
			};
		} // namespace RoomAcoustics
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RIR_SIMULATION_RESULT
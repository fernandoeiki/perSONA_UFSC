#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_TYPES
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_TYPES

// API includes
#include <ITA/SimulationScheduler/definitions.h>


// simulation scheduler includes
#include <ITA/SimulationScheduler/3d_object.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief struct to represent a source-receiver-pair.
		///
		typedef struct
		{
			const C3DObject* source;
			const C3DObject* receiver;
		} SourceReceiverPair;

		enum class CoordinateSystem
		{
			Cartesian,
			OpenGL
		};

		namespace RoomAcoustics
		{
			///
			/// \brief Field of duty of a room acoustic simulation.
			///
			enum class FieldOfDuty
			{
				directSound,
				earlyReflections,
				diffuseDecay
			};
		} // namespace RoomAcoustics
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_TYPES

#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_RESULT_HANDLER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_RESULT_HANDLER

// std includes
#include <memory>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/simulation_result.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Result handler interface.
		///
		/// This class defines the interface for result handler.
		/// \todo Add enable_shared_from_this? As a result a handler has to be instantiated as a shared_ptr. However, if the scheduler doesn't take ownership, passing a
		/// raw ptr is preferred anyways.
		///
		class ITA_SIMULATION_SCHEDULER_API IResultHandler //: public std::enable_shared_from_this<IResultHandler>
		{
		public:
			///
			/// \brief Post a result to the handler.
			///
			/// With this function a CSimulationResult gets passed to a result handler.
			/// \param pResult the CSimulationResult to be passed to the result handler.
			///
			virtual void PostResultReceived( std::unique_ptr<CSimulationResult> pResult ) = 0;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_RESULT_HANDLER
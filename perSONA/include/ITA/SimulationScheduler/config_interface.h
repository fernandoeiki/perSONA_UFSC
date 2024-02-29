#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_CONFIG_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_CONFIG_INTERFACE

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// Vista includes
#include <VistaAspects/VistaPropertyList.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Interface for a configuration.
		///
		class ITA_SIMULATION_SCHEDULER_API IConfig
		{
		public:
			///
			/// \brief Store the config as a VistaPropertyList.
			/// \return a VistaPropertyList with the config properties.
			///
			virtual VistaPropertyList Store( ) const = 0;

			///
			/// \brief Load the config from a VistaPropertyList.
			/// \param oProperties a VistaPropertyList fro which to load the config properties.
			///
			virtual void Load( const VistaPropertyList& oProperties ) = 0;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_CONFIG_INTERFACE

#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_MESSAGE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_MESSAGE

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// VISTA includes
#include <VistaAspects/VistaSerializable.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Abstract base interface for all update messages that can be issued to a scheduler or master controller.
		/// \note Currently this base interface does nothing, maybe one day it gets an additional use.
		///
		class ITA_SIMULATION_SCHEDULER_API IUpdateMessage : public IVistaSerializable
		{
		public:
			IUpdateMessage( );

			///
			/// \brief Pure virtual destructor to make this class abstract.
			///
			virtual ~IUpdateMessage( ) = 0;

			///
			/// \brief Get the ID of update.
			/// \return the ID of update.
			///
			unsigned int GetID( ) const;

		protected:
			///
			/// \brief The unique ID of the update.
			///
			int m_iID = -1;

		private:
			///
			/// \brief updateMaxID counts CUpdateScene%s that are constructed.
			///
			/// With this we can give every CUpdateScene an unique ID.
			///
			static unsigned int updateMaxID;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_MESSAGE

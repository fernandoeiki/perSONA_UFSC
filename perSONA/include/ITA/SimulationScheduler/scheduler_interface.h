#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SCHEDULER_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SCHEDULER_INTERFACE

// std includes
#include <memory>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include "../../../src/ITA/SimulationScheduler/configuration_keys.h"

#include <ITA/SimulationScheduler/Utils/utils.h>
#include <ITA/SimulationScheduler/config_interface.h>
#include <ITA/SimulationScheduler/simulation_result.h>
#include <ITA/SimulationScheduler/update_message.h>


namespace ITA
{
	namespace SimulationScheduler
	{
		class IResultHandler;

		///
		/// \brief Interface for a scheduler.
		///
		class ITA_SIMULATION_SCHEDULER_API ISchedulerInterface
		{
		public:
			///
			/// \brief Base configuration class for schedulers.
			///
			/// \note ::sSchedulerType is a read only property of the SchedulerConfig.
			/// Due to this the copy constructor and assignment operator are needed.
			///
			struct ITA_SIMULATION_SCHEDULER_API SchedulerConfig : public IConfig
			{
				SchedulerConfig( );

				explicit SchedulerConfig( std::string sType );

				SchedulerConfig( const SchedulerConfig& other );

				SchedulerConfig& operator=( const SchedulerConfig& other );

				const std::string& sSchedulerType;

				VistaPropertyList Store( ) const override = 0;

				void Load( const VistaPropertyList& oProperties ) override = 0;

			private:
				std::string m_sSchedulerType;
			};

			virtual ~ISchedulerInterface( ) = default;

			///
			/// \brief Push a new update to the scheduler.
			///
			/// \note This method takes ownership of the update.
			/// \param pUpdateMessage the new update for the scheduler.
			///
			virtual void PushUpdate( std::unique_ptr<IUpdateMessage> pUpdateMessage ) = 0;

			///
			/// \brief Attach a IResultHandler to the scheduler.
			/// \param pResultHandler the new IResultHandler.
			/// \todo Maybe use shared_ptr ... resultHandler have to support make shared form this ... and consequently have to be shared_ptr. This would also mean ,that
			/// the scheduler own the handler.
			///
			virtual void AttachResultHandler( IResultHandler* pResultHandler );

			///
			/// \brief Detach a IResultHandler from the scheduler.
			/// \param pResultHandler the IResultHandler to detach.
			///
			virtual void DetachResultHandler( IResultHandler* pResultHandler ) = 0;

			///
			/// \brief Handle when a result is finished.
			///
			/// This function is primarily called by workers who finished a simulation.
			/// The result of this simulation is passed back to the scheduler and distributed to the result handlers.
			/// \remark This function takes ownership of the result.
			/// \param pResult a finished result.
			///
			virtual void HandleSimulationFinished( std::unique_ptr<CSimulationResult> pResult ) = 0;

			///
			/// \brief Checks if the scheduler is busy.
			/// \return true if the scheduler is busy, else false.
			///
			virtual bool IsBusy( ) const = 0;
		};

		inline ISchedulerInterface::SchedulerConfig::SchedulerConfig( ) : SchedulerConfig( "Unkown" ) { };

		inline ISchedulerInterface::SchedulerConfig::SchedulerConfig( std::string sType ) : sSchedulerType( m_sSchedulerType ) { m_sSchedulerType = sType; };

		inline ISchedulerInterface::SchedulerConfig::SchedulerConfig( const SchedulerConfig& other )
		    : IConfig( other )
		    , sSchedulerType( m_sSchedulerType )
		    , m_sSchedulerType( other.m_sSchedulerType ) { };

		inline ISchedulerInterface::SchedulerConfig& ISchedulerInterface::SchedulerConfig::operator=( const SchedulerConfig& other )
		{
			if( this == &other )
				return *this;
			IConfig::operator=( other );
			m_sSchedulerType = other.m_sSchedulerType;
			return *this;
		};

		inline VistaPropertyList ISchedulerInterface::SchedulerConfig::Store( ) const
		{
			VistaPropertyList oProperties;
			oProperties.SetValue( schedulerTypeKey, m_sSchedulerType );
			return oProperties;
		};

		inline void ISchedulerInterface::SchedulerConfig::Load( const VistaPropertyList& oProperties )
		{
			oProperties.GetValue<std::string>( schedulerTypeKey, m_sSchedulerType );
		};

		inline void ISchedulerInterface::AttachResultHandler( IResultHandler* pResultHandler ) { };
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_SCHEDULER_INTERFACE
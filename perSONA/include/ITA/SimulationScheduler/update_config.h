#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_CONFIG
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_CONFIG

// std includes
#include <string>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/update_message.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Special IUpdateMessage to signal configuration changes.
		///
		class ITA_SIMULATION_SCHEDULER_API CUpdateConfig : public IUpdateMessage
		{
		public:
			///
			/// \brief Types of configuration changes
			///
			enum class ConfigChangeType
			{
				resetAll,         ///< Reset all simulations.
				shutdown,         ///< Shutdown the system.
				changeHRTF,       ///< Signal a change in receiver HRTF.
				changeDirectivity ///< Signal a change in source directivity.
			};

			///
			/// \brief Default constructor.
			///
			/// This constructor is primarily used for creating an object for deserialization.
			/// It initializes the object with ConfigChangeType::resetAll and an empty payload string.
			///
			CUpdateConfig( );

			///
			/// \brief Constructor for a CUpdateConfig.
			/// \param type the type of configuration change.
			/// \param payload optional payload of the update.
			/// Can encode a json file.
			///
			explicit CUpdateConfig( ConfigChangeType type, std::string payload = "" );

			///
			/// \brief Copy constructor.
			/// \param obj object to copy from.
			///
			CUpdateConfig( const CUpdateConfig& obj ) = default;

			///
			/// \brief Get the ConfigChangeType of the update.
			/// \return the ConfigChangeType of the update.
			///
			ConfigChangeType GetType( ) const;

			///
			/// \brief Get the payload of the update.
			/// \return the payload of the update.
			/// Can encode a json file.
			///
			const std::string& GetPayload( ) const;

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
			/// \return "CUpdateConfig".
			///
			virtual std::string GetSignature( ) const override;

		private:
			///
			/// \brief ConfigChangeType of the update.
			///
			ConfigChangeType m_eConfigChangeType;

			///
			/// \brief The payload of the update.
			/// Can encode a json file.
			///
			std::string m_sPayload;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_CONFIG

#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_SCENE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_SCENE

// std includes
#include <memory>
#include <string>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/3d_object.h>
#include <ITA/SimulationScheduler/types.h>
#include <ITA/SimulationScheduler/update_message.h>

// ITA includes
#include "ITAClock.h"

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Special IUpdateMessage to signal scene changes.
		///
		/// A scene change is a change of a source or receiver pose.
		/// A change of either source or receiver can lead to a change in the transfer path between a corresponding source-receiver-pair.
		/// Thus, a CUpdateScene combines pose information for such a source-receiver-pair.
		/// \todo May be change the separate source and receiver pointers to the struct?
		///
		class ITA_SIMULATION_SCHEDULER_API CUpdateScene : public IUpdateMessage
		{
		public:
			///
			/// \brief Default constructor.
			///
			/// This constructor is primarily used for creating an object for deserialization.
			/// It initializes the object with nullptrs for source and receiver and ID's to -1.
			///
			CUpdateScene( ) = default;

			///
			/// \brief Constructs a scene update giving a timestamp from an external clock
			///
			/// Source and receiver are nullptrs.
			///
			explicit CUpdateScene( double dTimeStamp );

			///
			/// \brief Copy constructor.
			/// \note This also copies the timestamp to keep the creation time of the original update.
			/// In addition it creates copies for the source and receiver.
			/// \param other object to copy from.
			///
			CUpdateScene( const CUpdateScene& other );

			///
			/// \brief Assignment operator.
			/// \param other object to copy from.
			/// \return a copy of the other object.
			///
			CUpdateScene& operator=( const CUpdateScene& other );

			///
			/// \brief Get the source-receiver-pair of the update.
			/// \return the SourceReceiverPair of the update.
			///
			SourceReceiverPair GetSourceReceiverPair( ) const;

			///
			/// \brief Set the source-receiver-pair of the update.
			///
			/// With this function the CUpdateScene takes ownership of the objects.
			/// \param pSource the new source for the update.
			/// \param pReceiver the new receiver for the update.
			/// \todo Maybe split this function?
			///
			void SetSourceReceiverPair( std::unique_ptr<C3DObject> pSource, std::unique_ptr<C3DObject> pReceiver );

			///
			/// \brief Get the timestamp of update.
			/// \return the timestamp of update.
			///
			double GetTimeStamp( ) const;

			///
			/// \brief Compare two CUpdateScene, with a given tolerance.
			///
			/// Similar to operator==(), this function compares two CUpdateScene.
			/// However, this comparison allows for a tolerance for the comparison of the source and receiver.
			/// And does \b not compare the unique ID and timestamp of the update.
			/// \sa C3DObject::isEqualTolerance()
			/// \param obj the object to check against.
			/// \param dTolerance the allowed tolerance.
			/// \return true if the given object is the same as this with the given tolerance.
			///
			bool IsEqualTolerance( const CUpdateScene& obj, double dTolerance ) const;

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
			/// \return "CUpdateScene".
			///
			virtual std::string GetSignature( ) const override;

		private:
			///
			/// \brief The source of the update.
			///
			std::unique_ptr<C3DObject> m_pSource;

			///
			/// \brief The source of the update.
			///
			std::unique_ptr<C3DObject> m_pReceiver;

			///
			/// \brief Time stamp of the update.
			/// \todo Is this necessary?
			/// Or for the profiler?
			/// Define it.
			///
			double m_dTimeStamp = ITAClock::getDefaultClock( )->getTime( );
		};

		///
		/// \brief Compare two CUpdateScene.
		///
		/// Check if \p lhs and \p rhs are exactly the same.
		/// For this all members have to match.
		/// \param lhs the first object to check.
		/// \param rhs the second object to check.
		/// \return true if the given objects are exactly the same.
		/// \todo Quick and dirty fix for empty source-receiver-pairs, should this be even possible? This has to be determined!
		///
		inline bool operator==( const CUpdateScene& lhs, const CUpdateScene& rhs )
		{
			const auto lhsSourceReceiverPair = lhs.GetSourceReceiverPair( );
			const auto rhsSourceReceiverPair = rhs.GetSourceReceiverPair( );

			if( lhsSourceReceiverPair.source && lhsSourceReceiverPair.receiver && rhsSourceReceiverPair.source && rhsSourceReceiverPair.receiver )
			{
				return lhs.GetID( ) == rhs.GetID( ) && lhs.GetTimeStamp( ) == rhs.GetTimeStamp( ) && *lhsSourceReceiverPair.source == *rhsSourceReceiverPair.source &&
				       *lhsSourceReceiverPair.receiver == *rhsSourceReceiverPair.receiver;
			}
			else
			{
				return lhs.GetID( ) == rhs.GetID( ) && lhs.GetTimeStamp( ) == rhs.GetTimeStamp( );
			}
		}

		///
		/// \brief Relational operator for CUpdateScene.
		/// \retrun true if m_dTimeStamp is smaller for lhs, else false.
		///
		inline bool operator<( const CUpdateScene& lhs, const CUpdateScene& rhs ) { return lhs.GetTimeStamp( ) < rhs.GetTimeStamp( ); }
		inline bool operator>( const CUpdateScene& lhs, const CUpdateScene& rhs ) { return rhs < lhs; }
		inline bool operator<=( const CUpdateScene& lhs, const CUpdateScene& rhs ) { return !( lhs > rhs ); }
		inline bool operator>=( const CUpdateScene& lhs, const CUpdateScene& rhs ) { return !( lhs < rhs ); }
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_UPDATE_CONFIG

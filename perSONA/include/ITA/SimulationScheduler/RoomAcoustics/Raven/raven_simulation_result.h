#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_SIMULATION_RESULT
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_SIMULATION_RESULT

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// std includes
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

// simulation scheduler includes
#include <ITA/SimulationScheduler/RoomAcoustics/raven/simulation_task.h>

// ITA includes
#include <ITASampleFrame.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			namespace Raven
			{
				///
				/// \brief Container for simulation results
				///
				struct ITA_SIMULATION_SCHEDULER_API CRavenSimulationResult
				{
					CRavenSimulationResult( ) = default;


					CRavenSimulationResult( const CRavenSimulationResult& other )
					{
						for( const auto& soundPath: other.vcspResult )
						{
							vcspResult.push_back( std::make_unique<ComplexSimulationSoundPath>( *soundPath ) );
						}
					}

					CRavenSimulationResult& operator=( const CRavenSimulationResult& other )
					{
						if( this == &other )
							return *this;
						for( const auto& soundPath: other.vcspResult )
						{
							vcspResult.push_back( std::make_unique<ComplexSimulationSoundPath>( *soundPath ) );
						}
						return *this;
					}

					///
					/// \brief Complex sound path of a sender-receiver-pair
					///
					struct ITA_SIMULATION_SCHEDULER_API ComplexSimulationSoundPath
					{
						ComplexSimulationSoundPath( ) { psfResult = std::make_unique<ITASampleFrame>( ); }

						ComplexSimulationSoundPath( const ComplexSimulationSoundPath& other )
						    : iReceiverID( other.iReceiverID )
						    , iSourceID( other.iSourceID )
						    , iNumChannels( other.iNumChannels )
						    , bDirectSoundAudible( other.bDirectSoundAudible )
						    , bEntitiesInSameRoom( other.bEntitiesInSameRoom )
						    , bEmpty( other.bEmpty )
						    , iLeadingZeros( other.iLeadingZeros )
						    , iTailingZeros( other.iTailingZeros )
						    , bZerosStripped( other.bZerosStripped )
						{
							psfResult = std::make_unique<ITASampleFrame>( *other.psfResult );
						}

						ComplexSimulationSoundPath& operator=( const ComplexSimulationSoundPath& other )
						{
							if( this == &other )
								return *this;
							iReceiverID         = other.iReceiverID;
							iSourceID           = other.iSourceID;
							iNumChannels        = other.iNumChannels;
							bDirectSoundAudible = other.bDirectSoundAudible;
							bEntitiesInSameRoom = other.bEntitiesInSameRoom;
							bEmpty              = other.bEmpty;
							iLeadingZeros       = other.iLeadingZeros;
							iTailingZeros       = other.iTailingZeros;
							bZerosStripped      = other.bZerosStripped;
							psfResult           = std::make_unique<ITASampleFrame>( *other.psfResult );
							return *this;
						}

						int iReceiverID                           = -1;      //!< ID of the receiver.
						int iSourceID                             = -1;      //!< ID of the source.
						int iNumChannels                          = -1;      //!< Number of channels.
						bool bDirectSoundAudible                  = false;   //!< True, if the direct sound is audible.
						bool bEntitiesInSameRoom                  = true;    //!< True, if source and receiver are in sme room.
						bool bEmpty                               = true;    //!< True, if the impulse response is empty.
						int iLeadingZeros                         = 0;       //!< Number of null samples before the start of the impulse response.
						int iTailingZeros                         = 0;       //!< Number of null samples after the start of the impulse response.
						bool bZerosStripped                       = false;   //!< Indicated, if zeros are stripped from result container (true) or still included (false).
						std::unique_ptr<ITASampleFrame> psfResult = nullptr; //!< pointer to the impulse response.
					};

					std::vector<std::unique_ptr<ComplexSimulationSoundPath> > vcspResult; //!< Result container
				};

			} // namespace Raven
		}     // namespace RoomAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_SIMULATION_RESULT
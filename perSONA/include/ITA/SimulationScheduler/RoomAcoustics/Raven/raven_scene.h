#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_SCENE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_SCENE

// std includes
#include <map>
#include <string>
#include <vector>

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/Utils/utils.h>

// RAVEN includes
#include "RG_Vector.h"

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			namespace Raven
			{
				///
				/// \brief Scene class for Raven instances.
				///
				/// Implements a Raven scene and provides functionality to compare two scenes.
				///
				class ITA_SIMULATION_SCHEDULER_API CRavenScene
				{
				public:
					///
					/// \brief Data type indicating the difference of number of objects from two scenes.
					///
					struct ITA_SIMULATION_SCHEDULER_API CSceneDifference
					{
						///
						/// \brief Data type saving the object IDs of all new, modified and removed objects.
						///
						struct DifferenceVectors
						{
							std::vector<int> viNewObjects; ///< New objects.
							std::vector<int> viModObjects; ///< Modified objects.
							std::vector<int> viDelObjects; ///< Removed objects.
						};

						DifferenceVectors receiverDifferences; ///< Differences for receivers.
						DifferenceVectors sourceDifferences;   ///< Differences for sources.

						///
						/// \brief Test of entities have changed.
						/// \return true if a difference was detected.
						///
						virtual bool EntitiesChanged( ) const;
					};

					///
					/// \brief Data type for the state of a sound source.
					///
					struct ITA_SIMULATION_SCHEDULER_API CSourceState
					{
						CSourceState( ) = default;

						///
						/// Flags indicating the difference between two CSourceState%s.
						///
						enum class DifferenceFlags : int
						{
							none        = 0,
							position    = 1, ///< Difference in position.
							orientation = 2, ///< Difference in orientation.
						};

						RG_Vector vPos  = RG_Vector( 0, 0, 0 ); ///< Vector indicating the position.
						RG_Vector vView = RG_Vector( 0, 0, 0 ); ///< Vector indicating the view direction.
						RG_Vector vUp   = RG_Vector( 0, 0, 0 ); ///< Vector indicating the up direction.

						///
						/// \brief Compare with another CSourceState.
						/// \return the DifferenceFlags indicating the differences.
						///
						DifferenceFlags Compare( const CSourceState& oState ) const;
					};

					///
					/// \brief Data type for the state of a sound receiver.
					///
					class ITA_SIMULATION_SCHEDULER_API CReceiverState
					{
					public:
						CReceiverState( ) = default;

						///
						/// Flags indicating the difference between two CReceiverState%s.
						///
						enum class DifferenceFlags : int
						{
							none        = 0,
							position    = 1, ///< Difference in position.
							orientation = 2, ///< Difference in orientation.
						};

						RG_Vector vPos  = RG_Vector( 0, 0, 0 ); ///< Vector indicating the position.
						RG_Vector vView = RG_Vector( 0, 0, 0 ); ///< Vector indicating the view direction.
						RG_Vector vUp   = RG_Vector( 0, 0, 0 ); ///< Vector indicating the up direction.

						///
						/// \brief Compare with another CReceiverState.
						/// \return the DifferenceFlags indicating the differences.
						///
						DifferenceFlags Compare( const CReceiverState& oState ) const;
					};

					CRavenScene( ) = default;

					CRavenScene( const CRavenScene& other ) = default;

					CRavenScene& operator=( const CRavenScene& other ) = default;

					///
					/// \brief Destructor of CRavenScene.
					///
					virtual ~CRavenScene( );

					///
					/// \brief Clears the scene.
					///
					/// Removes all objects.
					///
					virtual void Reset( );

					///
					/// \{
					/// \brief Methods for adding, removing, setting and getting of source and receiver states via the ID system.
					///
					virtual void AddSource( int iSoundSourceID );
					virtual void RemoveSource( int iSoundSourceID );
					virtual void SetSourceState( int iSoundSourceID, const CSourceState& oState );
					virtual const CSourceState& GetSourceState( int iSoundSourceID ) const;

					virtual void AddReceiver( int iReceiverID );
					virtual void RemoveReceiver( int iReceiverID );
					virtual void SetReceiverState( int iReceiverID, const CReceiverState& oState );
					virtual const CReceiverState& GetReceiverState( int iReceiverID ) const;
					///
					/// \}
					///

					///
					/// \brief Determine difference to another scene (entities only).
					/// \retrun the difference of both scenes.
					///
					CSceneDifference Difference( const CRavenScene& oScene ) const;

					///
					/// \brief Compare two scenes for equality.
					/// \param oScene the CRavenScene to compare against.
					/// \return true if the scenes are equal.
					///
					bool IsEqual( const CRavenScene& oScene ) const;

					///
					/// \brief Formats the scene content into string.
					/// \return the scene contents as a string.
					///
					std::string ToString( ) const;

					///
					/// \brief Load a INI file containing a CRavenScene.
					/// \param sPath path to the INI file.
					///
					void LoadFormIni( const std::string& sPath );

					///
					/// \brief Store a INI file containing a CRavenScene.
					/// \param sPath path to where the INI file should be stored.
					/// \param iFloatingPointPrecision the  with which the floats will be stored.
					///
					void StoreToIni( const std::string& sPath, int iFloatingPointPrecision = 2 ) const;

					///
					/// \brief Get the source map.
					/// \return the source map.
					///
					const std::map<int, CSourceState>& GetSourceMap( ) const;

					///
					/// \brief Get the receiver map.
					/// \return the receiver map.
					///
					const std::map<int, CReceiverState>& GetReceiverMap( ) const;

				private:
					///
					/// \brief Compute the difference for the receivers.
					/// \param mOld the reference receiver map.
					/// \param mNew the new receiver map.
					/// \return a DifferenceVector object containing the difference for receivers.
					///
					static CSceneDifference::DifferenceVectors DifferenceReceiver( const std::map<int, CReceiverState>& mOld, const std::map<int, CReceiverState>& mNew );

					///
					/// \brief Compute the difference for the sources.
					/// \param mOld the reference source map.
					/// \param mNew the new source map.
					/// \retrun a DifferenceVector object containing the difference for sources.
					///
					static CSceneDifference::DifferenceVectors DifferenceSource( const std::map<int, CSourceState>& mOld, const std::map<int, CSourceState>& mNew );

					///
					/// \{
					/// \brief Map containing the states of sources and receivers, keyed by their ID.
					///
					std::map<int, CReceiverState> m_mReceivers;
					std::map<int, CSourceState> m_mSources;
					///
					/// \}
					///
				};

				ENABLE_BITMASK_OPERATORS( RoomAcoustics::Raven::CRavenScene::CReceiverState::DifferenceFlags );
				ENABLE_BITMASK_OPERATORS( RoomAcoustics::Raven::CRavenScene::CSourceState::DifferenceFlags );

			} // namespace Raven
		}     // namespace RoomAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_RAVEN_SCENE
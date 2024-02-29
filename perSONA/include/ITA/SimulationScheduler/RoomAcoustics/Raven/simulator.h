#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATOR
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATOR

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// std includes
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

// simulation scheduler includes
#include <ITA/SimulationScheduler/RoomAcoustics/raven/raven_simulation_result.h>
#include <ITA/SimulationScheduler/RoomAcoustics/raven/simulation_task.h>
#include <ITA/SimulationScheduler/RoomAcoustics/raven/simulator_interface.h>

// RAVEN includes
#include "R_MasterController.h"

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace RoomAcoustics
		{
			namespace Raven
			{
				///
				/// \brief Simulator using Raven.
				///
				/// This Simulator uses a single Raven instance to simulate room acoustic simulations.
				/// The simulation is run synchronous/blocking.
				/// Thus, only one simulation can be run at the same time.
				/// \todo refactor "all" functions. Check for const ref.
				///
				class ITA_SIMULATION_SCHEDULER_API CSimulator : public ISimulatorInterface
				{
				public:
					///
					/// \brief Raven status types
					///
					enum class SimulatorStatus
					{
						uninitialized,     ///< Simulator is uninitialized.
						idle,              ///< Raven instance is running but no geometry is loaded.
						sceneLoaded,       ///< Raven instance is running and a geometry is loaded.
						filterEngineLoaded ///< Raven initialized the filter engine.
					};

					///
					/// \brief Constructor for CSimulator.
					/// \param eFieldOfDuty field of duty of the simulator.
					/// \param sRavenProjectFilePath path to raven data base.
					///
					CSimulator( FieldOfDuty eFieldOfDuty, const std::string& sRavenProjectFilePath = "." );

					~CSimulator( );

					CSimulator( const CSimulator& other ) = delete;
					CSimulator( CSimulator&& other )      = delete;
					CSimulator& operator=( const CSimulator& other ) = delete;
					CSimulator& operator=( CSimulator&& other ) = delete;

					///
					/// \brief Reset the simulator.
					///
					/// After reset the Simulator is idle again.
					///
					void Reset( ) override;

					///
					/// \brief Simulate the given task.
					/// \remark This function is blocking.
					/// No other function should be called in parallel.
					/// \param pTask the task to be simulated.
					/// \param[out] pResult the result of the simulation
					/// \todo Fix return type.
					///
					void Compute( CSimulationTask* pTask, CRavenSimulationResult* pResult ) override;

					///
					/// \brief Writes a .rpf file of the current scene.
					/// \param sFileName the file name of the .rpf file.
					///
					void WriteToRpf( const std::string& sFileName ) const;

				private:
					///
					/// \brief Pointer to the raven instance.
					///
					std::unique_ptr<R_MasterController> m_pRavenMasterController;

					///
					/// \brief Current status of the simulator.
					///
					SimulatorStatus m_eStatus;

					///
					/// \{
					/// \brief Internal representation, mapping the external source and receiver IDs to Raven IDs
					///
					std::map<int, int> m_mapSources;
					std::map<int, int> m_mapReceivers;
					///
					/// \}
					///

					///
					/// \{
					/// \brief Internal representation of static/used sources and receivers keyed by their Raven IDs.
					///
					/// If the value flag is false, the object is not used.
					/// \todo check this!
					///
					std::map<int, bool> m_mapStaticSourcesList;
					std::map<int, bool> m_mapStaticReceiversList;
					///
					/// \}
					///

					///
					/// \brief Current Raven scene.
					///
					CRavenScene m_oCurScene;

					///
					/// \brief New Raven scene.
					/// \todo Do we need this?
					///
					CRavenScene m_oNewScene;

					///
					/// \brief Field of duty of the simulator.
					///
					FieldOfDuty m_eFieldOfDuty;

					///
					/// \brief Current Raven config.
					///
					// CRavenConfig m_oCurConfig;

					///
					/// \brief New Raven config.
					/// \todo Do we need this?
					///
					// CRavenConfig m_oNewConfig;

					///
					/// \brief Raven data base path.
					///
					const std::string m_sRavenProjectFilePath;

					///
					/// \brief Loads a scene for the simulator.
					/// \param sFileName path to the scene file (.skp, .ac, obj).
					///
					void LoadScene( const std::string& sFileName );

					///
					/// \brief Initialise the raven instance.
					///
					/// The simulator is idle afterwards.
					///
					void Init( );

					///
					/// \brief Set a new scene for the simulator.
					/// \param oScene the new scene.
					///
					void SetScene( const CRavenScene& oScene );

					///
					/// \brief Adapt the current scene to the changes of the new scene.
					///
					/// This function also calculates what sources and receivers are outside the room.
					/// \param[out] viSourcesOutsideRoom IDs of the sources lying outside the room.
					/// \param[out] viReceiversOutsideRoom IDs of the receivers lying outside the room.
					/// \todo Fix return.
					///
					void AdaptScene( std::vector<int>& viSourcesOutsideRoom, std::vector<int>& viReceiversOutsideRoom );

					///
					/// \brief Compute the direct sound for all source-receiver-pairs in the scene.
					/// \param[out] vpResult the results for the computation.
					///
					void ComputeDirectSoundAudibility( std::vector<std::unique_ptr<CRavenSimulationResult::ComplexSimulationSoundPath> >& vpResult );

					///
					/// \brief Compute audibility of direct sound for a source-receiver-pair.
					/// \param iSourceID the ID of the source.
					/// \param iReceiverID the ID of the receiver.
					/// \param[out] bAudibility true if direct sound is audible.
					/// \todo fix return.
					/// \todo const ref.
					///
					void ComputeDirectSoundAudibility( const int iSourceID, const int iReceiverID, bool& bAudibility );

					///
					/// \brief Compute the direct sound for all source-receiver-pairs in the scene.
					/// \param[out] vpResult the results for the computation.
					/// \param iResultMixingMode mixing mode for the filter.
					///
					void ComputeDirectSound( std::vector<std::unique_ptr<CRavenSimulationResult::ComplexSimulationSoundPath> >& vpResult,
					                         const int iResultMixingMode = ITABase::MixingMethod::ADD );

					///
					/// \brief Compute direct sound for a source-receiver-pair.
					/// \param iSourceID the ID of the source.
					/// \param iReceiverID the ID of the receiver.
					/// \param[out] oFilter the resulting filter.
					/// \param iResultMixingMode mixing mode for the filter.
					/// \todo fix return.
					/// \todo const ref.
					/// \todo remove mixing mode ... only one thing to simulate, thus no mixing.
					///
					void ComputeDirectSound( const int iSourceID, const int iReceiverID, ITASampleFrame& oFilter, const int iResultMixingMode );

					///
					/// \brief Compute the image sources for all source-receiver-pairs in the scene.
					/// \param[out] vpResult the results for the computation.
					/// \param iResultMixingMode mixing mode for the filter.
					///
					void ComputeImageSources( std::vector<std::unique_ptr<CRavenSimulationResult::ComplexSimulationSoundPath> >& vpResult,
					                          const int iResultMixingMode = ITABase::MixingMethod::ADD );

					///
					/// \brief Compute image sources for a source-receiver-pair.
					/// \param iSourceID the ID of the source.
					/// \param iReceiverID the ID of the receiver.
					/// \param[out] oFilter the resulting filter.
					/// \param iResultMixingMode mixing mode for the filter.
					/// \todo fix return.
					/// \todo const ref.
					/// \todo remove mixing mode ... only one thing to simulate, thus no mixing.
					///
					void ComputeImageSources( const int iSourceID, const int iReceiverID, ITASampleFrame& oFilter, const int iResultMixingMode );

					///
					/// \brief Compute the ray-tracing for all source-receiver-pairs in the scene.
					/// \param[out] vpResult the results for the computation.
					/// \param iResultMixingMode mixing mode for the filter.
					/// \todo remove mixing mode we probably don't need it anymore.
					///
					void ComputeRayTracing( std::vector<std::unique_ptr<CRavenSimulationResult::ComplexSimulationSoundPath> >& vpResult,
					                        const int iResultMixingMode = ITABase::MixingMethod::ADD );


					///
					/// \brief Compute ray-tracing form one source to all given receivers.
					/// \param iSourceID the ID of the source.
					/// \param viReceiverIDs the IDs of all receivers to compute.
					/// \param[out] vpResult vector of the resulting filter.
					/// \param iResultMixingMode mixing mode for the filter.
					/// \todo remove mixing mode we probably don't need it anymore.
					///
					void ComputeRayTracing( const int iSourceID, const std::vector<int>& viReceiverIDs, std::vector<ITASampleFrame*>& vpResult,
					                        const int iResultMixingMode = ITABase::MixingMethod::ADD );

					///
					/// \brief Add a receiver with the given ID.
					/// \note Internally, a Raven ID is assigned to the receiver.
					/// \param iID the ID for the new receiver.
					///
					void AddReceiver( const int iID );

					///
					/// \brief Remove the receiver with the given ID.
					/// \param iID the ID of the receiver to be removed.
					///
					void RemoveReceiver( const int iID );

					///
					/// \brief Add a source with the given ID.
					/// \note Internally, a Raven ID is assigned to the source.
					/// \param iID the ID for the new source.
					///
					void AddSource( const int iID );

					///
					/// \brief Remove the source with the given ID.
					/// \param iID the ID of the source to be removed.
					///
					void RemoveSource( const int iID );

					///
					/// \brief Set the receiver state of the source with the given ID.
					/// \param iID the ID of the receiver to be set.
					/// \param oState the new receiver state.
					/// \param eFlags flags of the parameters to be set.
					/// \return true if the receiver is still inside the room.
					/// \todo jst: SimulationType mitgeben und nur die calls ausführen, die wirklich benötigt werden -> ppa: Ist das schneller?
					///
					bool SetReceiverState( const int iID, const CRavenScene::CReceiverState& oState, const CRavenScene::CReceiverState::DifferenceFlags eFlags );

					///
					/// \brief Set the source state of the source with the given ID.
					/// \param iID the ID of the source to be set.
					/// \param oState the new source state.
					/// \param eFlags flags of the parameters to be set.
					/// \return true if the source is still inside the room.
					/// \todo jst: SimulationType mitgeben und nur die calls ausführen, die wirklich benötigt werden -> ppa: Ist das schneller?
					///
					bool SetSourceState( const int iID, const CRavenScene::CSourceState& oState, const CRavenScene::CSourceState::DifferenceFlags& eFlags );

					///
					/// \brief Replaces "RavenDataBasePath" with m_sRavenDataBasePath.
					/// \param[out] s the string to replace.
					///
					void SubstituteMacros( std::string& s );
				};

				inline bool operator<( const CSimulator::SimulatorStatus& lhs, const CSimulator::SimulatorStatus& rhs )
				{
					return std::underlying_type_t<CSimulator::SimulatorStatus>( lhs ) < std::underlying_type_t<CSimulator::SimulatorStatus>( rhs );
				}

			} // namespace Raven
		}     // namespace RoomAcoustics
	}         // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_ROOM_ACOUSTICS_RAVEN_SIMULATOR
#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_ROTATION_FILTER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_ROTATION_FILTER

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/AudibilityFilter/audibility_filter_interface.h>

// std includes
#include <valarray>

namespace ITA
{
	namespace SimulationScheduler
	{
		class CUpdateScene;

		namespace AudibilityFilter
		{
			///
			/// \brief Rotation filter
			///
			/// This class implements a simple rotation filter.
			/// Depending on the rotation mode, the audibility is checked differently.
			/// If the relative mode is chosen, first, the azimuth and elevation angle for the source with the receiver as target is calculated and vice versa.
			/// If the delta between the previous angles and the new angles exceed the configured threshold, the update is deemed audible.
			///
			/// If the absolute mode is chosen, just the absolute rotation of source or receiver is checked against the threshold.
			///
			/// For an example, consider the use of a 5x5 HRTF.
			/// The threshold for the receiver could be set to 2.5 degree to allow a 5 degree "inaudible" zone around the previous angle.
			///
			class ITA_SIMULATION_SCHEDULER_API CRotationFilter : public IAudibilityFilter
			{
			public:
				///
				/// \brief Rotation modes for the CRotationFilter.
				///
				enum class RotationModes
				{
					relative, ///< In this mode, the rotation relative to the opposite element is considered, thus also translation can lead to a rotation.
					absolute  ///< In this mode, only the absolute rotation od source and receiver is considered.
				};

				///
				/// \brief Configuration class for the rotation filter.
				///
				struct ITA_SIMULATION_SCHEDULER_API RotationFilterConfig : public IAudibilityFilter::AudibilityFilterConfig
				{
					explicit RotationFilterConfig( );

					double dSourceThreshold = 2.5;

					double dReceiverThreshold = 2.5;

					RotationModes eMode = RotationModes::absolute;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				CRotationFilter( ) = delete;

				///
				/// \brief Constructor for a CRotationFilter.
				///
				/// This constructor configures the CRotationFilter with the given \p oConfig.
				/// \param oConfig the configuration for the CRotationFilter.
				///
				explicit CRotationFilter( const RotationFilterConfig& oConfig );

				//
				///
				/// \brief Check if the change between \p previousState and \p newUpdate is audible.
				///
				/// The change between \p previousState and \p newUpdate is audible when the rotation of source and receiver exceed the configured thresholds given the
				/// configured RotationMode.
				///
				/// \param previousState the previous state of the scene to check against.
				/// \param newUpdate the CUpdateScene to check for audibility.
				/// \return true if the change between \p previousState and \p newUpdate is audible, else false.
				///
				virtual bool ChangeIsAudible( const CUpdateScene& previousState, const CUpdateScene& newUpdate ) const override;

				///
				/// \brief Return a unique type identifying string.
				/// \return a unique type identifying string.
				///
				static std::string GetType( );

				///
				/// \brief Factory function for a filter.
				/// \remark This function should to be static.
				///
				static std::unique_ptr<IAudibilityFilter> CreateFilter( const std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>& pConfig );

			private:
				///
				/// \brief Check if the relative rotation of source and receiver exceeds the configured thresholds.
				///
				/// This method considers the rotation relative to the opposite element, thus also translation can lead to a rotation.
				/// \param previousState the previous state of the scene to check against.
				/// \param newUpdate the CUpdateScene to check for audibility.
				/// \return true if the change between \p previousState and \p newUpdate is audible, else false.
				///
				bool CheckRelativeRotation( const CUpdateScene& previousState, const CUpdateScene& newUpdate ) const;

				///
				/// \brief Check if the absolute rotation of source and receiver exceeds the configured thresholds.
				///
				/// This method only considers the absolute rotation of source and receiver.
				/// \param previousState the previous state of the scene to check against.
				/// \param newUpdate the CUpdateScene to check for audibility.
				/// \return true if the change between \p previousState and \p newUpdate is audible, else false.
				///
				bool CheckAbsoluteRotation( const CUpdateScene& previousState, const CUpdateScene& newUpdate ) const;

				///
				/// \brief The minimum translation, above which the filter deems the update audible.
				///
				double m_dSourceThreshold = 1.0;

				///
				/// \brief The minimum translation, above which the filter deems the update audible.
				///
				double m_dReceiverThreshold = 1.0;

				///
				/// \brief Mode in which the rotation should be evaluated.
				///
				RotationModes m_eRotationMode = RotationModes::absolute;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_ROTATION_FILTER
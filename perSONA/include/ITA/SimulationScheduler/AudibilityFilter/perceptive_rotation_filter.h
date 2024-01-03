#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_PERCEPTIVE_ROTATION_FILTER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_PERCEPTIVE_ROTATION_FILTER

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/AudibilityFilter/audibility_filter_interface.h>

// std includes
#include <map>

namespace ITA
{
	namespace SimulationScheduler
	{
		class CUpdateScene;

		namespace AudibilityFilter
		{
			///
			/// \brief Perceptive rotation filter.
			///
			/// This class implements a perceptive rotation filter.
			/// The human ability to localize sound in 3D space around them is not 100% accurate in all directions.
			/// As such, this fact can be utilized to determine the audibility of a rotation.
			/// Note however, that this only works if the direction of arrival is known.
			///
			/// The accuracy of human localization is taken from [1-3].
			///
			/// \sa [1] - Makous & Middlebrooks, Two-dimensional sound localization by human listeners, 1990
			/// \sa [2] - Blauert, Spatial Hearing, 1984
			/// \sa [3] - Damaske & Wagener, Richtungshörversuche über einen nachgebildeten Kopf, 1969
			///
			class ITA_SIMULATION_SCHEDULER_API CPerceptiveRotationFilter : public IAudibilityFilter
			{
			public:
				///
				/// \brief Configuration class for the perceptive rotation filter.
				///
				struct ITA_SIMULATION_SCHEDULER_API PerceptiveRotationFilterConfig : public IAudibilityFilter::AudibilityFilterConfig
				{
					explicit PerceptiveRotationFilterConfig( );

					double dStrengthFactor = 1.0;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				CPerceptiveRotationFilter( ) = delete;

				///
				/// \brief Constructor for a CPerceptiveRotationFilter.
				///
				/// This constructor configures the CPerceptiveRotationFilter with the given \p oConfig.
				/// \param oConfig the configuration for the CPerceptiveRotationFilter.
				///
				explicit CPerceptiveRotationFilter( const PerceptiveRotationFilterConfig& oConfig );

				//
				///
				/// \brief Check if the change between \p previousState and \p newUpdate is audible.
				///
				/// The change between \p previousState and \p newUpdate is audible when the rotation of the receiver relative to the source exceeds the threshold given
				/// by the localization uncertainty.
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
				/// \brief Find the nearest data point to the given direction.
				///
				/// First the neares azimuth angle is identified, and seconf the nearest elevation angle.
				/// \param azimuth azimuth angle for the query direction.
				/// \param elevation elevation angle for the query direction.
				/// \return the data point for the given direction
				/// @todo Check, if integer parameters should be replace by floating point type
				///
				static std::pair<double, double> FindNearest( int azimuth, int elevation );

				///
				/// \brief Strength factor
				///
				/// With this parameter the strength of the condition can be adjusted.
				/// A value of one corresponds to the full threshold.
				/// A value of zero corresponds to no threshold, thus every update is audible.
				///
				double m_dStrengthFactor = 1.0;

				///
				/// \brief 2D map containing human localization accuracy.
				///
				/// The data is ordered as [Azimuth, Elevation] -> [Azimuth error, Elevation error].
				///
				static const std::map<int, std::map<int, std::pair<double, double> > > m_mmLocalizationUncertainty;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_PERCEPTIVE_ROTATION_FILTER
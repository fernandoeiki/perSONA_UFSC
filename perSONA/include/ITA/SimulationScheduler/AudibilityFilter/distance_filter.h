#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_DISTANCE_FILTER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_DISTANCE_FILTER

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/AudibilityFilter/audibility_filter_interface.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		class CUpdateScene;

		namespace AudibilityFilter
		{
			///
			/// \brief Reverberation radius filter
			///
			/// This class implements a distance filter.
			/// This means, the update is considered audible, when the distance between source and receiver is smaller than the configured distance.
			///
			class ITA_SIMULATION_SCHEDULER_API CDistanceFilter : public IAudibilityFilter
			{
			public:
				///
				/// \brief Configuration class for the distance filter.
				///
				struct ITA_SIMULATION_SCHEDULER_API DistanceFilterConfig : public IAudibilityFilter::AudibilityFilterConfig
				{
					explicit DistanceFilterConfig( );

					double dDistanceThreshold = 5.0;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				CDistanceFilter( ) = delete;

				///
				/// \brief Constructor for a CDistanceFilter.
				///
				/// This constructor configures the CDistanceFilter with the given \p oConfig.
				/// \param oConfig the configuration for the CDistanceFilter.
				///
				explicit CDistanceFilter( const DistanceFilterConfig& oConfig );

				//
				///
				/// \brief Check if the change between \p previousState and \p newUpdate is audible.
				///
				/// The change between \p previousState and \p newUpdate is audible when the distance between the source and receiver is smaller than the configured
				/// distance threshold.
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
				/// \brief The distance threshold of the filter.
				///
				double m_dDistanceThreshold;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_DISTANCE_FILTER
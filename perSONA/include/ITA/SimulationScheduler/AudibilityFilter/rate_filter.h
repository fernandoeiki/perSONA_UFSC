#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_RATE_FILTER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_RATE_FILTER

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/AudibilityFilter/audibility_filter_interface.h>

// Vista includes
#include <VistaAspects/VistaPropertyList.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		class CUpdateScene;

		namespace AudibilityFilter
		{
			///
			/// \brief Rate filter
			///
			/// This class implements a simple rate filter.
			/// Only if the time interval between the two updates exceeds the configured rate, the update is considered audible.
			///
			class ITA_SIMULATION_SCHEDULER_API CRateFilter : public IAudibilityFilter
			{
			public:
				///
				/// \brief Configuration class for the rate filter.
				///
				struct ITA_SIMULATION_SCHEDULER_API RateFilterConfig : public IAudibilityFilter::AudibilityFilterConfig
				{
					explicit RateFilterConfig( );

					double dRate = 1.0;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				CRateFilter( ) = delete;

				///
				/// \brief Constructor for a CRateFilter.
				///
				/// This constructor configures the CRateFilter with the given \p oConfig.
				/// \param oConfig the configuration for the CRateFilter.
				///
				explicit CRateFilter( const RateFilterConfig& oConfig );

				//
				///
				/// \brief Check if the change between \p previousState and \p newUpdate is audible.
				///
				/// The change between \p previousState and \p newUpdate is audible when the time between the two updates is larger than the configured rate.
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
				/// \brief The minimum rate of the filter.
				///
				double m_dRate;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_RATE_FILTER
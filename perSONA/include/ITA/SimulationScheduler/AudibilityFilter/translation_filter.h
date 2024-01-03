#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_TRANSLATION_FILTER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_TRANSLATION_FILTER

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
			/// \brief Translation filter
			///
			/// This class implements a simple translation filter.
			/// Only if the length of the translation vector between the previous and new source or receiver position exceeds the configured distance, the update is
			/// audible.
			///
			class ITA_SIMULATION_SCHEDULER_API CTranslationFilter : public IAudibilityFilter
			{
			public:
				///
				/// \brief Translation modes for the CTranslationFilter.
				///
				enum class TranslationModes
				{
					relative, ///< In this mode, the distance relative to previous distance is considered.
					absolute  ///< In this mode, only the absolute translation of source and receiver is considered.
				};

				///
				/// \brief Configuration class for the translation filter.
				///
				struct ITA_SIMULATION_SCHEDULER_API TranslationFilterConfig : public IAudibilityFilter::AudibilityFilterConfig
				{
					explicit TranslationFilterConfig( );

					double dThreshold = 5.0;

					TranslationModes eMode = TranslationModes::absolute;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				CTranslationFilter( ) = delete;

				///
				/// \brief Constructor for a CTranslationFilter.
				///
				/// This constructor configures the CTranslationFilter with the given \p oConfig.
				/// \param oConfig the configuration for the CTranslationFilter.
				///
				explicit CTranslationFilter( const TranslationFilterConfig& oConfig );

				//
				///
				/// \brief Check if the change between \p previousState and \p newUpdate is audible.
				///
				/// The change between \p previousState and \p newUpdate in absolute mode is audible when the length of the translation vector of source or receiver is
				/// larger than the configured threshold. The change between \p previousState and \p newUpdate in relative mode is audible when the quotient of the new
				/// and previous distance between source and receiver is larger than the configured threshold. 
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
				/// \brief The minimum translation, above which the filter deems the update audible.
				///
				double m_dThreshold = 1.0;

				///
				/// \brief Mode in which the translation should be evaluated.
				///
				TranslationModes m_eTranslationMode = TranslationModes::absolute;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_TRANSLATION_FILTER
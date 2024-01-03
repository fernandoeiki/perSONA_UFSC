#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_AUDIBILITY_FILTER_INTERFACE
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_AUDIBILITY_FILTER_INTERFACE

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/config_interface.h>

// std includes
#include <functional>
#include <memory>
#include <vector>

namespace ITA
{
	namespace SimulationScheduler
	{
		class CUpdateScene;

		namespace AudibilityFilter
		{
			///
			/// \brief The interface for an audibility filter.
			///
			/// An audibility filter is used to determine the audibility of the change between two CUpdateScenes.
			///
			/// An audibility filter is created by CAudibilityFilterFactory.
			/// For this, a function like this is necessary:
			/// \code{.cpp}
			/// ///
			/// /// \brief Factory function for an audibility filter.
			/// /// \remark This function should to be static.
			/// ///
			/// static std::unique_ptr<IAudibilityFilter> createFilter ( const std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>& pConfig );
			/// \endcode
			///
			class ITA_SIMULATION_SCHEDULER_API IAudibilityFilter
			{
			public:
				///
				/// \brief Usage mode for audibility filter.
				///
				enum class UsageMode
				{
					filter,   ///< Use the audibility filter as an actual filter.
					condition ///< Use the audibility filter as a condition for following filters.
				};

				///
				/// \brief Base configuration class for audibility filter.
				///
				/// \note ::sFilterType is a read only property of the AudibilityFilterConfig.
				/// Due to this the copy constructor and assignment operator are needed.
				///
				struct ITA_SIMULATION_SCHEDULER_API AudibilityFilterConfig : public IConfig
				{
					AudibilityFilterConfig( );

					explicit AudibilityFilterConfig( std::string sType );

					AudibilityFilterConfig( const AudibilityFilterConfig& other );

					AudibilityFilterConfig& operator=( const AudibilityFilterConfig& other );

					std::string sFilterName = "Unknown";

					const std::string& sFilterType;

					std::vector<std::string> sNextFilter;

					UsageMode eUsageMode = UsageMode::filter;

					bool bInvertCondition = false;

					VistaPropertyList Store( ) const override = 0;

					void Load( const VistaPropertyList& oProperties ) override = 0;

				private:
					std::string m_sFilterType;
				};

				///
				/// \brief Check if the change between \p previousState and \p newUpdate is audible.
				/// \param previousState the previous state of the scene to check against.
				/// \param newUpdate the CUpdateScene to check for audibility.
				/// \return true if the change between \p previousState and \p newUpdate is audible, else false.
				///
				virtual bool ChangeIsAudible( const CUpdateScene& previousState, const CUpdateScene& newUpdate ) const = 0;

			protected:
				///
				/// \brief Checks weather the \p newUpdate happened after \p previousState.
				/// \note This method should be called first in every ::changeIsAudible.
				/// \throws ITAExcept when \p previousState happened after \p newUpdate.
				/// \param previousState CUpdateScene of the previous state.
				/// \param newUpdate new CUpdateScene.
				///
				static void CheckUpdateTimestamp( const CUpdateScene& previousState, const CUpdateScene& newUpdate );
			};

			///
			/// \brief Factory class for filter.
			///
			/// This class implements an extensible factory for filter.
			/// After a type of filter is registered with its IAudibilityFilter::createFilter, it can be created using this factory.
			/// \todo Add a way to get the correct config from the type. The factory already knows of all possible filters.
			///
			class ITA_SIMULATION_SCHEDULER_API CAudibilityFilterFactory
			{
			public:
				///
				/// \brief The function signature for a create function.
				///
				typedef std::function<std::unique_ptr<IAudibilityFilter>( const std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>& pConfig )> CreateCallback;

				///
				/// \brief The function signature for a config create function.
				///
				typedef std::function<std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>( )> ConfigCreateCallback;

				///
				/// \brief Register a type of filter to the factory.
				/// \param type name of the filter type to be registered.
				/// \param createFunction the corresponding create function.
				/// \param configCreateFunction the corresponding config create function.
				///
				static void RegisterFilter( const std::string& type, CreateCallback createFunction, ConfigCreateCallback configCreateFunction );

				///
				/// \brief Unregister a type of filter from the factory.
				/// \param type name of the filter type to be removed.
				///
				static void UnregisterFilter( const std::string& type );

				///
				/// \brief Factory method.
				/// \param pConfig the configuration for the filter.
				/// \return a pointer to the created filter.
				///
				static std::unique_ptr<IAudibilityFilter> CreateFilter( const std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>& pConfig );

				///
				/// \brief Factory method for filter configs.
				/// \param sType the configuration for the filter.
				/// \return a pointer to the created filter config.
				///
				static std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig> CreateConfig( const std::string& sType );

			private:
				///
				/// \brief Map containing all creation functions.
				///
				static std::map<std::string, std::pair<CreateCallback, ConfigCreateCallback>> m_mFilters;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_AUDIBILITY_FILTER_INTERFACE
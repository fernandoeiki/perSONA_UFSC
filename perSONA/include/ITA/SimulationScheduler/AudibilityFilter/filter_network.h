#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_FILTER_NETWORK
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_FILTER_NETWORK

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/AudibilityFilter/audibility_filter_interface.h>
#include <ITA/SimulationScheduler/config_interface.h>

// std includes
#include <memory>
#include <unordered_map>
#include <vector>

namespace ITA
{
	namespace SimulationScheduler
	{
		class CUpdateScene;

		namespace AudibilityFilter
		{
			///
			/// \brief This class models a network of audibility filters.
			///
			/// It enables a easy building an evaluation of the configured network.
			/// The actual network is modeled as a tree.
			/// Even though in trees paths can not merge, a tree enables an easy way to model the network.
			/// However, merging paths can still be modeled this way.
			///
			class ITA_SIMULATION_SCHEDULER_API CFilterNetwork
			{
			public:
				///
				/// \brief Configuration class for CFilterNetwork.
				///
				struct ITA_SIMULATION_SCHEDULER_API FilterNetworkConfig : public IConfig
				{
					std::vector<std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>> vpFilterConfigs;

					std::string sStartFilter;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				CFilterNetwork( ) = delete;

				CFilterNetwork( const CFilterNetwork& ) = delete;

				CFilterNetwork& operator=( const CFilterNetwork& ) = delete;

				///
				/// \brief Constructor for CFilterNetwork.
				/// \param oConfig the FilterNetworkConfig to configure the CFilterNetwork.
				///
				explicit CFilterNetwork( const FilterNetworkConfig& oConfig );

				///
				/// \brief Evaluate the CFilterNetwork.
				///
				/// This method goes through the configured network and checks weather the \p newUpdate is audible.
				/// \param previousState the previous state of the scene to check against.
				/// \param newUpdate the CUpdateScene to check.
				/// \return true if the change between \p previousState and \p newUpdate is audible, else false.
				///
				bool EvaluateNetwork( const CUpdateScene& previousState, const CUpdateScene& newUpdate ) const;

			private:
				///
				/// \brief Tree node used to model the actual network.
				///
				class NetworkTreeNode
				{
				public:
					///
					/// \brief Default constructor for NetworkTreeNode.
					///
					NetworkTreeNode( ) = default;

					///
					/// \brief Constructor for NetworkTreeNode.
					///
					/// This constructor set the filter to be executed for the tree node and how it should be used.
					/// \p bInvertCondition is only used if the UsageMode is set to be a condition.
					/// \param pFilter the filter to be executed for the tree node.
					/// \param sFilterName name of the filter.
					/// \param eUsageMode the UsageMode for the filter.
					/// \param bInvertCondition true, if the condition should be inverted.
					///
					NetworkTreeNode( const IAudibilityFilter* pFilter, std::string sFilterName, IAudibilityFilter::UsageMode eUsageMode, bool bInvertCondition );

					///
					/// \brief Evaluate the tree nodes filter and its children.
					///
					/// This method first evaluates the filter or condition for this node.
					/// Depending on the result, the children of this node are evaluated next.
					/// \param previousState the previous state of the scene to check against.
					/// \param newUpdate the CUpdateScene to check.
					/// \return true if the change between \p previousState and \p newUpdate is audible, else false.
					///
					bool Evaluate( const CUpdateScene& previousState, const CUpdateScene& newUpdate );

					///
					/// \brief Children of the node.
					///
					std::vector<NetworkTreeNode> vChildren;

				private:
					///
					/// \brief The audibility filter of the tree node.
					///
					const IAudibilityFilter* m_pFilter;

					///
					/// \brief The usage mode for the filter.
					///
					IAudibilityFilter::UsageMode m_eUsageMode;

					///
					/// \brief True, if the condition should be inverted.
					///
					bool m_bInvertCondition;

					///
					/// \brief Name of the filter of the tree node.
					/// \note This is primarily used for profiling.
					///
					std::string m_sFilterName;
				};

				///
				/// \brief Create all the actual filter instances that were configured.
				/// \param vpFilterConfigs vector of all filters that should be created.
				///
				void CreateFilters( const std::vector<std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>>& vpFilterConfigs );

				///
				/// \brief Build the network tree.
				/// \param oConfig configuration from which to build the tree.
				///
				void BuildNetwork( const FilterNetworkConfig& oConfig );

				///
				/// \brief Recursive helper method for building the network tree.
				/// \param mConfigMap map relating the filter name to its config.
				/// \param oRoot the root from which to build the tree.
				/// \param oRootConfig
				///
				void NetworkBuilderHelper( const std::map<std::string, std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>>& mConfigMap, NetworkTreeNode& oRoot,
				                           const IAudibilityFilter::AudibilityFilterConfig& oRootConfig );

				///
				/// \brief Map containing all configured filters, keyed by their names.
				///
				std::unordered_map<std::string, std::unique_ptr<IAudibilityFilter>> m_mAudibilityFilters;

				///
				/// \brief The actual network tree of the CFilterNetwork.
				///
				std::unique_ptr<NetworkTreeNode> m_pNetworkTree;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_FILTER_NETWORK
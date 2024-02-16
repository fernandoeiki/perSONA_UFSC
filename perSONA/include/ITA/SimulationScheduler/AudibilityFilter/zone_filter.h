#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_ZONE_FILTER
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_ZONE_FILTER

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
			/// \brief Zone filter.
			///
			/// This class implements a simple zone filter.
			/// Zones are cuboids defined by two points in 3D space.
			/// A Zone filter can have more than one of these zones.
			///
			class ITA_SIMULATION_SCHEDULER_API CZoneFilter : public IAudibilityFilter
			{
			public:
				///
				/// \brief Configuration class for CZoneFilter.
				///
				struct ITA_SIMULATION_SCHEDULER_API ZoneFilterConfig : AudibilityFilterConfig
				{
					explicit ZoneFilterConfig( );

					///
					/// \brief The zones for the config.
					///
					/// Zones are cuboids defined by two points in 3D space.
					/// As such, the definition is represented by a pair of VistaVector3D%s.
					std::vector<std::pair<VistaVector3D, VistaVector3D>> vpZones;

					VistaPropertyList Store( ) const override;

					void Load( const VistaPropertyList& oProperties ) override;
				};

				CZoneFilter( ) = delete;

				///
				/// \brief Constructor for CZoneFilter.
				/// \param oConfig the ZoneFilterConfig used to configure the CZoneFilter.
				///
				explicit CZoneFilter( const ZoneFilterConfig& oConfig );

				///
				/// \brief Checks if source or receiver of \p newUpdate lie inside any of the defined zones.
				/// \param previousState the previous state of the scene to check against.
				/// \param newUpdate the CUpdateScene to check.
				/// \remark \p previousState is not used by this function.
				/// \return true, source or receiver of \p newUpdate lie inside any of the defined zones.
				///
				bool ChangeIsAudible( const CUpdateScene& previousState, const CUpdateScene& newUpdate ) const override;

				///
				/// \brief Return a unique type identifying string.
				/// \return a unique type identifying string.
				///
				static std::string GetType( );

				///
				/// \brief Factory function for CZoneFilter.
				/// \remark This function should to be static.
				///
				static std::unique_ptr<IAudibilityFilter> CreateFilter( const std::shared_ptr<IAudibilityFilter::AudibilityFilterConfig>& pConfig );

			private:
				///
				/// \brief Zones of the CZoneFilter.
				///
				/// Zones are cuboids defined by two points in 3D space.
				/// As such, the definition is represented by a pair of VistaVector3D%s.
				///
				std::vector<std::pair<VistaVector3D, VistaVector3D>> m_vpZones;
			};
		} // namespace AudibilityFilter
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_AUDIBILITY_FILTER_ZONE_FILTER
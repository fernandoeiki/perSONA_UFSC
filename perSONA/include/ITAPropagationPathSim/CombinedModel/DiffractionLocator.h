#ifndef INCLUDE_WATCHER_DIFFRACTION_LOCATOR
#define INCLUDE_WATCHER_DIFFRACTION_LOCATOR

#include <ITABase/ITAProgress.h>
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/Utils.h>
#include <ITAPropagationPathSim/CombinedModel/PropagationShapes.h>

namespace ITAPropagationPathSim
{
	namespace CombinedModel
	{
		using namespace ITAGeo;


		namespace Diffraction
		{
			ITA_PROPAGATION_PATH_SIM_API bool ConstructAperturePoints( std::shared_ptr<const CPropagationAnchor> pEmitter,
			                                                           std::shared_ptr<const CPropagationAnchor> pSensor, const int iNumberIterations,
			                                                           const std::vector<CPropagationShapeShared> pPropagationListsIn,
			                                                           std::vector<CPropagationShapeShared>& pPropagationListsOut,
			                                                           ITABase::IProgressHandler* pProgressHandler = nullptr );

			//!< Exclude propagation paths with an accumulated diffraction angle that is bigger than the angle threshold.
			ITA_PROPAGATION_PATH_SIM_API bool AccumulatedAngleCulling( const float fAngleThreshold, std::shared_ptr<const CPropagationAnchor> pEmitter,
			                                                           const std::vector<CPropagationShapeShared> pPropagationTreeIn,
			                                                           std::vector<CPropagationShapeShared>& pPropagationTreeOut );

			ITA_PROPAGATION_PATH_SIM_API bool AccumulatedAngleCulling( const float fAngleThreshold, std::shared_ptr<const CPropagationAnchor> pEmitter,
			                                                           std::shared_ptr<const CPropagationAnchor> pSensor,
			                                                           const std::vector<CPropagationShapeShared> pPropagationListsIn,
			                                                           std::vector<CPropagationShapeShared>& pPropagationListsOut );
		} // namespace Diffraction

	} // namespace CombinedModel

} // namespace ITAPropagationPathSim

#endif // INCLUDE_WATCHER_DIFFRACTION_LOCATOR

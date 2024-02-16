#ifndef INCLUDE_WATCHER_REFLECTION_LOCATOR
#define INCLUDE_WATCHER_REFLECTION_LOCATOR


// ITA includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/Utils.h>
#include <ITAPropagationPathSim/CombinedModel/PropagationShapes.h>


namespace ITAPropagationPathSim
{
	namespace CombinedModel
	{
		namespace Reflection
		{
			ITA_PROPAGATION_PATH_SIM_API bool ConstructPointsOfReflection( std::shared_ptr<const ITAGeo::CPropagationAnchor> pSensor,
			                                                               const std::vector<CPropagationShapeShared> pPropagationListsIn,
			                                                               std::vector<CPropagationShapeShared>& pPropagationListsOut );
		}
	} // namespace CombinedModel
} // namespace ITAPropagationPathSim

#endif // INCLUDE_WATCHER_REFLECTION_LOCATOR

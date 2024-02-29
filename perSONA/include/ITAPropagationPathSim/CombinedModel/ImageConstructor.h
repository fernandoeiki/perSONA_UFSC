#ifndef INCLUDE_WATCHER_IMAGE_CONSTRUCTOR
#define INCLUDE_WATCHER_IMAGE_CONSTRUCTOR


#include <ITAPropagationPathSim/CombinedModel/PropagationShapes.h>

// ITA includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/Utils.h>

namespace ITAPropagationPathSim
{
	namespace CombinedModel
	{
		using namespace ITAGeo;


		namespace ImageConstruction
		{
			ITA_PROPAGATION_PATH_SIM_API bool ConstructImages( const VistaVector3D& v3Pos, std::vector<CPropagationShapeShared>& vpPropagationTree );

			ITA_PROPAGATION_PATH_SIM_API bool ConstructImageApertures( const std::vector<CPropagationShapeShared> vpPropagationListsIn,
			                                                           std::vector<CPropagationShapeShared>& vpPropagationListsOut );

			ITA_PROPAGATION_PATH_SIM_API bool ConstructImageEdges( std::vector<CPropagationShapeShared>& vpPropagationTree );
		} // namespace ImageConstruction
	}     // namespace CombinedModel
} // namespace ITAPropagationPathSim

#endif // INCLUDE_WATCHER_IMAGE_CONSTRUCTOR

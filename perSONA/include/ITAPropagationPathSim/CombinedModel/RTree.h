#ifndef INCLUDE_WATCHER_PROPAGATION_RTREE
#define INCLUDE_WATCHER_PROPAGATION_RTREE


// ITAGeo
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/ModelBase.h>
#include <ITAGeo/Utils.h>
#include <ITAPropagationPathSim/CombinedModel/PropagationShapes.h>


namespace ITAPropagationPathSim
{
	namespace CombinedModel
	{
		// Typedefs
		typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

		//! Buildings RTree class
		/**
		 * @todo
		 *
		 */
		class ITA_PROPAGATION_PATH_SIM_API CShapesTree
		{
		public:
			//---Constructor and Destructor---------------------------------------------
			CShapesTree( );

			~CShapesTree( );

			//---Public member functions------------------------------------------------

			void Create( const std::vector<CPropagationShapeShared>& vpShapesIn );

			// TODO
			bool CanLineSegmentIntersect( const VistaVector3D& oLineStart, const VistaVector3D& oLineEnd, const CPropagationShapeShared& oShape ) const;
			bool CanLineSegmentIntersect( const VistaVector3D& oLineStart, const VistaVector3D& oLineEnd ) const;

			bool RecursiveIntersectionTest( const VistaVector3D& oLineStart, const VistaVector3D& oLineEnd, const CShapesTree& oTree,
			                                const CPropagationShapeShared& oShape ) const;
			bool RecursiveIntersectionTest( const VistaVector3D& oLineStart, const VistaVector3D& oLineEnd, const CShapesTree& oTree ) const;

			bool ContainsShape( const CPropagationShapeShared& oShape ) const;
			// TODO
			// void GetNonIntersectedFaces(vector<CPropagationShapeShared>& vpFacesOut, const VistaVector3D& oLineStart, const VistaVector3D& oLineStart);

			/*TODO: For faster illumination tests
			void GetIlluminableShapes(vector<CPropagationShapeShared>& vpShapesOut, const VistaPlane& oPlaneIn);

			void GetIlluminableShapes(vector<CPropagationShapeShared>& vpShapesOut, const CPropagationFaceShared& pFace);

			void GetIlluminableShapes(vector<CPropagationShapeShared>& vpShapesOut, const CPropagationEdgeShared& pEdge);
			*/


			//---Public member variables------------------------------------------------

		private:
			//---Private member functions-----------------------------------------------

			void SetVertices( );

			void CreateBranches( );

			//---Private member variables-----------------------------------------------

			// Minimum and maximum of bounding box as well as vertices of box
			VistaVector3D m_v3TreeMin;
			VistaVector3D m_v3TreeMax;

			// Vector of shapes within bounding box
			std::vector<CPropagationShapeShared> m_vpShapes;

			// Branches
			std::vector<std::shared_ptr<CShapesTree>> m_vpBranches;
		};
	} // namespace CombinedModel
} // namespace ITAPropagationPathSim


#endif // INCLUDE_WATCHER_PROPAGATION_RTREE
/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 * 				    ____  __________  _______
 *				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 *				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 * ----------------------------------------------------------------
 *
 */

#include <ITAPropagationPathSim/Definitions.h>

// ITA includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/Utils.h>


namespace ITAPropagationPathSim
{
	namespace BaseEngine
	{
		// Typedefs
		typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

		class ITA_PROPAGATION_PATH_SIM_API CDiffractionPath
		{
			// Forward declaration
			struct DiffractionEdge;
			// Typedefs
			typedef std::map<std::string, std::set<std::shared_ptr<DiffractionEdge>>> DiffractionEdgesMap;
			typedef std::pair<std::string, CITAMesh::EdgeHandle> MeshListEdgeHandle;

		public:
			//---Constructor and Destructor---------------------------------------------------------------------------------------

			//! Construct an base diffraction engine for simple simulation
			/**
			 * Creates a copy if the model and pre-allocates all image sources.
			 *
			 * @param[in] oMeshModelList Mesh model list (will be copied)
			 * @param[in] iDiffractionOrder Defaults to 2 (first order diffraction of sending entity / source)
			 *
			 */
			CDiffractionPath( ITAGeo::Halfedge::CMeshModelList pMeshModelList, const int iDiffractionOrder = ITAGeo::ORDER_2 );

			//! Construct the diffraction path from the origin to the destination anchor
			/**
			 * Construct the diffraction path from the origin to the destination anchor.
			 *
			 * @param[in] pDestinationAnchor Entity anchor from which the pathlist is constructed
			 * @param[out] oPathList To be constructed path list
			 *
			 */
			void ConstructDiffractionPaths( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPathList& oPathList );

			bool CalculateDiffractionPath( std::vector<std::shared_ptr<DiffractionEdge>>& vpCurrentDiffractionPathEdges, ITAGeo::CPropagationPath* pPath );

			//! Construct the diffraction tree beginning at the illuminated edges
			/**
			 * Construct the diffraction tree beginning at the illuminated edges
			 *
			 * @param[in] pOrigin Propagation anchor from which the illuminated edges are calculated
			 *
			 */
			void ConstructDiffractionTree( const ITAGeo::CPropagationAnchor* pOrigin );

			void AddChildDiffractionEdge( std::shared_ptr<DiffractionEdge>& pChildDiffractionEdge, std::shared_ptr<DiffractionEdge>& pParentDiffractionEdge,
			                              const CITAMesh::EdgeHandle& hChildEdge, const std::string& sMeshName );

			void SetStartDiffractionEdges( );


		private:
			void ConstructDiffractionMatrix( );

			//! Recursively get illuminated diffraction edges which start and end points are illuminated by a first point(calculated beforehand) and a second point (here
			//! v3InOrigin)
			/**
			 * Recursively get illuminated diffraction edges which start and end points are illuminated by a first point(calculated beforehand) and a second point (here
			 * v3InOrigin). Function is performed for each child of pInParenEdge.
			 *
			 * @param[out] vpOutIllumEdges Output vector of illuminated diffraction edges to be recursively added in this function
			 * @param[in] v3InOrigin Location which illumination to the current diffraction edge is checked
			 * @param[in] pInParentEdge Shared pointer to diffraction which is checked for illumination and if it is illuminated, will be added to vpOutIllumEdges.
			 *
			 */
			void RecursiveGetIlluminableDiffractionEdges( std::vector<std::shared_ptr<DiffractionEdge>>& vpOutIllumEdges, const VistaVector3D& v3InOrigin,
			                                              std::shared_ptr<DiffractionEdge> pInParentEdge );

			//! Recursively add illuminated diffraction edges to diffraction tree
			/**
			 * Recursively add illuminated diffraction edges to diffraction tree
			 *
			 * @param[in] pParentDiffractionEdge Parent diffraction edge whose children are recursively added via the DiffractionMatrix
			 *
			 */
			void RecursiveAddIlluminatedEdges( std::shared_ptr<DiffractionEdge>& pParentDiffractionEdge );

			bool IsEdgeIlluminated( const CITAMesh& oEdgeMesh, const CITAMesh::EdgeHandle& hEdge, const VistaVector3D& v3Origin );

			bool CanEdgeIlluminateInDirection( const CITAMesh& oMesh, const CITAMesh::EdgeHandle hEdge, const VistaVector3D& v3Direction );

			bool IsDiffractionEdgeIlluminated( const DiffractionEdge& oStartEdge, const DiffractionEdge& oEndEdge );

			bool CanFaceBeIlluminated( const CITAMesh& oMesh, CITAMesh::FaceHandle hFace, const VistaVector3D& v3Origin );

			struct DiffractionEdge
			{
				// Name of corresponding mesh model
				std::string sMeshModelName;

				// Edge Handle
				CITAMesh::EdgeHandle hEdge;

				// Current diffraction order
				long long iDiffractionOrder = -1;

				// Diffraction angle and accumulated angle
				double dAngle;
				double dAccumulatedAngle;

				// Direction of corresponding first halfedge
				VistaVector3D v3Direction;

				// Position of start vertex
				VistaVector3D v3StartPoint;

				// Position of end vertex
				VistaVector3D v3EndPoint;

				VistaVector3D v3MainFaceNormal;
				VistaVector3D v3OppositeFaceNormal;

				int iMainWedgeFaceID, iOppositeWedgeFaceID;

				// Length of edge
				float fLength;

				//! Previous halfedge
				std::shared_ptr<DiffractionEdge> parentEdge = nullptr;

				//! Map of next edges (MeshModelName is key)
				DiffractionEdgesMap mChildren;
			};

			//! Maximum diffraction order
			size_t m_iMaxDiffractionOrder;

			//! Pointer to origin anchor
			std::shared_ptr<ITAGeo::CPropagationAnchor> m_pOriginAnchor;

			//! Pointer to destination anchor
			std::shared_ptr<ITAGeo::CPropagationAnchor> m_pDestinationAnchor;

			// Mesh model list
			ITAGeo::Halfedge::CMeshModelList m_vpMeshModelList;

			//! Map of illuminated edges
			DiffractionEdgesMap m_mvhIlluminatedEdges;

			// Relations map between two edge directions
			std::map<MeshListEdgeHandle, std::map<MeshListEdgeHandle, double>> m_mdEdgeDirMultiplicationMap;

			// Relations map between two start points for the calculation of the aperture points
			std::map<MeshListEdgeHandle, std::map<MeshListEdgeHandle, double>> m_mdApertureStartDifferenceMap;

			// RTree of meshes
			// shared_ptr<ITAGeo::Urban::RTree::CBuildings> m_pBuildingsTree;

			// Matrix of illumination of diffraction edges
			std::map<MeshListEdgeHandle, std::set<std::shared_ptr<DiffractionEdge>>> m_mDiffractionMatrix;
		};
	} // namespace BaseEngine
} // namespace ITAPropagationPathSim
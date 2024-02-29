#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_ENGINE_IMPL
#define INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_ENGINE_IMPL

#include <ITAPropagationPathSim/ConvexDiffraction/Engine.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

using namespace ITAPropagationPathSim;


typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

class CEngineImpl : public ConvexDiffraction::CEngine
{
public:
	CEngineImpl( const ITAGeo::Halfedge::CMeshModel* pModel, std::shared_ptr<ITAGeo::CPropagationAnchor> pSource, std::shared_ptr<ITAGeo::CPropagationAnchor> pTarget );
	bool CalculateDiffractionPaths( ITAGeo::CPropagationPathList& lPaths );

	//! Graph of edges, where each path forms a candidate for a propagation path
	/**
	 * A geo propagation path tree always starts with an edge of a face that is directly visible by source
	 * and ends at edge with face that is directly visible from target.
	 *
	 * @todo Check if graph data structure is really necessary. Currently lists of handles, where previous
	 * path is copied for each new child node.
	 */
	class CITAGeoPropagationPathTree
	{
	public:
		CITAMesh::FaceHandle hTrunkFace;
		int iTrunkFaceCombinedContourOrder;
		std::vector<std::vector<CITAMesh::HalfedgeHandle> > vvhCandidates;

		inline CITAGeoPropagationPathTree( ) : iTrunkFaceCombinedContourOrder( ITAGeo::DiffractionOrder::DIFFRACTION_ORDER_INF ) { };

		inline CITAGeoPropagationPathTree( CITAMesh::FaceHandle hContourFace_, const int iCombinedOrder_ = ITAGeo::DiffractionOrder::DIFFRACTION_ORDER_INF )
		    : hTrunkFace( hContourFace_ )
		    , iTrunkFaceCombinedContourOrder( iCombinedOrder_ ) { };
	};

	void GetCombinedDiffractionGradientVisualization( ITAGeo::Halfedge::CMeshModel* pModel ) const;
	void GetFromSourceDiffractionGradientVisualization( ITAGeo::Halfedge::CMeshModel* pModel ) const;
	void GetFromTargetDiffractionGradientVisualization( ITAGeo::Halfedge::CMeshModel* pModel ) const;

	//! Creates a copy of propagation path candidates for visualization purposes
	/**
	 * @note
	 */
	void GetPropagationPathCandidatesVisualization( ITAGeo::CPropagationPathList& lPropCandidates );

private:
	CEngineImpl( );
	virtual ~CEngineImpl( );

	const ITAGeo::Halfedge::CMeshModel* m_pGeoModel;             //!< Mesh model
	std::shared_ptr<ITAGeo::CPropagationAnchor> m_pSourceAnchor; //!< Abstract source for diffraction algorithm
	std::shared_ptr<ITAGeo::CPropagationAnchor> m_pTargetAnchor; //!< Abstract target for diffraction algorithm

	//! Prepares edge diffraction properties on given polygonal mesh
	/**
	 * The preparation includes determination of wedge opening angle, halfedge
	 * local coordinate system with axis-and-angle representation, direct
	 * line-of-sight visibility test for source and listener.
	 *
	 * @note Currently only works for convex geometries
	 */
	void PrepareDiffractionCrawlingParameters( );

	//! Checks if edges are coplanar, e.g. from triangulation, and marks all halfedges for acceleration
	void MarkCoplanarDiffractionEdges( );

	//! Marks all faces that are illuminated by the entities
	/**
	 * @note Currently only works for convex geometries!
	 *
	 * @return True, if illuminated faces are overlapping, false otherwise
	 *
	 */
	bool MarkIlluminatedFaces( );


	//! Recursively searches for the diffraction gradients
	/**
	 * @note Currently only works for convex geometries!
	 *
	 * @return True, if a connection between source and receiver could be found within given abortion criteria, false otherwise
	 *
	 */
	bool RecursiveDiffractionGradientSearch( const int iCurrentRecursionIterationOrder );

	//! Looks for actual propagation path tree candidates based on the diffraction countours beginning at illuminated faces by (abstract) source position
	/**
	 * Iterates over illuminated faces ny source and checks combined the diffraction order.
	 * In case the order is in compliance with the abortion criterium of maximum diffraction order, the path tree will be build up
	 * as a candidate (geometric validation still missing), exposing at least one valid path from source to target.
	 *
	 * Propagation paths can not start with a series of coplanar edges, so these will be eliminated.
	 *
	 * @param[out] voPropagationCandidateTrees Propagation path candidate tree list
	 *
	 */
	void DerivePropagationPathTreeFromIlluminationArea( std::vector<CITAGeoPropagationPathTree>& voPropagationCandidateTrees );

	//! Follows the gradient branches of a path candidate from diffraction countour to the target recursively
	/**
	 * @return True, if candidate valid, false if not
	 */
	void RecursiveFollowGradientBranchesToTarget( const std::vector<CITAMesh::HalfedgeHandle>& vhTrunkToThisBranchChain,
	                                              std::vector<std::vector<CITAMesh::HalfedgeHandle> >& vvhBranchesList ) const;

	//! Validates if diffraction propagation path is audible based on given abortion criteria for angular ranges
	bool ValidateAbortionAngleRanges( std::vector<CITAMesh::HalfedgeHandle>& oCandidatePath ) const;

	//! Reversely check the angle ranges for a diffraction edge list from a given source point
	bool ReverseAngleRangeTest( const std::vector<CITAMesh::HalfedgeHandle>& vhPath, const VistaVector3D& v3SourcePoint ) const;

	//! Checks incidence angle range for to
	/**
	 * @todo check if required
	 */
	double GetValidIncidenceAngleRad( CITAMesh::HalfedgeHandle hSourceEdge, CITAMesh::HalfedgeHandle hTargetEdge ) const;

	//! Constructs and validates a propagation path from a list of halfedges (candidate)
	/**
	 * @param[in] vhCandidate Halfedge list
	 * @param[out] oPath Path with propagation anchors including start and end point (usually source and receiver).
	 *
	 * @return True, if a valid path could be constructed, otherwise false
	 */
	bool ConstructPropagationPathFromCandidate( const std::vector<CITAMesh::HalfedgeHandle>& vhCandidate, ITAGeo::CPropagationPath& oPath ) const;

	//! Filter valid paths from candidates
	void FilterValidPropagationPaths( std::vector<CITAGeoPropagationPathTree>& voCandidateTrees, std::vector<ITAGeo::CPropagationPath>& oValidPropagationPaths ) const;
};

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_ENGINE_IMPL

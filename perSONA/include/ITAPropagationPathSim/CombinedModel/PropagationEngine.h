#ifndef INCLUDE_WATCHER_COMBINED_PROPAGATION_ENGINE
#define INCLUDE_WATCHER_COMBINED_PROPAGATION_ENGINE

#include <ITAPropagationPathSim/CombinedModel/PropagationShapes.h>
#include <ITAPropagationPathSim/CombinedModel/RTree.h>
#include <ITAPropagationPathSim/Definitions.h>

// ITA includes
#include <ITABase/ITAProgress.h>
#include <ITABase/ITAStatistics.h>
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/Utils.h>
#include <ITAStopWatch.h>

namespace ITAPropagationPathSim
{
	namespace CombinedModel
	{
		using namespace ITAGeo;

		//! Propagation path simulation engine combining reflections and diffractions
		/**
		 * Propagation simulation based on geometrical paths is performed from
		 * source to receiver (can also be inverted).
		 *
		 *
		 */
		class ITA_PROPAGATION_PATH_SIM_API CPathEngine
		{
		public:
			struct CSimulationConfig
			{
				bool bFilterNotNeighbouredEdges; //!< If true, only edge-to-edge paths are allowed that share at least 1 face
				bool bFilterIlluminatedRegionDiffraction;
				bool bFilterEdgeToEdgeIntersectedPaths;
				bool bFilterEmitterToEdgeIntersectedPaths;
				bool bFilterSensorToEdgeIntersectedPaths;
				bool bFilterIntersectedPaths;
				int iNumberIterationApexCalculation;
				float fIntersectionTestResolution;
				// bool bReciprocalPropagationSimulation;
				bool bExportRuntimeStatistics;

				inline CSimulationConfig( ) { SetDefaults( ); };

				inline void SetDefaults( )
				{
					bFilterNotNeighbouredEdges           = false;
					bFilterIlluminatedRegionDiffraction  = false;
					bFilterEdgeToEdgeIntersectedPaths    = false;
					bFilterEmitterToEdgeIntersectedPaths = false;
					bFilterSensorToEdgeIntersectedPaths  = false;
					bFilterIntersectedPaths              = false;
					iNumberIterationApexCalculation      = 5;
					fIntersectionTestResolution          = 0.001f;
					// bReciprocalPropagationSimulation = true; // more efficient for moving sources
					bExportRuntimeStatistics = true;
				};
			};

			struct CAbortionCriteria
			{
				int iMaxDiffractionOrder;
				int iMaxReflectionOrder;
				int iMaxCombinedOrder;
				float fDynamicRange;
				float fReflectionPenalty;
				float fDiffractionPenalty;
				float fAccumulatedAngleThreshold;

				inline CAbortionCriteria( ) { SetDefaults( ); };

				inline void SetDefaults( )
				{
					iMaxDiffractionOrder       = 2;
					iMaxReflectionOrder        = 2;
					iMaxCombinedOrder          = 4;
					fDynamicRange              = 124;
					fReflectionPenalty         = -10.0f * log10( 0.8f ); // for conservative sim, set to 0
					fDiffractionPenalty        = 2.5f;                   // for conservative sim, set to 0
					fAccumulatedAngleThreshold = -1.0f;                  // disabled
				};
			};

			CPathEngine( );

			void SetSimulationConfiguration( const CSimulationConfig& oConfig );
			void SetAbortionCriteria( const CAbortionCriteria& oAbort );

			void SetProgressCallbackHandler( ITABase::IProgressHandler* pHandler );

			void InitializePathEnvironment( std::shared_ptr<const Halfedge::CMeshModelList> pMeshModelList );

			//! Set the source and target entities for the path finder and perform pre-processing
			void SetEntities( std::shared_ptr<CPropagationAnchor> pOriginEntity, std::shared_ptr<CPropagationAnchor> pTargetEntity );

			//! Updates the emitter state (costly, if reciprocal mode is used)
			void UpdateOriginEntity( std::shared_ptr<CPropagationAnchor> pOriginEntity );

			// Updates the sensor state (costly, if normal (non-reciprocal) mode is used)
			void UpdateTargetEntity( std::shared_ptr<CPropagationAnchor> pTargetEntity );

			//! Constructs the propagation paths (requires entitites)
			void ConstructPropagationPaths( CPropagationPathList& oPaths );

			size_t GetNumberPropagationPathCandidates( );

			std::vector<ITABase::CStatistics> GetRuntimeStatistics( ) const;

		protected:
			void ApplyEmitter( std::shared_ptr<CEmitter> pEmitter );
			void ApplySensor( std::shared_ptr<CSensor> pSensor );

		private:
			CAbortionCriteria m_oAbort;
			CSimulationConfig m_oConfig;

			void PushStatus( std::string, float );
			ITABase::IProgressHandler* m_pProgressHandler;

			ITAStopWatch m_swVisibilityMap, m_swConstructShapes, m_swPropagationTreeConstruction, m_swImageConstruction, m_swPropgationPathsConstruction;

			std::vector<CPropagationShapeShared> m_vpPropagationShapes; //!< Vector of all propagation shapes
			// CShapesTree m_ShapesTree; TODO: Not working yet

			std::shared_ptr<const ITAGeo::Halfedge::CMeshModelList> m_pMeshModelList; //!< Copy of propagation model list
			CShapesMap m_mvpShapeVisibilityMap;                                       //!< Map of which shape can illuminate which ones
			std::vector<CPropagationShapeShared> m_vpPropagationTree;       //!< Vector of all propagation shapes (as well as its children) visible to the emitter
			std::vector<CPropagationShapeShared> m_vpPropagationCandidates; //!< Vector of all propagation shape visible to the emitter with each one pointing to up to
			                                                                //!< one child with the last one visible to the sensor

			std::shared_ptr<ITAGeo::CPropagationAnchor>
			    m_pOriginEntity; //!< Pointer to (geometrical) origin entity (can acoustically also be a sensor, if reciprocally used)
			std::shared_ptr<ITAGeo::CPropagationAnchor>
			    m_pTargetEntity; //!<  Pointer to (geometrical) target entity (can acoustically also be an emitter, if reciprocally used)

			float GetMaxPropagationRange( ) const;
			bool GetMaxPropagationRangeValid( ) const;

			void CreateVisibilityMap( );
			bool CanPointIlluminateFace( const VistaVector3D& v3Point, const std::string& sMeshModelName, CITAMesh::FaceHandle hFace );
			bool CanPointIlluminateEdge( const VistaVector3D& v3Point, CPropagationEdgeShared& pPropagationEdge, const bool& bTestIntersection = false );
			bool IsPathVisible( const VistaVector3D& v3StartPoint, const VistaVector3D& v3EndPoint );
			void CanEdgeIlluminateFace( bool& bCanEdgeIlluminateFaceOut, CPropagationFaceShared& pPropagationFace, CPropagationEdgeShared& pPropagationEdge );
			void CanFaceIlluminateEdge( bool& bCanFaceIlluminateEdgeOut, CPropagationFaceShared& pPropagationFace, CPropagationEdgeShared& pPropagationEdge );
			void CanFaceIlluminateFace( bool& bCanFaceIlluminateFaceOut, CPropagationFaceShared& pPropagationFaceStart, CPropagationFaceShared& pPropagationFaceEnd );
			void CanEdgeIlluminateEdge( bool& bCanEdgeIlluminateEdgeOut, CPropagationEdgeShared& pPropagationEdgeStart, CPropagationEdgeShared& pPropagationEdgeEnd,
			                            const bool& bTestIntersection = false );
			void ConstructPropagationShapes( );

			// Create the propagation tree
			void CreatePropagationTree( std::shared_ptr<CPropagationAnchor> pTrunk );
			void RecursiveAddChildrenToTree( const CPropagationShapeShared& pPropagationShapeChildIn, CPropagationShapeShared& vpShapeChildCopyOut, int iReflectionOrder,
			                                 int iDiffractionOrder, int iCombinedOrder, float fAccumulatedPenalty, float fFirstDistance, float fSecondDistance,
			                                 float fLevelDropAtFirstEdge );

			// Create the propagation list
			void CreatePropagationLists( );
			void RecursiveAddShapesToPropagationLists( std::shared_ptr<CPropagationShape>& pPropagationShapeIn );

			// Filter not visible, intersected, paths
			void FilterVisiblePaths( const std::vector<CPropagationShapeShared> vpAllPathsIn, std::vector<CPropagationShapeShared>& vpVisiblePathsOut );

			// Culling of unperceived paths
			void PerceptionalCulling( const std::vector<CPropagationShapeShared> vpAllPathsIn, std::vector<CPropagationShapeShared>& vpAudiblePathsOut );

			// Convert the propagation list
			void ConvertShapeListsToPropagationPaths( ITAGeo::CPropagationPathList& oPathsOut );
		};
	} // namespace CombinedModel
} // namespace ITAPropagationPathSim

#endif // INCLUDE_WATCHER_COMBINED_PROPAGATION_ENGINE

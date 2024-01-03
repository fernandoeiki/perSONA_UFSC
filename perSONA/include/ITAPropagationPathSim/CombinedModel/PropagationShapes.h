#ifndef INCLUDE_WATCHER_PROPAGATION_SHAPES
#define INCLUDE_WATCHER_PROPAGATION_SHAPES


#include <ITAPropagationPathSim/Definitions.h>

// ITA includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/Utils.h>

// Used Namespaces


namespace ITAPropagationPathSim
{
	namespace CombinedModel
	{
		// Typedefs
		class CPropagationShape;
		class CPropagationFace;
		class CPropagationEdge;
		typedef std::shared_ptr<CPropagationShape> CPropagationShapeShared;
		typedef std::shared_ptr<CPropagationFace> CPropagationFaceShared;
		typedef std::shared_ptr<CPropagationEdge> CPropagationEdgeShared;
		typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;
		typedef std::map<size_t, std::vector<CPropagationShapeShared>> CShapesMap;

		typedef std::string MeshModelHandle;
		typedef std::pair<MeshModelHandle, CITAMesh::FaceHandle> PropagationFaceHandle;

		// Old implementation[TODO: remove]
		// struct ImageReceiverMap : map<PropagationFaceHandle, shared_ptr<ImageReceiverMap>>
		/*	{
		        shared_ptr<VistaVector3D> v3ImageReceiver;
		        shared_ptr<bool> pHasIlluminableImageReceiver;
		    };*/

		enum Tristate : uint8_t
		{
			False     = 0,
			True      = 1,
			Undefined = 2
		};

		class ITA_PROPAGATION_PATH_SIM_API CPropagationShape
		{
		public:
			//---Public member variables-----------------------------------------------------------------------

			//!< Type of shape(e.g. edge or face)
			enum EShapeType
			{
				INVALID = -1, //!< Invalid shape
				POINT   = 0,  //!< Propagation point (acoustic source, receiver)
				EDGE,         //!< Propagation edge (for diffraction)
				FACE,         //!< Propagation face (for reflection)

				LAST_ELEMENT //!< Last element of EShapeType
			} iShapeType;    //! Type of Shape

			//!< Shows whether shape is illuminable by sensor or not
			std::shared_ptr<Tristate> pIsIlluminableByTargetEntity;

			//!< Point of interaction
			std::unique_ptr<VistaVector3D> v3InteractionPoint;

			//!< Shape handle
			OpenMesh::BaseHandle hShape;

			//!< Vertices of shape
			std::vector<std::shared_ptr<VistaVector3D>> vv3Vertices;

			//!< Parent shape(previous shape)
			std::weak_ptr<CPropagationShape> pParent;

			//!< Child(ren) shape(s)
			CPropagationShapeShared pChild;                  // Shape used in propagation paths
			std::vector<CPropagationShapeShared> vpChildren; // Shapes used in propagation trees

			std::shared_ptr<std::string> sMeshModelName;

			//!< Barycenter of shape (used for boundary sphere)
			std::shared_ptr<VistaVector3D> v3Barycenter;

			//!< Radius of boundary sphere (longest distance from barycenter to vertex)
			float fRadius;

			//!< Minimum distance to previous shape
			float fMinimumDistance = 0.0f;

			//!< Distance level drop
			float fDistanceLevelDrop = 0.0f;
			//---Public member functions--------------------------------------------------------------------

			//!< Copy shape
			void CopyFrom( const CPropagationShape& oPropagationShapeIn );

			void GetBoundingBoxAxesAligned( VistaVector3D& v3Min, VistaVector3D& v3Max ) const;

			//!< Set barycenter and radius of the boundary sphere of the shape
			bool SetBoundarySphere( );

			bool SetMinimumDistance( const CPropagationShape& oPropagationShape );

			//!< Set fMinimumDistance to point (e.g. emitter)
			bool SetMinimumDistance( const VistaVector3D& v3Point );

			//!< Calculate minimum distance to point (e.g. emitter) and return value
			float CalculateMinimumDistance( const VistaVector3D& v3Point );

			//!< Calculate the level drop due to the propagation of the sound
			float CalculateLevelDrop( float& fFirstDistance, float& fSecondDistance, float& fLevelDropAtFirstEdge );

			size_t GetIdentifier( ) const;

			int GetPolygonID( ) const;
		};

		class ITA_PROPAGATION_PATH_SIM_API CPropagationFace : public CPropagationShape
		{
		public:
			//---Public member variables--------------------------------------------------------------------

			CITAMesh::FaceHandle hFace; // Face handle corresponding to propagation face

			std::shared_ptr<VistaPlane> pPlane; // Plane built up by face

			std::shared_ptr<VistaVector3D> v3ImageSource;

			std::shared_ptr<VistaVector3D> v3ImageEdgeSourceStart;
			std::shared_ptr<VistaVector3D> v3ImageEdgeSourceEnd;

			std::shared_ptr<bool> pHasValidImageSource;

			//---Public member functions----------------------------------------------------------------------

			//!< Copy face
			void CopyFrom( const CPropagationFace& oPropagationFaceIn );

			// Set minimum distance to shape
			bool SetMinimumDistance( const CPropagationShape& oPropagationShape );

			// Set fMinimumDistance to point (e.g. emitter)
			bool SetMinimumDistance( const VistaVector3D& v3Point );

			// Calculate minimum distance to point (e.g. emitter) and return value
			float CalculateMinimumDistance( const VistaVector3D& v3Point );
		};

		class ITA_PROPAGATION_PATH_SIM_API CPropagationEdge : public CPropagationShape
		{
		public:
			//---Public member variables-------------------------------------------------------------------------
			CITAMesh::HalfedgeHandle hHalfedge;
			CITAMesh::EdgeHandle hEdge;
			CITAMesh::FaceHandle hMainFace;
			CITAMesh::FaceHandle hOppositeFace;

			std::shared_ptr<bool> pHasValidImageEdge;

			std::shared_ptr<VistaVector3D> v3StartVertex;        //!< Start vertex of corresponding halfedge
			std::shared_ptr<VistaVector3D> v3EndVertex;          //!<  End vertex of corresponding halfedge
			std::shared_ptr<VistaVector3D> v3MainFaceNormal;     //!<  Face normal of main face
			std::shared_ptr<VistaVector3D> v3OppositeFaceNormal; //!<  Face normal of opposing face

			std::shared_ptr<VistaVector3D> v3ImageEdgeReceiverStart; //!< Start vertex of corresponding mirrored halfedge
			std::shared_ptr<VistaVector3D> v3ImageEdgeReceiverEnd;   //!< End vertex of corresponding mirrored halfedge

			//!< Position of interaction point relative to the ray starting at v3FromVertex and showing in direction of (v3ToVertex - v3FromVertex)
			//!< If the relative position lies between 0.0(at v3FromVertex) and 1.0(at v3ToVertex), the interaction point is on the edge
			std::unique_ptr<float> pRelativeInteractionPoint;

			//---Public member functions-----------------------------------------------------------------------

			//! Returns true if wedge is like a room corner (inner wedge type)
			/**
			 * The angle of the SOLID part of the wedge is GREATER Pi in radiants or GREATER 180 degree.
			 * The opening angle is below Pi or 180 degree.
			 *
			 * ###|
			 * ###|   medium
			 * ###|______________
			 * ######## solid ###
			 */
			inline bool IsInnerWedge( ) const { return !IsOuterWedge( ); };

			//! Returns true if wedge is like a house corner (outer wedge type)
			/**
			 * The angle of the SOLID part of the wedge is SMALLER Pi in radiants or SMALLER 180 degree.
			 * The opening angle is greater Pi or 180 degree.
			 *
			 *               medium
			 *             _________________
			 *            |################
			 *   medium   |## solid #####
			 *            |############
			 *            |####
			 */
			bool IsOuterWedge( ) const;

			//!< Copy edge
			void CopyFrom( const CPropagationEdge& oPropagationEdgeIn );

			// Set minimum distance to shape
			bool SetMinimumDistance( const CPropagationShape& oPropagationShape );

			// Set fMinimumDistance to point (e.g. emitter)
			bool SetMinimumDistance( const VistaVector3D& v3Point );

			// Calculate minimum distance to point (e.g. emitter) and return value
			float CalculateMinimumDistance( const VistaVector3D& v3Point );

			//!< Calculate the level drop due to the propagation of the sound
			float CalculateLevelDrop( float& fFirstDistance, float& fSecondDistance, float& fLevelDropAtFirstEdge );
		};
	} // namespace CombinedModel
} // namespace ITAPropagationPathSim

#endif // INCLUDE_WATCHER_PROPAGATION_SHAPES

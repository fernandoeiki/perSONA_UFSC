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

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_MIRROR_IMAGE_ENGINE
#define INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_MIRROR_IMAGE_ENGINE

#include <ITAPropagationPathSim/Definitions.h>

// ITA includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/Utils.h>

// STL includes
#include <string>
#include <vector>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/IOManager.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )


// Typedefs
typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;


namespace ITAPropagationPathSim
{
	namespace MirrorImage
	{
		//! Simple image model
		/**
		 * Provides a simple image model that generates exponentially growing
		 * images depending on geometry input.
		 *
		 * Audibility test can be performed with or without
		 * backface culling (frontface culling can also be used in case normals are flipped).
		 *
		 * Emitters (sources) have an image order while the sensor (receiver / listener)
		 * is not mirrored. However, as the mirror image model is reciprocal, the
		 * actual use can be inverted by the user as well. For simplicity, the
		 * common nominclature will be used where sources are mirrored.
		 *
		 * The simple image engine is not fast (at all). It simply demonstrates how
		 * a fundamental mirror image method can be implemented. hence code structure
		 * and style should mainly serve the purpose of straighforward comprehension.
		 *
		 * You can use this enginge for moderately complex rooms / outdoor scenes.
		 *
		 */
		class ITA_PROPAGATION_PATH_SIM_API CEngine
		{
		public:
			//! Construct an image model engine for simple (brute-force) simulation
			/**
			 * Creates a copy if the model and pre-allocates all image sources.
			 * @note Not efficient for complex geometries! Use an engine that employs image pools and pre-filtering of possible images
			 *
			 * @param[in] oModel Mesh model (will be copied)
			 * @param[in] iEmitterImageOrder Defaults to 2 (first order images of sending entity / source)
			 *
			 */
			CEngine( const ITAGeo::Halfedge::CMeshModel& oModel, const int iEmitterImageOrder = ITAGeo::ORDER_2 );

			//! Destructor
			virtual ~CEngine( );

			//! Image order getter
			/**
			 * @return Order of images
			 */
			int GetImageOrder( ) const;

			//! Number of faces found in the model
			/**
			 * @return Number of faces
			 */
			unsigned long int GetNumberOfFaces( ) const;

			//! Absolute count of all images created
			/**
			 * @return Number of images
			 */
			unsigned long GetNumberOfImages( ) const;

			//! Constructs (determines) image positions and orientations / mirroring
			/**
			 * @param[in] pEmitter Entity anchor from which images are constructed (commonly the emitter)
			 */
			void ConstructImages( std::shared_ptr<const ITAGeo::CPropagationAnchor> pSource );

			//! Constructs (determines) reflection positions
			/**
			 * @param[in] pDestinationAnchor Entity anchor from which the pathlist is constructed
			 * @param[out] oPathList To be constructed path list
			 * @param[in] eCulling Frontface, Backface or none culling
			 * @param[in] iMaxOrder Maximum order to be considered
			 */
			void ConstructReflectionPaths( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPathList& oPathList,
			                               const ITAGeo::ECulling eCulling = ITAGeo::ECulling::NONE, const int iMaxOrder = -1 );

			//! Constructs (determines) reflection positions for outside reflections
			/**
			 * @param[in] pDestinationAnchor Entity anchor from which the pathlist is constructed
			 * @param[out] oPathList To be constructed path list
			 * @param[in] iMaxOrder Maximum order to be considered
			 */
			void ConstructReflectionPathsOutside( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPathList& oPathList,
			                                      const int iMaxOrder = -1 );

			//! Constructs (determines) reflection positions for inside reflections
			/**
			 * @param[in] pDestinationAnchor Entity anchor from which the pathlist is constructed
			 * @param[out] oPathList To be constructed path list
			 * @param[in] iMaxOrder Maximum order to be considered
			 */
			void ConstructReflectionPathsInside( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPathList& oPathList,
			                                     const int iMaxOrder = -1 );

			//! Constructs (determines) reflection positions for a specific order
			/**
			 * @param[in] pDestinationAnchor Entity anchor from which the pathlist is constructed
			 * @param[out] oPathList To be constructed path list
			 * @param[in] iOrder Order to be considered
			 * @param[in] eCulling Frontface, Backface or none culling
			 */
			void ConstructReflectionPathsForOrder( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPathList& oPathList,
			                                       const int iOrder, const ITAGeo::ECulling eCulling = ITAGeo::ECulling::NONE );

			//! Constructs (determines) reflection positions for outside reflections and a specific order
			/**
			 * @param[in] pDestinationAnchor Entity anchor from which the pathlist is constructed
			 * @param[out] oPathList To be constructed path list
			 * @param[in] iOrder Order to be considered
			 * @param[in] eCulling Frontface, Backface or none culling
			 */
			void ConstructReflectionPathsOutsideForOrder( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPathList& oPathList,
			                                              const int iOrder );

			//! Constructs (determines) reflection positions for inside reflections and a specific order
			/**
			 * @param[in] pDestinationAnchor Entity anchor from which the pathlist is constructed
			 * @param[out] oPathList To be constructed path list
			 * @param[in] iOrder Order to be considered
			 * @param[in] eCulling Frontface, Backface or none culling
			 */
			void ConstructReflectionPathsInsideForOrder( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPathList& oPathList,
			                                             const int iOrder );


			//! Audibility test for images up to given maximum order with or without culling
			/**
			 * @param[[in] pDestination Destination anchor (sensor, receiver, listener, etc.)
			 * @param[out] lImagePaths Audible paths after recursive audibility test (with specular reflection anchors)
			 * @param[in] iCulling Enables/disables culling
			 * @param[in] iMaxOrder Maximum image order requested
			 */
			void GetAudiblePaths( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestination, ITAGeo::CPropagationPathList& lImagePaths, const int iMaxOrder = -1,
			                      const int iCulling = ITAGeo::ECulling::NONE ) const;

			//! Audibility test for images for a specified order only and with or without culling
			/**
			 * @param[[in] pDestination Destination anchor (sensor, receiver, listener, etc.)
			 * @param[out] lImagePaths Audible paths after recursive audibility test (with specular reflection anchors)
			 * @param[in] iCulling Enables/disables culling
			 * @param[in] iMaxOrder Maximum image order requested
			 *
			 * @note Currently implemented by getting all paths and filtering the requested order. Very slow, only for visualization.
			 */
			void GetAudiblePathsForOrder( std::shared_ptr<ITAGeo::CPropagationAnchor> pDestination, ITAGeo::CPropagationPathList& lImagePaths, const int iMaxOrder,
			                              const int iCulling = ITAGeo::ECulling::NONE ) const;

			//! Returns connected paths with anchor points at all subsequent image positions
			void GetImageVisualizationPaths( ITAGeo::CPropagationPathList& lPaths, const int iOrder = -1 );

			//! Returns connected paths from emitter to all image points
			void GetImagesHedgehogVisualization( ITAGeo::CPropagationPathList& lPaths, std::shared_ptr<ITAGeo::CPropagationAnchor> pDestination, const int iOrder = -1 );

		protected:
			//! Protected default constructor, use Create() instead
			inline CEngine( ) { };

			class CImageNode;

			CImageNode* m_pImagesRoot = nullptr; //!< Emitter images tree root

			ITAGeo::Halfedge::CMeshModel m_oMeshModel; //!< Geometrical mesh model (halfedges)

			//! Calculates image
			void CalculateImage( CITAMesh* pMesh, std::shared_ptr<const ITAGeo::CMirrorImage> pOrigin, std::shared_ptr<ITAGeo::CMirrorImage> pImage,
			                     CITAMesh::FaceHandle hFace );

			//! Constructs images recursively until max order is reached (initial trunk image node must have a position)
			void ConstructImagesRecursive( CImageNode* pParent, const int iMaxOrder, const int iCurrentOrder = -1 );

			//! Constructs path list for reflections between image sources and a target down the image tree until given maximum order
			void ConstructReflectionPathList( CImageNode* pRoot, std::shared_ptr<ITAGeo::CPropagationAnchor> pDestination, ITAGeo::CPropagationPathList& oPathList,
			                                  const int iMaxOrder, const ITAGeo::ECulling eCulling, const int iOrder = -1 );

			//! Constructs path between current image node and a destination anchor
			void ConstructReflectionsPath( CImageNode* pNode, std::shared_ptr<const ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPath& oPath,
			                               const ITAGeo::ECulling eCulling = ITAGeo::ECulling::NONE );

			//! Runs audibility check recursively down the images tree until given maximum order
			void GetAudiblePathsRecursive( CImageNode* pSource, std::shared_ptr<ITAGeo::CPropagationAnchor> pDestination, ITAGeo::CPropagationPathList& lPaths,
			                               const int iCulling, const int iMaxOrder ) const;


			//! Recursively checks audibility by casting ray between source and target and validates polygon intersection order
			bool AudibilityTest( CImageNode* pSource, std::shared_ptr<ITAGeo::CPropagationAnchor> pDestination, ITAGeo::CPropagationPath& oPath,
			                     const int iCulling ) const;

			//! Combines images until root and assembles a visual path from image positions
			static ITAGeo::CPropagationPath GetImageVisualizationPath( CImageNode* );
		};

		//! Simple image node
		class CEngine::CImageNode
		{
		public:
			inline CImageNode( const int iOrder, const int iMaxOrder, const int iNumFaces, CImageNode* pParent_ = nullptr ) : pParent( pParent_ )
			{
				pImage         = std::make_shared<ITAGeo::CMirrorImage>( );
				pImage->iOrder = iOrder;

				// Construct node tree
				if( iOrder < iMaxOrder )
				{
					if( iOrder == ITAGeo::ORDER_0 )
					{
						for( int i = 0; i < iNumFaces; i++ )
							vpImageChildren.push_back( new CImageNode( iOrder + 1, iMaxOrder, iNumFaces, this ) );
					}
					else
					{
						// After first order we only create one image less because there is no image from the same face as parent
						for( int i = 0; i < iNumFaces - 1; i++ )
							vpImageChildren.push_back( new CImageNode( iOrder + 1, iMaxOrder, iNumFaces, this ) );
					}
				}
			};

			inline void ClearAllNodes( )
			{
				for( auto c: vpImageChildren )
				{
					c->ClearAllNodes( );
					delete c;
				}
			};

			inline int GetNumSiblings( ) const { return (int)vpImageChildren.size( ); };

			inline bool HasSiblings( ) const { return GetNumSiblings( ) > 0; };

			inline bool HasParent( ) const { return ( pParent != nullptr ); };

			inline void GetLeafNodes( std::vector<CImageNode*>& vpLeafNodes, const int iOrder )
			{
				if( iOrder < pImage->iOrder )
					return;

				for( auto node: vpImageChildren )
					if( node->HasSiblings( ) )
						node->GetLeafNodes( vpLeafNodes, iOrder );
					else
						vpLeafNodes.push_back( node );
			};

			CImageNode* pParent;                          //!< Pointer to parent node or nullptr
			std::vector<CImageNode*> vpImageChildren;     //!< List of siblings
			std::shared_ptr<ITAGeo::CMirrorImage> pImage; //!< Mirror image data
		};


	} // namespace MirrorImage
} // namespace ITAPropagationPathSim


#endif // INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_MIRROR_IMAGE_ENGINE

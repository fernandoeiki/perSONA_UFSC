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

// ITA includes
#include <ITAGeo/Urban/Model.h>
#include <ITAPropagationPathSim/MirrorImage/Engine.h>
#include <unordered_map>

namespace ITAPropagationPathSim
{
	namespace BaseEngine
	{
		namespace MirrorImage
		{
			//! Simple image model for urban models
			class ITA_PROPAGATION_PATH_SIM_API CSource : public ITAPropagationPathSim::MirrorImage::CEngine
			{
			public:
				//---Constructor and Destructor---------------------------------------------------------------------------------------


				//! Construct an image model engine for simple (brute-force) simulation
				/**
				 * Creates a copy if the model and pre-allocates all image sources.
				 * @note Not efficient for complex geometries! Use an engine that employs image pools and pre-filtering of possible images
				 *
				 * @param[in] vpMeshModelList Mesh model (will be copied)
				 * @param[in] iSourceImageOrder Defaults to 2 (first order images of sending entity / source)
				 *
				 */
				CSource( std::shared_ptr<const ITAGeo::Halfedge::CMeshModelList> vpMeshModelList, int iSourceImageOrder = ITAGeo::ORDER_2 );

				//! Destructor
				virtual ~CSource( );


				//---Construct functions----------------------------------------------------------------------------------------------

				//! Constructs (determines) image positions and orientations / mirroring
				/**
				 * @param[in] pEmitter Entity anchor from which images are constructed (commonly the emitter)
				 */
				void ConstructImages( std::shared_ptr<ITAGeo::CPropagationAnchor> pEmitter );

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

			private:
				//---Member classes---------------------------------------------------------------------------------------------------
				class CImageNode;

				//---Member functions-------------------------------------------------------------------------------------------------

				//! Constructs images recursively until max order is reached (initial trunk image node must have a position)
				void ConstructImagesRecursive( CImageNode* pParent, const int iMaxOrder, const int iCurrentOrder );

				//! Constructs path list for reflections between image sources and a target down the image tree until given maximum order
				void ConstructReflectionPathList( CImageNode* pRoot, std::shared_ptr<ITAGeo::CPropagationAnchor> pDestination, ITAGeo::CPropagationPathList& oPathList,
				                                  const int iMaxOrder, const ITAGeo::ECulling eCulling, const int iOrder = -1 );

				//! Constructs path between current image node and a destination anchor
				void ConstructReflectionsPath( CImageNode* pNode, std::shared_ptr<const ITAGeo::CPropagationAnchor> pDestinationAnchor, ITAGeo::CPropagationPath& oPath,
				                               const ITAGeo::ECulling eCulling = ITAGeo::ECulling::NONE );

				//! Get maximum order of images
				int GetImageOrder( ) const;

				//---Member variables-------------------------------------------------------------------------------------------------

				// Vector of mesh models
				std::shared_ptr<const ITAGeo::Halfedge::CMeshModelList> m_vpMeshModelList;

				//! Root of image sources as image source of order 0 (commonly the emitter)
				CImageNode* m_pImagesRoot;

				//! Root of image sources as propagation anchor (commonly the emitter)
				std::shared_ptr<ITAGeo::CPropagationAnchor> m_pStartAnchor;

				//! Max order of image sources
				int m_iMaxOrder;
			};

			//! Simple image node for urban models
			class CSource::CImageNode
			{
			public:
				//---Constructor------------------------------------------------------------------------------------------------------
				CImageNode( const int iOrder, const int iMaxOrder, const ITAGeo::Halfedge::CMeshModelList& vpMeshModelList, CImageNode* pParent_ = nullptr,
				            const int iBuildingIndex = -1 );

				//---Member functions-------------------------------------------------------------------------------------------------


				//---Member variables-------------------------------------------------------------------------------------------------

				std::string m_sMeshModelName = "";

				CImageNode* pParent;                                             //!< Pointer to parent node or nullptr
				std::map<std::string, std::vector<CImageNode*>> mpImageChildren; //!< List of siblings, mapped by its parent building and its own building
				std::shared_ptr<ITAGeo::CMirrorImage> pImage;                    //!< Mirror image data
			};

		} // namespace MirrorImage
	}     // namespace BaseEngine
} // namespace ITAPropagationPathSim
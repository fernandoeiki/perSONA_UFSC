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

#ifndef INCLUDE_WATCHER_ITA_GEO_SKETCHUP_MODEL
#define INCLUDE_WATCHER_ITA_GEO_SKETCHUP_MODEL

#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/ModelBase.h>

// Sketchup includes
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/initialize.h>
#include <SketchUpAPI/model/component_definition.h>
#include <SketchUpAPI/model/component_instance.h>
#include <SketchUpAPI/model/drawing_element.h>
#include <SketchUpAPI/model/edge.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/group.h>
#include <SketchUpAPI/model/layer.h>
#include <SketchUpAPI/model/material.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/rendering_options.h>
#include <SketchUpAPI/model/texture.h>
#include <SketchUpAPI/model/vertex.h>
#include <SketchUpAPI/transformation.h>
#include <SketchUpAPI/unicodestring.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/IOManager.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

// STL includes
#include <map>
#include <string>
#include <vector>

// class ITAGeo::Halfedge::CMeshModel;
class CITAMaterialManager;

namespace ITAGeo
{
	namespace SketchUp
	{
		//! SketchUp model class extending geo model
		/**
		 * This model based on geometrical data can be used
		 * for acoustic simulation. It uses halfedge meshes
		 * for fast acoustic algorithms for indoor and
		 * outdoor purposes. The representation is closely
		 * related to SketchUp. The importer/exporter methods
		 * use SketchUp file format, internal representation
		 * is OpenMesh half-edge mesh format.
		 *
		 */
		class ITA_GEO_API CModel : public CModelBase
		{
		public:
			CModel( );
			~CModel( );

			//! Loads SketchUp data from given file path
			/*
			 * \note Throws ITAException (i.e. if file not found)
			 * \return True, if SketchUp file can be translated into a scene
			 *
			 */
			bool Load( const std::string& sSKPFilePath );

			//! Saves SketchUp data to given file path
			/*
			 * \note Throws ITAException (i.e. if file could not be written)
			 * \return True, if file could be exported
			 */
			bool Store( const std::string& sSKPFilePath, bool bOverwrite = true ) const;


			void SetSketchUpVersion( int iVersion );
			int GetSketchUpVersion( ) const;

			//! Returns the number of groups
			size_t GetNumGroups( ) const;
			std::vector<std::string> GetGroupNames( ) const;

			size_t GetNumComponentInstances( ) const;
			size_t GetNumComponentDefinitions( ) const;
			std::vector<std::string> GetComponentDefinitionNames( ) const;

			size_t GetNumLayers( ) const;
			std::vector<std::string> GetLayers( ) const;

			const ITAGeo::Halfedge::CMeshModel* GetTopLevelMesh( ) const;

			//! Adds a layer (returns false, if name already exists)
			bool AddLayer( std::string& sLayerName );

			//! Adds an emitter to the SketchUp visualization
			void AddEmitterVisualization( const CPropagationAnchor& oEmitter, const std::string& sEmitterName = "Emitter", const std::string& sLayerName = "Emitter" );

			//! Adds a sensor to the SketchUp visualization
			void AddSensorVisualization( const CPropagationAnchor& oSensor, const std::string& sSensorName = "Sensor", const std::string& sLayerName = "Sensor" );


			//! Returns vector of const pointers to group meshes
			std::vector<const ITAGeo::Halfedge::CMeshModel*> GetGroupMeshModels( ) const;

			//! Returns vector of const pointers to component instances
			std::vector<Halfedge::CMeshModelShared> GetComponentMeshModels( ) const;

			//! Add group mesh
			void AddGroupMeshModel( const ITAGeo::Halfedge::CMeshModel* pMesh );

			//! Inverts all face normals
			void InvertAllFaceNormals( );

			//! Add propagation path visualization (that will be drawn if model is stored)
			/**
			 * @note Uses pointers to propagation anchors.
			 * @param[in] oPath Propagation anchor list
			 * @param[in] sLayerName SketchUp layer name (new or existing)
			 *
			 * @todo Add visualization as layers
			 */
			void AddPropagationPathVisualization( const ITAGeo::CPropagationPath& oPath, const std::string& sLayerName = "Layer0" );

			//! Add a visualization mesh
			void AddVisualizationMesh( const ITAGeo::Halfedge::CMeshModel* pVisMesh, const std::string& sLayerName = "Layer0" );

			//! Triangulate all meshes in model
			bool TriangulateMeshes( );

			//! Checks if all meshes in model are waterproof
			bool IsWaterproof( ) const;


		protected:
			int m_iSUVersion; //!< SketchUp version (slapi format, for writer)

			struct CHalfedgeMeshModelComponentDefinition
			{
				ITAGeo::Halfedge::CMeshModel* pMesh; //!< Pointer to halfedge mesh model
				std::string sName;                   //!< Component definition name (unique)
				int iNumReferences;                  //!< Flag that indicates if this component definition has instances in the geo model
			};

			struct CHalfedgeMeshModelComponentInstance
			{
				ITAGeo::Halfedge::CMeshModel* pComponentDefinition; //!< Pointer to halfedge mesh model of component definition
				VistaTransformMatrix oTransformMatrix;              //!< Transformation matrix
			};

			ITAGeo::Halfedge::CMeshModel* m_pTopLevelMeshModel;
			std::vector<ITAGeo::Halfedge::CMeshModel*> m_vpMeshGroups;                       //!< Halfedge mesh models from top-level groups (exploded)
			std::vector<CHalfedgeMeshModelComponentDefinition> m_voMeshComponentDefinitions; //!< Halfedge mesh models from top-level component definitions (exploded)
			std::vector<CHalfedgeMeshModelComponentInstance>
			    m_voMeshComponentInstances; //!< Halfedge mesh models from top-level component instances (pointer and transform matrix)

			std::map<std::string, std::map<std::string, ITAGeo::CPropagationAnchor> >
			    m_mGeoEmittersVisualization; //!< Propagation anchors for visualization of acoustic emitters
			std::map<std::string, std::map<std::string, ITAGeo::CPropagationAnchor> >
			    m_mGeoSensorsVisualization; //!< Propagation anchors for visualization of acoustic sensors
			std::map<std::string, ITAGeo::CPropagationPathList>
			    m_mGeoPropPathsVisualization; //!< Propagation paths for visualization of acoustic effects (never populated in Load() method)
			std::map<std::string, std::vector<const ITAGeo::Halfedge::CMeshModel*> > m_mAcousticVisualizationMeshes; //!< Mesh list with extra visualization data

			mutable OpenMesh::FPropHandleT<Material::CAcousticFaceProperty> m_tAcousticFaceProp;

			std::vector<std::string> m_vsLayers; //!< Layer names (also unused layers)

			// Add a cube to SUGroupRef
			void AddCubeToSUGroup( SUGroupRef& rGroup, const OpenMesh::Vec3f& v3CubePos, const float fLength ) const;
		};
	} // namespace SketchUp
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_SKETCHUP_MODEL
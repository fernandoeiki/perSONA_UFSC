/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 *				    ____  __________  _______
 *				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 *				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 * ----------------------------------------------------------------
 *
 */

#ifndef INCLUDE_WATCHER_ITA_GEO_HALFEDGE_MESH_MODEL
#define INCLUDE_WATCHER_ITA_GEO_HALFEDGE_MESH_MODEL

// ITAGeo includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Material/Manager.h>
#include <ITAGeo/ModelBase.h>

// STL includes
#include <map>
#include <string>
#include <vector>

// Forwards
struct ITA_GEO_API CITAMeshPtr;

// Used namespaces


namespace ITAGeo
{
	class IMaterial;

	namespace Halfedge
	{
		class CMeshModel;
		typedef std::shared_ptr<CMeshModel> CMeshModelShared;


		//! Halfedge mesh model using OpenMesh
		/**
		 * The halfedge mesh model representation requires, that
		 * every edge is connected to one or maximum two faces, only. This
		 * structure, besides some problems, offers the use of
		 * a few easy geometric algorithm implementations. Especially
		 * waterproof models with a single enclosed volume (like
		 * indoor rooms and buildings with facades only) can
		 * be represented as valid halfedge meshes.
		 */

		class ITA_GEO_API CMeshModel : public CModelBase
		{
		public:
			CMeshModel( );
			virtual ~CMeshModel( );

			//! Returns input file formats that can be loaded (forwards OpenMesh qt convenience function)
			/*
			 * Format of return string is <c>;;</c> with further information on formats
			 *
			 * @return Filter string of supported import file formats
			 *
			 * @see Load()
			 *
			 */
			static std::string GetSupportedInputFormats( );

			//! Returns output file formats that can be stored (forwards OpenMesh qt convenience function)
			/*
			 * Format of return string is <c>;;</c> with further information on formats
			 *
			 * @return List of supported export file formats (file extension list)
			 *
			 * @see Store()
			 *
			 */
			static std::string GetSupportedOutputFormats( );

			//! Checks if output format is supported
			/**
			 * @sa GetSupportedOutputFormats()
			 * @param[in] sFormatID Format identifier, i.e. "obj" or "skp"
			 * @return True, if format recognized
			 */
			static bool GetSupportedOutputFormat( const std::string& sFormatID );

			//! Checks if input format is supported
			/**
			 * @sa GetSupportedInputFormats()
			 * @param[in] sFormatID Format identifier, i.e. "obj" or "skp"
			 * @return True, if format recognized
			 */
			static bool GetSupportedInputFormat( const std::string& sFormatID );

			//! Loads a model from given file path
			/*
			 * Uses OpenMesh I/O manager to load geometries.
			 *
			 * @note Throws CITAException (i.e. if file not found)
			 *
			 * @see GetSupportedInputFormats()
			 *
			 * @sFilePath[in] sModelFilePath File path
			 * @return True, if successfull
			 *
			 * @return True, if content could be transformed into a valid halfedge mesh model.
			 *
			 */
			bool Load( const std::string& sModelFilePath );

			//! Saves a SketchUp model to given file path
			/*
			 * Uses OpenMesh I/O manager to store geometries to hard drive.
			 *
			 * @param[in] sModelFilePath Model file path
			 * @param[in] bOverwrite Flag to overwrite existing file
			 * @return True, if successfull
			 *
			 * @note Throws ITAException (i.e. if file could not be written)
			 *
			 * @see GetSupportedOutputFormats()
			 *
			 */
			bool Store( const std::string& sModelFilePath, bool bOverwrite = true ) const;

			//! Copy mesh model data
			void CopyFrom( const CMeshModel& );

			//! Get a transformed mesh model
			CMeshModelShared GetTransformedMesh( const VistaTransformMatrix& oTransformMatrix ) const;

			//! Checks weather the mesh is a valid waterproof model (no holes)
			bool IsWaterproofMesh( ) const;

			//! Checks if mesh is a valid triangle representation (only 3-edge faces)
			bool IsValidTriangleMesh( ) const;

			//! Triangulates mesh, if possible
			bool TriangulateMesh( );

			//! Add acoustic material to a face of mesh
			bool SetFaceAcousticMaterial( int iFaceID, std::shared_ptr<Material::IMaterial> pMaterial );

			//! Invert normal direction vector of all faces
			/**
			 * @todo This does not work for SketchUp meshes.
			 */
			bool InvertFaceNormals( );

			//! Returns const pointer to top level mesh
			// const ITAGeo::Halfedge::CMeshModel* GetTopLevelMeshModel() const;

			//! Get pointer to underlying mesh (OpenMESH)
			CITAMeshPtr* GetMesh( );

			//! Get pointer to underlying mesh (OpenMESH)
			const CITAMeshPtr* GetMesh( ) const;

			//! Returns bounding box min and max point
			void GetBoundingBoxAxisAligned( VistaVector3D& v3Min, VistaVector3D& v3Max ) const;

			//! Returns bounding sphere centroid and radius
			/**
			 * @param[out] v3Centroid Sphere center
			 * @param[out] fRadius Sphere radius in meter
			 */
			void GetBoundingSphere( VistaVector3D& v3Centroid, float& fRadius ) const;

			VistaVector3D GetBarycenter( ) const;

			//! Returns true, if position is within axis-aligned bounding box
			/**
			 * @param[in] v3Pos Position to be tested
			 *
			 */
			bool GetInsideBoundingBoxAxisAligned( const VistaVector3D& v3Pos ) const;

			//! Returns true, if position is within axis-aligned bounding box
			/**
			 * @param[in] v3Pos Position to be tested
			 * @note This function is slow because it has to create the bounding sphere. Consider own implementation
			 *
			 */
			bool GetInsideBoundingSphere( const VistaVector3D& v3Pos ) const;

			//! Checks if a point is inside the mesh model usign Jordan PIP method on random direction vector
			/**
			 * Throws @CITAException if not waterproof, because it uses Jordan test.
			 */
			bool GetInsideMeshJordanMethodRandomRay( const VistaVector3D& v3Pos ) const;

			inline bool GetOutsideMeshJordanMethodRandomRay( const VistaVector3D& v3Pos ) const { return !GetInsideMeshJordanMethodRandomRay( v3Pos ); };

			//! Checks if a point is inside the mesh model usign Jordan PIP method on the three axis-aligned vectors with majority decision
			/**
			 * @note Also works for non-waterproof models but without guarantee that result is as expected
			 */
			bool GetInsideMeshJordanMethodAxisAligned( const VistaVector3D& v3Pos ) const;

			void FilterVisiblePaths( CPropagationPathList& oPathListIn, CPropagationPathList& oPathListOut ) const;

			bool IsPathVisible( const CPropagationPath& oPath ) const;

			size_t GetNumFaces( ) const;

		protected:
			CITAMeshPtr* m_prModelMeshData; // CITAMesh pointer
		};


		class ITA_GEO_API CMeshModelList : public std::vector<std::shared_ptr<CMeshModel> >
		{
		public:
			//! Get the mesh model
			inline Halfedge::CMeshModelShared GetMeshModel( int index ) const { return this->at( index ); };

			//! Get the mesh model
			inline Halfedge::CMeshModelShared GetMeshModel( std::string sName ) const { return GetMeshModel( m_mapMeshNameToIndex.at( sName ) ); };

			//! Load mesh list data from another mesh list
			void CopyFrom( const CMeshModelList& vpMeshModelList );

			//! Get the number of meshes
			inline int GetNumMeshes( ) const { return (int)this->size( ); };

			//! Loads mesh list data from given file path
			/*
			 * Loads SketchUp file with meshes as groups
			 *
			 * @param[in] sMeshModelFilePath File path to mesh model, e.g. skp or gml file
			 * @param[in] bLoadTopLevelMesh Load the top level mesh
			 *
			 * @note Throws ITAException (i.e. if file not found)
			 * @return True, if model file can be translated into a scene
			 *
			 */
			bool Load( const std::string& sMeshModelFilePath, bool bLoadTopLevelMesh = true );

			//! Saves mesh model data to given file path
			/*
			 * @param[in] sMeshModelFilePath File path where to store urban model
			 * @param[in] bOverwrite Permit overwriting of eventually existing file
			 *
			 * @note Throws ITAException (i.e. if file could not be written)
			 * @return True, if file could be exported
			 */
			bool Store( const std::string& sMeshModelFilePath, bool bOverwrite = true ) const;

			//! Filters the visible paths
			/*
			 * @param[in] oPathListIn input path list that contains paths to be filtered
			 * @param[out] oPathListOut output path list that contains the filtered paths
			 */
			void FilterVisiblePaths( CPropagationPathList& oPathListIn, CPropagationPathList& oPathListOut ) const;

			//! Sets the material manager for this model
			/**
			 * On Loading a model, the associated material manager will be populated with the materials from
			 * the input file.
			 *
			 * @param[in] pMaterialManager Associated material manager (with write access)
			 */
			inline void SetMaterialManager( std::shared_ptr<ITAGeo::Material::IManager> pMaterialManager )
			{
				// Set material of each element
				for( auto& pMeshModel: *this )
					pMeshModel->SetMaterialManager( pMaterialManager );

				// Also set material manager of list
				m_pMaterialManager = pMaterialManager;
			};

		private:
			// Private member variables
			size_t m_iTotalNumFaces = 0;                                    //!< Number of faces of all meshes
			std::shared_ptr<ITAGeo::Material::IManager> m_pMaterialManager; //!< Associated material manager (where to add materials during load)
			std::map<std::string, int> m_mapMeshNameToIndex; //!< Map to associate mesh names with indices of meshes (to get the corresponding map by its name)

			// Private member functions
			bool IsPathVisible( const CPropagationPath& oPath ) const;
		};
	} // namespace Halfedge
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_HALFEDGE_MESH_MODEL

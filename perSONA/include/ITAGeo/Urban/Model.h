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

#ifndef INCLUDE_WATCHER_ITA_GEO_URBAN_MODEL
#define INCLUDE_WATCHER_ITA_GEO_URBAN_MODEL

// ITAGeo
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/ModelBase.h>
#include <ITAGeo/Utils.h>


// STL includes
#include <string>
#include <vector>


namespace ITAGeo
{
	namespace Urban
	{
		// Each building is a halfedge mesh model
		typedef Halfedge::CMeshModel CBuilding;
		typedef std::shared_ptr<CBuilding> CBuildingShared;

		//! Urban model class
		/**
		 * @todo
		 *
		 */
		class ITA_GEO_API CModel : public Halfedge::CMeshModelList
		{
		public:
			CModel( );
			virtual ~CModel( );

			//! Loads urban data from given file path
			/*
			 * Loads SketchUp file with buildings as groups and a ground surface
			 *
			 * @param[in] sUrbanModelFilePath File path to urban model, e.g. skp or gml file
			 *
			 * @note Throws ITAException (i.e. if file not found)
			 * @return True, if model file can be translated into a scene
			 *
			 */
			bool Load( const std::string& sUrbanModelFilePath );

			//! Saves urban data to given file path
			/*
			 * @param[in] sUrbanModelFilePath File path where to store urban model
			 *
			 * @note Throws ITAException (i.e. if file could not be written)
			 * @return True, if file could be exported
			 */
			bool Store( const std::string& sUrbanModelFilePath, bool bOverwrite = true ) const;

			//! Getter for all building meshes
			/**
			 * @return Vector of const pointers to halfedge meshes
			 */
			std::vector<const Halfedge::CMeshModel*> GetBuildings( ) const;

			//! Ground surface mesh
			//! Getter for all building meshes
			/**
			 * @return const pointer to halfedge mesh of surface
			 */
			const ITAGeo::Halfedge::CMeshModel* GetGroundSurface( ) const;

			//! Returns the number of building meshes
			size_t GetNumBuildings( ) const;

			//! Returns the names of the building meshes
			std::vector<std::string> GetBuildingNames( ) const;

			//! Adds a building to the urban model
			/*
			 * @param[in] pMesh pointer to mesh that contains building to be added
			 */
			void AddBuilding( const ITAGeo::Halfedge::CMeshModel* pMesh );

			//! Set Ground surface
			void SetGroundSurface( const ITAGeo::Halfedge::CMeshModel* pMesh );


		private:
			// Private member variables

			ITAGeo::Halfedge::CMeshModelShared m_pGroundSurface; //!< Ground surface mesh
			Halfedge::CMeshModelList m_vpBuildings;              //!< Vector of building meshes
		};

	} // namespace Urban
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_URBAN_MODEL

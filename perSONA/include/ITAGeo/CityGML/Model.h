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

#ifndef INCLUDE_WATCHER_ITA_GEO_CITYGML_MODEL
#define INCLUDE_WATCHER_ITA_GEO_CITYGML_MODEL

#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/ModelBase.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// STL includes
#include <string>
#include <vector>


namespace ITAGeo
{
	//! Helper struct forward declaration
	struct CCityGMLPtr;

	//! CityGML input and output class
	/**
	 * Interface that describes file I/O for CityGML files.
	 *
	 */
	class ITA_GEO_API CCityGMLModel : public CModelBase
	{
	public:
		struct CCityBuilding
		{
			int iNum;
			std::string sID;
			std::string sType;
			VistaVector3D v3CenterPos;
			float fBoundingSphereRadius;

			bool CenterInsideEllipse( const float coordinates[4], const float SemiMajorAxis, const float SemiMinorAxis ) const;

			bool BoundingSphereInsideEllipse( const VistaVector3D& v3centerpos, const float fBSradius, const float SemiMajorAxis, const float SemiMinorAxis ) const;
		};

		CCityGMLModel( );
		virtual ~CCityGMLModel( );

		//! Loads CityGML data from given file path
		/*
		 * \note Throws ITAException (i.e. if file not found)
		 * \return True, if CityGML file can be translated into a scene
		 *
		 */
		bool Load( const std::string& sGMLFilePath );

		//! Saves CityGML data to given file path
		/*
		 * \note Throws ITAException (i.e. if file could not be written)
		 * \return True, if file could be exported
		 */
		bool Store( const std::string& sGMLFilePath, bool bOverwrite = true ) const;

		void GetBuildingMesh( const CCityBuilding* pBuilding, ITAGeo::Halfedge::CMeshModel* pBuildingMesh,
		                      const VistaVector3D v3Shift = VistaVector3D( 0.0f, 0.0f, 0.0f ), const bool bCreateConnectedMesh = true );
		std::vector<const ITAGeo::CCityGMLModel::CCityBuilding*> GetBuildings( ) const;

		void DistanceCulling( const double dDetourDistance, const ITAGeo::CPropagationAnchor& v3Source, const ITAGeo::CPropagationAnchor& v3Target,
		                      std::vector<const ITAGeo::CCityGMLModel::CCityBuilding*>& vpResidualBuildings );

		void CalculateObjectCentroids( );

		std::vector<double> GetCityCenter( ) const;

	protected:
		CCityGMLPtr* m_pCityModel; //!< Encapsuled pointer to the city GML instance

		std::vector<ITAGeo::Halfedge::CMeshModel*> m_pBuildings;
		std::vector<CCityBuilding> m_voBuildings;
	};
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_CITYGML_MODEL

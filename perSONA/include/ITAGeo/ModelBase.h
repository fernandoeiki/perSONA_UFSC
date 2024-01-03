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

#ifndef INCLUDE_WATCHER_ITA_GEO_MODEL
#define INCLUDE_WATCHER_ITA_GEO_MODEL

// ITAGeo includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Material/Material.h>

// Vista includes
#include <VistaBase/VistaTransformMatrix.h>

// STL includes
#include <iostream>
#include <string>
#include <vector>

namespace ITAGeo
{
	class Material::IManager;

	//! Geometric model for acoustics
	/**
	 * This model based on geometrical data can be used
	 * for acoustic simulation. It uses halfedge meshes
	 * for fast acoustic algorithms for indoor and
	 * outdoor purposes. The importer/exporter methods
	 * use SketchUp file format, internal representation
	 * is OpenMesh half-edge mesh format.
	 *
	 */
	class ITA_GEO_API CModelBase
	{
	public:
		inline CModelBase( ) : m_pMaterialManager( nullptr ) { };
		inline virtual ~CModelBase( ) { };

		void SetName( const std::string& sName );
		std::string GetName( ) const;

		//! Loads a model from given file path
		/*
		 * \return True, if model file can be translated into an ITA model
		 *
		 */
		virtual bool Load( const std::string& sModelFilePath ) = 0;

		//! Saves a ITA geo model to given file path
		/*
		 * \note Throws ITAException (i.e. if file could not be written)
		 *
		 */
		virtual bool Store( const std::string& sModelFilePath, bool bOverwrite = true ) const = 0;


		friend std::ostream& operator<<( std::ostream&, const ITAGeo::CModelBase& );

		//! Sets the material manager for this model
		/**
		 * On Loading a model, the associated material manager will be populated with the materials from
		 * the input file.
		 *
		 * @param[in] pMaterialManager Associated material manager (with write access)
		 */
		void SetMaterialManager( std::shared_ptr<ITAGeo::Material::IManager> pMaterialManager );

	protected:
		std::string m_sModelName;                                       //!< Model name
		std::shared_ptr<ITAGeo::Material::IManager> m_pMaterialManager; //!< Associated material manager (where to add materials during load)

		/* @todo check if removal ok
		//friend class ITAGeo::SketchUp::CModel;
		//friend class ITAGeo::CCityGMLModel;

		friend class CITADiffractionEngine;

		friend void DistanceCulling( const ITAGeo::CModelBase* pInputModel, const float fSoundPressureLevelDynamicRange, ITAGeo::CModelBase* pOutputModel );
		*/
	};

} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_MODEL

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

#ifndef IW_ITA_GEO_RESOURCE_MANAGER
#define IW_ITA_GEO_RESOURCE_MANAGER

// ITAGeo includes
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Directivity/Manager.h>
#include <ITAGeo/Material/Manager.h>

// STL includes
#include <string>


namespace ITAGeo
{
	//! Resource manager
	class ITA_GEO_API CResourceManager
	{
	public:
		CResourceManager( );
		CResourceManager( std::shared_ptr<Material::IManager> );
		CResourceManager( std::shared_ptr<Directivity::IManager> );
		CResourceManager( std::shared_ptr<Material::IManager> pMM, std::shared_ptr<Directivity::IManager> pDM );
		virtual ~CResourceManager( );

		std::shared_ptr<Material::IManager> GetDefaultMaterialManager( ) const;
		std::shared_ptr<Directivity::IManager> GetDefaultDirectivityManager( ) const;

		//! Checks if material can be found
		virtual bool HasMaterial( const std::string& sMaterialIdentifier ) const;

		//! Retrieve acoustic material, if available
		/**
		 * @param[in] sMaterialIdentifier Text-based material identifier (usually the name of the material)
		 * @return Pointer to material or nullptr, if not available
		 */
		virtual std::shared_ptr<Material::IMaterial> GetMaterial( const std::string& sMaterialIdentifier ) const;

		//! Returns the identifier of a material pointer from the resource mapping
		std::string GetMaterialID( std::shared_ptr<Material::IMaterial> pMaterial ) const;


		//! Checks if directivity can be found
		virtual bool HasDirectivity( const std::string& sDirectivityIdentifier ) const;

		//! Retrieve directivity, if available
		/**
		 * @param[in] sID Text-based directivity identifier (usually the name of the directivity file)
		 * @return Pointer to directivity or nullptr, if not available
		 *
		 * @note Will first query default manager and then in order of manager list
		 */
		virtual std::shared_ptr<Directivity::IDirectivity> GetDirectivity( const std::string& sID ) const;

		//! Returns the identifier of a material pointer from the resource mapping
		std::string GetDirectivityID( std::shared_ptr<Directivity::IDirectivity> pDirectivity ) const;

		//! Add a material copy, if not already existant
		/**
		 * @return True, if possible, false if already existing or manager is read-only
		 */
		virtual bool AddMaterialToDefaultManager( const std::string& sIdentifier, std::shared_ptr<Material::IMaterial> pMat );

		//! Add a material copy, if not already existant
		/**
		 * @return True, if possible, false if already existing or manager is read-only
		 */
		virtual bool AddDirectivityToDefaultManager( const std::string& sIdentifier, std::shared_ptr<Directivity::IDirectivity> pDirectivity );

	private:
		std::shared_ptr<Material::IManager> m_pInMemoryMaterialManager;
		std::shared_ptr<Directivity::IManager> m_pInMemoryDirectivityManager;

		std::vector<std::shared_ptr<Material::IManager> > m_vpMaterialManagers;
		std::vector<std::shared_ptr<Directivity::IManager> > m_vpDirectivityManagers;
	};

} // namespace ITAGeo

#endif // IW_ITA_GEO_RESOURCE_MANAGER

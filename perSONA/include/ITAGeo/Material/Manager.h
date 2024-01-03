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

#ifndef IW_ITA_GEO_MATERIAL_MANAGER
#define IW_ITA_GEO_MATERIAL_MANAGER

// ITAGeo includes
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Material/Material.h>

// STL includes
#include <map>
#include <string>
#include <vector>


namespace ITAGeo
{
	namespace Material
	{
		//! Acoustic material basic manager
		class ITA_GEO_API IManager
		{
		public:
			IManager( );
			virtual ~IManager( );

			//! Retrieve acoustic material, if available
			/**
			 * @param[in] sMaterialIdentifier Text-based material identifier (usually the name of the material)
			 * @return Pointer to material or nullptr, if not available
			 */
			virtual std::shared_ptr<IMaterial> GetMaterial( const std::string& sMaterialIdentifier ) const = 0;

			//! Checks if material can be found
			virtual bool HasMaterial( const std::string& sMaterialIdentifier ) const = 0;

			//! Add a material copy, if not already existant
			/**
			 * @return True, if possible, false if already existing or manager is read-only
			 */
			virtual bool AddMaterial( const std::string& sIdentifier, std::shared_ptr<IMaterial> pMat ) = 0;

			virtual bool GetReadOnly( ) const = 0;
		};

		class ITA_GEO_API CInMemoryManager : public IManager
		{
		public:
			CInMemoryManager( );
			~CInMemoryManager( );
			std::shared_ptr<IMaterial> GetMaterial( const std::string& sMaterialIdentifier ) const;
			virtual bool HasMaterial( const std::string& sMaterialIdentifier ) const;
			bool AddMaterial( const std::string& sIdentifier, std::shared_ptr<IMaterial> pMat );
			bool GetReadOnly( ) const;

		private:
			std::map<std::string, std::shared_ptr<IMaterial> > m_mMaterials;
		};

		//! Acoustic material manager that retrieves data from a folder (checks file endings)
		class ITA_GEO_API CDirectory : public IManager
		{
		public:
			CDirectory( );
			CDirectory( const std::string& sFolderPath, const bool bRecursive = true );
			~CDirectory( );

			std::vector<std::string> GetPaths( ) const;
			void AddMaterialsFromFolder( const std::string& sFolderPath, const bool bRecursive = false );
			bool HasMaterial( const std::string& sMaterialIdentifier ) const;
			std::shared_ptr<IMaterial> GetMaterial( const std::string& sMaterialIdentifier ) const;
			int GetNumMaterials( ) const;
			std::vector<std::string> GetMaterialIdentifier( ) const;
			bool AddMaterial( const std::string&, std::shared_ptr<IMaterial> );
			bool GetReadOnly( ) const;


		private:
			std::map<std::string, std::shared_ptr<IMaterial> > m_mMaterials;
			std::vector<std::string> m_vsPaths;
		};

	} // namespace Material
} // namespace ITAGeo

#endif // IW_ITA_GEO_MATERIAL_MANAGER

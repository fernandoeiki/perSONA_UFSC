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

#ifndef IW_ITA_GEO_DIRECTIVITY_MANAGER
#define IW_ITA_GEO_DIRECTIVITY_MANAGER

// ITAGeo includes
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Directivity/Base.h>

// STL includes
#include <map>
#include <memory>
#include <string>
#include <vector>


namespace ITAGeo
{
	namespace Directivity
	{
		//! Acoustic directivity basic manager
		class ITA_GEO_API IManager
		{
		public:
			IManager( );
			virtual ~IManager( );

			//! Retrieve acoustic directivity, if available
			/**
			 * @param[in] sDirectivityID Text-based directivity identifier (usually the name of the dataset)
			 * @return Pointer to material or nullptr, if not available
			 */
			virtual std::shared_ptr<IDirectivity> GetDirectivity( const std::string& sDirectivityID ) const = 0;

			//! Retrieve ID of directivity, if available
			/**
			 * @param[in] pDirectivity Text-based directivity identifier (usually the name of the directivity)
			 * @return DDirectivity identifier or empty
			 */
			virtual std::string GetDirectivityID( std::shared_ptr<IDirectivity> pDirectivity ) const = 0;

			//! Checks if material can be found
			virtual bool HasDirectivity( const std::string& sDirectivityID ) const = 0;

			//! Add a material copy, if not already existant
			/**
			 * @return True, if possible, false if already existing or manager is read-only
			 */
			virtual bool AddDirectivity( const std::string& sIdentifier, std::shared_ptr<IDirectivity> pDirectivity ) = 0;

			virtual bool GetReadOnly( ) const = 0;
		};


		class ITA_GEO_API CInMemoryManager : public IManager
		{
		public:
			CInMemoryManager( );
			~CInMemoryManager( );
			std::shared_ptr<IDirectivity> GetDirectivity( const std::string& sID ) const;
			std::string GetDirectivityID( std::shared_ptr<IDirectivity> pDirectivity ) const;
			virtual bool HasDirectivity( const std::string& sID ) const;
			bool AddDirectivity( const std::string& sID, std::shared_ptr<IDirectivity> pDir );
			bool GetReadOnly( ) const;

		private:
			std::map<std::string, std::shared_ptr<IDirectivity> > m_mDirectivities;
		};

		//! Acoustic material manager that retrieves data from a folder (checks file endings)
		class ITA_GEO_API CDirectivityDirectory : public IManager
		{
		public:
			CDirectivityDirectory( );
			CDirectivityDirectory( const std::string& sFolderPath, const bool bRecursive = true );
			~CDirectivityDirectory( );

			std::vector<std::string> GetPaths( ) const;
			void AddDirectivitiesFromFolder( const std::string& sFolderPath, const bool bRecursive = false );
			std::shared_ptr<IDirectivity> GetDirectivity( const std::string& sDirectivityIdentifier ) const;
			std::string GetDirectivityID( std::shared_ptr<IDirectivity> pDirectivity ) const;
			int GetNumDirectivities( ) const;
			std::vector<std::string> GetDirectivityIdentifier( ) const;
			bool AddDirectivity( const std::string&, std::shared_ptr<IDirectivity> );
			bool GetReadOnly( ) const;

		private:
			std::map<std::string, std::shared_ptr<IDirectivity> > m_mDirectivities;
			std::vector<std::string> m_vsPaths;
		};

	} // namespace Directivity
} // namespace ITAGeo

#endif // IW_ITA_GEO_DIRECTIVITY_MANAGER

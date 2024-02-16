/*
 * ----------------------------------------------------------------
 *
 *		ITA core libs
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

#ifndef IW_ITA_GEO_UTILS_JSON_PROPAGATIONPATH
#define IW_ITA_GEO_UTILS_JSON_PROPAGATIONPATH

#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/ResourceManager.h>
#include <memory>
#include <string>

namespace ITAGeo
{
	namespace Utils
	{
		namespace JSON
		{
			//---PROPAGATION ANCHORS---

			ITA_GEO_API std::string Encode( const CPropagationAnchor& anchor );
			ITA_GEO_API void Decode( CPropagationAnchor& anchor, const std::string& sContent );

			ITA_GEO_API std::string Encode( const CEmitter& anchor, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CEmitter& anchor, const std::string& sContent, std::shared_ptr<CResourceManager> pResourceManager = nullptr );

			ITA_GEO_API std::string Encode( const CSensor& anchor, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CSensor& anchor, const std::string& sContent, std::shared_ptr<CResourceManager> pResourceManager = nullptr );

			ITA_GEO_API std::string Encode( const CMirrorImage& anchor );
			ITA_GEO_API void Decode( CMirrorImage& anchor, const std::string& sContent );

			ITA_GEO_API std::string Encode( const CSpecularReflection& anchor, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CSpecularReflection& anchor, const std::string& sContent, std::shared_ptr<CResourceManager> pResourceManager = nullptr );

			ITA_GEO_API std::string Encode( const CDetectionPoint& anchor );
			ITA_GEO_API void Decode( CDetectionPoint& anchor, const std::string& sContent );


			//---PROPAGATION ANCHORS - INHOMOGENOUS MEDIA---

			ITA_GEO_API std::string Encode( const CInhomogeneity& anchor );
			ITA_GEO_API void Decode( CInhomogeneity& anchor, const std::string& sContent );

			ITA_GEO_API std::string Encode( const CEmitterInhomogeneous& anchor, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CEmitterInhomogeneous& anchor, const std::string& sContent, std::shared_ptr<CResourceManager> pResourceManager = nullptr );

			ITA_GEO_API std::string Encode( const CSensorInhomogeneous& anchor, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CSensorInhomogeneous& anchor, const std::string& sContent, std::shared_ptr<CResourceManager> pResourceManager = nullptr );

			ITA_GEO_API std::string Encode( const CSpecularReflectionInhomogeneous& anchor, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CSpecularReflectionInhomogeneous& anchor, const std::string& sContent,
			                         std::shared_ptr<CResourceManager> pResourceManager = nullptr );

			//---PROPAGATION ANCHORS - DIFFRACTION---

			ITA_GEO_API std::string Encode( const CITADiffractionWedgeApertureBase& anchor );
			ITA_GEO_API void Decode( CITADiffractionWedgeApertureBase& anchor, const std::string& sContent );


			//---PROPAGATION PATH---

			ITA_GEO_API void Export( const CPropagationPath& path, const std::string& sTargetFilePath, bool bOverwrite = true,
			                         std::shared_ptr<ITAGeo::CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Import( CPropagationPath& path, const std::string& sFilePath, std::shared_ptr<ITAGeo::CResourceManager> pResourceManager = nullptr );

			ITA_GEO_API std::string Encode( const CPropagationPath& path, std::shared_ptr<ITAGeo::CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CPropagationPath& path, const std::string& sContent, std::shared_ptr<ITAGeo::CResourceManager> pResourceManager = nullptr );

			//---PROPAGATION PATH LIST---
			ITA_GEO_API void Export( const CPropagationPathList& pathList, const std::string& sTargetFilePath, bool bOverwrite = true,
			                         std::shared_ptr<ITAGeo::CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Import( CPropagationPathList& pathList, const std::string& sFilePath, std::shared_ptr<ITAGeo::CResourceManager> pResourceManager = nullptr );

			ITA_GEO_API std::string Encode( const CPropagationPathList& pathList, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
			ITA_GEO_API void Decode( CPropagationPathList& pathList, const std::string& sContent, std::shared_ptr<CResourceManager> pResourceManager = nullptr );
		} // namespace JSON
	}     // namespace Utils
} // namespace ITAGeo

#endif // IW_ITA_GEO_UTILS_JSON_PROPAGATIONPATH

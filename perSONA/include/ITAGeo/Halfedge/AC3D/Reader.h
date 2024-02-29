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


#ifndef INCLUDE_WATCHER_ITA_GEO_HALFEDGE_AC3D_READER
#define INCLUDE_WATCHER_ITA_GEO_HALFEDGE_AC3D_READER

#pragma warning( disable : 4512 4127 )
// OpenMesh includes
#include <OpenMesh/Core/IO/reader/BaseReader.hh>
#pragma warning( default : 4512 4127 )

// Vista includes
#include <VistaBase/VistaVector3D.h>

// STL includes
#include <string>


namespace ITAGeo
{
	namespace Halfedge
	{
		namespace AC3D
		{
			//! Invis AC3D generic reader class (file or stream output)
			/**
			 * This class is globally registered as the base reader
			 * for OpenMesh objects from AC3D files. It can
			 * only handle standard mesh functionality including
			 * textures.
			 */
			class CReader : public OpenMesh::IO::BaseReader
			{
			public:
				CReader( );
				~CReader( );

				std::string sModelName; //!< Name from file

				struct CAC3DObject
				{
					struct CSurface
					{
						unsigned int uiType;
						std::vector<int> viIndices;
						int iMaterialID;
						int iReferences;

						inline CSurface( )
						{
							iMaterialID = -1;
							iReferences = -1;
						};
					};

					struct CMaterial
					{
						double dRed, dGreen, dBlue;
						double dAmbientRed, dAmbientGreen, dAmbientBlue;
						double dEmissiveRed, dEmissiveGreen, dEmissiveBlue;
						double dSpecularRed, dSpecularGreen, dSpecularBlue;
						double dShining;
						double dTransmissive;
						std::string sMaterialID;

						inline CMaterial( ) { Reset( ); };

						inline void Reset( )
						{
							sMaterialID = "default";
							dRed = dGreen = dBlue = 0.0f;
							dAmbientRed = dAmbientGreen = dAmbientBlue = 0.0f;
							dEmissiveRed = dEmissiveGreen = dEmissiveBlue = 0.0f;
							dSpecularRed = dSpecularGreen = dSpecularBlue = 0.0f;
							dShining                                      = 0.0f;
							dTransmissive                                 = 0.0f;
						};
					};

					std::string sObjectType;
					std::string sName;
					std::vector<CAC3DObject> voKids;
					std::vector<VistaVector3D> v3DVertices;
					std::vector<CSurface> voSurfaces;
				};

			private:
				std::vector<ITAGeo::Halfedge::AC3D::CReader::CAC3DObject::CMaterial> m_voMaterial;

				inline std::string get_description( ) const { return std::string( "AC3D reader" ); };
				inline std::string get_extensions( ) const { return "ac"; };
				bool read( const std::string& sFilePath, OpenMesh::IO::BaseImporter& oBaseImporter, OpenMesh::IO::Options& oOptions );
				bool read( std::istream& ssInStream, OpenMesh::IO::BaseImporter& oBaseImporter, OpenMesh::IO::Options& oOptions );
			};
		} // namespace AC3D
	}     // namespace Halfedge
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_HALFEDGE_AC3D_READER

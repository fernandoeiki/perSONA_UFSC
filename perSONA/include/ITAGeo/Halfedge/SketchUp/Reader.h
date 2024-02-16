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

#ifndef INCLUDE_WATCHER_ITA_GEO_HALFEDGE_SKETCH_UP_READER
#define INCLUDE_WATCHER_ITA_GEO_HALFEDGE_SKETCH_UP_READER

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/reader/BaseReader.hh>
#pragma warning( default : 4512 4127 )

namespace ITAGeo
{
	namespace Halfedge
	{
		namespace SketchUp
		{
			//! SketchUp generic reader class (file or stream output)
			/**
			 * This class is globally registered as the base reader
			 * for OpenMesh objects from SketchUp files. It can
			 * only handle standard mesh functionality including
			 * textures, but does not support groups, layers and components.
			 * It uses top-level geometric data, only.
			 */
			class CReader : public OpenMesh::IO::BaseReader
			{
			public:
				CReader( );
				~CReader( );

				int iSUVersion;         //!< Version from file
				std::string sModelName; //!< Name from file

			private:
				inline std::string get_description( ) const { return std::string( "SketchUp reader" ); };
				inline std::string get_extensions( ) const { return "skp"; };
				bool read( const std::string& sFilePath, OpenMesh::IO::BaseImporter& oBaseImporter, OpenMesh::IO::Options& oOptions );
				bool read( std::istream& ssInStream, OpenMesh::IO::BaseImporter& oBaseImporter, OpenMesh::IO::Options& oOptions );
			};

		} // namespace SketchUp
	}     // namespace Halfedge
} // namespace ITAGeo


#endif // INCLUDE_WATCHER_ITA_GEO_HALFEDGE_SKETCH_UP_READER

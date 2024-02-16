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


#ifndef INCLUDE_WATCHER_ITA_GEO_HALFEDGE_AC3D_WRITER
#define INCLUDE_WATCHER_ITA_GEO_HALFEDGE_AC3D_WRITER

// ITABase includes
#include <ITAException.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/writer/BaseWriter.hh>
#pragma warning( default : 4512 4127 )


namespace ITAGeo
{
	namespace Halfedge
	{
		namespace AC3D
		{
			//! AC3D generic writer class (file or stream output)
			/**
			 * This class is globally registered as the base writer
			 * for AC3D files from an OpenMesh object.
			 */
			class CWriter : public OpenMesh::IO::BaseWriter
			{
			public:
				CWriter( );
				~CWriter( );

				std::string sModelName; //!< Default: ITAGeoHalfedgeSketchUpGenericWriter

			private:
				inline std::string get_description( ) const { return std::string( "AC3D writer" ); };
				inline std::string get_extensions( ) const { return "ac"; };

				//! AC3D plain file writer
				/**
				 * Exports to AC3D file format by iterating over
				 * OpenMesh faces (only).
				 */
				bool write( const std::string& _filename, OpenMesh::IO::BaseExporter& _be, OpenMesh::IO::Options _opt, std::streamsize _precision = 6 ) const;
				bool write( std::ostream& _os, OpenMesh::IO::BaseExporter& _be, OpenMesh::IO::Options _opt, std::streamsize _precision = 6 ) const;
			};
		} // namespace AC3D
	}     // namespace Halfedge
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_HALFEDGE_AC3D_WRITER

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


#ifndef INCLUDE_WATCHER_ITA_GEO_HALFEDGE_SKETCH_UP_WRITER
#define INCLUDE_WATCHER_ITA_GEO_HALFEDGE_SKETCH_UP_WRITER

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
		namespace SketchUp
		{
			//! SketchUp generic writer class (file or stream output)
			/**
			 * This class is globally registered as the base writer
			 * for SketchUp files from an OpenMesh object. It can
			 * only handle standard mesh export functionality including
			 * textures, but does not support groups, layers and components.
			 */
			class CWriter : public OpenMesh::IO::BaseWriter
			{
			public:
				CWriter( );
				~CWriter( );

				int iSUVersion;         //!< Default: 2015
				std::string sModelName; //!< Default: ITAGeoHalfedgeSketchUpGenericWriter

			private:
				inline std::string get_description( ) const { return std::string( "SketchUp writer" ); };
				inline std::string get_extensions( ) const { return "skp"; };

				//! SketchUp plain file writer
				/**
				 * Exports to SketchUp file format by iterating over
				 * OpenMesh faces (only) and creating connected SU faces.
				 */
				bool write( const std::string& _filename, OpenMesh::IO::BaseExporter& _be, OpenMesh::IO::Options _opt, std::streamsize _precision = 6 ) const;
				bool write( std::ostream& _os, OpenMesh::IO::BaseExporter& _be, OpenMesh::IO::Options _opt, std::streamsize _precision = 6 ) const;
			};
		} // namespace SketchUp
	}     // namespace Halfedge
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_HALFEDGE_SKETCH_UP_WRITER

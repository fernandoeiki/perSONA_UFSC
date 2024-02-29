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

#ifndef INCLUDE_WATCHER_ITA_GEO_HALFEDGE_CITY_GML_READER
#define INCLUDE_WATCHER_ITA_GEO_HALFEDGE_CITY_GML_READER

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/reader/BaseReader.hh>
#pragma warning( default : 4512 4127 )

//! SketchUp generic reader class (file or stream output)
/**
 * This class is globally registered as the base reader
 * for OpenMesh objects from CityGML files.
 */
class CITAGeoHalfedgeCityGMLReader : public OpenMesh::IO::BaseReader
{
public:
	CITAGeoHalfedgeCityGMLReader( );
	~CITAGeoHalfedgeCityGMLReader( );

private:
	inline std::string get_description( ) const { return std::string( "CityGML reader" ); };
	inline std::string get_extensions( ) const { return "gml"; };
	bool read( const std::string& sFilePath, OpenMesh::IO::BaseImporter& oBaseImporter, OpenMesh::IO::Options& oOptions );
	bool read( std::istream& ssInStream, OpenMesh::IO::BaseImporter& oBaseImporter, OpenMesh::IO::Options& oOptions );
};

#endif // INCLUDE_WATCHER_ITA_GEO_HALFEDGE_CITY_GML_READER

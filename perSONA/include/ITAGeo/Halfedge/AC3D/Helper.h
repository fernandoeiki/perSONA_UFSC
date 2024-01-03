/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 * 				    ____  __________  _______
 *				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 *				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 * ----------------------------------------------------------------
 *
 */

#ifndef INCLUDE_WATCHER_ITA_GEO_AC3D_HELPER
#define INCLUDE_WATCHER_ITA_GEO_AC3D_HELPER

// ITA includes
#include <ITAException.h>
#include <ITAGeo/Halfedge/AC3D/Reader.h>

// Vista includes
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/IOManager.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

// STL includes
#include <string>

// Typedefs
typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

// @see http://www.invis.com/ac3dfileformat.html

/* ITAGeoAC3DHelper
 *
 * Functions needed to read and write Invis AC3D format, a simple text-based
 * geometry representation that is commonly used for RAVEN and Inside.
 *
 */

inline bool ReadAC3DMaterialLine( std::istream& ssInStream, ITAGeo::Halfedge::AC3D::CReader::CAC3DObject::CMaterial& oMat )
{
	std::string sMaterialID;
	ssInStream >> sMaterialID;

	if( sMaterialID[0] == '\"' && sMaterialID[sMaterialID.size( ) - 1] == '\"' )
		sMaterialID = sMaterialID.substr( 1, sMaterialID.size( ) - 2 );

	oMat.sMaterialID = sMaterialID;

	std::string sNext;
	ssInStream >> sNext;
	assert( sNext == "rgb" );

	ssInStream >> oMat.dRed;
	ssInStream >> oMat.dGreen;
	ssInStream >> oMat.dBlue;

	ssInStream >> sNext;
	assert( sNext == "amb" );

	ssInStream >> oMat.dAmbientRed;
	ssInStream >> oMat.dAmbientGreen;
	ssInStream >> oMat.dAmbientBlue;

	ssInStream >> sNext;
	assert( sNext == "emis" );

	ssInStream >> oMat.dEmissiveRed;
	ssInStream >> oMat.dEmissiveGreen;
	ssInStream >> oMat.dEmissiveBlue;

	ssInStream >> sNext;
	assert( sNext == "spec" );

	ssInStream >> oMat.dSpecularRed;
	ssInStream >> oMat.dSpecularGreen;
	ssInStream >> oMat.dSpecularBlue;

	ssInStream >> sNext;
	assert( sNext == "shi" );

	ssInStream >> oMat.dShining;

	ssInStream >> sNext;
	assert( sNext == "trans" );

	ssInStream >> oMat.dTransmissive;

	return true;
};

inline bool ReadAC3DObject( std::istream& ssInStream, ITAGeo::Halfedge::AC3D::CReader::CAC3DObject& oObject )
{
	std::string sNext;

	while( ssInStream >> sNext )
	{
		if( sNext == "name" )
		{
			ssInStream >> sNext;
			if( sNext[0] == '\"' && sNext[sNext.size( ) - 1] == '\"' )
				oObject.sName = sNext.substr( 1, sNext.size( ) - 2 );
			else
				oObject.sName = sNext;
		}
		else if( sNext == "kids" )
		{
			int iNumKids;
			ssInStream >> iNumKids;
			oObject.voKids.resize( iNumKids );
			for( size_t i = 0; i < oObject.voKids.size( ); i++ )
			{
				ITAGeo::Halfedge::AC3D::CReader::CAC3DObject& oAC3DObject( oObject.voKids[i] );
				std::string sSecondToken;
				ssInStream >> sSecondToken;
				if( sSecondToken == "OBJECT" )
					ssInStream >> oAC3DObject.sObjectType;
				if( oAC3DObject.sObjectType == "poly" )
					ReadAC3DObject( ssInStream, oAC3DObject );
				else
					ITA_EXCEPT1( IO_ERROR, "Unkown AC3D object '" + oAC3DObject.sObjectType + "'" );
			}

			return true;
		}
		else if( sNext == "data" )
		{
			ITA_EXCEPT1( NOT_IMPLEMENTED, "Data block reading in AC3D file not implemented" );
			ssInStream;
		}
		else if( sNext == "numvert" )
		{
			int iTotalNumVertices;
			ssInStream >> iTotalNumVertices;
			oObject.v3DVertices.resize( iTotalNumVertices );
			for( size_t i = 0; i < oObject.v3DVertices.size( ); i++ )
			{
				VistaVector3D& v3DVertex( oObject.v3DVertices[i] );
				ssInStream >> v3DVertex[0];
				ssInStream >> v3DVertex[1];
				ssInStream >> v3DVertex[2];
			}
		}
		else if( sNext == "numsurf" )
		{
			size_t iTotalNumSurfaces;
			ssInStream >> iTotalNumSurfaces;
			oObject.voSurfaces.resize( iTotalNumSurfaces );
			for( size_t i = 0; i < oObject.voSurfaces.size( ); i++ )
			{
				ITAGeo::Halfedge::AC3D::CReader::CAC3DObject::CSurface& oSurf( oObject.voSurfaces[i] );

				std::string sSurfToken;

				ssInStream >> sSurfToken;

				assert( sSurfToken == "SURF" );
				std::string sNumVertices;
				ssInStream >> std::hex >> oSurf.uiType;

				ssInStream >> sSurfToken;
				assert( sSurfToken == "mat" );
				ssInStream >> std::dec >> oSurf.iMaterialID;

				ssInStream >> sSurfToken;
				assert( sSurfToken == "refs" );
				ssInStream >> oSurf.iReferences;

				oSurf.viIndices.resize( oSurf.iReferences );
				for( size_t v = 0; v < oSurf.viIndices.size( ); v++ )
				{
					ssInStream >> std::dec >> oSurf.viIndices[v]; // vertex idx
					std::string sDummy;
					ssInStream >> sDummy; // '0'
					ssInStream >> sDummy; // '0'

					assert( oSurf.viIndices[v] < oObject.v3DVertices.size( ) );
				}
			}
		}
		else
		{
			std::cerr << "Unkown AC3D object token " << sNext << std::endl;
		}
	}

	return true;
};

void ImportAC3DWorldObject( const ITAGeo::Halfedge::AC3D::CReader::CAC3DObject& oObject, OpenMesh::IO::BaseImporter& oBaseImporter,
                            const std::vector<ITAGeo::Halfedge::AC3D::CReader::CAC3DObject::CMaterial>& voMaterials )
{
	std::vector<OpenMesh::VertexHandle> vhVertices( oObject.v3DVertices.size( ) );
	for( size_t i = 0; i < oObject.v3DVertices.size( ); i++ )
	{
		const VistaVector3D& v3Point( oObject.v3DVertices[i] );
		OpenMesh::Vec3f v3VertexPoint( v3Point[0], v3Point[1], v3Point[2] );
		vhVertices[i] = oBaseImporter.add_vertex( v3VertexPoint );
	}

	// std::vector< OpenMesh::FaceHandle > vhFaces(oObject.voSurfaces.size());
	for( size_t i = 0; i < oObject.voSurfaces.size( ); i++ )
	{
		std::vector<CITAMesh::VertexHandle> vhFaceVertices( oObject.voSurfaces[i].viIndices.size( ) );
		for( size_t j = 0; j < vhFaceVertices.size( ); j++ )
		{
			int iIdx          = oObject.voSurfaces[i].viIndices[j];
			vhFaceVertices[j] = vhVertices[iIdx];
		}
		OpenMesh::FaceHandle hFace = oBaseImporter.add_face( vhFaceVertices );
		oBaseImporter.set_face_texindex( hFace, oObject.voSurfaces[i].iMaterialID );
		const ITAGeo::Halfedge::AC3D::CReader::CAC3DObject::CMaterial& oMat( voMaterials[oObject.voSurfaces[i].iMaterialID] );
		oBaseImporter.set_color( hFace, OpenMesh::Vec4f( float( oMat.dRed ), float( oMat.dGreen ), float( oMat.dBlue ), float( oMat.dTransmissive ) ) );
	}

	// Recursively add kids
	for( size_t o = 0; o < oObject.voKids.size( ); o++ )
		ImportAC3DWorldObject( oObject.voKids[o], oBaseImporter, voMaterials );
};

#endif // INCLUDE_WATCHER_ITA_GEO_AC3D_HELPER

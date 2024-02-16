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

#ifndef INCLUDE_WATCHER_ITA_GEO_CITYGML_CONVERSIONS
#define INCLUDE_WATCHER_ITA_GEO_CITYGML_CONVERSIONS

// Vista includes
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>

// CityGML includes
#pragma warning( disable : 4201 )
#include <citygml/vecs.hpp>
#pragma warning( default : 4201 )


#pragma warning( disable : 4512 4127 )

// OpenMesh includes
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

#pragma warning( default : 4512 4127 )


// STL includes
#include <string>

// Typedefs
typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

//! Creates CITAMesh point from CityGML point (double precision)
CITAMesh::Point CityGMLPoint3DToITAMeshPoint( TVec3d& vCityGMLPoint );

#endif // INCLUDE_WATCHER_ITA_GEO_CITYGML_CONVERSIONS

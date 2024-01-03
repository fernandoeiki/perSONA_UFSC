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

#ifndef INCLUDE_WATCHER_ITA_GEO_HALFEDGE_MATERIAL
#define INCLUDE_WATCHER_ITA_GEO_HALFEDGE_MATERIAL

// ITAGeo includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/ModelBase.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

namespace ITAGeo
{
	class IMaterial;

	namespace Halfedge
	{
		//! Adds CITAAcousticMaterialProperty to the mesh
		ITA_GEO_API void AddAcousticFacePropertyToMesh( CITAMesh* pMesh, OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp );

		//! Adds acoustic material to a mesh face
		ITA_GEO_API bool AssignFaceMaterial( CITAMesh* pMesh, std::shared_ptr<Material::IMaterial> pMaterial, CITAMesh::FaceHandle hFace,
		                                     OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp );
	} // namespace Halfedge
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_HALFEDGE_MATERIAL

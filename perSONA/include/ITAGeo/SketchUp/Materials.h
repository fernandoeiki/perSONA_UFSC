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

#ifndef INCLUDE_WATCHER_ITA_GEO_SU_MATERIALS
#define INCLUDE_WATCHER_ITA_GEO_SU_MATERIALS

#include <ITAGeo/Material/Manager.h>
#include <ITAGeo/Material/Material.h>

// Sketchup includes
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/material.h>
#include <SketchUpAPI/model/texture.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

// STL includes
#include <string>

// Typedefs
typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

namespace ITAGeo
{
	namespace SketchUp
	{
		//! Converts a color to a one-dimensional acoustic material
		ITA_GEO_API bool SUColorToOneDimAcousticMaterial( std::shared_ptr<Material::CScalarMaterial> pMaterial, const SUColor& tColor );

		//! Creates SU material from acoutic material
		ITA_GEO_API bool AcousticMaterialToSUMaterial( CITAMesh* pMesh, CITAMesh::FaceHandle hFace, SUMaterialRef* rFaceMaterial,
		                                               OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp,
		                                               std::shared_ptr<ITAGeo::Material::IManager> pManager );

		//! Connects an acoustic material from SU face to ITAMesh
		ITA_GEO_API SUResult SUMaterialToAcousticMaterial( CITAMesh* pMesh, CITAMesh::FaceHandle hFace, SUFaceRef rFace,
		                                                   OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp,
		                                                   std::shared_ptr<ITAGeo::Material::IManager> pManager = NULL );

	} // namespace SketchUp
} // namespace ITAGeo
#endif // INCLUDE_WATCHER_ITA_GEO_SU_MATERIALS

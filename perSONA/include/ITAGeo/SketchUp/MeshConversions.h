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

#ifndef INCLUDE_WATCHER_ITA_GEO_SU_MESH_CONVERSIONS
#define INCLUDE_WATCHER_ITA_GEO_SU_MESH_CONVERSIONS

// ITAGeo includes
#include <ITAGeo/Material/Manager.h>

// Sketchup includes
#include <SketchUpAPI/model/component_definition.h>
#include <SketchUpAPI/model/component_instance.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/layer.h>
#include <SketchUpAPI/transformation.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

// STL includes
#include <vector>

// Typedefs
typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

namespace ITAGeo
{
	namespace SketchUp
	{
		//! Add entities to the mesh
		ITA_GEO_API SUResult SUEntitiesToITAMesh( SUEntitiesRef rEntities, CITAMesh* pMesh, bool bExplodeGroups,
		                                          OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp,
		                                          std::shared_ptr<Material::IManager> pMaterialManager = nullptr );

		//! Add entities to the mesh with transformation chain
		ITA_GEO_API SUResult SUEntitiesToITAMesh( SUEntitiesRef rEntities, CITAMesh* pMesh, bool bExplodeGroups, std::vector<SUTransformation>& vtTransform,
		                                          OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp,
		                                          std::shared_ptr<Material::IManager> pMaterialManager = nullptr );

		//! Convert from ITAMesh to SketchUp entities (and add to a layer if not NULL)
		ITA_GEO_API SUResult ITAMeshToSUEntities( CITAMesh* pMesh, SUEntitiesRef* rEntities, OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp,
		                                          SULayerRef* pSULayer = NULL );

		//! Converts from SketchUp component instante to mesh
		ITA_GEO_API SUResult SUComponentInstanceToITAMesh( SUComponentInstanceRef rCompInstance, CITAMesh* pMesh,
		                                                   OpenMesh::FPropHandleT<Material::CAcousticFaceProperty>& tAcousticFaceProp,
		                                                   std::shared_ptr<Material::IManager> pMaterialManager = nullptr );
	} // namespace SketchUp
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_SU_MESH_CONVERSIONS

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

#ifndef INCLUDE_WATCHER_ITA_GEO_SU_CONVERSIONS
#define INCLUDE_WATCHER_ITA_GEO_SU_CONVERSIONS

// Vista includes
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>

// Sketchup includes
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/transformation.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

// STL includes
#include <string>

// Typedefs
typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

/*
 * \note SketchUp (SU) uses inches internally. We usually use SI units, hence meter. If
 * you don't care about units, however, this will be the default in all conversion functions.
 *
 */

//! Creates CITAMesh point from SketchUp point
CITAMesh::Point SUPoint3DToITAMeshPoint( const SUPoint3D& vSUPoint, SUModelUnits iUnits = SUModelUnits_Inches );

//! Returns VistaVector point from SketchUp point
VistaVector3D SUPoint3DToVistaVector3D( const SUPoint3D& vSUPoint, SUModelUnits iUnits = SUModelUnits_Inches );

//! Convert VistaVector to ITAMesh point (always SI units)
CITAMesh::Point VistaVectorToITAMeshPoint( const VistaVector3D& vVPoint );

//! Convert VistaVEctor to SketchUp point
SUPoint3D VistaVectorToSUPoint( const VistaVector3D& vVPoint, SUModelUnits iUnits = SUModelUnits_Inches );

//! Creates CITAMesh point from SketchUp point and applies transformation (i.e. from component instance)
CITAMesh::Point SUPoint3DToITAMeshPointTransformed( const SUPoint3D& vSUPoint, const std::vector<SUTransformation>& tTransformChain,
                                                    SUModelUnits iUnits = SUModelUnits_Inches );

//! Merges a vector of SU transformations to a single Vista transformation matrix
VistaTransformMatrix SUTransformVectorToVistaTransformMatrix( const std::vector<SUTransformation>&, SUModelUnits iUnits = SUModelUnits_Inches );

//! Convert from SketchUp transformation matrix to Vista transformation matrix
VistaTransformMatrix SUTransformToVistaTransformMatrix( const SUTransformation& tTransform, SUModelUnits iUnits = SUModelUnits_Inches );

//! Convert from Vista transformation matrix to SketchUp transformation
SUTransformation VistaTransformMatrixToSUTransform( const VistaTransformMatrix& oTransform, SUModelUnits iUnits = SUModelUnits_Inches );

//! Convert from CITAMesh point to SketchUp point
SUPoint3D ITAMeshPointToSUPoint3D( const CITAMesh::Point& vITAPoint, SUModelUnits iUnits = SUModelUnits_Inches );

#endif // INCLUDE_WATCHER_ITA_GEO_SU_CONVERSIONS

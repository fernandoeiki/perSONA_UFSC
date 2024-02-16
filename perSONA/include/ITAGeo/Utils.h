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

#ifndef INCLUDE_WATCHER_ITA_GEO_UTILS
#define INCLUDE_WATCHER_ITA_GEO_UTILS

// ITAGeo includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>

// Vista includes
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>
#include <VistaMath/VistaGeometries.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

// STL
#include <list>
#include <string>

//! Namespace of utility functions for geometrical acoustics
/**
 * The utility functions implemented are usually returning true if calculation was successfull
 * of if the result is valid, i.e. a point-in-polygon test will return true if point is in polygon,
 * but an finite aperture point calculation will return true if the point is in range while returning
 * the actual value into a provided output parameter.
 */
namespace ITAGeoUtils
{
	// Typedefs
	typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

	//! Returns only true, if a point lies within given polygon and in same plane, false otherwise
	/**
	 * Calculates the dot product of all edges with the start-vertex-to-point vector and compares
	 * them among each other. Only, if all dot products have the same sign, the function will return true.
	 */
	ITA_GEO_API bool IsPointInConvexPolygon( const VistaVector3D& v3Point, VistaPolygon& oPolygon );

	ITA_GEO_API bool IsPointInFace( const VistaVector3D& v3Point, CITAMesh* pMesh, CITAMesh::FaceHandle hFace );

	ITA_GEO_API bool IsPointInFace( const VistaVector3D& v3Point, const std::vector<std::shared_ptr<VistaVector3D>>& vv3FaceVertices );

	ITA_GEO_API bool IsPointOnHalfedge( const VistaVector3D& v3Point, const VistaVector3D& v3HalfedgeStart, const VistaVector3D& v3HalfedgeEnd );

	ITA_GEO_API bool IsPointOnHalfedge( const VistaVector3D& v3Point, CITAMesh* pMesh, CITAMesh::HalfedgeHandle hHalfedge );

	//! Returns only true, if a ray casts through given polygon, false otherwise
	ITA_GEO_API bool RayConvexPolygonIntersectionTest( const VistaRay& rRay, VistaPolygon& oPolygon, VistaVector3D& v3IntersectionPoint,
	                                                   ITAGeo::ECulling eFaceCulling = ITAGeo::ECulling::BACKFACE );

	//! Returns only true, if a ray casts through given mesh face, false otherwise
	ITA_GEO_API bool RayFaceIntersectionTest( const VistaRay& rRay, CITAMesh* pMesh, CITAMesh::FaceHandle hFace, VistaVector3D& v3IntersectionPoint,
	                                          ITAGeo::ECulling eFaceCulling = ITAGeo::ECulling::BACKFACE );

	//! Returns reflected direction of incident ray according to the principle of specular reflection (Snells law)
	/**
	 * @param[in] pMesh Mesh of the scene
	 * @param[in] hFace Face handle for identifying the corresponding reflection face
	 * @param[in] rRay Incident ray which direction is to be changed
	 *
	 * @return Direction of specular reflection
	 */
	ITA_GEO_API VistaVector3D GetReflectedDirection( CITAMesh* pMesh, CITAMesh::FaceHandle hFace, const VistaRay& rRay );

	//! Checks for intersection of a ray with a sphere
	/**
	 * @return: true if an intersection is given
	 * @param[in] rRay: ray
	 * @param[in] pDetectionSphereCenter: center of detection sphere
	 * @param[in] fDetectionSphereRadius: radius of detection sphere
	 */
	ITA_GEO_API bool RayDetectionSphereIntersectionTest( const VistaRay& rRay, std::shared_ptr<ITAGeo::CPropagationAnchor> pDetectionSphereCenter,
	                                                     float fDetectionSphereRadius, VistaVector3D& v3DetectionPoint );

	//! Sets random angles according to uniformly distributed PDF on the surface of the unity sphere
	/**
	 * @param[out] fRandomAzimuthAngleRad:	randomly distributed in the range [0, 2*pi]
	 * @param[out] fRandomElevationAngleRad:	randomly distributed in the range [0, pi]
	 */
	ITA_GEO_API void GetUniformlyDistributedSphericalCoordinateAngles( float& fRandomAzimuthAngleRad, float& fRandomElevationAngleRad );

	//! Creates vector which random direction is uniformly distributed on the surface of the unity sphere
	ITA_GEO_API VistaVector3D GetUniformlyDistributedSphericalRandomDirection( );

	ITA_GEO_API ITAGeo::EIntersecting IsLineIntersectingFace( const VistaVector3D& v3StartPoint, const VistaVector3D& v3EndPoint, CITAMesh* pMesh,
	                                                          CITAMesh::FaceHandle hFace );

	//! Mirrors point over a plane
	ITA_GEO_API void MirrorPointOverPlane( const VistaVector3D& v3Point, const VistaPlane& oPlane, VistaVector3D& v3MirroredPoint );

	//! Return opening angle from wedge main face to a point in space
	/**
	 * @param[out] fAngleRad Opening angle in radiants
	 */
	ITA_GEO_API float GetWedgeMainFaceElevationToPointRad( const VistaVector3D& v3StartVertex, const VistaVector3D& v3EndVertex, const VistaVector3D& v3FaceNormal1,
	                                                       const VistaVector3D& v3Point );

	//! Checks if a point is outside a diffraction wedge structure, returns true also in case a point lies right on faces.
	ITA_GEO_API bool IsPointOutsideDiffractionWedge( const VistaVector3D& v3StartVertex, const VistaVector3D& v3EndVertex, const VistaVector3D& v3FaceNormal1,
	                                                 const VistaVector3D& v3FaceNormal2, const VistaVector3D& v3Point );

	inline bool IsPointInsideDiffrationWedge( const VistaVector3D& v3StartVertex, const VistaVector3D& v3EndVertex, const VistaVector3D& v3FaceNormal1,
	                                          const VistaVector3D& v3FaceNormal2, const VistaVector3D& v3Point )
	{
		return !IsPointOutsideDiffractionWedge( v3StartVertex, v3EndVertex, v3FaceNormal1, v3FaceNormal2, v3Point );
	};

	//! Checks if a point lies in front of a face. If it lies beyond the face, the face can not be illuminated.
	ITA_GEO_API bool CanFaceBeIlluminated( const CITAMesh& oMesh, CITAMesh::FaceHandle hFace, const VistaVector3D& v3Origin );

	//! Checks if a point lies in front of a plane. If it lies beyond the plane, the point and the plane cannot illuminate each other
	ITA_GEO_API bool IsPointInFrontOfPlane( const VistaPlane& oPlane, const VistaVector3D& v3Point );

	//! Checks, if a position on a ray along the edge between given vertices is within range of the edge's endpoints
	/**
	 * Useful to test if a intersection point of a plane with the given edge is within the edge's vertices.
	 *
	 * @param[out] v3PointOnEdgeRay Aperture point under test, lies within ray with direction of edge between vertices
	 *
	 * @todo Move to wedge class
	 */
	ITA_GEO_API bool IsDiffractionAperturePointInRange( const VistaVector3D& v3StartVertex, const VistaVector3D& v3EndVertex, const VistaVector3D& v3PointOnEdge );

	//! Calculates the diffraction angle
	/**
	 * @param[out] dAngle Diffraction angle in radians
	 */
	ITA_GEO_API bool CalculateDiffractionAngle( const VistaVector3D& v3StartPoint, const VistaVector3D& v3AperturePoint, const VistaVector3D& v3EndPoint, float& dAngle );

	//! Calculates the aperture point on an finite wedge and returns true if within bounds
	/**
	 * @param[out] v3AperturePoint
	 * @todo Move to wedge class
	 */
	ITA_GEO_API bool CalculateDiffractionAperturePoint( const VistaVector3D& v3StartVertex, const VistaVector3D& v3EndVertex, const VistaVector3D& v3SourcePos,
	                                                    const VistaVector3D& v3TargetPos, VistaVector3D& v3AperturePoint );

	//! Calculates the aperture point on an infinite wedge along given ray and returns true if calculation possible
	/**
	 * @param[out] v3AperturePoint
	 * @return True, if calculation was possible (aperture point can still be outside of edge)
	 */
	ITA_GEO_API bool CalculateDiffractionAperturePoint( const VistaRay& rInfiniteDiffractionEdge, const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos,
	                                                    VistaVector3D& v3AperturePoint );

	//! Rotates a point into target face plane around edge given by vertices (rotatory projection)
	/**
	 * Rojection will always be performed right-handed around ray until circular trajectory intersects with positive face of plane,
	 * i.e. intersection from front-face and not back-face.
	 *
	 * @sa RojectPoint with two faces
	 */
	ITA_GEO_API bool RojectPoint( const VistaVector3D& v3VertexStart, const VistaVector3D& v3VertexEnd, const VistaVector3D& v3TargetPlaneNormal,
	                              const VistaVector3D& v3Point, VistaVector3D& v3RojectedPoint );

	//! Rotates a point into target face plane with respect to wedge formed with source face plane (rotatory projection)
	/**
	 * Rojection will always be performed in a from source to receiver manner for rojection algorithm,
	 * i.e. rojected point will always be lying off edge and never on target face polygon of wedge.
	 *
	 * @sa RojectPoint with two faces
	 */
	ITA_GEO_API bool RojectPoint( const VistaVector3D& v3VertexStart, const VistaVector3D& v3VertexEnd, const VistaVector3D& v3SourcePlaneNormal,
	                              const VistaVector3D& v3TargetPlaneNormal, const VistaVector3D& v3Point, VistaVector3D& v3RojectedPoint );


	//! Calculates the number of required images for a given order and face number
	/**
	 * @param[in] iFaceCount Number of faces
	 * @param[in] iOrder Image order (0 = no images), @sa ITAGeo::Order
	 *
	 * @return Numer of required images (not necessarily audible)
	 */
	ITA_GEO_API unsigned long int CalculateNumberOfImages( const int iFaceCount, const int iOrder );

	ITA_GEO_API std::string GetAcousticMaterialTypeString( const int iType );

	ITA_GEO_API bool VistaPlaneFromOpenMeshFace( CITAMesh* pMesh, CITAMesh::FaceHandle hFace, VistaPlane& oPlane );

	ITA_GEO_API bool VistaPolygonFromOpenMeshFace( CITAMesh* pMesh, CITAMesh::FaceHandle hFace, VistaPolygon& oPolygon );

	ITA_GEO_API bool VistaRaysFromOpenMeshFaceHalfedges( CITAMesh* pMesh, CITAMesh::FaceHandle hFace, std::vector<VistaRay>& vRays );

	//! Generates a clear text identifier based on anchor types and related data
	ITA_GEO_API std::string GenerateIdentifier( const ITAGeo::CPropagationPath& oPath );

	//! Substitutes path's identifier with clear text identifier to all paths in the list
	ITA_GEO_API void AddIdentifier( ITAGeo::CPropagationPathList& oPathList );
}; // namespace ITAGeoUtils

#endif // INCLUDE_WATCHER_ITA_GEO_UTILS

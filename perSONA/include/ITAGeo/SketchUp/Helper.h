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

#ifndef INCLUDE_WATCHER_ITA_GEO_SU_HELPER
#define INCLUDE_WATCHER_ITA_GEO_SU_HELPER

// Vista includes
#include <VistaBase/VistaTransformMatrix.h>
#include <VistaBase/VistaVector3D.h>

// Sketchup includes
#include <SketchUpAPI/slapi.h>
#include <SketchUpAPI/unicodestring.h>

// OpenMesh includes
#pragma warning( disable : 4512 4127 )
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#pragma warning( default : 4512 4127 )

// STL includes
#include <string>

//! ITAMesh short name
typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

//! Converts SketchUp result to ITAException on error (with function name)
void SU2ITAException( SUResult, std::string sFunctionName = "" );

//! SU function call with ITException raised on SU error (exception)
#define SU_EXC( SU_FUNCTION )                                                                                            \
	{                                                                                                                    \
		SUResult sur;                                                                                                    \
		if( ( sur = SU_FUNCTION ) != SU_ERROR_NONE )                                                                     \
			SU2ITAException( sur, __FUNCTION__ + std::string( " in line " ) + std::to_string( (long double)__LINE__ ) ); \
	};

//! SU function call with function return call on SU error (quiet)
#define SU_RET( SU_FUNCTION )                        \
	{                                                \
		SUResult sur;                                \
		if( ( sur = SU_FUNCTION ) != SU_ERROR_NONE ) \
			return sur;                              \
	};

//! SU function call with true/false condition on SU error (quiet)
#define SU_RET_FALSE( SU_FUNCTION ) { ( ( SU_FUNCTION ) != SU_ERROR_NONE ) ? true : false };

//! Converts from SketchUp string to std::string
std::string SUStringToStdString( SUStringRef sSUString );

#endif // INCLUDE_WATCHER_ITA_GEO_SU_HELPER

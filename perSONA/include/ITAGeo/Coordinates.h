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

#ifndef INCLUDE_WATCHER_ITA_GEO_COORDINATES
#define INCLUDE_WATCHER_ITA_GEO_COORDINATES

// ITAGeo includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes
#include <ITAConstants.h>

// STL includes
#include <algorithm>


namespace ITAGeo
{
	namespace Coordinates
	{
		inline float RadiansToDegree( float fRadianValue ) { return fRadianValue * 180.0f / ITAConstants::PI_F; };

		inline float DegreeToRadians( float fDegreeValue ) { return fDegreeValue / 180.0f * ITAConstants::PI_F; };

		//! Spherical coordinate system after ISO norm 80000-2:2009 (mathematical interpretation)
		class ITA_GEO_API CSpherical
		{
		public:
			//! Initializes with all values set to zero
			inline CSpherical( ) : m_fPhi( 0.0f ), m_fThetaRad( 0.0f ), m_fR( 0.0f ) { };

			//! Creates the coordinates based on an ISO Cartesian direction
			inline CSpherical( const VistaVector3D& v3TargetPos, const ECoordinateSystemConvention iCSC = ISO )
			{
				if( iCSC == ISO )
					CalculateFromCartesianISOConvention( v3TargetPos );
				else if( iCSC == OPENGL )
					CalculateFromCartesianOpenGLConvention( v3TargetPos );
				else
					ITA_EXCEPT_INVALID_PARAMETER( "Unrecognized coordinate system convention, cannot calculate spherical coordinates" )
			};

			inline virtual ~CSpherical( ) { };

			//! Azimuth angle in radians
			inline float GetAzimuthRadians( ) const { return m_fPhi; };

			//! Azimuth angle in degree
			inline float GetAzimuthDegree( ) const { return RadiansToDegree( GetAzimuthRadians( ) ); };

			//! Inclination angle (polar interpretation: zero starting at north pole) in radians
			inline float GetInclinationRadians( ) const { return m_fThetaRad; };

			//! Inclination angle (polar interpretation: zero starting at north pole) in degree
			inline float GetInclinationDegree( ) const { return RadiansToDegree( GetInclinationRadians( ) ); };

			//! Elevation angle (polar interpretation: equator is zero elevation) in radians
			inline float GetElevationRadians( ) const { return ITAConstants::HALF_PI_F - m_fThetaRad; };

			//! Elevation angle (polar interpretation: equator is zero elevation) in degree
			inline float GetElevationDegree( ) const { return RadiansToDegree( GetElevationRadians( ) ); };

			//! Returns the radius / distance (usually meters)
			float GetRadius( ) const { return m_fThetaRad; };

			//! Determines spherical angles based on ISO Cartesian point as target (reference frame is in coordinate system origin at [ 0 0 0 ])
			/**
			 * ISO convention means, that north pole (up vector) is at positive Z, front (view vector) is at X = 1 and Y = 0 and Z = 0
			 */
			inline void CalculateFromCartesianISOConvention( const VistaVector3D& v3TargetPos )
			{
				const float r = v3TargetPos.GetLength( );
				if( r == 0.0f )
				{
					m_fR = m_fPhi = m_fThetaRad = 0.0f;
					return;
				}

				m_fR        = r;
				m_fThetaRad = acos( v3TargetPos[Vista::X] / m_fR );
				m_fPhi      = atan2( v3TargetPos[Vista::Y], v3TargetPos[Vista::X] );
			};

			//! Determines spherical angles based on OpenGL Cartesian point as target (reference frame is in coordinate system origin at [ 0 0 0 ])
			/**
			 * OpenGL convention means, that north pole (up vector) is at positive Y, front (view vector) is at Z = -1 and Y = 0 and X = 0
			 */
			inline void CalculateFromCartesianOpenGLConvention( const VistaVector3D& v3TargetPos )
			{
				const float r = v3TargetPos.GetLength( );
				if( r == 0.0f )
				{
					m_fR = m_fPhi = m_fThetaRad = 0.0f;
					return;
				}

				m_fR        = r;
				m_fThetaRad = acos( v3TargetPos[Vista::Y] / m_fR );
				m_fPhi      = atan2( v3TargetPos[Vista::X], -v3TargetPos[Vista::Z] );
			};

		private:
			float m_fR, m_fThetaRad, m_fPhi;
		};

		typedef CSpherical CSpherical_ISO_80000_2_2009_Degree;
	} // namespace Coordinates
};    // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_COORDINATES

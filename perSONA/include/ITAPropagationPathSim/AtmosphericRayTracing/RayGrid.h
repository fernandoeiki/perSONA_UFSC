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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_RAYGRID
#define IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_RAYGRID

#include <ITAPropagationPathSim/Definitions.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes
#include <ITAPropagationPathSim/AtmosphericRayTracing/Rays.h>

// STD
#include <memory>
#include <set>
#include <vector>

namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		//! This class represents a set of rays which is ordered in a grid (matrix) referring to the angles of initial direction (theta and phi)
		/**
		 *	This special arrangement of rays allows to find the direct neigbors of any ray in this grid.
		 */
		class ITA_PROPAGATION_PATH_SIM_API CRayGrid
		{
		protected:
			typedef std::shared_ptr<CRay> RayPtr;
			typedef std::vector<RayPtr> RayVector;
			typedef std::vector<RayVector> RayMatrix;

			VistaVector3D m_v3SourcePos;      //!< Origin of all rays in this ray grid.
			std::vector<double> m_vdThetaDeg; //!< Sorted vector of elevation angles in degrees.
			std::vector<double> m_vdPhiDeg;   //!< Sorted vector of azimuth angles in degrees.
			bool m_bCircularPhi = false;      //!< Indicates whether the azimuth vector is considered to be circular (phi covers full 360 degrees) or not.
		private:
			RayMatrix m_vvpRayMatrix;        //!< Matrix of pointers to ray. First index refers to elevation (theta), second to azimuth (phi) angle.
			RayVector m_vpRays;              //!< Vector of all rays contained by vvpRayMatrix. May contain duplicates at poles (theta = 0 or 180°).
			std::set<RayPtr> m_vpUniqueRays; //!< Unique set of all rays contained by vvpRayMatrix.

		private:
			CRayGrid( const RayMatrix& rayMatrix, const std::vector<double>& thetaDeg, const std::vector<double>& phiDeg, const bool circularPhi = false );
			void UpdateDependentRayContainers( );

		protected:
			inline CRayGrid( bool circularPhi = false ) : m_bCircularPhi( circularPhi ) { };
			//! Creates new rays using the angles of initial directions and inserts them into the ray matrix
			void InitRays( );

		public:
			//! Creates a set of rays using a source position and the given elevation and azimuth angles [°] for the inital directions. An optional bool indicates whether
			//! the azimuth angle covers the full 360°.
			/**
			 * For each combination of theta and phi, one ray is created and stored.
			 *	Note, that both vectors with angles will be sorted before creating the rays if not specified otherwise.
			 */
			CRayGrid( const VistaVector3D& sourcePos, const std::vector<double>& thetaDeg, const std::vector<double>& phiDeg, const bool circularPhi = false,
			          const bool sortAngleVectors = true );

		protected:
			//! Updates the ray matrix and depenent vectors/set of rays.
			void SetRayMatrix( const RayMatrix& newRayMatrix );
			//! Filters for certain rays using indices for theta and phi.
			void FilterDirections( const std::vector<int>& thetaIdxVec, const std::vector<int>& phiIdxVec, const bool circularPhi = false );

			//! Returns a vector with all rays having the same initial elevation as the given ray. Throws an exception if the ray is not part of this grid.
			const RayVector& GetRaysWithSameTheta( const std::shared_ptr<CRay> pRay );
			//! Returns a vector with all rays having the same initial azimuth as the given ray. Throws an exception if the ray is not part of this grid.
			RayVector GetRaysWithSamePhi( const std::shared_ptr<CRay> pRay );

			//---Indicing Functions---
		protected:
			int GetIndex( const std::shared_ptr<CRay> pRay ) const;
			int IndexToThetaIndex( const int idx ) const;
			int IndexToPhiIndex( const int idx ) const;
			void GetNeighboringAngleIndices( const std::shared_ptr<CRay> pRay, std::vector<int>& thetaIdxVec, std::vector<int>& phiIdxVec ) const;

			//---Booleans---
		protected:
			bool IsPoleDirection( const double& thetaDeg ) const;
			bool HasPoleDirection( const std::shared_ptr<CRay> pRay ) const;

		public:
			//! Returns true if the phi angles are defined circular (covering a full circle)
			inline bool IsCircular( ) const { return m_bCircularPhi; };
			bool IsEmpty( ) const;
			bool Is2D( ) const;
			bool Contains( const std::shared_ptr<CRay> pRay ) const;

			//---GET Functions---
		protected:
			inline const std::vector<std::shared_ptr<CRay>>& Rays( ) const { return m_vpRays; };
			inline const RayMatrix& Matrix( ) const { return m_vvpRayMatrix; };

		public:
			inline const std::vector<double>& ThetaDeg( ) const { return m_vdThetaDeg; };
			inline const std::vector<double>& PhiDeg( ) const { return m_vdPhiDeg; };
			inline int NTheta( ) const { return (int)m_vdThetaDeg.size( ); };
			inline int NPhi( ) const { return (int)m_vdPhiDeg.size( ); };
			inline int NRays( ) const { return (int)m_vpRays.size( ); };
			inline const VistaVector3D& SourcePosition( ) const { return m_v3SourcePos; };
			inline const std::set<std::shared_ptr<CRay>>& UniqueRays( ) const { return m_vpUniqueRays; };
			inline const std::shared_ptr<CRay> At( int idxTheta, int idxPhi ) const { return m_vvpRayMatrix[idxTheta][idxPhi]; };

			//! Calculates and returns an approximation for the surface area of the wavefront at given time by spanning triangles between rays
			double WavefrontSurface( const double& time ) const;
			//! Calculates the surface area for a spherical wavefront at 1m distance using the limits of theta and phi of this grid
			double WavefrontSurfaceReference( ) const;

			//! Returns a ray grid containing the rays surrounding the given ray (including this ray).
			/**
			 * Throws an exception if the given ray is not part of this ray grid.
			 */
			CRayGrid SurroundingGrid( const std::shared_ptr<CRay> pRay ) const;
			//! Sets the boundaries of this ray grid to the rays surrounding the given ray (including this ray).
			/**
			 * Throws an exception if the given ray is not part of this ray grid.
			 */
			void SetToSurroundingGrid( const std::shared_ptr<CRay> pRay );

			//! Creates a ray grid with the same initial ray directions but new rays
			CRayGrid CopyWithNewRays( ) const;
		};

		//! A special CRayGrid with an equiangular distribution
		class ITA_PROPAGATION_PATH_SIM_API CEquiangularRayDistribution : public CRayGrid
		{
		public:
			//! Creates an equiangular ray distribution with N rays along elevation and azimuth respectively
			CEquiangularRayDistribution( const VistaVector3D& sourcePos, const int nAngles );
			//! Creates an equiangular ray distribution with N1 rays along elevation and N2 rays along azimuth
			CEquiangularRayDistribution( const VistaVector3D& sourcePos, const int nTheta, const int nPhi );
		};
	} // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_RAYGRID
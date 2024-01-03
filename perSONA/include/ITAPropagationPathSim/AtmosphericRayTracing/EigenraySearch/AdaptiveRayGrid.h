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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_ADAPTIVERAYGRID
#define IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_ADAPTIVERAYGRID

#include <ITAPropagationPathSim/AtmosphericRayTracing/RayGrid.h>


// STD
#include <set>


namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		namespace EigenraySearch
		{
			class ITA_PROPAGATION_PATH_SIM_API CAdaptiveRayGrid : public CRayGrid
			{
			private:
				double m_dMaxDeltaTheta = -1;
				double m_dMaxDeltaPhi   = -1;
				std::set<std::shared_ptr<CRay> > m_vpNewRaysOfLastAdaptation;

			public:
				inline CAdaptiveRayGrid( ) { };
				CAdaptiveRayGrid( const CRayGrid& rayGrid );

			public:
				void Init( );
				void Reset( const CRayGrid& rayGrid );

				//! Maximum angular resolution in degrees
				inline const double& MaxAngularResolution( ) { return m_dMaxDeltaTheta < m_dMaxDeltaPhi ? m_dMaxDeltaPhi : m_dMaxDeltaTheta; };
				//! Maximum elevation resolution in degrees
				inline const double& MaxDeltaTheta( ) { return m_dMaxDeltaTheta; };
				//! Maximum azimuth resolution in degrees
				inline const double& MaxDeltaPhi( ) { return m_dMaxDeltaPhi; };
				//! Returns a unique set of the rays which were adding during the last adaptation
				inline const std::set<std::shared_ptr<CRay> >& NewRaysOfLastAdaptation( ) const { return m_vpNewRaysOfLastAdaptation; };

				//! Simple adaptation method: Setting the limits to neighboring rays and shoots additional rays to double the angular resolution of the grid.
				void ZoomIntoRay( const std::shared_ptr<CRay> pRay );
				//! Advanced adaptation method: Further reduces the angular limits using additional information compared to simple method before doubling the angular
				//! resolution.
				void ZoomIntoRay( const std::shared_ptr<CRay> pRay, const VistaVector3D& v3ReceiverPosition, const double& dThreshold );
				//! Zooms into the given ray using a specific angular resolution by creating up to 8 new rays surrounding the given one.
				void ZoomIntoRay( const std::shared_ptr<CRay> pRay, const double& deltaTheta, const double& deltaPhi );

			private:
				//! Further reduces the limits of the ray grid using additional information on given rays and the receiver position
				/**
				 * If the original ray grid looks like the sketch below where r5 is the ray with minimum distance to the receiver,
				 *	this will decide whether the eigenray is rather above/below and left/right of it. In best case, the number of rays is reduced from 9 to 4.
				 *
				 *		r1--------r2----------r3
				 *		|   c1   /     c2      \
				 *		r4------r5-------------r6
				 *		\  c3   \    c4      /
				 *		r7------r8--------r9
				 *
				 *	Also works for a 1D ray grid (NTheta == 1 or NPhi() == 1)
				 */
				void SetAdvancedRayGridLimits( const std::shared_ptr<CRay> pRay, const int idxMinDist, const VistaVector3D& receiverPosition, const double& threshold );
				//! By comparing the vector from three rays to the receiver, this decides between which two rays the eigenray is located and returns their indices
				std::vector<int> FindAdvancedRayGridLimits1D( const std::vector<std::shared_ptr<CRay> >& pRays, const int idxMinDist,
				                                              const VistaVector3D& receiverPosition, const double& threshold ) const;
				void DoubleRayResolution( );
				void DoubleThetaResolution( );
				void DoublePhiResolution( );
			};
		} // namespace EigenraySearch
	}     // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_ADAPTIVERAYGRID
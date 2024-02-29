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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_ODESOLVER
#define IW_ITA_PROPAGATIONPATHSIM_ART_ODESOLVER

#include <ITAPropagationPathSim/Definitions.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes
#include <ITAGeo/Atmosphere/StratifiedAtmosphere.h>


namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		namespace ODESolver
		{
			//! Converts a wavefront normal to a slowness vector for given altitude in stratified atmosphere
			ITA_PROPAGATION_PATH_SIM_API VistaVector3D NormalToSlowness( const VistaVector3D& n, const double& rz, const ITAGeo::CStratifiedAtmosphere& atmosphere );

			//! Converts a slowness vector to a wavefront normal
			/**
			 * The wavefront normal has the same direction as the slowness vector (n = s / norm(s))
			 */
			ITA_PROPAGATION_PATH_SIM_API VistaVector3D SlownessToNormal( const VistaVector3D& s );


			//! Solves the ordinary differential equations (ODEs) of ray propagation in a stratified medium using the Euler method
			/**
			 * @param[in,out] r Current wavefront position. Will be updated.
			 * @param[in,out] s Current slowness vector. Will be updated.
			 * @param[in] dt Time step for integration
			 * @param[in] atmosphere Stratified atmosphere
			 */
			ITA_PROPAGATION_PATH_SIM_API void Euler( VistaVector3D& r, VistaVector3D& s, const double& dt, const ITAGeo::CStratifiedAtmosphere& atmosphere );


			//! Solves the ordinary differential equations (ODEs) of ray propagation in a stratified medium using the Euler method
			/**
			 * @param[in] r Current wavefront position.
			 * @param[in] s Current slowness vector.
			 * @param[in] dt Time step for integration
			 * @param[in] atmosphere Stratified atmosphere
			 * @param[out] rNew New wavefront position.
			 * @param[out] sNew New slowness vector.
			 *
			 * Literature for solver:
			 * W. H. Press, S. A. Teukolsky, W. T. Vetterling, and B. P. Flannery. Numerical recipes in C: The Art of Scientific Computing. Cambridge University Press,
			 * 2nd edition, 1992.
			 *
			 * The differential equations are taken from the slowness vector approach described in:
			 * A. D. Pierce. Acoustics: An Introduction to Its Physical Principles and Applications, volume 20. McGraw-Hill New York, 1981.
			 */
			ITA_PROPAGATION_PATH_SIM_API void Euler( const VistaVector3D& r, const VistaVector3D& s, const double& dt, const ITAGeo::CStratifiedAtmosphere& atmosphere,
			                                         VistaVector3D& rNew, VistaVector3D& sNew );


			//! Solves the ordinary differential equations (ODEs) of ray propagation in a stratified medium using the classical Runge-Kutta method (RK4)
			/**
			 * @param[in,out] r Current wavefront position. Will be updated.
			 * @param[in,out] s Current slowness vector. Will be updated.
			 * @param[in] dt Time step for integration
			 * @param[in] atmosphere Stratified atmosphere
			 */
			ITA_PROPAGATION_PATH_SIM_API void RungeKutta( VistaVector3D& r, VistaVector3D& s, const double& dt, const ITAGeo::CStratifiedAtmosphere& atmosphere );


			//! Solves the ordinary differential equations (ODEs) of ray propagation in a stratified medium using the classical Runge-Kutta method (RK4)
			/**
			 * @param[in] r Current wavefront position.
			 * @param[in] s Current slowness vector.
			 * @param[in] dt Time step for integration
			 * @param[in] atmosphere Stratified atmosphere
			 * @param[out] rNew New wavefront position.
			 * @param[out] sNew New slowness vector.
			 *
			 * Literature for solver:
			 * W. H. Press, S. A. Teukolsky, W. T. Vetterling, and B. P. Flannery. Numerical recipes in C: The Art of Scientific Computing. Cambridge University Press,
			 * 2nd edition, 1992.
			 *
			 * The differential equations are taken from the slowness vector approach described in:
			 * A. D. Pierce. Acoustics: An Introduction to Its Physical Principles and Applications, volume 20. McGraw-Hill New York, 1981.
			 */
			ITA_PROPAGATION_PATH_SIM_API void RungeKutta( const VistaVector3D& r, const VistaVector3D& s, const double& dt,
			                                              const ITAGeo::CStratifiedAtmosphere& atmosphere, VistaVector3D& rNew, VistaVector3D& sNew );
		} // namespace ODESolver
	}     // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_ODESOLVER
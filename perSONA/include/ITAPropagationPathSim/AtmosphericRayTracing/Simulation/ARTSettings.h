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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_SETTINGS
#define IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_SETTINGS

#include <ITAPropagationPathSim/Definitions.h>

// ITA includes
#include <ITAPropagationPathSim/AtmosphericRayTracing/Rays.h>

// STD
#include <memory>

namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		namespace Simulation
		{
			class ITA_PROPAGATION_PATH_SIM_API IExternalWatcher
			{
			public:
				//! Returns true if the abort criterion for tracing the given ray is reached
				virtual bool AbortRequested( const std::shared_ptr<CRay> pRay ) const = 0;
				//! Allows additional proecssing of the ray at the end of each time step.
				virtual void ProcessRay( std::shared_ptr<CRay> ) const = 0;
				//! This is called after the tracing of a ray is finished.
				virtual void FinalizeRay( std::shared_ptr<CRay> ) const = 0;
			};
			class ITA_PROPAGATION_PATH_SIM_API CAbortAtMaxTime : public IExternalWatcher
			{
			private:
				double dTMax;

			public:
				inline CAbortAtMaxTime( double tMax = 30 ) : dTMax( tMax ) { };
				inline bool AbortRequested( const std::shared_ptr<CRay> pRay ) const { return pRay->LastTimeStamp( ) >= dTMax; };
				inline virtual void ProcessRay( std::shared_ptr<CRay> ) const { };
				inline virtual void FinalizeRay( std::shared_ptr<CRay> ) const { };
			};

			enum ITA_PROPAGATION_PATH_SIM_API SolverMethod
			{
				EULER = 0,  //!< Euler method
				RUNGE_KUTTA //!< Classical Runge_Kutta method (RK4)
			};


			struct ITA_PROPAGATION_PATH_SIM_API AdaptiveIntegrationSettings
			{
				bool bActive                     = true;  //!< If this is set to false, the adaptation is bypassed and the integration step size is therefore constant
				double dMaxError                 = 0.015; //!< For errors above this threshold the time step is decreased.
				double dUncriticalError          = 0.005; //!< An error below this limit allows to increase the time step again.
				unsigned int iMaxAdaptationLevel = 31;    //!< Maximum times, the time step is halfed. Maximum valid value = 31.
			};

			struct ITA_PROPAGATION_PATH_SIM_API Settings
			{
				SolverMethod solverMethod   = SolverMethod::RUNGE_KUTTA;
				double dIntegrationTimeStep = 0.1;  //!< Base step size for time integration
				bool bMultiThreading        = true; //!< If this is activated, tracing multiple rays in a single call is done using multi-threading
				AdaptiveIntegrationSettings adaptiveIntegration;
			};
		} // namespace Simulation
	}     // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_SIMULATION_SETTINGS
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

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_SETTINGS
#define IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_SETTINGS

#include <ITAPropagationPathSim/Definitions.h>


namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		namespace EigenraySearch
		{
			struct ITA_PROPAGATION_PATH_SIM_API RayAdaptationSettings
			{
				struct AbortSettings
				{
					int maxNAdaptations          = 30;    //!< Abort after N adaptations of the ray resolution
					double minAngleResolutionDeg = 0.001; //!< Abort if angle between neighboring rays is below this value [°]
				} abort;

				struct AccuracySettings
				{
					double maxReceiverRadius        = 1;    //!< Maximum radius of receiver sphere [m]
					double maxSourceReceiverAngle   = 1;    //!< Maximum angle between vectors from source to receiver point and receiver sphere [°]
					double maxAngleForGeomSpreading = 0.01; //!< Angular resolution of rays which is required to calculate spreading loss [°]
				} accuracy;

				struct AdvancedRayZoomingSettings
				{
					bool bActive     = false; //!< Switch to enable/disable advanced ray zooming
					double threshold = 0.1;   //!< Threshold between 0 and 2 above which advanced ray zooming is performed (0 = always, 2 = never)
				} advancedRayZooming;
			};
			struct ITA_PROPAGATION_PATH_SIM_API RayTracingAbortSettings
			{
				int maxReflectionOrder            = 1;    //!< Maximum considered order of reflections
				double maxTime                    = 30;   //!< Maximum propagation time of rays [s]
				bool bAbortOnReceiverDistIncrease = true; //!< If enabled, ray tracing will be aborted as soon as ray receiver distance increases
			};
			struct ITA_PROPAGATION_PATH_SIM_API Settings
			{
				RayTracingAbortSettings rayTracing;
				RayAdaptationSettings rayAdaptation;
			};
		} // namespace EigenraySearch
	}     // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_EIGENRAYSEARCH_SETTINGS
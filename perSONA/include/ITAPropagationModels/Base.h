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

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_BASE
#define INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_BASE

namespace ITAPropagationModels
{
	enum DiffractionModels
	{
		MAEKAWA_DETOUR_LAW = 1,
		UNIFORM_THEORY_OF_DIFFRACTION,
		BIOT_TOLSTOY_MEDWIN_SVENSSON,
	};
} // namespace ITAPropagationModels

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_BASE

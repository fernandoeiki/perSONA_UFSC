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

#ifndef INCLUDE_WATCHER_ITA_GEO_SCENE
#define INCLUDE_WATCHER_ITA_GEO_SCENE

// ITAGeo includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/ModelBase.h>

// STL includes
#include <string>
#include <vector>

namespace ITAGeo
{
	//! ITA scene with geometric data and acoustic entities
	/**
	 * A scene with acoustic sources, receivers and geometric
	 * model data for indoor and outdoor scenarios.
	 *
	 */
	class ITA_GEO_API CScene
	{
	public:
		CScene( );
		~CScene( );

		CModelBase* pGeoModel;                                           //!< Acoustic geometric data
		std::vector<std::shared_ptr<ITAGeo::CEmitter> > vpSoundEmitters; //!< Acoustic sound sources
		std::vector<std::shared_ptr<ITAGeo::CSensor> > vpSoundSensors;   //!< Acoustic sound receivers
	};

} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_SCENE

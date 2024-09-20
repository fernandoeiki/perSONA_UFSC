/*
 *  --------------------------------------------------------------------------------------------
 *
 *    VVV        VVV A           Virtual Acoustics (VA) | http://www.virtualacoustics.org
 *     VVV      VVV AAA          Licensed under the Apache License, Version 2.0
 *      VVV    VVV   AAA
 *       VVV  VVV     AAA        Copyright 2015-2018
 *        VVVVVV       AAA       Institute of Technical Acoustics (ITA)
 *         VVVV         AAA      RWTH Aachen University
 *
 *  --------------------------------------------------------------------------------------------
 */

#ifndef IW_VACORE_SOUNDSOURCEDESC
#define IW_VACORE_SOUNDSOURCEDESC

#include <VAPoolObject.h>
#include <VAAudioSignalSource.h>

#include <ITASampleBuffer.h>

#include <atomic>


//! This class describes a static unversioned sound source
class CVASoundSourceDesc : public CVAPoolObject
{
public:
	int iID;											//!< Identifier
	std::string sName;									//!< Verbose name (for debugging)
	std::atomic< bool > bMuted;								//!< Muting switch (jst: Berechnungen sollen trotzdem durchgeführt werden? bActive dazu?)
	std::atomic< bool > bEnabled;								//!< Enabled/disable from rendering
	std::atomic< bool > bInitPositionOrientation;				//!< Flag to indicate if a pose has been set, which is required for spatialisation
	IVAAudioSignalSource* pSignalSource;	//!< Assigned signal source pointer
	std::atomic< const ITASampleBuffer* > pSignalSourceInputBuf;	//!< Puffer der Eingangsdaten der Signalquelle
	float fSoundPower;
	std::string sExplicitRendererID;					//!< Explicit renderer for this sound source (empty = all)
	
	void PreRequest()
	{
		iID = -1;
		sName = "";
		bMuted = false;
		bInitPositionOrientation = false;
		pSignalSourceInputBuf = nullptr;
		pSignalSource = nullptr;
	}
};

#endif // IW_VACORE_SOUNDSOURCEDESC

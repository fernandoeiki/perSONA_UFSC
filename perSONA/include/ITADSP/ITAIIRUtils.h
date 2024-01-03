/*
 * ----------------------------------------------------------------
 *
 *		ITA core libs
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

#ifndef IW_ITA_IIR_UTILS
#define IW_ITA_IIR_UTILS

#include <ITADSPDefinitions.h>
#include <ITAIIRCoefficients.h>
#include <string>

namespace ITADSP
{
	void ITA_DSP_API ExportIIRCoefficientsToJSON( const std::string& sJSONFilePath, const CFilterCoefficients& oCoefficients );
}


#endif // IW_ITA_IIR_UTILS

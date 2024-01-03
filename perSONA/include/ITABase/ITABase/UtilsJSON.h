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

#ifndef IW_ITA_BASE_UTILS_JSON
#define IW_ITA_BASE_UTILS_JSON

#include <ITABase/ITAStatistics.h>
#include <ITABaseDefinitions.h>
#include <ITASpectrum.h>
#include <string>

namespace ITABase
{
	namespace Utils
	{
		namespace JSON
		{
			//! Export a spectrum to JSON fromatted text file
			/**
			 * @param[in] oSpectrum Spectrum
			 * @param[in] sTargetFilePath Target file path
			 */
			ITA_BASE_API void Export( const CITASpectrum* pSpectrum, const std::string& sTargetFilePath );
			ITA_BASE_API void Export( const CStatistics& oStats, const std::string& sTargetFilePath );
			ITA_BASE_API void Export( const std::vector<CStatistics>& voStats, const std::string& sTargetFilePath );
		} // namespace JSON
	}     // namespace Utils
} // namespace ITABase

#endif // IW_ITA_BASE_UTILS_JSON

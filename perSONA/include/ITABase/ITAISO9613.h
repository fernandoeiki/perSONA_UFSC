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

#ifndef INCLUDE_WATCHER_ITA_ISO_9613
#define INCLUDE_WATCHER_ITA_ISO_9613

// ITABase
#include <ITABaseDefinitions.h>
#include <ITAThirdOctaveMagnitudeSpectrum.h>
#include <string>

namespace ITABase
{
	namespace ISO9613
	{
		//! Calculates the atmospheric absorption after ISO 9613-1 for one frequency in decibels
		/**
		 * Standard: ISO 9613-1:1993
		 *
		 * \param dFrequency Base frequency [Hz]
		 * \param fDistance Distance [m]
		 * \param fTemperature Temperature [°C]
		 * \param fHumidity Relative humidity [%]
		 * \param fStaticPressure Static air pressure [kPa]
		 *
		 * @return Atmospheric absorption in dB
		 */
		ITA_BASE_API double AtmosphericAbsorptionLevel( double dFrequency, double dDistance, double dTemperature, double dHumidity, double dStaticPressure = 101.325 );

		//! Calculates the atmospheric absorption after ISO 9613-1 for one frequency in linear factors (instead of decibels)
		/**
		 * Standard: ISO 9613-1:1993
		 *
		 * \param dFrequency Base frequency [Hz]
		 * \param fDistance Distance [m]
		 * \param fTemperature Temperature [°C]
		 * \param fHumidity Relative humidity [%]
		 * \param fStaticPressure Static air pressure [kPa]
		 *
		 * @return Atmospheric absorption in linear factors (instead of decibels)
		 */
		ITA_BASE_API double AtmosphericAbsorptionFactor( double dFrequency, double dDistance, double dTemperature, double dHumidity, double dStaticPressure = 101.325 );

		//! Calculates the atmospheric absorption after ISO 9613-1: A_{atm} (formula 8) in decibels
		/**
		 * Standard: ISO 9613-1:1993
		 *
		 * \param oA_atm_dB Third-octave magnitude spectrum with atmospheric attenuation values in decibel
		 * \param fDistance Distance [m]
		 * \param fTemperature Temperature [°C]
		 * \param fHumidity Relative humidity [%]
		 * \param fStaticPressure Static air pressure [kPa]
		 */
		ITA_BASE_API void AtmosphericAbsorption( ITABase::CThirdOctaveDecibelMagnitudeSpectrum& oA_atm_dB, double dDistance, double dTemperature, double dHumidity,
		                                         double dStaticPressure = 101.325 );

		//! Calculates the atmospheric absorption in linear factors (instead of decibels)
		ITA_BASE_API void AtmosphericAbsorption( ITABase::CThirdOctaveFactorMagnitudeSpectrum& oA_atm_factor, double dDistance, double dTemperature, double dHumidity,
		                                         double dStaticPressure = 101.325 );

	} // namespace ISO9613
} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_ISO_9613

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

#ifndef IW_ITA_GEO_UTILS_JSON_ATMOSPHERE
#define IW_ITA_GEO_UTILS_JSON_ATMOSPHERE

#include <ITAGeo/Atmosphere/StratifiedAtmosphere.h>
#include <ITAGeo/Definitions.h>
#include <memory>
#include <sstream>
#include <string>

namespace ITAGeo
{
	namespace Utils
	{
		namespace JSON
		{
			//---STARTIFIED ATMOSPHERE EXPORT/IMPORT/ENCODING/DECODING---

			//! Export a stratified atmosphere to JSON formatted text file
			ITA_GEO_API void Export( const CStratifiedAtmosphere& cAtmosphere, const std::string& sTargetFilePath, bool bOverwrite = false );
			//! Import a stratified atmosphere from JSON formatted text file
			ITA_GEO_API void Import( CStratifiedAtmosphere& cAtmosphere, const std::string& sFilePath );

			//! Create JSON formatted string from given stratified atmosphere
			ITA_GEO_API std::stringstream Encode( const CStratifiedAtmosphere& cAtmosphere );
			//! Parse properties from JSON formatted string to given stratified atmosphere
			ITA_GEO_API void Decode( CStratifiedAtmosphere& cAtmosphere, const std::string& sContent );

			//---WEATHER PROFILE FACTORY FUNCTIONS---

			//! Create JSON formatted string from given humidity profile interface
			ITA_GEO_API std::stringstream FromHumidityProfile( const HumidityProfiles::IHumidityProfile& iProfile );
			//! Factory function for humidity profiles based on a JSON formatted string
			ITA_GEO_API std::shared_ptr<HumidityProfiles::IHumidityProfile> ToHumidityProfile( const std::string& sContent );
			//! Create JSON formatted string from given temperature profile interface
			ITA_GEO_API std::stringstream FromTemperatureProfile( const TemperatureProfiles::ITemperatureProfile& iProfile );
			//! Factory function for temperature profiles based on a JSON formatted string
			ITA_GEO_API std::shared_ptr<TemperatureProfiles::ITemperatureProfile> ToTemperatureProfile( const std::string& sContent );
			//! Create JSON formatted string from given wind profile interface
			ITA_GEO_API std::stringstream FromWindProfile( const WindProfiles::IWindProfile& );
			//! Factory function for wind profiles based on a JSON formatted string
			ITA_GEO_API std::shared_ptr<WindProfiles::IWindProfile> ToWindProfile( const std::string& sContent );


			//---WEATHER PROFILE ENCODING/DECODING---

			//! Create JSON formatted string from given weather profile interface
			/**
			 *   Stores the basic data (type and class) for all weather profiles and should be called by all other weather profile Encode() functions.
			 *   A weather profile with no additional members needs no additional Encode() function.
			 */
			ITA_GEO_API std::stringstream Encode( const WeatherProfileBase::IWeatherProfile& iProfile );
			//! Parse properties from JSON formatted string to given given weather profile interface
			/**
			 *   Parses the basic data (type and class) for all weather profiles and should be called by all other weather profile Decode() functions.
			 *   A weather profile with no additional members needs no additional Decode() function.
			 */
			ITA_GEO_API void Decode( const WeatherProfileBase::IWeatherProfile& iProfile, const std::string& sContent );

			//! Create JSON formatted string from given constant humidity profile
			ITA_GEO_API std::stringstream Encode( const HumidityProfiles::CConstant& iProfile );
			//! Parse properties from JSON formatted string to given constant humidity profile
			ITA_GEO_API void Decode( HumidityProfiles::CConstant& iProfile, const std::string& sContent );
			//! Create JSON formatted string from given imported humidity profile
			ITA_GEO_API std::stringstream Encode( const HumidityProfiles::CImport& iProfile );
			//! Parse properties from JSON formatted string to given imported humidity profile
			ITA_GEO_API void Decode( HumidityProfiles::CImport& iProfile, const std::string& sContent );

			//! Create JSON formatted string from given constant temperature profile
			ITA_GEO_API std::stringstream Encode( const TemperatureProfiles::CConstant& iProfile );
			//! Parse properties from JSON formatted string to given constant temperature profile
			ITA_GEO_API void Decode( TemperatureProfiles::CConstant& iProfile, const std::string& sContent );
			//! Create JSON formatted string from given imported temperature profile
			ITA_GEO_API std::stringstream Encode( const TemperatureProfiles::CImport& iProfile );
			//! Parse properties from JSON formatted string to given imported temperature profile
			ITA_GEO_API void Decode( TemperatureProfiles::CImport& iProfile, const std::string& sContent );

			//! Create JSON formatted string from given constant wind profile
			ITA_GEO_API std::stringstream Encode( const WindProfiles::CConstant& iProfile );
			//! Parse properties from JSON formatted string to given constant wind profile
			ITA_GEO_API void Decode( WindProfiles::CConstant& iProfile, const std::string& sContent );
			//! Create JSON formatted string from given logarithmic wind profile
			ITA_GEO_API std::stringstream Encode( const WindProfiles::CLog& iProfile );
			//! Parse properties from JSON formatted string to given logarithmic wind profile
			ITA_GEO_API void Decode( WindProfiles::CLog& iProfile, const std::string& sContent );
			//! Create JSON formatted string from given imported wind profile
			ITA_GEO_API std::stringstream Encode( const WindProfiles::CImport& iProfile );
			//! Parse properties from JSON formatted string to given imported wind profile
			ITA_GEO_API void Decode( WindProfiles::CImport& iProfile, const std::string& sContent );
		} // namespace JSON
	}     // namespace Utils
} // namespace ITAGeo

#endif // IW_ITA_GEO_UTILS_JSON_ATMOSPHERE

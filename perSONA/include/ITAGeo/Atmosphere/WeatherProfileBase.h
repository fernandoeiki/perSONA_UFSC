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

#ifndef INCLUDE_WATCHER_ITA_GEO_WEATHERPROFILEBASE
#define INCLUDE_WATCHER_ITA_GEO_WEATHERPROFILEBASE

#include <ITAGeo/Definitions.h>
#include <VistaBase/VistaVector3D.h>

// ITABase includes
#include <ITAException.h>

// STL includes
#include <sstream>


// Helper Makros
#define ITA_HUMIDITY_PROFILE_STR    ITAGeo::WeatherProfileBase::IWeatherProfile::GetProfileTypeStr( ITAGeo::WeatherProfileBase::EProfileType::HUMIDITY )
#define ITA_TEMPERATURE_PROFILE_STR ITAGeo::WeatherProfileBase::IWeatherProfile::GetProfileTypeStr( ITAGeo::WeatherProfileBase::EProfileType::TEMPERATURE )
#define ITA_WIND_PROFILE_STR        ITAGeo::WeatherProfileBase::IWeatherProfile::GetProfileTypeStr( ITAGeo::WeatherProfileBase::EProfileType::WIND )

namespace ITAGeo
{
	namespace WeatherProfileBase
	{
		enum EProfileType
		{
			INVALID_PROFILE = -1,
			HUMIDITY        = 0,
			TEMPERATURE,
			WIND,

			NUM_PROFILE_TYPES //!< Last element of EClassType to iterate over EClassType
		};

		enum EClassType
		{
			INVALID_PROFILE_CLASS = -1,
			CONSTANT              = 0,
			IMPORT,
			ROOM,
			ISA,
			ZERO,
			LOG,

			NUM_PROFILE_CLASS_TYPES //!< Last element of EClassType to iterate over EClassType
		};

		//! Base class for all weather profile interfaces
		/**
		 *	Implements many JSON related functions and introduces enums for the different class types.
		 */
		class ITA_GEO_API IWeatherProfile
		{
		public:
			const EProfileType iProfileType; //! Type of weather profile
			const EClassType iClassType;     //! Type of weather profile class

		protected:
			inline IWeatherProfile( const EProfileType& iType, const EClassType& iClassType ) : iProfileType( iType ), iClassType( iClassType ) {}

		public:
			IWeatherProfile& operator=( const IWeatherProfile& oOther ) = delete;

		public:
			static inline std::string GetProfileTypeStr( const EProfileType& iType )
			{
				switch( iType )
				{
					case EProfileType::HUMIDITY:
						return "humidity_profile";
					case EProfileType::TEMPERATURE:
						return "temperature_profile";
					case EProfileType::WIND:
						return "wind_profile";
					default:
						return "Unknown";
				}
			}
			inline std::string GetProfileTypeStr( ) const { return GetProfileTypeStr( iProfileType ); }

			static inline std::string GetProfileClassStr( const EClassType& iType )
			{
				switch( iType )
				{
					case EClassType::CONSTANT:
						return "constant";
					case EClassType::IMPORT:
						return "import";
					case EClassType::ROOM:
						return "room";
					case EClassType::ISA:
						return "isa";
					case EClassType::ZERO:
						return "zero";
					case EClassType::LOG:
						return "log";
					default:
						return "Unknown";
				}
			}
			inline std::string GetProfileClassStr( ) const { return GetProfileClassStr( iClassType ); }

			inline static EProfileType ParseProfileType( const std::string& sTypeStr )
			{
				for( size_t i = 0; i < EProfileType::NUM_PROFILE_TYPES; i++ )
				{
					if( sTypeStr == GetProfileTypeStr( (EProfileType)i ) )
					{
						return (EProfileType)i;
					}
				}

				return EProfileType::INVALID_PROFILE;
			}
			inline static EClassType ParseProfileClassType( const std::string& sTypeStr )
			{
				for( size_t i = 0; i < EClassType::NUM_PROFILE_CLASS_TYPES; i++ )
				{
					if( sTypeStr == GetProfileClassStr( (EClassType)i ) )
					{
						return (EClassType)i;
					}
				}

				return EClassType::INVALID_PROFILE_CLASS;
			}
		};
	} // namespace WeatherProfileBase
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_WEATHERPROFILEBASE
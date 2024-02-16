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

#ifndef INCLUDE_WATCHER_ITA_GEO_TEMPERATUREPROFILES
#define INCLUDE_WATCHER_ITA_GEO_TEMPERATUREPROFILES

#include <ITAGeo/Atmosphere/WeatherProfileBase.h>
#include <ITAGeo/Definitions.h>
//#include <ITAGeo/Base.h>

// ITA
#include <ITABase/Math/PiecewisePolynomial.h>

// STL includes
#include <sstream>
#include <vector>

// ---Forward Declarations---
// ---for friend functions---
namespace ITAGeo
{
	namespace TemperatureProfiles
	{
		class CConstant;
		class CImport;
	} // namespace TemperatureProfiles
} // namespace ITAGeo
namespace ITAGeo
{
	namespace Utils
	{
		namespace JSON
		{
			ITA_GEO_API std::stringstream Encode( const TemperatureProfiles::CConstant& );
			ITA_GEO_API std::stringstream Encode( const TemperatureProfiles::CImport& );
			ITA_GEO_API void Decode( TemperatureProfiles::CConstant& iProfile, const std::string& sContent );
			ITA_GEO_API void Decode( TemperatureProfiles::CImport& iProfile, const std::string& sContent );
		} // namespace JSON
	}     // namespace Utils
};        // namespace ITAGeo
namespace ITAGeo
{
	namespace TemperatureProfiles
	{
		//! Interface to altitude-dependent temperature / static pressure profiles
		class ITA_GEO_API ITemperatureProfile : public ITAGeo::WeatherProfileBase::IWeatherProfile
		{
		public:
			inline ITemperatureProfile( const WeatherProfileBase::EClassType& classType )
			    : WeatherProfileBase::IWeatherProfile( WeatherProfileBase::EProfileType::TEMPERATURE, classType ) { };

			const ITemperatureProfile& operator=( const ITemperatureProfile& oOther ) = delete;

			//! Returns the static pressure [Pa] at a given altitude
			virtual double StaticPressure( const double& altitude ) const = 0;
			//! Returns the temperature [K] at a given altitude
			virtual double Temperature( const double& altitude ) const = 0;
			//! Returns the gradient (d/dz) of the temperature [K/m] at a given altitude
			virtual double TemperatureGradient( const double& altitude ) const = 0;
		};

		//! Profile with altitude-independent (constant) temperature and static pressure
		class ITA_GEO_API CConstant : public ITemperatureProfile
		{
		public:
			CConstant( const double& constTemperature, const double& staticPressure );
			CConstant( const CConstant& oOther );
			inline ~CConstant( ) { };

			CConstant& operator=( const CConstant& oOther );


		public:
			virtual double StaticPressure( const double& altitude ) const;
			virtual double Temperature( const double& altitude ) const;
			virtual double TemperatureGradient( const double& altitude ) const;

			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend std::stringstream ITAGeo::Utils::JSON::Encode( const TemperatureProfiles::CConstant& );
			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend void ITAGeo::Utils::JSON::Decode( TemperatureProfiles::CConstant& iProfile, const std::string& sContent );

		protected:
			double m_staticPressure; //[Pa]
			double m_temperature;    //[K]
		};

		//! A profile that uses a typical temperature (20°C) and static pressure (101325 Pa) for rooms along all altitudes
		class ITA_GEO_API CRoom : public ITemperatureProfile
		{
		public:
			inline CRoom( ) : ITemperatureProfile( WeatherProfileBase::EClassType::ROOM ) { };
			inline CRoom( const CRoom& ) : ITemperatureProfile( WeatherProfileBase::EClassType::ROOM ) { };
			inline ~CRoom( ) { };

			inline CRoom& operator=( const CRoom& ) { return *this; };

			virtual double StaticPressure( const double& altitude ) const;
			virtual double Temperature( const double& altitude ) const;
			virtual double TemperatureGradient( const double& altitude ) const;
		};

		//! Temperature and static pressure defined according to International Standard Atmosphere (ISA)
		/**
		 * N. Sissenwine, M. Dubin, and H. Wexler. The US standard atmosphere, 1962. Journal of Geophysical Research, 67(9):3627–3630, 1962.
		 */
		class ITA_GEO_API CISA : public ITemperatureProfile
		{
		public:
			inline CISA( ) : ITemperatureProfile( WeatherProfileBase::EClassType::ISA ) { };
			inline CISA( const CISA& ) : ITemperatureProfile( WeatherProfileBase::EClassType::ISA ) { };
			inline ~CISA( ) { };

			inline CISA& operator=( const CISA& ) { return *this; };

		public:
			double StaticPressure( const double& altitude ) const;
			double Temperature( const double& altitude ) const;
			double TemperatureGradient( const double& altitude ) const;
		};

		//! Imported temperature and static pressure using piecewise polynomials calculated from a cubic spline interpolation
		class ITA_GEO_API CImport : public ITemperatureProfile
		{
		public:
			//! Creates an imported profile initialized with dummy values
			CImport( );
			//! Creates an imported profile using giving altitude and data values
			CImport( const std::vector<double>& vdAltitude, const std::vector<double>& vdTemperature, const std::vector<double>& vdStaticPressure );

			CImport& operator=( const CImport& );

		public:
			double StaticPressure( const double& altitude ) const;
			double Temperature( const double& altitude ) const;
			double TemperatureGradient( const double& altitude ) const;

			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend std::stringstream ITAGeo::Utils::JSON::Encode( const TemperatureProfiles::CImport& );
			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend void ITAGeo::Utils::JSON::Decode( TemperatureProfiles::CImport& iProfile, const std::string& sContent );

		private:
			std::vector<double> m_vdAltitude;       //!< Raw altitude data: Supporting points for piecewise polynomial
			std::vector<double> m_vdTemperature;    //!< Raw temperature data
			std::vector<double> m_vdStaticPressure; //!< Raw static pressure data

			ITABase::Math::CPiecewisePolynomial m_polynomialStaticPressure;      //!< Piecewise polynomial with static pressure data
			ITABase::Math::CPiecewisePolynomial m_polynomialTemperature;         //!< Piecewise polynomial with temperature data
			ITABase::Math::CPiecewisePolynomial m_polynomialTemperatureGradient; //!< Piecewise polynomial with data of temperature gradient
		};
	} // namespace TemperatureProfiles
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_TEMPERATUREPROFILES

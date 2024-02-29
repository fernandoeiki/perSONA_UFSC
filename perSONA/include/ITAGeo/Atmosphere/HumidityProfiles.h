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

#ifndef INCLUDE_WATCHER_ITA_GEO_HUMIDITYPROFILES
#define INCLUDE_WATCHER_ITA_GEO_HUMIDITYPROFILES

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
	namespace HumidityProfiles
	{
		class CConstant;
		class CImport;
	} // namespace HumidityProfiles
} // namespace ITAGeo
namespace ITAGeo
{
	namespace Utils
	{
		namespace JSON
		{
			ITA_GEO_API std::stringstream Encode( const HumidityProfiles::CConstant& );
			ITA_GEO_API std::stringstream Encode( const HumidityProfiles::CImport& );
			ITA_GEO_API void Decode( HumidityProfiles::CConstant& iProfile, const std::string& sContent );
			ITA_GEO_API void Decode( HumidityProfiles::CImport& iProfile, const std::string& sContent );
		} // namespace JSON
	}     // namespace Utils
};        // namespace ITAGeo

namespace ITAGeo
{
	namespace HumidityProfiles
	{
		//! Interface to altitidude dependent humidity profiles
		class ITA_GEO_API IHumidityProfile : public WeatherProfileBase::IWeatherProfile
		{
		public:
			inline IHumidityProfile( const WeatherProfileBase::EClassType& classType )
			    : WeatherProfileBase::IWeatherProfile( WeatherProfileBase::EProfileType::HUMIDITY, classType ) { };

			IHumidityProfile& operator=( const IHumidityProfile& oOther ) = delete;

			//! Returns the relative humidity [%] at a given altitude
			virtual double RelativeHumidity( const double& altitude ) const = 0;
		};

		//! Profile with altitude-independent (constant) relative humidity
		class ITA_GEO_API CConstant : public IHumidityProfile
		{
		public:
			CConstant( const double& relativeHumidityPerc = 50.0 );
			//! Copy constructor
			CConstant( const CConstant& oOther );
			inline ~CConstant( ) { };

			CConstant& operator=( const CConstant& oOther );


		public:
			double RelativeHumidity( const double& altitude ) const;

			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend std::stringstream ITAGeo::Utils::JSON::Encode( const HumidityProfiles::CConstant& );
			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend void ITAGeo::Utils::JSON::Decode( HumidityProfiles::CConstant& iProfile, const std::string& sContent );

		protected:
			double m_relativeHumidity; //[%]
		};

		//! Imported relative humidity using piecewise polynomials calculated from a cubic spline interpolation
		class ITA_GEO_API CImport : public IHumidityProfile
		{
		public:
			//! Creates an imported profile initialized with dummy values
			CImport( );
			//! Creates an imported profile using giving altitude and data values
			CImport( const std::vector<double>& vdAltitude, const std::vector<double>& vdHumidity );

			CImport& operator=( const CImport& oOther );

		public:
			double RelativeHumidity( const double& altitude ) const;

			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend std::stringstream ITAGeo::Utils::JSON::Encode( const HumidityProfiles::CImport& );
			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend void ITAGeo::Utils::JSON::Decode( HumidityProfiles::CImport& iProfile, const std::string& sContent );

		private:
			std::vector<double> m_vdAltitude; //!< Raw altitude data: Supporting points for piecewise polynomial
			std::vector<double> m_vdHumidity; //!< Raw humidity data

			ITABase::Math::CPiecewisePolynomial m_polynomialRelativeHumidity; //!< Piecewise polynomial with humidity data
		};
	} // namespace HumidityProfiles
} // namespace ITAGeo
#endif // INCLUDE_WATCHER_ITA_GEO_HUMIDITYPROFILES

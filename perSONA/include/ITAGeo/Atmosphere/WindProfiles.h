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

#ifndef INCLUDE_WATCHER_ITA_GEO_WINDPROFILES
#define INCLUDE_WATCHER_ITA_GEO_WINDPROFILES

#include <ITAGeo/Atmosphere/WeatherProfileBase.h>
#include <ITAGeo/Definitions.h>

// ITA
#include <ITABase/Math/PiecewisePolynomial.h>

// STD
#include <vector>

// Vista includes
#include <VistaBase/VistaVector3D.h>


// ---Forward Declarations---
// ---for friend functions---
namespace ITAGeo
{
	namespace WindProfiles
	{
		class CConstant;
		class CLog;
		class CImport;
	} // namespace WindProfiles
} // namespace ITAGeo
namespace ITAGeo
{
	namespace Utils
	{
		namespace JSON
		{
			ITA_GEO_API std::stringstream Encode( const WindProfiles::CConstant& );
			ITA_GEO_API std::stringstream Encode( const WindProfiles::CLog& );
			ITA_GEO_API std::stringstream Encode( const WindProfiles::CImport& );
			ITA_GEO_API void Decode( WindProfiles::CConstant& iProfile, const std::string& sContent );
			ITA_GEO_API void Decode( WindProfiles::CLog& iProfile, const std::string& sContent );
			ITA_GEO_API void Decode( WindProfiles::CImport& iProfile, const std::string& sContent );
		} // namespace JSON
	}     // namespace Utils
};        // namespace ITAGeo

namespace ITAGeo
{
	namespace WindProfiles
	{
		//! Interface to altitude-dependent wind profiles
		/**
		 * Wind direction according to East-North-Up (ENU) system: X = East, Y = North, Z = Up.
		 */
		class ITA_GEO_API IWindProfile : public ITAGeo::WeatherProfileBase::IWeatherProfile
		{
		public:
			inline IWindProfile( const WeatherProfileBase::EClassType& classType )
			    : WeatherProfileBase::IWeatherProfile( WeatherProfileBase::EProfileType::WIND, classType ) { };
			virtual inline ~IWindProfile( ) { };

			IWindProfile& operator=( const IWindProfile& oOther ) = delete;

			//! Returns the 3D wind vector [m/s] at a given altitude
			virtual VistaVector3D WindVector( const double& altitude ) const = 0;
			//! Returns the gradient (d/dz) of the wind vector [1/s] at a given altitude
			virtual VistaVector3D WindVectorGradient( const double& altitude ) const = 0;
		};

		//! A wind profile with an altitude-independent wind velocity and direction
		class ITA_GEO_API CConstant : public IWindProfile
		{
		public:
			CConstant( const double&, const VistaVector3D& );
			//! Copy constructor
			CConstant( const CConstant& oOther );
			inline ~CConstant( ) { };

			CConstant& operator=( const CConstant& oOther );

		public:
			virtual VistaVector3D WindVector( const double& altitude ) const;
			virtual VistaVector3D WindVectorGradient( const double& altitude ) const;

			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend std::stringstream ITAGeo::Utils::JSON::Encode( const WindProfiles::CConstant& );
			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend void ITAGeo::Utils::JSON::Decode( WindProfiles::CConstant& iProfile, const std::string& sContent );

		protected:
			VistaVector3D m_windVector; //[m/s]
		};

		//! A wind profile without medium movement (no wind at all)
		class ITA_GEO_API CZero : public IWindProfile
		{
		public:
			CZero( );
			//! Copy constructor
			CZero( const CZero& );
			inline ~CZero( ) { };

			inline CZero& operator=( const CZero& ) { return *this; };

		public:
			virtual VistaVector3D WindVector( const double& altitude ) const;
			virtual VistaVector3D WindVectorGradient( const double& altitude ) const;
		};


		//! Logarithmic wind profile used in meteorology
		/**
		 * H. Kraus. Grundlagen der Grenzschicht-Meteorologie: Einführung in die Physik der Atmosphärischen Grenzschicht und in die Mikrometeorologie. Springer-Verlag,
		 * 2008.
		 */
		class ITA_GEO_API CLog : public IWindProfile
		{
		public:
			CLog( const double&, const double&, const VistaVector3D& );
			//! Copy constructor
			CLog( const CLog& oOther );
			inline ~CLog( ) { };

			CLog& operator=( const CLog& other );

		public:
			virtual VistaVector3D WindVector( const double& altitude ) const;
			virtual VistaVector3D WindVectorGradient( const double& altitude ) const;

			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend std::stringstream ITAGeo::Utils::JSON::Encode( const WindProfiles::CLog& );
			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend void ITAGeo::Utils::JSON::Decode( WindProfiles::CLog& iProfile, const std::string& sContent );

		private:
			const double c_karmanConstant = 0.4; // kappa []
			// double m_frictionVelocity; //v_* [m/s]
			double m_velocityPrefactor; //=frictionVelocity / karmanConstant

			double m_surfaceRoughness; // z0 [m]
			VistaVector3D m_windDirection;
		};

		//! Imported wind profile using piecewise polynomials calculated from multiple cubic spline interpolations
		class ITA_GEO_API CImport : public IWindProfile
		{
		public:
			//! Creates an imported profile initialized with dummy values
			CImport( );
			//! Creates piecewise polynomials for x and y component of the windvector using altitude-depenent wind velocity and wind direction angle
			/**
			 * Note, that azimuth angle is defined as 0° = wind from north, 90° = wind from east.
			 * The convention for the resulting data is that x = wind towards east, y = wind towards north (East-North-Up system).
			 */
			CImport( const std::vector<double>& vdAltitude, const std::vector<double>& vdWindVelocity, const std::vector<double>& vdWindAzimuthDeg );
			//! Creates piecewise polynomials for x and y component of the windvector using altitude-depenent wind velocity and wind direction x- and y-component
			CImport( const std::vector<double>& vdAltitude, const std::vector<double>& vdWindVelocity, const std::vector<double>& vdWindDirX,
			         const std::vector<double>& vdWindDirY );

			CImport& operator=( const CImport& other );

		public:
			virtual VistaVector3D WindVector( const double& altitude ) const;
			virtual VistaVector3D WindVectorGradient( const double& altitude ) const;

			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend std::stringstream ITAGeo::Utils::JSON::Encode( const WindProfiles::CImport& );
			//! Defined in ITAGeo/Utils/JSON/Atmosphere.h
			friend void ITAGeo::Utils::JSON::Decode( WindProfiles::CImport& iProfile, const std::string& sContent );

		private:
			std::vector<double> m_vdAltitude;       //!< Raw altitude data: Supporting points for piecewise polynomial
			std::vector<double> m_vdWindVelocity;   //!< Raw wind velocity data
			std::vector<double> m_vdWindDirectionX; //!< Raw wind direction x-component
			std::vector<double> m_vdWindDirectionY; //!< Raw wind direction y-component

			ITABase::Math::CPiecewisePolynomial m_polynomialWindX;
			ITABase::Math::CPiecewisePolynomial m_polynomialWindY;

			ITABase::Math::CPiecewisePolynomial m_polynomialWindGradientX;
			ITABase::Math::CPiecewisePolynomial m_polynomialWindGradientY;
		};
	} // namespace WindProfiles
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_WINDPROFILES

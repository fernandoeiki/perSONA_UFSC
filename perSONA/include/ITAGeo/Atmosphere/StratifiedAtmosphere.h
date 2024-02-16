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

#ifndef INCLUDE_WATCHER_ITA_GEO_STRATIFIED_ATMOSPHERE
#define INCLUDE_WATCHER_ITA_GEO_STRATIFIED_ATMOSPHERE

#include <ITAGeo/Atmosphere/HumidityProfiles.h>
#include <ITAGeo/Atmosphere/TemperatureProfiles.h>
#include <ITAGeo/Atmosphere/WindProfiles.h>
#include <ITAGeo/Definitions.h>
//#include <ITAGeo/Base.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// STL includes
#include <memory>
#include <sstream>


namespace ITAGeo
{
	//! Class representing a stratified atmosphere
	/**
	 * A stratified atmosphere combines multiple height-dependent weather parameters. The following parameters are stored using separate profiles
	 * - temperature (plus gradient) and static pressure
	 * - wind (plus gradient)
	 * - humidity
	 *
	 * Note, that for the wind direction the East-North-Up (ENU) coordinate system is used.
	 */
	class ITA_GEO_API CStratifiedAtmosphere
	{
	public:
		CStratifiedAtmosphere( );
		CStratifiedAtmosphere( std::shared_ptr<TemperatureProfiles::ITemperatureProfile>, std::shared_ptr<WindProfiles::IWindProfile>,
		                       std::shared_ptr<HumidityProfiles::IHumidityProfile> humidity );

		// Set and Get
	public:
		inline const std::shared_ptr<HumidityProfiles::IHumidityProfile> HumidityProfile( ) const { return pHumidityProfile; };
		inline const std::shared_ptr<TemperatureProfiles::ITemperatureProfile> TemperatureProfile( ) const { return pTemperatureProfile; };
		inline const std::shared_ptr<WindProfiles::IWindProfile> WindProfile( ) const { return pWindProfile; };

		inline void SetHumidityProfile( std::shared_ptr<HumidityProfiles::IHumidityProfile> pProfile ) { pHumidityProfile = pProfile; };
		inline void SetTemperatureProfile( std::shared_ptr<TemperatureProfiles::ITemperatureProfile> pProfile ) { pTemperatureProfile = pProfile; };
		inline void SetWindProfile( std::shared_ptr<WindProfiles::IWindProfile> pProfile ) { pWindProfile = pProfile; };

	public:
		double RelativeHumidity( double altitude ) const;

		double StaticPressure( double altitude ) const;
		double Temperature( double altitude ) const;
		double TemperatureGradient( double altitude ) const;

		//! Returns the speed of sound at a given altitude
		/**
		 *	M. A. Garc´es, R. A. Hansen, and K. G. Lindquist. Traveltimes for infrasonic waves propagating in a stratified atmosphere. Geophysical Journal International,
		 *135(1) : 255–263, 1998.
		 *
		 *	An equation including the influence of humidity can be found here:
		 *	Vladimir E. Ostashev and D. Keith Wilson. Acoustics in Moving Inhomogeneous Media. CRC Press, second edition, 2016.
		 *	See eq. (1.1).
		 */
		double SpeedOfSound( double altitude ) const;
		//! Returns the speed of sound gradient (d/dz) at a given altitude
		double SpeedOfSoundGradient( double altitude ) const;

		VistaVector3D WindVector( double altitude ) const;
		VistaVector3D WindVectorGradient( double altitude ) const;

	protected:
		//! Constant used in speed of sound formula [m ^ 2 / (s ^ 2 K)]
		/**
		 *	Multiplication of ratio of specific heats (= 1.4) and gas constant of air ( = 287.058 [m^2 / (s^2 K)])
		 *	Vladimir E. Ostashev and D. Keith Wilson. Acoustics in Moving Inhomogeneous Media. CRC Press, second edition, 2016.
		 *	See eq. (1.1).
		 */
		const double airGasConstant_times_ratioSpecificHeats = 1.4 * 287.058;

		std::shared_ptr<HumidityProfiles::IHumidityProfile> pHumidityProfile;
		std::shared_ptr<TemperatureProfiles::ITemperatureProfile> pTemperatureProfile;
		std::shared_ptr<WindProfiles::IWindProfile> pWindProfile;
	};
} // namespace ITAGeo

#endif // INCLUDE_WATCHER_ITA_GEO_STRATIFIED_ATMOSPHERE

/*
 * ----------------------------------------------------------------
 *
 *		ITA core libs
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 *				    ____  __________  _______
 * 				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 * 				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 *  ----------------------------------------------------------------
 *
 */

#ifndef INCLUDE_WATCHER_ITA_CONSTANTS
#define INCLUDE_WATCHER_ITA_CONSTANTS

// ITABase
#include <ITABaseDefinitions.h>

// STL
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

namespace ITAConstants
{
	// Pi constants (float)
	static float HALF_PI_F = std::acos( 0.0f );
	static float PI_F      = std::acos( -1.0f );
	static float TWO_PI_F  = 2 * std::acos( -1.0f );

	// Pi constants (double)
	static double HALF_PI_D = std::acos( 0.0 );
	static double PI_D      = std::acos( -1.0 );
	static double TWO_PI_D  = 2 * std::acos( -1.0 );

	// Pi constants (literals, float)
	static float PI_F_L      = 3.14159265358979323846264338327950288419716939937510f;
	static float TWO_PI_F_L  = 6.283185307179586476925286766559f;
	static float HALF_PI_F_L = 1.5707963267948966192313216916397514f;

	// Pi constants (literals, double)
	static double PI_D_L      = 3.14159265358979323846264338327950288419716939937510f;
	static double TWO_PI_D_L  = 6.283185307179586476925286766559f;
	static double HALF_PI_D_L = 1.5707963267948966192313216916397514f;

	// Epsilon (distance quantization)
	static float EPS_F_L  = 1.0e-5f; // 10 micro meter
	static double EPS_D_L = 1.0e-5f; // 10 micro meter

	// Log-scale limits
	static float INFINITY_F        = std::numeric_limits<float>::infinity( );
	static float MINUS_INFINITY_F  = -std::numeric_limits<float>::infinity( );
	static double INFINITY_D       = std::numeric_limits<double>::infinity( );
	static double MINUS_INFINITY_D = -std::numeric_limits<double>::infinity( );

	static std::vector<float> THIRD_OCTAVE_CENTER_FREQUENCIES_ISO_F  = { 20,  25,   31.5f, 40,   50,   63,   80,   100,  125,  160,  200,  250,   315,   400,   500,  630,
                                                                        800, 1000, 1250,  1600, 2000, 2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000 };
	static std::vector<double> THIRD_OCTAVE_CENTER_FREQUENCIES_ISO_D = { 20,  25,   31.5f, 40,   50,   63,   80,   100,  125,  160,  200,  250,   315,   400,   500,  630,
		                                                                 800, 1000, 1250,  1600, 2000, 2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000 };

	static std::vector<float> OCTAVE_CENTER_FREQUENCIES_ISO_F  = { 31.5f, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000 };
	static std::vector<double> OCTAVE_CENTER_FREQUENCIES_ISO_D = { 31.5f, 63, 125, 250, 500, 1000, 2000, 4000, 8000, 16000 };

	// Default speed of sound at 344 m/s
	static double DEFAULT_SPEED_OF_SOUND_D = 344.0f;                          // m/s
	static float DEFAULT_SPEED_OF_SOUND_F  = (float)DEFAULT_SPEED_OF_SOUND_D; // m/s

	// Dfault humindity at 80%
	static double DEFAULT_HUMIDITY_D = 80.0f;                     // Percent
	static float DEFAULT_HUMIDITY_F  = (float)DEFAULT_HUMIDITY_D; // Percent

	// Default temperature at 20 centigrade (degree celcius)
	static double DEFAULT_TEMPERATURE_D = 20.0f;                        // °C
	static float DEFAULT_TEMPERATURE_F  = (float)DEFAULT_TEMPERATURE_D; // °C

	// Default static pressure at 100125.0 Pa
	static double DEFAULT_STATIC_PRESSURE_D = 101325.0f;                        // Pascal (absolute)
	static float DEFAULT_STATIC_PRESSURE_F  = (float)DEFAULT_STATIC_PRESSURE_D; // Pascal (absolute)

	// Legacy, please use DEFAULT_SPEED_OF_SOUND instead
	static double SPEED_OF_SOUND_D = DEFAULT_SPEED_OF_SOUND_D; // m/s
	static float SPEED_OF_SOUND_F  = DEFAULT_SPEED_OF_SOUND_F; // m/s
};                                                             // namespace ITAConstants

#endif // INCLUDE_WATCHER_ITA_CONSTANTS

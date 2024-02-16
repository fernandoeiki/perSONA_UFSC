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

#ifndef INCLUDE_WATCHER_ITA_BASE_DEFINITIONS
#define INCLUDE_WATCHER_ITA_BASE_DEFINITIONS

#if( defined WIN32 ) && !( defined ITA_BASE_STATIC )
#	ifdef ITA_BASE_EXPORT
#		define ITA_BASE_API __declspec( dllexport )
#	else
#		define ITA_BASE_API __declspec( dllimport )
#	endif
#else
#	define ITA_BASE_API
#endif

namespace ITABase
{
	namespace MixingMethod
	{
		enum
		{
			OVERWRITE = 0, //!< Overwrites the target buffer with new samples
			ADD       = 1, //!< Adds (mixes) the new samples to the target buffer
		};
	} // namespace MixingMethod

	//! Überblendfunktionen
	namespace FadingFunction
	{
		enum
		{
			SWITCH = -1,
			LINEAR = 0,    //!< Lineare Überblendung aka. Rampe
			COSINE_SQUARE, //!< Cosinus-Quadrat Überblendung (aka Hanning-Fenster)
		};
	} // namespace FadingFunction

	//! Interpolation methods
	namespace InterpolationFunctions
	{
		enum
		{
			NONE   = -1,
			LINEAR = 0,    //!< Linear interpolation
			CUBIC_SPLINE,  //!< Cubic spline interpolation
			WINDOWED_SINC, //!< Windowed sinc interpolation
		};
	} // namespace InterpolationFunctions

	//! Fading sign
	/**
	 * Direction how to fade, i.e. in or out
	 */
	namespace FadingSign
	{
		enum
		{
			FADE_IN = 0, //!< Fade in
			FADE_OUT,    //!< Fade out
		};
	} // namespace FadingSign
	//! Crossfade direction
	/**
	 * Fading direction from source or to source
	 */
	namespace CrossfadeDirection
	{
		enum
		{
			TO_SOURCE = 0, //!< Crossfade to the source signal
			FROM_SOURCE,   //!< Crossfade off source signal
		};
	} // namespace CrossfadeDirection
} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_BASE_DEFINITIONS

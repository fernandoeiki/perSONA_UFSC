/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
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
 *		Diffraction simulation mode using the Kirchhoff
 *      approximation based on detour.
 *
 */

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_MAEKAWA
#define INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_MAEKAWA

#include "Definitions.h"

// ITA includes
#include <ITAConstants.h>
#include <ITAGeo/Base.h>
#include <ITAHDFTSpectrum.h>
#include <ITASampleBuffer.h>

// STL includes
#include <cassert>

namespace ITAPropagationModels
{
	//! Diffraction calculation based on Maekawa
	/**
	 * @sa Maekawa, Z.; Noise reduction by screens Applied Acoustics; 1968, 1, 157 - 173
	 * @sa Pierce, A. D.; Diffraction of sound around corners and over wide barriers; J. Acoust. Soc. Am., 1974, 55, 941-955
	 */
	namespace Maekawa
	{
		//! Validates if Maekawa diffraction method can be applied
		/**
		 * The Maekawa method only makes sense if the source is
		 * occluded by obstacles in it's way to the receiver (or vice versa).
		 * This may include specular reflections, but inverse wedges (corners) have to
		 * be excluded because they can not occlude entities.
		 *
		 * @param[in] v3SourcePos Source position
		 * @param[in] v3TargetPos Target position
		 * @param[in] pApex Aperture point on wedge
		 *
		 * @return True, if Maekawa can be used (diffracting into shadow zone)
		 *
		 * @sa MaekawaDetourAndLength
		 * @sa MaekawaDiffractionFilter
		 *
		 * @note Throws ITAException on error
		 *
		 */
		bool ITA_PROPAGATION_MODELS_API IsApplicable( const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos,
		                                              std::shared_ptr<const ITAGeo::CITADiffractionWedgeApertureBase> pApex );

		//! Calculates the detour of a propagation path for the Maekawa method
		/**
		 * Calculates the direct path vs. detour path by taking the diffraction anchor into account.
		 *
		 * @param[in] v3SourcePos Source position
		 * @param[in] v3TargetPos Target position
		 * @param[in] pApex Aperture point on wedge
		 * @param[out] dPropagationLengthFreeField Propagation path length without occlusion [m]
		 * @param[out] dPropagationLengthOverApex Propagation path detour length with occlusion [m]
		 *
		 * @sa IsMaekawaApplicable
		 *
		 * @note Throws ITAException on error
		 *
		 */
		void ITA_PROPAGATION_MODELS_API GetDirectLengthAndDetourLength( const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos,
		                                                                std::shared_ptr<const ITAGeo::CITADiffractionWedgeApertureBase> pApex,
		                                                                double& dPropagationLengthFreeField, double& dPropagationLengthOverApex );

		//! Calculates the detour-and-direct-path difference of a propagation path for the Maekawa method
		/**
		 * @param[in] dPropagationLengthFreeField Direct path length [m] (sometimes referred to as 'd')
		 * @param[in] dPropagationLengthOverApex Detour path length [m] (sometimes referred to as 'A+B')
		 *
		 * @return Kirchhoff delta (difference) [m] (\delta, sometimes referred to as 'A+B-d')
		 *
		 * @note Throws ITAException on error
		 *
		 */
		double ITA_PROPAGATION_MODELS_API KirchhoffDelta( const double dPropagationLengthFreeField, const double dPropagationLengthOverApex );

		//! Calculates the detour-and-direct-path inverse difference factor of a propagation path for the Maekawa method
		/**
		 * @return Kirchhoff delta factor (ratio), always greater or equal 1.0
		 *
		 * @note Throws ITAException on error
		 *
		 */
		inline double KirchhoffDeltaInverseFactor( const double dPropagationLengthFreeField, const double dPropagationLengthOverApex )
		{
			const double dKirchhoffDelta              = Maekawa::KirchhoffDelta( dPropagationLengthFreeField, dPropagationLengthOverApex );
			const double dKirchhoffDeltaInverseFactor = ( dPropagationLengthFreeField + dKirchhoffDelta ) / dPropagationLengthFreeField;
			return dKirchhoffDeltaInverseFactor;
		};

		//! Calculate diffraction filter based on the Maekawa detour method
		/**
		 * This function calculates the Maekawa diffraction filter coefficient based on detour length around a wedge obstacle
		 * and the direct path length with and without any obstacles.
		 *
		 * @param[in] dPropagationLengthFreeField Direct path length [m]
		 * @param[in] dPropagationLengthOverApex Detour path length [m]
		 * @param[in] fFrequency Frequency [Hz]
		 * @param[in] fSpeedOfSound Speed of sound [m/s]
		 *
		 */
		double ITA_PROPAGATION_MODELS_API CalculateDiffractionFilterCoefficient( const double dPropagationLengthFreeField, const double dPropagationLengthOverApex,
		                                                                         const float fFrequency,
		                                                                         const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );

		//! Calculate diffraction factor based on the Maekawa detour method
		/**
		 * This function calculates the Maekawa diffraction factor based on detour length around a wedge obstacle
		 * and the direct path length with and without any obstacles.
		 * The diffraction factor contains the influence of the wedge without the influence of the propagation path length.
		 *
		 * @param[in] dPropagationLengthFreeField Direct path length [m]
		 * @param[in] dPropagationLengthOverApex Detour path length [m]
		 * @param[in] fFrequency Frequency [Hz]
		 * @param[in] fSpeedOfSound Speed of sound [m/s]
		 *
		 */
		double ITA_PROPAGATION_MODELS_API CalculateDiffractionFactor( const double dPropagationLengthFreeField, const double dPropagationLengthOverApex,
		                                                              const float fFrequency, const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );


		//! Calculate diffraction filter (frequency domain) based on the Maekawa detour method
		/**
		 * This function calculates the Maekawa diffraction filter based on detour length around a wedge obstacle
		 * and the direct path length with and withont any obstacles.
		 *
		 * @param[in] dPropagationLengthFreeField Direct path length [m]
		 * @param[in] dPropagationLengthOverApex Detour path length [m]
		 * @param[out] oTransferFunction Destination filter of simulation (zero-phase frequency domain magnitude spectrum)
		 * @param[in] fSpeedOfSound Speed of sound [m/s]
		 *
		 */
		void ITA_PROPAGATION_MODELS_API CalculateDiffractionFilter( const double dPropagationLengthFreeField, const double dPropagationLengthOverApex,
		                                                            ITABase::CHDFTSpectrum& oTransferFunction,
		                                                            const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );
	} // namespace Maekawa
} // namespace ITAPropagationModels

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_MAEKAWA

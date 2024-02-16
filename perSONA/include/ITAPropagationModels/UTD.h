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
 *		Uniform Theory of Diffraction (UTD) approximation
 *
 *
 */

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_UTD
#define INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_UTD

#include "Base.h"
#include "Definitions.h"

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes
#include <ITAConstants.h>
#include <ITAGeo/Base.h>
#include <ITAHDFTSpectrum.h>
#include <ITASampleBuffer.h>

// STL includes
#include <ccomplex>

namespace ITAPropagationModels
{
	namespace UTD
	{
		//! UTD diffraction coefficient calculation methods (only approximation implemented yet!)
		enum UTD_DIFFRACTION_ALGORITHM
		{
			UTD_FRESNEL_INTEGRAL_FORM    = 1, //!< Solve Fresnel integral over komplex value (not implemented yet!)
			UTD_APPROX_KAWAI_KOUYOUMJIAN = 2, //!< Skip integral solution and use approximations
		};

		// ITA_PROPAGATION_MODELS_API bool GenerateUTDDiffractionFilter( const CITAGeoPropagationPath& vPath, ITAHDFTSpectrum& oDiffractionAttenuationSpectrum );
		// ITA_PROPAGATION_MODELS_API bool GenerateUTDDiffractionFilter( const CITAGeoPropagationAnchor& oSource, const CITAGeoPropagationAnchor& oTarget, const
		// CITADiffractionWedgeAperture& oApex, ITAHDFTSpectrum& oDiffractionAttenuationSpectrum );

		//! Calculates the complex valued UTD diffraction coefficient for a given constellation and wave number
		/**
		 * @sa Tsingos, N.; Funkhouser, T.; Ngan, A. & Carlbom, I.; Modeling Acoustics in Virtual Environments Using the Uniform Theory of Diffraction; Proceedings of the
		 * 28th Annual Conference on Computer Graphics and Interactive Techniques, ACM, 2001, 545-552
		 * @sa Kouyoumjian, R. G. & Pathak, P. H.; A uniform geometrical theory of diffraction for an edge in a perfectly conducting surface; Proceedings of the IEEE,
		 * IEEE, 1974, 62, 1448-1461
		 * @sa Kawai, T.; Sound diffraction by a many-sided barrier or pillar; Journal of Sound Vibration, 1981, 79, 229-242
		 *
		 * @param[in] v3SourcePos Source position (outside wedge), rojected position may have to be used for correct distances!
		 * @param[in] v3TargetPos target position (outside wedge)
		 * @param[in] pApex Aperture point including wedge parameters (angles, etc)
		 * @param[in] fWaveNumber Wave number ( k )
		 * @param[out] cfFactor Complex-valued diffraction coefficient ( D( n, k,\rho, r, \phi_i, \alpha_i, \alpha_d ) )
		 * @param[in] iMethod Approximation algorithm
		 */
		bool ITA_PROPAGATION_MODELS_API CalculateDiffractionCoefficient( const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos,
		                                                                 std::shared_ptr<const ITAGeo::CITADiffractionWedgeApertureBase> pApex, const float fFrequency,
		                                                                 std::complex<float>& cfCoeff, const int iMethod = UTD_APPROX_KAWAI_KOUYOUMJIAN,
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
		bool ITA_PROPAGATION_MODELS_API CalculateDiffractionFactor( const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos,
		                                                            std::shared_ptr<const ITAGeo::CITADiffractionWedgeApertureBase> pApex, const float fFrequency,
		                                                            std::complex<float>& cfFactor, const int iMethod = UTD_APPROX_KAWAI_KOUYOUMJIAN,
		                                                            const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );

		//! Calculates the UTD diffraction filter in frequency domain for a given constellation
		/**
		 * @sa Tsingos, N.; Funkhouser, T.; Ngan, A. & Carlbom, I.; Modeling Acoustics in Virtual Environments Using the Uniform Theory of Diffraction; Proceedings of the
		 * 28th Annual Conference on Computer Graphics and Interactive Techniques, ACM, 2001, 545-552
		 * @sa Kouyoumjian, R. G. & Pathak, P. H.; A uniform geometrical theory of diffraction for an edge in a perfectly conducting surface; Proceedings of the IEEE,
		 * IEEE, 1974, 62, 1448-1461
		 * @sa Kawai, T.; Sound diffraction by a many-sided barrier or pillar; Journal of Sound Vibration, 1981, 79, 229-242
		 *
		 * @param[in] v3SourcePos Source position (outside wedge), rojected position may have to be used for correct distances!
		 * @param[in] v3TargetPos target position (outside wedge)
		 * @param[in] pApex Aperture point including wedge parameters (angles, etc)
		 * @param[out] oTF Diffraction transfer function / filter in frequency domain
		 * @param[in] iMethod Approximation algorithm
		 * @param[in] fSpeedOfSound Sound speed
		 */
		void ITA_PROPAGATION_MODELS_API CalculateDiffractionFilter( const VistaVector3D& v3SourcePos, const VistaVector3D& v3TargetPos,
		                                                            std::shared_ptr<const ITAGeo::CITADiffractionWedgeApertureBase> pApex, ITABase::CHDFTSpectrum& oTF,
		                                                            const int iMethod         = UTD_APPROX_KAWAI_KOUYOUMJIAN,
		                                                            const float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F );
	} // namespace UTD
} // namespace ITAPropagationModels

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_UTD

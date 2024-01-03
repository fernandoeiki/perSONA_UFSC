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
 */

#ifndef IW_ITA_GEO_ACOUSTIC_MATERIAL
#define IW_ITA_GEO_ACOUSTIC_MATERIAL

#ifdef THIRD_OCTAVE
#	undef THIRD_OCTAVE
#endif

// ITAGeo includes
#include <ITAGeo/Definitions.h>

// ITABase
#include <ITAThirdOctaveMagnitudeSpectrum.h>

// Vista includes
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>

// STL includes
#include <complex>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace ITAGeo
{
	namespace Material
	{
		//! Acoustic material
		/**
		 * This class can be used as a base for acoustic
		 * material data sets. Depending on material type,
		 * a cast can be performed to acces specific data of
		 * that type of acoustic material.
		 *
		 */
		class ITA_GEO_API IMaterial
		{
		public:
			enum Type
			{
				NONE = 0,           //!< No data type specified
				VISUALIZATION,      //!< Visualization material (colors, textures, etc)
				SCALAR,             //!< One dimensional values, see CITAOneDimAcousticMaterial
				TRI_BAND,           //!< Three values, see CITATriBandAcousticMaterial
				WHOLE_OCTAVE,       //!< Whole-octave values, see CITAWholeOctaveAcousticMaterial
				THIRD_OCTAVE,       //!< Third-octave values, see CITAThirdOctaveAcousticMaterial
				COMPLEX_SPECTRUM,   //!< Complex-valued spectrum, see ?
				MAGNITUDE_SPECTRUM, //!< Magnitude spectrum values, see ?
			};

			//! Return string type (for casting)
			virtual int GetType( ) const = 0;

			//! Material identifier (string)
			virtual std::string GetIdentifier( ) const = 0;

			//! Material name (@sa GetIdentifier)
			inline std::string GetName( ) const { return GetIdentifier( ); };

			//! Get material type as string
			std::string GetTypeStr( ) const;
		};


		class ITA_GEO_API CVisualizationMaterial : public IMaterial
		{
		public:
			std::string sName;
			inline CVisualizationMaterial( ) : dRed( 0 ), dGreen( 0 ), dBlue( 0 ), dAlpha( 1.0f ) { };
			inline std::string GetIdentifier( ) const { return sName; };
			inline int GetType( ) const { return IMaterial::VISUALIZATION; };
			double dRed, dGreen, dBlue, dAlpha; //!< Data range from 0 to 1

			inline void SetBlack( )
			{
				dRed = dGreen = dBlue = 0.0f;
				dAlpha                = 1.0f;
			};

			inline void SetWhite( )
			{
				dRed = dGreen = dBlue = 1.0f;
				dAlpha                = 1.0f;
			};
		};

		class ITA_GEO_API CScalarMaterial : public IMaterial
		{
		public:
			std::string sName;                            //! Versatile name (for debugging)
			std::complex<double> cdReflectionFactor;      //! Complex-valued reflection factor with magnitude [0..1]
			std::complex<double> cdTransmissionFactor;    //! Complex-valued transmission factor with magnitude [0..1]
			std::complex<double> cdScatteringCoefficient; //! Complex-valued scattering coefficient with magnitude [0..1]

			inline CScalarMaterial( ) { SetDefaults( ); };

			inline CScalarMaterial( const std::complex<double>& cdR, const std::complex<double>& cdT, const std::complex<double>& cdS )
			    : cdReflectionFactor( cdR )
			    , cdTransmissionFactor( cdT )
			    , cdScatteringCoefficient( cdS ) { };

			inline ~CScalarMaterial( ) { };

			inline std::string GetIdentifier( ) const { return sName; };

			inline int GetType( ) const { return IMaterial::SCALAR; };

			inline void SetDefaults( )
			{
				cdReflectionFactor.real( 0.7f );
				cdReflectionFactor.imag( 0.0f );
				cdTransmissionFactor.real( 0.0f );
				cdTransmissionFactor.imag( 0.0f );
				cdScatteringCoefficient.real( 0.1f );
				cdScatteringCoefficient.imag( 0.0f );
			};

			inline double GetAbsorptionCoefficient( )
			{
				// alpha = 1 - |R|^2
				return ( 1.0f - std::pow( std::abs( cdReflectionFactor ), 2 ) );
			};
		};

		class ITA_GEO_API CThirdOctaveMaterial : public IMaterial
		{
		public:
			std::string sName; //! Versatile name (for debugging)

			ITABase::CThirdOctaveGainMagnitudeSpectrum oAbsorptionCoefficients;
			ITABase::CThirdOctaveGainMagnitudeSpectrum oScatteringCoefficients;

			inline ~CThirdOctaveMaterial( ) { };

			inline std::string GetIdentifier( ) const { return sName; };

			inline int GetType( ) const { return IMaterial::THIRD_OCTAVE; };

			inline int GetNumBands( ) const { return ITABase::CThirdOctaveGainMagnitudeSpectrum::GetNumBands( ); };

			inline float GetTransmissionFactor( int iFrequencyBandIndex ) const { return sqrt( 1 - oAbsorptionCoefficients[iFrequencyBandIndex] ); };
		};

		//! Acoustic vertex property
		struct ITA_GEO_API CAcousticVertexProperty
		{
			std::string sName; //! Versatile name (for debugging)
		};

		//! Acoustic edge property
		struct ITA_GEO_API CAcousticEdgeProperty
		{
			std::string sName; //! Versatile name (for debugging)
		};

		//! Acoustic face property
		/*
		 * Acoustic properties that are connected to a face
		 * of a mesh with polygons.
		 *
		 */
		class ITA_GEO_API CAcousticFaceProperty
		{
		public:
			std::string sName; //! Versatile name (for debugging)

			inline CAcousticFaceProperty( ) : m_pMaterial( NULL ), sName( "default" ) { };

			//! Destructor releases material, set material pointer to NULL to keep material in memory
			inline virtual ~CAcousticFaceProperty( ) { };

			inline CAcousticFaceProperty( const CAcousticFaceProperty& oOtherMaterial ) { *this = oOtherMaterial; };

			inline CAcousticFaceProperty& operator=( const CAcousticFaceProperty& oOtherMaterial )
			{
				m_pMaterial = oOtherMaterial.m_pMaterial;
				sName       = oOtherMaterial.sName;

				return *this;
			};

			inline std::shared_ptr<IMaterial> GetMaterial( ) const { return m_pMaterial; };

			inline void SetMaterial( std::shared_ptr<IMaterial> pMaterial ) { m_pMaterial = pMaterial; };

		private:
			std::shared_ptr<IMaterial> m_pMaterial; //! Shared pointer to complex material
		};
	} // namespace Material
} // namespace ITAGeo

#endif // IW_ITA_GEO_ACOUSTIC_MATERIAL

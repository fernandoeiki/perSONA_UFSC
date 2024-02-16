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

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_FILTER_ENGINE
#define INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_FILTER_ENGINE

// ITAPropagationModel includes
#include "Base.h"
#include "Definitions.h"

// ITA includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Directivity/Manager.h>
#include <ITAGeo/Material/Manager.h>
#include <ITAHDFTSpectra.h>
#include <ITAHDFTSpectrum.h>

// STL includes
#include <vector>


namespace ITAPropagationModels
{
	//! Transfer function filter generator for propagation paths
	/**
	 * Generates transfer functions in the frequency-domain that
	 * can be used as filters, e.g. for auralization.
	 *
	 * @note Not thread safe
	 */
	class ITA_PROPAGATION_MODELS_API CFilterEngine
	{
	public:
		//!< Material resolutions structure (used if not determined by material)
		struct TMaterialResolution
		{
			ITAGeo::Material::IMaterial::Type iReflection   = ITAGeo::Material::IMaterial::SCALAR;       //!< Default reflection component resolution
			ITAGeo::Material::IMaterial::Type iDiffraction  = ITAGeo::Material::IMaterial::THIRD_OCTAVE; //!< Default diffraction component resolution
			ITAGeo::Material::IMaterial::Type iTransmission = ITAGeo::Material::IMaterial::THIRD_OCTAVE; //!< Default transmission component resolution
		} oMaterialResolution;

		//! Static environment state description
		struct TStaticEnvironmentState
		{
			double dHumidity    = ITAConstants::DEFAULT_HUMIDITY_D;
			double dTemperature = ITAConstants::DEFAULT_TEMPERATURE_D;
			float fSpeedOfSound = ITAConstants::DEFAULT_SPEED_OF_SOUND_F;
		} oEnvironmentState; //!< Environment state

		enum EAtmoshpericAbsorption
		{
			NONE = -1,
			ISO9613,
		};

		enum EGeometricalSpreading
		{
			PLANE_WAVE = 1,
			CYLINDRIC_WAVE,
			SPHERICAL_WAVE,
		};

		//! Propagation model configuration description
		struct TPropagationModelConfiguration
		{
			int iAtmosphericAbsorption = EAtmoshpericAbsorption::ISO9613;
			int iDiffractionModel      = DiffractionModels::MAEKAWA_DETOUR_LAW;
			int iGeometricalSpreading  = SPHERICAL_WAVE;
		} oPropagationModelConfiguration; //!< Propagation model configuration


		//! Standard constructor for a filter engine
		CFilterEngine( const ITAGeo::ECoordinateSystemConvention iConvention = ITAGeo::ECoordinateSystemConvention::ISO );


		//! Default destructor of a filter engine
		~CFilterEngine( );

		//! Returns number of sensor channels
		/**
		 * @param[in] oPathList Propagation path list
		 *
		 * @note Throws ITAException if sensors have different number of channels
		 */
		static int GetNumSensorChannels( const ITAGeo::CPropagationPathList& oPathList );

		//! Checks if the sensor is the same anchor for all propagation paths
		/**
		 * @param[in] oPathList Propagation path list
		 * @return True, if path list shares the same sensor
		 *
		 * @note Throws ITAException if sensors have different number of channels
		 */
		static bool ValidateSameSensor( const ITAGeo::CPropagationPathList& oPathList );

		//! Checks if the sensor is the same anchor for all propagation paths
		/**
		 * @param[in] oPathList Propagation path list
		 * @return True, if path list shares the same emitter
		 *
		 * @note Throws ITAException if sensors have different number of channels
		 */
		static bool ValidateSameEmitter( const ITAGeo::CPropagationPathList& oPathList );

		//! Generate multi-channel propagation path (for multi-channel receiver directivity)
		/**
		 * @todo AER
		 */
		void Generate( const ITAGeo::CPropagationPathList& oPathList, ITABase::CHDFTSpectra& oFilter, bool* pbDFTDegreeTooSmall = NULL );

		//! Generate single propagation path (for multi-channel receiver directivity)
		inline void Generate( const ITAGeo::CPropagationPath& oPath, ITABase::CHDFTSpectra& oFilter, bool* pbDFTDegreeTooSmall = NULL )
		{
			ITAGeo::CPropagationPathList oPathList;
			oPathList.push_back( oPath );
			Generate( oPathList, oFilter, pbDFTDegreeTooSmall );
		};

		//! Generate single-channel propagation path (for single-channel receiver directivity)
		inline void Generate( const ITAGeo::CPropagationPathList& oPathList, ITABase::CHDFTSpectrum& oFilter, bool* pbDFTDegreeTooSmall = NULL )
		{
			const std::vector<ITABase::CHDFTSpectrum*> vpSpectra = { &oFilter };
			ITABase::CHDFTSpectra oTF( vpSpectra );
			Generate( oPathList, oTF, pbDFTDegreeTooSmall );
		};

		//! Sets a connection to the material manager
		void SetMaterialManager( std::shared_ptr<const ITAGeo::Material::IManager> pMaterialManager );

		// Returns pointer to material manager or null
		std::shared_ptr<const ITAGeo::Material::IManager> GetMaterialManager( ) const;

		//! Sets a connection to the diffraction manager
		void SetDirectivityManager( std::shared_ptr<const ITAGeo::Directivity::IManager> pDirectivityManager );

		// Returns pointer to directivity manager or null
		std::shared_ptr<const ITAGeo::Directivity::IManager> GetDirectivityManager( ) const;


	private:
		std::unique_ptr<ITABase::CHDFTSpectra> m_pAccumulatedSpectra;  //!< Gathered propagation paths from list
		std::unique_ptr<ITABase::CHDFTSpectra> m_pTempPropPathSpectra; //!< Single prop-path spectra


		std::shared_ptr<const ITAGeo::Material::IManager> m_pMaterialManager;
		std::shared_ptr<const ITAGeo::Directivity::IManager> m_pDirectivityManager;

		ITAGeo::ECoordinateSystemConvention m_iCoordinateSystemConvention;
	};
} // namespace ITAPropagationModels

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_MODELS_FILTER_ENGINE

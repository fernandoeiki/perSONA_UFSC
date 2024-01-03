#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_SIMULATION_RESULT
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_SIMULATION_RESULT

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/simulation_result.h>

// ITA includes
#include <ITAThirdOctaveMagnitudeSpectrum.h>

// Vista includes
#include <VistaAspects/VistaSerializable.h>
#include <VistaBase/VistaVector3D.h>

// STD
#include <string.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		namespace OutdoorAcoustics
		{
			///
			/// \brief Result of a room acoustic simulation.
			///
			/// This class is primarily just a container for the data of an update.
			///
			struct ITA_SIMULATION_SCHEDULER_API COutdoorSimulationResult : public CSimulationResult
			{
				struct ITA_SIMULATION_SCHEDULER_API CPathProperty : public IVistaSerializable
				{
					inline CPathProperty( )
					{
						oGeoAttenuationSpectrum.SetIdentity( );
						oAirAttenuationSpectrum.SetIdentity( );
					};

					std::string sID;

					double dPropagationDelay; //!< Delay in seconds
					double dSpreadingLoss;    //!< Wave type specific spreading loss factor

					int iReflectionOrder  = 0;
					int iDiffractionOrder = 0;

					ITABase::CThirdOctaveFactorMagnitudeSpectrum oGeoAttenuationSpectrum; //!< Combined attenuation of geometry interaction (reflections and diffractions)
					ITABase::CThirdOctaveFactorMagnitudeSpectrum oAirAttenuationSpectrum;

					VistaVector3D v3SourceWaveFrontNormal;   //!< Outgoing wave front normal at source (retarded?)
					VistaVector3D v3ReceiverWaveFrontNormal; //!< Incident wave front normal at receiver

					int Serialize( IVistaSerializer& pSerializer ) const override;
					int DeSerialize( IVistaDeSerializer& pDeserializer ) override;
					inline std::string GetSignature( ) const override { return "CPathProperty"; };
				};

				std::vector<CPathProperty> voPathProperties;

				///
				/// \brief Serialize the object.
				/// \param pSerializer the IVistaSerializer to use.
				/// \return the number of bytes written or -1 on failure.
				///
				int Serialize( IVistaSerializer& pSerializer ) const override;

				///
				/// \brief DeSerialize the object.
				/// \param pDeserializer the IVistaDeSerializer to use.
				/// \return the number of bytes written or -1 on failure.
				///
				int DeSerialize( IVistaDeSerializer& pDeserializer ) override;

				///
				/// \brief Return a unique identifier for the object for serialization.
				/// \return "COutdoorSimulationResult".
				///
				inline std::string GetSignature( ) const override { return "COutdoorSimulationResult"; };

				///
				/// \brief Method to clone the object.
				/// \return a clone of the object.
				///
				std::unique_ptr<CSimulationResult> Clone( ) const override;
			};
		} // namespace OutdoorAcoustics
	}     // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_OUTDOOR_ACOUSTICS_SIMULATION_RESULT
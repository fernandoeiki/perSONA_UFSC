#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SIMULATION_RESULT
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SIMULATION_RESULT

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/types.h>

// std includes
#include <memory>

// VISTA includes
#include <VistaAspects/VistaSerializable.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Base class for a result of an acoustic simulation.
		///
		/// This class is primarily just a container for the data of an result.
		///
		struct ITA_SIMULATION_SCHEDULER_API CSimulationResult : public IVistaSerializable
		{
			///
			/// \brief The C3DObject of source and receiver at the position when the update was issued that resulted in this result.
			/// \todo We probably need a copy of the pair .. make it bullet proof. Or do we just need the reference ID
			///
			SourceReceiverPair sourceReceiverPair = SourceReceiverPair( );

			//! \brief Time stamp of the scene update that lead to this result
			double dTimeStamp = -1;

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
			/// \return "CRIRSimulationResult".
			///
			virtual std::string GetSignature( ) const override;

			///
			/// \brief Method to clone the object.
			/// \return a clone of the object.
			///
			virtual std::unique_ptr<CSimulationResult> Clone( ) const;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_SIMULATION_RESULT
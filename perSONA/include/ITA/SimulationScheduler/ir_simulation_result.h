#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_IR_SIMULATION_RESULT
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_IR_SIMULATION_RESULT

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// simulation scheduler includes
#include <ITA/SimulationScheduler/simulation_result.h>

// ITA includes
#include <ITASampleFrame.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Result of a room acoustic simulation.
		///
		/// This class is primarily just a container for the data of an update.
		///
		struct ITA_SIMULATION_SCHEDULER_API CIRSimulationResult : public CSimulationResult
		{
			///
			/// \brief Sample Frame containing the actual result of the simulation.
			///
			ITASampleFrame sfResult = ITASampleFrame( );

			///
			/// \brief Number of leading zeros.
			///
			int iLeadingZeros = -1;

			///
			/// \brief Number of trailing zeros.
			///
			int iTrailingZeros = -1;

			///
			/// \brief True if leading and trailing zeros were removed from #sfResult.
			///
			bool bZerosStripped = true;

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
			std::unique_ptr<CSimulationResult> Clone( ) const override;
		};
	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_IR_SIMULATION_RESULT
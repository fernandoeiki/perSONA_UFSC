#ifndef INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_3D_OBJECT
#define INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_3D_OBJECT

// API includes
#include <ITA/SimulationScheduler/definitions.h>

// VISTA includes
#include <VistaAspects/VistaSerializable.h>
#include <VistaBase/VistaQuaternion.h>
#include <VistaBase/VistaVector3D.h>

namespace ITA
{
	namespace SimulationScheduler
	{
		///
		/// \brief Models a source or receiver in 3D space.
		///
		class ITA_SIMULATION_SCHEDULER_API C3DObject : public IVistaSerializable
		{
		public:
			///
			/// \brief Types of C3DObjects.
			///
			enum class Type
			{
				source,
				receiver
			};

			///
			/// \brief Default constructor.
			///
			/// This constructor is primarily used for creating an object for deserialization.
			/// It does initializes the object with m_iID=-1 and m_eType=Type::source.
			///
			C3DObject( ) = default;

			///
			/// \brief Constructor of a C3DObject.
			///
			/// C3DObject represent objects tracked in a virtual 3D environment.
			/// These can be either a source or a receiver.
			/// \param position position of the C3DObject.
			/// \param orientation orientation of the C3DObject.
			/// \param type the Type of C3DObject.
			/// \param id an identification number for the object.
			///
			C3DObject( const VistaVector3D& position, const VistaQuaternion& orientation, Type type, int id );


			///
			/// \brief Copy constructor.
			/// \param obj object to copy from.
			///
			C3DObject( const C3DObject& obj ) = default;

			///
			/// \brief Get the position of the C3DObject.
			/// \return a const ref to the position.
			///
			const VistaVector3D& GetPosition( ) const;

			///
			/// \brief Get the orientation of the C3DObject.
			/// \return a const ref to the orientation.
			///
			const VistaQuaternion& GetOrientation( ) const;

			///
			/// \brief Get the ID of the object.
			/// \return the ID of the C3DObject.
			///
			unsigned int GetId( ) const;

			///
			/// \brief Get the Type of the object.
			/// \return the Type of the C3DObject.
			///
			Type GetType( ) const;

			///
			/// \brief Compare two C3DObjects, with a given tolerance.
			///
			/// Similar to operator==(), this function compares two C3DObjects.
			/// However, this comparison allows for a tolerance for the comparison of #position and #orientation.
			/// \param obj the object to check against.
			/// \param dTolerance the allowed tolerance.
			/// \return true if the given object is the same as this with the given tolerance.
			///
			bool IsEqualTolerance( const C3DObject& obj, double dTolerance ) const;

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
			/// \return "CUpdateConfig".
			///
			virtual std::string GetSignature( ) const override;

		private:
			///
			/// \brief Identification number of the C3DObject.
			///
			int m_iID = -1;

			///
			/// \brief The type of the C3DObject.
			///
			Type m_eType = Type::source;

			///
			/// \brief The position of the C3DObject.
			///
			/// The postion is encoded in a 3D Vector.
			///
			VistaVector3D m_v3Position;

			///
			/// \brief The orientation of the C3DObject.
			///
			/// The orientation is encoded in Quaternion notation.
			///
			VistaQuaternion m_qOrientation;
		};

		///
		/// \brief Compare two C3DObjects.
		///
		/// Check if \p lhs and \p rhs are exactly the same.
		/// For this all members have to match.
		/// \param lhs the first object to check.
		/// \param rhs the second object to check.
		/// \return true if the given objects are exactly the same.
		///
		inline bool operator==( const C3DObject& lhs, const C3DObject& rhs )
		{
			return lhs.GetType( ) == rhs.GetType( ) && lhs.GetId( ) == rhs.GetId( ) && lhs.GetPosition( ) == rhs.GetPosition( ) &&
			       lhs.GetOrientation( ) == rhs.GetOrientation( );
		}

	} // namespace SimulationScheduler
} // namespace ITA

#endif // INCLUDE_WATCHER_ITA_SIMULATION_SCHEDULER_3D_OBJECT

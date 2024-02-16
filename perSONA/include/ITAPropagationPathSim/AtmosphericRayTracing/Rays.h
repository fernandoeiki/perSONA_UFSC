/*
 * ----------------------------------------------------------------
 *
 *		ITA geometrical acoustics
 *		(c) Copyright Institute of Technical Acoustics (ITA)
 *		RWTH Aachen University, Germany, 2015-2022
 *
 * ----------------------------------------------------------------
 * 				    ____  __________  _______
 *				   //  / //__   ___/ //  _   |
 *				  //  /    //  /    //  /_|  |
 *				 //  /    //  /    //  ___   |
 *				//__/    //__/    //__/   |__|
 *
 * ----------------------------------------------------------------
 *
 */

#ifndef IW_ITA_PROPAGATIONPATHSIM_ART_RAYS
#define IW_ITA_PROPAGATIONPATHSIM_ART_RAYS

#include <ITAPropagationPathSim/Definitions.h>

// Vista includes
#include <VistaBase/VistaVector3D.h>

// ITA includes

// STD
#include <map>
#include <vector>

namespace ITAPropagationPathSim
{
	namespace AtmosphericRayTracing
	{
		class ITA_PROPAGATION_PATH_SIM_API CRayElement
		{
		public:
			VistaVector3D position;
			VistaVector3D wavefrontNormal;
			double timeStamp;

			inline CRayElement( ) { };
			inline CRayElement( const VistaVector3D& r, const VistaVector3D& n, const double& time ) : position( r ), wavefrontNormal( n ), timeStamp( time ) { };

			//! Does a linear interpolation from this element to the given one using a factor [0.0 1.0] and returns the new element.
			CRayElement Interpolate( const CRayElement& target, const float fFraction ) const;
		};
		//! Compares the timestamps of given CRayElements using the < operator
		inline bool operator<( const CRayElement& lhs, const CRayElement& rhs ) { return lhs.timeStamp < rhs.timeStamp; };

		class ITA_PROPAGATION_PATH_SIM_API CRayReceiverData
		{
		public:
			bool bDistanceUpdatedInLastIt; //!< indicates whether receiver distance was updated in last during last integration step
			float distance;
			int idxMinDist;
			int reflectionOrder;
			VistaVector3D posMinDist;

			inline CRayReceiverData( ) : idxMinDist( -1 ), distance( -1 ), reflectionOrder( -1 ), posMinDist( VistaVector3D( ) ), bDistanceUpdatedInLastIt( false ) { };
			inline CRayReceiverData( int iMin, float dMin, int reflOrder, const VistaVector3D& rMin = VistaVector3D( ) )
			    : idxMinDist( iMin )
			    , distance( dMin )
			    , reflectionOrder( reflOrder )
			    , posMinDist( rMin )
			    , bDistanceUpdatedInLastIt( true ) { };
		};

		class ITA_PROPAGATION_PATH_SIM_API CRay : public std::vector<CRayElement>
		{
		private:
			bool m_bEigenray    = false; //!< Indicates whether ray is result of an eigenray search
			bool m_bReceiverHit = true;  //!< Indicates whether eigenray search was successful (accuracy criterion reached)
			std::vector<int> m_viReflectionIndices;
			double m_dSpreadingLoss = -1; //!< Spreadingloss at last point of ray (receiver), calculated at the end of Eigenray search.

			typedef const VistaVector3D* ReceiverPositionPtr;
			typedef std::map<ReceiverPositionPtr, CRayReceiverData> ReceiverDistanceMap;
			ReceiverDistanceMap m_mReceiverDistanceMap;

		public:
			CRay( const VistaVector3D& v3SourcePos, const double& thetaDeg, const double& phiDeg );
			CRay( const VistaVector3D& v3SourcePos, const VistaVector3D& v3Direction );

		public:
#pragma region Get Functions

			// Returns true if ray is result of an eigenray search
			inline bool IsEigenray( ) const { return m_bEigenray; };
			// Returns true if eigenray search reached desired precision (receiver sphere was hit)
			inline bool ReceiverHit( ) const { return m_bReceiverHit; };

			inline const std::vector<int>& ReflectionIndices( ) const { return m_viReflectionIndices; };

			inline int NumPoints( ) const { return int( size( ) ); };
			inline const VistaVector3D& SourcePoint( ) const { return front( ).position; };
			inline const VistaVector3D& InitialDirection( ) const { return front( ).wavefrontNormal; };

			inline const VistaVector3D& LastPoint( ) const { return back( ).position; };
			inline const VistaVector3D& LastWavefrontNormal( ) const { return back( ).wavefrontNormal; };
			inline const double& LastTimeStamp( ) const { return back( ).timeStamp; };

			inline int ReflectionOrder( ) const { return int( m_viReflectionIndices.size( ) ); };
			//! Returns the reflection order of the ray element with given index
			// int ReflectionOrder(const int idx) const;

			//! Returns the spreading loss at end point of receiver. If this has not been calculated yet, this returns -1.
			inline double SpreadingLoss( ) const { return m_dSpreadingLoss; };
#pragma endregion

			//! Indicate that ray is result of an eigenray search
			void MarkAsEigenray( bool bAccuracyReached );

			//! Appends a new element with position, wavefront normal and timestamp to the ray
			void Append( const VistaVector3D& position, const VistaVector3D& wavefrontNormal, const double& timeStamp );
			//! Appends a new element to the ray and adds its index to iReflectionIndices
			void AppendReflection( const VistaVector3D& position, const VistaVector3D& wavefrontNormal, const double& timeStamp );
			//! Adds the last point to the list of reflection points
			void AddLastPointToReflectionList( );
			inline void SetSpreadingLoss( const double& spreadingLoss ) { m_dSpreadingLoss = spreadingLoss; };

			//! Returns true, if both rays have the same initial direction
			bool SameDirection( const CRay& other ) const;
			bool IsReflectionIdx( const int idx ) const;

			//! Returns the ray element at a given time using a linear interpolation
			/**
			 * If the time exceeds the propagation time of the ray, the last element is returned.
			 */
			CRayElement AtTime( const double& time ) const;
			//! Returns the ray element closest to a given time using a nearest neighbor approach.
			const CRayElement& Nearest( const double& time ) const;

		private:
			CRay::const_iterator IteratorAfterTime( const double& time ) const;

			// MINIMUM RECEIVER DISTANCE
		public:
			//! Returns a pointer to ray receiver distance data for the given receiver position. Returns nullptr if data does not exist.
			const CRayReceiverData* ReceiverDistanceData( const VistaVector3D& receiverPos ) const;

			//! Updates the distance to given receiver using the last point of the ray. Returns true if distance became smaller.
			/**
			 * To be called after each integration step.
			 */
			void UpdateMinimumReceiverDistance( const VistaVector3D& receiverPos );

			//! Returns true if the receiver distance has been updated for at least one receiver during the last integration time step.
			bool ReceiverDistanceUpdatedOnLastTimeStep( );

			//! Increases the accuracy of each receiver distance using a linear interpolation to adjacent ray points.
			/**
			 * To be called after the ray tracing has been finished.
			 */
			void FinalizeMinimumReceiverDistances( );

		private:
			void InterpolateToRealMinimumPosition( const VistaVector3D& receiverPos );
		};
	} // namespace AtmosphericRayTracing
} // namespace ITAPropagationPathSim

#endif // IW_ITA_PROPAGATIONPATHSIM_ART_RAYS

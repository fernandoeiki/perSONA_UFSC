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

#ifndef IW_ITA_BASE_TRIANGULATION
#define IW_ITA_BASE_TRIANGULATION

#include <ITABaseDefinitions.h>
#include <VistaBase/VistaVector3D.h>
#include <VistaMath/VistaGeometries.h>
#include <vector>

namespace ITABase
{
	namespace Math
	{
		class ITA_BASE_API CTriangulation
		{
			class VAVec;
			class CLoudspeaker;

		public:
			// Legacy Constructor
			CTriangulation( const std::vector<VistaVector3D>& vv3Loudspeaker, const std::vector<std::string>& vsID, const std::vector<int>& viID,
			                const std::vector<int>& viChannel, const VistaVector3D& vReproductionCenterPos = VistaVector3D( 0, 0, 0 ) );
			CTriangulation( const std::vector<VistaVector3D>& vvLoudspeakerPos, const VistaVector3D& vReproductionCenterPos );
			CTriangulation( const std::vector<VistaVector3D>& vvLoudspeakerPos, const std::vector<VistaVector3D>& vvTriangulationIndices,
			                const VistaVector3D& vReproductionCenterPos = VistaVector3D( 0, 0, 0 ) );
			~CTriangulation( );

			int NumPoints( ) const;
			bool GetPointIndicesFromTriangle( const VistaTriangle& vtTriangle, VistaVector3D& v3PointIndices ) const;
			bool IsDelaunayTriangulation( const float epsilon = 1.0e-4 ) const;
			const VistaTriangle* GetTriangleIntersectedByPointDirection( const VistaVector3D& vPoint, VistaVector3D& vBarycentricCoords, int& iTriangleIndex,
			                                                             const bool bIsReferenced = false, const float epsilon = 1.0e-4 ) const;
			const VistaTriangle* GetTriangleIntersectedByPointDirection( const VistaVector3D& vPoint, VistaVector3D& vBarycentricCoords, const bool bIsReferenced = false,
			                                                             const float epsilon = 1.0e-4 ) const;
			const VistaTriangle* GetTriangleIntersectedByPointDirection( const VistaVector3D& vPoint, const bool bIsReferenced = false,
			                                                             const float epsilon = 1.0e-4 ) const;

			// Operators
			inline VistaTriangle operator[]( int i ) const { return m_vtTriangulation[i]; }

			inline VistaVector3D operator( )( int i ) const { return m_vv3TriangulationIndices[i]; }

		private:
			/* new Implementation @LVO */
			std::vector<VistaVector3D> m_vv3LoudspeakerPos;
			VistaVector3D m_v3CenterPosition;
			std::vector<VistaVector3D> m_vv3TriangulationIndices;
			std::vector<VistaTriangle> m_vtTriangulation;

			/* Implementation from VBAPFreeFieldRenderer */
			class VAVec3
			{
			public:
				double x, y, z;
			};
			// Loudspeaker
			class CLoudspeaker
			{
			public:
				std::string sIdentifier;
				int iIdentifier;
				int iChannel;
				VAVec3 pos;
			};

			std::vector<CLoudspeaker> m_voLoudspeaker; //!< List of all loudspeaker for the VBAP setup
			// The triangulation safed as a VistaVector with each entry in the vector corresponding to the index of a speaker
			std::vector<std::vector<CLoudspeaker> >
			    m_voTriangulationLoudspeaker; //!< Triangulation all loudspeaker for the VBAP setup; Entries are the actual loudspeaker according to m_voLoudspeaker

			void Triangulate( );
		};

		// ---------- Helper functions ----------
		float calculateCircumcenter3D( const VistaTriangle& tTriangle, VistaVector3D& vCenter );
		float sphereEquation( const VistaVector3D& vCenter, const VistaVector3D& vPoint );
	} // namespace Math
} // namespace ITABase

#endif // IW_ITA_BASE_TRIANGULATION
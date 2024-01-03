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


// ITAGeo
#include <ITAGeo/Base.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Halfedge/MeshModel.h>
#include <ITAGeo/ModelBase.h>
#include <ITAGeo/Utils.h>


namespace ITAGeo
{
	namespace Urban
	{
		namespace RTree
		{
			// Typedefs
			typedef OpenMesh::PolyMesh_ArrayKernelT<> CITAMesh;

			//! Buildings RTree class
			/**
			 * @todo
			 *
			 */
			class ITA_GEO_API CBuildings
			{
			public:
				//---Constructor and Destructor---------------------------------------------
				CBuildings( );

				~CBuildings( );

				//---Public member functions------------------------------------------------

				void Create( const std::vector<Halfedge::CMeshModelShared>& vpBuildings );

				void GetIlluminableBuildings( std::set<Halfedge::CMeshModelShared>& spBuildingsOut, const VistaPlane& oPlaneIn );

				void GetIlluminableBuildings( std::set<Halfedge::CMeshModelShared>& spBuildingsOut, CITAMesh* pMesh, CITAMesh::FaceHandle hFace );

				void GetIlluminableBuildnigs( std::set<Halfedge::CMeshModelShared>& spBuildingsOut, CITAMesh* pMesh, CITAMesh::HalfedgeHandle hHalfedge );

				//---Public member variables------------------------------------------------

			private:
				//---Private member functions-----------------------------------------------

				inline void SetVertices( )
				{
					for( auto& pBuilding: m_vpBuildings )
					{
						VistaVector3D v3BuildingMin, v3BuildingMax;
						pBuilding->GetBoundingBoxAxisAligned( v3BuildingMin, v3BuildingMax );

						for( int i = 0; i < 3; i++ )
						{
							m_v3TreeMin[i] = std::min( m_v3TreeMin[i], v3BuildingMin[i] );
							m_v3TreeMax[i] = std::max( m_v3TreeMax[i], v3BuildingMax[i] );
						}
					}

					// Add the eight axes aligned vertices
					m_v3TreeVertices.push_back( m_v3TreeMin );
					m_v3TreeVertices.push_back( VistaVector3D( m_v3TreeMin[0], m_v3TreeMin[1], m_v3TreeMax[2] ) );
					m_v3TreeVertices.push_back( VistaVector3D( m_v3TreeMin[0], m_v3TreeMax[1], m_v3TreeMin[2] ) );
					m_v3TreeVertices.push_back( VistaVector3D( m_v3TreeMin[0], m_v3TreeMax[1], m_v3TreeMax[2] ) );
					m_v3TreeVertices.push_back( VistaVector3D( m_v3TreeMax[0], m_v3TreeMin[1], m_v3TreeMin[2] ) );
					m_v3TreeVertices.push_back( VistaVector3D( m_v3TreeMax[0], m_v3TreeMin[1], m_v3TreeMax[2] ) );
					m_v3TreeVertices.push_back( VistaVector3D( m_v3TreeMax[0], m_v3TreeMax[1], m_v3TreeMin[2] ) );
					m_v3TreeVertices.push_back( m_v3TreeMax );
				};

				inline void CreateBranches( )
				{
					// Create 8 building vector vectors
					std::vector<std::vector<Halfedge::CMeshModelShared>> vvpBranchBuildings;
					vvpBranchBuildings.resize( 8 );

					// Points, where branches are sub-divided into. Mid points between max and min.
					float fSubDivideX = m_v3TreeMin[Vista::X] + m_v3TreeMax[Vista::X] / 2;
					float fSubDivideY = m_v3TreeMin[Vista::Y] + m_v3TreeMax[Vista::Y] / 2;
					float fSubDivideZ = m_v3TreeMin[Vista::Z] + m_v3TreeMax[Vista::Z] / 2;

					// Add building to branchbuildings vector according to its location
					for( auto& pBuilding: m_vpBuildings )
					{
						VistaVector3D v3BuildingMin, v3BuildingMax;
						pBuilding->GetBoundingBoxAxisAligned( v3BuildingMin, v3BuildingMax );

						if( v3BuildingMin[2] < fSubDivideZ )
						{
							if( v3BuildingMin[1] < fSubDivideY )
							{
								if( v3BuildingMin[0] < fSubDivideX )
								{
									vvpBranchBuildings[0].push_back( pBuilding );
								}
								else
								{
									vvpBranchBuildings[1].push_back( pBuilding );
								}
							}
							else
							{
								if( v3BuildingMin[0] < fSubDivideX )
								{
									vvpBranchBuildings[2].push_back( pBuilding );
								}
								else
								{
									vvpBranchBuildings[3].push_back( pBuilding );
								}
							}
						}
						else
						{
							if( v3BuildingMin[1] < fSubDivideY )
							{
								if( v3BuildingMin[0] < fSubDivideX )
								{
									vvpBranchBuildings[4].push_back( pBuilding );
								}
								else
								{
									vvpBranchBuildings[5].push_back( pBuilding );
								}
							}
							else
							{
								if( v3BuildingMin[0] < fSubDivideX )
								{
									vvpBranchBuildings[6].push_back( pBuilding );
								}
								else
								{
									vvpBranchBuildings[7].push_back( pBuilding );
								}
							}
						}
					}

					// For each subdivided building vector, create a branch
					for( auto& vpBuildingsCurrentBranch: vvpBranchBuildings )
					{
						if( vpBuildingsCurrentBranch.size( ) > 0 )
						{
							auto pBranch = std::make_shared<CBuildings>( );
							pBranch->Create( vpBuildingsCurrentBranch );

							m_vpBranches.push_back( pBranch );
						}
					}
				};

				//---Private member variables-----------------------------------------------

				// Minimum and maximum of bounding box as well as vertices of box
				VistaVector3D m_v3TreeMin;
				VistaVector3D m_v3TreeMax;
				std::vector<VistaVector3D> m_v3TreeVertices;

				// Vector of building mesh models within bounding box
				std::vector<Halfedge::CMeshModelShared> m_vpBuildings;

				// Branches
				std::vector<std::shared_ptr<CBuildings>> m_vpBranches;
			};

		} // namespace RTree
	}     // namespace Urban
} // namespace ITAGeo

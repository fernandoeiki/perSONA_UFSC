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

#ifndef INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_CONVEX_DIFFRACTION_ENGINE
#define INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_CONVEX_DIFFRACTION_ENGINE

#include <ITAPropagationPathSim/Definitions.h>

// ITA includes
#include <ITAGeo/Base.h>
#include <ITAGeo/Halfedge/MeshModel.h>

namespace ITAPropagationPathSim
{
	namespace ConvexDiffraction
	{
		//! Diffraction engine
		/**
		 * Calculates acoustic propagations paths between an emitter and a sensor
		 * taking geometry data into account, that include diffraction around
		 * and off objects.
		 *
		 * Different abortion criteria can be used.
		 *
		 * Abstract result can be visualized using CITAGeoHalfedgeMeshModel
		 * and, for an acoustic simulation, acoustic propagation filters can be
		 * generated using CITADiffractionFilter.
		 *
		 * @sa CITADiffractionFilter
		 */
		class ITA_PROPAGATION_PATH_SIM_API CEngine
		{
		public:
			//! Set of criteria when to stop the algorithm
			struct AbortionCriteria
			{
				int iNumMaxDiffractions;
				double dMaxDiffractionAngleRad;
				double dMaxAccumulatedDiffractionAngleRad;
				int iDiffractionPreparationOrder;

				inline AbortionCriteria( ) { SetDefaults( ); };

				inline void SetDefaults( )
				{
					iNumMaxDiffractions                = ITAGeo::DiffractionOrder::DIFFRACTION_ORDER_5;
					dMaxAccumulatedDiffractionAngleRad = 2 * Vista::Pi;
					dMaxDiffractionAngleRad            = Vista::Pi;
					iDiffractionPreparationOrder       = ITAGeo::DiffractionOrder::DIFFRACTION_ORDER_3;
				};

				inline bool Validate( ) const
				{
					if( iDiffractionPreparationOrder < iNumMaxDiffractions )
						return false;
					return true;
				};

				//! STL stream output operator
				inline friend std::ostream& operator<<( std::ostream& os, const AbortionCriteria& oAC )
				{
					os << "[ DiffractionAbortionCriteria ]" << std::endl;
					os << "  1. Maximum diffraction path order: " << oAC.iNumMaxDiffractions << std::endl;
					os << "  2. Maximum preparation diffraction order: " << oAC.iDiffractionPreparationOrder << std::endl;
					os << "  3. Maximum single diffraction angle (radiants): " << oAC.dMaxDiffractionAngleRad << std::endl;
					os << "  4. Maximum accumulated diffraction angle (radiants): " << oAC.dMaxAccumulatedDiffractionAngleRad << std::endl;

					return os;
				}

			} oAbortionCriteria;

			inline virtual ~CEngine( ) { };

			//! Factory method to create an instance of the diffraction engine
			/**
			 * With a diffraction engine, sound propagation paths with diffraction can be calculated.
			 *
			 * @param[in] pModel Acoustic mesh model
			 * @param[in] pAbstractSource An arbitrary anchor from where diffraction calculation will be driven (usually also the sound source, but not limited to)
			 * @param[in] pAbstractTarget An arbitrary anchor where the diffraction calculation will finalize all propagation paths.
			 *
			 * @sa AbortionCriterium
			 */
			static CEngine* Create( const ITAGeo::Halfedge::CMeshModel* pModel, std::shared_ptr<ITAGeo::CPropagationAnchor> pAbstractSource,
			                        std::shared_ptr<ITAGeo::CPropagationAnchor> pAbstractTarget );
			virtual bool CalculateDiffractionPaths( ITAGeo::CPropagationPathList& lPaths ) = 0;
			void SetDefaultAbortionCriteria( );
			virtual void GetCombinedDiffractionGradientVisualization( ITAGeo::Halfedge::CMeshModel* pModel ) const   = 0;
			virtual void GetFromSourceDiffractionGradientVisualization( ITAGeo::Halfedge::CMeshModel* pModel ) const = 0;
			virtual void GetFromTargetDiffractionGradientVisualization( ITAGeo::Halfedge::CMeshModel* pModel ) const = 0;
			virtual void GetPropagationPathCandidatesVisualization( ITAGeo::CPropagationPathList& lPropCandidates )  = 0;

		protected:
			//! Protected default constructor, use Create() instead
			inline CEngine( ) { };
		};
	} // namespace ConvexDiffraction
} // namespace ITAPropagationPathSim

#endif // INCLUDE_WATCHER_ITA_PROPAGATION_PATH_SIM_CONVEX_DIFFRACTION_ENGINE

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

#ifndef IW_ITA_GEO_DIRECTIVITY_DAFF_IMPULSE_RESPONSE
#define IW_ITA_GEO_DIRECTIVITY_DAFF_IMPULSE_RESPONSE

#include "../Coordinates.h"
#include "../Definitions.h"
#include "Base.h"
#include "DAFF_Format.h"

#include <ITAFiniteImpulseResponse.h>
#include <ITAMultichannelFiniteImpulseResponse.h>

namespace ITAGeo
{
	namespace Directivity
	{
		class ITA_GEO_API CDAFF_ImpulseResponse : public CDAFF_Format
		{
		public:
			CDAFF_ImpulseResponse( );
			CDAFF_ImpulseResponse( const std::string& sFilePath );
			virtual ~CDAFF_ImpulseResponse( );

			float GetFilterLengthSamples( ) const;

			void GetNearestNeighbourImpulseResponse( const ITAGeo::Coordinates::CSpherical& oDirection, ITABase::CFiniteImpulseResponse& oFIR,
			                                         const int iChannelIndex = 0 ) const;
			void GetNearestNeighbourImpulseResponse( const ITAGeo::Coordinates::CSpherical& oDirection, ITASampleBuffer& sbFIR, const int iChannelIndex = 0 ) const;
			void GetNearestNeighbourImpulseResponse( const ITAGeo::Coordinates::CSpherical& oDirection, ITABase::CMultichannelFiniteImpulseResponse& oFIR ) const;

			//! Rerturns the mean value of the TOA in seconds (for adjustements of delay
			float GetMeanTimeOfArrival( ) const;
		};
	} // namespace Directivity
} // namespace ITAGeo

#endif // IW_ITA_GEO_DIRECTIVITY_DAFF_IMPULSE_RESPONSE

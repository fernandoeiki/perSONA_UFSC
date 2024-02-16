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

#ifndef IW_ITA_GEO_DIRECTIVITY_DAFF_MAGINTUDE_SPECTRUM
#define IW_ITA_GEO_DIRECTIVITY_DAFF_MAGINTUDE_SPECTRUM

#include <ITAGeo/Coordinates.h>
#include <ITAGeo/Definitions.h>
#include <ITAGeo/Directivity/Base.h>
#include <ITAGeo/Directivity/DAFF_Format.h>
#include <ITAThirdOctaveMagnitudeSpectrum.h>

namespace ITAGeo
{
	namespace Directivity
	{
		class ITA_GEO_API CDAFF_MagnitudeSpectrum : public CDAFF_Format
		{
		public:
			CDAFF_MagnitudeSpectrum( );
			CDAFF_MagnitudeSpectrum( const std::string& sFilePath );
			virtual ~CDAFF_MagnitudeSpectrum( );

			int GetNumCenterFrequencies( ) const;
			void GetNearestNeighbourMagnitudeSpectrum( const ITAGeo::Coordinates::CSpherical& oDirection, ITABase::CThirdOctaveMagnitudeSpectrum& oSpectrum,
			                                           const int iChannelIndex = 0 ) const;
			inline void MultiplyNearestNeighbourMagnitudeSpectrum( const ITAGeo::Coordinates::CSpherical& oDirection, ITABase::CThirdOctaveMagnitudeSpectrum& oSpectrum,
			                                                       const int iChannelIndex = 0 ) const
			{
				ITABase::CThirdOctaveFactorMagnitudeSpectrum oTempSpectrum;
				GetNearestNeighbourMagnitudeSpectrum( oDirection, oTempSpectrum, iChannelIndex );
				oSpectrum.Multiply( oTempSpectrum );
			};
		};
	} // namespace Directivity
} // namespace ITAGeo

#endif // IW_ITA_GEO_DIRECTIVITY_DAFF_MAGINTUDE_SPECTRUM

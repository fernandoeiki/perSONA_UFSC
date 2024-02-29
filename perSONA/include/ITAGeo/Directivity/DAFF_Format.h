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

#ifndef IW_ITA_GEO_DIRECTIVITY_DAFF_FORMAT
#define IW_ITA_GEO_DIRECTIVITY_DAFF_FORMAT

#include <ITAGeo/Definitions.h>
#include <ITAGeo/Directivity/Base.h>

class DAFFReader;

namespace ITAGeo
{
	namespace Directivity
	{
		//! Directivity format class for the OpenDAFF
		/**
		 * This class partly implements the directivity base class
		 * to combine methods that are re-used across all content
		 * types of DAFF. Please instatiate a DAFF domain type directly
		 * or use the generic reader interface and work with the DAFF API
		 * directly.
		 */
		class ITA_GEO_API CDAFF_Format : public IDirectivity
		{
		public:
			CDAFF_Format( );
			CDAFF_Format( const std::string& sFilePath );
			virtual ~CDAFF_Format( );

			void LoadFromFile( const std::string& sFilePath );

			//! Throws ITAException if no file has been loaded
			int GetNumChannels( ) const;

		protected:
			DAFFReader* m_pDAFFReader;
		};
	} // namespace Directivity
} // namespace ITAGeo

#endif // IW_ITA_GEO_DIRECTIVITY_DAFF_FORMAT

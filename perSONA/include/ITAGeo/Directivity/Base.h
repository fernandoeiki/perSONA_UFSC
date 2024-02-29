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

#ifndef IW_ITA_GEO_DIRECTIVITY_BASE
#define IW_ITA_GEO_DIRECTIVITY_BASE

// ITAGeo includes
#include <ITAGeo/Definitions.h>
#include <ITATypes.h>
#include <string>

namespace ITAGeo
{
	namespace Directivity
	{
		//! Directivity base class
		/**
		 * Defines the format and domain of a directivity, e.g. based on a file
		 * or a function in time/frequency/SH domain.
		 *
		 */
		class ITA_GEO_API IDirectivity
		{
		public:
			IDirectivity( );
			virtual ~IDirectivity( );

			enum Format
			{
				NONE = 0,            //!< No data format specified
				OPENDAFF,            //!< Directivity based on the OpenDAFF format
				FUNCTIONAL,          //!< Directivity based on the evaluation of a function
				SPHERICAL_HARMONICS, //!< Directivity based on a set of spherical harmonics coefficients
			};

			//! Return string format (for casting)
			inline int GetFormat( ) const { return m_eFormat; };

			inline ITADomain GetDomain( ) const { return m_eDomain; };

			//! Set directivity name
			inline void SetName( const std::string& sName ) { m_sName = sName; };

			//! Get directivity name
			inline std::string GetName( ) const { return m_sName; };

			//! Get directivity format as string
			inline std::string GetFormatStr( ) const
			{
				switch( m_eFormat )
				{
					case OPENDAFF:
						return "OpenDAFF";
					case SPHERICAL_HARMONICS:
						return "SH";
					case NONE:
					default:
						return "none";
				}
			};

			inline std::string GetDomainStr( ) const { return toString( m_eDomain ); };

			//! Returns the number of channels
			virtual int GetNumChannels( ) const = 0;

		protected:
			inline void SetFormat( int eFormat ) { m_eFormat = eFormat; };

			void SetDomain( ITADomain eDomain ) { m_eDomain = eDomain; };


		private:
			int m_eFormat;
			ITADomain m_eDomain;
			std::string m_sName;
		};
	} // namespace Directivity
} // namespace ITAGeo

#endif // IW_ITA_GEO_DIRECTIVITY_BASE

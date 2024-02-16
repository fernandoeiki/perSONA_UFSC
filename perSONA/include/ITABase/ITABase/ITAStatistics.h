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

#ifndef INCLUDE_WATCHER_ITA_STATISTICS
#define INCLUDE_WATCHER_ITA_STATISTICS

// ITABase
#include <ITABaseDefinitions.h>
#include <algorithm>
#include <sstream>
#include <string>


namespace ITABase
{
	//! Statistical values class
	/**
	 * JSON exporter available: ITABase::Utils::JSON::Export( CStatistics(), "stats.json" );
	 */

	class ITA_BASE_API CStatistics
	{
	public:
		//! Konstruktor
		inline CStatistics( std::string sName = "", std::string sUnits = "s" ) : sName( sName ), sUnits( sUnits ) { Reset( ); };

		inline void Reset( )
		{
			dMean = dStdDev = dMin = dMax = 0.0;
			uiNumSamples                  = 0;
		};

		inline std::string ToString( ) const
		{
			std::stringstream ss;
			ss << dMean << " ( " << dStdDev << " ) [ " << dMin << " ..  " << dMax << " ], N = " << uiNumSamples << std::endl;
			return ss.str( );
		};

	public:
		double dMean, dStdDev, dMin, dMax;
		std::string sUnits, sName;
		unsigned int uiNumSamples;
	};

	//! Outstream operator
	inline std::ostream& operator<<( std::ostream& os, ITABase::CStatistics& stats )
	{
		os << stats.ToString( );
		return os;
	};
} // namespace ITABase

#endif // INCLUDE_WATCHER_ITA_STATISTICS

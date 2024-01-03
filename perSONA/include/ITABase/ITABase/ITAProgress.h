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

#ifndef IW_ITA_BASE_PROGRESS
#define IW_ITA_BASE_PROGRESS

#include <ITABaseDefinitions.h>
#include <string>

namespace ITABase
{
	//! A progress handler can be added to functions that are potentially time consuming to keep track of progress and to abort calculation
	/**
	 * Further improvements may introduce a granularity to keep down push message. Partly abstract only, still considered an interface as this is the main purpose.
	 */
	class ITA_BASE_API IProgressHandler
	{
	public:
		IProgressHandler( std::string sName = "unnamed" );
		~IProgressHandler( );

		void SetName( const std::string& sName );
		std::string GetName( ) const;

		void SetSection( const std::string& sSection );
		std::string GetSection( ) const;

		void SetItem( const std::string& sItem );
		std::string GetItem( ) const;

		virtual inline void PushProgressUpdate( std::string sSection, std::string sItem, float fProgressPercentage ) const;
		virtual inline void PushProgressUpdate( std::string sItem, float fProgressPercentage ) const;

		//!< Please implement push message, will be called by function
		/**
		 */
		virtual void PushProgressUpdate( float fProgressPercentage ) const = 0;

	private:
		mutable std::string m_sItem;    //!< Currently processed looping function or similar
		mutable std::string m_sSection; //!< Execution section, i.e. caller function
		std::string m_sName;            //!< Progress handler name, i.e. caller function or class or app
	};
} // namespace ITABase

#endif // IW_ITA_BASE_PROGRESS

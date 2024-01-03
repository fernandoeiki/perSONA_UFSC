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

#ifndef INCLUDE_WATCHER_ITA_EXCEPTION
#define INCLUDE_WATCHER_ITA_EXCEPTION

// ITABase
#include <ITABaseDefinitions.h>

// STL
#include <ostream>
#include <string>

//! Base class for exceptions
class ITA_BASE_API ITAException
{
public:
	//! Error types
	enum
	{
		UNKNOWN = 1,       //!< Unspecified
		OUT_OF_MEMORY,     //!< Out of memory
		INVALID_PARAMETER, //!< Invalid parameter
		MODAL_EXCEPTION,
		IO_ERROR,
		NOT_IMPLEMENTED,
		FILE_NOT_FOUND,
		PARSE_ERROR,
		SYNTAX_ERROR,
		CONFIG_ERROR,
		NETWORK_ERROR,
		LAST,
	};

	ITAException( int uiErrorcode = UNKNOWN, std::string sModule = "", std::string sReason = "" );
	inline virtual ~ITAException( ) { };

	std::string ToString( ) const;

	int iErrorCode;      //!< Error code
	std::string sModule; //!< Module name
	std::string sReason; //!< Versatile reason
};

// Helper macros
#define ITA_EXCEPT0( TYPE )                    throw ITAException( ITAException::TYPE, __FUNCTION__ );
#define ITA_EXCEPT1( TYPE, REASON )            throw ITAException( ITAException::TYPE, __FUNCTION__, REASON );
#define ITA_EXCEPT_INVALID_PARAMETER( REASON ) throw ITAException( ITAException::INVALID_PARAMETER, __FUNCTION__, REASON );
#define ITA_EXCEPT_NOT_IMPLEMENTED             throw ITAException( ITAException::NOT_IMPLEMENTED, __FUNCTION__ );

//! STL stream output operator
ITA_BASE_API std::ostream& operator<<( std::ostream& os, const ITAException& ex );

#endif

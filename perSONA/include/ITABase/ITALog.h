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

#ifndef INCLUDE_WATCHER_ITA_LOG
#define INCLUDE_WATCHER_ITA_LOG

#include "ITABaseDefinitions.h"

//! Ausgabe-Direktiven
enum
{
	ITALOG_OUTPUT_CONSOLE = 0, //!< Log to stdout, stderr
	ITALOG_OUTPUT_MSVC    = 1  //!< Log to the Visual Studio console ("OutputDebugString")
};

//! Log-Stufen
enum
{
	ITALOG_QUIET = 0, //!< Stumm
	ITALOG_ERROR = 1, //!< Fehler
	ITALOG_WARN  = 2, //!< Warnung
	ITALOG_INFO  = 3, //!< Information
	ITALOG_TRACE = 4  //!< Gesprächig
};

//! Flags
const int ITALOG_MODULENAME = 1 << 0;
const int ITALOG_SHORTNAME  = 1 << 1;
const int ITALOG_LEVELINFO  = 1 << 2;
const int ITALOG_TIMESTAMP  = 1 << 3;


//! Ausgabe-Funktionen
void ITA_BASE_API italog_printf( const char* pszModuleName, int iFlags, const char* format... );
void ITA_BASE_API italog_msvc( const char* pszModuleName, int iFlags, const char* format... );


// --= Makros für verschiedene Ausgabeversionen mit mehr oder weniger Parametern =--

//! Einfache Ausgabe ohne weitere Argumente
#define ITALOG_PRINTF0( ... )                \
	{                                        \
		italog_printf( "", 0, __VA_ARGS__ ); \
	}
#define ITALOG_PRINTF1( SHORTNAME, ... )                           \
	{                                                              \
		italog_printf( SHORTNAME, ITALOG_SHORTNAME, __VA_ARGS__ ); \
	}
#define ITALOG_PRINTF2( MODULENAME, ... )                            \
	{                                                                \
		italog_printf( MODULENAME, ITALOG_MODULENAME, __VA_ARGS__ ); \
	}
#define ITALOG_PRINTF9( MODULE, NAME, SHORTNAME, FLAGS, LOGLEVEL, LOGTYPE, ... ) \
	{                                                                            \
		if( LOGLEVEL >= LOGTYPE )                                                \
		{                                                                        \
			italog_printf( MODULENAME, FLAGS, __VA_ARGS__ );                     \
		}                                                                        \
	}

#define ITALOG_MSVC0( ... )                \
	{                                      \
		italog_msvc( "", 0, __VA_ARGS__ ); \
	}
#define ITALOG_MSVC1( SHORTNAME, ... )                           \
	{                                                            \
		italog_msvc( SHORTNAME, ITALOG_SHORTNAME, __VA_ARGS__ ); \
	}

#endif // INCLUDE_WATCHER_ITA_LOG

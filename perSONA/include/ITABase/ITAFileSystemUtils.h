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

#ifndef INCLUDE_WATCHER_ITA_FILE_SYSTEM_UTILS
#define INCLUDE_WATCHER_ITA_FILE_SYSTEM_UTILS

#include <ITABaseDefinitions.h>
#include <ITATypes.h>

// STL includes
#include <string>
#include <vector>

// Global constants
#ifndef WIN32
const char PATH_SEPARATOR = '/';
#else
const char PATH_SEPARATOR = '\\';
#endif

//! Prüfen ob Dateisystem-Pfad existiert
ITA_BASE_API bool doesPathExist( const std::string& sPath );

//! Prüfen ob ein Pfad existiert und auf eine Datei zeigt
ITA_BASE_API bool doesFileExist( const std::string& sPath );

//! Prüfen ob ein Pfad existiert und auf ein Verzeichnis zeigt
ITA_BASE_API bool doesDirectoryExist( const std::string& sPath );

namespace ITA
{
	namespace FileSystemUtils
	{
		ITA_BASE_API std::string GetAbsolutePath( const std::string& sFilePath_RelativeToExecutionFolder );
		ITA_BASE_API std::string GetBasePath( const std::string& sFilePath );
	} // namespace FileSystemUtils
} // namespace ITA

//! Prüfen ob ein Pfad auf eine Datei zeigt
ITA_BASE_API bool isFile( const std::string& sPath );

//! Prüfen ob ein Pfad auf ein Verzeichnis zeigt
ITA_BASE_API bool isDirectory( const std::string& sPath );

//! Verzeichnis erstellen
ITA_BASE_API bool makeDirectory( const std::string& sPath );

//! Suffix eines Dateinamens zurückgeben
ITA_BASE_API std::string getFilenameSuffix( const std::string& sFilename );

//! Return filename without the suffix
ITA_BASE_API std::string stripFilenameSuffix( const std::string& sFilename );

//! Get filename/foldername from a path to a file/folder
ITA_BASE_API std::string getFilenameFromPath( const std::string& sPath );

//! Get directory path from a path to a file/folder
ITA_BASE_API std::string getDirectoryFromPath( const std::string& sPath );

//! Größe einer Datei in Bytes zurückgeben (Gibt im Fehlerfall -1 zurück)
ITA_BASE_API int64_t getFileSize( const std::string& sFilename );

//! Einen Pfad aus mehreren Teilen zusammenbauen (Teile dürfen leer sein!)
ITA_BASE_API std::string combinePath( std::string p1, std::string p2 = "", std::string p3 = "", std::string p4 = "" );

//! Bringt die Pfad-Separatoren (Slash, Backslash) in das Format des Systems
ITA_BASE_API std::string correctPath( const std::string& sPath );

//! List files in directory
/**
 * Lists only files in a directory path (excludes directories)
 *
 * \param sPath Path to the directory
 * \param sFilenames List of filenames in path
 *
 * \return True, if valid path, False if not a path or not existent
 */
ITA_BASE_API bool listFilesInDirectory( const std::string& sPath, std::vector<std::string>& vsFilenames );

#endif // INCLUDE_WATCHER_ITA_FILE_SYSTEM_UTILS

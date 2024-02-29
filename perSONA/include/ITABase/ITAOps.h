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

#ifndef INCLUDE_WATCHER_ITA_OPS
#define INCLUDE_WATCHER_ITA_OPS

//--------------------------------------------------------------------------------------
// includes
//--------------------------------------------------------------------------------------

#include <ITABaseDefinitions.h>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <map>
#include <string>
#include <vector>

//--------------------------------------------------------------------------------------

float ITA_BASE_API roundIt( const float Zahl, const int Stellen );
//--------------------------------------------------------------------------------------
// define
//--------------------------------------------------------------------------------------

void ITA_BASE_API getUniqueIDsFromList( const std::vector<unsigned int> &inputList, std::list<unsigned int> &outputList );

void ITA_BASE_API getUniqueIDsFromList( unsigned int *&inputList, const int &inputListLength, std::list<unsigned int> &outputList );

void ITA_BASE_API getUniqueIDsFromList( const std::list<unsigned int> &inputList, std::list<unsigned int> &outputList );

unsigned int ITA_BASE_API getID_BinaryToInteger( const std::list<unsigned int> &inputList );

void ITA_BASE_API getID_BinaryToInteger( const std::list<unsigned int> &inputList, const unsigned int &roomCombinationListID );

void ITA_BASE_API storeCurrentSubPowerSet( const std::list<unsigned int> &my_power_set,    // IN
                                           std::list<unsigned int> &valid_power_set_ids ); // OUT

void ITA_BASE_API buildSubPowerSets( unsigned int &counter, unsigned int startIndex, const std::list<unsigned int> &my_power_set, std::list<unsigned int> &my_helper,
                                     std::list<unsigned int> &valid_power_set_ids );

void ITA_BASE_API buildSubPowerSets( const std::list<unsigned int> &my_power_set, std::list<unsigned int> &valid_power_set_ids );


// --= Interpolationsroutinen =--

//! Einfache lineare Interpolation zwischen zwei Vektoren
void ITA_BASE_API interpolate( std::vector<float> &result, const std::vector<float> &a, const std::vector<float> &b );

//! Interpolationroutine
/**
 * \param x				Ergebnis der Interpolation
 * \param y				Zu interpolierende Daten
 * \param xDomainScale	Skala des gewünschten Ergebnisses (gleiche Grösse wie x)
 * \param yDomainScale	Skala der Eingabedaten (gleiche Grösse wie y)
 * \param IntType		Gewünschte Interpolationsart: 0 für Halteglied, 1 für lineare Interpolation, 2 für Spline-Interpolation
 */
void ITA_BASE_API Interpolation( std::vector<float> &x, const std::vector<float> &y, const std::vector<float> &xDomainScale, const std::vector<float> &yDomainScale,
                                 const unsigned int IntType );


// --= Insert-Routinen =--

//! Fügt das Einzelfilter in das Gesamtfilter ein (Float-Vector zu Float-Vector Implementierung)
void ITA_BASE_API Insert( const std::vector<float> &pfSource, std::vector<float> &pfDest, const float fOffset, const unsigned int uiLength );

//! Fügt das Einzelfilter in das Gesamtfilter ein (Float-Feld zu Float-Vector Implementierung)
void ITA_BASE_API Insert( const float *pfSource, std::vector<float> &pfDest, const float fOffset, const unsigned int uiLength );

//! Fügt das Einzelfilter in das Gesamtfilter mit Skalierung ein
void ITA_BASE_API Insert_scaled( const std::vector<float> &pfSource, std::vector<float> &pfDest, const float iDestinationOffset, const unsigned int uiLength,
                                 const float fScaleFactor );

//! Fügt das Einzelfilter in das Gesamtfilter mit Skalierung ein
void ITA_BASE_API Insert_scaled( const std::vector<float> &pfSource, std::vector<float> &pfDest, const unsigned int uiDestinationOffset, const unsigned int uiLength,
                                 const float scaleFactor );

//! Fügt das Einzelfilter in das Gesamtfilter mit Skalierung ein
void ITA_BASE_API Insert_scaled( const float *pfSource, std::vector<float> &pfDest, const unsigned int uiDestinationOffset, const unsigned int uiLength,
                                 const float fScaleFactor );

//! Fügt das Einzelfilter in das Gesamtfilter mit Skalierung ein
void ITA_BASE_API Insert_scaled( const float *pfSource, float *pfDest, const unsigned int uiDestinationOffset, const unsigned int uiNumSamples,
                                 const float fScaleFactor );

//! Fügt das Einzelfilter in das Gesamtfilter mit Skalierung ein
void ITA_BASE_API Insert_scaled( const std::vector<float> &pfSource, std::vector<float> &pfDest, const unsigned int iInsertPosition, const float fScaleFactor );

//! Fügt das Einzelfilter in das Gesamtfilter mit Skalierung ein
void ITA_BASE_API Insert_scaled( const float *pfSource, float *pfDest, const int iDestinationOffset, const int iNumSamples, const float fScaleFactor );

//! cartesian2polar - converts a complex number from real/imaginary to magnitude/phase representation
void ITA_BASE_API cartesian2polar( float real, float imaginary, float &magnitude, float &phase );

//! polar2cartesian - converts a complex number from magnitude/phase to real/imaginary representation
void ITA_BASE_API polar2cartesian( float magnitude, float phase, float &real, float &imaginary );

int ITA_BASE_API readPortalParameter( const std::string filename_fullPath, std::vector<float> &transfer_function, std::string &portal_name, std::string &portal_notes,
                                      std::string &portal_surface_material );

/**
 *determineCurrentValidPowerSetIDs
 *
 **/
void ITA_BASE_API determineCurrentValidPowerSetIDs( const std::list<unsigned int> &currentValidRoomIDs, std::list<unsigned int> &currentValidPowerSetIDs );

//! Schreibt den Inhalt eines std::vector mit Float-Werten in den RavenOutput (zu Debugging-zwecken)
/**
 * \param vfVec Der Vektor, der runtergeschrieben werden soll
 * \param sName Dateiname
 *
 * \note Exportiert die Daten in den Ordner "..\RavenOutput" (muss existieren!)
 */
void ITA_BASE_API writeVector( const std::vector<float> vfVec, std::string sName );

#endif // INCLUDE_WATCHER_ITA_OPS

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

#ifndef INCLUDE_WATCHER_ITA_CONFIG_UTILS
#define INCLUDE_WATCHER_ITA_CONFIG_UTILS

#include <ITABaseDefinitions.h>
#include <string>
#include <vector>

/* +-----------------------------------------------------------------------------------------+
 * |                                                                                         |
 * |  Strukturelle Funktionen für INI-Dateien (Existenz von Sektionen, Schlüssel)            |
 * |                                                                                         |
 * +-----------------------------------------------------------------------------------------+ */

//! Prüfen ob eine INI-Datei existiert
ITA_BASE_API bool INIFileExists( const std::string& sINIFilename );

//! Prüfen ob eine INI-Datei die angegebene Sektion enthält (Case-Insensitive!)
ITA_BASE_API bool INIFileSectionExists( const std::string& sINIFilename, const std::string& sSection );

//! Liste der Namen aller Sektionen einer INI-Datei zurückgeben
ITA_BASE_API std::vector<std::string> INIFileGetSections( const std::string& sINIFilename );

//! Prüfen ob in einer Sektion einer INI-Datei der angegebene Schlüssel existiert (Case-Insensitive!)
ITA_BASE_API bool INIFileKeyExists( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! Liste der Schlüsselnamen einer Sektion in einer INI-Datei zurückgeben
ITA_BASE_API std::vector<std::string> INIFileGetKeys( const std::string& sINIFilename, const std::string& sSection );


//! Zu benutzende INI-Datei auswählen
/**
 * \note Falls die angegebene Datei nicht existiert wird eine ITAException ausgelöst.
 */
ITA_BASE_API void INIFileUseFile( const std::string& sINIFilename );

//! Zu benutzende Sektion auswählen
/**
 * \note Falls die angegebene Sektion nicht existiert wird eine ITAException ausgelöst.
 */
ITA_BASE_API void INIFileUseSection( const std::string& sSection );

//! Sektion zur Benutzung auswählen, falls diese existiert
/**
 * \return true  falls die Sektion existiert und ausgewählt wurde,
 *         false falls die Sektion nicht existiert
 */
ITA_BASE_API bool INIFileUseSectionIfExists( const std::string& sSection );

//! Benutzung der INI-Datei und Sektion zurücksetzen
/**
 * \note Stellt sicher dass keine Seiteneffekte bei Fehlern auftreten und sollte benutzt werden!
 */
ITA_BASE_API void INIFileUseNothing( );

/* +-----------------------------------------------------------------------------------------+
 * |                                                                                         |
 * |  Assertion-Funktionen: Lösen Ausnahmen aus, falls Bedingungen nicht erfüllt sind.       |
 * |                                                                                         |
 * +-----------------------------------------------------------------------------------------+ */

//! Sicherstellen das die angegebene INI-Datei existiert
ITA_BASE_API void INIFileRequireINIFile( const std::string& sINIFilename );

//! Sicherstellen das in der gegebenen INI-Datei die gegebene Sektion existiert
ITA_BASE_API void INIFileRequireSection( const std::string& sINIFilename, const std::string& sSection );

//! Sicherstellen das in der gegebenen INI-Datei der angegebene Schlüssel in der gegebenen Sektion existiert
/**
 * \note Der Schlüsselwert darf leer sein.
 */
ITA_BASE_API void INIFileRequireKey( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! Sicherstellen das in der gegebenen INI-Datei der angegebene Schlüssel in der gegebenen Sektion existiert und einen expliziten Wert hat
/**
 * \note Der Schlüsselwert darf leer sein.
 */
ITA_BASE_API void INIFileRequireNonemptyKey( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );


/* +----------------------------------------------------------------------------------------------+
 * |                                                                                              |
 * |  Implizite Lese-Funktionen                                                                   |
 * |                                                                                              |
 * |  Diese Funktionen geben Standardwerte zurück falls:                                          |
 * |                                                                                              |
 * |  - die Sektion nicht existiert.                                                              |
 * |  - der Schlüssel nicht existiert.                                                            |
 * |                                                                                              |
 * |  Diese Funktionen lösen Ausnahmen aus falls:                                                 |
 * |                                                                                              |
 * |  - die INI-Datei nicht existiert                                                             |
 * |  - der Wert nicht als gewünschter Datentyp interpretierbar ist.                              |
 * |                                                                                              |
 * +----------------------------------------------------------------------------------------------+ */

//! int-Wert aus INI-Datei lesen
/**
 * \note Tritt ein Fehler auf, so wird der Standardwert zurückgegeben.
 *       Fehler können z.B. auftreten falls:
 *
 *       - Die angebene INI-Datei nicht existiert
 *       - Die angebene Sektion und/oder der angegebene Schlüssel nicht existiert
 *       - Der vorgefundene Wert nicht als int-Wert interpretiert werden kann.
 */
ITA_BASE_API int INIFileReadInt( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, int iDefaultValue = -1 );

//! unsigned int-Wert aus INI-Datei lesen
/**
 * \note Tritt ein Fehler auf, so wird der Standardwert zurückgegeben.
 *       Mögliche Fehlerfälle sind bei getReadIntFromINIFile angegeben.
 */
ITA_BASE_API unsigned int INIFileReadUInt( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, unsigned int uiDefaultValue = 0 );

//! long-Wert aus INI-Datei lesen
/**
 * \note Tritt ein Fehler auf, so wird der Standardwert zurückgegeben.
 *       Mögliche Fehlerfälle sind bei getReadIntFromINIFile angegeben.
 */
ITA_BASE_API long INIFileReadLong( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, long lDefaultValue = -1 );

//! float-Wert aus INI-Datei lesen
/**
 * \note Tritt ein Fehler auf, so wird der Standardwert zurückgegeben.
 *       Mögliche Fehlerfälle sind bei getReadIntFromINIFile angegeben.
 */
ITA_BASE_API float INIFileReadFloat( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, float fDefaultValue = 0.0F );

//! double-Wert aus INI-Datei lesen
/**
 * \note Tritt ein Fehler auf, so wird der Standardwert zurückgegeben.
 *       Mögliche Fehlerfälle sind bei getReadIntFromINIFile angegeben.
 */
ITA_BASE_API double INIFileReadDouble( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, double dDefaultValue = 0.0 );

//! Booleschen Wert aus INI-Datei lesen
// Erkennt Zeichenketten Yes/No, Ja/Nein, True/False
/**
 * Diese Funktion vergleicht die vorgefundene Zeichenkette mit
 * "Ja"/"Nein", "Yes"/"No", "True"/"False" und "1"/"0". Der jeweils
 * erste Zeichenkette der oben aufgeführten Paare ergibt den Rückgabewert
 * true.
 *
 * \note Tritt ein Fehler auf, so wird der Standardwert zurückgegeben.
 *       Mögliche Fehlerfälle sind bei getReadIntFromINIFile angegeben.
 */
ITA_BASE_API bool INIFileReadBool( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, bool bDefaultValue = false );

//! Zeichenkette aus INI-Datei lesen
/**
 * \note Tritt ein Fehler auf, so wird der Standardwert zurückgegeben.
 *       Mögliche Fehlerfälle sind bei getReadIntFromINIFile angegeben.
 */
ITA_BASE_API std::string INIFileReadString( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, std::string sDefaultValue = "" );

//! Mit Kommas getrennte Liste von Strings aus INI-Datei lesen
ITA_BASE_API std::vector<std::string> INIFileReadStringList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey,
                                                             char cSeparator = ',' );

//! Mit Kommas getrennte Liste von int-Werten aus INI-Datei lesen und in template Enum-Typ konvertieren
template<typename TEnum>
std::vector<TEnum> INIFileReadEnumList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, char cSeparator = ',' )
{
	std::vector<std::string> vin = INIFileReadStringList( sINIFilename, sSection, sKey, cSeparator );
	std::vector<TEnum> vout;
	for( auto const& element: vin )
	{
		vout.push_back( static_cast<TEnum>( atoi( element.c_str( ) ) ) );
	}
	return vout;
};

//! Mit Kommas getrennte Liste von int-Werten aus INI-Datei lesen
ITA_BASE_API std::vector<int> INIFileReadIntList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, char cSeparator = ',' );

//! Mit Kommas getrennte Liste von unsigned int-Werten aus INI-Datei lesen
ITA_BASE_API std::vector<unsigned int> INIFileReadUIntList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey,
                                                            char cSeparator = ',' );

//! Mit Kommas getrennte Liste von float-Werten aus INI-Datei lesen
ITA_BASE_API std::vector<float> INIFileReadFloatList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, char cSeparator = ',' );

//! Mit Kommas getrennte Liste von double-Werten aus INI-Datei lesen
ITA_BASE_API std::vector<double> INIFileReadDoubleList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, char cSeparator = ',' );


/* +-----------------------------------------------------------------------------------------+
 * |                                                                                         |
 * |  Explizite Lese-Funktionen.                                                             |
 * |                                                                                         |
 * |  Diese Funktionen haben niemals Standardwerte und lösen Ausnahmen aus sobald:           |
 * |                                                                                         |
 * |  - die INI-Datei nicht existiert                                                        |
 * |  - die Sektion nicht existiert.                                                         |
 * |  - der Schlüssel nicht existiert.                                                       |
 * |  - der Schlüsselwert leer ist.                                                          |
 * |  - der Wert nicht als gewünschter Datentyp interpretierbar ist.                         |              |
 * |                                                                                         |
 * +-----------------------------------------------------------------------------------------+ */

//! int-Wert aus INI-Datei lesen (explizit)
ITA_BASE_API int INIFileReadIntExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! unsigned int-Wert aus INI-Datei lesen (explizit)
ITA_BASE_API unsigned int INIFileReadUIntExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! long-Wert aus INI-Datei lesen (explizit)
ITA_BASE_API long INIFileReadLongExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! float-Wert aus INI-Datei lesen (explizit)
ITA_BASE_API float INIFileReadFloatExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! double-Wert aus INI-Datei lesen (explizit)
ITA_BASE_API double INIFileReadDoubleExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! Booleschen Wert aus INI-Datei lesen (explizit)
ITA_BASE_API bool INIFileReadBoolExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! Zeichenkette aus INI-Datei lesen (explizit)
ITA_BASE_API std::string INIFileReadStringExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey );

//! Mit Kommas getrennte Liste von int-Werten aus INI-Datei lesen (explizit)
ITA_BASE_API std::vector<int> INIFileReadIntListExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, char cSeparator = ',' );

//! Mit Kommas getrennte Liste von unsigned int-Werten aus INI-Datei lesen (explizit)
ITA_BASE_API std::vector<unsigned int> INIFileReadUIntListExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey,
                                                                    char cSeparator = ',' );

//! Mit Kommas getrennte Liste von float-Werten aus INI-Datei lesen (explizit)
ITA_BASE_API std::vector<float> INIFileReadFloatListExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey,
                                                              char cSeparator = ',' );

//! Mit Kommas getrennte Liste von double-Werten aus INI-Datei lesen (explizit)
ITA_BASE_API std::vector<double> INIFileReadDoubleListExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey,
                                                                char cSeparator = ',' );

//! Mit Kommas getrennte Liste von Strings aus INI-Datei lesen
ITA_BASE_API std::vector<std::string> INIFileReadStringListExplicit( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey,
                                                                     char cSeparator = ',' );

/* +-----------------------------------------------------------------------------------------+
 * |                                                                                         |
 * |  Schreibfunktionen                                                                      |
 * |                                                                                         |
 * |  - Existiert eine INI-Datei nicht, so wird sie angelegt.                                |
 * |  - Existiert eine Sektion nicht, so wird sie angelegt.                                  |
 * |  - Existiert ein Schlüssel bereits, so wird sein Wert überschrieben                     |
 * |                                                                                         |
 * +-----------------------------------------------------------------------------------------+ */

//! int-Wert in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteInt( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, int iValue );

//! unsigned int-Wert in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteUInt( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, unsigned int uiValue );

//! long-Wert in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteLong( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, long lValue );

//! float-Wert in eine INI-Datei schreiben
/**
 * \param iDecimalPlaces Anzahl der Nachkommastellen [optional]
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteFloat( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, float fValue, int iDecimalPlaces = -1 );

//! double-Wert in eine INI-Datei schreiben
/**
 * \param iDecimalPlaces Anzahl der Nachkommastellen [optional]
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteDouble( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, double dValue, int iDecimalPlaces = -1 );

//! bool-Wert in eine INI-Datei schreiben
/**
 * \note Für true wird 1 geschrieben und für false 0
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteBool( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, bool bValue );

//! Zeichenkette in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteString( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, const std::string& sValue );


//! Liste von Enum-Werten (konvertiert nach int) in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
template<typename TEnum>
bool INIFileWriteEnumList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, const std::vector<TEnum>& veValues,
                           std::string sSeparator = ", " )
{
	return INIFileWriteString( sINIFilename, sSection, sKey, EnumVecToString( veValues, sSeparator ) );
};


//! Liste von int-Werten in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteIntList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, const std::vector<int>& viValues,
                                       std::string sSeparator = ", " );

//! Liste von unsigned int-Werten in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteUIntList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, const std::vector<unsigned int>& vuiValues,
                                        std::string sSeparator = ", " );

//! Liste von float-Werten in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteFloatList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, const std::vector<float>& vfValues,
                                         std::string sSeparator = ", " );

//! Liste von double-Werten in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteDoubleList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, const std::vector<double>& vdValues,
                                          std::string sSeparator = ", " );

//! Liste von Strings in eine INI-Datei schreiben
/**
 * \return true falls erfolgreich, false sonst
 */
ITA_BASE_API bool INIFileWriteStringList( const std::string& sINIFilename, const std::string& sSection, const std::string& sKey, const std::vector<std::string>& vsValues,
                                          std::string sSeparator = ", " );

/* +-----------------------------------------------------------------------------------------+
 * |                                                                                         |
 * |  Alias-Funktionen für vorausgewählte INI-Dateien und Sektionen                          |
 * |                                                                                         |
 * +-----------------------------------------------------------------------------------------+ */


ITA_BASE_API bool INIFileSectionExists( const std::string& sSection );
ITA_BASE_API std::vector<std::string> INIFileGetSections( );
ITA_BASE_API bool INIFileKeyExists( const std::string& sKey );
ITA_BASE_API std::vector<std::string> INIFileGetKeys( const std::string& sSection );

ITA_BASE_API void INIFileRequireSection( const std::string& sSection );
ITA_BASE_API void INIFileRequireKey( const std::string& sKey );
ITA_BASE_API void INIFileRequireNonemptyKey( const std::string& sKey );

ITA_BASE_API int INIFileReadInt( const std::string& sKey, int iDefaultValue = -1 );
ITA_BASE_API unsigned int INIFileReadUInt( const std::string& sKey, unsigned int uiDefaultValue = 0 );
ITA_BASE_API long INIFileReadLong( const std::string& sKey, long lDefaultValue = -1 );
ITA_BASE_API float INIFileReadFloat( const std::string& sKey, float fDefaultValue = 0.0F );
ITA_BASE_API double INIFileReadDouble( const std::string& sKey, double dDefaultValue = 0.0 );
ITA_BASE_API bool INIFileReadBool( const std::string& sKey, bool bDefaultValue = false );
ITA_BASE_API std::string INIFileReadString( const std::string& sKey, std::string sDefaultValue = "" );
ITA_BASE_API std::vector<int> INIFileReadIntList( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<unsigned int> INIFileReadUIntList( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<float> INIFileReadFloatList( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<double> INIFileReadDoubleList( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<std::string> INIFileReadStringList( const std::string& sKey, char cSeparator = ',' );

ITA_BASE_API int INIFileReadIntExplicit( const std::string& sKey );
ITA_BASE_API unsigned int INIFileReadUIntExplicit( const std::string& sKey );
ITA_BASE_API long INIFileReadLongExplicit( const std::string& sKey );
ITA_BASE_API float INIFileReadFloatExplicit( const std::string& sKey );
ITA_BASE_API double INIFileReadDoubleExplicit( const std::string& sKey );
ITA_BASE_API bool INIFileReadBoolExplicit( const std::string& sKey );
ITA_BASE_API std::string INIFileReadStringExplicit( const std::string& sKey );
ITA_BASE_API std::vector<int> INIFileReadIntListExplicit( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<unsigned int> INIFileReadUIntListExplicit( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<float> INIFileReadFloatListExplicit( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<double> INIFileReadDoubleListExplicit( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API std::vector<std::string> INIFileReadStringListExplicit( const std::string& sKey, char cSeparator = ',' );
ITA_BASE_API bool INIFileWriteInt( const std::string& sKey, int iValue );
ITA_BASE_API bool INIFileWriteUInt( const std::string& sKey, unsigned int uiValue );
ITA_BASE_API bool INIFileWriteLong( const std::string& sKey, long lValue );
ITA_BASE_API bool INIFileWriteFloat( const std::string& sKey, float fValue, int iDecimalPlaces = -1 );
ITA_BASE_API bool INIFileWriteDouble( const std::string& sKey, double dValue, int iDecimalPlaces = -1 );
ITA_BASE_API bool INIFileWriteBool( const std::string& sKey, bool bValue );
ITA_BASE_API bool INIFileWriteString( const std::string& sKey, const std::string& sValue );
ITA_BASE_API bool INIFileWriteIntList( const std::string& sKey, const std::vector<int>& viValues, std::string sSeparator = ", " );
ITA_BASE_API bool INIFileWriteUIntList( const std::string& sKey, const std::vector<unsigned int>& vuiValues, std::string sSeparator = ", " );
ITA_BASE_API bool INIFileWriteFloatList( const std::string& sKey, const std::vector<float>& vfValues, std::string sSeparator = ", " );
ITA_BASE_API bool INIFileWriteDoubleList( const std::string& sKey, const std::vector<double>& vdValues, std::string sSeparator = ", " );
ITA_BASE_API bool INIFileWriteStringList( const std::string& sKey, const std::vector<std::string>& vsValues, std::string sSeparator = ", " );

#endif // INCLUDE_WATCHER_ITA_CONFIG_UTILS
